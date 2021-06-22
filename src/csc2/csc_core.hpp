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
static constexpr auto VAR32_MIN = -VAR32_MAX ;
static constexpr auto VAR64_MAX = VAR64 (9223372036854775807) ;
static constexpr auto VAR64_MIN = -VAR64_MAX ;

namespace U {
template <class...>
trait VAR_HELP ;

template <class ARG1>
trait VAR_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_CONFIG_VAR32 ,ARG1>>> {
	using VAR = VAR32 ;

	static constexpr auto VAR_MAX = VAR32_MAX ;
	static constexpr auto VAR_MIN = VAR32_MIN ;
} ;

template <class ARG1>
trait VAR_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_CONFIG_VAR64 ,ARG1>>> {
	using VAR = VAR64 ;

	static constexpr auto VAR_MAX = VAR64_MAX ;
	static constexpr auto VAR_MIN = VAR64_MIN ;
} ;
} ;

using VAR = typename U::VAR_HELP<void ,ALWAYS>::VAR ;

static constexpr auto VAR_MAX = U::VAR_HELP<void ,void>::VAR_MAX ;
static constexpr auto VAR_MIN = U::VAR_HELP<void ,void>::VAR_MIN ;

static constexpr auto ZERO = VAR (+0) ;
static constexpr auto IDEN = VAR (+1) ;
static constexpr auto NONE = VAR (-1) ;
static constexpr auto USED = VAR (-2) ;

using INDEX = VAR ;
using LENGTH = VAR ;
using FLAG = VAR ;

using SINGLE = float ;
using DOUBLE = double ;

static constexpr auto SINGLE_MAX = SINGLE (3.402823466E+38) ;
static constexpr auto SINGLE_MIN = -SINGLE_MAX ;
static constexpr auto SINGLE_LOW = SINGLE (1.175494351E-38) ;
static constexpr auto SINGLE_EPS = SINGLE (1.192092896E-07) ;
static constexpr auto SINGLE_INF = SINGLE (std::numeric_limits<float>::infinity ()) ;
static constexpr auto DOUBLE_MAX = DOUBLE (1.7976931348623158E+308) ;
static constexpr auto DOUBLE_MIN = -DOUBLE_MAX ;
static constexpr auto DOUBLE_LOW = DOUBLE (2.2250738585072014E-308) ;
static constexpr auto DOUBLE_EPS = DOUBLE (2.2204460492503131E-016) ;
static constexpr auto DOUBLE_INF = SINGLE (std::numeric_limits<float>::infinity ()) ;

using STRA = char ;
using STRW = wchar_t ;

namespace U {
template <class...>
trait STR_HELP ;

template <class ARG1>
trait STR_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_CONFIG_STRA ,ARG1>>> {
	using STR = STRA ;
} ;

template <class ARG1>
trait STR_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_CONFIG_STRW ,ARG1>>> {
	using STR = STRW ;
} ;
} ;

using STR = typename U::STR_HELP<void ,ALWAYS>::STR ;

using BYTE = std::uint8_t ;
using WORD = std::uint16_t ;
using CHAR = std::uint32_t ;
using FEAT = std::uint64_t ;

static constexpr auto NULL = nullptr ;

template <class ARG1>
using DEF = ARG1 ;

template <class ARG1>
using PTR = ARG1 * ;

template <class ARG1>
using VREF = ARG1 & ;

template <class ARG1>
using CREF = const ARG1 & ;

template <class ARG1>
using RREF = ARG1 && ;

template <class ARG1>
using SIZE_OF = ENUMAS<VAR ,sizeof (ARG1)> ;

template <class ARG1>
using ALIGN_OF = ENUMAS<VAR ,alignof (ARG1)> ;

namespace U {
template <class...>
trait COUNT_OF_HELP ;

template <class...ARGS1>
trait COUNT_OF_HELP<TYPEAS<ARGS1...> ,ALWAYS> {
	using RET = ENUMAS<VAR ,sizeof... (ARGS1)> ;
} ;
} ;

template <class ARG1>
using COUNT_OF = typename U::COUNT_OF_HELP<ARG1 ,ALWAYS>::RET ;

namespace U {
template <class...>
trait IS_ENUM_HELP ;

template <class ARG1>
trait IS_ENUM_HELP<ARG1 ,ALWAYS> {
	using RET = ENUM_FALSE ;
} ;

template <class ARG1 ,ARG1 ARG2>
trait IS_ENUM_HELP<ENUMAS<ARG1 ,ARG2> ,ALWAYS> {
	using RET = ENUM_TRUE ;
} ;
} ;

template <class ARG1>
using IS_ENUM = typename U::IS_ENUM_HELP<ARG1 ,ALWAYS>::RET ;

namespace U {
template <class...>
trait ENUM_TYPE_HELP ;

template <class ARG1 ,ARG1 ARG2>
trait ENUM_TYPE_HELP<ENUMAS<ARG1 ,ARG2> ,ALWAYS> {
	using RET = ARG1 ;
} ;
} ;

template <class ARG1>
using ENUM_TYPE = typename U::ENUM_TYPE_HELP<ARG1 ,ALWAYS>::RET ;

namespace U {
template <class...>
trait IS_TYPE_HELP ;

template <class ARG1>
trait IS_TYPE_HELP<ARG1 ,ALWAYS> {
	using RET = ENUM_FALSE ;
} ;

template <class...ARGS1>
trait IS_TYPE_HELP<TYPEAS<ARGS1...> ,ALWAYS> {
	using RET = ENUM_TRUE ;
} ;
} ;

template <class ARG1>
using IS_TYPE = typename U::IS_TYPE_HELP<ARG1 ,ALWAYS>::RET ;

namespace U {
template <class...>
trait IS_SAME_HELP ;

template <class ARG1 ,class ARG2>
trait IS_SAME_HELP<ARG1 ,ARG2 ,ALWAYS> {
	using RET = ENUM_FALSE ;
} ;

template <class ARG1>
trait IS_SAME_HELP<ARG1 ,ARG1 ,ALWAYS> {
	using RET = ENUM_TRUE ;
} ;
} ;

template <class ARG1 ,class ARG2>
using IS_SAME = typename U::IS_SAME_HELP<ARG1 ,ARG2 ,ALWAYS>::RET ;

using ENUM_ZERO = ENUMAS<VAR ,ZERO> ;
using ENUM_IDEN = ENUMAS<VAR ,IDEN> ;
using ENUM_NONE = ENUMAS<VAR ,NONE> ;
using ENUM_USED = ENUMAS<VAR ,USED> ;

namespace U {
template <class...>
trait ENABLE_HELP ;

template <class ARG1 ,class ARG2>
trait ENABLE_HELP<ARG1 ,ARG2 ,REQUIRE<ARG1>> {
	using RET = ARG2 ;
} ;
} ;

template <class COND ,class YES = void>
using ENABLE = typename U::ENABLE_HELP<COND ,YES ,ALWAYS>::RET ;

template <class ARG1>
using ENUM_CHECK = ENABLE<IS_ENUM<ARG1> ,ARG1> ;

template <class ARG1>
using TYPE_CHECK = ENABLE<IS_TYPE<ARG1> ,ARG1> ;

namespace U {
template <class...>
trait ENUM_NOT_HELP ;

template <>
trait ENUM_NOT_HELP<ENUM_TRUE ,ALWAYS> {
	using RET = ENUM_FALSE ;
} ;

template <>
trait ENUM_NOT_HELP<ENUM_FALSE ,ALWAYS> {
	using RET = ENUM_TRUE ;
} ;
} ;

template <class ARG1>
using ENUM_NOT = typename U::ENUM_NOT_HELP<ARG1 ,ALWAYS>::RET ;

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
using CONDITIONAL = typename U::CONDITIONAL_HELP<COND ,YES ,NO ,ALWAYS>::RET ;

template <class ARG1 ,class ARG2>
using ENUM_EQUAL = ENUMAS<BOOL ,(ENUM_CHECK<ARG1>::value == ENUM_CHECK<ARG2>::value)> ;

template <class ARG1 ,class ARG2>
using ENUM_NOT_EQUAL = ENUM_NOT<ENUM_EQUAL<ARG1 ,ARG2>> ;

namespace U {
template <class...>
trait ENUM_COMPR_HELP ;

template <>
trait ENUM_COMPR_HELP<ENUM_TRUE ,ENUM_FALSE ,ALWAYS> {
	using RET = ENUM_NONE ;
} ;

template <>
trait ENUM_COMPR_HELP<ENUM_FALSE ,ENUM_TRUE ,ALWAYS> {
	using RET = ENUM_IDEN ;
} ;

template <>
trait ENUM_COMPR_HELP<ENUM_FALSE ,ENUM_FALSE ,ALWAYS> {
	using RET = ENUM_ZERO ;
} ;
} ;

template <class ARG1 ,class ARG2>
using ENUM_COMPR = typename U::ENUM_COMPR_HELP<
	ENUMAS<BOOL ,(ENUM_CHECK<ARG1>::value < ENUM_CHECK<ARG2>::value)> ,
	ENUMAS<BOOL ,(ENUM_CHECK<ARG2>::value < ENUM_CHECK<ARG1>::value)> ,
	ALWAYS>::RET ;

template <class ARG1 ,class ARG2>
using ENUM_COMPR_LT = ENUMAS<BOOL ,(ENUM_COMPR<ARG1 ,ARG2>::value < ZERO)> ;

template <class ARG1 ,class ARG2>
using ENUM_COMPR_LTEQ = ENUMAS<BOOL ,(ENUM_COMPR<ARG1 ,ARG2>::value <= ZERO)> ;

template <class ARG1 ,class ARG2>
using ENUM_COMPR_GT = ENUMAS<BOOL ,(ENUM_COMPR<ARG1 ,ARG2>::value > ZERO)> ;

template <class ARG1 ,class ARG2>
using ENUM_COMPR_GTEQ = ENUMAS<BOOL ,(ENUM_COMPR<ARG1 ,ARG2>::value >= ZERO)> ;

template <class ARG1>
using ENUM_EQ_ZERO = ENUM_EQUAL<ARG1 ,ENUM_ZERO> ;

template <class ARG1>
using ENUM_LT_ZERO = ENUM_COMPR_LT<ARG1 ,ENUM_ZERO> ;

template <class ARG1>
using ENUM_GT_ZERO = ENUM_COMPR_GT<ARG1 ,ENUM_ZERO> ;

template <class ARG1>
using ENUM_EQ_IDEN = ENUM_EQUAL<ARG1 ,ENUM_IDEN> ;

template <class ARG1>
using ENUM_LT_IDEN = ENUM_COMPR_LT<ARG1 ,ENUM_IDEN> ;

template <class ARG1>
using ENUM_GT_IDEN = ENUM_COMPR_GT<ARG1 ,ENUM_IDEN> ;

template <class ARG1 ,class ARG2>
using ENUM_ADD = ENUMAS<ENUM_TYPE<ARG1> ,(ENUM_CHECK<ARG1>::value + ENUM_CHECK<ARG2>::value)> ;

template <class ARG1 ,class ARG2>
using ENUM_SUB = ENUMAS<ENUM_TYPE<ARG1> ,(ENUM_CHECK<ARG1>::value - ENUM_CHECK<ARG2>::value)> ;

template <class ARG1 ,class ARG2>
using ENUM_MUL = ENUMAS<ENUM_TYPE<ARG1> ,(ENUM_CHECK<ARG1>::value * ENUM_CHECK<ARG2>::value)> ;

template <class ARG1 ,class ARG2>
using ENUM_DIV = ENUMAS<ENUM_TYPE<ARG1> ,(ENUM_CHECK<ARG1>::value / ENUM_CHECK<ARG2>::value)> ;

template <class ARG1 ,class ARG2>
using ENUM_MOD = ENUMAS<ENUM_TYPE<ARG1> ,(ENUM_CHECK<ARG1>::value % ENUM_CHECK<ARG2>::value)> ;

template <class ARG1>
using ENUM_MINUS = ENUM_SUB<ENUM_ZERO ,ARG1> ;

template <class ARG1>
using ENUM_INC = ENUM_ADD<ARG1 ,ENUM_IDEN> ;

template <class ARG1>
using ENUM_DEC = ENUM_SUB<ARG1 ,ENUM_IDEN> ;

namespace U {
template <class...>
trait TYPE_FIRST_HELP ;

template <class ARG1 ,class...ARGS>
trait TYPE_FIRST_HELP<TYPEAS<ARG1 ,ARGS...> ,ALWAYS> {
	using ONE = ARG1 ;
	using REST = TYPEAS<ARGS...> ;
} ;
} ;

template <class ARG1>
using TYPE_FIRST_ONE = typename U::TYPE_FIRST_HELP<ARG1 ,ALWAYS>::ONE ;

template <class ARG1>
using TYPE_FIRST_REST = typename U::TYPE_FIRST_HELP<ARG1 ,ALWAYS>::REST ;

namespace U {
template <class...>
trait TYPE_SECOND_HELP ;

template <class ARG1 ,class ARG2 ,class...ARGS>
trait TYPE_SECOND_HELP<TYPEAS<ARG1 ,ARG2 ,ARGS...> ,ALWAYS> {
	using ONE = ARG2 ;
	using REST = TYPEAS<ARGS...> ;
} ;
} ;

template <class ARG1>
using TYPE_SECOND_ONE = typename U::TYPE_SECOND_HELP<ARG1 ,ALWAYS>::ONE ;

template <class ARG1>
using TYPE_SECOND_REST = typename U::TYPE_SECOND_HELP<ARG1 ,ALWAYS>::REST ;

template <class ARG1>
using TYPE_UNWIND = ENABLE<ENUM_EQ_IDEN<COUNT_OF<ARG1>> ,TYPE_FIRST_ONE<ARG1>> ;

namespace U {
template <class...>
trait TYPE_CAT_HELP ;

template <class...ARGS1 ,class...ARGS2>
trait TYPE_CAT_HELP<TYPEAS<ARGS1...> ,TYPEAS<ARGS2...> ,ALWAYS> {
	using RET = TYPEAS<ARGS1... ,ARGS2...> ;
} ;
} ;

template <class ARG1 ,class ARG2>
using TYPE_CAT = typename U::TYPE_CAT_HELP<ARG1 ,ARG2 ,ALWAYS>::RET ;

namespace U {
template <class...>
trait TYPE_REPEAT_HELP ;

template <class ARG1 ,class ARG2>
trait TYPE_REPEAT_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_EQ_ZERO<ARG2>>> {
	using RET = TYPEAS<> ;
} ;

template <class ARG1 ,class ARG2>
trait TYPE_REPEAT_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_GT_ZERO<ARG2>>> {
	using R1X = typename TYPE_REPEAT_HELP<ARG1 ,ENUM_DEC<ARG2> ,ALWAYS>::RET ;
	using RET = TYPE_CAT<R1X ,TYPEAS<ARG1>> ;
} ;
} ;

template <class ITEM ,class SIZE>
using TYPE_REPEAT = typename U::TYPE_REPEAT_HELP<ITEM ,SIZE ,ALWAYS>::RET ;

namespace U {
template <class...>
trait ENUM_ALL_HELP ;

template <class ARG1>
trait ENUM_ALL_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<COUNT_OF<ARG1>>>> {
	using RET = ENUM_TRUE ;
} ;

template <class ARG1>
trait ENUM_ALL_HELP<ARG1 ,REQUIRE<ENUM_GT_ZERO<COUNT_OF<ARG1>>>> {
	using R1X = ENUM_BOOL<TYPE_FIRST_ONE<ARG1>> ;
	using R3X = typename ENUM_ALL_HELP<TYPE_FIRST_REST<ARG1> ,ALWAYS>::RET ;
	using RET = CONDITIONAL<R1X ,R3X ,ENUM_FALSE> ;
} ;
} ;

template <class...ARGS>
using ENUM_ALL = typename U::ENUM_ALL_HELP<TYPEAS<ARGS...> ,ALWAYS>::RET ;

namespace U {
template <class...>
trait ENUM_ANY_HELP ;

template <class ARG1>
trait ENUM_ANY_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<COUNT_OF<ARG1>>>> {
	using RET = ENUM_FALSE ;
} ;

template <class ARG1>
trait ENUM_ANY_HELP<ARG1 ,REQUIRE<ENUM_GT_ZERO<COUNT_OF<ARG1>>>> {
	using R1X = ENUM_BOOL<TYPE_FIRST_ONE<ARG1>> ;
	using R3X = typename ENUM_ANY_HELP<TYPE_FIRST_REST<ARG1> ,ALWAYS>::RET ;
	using RET = CONDITIONAL<R1X ,ENUM_TRUE ,R3X> ;
} ;
} ;

template <class...ARGS>
using ENUM_ANY = typename U::ENUM_ANY_HELP<TYPEAS<ARGS...> ,ALWAYS>::RET ;

namespace U {
template <class...>
trait PLACEHOLDER_HELP ;

template <class ARG1>
trait PLACEHOLDER_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<ARG1>>> {
	class PlaceHolder {} ;
} ;

template <class ARG1>
trait PLACEHOLDER_HELP<ARG1 ,REQUIRE<ENUM_GT_ZERO<ARG1>>> {
	using BASE = typename PLACEHOLDER_HELP<ENUM_DEC<ARG1> ,ALWAYS>::PlaceHolder ;

	class PlaceHolder :public BASE {} ;
} ;
} ;

template <class RANK>
using PlaceHolder = typename U::PLACEHOLDER_HELP<RANK ,ALWAYS>::PlaceHolder ;

static constexpr auto PH0 = PlaceHolder<ENUMAS<VAR ,(+0)>> () ;
static constexpr auto PH1 = PlaceHolder<ENUMAS<VAR ,(+1)>> () ;
static constexpr auto PH2 = PlaceHolder<ENUMAS<VAR ,(+2)>> () ;
static constexpr auto PH3 = PlaceHolder<ENUMAS<VAR ,(+3)>> () ;
static constexpr auto PH4 = PlaceHolder<ENUMAS<VAR ,(+4)>> () ;
static constexpr auto PH5 = PlaceHolder<ENUMAS<VAR ,(+5)>> () ;
static constexpr auto PH6 = PlaceHolder<ENUMAS<VAR ,(+6)>> () ;
static constexpr auto PH7 = PlaceHolder<ENUMAS<VAR ,(+7)>> () ;
static constexpr auto PH8 = PlaceHolder<ENUMAS<VAR ,(+8)>> () ;
static constexpr auto PH9 = PlaceHolder<ENUMAS<VAR ,(+9)>> () ;
static constexpr auto PHX = PlaceHolder<ENUMAS<VAR ,(10)>> () ;

template <class ARG1>
using IS_CLASS = ENUMAS<BOOL ,(std::is_class<ARG1>::value)> ;

namespace U {
template <class...>
trait IS_CONSTRUCTIBLE_HELP ;

template <class ARG1 ,class...ARGS2>
trait IS_CONSTRUCTIBLE_HELP<ARG1 ,TYPEAS<ARGS2...> ,ALWAYS> {
	using RET = ENUMAS<BOOL ,(std::is_constructible<ARG1 ,ARGS2...>::value)> ;
} ;
} ;

template <class RETURN ,class PARAMS>
using IS_CONSTRUCTIBLE = typename U::IS_CONSTRUCTIBLE_HELP<RETURN ,PARAMS ,ALWAYS>::RET ;

template <class FROM ,class TO>
using IS_CONVERTIBLE = IS_CONSTRUCTIBLE<TO ,TYPEAS<FROM>> ;

template <class ARG1>
using IS_NULLOPT = ENUMAS<BOOL ,(std::is_nothrow_default_constructible<ARG1>::value)> ;

template <class ARG1>
using IS_CLONEABLE = ENUM_ALL<
	ENUMAS<BOOL ,(std::is_copy_constructible<ARG1>::value)> ,
	ENUMAS<BOOL ,(std::is_copy_assignable<ARG1>::value)>> ;

template <class ARG1>
using IS_STRUCT = ENUMAS<BOOL ,(std::is_trivial<ARG1>::value)> ;

struct Interface {
	implicit Interface () = default ;
	virtual ~Interface () noexcept = default ;
	implicit Interface (CREF<Interface>) = delete ;
	void operator= (CREF<Interface>) = delete ;
	implicit Interface (RREF<Interface>) = delete ;
	void operator= (RREF<Interface>) = delete ;
} ;

template <class ARG1>
using IS_INTERFACE = ENUM_ALL<
	ENUMAS<BOOL ,(std::is_abstract<ARG1>::value)> ,
	ENUMAS<BOOL ,(std::is_base_of<Interface ,ARG1>::value)>> ;

template <class BASE ,class DERIVED>
using IS_EXTEND = ENUMAS<BOOL ,(std::is_base_of<BASE ,DERIVED>::value)> ;

template <class ARG1>
using IS_FUNCTION = ENUMAS<BOOL ,(std::is_function<ARG1>::value)> ;

namespace U {
template <class...>
trait REFLECT_FUNCTION_HELP ;

template <class ARG1 ,class...ARGS>
trait REFLECT_FUNCTION_HELP<DEF<ARG1 (ARGS...)> ,ALWAYS> {
	using R1X = REMOVE_CVR<ARG1> ;
	using R2X = TYPEAS<REMOVE_CVR<ARGS>...> ;
	using RET = TYPEAS<R1X ,R2X> ;
} ;

template <class ARG1 ,class ARG2 ,class...ARGS>
trait REFLECT_FUNCTION_HELP<DEF<DEF<ARG1 (ARGS...)> ARG2::*> ,ALWAYS> {
	using R1X = REMOVE_CVR<ARG1> ;
	using R2X = TYPEAS<REMOVE_CVR<ARGS>...> ;
	using RET = TYPEAS<R1X ,R2X> ;
} ;

template <class ARG1 ,class ARG2 ,class...ARGS>
trait REFLECT_FUNCTION_HELP<DEF<DEF<ARG1 (ARGS...) const> ARG2::*> ,ALWAYS> {
	using R1X = REMOVE_CVR<ARG1> ;
	using R2X = TYPEAS<REMOVE_CVR<ARGS>...> ;
	using RET = TYPEAS<R1X ,R2X> ;
} ;
} ;

template <class ARG1>
using REFLECT_FUNCTION = typename U::REFLECT_FUNCTION_HELP<typeof (ARG1::operator()) ,ALWAYS>::RET ;

template <class ARG1>
using FUNCTION_RETURN = TYPE_FIRST_ONE<REFLECT_FUNCTION<ARG1>> ;

template <class ARG1>
using FUNCTION_PARAMS = TYPE_SECOND_ONE<REFLECT_FUNCTION<ARG1>> ;

template <class ARG1>
using IS_BOOL = IS_SAME<ARG1 ,BOOL> ;

template <class ARG1>
using IS_VAR = ENUM_ANY<
	IS_SAME<ARG1 ,VAR32> ,
	IS_SAME<ARG1 ,VAR64>> ;

template <class ARG1>
using IS_FLOAT = ENUM_ANY<
	IS_SAME<ARG1 ,SINGLE> ,
	IS_SAME<ARG1 ,DOUBLE>> ;

template <class ARG1>
using IS_STR = ENUM_ANY<
	IS_SAME<ARG1 ,STRA> ,
	IS_SAME<ARG1 ,STRW>> ;

template <class ARG1>
using IS_BYTE = ENUM_ANY<
	IS_SAME<ARG1 ,BYTE> ,
	IS_SAME<ARG1 ,WORD> ,
	IS_SAME<ARG1 ,CHAR> ,
	IS_SAME<ARG1 ,FEAT>> ;

template <class ARG1>
using IS_NULL = IS_SAME<ARG1 ,typeof (NULL)> ;

template <class ARG1>
using IS_BASIC = ENUM_ANY<
	IS_BOOL<ARG1> ,
	IS_VAR<ARG1> ,
	IS_FLOAT<ARG1> ,
	IS_STR<ARG1> ,
	IS_BYTE<ARG1> ,
	IS_NULL<ARG1>> ;

template <class ARG1>
using IS_PLACEHOLDER = IS_EXTEND<ARG1 ,typeof (PH0)> ;

namespace U {
template <class...>
trait BYTE_BASE_HELP ;

template <class ARG1 ,class ARG2>
trait BYTE_BASE_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_ALL<
	ENUM_EQUAL<ARG1 ,SIZE_OF<BYTE>> ,
	ENUM_EQUAL<ARG2 ,ALIGN_OF<BYTE>>>>> {
	using RET = BYTE ;
} ;

template <class ARG1 ,class ARG2>
trait BYTE_BASE_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_ALL<
	ENUM_EQUAL<ARG1 ,SIZE_OF<WORD>> ,
	ENUM_EQUAL<ARG2 ,ALIGN_OF<WORD>>>>> {
	using RET = WORD ;
} ;

template <class ARG1 ,class ARG2>
trait BYTE_BASE_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_ALL<
	ENUM_EQUAL<ARG1 ,SIZE_OF<CHAR>> ,
	ENUM_EQUAL<ARG2 ,ALIGN_OF<CHAR>>>>> {
	using RET = CHAR ;
} ;

template <class ARG1 ,class ARG2>
trait BYTE_BASE_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_ALL<
	ENUM_EQUAL<ARG1 ,SIZE_OF<FEAT>> ,
	ENUM_EQUAL<ARG2 ,ALIGN_OF<FEAT>>>>> {
	using RET = FEAT ;
} ;
} ;

template <class SIZE ,class ALIGN>
using BYTE_BASE = typename U::BYTE_BASE_HELP<SIZE ,ALIGN ,ALWAYS>::RET ;

namespace U {
template <class...>
trait STORAGE_HELP ;

template <class ARG1 ,class ARG2>
trait STORAGE_HELP<ARG1 ,ARG2 ,ALWAYS> {
	using R3X = BYTE_BASE<ARG2 ,ARG2> ;
	using R1X = SIZE_OF<R3X> ;
	using R4X = ENUM_DIV<ENUM_ADD<ARG1 ,ENUM_DEC<R1X>> ,R1X> ;
	using RET = DEF<R3X[ENUM_CHECK<R4X>::value]> ;
} ;
} ;

template <class SIZE ,class ALIGN = ENUM_IDEN>
using Storage = typename U::STORAGE_HELP<SIZE ,ALIGN ,ALWAYS>::RET ;

namespace U {
template <class ARG1>
struct TEMPID {
	Storage<SIZE_OF<ARG1> ,ALIGN_OF<ARG1>> mStorage ;
} ;
} ;

template <class UNIT>
using TEMP = U::TEMPID<UNIT> ;

namespace U {
template <class...>
trait REMOVE_TEMP_HELP ;

template <class ARG1>
trait REMOVE_TEMP_HELP<ARG1 ,ALWAYS> {
	using RET = ARG1 ;
} ;

template <class ARG1>
trait REMOVE_TEMP_HELP<TEMP<ARG1> ,ALWAYS> {
	using RET = ARG1 ;
} ;
} ;

template <class ARG1>
using REMOVE_TEMP = typename U::REMOVE_TEMP_HELP<ARG1 ,ALWAYS>::RET ;

template <class ARG1>
using IS_TEMP = IS_SAME<ARG1 ,REMOVE_TEMP<ARG1>> ;

template <class ARG1>
using ENUM_ABS = CONDITIONAL<ENUM_COMPR_GTEQ<ARG1 ,ENUM_ZERO> ,ARG1 ,ENUM_MINUS<ARG1>> ;

template <class ARG1 ,class ARG2>
using ENUM_MIN = CONDITIONAL<ENUM_COMPR_LTEQ<ARG1 ,ARG2> ,ARG1 ,ARG2> ;

template <class ARG1 ,class ARG2>
using ENUM_MAX = CONDITIONAL<ENUM_COMPR_GTEQ<ARG1 ,ARG2> ,ARG1 ,ARG2> ;

template <class CURR ,class BEGIN ,class END>
using ENUM_BETWEEN = ENUM_ALL<ENUM_COMPR_GTEQ<CURR ,BEGIN> ,ENUM_COMPR_LT<CURR ,END>> ;

struct FUNCTION_noop {
	inline void operator() () const noexcept {
		//@info: noop
	}

	template <class ARG1>
	inline void operator() (CREF<ARG1> arg1) const noexcept {
		//@info: noop
	}
} ;

static constexpr auto noop = FUNCTION_noop () ;

namespace U {
template <class...>
trait FUNCTION_barrier_HELP ;

template <class ARG1>
trait FUNCTION_barrier_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_MSVC ,ARG1>>> {
	struct FUNCTION_barrier {
		inline void operator() () const {
			noop () ;
		}
	} ;
} ;

template <class ARG1>
trait FUNCTION_barrier_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_GNUC ,ARG1>>> {
	struct FUNCTION_barrier {
		template <class ARG1>
		inline void operator() () const {
#ifdef __CSC_COMPILER_GNUC__
			asm volatile ("" ::: "memory") ;
#endif
		}
	} ;
} ;

template <class ARG1>
trait FUNCTION_barrier_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_CLANG ,ARG1>>> {
	struct FUNCTION_barrier {
		inline void operator() () const {
#ifdef __CSC_COMPILER_CLANG__
			asm volatile ("" ::: "memory") ;
#endif
		}
	} ;
} ;
} ;

struct FUNCTION_barrier {
	inline void operator() () const {
		using R1X = typename U::FUNCTION_barrier_HELP<void ,ALWAYS>::FUNCTION_barrier ;
		static constexpr auto M_INVOKE = R1X () ;
		return M_INVOKE () ;
	}
} ;

static constexpr auto barrier = FUNCTION_barrier () ;

struct FUNCTION_unsafe_deref {
	template <class ARG1>
	inline VREF<ARG1> operator() (VREF<TEMP<ARG1>> arg1) const {
		return reinterpret_cast<VREF<ARG1>> (arg1) ;
	}

	template <class ARG1>
	inline CREF<ARG1> operator() (CREF<TEMP<ARG1>> arg1) const {
		return reinterpret_cast<CREF<ARG1>> (arg1) ;
	}

	template <class ARG1>
	inline RREF<ARG1> operator() (RREF<TEMP<ARG1>> arg1) const {
		requires (ENUM_FALSE) ;
	}
} ;

static constexpr auto unsafe_deref = FUNCTION_unsafe_deref () ;

struct FUNCTION_unsafe_deptr {
	template <class ARG1>
	inline VREF<TEMP<ARG1>> operator() (VREF<ARG1> arg1) const {
		return reinterpret_cast<VREF<TEMP<ARG1>>> (arg1) ;
	}

	template <class ARG1>
	inline CREF<TEMP<ARG1>> operator() (CREF<ARG1> arg1) const {
		return reinterpret_cast<CREF<TEMP<ARG1>>> (arg1) ;
	}

	template <class ARG1>
	inline RREF<TEMP<ARG1>> operator() (RREF<ARG1> arg1) const {
		requires (ENUM_FALSE) ;
	}
} ;

static constexpr auto unsafe_deptr = FUNCTION_unsafe_deptr () ;

struct FUNCTION_address {
	template <class ARG1>
	inline LENGTH operator() (CREF<ARG1> arg1) const {
		return LENGTH (&unsafe_deptr (arg1)) ;
	}
} ;

static constexpr auto address = FUNCTION_address () ;

struct FUNCTION_swap {
	template <class ARG1>
	inline void operator() (VREF<ARG1> arg1 ,VREF<ARG1> arg2) const {
		auto rax = unsafe_deptr (arg1) ;
		unsafe_deptr (arg1) = unsafe_deptr (arg2) ;
		unsafe_deptr (arg2) = rax ;
		barrier () ;
	}
} ;

static constexpr auto swap = FUNCTION_swap () ;

struct FUNCTION_move {
	template <class ARG1>
	inline CREF<REMOVE_CVR<ARG1>> operator() (CREF<ARG1> arg1) const {
		return arg1 ;
	}

	template <class ARG1>
	inline RREF<REMOVE_CVR<ARG1>> operator() (VREF<ARG1> arg1) const {
		return static_cast<RREF<REMOVE_CVR<ARG1>>> (arg1) ;
	}

	template <class ARG1>
	inline RREF<REMOVE_CVR<ARG1>> operator() (RREF<ARG1> arg1) const {
		requires (ENUM_FALSE) ;
	}
} ;

static constexpr auto move = FUNCTION_move () ;

struct FUNCTION_forward {
	template <class ARG1>
	inline REMOVE_CVR<ARG1> operator() (RREF<ARG1> arg1) const {
		//@mark
		return move (arg1) ;
	}
} ;

static constexpr auto forward = FUNCTION_forward () ;

struct FUNCTION_zeroize {
	template <class ARG1>
	inline void operator() (VREF<ARG1> arg1) const {
		unsafe_deptr (arg1) = {0} ;
		barrier () ;
	}
} ;

static constexpr auto zeroize = FUNCTION_zeroize () ;

struct FUNCTION_create {
	template <class ARG1 ,class...ARGS>
	inline void operator() (VREF<TEMP<ARG1>> thiz ,RREF<ARGS>...objs) const {
		using R1X = typeof (thiz) ;
		using R2X = REMOVE_TEMP<R1X> ;
		new (&unsafe_deref (thiz)) R2X (forward (objs)...) ;
	}
} ;

static constexpr auto create = FUNCTION_create () ;

struct FUNCTION_destroy {
	template <class ARG1 ,class...ARGS>
	inline void operator() (VREF<TEMP<ARG1>> thiz) const {
		using R1X = typeof (thiz) ;
		using R2X = REMOVE_TEMP<R1X> ;
		unsafe_deref (thiz).~R2X () ;
	}
} ;

static constexpr auto destroy = FUNCTION_destroy () ;

struct FUNCTION_recreate {
	template <class ARG1 ,class ARG2>
	inline void operator() (VREF<ARG1> thiz ,RREF<ARG2> that) const {
		using R1X = typeof (thiz) ;
		using R2X = typeof (that) ;
		requires (IS_SAME<R1X ,R2X>) ;
		destroy (unsafe_deptr (thiz)) ;
		create (unsafe_deptr (thiz) ,forward (that)) ;
		barrier () ;
	}
} ;

static constexpr auto recreate = FUNCTION_recreate () ;

namespace U {
template <class...>
trait FUNCTION_debug_assert_HELP ;

template <class ARG1>
trait FUNCTION_debug_assert_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_MSVC ,ARG1>>> {
	struct FUNCTION_debug_assert {
		inline void operator() (CREF<BOOL> expr) const {
			if (expr)
				return ;
#ifdef __CSC_COMPILER_MSVC__
			__debugbreak () ;
#endif
		}
	} ;
} ;

template <class ARG1>
trait FUNCTION_debug_assert_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_GNUC ,ARG1>>> {
	struct FUNCTION_debug_assert {
		inline void operator() (CREF<BOOL> expr) const {
			if (expr)
				return ;
#ifdef __CSC_COMPILER_GUNC__
			__builtin_trap () ;
#endif
		}
	} ;
} ;

template <class ARG1>
trait FUNCTION_debug_assert_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_CLANG ,ARG1>>> {
	struct FUNCTION_debug_assert {
		inline void operator() (CREF<BOOL> expr) const {
			if (expr)
				return ;
			std::abort () ;
		}
	} ;
} ;
} ;

struct FUNCTION_debug_assert {
	inline void operator() (CREF<BOOL> expr) const {
		using R1X = typename U::FUNCTION_debug_assert_HELP<void ,ALWAYS>::FUNCTION_debug_assert ;
		static constexpr auto M_INVOKE = R1X () ;
		return M_INVOKE (expr) ;
	}
} ;

static constexpr auto debug_assert = FUNCTION_debug_assert () ;

static constexpr auto unittest_assert = FUNCTION_debug_assert () ;

struct FUNCTION_bad {
	template <class ARG1>
	inline REMOVE_ALL<ARG1> operator() (CREF<ARG1> id) const {
		auto &&thiz = *this ;
		assert (FALSE) ;
		return thiz (id) ;
	}
} ;

static constexpr auto bad = FUNCTION_bad () ;

struct FUNCTION_memorize {
	template <class ARG1>
	inline CREF<FUNCTION_RETURN<REMOVE_CVR<ARG1>>> operator() (CREF<ARG1> proc) const {
		static const auto M_MEMORIZE = proc () ;
		return M_MEMORIZE ;
	}
} ;

static constexpr auto memorize = FUNCTION_memorize () ;

struct FUNCTION_operator_cabi {
	template <class BASE>
	struct CABI :public Interface {} ;

	template <class ARG1>
	inline FLAG operator() (CREF<ARG1> id) const {
		using R1X = typeof (id) ;
		using R2X = CABI<R1X> ;
		requires (ENUM_EQUAL<SIZE_OF<R2X> ,SIZE_OF<FLAG>>) ;
		requires (ENUM_EQUAL<ALIGN_OF<R2X> ,ALIGN_OF<FLAG>>) ;
		FLAG ret = ZERO ;
		R2X tmp ;
		swap (unsafe_deptr (ret).mStorage ,unsafe_deptr (tmp).mStorage) ;
		barrier () ;
		return move (ret) ;
	}
} ;

static constexpr auto operator_cabi = FUNCTION_operator_cabi () ;

namespace U {
template <class...>
trait FUNCTION_operator_compr_HELP ;

template <class ARG1>
trait FUNCTION_operator_compr_HELP<ARG1 ,REQUIRE<IS_CLASS<ARG1>>> {
	struct FUNCTION_operator_compr {
		template <class ARG1>
		inline FLAG operator() (CREF<ARG1> arg1 ,CREF<ARG1> arg2) const {
			return arg1.compr (arg2) ;
		}
	} ;
} ;

template <class ARG1>
trait FUNCTION_operator_compr_HELP<ARG1 ,REQUIRE<ENUM_NOT<IS_CLASS<ARG1>>>> {
	struct FUNCTION_operator_compr {
		template <class ARG1>
		inline FLAG operator() (CREF<ARG1> arg1 ,CREF<ARG1> arg2) const {
			if (arg1 < arg2)
				return NONE ;
			if (arg2 < arg1)
				return IDEN ;
			return ZERO ;
		}
	} ;
} ;
} ;

struct FUNCTION_operator_compr {
	template <class ARG1>
	inline FLAG operator() (CREF<ARG1> arg1 ,CREF<ARG1> arg2) const {
		using R1X = typeof (arg1) ;
		using R2X = typename U::FUNCTION_operator_compr_HELP<R1X ,ALWAYS>::FUNCTION_operator_compr ;
		static constexpr auto M_INVOKE = R2X () ;
		return M_INVOKE (arg1 ,arg2) ;
	}
} ;

static constexpr auto operator_compr = FUNCTION_operator_compr () ;

namespace U {
template <class...>
trait FUNCTION_operator_hash_HELP ;

template <class ARG1>
trait FUNCTION_operator_hash_HELP<ARG1 ,REQUIRE<IS_CLASS<ARG1>>> {
	struct FUNCTION_operator_hash {
		template <class ARG1>
		inline FLAG operator() (CREF<ARG1> arg1) const {
			return arg1.hash () ;
		}
	} ;
} ;

template <class ARG1>
trait FUNCTION_operator_hash_HELP<ARG1 ,REQUIRE<ENUM_NOT<IS_CLASS<ARG1>>>> {
	struct FUNCTION_operator_hash {
		template <class ARG1>
		inline FLAG operator() (CREF<ARG1> arg1) const {
			return FLAG (arg1) ;
		}
	} ;
} ;
} ;

struct FUNCTION_operator_hash {
	template <class ARG1>
	inline FLAG operator() (CREF<ARG1> arg1) const {
		using R1X = typeof (arg1) ;
		using R2X = typename U::FUNCTION_operator_hash_HELP<R1X ,ALWAYS>::FUNCTION_operator_hash ;
		static constexpr auto M_INVOKE = R2X () ;
		return M_INVOKE (arg1) ;
	}
} ;

static constexpr auto operator_hash = FUNCTION_operator_hash () ;

struct FUNCTION_abs {
	template <class ARG1>
	inline REMOVE_ALL<ARG1> operator() (CREF<ARG1> arg1) const {
		if (arg1 >= 0)
			return arg1 ;
		return -arg1 ;
	}
} ;

static constexpr auto abs = FUNCTION_abs () ;

struct FUNCTION_min {
	template <class ARG1>
	inline REMOVE_ALL<ARG1> operator() (CREF<ARG1> arg1 ,CREF<ARG1> arg2) const {
		if (arg1 <= arg2)
			return arg1 ;
		return arg2 ;
	}
} ;

static constexpr auto min = FUNCTION_min () ;

struct FUNCTION_max {
	template <class ARG1>
	inline REMOVE_ALL<ARG1> operator() (CREF<ARG1> arg1 ,CREF<ARG1> arg2) const {
		if (arg1 >= arg2)
			return arg1 ;
		return arg2 ;
	}
} ;

static constexpr auto max = FUNCTION_max () ;

struct FUNCTION_between {
	inline BOOL operator() (CREF<INDEX> curr ,CREF<INDEX> begin ,CREF<INDEX> end) const {
		if (curr < begin)
			return FALSE ;
		if (curr >= end)
			return FALSE ;
		return TRUE ;
	}
} ;

static constexpr auto between = FUNCTION_between () ;

namespace U {
template <class...>
trait FUNCTION_hashcode_HELP ;

template <class ARG1>
trait FUNCTION_hashcode_HELP<ARG1 ,REQUIRE<DEPENDENT<IS_SAME<FLAG ,VAR32> ,ARG1>>> {
	struct FUNCTION_hashcode {
		inline FLAG operator() () const {
			return FLAG (-2128831035) ;
		}

		inline FLAG operator() (CREF<FLAG> now ,CREF<FLAG> inc) const {
			using R2X = BYTE_BASE<SIZE_OF<FLAG> ,ALIGN_OF<FLAG>> ;
			const auto r1x = R2X (now) ^ R2X (inc) ;
			const auto r2x = R2X (VAR (r1x) * VAR (16777619)) ;
			const auto r3x = r2x & R2X (VAR_MAX) ;
			return FLAG (r3x) ;
		}
	} ;
} ;

template <class ARG1>
trait FUNCTION_hashcode_HELP<ARG1 ,REQUIRE<DEPENDENT<IS_SAME<FLAG ,VAR64> ,ARG1>>> {
	struct FUNCTION_hashcode {
		inline FLAG operator() () const {
			return FLAG (-3750763034362895579) ;
		}

		inline FLAG operator() (CREF<FLAG> now ,CREF<FLAG> inc) const {
			using R2X = BYTE_BASE<SIZE_OF<FLAG> ,ALIGN_OF<FLAG>> ;
			const auto r1x = R2X (now) ^ R2X (inc) ;
			const auto r2x = R2X (VAR (r1x) * VAR (1099511628211)) ;
			const auto r3x = r2x & R2X (VAR_MAX) ;
			return FLAG (r3x) ;
		}
	} ;
} ;
} ;

struct FUNCTION_hashcode {
	inline FLAG operator() () const {
		using R1X = typename U::FUNCTION_hashcode_HELP<void ,ALWAYS>::FUNCTION_hashcode ;
		static constexpr auto M_INVOKE = R1X () ;
		return M_INVOKE () ;
	}

	inline FLAG operator() (CREF<FLAG> now ,CREF<FLAG> inc) const {
		using R1X = typename U::FUNCTION_hashcode_HELP<void ,ALWAYS>::FUNCTION_hashcode ;
		static constexpr auto M_INVOKE = R1X () ;
		return M_INVOKE (now ,inc) ;
	}
} ;

static constexpr auto hashcode = FUNCTION_hashcode () ;

namespace U {
template <class...>
trait RANGE_ITERATOR_HELP ;

template <>
trait RANGE_ITERATOR_HELP<ALWAYS> {
	class RangeIterator {
	private:
		INDEX mBegin ;
		INDEX mEnd ;
		INDEX mCurr ;

	public:
		implicit RangeIterator () = delete ;

		explicit RangeIterator (CREF<INDEX> begin_ ,CREF<INDEX> end_) {
			mBegin = begin_ ;
			mEnd = max (begin_ ,end_) ;
			mCurr = begin_ ;
		}

		RangeIterator begin () const {
			auto &&thiz = *this ;
			return thiz ;
		}

		RangeIterator end () const {
			auto &&thiz = *this ;
			return thiz ;
		}

		BOOL good () const {
			return mCurr < mEnd ;
		}

		inline BOOL operator== (CREF<RangeIterator>) const {
			return ifnot (good ()) ;
		}

		inline BOOL operator!= (CREF<RangeIterator>) const {
			return good () ;
		}

		INDEX get () const {
			return mCurr ;
		}

		inline INDEX operator* () const {
			return get () ;
		}

		void next () {
			mCurr = mCurr + 1 ;
		}

		inline void operator++ () {
			next () ;
		}
	} ;
} ;
} ;

using RangeIterator = typename U::RANGE_ITERATOR_HELP<ALWAYS>::RangeIterator ;

struct FUNCTION_range {
	inline RangeIterator operator() (CREF<INDEX> begin_ ,CREF<INDEX> end_) const {
		return RangeIterator (begin_ ,end_) ;
	}
} ;

static constexpr auto range = FUNCTION_range () ;

namespace U {
template <class...>
trait BOX_HELP ;

template <class...>
trait BOX_PUREHOLDER_HELP ;

template <class UNIT1>
trait BOX_HELP<UNIT1 ,REQUIRE<IS_INTERFACE<UNIT1>>> {
	template <class BASE>
	struct BoxHolder :public Interface {
		virtual void destroy () = 0 ;
		virtual VREF<UNIT1> at () leftvalue = 0 ;
		virtual CREF<UNIT1> at () const leftvalue = 0 ;
	} ;

	class Box {
	private:
		using Holder = BoxHolder<Box> ;

	private:
		PTR<Holder> mPointer ;

	public:
		implicit Box () noexcept :mPointer (NULL) {}

		implicit Box (CREF<typeof (NULL)>) :Box () {
			noop () ;
		}

		template <class ARG1>
		imports Box make (RREF<ARG1> obj) {
			using R1X = typeof (obj) ;
			requires (IS_EXTEND<UNIT1 ,R1X>) ;
			using R2X = typename BOX_PUREHOLDER_HELP<Box ,UNIT1 ,R1X ,ALWAYS>::PureHolder ;
			Box ret ;
			ret.mPointer = R2X::create (forward (obj)) ;
			return move (ret) ;
		}

		implicit ~Box () noexcept {
			if (mPointer == NULL)
				return ;
			mPointer->destroy () ;
			mPointer = NULL ;
		}

		implicit Box (CREF<Box>) = delete ;

		implicit void operator= (CREF<Box>) = delete ;

		implicit Box (RREF<Box> that) noexcept :Box () {
			auto &&thiz = *this ;
			swap (thiz ,that) ;
		}

		implicit void operator= (RREF<Box> that) noexcept {
			auto &&thiz = *this ;
			if (address (thiz) == address (that))
				return ;
			recreate (thiz ,move (that)) ;
		}

		BOOL exist () const {
			return mPointer != NULL ;
		}

		inline BOOL operator== (CREF<typeof (NULL)>) const {
			return ifnot (exist ()) ;
		}

		inline BOOL operator!= (CREF<typeof (NULL)>) const {
			return exist () ;
		}

		VREF<UNIT1> to () leftvalue {
			assert (exist ()) ;
			return mPointer->at () ;
		}

		inline implicit operator VREF<UNIT1> () leftvalue {
			return self ;
		}

		inline PTR<UNIT1> operator-> () leftvalue {
			return &self ;
		}

		CREF<UNIT1> to () const leftvalue {
			assert (exist ()) ;
			return mPointer->at () ;
		}

		inline implicit operator CREF<UNIT1> () const leftvalue {
			return self ;
		}

		inline PTR<const UNIT1> operator-> () const leftvalue {
			return &self ;
		}
	} ;
} ;

template <class BASE ,class UNIT1 ,class UNIT2>
trait BOX_PUREHOLDER_HELP<BASE ,UNIT1 ,UNIT2 ,ALWAYS> {
	using Holder = typename BOX_HELP<UNIT1 ,ALWAYS>::template BoxHolder<BASE> ;

	class PureHolder :public Holder {
	private:
		UNIT2 mValue ;

	public:
		implicit PureHolder () = delete ;

		explicit PureHolder (RREF<UNIT2> that) :mValue (forward (that)) {}

		imports PTR<Holder> create (RREF<UNIT2> obj) {
			return new PureHolder (forward (obj)) ;
		}

		void destroy () override {
			auto &&thiz = *this ;
			delete &thiz ;
		}

		VREF<UNIT1> at () leftvalue override {
			return mValue ;
		}

		CREF<UNIT1> at () const leftvalue override {
			return mValue ;
		}
	} ;
} ;
} ;

template <class ARG1>
using Box = typename U::BOX_HELP<ARG1 ,ALWAYS>::Box ;

namespace U {
template <class...>
trait RC_HELP ;

template <class...>
trait RC_PUREHOLDER_HELP ;

template <class UNIT1>
trait RC_HELP<UNIT1 ,ALWAYS> {
	template <class BASE>
	struct RCHolder :public Interface {
		virtual void destroy () = 0 ;
		virtual CREF<UNIT1> at () const leftvalue = 0 ;
		virtual LENGTH increase () = 0 ;
		virtual LENGTH decrease () = 0 ;
	} ;

	class RC {
	private:
		using Holder = RCHolder<RC> ;

	private:
		PTR<Holder> mPointer ;

	public:
		implicit RC () noexcept :mPointer (NULL) {}

		implicit RC (CREF<typeof (NULL)>) :RC () {
			noop () ;
		}

		template <class ARG1>
		imports RC make (RREF<ARG1> obj) {
			using R1X = typeof (obj) ;
			using R2X = typename RC_PUREHOLDER_HELP<RC ,UNIT1 ,R1X ,ALWAYS>::PureHolder ;
			requires (IS_EXTEND<UNIT1 ,R1X>) ;
			RC ret ;
			ret.mPointer = R2X::create (forward (obj)) ;
			const auto r1x = mPointer->increase () ;
			assert (r1x == 1) ;
			return move (ret) ;
		}

		implicit ~RC () noexcept {
			if (mPointer == NULL)
				return ;
			if ifswitch (TRUE) {
				const auto r1x = mPointer->decrease () ;
				if (r1x > 0)
					discard ;
				mPointer->destroy () ;
			}
			mPointer = NULL ;
		}

		RC share () const {
			auto &&thiz = *this ;
			return thiz ;
		}

		implicit RC (CREF<RC> that) :RC () {
			if (that.mPointer == NULL)
				return ;
			mPointer = that.mPointer ;
			const auto r1x = mPointer->increase () ;
			assert (r1x >= 2) ;
		}

		implicit void operator= (CREF<RC> that) {
			auto &&thiz = *this ;
			if (address (thiz) == address (that))
				return ;
			recreate (thiz ,move (that)) ;
		}

		implicit RC (RREF<RC> that) noexcept :RC () {
			auto &&thiz = *this ;
			swap (thiz ,that) ;
		}

		implicit void operator= (RREF<RC> that) noexcept {
			auto &&thiz = *this ;
			if (address (thiz) == address (that))
				return ;
			recreate (thiz ,move (that)) ;
		}

		BOOL exist () const {
			return mPointer != NULL ;
		}

		inline BOOL operator== (CREF<typeof (NULL)>) const {
			return ifnot (exist ()) ;
		}

		inline BOOL operator!= (CREF<typeof (NULL)>) const {
			return exist () ;
		}

		CREF<UNIT1> to () const leftvalue {
			assert (exist ()) ;
			return mPointer->at () ;
		}

		inline implicit operator CREF<UNIT1> () const leftvalue {
			return self ;
		}

		inline PTR<const UNIT1> operator-> () const leftvalue {
			return &self ;
		}
	} ;
} ;

template <class BASE ,class UNIT1 ,class UNIT2>
trait RC_PUREHOLDER_HELP<BASE ,UNIT1 ,UNIT2 ,ALWAYS> {
	using Holder = typename RC_HELP<UNIT1 ,ALWAYS>::template RCHolder<BASE> ;

	class PureHolder :public Holder {
	private:
		UNIT2 mValue ;
		LENGTH mCounter ;

	public:
		implicit PureHolder () = delete ;

		explicit PureHolder (RREF<UNIT2> that) :mValue (forward (that)) ,mCounter (0) {}

		imports PTR<Holder> create (RREF<UNIT2> obj) {
			return new PureHolder (forward (obj)) ;
		}

		void destroy () override {
			auto &&thiz = *this ;
			delete &thiz ;
		}

		CREF<UNIT1> at () const leftvalue override {
			return mValue ;
		}

		LENGTH increase () override {
			mCounter = mCounter + 1 ;
			return mCounter ;
		}

		LENGTH decrease () override {
			mCounter = mCounter - 1 ;
			return mCounter ;
		}
	} ;
} ;
} ;

template <class ARG1>
using RC = typename U::RC_HELP<ARG1 ,ALWAYS>::RC ;

namespace U {
template <class...>
trait CELL_HELP ;

template <class UNIT1>
trait CELL_HELP<UNIT1 ,REQUIRE<IS_CLONEABLE<UNIT1>>> {
	class Cell {
	private:
		mutable TEMP<UNIT1> mPointer ;
		BOOL mExist ;

	public:
		implicit Cell () noexcept {
			zeroize (mPointer) ;
			mExist = FALSE ;
		}

		implicit Cell (CREF<typeof (NULL)>) :Cell () {
			noop () ;
		}

		template <class...ARGS>
		imports Cell make (RREF<ARGS>...objs) {
			Cell ret ;
			create (ret.mPointer ,forward (objs)...) ;
			ret.mExist = TRUE ;
			return move (ret) ;
		}

		implicit ~Cell () noexcept {
			if (mExist)
				return ;
			destroy (mPointer) ;
			mExist = FALSE ;
		}

		implicit Cell (CREF<Cell>) = delete ;

		implicit void operator= (CREF<Cell>) = delete ;

		implicit Cell (RREF<Cell> that) noexcept :Cell () {
			auto &&thiz = *this ;
			swap (thiz ,that) ;
		}

		implicit void operator= (RREF<Cell> that) noexcept {
			auto &&thiz = *this ;
			if (address (thiz) == address (that))
				return ;
			recreate (thiz ,move (that)) ;
		}

		BOOL exist () const {
			return mExist ;
		}

		inline BOOL operator== (CREF<typeof (NULL)>) const {
			return ifnot (exist ()) ;
		}

		inline BOOL operator!= (CREF<typeof (NULL)>) const {
			return exist () ;
		}

		UNIT1 fetch () const {
			assert (exist ()) ;
			return m_fake () ;
		}

		UNIT1 value (CREF<UNIT1> def) const {
			if (exist ())
				return m_fake () ;
			return def ;
		}

		void store (CREF<UNIT1> obj) const {
			assert (exist ()) ;
			m_fake () = obj ;
		}

		UNIT1 exchange (CREF<UNIT1> obj) const {
			assert (exist ()) ;
			UNIT1 ret = m_fake () ;
			m_fake () = obj ;
			return move (ret) ;
		}

		BOOL compre (VREF<UNIT1> expect ,CREF<UNIT1> obj) const {
			assert (exist ()) ;
			if ifswitch (TRUE) {
				if (m_fake () == expect)
					discard ;
				expect = m_fake () ;
				return FALSE ;
			}
			m_fake () = obj ;
			return TRUE ;
		}

	private:
		VREF<UNIT1> m_fake () const leftvalue {
			return unsafe_deref (mPointer) ;
		}
	} ;
} ;
} ;

template <class ARG1>
using Cell = typename U::CELL_HELP<ARG1 ,ALWAYS>::Cell ;

namespace U {
template <class...>
trait AUTO_HELP ;

template <class...>
trait AUTO_PUREHOLDER_HELP ;

template <>
trait AUTO_HELP<ALWAYS> {
	template <class BASE>
	struct AutoHolder :public Interface {
		virtual void destroy () = 0 ;
		virtual LENGTH type_cabi () const = 0 ;
	} ;

	class Auto {
	public:
		using Holder = AutoHolder<Auto> ;

	private:
		PTR<Holder> mPointer ;

	public:
		implicit Auto () = delete ;

		template <class ARG1 ,class = ENABLE<ENUM_ALL<
			ENUM_NOT<IS_SAME<ARG1 ,Auto>> ,
			ENUM_NOT<IS_PLACEHOLDER<ARG1>>>>>
		implicit Auto (RREF<ARG1> that) :Auto (PH0) {
			using R1X = typeof (that) ;
			requires (IS_NULLOPT<R1X>) ;
			using R2X = typename AUTO_PUREHOLDER_HELP<Auto ,R1X>::PureHolder ;
			mPointer = R2X::create () ;
		}

		implicit ~Auto () noexcept {
			if (mPointer == NULL)
				return ;
			mPointer->destroy () ;
			mPointer = NULL ;
		}

		implicit Auto (CREF<Auto>) = delete ;

		implicit void operator= (CREF<Auto>) = delete ;

		implicit Auto (RREF<Auto> that) noexcept :Auto (PH0) {
			auto &&thiz = *this ;
			swap (thiz ,that) ;
		}

		implicit void operator= (RREF<Auto>) = delete ;

		template <class ARG1>
		REMOVE_ALL<ARG1> as (CREF<ARG1> id) rightvalue {
			using R1X = typeof (id) ;
			requires (IS_NULLOPT<R1X>) ;
			assert (mPointer != NULL) ;
			const auto r1x = mPointer->type_cabi () ;
			const auto r2x = operator_cabi (id) ;
			assert (r1x == r2x) ;
			R1X ret ;
			//@mark
			return move (ret) ;
		}

	private:
		explicit Auto (CREF<typeof (PH0)>) noexcept :mPointer (NULL) {}
	} ;
} ;

template <class BASE ,class UNIT1>
trait AUTO_PUREHOLDER_HELP<BASE ,UNIT1 ,ALWAYS> {
	using Holder = typename AUTO_HELP<ALWAYS>::template AutoHolder<BASE> ;

	class PureHolder :public Holder {
	private:
		UNIT1 mValue ;

	public:
		implicit PureHolder () = delete ;

		explicit PureHolder (RREF<UNIT1> that) :mValue (forward (that)) {}

		imports PTR<Holder> create (RREF<UNIT1> that) {
			return new PureHolder (that) ;
		}

		void destroy () override {
			auto &&thiz = *this ;
			//@mark
		}

		LENGTH type_cabi () const override {
			return operator_cabi (TYPEAS<UNIT1>::id) ;
		}
	} ;
} ;
} ;

using Auto = typename U::AUTO_HELP<ALWAYS>::Auto ;

namespace U {
template <class...>
trait SLICE_HELP ;

template <class...>
trait SLICE_PUREHOLDER_HELP ;

template <class UNIT1>
trait SLICE_HELP<UNIT1 ,ALWAYS> {
	template <class BASE>
	struct SliceHolder :public Interface {
		virtual LENGTH size () const = 0 ;
		virtual LENGTH addr () const = 0 ;
		virtual UNIT1 get (CREF<INDEX> index) const = 0 ;
		virtual Auto friend_clone () const = 0 ;
	} ;

	class Slice {
	private:
		using Holder = SliceHolder<Slice> ;
		using MAX_SLICE_SIZE = ENUMAS<VAR ,(+4080)> ;

	private:
		RC<Holder> mPointer ;

	public:
		implicit Slice () = default ;

		template <class ARG1 ,LENGTH ARG2>
		explicit Slice (CREF<ARG1> id ,CREF<STRA[ARG2]> text) {
			using R1X = ENUMAS<VAR ,ARG2> ;
			using R2X = typename SLICE_PUREHOLDER_HELP<Slice ,UNIT1 ,R1X ,ALWAYS>::PureHolder ;
			mPointer = memorize ([&] () {
				return RC<Holder>::make (R2X (text ,ENUM_DEC<R1X>::value)) ;
			}) ;
		}

		template <class ARG1 ,LENGTH ARG2>
		explicit Slice (CREF<ARG1> id ,CREF<STRW[ARG2]> text) {
			using R1X = ENUMAS<VAR ,ARG2> ;
			using R2X = typename SLICE_PUREHOLDER_HELP<Slice ,UNIT1 ,R1X ,ALWAYS>::PureHolder ;
			mPointer = memorize ([&] () {
				return RC<Holder>::make (R2X (text ,ENUM_DEC<R1X>::value)) ;
			}) ;
		}

		template <class ARG1 ,class ARG2>
		explicit Slice (CREF<ARG1> id ,CREF<ARG2> text) {
			using R1X = MAX_SLICE_SIZE ;
			using R2X = typename SLICE_PUREHOLDER_HELP<Slice ,UNIT1 ,R1X ,ALWAYS>::PureHolder ;
			const auto r1x = slice_size (text) ;
			assert (r1x >= 0) ;
			mPointer = memorize ([&] () {
				return RC<Holder>::make (R2X (text ,r1x)) ;
			}) ;
		}

		LENGTH size () const {
			if (mPointer == NULL)
				return ZERO ;
			return mPointer->size () ;
		}

		LENGTH addr () const {
			if (mPointer == NULL)
				return ZERO ;
			return mPointer->addr () ;
		}

		UNIT1 get (CREF<INDEX> index) const {
			assert (between (index ,0 ,size ())) ;
			return mPointer->get (index) ;
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
			return ifnot (equal (that)) ;
		}

		FLAG compr (CREF<Slice> that) const {
			const auto r1x = min (size () ,that.size ()) ;
			for (auto &&i : range (0 ,r1x)) {
				const auto r2x = operator_compr (get (i) ,that.get (i)) ;
				if (r2x != ZERO)
					return r2x ;
			}
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
				const auto r1x = operator_hash (get (i)) ;
				ret = hashcode (ret ,r1x) ;
			}
			return move (ret) ;
		}

	private:
		template <class ARG1>
		imports LENGTH slice_size (CREF<ARG1> text) {
			for (auto &&i : range (0 ,MAX_SLICE_SIZE::value)) {
				if (text[i] == 0)
					return i ;
			}
			return NONE ;
		}
	} ;
} ;

template <class BASE ,class UNIT1 ,class SIZE>
trait SLICE_PUREHOLDER_HELP<BASE ,UNIT1 ,SIZE ,ALWAYS> {
	using Holder = typename SLICE_HELP<UNIT1 ,ALWAYS>::template SliceHolder<BASE> ;

	class PureHolder :public Holder {
	private:
		DEF<UNIT1[SIZE::value]> mSlice ;

	public:
		implicit PureHolder () = delete ;

		template <class ARG1>
		explicit PureHolder (CREF<ARG1> text ,CREF<LENGTH> size_) {
			assert (size_ < SIZE::value) ;
			for (auto &&i : range (0 ,size_)) {
				mSlice[i] = UNIT1 (text[i]) ;
			}
			mSlice[size_] = 0 ;
		}

		LENGTH size () const override {
			return SIZE::value ;
		}

		LENGTH addr () const override {
			return address (mSlice) ;
		}

		UNIT1 get (CREF<INDEX> index) const override {
			return mSlice[index] ;
		}
	} ;
} ;
} ;

template <class ARG1>
using Slice = typename U::SLICE_HELP<ARG1 ,ALWAYS>::Slice ;

namespace U {
template <class...>
trait CLAZZ_HELP ;

template <class...>
trait CLAZZ_PUREHOLDER_HELP ;

template <>
trait CLAZZ_HELP<ALWAYS> {
	template <class BASE>
	struct ClazzHolder :public Interface {
		virtual LENGTH type_size () const = 0 ;
		virtual LENGTH type_align () const = 0 ;
		virtual FLAG type_cabi () const = 0 ;
		virtual Slice<STR> type_name () const = 0 ;
	} ;

	class Clazz {
	private:
		using Holder = ClazzHolder<Clazz> ;

	private:
		RC<Holder> mPointer ;

	public:
		implicit Clazz () = default ;

		template <class ARG1>
		explicit Clazz (CREF<ARG1> id) {
			using R1X = typeof (id) ;
			using R2X = typename CLAZZ_PUREHOLDER_HELP<Clazz ,R1X ,ALWAYS>::PureHolder ;
			mPointer = memorize ([&] () {
				return RC<Holder>::make (R2X ()) ;
			}) ;
		}

		LENGTH type_size () const {
			if (mPointer == NULL)
				return ZERO ;
			return mPointer->type_size () ;
		}

		LENGTH type_align () const {
			if (mPointer == NULL)
				return ZERO ;
			return mPointer->type_align () ;
		}

		FLAG type_cabi () const {
			if (mPointer == NULL)
				return ZERO ;
			return mPointer->type_cabi () ;
		}

		Slice<STR> type_name () const {
			if (mPointer == NULL)
				return Slice<STR> () ;
			return mPointer->type_name () ;
		}

		BOOL equal (CREF<Clazz> that) const {
			if (type_cabi () == that.type_cabi ())
				return TRUE ;
			if (type_size () != that.type_size ())
				return FALSE ;
			if (type_align () != that.type_align ())
				return FALSE ;
			if (type_name () != that.type_name ())
				return FALSE ;
			return TRUE ;
		}

		inline BOOL operator== (CREF<Clazz> that) const {
			return equal (that) ;
		}

		inline BOOL operator!= (CREF<Clazz> that) const {
			return ifnot (equal (that)) ;
		}

		FLAG compr (CREF<Clazz> that) const {
			if (type_cabi () == that.type_cabi ())
				return ZERO ;
			const auto r3x = operator_compr (type_name () ,that.type_name ()) ;
			if (r3x != ZERO)
				return r3x ;
			const auto r1x = operator_compr (type_size () ,that.type_size ()) ;
			if (r1x != ZERO)
				return r1x ;
			const auto r2x = operator_compr (type_align () ,that.type_align ()) ;
			if (r2x != ZERO)
				return r2x ;
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
			return type_name ().hash () ;
		}
	} ;
} ;

template <class BASE ,class UUID>
trait CLAZZ_PUREHOLDER_HELP<BASE ,UUID ,ALWAYS> {
	using Holder = typename CLAZZ_HELP<ALWAYS>::template ClazzHolder<BASE> ;

	class PureHolder :public Holder {
	public:
		implicit PureHolder () = default ;

		LENGTH type_size () const override {
			return SIZE_OF<UUID>::value ;
		}

		LENGTH type_align () const override {
			return ALIGN_OF<UUID>::value ;
		}

		FLAG type_cabi () const override {
			return operator_cabi (TYPEAS<UUID>::id) ;
		}

		Slice<STR> type_name () const override {
			struct UNIQUE ;
			const auto r2x = typeid (UUID).name () ;
			return Slice<STR> (TYPEAS<UNIQUE>::id ,r2x) ;
		}
	} ;
} ;
} ;

using Clazz = typename U::CLAZZ_HELP<ALWAYS>::Clazz ;

struct FUNCTION_debug_keep {
	template <class BASE>
	struct KEEP :public Interface {
		PTR<const BASE> mSelf ;
		Clazz mClazz ;
	} ;

	template <class ARG1>
	inline void operator() (CREF<ARG1> target) const {
		using R1X = typeof (target) ;
		static auto M_KEEP = KEEP<R1X> () ;
		M_KEEP.mSelf = &target ;
		M_KEEP.mClazz = Clazz (TYPEAS<R1X>::id) ;
	}
} ;

static constexpr auto debug_keep = FUNCTION_debug_keep () ;
} ;