﻿#pragma once

#ifndef __CSC_EXTEND__
#define __CSC_EXTEND__
#endif

#include "csc.hpp"
#include "csc_core.hpp"
#include "csc_basic.hpp"

namespace CSC {
#ifdef __CSC_UNITTEST__
class GlobalWatch
	:private Wrapped<void> {
public:
	struct Public {
		imports void done (const Exception &e) ;
	} ;

private:
	struct Private {
		template <class>
		class WatchInterface ;
	} ;

public:
	imports void done (const Exception &e) {
		Public::done (e) ;
	}

	template <class _ARG1 ,class _ARG2>
	imports void done (const ARGVF<_ARG1> & ,const Plain<STR> &name ,_ARG2 &data) {
		struct Dependent ;
		using WatchInterface = typename DEPENDENT_TYPE<Private ,Dependent>::template WatchInterface<_ARG2> ;
		static WatchInterface mInstance ;
		mInstance.mName = name.self ;
		mInstance.mAddress = DEPTR[data] ;
		mInstance.mWatch (data) ;
	}
} ;

template <class UNIT>
class GlobalWatch::Private::WatchInterface
	:private Interface {
private:
	friend GlobalWatch ;
	PTR<const STR> mName ;
	PTR<UNIT> mAddress ;
	FLAG mTypeMID ;
	Function<void (UNIT &)> mWatch ;

public:
	implicit WatchInterface () {
		mName = NULL ;
		mAddress = NULL ;
		mTypeMID = _TYPEMID_ (ARGV<UNIT>::null) ;
		mWatch = Function<void (UNIT &)> ([] (UNIT &) {}) ;
	} ;
} ;
#endif

template <class>
class GlobalStatic ;

template <class UNIT>
class Singleton
	:private Proxy {
	_STATIC_ASSERT_ (stl::is_class<UNIT>::value) ;
	_STATIC_ASSERT_ (!stl::is_default_constructible<UNIT>::value) ;
	_STATIC_ASSERT_ (stl::is_nothrow_destructible<UNIT>::value) ;

private:
	class Holder {
	private:
		friend Singleton ;
		UNIT mValue ;

	public:
		template <class... _ARGS>
		explicit Holder (_ARGS &&...initval)
			:mValue (_FORWARD_ (ARGV<_ARGS>::null ,initval)...) {}
	} ;

private:
	friend GlobalStatic<Singleton> ;
	AutoRef<Holder> mHolder ;

private:
	implicit Singleton () {
		mHolder = AutoRef<Holder>::make () ;
	}

	UNIT &to () leftvalue {
		_DEBUG_ASSERT_ (mHolder.exist ()) ;
		return mHolder->mValue ;
	}

	inline implicit operator UNIT & () leftvalue {
		return to () ;
	}

public:
	//@warn: static instance across DLL ruins Singleton
	imports UNIT &instance () {
		struct Dependent ;
		using GlobalStatic = DEPENDENT_TYPE<GlobalStatic<Singleton<UNIT>> ,Dependent> ;
		return GlobalStatic::unique () ;
	}
} ;

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
	MEGA mValue ;

public:
	implicit VAR128 () = default ;

	implicit VAR128 (const VAR64 &that) {
		v2i1 = DATA (that) ;
		v2i0 = DATA (-_EBOOL_ (that < 0)) ;
	}

	inline explicit operator VAR32 () const {
		return VAR32 (v2i1) ;
	}

	inline explicit operator VAR64 () const {
		return VAR64 (v2i1) ;
	}

	inline BOOL operator== (const VAR128 &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const VAR128 &that) const {
		return !equal (that) ;
	}

	inline BOOL operator< (const VAR128 &that) const {
		return BOOL (compr (that) < 0) ;
	}

	inline BOOL operator>= (const VAR128 &that) const {
		return BOOL (compr (that) >= 0) ;
	}

	inline BOOL operator> (const VAR128 &that) const {
		return BOOL (compr (that) > 0) ;
	}

	inline BOOL operator<= (const VAR128 &that) const {
		return BOOL (compr (that) <= 0) ;
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
		ret.v2i0 = v2i0 + that.v2i0 + _EBOOL_ (v2i1 > ~that.v2i1) ;
		ret.v2i1 = v2i1 + that.v2i1 ;
		return _MOVE_ (ret) ;
	}

	inline VAR128 &operator+= (const VAR128 &that) {
		v2i0 += that.v2i0 + _EBOOL_ (v2i1 > ~that.v2i1) ;
		v2i1 += that.v2i1 ;
		return DEREF[this] ;
	}

	inline VAR128 operator- (const VAR128 &that) const {
		VAR128 ret = 0 ;
		ret.v2i0 = v2i0 - that.v2i0 - _EBOOL_ (v2i1 < that.v2i1) ;
		ret.v2i1 = v2i1 - that.v2i1 ;
		return _MOVE_ (ret) ;
	}

	inline VAR128 &operator-= (const VAR128 &that) {
		v2i0 -= that.v2i0 + _EBOOL_ (v2i1 < that.v2i1) ;
		v2i1 -= that.v2i1 ;
		return DEREF[this] ;
	}

	inline VAR128 operator* (const VAR128 &that) const {
		VAR128 ret = 0 ;
		auto rax = DATA (0) ;
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
		return _MOVE_ (ret) ;
	}

	inline VAR128 &operator*= (const VAR128 &that) {
		DEREF[this] = DEREF[this] * that ;
		return DEREF[this] ;
	}

	inline VAR128 operator/ (const VAR128 &that) const {
		VAR128 ret = 0 ;
		const auto r1x = _CAST_ (ARGV<VAR64>::null ,v2i0) ;
		const auto r2x = _CAST_ (ARGV<VAR64>::null ,that.v2i0) ;
		auto fax = TRUE ;
		if switch_once (fax) {
			if (!(r1x >= 0))
				discard ;
			if (!(that.v4i0 == 0))
				discard ;
			if (!(that.v4i1 == 0))
				discard ;
			if (!(that.v4i2 == 0))
				discard ;
			auto rax = DATA (0) ;
			const auto r3x = DATA (that.v4i3) ;
			_DEBUG_ASSERT_ (r3x != 0) ;
			rax = (DATA (rax % r3x) << (_SIZEOF_ (CHAR) * 8)) | DATA (v4i0) ;
			ret.v4i0 = CHAR (rax / r3x) ;
			rax = (DATA (rax % r3x) << (_SIZEOF_ (CHAR) * 8)) | DATA (v4i1) ;
			ret.v4i1 = CHAR (rax / r3x) ;
			rax = (DATA (rax % r3x) << (_SIZEOF_ (CHAR) * 8)) | DATA (v4i2) ;
			ret.v4i2 = CHAR (rax / r3x) ;
			rax = (DATA (rax % r3x) << (_SIZEOF_ (CHAR) * 8)) | DATA (v4i3) ;
			ret.v4i3 = CHAR (rax / r3x) ;
		}
		if switch_once (fax) {
			if (!(v2i0 == DATA (VAR64_MIN)))
				discard ;
			if (!(v2i1 == 0))
				discard ;
			if (!(r2x >= 0))
				discard ;
			ret = -(-(DEREF[this] + that) / that + 1) ;
		}
		if switch_once (fax) {
			if (!(v2i0 == DATA (VAR64_MIN)))
				discard ;
			if (!(v2i1 == 0))
				discard ;
			if (!(r2x < 0))
				discard ;
			ret = -(-(DEREF[this] - that) / that - 1) ;
		}
		if switch_once (fax) {
			if (!(r1x < 0))
				discard ;
			ret = -(-DEREF[this] / that) ;
		}
		if switch_once (fax) {
			if (!(r1x >= 0))
				discard ;
			if (!(that.v2i0 == DATA (VAR64_MIN)))
				discard ;
			if (!(that.v2i1 == 0))
				discard ;
			ret = VAR128 (0) ;
		}
		if switch_once (fax) {
			if (!(r1x >= 0))
				discard ;
			if (!(r2x < 0))
				discard ;
			ret = DEREF[this] / (-that) ;
		}
		if switch_once (fax) {
			ret = slow_divide (DEREF[this] ,that) ;
		}
		return _MOVE_ (ret) ;
	}

	inline VAR128 &operator/= (const VAR128 &that) {
		DEREF[this] = DEREF[this] / that ;
		return DEREF[this] ;
	}

	inline VAR128 operator% (const VAR128 &that) const {
		VAR128 ret = 0 ;
		const auto r1x = _CAST_ (ARGV<VAR64>::null ,v2i0) ;
		const auto r2x = _CAST_ (ARGV<VAR64>::null ,that.v2i0) ;
		auto fax = TRUE ;
		if switch_once (fax) {
			if (!(r1x >= 0))
				discard ;
			if (!(that.v4i0 == 0))
				discard ;
			if (!(that.v4i1 == 0))
				discard ;
			if (!(that.v4i2 == 0))
				discard ;
			auto rax = DATA (0) ;
			const auto r3x = DATA (that.v4i3) ;
			_DEBUG_ASSERT_ (r3x != 0) ;
			rax = (DATA (rax % r3x) << (_SIZEOF_ (CHAR) * 8)) | DATA (v4i0) ;
			ret.v4i0 = 0 ;
			rax = (DATA (rax % r3x) << (_SIZEOF_ (CHAR) * 8)) | DATA (v4i1) ;
			ret.v4i1 = 0 ;
			rax = (DATA (rax % r3x) << (_SIZEOF_ (CHAR) * 8)) | DATA (v4i2) ;
			ret.v4i2 = 0 ;
			rax = (DATA (rax % r3x) << (_SIZEOF_ (CHAR) * 8)) | DATA (v4i3) ;
			ret.v4i3 = CHAR (rax % r3x) ;
		}
		if switch_once (fax) {
			if (!(v2i0 == DATA (VAR64_MIN)))
				discard ;
			if (!(v2i1 == 0))
				discard ;
			if (!(r2x >= 0))
				discard ;
			ret = -(-(DEREF[this] + that) % that) ;
		}
		if switch_once (fax) {
			if (!(v2i0 == DATA (VAR64_MIN)))
				discard ;
			if (!(v2i1 == 0))
				discard ;
			if (!(r2x < 0))
				discard ;
			ret = -(-(DEREF[this] - that) % that) ;
		}
		if switch_once (fax) {
			if (!(r1x < 0))
				discard ;
			ret = -(-DEREF[this] % that) ;
		}
		if switch_once (fax) {
			if (!(r1x >= 0))
				discard ;
			if (!(that.v2i0 == DATA (VAR64_MIN)))
				discard ;
			if (!(that.v2i1 == 0))
				discard ;
			ret = DEREF[this] ;
		}
		if switch_once (fax) {
			if (!(r1x >= 0))
				discard ;
			if (!(r2x < 0))
				discard ;
			ret = DEREF[this] % (-that) ;
		}
		if switch_once (fax) {
			ret = that - slow_divide (DEREF[this] ,that) * that ;
		}
		return _MOVE_ (ret) ;
	}

	inline VAR128 &operator%= (const VAR128 &that) {
		DEREF[this] = DEREF[this] % that ;
		return DEREF[this] ;
	}

	inline VAR128 operator+ () const {
		return DEREF[this] ;
	}

	inline VAR128 operator- () const {
		VAR128 ret = 0 ;
		ret.v2i1 = ~v2i1 + 1 ;
		ret.v2i0 = ~v2i0 + _EBOOL_ (ret.v2i1 == DATA (0)) ;
		return _MOVE_ (ret) ;
	}

	inline VAR128 &operator++ () {
		v2i1++ ;
		v2i0 += _EBOOL_ (v2i1 == DATA (0)) ;
		return DEREF[this] ;
	}

	inline VAR128 operator++ (VAR32) side_effects {
		VAR128 ret = DEREF[this] ;
		++DEREF[this] ;
		return _MOVE_ (ret) ;
	}

	inline VAR128 &operator-- () {
		v2i1-- ;
		v2i0 -= _EBOOL_ (v2i1 == DATA (-1)) ;
		return DEREF[this] ;
	}

	inline VAR128 operator-- (VAR32) side_effects {
		VAR128 ret = DEREF[this] ;
		--DEREF[this] ;
		return _MOVE_ (ret) ;
	}

private:
	BOOL equal (const VAR128 &that) const {
		if (v2i1 != that.v2i1)
			return FALSE ;
		if (v2i0 != that.v2i0)
			return FALSE ;
		return TRUE ;
	}

	FLAG compr (const VAR128 &that) const {
		const auto r1x = _CAST_ (ARGV<VAR64>::null ,v2i0) ;
		const auto r2x = _CAST_ (ARGV<VAR64>::null ,that.v2i0) ;
		const auto r3x = U::OPERATOR_COMPR::invoke (r1x ,r2x) ;
		if (r3x != 0)
			return r3x ;
		return U::OPERATOR_COMPR::invoke (v2i1 ,that.v2i1) ;
	}

	DATA &m_v2i0 () leftvalue {
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = WORD (0X0001) ;
		return _CAST_ (ARGV<DATA[2]>::null ,mValue)[_CAST_ (ARGV<BYTE[2]>::null ,r1x)[0]] ;
	}

	const DATA &m_v2i0 () const leftvalue {
		const auto r1x = WORD (0X0001) ;
		return _CAST_ (ARGV<DATA[2]>::null ,mValue)[_CAST_ (ARGV<BYTE[2]>::null ,r1x)[0]] ;
	}

	DATA &m_v2i1 () leftvalue {
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = WORD (0X0001) ;
		return _CAST_ (ARGV<DATA[2]>::null ,mValue)[_CAST_ (ARGV<BYTE[2]>::null ,r1x)[1]] ;
	}

	const DATA &m_v2i1 () const leftvalue {
		const auto r1x = WORD (0X0001) ;
		return _CAST_ (ARGV<DATA[2]>::null ,mValue)[_CAST_ (ARGV<BYTE[2]>::null ,r1x)[1]] ;
	}

	CHAR &m_v4i0 () leftvalue {
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_ (ARGV<CHAR[4]>::null ,mValue)[_CAST_ (ARGV<BYTE[4]>::null ,r1x)[0]] ;
	}

	const CHAR &m_v4i0 () const leftvalue {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_ (ARGV<CHAR[4]>::null ,mValue)[_CAST_ (ARGV<BYTE[4]>::null ,r1x)[0]] ;
	}

	CHAR &m_v4i1 () leftvalue {
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_ (ARGV<CHAR[4]>::null ,mValue)[_CAST_ (ARGV<BYTE[4]>::null ,r1x)[1]] ;
	}

	const CHAR &m_v4i1 () const leftvalue {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_ (ARGV<CHAR[4]>::null ,mValue)[_CAST_ (ARGV<BYTE[4]>::null ,r1x)[1]] ;
	}

	CHAR &m_v4i2 () leftvalue {
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_ (ARGV<CHAR[4]>::null ,mValue)[_CAST_ (ARGV<BYTE[4]>::null ,r1x)[2]] ;
	}

	const CHAR &m_v4i2 () const leftvalue {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_ (ARGV<CHAR[4]>::null ,mValue)[_CAST_ (ARGV<BYTE[4]>::null ,r1x)[2]] ;
	}

	CHAR &m_v4i3 () leftvalue {
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_ (ARGV<CHAR[4]>::null ,mValue)[_CAST_ (ARGV<BYTE[4]>::null ,r1x)[3]] ;
	}

	const CHAR &m_v4i3 () const leftvalue {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_ (ARGV<CHAR[4]>::null ,mValue)[_CAST_ (ARGV<BYTE[4]>::null ,r1x)[3]] ;
	}

private:
	imports VAR128 slow_divide (const VAR128 &y ,const VAR128 &x) {
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
			auto fax = TRUE ;
			if switch_once (fax) {
				if (!(r1x < y))
					discard ;
				rax[0] = ret + 1 ;
			}
			if switch_once (fax) {
				rax[1] = ret - 1 ;
			}
		}
		ret -= _EBOOL_ (x * ret > y) ;
		return _MOVE_ (ret) ;
	}

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

namespace U {
struct CONSTEXPR_MAX_SIZEOF {
	imports constexpr LENGTH invoke (const ARGVF<ARGVS<>> &) {
		return 1 ;
	}

	template <class _ARG1>
	imports constexpr LENGTH invoke (const ARGVF<_ARG1> &) {
		using HINT_T1 = ARGVS_ONE_TYPE<_ARG1> ;
		using HINT_T2 = ARGVS_REST_TYPE<_ARG1> ;
		return _MAX_<const LENGTH> (_SIZEOF_ (HINT_T1) ,invoke (ARGV<HINT_T2>::null)) ;
	}
} ;

struct CONSTEXPR_MAX_ALIGNOF {
	imports constexpr LENGTH invoke (const ARGVF<ARGVS<>> &) {
		return 1 ;
	}

	template <class _ARG1>
	imports constexpr LENGTH invoke (const ARGVF<_ARG1> &) {
		using HINT_T1 = ARGVS_ONE_TYPE<_ARG1> ;
		using HINT_T2 = ARGVS_REST_TYPE<_ARG1> ;
		return _MAX_<const LENGTH> (_ALIGNOF_ (HINT_T1) ,invoke (ARGV<HINT_T2>::null)) ;
	}
} ;
} ;

template <class... UNITS>
class Variant final {
	_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS...>) > 0) ;
	_STATIC_ASSERT_ (!stl::is_any_same<REMOVE_CVR_TYPE<UNITS>...>::value) ;

private:
	static constexpr auto VARIANT_ALIGN = U::CONSTEXPR_MAX_ALIGNOF::invoke (ARGV<ARGVS<UNITS...>>::null) ;
	static constexpr auto VARIANT_SIZE = U::CONSTEXPR_MAX_SIZEOF::invoke (ARGV<ARGVS<UNITS...>>::null) ;

	//@error: fuck g++4.8
	template <LENGTH ALIGN = VARIANT_ALIGN>
	struct ALIGNED_UNION {
		alignas (ALIGN) DEF<BYTE[VARIANT_SIZE]> unused ;
	} ;

	using HINT_OPTIONAL = INDEX_TO_TYPE<ZERO ,ARGVS<UNITS...>> ;

private:
	TEMP<ALIGNED_UNION<>> mVariant ;
	INDEX mIndex ;

public:
	implicit Variant ()
		:Variant (ARGVP0) {
		const auto r1x = default_constructible_index (ARGV<ZERO>::null ,ARGV<ARGVS<UNITS...>>::null) ;
		template_construct (r1x ,ARGV<ARGVS<UNITS...>>::null) ;
		mIndex = r1x ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<(!stl::is_same<REMOVE_CVR_TYPE<_ARG1> ,Variant>::value && !stl::is_same<REMOVE_CVR_TYPE<_ARG1> ,REMOVE_CVR_TYPE<decltype (ARGVP0)>>::value)>>
	implicit Variant (_ARG1 &&that)
		:Variant (ARGVP0) {
		using HINT_T1 = INDEX_OF_TYPE<REMOVE_CVR_TYPE<_ARG1> ,ARGVS<REMOVE_CVR_TYPE<UNITS>...>> ;
		using HINT_T2 = ARGC<(stl::is_constructible<REMOVE_CVR_TYPE<_ARG1> ,_ARG1 &&>::value)> ;
		_STATIC_ASSERT_ (HINT_T1::value != VAR_NONE) ;
		auto &r1x = _LOAD_ (ARGV<TEMP<REMOVE_CVR_TYPE<_ARG1>>>::null ,DEPTR[mVariant]) ;
		template_create (ARGV<HINT_T2>::null ,DEPTR[r1x] ,_FORWARD_ (ARGV<_ARG1>::null ,that)) ;
		mIndex = HINT_T1::value ;
	}

	implicit ~Variant () noexcept {
		if (mIndex == VAR_NONE)
			return ;
		template_destruct (mIndex ,ARGV<ARGVS<UNITS...>>::null) ;
		mIndex = VAR_NONE ;
	}

	implicit Variant (const Variant &that)
		:Variant (ARGVP0) {
		if (that.mIndex == VAR_NONE)
			return ;
		template_copy_construct (that ,that.mIndex ,ARGV<ARGVS<UNITS...>>::null) ;
		mIndex = that.mIndex ;
	}

	inline Variant &operator= (const Variant &that) {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~Variant () ;
			new (this) Variant (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	implicit Variant (Variant &&that) noexcept
		:Variant (ARGVP0) {
		if (that.mIndex == VAR_NONE)
			return ;
		template_move_construct (that ,that.mIndex ,ARGV<ARGVS<UNITS...>>::null) ;
		mIndex = that.mIndex ;
	}

	inline Variant &operator= (Variant &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~Variant () ;
			new (this) Variant (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	BOOL exist () const {
		if (mIndex == VAR_NONE)
			return FALSE ;
		return TRUE ;
	}

	template <class _ARG1>
	BOOL available (const ARGVF<_ARG1> &) const {
		using HINT_T1 = INDEX_OF_TYPE<REMOVE_CVR_TYPE<_ARG1> ,ARGVS<REMOVE_CVR_TYPE<UNITS>...>> ;
		if (!exist ())
			return FALSE ;
		if (mIndex != HINT_T1::value)
			return FALSE ;
		return TRUE ;
	}

	HINT_OPTIONAL &to () leftvalue {
		_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS...>) == 1) ;
		_DYNAMIC_ASSERT_ (exist ()) ;
		auto &r1x = _LOAD_ (ARGV<TEMP<HINT_OPTIONAL>>::null ,DEPTR[mVariant]) ;
		return _CAST_ (ARGV<HINT_OPTIONAL>::null ,r1x) ;
	}

	inline implicit operator HINT_OPTIONAL & () leftvalue {
		return to () ;
	}

	const HINT_OPTIONAL &to () const leftvalue {
		_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS...>) == 1) ;
		_DYNAMIC_ASSERT_ (exist ()) ;
		auto &r1x = _LOAD_ (ARGV<TEMP<HINT_OPTIONAL>>::null ,DEPTR[mVariant]) ;
		return _CAST_ (ARGV<HINT_OPTIONAL>::null ,r1x) ;
	}

	inline implicit operator const HINT_OPTIONAL & () const leftvalue {
		return to () ;
	}

	template <class _ARG1>
	void apply (const Function<void (_ARG1 &)> &proc) {
		if (!available (ARGV<_ARG1>::null))
			return ;
		auto &r1x = _LOAD_ (ARGV<TEMP<_ARG1>>::null ,DEPTR[mVariant]) ;
		proc (_CAST_ (ARGV<_ARG1>::null ,r1x)) ;
	}

	template <class _ARG1>
	void apply (const Function<MEMPTR<void (_ARG1 &)>> &proc) {
		if (!available (ARGV<_ARG1>::null))
			return ;
		auto &r1x = _LOAD_ (ARGV<TEMP<_ARG1>>::null ,DEPTR[mVariant]) ;
		proc (_CAST_ (ARGV<_ARG1>::null ,r1x)) ;
	}

	//@warn: none class shall be base on its address
	void aswap (Variant &that) {
		_SWAP_ (mVariant ,that.mVariant) ;
		_SWAP_ (mIndex ,that.mIndex) ;
	}

public:
	imports Variant nullopt () {
		return Variant (ARGVP0) ;
	}

private:
	explicit Variant (const DEF<decltype (ARGVP0)> &) noexcept
		:mIndex (VAR_NONE) {}

private:
	void template_construct (const INDEX &index ,const ARGVF<ARGVS<>> &) {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1>
	void template_construct (const INDEX &index ,const ARGVF<_ARG1> &) {
		using HINT_T1 = ARGVS_ONE_TYPE<_ARG1> ;
		using HINT_T2 = ARGVS_REST_TYPE<_ARG1> ;
		using HINT_T3 = ARGC<(stl::is_default_constructible<HINT_T1>::value)> ;
		_STATIC_ASSERT_ (stl::is_nothrow_move_constructible<HINT_T1>::value) ;
		_STATIC_ASSERT_ (stl::is_nothrow_move_assignable<HINT_T1>::value) ;
		const auto r1x = BOOL (index == 0) ;
		if switch_once (TRUE) {
			if (!r1x)
				discard ;
			auto &r2x = _LOAD_ (ARGV<TEMP<HINT_T1>>::null ,DEPTR[mVariant]) ;
			template_create (ARGV<HINT_T3>::null ,DEPTR[r2x]) ;
		}
		if (r1x)
			return ;
		template_construct ((index - 1) ,ARGV<HINT_T2>::null) ;
	}

	void template_destruct (const INDEX &index ,const ARGVF<ARGVS<>> &) {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1>
	void template_destruct (const INDEX &index ,const ARGVF<_ARG1> &) {
		using HINT_T1 = ARGVS_ONE_TYPE<_ARG1> ;
		using HINT_T2 = ARGVS_REST_TYPE<_ARG1> ;
		_STATIC_ASSERT_ (stl::is_nothrow_destructible<HINT_T1>::value) ;
		_STATIC_ASSERT_ (stl::is_nothrow_move_constructible<HINT_T1>::value) ;
		_STATIC_ASSERT_ (stl::is_nothrow_move_assignable<HINT_T1>::value) ;
		const auto r1x = BOOL (index == 0) ;
		if switch_once (TRUE) {
			if (!r1x)
				discard ;
			auto &r2x = _LOAD_ (ARGV<TEMP<HINT_T1>>::null ,DEPTR[mVariant]) ;
			_DESTROY_ (DEPTR[r2x]) ;
		}
		if (r1x)
			return ;
		template_destruct ((index - 1) ,ARGV<HINT_T2>::null) ;
	}

	void template_copy_construct (const Variant &that ,const INDEX &index ,const ARGVF<ARGVS<>> &) {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1>
	void template_copy_construct (const Variant &that ,const INDEX &index ,const ARGVF<_ARG1> &) {
		using HINT_T1 = ARGVS_ONE_TYPE<_ARG1> ;
		using HINT_T2 = ARGVS_REST_TYPE<_ARG1> ;
		using HINT_T3 = ARGC<(stl::is_copy_constructible<HINT_T1>::value && stl::is_nothrow_move_constructible<HINT_T1>::value)> ;
		const auto r1x = BOOL (index == 0) ;
		if switch_once (TRUE) {
			if (!r1x)
				discard ;
			auto &r2x = _LOAD_ (ARGV<TEMP<HINT_T1>>::null ,DEPTR[mVariant]) ;
			auto &r3x = _LOAD_ (ARGV<TEMP<HINT_T1>>::null ,DEPTR[that.mVariant]) ;
			template_create (ARGV<HINT_T3>::null ,DEPTR[r2x] ,_MOVE_ (_CAST_ (ARGV<HINT_T1>::null ,r3x))) ;
		}
		if (r1x)
			return ;
		template_copy_construct (that ,(index - 1) ,ARGV<HINT_T2>::null) ;
	}

	void template_move_construct (Variant &that ,const INDEX &index ,const ARGVF<ARGVS<>> &) {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1>
	void template_move_construct (Variant &that ,const INDEX &index ,const ARGVF<_ARG1> &) {
		using HINT_T1 = ARGVS_ONE_TYPE<_ARG1> ;
		using HINT_T2 = ARGVS_REST_TYPE<_ARG1> ;
		_STATIC_ASSERT_ (stl::is_nothrow_move_constructible<HINT_T1>::value) ;
		_STATIC_ASSERT_ (stl::is_nothrow_move_assignable<HINT_T1>::value) ;
		const auto r1x = BOOL (index == 0) ;
		if switch_once (TRUE) {
			if (!r1x)
				discard ;
			auto &r2x = _LOAD_ (ARGV<TEMP<HINT_T1>>::null ,DEPTR[mVariant]) ;
			auto &r3x = _LOAD_ (ARGV<TEMP<HINT_T1>>::null ,DEPTR[that.mVariant]) ;
			template_create (ARGV<ARGC<TRUE>>::null ,DEPTR[r2x] ,_MOVE_ (_CAST_ (ARGV<HINT_T1>::null ,r3x))) ;
		}
		if (r1x)
			return ;
		template_move_construct (that ,(index - 1) ,ARGV<HINT_T2>::null) ;
	}

private:
	template <class _ARG1>
	imports INDEX default_constructible_index (const ARGVF<_ARG1> & ,const ARGVF<ARGVS<>> &) {
		return VAR_NONE ;
	}

	template <class _ARG1 ,class _ARG2>
	imports INDEX default_constructible_index (const ARGVF<_ARG1> & ,const ARGVF<_ARG2> &) {
		using HINT_T1 = ARGVS_ONE_TYPE<_ARG2> ;
		using HINT_T2 = ARGVS_REST_TYPE<_ARG2> ;
		if (stl::is_default_constructible<HINT_T1>::value)
			return _ARG1::value ;
		return default_constructible_index (ARGV<INCREASE<_ARG1>>::null ,ARGV<HINT_T2>::null) ;
	}

	template <class _ARG1 ,class... _ARGS>
	imports void template_create (const ARGVF<ARGC<TRUE>> & ,const PTR<TEMP<_ARG1>> &address ,_ARGS &&...initval) {
		_CREATE_ (address ,_FORWARD_ (ARGV<_ARGS>::null ,initval)...) ;
	}

	template <class _ARG1 ,class... _ARGS>
	imports void template_create (const ARGVF<ARGC<FALSE>> & ,const PTR<TEMP<_ARG1>> &address ,_ARGS &&...initval) {
		_DYNAMIC_ASSERT_ (FALSE) ;
	}
} ;

template <class UNIT>
using Optional = Variant<UNIT> ;

template <class UNIT>
class Monostate
	:private Proxy {
private:
	SharedRef<UNIT> mValue ;

public:
	implicit Monostate () {
		mValue = SharedRef<UNIT>::make () ;
	}

	UNIT &to () const leftvalue {
		return mValue.self ;
	}

	inline implicit operator UNIT & () const leftvalue {
		return to () ;
	}

	void swap (Monostate &that) {
		_SWAP_ (mValue ,that.mValue) ;
	}
} ;

template <class...>
class Tuple ;

template <>
class Tuple<> {
public:
	implicit Tuple () = default ;

	LENGTH capacity () const {
		return _CAPACITYOF_ (ARGVS<>) ;
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
		return 0 ;
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
} ;

template <class UNIT1 ,class... UNITS>
class Tuple<UNIT1 ,UNITS...>
	:private Tuple<UNITS...> {
	_STATIC_ASSERT_ (!stl::is_rvalue_reference<UNIT1>::value) ;

private:
	UNIT1 mValue ;

public:
	implicit Tuple () = default ;

	implicit Tuple (FORWARD_TRAITS_TYPE<UNIT1> &&one_ ,FORWARD_TRAITS_TYPE<UNITS> &&...rest_)
		:Tuple<UNITS...> (_FORWARD_ (ARGV<FORWARD_TRAITS_TYPE<UNITS>>::null ,rest_)...) ,mValue (_FORWARD_ (ARGV<FORWARD_TRAITS_TYPE<UNIT1>>::null ,one_)) {}

	LENGTH capacity () const {
		return _CAPACITYOF_ (ARGVS<UNIT1 ,UNITS...>) ;
	}

	UNIT1 &one () leftvalue {
		return mValue ;
	}

	const UNIT1 &one () const leftvalue {
		return mValue ;
	}

	Tuple<UNITS...> &rest () leftvalue {
		return DEREF[this] ;
	}

	const Tuple<UNITS...> &rest () const leftvalue {
		return DEREF[this] ;
	}

	template <class _ARG1>
	INDEX_TO_TYPE<DECREASE<_ARG1> ,ARGVS<UNIT1 ,UNITS...>> &pick (const ARGV<ARGVP<_ARG1>> &) leftvalue {
		return template_pick (ARGV<DECREASE<_ARG1>>::null) ;
	}

	template <class _ARG1>
	const INDEX_TO_TYPE<DECREASE<_ARG1> ,ARGVS<UNIT1 ,UNITS...>> &pick (const ARGV<ARGVP<_ARG1>> &) const leftvalue {
		return template_pick (ARGV<DECREASE<_ARG1>>::null) ;
	}

	BOOL equal (const Tuple &that) const {
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

	FLAG compr (const Tuple &that) const {
		const auto r1x = U::OPERATOR_COMPR::invoke (one () ,that.one ()) ;
		if (r1x != 0)
			return r1x ;
		auto &r2x = rest () ;
		auto &r3x = that.rest () ;
		return r2x.compr (r3x) ;
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
	UNIT1 &template_pick (const ARGVF<ZERO> &) leftvalue {
		return one () ;
	}

	template <class _ARG1>
	INDEX_TO_TYPE<_ARG1 ,ARGVS<UNIT1 ,UNITS...>> &template_pick (const ARGVF<_ARG1> &) leftvalue {
		_STATIC_ASSERT_ (_ARG1::value > 0 && _ARG1::value <= _CAPACITYOF_ (ARGVS<UNITS...>)) ;
		return rest ().template_pick (ARGV<DECREASE<_ARG1>>::null) ;
	}

	const UNIT1 &template_pick (const ARGVF<ZERO> &) const leftvalue {
		return one () ;
	}

	template <class _ARG1>
	const INDEX_TO_TYPE<_ARG1 ,ARGVS<UNIT1 ,UNITS...>> &template_pick (const ARGVF<_ARG1> &) const leftvalue {
		_STATIC_ASSERT_ (_ARG1::value > 0 && _ARG1::value <= _CAPACITYOF_ (ARGVS<UNITS...>)) ;
		return rest ().template_pick (ARGV<DECREASE<_ARG1>>::null) ;
	}
} ;

template <class... UNITS>
using TupleBinder = Tuple<UNITS &...> ;

template <class UNIT1 ,class... UNITS>
template <class... UNITS_>
class Function<UNIT1 (UNITS...)>::Private::ImplHolder<UNIT1 (UNITS... ,UNITS_...)>
	:public Function<UNIT1 (UNITS...)>::Holder {
private:
	Function<UNIT1 (UNITS... ,UNITS_...)> mFunctor ;
	Tuple<REMOVE_CVR_TYPE<UNITS_>...> mParameter ;

public:
	template <class... _ARGS>
	explicit ImplHolder (const DEF<UNIT1 (UNITS... ,UNITS_...)> &functor ,_ARGS &&...initval)
		:mFunctor (functor) ,mParameter (_FORWARD_ (ARGV<_ARGS>::null ,initval)...) {}

	UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const override {
		return template_invoke (mParameter ,_FORWARD_ (ARGV<FORWARD_TRAITS_TYPE<UNITS>>::null ,funcval)...) ;
	}

private:
	UNIT1 template_invoke (const Tuple<> &parameter ,FORWARD_TRAITS_TYPE<UNITS> &&...funcval1 ,const REMOVE_CVR_TYPE<UNITS_> &...funcval2) const {
		return mFunctor (_FORWARD_ (ARGV<FORWARD_TRAITS_TYPE<UNITS>>::null ,funcval1)... ,funcval2...) ;
	}

	template <class _ARG1 ,class... _ARGS>
	UNIT1 template_invoke (const _ARG1 &parameter ,_ARGS &&...funcval) const {
		return template_invoke (parameter.rest () ,_FORWARD_ (ARGV<_ARGS>::null ,funcval)... ,parameter.one ()) ;
	}
} ;

template <class...>
class AllOfTuple ;

template <class...>
class AnyOfTuple ;

template <class... UNITS>
class AllOfTuple
	:private Proxy {
	_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS...>) > 0) ;
	_STATIC_ASSERT_ (stl::is_all_same<UNITS...>::value) ;

private:
	using HINT_WRAPPED = INDEX_TO_TYPE<ZERO ,ARGVS<UNITS...>> ;

private:
	TupleBinder<const UNITS...> mBinder ;

public:
	implicit AllOfTuple () = delete ;

	implicit AllOfTuple (const UNITS &...initval)
		:mBinder (initval...) {}

	inline implicit operator BOOL () rightvalue {
		return template_boolean (mBinder) ;
	}

	inline BOOL operator== (const HINT_WRAPPED &that) const {
		return template_equal (mBinder ,that) ;
	}

	inline friend BOOL operator== (const HINT_WRAPPED &that ,const AllOfTuple &self_) {
		return _MOVE_ (self_) == that ;
	}

	inline BOOL operator!= (const HINT_WRAPPED &that) const {
		return template_not_equal (mBinder ,that) ;
	}

	inline friend BOOL operator!= (const HINT_WRAPPED &that ,const AllOfTuple &self_) {
		return _MOVE_ (self_) != that ;
	}

	inline BOOL operator< (const HINT_WRAPPED &that) const {
		return template_less (mBinder ,that) ;
	}

	inline friend BOOL operator< (const HINT_WRAPPED &that ,const AllOfTuple &self_) {
		return _MOVE_ (self_) > that ;
	}

	inline BOOL operator>= (const HINT_WRAPPED &that) const {
		return template_not_less (mBinder ,that) ;
	}

	inline friend BOOL operator>= (const HINT_WRAPPED &that ,const AllOfTuple &self_) {
		return _MOVE_ (self_) <= that ;
	}

	inline BOOL operator> (const HINT_WRAPPED &that) const {
		return template_less (that ,mBinder) ;
	}

	inline friend BOOL operator> (const HINT_WRAPPED &that ,const AllOfTuple &self_) {
		return _MOVE_ (self_) < that ;
	}

	inline BOOL operator<= (const HINT_WRAPPED &that) const {
		return template_not_less (that ,mBinder) ;
	}

	inline friend BOOL operator<= (const HINT_WRAPPED &that ,const AllOfTuple &self_) {
		return _MOVE_ (self_) >= that ;
	}

private:
	imports BOOL operator_equal (const HINT_WRAPPED &lhs ,const HINT_WRAPPED &rhs) {
		return BOOL (lhs == rhs) ;
	}

	imports BOOL operator_less (const HINT_WRAPPED &lhs ,const HINT_WRAPPED &rhs) {
		return BOOL (lhs < rhs) ;
	}

	imports BOOL template_boolean (const Tuple<> &self_) {
		return TRUE ;
	}

	template <class _ARG1>
	imports BOOL template_boolean (const _ARG1 &self_) {
		if (!BOOL (self_.one ()))
			return FALSE ;
		return template_boolean (self_.rest ()) ;
	}

	imports BOOL template_equal (const Tuple<> &self_ ,const HINT_WRAPPED &that) {
		return TRUE ;
	}

	template <class _ARG1>
	imports BOOL template_equal (const _ARG1 &self_ ,const HINT_WRAPPED &that) {
		if (!operator_equal (self_.one () ,that))
			return FALSE ;
		return template_equal (self_.rest () ,that) ;
	}

	imports BOOL template_not_equal (const Tuple<> &self_ ,const HINT_WRAPPED &that) {
		return TRUE ;
	}

	template <class _ARG1>
	imports BOOL template_not_equal (const _ARG1 &self_ ,const HINT_WRAPPED &that) {
		if (operator_equal (self_.one () ,that))
			return FALSE ;
		return template_not_equal (self_.rest () ,that) ;
	}

	imports BOOL template_less (const Tuple<> &self_ ,const HINT_WRAPPED &that) {
		return TRUE ;
	}

	template <class _ARG1>
	imports BOOL template_less (const _ARG1 &self_ ,const HINT_WRAPPED &that) {
		if (!operator_less (self_.one () ,that))
			return FALSE ;
		return template_less (self_.rest () ,that) ;
	}

	imports BOOL template_not_less (const Tuple<> &self_ ,const HINT_WRAPPED &that) {
		return TRUE ;
	}

	template <class _ARG1>
	imports BOOL template_not_less (const _ARG1 &self_ ,const HINT_WRAPPED &that) {
		if (operator_less (self_.one () ,that))
			return FALSE ;
		return template_not_less (self_.rest () ,that) ;
	}
} ;

template <class... UNITS>
class AnyOfTuple
	:private Proxy {
	_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS...>) > 0) ;
	_STATIC_ASSERT_ (stl::is_all_same<UNITS...>::value) ;

private:
	using HINT_WRAPPED = INDEX_TO_TYPE<ZERO ,ARGVS<UNITS...>> ;

private:
	TupleBinder<const UNITS...> mBinder ;

public:
	implicit AnyOfTuple () = delete ;

	implicit AnyOfTuple (const UNITS &...initval)
		:mBinder (initval...) {}

	inline implicit operator BOOL () rightvalue {
		return template_boolean (mBinder) ;
	}

	inline BOOL operator== (const HINT_WRAPPED &that) const {
		return template_equal (mBinder ,that) ;
	}

	inline friend BOOL operator== (const HINT_WRAPPED &that ,const AnyOfTuple &self_) {
		return _MOVE_ (self_) == that ;
	}

	inline BOOL operator!= (const HINT_WRAPPED &that) const {
		return template_not_equal (mBinder ,that) ;
	}

	inline friend BOOL operator!= (const HINT_WRAPPED &that ,const AnyOfTuple &self_) {
		return _MOVE_ (self_) != that ;
	}

	inline BOOL operator< (const HINT_WRAPPED &that) const {
		return template_less (mBinder ,that) ;
	}

	inline friend BOOL operator< (const HINT_WRAPPED &that ,const AnyOfTuple &self_) {
		return _MOVE_ (self_) > that ;
	}

	inline BOOL operator>= (const HINT_WRAPPED &that) const {
		return template_not_less (mBinder ,that) ;
	}

	inline friend BOOL operator>= (const HINT_WRAPPED &that ,const AnyOfTuple &self_) {
		return _MOVE_ (self_) <= that ;
	}

	inline BOOL operator> (const HINT_WRAPPED &that) const {
		return template_less (that ,mBinder) ;
	}

	inline friend BOOL operator> (const HINT_WRAPPED &that ,const AnyOfTuple &self_) {
		return _MOVE_ (self_) < that ;
	}

	inline BOOL operator<= (const HINT_WRAPPED &that) const {
		return template_not_less (that ,mBinder) ;
	}

	inline friend BOOL operator<= (const HINT_WRAPPED &that ,const AnyOfTuple &self_) {
		return _MOVE_ (self_) >= that ;
	}

private:
	imports BOOL operator_equal (const HINT_WRAPPED &lhs ,const HINT_WRAPPED &rhs) {
		return BOOL (lhs == rhs) ;
	}

	imports BOOL operator_less (const HINT_WRAPPED &lhs ,const HINT_WRAPPED &rhs) {
		return BOOL (lhs < rhs) ;
	}

	imports BOOL template_boolean (const Tuple<> &self_) {
		return FALSE ;
	}

	template <class _ARG1>
	imports BOOL template_boolean (const _ARG1 &self_) {
		if (BOOL (self_.one ()))
			return TRUE ;
		return template_boolean (self_.rest ()) ;
	}

	imports BOOL template_equal (const Tuple<> &self_ ,const HINT_WRAPPED &that) {
		return FALSE ;
	}

	template <class _ARG1>
	imports BOOL template_equal (const _ARG1 &self_ ,const HINT_WRAPPED &that) {
		if (operator_equal (self_.one () ,that))
			return TRUE ;
		return template_equal (self_.rest () ,that) ;
	}

	imports BOOL template_not_equal (const Tuple<> &self_ ,const HINT_WRAPPED &that) {
		return FALSE ;
	}

	template <class _ARG1>
	imports BOOL template_not_equal (const _ARG1 &self_ ,const HINT_WRAPPED &that) {
		if (!operator_equal (self_.one () ,that))
			return TRUE ;
		return template_not_equal (self_.rest () ,that) ;
	}

	imports BOOL template_less (const Tuple<> &self_ ,const HINT_WRAPPED &that) {
		return FALSE ;
	}

	template <class _ARG1>
	imports BOOL template_less (const _ARG1 &self_ ,const HINT_WRAPPED &that) {
		if (operator_less (self_.one () ,that))
			return TRUE ;
		return template_less (self_.rest () ,that) ;
	}

	imports BOOL template_not_less (const Tuple<> &self_ ,const HINT_WRAPPED &that) {
		return FALSE ;
	}

	template <class _ARG1>
	imports BOOL template_not_less (const _ARG1 &self_ ,const HINT_WRAPPED &that) {
		if (!operator_less (self_.one () ,that))
			return TRUE ;
		return template_not_less (self_.rest () ,that) ;
	}
} ;

template <class>
class StrongRef ;

template <class>
class WeakRef ;

template <>
class WeakRef<void> {
private:
	struct SELF_PACK {
		AnyRef<void> mHolder ;
		LENGTH mCounter ;
	} ;

private:
	template <class>
	friend class StrongRef ;
	template <class>
	friend class WeakRef ;
	SharedRef<SELF_PACK> mValue ;
} ;

namespace U {
struct OPERATOR_RECAST {
	template <class _ARG1 ,class _ARG2 ,class = ENABLE_TYPE<(stl::is_always_base_of<_ARG2 ,_ARG1>::value)>>
	imports PTR<_ARG2> template_recast (const PTR<_ARG1> &address ,const ARGVF<_ARG2> & ,const DEF<decltype (ARGVP3)> &) {
		return static_cast<PTR<_ARG2>> (address) ;
	}

	template <class _ARG1 ,class _ARG2 ,class = ENABLE_TYPE<(stl::is_always_base_of<Interface ,_ARG1>::value && stl::is_always_base_of<Interface ,_ARG2>::value)>>
	imports PTR<_ARG2> template_recast (const PTR<_ARG1> &address ,const ARGVF<_ARG2> & ,const DEF<decltype (ARGVP2)> &) {
		//@warn: RTTI might be different across DLL
		return dynamic_cast<PTR<_ARG2>> (address) ;
	}

	template <class _ARG1 ,class _ARG2>
	imports PTR<_ARG2> template_recast (const PTR<_ARG1> &address ,const ARGVF<_ARG2> & ,const DEF<decltype (ARGVP1)> &) {
		return NULL ;
	}

	template <class _ARG1 ,class _ARG2>
	imports PTR<_ARG1> invoke (const ARGVF<_ARG1> & ,const PTR<_ARG2> &address) {
		return template_recast (address ,ARGV<CAST_TRAITS_TYPE<_ARG1 ,_ARG2>>::null ,ARGVPX) ;
	}
} ;
} ;

template <class UNIT>
class StrongRef final {
private:
	using SELF_PACK = typename WeakRef<void>::SELF_PACK ;

private:
	template <class>
	friend class StrongRef ;
	template <class>
	friend class WeakRef ;
	SharedRef<SELF_PACK> mValue ;
	PTR<UNIT> mPointer ;

public:
	implicit StrongRef ()
		:StrongRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	//@warn: circular reference ruins StrongRef
	template <class _ARG1 ,class = ENABLE_TYPE<(stl::is_always_base_of<UNIT ,_ARG1>::value)>>
	implicit StrongRef (const StrongRef<_ARG1> &that)
		: StrongRef (that.recast (ARGV<UNIT>::null)) {
		_STATIC_WARNING_ ("noop") ;
	}

	implicit ~StrongRef () noexcept {
		if (mPointer == NULL)
			return ;
		_STATIC_WARNING_ ("mark") ;
		if switch_once (TRUE) {
			const auto r1x = --mValue->mCounter ;
			if (r1x != 0)
				discard ;
			mValue->mHolder = AnyRef<void> () ;
		}
		mPointer = NULL ;
	}

	implicit StrongRef (const StrongRef &that)
		:StrongRef (ARGVP0 ,_COPY_ (that.mValue) ,that.mPointer) {
		_STATIC_WARNING_ ("noop") ;
	}

	inline StrongRef &operator= (const StrongRef &that) {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~StrongRef () ;
			new (this) StrongRef (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	implicit StrongRef (StrongRef &&that) noexcept
		:StrongRef (ARGVP0) {
		mValue = _MOVE_ (that.mValue) ;
		mPointer = _EXCHANGE_ (that.mPointer) ;
	}

	inline StrongRef &operator= (StrongRef &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~StrongRef () ;
			new (this) StrongRef (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	BOOL exist () const {
		if (mPointer == NULL)
			return FALSE ;
		if (!mValue.exist ())
			return FALSE ;
		if (!mValue->mHolder.exist ())
			return FALSE ;
		return TRUE ;
	}

	template <class _ARG1>
	StrongRef<CAST_TRAITS_TYPE<_ARG1 ,UNIT>> recast (const ARGVF<_ARG1> &) const {
		const auto r1x = U::OPERATOR_RECAST::invoke (ARGV<_ARG1>::null ,mPointer) ;
		_DYNAMIC_ASSERT_ (_EBOOL_ (r1x != NULL) == _EBOOL_ (mPointer != NULL)) ;
		return StrongRef<CAST_TRAITS_TYPE<_ARG1 ,UNIT>> (ARGVP0 ,_COPY_ (mValue) ,r1x) ;
	}

	UNIT &to () leftvalue {
		_DEBUG_ASSERT_ (exist ()) ;
		return DEREF[mPointer] ;
	}

	inline implicit operator UNIT & () leftvalue {
		return to () ;
	}

	inline PTR<UNIT> operator-> () leftvalue {
		return DEPTR[to ()] ;
	}

	const UNIT &to () const leftvalue {
		_DEBUG_ASSERT_ (exist ()) ;
		return DEREF[mPointer] ;
	}

	inline implicit operator const UNIT & () const leftvalue {
		return to () ;
	}

	inline PTR<const UNIT> operator-> () const leftvalue {
		return DEPTR[to ()] ;
	}

	BOOL equal (const StrongRef &that) const {
		if (!mValue.exist ())
			if (!that.mValue.exist ())
				return TRUE ;
		if (!mValue.exist ())
			return FALSE ;
		if (!that.mValue.exist ())
			return FALSE ;
		if (DEPTR[mValue.self] != DEPTR[that.mValue.self])
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const StrongRef &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const StrongRef &that) const {
		return !equal (that) ;
	}

	BOOL equal (const WeakRef<UNIT> &that) const {
		struct Dependent ;
		auto &r1x = _XVALUE_ (ARGV<DEPENDENT_TYPE<WeakRef<UNIT> ,Dependent>>::null ,that) ;
		return r1x.equal (DEREF[this]) ;
	}

	inline BOOL operator== (const WeakRef<UNIT> &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const WeakRef<UNIT> &that) const {
		return !equal (that) ;
	}

public:
	template <class... _ARGS>
	imports StrongRef make (_ARGS &&...initval) {
		auto tmp = SharedRef<SELF_PACK>::make () ;
		tmp->mHolder = AnyRef<REMOVE_CVR_TYPE<UNIT>>::make (_FORWARD_ (ARGV<_ARGS>::null ,initval)...) ;
		tmp->mCounter = 0 ;
		auto &r1x = tmp->mHolder.rebind (ARGV<UNIT>::null).self ;
		return StrongRef (ARGVP0 ,_MOVE_ (tmp) ,DEPTR[r1x]) ;
	}

private:
	explicit StrongRef (const DEF<decltype (ARGVP0)> &) noexcept
		:mPointer (NULL) {}

	explicit StrongRef (const DEF<decltype (ARGVP0)> & ,SharedRef<SELF_PACK> &&this_ ,const PTR<UNIT> &pointer) noexcept
		:StrongRef (ARGVP0) {
		if (pointer == NULL)
			return ;
		const auto r1x = ++this_->mCounter ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x > 0) ;
		mValue = _MOVE_ (this_) ;
		mPointer = pointer ;
	}
} ;

template <class UNIT>
class WeakRef {
private:
	using SELF_PACK = typename WeakRef<void>::SELF_PACK ;

private:
	SharedRef<SELF_PACK> mValue ;
	PTR<UNIT> mPointer ;

public:
	implicit WeakRef () {
		mPointer = NULL ;
	}

	BOOL exist () const {
		if (!mValue.exist ())
			return FALSE ;
		if (!mValue->mHolder.exist ())
			return FALSE ;
		if (mPointer == NULL)
			return FALSE ;
		return TRUE ;
	}

	BOOL equal (const WeakRef &that) const {
		if (!mValue.exist ())
			if (!that.mValue.exist ())
				return TRUE ;
		if (!mValue.exist ())
			return FALSE ;
		if (!that.mValue.exist ())
			return FALSE ;
		if (DEPTR[mValue.self] != DEPTR[that.mValue.self])
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const WeakRef &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const WeakRef &that) const {
		return !equal (that) ;
	}

	BOOL equal (const StrongRef<UNIT> &that) const {
		if (!mValue.exist ())
			if (!that.mValue.exist ())
				return TRUE ;
		if (!mValue.exist ())
			return FALSE ;
		if (!that.mValue.exist ())
			return FALSE ;
		if (DEPTR[mValue.self] != DEPTR[that.mValue.self])
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const StrongRef<UNIT> &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const StrongRef<UNIT> &that) const {
		return !equal (that) ;
	}

	StrongRef<UNIT> watch () const {
		return StrongRef<UNIT> (mValue ,mPointer) ;
	}

	void assign (const StrongRef<UNIT> &that) {
		mValue = that.mValue ;
		mPointer = that.mPointer ;
	}
} ;

#ifdef __CSC_DEPRECATED__
template <class UNIT>
class SoftRef final {
public:
	implicit SoftRef () {
		_STATIC_WARNING_ ("unimplemented") ;
		_DYNAMIC_ASSERT_ (FALSE) ;
	}
} ;
#endif

template <class UNIT ,class CONT>
class IntrusiveRef final {
private:
	struct Private {
		class WatchProxy ;

		class LatchCounter ;
	} ;

private:
	stl::atomic<PTR<UNIT>> mPointer ;
	stl::atomic<LENGTH> mLatch ;

public:
	implicit IntrusiveRef ()
		:IntrusiveRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	//@warn: address must be from 'IntrusiveRef::make'
	template <class _ARG1 ,class = ENABLE_TYPE<(stl::is_same<_ARG1 ,PTR<UNIT>>::value)>>
	explicit IntrusiveRef (const _ARG1 &address)
		: IntrusiveRef (ARGVP0) {
		acquire (address ,FALSE) ;
		const auto r1x = safe_exchange (address) ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x == NULL) ;
	}

	implicit ~IntrusiveRef () noexcept {
		const auto r1x = safe_exchange (NULL) ;
		_CALL_TRY_ ([&] () {
			release (r1x) ;
		} ,[&] () {
			_DEBUG_ASSERT_ (FALSE) ;
		}) ;
	}

	implicit IntrusiveRef (const IntrusiveRef &) = delete ;

	inline IntrusiveRef &operator= (const IntrusiveRef &) = delete ;

	implicit IntrusiveRef (IntrusiveRef &&that) noexcept
		:IntrusiveRef (ARGVP0) {
		const auto r1x = that.safe_exchange (NULL) ;
		const auto r2x = safe_exchange (r1x) ;
		_STATIC_UNUSED_ (r2x) ;
		_DEBUG_ASSERT_ (r2x == NULL) ;
	}

	inline IntrusiveRef &operator= (IntrusiveRef &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~IntrusiveRef () ;
			new (this) IntrusiveRef (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	BOOL exist () const {
		const auto r1x = mPointer.load () ;
		if (r1x == NULL)
			return FALSE ;
		return TRUE ;
	}

	IntrusiveRef share () leftvalue {
		struct Dependent ;
		using LatchCounter = typename DEPENDENT_TYPE<Private ,Dependent>::LatchCounter ;
		ScopedGuard<LatchCounter> ANONYMOUS (_CAST_ (ARGV<LatchCounter>::null ,mLatch)) ;
		const auto r1x = mPointer.load () ;
		return IntrusiveRef (r1x) ;
	}

	template <class _RET = REMOVE_CVR_TYPE<typename Private::WatchProxy>>
	_RET watch () side_effects {
		struct Dependent ;
		using WatchProxy = typename DEPENDENT_TYPE<Private ,Dependent>::WatchProxy ;
		using LatchCounter = typename DEPENDENT_TYPE<Private ,Dependent>::LatchCounter ;
		ScopedGuard<LatchCounter> ANONYMOUS (_CAST_ (ARGV<LatchCounter>::null ,mLatch)) ;
		const auto r1x = mPointer.load () ;
		_DYNAMIC_ASSERT_ (r1x != NULL) ;
		auto tmp = IntrusiveRef (r1x) ;
		return WatchProxy (_MOVE_ (tmp) ,PhanRef<UNIT>::make (DEREF[r1x])) ;
	}

public:
	template <class... _ARGS>
	imports IntrusiveRef make (_ARGS &&...initval) {
		IntrusiveRef ret ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<UNIT>>::null) ;
		ScopedBuild<UNIT> ANONYMOUS (rax ,_FORWARD_ (ARGV<_ARGS>::null ,initval)...) ;
		auto &r1x = _LOAD_ (ARGV<UNIT>::null ,rax.self) ;
		acquire (DEPTR[r1x] ,TRUE) ;
		const auto r2x = ret.safe_exchange (DEPTR[r1x]) ;
		_STATIC_UNUSED_ (r2x) ;
		_DEBUG_ASSERT_ (r2x == NULL) ;
		rax = NULL ;
		return _MOVE_ (ret) ;
	}

private:
	explicit IntrusiveRef (const DEF<decltype (ARGVP0)> &) noexcept
		:mPointer (NULL) ,mLatch (0) {}

private:
	PTR<UNIT> safe_exchange (const PTR<UNIT> &address) side_effects {
		const auto r1x = mPointer.exchange (address) ;
		if (r1x == NULL)
			return r1x ;
		INDEX iw = 0 ;
		while (TRUE) {
			const auto r2x = iw++ ;
			_STATIC_UNUSED_ (r2x) ;
			_DEBUG_ASSERT_ (r2x <= DEFAULT_RECURSIVE_SIZE::value) ;
			const auto r3x = mLatch.load () ;
			if (r3x == 0)
				break ;
			CONT::friend_latch (DEREF[r1x]) ;
		}
		return r1x ;
	}

private:
	imports void acquire (const PTR<UNIT> &address ,const BOOL &init) {
		if (address == NULL)
			return ;
		if (init)
			CONT::friend_create (DEREF[address]) ;
		const auto r1x = CONT::friend_attach (DEREF[address]) ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x >= 1 + _EBOOL_ (!init)) ;
	}

	imports void release (const PTR<UNIT> &address) {
		if (address == NULL)
			return ;
		const auto r1x = CONT::friend_detach (DEREF[address]) ;
		_DEBUG_ASSERT_ (r1x >= 0) ;
		if (r1x > 0)
			return ;
		CONT::friend_destroy (DEREF[address]) ;
		address->~UNIT () ;
		GlobalHeap::free (address) ;
	}
} ;

template <class UNIT ,class CONT>
class IntrusiveRef<UNIT ,CONT>::Private::WatchProxy
	:private Proxy {
private:
	UniqueRef<IntrusiveRef> mBase ;
	PhanRef<UNIT> mRef ;

public:
	implicit WatchProxy () = delete ;

	explicit WatchProxy (IntrusiveRef &&base ,PhanRef<UNIT> &&ref_) {
		mBase = UniqueRef<IntrusiveRef> ([&] (IntrusiveRef &me) {
			me = _MOVE_ (base) ;
		} ,[] (IntrusiveRef &me) {
			_STATIC_WARNING_ ("noop") ;
		}) ;
		mRef = _MOVE_ (ref_) ;
	}

	UNIT &to () const leftvalue {
		_DEBUG_ASSERT_ (mBase.exist ()) ;
		return mRef.self ;
	}

	inline implicit operator UNIT & () const leftvalue {
		return to () ;
	}
} ;

template <class UNIT ,class CONT>
class IntrusiveRef<UNIT ,CONT>::Private::LatchCounter
	:private Wrapped<stl::atomic<LENGTH>> {
public:
	void lock () {
		const auto r1x = ++LatchCounter::mSelf ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x >= 1) ;
	}

	void unlock () {
		const auto r1x = --LatchCounter::mSelf ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x >= 0) ;
	}
} ;

class MemoryPool {
private:
	struct HEADER ;

	class Holder
		:public Interface {
	public:
		virtual void clear () noexcept = 0 ;
		virtual LENGTH size () const = 0 ;
		virtual LENGTH length () const = 0 ;
		virtual PTR<HEADER> alloc (const LENGTH &len) side_effects = 0 ;
		virtual void free (const PTR<HEADER> &address) noexcept = 0 ;
		virtual void clean () noexcept = 0 ;
	} ;

	struct HEADER {
		alignas (8) PTR<Holder> mFrom ;
		alignas (8) PTR<struct HEADER> mCurr ;
	} ;

	struct SELF_PACK {
		AutoBuffer<StrongRef<Holder>> mPool ;
	} ;

	struct Private {
		template <class ,class>
		class ImplHolder ;

		class HugeHolder ;
	} ;

private:
	UniqueRef<SharedRef<SELF_PACK>> mThis ;

public:
	implicit MemoryPool () ;

	LENGTH size () const {
		LENGTH ret = 0 ;
		for (auto &&i : _RANGE_ (0 ,mThis.self->mPool.size ()))
			ret += mThis.self->mPool[i]->size () ;
		return _MOVE_ (ret) ;
	}

	LENGTH length () const {
		LENGTH ret = 0 ;
		for (auto &&i : _RANGE_ (0 ,mThis.self->mPool.size ()))
			ret += mThis.self->mPool[i]->length () ;
		return _MOVE_ (ret) ;
	}

	//@warn: held by RAII to avoid static-memory-leaks
	template <class _ARG1>
	PTR<_ARG1> alloc (const ARGVF<_ARG1> &) side_effects {
		_STATIC_ASSERT_ (stl::is_pod<_ARG1>::value) ;
		const auto r1x = _ALIGNOF_ (_ARG1) - _ALIGNOF_ (HEADER) ;
		const auto r2x = VAR_ZERO ;
		const auto r3x = _MAX_ (r1x ,r2x) + _SIZEOF_ (_ARG1) ;
		const auto r4x = (r3x - 1) / 8 ;
		const auto r5x = _SIZEOF_ (HEADER) ;
		INDEX ix = _MIN_ (r4x ,r5x) ;
		const auto r6x = mThis.self->mPool[ix]->alloc (r3x) ;
		const auto r7x = _ALIGNAS_ (_ADDRESS_ (r6x) + r5x ,_ALIGNOF_ (_ARG1)) ;
		const auto r8x = r7x - r5x ;
		auto &r9x = _LOAD_UNSAFE_ (ARGV<HEADER>::null ,r8x) ;
		r9x.mFrom = DEPTR[mThis.self->mPool[ix].self] ;
		r9x.mCurr = r6x ;
		auto &r10x = _LOAD_UNSAFE_ (ARGV<_ARG1>::null ,r7x) ;
		return DEPTR[r10x] ;
	}

	//@warn: held by RAII to avoid static-memory-leaks
	template <class _ARG1>
	PTR<ARR<_ARG1>> alloc (const ARGVF<_ARG1> & ,const LENGTH &len) side_effects {
		_STATIC_ASSERT_ (stl::is_pod<_ARG1>::value) ;
		const auto r1x = _ALIGNOF_ (_ARG1) - _ALIGNOF_ (HEADER) ;
		const auto r2x = VAR_ZERO ;
		const auto r3x = _MAX_ (r1x ,r2x) + len * _SIZEOF_ (_ARG1) ;
		_DEBUG_ASSERT_ (r3x > 0) ;
		const auto r4x = (r3x - 1) / 8 ;
		const auto r5x = _SIZEOF_ (HEADER) ;
		INDEX ix = _MIN_ (r4x ,r5x) ;
		const auto r6x = mThis.self->mPool[ix]->alloc (r3x) ;
		const auto r7x = _ALIGNAS_ (_ADDRESS_ (r6x) + r5x ,_ALIGNOF_ (_ARG1)) ;
		const auto r8x = r7x - r5x ;
		auto &r9x = _LOAD_UNSAFE_ (ARGV<HEADER>::null ,r8x) ;
		r9x.mFrom = DEPTR[mThis.self->mPool[ix].self] ;
		r9x.mCurr = r6x ;
		auto &r10x = _LOAD_UNSAFE_ (ARGV<ARR<_ARG1>>::null ,r7x) ;
		return DEPTR[r10x] ;
	}

	template <class _ARG1>
	void free (const PTR<_ARG1> &address) noexcept {
		_STATIC_ASSERT_ (stl::is_pod<REMOVE_ARRAY_TYPE<_ARG1>>::value) ;
		const auto r1x = _ADDRESS_ (address) - _SIZEOF_ (HEADER) ;
		auto &r2x = _LOAD_UNSAFE_ (ARGV<HEADER>::null ,r1x) ;
		INDEX ix = BasicProc::mem_chr (mThis.self->mPool.self ,mThis.self->mPool.size () ,r2x.mFrom) ;
		mThis.self->mPool[ix]->free (r2x.mCurr) ;
	}

	void clean () {
		for (auto &&i : _RANGE_ (0 ,mThis.self->mPool.size ()))
			mThis.self->mPool[i]->clean () ;
	}
} ;

template <class SIZE ,class RESE>
class MemoryPool::Private::ImplHolder
	:public Holder {
	_STATIC_ASSERT_ (SIZE::value > 0) ;
	_STATIC_ASSERT_ (RESE::value > 0) ;

private:
	struct BLOCK_NODE {
		PTR<struct BLOCK_NODE> mNext ;
		HEADER mFlexData ;
	} ;

	struct CHUNK_NODE {
		PTR<ARR<BYTE>> mOrigin ;
		PTR<struct CHUNK_NODE> mPrev ;
		PTR<struct CHUNK_NODE> mNext ;
		LENGTH mCount ;
	} ;

private:
	PTR<CHUNK_NODE> mRoot ;
	PTR<BLOCK_NODE> mFree ;
	LENGTH mSize ;
	LENGTH mLength ;

public:
	implicit ImplHolder () {
		mRoot = NULL ;
		mFree = NULL ;
		mSize = 0 ;
		mLength = 0 ;
	}

	void clear () noexcept override {
		if (mRoot == NULL)
			return ;
		while (TRUE) {
			if (mRoot == NULL)
				break ;
			const auto r1x = mRoot->mNext ;
			GlobalHeap::free (mRoot->mOrigin) ;
			mRoot = r1x ;
		}
		mFree = NULL ;
		mSize = 0 ;
		mLength = 0 ;
	}

	LENGTH size () const override {
		return mSize ;
	}

	LENGTH length () const override {
		return mLength ;
	}

	void reserve () {
		if (mFree != NULL)
			return ;
		const auto r1x = _ALIGNAS_ (_SIZEOF_ (BLOCK_NODE) + SIZE::value ,_ALIGNOF_ (BLOCK_NODE)) ;
		const auto r2x = _ALIGNOF_ (CHUNK_NODE) - 1 + _SIZEOF_ (CHUNK_NODE) + _ALIGNOF_ (BLOCK_NODE) - 1 + RESE::value * r1x ;
		auto rax = GlobalHeap::alloc (ARGV<BYTE>::null ,r2x) ;
		const auto r3x = _ADDRESS_ (rax.self) ;
		const auto r4x = _ALIGNAS_ (r3x ,_ALIGNOF_ (CHUNK_NODE)) ;
		auto &r5x = _LOAD_UNSAFE_ (ARGV<CHUNK_NODE>::null ,r4x) ;
		r5x.mOrigin = rax ;
		r5x.mPrev = NULL ;
		r5x.mNext = mRoot ;
		r5x.mCount = RESE::value ;
		if (mRoot != NULL)
			mRoot->mPrev = DEPTR[r5x] ;
		mRoot = DEPTR[r5x] ;
		mSize += RESE::value * SIZE::value ;
		const auto r6x = _ALIGNAS_ (r4x + _SIZEOF_ (CHUNK_NODE) ,_ALIGNOF_ (BLOCK_NODE)) ;
		for (auto &&i : _RANGE_ (0 ,mRoot->mCount)) {
			const auto r7x = r6x + i * r1x ;
			auto &r8x = _LOAD_UNSAFE_ (ARGV<BLOCK_NODE>::null ,r7x) ;
			r8x.mNext = mFree ;
			mFree = DEPTR[r8x] ;
		}
		rax = NULL ;
	}

	PTR<HEADER> alloc (const LENGTH &len) side_effects override {
		_DEBUG_ASSERT_ (len <= SIZE::value) ;
		reserve () ;
		const auto r1x = mFree ;
		mFree = r1x->mNext ;
		mLength += SIZE::value ;
		const auto r2x = VAR_USED ;
		r1x->mNext = _BITWISE_CAST_ (ARGV<PTR<BLOCK_NODE>>::null ,r2x) ;
		return DEPTR[r1x->mFlexData] ;
	}

	void free (const PTR<HEADER> &address) noexcept override {
		_DEBUG_ASSERT_ (address != NULL) ;
		auto &r1x = _OFFSET_ (&BLOCK_NODE::mFlexData ,DEREF[address]) ;
		_DEBUG_ASSERT_ (_ADDRESS_ (r1x.mNext) == VAR_USED) ;
		r1x.mNext = mFree ;
		mFree = DEPTR[r1x] ;
		mLength -= SIZE::value ;
	}

	void clean () noexcept override {
		if (mSize == mLength)
			return ;
		auto rax = mRoot ;
		while (TRUE) {
			if (rax == NULL)
				break ;
			const auto r1x = rax->mNext ;
			if switch_once (TRUE) {
				if (!empty_node (rax))
					discard ;
				auto &r2x = _SWITCH_ (
					(rax->mPrev != NULL) ? rax->mPrev->mNext :
					mRoot) ;
				r2x = rax->mNext ;
				if (rax->mNext != NULL)
					rax->mNext->mPrev = rax->mPrev ;
				mSize -= rax->mCount * SIZE::value ;
				GlobalHeap::free (rax->mOrigin) ;
			}
			rax = r1x ;
		}
	}

private:
	BOOL empty_node (const PTR<const CHUNK_NODE> &node) const {
		const auto r1x = _ALIGNAS_ (_SIZEOF_ (BLOCK_NODE) + SIZE::value ,_ALIGNOF_ (BLOCK_NODE)) ;
		const auto r2x = _ALIGNAS_ (_ADDRESS_ (node) + _SIZEOF_ (CHUNK_NODE) ,_ALIGNOF_ (BLOCK_NODE)) ;
		for (auto &&i : _RANGE_ (0 ,node->mCount)) {
			const auto r3x = r2x + i * r1x ;
			auto &r4x = _LOAD_UNSAFE_ (ARGV<BLOCK_NODE>::null ,r3x) ;
			if (_ADDRESS_ (r4x.mNext) == VAR_USED)
				return FALSE ;
		}
		return TRUE ;
	}
} ;

class MemoryPool::Private::HugeHolder
	:public Holder {
private:
	struct FBLOCK_NODE {
		PTR<ARR<BYTE>> mOrigin ;
		PTR<struct FBLOCK_NODE> mPrev ;
		PTR<struct FBLOCK_NODE> mNext ;
		LENGTH mCount ;
		HEADER mFlexData ;
	} ;

private:
	PTR<FBLOCK_NODE> mRoot ;
	LENGTH mSize ;
	LENGTH mLength ;

public:
	implicit HugeHolder () {
		mRoot = NULL ;
		mSize = 0 ;
		mLength = 0 ;
	}

	void clear () noexcept override {
		if (mRoot == NULL)
			return ;
		while (TRUE) {
			if (mRoot == NULL)
				break ;
			const auto r1x = mRoot->mNext ;
			GlobalHeap::free (mRoot->mOrigin) ;
			mRoot = r1x ;
		}
		mSize = 0 ;
		mLength = 0 ;
	}

	LENGTH size () const override {
		return mSize ;
	}

	LENGTH length () const override {
		return mLength ;
	}

	PTR<HEADER> alloc (const LENGTH &len) side_effects override {
		const auto r1x = _ALIGNAS_ (len ,_ALIGNOF_ (FBLOCK_NODE)) ;
		const auto r2x = _ALIGNOF_ (FBLOCK_NODE) - 1 + _SIZEOF_ (FBLOCK_NODE) + r1x ;
		auto rax = GlobalHeap::alloc (ARGV<BYTE>::null ,r2x) ;
		const auto r3x = _ADDRESS_ (rax.self) ;
		const auto r4x = _ALIGNAS_ (r3x ,_ALIGNOF_ (FBLOCK_NODE)) ;
		auto &r5x = _LOAD_UNSAFE_ (ARGV<FBLOCK_NODE>::null ,r4x) ;
		r5x.mOrigin = rax ;
		r5x.mPrev = NULL ;
		r5x.mNext = mRoot ;
		r5x.mCount = r1x ;
		if (mRoot != NULL)
			mRoot->mPrev = DEPTR[r5x] ;
		mRoot = DEPTR[r5x] ;
		mSize += r5x.mCount ;
		mLength += r5x.mCount ;
		rax = NULL ;
		return DEPTR[r5x.mFlexData] ;
	}

	void free (const PTR<HEADER> &address) noexcept override {
		_DEBUG_ASSERT_ (address != NULL) ;
		auto &r1x = _OFFSET_ (&FBLOCK_NODE::mFlexData ,DEREF[address]) ;
		auto &r2x = _SWITCH_ (
			(r1x.mPrev != NULL) ? r1x.mPrev->mNext :
			mRoot) ;
		r2x = r1x.mNext ;
		if (r1x.mNext != NULL)
			r1x.mNext->mPrev = r1x.mPrev ;
		mSize -= r1x.mCount ;
		mLength -= r1x.mCount ;
		GlobalHeap::free (r1x.mOrigin) ;
	}

	void clean () noexcept override {
		_STATIC_WARNING_ ("noop") ;
	}
} ;

inline exports MemoryPool::MemoryPool () {
	struct Dependent ;
	using ImplHolderX8 = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<ARGC<8> ,ARGC<32>> ;
	using ImplHolderX16 = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<ARGC<16> ,ARGC<32>> ;
	using ImplHolderX24 = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<ARGC<24> ,ARGC<32>> ;
	using ImplHolderX32 = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<ARGC<32> ,ARGC<32>> ;
	using ImplHolderX40 = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<ARGC<40> ,ARGC<16>> ;
	using ImplHolderX48 = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<ARGC<48> ,ARGC<16>> ;
	using ImplHolderX56 = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<ARGC<56> ,ARGC<16>> ;
	using ImplHolderX64 = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<ARGC<64> ,ARGC<16>> ;
	using ImplHolderX72 = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<ARGC<72> ,ARGC<8>> ;
	using ImplHolderX80 = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<ARGC<80> ,ARGC<8>> ;
	using ImplHolderX88 = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<ARGC<88> ,ARGC<8>> ;
	using ImplHolderX96 = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<ARGC<96> ,ARGC<8>> ;
	using ImplHolderX104 = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<ARGC<104> ,ARGC<4>> ;
	using ImplHolderX112 = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<ARGC<112> ,ARGC<4>> ;
	using ImplHolderX120 = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<ARGC<120> ,ARGC<4>> ;
	using ImplHolderX128 = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<ARGC<128> ,ARGC<4>> ;
	using HugeHolder = typename DEPENDENT_TYPE<Private ,Dependent>::HugeHolder ;
	mThis = UniqueRef<SharedRef<SELF_PACK>> ([&] (SharedRef<SELF_PACK> &me) {
		me = SharedRef<SELF_PACK>::make () ;
	} ,[] (SharedRef<SELF_PACK> &me) {
		for (auto &&i : _RANGE_ (0 ,me->mPool.size ()))
			me->mPool[i]->clear () ;
		me->mPool = AutoBuffer<StrongRef<Holder>> () ;
	}) ;
	mThis.self->mPool = AutoBuffer<StrongRef<Holder>> (17) ;
	mThis.self->mPool[0] = StrongRef<ImplHolderX8>::make () ;
	mThis.self->mPool[1] = StrongRef<ImplHolderX16>::make () ;
	mThis.self->mPool[2] = StrongRef<ImplHolderX24>::make () ;
	mThis.self->mPool[3] = StrongRef<ImplHolderX32>::make () ;
	mThis.self->mPool[4] = StrongRef<ImplHolderX40>::make () ;
	mThis.self->mPool[5] = StrongRef<ImplHolderX48>::make () ;
	mThis.self->mPool[6] = StrongRef<ImplHolderX56>::make () ;
	mThis.self->mPool[7] = StrongRef<ImplHolderX64>::make () ;
	mThis.self->mPool[8] = StrongRef<ImplHolderX72>::make () ;
	mThis.self->mPool[9] = StrongRef<ImplHolderX80>::make () ;
	mThis.self->mPool[10] = StrongRef<ImplHolderX88>::make () ;
	mThis.self->mPool[11] = StrongRef<ImplHolderX96>::make () ;
	mThis.self->mPool[12] = StrongRef<ImplHolderX104>::make () ;
	mThis.self->mPool[13] = StrongRef<ImplHolderX112>::make () ;
	mThis.self->mPool[14] = StrongRef<ImplHolderX120>::make () ;
	mThis.self->mPool[15] = StrongRef<ImplHolderX128>::make () ;
	mThis.self->mPool[16] = StrongRef<HugeHolder>::make () ;
}

class Object ;

template <class>
class VirtualObject ;

class Objective
	:public Interface {
public:
	virtual WeakRef<Object> weak_of_this () const = 0 ;
	virtual void weak_of_this (const StrongRef<Object> &that) = 0 ;
	virtual StrongRef<Object> clone () const = 0 ;
} ;

class Object
	:public Objective {
private:
	struct Private {
		class Metadata ;
	} ;

private:
	WeakRef<Object> mWeakOfThis ;

public:
	implicit Object () = default ;

	WeakRef<Object> weak_of_this () const override {
		return mWeakOfThis ;
	}

	void weak_of_this (const StrongRef<Object> &that) override {
		mWeakOfThis.assign (that) ;
	}

	StrongRef<Object> clone () const override {
		return StrongRef<Object> () ;
	}
} ;

class Object::Private::Metadata {
private:
	LENGTH mObjectSize ;
	LENGTH mObjectAlign ;
	FLAG mObjectTypeMID ;
	Function<void (PTR<NONE>)> mConstrutor ;
	Function<void (PTR<NONE>)> mDestructor ;

public:
	implicit Metadata () = delete ;

	template <class _ARG1>
	explicit Metadata (const ARGVF<_ARG1> &) {
		_STATIC_ASSERT_ (stl::is_same<REMOVE_CVR_TYPE<_ARG1> ,_ARG1>::value) ;
		mObjectSize = _SIZEOF_ (_ARG1) ;
		mObjectAlign = _ALIGNOF_ (_ARG1) ;
		mObjectTypeMID = _TYPEMID_ (ARGV<_ARG1>::null) ;
		mConstrutor = Function<void (PTR<NONE>)> ([] (const PTR<NONE> &address) {
			auto &r1x = _LOAD_ (ARGV<TEMP<_ARG1>>::null ,address) ;
			_CREATE_ (DEPTR[r1x]) ;
		}) ;
		mDestructor = Function<void (PTR<NONE>)> ([] (const PTR<NONE> &address) {
			auto &r1x = _LOAD_ (ARGV<TEMP<_ARG1>>::null ,address) ;
			_DESTROY_ (DEPTR[r1x]) ;
		}) ;
	}
} ;

template <class UNIT>
class VirtualObject
	:public virtual Object {
public:
	implicit VirtualObject () {
		_STATIC_WARNING_ ("noop") ;
	}
} ;

template <class UNIT ,class CONT>
class Serializer {
private:
	class Holder
		:public Interface {
	public:
		virtual void compute_visit (UNIT &visitor ,CONT &context_) const = 0 ;
	} ;

	struct Private {
		class Member ;

		template <class...>
		class ImplHolder ;
	} ;

private:
	StrongRef<Holder> mHolder ;

public:
	implicit Serializer () = delete ;

	template <class... _ARGS>
	explicit Serializer (const ARGVF<ARGVS<_ARGS...>> &) {
		struct Dependent ;
		using ImplHolder = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<_ARGS...> ;
		_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<_ARGS...>) > 0) ;
		mHolder = StrongRef<ImplHolder>::make (ARGV<ARGVS<_ARGS...>>::null) ;
	}

	template <class _RET = REMOVE_CVR_TYPE<typename Private::Member>>
	inline _RET operator() (PhanRef<CONT> &&context_) const side_effects {
		struct Dependent ;
		using Member = typename DEPENDENT_TYPE<Private ,Dependent>::Member ;
		_DEBUG_ASSERT_ (mHolder.exist ()) ;
		return Member (PhanRef<const Serializer>::make (DEREF[this]) ,_MOVE_ (context_)) ;
	}
} ;

template <class UNIT ,class CONT>
class Serializer<UNIT ,CONT>::Private::Member
	:private Proxy {
private:
	PhanRef<const Serializer> mBase ;
	PhanRef<CONT> mContext ;

public:
	implicit Member () = delete ;

	explicit Member (PhanRef<const Serializer> &&base ,PhanRef<CONT> &&context_) {
		mBase = _MOVE_ (base) ;
		mContext = _MOVE_ (context_) ;
	}

	void friend_visit (UNIT &visitor) {
		mBase->mHolder->compute_visit (visitor ,mContext) ;
	}
} ;

template <class UNIT ,class CONT>
template <class... UNITS_>
class Serializer<UNIT ,CONT>::Private::ImplHolder
	:public Holder {
public:
	implicit ImplHolder () = delete ;

	explicit ImplHolder (const ARGVF<ARGVS<UNITS_...>> &) {
		_STATIC_WARNING_ ("noop") ;
	}

	void compute_visit (UNIT &visitor ,CONT &context_) const override {
		template_visit (visitor ,context_ ,ARGV<ARGVS<UNITS_...>>::null) ;
	}

private:
	void template_visit (UNIT &visitor ,CONT &context_ ,const ARGVF<ARGVS<>> &) const {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1>
	void template_visit (UNIT &visitor ,CONT &context_ ,const ARGVF<_ARG1> &) const {
		using HINT_T1 = ARGVS_ONE_TYPE<_ARG1> ;
		using HINT_T2 = ARGVS_REST_TYPE<_ARG1> ;
		auto &r1x = HINT_T1::compile (context_) ;
		visitor.visit (r1x) ;
		template_visit (visitor ,context_ ,ARGV<HINT_T2>::null) ;
	}
} ;
} ;