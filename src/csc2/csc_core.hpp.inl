#pragma once

#include "csc.hpp"
#include "csc_core.hpp"

namespace CSC {
namespace U {
template <class...>
trait AUTO_PUREHOLDER_HELP ;

template <class BASE ,class UNIT1>
trait AUTO_PUREHOLDER_HELP<BASE ,UNIT1> :public AUTO_HELP<void ,void> {
	class PureHolder :public AutoHolder<BASE> {
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
trait BOX_PUREHOLDER_HELP ;

template <class BASE ,class UNIT1 ,class UNIT2>
trait BOX_PUREHOLDER_HELP<BASE ,UNIT1 ,UNIT2> :public BOX_HELP<UNIT1 ,REQUIRE<IS_INTERFACE<UNIT1>>> {
	class PureHolder :public BoxHolder<BASE> {
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

template <class BASE ,class UNIT1>
trait RC_PUREHOLDER_HELP<BASE ,UNIT1> :public RC_HELP<UNIT1 ,void> {
	class PureHolder :public RCHolder<BASE> {
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

template <class BASE ,class UNIT1 ,class SIZE>
trait SLICE_PUREHOLDER_HELP<BASE ,UNIT1 ,SIZE> :public SLICE_HELP<UNIT1 ,void> {
	class PureHolder :public SliceHolder<BASE> {
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
	class PureHolder :public ClazzHolder<BASE> {
	public:
		implicit PureHolder () = default ;

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