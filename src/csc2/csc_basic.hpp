#pragma once

#ifndef __CSC_BASIC__
#define __CSC_BASIC__
#endif

#include "csc.hpp"
#include "csc_core.hpp"

namespace CSC {
namespace U {
template <class...>
trait TUPLE_HELP ;

template <class ARG1>
trait TUPLE_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_ZERO<COUNTOF<ARG1>>) ;

	class Tuple ;
} ;

template <class UNIT1>
class TUPLE_HELP<UNIT1 ,REQUIRE<ENUM_EQ_ZERO<COUNTOF<UNIT1>>>>::Tuple {
public:
	implicit Tuple () = default ;

	LENGTH capacity () const {
		return COUNTOF<UNIT1>::value ;
	}

	BOOL equal (const Tuple &that) const {
		return TRUE ;
	}

	inline BOOL operator== (const Tuple &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const Tuple &that) const {
		return !equal (that) ;
	}

	FLAG compr (const Tuple &that) const {
		return ZERO ;
	}

	inline BOOL operator< (const Tuple &that) const {
		return compr (that) < ZERO ;
	}

	inline BOOL operator<= (const Tuple &that) const {
		return compr (that) <= ZERO ;
	}

	inline BOOL operator> (const Tuple &that) const {
		return compr (that) > ZERO ;
	}

	inline BOOL operator>= (const Tuple &that) const {
		return compr (that) >= ZERO ;
	}

	FLAG hash () const {
		return hashcode () ;
	}
} ;

template <class ARG1>
trait TUPLE_HELP<ARG1 ,REQUIRE<ENUM_GT_ZERO<COUNTOF<ARG1>>>> {
	require (ENUM_GT_ZERO<COUNTOF<ARG1>>) ;

	using FIRST_ONE = TYPE_FIRST_ONE<ARG1> ;
	using FIRST_REST = TYPE_FIRST_REST<ARG1> ;
	using BASE = typename TUPLE_HELP<FIRST_REST ,void>::Tuple ;

	class Tuple ;
} ;

template <class UNIT1>
class TUPLE_HELP<UNIT1 ,REQUIRE<ENUM_GT_ZERO<COUNTOF<UNIT1>>>>::Tuple :
	delegate public BASE {
private:
	FIRST_ONE mValue ;

public:
	implicit Tuple () = default ;

	template <class ARG1 ,class...ARGS ,class = ENABLE<IS_SAME<FIRST_ONE ,REMOVE_CVR<ARG1>>>>
	explicit Tuple (DEF<ARG1 &> ,DEF<ARGS &&>...) = delete ;

	template <class ARG1 ,class...ARGS ,class = ENABLE<IS_SAME<FIRST_ONE ,REMOVE_CVR<ARG1>>>>
	explicit Tuple (DEF<ARG1 &&> one_ ,DEF<ARGS &&>...rest_) :
		delegate BASE (forward (rest_)...) ,
		delegate mValue (forward (one_)) {}

	LENGTH capacity () const {
		return COUNTOF<UNIT1>::value ;
	}

	VREF<FIRST_ONE> one[[nodiscard]] () {
		return mValue ;
	}

	CREF<FIRST_ONE> one[[nodiscard]] () const {
		return mValue ;
	}

	VREF<BASE> rest[[nodiscard]] () {
		return m_super () ;
	}

	CREF<BASE> rest[[nodiscard]] () const {
		return m_super () ;
	}

	template <class ARG1>
	VREF<TYPE_PICK<UNIT1 ,REMOVE_CVR<ARG1>>> pick[[nodiscard]] (CREF<ARG1> nth) {
		using R1X = typeof (nth) ;
		return template_pick (typeas<R1X>::id ,PHX) ;
	}

	template <class ARG1>
	CREF<TYPE_PICK<UNIT1 ,REMOVE_CVR<ARG1>>> pick[[nodiscard]] (CREF<ARG1> nth) const {
		using R1X = typeof (nth) ;
		return template_pick (typeas<R1X>::id ,PHX) ;
	}

	BOOL equal (const Tuple &that) const {
		if (mValue != that.mValue)
			return FALSE ;
		if (m_super () != that.m_super ())
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const Tuple &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const Tuple &that) const {
		return !equal (that) ;
	}

	FLAG compr (const Tuple &that) const {
		const auto r1x = op_compr (mValue ,that.mValue) ;
		if (r1x != ZERO)
			return r1x ;
		const auto r2x = op_compr (m_super () ,that.m_super ()) ;
		if (r2x != ZERO)
			return r2x ;
		return ZERO ;
	}

	inline BOOL operator< (const Tuple &that) const {
		return compr (that) < ZERO ;
	}

	inline BOOL operator<= (const Tuple &that) const {
		return compr (that) <= ZERO ;
	}

	inline BOOL operator> (const Tuple &that) const {
		return compr (that) > ZERO ;
	}

	inline BOOL operator>= (const Tuple &that) const {
		return compr (that) >= ZERO ;
	}

	FLAG hash () const {
		const auto r1x = op_hash (mValue) ;
		const auto r2x = op_hash (m_super ()) ;
		return hashcode (r1x ,r2x) ;
	}

private:
	VREF<BASE> m_super[[nodiscard]] () {
		auto &thix = (*this) ;
		return static_cast<VREF<BASE>> (thix) ;
	}

	CREF<BASE> m_super[[nodiscard]] () const {
		auto &thix = (*this) ;
		return static_cast<CREF<BASE>> (thix) ;
	}

	template <class ARG1 ,class = ENABLE<ENUM_EQ_ZERO<REMOVE_CVR<ARG1>>>>
	VREF<FIRST_ONE> template_pick[[nodiscard]] (CREF<ARG1> nth ,CREF<typeof (PH1)>) {
		return one () ;
	}

	template <class ARG1 ,class = ENABLE<ENUM_EQ_ZERO<REMOVE_CVR<ARG1>>>>
	CREF<FIRST_ONE> template_pick[[nodiscard]] (CREF<ARG1> nth ,CREF<typeof (PH1)>) const {
		return one () ;
	}

	template <class ARG1 ,class = ENABLE<ENUM_GT_ZERO<REMOVE_CVR<ARG1>>>>
	VREF<TYPE_PICK<UNIT1 ,REMOVE_CVR<ARG1>>> template_pick[[nodiscard]] (CREF<ARG1> nth ,CREF<typeof (PH2)>) {
		using R1X = typeof (nth) ;
		using R2X = ENUM_DEC<REMOVE_CVR<R1X>> ;
		return rest ().template_pick (typeas<R2X>::id ,PHX) ;
	}

	template <class ARG1 ,class = ENABLE<ENUM_GT_ZERO<REMOVE_CVR<ARG1>>>>
	CREF<TYPE_PICK<UNIT1 ,REMOVE_CVR<ARG1>>> template_pick[[nodiscard]] (CREF<ARG1> nth ,CREF<typeof (PH2)>) const {
		using R1X = typeof (nth) ;
		using R2X = ENUM_DEC<REMOVE_CVR<R1X>> ;
		return rest ().template_pick (typeas<R2X>::id ,PHX) ;
	}
} ;
} ;

template <class...UNITS>
using Tuple = typename U::TUPLE_HELP<typeas<UNITS...> ,void>::Tuple ;

namespace U {
template <class...>
trait VARIANT_HELP ;

template <class ARG1>
trait VARIANT_HELP<ARG1 ,REQUIRE<ENUM_EQ_IDEN<COUNTOF<ARG1>>>> {
	require (ENUM_EQ_IDEN<COUNTOF<ARG1>>) ;

	struct EXTERN {
		interface Holder ;
	} ;

	class Variant ;
} ;

template <class UNIT1>
interface VARIANT_HELP<UNIT1 ,REQUIRE<ENUM_EQ_IDEN<COUNTOF<UNIT1>>>>::EXTERN::Holder {
	virtual void test () = 0 ;
} ;

template <class...>
trait IMPLHOLDER_HELP ;

template <class ARG1 ,class ARG2>
trait IMPLHOLDER_HELP<ARG1 ,ARG2> {
	using Holder = typename VARIANT_HELP<ARG1 ,REQUIRE<ENUM_EQ_IDEN<COUNTOF<ARG1>>>>::EXTERN::Holder ;

	class ImplHolder ;
} ;

template <class UNIT1>
class VARIANT_HELP<UNIT1 ,REQUIRE<ENUM_EQ_IDEN<COUNTOF<UNIT1>>>>::Variant {
private:
	using Holder = typename VARIANT_HELP<UNIT1 ,REQUIRE<ENUM_EQ_IDEN<COUNTOF<UNIT1>>>>::EXTERN::Holder ;

private:

} ;

template <class UNIT1 ,class UNIT2>
class IMPLHOLDER_HELP<UNIT1 ,UNIT2>::ImplHolder :
	delegate public Holder {
public:
	void test () override {

	}
} ;

template <class ARG1>
trait VARIANT_HELP<ARG1 ,REQUIRE<ENUM_GT_IDEN<COUNTOF<ARG1>>>> {

	class Variant ;
} ;

template <class UNIT1>
class VARIANT_HELP<UNIT1 ,REQUIRE<ENUM_GT_IDEN<COUNTOF<UNIT1>>>>::Variant {
private:
	using Holder = typename VARIANT_HELP<UNIT1 ,REQUIRE<ENUM_GT_IDEN<COUNTOF<UNIT1>>>>::EXTERN::Holder ;

private:

} ;
} ;

template <class UNIT1>
using Optional = typename U::VARIANT_HELP<typeas<UNIT1> ,void>::Variant ;

template <class...UNITS>
using Variant = typename U::VARIANT_HELP<typeas<UNITS...> ,void>::Variant ;
} ;