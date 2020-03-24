#pragma once

#ifndef __CSC_FUNCTIONAL__
#error "б╞(д├бузебу ;)д├ : require 'csc_functional.hpp'"
#endif

namespace CSC {
namespace TS {
inline namespace FUNCTIONAL {
template <class...>
struct op_equal ;

template <class _ARG1>
struct op_equal<_ARG1> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &arg1 ,const _ARG1 &arg2) {
			return arg1 == arg2 ;
		}) ;
	}
} ;

template <class...>
struct op_compr ;

template <class _ARG1>
struct op_compr<_ARG1> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &arg1 ,const _ARG1 &arg2) {
			return _MEMCOMPR_ (PTRTOARR[&arg1] ,PTRTOARR[&arg2] ,1) ;
		}) ;
	}
} ;

template <class...>
struct op_not ;

template <class _ARG1>
struct op_not<_ARG1> {
	inline static Expression<RANK1> instance () {
		return Operator ([] (const _ARG1 &arg1) {
			return ~arg1 ;
		}) ;
	}
} ;

template <>
struct op_not<BOOL> {
	inline static Expression<RANK1> instance () {
		return Operator ([] (const BOOL &arg1) {
			return !arg1 ;
		}) ;
	}
} ;

template <class...>
struct op_and ;

template <class _ARG1>
struct op_and<_ARG1> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &arg1 ,const _ARG1 &arg2) {
			return arg1 & arg2 ;
		}) ;
	}
} ;

template <>
struct op_and<BOOL> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const BOOL &arg1 ,const BOOL &arg2) {
			return arg1 && arg2 ;
		}) ;
	}
} ;

template <class...>
struct op_or ;

template <class _ARG1>
struct op_or<_ARG1> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &arg1 ,const _ARG1 &arg2) {
			return arg1 | arg2 ;
		}) ;
	}
} ;

template <>
struct op_or<BOOL> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const BOOL &arg1 ,const BOOL &arg2) {
			return arg1 || arg2 ;
		}) ;
	}
} ;

template <class...>
struct op_xor ;

template <class _ARG1>
struct op_xor<_ARG1> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &arg1 ,const _ARG1 &arg2) {
			return arg1 ^ arg2 ;
		}) ;
	}
} ;

template <>
struct op_xor<BOOL> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const BOOL &arg1 ,const BOOL &arg2) {
			return arg1 != arg2 ;
		}) ;
	}
} ;

template <class...>
struct op_plus ;

template <class _ARG1>
struct op_plus<_ARG1> {
	inline static Expression<RANK1> instance () {
		return Operator ([] (const _ARG1 &arg1) {
			return +arg1 ;
		}) ;
	}
} ;

template <class...>
struct op_minus ;

template <class _ARG1>
struct op_minus<_ARG1> {
	inline static Expression<RANK1> instance () {
		return Operator ([] (const _ARG1 &arg1) {
			return -arg1 ;
		}) ;
	}
} ;

template <class...>
struct op_increase ;

template <class _ARG1>
struct op_increase<_ARG1> {
	inline static Expression<RANK1> instance () {
		return Operator ([] (const _ARG1 &arg1) {
			_ARG1 ret = arg1 ;
			++ret ;
			return std::move (ret) ;
		}) ;
	}
} ;

template <class...>
struct op_decrease ;

template <class _ARG1>
struct op_decrease<_ARG1> {
	inline static Expression<RANK1> instance () {
		return Operator ([] (const _ARG1 &arg1) {
			_ARG1 ret = arg1 ;
			--ret ;
			return std::move (ret) ;
		}) ;
	}
} ;

template <class...>
struct op_add ;

template <class _ARG1>
struct op_add<_ARG1> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &arg1 ,const _ARG1 &arg2) {
			return arg1 + arg2 ;
		}) ;
	}
} ;

template <class...>
struct op_sub ;

template <class _ARG1>
struct op_sub<_ARG1> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &arg1 ,const _ARG1 &arg2) {
			return arg1 - arg2 ;
		}) ;
	}
} ;

template <class...>
struct op_mul ;

template <class _ARG1>
struct op_mul<_ARG1> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &arg1 ,const _ARG1 &arg2) {
			return arg1 * arg2 ;
		}) ;
	}
} ;

template <class...>
struct op_div ;

template <class _ARG1>
struct op_div<_ARG1> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &arg1 ,const _ARG1 &arg2) {
			return arg1 / arg2 ;
		}) ;
	}
} ;

template <class...>
struct op_mod ;

template <class _ARG1>
struct op_mod<_ARG1> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &arg1 ,const _ARG1 &arg2) {
			return arg1 % arg2 ;
		}) ;
	}
} ;

template <class...>
struct op_cross ;

template <class _ARG1>
struct op_cross<_ARG1> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &arg1 ,const _ARG1 &arg2) {
			return arg1 ^ arg2 ;
		}) ;
	}
} ;

template <class...>
struct op_to ;

template <class _ARG1 ,class _ARG2>
struct op_to<_ARG1 ,_ARG2> {
	inline static Expression<RANK1> instance () {
		return Operator ([] (const _ARG1 &arg1) {
			return arg1.self ;
		}) ;
	}
} ;

template <class...>
struct op_get ;

template <class _ARG1>
struct op_get<_ARG1 ,INDEX> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &arg1 ,const INDEX &arg2) {
			return arg1[arg2] ;
		}) ;
	}
} ;

template <class _ARG1 ,class _ARG2>
struct op_get<_ARG1 ,DEF<_ARG2 _ARG1::*>> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &arg1 ,const DEF<_ARG2 _ARG1::*> &arg2) {
			return (arg1.*arg2) ;
		}) ;
	}
} ;

template <class...>
struct op_set ;

template <class _ARG1 ,class _ARG2>
struct op_set<_ARG1 ,INDEX ,_ARG2> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &arg1 ,const INDEX &arg2 ,const _ARG2 &arg3) {
			_ARG1 ret = arg1 ;
			ret[arg2] = arg3 ;
			return std::move (ret) ;
		}) ;
	}
} ;

template <class _ARG1 ,class _ARG2>
struct op_set<_ARG1 ,DEF<_ARG2 _ARG1::*> ,_ARG2> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &arg1 ,const DEF<_ARG2 _ARG1::*> &arg2 ,const _ARG2 &arg3) {
			_ARG1 ret = arg1 ;
			(arg1.*arg2) = arg3 ;
			return std::move (ret) ;
		}) ;
	}
} ;

template <class...>
struct op_read ;

template <class _ARG1 ,class _ARG2>
struct op_read<_ARG1 ,_ARG2> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &arg1 ,const _ARG2 &arg2) {
			_ARG2 ret = arg1 ;
			ret >> arg2 ;
			return std::move (ret) ;
		}) ;
	}
} ;

template <class...>
struct op_write ;

template <class _ARG1 ,class _ARG2>
struct op_write<_ARG1 ,_ARG2> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &arg1 ,const _ARG2 &arg2) {
			_ARG2 ret = arg1 ;
			ret << arg2 ;
			return std::move (ret) ;
		}) ;
	}
} ;
} ;

inline namespace FUNCTIONAL {
template <class...>
struct map ;

template <class _ARG1>
struct map<Array<_ARG1>> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const Array<_ARG1> &array_ ,const Expression<RANK1> &each) {
			Array<_ARG1> ret = Array<_ARG1> (array_.size ()) ;
			for (auto &&i : _RANGE_ (0 ,array_.length ())) {
				const auto r1x = each (i) ;
				ret[i] = r1x.template as<_ARG1> () ;
			}
			return std::move (ret) ;
		}) ;
	}
} ;

template <class _ARG1>
struct map<Deque<_ARG1>> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const Deque<_ARG1> &array_ ,const Expression<RANK1> &each) {
			Deque<_ARG1> ret = Deque<_ARG1> (array_.size ()) ;
			for (auto &&i : array_) {
				const auto r1x = each (i) ;
				INDEX ix = ret.insert () ;
				ret[ix] = r1x.template as<_ARG1> () ;
			}
			return std::move (ret) ;
		}) ;
	}
} ;

template <class...>
struct filter ;

template <class _ARG1>
struct filter<_ARG1> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &array_ ,const Expression<RANK1> &cond) {
			BitSet<> ret = BitSet<> (array_.size ()) ;
			for (auto &&i : _RANGE_ (0 ,array_.length ())) {
				const auto r1x = cond (array_[i]) ;
				if (!r1x.template as<BOOL> ())
					continue ;
				ret[i] = TRUE ;
			}
			return std::move (ret) ;
		}) ;
	}
} ;

template <class...>
struct empty ;

template <class _ARG1>
struct empty<_ARG1> {
	inline static Expression<RANK1> instance () {
		return Operator ([] (const _ARG1 &array_) {
			return BOOL {array_.length () == 0} ;
		}) ;
	}
} ;

template <class...>
struct some ;

template <class _ARG1>
struct some<_ARG1> {
	inline static Expression<RANK2> instance () {
		return op_not<BOOL>::instance () + empty<BitSet<>>::instance () + filter<_ARG1>::instance () ;
	}
} ;

template <class...>
struct every ;

template <class _ARG1>
struct every<_ARG1> {
	inline static Expression<RANK2> instance () {
		return op_not<BOOL>::instance () + some<_ARG1>::instance () ;
	}
} ;

template <class...>
struct apply ;

template <class _ARG1 ,class _ARG2>
struct apply<Array<_ARG1> ,_ARG2 ,BitSet<>> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG2 &array_ ,const BitSet<> &range_) {
			Array<_ARG1> ret = Array<_ARG1> (range_.length ()) ;
			INDEX iw = 0 ;
			for (auto &&i : range_)
				ret[iw++] = array_[i] ;
			return std::move (ret) ;
		}) ;
	}
} ;

template <class _ARG1>
struct apply<Deque<_ARG1> ,class _ARG2 ,BitSet<>> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG2 &array_ ,const BitSet<> &range_) {
			Deque<_ARG1> ret = Deque<_ARG1> (range_.length ()) ;
			for (auto &&i : range_) {
				INDEX ix = ret.insert () ;
				ret[ix] = array_[i] ;
			}
			return std::move (ret) ;
		}) ;
	}
} ;

template <class...>
struct reduce ;

template <>
struct reduce<BitSet<>> {
	inline static Expression<RANK3> instance () {
		return Operator ([] (const Operand &init ,const BitSet<> &range_ ,const Expression<RANK2> &iter) {
			Operand ret = init ;
			for (auto &&i : range_)
				ret = iter (ret ,INDEX (i)) ;
			return std::move (ret) ;
		}) ;
	}
} ;

template <class...>
struct conditional ;

template <>
struct conditional<> {
	inline static Expression<RANK3> instance () {
		return Operator ([] (const BOOL &flag ,const Operand &case1 ,const Operand &case2) {
			if (flag)
				return case1 ;
			return case2 ;
		}) ;
	}
} ;

template <class...>
struct tuple ;

template <class _ARG1>
struct tuple<_ARG1> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &item1) {
			return ARRAY1<_ARG1> {item1} ;
		}) ;
	}
} ;

template <class _ARG1>
struct tuple<_ARG1 ,_ARG1> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &item1 ,const _ARG1 &item2) {
			return ARRAY2<_ARG1> {item1 ,item2} ;
		}) ;
	}
} ;

template <class _ARG1>
struct tuple<_ARG1 ,_ARG1 ,_ARG1> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const _ARG1 &item1 ,const _ARG1 &item2 ,const _ARG1 &item3) {
			return ARRAY2<_ARG1> {item1 ,item2 ,item3} ;
		}) ;
	}
} ;

template <class...>
struct order ;

template <>
struct order<> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const Operand &case1 ,const Operand &case2) {
			const auto r1x = tuple<Operand ,Operand>::instance () + case1 + case2 ;
			const auto r2x = tuple<Operand ,Operand>::instance () + case2 + case1 ;
			const auto r3x = conditional<>::instance ().curry (ARGVP2 ,ARGVP3 ,ARGVP1) ;
			return r3x + r1x + r2x ;
		}) ;
	}
} ;

template <class...>
struct assign ;

template <class _ARG1>
struct assign<_ARG1> {
	inline static Expression<RANK2> instance () {
		return Operator ([] (const Operand &arg1 ,const Operand &arg2) {
			const auto r1x = op_set<_ARG1 ,INDEX ,_ARG2>::instance ().curry (ARGVP2 ,ARGVP3 ,ARGVP1) ;
			const auto r2x = Expression<RANK0> (arg1) ;
			const auto r3x = Expression<RANK0> (arg2) ;
			return r1x + r2x + r3x ;
		}) ;
	}
} ;
} ;
} ;
} ;