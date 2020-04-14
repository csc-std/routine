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
template <class>
struct RANK_FUNC ;

template <class... _ARGS>
struct RANK_FUNC<ARGVS<_ARGS...>> {
	using TYPE = PTR<Operand (const _ARGS &...)> ;
} ;

template <class _ARG1>
using RANK_FUNC_TYPE = typename RANK_FUNC<REPEAT_OF_TYPE<_ARG1 ,Operand>>::TYPE ;
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

namespace U {
template <class>
struct CONTEXT_RANK_FUNC ;

template <class... _ARGS>
struct CONTEXT_RANK_FUNC<PTR<Operand (const _ARGS &...)>> {
	using TYPE = PTR<Operand (const LexicalNode & ,const _ARGS &...)> ;
} ;

template <class _ARG1>
using CONTEXT_RANK_FUNC_TYPE = typename CONTEXT_RANK_FUNC<_ARG1>::TYPE ;
} ;

class Operand {
private:
	class Pack {
	private:
		friend Operand ;
		AnyRef<void> mValue ;
		AnyRef<void> mEvaluation ;
	} ;

private:
	SharedRef<Pack> mLazy ;

public:
	inline Operand () = default ;

	template <class _ARG1 ,class = ENABLE_TYPE<!std::is_same<REMOVE_CVR_TYPE<_ARG1> ,Operand>::value>>
	inline implicit Operand (_ARG1 &&that) {
		mLazy = SharedRef<Pack>::make () ;
		mLazy->mValue = AnyRef<REMOVE_CVR_TYPE<_ARG1>>::make (std::forward<_ARG1> (that)) ;
	}

	inline BOOL exist () const {
		if (!mLazy.exist ())
			return FALSE ;
		return mLazy->mValue.exist () ;
	}

	template <class _RET>
	inline const _RET &as () const & {
		return template_as (_NULL_<ARGV<REMOVE_CVR_TYPE<_RET>>> ()) ;
	}

	template <class _RET>
	inline const _RET &as () const && = delete ;

private:
	template <class _ARG1>
	inline const _ARG1 &template_as (const ARGV<_ARG1> &) const {
		const auto r1x = exist () ;
		_DYNAMIC_ASSERT_ (r1x) ;
		const auto r2x = mLazy->mValue.typemid () ;
		const auto r3x = _TYPEMID_<_ARG1> () ;
		_DYNAMIC_ASSERT_ (r2x == r3x) ;
		return mLazy->mValue.template rebind<_ARG1> ().self ;
	}

	inline const Operand &template_as (const ARGV<Operand> &) const {
		return (*this) ;
	}
} ;

class Operator {
private:
	exports struct Holder :public Interface {
		virtual LENGTH rank () const = 0 ;
		virtual Operand invoke (const LexicalNode &node) const = 0 ;
		virtual Operand invoke (const LexicalNode &node ,const Operand &in1) const = 0 ;
		virtual Operand invoke (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) const = 0 ;
		virtual Operand invoke (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) const = 0 ;
	} ;

	template <class>
	class ImplHolder ;

private:
	PTR<Holder> mHolder ;

public:
	inline Operator () {
		mHolder = NULL ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<!std::is_same<REMOVE_CVR_TYPE<_ARG1> ,Operator>::value>>
	inline implicit Operator (const _ARG1 &that) ;

	inline LENGTH rank () const {
		if (mHolder == NULL)
			return VAR_NONE ;
		return mHolder->rank () ;
	}

	inline Operand operator() (const LexicalNode &node) const {
		_DYNAMIC_ASSERT_ (mHolder != NULL) ;
		return mHolder->invoke (node) ;
	}

	inline Operand operator() (const LexicalNode &node ,const Operand &in1) const {
		_DYNAMIC_ASSERT_ (mHolder != NULL) ;
		return mHolder->invoke (node ,in1) ;
	}

	inline Operand operator() (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) const {
		_DYNAMIC_ASSERT_ (mHolder != NULL) ;
		return mHolder->invoke (node ,in1 ,in2) ;
	}

	inline Operand operator() (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) const {
		_DYNAMIC_ASSERT_ (mHolder != NULL) ;
		return mHolder->invoke (node ,in1 ,in2 ,in3) ;
	}
} ;

template <>
class Operator::ImplHolder<void> :public Holder {
public:
	inline ImplHolder () = delete ;

	inline LENGTH rank () const override {
		return VAR_NONE ;
	}

	inline Operand invoke (const LexicalNode &node) const override {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	inline Operand invoke (const LexicalNode &node ,const Operand &in1) const {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	inline Operand invoke (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) const {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	inline Operand invoke (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) const {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}
} ;

template <class _ARG1 ,class... _ARGS>
class Operator::ImplHolder<PTR<_ARG1 (const _ARGS &...)>> :public ImplHolder<void> {
private:
	using RANK = PTR<_ARG1 (const _ARGS &...)> ;

private:
	RANK mFunction ;

public:
	inline ImplHolder () = delete ;

	inline explicit ImplHolder (const RANK &function_) :mFunction (function_) {}

	inline LENGTH rank () const override {
		return _CAPACITYOF_ (ARGVS<_ARGS...>) ;
	}

	inline _ARG1 invoke (const LexicalNode &node ,const _ARGS &...args) const override {
		return mFunction (args...) ;
	}
} ;

template <class _ARG1 ,class... _ARGS>
class Operator::ImplHolder<PTR<_ARG1 (const LexicalNode & ,const _ARGS &...)>> :public ImplHolder<void> {
private:
	using RANK = PTR<_ARG1 (const LexicalNode & ,const _ARGS &...)> ;

private:
	RANK mFunction ;

public:
	inline ImplHolder () = delete ;

	inline explicit ImplHolder (const RANK &function_) :mFunction (function_) {}

	inline LENGTH rank () const override {
		return _CAPACITYOF_ (ARGVS<_ARGS...>) ;
	}

	inline _ARG1 invoke (const LexicalNode &node ,const _ARGS &...args) const override {
		return mFunction (node ,args...) ;
	}
} ;

template <class _ARG1 ,class>
inline Operator::Operator (const _ARG1 &that) {
	using RANK = PTR<REMOVE_FUNCATTR_TYPE<REMOVE_MEMPTR_TYPE<DEF<decltype (&_ARG1::operator())>>>> ;
	_STATIC_ASSERT_ (std::is_convertible<_ARG1 ,RANK>::value) ;
	_STATIC_ASSERT_ (stl::is_complete<ImplHolder<RANK>>::value) ;
	auto &r1x = _CACHE_ ([&] () {
		return SharedRef<Set<RANK ,AutoRef<ImplHolder<RANK>>>>::make () ;
	}) ;
	const auto r2x = _XVALUE_<RANK> (that) ;
	_DEBUG_ASSERT_ (r2x != NULL) ;
	INDEX ix = r1x->find (r2x) ;
	if switch_case (TRUE) {
		if (ix != VAR_NONE)
			discard ;
		ix = r1x->insert (r2x) ;
		r1x.self[ix].item = AutoRef<ImplHolder<RANK>>::make (that) ;
	}
	mHolder = &r1x.self[ix].item.self ;
}

template <class ,class = Operand>
class Expression ;

class LexicalNode :public Object::Virtual {
private:
	template <class ,class>
	friend class Expression ;
	Operand mOperand ;
	Operator mOperator ;
	ARRAY4<StrongRef<LexicalNode>> mChild ;

public:
	inline LexicalNode () :Object (_NULL_<ARGV<LexicalNode>> ()) {}
} ;

template <class TYPE>
class LexicalTree {
private:
	template <class ,class>
	friend class Expression ;
	StrongRef<LexicalNode> mTree ;

public:
	inline LexicalTree () {
		mTree = StrongRef<LexicalNode>::make () ;
	}

	inline const StrongRef<LexicalNode> &to () const {
		return mTree ;
	}

	inline implicit operator const StrongRef<LexicalNode> & () const {
		return to () ;
	}

private:
	inline static const TYPE &from (const StrongRef<LexicalNode> &me) {
		return _CAST_<TYPE> (me) ;
	}
} ;

template <class HINT>
class Expression<RANK0 ,HINT> :private LexicalTree<Expression<RANK0 ,HINT>> {
private:
	template <class ,class>
	friend class Expression ;
	using LexicalTree<Expression<RANK0 ,HINT>>::mTree ;

public:
	inline Expression () = default ;

	inline implicit Expression (const Operand &that) : Expression () {
		_DYNAMIC_ASSERT_ (that.exist ()) ;
		mTree->mOperand = that ;
	}

	inline implicit Expression (const Operator &that) : Expression () {
		_DYNAMIC_ASSERT_ (that.rank () == _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<RANK0>>)) ;
		mTree->mOperator = that ;
	}

	inline implicit operator const Expression<RANK0> & () const {
		return Expression<RANK0>::from ((*this)) ;
	}

	inline HINT operator() () const {
		_DYNAMIC_ASSERT_ (mTree.exist ()) ;
		if (mTree->mOperand.exist ())
			return mTree->mOperand.template as<HINT> () ;
		const auto r1x = mTree->mOperator (mTree.self) ;
		return r1x.template as<HINT> () ;
	}
} ;

namespace U {
template <class _ARG1>
inline constexpr LENGTH constexpr_max_value (const ARGV<ARGVS<_ARG1>> &) {
	return _ARG1::value ;
}

template <class _ARG1 ,class _ARG2 ,class... _ARGS>
inline constexpr LENGTH constexpr_max_value (const ARGV<ARGVS<_ARG1 ,_ARG2 ,_ARGS...>> &) {
	using BIGGER = ARGC<_MAX_<VAR> (_ARG1::value ,_ARG2::value)> ;
	return constexpr_max_value (_NULL_<ARGV<ARGVS<BIGGER ,_ARGS...>>> ()) ;
}
} ;

template <class HINT>
class Expression<RANK1 ,HINT> :private LexicalTree<Expression<RANK1 ,HINT>> {
private:
	using CURRY_TYPE = Expression<RANK1 ,HINT> ;

	template <class... _ARGS>
	struct FLIP_TYPE {
		using FLIP_RANK = U::RANK_FUNC_TYPE<ARGC<U::constexpr_max_value (_NULL_<ARGV<ARGVS<_ARGS...>>> ())>> ;
		using TYPE = Expression<FLIP_RANK> ;
	} ;

private:
	template <class ,class>
	friend class Expression ;
	using LexicalTree<Expression<RANK1 ,HINT>>::mTree ;

public:
	inline Expression () = default ;

	inline implicit Expression (const Operator &that) : Expression () {
		_DYNAMIC_ASSERT_ (that.rank () == _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<RANK1>>)) ;
		mTree->mOperator = that ;
	}

	inline implicit operator const Expression<RANK1> & () const {
		return Expression<RANK1>::from ((*this)) ;
	}

	inline HINT operator() (const Operand &in1) const {
		_DYNAMIC_ASSERT_ (mTree.exist ()) ;
		if (mTree->mOperand.exist ())
			return mTree->mOperand.template as<HINT> () ;
		const auto r1x = mTree->mOperator (mTree.self ,in1) ;
		return r1x.template as<HINT> () ;
	}

	template <class _ARG1>
	inline auto flip (const ARGV<ARGVP<_ARG1>> &) const
		->DEF<typename FLIP_TYPE<_ARG1>::TYPE> {
		using FLIP_RANK = typename FLIP_TYPE<_ARG1>::FLIP_RANK ;
		return template_flip (_NULL_<ARGV<ARGVS<_ARG1>>> () ,_NULL_<ARGV<FLIP_RANK>> () ,_NULL_<ARGV<INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<FLIP_RANK>>>> ()) ;
	}

	inline CURRY_TYPE curry () const {
		return (*this) ;
	}

	inline Expression<RANK0> operator+ (const Expression<RANK0> &that) const ;

	inline Expression<RANK1> operator+ (const Expression<RANK1> &that) const ;

	inline Expression<RANK2> operator+ (const Expression<RANK2> &that) const ;

	inline Expression<RANK3> operator+ (const Expression<RANK3> &that) const ;

	inline Expression<RANK4> operator+ (const Expression<RANK4> &that) const ;

	inline Expression<RANK5> operator+ (const Expression<RANK5> &that) const ;

	inline Expression<RANK6> operator+ (const Expression<RANK6> &that) const ;

	inline Expression<RANK7> operator+ (const Expression<RANK7> &that) const ;

	inline Expression<RANK8> operator+ (const Expression<RANK8> &that) const ;

	inline Expression<RANK9> operator+ (const Expression<RANK9> &that) const ;

private:
	template <class _ARG1 ,class _ARG2 ,class... _ARGS>
	inline Expression<_ARG2> template_flip (const ARGV<ARGVS<_ARG1>> & ,const ARGV<_ARG2> & ,const ARGV<ARGVS<_ARGS...>> &) const {
		Expression<_ARG2> ret ;
		ret.mTree->mOperator = _XVALUE_<U::CONTEXT_RANK_FUNC_TYPE<_ARG2>> ([] (const LexicalNode &node ,const _ARGS &...ins) {
			auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
			auto &r2x = Tuple<const _ARGS &...> (ins...).pick (_NULL_<ARGV<ARGVP<_ARG1>>> ()) ;
			return r1x (r2x) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		return std::move (ret) ;
	}
} ;

template <class HINT>
class Expression<RANK2 ,HINT> :private LexicalTree<Expression<RANK2 ,HINT>> {
private:
	using CURRY_TYPE = Expression<RANK1 ,typename Expression<RANK1>::CURRY_TYPE> ;

	template <class... _ARGS>
	struct FLIP_TYPE {
		using FLIP_RANK = U::RANK_FUNC_TYPE<ARGC<U::constexpr_max_value (_NULL_<ARGV<ARGVS<_ARGS...>>> ())>> ;
		using TYPE = Expression<FLIP_RANK> ;
	} ;

private:
	template <class ,class>
	friend class Expression ;
	using LexicalTree<Expression<RANK2 ,HINT>>::mTree ;

public:
	inline Expression () = default ;

	inline implicit Expression (const Operator &that) : Expression () {
		_DYNAMIC_ASSERT_ (that.rank () == _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<RANK2>>)) ;
		mTree->mOperator = that ;
	}

	inline implicit operator const Expression<RANK2> & () const {
		return Expression<RANK2>::from ((*this)) ;
	}

	inline HINT operator() (const Operand &in1 ,const Operand &in2) const {
		_DYNAMIC_ASSERT_ (mTree.exist ()) ;
		if (mTree->mOperand.exist ())
			return mTree->mOperand.template as<HINT> () ;
		const auto r1x = mTree->mOperator (mTree.self ,in1 ,in2) ;
		return r1x.template as<HINT> () ;
	}

	template <class _ARG1 ,class _ARG2>
	inline auto flip (const ARGV<ARGVP<_ARG1>> & ,const ARGV<ARGVP<_ARG2>> &) const
		->DEF<typename FLIP_TYPE<_ARG1 ,_ARG2>::TYPE> {
		using FLIP_RANK = typename FLIP_TYPE<_ARG1 ,_ARG2>::FLIP_RANK ;
		return template_flip (_NULL_<ARGV<ARGVS<_ARG1 ,_ARG2>>> () ,_NULL_<ARGV<FLIP_RANK>> () ,_NULL_<ARGV<INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<FLIP_RANK>>>> ()) ;
	}

	inline CURRY_TYPE curry () const {
		CURRY_TYPE ret ;
		ret.mTree->mOperator = _XVALUE_<U::CONTEXT_RANK_FUNC_TYPE<RANK1>> ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
			auto tmp = (r1x + in1).curry () ;
			return Operand (std::move (tmp)) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		return std::move (ret) ;
	}

	inline Expression<RANK1> operator+ (const Expression<RANK0> &that) const ;

	inline Expression<RANK2> operator+ (const Expression<RANK1> &that) const ;

	inline Expression<RANK3> operator+ (const Expression<RANK2> &that) const ;

private:
	template <class _ARG1 ,class _ARG2 ,class _ARG3 ,class... _ARGS>
	inline Expression<_ARG3> template_flip (const ARGV<ARGVS<_ARG1 ,_ARG2>> & ,const ARGV<_ARG3> & ,const ARGV<ARGVS<_ARGS...>> &) const {
		Expression<_ARG3> ret ;
		ret.mTree->mOperator = _XVALUE_<U::CONTEXT_RANK_FUNC_TYPE<_ARG3>> ([] (const LexicalNode &node ,const _ARGS &...ins) {
			auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
			auto &r2x = Tuple<const _ARGS &...> (ins...).pick (_NULL_<ARGV<ARGVP<_ARG1>>> ()) ;
			auto &r3x = Tuple<const _ARGS &...> (ins...).pick (_NULL_<ARGV<ARGVP<_ARG2>>> ()) ;
			return r1x (r2x ,r3x) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		return std::move (ret) ;
	}
} ;

template <class HINT>
class Expression<RANK3 ,HINT> :private LexicalTree<Expression<RANK3 ,HINT>> {
private:
	using CURRY_TYPE = Expression<RANK1 ,typename Expression<RANK2>::CURRY_TYPE> ;

	template <class... _ARGS>
	struct FLIP_TYPE {
		using FLIP_RANK = U::RANK_FUNC_TYPE<ARGC<U::constexpr_max_value (_NULL_<ARGV<ARGVS<_ARGS...>>> ())>> ;
		using TYPE = Expression<FLIP_RANK> ;
	} ;

private:
	template <class ,class>
	friend class Expression ;
	using LexicalTree<Expression<RANK3 ,HINT>>::mTree ;

public:
	inline Expression () = default ;

	inline implicit Expression (const Operator &that) : Expression () {
		_DYNAMIC_ASSERT_ (that.rank () == _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<RANK3>>)) ;
		mTree->mOperator = that ;
	}

	inline implicit operator const Expression<RANK3> & () const {
		return Expression<RANK3>::from ((*this)) ;
	}

	inline HINT operator() (const Operand &in1 ,const Operand &in2 ,const Operand &in3) const {
		_DYNAMIC_ASSERT_ (mTree.exist ()) ;
		if (mTree->mOperand.exist ())
			return mTree->mOperand.template as<HINT> () ;
		const auto r1x = mTree->mOperator (mTree.self ,in1 ,in2 ,in3) ;
		return r1x.template as<HINT> () ;
	}

	template <class _ARG1 ,class _ARG2 ,class _ARG3>
	inline auto flip (const ARGV<ARGVP<_ARG1>> & ,const ARGV<ARGVP<_ARG2>> & ,const ARGV<ARGVP<_ARG3>> &) const
		->DEF<typename FLIP_TYPE<_ARG1 ,_ARG2 ,_ARG3>::TYPE> {
		using FLIP_RANK = typename FLIP_TYPE<_ARG1 ,_ARG2 ,_ARG3>::FLIP_RANK ;
		return template_flip (_NULL_<ARGV<ARGVS<_ARG1 ,_ARG2 ,_ARG3>>> () ,_NULL_<ARGV<FLIP_RANK>> () ,_NULL_<ARGV<INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<FLIP_RANK>>>> ()) ;
	}

	inline CURRY_TYPE curry () const {
		CURRY_TYPE ret ;
		ret.mTree->mOperator = _XVALUE_<U::CONTEXT_RANK_FUNC_TYPE<RANK1>> ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK3>::from (node.mChild[0]) ;
			auto tmp = (r1x + in1).curry () ;
			return Operand (std::move (tmp)) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		return std::move (ret) ;
	}

	inline Expression<RANK2> operator+ (const Expression<RANK0> &that) const ;

	inline Expression<RANK3> operator+ (const Expression<RANK1> &that) const ;

private:
	template <class _ARG1 ,class _ARG2 ,class _ARG3 ,class _ARG4 ,class... _ARGS>
	inline Expression<_ARG4> template_flip (const ARGV<ARGVS<_ARG1 ,_ARG2 ,_ARG3>> & ,const ARGV<_ARG4> & ,const ARGV<ARGVS<_ARGS...>> &) const {
		Expression<_ARG4> ret ;
		ret.mTree->mOperator = _XVALUE_<U::CONTEXT_RANK_FUNC_TYPE<_ARG4>> ([] (const LexicalNode &node ,const _ARGS &...ins) {
			auto &r1x = Expression<RANK3>::from (node.mChild[0]) ;
			auto &r2x = Tuple<const _ARGS &...> (ins...).pick (_NULL_<ARGV<ARGVP<_ARG1>>> ()) ;
			auto &r3x = Tuple<const _ARGS &...> (ins...).pick (_NULL_<ARGV<ARGVP<_ARG2>>> ()) ;
			auto &r4x = Tuple<const _ARGS &...> (ins...).pick (_NULL_<ARGV<ARGVP<_ARG3>>> ()) ;
			return r1x (r2x ,r3x ,r4x) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		return std::move (ret) ;
	}
} ;

template <class HINT>
inline Expression<RANK0> Expression<RANK1 ,HINT>::operator+ (const Expression<RANK0> &that) const {
	Expression<RANK0> ret ;
	ret.mTree->mOperator = _XVALUE_<U::CONTEXT_RANK_FUNC_TYPE<RANK0>> ([] (const LexicalNode &node) {
		auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK0>::from (node.mChild[1]) ;
		return r1x (r2x ()) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	return std::move (ret) ;
}

template <class HINT>
inline Expression<RANK1> Expression<RANK1 ,HINT>::operator+ (const Expression<RANK1> &that) const {
	Expression<RANK1> ret ;
	ret.mTree->mOperator = _XVALUE_<U::CONTEXT_RANK_FUNC_TYPE<RANK1>> ([] (const LexicalNode &node ,const Operand &in1) {
		auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK1>::from (node.mChild[1]) ;
		return r1x (r2x (in1)) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	return std::move (ret) ;
}

template <class HINT>
inline Expression<RANK2> Expression<RANK1 ,HINT>::operator+ (const Expression<RANK2> &that) const {
	Expression<RANK2> ret ;
	ret.mTree->mOperator = _XVALUE_<U::CONTEXT_RANK_FUNC_TYPE<RANK2>> ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) {
		auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK2>::from (node.mChild[1]) ;
		return r1x (r2x (in1 ,in2)) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	return std::move (ret) ;
}

template <class HINT>
inline Expression<RANK3> Expression<RANK1 ,HINT>::operator+ (const Expression<RANK3> &that) const {
	Expression<RANK3> ret ;
	ret.mTree->mOperator = _XVALUE_<U::CONTEXT_RANK_FUNC_TYPE<RANK3>> ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) {
		auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK3>::from (node.mChild[1]) ;
		return r1x (r2x (in1 ,in2 ,in3)) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	return std::move (ret) ;
}

template <class HINT>
inline Expression<RANK1> Expression<RANK2 ,HINT>::operator+ (const Expression<RANK0> &that) const {
	Expression<RANK1> ret ;
	ret.mTree->mOperator = _XVALUE_<U::CONTEXT_RANK_FUNC_TYPE<RANK1>> ([] (const LexicalNode &node ,const Operand &in1) {
		auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK0>::from (node.mChild[1]) ;
		return r1x (r2x () ,in1) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	return std::move (ret) ;
}

template <class HINT>
inline Expression<RANK2> Expression<RANK2 ,HINT>::operator+ (const Expression<RANK1> &that) const {
	Expression<RANK2> ret ;
	ret.mTree->mOperator = _XVALUE_<U::CONTEXT_RANK_FUNC_TYPE<RANK2>> ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) {
		auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK1>::from (node.mChild[1]) ;
		return r1x (r2x (in1) ,in2) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	return std::move (ret) ;
}

template <class HINT>
inline Expression<RANK3> Expression<RANK2 ,HINT>::operator+ (const Expression<RANK2> &that) const {
	Expression<RANK3> ret ;
	ret.mTree->mOperator = _XVALUE_<U::CONTEXT_RANK_FUNC_TYPE<RANK3>> ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) {
		auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK2>::from (node.mChild[1]) ;
		return r1x (r2x (in1 ,in2) ,in3) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	return std::move (ret) ;
}

template <class HINT>
inline Expression<RANK2> Expression<RANK3 ,HINT>::operator+ (const Expression<RANK0> &that) const {
	Expression<RANK2> ret ;
	ret.mTree->mOperator = _XVALUE_<U::CONTEXT_RANK_FUNC_TYPE<RANK2>> ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) {
		auto &r1x = Expression<RANK3>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK0>::from (node.mChild[1]) ;
		return r1x (r2x () ,in1 ,in2) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	return std::move (ret) ;
}

template <class HINT>
inline Expression<RANK3> Expression<RANK3 ,HINT>::operator+ (const Expression<RANK1> &that) const {
	Expression<RANK3> ret ;
	ret.mTree->mOperator = _XVALUE_<U::CONTEXT_RANK_FUNC_TYPE<RANK3>> ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) {
		auto &r1x = Expression<RANK3>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK1>::from (node.mChild[1]) ;
		return r1x (r2x (in1) ,in2 ,in3) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	return std::move (ret) ;
}
} ;