module rust::basic

import module rust::core ;

private trait ENUM_MAX_ALIGN_HELP<ARGS> {
	using R1X = ENUM_MAX_ALIGN_HELP<TYPE_FIRST_REST<ARGS>>::RET ;
	using RET = ENUM_MAX<ALIGNOF<TYPE_FIRST<ARGS>> ,R1X> ;
} ;

private trait ENUM_MAX_SIZE_HELP<ARGS> {
	using R1X = ENUM_MAX_SIZE_HELP<TYPE_FIRST_REST<ARGS>>::RET ;
	using RET = ENUM_MAX<SIZEOF<TYPE_FIRST<ARGS>> ,R1X> ;
} ;

private trait VARIANT_HELP<UNITS> {
	class Variant {
		require (ENUM_NOT<IS_ANY_SAME<UNITS>...>) ;

		interface Holder ;
		class ImplHolder ;
		using VARIANT = UNION<ENUM_MAX_ALIGN_HELP<UNITS>::RET ,ENUM_MAX_SIZE_HELP<UNITS>::RET> ;

		variant mVariant :TEMP<VARIANT> ;
		constant mIndex :INDEX ;
	} ;

	interface Variant::Holder {
		function get = () :Reference => virtual ;

		function friend_create = (that :SafeReference<TEMP<VARIANT>>) :INDEX => virtual ;
	} ;

	private trait VARIANT_IMPLHOLDER_HELP<WRAP> {
		class Variant::ImplHolder {
			variant mValue :WRAP ;
		} ;

		implement Variant::ImplHolder {
			function new = () => default ;

			function new = (that :WRAP) => {
				mValue = that ;
			} ;
		} ;

		implement Variant::ImplHolder :Holder {
			function get = () => Reference (SafeReference<WRAP> (mValue)) ;

			function friend_create = (variant_ :SafeReference<TEMP<VARIANT>>) => {
				constant r1x = load (type<ImplHolder>::id ,variant_ ,address (variant_)) ;
				r1x->new (mValue) ;
				return TYPE_FIND<UNITS ,WRAP>::value ;
			} ;
		} ;
	} ;

	implement Variant {
		function new = () => {
			mVariant = TEMP<VARIANT> () ;
			mIndex = NONE ;
		} ;

		function new = (that) => {
			using R1X = _TYPE_ (that) ;
			using R2X = REMOVE_FUNCTION<R1X> ;
			require (ENUM_NOT_EQ<TYPE_FIND<UNITS ,R2X> ,ENUM_NONE>) ;
			constant r1x = PTR<R2X> => that ;
			constant r2x = VARIANT_IMPLHOLDER_HELP<R2X>::ImplHolder (r1x) ;
			constant r3x = SafeReference<TEMP<VARIANT>> (mVariant) ;
			mVariant = TEMP<VARIANT> (NULL) ;
			mIndex = r2x->friend_create (r3x) ;
		} ;

		function delete = () => {
			if (mIndex == NONE)
				return ;
			constant r1x = fake () ;
			r1x->delete () ;
			mIndex = NONE ;
		} ;

		function clone = () => {
			if (mIndex == VAR_NONE)
				return Variant () ;
			constant r1x = fake () ;
			constant r2x = SafeReference<TYPE_FIRST<UNITS>> (r1x->get ()) ;
			return Variant (r2x) ;
		} ;

		function share = () => delete ;

		private function fake = () => {
			if (mIndex == NONE)
				return PTR<Holder> (NULL) ;
			return FAKE_HELP<ENUM_ZERO>::fake (mIndex) ;
		} ;

		private trait FAKE_HELP<ARG1> {
			require (ENUM_BETWEEN<ARG1 ,ENUM_ZERO ,COUNTOF<UNITS>>) ;

			function fake = (index :INDEX) => {
				if (ENUM_CHECK<ARG1>::value == index)
					return load (type<ImplHolder<TYPE_GET<UNITS ,ARG1>>>::id ,mVariant ,address (mVariant)) ;
				return FAKE_HELP<ENUM_INCREASE<ARG1>>::fake (index) ;
			} ;
		} ;

		private trait FAKE_HELP<ARG1> {
			require (ENUM_NOT<ENUM_BETWEEN<ARG1 ,ENUM_ZERO ,COUNTOF<UNITS>>>) ;

			function fake = (index :INDEX) => PTR<Holder> (NULL) ;
		} ;

		function exist = () => mIndex != NONE ;

		function to = () => {
			require (ENUM_EQ<COUNTOF<UNITS> ,ENUM_IDEN>) ;
			constant r1x = fake () ;
			constant r2x = SafeReference<TYPE_FIRST<UNITS>> (r1x->get ()) ;
			return PTR<TYPE_FIRST<UNITS>> => r2x ;
		} ;

		function apply = (proc) => {
			using R1X = _TYPE_ (proc) ;
			require (IS_FUNCTION<R1X>) ;
			using R2X = REFLECT_FUNCTION<R1X>::SECOND ;
			require (ENUM_EQ<COUNTOF<R2X> ,ENUM_IDEN>) ;
			using R3X = R2X::FIRST ;
			if (TYPE_FIND<UNITS ,R3X>::value != mIndex)
				return ;
			constant r1x = fake () ;
			constant r2x = SafeReference<TYPE_FIRST<UNITS>> (r1x->get ()) ;
			proc (r2x) ;
		} ;
	} ;
} ;

using Variant<...> = VARIANT_HELP<type<...>>::Variant ;
using Optional<UNIT> = VARIANT_HELP<type<UNIT>>::Variant ;