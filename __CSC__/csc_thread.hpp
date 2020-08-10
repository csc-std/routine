#pragma once

#ifndef __CSC_THREAD__
#define __CSC_THREAD__
#endif

#include "csc.hpp"
#include "csc_core.hpp"
#include "csc_basic.hpp"
#include "csc_extend.hpp"
#include "csc_array.hpp"
#include "csc_math.hpp"
#include "csc_stream.hpp"
#include "csc_string.hpp"
#include "csc_runtime.hpp"

namespace CSC {
template <class ITEM>
class CalcThread {
private:
	struct SELF_PACK {
		Mutex mThreadMutex ;
		ConditionLock mThreadConditionLock ;
		AutoRef<BOOL> mThreadFlag ;
		LENGTH mThreadCounter ;
		Array<Function<MEMPTR<ITEM ()>>> mThreadProc ;
		Array<AutoRef<Thread>> mThreadPool ;
		AutoRef<List<ITEM ,SFIXED>> mItemQueue ;
		AutoRef<Exception> mException ;
	} ;

	struct Private {
		class ThreadBinder ;

		class ThreadCounter ;
	} ;

private:
	StrongRef<UniqueRef<SharedRef<SELF_PACK>>> mThis ;

public:
	implicit CalcThread () {
		auto tmp = UniqueRef<SharedRef<SELF_PACK>> ([&] (SharedRef<SELF_PACK> &me) {
			me = SharedRef<SELF_PACK>::make () ;
			static_create (me.self) ;
		} ,[] (SharedRef<SELF_PACK> &me) {
			static_destroy (me.self) ;
		}) ;
		mThis = StrongRef<UniqueRef<SharedRef<SELF_PACK>>>::make (_MOVE_ (tmp)) ;
	}

	LENGTH size () const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		if (!r1x.mItemQueue.exist ())
			return 0 ;
		return r1x.mItemQueue->size () ;
	}

	LENGTH length () const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		if (!r1x.mItemQueue.exist ())
			return 0 ;
		return r1x.mItemQueue->length () ;
	}

	void reserve (const LENGTH &post_len) const {
		_DEBUG_ASSERT_ (post_len >= 0) ;
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		if (r1x.mItemQueue.exist ())
			if (r1x.mItemQueue->length () + post_len <= r1x.mItemQueue->size ())
				return ;
		auto rbx = AutoRef<List<ITEM ,SFIXED>>::make (post_len) ;
		rbx->appand (_MOVE_ (r1x.mItemQueue.self)) ;
		r1x.mItemQueue = _MOVE_ (rbx) ;
	}

	ITEM poll () const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		while (TRUE) {
			if (!r1x.mThreadFlag.exist ())
				break ;
			if (!r1x.mItemQueue->empty ())
				break ;
			rbx.wait () ;
		}
		_DYNAMIC_ASSERT_ (r1x.mThreadFlag.exist ()) ;
		ITEM ret = _MOVE_ (r1x.mItemQueue.self[r1x.mItemQueue->head ()]) ;
		r1x.mItemQueue->take () ;
		return _MOVE_ (ret) ;
	}

	ITEM poll (const Duration &interval ,const Function<BOOL ()> &predicate) const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		while (TRUE) {
			if (!r1x.mThreadFlag.exist ())
				break ;
			if (!r1x.mItemQueue->empty ())
				break ;
			const auto r2x = predicate () ;
			_DYNAMIC_ASSERT_ (r2x) ;
			rbx.wait (interval) ;
		}
		_DYNAMIC_ASSERT_ (r1x.mThreadFlag.exist ()) ;
		ITEM ret = _MOVE_ (r1x.mItemQueue.self[r1x.mItemQueue->head ()]) ;
		r1x.mItemQueue->take () ;
		return _MOVE_ (ret) ;
	}

	void start (Array<Function<MEMPTR<ITEM ()>>> &&proc) const {
		struct Dependent ;
		using ThreadBinder = typename DEPENDENT_TYPE<Private ,Dependent>::ThreadBinder ;
		_DEBUG_ASSERT_ (proc.length () > 0) ;
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		_DEBUG_ASSERT_ (!r1x.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (r1x.mThreadCounter == 0) ;
		r1x.mThreadFlag = AutoRef<BOOL>::make (TRUE) ;
		r1x.mThreadCounter = 0 ;
		r1x.mThreadProc = Array<Function<MEMPTR<ITEM ()>>> (proc.length ()) ;
		for (auto &&i : _RANGE_ (0 ,proc.length ())) {
			_DEBUG_ASSERT_ (proc[i].exist ()) ;
			r1x.mThreadProc[i] = _MOVE_ (proc[i]) ;
		}
		if (!r1x.mItemQueue.exist ())
			r1x.mItemQueue = AutoRef<List<ITEM ,SFIXED>>::make (proc.length ()) ;
		r1x.mItemQueue->clear () ;
		r1x.mException = AutoRef<Exception> () ;
		r1x.mThreadPool = Array<AutoRef<Thread>> (proc.size ()) ;
		for (auto &&i : _RANGE_ (0 ,r1x.mThreadPool.length ())) {
			//@warn: forward object having captured context
			const auto r2x = StrongRef<ThreadBinder>::make (PhanRef<SELF_PACK>::make (r1x) ,i) ;
			r1x.mThreadPool[i] = AutoRef<Thread>::make (r2x) ;
		}
	}

	void join (const Duration &interval ,const Function<BOOL ()> &predicate) const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		_DYNAMIC_ASSERT_ (r1x.mItemQueue->size () > 0) ;
		while (TRUE) {
			_DYNAMIC_ASSERT_ (r1x.mThreadFlag.exist ()) ;
			if (r1x.mException.exist ())
				break ;
			if (r1x.mItemQueue->full ())
				break ;
			const auto r2x = predicate () ;
			if (!r2x)
				break ;
			rbx.wait (interval) ;
		}
		const auto r3x = _MOVE_ (r1x.mException) ;
		if (!r3x.exist ())
			return ;
		r3x->raise () ;
	}

	void stop () const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		static_destroy (r1x) ;
	}

private:
	imports void static_create (SELF_PACK &self_) {
		ScopedGuard<Mutex> ANONYMOUS (self_.mThreadMutex) ;
		self_.mThreadFlag = AutoRef<BOOL> () ;
		self_.mThreadCounter = 0 ;
		self_.mThreadPool = Array<AutoRef<Thread>> () ;
		self_.mThreadProc = Array<Function<MEMPTR<ITEM ()>>> () ;
	}

	imports void static_destroy (SELF_PACK &self_) {
		auto rbx = self_.mThreadConditionLock.watch (PhanRef<Mutex>::make (self_.mThreadMutex)) ;
		if (!self_.mThreadFlag.exist ())
			return ;
		self_.mThreadFlag.self = FALSE ;
		rbx.notify () ;
		while (TRUE) {
			if (!self_.mThreadFlag.exist ())
				break ;
			if (self_.mThreadCounter == 0)
				break ;
			rbx.yield () ;
		}
		_DYNAMIC_ASSERT_ (self_.mThreadFlag.exist ()) ;
		for (auto &&i : self_.mThreadPool) {
			if (!i.exist ())
				continue ;
			i->join () ;
		}
		self_.mThreadFlag = AutoRef<BOOL> () ;
		self_.mThreadCounter = 0 ;
		self_.mThreadPool = Array<AutoRef<Thread>> () ;
		self_.mThreadProc = Array<Function<MEMPTR<ITEM ()>>> () ;
	}

	imports void static_execute (SELF_PACK &self_ ,const INDEX &tid) {
		struct Dependent ;
		using ThreadCounter = typename DEPENDENT_TYPE<Private ,Dependent>::ThreadCounter ;
		ScopedGuard<ThreadCounter> ANONYMOUS (_CAST_ (ARGV<ThreadCounter>::null ,self_)) ;
		auto rbx = Optional<ITEM>::nullopt () ;
		while (TRUE) {
			_CATCH_ ([&] () {
				//@warn: 'mThreadProc' is not protected by 'mThreadMutex'
				rbx = self_.mThreadProc[tid] () ;
			} ,[&] (const Exception &e) {
				_CALL_TRY_ ([&] () {
					static_rethrow (self_ ,e) ;
				} ,[&] () {
					_STATIC_WARNING_ ("noop") ;
				}) ;
			}) ;
			if (rbx.exist ())
				static_push (self_ ,_MOVE_ (rbx.self)) ;
			rbx = Optional<ITEM>::nullopt () ;
		}
	}

	imports void static_push (SELF_PACK &self_ ,const REMOVE_CONST_TYPE<ITEM> &item) {
		auto rbx = self_.mThreadConditionLock.watch (PhanRef<Mutex>::make (self_.mThreadMutex)) ;
		_DEBUG_ASSERT_ (self_.mThreadFlag.exist ()) ;
		_DYNAMIC_ASSERT_ (self_.mThreadFlag.self) ;
		_DYNAMIC_ASSERT_ (self_.mItemQueue->size () > 0) ;
		if switch_once (TRUE) {
			if (!self_.mItemQueue->full ())
				discard ;
			rbx.yield () ;
			if (!self_.mItemQueue->full ())
				discard ;
			self_.mItemQueue->take () ;
		}
		self_.mItemQueue->add (_MOVE_ (item)) ;
		rbx.notify () ;
	}

	imports void static_push (SELF_PACK &self_ ,REMOVE_CONST_TYPE<ITEM> &&item) {
		auto rbx = self_.mThreadConditionLock.watch (PhanRef<Mutex>::make (self_.mThreadMutex)) ;
		_DEBUG_ASSERT_ (self_.mThreadFlag.exist ()) ;
		_DYNAMIC_ASSERT_ (self_.mThreadFlag.self) ;
		_DYNAMIC_ASSERT_ (self_.mItemQueue->size () > 0) ;
		if switch_once (TRUE) {
			if (!self_.mItemQueue->full ())
				discard ;
			rbx.yield () ;
			if (!self_.mItemQueue->full ())
				discard ;
			self_.mItemQueue->take () ;
		}
		self_.mItemQueue->add (_MOVE_ (item)) ;
		rbx.notify () ;
	}

	imports void static_rethrow (SELF_PACK &self_ ,const Exception &e) {
		ScopedGuard<Mutex> ANONYMOUS (self_.mThreadMutex) ;
		_DEBUG_ASSERT_ (self_.mThreadFlag.exist ()) ;
		if (self_.mException.exist ())
			return ;
		self_.mException = AutoRef<Exception>::make (e) ;
	}
} ;

template <class ITEM>
class CalcThread<ITEM>::Private::ThreadBinder
	:public Thread::Binder {
private:
	PhanRef<SELF_PACK> mThis ;
	INDEX mIndex ;

public:
	implicit ThreadBinder () = delete ;

	explicit ThreadBinder (PhanRef<SELF_PACK> &&this_ ,const INDEX &index) {
		mThis = _MOVE_ (this_) ;
		mIndex = index ;
	}

	void execute () override {
		_CALL_TRY_ ([&] () {
			static_execute (mThis ,mIndex) ;
		} ,[&] () {
			_STATIC_WARNING_ ("noop") ;
		}) ;
	}
} ;

template <class ITEM>
class CalcThread<ITEM>::Private::ThreadCounter
	:private Wrapped<SELF_PACK> {
public:
	void lock () {
		ScopedGuard<Mutex> ANONYMOUS (ThreadCounter::mSelf.mThreadMutex) ;
		ThreadCounter::mSelf.mThreadCounter++ ;
	}

	void unlock () {
		ScopedGuard<Mutex> ANONYMOUS (ThreadCounter::mSelf.mThreadMutex) ;
		ThreadCounter::mSelf.mThreadCounter-- ;
	}
} ;

template <class ITEM>
class WorkThread {
private:
	struct SELF_PACK {
		Mutex mThreadMutex ;
		ConditionLock mThreadConditionLock ;
		LENGTH mThreadCounter ;
		LENGTH mThreadWaitCounter ;
		AutoRef<BOOL> mThreadFlag ;
		Function<MEMPTR<void (const ITEM &)>> mThreadProc ;
		Array<AutoRef<Thread>> mThreadPool ;
		AutoRef<List<ITEM ,SFIXED>> mItemQueue ;
		AutoRef<Exception> mException ;
	} ;

	struct Private {
		class ThreadBinder ;

		class ThreadCounter ;

		class Counter ;
	} ;

private:
	StrongRef<UniqueRef<SharedRef<SELF_PACK>>> mThis ;

public:
	implicit WorkThread () {
		auto tmp = UniqueRef<SharedRef<SELF_PACK>> ([&] (SharedRef<SELF_PACK> &me) {
			me = SharedRef<SELF_PACK>::make () ;
			static_create (me.self) ;
		} ,[] (SharedRef<SELF_PACK> &me) {
			static_destroy (me.self) ;
		}) ;
		mThis = StrongRef<UniqueRef<SharedRef<SELF_PACK>>>::make (_MOVE_ (tmp)) ;
	}

	LENGTH size () const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		if (!r1x.mItemQueue.exist ())
			return 0 ;
		return r1x.mItemQueue->size () ;
	}

	LENGTH length () const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		if (!r1x.mItemQueue.exist ())
			return 0 ;
		return r1x.mItemQueue->length () ;
	}

	void reserve (const LENGTH &post_len) const {
		_DEBUG_ASSERT_ (post_len >= 0) ;
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		if (r1x.mItemQueue.exist ())
			if (r1x.mItemQueue->length () + post_len <= r1x.mItemQueue->size ())
				return ;
		auto rbx = AutoRef<List<ITEM ,SFIXED>>::make (post_len) ;
		rbx->appand (_MOVE_ (r1x.mItemQueue.self)) ;
		r1x.mItemQueue = _MOVE_ (rbx) ;
	}

	void post (const REMOVE_CONST_TYPE<ITEM> &item) const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		_DYNAMIC_ASSERT_ (r1x.mItemQueue->size () > 0) ;
		while (TRUE) {
			if (!r1x.mThreadFlag.exist ())
				break ;
			if (!r1x.mItemQueue->full ())
				break ;
			rbx.wait () ;
		}
		_DYNAMIC_ASSERT_ (r1x.mThreadFlag.exist ()) ;
		r1x.mItemQueue->add (_MOVE_ (item)) ;
		rbx.notify () ;
	}

	void post (REMOVE_CONST_TYPE<ITEM> &&item) const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		_DYNAMIC_ASSERT_ (r1x.mItemQueue->size () > 0) ;
		while (TRUE) {
			if (!r1x.mThreadFlag.exist ())
				break ;
			if (!r1x.mItemQueue->full ())
				break ;
			rbx.wait () ;
		}
		_DYNAMIC_ASSERT_ (r1x.mThreadFlag.exist ()) ;
		r1x.mItemQueue->add (_MOVE_ (item)) ;
		rbx.notify () ;
	}

	void post (const REMOVE_CONST_TYPE<ITEM> &item ,const Duration &interval ,const Function<BOOL ()> &predicate) const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		_DYNAMIC_ASSERT_ (r1x.mItemQueue->size () > 0) ;
		while (TRUE) {
			if (!r1x.mThreadFlag.exist ())
				break ;
			if (!r1x.mItemQueue->full ())
				break ;
			const auto r2x = predicate () ;
			_DYNAMIC_ASSERT_ (r2x) ;
			rbx.wait (interval) ;
		}
		_DYNAMIC_ASSERT_ (r1x.mThreadFlag.exist ()) ;
		r1x.mItemQueue->add (_MOVE_ (item)) ;
		rbx.notify () ;
	}

	void post (REMOVE_CONST_TYPE<ITEM> &&item ,const Duration &interval ,const Function<BOOL ()> &predicate) const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		_DYNAMIC_ASSERT_ (r1x.mItemQueue->size () > 0) ;
		while (TRUE) {
			if (!r1x.mThreadFlag.exist ())
				break ;
			if (!r1x.mItemQueue->full ())
				break ;
			const auto r2x = predicate () ;
			_DYNAMIC_ASSERT_ (r2x) ;
			rbx.wait (interval) ;
		}
		_DYNAMIC_ASSERT_ (r1x.mThreadFlag.exist ()) ;
		r1x.mItemQueue->add (_MOVE_ (item)) ;
		rbx.notify () ;
	}

	void start (const LENGTH &count ,Function<MEMPTR<void (const ITEM &)>> &&proc) const {
		struct Dependent ;
		using ThreadBinder = typename DEPENDENT_TYPE<Private ,Dependent>::ThreadBinder ;
		_DEBUG_ASSERT_ (count > 0) ;
		_DEBUG_ASSERT_ (proc.exist ()) ;
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		_DEBUG_ASSERT_ (!r1x.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (r1x.mThreadCounter == 0) ;
		r1x.mThreadFlag = AutoRef<BOOL>::make (TRUE) ;
		r1x.mThreadCounter = 0 ;
		r1x.mThreadWaitCounter = 0 ;
		r1x.mThreadProc = _MOVE_ (proc) ;
		if (!r1x.mItemQueue.exist ())
			r1x.mItemQueue = AutoRef<List<ITEM ,SFIXED>>::make (count) ;
		r1x.mItemQueue->clear () ;
		r1x.mException = AutoRef<Exception> () ;
		r1x.mThreadPool = Array<AutoRef<Thread>> (count) ;
		for (auto &&i : _RANGE_ (0 ,r1x.mThreadPool.length ())) {
			//@warn: forward object having captured context
			const auto r2x = StrongRef<ThreadBinder>::make (PhanRef<SELF_PACK>::make (r1x)) ;
			r1x.mThreadPool[i] = AutoRef<Thread>::make (r2x) ;
		}
	}

	void join (const Duration &interval ,const Function<BOOL ()> &predicate) const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		while (TRUE) {
			_DYNAMIC_ASSERT_ (r1x.mThreadFlag.exist ()) ;
			if (r1x.mException.exist ())
				break ;
			if (r1x.mThreadWaitCounter >= r1x.mThreadPool.length ())
				if (r1x.mItemQueue->empty ())
					break ;
			const auto r2x = predicate () ;
			if (!r2x)
				break ;
			rbx.wait (interval) ;
		}
		const auto r3x = _MOVE_ (r1x.mException) ;
		if (!r3x.exist ())
			return ;
		r3x->raise () ;
	}

	void stop () const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		static_destroy (r1x) ;
	}

private:
	imports void static_create (SELF_PACK &self_) {
		ScopedGuard<Mutex> ANONYMOUS (self_.mThreadMutex) ;
		self_.mThreadFlag = AutoRef<BOOL> () ;
		self_.mThreadCounter = 0 ;
		self_.mThreadWaitCounter = 0 ;
		self_.mThreadPool = Array<AutoRef<Thread>> () ;
		self_.mThreadProc = Function<MEMPTR<void (const ITEM &)>> () ;
	}

	imports void static_destroy (SELF_PACK &self_) {
		auto rbx = self_.mThreadConditionLock.watch (PhanRef<Mutex>::make (self_.mThreadMutex)) ;
		if (!self_.mThreadFlag.exist ())
			return ;
		self_.mThreadFlag.self = FALSE ;
		rbx.notify () ;
		while (TRUE) {
			if (!self_.mThreadFlag.exist ())
				break ;
			if (self_.mThreadCounter == 0)
				break ;
			rbx.yield () ;
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
		self_.mThreadPool = Array<AutoRef<Thread>> () ;
		self_.mThreadProc = Function<MEMPTR<void (const ITEM &)>> () ;
	}

	imports void static_execute (SELF_PACK &self_) {
		struct Dependent ;
		using ThreadCounter = typename DEPENDENT_TYPE<Private ,Dependent>::ThreadCounter ;
		ScopedGuard<ThreadCounter> ANONYMOUS (_CAST_ (ARGV<ThreadCounter>::null ,self_)) ;
		auto rbx = Optional<ITEM>::nullopt () ;
		while (TRUE) {
			static_poll (self_ ,rbx) ;
			_CATCH_ ([&] () {
				//@warn: 'mThreadProc' is not protected by 'mThreadMutex'
				self_.mThreadProc (rbx.self) ;
			} ,[&] (const Exception &e) {
				_CALL_TRY_ ([&] () {
					static_rethrow (self_ ,e) ;
				} ,[&] () {
					_STATIC_WARNING_ ("noop") ;
				}) ;
			}) ;
			rbx = Optional<ITEM>::nullopt () ;
		}
	}

	imports void static_poll (SELF_PACK &self_ ,Optional<ITEM> &item) {
		struct Dependent ;
		using Counter = typename DEPENDENT_TYPE<Private ,Dependent>::Counter ;
		auto rbx = self_.mThreadConditionLock.watch (PhanRef<Mutex>::make (self_.mThreadMutex)) ;
		_DEBUG_ASSERT_ (self_.mThreadFlag.exist ()) ;
		ScopedGuard<Counter> ANONYMOUS (_CAST_ (ARGV<Counter>::null ,self_.mThreadWaitCounter)) ;
		while (TRUE) {
			if (!self_.mThreadFlag.self)
				break ;
			if (!self_.mItemQueue->empty ())
				break ;
			rbx.wait () ;
		}
		_DYNAMIC_ASSERT_ (self_.mThreadFlag.self) ;
		item = _MOVE_ (self_.mItemQueue.self[self_.mItemQueue->head ()]) ;
		self_.mItemQueue->take () ;
	}

	imports void static_rethrow (SELF_PACK &self_ ,const Exception &e) {
		ScopedGuard<Mutex> ANONYMOUS (self_.mThreadMutex) ;
		_DEBUG_ASSERT_ (self_.mThreadFlag.exist ()) ;
		if (self_.mException.exist ())
			return ;
		self_.mException = AutoRef<Exception>::make (e) ;
	}
} ;

template <class ITEM>
class WorkThread<ITEM>::Private::ThreadBinder
	:public Thread::Binder {
private:
	PhanRef<SELF_PACK> mThis ;

public:
	implicit ThreadBinder () = delete ;

	explicit ThreadBinder (PhanRef<SELF_PACK> &&this_) {
		mThis = _MOVE_ (this_) ;
	}

	void execute () override {
		_CALL_TRY_ ([&] () {
			static_execute (mThis) ;
		} ,[&] () {
			_STATIC_WARNING_ ("noop") ;
		}) ;
	}
} ;

template <class ITEM>
class WorkThread<ITEM>::Private::ThreadCounter
	:private Wrapped<SELF_PACK> {
public:
	void lock () {
		ScopedGuard<Mutex> ANONYMOUS (ThreadCounter::mSelf.mThreadMutex) ;
		ThreadCounter::mSelf.mThreadCounter++ ;
	}

	void unlock () {
		ScopedGuard<Mutex> ANONYMOUS (ThreadCounter::mSelf.mThreadMutex) ;
		ThreadCounter::mSelf.mThreadCounter-- ;
	}
} ;

template <class ITEM>
class WorkThread<ITEM>::Private::Counter
	:private Wrapped<LENGTH> {
public:
	void lock () {
		Counter::mSelf++ ;
	}

	void unlock () {
		Counter::mSelf-- ;
	}
} ;

template <class>
class Future ;

template <class ITEM>
class Promise {
private:
	struct SELF_PACK {
		Mutex mThreadMutex ;
		ConditionLock mThreadConditionLock ;
		LENGTH mThreadCounter ;
		AutoRef<BOOL> mThreadFlag ;
		Function<MEMPTR<ITEM ()>> mThreadProc ;
		Function<MEMPTR<void (ITEM &)>> mCallbackProc ;
		AutoRef<Thread> mThreadPool ;
		AutoRef<ITEM> mItem ;
		AutoRef<Exception> mException ;
	} ;

	struct Private {
		class ThreadBinder ;

		class ThreadCounter ;
	} ;

private:
	StrongRef<UniqueRef<SharedRef<SELF_PACK>>> mThis ;

public:
	implicit Promise () {
		auto tmp = UniqueRef<SharedRef<SELF_PACK>> ([&] (SharedRef<SELF_PACK> &me) {
			me = SharedRef<SELF_PACK>::make () ;
			static_create (me.self) ;
		} ,[] (SharedRef<SELF_PACK> &me) {
			static_destroy (me.self) ;
		}) ;
		mThis = StrongRef<UniqueRef<SharedRef<SELF_PACK>>>::make (_MOVE_ (tmp)) ;
	}

	template <class _RET = REMOVE_CVR_TYPE<Future<ITEM>>>
	_RET future () const {
		struct Dependent ;
		using Future = DEPENDENT_TYPE<Future<ITEM> ,Dependent> ;
		return Future (mThis) ;
	}

	void push (const REMOVE_CONST_TYPE<ITEM> &item) const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		static_push (r1x ,_MOVE_ (item)) ;
	}

	void push (REMOVE_CONST_TYPE<ITEM> &&item) const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		static_push (r1x ,_MOVE_ (item)) ;
	}

	void rethrow (const Exception &e) const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		static_rethrow (r1x) ;
	}

	void start () const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (!r1x.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (r1x.mThreadCounter == 0) ;
		r1x.mThreadFlag = AutoRef<BOOL>::make (TRUE) ;
		r1x.mThreadCounter = 0 ;
		r1x.mThreadProc = Function<MEMPTR<ITEM ()>> () ;
		r1x.mCallbackProc = Function<MEMPTR<void (ITEM &)>> () ;
		r1x.mItem = AutoRef<ITEM> () ;
		r1x.mException = AutoRef<Exception> () ;
		r1x.mThreadPool = AutoRef<Thread> () ;
	}

	void start (Function<MEMPTR<ITEM ()>> &&proc) const {
		struct Dependent ;
		using ThreadBinder = typename DEPENDENT_TYPE<Private ,Dependent>::ThreadBinder ;
		_DEBUG_ASSERT_ (proc.exist ()) ;
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (!r1x.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (r1x.mThreadCounter == 0) ;
		r1x.mThreadFlag = AutoRef<BOOL>::make (TRUE) ;
		r1x.mThreadCounter = 0 ;
		r1x.mThreadProc = _MOVE_ (proc) ;
		r1x.mCallbackProc = Function<MEMPTR<void (ITEM &)>> () ;
		r1x.mItem = AutoRef<ITEM> () ;
		r1x.mException = AutoRef<Exception> () ;
		//@warn: forward object having captured context
		const auto r2x = StrongRef<ThreadBinder>::make (PhanRef<SELF_PACK>::make (r1x)) ;
		r1x.mThreadPool = AutoRef<Thread>::make (r2x) ;
	}

	void signal () const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		static_signal (r1x) ;
	}

	void stop () const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		static_destroy (r1x) ;
	}

	template <class _RET = REMOVE_CVR_TYPE<Future<ITEM>>>
	imports _RET async (Function<MEMPTR<ITEM ()>> &&proc) {
		auto rbx = Promise<ITEM> () ;
		rbx.start (_MOVE_ (proc)) ;
		return rbx.future () ;
	}

private:
	imports void static_create (SELF_PACK &self_) {
		ScopedGuard<Mutex> ANONYMOUS (self_.mThreadMutex) ;
		self_.mThreadFlag = AutoRef<BOOL> () ;
		self_.mThreadCounter = 0 ;
		self_.mThreadPool = AutoRef<Thread> () ;
		self_.mThreadProc = Function<MEMPTR<ITEM ()>> () ;
		self_.mCallbackProc = Function<MEMPTR<void (ITEM &)>> () ;
	}

	imports void static_destroy (SELF_PACK &self_) {
		auto rbx = self_.mThreadConditionLock.watch (PhanRef<Mutex>::make (self_.mThreadMutex)) ;
		if (!self_.mThreadFlag.exist ())
			return ;
		self_.mThreadFlag.self = FALSE ;
		rbx.notify () ;
		while (TRUE) {
			if (!self_.mThreadFlag.exist ())
				break ;
			if (self_.mThreadCounter == 0)
				break ;
			rbx.yield () ;
		}
		_DYNAMIC_ASSERT_ (self_.mThreadFlag.exist ()) ;
		if (self_.mThreadPool.exist ())
			self_.mThreadPool->join () ;
		self_.mThreadFlag = AutoRef<BOOL> () ;
		self_.mThreadCounter = 0 ;
		self_.mThreadPool = AutoRef<Thread> () ;
		self_.mThreadProc = Function<MEMPTR<ITEM ()>> () ;
		self_.mCallbackProc = Function<MEMPTR<void (ITEM &)>> () ;
	}

	imports void static_execute (SELF_PACK &self_) {
		struct Dependent ;
		using ThreadCounter = typename DEPENDENT_TYPE<Private ,Dependent>::ThreadCounter ;
		ScopedGuard<ThreadCounter> ANONYMOUS (_CAST_ (ARGV<ThreadCounter>::null ,self_)) ;
		auto rbx = Optional<ITEM>::nullopt () ;
		_CATCH_ ([&] () {
			//@warn: 'mThreadProc' is not protected by 'mThreadMutex'
			rbx = self_.mThreadProc () ;
		} ,[&] (const Exception &e) {
			_CALL_TRY_ ([&] () {
				static_rethrow (self_ ,e) ;
			} ,[&] () {
				_STATIC_WARNING_ ("noop") ;
			}) ;
		}) ;
		if (rbx.exist ())
			static_push (self_ ,_MOVE_ (rbx.self)) ;
		static_signal (self_) ;
	}

	imports void static_push (SELF_PACK &self_ ,const REMOVE_CONST_TYPE<ITEM> &item) {
		ScopedGuard<Mutex> ANONYMOUS (self_.mThreadMutex) ;
		_DEBUG_ASSERT_ (self_.mThreadFlag.exist ()) ;
		_DYNAMIC_ASSERT_ (self_.mThreadFlag.self) ;
		_DEBUG_ASSERT_ (!self_.mException.exist ()) ;
		self_.mItem = AutoRef<ITEM>::make (_MOVE_ (item)) ;
	}

	imports void static_push (SELF_PACK &self_ ,REMOVE_CONST_TYPE<ITEM> &&item) {
		ScopedGuard<Mutex> ANONYMOUS (self_.mThreadMutex) ;
		_DEBUG_ASSERT_ (self_.mThreadFlag.exist ()) ;
		_DYNAMIC_ASSERT_ (self_.mThreadFlag.self) ;
		_DEBUG_ASSERT_ (!self_.mException.exist ()) ;
		self_.mItem = AutoRef<ITEM>::make (_MOVE_ (item)) ;
	}

	imports void static_rethrow (SELF_PACK &self_ ,const Exception &e) {
		ScopedGuard<Mutex> ANONYMOUS (self_.mThreadMutex) ;
		_DEBUG_ASSERT_ (self_.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (!self_.mException.exist ()) ;
		self_.mItem = AutoRef<ITEM> () ;
		self_.mException = AutoRef<Exception>::make (e) ;
	}

	imports void static_signal (SELF_PACK &self_) {
		auto rbx = self_.mThreadConditionLock.watch (PhanRef<Mutex>::make (self_.mThreadMutex)) ;
		_DEBUG_ASSERT_ (self_.mThreadFlag.exist ()) ;
		self_.mThreadFlag.self = FALSE ;
		rbx.notify () ;
		if switch_once (TRUE) {
			if (!self_.mItem.exist ())
				discard ;
			if (!self_.mCallbackProc.exist ())
				discard ;
			self_.mCallbackProc (self_.mItem) ;
		}
		self_.mCallbackProc = Function<MEMPTR<void (ITEM &)>> () ;
	}
} ;

template <class ITEM>
class Promise<ITEM>::Private::ThreadBinder
	:public Thread::Binder {
private:
	PhanRef<SELF_PACK> mThis ;

public:
	implicit ThreadBinder () = delete ;

	explicit ThreadBinder (PhanRef<SELF_PACK> &&this_) {
		mThis = _MOVE_ (this_) ;
	}

	void execute () override {
		_CALL_TRY_ ([&] () {
			static_execute (mThis) ;
		} ,[&] () {
			_STATIC_WARNING_ ("noop") ;
		}) ;
	}
} ;

template <class ITEM>
class Promise<ITEM>::Private::ThreadCounter
	:private Wrapped<SELF_PACK> {
public:
	void lock () {
		ScopedGuard<Mutex> ANONYMOUS (ThreadCounter::mSelf.mThreadMutex) ;
		ThreadCounter::mSelf.mThreadCounter++ ;
	}

	void unlock () {
		ScopedGuard<Mutex> ANONYMOUS (ThreadCounter::mSelf.mThreadMutex) ;
		ThreadCounter::mSelf.mThreadCounter-- ;
	}
} ;

template <class ITEM>
class Future {
private:
	using SELF_PACK = typename Promise<ITEM>::SELF_PACK ;

private:
	StrongRef<UniqueRef<SharedRef<SELF_PACK>>> mThis ;

public:
	implicit Future () = delete ;

	explicit Future (const StrongRef<UniqueRef<SharedRef<SELF_PACK>>> &this_) {
		mThis = this_.share () ;
	}

	BOOL ready () const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		if (!r1x.mThreadFlag.exist ())
			return TRUE ;
		if (r1x.mThreadFlag.self)
			return FALSE ;
		return TRUE ;
	}

	ITEM poll () const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		while (TRUE) {
			if (!r1x.mThreadFlag.exist ())
				break ;
			if (!r1x.mThreadFlag.self)
				break ;
			rbx.wait () ;
		}
		if (r1x.mException.exist ())
			r1x.mException->raise () ;
		_DYNAMIC_ASSERT_ (r1x.mItem.exist ()) ;
		ITEM ret = _MOVE_ (r1x.mItem.self) ;
		r1x.mItem = AutoRef<ITEM> () ;
		return _MOVE_ (ret) ;
	}

	ITEM poll (const Duration &interval ,const Function<BOOL ()> &predicate) const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		while (TRUE) {
			if (!r1x.mThreadFlag.exist ())
				break ;
			if (!r1x.mThreadFlag.self)
				break ;
			const auto r2x = predicate () ;
			_DYNAMIC_ASSERT_ (r2x) ;
			rbx.wait (interval) ;
		}
		if (r1x.mException.exist ())
			r1x.mException->raise () ;
		_DYNAMIC_ASSERT_ (r1x.mItem.exist ()) ;
		ITEM ret = _MOVE_ (r1x.mItem.self) ;
		r1x.mItem = AutoRef<ITEM> () ;
		return _MOVE_ (ret) ;
	}

	ITEM value (const ITEM &def) const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		if (!r1x.mThreadFlag.exist ())
			return def ;
		if (r1x.mThreadFlag.self)
			return def ;
		if (!r1x.mItem.exist ())
			return def ;
		return r1x.mItem.self ;
	}

	void then (Function<MEMPTR<void (ITEM &)>> &&proc) const {
		_DEBUG_ASSERT_ (proc.exist ()) ;
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		_DYNAMIC_ASSERT_ (r1x.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (!r1x.mCallbackProc.exist ()) ;
		r1x.mCallbackProc = _MOVE_ (proc) ;
		if (r1x.mThreadFlag.self)
			return ;
		if (!r1x.mItem.exist ())
			return ;
		r1x.mCallbackProc (r1x.mItem.self) ;
		r1x.mCallbackProc = Function<MEMPTR<void (ITEM &)>> () ;
	}

	void stop () const {
		auto rax = mThis.share () ;
		auto &r1x = rax.self->self ;
		static_destroy (r1x) ;
	}
} ;
} ;