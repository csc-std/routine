#pragma once

#ifndef __CSC_MATH__
#error "∑(っ°Д° ;)っ : require 'csc_math.hpp'"
#endif

#ifdef __CSC__
#undef self
#undef implicit
#undef popping
#undef imports
#undef exports
#pragma pop_macro ("self")
#pragma pop_macro ("implicit")
#pragma pop_macro ("popping")
#pragma pop_macro ("imports")
#pragma pop_macro ("exports")
#endif

#ifdef __CSC_DEPRECATED__
#include <cmath>
#include <random>
#endif

#ifdef __CSC__
#pragma push_macro ("self")
#pragma push_macro ("implicit")
#pragma push_macro ("popping")
#pragma push_macro ("imports")
#pragma push_macro ("exports")
#define self to ()
#define implicit
#define popping
#define imports extern
#define exports
#endif

namespace CSC {
#if defined (_CMATH_) || defined (_GLIBCXX_CMATH)
inline namespace S {
inline exports VALX _SQRT_ (const VALX &arg) {
	return std::sqrt (arg) ;
}

inline exports VALX _POW_ (const VALX &arg1 ,const VALX &arg2) {
	return std::pow (arg1 ,arg2) ;
}

inline exports VALX _EXP_ (const VALX &arg) {
	return std::exp (arg) ;
}

inline exports VALX _LOG_ (const VALX &arg) {
	return std::log (arg) ;
}

inline exports VALX _SIN_ (const VALX &arg) {
	return std::sin (arg) ;
}

inline exports VALX _COS_ (const VALX &arg) {
	return std::cos (arg) ;
}

inline exports VALX _TAN_ (const VALX &arg) {
	return std::tan (arg) ;
}

inline exports VALX _ASIN_ (const VALX &arg) {
	return std::asin (arg) ;
}

inline exports VALX _ACOS_ (const VALX &arg) {
	return std::acos (arg) ;
}

inline exports VALX _ATAN_ (const VALX &arg) {
	return std::atan (arg) ;
}

inline exports VALX _ATAN_ (const VALX &arg1 ,const VALX &arg2) {
	return std::atan2 (arg1 ,arg2) ;
}
} ;
#endif
} ;