#pragma once

#ifndef __CSC_MATH__
#error "б╞(д├бузебу ;)д├ : require 'csc_math.hpp'"
#endif

#ifdef __CSC__
#pragma push_macro ("self")
#pragma push_macro ("implicit")
#pragma push_macro ("popping")
#pragma push_macro ("imports")
#pragma push_macro ("exports")
#pragma push_macro ("switch_case")
#pragma push_macro ("discard")
#undef self
#undef implicit
#undef popping
#undef imports
#undef exports
#undef switch_case
#undef discard
#endif

#ifdef __CSC_DEPRECATED__
#include <cmath>
#include <random>
#endif

#ifdef __CSC__
#pragma pop_macro ("self")
#pragma pop_macro ("implicit")
#pragma pop_macro ("popping")
#pragma pop_macro ("imports")
#pragma pop_macro ("exports")
#pragma pop_macro ("switch_case")
#pragma pop_macro ("discard")
#endif

namespace CSC {
inline namespace MATH {
namespace FP {
template <class _ARG1 ,class _ARG2>
inline _ARG1 map (const _ARG1 &array_ ,const _ARG2 &each) {
	_ARG1 ret = _ARG1 (array_.length ()) ;
	for (auto &&i : array_)
		ret.add (each (i)) ;
	return std::move (ret) ;
}

template <class _ARG1 ,class _ARG2>
inline BitSet<> filter (const _ARG1 &array_ ,const _ARG2 &cond) {
	BitSet<> ret = BitSet<> (array_.size ()) ;
	for (auto &&i : array_) {
		const auto r1x = cond (i) ;
		if (!r1x)
			continue ;
		INDEX ix = array_.at (i) ;
		ret[ix] = TRUE ;
	}
	return std::move (ret) ;
}

template <class _ARG1 ,class _ARG2>
inline _ARG1 apply (const _ARG1 &array_ ,const BitSet<> &part) {
	_ARG1 ret = _ARG1 (part.length ()) ;
	for (auto &&i : part)
		ret.add (array_[i]) ;
	return std::move (ret) ;
}

template <class _ARG1 ,class _ARG2 ,class _ARG3>
inline _ARG1 reduce (const _ARG1 &init ,const _ARG2 &range_ ,const _ARG3 &iter) {
	_ARG1 ret = init ;
	for (auto &&i : range_)
		ret = iter (ret ,i) ;
	return std::move (ret) ;
}

template <class _ARG1>
inline const _ARG1 &conditional (BOOL flag ,const _ARG1 &case1 ,const _ARG1 &case2) {
	return _SWITCH_ (
		flag ? case1 :
		case2) ;
}

template <class _ARG1 ,class _ARG2>
inline _ARG2 jump (const _ARG1 &func ,const _ARG2 &val) {
	return func (val) (val) ;
}

template <class _ARG1 ,class _ARG2>
inline _ARG1 set (_ARG1 &&arg1 ,INDEX index ,_ARG2 &&val) {
	_ARG1 ret = std::forward<_ARG1> (arg1) ;
	ret[index] = std::forward<_ARG2> (val) ;
	return std::move (ret) ;
}

template <class _ARG1 ,class _ARG2 ,class _ARG3 ,class _ARG4>
inline _ARG1 set (_ARG1 &&arg1 ,const DEF<_ARG2 _ARG3::*> &mptr ,_ARG4 &&val) {
	_STATIC_ASSERT_ (std::is_same<REMOVE_CVR_TYPE<_ARG1> ,REMOVE_CVR_TYPE<_ARG3>>::value) ;
	_STATIC_ASSERT_ (std::is_same<REMOVE_CVR_TYPE<_ARG2> ,REMOVE_CVR_TYPE<_ARG4>>::value) ;
	_ARG1 ret = std::forward<_ARG1> (arg1) ;
	(ret.*mptr) = std::forward<_ARG4> (val) ;
	return std::move (ret) ;
}

template <class _ARG1>
inline ARRAY2<_ARG1> order (BOOL order_ ,const _ARG1 &elm0 ,const _ARG1 &elm1) {
	ARRAY2<_ARG1> ret ;
	INDEX ix = 0 ;
	INDEX iy = 1 ;
	if (!order_)
		_SWAP_ (ix ,iy) ;
	ret[ix] = elm0 ;
	ret[iy] = elm1 ;
	return std::move (ret) ;
}
} ;
} ;
} ;