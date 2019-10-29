#pragma once

#ifndef __CSC_RUNTIME__
#error "��(�á㧥�� ;)�� : require 'csc_runtime.hpp'"
#endif

#ifdef __CSC__
#pragma push_macro ("self")
#pragma push_macro ("implicit")
#pragma push_macro ("popping")
#pragma push_macro ("imports")
#pragma push_macro ("exports")
#pragma push_macro ("discard")
#undef self
#undef implicit
#undef popping
#undef imports
#undef exports
#undef discard
#endif

#ifdef __CSC_DEPRECATED__
#include <setjmp.h>
#include <cmath>
#include <random>
#endif

#ifdef __CSC__
#pragma pop_macro ("self")
#pragma pop_macro ("implicit")
#pragma pop_macro ("popping")
#pragma pop_macro ("imports")
#pragma pop_macro ("exports")
#pragma pop_macro ("discard")
#endif

namespace CSC {
#ifdef __CSC_DEPRECATED__
template <class UNIT>
class Coroutine<UNIT>::Implement final :private Interface {
private:
	struct CONTEXT_EBP {
		jmp_buf mEbp ;
	} ;

	using CONTEXT_EBP_SIZE = ARGC<_ALIGNOF_ (CONTEXT_EBP) - 1 + _SIZEOF_ (CONTEXT_EBP)> ;
	using STACK_FRAME_SIZE = ARGC<65536> ;

	struct BREAKPOINT {
		DEF<BYTE[CONTEXT_EBP_SIZE::value]> mContextEbp ;
		ARRAY3<LENGTH> mStackPoint ;
		DEF<BYTE[STACK_FRAME_SIZE::value]> mStackFrame ;
	} ;

private:
	friend Coroutine<UNIT> ;

public:
	static void init_break_point (PTR<AnyRef<void>> bp) {
		auto rax = BREAKPOINT () ;
		_ZERO_ (rax) ;
		rax.mStackPoint[0] = _ADDRESS_ (&bp) ;
		rax.mStackPoint[1] = 0 ;
		rax.mStackPoint[2] = 0 ;
		(*bp) = AnyRef<BREAKPOINT>::make (std::move (rax)) ;
	}

	static void store_break_point (PTR<AnyRef<void>> bp) noexcept {
		auto &r1y = bp->rebind<BREAKPOINT> ().self ;
		_DEBUG_ASSERT_ (r1y.mStackPoint[0] != 0) ;
		r1y.mStackPoint[1] = _ADDRESS_  (&bp) ;
		const auto r2x = r1y.mStackPoint[1] - r1y.mStackPoint[0] ;
		_DEBUG_ASSERT_ (_ABS_ (r2x) <= _SIZEOF_ (decltype (r1y.mStackFrame))) ;
		const auto r3x = EFLAG (r2x < 0) ;
		auto &r4y = _LOAD_<ARR<BYTE>> (&bp ,r1y.mStackPoint[r3x]) ;
		_MEMCOPY_ (PTRTOARR[r1y.mStackFrame] ,r4y ,_ABS_ (r2x)) ;
		auto &r5y = load_context_ebp (r1y.mContextEbp) ;
		const auto r6x = setjmp (r5y.mEbp) ;
		(void) r6x ;
	}

	static void goto_break_point (PTR<AnyRef<void>> bp) noexcept {
		auto &r1y = bp->rebind<BREAKPOINT> ().self ;
		_DEBUG_ASSERT_ (r1y.mStackPoint[0] != 0) ;
		_DEBUG_ASSERT_ (r1y.mStackPoint[1] != 0) ;
		r1y.mStackPoint[2] = _ADDRESS_  (&bp) ;
		_STATIC_WARNING_ ("mark") ;
		_DEBUG_ASSERT_ (r1y.mStackPoint[2] == r1y.mStackPoint[1]) ;
		const auto r2x = r1y.mStackPoint[1] - r1y.mStackPoint[0] ;
		_DEBUG_ASSERT_ (_ABS_ (r2x) <= _SIZEOF_ (decltype (r1y.mStackFrame))) ;
		const auto r3x = EFLAG (r2x < 0) ;
		auto &r4y = _LOAD_<ARR<BYTE>> (&bp ,r1y.mStackPoint[r3x]) ;
		_MEMCOPY_ (r4y ,PTRTOARR[r1y.mStackFrame] ,_ABS_ (r2x)) ;
		auto &r5y = load_context_ebp (r1y.mContextEbp) ;
		longjmp (r5y.mEbp ,1) ;
	}

	static CONTEXT_EBP &load_context_ebp (DEF<BYTE[CONTEXT_EBP_SIZE::value]> &ebp) noexcept {
		const auto r1x = _ALIGNAS_ (_ADDRESS_ (&ebp) ,_ALIGNOF_ (CONTEXT_EBP)) ;
		return _LOAD_<CONTEXT_EBP> (&ebp ,r1x) ;
	}
} ;

template <class UNIT>
inline exports void Coroutine<UNIT>::init_break_point (AnyRef<void> &bp) popping {
	Implement::init_break_point (&bp) ;
}

template <class UNIT>
inline exports void Coroutine<UNIT>::store_break_point (AnyRef<void> &bp) noexcept popping {
	Implement::store_break_point (&bp) ;
}

template <class UNIT>
inline exports void Coroutine<UNIT>::goto_break_point (AnyRef<void> &bp) noexcept popping {
	Implement::goto_break_point (&bp) ;
}
#endif

class RandomService::Implement :public RandomService::Abstract {
private:
	SharedRef<std::random_device> mRandomSeed ;
	AutoRef<std::mt19937> mRandomDevice ;

public:
	Implement () {
		mRandomSeed = SharedRef<std::random_device>::make () ;
		mRandomDevice = AutoRef<std::mt19937>::make (CHAR (mRandomSeed.self ())) ;
	}

	VAR entropy () const override {
		return VAR (mRandomSeed->entropy ()) ;
	}

	void reset_seed (VAR _seed) override {
		mRandomDevice = AutoRef<std::mt19937>::make (CHAR (_seed)) ;
	}

	VAR random_value () popping override {
		return VAR (mRandomDevice.self ()) ;
	}

	void random_skip (LENGTH len) override {
#pragma push_macro ("discard")
#undef discard
		mRandomDevice->discard (len) ;
#pragma pop_macro ("discard")
	}
} ;

inline exports RandomService::RandomService () {
	mThis = StrongRef<Implement>::make () ;
}
} ;