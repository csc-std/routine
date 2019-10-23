#pragma once

#ifndef __CSC_THREAD__
#define __CSC_THREAD__
#endif

#include "csc.hpp"
#include "csc_ext.hpp"
#include "csc_array.hpp"
#include "csc_runtime.hpp"

namespace CSC {
template <class ITEM>
class CalcThread {
private:
	class Detail ;

	class Holder {
	public:
		using INTRUSIVE_TYPE = typename CalcThread::Detail ;

	private:
		friend CalcThread ;
		friend IntrusiveRef<Holder> ;
		Monostate<std::atomic<LENGTH>> mCounter ;
		Monostate<std::mutex> mThreadMutex ;
		Monostate<std::condition_variable> mThreadCondition ;
		AutoRef<BOOL> mThreadFlag ;
		LENGTH mThreadCounter ;
		Array<Function<DEF<ITEM ()> NONE::*>> mThreadProc ;
		Array<AutoRef<std::thread>> mThreadPool ;
		AutoRef<QList<ITEM ,SFIXED>> mItemQueue ;
		AutoRef<Exception> mException ;
	} ;

private:
	class Detail ;
	friend IntrusiveRef<Holder> ;
	IntrusiveRef<Holder> mThis ;

public:
	CalcThread () {
		mThis = IntrusiveRef<Holder>::make () ;
	}

	LENGTH size () popping {
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2y.mThreadMutex) ;
		if (!r2y.mItemQueue.exist ())
			return 0 ;
		return r2y.mItemQueue->size () ;
	}

	LENGTH length () popping {
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2y.mThreadMutex) ;
		if (!r2y.mItemQueue.exist ())
			return 0 ;
		return r2y.mItemQueue->length () ;
	}

	void reserve (LENGTH post_len) {
		_DEBUG_ASSERT_ (post_len >= 0) ;
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2y.mThreadMutex) ;
		if (r2y.mItemQueue.exist () && r2y.mItemQueue->length () + post_len <= r2y.mItemQueue->size ())
			return ;
		auto rax = AutoRef<QList<ITEM ,SFIXED>>::make (post_len) ;
		rax->appand (std::move (r2y.mItemQueue.self)) ;
		r2y.mItemQueue = std::move (rax) ;
	}

	ITEM poll () popping {
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2y.mThreadMutex) ;
		while (r2y.mThreadFlag.exist () && r2y.mItemQueue->empty ())
			r2y.mThreadCondition.self.wait (sgd) ;
		_DYNAMIC_ASSERT_ (r2y.mThreadFlag.exist ()) ;
		ITEM ret = std::move (r2y.mItemQueue.self[r2y.mItemQueue->head ()]) ;
		r2y.mItemQueue->take () ;
		return std::move (ret) ;
	}

	ITEM poll (const std::chrono::milliseconds &interval ,const Function<BOOL ()> &predicate) popping {
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2y.mThreadMutex) ;
		while (TRUE) {
			if (!r2y.mThreadFlag.exist ())
				break ;
			if (!r2y.mItemQueue->empty ())
				break ;
			const auto r3x = predicate () ;
			_DYNAMIC_ASSERT_ (r3x) ;
			r2y.mThreadCondition.self.wait_for (sgd ,interval) ;
		}
		_DYNAMIC_ASSERT_ (r2y.mThreadFlag.exist ()) ;
		ITEM ret = std::move (r2y.mItemQueue.self[r2y.mItemQueue->head ()]) ;
		r2y.mItemQueue->take () ;
		return std::move (ret) ;
	}

	void start (const Array<INDEX> &pid ,Array<Function<DEF<ITEM ()> NONE::*>> &&proc) {
		_DEBUG_ASSERT_ (pid.length () > 0) ;
		for (auto &&i : pid) {
			_DEBUG_ASSERT_ (i >= 0 && i < proc.size ()) ;
			(void) i ;
		}
		for (auto &&i : proc) {
			_DEBUG_ASSERT_ (i.exist ()) ;
			(void) i ;
		}
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2y.mThreadMutex) ;
		_DEBUG_ASSERT_ (!r2y.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (r2y.mThreadCounter == 0) ;
		r2y.mThreadFlag = AutoRef<BOOL>::make (TRUE) ;
		r2y.mThreadCounter = 0 ;
		r2y.mThreadProc = std::move (proc) ;
		if (!r2y.mItemQueue.exist ())
			r2y.mItemQueue = AutoRef<QList<ITEM ,SFIXED>>::make (pid.length ()) ;
		r2y.mItemQueue->clear () ;
		r2y.mException = AutoRef<Exception> () ;
		r2y.mThreadPool = Array<AutoRef<std::thread>> (pid.size ()) ;
		for (INDEX i = 0 ,ie = r2y.mThreadPool.length () ; i < ie ; i++) {
			const auto r3x = PACK<PTR<Holder> ,INDEX> {&r2y ,pid[i]} ;
			//@warn: move object having captured context
			r2y.mThreadPool[i] = AutoRef<std::thread>::make ([r3x] () noexcept {
				_CALL_TRY_ ([&] () {
					Detail::static_execute ((*r3x.P1) ,r3x.P2) ;
				} ,[&] () {
					_STATIC_WARNING_ ("noop") ;
				}) ;
			}) ;
		}
	}

	void join (const std::chrono::milliseconds &interval ,const Function<BOOL ()> &predicate) {
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2y.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (r2y.mItemQueue->size () > 0) ;
		while (TRUE) {
			_DYNAMIC_ASSERT_ (r2y.mThreadFlag.exist ()) ;
			if (r2y.mException.exist ())
				break ;
			if (r2y.mItemQueue->full ())
				break ;
			const auto r3x = predicate () ;
			if (!r3x)
				break ;
			r2y.mThreadCondition.self.wait_for (sgd ,interval) ;
		}
		const auto r4x = std::move (r2y.mException) ;
		if (!r4x.exist ())
			return ;
		r4x->raise () ;
	}

	void stop () {
		const auto r1x = mThis.watch () ;
		Detail::friend_destroy (r1x) ;
	}

private:
	class Detail :private Wrapped<void> {
	public:
		inline static void static_execute (Holder &_self ,INDEX pid) {
			class Finally :private Wrapped<Holder> {
			public:
				inline void lock () {
					ScopedGuard<std::mutex> ANONYMOUS (Finally::mSelf.mThreadMutex) ;
					Finally::mSelf.mThreadCounter++ ;
				}

				inline void unlock () {
					ScopedGuard<std::mutex> ANONYMOUS (Finally::mSelf.mThreadMutex) ;
					Finally::mSelf.mThreadCounter-- ;
				}
			} ;
			ScopedGuard<Finally> ANONYMOUS (_CAST_<Finally> (_self)) ;
			auto rax = Optional<ITEM>::nullopt () ;
			while (TRUE) {
				_CATCH_ ([&] () {
					rax.template recreate<ITEM> (_self.mThreadProc[pid] ()) ;
				} ,[&] (const Exception &e) noexcept {
					_CALL_TRY_ ([&] () {
						static_rethrow (_self ,e) ;
					} ,[&] () {
						_STATIC_WARNING_ ("noop") ;
					}) ;
				}) ;
				static_push (_self ,std::move (rax)) ;
				rax = Optional<ITEM>::nullopt () ;
			}
		}

		inline static void static_push (Holder &_self ,Optional<ITEM> &&item) {
			ScopedGuard<std::mutex> sgd (_self.mThreadMutex) ;
			_DEBUG_ASSERT_ (_self.mThreadFlag.exist ()) ;
			_DYNAMIC_ASSERT_ (_self.mThreadFlag.self) ;
			if (!item.exist ())
				return ;
			_DYNAMIC_ASSERT_ (_self.mItemQueue->size () > 0) ;
			for (FOR_ONCE_DO) {
				if (!_self.mItemQueue->full ())
					discard ;
				_self.mThreadCondition.self.wait_for (sgd ,std::chrono::milliseconds (0)) ;
				if (!_self.mItemQueue->full ())
					discard ;
				_self.mItemQueue->take () ;
			}
			_self.mItemQueue->add (std::move (item.self)) ;
			_self.mThreadCondition.self.notify_all () ;
		}

		inline static void static_rethrow (Holder &_self ,const Exception &e) {
			ScopedGuard<std::mutex> ANONYMOUS (_self.mThreadMutex) ;
			_DEBUG_ASSERT_ (_self.mThreadFlag.exist ()) ;
			if (_self.mException.exist ())
				return ;
			_self.mException = AutoRef<Exception>::make (e) ;
		}

		inline static void friend_create (Holder &_self) {
			ScopedGuard<std::mutex> ANONYMOUS (_self.mThreadMutex) ;
			_self.mCounter.self = 0 ;
			_self.mThreadFlag = AutoRef<BOOL> () ;
			_self.mThreadCounter = 0 ;
			_self.mThreadPool = Array<AutoRef<std::thread>> () ;
			_self.mThreadProc = Array<Function<DEF<ITEM ()> NONE::*>> () ;
		}

		inline static void friend_destroy (Holder &_self) {
			std::unique_lock<std::mutex> sgd (_self.mThreadMutex) ;
			if (!_self.mThreadFlag.exist ())
				return ;
			_self.mThreadFlag.self = FALSE ;
			_self.mThreadCondition.self.notify_all () ;
			while (_self.mThreadFlag.exist () && _self.mThreadCounter > 0)
				_self.mThreadCondition.self.wait_for (sgd ,std::chrono::milliseconds (0)) ;
			_DYNAMIC_ASSERT_ (_self.mThreadFlag.exist ()) ;
			for (auto &&i : _self.mThreadPool) {
				if (!i.exist ())
					continue ;
				i->join () ;
			}
			_self.mThreadFlag = AutoRef<BOOL> () ;
			_self.mThreadCounter = 0 ;
			_self.mThreadPool = Array<AutoRef<std::thread>> () ;
			_self.mThreadProc = Array<Function<DEF<ITEM ()> NONE::*>> () ;
		}

		inline static LENGTH friend_attach (Holder &_self) popping {
			return ++_self.mCounter.self ;
		}

		inline static LENGTH friend_detach (Holder &_self) popping {
			return --_self.mCounter.self ;
		}

		inline static void friend_latch (Holder &_self) {
			GlobalRuntime::thread_sleep () ;
		}
	} ;
} ;

template <class ITEM>
class WorkThread {
private:
	class Counter :private Wrapped<LENGTH> {
	public:
		inline void lock () {
			Counter::mSelf++ ;
		}

		inline void unlock () {
			Counter::mSelf-- ;
		}
	} ;

	class Detail ;

	class Holder {
	public:
		using INTRUSIVE_TYPE = typename WorkThread::Detail ;

	private:
		friend WorkThread ;
		friend IntrusiveRef<Holder> ;
		Monostate<std::atomic<LENGTH>> mCounter ;
		Monostate<std::mutex> mThreadMutex ;
		Monostate<std::condition_variable> mThreadCondition ;
		LENGTH mThreadCounter ;
		LENGTH mThreadWaitCounter ;
		AutoRef<BOOL> mThreadFlag ;
		Function<DEF<void (const ITEM &)> NONE::*> mThreadProc ;
		Array<AutoRef<std::thread>> mThreadPool ;
		AutoRef<QList<ITEM ,SFIXED>> mItemQueue ;
		AutoRef<Exception> mException ;
	} ;

private:
	class Detail ;
	friend IntrusiveRef<Holder> ;
	IntrusiveRef<Holder> mThis ;

public:
	WorkThread () {
		mThis = IntrusiveRef<Holder>::make () ;
	}

	LENGTH size () popping {
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2y.mThreadMutex) ;
		if (!r2y.mItemQueue.exist ())
			return 0 ;
		return r2y.mItemQueue->size () ;
	}

	LENGTH length () popping {
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2y.mThreadMutex) ;
		if (!r2y.mItemQueue.exist ())
			return 0 ;
		return r2y.mItemQueue->length () ;
	}

	void reserve (LENGTH post_len) {
		_DEBUG_ASSERT_ (post_len >= 0) ;
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2y.mThreadMutex) ;
		if (r2y.mItemQueue.exist () && r2y.mItemQueue->length () + post_len <= r2y.mItemQueue->size ())
			return ;
		auto rax = AutoRef<QList<ITEM ,SFIXED>>::make (post_len) ;
		rax->appand (std::move (r2y.mItemQueue.self)) ;
		r2y.mItemQueue = std::move (rax) ;
	}

	void post (const ITEM &item) {
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2y.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (r2y.mItemQueue->size () > 0) ;
		while (r2y.mThreadFlag.exist () && r2y.mItemQueue->full ())
			r2y.mThreadCondition.self.wait (sgd) ;
		_DYNAMIC_ASSERT_ (r2y.mThreadFlag.exist ()) ;
		r2y.mItemQueue->add (std::move (item)) ;
		r2y.mThreadCondition.self.notify_all () ;
	}

	void post (ITEM &&item) {
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2y.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (r2y.mItemQueue->size () > 0) ;
		while (r2y.mThreadFlag.exist () && r2y.mItemQueue->full ())
			r2y.mThreadCondition.self.wait (sgd) ;
		_DYNAMIC_ASSERT_ (r2y.mThreadFlag.exist ()) ;
		r2y.mItemQueue->add (std::move (item)) ;
		r2y.mThreadCondition.self.notify_all () ;
	}

	void post (const ITEM &item ,const std::chrono::milliseconds &interval ,const Function<BOOL ()> &predicate) {
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2y.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (r2y.mItemQueue->size () > 0) ;
		while (TRUE) {
			if (!r2y.mThreadFlag.exist ())
				break ;
			if (!r2y.mItemQueue->full ())
				break ;
			const auto r3x = predicate () ;
			_DYNAMIC_ASSERT_ (r3x) ;
			r2y.mThreadCondition.self.wait_for (sgd ,interval) ;
		}
		_DYNAMIC_ASSERT_ (r2y.mThreadFlag.exist ()) ;
		r2y.mItemQueue->add (std::move (item)) ;
		r2y.mThreadCondition.self.notify_all () ;
	}

	void post (ITEM &&item ,const std::chrono::milliseconds &interval ,const Function<BOOL ()> &predicate) {
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2y.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (r2y.mItemQueue->size () > 0) ;
		while (TRUE) {
			if (!r2y.mThreadFlag.exist ())
				break ;
			if (!r2y.mItemQueue->full ())
				break ;
			const auto r3x = predicate () ;
			_DYNAMIC_ASSERT_ (r3x) ;
			r2y.mThreadCondition.self.wait_for (sgd ,interval) ;
		}
		_DYNAMIC_ASSERT_ (r2y.mThreadFlag.exist ()) ;
		r2y.mItemQueue->add (std::move (item)) ;
		r2y.mThreadCondition.self.notify_all () ;
	}

	void start (LENGTH count ,Function<DEF<void (const ITEM &)> NONE::*> &&proc) {
		_DEBUG_ASSERT_ (count > 0) ;
		_DEBUG_ASSERT_ (proc.exist ()) ;
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2y.mThreadMutex) ;
		_DEBUG_ASSERT_ (!r2y.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (r2y.mThreadCounter == 0) ;
		r2y.mThreadFlag = AutoRef<BOOL>::make (TRUE) ;
		r2y.mThreadCounter = 0 ;
		r2y.mThreadWaitCounter = 0 ;
		r2y.mThreadProc = std::move (proc) ;
		if (!r2y.mItemQueue.exist ())
			r2y.mItemQueue = AutoRef<QList<ITEM ,SFIXED>>::make (count) ;
		r2y.mItemQueue->clear () ;
		r2y.mException = AutoRef<Exception> () ;
		r2y.mThreadPool = Array<AutoRef<std::thread>> (count) ;
		for (INDEX i = 0 ,ie = r2y.mThreadPool.length () ; i < ie ; i++) {
			const auto r3x = &r2y ;
			//@warn: move object having captured context
			r2y.mThreadPool[i] = AutoRef<std::thread>::make ([r3x] () noexcept {
				_CALL_TRY_ ([&] () {
					Detail::static_execute ((*r3x)) ;
				} ,[&] () {
					_STATIC_WARNING_ ("noop") ;
				}) ;
			}) ;
		}
	}

	void join (const std::chrono::milliseconds &interval ,const Function<BOOL ()> &predicate) {
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2y.mThreadMutex) ;
		while (TRUE) {
			_DYNAMIC_ASSERT_ (r2y.mThreadFlag.exist ()) ;
			if (r2y.mException.exist ())
				break ;
			if (r2y.mThreadWaitCounter >= r2y.mThreadPool.length () && r2y.mItemQueue->empty ())
				break ;
			const auto r3x = predicate () ;
			if (!r3x)
				break ;
			r2y.mThreadCondition.self.wait_for (sgd ,interval) ;
		}
		const auto r4x = std::move (r2y.mException) ;
		if (!r4x.exist ())
			return ;
		r4x->raise () ;
	}

	void stop () {
		const auto r1x = mThis.watch () ;
		Detail::friend_destroy (r1x) ;
	}

private:
	class Detail :private Wrapped<void> {
	public:
		inline static void static_execute (Holder &_self) {
			class Finally :private Wrapped<Holder> {
			public:
				inline void lock () {
					ScopedGuard<std::mutex> ANONYMOUS (Finally::mSelf.mThreadMutex) ;
					Finally::mSelf.mThreadCounter++ ;
				}

				inline void unlock () {
					ScopedGuard<std::mutex> ANONYMOUS (Finally::mSelf.mThreadMutex) ;
					Finally::mSelf.mThreadCounter-- ;
				}
			} ;
			ScopedGuard<Finally> ANONYMOUS (_CAST_<Finally> (_self)) ;
			auto rax = Optional<ITEM>::nullopt () ;
			while (TRUE) {
				static_poll (_self ,rax) ;
				_CATCH_ ([&] () {
					_self.mThreadProc (rax.self) ;
				} ,[&] (const Exception &e) noexcept {
					_CALL_TRY_ ([&] () {
						static_rethrow (_self ,e) ;
					} ,[&] () {
						_STATIC_WARNING_ ("noop") ;
					}) ;
				}) ;
				rax = Optional<ITEM>::nullopt () ;
			}
		}

		inline static void static_poll (Holder &_self ,Optional<ITEM> &item) {
			std::unique_lock<std::mutex> sgd (_self.mThreadMutex) ;
			_DEBUG_ASSERT_ (_self.mThreadFlag.exist ()) ;
			ScopedGuard<Counter> ANONYMOUS (_CAST_<Counter> (_self.mThreadWaitCounter)) ;
			while (_self.mThreadFlag.self && _self.mItemQueue->empty ())
				_self.mThreadCondition.self.wait (sgd) ;
			_DYNAMIC_ASSERT_ (_self.mThreadFlag.self) ;
			item = std::move (_self.mItemQueue.self[_self.mItemQueue->head ()]) ;
			_self.mItemQueue->take () ;
		}

		inline static void static_rethrow (Holder &_self ,const Exception &e) {
			ScopedGuard<std::mutex> ANONYMOUS (_self.mThreadMutex) ;
			_DEBUG_ASSERT_ (_self.mThreadFlag.exist ()) ;
			if (_self.mException.exist ())
				return ;
			_self.mException = AutoRef<Exception>::make (e) ;
		}

		inline static void friend_create (Holder &_self) {
			ScopedGuard<std::mutex> ANONYMOUS (_self.mThreadMutex) ;
			_self.mCounter.self = 0 ;
			_self.mThreadFlag = AutoRef<BOOL> () ;
			_self.mThreadCounter = 0 ;
			_self.mThreadWaitCounter = 0 ;
			_self.mThreadPool = Array<AutoRef<std::thread>> () ;
			_self.mThreadProc = Function<DEF<void (const ITEM &)> NONE::*> () ;
		}

		inline static void friend_destroy (Holder &_self) {
			std::unique_lock<std::mutex> sgd (_self.mThreadMutex) ;
			if (!_self.mThreadFlag.exist ())
				return ;
			_self.mThreadFlag.self = FALSE ;
			_self.mThreadCondition.self.notify_all () ;
			while (_self.mThreadFlag.exist () && _self.mThreadCounter > 0)
				_self.mThreadCondition.self.wait_for (sgd ,std::chrono::milliseconds (0)) ;
			_DYNAMIC_ASSERT_ (_self.mThreadFlag.exist ()) ;
			for (auto &&i : _self.mThreadPool) {
				if (!i.exist ())
					continue ;
				i->join () ;
			}
			_self.mThreadFlag = AutoRef<BOOL> () ;
			_self.mThreadCounter = 0 ;
			_self.mThreadWaitCounter = 0 ;
			_self.mThreadPool = Array<AutoRef<std::thread>> () ;
			_self.mThreadProc = Function<DEF<void (const ITEM &)> NONE::*> () ;
		}

		inline static LENGTH friend_attach (Holder &_self) popping {
			return ++_self.mCounter.self ;
		}

		inline static LENGTH friend_detach (Holder &_self) popping {
			return --_self.mCounter.self ;
		}

		inline static void friend_latch (Holder &_self) {
			GlobalRuntime::thread_sleep () ;
		}
	} ;
} ;

template <class ITEM>
class Promise {
public:
	class Future ;

private:
	class Detail ;

	class Holder {
	public:
		using INTRUSIVE_TYPE = typename Promise::Detail ;

	private:
		friend Promise ;
		friend Future ;
		friend IntrusiveRef<Holder> ;
		Monostate<std::atomic<LENGTH>> mCounter ;
		Monostate<std::mutex> mThreadMutex ;
		Monostate<std::condition_variable> mThreadCondition ;
		LENGTH mThreadCounter ;
		AutoRef<BOOL> mThreadFlag ;
		Function<DEF<ITEM ()> NONE::*> mThreadProc ;
		Function<DEF<void (ITEM &)> NONE::*> mCallbackProc ;
		AutoRef<std::thread> mThreadPool ;
		AutoRef<ITEM> mItem ;
		AutoRef<Exception> mException ;
	} ;

private:
	class Detail ;
	friend IntrusiveRef<Holder> ;
	IntrusiveRef<Holder> mThis ;

public:
	Promise () {
		mThis = IntrusiveRef<Holder>::make () ;
	}

	Future future () popping ;

	void push (const ITEM &item) {
		const auto r1x = mThis.watch () ;
		Detail::static_push (r1x) ;
	}

	void push (ITEM &&item) {
		const auto r1x = mThis.watch () ;
		Detail::static_push (r1x) ;
	}

	void raise (const Exception &e) {
		const auto r1x = mThis.watch () ;
		Detail::static_rethrow (r1x) ;
	}

	void start () {
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2y.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (!r2y.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (r2y.mThreadCounter == 0) ;
		r2y.mThreadFlag = AutoRef<BOOL>::make (TRUE) ;
		r2y.mThreadCounter = 0 ;
		r2y.mThreadProc = Function<DEF<ITEM ()> NONE::*> () ;
		r2y.mCallbackProc = Function<DEF<void (ITEM &)> NONE::*> () ;
		r2y.mItem = AutoRef<ITEM> () ;
		r2y.mException = AutoRef<Exception> () ;
		r2y.mThreadPool = AutoRef<std::thread> () ;
	}

	void start (Function<DEF<ITEM ()> NONE::*> &&proc) {
		_DEBUG_ASSERT_ (proc.exist ()) ;
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2y.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (!r2y.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (r2y.mThreadCounter == 0) ;
		r2y.mThreadFlag = AutoRef<BOOL>::make (TRUE) ;
		r2y.mThreadCounter = 0 ;
		r2y.mThreadProc = std::move (proc) ;
		r2y.mCallbackProc = Function<DEF<void (ITEM &)> NONE::*> () ;
		r2y.mItem = AutoRef<ITEM> () ;
		r2y.mException = AutoRef<Exception> () ;
		const auto r3x = &r2y ;
		//@warn: move object having captured context
		r2y.mThreadPool = AutoRef<std::thread>::make ([r3x] () noexcept {
			_CALL_TRY_ ([&] () {
				Detail::static_execute ((*r3x)) ;
			} ,[&] () {
				_STATIC_WARNING_ ("noop") ;
			}) ;
		}) ;
	}

	void signal () {
		const auto r1x = mThis.watch () ;
		Detail::static_signal (r1x) ;
	}

	void stop () {
		const auto r1x = mThis.watch () ;
		Detail::friend_destroy (r1x) ;
	}

private:
	explicit Promise (IntrusiveRef<Holder> &_this) popping : mThis (_this.copy ()) {}

public:
	static Future async (Function<DEF<ITEM ()> NONE::*> &&proc) ;

private:
	class Detail :private Wrapped<void> {
	public:
		inline static void static_execute (Holder &_self) {
			class Finally :private Wrapped<Holder> {
			public:
				inline void lock () {
					ScopedGuard<std::mutex> ANONYMOUS (Finally::mSelf.mThreadMutex) ;
					Finally::mSelf.mThreadCounter++ ;
				}

				inline void unlock () {
					ScopedGuard<std::mutex> ANONYMOUS (Finally::mSelf.mThreadMutex) ;
					Finally::mSelf.mThreadCounter-- ;
				}
			} ;
			ScopedGuard<Finally> ANONYMOUS (_CAST_<Finally> (_self)) ;
			_CATCH_ ([&] () {
				static_push (_self ,_self.mThreadProc ()) ;
			} ,[&] (const Exception &e) noexcept {
				_CALL_TRY_ ([&] () {
					static_rethrow (_self ,e) ;
				} ,[&] () {
					_STATIC_WARNING_ ("noop") ;
				}) ;
			}) ;
			static_signal (_self) ;
		}

		inline static void static_push (Holder &_self ,const ITEM &item) {
			ScopedGuard<std::mutex> ANONYMOUS (_self.mThreadMutex) ;
			_DEBUG_ASSERT_ (_self.mThreadFlag.exist ()) ;
			_DYNAMIC_ASSERT_ (_self.mThreadFlag.self) ;
			_DEBUG_ASSERT_ (!_self.mException.exist ()) ;
			_self.mItem = AutoRef<ITEM>::make (std::move (item)) ;
		}

		inline static void static_push (Holder &_self ,ITEM &&item) {
			ScopedGuard<std::mutex> ANONYMOUS (_self.mThreadMutex) ;
			_DEBUG_ASSERT_ (_self.mThreadFlag.exist ()) ;
			_DYNAMIC_ASSERT_ (_self.mThreadFlag.self) ;
			_DEBUG_ASSERT_ (!_self.mException.exist ()) ;
			_self.mItem = AutoRef<ITEM>::make (std::move (item)) ;
		}

		inline static void static_rethrow (Holder &_self ,const Exception &e) {
			ScopedGuard<std::mutex> ANONYMOUS (_self.mThreadMutex) ;
			_DEBUG_ASSERT_ (_self.mThreadFlag.exist ()) ;
			_DEBUG_ASSERT_ (!_self.mException.exist ()) ;
			_self.mItem = AutoRef<ITEM> () ;
			_self.mException = AutoRef<Exception>::make (e) ;
		}

		inline static void static_signal (Holder &_self) {
			ScopedGuard<std::mutex> ANONYMOUS (_self.mThreadMutex) ;
			_DEBUG_ASSERT_ (_self.mThreadFlag.exist ()) ;
			_self.mThreadFlag.self = FALSE ;
			_self.mThreadCondition.self.notify_all () ;
			for (FOR_ONCE_DO) {
				if (!_self.mItem.exist ())
					discard ;
				if (!_self.mCallbackProc.exist ())
					discard ;
				_self.mCallbackProc (_self.mItem) ;
			}
			_self.mCallbackProc = Function<DEF<void (ITEM &)> NONE::*> () ;
		}

		inline static void friend_create (Holder &_self) {
			ScopedGuard<std::mutex> ANONYMOUS (_self.mThreadMutex) ;
			_self.mCounter.self = 0 ;
			_self.mThreadFlag = AutoRef<BOOL> () ;
			_self.mThreadCounter = 0 ;
			_self.mThreadPool = AutoRef<std::thread> () ;
			_self.mThreadProc = Function<DEF<ITEM ()> NONE::*> () ;
			_self.mCallbackProc = Function<DEF<void (ITEM &)> NONE::*> () ;
		}

		inline static void friend_destroy (Holder &_self) {
			std::unique_lock<std::mutex> sgd (_self.mThreadMutex) ;
			if (!_self.mThreadFlag.exist ())
				return ;
			_self.mThreadFlag.self = FALSE ;
			_self.mThreadCondition.self.notify_all () ;
			while (_self.mThreadFlag.exist () && _self.mThreadCounter > 0)
				_self.mThreadCondition.self.wait_for (sgd ,std::chrono::milliseconds (0)) ;
			_DYNAMIC_ASSERT_ (_self.mThreadFlag.exist ()) ;
			if (_self.mThreadPool.exist ())
				_self.mThreadPool->join () ;
			_self.mThreadFlag = AutoRef<BOOL> () ;
			_self.mThreadCounter = 0 ;
			_self.mThreadPool = AutoRef<std::thread> () ;
			_self.mThreadProc = Function<DEF<ITEM ()> NONE::*> () ;
			_self.mCallbackProc = Function<DEF<void (ITEM &)> NONE::*> () ;
		}

		inline static LENGTH friend_attach (Holder &_self) popping {
			return ++_self.mCounter.self ;
		}

		inline static LENGTH friend_detach (Holder &_self) popping {
			return --_self.mCounter.self ;
		}

		inline static void friend_latch (Holder &_self) {
			GlobalRuntime::thread_sleep () ;
		}
	} ;
} ;

template <class ITEM>
class Promise<ITEM>::Future {
private:
	using Holder = typename Promise<ITEM>::Holder ;
	using Detail = typename Promise<ITEM>::Detail ;

private:
	friend Promise<ITEM> ;
	IntrusiveRef<Holder> mThis ;

public:
	Future () = delete ;

	BOOL ready () popping {
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2y.mThreadMutex) ;
		if (!r2y.mThreadFlag.exist ())
			return TRUE ;
		if (r2y.mThreadFlag.self)
			return FALSE ;
		return TRUE ;
	}

	ITEM poll () popping {
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2y.mThreadMutex) ;
		while (r2y.mThreadFlag.exist () && r2y.mThreadFlag.self)
			r2y.mThreadCondition.self.wait (sgd) ;
		for (FOR_ONCE_DO) {
			if (!r2y.mException.exist ())
				discard ;
			r2y.mException->raise () ;
		}
		_DYNAMIC_ASSERT_ (r2y.mItem.exist ()) ;
		ITEM ret = std::move (r2y.mItem.self) ;
		r2y.mItem = AutoRef<ITEM> () ;
		return std::move (ret) ;
	}

	ITEM poll (const std::chrono::milliseconds &interval ,const Function<BOOL ()> &predicate) popping {
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2y.mThreadMutex) ;
		while (TRUE) {
			if (!r2y.mThreadFlag.exist ())
				break ;
			if (!r2y.mThreadFlag.self)
				break ;
			const auto r3x = predicate () ;
			_DYNAMIC_ASSERT_ (r3x) ;
			r2y.mThreadCondition.self.wait_for (sgd ,interval) ;
		}
		for (FOR_ONCE_DO) {
			if (!r2y.mException.exist ())
				discard ;
			r2y.mException->raise () ;
		}
		_DYNAMIC_ASSERT_ (r2y.mItem.exist ()) ;
		ITEM ret = std::move (r2y.mItem.self) ;
		r2y.mItem = AutoRef<ITEM> () ;
		return std::move (ret) ;
	}

	ITEM value (const ITEM &def) popping {
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2y.mThreadMutex) ;
		if (!r2y.mThreadFlag.exist ())
			return def ;
		if (r2y.mThreadFlag.self)
			return def ;
		if (!r2y.mItem.exist ())
			return def ;
		return r2y.mItem.self ;
	}

	void then (Function<DEF<void (ITEM &)> NONE::*> &&proc) {
		_DEBUG_ASSERT_ (proc.exist ()) ;
		const auto r1x = mThis.watch () ;
		auto &r2y = _XVALUE_<Holder> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2y.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (r2y.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (!r2y.mCallbackProc.exist ()) ;
		r2y.mCallbackProc = std::move (proc) ;
		if (r2y.mThreadFlag.self)
			return ;
		if (!r2y.mItem.exist ())
			return ;
		r2y.mCallbackProc (r2y.mItem.self) ;
		r2y.mCallbackProc = Function<DEF<void (ITEM &)> NONE::*> () ;
	}

	void stop () {
		const auto r1x = mThis.watch () ;
		Detail::friend_destroy (r1x) ;
	}

private:
	explicit Future (IntrusiveRef<Holder> &_this) popping : mThis (_this.copy ()) {}
} ;

template <class ITEM>
inline typename Promise<ITEM>::Future Promise<ITEM>::future () popping {
	return Future (mThis) ;
}

template <class ITEM>
inline typename Promise<ITEM>::Future Promise<ITEM>::async (Function<DEF<ITEM ()> NONE::*> &&proc) {
	auto rax = Promise<ITEM> () ;
	rax.start (std::move (proc)) ;
	return rax.future () ;
}
} ;