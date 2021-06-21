#pragma once

#include "csc.hpp"
#include "csc_core.hpp"

namespace CSC {
namespace U {
template <class...>
trait AUTO_PUREHOLDER_HELP ;

template <class UNIT1 ,class BASE>
trait AUTO_PUREHOLDER_HELP<UNIT1 ,BASE> :public AUTO_HELP<void ,void> {
	class PureHolder :public AutoCRTP<BASE>::Holder {
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

		void addr_swap (CREF<LENGTH> addr_) override {
			const auto r1x = reinterpret_cast<PTR<UNIT1>> (addr_) ;
			assert (r1x != NULL) ;
			swap (mValue ,(*r1x)) ;
			barrier () ;
		}
	} ;
} ;
} ;

namespace U {
template <class...>
trait BOX_PUREHOLDER_HELP ;

template <class UNIT1 ,class UNIT2 ,class BASE>
trait BOX_PUREHOLDER_HELP<UNIT1 ,UNIT2 ,BASE> :public BOX_HELP<UNIT1 ,void> {
	class PureHolder :public BoxCRTP<BASE>::Holder {
	private:
		UNIT2 mValue ;

	public:
		implicit PureHolder () = delete ;

		explicit PureHolder (RREF<UNIT2> that) {
			mValue = move (that) ;
		}

		void destroy () override {
			auto &&thiz = *this ;
			//@mark
		}

		CREF<UNIT1> at () const override {
			return mValue ;
		}
	} ;
} ;
} ;

namespace U {
template <class...>
trait RC_PUREHOLDER_HELP ;

template <class UNIT1 ,class BASE>
trait RC_PUREHOLDER_HELP<UNIT1 ,BASE> :public RC_HELP<UNIT1 ,void> {
	class PureHolder :public RCCRTP<BASE>::Holder {
	private:
		UNIT1 mValue ;
		LENGTH mCounter ;

	public:
		implicit PureHolder () = delete ;

		explicit PureHolder (RREF<UNIT1> that) {
			mValue = move (that) ;
			mCounter = 0 ;
		}

		void destroy () override {
			auto &&thiz = *this ;
			//@mark
		}

		LENGTH increase () override {
			mCounter = mCounter + 1 ;
			return mCounter ;
		}

		LENGTH decrease () override {
			mCounter = mCounter - 1 ;
			return mCounter ;
		}

		CREF<UNIT1> at () const override {
			return mValue ;
		}
	} ;
} ;
} ;

namespace U {
template <class...>
trait SLICE_PUREHOLDER_HELP ;

template <class UNIT1 ,class SIZE ,class BASE>
trait SLICE_PUREHOLDER_HELP<UNIT1 ,SIZE ,BASE> :public SLICE_HELP<UNIT1 ,void> {
	class PureHolder :public SliceCRTP<BASE>::Holder {
	private:
		using Holder = typename SliceCRTP<BASE>::Holder ;

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

		Auto friend_clone () const override {
			//@mark
		}
	} ;
} ;
} ;

namespace U {
template <class...>
trait CLAZZ_PUREHOLDER_HELP ;

template <class BASE ,class UUID>
trait CLAZZ_PUREHOLDER_HELP<BASE ,UUID> :public CLAZZ_HELP<void ,void> {
	class PureHolder :public ClazzCRTP<BASE>::Holder {
	private:
		using Holder = typename ClazzCRTP<BASE>::Holder ;

	public:
		implicit PureHolder () = delete ;

		LENGTH type_size () const override {
			return SIZE_OF<UUID>::value ;
		}

		LENGTH type_align () const override {
			return ALIGN_OF<UUID>::value ;
		}

		FLAG type_cabi () const override {
			return operator_cabi (TYPEAS<PureHolder>::id) ;
		}

		Slice<STR> type_name () const override {
			struct PH ;
			return Slice<STR> (TYPEAS<PH>::id ,typeid (UUID).name ()) ;
		}

		Auto friend_clone () const override {
			//@mark
		}
	} ;
} ;
} ;
} ;