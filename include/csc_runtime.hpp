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
	struct VALUE_NODE {
		FLAG mGUID ;
		BOOL mReadOnly ;
		VAR mData ;
	} ;

	using GUID_TYPE = PACK<BYTE[256]> ;

	struct CLASS_NODE {
		GUID_TYPE mGUID ;
		PTR<NONE> mData ;
	} ;

	class Detail ;

	class Holder {
	public:
		using INTRUSIVE_TYPE = typename GlobalStatic::Detail ;

	private:
		template <class>
		friend class GlobalStatic ;
		friend IntrusiveRef<Holder> ;
		Monostate<std::atomic<LENGTH>> mCounter ;
		Monostate<std::mutex> mNodeMutex ;
		LinkedRef<VALUE_NODE> mValueNode ;
		LinkedRef<CLASS_NODE> mClassNode ;
	} ;

private:
	class Detail ;
	template <class>
	friend class GlobalStatic ;
	friend IntrusiveRef<Holder> ;

private:
	static Holder &static_unique () popping {
		return _CACHE_ ([] () {
			_STATIC_WARNING_ ("mark") ;
			auto rax = unique_atomic_address (NULL ,NULL) ;
			auto rbx = IntrusiveRef<Holder> () ;
			for (FOR_ONCE_DO) {
				if (rax != NULL)
					discard ;
				//@warn: sure 'GlobalHeap' can be used across DLL
				rbx = IntrusiveRef<Holder>::make () ;
				const auto r1x = rbx.watch () ;
				const auto r2x = &_XVALUE_<Holder> (r1x) ;
				const auto r3x = &_LOAD_<NONE> (r2x) ;
				rax = unique_atomic_address (NULL ,r3x) ;
			}
			_DYNAMIC_ASSERT_ (rax != NULL) ;
			const auto r4x = &_LOAD_<Holder> (rax) ;
			return IntrusiveRef<Holder> (r4x).watch () ;
		}) ;
	}

	static PTR<VALUE_NODE> static_new_node (Holder &_self ,FLAG guid) popping {
		_self.mValueNode.push () ;
		_self.mValueNode->mGUID = guid ;
		return &_self.mValueNode.self ;
	}

	static PTR<CLASS_NODE> static_new_node (Holder &_self ,const GUID_TYPE &guid) popping {
		_self.mClassNode.push () ;
		_self.mClassNode->mGUID = guid ;
		return &_self.mClassNode.self ;
	}

	static PTR<VALUE_NODE> static_find_node (Holder &_self ,FLAG guid) popping {
		PTR<VALUE_NODE> ret = NULL ;
		for (FOR_ONCE_DO) {
			if (!_self.mValueNode.exist ())
				discard ;
			const auto r1x = &_self.mValueNode.self ;
			while (TRUE) {
				if (ret != NULL)
					break ;
				if (_self.mValueNode->mGUID == guid)
					ret = &_self.mValueNode.self ;
				_self.mValueNode.cycle () ;
				if (&_self.mValueNode.self == r1x)
					break ;
				_STATIC_WARNING_ ("noop") ;
			}
		}
		return std::move (ret) ;
	}

	static PTR<CLASS_NODE> static_find_node (Holder &_self ,const GUID_TYPE &guid) popping {
		PTR<CLASS_NODE> ret = NULL ;
		for (FOR_ONCE_DO) {
			if (!_self.mClassNode.exist ())
				discard ;
			const auto r1x = &_self.mClassNode.self ;
			while (TRUE) {
				if (ret != NULL)
					break ;
				if (_MEMEQUAL_ (PTRTOARR[_self.mClassNode->mGUID.P1] ,PTRTOARR[guid.P1] ,_COUNTOF_ (decltype (guid.P1))))
					ret = &_self.mClassNode.self ;
				_self.mClassNode.cycle () ;
				if (&_self.mClassNode.self == r1x)
					break ;
				_STATIC_WARNING_ ("noop") ;
			}
		}
		return std::move (ret) ;
	}

public:
	//@warn: this function should be implemented in a 'runtime.dll'
	static DEF<PTR<NONE> (PTR<NONE> ,PTR<NONE>) popping> unique_atomic_address ;

private:
	class Detail :private Wrapped<void> {
	public:
		inline static void friend_create (Holder &_self) {
			ScopedGuard<std::mutex> ANONYMOUS (_self.mNodeMutex) ;
			_self.mCounter.self = 0 ;
			_self.mValueNode = LinkedRef<VALUE_NODE> () ;
			_self.mClassNode = LinkedRef<CLASS_NODE> () ;
		}

		inline static void friend_destroy (Holder &_self) {
			ScopedGuard<std::mutex> ANONYMOUS (_self.mNodeMutex) ;
			_self.mValueNode = LinkedRef<VALUE_NODE> () ;
			_self.mClassNode = LinkedRef<CLASS_NODE> () ;
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

template <FLAG GUID>
class GlobalStatic<ARGC<GUID>> final :private Wrapped<void> {
public:
	static void init (VAR data ,BOOL read_only) {
		auto &r1y = GlobalStatic<void>::static_unique () ;
		ScopedGuard<std::mutex> ANONYMOUS (r1y.mNodeMutex) ;
		const auto r2x = GlobalStatic<void>::static_find_node (r1y ,GUID) ;
		if (r2x != NULL)
			return ;
		const auto r3x = GlobalStatic<void>::static_new_node (r1y ,GUID) ;
		_DYNAMIC_ASSERT_ (r3x != NULL) ;
		r3x->mReadOnly = read_only ;
		r3x->mData = data ;
	}

	static VAR load () popping {
		auto &r1y = GlobalStatic<void>::static_unique () ;
		ScopedGuard<std::mutex> ANONYMOUS (r1y.mNodeMutex) ;
		const auto r2x = GlobalStatic<void>::static_find_node (r1y ,GUID) ;
		_DYNAMIC_ASSERT_ (r2x != NULL) ;
		return r2x->mData ;
	}

	static VAR compare_and_swap (VAR expect ,VAR data) popping {
		auto &r1y = GlobalStatic<void>::static_unique () ;
		ScopedGuard<std::mutex> ANONYMOUS (r1y.mNodeMutex) ;
		const auto r2x = GlobalStatic<void>::static_find_node (r1y ,GUID) ;
		_DYNAMIC_ASSERT_ (r2x != NULL) ;
		_DYNAMIC_ASSERT_ (!r2x->mReadOnly) ;
		if (r2x->mData == expect)
			r2x->mData = data ;
		return r2x->mData ;
	}

	static void save (VAR data) {
		auto &r1y = GlobalStatic<void>::static_unique () ;
		ScopedGuard<std::mutex> ANONYMOUS (r1y.mNodeMutex) ;
		auto rax = GlobalStatic<void>::static_find_node (r1y ,GUID) ;
		for (FOR_ONCE_DO) {
			if (rax != NULL)
				discard ;
			rax = GlobalStatic<void>::static_new_node (r1y ,GUID) ;
			rax->mReadOnly = FALSE ;
		}
		_DYNAMIC_ASSERT_ (rax != NULL) ;
		_DYNAMIC_ASSERT_ (!rax->mReadOnly) ;
		rax->mData = data ;
	}
} ;

template <class UNIT>
class GlobalStatic<Singleton<UNIT>> final :private Wrapped<void> {
private:
	class Detail ;

	class Holder {
	public:
		using INTRUSIVE_TYPE = typename GlobalStatic::Detail ;

	public:
		friend IntrusiveRef<Holder> ;
		Monostate<std::atomic<LENGTH>> mCounter ;
		Singleton<UNIT> mData ;
	} ;

	using GUID_TYPE = typename GlobalStatic<void>::GUID_TYPE ;

private:
	class Detail ;
	friend IntrusiveRef<Holder> ;

public:
	static Singleton<UNIT> &unique () popping {
		auto &r1y = _CACHE_ ([] () {
			auto &r2y = GlobalStatic<void>::static_unique () ;
			ScopedGuard<std::mutex> ANONYMOUS (r2y.mNodeMutex) ;
			const auto r3x = Detail::guid_from_typeid_name () ;
			auto rax = GlobalStatic<void>::static_find_node (r2y ,r3x) ;
			auto rbx = IntrusiveRef<Holder> () ;
			for (FOR_ONCE_DO) {
				if (rax != NULL)
					discard ;
				rax = GlobalStatic<void>::static_new_node (r2y ,r3x) ;
				_DYNAMIC_ASSERT_ (rax != NULL) ;
				//@warn: sure 'GlobalHeap' can be used across DLL
				rbx = IntrusiveRef<Holder>::make () ;
				const auto r4x = rbx.watch () ;
				const auto r5x = &_XVALUE_<Holder> (r4x) ;
				rax->mData = &_LOAD_<NONE> (r5x) ;
			}
			const auto r6x = &_LOAD_<Holder> (rax->mData) ;
			return IntrusiveRef<Holder> (r6x).watch () ;
		}) ;
		return _XVALUE_<Holder> (r1y).mData ;
	}

private:
	class Detail :private Wrapped<void> {
	public:
		inline static void friend_create (Holder &_self) {
			_self.mCounter.self = 0 ;
		}

		inline static void friend_destroy (Holder &_self) {
			_STATIC_WARNING_ ("noop") ;
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

		inline static GUID_TYPE guid_from_typeid_name () {
			DEF<BYTE[_SIZEOF_ (GUID_TYPE)]> ret ;
			_ZERO_ (ret) ;
			_STATIC_WARNING_ ("mark") ;
			const auto r1x = String<STRA> (PTRTOARR[typeid (UNIT).name ()]) ;
			auto &r2y = _LOAD_<ARR<BYTE>> (&PTRTOARR[&r1x[0]]) ;
			_DEBUG_ASSERT_ (r1x.size () > 0 && r1x.size () <= _SIZEOF_ (GUID_TYPE)) ;
			const auto r3x = _MIN_ (r1x.size () ,_SIZEOF_ (GUID_TYPE)) * _SIZEOF_ (STRA) ;
			_MEMCOPY_ (PTRTOARR[ret] ,r2y ,r3x) ;
			return _BITWISE_CAST_<GUID_TYPE> (ret) ;
		}
	} ;
} ;

#ifdef __CSC_DEPRECATED__
template <class UNIT>
class Coroutine {
public:
	class SubRef ;

private:
	static constexpr auto STATUS_CREATED = FLAG (0) ;
	static constexpr auto STATUS_RUNNING = FLAG (1) ;
	static constexpr auto STATUS_SUSPEND = FLAG (2) ;
	static constexpr auto STATUS_STOPPED = FLAG (3) ;

private:
	class Implement ;
	Monostate<FLAG> mStatus ;
	AutoRef<UNIT> mContext ;
	AnyRef<void> mBreakPoint ;
	Array<Function<DEF<void (SubRef &)> NONE::*>> mSubProc ;
	Array<AnyRef<void>> mSubBreakPoint ;
	Deque<INDEX> mSubQueue ;
	Priority<VAR ,INDEX> mSubAwaitQueue ;
	INDEX mSubCurr ;

public:
	Coroutine () {
		mStatus.self = STATUS_CREATED ;
		mSubCurr = VAR_NONE ;
	}

	BOOL ready () const {
		if (mStatus.self != STATUS_STOPPED)
			return FALSE ;
		return TRUE ;
	}

	UNIT &context () & {
		_DEBUG_ASSERT_ (mContext.exist ()) ;
		return mContext ;
	}

	UNIT &context () && = delete ;

	void start (Array<Function<DEF<void (SubRef &)> NONE::*>> &&proc) {
		_DEBUG_ASSERT_ (proc.length () > 0) ;
		mContext = AutoRef<UNIT>::make () ;
		mBreakPoint = AnyRef<void> () ;
		mSubProc = std::move (proc) ;
		mSubBreakPoint = Array<AnyRef<void>> (mSubProc.size ()) ;
		mSubQueue = Deque<INDEX> (mSubProc.length ()) ;
		for (INDEX i = 0 ,ie = mSubProc.length () ; i < ie ; i++)
			mSubQueue.add (i) ;
		mSubAwaitQueue = Priority<VAR ,INDEX> (mSubProc.length ()) ;
		mSubQueue.take (mSubCurr) ;
	}

	void execute () {
		_DEBUG_ASSERT_ (!mBreakPoint.exist ()) ;
		init_break_point (mBreakPoint) ;
		for (auto &&i : mSubBreakPoint) {
			_DEBUG_ASSERT_ (!i.exist ()) ;
			init_break_point (i) ;
		}
		mStatus.self = STATUS_CREATED ;
		store_break_point (mBreakPoint) ;
		for (auto &&i : mSubBreakPoint) {
			if (mStatus.self != STATUS_STOPPED)
				continue ;
			if (!i.exist ())
				continue ;
			goto_break_point (i) ;
		}
		if (mStatus.self != STATUS_CREATED)
			return ;
		for (auto &&i : mSubBreakPoint) {
			if (mStatus.self != STATUS_CREATED)
				continue ;
			store_break_point (i) ;
		}
		_DEBUG_ASSERT_ (mSubCurr != VAR_NONE) ;
		const auto r1x = mSubCurr ;
		_CALL_TRY_ ([&] () {
			if (mStatus.self == STATUS_STOPPED)
				return ;
			mStatus.self = STATUS_RUNNING ;
			mSubProc[r1x] (_CAST_<SubRef> ((*this))) ;
		} ,[&] () {
			_STATIC_WARNING_ ("noop") ;
		}) ;
		mSubBreakPoint[r1x] = AnyRef<void> () ;
		mStatus.self = STATUS_STOPPED ;
		goto_break_point (mBreakPoint) ;
	}

private:
	void init_break_point (AnyRef<void> &bp) popping ;

	void store_break_point (AnyRef<void> &bp) noexcept popping ;

	void goto_break_point (AnyRef<void> &bp) noexcept popping ;

public:
	static void csync (Array<Function<DEF<void (SubRef &)> NONE::*>> &&proc) ;
} ;

template <class UNIT>
class Coroutine<UNIT>::SubRef :private Wrapped<Coroutine<UNIT>> {
private:
	using Wrapped<Coroutine<UNIT>>::mSelf ;

public:
	UNIT &to () {
		_DEBUG_ASSERT_ (mSelf.mContext.exist ()) ;
		return mSelf.mContext ;
	}

	inline implicit operator UNIT & () {
		return to () ;
	}

	inline PTR<UNIT> operator-> () {
		return &to () ;
	}

	const UNIT &to () const {
		_DEBUG_ASSERT_ (mSelf.mContext.exist ()) ;
		return mSelf.mContext ;
	}

	inline implicit operator const UNIT & () const {
		return to () ;
	}

	inline PTR<const UNIT> operator-> () const {
		return &to () ;
	}

	void sub_await () {
		sub_await (mSelf.mSubAwaitQueue.length ()) ;
	}

	void sub_await (VAR priority) {
		_DEBUG_ASSERT_ (priority >= 0) ;
		_DEBUG_ASSERT_ (mSelf.mSubCurr != VAR_NONE) ;
		_DYNAMIC_ASSERT_ (mSelf.mStatus.self == STATUS_RUNNING) ;
		mSelf.mStatus.self = STATUS_SUSPEND ;
		store_break_point (mSelf.mSubBreakPoint[mSelf.mSubCurr]) ;
		_DYNAMIC_ASSERT_ (mSelf.mStatus.self != STATUS_STOPPED) ;
		if (mSelf.mStatus.self != STATUS_SUSPEND)
			return ;
		mSelf.mSubAwaitQueue.add (priority ,mSelf.mSubCurr) ;
		_DYNAMIC_ASSERT_ (!mSelf.mSubQueue.empty ()) ;
		mSelf.mSubQueue.take (mSelf.mSubCurr) ;
		mSelf.mStatus.self = STATUS_RUNNING ;
		goto_break_point (mSelf.mSubBreakPoint[mSelf.mSubCurr]) ;
	}

	void sub_resume () {
		sub_resume (mSelf.mSubAwaitQueue.length ()) ;
	}

	void sub_resume (LENGTH count) {
		for (INDEX i = 0 ,ie = count ; i < ie ; i++) {
			if (mSelf.mSubAwaitQueue.empty ())
				continue ;
			const auto r1x = mSelf.mSubAwaitQueue[mSelf.mSubAwaitQueue.head ()].item ;
			mSelf.mSubAwaitQueue.take () ;
			mSelf.mSubQueue.add (r1x) ;
		}
	}

	void sub_yield () {
		_DEBUG_ASSERT_ (mSelf.mSubCurr != VAR_NONE) ;
		if (mSelf.mSubQueue.empty ())
			return ;
		_DYNAMIC_ASSERT_ (mSelf.mStatus.self == STATUS_RUNNING) ;
		mSelf.mStatus.self = STATUS_SUSPEND ;
		store_break_point (mSelf.mSubBreakPoint[mSelf.mSubCurr]) ;
		_DYNAMIC_ASSERT_ (mSelf.mStatus.self != STATUS_STOPPED) ;
		if (mSelf.mStatus.self != STATUS_SUSPEND)
			return ;
		mSelf.mSubQueue.add (mSelf.mSubCurr) ;
		_DYNAMIC_ASSERT_ (!mSelf.mSubQueue.empty ()) ;
		mSelf.mSubQueue.take (mSelf.mSubCurr) ;
		mSelf.mStatus.self = STATUS_RUNNING ;
		goto_break_point (mSelf.mSubBreakPoint[mSelf.mSubCurr]) ;
	}

	void sub_return () {
		_DEBUG_ASSERT_ (mSubCurr != VAR_NONE) ;
		_DYNAMIC_ASSERT_ (mSelf.mStatus.self == STATUS_RUNNING) ;
		mSelf.mSubQueue.clear () ;
		mSelf.mSubAwaitQueue.clear () ;
		mSelf.mSubCurr = VAR_NONE ;
		mSelf.mStatus.self = STATUS_STOPPED ;
		goto_break_point (mSelf.mBreakPoint) ;
	}
} ;

template <class UNIT>
inline void Coroutine<UNIT>::csync (Array<Function<DEF<void (SubRef &)> NONE::*>> &&proc) {
	auto rax = Coroutine<UNIT> (std::move (proc)) ;
	rax.execute () ;
}
#endif

class RandomService final :private Interface {
private:
	exports struct Abstract :public Interface {
		virtual VAR entropy () const = 0 ;
		virtual void reset_seed (VAR _seed) = 0 ;
		virtual VAR random_value () popping = 0 ;
		virtual void random_skip (LENGTH len) = 0 ;
	} ;

private:
	class Detail ;
	class Implement ;
	friend Singleton<RandomService> ;
	Monostate<std::recursive_mutex> mMutex ;
	StrongRef<Abstract> mThis ;

public:
	VAR entropy () const {
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
		for (INDEX i = 0 ,ie = ret.length () ; i < ie ; i++) {
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
		BitSet<> ret = BitSet<> (range.size ()) ;
		compute_random_shuffle (count ,range ,ret) ;
		return std::move (ret) ;
	}

	void compute_random_shuffle (LENGTH count ,const BitSet<> &range ,BitSet<> &chosen) popping {
		_DEBUG_ASSERT_ (count >= 0 && count < range.size ()) ;
		_DEBUG_ASSERT_ (chosen.size () == range.size ()) ;
		chosen.clear () ;
		while (TRUE) {
			if (chosen.length () >= count)
				break ;
			INDEX ix = random_value (0 ,(range.size () - 1)) ;
			chosen[ix] = range[ix] ;
		}
	}

	String<STR> random_uuid () popping {
		static constexpr auto M_UUID = _PCSTR_ ("00000000-0000-0000-000000000000") ;
		String<STR> ret = String<STR> (M_UUID.size ()) ;
		INDEX iw = 0 ;
		const auto r1x = random_value (0 ,36 ,28) ;
		for (INDEX i = 0 ,ie = 8 ; i < ie ; i++) {
			INDEX ix = 0 + i ;
			ret[iw++] = Detail::index_to_hex_str (r1x[ix]) ;
		}
		ret[iw++] = STRU8 ('-') ;
		for (INDEX i = 0 ,ie = 4 ; i < ie ; i++) {
			INDEX ix = 8 + i ;
			ret[iw++] = Detail::index_to_hex_str (r1x[ix]) ;
		}
		ret[iw++] = STRU8 ('-') ;
		for (INDEX i = 0 ,ie = 4 ; i < ie ; i++) {
			INDEX ix = 12 + i ;
			ret[iw++] = Detail::index_to_hex_str (r1x[ix]) ;
		}
		ret[iw++] = STRU8 ('-') ;
		for (INDEX i = 0 ,ie = 12 ; i < ie ; i++) {
			INDEX ix = 16 + i ;
			ret[iw++] = Detail::index_to_hex_str (r1x[ix]) ;
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

private:
	class Detail :private Wrapped<void> {
	public:
		inline static STRU8 index_to_hex_str (INDEX index) {
			const auto r1x = _SWITCH_ (
				(index < 10) ? (STRU8 ('0')) :
				(STRU8 ('A') - 10)) ;
			return STRU8 (r1x + index) ;
		}
	} ;
} ;
} ;