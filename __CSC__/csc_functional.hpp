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
namespace TS {
class Operand ;

using RANK0 = PTR<Operand ()> ;
using RANK1 = PTR<Operand (const Operand &)> ;
using RANK2 = PTR<Operand (const Operand & ,const Operand &)> ;
using RANK3 = PTR<Operand (const Operand & ,const Operand & ,const Operand &)> ;

class LexicalNode ;

using RANK0_LN = PTR<Operand (const LexicalNode &)> ;
using RANK1_LN = PTR<Operand (const LexicalNode & ,const Operand &)> ;
using RANK2_LN = PTR<Operand (const LexicalNode & ,const Operand & ,const Operand &)> ;
using RANK3_LN = PTR<Operand (const LexicalNode & ,const Operand & ,const Operand & ,const Operand &)> ;

namespace U {
template <class>
struct EXPRESSION_RANK_TRAITS ;

template <>
struct EXPRESSION_RANK_TRAITS<RANK0> {
	using TYPE = ARGC<0> ;
} ;

template <>
struct EXPRESSION_RANK_TRAITS<RANK1> {
	using TYPE = ARGC<1> ;
} ;

template <>
struct EXPRESSION_RANK_TRAITS<RANK2> {
	using TYPE = ARGC<2> ;
} ;

template <>
struct EXPRESSION_RANK_TRAITS<RANK3> {
	using TYPE = ARGC<3> ;
} ;

template <>
struct EXPRESSION_RANK_TRAITS<RANK0_LN> {
	using TYPE = ARGC<0> ;
} ;

template <>
struct EXPRESSION_RANK_TRAITS<RANK1_LN> {
	using TYPE = ARGC<1> ;
} ;

template <>
struct EXPRESSION_RANK_TRAITS<RANK2_LN> {
	using TYPE = ARGC<2> ;
} ;

template <>
struct EXPRESSION_RANK_TRAITS<RANK3_LN> {
	using TYPE = ARGC<3> ;
} ;
} ;

class Operand {
private:
	class Lazy {
	private:
		friend Operand ;
		AnyRef<void> mValue ;
		AnyRef<void> mEvaluation ;
	} ;

private:
	SharedRef<Lazy> mLazy ;

public:
	inline Operand () = default ;

	template <class _ARG1 ,class = ENABLE_TYPE<!std::is_same<REMOVE_CVR_TYPE<_ARG1> ,Operand>::value>>
	inline implicit Operand (_ARG1 &&that) {
		mLazy = SharedRef<Lazy>::make () ;
		mLazy->mValue = AnyRef<_ARG1>::make (std::forward<_ARG1> (that)) ;
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
		virtual Operand invoke () const = 0 ;
		virtual Operand invoke (const Operand &in1) const = 0 ;
		virtual Operand invoke (const Operand &in1 ,const Operand &in2) const = 0 ;
		virtual Operand invoke (const Operand &in1 ,const Operand &in2 ,const Operand &in3) const = 0 ;
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

	inline implicit Operator (const RANK0 &that) ;

	inline implicit Operator (const RANK1 &that) ;

	inline implicit Operator (const RANK2 &that) ;

	inline implicit Operator (const RANK3 &that) ;

	inline implicit Operator (const RANK0_LN &that) ;

	inline implicit Operator (const RANK1_LN &that) ;

	inline implicit Operator (const RANK2_LN &that) ;

	inline implicit Operator (const RANK3_LN &that) ;

	template <class _ARG1 ,class = ENABLE_TYPE<!std::is_same<REMOVE_CVR_TYPE<_ARG1> ,Operator>::value>>
	inline implicit Operator (const _ARG1 &that) ;

	inline LENGTH rank () const {
		if (mHolder == NULL)
			return VAR_NONE ;
		return mHolder->rank () ;
	}

	inline Operand operator() () const {
		_DYNAMIC_ASSERT_ (mHolder != NULL) ;
		return mHolder->invoke () ;
	}

	inline Operand operator() (const Operand &in1) const {
		_DYNAMIC_ASSERT_ (mHolder != NULL) ;
		return mHolder->invoke (in1) ;
	}

	inline Operand operator() (const Operand &in1 ,const Operand &in2) const {
		_DYNAMIC_ASSERT_ (mHolder != NULL) ;
		return mHolder->invoke (in1 ,in2) ;
	}

	inline Operand operator() (const Operand &in1 ,const Operand &in2 ,const Operand &in3) const {
		_DYNAMIC_ASSERT_ (mHolder != NULL) ;
		return mHolder->invoke (in1 ,in2 ,in3) ;
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
	inline ImplHolder () = default ;

	inline LENGTH rank () const override {
		return VAR_NONE ;
	}

	inline Operand invoke () const override {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	inline Operand invoke (const Operand &in1) const {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	inline Operand invoke (const Operand &in1 ,const Operand &in2) const {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	inline Operand invoke (const Operand &in1 ,const Operand &in2 ,const Operand &in3) const {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Operand () ;
	}

	inline Operand invoke (const LexicalNode &node) const override {
		return invoke () ;
	}

	inline Operand invoke (const LexicalNode &node ,const Operand &in1) const {
		return invoke (in1) ;
	}

	inline Operand invoke (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) const {
		return invoke (in1 ,in2) ;
	}

	inline Operand invoke (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) const {
		return invoke (in1 ,in2 ,in3) ;
	}
} ;

template <>
class Operator::ImplHolder<RANK0> :public ImplHolder<void> {
private:
	RANK0 mFunction ;

public:
	inline ImplHolder () = delete ;

	inline explicit ImplHolder (const RANK0 &function_) :mFunction (function_) {}

	inline LENGTH rank () const override {
		return U::EXPRESSION_RANK_TRAITS<RANK0>::TYPE::value ;
	}

	inline Operand invoke () const override {
		return mFunction () ;
	}
} ;

inline Operator::Operator (const RANK0 &that) {
	_DEBUG_ASSERT_ (that != NULL) ;
	auto &r1y = _CACHE_ ([&] () {
		return SharedRef<Set<RANK0 ,AutoRef<Operator::ImplHolder<RANK0>>>>::make () ;
	}) ;
	INDEX ix = r1y->find (that) ;
	if switch_case (TRUE) {
		if (ix != VAR_NONE)
			discard ;
		ix = r1y->insert (that) ;
		r1y.self[ix].item = AutoRef<Operator::ImplHolder<RANK0>>::make (that) ;
	}
	mHolder = &r1y.self[ix].item.self ;
}

template <>
class Operator::ImplHolder<RANK1> :public ImplHolder<void> {
private:
	RANK1 mFunction ;

public:
	inline ImplHolder () = delete ;

	inline explicit ImplHolder (const RANK1 &function_) :mFunction (function_) {}

	inline LENGTH rank () const override {
		return U::EXPRESSION_RANK_TRAITS<RANK1>::TYPE::value ;
	}

	inline Operand invoke (const Operand &in1) const {
		return mFunction (in1) ;
	}
} ;

inline Operator::Operator (const RANK1 &that) {
	_DEBUG_ASSERT_ (that != NULL) ;
	auto &r1y = _CACHE_ ([&] () {
		return SharedRef<Set<RANK1 ,AutoRef<Operator::ImplHolder<RANK1>>>>::make () ;
	}) ;
	INDEX ix = r1y->find (that) ;
	if switch_case (TRUE) {
		if (ix != VAR_NONE)
			discard ;
		ix = r1y->insert (that) ;
		r1y.self[ix].item = AutoRef<Operator::ImplHolder<RANK1>>::make (that) ;
	}
	mHolder = &r1y.self[ix].item.self ;
}

template <>
class Operator::ImplHolder<RANK2> :public ImplHolder<void> {
private:
	RANK2 mFunction ;

public:
	inline ImplHolder () = delete ;

	inline explicit ImplHolder (const RANK2 &function_) :mFunction (function_) {}

	inline LENGTH rank () const override {
		return U::EXPRESSION_RANK_TRAITS<RANK2>::TYPE::value ;
	}

	inline Operand invoke (const Operand &in1 ,const Operand &in2) const {
		return mFunction (in1 ,in2) ;
	}
} ;

inline Operator::Operator (const RANK2 &that) {
	_DEBUG_ASSERT_ (that != NULL) ;
	auto &r1y = _CACHE_ ([&] () {
		return SharedRef<Set<RANK2 ,AutoRef<Operator::ImplHolder<RANK2>>>>::make () ;
	}) ;
	INDEX ix = r1y->find (that) ;
	if switch_case (TRUE) {
		if (ix != VAR_NONE)
			discard ;
		ix = r1y->insert (that) ;
		r1y.self[ix].item = AutoRef<Operator::ImplHolder<RANK2>>::make (that) ;
	}
	mHolder = &r1y.self[ix].item.self ;
}

template <>
class Operator::ImplHolder<RANK3> :public ImplHolder<void> {
private:
	RANK3 mFunction ;

public:
	inline ImplHolder () = delete ;

	inline explicit ImplHolder (const RANK3 &function_) :mFunction (function_) {}

	inline LENGTH rank () const override {
		return U::EXPRESSION_RANK_TRAITS<RANK3>::TYPE::value ;
	}

	inline Operand invoke (const Operand &in1 ,const Operand &in2 ,const Operand &in3) const {
		return mFunction (in1 ,in2 ,in3) ;
	}
} ;

inline Operator::Operator (const RANK3 &that) {
	_DEBUG_ASSERT_ (that != NULL) ;
	auto &r1y = _CACHE_ ([&] () {
		return SharedRef<Set<RANK3 ,AutoRef<Operator::ImplHolder<RANK3>>>>::make () ;
	}) ;
	INDEX ix = r1y->find (that) ;
	if switch_case (TRUE) {
		if (ix != VAR_NONE)
			discard ;
		ix = r1y->insert (that) ;
		r1y.self[ix].item = AutoRef<Operator::ImplHolder<RANK3>>::make (that) ;
	}
	mHolder = &r1y.self[ix].item.self ;
}

template <>
class Operator::ImplHolder<RANK0_LN> :public ImplHolder<void> {
private:
	RANK0_LN mFunction ;

public:
	inline ImplHolder () = delete ;

	inline explicit ImplHolder (const RANK0_LN &function_) :mFunction (function_) {}

	inline LENGTH rank () const override {
		return U::EXPRESSION_RANK_TRAITS<RANK0_LN>::TYPE::value ;
	}

	inline Operand invoke (const LexicalNode &node) const override {
		return mFunction (node) ;
	}
} ;

inline Operator::Operator (const RANK0_LN &that) {
	_DEBUG_ASSERT_ (that != NULL) ;
	auto &r1y = _CACHE_ ([&] () {
		return SharedRef<Set<RANK0_LN ,AutoRef<Operator::ImplHolder<RANK0_LN>>>>::make () ;
	}) ;
	INDEX ix = r1y->find (that) ;
	if switch_case (TRUE) {
		if (ix != VAR_NONE)
			discard ;
		ix = r1y->insert (that) ;
		r1y.self[ix].item = AutoRef<Operator::ImplHolder<RANK0_LN>>::make (that) ;
	}
	mHolder = &r1y.self[ix].item.self ;
}

template <>
class Operator::ImplHolder<RANK1_LN> :public ImplHolder<void> {
private:
	RANK1_LN mFunction ;

public:
	inline ImplHolder () = delete ;

	inline explicit ImplHolder (const RANK1_LN &function_) :mFunction (function_) {}

	inline LENGTH rank () const override {
		return U::EXPRESSION_RANK_TRAITS<RANK1_LN>::TYPE::value ;
	}

	inline Operand invoke (const LexicalNode &node ,const Operand &in1) const {
		return mFunction (node ,in1) ;
	}
} ;

inline Operator::Operator (const RANK1_LN &that) {
	_DEBUG_ASSERT_ (that != NULL) ;
	auto &r1y = _CACHE_ ([&] () {
		return SharedRef<Set<RANK1_LN ,AutoRef<Operator::ImplHolder<RANK1_LN>>>>::make () ;
	}) ;
	INDEX ix = r1y->find (that) ;
	if switch_case (TRUE) {
		if (ix != VAR_NONE)
			discard ;
		ix = r1y->insert (that) ;
		r1y.self[ix].item = AutoRef<Operator::ImplHolder<RANK1_LN>>::make (that) ;
	}
	mHolder = &r1y.self[ix].item.self ;
}

template <>
class Operator::ImplHolder<RANK2_LN> :public ImplHolder<void> {
private:
	RANK2_LN mFunction ;

public:
	inline ImplHolder () = delete ;

	inline explicit ImplHolder (const RANK2_LN &function_) :mFunction (function_) {}

	inline LENGTH rank () const override {
		return U::EXPRESSION_RANK_TRAITS<RANK2_LN>::TYPE::value ;
	}

	inline Operand invoke (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) const {
		return mFunction (node ,in1 ,in2) ;
	}
} ;

inline Operator::Operator (const RANK2_LN &that) {
	_DEBUG_ASSERT_ (that != NULL) ;
	auto &r1y = _CACHE_ ([&] () {
		return SharedRef<Set<RANK2_LN ,AutoRef<Operator::ImplHolder<RANK2_LN>>>>::make () ;
	}) ;
	INDEX ix = r1y->find (that) ;
	if switch_case (TRUE) {
		if (ix != VAR_NONE)
			discard ;
		ix = r1y->insert (that) ;
		r1y.self[ix].item = AutoRef<Operator::ImplHolder<RANK2_LN>>::make (that) ;
	}
	mHolder = &r1y.self[ix].item.self ;
}

template <>
class Operator::ImplHolder<RANK3_LN> :public ImplHolder<void> {
private:
	RANK3_LN mFunction ;

public:
	inline ImplHolder () = delete ;

	inline explicit ImplHolder (const RANK3_LN &function_) :mFunction (function_) {}

	inline LENGTH rank () const override {
		return U::EXPRESSION_RANK_TRAITS<RANK3_LN>::TYPE::value ;
	}

	inline Operand invoke (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) const {
		return mFunction (node ,in1 ,in2 ,in3) ;
	}
} ;

inline Operator::Operator (const RANK3_LN &that) {
	_DEBUG_ASSERT_ (that != NULL) ;
	auto &r1y = _CACHE_ ([&] () {
		return SharedRef<Set<RANK3_LN ,AutoRef<Operator::ImplHolder<RANK3_LN>>>>::make () ;
	}) ;
	INDEX ix = r1y->find (that) ;
	if switch_case (TRUE) {
		if (ix != VAR_NONE)
			discard ;
		ix = r1y->insert (that) ;
		r1y.self[ix].item = AutoRef<Operator::ImplHolder<RANK3_LN>>::make (that) ;
	}
	mHolder = &r1y.self[ix].item.self ;
}

template <class _ARG1>
class Operator::ImplHolder<PTR<_ARG1 ()>> :public ImplHolder<void> {
private:
	using RANK = PTR<_ARG1 ()> ;

private:
	RANK mFunction ;

public:
	inline ImplHolder () = delete ;

	inline explicit ImplHolder (const RANK &function_) :mFunction (function_) {}

	inline LENGTH rank () const override {
		return 0 ;
	}

	inline Operand invoke () const {
		return Operand (mFunction ()) ;
	}
} ;

template <class _ARG1 ,class _ARG2>
class Operator::ImplHolder<PTR<_ARG1 (_ARG2)>> :public ImplHolder<void> {
private:
	using RANK = PTR<_ARG1 (_ARG2)> ;

private:
	RANK mFunction ;

public:
	inline ImplHolder () = delete ;

	inline explicit ImplHolder (const RANK &function_) :mFunction (function_) {}

	inline LENGTH rank () const override {
		return 1 ;
	}

	inline Operand invoke (const Operand &in1) const {
		auto &r1y = in1.template as<_ARG2> () ;
		return Operand (mFunction (r1y)) ;
	}
} ;

template <class _ARG1 ,class _ARG2 ,class _ARG3>
class Operator::ImplHolder<PTR<_ARG1 (_ARG2 ,_ARG3)>> :public ImplHolder<void> {
private:
	using RANK = PTR<_ARG1 (_ARG2 ,_ARG3)> ;

private:
	RANK mFunction ;

public:
	inline ImplHolder () = delete ;

	inline explicit ImplHolder (const RANK &function_) :mFunction (function_) {}

	inline LENGTH rank () const override {
		return 2 ;
	}

	inline Operand invoke (const Operand &in1 ,const Operand &in2) const {
		auto &r1y = in1.template as<_ARG2> () ;
		auto &r2y = in2.template as<_ARG3> () ;
		return Operand (mFunction (r1y ,r2y)) ;
	}
} ;

template <class _ARG1 ,class _ARG2 ,class _ARG3 ,class _ARG4>
class Operator::ImplHolder<PTR<_ARG1 (_ARG2 ,_ARG3 ,_ARG4)>> :public ImplHolder<void> {
private:
	using RANK = PTR<_ARG1 (_ARG2 ,_ARG3 ,_ARG4)> ;

private:
	RANK mFunction ;

public:
	inline ImplHolder () = delete ;

	inline explicit ImplHolder (const RANK &function_) :mFunction (function_) {}

	inline LENGTH rank () const override {
		return 3 ;
	}

	inline Operand invoke (const Operand &in1 ,const Operand &in2 ,const Operand &in3) const {
		auto &r1y = in1.template as<_ARG2> () ;
		auto &r2y = in2.template as<_ARG3> () ;
		auto &r3y = in3.template as<_ARG4> () ;
		return Operand (mFunction (r1y ,r2y ,r3y)) ;
	}
} ;

template <class _ARG1 ,class>
inline Operator::Operator (const _ARG1 &that) {
	using RANK = PTR<REMOVE_FUNCATTR_TYPE<REMOVE_MEMPTR_TYPE<DEF<decltype (&_ARG1::operator())>>>> ;
	_STATIC_ASSERT_ (std::is_convertible<_ARG1 ,RANK>::value) ;
	auto &r1y = _CACHE_ ([&] () {
		return SharedRef<Set<RANK ,AutoRef<Operator::ImplHolder<RANK>>>>::make () ;
	}) ;
	INDEX ix = r1y->find (that) ;
	if switch_case (TRUE) {
		if (ix != VAR_NONE)
			discard ;
		ix = r1y->insert (that) ;
		r1y.self[ix].item = AutoRef<Operator::ImplHolder<RANK>>::make (that) ;
	}
	mHolder = &r1y.self[ix].item.self ;
}

template <class>
class Expression ;

class LexicalNode :public Object::Virtual {
private:
	template <class>
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
	template <class>
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

template <>
class Expression<RANK0> :private LexicalTree<Expression<RANK0>> {
private:
	template <class>
	friend class Expression ;

public:
	inline Expression () = default ;

	inline implicit Expression (const Operand &that) : Expression () {
		_DYNAMIC_ASSERT_ (that.exist ()) ;
		mTree->mOperand = that ;
	}

	inline implicit Expression (const Operator &that) : Expression () {
		_DYNAMIC_ASSERT_ (that.rank () == U::EXPRESSION_RANK_TRAITS<RANK0>::TYPE::value) ;
		mTree->mOperator = that ;
	}

	inline Operand operator() () const {
		_DYNAMIC_ASSERT_ (mTree.exist ()) ;
		if (mTree->mOperand.exist ())
			return mTree->mOperand ;
		return mTree->mOperator (mTree.self) ;
	}
} ;

inline namespace FUNCTIONAL {
template <class _ARG1 ,class... _ARGS>
inline auto &_PICK_ (const DEF<decltype (ARGVP1)> & ,_ARG1 &arg1 ,_ARGS &...args) {
	return arg1 ;
}

template <class _ARG1 ,class... _ARGS>
inline auto &_PICK_ (const DEF<decltype (ARGVP2)> & ,_ARG1 &arg1 ,_ARGS &...args) {
	_STATIC_ASSERT_ (_CAPACITYOF_ (_ARGS) >= 1) ;
	return _PICK_ (ARGVP1 ,args...) ;
}

template <class _ARG1 ,class... _ARGS>
inline auto &_PICK_ (const DEF<decltype (ARGVP3)> & ,_ARG1 &arg1 ,_ARGS &...args) {
	_STATIC_ASSERT_ (_CAPACITYOF_ (_ARGS) >= 2) ;
	return _PICK_ (ARGVP2 ,args...) ;
}

template <class _ARG1 ,class... _ARGS>
inline auto &_PICK_ (const DEF<decltype (ARGVP4)> & ,_ARG1 &arg1 ,_ARGS &...args) {
	_STATIC_ASSERT_ (_CAPACITYOF_ (_ARGS) >= 3) ;
	return _PICK_ (ARGVP3 ,args...) ;
}

template <class _ARG1 ,class... _ARGS>
inline auto &_PICK_ (const DEF<decltype (ARGVP5)> & ,_ARG1 &arg1 ,_ARGS &...args) {
	_STATIC_ASSERT_ (_CAPACITYOF_ (_ARGS) >= 4) ;
	return _PICK_ (ARGVP4 ,args...) ;
}

template <class _ARG1 ,class... _ARGS>
inline auto &_PICK_ (const DEF<decltype (ARGVP6)> & ,_ARG1 &arg1 ,_ARGS &...args) {
	_STATIC_ASSERT_ (_CAPACITYOF_ (_ARGS) >= 5) ;
	return _PICK_ (ARGVP5 ,args...) ;
}

template <class _ARG1 ,class... _ARGS>
inline auto &_PICK_ (const DEF<decltype (ARGVP7)> & ,_ARG1 &arg1 ,_ARGS &...args) {
	_STATIC_ASSERT_ (_CAPACITYOF_ (_ARGS) >= 6) ;
	return _PICK_ (ARGVP6 ,args...) ;
}

template <class _ARG1 ,class... _ARGS>
inline auto &_PICK_ (const DEF<decltype (ARGVP8)> & ,_ARG1 &arg1 ,_ARGS &...args) {
	_STATIC_ASSERT_ (_CAPACITYOF_ (_ARGS) >= 7) ;
	return _PICK_ (ARGVP7 ,args...) ;
}

template <class _ARG1 ,class... _ARGS>
inline auto &_PICK_ (const DEF<decltype (ARGVP9)> & ,_ARG1 &arg1 ,_ARGS &...args) {
	_STATIC_ASSERT_ (_CAPACITYOF_ (_ARGS) >= 8) ;
	return _PICK_ (ARGVP8 ,args...) ;
}
} ;

template <>
class Expression<RANK1> :private LexicalTree<Expression<RANK1>> {
private:
	template <class>
	friend class Expression ;

public:
	inline Expression () = default ;

	inline implicit Expression (const Operator &that) : Expression () {
		_DYNAMIC_ASSERT_ (that.rank () == U::EXPRESSION_RANK_TRAITS<RANK1>::TYPE::value) ;
		mTree->mOperator = that ;
	}

	inline Operand operator() (const Operand &in1) const {
		_DYNAMIC_ASSERT_ (mTree.exist ()) ;
		if (mTree->mOperand.exist ())
			return mTree->mOperand ;
		return mTree->mOperator (mTree.self ,in1) ;
	}

	template <class _ARG1>
	inline Expression<RANK1> curry (const ARGV<_ARG1> &) const {
		Expression<RANK1> ret ;
		ret.mTree->mOperator = _XVALUE_<RANK1_LN> ([] (const LexicalNode &node ,const Operand &in1) {
			auto &r1y = Expression<RANK1>::from (node.mChild[0]) ;
			auto &r2y = _PICK_ (_NULL_<ARGV<_ARG1>> () ,in1) ;
			return r1y (r2y) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		return std::move (ret) ;
	}

	inline Expression<RANK0> operator+ (const Expression<RANK0> &that) const ;

	inline Expression<RANK1> operator+ (const Expression<RANK1> &that) const ;

	inline Expression<RANK2> operator+ (const Expression<RANK2> &that) const ;

	inline Expression<RANK3> operator+ (const Expression<RANK3> &that) const ;

private:
	inline static const Expression &from (const StrongRef<LexicalNode> &me) {
		return _CAST_<Expression> (me) ;
	}
} ;

template <>
class Expression<RANK2> :private LexicalTree<Expression<RANK2>> {
private:
	template <class>
	friend class Expression ;

public:
	inline Expression () = default ;

	inline implicit Expression (const Operator &that) : Expression () {
		_DYNAMIC_ASSERT_ (that.rank () == U::EXPRESSION_RANK_TRAITS<RANK2>::TYPE::value) ;
		mTree->mOperator = that ;
	}

	inline Operand operator() (const Operand &in1 ,const Operand &in2) const {
		_DYNAMIC_ASSERT_ (mTree.exist ()) ;
		if (mTree->mOperand.exist ())
			return mTree->mOperand ;
		return mTree->mOperator (mTree.self ,in1 ,in2) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline Expression<RANK2> curry (const ARGV<_ARG1> & ,const ARGV<_ARG2> &) const {
		Expression<RANK2> ret ;
		ret.mTree->mOperator = _XVALUE_<RANK2_LN> ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) {
			auto &r1y = Expression<RANK2>::from (node.mChild[0]) ;
			auto &r2y = _PICK_ (_NULL_<ARGV<_ARG1>> () ,in1 ,in2) ;
			auto &r3y = _PICK_ (_NULL_<ARGV<_ARG2>> () ,in1 ,in2) ;
			return r1y (r2y ,r3y) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		return std::move (ret) ;
	}

	inline Expression<RANK1> operator+ (const Expression<RANK0> &that) const ;

	inline Expression<RANK2> operator+ (const Expression<RANK1> &that) const ;

	inline Expression<RANK3> operator+ (const Expression<RANK2> &that) const ;
} ;

template <>
class Expression<RANK3> :private LexicalTree<Expression<RANK3>> {
private:
	template <class>
	friend class Expression ;

public:
	inline Expression () = default ;

	inline implicit Expression (const Operator &that) : Expression () {
		_DYNAMIC_ASSERT_ (that.rank () == U::EXPRESSION_RANK_TRAITS<RANK3>::TYPE::value) ;
		mTree->mOperator = that ;
	}

	inline Operand operator() (const Operand &in1 ,const Operand &in2 ,const Operand &in3) const {
		_DYNAMIC_ASSERT_ (mTree.exist ()) ;
		if (mTree->mOperand.exist ())
			return mTree->mOperand ;
		return mTree->mOperator (mTree.self ,in1 ,in2 ,in3) ;
	}

	template <class _ARG1 ,class _ARG2 ,class _ARG3>
	inline Expression<RANK3> curry (const ARGV<_ARG1> & ,const ARGV<_ARG2> & ,const ARGV<_ARG3> &) const {
		Expression<RANK3> ret ;
		ret.mTree->mOperator = _XVALUE_<RANK3_LN> ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) {
			auto &r1y = Expression<RANK3>::from (node.mChild[0]) ;
			auto &r2y = _PICK_ (_NULL_<ARGV<_ARG1>> () ,in1 ,in2 ,in3) ;
			auto &r3y = _PICK_ (_NULL_<ARGV<_ARG2>> () ,in1 ,in2 ,in3) ;
			auto &r4y = _PICK_ (_NULL_<ARGV<_ARG3>> () ,in1 ,in2 ,in3) ;
			return r1y (r2y ,r3y ,r4y) ;
		}) ;
		ret.mTree->mChild[0] = (*this) ;
		return std::move (ret) ;
	}

	inline Expression<RANK2> operator+ (const Expression<RANK0> &that) const ;

	inline Expression<RANK3> operator+ (const Expression<RANK1> &that) const ;
} ;

inline Expression<RANK0> Expression<RANK1>::operator+ (const Expression<RANK0> &that) const {
	Expression<RANK0> ret ;
	ret.mTree->mOperator = _XVALUE_<RANK0_LN> ([] (const LexicalNode &node) {
		auto &r1y = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2y = Expression<RANK0>::from (node.mChild[1]) ;
		return r1y (r2y ()) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	return std::move (ret) ;
}

inline Expression<RANK1> Expression<RANK1>::operator+ (const Expression<RANK1> &that) const {
	Expression<RANK1> ret ;
	ret.mTree->mOperator = _XVALUE_<RANK1_LN> ([] (const LexicalNode &node ,const Operand &in1) {
		auto &r1y = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2y = Expression<RANK1>::from (node.mChild[1]) ;
		return r1y (r2y (in1)) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	return std::move (ret) ;
}

inline Expression<RANK2> Expression<RANK1>::operator+ (const Expression<RANK2> &that) const {
	Expression<RANK2> ret ;
	ret.mTree->mOperator = _XVALUE_<RANK2_LN> ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) {
		auto &r1y = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2y = Expression<RANK2>::from (node.mChild[1]) ;
		return r1y (r2y (in1 ,in2)) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	return std::move (ret) ;
}

inline Expression<RANK3> Expression<RANK1>::operator+ (const Expression<RANK3> &that) const {
	Expression<RANK3> ret ;
	ret.mTree->mOperator = _XVALUE_<RANK3_LN> ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) {
		auto &r1y = Expression<RANK1>::from (node.mChild[0]) ;
		auto &r2y = Expression<RANK3>::from (node.mChild[1]) ;
		return r1y (r2y (in1 ,in2 ,in3)) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	return std::move (ret) ;
}

inline Expression<RANK1> Expression<RANK2>::operator+ (const Expression<RANK0> &that) const {
	Expression<RANK1> ret ;
	ret.mTree->mOperator = _XVALUE_<RANK1_LN> ([] (const LexicalNode &node ,const Operand &in1) {
		auto &r1y = Expression<RANK2>::from (node.mChild[0]) ;
		auto &r2y = Expression<RANK0>::from (node.mChild[1]) ;
		return r1y (r2y () ,in1) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	return std::move (ret) ;
}

inline Expression<RANK2> Expression<RANK2>::operator+ (const Expression<RANK1> &that) const {
	Expression<RANK2> ret ;
	ret.mTree->mOperator = _XVALUE_<RANK2_LN> ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) {
		auto &r1y = Expression<RANK2>::from (node.mChild[0]) ;
		auto &r2y = Expression<RANK1>::from (node.mChild[1]) ;
		return r1y (r2y (in1) ,in2) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	return std::move (ret) ;
}

inline Expression<RANK3> Expression<RANK2>::operator+ (const Expression<RANK2> &that) const {
	Expression<RANK3> ret ;
	ret.mTree->mOperator = _XVALUE_<RANK3_LN> ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) {
		auto &r1y = Expression<RANK2>::from (node.mChild[0]) ;
		auto &r2y = Expression<RANK2>::from (node.mChild[1]) ;
		return r1y (r2y (in1 ,in2) ,in3) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	return std::move (ret) ;
}

inline Expression<RANK2> Expression<RANK3>::operator+ (const Expression<RANK0> &that) const {
	Expression<RANK2> ret ;
	ret.mTree->mOperator = _XVALUE_<RANK2_LN> ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2) {
		auto &r1y = Expression<RANK3>::from (node.mChild[0]) ;
		auto &r2y = Expression<RANK0>::from (node.mChild[1]) ;
		return r1y (r2y () ,in1 ,in2) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	return std::move (ret) ;
}

inline Expression<RANK3> Expression<RANK3>::operator+ (const Expression<RANK1> &that) const {
	Expression<RANK3> ret ;
	ret.mTree->mOperator = _XVALUE_<RANK3_LN> ([] (const LexicalNode &node ,const Operand &in1 ,const Operand &in2 ,const Operand &in3) {
		auto &r1y = Expression<RANK3>::from (node.mChild[0]) ;
		auto &r2y = Expression<RANK1>::from (node.mChild[1]) ;
		return r1y (r2y (in1) ,in2 ,in3) ;
	}) ;
	ret.mTree->mChild[0] = (*this) ;
	ret.mTree->mChild[1] = that ;
	return std::move (ret) ;
}
} ;
} ;