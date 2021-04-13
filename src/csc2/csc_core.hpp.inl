#pragma once

#include "csc_core.hpp"

namespace CSC {
namespace U {
struct ANY_HELP<>::DETAIL::BLOCK {
	FEAT mBlockCheck1 ;
	FEAT mBlockCheck2 ;
} ;

struct ANY_HELP<>::DETAIL::SLOT {
	BOOL mUsed ;
	LENGTH mBlockSize ;
	INDEX mBlock ;
} ;

class ANY_HELP<>::DETAIL::AnyHeap {
private:
	static constexpr auto BLOCK_SIZE = 256 ;
	static constexpr auto SLOT_SIZE = 16 ;
	static constexpr auto BLOCK_CHECK = FEAT (0XCCCCCCCCCCCCCCCC) ;

public:
	template <class ARG1>
	imports auto alloc (CREF<ARG1> id)
		->UNSAFE_PTR<REMOVE_ALL<ARG1>> {
		using R1X = typeof (id) ;
		require (IS_TRIVIAL<R1X>) ;
		const auto r1x = alloc (SIZEOF<R1X>::value ,ALIGNOF<R1X>::value) ;
		const auto r2x = address (block_array ()[slot_array ()[r1x].mBlock]) + SIZEOF<BLOCK>::value ;
		const auto r3x = alignto (r2x ,ALIGNOF<R1X>::value) ;
		barrier () ;
		return reinterpret_cast<UNSAFE_PTR<R1X>> (r3x) ;
	}

	imports auto alloc (CREF<LENGTH> size_len ,CREF<LENGTH> align_len)
		->INDEX {
		assert (size_len > ZERO) ;
		assert (align_len > ZERO) ;
		const auto r3x = property (slot_array ()) ;
		const auto r4x = property (block_array ()) ;
		auto &&r5x = capture ([&] () {
			for (auto &&i : range (0 ,SLOT_SIZE)) {
				if (property[r3x][i].mUsed)
					return i ;
			}
			return NONE ;
		}) ;
		INDEX ix = r5x.self () ;
		INDEX iy = ix + 1 ;
		assert (between (ix ,0 ,SLOT_SIZE)) ;
		assert (between (iy ,0 ,SLOT_SIZE)) ;
		const auto r10x = align_len - ALIGNOF<BLOCK>::value ;
		const auto r13x = alignto (size_len + max (r10x ,ZERO) ,SIZEOF<BLOCK>::value) ;
		assert (property[r3x][ix].mBlockSize + property[r3x][iy].mBlockSize >= r13x) ;
		const auto r14x = property[r3x][ix].mBlockSize ;
		property[r3x][ix].mBlockSize = r13x ;
		property[r3x][iy].mBlockSize += r14x - r13x ;
		INDEX jx = property[r3x][ix].mBlock + r13x / SIZEOF<BLOCK>::value ;
		property[r3x][iy].mBlock = jx ;
		property[r4x][jx].mBlockCheck1 = BLOCK_CHECK ;
		property[r4x][jx].mBlockCheck2 = BLOCK_CHECK ;
		property[r3x][ix].mBlockSize = r13x ;	
		return ix ;
	}

	imports void popup () {
		const auto r3x = property (slot_array ()) ;
		auto &&r5x = capture ([&] () {
			for (auto &&i : range (0 ,SLOT_SIZE)) {
				if (property[r3x][i].mUsed)
					return i ;
			}
			return NONE ;
		}) ;
		INDEX ix = r5x.self () ;
		assert (between (ix ,0 ,SLOT_SIZE)) ;
		property[r3x][ix].mUsed = TRUE ;
	}

	imports void free (CREF<LENGTH> addr) {
		const auto r3x = property (slot_array ()) ;
		const auto r4x = property (block_array ()) ;
		auto &&r5x = capture ([&] () {
			for (auto &&i : range (0 ,SLOT_SIZE)) {
				if (property[r3x][i].mUsed)
					return i ;
			}
			return NONE ;
		}) ;
		INDEX ix = r5x.self () ;
		INDEX iy = ix + 1 ;
		assert (between (ix ,0 ,SLOT_SIZE)) ;
		assert (between (iy ,0 ,SLOT_SIZE)) ;
		INDEX jx = property[r3x][ix].mBlock ;
		assert (jx != NONE) ;
		assert (property[r4x][jx].mBlockCheck1 == BLOCK_CHECK) ;
		assert (property[r4x][jx].mBlockCheck2 == BLOCK_CHECK) ;
		const auto r10x = address (property[r4x][jx]) + SIZEOF<BLOCK>::value ;
		const auto r11x = r10x + property[r3x][ix].mBlockSize * SIZEOF<BLOCK>::value ;
		const auto r12x = address (addr) ;
		assert (between (r12x ,r10x ,r11x)) ;
		property[r3x][ix].mUsed = FALSE ;
		property[r3x][ix].mBlockSize += property[r3x][iy].mBlockSize ;
		property[r3x][iy].mBlockSize = 0 ;
		property[r3x][iy].mBlock = NONE ;
	}

private:
	imports auto block_array ()
		->VREF<BLOCK[BLOCK_SIZE]> {
		auto &&r1x = capture ([&] () {
			PACK<BLOCK[BLOCK_SIZE]> ret ;
			ret.mP1[0].mBlockCheck1 = BLOCK_CHECK ;
			ret.mP1[0].mBlockCheck2 = BLOCK_CHECK ;
			return forward (ret) ;
		}) ;
		thread_local auto M_BLOCK = r1x.self () ;
		return M_BLOCK.mP1 ;
	}

	imports auto slot_array ()
		->VREF<SLOT[SLOT_SIZE]> {
		auto &&r1x = capture ([&] () {
			PACK<SLOT[SLOT_SIZE]> ret ;
			const auto r1x = SLOT {FALSE ,0 ,NONE} ;
			for (auto &&i : range (1 ,SLOT_SIZE))
				ret.mP1[i] = r1x ;
			ret.mP1[0].mUsed = FALSE ;
			ret.mP1[0].mBlockSize = BLOCK_SIZE ;
			ret.mP1[0].mBlock = 0 ;
			return forward (ret) ;
		}) ;
		thread_local auto M_SLOT = r1x.self () ;
		return M_SLOT.mP1 ;
	}
} ;

template <class UNIT1>
class ANY_IMPLHOLDER_HELP<UNIT1>::ImplHolder :
	public Holder {
private:
	using AnyHeap = typename DETAIL::AnyHeap ;

private:
	UNIT1 mValue ;

public:
	implicit ImplHolder () = delete ;

	explicit ImplHolder (RREF<UNIT1> that) :
		mValue (forward (that)) {}

	void destroy () const override {
		auto &&thiz = property[this] ;
		unsafe_destroy (unsafe_deptr[thiz]) ;
		AnyHeap::free (address (thiz)) ;
		barrier () ;
	}

	auto type_size () const override
		->LENGTH {
		return SIZEOF<ImplHolder>::value ;
	}

	auto type_align () const override
		->LENGTH {
		return ALIGNOF<ImplHolder>::value ;
	}

	auto type_cabi () const override
		->FLAG {
		return operator_cabi (typeas<ImplHolder>::id) ;
	}

	auto poll ()
		->UNIT1 {
		return forward (mValue) ;
	}
} ;

template <class UNIT1>
exports auto ANY_IMPLHOLDER_HELP<UNIT1>::EXTERN::create (RREF<UNIT1> that)
->UNSAFE_PTR<Holder> {
	using R1X = typeof (that) ;
	using R2X = typename ANY_IMPLHOLDER_HELP<R1X>::ImplHolder ;
	using R3X = typename DETAIL::AnyHeap ;
	const auto r1x = R3X::alloc (typeas<TEMP<R2X>>) ;
	unsafe_create (r1x ,forward (that)) ;
	R3X::popup () ;
	return unsafe_deref (r1x) ;
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
		mValue (forward (that)) {}

	void destroy () const override {
		auto &&thiz = property[this] ;
		delete property (thiz) ;
	}

	auto to () leftvalue override
		->VREF<UNIT1> {
		return mValue ;
	}

	auto to () const leftvalue override
		->CREF<UNIT1> {
		return mValue ;
	}
} ;

template <class UNIT1 ,class UNIT2>
exports auto BOX_IMPLHOLDER_HELP<UNIT1 ,UNIT2>::EXTERN::create (RREF<UNIT2> that)
->UNSAFE_PTR<Holder> {
	return new ImplHolder (forward (that)) ;
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
		mValue (forward (that)) ,
		mCounter (ZERO) {}

	void destroy () const override {
		auto &&thiz = property[this] ;
		delete property (thiz) ;
	}

	auto to () const leftvalue override
		->CREF<UNIT1> {
		return mValue ;
	}

	auto increase () override
		->LENGTH {
		return ++mCounter ;
	}

	auto decrease () override
		->LENGTH {
		return --mCounter ;
	}
} ;

template <class UNIT1>
exports auto RC_IMPLHOLDER_HELP<UNIT1>::EXTERN::create (RREF<UNIT1> that)
->UNSAFE_PTR<Holder> {
	return new ImplHolder (forward (that)) ;
} ;
} ;
} ;