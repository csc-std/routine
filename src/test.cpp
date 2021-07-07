#include "util.h"

using namespace CSC ;

struct Dynamic {
	PTR<CREF<MakerHolder>> mMaker ;

	implicit Dynamic () = delete ;
	implicit ~Dynamic () = delete ;
	implicit Dynamic (CREF<Dynamic>) = delete ;
	inline void operator= (CREF<Dynamic>) = delete ;
	implicit Dynamic (RREF<Dynamic>) = delete ;
	inline void operator= (RREF<Dynamic>) = delete ;

	void create (CREF<PTR<CREF<MakerHolder>>> maker) {
		auto &&thiz = *this ;
		assert (mMaker == NULL) ;
		mMaker = maker ;
		assert (mMaker != NULL) ;
		const auto r1x = address (thiz) + SIZE_OF<Dynamic>::value ;
		const auto r2x = alignto (r1x ,mMaker->type_align ()) ;
		mMaker->friend_create (unsafe_pointer (r2x)) ;
	}

	void destroy () {
		auto &&thiz = *this ;
		if (mMaker == NULL)
			return ;
		const auto r1x = address (thiz) + SIZE_OF<Dynamic>::value ;
		const auto r2x = alignto (r1x ,mMaker->type_align ()) ;
		mMaker->friend_destroy (unsafe_pointer (r2x)) ;
		mMaker = NULL ;
	}

	VREF<TEMP<void>> at () leftvalue {
		auto &&thiz = *this ;
		const auto r1x = address (thiz) + SIZE_OF<Dynamic>::value ;
		const auto r2x = alignto (r1x ,mMaker->type_align ()) + mMaker->type_offset () ;
		return unsafe_pointer (r2x) ;
	}

	CREF<TEMP<void>> at () const leftvalue {
		auto &&thiz = *this ;
		const auto r1x = address (thiz) + SIZE_OF<Dynamic>::value ;
		const auto r2x = alignto (r1x ,mMaker->type_align ()) + mMaker->type_offset () ;
		return unsafe_pointer (r2x) ;
	}
} ;