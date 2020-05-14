#pragma once

#ifndef __CSC_STRING__
#error "∑(っ°Д° ;)っ : require 'csc_string.hpp'"
#endif

#ifdef __CSC__
#pragma push_macro ("self")
#pragma push_macro ("implicit")
#pragma push_macro ("popping")
#pragma push_macro ("leftvalue")
#pragma push_macro ("rightvalue")
#pragma push_macro ("imports")
#pragma push_macro ("exports")
#pragma push_macro ("switch_case")
#pragma push_macro ("discard")
#undef self
#undef implicit
#undef popping
#undef leftvalue
#undef rightvalue
#undef imports
#undef exports
#undef switch_case
#undef discard
#endif

#ifdef __CSC_DEPRECATED__
#include <cstdlib>
#include <clocale>
#include <ctime>
#include <chrono>
#include <string>
#include <regex>
#endif

#ifdef __CSC__
#pragma pop_macro ("self")
#pragma pop_macro ("implicit")
#pragma pop_macro ("popping")
#pragma pop_macro ("leftvalue")
#pragma pop_macro ("rightvalue")
#pragma pop_macro ("imports")
#pragma pop_macro ("exports")
#pragma pop_macro ("switch_case")
#pragma pop_macro ("discard")
#endif

namespace CSC {
namespace api {
using std::smatch ;
using std::regex ;
using std::string ;

using std::regex_match ;
using std::regex_search ;
using std::regex_replace ;
using std::localtime ;
using std::setlocale ;
using std::mbstowcs ;
using std::wcstombs ;

using ::tm ;
using ::time_t ;

using ::mktime ;

#ifdef __CSC_COMPILER_MSVC__
using ::localtime_s ;
using ::_create_locale ;
using ::_free_locale ;
using ::_mbstowcs_s_l ;
using ::_wcstombs_s_l ;
#endif
} ;

namespace U {
#ifdef __CSC_COMPILER_MSVC__
inline const UniqueRef<_locale_t> &static_locale_page () {
	return _CACHE_ ([&] () {
		return UniqueRef<_locale_t> ([&] (_locale_t &me) {
			me = api::_create_locale (LC_CTYPE ,_PCSTRA_ ("")) ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
		} ,[] (_locale_t &me) {
			api::_free_locale (me) ;
		}) ;
	}) ;
}
#endif

#ifdef __CSC_COMPILER_MSVC__
inline String<STRW> static_locale_cvt_lastows (const String<STRA> &val) {
	auto &r1x = static_locale_page () ;
	String<STRW> ret = String<STRW> (val.length () + 1) ;
	_DEBUG_ASSERT_ (ret.size () < VAR32_MAX) ;
	if switch_case (TRUE) {
		const auto r2x = api::_mbstowcs_s_l (NULL ,ret.raw ().self ,VAR32 (ret.size ()) ,val.raw ().self ,_TRUNCATE ,r1x) ;
		if (r2x == 0)
			discard ;
		ret = String<STRW> () ;
	}
	return _MOVE_ (ret) ;
}
#endif

#ifndef __CSC_COMPILER_MSVC__
inline String<STRW> static_locale_cvt_lastows (const String<STRA> &val) {
	String<STRW> ret = String<STRW> (val.length () + 1) ;
	_DEBUG_ASSERT_ (ret.size () < VAR32_MAX) ;
	if switch_case (TRUE) {
		const auto r3x = api::mbstowcs (ret.raw ().self ,val.raw ().self ,VAR32 (ret.size ())) ;
		if (r3x == 0)
			discard ;
		ret = String<STRW> () ;
	}
	return _MOVE_ (ret) ;
}
#endif

#ifdef __CSC_COMPILER_MSVC__
inline String<STRA> static_locale_cvt_wstolas (const String<STRW> &val) {
	auto &r1x = static_locale_page () ;
	String<STRA> ret = String<STRA> ((val.length () + 1) * _SIZEOF_ (STRW)) ;
	_DEBUG_ASSERT_ (ret.size () < VAR32_MAX) ;
	if switch_case (TRUE) {
		const auto r2x = api::_wcstombs_s_l (NULL ,ret.raw ().self ,VAR32 (ret.size ()) ,val.raw ().self ,_TRUNCATE ,r1x) ;
		if (r2x == 0)
			discard ;
		ret = String<STRA> () ;
	}
	return _MOVE_ (ret) ;
}
#endif

#ifndef __CSC_COMPILER_MSVC__
inline String<STRA> static_locale_cvt_wstolas (const String<STRW> &val) {
	String<STRA> ret = String<STRA> ((val.length () + 1) * _SIZEOF_ (STRW)) ;
	_DEBUG_ASSERT_ (ret.size () < VAR32_MAX) ;
	if switch_case (TRUE) {
		const auto r3x = api::wcstombs (ret.raw ().self ,val.raw ().self ,VAR32 (ret.size ())) ;
		if (r3x == 0)
			discard ;
		ret = String<STRA> () ;
	}
	return _MOVE_ (ret) ;
}
#endif
} ;

inline exports String<STRW> StringProc::cvt_as_ws (const String<STRA> &val) {
	//@warn: not thread-safe due to internel storage
	const auto r1x = api::setlocale (LC_CTYPE ,NULL) ;
	_DEBUG_ASSERT_ (r1x != NULL) ;
	const auto r2x = BasicProc::mem_chr (PTRTOARR[r1x] ,VAR32_MAX ,STRA (0)) ;
	if (r2x == 1)
		if (BasicProc::mem_equal (PTRTOARR[r1x] ,_PCSTRA_ ("C").self ,1))
			return StringProc::cvt_u8s_ws (StringProc::cvt_uas_u8s (val)) ;
	if (r2x >= 4)
		if (BasicProc::mem_equal (PTRTOARR[&r1x[r2x - 4]] ,_PCSTRA_ (".936").self ,4))
			return StringProc::cvt_gbks_ws (val) ;
	if (r2x >= 5)
		if (BasicProc::mem_equal (PTRTOARR[r1x] ,_PCSTRA_ ("zh_CN").self ,5))
			return StringProc::cvt_gbks_ws (val) ;
	return U::static_locale_cvt_lastows (val) ;
}

inline exports String<STRA> StringProc::cvt_ws_as (const String<STRW> &val) {
	//@warn: not thread-safe due to internel storage
	const auto r1x = api::setlocale (LC_CTYPE ,NULL) ;
	_DEBUG_ASSERT_ (r1x != NULL) ;
	const auto r2x = BasicProc::mem_chr (PTRTOARR[r1x] ,VAR32_MAX ,STRA (0)) ;
	if (r2x == 1)
		if (BasicProc::mem_equal (PTRTOARR[r1x] ,_PCSTRA_ ("C").self ,1))
			return StringProc::cvt_u8s_uas (StringProc::cvt_ws_u8s (val)) ;
	if (r2x >= 4)
		if (BasicProc::mem_equal (PTRTOARR[&r1x[r2x - 4]] ,_PCSTRA_ (".936").self ,4))
			return StringProc::cvt_ws_gbks (val) ;
	if (r2x >= 5)
		if (BasicProc::mem_equal (PTRTOARR[r1x] ,_PCSTRA_ ("zh_CN").self ,5))
			return StringProc::cvt_ws_gbks (val) ;
	return U::static_locale_cvt_wstolas (val) ;
}

namespace U {
#ifdef __CSC_COMPILER_MSVC__
inline exports ARRAY8<VAR32> static_make_time_metric (const stl::chrono::system_clock::time_point &val) {
	ARRAY8<VAR32> ret ;
	ret.fill (0) ;
	const auto r1x = api::time_t (stl::chrono::system_clock::to_time_t (val)) ;
	auto rax = api::tm () ;
	_ZERO_ (rax) ;
	api::localtime_s (DEPTR[rax] ,DEPTR[r1x]) ;
	ret[0] = rax.tm_year + 1900 ;
	ret[1] = rax.tm_mon + 1 ;
	ret[2] = rax.tm_mday ;
	ret[3] = rax.tm_wday + 1 ;
	ret[4] = rax.tm_yday + 1 ;
	ret[5] = rax.tm_hour ;
	ret[6] = rax.tm_min ;
	ret[7] = rax.tm_sec ;
	return _MOVE_ (ret) ;
}
#endif

#ifndef __CSC_COMPILER_MSVC__
inline exports ARRAY8<VAR32> static_make_time_metric (const stl::chrono::system_clock::time_point &val) {
	ARRAY8<VAR32> ret ;
	ret.fill (0) ;
	const auto r1x = api::time_t (stl::chrono::system_clock::to_time_t (val)) ;
	auto rax = api::tm () ;
	_ZERO_ (rax) ;
	//@warn: not thread-safe due to internel storage
	const auto r2x = api::localtime (DEPTR[r1x]) ;
	_DEBUG_ASSERT_ (r2x != NULL) ;
	rax = DEREF[r2x] ;
	ret[0] = rax.tm_year + 1900 ;
	ret[1] = rax.tm_mon + 1 ;
	ret[2] = rax.tm_mday ;
	ret[3] = rax.tm_wday + 1 ;
	ret[4] = rax.tm_yday + 1 ;
	ret[5] = rax.tm_hour ;
	ret[6] = rax.tm_min ;
	ret[7] = rax.tm_sec ;
	return _MOVE_ (ret) ;
}
#endif

inline exports stl::chrono::system_clock::time_point static_make_time_point (const ARRAY8<VAR32> &val) {
	auto rax = api::tm () ;
	_ZERO_ (rax) ;
	const auto r1x = _EBOOL_ (val[0] > 0) * (val[0] - 1900) ;
	rax.tm_year = VAR32 (r1x) ;
	const auto r2x = _EBOOL_ (val[1] > 0) * (val[1] - 1) ;
	rax.tm_mon = VAR32 (r2x) ;
	rax.tm_mday = val[2] ;
	const auto r3x = _EBOOL_ (val[3] > 0) * (val[3] - 1) ;
	rax.tm_wday = VAR32 (r3x) ;
	const auto r4x = _EBOOL_ (val[4] > 0) * (val[4] - 1) ;
	rax.tm_yday = VAR32 (r4x) ;
	rax.tm_hour = val[5] ;
	rax.tm_min = val[6] ;
	rax.tm_sec = val[7] ;
	const auto r5x = api::mktime (DEPTR[rax]) ;
	return stl::chrono::system_clock::from_time_t (r5x) ;
}
} ;

#ifdef __CSC_EXTEND__
class RegexMatcher::Implement {
private:
	AutoRef<api::regex> mRegex ;

public:
	Implement () = delete ;

	explicit Implement (const String<STRU8> &reg) {
		const auto r1x = StringProc::cvt_u8s_uas (reg) ;
		mRegex = AutoRef<api::regex>::make (r1x.raw ().self) ;
	}

	BOOL match (const String<STRU8> &expr) const {
		if (expr.empty ())
			return FALSE ;
		const auto r1x = StringProc::cvt_u8s_uas (expr) ;
		if (!api::regex_match (r1x.raw ().self ,mRegex.self))
			return FALSE ;
		return TRUE ;
	}

	Deque<ARRAY2<INDEX>> search (const String<STRU8> &expr) const {
		Deque<ARRAY2<INDEX>> ret = Deque<ARRAY2<INDEX>> (expr.length ()) ;
		if switch_case (TRUE) {
			if (expr.empty ())
				discard ;
			auto rax = AutoRef<api::smatch>::make () ;
			const auto r1x = StringProc::cvt_u8s_uas (expr) ;
			const auto r2x = api::string (r1x.raw ().self) ;
			auto rbx = r2x.begin () ;
			const auto r3x = r2x.end () ;
			while (TRUE) {
				const auto r4x = api::regex_search (rbx ,r3x ,rax.self ,mRegex.self) ;
				if (!r4x)
					break ;
				INDEX ix = ret.insert () ;
				auto &r5x = (*rax.self[0].first) ;
				auto &r6x = (*rax.self[0].second) ;
				ret[ix][0] = INDEX (DEPTR[r5x] - &r2x[0]) ;
				ret[ix][1] = INDEX (DEPTR[r6x] - &r2x[0]) ;
				rbx = rax.self[0].second ;
			}
		}
		return _MOVE_ (ret) ;
	}

	String<STRU8> replace (const String<STRU8> &expr ,const String<STRU8> &rep) const {
		if (expr.empty ())
			return String<STRU8> () ;
		const auto r1x = StringProc::cvt_u8s_uas (expr) ;
		const auto r2x = StringProc::cvt_u8s_uas (rep) ;
		const auto r3x = api::string (r1x.raw ().self) ;
		const auto r4x = api::string (r2x.raw ().self) ;
		const auto r5x = api::regex_replace (r3x ,mRegex.self ,r4x) ;
		if (r5x.empty ())
			return String<STRU8> () ;
		return StringProc::cvt_uas_u8s (PTRTOARR[r5x.c_str ()]) ;
	}
} ;

inline exports RegexMatcher::RegexMatcher (const String<STRU8> &reg) {
	mThis = StrongRef<Implement>::make (reg) ;
}

inline exports BOOL RegexMatcher::match (const String<STRU8> &expr) const {
	return mThis->match (expr) ;
}

inline exports Deque<ARRAY2<INDEX>> RegexMatcher::search (const String<STRU8> &expr) const {
	return mThis->search (expr) ;
}

inline exports String<STRU8> RegexMatcher::replace (const String<STRU8> &expr ,const String<STRU8> &rep) const {
	return mThis->replace (expr ,rep) ;
}
#endif
} ;