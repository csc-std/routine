﻿#pragma once

#ifndef __CSC_EXTEND__
#define __CSC_EXTEND__
#endif

#include "csc.hpp"
#include "csc_core.hpp"
#include "csc_basic.hpp"

namespace CSC {
#ifdef __CSC_UNITTEST__
class GlobalWatch :
	delegate private Wrapped<> {
private:
	struct Private {
		template <class>
		class WatchInterface ;
	} ;

public:
	template <class _ARG1 ,class _ARG2>
	imports void done (const ARGVF<_ARG1> & ,const Plain<STR> &name ,_ARG2 &data) {
		using R1X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template WatchInterface<_ARG2> ;
		static R1X mInstance ;
		mInstance.mName = name.self ;
		mInstance.mAddress = DEPTR[data] ;
		mInstance.mWatch (data) ;
	}
} ;

template <class UNIT>
class GlobalWatch::Private::WatchInterface :
	delegate private Interface {
private:
	friend GlobalWatch ;
	PTR<const STR> mName ;
	PTR<UNIT> mAddress ;
	Function<void (UNIT &)> mWatch ;

public:
	implicit WatchInterface () {
		mName = NULL ;
		mAddress = NULL ;
		mWatch = Function<void (UNIT &)> ([] (UNIT &) {
			_STATIC_WARNING_ ("noop") ;
		}) ;
	} ;
} ;
#endif

class VAR128 {
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
		const auto r1x = _CAST_ (ARGV<VAR64>::ID ,v2i0) ;
		const auto r2x = _CAST_ (ARGV<VAR64>::ID ,that.v2i0) ;
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
		const auto r1x = _CAST_ (ARGV<VAR64>::ID ,v2i0) ;
		const auto r2x = _CAST_ (ARGV<VAR64>::ID ,that.v2i0) ;
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

	inline VAR128 operator++ (VAR32) {
		VAR128 ret = DEREF[this] ;
		++DEREF[this] ;
		return _MOVE_ (ret) ;
	}

	inline VAR128 &operator-- () {
		v2i1-- ;
		v2i0 -= _EBOOL_ (v2i1 == DATA (-1)) ;
		return DEREF[this] ;
	}

	inline VAR128 operator-- (VAR32) {
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
		const auto r1x = _CAST_ (ARGV<VAR64>::ID ,v2i0) ;
		const auto r2x = _CAST_ (ARGV<VAR64>::ID ,that.v2i0) ;
		const auto r3x = ComprInvokeProc::invoke (r1x ,r2x) ;
		if (r3x != 0)
			return r3x ;
		return ComprInvokeProc::invoke (v2i1 ,that.v2i1) ;
	}

	inline DATA &m_v2i0 () leftvalue {
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = WORD (0X0001) ;
		return _CAST_ (ARGV<DATA[2]>::ID ,mValue)[_CAST_ (ARGV<BYTE[2]>::ID ,r1x)[0]] ;
	}

	inline const DATA &m_v2i0 () const leftvalue {
		const auto r1x = WORD (0X0001) ;
		return _CAST_ (ARGV<DATA[2]>::ID ,mValue)[_CAST_ (ARGV<BYTE[2]>::ID ,r1x)[0]] ;
	}

	inline DATA &m_v2i1 () leftvalue {
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = WORD (0X0001) ;
		return _CAST_ (ARGV<DATA[2]>::ID ,mValue)[_CAST_ (ARGV<BYTE[2]>::ID ,r1x)[1]] ;
	}

	inline const DATA &m_v2i1 () const leftvalue {
		const auto r1x = WORD (0X0001) ;
		return _CAST_ (ARGV<DATA[2]>::ID ,mValue)[_CAST_ (ARGV<BYTE[2]>::ID ,r1x)[1]] ;
	}

	inline CHAR &m_v4i0 () leftvalue {
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_ (ARGV<CHAR[4]>::ID ,mValue)[_CAST_ (ARGV<BYTE[4]>::ID ,r1x)[0]] ;
	}

	inline const CHAR &m_v4i0 () const leftvalue {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_ (ARGV<CHAR[4]>::ID ,mValue)[_CAST_ (ARGV<BYTE[4]>::ID ,r1x)[0]] ;
	}

	inline CHAR &m_v4i1 () leftvalue {
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_ (ARGV<CHAR[4]>::ID ,mValue)[_CAST_ (ARGV<BYTE[4]>::ID ,r1x)[1]] ;
	}

	inline const CHAR &m_v4i1 () const leftvalue {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_ (ARGV<CHAR[4]>::ID ,mValue)[_CAST_ (ARGV<BYTE[4]>::ID ,r1x)[1]] ;
	}

	inline CHAR &m_v4i2 () leftvalue {
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_ (ARGV<CHAR[4]>::ID ,mValue)[_CAST_ (ARGV<BYTE[4]>::ID ,r1x)[2]] ;
	}

	inline const CHAR &m_v4i2 () const leftvalue {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_ (ARGV<CHAR[4]>::ID ,mValue)[_CAST_ (ARGV<BYTE[4]>::ID ,r1x)[2]] ;
	}

	inline CHAR &m_v4i3 () leftvalue {
		_STATIC_WARNING_ ("mark") ;
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_ (ARGV<CHAR[4]>::ID ,mValue)[_CAST_ (ARGV<BYTE[4]>::ID ,r1x)[3]] ;
	}

	inline const CHAR &m_v4i3 () const leftvalue {
		const auto r1x = CHAR (0X00010203) ;
		return _CAST_ (ARGV<CHAR[4]>::ID ,mValue)[_CAST_ (ARGV<BYTE[4]>::ID ,r1x)[3]] ;
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
} ;

namespace U {
template <class...>
struct CONSTEXPR_MAX_SIZEOF ;

template <>
struct CONSTEXPR_MAX_SIZEOF<> {
	imports constexpr VAR compile () {
		return LENGTH (1) ;
	}
} ;

template <class _ARG1 ,class... _ARGS>
struct CONSTEXPR_MAX_SIZEOF<_ARG1 ,_ARGS...> {
	imports constexpr VAR compile () {
		using R1X = SIZE_OF_TYPE<_ARG1> ;
		using R2X = CONSTEXPR_MAX_SIZEOF<_ARGS...> ;
		using R3X = CONSTEXPR_MAX<R1X ,R2X> ;
		return R3X::compile () ;
	}
} ;

template <class...>
struct CONSTEXPR_MAX_ALIGNOF ;

template <>
struct CONSTEXPR_MAX_ALIGNOF<> {
	imports constexpr VAR compile () {
		return LENGTH (1) ;
	}
} ;

template <class _ARG1 ,class... _ARGS>
struct CONSTEXPR_MAX_ALIGNOF<_ARG1 ,_ARGS...> {
	imports constexpr VAR compile () {
		using R1X = ALIGN_OF_TYPE<_ARG1> ;
		using R2X = CONSTEXPR_MAX_ALIGNOF<_ARGS...> ;
		using R3X = CONSTEXPR_MAX<R1X ,R2X> ;
		return R3X::compile () ;
	}
} ;
} ;

template <class... UNITS>
class Variant final {
#pragma push_macro ("fake")
#undef fake
#define fake m_fake ()

private:
	_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS...>) > 0) ;
	_STATIC_ASSERT_ (U::CONSTEXPR_NOT<IS_ANY_SAME_HELP<REMOVE_CVR_TYPE<UNITS>...>>::compile ()) ;

	struct Private {
		template <class>
		class ImplHolder ;
	} ;

	class FakeHolder ;

	class Holder :
		delegate public Interface {
	public:
		virtual INDEX type_index () const = 0 ;
		virtual PTR<NONE> fast_pointer () = 0 ;
		virtual PTR<const NONE> fast_pointer () const = 0 ;
		virtual void friend_copy (const PTR<TEMP<FakeHolder>> &address) const = 0 ;
		virtual void friend_move (const PTR<TEMP<FakeHolder>> &address) = 0 ;
	} ;

	//@error: fuck g++4.8
	template <LENGTH _ARG1 ,LENGTH _ARG2>
	struct ALIGNED_UNION {
		alignas (_ARG1) DEF<BYTE[_ARG2]> mUnused ;
	} ;

	class FakeHolder :
		delegate public Holder {
	private:
		using ALIGN = U::CONSTEXPR_MAX_ALIGNOF<UNITS...> ;
		using SIZE = U::CONSTEXPR_MAX_SIZEOF<UNITS...> ;

	private:
		TEMP<ALIGNED_UNION<(ALIGN::compile ()) ,(SIZE::compile ())>> mUnused ;
	} ;

	using OPTIONAL = INDEX_TO_TYPE<ZERO ,ARGVS<UNITS...>> ;

private:
	TEMP<FakeHolder> mVariant ;

public:
	implicit Variant () :
		delegate Variant (ARGVP0) {
		const auto r1x = default_constructible_index (ARGV<ZERO>::ID ,ARGV<ARGVS<UNITS...>>::ID) ;
		if (r1x == VAR_NONE)
			return ;
		template_construct (r1x ,ARGV<ARGVS<UNITS...>>::ID) ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<U::CONSTEXPR_AND<U::CONSTEXPR_NOT<IS_PLACEHOLDER_HELP<_ARG1>> ,U::CONSTEXPR_NOT<IS_SAME_HELP<REMOVE_CVR_TYPE<_ARG1> ,Variant>>>>>
	implicit Variant (_ARG1 &&that) :
		delegate Variant (ARGVP0) {
		using R1X = INDEX_OF_TYPE<REMOVE_CVR_TYPE<_ARG1> ,ARGVS<REMOVE_CVR_TYPE<UNITS>...>> ;
		using R2X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<REMOVE_CVR_TYPE<_ARG1>> ;
		_STATIC_ASSERT_ (U::CONSTEXPR_NOT<U::CONSTEXPR_EQUAL<R1X ,ARGC<VAR_NONE>>>::compile ()) ;
		const auto r1x = _POINTER_CAST_ (ARGV<TEMP<R2X>>::ID ,DEPTR[mVariant]) ;
		template_create (r1x ,ARGVPX ,_FORWARD_ (ARGV<_ARG1 &&>::ID ,that)) ;
	}

	implicit ~Variant () noexcept {
		if (!exist ())
			return ;
		_DESTROY_ (mVariant) ;
		_ZERO_ (mVariant) ;
	}

	implicit Variant (const Variant &that) :
		delegate Variant (ARGVP0) {
		if (!that.exist ())
			return ;
		that.fake.friend_copy (DEPTR[mVariant]) ;
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

	implicit Variant (Variant &&that) noexcept :
		delegate Variant (ARGVP0) {
		if (!that.exist ())
			return ;
		that.fake.friend_move (DEPTR[mVariant]) ;
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
		auto &r1x = _FORWARD_ (ARGV<Interface>::ID ,fake) ;
		const auto r2x = _CAST_ (ARGV<FLAG>::ID ,r1x) ;
		if (r2x == VAR_ZERO)
			return FALSE ;
		return TRUE ;
	}

	template <class _ARG1>
	BOOL available (const ARGVF<_ARG1> &) const {
		using R1X = INDEX_OF_TYPE<REMOVE_CVR_TYPE<_ARG1> ,ARGVS<REMOVE_CVR_TYPE<UNITS>...>> ;
		if (!exist ())
			return FALSE ;
		if (fake.type_index () != R1X::compile ())
			return FALSE ;
		return TRUE ;
	}

	OPTIONAL &to () leftvalue {
		_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS...>) == 1) ;
		_DYNAMIC_ASSERT_ (exist ()) ;
		const auto r1x = fake.fast_pointer () ;
		const auto r2x = _POINTER_CAST_ (ARGV<OPTIONAL>::ID ,r1x) ;
		return DEREF[r2x] ;
	}

	inline implicit operator OPTIONAL & () leftvalue {
		return self ;
	}

	const OPTIONAL &to () const leftvalue {
		_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS...>) == 1) ;
		_DYNAMIC_ASSERT_ (exist ()) ;
		const auto r1x = fake.fast_pointer () ;
		const auto r2x = _POINTER_CAST_ (ARGV<OPTIONAL>::ID ,r1x) ;
		return DEREF[r2x] ;
	}

	inline implicit operator const OPTIONAL & () const leftvalue {
		return self ;
	}

	template <class _ARG1>
	void apply (const Function<void (_ARG1 &)> &proc) {
		if (!available (ARGV<_ARG1>::ID))
			return ;
		const auto r1x = fake.fast_pointer () ;
		const auto r2x = _POINTER_CAST_ (ARGV<_ARG1>::ID ,r1x) ;
		proc (DEREF[r2x]) ;
	}

	imports Variant nullopt () {
		return Variant (ARGVP0) ;
	}

private:
	explicit Variant (const DEF<decltype (ARGVP0)> &) noexcept {
		_ZERO_ (mVariant) ;
	}

	inline Holder &m_fake () leftvalue {
		return _CAST_ (ARGV<FakeHolder>::ID ,mVariant) ;
	}

	inline const Holder &m_fake () const leftvalue {
		return _CAST_ (ARGV<FakeHolder>::ID ,mVariant) ;
	}

	template <class _ARG1>
	imports INDEX default_constructible_index (const ARGVF<_ARG1> & ,const ARGVF<ARGVS<>> &) {
		return VAR_NONE ;
	}

	template <class _ARG1 ,class _ARG2>
	imports INDEX default_constructible_index (const ARGVF<_ARG1> & ,const ARGVF<_ARG2> &) {
		using R1X = IS_DEFAULT_CONSTRUCTIBLE_HELP<PARAMS_ONE_TYPE<_ARG2>> ;
		using R2X = PARAMS_REST_TYPE<_ARG2> ;
		if (R1X::compile ())
			return _ARG1::compile () ;
		return default_constructible_index (ARGV<U::CONSTEXPR_INCREASE<_ARG1>>::ID ,ARGV<R2X>::ID) ;
	}

	template <class... _ARGS>
	void template_construct (const INDEX &index ,const ARGVF<ARGVS<>> & ,_ARGS &&...initval) {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1 ,class... _ARGS>
	void template_construct (const INDEX &index ,const ARGVF<_ARG1> & ,_ARGS &&...initval) {
		using R1X = PARAMS_ONE_TYPE<_ARG1> ;
		using R2X = PARAMS_REST_TYPE<_ARG1> ;
		using R3X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<REMOVE_CVR_TYPE<R1X>> ;
		if switch_once (TRUE) {
			if (!(index == 0))
				discard ;
			const auto r1x = _POINTER_CAST_ (ARGV<TEMP<R3X>>::ID ,DEPTR[mVariant]) ;
			template_create (r1x ,ARGVPX ,_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) ;
			return ;
		}
		template_construct ((index - 1) ,ARGV<R2X>::ID ,_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) ;
	}

	template <class _ARG1 ,class... _ARGS ,class = ENABLE_TYPE<IS_CONSTRUCTIBLE_HELP<_ARG1 ,ARGVS<_ARGS...>>>>
	imports void template_create (const PTR<TEMP<typename Private::template ImplHolder<_ARG1>>> &address ,const DEF<decltype (ARGVP2)> & ,_ARGS &&...initval) {
		using R1X = typename Private::template ImplHolder<_ARG1> ;
		const auto r1x = _POINTER_CAST_ (ARGV<TEMP<R1X>>::ID ,address) ;
		auto &r2x = _FORWARD_ (ARGV<Holder>::ID ,_CAST_ (ARGV<R1X>::ID ,DEREF[r1x])) ;
		auto &r3x = _FORWARD_ (ARGV<Holder>::ID ,_CAST_ (ARGV<FakeHolder>::ID ,DEREF[address])) ;
		_DYNAMIC_ASSERT_ (DEPTR[r2x] == DEPTR[r3x]) ;
		_CREATE_ (r1x ,ARGVP0 ,_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) ;
	}

	template <class _ARG1 ,class... _ARGS>
	imports void template_create (const PTR<TEMP<typename Private::template ImplHolder<_ARG1>>> &address ,const DEF<decltype (ARGVP1)> & ,_ARGS &&...initval) {
		_DYNAMIC_ASSERT_ (FALSE) ;
	}

#pragma pop_macro ("fake")
} ;

template <class... UNITS>
template <class UNIT_>
class Variant<UNITS...>::Private::ImplHolder :
	delegate public Holder {
private:
	_STATIC_ASSERT_ (IS_MOVE_CONSTRUCTIBLE_HELP<UNIT_>::compile ()) ;

private:
	REMOVE_CVR_TYPE<UNIT_> mValue ;

public:
	implicit ImplHolder () = delete ;

	template <class... _ARGS>
	explicit ImplHolder (const DEF<decltype (ARGVP0)> & ,_ARGS &&...initval) :
		delegate mValue (_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) {}

	INDEX type_index () const override {
		using R1X = INDEX_OF_TYPE<REMOVE_CVR_TYPE<UNIT_> ,ARGVS<REMOVE_CVR_TYPE<UNITS>...>> ;
		return R1X::compile () ;
	}

	PTR<NONE> fast_pointer () override {
		return DEPTR[mValue] ;
	}

	PTR<const NONE> fast_pointer () const override {
		return DEPTR[mValue] ;
	}

	void friend_copy (const PTR<TEMP<FakeHolder>> &address) const override {
		const auto r1x = _POINTER_CAST_ (ARGV<TEMP<ImplHolder<UNIT_>>>::ID ,address) ;
		template_create (r1x ,ARGVPX ,_MOVE_ (mValue)) ;
	}

	void friend_move (const PTR<TEMP<FakeHolder>> &address) override {
		const auto r1x = _POINTER_CAST_ (ARGV<TEMP<ImplHolder<UNIT_>>>::ID ,address) ;
		template_create (r1x ,ARGVPX ,_MOVE_ (mValue)) ;
	}
} ;

template <class UNIT>
using Optional = Variant<UNIT> ;

template <class UNIT>
class Monostate :
	delegate private Proxy {
private:
	SharedRef<UNIT> mThis ;

public:
	implicit Monostate () {
		mThis = SharedRef<UNIT>::make () ;
	}

	UNIT &to () const leftvalue {
		return mThis.self ;
	}

	inline implicit operator UNIT & () const leftvalue {
		return self ;
	}

	void swap (Monostate &that) {
		_SWAP_ (mThis ,that.mThis) ;
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
class Tuple<UNIT1 ,UNITS...> :
	delegate private Tuple<UNITS...> {
private:
	_STATIC_ASSERT_ (U::CONSTEXPR_NOT<IS_RVALUE_REFERENCE_HELP<UNIT1>>::compile ()) ;

private:
	template <class...>
	friend class Tuple ;
	UNIT1 mValue ;

public:
	implicit Tuple () = default ;

	implicit Tuple (FORWARD_TRAITS_TYPE<UNIT1> &&one_ ,FORWARD_TRAITS_TYPE<UNITS> &&...rest_) :
		delegate Tuple<UNITS...> (_FORWARD_ (ARGV<FORWARD_TRAITS_TYPE<UNITS> &&>::ID ,rest_)...) ,
		delegate mValue (_FORWARD_ (ARGV<FORWARD_TRAITS_TYPE<UNIT1> &&>::ID ,one_)) {}

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
	INDEX_TO_TYPE<U::CONSTEXPR_DECREASE<_ARG1> ,ARGVS<UNIT1 ,UNITS...>> &pick (const ARGV<ARGVP<_ARG1>> &) leftvalue {
		using R1X = ARGC_TYPE<U::CONSTEXPR_DECREASE<_ARG1>> ;
		return template_pick (ARGV<R1X>::ID) ;
	}

	template <class _ARG1>
	const INDEX_TO_TYPE<U::CONSTEXPR_DECREASE<_ARG1> ,ARGVS<UNIT1 ,UNITS...>> &pick (const ARGV<ARGVP<_ARG1>> &) const leftvalue {
		using R1X = ARGC_TYPE<U::CONSTEXPR_DECREASE<_ARG1>> ;
		return template_pick (ARGV<R1X>::ID) ;
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
		const auto r1x = ComprInvokeProc::invoke (one () ,that.one ()) ;
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
		using R1X = ARGC_TYPE<U::CONSTEXPR_DECREASE<_ARG1>> ;
		using R2X = CAPACITY_OF_TYPE<ARGVS<UNITS...>> ;
		_STATIC_ASSERT_ (U::CONSTEXPR_RANGE_CHECK<R1X ,ZERO ,R2X>::compile ()) ;
		return rest ().template_pick (ARGV<R1X>::ID) ;
	}

	const UNIT1 &template_pick (const ARGVF<ZERO> &) const leftvalue {
		return one () ;
	}

	template <class _ARG1>
	const INDEX_TO_TYPE<_ARG1 ,ARGVS<UNIT1 ,UNITS...>> &template_pick (const ARGVF<_ARG1> &) const leftvalue {
		using R1X = ARGC_TYPE<U::CONSTEXPR_DECREASE<_ARG1>> ;
		using R2X = CAPACITY_OF_TYPE<ARGVS<UNITS...>> ;
		_STATIC_ASSERT_ (U::CONSTEXPR_RANGE_CHECK<R1X ,ZERO ,R2X>::compile ()) ;
		return rest ().template_pick (ARGV<R1X>::ID) ;
	}
} ;

template <class... UNITS>
using TupleBinder = Tuple<UNITS &...> ;

template <class...>
class AllOfTuple ;

template <class...>
class AnyOfTuple ;

template <class... UNITS>
class AllOfTuple :
	delegate private Proxy {
private:
	_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS...>) > 0) ;
	_STATIC_ASSERT_ (IS_ALL_SAME_HELP<UNITS...>::compile ()) ;

	using WRAPPED = INDEX_TO_TYPE<ZERO ,ARGVS<UNITS...>> ;

private:
	TupleBinder<const UNITS...> mBinder ;

public:
	implicit AllOfTuple () = delete ;

	implicit AllOfTuple (const DEF<decltype (ARGVP0)> & ,const UNITS &...initval) :
		delegate mBinder (initval...) {}

	inline implicit operator BOOL () rightvalue {
		return template_boolean (mBinder) ;
	}

	inline implicit operator BOOL () const leftvalue = delete ;

	inline BOOL operator== (const WRAPPED &that) const {
		return template_equal (mBinder ,that) ;
	}

	inline friend BOOL operator== (const WRAPPED &that ,const AllOfTuple &this_) {
		return template_equal (this_.mBinder ,that) ;
	}

	inline BOOL operator!= (const WRAPPED &that) const {
		return template_not_equal (mBinder ,that) ;
	}

	inline friend BOOL operator!= (const WRAPPED &that ,const AllOfTuple &this_) {
		return template_not_equal (this_.mBinder ,that) ;
	}

	inline BOOL operator< (const WRAPPED &that) const {
		return template_less (mBinder ,that) ;
	}

	inline friend BOOL operator< (const WRAPPED &that ,const AllOfTuple &this_) {
		return template_less (that ,this_.mBinder) ;
	}

	inline BOOL operator>= (const WRAPPED &that) const {
		return template_not_less (mBinder ,that) ;
	}

	inline friend BOOL operator>= (const WRAPPED &that ,const AllOfTuple &this_) {
		return template_not_less (that ,this_.mBinder) ;
	}

	inline BOOL operator> (const WRAPPED &that) const {
		return template_less (that ,mBinder) ;
	}

	inline friend BOOL operator> (const WRAPPED &that ,const AllOfTuple &this_) {
		return template_less (this_.mBinder ,that) ;
	}

	inline BOOL operator<= (const WRAPPED &that) const {
		return template_not_less (that ,mBinder) ;
	}

	inline friend BOOL operator<= (const WRAPPED &that ,const AllOfTuple &this_) {
		return template_not_less (this_.mBinder ,that) ;
	}

private:
	imports BOOL operator_equal (const WRAPPED &lhs ,const WRAPPED &rhs) {
		return BOOL (lhs == rhs) ;
	}

	imports BOOL operator_less (const WRAPPED &lhs ,const WRAPPED &rhs) {
		return BOOL (lhs < rhs) ;
	}

	imports BOOL template_boolean (const Tuple<> &this_) {
		return TRUE ;
	}

	template <class _ARG1>
	imports BOOL template_boolean (const _ARG1 &this_) {
		if (!BOOL (this_.one ()))
			return FALSE ;
		return template_boolean (this_.rest ()) ;
	}

	imports BOOL template_equal (const Tuple<> &this_ ,const WRAPPED &that) {
		return TRUE ;
	}

	template <class _ARG1>
	imports BOOL template_equal (const _ARG1 &this_ ,const WRAPPED &that) {
		if (!operator_equal (this_.one () ,that))
			return FALSE ;
		return template_equal (this_.rest () ,that) ;
	}

	imports BOOL template_not_equal (const Tuple<> &this_ ,const WRAPPED &that) {
		return TRUE ;
	}

	template <class _ARG1>
	imports BOOL template_not_equal (const _ARG1 &this_ ,const WRAPPED &that) {
		if (operator_equal (this_.one () ,that))
			return FALSE ;
		return template_not_equal (this_.rest () ,that) ;
	}

	imports BOOL template_less (const Tuple<> &this_ ,const WRAPPED &that) {
		return TRUE ;
	}

	template <class _ARG1>
	imports BOOL template_less (const _ARG1 &this_ ,const WRAPPED &that) {
		if (!operator_less (this_.one () ,that))
			return FALSE ;
		return template_less (this_.rest () ,that) ;
	}

	imports BOOL template_not_less (const Tuple<> &this_ ,const WRAPPED &that) {
		return TRUE ;
	}

	template <class _ARG1>
	imports BOOL template_not_less (const _ARG1 &this_ ,const WRAPPED &that) {
		if (operator_less (this_.one () ,that))
			return FALSE ;
		return template_not_less (this_.rest () ,that) ;
	}
} ;

template <class... UNITS>
class AnyOfTuple :
	delegate private Proxy {
private:
	_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS...>) > 0) ;
	_STATIC_ASSERT_ (IS_ALL_SAME_HELP<UNITS...>::compile ()) ;

	using WRAPPED = INDEX_TO_TYPE<ZERO ,ARGVS<UNITS...>> ;

private:
	TupleBinder<const UNITS...> mBinder ;

public:
	implicit AnyOfTuple () = delete ;

	implicit AnyOfTuple (const DEF<decltype (ARGVP0)> & ,const UNITS &...initval) :
		delegate mBinder (initval...) {}

	inline implicit operator BOOL () rightvalue {
		return template_boolean (mBinder) ;
	}

	inline implicit operator BOOL () const leftvalue = delete ;

	inline BOOL operator== (const WRAPPED &that) const {
		return template_equal (mBinder ,that) ;
	}

	inline friend BOOL operator== (const WRAPPED &that ,const AnyOfTuple &this_) {
		return template_equal (this_.mBinder ,that) ;
	}

	inline BOOL operator!= (const WRAPPED &that) const {
		return template_not_equal (mBinder ,that) ;
	}

	inline friend BOOL operator!= (const WRAPPED &that ,const AnyOfTuple &this_) {
		return template_not_equal (this_.mBinder ,that) ;
	}

	inline BOOL operator< (const WRAPPED &that) const {
		return template_less (mBinder ,that) ;
	}

	inline friend BOOL operator< (const WRAPPED &that ,const AnyOfTuple &this_) {
		return template_less (that ,this_.mBinder) ;
	}

	inline BOOL operator>= (const WRAPPED &that) const {
		return template_not_less (mBinder ,that) ;
	}

	inline friend BOOL operator>= (const WRAPPED &that ,const AnyOfTuple &this_) {
		return template_not_less (that ,this_.mBinder) ;
	}

	inline BOOL operator> (const WRAPPED &that) const {
		return template_less (that ,mBinder) ;
	}

	inline friend BOOL operator> (const WRAPPED &that ,const AnyOfTuple &this_) {
		return template_less (this_.mBinder ,that) ;
	}

	inline BOOL operator<= (const WRAPPED &that) const {
		return template_not_less (that ,mBinder) ;
	}

	inline friend BOOL operator<= (const WRAPPED &that ,const AnyOfTuple &this_) {
		return template_not_less (this_.mBinder ,that) ;
	}

private:
	imports BOOL operator_equal (const WRAPPED &lhs ,const WRAPPED &rhs) {
		return BOOL (lhs == rhs) ;
	}

	imports BOOL operator_less (const WRAPPED &lhs ,const WRAPPED &rhs) {
		return BOOL (lhs < rhs) ;
	}

	imports BOOL template_boolean (const Tuple<> &this_) {
		return FALSE ;
	}

	template <class _ARG1>
	imports BOOL template_boolean (const _ARG1 &this_) {
		if (BOOL (this_.one ()))
			return TRUE ;
		return template_boolean (this_.rest ()) ;
	}

	imports BOOL template_equal (const Tuple<> &this_ ,const WRAPPED &that) {
		return FALSE ;
	}

	template <class _ARG1>
	imports BOOL template_equal (const _ARG1 &this_ ,const WRAPPED &that) {
		if (operator_equal (this_.one () ,that))
			return TRUE ;
		return template_equal (this_.rest () ,that) ;
	}

	imports BOOL template_not_equal (const Tuple<> &this_ ,const WRAPPED &that) {
		return FALSE ;
	}

	template <class _ARG1>
	imports BOOL template_not_equal (const _ARG1 &this_ ,const WRAPPED &that) {
		if (!operator_equal (this_.one () ,that))
			return TRUE ;
		return template_not_equal (this_.rest () ,that) ;
	}

	imports BOOL template_less (const Tuple<> &this_ ,const WRAPPED &that) {
		return FALSE ;
	}

	template <class _ARG1>
	imports BOOL template_less (const _ARG1 &this_ ,const WRAPPED &that) {
		if (operator_less (this_.one () ,that))
			return TRUE ;
		return template_less (this_.rest () ,that) ;
	}

	imports BOOL template_not_less (const Tuple<> &this_ ,const WRAPPED &that) {
		return FALSE ;
	}

	template <class _ARG1>
	imports BOOL template_not_less (const _ARG1 &this_ ,const WRAPPED &that) {
		if (!operator_less (this_.one () ,that))
			return TRUE ;
		return template_not_less (this_.rest () ,that) ;
	}
} ;

template <class UNIT>
class Atomic {
private:
	_STATIC_ASSERT_ (IS_BYTE_XYZ_HELP<UNIT>::compile ()) ;

private:
	api::atomic<UNIT> mValue ;

public:
	implicit Atomic () {
		mValue.store (UNIT (0)) ;
	}

	UNIT fetch () const {
		return mValue.load () ;
	}

	UNIT exchange (const UNIT &data) {
		return mValue.exchange (data) ;
	}

	UNIT compare_exchange (const UNIT &expect ,const UNIT &data) {
		UNIT ret = expect ;
		const auto r1x = mValue.compare_exchange_strong (ret ,data) ;
		if (r1x)
			ret = data ;
		return _MOVE_ (ret) ;
	}

	void store (const UNIT &data) {
		mValue.store (data) ;
	}

	UNIT increase () {
		const auto r1x = mValue.fetch_add (1) ;
		return UNIT (r1x + 1) ;
	}

	UNIT decrease () {
		const auto r1x = mValue.fetch_sub (1) ;
		return UNIT (r1x - 1) ;
	}

	UNIT addto (const UNIT &data) {
		const auto r1x = mValue.fetch_add (data) ;
		return UNIT (r1x + data) ;
	}

	UNIT subto (const UNIT &data) {
		const auto r1x = mValue.fetch_sub (data) ;
		return UNIT (r1x - data) ;
	}

	UNIT bandto (const UNIT &data) {
		const auto r1x = mValue.fetch_and (data) ;
		return UNIT (r1x & data) ;
	}

	UNIT borto (const UNIT &data) {
		const auto r1x = mValue.fetch_or (data) ;
		return UNIT (r1x | data) ;
	}

	void bxorto (const UNIT &data) {
		const auto r1x = mValue.fetch_xor (data) ;
		return UNIT (r1x ^ data) ;
	}
} ;

class AtomicVar {
private:
	using BASE_TYPE = BYTE_BASE_TYPE<VAR> ;

private:
	Atomic<BASE_TYPE> mValue ;

public:
	implicit AtomicVar () = default ;

	implicit AtomicVar (const VAR &that) {
		const auto r1x = _CAST_ (ARGV<BASE_TYPE>::ID ,that) ;
		const auto r2x = mValue.compare_exchange (0 ,r1x) ;
		_STATIC_UNUSED_ (r2x) ;
		_DEBUG_ASSERT_ (r2x == r1x) ;
	}

	VAR fetch () const {
		const auto r1x = mValue.fetch () ;
		return _CAST_ (ARGV<VAR>::ID ,r1x) ;
	}

	VAR exchange (const VAR &data) {
		const auto r1x = _CAST_ (ARGV<BASE_TYPE>::ID ,data) ;
		const auto r2x = mValue.exchange (r1x) ;
		return _CAST_ (ARGV<VAR>::ID ,r2x) ;
	}

	VAR compare_exchange (const VAR &expect ,const VAR &data) {
		const auto r1x = _CAST_ (ARGV<BASE_TYPE>::ID ,expect) ;
		const auto r2x = _CAST_ (ARGV<BASE_TYPE>::ID ,data) ;
		const auto r3x = mValue.compare_exchange (r1x ,r2x) ;
		return _CAST_ (ARGV<VAR>::ID ,r3x) ;
	}

	void store (const VAR &data) {
		const auto r1x = _CAST_ (ARGV<BASE_TYPE>::ID ,data) ;
		mValue.store (r1x) ;
	}

	VAR increase () {
		const auto r1x = mValue.increase () ;
		return _CAST_ (ARGV<VAR>::ID ,r1x) ;
	}

	VAR decrease () {
		const auto r1x = mValue.decrease () ;
		return _CAST_ (ARGV<VAR>::ID ,r1x) ;
	}

	void wait (const VAR &data) const {
		while (TRUE) {
			const auto r1x = fetch () ;
			if (r1x == data)
				break ;
			_STATIC_WARNING_ ("noop") ;
		}
	}
} ;

class AtomicPtr {
private:
	using BASE_TYPE = BYTE_BASE_TYPE<PTR<NONE>> ;

private:
	Atomic<BASE_TYPE> mValue ;

public:
	implicit AtomicPtr () = default ;

	implicit AtomicPtr (const PTR<NONE> &that) {
		const auto r1x = _ADDRESS_ (that) ;
		const auto r2x = _CAST_ (ARGV<BASE_TYPE>::ID ,r1x) ;
		const auto r3x = mValue.compare_exchange (0 ,r2x) ;
		_STATIC_UNUSED_ (r3x) ;
		_DEBUG_ASSERT_ (r3x == r2x) ;
	}

	PTR<NONE> fetch () const {
		const auto r1x = mValue.fetch () ;
		const auto r2x = _CAST_ (ARGV<VAR>::ID ,r1x) ;
		return _UNSAFE_POINTER_ (r2x) ;
	}

	PTR<NONE> exchange (const PTR<NONE> &data) {
		const auto r1x = _ADDRESS_ (data) ;
		const auto r2x = _CAST_ (ARGV<BASE_TYPE>::ID ,r1x) ;
		const auto r3x = mValue.exchange (r2x) ;
		const auto r4x = _CAST_ (ARGV<VAR>::ID ,r3x) ;
		return _UNSAFE_POINTER_ (r4x) ;
	}

	PTR<NONE> compare_exchange (const PTR<NONE> &expect ,const PTR<NONE> &data) {
		const auto r1x = _ADDRESS_ (expect) ;
		const auto r2x = _CAST_ (ARGV<BASE_TYPE>::ID ,r1x) ;
		const auto r3x = _ADDRESS_ (data) ;
		const auto r4x = _CAST_ (ARGV<BASE_TYPE>::ID ,r3x) ;
		const auto r5x = mValue.compare_exchange (r2x ,r4x) ;
		const auto r6x = _CAST_ (ARGV<VAR>::ID ,r5x) ;
		return _UNSAFE_POINTER_ (r6x) ;
	}

	void store (const PTR<NONE> &data) {
		const auto r1x = _ADDRESS_ (data) ;
		const auto r2x = _CAST_ (ARGV<BASE_TYPE>::ID ,r1x) ;
		mValue.store (r2x) ;
	}
} ;

template <class>
class StrongRef ;

class WeakRef final {
private:
	struct Private {
		class LatchCounter ;

		template <class>
		class ImplHolder ;
	} ;

	struct THIS_PACK {
		PTR<NONE> mOrigin ;
		AnyRef<> mHolder ;
		AtomicVar mStrongCounter ;
		AtomicVar mSoftCounter ;
	} ;

	class Holder :
		delegate public Interface {
	public:
		virtual PTR<THIS_PACK> strong_pointer () const = 0 ;
		virtual PTR<NONE> fast_pointer () const leftvalue = 0 ;
		virtual void weak_aquire () = 0 ;
		virtual void weak_release () = 0 ;
		virtual void strong_aquire () = 0 ;
		virtual void strong_release () = 0 ;
		virtual void soft_destroy () noexcept = 0 ;
		virtual void destroy () noexcept = 0 ;
	} ;

private:
	template <class>
	friend class StrongRef ;
	AtomicPtr mPointer ;
	mutable AtomicVar mLatch ;

public:
	implicit WeakRef () :
		delegate WeakRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	explicit WeakRef (const PTR<Holder> &pointer) :
		delegate WeakRef (ARGVP0) {
		if (pointer == NULL)
			return ;
		aquire (pointer) ;
		const auto r1x = safe_exchange (pointer) ;
		if (r1x == NULL)
			return ;
		release (r1x) ;
	}

	template <class _ARG1>
	implicit WeakRef (const StrongRef<_ARG1> &that) :
		delegate WeakRef (that.weak ()) {}

	implicit ~WeakRef () noexcept {
		const auto r1x = safe_exchange (NULL) ;
		if (r1x == NULL)
			return ;
		release (r1x) ;
	}

	implicit WeakRef (const WeakRef &that) :
		delegate WeakRef (that.share ()) {}

	inline WeakRef &operator= (const WeakRef &that) {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~WeakRef () ;
			new (this) WeakRef (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	implicit WeakRef (WeakRef &&that) noexcept :
		delegate WeakRef (ARGVP0) {
		const auto r1x = that.safe_exchange (NULL) ;
		const auto r2x = safe_exchange (r1x) ;
		if (r2x == NULL)
			return ;
		const auto r3x = that.safe_exchange (r2x) ;
		if (r3x == NULL)
			return ;
		release (r3x) ;
	}

	inline WeakRef &operator= (WeakRef &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~WeakRef () ;
			new (this) WeakRef (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	BOOL exist () const {
		const auto r1x = mPointer.fetch () ;
		if (r1x == NULL)
			return FALSE ;
		return TRUE ;
	}

	PTR<Holder> intrusive () const leftvalue {
		const auto r1x = mPointer.fetch () ;
		const auto r2x = _POINTER_CAST_ (ARGV<Holder>::ID ,r1x) ;
		return r2x ;
	}

	BOOL equal (const WeakRef &that) const {
		const auto r1x = mPointer.fetch () ;
		const auto r2x = that.mPointer.fetch () ;
		if (r1x != r2x)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const WeakRef &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const WeakRef &that) const {
		return !equal (that) ;
	}

	template <class _ARG1>
	BOOL equal (const StrongRef<_ARG1> &that) const {
		auto &r1x = _FORWARD_ (ARGV<DEPENDENT_TYPE<StrongRef<_ARG1> ,struct ANONYMOUS>>::ID ,that) ;
		const auto r2x = mPointer.fetch () ;
		const auto r3x = r1x.mPointer.fetch () ;
		if (r2x != r3x)
			return FALSE ;
		return TRUE ;
	}

	template <class _ARG1>
	inline BOOL operator== (const StrongRef<_ARG1> &that) const {
		return equal (that) ;
	}

	template <class _ARG1>
	inline BOOL operator!= (const StrongRef<_ARG1> &that) const {
		return !equal (that) ;
	}

	WeakRef share () const {
		using R1X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::LatchCounter ;
		ScopedGuard<R1X> ANONYMOUS (_CAST_ (ARGV<R1X>::ID ,mLatch)) ;
		const auto r1x = mPointer.fetch () ;
		const auto r2x = _POINTER_CAST_ (ARGV<Holder>::ID ,r1x) ;
		return WeakRef (r2x) ;
	}

	template <class _ARG1>
	StrongRef<_ARG1> strong (const ARGVF<_ARG1> &) const {
		using R1X = DEPENDENT_TYPE<StrongRef<_ARG1> ,struct ANONYMOUS> ;
		using R2X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::LatchCounter ;
		ScopedGuard<R2X> ANONYMOUS (_CAST_ (ARGV<R2X>::ID ,mLatch)) ;
		const auto r1x = mPointer.fetch () ;
		//@error: cast without any check if 'Holder' is 'ImplHolder<_ARG1>'
		const auto r2x = _POINTER_CAST_ (ARGV<Holder>::ID ,r1x) ;
		return R1X (r2x) ;
	}

private:
	explicit WeakRef (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mPointer (NULL) ,
		delegate mLatch (0) {}

	imports void aquire (const PTR<Holder> &pointer) {
		_DEBUG_ASSERT_ (pointer != NULL) ;
		DEREF[pointer].weak_aquire () ;
	}

	imports void release (const PTR<Holder> &pointer) {
		_DEBUG_ASSERT_ (pointer != NULL) ;
		DEREF[pointer].weak_release () ;
	}

	PTR<Holder> safe_exchange (const PTR<Holder> &pointer) {
		const auto r1x = mPointer.exchange (pointer) ;
		const auto r2x = _POINTER_CAST_ (ARGV<Holder>::ID ,r1x) ;
		if (r2x == NULL)
			return r2x ;
		mLatch.wait (0) ;
		return r2x ;
	}
} ;

class WeakRef::Private::LatchCounter :
	delegate private Wrapped<AtomicVar> {
private:
	using Wrapped<AtomicVar>::mSelf ;

public:
	void lock () {
		const auto r1x = mSelf.increase () ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x >= 1) ;
	}

	void unlock () {
		const auto r1x = mSelf.decrease () ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x >= 0) ;
	}
} ;

template <class UNIT>
class WeakRef::Private::ImplHolder :
	delegate public Holder {
private:
	PTR<THIS_PACK> mStrongPointer ;
	PTR<UNIT> mFaskPointer ;
	AtomicVar mWeakCounter ;

public:
	implicit ImplHolder () = delete ;

	explicit ImplHolder (const PTR<THIS_PACK> &strong_pointer_ ,const PTR<UNIT> &fast_pointer_) {
		mStrongPointer = strong_pointer_ ;
		mFaskPointer = fast_pointer_ ;
	}

	PTR<THIS_PACK> strong_pointer () const override {
		return mStrongPointer ;
	}

	PTR<NONE> fast_pointer () const leftvalue override {
		return mFaskPointer ;
	}

	void weak_aquire () override {
		const auto r1x = mWeakCounter.increase () ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x >= 1) ;
		if (r1x > 1)
			return ;
		const auto r2x = DEREF[mStrongPointer].mSoftCounter.increase () ;
		_STATIC_UNUSED_ (r2x) ;
		_DEBUG_ASSERT_ (r2x >= 1) ;
	}

	void weak_release () override {
		const auto r1x = mWeakCounter.decrease () ;
		if (r1x > 0)
			return ;
		if switch_once (TRUE) {
			const auto r2x = DEREF[mStrongPointer].mSoftCounter.decrease () ;
			if (r2x > 0)
				discard ;
			soft_destroy () ;
		}
		destroy () ;
	}

	void strong_aquire () override {
		_DEBUG_ASSERT_ (mWeakCounter.fetch () > 0) ;
		const auto r1x = DEREF[mStrongPointer].mStrongCounter.fetch () ;
		if (r1x < 0)
			return ;
		const auto r2x = DEREF[mStrongPointer].mStrongCounter.increase () ;
		_STATIC_UNUSED_ (r2x) ;
		_DEBUG_ASSERT_ (r2x >= 1) ;
		if (r2x > 1)
			return ;
		_DEBUG_ASSERT_ (DEREF[mStrongPointer].mHolder.exist ()) ;
	}

	void strong_release () override {
		_DEBUG_ASSERT_ (mWeakCounter.fetch () > 0) ;
		const auto r1x = DEREF[mStrongPointer].mStrongCounter.fetch () ;
		if (r1x < 0)
			return ;
		const auto r2x = DEREF[mStrongPointer].mStrongCounter.decrease () ;
		if (r2x > 0)
			return ;
		DEREF[mStrongPointer].mHolder = AnyRef<> () ;
		const auto r3x = DEREF[mStrongPointer].mStrongCounter.exchange (VAR_NONE) ;
		if (r3x <= 0)
			return ;
		_DEBUG_ASSERT_ (!DEREF[mStrongPointer].mHolder.exist ()) ;
	}

	void soft_destroy () noexcept override {
		const auto r1x = DEREF[mStrongPointer].mOrigin ;
		DEREF[mStrongPointer].~THIS_PACK () ;
		GlobalHeap::free (r1x) ;
		mStrongPointer = NULL ;
	}

	void destroy () noexcept override {
		const auto r1x = _FORWARD_ (ARGV<PTR<NONE>>::ID ,this) ;
		DEREF[this].~ImplHolder () ;
		GlobalHeap::free (r1x) ;
	}
} ;

class RecastInvokeProc :
	delegate private Wrapped<> {
public:
	template <class _ARG1 ,class _ARG2>
	imports PTR<_ARG1> invoke (const ARGVF<_ARG1> & ,const PTR<_ARG2> &pointer) {
		return template_recast (pointer ,ARGV<CAST_TRAITS_TYPE<_ARG1 ,_ARG2>>::ID ,ARGVPX) ;
	}

private:
	template <class _ARG1 ,class _ARG2 ,class = ENABLE_TYPE<IS_BASE_OF_HELP<_ARG2 ,_ARG1>>>
	imports PTR<_ARG2> template_recast (const PTR<_ARG1> &pointer ,const ARGVF<_ARG2> & ,const DEF<decltype (ARGVP3)> &) {
		return _FORWARD_ (ARGV<PTR<_ARG2>>::ID ,pointer) ;
	}

	template <class _ARG1 ,class _ARG2 ,class = ENABLE_TYPE<U::CONSTEXPR_AND<IS_BASE_OF_HELP<Interface ,_ARG1> ,IS_BASE_OF_HELP<Interface ,_ARG2>>>>
	imports PTR<_ARG2> template_recast (const PTR<_ARG1> &pointer ,const ARGVF<_ARG2> & ,const DEF<decltype (ARGVP2)> &) {
		//@warn: RTTI might be different across DLL
		return dynamic_cast<PTR<_ARG2>> (pointer) ;
	}

	template <class _ARG1 ,class _ARG2>
	imports PTR<_ARG2> template_recast (const PTR<_ARG1> &address ,const ARGVF<_ARG2> & ,const DEF<decltype (ARGVP1)> &) {
		return NULL ;
	}
} ;

template <class UNIT>
class StrongRef final {
private:
	using Holder = typename WeakRef::Holder ;
	using Private = typename WeakRef::Private ;

private:
	AtomicPtr mPointer ;
	mutable AtomicVar mLatch ;

public:
	implicit StrongRef () :
		delegate StrongRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	explicit StrongRef (const PTR<Holder> &pointer) :
		delegate StrongRef (ARGVP0) {
		if (pointer == NULL)
			return ;
		aquire (pointer) ;
		const auto r1x = safe_exchange (pointer) ;
		if (r1x == NULL)
			return ;
		release (pointer) ;
	}

	//@warn: circular reference ruins StrongRef
	template <class _ARG1 ,class = ENABLE_TYPE<IS_BASE_OF_HELP<UNIT ,_ARG1>>>
	implicit StrongRef (const StrongRef<_ARG1> &that) :
		delegate StrongRef (that.recast (ARGV<UNIT>::ID)) {
		_STATIC_WARNING_ ("noop") ;
	}

	implicit StrongRef (const WeakRef &that) :
		delegate StrongRef (that.strong (ARGV<UNIT>::ID)) {
		_STATIC_WARNING_ ("noop") ;
	}

	implicit ~StrongRef () noexcept {
		const auto r1x = safe_exchange (NULL) ;
		if (r1x == NULL)
			return ;
		release (r1x) ;
	}

	implicit StrongRef (const StrongRef &) = delete ;

	inline StrongRef &operator= (const StrongRef &) = delete ;

	implicit StrongRef (StrongRef &&that) noexcept :
		delegate StrongRef (ARGVP0) {
		const auto r1x = that.safe_exchange (NULL) ;
		const auto r2x = safe_exchange (r1x) ;
		if (r2x == NULL)
			return ;
		const auto r3x = that.safe_exchange (r2x) ;
		if (r3x == NULL)
			return ;
		release (r3x) ;
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
		const auto r1x = mPointer.fetch () ;
		if (r1x == NULL)
			return FALSE ;
		const auto r2x = _POINTER_CAST_ (ARGV<Holder>::ID ,r1x) ;
		const auto r3x = DEREF[r2x].strong_pointer () ;
		const auto r4x = DEREF[r3x].mStrongCounter.fetch () ;
		if (r4x <= 0)
			return FALSE ;
		return TRUE ;
	}

	UNIT &to () leftvalue {
		const auto r1x = mPointer.fetch () ;
		_DEBUG_ASSERT_ (r1x != NULL) ;
		const auto r2x = _POINTER_CAST_ (ARGV<Holder>::ID ,r1x) ;
		const auto r3x = DEREF[r2x].fast_pointer () ;
		const auto r4x = _POINTER_CAST_ (ARGV<UNIT>::ID ,r3x) ;
		return DEREF[r4x] ;
	}

	inline PTR<UNIT> operator-> () leftvalue {
		return DEPTR[self] ;
	}

	inline implicit operator UNIT & () leftvalue {
		return self ;
	}

	const UNIT &to () const leftvalue {
		const auto r1x = mPointer.fetch () ;
		_DEBUG_ASSERT_ (r1x != NULL) ;
		const auto r2x = _POINTER_CAST_ (ARGV<Holder>::ID ,r1x) ;
		const auto r3x = DEREF[r2x].fast_pointer () ;
		const auto r4x = _POINTER_CAST_ (ARGV<UNIT>::ID ,r3x) ;
		return DEREF[r4x] ;
	}

	inline PTR<const UNIT> operator-> () const leftvalue {
		return DEPTR[self] ;
	}

	inline implicit operator const UNIT & () const leftvalue {
		return self ;
	}

	BOOL equal (const StrongRef &that) const {
		const auto r1x = mPointer.fetch () ;
		const auto r2x = that.mPointer.fetch () ;
		if (r1x != r2x)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const StrongRef &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const StrongRef &that) const {
		return !equal (that) ;
	}

	BOOL equal (const WeakRef &that) const {
		return that.equal (DEREF[this]) ;
	}

	inline BOOL operator== (const WeakRef &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const WeakRef &that) const {
		return !equal (that) ;
	}

	StrongRef share () const {
		using R1X = typename Private::LatchCounter ;
		ScopedGuard<R1X> ANONYMOUS (_CAST_ (ARGV<R1X>::ID ,mLatch)) ;
		const auto r1x = mPointer.fetch () ;
		const auto r2x = _POINTER_CAST_ (ARGV<Holder>::ID ,r1x) ;
		return StrongRef (r2x) ;
	}

	template <class _ARG1>
	StrongRef<CAST_TRAITS_TYPE<_ARG1 ,UNIT>> recast (const ARGVF<_ARG1> &) const {
		using R1X = typename Private::LatchCounter ;
		using R2X = CAST_TRAITS_TYPE<_ARG1 ,UNIT> ;
		using R4X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<R2X> ;
		ScopedGuard<R1X> ANONYMOUS (_CAST_ (ARGV<R1X>::ID ,mLatch)) ;
		const auto r1x = mPointer.fetch () ;
		const auto r2x = _POINTER_CAST_ (ARGV<Holder>::ID ,r1x) ;
		if (r2x == NULL)
			return StrongRef<R2X> () ;
		const auto r3x = DEREF[r2x].fast_pointer () ;
		const auto r4x = _POINTER_CAST_ (ARGV<UNIT>::ID ,r3x) ;
		const auto r5x = RecastInvokeProc::invoke (ARGV<_ARG1>::ID ,r4x) ;
		_DYNAMIC_ASSERT_ (_EBOOL_ (r5x != NULL) == _EBOOL_ (r4x != NULL)) ;
		const auto r6x = DEREF[r2x].strong_pointer () ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<R4X>>::ID) ;
		ScopedBuild<R4X> ANONYMOUS (rax ,r6x ,r5x) ;
		const auto r7x = _POINTER_CAST_ (ARGV<R4X>::ID ,rax.self) ;
		StrongRef<R2X> ret = StrongRef<R2X> (r7x) ;
		rax = NULL ;
		return _MOVE_ (ret) ;
	}

	WeakRef weak () const {
		using R1X = typename Private::LatchCounter ;
		ScopedGuard<R1X> ANONYMOUS (_CAST_ (ARGV<R1X>::ID ,mLatch)) ;
		const auto r1x = mPointer.fetch () ;
		const auto r2x = _POINTER_CAST_ (ARGV<Holder>::ID ,r1x) ;
		return WeakRef (r2x) ;
	}

	template <class... _ARGS>
	imports StrongRef make (_ARGS &&...initval) {
		using R1X = typename WeakRef::THIS_PACK ;
		using R4X = DEPENDENT_TYPE<UNIT ,struct ANONYMOUS> ;
		using R3X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<R4X> ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<R1X>>::ID) ;
		ScopedBuild<R1X> ANONYMOUS (rax) ;
		const auto r1x = _POINTER_CAST_ (ARGV<R1X>::ID ,rax.self) ;
		DEREF[r1x].mOrigin = rax.self ;
		DEREF[r1x].mHolder = AnyRef<R4X>::make (_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) ;
		const auto r2x = DEPTR[DEREF[r1x].mHolder.rebind (ARGV<R4X>::ID).self] ;
		auto rbx = GlobalHeap::alloc (ARGV<TEMP<R3X>>::ID) ;
		ScopedBuild<R3X> ANONYMOUS (rbx ,r1x ,r2x) ;
		const auto r3x = _POINTER_CAST_ (ARGV<R3X>::ID ,rbx.self) ;
		StrongRef ret = StrongRef (r3x) ;
		rbx = NULL ;
		rax = NULL ;
		return _MOVE_ (ret) ;
	}

private:
	explicit StrongRef (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mPointer (NULL) ,
		delegate mLatch (0) {}

	imports void aquire (const PTR<Holder> &pointer) {
		_DEBUG_ASSERT_ (pointer != NULL) ;
		DEREF[pointer].weak_aquire () ;
		DEREF[pointer].strong_aquire () ;
	}

	imports void release (const PTR<Holder> &pointer) {
		_DEBUG_ASSERT_ (pointer != NULL) ;
		DEREF[pointer].strong_release () ;
		DEREF[pointer].weak_release () ;
	}

	PTR<Holder> safe_exchange (const PTR<Holder> &pointer) {
		const auto r1x = mPointer.exchange (pointer) ;
		const auto r2x = _POINTER_CAST_ (ARGV<Holder>::ID ,r1x) ;
		if (r2x == NULL)
			return r2x ;
		mLatch.wait (0) ;
		return r2x ;
	}
} ;

class GlobalRuntime ;

template <class UNIT>
class Later :
	delegate private Proxy {
private:
	struct THIS_PACK {
		FLAG mTag ;
		Function<UNIT ()> mOperator ;
		PTR<Later> mNode ;
		PTR<THIS_PACK> mPrev ;
		PTR<THIS_PACK> mNext ;
	} ;

private:
	SharedRef<THIS_PACK> mThis ;
	UniqueRef<SharedRef<THIS_PACK>> mKeep ;

public:
	implicit Later () = delete ;

	explicit Later (const FLAG &tag) {
		if switch_once (TRUE) {
			const auto r1x = find (tag) ;
			if (r1x == NULL)
				discard ;
			mThis = DEREF[DEREF[r1x].mNode].mThis ;
		}
	}

	template <class _ARG1 ,class = ENABLE_TYPE<U::CONSTEXPR_NOT<IS_PLACEHOLDER_HELP<_ARG1>>>>
	explicit Later (const FLAG &tag ,_ARG1 &&that) {
		mKeep = UniqueRef<SharedRef<THIS_PACK>> ([&] (SharedRef<THIS_PACK> &me) {
			me = SharedRef<THIS_PACK>::make () ;
			me->mNode = this ;
			link (DEPTR[me.self]) ;
		} ,[] (SharedRef<THIS_PACK> &me) {
			me->mNode = NULL ;
			unlink (DEPTR[me.self]) ;
		}) ;
		mThis = mKeep.self ;
		mThis->mTag = tag ;
		mThis->mOperator = Function<UNIT ()> (_FORWARD_ (ARGV<_ARG1>::ID ,that)) ;
	}

	UNIT invoke () const {
		_DYNAMIC_ASSERT_ (mThis.exist ()) ;
		return mThis->mOperator () ;
	}

	inline UNIT operator() () const {
		return invoke () ;
	}

private:
	imports FLAG thread_tid () {
		using R1X = DEPENDENT_TYPE<GlobalRuntime ,struct ANONYMOUS> ;
		return _CACHE_ ([&] () {
			return R1X::thread_tid () ;
		}) ;
	}

	imports PTR<THIS_PACK> &first () {
		using R1X = DEPENDENT_TYPE<GlobalRuntime ,struct ANONYMOUS> ;
		auto &r1x = _CACHE_ ([&] () {
			return SharedRef<PTR<THIS_PACK>>::make (NULL) ;
		}) ;
		_DYNAMIC_ASSERT_ (thread_tid () == R1X::thread_tid ()) ;
		return r1x.self ;
	}

	imports PTR<THIS_PACK> &last () {
		using R1X = DEPENDENT_TYPE<GlobalRuntime ,struct ANONYMOUS> ;
		auto &r1x = _CACHE_ ([&] () {
			return SharedRef<PTR<THIS_PACK>>::make (NULL) ;
		}) ;
		_DYNAMIC_ASSERT_ (thread_tid () == R1X::thread_tid ()) ;
		return r1x.self ;
	}

	imports PTR<THIS_PACK> find (const FLAG &tag) {
		PTR<THIS_PACK> ret = last () ;
		while (TRUE) {
			if (ret == NULL)
				break ;
			if (DEREF[ret].mTag == tag)
				break ;
			ret = DEREF[ret].mPrev ;
		}
		return _MOVE_ (ret) ;
	}

	imports void link (const PTR<THIS_PACK> &curr) {
		DEREF[curr].mPrev = last () ;
		DEREF[curr].mNext = NULL ;
		auto &r1x = _CALL_ ([&] () {
			if (DEREF[curr].mPrev != NULL)
				return _BYREF_ (DEREF[DEREF[curr].mPrev].mNext) ;
			return _BYREF_ (first ()) ;
		}).self ;
		r1x = curr ;
		last () = curr ;
	}

	imports void unlink (const PTR<THIS_PACK> &curr) {
		prev_next (curr) = DEREF[curr].mNext ;
		next_prev (curr) = DEREF[curr].mPrev ;
		DEREF[curr].mPrev = NULL ;
		DEREF[curr].mNext = NULL ;
	}

	imports PTR<THIS_PACK> &prev_next (const PTR<THIS_PACK> &curr) {
		if (DEREF[curr].mPrev == NULL)
			return first () ;
		return DEREF[DEREF[curr].mPrev].mNext ;
	}

	imports PTR<THIS_PACK> &next_prev (const PTR<THIS_PACK> &curr) {
		if (DEREF[curr].mNext == NULL)
			return last () ;
		return DEREF[DEREF[curr].mNext].mPrev ;
	}
} ;

class MemoryPool {
private:
	struct Private {
		template <class>
		class ImplHolder ;

		class HugeHolder ;
	} ;

	struct HEADER ;

	class Holder :
		delegate public Interface {
	public:
		virtual void clear () noexcept = 0 ;
		virtual LENGTH size () const = 0 ;
		virtual LENGTH length () const = 0 ;
		virtual PTR<HEADER> alloc (const LENGTH &len) = 0 ;
		virtual void free (const PTR<HEADER> &address) noexcept = 0 ;
		virtual void clean () noexcept = 0 ;
		virtual void soft_destroy () noexcept = 0 ;
	} ;

	struct HEADER {
		alignas (8) PTR<Holder> mFrom ;
		alignas (8) PTR<struct HEADER> mCurr ;
	} ;

	struct THIS_PACK {
		AutoBuffer<StrongRef<Holder>> mPool ;
	} ;

private:
	SharedRef<THIS_PACK> mThis ;
	UniqueRef<SharedRef<THIS_PACK>> mKeep ;

public:
	implicit MemoryPool () ;

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
	template <class _ARG1>
	PTR<_ARG1> alloc (const ARGVF<_ARG1> &) {
		_STATIC_ASSERT_ (IS_TRIVIAL_HELP<_ARG1>::compile ()) ;
		const auto r1x = _ALIGNOF_ (_ARG1) - _ALIGNOF_ (HEADER) ;
		const auto r2x = VAR_ZERO ;
		const auto r3x = _MAX_ (r1x ,r2x) + _SIZEOF_ (_ARG1) ;
		const auto r4x = (r3x - 1) / 8 ;
		const auto r5x = _SIZEOF_ (HEADER) ;
		INDEX ix = _MIN_ (r4x ,r5x) ;
		const auto r6x = mThis->mPool[ix]->alloc (r3x) ;
		const auto r7x = _ADDRESS_ (r6x) + r5x ;
		const auto r8x = _ALIGNAS_ (r7x ,_ALIGNOF_ (_ARG1)) ;
		const auto r9x = r8x - r5x ;
		const auto r10x = _POINTER_CAST_ (ARGV<HEADER>::ID ,_UNSAFE_POINTER_ (r9x)) ;
		DEREF[r10x].mFrom = DEPTR[mThis->mPool[ix].self] ;
		DEREF[r10x].mCurr = r6x ;
		const auto r11x = _POINTER_CAST_ (ARGV<_ARG1>::ID ,r8x) ;
		return r11x ;
	}

	//@warn: held by RAII to avoid static-memory-leaks
	template <class _ARG1>
	PTR<ARR<_ARG1>> alloc (const ARGVF<_ARG1> & ,const LENGTH &len) {
		_STATIC_ASSERT_ (IS_TRIVIAL_HELP<_ARG1>::compile ()) ;
		const auto r1x = _ALIGNOF_ (_ARG1) - _ALIGNOF_ (HEADER) ;
		const auto r2x = VAR_ZERO ;
		const auto r3x = _MAX_ (r1x ,r2x) + len * _SIZEOF_ (_ARG1) ;
		_DEBUG_ASSERT_ (r3x > 0) ;
		const auto r4x = (r3x - 1) / 8 ;
		const auto r5x = _SIZEOF_ (HEADER) ;
		INDEX ix = _MIN_ (r4x ,r5x) ;
		const auto r6x = mThis->mPool[ix]->alloc (r3x) ;
		const auto r7x = _ADDRESS_ (r6x) + r5x ;
		const auto r8x = _ALIGNAS_ (r7x ,_ALIGNOF_ (_ARG1)) ;
		const auto r9x = r8x - r5x ;
		const auto r10x = _POINTER_CAST_ (ARGV<HEADER>::ID ,_UNSAFE_POINTER_ (r9x)) ;
		DEREF[r10x].mFrom = DEPTR[mThis->mPool[ix].self] ;
		DEREF[r10x].mCurr = r6x ;
		const auto r11x = _POINTER_CAST_ (ARGV<ARR<_ARG1>>::ID ,r8x) ;
		return r11x ;
	}

	template <class _ARG1>
	void free (const PTR<_ARG1> &address) noexcept {
		_STATIC_ASSERT_ (IS_TRIVIAL_HELP<REMOVE_ARRAY_TYPE<_ARG1>>::compile ()) ;
		const auto r1x = _ADDRESS_ (address) - _SIZEOF_ (HEADER) ;
		const auto r2x = _POINTER_CAST_ (ARGV<HEADER>::ID ,r1x) ;
		const auto r3x = _CALL_ ([&] () {
			for (auto &&i : _RANGE_ (0 ,mThis->mPool.size ())) {
				if (DEPTR[mThis->mPool[i].self] == DEREF[r2x].mFrom)
					return i ;
			}
			return VAR_NONE ;
		}) ;
		_DEBUG_ASSERT_ (r3x != VAR_NONE) ;
		mThis->mPool[r3x]->free (DEREF[r2x].mCurr) ;
	}

	void clean () {
		for (auto &&i : _RANGE_ (0 ,mThis->mPool.size ()))
			mThis->mPool[i]->clean () ;
	}

private:
	explicit MemoryPool (const DEF<decltype (ARGVP0)> &) {
		mKeep = UniqueRef<SharedRef<THIS_PACK>> ([&] (SharedRef<THIS_PACK> &me) {
			me = SharedRef<THIS_PACK>::make () ;
		} ,[] (SharedRef<THIS_PACK> &me) {
			for (auto &&i : _RANGE_ (0 ,me->mPool.size ()))
				me->mPool[i]->clear () ;
			me->mPool = AutoBuffer<StrongRef<Holder>> () ;
		}) ;
		mThis = mKeep.self ;
	}
} ;

template <class SIZE>
class MemoryPool::Private::ImplHolder :
	delegate public Holder {
private:
	_STATIC_ASSERT_ (U::CONSTEXPR_COMPR_GT<SIZE ,ZERO>::compile ()) ;

	using DEFAULT_SMPAGE_SIZE = ARGC<4096> ;

	struct BLOCK_NODE {
		PTR<struct BLOCK_NODE> mNext ;
		HEADER mFlexData ;
	} ;

	struct CHUNK_NODE {
		PTR<NONE> mOrigin ;
		PTR<struct CHUNK_NODE> mPrev ;
		PTR<struct CHUNK_NODE> mNext ;
		LENGTH mCount ;
		HEADER mFlexData ;
	} ;

private:
	PTR<CHUNK_NODE> mRoot ;
	PTR<CHUNK_NODE> mRecycle ;
	PTR<BLOCK_NODE> mFree ;
	LENGTH mSize ;
	LENGTH mLength ;
	BLOCK_NODE mUsedNode ;

public:
	implicit ImplHolder () {
		mRoot = NULL ;
		mRecycle = NULL ;
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
			mRecycle = mRoot ;
			mRoot = DEREF[mRoot].mNext ;
			soft_destroy () ;
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
		const auto r1x = _ALIGNAS_ (_SIZEOF_ (BLOCK_NODE) + SIZE::compile () ,_ALIGNOF_ (BLOCK_NODE)) ;
		const auto r2x = _ALIGNOF_ (CHUNK_NODE) - 1 + _SIZEOF_ (CHUNK_NODE) + _ALIGNOF_ (BLOCK_NODE) - 1 ;
		const auto r3x = (DEFAULT_SMPAGE_SIZE::compile () - r2x) / r1x ;
		auto rax = GlobalHeap::alloc (ARGV<BYTE>::ID ,DEFAULT_SMPAGE_SIZE::compile ()) ;
		const auto r4x = _ADDRESS_ (rax.self) ;
		const auto r5x = _ALIGNAS_ (r4x ,_ALIGNOF_ (CHUNK_NODE)) ;
		const auto r6x = _POINTER_CAST_ (ARGV<CHUNK_NODE>::ID ,_UNSAFE_POINTER_ (r5x)) ;
		DEREF[r6x].mOrigin = rax.self ;
		DEREF[r6x].mPrev = NULL ;
		DEREF[r6x].mNext = mRoot ;
		DEREF[r6x].mCount = r3x ;
		if (mRoot != NULL)
			DEREF[mRoot].mPrev = r6x ;
		mRoot = r6x ;
		mSize += r3x * SIZE::compile () ;
		const auto r7x = _ALIGNAS_ (r5x + _SIZEOF_ (CHUNK_NODE) ,_ALIGNOF_ (BLOCK_NODE)) ;
		for (auto &&i : _RANGE_ (0 ,DEREF[mRoot].mCount)) {
			const auto r8x = r7x + i * r1x ;
			const auto r9x = _POINTER_CAST_ (ARGV<BLOCK_NODE>::ID ,_UNSAFE_POINTER_ (r8x)) ;
			DEREF[r9x].mNext = mFree ;
			mFree = r9x ;
		}
		rax = NULL ;
	}

	PTR<HEADER> alloc (const LENGTH &len) override {
		_DEBUG_ASSERT_ (len <= SIZE::compile ()) ;
		reserve () ;
		const auto r1x = mFree ;
		mFree = DEREF[r1x].mNext ;
		mLength += SIZE::compile () ;
		DEREF[r1x].mNext = DEPTR[mUsedNode] ;
		return DEPTR[DEREF[r1x].mFlexData] ;
	}

	void free (const PTR<HEADER> &address) noexcept override {
		_DEBUG_ASSERT_ (address != NULL) ;
		auto &r1x = _OFFSET_ (&BLOCK_NODE::mFlexData ,DEREF[address]) ;
		_DEBUG_ASSERT_ (r1x.mNext == DEPTR[mUsedNode]) ;
		r1x.mNext = mFree ;
		mFree = DEPTR[r1x] ;
		mLength -= SIZE::compile () ;
	}

	void clean () noexcept override {
		if (mSize == mLength)
			return ;
		auto rax = mRoot ;
		while (TRUE) {
			if (rax == NULL)
				break ;
			mRecycle = rax ;
			rax = DEREF[rax].mNext ;
			if switch_once (TRUE) {
				if (!empty_node (mRecycle))
					discard ;
				auto &r1x = _CALL_ ([&] () {
					if (DEREF[mRecycle].mPrev != NULL)
						return _BYREF_ (DEREF[DEREF[mRecycle].mPrev].mNext) ;
					return _BYREF_ (mRoot) ;
				}).self ;
				r1x = DEREF[mRecycle].mNext ;
				if (DEREF[mRecycle].mNext != NULL)
					DEREF[DEREF[mRecycle].mNext].mPrev = DEREF[mRecycle].mPrev ;
				mSize -= DEREF[mRecycle].mCount * SIZE::compile () ;
				soft_destroy () ;
			}
		}
	}

	void soft_destroy () noexcept override {
		_STATIC_ASSERT_ (IS_TRIVIAL_HELP<BLOCK_NODE>::compile ()) ;
		_STATIC_ASSERT_ (IS_TRIVIAL_HELP<CHUNK_NODE>::compile ()) ;
		const auto r1x = DEREF[mRecycle].mOrigin ;
		GlobalHeap::free (r1x) ;
		mRecycle = NULL ;
	}

private:
	BOOL empty_node (const PTR<const CHUNK_NODE> &node) const {
		const auto r1x = _ALIGNAS_ (_SIZEOF_ (BLOCK_NODE) + SIZE::compile () ,_ALIGNOF_ (BLOCK_NODE)) ;
		const auto r2x = _ADDRESS_ (node) + _SIZEOF_ (CHUNK_NODE) ;
		const auto r3x = _ALIGNAS_ (r2x ,_ALIGNOF_ (BLOCK_NODE)) ;
		for (auto &&i : _RANGE_ (0 ,DEREF[node].mCount)) {
			const auto r4x = r3x + i * r1x ;
			const auto r5x = _POINTER_CAST_ (ARGV<BLOCK_NODE>::ID ,_UNSAFE_POINTER_ (r4x)) ;
			if (DEREF[r5x].mNext == DEPTR[mUsedNode])
				return FALSE ;
		}
		return TRUE ;
	}
} ;

class MemoryPool::Private::HugeHolder :
	delegate public Holder {
private:
	struct FBLOCK_NODE {
		PTR<NONE> mOrigin ;
		PTR<struct FBLOCK_NODE> mPrev ;
		PTR<struct FBLOCK_NODE> mNext ;
		LENGTH mCount ;
		HEADER mFlexData ;
	} ;

private:
	PTR<FBLOCK_NODE> mRoot ;
	PTR<FBLOCK_NODE> mRecycle ;
	LENGTH mSize ;
	LENGTH mLength ;

public:
	implicit HugeHolder () {
		mRoot = NULL ;
		mRecycle = NULL ;
		mSize = 0 ;
		mLength = 0 ;
	}

	void clear () noexcept override {
		if (mRoot == NULL)
			return ;
		while (TRUE) {
			if (mRoot == NULL)
				break ;
			mRecycle = mRoot ;
			mRoot = DEREF[mRoot].mNext ;
			soft_destroy () ;
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

	PTR<HEADER> alloc (const LENGTH &len) override {
		const auto r1x = _ALIGNAS_ (len ,_ALIGNOF_ (FBLOCK_NODE)) ;
		const auto r2x = _ALIGNOF_ (FBLOCK_NODE) - 1 + _SIZEOF_ (FBLOCK_NODE) + r1x ;
		auto rax = GlobalHeap::alloc (ARGV<BYTE>::ID ,r2x) ;
		const auto r3x = _ADDRESS_ (rax.self) ;
		const auto r4x = _ALIGNAS_ (r3x ,_ALIGNOF_ (FBLOCK_NODE)) ;
		const auto r5x = _POINTER_CAST_ (ARGV<FBLOCK_NODE>::ID ,_UNSAFE_POINTER_ (r4x)) ;
		DEREF[r5x].mOrigin = rax.self ;
		DEREF[r5x].mPrev = NULL ;
		DEREF[r5x].mNext = mRoot ;
		DEREF[r5x].mCount = r1x ;
		if (mRoot != NULL)
			DEREF[mRoot].mPrev = r5x ;
		mRoot = r5x ;
		mSize += DEREF[r5x].mCount ;
		mLength += DEREF[r5x].mCount ;
		rax = NULL ;
		return DEPTR[DEREF[r5x].mFlexData] ;
	}

	void free (const PTR<HEADER> &address) noexcept override {
		_DEBUG_ASSERT_ (address != NULL) ;
		auto &r1x = _OFFSET_ (&FBLOCK_NODE::mFlexData ,DEREF[address]) ;
		mRecycle = DEPTR[r1x] ;
		if switch_once (TRUE) {
			auto &r2x = _CALL_ ([&] () {
				if (r1x.mPrev != NULL)
					return _BYREF_ (DEREF[r1x.mPrev].mNext) ;
				return _BYREF_ (mRoot) ;
			}).self ;
			r2x = r1x.mNext ;
			if (r1x.mNext != NULL)
				DEREF[r1x.mNext].mPrev = r1x.mPrev ;
			mSize -= r1x.mCount ;
			mLength -= r1x.mCount ;
			soft_destroy () ;
		}
	}

	void clean () noexcept override {
		_STATIC_WARNING_ ("noop") ;
	}

	void soft_destroy () noexcept override {
		_STATIC_ASSERT_ (IS_TRIVIAL_HELP<FBLOCK_NODE>::compile ()) ;
		const auto r1x = DEREF[mRecycle].mOrigin ;
		GlobalHeap::free (r1x) ;
		mRecycle = NULL ;
	}
} ;

inline exports MemoryPool::MemoryPool () :
	delegate MemoryPool (ARGVP0) {
	using R1X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<ARGC<8>> ;
	using R2X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<ARGC<16>> ;
	using R3X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<ARGC<24>> ;
	using R4X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<ARGC<32>> ;
	using R5X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<ARGC<40>> ;
	using R6X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<ARGC<48>> ;
	using R7X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<ARGC<56>> ;
	using R8X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<ARGC<64>> ;
	using R9X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<ARGC<72>> ;
	using R10X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<ARGC<80>> ;
	using R11X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<ARGC<88>> ;
	using R12X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<ARGC<96>> ;
	using R13X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<ARGC<104>> ;
	using R14X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<ARGC<112>> ;
	using R15X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<ARGC<120>> ;
	using R16X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<ARGC<128>> ;
	using R17X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::HugeHolder ;
	mThis->mPool = AutoBuffer<StrongRef<Holder>> (17) ;
	mThis->mPool[0] = StrongRef<R1X>::make () ;
	mThis->mPool[1] = StrongRef<R2X>::make () ;
	mThis->mPool[2] = StrongRef<R3X>::make () ;
	mThis->mPool[3] = StrongRef<R4X>::make () ;
	mThis->mPool[4] = StrongRef<R5X>::make () ;
	mThis->mPool[5] = StrongRef<R6X>::make () ;
	mThis->mPool[6] = StrongRef<R7X>::make () ;
	mThis->mPool[7] = StrongRef<R8X>::make () ;
	mThis->mPool[8] = StrongRef<R9X>::make () ;
	mThis->mPool[9] = StrongRef<R10X>::make () ;
	mThis->mPool[10] = StrongRef<R11X>::make () ;
	mThis->mPool[11] = StrongRef<R12X>::make () ;
	mThis->mPool[12] = StrongRef<R13X>::make () ;
	mThis->mPool[13] = StrongRef<R14X>::make () ;
	mThis->mPool[14] = StrongRef<R15X>::make () ;
	mThis->mPool[15] = StrongRef<R16X>::make () ;
	mThis->mPool[16] = StrongRef<R17X>::make () ;
}

class Object ;

class ObjectMetadata ;

class Objective :
	delegate public Interface {
public:
	virtual const ObjectMetadata &metadata () const leftvalue = 0 ;
	virtual const WeakRef &weak_of_this () const leftvalue = 0 ;
	virtual StrongRef<Object> clone () const = 0 ;
} ;

class Object :
	delegate public Objective {
private:
	WeakRef mWeakOfThis ;

public:
	implicit Object () = default ;

	const ObjectMetadata &metadata () const leftvalue override {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return _NULL_ (ARGV<ObjectMetadata>::ID) ;
	}

	const WeakRef &weak_of_this () const leftvalue override {
		return mWeakOfThis ;
	}

	StrongRef<Object> clone () const override {
		return StrongRef<Object> () ;
	}
} ;

class ObjectMetadata {
private:
	TYPEABI mTypeABI ;
	FLAG mTypeMID ;
	Function<void (PTR<NONE>)> mConstrutor ;
	Function<void (PTR<NONE>)> mDestructor ;

public:
	implicit ObjectMetadata () = default ;

	template <class _ARG1>
	explicit ObjectMetadata (const ARGVF<_ARG1> &) {
		_STATIC_ASSERT_ (IS_SAME_HELP<REMOVE_CVR_TYPE<_ARG1> ,_ARG1>::compile ()) ;
		mTypeABI = _TYPEABI_ (ARGV<_ARG1>::ID) ;
		mTypeMID = _TYPEMID_ (ARGV<_ARG1>::ID) ;
		mConstrutor = Function<void (PTR<NONE>)> ([] (const PTR<NONE> &address) {
			const auto r1x = _POINTER_CAST_ (ARGV<TEMP<_ARG1>>::ID ,address) ;
			_CREATE_ (r1x) ;
		}) ;
		mDestructor = Function<void (PTR<NONE>)> ([] (const PTR<NONE> &address) {
			const auto r1x = _POINTER_CAST_ (ARGV<TEMP<_ARG1>>::ID ,address) ;
			_DESTROY_ (r1x) ;
		}) ;
	}
} ;

template <class UNIT>
class ObjectVirtual :
	delegate public virtual Object {
public:
	implicit ObjectVirtual () = default ;

	const ObjectMetadata &metadata () const leftvalue override {
		return _CACHE_ ([&] () {
			return ObjectMetadata (ARGV<REMOVE_CVR_TYPE<UNIT>>::ID) ;
		}) ;
	}
} ;

template <class UNIT ,class CONT>
class Serializer {
private:
	struct Private {
		class Member ;

		template <class...>
		class ImplHolder ;
	} ;

	class Holder :
		delegate public Interface {
	public:
		virtual void compute_visit (UNIT &visitor ,CONT &context_) const = 0 ;
	} ;

private:
	StrongRef<Holder> mThis ;

public:
	implicit Serializer () = default ;

	template <class... _ARGS>
	explicit Serializer (const ARGVF<ARGVS<_ARGS...>> &) {
		using R1X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<_ARGS...> ;
		_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<_ARGS...>) > 0) ;
		mThis = StrongRef<R1X>::make (ARGV<ARGVS<_ARGS...>>::ID) ;
	}

	template <class _RET = REMOVE_CVR_TYPE<typename Private::Member>>
	inline _RET operator() (PhanRef<CONT> &&context_) const {
		using R1X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::Member ;
		return R1X (PhanRef<const Serializer>::make (DEREF[this]) ,_MOVE_ (context_)) ;
	}
} ;

template <class UNIT ,class CONT>
class Serializer<UNIT ,CONT>::Private::Member :
	delegate private Proxy {
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
		mBase->mThis->compute_visit (visitor ,mContext) ;
	}
} ;

template <class UNIT ,class CONT>
template <class... UNITS_>
class Serializer<UNIT ,CONT>::Private::ImplHolder :
	delegate public Holder {
public:
	implicit ImplHolder () = delete ;

	explicit ImplHolder (const ARGVF<ARGVS<UNITS_...>> &) {
		_STATIC_WARNING_ ("noop") ;
	}

	void compute_visit (UNIT &visitor ,CONT &context_) const override {
		template_visit (visitor ,context_ ,ARGV<ARGVS<UNITS_...>>::ID) ;
	}

private:
	void template_visit (UNIT &visitor ,CONT &context_ ,const ARGVF<ARGVS<>> &) const {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1>
	void template_visit (UNIT &visitor ,CONT &context_ ,const ARGVF<_ARG1> &) const {
		using R1X = PARAMS_ONE_TYPE<_ARG1> ;
		using R2X = PARAMS_REST_TYPE<_ARG1> ;
		auto &r1x = R1X::value (context_) ;
		visitor.visit (r1x) ;
		template_visit (visitor ,context_ ,ARGV<R2X>::ID) ;
	}
} ;

template <class>
class GlobalStatic ;

template <class UNIT>
class Singleton :
	delegate private Proxy {
private:
	_STATIC_ASSERT_ (IS_CLASS_HELP<UNIT>::compile ()) ;

	struct THIS_PACK {
		UNIT mValue ;

		template <class... _ARGS>
		explicit THIS_PACK (const DEF<decltype (ARGVP0)> & ,_ARGS &&...initval) :
			delegate mValue (_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) {}
	} ;

private:
	friend GlobalStatic<Singleton> ;
	StrongRef<THIS_PACK> mThis ;

public:
	//@warn: static instance across DLL ruins Singleton
	imports UNIT &instance () {
		using R1X = DEPENDENT_TYPE<GlobalStatic<Singleton<UNIT>> ,struct ANONYMOUS> ;
		return R1X::unique () ;
	}

private:
	implicit Singleton () {
		mThis = StrongRef<THIS_PACK>::make (ARGVP0 ,ARGV<Singleton>::ID) ;
	}

	UNIT &to () leftvalue {
		return mThis->mValue ;
	}

	inline implicit operator UNIT & () leftvalue {
		return self ;
	}
} ;
} ;