﻿#pragma once

#ifndef __CSC_CORE__
#define __CSC_CORE__
#endif

#include "csc.hpp"

namespace CSC {
using BOOL = bool ;

static constexpr auto TRUE = BOOL (true) ;
static constexpr auto FALSE = BOOL (false) ;

using VAR32 = std::int32_t ;
using VAR64 = std::int64_t ;

static constexpr auto VAR32_MAX = VAR32 (2147483647) ;
static constexpr auto VAR32_MIN = -VAR32_MAX - 1 ;
static constexpr auto VAR64_MAX = VAR64 (9223372036854775807) ;
static constexpr auto VAR64_MIN = -VAR64_MAX - 1 ;

namespace U {
template <class...>
trait VAR_HELP ;

#ifdef __CSC_CONFIG_VAR32__
template <>
trait VAR_HELP<> {
	using VAR = VAR32 ;

	static constexpr auto VAR_MAX = VAR32_MAX ;
	static constexpr auto VAR_MIN = VAR32_MIN ;
} ;
#endif

#ifdef __CSC_CONFIG_VAR64__
template <>
trait VAR_HELP<> {
	using VAR = VAR64 ;

	static constexpr auto VAR_MAX = VAR64_MAX ;
	static constexpr auto VAR_MIN = VAR64_MIN ;
} ;
#endif
} ;

using VAR = typename U::VAR_HELP<>::VAR ;

static constexpr auto VAR_MAX = U::VAR_HELP<>::VAR_MAX ;
static constexpr auto VAR_MIN = U::VAR_HELP<>::VAR_MIN ;

using INDEX = VAR ;
using LENGTH = VAR ;
using FLAG = VAR ;

static constexpr auto USED = VAR (-2) ;
static constexpr auto NONE = VAR (-1) ;
static constexpr auto ZERO = VAR (+0) ;
static constexpr auto IDEN = VAR (+1) ;

using FLOAT32 = float ;
using FLOAT64 = double ;

static constexpr auto FLOAT32_MAX = FLOAT32 (3.402823466E+38) ;
static constexpr auto FLOAT32_MIN = FLOAT32 (1.175494351E-38) ;
static constexpr auto FLOAT32_EPS = FLOAT32 (1.192092896E-07) ;
static constexpr auto FLOAT32_INF = FLOAT32 (std::numeric_limits<float>::infinity ()) ;
static constexpr auto FLOAT64_MAX = FLOAT64 (1.7976931348623158E+308) ;
static constexpr auto FLOAT64_MIN = FLOAT64 (2.2250738585072014E-308) ;
static constexpr auto FLOAT64_EPS = FLOAT64 (2.2204460492503131E-016) ;
static constexpr auto FLOAT64_INF = FLOAT64 (std::numeric_limits<float>::infinity ()) ;

using BYTE = std::uint8_t ;
using WORD = std::uint16_t ;
using CHAR = std::uint32_t ;
using FEAT = std::uint64_t ;

namespace U {
enum class easy_char8_t :unsigned char ;
} ;

using STRA = char ;
using STRW = wchar_t ;
using STRU8 = U::easy_char8_t ;
using STRU16 = char16_t ;
using STRU32 = char32_t ;

namespace U {
template <class...>
trait STR_HELP ;

#ifdef __CSC_CONFIG_STRA__
template <>
trait STR_HELP<> {
	using STR = STRA ;
} ;
#endif

#ifdef __CSC_CONFIG_STRW__
template <>
trait STR_HELP<> {
	using STR = STRW ;
} ;
#endif

#ifdef __CSC_CONFIG_STRU8__
template <>
trait STR_HELP<> {
	using STR = STRU8 ;
} ;
#endif

#ifdef __CSC_CONFIG_STRU16__
template <>
trait STR_HELP<> {
	using STR = STRU16 ;
} ;
#endif

#ifdef __CSC_CONFIG_STRU32__
template <>
trait STR_HELP<> {
	using STR = STRU32 ;
} ;
#endif
} ;

using STR = typename U::STR_HELP<>::STR ;

static constexpr auto NULL = nullptr ;

namespace U {
template <class...>
trait ENUMAS ;

template <VAR>
trait ENUMID {} ;

template <VAR ARG1>
trait ENUMAS<ENUMID<ARG1>> {
	static constexpr auto value = ARG1 ;
} ;
} ;

namespace U {
template <class...>
trait TYPEAS ;

template <class ARG1>
trait TYPEID {} ;

template <class ARG1>
trait TYPEAS<ARG1> {
	static constexpr auto id = TYPEID<ARG1> () ;
} ;
} ;

template <class UNIT1>
using REMOVE_CVR = typename std::remove_cv<typename std::remove_reference<UNIT1>::type>::type ;

namespace U {
template <class...>
trait REMOVE_TYPEID_HELP ;

template <>
trait REMOVE_TYPEID_HELP<void> ;

template <class ARG1>
trait REMOVE_TYPEID_HELP<ARG1> {
	using RET = REMOVE_CVR<ARG1> ;
} ;

template <class ARG1>
trait REMOVE_TYPEID_HELP<TYPEID<ARG1>> {
	using RET = REMOVE_CVR<ARG1> ;
} ;
} ;

template <class UNIT1>
using REMOVE_TYPEID = typename U::REMOVE_TYPEID_HELP<REMOVE_CVR<UNIT1>>::RET ;

template <class UNIT1>
using DEF = UNIT1 ;

template <class UNIT1>
using UNSAFE_PTR = DEF<typename std::remove_reference<UNIT1>::type> * ;

template <class UNIT1>
using VREF = UNIT1 & ;

template <class UNIT1>
using CREF = const UNIT1 & ;

template <class UNIT1>
using RREF = UNIT1 && ;

using ENUM_USED = enumof (-2) ;
using ENUM_NONE = enumof (-1) ;
using ENUM_ZERO = enumof (+0) ;
using ENUM_IDEN = enumof (+1) ;

template <class UNIT1>
using SIZEOF = enumof (sizeof (UNIT1)) ;

template <class UNIT1>
using ALIGNOF = enumof (alignof (UNIT1)) ;

namespace U {
template <class...>
trait COUNTOF_HELP ;

template <class...ARGS>
trait COUNTOF_HELP<typeas<ARGS...>> {
	using RET = enumof (sizeof... (ARGS)) ;
} ;
} ;

template <class UNIT1>
using COUNTOF = typename U::COUNTOF_HELP<UNIT1>::RET ;

template <class UNIT1 ,class UNIT2>
using IS_SAME = enumof (std::is_same<UNIT1 ,UNIT2>::value) ;

namespace U {
template <class...>
trait REQUIRE_HELP ;

template <>
trait REQUIRE_HELP<ENUM_IDEN> {
	using RET = void ;
} ;
} ;

template <class UNIT1>
using REQUIRE = typename U::REQUIRE_HELP<UNIT1>::RET ;

namespace U {
template <class...>
trait ENABLE_HELP ;

template <class ARG1 ,class ARG2>
trait ENABLE_HELP<ARG1 ,ARG2 ,REQUIRE<IS_SAME<ARG1 ,ENUM_IDEN>>> {
	require (IS_SAME<ARG1 ,ENUM_IDEN>) ;

	using RET = ARG2 ;
} ;
} ;

template <class COND ,class YES = typeas<>>
using ENABLE = typename U::ENABLE_HELP<COND ,YES ,void>::RET ;

namespace U {
template <class...>
trait DEPENDENT_HELP ;

template <class ARG1 ,class ARG2>
trait DEPENDENT_HELP<ARG1 ,ARG2> {
	using RET = ARG1 ;
} ;
} ;

template <class BASE ,class DEP>
using DEPENDENT = typename U::DEPENDENT_HELP<BASE ,DEP>::RET ;

namespace U {
template <class...>
trait CONDITIONAL_HELP ;

template <class ARG1 ,class ARG2 ,class ARG3>
trait CONDITIONAL_HELP<ARG1 ,ARG2 ,ARG3 ,REQUIRE<IS_SAME<ARG1 ,ENUM_IDEN>>> {
	require (IS_SAME<ARG1 ,ENUM_IDEN>) ;

	using RET = ARG2 ;
} ;

template <class ARG1 ,class ARG2 ,class ARG3>
trait CONDITIONAL_HELP<ARG1 ,ARG2 ,ARG3 ,REQUIRE<IS_SAME<ARG1 ,ENUM_ZERO>>> {
	require (IS_SAME<ARG1 ,ENUM_ZERO>) ;

	using RET = ARG3 ;
} ;
} ;

template <class COND ,class YES ,class NO>
using CONDITIONAL = typename U::CONDITIONAL_HELP<COND ,YES ,NO ,void>::RET ;

namespace U {
template <class...>
trait IS_ENUM_HELP ;

template <class...ARGS>
trait IS_ENUM_HELP<ENUMAS<ARGS...>> {
	using RET = ENUM_IDEN ;
} ;
} ;

template <class UNIT1>
using IS_ENUM = typename U::IS_ENUM_HELP<UNIT1>::RET ;

template <class UNIT1>
using ENUM_CHECK = ENABLE<IS_ENUM<UNIT1> ,UNIT1> ;

template <class UNIT1 ,class UNIT2>
using ENUM_EQUAL = enumof (ENUM_CHECK<UNIT1>::value == ENUM_CHECK<UNIT2>::value) ;

template <class UNIT1 ,class UNIT2>
using ENUM_NOT_EQUAL = enumof (ENUM_CHECK<UNIT1>::value != ENUM_CHECK<UNIT2>::value) ;

template <class UNIT1>
using ENUM_NOT = ENUM_EQUAL<UNIT1 ,ENUM_ZERO> ;

namespace U {
template <class...>
trait ENUM_COMPR_HELP ;

template <>
trait ENUM_COMPR_HELP<ENUM_IDEN ,ENUM_ZERO> {
	using RET = enumof (-1) ;
} ;

template <>
trait ENUM_COMPR_HELP<ENUM_ZERO ,ENUM_IDEN> {
	using RET = enumof (+1) ;
} ;

template <>
trait ENUM_COMPR_HELP<ENUM_ZERO ,ENUM_ZERO> {
	using RET = ENUM_ZERO ;
} ;
} ;

template <class UNIT1 ,class UNIT2>
using ENUM_COMPR = typename U::ENUM_COMPR_HELP<enumof (ENUM_CHECK<UNIT1>::value < ENUM_CHECK<UNIT2>::value) ,enumof (ENUM_CHECK<UNIT2>::value < ENUM_CHECK<UNIT1>::value)>::RET ;

template <class UNIT1 ,class UNIT2>
using ENUM_COMPR_LT = enumof (ENUM_COMPR<UNIT1 ,UNIT2>::value < ZERO) ;

template <class UNIT1 ,class UNIT2>
using ENUM_COMPR_LT_EQ = enumof (ENUM_COMPR<UNIT1 ,UNIT2>::value <= ZERO) ;

template <class UNIT1 ,class UNIT2>
using ENUM_COMPR_GT = enumof (ENUM_COMPR<UNIT1 ,UNIT2>::value > ZERO) ;

template <class UNIT1 ,class UNIT2>
using ENUM_COMPR_GT_EQ = enumof (ENUM_COMPR<UNIT1 ,UNIT2>::value >= ZERO) ;

template <class UNIT1>
using ENUM_EQ_ZERO = ENUM_EQUAL<UNIT1 ,ENUM_ZERO> ;

template <class UNIT1>
using ENUM_LT_ZERO = ENUM_COMPR_LT<UNIT1 ,ENUM_ZERO> ;

template <class UNIT1>
using ENUM_GT_ZERO = ENUM_COMPR_GT<UNIT1 ,ENUM_ZERO> ;

template <class UNIT1>
using ENUM_EQ_IDEN = ENUM_EQUAL<UNIT1 ,ENUM_IDEN> ;

template <class UNIT1>
using ENUM_LT_IDEN = ENUM_COMPR_LT<UNIT1 ,ENUM_IDEN> ;

template <class UNIT1>
using ENUM_GT_IDEN = ENUM_COMPR_GT<UNIT1 ,ENUM_IDEN> ;

template <class UNIT1 ,class UNIT2>
using ENUM_ADD = enumof (ENUM_CHECK<UNIT1>::value + ENUM_CHECK<UNIT2>::value) ;

template <class UNIT1 ,class UNIT2>
using ENUM_SUB = enumof (ENUM_CHECK<UNIT1>::value - ENUM_CHECK<UNIT2>::value) ;

template <class UNIT1 ,class UNIT2>
using ENUM_MUL = enumof (ENUM_CHECK<UNIT1>::value * ENUM_CHECK<UNIT2>::value) ;

template <class UNIT1 ,class UNIT2>
using ENUM_DIV = enumof (ENUM_CHECK<UNIT1>::value / ENUM_CHECK<UNIT2>::value) ;

template <class UNIT1 ,class UNIT2>
using ENUM_MOD = enumof (ENUM_CHECK<UNIT1>::value % ENUM_CHECK<UNIT2>::value) ;

template <class UNIT1>
using ENUM_INC = ENUM_ADD<UNIT1 ,ENUM_IDEN> ;

template <class UNIT1>
using ENUM_DEC = ENUM_SUB<UNIT1 ,ENUM_IDEN> ;

namespace U {
template <class...>
trait IS_TYPE_HELP ;

template <class...ARGS>
trait IS_TYPE_HELP<TYPEAS<ARGS...>> {
	using RET = ENUM_IDEN ;
} ;
} ;

template <class UNIT1>
using IS_TYPE = typename U::IS_TYPE_HELP<UNIT1>::RET ;

template <class UNIT1>
using TYPE_CHECK = ENABLE<IS_TYPE<UNIT1> ,UNIT1> ;

namespace U {
template <class...>
trait TYPE_FIRST_ONE_HELP ;

template <class ARG1 ,class...ARGS>
trait TYPE_FIRST_ONE_HELP<typeas<ARG1 ,ARGS...>> {
	using RET = ARG1 ;
} ;
} ;

template <class UNIT1>
using TYPE_FIRST_ONE = typename U::TYPE_FIRST_ONE_HELP<TYPE_CHECK<UNIT1>>::RET ;

namespace U {
template <class...>
trait TYPE_FIRST_REST_HELP ;

template <class ARG1 ,class...ARGS>
trait TYPE_FIRST_REST_HELP<typeas<ARG1 ,ARGS...>> {
	using RET = typeas<ARGS...> ;
} ;
} ;

template <class UNIT1>
using TYPE_FIRST_REST = typename U::TYPE_FIRST_REST_HELP<TYPE_CHECK<UNIT1>>::RET ;

namespace U {
template <class...>
trait TYPE_SECOND_ONE_HELP ;

template <class ARG1 ,class ARG2 ,class...ARGS>
trait TYPE_SECOND_ONE_HELP<typeas<ARG1 ,ARG2 ,ARGS...>> {
	using RET = ARG2 ;
} ;
} ;

template <class UNIT1>
using TYPE_SECOND_ONE = typename U::TYPE_SECOND_ONE_HELP<TYPE_CHECK<UNIT1>>::RET ;

namespace U {
template <class...>
trait TYPE_SECOND_REST_HELP ;

template <class ARG1 ,class ARG2 ,class...ARGS>
trait TYPE_SECOND_REST_HELP<typeas<ARG1 ,ARG2 ,ARGS...>> {
	using RET = typeas<ARGS...> ;
} ;
} ;

template <class UNIT1>
using TYPE_SECOND_REST = typename U::TYPE_SECOND_REST_HELP<TYPE_CHECK<UNIT1>>::RET ;

namespace U {
template <class...>
trait TYPE_UNWRAP_HELP ;

template <class ARG1>
trait TYPE_UNWRAP_HELP<ARG1 ,REQUIRE<ENUM_EQ_IDEN<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_IDEN<COUNTOF<ARG1>>) ;

	using RET = TYPE_FIRST_ONE<ARG1> ;
} ;
} ;

template <class UNIT1>
using TYPE_UNWRAP = typename U::TYPE_UNWRAP_HELP<UNIT1 ,void>::RET ;

namespace U {
template <class...>
trait TYPE_CAT_HELP ;

template <class...ARGS1 ,class...ARGS2>
trait TYPE_CAT_HELP<typeas<ARGS1...> ,typeas<ARGS2...>> {
	using RET = typeas<ARGS1... ,ARGS2...> ;
} ;
} ;

template <class UNIT1 ,class UNIT2>
using TYPE_CAT = typename U::TYPE_CAT_HELP<TYPE_CHECK<UNIT1> ,TYPE_CHECK<UNIT2>>::RET ;

namespace U {
template <class...>
trait TYPE_REPEAT_HELP ;

template <class ARG1 ,class ARG2>
trait TYPE_REPEAT_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_EQ_ZERO<ARG2>>> {
	require (ENUM_EQ_ZERO<ARG2>) ;

	using RET = typeas<> ;
} ;

template <class ARG1 ,class ARG2>
trait TYPE_REPEAT_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_GT_ZERO<ARG2>>> {
	require (ENUM_GT_ZERO<ARG2>) ;

	struct Dependent ;
	using R1X = typename DEPENDENT<TYPE_REPEAT_HELP<ARG1 ,ENUM_DEC<ARG2> ,void> ,Dependent>::RET ;

	using RET = TYPE_CAT<ARG1 ,R1X> ;
} ;
} ;

template <class UNIT1 ,class SIZE>
using TYPE_REPEAT = typename U::TYPE_REPEAT_HELP<typeas<UNIT1> ,SIZE ,void>::RET ;

namespace U {
template <class...>
trait TYPE_REVERSE_HELP ;

template <class ARG1>
trait TYPE_REVERSE_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;

	using RET = typeas<> ;
} ;

template <class ARG1>
trait TYPE_REVERSE_HELP<ARG1 ,REQUIRE<ENUM_GT_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_GT_ZERO<COUNTOF<ARG1>>) ;

	struct Dependent ;
	using R1X = TYPE_FIRST_ONE<ARG1> ;
	using R2X = typename DEPENDENT<TYPE_REVERSE_HELP<TYPE_FIRST_REST<ARG1>> ,Dependent>::RET ;

	using RET = TYPE_CAT<R2X ,typeas<R1X>> ;
} ;
} ;

template <class UNIT1>
using TYPE_REVERSE = typename U::TYPE_REVERSE_HELP<UNIT1 ,void>::RET ;

namespace U {
template <class...>
trait TYPE_PICK_HELP ;

template <class ARG1 ,class ARG2>
trait TYPE_PICK_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_EQ_ZERO<ARG2>>> {
	require (ENUM_EQ_ZERO<ARG2>) ;

	using RET = TYPE_FIRST_ONE<ARG1> ;
} ;

template <class ARG1 ,class ARG2>
trait TYPE_PICK_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_GT_ZERO<ARG2>>> {
	require (ENUM_GT_ZERO<ARG2>) ;

	struct Dependent ;
	using RET = typename DEPENDENT<TYPE_PICK_HELP<TYPE_FIRST_REST<ARG1> ,ENUM_DEC<ARG2>> ,Dependent>::RET ;
} ;
} ;

template <class LIST ,class INDEX>
using TYPE_PICK = typename U::TYPE_PICK_HELP<LIST ,INDEX ,void>::RET ;

namespace U {
template <class...>
trait ENUM_ALL_HELP ;

template <class ARG1>
trait ENUM_ALL_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;

	using RET = ENUM_IDEN ;
} ;

template <class ARG1>
trait ENUM_ALL_HELP<ARG1 ,REQUIRE<ENUM_GT_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_GT_ZERO<COUNTOF<ARG1>>) ;

	struct Dependent ;
	using R1X = ENUM_NOT<ENUM_EQ_ZERO<TYPE_FIRST_ONE<ARG1>>> ;
	using R2X = typename DEPENDENT<ENUM_ALL_HELP<TYPE_FIRST_REST<ARG1> ,void> ,Dependent>::RET ;

	using RET = CONDITIONAL<R1X ,R2X ,ENUM_ZERO> ;
} ;
} ;

template <class...ARGS>
using ENUM_ALL = typename U::ENUM_ALL_HELP<typeas<ARGS...> ,void>::RET ;

namespace U {
template <class...>
trait ENUM_ANY_HELP ;

template <class ARG1>
trait ENUM_ANY_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;

	using RET = ENUM_ZERO ;
} ;

template <class ARG1>
trait ENUM_ANY_HELP<ARG1 ,REQUIRE<ENUM_GT_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_GT_ZERO<COUNTOF<ARG1>>) ;

	struct Dependent ;
	using R1X = ENUM_NOT<ENUM_EQ_ZERO<TYPE_FIRST_ONE<ARG1>>> ;
	using R2X = typename DEPENDENT<ENUM_ANY_HELP<TYPE_FIRST_REST<ARG1> ,void> ,Dependent>::RET ;

	using RET = CONDITIONAL<R1X ,ENUM_IDEN ,R2X> ;
} ;
} ;

template <class...ARGS>
using ENUM_ANY = typename U::ENUM_ANY_HELP<typeas<ARGS...> ,void>::RET ;

namespace U {
template <class...>
trait IS_ALL_SAME_HELP ;

template <class ARG1>
trait IS_ALL_SAME_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;

	using RET = ENUM_IDEN ;
} ;

template <class ARG1>
trait IS_ALL_SAME_HELP<ARG1 ,REQUIRE<ENUM_EQ_IDEN<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_IDEN<COUNTOF<ARG1>>) ;

	using RET = ENUM_IDEN ;
} ;

template <class ARG1>
trait IS_ALL_SAME_HELP<ARG1 ,REQUIRE<ENUM_GT_IDEN<COUNTOF<ARG1>>>> {
	require (ENUM_GT_IDEN<COUNTOF<ARG1>>) ;

	struct Dependent ;
	using R1X = TYPE_FIRST_ONE<ARG1> ;
	using R2X = TYPE_SECOND_ONE<ARG1> ;
	using R3X = typename DEPENDENT<IS_ALL_SAME_HELP<TYPE_CAT<R1X ,TYPE_SECOND_REST<ARG1>> ,void> ,Dependent>::RET ;

	using RET = ENUM_ALL<IS_SAME<R1X ,R2X> ,R3X> ;
} ;
} ;

template <class...ARGS>
using IS_ALL_SAME = typename U::IS_ALL_SAME_HELP<typeas<ARGS...> ,void>::RET ;

namespace U {
template <class...>
trait IS_ANY_SAME_HELP ;

template <class ARG1>
trait IS_ANY_SAME_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;

	using RET = ENUM_ZERO ;
} ;

template <class ARG1>
trait IS_ANY_SAME_HELP<ARG1 ,REQUIRE<ENUM_EQ_IDEN<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_IDEN<COUNTOF<ARG1>>) ;

	using RET = ENUM_ZERO ;
} ;

template <class ARG1>
trait IS_ANY_SAME_HELP<ARG1 ,REQUIRE<ENUM_GT_IDEN<COUNTOF<ARG1>>>> {
	require (ENUM_GT_IDEN<COUNTOF<ARG1>>) ;

	struct Dependent ;
	using R1X = TYPE_FIRST_ONE<ARG1> ;
	using R2X = TYPE_SECOND_ONE<ARG1> ;
	using R3X = typename DEPENDENT<IS_ANY_SAME_HELP<TYPE_CAT<R1X ,TYPE_SECOND_REST<ARG1>>> ,Dependent>::RET ;
	using R4X = typename DEPENDENT<IS_ANY_SAME_HELP<TYPE_CAT<R2X ,TYPE_SECOND_REST<ARG1>>> ,Dependent>::RET ;

	using RET = ENUM_ANY<IS_SAME<R1X ,R2X> ,R3X ,R4X> ;
} ;
} ;

template <class...ARGS>
using IS_ANY_SAME = typename U::IS_ANY_SAME_HELP<typeas<ARGS...>>::RET ;

namespace U {
template <class...>
trait PLACEHOLDER_HELP ;

template <class ARG1>
trait PLACEHOLDER_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<ARG1>>> {
	require (ENUM_EQ_ZERO<ARG1>) ;

	class PlaceHolder ;
} ;

template <class UNIT1>
class PLACEHOLDER_HELP<UNIT1 ,REQUIRE<ENUM_EQ_ZERO<UNIT1>>>::PlaceHolder {} ;

template <class ARG1>
trait PLACEHOLDER_HELP<ARG1 ,REQUIRE<ENUM_GT_ZERO<ARG1>>> {
	require (ENUM_GT_ZERO<ARG1>) ;

	struct Dependent ;
	using BASE = typename DEPENDENT<PLACEHOLDER_HELP<ENUM_DEC<ARG1> ,void> ,Dependent>::PlaceHolder ;

	class PlaceHolder ;
} ;

template <class UNIT1>
class PLACEHOLDER_HELP<UNIT1 ,REQUIRE<ENUM_GT_ZERO<UNIT1>>>::PlaceHolder :
	public BASE {} ;
} ;

template <class RANK>
using PlaceHolder = typename U::PLACEHOLDER_HELP<RANK ,void>::PlaceHolder ;

static constexpr auto PH0 = PlaceHolder<enumof (0)> () ;
static constexpr auto PH1 = PlaceHolder<enumof (1)> () ;
static constexpr auto PH2 = PlaceHolder<enumof (2)> () ;
static constexpr auto PH3 = PlaceHolder<enumof (3)> () ;
static constexpr auto PH4 = PlaceHolder<enumof (4)> () ;
static constexpr auto PH5 = PlaceHolder<enumof (5)> () ;
static constexpr auto PH6 = PlaceHolder<enumof (6)> () ;
static constexpr auto PH7 = PlaceHolder<enumof (7)> () ;
static constexpr auto PH8 = PlaceHolder<enumof (8)> () ;
static constexpr auto PH9 = PlaceHolder<enumof (9)> () ;
static constexpr auto PHX = PlaceHolder<enumof (10)> () ;

template <class UNIT1>
using IS_BOOL = IS_SAME<UNIT1 ,BOOL> ;

template <class UNIT1>
using IS_VAR = ENUM_ANY<IS_SAME<UNIT1 ,VAR32> ,IS_SAME<UNIT1 ,VAR64>> ;

template <class UNIT1>
using IS_FLOAT = ENUM_ANY<IS_SAME<UNIT1 ,FLOAT32> ,IS_SAME<UNIT1 ,FLOAT64>> ;

template <class UNIT1>
using IS_BYTE = ENUM_ANY<IS_SAME<UNIT1 ,BYTE> ,IS_SAME<UNIT1 ,WORD> ,IS_SAME<UNIT1 ,CHAR> ,IS_SAME<UNIT1 ,FEAT>> ;

template <class UNIT1>
using IS_STR = ENUM_ANY<IS_SAME<UNIT1 ,STRA> ,IS_SAME<UNIT1 ,STRW> ,IS_SAME<UNIT1 ,STRU8> ,IS_SAME<UNIT1 ,STRU16> ,IS_SAME<UNIT1 ,STRU32>> ;

template <class UNIT1>
using IS_NULL = IS_SAME<UNIT1 ,typeof (NULL)> ;

template <class UNIT1>
using IS_BASIC = ENUM_ANY<IS_BOOL<UNIT1> ,IS_VAR<UNIT1> ,IS_FLOAT<UNIT1> ,IS_BYTE<UNIT1> ,IS_STR<UNIT1> ,IS_NULL<UNIT1>> ;

template <class UNIT1>
using IS_FUNCTION = enumof (std::is_function<UNIT1>::value) ;

template <class UNIT1>
using IS_NOEXCPET = enumof (FALSE) ;

template <class UNIT1>
using IS_CLASS = enumof (std::is_class<UNIT1>::value) ;

template <class UNIT1>
using IS_STRUCT = enumof (std::is_class<UNIT1>::value) ;

template <class UNIT1>
using IS_TRIVIAL = enumof (std::is_trivial<UNIT1>::value) ;

namespace U {
template <class...>
trait IS_CONSTRUCTIBLE_HELP ;

template <class ARG1 ,class...ARGS>
trait IS_CONSTRUCTIBLE_HELP<ARG1 ,typeas<ARGS...>> {
	using RET = enumof (std::is_constructible<ARG1 ,ARGS...>::value) ;
} ;
} ;

template <class UNIT1 ,class PARAMS>
using IS_CONSTRUCTIBLE = typename U::IS_CONSTRUCTIBLE_HELP<UNIT1 ,PARAMS>::RET ;

template <class UNIT1>
using IS_CLONEABLE = enumof (std::is_copy_constructible<UNIT1>::value && std::is_copy_assignable<UNIT1>::value) ;

class Interface {
public:
	implicit Interface () = default ;
	implicit virtual ~Interface () noexcept = default ;
	implicit Interface (CREF<Interface>) = delete ;
	inline void operator= (CREF<Interface>) = delete ;
	implicit Interface (RREF<Interface>) = delete ;
	inline void operator= (RREF<Interface>) = delete ;
} ;

template <class UNIT1>
using IS_INTERFACE = enumof (std::is_base_of<Interface ,UNIT1>::value && std::is_abstract<UNIT1>::value) ;

template <class BASE ,class DERIVED>
using IS_EXTEND = enumof (std::is_base_of<BASE ,DERIVED>::value) ;

template <class UNIT1>
using IS_PLACEHOLDER = IS_EXTEND<UNIT1 ,typeof (PH0)> ;

namespace U {
template <class...>
trait BYTE_TRAIT_HELP ;

template <class ARG1 ,class ARG2>
trait BYTE_TRAIT_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_EQUAL<ARG1 ,SIZEOF<BYTE>>> ,REQUIRE<ENUM_EQUAL<ARG2 ,ALIGNOF<BYTE>>>> {
	require (ENUM_EQUAL<ARG1 ,SIZEOF<BYTE>>) ;
	require (ENUM_EQUAL<ARG2 ,ALIGNOF<BYTE>>) ;

	using RET = BYTE ;
} ;

template <class ARG1 ,class ARG2>
trait BYTE_TRAIT_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_EQUAL<ARG1 ,SIZEOF<WORD>>> ,REQUIRE<ENUM_EQUAL<ARG2 ,ALIGNOF<WORD>>>> {
	require (ENUM_EQUAL<ARG1 ,SIZEOF<WORD>>) ;
	require (ENUM_EQUAL<ARG2 ,ALIGNOF<WORD>>) ;

	using RET = WORD ;
} ;

template <class ARG1 ,class ARG2>
trait BYTE_TRAIT_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_EQUAL<ARG1 ,SIZEOF<CHAR>>> ,REQUIRE<ENUM_EQUAL<ARG2 ,ALIGNOF<CHAR>>>> {
	require (ENUM_EQUAL<ARG1 ,SIZEOF<CHAR>>) ;
	require (ENUM_EQUAL<ARG2 ,ALIGNOF<CHAR>>) ;

	using RET = CHAR ;
} ;

template <class ARG1 ,class ARG2>
trait BYTE_TRAIT_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_EQUAL<ARG1 ,SIZEOF<FEAT>>> ,REQUIRE<ENUM_EQUAL<ARG2 ,ALIGNOF<FEAT>>>> {
	require (ENUM_EQUAL<ARG1 ,SIZEOF<FEAT>>) ;
	require (ENUM_EQUAL<ARG2 ,ALIGNOF<FEAT>>) ;

	using RET = FEAT ;
} ;
} ;

template <class SIZE ,class ALIGN>
using BYTE_TRAIT = typename U::BYTE_TRAIT_HELP<SIZE ,ALIGN ,void ,void>::RET ;

namespace U {
template <class...>
trait CAST_TRAIT_HELP ;

template <class ARG1 ,class ARG2>
trait CAST_TRAIT_HELP<ARG1 ,ARG2> {
	using RET = ARG1 ;
} ;

template <class ARG1 ,class ARG2>
trait CAST_TRAIT_HELP<ARG1 ,DEF<const ARG2>> {
	using RET = DEF<const ARG1> ;
} ;

template <class ARG1 ,class ARG2>
trait CAST_TRAIT_HELP<ARG1 ,DEF<volatile ARG2>> {
	using RET = DEF<volatile ARG1> ;
} ;

template <class ARG1 ,class ARG2>
trait CAST_TRAIT_HELP<ARG1 ,DEF<const volatile ARG2>> {
	using RET = DEF<const volatile ARG1> ;
} ;

template <class ARG1 ,class ARG2>
trait CAST_TRAIT_HELP<ARG1 ,DEF<ARG2 &>> {
	using RET = DEF<ARG1 &> ;
} ;

template <class ARG1 ,class ARG2>
trait CAST_TRAIT_HELP<ARG1 ,DEF<const ARG2 &>> {
	using RET = DEF<const ARG1 &> ;
} ;

template <class ARG1 ,class ARG2>
trait CAST_TRAIT_HELP<ARG1 ,DEF<volatile ARG2 &>> {
	using RET = DEF<volatile ARG1 &> ;
} ;

template <class ARG1 ,class ARG2>
trait CAST_TRAIT_HELP<ARG1 ,DEF<const volatile ARG2 &>> {
	using RET = DEF<const volatile ARG1 &> ;
} ;

template <class ARG1 ,class ARG2>
trait CAST_TRAIT_HELP<ARG1 ,DEF<ARG2 &&>> {
	using RET = DEF<ARG1 &&> ;
} ;

template <class ARG1 ,class ARG2>
trait CAST_TRAIT_HELP<ARG1 ,DEF<const ARG2 &&>> {
	using RET = DEF<const ARG1 &&> ;
} ;

template <class ARG1 ,class ARG2>
trait CAST_TRAIT_HELP<ARG1 ,DEF<volatile ARG2 &&>> {
	using RET = DEF<volatile ARG1 &&> ;
} ;

template <class ARG1 ,class ARG2>
trait CAST_TRAIT_HELP<ARG1 ,DEF<const volatile ARG2 &&>> {
	using RET = DEF<const volatile ARG1 &&> ;
} ;
} ;

template <class TO ,class FROM>
using CAST_TRAIT = typename U::CAST_TRAIT_HELP<TO ,FROM>::RET ;

namespace U {
template <class...>
trait PACK_HELP ;

template <>
trait PACK_HELP<> {
	struct PACK ;
} ;

struct PACK_HELP<>::PACK {} ;

template <class ARG1>
trait PACK_HELP<ARG1> {
	struct PACK ;
} ;

template <class UNIT1>
struct PACK_HELP<UNIT1>::PACK {
	UNIT1 mP1 ;
} ;

template <class ARG1 ,class ARG2>
trait PACK_HELP<ARG1 ,ARG2> {
	struct PACK ;
} ;

template <class UNIT1 ,class UNIT2>
struct PACK_HELP<UNIT1 ,UNIT2>::PACK {
	UNIT1 mP1 ;
	UNIT2 mP2 ;
} ;

template <class ARG1 ,class ARG2 ,class ARG3>
trait PACK_HELP<ARG1 ,ARG2 ,ARG3> {
	struct PACK ;
} ;

template <class UNIT1 ,class UNIT2 ,class UNIT3>
struct PACK_HELP<UNIT1 ,UNIT2 ,UNIT3>::PACK {
	UNIT1 mP1 ;
	UNIT2 mP2 ;
	UNIT3 mP3 ;
} ;
} ;

template <class...UNITS>
using PACK = typename U::PACK_HELP<UNITS...>::PACK ;

namespace U {
template <class...>
trait TEMP_HELP ;

template <class ARG1>
trait TEMP_HELP<ARG1> {
	struct TEMP ;
} ;

template <class UNIT1>
struct TEMP_HELP<UNIT1>::TEMP {
	using ITEM = BYTE_TRAIT<ALIGNOF<UNIT1> ,ALIGNOF<UNIT1>> ;
	using SIZE = ENUM_DIV<ENUM_DEC<ENUM_ADD<SIZEOF<UNIT1> ,SIZEOF<ITEM>>> ,SIZEOF<ITEM>> ;

	DEF<ITEM[SIZE::value]> mUnused ;
} ;
} ;

template <class...UNIT1>
using TEMP = typename U::TEMP_HELP<UNIT1...>::TEMP ;

namespace U {
struct FUNCTION_NOOP {
	inline void operator() () const {
		return ;
	}
} ;
} ;

static constexpr auto noop = U::FUNCTION_NOOP () ;

namespace U {
#ifdef __CSC_DEBUG__
#ifdef __CSC_COMPILER_MSVC__
struct FUNCTION_DEBUG_ASSERT {
	inline void operator() (CREF<BOOL> cond) const {
		if (cond)
			return ;
		__debugbreak () ;
		std::terminate () ;
	}
} ;
#endif
#endif

#ifdef __CSC_DEBUG__
#ifdef __CSC_COMPILER_GNUC__
struct FUNCTION_DEBUG_ASSERT {
	inline void operator() (CREF<BOOL> cond) const {
		if (cond)
			return ;
		std::terminate () ;
	}
} ;
#endif
#endif

#ifdef __CSC_DEBUG__
#ifdef __CSC_COMPILER_CLANG__
struct FUNCTION_DEBUG_ASSERT {
	inline void operator() (CREF<BOOL> cond) const {
		if (cond)
			return ;
		std::terminate () ;
	}
} ;
#endif
#endif
} ;

static constexpr auto debug_assert = U::FUNCTION_DEBUG_ASSERT () ;

namespace U {
#ifdef __CSC_COMPILER_MSVC__
using FUNCTION_BARRIER = FUNCTION_NOOP ;
#endif

#ifdef __CSC_COMPILER_GNUC__
struct FUNCTION_BARRIER {
	inline void operator() () const noexcept {
		asm volatile ("" ::: "memory") ;
	}
} ;
#endif

#ifdef __CSC_COMPILER_CLANG__
struct FUNCTION_BARRIER {
	inline void operator() () const noexcept {
		asm volatile ("" ::: "memory") ;
	}
} ;
#endif
} ;

static constexpr auto barrier = U::FUNCTION_BARRIER () ;

namespace U {
struct FUNCTION_ZEROIZE {
	template <class ARG1>
	inline void operator() (DEF<ARG1 &> obj) const noexcept {
		using R1X = typeof (obj) ;
		require (IS_TRIVIAL<R1X>) ;
		using R2X = TEMP<R1X> ;
		reinterpret_cast<VREF<R2X>> (obj) = {0} ;
		barrier () ;
	}
} ;
} ;

static constexpr auto zeroize = U::FUNCTION_ZEROIZE () ;

namespace U {
struct FUNCTION_BITWISE {
	template <class ARG1>
	inline BYTE_TRAIT<SIZEOF<ARG1> ,ALIGNOF<ARG1>> operator() (CREF<ARG1> obj) const noexcept {
		using R1X = typeof (obj) ;
		using R2X = BYTE_TRAIT<SIZEOF<R1X> ,ALIGNOF<R1X>> ;
		return R2X (reinterpret_cast<CREF<R2X>> (obj)) ;
	}
} ;
} ;

static constexpr auto bitwise = U::FUNCTION_BITWISE () ;

namespace U {
struct FUNCTION_SWAP {
	template <class ARG1 ,class ARG2>
	inline void operator() (DEF<ARG1 &> arg1 ,DEF<ARG2 &> arg2) const noexcept {
		using R1X = typeof (arg1) ;
		using R2X = typeof (arg2) ;
		require (IS_SAME<R1X ,R2X>) ;
		using R3X = TEMP<R1X> ;
		require (ENUM_EQUAL<SIZEOF<R3X> ,SIZEOF<R1X>>) ;
		require (ENUM_EQUAL<ALIGNOF<R3X> ,ALIGNOF<R1X>>) ;
		auto rax = reinterpret_cast<VREF<R3X>> (arg1) ;
		reinterpret_cast<VREF<R3X>> (arg1) = reinterpret_cast<VREF<R3X>> (arg2) ;
		reinterpret_cast<VREF<R3X>> (arg2) = rax ;
		barrier () ;
	}
} ;
} ;

static constexpr auto swap = U::FUNCTION_SWAP () ;

namespace U {
struct FUNCTION_CLONE {
	template <class ARG1>
	inline REMOVE_CVR<ARG1> operator() (DEF<ARG1 &> obj) const {
		return static_cast<CREF<ARG1>> (obj) ;
	}
} ;
} ;

static constexpr auto clone = U::FUNCTION_CLONE () ;

namespace U {
struct FUNCTION_FORWARD {
	template <class ARG1>
	inline CREF<REMOVE_CVR<ARG1>> operator()[[nodiscard]] (CREF<ARG1> obj) const {
		return static_cast<CREF<REMOVE_CVR<ARG1>>> (obj) ;
	}

	template <class ARG1>
	inline RREF<REMOVE_CVR<ARG1>> operator()[[nodiscard]] (DEF<ARG1 &> obj) const {
		return static_cast<RREF<REMOVE_CVR<ARG1>>> (obj) ;
	}
} ;
} ;

static constexpr auto forward = U::FUNCTION_FORWARD () ;

namespace U {
struct FUNCTION_ADDRESS {
	template <class ARG1>
	inline LENGTH operator() (CREF<ARG1> obj) const {
		return LENGTH (&reinterpret_cast<CREF<BOOL>> (obj)) ;
	}
} ;
} ;

static constexpr auto address = U::FUNCTION_ADDRESS () ;

namespace U {
struct FUNCTION_ALIGNTO {
	inline LENGTH operator() (CREF<LENGTH> base ,CREF<LENGTH> align) const {
		const auto r1x = align - base % align ;
		return base + r1x % align ;
	}
} ;
} ;

static constexpr auto alignto = U::FUNCTION_ALIGNTO () ;

namespace U {
struct FUNCTION_BETWEEN {
	inline BOOL operator() (CREF<INDEX> index ,CREF<INDEX> begin ,CREF<INDEX> end) const {
		return index >= begin && index < end ;
	}
} ;
} ;

static constexpr auto between = U::FUNCTION_BETWEEN () ;

namespace U {
struct FUNCTION_ABS {
	template <class ARG1>
	inline REMOVE_CVR<ARG1> operator() (CREF<ARG1> arg1) const {
		using R1X = typeof (arg1) ;
		if (arg1 < R1X (ZERO))
			return -arg1 ;
		return +arg1 ;
	}
} ;
} ;

static constexpr auto abs = U::FUNCTION_ABS () ;

namespace U {
struct FUNCTION_MIN {
	template <class ARG1>
	inline REMOVE_CVR<ARG1> operator() (CREF<ARG1> arg1 ,CREF<ARG1> arg2) const {
		if (arg1 < arg2)
			return arg1 ;
		return arg2 ;
	}
} ;
} ;

static constexpr auto min = U::FUNCTION_MIN () ;

namespace U {
struct FUNCTION_MAX {
	template <class ARG1>
	inline REMOVE_CVR<ARG1> operator() (CREF<ARG1> arg1 ,CREF<ARG1> arg2) const {
		if (arg1 < arg2)
			return arg2 ;
		return arg1 ;
	}
} ;
} ;

static constexpr auto max = U::FUNCTION_MAX () ;

namespace U {
template <class...>
trait FUNCTION_COMPARE_HELP ;

template <class ARG1>
trait FUNCTION_COMPARE_HELP<ARG1 ,REQUIRE<IS_BASIC<ARG1>>> {
	struct FUNCTION_COMPARE ;
} ;

template <class ARG1>
trait FUNCTION_COMPARE_HELP<ARG1 ,REQUIRE<IS_CLASS<ARG1>>> {
	struct FUNCTION_COMPARE ;
} ;

struct FUNCTION_COMPARE {
	template <class ARG1>
	inline FLAG operator() (CREF<ARG1> arg1 ,CREF<ARG1> arg2) const {
		struct Dependent ;
		using R1X = typeof (arg1) ;
		using R2X = typename DEPENDENT<FUNCTION_COMPARE_HELP<R1X ,void> ,Dependent>::FUNCTION_COMPARE ;
		static constexpr auto M_INVOKE = R2X () ;
		return M_INVOKE (arg1 ,arg2) ;
	}
} ;

template <class ARG1>
struct FUNCTION_COMPARE_HELP<ARG1 ,REQUIRE<IS_BASIC<ARG1>>>::FUNCTION_COMPARE {
	inline FLAG operator() (CREF<ARG1> arg1 ,CREF<ARG1> arg2) const {
		if (arg1 < arg2)
			return FLAG (-1) ;
		if (arg2 < arg1)
			return FLAG (+1) ;
		return ZERO ;
	}
} ;

template <class ARG1>
struct FUNCTION_COMPARE_HELP<ARG1 ,REQUIRE<IS_CLASS<ARG1>>>::FUNCTION_COMPARE {
	inline FLAG operator() (CREF<ARG1> arg1 ,CREF<ARG1> arg2) const {
		return arg1.compr (arg2) ;
	}
} ;
} ;

static constexpr auto compare = U::FUNCTION_COMPARE () ;

namespace U {
struct FUNCTION_HASHCODE {
	inline FLAG operator() () const {
		const auto r1x = VAR64 (-3750763034362895579) ;
		const auto r2x = VAR64 (FEAT (r1x) & FEAT (VAR64_MAX)) ;
		return FLAG (r2x) ;
	}

	inline FLAG operator() (CREF<FLAG> arg1 ,CREF<FLAG> arg2) const {
		const auto r1x = VAR64 (FEAT (arg1) ^ FEAT (arg2)) ;
		const auto r2x = r1x * VAR64 (1099511628211) ;
		const auto r3x = VAR64 (FEAT (r2x) & FEAT (VAR64_MAX)) ;
		return FLAG (r3x) ;
	}
} ;
} ;

static constexpr auto hashcode = U::FUNCTION_HASHCODE () ;

namespace U {
template <class...>
trait TYPEMID_HELP ;

template <class ARG1>
trait TYPEMID_HELP<ARG1> {
	class TYPEMID ;
} ;

struct FUNCTION_TYPE_MID {
	template <class ARG1>
	inline FLAG operator() (CREF<ARG1> id) const {
		struct Dependent ;
		using R1X = typeof (id) ;
		using R2X = typename DEPENDENT<TYPEMID_HELP<R1X> ,Dependent>::TYPEMID ;
		require (ENUM_EQUAL<SIZEOF<FLAG> ,SIZEOF<R2X>>) ;
		require (ENUM_EQUAL<ALIGNOF<FLAG> ,ALIGNOF<R2X>>) ;
		return FLAG (bitwise (R2X ())) ;
	}
} ;

template <class UNIT1>
class TYPEMID_HELP<UNIT1>::TYPEMID :
	private Interface {} ;
} ;

static constexpr auto type_mid = U::FUNCTION_TYPE_MID () ;

namespace U {
template <class...>
trait AUTO_HELP ;

template <>
trait AUTO_HELP<> {
	class AUTO ;

	struct EXTERN {
		interface Holder ;

		struct BLOCK ;
		class HeapProc ;
	} ;
} ;

interface AUTO_HELP<>::EXTERN::Holder :
	public Interface {
	virtual LENGTH type_size () const = 0 ;
	virtual LENGTH type_align () const = 0 ;
	virtual FLAG type_mid () const = 0 ;
} ;

struct AUTO_HELP<>::EXTERN::BLOCK {
	UNSAFE_PTR<struct BLOCK> mPrev ;
	UNSAFE_PTR<struct BLOCK> mNext ;
	LENGTH mBlockSize ;
	LENGTH mBlockCheck ;
} ;

class AUTO_HELP<>::EXTERN::HeapProc {
public:
	static UNSAFE_PTR<void> alloc (CREF<LENGTH> size_len ,CREF<LENGTH> align_len) {
		assert (size_len > ZERO) ;
		assert (align_len > ZERO) ;
		const auto r1x = align_len - SIZEOF<BLOCK>::value ;
		const auto r2x = size_len + max (r1x ,ZERO) ;
		const auto r3x = curr () ;
		assert (r3x->mBlockSize >= SIZEOF<BLOCK>::value + r2x) ;
		const auto r4x = INDEX (r3x) + SIZEOF<BLOCK>::value + r2x ;
		const auto r5x = alignto (r4x ,ALIGNOF<BLOCK>::value) ;
		const auto r6x = reinterpret_cast<UNSAFE_PTR<VREF<BLOCK>>> (r5x) ;
		r6x->mPrev = r3x ;
		r6x->mNext = NULL ;
		r6x->mBlockSize = r3x->mBlockSize - r2x ;
		r6x->mBlockCheck = LENGTH (0XCCCCCCCCCCCCCCCC) ;
		r3x->mNext = r6x ;
		r3x->mBlockSize -= r6x->mBlockSize ;
		const auto r7x = INDEX (r3x) + SIZEOF<BLOCK>::value ;
		const auto r8x = alignto (r7x ,align_len) ;
		return reinterpret_cast<UNSAFE_PTR<void>> (r8x) ;
	}

	static void free (CREF<UNSAFE_PTR<void>> addr) {
		const auto r1x = curr () ;
		const auto r2x = r1x->mPrev ;
		assert (r2x != NULL) ;
		const auto r3x = INDEX (r2x) + SIZEOF<BLOCK>::value ;
		const auto r4x = r3x + r2x->mBlockSize ;
		assert (between (INDEX (addr) ,r3x ,r4x)) ;
		r2x->mNext = NULL ;
		r2x->mBlockSize += r1x->mBlockSize ;
	}

private:
	static UNSAFE_PTR<BLOCK> root () {
		thread_local auto M_STORAGE = TEMP<BYTE[4096]> () ;
		const auto r1x = [&] () {
			const auto r2x = INDEX (&M_STORAGE) ;
			UNSAFE_PTR<BLOCK> ret = reinterpret_cast<UNSAFE_PTR<BLOCK>> (r2x) ;
			ret->mPrev = NULL ;
			ret->mNext = NULL ;
			ret->mBlockSize = SIZEOF<typeof (M_STORAGE)>::value ;
			ret->mBlockCheck = LENGTH (0XCCCCCCCCCCCCCCCC) ;
			return forward (ret) ;
		} ;
		thread_local auto M_ROOT = r1x () ;
		return M_ROOT ;
	}

	static UNSAFE_PTR<BLOCK> curr () {
		UNSAFE_PTR<BLOCK> ret = root () ;
		while (TRUE) {
			if (ret == NULL)
				break ;
			if (ret->mNext == NULL)
				break ;
			ret = ret->mNext ;
		}
		assert (ret != NULL) ;
		return forward (ret) ;
	}
} ;

template <class...>
trait AUTO_IMPLHOLDER_HELP ;

template <class ARG1>
trait AUTO_IMPLHOLDER_HELP<ARG1> {
	struct Dependent ;
	using EXTERN = typename DEPENDENT<AUTO_HELP<> ,Dependent>::EXTERN ;
	using Holder = typename EXTERN::Holder ;

	class ImplHolder ;
} ;

class AUTO_HELP<>::AUTO {
private:
	using Holder = typename EXTERN::Holder ;
	using HeapProc = typename EXTERN::HeapProc ;

private:
	UNSAFE_PTR<Holder> mPointer ;

public:
	implicit AUTO () = delete ;

	template <class ARG1 ,class = ENABLE<ENUM_NOT<IS_SAME<AUTO ,REMOVE_CVR<ARG1>>>>>
	implicit AUTO (DEF<ARG1 &>) = delete ;

	template <class ARG1 ,class = ENABLE<ENUM_NOT<IS_SAME<AUTO ,REMOVE_CVR<ARG1>>>>>
	implicit AUTO (DEF<ARG1 &&> that) :
		delegate AUTO (PH0) {
		struct Depentent ;
		using R1X = typeof (that) ;
		using R2X = typename DEPENDENT<AUTO_IMPLHOLDER_HELP<R1X> ,Depentent>::ImplHolder ;
		const auto r1x = HeapProc::alloc (SIZEOF<R2X>::value ,ALIGNOF<R2X>::value) ;
		assert (r1x != NULL) ;
		mPointer = new (r1x) R2X (forward (that)) ;
	}

	implicit ~AUTO () noexcept {
		if (mPointer == NULL)
			return ;
		mPointer->~Holder () ;
		HeapProc::free (mPointer) ;
		mPointer = NULL ;
	}

	implicit AUTO (CREF<AUTO>) = delete ;

	inline void operator= (CREF<AUTO>) = delete ;

	implicit AUTO (RREF<AUTO> that) noexcept :
		delegate AUTO (PH0) {
		auto &thix = (*this) ;
		swap (thix ,that) ;
	}

	inline void operator= (RREF<AUTO>) = delete ;

	template <class ARG1>
	REMOVE_TYPEID<ARG1> poll (CREF<ARG1> id) {
		struct Depentent ;
		using R1X = typeof (id) ;
		using R2X = typename DEPENDENT<AUTO_IMPLHOLDER_HELP<R1X> ,Depentent>::ImplHolder ;
		assert (mPointer != NULL) ;
		const auto r1x = type_mid (typeas<R2X>::id) ;
		const auto r2x = mPointer->type_mid () ;
		assert (r1x == r2x) ;
		return m_derived (typeas<R2X>::id).poll () ;
	}

private:
	explicit AUTO (CREF<typeof (PH0)>) noexcept :
		delegate mPointer (NULL) {}

	template <class ARG1>
	VREF<REMOVE_TYPEID<ARG1>> m_derived[[nodiscard]] (CREF<ARG1> id) {
		using R1X = typeof (id) ;
		return static_cast<VREF<R1X>> ((*mPointer)) ;
	}
} ;

template <class UNIT1>
class AUTO_IMPLHOLDER_HELP<UNIT1>::ImplHolder :
	public Holder {
private:
	UNIT1 mValue ;

public:
	implicit ImplHolder () = delete ;

	explicit ImplHolder (RREF<UNIT1> that) :
		delegate mValue (forward (that)) {}

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

using AUTO = typename U::AUTO_HELP<>::AUTO ;

namespace U {
struct FUNCTION_BAD {
	template <class ARG1>
	inline REMOVE_TYPEID<ARG1> operator() (CREF<ARG1> id) const {
		using R1X = typeof (id) ;
		assert (FALSE) ;
		const auto r1x = [&] ()->AUTO {
			return ZERO ;
		} ;
		return R1X (r1x ()) ;
	}
} ;
} ;

static constexpr auto bad = U::FUNCTION_BAD () ;

namespace U {
template <class...>
trait CAST_HELP ;

template <class ARG1>
trait CAST_HELP<ARG1> {
	class CAST ;
} ;

template <class UNIT1>
class CAST_HELP<UNIT1>::CAST {
public:
	static UNIT1 from (RREF<AUTO> obj) {
		return obj.poll (typeas<UNIT1>::id) ;
	}
} ;
} ;

template <class UNIT1>
using CAST = typename U::CAST_HELP<UNIT1>::CAST ;

namespace U {
template <class...>
trait BOX_HELP ;

template <class ARG1>
trait BOX_HELP<ARG1 ,REQUIRE<IS_INTERFACE<ARG1>>> {
	require (IS_INTERFACE<ARG1>) ;

	class Box ;
} ;

template <class UNIT1>
class BOX_HELP<UNIT1 ,REQUIRE<IS_INTERFACE<UNIT1>>>::Box {
private:
	UNSAFE_PTR<UNIT1> mPointer ;

public:
	implicit Box () noexcept :
		delegate Box (PH0) {}

	implicit Box (CREF<typeof (NULL)>) noexcept :
		delegate Box (PH0) {}

	template <class ARG1 ,class = ENABLE<IS_EXTEND<UNIT1 ,REMOVE_CVR<ARG1>>>>
	implicit Box (DEF<ARG1 &>) = delete ;

	template <class ARG1 ,class = ENABLE<IS_EXTEND<UNIT1 ,REMOVE_CVR<ARG1>>>>
	implicit Box (DEF<ARG1 &&> that) :
		delegate Box (PH0) {
		using R1X = typeof (that) ;
		require (IS_EXTEND<UNIT1 ,R1X>) ;
		mPointer = new R1X (forward (that)) ;
	}

	implicit ~Box () noexcept {
		if (mPointer == NULL)
			return ;
		delete mPointer ;
		mPointer = NULL ;
	}

	implicit Box (CREF<Box>) = delete ;

	inline void operator= (CREF<Box>) = delete ;

	implicit Box (RREF<Box> that) noexcept :
		delegate Box (PH0) {
		auto &thix = (*this) ;
		swap (thix ,that) ;
	}

	inline void operator= (RREF<Box> that) noexcept {
		auto &thix = (*this) ;
		if ((&thix) == (&that))
			return ;
		thix.~Box () ;
		new (&thix) Box (forward (that)) ;
	}

	BOOL exist () const {
		return mPointer != NULL ;
	}

	inline BOOL operator== (CREF<typeof (NULL)>) const {
		return !exist () ;
	}

	inline BOOL operator!= (CREF<typeof (NULL)>) const {
		return exist () ;
	}

	VREF<UNIT1> to[[nodiscard]] () {
		assert (exist ()) ;
		return (*mPointer) ;
	}

	inline implicit operator VREF<UNIT1> () leftvalue {
		return self ;
	}

	inline UNSAFE_PTR<VREF<UNIT1>> operator-> () {
		return (&self) ;
	}

	CREF<UNIT1> to[[nodiscard]] () const {
		assert (exist ()) ;
		return (*mPointer) ;
	}

	inline implicit operator CREF<UNIT1> () const leftvalue {
		return self ;
	}

	inline UNSAFE_PTR<CREF<UNIT1>> operator-> () const {
		return (&self) ;
	}

private:
	explicit Box (CREF<typeof (PH0)>) noexcept :
		delegate mPointer (NULL) {}
} ;
} ;

template <class UNIT1>
using Box = typename U::BOX_HELP<UNIT1 ,void>::Box ;

namespace U {
template <class...>
trait CELL_HELP ;

template <class ARG1>
trait CELL_HELP<ARG1 ,REQUIRE<IS_CLONEABLE<ARG1>>> {
	require (IS_CLONEABLE<ARG1>) ;

	class Cell ;
} ;

template <class UNIT1>
class CELL_HELP<UNIT1 ,REQUIRE<IS_CLONEABLE<UNIT1>>>::Cell {
private:
	mutable TEMP<UNIT1> mValue ;
	BOOL mExist ;

public:
	implicit Cell () noexcept :
		delegate Cell (PH0) {}

	implicit Cell (CREF<typeof (NULL)>) noexcept :
		delegate Cell (PH0) {}

	implicit Cell (RREF<UNIT1> that) :
		delegate Cell (PH0) {
		new (&m_fake ()) UNIT1 (forward (that)) ;
		mExist = TRUE ;
	}

	implicit ~Cell () noexcept {
		if (!mExist)
			return ;
		m_fake ().~UNIT1 () ;
		mExist = FALSE ;
	}

	implicit Cell (CREF<Cell> that) :
		delegate Cell (PH0) {
		auto &thix = (*this) ;
		if (!that.exist ())
			return ;
		thix = Cell (that.fetch ()) ;
	}

	inline void operator= (CREF<Cell> that) {
		auto &thix = (*this) ;
		if ((&thix) == (&that))
			return ;
		thix.~Cell () ;
		new (&thix) Cell (forward (that)) ;
	}

	implicit Cell (RREF<Cell> that) noexcept :
		delegate Cell (PH0) {
		auto &thix = (*this) ;
		swap (thix ,that) ;
	}

	inline void operator= (RREF<Cell> that) noexcept {
		auto &thix = (*this) ;
		if ((&thix) == (&that))
			return ;
		thix.~Cell () ;
		new (&thix) Cell (forward (that)) ;
	}

	BOOL exist () const {
		return mExist ;
	}

	inline BOOL operator== (CREF<typeof (NULL)>) const {
		return !exist () ;
	}

	inline BOOL operator!= (CREF<typeof (NULL)>) const {
		return exist () ;
	}

	UNIT1 fetch () const {
		assert (exist ()) ;
		return m_fake () ;
	}

	void store (CREF<UNIT1> obj) const {
		assert (exist ()) ;
		m_fake () = obj ;
	}

	UNIT1 exchange (CREF<UNIT1> obj) const {
		assert (exist ()) ;
		UNIT1 ret = m_fake () ;
		m_fake () = obj ;
		return forward (ret) ;
	}

	BOOL change (VREF<UNIT1> expect ,CREF<UNIT1> obj) const {
		assert (exist ()) ;
		if (m_fake () != expect) {
			expect = m_fake () ;
			return FALSE ;
		}
		m_fake () = obj ;
		return TRUE ;
	}

private:
	explicit Cell (CREF<typeof (PH0)>) noexcept :
		delegate mExist (FALSE) {}

	VREF<UNIT1> m_fake[[nodiscard]] () const {
		return reinterpret_cast<VREF<UNIT1>> (mValue) ;
	}
} ;
} ;

template <class UNIT1>
using Cell = typename U::CELL_HELP<UNIT1 ,void>::Cell ;

namespace U {
template <class...>
trait RC_HELP ;

template <class ARG1>
trait RC_HELP<ARG1> {
	struct NODE ;

	class RC ;
} ;

template <class UNIT1>
struct RC_HELP<UNIT1>::NODE {
	UNIT1 mValue ;
	LENGTH mCounter ;
} ;

template <class UNIT1>
class RC_HELP<UNIT1>::RC {
private:
	UNSAFE_PTR<NODE> mPointer ;

public:
	implicit RC () noexcept :
		delegate RC (PH0) {}

	implicit RC (CREF<typeof (NULL)>) noexcept :
		delegate RC (PH0) {}

	implicit RC (RREF<UNIT1> that) :
		delegate RC (PH0) {
		auto &thix = (*this) ;
		const auto r1x = new NODE {forward (that) ,ZERO} ;
		thix = RC (PH0 ,r1x) ;
	}

	implicit ~RC () noexcept {
		if (mPointer == NULL)
			return ;
		if switch_once (TRUE) {
			const auto r1x = --mPointer->mCounter ;
			if (r1x > ZERO)
				discard ;
			delete mPointer ;
		}
		mPointer = NULL ;
	}

	implicit RC (CREF<RC> that) :
		delegate RC (PH0) {
		auto &thix = (*this) ;
		if (!that.exist ())
			return ;
		assert (that.mPointer->mCounter > ZERO) ;
		thix = RC (PH0 ,that.mPointer) ;
	}

	inline void operator= (CREF<RC> that) {
		auto &thix = (*this) ;
		if ((&thix) == (&that))
			return ;
		thix.~RC () ;
		new (&thix) RC (forward (that)) ;
	}

	implicit RC (RREF<RC> that) noexcept :
		delegate RC (PH0) {
		auto &thix = (*this) ;
		swap (thix ,that) ;
	}

	inline void operator= (RREF<RC> that) noexcept {
		auto &thix = (*this) ;
		if ((&thix) == (&that))
			return ;
		thix.~RC () ;
		new (&thix) RC (forward (that)) ;
	}

	BOOL exist () const {
		return mPointer != NULL ;
	}

	inline BOOL operator== (CREF<typeof (NULL)>) const {
		return !exist () ;
	}

	inline BOOL operator!= (CREF<typeof (NULL)>) const {
		return exist () ;
	}

	CREF<UNIT1> to[[nodiscard]] () const {
		assert (exist ()) ;
		return mPointer->mValue ;
	}

	inline implicit operator CREF<UNIT1> () const leftvalue {
		return self ;
	}

	inline UNSAFE_PTR<CREF<UNIT1>> operator-> () const {
		return (&self) ;
	}

private:
	explicit RC (CREF<typeof (PH0)>) noexcept :
		delegate mPointer (NULL) {}

	explicit RC (CREF<typeof (PH0)> ,CREF<UNSAFE_PTR<NODE>> pointer) noexcept {
		assert (pointer != NULL) ;
		mPointer = pointer ;
		++mPointer->mCounter ;
	}
} ;
} ;

template <class UNIT1>
using RC = typename U::RC_HELP<UNIT1>::RC ;

namespace U {
template <class...>
trait ITERATOR_HELP ;

template <>
trait ITERATOR_HELP<> {
	class IteratorRange ;

	class Iterator ;
} ;

class ITERATOR_HELP<>::Iterator {
private:
	INDEX mCurr ;

public:
	implicit Iterator () = delete ;

	explicit Iterator (CREF<INDEX> curr) {
		mCurr = curr ;
	}

	inline BOOL operator!= (CREF<Iterator> that) const {
		return mCurr != that.mCurr ;
	}

	inline void operator++ () {
		mCurr++ ;
	}

	inline CREF<INDEX> operator*[[nodiscard]] () const {
		return mCurr ;
	}
} ;

class ITERATOR_HELP<>::IteratorRange {
private:
	INDEX mBegin ;
	INDEX mEnd ;

public:
	implicit IteratorRange () = delete ;

	explicit IteratorRange (CREF<INDEX> begin_ ,CREF<INDEX> end_) {
		mBegin = begin_ ;
		mEnd = max (begin_ ,end_) ;
	}

	Iterator begin () const {
		return Iterator (mBegin) ;
	}

	Iterator end () const {
		return Iterator (mEnd) ;
	}
} ;
} ;

namespace U {
struct FUNCTION_RANGE {
	using IteratorRange = typename U::ITERATOR_HELP<>::IteratorRange ;

	inline IteratorRange operator() (CREF<INDEX> begin ,CREF<INDEX> end) const {
		return IteratorRange (begin ,end) ;
	}
} ;
} ;

static constexpr auto range = U::FUNCTION_RANGE () ;

namespace U {
template <class...>
trait SLICE_HELP ;

template <class ARG1>
trait SLICE_HELP<ARG1 ,REQUIRE<IS_STR<ARG1>>> {
	require (IS_STR<ARG1>) ;

	struct EXTERN {
		interface Holder ;
	} ;

	class Slice ;
} ;

template <class UNIT1>
interface SLICE_HELP<UNIT1 ,REQUIRE<IS_STR<UNIT1>>>::EXTERN::Holder :
	public Interface {
	virtual AUTO clone () const = 0 ;
	virtual LENGTH size () const = 0 ;
	virtual UNIT1 get (CREF<INDEX> index) const = 0 ;
} ;

template <class...>
trait SLICE_IMPLHOLDER_HELP ;

template <class ARG1>
trait SLICE_IMPLHOLDER_HELP<ARG1> {
	class ImplHolder ;
} ;

template <class UNIT1>
class SLICE_HELP<UNIT1 ,REQUIRE<IS_STR<UNIT1>>>::Slice {
private:
	using Holder = typename EXTERN::Holder ;

private:
	Box<Holder> mPointer ;

public:
	implicit Slice () = default ;

	template <class ARG1 ,class ARG2>
	explicit Slice (CREF<ARG1> id ,DEF<ARG2 &&> that) {
		struct Dependent ;
		using R1X = typename DEPENDENT<SLICE_IMPLHOLDER_HELP<ARG2> ,Dependent>::ImplHolder ;
		mPointer = R1X (forward (that)) ;
	}

	implicit Slice (CREF<Slice> that) {
		if (that.mPointer == NULL)
			return ;
		mPointer = CAST<Box<Holder>>::from (mPointer->clone ()) ;
	}

	inline void operator= (CREF<Slice> that) {
		auto &thix = (*this) ;
		if ((&thix) == (&that))
			return ;
		thix.~Slice () ;
		new (&thix) Slice (forward (that)) ;
	}

	implicit Slice (RREF<Slice> that) noexcept {
		auto &thix = (*this) ;
		swap (thix ,that) ;
	}

	inline void operator= (RREF<Slice> that) noexcept {
		auto &thix = (*this) ;
		if ((&thix) == (&that))
			return ;
		thix.~Slice () ;
		new (&thix) Slice (forward (that)) ;
	}

	static Slice nullopt[[nodiscard]] () {
		static const auto M_NULLOPT = Slice () ;
		return M_NULLOPT ;
	}

	LENGTH size () const {
		if (mPointer == NULL)
			return ZERO ;
		return mPointer->size () ;
	}

	UNIT1 get (CREF<INDEX> index) const {
		assert (between (index ,0 ,size ())) ;
		return mPointer->get (index) ;
	}

	inline UNIT1 operator[] (CREF<INDEX> index) const {
		return get (index) ;
	}

	BOOL equal (CREF<Slice> that) const {
		if (size () != that.size ())
			return FALSE ;
		for (auto &&i : range (0 ,size ())) {
			if (get (i) != that.get (i))
				return FALSE ;
		}
		return TRUE ;
	}

	inline BOOL operator== (CREF<Slice> that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (CREF<Slice> that) const {
		return !equal (that) ;
	}

	FLAG compr (CREF<Slice> that) const {
		const auto r1x = min (size () ,that.size ()) ;
		for (auto &&i : range (0 ,r1x)) {
			const auto r2x = compare (get (i) ,that.get (i)) ;
			if (r2x != ZERO)
				return r2x ;
		}
		const auto r3x = compare (size () ,that.size ()) ;
		if (r3x != ZERO)
			return r3x ;
		return ZERO ;
	}

	inline BOOL operator< (CREF<Slice> that) const {
		return compr (that) < ZERO ;
	}

	inline BOOL operator<= (CREF<Slice> that) const {
		return compr (that) <= ZERO ;
	}

	inline BOOL operator> (CREF<Slice> that) const {
		return compr (that) > ZERO ;
	}

	inline BOOL operator>= (CREF<Slice> that) const {
		return compr (that) >= ZERO ;
	}

	FLAG hash () const {
		FLAG ret = hashcode () ;
		for (auto &&i : range (0 ,size ())) {
			const auto r1x = FLAG (get (i)) ;
			ret = hashcode (ret ,r1x) ;
		}
		return forward (ret) ;
	}
} ;
} ;

template <class UNIT1>
using Slice = typename U::SLICE_HELP<UNIT1 ,void>::Slice ;

namespace U {
template <class...>
trait CLAZZ_HELP ;

template <>
trait CLAZZ_HELP<> {
	struct EXTERN {
		interface Holder ;
	} ;

	class Clazz ;
} ;

interface CLAZZ_HELP<>::EXTERN::Holder :
	public Interface {
	virtual AUTO clone () const = 0 ;
	virtual LENGTH type_size () const = 0 ;
	virtual LENGTH type_align () const = 0 ;
	virtual FLAG type_mid () const = 0 ;
	virtual Slice<STR> type_name () const = 0 ;
} ;

class CLAZZ_HELP<>::Clazz {
private:
	using Holder = typename EXTERN::Holder ;

private:
	Box<Holder> mPointer ;

public:
	implicit Clazz () = default ;

	implicit Clazz (CREF<Clazz> that) {
		if (that.mPointer == NULL)
			return ;
		mPointer = CAST<Box<Holder>>::from (mPointer->clone ()) ;
	}

	inline void operator= (CREF<Clazz> that) {
		auto &thix = (*this) ;
		if ((&thix) == (&that))
			return ;
		thix.~Clazz () ;
		new (&thix) Clazz (forward (that)) ;
	}

	implicit Clazz (RREF<Clazz> that) noexcept {
		auto &thix = (*this) ;
		swap (thix ,that) ;
	}

	inline void operator= (RREF<Clazz> that) noexcept {
		auto &thix = (*this) ;
		if ((&thix) == (&that))
			return ;
		thix.~Clazz () ;
		new (&thix) Clazz (forward (that)) ;
	}

	BOOL equal (CREF<Clazz> that) const {
		if (mPointer == NULL && that.mPointer == NULL)
			return TRUE ;
		if (mPointer == NULL || that.mPointer == NULL)
			return FALSE ;
		if (mPointer->type_mid () != that.type_mid ())
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (CREF<Clazz> that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (CREF<Clazz> that) const {
		return !equal (that) ;
	}

	FLAG compr (CREF<Clazz> that) const {
		if (mPointer == NULL && that.mPointer == NULL)
			return ZERO ;
		if (mPointer == NULL)
			return FLAG (-1) ;
		if (that.mPointer == NULL)
			return FLAG (+1) ;
		const auto r1x = compare (type_mid () ,that.type_mid ()) ;
		if (r1x != ZERO)
			return r1x ;
		return ZERO ;
	}

	inline BOOL operator< (CREF<Clazz> that) const {
		return compr (that) < ZERO ;
	}

	inline BOOL operator<= (CREF<Clazz> that) const {
		return compr (that) <= ZERO ;
	}

	inline BOOL operator> (CREF<Clazz> that) const {
		return compr (that) > ZERO ;
	}

	inline BOOL operator>= (CREF<Clazz> that) const {
		return compr (that) >= ZERO ;
	}

	FLAG hash () const {
		if (mPointer == NULL)
			return ZERO ;
		return mPointer->type_mid () ;
	}

	LENGTH type_size () const {
		if (mPointer == NULL)
			return ZERO ;
		return mPointer->type_size () ;
	}

	LENGTH type_align () const {
		if (mPointer == NULL)
			return ZERO ;
		return mPointer->type_size () ;
	}

	FLAG type_mid () const {
		if (mPointer == NULL)
			return ZERO ;
		return mPointer->type_size () ;
	}

	Slice<STR> type_name () const {
		if (mPointer == NULL)
			return Slice<STR>::nullopt () ;
		return mPointer->type_name () ;
	}
} ;
} ;

using Clazz = typename U::CLAZZ_HELP<>::Clazz ;

namespace U {
template <class...>
trait EXCEPTION_HELP ;

template <>
trait EXCEPTION_HELP<> {
	class Exception ;
} ;

class EXCEPTION_HELP<>::Exception {
private:
	Slice<STR> mWhat ;

public:
	implicit Exception () = default ;

	CREF<Slice<STR>> what[[nodiscard]] () {
		return mWhat ;
	}

	void raise[[noreturn]] () {
		auto &thix = (*this) ;
		throw thix ;
	}
} ;
} ;

using Exception = typename U::EXCEPTION_HELP<>::Exception ;
} ;