#pragma once

#ifndef __CSC_RUNTIME__
#define __CSC_RUNTIME__
#endif

#include "csc.hpp"
#include "csc_ext.hpp"
#include "csc_array.hpp"

namespace CSC {
class GlobalRuntime :private Wrapped<void> {
public:
	inline static std::chrono::system_clock::time_point clock_now () {
		return std::chrono::system_clock::now () ;
	}

	inline static std::thread::id thread_id () {
		return std::this_thread::get_id () ;
	}

	template <class... _ARGS>
	inline static void thread_sleep (const std::chrono::duration<_ARGS...> &_time) {
		std::this_thread::sleep_for (_time) ;
	}

	template <class... _ARGS>
	inline static void thread_sleep (const std::chrono::time_point<_ARGS...> &_time) {
		std::this_thread::sleep_for (_time) ;
	}

	inline static void thread_sleep () {
		std::this_thread::yield () ;
	}

	inline static LENGTH thread_concurrency () {
		return LENGTH (std::thread::hardware_concurrency ()) ;
	}

	template <LENGTH _VAL1>
	inline static void locale_init (const DEF<STRA[_VAL1]> &_locale) {
		std::setlocale (LC_ALL ,_locale) ;
	}

	inline static void process_exit () {
		std::exit (-1) ;
	}

	inline static void process_abort () {
		std::abort () ;
	}
} ;

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

	class Pack {
	public:
		using INTRUSIVE_TYPE = GlobalStatic ;

	private:
		template <class>
		friend class GlobalStatic ;
		friend IntrusiveRef<Pack> ;
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
	friend IntrusiveRef<Pack> ;

private:
	//@warn: this function should be implemented in 'routime.dll'
	inline static DEF<PTR<NONE> (PTR<NONE> ,PTR<NONE>) popping> unique_atomic_address ;

	inline static Pack &unique () popping {
		return _CACHE_ ([] () {
			auto rax = unique_atomic_address (NULL ,NULL) ;
			auto rbx = IntrusiveRef<Pack> () ;
			for (FOR_ONCE_DO_WHILE_FALSE) {
				if (rax != NULL)
					continue ;
				//@warn: sure 'GlobalHeap' can be used across DLL
				rbx = IntrusiveRef<Pack>::make () ;
				const auto r2x = rbx.watch () ;
				const auto r3x = &_XVALUE_<Pack> (r2x) ;
				const auto r4x = &_LOAD_<NONE> (r3x) ;
				rax = unique_atomic_address (NULL ,r4x) ;
			}
			_DYNAMIC_ASSERT_ (rax != NULL) ;
			const auto r5x = &_LOAD_<Pack> (rax) ;
			return IntrusiveRef<Pack> (r5x).watch () ;
		}) ;
	}

	inline static PTR<NODE_A> static_new_node (Pack &_self ,FLAG guid) popping {
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

	inline static PTR<NODE_B> static_new_node (Pack &_self ,const GUID_TYPE &guid) popping {
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

	inline static PTR<NODE_A> static_find_node (const Pack &_self ,FLAG guid) {
		for (PTR<NODE_A> i = _self.mRoot_a ; i != NULL ; i = i->mNext)
			if (i->mGUID == guid)
				return i ;
		return NULL ;
	}

	inline static PTR<NODE_B> static_find_node (const Pack &_self ,const GUID_TYPE &guid) {
		for (PTR<NODE_B> i = _self.mRoot_b ; i != NULL ; i = i->mNext)
			if (_MEMEQUAL_ (i->mGUID.unused ,PTRTOARR[&guid.unused[0]]))
				return i ;
		return NULL ;
	}

	inline static void intrusive_create (Pack &_self) {
		ScopedGuard<std::mutex> ANONYMOUS (_self.mNodeMutex) ;
		_self.mCounter.self = 0 ;
		_self.mLength_a = 0 ;
		_self.mRoot_a = NULL ;
		_self.mLength_b = 0 ;
		_self.mRoot_b = NULL ;
	}

	inline static void intrusive_destroy (Pack &_self) {
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

	inline static LENGTH intrusive_attach (Pack &_self) popping {
		return ++_self.mCounter.self ;
	}

	inline static LENGTH intrusive_detach (Pack &_self) popping {
		return --_self.mCounter.self ;
	}

	inline static void intrusive_latch () {
		GlobalRuntime::thread_sleep () ;
	}
} ;

template <FLAG GUID>
class GlobalStatic<ARGC<GUID>> final :private Wrapped<void> {
public:
	inline static void init (VAR data ,BOOL read_only) {
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

	inline static VAR load () popping {
		auto &r1 = GlobalStatic<void>::unique () ;
		ScopedGuard<std::mutex> ANONYMOUS (r1.mNodeMutex) ;
		const auto r1x = GlobalStatic<void>::static_find_node (r1 ,GUID) ;
		_DYNAMIC_ASSERT_ (r1x != NULL) ;
		return r1x->mData ;
	}

	inline static VAR compare_and_swap (VAR expect ,VAR data) popping {
		auto &r1 = GlobalStatic<void>::unique () ;
		ScopedGuard<std::mutex> ANONYMOUS (r1.mNodeMutex) ;
		const auto r1x = GlobalStatic<void>::static_find_node (r1 ,GUID) ;
		_DYNAMIC_ASSERT_ (r1x != NULL) ;
		_DYNAMIC_ASSERT_ (!r1x->mReadOnly) ;
		if (r1x->mData == expect)
			r1x->mData = data ;
		return r1x->mData ;
	}

	inline static void save (VAR data) {
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
	class Pack {
	public:
		using INTRUSIVE_TYPE = GlobalStatic ;

	public:
		friend IntrusiveRef<Pack> ;
		Monostate<std::atomic<LENGTH>> mCounter ;
		Singleton<TYPE> mData ;
	} ;

	using GUID_TYPE = typename GlobalStatic<void>::GUID_TYPE ;

private:
	friend IntrusiveRef<Pack> ;

private:
	inline static void intrusive_create (Pack &_self) {
		_self.mCounter.self = 0 ;
	}

	inline static void intrusive_destroy (Pack &_self) {
		_STATIC_WARNING_ ("noop") ;
	}

	inline static LENGTH intrusive_attach (Pack &_self) popping {
		return ++_self.mCounter.self ;
	}

	inline static LENGTH intrusive_detach (Pack &_self) popping {
		return --_self.mCounter.self ;
	}

	inline static void intrusive_latch () {
		GlobalRuntime::thread_sleep () ;
	}

	inline static GUID_TYPE guid_from_typeid_name () {
		GUID_TYPE ret ;
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = &_NULL_<BYTE> () + _ADDRESS_ (typeid (TYPE).name ()) ;
		const auto r2x = _MEMCHR_ (PTRTOARR[&r1x[0]] ,DEFAULT_HUGEBUFFER_SIZE::value ,BYTE (0X00)) ;
		_DEBUG_ASSERT_ (r2x > 0 && r2x < _SIZEOF_ (GUID_TYPE)) ;
		const auto r3x = _MIN_ (r2x ,_SIZEOF_ (GUID_TYPE)) ;
		_MEMCOPY_ (PTRTOARR[&_ZERO_ (ret).unused[0]] ,PTRTOARR[&r1x[0]] ,r3x) ;
		return std::move (ret) ;
	}

public:
	inline static Singleton<TYPE> &unique () popping {
		auto &r1 = _CACHE_ ([] () {
			auto &r2 = GlobalStatic<void>::unique () ;
			ScopedGuard<std::mutex> ANONYMOUS (r2.mNodeMutex) ;
			const auto r2x = guid_from_typeid_name () ;
			auto rax = GlobalStatic<void>::static_find_node (r2 ,r2x) ;
			auto rbx = IntrusiveRef<Pack> () ;
			for (FOR_ONCE_DO_WHILE_FALSE) {
				if (rax != NULL)
					continue ;
				rax = GlobalStatic<void>::static_new_node (r2 ,r2x) ;
				_DYNAMIC_ASSERT_ (rax != NULL) ;
				//@warn: sure 'GlobalHeap' can be used across DLL
				rbx = IntrusiveRef<Pack>::make () ;
				const auto r3x = rbx.watch () ;
				const auto r4x = &_XVALUE_<Pack> (r3x) ;
				rax->mData = &_LOAD_<NONE> (r4x) ;
			}
			const auto r5x = &_LOAD_<Pack> (rax->mData) ;
			return IntrusiveRef<Pack> (r5x).watch () ;
		}) ;
		return _XVALUE_<Pack> (r1).mData ;
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
	}

	void goto_break_point (ARRAY2<PTR<void>> &bp) noexcept {
		_STATIC_WARNING_ ("unimplemented") ;
	}
} ;
#endif
} ;