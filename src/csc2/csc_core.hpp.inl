#pragma once

#include "csc.hpp"
#include "csc_core.hpp"

namespace CSC {
namespace U {
template <class ARG1>
using FUNCTION_barrier_HELP_HINT1 = typename FUNCTION_barrier_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_MSVC ,ARG1>>>::FUNCTION_barrier ;

template <class ARG1>
exports void FUNCTION_barrier_HELP_HINT1<ARG1>::extern_invoke () {
	noop () ;
}

template <class ARG1>
using FUNCTION_barrier_HELP_HINT2 = typename FUNCTION_barrier_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_GNUC ,ARG1>>>::FUNCTION_barrier ;

template <class ARG1>
exports void FUNCTION_barrier_HELP_HINT2<ARG1>::extern_invoke () {
#ifdef __CSC_COMPILER_GNUC__
	asm volatile ("" ::: "memory") ;
#endif
}

template <class ARG1>
using FUNCTION_barrier_HELP_HINT3 = typename FUNCTION_barrier_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_CLANG ,ARG1>>>::FUNCTION_barrier ;

template <class ARG1>
exports void FUNCTION_barrier_HELP_HINT3<ARG1>::extern_invoke () {
#ifdef __CSC_COMPILER_GNUC__
	asm volatile ("" ::: "memory") ;
#endif
}

template <class ARG1>
using FUNCTION_debug_break_HELP_HINT1 = typename FUNCTION_debug_assert_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_MSVC ,ARG1>>>::FUNCTION_debug_break ;

template <class ARG1>
exports void FUNCTION_debug_break_HELP_HINT1<ARG1>::extern_invoke () {
#ifdef __CSC_COMPILER_MSVC__
	__debugbreak () ;
#endif
}

template <class ARG1>
using FUNCTION_debug_break_HELP_HINT2 = typename FUNCTION_debug_assert_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_GNUC ,ARG1>>>::FUNCTION_debug_break ;

template <class ARG1>
exports void FUNCTION_debug_break_HELP_HINT2<ARG1>::extern_invoke () {
#ifdef __CSC_COMPILER_GUNC__
	__builtin_trap () ;
#endif
}

template <class ARG1>
using FUNCTION_debug_break_HELP_HINT3 = typename FUNCTION_debug_assert_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_CLANG ,ARG1>>>::FUNCTION_debug_break ;

template <class ARG1>
exports void FUNCTION_debug_break_HELP_HINT3<ARG1>::extern_invoke () {
	std::abort () ;
}
} ;
} ;