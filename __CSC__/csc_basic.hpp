﻿#pragma once

#ifndef __CSC_BASIC__
#define __CSC_BASIC__
#endif

#include "csc.hpp"
#include "csc_core.hpp"

namespace CSC {
class BasicProc :
	delegate private Wrapped<> {
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

class EqualInvokeProc :
	delegate private Wrapped<> {
public:
	template <class _ARG1>
	imports FLAG invoke (const _ARG1 &lhs ,const _ARG1 &rhs) {
		return template_equal (lhs ,rhs ,ARGVPX) ;
	}

private:
	template <class _ARG1 ,class = ENABLE_TYPE<IS_ARRAY_HELP<_ARG1>>>
	imports FLAG template_equal (const _ARG1 &lhs ,const _ARG1 &rhs ,const DEF<decltype (ARGVP3)> &) {
		return BasicProc::mem_equal (PTRTOARR[lhs] ,PTRTOARR[rhs] ,_COUNTOF_ (_ARG1)) ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<IS_SAME_HELP<DEF<decltype (_NULL_ (ARGV<const REMOVE_REFERENCE_TYPE<_ARG1>>::ID).equal (_NULL_ (ARGV<const REMOVE_REFERENCE_TYPE<_ARG1>>::ID)))> ,BOOL>>>
	imports FLAG template_equal (const _ARG1 &lhs ,const _ARG1 &rhs ,const DEF<decltype (ARGVP2)> &) {
		return lhs.equal (rhs) ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<IS_SAME_HELP<DEF<decltype (_NULL_ (ARGV<const REMOVE_REFERENCE_TYPE<_ARG1>>::ID) == _NULL_ (ARGV<const REMOVE_REFERENCE_TYPE<_ARG1>>::ID))> ,BOOL>>>
	imports FLAG template_equal (const _ARG1 &lhs ,const _ARG1 &rhs ,const DEF<decltype (ARGVP1)> &) {
		return BOOL (lhs == rhs) ;
	}
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
	for (auto &&i : _RANGE_ (0 ,len)) {
		if (!EqualInvokeProc::invoke (src1[i] ,src2[i]))
			return FALSE ;
	}
	return TRUE ;
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
}

class ComprInvokeProc :
	delegate private Wrapped<> {
public:
	template <class _ARG1>
	imports FLAG invoke (const _ARG1 &lhs ,const _ARG1 &rhs) {
		return template_compr (lhs ,rhs ,ARGVPX) ;
	}

private:
	template <class _ARG1 ,class = ENABLE_TYPE<IS_ARRAY_HELP<_ARG1>>>
	imports FLAG template_compr (const _ARG1 &lhs ,const _ARG1 &rhs ,const DEF<decltype (ARGVP3)> &) {
		return BasicProc::mem_compr (PTRTOARR[lhs] ,PTRTOARR[rhs] ,_COUNTOF_ (_ARG1)) ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<IS_SAME_HELP<DEF<decltype (_NULL_ (ARGV<const REMOVE_REFERENCE_TYPE<_ARG1>>::ID).compr (_NULL_ (ARGV<const REMOVE_REFERENCE_TYPE<_ARG1>>::ID)))> ,FLAG>>>
	imports FLAG template_compr (const _ARG1 &lhs ,const _ARG1 &rhs ,const DEF<decltype (ARGVP2)> &) {
		return lhs.compr (rhs) ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<IS_SAME_HELP<DEF<decltype (_NULL_ (ARGV<const REMOVE_REFERENCE_TYPE<_ARG1>>::ID) < _NULL_ (ARGV<const REMOVE_REFERENCE_TYPE<_ARG1>>::ID))> ,BOOL>>>
		imports FLAG template_compr (const _ARG1 &lhs ,const _ARG1 &rhs ,const DEF<decltype (ARGVP1)> &) {
			if (lhs < rhs)
				return FLAG (-1) ;
			if (rhs < lhs)
				return FLAG (+1) ;
			return FLAG (0) ;
		}
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
		const auto r1x = ComprInvokeProc::invoke (src1[i] ,src2[i]) ;
		if (r1x != 0)
			return r1x ;
	}
	return FLAG (0) ;
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
}

class HashInvokeProc :
	delegate private Wrapped<> {
public:
	template <class _ARG1>
	imports FLAG invoke (const _ARG1 &lhs) {
		FLAG ret = template_hash (lhs ,ARGVPX) ;
		ret &= VAR_MAX ;
		return _MOVE_ (ret) ;
	}

private:
	template <class _ARG1 ,class = ENABLE_TYPE<IS_ARRAY_HELP<_ARG1>>>
	imports FLAG template_hash (const _ARG1 &lhs ,const DEF<decltype (ARGVP3)> &) {
		return BasicProc::mem_hash (PTRTOARR[lhs] ,_SIZEOF_ (_ARG1)) ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<IS_SAME_HELP<DEF<decltype (_NULL_ (ARGV<const REMOVE_REFERENCE_TYPE<_ARG1>>::ID).hash ())> ,FLAG>>>
	imports FLAG template_hash (const _ARG1 &lhs ,const DEF<decltype (ARGVP2)> &) {
		return lhs.hash () ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<IS_XYZ_HELP<_ARG1>>>
	imports FLAG template_hash (const _ARG1 &lhs ,const DEF<decltype (ARGVP1)> &) {
		auto &r1x = _CAST_ (ARGV<BYTE_BASE_TYPE<_ARG1>>::ID ,lhs) ;
		return FLAG (r1x) ;
	}
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
		ret ^= HashInvokeProc::invoke (src[i]) ;
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
		ret ^= HashInvokeProc::invoke (src[i]) ;
		ret *= M_MAGIC_N2 ;
	}
	ret &= VAR_MAX ;
	return _MOVE_ (ret) ;
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
}
#endif

class CRC32StaticProc :
	delegate private Wrapped<> {
public:
	imports CHAR static_mem_crc32_table_each (const CHAR &val) ;

	imports const PACK<CHAR[256]> &static_mem_crc32_table () ;
} ;

inline exports CHAR CRC32StaticProc::static_mem_crc32_table_each (const CHAR &val) {
	CHAR ret = val ;
	for (auto &&i : _RANGE_ (0 ,8)) {
		_STATIC_UNUSED_ (i) ;
		const auto r1x = CHAR (ret & CHAR (0X00000001)) ;
		ret = CHAR (ret >> 1) ;
		if (r1x == 0)
			continue ;
		ret ^= CHAR (0XEDB88320) ;
	}
	return _MOVE_ (ret) ;
}

inline exports const PACK<CHAR[256]> &CRC32StaticProc::static_mem_crc32_table () {
	return _CACHE_ ([&] () {
		PACK<CHAR[256]> ret ;
		for (auto &&i : _RANGE_ (0 ,_COUNTOF_ (DEF<decltype (ret.mP1)>)))
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
	_STATIC_ASSERT_ (IS_SAME_HELP<_ARG1 ,BYTE>::compile ()) ;
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
	for (auto &&i : _RANGE_ (0 ,len)) {
		if (EqualInvokeProc::invoke (src[i] ,val))
			return i ;
	}
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
	for (auto &&i : _RANGE_ (0 ,len)) {
		INDEX ix = len + ~i ;
		if (EqualInvokeProc::invoke (src[ix] ,val))
			return ix ;
	}
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
		if (dst == src)
			discard ;
		_DEBUG_ASSERT_ (_ABS_ (dst - src) >= len) ;
		for (auto &&i : _RANGE_ (0 ,len))
			dst[i] = src[len + ~i] ;
	}
	if switch_once (fax) {
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
		if (!(dst1 <= dst2))
			discard ;
		for (auto &&i : _RANGE_ (0 ,len))
			dst1[i] = _MOVE_ (dst2[i]) ;
	}
	if switch_once (fax) {
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
class ScopedPtr final {
private:
	PTR<UNIT> mPointer ;

public:
	implicit ScopedPtr () = delete ;

	explicit ScopedPtr (const PTR<UNIT> &pointer) :
		delegate ScopedPtr (ARGVP0) {
		mPointer = pointer ;
	}

	implicit ~ScopedPtr () noexcept {
		if (mPointer == NULL)
			return ;
		const auto r1x = _FORWARD_ (ARGV<PTR<NONE>>::ID ,mPointer) ;
		CONT::free (r1x) ;
		mPointer = NULL ;
	}

	implicit ScopedPtr (const ScopedPtr &) = delete ;

	inline ScopedPtr &operator= (const ScopedPtr &) = delete ;

	implicit ScopedPtr (ScopedPtr &&that) noexcept {
		_SWAP_ (mPointer ,that.mPointer) ;
	}

	inline ScopedPtr &operator= (ScopedPtr &&that) noexcept {
		if switch_once (TRUE) {
			if (this == DEPTR[that])
				discard ;
			DEREF[this].~ScopedPtr () ;
			new (this) ScopedPtr (_MOVE_ (that)) ;
		}
		return DEREF[this] ;
	}

	const PTR<UNIT> &to () const leftvalue {
		_DEBUG_ASSERT_ (mPointer != NULL) ;
		return mPointer ;
	}

	inline implicit operator const PTR<UNIT> & () const leftvalue {
		return self ;
	}

	inline implicit operator PTR<UNIT> () const leftvalue = delete ;

	inline void operator= (const DEF<decltype (NULL)> &) leftvalue noexcept {
		mPointer = NULL ;
	}

private:
	explicit ScopedPtr (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mPointer (NULL) {}
} ;

template <class UNIT>
class ScopedGuard final :
	delegate private Proxy {
private:
	PTR<UNIT> mPointer ;

public:
	implicit ScopedGuard () = delete ;

	template <class _ARG1>
	explicit ScopedGuard (_ARG1 &address) :
		delegate ScopedGuard (ARGVP0) {
		auto &r1x = _FORWARD_ (ARGV<UNIT>::ID ,address) ;
		r1x.lock () ;
		mPointer = DEPTR[r1x] ;
	}

	implicit ~ScopedGuard () noexcept {
		if (mPointer == NULL)
			return ;
		_CALL_TRY_ ([&] () {
			DEREF[mPointer].unlock () ;
		} ,[&] () {
			_DEBUG_ASSERT_ (FALSE) ;
		}) ;
		mPointer = NULL ;
	}

	implicit ScopedGuard (const ScopedGuard &) = delete ;

	inline ScopedGuard &operator= (const ScopedGuard &) = delete ;

	implicit ScopedGuard (ScopedGuard &&) = delete ;

	inline ScopedGuard &operator= (ScopedGuard &&) = delete ;

private:
	explicit ScopedGuard (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mPointer (NULL) {}
} ;

template <class UNIT>
class ScopedBuild final :
	delegate private Proxy {
private:
	PTR<const PTR<TEMP<UNIT>>> mPointer ;
	LENGTH mSize ;

public:
	implicit ScopedBuild () = delete ;

	template <class _ARG1 ,class... _ARGS>
	explicit ScopedBuild (_ARG1 &address ,_ARGS &&...initval) :
		delegate ScopedBuild (ARGVP0) {
		auto &r1x = _FORWARD_ (ARGV<PTR<TEMP<UNIT>>>::ID ,address) ;
		if (r1x == NULL)
			return ;
		mPointer = DEPTR[r1x] ;
		_CREATE_ (r1x ,_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) ;
		mSize++ ;
	}

	implicit ~ScopedBuild () noexcept {
		if (mPointer == NULL)
			return ;
		const auto r1x = DEREF[mPointer] ;
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

	implicit ScopedBuild (const ScopedBuild &) = delete ;

	inline ScopedBuild &operator= (const ScopedBuild &) = delete ;

	implicit ScopedBuild (ScopedBuild &&) = delete ;

	inline ScopedBuild &operator= (ScopedBuild &&) = delete ;

private:
	explicit ScopedBuild (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mPointer (NULL) ,
		delegate mSize (0) {}
} ;

template <class UNIT>
class ScopedBuild<ARR<UNIT>> final :
	delegate private Proxy {
private:
	PTR<const PTR<ARR<TEMP<UNIT>>>> mPointer ;
	LENGTH mSize ;

public:
	implicit ScopedBuild () = delete ;

	template <class _ARG1>
	explicit ScopedBuild (_ARG1 &address ,const LENGTH &len) :
		delegate ScopedBuild (ARGVP0) {
		auto &r1x = _FORWARD_ (ARGV<PTR<ARR<TEMP<UNIT>>>>::ID ,address) ;
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

	template <class _ARG1>
	explicit ScopedBuild (_ARG1 &address ,const ARR<UNIT> &src ,const LENGTH &len) :
		delegate ScopedBuild (ARGVP0) {
		auto &r1x = _FORWARD_ (ARGV<PTR<ARR<TEMP<UNIT>>>>::ID ,address) ;
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

	implicit ~ScopedBuild () noexcept {
		if (mPointer == NULL)
			return ;
		const auto r1x = DEREF[mPointer] ;
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

	implicit ScopedBuild (const ScopedBuild &) = delete ;

	inline ScopedBuild &operator= (const ScopedBuild &) = delete ;

	implicit ScopedBuild (ScopedBuild &&) = delete ;

	inline ScopedBuild &operator= (ScopedBuild &&) = delete ;

private:
	explicit ScopedBuild (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mPointer (NULL) ,
		delegate mSize (0) {}
} ;

class GlobalHeap :
	delegate private Wrapped<> {
public:
	template <class _ARG1>
	imports ScopedPtr<_ARG1 ,GlobalHeap> alloc (const ARGVF<_ARG1> &) {
		_STATIC_ASSERT_ (IS_TRIVIAL_HELP<_ARG1>::compile ()) ;
		_STATIC_ASSERT_ (_ALIGNOF_ (_ARG1) <= _ALIGNOF_ (api::max_align_t)) ;
		const auto r1x = operator new (_SIZEOF_ (_ARG1) ,api::nothrow) ;
		_DYNAMIC_ASSERT_ (r1x != NULL) ;
		const auto r2x = _POINTER_CAST_ (ARGV<_ARG1>::ID ,r1x) ;
		_DYNAMIC_ASSERT_ (_ADDRESS_ (r2x) % _ALIGNOF_ (_ARG1) == 0) ;
		return ScopedPtr<_ARG1 ,GlobalHeap> (r2x) ;
	}

	template <class _ARG1>
	imports ScopedPtr<ARR<_ARG1> ,GlobalHeap> alloc (const ARGVF<_ARG1> & ,const LENGTH &len) {
		_STATIC_ASSERT_ (IS_TRIVIAL_HELP<_ARG1>::compile ()) ;
		_STATIC_ASSERT_ (_ALIGNOF_ (_ARG1) <= _ALIGNOF_ (api::max_align_t)) ;
		_DEBUG_ASSERT_ (len > 0) ;
		const auto r1x = len * _SIZEOF_ (_ARG1) ;
		_DEBUG_ASSERT_ (r1x > 0) ;
		const auto r2x = operator new (r1x ,api::nothrow) ;
		_DYNAMIC_ASSERT_ (r2x != NULL) ;
		const auto r3x = _POINTER_CAST_ (ARGV<ARR<_ARG1>>::ID ,r2x) ;
		_DYNAMIC_ASSERT_ (_ADDRESS_ (r3x) % _ALIGNOF_ (_ARG1) == 0) ;
		return ScopedPtr<ARR<_ARG1> ,GlobalHeap> (r3x) ;
	}

	template <class _ARG1>
	imports void free (const PTR<_ARG1> &address) noexcept {
		_STATIC_ASSERT_ (IS_SAME_HELP<_ARG1 ,NONE>::compile ()) ;
		if (address == NULL)
			return ;
		//@error: 'operator delete' may be dismatch with 'operator new'
		operator delete (address ,api::nothrow) ;
	}
} ;

template <class>
class AutoRef ;

template <class UNIT>
class AutoRef<SPECIALIZATION<UNIT ,ARGC<FALSE>>> {
	_STATIC_ASSERT_ (IS_COMPLETE_HELP<UNIT ,struct ANONYMOUS>::compile ()) ;

protected:
	struct Private {
		class PureHolder ;
	} ;

	class Holder :
		delegate public Interface {
	public:
		virtual UNIT &deref () leftvalue = 0 ;
	} ;

protected:
	PTR<NONE> mOrigin ;
	PTR<Holder> mPointer ;

protected:
	implicit AutoRef () :
		delegate AutoRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	implicit ~AutoRef () noexcept {
		if (mPointer == NULL)
			return ;
		DEREF[mPointer].~Holder () ;
		GlobalHeap::free (mOrigin) ;
		mOrigin = NULL ;
		mPointer = NULL ;
	}

	implicit AutoRef (const AutoRef &) = delete ;

	inline AutoRef &operator= (const AutoRef &) = delete ;

	implicit AutoRef (AutoRef &&that) noexcept :
		delegate AutoRef (ARGVP0) {
		_SWAP_ (mOrigin ,that.mOrigin) ;
		_SWAP_ (mPointer ,that.mPointer) ;
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

protected:
	explicit AutoRef (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mOrigin (NULL) ,
		delegate mPointer (NULL) {}
} ;

template <class UNIT>
class AutoRef<SPECIALIZATION<UNIT ,ARGC<FALSE>>>::Private::PureHolder :
	delegate public Holder {
private:
	REMOVE_CVR_TYPE<UNIT> mValue ;

public:
	implicit PureHolder () = delete ;

	template <class... _ARGS>
	explicit PureHolder (const DEF<decltype (ARGVP0)> & ,_ARGS &&...initval) :
		delegate mValue (_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) {}

	UNIT &deref () leftvalue override {
		return mValue ;
	}
} ;

template <class UNIT>
class AutoRef<SPECIALIZATION<UNIT ,ARGC<TRUE>>> {
	_STATIC_ASSERT_ (IS_COMPLETE_HELP<UNIT ,struct ANONYMOUS>::compile ()) ;

protected:
	struct Private {
		class PureHolder ;
	} ;

	class Holder :
		delegate public Interface {
	public:
		virtual UNIT &deref () leftvalue = 0 ;
	} ;

protected:
	PTR<NONE> mOrigin ;
	PTR<Holder> mPointer ;

protected:
	implicit AutoRef () :
		delegate AutoRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	implicit ~AutoRef () noexcept {
		if (mPointer == NULL)
			return ;
		DEREF[mPointer].~Holder () ;
		GlobalHeap::free (mOrigin) ;
		mOrigin = NULL ;
		mPointer = NULL ;
	}

	implicit AutoRef (const AutoRef &that) :
		delegate AutoRef (ARGVP0) {
		using R1X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::PureHolder ;
		if (that.mPointer == NULL)
			return ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<R1X>>::ID) ;
		auto &r1x = _FORWARD_ (ARGV<const UNIT>::ID ,DEREF[that.mPointer].deref ()) ;
		ScopedBuild<R1X> ANONYMOUS (rax ,ARGVP0 ,r1x) ;
		const auto r2x = _POINTER_CAST_ (ARGV<R1X>::ID ,rax.self) ;
		mOrigin = rax.self ;
		mPointer = r2x ;
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

	implicit AutoRef (AutoRef &&that) noexcept :
		delegate AutoRef (ARGVP0) {
		_SWAP_ (mOrigin ,that.mOrigin) ;
		_SWAP_ (mPointer ,that.mPointer) ;
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

protected:
	explicit AutoRef (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mOrigin (NULL) ,
		delegate mPointer (NULL) {}
} ;

template <class UNIT>
class AutoRef<SPECIALIZATION<UNIT ,ARGC<TRUE>>>::Private::PureHolder :
	delegate public Holder {
private:
	REMOVE_CVR_TYPE<UNIT> mValue ;

public:
	implicit PureHolder () = delete ;

	template <class... _ARGS>
	explicit PureHolder (const DEF<decltype (ARGVP0)> & ,_ARGS &&...initval) :
		delegate mValue (_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) {}

	UNIT &deref () leftvalue override {
		return mValue ;
	}
} ;

template <class UNIT>
class AutoRef final :
	delegate private AutoRef<SPECIALIZATION<UNIT ,ARGC_TYPE<IS_COPY_CONSTRUCTIBLE_HELP<UNIT>>>> {
private:
	using SPECIALIZATION_BASE = AutoRef<SPECIALIZATION<UNIT ,ARGC_TYPE<IS_COPY_CONSTRUCTIBLE_HELP<UNIT>>>> ;
	using Holder = typename SPECIALIZATION_BASE::Holder ;

private:
	friend SPECIALIZATION_BASE ;
	using SPECIALIZATION_BASE::mOrigin ;
	using SPECIALIZATION_BASE::mPointer ;

public:
	implicit AutoRef () = default ;

	BOOL exist () const {
		if (mPointer == NULL)
			return FALSE ;
		return TRUE ;
	}

	UNIT &to () leftvalue {
		_DEBUG_ASSERT_ (exist ()) ;
		return DEREF[mPointer].deref () ;
	}

	inline PTR<UNIT> operator-> () leftvalue {
		return DEPTR[self] ;
	}

	inline implicit operator UNIT & () leftvalue {
		return self ;
	}

	const UNIT &to () const leftvalue {
		_DEBUG_ASSERT_ (exist ()) ;
		return DEREF[mPointer].deref () ;
	}

	inline PTR<const UNIT> operator-> () const leftvalue {
		return DEPTR[self] ;
	}

	inline implicit operator const UNIT & () const leftvalue {
		return self ;
	}

	template <class... _ARGS>
	imports AutoRef make (_ARGS &&...initval) {
		using R1X = typename SPECIALIZATION_BASE::Private::PureHolder ;
		AutoRef ret ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<R1X>>::ID) ;
		ScopedBuild<R1X> ANONYMOUS (rax ,ARGVP0 ,_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) ;
		const auto r1x = _POINTER_CAST_ (ARGV<R1X>::ID ,rax.self) ;
		ret.mOrigin = rax.self ;
		ret.mPointer = r1x ;
		rax = NULL ;
		return _MOVE_ (ret) ;
	}
} ;

template <class UNIT>
class SharedRef final {
	_STATIC_ASSERT_ (IS_COMPLETE_HELP<UNIT ,struct ANONYMOUS>::compile ()) ;

private:
	struct Private {
		class PureHolder ;

		class KeepHolder ;

		class KeepProxy ;
	} ;

	class Holder :
		delegate public Interface {
	public:
		virtual BOOL exist () const = 0 ;
		virtual UNIT &deref () leftvalue = 0 ;
		virtual LENGTH increase () = 0 ;
		virtual LENGTH decrease () = 0 ;
		virtual void reset () = 0 ;
	} ;

private:
	PTR<NONE> mOrigin ;
	PTR<Holder> mPointer ;

public:
	implicit SharedRef () :
		delegate SharedRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	implicit ~SharedRef () noexcept {
		if (mPointer == NULL)
			return ;
		if switch_once (TRUE) {
			const auto r1x = DEREF[mPointer].decrease () ;
			if (r1x > 0)
				discard ;
			DEREF[mPointer].~Holder () ;
			GlobalHeap::free (mOrigin) ;
		}
		mOrigin = NULL ;
		mPointer = NULL ;
	}

	implicit SharedRef (const SharedRef &that) :
		delegate SharedRef (ARGVP0) {
		aquire (that.mPointer) ;
		mOrigin = that.mOrigin ;
		mPointer = that.mPointer ;
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

	implicit SharedRef (SharedRef &&that) noexcept :
		delegate SharedRef (ARGVP0) {
		_SWAP_ (mOrigin ,that.mOrigin) ;
		_SWAP_ (mPointer ,that.mPointer) ;
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
		if (!DEREF[mPointer].exist ())
			return FALSE ;
		return TRUE ;
	}

	UNIT &to () const leftvalue {
		_DEBUG_ASSERT_ (exist ()) ;
		return DEREF[mPointer].deref () ;
	}

	inline PTR<UNIT> operator-> () const leftvalue {
		return DEPTR[self] ;
	}

	inline implicit operator UNIT & () const leftvalue {
		return self ;
	}

	template <class _RET = REMOVE_CVR_TYPE<typename Private::KeepProxy>>
	imports _RET keep (UNIT &me) {
		using R1X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::KeepProxy ;
		return R1X (DEPTR[me]) ;
	}

	template <class... _ARGS>
	imports SharedRef make (_ARGS &&...initval) {
		using R1X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::PureHolder ;
		SharedRef ret ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<R1X>>::ID) ;
		ScopedBuild<R1X> ANONYMOUS (rax ,ARGVP0 ,_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) ;
		const auto r1x = _POINTER_CAST_ (ARGV<R1X>::ID ,rax.self) ;
		aquire (r1x) ;
		ret.mOrigin = rax.self ;
		ret.mPointer = r1x ;
		rax = NULL ;
		return _MOVE_ (ret) ;
	}

private:
	explicit SharedRef (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mOrigin (NULL) ,
		delegate mPointer (NULL) {}

	imports void aquire (const PTR<Holder> &pointer) {
		if (pointer == NULL)
			return ;
		const auto r1x = DEREF[pointer].increase () ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x >= 1) ;
	}
} ;

template <class UNIT>
class SharedRef<UNIT>::Private::PureHolder :
	delegate public Holder {
private:
	REMOVE_CVR_TYPE<UNIT> mValue ;
	LENGTH mCounter ;

public:
	implicit PureHolder () = delete ;

	template <class... _ARGS>
	explicit PureHolder (const DEF<decltype (ARGVP0)> & ,_ARGS &&...initval) :
		delegate mValue (_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) ,
		delegate mCounter (0) {}

	BOOL exist () const override {
		return TRUE ;
	}

	UNIT &deref () leftvalue override {
		return mValue ;
	}

	LENGTH increase () override {
		return ++mCounter ;
	}

	LENGTH decrease () override {
		return --mCounter ;
	}

	void reset () override {
		_DEBUG_ASSERT_ (FALSE) ;
	}
} ;

template <class UNIT>
class SharedRef<UNIT>::Private::KeepHolder :
	delegate public Holder {
private:
	PTR<UNIT> mPointer ;
	LENGTH mCounter ;

public:
	implicit KeepHolder () = delete ;

	template <class... _ARGS>
	explicit KeepHolder (const DEF<decltype (ARGVP0)> & ,const PTR<UNIT> &pointer) :
		delegate mPointer (pointer) ,
		delegate mCounter (0) {}

	BOOL exist () const override {
		if (mPointer == NULL)
			return FALSE ;
		return TRUE ;
	}

	UNIT &deref () leftvalue override {
		return DEREF[mPointer] ;
	}

	LENGTH increase () override {
		return ++mCounter ;
	}

	LENGTH decrease () override {
		return --mCounter ;
	}

	void reset () override {
		mPointer = NULL ;
	}
} ;

template <class UNIT>
class SharedRef<UNIT>::Private::KeepProxy final :
delegate private Proxy {
private:
	using KeepHolder = typename Private::KeepHolder ;

private:
	SharedRef mBase ;

public:
	implicit KeepProxy () = delete ;

	explicit KeepProxy (const PTR<UNIT> &pointer) {
		using R1X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::KeepHolder ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<R1X>>::ID) ;
		ScopedBuild<R1X> ANONYMOUS (rax ,ARGVP0 ,pointer) ;
		const auto r1x = _POINTER_CAST_ (ARGV<R1X>::ID ,rax.self) ;
		aquire (r1x) ;
		mBase.mOrigin = rax.self ;
		mBase.mPointer = r1x ;
		rax = NULL ;
	}

	implicit KeepProxy (KeepProxy &&that) noexcept {
		mBase = _MOVE_ (that.mBase) ;
	}

	implicit ~KeepProxy () noexcept {
		if (!mBase.exist ())
			return ;
		DEREF[mBase.mPointer].reset () ;
	}

	const SharedRef &to () const leftvalue {
		return mBase ;
	}

	inline implicit operator const SharedRef & () const leftvalue {
		return self ;
	}
} ;

template <class UNIT = NONE>
class AnyRef ;

template <>
class AnyRef<NONE> final {
private:
	class Holder :
		delegate public Interface {
	public:
		virtual TYPEABI type_abi () const = 0 ;
		virtual FLAG type_mid () const = 0 ;
		virtual PTR<NONE> type_address () = 0 ;
		virtual PTR<const NONE> type_address () const = 0 ;
		virtual AnyRef clone () const = 0 ;
	} ;

private:
	template <class>
	friend class AnyRef ;
	PTR<NONE> mOrigin ;
	PTR<Holder> mPointer ;

public:
	implicit AnyRef () :
		delegate AnyRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1>
	implicit AnyRef (AnyRef<_ARG1> &&that) :
		delegate AnyRef (_MOVE_ (that.rebind (ARGV<NONE>::ID))) {
		_STATIC_WARNING_ ("noop") ;
	}

	implicit ~AnyRef () noexcept {
		if (mPointer == NULL)
			return ;
		DEREF[mPointer].~Holder () ;
		GlobalHeap::free (mOrigin) ;
		mOrigin = NULL ;
		mPointer = NULL ;
	}

	implicit AnyRef (const AnyRef &) = delete ;

	inline AnyRef &operator= (const AnyRef &) = delete ;

	implicit AnyRef (AnyRef &&that) noexcept :
		delegate AnyRef (ARGVP0) {
		_SWAP_ (mOrigin ,that.mOrigin) ;
		_SWAP_ (mPointer ,that.mPointer) ;
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
	AnyRef<_ARG1> &rebind (const ARGVF<_ARG1> &) leftvalue {
		return _CAST_ (ARGV<AnyRef<_ARG1>>::ID ,DEREF[this]) ;
	}

	template <class _ARG1>
	const AnyRef<_ARG1> &rebind (const ARGVF<_ARG1> &) const leftvalue {
		return _CAST_ (ARGV<AnyRef<_ARG1>>::ID ,DEREF[this]) ;
	}

	BOOL exist () const {
		if (mPointer == NULL)
			return FALSE ;
		return TRUE ;
	}

	TYPEABI type_abi () const {
		_DEBUG_ASSERT_ (exist ()) ;
		return DEREF[mPointer].type_abi () ;
	}

	FLAG type_mid () const {
		_DEBUG_ASSERT_ (exist ()) ;
		return DEREF[mPointer].type_mid () ;
	}

	PTR<NONE> type_address () {
		_DEBUG_ASSERT_ (exist ()) ;
		return DEREF[mPointer].type_address () ;
	}

	PTR<const NONE> type_address () const {
		_DEBUG_ASSERT_ (exist ()) ;
		return DEREF[mPointer].type_address () ;
	}

	AnyRef clone () const {
		_DEBUG_ASSERT_ (exist ()) ;
		return DEREF[mPointer].clone () ;
	}

private:
	explicit AnyRef (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mOrigin (NULL) ,
		delegate mPointer (NULL) {}
} ;

template <class UNIT>
class AnyRef final {
	_STATIC_ASSERT_ (IS_COMPLETE_HELP<UNIT ,struct ANONYMOUS>::compile ()) ;

private:
	struct Private {
		class ImplHolder ;
	} ;

	using Holder = typename AnyRef<NONE>::Holder ;

private:
	PTR<NONE> mOrigin ;
	PTR<Holder> mPointer ;

public:
	implicit AnyRef () :
		delegate AnyRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1>
	implicit AnyRef (AnyRef<_ARG1> &&that) :
		delegate AnyRef (_MOVE_ (that.rebind (ARGV<UNIT>::ID))) {
		_STATIC_WARNING_ ("noop") ;
	}

	implicit ~AnyRef () noexcept {
		if (mPointer == NULL)
			return ;
		DEREF[mPointer].~Holder () ;
		GlobalHeap::free (mOrigin) ;
		mOrigin = NULL ;
		mPointer = NULL ;
	}

	implicit AnyRef (const AnyRef &) = delete ;

	inline AnyRef &operator= (const AnyRef &) = delete ;

	implicit AnyRef (AnyRef &&that) noexcept :
		delegate AnyRef (ARGVP0) {
		_SWAP_ (mOrigin ,that.mOrigin) ;
		_SWAP_ (mPointer ,that.mPointer) ;
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
	AnyRef<_ARG1> &rebind (const ARGVF<_ARG1> &) leftvalue {
		return _CAST_ (ARGV<AnyRef<_ARG1>>::ID ,DEREF[this]) ;
	}

	template <class _ARG1>
	const AnyRef<_ARG1> &rebind (const ARGVF<_ARG1> &) const leftvalue {
		return _CAST_ (ARGV<AnyRef<_ARG1>>::ID ,DEREF[this]) ;
	}

	BOOL exist () const {
		if (mPointer == NULL)
			return FALSE ;
		return TRUE ;
	}

	LENGTH type_abi () const {
		_DEBUG_ASSERT_ (exist ()) ;
		return DEREF[mPointer].type_abi () ;
	}

	FLAG type_mid () const {
		_DEBUG_ASSERT_ (exist ()) ;
		return DEREF[mPointer].type_mid () ;
	}

	PTR<NONE> type_address () {
		_DEBUG_ASSERT_ (exist ()) ;
		return DEREF[mPointer].type_address () ;
	}

	PTR<const NONE> type_address () const {
		_DEBUG_ASSERT_ (exist ()) ;
		return DEREF[mPointer].type_address () ;
	}

	AnyRef clone () const {
		_DEBUG_ASSERT_ (exist ()) ;
		return DEREF[mPointer].clone () ;
	}

	UNIT &to () leftvalue {
		_DEBUG_ASSERT_ (type_mid () == _TYPEMID_ (ARGV<UNIT>::ID)) ;
		const auto r1x = DEREF[mPointer].type_address () ;
		const auto r2x = _POINTER_CAST_ (ARGV<UNIT>::ID ,r1x) ;
		return DEREF[r2x] ;
	}

	inline PTR<UNIT> operator-> () leftvalue {
		return DEPTR[self] ;
	}

	inline implicit operator UNIT & () leftvalue {
		return self ;
	}

	const UNIT &to () const leftvalue {
		_DEBUG_ASSERT_ (type_mid () == _TYPEMID_ (ARGV<UNIT>::ID)) ;
		const auto r1x = DEREF[mPointer].type_address () ;
		const auto r2x = _POINTER_CAST_ (ARGV<UNIT>::ID ,r1x) ;
		return DEREF[r2x] ;
	}

	inline PTR<const UNIT> operator-> () const leftvalue {
		return DEPTR[self] ;
	}

	inline implicit operator const UNIT & () const leftvalue {
		return self ;
	}

	template <class... _ARGS>
	imports AnyRef make (_ARGS &&...initval) {
		using R1X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::ImplHolder ;
		AnyRef ret ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<R1X>>::ID) ;
		ScopedBuild<R1X> ANONYMOUS (rax ,ARGVP0 ,_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) ;
		const auto r1x = _POINTER_CAST_ (ARGV<R1X>::ID ,rax.self) ;
		ret.mOrigin = rax.self ;
		ret.mPointer = r1x ;
		rax = NULL ;
		return _MOVE_ (ret) ;
	}

private:
	explicit AnyRef (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mOrigin (NULL) ,
		delegate mPointer (NULL) {}
} ;

template <class UNIT>
class AnyRef<UNIT>::Private::ImplHolder :
	delegate public Holder {
private:
	UNIT mValue ;

public:
	implicit ImplHolder () = delete ;

	template <class... _ARGS>
	explicit ImplHolder (const DEF<decltype (ARGVP0)> & ,_ARGS &&...initval) :
		delegate mValue (_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) {}

	TYPEABI type_abi () const override {
		return _TYPEABI_ (ARGV<UNIT>::ID) ;
	}

	FLAG type_mid () const override {
		return _TYPEMID_ (ARGV<UNIT>::ID) ;
	}

	PTR<NONE> type_address () override {
		return DEPTR[mValue] ;
	}

	PTR<const NONE> type_address () const override {
		return DEPTR[mValue] ;
	}

	AnyRef<> clone () const override {
		using R1X = ARGC_TYPE<IS_COPY_CONSTRUCTIBLE_HELP<UNIT>> ;
		return template_clone (ARGV<R1X>::ID) ;
	}

private:
	AnyRef<> template_clone (const ARGVF<ARGC<TRUE>> &) const {
		AnyRef ret ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<ImplHolder>>::ID) ;
		ScopedBuild<ImplHolder> ANONYMOUS (rax ,ARGVP0 ,_FORWARD_ (ARGV<const UNIT &>::ID ,mValue)) ;
		const auto r1x = _POINTER_CAST_ (ARGV<ImplHolder>::ID ,rax.self) ;
		ret.mOrigin = rax.self ;
		ret.mPointer = r1x ;
		rax = NULL ;
		return _MOVE_ (ret) ;
	}

	AnyRef<> template_clone (const ARGVF<ARGC<FALSE>> &) const {
		return AnyRef () ;
	}
} ;

template <class>
class Function ;

template <class UNIT = NONE>
class UniqueRef ;

template <>
class UniqueRef<NONE> final {
private:
	struct Private {
		template <class>
		class ImplHolder ;
	} ;

	class Holder :
		delegate public Interface {
	public:
		virtual void release () = 0 ;
	} ;

private:
	PTR<NONE> mOrigin ;
	PTR<Holder> mPointer ;

public:
	implicit UniqueRef () :
		delegate UniqueRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1 ,class _ARG2 ,class = ENABLE_TYPE<U::CONSTEXPR_NOT<IS_PLACEHOLDER_HELP<_ARG1>>>>
	explicit UniqueRef (const _ARG1 &constructor ,_ARG2 &&destructor) :
		delegate UniqueRef (ARGVP0) {
		using R1X = DEPENDENT_TYPE<Function<void ()> ,struct ANONYMOUS> ;
		using R2X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<R1X> ;
		_STATIC_ASSERT_ (IS_VOID_HELP<RESULT_OF_TYPE<_ARG1 ,ARGVS<>>>::compile ()) ;
		_STATIC_ASSERT_ (U::CONSTEXPR_NOT<IS_REFERENCE_HELP<_ARG2>>::compile ()) ;
		_STATIC_ASSERT_ (IS_VOID_HELP<RESULT_OF_TYPE<_ARG2 ,ARGVS<>>>::compile ()) ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<R2X>>::ID) ;
		auto rbx = R1X (_FORWARD_ (ARGV<_ARG2 &&>::ID ,destructor)) ;
		ScopedBuild<R2X> ANONYMOUS (rax ,ARGVP0 ,_MOVE_ (rbx)) ;
		const auto r2x = _POINTER_CAST_ (ARGV<R2X>::ID ,rax.self) ;
		constructor () ;
		mOrigin = rax.self ;
		mPointer = r2x ;
		rax = NULL ;
	}

	implicit ~UniqueRef () noexcept {
		if (mPointer == NULL)
			return ;
		_CALL_TRY_ ([&] () {
			DEREF[mPointer].release () ;
		} ,[&] () {
			_DEBUG_ASSERT_ (FALSE) ;
		}) ;
		DEREF[mPointer].~Holder () ;
		GlobalHeap::free (mOrigin) ;
		mOrigin = NULL ;
		mPointer = NULL ;
	}

	implicit UniqueRef (const UniqueRef &) = delete ;

	inline UniqueRef &operator= (const UniqueRef &) = delete ;

	implicit UniqueRef (UniqueRef &&that) noexcept :
		delegate UniqueRef (ARGVP0) {
		_SWAP_ (mOrigin ,that.mOrigin) ;
		_SWAP_ (mPointer ,that.mPointer) ;
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
	explicit UniqueRef (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mOrigin (NULL) ,
		delegate mPointer (NULL) {}
} ;

template <class UNIT_>
class UniqueRef<>::Private::ImplHolder :
	delegate public Holder {
private:
	UNIT_ mFunctor ;

public:
	implicit ImplHolder () = delete ;

	template <class... _ARGS>
	explicit ImplHolder (const DEF<decltype (ARGVP0)> & ,_ARGS &&...initval) :
		delegate mFunctor (_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) {}

	void release () override {
		mFunctor () ;
	}
} ;

template <class UNIT>
class UniqueRef final {
	_STATIC_ASSERT_ (IS_COMPLETE_HELP<UNIT ,struct ANONYMOUS>::compile ()) ;

private:
	struct Private {
		template <class>
		class ImplHolder ;
	} ;

	class Holder :
		delegate public Interface {
	public:
		virtual UNIT &deref () leftvalue = 0 ;
		virtual void release () = 0 ;
	} ;

private:
	PTR<NONE> mOrigin ;
	PTR<Holder> mPointer ;

public:
	implicit UniqueRef () :
		delegate UniqueRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1 ,class _ARG2 ,class = ENABLE_TYPE<U::CONSTEXPR_NOT<IS_PLACEHOLDER_HELP<_ARG1>>>>
	explicit UniqueRef (const _ARG1 &constructor ,_ARG2 &&destructor) :
		delegate UniqueRef (ARGVP0) {
		using R1X = DEPENDENT_TYPE<Function<void (UNIT &)> ,struct ANONYMOUS> ;
		using R2X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<R1X> ;
		_STATIC_ASSERT_ (IS_VOID_HELP<RESULT_OF_TYPE<_ARG1 ,ARGVS<UNIT &>>>::compile ()) ;
		_STATIC_ASSERT_ (U::CONSTEXPR_NOT<IS_REFERENCE_HELP<_ARG2>>::compile ()) ;
		_STATIC_ASSERT_ (IS_VOID_HELP<RESULT_OF_TYPE<_ARG2 ,ARGVS<UNIT &>>>::compile ()) ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<R2X>>::ID) ;
		auto rbx = R1X (_FORWARD_ (ARGV<_ARG2 &&>::ID ,destructor)) ;
		ScopedBuild<R2X> ANONYMOUS (rax ,ARGVP0 ,_MOVE_ (rbx)) ;
		const auto r2x = _POINTER_CAST_ (ARGV<R2X>::ID ,rax.self) ;
		constructor (DEREF[r2x].deref ()) ;
		mOrigin = rax.self ;
		mPointer = r2x ;
		rax = NULL ;
	}

	implicit ~UniqueRef () noexcept {
		if (mPointer == NULL)
			return ;
		_CALL_TRY_ ([&] () {
			DEREF[mPointer].release () ;
		} ,[&] () {
			_DEBUG_ASSERT_ (FALSE) ;
		}) ;
		DEREF[mPointer].~Holder () ;
		GlobalHeap::free (mOrigin) ;
		mOrigin = NULL ;
		mPointer = NULL ;
	}

	implicit UniqueRef (const UniqueRef &) = delete ;

	inline UniqueRef &operator= (const UniqueRef &) = delete ;

	implicit UniqueRef (UniqueRef &&that) noexcept :
		delegate UniqueRef (ARGVP0) {
		_SWAP_ (mOrigin ,that.mOrigin) ;
		_SWAP_ (mPointer ,that.mPointer) ;
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
		_DEBUG_ASSERT_ (exist ()) ;
		return DEREF[mPointer].deref () ;
	}

	inline PTR<const UNIT> operator-> () const leftvalue {
		return DEPTR[self] ;
	}

	inline implicit operator const UNIT & () const leftvalue {
		return self ;
	}

	template <class... _ARGS>
	imports UniqueRef make (_ARGS &&...initval) {
		using R1X = DEPENDENT_TYPE<Function<void (UNIT &)> ,struct ANONYMOUS> ;
		using R2X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<R1X> ;
		UniqueRef ret ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<R2X>>::ID) ;
		auto rbx = R1X ([] (UNIT &) {
			_STATIC_WARNING_ ("noop") ;
		}) ;
		ScopedBuild<R2X> ANONYMOUS (rax ,ARGVP0 ,_MOVE_ (rbx)) ;
		const auto r2x = _POINTER_CAST_ (ARGV<R2X>::ID ,rax.self) ;
		auto &r3x = DEREF[r2x].deref () ;
		r3x = UNIT (_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) ;
		ret.mOrigin = rax.self ;
		ret.mPointer = r2x ;
		rax = NULL ;
		return _MOVE_ (ret) ;
	}

private:
	explicit UniqueRef (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mOrigin (NULL) ,
		delegate mPointer (NULL) {}
} ;

template <class UNIT>
template <class UNIT_>
class UniqueRef<UNIT>::Private::ImplHolder :
	delegate public Holder {
private:
	REMOVE_CVR_TYPE<UNIT> mValue ;
	UNIT_ mFunctor ;

public:
	implicit ImplHolder () = delete ;

	template <class... _ARGS>
	explicit ImplHolder (const DEF<decltype (ARGVP0)> & ,_ARGS &&...initval) :
		delegate mFunctor (_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) {}

	UNIT &deref () leftvalue override {
		return mValue ;
	}

	void release () override {
		mFunctor (mValue) ;
	}
} ;

template <class UNIT>
class PhanRef final {
	_STATIC_ASSERT_ (IS_COMPLETE_HELP<UNIT ,struct ANONYMOUS>::compile ()) ;

private:
	PTR<UNIT> mPointer ;

public:
	implicit PhanRef () :
		delegate PhanRef (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	implicit ~PhanRef () noexcept {
		if (mPointer == NULL)
			return ;
		mPointer = NULL ;
	}

	implicit PhanRef (const PhanRef &) = delete ;

	inline PhanRef &operator= (const PhanRef &) = delete ;

	implicit PhanRef (PhanRef &&that) noexcept :
		delegate PhanRef (ARGVP0) {
		_SWAP_ (mPointer ,that.mPointer) ;
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
		return DEREF[mPointer] ;
	}

	inline PTR<UNIT> operator-> () const leftvalue {
		return DEPTR[self] ;
	}

	inline implicit operator UNIT & () const leftvalue {
		return self ;
	}

	//@warn: phantom means deliver pointer without holder
	template <class _ARG1 ,class = ENABLE_TYPE<IS_SAME_HELP<REMOVE_CVR_TYPE<_ARG1> ,REMOVE_CVR_TYPE<UNIT>>>>
	imports PhanRef make (_ARG1 &val) {
		PhanRef ret ;
		ret.mPointer = DEPTR[val] ;
		return _MOVE_ (ret) ;
	}

	template <class _ARG1>
	imports PhanRef make (const PhanRef<_ARG1> &val) {
		if (!val.exist ())
			return PhanRef () ;
		auto &r1x = _FORWARD_ (ARGV<UNIT>::ID ,val.self) ;
		return make (r1x) ;
	}

private:
	explicit PhanRef (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mPointer (NULL) {}
} ;

template <class>
class Function ;

class FunctorDecayProc :
	delegate public Wrapped<> {
public:
	template <class _ARG1 ,class _ARG2>
	imports PTR<_ARG1> invoke (const ARGVF<_ARG1> & ,_ARG2 &functor) {
		return template_decay (ARGV<_ARG1>::ID ,functor ,ARGVPX) ;
	}

private:
	template <class _ARG1 ,class _ARG2 ,class = ENABLE_TYPE<IS_CONVERTIBLE_HELP<_ARG2 ,PTR<_ARG1>>>>
	imports PTR<_ARG1> template_decay (const ARGVF<_ARG1> & ,_ARG2 &functor ,const DEF<decltype (ARGVP2)> &) {
		return _FORWARD_ (ARGV<PTR<_ARG1>>::ID ,functor) ;
	}

	template <class _ARG1 ,class _ARG2>
	imports PTR<_ARG1> template_decay (const ARGVF<_ARG1> & ,_ARG2 &functor ,const DEF<decltype (ARGVP1)> &) {
		return NULL ;
	}
} ;

template <class UNIT1 ,class... UNITS>
class Function<UNIT1 (UNITS...)> final {
private:
	struct Private {
		template <class>
		class ImplHolder ;

		template <class ,class>
		class MemPtrHolder ;
	} ;

	class Holder :
		delegate public Interface {
	public:
		virtual UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const = 0 ;
	} ;

private:
	PTR<NONE> mOrigin ;
	PTR<Holder> mPointer ;
	PTR<UNIT1 (UNITS...)> mFastPointer ;

public:
	implicit Function () :
		delegate Function (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	implicit Function (const DEF<UNIT1 (UNITS...)> &that) :
		delegate Function (ARGVP0) {
		mFastPointer = DEPTR[that] ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<U::CONSTEXPR_AND<U::CONSTEXPR_NOT<IS_PLACEHOLDER_HELP<_ARG1>> ,U::CONSTEXPR_NOT<IS_SAME_HELP<REMOVE_CVR_TYPE<_ARG1> ,Function>>>>>
	implicit Function (_ARG1 &&that) :
		delegate Function (ARGVP0) {
		using R1X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template ImplHolder<REMOVE_REFERENCE_TYPE<_ARG1>> ;
		_STATIC_ASSERT_ (IS_SAME_HELP<RESULT_OF_TYPE<_ARG1 ,ARGVS<UNITS...>> ,UNIT1>::compile ()) ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<R1X>>::ID) ;
		ScopedBuild<R1X> ANONYMOUS (rax ,ARGVP0 ,_FORWARD_ (ARGV<_ARG1 &&>::ID ,that)) ;
		const auto r1x = _POINTER_CAST_ (ARGV<R1X>::ID ,rax.self) ;
		mOrigin = rax.self ;
		mPointer = r1x ;
		mFastPointer = FunctorDecayProc::invoke (ARGV<UNIT1 (UNITS...)>::ID ,DEREF[r1x].deref ()) ;
		rax = NULL ;
	}

	template <class _ARG1>
	explicit Function (PhanRef<_ARG1> &&context_ ,const MEMPTR<DEF<UNIT1 (UNITS...)> ,_ARG1> &functor) :
		delegate Function (ARGVP0) {
		using R1X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template MemPtrHolder<_ARG1 ,ARGC<1>> ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<R1X>>::ID) ;
		ScopedBuild<R1X> ANONYMOUS (rax ,functor ,_MOVE_ (context_)) ;
		const auto r1x = _POINTER_CAST_ (ARGV<R1X>::ID ,rax.self) ;
		mOrigin = rax.self ;
		mPointer = r1x ;
		mFastPointer = NULL ;
		rax = NULL ;
	}

	template <class _ARG1>
	explicit Function (PhanRef<const _ARG1> &&context_ ,const MEMPTR<DEF<UNIT1 (UNITS...) const> ,_ARG1> &functor) :
		delegate Function (ARGVP0) {
		using R1X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template MemPtrHolder<_ARG1 ,ARGC<2>> ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<R1X>>::ID) ;
		ScopedBuild<R1X> ANONYMOUS (rax ,functor ,_MOVE_ (context_)) ;
		const auto r1x = _POINTER_CAST_ (ARGV<R1X>::ID ,rax.self) ;
		mOrigin = rax.self ;
		mPointer = r1x ;
		mFastPointer = NULL ;
		rax = NULL ;
	}

	template <class _ARG1 ,class _ARG2 ,class = ENABLE_TYPE<U::CONSTEXPR_NOT<IS_FUNCTION_HELP<_ARG2>>>>
	explicit Function (PhanRef<_ARG1> &&context_ ,const MEMPTR<_ARG2 ,_ARG1> &functor) :
		delegate Function (ARGVP0) {
		using R1X = typename DEPENDENT_TYPE<Private ,struct ANONYMOUS>::template MemPtrHolder<_ARG1 ,ARGC<3>> ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<R1X>>::ID) ;
		ScopedBuild<R1X> ANONYMOUS (rax ,functor ,_MOVE_ (context_)) ;
		const auto r1x = _POINTER_CAST_ (ARGV<R1X>::ID ,rax.self) ;
		mOrigin = rax.self ;
		mPointer = r1x ;
		mFastPointer = NULL ;
		rax = NULL ;
	}

	implicit ~Function () noexcept {
		if (mPointer == NULL)
			if (mFastPointer == NULL)
				return ;
		if switch_once (TRUE) {
			if (mPointer == NULL)
				discard ;
			DEREF[mPointer].~Holder () ;
			GlobalHeap::free (mOrigin) ;
		}
		mOrigin = NULL ;
		mPointer = NULL ;
		mFastPointer = NULL ;
	}

	implicit Function (const Function &) = delete ;

	inline Function &operator= (const Function &) = delete ;

	implicit Function (Function &&that) noexcept :
		delegate Function (ARGVP0) {
		_SWAP_ (mOrigin ,that.mOrigin) ;
		_SWAP_ (mPointer ,that.mPointer) ;
		_SWAP_ (mFastPointer ,that.mFastPointer) ;
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
			if (mFastPointer == NULL)
				return FALSE ;
		return TRUE ;
	}

	const DEF<UNIT1 (UNITS...)> &to () const leftvalue {
		_DEBUG_ASSERT_ (mFastPointer != NULL) ;
		return DEREF[mFastPointer] ;
	}

	inline implicit operator const DEF<UNIT1 (UNITS...)> & () const leftvalue {
		return self ;
	}

	inline implicit operator PTR<UNIT1 (UNITS...)> () const leftvalue = delete ;

	UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const {
		_DEBUG_ASSERT_ (exist ()) ;
		if (mFastPointer != NULL)
			return mFastPointer (_FORWARD_ (ARGV<FORWARD_TRAITS_TYPE<UNITS> &&>::ID ,funcval)...) ;
		return DEREF[mPointer].invoke (_FORWARD_ (ARGV<FORWARD_TRAITS_TYPE<UNITS> &&>::ID ,funcval)...) ;
	}

	inline UNIT1 operator() (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const {
		return invoke (_FORWARD_ (ARGV<FORWARD_TRAITS_TYPE<UNITS> &&>::ID ,funcval)...) ;
	}

private:
	explicit Function (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mOrigin (NULL) ,
		delegate mPointer (NULL) ,
		delegate mFastPointer (NULL) {}
} ;

template <class UNIT1 ,class... UNITS>
template <class UNIT_>
class Function<UNIT1 (UNITS...)>::Private::ImplHolder :
	delegate public Holder {
	_STATIC_ASSERT_ (IS_SAME_HELP<RESULT_OF_TYPE<UNIT_ ,ARGVS<UNITS...>> ,UNIT1>::compile ()) ;

private:
	UNIT_ mFunctor ;

public:
	implicit ImplHolder () = delete ;

	template <class... _ARGS>
	explicit ImplHolder (const DEF<decltype (ARGVP0)> & ,_ARGS &&...initval) :
		delegate mFunctor (_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) {}

	UNIT_ &deref () leftvalue {
		return mFunctor ;
	}

	UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const override {
		return mFunctor (_FORWARD_ (ARGV<FORWARD_TRAITS_TYPE<UNITS> &&>::ID ,funcval)...) ;
	}
} ;

template <class UNIT1 ,class... UNITS>
template <class UNIT_>
class Function<UNIT1 (UNITS...)>::Private::MemPtrHolder<UNIT_ ,ARGC<1>> :
	delegate public Holder {
private:
	MEMPTR<DEF<UNIT1 (UNITS...)> ,UNIT_> mFunctor ;
	PhanRef<UNIT_> mContext ;

public:
	implicit MemPtrHolder () = delete ;

	template <class... _ARGS>
	explicit MemPtrHolder (PhanRef<UNIT_> &&context_ ,_ARGS &&...initval) :
		delegate mFunctor (_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) ,
		delegate mContext (_MOVE_ (context_)) {}

	UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const override {
		auto &r1x = mContext.self ;
		return (r1x.*mFunctor) (_FORWARD_ (ARGV<FORWARD_TRAITS_TYPE<UNITS> &&>::ID ,funcval)...) ;
	}
} ;

template <class UNIT1 ,class... UNITS>
template <class UNIT_>
class Function<UNIT1 (UNITS...)>::Private::MemPtrHolder<UNIT_ ,ARGC<2>> :
	delegate public Holder {
private:
	MEMPTR<DEF<UNIT1 (UNITS...) const> ,UNIT_> mFunctor ;
	PhanRef<const UNIT_> mContext ;

public:
	implicit MemPtrHolder () = delete ;

	template <class... _ARGS>
	explicit MemPtrHolder (PhanRef<const UNIT_> &&context_ ,_ARGS &&...initval) :
		delegate mFunctor (_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) ,
		delegate mContext (_MOVE_ (context_)) {}

	UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const override {
		auto &r1x = mContext.self ;
		return (r1x.*mFunctor) (_FORWARD_ (ARGV<FORWARD_TRAITS_TYPE<UNITS> &&>::ID ,funcval)...) ;
	}
} ;

template <class UNIT1 ,class... UNITS>
template <class UNIT_>
class Function<UNIT1 (UNITS...)>::Private::MemPtrHolder<UNIT_ ,ARGC<3>> :
	delegate public Holder {
	_STATIC_ASSERT_ (_CAPACITYOF_ (ARGVS<UNITS...>) == 0) ;

private:
	MEMPTR<REMOVE_REFERENCE_TYPE<UNIT1> ,UNIT_> mFunctor ;
	PhanRef<UNIT_> mContext ;

public:
	implicit MemPtrHolder () = delete ;

	template <class... _ARGS>
	explicit MemPtrHolder (PhanRef<UNIT_> &&context_ ,_ARGS &&...initval) :
		delegate mFunctor (_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) ,
		delegate mContext (_MOVE_ (context_)) {}

	UNIT1 invoke (FORWARD_TRAITS_TYPE<UNITS> &&...funcval) const override {
		auto &r1x = mContext.self ;
		return (r1x.*mFunctor) ;
	}
} ;

template <class ,class>
class Buffer ;

using SFLEX = ZERO ;
using SFIXED = ARGC<(-1)> ;
using SAUTO = ARGC<(-2)> ;
using SCPHAN = ARGC<(-4)> ;
using SMPHAN = ARGC<(-5)> ;

template <class UNIT ,class SIZE>
class Buffer {
	_STATIC_ASSERT_ (U::CONSTEXPR_COMPR_GT<SIZE ,ZERO>::compile ()) ;
	_STATIC_ASSERT_ (IS_COMPLETE_HELP<UNIT ,struct ANONYMOUS>::compile ()) ;

private:
	using BUFFER = ARRAY_BIND_TYPE<REMOVE_CVR_TYPE<UNIT> ,SIZE> ;

private:
#ifdef __CSC_COMPILER_MSVC__
	//@error: fuck vs2017
	template <class ,class>
	friend class Buffer ;
#endif
	BUFFER mBuffer ;

public:
	implicit Buffer () = default ;

	explicit Buffer (const LENGTH &len) {
		_DEBUG_ASSERT_ (len >= 0 && len <= SIZE::compile ()) ;
	}

	implicit Buffer (const BUFFER &that) :
		delegate Buffer (_MOVE_ (_CAST_ (ARGV<Buffer>::ID ,that))) {
		_STATIC_WARNING_ ("noop") ;
	}

	implicit Buffer (BUFFER &&that) :
		delegate Buffer (_MOVE_ (_CAST_ (ARGV<Buffer>::ID ,that))) {
		_STATIC_WARNING_ ("noop") ;
	}

	ARR<UNIT> &to () leftvalue {
		return PTRTOARR[mBuffer] ;
	}

	inline implicit operator ARR<UNIT> & () leftvalue {
		return self ;
	}

	inline implicit operator PTR<UNIT> () leftvalue = delete ;

	const ARR<UNIT> &to () const leftvalue {
		return PTRTOARR[mBuffer] ;
	}

	inline implicit operator const ARR<UNIT> & () const leftvalue {
		return self ;
	}

	inline implicit operator PTR<const UNIT> () leftvalue = delete ;

	LENGTH size () const {
		return SIZE::compile () ;
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
		return BasicProc::mem_equal (PTRTOARR[mBuffer] ,PTRTOARR[that.mBuffer] ,SIZE::compile ()) ;
	}

	inline BOOL operator== (const Buffer &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const Buffer &that) const {
		return !equal (that) ;
	}

	FLAG compr (const Buffer &that) const {
		return BasicProc::mem_compr (PTRTOARR[mBuffer] ,PTRTOARR[that.mBuffer] ,SIZE::compile ()) ;
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
		BasicProc::mem_swap (PTRTOARR[mBuffer] ,PTRTOARR[that.mBuffer] ,SIZE::compile ()) ;
	}
} ;

template <class UNIT>
class Buffer<UNIT ,SFIXED> final {
	_STATIC_ASSERT_ (IS_COMPLETE_HELP<UNIT ,struct ANONYMOUS>::compile ()) ;

private:
	PTR<NONE> mOrigin ;
	PTR<ARR<UNIT>> mBuffer ;
	LENGTH mSize ;

public:
	implicit Buffer () :
		delegate Buffer (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	explicit Buffer (const LENGTH &len) :
		delegate Buffer (ARGVP0) {
		if (len == 0)
			return ;
		_DEBUG_ASSERT_ (len > 0) ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<UNIT>>::ID ,len) ;
		ScopedBuild<ARR<UNIT>> ANONYMOUS (rax ,len) ;
		mOrigin = rax.self ;
		const auto r1x = _POINTER_CAST_ (ARGV<ARR<UNIT>>::ID ,rax.self) ;
		mBuffer = r1x ;
		mSize = len ;
		rax = NULL ;
	}

	implicit ~Buffer () noexcept {
		if (mBuffer == NULL)
			return ;
		for (auto &&i : _RANGE_ (0 ,mSize))
			DEREF[mBuffer][i].~UNIT () ;
		GlobalHeap::free (mOrigin) ;
		mOrigin = NULL ;
		mBuffer = NULL ;
		mSize = 0 ;
	}

	implicit Buffer (const Buffer &) = delete ;

	inline Buffer &operator= (const Buffer &) = delete ;

	implicit Buffer (Buffer &&) = delete ;

	inline Buffer &operator= (Buffer &&) = delete ;

	ARR<UNIT> &to () leftvalue {
		if (mBuffer == NULL)
			return _NULL_ (ARGV<ARR<UNIT>>::ID) ;
		return DEREF[mBuffer] ;
	}

	inline implicit operator ARR<UNIT> & () leftvalue {
		return self ;
	}

	inline implicit operator PTR<UNIT> () leftvalue = delete ;

	const ARR<UNIT> &to () const leftvalue {
		if (mBuffer == NULL)
			return _NULL_ (ARGV<ARR<UNIT>>::ID) ;
		return DEREF[mBuffer] ;
	}

	inline implicit operator const ARR<UNIT> & () const leftvalue {
		return self ;
	}

	inline implicit operator PTR<const UNIT> () const leftvalue = delete ;

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
		return ComprInvokeProc::invoke (mSize ,that.mSize) ;
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
	explicit Buffer (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mOrigin (NULL) ,
		delegate mBuffer (NULL) ,
		delegate mSize (0) {}
} ;

template <class UNIT>
using FixedBuffer = CAST_TRAITS_TYPE<Buffer<REMOVE_CVR_TYPE<UNIT> ,SFIXED> ,UNIT> ;

template <class UNIT>
class Buffer<UNIT ,SAUTO> ;

template <class UNIT>
class Buffer<SPECIALIZATION<UNIT ,ARGC<FALSE>> ,SAUTO> {
	_STATIC_ASSERT_ (IS_COMPLETE_HELP<UNIT ,struct ANONYMOUS>::compile ()) ;

protected:
	PTR<NONE> mOrigin ;
	PTR<ARR<UNIT>> mBuffer ;
	LENGTH mSize ;

protected:
	implicit Buffer () :
		delegate Buffer (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	explicit Buffer (const LENGTH &len) :
		delegate Buffer (ARGVP0) {
		if (len == 0)
			return ;
		_DEBUG_ASSERT_ (len > 0) ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<UNIT>>::ID ,len) ;
		ScopedBuild<ARR<UNIT>> ANONYMOUS (rax ,len) ;
		mOrigin = rax.self ;
		const auto r1x = _POINTER_CAST_ (ARGV<ARR<UNIT>>::ID ,rax.self) ;
		mBuffer = r1x ;
		mSize = len ;
		rax = NULL ;
	}

	implicit ~Buffer () noexcept {
		if (mBuffer == NULL)
			return ;
		for (auto &&i : _RANGE_ (0 ,mSize))
			DEREF[mBuffer][i].~UNIT () ;
		GlobalHeap::free (mOrigin) ;
		mOrigin = NULL ;
		mBuffer = NULL ;
		mSize = 0 ;
	}

	implicit Buffer (const Buffer &) = delete ;

	inline Buffer &operator= (const Buffer &) = delete ;

	implicit Buffer (Buffer &&that) noexcept :
		delegate Buffer (ARGVP0) {
		_SWAP_ (mOrigin ,that.mOrigin) ;
		_SWAP_ (mBuffer ,that.mBuffer) ;
		_SWAP_ (mSize ,that.mSize) ;
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

protected:
	explicit Buffer (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mOrigin (NULL) ,
		delegate mBuffer (NULL) ,
		delegate mSize (0) {}
} ;

template <class UNIT>
class Buffer<SPECIALIZATION<UNIT ,ARGC<TRUE>> ,SAUTO> {
	_STATIC_ASSERT_ (IS_COMPLETE_HELP<UNIT ,struct ANONYMOUS>::compile ()) ;

protected:
	PTR<NONE> mOrigin ;
	PTR<ARR<UNIT>> mBuffer ;
	LENGTH mSize ;

protected:
	implicit Buffer () :
		delegate Buffer (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	explicit Buffer (const LENGTH &len) :
		delegate Buffer (ARGVP0) {
		if (len == 0)
			return ;
		_DEBUG_ASSERT_ (len > 0) ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<UNIT>>::ID ,len) ;
		ScopedBuild<ARR<UNIT>> ANONYMOUS (rax ,len) ;
		mOrigin = rax.self ;
		const auto r1x = _POINTER_CAST_ (ARGV<ARR<UNIT>>::ID ,rax.self) ;
		mBuffer = r1x ;
		mSize = len ;
		rax = NULL ;
	}

	implicit ~Buffer () noexcept {
		if (mBuffer == NULL)
			return ;
		for (auto &&i : _RANGE_ (0 ,mSize))
			DEREF[mBuffer][i].~UNIT () ;
		GlobalHeap::free (mOrigin) ;
		mOrigin = NULL ;
		mBuffer = NULL ;
		mSize = 0 ;
	}

	implicit Buffer (const Buffer &that) :
		delegate Buffer (ARGVP0) {
		if (that.mBuffer == NULL)
			return ;
		auto rax = GlobalHeap::alloc (ARGV<TEMP<UNIT>>::ID ,that.mSize) ;
		ScopedBuild<ARR<UNIT>> ANONYMOUS (rax ,DEREF[that.mBuffer] ,that.mSize) ;
		mOrigin = rax.self ;
		const auto r1x = _POINTER_CAST_ (ARGV<ARR<UNIT>>::ID ,rax.self) ;
		mBuffer = r1x ;
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

	implicit Buffer (Buffer &&that) noexcept :
		delegate Buffer (ARGVP0) {
		_SWAP_ (mOrigin ,that.mOrigin) ;
		_SWAP_ (mBuffer ,that.mBuffer) ;
		_SWAP_ (mSize ,that.mSize) ;
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

protected:
	explicit Buffer (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mOrigin (NULL) ,
		delegate mBuffer (NULL) ,
		delegate mSize (0) {}
} ;

template <class UNIT>
class Buffer<UNIT ,SAUTO> final :
	delegate private Buffer<SPECIALIZATION<UNIT ,ARGC_TYPE<IS_COPY_CONSTRUCTIBLE_HELP<UNIT>>> ,SAUTO> {
private:
	using SPECIALIZATION_BASE = Buffer<SPECIALIZATION<UNIT ,ARGC_TYPE<IS_COPY_CONSTRUCTIBLE_HELP<UNIT>>> ,SAUTO> ;

private:
	friend SPECIALIZATION_BASE ;
	using SPECIALIZATION_BASE::mOrigin ;
	using SPECIALIZATION_BASE::mBuffer ;
	using SPECIALIZATION_BASE::mSize ;

public:
	implicit Buffer () = default ;

	explicit Buffer (const LENGTH &len) :
		delegate SPECIALIZATION_BASE (len) {
		_STATIC_WARNING_ ("noop") ;
	}

	ARR<UNIT> &to () leftvalue {
		if (mBuffer == NULL)
			return _NULL_ (ARGV<ARR<UNIT>>::ID) ;
		return DEREF[mBuffer] ;
	}

	inline implicit operator ARR<UNIT> & () leftvalue {
		return self ;
	}

	inline implicit operator PTR<UNIT> () leftvalue = delete ;

	const ARR<UNIT> &to () const leftvalue {
		if (mBuffer == NULL)
			return _NULL_ (ARGV<ARR<UNIT>>::ID) ;
		return DEREF[mBuffer] ;
	}

	inline implicit operator const ARR<UNIT> & () const leftvalue {
		return self ;
	}

	inline implicit operator PTR<const UNIT> () const leftvalue = delete ;

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
		return ComprInvokeProc::invoke (mSize ,that.mSize) ;
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
		const auto r2x = mSize + DEFAULT_RECURSIVE_SIZE::compile () ;
		return _MAX_ (r1x ,r2x) ;
	}

	Buffer expand (const LENGTH &len) const {
		return Buffer (len) ;
	}

	void swap (Buffer &that) {
		_SWAP_ (mOrigin ,that.mOrigin) ;
		_SWAP_ (mBuffer ,that.mBuffer) ;
		_SWAP_ (mSize ,that.mSize) ;
	}
} ;

template <class UNIT>
using AutoBuffer = CAST_TRAITS_TYPE<Buffer<REMOVE_CVR_TYPE<UNIT> ,SAUTO> ,UNIT> ;

template <class UNIT>
class Buffer<UNIT ,SCPHAN> final {
	_STATIC_ASSERT_ (IS_COMPLETE_HELP<UNIT ,struct ANONYMOUS>::compile ()) ;

private:
	PTR<NONE> mOrigin ;
	PTR<const ARR<UNIT>> mBuffer ;
	LENGTH mSize ;

public:
	implicit Buffer () :
		delegate Buffer (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	explicit Buffer (const LENGTH &len) :
		delegate Buffer (ARGVP0) {
		_DEBUG_ASSERT_ (len == 0) ;
	}

	implicit ~Buffer () noexcept {
		if (mBuffer == NULL)
			return ;
		mBuffer = NULL ;
		mSize = 0 ;
	}

	implicit Buffer (const Buffer &) = delete ;

	inline Buffer &operator= (const Buffer &) = delete ;

	implicit Buffer (Buffer &&that) noexcept :
		delegate Buffer (ARGVP0) {
		_SWAP_ (mBuffer ,that.mBuffer) ;
		_SWAP_ (mSize ,that.mSize) ;
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
			return _NULL_ (ARGV<ARR<UNIT>>::ID) ;
		return DEREF[mBuffer] ;
	}

	inline implicit operator const ARR<UNIT> & () const leftvalue {
		return self ;
	}

	inline implicit operator PTR<const UNIT> () const leftvalue = delete ;

	LENGTH size () const {
		return mSize ;
	}

	const UNIT &get (const INDEX &index) const leftvalue {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
		_DEBUG_ASSERT_ (index >= 0 && index < size ()) ;
		return DEREF[mBuffer][index] ;
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
		return ComprInvokeProc::invoke (mSize ,that.mSize) ;
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

	//@warn: phantom means deliver pointer without holder
	imports Buffer make (const ARR<UNIT> &src ,const LENGTH &len) {
		return Buffer (ARGVP0 ,DEPTR[src] ,len) ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<IS_ARRAY_OF_HELP<UNIT ,_ARG1>>>
	imports Buffer make (_ARG1 &val) {
		return make (PTRTOARR[val] ,_COUNTOF_ (_ARG1)) ;
	}

	template <class _ARG1>
	imports Buffer make (const Buffer<UNIT ,_ARG1> &val) {
		return make (val.self ,val.size ()) ;
	}

	template <class _ARG1 ,class _ARG2 ,class = ENABLE_TYPE<U::CONSTEXPR_AND<IS_SAME_HELP<UNIT ,BYTE> ,U::CONSTEXPR_NOT<IS_SAME_HELP<_ARG1 ,BYTE>>>>>
	imports Buffer make (const Buffer<_ARG1 ,_ARG2> &val) {
		_STATIC_ASSERT_ (IS_SAFE_ALIASING_HELP<ARR<BYTE> ,ARR<_ARG1>>::compile ()) ;
		const auto r1x = _POINTER_CAST_ (ARGV<ARR<BYTE>>::ID ,DEPTR[val.self]) ;
		const auto r2x = val.size () * _SIZEOF_ (_ARG1) ;
		return make (DEREF[r1x] ,r2x) ;
	}

private:
	explicit Buffer (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mOrigin (NULL) ,
		delegate mBuffer (NULL) ,
		delegate mSize (0) {}

	explicit Buffer (const DEF<decltype (ARGVP0)> & ,const PTR<const ARR<UNIT>> &buffer ,const LENGTH &size_) :
		delegate Buffer (ARGVP0) {
		if (size_ == 0)
			return ;
		_DEBUG_ASSERT_ (size_ > 0) ;
		mBuffer = buffer ;
		mSize = size_ ;
	}
} ;

template <class UNIT>
class Buffer<UNIT ,SMPHAN> final {
	_STATIC_ASSERT_ (IS_COMPLETE_HELP<UNIT ,struct ANONYMOUS>::compile ()) ;

private:
	PTR<NONE> mOrigin ;
	PTR<ARR<UNIT>> mBuffer ;
	LENGTH mSize ;

public:
	implicit Buffer () :
		delegate Buffer (ARGVP0) {
		_STATIC_WARNING_ ("noop") ;
	}

	explicit Buffer (const LENGTH &len) :
		delegate Buffer (ARGVP0) {
		_DEBUG_ASSERT_ (len == 0) ;
	}

	implicit ~Buffer () noexcept {
		if (mBuffer == NULL)
			return ;
		mBuffer = NULL ;
		mSize = 0 ;
	}

	implicit Buffer (const Buffer &) = delete ;

	inline Buffer &operator= (const Buffer &) = delete ;

	implicit Buffer (Buffer &&that) noexcept :
		delegate Buffer (ARGVP0) {
		_SWAP_ (mBuffer ,that.mBuffer) ;
		_SWAP_ (mSize ,that.mSize) ;
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
			return _NULL_ (ARGV<ARR<UNIT>>::ID) ;
		return DEREF[mBuffer] ;
	}

	inline implicit operator ARR<UNIT> & () const leftvalue {
		return self ;
	}

	inline implicit operator PTR<UNIT> () const leftvalue = delete ;

	LENGTH size () const {
		return mSize ;
	}

	UNIT &get (const INDEX &index) const leftvalue {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
		_DEBUG_ASSERT_ (index >= 0 && index < size ()) ;
		return DEREF[mBuffer][index] ;
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
		return ComprInvokeProc::invoke (mSize ,that.mSize) ;
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

	//@warn: phantom means deliver pointer without holder
	imports Buffer make (ARR<UNIT> &src ,const LENGTH &len) {
		return Buffer (ARGVP0 ,DEPTR[src] ,len) ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<IS_ARRAY_OF_HELP<UNIT ,_ARG1>>>
	imports Buffer make (_ARG1 &val) {
		return make (PTRTOARR[val] ,_COUNTOF_ (_ARG1)) ;
	}

	template <class _ARG1>
	imports Buffer make (Buffer<UNIT ,_ARG1> &val) {
		return make (val.self ,val.size ()) ;
	}

	imports Buffer make (const Buffer<UNIT ,SMPHAN> &val) {
		return make (val.self ,val.size ()) ;
	}

	template <class _ARG1 ,class _ARG2 ,class = ENABLE_TYPE<U::CONSTEXPR_AND<IS_SAME_HELP<UNIT ,BYTE> ,U::CONSTEXPR_NOT<IS_SAME_HELP<_ARG1 ,BYTE>>>>>
	imports Buffer make (Buffer<_ARG1 ,_ARG2> &val) {
		_STATIC_ASSERT_ (IS_SAFE_ALIASING_HELP<ARR<BYTE> ,ARR<_ARG1>>::compile ()) ;
		const auto r1x = _POINTER_CAST_ (ARGV<ARR<BYTE>>::ID ,DEPTR[val.self]) ;
		const auto r2x = val.size () * _SIZEOF_ (_ARG1) ;
		return make (DEREF[r1x] ,r2x) ;
	}

	template <class _ARG1 ,class = ENABLE_TYPE<U::CONSTEXPR_AND<IS_SAME_HELP<UNIT ,BYTE> ,U::CONSTEXPR_NOT<IS_SAME_HELP<_ARG1 ,BYTE>>>>>
	imports Buffer make (const Buffer<_ARG1 ,SMPHAN> &val) {
		_STATIC_ASSERT_ (IS_SAFE_ALIASING_HELP<ARR<BYTE> ,ARR<_ARG1>>::compile ()) ;
		const auto r1x = _POINTER_CAST_ (ARGV<ARR<BYTE>>::ID ,DEPTR[val.self]) ;
		const auto r2x = val.size () * _SIZEOF_ (_ARG1) ;
		return make (DEREF[r1x] ,r2x) ;
	}

private:
	explicit Buffer (const DEF<decltype (ARGVP0)> &) noexcept :
		delegate mOrigin (NULL) ,
		delegate mBuffer (NULL) ,
		delegate mSize (0) {}

	explicit Buffer (const DEF<decltype (ARGVP0)> & ,const PTR<ARR<UNIT>> &buffer ,const LENGTH &size_) :
		delegate Buffer (ARGVP0) {
		if (size_ == 0)
			return ;
		_DEBUG_ASSERT_ (size_ > 0) ;
		mBuffer = buffer ;
		mSize = size_ ;
	}
} ;

template <class UNIT>
using PhanBuffer = Buffer<REMOVE_CONST_TYPE<UNIT> ,CONDITIONAL_TYPE<IS_CONST_HELP<UNIT> ,SCPHAN ,SMPHAN>> ;

template <class ,class>
class Allocator ;

template <class UNIT ,class SIZE>
class Allocator<SPECIALIZATION<UNIT ,ARGC<FALSE> ,ARGC<FALSE>> ,SIZE> {
#pragma push_macro ("spec")
#undef spec
#define spec m_spec ()

protected:
	using SPECIALIZATION_THIS = Allocator<UNIT ,SIZE> ;

	//@warn: memory alignment reduce utilization ratio of memory
	struct NODE_PACK {
		TEMP<UNIT> mValue ;
		INDEX mNext ;
	} ;

protected:
	Buffer<NODE_PACK ,SIZE> mAllocator ;
	LENGTH mSize ;
	LENGTH mLength ;
	INDEX mFree ;

protected:
	implicit Allocator () :
		delegate Allocator (ARGVP0 ,0) {
		spec.update_reserve (mSize ,mFree) ;
	}

	explicit Allocator (const LENGTH &len) :
		delegate Allocator (ARGVP0 ,len) {
		spec.update_reserve (mSize ,mFree) ;
	}

	implicit ~Allocator () noexcept {
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

	implicit Allocator (const Allocator &) = delete ;

	inline Allocator &operator= (const Allocator &) = delete ;

	implicit Allocator (Allocator &&) = delete ;

	inline Allocator &operator= (Allocator &&) = delete ;

protected:
	explicit Allocator (const DEF<decltype (ARGVP0)> & ,const LENGTH &len) :
		delegate mAllocator (len) ,
		delegate mSize (0) ,
		delegate mLength (0) ,
		delegate mFree (VAR_NONE) {}

	inline SPECIALIZATION_THIS &m_spec () leftvalue {
		const auto r1x = _POINTER_CAST_ (ARGV<SPECIALIZATION_THIS>::ID ,this) ;
		_DEBUG_ASSERT_ (r1x != NULL) ;
		return DEREF[r1x] ;
	}

	inline const SPECIALIZATION_THIS &m_spec () const leftvalue {
		const auto r1x = _POINTER_CAST_ (ARGV<SPECIALIZATION_THIS>::ID ,this) ;
		_DEBUG_ASSERT_ (r1x != NULL) ;
		return DEREF[r1x] ;
	}

#pragma pop_macro ("spec")
} ;

template <class UNIT ,class SIZE>
class Allocator<SPECIALIZATION<UNIT ,ARGC<FALSE> ,ARGC<TRUE>> ,SIZE> {
#pragma push_macro ("spec")
#undef spec
#define spec m_spec ()

protected:
	using SPECIALIZATION_THIS = Allocator<UNIT ,SIZE> ;

	//@warn: memory alignment reduce utilization ratio of memory
	struct NODE_PACK {
		TEMP<UNIT> mValue ;
		INDEX mNext ;
	} ;

protected:
	Buffer<NODE_PACK ,SIZE> mAllocator ;
	LENGTH mSize ;
	LENGTH mLength ;
	INDEX mFree ;

protected:
	implicit Allocator () :
		delegate Allocator (ARGVP0 ,0) {
		spec.update_reserve (mSize ,mFree) ;
	}

	explicit Allocator (const LENGTH &len) :
		delegate Allocator (ARGVP0 ,len) {
		spec.update_reserve (mSize ,mFree) ;
	}

	implicit ~Allocator () noexcept {
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

	implicit Allocator (const Allocator &) = delete ;

	inline Allocator &operator= (const Allocator &) = delete ;

	implicit Allocator (Allocator &&that) noexcept :
		delegate Allocator (ARGVP0 ,_MOVE_ (that.mAllocator)) {
		using R1X = IS_TRIVIAL_HELP<UNIT> ;
		if (mAllocator.size () != that.mAllocator.size ())
			_SWAP_ (mSize ,that.mSize) ;
		const auto r1x = that.mSize - mSize ;
		const auto r2x = VAR_ZERO ;
		mSize += _MAX_ (r1x ,r2x) * _EBOOL_ (R1X::compile ()) ;
		while (TRUE) {
			if (mSize >= that.mSize)
				break ;
			if switch_once (TRUE) {
				INDEX ix = mSize ;
				if (mAllocator[ix].mNext != VAR_USED)
					discard ;
				_CREATE_ (DEPTR[mAllocator[ix].mValue] ,_MOVE_ (_CAST_ (ARGV<UNIT>::ID ,that.mAllocator[ix].mValue))) ;
			}
			mSize++ ;
		}
		_SWAP_ (mLength ,that.mLength) ;
		_SWAP_ (mFree ,that.mFree) ;
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
	explicit Allocator (const DEF<decltype (ARGVP0)> & ,const LENGTH &len) :
		delegate mAllocator (len) ,
		delegate mSize (0) ,
		delegate mLength (0) ,
		delegate mFree (VAR_NONE) {}

	explicit Allocator (const DEF<decltype (ARGVP0)> & ,Buffer<NODE_PACK ,SIZE> &&allocator_) :
		delegate mAllocator (_MOVE_ (allocator_)) ,
		delegate mSize (0) ,
		delegate mLength (0) ,
		delegate mFree (VAR_NONE) {}

	inline SPECIALIZATION_THIS &m_spec () leftvalue {
		const auto r1x = _POINTER_CAST_ (ARGV<SPECIALIZATION_THIS>::ID ,this) ;
		_DEBUG_ASSERT_ (r1x != NULL) ;
		return DEREF[r1x] ;
	}

	inline const SPECIALIZATION_THIS &m_spec () const leftvalue {
		const auto r1x = _POINTER_CAST_ (ARGV<SPECIALIZATION_THIS>::ID ,this) ;
		_DEBUG_ASSERT_ (r1x != NULL) ;
		return DEREF[r1x] ;
	}

#pragma pop_macro ("spec")
} ;

template <class UNIT ,class SIZE>
class Allocator<SPECIALIZATION<UNIT ,ARGC<TRUE> ,ARGC<TRUE>> ,SIZE> {
#pragma push_macro ("spec")
#undef spec
#define spec m_spec ()

protected:
	using SPECIALIZATION_THIS = Allocator<UNIT ,SIZE> ;

	//@warn: memory alignment reduce utilization ratio of memory
	struct NODE_PACK {
		TEMP<UNIT> mValue ;
		INDEX mNext ;
	} ;

protected:
	Buffer<NODE_PACK ,SIZE> mAllocator ;
	LENGTH mSize ;
	LENGTH mLength ;
	INDEX mFree ;

protected:
	implicit Allocator () :
		delegate Allocator (ARGVP0 ,0) {
		spec.update_reserve (mSize ,mFree) ;
	}

	explicit Allocator (const LENGTH &len) :
		delegate Allocator (ARGVP0 ,len) {
		spec.update_reserve (mSize ,mFree) ;
	}

	implicit ~Allocator () noexcept {
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

	implicit Allocator (const Allocator &that) :
		delegate Allocator (ARGVP0 ,_MOVE_ (that.mAllocator)) {
		using R1X = IS_TRIVIAL_HELP<UNIT> ;
		if (mAllocator.size () != that.mAllocator.size ())
			mSize = that.mSize ;
		const auto r1x = that.mSize - mSize ;
		const auto r2x = VAR_ZERO ;
		mSize += _MAX_ (r1x ,r2x) * _EBOOL_ (R1X::compile ()) ;
		while (TRUE) {
			if (mSize >= that.mSize)
				break ;
			if switch_once (TRUE) {
				INDEX ix = mSize ;
				if (mAllocator[ix].mNext != VAR_USED)
					discard ;
				_CREATE_ (DEPTR[mAllocator[ix].mValue] ,_MOVE_ (_CAST_ (ARGV<UNIT>::ID ,that.mAllocator[ix].mValue))) ;
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

	implicit Allocator (Allocator &&that) noexcept :
		delegate Allocator (ARGVP0 ,_MOVE_ (that.mAllocator)) {
		using R1X = IS_TRIVIAL_HELP<UNIT> ;
		if (mAllocator.size () != that.mAllocator.size ())
			_SWAP_ (mSize ,that.mSize) ;
		const auto r1x = that.mSize - mSize ;
		const auto r2x = VAR_ZERO ;
		mSize += _MAX_ (r1x ,r2x) * _EBOOL_ (R1X::compile ()) ;
		while (TRUE) {
			if (mSize >= that.mSize)
				break ;
			if switch_once (TRUE) {
				INDEX ix = mSize ;
				if (mAllocator[ix].mNext != VAR_USED)
					discard ;
				_CREATE_ (DEPTR[mAllocator[ix].mValue] ,_MOVE_ (_CAST_ (ARGV<UNIT>::ID ,that.mAllocator[ix].mValue))) ;
			}
			mSize++ ;
		}
		_SWAP_ (mLength ,that.mLength) ;
		_SWAP_ (mFree ,that.mFree) ;
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

protected:
	explicit Allocator (const DEF<decltype (ARGVP0)> & ,const LENGTH &len) :
		delegate mAllocator (len) ,
		delegate mSize (0) ,
		delegate mLength (0) ,
		delegate mFree (VAR_NONE) {}

	explicit Allocator (const DEF<decltype (ARGVP0)> & ,const Buffer<NODE_PACK ,SIZE> &allocator_) :
		delegate mAllocator (_MOVE_ (allocator_)) ,
		delegate mSize (0) ,
		delegate mLength (0) ,
		delegate mFree (VAR_NONE) {}

	explicit Allocator (const DEF<decltype (ARGVP0)> & ,Buffer<NODE_PACK ,SIZE> &&allocator_) :
		delegate mAllocator (_MOVE_ (allocator_)) ,
		delegate mSize (0) ,
		delegate mLength (0) ,
		delegate mFree (VAR_NONE) {}

	inline SPECIALIZATION_THIS &m_spec () leftvalue {
		const auto r1x = _POINTER_CAST_ (ARGV<SPECIALIZATION_THIS>::ID ,this) ;
		_DEBUG_ASSERT_ (r1x != NULL) ;
		return DEREF[r1x] ;
	}

	inline const SPECIALIZATION_THIS &m_spec () const leftvalue {
		const auto r1x = _POINTER_CAST_ (ARGV<SPECIALIZATION_THIS>::ID ,this) ;
		_DEBUG_ASSERT_ (r1x != NULL) ;
		return DEREF[r1x] ;
	}

#pragma pop_macro ("spec")
} ;

template <class UNIT ,class SIZE>
class Allocator final :
	delegate private Allocator<SPECIALIZATION<UNIT ,ARGC_TYPE<IS_COPY_CONSTRUCTIBLE_HELP<Buffer<UNIT ,SIZE>>> ,ARGC_TYPE<IS_MOVE_CONSTRUCTIBLE_HELP<Buffer<UNIT ,SIZE>>>> ,SIZE> {

private:
	using SPECIALIZATION_BASE = Allocator<SPECIALIZATION<UNIT ,ARGC_TYPE<IS_COPY_CONSTRUCTIBLE_HELP<Buffer<UNIT ,SIZE>>> ,ARGC_TYPE<IS_MOVE_CONSTRUCTIBLE_HELP<Buffer<UNIT ,SIZE>>>> ,SIZE> ;

private:
	friend SPECIALIZATION_BASE ;
	using SPECIALIZATION_BASE::mAllocator ;
	using SPECIALIZATION_BASE::mSize ;
	using SPECIALIZATION_BASE::mLength ;
	using SPECIALIZATION_BASE::mFree ;

public:
	implicit Allocator () = default ;

	explicit Allocator (const LENGTH &len) :
		delegate SPECIALIZATION_BASE (len) {
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
		for (auto &&i : _RANGE_ (0 ,mSize)) {
			INDEX iy = ix ;
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
		return _CAST_ (ARGV<UNIT>::ID ,mAllocator[index].mValue) ;
	}

	inline UNIT &operator[] (const INDEX &index) leftvalue {
		return get (index) ;
	}

	const UNIT &get (const INDEX &index) const leftvalue {
		_DEBUG_ASSERT_ (used (index)) ;
		return _CAST_ (ARGV<UNIT>::ID ,mAllocator[index].mValue) ;
	}

	inline const UNIT &operator[] (const INDEX &index) const leftvalue {
		return get (index) ;
	}

	INDEX at (const UNIT &item) const {
		using R1X = typename SPECIALIZATION_BASE::NODE_PACK ;
		auto &r1x = _OFFSET_ (&R1X::mValue ,_CAST_ (ARGV<TEMP<UNIT>>::ID ,item)) ;
		INDEX ret = mAllocator.at (r1x) ;
		if (!used (ret))
			ret = VAR_NONE ;
		return _MOVE_ (ret) ;
	}

	template <class... _ARGS>
	INDEX alloc (_ARGS &&...initval) {
		_STATIC_ASSERT_ (IS_MOVE_CONSTRUCTIBLE_HELP<UNIT>::compile ()) ;
		INDEX ret = VAR_NONE ;
		auto fax = TRUE ;
		if switch_once (fax) {
			if (mFree != VAR_NONE)
				discard ;
			auto rax = mAllocator.expand (mAllocator.expand_size ()) ;
			ret = mSize ;
			_CREATE_ (DEPTR[rax[ret].mValue] ,_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) ;
			for (auto &&i : _RANGE_ (0 ,mSize)) {
				_CREATE_ (DEPTR[rax[i].mValue] ,_MOVE_ (_CAST_ (ARGV<UNIT>::ID ,mAllocator[i].mValue))) ;
				rax[i].mNext = VAR_USED ;
			}
			mAllocator.swap (rax) ;
			update_reserve (mSize ,mFree) ;
		}
		if switch_once (fax) {
			ret = mFree ;
			_CREATE_ (DEPTR[mAllocator[ret].mValue] ,_FORWARD_ (ARGV<_ARGS &&>::ID ,initval)...) ;
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
		_STATIC_ASSERT_ (IS_MOVE_CONSTRUCTIBLE_HELP<UNIT>::compile ()) ;
		_DEBUG_ASSERT_ (len >= 0) ;
		const auto r1x = len - (mSize - mLength) ;
		const auto r2x = VAR_ZERO ;
		const auto r3x = _MAX_ (r1x ,r2x) ;
		if (r3x == 0)
			return ;
		_DEBUG_ASSERT_ (mSize + r3x > mSize) ;
		auto rax = mAllocator.expand (mSize + r3x) ;
		for (auto &&i : _RANGE_ (0 ,mSize)) {
			if (mAllocator[i].mNext == VAR_USED)
				_CREATE_ (DEPTR[rax[i].mValue] ,_MOVE_ (_CAST_ (ARGV<UNIT>::ID ,mAllocator[i].mValue))) ;
			rax[i].mNext = mAllocator[i].mNext ;
		}
		mAllocator.swap (rax) ;
		update_reserve (mSize ,mFree) ;
	}

	void clean () {
		_STATIC_ASSERT_ (IS_MOVE_CONSTRUCTIBLE_HELP<UNIT>::compile ()) ;
		const auto r1x = shrink_size () ;
		if (r1x == mSize)
			return ;
		_DYNAMIC_ASSERT_ (r1x == mLength) ;
		auto rax = mAllocator.expand (r1x) ;
		for (auto &&i : _RANGE_ (0 ,rax.size ())) {
			_DEBUG_ASSERT_ (mAllocator[i].mNext == VAR_USED) ;
			_CREATE_ (DEPTR[rax[i].mValue] ,_MOVE_ (_CAST_ (ARGV<UNIT>::ID ,mAllocator[i].mValue))) ;
			rax[i].mNext = VAR_USED ;
		}
		mAllocator.swap (rax) ;
		update_reserve (r1x ,VAR_NONE) ;
	}

private:
	void update_reserve (const INDEX &size_ ,const INDEX &free_) noexcept {
		INDEX ix = free_ ;
		for (auto &&i : _RANGE_ (size_ ,mAllocator.size ())) {
			INDEX iy = ix ;
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