#pragma once

#ifndef __CSC_BASIC__
#define __CSC_BASIC__
#endif

#include "csc.hpp"
#include "csc_core.hpp"

namespace CSC {
namespace U {
template <class...>
trait STATUS_HELP ;

template <class ARG1>
trait STATUS_HELP<ARG1> {
	class Status ;
} ;

template <class UNIT1>
class STATUS_HELP<UNIT1>::Status {
private:
	FLAG mStatus ;

public:
	implicit Status () = delete ;

	template <class ARG1>
	explicit Status (CREF<ARG1> id) {
		using R1X = typeof (id) ;
		mStatus = ENUM_CHECK<R1X>::value ;
	}

	template <class ARG1>
	auto cast (CREF<ARG1> id) const
		->REMOVE_ALL<ARG1> {
		using R1X = typeof (id) ;
		return R1X (mStatus) ;
	}

	inline explicit operator FLAG () const {
		return cast (typeas<FLAG>::id) ;
	}

	auto equal (CREF<Status> that) const
		->BOOL {
		return mStatus == that.mStatus ;
	}

	inline auto operator== (CREF<Status> that) const
		->BOOL {
		return equal (that) ;
	}

	inline auto operator!= (CREF<Status> that) const
		->BOOL {
		return equal (that) ;
	}

	auto compr (CREF<Status> that) const
		->FLAG {
		return operator_compr (mStatus ,that.mStatus) ;
	}

	inline auto operator< (CREF<Status> that) const
		->BOOL {
		return compr (that) < ZERO ;
	}

	inline auto operator<= (CREF<Status> that) const
		->BOOL {
		return compr (that) <= ZERO ;
	}

	inline auto operator> (CREF<Status> that) const
		->BOOL {
		return compr (that) > ZERO ;
	}

	inline auto operator>= (CREF<Status> that) const
		->BOOL {
		return compr (that) >= ZERO ;
	}

	auto hash () const
		->FLAG {
		return mStatus ;
	}
} ;
} ;

namespace U {
template <class...>
trait TUPLE_HELP ;

template <class ARG1>
trait TUPLE_HELP<ARG1 ,REQUIRE<ENUM_EQ_ZERO<COUNTOF<ARG1>>>> {
	class Tuple ;
} ;

template <class UNIT1>
class TUPLE_HELP<UNIT1 ,REQUIRE<ENUM_EQ_ZERO<COUNTOF<UNIT1>>>>::Tuple {
public:
	implicit Tuple () = default ;

	auto rank () const
		->LENGTH {
		return COUNTOF<UNIT1>::value ;
	}

	auto equal (CREF<Tuple> that) const
		->BOOL {
		return TRUE ;
	}

	inline auto operator== (CREF<Tuple> that) const
		->BOOL {
		return equal (that) ;
	}

	inline auto operator!= (CREF<Tuple> that) const
		->BOOL {
		return ifnot (equal (that)) ;
	}

	auto compr (CREF<Tuple> that) const
		->FLAG {
		return ZERO ;
	}

	inline auto operator< (CREF<Tuple> that) const
		->BOOL {
		return compr (that) < ZERO ;
	}

	inline auto operator<= (CREF<Tuple> that) const
		->BOOL {
		return compr (that) <= ZERO ;
	}

	inline auto operator> (CREF<Tuple> that) const
		->BOOL {
		return compr (that) > ZERO ;
	}

	inline auto operator>= (CREF<Tuple> that) const
		->BOOL {
		return compr (that) >= ZERO ;
	}

	auto hash () const
		->FLAG {
		return hashcode () ;
	}
} ;

template <class ARG1>
trait TUPLE_HELP<ARG1 ,REQUIRE<ENUM_GT_ZERO<COUNTOF<ARG1>>>> {
	using ALL = TYPE_CHECK<ARG1> ;
	using ONE = TYPE_FIRST_ONE<ALL> ;
	using REST = TYPE_FIRST_REST<ALL> ;
	using BASE = typename TUPLE_HELP<REST ,void>::Tuple ;

	class Tuple ;
} ;

template <class UNIT1>
class TUPLE_HELP<UNIT1 ,REQUIRE<ENUM_GT_ZERO<COUNTOF<UNIT1>>>>::Tuple {
private:
	ONE mValue ;
	BASE mSuper ;

public:
	implicit Tuple () = default ;

	template <class ARG1 ,class...ARGS ,class = ENABLE<IS_SAME<ONE ,REMOVE_ALL<ARG1>>>>
	explicit Tuple (RREF<ARG1> one_ ,RREF<ARGS>...rest_) :
		mValue (forward (one_)) ,
		mSuper (forward (rest_)...) {}

	auto rank () const
		->LENGTH {
		return COUNTOF<ALL>::value ;
	}

	auto one () leftvalue
		->VREF<ONE> {
		return mValue ;
	}

	auto one () const leftvalue
		->CREF<ONE> {
		return mValue ;
	}

	auto rest () leftvalue
		->VREF<BASE> {
		return mSuper ;
	}

	auto rest () const leftvalue
		->CREF<BASE> {
		return mSuper ;
	}

	template <class ARG1>
	auto pick (CREF<ARG1> nth) leftvalue
		->VREF<TYPE_PICK<UNIT1 ,REMOVE_ALL<ARG1>>> {
		using R1X = typeof (nth) ;
		require (ENUM_COMPR_GTEQ<R1X ,ENUM_ZERO>) ;
		require (ENUM_COMPR_LT<R1X ,COUNTOF<ALL>>) ;
		return template_pick (typeas<R1X>::id ,PHX) ;
	}

	template <class ARG1>
	auto pick (CREF<ARG1> nth) const leftvalue
		->CREF<TYPE_PICK<UNIT1 ,REMOVE_ALL<ARG1>>> {
		using R1X = typeof (nth) ;
		require (ENUM_COMPR_GTEQ<R1X ,ENUM_ZERO>) ;
		require (ENUM_COMPR_LT<R1X ,COUNTOF<ALL>>) ;
		return template_pick (typeas<R1X>::id ,PHX) ;
	}

	auto equal (CREF<Tuple> that) const
		->BOOL {
		if (mValue != that.mValue)
			return FALSE ;
		if (mSuper != that.mSuper)
			return FALSE ;
		return TRUE ;
	}

	inline auto operator== (CREF<Tuple> that) const
		->BOOL {
		return equal (that) ;
	}

	inline auto operator!= (CREF<Tuple> that) const
		->BOOL {
		return ifnot (equal (that)) ;
	}

	auto compr (CREF<Tuple> that) const
		->FLAG {
		const auto r1x = operator_compr (mValue ,that.mValue) ;
		if (r1x != ZERO)
			return r1x ;
		const auto r2x = operator_compr (mSuper ,that.mSuper) ;
		if (r2x != ZERO)
			return r2x ;
		return ZERO ;
	}

	inline auto operator< (CREF<Tuple> that) const
		->BOOL {
		return compr (that) < ZERO ;
	}

	inline auto operator<= (CREF<Tuple> that) const
		->BOOL {
		return compr (that) <= ZERO ;
	}

	inline auto operator> (CREF<Tuple> that) const
		->BOOL {
		return compr (that) > ZERO ;
	}

	inline auto operator>= (CREF<Tuple> that) const
		->BOOL {
		return compr (that) >= ZERO ;
	}

	auto hash () const
		->FLAG {
		const auto r1x = operator_hash (mValue) ;
		const auto r2x = operator_hash (mSuper) ;
		return hashcode (r1x ,r2x) ;
	}

private:
	template <class ARG1 ,class = ENABLE<ENUM_EQ_ZERO<REMOVE_ALL<ARG1>>>>
	auto template_pick (CREF<ARG1> nth ,CREF<typeof (PH1)>) leftvalue
		->VREF<ONE> {
		return one () ;
	}

	template <class ARG1 ,class = ENABLE<ENUM_EQ_ZERO<REMOVE_ALL<ARG1>>>>
	auto template_pick (CREF<ARG1> nth ,CREF<typeof (PH1)>) const leftvalue
		->CREF<ONE> {
		return one () ;
	}

	template <class ARG1 ,class = ENABLE<ENUM_GT_ZERO<REMOVE_ALL<ARG1>>>>
	auto template_pick (CREF<ARG1> nth ,CREF<typeof (PH2)>) leftvalue
		->VREF<TYPE_PICK<UNIT1 ,REMOVE_ALL<ARG1>>> {
		using R1X = typeof (nth) ;
		using R2X = ENUM_DEC<REMOVE_ALL<R1X>> ;
		return rest ().template_pick (typeas<R2X>::id ,PHX) ;
	}

	template <class ARG1 ,class = ENABLE<ENUM_GT_ZERO<REMOVE_ALL<ARG1>>>>
	auto template_pick (CREF<ARG1> nth ,CREF<typeof (PH2)>) const leftvalue
		->CREF<TYPE_PICK<UNIT1 ,REMOVE_ALL<ARG1>>> {
		using R1X = typeof (nth) ;
		using R2X = ENUM_DEC<REMOVE_ALL<R1X>> ;
		return rest ().template_pick (typeas<R2X>::id ,PHX) ;
	}
} ;
} ;

template <class...UNITS>
using Tuple = typename U::TUPLE_HELP<typeas<UNITS...> ,void>::Tuple ;
} ;