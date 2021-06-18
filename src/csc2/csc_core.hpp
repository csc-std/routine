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
struct VAR_HELP ;

template <class ARG1>
struct VAR_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_CONFIG_VAR32 ,ARG1>>> {
	using VAR = VAR32 ;

	static constexpr auto VAR_MAX = VAR32_MAX ;
	static constexpr auto VAR_MIN = VAR32_MIN ;
} ;

template <class ARG1>
struct VAR_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_CONFIG_VAR64 ,ARG1>>> {
	using VAR = VAR64 ;

	static constexpr auto VAR_MAX = VAR64_MAX ;
	static constexpr auto VAR_MIN = VAR64_MIN ;
} ;
} ;

using VAR = typename U::VAR_HELP<void ,void>::VAR ;

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
struct STR_HELP ;

template <class ARG1>
struct STR_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_CONFIG_STRA ,ARG1>>> {
	using STR = STRA ;
} ;

template <class ARG1>
struct STR_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_CONFIG_STRW ,ARG1>>> {
	using STR = STRW ;
} ;
} ;

using STR = typename U::STR_HELP<void ,void>::STR ;

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
using CREF = const ARG1 & ;

template <class ARG1>
using VREF = ARG1 & ;

template <class ARG1>
using RREF = ARG1 && ;

template <class ARG1>
using SIZE_OF = ENUMAS<VAR ,sizeof (ARG1)> ;

template <class ARG1>
using ALIGN_OF = ENUMAS<VAR ,alignof (ARG1)> ;

namespace U {
template <class...>
struct COUNT_OF_HELP ;

template <class...ARGS1>
struct COUNT_OF_HELP<TYPEAS<ARGS1...> ,void> {
	using RET = ENUMAS<VAR ,sizeof... (ARGS1)> ;
} ;
} ;

template <class ARG1>
using COUNT_OF = typename U::COUNT_OF_HELP<ARG1 ,void>::RET ;

namespace U {
template <class...>
struct IS_ENUM_HELP ;

template <class ARG1>
struct IS_ENUM_HELP<ARG1 ,void> {
	using RET = ENUM_FALSE ;
} ;

template <class ARG1 ,ARG1 ARG2>
struct IS_ENUM_HELP<ENUMAS<ARG1 ,ARG2> ,void> {
	using RET = ENUM_TRUE ;
} ;
} ;

template <class ARG1>
using IS_ENUM = typename U::IS_ENUM_HELP<ARG1 ,void>::RET ;

namespace U {
template <class...>
struct ENUM_TYPE_HELP ;

template <class ARG1 ,ARG1 ARG2>
struct ENUM_TYPE_HELP<ENUMAS<ARG1 ,ARG2> ,void> {
	using RET = ARG1 ;
} ;
} ;

template <class ARG1>
using ENUM_TYPE = typename U::ENUM_TYPE_HELP<ARG1 ,void>::RET ;

namespace U {
template <class...>
struct IS_TYPE_HELP ;

template <class ARG1>
struct IS_TYPE_HELP<ARG1 ,void> {
	using RET = ENUM_FALSE ;
} ;

template <class...ARGS1>
struct IS_TYPE_HELP<TYPEAS<ARGS1...> ,void> {
	using RET = ENUM_TRUE ;
} ;
} ;

template <class ARG1>
using IS_TYPE = typename U::IS_TYPE_HELP<ARG1 ,void>::RET ;

namespace U {
template <class...>
struct IS_SAME_HELP ;

template <class ARG1 ,class ARG2>
struct IS_SAME_HELP<ARG1 ,ARG2 ,void> {
	using RET = ENUM_FALSE ;
} ;

template <class ARG1>
struct IS_SAME_HELP<ARG1 ,ARG1 ,void> {
	using RET = ENUM_TRUE ;
} ;
} ;

template <class ARG1 ,class ARG2>
using IS_SAME = typename U::IS_SAME_HELP<ARG1 ,ARG2 ,void>::RET ;

using ENUM_ZERO = ENUMAS<VAR ,ZERO> ;
using ENUM_IDEN = ENUMAS<VAR ,IDEN> ;
using ENUM_NONE = ENUMAS<VAR ,NONE> ;
using ENUM_USED = ENUMAS<VAR ,USED> ;

namespace U {
template <class...>
struct ENABLE_HELP ;

template <class ARG1 ,class ARG2>
struct ENABLE_HELP<ARG1 ,ARG2 ,REQUIRE<ARG1>> {
	using RET = ARG2 ;
} ;
} ;

template <class COND ,class YES = void>
using ENABLE = typename U::ENABLE_HELP<COND ,YES ,void>::RET ;

namespace U {
template <class...>
struct CONDITIONAL_HELP ;

template <class ARG1 ,class ARG2 ,class ARG3>
struct CONDITIONAL_HELP<ARG1 ,ARG2 ,ARG3 ,REQUIRE<ARG1>> {
	using RET = ARG2 ;
} ;

template <class ARG1 ,class ARG2 ,class ARG3>
struct CONDITIONAL_HELP<ARG1 ,ARG2 ,ARG3 ,REQUIRE<ENUM_NOT<ARG1>>> {
	using RET = ARG3 ;
} ;
} ;

template <class COND ,class YES ,class NO>
using CONDITIONAL = typename U::CONDITIONAL_HELP<COND ,YES ,NO ,void>::RET ;

template <class ARG1>
using ENUM_CHECK = ENABLE<IS_ENUM<ARG1> ,ARG1> ;

template <class ARG1 ,class ARG2>
using ENUM_EQUAL = ENUMAS<BOOL ,(ENUM_CHECK<ARG1>::value == ENUM_CHECK<ARG2>::value)> ;

template <class ARG1 ,class ARG2>
using ENUM_NOT_EQUAL = ENUM_NOT<ENUM_EQUAL<ARG1 ,ARG2>> ;

namespace U {
template <class...>
struct ENUM_COMPR_HELP ;

template <>
struct ENUM_COMPR_HELP<ENUM_TRUE ,ENUM_FALSE ,void> {
	using RET = ENUM_NONE ;
} ;

template <>
struct ENUM_COMPR_HELP<ENUM_FALSE ,ENUM_TRUE ,void> {
	using RET = ENUM_IDEN ;
} ;

template <>
struct ENUM_COMPR_HELP<ENUM_FALSE ,ENUM_FALSE ,void> {
	using RET = ENUM_ZERO ;
} ;
} ;

template <class ARG1 ,class ARG2>
using ENUM_COMPR = typename U::ENUM_COMPR_HELP<
	ENUMAS<BOOL ,(ENUM_CHECK<ARG1>::value < ENUM_CHECK<ARG2>::value)> ,
	ENUMAS<BOOL ,(ENUM_CHECK<ARG2>::value < ENUM_CHECK<ARG1>::value)> ,
	void>::RET ;

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

template <class ARG1>
using TYPE_CHECK = ENABLE<IS_TYPE<ARG1> ,ARG1> ;

namespace U {
template <class...>
struct TYPE_FIRST_HELP ;

template <class ARG1 ,class...ARGS>
struct TYPE_FIRST_HELP<TYPEAS<ARG1 ,ARGS...> ,void> {
	using ONE = ARG1 ;
	using REST = TYPEAS<ARGS...> ;
} ;
} ;

template <class ARG1>
using TYPE_FIRST_ONE = typename U::TYPE_FIRST_HELP<ARG1 ,void>::ONE ;

template <class ARG1>
using TYPE_FIRST_REST = typename U::TYPE_FIRST_HELP<ARG1 ,void>::REST ;

namespace U {
template <class...>
struct TYPE_SECOND_HELP ;

template <class ARG1 ,class ARG2 ,class...ARGS>
struct TYPE_SECOND_HELP<TYPEAS<ARG1 ,ARG2 ,ARGS...> ,void> {
	using ONE = ARG2 ;
	using REST = TYPEAS<ARGS...> ;
} ;
} ;

template <class ARG1>
using TYPE_SECOND_ONE = typename U::TYPE_SECOND_HELP<ARG1 ,void>::ONE ;

template <class ARG1>
using TYPE_SECOND_REST = typename U::TYPE_SECOND_HELP<ARG1 ,void>::REST ;

template <class ARG1>
using TYPE_UNWIND = ENABLE<ENUM_EQ_IDEN<COUNT_OF<ARG1>> ,TYPE_FIRST_ONE<ARG1>> ;

namespace U {
template <class...>
struct TYPE_CAT_HELP ;

template <class...ARGS1 ,class...ARGS2>
struct TYPE_CAT_HELP<TYPEAS<ARGS1...> ,TYPEAS<ARGS2...> ,void> {
	using RET = TYPEAS<ARGS1... ,ARGS2...> ;
} ;
} ;

template <class ARG1 ,class ARG2>
using TYPE_CAT = typename U::TYPE_CAT_HELP<ARG1 ,ARG2 ,void>::RET ;

namespace U {
template <class...>
struct TYPE_REPEAT_HELP ;

template <class ARG1 ,class ARG2>
struct TYPE_REPEAT_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_EQ_ZERO<ARG2>>> {
	using RET = TYPEAS<> ;
} ;

template <class ARG1 ,class ARG2>
struct TYPE_REPEAT_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_GT_ZERO<ARG2>>> {
	using R1X = typename TYPE_REPEAT_HELP<ARG1 ,ENUM_DEC<ARG2> ,void>::RET ;
	using RET = TYPE_CAT<R1X ,TYPEAS<ARG1>> ;
} ;
} ;

template <class ITEM ,class SIZE>
using TYPE_REPEAT = typename U::TYPE_REPEAT_HELP<ITEM ,SIZE ,void>::RET ;

namespace U {
template <class...>
struct ENUM_ALL_HELP ;

template <class ARG1>
struct ENUM_ALL_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<COUNT_OF<ARG1>>>> {
	using RET = ENUM_TRUE ;
} ;

template <class ARG1>
struct ENUM_ALL_HELP<ARG1 ,REQUIRE<ENUM_GT_ZERO<COUNT_OF<ARG1>>>> {
	using R1X = ENUM_BOOL<TYPE_FIRST_ONE<ARG1>> ;
	using R3X = typename ENUM_ALL_HELP<TYPE_FIRST_REST<ARG1> ,void>::RET ;
	using RET = CONDITIONAL<R1X ,R3X ,ENUM_FALSE> ;
} ;
} ;

template <class...ARGS>
using ENUM_ALL = typename U::ENUM_ALL_HELP<TYPEAS<ARGS...> ,void>::RET ;

namespace U {
template <class...>
struct ENUM_ANY_HELP ;

template <class ARG1>
struct ENUM_ANY_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<COUNT_OF<ARG1>>>> {
	using RET = ENUM_FALSE ;
} ;

template <class ARG1>
struct ENUM_ANY_HELP<ARG1 ,REQUIRE<ENUM_GT_ZERO<COUNT_OF<ARG1>>>> {
	using R1X = ENUM_BOOL<TYPE_FIRST_ONE<ARG1>> ;
	using R3X = typename ENUM_ANY_HELP<TYPE_FIRST_REST<ARG1> ,void>::RET ;
	using RET = CONDITIONAL<R1X ,ENUM_TRUE ,R3X> ;
} ;
} ;

template <class...ARGS>
using ENUM_ANY = typename U::ENUM_ANY_HELP<TYPEAS<ARGS...> ,void>::RET ;

namespace U {
template <class...>
struct PLACEHOLDER_HELP ;

template <class ARG1>
struct PLACEHOLDER_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<ARG1>>> {
	class PlaceHolder {} ;
} ;

template <class ARG1>
struct PLACEHOLDER_HELP<ARG1 ,REQUIRE<ENUM_GT_ZERO<ARG1>>> {
	using BASE = typename PLACEHOLDER_HELP<ENUM_DEC<ARG1> ,void>::PlaceHolder ;

	class PlaceHolder :public BASE {} ;
} ;
} ;

template <class RANK>
using PlaceHolder = typename U::PLACEHOLDER_HELP<RANK ,void>::PlaceHolder ;

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
struct IS_CONSTRUCTIBLE_HELP ;

template <class ARG1 ,class...ARGS2>
struct IS_CONSTRUCTIBLE_HELP<ARG1 ,TYPEAS<ARGS2...> ,void> {
	using RET = ENUMAS<BOOL ,(std::is_constructible<ARG1 ,ARGS2...>::value)> ;
} ;
} ;

template <class RETURN ,class PARAMS>
using IS_CONSTRUCTIBLE = typename U::IS_CONSTRUCTIBLE_HELP<RETURN ,PARAMS ,void>::RET ;

template <class FROM ,class TO>
using IS_CONVERTIBLE = IS_CONSTRUCTIBLE<TO ,TYPEAS<FROM>> ;

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
struct REFLECT_FUNCTION_HELP ;

template <class ARG1 ,class...ARGS>
struct REFLECT_FUNCTION_HELP<DEF<ARG1 (ARGS...)> ,void> {
	using R1X = REMOVE_ALL<ARG1> ;
	using R2X = TYPEAS<REMOVE_ALL<ARGS>...> ;
	using RET = TYPEAS<R1X ,R2X> ;
} ;
} ;

template <class ARG1>
using REFLECT_FUNCTION = typename U::REFLECT_FUNCTION_HELP<typeof (ARG1::operator()) ,void>::RET ;

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
struct BYTE_BASE_HELP ;

template <class ARG1 ,class ARG2>
struct BYTE_BASE_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_ALL<
	ENUM_EQUAL<ARG1 ,SIZE_OF<BYTE>> ,
	ENUM_EQUAL<ARG2 ,ALIGN_OF<BYTE>>>>> {
	using RET = BYTE ;
} ;

template <class ARG1 ,class ARG2>
struct BYTE_BASE_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_ALL<
	ENUM_EQUAL<ARG1 ,SIZE_OF<WORD>> ,
	ENUM_EQUAL<ARG2 ,ALIGN_OF<WORD>>>>> {
	using RET = WORD ;
} ;

template <class ARG1 ,class ARG2>
struct BYTE_BASE_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_ALL<
	ENUM_EQUAL<ARG1 ,SIZE_OF<CHAR>> ,
	ENUM_EQUAL<ARG2 ,ALIGN_OF<CHAR>>>>> {
	using RET = CHAR ;
} ;

template <class ARG1 ,class ARG2>
struct BYTE_BASE_HELP<ARG1 ,ARG2 ,REQUIRE<ENUM_ALL<
	ENUM_EQUAL<ARG1 ,SIZE_OF<FEAT>> ,
	ENUM_EQUAL<ARG2 ,ALIGN_OF<FEAT>>>>> {
	using RET = FEAT ;
} ;
} ;

template <class SIZE ,class ALIGN>
using BYTE_BASE = typename U::BYTE_BASE_HELP<SIZE ,ALIGN ,void>::RET ;

namespace U {
template <class...>
struct STORAGE_HELP ;

template <class ARG1 ,class ARG2>
struct STORAGE_HELP<ARG1 ,ARG2 ,void> {
	using R3X = BYTE_BASE<ARG2 ,ARG2> ;
	using R1X = SIZE_OF<R3X> ;
	using R4X = ENUM_DIV<ENUM_ADD<ARG1 ,ENUM_DEC<R1X>> ,R1X> ;

	struct Storage {
		DEF<R3X[ENUM_CHECK<R4X>::value]> mStorage ;
	} ;
} ;
} ;

template <class SIZE ,class ALIGN = ENUM_IDEN>
using Storage = typename U::STORAGE_HELP<SIZE ,ALIGN ,void>::Storage ;

template <class UNIT>
struct TEMP {
	Storage<SIZE_OF<UNIT> ,ALIGN_OF<UNIT>> mUnused ;
} ;

template <class ARG1>
using ENUM_ABS = CONDITIONAL<ENUM_COMPR_GTEQ<ARG1 ,ENUM_ZERO> ,ARG1 ,ENUM_MINUS<ARG1>> ;

template <class ARG1 ,class ARG2>
using ENUM_MIN = CONDITIONAL<ENUM_COMPR_LTEQ<ARG1 ,ARG2> ,ARG1 ,ARG2> ;

template <class ARG1 ,class ARG2>
using ENUM_MAX = CONDITIONAL<ENUM_COMPR_GTEQ<ARG1 ,ARG2> ,ARG1 ,ARG2> ;

template <class CURR ,class BEGIN ,class END>
using ENUM_BETWEEN = ENUM_ALL<ENUM_COMPR_GTEQ<CURR ,BEGIN> ,ENUM_COMPR_LT<CURR ,END>> ;

struct FUNCTION_noop {
	inline void operator() () const {
		//@info: noop
	}
} ;

static constexpr auto noop = FUNCTION_noop () ;

struct FUNCTION_address {
	template <class ARG1>
	inline LENGTH operator() (CREF<ARG1> arg1) const {
		return LENGTH (&reinterpret_cast<CREF<BYTE>> (arg1)) ;
	}
} ;

static constexpr auto address = FUNCTION_address () ;

namespace U {
template <class...>
struct FUNCTION_barrier_HELP ;

template <class ARG1>
struct FUNCTION_barrier_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_MSVC ,ARG1>>> {
	struct FUNCTION_barrier {
		inline void operator() () const {
			noop () ;
		}
	} ;
} ;

template <class ARG1>
struct FUNCTION_barrier_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_GNUC ,ARG1>>> {
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
struct FUNCTION_barrier_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_CLANG ,ARG1>>> {
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
		using R1X = typename U::FUNCTION_barrier_HELP<void ,void>::FUNCTION_barrier ;
		static constexpr auto M_INVOKE = R1X () ;
		return M_INVOKE () ;
	}
} ;

static constexpr auto barrier = FUNCTION_barrier () ;

struct FUNCTION_swap {
	template <class ARG1>
	inline void operator() (VREF<ARG1> arg1 ,VREF<ARG1> arg2) const {
		using R1X = TEMP<REMOVE_CVR<ARG1>> ;
		auto rax = reinterpret_cast<VREF<R1X>> (arg1) ;
		reinterpret_cast<VREF<R1X>> (arg1) = reinterpret_cast<VREF<R1X>> (arg2) ;
		reinterpret_cast<VREF<R1X>> (arg2) = rax ;
		barrier () ;
	}
} ;

static constexpr auto swap = FUNCTION_swap () ;

struct FUNCTION_move {
	template <class ARG1>
	inline RREF<REMOVE_CVR<ARG1>> operator() (RREF<ARG1> arg1) const {
		return static_cast<RREF<REMOVE_CVR<ARG1>>> (arg1) ;
	}
} ;

static constexpr auto move = FUNCTION_move () ;

struct FUNCTION_forward {
	template <class ARG1>
	inline REMOVE_CVR<ARG1> operator() (CREF<ARG1> arg1) const {
		using R1X = REMOVE_CVR<ARG1> ;
		return R1X (arg1) ;
	}

	template <class ARG1>
	inline REMOVE_CVR<ARG1> operator() (RREF<ARG1> arg1) const {
		using R1X = REMOVE_CVR<ARG1> ;
		return R1X (move (arg1)) ;
	}
} ;

static constexpr auto forward = FUNCTION_forward () ;

struct FUNCTION_zeroize {
	template <class ARG1>
	inline void operator() (VREF<ARG1> arg1) const {
		using R1X = TEMP<REMOVE_CVR<ARG1>> ;
		reinterpret_cast<VREF<R1X>> (arg1) = {0} ;
		barrier () ;
	}
} ;

static constexpr auto zeroize = FUNCTION_zeroize () ;

struct FUNCTION_create {
	template <class ARG1 ,class...ARGS>
	inline void operator() (VREF<TEMP<ARG1>> thiz ,RREF<ARGS>...objs) const {
		using R1X = REMOVE_CVR<ARG1> ;
		new (&thiz) R1X (forward (objs)...) ;
	}
} ;

static constexpr auto create = FUNCTION_create () ;

struct FUNCTION_destroy {
	template <class ARG1 ,class...ARGS>
	inline void operator() (VREF<TEMP<ARG1>> thiz) const {
		using R1X = REMOVE_CVR<ARG1> ;
		reinterpret_cast<VREF<R1X>> (thiz).~R1X () ;
	}
} ;

static constexpr auto destroy = FUNCTION_destroy () ;

struct FUNCTION_recreate {
	template <class ARG1>
	inline void operator() (VREF<ARG1> thiz ,CREF<REMOVE_CVR<ARG1>> that) const {
		using R1X = REMOVE_CVR<ARG1> ;
		thiz.~R1X () ;
		new (&thiz) R1X (move (that)) ;
	}

	template <class ARG1>
	inline void operator() (VREF<ARG1> thiz ,RREF<REMOVE_CVR<ARG1>> that) const {
		using R1X = REMOVE_CVR<ARG1> ;
		thiz.~R1X () ;
		new (&thiz) R1X (move (that)) ;
	}
} ;

static constexpr auto recreate = FUNCTION_recreate () ;

namespace U {
template <class...>
struct FUNCTION_debug_assert_HELP ;

template <class ARG1>
struct FUNCTION_debug_assert_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_MSVC ,ARG1>>> {
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
struct FUNCTION_debug_assert_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_GNUC ,ARG1>>> {
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
struct FUNCTION_debug_assert_HELP<ARG1 ,REQUIRE<DEPENDENT<MACRO_COMPILER_CLANG ,ARG1>>> {
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
		using R1X = typename U::FUNCTION_debug_assert_HELP<void ,void>::FUNCTION_debug_assert ;
		static constexpr auto M_INVOKE = R1X () ;
		return M_INVOKE (expr) ;
	}
} ;

static constexpr auto debug_assert = FUNCTION_debug_assert () ;

static constexpr auto unittest_assert = FUNCTION_debug_assert () ;

struct FUNCTION_bad {
	template <class ARG1>
	inline REMOVE_CVR<ARG1> operator() (CREF<ARG1>) const {
		const auto r1x = DEF<REMOVE_CVR<ARG1> (*) ()> (NULL) ;
		assert (FALSE) ;
		return r1x () ;
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

namespace U {
template <class...>
struct CABI_HELP ;

template <class ARG1>
struct CABI_HELP<ARG1 ,void> {
	struct CABI :public Interface {} ;
} ;
} ;

struct FUNCTION_operator_cabi {
	template <class>
	struct CABI :public Interface {} ;

	template <class ARG1>
	inline FLAG operator() (CREF<ARG1> id) const {
		using R1X = typeof (id) ;
		using R2X = typename U::CABI_HELP<R1X ,void>::CABI ;
		requires (ENUM_EQUAL<SIZE_OF<R2X> ,SIZE_OF<FLAG>>) ;
		requires (ENUM_EQUAL<ALIGN_OF<R2X> ,ALIGN_OF<FLAG>>) ;
		R2X tmp ;
		return reinterpret_cast<CREF<FLAG>> (tmp) ;
	}
} ;

static constexpr auto operator_cabi = FUNCTION_operator_cabi () ;

namespace U {
template <class...>
struct FUNCTION_operator_compr_HELP ;

template <class ARG1>
struct FUNCTION_operator_compr_HELP<ARG1 ,REQUIRE<IS_CLASS<ARG1>>> {
	struct FUNCTION_operator_compr {
		template <class ARG1>
		inline FLAG operator() (CREF<ARG1> arg1 ,CREF<ARG1> arg2) const {
			return arg1.compr (arg2) ;
		}
	} ;
} ;

template <class ARG1>
struct FUNCTION_operator_compr_HELP<ARG1 ,REQUIRE<ENUM_NOT<IS_CLASS<ARG1>>>> {
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
		using R2X = REMOVE_CVR<ARG1> ;
		using R1X = typename U::FUNCTION_operator_compr_HELP<R2X ,void>::FUNCTION_operator_compr ;
		static constexpr auto M_INVOKE = R1X () ;
		return M_INVOKE (arg1 ,arg2) ;
	}
} ;

static constexpr auto operator_compr = FUNCTION_operator_compr () ;

namespace U {
template <class...>
struct FUNCTION_operator_hash_HELP ;

template <class ARG1>
struct FUNCTION_operator_hash_HELP<ARG1 ,REQUIRE<IS_CLASS<ARG1>>> {
	struct FUNCTION_operator_hash {
		template <class ARG1>
		inline FLAG operator() (CREF<ARG1> arg1) const {
			return arg1.hash () ;
		}
	} ;
} ;

template <class ARG1>
struct FUNCTION_operator_hash_HELP<ARG1 ,REQUIRE<ENUM_NOT<IS_CLASS<ARG1>>>> {
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
		using R2X = REMOVE_CVR<ARG1> ;
		using R1X = typename U::FUNCTION_operator_hash_HELP<R2X ,void>::FUNCTION_operator_hash ;
		static constexpr auto M_INVOKE = R1X () ;
		return M_INVOKE (arg1) ;
	}
} ;

static constexpr auto operator_hash = FUNCTION_operator_hash () ;

struct FUNCTION_abs {
	template <class ARG1>
	inline REMOVE_CVR<ARG1> operator() (CREF<ARG1> arg1) const {
		if (arg1 >= 0)
			return arg1 ;
		return -arg1 ;
	}
} ;

static constexpr auto abs = FUNCTION_abs () ;

struct FUNCTION_min {
	template <class ARG1>
	inline REMOVE_CVR<ARG1> operator() (CREF<ARG1> arg1 ,CREF<ARG1> arg2) const {
		if (arg1 <= arg2)
			return arg1 ;
		return arg2 ;
	}
} ;

static constexpr auto min = FUNCTION_min () ;

struct FUNCTION_max {
	template <class ARG1>
	inline REMOVE_CVR<ARG1> operator() (CREF<ARG1> arg1 ,CREF<ARG1> arg2) const {
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
struct FUNCTION_hashcode_HELP ;

template <class ARG1>
struct FUNCTION_hashcode_HELP<ARG1 ,REQUIRE<DEPENDENT<IS_SAME<FLAG ,VAR32> ,ARG1>>> {
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
struct FUNCTION_hashcode_HELP<ARG1 ,REQUIRE<DEPENDENT<IS_SAME<FLAG ,VAR64> ,ARG1>>> {
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
		using R1X = typename U::FUNCTION_hashcode_HELP<void ,void>::FUNCTION_hashcode ;
		static constexpr auto M_INVOKE = R1X () ;
		return M_INVOKE () ;
	}

	inline FLAG operator() (CREF<FLAG> now ,CREF<FLAG> inc) const {
		using R1X = typename U::FUNCTION_hashcode_HELP<void ,void>::FUNCTION_hashcode ;
		static constexpr auto M_INVOKE = R1X () ;
		return M_INVOKE (now ,inc) ;
	}
} ;

static constexpr auto hashcode = FUNCTION_hashcode () ;

namespace U {
template <class...>
struct RANGE_ITERATOR_HELP ;

template <>
struct RANGE_ITERATOR_HELP<void ,void> {
	template <class BASE>
	struct RangeIteratorCRTP {
		INDEX mBegin ;
		INDEX mEnd ;
		INDEX mCurr ;
	} ;

	class RangeIterator :private RangeIteratorCRTP<RangeIterator> {
	private:
		using RangeIteratorCRTP<RangeIterator>::mBegin ;
		using RangeIteratorCRTP<RangeIterator>::mEnd ;
		using RangeIteratorCRTP<RangeIterator>::mCurr ;

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

using RangeIterator = typename U::RANGE_ITERATOR_HELP<void ,void>::RangeIterator ;

struct FUNCTION_range {
	inline RangeIterator operator() (CREF<INDEX> begin_ ,CREF<INDEX> end_) const {
		return RangeIterator (begin_ ,end_) ;
	}
} ;

static constexpr auto range = FUNCTION_range () ;

namespace U {
template <class...>
struct AUTO_HELP ;

template <>
struct AUTO_HELP<void ,void> {
	struct AutoHolder ;

	template <class BASE>
	struct AutoCRTP {
		using Holder = DEPENDENT<AutoHolder ,BASE> ;

		PTR<Holder> mPointer ;
	} ;

	struct AutoHolder :public Interface {
		virtual void destroy () = 0 ;
		virtual LENGTH type_cabi () const = 0 ;
		virtual void addr_swap (CREF<LENGTH> addr_) = 0 ;
	} ;

	class Auto :private AutoCRTP<Auto> {
	private:
		using AutoCRTP<Auto>::mPointer ;

	public:
		implicit Auto () noexcept {
			mPointer = NULL ;
		}

		template <class ARG1 ,class = ENABLE<ENUM_NOT<IS_SAME<ARG1 ,Auto>>>>
		explicit Auto (RREF<ARG1> that) {
			using R1X = REMOVE_CVR<ARG1> ;
			requires (IS_CONSTRUCTIBLE<R1X ,TYPEAS<>>) ;
			//@mark
		}

		implicit ~Auto () noexcept {
			if (mPointer == NULL)
				return ;
			mPointer->destroy () ;
			mPointer = NULL ;
		}

		implicit Auto (CREF<Auto>) = delete ;

		implicit void operator= (CREF<Auto>) = delete ;

		implicit Auto (RREF<Auto> that) noexcept :Auto () {
			auto &&thiz = *this ;
			swap (thiz ,that) ;
		}

		implicit void operator= (RREF<Auto>) = delete ;

		template <class ARG1>
		REMOVE_ALL<ARG1> as (CREF<ARG1> id) {
			using R1X = REMOVE_ALL<ARG1> ;
			requires (IS_CONSTRUCTIBLE<R1X ,TYPEAS<>>) ;
			assert (mPointer != NULL) ;
			const auto r1x = mPointer->type_cabi () ;
			const auto r2x = operator_cabi (id) ;
			assert (r1x == r2x) ;
			R1X ret ;
			mPointer->addr_swap (address (ret)) ;
			mPointer->destroy () ;
			mPointer = NULL ;
			return move (ret) ;
		}
	} ;
} ;
} ;

using Auto = typename U::AUTO_HELP<void ,void>::Auto ;

namespace U {
template <class...>
struct BOX_HELP ;

template <class UNIT1>
struct BOX_HELP<UNIT1 ,REQUIRE<IS_INTERFACE<UNIT1>>> {
	struct BoxHolder ;

	template <class BASE>
	struct BoxCRTP {
		using Holder = DEPENDENT<BoxHolder ,BASE> ;

		PTR<Holder> mPointer ;
	} ;

	struct BoxHolder :public Interface {
		virtual void destroy () = 0 ;
		virtual VREF<UNIT1> at () = 0 ;
		virtual CREF<UNIT1> at () const = 0 ;
	} ;

	class Box :private BoxCRTP<Box> {
	private:
		using BoxCRTP<Box>::mPointer ;

	public:
		implicit Box () noexcept {
			mPointer = NULL ;
		}

		implicit Box (CREF<typeof (NULL)>) :Box () {}

		template <class ARG1>
		imports Box make (RREF<ARG1> obj) {
			using R1X = REMOVE_CVR<ARG1> ;
			requires (IS_EXTEND<UNIT1 ,R1X>) ;
			Box ret ;
			//@mark
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

		VREF<UNIT1> to () {
			assert (exist ()) ;
			return mPointer->at () ;
		}

		inline implicit operator VREF<UNIT1> () {
			return self ;
		}

		inline PTR<UNIT1> operator-> () {
			return &self ;
		}

		CREF<UNIT1> to () const {
			assert (exist ()) ;
			return mPointer->at () ;
		}

		inline implicit operator CREF<UNIT1> () const {
			return self ;
		}

		inline PTR<const UNIT1> operator-> () const {
			return &self ;
		}
	} ;
} ;
} ;

template <class ARG1>
using Box = typename U::BOX_HELP<ARG1 ,void>::Box ;

namespace U {
template <class...>
struct RC_HELP ;

template <class UNIT1>
struct RC_HELP<UNIT1 ,void> {
	struct RCHolder ;

	template <class BASE>
	struct RCCRTP {
		using Holder = DEPENDENT<RCHolder ,BASE> ;

		PTR<Holder> mPointer ;
	} ;

	struct RCHolder :public Interface {
		virtual void destroy () = 0 ;
		virtual LENGTH increase () = 0 ;
		virtual LENGTH decrease () = 0 ;
		virtual CREF<UNIT1> at () const = 0 ;
	} ;

	class RC :private RCCRTP<RC> {
	private:
		using RCCRTP<RC>::mPointer ;

	public:
		implicit RC () noexcept {
			mPointer = NULL ;
		}

		implicit RC (CREF<typeof (NULL)>) :RC () {}

		template <class...ARGS>
		imports RC make (RREF<ARGS>...objs) {
			RC ret ;
			//@mark
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

		CREF<UNIT1> to () const {
			assert (exist ()) ;
			return mPointer->at () ;
		}

		inline implicit operator CREF<UNIT1> () const {
			return self ;
		}

		inline PTR<const UNIT1> operator-> () const {
			return &self ;
		}
	} ;
} ;
} ;

template <class ARG1>
using RC = typename U::RC_HELP<ARG1 ,void>::RC ;

namespace U {
template <class...>
struct CELL_HELP ;

template <class UNIT1>
struct CELL_HELP<UNIT1 ,REQUIRE<IS_CLONEABLE<UNIT1>>> {
	template <class BASE>
	struct CellCRTP {
		mutable TEMP<UNIT1> mPointer ;
		BOOL mExist ;
	} ;

	class Cell :private CellCRTP<Cell> {
	private:
		using CellCRTP<Cell>::mPointer ;
		using CellCRTP<Cell>::mExist ;

	public:
		implicit Cell () noexcept {
			zeroize (mPointer) ;
			mExist = FALSE ;
		}

		implicit Cell (CREF<typeof (NULL)>) :Cell () {}

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
		VREF<UNIT1> m_fake () const {
			return reinterpret_cast<VREF<UNIT1>> (mPointer) ;
		}
	} ;
} ;
} ;

template <class ARG1>
using Cell = typename U::CELL_HELP<ARG1 ,void>::Cell ;

namespace U {
template <class...>
struct SLICE_HELP ;

template <class UNIT1>
struct SLICE_HELP<UNIT1 ,void> {
	struct SliceHolder ;
	struct SliceBuilder ;

	template <class BASE>
	struct SliceCRTP {
		using Holder = DEPENDENT<SliceHolder ,BASE> ;
		using SliceBuilder = DEPENDENT<SliceBuilder ,BASE> ;

		Box<Holder> mPointer ;
	} ;

	struct SliceHolder :public Interface {
		virtual LENGTH size () const = 0 ;
		virtual LENGTH addr () const = 0 ;
		virtual UNIT1 get (CREF<INDEX> index) const = 0 ;
		virtual Auto friend_clone () const = 0 ;
	} ;

	struct SliceBuilder {
		imports Box<SliceBuilder> create () ;
	} ;

	class Slice :private SliceCRTP<Slice> {
	private:
		using Holder = typename SliceCRTP<Slice>::Holder ;

	private:
		using SliceCRTP<Slice>::mPointer ;

	public:
		implicit Slice () = default ;

		template <class ARG1 ,LENGTH ARG2>
		explicit Slice (CREF<ARG1> id ,CREF<STRA[ARG2]> text) {
			mPointer = SliceBuilder::create () ;
		}

		template <class ARG1 ,LENGTH ARG2>
		explicit Slice (CREF<ARG1> id ,CREF<STRW[ARG2]> text) {
			mPointer = SliceBuilder::create () ;
		}

		implicit Slice (CREF<Slice> that) {
			if (that.mPointer == NULL)
				return ;
			mPointer = Box<Holder> (that.mPointer->friend_clone ().as (TYPEAS<Box<Holder>>::id)) ;
		}

		implicit void operator= (CREF<Slice> that) {
			auto &&thiz = *this ;
			if (address (thiz) == address (that))
				return ;
			recreate (thiz ,move (that)) ;
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
			} ;
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
			} ;
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
			} ;
			return move (ret) ;
		}
	} ;
} ;
} ;

template <class ARG1>
using Slice = typename U::SLICE_HELP<ARG1 ,void>::Slice ;

namespace U {
template <class...>
struct CLAZZ_HELP ;

template <>
struct CLAZZ_HELP<void ,void> {
	struct ClazzHolder ;

	template <class BASE>
	struct ClazzCRTP {
		using Holder = DEPENDENT<ClazzHolder ,BASE> ;

		Box<Holder> mPointer ;
	} ;

	struct ClazzHolder :public Interface {
		virtual LENGTH type_size () const = 0 ;
		virtual LENGTH type_align () const = 0 ;
		virtual FLAG type_cabi () const = 0 ;
		virtual Slice<STR> type_name () const = 0 ;
		virtual Auto friend_clone () const = 0 ;
	} ;

	class Clazz :private ClazzCRTP<Clazz> {
	private:
		using Holder = typename ClazzCRTP<Clazz>::Holder ;

	private:
		using ClazzCRTP<Clazz>::mPointer ;

	public:
		implicit Clazz () = default ;

		template <class ARG1>
		explicit Clazz (CREF<ARG1> id) {
			//@mark
		}

		implicit Clazz (CREF<Clazz> that) {
			if (that.mPointer == NULL)
				return ;
			mPointer = Box<Holder> (that.mPointer->friend_clone ().as (TYPEAS<Box<Holder>>::id)) ;
		}

		implicit void operator= (CREF<Clazz> that) {
			auto &&thiz = *this ;
			if (address (thiz) == address (that))
				return ;
			recreate (thiz ,move (that)) ;
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
			return type_name () == that.type_name () ;
		}

		inline BOOL operator== (CREF<Clazz> that) const {
			return equal (that) ;
		}

		inline BOOL operator!= (CREF<Clazz> that) const {
			return ifnot (equal (that)) ;
		}

		FLAG compr (CREF<Clazz> that) const {
			return operator_compr (type_name () ,that.type_name ()) ;
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
} ;

using Clazz = typename U::CLAZZ_HELP<void ,void>::Clazz ;

struct FUNCTION_debug_watch {
	template <class ARG1>
	inline BOOL operator() (CREF<ARG1> target) const {
		//@mark
	}
} ;

static constexpr auto debug_watch = FUNCTION_debug_watch () ;
} ;