#pragma once

#include "csc_core.hpp"

namespace CSC {
namespace U {
struct AUTO_HELP<>::EXTERN::BLOCK {
	VAR32 mBlockCheck1 ;
	VAR32 mSlot ;
	VAR32 mBlockCheck2 ;
} ;

struct AUTO_HELP<>::EXTERN::SLOT {
	VAR32 mUsed ;
	VAR32 mBlockSize ;
	VAR32 mBlock ;
} ;

class AUTO_HELP<>::EXTERN::AutoHeap {
public:
	template <class ARG1>
	static PTR<REMOVE_ALL<ARG1>> alloc (CREF<ARG1> id) {
		using R1X = typeof (id) ;
		require (IS_TRIVIAL<R1X>) ;
		const auto r1x = alloc (SIZEOF<R1X>::value ,ALIGNOF<R1X>::value) ;
		const auto r2x = address (block_array ()[slot_array ()[r1x].mBlock]) + SIZEOF<BLOCK>::value ;
		const auto r3x = alignto (r2x ,ALIGNOF<R1X>::value) ;
		barrier () ;
		return reinterpret_cast<PTR<R1X>> (r3x) ;
	}

	static INDEX alloc (CREF<LENGTH> size_len ,CREF<LENGTH> align_len) {
		assert (size_len > ZERO) ;
		assert (align_len > ZERO) ;
		const auto r1x = align_len - ALIGNOF<BLOCK>::value ;
		const auto r2x = size_len + max (r1x ,ZERO) ;
		INDEX ret = 0 ;
		assert (slot_array ()[ret].mBlockSize >= SIZEOF<BLOCK>::value + r2x) ;
		INDEX jx = slot_array ()[ret].mBlock ;
		block_array ()[jx].mBlockCheck1 = VAR32 (0XCCCCCCCC) ;
		block_array ()[jx].mBlockCheck2 = VAR32 (0XCCCCCCCC) ;
		INDEX ix = ret + 1 ;
		slot_array ()[ix].mUsed = 0 ;
		slot_array ()[ix].mBlockSize = 0 ;
		slot_array ()[ix].mBlock = 0 ;
		return forward (ret) ;
	}

	static void free (CREF<LENGTH> addr) {
		const auto r1x = slot_array ()[0] ;
		assert (r1x.mBlockCheck1 == VAR32 (0XCCCCCCCC)) ;
		assert (r1x.mBlockCheck2 == VAR32 (0XCCCCCCCC)) ;

	}

private:
	static VREF<BLOCK[]> block_array () {

	}

	static VREF<SLOT[]> slot_array () {

	}

	static VAR32 root () {
		thread_local auto M_STORAGE = TEMP<BYTE[4096]> () ;
		auto &&r1x = capture ([&] () {
			const auto r2x = address (M_STORAGE) ;
			PTR<BLOCK> ret = reinterpret_cast<PTR<BLOCK>> (r2x) ;
			ret->mPrev = NONE ;
			ret->mNext = NONE ;
			ret->mBlockSize = VAR32 (SIZEOF<typeof (M_STORAGE)>::value) ;
			ret->mBlockCheck1 = VAR32 (0XCCCCCCCC) ;
			ret->mBlockCheck2 = VAR32 (0XCCCCCCCC) ;
			return forward (ret) ;
		}) ;
		thread_local auto M_ROOT = r1x.self () ;
		return M_ROOT ;
	}
} ;

template <class UNIT1>
class AUTO_IMPLHOLDER_HELP<UNIT1>::ImplHolder :
	public Holder {
private:
	using AutoHeap = typename EXTERN::AutoHeap ;

private:
	UNIT1 mValue ;

public:
	implicit ImplHolder () = delete ;

	explicit ImplHolder (RREF<UNIT1> that) :
		delegate mValue (forward (that)) {}

	void inl_destroy () const override {
		auto &&thiz = property[this] ;
		CSC::inl_destroy (unsafe_deptr[thiz]) ;
		AutoHeap::free (address (thiz)) ;
		barrier () ;
	}

	LENGTH type_size () const override {
		return SIZEOF<ImplHolder>::value ;
	}

	LENGTH type_align () const override {
		return ALIGNOF<ImplHolder>::value ;
	}

	FLAG type_mid () const override {
		return CSC::type_mid (typeas<ImplHolder>::id) ;
	}

	UNIT1 poll () {
		return forward (mValue) ;
	}
} ;
} ;

namespace U {
template <class UNIT1 ,class UNTI2>
class BOX_IMPLHOLDER_HELP<UNIT1 ,UNTI2>::ImplHolder :
	public Holder {
private:
	UNTI2 mValue ;

public:
	implicit ImplHolder () = delete ;

	explicit ImplHolder (RREF<UNTI2> that) :
		delegate mValue (forward (that)) {}

	void inl_destroy () const override {
		auto &&thiz = property[this] ;
		delete property (thiz) ;
	}

	VREF<UNIT1> to () leftvalue override {
		return mValue ;
	}

	CREF<UNIT1> to () const leftvalue override {
		return mValue ;
	}
} ;
} ;

namespace U {
template <class UNIT1>
class RC_IMPLHOLDER_HELP<UNIT1>::ImplHolder :
	public Holder {
private:
	UNIT1 mValue ;
	LENGTH mCounter ;

public:
	implicit ImplHolder () = delete ;

	explicit ImplHolder (RREF<UNIT1> that) :
		delegate mValue (forward (that)) ,mCounter (ZERO) {}

	void inl_destroy () const override {
		auto &&thiz = property[this] ;
		delete property (thiz) ;
	}

	CREF<UNIT1> to () const leftvalue override {
		return mValue ;
	}

	LENGTH increase () override {
		return ++mCounter ;
	}

	LENGTH decrease () override {
		return --mCounter ;
	}
} ;
} ;
} ;