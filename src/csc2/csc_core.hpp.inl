#pragma once

#include "csc.hpp"
#include "csc_core.hpp"

namespace CSC {
namespace U {
template <class UNIT1>
exports void FUNCTION_barrier_HELP<UNIT1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_MSVC ,UNIT1>>>::
FUNCTION_barrier::extern_invoke () {
	noop () ;
}

template <class UNIT1>
exports void FUNCTION_barrier_HELP<UNIT1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_GNUC ,UNIT1>>>::
FUNCTION_barrier::extern_invoke () {
#ifdef __CSC_COMPILER_GNUC__
	asm volatile ("" ::: "memory") ;
#endif
}

template <class UNIT1>
exports void FUNCTION_barrier_HELP<UNIT1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_CLANG ,UNIT1>>>::
FUNCTION_barrier::extern_invoke () {
#ifdef __CSC_COMPILER_GNUC__
	asm volatile ("" ::: "memory") ;
#endif
}

template <class UNIT1>
exports void FUNCTION_debug_assert_HELP<UNIT1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_MSVC ,UNIT1>>>::
FUNCTION_debug_break::extern_invoke () {
#ifdef __CSC_COMPILER_MSVC__
	__debugbreak () ;
#endif
}

template <class UNIT1>
exports void FUNCTION_debug_assert_HELP<UNIT1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_GNUC ,UNIT1>>>::
FUNCTION_debug_break::extern_invoke () {
#ifdef __CSC_COMPILER_GUNC__
	__builtin_trap () ;
#endif
}

template <class UNIT1>
exports void FUNCTION_debug_assert_HELP<UNIT1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_CLANG ,UNIT1>>>::
FUNCTION_debug_break::extern_invoke () {
	std::abort () ;
}
} ;
} ;