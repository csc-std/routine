#pragma once

#ifndef __CSC_THREAD__
#define __CSC_THREAD__
#endif

#include "csc.hpp"
#include "csc_basic.hpp"
#include "csc_extend.hpp"
#include "csc_array.hpp"
#include "csc_runtime.hpp"

namespace CSC {
template <class ITEM>
class CalcThread {
private:
	class Pack {
	public:
		using INTRUSIVE_TYPE = CalcThread ;

	private:
		friend CalcThread ;
		friend IntrusiveRef<Pack> ;
		std::atomic<LENGTH> mCounter ;
		Monostate<std::mutex> mThreadMutex ;
		Monostate<std::condition_variable> mThreadCondition ;
		AutoRef<BOOL> mThreadFlag ;
		LENGTH mThreadCounter ;
		Set<INDEX ,Function<DEF<ITEM ()> NONE::*>> mThreadProcSet ;
		Array<AutoRef<std::thread>> mThreadPool ;
		AutoRef<QList<ITEM ,SFIXED>> mItemQueue ;
		AutoRef<Exception> mException ;
	} ;

private:
	struct Detail ;
	friend IntrusiveRef<Pack> ;
	IntrusiveRef<Pack> mThis ;

public:
	CalcThread () {
		mThis = IntrusiveRef<Pack>::make () ;
	}

	LENGTH size () popping {
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2x.mThreadMutex) ;
		if (!r2x.mItemQueue.exist ())
			return 0 ;
		return r2x.mItemQueue->size () ;
	}

	LENGTH length () popping {
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2x.mThreadMutex) ;
		if (!r2x.mItemQueue.exist ())
			return 0 ;
		return r2x.mItemQueue->length () ;
	}

	void reserve (LENGTH post_len) {
		_DEBUG_ASSERT_ (post_len >= 0) ;
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2x.mThreadMutex) ;
		if (r2x.mItemQueue.exist ())
			if (r2x.mItemQueue->length () + post_len <= r2x.mItemQueue->size ())
				return ;
		auto tmp = AutoRef<QList<ITEM ,SFIXED>>::make (post_len) ;
		tmp->appand (std::move (r2x.mItemQueue.self)) ;
		r2x.mItemQueue = std::move (tmp) ;
	}

	ITEM poll () popping {
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2x.mThreadMutex) ;
		while (TRUE) {
			if (!r2x.mThreadFlag.exist ())
				break ;
			if (!r2x.mItemQueue->empty ())
				break ;
			r2x.mThreadCondition.self.wait (sgd) ;
		}
		_DYNAMIC_ASSERT_ (r2x.mThreadFlag.exist ()) ;
		ITEM ret = std::move (r2x.mItemQueue.self[r2x.mItemQueue->head ()]) ;
		r2x.mItemQueue->take () ;
		return std::move (ret) ;
	}

	template <class _ARG1 ,class _ARG2>
	ITEM poll (const std::chrono::duration<_ARG1 ,_ARG2> &interval ,const Function<BOOL ()> &predicate) popping {
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2x.mThreadMutex) ;
		while (TRUE) {
			if (!r2x.mThreadFlag.exist ())
				break ;
			if (!r2x.mItemQueue->empty ())
				break ;
			const auto r3x = predicate () ;
			_DYNAMIC_ASSERT_ (r3x) ;
			r2x.mThreadCondition.self.wait_for (sgd ,interval) ;
		}
		_DYNAMIC_ASSERT_ (r2x.mThreadFlag.exist ()) ;
		ITEM ret = std::move (r2x.mItemQueue.self[r2x.mItemQueue->head ()]) ;
		r2x.mItemQueue->take () ;
		return std::move (ret) ;
	}

	void start (Array<Function<DEF<ITEM ()> NONE::*>> &&proc) {
		using LocalProc = typename Detail::LocalProc ;
		_DEBUG_ASSERT_ (proc.length () > 0) ;
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2x.mThreadMutex) ;
		_DEBUG_ASSERT_ (!r2x.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (r2x.mThreadCounter == 0) ;
		r2x.mThreadFlag = AutoRef<BOOL>::make (TRUE) ;
		r2x.mThreadCounter = 0 ;
		r2x.mThreadProcSet = Set<INDEX ,Function<DEF<ITEM ()> NONE::*>> (proc.length ()) ;
		for (auto &&i : _RANGE_ (0 ,proc.length ())) {
			_DEBUG_ASSERT_ (proc[i].exist ()) ;
			r2x.mThreadProcSet.add (i ,std::move (proc[i])) ;
		}
		if (!r2x.mItemQueue.exist ())
			r2x.mItemQueue = AutoRef<QList<ITEM ,SFIXED>>::make (proc.length ()) ;
		r2x.mItemQueue->clear () ;
		r2x.mException = AutoRef<Exception> () ;
		r2x.mThreadPool = Array<AutoRef<std::thread>> (proc.size ()) ;
		for (auto &&i : _RANGE_ (0 ,r2x.mThreadPool.length ())) {
			//@warn: forward object having captured context
			const auto r3x = LocalProc (&r2x ,i) ;
			r2x.mThreadPool[i] = AutoRef<std::thread>::make (r3x) ;
		}
	}

	template <class _ARG1 ,class _ARG2>
	void join (const std::chrono::duration<_ARG1 ,_ARG2> &interval ,const Function<BOOL ()> &predicate) {
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2x.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (r2x.mItemQueue->size () > 0) ;
		while (TRUE) {
			_DYNAMIC_ASSERT_ (r2x.mThreadFlag.exist ()) ;
			if (r2x.mException.exist ())
				break ;
			if (r2x.mItemQueue->full ())
				break ;
			const auto r3x = predicate () ;
			if (!r3x)
				break ;
			r2x.mThreadCondition.self.wait_for (sgd ,interval) ;
		}
		const auto r4x = std::move (r2x.mException) ;
		if (!r4x.exist ())
			return ;
		r4x->raise () ;
	}

	void stop () {
		const auto r1x = mThis.watch () ;
		friend_destroy (r1x) ;
	}

private:
	inline static void static_execute (Pack &self_ ,INDEX tid) {
		using ThreadCounter = typename Detail::ThreadCounter ;
		ScopedGuard<ThreadCounter> ANONYMOUS (_CAST_<ThreadCounter> (self_)) ;
		INDEX ix = self_.mThreadProcSet.find (tid) ;
		_DEBUG_ASSERT_ (ix != VAR_NONE) ;
		auto rax = Optional<ITEM>::nullopt () ;
		while (TRUE) {
			_CATCH_ ([&] () {
				//@warn: 'mThreadProc' is not protected by 'mThreadMutex'
				rax = self_.mThreadProcSet[ix].item () ;
			} ,[&] (const Exception &e) noexcept {
				_CALL_TRY_ ([&] () {
					static_rethrow (self_ ,e) ;
				} ,[&] () {
					_STATIC_WARNING_ ("noop") ;
				}) ;
			}) ;
			if (rax.exist ())
				static_push (self_ ,std::move (rax.self)) ;
			rax = Optional<ITEM>::nullopt () ;
		}
	}

	inline static void static_push (Pack &self_ ,ITEM &&item) {
		ScopedGuard<std::mutex> sgd (self_.mThreadMutex) ;
		_DEBUG_ASSERT_ (self_.mThreadFlag.exist ()) ;
		_DYNAMIC_ASSERT_ (self_.mThreadFlag.self) ;
		_DYNAMIC_ASSERT_ (self_.mItemQueue->size () > 0) ;
		if switch_case (TRUE) {
			if (!self_.mItemQueue->full ())
				discard ;
			self_.mThreadCondition.self.wait_for (sgd ,std::chrono::milliseconds (0)) ;
			if (!self_.mItemQueue->full ())
				discard ;
			self_.mItemQueue->take () ;
		}
		self_.mItemQueue->add (std::move (item)) ;
		self_.mThreadCondition.self.notify_all () ;
	}

	inline static void static_rethrow (Pack &self_ ,const Exception &e) {
		ScopedGuard<std::mutex> ANONYMOUS (self_.mThreadMutex) ;
		_DEBUG_ASSERT_ (self_.mThreadFlag.exist ()) ;
		if (self_.mException.exist ())
			return ;
		self_.mException = AutoRef<Exception>::make (e) ;
	}

	inline static void friend_create (Pack &self_) {
		ScopedGuard<std::mutex> ANONYMOUS (self_.mThreadMutex) ;
		self_.mCounter = 0 ;
		self_.mThreadFlag = AutoRef<BOOL> () ;
		self_.mThreadCounter = 0 ;
		self_.mThreadPool = Array<AutoRef<std::thread>> () ;
		self_.mThreadProcSet = Set<INDEX ,Function<DEF<ITEM ()> NONE::*>> () ;
	}

	inline static void friend_destroy (Pack &self_) {
		std::unique_lock<std::mutex> sgd (self_.mThreadMutex) ;
		if (!self_.mThreadFlag.exist ())
			return ;
		self_.mThreadFlag.self = FALSE ;
		self_.mThreadCondition.self.notify_all () ;
		while (TRUE) {
			if (!self_.mThreadFlag.exist ())
				break ;
			if (self_.mThreadCounter == 0)
				break ;
			self_.mThreadCondition.self.wait_for (sgd ,std::chrono::milliseconds (0)) ;
		}
		_DYNAMIC_ASSERT_ (self_.mThreadFlag.exist ()) ;
		for (auto &&i : self_.mThreadPool) {
			if (!i.exist ())
				continue ;
			i->join () ;
		}
		self_.mThreadFlag = AutoRef<BOOL> () ;
		self_.mThreadCounter = 0 ;
		self_.mThreadPool = Array<AutoRef<std::thread>> () ;
		self_.mThreadProcSet = Set<INDEX ,Function<DEF<ITEM ()> NONE::*>> () ;
	}

	inline static LENGTH friend_attach (Pack &self_) popping {
		return ++self_.mCounter ;
	}

	inline static LENGTH friend_detach (Pack &self_) popping {
		return --self_.mCounter ;
	}

	inline static void friend_latch (Pack &self_) {
		GlobalRuntime::thread_sleep () ;
	}

private:
	struct Detail {
		class LocalProc {
		private:
			PTR<Pack> mHolder ;
			INDEX mIndex ;

		public:
			inline LocalProc () = delete ;

			inline explicit LocalProc (PTR<Pack> holder ,INDEX index) :mHolder (holder) ,mIndex (index) {}

			inline void operator() () {
				_CALL_TRY_ ([&] () {
					static_execute ((*mHolder) ,mIndex) ;
				} ,[&] () {
					_STATIC_WARNING_ ("noop") ;
				}) ;
			}
		} ;

		class ThreadCounter :private Wrapped<Pack> {
		public:
			inline void lock () {
				ScopedGuard<std::mutex> ANONYMOUS (ThreadCounter::mSelf.mThreadMutex) ;
				ThreadCounter::mSelf.mThreadCounter++ ;
			}

			inline void unlock () {
				ScopedGuard<std::mutex> ANONYMOUS (ThreadCounter::mSelf.mThreadMutex) ;
				ThreadCounter::mSelf.mThreadCounter-- ;
			}
		} ;
	} ;
} ;

template <class ITEM>
class WorkThread {
private:
	class Pack {
	public:
		using INTRUSIVE_TYPE = WorkThread ;

	private:
		friend WorkThread ;
		friend IntrusiveRef<Pack> ;
		std::atomic<LENGTH> mCounter ;
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
	struct Detail ;
	friend IntrusiveRef<Pack> ;
	IntrusiveRef<Pack> mThis ;

public:
	WorkThread () {
		mThis = IntrusiveRef<Pack>::make () ;
	}

	LENGTH size () popping {
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2x.mThreadMutex) ;
		if (!r2x.mItemQueue.exist ())
			return 0 ;
		return r2x.mItemQueue->size () ;
	}

	LENGTH length () popping {
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2x.mThreadMutex) ;
		if (!r2x.mItemQueue.exist ())
			return 0 ;
		return r2x.mItemQueue->length () ;
	}

	void reserve (LENGTH post_len) {
		_DEBUG_ASSERT_ (post_len >= 0) ;
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2x.mThreadMutex) ;
		if (r2x.mItemQueue.exist ())
			if (r2x.mItemQueue->length () + post_len <= r2x.mItemQueue->size ())
				return ;
		auto tmp = AutoRef<QList<ITEM ,SFIXED>>::make (post_len) ;
		tmp->appand (std::move (r2x.mItemQueue.self)) ;
		r2x.mItemQueue = std::move (tmp) ;
	}

	void post (const ITEM &item) {
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2x.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (r2x.mItemQueue->size () > 0) ;
		while (TRUE) {
			if (!r2x.mThreadFlag.exist ())
				break ;
			if (!r2x.mItemQueue->full ())
				break ;
			r2x.mThreadCondition.self.wait (sgd) ;
		}
		_DYNAMIC_ASSERT_ (r2x.mThreadFlag.exist ()) ;
		r2x.mItemQueue->add (std::move (item)) ;
		r2x.mThreadCondition.self.notify_all () ;
	}

	void post (ITEM &&item) {
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2x.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (r2x.mItemQueue->size () > 0) ;
		while (TRUE) {
			if (!r2x.mThreadFlag.exist ())
				break ;
			if (!r2x.mItemQueue->full ())
				break ;
			r2x.mThreadCondition.self.wait (sgd) ;
		}
		_DYNAMIC_ASSERT_ (r2x.mThreadFlag.exist ()) ;
		r2x.mItemQueue->add (std::move (item)) ;
		r2x.mThreadCondition.self.notify_all () ;
	}

	template <class _ARG1 ,class _ARG2>
	void post (const ITEM &item ,const std::chrono::duration<_ARG1 ,_ARG2> &interval ,const Function<BOOL ()> &predicate) {
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2x.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (r2x.mItemQueue->size () > 0) ;
		while (TRUE) {
			if (!r2x.mThreadFlag.exist ())
				break ;
			if (!r2x.mItemQueue->full ())
				break ;
			const auto r3x = predicate () ;
			_DYNAMIC_ASSERT_ (r3x) ;
			r2x.mThreadCondition.self.wait_for (sgd ,interval) ;
		}
		_DYNAMIC_ASSERT_ (r2x.mThreadFlag.exist ()) ;
		r2x.mItemQueue->add (std::move (item)) ;
		r2x.mThreadCondition.self.notify_all () ;
	}

	template <class _ARG1 ,class _ARG2>
	void post (ITEM &&item ,const std::chrono::duration<_ARG1 ,_ARG2> &interval ,const Function<BOOL ()> &predicate) {
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2x.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (r2x.mItemQueue->size () > 0) ;
		while (TRUE) {
			if (!r2x.mThreadFlag.exist ())
				break ;
			if (!r2x.mItemQueue->full ())
				break ;
			const auto r3x = predicate () ;
			_DYNAMIC_ASSERT_ (r3x) ;
			r2x.mThreadCondition.self.wait_for (sgd ,interval) ;
		}
		_DYNAMIC_ASSERT_ (r2x.mThreadFlag.exist ()) ;
		r2x.mItemQueue->add (std::move (item)) ;
		r2x.mThreadCondition.self.notify_all () ;
	}

	void start (LENGTH count ,Function<DEF<void (const ITEM &)> NONE::*> &&proc) {
		using LocalProc = typename Detail::LocalProc ;
		_DEBUG_ASSERT_ (count > 0) ;
		_DEBUG_ASSERT_ (proc.exist ()) ;
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2x.mThreadMutex) ;
		_DEBUG_ASSERT_ (!r2x.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (r2x.mThreadCounter == 0) ;
		r2x.mThreadFlag = AutoRef<BOOL>::make (TRUE) ;
		r2x.mThreadCounter = 0 ;
		r2x.mThreadWaitCounter = 0 ;
		r2x.mThreadProc = std::move (proc) ;
		if (!r2x.mItemQueue.exist ())
			r2x.mItemQueue = AutoRef<QList<ITEM ,SFIXED>>::make (count) ;
		r2x.mItemQueue->clear () ;
		r2x.mException = AutoRef<Exception> () ;
		r2x.mThreadPool = Array<AutoRef<std::thread>> (count) ;
		for (auto &&i : _RANGE_ (0 ,r2x.mThreadPool.length ())) {
			//@warn: forward object having captured context
			const auto r3x = LocalProc (&r2x) ;
			r2x.mThreadPool[i] = AutoRef<std::thread>::make (r3x) ;
		}
	}

	template <class _ARG1 ,class _ARG2>
	void join (const std::chrono::duration<_ARG1 ,_ARG2> &interval ,const Function<BOOL ()> &predicate) {
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2x.mThreadMutex) ;
		while (TRUE) {
			_DYNAMIC_ASSERT_ (r2x.mThreadFlag.exist ()) ;
			if (r2x.mException.exist ())
				break ;
			if (r2x.mThreadWaitCounter >= r2x.mThreadPool.length ())
				if (r2x.mItemQueue->empty ())
					break ;
			const auto r3x = predicate () ;
			if (!r3x)
				break ;
			r2x.mThreadCondition.self.wait_for (sgd ,interval) ;
		}
		const auto r4x = std::move (r2x.mException) ;
		if (!r4x.exist ())
			return ;
		r4x->raise () ;
	}

	void stop () {
		const auto r1x = mThis.watch () ;
		friend_destroy (r1x) ;
	}

private:
	inline static void static_execute (Pack &self_) {
		using ThreadCounter = typename Detail::ThreadCounter ;
		ScopedGuard<ThreadCounter> ANONYMOUS (_CAST_<ThreadCounter> (self_)) ;
		auto rax = Optional<ITEM>::nullopt () ;
		while (TRUE) {
			static_poll (self_ ,rax) ;
			_CATCH_ ([&] () {
				//@warn: 'mThreadProc' is not protected by 'mThreadMutex'
				self_.mThreadProc (rax.self) ;
			} ,[&] (const Exception &e) noexcept {
				_CALL_TRY_ ([&] () {
					static_rethrow (self_ ,e) ;
				} ,[&] () {
					_STATIC_WARNING_ ("noop") ;
				}) ;
			}) ;
			rax = Optional<ITEM>::nullopt () ;
		}
	}

	inline static void static_poll (Pack &self_ ,Optional<ITEM> &item) {
		using Counter = typename Detail::Counter ;
		std::unique_lock<std::mutex> sgd (self_.mThreadMutex) ;
		_DEBUG_ASSERT_ (self_.mThreadFlag.exist ()) ;
		ScopedGuard<Counter> ANONYMOUS (_CAST_<Counter> (self_.mThreadWaitCounter)) ;
		while (TRUE) {
			if (!self_.mThreadFlag.self)
				break ;
			if (!self_.mItemQueue->empty ())
				break ;
			self_.mThreadCondition.self.wait (sgd) ;
		}
		_DYNAMIC_ASSERT_ (self_.mThreadFlag.self) ;
		item = std::move (self_.mItemQueue.self[self_.mItemQueue->head ()]) ;
		self_.mItemQueue->take () ;
	}

	inline static void static_rethrow (Pack &self_ ,const Exception &e) {
		ScopedGuard<std::mutex> ANONYMOUS (self_.mThreadMutex) ;
		_DEBUG_ASSERT_ (self_.mThreadFlag.exist ()) ;
		if (self_.mException.exist ())
			return ;
		self_.mException = AutoRef<Exception>::make (e) ;
	}

	inline static void friend_create (Pack &self_) {
		ScopedGuard<std::mutex> ANONYMOUS (self_.mThreadMutex) ;
		self_.mCounter = 0 ;
		self_.mThreadFlag = AutoRef<BOOL> () ;
		self_.mThreadCounter = 0 ;
		self_.mThreadWaitCounter = 0 ;
		self_.mThreadPool = Array<AutoRef<std::thread>> () ;
		self_.mThreadProc = Function<DEF<void (const ITEM &)> NONE::*> () ;
	}

	inline static void friend_destroy (Pack &self_) {
		std::unique_lock<std::mutex> sgd (self_.mThreadMutex) ;
		if (!self_.mThreadFlag.exist ())
			return ;
		self_.mThreadFlag.self = FALSE ;
		self_.mThreadCondition.self.notify_all () ;
		while (TRUE) {
			if (!self_.mThreadFlag.exist ())
				break ;
			if (self_.mThreadCounter == 0)
				break ;
			self_.mThreadCondition.self.wait_for (sgd ,std::chrono::milliseconds (0)) ;
		}
		_DYNAMIC_ASSERT_ (self_.mThreadFlag.exist ()) ;
		for (auto &&i : self_.mThreadPool) {
			if (!i.exist ())
				continue ;
			i->join () ;
		}
		self_.mThreadFlag = AutoRef<BOOL> () ;
		self_.mThreadCounter = 0 ;
		self_.mThreadWaitCounter = 0 ;
		self_.mThreadPool = Array<AutoRef<std::thread>> () ;
		self_.mThreadProc = Function<DEF<void (const ITEM &)> NONE::*> () ;
	}

	inline static LENGTH friend_attach (Pack &self_) popping {
		return ++self_.mCounter ;
	}

	inline static LENGTH friend_detach (Pack &self_) popping {
		return --self_.mCounter ;
	}

	inline static void friend_latch (Pack &self_) {
		GlobalRuntime::thread_sleep () ;
	}

private:
	struct Detail {
		class LocalProc {
		private:
			PTR<Pack> mHolder ;

		public:
			inline LocalProc () = delete ;

			inline explicit LocalProc (PTR<Pack> holder) :mHolder (holder) {}

			inline void operator() () {
				_CALL_TRY_ ([&] () {
					static_execute ((*mHolder)) ;
				} ,[&] () {
					_STATIC_WARNING_ ("noop") ;
				}) ;
			}
		} ;

		class ThreadCounter :private Wrapped<Pack> {
		public:
			inline void lock () {
				ScopedGuard<std::mutex> ANONYMOUS (ThreadCounter::mSelf.mThreadMutex) ;
				ThreadCounter::mSelf.mThreadCounter++ ;
			}

			inline void unlock () {
				ScopedGuard<std::mutex> ANONYMOUS (ThreadCounter::mSelf.mThreadMutex) ;
				ThreadCounter::mSelf.mThreadCounter-- ;
			}
		} ;

		class Counter :private Wrapped<LENGTH> {
		public:
			inline void lock () {
				Counter::mSelf++ ;
			}

			inline void unlock () {
				Counter::mSelf-- ;
			}
		} ;
	} ;
} ;

template <class ITEM>
class Promise {
public:
	class Future ;

private:
	class Pack {
	public:
		using INTRUSIVE_TYPE = Promise ;

	private:
		friend Promise ;
		friend Future ;
		friend IntrusiveRef<Pack> ;
		std::atomic<LENGTH> mCounter ;
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
	struct Detail ;
	friend IntrusiveRef<Pack> ;
	IntrusiveRef<Pack> mThis ;

public:
	Promise () {
		mThis = IntrusiveRef<Pack>::make () ;
	}

	Future future () popping ;

	void push (const ITEM &item) {
		const auto r1x = mThis.watch () ;
		static_push (r1x) ;
	}

	void push (ITEM &&item) {
		const auto r1x = mThis.watch () ;
		static_push (r1x) ;
	}

	void rethrow (const Exception &e) {
		const auto r1x = mThis.watch () ;
		static_rethrow (r1x) ;
	}

	void start () {
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2x.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (!r2x.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (r2x.mThreadCounter == 0) ;
		r2x.mThreadFlag = AutoRef<BOOL>::make (TRUE) ;
		r2x.mThreadCounter = 0 ;
		r2x.mThreadProc = Function<DEF<ITEM ()> NONE::*> () ;
		r2x.mCallbackProc = Function<DEF<void (ITEM &)> NONE::*> () ;
		r2x.mItem = AutoRef<ITEM> () ;
		r2x.mException = AutoRef<Exception> () ;
		r2x.mThreadPool = AutoRef<std::thread> () ;
	}

	void start (Function<DEF<ITEM ()> NONE::*> &&proc) {
		using LocalProc = typename Detail::LocalProc ;
		_DEBUG_ASSERT_ (proc.exist ()) ;
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2x.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (!r2x.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (r2x.mThreadCounter == 0) ;
		r2x.mThreadFlag = AutoRef<BOOL>::make (TRUE) ;
		r2x.mThreadCounter = 0 ;
		r2x.mThreadProc = std::move (proc) ;
		r2x.mCallbackProc = Function<DEF<void (ITEM &)> NONE::*> () ;
		r2x.mItem = AutoRef<ITEM> () ;
		r2x.mException = AutoRef<Exception> () ;
		//@warn: forward object having captured context
		const auto r3x = LocalProc (&r2x) ;
		r2x.mThreadPool = AutoRef<std::thread>::make (r3x) ;
	}

	void signal () {
		const auto r1x = mThis.watch () ;
		static_signal (r1x) ;
	}

	void stop () {
		const auto r1x = mThis.watch () ;
		friend_destroy (r1x) ;
	}

private:
	explicit Promise (IntrusiveRef<Pack> &this_) popping : mThis (this_.copy ()) {}

public:
	static Future async (Function<DEF<ITEM ()> NONE::*> &&proc) ;

private:
	inline static void static_execute (Pack &self_) {
		using ThreadCounter = typename Detail::ThreadCounter ;
		ScopedGuard<ThreadCounter> ANONYMOUS (_CAST_<ThreadCounter> (self_)) ;
		auto rax = Optional<ITEM>::nullopt () ;
		_CATCH_ ([&] () {
			//@warn: 'mThreadProc' is not protected by 'mThreadMutex'
			rax = self_.mThreadProc () ;
		} ,[&] (const Exception &e) noexcept {
			_CALL_TRY_ ([&] () {
				static_rethrow (self_ ,e) ;
			} ,[&] () {
				_STATIC_WARNING_ ("noop") ;
			}) ;
		}) ;
		if (rax.exist ())
			static_push (self_ ,std::move (rax.self)) ;
		static_signal (self_) ;
	}

	inline static void static_push (Pack &self_ ,const ITEM &item) {
		ScopedGuard<std::mutex> ANONYMOUS (self_.mThreadMutex) ;
		_DEBUG_ASSERT_ (self_.mThreadFlag.exist ()) ;
		_DYNAMIC_ASSERT_ (self_.mThreadFlag.self) ;
		_DEBUG_ASSERT_ (!self_.mException.exist ()) ;
		self_.mItem = AutoRef<ITEM>::make (std::move (item)) ;
	}

	inline static void static_push (Pack &self_ ,ITEM &&item) {
		ScopedGuard<std::mutex> ANONYMOUS (self_.mThreadMutex) ;
		_DEBUG_ASSERT_ (self_.mThreadFlag.exist ()) ;
		_DYNAMIC_ASSERT_ (self_.mThreadFlag.self) ;
		_DEBUG_ASSERT_ (!self_.mException.exist ()) ;
		self_.mItem = AutoRef<ITEM>::make (std::move (item)) ;
	}

	inline static void static_rethrow (Pack &self_ ,const Exception &e) {
		ScopedGuard<std::mutex> ANONYMOUS (self_.mThreadMutex) ;
		_DEBUG_ASSERT_ (self_.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (!self_.mException.exist ()) ;
		self_.mItem = AutoRef<ITEM> () ;
		self_.mException = AutoRef<Exception>::make (e) ;
	}

	inline static void static_signal (Pack &self_) {
		ScopedGuard<std::mutex> ANONYMOUS (self_.mThreadMutex) ;
		_DEBUG_ASSERT_ (self_.mThreadFlag.exist ()) ;
		self_.mThreadFlag.self = FALSE ;
		self_.mThreadCondition.self.notify_all () ;
		if switch_case (TRUE) {
			if (!self_.mItem.exist ())
				discard ;
			if (!self_.mCallbackProc.exist ())
				discard ;
			self_.mCallbackProc (self_.mItem) ;
		}
		self_.mCallbackProc = Function<DEF<void (ITEM &)> NONE::*> () ;
	}

	inline static void friend_create (Pack &self_) {
		ScopedGuard<std::mutex> ANONYMOUS (self_.mThreadMutex) ;
		self_.mCounter = 0 ;
		self_.mThreadFlag = AutoRef<BOOL> () ;
		self_.mThreadCounter = 0 ;
		self_.mThreadPool = AutoRef<std::thread> () ;
		self_.mThreadProc = Function<DEF<ITEM ()> NONE::*> () ;
		self_.mCallbackProc = Function<DEF<void (ITEM &)> NONE::*> () ;
	}

	inline static void friend_destroy (Pack &self_) {
		std::unique_lock<std::mutex> sgd (self_.mThreadMutex) ;
		if (!self_.mThreadFlag.exist ())
			return ;
		self_.mThreadFlag.self = FALSE ;
		self_.mThreadCondition.self.notify_all () ;
		while (TRUE) {
			if (!self_.mThreadFlag.exist ())
				break ;
			if (self_.mThreadCounter == 0)
				break ;
			self_.mThreadCondition.self.wait_for (sgd ,std::chrono::milliseconds (0)) ;
		}
		_DYNAMIC_ASSERT_ (self_.mThreadFlag.exist ()) ;
		if (self_.mThreadPool.exist ())
			self_.mThreadPool->join () ;
		self_.mThreadFlag = AutoRef<BOOL> () ;
		self_.mThreadCounter = 0 ;
		self_.mThreadPool = AutoRef<std::thread> () ;
		self_.mThreadProc = Function<DEF<ITEM ()> NONE::*> () ;
		self_.mCallbackProc = Function<DEF<void (ITEM &)> NONE::*> () ;
	}

	inline static LENGTH friend_attach (Pack &self_) popping {
		return ++self_.mCounter ;
	}

	inline static LENGTH friend_detach (Pack &self_) popping {
		return --self_.mCounter ;
	}

	inline static void friend_latch (Pack &self_) {
		GlobalRuntime::thread_sleep () ;
	}

private:
	struct Detail {
		class LocalProc {
		private:
			PTR<Pack> mHolder ;

		public:
			inline LocalProc () = delete ;

			inline explicit LocalProc (PTR<Pack> holder) :mHolder (holder) {}

			inline void operator() () {
				_CALL_TRY_ ([&] () {
					static_execute ((*mHolder)) ;
				} ,[&] () {
					_STATIC_WARNING_ ("noop") ;
				}) ;
			}
		} ;

		class ThreadCounter :private Wrapped<Pack> {
		public:
			inline void lock () {
				ScopedGuard<std::mutex> ANONYMOUS (ThreadCounter::mSelf.mThreadMutex) ;
				ThreadCounter::mSelf.mThreadCounter++ ;
			}

			inline void unlock () {
				ScopedGuard<std::mutex> ANONYMOUS (ThreadCounter::mSelf.mThreadMutex) ;
				ThreadCounter::mSelf.mThreadCounter-- ;
			}
		} ;
	} ;
} ;

template <class ITEM>
class Promise<ITEM>::Future {
private:
	using Pack = typename Promise<ITEM>::Pack ;

private:
	friend Promise<ITEM> ;
	IntrusiveRef<Pack> mThis ;

public:
	Future () = delete ;

	BOOL ready () popping {
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2x.mThreadMutex) ;
		if (!r2x.mThreadFlag.exist ())
			return TRUE ;
		if (r2x.mThreadFlag.self)
			return FALSE ;
		return TRUE ;
	}

	ITEM poll () popping {
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2x.mThreadMutex) ;
		while (TRUE) {
			if (!r2x.mThreadFlag.exist ())
				break ;
			if (!r2x.mThreadFlag.self)
				break ;
			r2x.mThreadCondition.self.wait (sgd) ;
		}
		if (r2x.mException.exist ())
			r2x.mException->raise () ;
		_DYNAMIC_ASSERT_ (r2x.mItem.exist ()) ;
		ITEM ret = std::move (r2x.mItem.self) ;
		r2x.mItem = AutoRef<ITEM> () ;
		return std::move (ret) ;
	}

	template <class _ARG1 ,class _ARG2>
	ITEM poll (const std::chrono::duration<_ARG1 ,_ARG2> &interval ,const Function<BOOL ()> &predicate) popping {
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		std::unique_lock<std::mutex> sgd (r2x.mThreadMutex) ;
		while (TRUE) {
			if (!r2x.mThreadFlag.exist ())
				break ;
			if (!r2x.mThreadFlag.self)
				break ;
			const auto r3x = predicate () ;
			_DYNAMIC_ASSERT_ (r3x) ;
			r2x.mThreadCondition.self.wait_for (sgd ,interval) ;
		}
		if (r2x.mException.exist ())
			r2x.mException->raise () ;
		_DYNAMIC_ASSERT_ (r2x.mItem.exist ()) ;
		ITEM ret = std::move (r2x.mItem.self) ;
		r2x.mItem = AutoRef<ITEM> () ;
		return std::move (ret) ;
	}

	ITEM value (const ITEM &def) popping {
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2x.mThreadMutex) ;
		if (!r2x.mThreadFlag.exist ())
			return def ;
		if (r2x.mThreadFlag.self)
			return def ;
		if (!r2x.mItem.exist ())
			return def ;
		return r2x.mItem.self ;
	}

	void then (Function<DEF<void (ITEM &)> NONE::*> &&proc) {
		_DEBUG_ASSERT_ (proc.exist ()) ;
		const auto r1x = mThis.watch () ;
		auto &r2x = _XVALUE_<Pack> (r1x) ;
		ScopedGuard<std::mutex> ANONYMOUS (r2x.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (r2x.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (!r2x.mCallbackProc.exist ()) ;
		r2x.mCallbackProc = std::move (proc) ;
		if (r2x.mThreadFlag.self)
			return ;
		if (!r2x.mItem.exist ())
			return ;
		r2x.mCallbackProc (r2x.mItem.self) ;
		r2x.mCallbackProc = Function<DEF<void (ITEM &)> NONE::*> () ;
	}

	void stop () {
		const auto r1x = mThis.watch () ;
		friend_destroy (r1x) ;
	}

private:
	explicit Future (IntrusiveRef<Pack> &this_) popping : mThis (this_.copy ()) {}
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