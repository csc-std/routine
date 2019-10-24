﻿#pragma once

#ifndef __CSC_EXT__
#define __CSC_EXT__
#endif

#include "csc.hpp"

#ifdef __CSC__
#pragma push_macro ("self")
#pragma push_macro ("implicit")
#pragma push_macro ("popping")
#pragma push_macro ("imports")
#pragma push_macro ("exports")
#pragma push_macro ("discard")
#undef self
#undef implicit
#undef popping
#undef imports
#undef exports
#undef discard
#endif

#pragma region
#pragma warning (push)
#ifdef __CSC_COMPILER_MSVC__
#pragma warning (disable :5039)
#endif
#include <cstdlib>
#include <locale>
#include <exception>
#include <chrono>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <thread>
#pragma warning (pop)
#pragma endregion

#ifdef __CSC__
#pragma pop_macro ("self")
#pragma pop_macro ("implicit")
#pragma pop_macro ("popping")
#pragma pop_macro ("imports")
#pragma pop_macro ("exports")
#pragma pop_macro ("discard")
#endif

namespace CSC {
namespace stl {
using std::exception ;

using std::mutex ;
using std::recursive_mutex ;
using std::atomic ;
using std::unique_lock ;
using std::condition_variable ;
using std::thread ;

namespace chrono {
using std::chrono::duration ;
using std::chrono::time_point ;
using std::chrono::nanoseconds ;
using std::chrono::microseconds ;
using std::chrono::milliseconds ;
using std::chrono::seconds ;
using std::chrono::minutes ;
using std::chrono::hours ;
using std::chrono::system_clock ;
using std::chrono::steady_clock ;
} ;

namespace this_thread {
using std::this_thread::get_id ;
using std::this_thread::sleep_for ;
using std::this_thread::sleep_until ;
using std::this_thread::yield ;
} ;

using std::atomic_thread_fence ;
using std::atomic_signal_fence ;

using std::exit ;
using std::abort ;
} ;

#ifdef __CSC_COMPILER_MSVC__
#define DLLABI_IMPORT __declspec (dllimport)
#define DLLABI_EXPORT __declspec (dllexport)
#define DLLABI_API __stdcall
#define DLLABI_NATIVE extern "C"
#elif defined __CSC_COMPILER_GNUC__
#define DLLABI_IMPORT
#define DLLABI_EXPORT __attribute__ ((visibility ("default")))
#define DLLABI_API
#define DLLABI_NATIVE extern "C"
#elif defined __CSC_COMPILER_CLANG__
#define DLLABI_IMPORT
#define DLLABI_EXPORT __attribute__ ((visibility ("default")))
#define DLLABI_API
#define DLLABI_NATIVE extern "C"
#else
#define DLLABI_IMPORT
#define DLLABI_EXPORT
#define DLLABI_API
#define DLLABI_NATIVE
#endif

template <class UNIT1 ,class UNIT2>
struct Component {
	UNIT1 mValue ;
	UNIT2 mClazz ;
} ;

namespace stl {
template <class... _ARGS>
using is_all_same = U::is_all_same<_ARGS...> ;

template <class... _ARGS>
using is_any_same = U::is_any_same<_ARGS...> ;

template <class _ARG1>
using is_template_type = U::is_template_type<_ARG1> ;

template <class _ARG1>
using is_complete_type = U::is_complete_type<_ARG1> ;

template <class _ARG1>
using is_interface_type = U::is_interface_type<_ARG1 ,Interface> ;

template <class _ARG1 ,class _ARG2>
using is_always_base_of = U::is_always_base_of<_ARG1 ,_ARG2> ;
} ;

template <class _ARG1 ,class _ARG2>
using INDEX_OF_TYPE = U::INDEX_OF_TYPE<_ARG1 ,_ARG2> ;

template <class _ARG1 ,class _ARG2>
using INDEX_TO_TYPE = U::INDEX_TO_TYPE<_ARG1 ,_ARG2> ;

template <class _ARG1>
using REMOVE_TEMPLATE_TYPE = U::REMOVE_TEMPLATE_TYPE<_ARG1> ;

template <class _ARG1>
using TEMPLATE_PARAMS_TYPE = U::TEMPLATE_PARAMS_TYPE<_ARG1> ;

class GlobalRuntime final :private Wrapped<void> {
public:
	inline static std::chrono::system_clock::time_point clock_now () {
		return std::chrono::system_clock::now () ;
	}

	inline static std::chrono::steady_clock::time_point clock_ios () {
		return std::chrono::steady_clock::now () ;
	}

	inline static std::thread::id thread_tid () {
		return std::this_thread::get_id () ;
	}

	template <class... _ARGS>
	inline static void thread_sleep (const std::chrono::duration<_ARGS...> &_time) {
		std::this_thread::sleep_for (_time) ;
	}

	template <class... _ARGS>
	inline static void thread_sleep (const std::chrono::time_point<_ARGS...> &_time) {
		std::this_thread::sleep_for (_time) ;
	}

	inline static void thread_sleep () {
		std::this_thread::yield () ;
	}

	inline static LENGTH thread_concurrency () {
		return LENGTH (std::thread::hardware_concurrency ()) ;
	}

	inline static void thread_fence (std::memory_order _order) {
		std::atomic_thread_fence (_order) ;
	}

	inline static void locale_init (const Plain<STRA> &_locale) {
		setlocale (LC_ALL ,_locale.self) ;
	}

	inline static void process_exit () {
		std::exit (EXIT_FAILURE) ;
	}

	inline static void process_abort () {
		std::abort () ;
	}
} ;

template <class _ARG1 ,class _ARG2>
inline void _CATCH_ (_ARG1 &&try_proc ,_ARG2 &&catch_proc) noexcept {
	_STATIC_ASSERT_ (!std::is_reference<_ARG1>::value) ;
	_STATIC_ASSERT_ (std::is_same<RESULT_OF_TYPE<_ARG1 ,ARGVS<>> ,void>::value) ;
	_STATIC_ASSERT_ (!std::is_reference<_ARG2>::value) ;
	_STATIC_ASSERT_ (std::is_same<RESULT_OF_TYPE<_ARG2 ,ARGVS<const Exception &>> ,void>::value) ;
	try {
		try_proc () ;
		return ;
	} catch (const Exception &e) {
		catch_proc (e) ;
	} catch (const std::exception &) {
		catch_proc (Exception (_PCSTR_ ("std::exception : null"))) ;
	} catch (...) {
		catch_proc (Exception (_PCSTR_ ("unknown C++ exception"))) ;
	}
}

#ifdef __CSC_UNITTEST__
class GlobalWatch final :private Wrapped<void> {
private:
	template <class UNIT1 ,class UNIT2>
	class Storage final :private Interface {
	private:
		friend GlobalWatch ;
		PTR<const STR> mName ;
		PTR<UNIT2> mAddress ;
		FLAG mTypeUID ;
		PTR<void (UNIT2 &)> mWatch ;

	public:
		inline Storage () {
			mName = NULL ;
			mAddress = NULL ;
			mTypeUID = 0 ;
			mWatch = NULL ;
		} ;
	} ;

public:
	template <class _ARG1 ,class _ARG2>
	inline static void done (const ARGV<_ARG1> & ,const Plain<STR> &name ,_ARG2 &data) noexcept {
		static volatile Storage<_ARG1 ,_ARG2> mInstance ;
		mInstance.mName = name.self ;
		mInstance.mAddress = &data ;
		mInstance.mTypeUID = _TYPEUID_<_ARG2> () ;
		const auto r1x = _COPY_ (mInstance.mWatch) ;
		if (r1x == NULL)
			return ;
		r1x (data) ;
	}
} ;
#endif

class VAR128 {
#pragma region
#pragma push_macro ("v2i0")
#pragma push_macro ("v2i1")
#pragma push_macro ("v4i0")
#pragma push_macro ("v4i1")
#pragma push_macro ("v4i2")
#pragma push_macro ("v4i3")
#undef v2i0
#undef v2i1
#undef v4i0
#undef v4i1
#undef v4i2
#undef v4i3
#define v2i0 m_v2i0 ()
#define v2i1 m_v2i1 ()
#define v4i0 m_v4i0 ()
#define v4i1 m_v4i1 ()
#define v4i2 m_v4i2 ()
#define v4i3 m_v4i3 ()

private:
	class Detail ;
	MEGA mData ;

public:
	inline VAR128 () = default ;

	inline implicit VAR128 (VAR64 that) {
		v2i1 = DATA (that) ;
		const auto r1x = _SWITCH_ (
			(that >= 0) ? (DATA (0)) :
			(DATA (-1))) ;
		v2i0 = r1x ;
	}

	inline explicit operator VAR32 () const {
		return VAR32 (v2i1) ;
	}

	inline explicit operator VAR64 () const {
		return VAR64 (v2i1) ;
	}

	inline BOOL operator== (const VAR128 &that) const {
		if (v2i1 != that.v2i1)
			return FALSE ;
		if (v2i0 != that.v2i0)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator!= (const VAR128 &that) const {
		return !operator== (that) ;
	}

	inline BOOL operator< (const VAR128 &that) const {
		const auto r1x = _CAST_<VAR64> (v2i0) ;
		const auto r2x = _CAST_<VAR64> (that.v2i0) ;
		if (r1x < r2x)
			return TRUE ;
		if (r1x > r2x)
			return FALSE ;
		if (v2i1 >= that.v2i1)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator>= (const VAR128 &that) const {
		return !operator< (that) ;
	}

	inline BOOL operator> (const VAR128 &that) const {
		return that.operator< ((*this)) ;
	}

	inline BOOL operator<= (const VAR128 &that) const {
		return !operator> (that) ;
	}

	inline VAR128 operator& (const VAR128 &) const = delete ;

	inline VAR128 &operator&= (const VAR128 &) = delete ;

	inline VAR128 operator| (const VAR128 &) const = delete ;

	inline VAR128 &operator|= (const VAR128 &) = delete ;

	inline VAR128 operator^ (const VAR128 &) const = delete ;

	inline VAR128 &operator^= (const VAR128 &) = delete ;

	inline VAR128 operator~ () const = delete ;

	inline VAR128 operator>> (VAR) const = delete ;

	inline VAR128 &operator>>= (VAR) = delete ;

	inline VAR128 operator<< (VAR) const = delete ;

	inline VAR128 &operator<<= (VAR) = delete ;

	inline VAR128 operator+ (const VAR128 &that) const {
		VAR128 ret = 0 ;
		ret.v2i0 = v2i0 + that.v2i0 + EFLAG (v2i1 > ~that.v2i1) ;
		ret.v2i1 = v2i1 + that.v2i1 ;
		return std::move (ret) ;
	}

	inline VAR128 &operator+= (const VAR128 &that) {
		v2i0 += that.v2i0 + EFLAG (v2i1 > ~that.v2i1) ;
		v2i1 += that.v2i1 ;
		return (*this) ;
	}

	inline VAR128 operator- (const VAR128 &that) const {
		VAR128 ret = 0 ;
		ret.v2i0 = v2i0 - that.v2i0 - EFLAG (v2i1 < that.v2i1) ;
		ret.v2i1 = v2i1 - that.v2i1 ;
		return std::move (ret) ;
	}

	inline VAR128 &operator-= (const VAR128 &that) {
		v2i0 -= that.v2i0 + EFLAG (v2i1 < that.v2i1) ;
		v2i1 -= that.v2i1 ;
		return (*this) ;
	}

	inline VAR128 operator* (const VAR128 &that) const {
		VAR128 ret = 0 ;
		auto rax = DATA () ;
		rax = CHAR (rax >> (_SIZEOF_ (CHAR) * 8)) ;
		rax += DATA (v4i3) * DATA (that.v4i3) ;
		ret.v4i3 = CHAR (rax) ;
		rax = CHAR (rax >> (_SIZEOF_ (CHAR) * 8)) ;
		rax += DATA (v4i3) * DATA (that.v4i2) ;
		rax += DATA (v4i2) * DATA (that.v4i3) ;
		ret.v4i2 = CHAR (rax) ;
		rax = CHAR (rax >> (_SIZEOF_ (CHAR) * 8)) ;
		rax += DATA (v4i3) * DATA (that.v4i1) ;
		rax += DATA (v4i2) * DATA (that.v4i2) ;
		rax += DATA (v4i1) * DATA (that.v4i3) ;
		ret.v4i1 = CHAR (rax) ;
		rax = CHAR (rax >> (_SIZEOF_ (CHAR) * 8)) ;
		rax += DATA (v4i3) * DATA (that.v4i0) ;
		rax += DATA (v4i2) * DATA (that.v4i1) ;
		rax += DATA (v4i1) * DATA (that.v4i2) ;
		rax += DATA (v4i0) * DATA (that.v4i3) ;
		ret.v4i0 = CHAR (rax) ;
		return std::move (ret) ;
	}

	inline VAR128 &operator*= (const VAR128 &that) {
		(*this) = (*this) * that ;
		return (*this) ;
	}

	inline VAR128 operator/ (const VAR128 &that) const {
		VAR128 ret = 0 ;
		const auto r1x = _CAST_<VAR64> (v2i0) ;
		const auto r2x = _CAST_<VAR64> (that.v2i0) ;
		auto fax = FALSE ;
		if SWITCH_CASE (fax) {
			if (!(r1x >= 0))
				discard ;
			if (!(that.v4i0 == 0))
				discard ;
			if (!(that.v4i1 == 0))
				discard ;
			if (!(that.v4i2 == 0))
				discard ;
			auto rax = DATA () ;
			const auto r3x = DATA (that.v4i3) ;
			_DEBUG_ASSERT_ (r3x != 0) ;
			rax = (DATA (0) << (_SIZEOF_ (CHAR) * 8)) | DATA (v4i0) ;
			ret.v4i0 = CHAR (rax / r3x) ;
			rax = (DATA (rax % r3x) << (_SIZEOF_ (CHAR) * 8)) | DATA (v4i1) ;
			ret.v4i1 = CHAR (rax / r3x) ;
			rax = (DATA (rax % r3x) << (_SIZEOF_ (CHAR) * 8)) | DATA (v4i2) ;
			ret.v4i2 = CHAR (rax / r3x) ;
			rax = (DATA (rax % r3x) << (_SIZEOF_ (CHAR) * 8)) | DATA (v4i3) ;
			ret.v4i3 = CHAR (rax / r3x) ;
		}
		if SWITCH_CASE (fax) {
			if (!(v2i0 == DATA (VAR64_MIN)))
				discard ;
			if (!(v2i1 == 0))
				discard ;
			if (!(r2x >= 0))
				discard ;
			ret = -(-((*this) + that) / that + 1) ;
		}
		if SWITCH_CASE (fax) {
			if (!(v2i0 == DATA (VAR64_MIN)))
				discard ;
			if (!(v2i1 == 0))
				discard ;
			if (!(r2x < 0))
				discard ;
			ret = -(-((*this) - that) / that - 1) ;
		}
		if SWITCH_CASE (fax) {
			if (!(r1x < 0))
				discard ;
			ret = -(-(*this) / that) ;
		}
		if SWITCH_CASE (fax) {
			if (!(r1x >= 0))
				discard ;
			if (!(that.v2i0 == DATA (VAR64_MIN)))
				discard ;
			if (!(that.v2i1 == 0))
				discard ;
			ret = VAR128 (0) ;
		}
		if SWITCH_CASE (fax) {
			if (!(r1x >= 0))
				discard ;
			if (!(r2x < 0))
				discard ;
			ret = (*this) / (-that) ;
		}
		if SWITCH_CASE (fax) {
			ret = Detail::slow_divide ((*this) ,that) ;
		}
		return std::move (ret) ;
	}

	inline VAR128 &operator/= (const VAR128 &that) {
		(*this) = (*this) / that ;
		return (*this) ;
	}

	inline VAR128 operator% (const VAR128 &that) const {
		VAR128 ret = 0 ;
		const auto r1x = _CAST_<VAR64> (v2i0) ;
		const auto r2x = _CAST_<VAR64> (that.v2i0) ;
		auto fax = FALSE ;
		if SWITCH_CASE (fax) {
			if (!(r1x >= 0))
				discard ;
			if (!(that.v4i0 == 0))
				discard ;
			if (!(that.v4i1 == 0))
				discard ;
			if (!(that.v4i2 == 0))
				discard ;
			auto rax = DATA () ;
			const auto r3x = DATA (that.v4i3) ;
			_DEBUG_ASSERT_ (r3x != 0) ;
			rax = (DATA (0) << (_SIZEOF_ (CHAR) * 8)) | DATA (v4i0) ;
			ret.v4i0 = 0 ;
			rax = (DATA (rax % r3x) << (_SIZEOF_ (CHAR) * 8)) | DATA (v4i1) ;
			ret.v4i1 = 0 ;
			rax = (DATA (rax % r3x) << (_SIZEOF_ (CHAR) * 8)) | DATA (v4i2) ;
			ret.v4i2 = 0 ;
			rax = (DATA (rax % r3x) << (_SIZEOF_ (CHAR) * 8)) | DATA (v4i3) ;
			ret.v4i3 = CHAR (rax % r3x) ;
		}
		if SWITCH_CASE (fax) {
			if (!(v2i0 == DATA (VAR64_MIN)))
				discard ;
			if (!(v2i1 == 0))
				discard ;
			if (!(r2x >= 0))
				discard ;
			ret = -(-((*this) + that) % that) ;
		}
		if SWITCH_CASE (fax) {
			if (!(v2i0 == DATA (VAR64_MIN)))
				discard ;
			if (!(v2i1 == 0))
				discard ;
			if (!(r2x < 0))
				discard ;
			ret = -(-((*this) - that) % that) ;
		}
		if SWITCH_CASE (fax) {
			if (!(r1x < 0))
				discard ;
			ret = -(-(*this) % that) ;
		}
		if SWITCH_CASE (fax) {
			if (!(r1x >= 0))
				discard ;
			if (!(that.v2i0 == DATA (VAR64_MIN)))
				discard ;
			if (!(that.v2i1 == 0))
				discard ;
			ret = (*this) ;
		}
		if SWITCH_CASE (fax) {
			if (!(r1x >= 0))
				discard ;
			if (!(r2x < 0))
				discard ;
			ret = (*this) % (-that) ;
		}
		if SWITCH_CASE (fax) {
			ret = that - Detail::slow_divide ((*this) ,that) * that ;
		}
		return std::move (ret) ;
	}

	inline VAR128 &operator%= (const VAR128 &that) {
		(*this) = (*this) % that ;
		return (*this) ;
	}

	inline VAR128 operator+ () const {
		return (*this) ;
	}

	inline VAR128 operator- () const {
		VAR128 ret = 0 ;
		ret.v2i1 = ~v2i1 + 1 ;
		ret.v2i0 = ~v2i0 + EFLAG (ret.v2i1 == DATA (0)) ;
		return std::move (ret) ;
	}

	inline VAR128 &operator++ () {
		v2i1++ ;
		v2i0 += EFLAG (v2i1 == DATA (0)) ;
		return (*this) ;
	}

	inline VAR128 operator++ (VAR32) popping {
		VAR128 ret = (*this) ;
		++(*this) ;
		return std::move (ret) ;
	}

	inline VAR128 &operator-- () {
		v2i1-- ;
		v2i0 -= EFLAG (v2i1 == DATA (-1)) ;
		return (*this) ;
	}

	inline VAR128 operator-- (VAR32) popping {
		VAR128 ret = (*this) ;
		--(*this) ;
		return std::move (ret) ;
	}

private:
	inline DATA &m_v2i0 () & {
		const auto r1x = WORD (0X0001) ;
		return _CAST_<DATA[2]> (mData)[_CAST_<BYTE[2]> (r1x)[0]] ;
	}

	inline const DATA &m_v2i0 () const & {
		const auto r1x = WORD (0X0001) ;
		return _CAST_<DATA[2]> (mData)[_CAST_<BYTE[2]> (r1x)[0]] ;
	}

	inline DATA &m_v2i0 () && = delete ;

	inline DATA &m_v2i1 () & {
		const auto r1x = WORD (0X0001) ;
		return _CAST_<DATA[2]> (mData)[_CAST_<BYTE[2]> (r1x)[1]] ;
	}

	inline const DATA &m_v2i1 () const & {
		const auto r1x = WORD (0X0001) ;
		return _CAST_<DATA[2]> (mData)[_CAST_<BYTE[2]> (r1x)[1]] ;
	}

	inline DATA &m_v2i1 () && = delete ;

	inline CHAR &m_v4i0 () & {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_<CHAR[4]> (mData)[_CAST_<BYTE[4]> (r1x)[0]] ;
	}

	inline const CHAR &m_v4i0 () const & {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_<CHAR[4]> (mData)[_CAST_<BYTE[4]> (r1x)[0]] ;
	}

	inline CHAR &m_v4i0 () && = delete ;

	inline CHAR &m_v4i1 () & {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_<CHAR[4]> (mData)[_CAST_<BYTE[4]> (r1x)[1]] ;
	}

	inline const CHAR &m_v4i1 () const & {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_<CHAR[4]> (mData)[_CAST_<BYTE[4]> (r1x)[1]] ;
	}

	inline CHAR &m_v4i1 () && = delete ;

	inline CHAR &m_v4i2 () & {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_<CHAR[4]> (mData)[_CAST_<BYTE[4]> (r1x)[2]] ;
	}

	inline const CHAR &m_v4i2 () const & {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_<CHAR[4]> (mData)[_CAST_<BYTE[4]> (r1x)[2]] ;
	}

	inline CHAR &m_v4i2 () && = delete ;

	inline CHAR &m_v4i3 () & {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_<CHAR[4]> (mData)[_CAST_<BYTE[4]> (r1x)[3]] ;
	}

	inline const CHAR &m_v4i3 () const & {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_<CHAR[4]> (mData)[_CAST_<BYTE[4]> (r1x)[3]] ;
	}

	inline CHAR &m_v4i3 () && = delete ;

private:
	class Detail :private Wrapped<void> {
	public:
		inline static VAR128 slow_divide (const VAR128 &y ,const VAR128 &x) {
			_DEBUG_ASSERT_ (y >= 0) ;
			_DEBUG_ASSERT_ (x > 0) ;
			VAR128 ret = 0 ;
			auto rax = Buffer<VAR128 ,ARGC<2>> () ;
			rax[0] = 0 ;
			rax[1] = y ;
			while (TRUE) {
				if (rax[0] > rax[1])
					break ;
				ret = rax[0] + (rax[1] - rax[0]) / 2 ;
				const auto r1x = x * ret ;
				if (r1x == y)
					break ;
				auto &r2y = _SWITCH_ (
					(r1x < y) ? (rax[0]) :
					(rax[1])) ;
				const auto r3x = _SWITCH_ (
					(r1x < y) ? (ret + 1) :
					(ret - 1)) ;
				r2y = r3x ;
			}
			ret -= EFLAG (ret * x > y) ;
			return std::move (ret) ;
		}
	} ;

#undef v2i0
#undef v2i1
#undef v4i0
#undef v4i1
#undef v4i2
#undef v4i3
#pragma pop_macro ("v2i1")
#pragma pop_macro ("v2i0")
#pragma pop_macro ("v4i3")
#pragma pop_macro ("v4i2")
#pragma pop_macro ("v4i1")
#pragma pop_macro ("v4i0")
#pragma endregion
} ;

class VAL128 {
#pragma region
#pragma push_macro ("v2f0")
#pragma push_macro ("v2f1")
#undef v2f0
#undef v2f1
#define v2f0 m_v2f0 ()
#define v2f1 m_v2f1 ()

private:
	MEGA mData ;

public:
	inline VAL128 () = default ;

	inline implicit VAL128 (VAL64 that) {
		v2f1 = that ;
		v2f0 = 1 ;
	}

	inline explicit operator VAL32 () const {
		return VAL32 (v2f1) ;
	}

	inline explicit operator VAL64 () const {
		return VAL64 (v2f1) ;
	}

	inline BOOL operator== (const VAL128 &) const = delete ;

	inline BOOL operator!= (const VAL128 &) const = delete ;

	inline BOOL operator< (const VAL128 &that) const {
		if (v2f1 >= that.v2f1)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator>= (const VAL128 &) const = delete ;

	inline BOOL operator> (const VAL128 &that) const {
		return that.operator< ((*this)) ;
	}

	inline BOOL operator<= (const VAL128 &) const = delete ;

	inline VAL128 operator+ (const VAL128 &that) const {
		VAL128 ret = 0 ;
		ret.v2f1 = v2f1 + that.v2f1 ;
		return std::move (ret) ;
	}

	inline VAL128 &operator+= (const VAL128 &that) {
		v2f1 += that.v2f1 ;
		return (*this) ;
	}

	inline VAL128 operator- (const VAL128 &that) const {
		VAL128 ret = 0 ;
		ret.v2f1 = v2f1 - that.v2f1 ;
		return std::move (ret) ;
	}

	inline VAL128 &operator-= (const VAL128 &that) {
		v2f1 -= that.v2f1 ;
		return (*this) ;
	}

	inline VAL128 operator* (const VAL128 &that) const {
		VAL128 ret = 0 ;
		ret.v2f1 = v2f1 * that.v2f1 ;
		return std::move (ret) ;
	}

	inline VAL128 &operator*= (const VAL128 &that) {
		v2f1 *= that.v2f1 ;
		return (*this) ;
	}

	inline VAL128 operator/ (const VAL128 &that) const {
		VAL128 ret = 0 ;
		ret.v2f1 = v2f1 / that.v2f1 ;
		return std::move (ret) ;
	}

	inline VAL128 &operator/= (const VAL128 &that) {
		v2f1 *= that.v2f1 ;
		return (*this) ;
	}

	inline VAL128 operator+ () const {
		return (*this) ;
	}

	inline VAL128 operator- () const {
		VAL128 ret = 0 ;
		ret.v2f1 = -v2f1 ;
		return std::move (ret) ;
	}

private:
	inline VAL64 &m_v2f0 () & {
		return _CAST_<VAL64[2]> (mData)[0] ;
	}

	inline const VAL64 &m_v2f0 () const & {
		return _CAST_<VAL64[2]> (mData)[0] ;
	}

	inline VAL64 &m_v2f0 () && = delete ;

	inline VAL64 &m_v2f1 () & {
		return _CAST_<VAL64[2]> (mData)[1] ;
	}

	inline const VAL64 &m_v2f1 () const & {
		return _CAST_<VAL64[2]> (mData)[1] ;
	}

	inline VAL64 &m_v2f1 () && = delete ;

#undef v2f0
#undef v2f1
#pragma pop_macro ("v2f0")
#pragma pop_macro ("v2f1")
#pragma endregion
} ;

namespace U {
struct OPERATOR_CRC32 {
	inline static constexpr BOOL constexpr_check (INDEX index ,LENGTH range) {
		return BOOL (index >= 0 && index < range) ;
	}

	inline static constexpr CHAR constexpr_crc32_next (CHAR val) {
		return _SWITCH_ (
			((val & CHAR (0X00000001)) != 0) ? (CHAR (0)) :
			(CHAR (0XEDB88320) ^ (val >> 1))) ;
	}

	inline static constexpr CHAR constexpr_crc32_table (CHAR val ,INDEX curr) {
		return _SWITCH_ (
			!(constexpr_check (curr ,8)) ? val :
			(constexpr_crc32_table (constexpr_crc32_next (val) ,(curr + 1)))) ;
	}

	inline static constexpr CHAR constexpr_crc32_hash (const Plain<STR> &stri ,CHAR val ,INDEX curr) {
#pragma GCC diagnostic push
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
		return _SWITCH_ (
			!(constexpr_check (curr ,stri.size ())) ? val :
			(constexpr_crc32_hash (stri ,(constexpr_crc32_table (INDEX ((CHAR (val) ^ CHAR (stri.self[curr])) & CHAR (0X000000FF)) ,0) ^ (val >> 8)) ,(curr + 1)))) ;
#pragma GCC diagnostic pop
	}

	inline static constexpr FLAG invoke (const Plain<STR> &stri) {
		return FLAG (VAR32 (constexpr_crc32_hash (stri ,CHAR (0XFFFFFFFF) ,0)) & VAR32_MAX) ;
	}
} ;
} ;

template <class UNIT>
class Mutable {
private:
	static constexpr auto STATUS_CACHED = FLAG (1) ;
	static constexpr auto STATUS_SIGNALED = FLAG (2) ;
	static constexpr auto STATUS_FINISHED = FLAG (3) ;

private:
	mutable UNIT mData ;
	mutable FLAG mStatus ;

public:
	inline Mutable () {
		mStatus = STATUS_SIGNALED ;
	}

	inline implicit Mutable (const UNIT &that) :Mutable (ARGVP0 ,std::move (that)) {}

	inline implicit Mutable (UNIT &&that) : Mutable (ARGVP0 ,std::move (that)) {}

	inline const UNIT &to () const {
		return mData ;
	}

	inline implicit operator const UNIT & () const {
		return to () ;
	}

	template <class _ARG1>
	inline void apply (const Function<void (_ARG1 &)> &proc) const {
		_STATIC_ASSERT_ (std::is_same<REMOVE_CVR_TYPE<_ARG1> ,UNIT>::value) ;
		if (mStatus != STATUS_SIGNALED)
			return ;
		proc (mData) ;
		mStatus = STATUS_CACHED ;
	}

	template <class _ARG1>
	inline void apply (const Function<FIX_MSVC_DEDUCTION_2<void ,_ARG1 &>> &proc) const {
		_STATIC_ASSERT_ (std::is_same<REMOVE_CVR_TYPE<_ARG1> ,UNIT>::value) ;
		if (mStatus != STATUS_SIGNALED)
			return ;
		proc (mData) ;
		mStatus = STATUS_CACHED ;
	}

	inline void signal () const {
		if (mStatus != STATUS_CACHED)
			return ;
		mStatus = STATUS_SIGNALED ;
	}

	inline void finish () const {
		mStatus = STATUS_FINISHED ;
	}

private:
	template <class... _ARGS>
	inline explicit Mutable (const DEF<decltype (ARGVP0)> & ,_ARGS &&...initval) :mData (std::forward<_ARGS> (initval)...) ,mStatus (STATUS_CACHED) {}
} ;

template <class... UNITS>
class Variant {
private:
	inline static constexpr LENGTH constexpr_max_sizeof (const ARGVS<> &) {
		return 1 ;
	}

	template <class _ARG1 ,class... _ARGS>
	inline static constexpr LENGTH constexpr_max_sizeof (const ARGVS<_ARG1 ,_ARGS...> &) {
		return _MAX_ (_SIZEOF_ (_ARG1) ,constexpr_max_sizeof (_NULL_<ARGVS<_ARGS...>> ())) ;
	}

	inline static constexpr LENGTH constexpr_max_alignof (const ARGVS<> &) {
		return 1 ;
	}

	template <class _ARG1 ,class... _ARGS>
	inline static constexpr LENGTH constexpr_max_alignof (const ARGVS<_ARG1 ,_ARGS...> &) {
		return _MAX_ (_ALIGNOF_ (_ARG1) ,constexpr_max_alignof (_NULL_<ARGVS<_ARGS...>> ())) ;
	}

	//@error: g++4.8 is too useless to use constexpr value in alignas expression
	template <LENGTH ALIGN ,LENGTH SIZE>
	struct ALIGNED_UNION {
		alignas (ALIGN) DEF<BYTE[SIZE]> unused ;
	} ;

	//@error: 'std::aligned_union' is not avaliable in g++4.8
	using VARIANT = ALIGNED_UNION<constexpr_max_alignof (_NULL_<ARGVS<UNITS...>> ()) ,constexpr_max_sizeof (_NULL_<ARGVS<UNITS...>> ())> ;

	template <class _ARG1>
	inline static constexpr INDEX default_constructible_index (const ARGV<_ARG1> & ,const ARGVS<> &) {
		return VAR_NONE ;
	}

	template <class _ARG1 ,class _ARG2 ,class... _ARGS>
	inline static constexpr INDEX default_constructible_index (const ARGV<_ARG1> & ,const ARGVS<_ARG2 ,_ARGS...> &) {
		return _SWITCH_ (
			(std::is_default_constructible<_ARG2>::value) ? (_ARG1::value) :
			(default_constructible_index (_NULL_<ARGV<ARGC<_ARG1::value + 1>>> () ,_NULL_<ARGVS<_ARGS...>> ()))) ;
	}

private:
	_STATIC_ASSERT_ (_CAPACITYOF_ (UNITS) > 0) ;
	_STATIC_ASSERT_ (!stl::is_any_same<REMOVE_CVR_TYPE<UNITS>...>::value) ;
	class Detail ;
	TEMP<VARIANT> mVariant ;
	INDEX mIndex ;

public:
	inline Variant () :Variant (ARGVP0) {
		const auto r1x = default_constructible_index (_NULL_<ARGV<ARGC<0>>> () ,_NULL_<ARGVS<UNITS...>> ()) ;
		Detail::template_construct (&mVariant ,r1x ,_NULL_<ARGVS<UNITS...>> ()) ;
		mIndex = r1x ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<!std::is_same<REMOVE_CVR_TYPE<_ARG1> ,Variant>::value && INDEX_OF_TYPE<_ARG1 ,ARGVS<UNITS...>>::value != VAR_NONE>>
	inline implicit Variant (_ARG1 &&that) :Variant (ARGVP0) {
		_STATIC_ASSERT_ (!std::is_same<REMOVE_CVR_TYPE<_ARG1> ,DEF<decltype (ARGVP0)>>::value) ;
		auto &r1y = _LOAD_<TEMP<REMOVE_CVR_TYPE<_ARG1>>> (&mVariant) ;
		Detail::template_create (_NULL_<ARGV<ARGC<std::is_constructible<REMOVE_CVR_TYPE<_ARG1> ,_ARG1 &&>::value>>> () ,&r1y ,std::forward<_ARG1> (that)) ;
		mIndex = INDEX_OF_TYPE<_ARG1 ,ARGVS<UNITS...>>::value ;
	}

	inline ~Variant () noexcept {
		if (mIndex == VAR_NONE)
			return ;
		Detail::template_destruct (&mVariant ,mIndex ,_NULL_<ARGVS<UNITS...>> ()) ;
		mIndex = VAR_NONE ;
	}

	inline Variant (const Variant &that) :Variant (ARGVP0) {
		if (that.mIndex == VAR_NONE)
			return ;
		Detail::template_copy_construct (&mVariant ,&that.mVariant ,that.mIndex ,_NULL_<ARGVS<UNITS...>> ()) ;
		mIndex = that.mIndex ;
	}

	inline Variant &operator= (const Variant &that) {
		for (FOR_ONCE_DO) {
			if (this == &that)
				discard ;
			(*this).~Variant () ;
			new (this) Variant (std::move (that)) ;
		}
		return (*this) ;
	}

	inline Variant (Variant &&that) noexcept :Variant (ARGVP0) {
		if (that.mIndex == VAR_NONE)
			return ;
		Detail::template_move_construct (&mVariant ,&that.mVariant ,that.mIndex ,_NULL_<ARGVS<UNITS...>> ()) ;
		mIndex = that.mIndex ;
	}

	inline Variant &operator= (Variant &&that) noexcept {
		for (FOR_ONCE_DO) {
			if (this == &that)
				discard ;
			(*this).~Variant () ;
			new (this) Variant (std::move (that)) ;
		}
		return (*this) ;
	}

	inline BOOL exist () const {
		if (mIndex == VAR_NONE)
			return FALSE ;
		return TRUE ;
	}

	template <class _RET>
	inline BOOL available () const {
		_STATIC_ASSERT_ (!std::is_reference<_RET>::value) ;
		_STATIC_ASSERT_ (INDEX_OF_TYPE<_RET ,ARGVS<UNITS...>>::value != VAR_NONE) ;
		if (mIndex != INDEX_OF_TYPE<_RET ,ARGVS<UNITS...>>::value)
			return FALSE ;
		return TRUE ;
	}

	inline INDEX_TO_TYPE<ARGC<0> ,ARGVS<UNITS...>> &to () {
		_STATIC_ASSERT_ (_CAPACITYOF_ (UNITS) == 1) ;
		_DYNAMIC_ASSERT_ (exist ()) ;
		auto &r1y = _LOAD_<TEMP<INDEX_TO_TYPE<ARGC<0> ,ARGVS<UNITS...>>>> (&mVariant) ;
		return _CAST_<INDEX_TO_TYPE<ARGC<0> ,ARGVS<UNITS...>>> (r1y) ;
	}

	inline implicit operator INDEX_TO_TYPE<ARGC<0> ,ARGVS<UNITS...>> & () {
		return to () ;
	}

	inline const INDEX_TO_TYPE<ARGC<0> ,ARGVS<UNITS...>> &to () const {
		_STATIC_ASSERT_ (_CAPACITYOF_ (UNITS) == 1) ;
		_DYNAMIC_ASSERT_ (exist ()) ;
		auto &r1y = _LOAD_<TEMP<INDEX_TO_TYPE<ARGC<0> ,ARGVS<UNITS...>>>> (&mVariant) ;
		return _CAST_<INDEX_TO_TYPE<ARGC<0> ,ARGVS<UNITS...>>> (r1y) ;
	}

	inline implicit operator const INDEX_TO_TYPE<ARGC<0> ,ARGVS<UNITS...>> & () const {
		return to () ;
	}

	template <class _ARG1>
	inline void apply (const Function<void (_ARG1 &)> &proc) {
		if (!available<_ARG1> ())
			return ;
		auto &r1y = _LOAD_<TEMP<_ARG1>> (&mVariant) ;
		proc (_CAST_<_ARG1> (r1y)) ;
	}

	template <class _ARG1>
	inline void apply (const Function<FIX_MSVC_DEDUCTION_2<void ,_ARG1 &>> &proc) {
		if (!available<_ARG1> ())
			return ;
		auto &r1y = _LOAD_<TEMP<_ARG1>> (&mVariant) ;
		proc (_CAST_<_ARG1> (r1y)) ;
	}

	//@warn: none class shall be base on its address
	inline void address_swap (Variant &that) noexcept popping {
		_SWAP_ (mVariant ,that.mVariant) ;
		_SWAP_ (mIndex ,that.mIndex) ;
	}

private:
	inline explicit Variant (const DEF<decltype (ARGVP0)> &) noexcept :mIndex (VAR_NONE) {}

public:
	inline static Variant nullopt () noexcept {
		return Variant (ARGVP0) ;
	}

private:
	class Detail :private Wrapped<void> {
	public:
		inline static void template_construct (PTR<TEMP<VARIANT>> address ,INDEX index ,const ARGVS<> &) {
			_STATIC_WARNING_ ("noop") ;
		}

		template <class _ARG1 ,class... _ARGS>
		inline static void template_construct (PTR<TEMP<VARIANT>> address ,INDEX index ,const ARGVS<_ARG1 ,_ARGS...> &) {
			_STATIC_ASSERT_ (std::is_nothrow_move_constructible<_ARG1>::value) ;
			_STATIC_ASSERT_ (std::is_nothrow_move_assignable<_ARG1>::value) ;
			const auto r1x = BOOL (index == 0) ;
			for (FOR_ONCE_DO) {
				if (!r1x)
					discard ;
				auto &r2y = _LOAD_<TEMP<_ARG1>> (address) ;
				template_create (_NULL_<ARGV<ARGC<std::is_default_constructible<_ARG1>::value>>> () ,&r2y) ;
			}
			if (r1x)
				return ;
			template_construct (address ,(index - 1) ,_NULL_<ARGVS<_ARGS...>> ()) ;
		}

		inline static void template_destruct (PTR<TEMP<VARIANT>> address ,INDEX index ,const ARGVS<> &) noexcept {
			_STATIC_WARNING_ ("noop") ;
		}

		template <class _ARG1 ,class... _ARGS>
		inline static void template_destruct (PTR<TEMP<VARIANT>> address ,INDEX index ,const ARGVS<_ARG1 ,_ARGS...> &) noexcept {
			_STATIC_ASSERT_ (std::is_nothrow_destructible<_ARG1>::value) ;
			_STATIC_ASSERT_ (std::is_nothrow_move_constructible<_ARG1>::value) ;
			_STATIC_ASSERT_ (std::is_nothrow_move_assignable<_ARG1>::value) ;
			const auto r1x = BOOL (index == 0) ;
			for (FOR_ONCE_DO) {
				if (!r1x)
					discard ;
				auto &r2y = _LOAD_<TEMP<_ARG1>> (address) ;
				_DESTROY_ (&r2y) ;
			}
			if (r1x)
				return ;
			template_destruct (address ,(index - 1) ,_NULL_<ARGVS<_ARGS...>> ()) ;
		}

		inline static void template_copy_construct (PTR<TEMP<VARIANT>> address ,PTR<const TEMP<VARIANT>> that ,INDEX index ,const ARGVS<> &) {
			_STATIC_WARNING_ ("noop") ;
		}

		template <class _ARG1 ,class... _ARGS>
		inline static void template_copy_construct (PTR<TEMP<VARIANT>> address ,PTR<const TEMP<VARIANT>> that ,INDEX index ,const ARGVS<_ARG1 ,_ARGS...> &) {
			const auto r1x = BOOL (index == 0) ;
			for (FOR_ONCE_DO) {
				if (!r1x)
					discard ;
				auto &r2y = _LOAD_<TEMP<_ARG1>> (address) ;
				auto &r3y = _LOAD_<TEMP<_ARG1>> (that) ;
				template_create (_NULL_<ARGV<ARGC<std::is_copy_constructible<_ARG1>::value && std::is_nothrow_move_constructible<_ARG1>::value>>> () ,&r2y ,std::move (_CAST_<_ARG1> (r3y))) ;
			}
			if (r1x)
				return ;
			template_copy_construct (address ,that ,(index - 1) ,_NULL_<ARGVS<_ARGS...>> ()) ;
		}

		inline static void template_move_construct (PTR<TEMP<VARIANT>> address ,PTR<TEMP<VARIANT>> that ,INDEX index ,const ARGVS<> &) noexcept {
			_STATIC_WARNING_ ("noop") ;
		}

		template <class _ARG1 ,class... _ARGS>
		inline static void template_move_construct (PTR<TEMP<VARIANT>> address ,PTR<TEMP<VARIANT>> that ,INDEX index ,const ARGVS<_ARG1 ,_ARGS...> &) noexcept {
			_STATIC_ASSERT_ (std::is_nothrow_move_constructible<_ARG1>::value) ;
			_STATIC_ASSERT_ (std::is_nothrow_move_assignable<_ARG1>::value) ;
			const auto r1x = BOOL (index == 0) ;
			for (FOR_ONCE_DO) {
				if (!r1x)
					discard ;
				auto &r2y = _LOAD_<TEMP<_ARG1>> (address) ;
				auto &r3y = _LOAD_<TEMP<_ARG1>> (that) ;
				template_create (_NULL_<ARGV<ARGC<TRUE>>> () ,&r2y ,std::move (_CAST_<_ARG1> (r3y))) ;
			}
			if (r1x)
				return ;
			template_move_construct (address ,that ,(index - 1) ,_NULL_<ARGVS<_ARGS...>> ()) ;
		}

		template <class _ARG1 ,class... _ARGS>
		inline static void template_create (const ARGV<ARGC<TRUE>> & ,PTR<TEMP<_ARG1>> address ,_ARGS &&...initval) {
			_CREATE_ (address ,std::forward<_ARGS> (initval)...) ;
		}

		template <class _ARG1 ,class... _ARGS>
		inline static void template_create (const ARGV<ARGC<FALSE>> & ,PTR<TEMP<_ARG1>> address ,_ARGS &&...initval) {
			_STATIC_WARNING_ ("unexpected") ;
			_DYNAMIC_ASSERT_ (FALSE) ;
		}
	} ;
} ;

template <class UNIT>
using Optional = Variant<UNIT> ;

template <class...>
class Tuple ;

template <>
class Tuple<> {
public:
	inline constexpr Tuple () = default ;

	inline constexpr LENGTH capacity () const {
		return 0 ;
	}

	inline constexpr BOOL equal (const Tuple &that) const {
		return TRUE ;
	}

	inline constexpr BOOL operator== (const Tuple &that) const {
		return equal (that) ;
	}

	inline constexpr BOOL operator!= (const Tuple &that) const {
		return !equal (that) ;
	}

	inline constexpr FLAG compr (const Tuple &that) const {
		return 0 ;
	}

	inline constexpr BOOL operator< (const Tuple &that) const {
		return BOOL (compr (that) < 0) ;
	}

	inline constexpr BOOL operator>= (const Tuple &that) const {
		return BOOL (compr (that) >= 0) ;
	}

	inline constexpr BOOL operator> (const Tuple &that) const {
		return BOOL (compr (that) > 0) ;
	}

	inline constexpr BOOL operator<= (const Tuple &that) const {
		return BOOL (compr (that) <= 0) ;
	}
} ;

template <class UNIT1 ,class... UNITS>
class Tuple<UNIT1 ,UNITS...> :private Tuple<UNITS...> {
private:
	_STATIC_ASSERT_ (!std::is_rvalue_reference<UNIT1>::value) ;
	class Detail ;
	template <class...>
	friend class Tuple ;
	UNIT1 mData ;

public:
	inline constexpr Tuple () = default ;

	inline constexpr implicit Tuple (FORWARD_TRAITS_TYPE<UNIT1> &&_one ,FORWARD_TRAITS_TYPE<UNITS> &&..._rest) :Tuple<UNITS...> (std::forward<FORWARD_TRAITS_TYPE<UNITS>> (_rest)...) ,mData (std::forward<FORWARD_TRAITS_TYPE<UNIT1>> (_one)) {}

	inline constexpr LENGTH capacity () const {
		return 1 + rest ().capacity () ;
	}

	inline UNIT1 &one () & {
		return mData ;
	}

	inline constexpr const UNIT1 &one () const & {
		return mData ;
	}

	inline UNIT1 &one () && = delete ;

	inline Tuple<UNITS...> &rest () & {
		return (*this) ;
	}

	inline constexpr const Tuple<UNITS...> &rest () const & {
		return (*this) ;
	}

	inline Tuple<UNITS...> &rest () && = delete ;

	template <class _RET>
	inline INDEX_TO_TYPE<_RET ,ARGVS<UNIT1 ,UNITS...>> &pick () & {
		return Detail::template_pick ((*this) ,_NULL_<ARGV<_RET>> ()) ;
	}

	template <class _RET>
	inline constexpr const INDEX_TO_TYPE<_RET ,ARGVS<UNIT1 ,UNITS...>> &pick () const & {
		return Detail::template_pick ((*this) ,_NULL_<ARGV<_RET>> ()) ;
	}

	template <class _RET>
	inline INDEX_TO_TYPE<_RET ,ARGVS<UNIT1 ,UNITS...>> &pick () && = delete ;

	inline BOOL equal (const Tuple &that) const {
		if (one () != that.one ())
			return FALSE ;
		if (rest () != that.rest ())
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const Tuple &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const Tuple &that) const {
		return !equal (that) ;
	}

	inline FLAG compr (const Tuple &that) const {
		const auto r1x = _MEMCOMPR_ (PTRTOARR[&one ()] ,PTRTOARR[&that.one ()] ,1) ;
		if (r1x != 0)
			return r1x ;
		return rest ().compr (that.rest ()) ;
	}

	inline BOOL operator< (const Tuple &that) const {
		return BOOL (compr (that) < 0) ;
	}

	inline BOOL operator>= (const Tuple &that) const {
		return BOOL (compr (that) >= 0) ;
	}

	inline BOOL operator> (const Tuple &that) const {
		return BOOL (compr (that) > 0) ;
	}

	inline BOOL operator<= (const Tuple &that) const {
		return BOOL (compr (that) <= 0) ;
	}

private:
	class Detail :private Wrapped<void> {
	public:
		inline static UNIT1 &template_pick (Tuple &_self ,const ARGV<ARGC<0>> &) {
			return _self.one () ;
		}

		template <class _ARG1>
		inline static INDEX_TO_TYPE<_ARG1 ,ARGVS<UNIT1 ,UNITS...>> &template_pick (Tuple &_self ,const ARGV<_ARG1> &) {
			_STATIC_ASSERT_ (LENGTH (_ARG1::value) > 0 && LENGTH (_ARG1::value) < 1 + _CAPACITYOF_ (UNITS)) ;
			return Tuple<UNITS...>::template_pick (_self.rest () ,_NULL_<ARGV<ARGC<_ARG1::value - 1>>> ()) ;
		}

		inline static constexpr const UNIT1 &template_pick (const Tuple &_self ,const ARGV<ARGC<0>> &) {
			return _self.one () ;
		}

		template <class _ARG1>
		inline static constexpr const INDEX_TO_TYPE<_ARG1 ,ARGVS<UNIT1 ,UNITS...>> &template_pick (const Tuple &_self ,const ARGV<_ARG1> &) {
			_STATIC_ASSERT_ (LENGTH (_ARG1::value) > 0 && LENGTH (_ARG1::value) < 1 + _CAPACITYOF_ (UNITS)) ;
			return Tuple<UNITS...>::template_pick (_self.rest () ,_NULL_<ARGV<ARGC<_ARG1::value - 1>>> ()) ;
		}
	} ;
} ;

template <class... UNITS>
using TupleBinder = Tuple<UNITS &...> ;

template <class UNIT1 ,class... UNITS>
template <class... _UNITS>
class Function<UNIT1 (UNITS...)>::ImplHolder<PTR<UNIT1 (UNITS... ,_UNITS...)>> :public Function<UNIT1 (UNITS...)>::Holder {
private:
	class Detail ;
	PTR<UNIT1 (UNITS... ,_UNITS...)> mFunction ;
	Tuple<REMOVE_CVR_TYPE<_UNITS>...> mParameter ;

public:
	inline ImplHolder () = delete ;

	inline explicit ImplHolder (const PTR<UNIT1 (UNITS... ,_UNITS...)> &func ,const REMOVE_CVR_TYPE<_UNITS> &...parameter) :mFunction (func) ,mParameter (parameter...) {}

	inline UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const popping override {
		return Detail::template_apply (mFunction ,mParameter ,std::forward<FORWARD_TRAITS_TYPE<UNITS>> (funcval)...) ;
	}
} ;

template <class UNIT1 ,class... UNITS>
template <class... _UNITS>
class Function<UNIT1 (UNITS...)>::ImplHolder<PTR<UNIT1 (UNITS... ,_UNITS...)>>::Detail :private Wrapped<void> {
public:
	//@error: vs2015 is too useless to compile without hint
	inline static UNIT1 template_apply (const PTR<UNIT1 (UNITS... ,_UNITS...)> &func ,const Tuple<> &parameter ,FORWARD_TRAITS_TYPE<UNITS> &&...funcval ,const REMOVE_CVR_TYPE<_UNITS> &..._fill) popping {
		const auto r1x = Function<UNIT1 (UNITS... ,_UNITS...)> (func) ;
		return r1x (std::forward<FORWARD_TRAITS_TYPE<UNITS>> (funcval)... ,_fill...) ;
	}

	//@error: vs2015 is too useless to compile without hint
	template <class _ARG1 ,class... _ARGS>
	inline static UNIT1 template_apply (const PTR<UNIT1 (UNITS... ,_UNITS...)> &func ,const _ARG1 &parameter ,_ARGS &&...funcval) popping {
		return template_apply (func ,parameter.rest () ,std::forward<_ARGS> (funcval)... ,parameter.one ()) ;
	}
} ;

template <class UNIT1 ,class... UNITS>
template <class... _ARGS>
inline Function<UNIT1 (UNITS...)> Function<UNIT1 (UNITS...)>::make (const PTR<UNIT1 (UNITS... ,_ARGS...)> &func ,const REMOVE_CVR_TYPE<_ARGS> &...parameter) {
	auto rax = GlobalHeap::alloc<TEMP<ImplHolder<PTR<UNIT1 (UNITS... ,_ARGS...)>>>> () ;
	ScopedBuild<ImplHolder<PTR<UNIT1 (UNITS... ,_ARGS...)>>> ANONYMOUS (rax ,func ,parameter...) ;
	auto &r1y = _LOAD_<ImplHolder<PTR<UNIT1 (UNITS... ,_ARGS...)>>> (_XVALUE_<PTR<TEMP<ImplHolder<PTR<UNIT1 (UNITS... ,_ARGS...)>>>>> (rax)) ;
	Function ret = Function (ARGVP0 ,_XVALUE_<PTR<Holder>> (&r1y)) ;
	rax = NULL ;
	return std::move (ret) ;
}

template <class...>
class AllOfTuple ;

template <class...>
class AnyOfTuple ;

template <class... UNITS>
class AllOfTuple final :private TupleBinder<const UNITS...> {
private:
	_STATIC_ASSERT_ (_CAPACITYOF_ (UNITS) > 0) ;
	_STATIC_ASSERT_ (stl::is_all_same<UNITS...>::value) ;
	class Detail ;

public:
	inline AllOfTuple () = delete ;

	inline AllOfTuple (const AllOfTuple &) = delete ;
	inline AllOfTuple &operator= (const AllOfTuple &) = delete ;

	inline AllOfTuple (AllOfTuple &&) noexcept = default ;
	inline AllOfTuple &operator= (AllOfTuple &&) = delete ;

	inline implicit operator BOOL () && {
		return Detail::template_boolean (_XVALUE_<TupleBinder<const UNITS...>> ((*this))) ;
	}

	template <class _ARG1>
	inline BOOL operator== (const _ARG1 &that) && {
		return Detail::template_equal (_XVALUE_<TupleBinder<const UNITS...>> ((*this)) ,that) ;
	}

	template <class _ARG1>
	inline friend BOOL operator== (const _ARG1 &lhs ,AllOfTuple &&rhs) {
		return std::move (rhs) == lhs ;
	}

	template <class _ARG1>
	inline BOOL operator!= (const _ARG1 &that) && {
		return Detail::template_not_equal (_XVALUE_<TupleBinder<const UNITS...>> ((*this)) ,that) ;
	}

	template <class _ARG1>
	inline friend BOOL operator!= (const _ARG1 &lhs ,AllOfTuple &&rhs) {
		return std::move (rhs) != lhs ;
	}

	template <class _ARG1>
	inline BOOL operator< (const _ARG1 &that) && {
		return Detail::template_less (_XVALUE_<TupleBinder<const UNITS...>> ((*this)) ,that) ;
	}

	template <class _ARG1>
	inline friend BOOL operator< (const _ARG1 &lhs ,AllOfTuple &&rhs) {
		return std::move (rhs) > lhs ;
	}

	template <class _ARG1>
	inline BOOL operator>= (const _ARG1 &that) && {
		return Detail::template_not_less (_XVALUE_<TupleBinder<const UNITS...>> ((*this)) ,that) ;
	}

	template <class _ARG1>
	inline friend BOOL operator>= (const _ARG1 &lhs ,AllOfTuple &&rhs) {
		return std::move (rhs) <= lhs ;
	}

	template <class _ARG1>
	inline BOOL operator> (const _ARG1 &that) && {
		return Detail::template_less (that ,_XVALUE_<TupleBinder<const UNITS...>> ((*this))) ;
	}

	template <class _ARG1>
	inline friend BOOL operator> (const _ARG1 &lhs ,AllOfTuple &&rhs) {
		return std::move (rhs) < lhs ;
	}

	template <class _ARG1>
	inline BOOL operator<= (const _ARG1 &that) && {
		return Detail::template_not_less (that ,_XVALUE_<TupleBinder<const UNITS...>> ((*this))) ;
	}

	template <class _ARG1>
	inline friend BOOL operator<= (const _ARG1 &lhs ,AllOfTuple &&rhs) {
		return std::move (rhs) >= lhs ;
	}

private:
	class Detail :private Wrapped<void> {
	public:
		template <class _ARG1 ,class _ARG2>
		inline static BOOL operator_equal (const _ARG1 &lhs ,const _ARG2 &rhs) {
			return BOOL (lhs == rhs) ;
		}

		template <class _ARG1 ,class... _ARGS>
		inline static BOOL operator_equal (const _ARG1 &lhs ,const AllOfTuple<_ARGS...> &rhs) {
			return BOOL (rhs == lhs) ;
		}

		template <class _ARG1 ,class... _ARGS>
		inline static BOOL operator_equal (const _ARG1 &lhs ,const AnyOfTuple<_ARGS...> &rhs) {
			return BOOL (rhs == lhs) ;
		}

		template <class _ARG1 ,class _ARG2>
		inline static BOOL operator_less (const _ARG1 &lhs ,const _ARG2 &rhs) {
			return BOOL (lhs < rhs) ;
		}

		template <class _ARG1 ,class... _ARGS>
		inline static BOOL operator_less (const _ARG1 &lhs ,const AllOfTuple<_ARGS...> &rhs) {
			return BOOL (rhs > lhs) ;
		}

		template <class _ARG1 ,class... _ARGS>
		inline static BOOL operator_less (const _ARG1 &lhs ,const AnyOfTuple<_ARGS...> &rhs) {
			return BOOL (rhs > lhs) ;
		}

		template <class _ARG1>
		inline static BOOL template_boolean (const Tuple<_ARG1> &lhs) {
			_STATIC_ASSERT_ (std::is_same<REMOVE_CVR_TYPE<_ARG1> ,BOOL>::value) ;
			return BOOL (lhs.one ()) ;
		}

		template <class _ARG1 ,class... _ARGS>
		inline static BOOL template_boolean (const Tuple<_ARG1 ,_ARGS...> &lhs) {
			_STATIC_ASSERT_ (std::is_same<REMOVE_CVR_TYPE<_ARG1> ,BOOL>::value) ;
			if (!(lhs.one ()))
				return FALSE ;
			if (!template_boolean (lhs.rest ()))
				return FALSE ;
			return TRUE ;
		}

		template <class _ARG1 ,class _ARG2>
		inline static BOOL template_equal (const Tuple<_ARG1> &lhs ,const _ARG2 &rhs) {
			return operator_equal (lhs.one () ,rhs) ;
		}

		template <class _ARG1 ,class _ARG2 ,class... _ARGS>
		inline static BOOL template_equal (const Tuple<_ARG1 ,_ARG1 ,_ARGS...> &lhs ,const _ARG2 &rhs) {
			if (!operator_equal (lhs.one () ,rhs))
				return FALSE ;
			if (!template_equal (lhs.rest () ,rhs))
				return FALSE ;
			return TRUE ;
		}

		template <class _ARG1 ,class _ARG2>
		inline static BOOL template_not_equal (const Tuple<_ARG1> &lhs ,const _ARG2 &rhs) {
			return !operator_equal (lhs.one () ,rhs) ;
		}

		template <class _ARG1 ,class _ARG2 ,class... _ARGS>
		inline static BOOL template_not_equal (const Tuple<_ARG1 ,_ARG1 ,_ARGS...> &lhs ,const _ARG2 &rhs) {
			if (operator_equal (lhs.one () ,rhs))
				return FALSE ;
			if (!template_not_equal (lhs.rest () ,rhs))
				return FALSE ;
			return TRUE ;
		}

		template <class _ARG1 ,class _ARG2>
		inline static BOOL template_less (const Tuple<_ARG1> &lhs ,const _ARG2 &rhs) {
			return operator_less (lhs.one () ,rhs) ;
		}

		template <class _ARG1 ,class _ARG2 ,class... _ARGS>
		inline static BOOL template_less (const Tuple<_ARG1 ,_ARG1 ,_ARGS...> &lhs ,const _ARG2 &rhs) {
			if (!operator_less (lhs.one () ,rhs))
				return FALSE ;
			if (!template_less (lhs.rest () ,rhs))
				return FALSE ;
			return TRUE ;
		}

		template <class _ARG1 ,class _ARG2>
		inline static BOOL template_not_less (const Tuple<_ARG1> &lhs ,const _ARG2 &rhs) {
			return !operator_less (lhs.one () ,rhs) ;
		}

		template <class _ARG1 ,class _ARG2 ,class... _ARGS>
		inline static BOOL template_not_less (const Tuple<_ARG1 ,_ARG1 ,_ARGS...> &lhs ,const _ARG2 &rhs) {
			if (operator_less (lhs.one () ,rhs))
				return FALSE ;
			if (!template_not_less (lhs.rest () ,rhs))
				return FALSE ;
			return TRUE ;
		}

		template <class _ARG1 ,class _ARG2>
		inline static BOOL template_less (const _ARG2 &lhs ,const Tuple<_ARG1> &rhs) {
			return operator_less (lhs ,rhs.one ()) ;
		}

		template <class _ARG1 ,class _ARG2 ,class... _ARGS>
		inline static BOOL template_less (const _ARG2 &lhs ,const Tuple<_ARG1 ,_ARG1 ,_ARGS...> &rhs) {
			if (!operator_less (lhs ,rhs.one ()))
				return FALSE ;
			if (!template_less (lhs ,rhs.rest ()))
				return FALSE ;
			return TRUE ;
		}

		template <class _ARG1 ,class _ARG2>
		inline static BOOL template_not_less (const _ARG2 &lhs ,const Tuple<_ARG1> &rhs) {
			return !operator_less (lhs ,rhs.one ()) ;
		}

		template <class _ARG1 ,class _ARG2 ,class... _ARGS>
		inline static BOOL template_not_less (const _ARG2 &lhs ,const Tuple<_ARG1 ,_ARG1 ,_ARGS...> &rhs) {
			if (operator_less (lhs ,rhs.one ()))
				return FALSE ;
			if (!template_not_less (lhs ,rhs.rest ()))
				return FALSE ;
			return TRUE ;
		}
	} ;
} ;

template <class... UNITS>
class AnyOfTuple final :private TupleBinder<const UNITS...> {
private:
	_STATIC_ASSERT_ (_CAPACITYOF_ (UNITS) > 0) ;
	_STATIC_ASSERT_ (stl::is_all_same<UNITS...>::value) ;
	class Detail ;

public:
	inline AnyOfTuple () = delete ;

	inline AnyOfTuple (const AnyOfTuple &) = delete ;
	inline AnyOfTuple &operator= (const AnyOfTuple &) = delete ;

	inline AnyOfTuple (AnyOfTuple &&) noexcept = default ;
	inline AnyOfTuple &operator= (AnyOfTuple &&) = delete ;

	inline implicit operator BOOL () && {
		return Detail::template_boolean (_XVALUE_<TupleBinder<const UNITS...>> ((*this))) ;
	}

	template <class _ARG1>
	inline BOOL operator== (const _ARG1 &that) && {
		return Detail::template_equal (_XVALUE_<TupleBinder<const UNITS...>> ((*this)) ,that) ;
	}

	template <class _ARG1>
	inline friend BOOL operator== (const _ARG1 &lhs ,AnyOfTuple &&rhs) {
		return std::move (rhs) == lhs ;
	}

	template <class _ARG1>
	inline BOOL operator!= (const _ARG1 &that) && {
		return Detail::template_not_equal (_XVALUE_<TupleBinder<const UNITS...>> ((*this)) ,that) ;
	}

	template <class _ARG1>
	inline friend BOOL operator!= (const _ARG1 &lhs ,AnyOfTuple &&rhs) {
		return std::move (rhs) != lhs ;
	}

	template <class _ARG1>
	inline BOOL operator< (const _ARG1 &that) && {
		return Detail::template_less (_XVALUE_<TupleBinder<const UNITS...>> ((*this)) ,that) ;
	}

	template <class _ARG1>
	inline friend BOOL operator< (const _ARG1 &lhs ,AnyOfTuple &&rhs) {
		return std::move (rhs) > lhs ;
	}

	template <class _ARG1>
	inline BOOL operator>= (const _ARG1 &that) && {
		return Detail::template_not_less (_XVALUE_<TupleBinder<const UNITS...>> ((*this)) ,that) ;
	}

	template <class _ARG1>
	inline friend BOOL operator>= (const _ARG1 &lhs ,AnyOfTuple &&rhs) {
		return std::move (rhs) <= lhs ;
	}

	template <class _ARG1>
	inline BOOL operator> (const _ARG1 &that) && {
		return Detail::template_less (that ,_XVALUE_<TupleBinder<const UNITS...>> ((*this))) ;
	}

	template <class _ARG1>
	inline friend BOOL operator> (const _ARG1 &lhs ,AnyOfTuple &&rhs) {
		return std::move (rhs) < lhs ;
	}

	template <class _ARG1>
	inline BOOL operator<= (const _ARG1 &that) && {
		return Detail::template_not_less (that ,_XVALUE_<TupleBinder<const UNITS...>> ((*this))) ;
	}

	template <class _ARG1>
	inline friend BOOL operator<= (const _ARG1 &lhs ,AnyOfTuple &&rhs) {
		return std::move (rhs) >= lhs ;
	}

private:
	class Detail :private Wrapped<void> {
	public:
		template <class _ARG1 ,class _ARG2>
		inline static BOOL operator_equal (const _ARG1 &lhs ,const _ARG2 &rhs) {
			return BOOL (lhs == rhs) ;
		}

		template <class _ARG1 ,class... _ARGS>
		inline static BOOL operator_equal (const _ARG1 &lhs ,const AllOfTuple<_ARGS...> &rhs) {
			return BOOL (rhs == lhs) ;
		}

		template <class _ARG1 ,class... _ARGS>
		inline static BOOL operator_equal (const _ARG1 &lhs ,const AnyOfTuple<_ARGS...> &rhs) {
			return BOOL (rhs == lhs) ;
		}

		template <class _ARG1 ,class _ARG2>
		inline static BOOL operator_less (const _ARG1 &lhs ,const _ARG2 &rhs) {
			return BOOL (lhs < rhs) ;
		}

		template <class _ARG1 ,class... _ARGS>
		inline static BOOL operator_less (const _ARG1 &lhs ,const AllOfTuple<_ARGS...> &rhs) {
			return BOOL (rhs > lhs) ;
		}

		template <class _ARG1 ,class... _ARGS>
		inline static BOOL operator_less (const _ARG1 &lhs ,const AnyOfTuple<_ARGS...> &rhs) {
			return BOOL (rhs > lhs) ;
		}

		template <class _ARG1>
		inline static BOOL template_boolean (const Tuple<_ARG1> &lhs) {
			_STATIC_ASSERT_ (std::is_same<REMOVE_CVR_TYPE<_ARG1> ,BOOL>::value) ;
			return BOOL (lhs.one ()) ;
		}

		template <class _ARG1 ,class... _ARGS>
		inline static BOOL template_boolean (const Tuple<_ARG1 ,_ARGS...> &lhs) {
			_STATIC_ASSERT_ (std::is_same<REMOVE_CVR_TYPE<_ARG1> ,BOOL>::value) ;
			if (lhs.one ())
				return TRUE ;
			if (!template_boolean (lhs.rest ()))
				return FALSE ;
			return TRUE ;
		}

		template <class _ARG1 ,class _ARG2>
		inline static BOOL template_equal (const Tuple<_ARG1> &lhs ,const _ARG2 &rhs) {
			return operator_equal (lhs.one () ,rhs) ;
		}

		template <class _ARG1 ,class _ARG2 ,class... _ARGS>
		inline static BOOL template_equal (const Tuple<_ARG1 ,_ARG1 ,_ARGS...> &lhs ,const _ARG2 &rhs) {
			if (operator_equal (lhs.one () ,rhs))
				return TRUE ;
			if (!template_equal (lhs.rest () ,rhs))
				return FALSE ;
			return TRUE ;
		}

		template <class _ARG1 ,class _ARG2>
		inline static BOOL template_not_equal (const Tuple<_ARG1> &lhs ,const _ARG2 &rhs) {
			return !operator_equal (lhs.one () ,rhs) ;
		}

		template <class _ARG1 ,class _ARG2 ,class... _ARGS>
		inline static BOOL template_not_equal (const Tuple<_ARG1 ,_ARG1 ,_ARGS...> &lhs ,const _ARG2 &rhs) {
			if (!operator_equal (lhs.one () ,rhs))
				return TRUE ;
			if (!template_not_equal (lhs.rest () ,rhs))
				return FALSE ;
			return TRUE ;
		}

		template <class _ARG1 ,class _ARG2>
		inline static BOOL template_less (const Tuple<_ARG1> &lhs ,const _ARG2 &rhs) {
			return operator_less (lhs.one () ,rhs) ;
		}

		template <class _ARG1 ,class _ARG2 ,class... _ARGS>
		inline static BOOL template_less (const Tuple<_ARG1 ,_ARG1 ,_ARGS...> &lhs ,const _ARG2 &rhs) {
			if (operator_less (lhs.one () ,rhs))
				return TRUE ;
			if (!template_less (lhs.rest () ,rhs))
				return FALSE ;
			return TRUE ;
		}

		template <class _ARG1 ,class _ARG2>
		inline static BOOL template_not_less (const Tuple<_ARG1> &lhs ,const _ARG2 &rhs) {
			return !operator_less (lhs.one () ,rhs) ;
		}

		template <class _ARG1 ,class _ARG2 ,class... _ARGS>
		inline static BOOL template_not_less (const Tuple<_ARG1 ,_ARG1 ,_ARGS...> &lhs ,const _ARG2 &rhs) {
			if (!operator_less (lhs.one () ,rhs))
				return TRUE ;
			if (!template_not_less (lhs.rest () ,rhs))
				return FALSE ;
			return TRUE ;
		}

		template <class _ARG1 ,class _ARG2>
		inline static BOOL template_less (const _ARG2 &lhs ,const Tuple<_ARG1> &rhs) {
			return operator_less (lhs ,rhs.one ()) ;
		}

		template <class _ARG1 ,class _ARG2 ,class... _ARGS>
		inline static BOOL template_less (const _ARG2 &lhs ,const Tuple<_ARG1 ,_ARG1 ,_ARGS...> &rhs) {
			if (operator_less (lhs ,rhs.one ()))
				return TRUE ;
			if (!template_less (lhs ,rhs.rest ()))
				return FALSE ;
			return TRUE ;
		}

		template <class _ARG1 ,class _ARG2>
		inline static BOOL template_not_less (const _ARG2 &lhs ,const Tuple<_ARG1> &rhs) {
			return !operator_less (lhs ,rhs.one ()) ;
		}

		template <class _ARG1 ,class _ARG2 ,class... _ARGS>
		inline static BOOL template_not_less (const _ARG2 &lhs ,const Tuple<_ARG1 ,_ARG1 ,_ARGS...> &rhs) {
			if (!operator_less (lhs ,rhs.one ()))
				return TRUE ;
			if (!template_not_less (lhs ,rhs.rest ()))
				return FALSE ;
			return TRUE ;
		}
	} ;
} ;

namespace S {
template <class... _ARGS>
inline static AllOfTuple<_ARGS...> _ALLOF_ (const _ARGS &...list) {
	_STATIC_ASSERT_ (_CAPACITYOF_ (_ARGS) > 0) ;
	TupleBinder<const _ARGS...> ret = TupleBinder<const _ARGS...> (list...) ;
	return std::move (_CAST_<AllOfTuple<_ARGS...>> (ret)) ;
}

template <class... _ARGS>
inline static AnyOfTuple<_ARGS...> _ANYOF_ (const _ARGS &...list) {
	_STATIC_ASSERT_ (_CAPACITYOF_ (_ARGS) > 0) ;
	TupleBinder<const _ARGS...> ret = TupleBinder<const _ARGS...> (list...) ;
	return std::move (_CAST_<AnyOfTuple<_ARGS...>> (ret)) ;
}
} ;

template <class UNIT>
class LinkedRef {
private:
	class Node {
	private:
		friend LinkedRef ;
		UNIT mData ;
		PTR<class Node> mPrev ;
		PTR<class Node> mNext ;

	public:
		inline Node () = default ;
	} ;

private:
	PTR<Node> mRoot ;

public:
	inline LinkedRef () noexcept {
		mRoot = NULL ;
	}

	inline ~LinkedRef () noexcept {
		if (mRoot == NULL)
			return ;
		_DEBUG_ASSERT_ (mRoot->mPrev != NULL) ;
		mRoot->mPrev->mNext = NULL ;
		mRoot->mPrev = NULL ;
		for (PTR<Node> i = mRoot ,it ; i != NULL ; i = it) {
			it = i->mNext ;
			i->~Node () ;
			GlobalHeap::free (i) ;
		}
		mRoot = NULL ;
	}

	inline LinkedRef (const LinkedRef &) = delete ;
	inline LinkedRef &operator= (const LinkedRef &) = delete ;

	inline LinkedRef (LinkedRef &&that) noexcept {
		mRoot = _EXCHANGE_ (that.mRoot) ;
	}

	inline LinkedRef &operator= (LinkedRef &&that) noexcept {
		for (FOR_ONCE_DO) {
			if (this == &that)
				discard ;
			(*this).~LinkedRef () ;
			new (this) LinkedRef (std::move (that)) ;
		}
		return (*this) ;
	}

	inline BOOL exist () const {
		if (mRoot == NULL)
			return FALSE ;
		return TRUE ;
	}

	inline UNIT &to () {
		_DEBUG_ASSERT_ (exist ()) ;
		return mRoot->mData ;
	}

	inline implicit operator UNIT & () {
		return to () ;
	}

	inline PTR<UNIT> operator-> () {
		return &to () ;
	}

	inline const UNIT &to () const {
		_DEBUG_ASSERT_ (exist ()) ;
		return mRoot->mData ;
	}

	inline implicit operator const UNIT & () const {
		return to () ;
	}

	inline PTR<const UNIT> operator-> () const {
		return &to () ;
	}

	inline void push () {
		auto rax = GlobalHeap::alloc<TEMP<Node>> () ;
		ScopedBuild<Node> ANONYMOUS (rax) ;
		auto &r1y = _LOAD_<Node> (_XVALUE_<PTR<TEMP<Node>>> (rax)) ;
		auto fax = FALSE ;
		if SWITCH_CASE (fax) {
			if (!(mRoot == NULL))
				discard ;
			r1y.mPrev = &r1y ;
			r1y.mNext = &r1y ;
		}
		if SWITCH_CASE (fax) {
			if (!(mRoot != NULL))
				discard ;
			_DEBUG_ASSERT_ (mRoot->mPrev != NULL) ;
			r1y.mPrev = mRoot->mPrev ;
			r1y.mNext = mRoot ;
			mRoot->mPrev->mNext = &r1y ;
			mRoot->mPrev = &r1y ;
		}
		mRoot = &r1y ;
		rax = NULL ;
	}

	inline void cycle () {
		_DEBUG_ASSERT_ (exist ()) ;
		mRoot = mRoot->mNext ;
	}
} ;

template <class>
class StrongRef ;

template <class>
class WeakRef ;

template <class>
class SoftRef ;

template <>
class WeakRef<void> {
public:
	class Virtual ;

private:
	class Holder {
	private:
		template <class>
		friend class StrongRef ;
		template <class>
		friend class WeakRef ;
		AnyRef<void> mData ;
		LENGTH mCounter ;
	} ;

private:
	template <class>
	friend class StrongRef ;
	template <class>
	friend class WeakRef ;
	SharedRef<Holder> mHolder ;
} ;

class WeakRef<void>::Virtual :public virtual WeakRef<void> {
private:
	template <class>
	friend class StrongRef ;
} ;

template <class UNIT>
class StrongRef {
private:
	using Holder = typename WeakRef<void>::Holder ;

private:
	class Detail ;
	template <class>
	friend class StrongRef ;
	friend WeakRef<UNIT> ;
	friend SoftRef<UNIT> ;
	SharedRef<Holder> mHolder ;
	PTR<UNIT> mPointer ;

public:
	inline StrongRef () noexcept {
		mPointer = NULL ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<std::is_same<_ARG1 ,PTR<UNIT>>::value>>
	inline explicit StrongRef (const _ARG1 &that) :StrongRef () {
		_STATIC_ASSERT_ (stl::is_always_base_of<WeakRef<void>::Virtual ,UNIT>::value) ;
		_DEBUG_ASSERT_ (that != NULL) ;
		const auto r1x = _XVALUE_<PTR<CAST_TRAITS_TYPE<WeakRef<void>::Virtual ,UNIT>>> (that) ;
		const auto r2x = _XVALUE_<PTR<CAST_TRAITS_TYPE<WeakRef<void> ,UNIT>>> (r1x) ;
		mHolder = r2x->mHolder ;
		mPointer = that ;
	}

	//@warn: circular reference ruins StrongRef
	template <class _ARG1 ,class = ENABLE_TYPE<stl::is_always_base_of<UNIT ,_ARG1>::value>>
	inline implicit StrongRef (const StrongRef<_ARG1> &that) : StrongRef (that.template recast<UNIT> ()) {}

	inline implicit StrongRef (const WeakRef<UNIT> &that) ;

	inline implicit StrongRef (const SoftRef<UNIT> &that) ;

	inline ~StrongRef () noexcept {
		if (mPointer == NULL)
			return ;
		if (!mHolder.exist ())
			return ;
		if (!mHolder->mData.exist ())
			return ;
		for (FOR_ONCE_DO) {
			const auto r1x = --mHolder->mCounter ;
			if (r1x != 0)
				discard ;
			mHolder->mData = AnyRef<void> () ;
		}
		mPointer = NULL ;
	}

	inline StrongRef (const StrongRef &that) :StrongRef (that.mHolder ,that.mPointer) {
		_STATIC_WARNING_ ("noop") ;
	}

	inline StrongRef &operator= (const StrongRef &that) {
		for (FOR_ONCE_DO) {
			if (this == &that)
				discard ;
			(*this).~StrongRef () ;
			new (this) StrongRef (std::move (that)) ;
		}
		return (*this) ;
	}

	inline StrongRef (StrongRef &&that) noexcept {
		mHolder = std::move (that.mHolder) ;
		mPointer = _EXCHANGE_ (that.mPointer) ;
	}

	inline StrongRef &operator= (StrongRef &&that) noexcept {
		for (FOR_ONCE_DO) {
			if (this == &that)
				discard ;
			(*this).~StrongRef () ;
			new (this) StrongRef (std::move (that)) ;
		}
		return (*this) ;
	}

	inline BOOL exist () const {
		if (mPointer == NULL)
			return FALSE ;
		if (!mHolder.exist ())
			return FALSE ;
		if (!mHolder->mData.exist ())
			return FALSE ;
		return TRUE ;
	}

	template <class _RET>
	inline StrongRef<CAST_TRAITS_TYPE<_RET ,UNIT>> recast () const {
		_STATIC_ASSERT_ (!std::is_reference<_RET>::value) ;
		const auto r1x = Detail::template_recast (mPointer ,_NULL_<ARGV<CAST_TRAITS_TYPE<_RET ,UNIT>>> () ,ARGVPX ,ARGVP9) ;
		_DYNAMIC_ASSERT_ (EFLAG (r1x != NULL) == EFLAG (mPointer != NULL)) ;
		return StrongRef<CAST_TRAITS_TYPE<_RET ,UNIT>> (mHolder ,r1x) ;
	}

	inline UNIT &to () const {
		_DEBUG_ASSERT_ (exist ()) ;
		return _LOAD_<UNIT> (mPointer) ;
	}

	inline implicit operator UNIT & () const {
		return to () ;
	}

	inline PTR<UNIT> operator-> () const {
		return &to () ;
	}

	inline BOOL equal (const StrongRef &that) const {
		if (!mHolder.exist () && !that.mHolder.exist ())
			return TRUE ;
		if (!mHolder.exist ())
			return FALSE ;
		if (!that.mHolder.exist ())
			return FALSE ;
		if (&mHolder.self != &that.mHolder.self)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const StrongRef &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const StrongRef &that) const {
		return !equal (that) ;
	}

	inline BOOL equal (const WeakRef<UNIT> &that) const ;

	inline BOOL operator== (const WeakRef<UNIT> &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const WeakRef<UNIT> &that) const {
		return !equal (that) ;
	}

	inline BOOL equal (const SoftRef<UNIT> &that) const ;

	inline BOOL operator== (const SoftRef<UNIT> &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const SoftRef<UNIT> &that) const {
		return !equal (that) ;
	}

private:
	inline explicit StrongRef (const SharedRef<Holder> &holder ,PTR<UNIT> pointer) :StrongRef () {
		if (pointer == NULL)
			return ;
		if (!holder.exist ())
			return ;
		if (!holder->mData.exist ())
			return ;
		const auto r1x = ++holder->mCounter ;
		_DEBUG_ASSERT_ (r1x > 0) ;
		(void) r1x ;
		mHolder = holder ;
		mPointer = pointer ;
	}

public:
	template <class... _ARGS>
	inline static StrongRef make (_ARGS &&...initval) {
		auto rax = SharedRef<Holder>::make () ;
		rax->mData = AnyRef<REMOVE_CVR_TYPE<UNIT>>::make (std::forward<_ARGS> (initval)...) ;
		rax->mCounter = 0 ;
		auto &r1y = rax->mData.rebind<REMOVE_CVR_TYPE<UNIT>> ().self ;
		Detail::template_shared (rax ,&r1y ,ARGVPX ,ARGVP9) ;
		return StrongRef (rax ,&r1y) ;
	}

private:
	class Detail :private Wrapped<void> {
	public:
		template <class _ARG1>
		inline static void template_shared (const SharedRef<Holder> &holder ,PTR<_ARG1> _this ,const ARGV<ENABLE_TYPE<stl::is_always_base_of<WeakRef<void>::Virtual ,_ARG1>::value>> & ,const DEF<decltype (ARGVP2)> &) {
			_DEBUG_ASSERT_ (_this != NULL) ;
			const auto r1x = _XVALUE_<PTR<CAST_TRAITS_TYPE<WeakRef<void>::Virtual ,_ARG1>>> (_this) ;
			const auto r2x = _XVALUE_<PTR<CAST_TRAITS_TYPE<WeakRef<void> ,_ARG1>>> (r1x) ;
			r2x->mHolder = holder ;
		}

		template <class _ARG1>
		inline static void template_shared (const SharedRef<Holder> &holder ,PTR<_ARG1> _this ,const DEF<decltype (ARGVPX)> & ,const DEF<decltype (ARGVP1)> &) {
			_DEBUG_ASSERT_ (_this != NULL) ;
		}

		template <class _ARG1>
		inline static PTR<_ARG1> template_recast (PTR<UNIT> pointer ,const ARGV<_ARG1> & ,const ARGV<ENABLE_TYPE<stl::is_always_base_of<_ARG1 ,UNIT>::value>> & ,const DEF<decltype (ARGVP3)> &) {
			return _XVALUE_<PTR<_ARG1>> (pointer) ;
		}

		template <class _ARG1>
		inline static PTR<_ARG1> template_recast (PTR<UNIT> pointer ,const ARGV<_ARG1> & ,const ARGV<ENABLE_TYPE<stl::is_always_base_of<Interface ,UNIT>::value && stl::is_always_base_of<Interface ,_ARG1>::value>> & ,const DEF<decltype (ARGVP2)> &) {
			//@warn: RTTI might be different across DLL
			return dynamic_cast<PTR<_ARG1>> (pointer) ;
		}

		template <class _ARG1>
		inline static PTR<_ARG1> template_recast (PTR<UNIT> pointer ,const ARGV<_ARG1> & ,const DEF<decltype (ARGVPX)> & ,const DEF<decltype (ARGVP1)> &) {
			return NULL ;
		}
	} ;
} ;

template <class UNIT>
class WeakRef {
private:
	using Holder = typename WeakRef<void>::Holder ;

private:
	SharedRef<Holder> mHolder ;
	PTR<UNIT> mPointer ;

public:
	inline WeakRef () noexcept {
		mPointer = NULL ;
	}

	inline BOOL exist () const {
		if (!mHolder.exist ())
			return FALSE ;
		if (!mHolder->mData.exist ())
			return FALSE ;
		if (mPointer == NULL)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL equal (const WeakRef &that) const {
		if (!mHolder.exist () && !that.mHolder.exist ())
			return TRUE ;
		if (!mHolder.exist ())
			return FALSE ;
		if (!that.mHolder.exist ())
			return FALSE ;
		if (&mHolder.self != &that.mHolder.self)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const WeakRef &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const WeakRef &that) const {
		return !equal (that) ;
	}

	inline BOOL equal (const StrongRef<UNIT> &that) const {
		if (!mHolder.exist () && !that.mHolder.exist ())
			return TRUE ;
		if (!mHolder.exist ())
			return FALSE ;
		if (!that.mHolder.exist ())
			return FALSE ;
		if (&mHolder.self != &that.mHolder.self)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const StrongRef<UNIT> &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const StrongRef<UNIT> &that) const {
		return !equal (that) ;
	}

	inline StrongRef<UNIT> watch () const {
		return StrongRef<UNIT> (mHolder ,mPointer) ;
	}

	inline void assign (const StrongRef<UNIT> &that) {
		mHolder = that.mHolder ;
		mPointer = that.mPointer ;
	}

	inline void operator<<= (const StrongRef<UNIT> &that) {
		assign (that) ;
	}
} ;

template <class UNIT>
inline StrongRef<UNIT>::StrongRef (const WeakRef<UNIT> &that) :StrongRef (that.watch ()) {}

template <class UNIT>
inline BOOL StrongRef<UNIT>::equal (const WeakRef<UNIT> &that) const {
	return that.equal ((*this)) ;
}

template <class UNIT>
class SoftRef {
private:
	class Node {
	private:
		friend SoftRef ;
		StrongRef<UNIT> mData ;
		LENGTH mWeight ;

	public:
		inline Node () :mWeight (0) {}
	} ;

	inline static constexpr VAR constexpr_log2x (VAR val) {
		return _SWITCH_ (
			(val <= 0) ? VAR_NONE :
			(val == 1) ? 0 :
			(1 + constexpr_log2x (val / 2))) ;
	}

private:
	SharedRef<FixedBuffer<Node>> mHeap ;
	WeakRef<UNIT> mWeakRef ;
	INDEX mIndex ;

public:
	inline SoftRef () {
		mIndex = VAR_NONE ;
	}

	inline explicit SoftRef (LENGTH len) {
		mHeap = SharedRef<FixedBuffer<Node>>::make (len) ;
		mIndex = VAR_NONE ;
	}

	inline SoftRef (const SoftRef &that) {
		mHeap = that.mHeap ;
		mWeakRef = that.mWeakRef ;
		mIndex = that.mIndex ;
		acquire () ;
	}

	inline SoftRef &operator= (const SoftRef &that) {
		for (FOR_ONCE_DO) {
			if (this == &that)
				discard ;
			(*this).~SoftRef () ;
			new (this) SoftRef (std::move (that)) ;
		}
		return (*this) ;
	}

	inline SoftRef (SoftRef &&that) noexcept {
		mHeap = std::move (that.mHeap) ;
		mWeakRef = std::move (that.mWeakRef) ;
		mIndex = that.mIndex ;
	}

	inline SoftRef &operator= (SoftRef &&that) noexcept {
		for (FOR_ONCE_DO) {
			if (this == &that)
				discard ;
			(*this).~SoftRef () ;
			new (this) SoftRef (std::move (that)) ;
		}
		return (*this) ;
	}

	LENGTH capacity () const {
		if (!mHeap.exist ())
			return 0 ;
		return mHeap->size () ;
	}

	inline BOOL exist () const {
		return mWeakRef.exist () ;
	}

	inline SoftRef share () popping {
		SoftRef ret ;
		ret.mHeap = mHeap ;
		ret.mIndex = VAR_NONE ;
		return std::move (ret) ;
	}

	inline BOOL equal (const SoftRef &that) const {
		return BOOL (mWeakRef == that.mWeakRef) ;
	}

	inline BOOL operator== (const SoftRef &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const SoftRef &that) const {
		return !equal (that) ;
	}

	inline BOOL equal (const StrongRef<UNIT> &that) const {
		return BOOL (mWeakRef == that) ;
	}

	inline BOOL operator== (const StrongRef<UNIT> &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const StrongRef<UNIT> &that) const {
		return !equal (that) ;
	}

	inline StrongRef<UNIT> watch () const {
		for (FOR_ONCE_DO) {
			if (!linked ())
				discard ;
			auto &r1y = mHeap.self[mIndex].mWeight ;
			const auto r2x = EFLAG (r1y >= 0 && r1y < VAR32_MAX) ;
			const auto r3x = EFLAG (r1y < 0 && r1y > VAR32_MIN) ;
			r1y += r2x - r3x ;
		}
		return mWeakRef.watch () ;
	}

	inline void assign (const StrongRef<UNIT> &that) {
		mIndex = has_linked_one (that) ;
		mWeakRef.assign (that) ;
		acquire () ;
	}

	inline void operator<<= (const StrongRef<UNIT> &that) {
		assign (that) ;
	}

	inline void as_strong () const {
		if (!linked ())
			return ;
		if (mHeap.self[mIndex].mWeight < 0)
			return ;
		mHeap.self[mIndex].mWeight = ~mHeap.self[mIndex].mWeight ;
	}

	inline void as_weak () const {
		if (!linked ())
			return ;
		if (mHeap.self[mIndex].mWeight >= 0)
			return ;
		mHeap.self[mIndex].mWeight = ~mHeap.self[mIndex].mWeight ;
	}

	inline void clean () const {
		if (!mHeap.exist ())
			return ;
		for (INDEX i = 0 ,ie = mHeap->size () ; i < ie ; i++) {
			if (mHeap.self[i].mWeight < 0)
				continue ;
			mHeap.self[i].mData = StrongRef<UNIT> () ;
			mHeap.self[i].mWeight = 0 ;
		}
	}

private:
	inline BOOL linked () const {
		if (!mHeap.exist ())
			return FALSE ;
		if (!mWeakRef.exist ())
			return FALSE ;
		if (!(mIndex >= 0 && mIndex < mHeap->size ()))
			return FALSE ;
		if (mWeakRef != mHeap.self[mIndex].mData)
			return FALSE ;
		return TRUE ;
	}

	inline INDEX has_linked_one (const StrongRef<UNIT> &that) const {
		for (INDEX i = 0 ,ie = mHeap->size () ; i < ie ; i++)
			if (mHeap.self[i].mData == that)
				return i ;
		return VAR_NONE ;
	}

	inline void acquire () {
		if (linked ())
			return ;
		if (!mHeap.exist ())
			return ;
		if (!mWeakRef.exist ())
			return ;
		for (FOR_ONCE_DO) {
			mIndex = min_weight_one () ;
			if (mIndex == VAR_NONE)
				discard ;
			const auto r1x = constexpr_log2x (mHeap.self[mIndex].mWeight) ;
			if (r1x <= 0)
				discard ;
			for (INDEX i = 0 ,ie = mHeap->size () ; i < ie ; i++)
				mHeap.self[i].mWeight = mHeap.self[i].mWeight >> r1x ;
		}
		_DYNAMIC_ASSERT_ (mIndex != VAR_NONE) ;
		mHeap.self[mIndex].mData = mWeakRef ;
		mHeap.self[mIndex].mWeight = 3 ;
	}

	inline INDEX min_weight_one () const {
		INDEX ret = VAR_NONE ;
		auto rax = LENGTH () ;
		for (INDEX i = 0 ,ie = mHeap->size () ; i < ie ; i++) {
			const auto r1x = mHeap.self[i].mWeight ;
			if (r1x < 0)
				continue ;
			if (ret != VAR_NONE && rax <= r1x)
				continue ;
			ret = i ;
			rax = r1x ;
		}
		return std::move (ret) ;
	}
} ;

template <class UNIT>
inline StrongRef<UNIT>::StrongRef (const SoftRef<UNIT> &that) :StrongRef (that.watch ()) {}

template <class UNIT>
inline BOOL StrongRef<UNIT>::equal (const SoftRef<UNIT> &that) const {
	return that.equal ((*this)) ;
}

template <class UNIT>
class IntrusiveRef {
private:
	using INTRUSIVE_TYPE = typename UNIT::INTRUSIVE_TYPE ;

	class WatchProxy final {
	private:
		friend IntrusiveRef ;
		PTR<UNIT> mPointer ;

	public:
		inline WatchProxy () = delete ;

		inline ~WatchProxy () noexcept {
			if (mPointer == NULL)
				return ;
			_CATCH_ ([&] () {
				Detail::release (mPointer) ;
			}) ;
			mPointer = NULL ;
		}

		inline WatchProxy (const WatchProxy &) = delete ;
		inline WatchProxy &operator= (const WatchProxy &) = delete ;

		inline WatchProxy (WatchProxy &&) noexcept = default ;
		inline WatchProxy &operator= (WatchProxy &&) = delete ;

		inline implicit operator UNIT & () const & noexcept {
			return _LOAD_<UNIT> (mPointer) ;
		}

		inline implicit operator UNIT & () && = delete ;

		template <class _RET ,class = ENABLE_TYPE<std::is_convertible<UNIT & ,_RET>::value>>
		inline implicit operator _RET () const & {
			return _RET (_LOAD_<UNIT> (mPointer)) ;
		}

		template <class _RET>
		inline implicit operator _RET () && = delete ;

	private:
		inline explicit WatchProxy (PTR<UNIT> pointer) noexcept :mPointer (pointer) {}
	} ;

	class Counter :private Wrapped<std::atomic<LENGTH>> {
	public:
		inline void lock () {
			const auto r1x = ++Counter::mSelf ;
			_DEBUG_ASSERT_ (r1x >= 1) ;
			(void) r1x ;
		}

		inline void unlock () {
			const auto r1x = --Counter::mSelf ;
			_DEBUG_ASSERT_ (r1x >= 0) ;
			(void) r1x ;
		}
	} ;

private:
	_STATIC_ASSERT_ (_SIZEOF_ (UNIT) > 0) ;
	class Detail ;
	friend ScopedGuard<IntrusiveRef> ;
	std::atomic<PTR<UNIT>> mPointer ;
	std::atomic<LENGTH> mLatch ;

public:
	inline IntrusiveRef () noexcept {
		mPointer = NULL ;
		mLatch = 0 ;
	}

	//@warn: address must be from 'IntrusiveRef::make'
	template <class _ARG1 ,class = ENABLE_TYPE<std::is_same<_ARG1 ,PTR<UNIT>>::value>>
	inline explicit IntrusiveRef (const _ARG1 &that) : IntrusiveRef (ARGVP0) {
		Detail::acquire (that ,FALSE) ;
		const auto r1x = safe_exchange (that) ;
		_DEBUG_ASSERT_ (r1x == NULL) ;
		(void) r1x ;
	}

	inline ~IntrusiveRef () noexcept {
		const auto r1x = safe_exchange (NULL) ;
		_CATCH_ ([&] () {
			Detail::release (r1x) ;
		}) ;
	}

	inline IntrusiveRef (const IntrusiveRef &) = delete ;
	inline IntrusiveRef &operator= (const IntrusiveRef &) = delete ;

	inline IntrusiveRef (IntrusiveRef &&that) noexcept :IntrusiveRef (ARGVP0) {
		const auto r1x = that.safe_exchange (NULL) ;
		const auto r2x = safe_exchange (r1x) ;
		_DEBUG_ASSERT_ (r2x == NULL) ;
		(void) r2x ;
	}

	inline IntrusiveRef &operator= (IntrusiveRef &&that) noexcept {
		for (FOR_ONCE_DO) {
			if (this == &that)
				discard ;
			(*this).~IntrusiveRef () ;
			new (this) IntrusiveRef (std::move (that)) ;
		}
		return (*this) ;
	}

	inline BOOL exist () const {
		const auto r1x = mPointer.load () ;
		if (r1x == NULL)
			return FALSE ;
		return TRUE ;
	}

	inline IntrusiveRef copy () popping {
		ScopedGuard<Counter> ANONYMOUS (_CAST_<Counter> (mLatch)) ;
		IntrusiveRef ret = IntrusiveRef (ARGVP0) ;
		const auto r1x = mPointer.load () ;
		Detail::acquire (r1x ,FALSE) ;
		const auto r2x = ret.safe_exchange (r1x) ;
		_DEBUG_ASSERT_ (r2x == NULL) ;
		(void) r2x ;
		return std::move (ret) ;
	}

	inline WatchProxy watch () popping {
		ScopedGuard<Counter> ANONYMOUS (_CAST_<Counter> (mLatch)) ;
		const auto r1x = mPointer.load () ;
		_DYNAMIC_ASSERT_ (r1x != NULL) ;
		Detail::acquire (r1x ,FALSE) ;
		return WatchProxy (r1x) ;
	}

private:
	inline explicit IntrusiveRef (const DEF<decltype (ARGVP0)> &) noexcept :mPointer (NULL) ,mLatch (0) {}

private:
	inline PTR<UNIT> safe_exchange (PTR<UNIT> address) noexcept popping {
#pragma GCC diagnostic push
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif
		using DEFAULT_RETRYTIMES_SIZE = ARGC<64> ;
		const auto r1x = mPointer.exchange (address) ;
		if (r1x == NULL)
			return r1x ;
		INDEX ir = 0 ;
		while (TRUE) {
			const auto r2x = ir++ ;
			_DEBUG_ASSERT_ (r2x < DEFAULT_RETRYTIMES_SIZE::value) ;
			(void) r2x ;
			const auto r3x = mLatch.load () ;
			if (r3x == 0)
				break ;
			INTRUSIVE_TYPE::friend_latch ((*r1x)) ;
		}
		return r1x ;
#pragma GCC diagnostic pop
	}

public:
	template <class... _ARGS>
	inline static IntrusiveRef make (_ARGS &&...initval) {
		IntrusiveRef ret = IntrusiveRef (ARGVP0) ;
		auto rax = GlobalHeap::alloc<TEMP<UNIT>> () ;
		ScopedBuild<UNIT> ANONYMOUS (rax ,std::forward<_ARGS> (initval)...) ;
		auto &r1y = _LOAD_<UNIT> (_XVALUE_<PTR<TEMP<UNIT>>> (rax)) ;
		Detail::acquire (&r1y ,TRUE) ;
		const auto r2x = ret.safe_exchange (&r1y) ;
		_DEBUG_ASSERT_ (r2x == NULL) ;
		(void) r2x ;
		rax = NULL ;
		return std::move (ret) ;
	}

private:
	class Detail :private Wrapped<void> {
	public:
		inline static void acquire (PTR<UNIT> address ,BOOL init) {
			if (address == NULL)
				return ;
			if (init)
				INTRUSIVE_TYPE::friend_create ((*address)) ;
			const auto r1x = INTRUSIVE_TYPE::friend_attach ((*address)) ;
			_DEBUG_ASSERT_ (r1x >= 1 + EFLAG (!init)) ;
			(void) r1x ;
		}

		inline static void release (PTR<UNIT> address) {
			if (address == NULL)
				return ;
			const auto r1x = INTRUSIVE_TYPE::friend_detach ((*address)) ;
			_DEBUG_ASSERT_ (r1x >= 0) ;
			if (r1x > 0)
				return ;
			INTRUSIVE_TYPE::friend_destroy ((*address)) ;
			address->~UNIT () ;
			GlobalHeap::free (address) ;
		}
	} ;
} ;

template <class UNIT>
class Monostate {
private:
	SharedRef<UNIT> mThis ;

public:
	inline Monostate () {
		mThis = SharedRef<UNIT>::make () ;
	}

	inline Monostate (const Monostate &) = delete ;
	inline Monostate &operator= (const Monostate &) = delete ;
	inline Monostate (Monostate &&) = delete ;
	inline Monostate &operator= (Monostate &&) = delete ;

	inline UNIT &to () const {
		return mThis.self ;
	}

	inline implicit operator UNIT & () const {
		return to () ;
	}

	inline void swap (Monostate &that) popping {
		_SWAP_ (mThis ,that.mThis) ;
	}
} ;

template <class UNIT>
class Lazy {
private:
	class ApplyTo :private Wrapped<UNIT> {
	public:
		inline void friend_move (UNIT &data) popping {
			data = std::move (ApplyTo::mSelf) ;
		}

		inline void friend_move (UNIT &data) const popping {
			data = std::move (ApplyTo::mSelf) ;
		}
	} ;

	class Holder :public WeakRef<void>::Virtual {
	private:
		friend Lazy ;
		Mutable<UNIT> mData ;
		Function<DEF<UNIT ()> NONE::*> mEvaluator ;
		AnyRef<void> mFunction ;
	} ;

private:
	SoftRef<Holder> mThis ;

public:
	inline Lazy () = default ;

	inline implicit Lazy (const UNIT &that) {
		mThis = SoftRef<Holder> (9) ;
		const auto r1x = StrongRef<Holder>::make () ;
		const auto r2x = Function<DEF<void (UNIT &)> NONE::*> (PhanRef<const ApplyTo>::make (_CAST_<ApplyTo> (that)) ,&ApplyTo::friend_move) ;
		r1x->mData.apply (r2x) ;
		r1x->mData.finish () ;
		mThis.assign (r1x) ;
		mThis.as_strong () ;
	}

	inline implicit Lazy (UNIT &&that) {
		mThis = SoftRef<Holder> (9) ;
		const auto r1x = StrongRef<Holder>::make () ;
		const auto r2x = Function<DEF<void (UNIT &)> NONE::*> (PhanRef<ApplyTo>::make (_CAST_<ApplyTo> (that)) ,&ApplyTo::friend_move) ;
		r1x->mData.apply (r2x) ;
		r1x->mData.finish () ;
		mThis.assign (r1x) ;
		mThis.as_strong () ;
	}

	inline implicit Lazy (Function<DEF<UNIT ()> NONE::*> &&that) {
		mThis = SoftRef<Holder> (9) ;
		const auto r1x = StrongRef<Holder>::make () ;
		r1x = StrongRef<Holder>::make () ;
		r1x->mData.signal () ;
		r1x->mEvaluator = std::move (that) ;
		mThis.assign (r1x) ;
		mThis.as_strong () ;
	}

#ifdef __CSC_DEPRECATED__
	inline explicit Lazy (Function<UNIT ()> &&that) {
		mThis = SoftRef<Holder> (9) ;
		const auto r1x = StrongRef<Holder>::make () ;
		r1x = StrongRef<Holder>::make () ;
		r1x->mData.signal () ;
		r1x->mFunction = AnyRef<Function<UNIT ()>>::make (std::move (that)) ;
		auto &r2y = r1x->mFunction.template rebind<Function<UNIT ()>> ().self ;
		r1x->mEvaluator = Function<DEF<UNIT ()> NONE::*>::make (PhanRef<Function<UNIT ()>> (r2y) ,&Function<UNIT ()>::invoke) ;
		mThis.assign (r1x) ;
		mThis.as_strong () ;
	}
#endif

	inline BOOL exist () const {
		return mThis.exist () ;
	}

	inline const UNIT &to () const {
		_DEBUG_ASSERT_ (exist ()) ;
		finish () ;
		const auto r1x = mThis.watch () ;
		return r1x->mData.self ;
	}

	inline implicit operator const UNIT & () const {
		return to () ;
	}

	inline LENGTH rank () const {
		_DEBUG_ASSERT_ (exist ()) ;
		return 0 ;
	}

	inline void finish () const {
		_DEBUG_ASSERT_ (exist ()) ;
		const auto r1x = mThis.watch () ;
		const auto r2x = Function<DEF<void (UNIT &)> NONE::*> (PhanRef<const Lazy>::make ((*this)) ,&Lazy::compute_evaluation) ;
		r1x->mData.apply (r2x) ;
		r1x->mData.finish () ;
	}

	inline Lazy concat (const Lazy &that) const {
		if (!exist ())
			return that ;
		if (!that.exist ())
			return (*this) ;
		_STATIC_WARNING_ ("unimplemented") ;
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Lazy () ;
	}

	inline Lazy operator+ (const Lazy &that) const {
		return concat (that) ;
	}

	inline Lazy &operator+= (const Lazy &that) {
		(*this) = concat (that) ;
		return (*this) ;
	}

	inline Lazy operator- (const Lazy &that) const {
		return that.concat ((*this)) ;
	}

	inline Lazy &operator-= (const Lazy &that) {
		(*this) = that.concat ((*this)) ;
		return (*this) ;
	}

private:
	inline void compute_evaluation (UNIT &data) const {
		const auto r1x = mThis.watch () ;
		_DYNAMIC_ASSERT_ (r1x->mEvaluator.exist ()) ;
		data = r1x->mEvaluator () ;
	}
} ;

inline namespace S {
inline constexpr VAR _ALIGNAS_ (VAR base ,VAR align) {
	return base + (align - base % align) % align ;
}
} ;

inline namespace S {
template <class _RET ,class _ARG1>
inline _RET _BITWISE_CAST_ (const _ARG1 &object) {
	_STATIC_ASSERT_ (!std::is_reference<_RET>::value) ;
	_STATIC_ASSERT_ (std::is_pod<_RET>::value) ;
	_STATIC_ASSERT_ (!std::is_pointer<_RET>::value) ;
	_STATIC_ASSERT_ (std::is_pod<_ARG1>::value) ;
	_STATIC_ASSERT_ (!std::is_pointer<_ARG1>::value) ;
	_STATIC_ASSERT_ (_SIZEOF_ (_RET) == _SIZEOF_ (_ARG1)) ;
	TEMP<_RET> ret ;
	_ZERO_ (ret) ;
	auto &r1y = _CAST_<BYTE[_SIZEOF_ (_ARG1)]> (object) ;
	_MEMCOPY_ (PTRTOARR[ret.unused] ,PTRTOARR[r1y] ,_COUNTOF_ (decltype (r1y))) ;
	return std::move (_CAST_<_RET> (ret)) ;
}
} ;

class MemoryPool {
private:
	struct HEADER ;

	struct Pool :public Interface {
		virtual LENGTH size () const = 0 ;
		virtual LENGTH length () const = 0 ;
		virtual PTR<HEADER> alloc (LENGTH) popping = 0 ;
		virtual void free (PTR<HEADER> address) noexcept = 0 ;
		virtual void clean () = 0 ;
	} ;

	struct HEADER {
		alignas (8) PTR<Pool> mPool ;
		alignas (8) PTR<struct HEADER> mCurr ;
	} ;

	template <class SIZE ,class RESE>
	class ImplPool :public Pool {
	private:
		struct BLOCK {
			PTR<struct BLOCK> mNext ;
			HEADER mFlexData ;
		} ;

		struct CHUNK {
			PTR<ARR<BYTE>> mOrigin ;
			PTR<struct CHUNK> mPrev ;
			PTR<struct CHUNK> mNext ;
			LENGTH mCount ;
		} ;

	private:
		PTR<CHUNK> mRoot ;
		PTR<BLOCK> mFree ;
		LENGTH mSize ;
		LENGTH mLength ;

	public:
		inline ImplPool () noexcept {
			mRoot = NULL ;
			mFree = NULL ;
			mSize = 0 ;
			mLength = 0 ;
		}

		inline ~ImplPool () noexcept override {
			if (mRoot == NULL)
				return ;
			for (PTR<CHUNK> i = mRoot ,it ; i != NULL ; i = it) {
				it = i->mNext ;
				GlobalHeap::free (i->mOrigin) ;
			}
			mRoot = NULL ;
		}

		inline LENGTH size () const override {
			return mSize ;
		}

		inline LENGTH length () const override {
			return mLength ;
		}

		inline void reserve () {
			if (mFree != NULL)
				return ;
			const auto r1x = _ALIGNAS_ (_SIZEOF_ (BLOCK) + SIZE::value ,_ALIGNOF_ (BLOCK)) ;
			const auto r2x = _ALIGNOF_ (CHUNK) - 1 + _SIZEOF_ (CHUNK) + _ALIGNOF_ (BLOCK) - 1 + RESE::value * r1x ;
			auto rax = GlobalHeap::alloc<BYTE> (r2x) ;
			const auto r3x = _ADDRESS_ (_XVALUE_<PTR<ARR<BYTE>>> (rax)) ;
			const auto r4x = _ALIGNAS_ (r3x ,_ALIGNOF_ (CHUNK)) ;
			const auto r5x = _XVALUE_<PTR<VOID>> (&_NULL_<BYTE> () + r4x) ;
			auto &r6y = _LOAD_<CHUNK> (r5x) ;
			r6y.mOrigin = _XVALUE_<PTR<ARR<BYTE>>> (rax) ;
			r6y.mPrev = NULL ;
			r6y.mNext = mRoot ;
			r6y.mCount = RESE::value ;
			if (mRoot != NULL)
				mRoot->mPrev = &r6y ;
			mRoot = &r6y ;
			mSize += RESE::value * SIZE::value ;
			const auto r7x = _ALIGNAS_ (r4x + _SIZEOF_ (CHUNK) ,_ALIGNOF_ (BLOCK)) ;
			for (INDEX i = 0 ,ie = mRoot->mCount ; i < ie ; i++) {
				const auto r8x = r7x + i * r1x ;
				const auto r9x = _XVALUE_<PTR<VOID>> (&_NULL_<BYTE> () + r8x) ;
				auto &r10y = _LOAD_<BLOCK> (r9x) ;
				r10y.mNext = mFree ;
				mFree = &r10y ;
			}
			rax = NULL ;
		}

		inline PTR<HEADER> alloc (LENGTH len) popping override {
			_DEBUG_ASSERT_ (len <= SIZE::value) ;
			reserve () ;
			const auto r1x = mFree ;
			mFree = r1x->mNext ;
			mLength += SIZE::value ;
			const auto r2x = _CAST_<TEMP<PTR<BLOCK>>> (VAR_USED) ;
			r1x->mNext = _LOAD_<PTR<BLOCK>> (&r2x) ;
			return &r1x->mFlexData ;
		}

		inline void free (PTR<HEADER> address) noexcept override {
			_DEBUG_ASSERT_ (address != NULL) ;
			auto &r1y = _OFFSET_ (&BLOCK::mFlexData ,(*address)) ;
			_DEBUG_ASSERT_ (_ADDRESS_ (r1y.mNext) == VAR_USED) ;
			r1y.mNext = mFree ;
			mFree = &r1y ;
			mLength -= SIZE::value ;
		}

		inline void clean () override {
			if (mSize == mLength)
				return ;
			for (PTR<CHUNK> i = mRoot ,it ; i != NULL ; i = it) {
				it = i->mNext ;
				if (!empty_node (i))
					continue ;
				auto &r1y = _SWITCH_ (
					(i->mPrev != NULL) ? (i->mPrev->mNext) :
					mRoot) ;
				r1y = i->mNext ;
				if (i->mNext != NULL)
					i->mNext->mPrev = i->mPrev ;
				mSize -= i->mCount * SIZE::value ;
				GlobalHeap::free (i->mOrigin) ;
			}
		}

	private:
		inline BOOL empty_node (PTR<const CHUNK> node) const {
			const auto r1x = _ALIGNAS_ (_SIZEOF_ (BLOCK) + SIZE::value ,_ALIGNOF_ (BLOCK)) ;
			const auto r2x = _ALIGNAS_ (_ADDRESS_ (node) + _SIZEOF_ (CHUNK) ,_ALIGNOF_ (BLOCK)) ;
			for (INDEX i = 0 ,ie = node->mCount ; i < ie ; i++) {
				const auto r3x = r2x + i * r1x ;
				const auto r4x = _XVALUE_<PTR<VOID>> (&_NULL_<BYTE> () + r3x) ;
				auto &r5y = _LOAD_<BLOCK> (r4x) ;
				if (_ADDRESS_ (r5y.mNext) == VAR_USED)
					return FALSE ;
			}
			return TRUE ;
		}
	} ;

	class HugePool :public Pool {
	private:
		struct BLOCK {
			PTR<ARR<BYTE>> mOrigin ;
			PTR<struct BLOCK> mPrev ;
			PTR<struct BLOCK> mNext ;
			LENGTH mCount ;
			HEADER mFlexData ;
		} ;

	private:
		PTR<BLOCK> mRoot ;
		LENGTH mSize ;
		LENGTH mLength ;

	public:
		inline HugePool () noexcept {
			mRoot = NULL ;
			mLength = 0 ;
			mSize = 0 ;
		}

		inline ~HugePool () noexcept override {
			if (mRoot == NULL)
				return ;
			for (PTR<BLOCK> i = mRoot ,it ; i != NULL ; i = it) {
				it = i->mNext ;
				GlobalHeap::free (i->mOrigin) ;
			}
			mRoot = NULL ;
		}

		inline LENGTH size () const override {
			return mSize ;
		}

		inline LENGTH length () const override {
			return mLength ;
		}

		inline PTR<HEADER> alloc (LENGTH len) popping override {
			const auto r1x = _ALIGNAS_ (len ,_ALIGNOF_ (BLOCK)) ;
			const auto r2x = _ALIGNOF_ (BLOCK) - 1 + _SIZEOF_ (BLOCK) + r1x ;
			auto rax = GlobalHeap::alloc<BYTE> (r2x) ;
			const auto r3x = _ADDRESS_ (_XVALUE_<PTR<ARR<BYTE>>> (rax)) ;
			const auto r4x = _ALIGNAS_ (r3x ,_ALIGNOF_ (BLOCK)) ;
			const auto r5x = _XVALUE_<PTR<VOID>> (&_NULL_<BYTE> () + r4x) ;
			auto &r6y = _LOAD_<BLOCK> (r5x) ;
			r6y.mOrigin = _XVALUE_<PTR<ARR<BYTE>>> (rax) ;
			r6y.mPrev = NULL ;
			r6y.mNext = mRoot ;
			r6y.mCount = r1x ;
			if (mRoot != NULL)
				mRoot->mPrev = &r6y ;
			mRoot = &r6y ;
			mSize += r6y.mCount ;
			mLength += r6y.mCount ;
			rax = NULL ;
			return &r6y.mFlexData ;
		}

		inline void free (PTR<HEADER> address) noexcept override {
			_DEBUG_ASSERT_ (address != NULL) ;
			auto &r1y = _OFFSET_ (&BLOCK::mFlexData ,(*address)) ;
			auto &r2y = _SWITCH_ (
				(r1y.mPrev != NULL) ? (r1y.mPrev->mNext) :
				mRoot) ;
			r2y = r1y.mNext ;
			if (r1y.mNext != NULL)
				r1y.mNext->mPrev = r1y.mPrev ;
			mSize -= r1y.mCount ;
			mLength -= r1y.mCount ;
			GlobalHeap::free (r1y.mOrigin) ;
		}

		inline void clean () override {
			_STATIC_WARNING_ ("noop") ;
		}
	} ;

private:
	ImplPool<ARGC<8> ,ARGC<32>> mPool1 ;
	ImplPool<ARGC<16> ,ARGC<32>> mPool2 ;
	ImplPool<ARGC<24> ,ARGC<32>> mPool3 ;
	ImplPool<ARGC<32> ,ARGC<32>> mPool4 ;
	ImplPool<ARGC<40> ,ARGC<16>> mPool5 ;
	ImplPool<ARGC<48> ,ARGC<16>> mPool6 ;
	ImplPool<ARGC<56> ,ARGC<16>> mPool7 ;
	ImplPool<ARGC<64> ,ARGC<16>> mPool8 ;
	ImplPool<ARGC<72> ,ARGC<8>> mPool9 ;
	ImplPool<ARGC<80> ,ARGC<8>> mPool10 ;
	ImplPool<ARGC<88> ,ARGC<8>> mPool11 ;
	ImplPool<ARGC<96> ,ARGC<8>> mPool12 ;
	ImplPool<ARGC<104> ,ARGC<4>> mPool13 ;
	ImplPool<ARGC<112> ,ARGC<4>> mPool14 ;
	ImplPool<ARGC<120> ,ARGC<4>> mPool15 ;
	ImplPool<ARGC<128> ,ARGC<4>> mPool16 ;
	HugePool mPool17 ;
	Monostate<Buffer<PTR<Pool> ,ARGC<17>>> mPool ;

public:
	inline MemoryPool () {
		mPool.self = Buffer<PTR<Pool> ,ARGC<17>> ({
			&mPool1 ,&mPool2 ,&mPool3 ,&mPool4 ,&mPool5 ,&mPool6 ,&mPool7 ,&mPool8 ,
			&mPool9 ,&mPool10 ,&mPool11 ,&mPool12 ,&mPool13 ,&mPool14 ,&mPool15 ,&mPool16 ,
			&mPool17}) ;
	}

	inline LENGTH size () const {
		LENGTH ret = 0 ;
		for (INDEX i = 0 ,ie = mPool.self.size () ; i < ie ; i++)
			ret += mPool.self[i]->size () ;
		return std::move (ret) ;
	}

	inline LENGTH length () const {
		LENGTH ret = 0 ;
		for (INDEX i = 0 ,ie = mPool.self.size () ; i < ie ; i++)
			ret += mPool.self[i]->length () ;
		return std::move (ret) ;
	}

	//@warn: held by RAII to avoid static-memory-leaks
	template <class _RET>
	inline PTR<_RET> alloc () popping {
		_STATIC_ASSERT_ (!std::is_reference<_RET>::value) ;
		_STATIC_ASSERT_ (std::is_pod<_RET>::value) ;
		const auto r1x = _MAX_ (_ALIGNOF_ (_RET) - _ALIGNOF_ (HEADER) ,VAR_ZERO) + _SIZEOF_ (_RET) ;
		INDEX ix = _MIN_ (((r1x - 1) / 8) ,_SIZEOF_ (HEADER)) ;
		const auto r2x = mPool.self[ix]->alloc (r1x) ;
		const auto r3x = _ALIGNAS_ (_ADDRESS_ (r2x) + _SIZEOF_ (HEADER) ,_ALIGNOF_ (_RET)) ;
		const auto r4x = _XVALUE_<PTR<VOID>> (&_NULL_<BYTE> () + r3x - _SIZEOF_ (HEADER)) ;
		auto &r5y = _LOAD_<HEADER> (r4x) ;
		r5y.mPool = mPool.self[ix] ;
		r5y.mCurr = r2x ;
		const auto r6x = _XVALUE_<PTR<VOID>> (&_NULL_<BYTE> () + r3x) ;
		auto &r7y = _LOAD_<_RET> (r6x) ;
		return &r7y ;
	}

	//@warn: held by RAII to avoid static-memory-leaks
	template <class _RET>
	inline PTR<ARR<_RET>> alloc (LENGTH len) popping {
		_STATIC_ASSERT_ (!std::is_reference<_RET>::value) ;
		_STATIC_ASSERT_ (std::is_pod<_RET>::value) ;
		const auto r1x = _MAX_ (_ALIGNOF_ (_RET) - _ALIGNOF_ (HEADER) ,VAR_ZERO) + len * _SIZEOF_ (_RET) ;
		_DEBUG_ASSERT_ (r1x > 0) ;
		INDEX ix = _MIN_ (((r1x - 1) / 8) ,_SIZEOF_ (HEADER)) ;
		const auto r2x = mPool.self[ix]->alloc (r1x) ;
		const auto r3x = _ALIGNAS_ (_ADDRESS_ (r2x) + _SIZEOF_ (HEADER) ,_ALIGNOF_ (_RET)) ;
		const auto r4x = _XVALUE_<PTR<VOID>> (&_NULL_<BYTE> () + r3x - _SIZEOF_ (HEADER)) ;
		auto &r5y = _LOAD_<HEADER> (r4x) ;
		r5y.mPool = mPool.self[ix] ;
		r5y.mCurr = r2x ;
		const auto r6x = _XVALUE_<PTR<VOID>> (&_NULL_<BYTE> () + r3x) ;
		auto &r7y = _LOAD_<ARR<_RET>> (r6x) ;
		return &r7y ;
	}

	template <class _ARG1>
	inline void free (const PTR<_ARG1> &address) noexcept {
		_STATIC_ASSERT_ (std::is_pod<REMOVE_ARRAY_TYPE<_ARG1>>::value) ;
		const auto r1x = _ADDRESS_ (address) - _SIZEOF_ (HEADER) ;
		const auto r2x = _XVALUE_<PTR<VOID>> (&_NULL_<BYTE> () + r1x) ;
		auto &r3y = _LOAD_<HEADER> (r2x) ;
		INDEX ix = _MEMCHR_ (mPool.self.self ,mPool.self.size () ,r3y.mPool) ;
		_DEBUG_ASSERT_ (ix != VAR_NONE) ;
		mPool.self[ix]->free (r3y.mCurr) ;
	}

	inline void clean () {
		for (INDEX i = 0 ,ie = mPool.self.size () ; i < ie ; i++)
			mPool.self[i]->clean () ;
	}
} ;

class Object ;

struct Objective :public Interface {
	virtual StrongRef<Object> clone () const = 0 ;
} ;

class Object :public Objective ,public WeakRef<void>::Virtual {
private:
	class Metadata {
	private:
		friend Object ;
		LENGTH mObjectSize ;
		LENGTH mObjectAlign ;
		FLAG mObjectTypeUID ;
		Function<void (PTR<NONE>)> mConstrutor ;
		Function<void (PTR<NONE>)> mDestructor ;

	private:
		inline Metadata () = delete ;

		template <class _ARG1>
		inline explicit Metadata (const ARGV<_ARG1> &) {
			_STATIC_ASSERT_ (std::is_same<REMOVE_CVR_TYPE<_ARG1> ,_ARG1>::value) ;
			mObjectSize = _SIZEOF_ (_ARG1) ;
			mObjectAlign = _ALIGNOF_ (_ARG1) ;
			mObjectTypeUID = _TYPEUID_<_ARG1> () ;
			const auto r1x = _XVALUE_<PTR<void (PTR<NONE>)>> ([] (PTR<NONE> address) {
				auto &r2y = _LOAD_<TEMP<_ARG1>> (address) ;
				_CREATE_ (&r2y) ;
			}) ;
			mConstrutor = r1x ;
			const auto r3x = _XVALUE_<PTR<void (PTR<NONE>)>> ([] (PTR<NONE> address) {
				auto &r4y = _LOAD_<TEMP<_ARG1>> (address) ;
				_DESTROY_ (&r4y) ;
			}) ;
			mDestructor = r1x ;
		}
	} ;

public:
	inline Object () = delete ;

	template <class _ARG1>
	inline explicit Object (PTR<_ARG1> deriver) {
		_STATIC_ASSERT_ (stl::is_always_base_of<Object ,_ARG1>::value) ;
		_STATIC_ASSERT_ (!std::is_same<REMOVE_CVR_TYPE<_ARG1> ,Object>::value) ;
		_DEBUG_ASSERT_ (_ADDRESS_ (this) == _ADDRESS_ (deriver)) ;
	}

	inline StrongRef<Object> clone () const override {
		return StrongRef<Object> () ;
	}
} ;

template <class UNIT1 ,class UNIT2>
class Serializer {
private:
	struct Binder :public Interface {
		virtual void compute_visit (UNIT1 &visitor ,UNIT2 &context) const = 0 ;
	} ;

	template <class... _UNITS>
	class ImplBinder :public Binder {
	private:
		Tuple<DEF<_UNITS UNIT2::*>...> mMemPtr ;

	public:
		inline ImplBinder () = delete ;

		inline explicit ImplBinder (const DEF<_UNITS UNIT2::*> &...memptr) :mMemPtr (memptr...) {}

		inline void compute_visit (UNIT1 &visitor ,UNIT2 &context) const override {
			Detail::template_visit (visitor ,context ,mMemPtr) ;
		}
	} ;

	class Member {
	private:
		friend Serializer ;
		const Serializer &mBase ;
		UNIT2 &mContext ;

	public:
		inline Member () = delete ;

		inline Member (const Member &) = delete ;

		inline Member (Member &&) noexcept = default ;

		inline void friend_visit (UNIT1 &) const & = delete ;

		inline void friend_visit (UNIT1 &visitor) && popping {
			mBase.mBinder->compute_visit (visitor ,mContext) ;
		}

	private:
		inline explicit Member (const Serializer &base ,UNIT2 &context) popping : mBase (base) ,mContext (context) {}
	} ;

private:
	class Detail ;
	StrongRef<const Binder> mBinder ;

public:
	inline Serializer () = delete ;

	template <class... _ARGS>
	inline explicit Serializer (const DEF<_ARGS UNIT2::*> &...memptr) {
		_STATIC_ASSERT_ (_CAPACITYOF_ (_ARGS) > 0) ;
		_DEBUG_ASSERT_ (Detail::template_available (memptr...)) ;
		mBinder = StrongRef<const ImplBinder<_ARGS...>>::make (memptr...) ;
	}

	inline Member operator() (UNIT2 &context) const popping {
		_DEBUG_ASSERT_ (mBinder.exist ()) ;
		return Member ((*this) ,context) ;
	}

private:
	class Detail :private Wrapped<void> {
	public:
		inline static BOOL template_available () {
			return TRUE ;
		}

		template <class _ARG1 ,class... _ARGS>
		inline static BOOL template_available (const DEF<_ARG1 UNIT2::*> &memptr_one ,const DEF<_ARGS UNIT2::*> &...memptr_rest) {
			if (memptr_one == NULL)
				return FALSE ;
			return template_available (memptr_rest...) ;
		}

		inline static void template_visit (UNIT1 &visitor ,UNIT2 &context ,const Tuple<> &memptr) {
			_STATIC_WARNING_ ("noop") ;
		}

		template <class... _ARGS>
		inline static void template_visit (UNIT1 &visitor ,UNIT2 &context ,const Tuple<DEF<_ARGS UNIT2::*>...> &memptr) {
			auto &r1y = (context.*memptr.one ()) ;
			visitor.visit (r1y) ;
			template_visit (visitor ,context ,memptr.rest ()) ;
		}
	} ;
} ;

#ifdef __CSC_COMPILER_GNUC__
template <class UNIT1 ,class UNIT2>
inline void Serializer<UNIT1 ,UNIT2>::Binder::compute_visit (UNIT1 &visitor ,UNIT2 &context) const {
	//@error: g++4.8 is too useless to compile with a function-local-type
	_STATIC_WARNING_ ("unexpected") ;
	_DEBUG_ASSERT_ (FALSE) ;
	}
#endif
} ;