﻿#pragma once

#ifndef __CSC_FUNCTIONAL__
#define __CSC_FUNCTIONAL__
#endif

#include "csc.hpp"
#include "csc_core.hpp"
#include "csc_basic.hpp"
#include "csc_extend.hpp"
#include "csc_array.hpp"
#include "csc_math.hpp"

namespace CSC {
class Operand ;

namespace U {
template <class _ARG1>
using RANK_FUNC_TYPE = FUNCTION_BIND_TYPE<Operand ,REPEAT_PARAMS_TYPE<_ARG1 ,const Operand &>> ;
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
	struct THIS_PACK {
		AnyRef<> mHolder ;
	} ;

private:
	StrongRef<THIS_PACK> mThis ;

public:
	implicit Operand () = default ;

	template <class _ARG1 ,class = ENABLE_TYPE<U::CONSTEXPR_AND<U::CONSTEXPR_NOT<IS_PLACEHOLDER_HELP<_ARG1>> ,U::CONSTEXPR_NOT<IS_SAME_HELP<REMOVE_CVR_TYPE<_ARG1> ,Operand>>>>>
	implicit Operand (_ARG1 &&that) {
		mThis = StrongRef<THIS_PACK>::make () ;
		mThis->mHolder = AnyRef<REMOVE_CVR_TYPE<_ARG1>>::make (_FORWARD_ (ARGV<_ARG1 &&>::ID ,that)) ;
	}

	implicit Operand (const Operand &that) {
		mThis = that.mThis.share () ;
	}

	inline Operand &operator= (const Operand &that) {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~Operand () ;
			new (this) Operand (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	BOOL exist () const {
		if (!mThis.exist ())
			return FALSE ;
		if (!mThis->mHolder.exist ())
			return FALSE ;
		return TRUE ;
	}

	BOOL equal (const Operand &that) const {
		if (_EBOOL_ (mThis.exist ()) != _EBOOL_ (that.mThis.exist ()))
			return FALSE ;
		if (!mThis.exist ())
			return TRUE ;
		if (DEPTR[mThis.self] != DEPTR[that.mThis.self])
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const Operand &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const Operand &that) const {
		return !equal (that) ;
	}

	template <class _ARG1>
	const _ARG1 &as (const ARGVF<_ARG1> &) const leftvalue {
		return template_as (ARGV<REMOVE_CVR_TYPE<_ARG1>>::ID) ;
	}

	template <class _ARG1>
	imports const Operand &nth (const ARGV<ARGVP<_ARG1>> &) {
		return _CACHE_ ([&] () {
			return Operand (ARGV<ARGVP<_ARG1>> {}) ;
		}) ;
	}

private:
	template <class _ARG1>
	const _ARG1 &template_as (const ARGVF<_ARG1> &) const leftvalue {
		_DYNAMIC_ASSERT_ (exist ()) ;
		const auto r1x = mThis->mHolder.type_mid () ;
		const auto r2x = _TYPEMID_ (ARGV<_ARG1>::ID) ;
		_DYNAMIC_ASSERT_ (r1x == r2x) ;
		return mThis->mHolder.rebind (ARGV<REMOVE_CVR_TYPE<_ARG1>>::ID).self ;
	}

	const Operand &template_as (const ARGVF<Operand> &) const leftvalue {
		return DEREF[this] ;
	}
} ;

class Operator {
private:
	struct Private {
		class DefHolder ;

		template <class ,class>
		class ImplHolder ;
	} ;

	class Holder :
		delegate public Interface {
	public:
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

private:
	StrongRef<Holder> mThis ;

public:
	implicit Operator () = default ;

	template <class _ARG1 ,class = ENABLE_TYPE<U::CONSTEXPR_AND<U::CONSTEXPR_NOT<IS_PLACEHOLDER_HELP<_ARG1>> ,U::CONSTEXPR_NOT<IS_SAME_HELP<REMOVE_CVR_TYPE<_ARG1> ,Operator>>>>>
	implicit Operator (_ARG1 &&that) {
		using R1X = FUNCTION_OF_TYPE<_ARG1> ;
		using R2X = REPEAT_PARAMS_TYPE<CAPACITY_OF_TYPE<FUNCTION_PARAMS_TYPE<R1X>> ,Operand> ;
		_STATIC_ASSERT_ (U::CONSTEXPR_NOT<IS_REFERENCE_HELP<_ARG1>>::compile ()) ;
		using R3X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<R1X ,R2X> ;
		auto rax = Function<R1X> (_FORWARD_ (ARGV<_ARG1 &&>::ID ,that)) ;
		mThis = StrongRef<R3X>::make (ARGVP0 ,_MOVE_ (rax)) ;
	}

	implicit Operator (const Operator &that) {
		mThis = that.mThis.share () ;
	}

	inline Operator &operator= (const Operator &that) {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~Operator () ;
			new (this) Operator (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	LENGTH rank () const {
		if (!mThis.exist ())
			return VAR_NONE ;
		return mThis->rank () ;
	}

	template <class... _ARGS>
	Operand invoke (const LexicalNode &node ,const _ARGS &...funcval) const {
		_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<_ARGS...>) <= 9) ;
		_DYNAMIC_ASSERT_ (mThis.exist ()) ;
		return mThis->invoke (node ,funcval...) ;
	}

	template <class... _ARGS>
	inline Operand operator() (const LexicalNode &node ,const _ARGS &...funcval) const {
		return invoke (node ,funcval...) ;
	}
} ;

class Operator::Private::DefHolder :
	delegate public Holder {
public:
	implicit DefHolder () = default ;

	Operand invoke (const LexicalNode &node) const override {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	Operand invoke (const LexicalNode &node ,const Operand &) const override {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	Operand invoke (const LexicalNode &node ,const Operand & ,const Operand &) const override {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand &) const override {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand & ,const Operand &) const override {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand &) const override {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand &) const override {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand &) const override {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand &) const override {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	Operand invoke (const LexicalNode &node ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand & ,const Operand &) const override {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}
} ;

template <class UNIT1 ,class... UNITS1 ,class... UNITS2>
class Operator::Private::ImplHolder<DEF<UNIT1 (UNITS1...)> ,ARGVS<UNITS2...>> :
	delegate public DefHolder {
	_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS1...>) == _CAPACITYOF_ (ARGVS<UNITS2...>)) ;

private:
	Function<UNIT1 (UNITS1...)> mFunctor ;

public:
	implicit ImplHolder () = delete ;

	template <class... _ARGS>
	explicit ImplHolder (const DEF<decltype (ARGVP0)> & ,_ARGS &&...initval) :
		delegate mFunctor (_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) {}

	LENGTH rank () const override {
		return _CAPACITYOF_ (ARGVS<UNITS2...>) ;
	}

	Operand invoke (const LexicalNode &node ,FORWARD_TRAITS_TYPE<UNITS2> &&...funcval) const {
		const auto r1x = TupleBinder<const UNITS2...> (funcval...) ;
		auto rax = template_invoke (r1x ,ARGV<ARGVS<UNITS1...>>::ID) ;
		return Operand (_MOVE_ (rax)) ;
	}

private:
	UNIT1 template_invoke (const Tuple<> &parameter ,const ARGVF<ARGVS<>> & ,FORWARD_TRAITS_TYPE<UNITS1> &&...funcval) const {
		return mFunctor (_FORWARD_ (ARGV<FORWARD_TRAITS_TYPE<UNITS1> &&>::ID ,funcval)...) ;
	}

	template <class _ARG1 ,class _ARG2 ,class... _ARGS>
	UNIT1 template_invoke (const _ARG1 &parameter ,const ARGVF<_ARG2> & ,_ARGS &&...funcval) const {
		using R1X = PARAMS_ONE_TYPE<_ARG2> ;
		using R2X = PARAMS_REST_TYPE<_ARG2> ;
		auto &r1x = parameter.one ().as (ARGV<R1X>::ID) ;
		return template_invoke (parameter.rest () ,ARGV<R2X>::ID ,_FORWARD_ (ARGV<_ARGS &&>::ID ,funcval)... ,r1x) ;
	}
} ;

template <class UNIT1 ,class... UNITS1 ,class... UNITS2>
class Operator::Private::ImplHolder<DEF<UNIT1 (const LexicalNode & ,UNITS1...)> ,ARGVS<Operand ,UNITS2...>> :
	delegate public DefHolder {
	_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS1...>) == _CAPACITYOF_ (ARGVS<UNITS2...>)) ;

private:
	Function<UNIT1 (const LexicalNode & ,UNITS1...)> mFunctor ;

public:
	implicit ImplHolder () = delete ;

	template <class... _ARGS>
	explicit ImplHolder (const DEF<decltype (ARGVP0)> & ,_ARGS &&...initval) :
		delegate mFunctor (_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) {}

	LENGTH rank () const override {
		return _CAPACITYOF_ (ARGVS<UNITS2...>) ;
	}

	Operand invoke (const LexicalNode &node ,FORWARD_TRAITS_TYPE<UNITS2> &&...funcval) const override {
		const auto r1x = TupleBinder<const UNITS2...> (funcval...) ;
		auto rax = template_invoke (r1x ,ARGV<ARGVS<UNITS1...>>::ID ,node) ;
		return Operand (_MOVE_ (rax)) ;
	}

private:
	UNIT1 template_invoke (const Tuple<> &parameter ,const ARGVF<ARGVS<>> & ,const LexicalNode &node ,FORWARD_TRAITS_TYPE<UNITS1> &&...funcval) const {
		return mFunctor (node ,_FORWARD_ (ARGV<FORWARD_TRAITS_TYPE<UNITS1> &&>::ID ,funcval)...) ;
	}

	template <class _ARG1 ,class _ARG2 ,class... _ARGS>
	UNIT1 template_invoke (const _ARG1 &parameter ,const ARGVF<_ARG2> & ,_ARGS &&...funcval) const {
		using R1X = PARAMS_ONE_TYPE<_ARG2> ;
		using R2X = PARAMS_REST_TYPE<_ARG2> ;
		auto &r1x = parameter.one ().as (ARGV<R1X>::ID) ;
		return template_invoke (parameter.rest () ,ARGV<R2X>::ID ,_FORWARD_ (ARGV<_ARGS &&>::ID ,funcval)... ,r1x) ;
	}
} ;

template <class RANK ,class RETR = Operand>
class Expression ;

namespace U {
template <class _ARG1>
struct RETR_FUNC {
	_STATIC_ASSERT_ (U::CONSTEXPR_COMPR_GT<U::CONSTEXPR_DECREASE<_ARG1> ,ZERO>::compile ()) ;
	using R1X = ARGC_TYPE<U::CONSTEXPR_DECREASE<_ARG1>> ;
	using R2X = typename RETR_FUNC<R1X>::TYPE ;
	using TYPE = Expression<RANK1 ,R2X> ;
} ;

template <>
struct RETR_FUNC<ZERO> {
	using TYPE = Operand ;
} ;

template <>
struct RETR_FUNC<ARGC<1>> {
	using TYPE = Operand ;
} ;

template <class _ARG1>
using RETR_FUNC_TYPE = typename RETR_FUNC<CAPACITY_OF_TYPE<FUNCTION_PARAMS_TYPE<_ARG1>>>::TYPE ;
} ;

class LexicalNode {
private:
	template <class ,class>
	friend class Expression ;
	Operand mOperand ;
	Operator mOperator ;
	ARRAY3<StrongRef<LexicalNode>> mChild ;
	LENGTH mRank ;
	LENGTH mDepth ;

public:
	implicit LexicalNode () {
		mRank = VAR_NONE ;
		mDepth = 0 ;
	}
} ;

namespace U {
template <class _ARG1>
struct CONSTEXPR_MAXOF {
	imports constexpr VAR compile () {
		using R1X = PARAMS_ONE_TYPE<_ARG1> ;
		using R2X = CONSTEXPR_MAXOF<PARAMS_REST_TYPE<_ARG1>> ;
		using R3X = CONSTEXPR_MAX<R1X ,R2X> ;
		return R3X::compile () ;
	}
} ;

template <class _ARG1>
struct CONSTEXPR_MAXOF<ARGVS<_ARG1>> {
	imports constexpr VAR compile () {
		return _ARG1::compile () ;
	}
} ;
} ;

template <class RETR ,class... UNITS>
class Expression<SPECIALIZATION<Operand (UNITS...)> ,RETR> {
	_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS...>) >= 0 && _CAPACITYOF_ (ARGVS<UNITS...>) <= 9) ;

protected:
	using RANK = DEF<Operand (UNITS...)> ;

protected:
	template <class ,class>
	friend class Expression ;
	StrongRef<LexicalNode> mThis ;

protected:
	implicit Expression () :
		delegate Expression (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	implicit Expression (const Operator &that) :
		delegate Expression (ARGVP0) {
		_DYNAMIC_ASSERT_ (that.rank () == _CAPACITYOF_ (ARGVS<UNITS...>)) ;
		mThis->mOperator = that ;
		mThis->mDepth = 1 ;
	}

	implicit Expression (const Expression &that) {
		mThis = that.mThis.share () ;
	}

	inline Expression &operator= (const Expression &that) {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~Expression () ;
			new (this) Expression (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	const RETR &invoke (const UNITS &...funcval) const leftvalue {
		_DYNAMIC_ASSERT_ (mThis.exist ()) ;
		auto rax = mThis.share () ;
		_DYNAMIC_ASSERT_ (rax->mOperator.rank () == _CAPACITYOF_ (ARGVS<UNITS...>)) ;
		rax->mOperand = rax->mOperator (rax.self ,funcval...) ;
		return rax->mOperand.as (ARGV<RETR>::ID) ;
	}

	Expression<RANK ,RETR> flip () const {
		Expression<RANK ,RETR> ret ;
		_STATIC_ASSERT_ (IS_SAME_HELP<RANK ,U::RANK_FUNC_TYPE<CAPACITY_OF_TYPE<ARGVS<UNITS...>>>>::compile ()) ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const UNITS &...ins) {
			auto &r1x = _CAST_ (ARGV<Expression<RANK ,RETR>>::ID ,node.mChild[0]) ;
			const auto r2x = TupleBinder<const UNITS...> (ins...) ;
			auto &r3x = r1x.template_flip_invoke (ARGV<ARGVS<const UNITS...>>::ID ,r2x) ;
			_STATIC_UNUSED_ (r3x) ;
			return r1x.mThis->mOperand ;
		}) ;
		ret.mThis->mChild[0] = mThis.share () ;
		ret.mThis->mDepth = MathProc::maxof (mThis->mDepth) + 1 ;
		return _MOVE_ (ret) ;
	}

	template <class... _ARGS ,class _RET = REMOVE_CVR_TYPE<Expression<U::RANK_FUNC_TYPE<U::CONSTEXPR_MAXOF<ARGVS<_ARGS...>>> ,RETR>>>
	_RET flips (const ARGV<ARGVP<_ARGS>> &...) const {
		using R1X = U::RANK_FUNC_TYPE<U::CONSTEXPR_MAXOF<ARGVS<_ARGS...>>> ;
		_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<_ARGS...>) == _CAPACITYOF_ (ARGVS<UNITS...>)) ;
		return template_flips (ARGV<R1X>::ID ,ARGV<ARGVS<_ARGS...>>::ID ,ARGV<FUNCTION_PARAMS_TYPE<R1X>>::ID) ;
	}

	Expression<RANK0 ,Expression<RANK ,RETR>> fold () const {
		Expression<RANK0 ,Expression<RANK ,RETR>> ret ;
		_STATIC_ASSERT_ (IS_SAME_HELP<RANK0 ,U::RANK_FUNC_TYPE<ZERO>>::compile ()) ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node) {
			auto &r1x = _CAST_ (ARGV<Expression<RANK ,RETR>>::ID ,node.mChild[0]) ;		
			return Operand (r1x.share ()) ;
		}) ;
		ret.mThis->mChild[0] = mThis.share () ;
		ret.mThis->mDepth = MathProc::maxof (mThis->mDepth) + 1 ;
		return _MOVE_ (ret) ;
	}

	template <class _RET = REMOVE_CVR_TYPE<Expression<RANK1 ,U::RETR_FUNC_TYPE<RANK>>>>
	_RET curry () const {
		return template_curry (ARGV<RANK>::ID) ;
	}

	template <class _ARG1 ,class _ARG2 ,class _RET = REMOVE_CVR_TYPE<Expression<U::RANK_FUNC_TYPE<U::CONSTEXPR_ADD<U::CONSTEXPR_DECREASE<CAPACITY_OF_TYPE<FUNCTION_PARAMS_TYPE<RANK>>> ,CAPACITY_OF_TYPE<FUNCTION_PARAMS_TYPE<_ARG1>>>> ,RETR>>>
	_RET bind (const Expression<_ARG1 ,_ARG2> &that) const {
		using R1X = U::RANK_FUNC_TYPE<U::CONSTEXPR_ADD<U::CONSTEXPR_DECREASE<CAPACITY_OF_TYPE<FUNCTION_PARAMS_TYPE<RANK>>> ,CAPACITY_OF_TYPE<FUNCTION_PARAMS_TYPE<_ARG1>>>> ;
		return template_bind (ARGV<R1X>::ID ,that ,ARGV<FUNCTION_PARAMS_TYPE<R1X>>::ID) ;
	}

protected:
	explicit Expression (const DEF<decltype (ARGVP0)> &) {
		mThis = StrongRef<LexicalNode>::make () ;
		mThis->mRank = _CAPACITYOF_ (FUNCTION_PARAMS_TYPE<RANK>) ;
	}

	template <class _ARG1 ,class _ARG2 ,class... _ARGS>
	const RETR &template_flip_invoke (const ARGVF<ARGVS<>> & ,const _ARG2 &parameter ,const _ARGS &...funcval) const leftvalue {
		return invoke (funcval...) ;
	}

	template <class _ARG1 ,class _ARG2 ,class... _ARGS>
	const RETR &template_flip_invoke (const ARGVF<ARGVS<_ARG1>> & ,const _ARG2 &parameter ,const _ARGS &...funcval) const leftvalue {
		return invoke (parameter.one () ,funcval...) ;
	}

	template <class _ARG1 ,class _ARG2 ,class... _ARGS>
	const RETR &template_flip_invoke (const ARGVF<_ARG1> & ,const _ARG2 &parameter ,const _ARGS &...funcval) const leftvalue {
		return template_flip_invoke (ARGV<PARAMS_REST_TYPE<_ARG1>>::ID ,parameter.rest () ,funcval... ,parameter.one ()) ;
	}

	template <class _ARG1 ,class... _ARGS>
	const RETR &template_flips_invoke (const _ARG1 &parameter ,const ARGVF<ARGVS<_ARGS...>> &) const leftvalue {
		return invoke (parameter.pick (ARGV<ARGVP<_ARGS>> {})...) ;
	}

	template <class _ARG1 ,class _ARG2 ,class... _ARGS>
	Expression<_ARG1 ,RETR> template_flips (const ARGVF<_ARG1> & ,const ARGVF<_ARG2> & ,const ARGVF<ARGVS<_ARGS...>> &) const {
		Expression<_ARG1 ,RETR> ret ;
		_STATIC_ASSERT_ (IS_SAME_HELP<_ARG1 ,U::RANK_FUNC_TYPE<CAPACITY_OF_TYPE<ARGVS<_ARGS...>>>>::compile ()) ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const _ARGS &...ins) {
			auto &r1x = _CAST_ (ARGV<Expression<RANK ,RETR>>::ID ,node.mChild[0]) ;
			const auto r2x = TupleBinder<const _ARGS...> (ins...) ;
			auto &r3x = r1x.template_flips_invoke (r2x ,ARGV<_ARG2>::ID) ;
			_STATIC_UNUSED_ (r3x) ;
			return r1x.mThis->mOperand ;
		}) ;
		ret.mThis->mChild[0] = mThis.share () ;
		ret.mThis->mDepth = MathProc::maxof (mThis->mDepth) + 1 ;
		return _MOVE_ (ret) ;
	}

	Expression<RANK ,RETR> template_curry (const ARGVF<RANK1> &) const {
		return _CAST_ (ARGV<Expression<RANK ,RETR>>::ID ,DEREF[this]) ;
	}

	template <class _ARG1 ,class _RET = REMOVE_CVR_TYPE<Expression<RANK1 ,U::RETR_FUNC_TYPE<_ARG1>>>>
	_RET template_curry (const ARGVF<_ARG1> &) const {
		using R1X = DEPENDENT_TYPE<Expression<RANK1 ,U::RETR_FUNC_TYPE<_ARG1>> ,struct ANONYMOUS> ;
		R1X ret ;
		_STATIC_ASSERT_ (IS_SAME_HELP<RANK1 ,U::RANK_FUNC_TYPE<ARGC<1>>>::compile ()) ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1x = _CAST_ (ARGV<Expression<_ARG1 ,RETR>>::ID ,node.mChild[0]) ;
			const auto r2x = Expression<RANK0> (in1) ;
			return Operand (r1x.bind (r2x).curry ()) ;
		}) ;
		ret.mThis->mChild[0] = mThis.share () ;
		ret.mThis->mDepth = MathProc::maxof (mThis->mDepth) + 1 ;
		return _MOVE_ (ret) ;
	}

	template <class... _ARGS>
	const RETR &template_bind_invoke (const Tuple<> &parameter ,const _ARGS &...funcval) const leftvalue {
		return invoke (funcval...) ;
	}

	template <class _ARG1 ,class... _ARGS>
	const RETR &template_bind_invoke (const _ARG1 &parameter ,const _ARGS &...funcval) const leftvalue {
		return template_bind_invoke (parameter.rest () ,funcval... ,parameter.one ()) ;
	}

	template <class _ARG1 ,class _ARG2 ,class _ARG3 ,class... _ARGS>
	const RETR &template_bind_patch (const Expression<_ARG1 ,_ARG3> &patch_ ,const ARGVF<ARGVS<>> & ,const _ARG2 &parameter ,const _ARGS &...funcval) const leftvalue {
		return template_bind_invoke (parameter ,patch_.invoke (funcval...)) ;
	}

	template <class _ARG1 ,class _ARG2 ,class _ARG3 ,class _ARG4 ,class... _ARGS>
	const RETR &template_bind_patch (const Expression<_ARG1 ,_ARG4> &patch_ ,const ARGVF<_ARG2> & ,const _ARG3 &parameter ,const _ARGS &...funcval) const leftvalue {
		return template_bind_patch (patch_ ,ARGV<PARAMS_REST_TYPE<_ARG2>>::ID ,parameter.rest () ,funcval... ,parameter.one ()) ;
	}

	template <class _ARG1 ,class _ARG2 ,class _ARG3 ,class... _ARGS>
	Expression<_ARG1 ,RETR> template_bind (const ARGVF<_ARG1> & ,const Expression<_ARG2 ,_ARG3> &that ,const ARGVF<ARGVS<_ARGS...>> &) const {
		Expression<_ARG1 ,RETR> ret ;
		_STATIC_ASSERT_ (IS_SAME_HELP<_ARG1 ,U::RANK_FUNC_TYPE<CAPACITY_OF_TYPE<ARGVS<_ARGS...>>>>::compile ()) ;
		ret.mThis->mOperator = Operator ([] (const LexicalNode &node ,const _ARGS &...ins) {
			auto &r1x = _CAST_ (ARGV<Expression<RANK ,RETR>>::ID ,node.mChild[0]) ;
			auto &r2x = _CAST_ (ARGV<Expression<_ARG2 ,_ARG3>>::ID ,node.mChild[1]) ;
			const auto r3x = TupleBinder<const _ARGS...> (ins...) ;
			auto &r4x = r1x.template_bind_patch (r2x ,ARGV<FUNCTION_PARAMS_TYPE<_ARG2>>::ID ,r3x) ;
			_STATIC_UNUSED_ (r4x) ;
			return r1x.mThis->mOperand ;
		}) ;
		ret.mThis->mChild[0] = mThis.share () ;
		ret.mThis->mChild[1] = that.mThis.share () ;
		ret.mThis->mDepth = MathProc::maxof (mThis->mDepth ,that.mThis->mDepth) + 1 ;
		return _MOVE_ (ret) ;
	}
} ;

template <class RETR>
class Expression<RANK0 ,RETR> :
	delegate private Expression<SPECIALIZATION<RANK0>> {
private:
	using SPECIALIZATION_BASE = Expression<SPECIALIZATION<RANK0> ,RETR> ;

private:
	template <class ,class>
	friend class Expression ;
	friend SPECIALIZATION_BASE ;
	using SPECIALIZATION_BASE::mThis ;

public:
	implicit Expression () = default ;

	implicit Expression (const Operand &that) {
		_DYNAMIC_ASSERT_ (that.exist ()) ;
		mThis->mOperand = that ;
		mThis->mDepth = 1 ;
	}

	implicit Expression (const Operator &that) :
		delegate SPECIALIZATION_BASE (that) {
		_STATIC_WARNING_ ("noop") ;
	}

	const RETR &invoke () const leftvalue {
		_DYNAMIC_ASSERT_ (mThis.exist ()) ;
		if switch_once (TRUE) {
			if (mThis->mOperator.rank () == VAR_NONE)
				discard ;
			auto rax = mThis.share () ;
			_DYNAMIC_ASSERT_ (rax->mOperator.rank () == 0) ;
			const auto r1x = _MOVE_ (rax->mOperator) ;
			rax->mOperand = r1x (rax.self) ;
			rax->mChild[0] = StrongRef<LexicalNode> () ;
			rax->mChild[1] = StrongRef<LexicalNode> () ;
			rax->mChild[2] = StrongRef<LexicalNode> () ;
		}
		return mThis->mOperand.as (ARGV<RETR>::ID) ;
	}

	template <class... _ARGS>
	inline const RETR &operator() (const _ARGS &...funcval) const leftvalue {
		return invoke (funcval...) ;
	}
} ;

template <class RETR>
class Expression<RANK1 ,RETR> :
	delegate private Expression<SPECIALIZATION<RANK1> ,RETR> {
private:
	using SPECIALIZATION_BASE = Expression<SPECIALIZATION<RANK1> ,RETR> ;

private:
	template <class ,class>
	friend class Expression ;
	friend SPECIALIZATION_BASE ;
	using SPECIALIZATION_BASE::mThis ;

public:
	implicit Expression () = default ;

	implicit Expression (const Operator &that) :
		delegate SPECIALIZATION_BASE (that) {
		_STATIC_WARNING_ ("noop") ;
	}

	using SPECIALIZATION_BASE::invoke ;

	template <class... _ARGS>
	inline const RETR &operator() (const _ARGS &...funcval) const leftvalue {
		return invoke (funcval...) ;
	}

	using SPECIALIZATION_BASE::flip ;

	using SPECIALIZATION_BASE::flips ;

	using SPECIALIZATION_BASE::fold ;

	using SPECIALIZATION_BASE::curry ;

	using SPECIALIZATION_BASE::bind ;

	template <class _ARG1 ,class _ARG2 ,class _RET = REMOVE_CVR_TYPE<Expression<U::RANK_FUNC_TYPE<U::CONSTEXPR_ADD<U::CONSTEXPR_DECREASE<CAPACITY_OF_TYPE<FUNCTION_PARAMS_TYPE<RANK1>>> ,CAPACITY_OF_TYPE<FUNCTION_PARAMS_TYPE<_ARG1>>>> ,RETR>>>
	inline _RET operator+ (const Expression<_ARG1 ,_ARG2> &that) const {
		return bind (that) ;
	}
} ;

template <class RANK ,class RETR>
class Expression :
	delegate private Expression<SPECIALIZATION<RANK> ,RETR> {

private:
	using SPECIALIZATION_BASE = Expression<SPECIALIZATION<RANK> ,RETR> ;

private:
	template <class ,class>
	friend class Expression ;
	friend SPECIALIZATION_BASE ;
	using SPECIALIZATION_BASE::mThis ;

public:
	implicit Expression () = default ;

	implicit Expression (const Operator &that) :
		delegate SPECIALIZATION_BASE (that) {
		_STATIC_WARNING_ ("noop") ;
	}

	using SPECIALIZATION_BASE::invoke ;

	template <class... _ARGS>
	inline const RETR &operator() (const _ARGS &...funcval) const leftvalue {
		return invoke (funcval...) ;
	}

	using SPECIALIZATION_BASE::flip ;

	using SPECIALIZATION_BASE::flips ;

	using SPECIALIZATION_BASE::fold ;

	using SPECIALIZATION_BASE::curry ;

	using SPECIALIZATION_BASE::bind ;

	template <class _ARG1 ,class _ARG2 ,class _RET = REMOVE_CVR_TYPE<Expression<U::RANK_FUNC_TYPE<U::CONSTEXPR_ADD<U::CONSTEXPR_DECREASE<CAPACITY_OF_TYPE<FUNCTION_PARAMS_TYPE<RANK>>> ,CAPACITY_OF_TYPE<FUNCTION_PARAMS_TYPE<_ARG1>>>> ,RETR>>>
	inline _RET operator+ (const Expression<_ARG1 ,_ARG2> &that) const {
		return bind (that) ;
	}
} ;
} ;