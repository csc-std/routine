#pragma once

#ifndef __CSC_RUNTIME__
#error "б╞(д├бузебу ;)д├ : require 'csc_runtime.hpp'"
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
template <class TYPE>
class Coroutine<TYPE>::Implement {
private:
	struct BREAKPOINT {
		jmp_buf unused ;
	} ;

	static constexpr auto BREAK_POINT_SIZE = _SIZEOF_ (BREAKPOINT) + _ALIGNOF_ (BREAKPOINT) ;
	static constexpr auto STACK_FRAME_SIZE = 65536 ;

	struct BREAK_POINT {
		DEF<BYTE[BREAK_POINT_SIZE]> mBreakPoint ;
		ARRAY3<PTR<void>> mStackPoint ;
		DEF<BYTE[STACK_FRAME_SIZE]> mStackFrame ;
	} ;

private:
	friend Coroutine<TYPE> ;

public:
	static void init_break_point (PTR<AnyRef<void>> bp) {
		auto rax = BREAK_POINT () ;
		_ZERO_ (rax) ;
		rax.mStackPoint[0] = &bp ;
		rax.mStackPoint[1] = NULL ;
		rax.mStackPoint[2] = NULL ;
		*bp = AnyRef<BREAK_POINT>::make (std::move (rax)) ;
	}

	static void store_break_point (PTR<AnyRef<void>> bp) noexcept {
		auto &r1 = bp->rebind<BREAK_POINT> ().self ;
		_DEBUG_ASSERT_ (r1.mStackPoint[0] != NULL) ;
		r1.mStackPoint[1] = &bp ;
		const auto r1x = _ADDRESS_ (&r1.mBreakPoint) % _ALIGNOF_ (BREAKPOINT) ;
		const auto r2x = (r1x != 0) ? (_ALIGNOF_ (BREAKPOINT) - r1x) : 0 ;
		const auto r3x = &_NULL_<BYTE> () + (_ADDRESS_ (&r1.mBreakPoint) + r1x) ;
		const auto r4x = _ADDRESS_ (r1.mStackPoint[1]) - _ADDRESS_ (r1.mStackPoint[0]) ;
		_DEBUG_ASSERT_ (_ABS_ (r4x) <= _COUNTOF_ (decltype (r1.mStackFrame))) ;
		_MEMCOPY_ (PTRTOARR[r1.mStackFrame] ,_LOAD_<ARR<BYTE>> (r1.mStackPoint[EFLAG (r4x < 0)]) ,_ABS_ (r4x)) ;
		const auto r5x = setjmp (_LOAD_<BREAKPOINT> (r3x)) ;
		(void) r5x ;
	}

	static void goto_break_point (PTR<AnyRef<void>> bp) noexcept {
		auto &r1 = bp->rebind<BREAK_POINT> ().self ;
		_DEBUG_ASSERT_ (r1.mStackPoint[0] != NULL) ;
		_DEBUG_ASSERT_ (r1.mStackPoint[1] != NULL) ;
		r1.mStackPoint[2] = &bp ;
		_STATIC_WARNING_ ("mark") ;
		_DEBUG_ASSERT_ (r1.mStackPoint[2] == r1.mStackPoint[1]) ;
		const auto r1x = _ADDRESS_ (&r1.mBreakPoint) % _ALIGNOF_ (BREAKPOINT) ;
		const auto r2x = (r1x != 0) ? (_ALIGNOF_ (BREAKPOINT) - r1x) : 0 ;
		const auto r3x = &_NULL_<BYTE> () + (_ADDRESS_ (&r1.mBreakPoint) + r1x) ;
		const auto r4x = _ADDRESS_ (r1.mStackPoint[1]) - _ADDRESS_ (r1.mStackPoint[0]) ;
		_DEBUG_ASSERT_ (_ABS_ (r4x) <= _COUNTOF_ (decltype (r1.mStackFrame))) ;
		_MEMCOPY_ (_LOAD_<ARR<BYTE>> (r1.mStackPoint[EFLAG (r4x < 0)]) ,PTRTOARR[r1.mStackFrame] ,_ABS_ (r4x)) ;
		longjmp (_LOAD_<BREAKPOINT> (r3x) ,1) ;
	}
} ;

template <class TYPE>
inline exports void Coroutine<TYPE>::init_break_point (AnyRef<void> &bp) {
	Implement::init_break_point (&bp) ;
}

template <class TYPE>
inline exports void Coroutine<TYPE>::store_break_point (AnyRef<void> &bp) noexcept {
	Implement::store_break_point (&bp) ;
}

template <class TYPE>
inline exports void Coroutine<TYPE>::goto_break_point (AnyRef<void> &bp) noexcept {
	Implement::goto_break_point (&bp) ;
}
#endif

class RandomService::Implement final :private RandomService::Abstract {
private:
	friend RandomService ;
	friend StrongRef<Implement> ;
	SharedRef<std::random_device> mRandomSeed ;
	AutoRef<std::mt19937> mRandomDevice ;

public:
	Implement () {
		mRandomSeed = SharedRef<std::random_device>::make () ;
		mRandomDevice = AutoRef<std::mt19937>::make (CHAR (mRandomSeed.self ())) ;
	}

	VAL entropy () const override {
		return VAL (mRandomSeed->entropy ()) ;
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