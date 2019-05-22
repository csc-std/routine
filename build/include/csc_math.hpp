#pragma once

#ifndef __CSC_MATH__
#define __CSC_MATH__
#endif

#include "csc.hpp"
#include "csc_array.hpp"

namespace CSC {
inline namespace S {
inline BOOL _ISNAN_ (const VAL32 &arg) {
	const auto r1x = _CAST_<CHAR> (arg) & CHAR (0X7F800000) ;
	const auto r2x = _CAST_<CHAR> (arg) & CHAR (0X007FFFFF) ;
	if (r1x != CHAR (0X7F800000))
		return FALSE ;
	if (r2x == 0)
		return FALSE ;
	return TRUE ;
}

inline BOOL _ISNAN_ (const VAL64 &arg) {
	const auto r1x = _CAST_<DATA> (arg) & DATA (0X7FF0000000000000) ;
	const auto r2x = _CAST_<DATA> (arg) & DATA (0X000FFFFFFFFFFFFF) ;
	if (r1x != DATA (0X7FF0000000000000))
		return FALSE ;
	if (r2x == 0)
		return FALSE ;
	return TRUE ;
}

inline BOOL _ISINF_ (const VAL32 &arg) {
	const auto r1x = _CAST_<CHAR> (arg) & CHAR (0X7F800000) ;
	const auto r2x = _CAST_<CHAR> (arg) & CHAR (0X007FFFFF) ;
	if (r1x != CHAR (0X7F800000))
		return FALSE ;
	if (r2x != 0)
		return FALSE ;
	return TRUE ;
}

inline BOOL _ISINF_ (const VAL64 &arg) {
	const auto r1x = _CAST_<DATA> (arg) & DATA (0X7FF0000000000000) ;
	const auto r2x = _CAST_<DATA> (arg) & DATA (0X000FFFFFFFFFFFFF) ;
	if (r1x != DATA (0X7FF0000000000000))
		return FALSE ;
	if (r2x != 0)
		return FALSE ;
	return TRUE ;
}

inline imports DEF<VALX (const VALX &arg)> _SQRT_ ;

template <class _ARG>
inline _ARG _SQRT_ (const _ARG &arg) {
	_STATIC_ASSERT_ (stl::is_arithmetic<_ARG>::value) ;
	return _ARG (_SQRT_ (VALX (arg))) ;
}

inline imports DEF<VALX (const VALX &arg1 ,const VALX &arg2)> _POW_ ;

template <class _ARG>
inline _ARG _POW_ (const _ARG &arg1 ,const _ARG &arg2) {
	_STATIC_ASSERT_ (stl::is_arithmetic<_ARG>::value) ;
	return _ARG (_POW_ (VALX (arg1) ,VALX (arg2))) ;
}

inline imports DEF<VALX (const VALX &arg)> _EXP_ ;

template <class _ARG>
inline _ARG _EXP_ (const _ARG &arg) {
	_STATIC_ASSERT_ (stl::is_arithmetic<_ARG>::value) ;
	return _ARG (_EXP_ (VALX (arg))) ;
}

inline imports DEF<VALX (const VALX &arg)> _LOG_ ;

template <class _ARG>
inline _ARG _LOG_ (const _ARG &arg) {
	_STATIC_ASSERT_ (stl::is_arithmetic<_ARG>::value) ;
	return _ARG (_LOG_ (VALX (arg))) ;
}

inline imports DEF<VALX (const VALX &arg)> _SIN_ ;

template <class _ARG>
inline _ARG _SIN_ (const _ARG &arg) {
	_STATIC_ASSERT_ (stl::is_arithmetic<_ARG>::value) ;
	return _ARG (_SIN_ (VALX (arg))) ;
}

inline imports DEF<VALX (const VALX &arg)> _COS_ ;

template <class _ARG>
inline _ARG _COS_ (const _ARG &arg) {
	_STATIC_ASSERT_ (stl::is_arithmetic<_ARG>::value) ;
	return _ARG (_COS_ (VALX (arg))) ;
}

inline imports DEF<VALX (const VALX &arg)> _TAN_ ;

template <class _ARG>
inline _ARG _TAN_ (const _ARG &arg) {
	_STATIC_ASSERT_ (stl::is_arithmetic<_ARG>::value) ;
	return _ARG (_TAN_ (VALX (arg))) ;
}

inline imports DEF<VALX (const VALX &arg)> _ASIN_ ;

template <class _ARG>
inline _ARG _ASIN_ (const _ARG &arg) {
	_STATIC_ASSERT_ (stl::is_arithmetic<_ARG>::value) ;
	return _ARG (_ASIN_ (VALX (arg))) ;
}

inline imports DEF<VALX (const VALX &arg)> _ACOS_ ;

template <class _ARG>
inline _ARG _ACOS_ (const _ARG &arg) {
	_STATIC_ASSERT_ (stl::is_arithmetic<_ARG>::value) ;
	return _ARG (_ACOS_ (VALX (arg))) ;
}

inline imports DEF<VALX (const VALX &arg)> _ATAN_ ;

template <class _ARG>
inline _ARG _ATAN_ (const _ARG &arg) {
	_STATIC_ASSERT_ (stl::is_arithmetic<_ARG>::value) ;
	return _ARG (_ATAN_ (VALX (arg))) ;
}

inline imports DEF<VALX (const VALX &arg1 ,const VALX &arg2)> _ATAN_ ;

template <class _ARG>
inline _ARG _ATAN_ (const _ARG &arg1 ,const _ARG &arg2) {
	_STATIC_ASSERT_ (stl::is_arithmetic<_ARG>::value) ;
	return _ARG (_ATAN_ (VALX (arg1) ,VALX (arg2))) ;
}

template <class _ARG>
inline _ARG _SIGN_ (const _ARG &arg) {
	if (arg < _ARG (0))
		return _ARG (-1) ;
	if (_ARG (0) < arg)
		return _ARG (+1) ;
	return _ARG (0) ;
}

template <class _ARG>
inline _ARG _PINV_ (const _ARG &arg) {
	_STATIC_ASSERT_ (stl::is_arithmetic<_ARG>::value) ;
	if (arg == _ARG (0))
		return _ARG (0) ;
	return _ARG (1) / arg ;
}

template <class _ARG>
inline _ARG _PINV_ (const _ARG &arg1 ,const _ARG &arg2) {
	_STATIC_ASSERT_ (stl::is_arithmetic<_ARG>::value) ;
	_DEBUG_ASSERT_ (arg2 > VALX (0)) ;
	if (_ABS_ (arg1) < arg2)
		return _ARG (0) ;
	return _ARG (1) / arg1 ;
}

inline VALX _FLOOR_ (const VALX &arg1 ,const VALX &arg2) {
	_DEBUG_ASSERT_ (arg2 > VALX (0)) ;
	const auto r1x = VAR64 (arg1 / arg2) ;
	VALX ret = arg2 * VALX (r1x) ;
	if (arg1 < 0 && arg1 < ret)
		ret = arg2 * VALX (r1x - 1) ;
	return std::move (ret) ;
}

template <class _ARG>
inline _ARG _FLOOR_ (const _ARG &arg1 ,const _ARG &arg2) {
	_STATIC_ASSERT_ (stl::is_arithmetic<_ARG>::value) ;
	return _ARG (_FLOOR_ (VALX (arg1) ,VALX (arg2))) ;
}

inline VALX _CEIL_ (const VALX &arg1 ,const VALX &arg2) {
	_DEBUG_ASSERT_ (arg2 > VALX (0)) ;
	const auto r1x = VAR64 (arg1 / arg2) ;
	VALX ret = arg2 * VALX (r1x) ;
	if (0 < arg1 && ret < arg1)
		ret = arg2 * VALX (r1x + 1) ;
	return std::move (ret) ;
}

template <class _ARG>
inline _ARG _CEIL_ (const _ARG &arg1 ,const _ARG &arg2) {
	_STATIC_ASSERT_ (stl::is_arithmetic<_ARG>::value) ;
	return _ARG (_CEIL_ (VALX (arg1) ,VALX (arg2))) ;
}

template <class _ARG>
inline _ARG _ROUND_ (const _ARG &arg1 ,const _ARG &arg2) {
	_STATIC_ASSERT_ (stl::is_arithmetic<_ARG>::value) ;
	_DEBUG_ASSERT_ (arg2 > _ARG (0)) ;
	return _ARG (_FLOOR_ (VALX (arg1) + VALX (arg2) / 2 ,VALX (arg2))) ;
}

template <class _ARG1 ,class _ARG2>
inline _ARG2 _CLAMP_ (const _ARG1 &arg1 ,const _ARG2 &arg2 ,const _ARG2 &arg3) {
	if (arg1 < _ARG1 (arg2))
		return arg2 ;
	if (_ARG1 (arg3) < arg1)
		return arg3 ;
	return _ARG2 (arg1) ;
}

template <class _ARG>
inline const _ARG &_MINOF_ (const _ARG &arg) {
	return arg ;
}

template <class _ARG1 ,class _ARG2 ,class... _ARGS>
inline const _ARG1 &_MINOF_ (const _ARG1 &arg1 ,const _ARG2 &arg2 ,const _ARGS &...args) {
	_STATIC_ASSERT_ (std::is_same<_ARG1 ,_ARG2>::value) ;
	return _MIN_ (arg1 ,_MINOF_ (arg2 ,args...)) ;
}

template <class _ARG>
inline const _ARG &_MAXOF_ (const _ARG &arg) {
	return arg ;
}

template <class _ARG1 ,class _ARG2 ,class... _ARGS>
inline const _ARG1 &_MAXOF_ (const _ARG1 &arg1 ,const _ARG2 &arg2 ,const _ARGS &...args) {
	_STATIC_ASSERT_ (std::is_same<_ARG1 ,_ARG2>::value) ;
	return _MAX_ (arg1 ,_MAXOF_ (arg2 ,args...)) ;
}

inline VAL64 _IEEE754ENCODE_ (const ARRAY2<VAR64> &arg) {
	DATA ret = 0 ;
	const auto r1x = _CALL_ ([&] () {
		ARRAY3<DATA> ret ;
		ret[0] = DATA (arg[0]) ;
		ret[1] = DATA (arg[1]) ;
		ret[2] = ret[0] ;
		if ((ret[0] & DATA (0X8000000000000000)) != 0)
			ret[0] = ~ret[0] + 1 ;
		while (ret[0] != 0 && (ret[0] & ~0X000FFFFFFFFFFFFF) != 0X0010000000000000) {
			ret[0] <<= 1 ;
			ret[1]-- ;
		}
		const auto r3x = VAR64 (ret[1]) ;
		while (VAR64 (ret[1]) <= -1075) {
			ret[0] >>= 1 ;
			ret[1]++ ;
		}
		ret[1] = ret[1] + 1075 - EFLAG (r3x <= -1075) ;
		ret[1] <<= 52 ;
		if (ret[0] == 0)
			ret[1] = 0 ;
		return std::move (ret) ;
	}) ;
	_DYNAMIC_ASSERT_ ((r1x[0] & ~0X001FFFFFFFFFFFFF) == 0) ;
	_DYNAMIC_ASSERT_ ((r1x[1] & ~0X7FF0000000000000) == 0) ;
	ret |= r1x[0] & DATA (0X000FFFFFFFFFFFFF) ;
	ret |= r1x[1] & DATA (0X7FF0000000000000) ;
	ret |= r1x[2] & DATA (0X8000000000000000) ;
	return std::move (_CAST_<VAL64> (ret)) ;
}

inline ARRAY2<VAR64> _IEEE754DECODE_ (const VAL64 &arg) {
	ARRAY2<DATA> ret ;
	const auto r1x = _CAST_<DATA> (arg) ;
	ret[0] = r1x & DATA (0X000FFFFFFFFFFFFF) ;
	const auto r2x = r1x & DATA (0X7FF0000000000000) ;
	if (r2x != 0)
		ret[0] |= DATA (0X0010000000000000) ;
	ret[1] = r2x >> 52 ;
	ret[1] -= DATA (1074 + EFLAG (r2x != 0)) ;
	while (ret[0] != 0 && (ret[0] & DATA (0X0000000000000001)) == 0) {
		ret[0] >>= 1 ;
		ret[1]++ ;
	}
	if ((r1x & DATA (0X8000000000000000)) != 0)
		ret[0] = ~ret[0] + 1 ;
	if (r1x == 0) {
		ret[0] = 0 ;
		ret[1] = 0 ;
	}
	return std::move (_CAST_<ARRAY2<VAR64>> (ret)) ;
}

inline ARRAY2<VAR64> _IEEE754E2TOE10_ (const ARRAY2<VAR64> &arg) {
	_STATIC_WARNING_ ("note") ;
	/*
	X^(b/a) => { Y[0]=X^b ; Y[K+1]=Y[k]+((X^b)/(Y[k]^(a-1))-Y[k])/a ; }
	X^(b/a) = Y[inf]
	*/
	const auto r1x = _CALL_ ([&] () {
		ARRAY2<DATA> ret = _CAST_<ARRAY2<DATA>> (arg) ;
		if (arg[0] < 0)
			ret[0] = ~ret[0] + 1 ;
		_DEBUG_ASSERT_ ((ret[0] & DATA (0X8000000000000000)) == 0) ;
		while (ret[0] != 0 && (ret[0] & ~0X000FFFFFFFFFFFFF) != 0X0010000000000000) {
			ret[0] <<= 1 ;
			ret[1]-- ;
		}
		return std::move (_CAST_<ARRAY2<VAR64>> (ret)) ;
	}) ;
	const auto r2x = (VALX_LOGE2 / VALX_LOGE10) * r1x[1] ;
	ARRAY2<DATA> ret ;
	ret[0] = DATA (VAR64 (r1x[0] * _POW_ (10 ,(r2x - VAR64 (r2x))) + VAL64 (0.5))) ;
	ret[1] = DATA (VAR64 (r2x)) ;
	while (ret[0] != 0 && ret[0] % 10 == 0) {
		ret[0] /= 10 ;
		ret[1]++ ;
	}
	if (arg[0] < 0)
		ret[0] = ~ret[0] + 1 ;
	return std::move (_CAST_<ARRAY2<VAR64>> (ret)) ;
}

inline ARRAY2<VAR64> _IEEE754E10TOE2_ (const ARRAY2<VAR64> &arg) {
	_STATIC_WARNING_ ("note") ;
	/*
	X^(b/a) => { Y[0]=X^b ; Y[K+1]=Y[k]+((X^b)/(Y[k]^(a-1))-Y[k])/a ; }
	X^(b/a) = Y[inf]
	*/
	const auto r1x = _CALL_ ([&] () {
		ARRAY2<DATA> ret = _CAST_<ARRAY2<DATA>> (arg) ;
		if (arg[0] < 0)
			ret[0] = ~ret[0] + 1 ;
		_DEBUG_ASSERT_ ((ret[0] & DATA (0X8000000000000000)) == 0) ;
		while (ret[0] != 0 && (ret[0] & ~0X000FFFFFFFFFFFFF) == 0) {
			ret[0] = (ret[0] << 3) + (ret[0] << 1) ;
			ret[1]-- ;
		}
		return std::move (_CAST_<ARRAY2<VAR64>> (ret)) ;
	}) ;
	const auto r2x = (VALX_LOGE10 / VALX_LOGE2) * r1x[1] ;
	ARRAY2<DATA> ret ;
	ret[0] = DATA (VAR64 (r1x[0] * _POW_ (2 ,(r2x - VAR64 (r2x))) + VAL64 (0.5))) ;
	ret[1] = DATA (VAR64 (r2x)) ;
	while (ret[0] != 0 && (ret[0] & DATA (~0X001FFFFFFFFFFFFF)) != 0) {
		ret[0] >>= 1 ;
		ret[1]++ ;
	}
	while (ret[0] != 0 && (ret[0] & DATA (0X0000000000000001)) == 0) {
		ret[0] >>= 1 ;
		ret[1]++ ;
	}
	if (arg[0] < 0)
		ret[0] = ~ret[0] + 1 ;
	return std::move (_CAST_<ARRAY2<VAR64>> (ret)) ;
}
} ;

template <class TYPE ,class SUBJECT = VAR>
struct Classified {
	TYPE mData ;
	SUBJECT mGroup ;
} ;

template <class TYPE ,class SUBJECT = VAL>
struct Weighted {
	TYPE mData ;
	SUBJECT mWeight ;
} ;

#ifdef __CSC_DEPRECATED__
inline namespace S {
template <class _ARG1 ,class _ARG2>
inline Array<_ARG2> _MAP_ (const Array<_ARG1> &arg1 ,const Function<_ARG2 (const _ARG1 &)> &func) {
	Array<_ARG2> ret = Array<_ARG2> (arg1.size ()) ;
	for (INDEX i = 0 ; i < arg1.length () ; i++)
		ret[i] = func (arg1[i]) ;
	return std::move (ret) ;
}

template <class _ARG1 ,class _ARG2 ,class _ARG3>
inline Array<_ARG3> _MAP_ (const Array<_ARG1> &arg1 ,const Array<_ARG2> &arg2 ,const Function<_ARG3 (const _ARG1 & ,const _ARG2 &)> &func) {
	_DEBUG_ASSERT_ (arg1.size () == arg2.size ()) ;
	Array<_ARG3> ret = Array<_ARG3> (arg1.size ()) ;
	for (INDEX i = 0 ; i < arg1.length () ; i++)
		ret[i] = func (arg1[i] ,arg2[i]) ;
	return std::move (ret) ;
}

template <class _ARG>
inline Array<_ARG> _FILTER_ (const Array<_ARG> &arg1 ,const Array<INDEX> &elem) {
	Array<_ARG> ret = Array<_ARG> (elem.length ()) ;
	INDEX iw = 0 ;
	for (auto &&i : elem)
		ret[iw++] = arg1[i] ;
	return std::move (ret) ;
}

inline Array<INDEX> _ELEMENT_ (const Array<BOOL> &elem) {
	const auto r1x = _CALL_ ([&] () {
		LENGTH ret = 0 ;
		for (auto &&i : elem)
			ret += EFLAG (i) ;
		return std::move (ret) ;
	}) ;
	Array<INDEX> ret = Array<INDEX> (r1x) ;
	INDEX iw = 0 ;
	for (INDEX i = 0 ; i < elem.length () ; i++) {
		if (!elem[i])
			continue ;
		ret[iw++] = i ;
	}
	return std::move (ret) ;
}

template <class _ARG>
inline Array<_ARG> _FILTER_ (const Array<_ARG> &arg1 ,const Array<BOOL> &elem) {
	_DEBUG_ASSERT_ (arg1.size () == elem.size ()) ;
	return _FILTER_ (arg1 ,_ELEMENT_ (elem)) ;
}

template <class _ARG>
inline Array<_ARG> _REDUCE_ (const _ARG &first ,LENGTH count ,const Function<_ARG (const _ARG &)> &func) {
	Array<_ARG> ret = Array<_ARG> (count) ;
	for (INDEX i = 0 ,ie = _MIN_ (LENGTH (1) ,ret.length ()) ; i < ie ; i++)
		ret[i] = first ;
	for (INDEX i = 1 ; i < ret.length () ; i++)
		ret[i] = func (ret[i - 1]) ;
	return std::move (ret) ;
}

template <class _ARG1 ,class _ARG2>
inline _ARG1 _REDUCE_ (const _ARG1 &first ,const Array<_ARG2> &arg1 ,const Function<_ARG1 (const _ARG1 & ,const _ARG2 &)> &func) {
	_ARG1 ret = first ;
	for (auto &&i : arg1)
		ret = func (ret ,i) ;
	return std::move (ret) ;
}

template <class _ARG>
inline Array<_ARG> _CONCAT_ (const Array<_ARG> &arg1 ,const _ARG &arg2) {
	Array<_ARG> ret = Array<_ARG> (arg1.length () + 1) ;
	for (INDEX i = 0 ; i < arg1.length () ; i++)
		ret[i] = arg1[i] ;
	INDEX ix = arg1.length () ;
	ret[ix] = arg2 ;
	return std::move (ret) ;
}

template <class _ARG>
inline Array<_ARG> _CONCAT_ (const Array<_ARG> &arg1 ,const Array<_ARG> &arg2) {
	Array<_ARG> ret = Array<_ARG> (arg1.length () + arg2.length ()) ;
	for (INDEX i = 0 ; i < arg1.length () ; i++)
		ret[i] = arg1[i] ;
	INDEX ix = arg1.length () ;
	for (INDEX i = 0 ; i < arg2.length () ; i++)
		ret[ix + i] = arg2[i] ;
	return std::move (ret) ;
}

template <class _ARG1 ,class... _ARGS>
inline Function<_ARG1 (const _ARGS &...)> _BIND_ (const PTR<_ARG1 (const _ARGS &...)> &func) {
	return Function<_ARG1 (const _ARGS &...)> (func) ;
}

template <class _ARG1 ,class _ARG2 ,class _ARG3 ,class _ARG4>
inline Function<_ARG1 (const _ARG2 & ,const _ARG3 &)> _BIND_ (const decltype (ARGVP1) & ,const decltype (ARGVP1) & ,const decltype (ARGVP2) & ,const Function<_ARG4 (const _ARG2 & ,const _ARG3 &)> &func1 ,const Function<_ARG1 (const _ARG2 & ,const _ARG4 &)> &func2) {
	return Function<_ARG1 (const _ARG2 & ,const _ARG3 &)> ([&] (const _ARG2 &op1 ,const _ARG3 &op2) {
		return func2 (op1 ,func1 (op1 ,op2)) ;
	}) ;
}

template <class _ARG>
inline Array<Array<_ARG>> _GROUP_ (const Array<_ARG> &arg1 ,const Array<Function<BOOL (const _ARG &)>> &func) {
	Array<Array<_ARG>> ret ;
	const auto r1x = _BIND_<Array<_ARG> ,Array<_ARG>> (&_COPY_<Array<_ARG>>) ;
	const auto r2x = _REDUCE_ (arg1 ,func.length () ,r1x) ;
	const auto r3x = _BIND_<Array<BOOL> ,Array<_ARG> ,Function<BOOL (const _ARG &)>> (&_MAP_<_ARG ,BOOL>) ;
	const auto r4x = _BIND_<Array<_ARG> ,Array<_ARG> ,Array<BOOL>> (&_FILTER_< _ARG>) ;
	const auto r5x = _BIND_<Array<_ARG> ,Array<_ARG> ,Function<BOOL (const _ARG &)>> (ARGVP1 ,ARGVP1 ,ARGVP2 ,r3x ,r4x) ;
	const auto r6x = _MAP_ (r2x ,func ,r5x) ;
	const auto r7x = _BIND_<Array<Array<_ARG>> ,Array<Array<_ARG>> ,Array<_ARG>> (&_CONCAT_<Array<_ARG>>) ;
	ret = _REDUCE_ (ret ,r6x ,r7x) ;
	return std::move (ret) ;
}

template <class _ARG>
inline Array<_ARG> _FLATTEN_ (const Array<Array<_ARG>> &arg1) {
	const auto r1x = _CALL_ ([&] () {
		LENGTH ret = 0 ;
		for (auto &&i : arg1)
			ret += i.length () ;
		return std::move (ret) ;
	}) ;
	Array<_ARG> ret = Array<_ARG> (r1x) ;
	INDEX iw = 0 ;
	for (auto &&i : arg1) {
		for (auto &&j : i)
			ret[iw++] = j ;
	}
	return std::move (ret) ;
}
} ;
#endif

#ifdef __CSC_DEPRECATED__
class Number {
public:
	Number () {
		_STATIC_WARNING_ ("unimplemented") ;
	}
} ;
#endif

#ifdef __CSC_DEPRECATED__
class Operator {
public:
	Operator () {
		_STATIC_WARNING_ ("unimplemented") ;
	}
} ;
#endif

#ifdef __CSC_DEPRECATED__
class Expression {
public:
	Expression () {
		_STATIC_WARNING_ ("unimplemented") ;
	}
} ;
#endif
} ;