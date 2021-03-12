module rust::core ;

using BOOL = internel::bool ;

static constant TRUE = BOOL (internel::true) ;
static constant FALSE = BOOL (internel::false) ;

using VAR32 = internel::int32 ;
using VAR64 = internel::int64 ;

static constant VAR32_MAX = VAR32 (2147483647) ;
static constant VAR32_MIN = -VAR32_MAX - 1 ;
static constant VAR64_MAX = VAR64 (9223372036854775807) ;
static constant VAR64_MIN = -VAR64_MAX - 1 ;

trait VAR_HELP<> {
	require (macro ("config::int32")) ;

	using VAR = VAR32 ;

	static constant VAR_MAX = VAR32_MAX ;
	static constant VAR_MIN = VAR32_MIN ;
} ;

trait VAR_HELP<> {
	require (macro ("config::int64")) ;

	using VAR = VAR64 ;

	static constant VAR_MAX = VAR64_MAX ;
	static constant VAR_MIN = VAR64_MIN ;
} ;

using VAR = typename VAR_HELP<>::VAR ;

static constant VAR_MAX = VAR_HELP<>::VAR_MAX ;
static constant VAR_MIN = VAR_HELP<>::VAR_MIN ;

using INDEX = VAR ;
using LENGTH = VAR ;
using FLAG = VAR ;

static constant USED = VAR (-2) ;
static constant NONE = VAR (-1) ;
static constant ZERO = VAR (+0) ;
static constant IDEN = VAR (+1) ;

using FLOAT32 = internel::float32 ;
using FLOAT64 = internel::float64 ;

static constant FLOAT32_MAX = FLOAT32 (3.402823466E+38) ;
static constant FLOAT32_MIN = FLOAT32 (1.175494351E-38) ;
static constant FLOAT32_EPS = FLOAT32 (1.192092896E-07) ;
static constant FLOAT32_INF = FLOAT32 (internel::infinity) ;
static constant FLOAT64_MAX = FLOAT64 (1.7976931348623158E+308) ;
static constant FLOAT64_MIN = FLOAT64 (2.2250738585072014E-308) ;
static constant FLOAT64_EPS = FLOAT64 (2.2204460492503131E-016) ;
static constant FLOAT64_INF = FLOAT64 (internel::infinity) ;

using BYTE = internel::byte8 ;
using WORD = internel::byte16 ;
using CHAR = internel::byte32 ;
using FEAT = internel::byte64 ;

using STRA = internel::stra ;
using STRU8 = internel::stru8 ;
using STRU16 = internel::stru16 ;
using STRU32 = internel::stru32 ;

trait STR_HELP<> {
	require (macro ("config::stra")) ;

	using STR = STRA ;
} ;

trait STR_HELP<> {
	require (macro ("config::stru8")) ;

	using STR = STRU8 ;
} ;

trait STR_HELP<> {
	require (macro ("config::stru16")) ;

	using STR = STRU16 ;
} ;

trait STR_HELP<> {
	require (macro ("config::stru32")) ;

	using STR = STRU32 ;
} ;

using STR = typename STR_HELP<>::STR ;

static constant NULL = internel::null ;

using ENUM_USED = enum (-2) ;
using ENUM_NONE = enum (-1) ;
using ENUM_ZERO = enum (+0) ;
using ENUM_IDEN = enum (+1) ;

define SIZEOF<UNIT> = enum (internel::sizeof (UNIT)) ;
define ALIGNOF<UNIT> = enum (internel::alignof (UNIT)) ;
define COUNTOF<UNIT> = enum (internel::countof (UNIT)) ;

define IS_SAME<UNIT1 ,UNIT2> = enum (internel::is_same (UNIT1 ,UNIT2)) ;

trait ENABLE_HELP<ARG1 ,ARG2> {
	require (IS_SAME<ARG1 ,ENUM_IDEN>) ;

	using RET = ARG2 ;
} ;

define ENABLE<COND> = typename ENABLE_HELP<COND ,type<>>::RET ;
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

define IS_ENUM<UNIT> = enum (internel::is_enum (UNIT)) ;
define ENUM_CHECK<UNIT> = ENABLE<IS_ENUM<UNIT> ,UNIT> ;

define ENUM_EQUAL<UNIT1 ,UNIT2> = enum (ENUM_CHECK<UNIT1>::value == ENUM_CHECK<UNIT2>::value) ;
define ENUM_NOT_EQUAL<UNIT1 ,UNIT2> = enum (ENUM_CHECK<UNIT1>::value != ENUM_CHECK<UNIT2>::value) ;
define ENUM_BOOL<UNIT> = ENUM_NOT_EQUAL<UNIT ,ENUM_ZERO> ;

define ENUM_COMPR<UNIT1 ,UNIT2> = enum (ENUM_CHECK<UNIT1>::value <=> ENUM_CHECK<ARG2>::value) ;
define ENUM_COMPR_LT<UNIT1 ,UNIT2> = enum (ENUM_COMPR<UNIT1 ,UNIT2>::value < ZERO) ;
define ENUM_COMPR_LT_EQ<UNIT1 ,UNIT2> = enum (ENUM_COMPR<UNIT1 ,UNIT2>::value <= ZERO) ;
define ENUM_COMPR_GT<UNIT1 ,UNIT2> = enum (ENUM_COMPR<UNIT1 ,UNIT2>::value > ZERO) ;
define ENUM_COMPR_GT_EQ<UNIT1 ,UNIT2> = enum (ENUM_COMPR<UNIT1 ,UNIT2>::value >= ZERO) ;
define ENUM_EQ_ZERO<UNIT> = ENUM_EQUAL<UNIT ,ENUM_ZERO> ;
define ENUM_LT_ZERO<UNIT> = ENUM_COMPR_LT<UNIT ,ENUM_ZERO> ;
define ENUM_GT_ZERO<UNIT> = ENUM_COMPR_GT<UNIT ,ENUM_ZERO> ;
define ENUM_EQ_IDEN<UNIT> = ENUM_EQUAL<UNIT ,ENUM_IDEN> ;
define ENUM_LT_IDEN<UNIT> = ENUM_COMPR_LT<UNIT ,ENUM_IDEN> ;
define ENUM_GT_IDEN<UNIT> = ENUM_COMPR_GT<UNIT ,ENUM_IDEN> ;

define ENUM_ADD<UNIT1 ,UNIT2> = enum (ENUM_CHECK<UNIT1>::value + ENUM_CHECK<UNIT2>::value) ;
define ENUM_SUB<UNIT1 ,UNIT2> = enum (ENUM_CHECK<UNIT1>::value - ENUM_CHECK<UNIT2>::value) ;
define ENUM_MUL<UNIT1 ,UNIT2> = enum (ENUM_CHECK<UNIT1>::value * ENUM_CHECK<UNIT2>::value) ;
define ENUM_DIV<UNIT1 ,UNIT2> = enum (ENUM_CHECK<UNIT1>::value / ENUM_CHECK<UNIT2>::value) ;
define ENUM_MOD<UNIT1 ,UNIT2> = enum (ENUM_CHECK<UNIT1>::value % ENUM_CHECK<UNIT2>::value) ;
define ENUM_INC<UNIT> = ENUM_ADD<UNIT ,ENUM_IDEN> ;
define ENUM_DEC<UNIT> = ENUM_SUB<UNIT ,ENUM_IDEN> ;

define IS_TYPE<UNIT> = enum (internel::is_type (UNIT)) ;
define TYPE_CHECK<UNIT> = ENABLE<IS_TYPE<UNIT> ,UNIT> ;

define TYPE_FIRST_ONE<UNIT1 ,UNITS...> = UNIT1 ;
define TYPE_FIRST_REST<UNIT1 ,UNITS...> = UNITS ;
define TYPE_SECOND_ONE<UNIT1 ,UNIT2 ,UNITS...> = UNIT2 ;
define TYPE_SECOND_REST<UNIT1 ,UNIT2 ,UNITS...> = UNITS ;
define TYPE_CAT<UNIT1 ,UNIT2> = type<TYPE_CHECK<UNIT1>... ,TYPE_CHECK<UNIT2>...> ;

trait TYPE_UNWRAP_HELP<ARG1> {
	require (ENUM_EQ_IDEN<COUNTOF<ARG1>>) ;

	using RET = TYPE_FIRST_ONE<ARG1> ;
} ;

define TYPE_UNWRAP<UNIT> = typename TYPE_UNWRAP_HELP<UNIT>::RET ;

trait TYPE_REPEAT_HELP<ARG1 ,ARG2> {
	require (ENUM_EQ_ZERO<ARG2>) ;

	using RET = type<> ;
} ;

trait TYPE_REPEAT_HELP<ARG1 ,ARG2> {
	require (ENUM_GT_ZERO<ARG2>) ;
	
	using R1X = typename TYPE_REPEAT_HELP<ARG1 ,ENUM_DEC<ARG2>>::RET ;

	using RET = TYPE_CAT<ARG1 ,R1X> ;
} ;

define TYPE_REPEAT<UNIT ,SIZE> = typename TYPE_REPEAT_HELP<type<UNIT> ,SIZE>::RET ;

trait TYPE_REVERSE_HELP<ARG1> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;

	using RET = type<> ;
} ;

trait TYPE_REVERSE_HELP<ARG1> {
	require (ENUM_GT_ZERO<COUNTOF<ARG1>>) ;
	
	using R1X = TYPE_FIRST_ONE<ARG1> ;
	using R2X = typename TYPE_REVERSE_HELP<TYPE_FIRST_REST<ARG1>>::RET ;

	using RET = TYPE_CAT<R2X ,type<R1X>> ;
} ;

define TYPE_REVERSE<UNIT> = typename TYPE_REVERSE_HELP<UNIT>::RET ;

trait TYPE_FIND_HELP<ARG1 ,ARG2 ,ARG3> {
	require (ENUM_EQ_ZERO<ARG2>) ;

	using RET = ENUM_NONE ;
} ;

trait TYPE_FIND_HELP<ARG1 ,ARG2 ,ARG3> {
	require (ENUM_GT_ZERO<ARG2>) ;

	using R1X = TYPE_FIRST_ONE<ARG1> ;
	using R2X = typename TYPE_FIND_HELP<TYPE_FIRST_REST<ARG1> ,ARG2 ,ENUM_INC<ARG3>>::RET ;

	using RET = CONDITIONAL<IS_SAME<R1X ,ARG2> ,ARG3 ,R2X> ;
} ;

define TYPE_FIND<LIST ,ITEM> = typename TYPE_FIND_HELP<LIST ,ITEM ,ENUM_ZERO>::RET ;

trait TYPE_PICK_HELP<ARG1 ,ARG2> {
	require (ENUM_EQ_ZERO<ARG2>) ;

	using RET = TYPE_FIRST_ONE<ARG1> ;
} ;

trait TYPE_PICK_HELP<ARG1 ,ARG2> {
	require (ENUM_GT_ZERO<ARG2>) ;

	using RET = typename TYPE_PICK_HELP<TYPE_FIRST_REST<ARG1> ,ENUM_DEC<ARG2>>::RET ;
} ;

define TYPE_PICK<LIST ,INDEX> = typename TYPE_PICK_HELP<LIST ,INDEX>::RET ;

trait ENUM_ALL_HELP<ARG1> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;

	using RET = ENUM_IDEN ;
} ;

trait ENUM_ALL_HELP<ARG1> {
	require (ENUM_GT_ZERO<COUNTOF<ARG1>>) ;

	using R1X = ENUM_BOOL<TYPE_FIRST_ONE<ARG1>> ;
	using R2X = typename ENUM_ALL_HELP<TYPE_FIRST_REST<ARG1>>::RET ;

	using RET = CONDITIONAL<R1X ,R2X ,ENUM_ZERO> ;
} ;

trait ENUM_ANY_HELP<ARG1> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;

	using RET = ENUM_ZERO ;
} ;

trait ENUM_ANY_HELP<ARG1> {
	require (ENUM_GT_ZERO<COUNTOF<ARG1>>) ;

	using R1X = ENUM_BOOL<TYPE_FIRST_ONE<ARG1>> ;
	using R2X = typename ENUM_ANY_HELP<TYPE_FIRST_REST<ARG1>>::RET ;

	using RET = CONDITIONAL<R1X ,ENUM_IDEN ,R2X> ;
} ;

define ENUM_ALL<UNITS...> = typename ENUM_ALL_HELP<UNITS>::RET ;
define ENUM_ANY<UNITS...> = typename ENUM_ANY_HELP<UNITS>::RET ;

trait IS_ALL_SAME_HELP<ARG1> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;

	using RET = ENUM_IDEN ;
} ;

trait IS_ALL_SAME_HELP<ARG1> {
	require (ENUM_EQ_IDEN<COUNTOF<ARG1>>) ;

	using RET = ENUM_IDEN ;
} ;

trait IS_ALL_SAME_HELP<ARG1> {
	require (ENUM_GT_IDEN<COUNTOF<ARG1>>) ;

	using R1X = TYPE_FIRST_ONE<ARG1> ;
	using R2X = TYPE_SECOND_ONE<ARG1> ;
	using R3X = typename IS_ALL_SAME_HELP<TYPE_CAT<R1X ,TYPE_SECOND_REST<ARG1>>>::RET ;

	using RET = ENUM_ALL<IS_SAME<R1X ,R2X> ,R3X> ;
} ;

trait IS_ANY_SAME_HELP<ARG1> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;

	using RET = ENUM_ZERO ;
} ;

trait IS_ANY_SAME_HELP<ARG1> {
	require (ENUM_EQ_IDEN<COUNTOF<ARG1>>) ;

	using RET = ENUM_ZERO ;
} ;

trait IS_ANY_SAME_HELP<ARG1> {
	require (ENUM_GT_IDEN<COUNTOF<ARG1>>) ;

	using R1X = TYPE_FIRST_ONE<ARG1> ;
	using R2X = TYPE_SECOND_ONE<ARG1> ;
	using R3X = typename IS_ANY_SAME_HELP<TYPE_CAT<R1X ,TYPE_SECOND_REST<ARG1>>>::RET ;
	using R4X = typename IS_ANY_SAME_HELP<TYPE_CAT<R2X ,TYPE_SECOND_REST<ARG1>>>::RET ;

	using RET = ENUM_ANY<IS_SAME<R1X ,R2X> ,R3X ,R4X> ;
} ;

define IS_ALL_SAME<UNITS...> = typename IS_ALL_SAME_HELP<UNITS>::RET ;
define IS_ANY_SAME<UNITS...> = typename IS_ANY_SAME_HELP<UNITS>::RET ;

trait PLACEHOLDER_HELP<ARG1> {
	require (ENUM_EQ_ZERO<ARG1>) ;

	class PlaceHolder {} ;
} ;

trait PLACEHOLDER_HELP<ARG1> {
	require (ENUM_GT_ZERO<ARG1>) ;

	using BASE = typename PLACEHOLDER_HELP<ENUM_DEC<ARG1>>::PlaceHolder ;

	class PlaceHolder {
		extend :BASE ;
	} ;
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

define IS_BOOL<UNIT> = IS_SAME<UNIT ,BOOL> ;
define IS_VAR<UNIT> = ENUM_ANY<IS_SAME<UNIT ,VAR32> ,IS_SAME<UNIT ,VAR64>> ;
define IS_FLOAT<UNIT> = ENUM_ANY<IS_SAME<UNIT ,FLOAT32> ,IS_SAME<UNIT ,FLOAT64>> ;
define IS_BYTE<UNIT> = ENUM_ANY<IS_SAME<UNIT ,BYTE> ,IS_SAME<UNIT ,WORD> ,IS_SAME<UNIT ,CHAR> ,IS_SAME<UNIT ,FEAT> ,IS_SAME<UNIT ,internel::byte128> ,IS_SAME<UNIT ,internel::byte256> ,IS_SAME<UNIT ,internel::byte512>> ;
define IS_STR<UNIT> = ENUM_ANY<IS_SAME<UNIT ,STRA> ,IS_SAME<UNIT ,STRU8> ,IS_SAME<UNIT ,STRU16> ,IS_SAME<UNIT ,STRU32>> ;
define IS_NULL<UNIT> = IS_SAME<UNIT ,type (NULL)> ;
define IS_BASIC<UNIT> = ENUM_ANY<IS_BOOL<UNIT> ,IS_VAR<UNIT> ,IS_FLOAT<UNIT> ,IS_BYTE<UNIT> ,IS_STR<UNIT> ,IS_NULL<UNIT>> ;

define IS_FUNCTION<UNIT> = enum (internel::is_function (UNIT)) ;
define IS_NOEXCEPT<UNIT> = enum (internel::is_noexcept (UNIT)) ;

define IS_CLASS<UNIT> = enum (internel::is_class (UNIT)) ;
define IS_STRUCT<UNIT> = enum (internel::is_struct (UNIT)) ;
define IS_TRIVIAL<UNIT> = enum (internel::is_trivial (UNIT)) ;
define IS_CONSTRUCTIBLE<RETURN ,PARAMS> = enum (internel::is_constructible (RETURN ,PARAMS)) ;
define IS_CLONEABLE<UNIT> = enum (internel::is_cloneable (UNIT)) ;
define IS_INTERFACE<UNIT> = enum (internel::is_interface (UNIT)) ;
define IS_EXTEND<BASE ,DERIVED> = enum (internel::is_extend (BASE ,DERIVED)) ;
define IS_PLACEHOLDER<UNIT> = IS_EXTEND<UNIT ,type (PH0)> ;

trait BYTE_TRAIT_HELP<ARG1> {
	require (ENUM_EQUAL<SIZEOF<ARG1> ,SIZEOF<BYTE>>) ;
	require (ENUM_EQUAL<ALIGNOF<ARG1> ,ALIGNOF<BYTE>>) ;

	using RET = BYTE ;
} ;

trait BYTE_TRAIT_HELP<ARG1> {
	require (ENUM_EQUAL<SIZEOF<ARG1> ,SIZEOF<WORD>>) ;
	require (ENUM_EQUAL<ALIGNOF<ARG1> ,ALIGNOF<WORD>>) ;

	using RET = WORD ;
} ;

trait BYTE_TRAIT_HELP<ARG1> {
	require (ENUM_EQUAL<SIZEOF<ARG1> ,SIZEOF<CHAR>>) ;
	require (ENUM_EQUAL<ALIGNOF<ARG1> ,ALIGNOF<CHAR>>) ;

	using RET = CHAR ;
} ;

trait BYTE_TRAIT_HELP<ARG1> {
	require (ENUM_EQUAL<SIZEOF<ARG1> ,SIZEOF<FEAT>>) ;
	require (ENUM_EQUAL<ALIGNOF<ARG1> ,ALIGNOF<FEAT>>) ;

	using RET = FEAT ;
} ;

trait BYTE_TRAIT_HELP<ARG1> {
	require (ENUM_EQUAL<SIZEOF<ARG1> ,SIZEOF<internel::byte128>>) ;
	require (ENUM_EQUAL<ALIGNOF<ARG1> ,ALIGNOF<internel::byte128>>) ;

	using RET = internel::byte128 ;
} ;

trait BYTE_TRAIT_HELP<ARG1> {
	require (ENUM_EQUAL<SIZEOF<ARG1> ,SIZEOF<internel::byte256>>) ;
	require (ENUM_EQUAL<ALIGNOF<ARG1> ,ALIGNOF<internel::byte256>>) ;

	using RET = internel::byte256 ;
} ;

trait BYTE_TRAIT_HELP<ARG1> {
	require (ENUM_EQUAL<SIZEOF<ARG1> ,SIZEOF<internel::byte512>>) ;
	require (ENUM_EQUAL<ALIGNOF<ARG1> ,ALIGNOF<internel::byte512>>) ;

	using RET = internel::byte512 ;
} ;

define BYTE_TRAIT<UNIT> = typename BYTE_TRAIT_HELP<UNIT>::RET ;

static function noop = () => {} ;

static function bad = (id) => {
	using R1X = type (id) ;
	assert (FALSE) ;
	constant r1x = () :auto => ZERO ;
	return R1X (r1x ()) ;
} ;

static function swap = (obj1 ,obj2) => internel::swap (obj1 ,obj2) ;

static function forward = (obj) => internel::forward (obj) ;

static function exchange = (obj1 ,obj2) => {
	variable ret = forward (obj2) ;
	swap (ret ,obj1) ;
	return ret ;
} ;

static function address = (obj) :LENGTH => internel::address (obj) ;

static function alignto = (base :LENGTH ,align :LENGTH) :LENGTH => {
	constant r1x = align - base % align ;
	return base + r1x % align ;
} ;

static function between = (index :INDEX ,begin :INDEX ,end :INDEX) :BOOL => index >= begin && index < end ;

static function abs = (obj) => {
	using R1X = type (obj) ;
	if (obj < R1X (ZERO))
		return -obj ;
	return +obj ;
} ;

static function min = (obj1 ,obj2) => {
	if (obj1 < obj2)
		return obj1 ;
	return obj2 ;
} ;

static function max = (obj1 ,obj2) => {
	if (obj1 < obj2)
		return obj2 ;
	return obj1 ;
} ;

static function hashcode = () :FLAG => {
	constant r2x = VAR64 (-3750763034362895579) ;
	constant r3x = VAR64 (FEAT (r2x) & FEAT (VAR_MAX)) ;
	return FLAG (r3x) ;
} ;

static function hashcode = (obj1 :FLAG ,obj2 :FLAG) :FLAG => {
	constant r1x = VAR64 (FEAT (obj1) ^ FEAT (obj2)) ;
	constant r2x = r1x * VAR64 (1099511628211) ;
	constant r3x = VAR64 (FEAT (r2x) & FEAT (VAR_MAX)) ;
	return FLAG (r3x) ;
} ;

trait ITERATOR_HELP<> {
	class Iterator {
		constant mBegin :INDEX ;
		constant mEnd :INDEX ;
		variable mCurr :INDEX ;
	} ;

	implement Iterator {
		function new = (begin :INDEX ,end :INDEX) => {
			mBegin = begin ;
			mEnd = max (begin ,end) ;
			mCurr = mBegin ;
		} ;

		function good = () :BOOL => mCurr < mEnd ;

		function step_next = () => mCurr = mCurr + 1 ;

		property get = [] :INDEX => mCurr ;
	} ;
} ;

using Iterator = typename ITERATOR_HELP<>::Iterator ;

static function range = (begin :INDEX ,end :INDEX) :Iterator => Iterator (begin ,end) ;

trait SLICE_HELP<ARG1> {
	using UNIT = ARG1 ;

	class Slice {
		interface Holder ;

		variable mPointer :Holder ;
	} ;

	interface Slice::Holder {
		function copy = () :Holder => virtual ;
		function size = () :LENGTH => virtual ;
		property at = [index :INDEX] :UNIT => virtual ;
	} ;

	implement Slice {
		function new = () => mPointer = NULL ;

		function new = (that ,rest...) => mPointer = internel::builtin_slice (that ,rest...) ;

		function clone = () :Slice => {
			variable ret = Slice () ;
			switch {
				if (mPointer == NULL)
					continue ;
				ret.mPointer = mPointer->copy () ;
			} ;
			return ret ;
		} ;

		function size = () :LENGTH => {
			if (mPointer == NULL)
				return ZERO ;
			return mPointer->size () ;
		} ;

		function addr = () :LENGTH => {
			if (mPointer == NULL)
				return ZERO ;
			return address (mPointer->at[0]) ;
		} ;

		property at = [index :INDEX] :UNIT => {
			assert (between (index ,0 ,size ())) ;
			return mPointer->at[index] ;
		} ;

		function equal = (that :Slice) :BOOL => {
			if (mSize != that.mSize)
				return FALSE ;
			for (i) in range (0 ,mSize) {
				if (at[i] != that.at[i])
					return FALSE ;
			} ;
			return TRUE ;
		} ;

		function compr = (that :Slice) :FLAG => {
			constant r1x = min (mSize ,that.mSize) ;
			for (i) in range (0 ,r1x) {
				constant r2x = at[i] <=> that.at[i] ;
				if (r2x != ZERO)
					return r2x ;
			} ;
			return mSize <=> that.mSize ;
		} ;
	} ;
} ;

define Slice<UNIT> = typename SLICE_HELP<UNIT>::Slice ;

trait CLAZZ_HELP<> {
	class Clazz {
		interface Holder ;

		variable mPointer :Holder ;
	} ;

	interface Clazz::Holder {
		function copy = () :Holder => virtual ;
		property type_hash = [] :FLAG => virtual ;
		property type_name = [] :Slice<STR> => virtual ;
		property type_size = [] :LENGTH => virtual ;
		property type_align = [] :LENGTH => virtual ;
	} ;

	implement Clazz {
		function new = () => mPointer = NULL ;

		function new = (that) => mPointer = internel::builtin_clazz (that) ;

		static property nullopt = [] => {
			static constant M_NULLOPT = Clazz () ;
			return M_NULLOPT ;
		} ;

		function clone = () :Clazz => {
			variable ret = Clazz () ;
			switch {
				if (mPointer == NULL)
					continue ;
				ret.mPointer = mPointer->copy () ;
			} ;
			return ret ;
		} ;

		property type_hash = [] :FLAG => {
			static constant M_HASH = ZERO ;
			if (mPointer == NULL)
				return M_HASH ;
			return mPointer->type_hash[] ;
		} ;

		property type_name = [] :Slice<STR> => {
			static constant M_NAME = "" ;
			if (mPointer == NULL)
				return M_NAME ;
			return mPointer->type_name[] ;
		} ;

		property type_size = [] :LENGTH => {
			static constant M_SIZE = LENGTH (1) ;
			if (mPointer == NULL)
				return M_SIZE ;
			return mPointer->type_size[] ;
		} ;

		property type_align = [] :LENGTH => {
			static constant M_ALIGN = LENGTH (1) ;
			if (mPointer == NULL)
				return M_ALIGN ;
			return mPointer->type_align[] ;
		} ;

		function equal = (that :Clazz) :BOOL => {
			if (type_hash != that.type_hash[])
				return FALSE ;
			if (type_name != that.type_name[])
				return FALSE ;
			return TRUE ;
		} ;

		function compr = (that :Clazz) :FLAG => {
			constant r2x = type_name[] <=> that.type_name[] ;
			if (r2x != ZERO)
				return r2x ;
			return ZERO ;
		} ;
	} ;
} ;

using Clazz = typename CLAZZ_HELP<>::Clazz ;