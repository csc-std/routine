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
} ;

class Operator {
private:
	exports struct Holder :public Interface {
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
	class ImplHolder ;

	class Pack {
	private:
		friend Operator ;
		AnyRef<void> mHolder ;
	} ;

private:
	SharedRef<Pack> mThis ;
	PTR<Holder> mPointer ;

public:
	Operator () {
		mPointer = NULL ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<!std::is_same<REMOVE_CVR_TYPE<_ARG1> ,Operator>::value>>
	explicit Operator (const _ARG1 &that) ;

	LENGTH rank () const {
		if (mPointer == NULL)
			return VAR_NONE ;
		return mPointer->rank () ;
	}

	template <class... _ARGS>
	Operand invoke (const LexicalNode &node ,const _ARGS &...args) const {
		_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<_ARGS...>) <= 9) ;
		_DYNAMIC_ASSERT_ (mPointer != NULL) ;
		return mPointer->invoke (node ,args...) ;
	}

	template <class... _ARGS>
	inline Operand operator() (const LexicalNode &node ,const _ARGS &...args) const {
		return invoke (node ,args...) ;
	}
} ;

template <>
class Operator::ImplHolder<void ,void> :public Holder {
public:
	ImplHolder () = default ;

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
class Operator::ImplHolder<PTR<UNIT1 (UNITS1...)> ,ARGVS<UNITS2...>> :public ImplHolder<void ,void> {
	_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS1...>) == _CAPACITYOF_ (ARGVS<UNITS2...>)) ;

private:
	Function<UNIT1 (UNITS1...)> mFunction ;

public:
	ImplHolder () = delete ;

	explicit ImplHolder (const PTR<UNIT1 (UNITS1...)> &function_)
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

	//@error: vs2015 is too useless to compile without hint
	template <class _ARG1 ,class _ARG2 ,class... _ARGS>
	static UNIT1 template_invoke (const Function<UNIT1 (UNITS1...)> &func ,const _ARG1 &parameter ,const ARGV<_ARG2> & ,_ARGS &&...funcval) popping {
		using ARGVS_ONE = ARGVS_ONE_TYPE<_ARG2> ;
		using ARGVS_REST = ARGVS_REST_TYPE<_ARG2> ;
		auto &r1x = parameter.one ().template as<ARGVS_ONE> () ;
		return template_invoke (func ,parameter.rest () ,_NULL_<ARGV<ARGVS_REST>> () ,std::forward<_ARGS> (funcval)... ,r1x) ;
	}
} ;

template <class UNIT1 ,class... UNITS1 ,class... UNITS2>
class Operator::ImplHolder<PTR<UNIT1 (const LexicalNode & ,UNITS1...)> ,ARGVS<Operand ,UNITS2...>> :public ImplHolder<void ,void> {
	_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS1...>) == _CAPACITYOF_ (ARGVS<UNITS2...>)) ;

private:
	Function<UNIT1 (const LexicalNode & ,UNITS1...)> mFunction ;

public:
	ImplHolder () = delete ;

	explicit ImplHolder (const PTR<UNIT1 (const LexicalNode & ,UNITS1...)> &function_)
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

	//@error: vs2015 is too useless to compile without hint
	template <class _ARG1 ,class _ARG2 ,class... _ARGS>
	static UNIT1 template_invoke (const Function<UNIT1 (const LexicalNode & ,UNITS1...)> &func ,const _ARG1 &parameter ,const ARGV<_ARG2> & ,_ARGS &&...funcval) popping {
		using ARGVS_ONE = ARGVS_ONE_TYPE<_ARG2> ;
		using ARGVS_REST = ARGVS_REST_TYPE<_ARG2> ;
		auto &r1x = parameter.one ().template as<ARGVS_ONE> () ;
		return template_invoke (func ,parameter.rest () ,_NULL_<ARGV<ARGVS_REST>> () ,std::forward<_ARGS> (funcval)... ,r1x) ;
	}
} ;

template <class _ARG1 ,class>
Operator::Operator (const _ARG1 &that) {
	using FUNC = REMOVE_FUNCATTR_TYPE<REMOVE_MEMPTR_TYPE<DEF<decltype (&_ARG1::operator())>>> ;
	using HOLDER = ImplHolder<PTR<FUNC> ,REPEAT_OF_TYPE<ARGC<_CAPACITYOF_ (INVOKE_PARAMS_TYPE<FUNC>)> ,Operand>> ;
	_STATIC_ASSERT_ (std::is_convertible<_ARG1 ,PTR<FUNC>>::value) ;
	_STATIC_ASSERT_ (stl::is_complete<HOLDER>::value) ;
	const auto r2x = _XVALUE_<PTR<FUNC>> (that) ;
	auto tmp = AutoRef<HOLDER>::make (r2x) ;
	mThis->mHolder = AnyRef<AutoRef<HOLDER>>::make (std::move (tmp)) ;
	mPointer = &mThis->mHolder.rebind<AutoRef<HOLDER>> ()->self ;
}

template <class ,class = Operand>
class Expression ;

class LexicalNode :public Object::Virtual {
private:
	template <class ,class>
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
	template <class ,class>
	friend class Expression ;
	StrongRef<LexicalNode> mTree ;

public:
	LexicalTree () {
		mTree = StrongRef<LexicalNode>::make () ;
	}

	const StrongRef<LexicalNode> &to () const {
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

template <>
class Expression<RANK0> :private LexicalTree<Expression<RANK0>> {
private:
	template <class ,class>
	friend class Expression ;
	using LexicalTree<Expression<RANK0>>::mTree ;

public:
	Expression () = default ;

	implicit Expression (const Operand &that) {
		_DYNAMIC_ASSERT_ (that.exist ()) ;
		mTree->mOperand = that ;
		mTree->mDepth = 1 ;
	}

	implicit Expression (const Operator &that) {
		_DYNAMIC_ASSERT_ (that.rank () == _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<RANK0>>)) ;
		mTree->mOperator = that ;
		mTree->mDepth = 1 ;
	}

	const Operand &invoke () const {
		_DYNAMIC_ASSERT_ (mTree.exist ()) ;
		if switch_case (TRUE) {
			if (mTree->mOperand.exist ())
				discard ;
			mTree->mOperand = mTree->mOperator (mTree.self) ;
			mTree->mOperator = Operator () ;
			mTree->mChild[0] = StrongRef<LexicalNode> () ;
			mTree->mChild[1] = StrongRef<LexicalNode> () ;
			mTree->mChild[2] = StrongRef<LexicalNode> () ;

		}
		return mTree->mOperand ;
	}

	inline const Operand &operator() () const {
		return invoke () ;
	}
} ;

namespace U {
template <class _ARG1>
constexpr LENGTH constexpr_max_value (const ARGV<ARGVS<_ARG1>> &) {
	return _ARG1::value ;
}

template <class _ARG1 ,class _ARG2 ,class... _ARGS>
constexpr LENGTH constexpr_max_value (const ARGV<ARGVS<_ARG1 ,_ARG2 ,_ARGS...>> &) {
	using BIGGER = ARGC<_MAX_<VAR> (_ARG1::value ,_ARG2::value)> ;
	return constexpr_max_value (_NULL_<ARGV<ARGVS<BIGGER ,_ARGS...>>> ()) ;
}
} ;

template <>
class Expression<RANK1> :private LexicalTree<Expression<RANK1>> {
private:
	using RANK = RANK1 ;

	template <class... _ARGS>
	using FLIP_RANK_HINT = U::RANK_FUNC_TYPE<ARGC<U::constexpr_max_value (_NULL_<ARGV<ARGVS<_ARGS...>>> ())>> ;

	template <class _ARG1>
	using CONCAT_RANK_HINT = U::RANK_FUNC_TYPE<ARGC<0 + _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<_ARG1>>)>> ;

private:
	template <class ,class>
	friend class Expression ;
	using LexicalTree<Expression<RANK>>::mTree ;

public:
	Expression () = default ;

	implicit Expression (const Operator &that) {
		_DYNAMIC_ASSERT_ (that.rank () == _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<RANK>>)) ;
		mTree->mOperator = that ;
		mTree->mDepth = 1 ;
	}

	const Operand &invoke (const Operand &in1) const {
		_DYNAMIC_ASSERT_ (mTree.exist ()) ;
		if switch_case (TRUE) {
			if (mTree->mOperand.exist ())
				discard ;
			mTree->mOperand = mTree->mOperator (mTree.self ,in1) ;
			mTree->mOperator = Operator () ;
			mTree->mChild[0] = StrongRef<LexicalNode> () ;
			mTree->mChild[1] = StrongRef<LexicalNode> () ;
			mTree->mChild[2] = StrongRef<LexicalNode> () ;
		}
		return mTree->mOperand ;
	}

	inline const Operand &operator() (const Operand &in1) const {
		return invoke (in1) ;
	}

	Expression<RANK> flip () const {
		return (*this) ;
	}

	template <class _ARG1>
	Expression<FLIP_RANK_HINT<_ARG1>> flip (const ARGV<ARGVP<_ARG1>> &) const {
		using FLIP_RANK_T = FLIP_RANK_HINT<_ARG1> ;
		auto &r1x = _NULL_<ARGV<ARGVS<_ARG1>>> () ;
		auto &r2x = _NULL_<ARGV<FLIP_RANK_T>> () ;
		auto &r3x = _NULL_<ARGV<INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<FLIP_RANK_T>>>> () ;
		return template_flip (r1x ,r2x ,r3x) ;
	}

	Expression<RANK1> curry () const {
		return (*this) ;
	}

	Expression<RANK1> fold () const {
		Expression<RANK1> ret ;
		ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK>::from (node.mChild[0]) ;
			auto &r2x = in1.template as<Expression<RANK1>> () ;
			return r1x (r2x (Operand (1))) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		ret.mTree->mDepth = _MAXOF_ (mTree->mDepth) + 1 ;
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
	inline Expression<CONCAT_RANK_HINT<_ARG1>> operator+ (const Expression<_ARG1> &that) const {
		return concat (that) ;
	}

private:
	template <class _ARG1 ,class _ARG2 ,class... _ARGS>
	Expression<_ARG2> template_flip (const ARGV<ARGVS<_ARG1>> & ,const ARGV<_ARG2> & ,const ARGV<ARGVS<_ARGS...>> &) const {
		Expression<_ARG2> ret ;
		ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const _ARGS &...ins) {
			auto &r1x = Expression<RANK>::from (node.mChild[0]) ;
			const auto r10x = Tuple<const _ARGS &...> (ins...) ;
			auto &r2x = r10x.pick (_NULL_<ARGV<ARGVP<_ARG1>>> ()) ;
			return r1x (r2x) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		ret.mTree->mDepth = _MAXOF_ (mTree->mDepth) + 1 ;
		return std::move (ret) ;
	}
} ;

template <>
class Expression<RANK2> :private LexicalTree<Expression<RANK2>> {
private:
	using RANK = RANK2 ;

	template <class... _ARGS>
	using FLIP_RANK_HINT = U::RANK_FUNC_TYPE<ARGC<U::constexpr_max_value (_NULL_<ARGV<ARGVS<_ARGS...>>> ())>> ;

	template <class _ARG1>
	using CONCAT_RANK_HINT = U::RANK_FUNC_TYPE<ARGC<1 + _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<_ARG1>>)>> ;

private:
	template <class ,class>
	friend class Expression ;
	using LexicalTree<Expression<RANK>>::mTree ;

public:
	Expression () = default ;

	implicit Expression (const Operator &that) {
		_DYNAMIC_ASSERT_ (that.rank () == _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<RANK>>)) ;
		mTree->mOperator = that ;
		mTree->mDepth = 1 ;
	}

	const Operand &invoke (const Operand &in1 ,const Operand &in2) const {
		_DYNAMIC_ASSERT_ (mTree.exist ()) ;
		if switch_case (TRUE) {
			if (mTree->mOperand.exist ())
				discard ;
			mTree->mOperand = mTree->mOperator (mTree.self ,in1 ,in2) ;
			mTree->mOperator = Operator () ;
			mTree->mChild[0] = StrongRef<LexicalNode> () ;
			mTree->mChild[1] = StrongRef<LexicalNode> () ;
			mTree->mChild[2] = StrongRef<LexicalNode> () ;
		}
		return mTree->mOperand ;
	}

	inline const Operand &operator() (const Operand &in1 ,const Operand &in2) const {
		return invoke (in1 ,in2) ;
	}

	Expression<RANK> flip () const {
		Expression<RANK> ret ;
		ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) {
			auto &r1x = Expression<RANK>::from (node.mChild[0]) ;
			return r1x (in2 ,in1) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		ret.mTree->mDepth = _MAXOF_ (mTree->mDepth) + 1 ;
		return std::move (ret) ;
	}

	template <class _ARG1 ,class _ARG2>
	Expression<FLIP_RANK_HINT<_ARG1 ,_ARG2>> flip (const ARGV<ARGVP<_ARG1>> & ,const ARGV<ARGVP<_ARG2>> &) const {
		using FLIP_RANK_T = FLIP_RANK_HINT<_ARG1 ,_ARG2> ;
		auto &r1x = _NULL_<ARGV<ARGVS<_ARG1 ,_ARG2>>> () ;
		auto &r2x = _NULL_<ARGV<FLIP_RANK_T>> () ;
		auto &r3x = _NULL_<ARGV<INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<FLIP_RANK_T>>>> () ;
		return template_flip (r1x ,r2x ,r3x) ;
	}

	Expression<RANK1> curry () const {
		Expression<RANK1> ret ;
		ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK>::from (node.mChild[0]) ;
			auto tmp = r1x.concat (in1).curry () ;
			return Operand (std::move (tmp)) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		ret.mTree->mDepth = _MAXOF_ (mTree->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK1> fold () const {
		Expression<RANK1> ret ;
		ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK>::from (node.mChild[0]) ;
			auto &r2x = in1.template as<Expression<RANK1>> () ;
			return r1x (r2x (Operand (1)) ,r2x (Operand (2))) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		ret.mTree->mDepth = _MAXOF_ (mTree->mDepth) + 1 ;
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
	inline Expression<CONCAT_RANK_HINT<_ARG1>> operator+ (const Expression<_ARG1> &that) const {
		return concat (that) ;
	}

private:
	template <class _ARG1 ,class _ARG2 ,class _ARG3 ,class... _ARGS>
	Expression<_ARG3> template_flip (const ARGV<ARGVS<_ARG1 ,_ARG2>> & ,const ARGV<_ARG3> & ,const ARGV<ARGVS<_ARGS...>> &) const {
		Expression<_ARG3> ret ;
		ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const _ARGS &...ins) {
			auto &r1x = Expression<RANK>::from (node.mChild[0]) ;
			const auto r10x = Tuple<const _ARGS &...> (ins...) ;
			auto &r2x = r10x.pick (_NULL_<ARGV<ARGVP<_ARG1>>> ()) ;
			auto &r3x = r10x.pick (_NULL_<ARGV<ARGVP<_ARG2>>> ()) ;
			return r1x (r2x ,r3x) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		ret.mTree->mDepth = _MAXOF_ (mTree->mDepth) + 1 ;
		return std::move (ret) ;
	}
} ;

template <>
class Expression<RANK3> :private LexicalTree<Expression<RANK3>> {
private:
	using RANK = RANK3 ;

	template <class... _ARGS>
	using FLIP_RANK_HINT = U::RANK_FUNC_TYPE<ARGC<U::constexpr_max_value (_NULL_<ARGV<ARGVS<_ARGS...>>> ())>> ;

	template <class _ARG1>
	using CONCAT_RANK_HINT = U::RANK_FUNC_TYPE<ARGC<2 + _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<_ARG1>>)>> ;

private:
	template <class ,class>
	friend class Expression ;
	using LexicalTree<Expression<RANK>>::mTree ;

public:
	Expression () = default ;

	implicit Expression (const Operator &that) {
		_DYNAMIC_ASSERT_ (that.rank () == _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<RANK>>)) ;
		mTree->mOperator = that ;
		mTree->mDepth = 1 ;
	}

	const Operand &invoke (const Operand &in1 ,const Operand &in2 ,const Operand &in3) const {
		_DYNAMIC_ASSERT_ (mTree.exist ()) ;
		if switch_case (TRUE) {
			if (mTree->mOperand.exist ())
				discard ;
			mTree->mOperand = mTree->mOperator (mTree.self ,in1 ,in2 ,in3) ;
			mTree->mOperator = Operator () ;
			mTree->mChild[0] = StrongRef<LexicalNode> () ;
			mTree->mChild[1] = StrongRef<LexicalNode> () ;
			mTree->mChild[2] = StrongRef<LexicalNode> () ;
		}
		return mTree->mOperand ;
	}

	inline const Operand &operator() (const Operand &in1 ,const Operand &in2 ,const Operand &in3) const {
		return invoke (in1 ,in2 ,in3) ;
	}

	Expression<RANK> flip () const {
		Expression<RANK> ret ;
		ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) {
			auto &r1x = Expression<RANK>::from (node.mChild[0]) ;
			return r1x (in3 ,in2 ,in1) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		ret.mTree->mDepth = _MAXOF_ (mTree->mDepth) + 1 ;
		return std::move (ret) ;
	}

	template <class _ARG1 ,class _ARG2 ,class _ARG3>
	Expression<FLIP_RANK_HINT<_ARG1 ,_ARG2 ,_ARG3>> flip (const ARGV<ARGVP<_ARG1>> & ,const ARGV<ARGVP<_ARG2>> & ,const ARGV<ARGVP<_ARG3>> &) const {
		using FLIP_RANK_T = FLIP_RANK_HINT<_ARG1 ,_ARG2 ,_ARG3> ;
		auto &r1x = _NULL_<ARGV<ARGVS<_ARG1 ,_ARG2 ,_ARG3>>> () ;
		auto &r2x = _NULL_<ARGV<FLIP_RANK_T>> () ;
		auto &r3x = _NULL_<ARGV<INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<FLIP_RANK_T>>>> () ;
		return template_flip (r1x ,r2x ,r3x) ;
	}

	Expression<RANK1> curry () const {
		Expression<RANK1> ret ;
		ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK>::from (node.mChild[0]) ;
			auto tmp = r1x.concat (in1).curry () ;
			return Operand (std::move (tmp)) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		ret.mTree->mDepth = _MAXOF_ (mTree->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK1> fold () const {
		Expression<RANK1> ret ;
		ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK>::from (node.mChild[0]) ;
			auto &r2x = in1.template as<Expression<RANK1>> () ;
			return r1x (r2x (Operand (1)) ,r2x (Operand (2)) ,r2x (Operand (3))) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		ret.mTree->mDepth = _MAXOF_ (mTree->mDepth) + 1 ;
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
	inline Expression<CONCAT_RANK_HINT<_ARG1>> operator+ (const Expression<_ARG1> &that) const {
		return concat (that) ;
	}

private:
	template <class _ARG1 ,class _ARG2 ,class _ARG3 ,class _ARG4 ,class... _ARGS>
	Expression<_ARG4> template_flip (const ARGV<ARGVS<_ARG1 ,_ARG2 ,_ARG3>> & ,const ARGV<_ARG4> & ,const ARGV<ARGVS<_ARGS...>> &) const {
		Expression<_ARG4> ret ;
		ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const _ARGS &...ins) {
			auto &r1x = Expression<RANK>::from (node.mChild[0]) ;
			const auto r10x = Tuple<const _ARGS &...> (ins...) ;
			auto &r2x = r10x.pick (_NULL_<ARGV<ARGVP<_ARG1>>> ()) ;
			auto &r3x = r10x.pick (_NULL_<ARGV<ARGVP<_ARG2>>> ()) ;
			auto &r4x = r10x.pick (_NULL_<ARGV<ARGVP<_ARG3>>> ()) ;
			return r1x (r2x ,r3x ,r4x) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		ret.mTree->mDepth = _MAXOF_ (mTree->mDepth) + 1 ;
		return std::move (ret) ;
	}
} ;

template <>
class Expression<RANK4> :private LexicalTree<Expression<RANK4>> {
private:
	using RANK = RANK4 ;

	template <class... _ARGS>
	using FLIP_RANK_HINT = U::RANK_FUNC_TYPE<ARGC<U::constexpr_max_value (_NULL_<ARGV<ARGVS<_ARGS...>>> ())>> ;

	template <class _ARG1>
	using CONCAT_RANK_HINT = U::RANK_FUNC_TYPE<ARGC<3 + _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<_ARG1>>)>> ;

private:
	template <class ,class>
	friend class Expression ;
	using LexicalTree<Expression<RANK>>::mTree ;

public:
	Expression () = default ;

	implicit Expression (const Operator &that) {
		_DYNAMIC_ASSERT_ (that.rank () == _CAPACITYOF_ (INVOKE_PARAMS_TYPE<REMOVE_POINTER_TYPE<RANK>>)) ;
		mTree->mOperator = that ;
		mTree->mDepth = 1 ;
	}

	const Operand &invoke (const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4) const {
		_DYNAMIC_ASSERT_ (mTree.exist ()) ;
		if switch_case (TRUE) {
			if (mTree->mOperand.exist ())
				discard ;
			mTree->mOperand = mTree->mOperator (mTree.self ,in1 ,in2 ,in3 ,in4) ;
			mTree->mOperator = Operator () ;
			mTree->mChild[0] = StrongRef<LexicalNode> () ;
			mTree->mChild[1] = StrongRef<LexicalNode> () ;
			mTree->mChild[2] = StrongRef<LexicalNode> () ;
		}
		return mTree->mOperand ;
	}

	inline const Operand &operator() (const Operand &in1 ,const Operand &in2 ,const Operand &in3 ,const Operand &in4) const {
		return invoke (in1 ,in2 ,in3 ,in4) ;
	}

	Expression<RANK1> curry () const {
		Expression<RANK1> ret ;
		ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK>::from (node.mChild[0]) ;
			auto tmp = r1x.concat (in1).curry () ;
			return Operand (std::move (tmp)) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		ret.mTree->mDepth = _MAXOF_ (mTree->mDepth) + 1 ;
		return std::move (ret) ;
	}

	Expression<RANK1> fold () const {
		Expression<RANK1> ret ;
		ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = Expression<RANK>::from (node.mChild[0]) ;
			auto &r2x = in1.template as<Expression<RANK1>> () ;
			return r1x (r2x (Operand (1)) ,r2x (Operand (2)) ,r2x (Operand (3)) ,r2x (Operand (4))) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		ret.mTree->mDepth = _MAXOF_ (mTree->mDepth) + 1 ;
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
	inline Expression<CONCAT_RANK_HINT<_ARG1>> operator+ (const Expression<_ARG1> &that) const {
		return concat (that) ;
	}
} ;

inline Expression<RANK0> Expression<RANK1>::concat (const Expression<RANK0> &that) const {
	Expression<RANK0> ret ;
	ret.mTree->mOperator = Operator ([] (const LexicalNode &node) {
		auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK0>::from (node.mChild[1]) ;
		return r1x (r2x ()) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	ret.mTree->mDepth = _MAXOF_ (mTree->mDepth ,that.mTree->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK1> Expression<RANK1>::concat (const Expression<RANK1> &that) const {
	Expression<RANK1> ret ;
	ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
		auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK1>::from (node.mChild[1]) ;
		return r1x (r2x (in1)) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	ret.mTree->mDepth = _MAXOF_ (mTree->mDepth ,that.mTree->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK2> Expression<RANK1>::concat (const Expression<RANK2> &that) const {
	Expression<RANK2> ret ;
	ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) {
		auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK2>::from (node.mChild[1]) ;
		return r1x (r2x (in1 ,in2)) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	ret.mTree->mDepth = _MAXOF_ (mTree->mDepth ,that.mTree->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK3> Expression<RANK1>::concat (const Expression<RANK3> &that) const {
	Expression<RANK3> ret ;
	ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) {
		auto &r1x = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK3>::from (node.mChild[1]) ;
		return r1x (r2x (in1 ,in2 ,in3)) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	ret.mTree->mDepth = _MAXOF_ (mTree->mDepth ,that.mTree->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK1> Expression<RANK2>::concat (const Expression<RANK0> &that) const {
	Expression<RANK1> ret ;
	ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
		auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK0>::from (node.mChild[1]) ;
		return r1x (r2x () ,in1) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	ret.mTree->mDepth = _MAXOF_ (mTree->mDepth ,that.mTree->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK2> Expression<RANK2>::concat (const Expression<RANK1> &that) const {
	Expression<RANK2> ret ;
	ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) {
		auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK1>::from (node.mChild[1]) ;
		return r1x (r2x (in1) ,in2) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	ret.mTree->mDepth = _MAXOF_ (mTree->mDepth ,that.mTree->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK3> Expression<RANK2>::concat (const Expression<RANK2> &that) const {
	Expression<RANK3> ret ;
	ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) {
		auto &r1x = Expression<RANK2>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK2>::from (node.mChild[1]) ;
		return r1x (r2x (in1 ,in2) ,in3) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	ret.mTree->mDepth = _MAXOF_ (mTree->mDepth ,that.mTree->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK2> Expression<RANK3>::concat (const Expression<RANK0> &that) const {
	Expression<RANK2> ret ;
	ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) {
		auto &r1x = Expression<RANK3>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK0>::from (node.mChild[1]) ;
		return r1x (r2x () ,in1 ,in2) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	ret.mTree->mDepth = _MAXOF_ (mTree->mDepth ,that.mTree->mDepth) + 1 ;
	return std::move (ret) ;
}

inline Expression<RANK3> Expression<RANK3>::concat (const Expression<RANK1> &that) const {
	Expression<RANK3> ret ;
	ret.mTree->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) {
		auto &r1x = Expression<RANK3>::from (node.mChild[0]) ;
		auto &r2x = Expression<RANK1>::from (node.mChild[1]) ;
		return r1x (r2x (in1) ,in2 ,in3) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	ret.mTree->mDepth = _MAXOF_ (mTree->mDepth ,that.mTree->mDepth) + 1 ;
	return std::move (ret) ;
}
} ;