#pragma once

#ifndef __CSC_DATABASE__
#error "��(�á㧥�� ;)�� : require 'csc_database.hpp'"
#endif

#ifdef __CSC__
#pragma push_macro ("self")
#pragma push_macro ("implicit")
#pragma push_macro ("side_effects")
#pragma push_macro ("leftvalue")
#pragma push_macro ("rightvalue")
#pragma push_macro ("imports")
#pragma push_macro ("exports")
#pragma push_macro ("switch_once")
#pragma push_macro ("discard")
#undef self
#undef implicit
#undef side_effects
#undef leftvalue
#undef rightvalue
#undef imports
#undef exports
#undef switch_once
#undef discard
#endif

#ifdef __CSC_DEPRECATED__
#include <mysql.h>
#endif

#ifndef _mysql_h
#error "��(�á㧥�� ;)�� : require 'mysql.h'"
#endif

#ifdef __CSC_DEPRECATED__
#ifdef __CSC_COMPILER_MSVC__
#ifndef use_comment_lib_mysql
#ifdef __CSC_DEBUG__
#define use_comment_lib_mysql "libmysqld.lib"
#endif
#endif

#ifndef use_comment_lib_mysql
#ifndef __CSC_DEBUG__
#define use_comment_lib_mysql "libmysql.lib"
#endif
#endif
#pragma comment (lib ,use_comment_lib_mysql)
#undef use_comment_lib_mysql
#endif
#endif

#ifdef __CSC__
#pragma pop_macro ("self")
#pragma pop_macro ("implicit")
#pragma pop_macro ("side_effects")
#pragma pop_macro ("leftvalue")
#pragma pop_macro ("rightvalue")
#pragma pop_macro ("imports")
#pragma pop_macro ("exports")
#pragma pop_macro ("switch_once")
#pragma pop_macro ("discard")
#endif

namespace CSC {
namespace api {
using ::MYSQL ;

using ::mysql_init ;
using ::mysql_close ;
using ::mysql_error ;
} ;

class AbstractDatabase_Engine_MYSQL
	:public AbstractDatabase::Abstract {
private:
	using NATIVE_THIS = UniqueRef<api::MYSQL> ;

public:
	AbstractDatabase_Engine_MYSQL () {
		_STATIC_ASSERT_ (_SIZEOF_ (decltype (DEREF[this])) == _SIZEOF_ (Interface)) ;
		_STATIC_ASSERT_ (_ALIGNOF_ (decltype (DEREF[this])) == _ALIGNOF_ (Interface)) ;
	}

	void compute_load_data (AnyRef<void> &holder) const override {
		auto tmp = UniqueRef<api::MYSQL> ([&] (api::MYSQL &me) {
			api::mysql_init (DEPTR[me]) ;
		} ,[] (api::MYSQL &me) {
			api::mysql_close (DEPTR[me]) ;
		}) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (tmp)) ;
	}

private:
	void compute_check_error (api::MYSQL &self_) const {
		const auto r1x = api::mysql_error (DEPTR[self_]) ;
		_DYNAMIC_ASSERT_ (r1x == NULL) ;
	}
} ;
} ;