module rust::basic ;

import module rust::core::* ;

trait TUPLE_HELP<ARG1> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;
	
	class Tuple {} ;

	implement Tuple {
		function new = () => default ;

		function clone = () :Tuple => Tuple () ;
		
		function capacity = () :LENGTH => ZERO ;

		function equal = (that :Tuple) :BOOL => TRUE ;

		function compr = (that :Tuple) :FLAG => ZERO ;

		function hash = () :FLAG => hashcode () ;
	} ;
} ;

trait TUPLE_HELP<ARG1> {
	require (ENUM_GT_ZERO<COUNTOF<ARG1>>) ;

	using ALL = TYPE_CHECK<ARG1> ;
	using UNIT = TYPE_FIRST_ONE<ALL> ;
	using REST = TYPE_FIRST_REST<ALL> ;
	using BASE = typename TUPLE_HELP<REST>::Tuple ;
	
	class Tuple {
		extend mSuper :BASE ;
		variable mValue :UNIT ;
	} ;

	implement Tuple {
		function new = () => default ;

		function new = (that :UNIT ,rest... :REST...) => {
			mValue = forward (that) ;
			mSuper = BASE (rest...) ;
		} ;

		trait CLONE_HELP<ARG3> {
			require (ENUM_EQ_ZERO<ARG3>) ;

			function clone = (params ,initval...) :Tuple => Tuple (initval...) ;
		} ;

		trait CLONE_HELP<ARG3> {
			require (ENUM_GT_ZERO<ARG3>) ;

			function clone = (params ,initval...) :Tuple => CLONE_HELP<ENUM_DEC<ARG3>>::clone (params.rest ,initial... ,params.one) ;
		} ;

		function clone = () :Tuple => CLONE_HELP<COUNTOF<REST>>::clone (mSuper ,mValue) ;

		function capacity = () :LENGTH => COUNTOF<ALL>::value ;

		property one = [] :UNIT => mValue ;

		property rest = [] :BASE => mSuper ;

		trait PICK_HELP<ARG3> {
			require (ENUM_EQ_ZERO<ARG3>) ;

			property pick = [] => one[] ;
		} ;

		trait PICK_HELP<ARG3> {
			require (ENUM_GT_ZERO<ARG3>) ;

			using R1X = ENUM_DEC<ARG3> ;

			property pick = [] => rest.pick[type<R1X>::id] ;
		} ;

		property pick = [nth] => {
			using R1X = type (nth) ;
			require (IS_ENUM<R1X>) ;
			require (ENUM_BETWEEN<R1X ,ENUM_ZERO ,COUNTOF<ALL>>) ;
			return PICK_HELP<R1X>::pick[] ;
		} ;

		function equal = (that :Tuple) :BOOL => {
			if (mValue != that.mValue)
				return FALSE ;
			if (mSuper != that.mSuper)
				return FALSE ;
			return TRUE ;
		} ;

		function compr = (that :Tuple) :FLAG => {
			constant r1x = mValue <=> that.mValue ;
			if (r1x != ZERO)
				return r1x ;
			constant r2x = mSuper <=> that.mSuper ;
			if (r2x != ZERO)
				return r2x ;
			return ZERO ;
		} ;

		function hash = () :FLAG => {
			constant r1x = operator hash (mValue) ;
			constant r2x = operator hash (mSuper) ;
			return hashcode (r1x ,r2x) ;
		} ;
	} ;
} ;

define Tuple<UNITS...> = typename TUPLE_HELP<UNITS>::Tuple ;

trait STORAGE_HELP<ARG1 ,ARG2> {
	using UNIT = BYTE_TRAIT<ARG1 ,ARG1> ;
	using SIZE = ENUM_DIV<ENUM_DEC<ENUM_ADD<ARG2 ,ARG1>> ,ARG1> ;
	using STORAGE = Tuple<TYPE_REPEAT<UNIT ,SIZE>> ;

	class Storage {
		variable mStorage :STORAGE ;
	} ;

	require (ENUM_EQUAL<SIZEOF<Storage> ,SIZEOF<STORAGE>>) ;

	implement Storage {
		static function zero = () :Storage => {
			require (IS_TRIVIAL<STORAGE>) ;
			variable ret = Storage () ;
			internel::zeroize (ret.mStorage) ;
			return ret ;
		} ;
	} ;
} ;

define Storage<ALIGN ,SIZE> = typename STORAGE_HELP<ALIGN ,SIZE>::Storage ;

trait ENUM_SUMOF_HELP<ARG1> {
	require (ENUM_EQ_IDEN<COUNTOF<ARG1>>) ;

	using RET = TYPE_FIRST_ONE<ARG1> ;
} ;

trait ENUM_SUMOF_HELP<ARG1> {
	require (ENUM_GT_IDEN<COUNTOF<ARG1>>) ;

	using R1X = TYPE_FIRST_ONE<ARG1> ;
	using R2X = typename ENUM_SUMOF_HELP<TYPE_FIRST_REST<ARG1>>::RET ;

	using RET = ENUM_ADD<R1X ,R2X> ;
} ;

define ENUM_SUMOF<UNITS...> typename ENUM_SUMOF_HELP<UNITS>::RET ;

trait ENUM_MAXOF_HELP<ARG1> {
	require (ENUM_EQ_IDEN<COUNTOF<ARG1>>) ;

	using RET = TYPE_FIRST_ONE<ARG1> ;
} ;

trait ENUM_MAXOF_HELP<ARG1> {
	require (ENUM_GT_IDEN<COUNTOF<ARG1>>) ;

	using R1X = TYPE_FIRST_ONE<ARG1> ;
	using R2X = typename ENUM_MAXOF_HELP<TYPE_FIRST_REST<ARG1>>::RET ;

	using RET = CONDITIONAL<ENUM_COMPR_LT<R1X ,R2X> ,R2X ,R1X> ;
} ;

define ENUM_MAXOF<UNITS...> typename ENUM_MAXOF_HELP<UNITS>::RET ;

trait VARIANT_HELP<ARG1> {
	using ALL = TYPE_CHECK<ARG1> ;

	class Variant {
		interface Holder ;
		class ImplHolder ;
	} ;
} ;

define Optional<UNIT> = typename VARIANT_HELP<type<UNIT>>::Variant ;
define Variant<UNITS...> = typename VARIANT_HELP<UNITS>::Variant ;