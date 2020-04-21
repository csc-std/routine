#pragma once

#ifndef __CSC_FUNCTIONAL__
#define __CSC_FUNCTIONAL__
#endif

#include "csc.hpp"
#include "csc_basic.hpp"
#include "csc_extend.hpp"
#include "csc_array.hpp"
#include "csc_math.hpp"

namespace CSC {
class Operand ;

namespace U {
template <class ,class>
struct RANK_FUNC ;

template <class _ARG1 ,class... _ARGS>
struct RANK_FUNC<_ARG1 ,ARGVS<_ARGS...>> {
	using TYPE = PTR<_ARG1 (_ARGS...)> ;
} ;

template <class _ARG1>
using RANK_FUNC_TYPE = typename RANK_FUNC<Operand ,REPEAT_OF_TYPE<_ARG1 ,const Operand &>>::TYPE ;
} ;

using RANK0 = U::RANK_FUNC_TYPE<ZERO> ;
using RANK1 = U::RANK_FUNC_TYPE<ARGC<1>> ;
using RANK2 = U::RANK_FUNC_TYPE<ARGC<2>> ;
using RANK3 = U::RANK_FUNC_TYPE<ARGC<3>> ;
using RANK4 = U::RANK_FUNC_TYPE<ARGC<4>> ;
using RANK5 = U::RANK_FUNC_TYPE<ARGC<5>> ;
using RANK6 = U::RANK_FUNC_TYPE<ARGC<6>> ;
using RANK7 = U::RANK_FUNC_TYPE<ARGC<7>> ;
using RANK8 = U::RANK_FUNC_TYPE<ARGC<8>> ;
using RANK9 = U::RANK_FUNC_TYPE<ARGC<9>> ;

class LexicalNode ;

class Operand {
private:
	class Pack {
	private:
		friend Operand ;
		AnyRef<void> mHolder ;
	} ;

private:
	SharedRef<Pack> mThis ;

public:
	Operand () = default ;

	template <class _ARG1 ,class = ENABLE_TYPE<!std::is_same<REMOVE_CVR_TYPE<_ARG1> ,Operand>::value>>
	explicit Operand (_ARG1 &&that) {
		mThis = SharedRef<Pack>::make () ;
		mThis->mHolder = AnyRef<REMOVE_CVR_TYPE<_ARG1>>::make (std::forward<_ARG1> (that)) ;
	}

	BOOL exist () const {
		if (!mThis.exist ())
			return FALSE ;
		if (!mThis->mHolder.exist ())
			return FALSE ;
		return TRUE ;
	}

	BOOL equal (const Operand &that) const {
		if (!mThis.exist ())
			if (!that.mThis.exist ())
				return TRUE ;
		if (!mThis.exist ())
			return FALSE ;
		if (!that.mThis.exist ())
			return FALSE ;
		if (&mThis.self != &that.mThis.self)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const Operand &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const Operand &that) const {
		return !equal (that) ;
	}

	template <class _RET>
	const _RET &as () const & {
		return template_as (_NULL_<ARGV<REMOVE_CVR_TYPE<_RET>>> ()) ;
	}

	template <class _RET>
	const _RET &as () && = delete ;

private:
	template <class _ARG1>
	const _ARG1 &template_as (const ARGV<_ARG1> &) const {
		const auto r1x = exist () ;
		_DYNAMIC_ASSERT_ (r1x) ;
		const auto r2x = mThis->mHolder.typemid () ;
		const auto r3x = _TYPEMID_<_ARG1> () ;
		_DYNAMIC_ASSERT_ (r2x == r3x) ;
		return mThis->mHolder.template rebind<_ARG1> ().self ;
	}

	const Operand &template_as (const ARGV<Operand> &) const {
		return (*this) ;
	}

public:
	template <class _ARG1>
	inline static const Operand &argvp (const ARGV<ARGVP<_ARG1>> &) {
		return _CACHE_ ([&] () {
			return Operand (_NULL_<ARGV<ARGVP<_ARG1>>> ()) ;
		}) ;
	}
} ;

class Operator {
private:
	exports struct Functor
		:public Interface {
		virtual LENGTH rank () const = 0 ;
		virtual Operand invoke (const LexicalNode &node) const = 0 ;
		virtual Operand invoke (const LexicalNode &node ,const Operand &) const = 0 ;
		virtual Operand invoke (const LexicalNode &node ,const Operand & ,const Operand &) const = 0 ;
		virtual Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand &) const = 0 ;
		virtual Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand & ,const Operand &) const = 0 ;
		virtual Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand &) const = 0 ;
		virtual Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand &) const = 0 ;
		virtual Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand &) const = 0 ;
		virtual Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand &) const = 0 ;
		virtual Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand &) const = 0 ;
	} ;

	template <class ,class>
	class ImplFunctor ;

private:
	StrongRef<Functor> mThis ;

public:
	Operator () = default ;

	template <class _ARG1 ,class = ENABLE_TYPE<!std::is_same<REMOVE_CVR_TYPE<_ARG1> ,Operator>::value>>
	explicit Operator (const _ARG1 &that) ;

	LENGTH rank () const {
		if (!mThis.exist ())
			return VAR_NONE ;
		return mThis->rank () ;
	}

	template <class... _ARGS>
	Operand invoke (const LexicalNode &node ,const _ARGS &...args) const {
		_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<_ARGS...>) <= 9) ;
		_DYNAMIC_ASSERT_ (mThis.exist ()) ;
		return mThis->invoke (node ,args...) ;
	}

	template <class... _ARGS>
	inline Operand operator() (const LexicalNode &node ,const _ARGS &...args) const {
		return invoke (node ,args...) ;
	}
} ;

template <>
class Operator::ImplFunctor<void ,void>
	:public Functor {
public:
	ImplFunctor () = default ;

	LENGTH rank () const override {
		return VAR_NONE ;
	}

	Operand invoke (const LexicalNode &node) const override {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	Operand invoke (const LexicalNode &node ,const Operand &) const {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	Operand invoke (const LexicalNode &node ,const Operand & ,const Operand &) const {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand &) const {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand & ,const Operand &) const {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand &) const {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand &) const {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand &) const {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand &) const {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand &) const {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}
} ;

template <class UNIT1 ,class... UNITS1 ,class... UNITS2>
class Operator::ImplFunctor<PTR<UNIT1 (UNITS1...)> ,ARGVS<UNITS2...>>
	:public ImplFunctor<void ,void> {
	_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS1...>) == _CAPACITYOF_ (ARGVS<UNITS2...>)) ;

private:
	Function<UNIT1 (UNITS1...)> mFunction ;

public:
	ImplFunctor () = delete ;

	explicit ImplFunctor (const PTR<UNIT1 (UNITS1...)> &function_)
		:mFunction (function_) {}

	LENGTH rank () const override {
		return _CAPACITYOF_ (ARGVS<UNITS2...>) ;
	}

	Operand invoke (const LexicalNode &node ,const UNITS2 &...args) const {
		auto tmp = template_invoke (mFunction ,TupleBinder<const UNITS2...> (args...) ,_NULL_<ARGV<ARGVS<UNITS1...>>> ()) ;
		return Operand (std::move (tmp)) ;
	}

private:
	static UNIT1 template_invoke (const Function<UNIT1 (UNITS1...)> &func ,const Tuple<> &parameter ,const ARGV<ARGVS<>> & ,FORWARD_TRAITS_TYPE<UNITS1> &&...funcval) popping {
		return func (std::forward<FORWARD_TRAITS_TYPE<UNITS1>> (funcval)...) ;
	}

	//@error: fuck vs2015
	template <class _ARG1 ,class _ARG2 ,class... _ARGS>
	static UNIT1 template_invoke (const Function<UNIT1 (UNITS1...)> &func ,const _ARG1 &parameter ,const ARGV<_ARG2> & ,_ARGS &&...funcval) popping {
		using ONE_HINT = ARGVS_ONE_TYPE<_ARG2> ;
		using REST_HINT = ARGVS_REST_TYPE<_ARG2> ;
		auto &r1x = parameter.one ().template as<ONE_HINT> () ;
		return template_invoke (func ,parameter.rest () ,_NULL_<ARGV<REST_HINT>> () ,std::forward<_ARGS> (funcval)... ,r1x) ;
	}
} ;

template <class UNIT1 ,class... UNITS1 ,class... UNITS2>
class Operator::ImplFunctor<PTR<UNIT1 (const LexicalNode & ,UNITS1...)> ,ARGVS<Operand ,UNITS2...>>
	:public ImplFunctor<void ,void> {
	_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS1...>) == _CAPACITYOF_ (ARGVS<UNITS2...>)) ;

private:
	Function<UNIT1 (const LexicalNode & ,UNITS1...)> mFunction ;

public:
	ImplFunctor () = delete ;

	explicit ImplFunctor (const PTR<UNIT1 (const LexicalNode & ,UNITS1...)> &function_)
		:mFunction (function_) {}

	LENGTH rank () const override {
		return _CAPACITYOF_ (ARGVS<UNITS2...>) ;
	}

	Operand invoke (const LexicalNode &node ,const UNITS2 &...args) const override {
		auto tmp = template_invoke (mFunction ,TupleBinder<const UNITS2...> (args...) ,_NULL_<ARGV<ARGVS<UNITS1...>>> () ,node) ;
		return Operand (std::move (tmp)) ;
	}

private:
	static UNIT1 template_invoke (const Function<UNIT1 (const LexicalNode & ,UNITS1...)> &func ,const Tuple<> &parameter ,const ARGV<ARGVS<>> & ,const LexicalNode &node ,FORWARD_TRAITS_TYPE<UNITS1> &&...funcval) popping {
		return func (node ,std::forward<FORWARD_TRAITS_TYPE<UNITS1>> (funcval)...) ;
	}

	//@error: fuck vs2015
	template <class _ARG1 ,class _ARG2 ,class... _ARGS>
	static UNIT1 template_invoke (const Function<UNIT1 (const LexicalNode & ,UNITS1...)> &func ,const _ARG1 &parameter ,const ARGV<_ARG2> & ,_ARGS &&...funcval) popping {
		using ONE_HINT = ARGVS_ONE_TYPE<_ARG2> ;
		using REST_HINT = ARGVS_REST_TYPE<_ARG2> ;
		auto &r1x = parameter.one ().template as<ONE_HINT> () ;
		return template_invoke (func ,parameter.rest () ,_NULL_<ARGV<REST_HINT>> () ,std::forward<_ARGS> (funcval)... ,r1x) ;
	}
} ;

template <class _ARG1 ,class>
inline Operator::Operator (const _ARG1 &that) {
	using FUNC_HINT = REMOVE_FUNCATTR_TYPE<REMOVE_MEMPTR_TYPE<DEF<decltype (&_ARG1::operator())>>> ;
	using HOLDER_HINT = ImplFunctor<PTR<FUNC_HINT> ,REPEAT_OF_TYPE<ARGC<_CAPACITYOF_ (INVOKE_PARAMS_TYPE<FUNC_HINT>)> ,Operand>> ;
	_STATIC_ASSERT_ (std::is_convertible<_ARG1 ,PTR<FUNC_HINT>>::value) ;
	_STATIC_ASSERT_ (stl::is_complete<HOLDER_HINT>::value) ;
	const auto r1x = _XVALUE_<PTR<FUNC_HINT>> (that) ;
	mThis = StrongRef<HOLDER_HINT>::make (r1x) ;
}

template <class>
class Expression ;

class LexicalNode
	:public Object::Virtual {
private:
	template <class>
	friend class Expression ;
	Operand mOperand ;
	Operator mOperator ;
	ARRAY3<StrongRef<LexicalNode>> mChild ;
	LENGTH mDepth ;

public:
	LexicalNode ()
		:Object (_NULL_<ARGV<LexicalNode>> ()) ,mDepth (0) {}
} ;

template <class TYPE>
class LexicalTree {
private:
	template <class>
	friend class Expression ;
	StrongRef<LexicalNode> mThis ;

public:
	LexicalTree () {
		mThis = StrongRef<LexicalNode>::make () ;
	}

	const StrongRef<LexicalNode> &to () const {
		return mThis ;
	}

	inline implicit operator const StrongRef<LexicalNode> & () const {
		return to () ;
	}

private:
	inline static const TYPE &from (const StrongRef<LexicalNode> &me) {
		return _CAST_<TYPE> (me) ;
	}
} ;

namespace U {
inline constexpr LENGTH constexpr_max_value (const ARGV<ARGVS<>> &) {
	//@error: fuck clang
	return 0 ;
}

template <class _ARG1>
inline constexpr LENGTH constexpr_max_value (const ARGV<ARGVS<_ARG1>> &) {
	return _ARG1::value ;
}

template <class _ARG1>
inline constexpr LENGTH constexpr_max_value (const ARGV<_ARG1> &) {
	using ONE_HINT = ARGVS_ONE_TYPE<_ARG1> ;
	using TWO_HINT = ARGVS_ONE_TYPE<ARGVS_REST_TYPE<_ARG1>> ;
	using BIGGER_HINT = ARGVS<ARGC<_MAX_<VAR> (ONE_HINT::value ,TWO_HINT::value)>> ;
	using REST_HINT = ARGVS_REST_TYPE<ARGVS_REST_TYPE<_ARG1>> ;
	return constexpr_max_value (_NULL_<ARGV<ARGVS_CAT_TYPE<BIGGER_HINT ,REST_HINT>>> ()) ;
}
} ;

template <class... UNITS>
class Expression<SPECIALIZATION<PTR<Operand (const UNITS &...)>>>
	:private LexicalTree<Expression<PTR<Operand (const UNITS &...)>>> {
private:
	using RANK = PTR<Operand (const UNITS &...)> ;

	template <class... _ARGS>
	using FLIP_RETURN_HINT = Expression<U::RANK_FUNC_TYPE<ARGC<U::constexpr_max_value (_NULL_<ARGV<ARGVS<_ARGS...>>> ())>>> ;

private:
	template <class>
	friend class Expression ;
	using LexicalTree<Expression<RANK>>::mThis ;

public:
	Expression () = default ;

	implicit Expression (const Operator &that) {
		_DYNAMIC_ASSERT_ (that.rank () == _CAPACITYOF_ (ARGVS<UNITS...>)) ;
		mThis->mOperator = that ;
		mThis->mDepth = 1 ;
	}

	const Operand &invoke (const UNITS &...args) const {
		_DYNAMIC_ASSERT_ (mThis.exist ()) ;
		if switch_case (TRUE) {
			if (mThis->mOperand.exist ())
				discard ;
			mThis->mOperand = mThis->mOperator (mThis.self ,args...) ;
			mThis->mOperator = Operator () ;
			mThis->mChild[0] = StrongRef<LexicalNode> () ;
			mThis->mChild[1] = StrongRef<LexicalNode> () ;
			mThis->mChild[2] = StrongRef<LexicalNode> () ;

		}
		return mThis->mOperand ;
	}

	Expression<RANK> flip () const {
		Expression<RANK> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const UNITS &...args) {
			auto &r1x = Expression<RANK>::from (node.mChild[0]) ;
			return r1x.template_flip_invoke (_NULL_<ARGV<ARGVS<UNITS...>>> () ,args...) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}

	template <class... _ARGS>
	FLIP_RETURN_HINT<_ARGS...> flip (const ARGV<ARGVP<_ARGS>> &...) const {
		using FLIP_RANK_HINT = U::RANK_FUNC_TYPE<ARGC<U::constexpr_max_value (_NULL_<ARGV<ARGVS<_ARGS...>>> ())>> ;
		return template_flip (_NULL_<ARGV<FLIP_RANK_HINT>> () ,_NULL_<ARGV<ARGVS<_ARGS...>>> () ,_NULL_<ARGV<INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<FLIP_RANK_HINT>>>> ()) ;
	}

private:
	template <class... _ARGS>
	const Operand &template_flip_invoke (const ARGV<ARGVS<>> & ,const _ARGS &...args) const {
		return invoke (args...) ;
	}

	template <class _ARG1 ,class... _ARGS>
	const Operand &template_flip_invoke (const ARGV<_ARG1> & ,const ARGVS_ONE_TYPE<_ARG1> &arg1 ,const _ARGS &...args) const {
		return template_flip_invoke (_NULL_<ARGV<ARGVS_REST_TYPE<_ARG1>>> () ,args... ,arg1) ;
	}

	template <class _ARG1 ,class... _ARGS1 ,class... _ARGS2>
	Expression<_ARG1> template_flip (const ARGV<_ARG1> & ,const ARGV<ARGVS<_ARGS1...>> & ,const ARGV<ARGVS<_ARGS2...>> &) const {
		Expression<_ARG1> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const _ARGS2 &...ins) {
			auto &r1x = Expression<RANK>::from (node.mChild[0]) ;
			const auto r2x = TupleBinder<const _ARGS2...> (ins...) ;
			return r1x.invoke (r2x.pick (_NULL_<ARGV<ARGVP<_ARGS1>>> ())...) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}
} ;

template <>
class Expression<RANK0>
	:private Expression<SPECIALIZATION<RANK0>> {
private:
	using SPECIALIZATION_BASE = Expression<SPECIALIZATION<RANK0>> ;

private:
	template <class>
	friend class Expression ;
	using LexicalTree<Expression<RANK0>>::mThis ;

public:
	Expression () = default ;

	implicit Expression (const Operand &that) {
		_DYNAMIC_ASSERT_ (that.exist ()) ;
		mThis->mOperand = that ;
		mThis->mDepth = 1 ;
	}

	implicit Expression (const Operator &that)
		:SPECIALIZATION_BASE (that) {}

	using SPECIALIZATION_BASE::invoke ;

	template <class... _ARGS>
	inline const Operand &operator() (const _ARGS &...args) const {
		return invoke (args...) ;
	}
} ;

template <>
class Expression<RANK1>
	:private Expression<SPECIALIZATION<RANK1>> {
private:
	using SPECIALIZATION_BASE = Expression<SPECIALIZATION<RANK1>> ;

	template <class _ARG1>
	using CONCAT_RETURN_HINT = Expression<U::RANK_FUNC_TYPE<ARGC<_CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<RANK1>>) - 1 + _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<_ARG1>>)>>> ;

private:
	template <class>
	friend class Expression ;
	using LexicalTree<Expression<RANK1>>::mThis ;

public:
	Expression () = default ;

	implicit Expression (const Operator &that)
		:SPECIALIZATION_BASE (that) {}

	using SPECIALIZATION_BASE::invoke ;

	template <class... _ARGS>
	inline const Operand &operator() (const _ARGS &...args) const {
		return invoke (args...) ;
	}

	using SPECIALIZATION_BASE::flip ;

	Expression<RANK1> curry () const {
		return (*this) ;
	}

	Expression<RANK1> fold () const {
		Expression<RANK1> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
			auto &r2x = in1.template as<Expression<RANK1>> () ;
			auto &r3x = r2x.invoke (Operand::argvp (ARGVP1)) ;
			return r1x.invoke (r3x) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK0> concat (const Expression<RANK0> &that) const ;
	Expression<RANK1> concat (const Expression<RANK1> &that) const ;
	Expression<RANK2> concat (const Expression<RANK2> &that) const ;
	Expression<RANK3> concat (const Expression<RANK3> &that) const ;
	Expression<RANK4> concat (const Expression<RANK4> &that) const ;
	Expression<RANK5> concat (const Expression<RANK5> &that) const ;
	Expression<RANK6> concat (const Expression<RANK6> &that) const ;
	Expression<RANK7> concat (const Expression<RANK7> &that) const ;
	Expression<RANK8> concat (const Expression<RANK8> &that) const ;
	Expression<RANK9> concat (const Expression<RANK9> &that) const ;

	template <class _ARG1>
	inline CONCAT_RETURN_HINT<_ARG1> operator+ (const Expression<_ARG1> &that) const {
		return concat (that) ;
	}
} ;

template <>
class Expression<RANK2>
	:private Expression<SPECIALIZATION<RANK2>> {
private:
	using SPECIALIZATION_BASE = Expression<SPECIALIZATION<RANK2>> ;

	template <class _ARG1>
	using CONCAT_RETURN_HINT = Expression<U::RANK_FUNC_TYPE<ARGC<_CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<RANK2>>) - 1 + _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<_ARG1>>)>>> ;

private:
	template <class>
	friend class Expression ;
	using LexicalTree<Expression<RANK2>>::mThis ;

public:
	Expression () = default ;

	implicit Expression (const Operator &that)
		:SPECIALIZATION_BASE (that) {}

	using SPECIALIZATION_BASE::invoke ;

	template <class... _ARGS>
	inline const Operand &operator() (const _ARGS &...args) const {
		return invoke (args...) ;
	}

	using SPECIALIZATION_BASE::flip ;

	Expression<RANK1> curry () const {
		Expression<RANK1> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
			auto tmp = r1x.concat (in1).curry () ;
			return Operand (std::move (tmp)) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK1> fold () const {
		Expression<RANK1> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
			auto &r2x = in1.template as<Expression<RANK1>> () ;
			auto &r3x = r2x.invoke (Operand::argvp (ARGVP1)) ;
			auto &r4x = r2x.invoke (Operand::argvp (ARGVP2)) ;
			return r1x.invoke (r3x ,r4x) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK1> concat (const Expression<RANK0> &that) const ;
	Expression<RANK2> concat (const Expression<RANK1> &that) const ;
	Expression<RANK3> concat (const Expression<RANK2> &that) const ;
	Expression<RANK4> concat (const Expression<RANK3> &that) const ;
	Expression<RANK5> concat (const Expression<RANK4> &that) const ;
	Expression<RANK6> concat (const Expression<RANK5> &that) const ;
	Expression<RANK7> concat (const Expression<RANK6> &that) const ;
	Expression<RANK8> concat (const Expression<RANK7> &that) const ;
	Expression<RANK9> concat (const Expression<RANK8> &that) const ;

	template <class _ARG1>
	inline CONCAT_RETURN_HINT<_ARG1> operator+ (const Expression<_ARG1> &that) const {
		return concat (that) ;
	}
} ;

template <>
class Expression<RANK3>
	:private Expression<SPECIALIZATION<RANK3>> {
private:
	using SPECIALIZATION_BASE = Expression<SPECIALIZATION<RANK3>> ;

	template <class _ARG1>
	using CONCAT_RETURN_HINT = Expression<U::RANK_FUNC_TYPE<ARGC<_CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<RANK3>>) - 1 + _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<_ARG1>>)>>> ;

private:
	template <class>
	friend class Expression ;
	using LexicalTree<Expression<RANK3>>::mThis ;

public:
	Expression () = default ;

	implicit Expression (const Operator &that)
		:SPECIALIZATION_BASE (that) {}

	using SPECIALIZATION_BASE::invoke ;

	template <class... _ARGS>
	inline const Operand &operator() (const _ARGS &...args) const {
		return invoke (args...) ;
	}

	using SPECIALIZATION_BASE::flip ;

	Expression<RANK1> curry () const {
		Expression<RANK1> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK3>::from (node.mChild[0]) ;
			auto tmp = r1x.concat (in1).curry () ;
			return Operand (std::move (tmp)) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK1> fold () const {
		Expression<RANK1> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK3>::from (node.mChild[0]) ;
			auto &r2x = in1.template as<Expression<RANK1>> () ;
			auto &r3x = r2x.invoke (Operand::argvp (ARGVP1)) ;
			auto &r4x = r2x.invoke (Operand::argvp (ARGVP2)) ;
			auto &r5x = r2x.invoke (Operand::argvp (ARGVP3)) ;
			return r1x.invoke (r3x ,r4x ,r5x) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK2> concat (const Expression<RANK0> &that) const ;
	Expression<RANK3> concat (const Expression<RANK1> &that) const ;
	Expression<RANK4> concat (const Expression<RANK2> &that) const ;
	Expression<RANK5> concat (const Expression<RANK3> &that) const ;
	Expression<RANK6> concat (const Expression<RANK4> &that) const ;
	Expression<RANK7> concat (const Expression<RANK5> &that) const ;
	Expression<RANK8> concat (const Expression<RANK6> &that) const ;
	Expression<RANK9> concat (const Expression<RANK7> &that) const ;

	template <class _ARG1>
	inline CONCAT_RETURN_HINT<_ARG1> operator+ (const Expression<_ARG1> &that) const {
		return concat (that) ;
	}
} ;

template <>
class Expression<RANK4>
	:private Expression<SPECIALIZATION<RANK4>> {
private:
	using SPECIALIZATION_BASE = Expression<SPECIALIZATION<RANK4>> ;

	template <class _ARG1>
	using CONCAT_RETURN_HINT = Expression<U::RANK_FUNC_TYPE<ARGC<_CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<RANK4>>) - 1 + _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<_ARG1>>)>>> ;

private:
	template <class>
	friend class Expression ;
	using LexicalTree<Expression<RANK4>>::mThis ;

public:
	Expression () = default ;

	implicit Expression (const Operator &that)
		:SPECIALIZATION_BASE (that) {}

	using SPECIALIZATION_BASE::invoke ;

	template <class... _ARGS>
	inline const Operand &operator() (const _ARGS &...args) const {
		return invoke (args...) ;
	}

	using SPECIALIZATION_BASE::flip ;

	Expression<RANK1> curry () const {
		Expression<RANK1> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK4>::from (node.mChild[0]) ;
			auto tmp = r1x.concat (in1).curry () ;
			return Operand (std::move (tmp)) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK1> fold () const {
		Expression<RANK1> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK4>::from (node.mChild[0]) ;
			auto &r2x = in1.template as<Expression<RANK1>> () ;
			auto &r3x = r2x.invoke (Operand::argvp (ARGVP1)) ;
			auto &r4x = r2x.invoke (Operand::argvp (ARGVP2)) ;
			auto &r5x = r2x.invoke (Operand::argvp (ARGVP3)) ;
			auto &r6x = r2x.invoke (Operand::argvp (ARGVP4)) ;
			return r1x.invoke (r3x ,r4x ,r5x ,r6x) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK3> concat (const Expression<RANK0> &that) const ;
	Expression<RANK4> concat (const Expression<RANK1> &that) const ;
	Expression<RANK5> concat (const Expression<RANK2> &that) const ;
	Expression<RANK6> concat (const Expression<RANK3> &that) const ;
	Expression<RANK7> concat (const Expression<RANK4> &that) const ;
	Expression<RANK8> concat (const Expression<RANK5> &that) const ;
	Expression<RANK9> concat (const Expression<RANK6> &that) const ;

	template <class _ARG1>
	inline CONCAT_RETURN_HINT<_ARG1> operator+ (const Expression<_ARG1> &that) const {
		return concat (that) ;
	}
} ;

template <>
class Expression<RANK5>
	:private Expression<SPECIALIZATION<RANK5>> {
private:
	using SPECIALIZATION_BASE = Expression<SPECIALIZATION<RANK5>> ;

	template <class _ARG1>
	using CONCAT_RETURN_HINT = Expression<U::RANK_FUNC_TYPE<ARGC<_CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<RANK5>>) - 1 + _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<_ARG1>>)>>> ;

private:
	template <class>
	friend class Expression ;
	using LexicalTree<Expression<RANK5>>::mThis ;

public:
	Expression () = default ;

	implicit Expression (const Operator &that)
		:SPECIALIZATION_BASE (that) {}

	using SPECIALIZATION_BASE::invoke ;

	template <class... _ARGS>
	inline const Operand &operator() (const _ARGS &...args) const {
		return invoke (args...) ;
	}

	using SPECIALIZATION_BASE::flip ;

	Expression<RANK1> curry () const {
		Expression<RANK1> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK5>::from (node.mChild[0]) ;
			auto tmp = r1x.concat (in1).curry () ;
			return Operand (std::move (tmp)) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK1> fold () const {
		Expression<RANK1> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK5>::from (node.mChild[0]) ;
			auto &r2x = in1.template as<Expression<RANK1>> () ;
			auto &r3x = r2x.invoke (Operand::argvp (ARGVP1)) ;
			auto &r4x = r2x.invoke (Operand::argvp (ARGVP2)) ;
			auto &r5x = r2x.invoke (Operand::argvp (ARGVP3)) ;
			auto &r6x = r2x.invoke (Operand::argvp (ARGVP4)) ;
			auto &r7x = r2x.invoke (Operand::argvp (ARGVP5)) ;
			return r1x.invoke (r3x ,r4x ,r5x ,r6x ,r7x) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK4> concat (const Expression<RANK0> &that) const ;
	Expression<RANK5> concat (const Expression<RANK1> &that) const ;
	Expression<RANK6> concat (const Expression<RANK2> &that) const ;
	Expression<RANK7> concat (const Expression<RANK3> &that) const ;
	Expression<RANK8> concat (const Expression<RANK4> &that) const ;
	Expression<RANK9> concat (const Expression<RANK5> &that) const ;

	template <class _ARG1>
	inline CONCAT_RETURN_HINT<_ARG1> operator+ (const Expression<_ARG1> &that) const {
		return concat (that) ;
	}
} ;

template <>
class Expression<RANK6>
	:private Expression<SPECIALIZATION<RANK6>> {
private:
	using SPECIALIZATION_BASE = Expression<SPECIALIZATION<RANK6>> ;

	template <class _ARG1>
	using CONCAT_RETURN_HINT = Expression<U::RANK_FUNC_TYPE<ARGC<_CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<RANK6>>) - 1 + _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<_ARG1>>)>>> ;

private:
	template <class>
	friend class Expression ;
	using LexicalTree<Expression<RANK6>>::mThis ;

public:
	Expression () = default ;

	implicit Expression (const Operator &that)
		:SPECIALIZATION_BASE (that) {}

	using SPECIALIZATION_BASE::invoke ;

	template <class... _ARGS>
	inline const Operand &operator() (const _ARGS &...args) const {
		return invoke (args...) ;
	}

	using SPECIALIZATION_BASE::flip ;

	Expression<RANK1> curry () const {
		Expression<RANK1> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK6>::from (node.mChild[0]) ;
			auto tmp = r1x.concat (in1).curry () ;
			return Operand (std::move (tmp)) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK1> fold () const {
		Expression<RANK1> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK6>::from (node.mChild[0]) ;
			auto &r2x = in1.template as<Expression<RANK1>> () ;
			auto &r3x = r2x.invoke (Operand::argvp (ARGVP1)) ;
			auto &r4x = r2x.invoke (Operand::argvp (ARGVP2)) ;
			auto &r5x = r2x.invoke (Operand::argvp (ARGVP3)) ;
			auto &r6x = r2x.invoke (Operand::argvp (ARGVP4)) ;
			auto &r7x = r2x.invoke (Operand::argvp (ARGVP5)) ;
			auto &r8x = r2x.invoke (Operand::argvp (ARGVP6)) ;
			return r1x.invoke (r3x ,r4x ,r5x ,r6x ,r7x ,r8x) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK5> concat (const Expression<RANK0> &that) const ;
	Expression<RANK6> concat (const Expression<RANK1> &that) const ;
	Expression<RANK7> concat (const Expression<RANK2> &that) const ;
	Expression<RANK8> concat (const Expression<RANK3> &that) const ;
	Expression<RANK9> concat (const Expression<RANK4> &that) const ;

	template <class _ARG1>
	inline CONCAT_RETURN_HINT<_ARG1> operator+ (const Expression<_ARG1> &that) const {
		return concat (that) ;
	}
} ;

template <>
class Expression<RANK7>
	:private Expression<SPECIALIZATION<RANK7>> {
private:
	using SPECIALIZATION_BASE = Expression<SPECIALIZATION<RANK7>> ;

	template <class _ARG1>
	using CONCAT_RETURN_HINT = Expression<U::RANK_FUNC_TYPE<ARGC<_CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<RANK7>>) - 1 + _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<_ARG1>>)>>> ;

private:
	template <class>
	friend class Expression ;
	using LexicalTree<Expression<RANK7>>::mThis ;

public:
	Expression () = default ;

	implicit Expression (const Operator &that)
		:SPECIALIZATION_BASE (that) {}

	using SPECIALIZATION_BASE::invoke ;

	template <class... _ARGS>
	inline const Operand &operator() (const _ARGS &...args) const {
		return invoke (args...) ;
	}

	using SPECIALIZATION_BASE::flip ;

	Expression<RANK1> curry () const {
		Expression<RANK1> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK7>::from (node.mChild[0]) ;
			auto tmp = r1x.concat (in1).curry () ;
			return Operand (std::move (tmp)) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK1> fold () const {
		Expression<RANK1> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK7>::from (node.mChild[0]) ;
			auto &r2x = in1.template as<Expression<RANK1>> () ;
			auto &r3x = r2x.invoke (Operand::argvp (ARGVP1)) ;
			auto &r4x = r2x.invoke (Operand::argvp (ARGVP2)) ;
			auto &r5x = r2x.invoke (Operand::argvp (ARGVP3)) ;
			auto &r6x = r2x.invoke (Operand::argvp (ARGVP4)) ;
			auto &r7x = r2x.invoke (Operand::argvp (ARGVP5)) ;
			auto &r8x = r2x.invoke (Operand::argvp (ARGVP6)) ;
			auto &r9x = r2x.invoke (Operand::argvp (ARGVP7)) ;
			return r1x.invoke (r3x ,r4x ,r5x ,r6x ,r7x ,r8x ,r9x) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK6> concat (const Expression<RANK0> &that) const ;
	Expression<RANK7> concat (const Expression<RANK1> &that) const ;
	Expression<RANK8> concat (const Expression<RANK2> &that) const ;
	Expression<RANK9> concat (const Expression<RANK3> &that) const ;

	template <class _ARG1>
	inline CONCAT_RETURN_HINT<_ARG1> operator+ (const Expression<_ARG1> &that) const {
		return concat (that) ;
	}
} ;

template <>
class Expression<RANK8>
	:private Expression<SPECIALIZATION<RANK8>> {
private:
	using SPECIALIZATION_BASE = Expression<SPECIALIZATION<RANK8>> ;

	template <class _ARG1>
	using CONCAT_RETURN_HINT = Expression<U::RANK_FUNC_TYPE<ARGC<_CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<RANK8>>) - 1 + _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<_ARG1>>)>>> ;

private:
	template <class>
	friend class Expression ;
	using LexicalTree<Expression<RANK8>>::mThis ;

public:
	Expression () = default ;

	implicit Expression (const Operator &that)
		:SPECIALIZATION_BASE (that) {}

	using SPECIALIZATION_BASE::invoke ;

	template <class... _ARGS>
	inline const Operand &operator() (const _ARGS &...args) const {
		return invoke (args...) ;
	}

	using SPECIALIZATION_BASE::flip ;

	Expression<RANK1> curry () const {
		Expression<RANK1> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK8>::from (node.mChild[0]) ;
			auto tmp = r1x.concat (in1).curry () ;
			return Operand (std::move (tmp)) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK1> fold () const {
		Expression<RANK1> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK8>::from (node.mChild[0]) ;
			auto &r2x = in1.template as<Expression<RANK1>> () ;
			auto &r3x = r2x.invoke (Operand::argvp (ARGVP1)) ;
			auto &r4x = r2x.invoke (Operand::argvp (ARGVP2)) ;
			auto &r5x = r2x.invoke (Operand::argvp (ARGVP3)) ;
			auto &r6x = r2x.invoke (Operand::argvp (ARGVP4)) ;
			auto &r7x = r2x.invoke (Operand::argvp (ARGVP5)) ;
			auto &r8x = r2x.invoke (Operand::argvp (ARGVP6)) ;
			auto &r9x = r2x.invoke (Operand::argvp (ARGVP7)) ;
			auto &r10x = r2x.invoke (Operand::argvp (ARGVP8)) ;
			return r1x.invoke (r3x ,r4x ,r5x ,r6x ,r7x ,r8x ,r9x ,r10x) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK7> concat (const Expression<RANK0> &that) const ;
	Expression<RANK8> concat (const Expression<RANK1> &that) const ;
	Expression<RANK9> concat (const Expression<RANK2> &that) const ;

	template <class _ARG1>
	inline CONCAT_RETURN_HINT<_ARG1> operator+ (const Expression<_ARG1> &that) const {
		return concat (that) ;
	}
} ;

template <>
class Expression<RANK9>
	:private Expression<SPECIALIZATION<RANK9>> {
private:
	using SPECIALIZATION_BASE = Expression<SPECIALIZATION<RANK9>> ;

	template <class _ARG1>
	using CONCAT_RETURN_HINT = Expression<U::RANK_FUNC_TYPE<ARGC<_CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<RANK9>>) - 1 + _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<_ARG1>>)>>> ;

private:
	template <class>
	friend class Expression ;
	using LexicalTree<Expression<RANK9>>::mThis ;

public:
	Expression () = default ;

	implicit Expression (const Operator &that)
		:SPECIALIZATION_BASE (that) {}

	using SPECIALIZATION_BASE::invoke ;

	template <class... _ARGS>
	inline const Operand &operator() (const _ARGS &...args) const {
		return invoke (args...) ;
	}

	using SPECIALIZATION_BASE::flip ;

	Expression<RANK1> curry () const {
		Expression<RANK1> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK9>::from (node.mChild[0]) ;
			auto tmp = r1x.concat (in1).curry () ;
			return Operand (std::move (tmp)) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK1> fold () const {
		Expression<RANK1> ret ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK9>::from (node.mChild[0]) ;
			auto &r2x = in1.template as<Expression<RANK1>> () ;
			auto &r3x = r2x.invoke (Operand::argvp (ARGVP1)) ;
			auto &r4x = r2x.invoke (Operand::argvp (ARGVP2)) ;
			auto &r5x = r2x.invoke (Operand::argvp (ARGVP3)) ;
			auto &r6x = r2x.invoke (Operand::argvp (ARGVP4)) ;
			auto &r7x = r2x.invoke (Operand::argvp (ARGVP5)) ;
			auto &r8x = r2x.invoke (Operand::argvp (ARGVP6)) ;
			auto &r9x = r2x.invoke (Operand::argvp (ARGVP7)) ;
			auto &r10x = r2x.invoke (Operand::argvp (ARGVP8)) ;
			auto &r11x = r2x.invoke (Operand::argvp (ARGVP9)) ;
			return r1x.invoke (r3x ,r4x ,r5x ,r6x ,r7x ,r8x ,r9x ,r10x ,r11x) ;
		}) ;
		ret.mThis->mChild[0] = (*this) ;
		ret.mThis->mDepth = _MAXOF_ (mThis->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK8> concat (const Expression<RANK0> &that) const ;
	Expression<RANK9> concat (const Expression<RANK1> &that) const ;

	template <class _ARG1>
	inline CONCAT_RETURN_HINT<_ARG1> operator+ (const Expression<_ARG1> &that) const {
		return concat (that) ;
	}
} ;

inline Expression<RANK0> Expression<RANK1>::concat (const Expression<RANK0> &that) const {
	Expression<RANK0> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node) {
		auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK0>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke ()) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK1> Expression<RANK1>::concat (const Expression<RANK1> &that) const {
	Expression<RANK1> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
		auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK1>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1)) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK2> Expression<RANK1>::concat (const Expression<RANK2> &that) const {
	Expression<RANK2> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) {
		auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK2>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2)) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK3> Expression<RANK1>::concat (const Expression<RANK3> &that) const {
	Expression<RANK3> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) {
		auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK3>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3)) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK4> Expression<RANK1>::concat (const Expression<RANK4> &that) const {
	Expression<RANK4> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4) {
		auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK4>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4)) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK5> Expression<RANK1>::concat (const Expression<RANK5> &that) const {
	Expression<RANK5> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5) {
		auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK5>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4 ,in5)) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK6> Expression<RANK1>::concat (const Expression<RANK6> &that) const {
	Expression<RANK6> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6) {
		auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK6>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4 ,in5 ,in6)) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK7> Expression<RANK1>::concat (const Expression<RANK7> &that) const {
	Expression<RANK7> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7) {
		auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK7>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4 ,in5 ,in6 ,in7)) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK8> Expression<RANK1>::concat (const Expression<RANK8> &that) const {
	Expression<RANK8> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7 ,const Operand &in8) {
		auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK8>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4 ,in5 ,in6 ,in7 ,in8)) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK9> Expression<RANK1>::concat (const Expression<RANK9> &that) const {
	Expression<RANK9> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7 ,const Operand &in8 ,const Operand &in9) {
		auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK9>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4 ,in5 ,in6 ,in7 ,in8 ,in9)) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK1> Expression<RANK2>::concat (const Expression<RANK0> &that) const {
	Expression<RANK1> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
		auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK0>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke () ,in1) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK2> Expression<RANK2>::concat (const Expression<RANK1> &that) const {
	Expression<RANK2> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) {
		auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK1>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1) ,in2) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK3> Expression<RANK2>::concat (const Expression<RANK2> &that) const {
	Expression<RANK3> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) {
		auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK2>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2) ,in3) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK4> Expression<RANK2>::concat (const Expression<RANK3> &that) const {
	Expression<RANK4> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4) {
		auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK3>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3) ,in4) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK5> Expression<RANK2>::concat (const Expression<RANK4> &that) const {
	Expression<RANK5> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5) {
		auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK4>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4) ,in5) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK6> Expression<RANK2>::concat (const Expression<RANK5> &that) const {
	Expression<RANK6> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6) {
		auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK5>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4 ,in5) ,in6) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK7> Expression<RANK2>::concat (const Expression<RANK6> &that) const {
	Expression<RANK7> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7) {
		auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK6>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4 ,in5 ,in6) ,in7) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK8> Expression<RANK2>::concat (const Expression<RANK7> &that) const {
	Expression<RANK8> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7 ,const Operand &in8) {
		auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK7>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4 ,in5 ,in6 ,in7) ,in8) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK9> Expression<RANK2>::concat (const Expression<RANK8> &that) const {
	Expression<RANK9> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7 ,const Operand &in8 ,const Operand &in9) {
		auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK8>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4 ,in5 ,in6 ,in7 ,in8) ,in9) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK2> Expression<RANK3>::concat (const Expression<RANK0> &that) const {
	Expression<RANK2> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) {
		auto &r1x = Expression<RANK3>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK0>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke () ,in1 ,in2) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK3> Expression<RANK3>::concat (const Expression<RANK1> &that) const {
	Expression<RANK3> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) {
		auto &r1x = Expression<RANK3>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK1>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1) ,in2 ,in3) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK4> Expression<RANK3>::concat (const Expression<RANK2> &that) const {
	Expression<RANK4> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4) {
		auto &r1x = Expression<RANK3>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK2>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2) ,in3 ,in4) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK5> Expression<RANK3>::concat (const Expression<RANK3> &that) const {
	Expression<RANK5> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5) {
		auto &r1x = Expression<RANK3>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK3>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3) ,in4 ,in5) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK6> Expression<RANK3>::concat (const Expression<RANK4> &that) const {
	Expression<RANK6> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6) {
		auto &r1x = Expression<RANK3>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK4>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4) ,in5 ,in6) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK7> Expression<RANK3>::concat (const Expression<RANK5> &that) const {
	Expression<RANK7> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7) {
		auto &r1x = Expression<RANK3>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK5>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4 ,in5) ,in6 ,in7) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK8> Expression<RANK3>::concat (const Expression<RANK6> &that) const {
	Expression<RANK8> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7 ,const Operand &in8) {
		auto &r1x = Expression<RANK3>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK6>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4 ,in5 ,in6) ,in7 ,in8) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK9> Expression<RANK3>::concat (const Expression<RANK7> &that) const {
	Expression<RANK9> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7 ,const Operand &in8 ,const Operand &in9) {
		auto &r1x = Expression<RANK3>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK7>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4 ,in5 ,in6 ,in7) ,in8 ,in9) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK3> Expression<RANK4>::concat (const Expression<RANK0> &that) const {
	Expression<RANK3> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) {
		auto &r1x = Expression<RANK4>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK0>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke () ,in1 ,in2 ,in3) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK4> Expression<RANK4>::concat (const Expression<RANK1> &that) const {
	Expression<RANK4> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4) {
		auto &r1x = Expression<RANK4>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK1>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1) ,in2 ,in3 ,in4) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK5> Expression<RANK4>::concat (const Expression<RANK2> &that) const {
	Expression<RANK5> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5) {
		auto &r1x = Expression<RANK4>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK2>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2) ,in3 ,in4 ,in5) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK6> Expression<RANK4>::concat (const Expression<RANK3> &that) const {
	Expression<RANK6> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6) {
		auto &r1x = Expression<RANK4>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK3>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3) ,in4 ,in5 ,in6) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK7> Expression<RANK4>::concat (const Expression<RANK4> &that) const {
	Expression<RANK7> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7) {
		auto &r1x = Expression<RANK4>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK4>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4) ,in5 ,in6 ,in7) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK8> Expression<RANK4>::concat (const Expression<RANK5> &that) const {
	Expression<RANK8> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7 ,const Operand &in8) {
		auto &r1x = Expression<RANK4>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK5>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4 ,in5) ,in6 ,in7 ,in8) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK9> Expression<RANK4>::concat (const Expression<RANK6> &that) const {
	Expression<RANK9> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7 ,const Operand &in8 ,const Operand &in9) {
		auto &r1x = Expression<RANK4>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK6>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4 ,in5 ,in6) ,in7 ,in8 ,in9) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK4> Expression<RANK5>::concat (const Expression<RANK0> &that) const {
	Expression<RANK4> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4) {
		auto &r1x = Expression<RANK5>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK0>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke () ,in1 ,in2 ,in3 ,in4) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK5> Expression<RANK5>::concat (const Expression<RANK1> &that) const {
	Expression<RANK5> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5) {
		auto &r1x = Expression<RANK5>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK1>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1) ,in2 ,in3 ,in4 ,in5) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK6> Expression<RANK5>::concat (const Expression<RANK2> &that) const {
	Expression<RANK6> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6) {
		auto &r1x = Expression<RANK5>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK2>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2) ,in3 ,in4 ,in5 ,in6) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK7> Expression<RANK5>::concat (const Expression<RANK3> &that) const {
	Expression<RANK7> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7) {
		auto &r1x = Expression<RANK5>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK3>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3) ,in4 ,in5 ,in6 ,in7) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK8> Expression<RANK5>::concat (const Expression<RANK4> &that) const {
	Expression<RANK8> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7 ,const Operand &in8) {
		auto &r1x = Expression<RANK5>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK4>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4) ,in5 ,in6 ,in7 ,in8) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK9> Expression<RANK5>::concat (const Expression<RANK5> &that) const {
	Expression<RANK9> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7 ,const Operand &in8 ,const Operand &in9) {
		auto &r1x = Expression<RANK5>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK5>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4 ,in5) ,in6 ,in7 ,in8 ,in9) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK5> Expression<RANK6>::concat (const Expression<RANK0> &that) const {
	Expression<RANK5> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5) {
		auto &r1x = Expression<RANK6>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK0>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke () ,in1 ,in2 ,in3 ,in4 ,in5) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK6> Expression<RANK6>::concat (const Expression<RANK1> &that) const {
	Expression<RANK6> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6) {
		auto &r1x = Expression<RANK6>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK1>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1) ,in2 ,in3 ,in4 ,in5 ,in6) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK7> Expression<RANK6>::concat (const Expression<RANK2> &that) const {
	Expression<RANK7> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7) {
		auto &r1x = Expression<RANK6>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK2>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2) ,in3 ,in4 ,in5 ,in6 ,in7) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK8> Expression<RANK6>::concat (const Expression<RANK3> &that) const {
	Expression<RANK8> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7 ,const Operand &in8) {
		auto &r1x = Expression<RANK6>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK3>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3) ,in4 ,in5 ,in6 ,in7 ,in8) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK9> Expression<RANK6>::concat (const Expression<RANK4> &that) const {
	Expression<RANK9> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7 ,const Operand &in8 ,const Operand &in9) {
		auto &r1x = Expression<RANK6>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK4>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3 ,in4) ,in5 ,in6 ,in7 ,in8 ,in9) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK6> Expression<RANK7>::concat (const Expression<RANK0> &that) const {
	Expression<RANK6> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6) {
		auto &r1x = Expression<RANK7>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK0>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke () ,in1 ,in2 ,in3 ,in4 ,in5 ,in6) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK7> Expression<RANK7>::concat (const Expression<RANK1> &that) const {
	Expression<RANK7> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7) {
		auto &r1x = Expression<RANK7>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK1>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1) ,in2 ,in3 ,in4 ,in5 ,in6 ,in7) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK8> Expression<RANK7>::concat (const Expression<RANK2> &that) const {
	Expression<RANK8> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7 ,const Operand &in8) {
		auto &r1x = Expression<RANK7>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK2>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2) ,in3 ,in4 ,in5 ,in6 ,in7 ,in8) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK9> Expression<RANK7>::concat (const Expression<RANK3> &that) const {
	Expression<RANK9> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7 ,const Operand &in8 ,const Operand &in9) {
		auto &r1x = Expression<RANK7>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK3>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2 ,in3) ,in4 ,in5 ,in6 ,in7 ,in8 ,in9) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK7> Expression<RANK8>::concat (const Expression<RANK0> &that) const {
	Expression<RANK7> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7) {
		auto &r1x = Expression<RANK8>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK0>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke () ,in1 ,in2 ,in3 ,in4 ,in5 ,in6 ,in7) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK8> Expression<RANK8>::concat (const Expression<RANK1> &that) const {
	Expression<RANK8> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7 ,const Operand &in8) {
		auto &r1x = Expression<RANK8>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK1>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1) ,in2 ,in3 ,in4 ,in5 ,in6 ,in7 ,in8) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK9> Expression<RANK8>::concat (const Expression<RANK2> &that) const {
	Expression<RANK9> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7 ,const Operand &in8 ,const Operand &in9) {
		auto &r1x = Expression<RANK8>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK2>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1 ,in2) ,in3 ,in4 ,in5 ,in6 ,in7 ,in8 ,in9) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK8> Expression<RANK9>::concat (const Expression<RANK0> &that) const {
	Expression<RANK8> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7 ,const Operand &in8) {
		auto &r1x = Expression<RANK9>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK0>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke () ,in1 ,in2 ,in3 ,in4 ,in5 ,in6 ,in7 ,in8) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK9> Expression<RANK9>::concat (const Expression<RANK1> &that) const {
	Expression<RANK9> ret ;
	ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4 ,const Operand &in5 ,const Operand &in6 ,const Operand &in7 ,const Operand &in8 ,const Operand &in9) {
		auto &r1x = Expression<RANK9>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK1>::from (node.mChild[1]) ;
		return r1x.invoke (r2x.invoke (in1) ,in2 ,in3 ,in4 ,in5 ,in6 ,in7 ,in8 ,in9) ;
	}) ;
	ret.mThis->mChild[0] = (*this) ;
	ret.mThis->mChild[1] = that ;
	ret.mThis->mDepth = _MAXOF_ (mThis->mDepth ,that.mThis->mDepth) + 1 ;
	return std::move (ret) ;
}
} ;