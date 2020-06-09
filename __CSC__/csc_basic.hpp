#pragma once

#ifndef __CSC_BASIC__
#define __CSC_BASIC__
#endif

#include "csc.hpp"
#include "csc_core.hpp"

namespace CSC {
class BasicProc
	:private Wrapped<void> {
public:
	template <class _ARG1>
	imports BOOL mem_equal (const ARR<_ARG1> &src1 ,const ARR<_ARG1> &src2 ,const LENGTH &len) ;

	template <class _ARG1>
	imports FLAG mem_compr (const ARR<_ARG1> &src1 ,const ARR<_ARG1> &src2 ,const LENGTH &len) ;

	template <class _ARG1>
	imports FLAG mem_hash (const ARR<_ARG1> &src ,const LENGTH &len) ;

	template <class _ARG1>
	imports FLAG mem_crc32 (const ARR<_ARG1> &src ,const LENGTH &len) ;

	template <class _ARG1>
	imports INDEX mem_chr (const ARR<_ARG1> &src ,const LENGTH &len ,const _ARG1 &val) ;

	template <class _ARG1>
	imports INDEX mem_rchr (const ARR<_ARG1> &src ,const LENGTH &len ,const _ARG1 &val) ;

	template <class _ARG1>
	imports void mem_copy (ARR<_ARG1> &dst ,const ARR<_ARG1> &src ,const LENGTH &len) ;

	template <class _ARG1>
	imports void mem_rcopy (ARR<_ARG1> &dst ,const ARR<_ARG1> &src ,const LENGTH &len) ;

	template <class _ARG1>
	imports void mem_move (ARR<_ARG1> &dst1 ,ARR<_ARG1> &dst2 ,const LENGTH &len) ;

	template <class _ARG1>
	imports void mem_swap (ARR<_ARG1> &dst1 ,ARR<_ARG1> &dst2 ,const LENGTH &len) ;

	template <class _ARG1>
	imports void mem_fill (ARR<_ARG1> &dst ,const LENGTH &len ,const _ARG1 &val) ;
} ;

template <class _ARG1>
inline exports BOOL BasicProc::mem_equal (const ARR<_ARG1> &src1 ,const ARR<_ARG1> &src2 ,const LENGTH &len) {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
	_DEBUG_ASSERT_ (len >= 0) ;
	if (src1 == src2)
		return TRUE ;
	for (auto &&i : _RANGE_ (0 ,len))
		if (!(src1[i] == src2[i]))
			return FALSE ;
	return TRUE ;
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
}

namespace U {
struct OPERATOR_COMPR {
	template <class _ARG1>
	imports FLAG template_compr (const _ARG1 &lhs ,const _ARG1 &rhs ,const ARGV<ENABLE_TYPE<stl::is_same<DEF<decltype (_NULL_<const REMOVE_REFERENCE_TYPE<_ARG1>> ().compr (_NULL_<const REMOVE_REFERENCE_TYPE<_ARG1>> ()))> ,FLAG>::value>> & ,const DEF<decltype (ARGVP3)> &) {
		return lhs.compr (rhs) ;
	}

	template <class _ARG1>
	imports FLAG template_compr (const _ARG1 &lhs ,const _ARG1 &rhs ,const ARGV<ENABLE_TYPE<stl::is_same<DEF<decltype (_NULL_<const REMOVE_REFERENCE_TYPE<_ARG1>> () < _NULL_<const REMOVE_REFERENCE_TYPE<_ARG1>> ())> ,BOOL>::value>> & ,const DEF<decltype (ARGVP2)> &) {
		if (lhs < rhs)
			return FLAG (-1) ;
		if (rhs < lhs)
			return FLAG (+1) ;
		return FLAG (0) ;
	}

	template <class _ARG1>
	imports FLAG template_compr (const _ARG1 &lhs ,const _ARG1 &rhs ,const ARGV<ENABLE_TYPE<stl::is_pod<_ARG1>::value>> & ,const DEF<decltype (ARGVP1)> &) {
		return BasicProc::mem_compr (PTRTOARR[_CAST_ (_NULL_<ARGV<BYTE[_SIZEOF_ (_ARG1)]>> () ,lhs)] ,PTRTOARR[_CAST_ (_NULL_<ARGV<BYTE[_SIZEOF_ (_ARG1)]>> () ,rhs)] ,_SIZEOF_ (_ARG1)) ;
	}

	template <class _ARG1>
	imports FLAG invoke (const _ARG1 &lhs ,const _ARG1 &rhs) {
		return template_compr (lhs ,rhs ,ARGVPX ,ARGVP9) ;
	}
} ;
} ;

template <class _ARG1>
inline exports FLAG BasicProc::mem_compr (const ARR<_ARG1> &src1 ,const ARR<_ARG1> &src2 ,const LENGTH &len) {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
	_DEBUG_ASSERT_ (len >= 0) ;
	if (src1 == src2)
		return FLAG (0) ;
	for (auto &&i : _RANGE_ (0 ,len)) {
		const auto r1x = U::OPERATOR_COMPR::invoke (src1[i] ,src2[i]) ;
		if (r1x != 0)
			return r1x ;
	}
	return FLAG (0) ;
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
}

namespace U {
struct OPERATOR_HASH {
	template <class _ARG1>
	imports FLAG template_hash (const _ARG1 &self_ ,const ARGV<ENABLE_TYPE<stl::is_same<DEF<decltype (_NULL_<const REMOVE_REFERENCE_TYPE<_ARG1>> ().hash ())> ,FLAG>::value>> & ,const DEF<decltype (ARGVP3)> &) {
		return self_.hash () ;
	}

	template <class _ARG1>
	imports FLAG template_hash (const _ARG1 &self_ ,const ARGV<ENABLE_TYPE<stl::is_integral<_ARG1>::value>> & ,const DEF<decltype (ARGVP2)> &) {
		return FLAG (self_) ;
	}

	template <class _ARG1>
	imports FLAG template_hash (const _ARG1 &self_ ,const ARGV<ENABLE_TYPE<stl::is_pod<_ARG1>::value>> & ,const DEF<decltype (ARGVP1)> &) {
		return BasicProc::mem_hash (PTRTOARR[_CAST_ (_NULL_<ARGV<BYTE[_SIZEOF_ (_ARG1)]>> () ,self_)] ,_SIZEOF_ (_ARG1)) ;
	}

	template <class _ARG1>
	imports FLAG invoke (const _ARG1 &self_) {
		FLAG ret = template_hash (self_ ,ARGVPX ,ARGVP9) ;
		ret &= VAR_MAX ;
		return _MOVE_ (ret) ;
	}
} ;
} ;

#ifdef __CSC_CONFIG_VAR32__
template <class _ARG1>
inline exports FLAG BasicProc::mem_hash (const ARR<_ARG1> &src ,const LENGTH &len) {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
	static constexpr auto M_MAGIC_N1 = VAR (-2128831035) ;
	static constexpr auto M_MAGIC_N2 = VAR (16777619) ;
	_DEBUG_ASSERT_ (len >= 0) ;
	FLAG ret = M_MAGIC_N1 ;
	for (auto &&i : _RANGE_ (0 ,len)) {
		ret ^= U::OPERATOR_HASH::invoke (src[i]) ;
		ret *= M_MAGIC_N2 ;
	}
	ret &= VAR_MAX ;
	return _MOVE_ (ret) ;
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
}
#endif

#ifdef __CSC_CONFIG_VAR64__
template <class _ARG1>
inline exports FLAG BasicProc::mem_hash (const ARR<_ARG1> &src ,const LENGTH &len) {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
	static constexpr auto M_MAGIC_N1 = VAR (-3750763034362895579) ;
	static constexpr auto M_MAGIC_N2 = VAR (1099511628211) ;
	_DEBUG_ASSERT_ (len >= 0) ;
	FLAG ret = M_MAGIC_N1 ;
	for (auto &&i : _RANGE_ (0 ,len)) {
		ret ^= U::OPERATOR_HASH::invoke (src[i]) ;
		ret *= M_MAGIC_N2 ;
	}
	ret &= VAR_MAX ;
	return _MOVE_ (ret) ;
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
}
#endif

class CRC32StaticProc
	:private Wrapped<void> {
public:
	imports CHAR static_mem_crc32_table_each (const CHAR &val) ;

	imports const PACK<CHAR[256]> &static_mem_crc32_table () ;
} ;

inline exports CHAR CRC32StaticProc::static_mem_crc32_table_each (const CHAR &val) {
	CHAR ret = val ;
	for (auto &&i : _RANGE_ (0 ,8)) {
		_STATIC_UNUSED_ (i) ;
		const auto r1x = CHAR (ret & CHAR (0X00000001)) ;
		ret >>= 1 ;
		if (r1x == 0)
			continue ;
		ret ^= CHAR (0XEDB88320) ;
	}
	return _MOVE_ (ret) ;
}

inline exports const PACK<CHAR[256]> &CRC32StaticProc::static_mem_crc32_table () {
	return _CACHE_ ([&] () {
		PACK<CHAR[256]> ret ;
		for (auto &&i : _RANGE_ (0 ,_COUNTOF_ (decltype (ret.mP1))))
			ret.mP1[i] = CRC32StaticProc::static_mem_crc32_table_each (CHAR (i)) ;
		return _MOVE_ (ret) ;
	}) ;
}

template <class _ARG1>
inline exports FLAG BasicProc::mem_crc32 (const ARR<_ARG1> &src ,const LENGTH &len) {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
	_STATIC_ASSERT_ (stl::is_same<_ARG1 ,BYTE>::value) ;
	FLAG ret = FLAG (0XFFFFFFFF) ;
	auto &r1x = CRC32StaticProc::static_mem_crc32_table () ;
	for (auto &&i : _RANGE_ (0 ,len)) {
		const auto r2x = CHAR ((CHAR (ret) ^ CHAR (src[i])) & CHAR (0X000000FF)) ;
		ret = FLAG (r1x.mP1[INDEX (r2x)] ^ (CHAR (ret) >> 8)) ;
	}
	ret &= VAR32_MAX ;
	return _MOVE_ (ret) ;
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
}

template <class _ARG1>
inline exports INDEX BasicProc::mem_chr (const ARR<_ARG1> &src ,const LENGTH &len ,const _ARG1 &val) {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
	_DEBUG_ASSERT_ (len >= 0) ;
	for (auto &&i : _RANGE_ (0 ,len))
		if (src[i] == val)
			return i ;
	return VAR_NONE ;
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
}

template <class _ARG1>
inline exports INDEX BasicProc::mem_rchr (const ARR<_ARG1> &src ,const LENGTH &len ,const _ARG1 &val) {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
	_DEBUG_ASSERT_ (len >= 0) ;
	for (auto &&i : _RANGE_ (0 ,len))
		if (src[len + ~i] == val)
			return (len + ~i) ;
	return VAR_NONE ;
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
}

template <class _ARG1>
inline exports void BasicProc::mem_copy (ARR<_ARG1> &dst ,const ARR<_ARG1> &src ,const LENGTH &len) {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
	_DEBUG_ASSERT_ (len >= 0) ;
	if (dst == src)
		return ;
	_DEBUG_ASSERT_ (_ABS_ (dst - src) >= len) ;
	for (auto &&i : _RANGE_ (0 ,len))
		dst[i] = src[i] ;
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
}

template <class _ARG1>
inline exports void BasicProc::mem_rcopy (ARR<_ARG1> &dst ,const ARR<_ARG1> &src ,const LENGTH &len) {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
	_DEBUG_ASSERT_ (len >= 0) ;
	auto fax = TRUE ;
	if switch_once (fax) {
		if (!(dst != src))
			discard ;
		_DEBUG_ASSERT_ (_ABS_ (dst - src) >= len) ;
		for (auto &&i : _RANGE_ (0 ,len))
			dst[i] = src[len + ~i] ;
	}
	if switch_once (fax) {
		if (!(dst == src))
			discard ;
		for (auto &&i : _RANGE_ (0 ,len / 2)) {
			const auto r1x = dst[i] ;
			dst[i] = dst[len + ~i] ;
			dst[len + ~i] = r1x ;
		}
	}
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
}

template <class _ARG1>
inline exports void BasicProc::mem_move (ARR<_ARG1> &dst1 ,ARR<_ARG1> &dst2 ,const LENGTH &len) {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
	_DEBUG_ASSERT_ (len >= 0) ;
	if (dst1 == dst2)
		return ;
	auto fax = TRUE ;
	if switch_once (fax) {
		if (!(dst1 < dst2))
			discard ;
		for (auto &&i : _RANGE_ (0 ,len))
			dst1[i] = _MOVE_ (dst2[i]) ;
	}
	if switch_once (fax) {
		if (!(dst1 > dst2))
			discard ;
		for (auto &&i : _RANGE_ (0 ,len))
			dst1[len + ~i] = _MOVE_ (dst2[len + ~i]) ;
	}
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
}

template <class _ARG1>
inline exports void BasicProc::mem_swap (ARR<_ARG1> &dst1 ,ARR<_ARG1> &dst2 ,const LENGTH &len) {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
	_DEBUG_ASSERT_ (len >= 0) ;
	if (dst1 == dst2)
		return ;
	_DEBUG_ASSERT_ (_ABS_ (dst1 - dst2) >= len) ;
	for (auto &&i : _RANGE_ (0 ,len))
		_SWAP_ (dst1[i] ,dst2[i]) ;
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
}

template <class _ARG1>
inline exports void BasicProc::mem_fill (ARR<_ARG1> &dst ,const LENGTH &len ,const _ARG1 &val) {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
	_DEBUG_ASSERT_ (len >= 0) ;
	for (auto &&i : _RANGE_ (0 ,len))
		dst[i] = val ;
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
}

template <class UNIT ,class CONT>
class ScopedPtr final
	:private Proxy {
private:
	PTR<UNIT> mPointer ;

public:
	ScopedPtr () = delete ;

	explicit ScopedPtr (const PTR<UNIT> &pointer)
		:ScopedPtr (ARGVP0) {
		mPointer = pointer ;
	}

	inline ~ScopedPtr () noexcept {
		if (mPointer == NULL)
			return ;
		CONT::free (mPointer) ;
		mPointer = NULL ;
	}

	inline ScopedPtr (const ScopedPtr &) = default ;
	inline ScopedPtr &operator= (const ScopedPtr &) = default ;

	inline ScopedPtr (ScopedPtr &&) = default ;
	inline ScopedPtr &operator= (ScopedPtr &&) = default ;

	inline implicit operator const PTR<UNIT> & () const leftvalue {
		_DEBUG_ASSERT_ (mPointer != NULL) ;
		return mPointer ;
	}

	inline void operator= (const DEF<decltype (NULL)> &) leftvalue noexcept {
		mPointer = NULL ;
	}

private:
	explicit ScopedPtr (const DEF<decltype (ARGVP0)> &) noexcept
		:mPointer (NULL) {}
} ;

template <class UNIT>
class ScopedGuard final
	:private Proxy {
private:
	PTR<UNIT> mPointer ;

public:
	ScopedGuard () = delete ;

	template <class _ARG1>
	explicit ScopedGuard (_ARG1 &address) side_effects
		:ScopedGuard (ARGVP0) {
		auto &r1x = _XVALUE_<UNIT> (address) ;
		r1x.lock () ;
		mPointer = DEPTR[r1x] ;
	}

	inline ~ScopedGuard () noexcept {
		if (mPointer == NULL)
			return ;
		_CALL_TRY_ ([&] () {
			mPointer->unlock () ;
		} ,[&] () {
			_DEBUG_ASSERT_ (FALSE) ;
		}) ;
		mPointer = NULL ;
	}

	inline ScopedGuard (const ScopedGuard &) = default ;
	inline ScopedGuard &operator= (const ScopedGuard &) = default ;

	inline ScopedGuard (ScopedGuard &&) = default ;
	inline ScopedGuard &operator= (ScopedGuard &&) = default ;

private:
	explicit ScopedGuard (const DEF<decltype (ARGVP0)> &) noexcept
		:mPointer (NULL) {}
} ;

template <class UNIT>
class ScopedBuild final
	:private Proxy {
private:
	PTR<const volatile PTR<TEMP<UNIT>>> mPointer ;
	LENGTH mSize ;

public:
	ScopedBuild () = delete ;

	template <class _ARG1 ,class... _ARGS>
	explicit ScopedBuild (_ARG1 &address ,_ARGS &&...initval) side_effects
		:ScopedBuild (ARGVP0) {
		auto &r1x = _XVALUE_<PTR<TEMP<UNIT>>> (address) ;
		if (r1x == NULL)
			return ;
		mPointer = DEPTR[r1x] ;
		_CREATE_ (r1x ,_FORWARD_<_ARGS> (initval)...) ;
		mSize++ ;
	}

	inline ~ScopedBuild () noexcept {
		if (mPointer == NULL)
			return ;
		const auto r1x = _COPY_ (DEREF[mPointer]) ;
		if (r1x == NULL)
			return ;
		if switch_once (TRUE) {
			if (mSize <= 0)
				discard ;
			_DESTROY_ (r1x) ;
			mSize-- ;
		}
		mPointer = NULL ;
	}

	inline ScopedBuild (const ScopedBuild &) = default ;
	inline ScopedBuild &operator= (const ScopedBuild &) = default ;

	inline ScopedBuild (ScopedBuild &&) = default ;
	inline ScopedBuild &operator= (ScopedBuild &&) = default ;

private:
	explicit ScopedBuild (const DEF<decltype (ARGVP0)> &) noexcept
		:mPointer (NULL) ,mSize (0) {}
} ;

template <class UNIT>
class ScopedBuild<ARR<UNIT>> final
	:private Proxy {
private:
	PTR<const volatile PTR<ARR<TEMP<UNIT>>>> mPointer ;
	LENGTH mSize ;

public:
	ScopedBuild () = delete ;

	template <class _ARG1 ,class... _ARGS>
	explicit ScopedBuild (_ARG1 &address ,const LENGTH &len) side_effects
		:ScopedBuild (ARGVP0) {
		auto &r1x = _XVALUE_<PTR<ARR<TEMP<UNIT>>>> (address) ;
		if (r1x == NULL)
			return ;
		mPointer = DEPTR[r1x] ;
		while (TRUE) {
			if (mSize >= len)
				break ;
			_CREATE_ (DEPTR[DEREF[r1x][mSize]]) ;
			mSize++ ;
		}
	}

	template <class _ARG1 ,class... _ARGS>
	explicit ScopedBuild (_ARG1 &address ,const ARR<UNIT> &src ,const LENGTH &len) side_effects
		:ScopedBuild (ARGVP0) {
		auto &r1x = _XVALUE_<PTR<ARR<TEMP<UNIT>>>> (address) ;
		if (r1x == NULL)
			return ;
		mPointer = DEPTR[r1x] ;
		while (TRUE) {
			if (mSize >= len)
				break ;
			_CREATE_ (DEPTR[DEREF[r1x][mSize]] ,src[mSize]) ;
			mSize++ ;
		}
	}

	inline ~ScopedBuild () noexcept {
		if (mPointer == NULL)
			return ;
		const auto r1x = _COPY_ (DEREF[mPointer]) ;
		if (r1x == NULL)
			return ;
		while (TRUE) {
			if (mSize <= 0)
				break ;
			_DESTROY_ (DEPTR[DEREF[r1x][mSize - 1]]) ;
			mSize-- ;
		}
		mPointer = NULL ;
	}

	inline ScopedBuild (const ScopedBuild &) = default ;
	inline ScopedBuild &operator= (const ScopedBuild &) = default ;

	inline ScopedBuild (ScopedBuild &&) = default ;
	inline ScopedBuild &operator= (ScopedBuild &&) = default ;

private:
	explicit ScopedBuild (const DEF<decltype (ARGVP0)> &) noexcept
		:mPointer (NULL) ,mSize (0) {}
} ;

class GlobalHeap
	:private Wrapped<void> {
public:
	template <class _ARG1>
	imports ScopedPtr<_ARG1 ,GlobalHeap> alloc (const ARGV<_ARG1> &) side_effects {
		_STATIC_ASSERT_ (stl::is_pod<_ARG1>::value) ;
		_STATIC_ASSERT_ (_ALIGNOF_ (_ARG1) <= _ALIGNOF_ (stl::max_align_t)) ;
		const auto r1x = operator new (_SIZEOF_ (_ARG1) ,stl::nothrow) ;
		_DYNAMIC_ASSERT_ (r1x != NULL) ;
		auto &r2x = _LOAD_ (_NULL_<ARGV<_ARG1>> () ,r1x) ;
		return ScopedPtr<_ARG1 ,GlobalHeap> (DEPTR[r2x]) ;
	}

	template <class _ARG1>
	imports ScopedPtr<ARR<_ARG1> ,GlobalHeap> alloc (const ARGV<_ARG1> & ,const LENGTH &len) side_effects {
		_STATIC_ASSERT_ (stl::is_pod<_ARG1>::value) ;
		_STATIC_ASSERT_ (_ALIGNOF_ (_ARG1) <= _ALIGNOF_ (stl::max_align_t)) ;
		_DEBUG_ASSERT_ (len > 0) ;
		const auto r1x = len * _SIZEOF_ (_ARG1) ;
		_DEBUG_ASSERT_ (r1x > 0) ;
		const auto r2x = operator new (r1x ,stl::nothrow) ;
		_DYNAMIC_ASSERT_ (r2x != NULL) ;
		auto &r3x = _LOAD_ (_NULL_<ARGV<ARR<_ARG1>>> () ,r2x) ;
		return ScopedPtr<ARR<_ARG1> ,GlobalHeap> (DEPTR[r3x]) ;
	}

	template <class _ARG1>
	imports void free (const PTR<_ARG1> &address) noexcept {
		auto &r1x = _LOAD_UNSAFE_ (_NULL_<ARGV<NONE>> () ,_ADDRESS_ (address)) ;
		operator delete (DEPTR[r1x] ,stl::nothrow) ;
	}
} ;

template <class>
class AutoRef ;

template <class UNIT>
class AutoRef<SPECIALIZATION<UNIT ,FALSE>> {
	_STATIC_ASSERT_ (stl::is_complete<UNIT>::value) ;

private:
	using SPECIALIZATION_THIS = AutoRef<UNIT> ;

	class Holder {
	private:
		friend AutoRef ;
		friend SPECIALIZATION_THIS ;
		UNIT mValue ;

	public:
		template <class... _ARGS>
		explicit Holder (_ARGS &&...initval)
			:mValue (_FORWARD_<_ARGS> (initval)...) {}
	} ;

private:
	friend SPECIALIZATION_THIS ;
	PTR<Holder> mPointer ;

public:
	AutoRef ()
		:AutoRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	inline ~AutoRef () noexcept {
		if (mPointer == NULL)
			return ;
		mPointer->~Holder () ;
		GlobalHeap::free (mPointer) ;
		mPointer = NULL ;
	}

	inline AutoRef (const AutoRef &) = delete ;
	inline AutoRef &operator= (const AutoRef &) = delete ;

	inline AutoRef (AutoRef &&that) noexcept
		:AutoRef (ARGVP0) {
		mPointer = _EXCHANGE_ (that.mPointer) ;
	}

	inline AutoRef &operator= (AutoRef &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~AutoRef () ;
			new (this) AutoRef (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

private:
	explicit AutoRef (const DEF<decltype (ARGVP0)> &) noexcept
		:mPointer (NULL) {}
} ;

template <class UNIT>
class AutoRef<SPECIALIZATION<UNIT ,TRUE>> {
	_STATIC_ASSERT_ (stl::is_complete<UNIT>::value) ;

private:
	using SPECIALIZATION_THIS = AutoRef<UNIT> ;

	class Holder {
	private:
		friend AutoRef ;
		friend SPECIALIZATION_THIS ;
		UNIT mValue ;

	public:
		template <class... _ARGS>
		explicit Holder (_ARGS &&...initval)
			:mValue (_FORWARD_<_ARGS> (initval)...) {}
	} ;

private:
	friend SPECIALIZATION_THIS ;
	PTR<Holder> mPointer ;

public:
	AutoRef ()
		:AutoRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	inline ~AutoRef () noexcept {
		if (mPointer == NULL)
			return ;
		mPointer->~Holder () ;
		GlobalHeap::free (mPointer) ;
		mPointer = NULL ;
	}

	inline AutoRef (const AutoRef &that)
		:AutoRef (ARGVP0) {
		if (that.mPointer == NULL)
			return ;
		auto rax = GlobalHeap::alloc (_NULL_<ARGV<TEMP<Holder>>> ()) ;
		ScopedBuild<Holder> ANONYMOUS (rax ,_XVALUE_<const UNIT> (that.mPointer->mValue)) ;
		auto &r1x = _LOAD_ (_NULL_<ARGV<Holder>> () ,_XVALUE_<PTR<TEMP<Holder>>> (rax)) ;
		mPointer = DEPTR[r1x] ;
		rax = NULL ;
	}

	inline AutoRef &operator= (const AutoRef &that) {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~AutoRef () ;
			new (this) AutoRef (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	inline AutoRef (AutoRef &&that) noexcept
		:AutoRef (ARGVP0) {
		mPointer = _EXCHANGE_ (that.mPointer) ;
	}

	inline AutoRef &operator= (AutoRef &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~AutoRef () ;
			new (this) AutoRef (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

private:
	explicit AutoRef (const DEF<decltype (ARGVP0)> &) noexcept
		:mPointer (NULL) {}
} ;

template <class UNIT>
class AutoRef final
	:private AutoRef<SPECIALIZATION<UNIT ,(stl::is_copy_constructible<UNIT>::value && stl::is_nothrow_move_constructible<UNIT>::value)>> {
private:
	using SPECIALIZATION_BASE = AutoRef<SPECIALIZATION<UNIT ,(stl::is_copy_constructible<UNIT>::value && stl::is_nothrow_move_constructible<UNIT>::value)>> ;
	using Holder = typename SPECIALIZATION_BASE::Holder ;

private:
	friend SPECIALIZATION_BASE ;
	using SPECIALIZATION_BASE::mPointer ;

public:
	AutoRef () = default ;

	BOOL exist () const {
		if (mPointer == NULL)
			return FALSE ;
		return TRUE ;
	}

	UNIT &to () leftvalue {
		_DEBUG_ASSERT_ (exist ()) ;
		return mPointer->mValue ;
	}

	inline implicit operator UNIT & () leftvalue {
		return to () ;
	}

	inline PTR<UNIT> operator-> () leftvalue {
		return DEPTR[to ()] ;
	}

	const UNIT &to () const leftvalue {
		_DEBUG_ASSERT_ (exist ()) ;
		return mPointer->mValue ;
	}

	inline implicit operator const UNIT & () const leftvalue {
		return to () ;
	}

	inline PTR<const UNIT> operator-> () const leftvalue {
		return DEPTR[to ()] ;
	}

public:
	template <class... _ARGS>
	imports AutoRef make (_ARGS &&...initval) {
		auto rax = GlobalHeap::alloc (_NULL_<ARGV<TEMP<Holder>>> ()) ;
		ScopedBuild<Holder> ANONYMOUS (rax ,_FORWARD_<_ARGS> (initval)...) ;
		auto &r1x = _LOAD_ (_NULL_<ARGV<Holder>> () ,_XVALUE_<PTR<TEMP<Holder>>> (rax)) ;
		AutoRef ret = AutoRef (DEPTR[r1x]) ;
		rax = NULL ;
		return _MOVE_ (ret) ;
	}

private:
	explicit AutoRef (const PTR<Holder> &pointer)
		:SPECIALIZATION_BASE (ARGVP0) {
		mPointer = pointer ;
	}
} ;

template <class UNIT>
class SharedRef final {
	_STATIC_ASSERT_ (stl::is_complete<UNIT>::value) ;

private:
	class Holder {
	private:
		friend SharedRef ;
		UNIT mValue ;
		LENGTH mCounter ;

	public:
		template <class... _ARGS>
		explicit Holder (_ARGS &&...initval)
			:mValue (_FORWARD_<_ARGS> (initval)...) ,mCounter (0) {}
	} ;

private:
	PTR<Holder> mPointer ;

public:
	SharedRef ()
		:SharedRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	inline ~SharedRef () noexcept {
		if (mPointer == NULL)
			return ;
		if switch_once (TRUE) {
			const auto r1x = --mPointer->mCounter ;
			if (r1x != 0)
				discard ;
			mPointer->~Holder () ;
			GlobalHeap::free (mPointer) ;
		}
		mPointer = NULL ;
	}

	inline SharedRef (const SharedRef &that)
		:SharedRef (that.mPointer) {
		_STATIC_WARNING_ ("noop") ;
	}

	inline SharedRef &operator= (const SharedRef &that) {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~SharedRef () ;
			new (this) SharedRef (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	inline SharedRef (SharedRef &&that) noexcept
		:SharedRef (ARGVP0) {
		mPointer = _EXCHANGE_ (that.mPointer) ;
	}

	inline SharedRef &operator= (SharedRef &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~SharedRef () ;
			new (this) SharedRef (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	BOOL exist () const {
		if (mPointer == NULL)
			return FALSE ;
		return TRUE ;
	}

	UNIT &to () const leftvalue {
		_DEBUG_ASSERT_ (exist ()) ;
		const auto r1x = static_cast<PTR<Holder>> (mPointer) ;
		return r1x->mValue ;
	}

	inline implicit operator UNIT & () const leftvalue {
		return to () ;
	}

	inline PTR<UNIT> operator-> () const leftvalue {
		return DEPTR[to ()] ;
	}

public:
	template <class... _ARGS>
	imports SharedRef make (_ARGS &&...initval) {
		auto rax = GlobalHeap::alloc (_NULL_<ARGV<TEMP<Holder>>> ()) ;
		ScopedBuild<Holder> ANONYMOUS (rax ,_FORWARD_<_ARGS> (initval)...) ;
		auto &r1x = _LOAD_ (_NULL_<ARGV<Holder>> () ,_XVALUE_<PTR<TEMP<Holder>>> (rax)) ;
		SharedRef ret = SharedRef (DEPTR[r1x]) ;
		rax = NULL ;
		return _MOVE_ (ret) ;
	}

private:
	explicit SharedRef (const DEF<decltype (ARGVP0)> &) noexcept
		:mPointer (NULL) {}

	explicit SharedRef (const PTR<Holder> &pointer) noexcept
		:SharedRef (ARGVP0) {
		if (pointer == NULL)
			return ;
		const auto r1x = ++pointer->mCounter ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x > 0) ;
		mPointer = pointer ;
	}
} ;

template <class>
class AnyRef ;

template <>
class AnyRef<void> final {
private:
	class Holder
		:public Interface {
	public:
		virtual FLAG typemid () const = 0 ;
	} ;

private:
	template <class>
	friend class AnyRef ;
	PTR<Holder> mPointer ;

public:
	AnyRef ()
		:AnyRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1>
	implicit AnyRef (AnyRef<_ARG1> &&that)
		: AnyRef (_MOVE_ (that.rebind (_NULL_<ARGV<void>> ()))) {
		_STATIC_WARNING_ ("noop") ;
	}

	inline ~AnyRef () noexcept {
		if (mPointer == NULL)
			return ;
		mPointer->~Holder () ;
		GlobalHeap::free (mPointer) ;
		mPointer = NULL ;
	}

	inline AnyRef (const AnyRef &) = delete ;
	inline AnyRef &operator= (const AnyRef &) = delete ;

	inline AnyRef (AnyRef &&that) noexcept
		:AnyRef (ARGVP0) {
		mPointer = _EXCHANGE_ (that.mPointer) ;
	}

	inline AnyRef &operator= (AnyRef &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~AnyRef () ;
			new (this) AnyRef (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	template <class _ARG1>
	AnyRef<_ARG1> &rebind (const ARGV<_ARG1> &) leftvalue {
		return _CAST_ (_NULL_<ARGV<AnyRef<_ARG1>>> () ,DEREF[this]) ;
	}

	template <class _ARG1>
	const AnyRef<_ARG1> &rebind (const ARGV<_ARG1> &) const leftvalue {
		return _CAST_ (_NULL_<ARGV<AnyRef<_ARG1>>> () ,DEREF[this]) ;
	}

	BOOL exist () const {
		if (mPointer == NULL)
			return FALSE ;
		return TRUE ;
	}

	FLAG typemid () const {
		_DEBUG_ASSERT_ (exist ()) ;
		return mPointer->typemid () ;
	}

private:
	explicit AnyRef (const DEF<decltype (ARGVP0)> &) noexcept
		:mPointer (NULL) {}
} ;

template <class UNIT>
class AnyRef final {
	_STATIC_ASSERT_ (stl::is_complete<UNIT>::value) ;

private:
	using Holder = typename AnyRef<void>::Holder ;

	struct Private {
		template <class>
		class ImplHolder ;
	} ;

private:
	PTR<Holder> mPointer ;

public:
	AnyRef ()
		:AnyRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1>
	implicit AnyRef (AnyRef<_ARG1> &&that)
		: AnyRef (_MOVE_ (that.rebind (_NULL_<ARGV<UNIT>> ()))) {
		_STATIC_WARNING_ ("noop") ;
	}

	inline ~AnyRef () noexcept {
		if (mPointer == NULL)
			return ;
		mPointer->~Holder () ;
		GlobalHeap::free (mPointer) ;
		mPointer = NULL ;
	}

	inline AnyRef (const AnyRef &) = delete ;
	inline AnyRef &operator= (const AnyRef &) = delete ;

	inline AnyRef (AnyRef &&that) noexcept
		:AnyRef (ARGVP0) {
		mPointer = _EXCHANGE_ (that.mPointer) ;
	}

	inline AnyRef &operator= (AnyRef &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~AnyRef () ;
			new (this) AnyRef (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	template <class _ARG1>
	AnyRef<_ARG1> &rebind (const ARGV<_ARG1> &) leftvalue {
		return _CAST_ (_NULL_<ARGV<AnyRef<_ARG1>>> () ,DEREF[this]) ;
	}

	template <class _ARG1>
	const AnyRef<_ARG1> &rebind (const ARGV<_ARG1> &) const leftvalue {
		return _CAST_ (_NULL_<ARGV<AnyRef<_ARG1>>> () ,DEREF[this]) ;
	}

	BOOL exist () const {
		if (mPointer == NULL)
			return FALSE ;
		return TRUE ;
	}

	FLAG typemid () const {
		_DEBUG_ASSERT_ (exist ()) ;
		return mPointer->typemid () ;
	}

	UNIT &to () leftvalue {
		struct Dependent ;
		using ImplHolder = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<UNIT> ;
		_DEBUG_ASSERT_ (typemid () == _TYPEMID_ (_NULL_<ARGV<UNIT>> ())) ;
		const auto r1x = static_cast<PTR<ImplHolder>> (mPointer) ;
		return r1x->mValue ;
	}

	inline implicit operator UNIT & () leftvalue {
		return to () ;
	}

	inline PTR<UNIT> operator-> () leftvalue {
		return DEPTR[to ()] ;
	}

	const UNIT &to () const leftvalue {
		struct Dependent ;
		using ImplHolder = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<UNIT> ;
		_DEBUG_ASSERT_ (typemid () == _TYPEMID_ (_NULL_<ARGV<UNIT>> ())) ;
		const auto r1x = static_cast<PTR<ImplHolder>> (mPointer) ;
		return r1x->mValue ;
	}

	inline implicit operator const UNIT & () const leftvalue {
		return to () ;
	}

	inline PTR<const UNIT> operator-> () const leftvalue {
		return DEPTR[to ()] ;
	}

public:
	template <class... _ARGS>
	imports AnyRef make (_ARGS &&...initval) {
		struct Dependent ;
		using ImplHolder = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<UNIT> ;
		auto rax = GlobalHeap::alloc (_NULL_<ARGV<TEMP<ImplHolder>>> ()) ;
		ScopedBuild<ImplHolder> ANONYMOUS (rax ,_FORWARD_<_ARGS> (initval)...) ;
		auto &r1x = _LOAD_ (_NULL_<ARGV<ImplHolder>> () ,_XVALUE_<PTR<TEMP<ImplHolder>>> (rax)) ;
		AnyRef ret = AnyRef (DEPTR[r1x]) ;
		rax = NULL ;
		return _MOVE_ (ret) ;
	}

private:
	explicit AnyRef (const DEF<decltype (ARGVP0)> &) noexcept
		:mPointer (NULL) {}

	explicit AnyRef (const PTR<Holder> &pointer)
		:AnyRef (ARGVP0) {
		mPointer = pointer ;
	}
} ;

template <class UNIT>
template <class UNIT_>
class AnyRef<UNIT>::Private::ImplHolder
	:public Holder {
private:
	friend AnyRef ;
	UNIT_ mValue ;

public:
	template <class... _ARGS>
	explicit ImplHolder (_ARGS &&...initval)
		:mValue (_FORWARD_<_ARGS> (initval)...) {}

	FLAG typemid () const override {
		return _TYPEMID_ (_NULL_<ARGV<UNIT_>> ()) ;
	}
} ;

template <class>
class UniqueRef ;

template <>
class UniqueRef<void> final {
private:
	class Holder
		:public Interface {
	public:
		virtual void release () = 0 ;
	} ;

	struct Private {
		template <class>
		class ImplHolder ;
	} ;

private:
	template <class>
	friend class UniqueRef ;
	PTR<Holder> mPointer ;

public:
	UniqueRef ()
		:UniqueRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1 ,class _ARG2>
	explicit UniqueRef (const _ARG1 &constructor ,_ARG2 &&destructor) side_effects
		: UniqueRef (ARGVP0) {
		struct Dependent ;
		using ImplHolder = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<PTR<void ()>> ;
		_STATIC_ASSERT_ (stl::is_same<RESULT_OF_TYPE<_ARG1 ,ARGVS<>> ,void>::value) ;
		_STATIC_ASSERT_ (!stl::is_reference<_ARG2>::value) ;
		_STATIC_ASSERT_ (stl::is_same<RESULT_OF_TYPE<_ARG2 ,ARGVS<>> ,void>::value) ;
		auto rax = GlobalHeap::alloc (_NULL_<ARGV<TEMP<ImplHolder>>> ()) ;
		const auto r1x = _FORWARD_<PTR<void ()>> (destructor) ;
		ScopedBuild<ImplHolder> ANONYMOUS (rax ,r1x) ;
		auto &r2x = _LOAD_ (_NULL_<ARGV<ImplHolder>> () ,_XVALUE_<PTR<TEMP<ImplHolder>>> (rax)) ;
		constructor () ;
		mPointer = DEPTR[r2x] ;
		rax = NULL ;
	}

	inline ~UniqueRef () noexcept {
		if (mPointer == NULL)
			return ;
		_CALL_TRY_ ([&] () {
			mPointer->release () ;
		} ,[&] () {
			_DEBUG_ASSERT_ (FALSE) ;
		}) ;
		mPointer->~Holder () ;
		GlobalHeap::free (mPointer) ;
		mPointer = NULL ;
	}

	inline UniqueRef (const UniqueRef &) = delete ;
	inline UniqueRef &operator= (const UniqueRef &) = delete ;

	inline UniqueRef (UniqueRef &&that) noexcept
		:UniqueRef (ARGVP0) {
		mPointer = _EXCHANGE_ (that.mPointer) ;
	}

	inline UniqueRef &operator= (UniqueRef &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~UniqueRef () ;
			new (this) UniqueRef (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	BOOL exist () const {
		if (mPointer == NULL)
			return FALSE ;
		return TRUE ;
	}

private:
	explicit UniqueRef (const DEF<decltype (ARGVP0)> &) noexcept
		:mPointer (NULL) {}
} ;

template <class UNIT_>
class UniqueRef<void>::Private::ImplHolder
	:public Holder {
private:
	UNIT_ mFunctor ;

public:
	ImplHolder () = delete ;

	explicit ImplHolder (const REMOVE_CVR_TYPE<UNIT_> &func)
		:mFunctor (_MOVE_ (func)) {}

	explicit ImplHolder (REMOVE_CVR_TYPE<UNIT_> &&func)
		:mFunctor (_MOVE_ (func)) {}

	void release () override {
		mFunctor () ;
	}
} ;

template <class UNIT>
class UniqueRef final {
	_STATIC_ASSERT_ (stl::is_complete<UNIT>::value) ;

private:
	using Holder = typename UniqueRef<void>::Holder ;

	struct Private {
		template <class>
		class ImplHolder ;
	} ;

private:
	PTR<Holder> mPointer ;

public:
	UniqueRef ()
		:UniqueRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1 ,class _ARG2>
	explicit UniqueRef (const _ARG1 &constructor ,_ARG2 &&destructor) side_effects
		: UniqueRef (ARGVP0) {
		struct Dependent ;
		using ImplHolder = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<PTR<void (UNIT &)>> ;
		_STATIC_ASSERT_ (stl::is_same<RESULT_OF_TYPE<_ARG1 ,ARGVS<UNIT &>> ,void>::value) ;
		_STATIC_ASSERT_ (!stl::is_reference<_ARG2>::value) ;
		_STATIC_ASSERT_ (stl::is_same<RESULT_OF_TYPE<_ARG2 ,ARGVS<UNIT &>> ,void>::value) ;
		auto rax = GlobalHeap::alloc (_NULL_<ARGV<TEMP<ImplHolder>>> ()) ;
		const auto r1x = _FORWARD_<PTR<void (UNIT &)>> (destructor) ;
		ScopedBuild<ImplHolder> ANONYMOUS (rax ,r1x) ;
		auto &r2x = _LOAD_ (_NULL_<ARGV<ImplHolder>> () ,_XVALUE_<PTR<TEMP<ImplHolder>>> (rax)) ;
		constructor (r2x.mValue) ;
		mPointer = DEPTR[r2x] ;
		rax = NULL ;
	}

	inline ~UniqueRef () noexcept {
		if (mPointer == NULL)
			return ;
		_CALL_TRY_ ([&] () {
			mPointer->release () ;
		} ,[&] () {
			_DEBUG_ASSERT_ (FALSE) ;
		}) ;
		mPointer->~Holder () ;
		GlobalHeap::free (mPointer) ;
		mPointer = NULL ;
	}

	inline UniqueRef (const UniqueRef &) = delete ;
	inline UniqueRef &operator= (const UniqueRef &) = delete ;

	inline UniqueRef (UniqueRef &&that) noexcept
		: UniqueRef (ARGVP0) {
		mPointer = _EXCHANGE_ (that.mPointer) ;
	}

	inline UniqueRef &operator= (UniqueRef &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~UniqueRef () ;
			new (this) UniqueRef (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	BOOL exist () const {
		if (mPointer == NULL)
			return FALSE ;
		return TRUE ;
	}

	const UNIT &to () const leftvalue {
		struct Dependent ;
		using ImplHolder = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<PTR<void (UNIT &)>> ;
		_DEBUG_ASSERT_ (exist ()) ;
		const auto r1x = static_cast<PTR<ImplHolder>> (mPointer) ;
		return r1x->mValue ;
	}

	inline implicit operator const UNIT & () const leftvalue {
		return to () ;
	}

	inline PTR<const UNIT> operator-> () const leftvalue {
		return DEPTR[to ()] ;
	}

public:
	template <class... _ARGS>
	imports UniqueRef make (_ARGS &&...initval) {
		struct Dependent ;
		using ImplHolder = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<PTR<void (UNIT &)>> ;
		auto rax = GlobalHeap::alloc (_NULL_<ARGV<TEMP<ImplHolder>>> ()) ;
		const auto r1x = _FORWARD_<PTR<void (UNIT &)>> ([] (UNIT &) {}) ;
		ScopedBuild<ImplHolder> ANONYMOUS (rax ,r1x) ;
		auto &r2x = _LOAD_ (_NULL_<ARGV<ImplHolder>> () ,_XVALUE_<PTR<TEMP<ImplHolder>>> (rax)) ;
		r2x.mValue = UNIT (_FORWARD_<_ARGS> (initval)...) ;
		const auto r3x = _FORWARD_<PTR<Holder>> (DEPTR[r2x]) ;
		UniqueRef ret = UniqueRef (r3x) ;
		rax = NULL ;
		return _MOVE_ (ret) ;
	}

private:
	explicit UniqueRef (const DEF<decltype (ARGVP0)> &) noexcept
		:mPointer (NULL) {}

	explicit UniqueRef (const PTR<Holder> &pointer)
		:UniqueRef (ARGVP0) {
		mPointer = pointer ;
	}
} ;

template <class UNIT>
template <class UNIT_>
class UniqueRef<UNIT>::Private::ImplHolder
	:public Holder {
private:
	friend UniqueRef ;
	REMOVE_CVR_TYPE<UNIT> mValue ;
	UNIT_ mFunctor ;

public:
	ImplHolder () = delete ;

	explicit ImplHolder (const REMOVE_CVR_TYPE<UNIT_> &func)
		:mFunctor (_MOVE_ (func)) {}

	explicit ImplHolder (REMOVE_CVR_TYPE<UNIT_> &&func)
		:mFunctor (_MOVE_ (func)) {}

	void release () override {
		mFunctor (mValue) ;
	}
} ;

template <class UNIT>
class PhanRef final {
	_STATIC_ASSERT_ (_SIZEOF_ (UNIT) > 0) ;

private:
	PTR<UNIT> mPointer ;

public:
	PhanRef ()
		:PhanRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	inline ~PhanRef () noexcept {
		if (mPointer == NULL)
			return ;
		mPointer = NULL ;
	}

	inline PhanRef (const PhanRef &) = delete ;
	inline PhanRef &operator= (const PhanRef &) = delete ;

	inline PhanRef (PhanRef &&that) noexcept
		:PhanRef (ARGVP0) {
		mPointer = _EXCHANGE_ (that.mPointer) ;
	}

	inline PhanRef &operator= (PhanRef &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~PhanRef () ;
			new (this) PhanRef (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	BOOL exist () const {
		if (mPointer == NULL)
			return FALSE ;
		return TRUE ;
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

private:
	explicit PhanRef (const DEF<decltype (ARGVP0)> &) noexcept
		:mPointer (NULL) {}

	explicit PhanRef (const PTR<UNIT> &pointer)
		:PhanRef (ARGVP0) {
		mPointer = pointer ;
	}

public:
	//@warn: phantom means deliver pointer without holder
	template <class _ARG1 ,class = ENABLE_TYPE<stl::is_same<REMOVE_CVR_TYPE<_ARG1> ,REMOVE_CVR_TYPE<UNIT>>::value>>
	imports PhanRef make (_ARG1 &val) side_effects {
		return PhanRef (DEPTR[val]) ;
	}

	template <class _ARG1>
	imports PhanRef make (const PhanRef<_ARG1> &val) {
		if (!val.exist ())
			return PhanRef () ;
		return make (_XVALUE_<UNIT> (val.self)) ;
	}
} ;

template <class>
class Function ;

template <class UNIT1 ,class... UNITS>
class Function<UNIT1 (UNITS...)> final {
private:
	class Holder
		:public Interface {
	public:
		virtual UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const = 0 ;
	} ;

	struct Private {
		template <class>
		class ImplHolder ;
	} ;

private:
	PTR<Holder> mPointer ;
	PTR<UNIT1 (UNITS...)> mFunction ;

public:
	Function ()
		:Function (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	implicit Function (const PTR<UNIT1 (UNITS...)> &that)
		: Function (ARGVP0) {
		_DEBUG_ASSERT_ (that != NULL) ;
		mFunction = that ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<!stl::is_same<REMOVE_CVR_TYPE<_ARG1> ,Function>::value>>
	implicit Function (_ARG1 &&that)
		: Function (ARGVP0) {
		struct Dependent ;
		using ImplHolder = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<REMOVE_REFERENCE_TYPE<_ARG1>> ;
		_STATIC_ASSERT_ (stl::is_same<RESULT_OF_TYPE<_ARG1 ,ARGVS<UNITS...>> ,UNIT1>::value) ;
		auto rax = GlobalHeap::alloc (_NULL_<ARGV<TEMP<ImplHolder>>> ()) ;
		ScopedBuild<ImplHolder> ANONYMOUS (rax ,_FORWARD_<_ARG1> (that)) ;
		auto &r1x = _LOAD_ (_NULL_<ARGV<ImplHolder>> () ,_XVALUE_<PTR<TEMP<ImplHolder>>> (rax)) ;
		mPointer = DEPTR[r1x] ;
		rax = NULL ;
	}

	inline ~Function () noexcept {
		if (mPointer == NULL)
			if (mFunction == NULL)
				return ;
		if switch_once (TRUE) {
			if (mPointer == NULL)
				discard ;
			mPointer->~Holder () ;
			GlobalHeap::free (mPointer) ;
		}
		mFunction = NULL ;
		mPointer = NULL ;
	}

	inline Function (const Function &) = delete ;
	inline Function &operator= (const Function &) = delete ;

	inline Function (Function &&that) noexcept
		:Function (ARGVP0) {
		mPointer = _EXCHANGE_ (that.mPointer) ;
		mFunction = _EXCHANGE_ (that.mFunction) ;
	}

	inline Function &operator= (Function &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~Function () ;
			new (this) Function (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	BOOL exist () const {
		if (mPointer == NULL)
			if (mFunction == NULL)
				return FALSE ;
		return TRUE ;
	}

	UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const {
		_DEBUG_ASSERT_ (exist ()) ;
		if (mFunction != NULL)
			return mFunction (_FORWARD_<FORWARD_TRAITS_TYPE<UNITS>> (funcval)...) ;
		return mPointer->invoke (_FORWARD_<FORWARD_TRAITS_TYPE<UNITS>> (funcval)...) ;
	}

	inline UNIT1 operator() (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const {
		return invoke (_FORWARD_<FORWARD_TRAITS_TYPE<UNITS>> (funcval)...) ;
	}

public:
	template <class... _ARGS>
	imports Function make (const PTR<UNIT1 (UNITS... ,_ARGS...)> &func ,const REMOVE_CVR_TYPE<_ARGS> &...parameter) {
		struct Dependent ;
		using ImplHolder = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<PTR<UNIT1 (UNITS... ,_ARGS...)>> ;
		auto rax = GlobalHeap::alloc (_NULL_<ARGV<TEMP<ImplHolder>>> ()) ;
		ScopedBuild<ImplHolder> ANONYMOUS (rax ,func ,parameter...) ;
		auto &r1x = _LOAD_ (_NULL_<ARGV<ImplHolder>> () ,_XVALUE_<PTR<TEMP<ImplHolder>>> (rax)) ;
		const auto r2x = _FORWARD_<PTR<Holder>> (DEPTR[r1x]) ;
		Function ret = Function (r2x) ;
		rax = NULL ;
		return _MOVE_ (ret) ;
	}

private:
	explicit Function (const DEF<decltype (ARGVP0)> &) noexcept
		:mPointer (NULL) ,mFunction (NULL) {}

	explicit Function (const PTR<Holder> &pointer)
		:Function (ARGVP0) {
		mPointer = pointer ;
	}
} ;

template <class UNIT1 ,class... UNITS>
template <class UNIT_>
class Function<UNIT1 (UNITS...)>::Private::ImplHolder
	:public Holder {
	_STATIC_ASSERT_ (stl::is_same<RESULT_OF_TYPE<UNIT_ ,ARGVS<UNITS...>> ,UNIT1>::value) ;

private:
	UNIT_ mFunctor ;

public:
	ImplHolder () = delete ;

	explicit ImplHolder (const REMOVE_CVR_TYPE<UNIT_> &func)
		:mFunctor (_MOVE_ (func)) {}

	explicit ImplHolder (REMOVE_CVR_TYPE<UNIT_> &&func)
		:mFunctor (_MOVE_ (func)) {}

	UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const override {
		return mFunctor (_FORWARD_<FORWARD_TRAITS_TYPE<UNITS>> (funcval)...) ;
	}
} ;

namespace U {
//@error: fuck vs2017
template <class _ARG1 ,class... _ARGS>
using MEMBER_FUNCTION_HINT = DEF<DEF<_ARG1 (_ARGS...)> NONE::*> ;
} ;

template <class UNIT1 ,class... UNITS>
class Function<U::MEMBER_FUNCTION_HINT<UNIT1 ,UNITS...>> final {
#pragma push_macro ("fake")
#undef fake
#define fake m_fake ()

private:
	class FakeHolder ;

	class Holder
		:public Interface {
	public:
		virtual void friend_copy (const PTR<TEMP<FakeHolder>> &address) const = 0 ;
		virtual UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const = 0 ;
	} ;

	class FakeHolder
		:public Holder {
	private:
		PTR<NONE> mContext ;
		DEF<DEF<UNIT1 (UNITS...)> NONE::*> mFunction ;

	public:
		FakeHolder () = delete ;

		void friend_copy (const PTR<TEMP<FakeHolder>> &address) const override ;

		UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const override ;
	} ;

	struct Private {
		class PureHolder ;

		template <class>
		class ImplHolder ;
	} ;

private:
	TEMP<FakeHolder> mVariant ;

public:
	Function ()
		:Function (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	implicit Function (const PTR<UNIT1 (UNITS...)> &that)
		: Function (ARGVP0) {
		struct Dependent ;
		using PureHolder = typename DEPENDENT_TYPE<Private ,Dependent>::PureHolder ;
		_DEBUG_ASSERT_ (that != NULL) ;
		static_create (_NULL_<ARGV<PureHolder>> () ,DEPTR[mVariant] ,that) ;
	}

	template <class _ARG1>
	explicit Function (const PhanRef<_ARG1> &context_ ,const DEF<DEF<UNIT1 (UNITS...)> _ARG1::*> &func)
		:Function (ARGVP0) {
		struct Dependent ;
		using ImplHolder = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<_ARG1> ;
		static_create (_NULL_<ARGV<ImplHolder>> () ,DEPTR[mVariant] ,DEPTR[context_.self] ,func) ;
	}

	template <class _ARG1>
	explicit Function (const PhanRef<const _ARG1> &context_ ,const DEF<DEF<UNIT1 (UNITS...) const> _ARG1::*> &func)
		:Function (ARGVP0) {
		struct Dependent ;
		using ImplHolder = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<const _ARG1> ;
		static_create (_NULL_<ARGV<ImplHolder>> () ,DEPTR[mVariant] ,DEPTR[context_.self] ,func) ;
	}

	template <class _ARG1>
	explicit Function (const PhanRef<_ARG1> &context_ ,const PTR<UNIT1 (PTR<_ARG1> ,UNITS...)> &func)
		:Function (ARGVP0) {
		struct Dependent ;
		using ImplHolder = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<PTR<_ARG1>> ;
		_DEBUG_ASSERT_ (func != NULL) ;
		static_create (_NULL_<ARGV<ImplHolder>> () ,DEPTR[mVariant] ,DEPTR[context_.self] ,func) ;
	}

	template <class _ARG1>
	explicit Function (const PhanRef<const _ARG1> &context_ ,const PTR<UNIT1 (PTR<const _ARG1> ,UNITS...)> &func)
		:Function (ARGVP0) {
		struct Dependent ;
		using ImplHolder = typename DEPENDENT_TYPE<Private ,Dependent>::template ImplHolder<PTR<const _ARG1>> ;
		_DEBUG_ASSERT_ (func != NULL) ;
		static_create (_NULL_<ARGV<ImplHolder>> () ,DEPTR[mVariant] ,DEPTR[context_.self] ,func) ;
	}

	inline ~Function () noexcept {
		if (!exist ())
			return ;
		fake.~Holder () ;
		_ZERO_ (mVariant) ;
	}

	inline Function (const Function &) = delete ;
	inline Function &operator= (const Function &) = delete ;

	inline Function (Function &&that) noexcept
		:Function (ARGVP0) {
		if (!that.exist ())
			return ;
		that.fake.friend_copy (DEPTR[mVariant]) ;
	}

	inline Function &operator= (Function &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~Function () ;
			new (this) Function (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	BOOL exist () const {
		const auto r1x = _CAST_ (_NULL_<ARGV<FLAG>> () ,_XVALUE_<Interface> (fake)) ;
		if (r1x == VAR_ZERO)
			return FALSE ;
		return TRUE ;
	}

	UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const {
		_DEBUG_ASSERT_ (exist ()) ;
		return fake.invoke (_FORWARD_<FORWARD_TRAITS_TYPE<UNITS>> (funcval)...) ;
	}

	inline UNIT1 operator() (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const {
		return invoke (_FORWARD_<FORWARD_TRAITS_TYPE<UNITS>> (funcval)...) ;
	}

private:
	explicit Function (const DEF<decltype (ARGVP0)> &) noexcept {
		_ZERO_ (mVariant) ;
	}

private:
	Holder &m_fake () leftvalue {
		return _CAST_ (_NULL_<ARGV<FakeHolder>> () ,mVariant) ;
	}

	const Holder &m_fake () const leftvalue {
		return _CAST_ (_NULL_<ARGV<FakeHolder>> () ,mVariant) ;
	}

private:
	template <class _ARG1 ,class... _ARGS>
	imports void static_create (const ARGV<_ARG1> & ,const PTR<TEMP<FakeHolder>> &address ,_ARGS &&...funcval) {
		_STATIC_ASSERT_ (stl::is_constructible<_ARG1 ,_ARGS &&...>::value) ;
		auto &r1x = _LOAD_ (_NULL_<ARGV<TEMP<_ARG1>>> () ,address) ;
		auto &r2x = _XVALUE_<Holder> (_CAST_ (_NULL_<ARGV<_ARG1>> () ,r1x)) ;
		auto &r3x = _XVALUE_<Holder> (_CAST_ (_NULL_<ARGV<FakeHolder>> () ,DEREF[address])) ;
		_DYNAMIC_ASSERT_ (DEPTR[r2x] == DEPTR[r3x]) ;
		_CREATE_ (DEPTR[r1x] ,_FORWARD_<_ARGS> (funcval)...) ;
	}

#pragma pop_macro ("fake")
} ;

template <class UNIT1 ,class... UNITS>
class Function<U::MEMBER_FUNCTION_HINT<UNIT1 ,UNITS...>>::Private::PureHolder
	:public Holder {
private:
	PTR<UNIT1 (UNITS...)> mFunction ;

public:
	PureHolder () = delete ;

	explicit PureHolder (const PTR<UNIT1 (UNITS...)> &func)
		:mFunction (func) {}

	void friend_copy (const PTR<TEMP<FakeHolder>> &address) const override {
		static_create (_NULL_<ARGV<PureHolder>> () ,address ,mFunction) ;
	}

	UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const override {
		return mFunction (_FORWARD_<FORWARD_TRAITS_TYPE<UNITS>> (funcval)...) ;
	}
} ;

template <class UNIT1 ,class... UNITS>
template <class UNIT_>
class Function<U::MEMBER_FUNCTION_HINT<UNIT1 ,UNITS...>>::Private::ImplHolder
	:public Holder {
private:
	PTR<UNIT_> mContext ;
	DEF<DEF<UNIT1 (UNITS...)> UNIT_::*> mFunction ;

public:
	ImplHolder () = delete ;

	explicit ImplHolder (const PTR<UNIT_> &context_ ,const DEF<DEF<UNIT1 (UNITS...)> UNIT_::*> &func)
		:mContext (context_) ,mFunction (func) {}

	void friend_copy (const PTR<TEMP<FakeHolder>> &address) const override {
		static_create (_NULL_<ARGV<ImplHolder>> () ,address ,mContext ,mFunction) ;
	}

	UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const override {
		return (DEREF[mContext].*mFunction) (_FORWARD_<FORWARD_TRAITS_TYPE<UNITS>> (funcval)...) ;
	}
} ;

template <class UNIT1 ,class... UNITS>
template <class UNIT_>
class Function<U::MEMBER_FUNCTION_HINT<UNIT1 ,UNITS...>>::Private::ImplHolder<const UNIT_>
	:public Holder {
private:
	PTR<const UNIT_> mContext ;
	DEF<DEF<UNIT1 (UNITS...) const> UNIT_::*> mFunction ;

public:
	ImplHolder () = delete ;

	explicit ImplHolder (const PTR<const UNIT_> &context_ ,const DEF<DEF<UNIT1 (UNITS...) const> UNIT_::*> &func)
		:mContext (context_) ,mFunction (func) {}

	void friend_copy (const PTR<TEMP<FakeHolder>> &address) const override {
		static_create (_NULL_<ARGV<ImplHolder>> () ,address ,mContext ,mFunction) ;
	}

	UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const override {
		return (DEREF[mContext].*mFunction) (_FORWARD_<FORWARD_TRAITS_TYPE<UNITS>> (funcval)...) ;
	}
} ;

template <class UNIT1 ,class... UNITS>
template <class UNIT_>
class Function<U::MEMBER_FUNCTION_HINT<UNIT1 ,UNITS...>>::Private::ImplHolder<PTR<UNIT_>>
	:public Holder {
private:
	PTR<UNIT_> mContext ;
	PTR<UNIT1 (PTR<UNIT_> ,UNITS...)> mFunction ;

public:
	ImplHolder () = delete ;

	explicit ImplHolder (const PTR<UNIT_> &context_ ,const PTR<UNIT1 (PTR<UNIT_> ,UNITS...)> &func)
		:mContext (context_) ,mFunction (func) {}

	void friend_copy (const PTR<TEMP<FakeHolder>> &address) const override {
		static_create (_NULL_<ARGV<ImplHolder>> () ,address ,mContext ,mFunction) ;
	}

	UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const override {
		return mFunction (mContext ,_FORWARD_<FORWARD_TRAITS_TYPE<UNITS>> (funcval)...) ;
	}
} ;

template <class ,class>
class Buffer ;

using SFLEX = ZERO ;
using SFIXED = ARGC<-1> ;
using SAUTO = ARGC<-2> ;
using SCPHAN = ARGC<-4> ;
using SMPHAN = ARGC<-5> ;

template <class UNIT ,class SIZE>
class Buffer {
	_STATIC_ASSERT_ (SIZE::value > 0) ;
	_STATIC_ASSERT_ (stl::is_complete<UNIT>::value) ;

private:
#ifdef __CSC_COMPILER_MSVC__
	//@error: fuck vs2017
	template <class ,class>
	friend class Buffer ;
#endif
	DEF<UNIT[SIZE::value]> mBuffer ;

public:
	Buffer () = default ;

	explicit Buffer (const LENGTH &len) {
		_DEBUG_ASSERT_ (len >= 0 && len <= SIZE::value) ;
	}

	implicit Buffer (const DEF<UNIT[SIZE::value]> &that)
		:Buffer (_MOVE_ (_CAST_ (_NULL_<ARGV<Buffer>> () ,that))) {
		_STATIC_WARNING_ ("noop") ;
	}

	implicit Buffer (DEF<UNIT[SIZE::value]> &&that)
		: Buffer (_MOVE_ (_CAST_ (_NULL_<ARGV<Buffer>> () ,that))) {
		_STATIC_WARNING_ ("noop") ;
	}

	ARR<UNIT> &to () leftvalue {
		return PTRTOARR[mBuffer] ;
	}

	inline implicit operator ARR<UNIT> & () leftvalue {
		return to () ;
	}

	inline implicit operator PTR<UNIT> () = delete ;

	const ARR<UNIT> &to () const leftvalue {
		return PTRTOARR[mBuffer] ;
	}

	inline implicit operator const ARR<UNIT> & () const leftvalue {
		return to () ;
	}

	inline implicit operator PTR<const UNIT> () = delete ;

	LENGTH size () const {
		return SIZE::value ;
	}

	UNIT &get (const INDEX &index) leftvalue {
		_DEBUG_ASSERT_ (index >= 0 && index < size ()) ;
		return mBuffer[index] ;
	}

	inline UNIT &operator[] (const INDEX &index) leftvalue {
		return get (index) ;
	}

	const UNIT &get (const INDEX &index) const leftvalue {
		_DEBUG_ASSERT_ (index >= 0 && index < size ()) ;
		return mBuffer[index] ;
	}

	inline const UNIT &operator[] (const INDEX &index) const leftvalue {
		return get (index) ;
	}

	INDEX at (const UNIT &item) const {
		INDEX ret = DEPTR[item] - PTRTOARR[mBuffer] ;
		if (!(ret >= 0 && ret < size ()))
			ret = VAR_NONE ;
		return _MOVE_ (ret) ;
	}

	BOOL equal (const Buffer &that) const {
		return BasicProc::mem_equal (PTRTOARR[mBuffer] ,PTRTOARR[that.mBuffer] ,SIZE::value) ;
	}

	inline BOOL operator== (const Buffer &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const Buffer &that) const {
		return !equal (that) ;
	}

	FLAG compr (const Buffer &that) const {
		return BasicProc::mem_compr (PTRTOARR[mBuffer] ,PTRTOARR[that.mBuffer] ,SIZE::value) ;
	}

	inline BOOL operator< (const Buffer &that) const {
		return BOOL (compr (that) < 0) ;
	}

	inline BOOL operator>= (const Buffer &that) const {
		return BOOL (compr (that) >= 0) ;
	}

	inline BOOL operator> (const Buffer &that) const {
		return BOOL (compr (that) > 0) ;
	}

	inline BOOL operator<= (const Buffer &that) const {
		return BOOL (compr (that) <= 0) ;
	}

	LENGTH expand_size () const {
		return 0 ;
	}

	Buffer expand (const LENGTH &len) const {
		_DEBUG_ASSERT_ (FALSE) ;
		return Buffer () ;
	}

	void swap (Buffer &that) {
		BasicProc::mem_swap (PTRTOARR[mBuffer] ,PTRTOARR[that.mBuffer] ,SIZE::value) ;
	}
} ;

template <class UNIT>
class Buffer<UNIT ,SFIXED> final {
	_STATIC_ASSERT_ (stl::is_complete<UNIT>::value) ;

private:
	PTR<ARR<UNIT>> mBuffer ;
	LENGTH mSize ;

public:
	Buffer ()
		:Buffer (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	explicit Buffer (const LENGTH &len)
		:Buffer (ARGVP0) {
		if (len == 0)
			return ;
		_DEBUG_ASSERT_ (len > 0) ;
		auto rax = GlobalHeap::alloc (_NULL_<ARGV<TEMP<UNIT>>> () ,len) ;
		ScopedBuild<ARR<UNIT>> ANONYMOUS (rax ,len) ;
		auto &r1x = _LOAD_ (_NULL_<ARGV<ARR<UNIT>>> () ,_XVALUE_<PTR<ARR<TEMP<UNIT>>>> (rax)) ;
		mBuffer = DEPTR[r1x] ;
		mSize = len ;
		rax = NULL ;
	}

	inline ~Buffer () noexcept {
		if (mBuffer == NULL)
			return ;
		for (auto &&i : _RANGE_ (0 ,mSize)) {
			_STATIC_UNUSED_ (i) ;
			DEREF[mBuffer][i].~UNIT () ;
		}
		GlobalHeap::free (mBuffer) ;
		mBuffer = NULL ;
		mSize = 0 ;
	}

	inline Buffer (const Buffer &) = delete ;
	inline Buffer &operator= (const Buffer &) = delete ;

	inline Buffer (Buffer &&) = delete ;
	inline Buffer &operator= (Buffer &&) = delete ;

	ARR<UNIT> &to () leftvalue {
		if (mBuffer == NULL)
			return _NULL_<ARR<UNIT>> () ;
		return DEREF[mBuffer] ;
	}

	inline implicit operator ARR<UNIT> & () leftvalue {
		return to () ;
	}

	inline implicit operator PTR<UNIT> () = delete ;

	const ARR<UNIT> &to () const leftvalue {
		if (mBuffer == NULL)
			return _NULL_<ARR<UNIT>> () ;
		return DEREF[mBuffer] ;
	}

	inline implicit operator const ARR<UNIT> & () const leftvalue {
		return to () ;
	}

	inline implicit operator PTR<const UNIT> () = delete ;

	LENGTH size () const {
		return mSize ;
	}

	UNIT &get (const INDEX &index) leftvalue {
		_DEBUG_ASSERT_ (index >= 0 && index < size ()) ;
		return DEREF[mBuffer][index] ;
	}

	inline UNIT &operator[] (const INDEX &index) leftvalue {
		return get (index) ;
	}

	const UNIT &get (const INDEX &index) const leftvalue {
		_DEBUG_ASSERT_ (index >= 0 && index < size ()) ;
		return DEREF[mBuffer][index] ;
	}

	inline const UNIT &operator[] (const INDEX &index) const leftvalue {
		return get (index) ;
	}

	INDEX at (const UNIT &item) const {
		INDEX ret = DEPTR[item] - DEREF[mBuffer] ;
		if (!(ret >= 0 && ret < size ()))
			ret = VAR_NONE ;
		return _MOVE_ (ret) ;
	}

	BOOL equal (const Buffer &that) const {
		if (mSize != that.mSize)
			return FALSE ;
		if (!BasicProc::mem_equal (DEREF[mBuffer] ,DEREF[that.mBuffer] ,that.mSize))
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const Buffer &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const Buffer &that) const {
		return !equal (that) ;
	}

	FLAG compr (const Buffer &that) const {
		const auto r1x = _MIN_ (mSize ,that.mSize) ;
		const auto r2x = BasicProc::mem_compr (DEREF[mBuffer] ,DEREF[that.mBuffer] ,r1x) ;
		if (r2x != 0)
			return r2x ;
		return U::OPERATOR_COMPR::invoke (mSize ,that.mSize) ;
	}

	inline BOOL operator< (const Buffer &that) const {
		return BOOL (compr (that) < 0) ;
	}

	inline BOOL operator>= (const Buffer &that) const {
		return BOOL (compr (that) >= 0) ;
	}

	inline BOOL operator> (const Buffer &that) const {
		return BOOL (compr (that) > 0) ;
	}

	inline BOOL operator<= (const Buffer &that) const {
		return BOOL (compr (that) <= 0) ;
	}

	LENGTH expand_size () const {
		return 0 ;
	}

	Buffer<UNIT ,SAUTO> expand (const LENGTH &len) const {
		_DYNAMIC_ASSERT_ (FALSE) ;
		return Buffer<UNIT ,SAUTO> () ;
	}

	void swap (Buffer<UNIT ,SAUTO> &that) {
		_DYNAMIC_ASSERT_ (FALSE) ;
	}

	void swap (Buffer &that) {
		_DYNAMIC_ASSERT_ (mSize == that.mSize) ;
		BasicProc::mem_swap (PTRTOARR[mBuffer] ,PTRTOARR[that.mBuffer] ,mSize) ;
	}

private:
	explicit Buffer (const DEF<decltype (ARGVP0)> &) noexcept
		:mBuffer (NULL) ,mSize (0) {}
} ;

template <class UNIT>
using FixedBuffer = CAST_TRAITS_TYPE<Buffer<REMOVE_CVR_TYPE<UNIT> ,SFIXED> ,UNIT> ;

template <class UNIT>
class Buffer<UNIT ,SAUTO> ;

template <class UNIT>
class Buffer<SPECIALIZATION<UNIT ,FALSE> ,SAUTO> {
	_STATIC_ASSERT_ (stl::is_complete<UNIT>::value) ;

private:
	using SPECIALIZATION_THIS = Buffer<UNIT ,SAUTO> ;

private:
	friend SPECIALIZATION_THIS ;
	PTR<ARR<UNIT>> mBuffer ;
	LENGTH mSize ;

public:
	Buffer ()
		:Buffer (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	explicit Buffer (const LENGTH &len)
		:Buffer (ARGVP0) {
		if (len == 0)
			return ;
		_DEBUG_ASSERT_ (len > 0) ;
		auto rax = GlobalHeap::alloc (_NULL_<ARGV<TEMP<UNIT>>> () ,len) ;
		ScopedBuild<ARR<UNIT>> ANONYMOUS (rax ,len) ;
		auto &r1x = _LOAD_ (_NULL_<ARGV<ARR<UNIT>>> () ,_XVALUE_<PTR<ARR<TEMP<UNIT>>>> (rax)) ;
		mBuffer = DEPTR[r1x] ;
		mSize = len ;
		rax = NULL ;
	}

	inline ~Buffer () noexcept {
		if (mBuffer == NULL)
			return ;
		for (auto &&i : _RANGE_ (0 ,mSize)) {
			_STATIC_UNUSED_ (i) ;
			DEREF[mBuffer][i].~UNIT () ;
		}
		GlobalHeap::free (mBuffer) ;
		mBuffer = NULL ;
		mSize = 0 ;
	}

	inline Buffer (const Buffer &) = delete ;
	inline Buffer &operator= (const Buffer &) = delete ;

	inline Buffer (Buffer &&that) noexcept
		:Buffer (ARGVP0) {
		mBuffer = _EXCHANGE_ (that.mBuffer) ;
		mSize = _EXCHANGE_ (that.mSize) ;
	}

	inline Buffer &operator= (Buffer &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~Buffer () ;
			new (this) Buffer (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

private:
	explicit Buffer (const DEF<decltype (ARGVP0)> &) noexcept
		: mBuffer (NULL) ,mSize (0) {}
} ;

template <class UNIT>
class Buffer<SPECIALIZATION<UNIT ,TRUE> ,SAUTO> {
	_STATIC_ASSERT_ (stl::is_complete<UNIT>::value) ;

private:
	using SPECIALIZATION_THIS = Buffer<UNIT ,SAUTO> ;

private:
	friend SPECIALIZATION_THIS ;
	PTR<ARR<UNIT>> mBuffer ;
	LENGTH mSize ;

public:
	Buffer ()
		:Buffer (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	explicit Buffer (const LENGTH &len)
		:Buffer (ARGVP0) {
		if (len == 0)
			return ;
		_DEBUG_ASSERT_ (len > 0) ;
		auto rax = GlobalHeap::alloc (_NULL_<ARGV<TEMP<UNIT>>> () ,len) ;
		ScopedBuild<ARR<UNIT>> ANONYMOUS (rax ,len) ;
		auto &r1x = _LOAD_ (_NULL_<ARGV<ARR<UNIT>>> () ,_XVALUE_<PTR<ARR<TEMP<UNIT>>>> (rax)) ;
		mBuffer = DEPTR[r1x] ;
		mSize = len ;
		rax = NULL ;
	}

	inline ~Buffer () noexcept {
		if (mBuffer == NULL)
			return ;
		for (auto &&i : _RANGE_ (0 ,mSize)) {
			_STATIC_UNUSED_ (i) ;
			DEREF[mBuffer][i].~UNIT () ;
		}
		GlobalHeap::free (mBuffer) ;
		mBuffer = NULL ;
		mSize = 0 ;
	}

	inline Buffer (const Buffer &that)
		:Buffer (ARGVP0) {
		if (that.mBuffer == NULL)
			return ;
		auto rax = GlobalHeap::alloc (_NULL_<ARGV<TEMP<UNIT>>> () ,that.mSize) ;
		ScopedBuild<ARR<UNIT>> ANONYMOUS (rax ,DEREF[that.mBuffer] ,that.mSize) ;
		auto &r1x = _LOAD_ (_NULL_<ARGV<ARR<UNIT>>> () ,_XVALUE_<PTR<ARR<TEMP<UNIT>>>> (rax)) ;
		mBuffer = DEPTR[r1x] ;
		mSize = that.mSize ;
		rax = NULL ;
	}

	inline Buffer &operator= (const Buffer &that) {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~Buffer () ;
			new (this) Buffer (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	inline Buffer (Buffer &&that) noexcept
		:Buffer (ARGVP0) {
		mBuffer = _EXCHANGE_ (that.mBuffer) ;
		mSize = _EXCHANGE_ (that.mSize) ;
	}

	inline Buffer &operator= (Buffer &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~Buffer () ;
			new (this) Buffer (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

private:
	explicit Buffer (const DEF<decltype (ARGVP0)> &) noexcept
		: mBuffer (NULL) ,mSize (0) {}
} ;

template <class UNIT>
class Buffer<UNIT ,SAUTO> final
	:private Buffer<SPECIALIZATION<UNIT ,(stl::is_copy_constructible<UNIT>::value && stl::is_nothrow_move_constructible<UNIT>::value)> ,SAUTO> {
private:
	using SPECIALIZATION_BASE = Buffer<SPECIALIZATION<UNIT ,(stl::is_copy_constructible<UNIT>::value && stl::is_nothrow_move_constructible<UNIT>::value)> ,SAUTO> ;

private:
	friend SPECIALIZATION_BASE ;
	using SPECIALIZATION_BASE::mBuffer ;
	using SPECIALIZATION_BASE::mSize ;

public:
	Buffer () = default ;

	explicit Buffer (const LENGTH &len)
		:SPECIALIZATION_BASE (len) {
		_STATIC_WARNING_ ("noop") ;
	}

	ARR<UNIT> &to () leftvalue {
		if (mBuffer == NULL)
			return _NULL_<ARR<UNIT>> () ;
		return DEREF[mBuffer] ;
	}

	inline implicit operator ARR<UNIT> & () leftvalue {
		return to () ;
	}

	inline implicit operator PTR<UNIT> () = delete ;

	const ARR<UNIT> &to () const leftvalue {
		if (mBuffer == NULL)
			return _NULL_<ARR<UNIT>> () ;
		return DEREF[mBuffer] ;
	}

	inline implicit operator const ARR<UNIT> & () const leftvalue {
		return to () ;
	}

	inline implicit operator PTR<const UNIT> () = delete ;

	LENGTH size () const {
		return mSize ;
	}

	UNIT &get (const INDEX &index) leftvalue {
		_DEBUG_ASSERT_ (index >= 0 && index < size ()) ;
		return DEREF[mBuffer][index] ;
	}

	inline UNIT &operator[] (const INDEX &index) leftvalue {
		return get (index) ;
	}

	const UNIT &get (const INDEX &index) const leftvalue {
		_DEBUG_ASSERT_ (index >= 0 && index < size ()) ;
		return DEREF[mBuffer][index] ;
	}

	inline const UNIT &operator[] (const INDEX &index) const leftvalue {
		return get (index) ;
	}

	INDEX at (const UNIT &item) const {
		INDEX ret = DEPTR[item] - DEREF[mBuffer] ;
		if (!(ret >= 0 && ret < size ()))
			ret = VAR_NONE ;
		return _MOVE_ (ret) ;
	}

	BOOL equal (const Buffer &that) const {
		if (mSize != that.mSize)
			return FALSE ;
		if (!BasicProc::mem_equal (DEREF[mBuffer] ,DEREF[that.mBuffer] ,that.mSize))
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const Buffer &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const Buffer &that) const {
		return !equal (that) ;
	}

	FLAG compr (const Buffer &that) const {
		const auto r1x = _MIN_ (mSize ,that.mSize) ;
		const auto r2x = BasicProc::mem_compr (DEREF[mBuffer] ,DEREF[that.mBuffer] ,r1x) ;
		if (r2x != 0)
			return r2x ;
		return U::OPERATOR_COMPR::invoke (mSize ,that.mSize) ;
	}

	inline BOOL operator< (const Buffer &that) const {
		return BOOL (compr (that) < 0) ;
	}

	inline BOOL operator>= (const Buffer &that) const {
		return BOOL (compr (that) >= 0) ;
	}

	inline BOOL operator> (const Buffer &that) const {
		return BOOL (compr (that) > 0) ;
	}

	inline BOOL operator<= (const Buffer &that) const {
		return BOOL (compr (that) <= 0) ;
	}

	LENGTH expand_size () const {
		const auto r1x = LENGTH (mSize * MATH_SQRT2) ;
		const auto r2x = mSize + DEFAULT_RECURSIVE_SIZE::value ;
		return _MAX_ (r1x ,r2x) ;
	}

	Buffer expand (const LENGTH &len) const {
		return Buffer (len) ;
	}

	void swap (Buffer &that) {
		_SWAP_ (mBuffer ,that.mBuffer) ;
		_SWAP_ (mSize ,that.mSize) ;
	}
} ;

template <class UNIT>
using AutoBuffer = CAST_TRAITS_TYPE<Buffer<REMOVE_CVR_TYPE<UNIT> ,SAUTO> ,UNIT> ;

template <class UNIT>
class Buffer<UNIT ,SCPHAN> final {
	_STATIC_ASSERT_ (stl::is_complete<UNIT>::value) ;

private:
	PTR<const ARR<UNIT>> mBuffer ;
	LENGTH mSize ;

public:
	Buffer ()
		:Buffer (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	explicit Buffer (const LENGTH &len)
		:Buffer (ARGVP0) {
		_DEBUG_ASSERT_ (len == 0) ;
	}

	inline ~Buffer () noexcept {
		if (mBuffer == NULL)
			return ;
		mBuffer = NULL ;
		mSize = 0 ;
	}

	inline Buffer (const Buffer &) = delete ;
	inline Buffer &operator= (const Buffer &) = delete ;

	inline Buffer (Buffer &&that) noexcept
		:Buffer (ARGVP0) {
		mBuffer = _EXCHANGE_ (that.mBuffer) ;
		mSize = _EXCHANGE_ (that.mSize) ;
	}

	inline Buffer &operator= (Buffer &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~Buffer () ;
			new (this) Buffer (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	const ARR<UNIT> &to () const leftvalue {
		if (mBuffer == NULL)
			return _NULL_<ARR<UNIT>> () ;
		const auto r1x = static_cast<PTR<const ARR<UNIT>>> (mBuffer) ;
		return DEREF[r1x] ;
	}

	inline implicit operator const ARR<UNIT> & () const leftvalue {
		return to () ;
	}

	inline implicit operator PTR<const UNIT> () = delete ;

	LENGTH size () const {
		return mSize ;
	}

	const UNIT &get (const INDEX &index) const leftvalue {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
		_DEBUG_ASSERT_ (index >= 0 && index < size ()) ;
		const auto r1x = static_cast<PTR<const ARR<UNIT>>> (mBuffer) ;
		return DEREF[r1x][index] ;
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
	}

	inline const UNIT &operator[] (const INDEX &index) const leftvalue {
		return get (index) ;
	}

	INDEX at (const UNIT &item) const {
		INDEX ret = DEPTR[item] - DEREF[mBuffer] ;
		if (!(ret >= 0 && ret < size ()))
			ret = VAR_NONE ;
		return _MOVE_ (ret) ;
	}

	BOOL equal (const Buffer &that) const {
		if (mSize != that.mSize)
			return FALSE ;
		if (!BasicProc::mem_equal (DEREF[mBuffer] ,DEREF[that.mBuffer] ,that.mSize))
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const Buffer &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const Buffer &that) const {
		return !equal (that) ;
	}

	FLAG compr (const Buffer &that) const {
		const auto r1x = _MIN_ (mSize ,that.mSize) ;
		const auto r2x = BasicProc::mem_compr (DEREF[mBuffer] ,DEREF[that.mBuffer] ,r1x) ;
		if (r2x != 0)
			return r2x ;
		return U::OPERATOR_COMPR::invoke (mSize ,that.mSize) ;
	}

	inline BOOL operator< (const Buffer &that) const {
		return BOOL (compr (that) < 0) ;
	}

	inline BOOL operator>= (const Buffer &that) const {
		return BOOL (compr (that) >= 0) ;
	}

	inline BOOL operator> (const Buffer &that) const {
		return BOOL (compr (that) > 0) ;
	}

	inline BOOL operator<= (const Buffer &that) const {
		return BOOL (compr (that) <= 0) ;
	}

	LENGTH expand_size () const {
		return 0 ;
	}

	Buffer expand (const LENGTH &len) const {
		_DEBUG_ASSERT_ (FALSE) ;
		return Buffer () ;
	}

	void swap (Buffer &that) {
		_SWAP_ (mBuffer ,that.mBuffer) ;
		_SWAP_ (mSize ,that.mSize) ;
	}

private:
	explicit Buffer (const DEF<decltype (ARGVP0)> &) noexcept
		: mBuffer (NULL) ,mSize (0) {}

	explicit Buffer (const PTR<const ARR<UNIT>> &buffer ,const LENGTH &size_)
		: Buffer (ARGVP0) {
		if (size_ == 0)
			return ;
		_DEBUG_ASSERT_ (size_ > 0) ;
		mBuffer = buffer ;
		mSize = size_ ;
	}

public:
	//@warn: phantom means deliver pointer without holder
	imports Buffer make (const ARR<UNIT> &src ,const LENGTH &len) side_effects {
		return Buffer (DEPTR[src] ,len) ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<stl::is_bounded_array_of<UNIT ,_ARG1>::value>>
	imports Buffer make (_ARG1 &val) side_effects {
		return make (PTRTOARR[val] ,_COUNTOF_ (_ARG1)) ;
	}

	template <class _ARG1>
	imports Buffer make (const Buffer<UNIT ,_ARG1> &val) {
		return make (val ,val.size ()) ;
	}

	template <class _ARG1 ,class _ARG2 ,class = ENABLE_TYPE<stl::is_same<UNIT ,BYTE>::value && !stl::is_same<_ARG1 ,BYTE>::value>>
	imports Buffer make (const Buffer<_ARG1 ,_ARG2> &val) {
		_STATIC_ASSERT_ (U::IS_SAFE_ALIASING_HELP<ARR<BYTE> ,ARR<_ARG1>>::value) ;
		if (val.size () == 0)
			return Buffer () ;
		auto &r1x = _LOAD_ (_NULL_<ARGV<ARR<BYTE>>> () ,DEPTR[val.self]) ;
		return make (r1x ,(val.size () * _SIZEOF_ (_ARG1))) ;
	}
} ;

template <class UNIT>
class Buffer<UNIT ,SMPHAN> final {
	_STATIC_ASSERT_ (stl::is_complete<UNIT>::value) ;

private:
	PTR<ARR<UNIT>> mBuffer ;
	LENGTH mSize ;

public:
	Buffer ()
		:Buffer (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	explicit Buffer (const LENGTH &len)
		:Buffer (ARGVP0) {
		_DEBUG_ASSERT_ (len == 0) ;
	}

	inline ~Buffer () noexcept {
		if (mBuffer == NULL)
			return ;
		mBuffer = NULL ;
		mSize = 0 ;
	}

	inline Buffer (const Buffer &) = delete ;
	inline Buffer &operator= (const Buffer &) = delete ;

	inline Buffer (Buffer &&that) noexcept
		:Buffer (ARGVP0) {
		mBuffer = _EXCHANGE_ (that.mBuffer) ;
		mSize = _EXCHANGE_ (that.mSize) ;
	}

	inline Buffer &operator= (Buffer &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~Buffer () ;
			new (this) Buffer (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	ARR<UNIT> &to () const leftvalue {
		if (mBuffer == NULL)
			return _NULL_<ARR<UNIT>> () ;
		const auto r1x = static_cast<PTR<ARR<UNIT>>> (mBuffer) ;
		return DEREF[r1x] ;
	}

	inline implicit operator ARR<UNIT> & () const leftvalue {
		return to () ;
	}

	inline implicit operator PTR<UNIT> () = delete ;

	LENGTH size () const {
		return mSize ;
	}

	UNIT &get (const INDEX &index) const leftvalue {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
		_DEBUG_ASSERT_ (index >= 0 && index < size ()) ;
		const auto r1x = static_cast<PTR<ARR<UNIT>>> (mBuffer) ;
		return DEREF[r1x][index] ;
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
	}

	inline UNIT &operator[] (const INDEX &index) const leftvalue {
		return get (index) ;
	}

	INDEX at (const UNIT &item) const {
		INDEX ret = DEPTR[item] - DEREF[mBuffer] ;
		if (!(ret >= 0 && ret < size ()))
			ret = VAR_NONE ;
		return _MOVE_ (ret) ;
	}

	BOOL equal (const Buffer &that) const {
		if (mSize != that.mSize)
			return FALSE ;
		if (!BasicProc::mem_equal (DEREF[mBuffer] ,DEREF[that.mBuffer] ,that.mSize))
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const Buffer &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const Buffer &that) const {
		return !equal (that) ;
	}

	FLAG compr (const Buffer &that) const {
		const auto r1x = _MIN_ (mSize ,that.mSize) ;
		const auto r2x = BasicProc::mem_compr (DEREF[mBuffer] ,DEREF[that.mBuffer] ,r1x) ;
		if (r2x != 0)
			return r2x ;
		return U::OPERATOR_COMPR::invoke (mSize ,that.mSize) ;
	}

	inline BOOL operator< (const Buffer &that) const {
		return BOOL (compr (that) < 0) ;
	}

	inline BOOL operator>= (const Buffer &that) const {
		return BOOL (compr (that) >= 0) ;
	}

	inline BOOL operator> (const Buffer &that) const {
		return BOOL (compr (that) > 0) ;
	}

	inline BOOL operator<= (const Buffer &that) const {
		return BOOL (compr (that) <= 0) ;
	}

	LENGTH expand_size () const {
		return 0 ;
	}

	Buffer expand (const LENGTH &len) const {
		_DEBUG_ASSERT_ (FALSE) ;
		return Buffer () ;
	}

	void swap (Buffer &that) {
		_SWAP_ (mBuffer ,that.mBuffer) ;
		_SWAP_ (mSize ,that.mSize) ;
	}

private:
	explicit Buffer (const DEF<decltype (ARGVP0)> &) noexcept
		: mBuffer (NULL) ,mSize (0) {}

	explicit Buffer (const PTR<ARR<UNIT>> &buffer ,const LENGTH &size_)
		: Buffer (ARGVP0) {
		if (size_ == 0)
			return ;
		_DEBUG_ASSERT_ (size_ > 0) ;
		mBuffer = buffer ;
		mSize = size_ ;
	}

public:
	//@warn: phantom means deliver pointer without holder
	imports Buffer make (ARR<UNIT> &src ,const LENGTH &len) side_effects {
		return Buffer (DEPTR[src] ,len) ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<stl::is_bounded_array_of<UNIT ,_ARG1>::value>>
	imports Buffer make (_ARG1 &val) side_effects {
		return make (PTRTOARR[val] ,_COUNTOF_ (_ARG1)) ;
	}

	template <class _ARG1>
	imports Buffer make (Buffer<UNIT ,_ARG1> &val) side_effects {
		return make (val.self ,val.size ()) ;
	}

	imports Buffer make (const Buffer<UNIT ,SMPHAN> &val) {
		return make (val.self ,val.size ()) ;
	}

	template <class _ARG1 ,class _ARG2 ,class = ENABLE_TYPE<stl::is_same<UNIT ,BYTE>::value && !stl::is_same<_ARG1 ,BYTE>::value>>
	imports Buffer make (Buffer<_ARG1 ,_ARG2> &val) side_effects {
		_STATIC_ASSERT_ (U::IS_SAFE_ALIASING_HELP<ARR<BYTE> ,ARR<_ARG1>>::value) ;
		if (val.size () == 0)
			return Buffer () ;
		auto &r1x = _LOAD_ (_NULL_<ARGV<ARR<BYTE>>> () ,DEPTR[val.self]) ;
		return make (r1x ,(val.size () * _SIZEOF_ (_ARG1))) ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<stl::is_same<UNIT ,BYTE>::value && !stl::is_same<_ARG1 ,BYTE>::value>>
	imports Buffer make (const Buffer<_ARG1 ,SMPHAN> &val) {
		_STATIC_ASSERT_ (U::IS_SAFE_ALIASING_HELP<ARR<BYTE> ,ARR<_ARG1>>::value) ;
		if (val.size () == 0)
			return Buffer () ;
		auto &r1x = _LOAD_ (_NULL_<ARGV<ARR<BYTE>>> () ,DEPTR[val.self]) ;
		return make (r1x ,(val.size () * _SIZEOF_ (_ARG1))) ;
	}
} ;

template <class UNIT>
using PhanBuffer = Buffer<REMOVE_CONST_TYPE<UNIT> ,CONDITIONAL_TYPE<(stl::is_const<UNIT>::value) ,SCPHAN ,SMPHAN>> ;

template <class ,class>
class Allocator ;

template <class UNIT ,class SIZE>
class Allocator<SPECIALIZATION<UNIT ,FALSE ,FALSE> ,SIZE> {
#pragma push_macro ("spec")
#undef spec
#define spec m_spec ()

private:
	using SPECIALIZATION_THIS = Allocator<UNIT ,SIZE> ;

	//@warn: memory alignment reduce utilization ratio of memory
	struct NODE {
		TEMP<UNIT> mValue ;
		INDEX mNext ;
	} ;

private:
	friend SPECIALIZATION_THIS ;
	Buffer<NODE ,SIZE> mAllocator ;
	LENGTH mSize ;
	LENGTH mLength ;
	INDEX mFree ;

public:
	Allocator ()
		:Allocator (ARGVP0 ,0) {
		spec.update_reserve (mSize ,mFree) ;
	}

	explicit Allocator (const LENGTH &len)
		:Allocator (ARGVP0 ,len) {
		spec.update_reserve (mSize ,mFree) ;
	}

	inline ~Allocator () noexcept {
		if (mAllocator.size () == 0)
			return ;
		while (TRUE) {
			if (mSize <= 0)
				break ;
			if switch_once (TRUE) {
				INDEX ix = mSize - 1 ;
				if (mAllocator[ix].mNext != VAR_USED)
					discard ;
				_DESTROY_ (DEPTR[mAllocator[ix].mValue]) ;
			}
			mSize-- ;
		}
		mLength = 0 ;
		mFree = VAR_NONE ;
	}

	inline Allocator (const Allocator &) = delete ;
	inline Allocator &operator= (const Allocator &) = delete ;

	inline Allocator (Allocator &&) = delete ;
	inline Allocator &operator= (Allocator &&) = delete ;

private:
	explicit Allocator (const DEF<decltype (ARGVP0)> & ,const LENGTH &len)
		:mAllocator (len) ,mSize (0) ,mLength (0) ,mFree (VAR_NONE) {}

private:
	SPECIALIZATION_THIS &m_spec () leftvalue {
		return DEREF[static_cast<PTR<SPECIALIZATION_THIS>> (this)] ;
	}

	const SPECIALIZATION_THIS &m_spec () const leftvalue {
		return DEREF[static_cast<PTR<const SPECIALIZATION_THIS>> (this)] ;
	}

#pragma pop_macro ("spec")
} ;

template <class UNIT ,class SIZE>
class Allocator<SPECIALIZATION<UNIT ,FALSE ,TRUE> ,SIZE> {
#pragma push_macro ("spec")
#undef spec
#define spec m_spec ()

private:
	using SPECIALIZATION_THIS = Allocator<UNIT ,SIZE> ;

	//@warn: memory alignment reduce utilization ratio of memory
	struct NODE {
		TEMP<UNIT> mValue ;
		INDEX mNext ;
	} ;

private:
	friend SPECIALIZATION_THIS ;
	Buffer<NODE ,SIZE> mAllocator ;
	LENGTH mSize ;
	LENGTH mLength ;
	INDEX mFree ;

public:
	Allocator ()
		:Allocator (ARGVP0 ,0) {
		spec.update_reserve (mSize ,mFree) ;
	}

	explicit Allocator (const LENGTH &len)
		:Allocator (ARGVP0 ,len) {
		spec.update_reserve (mSize ,mFree) ;
	}

	inline ~Allocator () noexcept {
		if (mAllocator.size () == 0)
			return ;
		while (TRUE) {
			if (mSize <= 0)
				break ;
			if switch_once (TRUE) {
				INDEX ix = mSize - 1 ;
				if (mAllocator[ix].mNext != VAR_USED)
					discard ;
				_DESTROY_ (DEPTR[mAllocator[ix].mValue]) ;
			}
			mSize-- ;
		}
		mLength = 0 ;
		mFree = VAR_NONE ;
	}

	inline Allocator (const Allocator &) = delete ;
	inline Allocator &operator= (const Allocator &) = delete ;

	inline Allocator (Allocator &&that) noexcept
		:Allocator (ARGVP0 ,_MOVE_ (that.mAllocator)) {
		if (mAllocator.size () != that.mAllocator.size ())
			mSize = _EXCHANGE_ (that.mSize) ;
		const auto r1x = that.mSize - mSize ;
		const auto r2x = VAR_ZERO ;
		mSize += _EBOOL_ (stl::is_pod<UNIT>::value) * _MAX_ (r1x ,r2x) ;
		while (TRUE) {
			if (mSize >= that.mSize)
				break ;
			if switch_once (TRUE) {
				INDEX ix = mSize ;
				if (mAllocator[ix].mNext != VAR_USED)
					discard ;
				_CREATE_ (DEPTR[mAllocator[ix].mValue] ,_MOVE_ (_CAST_ (_NULL_<ARGV<UNIT>> () ,that.mAllocator[ix].mValue))) ;
			}
			mSize++ ;
		}
		mLength = _EXCHANGE_ (that.mLength) ;
		mFree = _EXCHANGE_ (that.mFree ,VAR_NONE) ;
	}

	inline Allocator &operator= (Allocator &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~Allocator () ;
			new (this) Allocator (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

private:
	explicit Allocator (const DEF<decltype (ARGVP0)> & ,const LENGTH &len)
		:mAllocator (len) ,mSize (0) ,mLength (0) ,mFree (VAR_NONE) {}

	explicit Allocator (const DEF<decltype (ARGVP0)> & ,Buffer<NODE ,SIZE> &&allocator_)
		:mAllocator (_MOVE_ (allocator_)) ,mSize (0) ,mLength (0) ,mFree (VAR_NONE) {}

private:
	SPECIALIZATION_THIS &m_spec () leftvalue {
		return DEREF[static_cast<PTR<SPECIALIZATION_THIS>> (this)] ;
	}

	const SPECIALIZATION_THIS &m_spec () const leftvalue {
		return DEREF[static_cast<PTR<const SPECIALIZATION_THIS>> (this)] ;
	}

#pragma pop_macro ("spec")
} ;

template <class UNIT ,class SIZE>
class Allocator<SPECIALIZATION<UNIT ,TRUE ,TRUE> ,SIZE> {
#pragma push_macro ("spec")
#undef spec
#define spec m_spec ()

private:
	using SPECIALIZATION_THIS = Allocator<UNIT ,SIZE> ;

	//@warn: memory alignment reduce utilization ratio of memory
	struct NODE {
		TEMP<UNIT> mValue ;
		INDEX mNext ;
	} ;

private:
	friend SPECIALIZATION_THIS ;
	Buffer<NODE ,SIZE> mAllocator ;
	LENGTH mSize ;
	LENGTH mLength ;
	INDEX mFree ;

public:
	Allocator ()
		:Allocator (ARGVP0 ,0) {
		spec.update_reserve (mSize ,mFree) ;
	}

	explicit Allocator (const LENGTH &len)
		:Allocator (ARGVP0 ,len) {
		spec.update_reserve (mSize ,mFree) ;
	}

	inline ~Allocator () noexcept {
		if (mAllocator.size () == 0)
			return ;
		while (TRUE) {
			if (mSize <= 0)
				break ;
			if switch_once (TRUE) {
				INDEX ix = mSize - 1 ;
				if (mAllocator[ix].mNext != VAR_USED)
					discard ;
				_DESTROY_ (DEPTR[mAllocator[ix].mValue]) ;
			}
			mSize-- ;
		}
		mLength = 0 ;
		mFree = VAR_NONE ;
	}

	inline Allocator (const Allocator &that)
		:Allocator (ARGVP0 ,_MOVE_ (that.mAllocator)) {
		if (mAllocator.size () != that.mAllocator.size ())
			mSize = that.mSize ;
		const auto r1x = that.mSize - mSize ;
		const auto r2x = VAR_ZERO ;
		mSize += _EBOOL_ (stl::is_pod<UNIT>::value) * _MAX_ (r1x ,r2x) ;
		while (TRUE) {
			if (mSize >= that.mSize)
				break ;
			if switch_once (TRUE) {
				INDEX ix = mSize ;
				if (mAllocator[ix].mNext != VAR_USED)
					discard ;
				_CREATE_ (DEPTR[mAllocator[ix].mValue] ,_MOVE_ (_CAST_ (_NULL_<ARGV<UNIT>> () ,that.mAllocator[ix].mValue))) ;
			}
			mSize++ ;
		}
		mLength = that.mLength ;
		mFree = that.mFree ;
	}

	inline Allocator &operator= (const Allocator &that) {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~Allocator () ;
			new (this) Allocator (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	inline Allocator (Allocator &&that) noexcept
		:Allocator (ARGVP0 ,_MOVE_ (that.mAllocator)) {
		if (mAllocator.size () != that.mAllocator.size ())
			mSize = _EXCHANGE_ (that.mSize) ;
		const auto r1x = that.mSize - mSize ;
		const auto r2x = VAR_ZERO ;
		mSize += _EBOOL_ (stl::is_pod<UNIT>::value) * _MAX_ (r1x ,r2x) ;
		while (TRUE) {
			if (mSize >= that.mSize)
				break ;
			if switch_once (TRUE) {
				INDEX ix = mSize ;
				if (mAllocator[ix].mNext != VAR_USED)
					discard ;
				_CREATE_ (DEPTR[mAllocator[ix].mValue] ,_MOVE_ (_CAST_ (_NULL_<ARGV<UNIT>> () ,that.mAllocator[ix].mValue))) ;
			}
			mSize++ ;
		}
		mLength = _EXCHANGE_ (that.mLength) ;
		mFree = _EXCHANGE_ (that.mFree ,VAR_NONE) ;
	}

	inline Allocator &operator= (Allocator &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~Allocator () ;
			new (this) Allocator (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

private:
	explicit Allocator (const DEF<decltype (ARGVP0)> & ,const LENGTH &len)
		:mAllocator (len) ,mSize (0) ,mLength (0) ,mFree (VAR_NONE) {}

	explicit Allocator (const DEF<decltype (ARGVP0)> & ,const Buffer<NODE ,SIZE> &allocator_)
		:mAllocator (_MOVE_ (allocator_)) ,mSize (0) ,mLength (0) ,mFree (VAR_NONE) {}

	explicit Allocator (const DEF<decltype (ARGVP0)> & ,Buffer<NODE ,SIZE> &&allocator_)
		:mAllocator (_MOVE_ (allocator_)) ,mSize (0) ,mLength (0) ,mFree (VAR_NONE) {}

private:
	SPECIALIZATION_THIS &m_spec () leftvalue {
		return DEREF[static_cast<PTR<SPECIALIZATION_THIS>> (this)] ;
	}

	const SPECIALIZATION_THIS &m_spec () const leftvalue {
		return DEREF[static_cast<PTR<const SPECIALIZATION_THIS>> (this)] ;
	}

#pragma pop_macro ("spec")
} ;

template <class UNIT ,class SIZE>
class Allocator final
	:private Allocator<SPECIALIZATION<UNIT ,(stl::is_copy_constructible<Buffer<UNIT ,SIZE>>::value && stl::is_nothrow_move_constructible<Buffer<UNIT ,SIZE>>::value) ,stl::is_nothrow_move_constructible<Buffer<UNIT ,SIZE>>::value> ,SIZE> {
	_STATIC_ASSERT_ (stl::is_nothrow_move_constructible<UNIT>::value) ;
	_STATIC_ASSERT_ (stl::is_nothrow_move_assignable<UNIT>::value) ;

private:
	using SPECIALIZATION_BASE = Allocator<SPECIALIZATION<UNIT ,(stl::is_copy_constructible<Buffer<UNIT ,SIZE>>::value && stl::is_nothrow_move_constructible<Buffer<UNIT ,SIZE>>::value) ,stl::is_nothrow_move_constructible<Buffer<UNIT ,SIZE>>::value> ,SIZE> ;
	using NODE = typename SPECIALIZATION_BASE::NODE ;

private:
	friend SPECIALIZATION_BASE ;
	using SPECIALIZATION_BASE::mAllocator ;
	using SPECIALIZATION_BASE::mSize ;
	using SPECIALIZATION_BASE::mLength ;
	using SPECIALIZATION_BASE::mFree ;

public:
	Allocator () = default ;

	explicit Allocator (const LENGTH &len)
		:SPECIALIZATION_BASE (len) {
		_STATIC_WARNING_ ("noop") ;
	}

	LENGTH size () const {
		return mSize ;
	}

	LENGTH length () const {
		if (mAllocator.size () == 0)
			return 0 ;
		return mLength ;
	}

	void clear () {
		INDEX ix = VAR_NONE ;
		INDEX iy = VAR_NONE ;
		for (auto &&i : _RANGE_ (0 ,mSize)) {
			iy = ix ;
			ix = mSize + ~i ;
			if (mAllocator[ix].mNext == VAR_USED)
				_DESTROY_ (DEPTR[mAllocator[ix].mValue]) ;
			mAllocator[ix].mNext = iy ;
		}
		mLength = 0 ;
		mFree = ix ;
	}

	BOOL used (const INDEX &index) const {
		if (mAllocator[index].mNext != VAR_USED)
			return FALSE ;
		return TRUE ;
	}

	UNIT &get (const INDEX &index) leftvalue {
		_DEBUG_ASSERT_ (used (index)) ;
		return _CAST_ (_NULL_<ARGV<UNIT>> () ,mAllocator[index].mValue) ;
	}

	inline UNIT &operator[] (const INDEX &index) leftvalue {
		return get (index) ;
	}

	const UNIT &get (const INDEX &index) const leftvalue {
		_DEBUG_ASSERT_ (used (index)) ;
		return _CAST_ (_NULL_<ARGV<UNIT>> () ,mAllocator[index].mValue) ;
	}

	inline const UNIT &operator[] (const INDEX &index) const leftvalue {
		return get (index) ;
	}

	INDEX at (const UNIT &item) const {
		auto &r1x = _OFFSET_ (&NODE::mValue ,_CAST_ (_NULL_<ARGV<TEMP<UNIT>>> () ,item)) ;
		INDEX ret = mAllocator.at (r1x) ;
		if (!used (ret))
			ret = VAR_NONE ;
		return _MOVE_ (ret) ;
	}

	template <class... _ARGS>
	INDEX alloc (_ARGS &&...initval) side_effects {
		INDEX ret = VAR_NONE ;
		auto fax = TRUE ;
		if switch_once (fax) {
			if (mFree != VAR_NONE)
				discard ;
			auto tmp = mAllocator.expand (mAllocator.expand_size ()) ;
			ret = mSize ;
			_CREATE_ (DEPTR[tmp[ret].mValue] ,_FORWARD_<_ARGS> (initval)...) ;
			for (auto &&i : _RANGE_ (0 ,mSize)) {
				_CREATE_ (DEPTR[tmp[i].mValue] ,_MOVE_ (_CAST_ (_NULL_<ARGV<UNIT>> () ,mAllocator[i].mValue))) ;
				tmp[i].mNext = VAR_USED ;
			}
			mAllocator.swap (tmp) ;
			update_reserve (mSize ,mFree) ;
		}
		if switch_once (fax) {
			ret = mFree ;
			_CREATE_ (DEPTR[mAllocator[ret].mValue] ,_FORWARD_<_ARGS> (initval)...) ;
		}
		mFree = mAllocator[ret].mNext ;
		mAllocator[ret].mNext = VAR_USED ;
		mLength++ ;
		return _MOVE_ (ret) ;
	}

	void free (const INDEX &index) noexcept {
		_DEBUG_ASSERT_ (used (index)) ;
		_DESTROY_ (DEPTR[mAllocator[index].mValue]) ;
		mAllocator[index].mNext = mFree ;
		mFree = index ;
		mLength-- ;
	}

	void reserve (const LENGTH &len) {
		_DEBUG_ASSERT_ (len >= 0) ;
		const auto r1x = len - (mSize - mLength) ;
		const auto r2x = VAR_ZERO ;
		const auto r3x = _MAX_ (r1x ,r2x) ;
		if (r3x == 0)
			return ;
		_DEBUG_ASSERT_ (mSize + r3x > mSize) ;
		auto tmp = mAllocator.expand (mSize + r3x) ;
		for (auto &&i : _RANGE_ (0 ,mSize)) {
			if (mAllocator[i].mNext == VAR_USED)
				_CREATE_ (DEPTR[tmp[i].mValue] ,_MOVE_ (_CAST_ (_NULL_<ARGV<UNIT>> () ,mAllocator[i].mValue))) ;
			tmp[i].mNext = mAllocator[i].mNext ;
		}
		mAllocator.swap (tmp) ;
		update_reserve (mSize ,mFree) ;
	}

	void clean () {
		const auto r1x = shrink_size () ;
		if (r1x == mSize)
			return ;
		_DYNAMIC_ASSERT_ (r1x == mLength) ;
		auto tmp = mAllocator.expand (r1x) ;
		for (auto &&i : _RANGE_ (0 ,tmp.size ())) {
			_DEBUG_ASSERT_ (mAllocator[i].mNext == VAR_USED) ;
			_CREATE_ (DEPTR[tmp[i].mValue] ,_MOVE_ (_CAST_ (_NULL_<ARGV<UNIT>> () ,mAllocator[i].mValue))) ;
			tmp[i].mNext = VAR_USED ;
		}
		mAllocator.swap (tmp) ;
		update_reserve (r1x ,VAR_NONE) ;
	}

private:
	void update_reserve (const INDEX &size_ ,const INDEX &free_) noexcept {
		INDEX ix = free_ ;
		INDEX iy = VAR_NONE ;
		for (auto &&i : _RANGE_ (size_ ,mAllocator.size ())) {
			iy = ix ;
			ix = mAllocator.size () + ~(i - size_) ;
			mAllocator[ix].mNext = iy ;
		}
		mSize = mAllocator.size () ;
		mFree = ix ;
	}

	LENGTH shrink_size () const {
		LENGTH ret = mSize ;
		while (TRUE) {
			if (ret < 1)
				break ;
			if (mAllocator[ret - 1].mNext == VAR_USED)
				break ;
			ret-- ;
		}
		return _MOVE_ (ret) ;
	}
} ;
} ;