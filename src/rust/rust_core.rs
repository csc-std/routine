
module rust::core ;

import module rust ;

using BOOL = rust::bool ;

static constant TRUE = BOOL (rust::true) ;
static constant FALSE = BOOL (rust::false) ;

using VAR32 = rust::int32 ;
using VAR64 = rust::int64 ;

static constant VAR32_MAX = VAR32 (+2147483647) ;
static constant VAR32_MIN = VAR32 (-2147483648) ;
static constant VAR64_MAX = VAR64 (+9223372036854775807) ;
static constant VAR64_MIN = VAR64 (-9223372036854775808) ;

private trait VAR_HELP {
	require (macro ("config_int32")) ;

	using VAR = VAR32 ;

	static constant VAR_MAX = VAR32_MAX ;
	static constant VAR_MIN = VAR32_MIN ;
} ;

private trait VAR_HELP {
	require (macro ("config_int64")) ;

	using VAR = VAR64 ;

	static constant VAR_MAX = VAR64_MAX ;
	static constant VAR_MIN = VAR64_MIN ;
} ;

using VAR = VAR_HELP::VAR ;

static constant VAR_MAX = VAR_HELP::VAR_MAX ;
static constant VAR_MIN = VAR_HELP::VAR_MIN ;

static constant USED = VAR (-2) ;
static constant NONE = VAR (-1) ;
static constant ZERO = VAR (+0) ;
static constant IDEN = VAR (+1) ;

using INDEX = VAR ;
using LENGTH = VAR ;
using FLAG = VAR ;

static constant EQUAL = ZERO ;

using FLOAT32 = rust::float32 ;
using FLOAT64 = rust::float64 ;

static constant FLOAT32_MAX = FLOAT32 (3.402823466E+38) ;
static constant FLOAT32_MIN = FLOAT32 (1.175494351E-38) ;
static constant FLOAT32_EPS = FLOAT32 (1.192092896E-07) ;
static constant FLOAT32_INF = FLOAT32 (rust::infinity) ;
static constant FLOAT64_MAX = FLOAT64 (1.7976931348623158E+308) ;
static constant FLOAT64_MIN = FLOAT64 (2.2250738585072014E-308) ;
static constant FLOAT64_EPS = FLOAT64 (2.2204460492503131E-016) ;
static constant FLOAT64_INF = FLOAT64 (rust::infinity) ;

using BYTE = rust::byte ;
using WORD = rust::word ;
using CHAR = rust::char ;
using FEAT = rust::feat ;

using STRA = rust::stra ;
using STRU8 = rust::stru8 ;
using STRU16 = rust::stru16 ;
using STRU32 = rust::stru32 ;

private trait STR_HELP {
	require (macro ("config_stra")) ;

	using STR = STRA ;
} ;

private trait STR_HELP {
	require (macro ("config_stru8")) ;

	using STR = STRU8 ;
} ;

private trait STR_HELP {
	require (macro ("config_stru16")) ;

	using STR = STRU16 ;
} ;

private trait STR_HELP {
	require (macro ("config_stru32")) ;

	using STR = STRU32 ;
} ;

using STR = STR_HELP::STR ;

static constant NULL = rust::null ;

define _ENUM_(...) rust::enum (...)

define _TYPE_(...) rust::type (...)

using ENUM_USED = _ENUM_ (-2) ;
using ENUM_NONE = _ENUM_ (-1) ;
using ENUM_ZERO = _ENUM_ (+0) ;
using ENUM_IDEN = _ENUM_ (+1) ;

using ALIGNOF<UNIT> = _ENUM_ (rust::alignof (UNIT)) ;
using SIZEOF<UNIT> = _ENUM_ (rust::sizeof (UNIT)) ;
using COUNTOF<UNIT> = _ENUM_ (rust::countof (UNIT)) ;

using DEF<UNIT> = UNIT ;

using PTR<UNIT> = () :UNIT ;

using CALL<UNIT> = UNIT::RET ;

private trait ENUM_CHECK_HELP<ARG1> {
	require (IS_ENUM<EXPR>) ;

	using RET = ARG1 ;
} ;

private trait ENUM_ALL_HELP<ARGS> {
	require (ENUM_EQ<COUNTOF<ARGS> ,ENUM_ZERO>) ;

	using RET = ENUM_IDEN ;
} ;

private trait ENUM_ALL_HELP<ARGS> {
	require (ENUM_GT<COUNTOF<ARGS> ,ENUM_ZERO>) ;

	using R1X = TYPE_FIRST<ARGS> ;
	using R2X = CALL<ENUM_ALL_HELP<TYPE_FIRST_REST<ARGS>>> ;
	using RET = ENUM_AND<R1X ,R2X> ;
} ;

private trait ENUM_ANY_HELP<ARGS> {
	require (ENUM_EQ<COUNTOF<ARGS> ,ENUM_ZERO>) ;

	using RET = ENUM_ZERO ;
} ;

private trait ENUM_ANY_HELP<ARGS> {
	require (ENUM_GT<COUNTOF<ARGS> ,ENUM_ZERO>) ;

	using R1X = TYPE_FIRST<ARGS> ;
	using R2X = CALL<ENUM_ANY_HELP<TYPE_FIRST_REST<ARGS>>> ;
	using RET = ENUM_OR<R1X ,R2X> ;
} ;

using ENUM_CHECK<EXPR> = CALL<ENUM_CHECK_HELP<EXPR>> ;
using ENUM_AND<EXPR1 ,EXPR2> = _ENUM_ (ENUM_CHECK<EXPR1>::value && ENUM_CHECK<EXPR2>::value) ;
using ENUM_OR<EXPR1 ,EXPR2> = _ENUM_ (ENUM_CHECK<EXPR1>::value || ENUM_CHECK<EXPR2>::value) ;
using ENUM_ALL<...> = CALL<ENUM_ALL_HELP<type<...>>> ;
using ENUM_ANY<...> = CALL<ENUM_ANY_HELP<type<...>>> ;
using ENUM_NOT<EXPR> = _ENUM_ (!ENUM_CHECK<EXPR>::value) ;
using ENUM_EQ<EXPR1 ,EXPR2> = _ENUM_ (ENUM_CHECK<EXPR1>::value == ENUM_CHECK<EXPR2>::value) ;
using ENUM_NOT_EQ<EXPR1 ,EXPR2> = ENUM_NOT<ENUM_EQ<EXPR1 ,EXPR2>> ;
using ENUM_COMPR<EXPR1 ,EXPR2> = _ENUM_ (ENUM_CHECK<EXPR1>::value <=> ENUM_CHECK<EXPR2>::value) ;
using ENUM_LT<EXPR1 ,EXPR2> = _ENUM_ (ENUM_COMPR<EXPR1 ,EXPR2>::value < EQUAL) ;
using ENUM_GT<EXPR1 ,EXPR2> = _ENUM_ (ENUM_COMPR<EXPR1 ,EXPR2>::value > EQUAL) ;
using ENUM_LT_EQ<EXPR1 ,EXPR2> = _ENUM_ (ENUM_COMPR<EXPR1 ,EXPR2>::value <= EQUAL) ;
using ENUM_GT_EQ<EXPR1 ,EXPR2> = _ENUM_ (ENUM_COMPR<EXPR1 ,EXPR2>::value >= EQUAL) ;
using ENUM_BETWEEN<EXPR ,BEGIN ,END> = ENUM_AND<ENUM_GT_EQ<EXPR ,BEGIN> ,ENUM_LT<EXPR ,END>> ;
using ENUM_ADD<EXPR1 ,EXPR2> = _ENUM_ (ENUM_CHECK<EXPR1>::value + ENUM_CHECK<EXPR2>::value) ;
using ENUM_SUB<EXPR1 ,EXPR2> = _ENUM_ (ENUM_CHECK<EXPR1>::value - ENUM_CHECK<EXPR2>::value) ;
using ENUM_MUL<EXPR1 ,EXPR2> = _ENUM_ (ENUM_CHECK<EXPR1>::value * ENUM_CHECK<EXPR2>::value) ;
using ENUM_DIV<EXPR1 ,EXPR2> = _ENUM_ (ENUM_CHECK<EXPR1>::value / ENUM_CHECK<EXPR2>::value) ;
using ENUM_MOD<EXPR1 ,EXPR2> = _ENUM_ (ENUM_CHECK<EXPR1>::value % ENUM_CHECK<EXPR2>::value) ;
using ENUM_MAX<EXPR1 ,EXPR2> = CONDITIONAL<ENUM_GT_EQ<EXPR1 ,EXPR2> ,EXPR1 ,EXPR2> ;
using ENUM_MIN<EXPR1 ,EXPR2> = CONDITIONAL<ENUM_LT_EQ<EXPR1 ,EXPR2> ,EXPR1 ,EXPR2> ;

private trait PLACEHOLDER_HELP<ARG1> {
	require (ENUM_EQ<ARG1 ,ENUM_ZERO>) ;

	class PLACEHOLDER {} ;
} ;

private trait PLACEHOLDER_HELP<ARG1> {
	require (ENUM_GT<ARG1 ,ENUM_ZERO>) ;

	using R1X = PLACEHOLDER_HELP<ENUM_DECREASE<ARG1>>::PLACEHOLDER ;

	class PLACEHOLDER {
		public extend :R1X ;
	} ;
} ;

using PLACEHOLDER<RANK> = PLACEHOLDER_HELP<RANK>::PLACEHOLDER ;

static constant P0 = PLACEHOLDER<_ENUM_ (0)> () ;
static constant P1 = PLACEHOLDER<_ENUM_ (1)> () ;
static constant P2 = PLACEHOLDER<_ENUM_ (2)> () ;
static constant P3 = PLACEHOLDER<_ENUM_ (3)> () ;
static constant P4 = PLACEHOLDER<_ENUM_ (4)> () ;
static constant P5 = PLACEHOLDER<_ENUM_ (5)> () ;
static constant P6 = PLACEHOLDER<_ENUM_ (6)> () ;
static constant P7 = PLACEHOLDER<_ENUM_ (7)> () ;
static constant P8 = PLACEHOLDER<_ENUM_ (8)> () ;
static constant P9 = PLACEHOLDER<_ENUM_ (9)> () ;
static constant PX = PLACEHOLDER<_ENUM_ (10)> () ;

private trait CONDITIONAL_HELP<ARG1 ,ARG2 ,ARG3> {
	require (ARG1) ;

	using RET = ARG2 ;
} ;

private trait CONDITIONAL_HELP<ARG1 ,ARG2 ,ARG3> {
	require (ENUM_NOT<ARG1>) ;

	using RET = ARG3 ;
} ;

private trait IS_ALL_SAME_HELP<ARGS> {
	require (ENUM_EQ<COUNTOF<ARGS> ,ENUM_ZERO>) ;

	using RET = ENUM_IDEN ;
} ;

private trait IS_ALL_SAME_HELP<ARGS> {
	require (ENUM_EQ<COUNTOF<ARGS> ,ENUM_IDEN>) ;

	using RET = ENUM_IDEN ;
} ;

private trait IS_ALL_SAME_HELP<ARGS> {
	require (ENUM_GT<COUNTOF<ARGS> ,ENUM_IDEN>) ;

	using R1X = TYPE_FIRST<ARGS> ;
	using R2X = TYPE_SECOND<ARGS> ;
	using R3X = CALL<IS_ALL_SAME_HELP<type<R1X ,TYPE_SECOND_REST<ARGS>...>>> ;
	using RET = ENUM_ALL<IS_SAME<R1X ,R2X> ,R3X> ;
} ;

private trait IS_ANY_SAME<ARGS> {
	require (ENUM_EQ<COUNTOF<ARGS> ,ENUM_ZERO>) ;

	using RET = ENUM_ZERO ;
} ;

private trait IS_ANY_SAME<ARGS> {
	require (ENUM_EQ<COUNTOF<ARGS> ,ENUM_IDEN>) ;

	using RET = ENUM_ZERO ;
} ;

private trait IS_ANY_SAME<ARGS> {
	require (ENUM_GT<COUNTOF<ARGS> ,ENUM_IDEN>) ;

	using R1X = TYPE_FIRST<ARGS> ;
	using R2X = TYPE_SECOND<ARGS> ;
	using R3X = CALL<IS_ANY_SAME<type<R1X ,TYPE_SECOND_REST<ARGS>...>>> ;
	using R4X = CALL<IS_ANY_SAME<type<R2X ,TYPE_SECOND_REST<ARGS>...>>> ;
	using RET = ENUM_ANY<IS_SAME<R1X ,R2X> ,R3X ,R4X> ;
} ;

using CONDITIONAL<COND ,YES ,NO> = CALL<CONDITIONAL_HELP<COND ,YES ,NO>> ;

using IS_SAME<UNIT1 ,UNIT2> = concept (UNIT1 as UNIT2) ;
using IS_ALL_SAME<...> = CALL<IS_ALL_SAME_HELP<type<...>>> ;
using IS_ANY_SAME<...> = CALL<IS_ANY_SAME_HELP<type<...>>> ;

using IS_BOOL<UNIT> = IS_SAME<UNIT ,BOOL> ;
using IS_VAR<UNIT> = ENUM_ALL<IS_SAME<UNIT ,VAR32> ,IS_SAME<UNIT ,VAR64>> ;
using IS_FLOAT<UNIT> = ENUM_ALL<IS_SAME<UNIT ,FLOAT32> ,IS_SAME<UNIT ,FLOAT64>> ;
using IS_BYTE<UNIT> = ENUM_ALL<IS_SAME<UNIT ,BYTE> ,IS_SAME<UNIT ,WORD> ,IS_SAME<UNIT ,CHAR> ,IS_SAME<UNIT ,FEAT>> ;
using IS_STR<UNIT> = ENUM_ALL<IS_SAME<UNIT ,STRA> ,IS_SAME<UNIT ,STRU8> ,IS_SAME<UNIT ,STRU16> ,IS_SAME<UNIT ,STRU32>> ;
using IS_BASIC<UNIT> = ENUM_ALL<IS_BOOL<UNIT> ,IS_VAR<UNIT> ,IS_FLOAT<UNIT> ,IS_BYTE<UNIT> ,IS_STR<UNIT>> ;

using IS_ENUM<UNIT> = concept (UNIT as "enum") ;

using IS_TYPE<UNIT> = concept (UNIT as "type") ;

using TYPE_FIRST<ALL> = ALL::FIRST ;
using TYPE_SECOND<ALL> = ALL::SECOND ;
using TYPE_FIRST_REST<ALL> = ALL::FIRST_REST ;
using TYPE_SECOND_REST<ALL> = ALL::SECOND_REST ;
using TYPE_CAT<UNIT1 ,UNIT2> = type<UNIT1... ,UNIT2...> ;
using TYPE_GET<ALL ,POS> = TYPE_GET_HELP<ALL ,POS> ;
using TYPE_FIND<ALL ,KEY> = TYPE_FIND_HELP<ALL ,KEY> ;
using TYPE_REPEAT<UNIT ,SIZE> = TYPE_REPEAT_HELP<UNIT ,SIZE> ;

using IS_PLACEHOLDER<UNIT> = concept (UNIT as class PLACEHOLDER) ;

using IS_TEMP<UNIT> = concept (UNIT as class TEMP) ;
using REMOVE_TEMP<UNIT> = rust::REMOVE_TEMP_HELP<UNIT> ;

using IS_STRUCT<UNIT> = concept (UNIT as "[...:ARGS]") ;
using REFLECT_STRUCT<UNIT> = CALL<rust::REFLECT_STRUCT_HELP<UNIT>> ;
using STRUCT_BIND<PARAMS> = [...:PARAMS] ;

using IS_FUNCTION<UNIT> = concept (UNIT as "(...:ARGS) :ARG1") ;
using REMOVE_FUNCTION<UNIT> = CALL<rust::REMOVE_FUNCTION_HELP<UNIT>> ;
using REFLECT_FUNCTION<UNIT> = CALL<rust::REFLECT_FUNCTION_HELP<UNIT>> ;
using FUNCTION_BIND<RETURN ,PARAMS> = (...:PARAMS) :RETURN ;

using IS_TRIVIAL<UNIT> = _ENUM_ (rust::is_trivial (UNIT)) ;
using IS_INTERFACE<UNIT> = _ENUM_ (rust::is_interface (UNIT)) ;

using IS_CLASS<UNIT> = _ENUM_ (rust::is_class (UNIT)) ;
using IS_CLASS_CLONEABLE<UNIT> = concept (UNIT::clone) ;
using IS_CLASS_SHAREABLE<UNIT> = concept (UNIT::share) ;
using IS_CONSTRUCTIBLE<UNIT ,ALL> = concept () ;
using IS_CONVERTIBLE<FROM ,TO> = concept () ;
using IS_EXTEND<BASE ,DERIVE> = concept ("class DERIVE { extend :BASE ; }") ;
using IS_IMPLEMENT<BASE ,DERIVE> = concept ("implement DERIVE :BASE") ;

using BYTE_TRAIT<UNIT> = CALL<BYTE_TRAIT_HELP<UNIT>> ;

define _ASSERT_(...) switch { if (...) discard ; Exception ("assert failed : " ++ rust::literal (...) ++ " : at " ++ rust::function_name ++ " in " ++ rust::file_name ++ " ," ++ rust::line_name).raise () ; }

function noop = () => {
	_ASSERT_ (TRUE) ;
} ;

function unimplemented = () => {
	_ASSERT_ (FALSE) ;
} ;

function address = (obj) => {
	##???##
} ;

function alignas = (base :LENGTH ,align :LENGTH) => {
	return base + (align - base % align) % align ;
} ;

function load = (id1 ,owner ,addr :LENGTH) => {
	using R1X = _TYPE_ (id1) ;
	using R2X = _TYPE_ (owner) ;
	require (IS_FUNCTION<R2X>) ;
	##???##
} ;

function swap = (obj1 ,obj2) => {
	using R1X = _TYPE_ (obj1) ;
	using R2X = _TYPE_ (obj2) ;
	require (IS_SAME<R1X ,R2X>) ;
	##???##
} ;

function hash = (...) => HASH_HELP<_TYPE_ (...)>::hash (...) ;

function between = (obj :INDEX ,begin :INDEX ,end :INDEX) => {
	return obj >= begin && obj < end ;
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

private trait SYNTAX_HELP<UNIT> {
	class Syntax {
		constant mPointer :PTR<UNIT> ;
	} ;

	implement Syntax {
		function new = () => delete ;

		function new = (that :UNIT) => {
			mPointer = PTR<UNIT> => that ;
		} ;
	} ;

	implement Syntax :Wrapped<UNIT> {
		function to = () => mPointer ;
	} ;
} ;

using Syntax<UNIT> = SYNTAX_HELP<UNIT>::Syntax ;

using UNION<ALIGN ,SIZE> = UNION_HELP<ALIGN ,SIZE>::UNION ;

private trait TEMP_HELP<UNIT> {
	class TEMP {
		variable mStorage :UNION<ALIGNOF<UNIT> ,SIZEOF<UNIT>> ;
	} ;	

	implement TEMP {
		function new = () => default ;

		function new = (that) => {
			using R1X = _TYPE_ (that) ;
			using R2X = _TYPE_ (NULL) ;
			require (IS_SAME<R1X ,R2X>) ;
			mStorage = UNION<ALIGNOF<UNIT> ,SIZEOF<UNIT>> => zeroize ;
		} ;

		function swap = mutable (that :TEMP) => {
			variable rax = mStorage ;
			mStorage = that.mStorage ;
			that.mStorage = rax ;
		} ;
	} ;
} ;

using TEMP<UNIT> = TEMP_HELP<UNIT>::TEMP ;

private trait SLICE_HELP<REAL> {
	class Slice {
		interface Holder ;
		class ImplHolder ;
		class ConcatHolder ;

		constant mPointer :PTR<Holder> ;
	} ;

	interface Slice::Holder {
		function size = () :LENGTH => virtual ;
		function get = (index :INDEX) :REAL => virtual ;
	} ;

	private trait SLICE_IMPLHOLDER_HELP<WRAP> {
		class Slice::ImplHolder {
			require (IS_STRUCT<WRAP>) ;

			constant mTuple :PTR<WRAP> ;
			constant mSize :LENGTH ;
			constant mHashCode :FLAG ;
		} ;

		implement Slice::ImplHolder {
			function new = () => delete ;

			function new = (that :PTR<WRAP>) => {
				mTuple = that ;
				mSize = mTuple->count () ;
				mHashCode = mTuple->hashcode () ;
			} ;
		} ;

		implement Slice::ImplHolder :Holder {
			function size = () => mSize ;

			function hashcode = () => mHashCode ;

			function get = (index :INDEX) => mTuple->[index] ;
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
			mHashCode = hash (mHead->hashcode () ,mTail->hashcode ()) ;
		} ;
	} ;

	implement Slice::ConcatHolder :Holder {
		function size = () => mSize ;

		function hashcode = () => mHashCode ;

		function get = (index :INDEX) => {
			if (index < mHeadSize)
				return mHead.[index] ;
			return mTail.[index - mHeadSize] ;
		} ;
	} ;

	implement Slice {
		function new = () => {
			mPointer = NULL ;
		} ;
		
		function new = (id1 ,that) => {
			using R1X = _TYPE_ (that) ;
			using R2X = REMOVE_FUNCTION<R1X> ;
			constant r1x = PTR<R2X> => that ;
			static constant M_HOLDER = SLICE_IMPLHOLDER_HELP<R2X>::ImplHolder (r1x) ;
			mPointer = PTR<Holder> => M_HOLDER ;
		} ;
		
		function new = (id1 ,head :Slice ,tail :Slice) => {
			static constant M_HOLDER = ConcatHolder (head ,tail) ;
			mPointer = PTR<Holder> => M_HOLDER ;
		} ;

		function size = () => {
			if (mPointer == NULL)
				return ZERO ;
			return mPointer->size () ;
		} ;
	} ;

	implement Slice :Getable {
		function get = (index :INDEX) => {
			_ASSERT_ (between (index ,0 ,size ())) ;
			return mPointer->get (index) ;
		} ;
	} ;
	
	implement Slice :Concatable {	
		function concat = (that :Slice) => Slice (P0 ,this ,that) ;
	} ;

	implement Slice :Equalable<Slice> {
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
	} ;

	implement Slice :Comprable<Slice> {
		function compr = (that :Slice) => {
			constant r1x = min (size () ,that.size ()) ;
			for (i in range (0 ,r1x)) {
				constant r4x = get (i) <=> that.get (i) ;
				if (r4x != EQUAL)
					return r4x ;
			}
			constant r3x = size () <=> that.size () ;
			if (r3x != EQUAL)
				return r3x ;
			return EQUAL ;
		} ;
	} ;
} ;

using Slice<REAL> = SLICE_HELP<REAL>::Slice ;

class Class {
	interface Holder ;
	class Reflection ;
	class ImplHolder ;

	constant mPointer :PTR<Holder> ;
} ;

interface Class::Holder {
	function type_hash = () :FLAG => virtual ;
	function type_align = () :LENGTH => virtual ;
	function type_size = () :LENGTH => virtual ;
	function type_name = () :Slice<STR> => virtual ;
	function reflect = () :PTR<Reflection> => virtual ;
} ;

class Class::Reflection {
	public constant mType :Class ;
	public constant mOffset :LENGTH ;
	public constant mMember :Slice<STR> ;
	public constant mPrev :PTR<Reflection> ;
	public constant mNext :PTR<Reflection> ;
} ;

private trait CLASS_IMPLHOLDER_HELP<WRAP> {
	class Class::ImplHolder {} ;

	implement Class::ImplHolder :Holder {
		function type_hash = () => address (this) ;

		function type_align = () => ALIGNOF<WRAP>::value ;

		function type_size = () => SIZEOF<WRAP>::value ;

		function type_name = () => {
			constant r1x = () => {} ;
			using R1X = _TYPE_ (r1x) ;
			return Slice<STR> (type<R1X>::value ,rust::func_name) ;
		} ;

		function reflect = () => {
			##???##
			return PTR<Reflection> (NULL) ;
		} ;
	} ;
} ;

implement Class {
	function new = () => delete ;

	function new = (id1) => {
		using R1X = _TYPE_ (id1) ;
		static constant M_HOLDER = CLASS_IMPLHOLDER_HELP<R1X>::ImplHolder () ;
		mPointer = PTR<Holder> => M_HOLDER ;
	} ;
	
	function type_hash = () => mPointer->type_hash () ;

	function type_align = () => mPointer->type_align () ;

	function type_size = () => mPointer->type_size () ;

	function type_name = () => mPointer->type_name () ;
} ;

implement Class :Equalable<Slice> {
	function equal = (that :Class) => {
		if (type_hash () != that.type_hash ())
			return FALSE ;
		if (type_name () != that.type_name ())
			return FALSE ;
		return TRUE ;
	} ;
} ;

implement Class :Comprable<Slice> {
	function compr = (that :Class) => {
		constant r1x = type_hash () <=> that.type_hash () ;
		if (r1x != EQUAL)
			return r1x ;
		constant r2x = type_name () <=> that.type_name () ;
		if (r2x != EQUAL)
			return r2x ;
		return EQUAL ;
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

interface Iteratable {
	function ibegin = () :INDEX => virtual ;
	function iend = () :INDEX => virtual ;
	function inext = (index :INDEX) :INDEX => virtual ;
} ;

class Iterator {
	constant mArray :PTR<Iteratable> ;
	constant mEnd :INDEX ;
	variable mIndex :INDEX ;
} ;

implement Iterator {
	function new = () => delete ;

	function new = (array :PTR<Iteratable>) => {
		mArray = array ;
		mIndex = mArray->ibegin () ;
		mEnd = mArray->iend () ;
	} ;
} ;

implement Iterator {
	function next = mutable () => {
		mIndex = mArray->inext (mIndex) ;
	} ;

	function good = () => mIndex != mEnd ;

	function get = () => mIndex ;
} ;

class RangeIterator {
	constant mBegin :INDEX ;
	constant mEnd :INDEX ;
} ;

implement RangeIterator {
	function new = () => delete ;

	function new = (begin :INDEX ,end :INDEX) => {
		mBegin = begin ;
		mEnd = max (begin ,end) ;
	} ;
} ;

implement RangeIterator :Iteratable {
	function ibegin = () => mBegin ;

	function iend = () => mEnd ;

	function inext = (index :INDEX) => index + 1 ;
} ;

function range = (begin :INDEX ,end :INDEX) => RangeIterator (begin ,end) ;

class Reference {
	public constant mPointer :() ;
} ;

implement Reference {
	function new = () => {
		mPointer = NULL ;
	} ;

	function new = (that) => {
		mPointer = that.mPointer ;
	} ;
} ;

private trait SAFEREFERENCE_HELP<UNIT> {
	class SafeReference {
		constant mPointer :PTR<UNIT> ;
	} ;

	implement SafeReference {
		function new = () => delete ;

		private trait NEW_HELP<ARG1> {
			require (IS_SAME<ARG1 ,PTR<UNIT>>) ;
			
			function new = (that :PTR<UNIT>) => {
				mPointer = that ;
			} ;
		} ;

		private trait NEW_HELP<ARG1> {
			require (IS_SAME<ARG1 ,Reference>) ;

			function new = (that :Reference) => {
				_ASSERT_ (that.mPointer != NULL) ;
				mPointer = that.mPointer ;
			} ;
		} ;

		function new = (that) => NEW_HELP<_TYPE_ (that)>::new (that) ;
	} ;

	implement SafeReference :Wrapped<UNIT> {
		function to = () => mPointer ;
	} ;
} ;

using SafeReference<UNIT> = SAFEREFERENCE_HELP<UNIT>::SafeReference ;