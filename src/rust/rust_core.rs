module core ;

using BOOL = bool_t ;

static constant TRUE = BOOL (true) ;
static constant FALSE = BOOL (false) ;

using VAR32 = int32_t ;
using VAR64 = int64_t ;

static constant VAR32_MAX = VAR32 (2147483647) ;
static constant VAR32_MIN = -VAR32_MAX - 1 ;
static constant VAR64_MAX = VAR64 (9223372036854775807) ;
static constant VAR64_MIN = -VAR64_MAX - 1 ;

trait VAR_HELP<> {
	require (macro ("config_VAR32")) ;

	using VAR = VAR32 ;

	static constant VAR_MAX = VAR32_MAX ;
	static constant VAR_MIN = VAR32_MIN ;
} ;

trait VAR_HELP<> {
	require (macro ("config_VAR64")) ;

	using VAR = VAR64 ;

	static constant VAR_MAX = VAR64_MAX ;
	static constant VAR_MIN = VAR64_MIN ;
} ;

using VAR = typename VAR_HELP<>::VAR ;

using INDEX = VAR ;
using LENGTH = VAR ;
using FLAG = VAR ;

static constant USED = VAR (-2) ;
static constant NONE = VAR (-1) ;
static constant ZERO = VAR (+0) ;
static constant IDEN = VAR (+1) ;

using SINGLE = float32_t ;
using DOUBLE = float64_t ;

static constant SINGLE_MAX = SINGLE (3.402823466E+38) ;
static constant SINGLE_MIN = SINGLE (1.175494351E-38) ;
static constant SINGLE_EPS = SINGLE (1.192092896E-07) ;
static constant SINGLE_INF = SINGLE (infinity) ;
static constant DOUBLE_MAX = DOUBLE (1.7976931348623158E+308) ;
static constant DOUBLE_MIN = DOUBLE (2.2250738585072014E-308) ;
static constant DOUBLE_EPS = DOUBLE (2.2204460492503131E-016) ;
static constant DOUBLE_INF = DOUBLE (infinity) ;

using BYTE = byte8_t ;
using WORD = byte16_t ;
using CHAR = byte32_t ;
using FEAT = byte64_t ;

using STRA = stra_t ;
using STRU8 = str8_t ;
using STRU16 = str16_t ;
using STRU32 = str32_t ;

trait STR_HELP<> {
	require (macro ("config_STRA")) ;

	using STR = STRA ;
} ;

trait STR_HELP<> {
	require (macro ("config_STRU8")) ;

	using STR = STRU8 ;
} ;

trait STR_HELP<> {
	require (macro ("config_STRU16")) ;

	using STR = STRU16 ;
} ;

trait STR_HELP<> {
	require (macro ("config_STRU32")) ;

	using STR = STRU32 ;
} ;

using STR = typename STR_HELP<>::STR ;

static constant NULL = null ;

using ENUM_USED = enum (-2) ;
using ENUM_NONE = enum (-1) ;
using ENUM_ZERO = enum (+0) ;
using ENUM_IDEN = enum (+1) ;

define SIZEOF<UNIT1> = enum (sizeof (UNIT1)) ;

define ALIGNOF<UNIT1> = enum (alignof (UNIT1)) ;

define COUNTOF<UNIT1> = enum (countof (UNIT1)) ;

define IS_SAME<UNIT1 ,UNIT2> = enum (is_same (UNIT1 ,UNIT2)) ;

trait ENABLE_HELP<ARG1 ,ARG2> {
	require (IS_SAME<ARG1 ,ENUM_IDEN>) ;

	using RET = ARG2 ;
} ;

define ENABLE<COND ,YES> = typename ENABLE_HELP<COND ,YES>::RET ;

trait CONDITIONAL_HELP<ARG1 ,ARG2 ,ARG3> {
	require (IS_SAME<ARG1 ,ENUM_IDEN>) ;

	using RET = ARG2 ;
} ;

trait CONDITIONAL_HELP<ARG1 ,ARG2 ,ARG3> {
	require (IS_SAME<ARG1 ,ENUM_ZERO>) ;

	using RET = ARG3 ;
} ;

define CONDITIONAL<COND ,YES ,NO> = typename CONDITIONAL_HELP<COND ,YES ,NO>::RET ;

define IS_ENUM<UNIT1> = enum (is_enum (UNIT1)) ;
define ENUM_CHECK<UNIT1> = ENABLE<IS_ENUM<UNIT1> ,UNIT1> ;
define ENUM_EQUAL<UNIT1 ,UNIT2> = enum (ENUM_CHECK<UNIT1>::value == ENUM_CHECK<UNIT2>::value) ;
define ENUM_NOT_EQUAL<UNIT1 ,UNIT2> = enum (ENUM_CHECK<UNIT1>::value != ENUM_CHECK<UNIT2>::value) ;
define ENUM_BOOL<UNIT1> = ENUM_NOT_EQUAL<UNIT1 ,ENUM_ZERO> ;
define ENUM_NOT_BOOL<UNIT1> = ENUM_EQUAL<UNIT1 ,ENUM_ZERO> ;
define ENUM_COMPR<UNIT1 ,UNIT2> = enum (ENUM_CHECK<UNIT1>::value <=> ENUM_CHECK<UNIT2>::value) ;
define ENUM_COMPR_LT<UNIT1 ,UNIT2> = enum (ENUM_COMPR<UNIT1 ,UNIT2>::value < ZERO) ;
define ENUM_COMPR_LTEQ<UNIT1 ,UNIT2> = enum (ENUM_COMPR<UNIT1 ,UNIT2>::value <= ZERO) ;
define ENUM_COMPR_GT<UNIT1 ,UNIT2> = enum (ENUM_COMPR<UNIT1 ,UNIT2>::value > ZERO) ;
define ENUM_COMPR_GTEQ<UNIT1 ,UNIT2> = enum (ENUM_COMPR<UNIT1 ,UNIT2>::value >= ZERO) ;
define ENUM_EQ_ZERO<UNIT1> = ENUM_EQUAL<UNIT1 ,ENUM_ZERO> ;
define ENUM_LT_ZERO<UNIT1> = ENUM_COMPR_LT<UNIT1 ,ENUM_ZERO> ;
define ENUM_GT_ZERO<UNIT1> = ENUM_COMPR_GT<UNIT1 ,ENUM_ZERO> ;
define ENUM_EQ_IDEN<UNIT1> = ENUM_EQUAL<UNIT1 ,ENUM_IDEN> ;
define ENUM_LT_IDEN<UNIT1> = ENUM_COMPR_LT<UNIT1 ,ENUM_IDEN> ;
define ENUM_GT_IDEN<UNIT1> = ENUM_COMPR_GT<UNIT1 ,ENUM_IDEN> ;
define ENUM_ADD<UNIT1 ,UNIT2> = enum (ENUM_CHECK<UNIT1>::value + ENUM_CHECK<UNIT2>::value) ;
define ENUM_SUB<UNIT1 ,UNIT2> = enum (ENUM_CHECK<UNIT1>::value - ENUM_CHECK<UNIT2>::value) ;
define ENUM_MUL<UNIT1 ,UNIT2> = enum (ENUM_CHECK<UNIT1>::value * ENUM_CHECK<UNIT2>::value) ;
define ENUM_DIV<UNIT1 ,UNIT2> = enum (ENUM_CHECK<UNIT1>::value / ENUM_CHECK<UNIT2>::value) ;
define ENUM_MOD<UNIT1 ,UNIT2> = enum (ENUM_CHECK<UNIT1>::value % ENUM_CHECK<UNIT2>::value) ;
define ENUM_INC<UNIT1> = ENUM_ADD<UNIT1 ,ENUM_IDEN> ;
define ENUM_DEC<UNIT1> = ENUM_SUB<UNIT1 ,ENUM_IDEN> ;

define IS_TYPE<UNIT1> = enum (is_type (UNIT1)) ;
define TYPE_CHECK<UNIT1> = ENABLE<IS_TYPE<UNIT1> ,UNIT1> ;
define TYPE_FIRST_ONE<UNIT1> = TYPE_CHECK<UNIT1>::first_one ;
define TYPE_FIRST_REST<UNIT1> = TYPE_CHECK<UNIT1>::fist_rest ;
define TYPE_SECOND_ONE<UNIT1> = TYPE_CHECK<UNIT1>::second_one ;
define TYPE_SECOND_REST<UNIT1> = TYPE_CHECK<UNIT1>::second_rest ;
define TYPE_UNWRAP<UNIT1> = TYPE_FIRST_ONE<ENABLE<ENUM_EQ_IDEN<COUNTOF<UNIT1>> ,UNIT1>> ;
define TYPE_CAT<UNIT1 ,UNIT2> = type<UNIT1... ,UNIT2...> ;

trait TYPE_REPEAT_HELP<ARG1 ,ARG2> {
	require (ENUM_EQ_ZERO<ARG2>) ;
	
	using RET = type<> ;
} ;

trait TYPE_REPEAT_HELP<ARG1 ,ARG2> {
	require (ENUM_EQ_ZERO<ARG2>) ;

	using R1X = typename TYPE_REPEAT_HELP<ARG1 ,ENUM_DEC<ARG2>>::RET ;
	
	using RET = TYPE_CAT<type<ARG1> ,R1X> ;
} ;

define TYPE_REPEAT<ITEM ,SIZE> = typename TYPE_REPEAT_HELP<ITEM ,SIZE>::RET ;

define TYPE_REVERSE<LIST> ;
define TYPE_PICK<LIST ,NTH> ;
define TYPE_FIND<LIST ,ITEM> ;

trait ENUM_ALL_HELP<ARGS> {
	require (ENUM_EQ_ZERO<COUNTOF<ARGS>>) ;
	
	using RET = ENUM_IDEN ;
} ;

trait ENUM_ALL_HELP<ARGS> {
	require (ENUM_GT_ZERO<COUNTOF<ARGS>>) ;

	using R1X = ENUM_BOOL<TYPE_FIRST_ONE<ARG1>> ;
	using R2X = typename ENUM_ALL_HELP<TYPE_FIRST_REST<ARG1>>::RET ;

	using RET = CONDITIONAL<R1X ,R2X ,ENUM_ZERO> ;
} ;

define ENUM_ALL<...UNITS> = typename ENUM_ALL_HELP<UNITS>::RET ;

trait ENUM_ANY_HELP<ARGS> {
	require (ENUM_EQ_ZERO<COUNTOF<ARGS>>) ;

	using RET = ENUM_ZERO ;
} ;

trait ENUM_ANY_HELP<ARGS> {
	require (ENUM_GT_ZERO<COUNTOF<ARGS>>) ;

	using R1X = ENUM_BOOL<TYPE_FIRST_ONE<ARG1>> ;
	using R2X = typename ENUM_ALL_HELP<TYPE_FIRST_REST<ARG1>>::RET ;

	using RET = CONDITIONAL<R1X ,ENUM_IDEN ,R2X> ;
} ;

define ENUM_ANY<...UNITS> = typename ENUM_ANY_HELP<UNITS>::RET ;

trait PLACEHOLDER_HELP<ARG1> {
	require (ENUM_EQ_ZERO<ARG1>) ;

	class PlaceHolder {} ;
} ;

trait PLACEHOLDER_HELP<ARG1> {
	require (ENUM_GT_ZERO<ARG1>) ;

	using BASE = typename PLACEHOLDER_HELP<ENUM_DEC<ARG1>>::PlaceHolder ;

	class PlaceHolder {} ;

	implement PlaceHolder {} ;
} ;

define PlaceHolder<RANK> = typename PLACEHOLDER_HELP<RANK>::PlaceHolder ;

static constant PH0 = PlaceHolder<enum (0)> () ;
static constant PH1 = PlaceHolder<enum (1)> () ;
static constant PH2 = PlaceHolder<enum (2)> () ;
static constant PH3 = PlaceHolder<enum (3)> () ;
static constant PH4 = PlaceHolder<enum (4)> () ;
static constant PH5 = PlaceHolder<enum (5)> () ;
static constant PH6 = PlaceHolder<enum (6)> () ;
static constant PH7 = PlaceHolder<enum (7)> () ;
static constant PH8 = PlaceHolder<enum (8)> () ;
static constant PH9 = PlaceHolder<enum (9)> () ;
static constant PHX = PlaceHolder<enum (10)> () ;

define IS_BOOL<UNIT1> = IS_SAME<UNIT1 ,BOOL> ;
define IS_VAR<UNIT1> = ENUM_ANY<IS_SAME<UNIT1 ,VAR32> ,IS_SAME<UNIT1 ,VAR64>> ;
define IS_FLOAT<UNIT1> = ENUM_ANY<IS_SAME<UNIT1 ,SINGLE> ,IS_SAME<UNIT1 ,DOUBLE>> ;
define IS_BYTE<UNIT1> = ENUM_ANY<IS_SAME<UNIT1 ,BYTE> ,IS_SAME<UNIT1 ,WORD> ,IS_SAME<UNIT1 ,CHAR> ,IS_SAME<UNIT1 ,FEAT>> ;
define IS_STR<UNIT1> = ENUM_ANY<IS_SAME<UNIT1 ,STRA> ,IS_SAME<UNIT1 ,STRU8> ,IS_SAME<UNIT1 ,STRU16> ,IS_SAME<UNIT1 ,STRU32>> ;
define IS_NULL<UNIT1> = IS_SAME<UNIT1 ,typeof (NULL)> ;
define IS_BASIC<UNIT1> = ENUM_ANY<IS_BOOL<UNIT1> ,IS_VAR<UNIT1> ,IS_FLOAT<UNIT1> ,IS_BYTE<UNIT1> ,IS_STR<UNIT1> ,IS_NULL<UNIT1>> ;
define IS_FUNCTION<UNIT1> = enum (is_function (UNIT1)) ;
define IS_NOEXCEPT<UNIT1> = enum (is_noexcept (UNIT1)) ;
define IS_CLASS<UNIT1> = enum (is_class (UNIT1)) ;
define IS_STRUCT<UNIT1> = enum (is_struct (UNIT1)) ;
define IS_TRIVIAL<UNIT1> = enum (is_trivial (UNIT1)) ;
define IS_INTERFACE<UNIT1> = enum (is_interface (UNIT1)) ;
define IS_CONSTRUCTIBLE<RETURN ,PARAMS> = enum (is_constructible (RETURN ,PARAMS)) ;
define IS_CLONEABLE<UNIT1> = enum (is_cloneable (UNIT1)) ;
define IS_EXTEND<BASE ,DERIVED> = enum (is_extend (BASE ,DERIVED)) ;
define IS_CONVERTIBLE<FROM ,TO> = enum (is_convertible (FROM ,TO)) ;
define IS_PLACEHOLDER<UNIT1> = IS_CONVERTIBLE<UNIT1 ,type (PH0)> ;

trait IS_ALL_SAME_HELP<ARGS> {
	require (ENUM_EQ_ZERO<COUNTOF<ARGS>>) ;

	using RET = ENUM_IDEN ;
} ;

trait IS_ALL_SAME_HELP<ARGS> {
	require (ENUM_EQ_IDEN<COUNTOF<ARGS>>) ;

	using RET = ENUM_IDEN ;
} ;

trait IS_ALL_SAME_HELP<ARGS> {
	require (ENUM_GT_IDEN<COUNTOF<ARGS>>) ;

	using R1X = IS_SAME<TYPE_FIRST_ONE<ARGS> ,TYPE_SECOND_ONE<ARGS>> ;
	using R2X = typename IS_ALL_SAME_HELP<TYPE_FIRST_REST<ARGS>>::RET ;

	using RET = ENUM_ALL<R1X ,R2X> ;
} ;

define IS_ALL_SAME<...UNITS> = typename IS_ALL_SAME_HELP<UNITS>::RET ;

trait IS_ANY_SAME_HELP<ARGS> {
	require (ENUM_EQ_ZERO<COUNTOF<ARGS>>) ;

	using RET = ENUM_ZERO ;
} ;

trait IS_ANY_SAME_HELP<ARGS> {
	require (ENUM_EQ_IDEN<COUNTOF<ARGS>>) ;

	using RET = ENUM_ZERO ;
} ;

trait IS_ANY_SAME_HELP<ARGS> {
	require (ENUM_GT_IDEN<COUNTOF<ARGS>>) ;

	using R1X = IS_SAME<TYPE_FIRST_ONE<ARGS> ,TYPE_SECOND_ONE<ARGS>> ;
	using R2X = typename IS_ANY_SAME_HELP<TYPE_FIRST_REST<ARGS>>::RET ;
	using R3X = typename IS_ANY_SAME_HELP<TYPE_CAT<type<R1X> ,TYPE_SECOND_REST<ARGS>>>::RET ;

	using RET = ENUM_ANY<R1X ,R2X ,R3X> ;
} ;

define IS_ANY_SAME<...UNITS> = typename IS_ANY_SAME_HELP<UNITS>::RET ;

trait BYTE_TRAIT_HELP<ARG1 ,ARG2> {
	require (ENUM_EQUAL<ARG1 ,SIZEOF<BYTE>>) ;
	require (ENUM_EQUAL<ARG1 ,ALIGNOF<BYTE>>) ;

	using RET = BYTE ;
} ;

trait BYTE_TRAIT_HELP<ARG1 ,ARG2> {
	require (ENUM_EQUAL<ARG1 ,SIZEOF<WORD>>) ;
	require (ENUM_EQUAL<ARG1 ,ALIGNOF<WORD>>) ;

	using RET = WORD ;
} ;

trait BYTE_TRAIT_HELP<ARG1 ,ARG2> {
	require (ENUM_EQUAL<ARG1 ,SIZEOF<CHAR>>) ;
	require (ENUM_EQUAL<ARG1 ,ALIGNOF<CHAR>>) ;

	using RET = CHAR ;
} ;

trait BYTE_TRAIT_HELP<ARG1 ,ARG2> {
	require (ENUM_EQUAL<ARG1 ,SIZEOF<FEAT>>) ;
	require (ENUM_EQUAL<ARG1 ,ALIGNOF<FEAT>>) ;

	using RET = FEAT ;
} ;

define BYTE_TRAIT<SIZE ,ALIGN> = typename BYTE_TRAIT_HELP<SIZE ,ALIGN>::RET ;

static function noop = () => {} ;

static function abort = () => rust::abort () ;

static function address = (arg1) => rust::address (arg1) ;

static function bitwise = (arg1) => rust::bitwise (arg1) ;

static function swap = (arg1 ,arg2) => rust::swap (arg1 ,arg2) ;

static function forward = (obj) => {
	using R1X = type (obj) ;
	variable ret = R1X () ;
	swap (ret ,obj) ;
	return ret ;
} ;

static function alignas = (base :LENGTH ,align :LENGTH) :LENGTH => {
	constant r1x = align - base % align ;
	return base + r1x % align ;
} ;

static function between = (index :INDEX ,begin :INDEX ,end :INDEX) :BOOL => index >= begin && index < end ;

static function abs = (arg1) => {
	using R1X = type (arg1) ;
	if (arg1 < R1X (ZERO))
		return -arg1 ;
	return +arg1 ;
} ;

static function min = (arg1 ,arg2) => {
	if (arg1 < arg2)
		return arg1 ;
	return arg2 ;
} ;

static function max = (arg1 ,arg2) => {
	if (arg1 < arg2)
		return arg2 ;
	return arg1 ;
} ;

static function hashcode = () :FLAG => {
	constant r1x = VAR64 (-3750763034362895579) ;
	constant r2x = VAR64 (FEAT (r1x) & FEAT (VAR64_MAX)) ;
	return FLAG (r2x) ;
} ;

static function hashcode = (arg1 :FLAG ,arg2 :FLAG)) :FLAG => {
	constant r1x = VAR64 (FEAT (arg1) ^ FEAT (arg2)) ;
	constant r2x = r1x * VAR64 (1099511628211) ;
	constant r3x = VAR64 (FEAT (r2x) & FEAT (VAR64_MAX)) ;
	return FLAG (r3x) ;
} ;

static function bad = (id) => {
	using R1X = type (id) ;
	register r1x = () :auto => ZERO ;
	assert (FALSE) ;
	return R1X (r1x ()) ;
} ;

static function range = (begin :INDEX ,end :INDEX) => rust::range (begin ,end) ;

static function cabi = (id) => rust::cabi (id) ;

trait BOX_HELP<ARG1> {
	require (IS_INTERFACE<ARG1>) ;

	using UNIT1 = ARG1 ;

	class Box {
		interface Holder ;
		class ImplHolder ;

		variable mPointer :Holder ;
	} ;

	interface Box::Holder {
		function destroy = () => virtual ;
		function to[] = () :UNIT1 => virtual ;
	} ;

	trait IMPLHOLDER_HELP<ARG2> {
		using UNIT2 = ARG2 ;

		class Box::ImplHolder {
			variable mValue :UNIT2 ;
		} ;

		implement Box::ImplHolder {
			function new = (that) => mValue = forward (that) ;

			static function create = (that) :Holder => {
				register r1x = ImplHolder (forward (that)) ;
				return new Holder (r1x) ;
			} ;
		} ;

		implement Box::ImplHolder :Holder {
			function destroy = () => delete this ;

			function to[] = () :UNIT1 => mValue ;
		} ;
	} ;

	implement Box {
		function new = () => mPointer = NULL ;

		function delete = noexcept () => {
			if (mPointer == NULL)
				return ;
			mPointer->destroy () ;
			mPointer = NULL ;
		} ;

		static function make = (that) :Box => {
			using R1X = type (that) ;
			require (IS_EXTEND<UNIT1 ,R1X>) ;
			using R2X = typename IMPLHOLDER_HELP<R1X>::ImplHolder ;
			variable ret = Box () ;
			ret.mPointer = R2X::create (forward (that)) ;
			return ret ;
		} ;

		function exist = () :BOOL => mPointer != NULL ;

		function to[] = () :UNIT1 => {
			assert (exist ()) ;
			return mPointer->this->this ;
		} ;
	} ;
} ;

trait CELL_HELP<ARG1> {
	class Cell {
		
	} ;
} ;