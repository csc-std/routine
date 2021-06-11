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

static constexpr auto VAR32_MAX = VAR32 (+2147483647) ;
static constexpr auto VAR32_MIN = VAR32 (-2147483647) ;
static constexpr auto VAR64_MAX = VAR64 (+9223372036854775807) ;
static constexpr auto VAR64_MIN = VAR64 (-9223372036854775807) ;

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

using SINGLE = float ;
using DOUBLE = double ;

static constexpr auto SINGLE_MAX = SINGLE (+3.402823466E+38) ;
static constexpr auto SINGLE_MIN = SINGLE (-3.402823466E+38) ;
static constexpr auto SINGLE_LOW = SINGLE (1.175494351E-38) ;
static constexpr auto SINGLE_EPS = SINGLE (1.192092896E-07) ;
static constexpr auto SINGLE_INF = SINGLE (std::numeric_limits<float>::infinity ()) ;
static constexpr auto DOUBLE_MAX = DOUBLE (+1.7976931348623158E+308) ;
static constexpr auto DOUBLE_MIN = DOUBLE (-1.7976931348623158E+308) ;
static constexpr auto DOUBLE_LOW = DOUBLE (2.2250738585072014E-308) ;
static constexpr auto DOUBLE_EPS = DOUBLE (2.2204460492503131E-016) ;
static constexpr auto DOUBLE_INF = DOUBLE (std::numeric_limits<float>::infinity ()) ;

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
} ;

using STR = typename U::STR_HELP<>::STR ;

static constexpr auto NULL = nullptr ;

namespace U {
template <class...>
struct ENUMAS ;

template <VAR UNIT1>
struct ENUMID {
	imports constexpr VAR compile () {
		return UNIT1 ;
	}
} ;

template <class UNIT1>
struct ENUMAS<UNIT1> {
	static constexpr auto value = UNIT1::compile () ;
} ;
} ;

template <class...ARGS>
using ENUMAS = U::ENUMAS<ARGS...> ;

namespace U {
template <class...>
struct TYPEAS ;

template <class>
struct TYPEID {} ;

template <class UNIT1>
struct TYPEAS<UNIT1> {
	static constexpr auto id = TYPEID<UNIT1> () ;
} ;
} ;

template <class...ARGS>
using TYPEAS = U::TYPEAS<ARGS...> ;

template <class UNIT1>
using REMOVE_CVR = typename std::remove_cv<typename std::remove_reference<UNIT1>::type>::type ;

namespace U {
template <class...>
trait REMOVE_TYPEID_HELP ;

template <>
trait REMOVE_TYPEID_HELP<void> ;

template <class ARG1>
trait REMOVE_TYPEID_HELP<ARG1> {
	using RET = ARG1 ;
} ;

template <class ARG1>
trait REMOVE_TYPEID_HELP<TYPEID<ARG1>> {
	using RET = ARG1 ;
} ;
} ;

template <class UNIT1>
using REMOVE_TYPEID = typename U::REMOVE_TYPEID_HELP<UNIT1>::RET ;

template <class UNIT1>
using REMOVE_ALL = REMOVE_CVR<REMOVE_TYPEID<REMOVE_CVR<UNIT1>>> ;

template <class UNIT1>
using DEF = UNIT1 ;

template <class UNIT1>
using UNSAFE_PTR = DEF<typename std::remove_reference<UNIT1>::type> * ;

template <class UNIT1>
using VREF = DEF<UNIT1 &> ;

template <class UNIT1>
using CREF = DEF<const UNIT1 &> ;

template <class UNIT1>
using RREF = DEF<UNIT1 &&> ;

using ENUM_USED = enumof (USED) ;
using ENUM_NONE = enumof (NONE) ;
using ENUM_ZERO = enumof (ZERO) ;
using ENUM_IDEN = enumof (IDEN) ;

namespace U {
template <class...>
trait SIZEOF_HELP ;

template <class ARG1>
trait SIZEOF_HELP<ARG1> {
	struct ID1 {
		imports constexpr VAR compile () {
			return sizeof (ARG1) ;
		}
	} ;

	using RET = ENUMAS<ID1> ;
} ;
} ;

template <class UNIT1>
using SIZEOF = typename U::SIZEOF_HELP<UNIT1>::RET ;

namespace U {
template <class...>
trait ALIGNOF_HELP ;

template <class ARG1>
trait ALIGNOF_HELP<ARG1> {
	struct ID1 {
		imports constexpr VAR compile () {
			return alignof (ARG1) ;
		}
	} ;

	using RET = ENUMAS<ID1> ;
} ;
} ;

template <class UNIT1>
using ALIGNOF = typename U::ALIGNOF_HELP<UNIT1>::RET ;

namespace U {
template <class...>
trait COUNTOF_HELP ;

template <class...ARGS>
trait COUNTOF_HELP<TYPEAS<ARGS...>> {
	struct ID1 {
		imports constexpr VAR compile () {
			return sizeof... (ARGS) ;
		}
	} ;

	using RET = ENUMAS<ID1> ;
} ;
} ;

template <class UNIT1>
using COUNTOF = typename U::COUNTOF_HELP<UNIT1>::RET ;

namespace U {
template <class...>
trait IS_SAME_HELP ;

template <class ARG1>
trait IS_SAME_HELP<ARG1 ,ARG1> {
	using RET = ENUM_IDEN ;
} ;

template <class ARG1 ,class ARG2>
trait IS_SAME_HELP<ARG1 ,ARG2> {
	using RET = ENUM_ZERO ;
} ;
} ;

template <class UNIT1 ,class UNIT2>
using IS_SAME = typename U::IS_SAME_HELP<UNIT1 ,UNIT2>::RET ;

namespace U {
template <class...>
trait REQUIRE_HELP ;

template <>
trait REQUIRE_HELP<ENUM_IDEN> {
	using RET = void ;
} ;
} ;

template <class UNIT1>
using REQUIRE = typename U::REQUIRE_HELP<enumof (UNIT1::value)>::RET ;

namespace U {
template <class...>
trait ENABLE_HELP ;

template <class ARG1 ,class ARG2>
trait ENABLE_HELP<ARG1 ,ARG2 ,REQUIRE<ARG1>> {
	using RET = ARG2 ;
} ;
} ;

template <class COND ,class YES = TYPEAS<>>
using ENABLE = typename U::ENABLE_HELP<COND ,YES ,void>::RET ;

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

namespace U {
template <class...>
trait ENUM_NOT_HELP ;

template <class ARG1>
trait ENUM_NOT_HELP<ARG1> {
	struct ID1 {
		imports constexpr VAR compile () {
			return ifnot (ENUM_CHECK<ARG1>::value) ;
		}
	} ;

	using RET = ENUMAS<ID1> ;
} ;
} ;

template <class UNIT1>
using ENUM_NOT = typename U::ENUM_NOT_HELP<UNIT1>::RET ;

namespace U {
template <class...>
trait CONDITIONAL_HELP ;

template <class ARG1 ,class ARG2 ,class ARG3>
trait CONDITIONAL_HELP<ARG1 ,ARG2 ,ARG3 ,REQUIRE<ARG1>> {
	using RET = ARG2 ;
} ;

template <class ARG1 ,class ARG2 ,class ARG3>
trait CONDITIONAL_HELP<ARG1 ,ARG2 ,ARG3 ,REQUIRE<ENUM_NOT<ARG1>>> {
	using RET = ARG3 ;
} ;
} ;

template <class COND ,class YES ,class NO>
using CONDITIONAL = typename U::CONDITIONAL_HELP<COND ,YES ,NO ,void>::RET ;

namespace U {
template <class...>
trait ENUM_EQUAL_HELP ;

template <class ARG1 ,class ARG2>
trait ENUM_EQUAL_HELP<ARG1 ,ARG2> {
	struct ID1 {
		imports constexpr VAR compile () {
			return ENUM_CHECK<ARG1>::value == ENUM_CHECK<ARG2>::value ;
		}
	} ;

	using RET = ENUMAS<ID1> ;
} ;
} ;

template <class UNIT1 ,class UNIT2>
using ENUM_EQUAL = typename U::ENUM_EQUAL_HELP<UNIT1 ,UNIT2>::RET ;

template <class UNIT1 ,class UNIT2>
using ENUM_NOT_EQUAL = ENUM_NOT<ENUM_EQUAL<UNIT1 ,UNIT2>> ;

namespace U {
template <class...>
trait ENUM_COMPR_HELP ;

template <class ARG1 ,class ARG2>
trait ENUM_COMPR_HELP<ARG1 ,ARG2> {
	struct ID1 {
		imports constexpr VAR compile () {
			if constexpr (ENUM_CHECK<ARG1>::value < ENUM_CHECK<ARG2>::value)
				return NONE ;
			if constexpr (ENUM_CHECK<ARG1>::value > ENUM_CHECK<ARG2>::value)
				return IDEN ;
			return ZERO ;
		}
	} ;

	using RET = ENUMAS<ID1> ;
} ;
} ;

template <class UNIT1 ,class UNIT2>
using ENUM_COMPR = typename U::ENUM_COMPR_HELP<UNIT1 ,UNIT2>::RET ;

template <class UNIT1 ,class UNIT2>
using ENUM_COMPR_LT = ENUM_EQUAL<ENUM_COMPR<UNIT1 ,UNIT2> ,ENUM_NONE> ;

template <class UNIT1 ,class UNIT2>
using ENUM_COMPR_GTEQ = ENUM_NOT<ENUM_COMPR_LT<UNIT1 ,UNIT2>> ;

template <class UNIT1 ,class UNIT2>
using ENUM_COMPR_GT = ENUM_EQUAL<ENUM_COMPR<UNIT1 ,UNIT2> ,ENUM_IDEN> ;

template <class UNIT1 ,class UNIT2>
using ENUM_COMPR_LTEQ = ENUM_NOT<ENUM_COMPR_GT<UNIT1 ,UNIT2>> ;

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

namespace U {
template <class...>
trait ENUM_ADD_HELP ;

template <class ARG1 ,class ARG2>
trait ENUM_ADD_HELP<ARG1 ,ARG2> {
	struct ID1 {
		imports constexpr VAR compile () {
			return ENUM_CHECK<ARG1>::value + ENUM_CHECK<ARG2>::value ;
		}
	} ;

	using RET = ENUMAS<ID1> ;
} ;
} ;

template <class UNIT1 ,class UNIT2>
using ENUM_ADD = typename U::ENUM_ADD_HELP<UNIT1 ,UNIT2>::RET ;

namespace U {
template <class...>
trait ENUM_SUB_HELP ;

template <class ARG1 ,class ARG2>
trait ENUM_SUB_HELP<ARG1 ,ARG2> {
	struct ID1 {
		imports constexpr VAR compile () {
			return ENUM_CHECK<ARG1>::value - ENUM_CHECK<ARG2>::value ;
		}
	} ;

	using RET = ENUMAS<ID1> ;
} ;
} ;

template <class UNIT1 ,class UNIT2>
using ENUM_SUB = typename U::ENUM_SUB_HELP<UNIT1 ,UNIT2>::RET ;

namespace U {
template <class...>
trait ENUM_MUL_HELP ;

template <class ARG1 ,class ARG2>
trait ENUM_MUL_HELP<ARG1 ,ARG2> {
	struct ID1 {
		imports constexpr VAR compile () {
			return ENUM_CHECK<ARG1>::value * ENUM_CHECK<ARG2>::value ;
		}
	} ;

	using RET = ENUMAS<ID1> ;
} ;
} ;

template <class UNIT1 ,class UNIT2>
using ENUM_MUL = typename U::ENUM_MUL_HELP<UNIT1 ,UNIT2>::RET ;

namespace U {
template <class...>
trait ENUM_DIV_HELP ;

template <class ARG1 ,class ARG2>
trait ENUM_DIV_HELP<ARG1 ,ARG2> {
	struct ID1 {
		imports constexpr VAR compile () {
			return ENUM_CHECK<ARG1>::value / ENUM_CHECK<ARG2>::value ;
		}
	} ;

	using RET = ENUMAS<ID1> ;
} ;
} ;

template <class UNIT1 ,class UNIT2>
using ENUM_DIV = typename U::ENUM_DIV_HELP<UNIT1 ,UNIT2>::RET ;

namespace U {
template <class...>
trait ENUM_MOD_HELP ;

template <class ARG1 ,class ARG2>
trait ENUM_MOD_HELP<ARG1 ,ARG2> {
	struct ID1 {
		imports constexpr VAR compile () {
			return ENUM_CHECK<ARG1>::value % ENUM_CHECK<ARG2>::value ;
		}
	} ;

	using RET = ENUMAS<ID1> ;
} ;
} ;

template <class UNIT1 ,class UNIT2>
using ENUM_MOD = typename U::ENUM_MOD_HELP<UNIT1 ,UNIT2>::RET ;

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
trait TYPE_FIRST_ONE_HELP<TYPEAS<ARG1 ,ARGS...>> {
	using RET = ARG1 ;
} ;
} ;

template <class UNIT1>
using TYPE_FIRST_ONE = typename U::TYPE_FIRST_ONE_HELP<UNIT1>::RET ;

namespace U {
template <class...>
trait TYPE_FIRST_REST_HELP ;

template <class ARG1 ,class...ARGS>
trait TYPE_FIRST_REST_HELP<TYPEAS<ARG1 ,ARGS...>> {
	using RET = TYPEAS<ARGS...> ;
} ;
} ;

template <class UNIT1>
using TYPE_FIRST_REST = typename U::TYPE_FIRST_REST_HELP<UNIT1>::RET ;

namespace U {
template <class...>
trait TYPE_SECOND_ONE_HELP ;

template <class ARG1 ,class ARG2 ,class...ARGS>
trait TYPE_SECOND_ONE_HELP<TYPEAS<ARG1 ,ARG2 ,ARGS...>> {
	using RET = ARG2 ;
} ;
} ;

template <class UNIT1>
using TYPE_SECOND_ONE = typename U::TYPE_SECOND_ONE_HELP<UNIT1>::RET ;

namespace U {
template <class...>
trait TYPE_SECOND_REST_HELP ;

template <class ARG1 ,class ARG2 ,class...ARGS>
trait TYPE_SECOND_REST_HELP<TYPEAS<ARG1 ,ARG2 ,ARGS...>> {
	using RET = TYPEAS<ARGS...> ;
} ;
} ;

template <class UNIT1>
using TYPE_SECOND_REST = typename U::TYPE_SECOND_REST_HELP<UNIT1>::RET ;

namespace U {
template <class...>
trait TYPE_UNWRAP_HELP ;

template <class ARG1>
trait TYPE_UNWRAP_HELP<ARG1 ,REQUIRE<ENUM_EQ_IDEN<COUNTOF<ARG1>>>> {
	using RET = TYPE_FIRST_ONE<ARG1> ;
} ;
} ;

template <class UNIT1>
using TYPE_UNWRAP = typename U::TYPE_UNWRAP_HELP<UNIT1 ,void>::RET ;

namespace U {
template <class...>
trait TYPE_CAT_HELP ;

template <class...ARGS1 ,class...ARGS2>
trait TYPE_CAT_HELP<TYPEAS<ARGS1...> ,TYPEAS<ARGS2...>> {
	using RET = TYPEAS<ARGS1... ,ARGS2...> ;
} ;
} ;

template <class UNIT1 ,class UNIT2>
using TYPE_CAT = typename U::TYPE_CAT_HELP<UNIT1 ,UNIT2>::RET ;

namespace U {
template <class...>
trait TYPE_REPEAT_HELP ;

template <class ARG1 ,class ARG2>
trait TYPE_REPEAT_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_EQ_ZERO<ARG2>>> {
	using RET = TYPEAS<> ;
} ;

template <class ARG1 ,class ARG2>
trait TYPE_REPEAT_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_GT_ZERO<ARG2>>> {
	using R1X = typename TYPE_REPEAT_HELP<ARG1 ,ENUM_DEC<ARG2> ,void>::RET ;

	using RET = TYPE_CAT<TYPEAS<ARG1> ,R1X> ;
} ;
} ;

template <class ITEM ,class SIZE>
using TYPE_REPEAT = typename U::TYPE_REPEAT_HELP<ITEM ,SIZE ,void>::RET ;

namespace U {
template <class...>
trait TYPE_REVERSE_HELP ;

template <class ARG1>
trait TYPE_REVERSE_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>> {
	using RET = TYPEAS<> ;
} ;

template <class ARG1>
trait TYPE_REVERSE_HELP<ARG1 ,REQUIRE<ENUM_GT_ZERO<COUNTOF<ARG1>>>> {
	using R1X = TYPE_FIRST_ONE<ARG1> ;
	using R2X = typename TYPE_REVERSE_HELP<TYPE_FIRST_REST<ARG1> ,void>::RET ;

	using RET = TYPE_CAT<R2X ,TYPEAS<R1X>> ;
} ;
} ;

template <class LIST>
using TYPE_REVERSE = typename U::TYPE_REVERSE_HELP<LIST ,void>::RET ;

namespace U {
template <class...>
trait TYPE_PICK_HELP ;

template <class ARG1 ,class ARG2>
trait TYPE_PICK_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_EQ_ZERO<ARG2>>> {
	using RET = TYPE_FIRST_ONE<ARG1> ;
} ;

template <class ARG1 ,class ARG2>
trait TYPE_PICK_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_GT_ZERO<ARG2>>> {
	using RET = typename TYPE_PICK_HELP<TYPE_FIRST_REST<ARG1> ,ENUM_DEC<ARG2> ,void>::RET ;
} ;
} ;

template <class LIST ,class NTH>
using TYPE_PICK = typename U::TYPE_PICK_HELP<LIST ,NTH ,void>::RET ;

template <class LIST>
using TYPE_PICK_1ST = typename U::TYPE_PICK_HELP<LIST ,enumof (0) ,void>::RET ;

template <class LIST>
using TYPE_PICK_2ND = typename U::TYPE_PICK_HELP<LIST ,enumof (1) ,void>::RET ;

template <class LIST>
using TYPE_PICK_3RD = typename U::TYPE_PICK_HELP<LIST ,enumof (2) ,void>::RET ;

template <class LIST>
using TYPE_PICK_4TH = typename U::TYPE_PICK_HELP<LIST ,enumof (3) ,void>::RET ;

template <class LIST>
using TYPE_PICK_5TH = typename U::TYPE_PICK_HELP<LIST ,enumof (4) ,void>::RET ;

template <class LIST>
using TYPE_PICK_6TH = typename U::TYPE_PICK_HELP<LIST ,enumof (5) ,void>::RET ;

template <class LIST>
using TYPE_PICK_7TH = typename U::TYPE_PICK_HELP<LIST ,enumof (6) ,void>::RET ;

template <class LIST>
using TYPE_PICK_8TH = typename U::TYPE_PICK_HELP<LIST ,enumof (7) ,void>::RET ;

template <class LIST>
using TYPE_PICK_9TH = typename U::TYPE_PICK_HELP<LIST ,enumof (8) ,void>::RET ;

namespace U {
template <class...>
trait ENUM_ALL_HELP ;

template <class ARG1>
trait ENUM_ALL_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>> {
	using RET = ENUM_IDEN ;
} ;

template <class ARG1>
trait ENUM_ALL_HELP<ARG1 ,REQUIRE<ENUM_GT_ZERO<COUNTOF<ARG1>>>> {
	using R1X = ENUM_NOT_EQUAL<TYPE_FIRST_ONE<ARG1> ,ENUM_ZERO> ;
	using R2X = typename ENUM_ALL_HELP<TYPE_FIRST_REST<ARG1> ,void>::RET ;

	using RET = CONDITIONAL<R1X ,R2X ,ENUM_ZERO> ;
} ;
} ;

template <class...ARGS>
using ENUM_ALL = typename U::ENUM_ALL_HELP<TYPEAS<ARGS...> ,void>::RET ;

namespace U {
template <class...>
trait ENUM_ANY_HELP ;

template <class ARG1>
trait ENUM_ANY_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>> {
	using RET = ENUM_ZERO ;
} ;

template <class ARG1>
trait ENUM_ANY_HELP<ARG1 ,REQUIRE<ENUM_GT_ZERO<COUNTOF<ARG1>>>> {
	using R1X = ENUM_NOT_EQUAL<TYPE_FIRST_ONE<ARG1> ,ENUM_ZERO> ;
	using R2X = typename ENUM_ANY_HELP<TYPE_FIRST_REST<ARG1> ,void>::RET ;

	using RET = CONDITIONAL<R1X ,ENUM_IDEN ,R2X> ;
} ;
} ;

template <class...ARGS>
using ENUM_ANY = typename U::ENUM_ANY_HELP<TYPEAS<ARGS...> ,void>::RET ;

namespace S0 {
struct PLACEHOLDER {} ;
} ;

namespace S1 {
template <class BASE>
struct PLACEHOLDER :public BASE {} ;
} ;

namespace U {
template <class...>
trait PLACEHOLDER_HELP ;

template <class ARG1>
trait PLACEHOLDER_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<ARG1>>> {
	using RET = S0::PLACEHOLDER ;
} ;

template <class ARG1>
trait PLACEHOLDER_HELP<ARG1 ,REQUIRE<ENUM_GT_ZERO<ARG1>>> {
	using BASE = typename PLACEHOLDER_HELP<ENUM_DEC<ARG1> ,void>::RET ;

	using RET = S1::PLACEHOLDER<BASE> ;
} ;
} ;

template <class RANK>
using PLACEHOLDER = typename U::PLACEHOLDER_HELP<RANK ,void>::RET ;

static constexpr auto PH0 = PLACEHOLDER<enumof (0)> () ;
static constexpr auto PH1 = PLACEHOLDER<enumof (1)> () ;
static constexpr auto PH2 = PLACEHOLDER<enumof (2)> () ;
static constexpr auto PH3 = PLACEHOLDER<enumof (3)> () ;
static constexpr auto PH4 = PLACEHOLDER<enumof (4)> () ;
static constexpr auto PH5 = PLACEHOLDER<enumof (5)> () ;
static constexpr auto PH6 = PLACEHOLDER<enumof (6)> () ;
static constexpr auto PH7 = PLACEHOLDER<enumof (7)> () ;
static constexpr auto PH8 = PLACEHOLDER<enumof (8)> () ;
static constexpr auto PH9 = PLACEHOLDER<enumof (9)> () ;
static constexpr auto PHX = PLACEHOLDER<enumof (10)> () ;

template <class UNIT1>
using IS_BOOL = IS_SAME<UNIT1 ,BOOL> ;

template <class UNIT1>
using IS_VAR = ENUM_ANY<IS_SAME<UNIT1 ,VAR32> ,IS_SAME<UNIT1 ,VAR64>> ;

template <class UNIT1>
using IS_REAL = ENUM_ANY<IS_SAME<UNIT1 ,SINGLE> ,IS_SAME<UNIT1 ,DOUBLE>> ;

template <class UNIT1>
using IS_BYTE = ENUM_ANY<IS_SAME<UNIT1 ,BYTE> ,IS_SAME<UNIT1 ,WORD> ,IS_SAME<UNIT1 ,CHAR> ,IS_SAME<UNIT1 ,FEAT>> ;

template <class UNIT1>
using IS_STR = ENUM_ANY<IS_SAME<UNIT1 ,STRA> ,IS_SAME<UNIT1 ,STRW> ,IS_SAME<UNIT1 ,STRU8> ,IS_SAME<UNIT1 ,STRU16> ,IS_SAME<UNIT1 ,STRU32>> ;

template <class UNIT1>
using IS_NULL = IS_SAME<UNIT1 ,typeof (NULL)> ;

template <class UNIT1>
using IS_BASIC = ENUM_ANY<IS_BOOL<UNIT1> ,IS_VAR<UNIT1> ,IS_REAL<UNIT1> ,IS_BYTE<UNIT1> ,IS_STR<UNIT1> ,IS_NULL<UNIT1>> ;

namespace U {
template <class...>
trait IS_FUNCTION_HELP ;

template <class ARG1>
trait IS_FUNCTION_HELP<ARG1> {
	struct ID1 {
		imports constexpr VAR compile () {
			return std::is_function<ARG1>::value ;
		}
	} ;

	using RET = ENUMAS<ID1> ;
} ;
} ;

template <class UNIT1>
using IS_FUNCTION = typename U::IS_FUNCTION_HELP<UNIT1>::RET ;

template <class UNIT1>
using IS_NOEXCPET = ENUM_ZERO ;

namespace U {
template <class...>
trait IS_CLASS_HELP ;

template <class ARG1>
trait IS_CLASS_HELP<ARG1> {
	struct ID1 {
		imports constexpr VAR compile () {
			return std::is_class<ARG1>::value ;
		}
	} ;

	using RET = ENUMAS<ID1> ;
} ;
} ;

template <class UNIT1>
using IS_CLASS = typename U::IS_CLASS_HELP<UNIT1>::RET ;

template <class UNIT1>
using IS_STRUCT = IS_CLASS<UNIT1> ;

namespace U {
template <class...>
trait IS_TRIVIAL_HELP ;

template <class ARG1>
trait IS_TRIVIAL_HELP<ARG1> {
	struct ID1 {
		imports constexpr VAR compile () {
			return std::is_trivial<ARG1>::value ;
		}
	} ;

	using RET = ENUMAS<ID1> ;
} ;
} ;

template <class UNIT1>
using IS_TRIVIAL = typename U::IS_TRIVIAL_HELP<UNIT1>::RET ;

namespace U {
template <class...>
trait IS_CONSTRUCTIBLE_HELP ;

template <class ARG1 ,class...ARGS>
trait IS_CONSTRUCTIBLE_HELP<ARG1 ,TYPEAS<ARGS...>> {
	struct ID1 {
		imports constexpr VAR compile () {
			return std::is_constructible<ARG1 ,ARGS...>::value ;
		}
	} ;

	using RET = ENUMAS<ID1> ;
} ;
} ;

template <class UNIT1 ,class PARAMS>
using IS_CONSTRUCTIBLE = typename U::IS_CONSTRUCTIBLE_HELP<UNIT1 ,PARAMS>::RET ;

namespace U {
template <class...>
trait IS_CLONEABLE_HELP ;

template <class ARG1 ,class ARG2>
trait IS_CLONEABLE_HELP<ARG1 ,ARG2> {
	struct ID1 {
		imports constexpr VAR compile () {
			return std::is_copy_constructible<ARG1>::value ;
		}
	} ;

	struct ID2 {
		imports constexpr VAR compile () {
			return std::is_copy_assignable<ARG1>::value ;
		}
	} ;

	using RET = ENUM_ALL<ENUMAS<ID1> ,ENUMAS<ID2>> ;
} ;
} ;

template <class UNIT1>
using IS_CLONEABLE = typename U::IS_CLONEABLE_HELP<UNIT1>::RET ;

class Interface {
public:
	implicit Interface () = default ;
	implicit virtual ~Interface () noexcept = default ;
	implicit Interface (CREF<Interface>) = delete ;
	inline void operator= (CREF<Interface>) = delete ;
	implicit Interface (RREF<Interface>) = delete ;
	inline void operator= (RREF<Interface>) = delete ;
} ;

namespace U {
template <class...>
trait IS_INTERFACE_HELP ;

template <class ARG1 ,class ARG2>
trait IS_INTERFACE_HELP<ARG1 ,ARG2> {
	struct ID1 {
		imports constexpr VAR compile () {
			return std::is_base_of<ARG2 ,ARG1>::value ;
		}
	} ;

	struct ID2 {
		imports constexpr VAR compile () {
			return std::is_abstract<ARG1>::value ;
		}
	} ;

	using RET = ENUM_ALL<ENUMAS<ID1> ,ENUMAS<ID2>> ;
} ;
} ;

template <class UNIT1>
using IS_INTERFACE = typename U::IS_INTERFACE_HELP<UNIT1 ,Interface>::RET ;

namespace U {
template <class...>
trait IS_EXTEND_HELP ;

template <class ARG1 ,class ARG2>
trait IS_EXTEND_HELP<ARG1 ,ARG2> {
	struct ID1 {
		imports constexpr VAR compile () {
			return std::is_base_of<ARG1 ,ARG2>::value ;
		}
	} ;

	using RET = ENUMAS<ID1> ;
} ;
} ;

template <class BASE ,class DERIVED>
using IS_EXTEND = typename U::IS_EXTEND_HELP<BASE ,DERIVED>::RET ;

namespace U {
template <class...>
trait IS_CONVERTIBLE_HELP ;

template <class ARG1 ,class ARG2>
trait IS_CONVERTIBLE_HELP<ARG1 ,ARG2> {
	struct ID1 {
		imports constexpr VAR compile () {
			return std::is_convertible<ARG1 ,ARG2>::value ;
		}
	} ;

	using RET = ENUMAS<ID1> ;
} ;
} ;

template <class FROM ,class TO>
using IS_CONVERTIBLE = typename U::IS_CONVERTIBLE_HELP<FROM ,TO>::RET ;

template <class UNIT1>
using IS_PLACEHOLDER = IS_EXTEND<UNIT1 ,typeof (PH0)> ;

namespace U {
template <class...>
trait IS_ALL_SAME_HELP ;

template <class ARG1>
trait IS_ALL_SAME_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>> {
	using RET = ENUM_IDEN ;
} ;

template <class ARG1>
trait IS_ALL_SAME_HELP<ARG1 ,REQUIRE<ENUM_EQ_IDEN<COUNTOF<ARG1>>>> {
	using RET = ENUM_IDEN ;
} ;

template <class ARG1>
trait IS_ALL_SAME_HELP<ARG1 ,REQUIRE<ENUM_GT_IDEN<COUNTOF<ARG1>>>> {
	using R1X = TYPE_FIRST_ONE<ARG1> ;
	using R2X = TYPE_SECOND_ONE<ARG1> ;
	using R3X = typename IS_ALL_SAME_HELP<TYPE_CAT<R1X ,TYPE_SECOND_REST<ARG1>> ,void>::RET ;

	using RET = ENUM_ALL<IS_SAME<R1X ,R2X> ,R3X> ;
} ;
} ;

template <class...ARGS>
using IS_ALL_SAME = typename U::IS_ALL_SAME_HELP<TYPEAS<ARGS...> ,void>::RET ;

namespace U {
template <class...>
trait IS_ANY_SAME_HELP ;

template <class ARG1>
trait IS_ANY_SAME_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>> {
	using RET = ENUM_ZERO ;
} ;

template <class ARG1>
trait IS_ANY_SAME_HELP<ARG1 ,REQUIRE<ENUM_EQ_IDEN<COUNTOF<ARG1>>>> {
	using RET = ENUM_ZERO ;
} ;

template <class ARG1>
trait IS_ANY_SAME_HELP<ARG1 ,REQUIRE<ENUM_GT_IDEN<COUNTOF<ARG1>>>> {
	using R1X = TYPE_FIRST_ONE<ARG1> ;
	using R2X = TYPE_SECOND_ONE<ARG1> ;
	using R3X = typename IS_ANY_SAME_HELP<TYPE_CAT<R1X ,TYPE_SECOND_REST<ARG1>> ,void>::RET ;
	using R4X = typename IS_ANY_SAME_HELP<TYPE_CAT<R2X ,TYPE_SECOND_REST<ARG1>> ,void>::RET ;

	using RET = ENUM_ANY<IS_SAME<R1X ,R2X> ,R3X ,R4X> ;
} ;
} ;

template <class...ARGS>
using IS_ANY_SAME = typename U::IS_ANY_SAME_HELP<TYPEAS<ARGS...> ,void>::RET ;

namespace U {
template <class...>
trait BYTE_TRAIT_HELP ;

template <class ARG1 ,class ARG2>
trait BYTE_TRAIT_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_ALL<ENUM_EQUAL<ARG1 ,SIZEOF<BYTE>> ,ENUM_EQUAL<ARG2 ,ALIGNOF<BYTE>>>>> {
	using RET = BYTE ;
} ;

template <class ARG1 ,class ARG2>
trait BYTE_TRAIT_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_ALL<ENUM_EQUAL<ARG1 ,SIZEOF<WORD>> ,ENUM_EQUAL<ARG2 ,ALIGNOF<WORD>>>>> {
	using RET = WORD ;
} ;

template <class ARG1 ,class ARG2>
trait BYTE_TRAIT_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_ALL<ENUM_EQUAL<ARG1 ,SIZEOF<CHAR>> ,ENUM_EQUAL<ARG2 ,ALIGNOF<CHAR>>>>> {
	using RET = CHAR ;
} ;

template <class ARG1 ,class ARG2>
trait BYTE_TRAIT_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_ALL<ENUM_EQUAL<ARG1 ,SIZEOF<FEAT>> ,ENUM_EQUAL<ARG2 ,ALIGNOF<FEAT>>>>> {
	using RET = FEAT ;
} ;
} ;

template <class SIZE ,class ALIGN>
using BYTE_TRAIT = typename U::BYTE_TRAIT_HELP<SIZE ,ALIGN ,void>::RET ;

namespace U {
template <class...>
trait CAST_TRAIT_HELP ;

template <class ARG1 ,class ARG2>
trait CAST_TRAIT_HELP<ARG1 ,ARG2> {
	using RET = ARG1 ;
} ;

template <class ARG1 ,class ARG2>
trait CAST_TRAIT_HELP<ARG1 ,VREF<ARG2>> {
	using RET = VREF<ARG1> ;
} ;

template <class ARG1 ,class ARG2>
trait CAST_TRAIT_HELP<ARG1 ,CREF<ARG2>> {
	using RET = CREF<ARG1> ;
} ;

template <class ARG1 ,class ARG2>
trait CAST_TRAIT_HELP<ARG1 ,RREF<ARG2>> {
	using RET = RREF<ARG1> ;
} ;
} ;

template <class TO ,class FROM>
using CAST_TRAIT = typename U::CAST_TRAIT_HELP<TO ,FROM>::RET ;

namespace U {
template <class...>
trait STORAGE_HELP ;

template <class ARG1 ,class ARG2>
trait STORAGE_HELP<ARG1 ,ARG2> {
	using ITEM = BYTE_TRAIT<ARG2 ,ARG2> ;
	using SIZE = ENUM_DIV<ENUM_DEC<ENUM_ADD<ARG1 ,SIZEOF<ITEM>>> ,SIZEOF<ITEM>> ;

	struct STORAGE {
		DEF<ITEM[SIZE::value]> mUnused ;
	} ;
} ;
} ;

template <class SIZE ,class ALIGN = ENUM_IDEN>
using STORAGE = typename U::STORAGE_HELP<SIZE ,ALIGN>::STORAGE ;

namespace U {
template <class...>
trait TEMP_HELP ;

template <class UNIT1>
struct TEMPAS {
	STORAGE<SIZEOF<UNIT1> ,ALIGNOF<UNIT1>> mStorage ;
} ;

template <class ARG1>
trait TEMP_HELP<ARG1> {
	using RET = TEMPAS<REMOVE_ALL<ARG1>> ;
} ;
} ;

template <class UNIT1>
using TEMP = typename U::TEMP_HELP<UNIT1>::RET ;

namespace U {
template <class...>
trait REMOVE_TEMP_HELP ;

template <class ARG1>
trait REMOVE_TEMP_HELP<ARG1> {
	using RET = ARG1 ;
} ;

template <class ARG1>
trait REMOVE_TEMP_HELP<TEMPAS<ARG1>> {
	using RET = ARG1 ;
} ;
} ;

template <class UNIT1>
using REMOVE_TEMP = typename U::REMOVE_TEMP_HELP<UNIT1>::RET ;

namespace S0 {
struct PACK {} ;
} ;

namespace S1 {
template <class UNIT1>
struct PACK {
	UNIT1 mP1 ;
} ;
} ;

namespace S2 {
template <class UNIT1 ,class UNIT2>
struct PACK {
	UNIT1 mP1 ;
	UNIT2 mP2 ;
} ;
} ;

namespace S3 {
template <class UNIT1 ,class UNIT2 ,class UNIT3>
struct PACK {
	UNIT1 mP1 ;
	UNIT2 mP2 ;
	UNIT3 mP3 ;
} ;
} ;

namespace U {
template <class...>
trait PACK_HELP ;

template <class ARG1>
trait PACK_HELP<ARG1 ,REQUIRE<ENUM_EQUAL<COUNTOF<ARG1> ,enumof (0)>>> {
	using RET = S0::PACK ;
} ;

template <class ARG1>
trait PACK_HELP<ARG1 ,REQUIRE<ENUM_EQUAL<COUNTOF<ARG1> ,enumof (1)>>> {
	using FIRST = TYPE_PICK_1ST<ARG1> ;

	using RET = S1::PACK<FIRST> ;
} ;

template <class ARG1>
trait PACK_HELP<ARG1 ,REQUIRE<ENUM_EQUAL<COUNTOF<ARG1> ,enumof (2)>>> {
	using FIRST = TYPE_PICK_1ST<ARG1> ;
	using SECOND = TYPE_PICK_2ND<ARG1> ;

	using RET = S2::PACK<FIRST ,SECOND> ;
} ;

template <class ARG1>
trait PACK_HELP<ARG1 ,REQUIRE<ENUM_EQUAL<COUNTOF<ARG1> ,enumof (3)>>> {
	using FIRST = TYPE_PICK_1ST<ARG1> ;
	using SECOND = TYPE_PICK_2ND<ARG1> ;
	using THIRD = TYPE_PICK_3RD<ARG1> ;

	using RET = S3::PACK<FIRST ,SECOND ,THIRD> ;
} ;
} ;

template <class...UNITS>
using PACK = typename U::PACK_HELP<TYPEAS<UNITS...> ,void>::RET ;
} ;