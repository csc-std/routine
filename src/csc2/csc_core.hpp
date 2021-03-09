#pragma once

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
enum class STRU8 :unsigned char ;
} ;

using STRA = char ;
using STRW = wchar_t ;
using STRU8 = U::STRU8 ;
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

template <VAR ARG1>
trait ENUMID {
	static constexpr auto value = ARG1 ;
} ;

template <class ARG1>
trait ENUMAS<ARG1> {
	static constexpr auto value = ARG1::value ;
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

namespace U {
template <class...>
trait REMOVE_TYPEID_HELP ;

template <>
trait REMOVE_TYPEID_HELP<void> ;

template <class ARG1>
trait REMOVE_TYPEID_HELP<ARG1> {
	using R1X = typename std::remove_reference<ARG1>::type ;
	using R2X = typename std::remove_cv<R1X>::type ;

	using RET = R2X ;
} ;

template <class ARG1>
trait REMOVE_TYPEID_HELP<TYPEID<ARG1>> {
	using R1X = typename std::remove_reference<ARG1>::type ;
	using R2X = typename std::remove_cv<R1X>::type ;

	using RET = R2X ;
} ;
} ;

template <class UNIT>
using REMOVE_TYPEID = typename U::REMOVE_TYPEID_HELP<UNIT>::RET ;

template <class UNIT>
using DEF = UNIT ;

template <class UNIT>
using VREF = REMOVE_TYPEID<UNIT> & ;

template <class UNIT>
using CREF = const REMOVE_TYPEID<UNIT> & ;

template <class UNIT>
using RREF = REMOVE_TYPEID<UNIT> && ;

using ENUM_USED = enumof (-2) ;
using ENUM_NONE = enumof (-1) ;
using ENUM_ZERO = enumof (+0) ;
using ENUM_IDEN = enumof (+1) ;

template <class UNIT>
using SIZEOF = enumof (sizeof (UNIT)) ;

template <class UNIT>
using ALIGNOF = enumof (alignof (UNIT)) ;

namespace U {
template <class...>
trait COUNTOF_HELP ;

template <class...ARGS>
trait COUNTOF_HELP<typeas<ARGS...>> {
	using RET = enumof (sizeof... (ARGS)) ;
} ;
} ;

template <class UNIT>
using COUNTOF = typename U::COUNTOF_HELP<UNIT>::RET ;

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

template <class UNIT>
using REQUIRE = typename U::REQUIRE_HELP<UNIT>::RET ;

namespace U {
template <class...>
trait ENABLE_HELP ;

template <class ARG1 ,class ARG2>
trait ENABLE_HELP<ARG1 ,ARG2 ,
	REQUIRE<IS_SAME<ARG1 ,ENUM_IDEN>>> {
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
trait CONDITIONAL_HELP<ARG1 ,ARG2 ,ARG3 ,
	REQUIRE<IS_SAME<ARG1 ,ENUM_IDEN>>> {
	require (IS_SAME<ARG1 ,ENUM_IDEN>) ;

	using RET = ARG2 ;
} ;

template <class ARG1 ,class ARG2 ,class ARG3>
trait CONDITIONAL_HELP<ARG1 ,ARG2 ,ARG3 ,
	REQUIRE<IS_SAME<ARG1 ,ENUM_ZERO>>> {
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

template <class UNIT>
using IS_ENUM = typename U::IS_ENUM_HELP<UNIT>::RET ;

template <class UNIT>
using ENUM_CHECK = ENABLE<IS_ENUM<UNIT> ,UNIT> ;

template <class UNIT1 ,class UNIT2>
using ENUM_EQUAL = enumof (ENUM_CHECK<UNIT1>::value == ENUM_CHECK<UNIT2>::value) ;

template <class UNIT1 ,class UNIT2>
using ENUM_NOT_EQUAL = enumof (ENUM_CHECK<UNIT1>::value != ENUM_CHECK<UNIT2>::value) ;

template <class UNIT>
using ENUM_NOT = ENUM_EQUAL<UNIT ,ENUM_ZERO> ;

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

template <class UNIT>
using ENUM_EQ_ZERO = ENUM_EQUAL<UNIT ,ENUM_ZERO> ;

template <class UNIT>
using ENUM_LT_ZERO = ENUM_COMPR_LT<UNIT ,ENUM_ZERO> ;

template <class UNIT>
using ENUM_GT_ZERO = ENUM_COMPR_GT<UNIT ,ENUM_ZERO> ;

template <class UNIT>
using ENUM_EQ_IDEN = ENUM_EQUAL<UNIT ,ENUM_IDEN> ;

template <class UNIT>
using ENUM_LT_IDEN = ENUM_COMPR_LT<UNIT ,ENUM_IDEN> ;

template <class UNIT>
using ENUM_GT_IDEN = ENUM_COMPR_GT<UNIT ,ENUM_IDEN> ;

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

template <class UNIT>
using ENUM_INC = ENUM_ADD<UNIT ,ENUM_IDEN> ;

template <class UNIT>
using ENUM_DEC = ENUM_SUB<UNIT ,ENUM_IDEN> ;

namespace U {
template <class...>
trait IS_TYPE_HELP ;

template <class...ARGS>
trait IS_TYPE_HELP<TYPEAS<ARGS...>> {
	using RET = ENUM_IDEN ;
} ;
} ;

template <class UNIT>
using IS_TYPE = typename U::IS_TYPE_HELP<UNIT>::RET ;

template <class UNIT>
using TYPE_CHECK = ENABLE<IS_TYPE<UNIT> ,UNIT> ;

namespace U {
template <class...>
trait TYPE_FIRST_ONE_HELP ;

template <class ARG1 ,class...ARGS>
trait TYPE_FIRST_ONE_HELP<typeas<ARG1 ,ARGS...>> {
	using RET = ARG1 ;
} ;
} ;

template <class UNIT>
using TYPE_FIRST_ONE = typename U::TYPE_FIRST_ONE_HELP<TYPE_CHECK<UNIT>>::RET ;

namespace U {
template <class...>
trait TYPE_FIRST_REST_HELP ;

template <class ARG1 ,class...ARGS>
trait TYPE_FIRST_REST_HELP<typeas<ARG1 ,ARGS...>> {
	using RET = typeas<ARGS...> ;
} ;
} ;

template <class UNIT>
using TYPE_FIRST_REST = typename U::TYPE_FIRST_REST_HELP<TYPE_CHECK<UNIT>>::RET ;

namespace U {
template <class...>
trait TYPE_SECOND_ONE_HELP ;

template <class ARG1 ,class ARG2 ,class...ARGS>
trait TYPE_SECOND_ONE_HELP<typeas<ARG1 ,ARG2 ,ARGS...>> {
	using RET = ARG2 ;
} ;
} ;

template <class UNIT>
using TYPE_SECOND_ONE = typename U::TYPE_SECOND_ONE_HELP<TYPE_CHECK<UNIT>>::RET ;

namespace U {
template <class...>
trait TYPE_SECOND_REST_HELP ;

template <class ARG1 ,class ARG2 ,class...ARGS>
trait TYPE_SECOND_REST_HELP<typeas<ARG1 ,ARG2 ,ARGS...>> {
	using RET = typeas<ARGS...> ;
} ;
} ;

template <class UNIT>
using TYPE_SECOND_REST = typename U::TYPE_SECOND_REST_HELP<TYPE_CHECK<UNIT>>::RET ;

namespace U {
template <class...>
trait TYPE_UNWRAP_HELP ;

template <class ARG1>
trait TYPE_UNWRAP_HELP<ARG1 ,
	REQUIRE<ENUM_EQ_IDEN<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_IDEN<COUNTOF<ARG1>>) ;

	using RET = TYPE_FIRST_ONE<ARG1> ;
} ;
} ;

template <class UNIT>
using TYPE_UNWRAP = typename U::TYPE_UNWRAP_HELP<UNIT ,void>::RET ;

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
trait TYPE_REPEAT_HELP<ARG1 ,ARG2 ,
	REQUIRE<ENUM_EQ_ZERO<ARG2>>> {
	require (ENUM_EQ_ZERO<ARG2>) ;

	using RET = typeas<> ;
} ;

template <class ARG1 ,class ARG2>
trait TYPE_REPEAT_HELP<ARG1 ,ARG2 ,
	REQUIRE<ENUM_GT_ZERO<ARG2>>> {
	require (ENUM_GT_ZERO<ARG2>) ;

	using R1X = typename TYPE_REPEAT_HELP<ARG1 ,ENUM_DEC<ARG2> ,void>::RET ;

	using RET = TYPE_CAT<ARG1 ,R1X> ;
} ;
} ;

template <class UNIT ,class SIZE>
using TYPE_REPEAT = typename U::TYPE_REPEAT_HELP<typeas<UNIT> ,SIZE ,void>::RET ;

namespace U {
template <class...>
trait TYPE_REVERSE_HELP ;

template <class ARG1>
trait TYPE_REVERSE_HELP<ARG1 ,
	REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;

	using RET = typeas<> ;
} ;

template <class ARG1>
trait TYPE_REVERSE_HELP<ARG1 ,
	REQUIRE<ENUM_GT_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_GT_ZERO<COUNTOF<ARG1>>) ;

	using R1X = TYPE_FIRST_ONE<ARG1> ;
	using R2X = typename TYPE_REVERSE_HELP<TYPE_FIRST_REST<ARG1>>::RET ;

	using RET = TYPE_CAT<R2X ,typeas<R1X>> ;
} ;
} ;

template <class UNIT>
using TYPE_REVERSE = typename U::TYPE_REVERSE_HELP<UNIT ,void>::RET ;

namespace U {
template <class...>
trait TYPE_PICK_HELP ;

template <class ARG1 ,class ARG2>
trait TYPE_PICK_HELP<ARG1 ,ARG2 ,
	REQUIRE<ENUM_EQ_ZERO<ARG2>>> {
	require (ENUM_EQ_ZERO<ARG2>) ;

	using RET = TYPE_FIRST_ONE<ARG1> ;
} ;

template <class ARG1 ,class ARG2>
trait TYPE_PICK_HELP<ARG1 ,ARG2 ,
	REQUIRE<ENUM_GT_ZERO<ARG2>>> {
	require (ENUM_GT_ZERO<ARG2>) ;

	using RET = typename TYPE_PICK_HELP<TYPE_FIRST_REST<ARG1> ,ENUM_DEC<ARG2>>::RET ;
} ;
} ;

template <class LIST ,class INDEX>
using TYPE_PICK = typename U::TYPE_PICK_HELP<LIST ,INDEX ,void>::RET ;

namespace U {
template <class...>
trait ENUM_ALL_HELP ;

template <class ARG1>
trait ENUM_ALL_HELP<ARG1 ,
	REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;

	using RET = ENUM_IDEN ;
} ;

template <class ARG1>
trait ENUM_ALL_HELP<ARG1 ,
	REQUIRE<ENUM_GT_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_GT_ZERO<COUNTOF<ARG1>>) ;

	using R1X = ENUM_NOT<ENUM_EQ_ZERO<TYPE_FIRST_ONE<ARG1>>> ;
	using R2X = typename ENUM_ALL_HELP<TYPE_FIRST_REST<ARG1> ,void>::RET ;

	using RET = CONDITIONAL<R1X ,R2X ,ENUM_ZERO> ;
} ;
} ;

template <class...ARGS>
using ENUM_ALL = typename U::ENUM_ALL_HELP<typeas<ARGS...> ,void>::RET ;

namespace U {
template <class...>
trait ENUM_ANY_HELP ;

template <class ARG1>
trait ENUM_ANY_HELP<ARG1 ,
	REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;

	using RET = ENUM_ZERO ;
} ;

template <class ARG1>
trait ENUM_ANY_HELP<ARG1 ,
	REQUIRE<ENUM_GT_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_GT_ZERO<COUNTOF<ARG1>>) ;

	using R1X = ENUM_NOT<ENUM_EQ_ZERO<TYPE_FIRST_ONE<ARG1>>> ;
	using R2X = typename ENUM_ANY_HELP<TYPE_FIRST_REST<ARG1> ,void>::RET ;

	using RET = CONDITIONAL<R1X ,ENUM_IDEN ,R2X> ;
} ;
} ;

template <class...ARGS>
using ENUM_ANY = typename U::ENUM_ANY_HELP<typeas<ARGS...> ,void>::RET ;

namespace U {
template <class...>
trait IS_ALL_SAME_HELP ;

template <class ARG1>
trait IS_ALL_SAME_HELP<ARG1 ,
	REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;

	using RET = ENUM_IDEN ;
} ;

template <class ARG1>
trait IS_ALL_SAME_HELP<ARG1 ,
	REQUIRE<ENUM_EQ_IDEN<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_IDEN<COUNTOF<ARG1>>) ;

	using RET = ENUM_IDEN ;
} ;

template <class ARG1>
trait IS_ALL_SAME_HELP<ARG1 ,
	REQUIRE<ENUM_GT_IDEN<COUNTOF<ARG1>>>> {
	require (ENUM_GT_IDEN<COUNTOF<ARG1>>) ;

	using R1X = TYPE_FIRST_ONE<ARG1> ;
	using R2X = TYPE_SECOND_ONE<ARG1> ;
	using R3X = typename IS_ALL_SAME_HELP<TYPE_CAT<R1X ,TYPE_SECOND_REST<ARG1>> ,void>::RET ;

	using RET = ENUM_ALL<IS_SAME<R1X ,R2X> ,R3X> ;
} ;
} ;

template <class...ARGS>
using IS_ALL_SAME = typename U::IS_ALL_SAME_HELP<typeas<ARGS...> ,void>::RET ;

namespace U {
template <class...>
trait IS_ANY_SAME_HELP ;

template <class ARG1>
trait IS_ANY_SAME_HELP<ARG1 ,
	REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;

	using RET = ENUM_ZERO ;
} ;

template <class ARG1>
trait IS_ANY_SAME_HELP<ARG1 ,
	REQUIRE<ENUM_EQ_IDEN<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_IDEN<COUNTOF<ARG1>>) ;

	using RET = ENUM_ZERO ;
} ;

template <class ARG1>
trait IS_ANY_SAME_HELP<ARG1 ,
	REQUIRE<ENUM_GT_IDEN<COUNTOF<ARG1>>>> {
	require (ENUM_GT_IDEN<COUNTOF<ARG1>>) ;

	using R1X = TYPE_FIRST_ONE<ARG1> ;
	using R2X = TYPE_SECOND_ONE<ARG1> ;
	using R3X = typename IS_ANY_SAME_HELP<TYPE_CAT<R1X ,TYPE_SECOND_REST<ARG1>>>::RET ;
	using R4X = typename IS_ANY_SAME_HELP<TYPE_CAT<R2X ,TYPE_SECOND_REST<ARG1>>>::RET ;

	using RET = ENUM_ANY<IS_SAME<R1X ,R2X> ,R3X ,R4X> ;
} ;
} ;

template <class...ARGS>
using IS_ANY_SAME = typename U::IS_ANY_SAME_HELP<typeas<ARGS...>>::RET ;

namespace U {
template <class...>
trait PLACEHOLDER_HELP ;

template <class ARG1>
trait PLACEHOLDER_HELP<ARG1 ,
	REQUIRE<ENUM_EQ_ZERO<ARG1>>> {
	require (ENUM_EQ_ZERO<ARG1>) ;

	class PlaceHolder ;
} ;

template <class ARG1>
class PLACEHOLDER_HELP<ARG1 ,
	REQUIRE<ENUM_EQ_ZERO<ARG1>>>::PlaceHolder {} ;

template <class ARG1>
trait PLACEHOLDER_HELP<ARG1 ,
	REQUIRE<ENUM_GT_ZERO<ARG1>>> {
	require (ENUM_GT_ZERO<ARG1>) ;

	using BASE = typename PLACEHOLDER_HELP<ENUM_DEC<ARG1> ,void>::PlaceHolder ;

	class PlaceHolder ;
} ;

template <class ARG1>
class PLACEHOLDER_HELP<ARG1 ,
	REQUIRE<ENUM_GT_ZERO<ARG1>>>::PlaceHolder :public BASE {} ;
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

template <class UNIT>
using IS_BOOL = IS_SAME<UNIT ,BOOL> ;

template <class UNIT>
using IS_VAR = ENUM_ANY<IS_SAME<UNIT ,VAR32> ,IS_SAME<UNIT ,VAR64>> ;

template <class UNIT>
using IS_FLOAT = ENUM_ANY<IS_SAME<UNIT ,FLOAT32> ,IS_SAME<UNIT ,FLOAT64>> ;

template <class UNIT>
using IS_BYTE = ENUM_ANY<IS_SAME<UNIT ,BYTE> ,IS_SAME<UNIT ,WORD> ,IS_SAME<UNIT ,CHAR> ,IS_SAME<UNIT ,FEAT>> ;

template <class UNIT>
using IS_STR = ENUM_ANY<IS_SAME<UNIT ,STRA> ,IS_SAME<UNIT ,STRW> ,IS_SAME<UNIT ,STRU8> ,IS_SAME<UNIT ,STRU16> ,IS_SAME<UNIT ,STRU32>> ;

template <class UNIT>
using IS_NULL = IS_SAME<UNIT ,typeof (NULL)> ;

template <class UNIT>
using IS_BASIC = ENUM_ANY<IS_BOOL<UNIT> ,IS_VAR<UNIT> ,IS_FLOAT<UNIT> ,IS_BYTE<UNIT> ,IS_STR<UNIT> ,IS_NULL<UNIT>> ;

template <class UNIT>
using IS_FUNCTION = enumof (std::is_function<UNIT>::value) ;

template <class UNIT>
using IS_NOEXCPET = enumof (FALSE) ;

template <class UNIT>
using IS_CLASS = enumof (std::is_class<UNIT>::value) ;

template <class UNIT>
using IS_STRUCT = enumof (std::is_class<UNIT>::value) ;

template <class UNIT>
using IS_TRIVIAL = enumof (std::is_trivial<UNIT>::value) ;

namespace U {
template <class...>
trait IS_CONSTRUCTIBLE_HELP ;

template <class ARG1 ,class...ARGS>
trait IS_CONSTRUCTIBLE_HELP<ARG1 ,typeas<ARGS...>> {
	using RET = enumof (std::is_constructible<ARG1 ,ARGS...>::value) ;
} ;
} ;

template <class UNIT ,class PARAMS>
using IS_CONSTRUCTIBLE = typename U::IS_CONSTRUCTIBLE_HELP<UNIT ,PARAMS>::RET ;

template <class UNIT>
using IS_CLONEABLE = enumof (std::is_copy_constructible<UNIT>::value && std::is_copy_assignable<UNIT>::value) ;

class Interface {
public:
	implicit Interface () = default ;
	implicit virtual ~Interface () noexcept = default ;
	implicit Interface (CREF<Interface>) = delete ;
	inline void operator= (CREF<Interface>) = delete ;
	implicit Interface (RREF<Interface>) = delete ;
	inline void operator= (RREF<Interface>) = delete ;
} ;

template <class UNIT>
using IS_INTERFACE = enumof (std::is_base_of<Interface ,UNIT>::value && std::is_abstract<UNIT>::value) ;

template <class BASE ,class DERIVED>
using IS_EXTEND = enumof (std::is_base_of<BASE ,DERIVED>::value) ;

template <class UNIT>
using IS_PLACEHOLDER = IS_EXTEND<UNIT ,typeof (PH0)> ;

class Exception {} ;

namespace U {
template <class...>
trait BYTE_TRAIT_HELP ;

template <class ARG1 ,class ARG2>
trait BYTE_TRAIT_HELP<ARG1 ,ARG2 ,
	REQUIRE<ENUM_EQUAL<ARG1 ,SIZEOF<BYTE>>> ,
	REQUIRE<ENUM_EQUAL<ARG2 ,ALIGNOF<BYTE>>>> {
	require (ENUM_EQUAL<ARG1 ,SIZEOF<BYTE>>) ;
	require (ENUM_EQUAL<ARG2 ,ALIGNOF<BYTE>>) ;

	using RET = BYTE ;
} ;

template <class ARG1 ,class ARG2>
trait BYTE_TRAIT_HELP<ARG1 ,ARG2 ,
	REQUIRE<ENUM_EQUAL<ARG1 ,SIZEOF<WORD>>> ,
	REQUIRE<ENUM_EQUAL<ARG2 ,ALIGNOF<WORD>>>> {
	require (ENUM_EQUAL<ARG1 ,SIZEOF<WORD>>) ;
	require (ENUM_EQUAL<ARG2 ,ALIGNOF<WORD>>) ;

	using RET = WORD ;
} ;

template <class ARG1 ,class ARG2>
trait BYTE_TRAIT_HELP<ARG1 ,ARG2 ,
	REQUIRE<ENUM_EQUAL<ARG1 ,SIZEOF<CHAR>>> ,
	REQUIRE<ENUM_EQUAL<ARG2 ,ALIGNOF<CHAR>>>> {
	require (ENUM_EQUAL<ARG1 ,SIZEOF<CHAR>>) ;
	require (ENUM_EQUAL<ARG2 ,ALIGNOF<CHAR>>) ;

	using RET = CHAR ;
} ;

template <class ARG1 ,class ARG2>
trait BYTE_TRAIT_HELP<ARG1 ,ARG2 ,
	REQUIRE<ENUM_EQUAL<ARG1 ,SIZEOF<FEAT>>> ,
	REQUIRE<ENUM_EQUAL<ARG2 ,ALIGNOF<FEAT>>>> {
	require (ENUM_EQUAL<ARG1 ,SIZEOF<FEAT>>) ;
	require (ENUM_EQUAL<ARG2 ,ALIGNOF<FEAT>>) ;

	using RET = FEAT ;
} ;
} ;

template <class SIZE ,class ALIGN>
using BYTE_TRAIT = typename U::BYTE_TRAIT_HELP<SIZE ,ALIGN ,void ,void>::RET ;

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

template <class ARG1>
struct PACK_HELP<ARG1>::PACK {
	ARG1 mP1 ;
} ;

template <class ARG1 ,class ARG2>
trait PACK_HELP<ARG1 ,ARG2> {
	struct PACK ;
} ;

template <class ARG1 ,class ARG2>
struct PACK_HELP<ARG1 ,ARG2>::PACK {
	ARG1 mP1 ;
	ARG2 mP2 ;
} ;

template <class ARG1 ,class ARG2 ,class ARG3>
trait PACK_HELP<ARG1 ,ARG2 ,ARG3> {
	struct PACK ;
} ;

template <class ARG1 ,class ARG2 ,class ARG3>
struct PACK_HELP<ARG1 ,ARG2 ,ARG3>::PACK {
	ARG1 mP1 ;
	ARG2 mP2 ;
	ARG3 mP3 ;
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

template <class ARG1>
struct TEMP_HELP<ARG1>::TEMP {
	using ITEM = BYTE_TRAIT<ALIGNOF<ARG1> ,ALIGNOF<ARG1>> ;
	using SIZE = ENUM_DIV<ENUM_DEC<ENUM_ADD<SIZEOF<ARG1> ,SIZEOF<ITEM>>> ,SIZEOF<ITEM>> ;

	DEF<ITEM[SIZE::value]> mUnused ;
} ;
} ;

template <class...UNIT>
using TEMP = typename U::TEMP_HELP<UNIT...>::TEMP ;

namespace U {
struct FUNCTION_NOOP {
	inline void operator() () const {
		return ;
	}
} ;
} ;

static constexpr auto noop = U::FUNCTION_NOOP () ;

namespace U {
#ifdef __CSC_COMPILER_MSVC__
struct FUNCTION_ASSERT {
	inline void operator() (CREF<BOOL> cond) const {
		if (cond)
			return ;
		__debugbreak () ;
		std::terminate () ;
	}
} ;
#endif

#ifndef __CSC_COMPILER_MSVC__
struct FUNCTION_ASSERT {
	inline void operator() (CREF<BOOL> cond) const {
		if (cond)
			return ;
		std::terminate () ;
	}
} ;
#endif
} ;

static constexpr auto builtin_assert = U::FUNCTION_ASSERT () ;

namespace U {
struct FUNCTION_SWAP {
	template <class ARG1 ,class ARG2>
	inline void operator() (DEF<ARG1 &&> obj1 ,DEF<ARG2 &&> obj2) const noexcept {
		using R1X = typeof (obj1) ;
		using R2X = typeof (obj2) ;
		require (IS_SAME<R1X ,R2X>) ;
		using R3X = TEMP<R1X> ;
		require (ENUM_EQUAL<SIZEOF<R3X> ,SIZEOF<R1X>>) ;
		require (ENUM_EQUAL<ALIGNOF<R3X> ,ALIGNOF<R1X>>) ;
		std::swap (reinterpret_cast<VREF<R3X>> (obj1) ,reinterpret_cast<VREF<R3X>> (obj2)) ;
	}
} ;
} ;

static constexpr auto swap = U::FUNCTION_SWAP () ;

namespace U {
struct FUNCTION_FORWARD {
	template <class ARG1>
	inline REMOVE_TYPEID<ARG1> operator() (DEF<ARG1 &&> obj) const {
		return std::move (obj) ;
	}
} ;
} ;

static constexpr auto forward = U::FUNCTION_FORWARD () ;

namespace U {
struct FUNCTION_ADDRESS {
	template <class ARG1>
	inline LENGTH operator() (DEF<ARG1 &&> obj) const {
		return LENGTH (std::addressof (obj)) ;
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
	inline REMOVE_TYPEID<ARG1> operator() (DEF<ARG1 &&> obj) const {
		using R1X = typeof (obj) ;
		if (obj < R1X (ZERO))
			return -obj ;
		return +obj ;
	}
} ;
} ;

static constexpr auto abs = U::FUNCTION_ABS () ;

namespace U {
struct FUNCTION_MIN {
	template <class ARG1>
	inline REMOVE_TYPEID<ARG1> operator() (DEF<ARG1 &&> obj1 ,DEF<ARG1 &&> obj2) const {
		if (obj1 < obj2)
			return obj1 ;
		return obj2 ;
	}
} ;
} ;

static constexpr auto min = U::FUNCTION_MIN () ;

namespace U {
struct FUNCTION_MAX {
	template <class ARG1>
	inline REMOVE_TYPEID<ARG1> operator() (DEF<ARG1 &&> obj1 ,DEF<ARG1 &&> obj2) const {
		if (obj1 < obj2)
			return obj2 ;
		return obj1 ;
	}
} ;
} ;

static constexpr auto max = U::FUNCTION_MAX () ;

namespace U {
struct FUNCTION_HASHCODE {
	inline FLAG operator() () const {
		const auto r2x = VAR64 (-3750763034362895579) ;
		const auto r3x = VAR64 (FEAT (r2x) & FEAT (VAR64_MAX)) ;
		return FLAG (r3x) ;
	}

	inline FLAG operator() (CREF<FLAG> obj1 ,CREF<FLAG> obj2) const {
		const auto r1x = VAR64 (FEAT (obj1) ^ FEAT (obj2)) ;
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

template <class ARG1>
class TYPEMID_HELP<ARG1>::TYPEMID :Interface {} ;

struct FUNCTION_TYPE_MID {
	template <class ARG1>
	inline FLAG operator() (DEF<ARG1 &&> id) const {
		using R1X = typeof (id) ;
		using R2X = TYPEMID_HELP<R1X> ;
		const auto r1x = R2X () ;
		require (ENUM_EQUAL<SIZEOF<FLAG> ,SIZEOF<R2X>>) ;
		require (ENUM_EQUAL<ALIGNOF<FLAG> ,ALIGNOF<R2X>>) ;
		return FLAG (reinterpret_cast<CREF<FLAG>> (r1x)) ;
	}
} ;
} ;

static constexpr auto type_mid = U::FUNCTION_TYPE_MID () ;

namespace U {
template <class...>
trait BOX_HELP ;

template <class ARG1>
trait BOX_HELP<ARG1 ,
	REQUIRE<IS_INTERFACE<ARG1>>> {
	require (IS_INTERFACE<ARG1>) ;

	using UNIT = ARG1 ;

	class Box ;
} ;

template <class ARG1>
class BOX_HELP<ARG1 ,
	REQUIRE<IS_INTERFACE<ARG1>>>::Box {
private:
	DEF<UNIT *> mPointer ;

public:
	implicit Box () noexcept :Box (NULL) {}

	implicit Box (CREF<typeof (NULL)>) noexcept :mPointer (NULL) {}

	template <class ARG1 ,class = REQUIRE<IS_EXTEND<UNIT ,REMOVE_TYPEID<ARG1>>>>
	implicit Box (DEF<ARG1 &&> that) : Box (NULL) {
		using R1X = typeof (that) ;
		require (IS_EXTEND<UNIT ,R1X>) ;
		mPointer = new R1X (std::forward<ARG1> (that)) ;
	}

	implicit ~Box () noexcept {
		if (mPointer == NULL)
			return ;
		delete mPointer ;
		mPointer = NULL ;
	}

	implicit Box (CREF<Box>) = delete ;

	inline void operator= (CREF<Box>) = delete ;

	implicit Box (RREF<Box> that) noexcept :Box (NULL) {
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

	inline BOOL operator== (CREF<typeof (NULL)>) {
		return !exist () ;
	}

	inline BOOL operator!= (CREF<typeof (NULL)>) {
		return exist () ;
	}

	VREF<UNIT> to () {
		assert (exist ()) ;
		return (*mPointer) ;
	}

	inline implicit operator VREF<UNIT> () leftvalue {
		return self ;
	}

	inline DEF<UNIT *> operator-> () {
		return (&self) ;
	}

	CREF<UNIT> to () const {
		assert (exist ()) ;
		return (*mPointer) ;
	}

	inline implicit operator CREF<UNIT> () const leftvalue {
		return self ;
	}

	inline DEF<const UNIT *> operator-> () const {
		return (&self) ;
	}
} ;
} ;

template <class UNIT>
using Box = typename U::BOX_HELP<UNIT ,void>::Box ;

namespace U {
template <class...>
trait CELL_HELP ;

template <class ARG1>
trait CELL_HELP<ARG1 ,
	REQUIRE<IS_CLONEABLE<ARG1>>> {
	require (IS_CLONEABLE<ARG1>) ;

	using UNIT = ARG1 ;

	class Cell ;
} ;

template <class ARG1>
class CELL_HELP<ARG1 ,
	REQUIRE<IS_CLONEABLE<ARG1>>>::Cell {
private:
	mutable TEMP<UNIT> mValue ;
	BOOL mExist ;

public:
	implicit Cell () noexcept :Cell (NULL) {}

	implicit Cell (CREF<typeof (NULL)>) noexcept :mExist (FALSE) {}

	implicit Cell (RREF<UNIT> that) : Cell (NULL) {
		new (&m_fake ()) UNIT (forward (that)) ;
		mExist = TRUE ;
	}

	implicit ~Cell () noexcept {
		if (!mExist)
			return ;
		m_fake ().~UNIT () ;
		mExist = FALSE ;
	}

	implicit Cell (CREF<Cell> that) :Cell (NULL) {
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

	implicit Cell (RREF<Cell> that) noexcept :Cell (NULL) {
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

	inline BOOL operator== (CREF<typeof (NULL)>) {
		return !exist () ;
	}

	inline BOOL operator!= (CREF<typeof (NULL)>) {
		return exist () ;
	}

	UNIT fetch () const {
		assert (exist ()) ;
		return m_fake () ;
	}

	void store (RREF<UNIT> obj) const {
		assert (exist ()) ;
		m_fake () = forward (obj) ;
	}

	UNIT exchange (RREF<UNIT> obj) const {
		assert (exist ()) ;
		auto ret = forward (m_fake ()) ;
		m_fake () = forward (obj) ;
		return forward (ret) ;
	}

	BOOL change (VREF<UNIT> expect ,RREF<UNIT> obj) const {
		assert (exist ()) ;
		if (m_fake () != expect) {
			expect = m_fake () ;
			return FALSE ;
		}
		m_fake () = forward (obj) ;
		return TRUE ;
	}

private:
	VREF<UNIT> m_fake () const {
		return reinterpret_cast<VREF<UNIT>> (mValue) ;
	}
} ;
} ;

template <class UNIT>
using Cell = typename U::CELL_HELP<UNIT ,void>::Cell ;

namespace U {
template <class...>
trait RC_HELP ;

template <class ARG1>
trait RC_HELP<ARG1> {
	using UNIT = ARG1 ;

	struct NODE ;

	class RC ;
} ;

template <class ARG1>
struct RC_HELP<ARG1>::NODE {
	ARG1 mValue ;
	LENGTH mCounter ;
} ;

template <class ARG1>
class RC_HELP<ARG1>::RC {
private:
	DEF<NODE *> mPointer ;

public:
	implicit RC () noexcept :RC (NULL) {}

	implicit RC (CREF<typeof (NULL)>) noexcept : RC (NULL) {}

	implicit RC (RREF<UNIT> that) : RC (NULL) {
		auto &thix = (*this) ;
		const auto r1x = new NODE {forward (that) ,ZERO} ;
		thix = RC (r1x) ;
	}

	implicit ~RC () noexcept {
		if (mPointer == NULL)
			return ;
		if switch_once (TRUE) {
			const auto r1x = --mPointer->mCounter ;
			if (r1x > 0)
				discard ;
			delete mPointer ;
		}
		mPointer = NULL ;
	}

	implicit RC (CREF<RC> that) :RC (NULL) {
		auto &thix = (*this) ;
		if (!that.exist ())
			return ;
		if (that.mPointer->mCounter <= 0)
			throw Exception () ;
		thix = RC (that.mPointer) ;
	}

	inline void operator= (CREF<RC> that) {
		auto &thix = (*this) ;
		if ((&thix) == (&that))
			return ;
		thix.~RC () ;
		new (&thix) RC (forward (that)) ;
	}

	implicit RC (RREF<RC> that) noexcept :RC (NULL) {
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

	inline BOOL operator== (CREF<typeof (NULL)>) {
		return !exist () ;
	}

	inline BOOL operator!= (CREF<typeof (NULL)>) {
		return exist () ;
	}

	CREF<UNIT> to () const {
		assert (exist ()) ;
		return mPointer->mValue ;
	}

	inline implicit operator CREF<UNIT> () const leftvalue {
		return self ;
	}

	inline DEF<const UNIT *> operator-> () const {
		return (&self) ;
	}

private:
	explicit RC (DEF<NODE *> pointer) noexcept :RC (NULL) {
		assert (pointer != NULL) ;
		mPointer = pointer ;
		++mPointer->mCounter ;
	}
} ;
} ;

namespace U {
template <class...>
trait AUTO_HELP ;

template <>
trait AUTO_HELP<> {
	class AUTO ;

	struct EXTERN {
		interface Holder ;
	} ;
} ;

interface AUTO_HELP<>::EXTERN::Holder :Interface {
	virtual FLAG type_mid () const = 0 ;
} ;

template <class...>
trait IMPLHOLDER_HELP ;

template <class ARG1>
trait IMPLHOLDER_HELP<ARG1> {
	using UNIT = ARG1 ;

	using Holder = typename AUTO_HELP<>::EXTERN::Holder ;

	class ImplHolder ;
} ;

class AUTO_HELP<>::AUTO {
private:
	using Holder = typename AUTO_HELP<>::EXTERN::Holder ;

private:
	Box<Holder> mPointer ;

public:
	implicit AUTO () = delete ;

	template <class ARG1 ,class = ENABLE<ENUM_NOT<IS_SAME<AUTO ,REMOVE_TYPEID<ARG1>>>>>
	implicit AUTO (DEF<ARG1 &&> that) {
		struct Depentent ;
		using R1X = typeof (that) ;
		using R2X = typename IMPLHOLDER_HELP<R1X>::ImplHolder ;
		mPointer = Box<Holder> (std::forward<ARG1> (that)) ;
	}

	implicit AUTO (CREF<AUTO>) = delete ;

	inline void operator= (CREF<AUTO>) = delete ;

	implicit AUTO (RREF<AUTO> that) noexcept {
		auto &thix = (*this) ;
		swap (thix ,that) ;
	}

	inline void operator= (RREF<AUTO> that) noexcept {
		auto &thix = (*this) ;
		if ((&thix) == (&that))
			return ;
		thix.~AUTO () ;
		new (&thix) AUTO (forward (that)) ;
	}

	template <class ARG1>
	ARG1 poll (DEF<ARG1 &&> id) {
		struct Depentent ;
		using R1X = typeof (ARG1 ()) ;
		using R2X = typename IMPLHOLDER_HELP<R1X>::ImplHolder ;
		assert (mPointer != NULL) ;
		const auto r1x = type_mid (typeas<R1X>::id) ;
		const auto r2x = mPointer->type_mid () ;
		assert (r1x == r2x) ;
		return m_derived (typeas<R2X>::id).poll () ;
	}

	template <class ARG1>
	inline implicit operator ARG1 () rightvalue {
		return poll (typeas<ARG1>::id) ;
	}

private:
	template <class ARG1>
	VREF<REMOVE_TYPEID<ARG1>> m_derived (DEF<ARG1 &&> id) {
		using R1X = typeof (id) ;
		return static_cast<VREF<R1X>> (mPointer.self) ;
	}
} ;

template <class ARG1>
class IMPLHOLDER_HELP<ARG1>::ImplHolder :public Holder {
private:
	UNIT mValue ;

public:
	implicit ImplHolder () = delete ;

	explicit ImplHolder (RREF<UNIT> that) :mValue (forward (that)) {}

	FLAG type_mid () const override {
		return type_mid (typeas<UNIT>::id) ;
	}

	UNIT poll () {
		return forward (mValue) ;
	}
} ;
} ;

using AUTO = typename U::AUTO_HELP<>::AUTO ;

namespace U {
struct FUNCTION_BAD {
	template <class ARG1>
	inline REMOVE_TYPEID<ARG1> operator() (DEF<ARG1 &&> id) const {
		using R1X = typeof (id) ;
		assert (FALSE) ;
		const auto r1x = [&] ()->AUTO { return ZERO ; } ;
		return R1X (r1x ()) ;
	}
} ;
} ;

static constexpr auto bad = U::FUNCTION_BAD () ;

namespace U {
template <class...>
trait TUPLE_HELP ;

template <class ARG1>
trait TUPLE_HELP<ARG1 ,
	REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;

	using UNIT = ARG1 ;

	class Tuple ;
} ;

template <class ARG1>
class TUPLE_HELP<ARG1 ,
	REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>>::Tuple {
public:
	implicit Tuple () = default ;

	LENGTH capacity () const {
		return COUNTOF<UNIT>::value ;
	}

	BOOL equal (const Tuple &that) const {
		return TRUE ;
	}

	inline BOOL operator== (const Tuple &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const Tuple &that) const {
		return !equal (that) ;
	}

	FLAG compr (const Tuple &that) const {
		return ZERO ;
	}

	inline BOOL operator< (const Tuple &that) const {
		return compr (that) < ZERO ;
	}

	inline BOOL operator<= (const Tuple &that) const {
		return compr (that) <= ZERO ;
	}

	inline BOOL operator> (const Tuple &that) const {
		return compr (that) > ZERO ;
	}

	inline BOOL operator>= (const Tuple &that) const {
		return compr (that) >= ZERO ;
	}

	FLAG hash () const {
		return hashcode () ;
	}
} ;

template <class ARG1>
trait TUPLE_HELP<ARG1 ,
	REQUIRE<ENUM_GT_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_GT_ZERO<COUNTOF<ARG1>>) ;

	using UNIT = ARG1 ;
	using FIRST_ONE = TYPE_FIRST_ONE<ARG1> ;
	using FIRST_REST = TYPE_FIRST_REST<ARG1> ;
	using BASE = typename TUPLE_HELP<FIRST_REST ,void>::Tuple ;

	class Tuple ;
} ;

template <class ARG1>
class TUPLE_HELP<ARG1 ,
	REQUIRE<ENUM_GT_ZERO<COUNTOF<ARG1>>>>::Tuple :public BASE {
private:
	FIRST_ONE mValue ;

public:
	implicit Tuple () = default ;

	template <class ARG1 ,class...ARGS>
	explicit Tuple (DEF<ARG1 &&> one_ ,DEF<ARGS &&>...rest_) :mValue (std::forward<ARG1> (one_)) ,BASE (std::forward<ARGS> (rest_)...) {}

	LENGTH capacity () const {
		return COUNTOF<UNIT>::value ;
	}

	VREF<FIRST_ONE> one () {
		return mValue ;
	}

	CREF<FIRST_ONE> one () const {
		return mValue ;
	}

	VREF<BASE> rest () {
		return m_super () ;
	}

	CREF<BASE> rest () const {
		return m_super () ;
	}

	template <class ARG1>
	VREF<TYPE_PICK<UNIT ,REMOVE_TYPEID<ARG1>>> pick (DEF<ARG1 &&> nth) {
		using R1X = typeof (nth) ;
		return template_pick (typeas<R1X>::id ,PHX) ;
	}

	template <class ARG1>
	CREF<TYPE_PICK<UNIT ,REMOVE_TYPEID<ARG1>>> pick (DEF<ARG1 &&> nth) const {
		using R1X = typeof (nth) ;
		return template_pick (typeas<R1X>::id ,PHX) ;
	}

	BOOL equal (const Tuple &that) const {
		if (mValue != that.mValue)
			return FALSE ;
		if (m_super () != that.m_super ())
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const Tuple &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const Tuple &that) const {
		return !equal (that) ;
	}

	FLAG compr (const Tuple &that) const {
		const auto r1x = op_compr (mValue ,that.mValue) ;
		if (r1x != ZERO)
			return r1x ;
		const auto r2x = op_compr (m_super () ,that.m_super ()) ;
		if (r2x != ZERO)
			return r2x ;
		return ZERO ;
	}

	inline BOOL operator< (const Tuple &that) const {
		return compr (that) < ZERO ;
	}

	inline BOOL operator<= (const Tuple &that) const {
		return compr (that) <= ZERO ;
	}

	inline BOOL operator> (const Tuple &that) const {
		return compr (that) > ZERO ;
	}

	inline BOOL operator>= (const Tuple &that) const {
		return compr (that) >= ZERO ;
	}

	FLAG hash () const {
		const auto r1x = op_hash (mValue) ;
		const auto r2x = op_hash (m_super ()) ;
		return hashcode (r1x ,r2x) ;
	}

private:
	VREF<BASE> m_super () {
		return static_cast<VREF<BASE>> (*this) ;
	}

	CREF<BASE> m_super () const {
		return static_cast<CREF<BASE>> (*this) ;
	}

	template <class ARG1 ,class = REQUIRE<ENUM_EQ_ZERO<REMOVE_TYPEID<ARG1>>>>
	VREF<FIRST_ONE> template_pick (DEF<ARG1 &&> nth ,CREF<typeof (PH1)>) {
		return one () ;
	}

	template <class ARG1 ,class = REQUIRE<ENUM_EQ_ZERO<REMOVE_TYPEID<ARG1>>>>
	CREF<FIRST_ONE> template_pick (DEF<ARG1 &&> nth ,CREF<typeof (PH1)>) const {
		return one () ;
	}

	template <class ARG1 ,class = REQUIRE<ENUM_GT_ZERO<REMOVE_TYPEID<ARG1>>>>
	VREF<TYPE_PICK<UNIT ,REMOVE_TYPEID<ARG1>>> template_pick (DEF<ARG1 &&> nth ,CREF<typeof (PH2)>) {
		using R1X = typeof (nth) ;
		using R2X = ENUM_DEC<REMOVE_TYPEID<R1X>> ;
		return rest ().template_pick (typeas<R2X>::id ,PHX) ;
	}

	template <class ARG1 ,class = REQUIRE<ENUM_GT_ZERO<REMOVE_TYPEID<ARG1>>>>
	CREF<TYPE_PICK<UNIT ,REMOVE_TYPEID<ARG1>>> template_pick (DEF<ARG1 &&> nth ,CREF<typeof (PH2)>) const {
		using R1X = typeof (nth) ;
		using R2X = ENUM_DEC<REMOVE_TYPEID<R1X>> ;
		return rest ().template_pick (typeas<R2X>::id ,PHX) ;
	}
} ;
} ;

template <class...UNITS>
using Tuple = typename U::TUPLE_HELP<typeas<UNITS...> ,void>::Tuple ;

namespace U {
template <class...>
trait VARIANT_HELP ;

template <class ARG1>
trait VARIANT_HELP<ARG1 ,
	REQUIRE<ENUM_EQ_IDEN<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_IDEN<COUNTOF<ARG1>>) ;

	using UNIT = TYPE_UNWRAP<ARG1> ;

	struct EXTERN {
		interface Holder ;
	} ;

	class Variant ;
} ;

template <class ARG1>
interface VARIANT_HELP<ARG1 ,
	REQUIRE<ENUM_EQ_IDEN<COUNTOF<ARG1>>>>::EXTERN::Holder {
	virtual void test () = 0 ;
} ;

template <class...>
trait IMPLHOLDER_HELP ;

template <class ARG1 ,class ARG2>
trait IMPLHOLDER_HELP<ARG1 ,ARG2> {
	using UNIT = ARG2 ;

	using Holder = typename VARIANT_HELP<ARG1 ,REQUIRE<ENUM_EQ_IDEN<COUNTOF<ARG1>>>>::EXTERN::Holder ;

	class ImplHolder ;
} ;

template <class ARG1>
class VARIANT_HELP<ARG1 ,
	REQUIRE<ENUM_EQ_IDEN<COUNTOF<ARG1>>>>::Variant {
private:
	using Holder = typename VARIANT_HELP<ARG1 ,REQUIRE<ENUM_EQ_IDEN<COUNTOF<ARG1>>>>::EXTERN::Holder ;

private:

} ;

template <class ARG1 ,class ARG2>
class IMPLHOLDER_HELP<ARG1 ,ARG2>::ImplHolder :public Holder {
public:
	void test () override {

	}
} ;

template <class ARG1>
trait VARIANT_HELP<ARG1 ,
	REQUIRE<ENUM_GT_IDEN<COUNTOF<ARG1>>>> {

	class Variant ;
} ;

template <class ARG1>
class VARIANT_HELP<ARG1 ,
	REQUIRE<ENUM_GT_IDEN<COUNTOF<ARG1>>>>::Variant {
private:
	using Holder = typename VARIANT_HELP<ARG1 ,REQUIRE<ENUM_GT_IDEN<COUNTOF<ARG1>>>>::EXTERN::Holder ;

private:

} ;
} ;

template <class UNIT>
using Optional = typename U::VARIANT_HELP<typeas<UNIT> ,void>::Variant ;

template <class...UNITS>
using Variant = typename U::VARIANT_HELP<typeas<UNITS...> ,void>::Variant ;

} ;