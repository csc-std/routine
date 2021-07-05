#pragma once

#include "csc.hpp"
#include "csc_core.hpp"

namespace CSC {
namespace U {
template <class...>
trait FUNCTION_barrier_IMPLHOLDER_HELP ;

template <class UNIT1>
trait FUNCTION_barrier_IMPLHOLDER_HELP<UNIT1 ,REQUIRE<MACRO_COMPILER_MSVC<UNIT1>>> {
	using Holder = typename FUNCTION_barrier_HELP<ALWAYS>::FUNCTION_barrier::Holder ;

	class ImplHolder :public Holder {
	public:
		void barrier () const override {
			noop () ;
		}
	} ;
} ;

template <class UNIT1>
trait FUNCTION_barrier_IMPLHOLDER_HELP<UNIT1 ,REQUIRE<MACRO_COMPILER_GNUC<UNIT1>>> {
	using Holder = typename FUNCTION_barrier_HELP<ALWAYS>::FUNCTION_barrier::Holder ;

	class ImplHolder :public Holder {
	public:
		void barrier () const override {
#ifdef __CSC_COMPILER_GNUC__
			asm volatile ("" ::: "memory") ;
#endif
		}
	} ;
} ;

template <class UNIT1>
trait FUNCTION_barrier_IMPLHOLDER_HELP<UNIT1 ,REQUIRE<MACRO_COMPILER_CLANG<UNIT1>>> {
	using Holder = typename FUNCTION_barrier_HELP<ALWAYS>::FUNCTION_barrier::Holder ;

	class ImplHolder :public Holder {
	public:
		void barrier () const override {
#ifdef __CSC_COMPILER_GNUC__
			asm volatile ("" ::: "memory") ;
#endif
		}
	} ;
} ;

exports CREF<typename FUNCTION_barrier_HELP<ALWAYS>::FUNCTION_barrier::Holder> FUNCTION_barrier_HELP<ALWAYS>::
FUNCTION_barrier::extern_invoke () {
	using R1X = typename FUNCTION_barrier_IMPLHOLDER_HELP<void ,ALWAYS>::ImplHolder ;
	static R1X tmp ;
	return tmp ;
}
} ;

namespace U {
template <class...>
trait FUNCTION_launder_IMPLHOLDER_HELP ;

template <>
trait FUNCTION_launder_IMPLHOLDER_HELP<ALWAYS> {
	using Holder = typename FUNCTION_launder_HELP<ALWAYS>::FUNCTION_launder::Holder ;

	class ImplHolder :public Holder {
	public:
		void launder (CREF<LENGTH> addr) const override {
			noop () ;
		}
	} ;
} ;

exports CREF<typename FUNCTION_launder_HELP<ALWAYS>::FUNCTION_launder::Holder> FUNCTION_launder_HELP<ALWAYS>::
FUNCTION_launder::extern_invoke () {
	using R1X = typename FUNCTION_launder_IMPLHOLDER_HELP<ALWAYS>::ImplHolder ;
	static R1X tmp ;
	return tmp ;
}
} ;

namespace U {
template <class...>
trait FUNCTION_debug_break_IMPLHOLDER_HELP ;

template <class UNIT1>
trait FUNCTION_debug_break_IMPLHOLDER_HELP<UNIT1 ,REQUIRE<MACRO_COMPILER_MSVC<UNIT1>>> {
	using Holder = typename FUNCTION_debug_break_HELP<ALWAYS>::FUNCTION_debug_break::Holder ;

	class ImplHolder :public Holder {
	public:
		void debug_break () const override {
#ifdef __CSC_COMPILER_MSVC__
			__debugbreak () ;
#endif
		}
	} ;
} ;

template <class UNIT1>
trait FUNCTION_debug_break_IMPLHOLDER_HELP<UNIT1 ,REQUIRE<MACRO_COMPILER_GNUC<UNIT1>>> {
	using Holder = typename FUNCTION_debug_break_HELP<ALWAYS>::FUNCTION_debug_break::Holder ;

	class ImplHolder :public Holder {
	public:
		void debug_break () const override {
#ifdef __CSC_COMPILER_GUNC__
			__builtin_trap () ;
#endif
		}
	} ;
} ;

template <class UNIT1>
trait FUNCTION_debug_break_IMPLHOLDER_HELP<UNIT1 ,REQUIRE<MACRO_COMPILER_CLANG<UNIT1>>> {
	using Holder = typename FUNCTION_debug_break_HELP<ALWAYS>::FUNCTION_debug_break::Holder ;

	class ImplHolder :public Holder {
	public:
		void debug_break () const override {
			std::abort () ;
		}
	} ;
} ;

exports CREF<typename FUNCTION_debug_break_HELP<ALWAYS>::FUNCTION_debug_break::Holder> FUNCTION_debug_break_HELP<ALWAYS>::
FUNCTION_debug_break::extern_invoke () {
	using R1X = typename FUNCTION_debug_break_IMPLHOLDER_HELP<void ,ALWAYS>::ImplHolder ;
	static R1X tmp ;
	return tmp ;
}
} ;
} ;