module rust::basic ;

import module rust::core::* ;

trait AUTOREF_HELP<ARG1> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;

	class AutoRef {
		interface Holder ;

		variable mPointer :Holder ;
	} ;

	interface AutoRef::Holder {
		function copy = () :Holder => virtual ;
		function poll = mutable () :auto => virtual ;
		function push = mutable (obj :Holder) => virtual ;
		property clazz = [] :Clazz => virtual ;
	} ;

	implement AutoRef {
		function new = () => mPointer = NULL ;

		function new = (that) => new (that.rebind ()) ;
		
		function exist = () :BOOL => mPointer != NULL ;

		property clazz = () :Clazz => {
			if (mPointer == NULL)
				return Clazz::nullopt ;
			return mPointer->clazz ;
		} ;

		function rebind_move = () :AutoRef => {
			variable ret = AutoRef () ;		
			swap (ret.mPointer ,mPointer) ;
			return ret ;
		} ;

		function rebind_move = (id) => {
			using R1X = type (id) ;
			using R2X = typename AUTOREF_HELP<type<R1X>>::AutoRef ;
			variable ret = R2X () ;
			swap (ret.mPointer ,mPointer) ;
			return ret ;
		} ;
	} ;
} ;

trait AUTOREF_HELP<ARG1> {
	require (ENUM_GT_ZERO<COUNTOF<ARG1>>) ;

	using UNIT = TYPE_UNWRAP<ARG1> ;
	using BASE = typename AUTOREF_HELP<type<>>::AutoRef ;

	class AutoRef {
		interface Holder ;
		class ImplHolder ;

		extend mSuper :BASE ;
	} ;

	interface AutoRef::Holder = typename BASE::Holder ;

	trait IMPLHOLDER_HELP<ARG1> {
		using UNIT = ARG1 ;

		class AutoRef::ImplHolder {
			variable mValue :UNIT ;
			variable mClazz :Clazz ;
		} ;

		implement AutoRef::ImplHolder {
			function new = (value_ :UNIT) => {
				mValue = forward (value_) ;
				mClazz = Clazz (type<UNIT>::id) ;
			} ;
		} ;
		
		implement AutoRef::ImplHolder :Holder {
			trait COPY_HELP {
				require (IS_CLONEABLE<UNIT>) ;

				function copy = () :Holder => ImplHolder (UNIT (mValue)) ;
			} ;

			trait COPY_HELP {
				require not (IS_CLONEABLE<UNIT>) ;

				function copy = () :Holder => NULL ;
			} ;

			function copy = () :Holder => COPY_HELP::copy () ;

			function poll = mutable () :auto => forward (mValue) ;

			function push = mutable (obj :Holder) => mValue = UNIT (obj.poll ()) ;

			property clazz = [] :Clazz => mClazz ;
		} ;
	} ;

	implement AutoRef {
		function new = () => mSuper = BASE () ;

		function new = (that) => new (that.rebind_move (type<UNIT>::id)) ;

		static function make = (initval...) => {
			using R1X = typename IMPLHOLDER_HELP<UNIT>::ImplHolder ;
			register r1x = UNIT (initval...) ;
			variable ret = AutoRef () ;
			ret.mSuper.mPointer = R1X (r1x) ;
			return ret ;
		} ;
		
		function exist = () :BOOL => mSuper.exist () ;

		property clazz = [] :Clazz => mSuper.clazz () ;

		function rebind_move = () :BASE => mSuper.rebind_move () ;

		function rebind_move = (id) => mSuper.rebind_move (id) ;

		function get = () :UNIT => {
			assert (exist ()) ;
			assert (clazz == Clazz (type<UNIT>::id)) ;
			register r1x = mSuper.mPointer->copy () ;
			return UNIT (r1x->poll ()) ;
		} ;

		function poll = () :UNIT => {
			assert (exist ()) ;
			assert (clazz == Clazz (type<UNIT>::id)) ;
			return UNIT (mSuper.mPointer->poll ()) ;
		} ;

		function push = (that :UNIT) => {
			using R1X = typename IMPLHOLDER_HELP<UNIT>::ImplHolder ;
			assert (exist ()) ;
			assert (clazz == Clazz (type<UNIT>::id)) ;
			register r1x = R1X (forward (that)) ;
			mSuper.mPointer->push (r1x) ;
		} ;
	} ;
} ;

define AutoRef<> = typename AUTOREF_HELP<type<>>::AutoRef ;
define AutoRef<UNIT> = typename AUTOREF_HELP<type<UNIT>>::AutoRef ;

trait FUNCTION_HELP<ARG1 ,ARG2> {
	using RETURN = ARG1 ;
	using PARAMS = TYPE_CHECK<ARG2> ;
	
	class Function {
		interface Holder ;
		class ImplHolder ;

		variable mPointer :Holder ;
	} ;

	interface Function::Holder {
		function is_noexcept_invoke = () :BOOL => virtual ;
		function invoke = (params... :PARAMS...) :RETURN => virtual ;
	} ;

	trait IMPLHOLDER_HELP<ARG1> {
		using UNIT = ARG1 ;

		class Function::ImplHolder {
			variable mValue :UNIT ;
		} ;

		implement Function::ImplHolder {
			function new = (value_ :UNIT) => mValue = forward (value_) ;
		} ;

		implement Function::ImplHolder :Holder {
			function is_noexcept_invoke = () :BOOL => IS_NOEXCEPT<UNIT>::value ;

			function invoke = (params... :PARAMS...) :RETURN => mValue (params...) ;
		} ;
	} ;

	implement Function {
		function new = () => mPointer = NULL ;

		function new = (that) => {
			using R1X = type (that) ;
			using R2X = typename IMPLHOLDER_HELP<R1X>::ImplHolder ;
			mPointer = R2X (that) ;
		} ;
		
		function exist = () :BOOL => mPointer != NULL ;

		function rank = () :LENGTH => COUNTOF<PARAMS>::value ;

		function is_noexcept_invoke = () :BOOL => {
			if not (exist ())
				return FALSE ;
			return mPointer->is_noexcept_invoke () ;
		} ;

		function invoke = (params... :PARAMS...) :RETURN => {
			assert (exist ()) ;
			return mPointer->invoke (params...) ;
		} ;
	} ;
} ;

define Function<RETURN ,PARAMS> = typename FUNCTION_HELP<RETURN ,PARAMS>::Function ;

trait SHAREDREF_HELP<ARG1> {
	using UNIT = ARG1 ;
	
	class SharedRef {
		interface Holder ;
		class ImplHolder ;

		variable mPointer :Holder ;
	} ;

	interface SharedRef::Holder {
		function copy = () :Holder => virtual ;
		property to = [] :UNIT => virtual ;
		function increase = () :LENGTH => virtual ;
		function decrease = () :LENGTH => virtual ;
		function release = () :BOOL => virtual ;
	} ;

	trait IMPLHOLDER_HELP<ARG1> {
		using UNIT = ARG1 ;

		class SharedRef::ImplHolder {
			variable mValue :UNIT ;
			variable mCounter :LENGTH ;
			variable mRelaser :Function<void ,type<UNIT>> ;
		} ;

		implement SharedRef::ImplHolder {
			function new = (value_ :UNIT) => {
				mValue = forward (value_) ;
				mCounter = 0 ;
				mRelaser = Function<void ,type<UNIT>> () ;
			} ;
		} ;

		implement SharedRef::ImplHolder :Holder {
			trait COPY_HELP {
				require (IS_CLONEABLE<UNIT>) ;

				function copy = () :Holder => ImplHolder (UNIT (mValue)) ;
			} ;

			trait COPY_HELP {
				require not (IS_CLONEABLE<UNIT>) ;

				function copy = () :Holder => NULL ;
			} ;

			function copy = () :Holder => COPY_HELP::copy () ;

			property to = [] :UNIT => mValue ;

			function increase = () => {
				mCounter = mCounter + 1 ;
				return mCounter ;
			} ;

			function decrease = () => {
				mCounter = mCounter - 1 ;
				return mCounter ;
			} ;

			function release = () => {
				if (mRelaser == NULL)
					return FALSE ;
				mRelaser (mValue) ;			
				mRelaser = NULL ;
				return TRUE ;
			} ;
		} ;
	} ;

	implement SharedRef {
		function new = () => mPointer = NULL ;

		function new = (creator ,destroyer) => {
			using R1X = typename IMPLHOLDER_HELP<UNIT>::ImplHolder ;
			variable rax = UNIT () ;
			creator (rax) ;
			mPointer = R1X (rax ,destroyer) ;
		} ;

		function delete = noexcept () => {
			if (mPointer == NULL)
				return ;
			constant r1x = try mPointer->release () ;
			assert (r1x.exist ()) ;
			mPointer = NULL ;
		} ;

		static function make = (initval...) => {
			using R1X = typename IMPLHOLDER_HELP<UNIT>::ImplHolder ;
			register r1x = UNIT (initval...) ;
			variable ret = AutoRef () ;
			ret.mPointer = R1X (r1x) ;
			constant r2x = ret.increase () ;
			assert (r2x == 1) ;
			return ret ;
		} ;
		
		function exist = () :BOOL => mPointer != NULL ;

		property to = [] => {
			assert (exist ()) ;
			return mPointer->to ;
		} ;
	} ;
} ;

define SharedRef<UNIT> = typename SHAREDREF_HELP<type<UNIT>>::SharedRef ;