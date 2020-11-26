
module rust ;

interface Nullable {
	function is_null = () => virtual ;
} ;

private trait EQUALABLE_HELP<UNIT> {
	interface Equalable {
		function equal = (that :UNIT) => virtual ;
	} ;
} ;

using Equalable<UNIT> = EQUALABLE_HELP<UNIT>::Equalable ;

private trait COMPRABLE_HELP<UNIT> {
	interface Comprable {
		function compr = (that :UNIT) => virtual ;
	} ;
} ;

using Comprable<UNIT> = COMPRABLE_HELP<UNIT>::Comprable ;