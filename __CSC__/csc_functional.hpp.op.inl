#pragma once

#ifndef __CSC_FUNCTIONAL__
#error "б╞(д├бузебу ;)д├ : require 'csc_functional.hpp'"
#endif

namespace CSC {
namespace U {
template <class _ARG1 ,class _ARG2>
struct COMPILE_RETURN {
	using TYPE = REMOVE_CVR_TYPE<RESULT_OF_TYPE<DEF<decltype (&_ARG1::compile)> ,ARGVS<_ARG2 &>>> ;
} ;

template <class _ARG1 ,class _ARG2>
using COMPILE_RETURN_TYPE = typename COMPILE_RETURN<_ARG1 ,_ARG2>::TYPE ;
} ;

template <class...>
struct FUN_equal ;

template <class IN_lhs ,class IN_rhs>
struct FUN_equal<IN_lhs ,IN_rhs> {
	struct CON_return {
		template <class CONTEXT>
		static BOOL compile (CONTEXT &me) {
			return IN_lhs::compile (me) == IN_rhs::compile (me) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_compr ;

template <class IN_lhs ,class IN_rhs>
struct FUN_compr<IN_lhs ,IN_rhs> {
	struct CON_return {
		template <class CONTEXT>
		static FLAG compile (CONTEXT &me) {
			return U::OPERATOR_COMPR::invoke (IN_lhs::compile (me) ,IN_rhs::compile (me)) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_not ;

template <class IN_lhs>
struct FUN_not<IN_lhs> {
	struct CON_return {
		template <class CONTEXT>
		static BOOL compile (CONTEXT &me) {
			return !IN_lhs::compile (me) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_and ;

template <class IN_lhs ,class IN_rhs>
struct FUN_and<IN_lhs ,IN_rhs> {
	struct CON_return {
		template <class CONTEXT>
		static BOOL compile (CONTEXT &me) {
			return IN_lhs::compile (me) && IN_rhs::compile (me) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_band ;

template <class IN_lhs ,class IN_rhs>
struct FUN_band<IN_lhs ,IN_rhs> {
	struct CON_return {
		template <class CONTEXT>
		static U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> compile (CONTEXT &me) {
			const auto r1x = IN_lhs::compile (me) & IN_rhs::compile (me) ;
			return U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> (r1x) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_or ;

template <class IN_lhs ,class IN_rhs>
struct FUN_or<IN_lhs ,IN_rhs> {
	struct CON_return {
		template <class CONTEXT>
		static BOOL compile (CONTEXT &me) {
			return IN_lhs::compile (me) || IN_rhs::compile (me) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_bor ;

template <class IN_lhs ,class IN_rhs>
struct FUN_bor<IN_lhs ,IN_rhs> {
	struct CON_return {
		template <class CONTEXT>
		static U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> compile (CONTEXT &me) {
			const auto r1x = IN_lhs::compile (me) | IN_rhs::compile (me) ;
			return U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> (r1x) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_xor ;

template <class IN_lhs ,class IN_rhs>
struct FUN_xor<IN_lhs ,IN_rhs> {
	struct CON_return {
		template <class CONTEXT>
		static BOOL compile (CONTEXT &me) {
			return IN_lhs::compile (me) != IN_rhs::compile (me) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_bxor ;

template <class IN_lhs ,class IN_rhs>
struct FUN_bxor<IN_lhs ,IN_rhs> {
	struct CON_return {
		template <class CONTEXT>
		static U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> compile (CONTEXT &me) {
			const auto r1x = IN_lhs::compile (me) ^ IN_rhs::compile (me) ;
			return U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> (r1x) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_plus ;

template <class IN_lhs>
struct FUN_plus<IN_lhs> {
	struct CON_return {
		template <class CONTEXT>
		static U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> compile (CONTEXT &me) {
			return +IN_lhs::compile (me) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_minus ;

template <class IN_lhs>
struct FUN_minus<IN_lhs> {
	struct CON_return {
		template <class CONTEXT>
		static U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> compile (CONTEXT &me) {
			return -IN_lhs::compile (me) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_increase ;

template <class IN_lhs>
struct FUN_increase<IN_lhs> {
	struct CON_return {
		template <class CONTEXT>
		static U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> compile (CONTEXT &me) {
			U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> ret = IN_lhs::compile (me) ;
			++ret ;
			return _MOVE_ (ret) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_decrease ;

template <class IN_lhs>
struct FUN_decrease<IN_lhs> {
	struct CON_return {
		template <class CONTEXT>
		static U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> compile (CONTEXT &me) {
			U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> ret = IN_lhs::compile (me) ;
			--ret ;
			return _MOVE_ (ret) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_add ;

template <class IN_lhs ,class IN_rhs>
struct FUN_add<IN_lhs ,IN_rhs> {
	struct CON_return {
		template <class CONTEXT>
		static U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> compile (CONTEXT &me) {
			return IN_lhs::compile (me) + IN_rhs::compile (me) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_sub ;

template <class IN_lhs ,class IN_rhs>
struct FUN_sub<IN_lhs ,IN_rhs> {
	struct CON_return {
		template <class CONTEXT>
		static U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> compile (CONTEXT &me) {
			return IN_lhs::compile (me) - IN_rhs::compile (me) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_mul ;

template <class IN_lhs ,class IN_rhs>
struct FUN_mul<IN_lhs ,IN_rhs> {
	struct CON_return {
		template <class CONTEXT>
		static U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> compile (CONTEXT &me) {
			return IN_lhs::compile (me) * IN_rhs::compile (me) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_div ;

template <class IN_lhs ,class IN_rhs>
struct FUN_div<IN_lhs ,IN_rhs> {
	struct CON_return {
		template <class CONTEXT>
		static U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> compile (CONTEXT &me) {
			return IN_lhs::compile (me) / IN_rhs::compile (me) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_mod ;

template <class IN_lhs ,class IN_rhs>
struct FUN_mod<IN_lhs ,IN_rhs> {
	struct CON_return {
		template <class CONTEXT>
		static U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> compile (CONTEXT &me) {
			return IN_lhs::compile (me) % IN_rhs::compile (me) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_cross ;

template <class IN_lhs ,class IN_rhs>
struct FUN_cross<IN_lhs ,IN_rhs> {
	struct CON_return {
		template <class CONTEXT>
		static U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> compile (CONTEXT &me) {
			return IN_lhs::compile (me) ^ IN_rhs::compile (me) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class... IN_lhs>
struct FUN_tuple {
	struct CON_return {
		using TYPE = ARGVS<IN_lhs...> ;
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_tuple_pick ;

template <class IN_tuple ,class IN_id>
struct FUN_tuple_pick<IN_tuple ,IN_id> {
	using tuple_argvs = typename IN_tuple::TYPE ;

	using TYPE = INDEX_TO_TYPE<IN_id ,tuple_argvs> ;
} ;

template <class...>
struct FUN_get ;

template <class IN_lhs ,class IN_rhs>
struct FUN_get<IN_lhs ,IN_rhs> {
	struct CON_return {
		template <class CONTEXT ,class _DEP = NONE>
		static auto compile (CONTEXT &me)
			->DEPENDENT_TYPE<DEF<decltype (_NULL_<U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT>> ()[_NULL_<U::COMPILE_RETURN_TYPE<IN_rhs ,CONTEXT>> ()])> ,_DEP> {
			return IN_lhs::compile (me)[IN_rhs::compile (me)] ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_assign ;

template <class IN_lhs ,class IN_rhs>
struct FUN_assign<IN_lhs ,IN_rhs> {
	struct CON_return {
		template <class CONTEXT>
		static U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT> compile (CONTEXT &me) {
			_STATIC_ASSERT_ (stl::is_lvalue_reference<U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT>>::value) ;
			return IN_lhs::compile (me) = IN_rhs::compile (me) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_call ;

template <class IN_lhs ,class... IN_rhs>
struct FUN_call<IN_lhs ,IN_rhs...> {
	struct CON_return {
		template <class CONTEXT ,class _DEP = NONE>
		static auto compile (CONTEXT &me)
			->DEPENDENT_TYPE<RESULT_OF_TYPE<DEF<decltype (&U::COMPILE_RETURN_TYPE<IN_lhs ,CONTEXT>::operator())> ,ARGVS<U::COMPILE_RETURN_TYPE<IN_rhs ,CONTEXT>...>> ,_DEP> {
			return IN_lhs::compile (me) (IN_rhs::compile (me)...) ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_assert ;

template <class IN_lhs>
struct FUN_assert<IN_lhs> {
	struct CON_return {
		template <class CONTEXT>
		static BOOL compile (CONTEXT &me) {
			_DYNAMIC_ASSERT_ (IN_lhs::compile (me)) ;
			return TRUE ;
		}
	} ;

	using TYPE = CON_return ;
} ;

template <class...>
struct FUN_switch ;

template <class IN_lhs ,class IN_rhs1 ,class IN_rhs2>
struct FUN_switch<IN_lhs ,IN_rhs1 ,IN_rhs2> {
	struct CON_return {
		template <class CONTEXT>
		static U::COMPILE_RETURN_TYPE<IN_rhs1 ,CONTEXT> compile (CONTEXT &me) {
			if (IN_lhs::compile (me))
				return IN_rhs1::compile (me) ;
			return IN_rhs2::compile (me) ;
		}
	} ;

	using TYPE = CON_return ;
} ;
} ;