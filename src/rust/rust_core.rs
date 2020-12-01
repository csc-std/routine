
module rust::core ;

import module rust ;

using BOOL = bool ;

static constant TRUE = BOOL (true) ;
static constant FALSE = BOOL (false) ;

using VAR32 = int32 ;
using VAR64 = int64 ;

static constant VAR32_MAX = VAR32 (+2147483647) ;
static constant VAR32_MIN = VAR32 (-2147483648) ;
static constant VAR64_MAX = VAR64 (+9223372036854775807) ;
static constant VAR64_MIN = VAR64 (-9223372036854775808) ;

trait VAR_HELP {
	require (macro ("config_int32")) ;

	using VAR = VAR32 ;

	static constant VAR_MAX = VAR32_MAX ;
	static constant VAR_MIN = VAR32_MIN ;
} ;

trait VAR_HELP {
	require (macro ("config_int64")) ;

	using VAR = VAR64 ;

	static constant VAR_MAX = VAR64_MAX ;
	static constant VAR_MIN = VAR64_MIN ;
} ;

using VAR = VAR_HELP::VAR ;

static constant VAR_MAX = VAR_HELP::VAR_MAX ;
static constant VAR_MIN = VAR_HELP::VAR_MIN ;

using INDEX = VAR ;
using LENGTH = VAR ;
using FLAG = VAR ;

static constant USED = VAR (-2) ;
static constant NONE = VAR (-1) ;
static constant ZERO = VAR (+0) ;
static constant IDEN = VAR (+1) ;

using FLOAT32 = float32 ;
using FLOAT64 = float64 ;

static constant FLOAT32_MAX = FLOAT32 (3.402823466E+38) ;
static constant FLOAT32_MIN = FLOAT32 (1.175494351E-38) ;
static constant FLOAT32_EPS = FLOAT32 (1.192092896E-07) ;
static constant FLOAT32_INF = FLOAT32 (infinity) ;
static constant FLOAT64_MAX = FLOAT64 (1.7976931348623158E+308) ;
static constant FLOAT64_MIN = FLOAT64 (2.2250738585072014E-308) ;
static constant FLOAT64_EPS = FLOAT64 (2.2204460492503131E-016) ;
static constant FLOAT64_INF = FLOAT64 (infinity) ;

using BYTE = byte8 ;
using WORD = byte16 ;
using CHAR = byte32 ;
using FEAT = byte64 ;

using STRA = stra ;
using STRU8 = stru8 ;
using STRU16 = stru16 ;
using STRU32 = stru32 ;

trait STR_HELP {
	require (macro ("config_stra")) ;

	using STR = STRA ;
} ;

trait STR_HELP {
	require (macro ("config_stru8")) ;

	using STR = STRU8 ;
} ;

trait STR_HELP {
	require (macro ("config_stru16")) ;

	using STR = STRU16 ;
} ;

trait STR_HELP {
	require (macro ("config_stru32")) ;

	using STR = STRU32 ;
} ;

using STR = STR_HELP::STR ;

static constant NULL = null ;

using ENUM_NONE = enum (NONE) ;
using ENUM_ZERO = enum (ZERO ;
using ENUM_IDEN = enum (IDEN) ;

using ALIGNOF<UNIT> = enum (rust::alignof (UNIT)) ;
using SIZEOF<UNIT> = enum (rust::sizeof (UNIT)) ;
using COUNTOF<UNIT> = enum (rust::countof (UNIT)) ;

using CALL<UNIT> = UNIT::RET ;

trait ENUM_UNWRAP_HELP<ARG1> {
	require (IS_ENUM<EXPR>) ;

	using RET = ARG1 ;
} ;

trait ENUM_ALL_HELP<ARGS> {
	require (ENUM_EQ<COUNTOF<ARGS> ,ENUM_ZERO>) ;

	using RET = ENUM_IDEN ;
} ;

trait ENUM_ALL_HELP<ARGS> {
	require (ENUM_GT<COUNTOF<ARGS> ,ENUM_ZERO>) ;

	using R1X = TYPE_FIRST<ARGS> ;
	using R2X = CALL<ENUM_ALL_HELP<TYPE_FIRST_REST<ARGS>>> ;
	using RET = ENUM_AND<R1X ,R2X> ;
} ;

trait ENUM_ANY_HELP<ARGS> {
	require (ENUM_EQ<COUNTOF<ARGS> ,ENUM_ZERO>) ;

	using RET = ENUM_ZERO ;
} ;

trait ENUM_ANY_HELP<ARGS> {
	require (ENUM_GT<COUNTOF<ARGS> ,ENUM_ZERO>) ;

	using R1X = TYPE_FIRST<ARGS> ;
	using R2X = CALL<ENUM_ANY_HELP<TYPE_FIRST_REST<ARGS>>> ;
	using RET = ENUM_OR<R1X ,R2X> ;
} ;

using ENUM_UNWRAP<EXPR> = CALL<ENUM_UNWRAP_HELP<EXPR>> ;
using ENUM_AND<EXPR1 ,EXPR2> = enum (ENUM_UNWRAP<EXPR1>::value && ENUM_UNWRAP<EXPR2>::value) ;
using ENUM_OR<EXPR1 ,EXPR2> = enum (ENUM_UNWRAP<EXPR1>::value || ENUM_UNWRAP<EXPR2>::value) ;
using ENUM_ALL<...> = CALL<ENUM_ALL_HELP<type<...>>> ;
using ENUM_ANY<...> = CALL<ENUM_ANY_HELP<type<...>>> ;
using ENUM_NOT<EXPR> = enum (not ENUM_UNWRAP<EXPR>::value) ;
using ENUM_EQ<EXPR1 ,EXPR2> = enum (ENUM_UNWRAP<EXPR1>::value == ENUM_UNWRAP<EXPR2>::value) ;
using ENUM_NOT_EQ<EXPR1 ,EXPR2> = ENUM_NOT<ENUM_EQ<EXPR1 ,EXPR2>> ;
using ENUM_COMPR<EXPR1 ,EXPR2> = enum (ENUM_UNWRAP<EXPR1>::value <=> ENUM_UNWRAP<EXPR2>::value) ;
using ENUM_LT<EXPR1 ,EXPR2> = enum (ENUM_COMPR<EXPR1 ,EXPR2>::value < ZERO) ;
using ENUM_GT<EXPR1 ,EXPR2> = enum (ENUM_COMPR<EXPR1 ,EXPR2>::value > ZERO) ;
using ENUM_LT_EQ<EXPR1 ,EXPR2> = enum (ENUM_COMPR<EXPR1 ,EXPR2>::value <= ZERO) ;
using ENUM_GT_EQ<EXPR1 ,EXPR2> = enum (ENUM_COMPR<EXPR1 ,EXPR2>::value >= ZERO) ;
using ENUM_BETWEEN<EXPR ,BEGIN ,END> = ENUM_AND<ENUM_GT_EQ<EXPR ,BEGIN> ,ENUM_LT<EXPR ,END>> ;
using ENUM_ADD<EXPR1 ,EXPR2> = enum (ENUM_UNWRAP<EXPR1>::value + ENUM_UNWRAP<EXPR2>::value) ;
using ENUM_SUB<EXPR1 ,EXPR2> = enum (ENUM_UNWRAP<EXPR1>::value - ENUM_UNWRAP<EXPR2>::value) ;
using ENUM_MUL<EXPR1 ,EXPR2> = enum (ENUM_UNWRAP<EXPR1>::value * ENUM_UNWRAP<EXPR2>::value) ;
using ENUM_DIV<EXPR1 ,EXPR2> = enum (ENUM_UNWRAP<EXPR1>::value / ENUM_UNWRAP<EXPR2>::value) ;
using ENUM_MOD<EXPR1 ,EXPR2> = enum (ENUM_UNWRAP<EXPR1>::value % ENUM_UNWRAP<EXPR2>::value) ;
using ENUM_INC<EXPR> = ENUM_ADD<EXPR ,ENUM_IDEN> ;
using ENUM_DEC<EXPR> = ENUM_SUB<EXPR ,ENUM_IDEN> ;
using ENUM_MAX<EXPR1 ,EXPR2> = CONDITIONAL<ENUM_GT_EQ<EXPR1 ,EXPR2> ,EXPR1 ,EXPR2> ;
using ENUM_MIN<EXPR1 ,EXPR2> = CONDITIONAL<ENUM_LT_EQ<EXPR1 ,EXPR2> ,EXPR1 ,EXPR2> ;

trait PLACEHOLDER_HELP<ARG1> {
	require (ENUM_EQ<ARG1 ,ENUM_ZERO>) ;

	class PLACEHOLDER {} ;
} ;

trait PLACEHOLDER_HELP<ARG1> {
	require (ENUM_GT<ARG1 ,ENUM_ZERO>) ;

	using R1X = PLACEHOLDER_HELP<ENUM_DEC<ARG1>>::PLACEHOLDER ;

	class PLACEHOLDER {
		public extend :R1X ;
	} ;
} ;

using PLACEHOLDER<RANK> = PLACEHOLDER_HELP<RANK>::PLACEHOLDER ;

static constant P0 = PLACEHOLDER<enum (0)> () ;
static constant P1 = PLACEHOLDER<enum (1)> () ;
static constant P2 = PLACEHOLDER<enum (2)> () ;
static constant P3 = PLACEHOLDER<enum (3)> () ;
static constant P4 = PLACEHOLDER<enum (4)> () ;
static constant P5 = PLACEHOLDER<enum (5)> () ;
static constant P6 = PLACEHOLDER<enum (6)> () ;
static constant P7 = PLACEHOLDER<enum (7)> () ;
static constant P8 = PLACEHOLDER<enum (8)> () ;
static constant P9 = PLACEHOLDER<enum (9)> () ;
static constant PX = PLACEHOLDER<enum (10)> () ;

using UNION<ALIGN ,SIZE> = CALL<UNION_HELP<ALIGN ,SIZE>> ;

trait TEMP_HELP<UNIT> {
	class TEMP {
		public using REMOVE_TEMP_TYPE = UNIT ;

		variable mStorage :UNION<ALIGNOF<UNIT> ,SIZEOF<UNIT>> ;
	} ;	

	implement TEMP {
		function new = () => default ;
	} ;
} ;

using TEMP<UNIT> = TEMP_HELP<UNIT>::TEMP ;

trait CONDITIONAL_HELP<ARG1 ,ARG2 ,ARG3> {
	require (ARG1) ;

	using RET = ARG2 ;
} ;

trait CONDITIONAL_HELP<ARG1 ,ARG2 ,ARG3> {
	require (ENUM_NOT<ARG1>) ;

	using RET = ARG3 ;
} ;

trait IS_ALL_SAME_HELP<ARGS> {
	require (ENUM_EQ<COUNTOF<ARGS> ,ENUM_ZERO>) ;

	using RET = ENUM_IDEN ;
} ;

trait IS_ALL_SAME_HELP<ARGS> {
	require (ENUM_EQ<COUNTOF<ARGS> ,ENUM_IDEN>) ;

	using RET = ENUM_IDEN ;
} ;

trait IS_ALL_SAME_HELP<ARGS> {
	require (ENUM_GT<COUNTOF<ARGS> ,ENUM_IDEN>) ;

	using R1X = TYPE_FIRST<ARGS> ;
	using R2X = TYPE_SECOND<ARGS> ;
	using R3X = CALL<IS_ALL_SAME_HELP<type<R1X ,TYPE_SECOND_REST<ARGS>...>>> ;
	using RET = ENUM_ALL<IS_SAME<R1X ,R2X> ,R3X> ;
} ;

trait IS_ANY_SAME<ARGS> {
	require (ENUM_EQ<COUNTOF<ARGS> ,ENUM_ZERO>) ;

	using RET = ENUM_ZERO ;
} ;

trait IS_ANY_SAME<ARGS> {
	require (ENUM_EQ<COUNTOF<ARGS> ,ENUM_IDEN>) ;

	using RET = ENUM_ZERO ;
} ;

trait IS_ANY_SAME<ARGS> {
	require (ENUM_GT<COUNTOF<ARGS> ,ENUM_IDEN>) ;

	using R1X = TYPE_FIRST<ARGS> ;
	using R2X = TYPE_SECOND<ARGS> ;
	using R3X = CALL<IS_ANY_SAME<type<R1X ,TYPE_SECOND_REST<ARGS>...>>> ;
	using R4X = CALL<IS_ANY_SAME<type<R2X ,TYPE_SECOND_REST<ARGS>...>>> ;
	using RET = ENUM_ANY<IS_SAME<R1X ,R2X> ,R3X ,R4X> ;
} ;

using CONDITIONAL<COND ,YES ,NO> = CALL<CONDITIONAL_HELP<COND ,YES ,NO>> ;

using IS_SAME<UNIT1 ,UNIT2> = enum (rust::is_same (UNIT1 ,UNIT2)) ;
using IS_ALL_SAME<...> = CALL<IS_ALL_SAME_HELP<type<...>>> ;
using IS_ANY_SAME<...> = CALL<IS_ANY_SAME_HELP<type<...>>> ;

using IS_BOOL<UNIT> = IS_SAME<UNIT ,BOOL> ;
using IS_VAR<UNIT> = ENUM_ALL<IS_SAME<UNIT ,VAR32> ,IS_SAME<UNIT ,VAR64>> ;
using IS_FLOAT<UNIT> = ENUM_ALL<IS_SAME<UNIT ,FLOAT32> ,IS_SAME<UNIT ,FLOAT64>> ;
using IS_BYTE<UNIT> = ENUM_ALL<IS_SAME<UNIT ,BYTE> ,IS_SAME<UNIT ,WORD> ,IS_SAME<UNIT ,CHAR> ,IS_SAME<UNIT ,FEAT>> ;
using IS_STR<UNIT> = ENUM_ALL<IS_SAME<UNIT ,STRA> ,IS_SAME<UNIT ,STRU8> ,IS_SAME<UNIT ,STRU16> ,IS_SAME<UNIT ,STRU32>> ;
using IS_BASIC<UNIT> = ENUM_ALL<IS_BOOL<UNIT> ,IS_VAR<UNIT> ,IS_FLOAT<UNIT> ,IS_BYTE<UNIT> ,IS_STR<UNIT>> ;

using IS_ENUM<UNIT> = enum (rust::is_enum (UNIT)) ;

using IS_TYPE<UNIT> = enum (rust::is_type (UNIT)) ;

using TYPE_FIRST<ALL> = ALL::FIRST_TYPE ;
using TYPE_SECOND<ALL> = ALL::SECOND_TYPE ;
using TYPE_FIRST_REST<ALL> = ALL::FIRST_REST_TYPE ;
using TYPE_SECOND_REST<ALL> = ALL::SECOND_REST_TYPE ;
using TYPE_LAST<ALL> = ALL::LAST_TYPE ;
using TYPE_SLAST<ALL> = ALL::SLAST_TYPE ;
using TYPE_REST_LAST<ALL> = ALL::REST_LAST_TYPE ;
using TYPE_REST_SLAST<ALL> = ALL::REST_SLAST_TYPE ;
using TYPE_CAT<UNIT1 ,UNIT2> = type<UNIT1... ,UNIT2...> ;
using TYPE_UNWRAP<ALL> = CALL<TYPE_UNWRAP_HELP<ALL>>
using TYPE_PICK<ALL ,POS> = CALL<TYPE_PICK_HELP<ALL ,POS>> ;
using TYPE_FIND<ALL ,KEY> = CALL<TYPE_FIND_HELP<ALL ,KEY>> ;
using TYPE_REPEAT<UNIT ,SIZE> = CALL<TYPE_REPEAT_HELP<UNIT ,SIZE>> ;

using IS_STRUCT<UNIT> = enum (rust::is_struct (UNIT)) ;
using REFLECT_STRUCT<UNIT> = rust::reflct_struct (UNIT) ;
using STRUCT_BIND<PARAMS> = [...:PARAMS] ;

using IS_FUNCTION<UNIT> = enum (rust::is_function (UNIT)) ;
using REFLECT_FUNCTION<UNIT> = rust::reflect_function (UNIT) ;
using REMOVE_FUNCTION<UNIT> = TYPE_UNWRAP<TYPE_FIRST<REFLECT_FUNCTION<UNIT>>> ;
using FUNCTION_BIND<RETURN ,PARAMS> = (...:PARAMS) :RETURN ;

using IS_TRIVIAL<UNIT> = enum (rust::is_trivial (UNIT)) ;
using IS_INTERFACE<UNIT> = enum (rust::is_interface (UNIT)) ;

using IS_CLASS<UNIT> = enum (rust::is_class (UNIT)) ;
using IS_CONSTRUCTIBLE<UNIT ,PARAPMS> = enum (rust::is_constructible (UNIT ,PARAPMS)) ;
using IS_SHAREABLE<UNIT> = enum (rust::is_shareable (UNIT)) ;
using IS_CLONEABLE<UNIT> = enum (rust::is_cloneable (UNIT)) ;
using IS_EXTEND<BASE ,DERIVED> = enum (rust::is_extend (BASE ,DERIVED)) ;
using IS_IMPLEMENT<BASE ,DERIVED> = enum (rust::is_implement (BASE ,DERIVED)) ;

using IS_PLACEHOLDER<UNIT> = IS_EXTEND<PLACEHOLDER<ZERO> ,UNIT> ;

trait IS_TEMP_HELP<ARG1 ,ARG2> {
	using RET = ARG1::REMOVE_TEMP_TYPE ;
} ;

trait IS_TEMP_HELP<ARG1 ,ARG2> {
	require (ENUM_EQ<ARG2 ,ENUM_ZERO>) ;

	using RET = CALL<IS_TEMP_HELP<ARG1 ,ENUM_IDEN>> ;
} ;

trait IS_TEMP_HELP<ARG1 ,ARG2> {
	require (ENUM_EQ<ARG2 ,ENUM_IDEN>) ;

	using RET = ENUM_ZERO ;
} ;

using IS_TEMP<UNIT> = CALL<IS_TEMP_HELP<UNIT ,ENUM_ZERO>> ;
using REMOVE_TEMP<UNIT> = UNIT::REMOVE_TEMP_TYPE ;

trait BYTE_TRAIT_HELP<ARG1 ,ARG2> {
	require (ENUM_EQ<ARG1 ,ALIGNOF<BYTE>>) ;
	require (ENUM_EQ<ARG2 ,SIZEOF<BYTE>>) ;

	using RET = BYTE ;
} ;

trait BYTE_TRAIT_HELP<ARG1 ,ARG2> {
	require (ENUM_EQ<ARG1 ,ALIGNOF<WORD>>) ;
	require (ENUM_EQ<ARG2 ,SIZEOF<WORD>>) ;

	using RET = WORD ;
} ;

trait BYTE_TRAIT_HELP<ARG1 ,ARG2> {
	require (ENUM_EQ<ARG1 ,ALIGNOF<CHAR>>) ;
	require (ENUM_EQ<ARG2 ,SIZEOF<CHAR>>) ;

	using RET = CHAR ;
} ;

trait BYTE_TRAIT_HELP<ARG1 ,ARG2> {
	require (ENUM_EQ<ARG1 ,ALIGNOF<FEAT>>) ;
	require (ENUM_EQ<ARG2 ,SIZEOF<FEAT>>) ;

	using RET = FEAT ;
} ;

using BYTE_TRAIT<UNIT> = CALL<BYTE_TRAIT_HELP<UNIT>> ;

function noop = () => {
	rust::assert (TRUE) ;
} ;

function unimplemented = () => {
	rust::assert (FALSE) ;
} ;

function address = (obj) => rust::address (obj) ;

function alignas = (base :LENGTH ,align :LENGTH) => base + (align - base % align) % align;

function between = (obj :INDEX ,begin :INDEX ,end :INDEX) => obj >= begin && obj < end ;

function at = (id1 ,owner ,addr :LENGTH ,rc) => {
	return rust::at (id1 ,addr ,rc) ;
} ;

function swap = (obj1 ,obj2) => {
	using R1X = type (obj1) ;
	using R2X = type (obj2) ;
	require (IS_SAME<R1X ,R2X>) ;
	at (type<TEMP<R1X>>::id ,obj1 ,address (obj1) ,borrow (x :TEMP<R1X>) => at (type<TEMP<R1X>>::id ,obj2 ,address (obj2) ,borrow (y :TEMP<R1X>) => {
		constant r1x = x ;
		constant r2x = y ;
		x = r2x ;
		y = r1x ;
	})) ;
} ;

trait HASH_HELP<ARGS> {
	require (ENUM_EQ<COUNTOF<ARGS> ,ZERO>) ;

	function hash = () => FLAG (-3750763034362895579) ;
} ;

trait HASH_HELP<ARGS> {
	require (ENUM_GT<COUNTOF<ARGS> ,ZERO>) ;

	function hash = (... ,last) => {
		constant r1x = HASH_HELP<TYPE_REST_LAST<ARGS>>::hash (...) ;
		constant r2x = FLAG (FEAT (r1x) ^ FEAT (last)) ;
		return r2x * FLAG (1099511628211) ;
	} ;
} ;

function hash = (...) => {
	constant r1x = HASH_HELP<type (...)>::hash (...) ;
	if (r1x >= 0)
		return r1x ;
	return -r1x - 1 ;
} ;

function min = (obj1 ,obj2) => {
	if (obj1 <= obj2)
		return obj1 ;
	return obj2 ;
} ;

function max = (obj1 ,obj2) => {
	if (obj1 >= obj2)
		return obj1 ;
	return obj2 ;
} ;

trait SLICE_HELP<REAL> {
	class Slice {
		interface Holder ;
		class ImplHolder ;
		class ConcatHolder ;

		constant mPointer :(:(:Holder)) ;
	} ;

	interface Slice::Holder {
		function size = () :LENGTH => virtual ;
		function get = (index :INDEX) :REAL => virtual ;
	} ;

	trait SLICE_IMPLHOLDER_HELP<WRAP> {
		class Slice::ImplHolder {
			require (IS_STRUCT<WRAP>) ;

			constant mTuple :WRAP ;
			constant mSize :LENGTH ;
			constant mHashCode :FLAG ;
		} ;

		implement Slice::ImplHolder {
			function new = () => delete ;

			function new = (that :WRAP) => {
				mTuple = that ;
				mSize = mTuple.count () ;
				mHashCode = mTuple.hashcode () ;
			} ;
		} ;

		implement Slice::ImplHolder :Holder {
			function size = () => mSize ;

			function hashcode = () => mHashCode ;

			function get = (index :INDEX) => mTuple.get (index) ;
		} ;
	} ;

	class Slice::ConcatHolder {
		constant mHead :Slice ;
		constant mTail :Slice ;
		constant mHeadSize :INDEX ;
		constant mSize :LENGTH ;
		constant mHashCode :FLAG ;
	} ;

	implement Slice::ImplHolder {
		function new = () => delete ;

		function new = (head :Slice ,tail :Slice) => {
			mHead = head ;
			mTail = tail ;
			mHeadSize = head.size () ;
			mSize = mHeadSize + tail.size () ;
			constant r1x = mHead.mPointer (borrow (x :Holder) => x.hashcode ()) ;
			constant r2x = mTail.mPointer (borrow (x :Holder) => x.hashcode ()) ;
			mHashCode = hash (r1x ,r2x) ;
		} ;
	} ;

	implement Slice::ConcatHolder :Holder {
		function size = () => mSize ;

		function hashcode = () => mHashCode ;

		function get = (index :INDEX) => {
			if (index < mHeadSize)
				return mHead.get (index) ;
			return mTail.get (index - mHeadSize) ;
		} ;
	} ;

	implement Slice {
		function new = () => {
			mPointer = NULL ;
		} ;
		
		function new = (id1 ,that) => {
			using R1X = type (that) ;
			static constant M_HOLDER = SLICE_IMPLHOLDER_HELP<R1X>::ImplHolder (that) ;
			mPointer = (rc :(:Holder)) => rc (M_HOLDER) ;
		} ;
		
		function new = (id1 ,head :Slice ,tail :Slice) => {
			static constant M_HOLDER = ConcatHolder (head ,tail) ;
			mPointer = (rc :(:Holder)) => rc (M_HOLDER) ;
		} ;

		function size = () => {
			if (mPointer == NULL)
				return ZERO ;
			return mPointer (borrow (x :Holder) => x.size ()) ;
		} ;
		
		function get = (index :INDEX) => {
			rust::assert (between (index ,0 ,size ())) ;
			return mPointer (borrow (x :Holder) => x.get (index)) ;
		} ;
		
		function concat = (that :Slice) => Slice (P0 ,this ,that) ;
		
		function equal = (that :Slice) => {
			if (size () != that.size ())
				return FALSE ;
			if (hashcode () != that.hashcode ())
				return FALSE ;
			for (i in range (0 ,size ())) {
				if (get (i) != that.get (i))
					return FALSE ;
			}
			return TRUE ;
		} ;
		
		function compr = (that :Slice) => {
			constant r1x = min (size () ,that.size ()) ;
			for (i in range (0 ,r1x)) {
				constant r4x = get (i) <=> that.get (i) ;
				if (r4x != ZERO)
					return r4x ;
			}
			constant r3x = size () <=> that.size () ;
			if (r3x != ZERO)
				return r3x ;
			return ZERO ;
		} ;
	} ;
} ;

using Slice<REAL> = SLICE_HELP<REAL>::Slice ;

class Class {
	interface Holder ;
	class Reflection ;
	class ImplHolder ;

	constant mPointer :(:(:Holder)) ;
} ;

interface Class::Holder {
	function type_hash = () :FLAG => virtual ;
	function type_align = () :LENGTH => virtual ;
	function type_size = () :LENGTH => virtual ;
	function type_name = () :Slice<STR> => virtual ;
} ;

trait CLASS_IMPLHOLDER_HELP<WRAP> {
	class Class::ImplHolder {} ;

	implement Class::ImplHolder :Holder {
		function type_hash = () => address (this) ;

		function type_align = () => ALIGNOF<WRAP>::value ;

		function type_size = () => SIZEOF<WRAP>::value ;

		function type_name = () => {
			constant r1x = () => {} ;
			using R1X = type (r1x) ;
			return Slice<STR> (type<R1X>::value ,rust::func_name) ;
		} ;
	} ;
} ;

implement Class {
	function new = () => delete ;

	function new = (id1) => {
		using R1X = type (id1) ;
		static constant M_HOLDER = CLASS_IMPLHOLDER_HELP<R1X>::ImplHolder () ;
		mPointer = (rc :(:Holder)) => rc (M_HOLDER) ;
	} ;
	
	function type_hash = () => mPointer (borrow (x :Holder) => x.type_hash ()) ;

	function type_align = () => mPointer (borrow (x :Holder) => x.type_align ()) ;

	function type_size = () => mPointer (borrow (x :Holder) => x.type_size ()) ;

	function type_name = () => mPointer (borrow (x :Holder) => x.type_name ()) ;
	
	function equal = (that :Class) => {
		if (type_hash () != that.type_hash ())
			return FALSE ;
		if (type_name () != that.type_name ())
			return FALSE ;
		return TRUE ;
	} ;
	
	function compr = (that :Class) => {
		constant r1x = type_hash () <=> that.type_hash () ;
		if (r1x != ZERO)
			return r1x ;
		constant r2x = type_name () <=> that.type_name () ;
		if (r2x != ZERO)
			return r2x ;
		return ZERO ;
	} ;
} ;

class Exception {
	constant mWhat :Slice<STR> ;
} ;

implement Exception {
	function new = () => default ;

	function new = (that :Slice<STR>) => {
		mWhat = that ;
	} ;

	function what = () => mWhat ;

	function raise = () => {
		throw this ;
	} ;
} ;

class Iterator {
	constant mBegin :INDEX ;
	constant mEnd :INDEX ;
	constant mNext :(:INDEX) :INDEX ;
	variable mIndex :INDEX ;
} ;

implement Iterator {
	function new = () => delete ;

	function new = (begin :INDEX ,end :INDEX ,next :(:INDEX) :INDEX) => {
		mBegin = begin ;
		mEnd = end ;
		mNext = next ;
		mIndex = mBegin ;
	} ;
} ;

implement Iterator {
	function good = () => mIndex != mEnd ;

	function next = () => {
		mIndex = mNext (mIndex) ;
	} ;

	function get = () => mIndex ;
} ;

class RangeIterator {
	constant mBegin :INDEX ;
	constant mEnd :INDEX ;
	constant mNext :(:INDEX) :INDEX ;
} ;

implement RangeIterator {
	function new = () => delete ;

	function new = (begin :INDEX ,end :INDEX) => {
		static constant M_NEXT = (x :INDEX) => x + 1 ;
		mBegin = begin ;
		mEnd = max (begin ,end) ;
		mNext = M_NEXT ;
	} ;

	function range_for = () => Iterator (mBegin ,mEnd ,mNext) ;
} ;

function range = (begin :INDEX ,end :INDEX) => RangeIterator (begin ,end) ;