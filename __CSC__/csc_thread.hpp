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
	struct THIS_PACK {
		Mutex mThreadMutex ;
		ConditionLock mThreadConditionLock ;
		AutoRef<BOOL> mThreadFlag ;
		LENGTH mThreadCounter ;
		Array<Function<MEMPTR<ITEM ()>>> mThreadProc ;
		Array<AutoRef<Thread>> mThreadPool ;
		AutoRef<List<ITEM ,SFIXED>> mItemQueue ;
		AutoRef<Exception> mException ;
	} ;

	struct THREAD_PACK {
		SharedRef<THIS_PACK> mThis ;
		UniqueRef<SharedRef<THIS_PACK>> mKeep ;
	} ;

	struct Private {
		class ThreadBinder ;

		class ThreadCounter ;
	} ;

private:
	StrongRef<THREAD_PACK> mThis ;

public:
	implicit CalcThread () {
		mThis = StrongRef<THREAD_PACK>::make () ;
		mThis->mKeep = UniqueRef<SharedRef<THIS_PACK>> ([&] (SharedRef<THIS_PACK> &me) {
			me = SharedRef<THIS_PACK>::make () ;
		} ,[] (SharedRef<THIS_PACK> &me) {
			static_destroy (me.self) ;
		}) ;
		mThis->mThis = mThis->mKeep.self ;
		auto &r1x = mThis->mThis.self ;
		static_create (r1x) ;
	}

	LENGTH size () const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		if (!r1x.mItemQueue.exist ())
			return 0 ;
		return r1x.mItemQueue->size () ;
	}

	LENGTH length () const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		if (!r1x.mItemQueue.exist ())
			return 0 ;
		return r1x.mItemQueue->length () ;
	}

	ITEM poll () const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		_DEBUG_ASSERT_ (r1x.mThreadFlag.exist ()) ;
		while (TRUE) {
			if (!r1x.mThreadFlag.self ())
				break ;
			if (!r1x.mItemQueue->empty ())
				break ;
			rbx.wait () ;
		}
		_DYNAMIC_ASSERT_ (r1x.mThreadFlag.self) ;
		rbx.notify () ;
		ITEM ret = _MOVE_ (r1x.mItemQueue.self[r1x.mItemQueue->head ()]) ;
		r1x.mItemQueue->take () ;
		return _MOVE_ (ret) ;
	}

	ITEM poll (const Duration &interval ,const Function<BOOL ()> &predicate) const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		_DEBUG_ASSERT_ (r1x.mThreadFlag.exist ()) ;
		while (TRUE) {
			if (!r1x.mThreadFlag.self)
				break ;
			if (!r1x.mItemQueue->empty ())
				break ;
			const auto r2x = predicate () ;
			_DYNAMIC_ASSERT_ (r2x) ;
			rbx.wait (interval) ;
		}
		_DYNAMIC_ASSERT_ (r1x.mThreadFlag.self) ;
		rbx.notify () ;
		ITEM ret = _MOVE_ (r1x.mItemQueue.self[r1x.mItemQueue->head ()]) ;
		r1x.mItemQueue->take () ;
		return _MOVE_ (ret) ;
	}

	void start (const LENGTH &count ,Array<Function<MEMPTR<ITEM ()>>> &&proc) const {
		struct Dependent ;
		using R1X = typename DEPENDENT_TYPE<Private ,Dependent>::ThreadBinder ;
		_DEBUG_ASSERT_ (count > 0) ;
		_DEBUG_ASSERT_ (proc.length () > 0) ;
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		_DEBUG_ASSERT_ (!r1x.mThreadFlag.exist ()) ;
		r1x.mThreadFlag = AutoRef<BOOL>::make (TRUE) ;
		r1x.mThreadCounter = 0 ;
		r1x.mThreadProc = Array<Function<MEMPTR<ITEM ()>>> (proc.length ()) ;
		for (auto &&i : _RANGE_ (0 ,proc.length ())) {
			_DEBUG_ASSERT_ (proc[i].exist ()) ;
			r1x.mThreadProc[i] = _MOVE_ (proc[i]) ;
		}
		r1x.mItemQueue = AutoRef<List<ITEM ,SFIXED>>::make (count) ;
		r1x.mException = AutoRef<Exception> () ;
		r1x.mThreadPool = Array<AutoRef<Thread>> (proc.size ()) ;
		for (auto &&i : _RANGE_ (0 ,r1x.mThreadPool.length ())) {
			//@warn: forward object having captured context
			const auto r2x = StrongRef<R1X>::make (PhanRef<THIS_PACK>::make (r1x) ,i) ;
			r1x.mThreadPool[i] = AutoRef<Thread>::make (r2x) ;
		}
	}

	void join (const Duration &interval ,const Function<BOOL ()> &predicate) const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		_DEBUG_ASSERT_ (r1x.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (r1x.mItemQueue->size () > 0) ;
		while (TRUE) {
			if (!r1x.mThreadFlag.self)
				break ;
			if (r1x.mException.exist ())
				break ;
			if (r1x.mItemQueue->full ())
				break ;
			const auto r2x = predicate () ;
			if (!r2x)
				break ;
			rbx.wait (interval) ;
		}
		_DYNAMIC_ASSERT_ (r1x.mThreadFlag.self) ;
		const auto r3x = _MOVE_ (r1x.mException) ;
		if (!r3x.exist ())
			return ;
		r3x->raise () ;
	}

	void stop () const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		static_destroy (r1x) ;
	}

private:
	imports void static_create (THIS_PACK &this_) {
		ScopedGuard<Mutex> ANONYMOUS (this_.mThreadMutex) ;
		this_.mThreadFlag = AutoRef<BOOL> () ;
		this_.mThreadCounter = 0 ;
		this_.mThreadPool = Array<AutoRef<Thread>> () ;
		this_.mThreadProc = Array<Function<MEMPTR<ITEM ()>>> () ;
	}

	imports void static_destroy (THIS_PACK &this_) {
		auto rax = this_.mThreadConditionLock.watch (PhanRef<Mutex>::make (this_.mThreadMutex)) ;
		if (!this_.mThreadFlag.exist ())
			return ;
		this_.mThreadFlag.self = FALSE ;
		while (TRUE) {
			if (!this_.mThreadFlag.exist ())
				break ;
			if (this_.mThreadCounter == 0)
				break ;
			rax.yield () ;
		}
		_DYNAMIC_ASSERT_ (this_.mThreadFlag.exist ()) ;
		for (auto &&i : this_.mThreadPool) {
			if (!i.exist ())
				continue ;
			i->join () ;
		}
		this_.mThreadFlag = AutoRef<BOOL> () ;
		this_.mThreadCounter = 0 ;
		this_.mThreadPool = Array<AutoRef<Thread>> () ;
		this_.mThreadProc = Array<Function<MEMPTR<ITEM ()>>> () ;
	}

	imports void static_execute (THIS_PACK &this_ ,const INDEX &tid) {
		struct Dependent ;
		using R1X = typename DEPENDENT_TYPE<Private ,Dependent>::ThreadCounter ;
		ScopedGuard<R1X> ANONYMOUS (_CAST_ (ARGV<R1X>::null ,this_)) ;
		auto rax = Optional<ITEM>::nullopt () ;
		while (TRUE) {
			try {
				//@warn: 'mThreadProc' is not protected by 'mThreadMutex'
				rax = this_.mThreadProc[tid] () ;
			} catch (const Exception &e) {
				static_rethrow (this_ ,e) ;
			} catch (...) {
				const auto r1x = Exception (_PCSTR_ ("unknown C++ exception")) ;
				static_rethrow (this_ ,r1x) ;
			}
			if (rax.exist ())
				static_push (this_ ,_MOVE_ (rax.self)) ;
			rax = Optional<ITEM>::nullopt () ;
		}
	}

	imports void static_push (THIS_PACK &this_ ,const REMOVE_CONST_TYPE<ITEM> &item) {
		auto rax = this_.mThreadConditionLock.watch (PhanRef<Mutex>::make (this_.mThreadMutex)) ;
		_DEBUG_ASSERT_ (this_.mThreadFlag.exist ()) ;
		if switch_once (TRUE) {
			if (!this_.mThreadFlag.self)
				discard ;
			if (!this_.mItemQueue->full ())
				discard ;
			rax.yield () ;
		}
		_DYNAMIC_ASSERT_ (this_.mThreadFlag.self) ;
		rax.notify () ;
		if (this_.mItemQueue->full ())
			this_.mItemQueue->take () ;
		this_.mItemQueue->add (_MOVE_ (item)) ;
	}

	imports void static_push (THIS_PACK &this_ ,REMOVE_CONST_TYPE<ITEM> &&item) {
		auto rax = this_.mThreadConditionLock.watch (PhanRef<Mutex>::make (this_.mThreadMutex)) ;
		_DEBUG_ASSERT_ (this_.mThreadFlag.exist ()) ;
		if switch_once (TRUE) {
			if (!this_.mThreadFlag.self)
				discard ;
			if (!this_.mItemQueue->full ())
				discard ;
			rax.yield () ;
		}
		_DYNAMIC_ASSERT_ (this_.mThreadFlag.self) ;
		rax.notify () ;
		if (this_.mItemQueue->full ())
			this_.mItemQueue->take () ;
		this_.mItemQueue->add (_MOVE_ (item)) ;
	}

	imports void static_rethrow (THIS_PACK &this_ ,const Exception &e) {
		ScopedGuard<Mutex> ANONYMOUS (this_.mThreadMutex) ;
		_DEBUG_ASSERT_ (this_.mThreadFlag.exist ()) ;
		if (this_.mException.exist ())
			return ;
		this_.mException = AutoRef<Exception>::make (e) ;
	}
} ;

template <class ITEM>
class CalcThread<ITEM>::Private::ThreadBinder
	:public Thread::Binder {
private:
	PhanRef<THIS_PACK> mThis ;
	INDEX mThreadID ;

public:
	implicit ThreadBinder () = delete ;

	explicit ThreadBinder (PhanRef<THIS_PACK> &&this_ ,const INDEX &tid) {
		mThis = _MOVE_ (this_) ;
		mThreadID = tid ;
	}

	void execute () override {
		_CALL_TRY_ ([&] () {
			static_execute (mThis ,mThreadID) ;
		} ,[&] () {
			_STATIC_WARNING_ ("noop") ;
		}) ;
	}
} ;

template <class ITEM>
class CalcThread<ITEM>::Private::ThreadCounter
	:private Wrapped<THIS_PACK> {
private:
	using Wrapped<THIS_PACK>::mSelf ;

public:
	void lock () {
		ScopedGuard<Mutex> ANONYMOUS (mSelf.mThreadMutex) ;
		mSelf.mThreadCounter++ ;
	}

	void unlock () {
		ScopedGuard<Mutex> ANONYMOUS (mSelf.mThreadMutex) ;
		mSelf.mThreadCounter-- ;
	}
} ;

template <class ITEM>
class WorkThread {
private:
	struct THIS_PACK {
		Mutex mThreadMutex ;
		ConditionLock mThreadConditionLock ;
		LENGTH mThreadCounter ;
		AutoRef<BOOL> mThreadFlag ;
		Function<MEMPTR<void (const ITEM &)>> mThreadProc ;
		Set<INDEX> mThreadPendingSet ;
		Array<AutoRef<Thread>> mThreadPool ;
		AutoRef<List<ITEM ,SFIXED>> mItemQueue ;
		AutoRef<Exception> mException ;
	} ;

	struct THREAD_PACK {
		SharedRef<THIS_PACK> mThis ;
		UniqueRef<SharedRef<THIS_PACK>> mKeep ;
	} ;

	struct Private {
		class ThreadBinder ;

		class ThreadCounter ;
	} ;

private:
	StrongRef<THREAD_PACK> mThis ;

public:
	implicit WorkThread () {
		mThis = StrongRef<THREAD_PACK>::make () ;
		mThis->mKeep = UniqueRef<SharedRef<THIS_PACK>> ([&] (SharedRef<THIS_PACK> &me) {
			me = SharedRef<THIS_PACK>::make () ;
		} ,[] (SharedRef<THIS_PACK> &me) {
			static_destroy (me.self) ;
		}) ;
		mThis->mThis = mThis->mKeep.self ;
		auto &r1x = mThis->mThis.self ;
		static_create (r1x) ;
	}

	LENGTH size () const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		if (!r1x.mItemQueue.exist ())
			return 0 ;
		return r1x.mItemQueue->size () ;
	}

	LENGTH length () const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		if (!r1x.mItemQueue.exist ())
			return 0 ;
		return r1x.mItemQueue->length () ;
	}

	void post (const REMOVE_CONST_TYPE<ITEM> &item) const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		_DEBUG_ASSERT_ (r1x.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (r1x.mItemQueue->size () > 0) ;
		while (TRUE) {
			if (!r1x.mThreadFlag.self)
				break ;
			if (!r1x.mItemQueue->full ())
				break ;
			rbx.wait () ;
		}
		_DYNAMIC_ASSERT_ (r1x.mThreadFlag.self) ;
		rbx.notify () ;
		r1x.mItemQueue->add (_MOVE_ (item)) ;
	}

	void post (REMOVE_CONST_TYPE<ITEM> &&item) const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		_DEBUG_ASSERT_ (r1x.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (r1x.mItemQueue->size () > 0) ;
		while (TRUE) {
			if (!r1x.mThreadFlag.self)
				break ;
			if (!r1x.mItemQueue->full ())
				break ;
			rbx.wait () ;
		}
		_DYNAMIC_ASSERT_ (r1x.mThreadFlag.self) ;
		rbx.notify () ;
		r1x.mItemQueue->add (_MOVE_ (item)) ;
	}

	void post (const Array<REMOVE_CVR_TYPE<ITEM>> &item) const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		_DEBUG_ASSERT_ (r1x.mThreadFlag.exist ()) ;
		_DYNAMIC_ASSERT_ (r1x.mItemQueue->size () > 0) ;
		while (TRUE) {
			if (!r1x.mThreadFlag.self)
				break ;
			if (!r1x.mItemQueue->full ())
				break ;
			rbx.wait () ;
		}
		_DYNAMIC_ASSERT_ (r1x.mThreadFlag.self) ;
		rbx.notify () ;
		if switch_once (TRUE) {
			if (r1x.mItemQueue->length () + item.length () <= r1x.mItemQueue->size ())
				discard ;
			auto rcx = AutoRef<List<ITEM ,SFIXED>>::make (item.length ()) ;
			rcx->appand (_MOVE_ (r1x.mItemQueue.self)) ;
			r1x.mItemQueue = _MOVE_ (rcx) ;
		}
		for (auto &&i : _RANGE_ (0 ,item.length ()))
			r1x.mItemQueue->add (_MOVE_ (item[i])) ;
	}

	void post (Array<REMOVE_CVR_TYPE<ITEM>> &&item) const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		_DEBUG_ASSERT_ (r1x.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (r1x.mItemQueue->size () > 0) ;
		while (TRUE) {
			if (!r1x.mThreadFlag.self)
				break ;
			if (!r1x.mItemQueue->full ())
				break ;
			rbx.wait () ;
		}
		_DYNAMIC_ASSERT_ (r1x.mThreadFlag.self) ;
		rbx.notify () ;
		if switch_once (TRUE) {
			if (r1x.mItemQueue->length () + item.length () <= r1x.mItemQueue->size ())
				discard ;
			auto rcx = AutoRef<List<ITEM ,SFIXED>>::make (item.length ()) ;
			rcx->appand (_MOVE_ (r1x.mItemQueue.self)) ;
			r1x.mItemQueue = _MOVE_ (rcx) ;
		}
		for (auto &&i : _RANGE_ (0 ,item.length ()))
			r1x.mItemQueue->add (_MOVE_ (item[i])) ;
	}

	void start (const LENGTH &count ,Function<MEMPTR<void (const ITEM &)>> &&proc) const {
		struct Dependent ;
		using R1X = typename DEPENDENT_TYPE<Private ,Dependent>::ThreadBinder ;
		_DEBUG_ASSERT_ (count > 0) ;
		_DEBUG_ASSERT_ (proc.exist ()) ;
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		_DEBUG_ASSERT_ (!r1x.mThreadFlag.exist ()) ;
		r1x.mThreadFlag = AutoRef<BOOL>::make (TRUE) ;
		r1x.mThreadCounter = 0 ;
		r1x.mThreadProc = _MOVE_ (proc) ;
		r1x.mThreadPendingSet = Set<INDEX> (count) ;
		for (auto &&i : _RANGE_ (0 ,count))
			r1x.mThreadPendingSet.add (i) ;
		r1x.mItemQueue = AutoRef<List<ITEM ,SFIXED>>::make (count) ;
		r1x.mException = AutoRef<Exception> () ;
		r1x.mThreadPool = Array<AutoRef<Thread>> (count) ;
		for (auto &&i : _RANGE_ (0 ,r1x.mThreadPool.length ())) {
			//@warn: forward object having captured context
			const auto r2x = StrongRef<R1X>::make (PhanRef<THIS_PACK>::make (r1x) ,i) ;
			r1x.mThreadPool[i] = AutoRef<Thread>::make (r2x) ;
		}
	}

	void join (const Duration &interval ,const Function<BOOL ()> &predicate) const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		_DEBUG_ASSERT_ (r1x.mThreadFlag.exist ()) ;
		while (TRUE) {
			if (!r1x.mThreadFlag.self)
				break ;
			if (r1x.mException.exist ())
				break ;
			if (r1x.mThreadPendingSet.length () >= r1x.mThreadPool.length ())
				if (r1x.mItemQueue->empty ())
					break ;
			const auto r2x = predicate () ;
			if (!r2x)
				break ;
			rbx.wait (interval) ;
		}
		_DYNAMIC_ASSERT_ (r1x.mThreadFlag.self) ;
		const auto r3x = _MOVE_ (r1x.mException) ;
		if (!r3x.exist ())
			return ;
		r3x->raise () ;
	}

	void stop () const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		static_destroy (r1x) ;
	}

private:
	imports void static_create (THIS_PACK &this_) {
		ScopedGuard<Mutex> ANONYMOUS (this_.mThreadMutex) ;
		this_.mThreadFlag = AutoRef<BOOL> () ;
		this_.mThreadCounter = 0 ;
		this_.mThreadPool = Array<AutoRef<Thread>> () ;
		this_.mThreadProc = Function<MEMPTR<void (const ITEM &)>> () ;
		this_.mThreadPendingSet = Set<INDEX> () ;
	}

	imports void static_destroy (THIS_PACK &this_) {
		auto rax = this_.mThreadConditionLock.watch (PhanRef<Mutex>::make (this_.mThreadMutex)) ;
		if (!this_.mThreadFlag.exist ())
			return ;
		this_.mThreadFlag.self = FALSE ;
		while (TRUE) {
			if (!this_.mThreadFlag.exist ())
				break ;
			if (this_.mThreadCounter == 0)
				break ;
			rax.yield () ;
		}
		_DYNAMIC_ASSERT_ (this_.mThreadFlag.exist ()) ;
		for (auto &&i : this_.mThreadPool) {
			if (!i.exist ())
				continue ;
			i->join () ;
		}
		this_.mThreadFlag = AutoRef<BOOL> () ;
		this_.mThreadCounter = 0 ;
		this_.mThreadPool = Array<AutoRef<Thread>> () ;
		this_.mThreadProc = Function<MEMPTR<void (const ITEM &)>> () ;
		this_.mThreadPendingSet = Set<INDEX> () ;
	}

	imports void static_execute (THIS_PACK &this_ ,const INDEX &tid) {
		struct Dependent ;
		using R1X = typename DEPENDENT_TYPE<Private ,Dependent>::ThreadCounter ;
		ScopedGuard<R1X> ANONYMOUS (_CAST_ (ARGV<R1X>::null ,this_)) ;
		auto rax = List<ITEM> () ;
		while (TRUE) {
			if (rax.empty ())
				static_poll (this_ ,tid ,rax) ;
			INDEX ix = rax.head () ;
			try {
				//@warn: 'mThreadProc' is not protected by 'mThreadMutex'
				this_.mThreadProc (rax[ix]) ;
			} catch (const Exception &e) {
				static_rethrow (this_ ,e) ;
			} catch (...) {
				const auto r1x = Exception (_PCSTR_ ("unknown C++ exception")) ;
				static_rethrow (this_ ,r1x) ;
			}
			rax.remove (ix) ;
		}
	}

	imports void static_poll (THIS_PACK &this_ ,const INDEX &tid ,List<ITEM> &list) {
		struct Dependent ;
		auto rax = this_.mThreadConditionLock.watch (PhanRef<Mutex>::make (this_.mThreadMutex)) ;
		_DEBUG_ASSERT_ (this_.mThreadFlag.exist ()) ;
		this_.mThreadPendingSet.add (tid) ;
		while (TRUE) {
			if (!this_.mThreadFlag.self)
				break ;
			if (!this_.mItemQueue->empty ())
				break ;
			rax.wait () ;
		}
		_DYNAMIC_ASSERT_ (this_.mThreadFlag.self) ;
		rax.notify () ;
		const auto r1x = this_.mThreadPendingSet.length () + this_.mThreadPendingSet.size () ;
		const auto r2x = (this_.mItemQueue->length () + r1x - 1) / r1x ;
		for (auto &&i : _RANGE_ (0 ,r2x)) {
			_STATIC_UNUSED_ (i) ;
			list.add (_MOVE_ (this_.mItemQueue.self[this_.mItemQueue->head ()])) ;
			this_.mItemQueue->take () ;
		}
		this_.mThreadPendingSet.erase (tid) ;
	}

	imports void static_rethrow (THIS_PACK &this_ ,const Exception &e) {
		ScopedGuard<Mutex> ANONYMOUS (this_.mThreadMutex) ;
		_DEBUG_ASSERT_ (this_.mThreadFlag.exist ()) ;
		if (this_.mException.exist ())
			return ;
		this_.mException = AutoRef<Exception>::make (e) ;
	}
} ;

template <class ITEM>
class WorkThread<ITEM>::Private::ThreadBinder
	:public Thread::Binder {
private:
	PhanRef<THIS_PACK> mThis ;
	INDEX mThreadID ;

public:
	implicit ThreadBinder () = delete ;

	explicit ThreadBinder (PhanRef<THIS_PACK> &&this_ ,const INDEX &tid) {
		mThis = _MOVE_ (this_) ;
		mThreadID = tid ;
	}

	void execute () override {
		_CALL_TRY_ ([&] () {
			static_execute (mThis ,mThreadID) ;
		} ,[&] () {
			_STATIC_WARNING_ ("noop") ;
		}) ;
	}
} ;

template <class ITEM>
class WorkThread<ITEM>::Private::ThreadCounter
	:private Wrapped<THIS_PACK> {
private:
	using Wrapped<THIS_PACK>::mSelf ;

public:
	void lock () {
		ScopedGuard<Mutex> ANONYMOUS (mSelf.mThreadMutex) ;
		mSelf.mThreadCounter++ ;
	}

	void unlock () {
		ScopedGuard<Mutex> ANONYMOUS (mSelf.mThreadMutex) ;
		mSelf.mThreadCounter-- ;
	}
} ;

template <class>
class Future ;

template <class ITEM>
class Promise {
private:
	struct THIS_PACK {
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

	struct THREAD_PACK {
		SharedRef<THIS_PACK> mThis ;
		UniqueRef<SharedRef<THIS_PACK>> mKeep ;
	} ;

	struct Private {
		class ThreadBinder ;

		class ThreadCounter ;
	} ;

private:
	StrongRef<THREAD_PACK> mThis ;

public:
	implicit Promise () {
		mThis = StrongRef<THREAD_PACK>::make () ;
		mThis->mKeep = UniqueRef<SharedRef<THIS_PACK>> ([&] (SharedRef<THIS_PACK> &me) {
			me = SharedRef<THIS_PACK>::make () ;
		} ,[] (SharedRef<THIS_PACK> &me) {
			static_destroy (me.self) ;
		}) ;
		mThis->mThis = mThis->mKeep.self ;
		auto &r1x = mThis->mThis.self ;
		static_create (r1x) ;
	}

	template <class _RET = REMOVE_CVR_TYPE<Future<ITEM>>>
	_RET future () const {
		struct Dependent ;
		using R1X = DEPENDENT_TYPE<Future<ITEM> ,Dependent> ;
		return R1X (mThis) ;
	}

	void push (const REMOVE_CONST_TYPE<ITEM> &item) const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		static_push (r1x ,_MOVE_ (item)) ;
	}

	void push (REMOVE_CONST_TYPE<ITEM> &&item) const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		static_push (r1x ,_MOVE_ (item)) ;
	}

	void rethrow (const Exception &e) const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		static_rethrow (r1x) ;
	}

	void start () const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		_DEBUG_ASSERT_ (!r1x.mThreadFlag.exist ()) ;
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
		using R1X = typename DEPENDENT_TYPE<Private ,Dependent>::ThreadBinder ;
		_DEBUG_ASSERT_ (proc.exist ()) ;
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		_DEBUG_ASSERT_ (!r1x.mThreadFlag.exist ()) ;
		r1x.mThreadFlag = AutoRef<BOOL>::make (TRUE) ;
		r1x.mThreadCounter = 0 ;
		r1x.mThreadProc = _MOVE_ (proc) ;
		r1x.mCallbackProc = Function<MEMPTR<void (ITEM &)>> () ;
		r1x.mItem = AutoRef<ITEM> () ;
		r1x.mException = AutoRef<Exception> () ;
		//@warn: forward object having captured context
		const auto r2x = StrongRef<R1X>::make (PhanRef<THIS_PACK>::make (r1x)) ;
		r1x.mThreadPool = AutoRef<Thread>::make (r2x) ;
	}

	void signal () const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		static_signal (r1x) ;
	}

	void stop () const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		static_destroy (r1x) ;
	}

	template <class _RET = REMOVE_CVR_TYPE<Future<ITEM>>>
	imports _RET async (Function<MEMPTR<ITEM ()>> &&proc) {
		auto rax = Promise<ITEM> () ;
		rax.start (_MOVE_ (proc)) ;
		return rax.future () ;
	}

private:
	imports void static_create (THIS_PACK &this_) {
		ScopedGuard<Mutex> ANONYMOUS (this_.mThreadMutex) ;
		this_.mThreadFlag = AutoRef<BOOL> () ;
		this_.mThreadCounter = 0 ;
		this_.mThreadPool = AutoRef<Thread> () ;
		this_.mThreadProc = Function<MEMPTR<ITEM ()>> () ;
		this_.mCallbackProc = Function<MEMPTR<void (ITEM &)>> () ;
	}

	imports void static_destroy (THIS_PACK &this_) {
		auto rax = this_.mThreadConditionLock.watch (PhanRef<Mutex>::make (this_.mThreadMutex)) ;
		if (!this_.mThreadFlag.exist ())
			return ;
		this_.mThreadFlag.self = FALSE ;
		while (TRUE) {
			if (!this_.mThreadFlag.exist ())
				break ;
			if (this_.mThreadCounter == 0)
				break ;
			rax.yield () ;
		}
		_DYNAMIC_ASSERT_ (this_.mThreadFlag.exist ()) ;
		if (this_.mThreadPool.exist ())
			this_.mThreadPool->join () ;
		this_.mThreadFlag = AutoRef<BOOL> () ;
		this_.mThreadCounter = 0 ;
		this_.mThreadPool = AutoRef<Thread> () ;
		this_.mThreadProc = Function<MEMPTR<ITEM ()>> () ;
		this_.mCallbackProc = Function<MEMPTR<void (ITEM &)>> () ;
	}

	imports void static_execute (THIS_PACK &this_) {
		struct Dependent ;
		using R1X = typename DEPENDENT_TYPE<Private ,Dependent>::ThreadCounter ;
		ScopedGuard<R1X> ANONYMOUS (_CAST_ (ARGV<R1X>::null ,this_)) ;
		auto rax = Optional<ITEM>::nullopt () ;
		try {
			//@warn: 'mThreadProc' is not protected by 'mThreadMutex'
			rax = this_.mThreadProc () ;
		} catch (const Exception &e) {
			static_rethrow (this_ ,e) ;
		} catch (...) {
			const auto r1x = Exception (_PCSTR_ ("unknown C++ exception")) ;
			static_rethrow (this_ ,r1x) ;
		}
		if (rax.exist ())
			static_push (this_ ,_MOVE_ (rax.self)) ;
		static_signal (this_) ;
	}

	imports void static_push (THIS_PACK &this_ ,const REMOVE_CONST_TYPE<ITEM> &item) {
		ScopedGuard<Mutex> ANONYMOUS (this_.mThreadMutex) ;
		_DEBUG_ASSERT_ (this_.mThreadFlag.exist ()) ;
		_DYNAMIC_ASSERT_ (this_.mThreadFlag.self) ;
		_DEBUG_ASSERT_ (!this_.mException.exist ()) ;
		this_.mItem = AutoRef<ITEM>::make (_MOVE_ (item)) ;
	}

	imports void static_push (THIS_PACK &this_ ,REMOVE_CONST_TYPE<ITEM> &&item) {
		ScopedGuard<Mutex> ANONYMOUS (this_.mThreadMutex) ;
		_DEBUG_ASSERT_ (this_.mThreadFlag.exist ()) ;
		_DYNAMIC_ASSERT_ (this_.mThreadFlag.self) ;
		_DEBUG_ASSERT_ (!this_.mException.exist ()) ;
		this_.mItem = AutoRef<ITEM>::make (_MOVE_ (item)) ;
	}

	imports void static_rethrow (THIS_PACK &this_ ,const Exception &e) {
		ScopedGuard<Mutex> ANONYMOUS (this_.mThreadMutex) ;
		_DEBUG_ASSERT_ (this_.mThreadFlag.exist ()) ;
		_DEBUG_ASSERT_ (!this_.mException.exist ()) ;
		this_.mItem = AutoRef<ITEM> () ;
		this_.mException = AutoRef<Exception>::make (e) ;
	}

	imports void static_signal (THIS_PACK &this_) {
		auto rax = this_.mThreadConditionLock.watch (PhanRef<Mutex>::make (this_.mThreadMutex)) ;
		_DEBUG_ASSERT_ (this_.mThreadFlag.exist ()) ;
		this_.mThreadFlag.self = FALSE ;
		rax.notify () ;
		if switch_once (TRUE) {
			if (!this_.mItem.exist ())
				discard ;
			if (!this_.mCallbackProc.exist ())
				discard ;
			this_.mCallbackProc (this_.mItem) ;
		}
		this_.mCallbackProc = Function<MEMPTR<void (ITEM &)>> () ;
	}
} ;

template <class ITEM>
class Promise<ITEM>::Private::ThreadBinder
	:public Thread::Binder {
private:
	PhanRef<THIS_PACK> mThis ;

public:
	implicit ThreadBinder () = delete ;

	explicit ThreadBinder (PhanRef<THIS_PACK> &&this_) {
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
	:private Wrapped<THIS_PACK> {
private:
	using Wrapped<THIS_PACK>::mSelf ;

public:
	void lock () {
		ScopedGuard<Mutex> ANONYMOUS (mSelf.mThreadMutex) ;
		mSelf.mThreadCounter++ ;
	}

	void unlock () {
		ScopedGuard<Mutex> ANONYMOUS (mSelf.mThreadMutex) ;
		mSelf.mThreadCounter-- ;
	}
} ;

template <class ITEM>
class Future {
private:
	using THREAD_PACK = typename Promise<ITEM>::THREAD_PACK ;

private:
	StrongRef<THREAD_PACK> mThis ;

public:
	implicit Future () = delete ;

	explicit Future (const StrongRef<THREAD_PACK> &this_) {
		mThis = this_.share () ;
	}

	BOOL ready () const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		if (!r1x.mThreadFlag.exist ())
			return TRUE ;
		if (r1x.mThreadFlag.self)
			return FALSE ;
		return TRUE ;
	}

	ITEM poll () const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
		auto rbx = r1x.mThreadConditionLock.watch (PhanRef<Mutex>::make (r1x.mThreadMutex)) ;
		while (TRUE) {
			if (!r1x.mThreadFlag.exist ())
				break ;
			if (!r1x.mThreadFlag.self)
				break ;
			rbx.wait () ;
		}
		rbx.notify () ;
		if (r1x.mException.exist ())
			r1x.mException->raise () ;
		_DYNAMIC_ASSERT_ (r1x.mItem.exist ()) ;
		ITEM ret = _MOVE_ (r1x.mItem.self) ;
		r1x.mItem = AutoRef<ITEM> () ;
		return _MOVE_ (ret) ;
	}

	ITEM poll (const Duration &interval ,const Function<BOOL ()> &predicate) const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
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
		rbx.notify () ;
		if (r1x.mException.exist ())
			r1x.mException->raise () ;
		_DYNAMIC_ASSERT_ (r1x.mItem.exist ()) ;
		ITEM ret = _MOVE_ (r1x.mItem.self) ;
		r1x.mItem = AutoRef<ITEM> () ;
		return _MOVE_ (ret) ;
	}

	ITEM value (const ITEM &def) const {
		auto rax = mThis.share () ;
		auto &r1x = rax->mThis.self ;
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
		auto &r1x = rax->mThis.self ;
		ScopedGuard<Mutex> ANONYMOUS (r1x.mThreadMutex) ;
		_DEBUG_ASSERT_ (r1x.mThreadFlag.exist ()) ;
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
		auto &r1x = rax->mThis.self ;
		static_destroy (r1x) ;
	}
} ;
} ;