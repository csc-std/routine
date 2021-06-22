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
} ;