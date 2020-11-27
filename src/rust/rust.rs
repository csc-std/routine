
module rust ;

# module
# import

# private
# public

# trait
# using

# require
# macro
# concept
# as

# static
# constant
# variable

# function
# default
# delete
# virtual
# zeroize

# class
# extend
# interface
# implement
# new
# delete

# bool ;
# true ;
# false ;

# int32 ;
# int64 ;

# float32 ;
# float64 ;
# infinity ;

# byte ;
# word ;
# char ;
# feat ;

# stra ;
# stru8 ;
# stru16 ;
# stru32 ;

# null ;

# enum ;

# type ;

# alignof ;
# sizeof ;
# countof ;

# define

# literal ;

# func_name ;
# function_name ;
# module_name ;
# file_name ;
# line_name ;

# anonymous ;

# if ;

# for ;
# in ;
# continue ;

# while ;
# break ;

# switch ;
# discard ;

# throw ;
# catch ;

# later ;

# await ;
# yield ;

# syntax

private trait WRAPPED<UNIT> {
	interface Wrapped {
		function to = () :PTR<UNIT> => virtual ;
	} ;
} ;

using Wrapped<UNIT> = WRAPPED<UNIT>::Wrapped ;

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