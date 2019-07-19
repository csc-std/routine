#pragma once

#ifndef __CSC_RUNTIME__
#define __CSC_RUNTIME__
#endif

#include "csc.hpp"
#include "csc_ext.hpp"
#include "csc_array.hpp"

namespace CSC {
template <class>
class GlobalStatic ;

template <>
class GlobalStatic<void> final :private Wrapped<void> {
private:
	struct NODE_A {
		FLAG mGUID ;
		PTR<struct NODE_A> mNext ;
		BOOL mReadOnly ;
		VAR mData ;
	} ;

	using GUID_TYPE = TEMP<BYTE[DEFAULT_RECURSIVE_SIZE::value]> ;

	struct NODE_B {
		GUID_TYPE mGUID ;
		PTR<struct NODE_B> mNext ;
		PTR<NONE> mData ;
	} ;

	class Holder {
	public:
		using INTRUSIVE_TYPE = GlobalStatic ;

	private:
		template <class>
		friend class GlobalStatic ;
		friend IntrusiveRef<Holder> ;
		Monostate<std::atomic<LENGTH>> mCounter ;
		Monostate<std::mutex> mNodeMutex ;
		LENGTH mLength_a ;
		PTR<NODE_A> mRoot_a ;
		LENGTH mLength_b ;
		PTR<NODE_B> mRoot_b ;
	} ;

private:
	template <class>
	friend class GlobalStatic ;
	friend IntrusiveRef<Holder> ;

private:
	//@warn: this function should be implemented with a 'runtime.dll'
	static DEF<PTR<NONE> (PTR<NONE> ,PTR<NONE>) popping> unique_atomic_address ;

	static Holder &unique () popping {
		return _CACHE_ ([] () {
			_STATIC_WARNING_ ("mark") ;
			auto rax = unique_atomic_address (NULL ,NULL) ;
			auto rbx = IntrusiveRef<Holder> () ;
			for (FOR_ONCE_DO_WHILE_FALSE) {
				if (rax != NULL)
					continue ;
				//@warn: sure 'GlobalHeap' can be used across DLL
				rbx = IntrusiveRef<Holder>::make () ;
				const auto r2x = rbx.watch () ;
				const auto r3x = &_XVALUE_<Holder> (r2x) ;
				const auto r4x = &_LOAD_<NONE> (r3x) ;
				rax = unique_atomic_address (NULL ,r4x) ;
			}
			_DYNAMIC_ASSERT_ (rax != NULL) ;
			const auto r5x = &_LOAD_<Holder> (rax) ;
			return IntrusiveRef<Holder> (r5x).watch () ;
		}) ;
	}

	static PTR<NODE_A> static_new_node (Holder &_self ,FLAG guid) popping {
		//@warn: sure 'GlobalHeap' can be used across DLL
		auto sgd = GlobalHeap::alloc<TEMP<NODE_A>> () ;
		ScopedHolder<NODE_A> ANONYMOUS (sgd) ;
		PTR<NODE_A> ret = &_LOAD_<NODE_A> (_XVALUE_<PTR<TEMP<NODE_A>>> (sgd)) ;
		_DEBUG_ASSERT_ (ret != NULL) ;
		ret->mGUID = guid ;
		ret->mNext = _self.mRoot_a ;
		_self.mRoot_a = ret ;
		_self.mLength_a++ ;
		sgd = NULL ;
		return std::move (ret) ;
	}

	static PTR<NODE_B> static_new_node (Holder &_self ,const GUID_TYPE &guid) popping {
		//@warn: sure 'GlobalHeap' can be used across DLL
		auto sgd = GlobalHeap::alloc<TEMP<NODE_B>> () ;
		ScopedHolder<NODE_B> ANONYMOUS (sgd) ;
		PTR<NODE_B> ret = &_LOAD_<NODE_B> (_XVALUE_<PTR<TEMP<NODE_B>>> (sgd)) ;
		_DEBUG_ASSERT_ (ret != NULL) ;
		ret->mGUID = guid ;
		ret->mNext = _self.mRoot_b ;
		_self.mRoot_b = ret ;
		_self.mLength_b++ ;
		sgd = NULL ;
		return std::move (ret) ;
	}

	static PTR<NODE_A> static_find_node (const Holder &_self ,FLAG guid) {
		for (PTR<NODE_A> i = _self.mRoot_a ; i != NULL ; i = i->mNext)
			if (i->mGUID == guid)
				return i ;
		return NULL ;
	}

	static PTR<NODE_B> static_find_node (const Holder &_self ,const GUID_TYPE &guid) {
		for (PTR<NODE_B> i = _self.mRoot_b ; i != NULL ; i = i->mNext)
			if (_MEMEQUAL_ (i->mGUID.unused ,PTRTOARR[guid.unused]))
				return i ;
		return NULL ;
	}

	static void intrusive_create (Holder &_self) {
		ScopedGuard<std::mutex> ANONYMOUS (_self.mNodeMutex) ;
		_self.mCounter.self = 0 ;
		_self.mLength_a = 0 ;
		_self.mRoot_a = NULL ;
		_self.mLength_b = 0 ;
		_self.mRoot_b = NULL ;
	}

	static void intrusive_destroy (Holder &_self) {
		ScopedGuard<std::mutex> ANONYMOUS (_self.mNodeMutex) ;
		_CALL_SEH_ ([&] () {
			for (PTR<NODE_A> i = _self.mRoot_a ,ir ; i != NULL ; i = ir) {
				ir = i->mNext ;
				i->~NODE_A () ;
				GlobalHeap::free (i) ;
			}
		}) ;
		_self.mLength_a = 0 ;
		_self.mRoot_a = NULL ;
		_CALL_SEH_ ([&] () {
			for (PTR<NODE_B> i = _self.mRoot_b ,ir ; i != NULL ; i = ir) {
				ir = i->mNext ;
				i->~NODE_B () ;
				GlobalHeap::free (i) ;
			}
		}) ;
		_self.mLength_b = 0 ;
		_self.mRoot_b = NULL ;
	}

	static LENGTH intrusive_attach (Holder &_self) popping {
		return ++_self.mCounter.self ;
	}

	static LENGTH intrusive_detach (Holder &_self) popping {
		return --_self.mCounter.self ;
	}

	static void intrusive_latch (Holder &_self) {
		GlobalRuntime::thread_sleep () ;
	}
} ;

template <FLAG GUID>
class GlobalStatic<ARGC<GUID>> final :private Wrapped<void> {
public:
	static void init (VAR data ,BOOL read_only) {
		auto &r1 = GlobalStatic<void>::unique () ;
		ScopedGuard<std::mutex> ANONYMOUS (r1.mNodeMutex) ;
		const auto r1x = GlobalStatic<void>::static_find_node (r1 ,GUID) ;
		if (r1x != NULL)
			return ;
		const auto r2x = GlobalStatic<void>::static_new_node (r1 ,GUID) ;
		_DYNAMIC_ASSERT_ (r2x != NULL) ;
		r2x->mReadOnly = read_only ;
		r2x->mData = data ;
	}

	static VAR load () popping {
		auto &r1 = GlobalStatic<void>::unique () ;
		ScopedGuard<std::mutex> ANONYMOUS (r1.mNodeMutex) ;
		const auto r1x = GlobalStatic<void>::static_find_node (r1 ,GUID) ;
		_DYNAMIC_ASSERT_ (r1x != NULL) ;
		return r1x->mData ;
	}

	static VAR compare_and_swap (VAR expect ,VAR data) popping {
		auto &r1 = GlobalStatic<void>::unique () ;
		ScopedGuard<std::mutex> ANONYMOUS (r1.mNodeMutex) ;
		const auto r1x = GlobalStatic<void>::static_find_node (r1 ,GUID) ;
		_DYNAMIC_ASSERT_ (r1x != NULL) ;
		_DYNAMIC_ASSERT_ (!r1x->mReadOnly) ;
		if (r1x->mData == expect)
			r1x->mData = data ;
		return r1x->mData ;
	}

	static void save (VAR data) {
		auto &r1 = GlobalStatic<void>::unique () ;
		ScopedGuard<std::mutex> ANONYMOUS (r1.mNodeMutex) ;
		auto rax = GlobalStatic<void>::static_find_node (r1 ,GUID) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (rax != NULL)
				continue ;
			rax = GlobalStatic<void>::static_new_node (r1 ,GUID) ;
			rax->mReadOnly = FALSE ;
		}
		_DYNAMIC_ASSERT_ (rax != NULL) ;
		_DYNAMIC_ASSERT_ (!rax->mReadOnly) ;
		rax->mData = data ;
	}
} ;

template <class TYPE>
class GlobalStatic<Singleton<TYPE>> final :private Wrapped<void> {
private:
	class Holder {
	public:
		using INTRUSIVE_TYPE = GlobalStatic ;

	public:
		friend IntrusiveRef<Holder> ;
		Monostate<std::atomic<LENGTH>> mCounter ;
		Singleton<TYPE> mData ;
	} ;

	using GUID_TYPE = typename GlobalStatic<void>::GUID_TYPE ;

private:
	friend IntrusiveRef<Holder> ;

private:
	static void intrusive_create (Holder &_self) {
		_self.mCounter.self = 0 ;
	}

	static void intrusive_destroy (Holder &_self) {
		_STATIC_WARNING_ ("noop") ;
	}

	static LENGTH intrusive_attach (Holder &_self) popping {
		return ++_self.mCounter.self ;
	}

	static LENGTH intrusive_detach (Holder &_self) popping {
		return --_self.mCounter.self ;
	}

	static void intrusive_latch (Holder &_self) {
		GlobalRuntime::thread_sleep () ;
	}

	static GUID_TYPE guid_from_typeid_name () {
		GUID_TYPE ret ;
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = &_NULL_<BYTE> () + _ADDRESS_ (typeid (TYPE).name ()) ;
		const auto r2x = _MEMCHR_ (PTRTOARR[r1x] ,DEFAULT_HUGEBUFFER_SIZE::value ,BYTE (0X00)) ;
		_DEBUG_ASSERT_ (r2x > 0 && r2x < _SIZEOF_ (GUID_TYPE)) ;
		const auto r3x = _MIN_ (r2x ,_SIZEOF_ (GUID_TYPE)) ;
		_MEMCOPY_ (PTRTOARR[_ZERO_ (ret).unused] ,PTRTOARR[r1x] ,r3x) ;
		return std::move (ret) ;
	}

public:
	static Singleton<TYPE> &unique () popping {
		auto &r1 = _CACHE_ ([] () {
			auto &r2 = GlobalStatic<void>::unique () ;
			ScopedGuard<std::mutex> ANONYMOUS (r2.mNodeMutex) ;
			const auto r2x = guid_from_typeid_name () ;
			auto rax = GlobalStatic<void>::static_find_node (r2 ,r2x) ;
			auto rbx = IntrusiveRef<Holder> () ;
			for (FOR_ONCE_DO_WHILE_FALSE) {
				if (rax != NULL)
					continue ;
				rax = GlobalStatic<void>::static_new_node (r2 ,r2x) ;
				_DYNAMIC_ASSERT_ (rax != NULL) ;
				//@warn: sure 'GlobalHeap' can be used across DLL
				rbx = IntrusiveRef<Holder>::make () ;
				const auto r3x = rbx.watch () ;
				const auto r4x = &_XVALUE_<Holder> (r3x) ;
				rax->mData = &_LOAD_<NONE> (r4x) ;
			}
			const auto r5x = &_LOAD_<Holder> (rax->mData) ;
			return IntrusiveRef<Holder> (r5x).watch () ;
		}) ;
		return _XVALUE_<Holder> (r1).mData ;
	}
} ;

#ifdef __CSC_DEPRECATED__
template <class TYPE>
class Coroutine {
private:
	static constexpr auto STATUS_CREATED = FLAG (0) ;
	static constexpr auto STATUS_RUNNING = FLAG (1) ;
	static constexpr auto STATUS_SUSPEND = FLAG (2) ;
	static constexpr auto STATUS_STOPPED = FLAG (3) ;

private:
	Monostate<FLAG> mCoroutine ;
	Array<Function<DEF<void (Coroutine &)> NONE::*>> mSubProc ;
	Array<ARRAY2<PTR<void>>> mSubBreakPoint ;
	ARRAY2<PTR<void>> mCoBreakPoint ;
	Array<TYPE> mSubContext ;
	Queue<INDEX> mSubQueue ;
	Queue<INDEX> mSubAwaitQueue ;
	INDEX mSubCurr ;
	AnyRef<void> mCoResult ;

public:
	Coroutine () {
		mCoroutine.self = STATUS_CREATED ;
		mSubCurr = VAR_NONE ;
	}

	BOOL ready () const {
		if (mCoroutine.self != STATUS_STOPPED)
			return FALSE ;
		return TRUE ;
	}

	AnyRef<void> poll () popping {
		return std::move (mCoResult) ;
	}

	template <class _ARG1>
	_ARG1 value (const _ARG1 &def) const {
		_STATIC_ASSERT_ (std::is_copy_constructible<_ARG1>::value && std::is_nothrow_move_constructible<_ARG1>::value) ;
		if (!mCoResult.exist ())
			return def ;
		if (mCoResult.type () != _TYPEID_<_ARG1> ())
			return def ;
		return mCoResult.rebind<_ARG1> ().self ;
	}

	void start (Array<Function<DEF<void (Coroutine &)> NONE::*>> &&proc) {
		_DEBUG_ASSERT_ (proc.length () > 0) ;
		mSubProc = std::move (proc) ;
		mSubBreakPoint = Array<ARRAY2<PTR<void>>> (mSubProc.size ()) ;
		const auto r1x = ARRAY2<PTR<void>> {NULL ,NULL} ;
		mSubBreakPoint.fill (r1x) ;
		mSubContext = Array<TYPE> (mSubProc.size ()) ;
		mSubQueue = Queue<INDEX> (mSubProc.length ()) ;
		for (INDEX i = 0 ; i < mSubProc.length () ; i++)
			mSubQueue.add (i) ;
		mSubAwaitQueue = Queue<INDEX> (mSubProc.length ()) ;
		mCoResult = AnyRef<void> () ;
		mSubCurr = VAR_NONE ;
	}

	void stop () {
		mSubProc = Array<Function<DEF<void (Coroutine &)> NONE::*>> () ;
		mSubBreakPoint = Array<ARRAY2<PTR<void>>> () ;
		mSubContext = Array<TYPE> () ;
		mSubQueue = Queue<INDEX> () ;
		mSubAwaitQueue = Queue<INDEX> () ;
		mCoResult = AnyRef<void> () ;
		mSubCurr = VAR_NONE ;
	}

	void execute () {
		_DEBUG_ASSERT_ (mSubCurr == VAR_NONE) ;
		_DEBUG_ASSERT_ (mSubQueue.length () > 0) ;
		mCoroutine.self = STATUS_RUNNING ;
		store_break_point (mCoBreakPoint) ;
		if (mCoroutine.self != STATUS_RUNNING)
			return ;
		mSubQueue.take (mSubCurr) ;
		mSubProc[mSubCurr] (*this) ;
	}

	TYPE &sub_context () & {
		_DEBUG_ASSERT_ (mSubCurr != VAR_NONE) ;
		return mSubContext[mSubCurr] ;
	}

	TYPE &sub_context () && = delete ;

	void sub_await () {
		_DEBUG_ASSERT_ (mSubCurr != VAR_NONE) ;
		mCoroutine.self = STATUS_SUSPEND ;
		store_break_point (mSubBreakPoint[mSubCurr]) ;
		if (mCoroutine.self != STATUS_SUSPEND)
			return ;
		mSubAwaitQueue.add (mSubCurr) ;
		_DYNAMIC_ASSERT_ (mSubQueue.length () > 0) ;
		mSubQueue.take (mSubCurr) ;
		mCoroutine.self = STATUS_RUNNING ;
		goto_break_point (mSubBreakPoint[mSubCurr]) ;
	}

	void sub_resume_one () {
		_DEBUG_ASSERT_ (mSubCurr != VAR_NONE) ;
		if (mSubAwaitQueue.length () == 0)
			return ;
		INDEX ix = VAR_NONE ;
		mSubAwaitQueue.take (ix) ;
		mSubQueue.add (ix) ;
	}

	void sub_resume_all () {
		_DEBUG_ASSERT_ (mSubCurr != VAR_NONE) ;
		mSubQueue.appand (mSubAwaitQueue) ;
		mSubAwaitQueue.clear () ;
	}

	void sub_yield () {
		_DEBUG_ASSERT_ (mSubCurr != VAR_NONE) ;
		if (mSubQueue.length () == 1)
			return ;
		mCoroutine.self = STATUS_SUSPEND ;
		store_break_point (mSubBreakPoint[mSubCurr]) ;
		if (mCoroutine.self != STATUS_SUSPEND)
			return ;
		mSubQueue.add (mSubCurr) ;
		_DYNAMIC_ASSERT_ (mSubQueue.length () > 0) ;
		mSubQueue.take (mSubCurr) ;
		mCoroutine.self = STATUS_RUNNING ;
		goto_break_point (mSubBreakPoint[mSubCurr]) ;
	}

	void sub_return () {
		_DEBUG_ASSERT_ (mSubCurr != VAR_NONE) ;
		mSubQueue.clear () ;
		mSubAwaitQueue.clear () ;
		mSubCurr = VAR_NONE ;
		mCoroutine.self = STATUS_STOPPED ;
		goto_break_point (mCoBreakPoint) ;
	}

	template <class _ARG1>
	void sub_return (_ARG1 &&result) {
		_DEBUG_ASSERT_ (mSubCurr != VAR_NONE) ;
		mCoResult = AnyRef<_ARG1>::make (std::forward<_ARG1> (result)) ;
		sub_return () ;
	}

private:
	void store_break_point (ARRAY2<PTR<void>> &bp) noexcept {
		_STATIC_WARNING_ ("unimplemented") ;
		_DEBUG_ASSERT_ (FALSE) ;
	}

	void goto_break_point (ARRAY2<PTR<void>> &bp) noexcept {
		_STATIC_WARNING_ ("unimplemented") ;
		_DEBUG_ASSERT_ (FALSE) ;
	}
} ;
#endif

class RandomService final :private Interface {
private:
	exports struct Abstract :public Interface {
		virtual VAL entropy () const = 0 ;
		virtual void reset_seed (VAR _seed) = 0 ;
		virtual VAR random_value () popping = 0 ;
		virtual void random_skip (LENGTH len) = 0 ;
	} ;

private:
	class Implement ;
	friend Singleton<RandomService> ;
	Monostate<std::recursive_mutex> mMutex ;
	StrongRef<Abstract> mThis ;

public:
	VAL entropy () const {
		ScopedGuard<std::recursive_mutex> ANONYMOUS (mMutex) ;
		return mThis->entropy () ;
	}

	void reset_seed (VAR _seed) {
		ScopedGuard<std::recursive_mutex> ANONYMOUS (mMutex) ;
		mThis->reset_seed (_seed) ;
	}

	VAR random_value (VAR _min ,VAR _max) popping {
		ScopedGuard<std::recursive_mutex> ANONYMOUS (mMutex) ;
		_DEBUG_ASSERT_ (_min >= 0 && _min <= _max) ;
		const auto r1x = mThis->random_value () ;
		return r1x % (_max - _min + 1) + _min ;
	}

	Array<VAR> random_value (VAR _min ,VAR _max ,LENGTH len) popping {
		ScopedGuard<std::recursive_mutex> ANONYMOUS (mMutex) ;
		Array<VAR> ret = Array<VAR> (len) ;
		const auto r1x = _max - _min + 1 ;
		for (INDEX i = 0 ; i < ret.length () ; i++) {
			const auto r2x = mThis->random_value () ;
			ret[i] = r2x % r1x + _min ;
		}
		return std::move (ret) ;
	}

	BitSet<> random_shuffle (LENGTH count ,LENGTH range) popping {
		return random_shuffle (count ,range ,BitSet<> (range)) ;
	}

	BitSet<> random_shuffle (LENGTH count ,LENGTH range ,BitSet<> &&res) popping {
		_DEBUG_ASSERT_ (count >= 0 && count < range) ;
		_DEBUG_ASSERT_ (res.size () == range) ;
		BitSet<> ret = std::move (res) ;
		ret.clear () ;
		while (TRUE) {
			if (ret.length () >= count)
				break ;
			INDEX ix = random_value (0 ,(range - 1)) ;
			ret[ix] = TRUE ;
		}
		return std::move (ret) ;
	}

	BitSet<> random_shuffle (LENGTH count ,const BitSet<> &range) popping {
		return random_shuffle (count ,range ,BitSet<> (range.size ())) ;
	}

	BitSet<> random_shuffle (LENGTH count ,const BitSet<> &range ,BitSet<> &&res) popping {
		_DEBUG_ASSERT_ (count >= 0 && count < range.size ()) ;
		_DEBUG_ASSERT_ (res.size () == range.size ()) ;
		BitSet<> ret = std::move (res) ;
		ret.clear () ;
		while (TRUE) {
			if (ret.length () >= count)
				break ;
			INDEX ix = random_value (0 ,(range.size () - 1)) ;
			ret[ix] = range[ix] ;
		}
		return std::move (ret) ;
	}

	String<STR> random_uuid () popping {
		String<STR> ret = String<STR> (_COUNTOF_ (decltype (_PCSTR_ ("00000000-0000-0000-000000000000")))) ;
		INDEX iw = 0 ;
		const auto r5x = random_value (0 ,36 ,28) ;
		for (INDEX i = 0 ; i < 8 ; i++) {
			INDEX ix = 0 + i ;
			const auto r1x = (r5x[ix] < 10) ? (STRU8 ('0')) : (STRU8 ('A') - 10) ;
			ret[iw++] = STRU8 (r1x + r5x[ix]) ;
		}
		ret[iw++] = STRU8 ('-') ;
		for (INDEX i = 0 ; i < 4 ; i++) {
			INDEX ix = 8 + i ;
			const auto r2x = (r5x[ix] < 10) ? (STRU8 ('0')) : (STRU8 ('A') - 10) ;
			ret[iw++] = STRU8 (r2x + r5x[ix]) ;
		}
		ret[iw++] = STRU8 ('-') ;
		for (INDEX i = 0 ; i < 4 ; i++) {
			INDEX ix = 12 + i ;
			const auto r3x = (r5x[ix] < 10) ? (STRU8 ('0')) : (STRU8 ('A') - 10) ;
			ret[iw++] = STRU8 (r3x + r5x[ix]) ;
		}
		ret[iw++] = STRU8 ('-') ;
		for (INDEX i = 0 ; i < 12 ; i++) {
			INDEX ix = 16 + i ;
			const auto r4x = (r5x[ix] < 10) ? (STRU8 ('0')) : (STRU8 ('A') - 10) ;
			ret[iw++] = STRU8 (r4x + r5x[ix]) ;
		}
		if (iw < ret.size ())
			ret[iw] = 0 ;
		return std::move (ret) ;
	}

	void random_skip (LENGTH len) {
		ScopedGuard<std::recursive_mutex> ANONYMOUS (mMutex) ;
		return mThis->random_skip (len) ;
	}

private:
	RandomService () ;
} ;
} ;