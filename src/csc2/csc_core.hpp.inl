#pragma once

#include "csc.hpp"
#include "csc_core.hpp"

namespace CSC {
namespace U {
template <class...>
trait AUTO_PUREHOLDER_HELP ;

template <class BASE ,class UNIT1>
trait AUTO_PUREHOLDER_HELP<BASE ,UNIT1 ,ALWAYS> {
	using Holder = typename AUTO_HELP<ALWAYS>::template AutoHolder<BASE> ;

	class PureHolder :public Holder {
	private:
		UNIT1 mValue ;

	public:
		implicit PureHolder () = delete ;

		explicit PureHolder (RREF<UNIT1> that) {
			mValue = move (that) ;
		}

		void destroy () override {
			auto &&thiz = *this ;
			//@mark
		}

		LENGTH type_cabi () const override {
			return operator_cabi (TYPEAS<UNIT1>::id) ;
		}
	} ;
} ;
} ;

namespace U {
template <class...>
trait SLICE_PUREHOLDER_HELP ;

template <class BASE ,class UNIT1 ,class SIZE>
trait SLICE_PUREHOLDER_HELP<BASE ,UNIT1 ,SIZE ,ALWAYS> {
	using Holder = typename SLICE_HELP<UNIT1 ,ALWAYS>::template SliceHolder<BASE> ;

	class PureHolder :public Holder {
	private:
		DEF<UNIT1[SIZE::value]> mSlice ;

	public:
		implicit PureHolder () = delete ;

		LENGTH size () const override {
			return SIZE::value ;
		}

		LENGTH addr () const override {
			return address (mSlice) ;
		}

		UNIT1 get (CREF<INDEX> index) const override {
			return mSlice[index] ;
		}
	} ;
} ;
} ;
} ;