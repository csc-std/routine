﻿#pragma once

#ifndef __CSC_CORE__
#define __CSC_CORE__
#endif

#include "csc.hpp"

namespace CSC {
namespace api {
using std::int32_t ;
using std::int64_t ;
using std::uint8_t ;
using std::uint16_t ;
using std::uint32_t ;
using std::uint64_t ;

using std::nothrow ;

#ifndef __CSC_COMPILER_GNUC__
using std::max_align_t ;
#endif

#ifdef __CSC_COMPILER_GNUC__
//@error: fuck g++4.8
using ::max_align_t ;
#endif

using std::numeric_limits ;
using std::initializer_list ;

using std::is_class ;
using std::is_base_of ;
using std::is_pod ;

#ifndef __CSC_COMPILER_GNUC__
using std::is_trivial ;
#endif

using std::is_default_constructible ;
using std::is_constructible ;
using std::is_nothrow_destructible ;
using std::is_copy_constructible ;
using std::is_copy_assignable ;
using std::is_nothrow_move_constructible ;
using std::is_nothrow_move_assignable ;
using std::is_convertible ;

using std::atomic ;
} ;

using BOOL = bool ;

using VAR32 = api::int32_t ;
using VAR64 = api::int64_t ;

static constexpr auto VAR32_MAX = VAR32 (2147483647) ;
static constexpr auto VAR32_MIN = ~VAR32_MAX ;
static constexpr auto VAR64_MAX = VAR64 (9223372036854775807) ;
static constexpr auto VAR64_MIN = ~VAR64_MAX ;

#ifdef __CSC_CONFIG_VAR32__
using VAR = VAR32 ;

static constexpr auto VAR_MAX = VAR32_MAX ;
static constexpr auto VAR_MIN = VAR32_MIN ;
#endif

#ifdef __CSC_CONFIG_VAR64__
using VAR = VAR64 ;

static constexpr auto VAR_MAX = VAR64_MAX ;
static constexpr auto VAR_MIN = VAR64_MIN ;
#endif

static constexpr auto VAR_ZERO = VAR (+0) ;
static constexpr auto VAR_NONE = VAR (-1) ;
static constexpr auto VAR_USED = VAR (-2) ;

using VARX = long ;
using VARY = unsigned long ;

using INDEX = VAR ;
using LENGTH = VAR ;
using FLAG = VAR ;

enum class EFLAG :VAR ;

using VAL32 = float ;
using VAL64 = double ;

static constexpr auto VAL32_MAX = VAL32 (3.402823466E+38) ;
static constexpr auto VAL32_MIN = VAL32 (1.175494351E-38) ;
static constexpr auto VAL32_EPS = VAL32 (1.192092896E-07) ;
static constexpr auto VAL32_INF = api::numeric_limits<VAL32>::infinity () ;
static constexpr auto VAL32_NAN = api::numeric_limits<VAL32>::quiet_NaN () ;
static constexpr auto VAL64_MAX = VAL64 (1.7976931348623158E+308) ;
static constexpr auto VAL64_MIN = VAL64 (2.2250738585072014E-308) ;
static constexpr auto VAL64_EPS = VAL64 (2.2204460492503131E-016) ;
static constexpr auto VAL64_INF = api::numeric_limits<VAL64>::infinity () ;
static constexpr auto VAL64_NAN = api::numeric_limits<VAL64>::quiet_NaN () ;

#ifdef __CSC_CONFIG_VAL32__
using VAL = VAL32 ;

static constexpr auto VAL_MAX = VAL32_MAX ;
static constexpr auto VAL_MIN = VAL32_MIN ;
static constexpr auto VAL_EPS = VAL32_EPS ;
static constexpr auto VAL_INF = VAL32_INF ;
static constexpr auto VAL_NAN = VAL32_NAN ;
#endif

#ifdef __CSC_CONFIG_VAL64__
using VAL = VAL64 ;

static constexpr auto VAL_MAX = VAL64_MAX ;
static constexpr auto VAL_MIN = VAL64_MIN ;
static constexpr auto VAL_EPS = VAL64_EPS ;
static constexpr auto VAL_INF = VAL64_INF ;
static constexpr auto VAL_NAN = VAL64_NAN ;
#endif

using VALX = long double ;

static constexpr auto MATH_E = VALX (2.71828182845904523536) ;
static constexpr auto MATH_PI = VALX (3.14159265358979323846) ;
static constexpr auto MATH_SQRT2 = VALX (1.41421356237309504880) ;
static constexpr auto MATH_LN2 = VALX (0.693147180559945309417) ;
static constexpr auto MATH_LN10 = VALX (2.30258509299404568402) ;

template <class UNIT>
using DEF = UNIT ;

template <class UNIT>
using PTR = DEF<UNIT *> ;

template <class UNIT1 ,class UNIT2>
using MEMPTR = DEF<UNIT1 UNIT2::*> ;

#ifndef __CSC_COMPILER_GNUC__
template <class UNIT>
using ARR = DEF<UNIT[]> ;
#endif

#ifdef __CSC_COMPILER_GNUC__
//@error: fuck g++4.8
template <class UNIT>
using ARR = DEF<UNIT[0]> ;
#endif

using BYTE = api::uint8_t ;
using WORD = api::uint16_t ;
using CHAR = api::uint32_t ;
using DATA = api::uint64_t ;

class __uint128_t {
private:
	alignas (16) DEF<BYTE[16]> unused ;
} ;

using MEGA = __uint128_t ;

using STRU8 = unsigned char ;
using STRU16 = char16_t ;
using STRU32 = char32_t ;
using STRA = char ;
using STRW = wchar_t ;

#ifdef __CSC_CONFIG_STRA__
using STR = STRA ;
#endif

#ifdef __CSC_CONFIG_STRW__
using STR = STRW ;
#endif

using STRX = signed char ;

template <VAR _ARG1>
struct ARGC {
	imports constexpr VAR compile () {
		return _ARG1 ;
	}
} ;

using ZERO = ARGC<0> ;

template <class UNIT>
struct ARGV {
	static DEF<void (const ARGV &)> ID ;
} ;

template <class UNIT>
inline void ARGV<UNIT>::ID (const ARGV &) {}

template <class _ARG1>
using ARGVF = DEF<void (const ARGV<_ARG1> &)> ;

template <class...>
struct ARGVS ;

template <class>
struct ARGVP ;

using DEFAULT_RECURSIVE_SIZE = ARGC<256> ;
using DEFAULT_LONGSTRING_SIZE = ARGC<8195> ;
using DEFAULT_HUGESTRING_SIZE = ARGC<8388607> ;

template <class ,class...>
struct SPECIALIZATION ;

template <class>
struct TEMP ;

template <class...>
struct PACK ;

class Interface ;

namespace U {
template <class...>
struct CONSTEXPR_AND ;

template <>
struct CONSTEXPR_AND<> {
	imports constexpr VAR compile () {
		return TRUE ;
	}
} ;

template <class _ARG1 ,class... _ARGS>
struct CONSTEXPR_AND<_ARG1 ,_ARGS...> {
	imports constexpr VAR compile () {
		using R1X = CONSTEXPR_AND<_ARGS...> ;
		return VAR (_ARG1::compile () && R1X::compile ()) ;
	}
} ;

template <class...>
struct CONSTEXPR_OR ;

template <>
struct CONSTEXPR_OR<> {
	imports constexpr VAR compile () {
		return FALSE ;
	}
} ;

template <class _ARG1 ,class... _ARGS>
struct CONSTEXPR_OR<_ARG1 ,_ARGS...> {
	imports constexpr VAR compile () {
		using R1X = CONSTEXPR_OR<_ARGS...> ;
		return VAR (_ARG1::compile () || R1X::compile ()) ;
	}
} ;

template <class _ARG1>
struct CONSTEXPR_NOT {
	imports constexpr VAR compile () {
		return VAR (!_ARG1::compile ()) ;
	}
} ;
} ;

namespace U {
template <class _ARG1 ,class _ARG2>
struct CONSTEXPR_EQUAL {
	imports constexpr VAR compile () {
		return VAR (_ARG1::compile () == _ARG2::compile ()) ;
	}
} ;

template <class _ARG1 ,class _ARG2>
struct CONSTEXPR_COMPR_LT {
	imports constexpr VAR compile () {
		return VAR (_ARG1::compile () < _ARG2::compile ()) ;
	}
} ;

template <class _ARG1 ,class _ARG2>
struct CONSTEXPR_COMPR_NLT {
	imports constexpr VAR compile () {
		return VAR (_ARG1::compile () >= _ARG2::compile ()) ;
	}
} ;

template <class _ARG1 ,class _ARG2>
struct CONSTEXPR_COMPR_GT {
	imports constexpr VAR compile () {
		return VAR (_ARG1::compile () > _ARG2::compile ()) ;
	}
} ;

template <class _ARG1 ,class _ARG2>
struct CONSTEXPR_COMPR_NGT {
	imports constexpr VAR compile () {
		return VAR (_ARG1::compile () <= _ARG2::compile ()) ;
	}
} ;
} ;

namespace U {
template <class _ARG1 ,class _ARG2>
struct CONSTEXPR_ADD {
	imports constexpr VAR compile () {
		return _ARG1::compile () + _ARG2::compile () ;
	}
} ;

template <class _ARG1 ,class _ARG2>
struct CONSTEXPR_SUB {
	imports constexpr VAR compile () {
		return _ARG1::compile () - _ARG2::compile () ;
	}
} ;

template <class _ARG1 ,class _ARG2>
struct CONSTEXPR_MUL {
	imports constexpr VAR compile () {
		return _ARG1::compile () * _ARG2::compile () ;
	}
} ;

template <class _ARG1 ,class _ARG2>
struct CONSTEXPR_DIV {
	imports constexpr VAR compile () {
		return _ARG1::compile () / _ARG2::compile () ;
	}
} ;

template <class _ARG1 ,class _ARG2>
struct CONSTEXPR_MOD {
	imports constexpr VAR compile () {
		return _ARG1::compile () % _ARG2::compile () ;
	}
} ;
} ;

namespace U {
template <class _ARG1>
struct CONSTEXPR_INCREASE {
	imports constexpr VAR compile () {
		using R1X = CONSTEXPR_ADD<_ARG1 ,ARGC<1>> ;
		return R1X::compile () ;
	}
} ;

template <class _ARG1>
struct CONSTEXPR_DECREASE {
	imports constexpr VAR compile () {
		using R1X = CONSTEXPR_SUB<_ARG1 ,ARGC<1>> ;
		return R1X::compile () ;
	}
} ;
} ;

#ifdef __CSC__
namespace U {
template <class _ARG1>
inline constexpr VAR _COMPILE_FORCE_ (const ARGVF<_ARG1> &) {
	return _ARG1::compile () ;
}

template <class _ARG1>
using ARGC_TYPE = ARGC<(_COMPILE_FORCE_ (ARGV<_ARG1>::ID))> ;
} ;

namespace U {
template <class>
struct ENABLE ;

template <>
struct ENABLE<ARGC<TRUE>> {
	using TYPE = NONE ;
} ;

template <class _ARG1>
using ENABLE_TYPE = typename ENABLE<ARGC_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class _ARG1 ,class>
struct DEPENDENT {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1 ,class _ARG2>
using DEPENDENT_TYPE = typename DEPENDENT<_ARG1 ,_ARG2>::TYPE ;
} ;

namespace U {
template <class ,class ,class>
struct CONDITIONAL ;

template <class _ARG1 ,class _ARG2>
struct CONDITIONAL<ARGC<TRUE> ,_ARG1 ,_ARG2> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1 ,class _ARG2>
struct CONDITIONAL<ARGC<FALSE> ,_ARG1 ,_ARG2> {
	using TYPE = _ARG2 ;
} ;

template <class _ARG1 ,class _ARG2 ,class _ARG3>
using CONDITIONAL_TYPE = typename CONDITIONAL<ARGC_TYPE<_ARG1> ,_ARG2 ,_ARG3>::TYPE ;
} ;

namespace U {
template <class ,class>
struct IS_SAME {
	using TYPE = ARGC<FALSE> ;
} ;

template <class _ARG1>
struct IS_SAME<_ARG1 ,_ARG1> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1 ,class _ARG2>
using IS_SAME_HELP = typename IS_SAME<_ARG1 ,_ARG2>::TYPE ;
} ;

namespace U {
template <class _ARG1>
struct REMOVE_REFERENCE {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
struct REMOVE_REFERENCE<_ARG1 &> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
struct REMOVE_REFERENCE<_ARG1 &&> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using REMOVE_REFERENCE_TYPE = typename REMOVE_REFERENCE<_ARG1>::TYPE ;
} ;

namespace U {
template <class _ARG1>
using IS_REFERENCE_HELP = U::CONSTEXPR_NOT<IS_SAME_HELP<_ARG1 ,REMOVE_REFERENCE_TYPE<_ARG1>>> ;
} ;

namespace U {
template <class _ARG1>
using IS_LVALUE_REFERENCE_HELP = IS_SAME_HELP<_ARG1 ,REMOVE_REFERENCE_TYPE<_ARG1> &> ;
} ;

namespace U {
template <class _ARG1>
using IS_RVALUE_REFERENCE_HELP = IS_SAME_HELP<_ARG1 ,REMOVE_REFERENCE_TYPE<_ARG1> &&> ;
} ;

namespace U {
template <class _ARG1>
struct REMOVE_CONST {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
struct REMOVE_CONST<const _ARG1> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using REMOVE_CONST_TYPE = typename REMOVE_CONST<_ARG1>::TYPE ;
} ;

namespace U {
template <class _ARG1>
using IS_CONST_HELP = U::CONSTEXPR_NOT<IS_SAME_HELP<_ARG1 ,REMOVE_CONST_TYPE<_ARG1>>> ;
} ;

namespace U {
template <class _ARG1>
struct REMOVE_VOLATILE {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
struct REMOVE_VOLATILE<volatile _ARG1> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using REMOVE_VOLATILE_TYPE = typename REMOVE_VOLATILE<_ARG1>::TYPE ;
} ;

namespace U {
template <class _ARG1>
using IS_VOLATILE_HELP = U::CONSTEXPR_NOT<IS_SAME_HELP<_ARG1 ,REMOVE_VOLATILE_TYPE<_ARG1>>> ;
} ;

namespace U {
template <class _ARG1>
using REMOVE_CVR_TYPE = REMOVE_CONST_TYPE<REMOVE_VOLATILE_TYPE<REMOVE_REFERENCE_TYPE<_ARG1>>> ;
} ;

namespace U {
template <class _ARG1>
struct REMOVE_POINTER {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
struct REMOVE_POINTER<PTR<_ARG1>> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using REMOVE_POINTER_TYPE = typename REMOVE_POINTER<REMOVE_CVR_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class _ARG1>
using IS_POINTER_HELP = U::CONSTEXPR_NOT<IS_SAME_HELP<REMOVE_CVR_TYPE<_ARG1> ,REMOVE_POINTER_TYPE<_ARG1>>> ;
} ;

namespace U {
template <class _ARG1>
struct REMOVE_ARRAY {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
struct REMOVE_ARRAY<ARR<_ARG1>> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1 ,LENGTH _ARG2>
struct REMOVE_ARRAY<_ARG1[_ARG2]> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using REMOVE_ARRAY_TYPE = typename REMOVE_ARRAY<_ARG1>::TYPE ;
} ;

namespace U {
template <class _ARG1>
using IS_ARRAY_HELP = U::CONSTEXPR_NOT<IS_SAME_HELP<_ARG1 ,REMOVE_ARRAY_TYPE<_ARG1>>> ;
} ;

namespace U {
template <class _ARG1 ,class _ARG2>
using ARRAY_BIND_TYPE = DEF<_ARG1[_ARG2::compile ()]> ;
} ;

namespace U {
template <class _ARG1>
struct REMOVE_MEMPTR {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1 ,class _ARG2>
struct REMOVE_MEMPTR<MEMPTR<_ARG1 ,_ARG2>> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using REMOVE_MEMPTR_TYPE = typename REMOVE_MEMPTR<REMOVE_CVR_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class _ARG1>
using IS_MEMPTR_HELP = U::CONSTEXPR_NOT<IS_SAME_HELP<REMOVE_CVR_TYPE<_ARG1> ,REMOVE_MEMPTR_TYPE<_ARG1>>> ;
} ;

namespace U {
template <class>
struct MEMPTR_CLASS ;

template <class _ARG1 ,class _ARG2>
struct MEMPTR_CLASS<MEMPTR<_ARG1 ,_ARG2>> {
	using TYPE = _ARG2 ;
} ;

template <class _ARG1>
using MEMPTR_CLASS_TYPE = typename MEMPTR_CLASS<REMOVE_CVR_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class _ARG1>
struct REMOVE_TEMP {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
struct REMOVE_TEMP<TEMP<_ARG1>> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using REMOVE_TEMP_TYPE = typename REMOVE_TEMP<REMOVE_CVR_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class>
struct IS_PLACEHOLDER {
	using TYPE = ARGC<FALSE> ;
} ;

template <class _ARG1>
struct IS_PLACEHOLDER<ARGV<ARGVP<_ARG1>>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
using IS_PLACEHOLDER_HELP = typename IS_PLACEHOLDER<REMOVE_CVR_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class _ARG1>
struct REMOVE_FUNCATTR {
	using TYPE = _ARG1 ;
} ;

//@warn: exclude reference attribute of function
template <class _ARG1 ,class... _ARGS>
struct REMOVE_FUNCATTR<_ARG1 (_ARGS...)> {
	using TYPE = DEF<_ARG1 (_ARGS...)> ;
} ;

template <class _ARG1 ,class... _ARGS>
struct REMOVE_FUNCATTR<_ARG1 (_ARGS...) const> {
	using TYPE = DEF<_ARG1 (_ARGS...)> ;
} ;

template <class _ARG1 ,class... _ARGS>
struct REMOVE_FUNCATTR<_ARG1 (_ARGS...) volatile> {
	using TYPE = DEF<_ARG1 (_ARGS...)> ;
} ;

template <class _ARG1 ,class... _ARGS>
struct REMOVE_FUNCATTR<_ARG1 (_ARGS...) const volatile> {
	using TYPE = DEF<_ARG1 (_ARGS...)> ;
} ;

//@warn: behaviors of 'noexcept' changed in C++17
#ifdef __CSC_CXX_LATEST__
template <class _ARG1 ,class... _ARGS>
struct REMOVE_FUNCATTR<_ARG1 (_ARGS...) noexcept> {
	using TYPE = DEF<_ARG1 (_ARGS...)> ;
} ;

template <class _ARG1 ,class... _ARGS>
struct REMOVE_FUNCATTR<_ARG1 (_ARGS...) const noexcept> {
	using TYPE = DEF<_ARG1 (_ARGS...)> ;
} ;

template <class _ARG1 ,class... _ARGS>
struct REMOVE_FUNCATTR<_ARG1 (_ARGS...) volatile noexcept> {
	using TYPE = DEF<_ARG1 (_ARGS...)> ;
} ;

template <class _ARG1 ,class... _ARGS>
struct REMOVE_FUNCATTR<_ARG1 (_ARGS...) const volatile noexcept> {
	using TYPE = DEF<_ARG1 (_ARGS...)> ;
} ;
#endif

template <class _ARG1>
using REMOVE_FUNCATTR_TYPE = typename REMOVE_FUNCATTR<_ARG1>::TYPE ;
} ;

namespace U {
template <class _ARG1>
struct REMOVE_FUNCTION {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1 ,class... _ARGS>
struct REMOVE_FUNCTION<_ARG1 (_ARGS...)> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using REMOVE_FUNCTION_TYPE = typename REMOVE_FUNCTION<REMOVE_FUNCATTR_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class _ARG1>
using IS_FUNCTION_HELP = U::CONSTEXPR_NOT<IS_SAME_HELP<REMOVE_FUNCATTR_TYPE<_ARG1> ,REMOVE_FUNCTION_TYPE<_ARG1>>> ;
} ;

namespace U {
template <class>
struct FUNCTION_PARAMS ;

template <class _ARG1 ,class... _ARGS>
struct FUNCTION_PARAMS<_ARG1 (_ARGS...)> {
	using TYPE = ARGVS<_ARGS...> ;
} ;

template <class _ARG1>
using FUNCTION_PARAMS_TYPE = typename FUNCTION_PARAMS<REMOVE_FUNCATTR_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class ,class>
struct FUNCTION_BIND ;

template <class _ARG1 ,class... _ARGS>
struct FUNCTION_BIND<_ARG1 ,ARGVS<_ARGS...>> {
	using TYPE = DEF<_ARG1 (_ARGS...)> ;
} ;

template <class _ARG1 ,class _ARG2>
using FUNCTION_BIND_TYPE = typename FUNCTION_BIND<_ARG1 ,_ARG2>::TYPE ;
} ;

namespace U {
template <class ,class>
struct IS_CLASS {
	using TYPE = ARGC<FALSE> ;
} ;

template <class _ARG1>
struct IS_CLASS<_ARG1 ,NONE> {
	using TYPE = ARGC<(api::is_class<_ARG1>::value)> ;
} ;

template <class _ARG1>
using IS_CLASS_HELP = typename IS_CLASS<_ARG1 ,NONE>::TYPE ;
} ;

namespace U {
template <class ,class>
struct IS_TRIVIAL {
	using TYPE = ARGC<FALSE> ;
} ;

template <class _ARG1>
struct IS_TRIVIAL<_ARG1 ,NONE> {
#ifndef __CSC_CXX_LATEST__
	using TYPE = ARGC<(api::is_pod<_ARG1>::value)> ;
#endif

#ifdef __CSC_CXX_LATEST__
	using TYPE = ARGC<(api::is_trivial<_ARG1>::value)> ;
#endif
} ;

template <class _ARG1>
using IS_TRIVIAL_HELP = typename IS_TRIVIAL<_ARG1 ,NONE>::TYPE ;
} ;

namespace U {
template <class ,class ,class>
struct IS_COMPLETE {
	using TYPE = ARGC<FALSE> ;
} ;

template <class _ARG1 ,class _ARG2>
struct IS_COMPLETE<_ARG1 ,_ARG2 ,ENABLE_TYPE<ARGC<(sizeof (_ARG1) > 0)>>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1 ,class _ARG2>
using IS_COMPLETE_HELP = typename IS_COMPLETE<REMOVE_CVR_TYPE<_ARG1> ,_ARG2 ,NONE>::TYPE ;
} ;

namespace U {
template <class>
struct IS_TEMPLATE {
	using TYPE = ARGC<FALSE> ;
} ;

template <template <class...> class _ARGT ,class... _ARGS>
struct IS_TEMPLATE<_ARGT<_ARGS...>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
using IS_TEMPLATE_HELP = typename IS_TEMPLATE<REMOVE_CVR_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class>
struct TEMPLATE_PARAMS ;

template <template <class...> class _ARGT ,class... _ARGS>
struct TEMPLATE_PARAMS<_ARGT<_ARGS...>> {
	using TYPE = ARGVS<_ARGS...> ;
} ;

template <class _ARG1>
using TEMPLATE_PARAMS_TYPE = typename TEMPLATE_PARAMS<REMOVE_CVR_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class ,class>
struct SIZE_OF {
	using TYPE = ZERO ;
} ;

template <class _ARG1>
struct SIZE_OF<_ARG1 ,NONE> {
	using TYPE = ARGC<(sizeof (_ARG1))> ;
} ;

template <class _ARG1>
using SIZE_OF_TYPE = typename SIZE_OF<REMOVE_CVR_TYPE<_ARG1> ,NONE>::TYPE ;
} ;

namespace U {
template <class ,class>
struct ALIGN_OF {
	using TYPE = ZERO ;
} ;

template <class _ARG1>
struct ALIGN_OF<_ARG1 ,NONE> {
	using TYPE = ARGC<(alignof (_ARG1))> ;
} ;

template <class _ARG1>
using ALIGN_OF_TYPE = typename ALIGN_OF<REMOVE_ARRAY_TYPE<REMOVE_CVR_TYPE<_ARG1>> ,NONE>::TYPE ;
} ;

namespace U {
template <class>
struct COUNT_OF ;

template <class _ARG1>
struct COUNT_OF<ARR<_ARG1>> {
	using TYPE = ZERO ;
} ;

template <class _ARG1 ,LENGTH _ARG2>
struct COUNT_OF<_ARG1[_ARG2]> {
	using TYPE = ARGC<_ARG2> ;
} ;

template <class _ARG1>
using COUNT_OF_TYPE = typename COUNT_OF<REMOVE_CVR_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class>
struct CAPACITY_OF ;

template <>
struct CAPACITY_OF<ARGVS<>> {
	using TYPE = ZERO ;
} ;

template <class... _ARGS>
struct CAPACITY_OF<ARGVS<_ARGS...>> {
	using TYPE = ARGC<(sizeof... (_ARGS))> ;
} ;

template <class _ARG1>
using CAPACITY_OF_TYPE = typename CAPACITY_OF<REMOVE_CVR_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class ,class ,class>
struct IS_ARRAY_OF {
	using TYPE = ARGC<FALSE> ;
} ;

template <class _ARG1>
struct IS_ARRAY_OF<REMOVE_ARRAY_TYPE<_ARG1> ,_ARG1 ,ENABLE_TYPE<U::CONSTEXPR_COMPR_GT<COUNT_OF_TYPE<_ARG1> ,ZERO>>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1 ,class _ARG2>
using IS_ARRAY_OF_HELP = typename IS_ARRAY_OF<REMOVE_CVR_TYPE<_ARG1> ,REMOVE_CVR_TYPE<_ARG2> ,NONE>::TYPE ;
} ;

namespace U {
template <class ,class ,class>
struct FUNCTION_OF ;

template <class _ARG1>
struct FUNCTION_OF<_ARG1 ,ENABLE_TYPE<IS_FUNCTION_HELP<REMOVE_POINTER_TYPE<_ARG1>>> ,ARGC<1>> {
	using TYPE = REMOVE_FUNCATTR_TYPE<REMOVE_POINTER_TYPE<_ARG1>> ;
} ;

template <class _ARG1 ,class _ARG2>
struct FUNCTION_OF<_ARG1 ,_ARG2 ,ARGC<1>> {
	using TYPE = typename FUNCTION_OF<_ARG1 ,_ARG2 ,ARGC<2>>::TYPE ;
} ;

template <class _ARG1>
struct FUNCTION_OF<_ARG1 ,ENABLE_TYPE<IS_MEMPTR_HELP<decltype (&_ARG1::operator())>> ,ARGC<2>> {
	using TYPE = REMOVE_FUNCATTR_TYPE<REMOVE_MEMPTR_TYPE<decltype (&_ARG1::operator())>> ;
} ;

template <class _ARG1>
using FUNCTION_OF_TYPE = typename FUNCTION_OF<REMOVE_CVR_TYPE<_ARG1> ,NONE ,ARGC<1>>::TYPE ;
} ;

namespace U {
template <class ,class ,class>
struct RESULT_OF ;

template <class _ARG1 ,class _ARG2>
struct RESULT_OF<_ARG1 ,_ARG2 ,ENABLE_TYPE<IS_SAME_HELP<_ARG2 ,FUNCTION_PARAMS_TYPE<_ARG1>>>> {
	using TYPE = REMOVE_FUNCTION_TYPE<_ARG1> ;
} ;

template <class _ARG1 ,class _ARG2>
using RESULT_OF_TYPE = typename RESULT_OF<FUNCTION_OF_TYPE<_ARG1> ,_ARG2 ,NONE>::TYPE ;
} ;

namespace U {
template <class ,class ,class>
struct REPEAT_PARAMS ;

template <class _ARG1 ,class... _ARGS>
struct REPEAT_PARAMS<ZERO ,_ARG1 ,ARGVS<_ARGS...>> {
	using TYPE = ARGVS<_ARGS...> ;
} ;

template <class _ARG1 ,class _ARG2 ,class... _ARGS>
struct REPEAT_PARAMS<_ARG1 ,_ARG2 ,ARGVS<_ARGS...>> {
	_STATIC_ASSERT_ (U::CONSTEXPR_COMPR_GT<_ARG1 ,ZERO>::compile ()) ;
	using R1X = ARGC_TYPE<U::CONSTEXPR_DECREASE<_ARG1>> ;
	using TYPE = typename REPEAT_PARAMS<R1X ,_ARG2 ,ARGVS<_ARG2 ,_ARGS...>>::TYPE ;
} ;

template <class _ARG1 ,class _ARG2>
using REPEAT_PARAMS_TYPE = typename REPEAT_PARAMS<ARGC_TYPE<_ARG1> ,_ARG2 ,ARGVS<>>::TYPE ;
} ;

namespace U {
template <class ,class ,class>
struct RANGE_PARAMS ;

template <class _ARG1 ,class... _ARGS>
struct RANGE_PARAMS<ZERO ,_ARG1 ,ARGVS<_ARGS...>> {
	using TYPE = ARGVS<_ARGS...> ;
} ;

template <class _ARG1 ,class _ARG2 ,class... _ARGS>
struct RANGE_PARAMS<_ARG1 ,_ARG2 ,ARGVS<_ARGS...>> {
	_STATIC_ASSERT_ (U::CONSTEXPR_COMPR_GT<_ARG1 ,ZERO>::compile ()) ;
	using R1X = ARGC_TYPE<U::CONSTEXPR_DECREASE<_ARG1>> ;
	using R2X = ARGC_TYPE<U::CONSTEXPR_INCREASE<_ARG2>> ;
	using TYPE = typename RANGE_PARAMS<R1X ,R2X ,ARGVS<_ARGS... ,_ARG2>>::TYPE ;
} ;

template <class _ARG1>
using RANGE_PARAMS_TYPE = typename RANGE_PARAMS<ARGC_TYPE<_ARG1> ,ARGC<1> ,ARGVS<>>::TYPE ;
} ;

namespace U {
template <class>
struct PARAMS_ONE ;

template <class _ARG1 ,class... _ARGS>
struct PARAMS_ONE<ARGVS<_ARG1 ,_ARGS...>> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using PARAMS_ONE_TYPE = typename PARAMS_ONE<_ARG1>::TYPE ;
} ;

namespace U {
template <class>
struct PARAMS_REST ;

template <class _ARG1 ,class... _ARGS>
struct PARAMS_REST<ARGVS<_ARG1 ,_ARGS...>> {
	using TYPE = ARGVS<_ARGS...> ;
} ;

template <class _ARG1>
using PARAMS_REST_TYPE = typename PARAMS_REST<_ARG1>::TYPE ;
} ;

namespace U {
template <class ,class>
struct PARAMS_CAT ;

template <class... _ARGS1 ,class... _ARGS2>
struct PARAMS_CAT<ARGVS<_ARGS1...> ,ARGVS<_ARGS2...>> {
	using TYPE = ARGVS<_ARGS1... ,_ARGS2...> ;
} ;

template <class _ARG1 ,class _ARG2>
using PARAMS_CAT_TYPE = typename PARAMS_CAT<_ARG1 ,_ARG2>::TYPE ;
} ;

namespace U {
template <class ,class ,class>
struct INDEX_OF {
	using TYPE = ARGC<VAR_NONE> ;
} ;

template <class _ARG1 ,class _ARG2 ,class... _ARGS>
struct INDEX_OF<_ARG1 ,_ARG2 ,ARGVS<_ARG2 ,_ARGS...>> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1 ,class _ARG2 ,class _ARG3 ,class... _ARGS>
struct INDEX_OF<_ARG1 ,_ARG2 ,ARGVS<_ARG3 ,_ARGS...>> {
	using R1X = ARGC_TYPE<U::CONSTEXPR_INCREASE<_ARG1>> ;
	using TYPE = typename INDEX_OF<R1X ,_ARG2 ,ARGVS<_ARGS...>>::TYPE ;
} ;

template <class _ARG1 ,class _ARG2>
using INDEX_OF_TYPE = typename INDEX_OF<ZERO ,_ARG1 ,_ARG2>::TYPE ;
} ;

namespace U {
template <class ,class>
struct INDEX_TO ;

template <class _ARG1 ,class... _ARGS>
struct INDEX_TO<ZERO ,ARGVS<_ARG1 ,_ARGS...>> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
struct INDEX_TO<_ARG1 ,ARGVS<>> {
	//@info: bad index_to
	using TYPE = NONE ;
} ;

template <class _ARG1 ,class _ARG2 ,class... _ARGS>
struct INDEX_TO<_ARG1 ,ARGVS<_ARG2 ,_ARGS...>> {
	_STATIC_ASSERT_ (U::CONSTEXPR_COMPR_GT<_ARG1 ,ZERO>::compile ()) ;
	using R1X = ARGC_TYPE<U::CONSTEXPR_DECREASE<_ARG1>> ;
	using TYPE = typename INDEX_TO<R1X ,ARGVS<_ARGS...>>::TYPE ;
} ;

template <class _ARG1 ,class _ARG2>
using INDEX_TO_TYPE = typename INDEX_TO<ARGC_TYPE<_ARG1> ,_ARG2>::TYPE ;
} ;

namespace U {
template <class _ARG1>
using IS_VOID_HELP = IS_SAME_HELP<REMOVE_CVR_TYPE<_ARG1> ,NONE> ;
} ;

namespace U {
template <class ,class>
struct IS_VAR_XYZ {
	using TYPE = ARGC<FALSE> ;
} ;

template <>
struct IS_VAR_XYZ<VAR32 ,VAR32> {
	using TYPE = ARGC<TRUE> ;
} ;

template <>
struct IS_VAR_XYZ<VAR64 ,VAR64> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
struct IS_VAR_XYZ<_ARG1 ,VARX> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
struct IS_VAR_XYZ<_ARG1 ,VARY> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
using IS_VAR_XYZ_HELP = typename IS_VAR_XYZ<REMOVE_CVR_TYPE<_ARG1> ,REMOVE_CVR_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class ,class>
struct IS_VAL_XYZ {
	using TYPE = ARGC<FALSE> ;
} ;

template <>
struct IS_VAL_XYZ<VAL32 ,VAL32> {
	using TYPE = ARGC<TRUE> ;
} ;

template <>
struct IS_VAL_XYZ<VAL64 ,VAL64> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
struct IS_VAL_XYZ<_ARG1 ,VALX> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
using IS_VAL_XYZ_HELP = typename IS_VAL_XYZ<REMOVE_CVR_TYPE<_ARG1> ,REMOVE_CVR_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class ,class>
struct IS_BYTE_XYZ {
	using TYPE = ARGC<FALSE> ;
} ;

template <>
struct IS_BYTE_XYZ<BYTE ,BYTE> {
	using TYPE = ARGC<TRUE> ;
} ;

template <>
struct IS_BYTE_XYZ<WORD ,WORD> {
	using TYPE = ARGC<TRUE> ;
} ;

template <>
struct IS_BYTE_XYZ<CHAR ,CHAR> {
	using TYPE = ARGC<TRUE> ;
} ;

template <>
struct IS_BYTE_XYZ<DATA ,DATA> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
struct IS_BYTE_XYZ<_ARG1 ,MEGA> {
	using TYPE = U::CONSTEXPR_NOT<IS_CLASS_HELP<_ARG1>> ;
} ;

template <class _ARG1>
using IS_BYTE_XYZ_HELP = typename IS_BYTE_XYZ<REMOVE_CVR_TYPE<_ARG1> ,REMOVE_CVR_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class ,class>
struct IS_STR_XYZ {
	using TYPE = ARGC<FALSE> ;
} ;

template <>
struct IS_STR_XYZ<STRU8 ,STRU8> {
	using TYPE = ARGC<TRUE> ;
} ;

template <>
struct IS_STR_XYZ<STRU16 ,STRU16> {
	using TYPE = ARGC<TRUE> ;
} ;

template <>
struct IS_STR_XYZ<STRU32 ,STRU32> {
	using TYPE = ARGC<TRUE> ;
} ;

template <>
struct IS_STR_XYZ<STRA ,STRA> {
	using TYPE = ARGC<TRUE> ;
} ;

template <>
struct IS_STR_XYZ<STRW ,STRW> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
struct IS_STR_XYZ<_ARG1 ,STRX> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
using IS_STR_XYZ_HELP = typename IS_STR_XYZ<REMOVE_CVR_TYPE<_ARG1> ,REMOVE_CVR_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class _ARG1>
using IS_BOOL_HELP = IS_SAME_HELP<REMOVE_CVR_TYPE<_ARG1> ,BOOL> ;

template <class _ARG1>
using IS_EFLAG_HELP = IS_SAME_HELP<REMOVE_CVR_TYPE<_ARG1> ,EFLAG> ;

template <class _ARG1>
using IS_XYZ_HELP = U::CONSTEXPR_OR<IS_VOID_HELP<_ARG1> ,IS_BOOL_HELP<_ARG1> ,IS_EFLAG_HELP<_ARG1> ,IS_VAR_XYZ_HELP<_ARG1> ,IS_VAL_XYZ_HELP<_ARG1> ,IS_BYTE_XYZ_HELP<_ARG1> ,IS_STR_XYZ_HELP<_ARG1>> ;
} ;

namespace U {
template <class ,class>
struct BYTE_BASE ;

template <>
struct BYTE_BASE<ALIGN_OF_TYPE<BYTE> ,SIZE_OF_TYPE<BYTE>> {
	using TYPE = BYTE ;
} ;

template <>
struct BYTE_BASE<ALIGN_OF_TYPE<WORD> ,SIZE_OF_TYPE<WORD>> {
	using TYPE = WORD ;
} ;

template <>
struct BYTE_BASE<ALIGN_OF_TYPE<CHAR> ,SIZE_OF_TYPE<CHAR>> {
	using TYPE = CHAR ;
} ;

template <>
struct BYTE_BASE<ALIGN_OF_TYPE<DATA> ,SIZE_OF_TYPE<DATA>> {
	using TYPE = DATA ;
} ;

template <class _ARG1>
using BYTE_BASE_TYPE = typename BYTE_BASE<ALIGN_OF_TYPE<_ARG1> ,SIZE_OF_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class ,class>
struct TEXT_BASE ;

template <>
struct TEXT_BASE<ALIGN_OF_TYPE<STRU8> ,SIZE_OF_TYPE<STRU8>> {
	using TYPE = STRU8 ;
} ;

template <>
struct TEXT_BASE<ALIGN_OF_TYPE<STRU16> ,SIZE_OF_TYPE<STRU16>> {
	using TYPE = STRU16 ;
} ;

template <>
struct TEXT_BASE<ALIGN_OF_TYPE<STRU32> ,SIZE_OF_TYPE<STRU32>> {
	using TYPE = STRU32 ;
} ;

template <class _ARG1>
using TEXT_BASE_TYPE = typename TEXT_BASE<ALIGN_OF_TYPE<_ARG1> ,SIZE_OF_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class ,class>
struct IS_DEFAULT_CONSTRUCTIBLE {
	using TYPE = ARGC<FALSE> ;
} ;

template <class _ARG1>
struct IS_DEFAULT_CONSTRUCTIBLE<_ARG1 ,NONE> {
	using TYPE = U::CONSTEXPR_AND<ARGC<(api::is_default_constructible<_ARG1>::value)> ,ARGC<(api::is_nothrow_destructible<_ARG1>::value)>> ;
} ;

template <class _ARG1>
using IS_DEFAULT_CONSTRUCTIBLE_HELP = typename IS_DEFAULT_CONSTRUCTIBLE<_ARG1 ,NONE>::TYPE ;
} ;

namespace U {
template <class ,class ,class>
struct IS_CONSTRUCTIBLE {
	using TYPE = ARGC<FALSE> ;
} ;

template <class _ARG1 ,class... _ARGS>
struct IS_CONSTRUCTIBLE<_ARG1 ,ARGVS<_ARGS...> ,NONE> {
	using TYPE = U::CONSTEXPR_AND<ARGC<(api::is_constructible<_ARG1 ,_ARGS...>::value)> ,ARGC<(api::is_nothrow_destructible<_ARG1>::value)>> ;
} ;

template <class _ARG1 ,class _ARG2>
using IS_CONSTRUCTIBLE_HELP = typename IS_CONSTRUCTIBLE<_ARG1 ,_ARG2 ,NONE>::TYPE ;
} ;

namespace U {
template <class ,class>
struct IS_COPY_CONSTRUCTIBLE {
	using TYPE = ARGC<FALSE> ;
} ;

template <class _ARG1>
struct IS_COPY_CONSTRUCTIBLE<_ARG1 ,NONE> {
	using TYPE = U::CONSTEXPR_AND<ARGC<(api::is_copy_constructible<_ARG1>::value)> ,ARGC<(api::is_copy_assignable<_ARG1>::value)> ,ARGC<(api::is_nothrow_move_constructible<_ARG1>::value)> ,ARGC<(api::is_nothrow_move_assignable<_ARG1>::value)>> ;
} ;

template <class _ARG1>
using IS_COPY_CONSTRUCTIBLE_HELP = typename IS_COPY_CONSTRUCTIBLE<_ARG1 ,NONE>::TYPE ;
} ;

namespace U {
template <class ,class>
struct IS_MOVE_CONSTRUCTIBLE {
	using TYPE = ARGC<FALSE> ;
} ;

template <class _ARG1>
struct IS_MOVE_CONSTRUCTIBLE<_ARG1 ,NONE> {
	using TYPE = U::CONSTEXPR_AND<ARGC<(api::is_nothrow_move_constructible<_ARG1>::value)> ,ARGC<(api::is_nothrow_move_assignable<_ARG1>::value)>> ;
} ;

template <class _ARG1>
using IS_MOVE_CONSTRUCTIBLE_HELP = typename IS_MOVE_CONSTRUCTIBLE<_ARG1 ,NONE>::TYPE ;
} ;

namespace U {
template <class ,class ,class>
struct IS_CONVERTIBLE {
	using TYPE = ARGC<FALSE> ;
} ;

template <class _ARG1 ,class _ARG2>
struct IS_CONVERTIBLE<_ARG1 ,_ARG2 ,NONE> {
	using TYPE = ARGC<(api::is_convertible<_ARG1 ,_ARG2>::value)> ;
} ;

template <class _ARG1 ,class _ARG2>
using IS_CONVERTIBLE_HELP = typename IS_CONVERTIBLE<_ARG1 ,_ARG2 ,NONE>::TYPE ;
} ;

namespace U {
template <class ,class ,class>
struct IS_BASE_OF {
	using TYPE = ARGC<FALSE> ;
} ;

template <class _ARG1 ,class _ARG2>
struct IS_BASE_OF<_ARG1 ,_ARG2 ,NONE> {
	using TYPE = ARGC<(api::is_base_of<_ARG1 ,_ARG2>::value)> ;
} ;

template <class _ARG1 ,class _ARG2>
using IS_BASE_OF_HELP = typename IS_BASE_OF<REMOVE_CVR_TYPE<_ARG1> ,REMOVE_CVR_TYPE<_ARG2> ,NONE>::TYPE ;
} ;

namespace U {
template <class ,class ,class>
struct IS_INTERFACE {
	using TYPE = ARGC<FALSE> ;
} ;

template <class _ARG1 ,class _ARG2>
struct IS_INTERFACE<_ARG1 ,_ARG2 ,ENABLE_TYPE<U::CONSTEXPR_AND<IS_BASE_OF_HELP<_ARG2 ,_ARG1> ,U::CONSTEXPR_EQUAL<ALIGN_OF_TYPE<_ARG1> ,ALIGN_OF_TYPE<_ARG2>> ,U::CONSTEXPR_EQUAL<SIZE_OF_TYPE<_ARG1> ,SIZE_OF_TYPE<_ARG2>>>>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
using IS_INTERFACE_HELP = typename IS_INTERFACE<REMOVE_CVR_TYPE<_ARG1> ,Interface ,NONE>::TYPE ;
} ;

namespace U {
template <class _ARG1>
struct FORWARD_TRAITS {
	//@warn: should not be used
	using TYPE = DEF<const _ARG1 &> ;
} ;

template <class _ARG1>
struct FORWARD_TRAITS<_ARG1 &> {
	using TYPE = DEF<_ARG1 &> ;
} ;

template <class _ARG1>
struct FORWARD_TRAITS<_ARG1 &&> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using FORWARD_TRAITS_TYPE = typename FORWARD_TRAITS<_ARG1>::TYPE ;
} ;

namespace U {
template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS {
	using TYPE = REMOVE_REFERENCE_TYPE<_ARG1> ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,const _ARG2> {
	using TYPE = DEF<const REMOVE_REFERENCE_TYPE<_ARG1>> ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,volatile _ARG2> {
	using TYPE = DEF<volatile REMOVE_REFERENCE_TYPE<_ARG1>> ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,const volatile _ARG2> {
	using TYPE = DEF<const volatile REMOVE_REFERENCE_TYPE<_ARG1>> ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,_ARG2 &> {
	using TYPE = DEF<REMOVE_REFERENCE_TYPE<_ARG1> &> ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,const _ARG2 &> {
	using TYPE = DEF<const REMOVE_REFERENCE_TYPE<_ARG1> &> ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,volatile _ARG2 &> {
	using TYPE = DEF<volatile REMOVE_REFERENCE_TYPE<_ARG1> &> ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,const volatile _ARG2 &> {
	using TYPE = DEF<const volatile REMOVE_REFERENCE_TYPE<_ARG1> &> ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,_ARG2 &&> {
	using TYPE = DEF<REMOVE_REFERENCE_TYPE<_ARG1> &&> ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,const _ARG2 &&> {
	using TYPE = DEF<const REMOVE_REFERENCE_TYPE<_ARG1> &&> ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,volatile _ARG2 &&> {
	using TYPE = DEF<volatile REMOVE_REFERENCE_TYPE<_ARG1> &&> ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,const volatile _ARG2 &&> {
	using TYPE = DEF<const volatile REMOVE_REFERENCE_TYPE<_ARG1> &&> ;
} ;

template <class _ARG1 ,class _ARG2>
using CAST_TRAITS_TYPE = typename CAST_TRAITS<_ARG1 ,_ARG2>::TYPE ;
} ;

namespace U {
template <class ,class ,class ,class>
struct IS_SAFE_ALIASING {
	using TYPE = ARGC<FALSE> ;
} ;

template <class _ARG1>
struct IS_SAFE_ALIASING<_ARG1 ,TEMP<_ARG1> ,NONE ,ARGC<1>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
struct IS_SAFE_ALIASING<TEMP<_ARG1> ,_ARG1 ,NONE ,ARGC<1>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
struct IS_SAFE_ALIASING<ARR<_ARG1> ,ARR<TEMP<_ARG1>> ,NONE ,ARGC<1>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
struct IS_SAFE_ALIASING<ARR<TEMP<_ARG1>> ,ARR<_ARG1> ,NONE ,ARGC<1>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1 ,class _ARG2 ,class _ARG3>
struct IS_SAFE_ALIASING<_ARG1 ,_ARG2 ,_ARG3 ,ARGC<1>> {
	using TYPE = typename IS_SAFE_ALIASING<_ARG1 ,_ARG2 ,_ARG3 ,ARGC<2>>::TYPE ;
} ;

template <class _ARG1 ,class _ARG2>
struct IS_SAFE_ALIASING<TEMP<_ARG1> ,TEMP<_ARG2> ,ENABLE_TYPE<U::CONSTEXPR_AND<U::CONSTEXPR_EQUAL<U::CONSTEXPR_MOD<ALIGN_OF_TYPE<TEMP<_ARG2>> ,ALIGN_OF_TYPE<TEMP<_ARG1>>> ,ZERO> ,U::CONSTEXPR_COMPR_NLT<SIZE_OF_TYPE<TEMP<_ARG2>> ,SIZE_OF_TYPE<TEMP<_ARG1>>>>> ,ARGC<2>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1 ,class _ARG2 ,class _ARG3>
struct IS_SAFE_ALIASING<_ARG1 ,_ARG2 ,_ARG3 ,ARGC<2>> {
	using TYPE = typename IS_SAFE_ALIASING<_ARG1 ,_ARG2 ,_ARG3 ,ARGC<3>>::TYPE ;
} ;

template <class _ARG1>
struct IS_SAFE_ALIASING<ARR<BYTE> ,ARR<_ARG1> ,ENABLE_TYPE<IS_XYZ_HELP<_ARG1>> ,ARGC<3>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1 ,class _ARG2 ,class _ARG3>
struct IS_SAFE_ALIASING<_ARG1 ,_ARG2 ,_ARG3 ,ARGC<3>> {
	using TYPE = typename IS_SAFE_ALIASING<_ARG1 ,_ARG2 ,_ARG3 ,ARGC<4>>::TYPE ;
} ;

//@info: compatible for old c api
template <>
struct IS_SAFE_ALIASING<ARR<STRA> ,ARR<BYTE> ,NONE ,ARGC<4>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1 ,class _ARG2 ,class _ARG3>
struct IS_SAFE_ALIASING<_ARG1 ,_ARG2 ,_ARG3 ,ARGC<4>> {
	using TYPE = typename IS_SAFE_ALIASING<_ARG1 ,_ARG2 ,_ARG3 ,ARGC<5>>::TYPE ;
} ;

template <class _ARG1>
struct IS_SAFE_ALIASING<_ARG1 ,NONE ,NONE ,ARGC<5>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1 ,class _ARG2>
using IS_SAFE_ALIASING_HELP = typename IS_SAFE_ALIASING<REMOVE_CVR_TYPE<_ARG1> ,REMOVE_CVR_TYPE<_ARG2> ,NONE ,ARGC<1>>::TYPE ;
} ;

namespace U {
template <class...>
struct IS_ALL_SAME {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1 ,class _ARG2 ,class... _ARGS>
struct IS_ALL_SAME<_ARG1 ,_ARG2 ,_ARGS...> {
	using R1X = IS_SAME_HELP<_ARG1 ,_ARG2> ;
	using R2X = typename IS_ALL_SAME<_ARG1 ,_ARGS...>::TYPE ;
	using TYPE = CONSTEXPR_AND<R1X ,R2X> ;
} ;

template <class... _ARGS>
using IS_ALL_SAME_HELP = typename IS_ALL_SAME<_ARGS...>::TYPE ;
} ;

namespace U {
template <class...>
struct IS_ANY_SAME {
	using TYPE = ARGC<FALSE> ;
} ;

template <class _ARG1 ,class _ARG2 ,class... _ARGS>
struct IS_ANY_SAME<_ARG1 ,_ARG2 ,_ARGS...> {
	using R1X = IS_SAME_HELP<_ARG1 ,_ARG2> ;
	using R2X = typename IS_ANY_SAME<_ARG1 ,_ARGS...>::TYPE ;
	using R3X = typename IS_ANY_SAME<_ARG2 ,_ARGS...>::TYPE ;
	using TYPE = U::CONSTEXPR_OR<R1X ,R2X ,R3X> ;
} ;

template <class... _ARGS>
using IS_ANY_SAME_HELP = typename IS_ANY_SAME<_ARGS...>::TYPE ;
} ;
#endif

using U::ARGC_TYPE ;
using U::ENABLE_TYPE ;
using U::DEPENDENT_TYPE ;
using U::CONDITIONAL_TYPE ;
using U::IS_SAME_HELP ;
using U::REMOVE_REFERENCE_TYPE ;
using U::IS_REFERENCE_HELP ;
using U::IS_LVALUE_REFERENCE_HELP ;
using U::IS_RVALUE_REFERENCE_HELP ;
using U::REMOVE_CONST_TYPE ;
using U::IS_CONST_HELP ;
using U::REMOVE_VOLATILE_TYPE ;
using U::IS_VOLATILE_HELP ;
using U::REMOVE_CVR_TYPE ;
using U::REMOVE_POINTER_TYPE ;
using U::IS_POINTER_HELP ;
using U::REMOVE_ARRAY_TYPE ;
using U::ARRAY_BIND_TYPE ;
using U::IS_ARRAY_HELP ;
using U::REMOVE_MEMPTR_TYPE ;
using U::MEMPTR_CLASS_TYPE ;
using U::IS_MEMPTR_HELP ;
using U::REMOVE_TEMP_TYPE ;
using U::IS_PLACEHOLDER_HELP ;
using U::REMOVE_FUNCATTR_TYPE ;
using U::REMOVE_FUNCTION_TYPE ;
using U::IS_FUNCTION_HELP ;
using U::FUNCTION_PARAMS_TYPE ;
using U::FUNCTION_BIND_TYPE ;
using U::IS_CLASS_HELP ;
using U::IS_TRIVIAL_HELP ;
using U::IS_COMPLETE_HELP ;
using U::IS_TEMPLATE_HELP ;
using U::TEMPLATE_PARAMS_TYPE ;
using U::SIZE_OF_TYPE ;
using U::ALIGN_OF_TYPE ;
using U::COUNT_OF_TYPE ;
using U::CAPACITY_OF_TYPE ;
using U::IS_ARRAY_OF_HELP ;
using U::FUNCTION_OF_TYPE ;
using U::RESULT_OF_TYPE ;
using U::REPEAT_PARAMS_TYPE ;
using U::RANGE_PARAMS_TYPE ;
using U::PARAMS_ONE_TYPE ;
using U::PARAMS_REST_TYPE ;
using U::PARAMS_CAT_TYPE ;
using U::INDEX_OF_TYPE ;
using U::INDEX_TO_TYPE ;
using U::IS_VOID_HELP ;
using U::IS_VAR_XYZ_HELP ;
using U::IS_VAL_XYZ_HELP ;
using U::IS_BYTE_XYZ_HELP ;
using U::IS_STR_XYZ_HELP ;
using U::IS_XYZ_HELP ;
using U::BYTE_BASE_TYPE ;
using U::TEXT_BASE_TYPE ;
using U::IS_DEFAULT_CONSTRUCTIBLE_HELP ;
using U::IS_CONSTRUCTIBLE_HELP ;
using U::IS_COPY_CONSTRUCTIBLE_HELP ;
using U::IS_MOVE_CONSTRUCTIBLE_HELP ;
using U::IS_CONVERTIBLE_HELP ;
using U::IS_BASE_OF_HELP ;
using U::IS_INTERFACE_HELP ;
using U::FORWARD_TRAITS_TYPE ;
using U::CAST_TRAITS_TYPE ;
using U::IS_SAFE_ALIASING_HELP ;
using U::IS_ALL_SAME_HELP ;
using U::IS_ANY_SAME_HELP ;

namespace U {
template <class _ARG1 ,class _ARG2>
struct CONSTEXPR_MAX {
	imports constexpr VAR compile () {
		using R1X = CONSTEXPR_COMPR_LT<_ARG1 ,_ARG2> ;
		using R2X = CONDITIONAL_TYPE<R1X ,_ARG2 ,_ARG1> ;
		return R2X::compile () ;
	}
} ;

template <class _ARG1 ,class _ARG2>
struct CONSTEXPR_MIN {
	imports constexpr VAR compile () {
		using R1X = CONSTEXPR_COMPR_LT<_ARG1 ,_ARG2> ;
		using R2X = CONDITIONAL_TYPE<R1X ,_ARG1 ,_ARG2> ;
		return R2X::compile () ;
	}
} ;

template <class _ARG1 ,class _ARG2 ,class _ARG3>
struct CONSTEXPR_RANGE_CHECK {
	imports constexpr VAR compile () {
		using R1X = CONSTEXPR_COMPR_NLT<_ARG1 ,_ARG2> ;
		using R2X = CONSTEXPR_COMPR_LT<_ARG1 ,_ARG3> ;
		using R3X = CONSTEXPR_AND<R1X ,R2X> ;
		return R3X::compile () ;
	}
} ;
} ;

template <>
struct ARGV<ARGVP<ZERO>> {
	_STATIC_WARNING_ ("noop") ;
} ;

template <class UNIT>
struct ARGV<ARGVP<UNIT>> :
	delegate public ARGV<ARGVP<ARGC_TYPE<U::CONSTEXPR_DECREASE<UNIT>>>> {
	_STATIC_ASSERT_ (U::CONSTEXPR_COMPR_GT<UNIT ,ZERO>::compile ()) ;
} ;

static constexpr auto ARGVP0 = ARGV<ARGVP<ZERO>> {} ;
static constexpr auto ARGVP1 = ARGV<ARGVP<ARGC<1>>> {} ;
static constexpr auto ARGVP2 = ARGV<ARGVP<ARGC<2>>> {} ;
static constexpr auto ARGVP3 = ARGV<ARGVP<ARGC<3>>> {} ;
static constexpr auto ARGVP4 = ARGV<ARGVP<ARGC<4>>> {} ;
static constexpr auto ARGVP5 = ARGV<ARGVP<ARGC<5>>> {} ;
static constexpr auto ARGVP6 = ARGV<ARGVP<ARGC<6>>> {} ;
static constexpr auto ARGVP7 = ARGV<ARGVP<ARGC<7>>> {} ;
static constexpr auto ARGVP8 = ARGV<ARGVP<ARGC<8>>> {} ;
static constexpr auto ARGVP9 = ARGV<ARGVP<ARGC<9>>> {} ;
static constexpr auto ARGVPX = ARGV<ARGVP<ARGC<10>>> {} ;

namespace U {
struct OPERATOR_FOR_ONCE {
	inline BOOL operator() (const BOOL &) const {
		return FALSE ;
	}

	inline BOOL operator() (BOOL &flag) const {
		flag = FALSE ;
		return FALSE ;
	}
} ;
} ;

static constexpr auto FOR_ONCE = U::OPERATOR_FOR_ONCE {} ;

namespace U {
struct OPERATOR_DEREF {
	template <class _ARG1>
	inline _ARG1 &operator[] (const PTR<_ARG1> &address) const {
		return (*address) ;
	}
} ;

struct OPERATOR_DEPTR {
	template <class _ARG1>
	inline PTR<_ARG1> operator[] (_ARG1 &object) const {
		return (&object) ;
	}
} ;
} ;

static constexpr auto DEREF = U::OPERATOR_DEREF {} ;
static constexpr auto DEPTR = U::OPERATOR_DEPTR {} ;

namespace U {
struct OPERATOR_PTRTOARR {
	template <class _ARG1>
	inline ARR<_ARG1> &operator[] (const PTR<_ARG1> &address) const {
		return DEREF[PTR<ARR<_ARG1>> (address)] ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<IS_ARRAY_OF_HELP<REMOVE_ARRAY_TYPE<_ARG1> ,_ARG1>>>
	inline ARR<REMOVE_ARRAY_TYPE<_ARG1>> &operator[] (_ARG1 &object) const {
		return DEREF[PTR<ARR<REMOVE_ARRAY_TYPE<_ARG1>>> (DEPTR[object])] ;
	}
} ;
} ;

static constexpr auto PTRTOARR = U::OPERATOR_PTRTOARR {} ;

template <class _ARG1>
inline _ARG1 &_NULL_ (const ARGVF<_ARG1> &) {
	return DEREF[PTR<REMOVE_REFERENCE_TYPE<_ARG1>> (NULL)] ;
}

template <class _ARG1>
inline LENGTH _ADDRESS_ (const PTR<_ARG1> &address) {
	_STATIC_ASSERT_ (IS_SAME_HELP<REMOVE_CVR_TYPE<_ARG1> ,_ARG1>::compile ()) ;
#ifdef __CSC_COMPILER_GNUC__
	asm volatile ("" ::: "memory") ;
#endif
	return LENGTH (address) ;
}

template <class _ARG1>
inline LENGTH _ADDRESS_ (const PTR<const _ARG1> &address) {
	_STATIC_ASSERT_ (IS_SAME_HELP<REMOVE_CVR_TYPE<_ARG1> ,_ARG1>::compile ()) ;
	return LENGTH (address) ;
}

inline INDEX _ALIGNAS_ (const INDEX &base ,const LENGTH &align_) {
	return base + (align_ - base % align_) % align_ ;
}

//@warn: not type-safe ,be careful about strict-aliasing
template <class _ARG1 ,class _ARG2>
inline CAST_TRAITS_TYPE<_ARG1 ,_ARG2> &_CAST_ (const ARGVF<_ARG1> & ,_ARG2 &object) {
	_STATIC_ASSERT_ (U::CONSTEXPR_OR<U::CONSTEXPR_NOT<IS_POINTER_HELP<_ARG1>> ,IS_SAME_HELP<REMOVE_CVR_TYPE<_ARG2> ,TEMP<_ARG1>>>::compile ()) ;
	_STATIC_ASSERT_ (U::CONSTEXPR_OR<U::CONSTEXPR_NOT<IS_POINTER_HELP<_ARG2>> ,IS_SAME_HELP<REMOVE_CVR_TYPE<_ARG1> ,TEMP<_ARG2>>>::compile ()) ;
	_STATIC_ASSERT_ (_ALIGNOF_ (_ARG2) % _ALIGNOF_ (_ARG1) == 0) ;
	_STATIC_ASSERT_ (_SIZEOF_ (_ARG1) == _SIZEOF_ (_ARG2)) ;
	const auto r1x = _ADDRESS_ (DEPTR[object]) ;
	const auto r2x = reinterpret_cast<PTR<CAST_TRAITS_TYPE<_ARG1 ,_ARG2>>> (r1x) ;
	return DEREF[r2x] ;
}

template <class _ARG1>
inline void _ZERO_ (_ARG1 &object) {
	_STATIC_ASSERT_ (IS_TRIVIAL_HELP<_ARG1>::compile ()) ;
	_CAST_ (ARGV<TEMP<_ARG1>>::ID ,object) = {0} ;
}

template <class _ARG1>
inline REMOVE_CVR_TYPE<_ARG1> _COPY_ (const _ARG1 &object) {
	return object ;
}

template <class _ARG1>
inline REMOVE_REFERENCE_TYPE<_ARG1> &&_MOVE_ (_ARG1 &&object) {
	return static_cast<REMOVE_REFERENCE_TYPE<_ARG1> &&> (object) ;
}

template <class _ARG1>
inline _ARG1 &_FORWARD_ (const ARGVF<_ARG1> & ,REMOVE_CVR_TYPE<_ARG1> &object) {
	return static_cast<_ARG1 &> (object) ;
}

template <class _ARG1>
inline _ARG1 &&_FORWARD_ (const ARGVF<_ARG1 &&> & ,REMOVE_CVR_TYPE<_ARG1> &object) {
	return static_cast<_ARG1 &&> (object) ;
}

template <class _ARG1>
inline const _ARG1 &_FORWARD_ (const ARGVF<_ARG1> & ,const REMOVE_CVR_TYPE<_ARG1> &object) {
	return static_cast<const _ARG1 &> (object) ;
}

template <class _ARG1>
inline _ARG1 &&_FORWARD_ (const ARGVF<_ARG1> & ,REMOVE_CVR_TYPE<_ARG1> &&object) {
	_STATIC_ASSERT_ (U::CONSTEXPR_NOT<IS_LVALUE_REFERENCE_HELP<_ARG1>>::compile ()) ;
	return static_cast<_ARG1 &&> (object) ;
}

template <class _ARG1>
inline void _SWAP_ (_ARG1 &lhs ,_ARG1 &rhs) {
	_STATIC_ASSERT_ (IS_MOVE_CONSTRUCTIBLE_HELP<_ARG1>::compile ()) ;
	auto rax = _MOVE_ (lhs) ;
	lhs = _MOVE_ (rhs) ;
	rhs = _MOVE_ (rax) ;
}

template <class _ARG1 ,class _ARG2>
inline REMOVE_CVR_TYPE<_ARG1> _BITWISE_CAST_ (const ARGVF<_ARG1> & ,const _ARG2 &object) {
	using R1X = TEMP<BYTE[_SIZEOF_ (_ARG1)]> ;
	_STATIC_ASSERT_ (U::CONSTEXPR_NOT<IS_POINTER_HELP<_ARG1>>::compile ()) ;
	_STATIC_ASSERT_ (U::CONSTEXPR_NOT<IS_POINTER_HELP<_ARG2>>::compile ()) ;
	_STATIC_ASSERT_ (IS_TRIVIAL_HELP<_ARG1>::compile ()) ;
	_STATIC_ASSERT_ (IS_TRIVIAL_HELP<_ARG2>::compile ()) ;
	_STATIC_ASSERT_ (_SIZEOF_ (_ARG1) == _SIZEOF_ (_ARG2)) ;
	TEMP<_ARG1> ret ;
	_ZERO_ (ret) ;
	_CAST_ (ARGV<R1X>::ID ,ret) = _CAST_ (ARGV<R1X>::ID ,object) ;
	return _MOVE_ (_CAST_ (ARGV<_ARG1>::ID ,ret)) ;
}

//@warn: not type-safe ,be careful about strict-aliasing
template <class _ARG1 ,class _ARG2>
inline PTR<CAST_TRAITS_TYPE<_ARG1 ,_ARG2>> _POINTER_CAST_ (const ARGVF<_ARG1> & ,const PTR<_ARG2> &pointer) {
	using R1X = PTR<CAST_TRAITS_TYPE<_ARG1 ,_ARG2>> ;
	_STATIC_ASSERT_ (IS_SAFE_ALIASING_HELP<_ARG1 ,_ARG2>::compile ()) ;
	if (pointer == NULL)
		return NULL ;
	const auto r1x = _ALIGNOF_ (CONDITIONAL_TYPE<IS_SAME_HELP<REMOVE_CVR_TYPE<_ARG1> ,NONE> ,BYTE ,_ARG1>) ;
	const auto r2x = _ADDRESS_ (pointer) ;
	if (r2x % r1x != 0)
		return NULL ;
	const auto r3x = _CAST_ (ARGV<TEMP<R1X>>::ID ,r2x) ;
	return _CAST_ (ARGV<R1X>::ID ,r3x) ;
}

template <class _ARG1>
inline PTR<_ARG1> _UNSAFE_POINTER_CAST_ (const ARGVF<_ARG1> & ,const LENGTH &address) {
	const auto r1x = DEPTR[_NULL_ (ARGV<BYTE>::ID)] + address ;
	const auto r2x = _FORWARD_ (ARGV<PTR<NONE>>::ID ,r1x) ;
	return _POINTER_CAST_ (ARGV<_ARG1>::ID ,r2x) ;
}

template <class _ARG1 ,class _ARG2 ,class _ARG3>
inline CAST_TRAITS_TYPE<_ARG2 ,_ARG3> &_OFFSET_ (const MEMPTR<_ARG1 ,_ARG2> &mptr ,_ARG3 &mref) {
	_STATIC_ASSERT_ (IS_SAME_HELP<REMOVE_CVR_TYPE<_ARG1> ,REMOVE_CVR_TYPE<_ARG3>>::compile ()) ;
	const auto r1x = DEPTR[(_NULL_ (ARGV<_ARG2>::ID).*mptr)] ;
	const auto r2x = _ADDRESS_ (DEPTR[mref]) - _ADDRESS_ (r1x) ;
	const auto r3x = _UNSAFE_POINTER_CAST_ (ARGV<CAST_TRAITS_TYPE<_ARG2 ,_ARG3>>::ID ,r2x) ;
	return DEREF[r3x] ;
}

template <class _ARG1 ,class... _ARGS>
inline void _CREATE_ (const PTR<TEMP<_ARG1>> &address ,_ARGS &&...initval) {
	_STATIC_ASSERT_ (IS_CONSTRUCTIBLE_HELP<_ARG1 ,ARGVS<_ARGS &&...>>::compile ()) ;
	_STATIC_ASSERT_ (U::CONSTEXPR_NOT<IS_ARRAY_HELP<_ARG1>>::compile ()) ;
	const auto r1x = _POINTER_CAST_ (ARGV<_ARG1>::ID ,address) ;
	if (r1x == NULL)
		return ;
	_ZERO_ (DEREF[address]) ;
	new (r1x) _ARG1 (_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) ;
}

template <class _ARG1>
inline void _DESTROY_ (const PTR<TEMP<_ARG1>> &address) {
	_STATIC_ASSERT_ (U::CONSTEXPR_NOT<IS_ARRAY_HELP<_ARG1>>::compile ()) ;
	const auto r1x = _POINTER_CAST_ (ARGV<_ARG1>::ID ,address) ;
	if (r1x == NULL)
		return ;
	DEREF[r1x].~_ARG1 () ;
}

template <class>
class PhanRef ;

template <class _ARG1 ,class _RET = REMOVE_CVR_TYPE<PhanRef<_ARG1>>>
inline _RET _BYREF_ (_ARG1 &object) {
	using R1X = DEPENDENT_TYPE<PhanRef<_ARG1> ,struct ANONYMOUS> ;
	return R1X::make (object) ;
}

template <class _ARG1>
inline REMOVE_CVR_TYPE<_ARG1> _ABS_ (const _ARG1 &val) {
	if (val < _ARG1 (0))
		return -val ;
	return +val ;
}

template <class _ARG1>
inline _ARG1 &_MIN_ (_ARG1 &lhs ,_ARG1 &rhs) {
	if (rhs < lhs)
		return rhs ;
	return lhs ;
}

template <class _ARG1>
inline _ARG1 &_MAX_ (_ARG1 &lhs ,_ARG1 &rhs) {
	if (lhs < rhs)
		return rhs ;
	return lhs ;
}

inline VAR _EBOOL_ (const BOOL &flag) {
	if (flag)
		return VAR (1) ;
	return VAR_ZERO ;
}

template <class UNIT>
struct TEMP {
	_STATIC_ASSERT_ (U::CONSTEXPR_NOT<IS_REFERENCE_HELP<UNIT>>::compile ()) ;
	alignas (UNIT) DEF<BYTE[_SIZEOF_ (UNIT)]> unused ;
} ;

class EqualInvokeProc ;
class ComprInvokeProc ;
class HashInvokeProc ;

template <>
struct PACK<> {
	BOOL equal (const PACK &that) const {
		return TRUE ;
	}

	inline BOOL operator== (const PACK &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const PACK &that) const {
		return !equal (that) ;
	}

	FLAG compr (const PACK &that) const {
		return FLAG (0) ;
	}

	inline FLAG operator< (const PACK &that) const {
		return compr (that) < 0 ;
	}

	inline FLAG operator>= (const PACK &that) const {
		return compr (that) >= 0 ;
	}

	inline FLAG operator> (const PACK &that) const {
		return compr (that) > 0 ;
	}

	inline FLAG operator<= (const PACK &that) const {
		return compr (that) <= 0 ;
	}

	FLAG hash () const {
		return FLAG (0) ;
	}
} ;

template <class UNIT1>
struct PACK<UNIT1> {
	UNIT1 mP1 ;

	BOOL equal (const PACK &that) const {
		using R1X = DEPENDENT_TYPE<EqualInvokeProc ,struct ANONYMOUS> ;
		if (!R1X::invoke (mP1 ,that.mP1))
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const PACK &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const PACK &that) const {
		return !equal (that) ;
	}

	FLAG compr (const PACK &that) const {
		using R2X = DEPENDENT_TYPE<ComprInvokeProc ,struct ANONYMOUS> ;
		const auto r1x = R2X::invoke (mP1 ,that.mP1) ;
		if (r1x != 0)
			return r1x ;
		return FLAG (0) ;
	}

	inline FLAG operator< (const PACK &that) const {
		return compr (that) < 0 ;
	}

	inline FLAG operator>= (const PACK &that) const {
		return compr (that) >= 0 ;
	}

	inline FLAG operator> (const PACK &that) const {
		return compr (that) > 0 ;
	}

	inline FLAG operator<= (const PACK &that) const {
		return compr (that) <= 0 ;
	}

	FLAG hash () const {
		using R1X = DEPENDENT_TYPE<HashInvokeProc ,struct ANONYMOUS> ;
		const auto r1x = R1X::invoke (mP1) ;
		return r1x ;
	}
} ;

template <class UNIT1 ,class UNIT2>
struct PACK<UNIT1 ,UNIT2> {
	UNIT1 mP1 ;
	UNIT2 mP2 ;

	BOOL equal (const PACK &that) const {
		using R1X = DEPENDENT_TYPE<EqualInvokeProc ,struct ANONYMOUS> ;
		if (!R1X::invoke (mP1 ,that.mP1))
			return FALSE ;
		if (!R1X::invoke (mP2 ,that.mP2))
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const PACK &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const PACK &that) const {
		return !equal (that) ;
	}

	FLAG compr (const PACK &that) const {
		using R1X = DEPENDENT_TYPE<ComprInvokeProc ,struct ANONYMOUS> ;
		const auto r1x = R1X::invoke (mP1 ,that.mP1) ;
		if (r1x != 0)
			return r1x ;
		const auto r2x = R1X::invoke (mP2 ,that.mP2) ;
		if (r2x != 0)
			return r2x ;
		return FLAG (0) ;
	}

	inline FLAG operator< (const PACK &that) const {
		return compr (that) < 0 ;
	}

	inline FLAG operator>= (const PACK &that) const {
		return compr (that) >= 0 ;
	}

	inline FLAG operator> (const PACK &that) const {
		return compr (that) > 0 ;
	}

	inline FLAG operator<= (const PACK &that) const {
		return compr (that) <= 0 ;
	}

	FLAG hash () const {
		using R1X = DEPENDENT_TYPE<HashInvokeProc ,struct ANONYMOUS> ;
		const auto r1x = R1X::invoke (mP1) ;
		const auto r2x = R1X::invoke (mP2) ;
		return r1x + r2x ;
	}
} ;

template <class UNIT1 ,class UNIT2 ,class UNIT3>
struct PACK<UNIT1 ,UNIT2 ,UNIT3> {
	UNIT1 mP1 ;
	UNIT2 mP2 ;
	UNIT3 mP3 ;

	BOOL equal (const PACK &that) const {
		using R1X = DEPENDENT_TYPE<EqualInvokeProc ,struct ANONYMOUS> ;
		if (!R1X::invoke (mP1 ,that.mP1))
			return FALSE ;
		if (!R1X::invoke (mP2 ,that.mP2))
			return FALSE ;
		if (!R1X::invoke (mP3 ,that.mP3))
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const PACK &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const PACK &that) const {
		return !equal (that) ;
	}

	FLAG compr (const PACK &that) const {
		using R1X = DEPENDENT_TYPE<ComprInvokeProc ,struct ANONYMOUS> ;
		const auto r1x = R1X::invoke (mP1 ,that.mP1) ;
		if (r1x != 0)
			return r1x ;
		const auto r2x = R1X::invoke (mP2 ,that.mP2) ;
		if (r2x != 0)
			return r2x ;
		const auto r3x = R1X::invoke (mP3 ,that.mP3) ;
		if (r3x != 0)
			return r3x ;
		return FLAG (0) ;
	}

	inline FLAG operator< (const PACK &that) const {
		return compr (that) < 0 ;
	}

	inline FLAG operator>= (const PACK &that) const {
		return compr (that) >= 0 ;
	}

	inline FLAG operator> (const PACK &that) const {
		return compr (that) > 0 ;
	}

	inline FLAG operator<= (const PACK &that) const {
		return compr (that) <= 0 ;
	}

	FLAG hash () const {
		using R1X = DEPENDENT_TYPE<HashInvokeProc ,struct ANONYMOUS> ;
		const auto r1x = R1X::invoke (mP1) ;
		const auto r2x = R1X::invoke (mP2) ;
		const auto r3x = R1X::invoke (mP3) ;
		return r1x + r2x + r3x ;
	}
} ;

class Interface {
public:
	implicit Interface () = default ;

	implicit virtual ~Interface () = default ;

	implicit Interface (const Interface &) = delete ;

	inline Interface &operator= (const Interface &) = delete ;

	implicit Interface (Interface &&) = delete ;

	inline Interface &operator= (Interface &&) = delete ;
} ;

struct TYPEABI {
	LENGTH mAlign ;
	LENGTH mSize ;
	PACK<BOOL[9]> mSign ;
} ;

template <class _ARG1>
inline TYPEABI _TYPEABI_ (const ARGVF<_ARG1> &) {
	using R1X = IS_POINTER_HELP<_ARG1> ;
	using R2X = IS_ARRAY_HELP<_ARG1> ;
	using R3X = IS_MEMPTR_HELP<_ARG1> ;
	using R4X = IS_FUNCTION_HELP<_ARG1> ;
	using R5X = IS_CLASS_HELP<_ARG1> ;
	using R6X = IS_TRIVIAL_HELP<_ARG1> ;
	using R7X = IS_TEMPLATE_HELP<_ARG1> ;
	using R8X = IS_INTERFACE_HELP<_ARG1> ;
	using R9X = IS_XYZ_HELP<_ARG1> ;
	TYPEABI ret ;
	_ZERO_ (ret) ;
	ret.mAlign = _ALIGNOF_ (_ARG1) ;
	ret.mSize = _SIZEOF_ (_ARG1) ;
	ret.mSign.mP1[0] = R1X::compile () ;
	ret.mSign.mP1[1] = R2X::compile () ;
	ret.mSign.mP1[2] = R3X::compile () ;
	ret.mSign.mP1[3] = R4X::compile () ;
	ret.mSign.mP1[4] = R5X::compile () ;
	ret.mSign.mP1[5] = R6X::compile () ;
	ret.mSign.mP1[6] = R7X::compile () ;
	ret.mSign.mP1[7] = R8X::compile () ;
	ret.mSign.mP1[8] = R9X::compile () ;
	return _MOVE_ (ret) ;
}

template <class UNIT>
class TypeInterface :
	delegate private Interface {
	_STATIC_ASSERT_ (IS_SAME_HELP<REMOVE_CVR_TYPE<UNIT> ,UNIT>::compile ()) ;
} ;

template <class _ARG1>
inline FLAG _TYPEMID_ (const ARGVF<_ARG1> &) {
	TypeInterface<REMOVE_CVR_TYPE<_ARG1>> ret ;
	return _MOVE_ (_CAST_ (ARGV<FLAG>::ID ,ret)) ;
}

template <class UNIT = NONE>
class Wrapped ;

template <>
class Wrapped<NONE> {
public:
	implicit Wrapped () = delete ;

	implicit ~Wrapped () = delete ;

	implicit Wrapped (const Wrapped &) = delete ;

	inline Wrapped &operator= (const Wrapped &) = delete ;

	implicit Wrapped (Wrapped &&) = delete ;

	inline Wrapped &operator= (Wrapped &&) = delete ;
} ;

template <class UNIT>
class Wrapped {
protected:
	UNIT mSelf ;

public:
	implicit Wrapped () = delete ;

	implicit ~Wrapped () = delete ;

	implicit Wrapped (const Wrapped &) = delete ;

	inline Wrapped &operator= (const Wrapped &) = delete ;

	implicit Wrapped (Wrapped &&) = delete ;

	inline Wrapped &operator= (Wrapped &&) = delete ;
} ;

class Proxy {
public:
	implicit Proxy () = default ;

	implicit Proxy (const Proxy &) = delete ;

	inline Proxy &operator= (const Proxy &) = delete ;

#ifndef __CSC_CXX_LATEST__
	implicit Proxy (Proxy &&) = default ;

	inline Proxy &operator= (Proxy &&) = delete ;
#endif

#ifdef __CSC_CXX_LATEST__
	implicit Proxy (Proxy &&) = delete ;

	inline Proxy &operator= (Proxy &&) = delete ;
#endif
} ;

template <class SIZE>
class ArrayRange ;

template <>
class ArrayRange<ZERO> :
	delegate private Proxy {
private:
	struct Private {
		class Iterator ;
	} ;

private:
	INDEX mIBegin ;
	INDEX mIEnd ;

public:
	implicit ArrayRange () = delete ;

	explicit ArrayRange (const INDEX &ibegin_ ,const INDEX &iend_) {
		mIBegin = ibegin_ ;
		mIEnd = _MAX_ (ibegin_ ,iend_) ;
	}

	LENGTH size () const {
		return mIEnd - mIBegin ;
	}

	template <class _RET = REMOVE_CVR_TYPE<typename Private::Iterator>>
	_RET begin () const {
		using R1X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::Iterator ;
		return R1X (mIBegin) ;
	}

	template <class _RET = REMOVE_CVR_TYPE<typename Private::Iterator>>
	_RET end () const {
		using R1X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::Iterator ;
		return R1X (mIEnd) ;
	}
} ;

class ArrayRange<ZERO>::Private::Iterator :
	delegate private Proxy {
private:
	INDEX mIndex ;

public:
	implicit Iterator () = delete ;

	explicit Iterator (const INDEX &index) {
		mIndex = index ;
	}

	inline BOOL operator!= (const Iterator &that) const {
		return BOOL (mIndex != that.mIndex) ;
	}

	inline const INDEX &operator* () const leftvalue {
		return mIndex ;
	}

	inline void operator++ () {
		mIndex++ ;
	}
} ;

inline ArrayRange<ZERO> _RANGE_ (const INDEX &ibegin_ ,const INDEX &iend_) {
	return ArrayRange<ZERO> (ibegin_ ,iend_) ;
}

template <class ,class>
class Array ;

template <class _ARG1>
inline ArrayRange<_ARG1> _RANGE_ (const Array<LENGTH ,_ARG1> &range_) {
	using R1X = DEPENDENT_TYPE<ArrayRange<_ARG1> ,struct ANONYMOUS> ;
	return R1X (range_) ;
}

template <class _ARG1>
inline const RESULT_OF_TYPE<_ARG1 ,ARGVS<>> &_CACHE_ (const _ARG1 &proc) {
	_STATIC_ASSERT_ (U::CONSTEXPR_NOT<IS_REFERENCE_HELP<RESULT_OF_TYPE<_ARG1 ,ARGVS<>>>>::compile ()) ;
	_STATIC_ASSERT_ (U::CONSTEXPR_NOT<IS_VOID_HELP<RESULT_OF_TYPE<_ARG1 ,ARGVS<>>>>::compile ()) ;
	static const RESULT_OF_TYPE<_ARG1 ,ARGVS<>> mInstance = proc () ;
	return mInstance ;
}

namespace U {
template <class...>
struct CONSTEXPR_CACHE_STRING_SIZE ;

template <>
struct CONSTEXPR_CACHE_STRING_SIZE<> {
	imports constexpr VAR compile () {
		return LENGTH (1) ;
	}
} ;

template <class _ARG1 ,class... _ARGS>
struct CONSTEXPR_CACHE_STRING_SIZE<_ARG1 ,_ARGS...> {
	imports constexpr VAR compile () {
		using R1X = COUNT_OF_TYPE<_ARG1> ;
		using R2X = CONSTEXPR_CACHE_STRING_SIZE<_ARGS...> ;
		using R3X = CONSTEXPR_ADD<CONSTEXPR_DECREASE<R1X> ,R2X> ;
		return R3X::compile () ;
	}
} ;
} ;

template <class REAL>
class Plain :
	delegate private Proxy {
	_STATIC_ASSERT_ (IS_STR_XYZ_HELP<REAL>::compile ()) ;

private:
	struct Private {
		template <class>
		class PlainString ;
	} ;

private:
	PTR<const ARR<REAL>> mPlain ;
	LENGTH mSize ;

public:
	implicit Plain () = delete ;

	template <class _ARG1 ,class = ENABLE_TYPE<U::CONSTEXPR_AND<IS_CONST_HELP<_ARG1> ,IS_ARRAY_OF_HELP<REAL ,_ARG1>>>>
	implicit Plain (_ARG1 &that) :
		delegate mPlain (DEPTR[PTRTOARR[that]]) ,
		delegate mSize (_COUNTOF_ (_ARG1) - 1) {}

	template <class _ARG1 ,class... _ARGS>
	explicit Plain (const ARGVF<_ARG1> & ,const _ARGS &...text) :
		delegate Plain (cache_string (ARGV<_ARG1>::ID ,text...)) {
		_STATIC_WARNING_ ("noop") ;
	}

	LENGTH size () const {
		return mSize ;
	}

	const ARR<REAL> &to () const leftvalue {
		_STATIC_WARNING_ ("mark") ;
		return DEREF[mPlain] ;
	}

	inline implicit operator const ARR<REAL> & () const leftvalue {
		return self ;
	}

	const REAL &get (const INDEX &index) const leftvalue {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
		return DEREF[mPlain][index] ;
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
	}

	inline const REAL &operator[] (const INDEX &index) const leftvalue {
		return get (index) ;
	}

private:
	template <class _ARG1 ,class... _ARGS ,class _RET = REMOVE_CVR_TYPE<ARRAY_BIND_TYPE<REAL ,U::CONSTEXPR_CACHE_STRING_SIZE<_ARGS...>>>>
	imports const _RET &cache_string (const ARGVF<_ARG1> & ,const _ARGS &...text) {
		using R1X = ARGC_TYPE<U::CONSTEXPR_CACHE_STRING_SIZE<_ARGS...>> ;
		using R2X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template PlainString<R1X> ;
		const auto r1x = R2X (text...) ;
		return _CACHE_ ([&] () {
			return r1x ;
		}) ;
	}
} ;

template <class REAL>
template <class SIZE>
class Plain<REAL>::Private::PlainString {
	_STATIC_ASSERT_ (U::CONSTEXPR_COMPR_GT<SIZE ,ZERO>::compile ()) ;

private:
	using STRING = ARRAY_BIND_TYPE<REAL ,SIZE> ;

private:
	STRING mString ;

public:
	implicit PlainString () = delete ;

	template <class... _ARGS>
	explicit PlainString (const _ARGS &...text) {
		template_write (ARGV<ZERO>::ID ,text...) ;
	}

	const STRING &to () const leftvalue {
		return mString ;
	}

	inline implicit operator const STRING & () const leftvalue {
		return self ;
	}

private:
	template <class _ARG1>
	void template_write (const ARGVF<_ARG1> &) {
		_STATIC_ASSERT_ (U::CONSTEXPR_EQUAL<_ARG1 ,U::CONSTEXPR_DECREASE<SIZE>>::compile ()) ;
		mString[_ARG1::compile ()] = 0 ;
	}

	template <class _ARG1 ,class _ARG2 ,class... _ARGS>
	void template_write (const ARGVF<_ARG1> & ,const _ARG2 &text_one ,const _ARGS &...text_rest) {
		using R1X = U::CONSTEXPR_ADD<_ARG1 ,U::CONSTEXPR_DECREASE<COUNT_OF_TYPE<_ARG2>>> ;
		_STATIC_ASSERT_ (U::CONSTEXPR_RANGE_CHECK<_ARG1 ,ZERO ,SIZE>::compile ()) ;
		_STATIC_ASSERT_ (U::CONSTEXPR_OR<IS_ARRAY_OF_HELP<STRX ,_ARG2> ,IS_ARRAY_OF_HELP<STRA ,_ARG2> ,IS_ARRAY_OF_HELP<STRW ,_ARG2>>::compile ()) ;
		for (auto &&i : _RANGE_ (0 ,_COUNTOF_ (_ARG2) - 1))
			mString[i + _ARG1::compile ()] = REAL (text_one[i]) ;
		template_write (ARGV<R1X>::ID ,text_rest...) ;
	}
} ;

class Exception final {
private:
	PTR<const ARR<STR>> mWhat ;

public:
	implicit Exception () = delete ;

	explicit Exception (const Plain<STR> &what_) {
		mWhat = DEPTR[what_.self] ;
	}

	implicit Exception (const Exception &) = default ;

	inline Exception &operator= (const Exception &) = default ;

	implicit Exception (Exception &&) = default ;

	inline Exception &operator= (Exception &&) = default ;

	const ARR<STR> &what () const leftvalue {
		return DEREF[mWhat] ;
	}

	void raise[[noreturn]] () const {
		throw DEREF[this] ;
	}
} ;

template <class _ARG1>
inline RESULT_OF_TYPE<_ARG1 ,ARGVS<>> _CALL_ (const _ARG1 &proc) {
	_STATIC_ASSERT_ (U::CONSTEXPR_NOT<IS_REFERENCE_HELP<RESULT_OF_TYPE<_ARG1 ,ARGVS<>>>>::compile ()) ;
	return proc () ;
}

template <class _ARG1>
inline void _CALL_TRY_ (_ARG1 &&proc) {
	_STATIC_ASSERT_ (IS_VOID_HELP<RESULT_OF_TYPE<_ARG1 ,ARGVS<>>>::compile ()) ;
	proc () ;
}

//@warn: check ruined object when an exception was thrown
template <class _ARG1 ,class... _ARGS>
inline void _CALL_TRY_ (_ARG1 &&proc_one ,_ARGS &&...proc_rest) {
	_STATIC_ASSERT_ (IS_VOID_HELP<RESULT_OF_TYPE<_ARG1 ,ARGVS<>>>::compile ()) ;
	try {
		proc_one () ;
		return ;
	} catch (const Exception &e) {
		_STATIC_UNUSED_ (e) ;
	} catch (...) {
		_DYNAMIC_ASSERT_ (FALSE) ;
	}
	_CALL_TRY_ (proc_rest...) ;
}
} ;