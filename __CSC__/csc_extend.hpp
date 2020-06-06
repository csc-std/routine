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
		imports DEF<void (const Exception &)> done ;
	} ;

private:
	struct Private {
		template <class>
		class WatchInterface ;
	} ;

public:
	static void done (const Exception &e) {
		Public::done (e) ;
	}

	template <class _ARG1 ,class _ARG2>
	static void done (const ARGV<_ARG1> & ,const Plain<STR> &name ,_ARG2 &data) {
		struct Dependent ;
		using WatchInterface = DEPENDENT_TYPE<DEF<typename Private::template WatchInterface<_ARG2>> ,Dependent> ;
		static volatile WatchInterface mInstance ;
		mInstance.mName = name.self ;
		mInstance.mAddress = DEPTR[data] ;
		mInstance.mTypeMID = _TYPEMID_<_ARG2> () ;
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
	PTR<void (UNIT &)> mWatch ;

public:
	WatchInterface () {
		mName = NULL ;
		mAddress = NULL ;
		mTypeMID = 0 ;
		const auto r1x = _FORWARD_<PTR<void (UNIT &)>> ([] (UNIT &) {}) ;
		mWatch = r1x ;
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
			:mValue (_FORWARD_<_ARGS> (initval)...) {}
	} ;

private:
	friend GlobalStatic<Singleton> ;
	AutoRef<Holder> mHolder ;

private:
	Singleton () {
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
	static UNIT &instance () {
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
	VAR128 () = default ;

	implicit VAR128 (const VAR64 &that) {
		const auto r1x = _EBOOL_ (that < 0) * DATA (-1) ;
		v2i1 = DATA (that) ;
		v2i0 = r1x ;
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
		const auto r1x = _CAST_<VAR64> (v2i0) ;
		const auto r2x = _CAST_<VAR64> (that.v2i0) ;
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
		const auto r1x = _CAST_<VAR64> (v2i0) ;
		const auto r2x = _CAST_<VAR64> (that.v2i0) ;
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
		const auto r1x = _CAST_<VAR64> (v2i0) ;
		const auto r2x = _CAST_<VAR64> (that.v2i0) ;
		const auto r3x = U::OPERATOR_COMPR::invoke (r1x ,r2x) ;
		if (r3x != 0)
			return r3x ;
		return U::OPERATOR_COMPR::invoke (v2i1 ,that.v2i1) ;
	}

	DATA &m_v2i0 () leftvalue {
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = WORD (0X0001) ;
		return _CAST_<DATA[2]> (mValue)[_CAST_<BYTE[2]> (r1x)[0]] ;
	}

	const DATA &m_v2i0 () const leftvalue {
		const auto r1x = WORD (0X0001) ;
		return _CAST_<DATA[2]> (mValue)[_CAST_<BYTE[2]> (r1x)[0]] ;
	}

	DATA &m_v2i1 () leftvalue {
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = WORD (0X0001) ;
		return _CAST_<DATA[2]> (mValue)[_CAST_<BYTE[2]> (r1x)[1]] ;
	}

	const DATA &m_v2i1 () const leftvalue {
		const auto r1x = WORD (0X0001) ;
		return _CAST_<DATA[2]> (mValue)[_CAST_<BYTE[2]> (r1x)[1]] ;
	}

	CHAR &m_v4i0 () leftvalue {
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_<CHAR[4]> (mValue)[_CAST_<BYTE[4]> (r1x)[0]] ;
	}

	const CHAR &m_v4i0 () const leftvalue {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_<CHAR[4]> (mValue)[_CAST_<BYTE[4]> (r1x)[0]] ;
	}

	CHAR &m_v4i1 () leftvalue {
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_<CHAR[4]> (mValue)[_CAST_<BYTE[4]> (r1x)[1]] ;
	}

	const CHAR &m_v4i1 () const leftvalue {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_<CHAR[4]> (mValue)[_CAST_<BYTE[4]> (r1x)[1]] ;
	}

	CHAR &m_v4i2 () leftvalue {
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_<CHAR[4]> (mValue)[_CAST_<BYTE[4]> (r1x)[2]] ;
	}

	const CHAR &m_v4i2 () const leftvalue {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_<CHAR[4]> (mValue)[_CAST_<BYTE[4]> (r1x)[2]] ;
	}

	CHAR &m_v4i3 () leftvalue {
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_<CHAR[4]> (mValue)[_CAST_<BYTE[4]> (r1x)[3]] ;
	}

	const CHAR &m_v4i3 () const leftvalue {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_<CHAR[4]> (mValue)[_CAST_<BYTE[4]> (r1x)[3]] ;
	}

private:
	static VAR128 slow_divide (const VAR128 &y ,const VAR128 &x) {
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

template <class UNIT>
class Mutable {
private:
	static constexpr auto STATE_CACHED = EFLAG (1) ;
	static constexpr auto STATE_SIGNALED = EFLAG (2) ;
	static constexpr auto STATE_FINISHED = EFLAG (3) ;

private:
	mutable UNIT mValue ;
	mutable EFLAG mState ;

public:
	Mutable () {
		mState = STATE_SIGNALED ;
	}

	implicit Mutable (const REMOVE_CVR_TYPE<UNIT> &that)
		:Mutable (ARGVP0 ,_MOVE_ (that)) {
		_STATIC_WARNING_ ("noop") ;
	}

	implicit Mutable (REMOVE_CVR_TYPE<UNIT> &&that)
		: Mutable (ARGVP0 ,_MOVE_ (that)) {
		_STATIC_WARNING_ ("noop") ;
	}

	const UNIT &to () const leftvalue {
		return mValue ;
	}

	inline implicit operator const UNIT & () const leftvalue {
		return to () ;
	}

	template <class _ARG1>
	void apply (const Function<void (_ARG1 &)> &proc) const {
		_STATIC_ASSERT_ (stl::is_same<REMOVE_CVR_TYPE<_ARG1> ,UNIT>::value) ;
		if (mState != STATE_SIGNALED)
			return ;
		proc (mValue) ;
		mState = STATE_CACHED ;
	}

	template <class _ARG1>
	void apply (const Function<U::MEMBER_FUNCTION_HINT<void ,_ARG1 &>> &proc) const {
		_STATIC_ASSERT_ (stl::is_same<REMOVE_CVR_TYPE<_ARG1> ,UNIT>::value) ;
		if (mState != STATE_SIGNALED)
			return ;
		proc (mValue) ;
		mState = STATE_CACHED ;
	}

	void signal () const {
		if (mState != STATE_CACHED)
			return ;
		mState = STATE_SIGNALED ;
	}

	void finish () const {
		mState = STATE_FINISHED ;
	}

private:
	template <class... _ARGS>
	explicit Mutable (const DEF<decltype (ARGVP0)> & ,_ARGS &&...initval)
		:mValue (_FORWARD_<_ARGS> (initval)...) ,mState (STATE_CACHED) {}
} ;

namespace U {
inline constexpr LENGTH constexpr_max_sizeof (const ARGV<ARGVS<>> &) {
	return 1 ;
}

template <class _ARG1>
inline constexpr LENGTH constexpr_max_sizeof (const ARGV<_ARG1> &) {
	using ONE_HINT = ARGVS_ONE_TYPE<_ARG1> ;
	using REST_HINT = ARGVS_REST_TYPE<_ARG1> ;
	return _MAX_<const LENGTH> (_SIZEOF_ (ONE_HINT) ,constexpr_max_sizeof (_NULL_<ARGV<REST_HINT>> ())) ;
}

inline constexpr LENGTH constexpr_max_alignof (const ARGV<ARGVS<>> &) {
	return 1 ;
}

template <class _ARG1>
inline constexpr LENGTH constexpr_max_alignof (const ARGV<_ARG1> &) {
	using ONE_HINT = ARGVS_ONE_TYPE<_ARG1> ;
	using REST_HINT = ARGVS_REST_TYPE<_ARG1> ;
	return _MAX_<const LENGTH> (_ALIGNOF_ (ONE_HINT) ,constexpr_max_alignof (_NULL_<ARGV<REST_HINT>> ())) ;
}
} ;

template <class... UNITS>
class Variant final {
	_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS...>) > 0) ;
	_STATIC_ASSERT_ (!stl::is_any_same<REMOVE_CVR_TYPE<UNITS>...>::value) ;

private:
	static constexpr auto VARIANT_ALIGN = U::constexpr_max_alignof (_NULL_<ARGV<ARGVS<UNITS...>>> ()) ;
	static constexpr auto VARIANT_SIZE = U::constexpr_max_sizeof (_NULL_<ARGV<ARGVS<UNITS...>>> ()) ;

	//@error: fuck g++4.8
	template <LENGTH ALIGN = VARIANT_ALIGN>
	struct ALIGNED_UNION {
		alignas (ALIGN) DEF<BYTE[VARIANT_SIZE]> unused ;
	} ;

	using VARIANT = ALIGNED_UNION<> ;

	using OPTIONAL = INDEX_TO_TYPE<ZERO ,ARGVS<UNITS...>> ;

private:
	TEMP<VARIANT> mVariant ;
	INDEX mIndex ;

public:
	Variant ()
		:Variant (ARGVP0) {
		const auto r1x = default_constructible_index (_NULL_<ARGV<ZERO>> () ,_NULL_<ARGV<ARGVS<UNITS...>>> ()) ;
		template_construct (r1x ,_NULL_<ARGV<ARGVS<UNITS...>>> ()) ;
		mIndex = r1x ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<!stl::is_same<REMOVE_CVR_TYPE<_ARG1> ,Variant>::value>>
	implicit Variant (_ARG1 &&that)
		:Variant (ARGVP0) {
		_STATIC_ASSERT_ (INDEX_OF_TYPE<REMOVE_CVR_TYPE<_ARG1> ,ARGVS<UNITS...>>::value != VAR_NONE) ;
		_STATIC_ASSERT_ (!stl::is_same<REMOVE_CVR_TYPE<_ARG1> ,DEF<decltype (ARGVP0)>>::value) ;
		auto &r1x = _NULL_<ARGV<ARGC<stl::is_constructible<REMOVE_CVR_TYPE<_ARG1> ,_ARG1 &&>::value>>> () ;
		auto &r2x = _LOAD_<TEMP<REMOVE_CVR_TYPE<_ARG1>>> (DEPTR[mVariant]) ;
		template_create (r1x ,DEPTR[r2x] ,_FORWARD_<_ARG1> (that)) ;
		mIndex = INDEX_OF_TYPE<REMOVE_CVR_TYPE<_ARG1> ,ARGVS<UNITS...>>::value ;
	}

	inline ~Variant () noexcept {
		if (mIndex == VAR_NONE)
			return ;
		template_destruct (mIndex ,_NULL_<ARGV<ARGVS<UNITS...>>> ()) ;
		mIndex = VAR_NONE ;
	}

	inline Variant (const Variant &that)
		:Variant (ARGVP0) {
		if (that.mIndex == VAR_NONE)
			return ;
		template_copy_construct (that ,that.mIndex ,_NULL_<ARGV<ARGVS<UNITS...>>> ()) ;
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

	inline Variant (Variant &&that) noexcept
		:Variant (ARGVP0) {
		if (that.mIndex == VAR_NONE)
			return ;
		template_move_construct (that ,that.mIndex ,_NULL_<ARGV<ARGVS<UNITS...>>> ()) ;
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

	template <class _RET>
	BOOL available () const {
		_STATIC_ASSERT_ (!stl::is_reference<_RET>::value) ;
		_STATIC_ASSERT_ (INDEX_OF_TYPE<REMOVE_CVR_TYPE<_RET> ,ARGVS<UNITS...>>::value != VAR_NONE) ;
		if (mIndex != INDEX_OF_TYPE<REMOVE_CVR_TYPE<_RET> ,ARGVS<UNITS...>>::value)
			return FALSE ;
		return TRUE ;
	}

	OPTIONAL &to () leftvalue {
		_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS...>) == 1) ;
		_DYNAMIC_ASSERT_ (exist ()) ;
		auto &r1x = _LOAD_<TEMP<OPTIONAL>> (DEPTR[mVariant]) ;
		return _CAST_<OPTIONAL> (r1x) ;
	}

	inline implicit operator OPTIONAL & () leftvalue {
		return to () ;
	}

	const OPTIONAL &to () const leftvalue {
		_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS...>) == 1) ;
		_DYNAMIC_ASSERT_ (exist ()) ;
		auto &r1x = _LOAD_<TEMP<OPTIONAL>> (DEPTR[mVariant]) ;
		return _CAST_<OPTIONAL> (r1x) ;
	}

	inline implicit operator const OPTIONAL & () const leftvalue {
		return to () ;
	}

	template <class _ARG1>
	void apply (const Function<void (_ARG1 &)> &proc) {
		if (!available<_ARG1> ())
			return ;
		auto &r1x = _LOAD_<TEMP<_ARG1>> (DEPTR[mVariant]) ;
		proc (_CAST_<_ARG1> (r1x)) ;
	}

	template <class _ARG1>
	void apply (const Function<U::MEMBER_FUNCTION_HINT<void ,_ARG1 &>> &proc) {
		if (!available<_ARG1> ())
			return ;
		auto &r1x = _LOAD_<TEMP<_ARG1>> (DEPTR[mVariant]) ;
		proc (_CAST_<_ARG1> (r1x)) ;
	}

	//@warn: none class shall be base on its address
	void aswap (Variant &that) {
		_SWAP_ (mVariant ,that.mVariant) ;
		_SWAP_ (mIndex ,that.mIndex) ;
	}

public:
	static Variant nullopt () {
		return Variant (ARGVP0) ;
	}

private:
	explicit Variant (const DEF<decltype (ARGVP0)> &) noexcept
		:mIndex (VAR_NONE) {}

private:
	void template_construct (const INDEX &index ,const ARGV<ARGVS<>> &) {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1>
	void template_construct (const INDEX &index ,const ARGV<_ARG1> &) {
		using ONE_HINT = ARGVS_ONE_TYPE<_ARG1> ;
		using REST_HINT = ARGVS_REST_TYPE<_ARG1> ;
		_STATIC_ASSERT_ (stl::is_nothrow_move_constructible<ONE_HINT>::value) ;
		_STATIC_ASSERT_ (stl::is_nothrow_move_assignable<ONE_HINT>::value) ;
		const auto r1x = BOOL (index == 0) ;
		if switch_once (TRUE) {
			if (!r1x)
				discard ;
			auto &r2x = _NULL_<ARGV<ARGC<stl::is_default_constructible<ONE_HINT>::value>>> () ;
			auto &r3x = _LOAD_<TEMP<ONE_HINT>> (DEPTR[mVariant]) ;
			template_create (r2x ,DEPTR[r3x]) ;
		}
		if (r1x)
			return ;
		template_construct ((index - 1) ,_NULL_<ARGV<REST_HINT>> ()) ;
	}

	void template_destruct (const INDEX &index ,const ARGV<ARGVS<>> &) {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1>
	void template_destruct (const INDEX &index ,const ARGV<_ARG1> &) {
		using ONE_HINT = ARGVS_ONE_TYPE<_ARG1> ;
		using REST_HINT = ARGVS_REST_TYPE<_ARG1> ;
		_STATIC_ASSERT_ (stl::is_nothrow_destructible<ONE_HINT>::value) ;
		_STATIC_ASSERT_ (stl::is_nothrow_move_constructible<ONE_HINT>::value) ;
		_STATIC_ASSERT_ (stl::is_nothrow_move_assignable<ONE_HINT>::value) ;
		const auto r1x = BOOL (index == 0) ;
		if switch_once (TRUE) {
			if (!r1x)
				discard ;
			auto &r2x = _LOAD_<TEMP<ONE_HINT>> (DEPTR[mVariant]) ;
			_DESTROY_ (DEPTR[r2x]) ;
		}
		if (r1x)
			return ;
		template_destruct ((index - 1) ,_NULL_<ARGV<REST_HINT>> ()) ;
	}

	void template_copy_construct (const Variant &that ,const INDEX &index ,const ARGV<ARGVS<>> &) {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1>
	void template_copy_construct (const Variant &that ,const INDEX &index ,const ARGV<_ARG1> &) {
		using ONE_HINT = ARGVS_ONE_TYPE<_ARG1> ;
		using REST_HINT = ARGVS_REST_TYPE<_ARG1> ;
		const auto r1x = BOOL (index == 0) ;
		if switch_once (TRUE) {
			if (!r1x)
				discard ;
			auto &r2x = _NULL_<ARGV<ARGC<stl::is_copy_constructible<ONE_HINT>::value && stl::is_nothrow_move_constructible<ONE_HINT>::value>>> () ;
			auto &r3x = _LOAD_<TEMP<ONE_HINT>> (DEPTR[mVariant]) ;
			auto &r4x = _LOAD_<TEMP<ONE_HINT>> (DEPTR[that.mVariant]) ;
			template_create (r2x ,DEPTR[r3x] ,_MOVE_ (_CAST_<ONE_HINT> (r4x))) ;
		}
		if (r1x)
			return ;
		template_copy_construct (that ,(index - 1) ,_NULL_<ARGV<REST_HINT>> ()) ;
	}

	void template_move_construct (Variant &that ,const INDEX &index ,const ARGV<ARGVS<>> &) {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1>
	void template_move_construct (Variant &that ,const INDEX &index ,const ARGV<_ARG1> &) {
		using ONE_HINT = ARGVS_ONE_TYPE<_ARG1> ;
		using REST_HINT = ARGVS_REST_TYPE<_ARG1> ;
		_STATIC_ASSERT_ (stl::is_nothrow_move_constructible<ONE_HINT>::value) ;
		_STATIC_ASSERT_ (stl::is_nothrow_move_assignable<ONE_HINT>::value) ;
		const auto r1x = BOOL (index == 0) ;
		if switch_once (TRUE) {
			if (!r1x)
				discard ;
			auto &r2x = _LOAD_<TEMP<ONE_HINT>> (DEPTR[mVariant]) ;
			auto &r3x = _LOAD_<TEMP<ONE_HINT>> (DEPTR[that.mVariant]) ;
			template_create (_NULL_<ARGV<ARGC<TRUE>>> () ,DEPTR[r2x] ,_MOVE_ (_CAST_<ONE_HINT> (r3x))) ;
		}
		if (r1x)
			return ;
		template_move_construct (that ,(index - 1) ,_NULL_<ARGV<REST_HINT>> ()) ;
	}

private:
	template <class _ARG1>
	static INDEX default_constructible_index (const ARGV<_ARG1> & ,const ARGV<ARGVS<>> &) {
		return VAR_NONE ;
	}

	template <class _ARG1 ,class _ARG2>
	static INDEX default_constructible_index (const ARGV<_ARG1> & ,const ARGV<_ARG2> &) {
		using ONE_HINT = ARGVS_ONE_TYPE<_ARG2> ;
		using REST_HINT = ARGVS_REST_TYPE<_ARG2> ;
		if (stl::is_default_constructible<ONE_HINT>::value)
			return _ARG1::value ;
		return default_constructible_index (_NULL_<ARGV<INCREASE<_ARG1>>> () ,_NULL_<ARGV<REST_HINT>> ()) ;
	}

	template <class _ARG1 ,class... _ARGS>
	static void template_create (const ARGV<ARGC<TRUE>> & ,const PTR<TEMP<_ARG1>> &address ,_ARGS &&...initval) {
		_CREATE_ (address ,_FORWARD_<_ARGS> (initval)...) ;
	}

	template <class _ARG1 ,class... _ARGS>
	static void template_create (const ARGV<ARGC<FALSE>> & ,const PTR<TEMP<_ARG1>> &address ,_ARGS &&...initval) {
		_DYNAMIC_ASSERT_ (FALSE) ;
	}
} ;

template <class UNIT>
using Optional = Variant<UNIT> ;

template <class UNIT>
class Monostate {
private:
	SharedRef<UNIT> mValue ;

public:
	Monostate () {
		mValue = SharedRef<UNIT>::make () ;
	}

	inline Monostate (const Monostate &) = delete ;
	inline Monostate &operator= (const Monostate &) = delete ;

	inline Monostate (Monostate &&) = delete ;
	inline Monostate &operator= (Monostate &&) = delete ;

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
	Tuple () = default ;

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
	Tuple () = default ;

	implicit Tuple (FORWARD_TRAITS_TYPE<UNIT1> &&one_ ,FORWARD_TRAITS_TYPE<UNITS> &&...rest_)
		:Tuple<UNITS...> (_FORWARD_<FORWARD_TRAITS_TYPE<UNITS>> (rest_)...) ,mValue (_FORWARD_<FORWARD_TRAITS_TYPE<UNIT1>> (one_)) {}

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
		return template_pick (_NULL_<ARGV<DECREASE<_ARG1>>> ()) ;
	}

	template <class _ARG1>
	const INDEX_TO_TYPE<DECREASE<_ARG1> ,ARGVS<UNIT1 ,UNITS...>> &pick (const ARGV<ARGVP<_ARG1>> &) const leftvalue {
		return template_pick (_NULL_<ARGV<DECREASE<_ARG1>>> ()) ;
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
	UNIT1 &template_pick (const ARGV<ZERO> &) leftvalue {
		return one () ;
	}

	template <class _ARG1>
	INDEX_TO_TYPE<_ARG1 ,ARGVS<UNIT1 ,UNITS...>> &template_pick (const ARGV<_ARG1> &) leftvalue {
		_STATIC_ASSERT_ (_ARG1::value > 0 && _ARG1::value <= _CAPACITYOF_ (ARGVS<UNITS...>)) ;
		return rest ().template_pick (_NULL_<ARGV<DECREASE<_ARG1>>> ()) ;
	}

	const UNIT1 &template_pick (const ARGV<ZERO> &) const leftvalue {
		return one () ;
	}

	template <class _ARG1>
	const INDEX_TO_TYPE<_ARG1 ,ARGVS<UNIT1 ,UNITS...>> &template_pick (const ARGV<_ARG1> &) const leftvalue {
		_STATIC_ASSERT_ (_ARG1::value > 0 && _ARG1::value <= _CAPACITYOF_ (ARGVS<UNITS...>)) ;
		return rest ().template_pick (_NULL_<ARGV<DECREASE<_ARG1>>> ()) ;
	}
} ;

template <class... UNITS>
using TupleBinder = Tuple<UNITS &...> ;

template <class UNIT1 ,class... UNITS>
template <class... UNITS_>
class Function<UNIT1 (UNITS...)>::Private::ImplHolder<PTR<UNIT1 (UNITS... ,UNITS_...)>>
	:public Function<UNIT1 (UNITS...)>::Holder {
private:
	Function<UNIT1 (UNITS... ,UNITS_...)> mFunctor ;
	Tuple<REMOVE_CVR_TYPE<UNITS_>...> mParameter ;

public:
	ImplHolder () = delete ;

	explicit ImplHolder (const PTR<UNIT1 (UNITS... ,UNITS_...)> &func ,const REMOVE_CVR_TYPE<UNITS_> &...parameter)
		:mFunctor (func) ,mParameter (parameter...) {}

	UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const override {
		return template_invoke (mParameter ,_FORWARD_<FORWARD_TRAITS_TYPE<UNITS>> (funcval)...) ;
	}

private:
	UNIT1 template_invoke (const Tuple<> &parameter ,FORWARD_TRAITS_TYPE<UNITS> &&...funcval1 ,const REMOVE_CVR_TYPE<UNITS_> &...funcval2) const {
		return mFunctor (_FORWARD_<FORWARD_TRAITS_TYPE<UNITS>> (funcval1)... ,funcval2...) ;
	}

	template <class _ARG1 ,class... _ARGS>
	UNIT1 template_invoke (const _ARG1 &parameter ,_ARGS &&...funcval) const {
		return template_invoke (parameter.rest () ,_FORWARD_<_ARGS> (funcval)... ,parameter.one ()) ;
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
	using WRAPPED = INDEX_TO_TYPE<ZERO ,ARGVS<UNITS...>> ;

private:
	TupleBinder<const UNITS...> mTuple ;

public:
	AllOfTuple () = delete ;

	implicit AllOfTuple (const UNITS &...initval)
		:mTuple (initval...) {}

	inline implicit operator BOOL () rightvalue {
		return template_boolean (mTuple) ;
	}

	inline BOOL operator== (const WRAPPED &that) const {
		return template_equal (mTuple ,that) ;
	}

	inline friend BOOL operator== (const WRAPPED &that ,const AllOfTuple &self_) {
		return _MOVE_ (self_) == that ;
	}

	inline BOOL operator!= (const WRAPPED &that) const {
		return template_not_equal (mTuple ,that) ;
	}

	inline friend BOOL operator!= (const WRAPPED &that ,const AllOfTuple &self_) {
		return _MOVE_ (self_) != that ;
	}

	inline BOOL operator< (const WRAPPED &that) const {
		return template_less (mTuple ,that) ;
	}

	inline friend BOOL operator< (const WRAPPED &that ,const AllOfTuple &self_) {
		return _MOVE_ (self_) > that ;
	}

	inline BOOL operator>= (const WRAPPED &that) const {
		return template_not_less (mTuple ,that) ;
	}

	inline friend BOOL operator>= (const WRAPPED &that ,const AllOfTuple &self_) {
		return _MOVE_ (self_) <= that ;
	}

	inline BOOL operator> (const WRAPPED &that) const {
		return template_less (that ,mTuple) ;
	}

	inline friend BOOL operator> (const WRAPPED &that ,const AllOfTuple &self_) {
		return _MOVE_ (self_) < that ;
	}

	inline BOOL operator<= (const WRAPPED &that) const {
		return template_not_less (that ,mTuple) ;
	}

	inline friend BOOL operator<= (const WRAPPED &that ,const AllOfTuple &self_) {
		return _MOVE_ (self_) >= that ;
	}

private:
	static BOOL operator_equal (const WRAPPED &lhs ,const WRAPPED &rhs) {
		return BOOL (lhs == rhs) ;
	}

	static BOOL operator_less (const WRAPPED &lhs ,const WRAPPED &rhs) {
		return BOOL (lhs < rhs) ;
	}

	static BOOL template_boolean (const Tuple<> &self_) {
		return TRUE ;
	}

	template <class _ARG1>
	static BOOL template_boolean (const _ARG1 &self_) {
		if (!BOOL (self_.one ()))
			return FALSE ;
		return template_boolean (self_.rest ()) ;
	}

	static BOOL template_equal (const Tuple<> &self_ ,const WRAPPED &that) {
		return TRUE ;
	}

	template <class _ARG1>
	static BOOL template_equal (const _ARG1 &self_ ,const WRAPPED &that) {
		if (!operator_equal (self_.one () ,that))
			return FALSE ;
		return template_equal (self_.rest () ,that) ;
	}

	static BOOL template_not_equal (const Tuple<> &self_ ,const WRAPPED &that) {
		return TRUE ;
	}

	template <class _ARG1>
	static BOOL template_not_equal (const _ARG1 &self_ ,const WRAPPED &that) {
		if (operator_equal (self_.one () ,that))
			return FALSE ;
		return template_not_equal (self_.rest () ,that) ;
	}

	static BOOL template_less (const Tuple<> &self_ ,const WRAPPED &that) {
		return TRUE ;
	}

	template <class _ARG1>
	static BOOL template_less (const _ARG1 &self_ ,const WRAPPED &that) {
		if (!operator_less (self_.one () ,that))
			return FALSE ;
		return template_less (self_.rest () ,that) ;
	}

	static BOOL template_not_less (const Tuple<> &self_ ,const WRAPPED &that) {
		return TRUE ;
	}

	template <class _ARG1>
	static BOOL template_not_less (const _ARG1 &self_ ,const WRAPPED &that) {
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
	using WRAPPED = INDEX_TO_TYPE<ZERO ,ARGVS<UNITS...>> ;

private:
	TupleBinder<const UNITS...> mTuple ;

public:
	AnyOfTuple () = delete ;

	implicit AnyOfTuple (const UNITS &...initval)
		:mTuple (initval...) {}

	inline implicit operator BOOL () rightvalue {
		return template_boolean (mTuple) ;
	}

	inline BOOL operator== (const WRAPPED &that) const {
		return template_equal (mTuple ,that) ;
	}

	inline friend BOOL operator== (const WRAPPED &that ,const AnyOfTuple &self_) {
		return _MOVE_ (self_) == that ;
	}

	inline BOOL operator!= (const WRAPPED &that) const {
		return template_not_equal (mTuple ,that) ;
	}

	inline friend BOOL operator!= (const WRAPPED &that ,const AnyOfTuple &self_) {
		return _MOVE_ (self_) != that ;
	}

	inline BOOL operator< (const WRAPPED &that) const {
		return template_less (mTuple ,that) ;
	}

	inline friend BOOL operator< (const WRAPPED &that ,const AnyOfTuple &self_) {
		return _MOVE_ (self_) > that ;
	}

	inline BOOL operator>= (const WRAPPED &that) const {
		return template_not_less (mTuple ,that) ;
	}

	inline friend BOOL operator>= (const WRAPPED &that ,const AnyOfTuple &self_) {
		return _MOVE_ (self_) <= that ;
	}

	inline BOOL operator> (const WRAPPED &that) const {
		return template_less (that ,mTuple) ;
	}

	inline friend BOOL operator> (const WRAPPED &that ,const AnyOfTuple &self_) {
		return _MOVE_ (self_) < that ;
	}

	inline BOOL operator<= (const WRAPPED &that) const {
		return template_not_less (that ,mTuple) ;
	}

	inline friend BOOL operator<= (const WRAPPED &that ,const AnyOfTuple &self_) {
		return _MOVE_ (self_) >= that ;
	}

private:
	static BOOL operator_equal (const WRAPPED &lhs ,const WRAPPED &rhs) {
		return BOOL (lhs == rhs) ;
	}

	static BOOL operator_less (const WRAPPED &lhs ,const WRAPPED &rhs) {
		return BOOL (lhs < rhs) ;
	}

	static BOOL template_boolean (const Tuple<> &self_) {
		return FALSE ;
	}

	template <class _ARG1>
	static BOOL template_boolean (const _ARG1 &self_) {
		if (BOOL (self_.one ()))
			return TRUE ;
		return template_boolean (self_.rest ()) ;
	}

	static BOOL template_equal (const Tuple<> &self_ ,const WRAPPED &that) {
		return FALSE ;
	}

	template <class _ARG1>
	static BOOL template_equal (const _ARG1 &self_ ,const WRAPPED &that) {
		if (operator_equal (self_.one () ,that))
			return TRUE ;
		return template_equal (self_.rest () ,that) ;
	}

	static BOOL template_not_equal (const Tuple<> &self_ ,const WRAPPED &that) {
		return FALSE ;
	}

	template <class _ARG1>
	static BOOL template_not_equal (const _ARG1 &self_ ,const WRAPPED &that) {
		if (!operator_equal (self_.one () ,that))
			return TRUE ;
		return template_not_equal (self_.rest () ,that) ;
	}

	static BOOL template_less (const Tuple<> &self_ ,const WRAPPED &that) {
		return FALSE ;
	}

	template <class _ARG1>
	static BOOL template_less (const _ARG1 &self_ ,const WRAPPED &that) {
		if (operator_less (self_.one () ,that))
			return TRUE ;
		return template_less (self_.rest () ,that) ;
	}

	static BOOL template_not_less (const Tuple<> &self_ ,const WRAPPED &that) {
		return FALSE ;
	}

	template <class _ARG1>
	static BOOL template_not_less (const _ARG1 &self_ ,const WRAPPED &that) {
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
	SharedRef<SELF_PACK> mThis ;
} ;

namespace U {
struct OPERATOR_RECAST {
	template <class _ARG1 ,class _ARG2>
	static PTR<_ARG2> template_recast (const PTR<_ARG1> &address ,const ARGV<_ARG2> & ,const ARGV<ENABLE_TYPE<stl::is_always_base_of<_ARG2 ,_ARG1>::value>> & ,const DEF<decltype (ARGVP3)> &) {
		return static_cast<PTR<_ARG2>> (address) ;
	}

	template <class _ARG1 ,class _ARG2>
	static PTR<_ARG2> template_recast (const PTR<_ARG1> &address ,const ARGV<_ARG2> & ,const ARGV<ENABLE_TYPE<stl::is_always_base_of<Interface ,_ARG1>::value && stl::is_always_base_of<Interface ,_ARG2>::value>> & ,const DEF<decltype (ARGVP2)> &) {
		//@warn: RTTI might be different across DLL
		return dynamic_cast<PTR<_ARG2>> (address) ;
	}

	template <class _ARG1 ,class _ARG2>
	static PTR<_ARG2> template_recast (const PTR<_ARG1> &address ,const ARGV<_ARG2> & ,const DEF<decltype (ARGVPX)> & ,const DEF<decltype (ARGVP1)> &) {
		return NULL ;
	}

	template <class _RET ,class _ARG1>
	static PTR<_RET> invoke (const PTR<_ARG1> &address) {
		_STATIC_ASSERT_ (!stl::is_reference<_RET>::value) ;
		return template_recast (address ,_NULL_<ARGV<CAST_TRAITS_TYPE<_RET ,_ARG1>>> () ,ARGVPX ,ARGVP9) ;
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
	SharedRef<SELF_PACK> mThis ;
	PTR<UNIT> mPointer ;

public:
	StrongRef ()
		:StrongRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	//@warn: circular reference ruins StrongRef
	template <class _ARG1 ,class = ENABLE_TYPE<stl::is_always_base_of<UNIT ,_ARG1>::value>>
	implicit StrongRef (const StrongRef<_ARG1> &that)
		: StrongRef (that.template recast<UNIT> ()) {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _DEP = NONE>
	implicit StrongRef (const WeakRef<UNIT> &that)
		: StrongRef (_FORWARD_<DEPENDENT_TYPE<WeakRef<UNIT> ,_DEP>> (that).watch ()) {
		_STATIC_WARNING_ ("noop") ;
	}

	inline ~StrongRef () noexcept {
		if (mPointer == NULL)
			return ;
		_STATIC_WARNING_ ("mark") ;
		if switch_once (TRUE) {
			const auto r1x = --mThis->mCounter ;
			if (r1x != 0)
				discard ;
			mThis->mHolder = AnyRef<void> () ;
		}
		mPointer = NULL ;
	}

	inline StrongRef (const StrongRef &that)
		:StrongRef (_COPY_ (that.mThis) ,that.mPointer) {
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

	inline StrongRef (StrongRef &&that) noexcept
		:StrongRef (ARGVP0) {
		mThis = _MOVE_ (that.mThis) ;
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
		if (!mThis.exist ())
			return FALSE ;
		if (!mThis->mHolder.exist ())
			return FALSE ;
		return TRUE ;
	}

	template <class _RET>
	StrongRef<CAST_TRAITS_TYPE<_RET ,UNIT>> recast () const {
		_STATIC_ASSERT_ (!stl::is_reference<_RET>::value) ;
		const auto r1x = U::OPERATOR_RECAST::template invoke<_RET> (mPointer) ;
		_DYNAMIC_ASSERT_ (_EBOOL_ (r1x != NULL) == _EBOOL_ (mPointer != NULL)) ;
		return StrongRef<CAST_TRAITS_TYPE<_RET ,UNIT>> (_COPY_ (mThis) ,r1x) ;
	}

	UNIT &to () const leftvalue {
		_DEBUG_ASSERT_ (exist ()) ;
		const auto r1x = static_cast<PTR<UNIT>> (mPointer) ;
		return DEREF[r1x] ;
	}

	inline implicit operator UNIT & () const leftvalue {
		return to () ;
	}

	inline PTR<UNIT> operator-> () const leftvalue {
		return DEPTR[to ()] ;
	}

	BOOL equal (const StrongRef &that) const {
		if (!mThis.exist ())
			if (!that.mThis.exist ())
				return TRUE ;
		if (!mThis.exist ())
			return FALSE ;
		if (!that.mThis.exist ())
			return FALSE ;
		if (DEPTR[mThis.self] != DEPTR[that.mThis.self])
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
		auto &r1x = _FORWARD_<const DEPENDENT_TYPE<WeakRef<UNIT> ,Dependent> &> (that) ;
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
	static StrongRef make (_ARGS &&...initval) {
		auto tmp = SharedRef<SELF_PACK>::make () ;
		tmp->mHolder = AnyRef<REMOVE_CVR_TYPE<UNIT>>::make (_FORWARD_<_ARGS> (initval)...) ;
		tmp->mCounter = 0 ;
		auto &r1x = tmp->mHolder.rebind<UNIT> ().self ;
		return StrongRef (_MOVE_ (tmp) ,DEPTR[r1x]) ;
	}

private:
	explicit StrongRef (const DEF<decltype (ARGVP0)> &) noexcept
		:mPointer (NULL) {}

	explicit StrongRef (SharedRef<SELF_PACK> &&this_ ,const PTR<UNIT> &pointer) noexcept
		:StrongRef (ARGVP0) {
		if (pointer == NULL)
			return ;
		const auto r1x = ++this_->mCounter ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x > 0) ;
		mThis = _MOVE_ (this_) ;
		mPointer = pointer ;
	}
} ;

template <class UNIT>
class WeakRef {
private:
	using SELF_PACK = typename WeakRef<void>::SELF_PACK ;

private:
	SharedRef<SELF_PACK> mThis ;
	PTR<UNIT> mPointer ;

public:
	WeakRef () {
		mPointer = NULL ;
	}

	BOOL exist () const {
		if (!mThis.exist ())
			return FALSE ;
		if (!mThis->mHolder.exist ())
			return FALSE ;
		if (mPointer == NULL)
			return FALSE ;
		return TRUE ;
	}

	BOOL equal (const WeakRef &that) const {
		if (!mThis.exist ())
			if (!that.mThis.exist ())
				return TRUE ;
		if (!mThis.exist ())
			return FALSE ;
		if (!that.mThis.exist ())
			return FALSE ;
		if (DEPTR[mThis.self] != DEPTR[that.mThis.self])
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
		if (!mThis.exist ())
			if (!that.mThis.exist ())
				return TRUE ;
		if (!mThis.exist ())
			return FALSE ;
		if (!that.mThis.exist ())
			return FALSE ;
		if (DEPTR[mThis.self] != DEPTR[that.mThis.self])
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
		return StrongRef<UNIT> (mThis ,mPointer) ;
	}

	void assign (const StrongRef<UNIT> &that) {
		mThis = that.mThis ;
		mPointer = that.mPointer ;
	}

	void assign (StrongRef<UNIT> &&that) {
		mThis = _MOVE_ (that.mThis) ;
		mPointer = _MOVE_ (that.mPointer) ;
	}
} ;

#ifdef __CSC_DEPRECATED__
template <class UNIT>
class SoftRef final {
public:
	SoftRef () {
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
	IntrusiveRef ()
		:IntrusiveRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	//@warn: address must be from 'IntrusiveRef::make'
	template <class _ARG1 ,class = ENABLE_TYPE<stl::is_same<_ARG1 ,PTR<UNIT>>::value>>
	explicit IntrusiveRef (const _ARG1 &address)
		: IntrusiveRef (ARGVP0) {
		acquire (address ,FALSE) ;
		const auto r1x = safe_exchange (address) ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x == NULL) ;
	}

	inline ~IntrusiveRef () noexcept {
		const auto r1x = safe_exchange (NULL) ;
		_CALL_TRY_ ([&] () {
			release (r1x) ;
		} ,[&] () {
			_DEBUG_ASSERT_ (FALSE) ;
		}) ;
	}

	inline IntrusiveRef (const IntrusiveRef &) = delete ;
	inline IntrusiveRef &operator= (const IntrusiveRef &) = delete ;

	inline IntrusiveRef (IntrusiveRef &&that) noexcept
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

	IntrusiveRef share () side_effects {
		struct Dependent ;
		using LatchCounter = DEPENDENT_TYPE<DEF<typename Private::LatchCounter> ,Dependent> ;
		ScopedGuard<LatchCounter> ANONYMOUS (_CAST_<LatchCounter> (mLatch)) ;
		const auto r1x = mPointer.load () ;
		return IntrusiveRef (r1x) ;
	}

	DEF<typename Private::WatchProxy> watch () side_effects {
		struct Dependent ;
		using WatchProxy = DEPENDENT_TYPE<DEF<typename Private::WatchProxy> ,Dependent> ;
		using LatchCounter = DEPENDENT_TYPE<DEF<typename Private::LatchCounter> ,Dependent> ;
		ScopedGuard<LatchCounter> ANONYMOUS (_CAST_<LatchCounter> (mLatch)) ;
		const auto r1x = mPointer.load () ;
		_DYNAMIC_ASSERT_ (r1x != NULL) ;
		auto tmp = IntrusiveRef (r1x) ;
		return WatchProxy (_MOVE_ (tmp) ,r1x) ;
	}

public:
	template <class... _ARGS>
	static IntrusiveRef make (_ARGS &&...initval) {
		IntrusiveRef ret ;
		auto rax = GlobalHeap::alloc<TEMP<UNIT>> () ;
		ScopedBuild<UNIT> ANONYMOUS (rax ,_FORWARD_<_ARGS> (initval)...) ;
		auto &r1x = _LOAD_<UNIT> (_FORWARD_<const PTR<TEMP<UNIT>> &> (rax)) ;
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
		INDEX ir = 0 ;
		while (TRUE) {
			const auto r2x = ir++ ;
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
	static void acquire (const PTR<UNIT> &address ,const BOOL &init) {
		if (address == NULL)
			return ;
		if (init)
			CONT::friend_create (DEREF[address]) ;
		const auto r1x = CONT::friend_attach (DEREF[address]) ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x >= 1 + _EBOOL_ (!init)) ;
	}

	static void release (const PTR<UNIT> &address) {
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
	PTR<UNIT> mPointer ;

public:
	WatchProxy () = delete ;

	explicit WatchProxy (IntrusiveRef &&base ,const PTR<UNIT> &pointer) {
		mBase = UniqueRef<IntrusiveRef> ([&] (IntrusiveRef &me) {
			me = _MOVE_ (base) ;
		} ,[] (IntrusiveRef &me) {
			_STATIC_WARNING_ ("noop") ;
		}) ;
		mPointer = pointer ;
	}

	inline implicit operator UNIT & () const leftvalue {
		const auto r1x = static_cast<PTR<UNIT>> (mPointer) ;
		return DEREF[r1x] ;
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

	exports class Holder
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
	UniqueRef<SELF_PACK> mThis ;

public:
	MemoryPool () {
		initialize () ;
	}

	LENGTH size () const {
		LENGTH ret = 0 ;
		for (auto &&i : _RANGE_ (0 ,mThis->mPool.size ()))
			ret += mThis->mPool[i]->size () ;
		return _MOVE_ (ret) ;
	}

	LENGTH length () const {
		LENGTH ret = 0 ;
		for (auto &&i : _RANGE_ (0 ,mThis->mPool.size ()))
			ret += mThis->mPool[i]->length () ;
		return _MOVE_ (ret) ;
	}

	//@warn: held by RAII to avoid static-memory-leaks
	template <class _RET>
	PTR<_RET> alloc () side_effects {
		_STATIC_ASSERT_ (!stl::is_reference<_RET>::value) ;
		_STATIC_ASSERT_ (stl::is_pod<_RET>::value) ;
		const auto r1x = _ALIGNOF_ (_RET) - _ALIGNOF_ (HEADER) ;
		const auto r2x = VAR_ZERO ;
		const auto r3x = _MAX_ (r1x ,r2x) + _SIZEOF_ (_RET) ;
		const auto r4x = (r3x - 1) / 8 ;
		const auto r5x = _SIZEOF_ (HEADER) ;
		INDEX ix = _MIN_ (r4x ,r5x) ;
		const auto r6x = mThis->mPool[ix]->alloc (r3x) ;
		const auto r7x = _ALIGNAS_ (_ADDRESS_ (r6x) + r5x ,_ALIGNOF_ (_RET)) ;
		const auto r8x = r7x - r5x ;
		auto &r9x = _LOAD_UNSAFE_<HEADER> (r8x) ;
		r9x.mFrom = DEPTR[mThis->mPool[ix].self] ;
		r9x.mCurr = r6x ;
		auto &r10x = _LOAD_UNSAFE_<_RET> (r7x) ;
		return DEPTR[r10x] ;
	}

	//@warn: held by RAII to avoid static-memory-leaks
	template <class _RET>
	PTR<ARR<_RET>> alloc (const LENGTH &len) side_effects {
		_STATIC_ASSERT_ (!stl::is_reference<_RET>::value) ;
		_STATIC_ASSERT_ (stl::is_pod<_RET>::value) ;
		const auto r1x = _ALIGNOF_ (_RET) - _ALIGNOF_ (HEADER) ;
		const auto r2x = VAR_ZERO ;
		const auto r3x = _MAX_ (r1x ,r2x) + len * _SIZEOF_ (_RET) ;
		_DEBUG_ASSERT_ (r3x > 0) ;
		const auto r4x = (r3x - 1) / 8 ;
		const auto r5x = _SIZEOF_ (HEADER) ;
		INDEX ix = _MIN_ (r4x ,r5x) ;
		const auto r6x = mThis->mPool[ix]->alloc (r3x) ;
		const auto r7x = _ALIGNAS_ (_ADDRESS_ (r6x) + r5x ,_ALIGNOF_ (_RET)) ;
		const auto r8x = r7x - r5x ;
		auto &r9x = _LOAD_UNSAFE_<HEADER> (r8x) ;
		r9x.mFrom = DEPTR[mThis->mPool[ix].self] ;
		r9x.mCurr = r6x ;
		auto &r10x = _LOAD_UNSAFE_<ARR<_RET>> (r7x) ;
		return DEPTR[r10x] ;
	}

	template <class _ARG1>
	void free (const PTR<_ARG1> &address) noexcept {
		_STATIC_ASSERT_ (stl::is_pod<REMOVE_ARRAY_TYPE<_ARG1>>::value) ;
		const auto r1x = _ADDRESS_ (address) - _SIZEOF_ (HEADER) ;
		auto &r2x = _LOAD_UNSAFE_<HEADER> (r1x) ;
		INDEX ix = BasicProc::mem_chr (mThis->mPool.self ,mThis->mPool.size () ,r2x.mFrom) ;
		mThis->mPool[ix]->free (r2x.mCurr) ;
	}

	void clean () {
		for (auto &&i : _RANGE_ (0 ,mThis->mPool.size ()))
			mThis->mPool[i]->clean () ;
	}

private:
	void initialize () ;
} ;

template <class SIZE ,class RESE>
class MemoryPool::Private::ImplHolder
	:public Holder {
	_STATIC_ASSERT_ (SIZE::value > 0) ;
	_STATIC_ASSERT_ (RESE::value > 0) ;

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
	ImplHolder () {
		mRoot = NULL ;
		mFree = NULL ;
		mSize = 0 ;
		mLength = 0 ;
	}

	void clear () noexcept override {
		if (mRoot == NULL)
			return ;
		for (PTR<CHUNK> i = mRoot ,it ; i != NULL ; i = it) {
			it = i->mNext ;
			GlobalHeap::free (i->mOrigin) ;
		}
		mRoot = NULL ;
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
		const auto r1x = _ALIGNAS_ (_SIZEOF_ (BLOCK) + SIZE::value ,_ALIGNOF_ (BLOCK)) ;
		const auto r2x = _ALIGNOF_ (CHUNK) - 1 + _SIZEOF_ (CHUNK) + _ALIGNOF_ (BLOCK) - 1 + RESE::value * r1x ;
		auto rax = GlobalHeap::alloc<BYTE> (r2x) ;
		const auto r3x = _ADDRESS_ (_FORWARD_<const PTR<ARR<BYTE>> &> (rax)) ;
		const auto r4x = _ALIGNAS_ (r3x ,_ALIGNOF_ (CHUNK)) ;
		auto &r5x = _LOAD_UNSAFE_<CHUNK> (r4x) ;
		r5x.mOrigin = rax ;
		r5x.mPrev = NULL ;
		r5x.mNext = mRoot ;
		r5x.mCount = RESE::value ;
		if (mRoot != NULL)
			mRoot->mPrev = DEPTR[r5x] ;
		mRoot = DEPTR[r5x] ;
		mSize += RESE::value * SIZE::value ;
		const auto r6x = _ALIGNAS_ (r4x + _SIZEOF_ (CHUNK) ,_ALIGNOF_ (BLOCK)) ;
		for (auto &&i : _RANGE_ (0 ,mRoot->mCount)) {
			const auto r7x = r6x + i * r1x ;
			auto &r8x = _LOAD_UNSAFE_<BLOCK> (r7x) ;
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
		r1x->mNext = _BITWISE_CAST_<PTR<BLOCK>> (r2x) ;
		return DEPTR[r1x->mFlexData] ;
	}

	void free (const PTR<HEADER> &address) noexcept override {
		_DEBUG_ASSERT_ (address != NULL) ;
		auto &r1x = _OFFSET_ (&BLOCK::mFlexData ,DEREF[address]) ;
		_DEBUG_ASSERT_ (_ADDRESS_ (r1x.mNext) == VAR_USED) ;
		r1x.mNext = mFree ;
		mFree = DEPTR[r1x] ;
		mLength -= SIZE::value ;
	}

	void clean () noexcept override {
		if (mSize == mLength)
			return ;
		for (PTR<CHUNK> i = mRoot ,it ; i != NULL ; i = it) {
			it = i->mNext ;
			if (!empty_node (i))
				continue ;
			auto &r1x = _SWITCH_ (
				(i->mPrev != NULL) ? i->mPrev->mNext :
				mRoot) ;
			r1x = i->mNext ;
			if (i->mNext != NULL)
				i->mNext->mPrev = i->mPrev ;
			mSize -= i->mCount * SIZE::value ;
			GlobalHeap::free (i->mOrigin) ;
		}
	}

private:
	BOOL empty_node (const PTR<const CHUNK> &node) const {
		const auto r1x = _ALIGNAS_ (_SIZEOF_ (BLOCK) + SIZE::value ,_ALIGNOF_ (BLOCK)) ;
		const auto r2x = _ALIGNAS_ (_ADDRESS_ (node) + _SIZEOF_ (CHUNK) ,_ALIGNOF_ (BLOCK)) ;
		for (auto &&i : _RANGE_ (0 ,node->mCount)) {
			const auto r3x = r2x + i * r1x ;
			auto &r4x = _LOAD_UNSAFE_<BLOCK> (r3x) ;
			if (_ADDRESS_ (r4x.mNext) == VAR_USED)
				return FALSE ;
		}
		return TRUE ;
	}
} ;

class MemoryPool::Private::HugeHolder
	:public Holder {
private:
	struct FBLOCK {
		PTR<ARR<BYTE>> mOrigin ;
		PTR<struct FBLOCK> mPrev ;
		PTR<struct FBLOCK> mNext ;
		LENGTH mCount ;
		HEADER mFlexData ;
	} ;

private:
	PTR<FBLOCK> mRoot ;
	LENGTH mSize ;
	LENGTH mLength ;

public:
	HugeHolder () {
		mRoot = NULL ;
		mSize = 0 ;
		mLength = 0 ;
	}

	void clear () noexcept override {
		if (mRoot == NULL)
			return ;
		for (PTR<FBLOCK> i = mRoot ,it ; i != NULL ; i = it) {
			it = i->mNext ;
			GlobalHeap::free (i->mOrigin) ;
		}
		mRoot = NULL ;
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
		const auto r1x = _ALIGNAS_ (len ,_ALIGNOF_ (FBLOCK)) ;
		const auto r2x = _ALIGNOF_ (FBLOCK) - 1 + _SIZEOF_ (FBLOCK) + r1x ;
		auto rax = GlobalHeap::alloc<BYTE> (r2x) ;
		const auto r3x = _ADDRESS_ (_FORWARD_<const PTR<ARR<BYTE>> &> (rax)) ;
		const auto r4x = _ALIGNAS_ (r3x ,_ALIGNOF_ (FBLOCK)) ;
		auto &r5x = _LOAD_UNSAFE_<FBLOCK> (r4x) ;
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
		auto &r1x = _OFFSET_ (&FBLOCK::mFlexData ,DEREF[address]) ;
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

inline exports void MemoryPool::initialize () {
	struct Dependent ;
	using ImplHolder8 = DEPENDENT_TYPE<DEF<typename Private::template ImplHolder<ARGC<8> ,ARGC<32>>> ,Dependent> ;
	using ImplHolder16 = DEPENDENT_TYPE<DEF<typename Private::template ImplHolder<ARGC<16> ,ARGC<32>>> ,Dependent> ;
	using ImplHolder24 = DEPENDENT_TYPE<DEF<typename Private::template ImplHolder<ARGC<24> ,ARGC<32>>> ,Dependent> ;
	using ImplHolder32 = DEPENDENT_TYPE<DEF<typename Private::template ImplHolder<ARGC<32> ,ARGC<32>>> ,Dependent> ;
	using ImplHolder40 = DEPENDENT_TYPE<DEF<typename Private::template ImplHolder<ARGC<40> ,ARGC<16>>> ,Dependent> ;
	using ImplHolder48 = DEPENDENT_TYPE<DEF<typename Private::template ImplHolder<ARGC<48> ,ARGC<16>>> ,Dependent> ;
	using ImplHolder56 = DEPENDENT_TYPE<DEF<typename Private::template ImplHolder<ARGC<56> ,ARGC<16>>> ,Dependent> ;
	using ImplHolder64 = DEPENDENT_TYPE<DEF<typename Private::template ImplHolder<ARGC<64> ,ARGC<16>>> ,Dependent> ;
	using ImplHolder72 = DEPENDENT_TYPE<DEF<typename Private::template ImplHolder<ARGC<72> ,ARGC<8>>> ,Dependent> ;
	using ImplHolder80 = DEPENDENT_TYPE<DEF<typename Private::template ImplHolder<ARGC<80> ,ARGC<8>>> ,Dependent> ;
	using ImplHolder88 = DEPENDENT_TYPE<DEF<typename Private::template ImplHolder<ARGC<88> ,ARGC<8>>> ,Dependent> ;
	using ImplHolder96 = DEPENDENT_TYPE<DEF<typename Private::template ImplHolder<ARGC<96> ,ARGC<8>>> ,Dependent> ;
	using ImplHolder104 = DEPENDENT_TYPE<DEF<typename Private::template ImplHolder<ARGC<104> ,ARGC<4>>> ,Dependent> ;
	using ImplHolder112 = DEPENDENT_TYPE<DEF<typename Private::template ImplHolder<ARGC<112> ,ARGC<4>>> ,Dependent> ;
	using ImplHolder120 = DEPENDENT_TYPE<DEF<typename Private::template ImplHolder<ARGC<120> ,ARGC<4>>> ,Dependent> ;
	using ImplHolder128 = DEPENDENT_TYPE<DEF<typename Private::template ImplHolder<ARGC<128> ,ARGC<4>>> ,Dependent> ;
	using HugeHolder = DEPENDENT_TYPE<DEF<typename Private::HugeHolder> ,Dependent> ;
	mThis = UniqueRef<SELF_PACK> ([&] (SELF_PACK &me) {
		me.mPool = AutoBuffer<StrongRef<Holder>> (17) ;
		me.mPool[0] = StrongRef<ImplHolder8>::make () ;
		me.mPool[1] = StrongRef<ImplHolder16>::make () ;
		me.mPool[2] = StrongRef<ImplHolder24>::make () ;
		me.mPool[3] = StrongRef<ImplHolder32>::make () ;
		me.mPool[4] = StrongRef<ImplHolder40>::make () ;
		me.mPool[5] = StrongRef<ImplHolder48>::make () ;
		me.mPool[6] = StrongRef<ImplHolder56>::make () ;
		me.mPool[7] = StrongRef<ImplHolder64>::make () ;
		me.mPool[8] = StrongRef<ImplHolder72>::make () ;
		me.mPool[9] = StrongRef<ImplHolder80>::make () ;
		me.mPool[10] = StrongRef<ImplHolder88>::make () ;
		me.mPool[11] = StrongRef<ImplHolder96>::make () ;
		me.mPool[12] = StrongRef<ImplHolder104>::make () ;
		me.mPool[13] = StrongRef<ImplHolder112>::make () ;
		me.mPool[14] = StrongRef<ImplHolder120>::make () ;
		me.mPool[15] = StrongRef<ImplHolder128>::make () ;
		me.mPool[16] = StrongRef<HugeHolder>::make () ;
	} ,[] (SELF_PACK &me) {
		for (auto &&i : _RANGE_ (0 ,me.mPool.size ()))
			me.mPool[i]->clear () ;
	}) ;
}

class Object ;

exports class Objective
	:public Interface {
public:
	virtual WeakRef<Object> weak_of_this () const = 0 ;
	virtual void weak_of_this (const StrongRef<Object> &that) = 0 ;
	virtual StrongRef<Object> clone () const = 0 ;
} ;

class Object
	:public Objective {
public:
	struct Public {
		class Virtual ;
	} ;

private:
	struct Private {
		class Metadata ;
	} ;

private:
	WeakRef<Object> mWeakOfThis ;

public:
	Object () = delete ;

	template <class _ARG1>
	explicit Object (const ARGV<_ARG1> &) {
		_STATIC_ASSERT_ (stl::is_always_base_of<Object ,_ARG1>::value) ;
		_STATIC_ASSERT_ (!stl::is_same<REMOVE_CVR_TYPE<_ARG1> ,Object>::value) ;
	}

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

private:
	Metadata () = delete ;

	template <class _ARG1>
	explicit Metadata (const ARGV<_ARG1> &) {
		_STATIC_ASSERT_ (stl::is_same<REMOVE_CVR_TYPE<_ARG1> ,_ARG1>::value) ;
		mObjectSize = _SIZEOF_ (_ARG1) ;
		mObjectAlign = _ALIGNOF_ (_ARG1) ;
		mObjectTypeMID = _TYPEMID_<_ARG1> () ;
		const auto r1x = _FORWARD_<PTR<void (PTR<NONE>)>> ([] (const PTR<NONE> &address) {
			auto &r2x = _LOAD_<TEMP<_ARG1>> (address) ;
			_CREATE_ (DEPTR[r2x]) ;
		}) ;
		mConstrutor = r1x ;
		const auto r3x = _FORWARD_<PTR<void (PTR<NONE>)>> ([] (const PTR<NONE> &address) {
			auto &r4x = _LOAD_<TEMP<_ARG1>> (address) ;
			_DESTROY_ (DEPTR[r4x]) ;
		}) ;
		mDestructor = r1x ;
	}
} ;

class Object::Public::Virtual
	:public virtual Object {
public:
	Virtual ()
		:Object (_NULL_<ARGV<decltype (DEREF[this])>> ()) {
		_STATIC_WARNING_ ("noop") ;
	}
} ;

template <class UNIT ,class CONT>
class Serializer {
private:
	exports class Holder
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
	Serializer () = delete ;

	template <class... _ARGS>
	explicit Serializer (const ARGV<ARGVS<_ARGS...>> &) {
		struct Dependent ;
		using ImplHolder = DEPENDENT_TYPE<DEF<typename Private::template ImplHolder<_ARGS...>> ,Dependent> ;
		_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<_ARGS...>) > 0) ;
		mHolder = StrongRef<ImplHolder>::make (_NULL_<ARGV<ARGVS<_ARGS...>>> ()) ;
	}

	inline DEF<typename Private::Member> operator() (CONT &context_) const side_effects {
		struct Dependent ;
		using Member = DEPENDENT_TYPE<DEF<typename Private::Member> ,Dependent> ;
		_DEBUG_ASSERT_ (mHolder.exist ()) ;
		return Member (DEREF[this] ,context_) ;
	}
} ;

template <class UNIT ,class CONT>
class Serializer<UNIT ,CONT>::Private::Member
	:private Proxy {
private:
	const Serializer &mBase ;
	CONT &mContext ;

public:
	Member () = delete ;

	explicit Member (const Serializer &base ,CONT &context_)
		: mBase (base) ,mContext (context_) {}

	void friend_visit (UNIT &visitor) {
		mBase.mHolder->compute_visit (visitor ,mContext) ;
	}
} ;

template <class UNIT ,class CONT>
template <class... UNITS_>
class Serializer<UNIT ,CONT>::Private::ImplHolder
	:public Holder {
public:
	ImplHolder () = delete ;

	explicit ImplHolder (const ARGV<ARGVS<UNITS_...>> &) {
		_STATIC_WARNING_ ("noop") ;
	}

	void compute_visit (UNIT &visitor ,CONT &context_) const override {
		template_visit (visitor ,context_ ,_NULL_<ARGV<ARGVS<UNITS_...>>> ()) ;
	}

private:
	void template_visit (UNIT &visitor ,CONT &context_ ,const ARGV<ARGVS<>> &) const {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1>
	void template_visit (UNIT &visitor ,CONT &context_ ,const ARGV<_ARG1> &) const {
		using ONE_HINT = ARGVS_ONE_TYPE<_ARG1> ;
		using REST_HINT = ARGVS_REST_TYPE<_ARG1> ;
		auto &r1x = ONE_HINT::compile (context_) ;
		visitor.visit (r1x) ;
		template_visit (visitor ,context_ ,_NULL_<ARGV<REST_HINT>> ()) ;
	}
} ;
} ;