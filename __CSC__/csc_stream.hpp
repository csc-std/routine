﻿#pragma once

#ifndef __CSC_STREAM__
#define __CSC_STREAM__
#endif

#include "csc.hpp"
#include "csc_core.hpp"
#include "csc_basic.hpp"
#include "csc_array.hpp"
#include "csc_math.hpp"

namespace CSC {
namespace U {
template <class ,class>
struct BYTE_BASE ;

template <>
struct BYTE_BASE<ARGC<_SIZEOF_ (BYTE)> ,ARGC<_ALIGNOF_ (BYTE)>> {
	using TYPE = BYTE ;
} ;

template <>
struct BYTE_BASE<ARGC<_SIZEOF_ (WORD)> ,ARGC<_ALIGNOF_ (WORD)>> {
	using TYPE = WORD ;
} ;

template <>
struct BYTE_BASE<ARGC<_SIZEOF_ (CHAR)> ,ARGC<_ALIGNOF_ (CHAR)>> {
	using TYPE = CHAR ;
} ;

template <>
struct BYTE_BASE<ARGC<_SIZEOF_ (DATA)> ,ARGC<_ALIGNOF_ (DATA)>> {
	using TYPE = DATA ;
} ;

template <class _ARG1>
using BYTE_BASE_TYPE = typename U::BYTE_BASE<ARGC<_SIZEOF_ (_ARG1)> ,ARGC<_ALIGNOF_ (_ARG1)>>::TYPE ;
} ;

namespace U {
template <class ,class>
struct TEXT_BASE ;

template <>
struct TEXT_BASE<ARGC<_SIZEOF_ (STRU8)> ,ARGC<_ALIGNOF_ (STRU8)>> {
	using TYPE = STRU8 ;
} ;

template <>
struct TEXT_BASE<ARGC<_SIZEOF_ (STRU16)> ,ARGC<_ALIGNOF_ (STRU16)>> {
	using TYPE = STRU16 ;
} ;

template <>
struct TEXT_BASE<ARGC<_SIZEOF_ (STRU32)> ,ARGC<_ALIGNOF_ (STRU32)>> {
	using TYPE = STRU32 ;
} ;

template <class _ARG1>
using TEXT_BASE_TYPE = typename U::TEXT_BASE<ARGC<_SIZEOF_ (_ARG1)> ,ARGC<_ALIGNOF_ (_ARG1)>>::TYPE ;
} ;

using STRUA = U::TEXT_BASE_TYPE<STRA> ;
using STRUW = U::TEXT_BASE_TYPE<STRW> ;

template <class REAL>
class ByteReader {
	_STATIC_ASSERT_ (stl::is_same<REAL ,BYTE>::value) ;

public:
	class Binder
		:public Interface {
	public:
		virtual void friend_read (ByteReader &reader) = 0 ;
	} ;

	static DEF<void (const ARGVF<ARGC<1>> &)> CLS ;
	static DEF<void (const ARGVF<ARGC<3>> &)> GAP ;
	static DEF<void (const ARGVF<ARGC<4>> &)> EOS ;

private:
	struct HEAP_PACK {
		BOOL mEndianFlag ;
	} ;

	struct Private {
		template <class>
		class Attribute ;
	} ;

private:
	SharedRef<HEAP_PACK> mHeap ;
	PhanBuffer<const REAL> mStream ;
	INDEX mRead ;
	INDEX mWrite ;

public:
	implicit ByteReader () {
		reset () ;
	}

	explicit ByteReader (PhanBuffer<const REAL> &&stream) {
		mHeap = SharedRef<HEAP_PACK>::make () ;
		mStream = _MOVE_ (stream) ;
		reset () ;
	}

	template <class _RET = REMOVE_CVR_TYPE<typename Private::template Attribute<ByteReader>>>
	_RET attr () leftvalue {
		struct Dependent ;
		using Attribute = typename DEPENDENT_TYPE<Private ,Dependent>::template Attribute<ByteReader> ;
		return Attribute (PhanRef<ByteReader>::make (DEREF[this])) ;
	}

	LENGTH size () const {
		return mStream.size () ;
	}

	LENGTH length () const {
		if (mStream.size () == 0)
			return 0 ;
		return mWrite - mRead ;
	}

	PhanBuffer<const REAL> raw () const leftvalue {
		_DYNAMIC_ASSERT_ (size () > 0) ;
		return PhanBuffer<const REAL>::make (mStream ,length ()) ;
	}

	void reset () {
		mRead = 0 ;
		mWrite = mStream.size () ;
	}

	void reset (const INDEX &read_ ,const INDEX &write_) {
		_DEBUG_ASSERT_ (mHeap.exist ()) ;
		_DEBUG_ASSERT_ (read_ >= 0 && read_ < mStream.size ()) ;
		_DEBUG_ASSERT_ (write_ >= 0 && write_ < mStream.size ()) ;
		_DEBUG_ASSERT_ (read_ <= write_) ;
		mRead = read_ ;
		mWrite = write_ ;
	}

	ByteReader share () leftvalue {
		ByteReader ret ;
		ret.mHeap = mHeap ;
		ret.mStream = PhanBuffer<const REAL>::make (mStream) ;
		ret.mRead = mRead ;
		ret.mWrite = mWrite ;
		return _MOVE_ (ret) ;
	}

	template <class _ARG1>
	_ARG1 read (const ARGVF<_ARG1> &) {
		_ARG1 ret ;
		read (ret) ;
		return _MOVE_ (ret) ;
	}

	void read (BYTE &data) {
		const auto r1x = attr () ;
		auto fax = TRUE ;
		if switch_once (fax) {
			if (!(mRead < mWrite))
				discard ;
			data = BYTE (mStream[mRead]) ;
			mRead++ ;
		}
		if switch_once (fax) {
			data = r1x.varify_ending_item () ;
		}
	}

	inline ByteReader &operator>> (BYTE &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (WORD &data) {
		const auto r1x = WORD (0X0001) ;
		auto &r2x = _CAST_ (ARGV<BYTE[_SIZEOF_ (WORD)]>::null ,r1x) ;
		auto &r3x = _CAST_ (ARGV<BYTE[_SIZEOF_ (WORD)]>::null ,data) ;
		for (auto &&i : _RANGE_ (0 ,_COUNTOF_ (DEF<decltype (r3x)>)))
			read (r3x[r2x[i]]) ;
	}

	inline ByteReader &operator>> (WORD &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (CHAR &data) {
		const auto r1x = CHAR (0X00010203) ;
		auto &r2x = _CAST_ (ARGV<BYTE[_SIZEOF_ (CHAR)]>::null ,r1x) ;
		auto &r3x = _CAST_ (ARGV<BYTE[_SIZEOF_ (CHAR)]>::null ,data) ;
		for (auto &&i : _RANGE_ (0 ,_COUNTOF_ (DEF<decltype (r3x)>)))
			read (r3x[r2x[i]]) ;
	}

	inline ByteReader &operator>> (CHAR &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (DATA &data) {
		const auto r1x = DATA (0X0001020304050607) ;
		auto &r2x = _CAST_ (ARGV<BYTE[_SIZEOF_ (DATA)]>::null ,r1x) ;
		auto &r3x = _CAST_ (ARGV<BYTE[_SIZEOF_ (DATA)]>::null ,data) ;
		for (auto &&i : _RANGE_ (0 ,_COUNTOF_ (DEF<decltype (r3x)>)))
			read (r3x[r2x[i]]) ;
	}

	inline ByteReader &operator>> (DATA &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (BOOL &data) {
		read (_CAST_ (ARGV<U::BYTE_BASE_TYPE<BOOL>>::null ,data)) ;
	}

	inline ByteReader &operator>> (BOOL &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (VAR32 &data) {
		read (_CAST_ (ARGV<U::BYTE_BASE_TYPE<VAR32>>::null ,data)) ;
	}

	inline ByteReader &operator>> (VAR32 &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (VAR64 &data) {
		read (_CAST_ (ARGV<U::BYTE_BASE_TYPE<VAR64>>::null ,data)) ;
	}

	inline ByteReader &operator>> (VAR64 &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (VAL32 &data) {
		read (_CAST_ (ARGV<U::BYTE_BASE_TYPE<VAL32>>::null ,data)) ;
	}

	inline ByteReader &operator>> (VAL32 &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (VAL64 &data) {
		read (_CAST_ (ARGV<U::BYTE_BASE_TYPE<VAL64>>::null ,data)) ;
	}

	inline ByteReader &operator>> (VAL64 &data) {
		read (data) ;
		return DEREF[this] ;
	}

	template <class _ARG1 ,class _ARG2>
	void read (Array<_ARG1 ,_ARG2> &data) {
		const auto r1x = LENGTH (read (ARGV<VAR32>::null)) ;
		_DYNAMIC_ASSERT_ (r1x >= 0 && r1x < VAR32_MAX) ;
		if (data.size () < r1x)
			data = Array<_ARG1 ,_ARG2> (r1x) ;
		for (auto &&i : _RANGE_ (0 ,r1x))
			read (data[i]) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline ByteReader &operator>> (Array<_ARG1 ,_ARG2> &data) {
		read (data) ;
		return DEREF[this] ;
	}

	template <class _ARG1>
	void read (const Plain<_ARG1> &data) {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
		auto rax = REAL () ;
		for (auto &&i : _RANGE_ (0 ,data.size ())) {
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == data.self[i]) ;
		}
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
	}

	template <class _ARG1>
	inline ByteReader &operator>> (const Plain<_ARG1> &data) {
		read (data) ;
		return DEREF[this] ;
	}

	template <class _ARG1 ,class _ARG2>
	void read (String<_ARG1 ,_ARG2> &data) {
		_STATIC_ASSERT_ (stl::is_str_xyz<_ARG1>::value) ;
		const auto r1x = LENGTH (read (ARGV<VAR32>::null)) ;
		_DYNAMIC_ASSERT_ (r1x >= 0 && r1x < VAR32_MAX) ;
		if (data.size () < r1x)
			data = String<_ARG1 ,_ARG2> (r1x) ;
		data.clear () ;
		for (auto &&i : _RANGE_ (0 ,r1x))
			read (data[i]) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline ByteReader &operator>> (String<_ARG1 ,_ARG2> &data) {
		read (data) ;
		return DEREF[this] ;
	}

	template <class _ARG1 ,class _ARG2>
	void read (Buffer<_ARG1 ,_ARG2> &data) {
		for (auto &&i : _RANGE_ (0 ,data.size ()))
			read (data[i]) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline ByteReader &operator>> (Buffer<_ARG1 ,_ARG2> &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (Binder &data) {
		data.friend_read (DEREF[this]) ;
	}

	inline ByteReader &operator>> (Binder &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (const DEF<void (ByteReader &)> &proc) {
		const auto r1x = Function<void (ByteReader &)> (proc) ;
		r1x (DEREF[this]) ;
	}

	inline ByteReader &operator>> (const DEF<void (ByteReader &)> &proc) {
		read (proc) ;
		return DEREF[this] ;
	}

	void scans () {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1 ,class... _ARGS>
	void scans (_ARG1 &list_one ,_ARGS &...list_rest) {
		read (list_one) ;
		scans (list_rest...) ;
	}

	void read (const DEF<decltype (CLS)> &) {
		reset () ;
	}

	inline ByteReader &operator>> (const DEF<decltype (CLS)> &proc) {
		read (proc) ;
		return DEREF[this] ;
	}

	void read (const DEF<decltype (GAP)> &) {
		const auto r1x = attr () ;
		auto rax = share () ;
		auto rbx = REAL () ;
		rax >> rbx ;
		_DYNAMIC_ASSERT_ (rbx == r1x.varify_space_item ()) ;
		rax >> rbx ;
		_DYNAMIC_ASSERT_ (rbx == r1x.varify_space_item ()) ;
		DEREF[this] = rax.share () ;
	}

	inline ByteReader &operator>> (const DEF<decltype (GAP)> &proc) {
		read (proc) ;
		return DEREF[this] ;
	}

	void read (const DEF<decltype (EOS)> &) {
		const auto r1x = attr () ;
		auto rax = share () ;
		auto rbx = REAL () ;
		while (TRUE) {
			if (rax.length () == 0)
				break ;
			rax >> rbx ;
			_DYNAMIC_ASSERT_ (rbx == r1x.varify_ending_item ()) ;
		}
		DEREF[this] = rax.share () ;
	}

	inline ByteReader &operator>> (const DEF<decltype (EOS)> &proc) {
		read (proc) ;
		return DEREF[this] ;
	}
} ;

template <class REAL>
template <class BASE>
class ByteReader<REAL>::Private::Attribute
	:private Proxy {
private:
	PhanRef<BASE> mBase ;

public:
	implicit Attribute () = delete ;

	explicit Attribute (PhanRef<BASE> &&base) {
		mBase = _MOVE_ (base) ;
	}

	REAL varify_ending_item () const {
		return REAL (0X00) ;
	}

	REAL varify_space_item () const {
		return REAL (0X00) ;
	}
} ;

template <class REAL>
inline void ByteReader<REAL>::CLS (const ARGVF<ARGC<1>> &) {}

template <class REAL>
inline void ByteReader<REAL>::GAP (const ARGVF<ARGC<3>> &) {}

template <class REAL>
inline void ByteReader<REAL>::EOS (const ARGVF<ARGC<4>> &) {}

template <class REAL>
class ByteWriter {
	_STATIC_ASSERT_ (stl::is_same<REAL ,BYTE>::value) ;

public:
	class Binder
		:public Interface {
	public:
		virtual void friend_write (ByteWriter &writer) const = 0 ;
	} ;

	static DEF<void (const ARGVF<ARGC<1>> &)> CLS ;
	static DEF<void (const ARGVF<ARGC<3>> &)> GAP ;
	static DEF<void (const ARGVF<ARGC<4>> &)> EOS ;

private:
	struct HEAP_PACK {
		SharedRef<FixedBuffer<REAL>> mBuffer ;
	} ;

	struct Private {
		template <class>
		class Attribute ;
	} ;

private:
	SharedRef<HEAP_PACK> mHeap ;
	PhanBuffer<REAL> mStream ;
	INDEX mRead ;
	INDEX mWrite ;

public:
	implicit ByteWriter () {
		reset () ;
	}

	explicit ByteWriter (PhanBuffer<REAL> &&stream) {
		mHeap = SharedRef<HEAP_PACK>::make () ;
		mStream = _MOVE_ (stream) ;
		reset () ;
	}

	explicit ByteWriter (const SharedRef<FixedBuffer<REAL>> &stream) {
		mHeap = SharedRef<HEAP_PACK>::make () ;
		mHeap->mBuffer = stream ;
		mStream = PhanBuffer<REAL>::make (mHeap->mBuffer.self) ;
		reset () ;
	}

	template <class _RET = REMOVE_CVR_TYPE<typename Private::template Attribute<ByteWriter>>>
	_RET attr () leftvalue {
		struct Dependent ;
		using Attribute = typename DEPENDENT_TYPE<Private ,Dependent>::template Attribute<ByteWriter> ;
		return Attribute (PhanRef<ByteWriter>::make (DEREF[this])) ;
	}

	LENGTH size () const {
		return mStream.size () ;
	}

	LENGTH length () const {
		if (mStream.size () == 0)
			return 0 ;
		return mWrite - mRead ;
	}

	PhanBuffer<const REAL> raw () const leftvalue {
		_DYNAMIC_ASSERT_ (size () > 0) ;
		return PhanBuffer<const REAL>::make (mStream ,length ()) ;
	}

	void reset () {
		mRead = 0 ;
		mWrite = 0 ;
	}

	void reset (const INDEX &read_ ,const INDEX &write_) {
		_DEBUG_ASSERT_ (mHeap.exist ()) ;
		_DEBUG_ASSERT_ (read_ >= 0 && read_ < mStream.size ()) ;
		_DEBUG_ASSERT_ (write_ >= 0 && write_ < mStream.size ()) ;
		_DEBUG_ASSERT_ (read_ <= write_) ;
		mRead = read_ ;
		mWrite = write_ ;
	}

	ByteWriter share () leftvalue {
		ByteWriter ret ;
		ret.mHeap = mHeap ;
		ret.mStream = PhanBuffer<REAL>::make (mStream) ;
		ret.mRead = mRead ;
		ret.mWrite = mWrite ;
		return _MOVE_ (ret) ;
	}

	void write (const BYTE &data) {
		_DYNAMIC_ASSERT_ (mWrite < mStream.size ()) ;
		mStream[mWrite] = REAL (data) ;
		mWrite++ ;
	}

	inline ByteWriter &operator<< (const BYTE &data) {
		write (data) ;
		return DEREF[this] ;
	}

	void write (const WORD &data) {
		const auto r1x = WORD (0X0001) ;
		auto &r2x = _CAST_ (ARGV<BYTE[_SIZEOF_ (WORD)]>::null ,r1x) ;
		auto &r3x = _CAST_ (ARGV<BYTE[_SIZEOF_ (WORD)]>::null ,data) ;
		for (auto &&i : _RANGE_ (0 ,_COUNTOF_ (DEF<decltype (r3x)>)))
			write (r3x[r2x[i]]) ;
	}

	inline ByteWriter &operator<< (const WORD &data) {
		write (data) ;
		return DEREF[this] ;
	}

	void write (const CHAR &data) {
		const auto r1x = CHAR (0X00010203) ;
		auto &r2x = _CAST_ (ARGV<BYTE[_SIZEOF_ (CHAR)]>::null ,r1x) ;
		auto &r3x = _CAST_ (ARGV<BYTE[_SIZEOF_ (CHAR)]>::null ,data) ;
		for (auto &&i : _RANGE_ (0 ,_COUNTOF_ (DEF<decltype (r3x)>)))
			write (r3x[r2x[i]]) ;
	}

	inline ByteWriter &operator<< (const CHAR &data) {
		write (data) ;
		return DEREF[this] ;
	}

	void write (const DATA &data) {
		const auto r1x = DATA (0X0001020304050607) ;
		auto &r2x = _CAST_ (ARGV<BYTE[_SIZEOF_ (DATA)]>::null ,r1x) ;
		auto &r3x = _CAST_ (ARGV<BYTE[_SIZEOF_ (DATA)]>::null ,data) ;
		for (auto &&i : _RANGE_ (0 ,_COUNTOF_ (DEF<decltype (r3x)>)))
			write (r3x[r2x[i]]) ;
	}

	inline ByteWriter &operator<< (const DATA &data) {
		write (data) ;
		return DEREF[this] ;
	}

	void write (const BOOL &data) {
		const auto r1x = _CAST_ (ARGV<U::BYTE_BASE_TYPE<BOOL>>::null ,data) ;
		write (r1x) ;
	}

	inline ByteWriter &operator<< (const BOOL &data) {
		write (data) ;
		return DEREF[this] ;
	}

	void write (const PTR<const VOID> &) = delete ;

	inline ByteWriter &operator<< (const PTR<const VOID> &) = delete ;

	void write (const VAR32 &data) {
		const auto r1x = _CAST_ (ARGV<U::BYTE_BASE_TYPE<VAR32>>::null ,data) ;
		write (r1x) ;
	}

	inline ByteWriter &operator<< (const VAR32 &data) {
		write (data) ;
		return DEREF[this] ;
	}

	void write (const VAR64 &data) {
		const auto r1x = _CAST_ (ARGV<U::BYTE_BASE_TYPE<VAR64>>::null ,data) ;
		write (r1x) ;
	}

	inline ByteWriter &operator<< (const VAR64 &data) {
		write (data) ;
		return DEREF[this] ;
	}

	void write (const VAL32 &data) {
		const auto r1x = _CAST_ (ARGV<U::BYTE_BASE_TYPE<VAL32>>::null ,data) ;
		write (r1x) ;
	}

	inline ByteWriter &operator<< (const VAL32 &data) {
		write (data) ;
		return DEREF[this] ;
	}

	void write (const VAL64 &data) {
		const auto r1x = _CAST_ (ARGV<U::BYTE_BASE_TYPE<VAL64>>::null ,data) ;
		write (r1x) ;
	}

	inline ByteWriter &operator<< (const VAL64 &data) {
		write (data) ;
		return DEREF[this] ;
	}

	template <class _ARG1 ,class _ARG2>
	void write (const Array<_ARG1 ,_ARG2> &data) {
		const auto r1x = data.length () ;
		_DYNAMIC_ASSERT_ (r1x >= 0 && r1x < VAR32_MAX) ;
		write (VAR32 (r1x)) ;
		for (auto &&i : data)
			write (i) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline ByteWriter &operator<< (const Array<_ARG1 ,_ARG2> &data) {
		write (data) ;
		return DEREF[this] ;
	}

	template <class _ARG1>
	void write (const Plain<_ARG1> &data) {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
		for (auto &&i : _RANGE_ (0 ,data.size ()))
			write (data.self[i]) ;
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
	}

	template <class _ARG1>
	inline ByteWriter &operator<< (const Plain<_ARG1> &data) {
		write (data) ;
		return DEREF[this] ;
	}

	template <class _ARG1 ,class _ARG2>
	void write (const String<_ARG1 ,_ARG2> &data) {
		_STATIC_ASSERT_ (stl::is_str_xyz<_ARG1>::value) ;
		const auto r1x = data.length () ;
		_DYNAMIC_ASSERT_ (r1x >= 0 && r1x < VAR32_MAX) ;
		write (VAR32 (r1x)) ;
		for (auto &&i : data)
			write (i) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline ByteWriter &operator<< (const String<_ARG1 ,_ARG2> &data) {
		write (data) ;
		return DEREF[this] ;
	}

	template <class _ARG1 ,class _ARG2>
	void write (const Buffer<_ARG1 ,_ARG2> &data) {
		for (auto &&i : _RANGE_ (0 ,data.size ()))
			write (data[i]) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline ByteWriter &operator<< (const Buffer<_ARG1 ,_ARG2> &data) {
		write (data) ;
		return DEREF[this] ;
	}

	void write (const Binder &data) {
		data.friend_write (DEREF[this]) ;
	}

	inline ByteWriter &operator<< (const Binder &data) {
		write (data) ;
		return DEREF[this] ;
	}

	void write (const DEF<void (ByteWriter &)> &proc) {
		const auto r1x = Function<void (ByteWriter &)> (proc) ;
		r1x (DEREF[this]) ;
	}

	inline ByteWriter &operator<< (const DEF<void (ByteWriter &)> &proc) {
		write (proc) ;
		return DEREF[this] ;
	}

	void prints () {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1 ,class... _ARGS>
	void prints (const _ARG1 &list_one ,const _ARGS &...list_rest) {
		write (list_one) ;
		prints (list_rest...) ;
	}

	void write (const DEF<decltype (CLS)> &) {
		reset () ;
	}

	inline ByteWriter &operator<< (const DEF<decltype (CLS)> &proc) {
		write (proc) ;
		return DEREF[this] ;
	}

	void write (const DEF<decltype (GAP)> &) {
		const auto r1x = attr () ;
		auto rax = share () ;
		rax << r1x.varify_space_item () ;
		rax << r1x.varify_space_item () ;
		DEREF[this] = rax.share () ;
	}

	inline ByteWriter &operator<< (const DEF<decltype (GAP)> &proc) {
		write (proc) ;
		return DEREF[this] ;
	}

	void write (const DEF<decltype (EOS)> &) {
		const auto r1x = attr () ;
		auto rax = share () ;
		for (auto &&i : _RANGE_ (0 ,rax.size () - rax.length ())) {
			_STATIC_UNUSED_ (i) ;
			rax << r1x.varify_ending_item () ;
		}
		DEREF[this] = rax.share () ;
	}

	inline ByteWriter &operator<< (const DEF<decltype (EOS)> &proc) {
		write (proc) ;
		return DEREF[this] ;
	}
} ;

template <class REAL>
template <class BASE>
class ByteWriter<REAL>::Private::Attribute
	:private Proxy {
private:
	PhanRef<BASE> mBase ;

public:
	implicit Attribute () = delete ;

	explicit Attribute (PhanRef<BASE> &&base) {
		mBase = _MOVE_ (base) ;
	}

	REAL varify_ending_item () const {
		return REAL (0X00) ;
	}

	REAL varify_space_item () const {
		return REAL (0X00) ;
	}
} ;

template <class REAL>
inline void ByteWriter<REAL>::CLS (const ARGVF<ARGC<1>> &) {}

template <class REAL>
inline void ByteWriter<REAL>::GAP (const ARGVF<ARGC<3>> &) {}

template <class REAL>
inline void ByteWriter<REAL>::EOS (const ARGVF<ARGC<4>> &) {}

template <class REAL>
class TextReader {
	_STATIC_ASSERT_ (stl::is_str_xyz<REAL>::value) ;

public:
	class Binder
		:public Interface {
	public:
		virtual void friend_read (TextReader &reader) = 0 ;
	} ;

	static DEF<void (const ARGVF<ARGC<1>> &)> CLS ;
	static DEF<void (const ARGVF<ARGC<2>> &)> BOM ;
	static DEF<void (const ARGVF<ARGC<3>> &)> GAP ;
	static DEF<void (const ARGVF<ARGC<4>> &)> EOS ;

private:
	struct HEAP_PACK {
		BOOL mEndianFlag ;
		BOOL mEscapeFlag ;
		Deque<REAL> mEscape ;
		HashSet<REAL> mEscapeMappingSet ;
		Deque<PACK<REAL ,FLAG>> mSpace ;
		HashSet<REAL> mSpaceMappingSet ;
	} ;

	struct Private {
		template <class>
		class Attribute ;
	} ;

private:
	SharedRef<HEAP_PACK> mHeap ;
	PhanBuffer<const REAL> mStream ;
	INDEX mRead ;
	INDEX mWrite ;

public:
	implicit TextReader () {
		reset () ;
	}

	explicit TextReader (PhanBuffer<const REAL> &&stream) {
		const auto r1x = attr () ;
		mHeap = SharedRef<HEAP_PACK>::make () ;
		r1x.enable_endian (FALSE) ;
		r1x.enable_escape (FALSE) ;
		mStream = _MOVE_ (stream) ;
		reset () ;
	}

	template <class _RET = REMOVE_CVR_TYPE<typename Private::template Attribute<TextReader>>>
	_RET attr () leftvalue {
		struct Dependent ;
		using Attribute = typename DEPENDENT_TYPE<Private ,Dependent>::template Attribute<TextReader> ;
		return Attribute (PhanRef<TextReader>::make (DEREF[this])) ;
	}

	LENGTH size () const {
		return mStream.size () ;
	}

	LENGTH length () const {
		if (mStream.size () == 0)
			return 0 ;
		return mWrite - mRead ;
	}

	PhanBuffer<const REAL> raw () const leftvalue {
		_DYNAMIC_ASSERT_ (size () > 0) ;
		return PhanBuffer<const REAL>::make (mStream ,length ()) ;
	}

	void reset () {
		mRead = 0 ;
		mWrite = mStream.size () ;
	}

	void reset (const INDEX &read_ ,const INDEX &write_) {
		_DEBUG_ASSERT_ (mHeap.exist ()) ;
		_DEBUG_ASSERT_ (read_ >= 0 && read_ < mStream.size ()) ;
		_DEBUG_ASSERT_ (write_ >= 0 && write_ < mStream.size ()) ;
		_DEBUG_ASSERT_ (read_ <= write_) ;
		mRead = read_ ;
		mWrite = write_ ;
	}

	TextReader share () leftvalue {
		TextReader ret ;
		ret.mHeap = mHeap ;
		ret.mStream = PhanBuffer<const REAL>::make (mStream) ;
		ret.mRead = mRead ;
		ret.mWrite = mWrite ;
		return _MOVE_ (ret) ;
	}

	template <class _ARG1>
	_ARG1 read (const ARGVF<_ARG1> &) {
		_ARG1 ret ;
		read (ret) ;
		return _MOVE_ (ret) ;
	}

	void read (REAL &data) {
		const auto r1x = attr () ;
		auto fax = TRUE ;
		if switch_once (fax) {
			if (!(mRead < mWrite))
				discard ;
			if switch_once (TRUE) {
				data = r1x.convert_endian (mStream[mRead]) ;
				const auto r2x = r1x.varify_escape_r (data) ;
				mRead++ ;
				if (!r2x)
					discard ;
				_DYNAMIC_ASSERT_ (mRead < mWrite) ;
				data = r1x.convert_endian (mStream[mRead]) ;
				data = r1x.convert_escape_r (data) ;
				mRead++ ;
			}
		}
		if switch_once (fax) {
			data = r1x.varify_ending_item () ;
		}
	}

	inline TextReader &operator>> (REAL &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (BOOL &data) {
		auto rax = REAL () ;
		read (rax) ;
		auto fax = TRUE ;
		if switch_once (fax) {
			if (!(rax == REAL ('t')))
				discard ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('r')) ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('u')) ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('e')) ;
			data = TRUE ;
		}
		if switch_once (fax) {
			if (!(rax == REAL ('T')))
				discard ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('R')) ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('U')) ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('E')) ;
			data = TRUE ;
		}
		if switch_once (fax) {
			if (!(rax == REAL ('f')))
				discard ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('a')) ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('l')) ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('s')) ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('e')) ;
			data = FALSE ;
		}
		if switch_once (fax) {
			if (!(rax == REAL ('F')))
				discard ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('A')) ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('L')) ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('S')) ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('E')) ;
			data = FALSE ;
		}
		if switch_once (fax) {
			_DYNAMIC_ASSERT_ (FALSE) ;
		}
	}

	inline TextReader &operator>> (BOOL &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (VAR32 &data) {
		const auto r1x = read (ARGV<VAR64>::null) ;
		_DYNAMIC_ASSERT_ (r1x >= VAR32_MIN && r1x <= VAR32_MAX) ;
		data = VAR32 (r1x) ;
	}

	inline TextReader &operator>> (VAR32 &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (VAR64 &data) {
		auto rax = REAL () ;
		read (rax) ;
		const auto r1x = BOOL (rax == REAL ('-')) ;
		const auto r2x = BOOL (rax == REAL ('+')) ;
		if (_ANYOF_ (r1x ,r2x))
			read (rax) ;
		compute_read_number (data ,rax) ;
		if (!r1x)
			return ;
		data = -data ;
	}

	inline TextReader &operator>> (VAR64 &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (VAL32 &data) {
		const auto r1x = read (ARGV<VAL64>::null) ;
		if switch_once (TRUE) {
			if (MathProc::is_infinite (r1x))
				discard ;
			if (MathProc::is_nan (r1x))
				discard ;
			_DYNAMIC_ASSERT_ (r1x >= VAL32_MIN && r1x <= VAL32_MAX) ;
		}
		data = VAL32 (r1x) ;
	}

	inline TextReader &operator>> (VAL32 &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (VAL64 &data) {
		const auto r1x = attr () ;
		auto rax = REAL () ;
		read (rax) ;
		const auto r2x = BOOL (rax == REAL ('-')) ;
		if switch_once (TRUE) {
			if (!r2x)
				if (rax != REAL ('+'))
					discard ;
			read (rax) ;
		}
		auto fax = TRUE ;
		if switch_once (fax) {
			if (!(rax == REAL ('i')))
				discard ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('n')) ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('f')) ;
			data = VAL64_INF ;
		}
		if switch_once (fax) {
			if (!(rax == REAL ('I')))
				discard ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('N')) ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('F')) ;
			data = VAL64_INF ;
		}
		if switch_once (fax) {
			if (!(rax == REAL ('n')))
				discard ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('a')) ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('n')) ;
			data = VAL64_NAN ;
		}
		if switch_once (fax) {
			if (!(rax == REAL ('N')))
				discard ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('A')) ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('N')) ;
			data = VAL64_NAN ;
		}
		if switch_once (fax) {
			const auto r3x = r1x.varify_number_item (rax) ;
			_DYNAMIC_ASSERT_ (r3x) ;
			compute_read_number (data ,rax) ;
		}
		if (!r2x)
			return ;
		data = -data ;
	}

	inline TextReader &operator>> (VAL64 &data) {
		read (data) ;
		return DEREF[this] ;
	}

	template <class _ARG1 ,class _ARG2>
	void read (Array<_ARG1 ,_ARG2> &data) {
		_DEBUG_ASSERT_ (FALSE) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline TextReader &operator>> (Array<_ARG1 ,_ARG2> &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (const Plain<REAL> &data) {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
		auto rax = REAL () ;
		for (auto &&i : _RANGE_ (0 ,data.size ())) {
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == data.self[i]) ;
		}
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
	}

	inline TextReader &operator>> (const Plain<REAL> &data) {
		read (data) ;
		return DEREF[this] ;
	}

	template <class _ARG1>
	void read (String<REAL ,_ARG1> &data) {
		const auto r1x = next_string_size () ;
		_DYNAMIC_ASSERT_ (r1x >= 0 && r1x < VAR32_MAX) ;
		if (data.size () < r1x)
			data = String<REAL ,_ARG1> (r1x) ;
		data.clear () ;
		for (auto &&i : _RANGE_ (0 ,r1x))
			read (data[i]) ;
	}

	template <class _ARG1>
	inline TextReader &operator>> (String<REAL ,_ARG1> &data) {
		read (data) ;
		return DEREF[this] ;
	}

	template <class _ARG1 ,class _ARG2>
	void read (Buffer<_ARG1 ,_ARG2> &data) {
		for (auto &&i : _RANGE_ (0 ,data.size ()))
			read (data[i]) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline TextReader &operator>> (Buffer<_ARG1 ,_ARG2> &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (Binder &data) {
		data.friend_read (DEREF[this]) ;
	}

	inline TextReader &operator>> (Binder &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (const DEF<void (TextReader &)> &proc) {
		const auto r1x = Function<void (TextReader &)> (proc) ;
		r1x (DEREF[this]) ;
	}

	inline TextReader &operator>> (const DEF<void (TextReader &)> &proc) {
		read (proc) ;
		return DEREF[this] ;
	}

	void scans () {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1 ,class... _ARGS>
	void scans (_ARG1 &list_one ,_ARGS &...list_rest) {
		read (list_one) ;
		scans (list_rest...) ;
	}

	void read (const DEF<decltype (CLS)> &) {
		reset () ;
	}

	inline TextReader &operator>> (const DEF<decltype (CLS)> &proc) {
		read (proc) ;
		return DEREF[this] ;
	}

	void read (const DEF<decltype (BOM)> &) {
		template_read_bom (ARGV<REAL>::null) ;
	}

	inline TextReader &operator>> (const DEF<decltype (BOM)> &proc) {
		read (proc) ;
		return DEREF[this] ;
	}

	void read (const DEF<decltype (GAP)> &) {
		const auto r1x = attr () ;
		auto rax = share () ;
		auto rbx = REAL () ;
		rax >> rbx ;
		while (TRUE) {
			if (!r1x.varify_space (rbx))
				break ;
			DEREF[this] = rax.share () ;
			rax >> rbx ;
		}
	}

	inline TextReader &operator>> (const DEF<decltype (GAP)> &proc) {
		read (proc) ;
		return DEREF[this] ;
	}

	void read (const DEF<decltype (EOS)> &) {
		const auto r1x = attr () ;
		auto rax = share () ;
		auto rbx = REAL () ;
		rax.read (rbx) ;
		_DYNAMIC_ASSERT_ (rbx == r1x.varify_ending_item ()) ;
		DEREF[this] = rax.share () ;
	}

	inline TextReader &operator>> (const DEF<decltype (EOS)> &proc) {
		read (proc) ;
		return DEREF[this] ;
	}

private:
	LENGTH next_string_size () {
		const auto r1x = attr () ;
		LENGTH ret = 0 ;
		auto rax = share () ;
		auto rbx = REAL () ;
		rax.read (rbx) ;
		while (TRUE) {
			if (rbx == r1x.varify_ending_item ())
				break ;
			if (r1x.varify_space (rbx))
				break ;
			ret++ ;
			rax.read (rbx) ;
		}
		return _MOVE_ (ret) ;
	}

	void compute_read_number (VAR64 &data ,REAL &top) {
		const auto r1x = attr () ;
		_DEBUG_ASSERT_ (r1x.varify_number_item (top)) ;
		auto rax = share () ;
		data = r1x.convert_number_r (top) ;
		rax.read (top) ;
		while (TRUE) {
			if (!r1x.varify_number_item (top))
				break ;
			const auto r2x = data * r1x.varify_radix () + r1x.convert_number_r (top) ;
			_DYNAMIC_ASSERT_ (data <= r2x) ;
			data = r2x ;
			DEREF[this] = rax.share () ;
			rax.read (top) ;
		}
	}

	void compute_read_number (VAL64 &data ,REAL &top) {
		const auto r1x = attr () ;
		_DEBUG_ASSERT_ (r1x.varify_number_item (top)) ;
		auto rax = share () ;
		while (TRUE) {
			if (r1x.convert_number_r (top) != 0)
				break ;
			DEREF[this] = rax.share () ;
			rax.read (top) ;
		}
		auto rbx = ARRAY3<VAR64> {0 ,0 ,0} ;
		if switch_once (TRUE) {
			if (!r1x.varify_number_item (top))
				discard ;
			rbx[0] = r1x.convert_number_r (top) ;
			DEREF[this] = rax.share () ;
			rax.read (top) ;
			while (TRUE) {
				if (!r1x.varify_number_item (top))
					break ;
				auto fax = TRUE ;
				if switch_once (fax) {
					const auto r2x = rbx[0] * r1x.varify_radix () + r1x.convert_number_r (top) ;
					if (!(rbx[0] < r2x))
						discard ;
					rbx[0] = r2x ;
				}
				if switch_once (fax) {
					rbx[1]++ ;
				}
				DEREF[this] = rax.share () ;
				rax.read (top) ;
			}
		}
		if switch_once (TRUE) {
			if (top != REAL ('.'))
				discard ;
			DEREF[this] = rax.share () ;
			rax.read (top) ;
			_DYNAMIC_ASSERT_ (r1x.varify_number_item (top)) ;
			while (TRUE) {
				if (!r1x.varify_number_item (top))
					break ;
				if switch_once (TRUE) {
					const auto r3x = rbx[0] * r1x.varify_radix () + r1x.convert_number_r (top) ;
					if (rbx[0] > r3x)
						discard ;
					rbx[0] = r3x ;
					rbx[1]-- ;
				}
				DEREF[this] = rax.share () ;
				rax.read (top) ;
			}
		}
		if switch_once (TRUE) {
			if (!(top == REAL ('e') || top == REAL ('E')))
				discard ;
			const auto r4x = rax.read (ARGV<VAR32>::null) ;
			rbx[1] += r4x ;
			DEREF[this] = rax.share () ;
		}
		if switch_once (TRUE) {
			if (rbx[0] >= 0)
				discard ;
			rbx[0] = -rbx[0] ;
			rbx[2] = -1 ;
			if (rbx[0] >= 0)
				discard ;
			rbx[0] = -(rbx[0] / r1x.varify_radix ()) ;
			rbx[1]++ ;
		}
		const auto r5x = MathProc::ieee754_e10_e2 (rbx) ;
		data = MathProc::ieee754_encode (r5x) ;
	}

	template <class _ARG1>
	void template_read_bom (const ARGVF<_ARG1> &) {
		_STATIC_WARNING_ ("noop") ;
	}

	void template_read_bom (const ARGVF<STRU8> &) {
		static constexpr auto M_BOM = PACK<STRU8[3]> ({
			STRU8 (0XEF) ,STRU8 (0XBB) ,STRU8 (0XBF)}) ;
		const auto r1x = attr () ;
		auto rax = share () ;
		auto rbx = STRU8 () ;
		rax >> rbx ;
		if (rbx != M_BOM.mP1[0])
			return ;
		rax >> rbx ;
		if (rbx != M_BOM.mP1[1])
			return ;
		rax >> rbx ;
		if (rbx != M_BOM.mP1[2])
			return ;
		r1x.enable_endian (FALSE) ;
		DEREF[this] = rax.share () ;
	}

	void template_read_bom (const ARGVF<STRU16> &) {
		static constexpr auto M_BOM = PACK<STRU16[2]> ({
			STRU16 (0XFEFF) ,STRU16 (0XFFFE)}) ;
		const auto r1x = attr () ;
		auto rax = share () ;
		auto rbx = STRU16 () ;
		rax >> rbx ;
		if (!(rbx == M_BOM.mP1[0] || rbx == M_BOM.mP1[1]))
			return ;
		const auto r2x = BOOL (rbx != M_BOM.mP1[0]) ;
		r1x.enable_endian (r2x) ;
		DEREF[this] = rax.share () ;
	}

	void template_read_bom (const ARGVF<STRU32> &) {
		static constexpr auto M_BOM = PACK<STRU32[2]> ({
			STRU32 (0X0000FEFF) ,STRU32 (0XFFFE0000)}) ;
		const auto r1x = attr () ;
		auto rax = share () ;
		auto rbx = STRU32 () ;
		rax >> rbx ;
		if (!(rbx == M_BOM.mP1[0] || rbx == M_BOM.mP1[1]))
			return ;
		const auto r2x = BOOL (rbx != M_BOM.mP1[0]) ;
		r1x.enable_endian (r2x) ;
		DEREF[this] = rax.share () ;
	}

	void template_read_bom (const ARGVF<STRW> &) {
		auto rax = share () ;
		_CAST_ (ARGV<TextReader<STRUW>>::null ,rax).template_read_bom (ARGV<STRUW>::null) ;
		DEREF[this] = rax.share () ;
	}
} ;

template <class REAL>
template <class BASE>
class TextReader<REAL>::Private::Attribute
	:private Proxy {
private:
	PhanRef<BASE> mBase ;

public:
	implicit Attribute () = delete ;

	explicit Attribute (PhanRef<BASE> &&base) {
		mBase = _MOVE_ (base) ;
	}

	REAL varify_ending_item () const {
		return REAL ('\0') ;
	}

	void enable_endian (const BOOL &flag) const {
		_STATIC_ASSERT_ (!stl::is_const<BASE>::value) ;
		mBase->mHeap->mEndianFlag = flag ;
	}

	REAL convert_endian (const REAL &item) const {
		if (!mBase->mHeap->mEndianFlag)
			return item ;
		U::BYTE_BASE_TYPE<REAL> ret ;
		auto &r1x = _CAST_ (ARGV<BYTE[_SIZEOF_ (REAL)]>::null ,item) ;
		ByteReader<BYTE> (PhanBuffer<const BYTE>::make (r1x)) >> ret ;
		return _MOVE_ (_CAST_ (ARGV<REAL>::null ,ret)) ;
	}

	VAR64 varify_radix () const {
		return 10 ;
	}

	LENGTH varify_val32_precision () const {
		return 6 ;
	}

	LENGTH varify_val64_precision () const {
		_STATIC_WARNING_ ("mark") ;
		return 13 ;
	}

	BOOL varify_number_item (const REAL &item) const {
		if (!(item >= REAL ('0') && item <= REAL ('9')))
			return FALSE ;
		return TRUE ;
	}

	VAR64 convert_number_r (const REAL &item) const {
		return VAR64 (item) - VAR64 ('0') ;
	}

	void enable_escape (const BOOL &flag) const {
		_STATIC_ASSERT_ (!stl::is_const<BASE>::value) ;
		mBase->mHeap->mEscapeFlag = flag ;
	}

	REAL varify_escape_item () const {
		return REAL ('\\') ;
	}

	BOOL varify_escape_r (const REAL &item) const {
		if (!mBase->mHeap->mEscapeFlag)
			return FALSE ;
		if (item != varify_escape_item ())
			return FALSE ;
		return TRUE ;
	}

	void modify_escape_r (const REAL &str_a ,const REAL &str_e) const {
		_STATIC_ASSERT_ (!stl::is_const<BASE>::value) ;
		_DEBUG_ASSERT_ (str_e != varify_ending_item ()) ;
		INDEX ix = mBase->mHeap->mEscapeMappingSet.map (str_a) ;
		_DEBUG_ASSERT_ (ix == VAR_NONE) ;
		ix = mBase->mHeap->mEscape.insert () ;
		mBase->mHeap->mEscapeMappingSet.add (str_a ,ix) ;
		mBase->mHeap->mEscape[ix] = str_e ;
	}

	REAL convert_escape_r (const REAL &str_a) const {
		INDEX ix = mBase->mHeap->mEscapeMappingSet.map (str_a) ;
		_DYNAMIC_ASSERT_ (ix != VAR_NONE) ;
		return mBase->mHeap->mEscape[ix] ;
	}

	BOOL varify_space (const REAL &item) const {
		INDEX ix = mBase->mHeap->mSpaceMappingSet.map (item) ;
		if (ix == VAR_NONE)
			return FALSE ;
		return TRUE ;
	}

	BOOL varify_space (const REAL &item ,const VAR32 &group) const {
		INDEX ix = mBase->mHeap->mSpaceMappingSet.map (item) ;
		if (ix == VAR_NONE)
			return FALSE ;
		if (mBase->mHeap->mSpace[ix].mP2 != group)
			return FALSE ;
		return TRUE ;
	}

	void modify_space (const REAL &item ,const VAR32 &group) const {
		_STATIC_ASSERT_ (!stl::is_const<BASE>::value) ;
		_DEBUG_ASSERT_ (item != varify_ending_item ()) ;
		INDEX ix = mBase->mHeap->mSpaceMappingSet.map (item) ;
		_DEBUG_ASSERT_ (ix == VAR_NONE) ;
		ix = mBase->mHeap->mSpace.insert () ;
		mBase->mHeap->mSpaceMappingSet.add (item ,ix) ;
		mBase->mHeap->mSpace[ix].mP1 = item ;
		mBase->mHeap->mSpace[ix].mP2 = group ;
	}

	BOOL varify_control (const REAL &item) const {
		if (!(item >= REAL (0) && item <= REAL (32)))
			if (item != REAL (127))
				return FALSE ;
		if (varify_space (item))
			return FALSE ;
		return TRUE ;
	}
} ;

template <class REAL>
inline void TextReader<REAL>::CLS (const ARGVF<ARGC<1>> &) {}

template <class REAL>
inline void TextReader<REAL>::BOM (const ARGVF<ARGC<2>> &) {}

template <class REAL>
inline void TextReader<REAL>::GAP (const ARGVF<ARGC<3>> &) {}

template <class REAL>
inline void TextReader<REAL>::EOS (const ARGVF<ARGC<4>> &) {}

template <class REAL>
class TextWriter {
	_STATIC_ASSERT_ (stl::is_str_xyz<REAL>::value) ;

public:
	class Binder
		:public Interface {
	public:
		virtual void friend_write (TextWriter &writer) const = 0 ;
	} ;

	static DEF<void (const ARGVF<ARGC<1>> &)> CLS ;
	static DEF<void (const ARGVF<ARGC<2>> &)> BOM ;
	static DEF<void (const ARGVF<ARGC<3>> &)> GAP ;
	static DEF<void (const ARGVF<ARGC<4>> &)> EOS ;

private:
	struct HEAP_PACK {
		SharedRef<FixedBuffer<REAL>> mBuffer ;
		BOOL mEscapeFlag ;
		Deque<REAL> mEscape ;
		HashSet<REAL> mEscapeMappingSet ;
	} ;

	struct Private {
		template <class>
		class Attribute ;
	} ;

private:
	SharedRef<HEAP_PACK> mHeap ;
	PhanBuffer<REAL> mStream ;
	INDEX mRead ;
	INDEX mWrite ;

public:
	implicit TextWriter () {
		reset () ;
	}

	explicit TextWriter (PhanBuffer<REAL> &&stream) {
		const auto r1x = attr () ;
		mHeap = SharedRef<HEAP_PACK>::make () ;
		r1x.enable_escape (FALSE) ;
		mStream = _MOVE_ (stream) ;
		reset () ;
	}

	explicit TextWriter (const SharedRef<FixedBuffer<REAL>> &stream) {
		const auto r1x = attr () ;
		mHeap = SharedRef<HEAP_PACK>::make () ;
		mHeap->mBuffer = stream ;
		r1x.enable_escape (FALSE) ;
		mStream = PhanBuffer<REAL>::make (mHeap->mBuffer.self) ;
		reset () ;
	}

	template <class _RET = REMOVE_CVR_TYPE<typename Private::template Attribute<TextWriter>>>
	_RET attr () leftvalue {
		struct Dependent ;
		using Attribute = typename DEPENDENT_TYPE<Private ,Dependent>::template Attribute<TextWriter> ;
		return Attribute (PhanRef<TextWriter>::make (DEREF[this])) ;
	}

	LENGTH size () const {
		return mStream.size () ;
	}

	LENGTH length () const {
		if (mStream.size () == 0)
			return 0 ;
		return mWrite - mRead ;
	}

	PhanBuffer<const REAL> raw () const leftvalue {
		_DYNAMIC_ASSERT_ (size () > 0) ;
		return PhanBuffer<const REAL>::make (mStream ,length ()) ;
	}

	void reset () {
		mRead = 0 ;
		mWrite = 0 ;
	}

	void reset (const INDEX &read_ ,const INDEX &write_) {
		_DEBUG_ASSERT_ (mHeap.exist ()) ;
		_DEBUG_ASSERT_ (read_ >= 0 && read_ < mStream.size ()) ;
		_DEBUG_ASSERT_ (write_ >= 0 && write_ < mStream.size ()) ;
		_DEBUG_ASSERT_ (read_ <= write_) ;
		mRead = read_ ;
		mWrite = write_ ;
	}

	TextWriter share () leftvalue {
		TextWriter ret ;
		ret.mHeap = mHeap ;
		ret.mStream = PhanBuffer<REAL>::make (mStream) ;
		ret.mRead = mRead ;
		ret.mWrite = mWrite ;
		return _MOVE_ (ret) ;
	}

	void write (const REAL &data) {
		const auto r1x = attr () ;
		auto fax = TRUE ;
		if switch_once (fax) {
			if (!r1x.varify_escape_w (data))
				discard ;
			_DYNAMIC_ASSERT_ (mWrite + 1 < mStream.size ()) ;
			mStream[mWrite] = r1x.varify_escape_item () ;
			mWrite++ ;
			const auto r2x = r1x.convert_escape_w (data) ;
			mStream[mWrite] = r2x ;
			mWrite++ ;
		}
		if switch_once (fax) {
			_DYNAMIC_ASSERT_ (mWrite < mStream.size ()) ;
			mStream[mWrite] = data ;
			mWrite++ ;
		}
	}

	inline TextWriter &operator<< (const REAL &data) {
		write (data) ;
		return DEREF[this] ;
	}

	void write (const BOOL &data) {
		static constexpr auto M_TRUE = PACK<REAL[4]> ({
			REAL ('t') ,REAL ('r') ,REAL ('u') ,REAL ('e')}) ;
		static constexpr auto M_FALSE = PACK<REAL[5]> ({
			REAL ('f') ,REAL ('a') ,REAL ('l') ,REAL ('s') ,REAL ('e')}) ;
		const auto r1x = _CALL_ ([&] () {
			if (data)
				return PhanBuffer<const REAL>::make (M_TRUE.mP1) ;
			return PhanBuffer<const REAL>::make (M_FALSE.mP1) ;
		}) ;
		write (r1x) ;
	}

	inline TextWriter &operator<< (const BOOL &data) {
		write (data) ;
		return DEREF[this] ;
	}

	void write (const PTR<const VOID> &) = delete ;

	inline TextWriter &operator<< (const PTR<const VOID> &) = delete ;

	void write (const VAR32 &data) {
		write (VAR64 (data)) ;
	}

	inline TextWriter &operator<< (const VAR32 &data) {
		write (data) ;
		return DEREF[this] ;
	}

	void write (const VAR64 &data) {
		auto rax = Buffer<REAL ,ARGC<128>> () ;
		INDEX iw = rax.size () ;
		compute_write_number (data ,PhanBuffer<REAL>::make (rax) ,iw) ;
		const auto r1x = PhanBuffer<const REAL>::make (PTRTOARR[DEPTR[rax.self[iw]]] ,(rax.size () - iw)) ;
		write (r1x) ;
	}

	inline TextWriter &operator<< (const VAR64 &data) {
		write (data) ;
		return DEREF[this] ;
	}

	void write (const VAL32 &data) {
		static constexpr auto M_NAN = PACK<REAL[3]> ({
			REAL ('n') ,REAL ('a') ,REAL ('n')}) ;
		static constexpr auto M_INF = PACK<REAL[4]> ({
			REAL ('+') ,REAL ('i') ,REAL ('n') ,REAL ('f')}) ;
		static constexpr auto M_SINF = PACK<REAL[4]> ({
			REAL ('-') ,REAL ('i') ,REAL ('n') ,REAL ('f')}) ;
		const auto r1x = attr () ;
		auto fax = TRUE ;
		if switch_once (fax) {
			if (!MathProc::is_nan (data))
				discard ;
			write (PhanBuffer<const REAL>::make (M_NAN.mP1)) ;
		}
		if switch_once (fax) {
			if (!MathProc::is_infinite (data))
				discard ;
			if (!(data > 0))
				discard ;
			write (PhanBuffer<const REAL>::make (M_INF.mP1)) ;
		}
		if switch_once (fax) {
			if (!MathProc::is_infinite (data))
				discard ;
			if (!(data < 0))
				discard ;
			write (PhanBuffer<const REAL>::make (M_SINF.mP1)) ;
		}
		if switch_once (fax) {
			auto rax = Buffer<REAL ,ARGC<256>> () ;
			INDEX iw = rax.size () ;
			const auto r2x = r1x.varify_val32_precision () ;
			compute_write_number (data ,r2x ,PhanBuffer<REAL>::make (rax) ,iw) ;
			const auto r3x = PhanBuffer<const REAL>::make (PTRTOARR[DEPTR[rax.self[iw]]] ,(rax.size () - iw)) ;
			write (r3x) ;
		}
	}

	inline TextWriter &operator<< (const VAL32 &data) {
		write (data) ;
		return DEREF[this] ;
	}

	void write (const VAL64 &data) {
		static constexpr auto M_NAN = PACK<REAL[3]> ({
			REAL ('n') ,REAL ('a') ,REAL ('n')}) ;
		static constexpr auto M_INF = PACK<REAL[4]> ({
			REAL ('+') ,REAL ('i') ,REAL ('n') ,REAL ('f')}) ;
		static constexpr auto M_SINF = PACK<REAL[4]> ({
			REAL ('-') ,REAL ('i') ,REAL ('n') ,REAL ('f')}) ;
		const auto r1x = attr () ;
		auto fax = TRUE ;
		if switch_once (fax) {
			if (!MathProc::is_nan (data))
				discard ;
			write (PhanBuffer<const REAL>::make (M_NAN.mP1)) ;
		}
		if switch_once (fax) {
			if (!MathProc::is_infinite (data))
				discard ;
			if (!(data > 0))
				discard ;
			write (PhanBuffer<const REAL>::make (M_INF.mP1)) ;
		}
		if switch_once (fax) {
			if (!MathProc::is_infinite (data))
				discard ;
			if (!(data < 0))
				discard ;
			write (PhanBuffer<const REAL>::make (M_SINF.mP1)) ;
		}
		if switch_once (fax) {
			auto rax = Buffer<REAL ,ARGC<256>> () ;
			INDEX iw = rax.size () ;
			const auto r2x = r1x.varify_val64_precision () ;
			compute_write_number (data ,r2x ,PhanBuffer<REAL>::make (rax) ,iw) ;
			const auto r3x = PhanBuffer<const REAL>::make (PTRTOARR[DEPTR[rax.self[iw]]] ,(rax.size () - iw)) ;
			write (r3x) ;
		}
	}

	inline TextWriter &operator<< (const VAL64 &data) {
		write (data) ;
		return DEREF[this] ;
	}

	template <class _ARG1 ,class _ARG2>
	void write (const Array<_ARG1 ,_ARG2> &data) {
		_DEBUG_ASSERT_ (FALSE) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline TextWriter &operator<< (const Array<_ARG1 ,_ARG2> &data) {
		write (data) ;
		return DEREF[this] ;
	}

	void write (const Plain<REAL> &data) {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
		for (auto &&i : _RANGE_ (0 ,data.size ()))
			write (data.self[i]) ;
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
	}

	inline TextWriter &operator<< (const Plain<REAL> &data) {
		write (data) ;
		return DEREF[this] ;
	}

	template <class _ARG1>
	void write (const String<REAL ,_ARG1> &data) {
		const auto r1x = data.length () ;
		_DYNAMIC_ASSERT_ (r1x >= 0 && r1x < VAR32_MAX) ;
		for (auto &&i : data)
			write (i) ;
	}

	template <class _ARG1>
	inline TextWriter &operator<< (const String<REAL ,_ARG1> &data) {
		write (data) ;
		return DEREF[this] ;
	}

	template <class _ARG1 ,class _ARG2>
	void write (const Buffer<_ARG1 ,_ARG2> &data) {
		for (auto &&i : _RANGE_ (0 ,data.size ()))
			write (data[i]) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline TextWriter &operator<< (const Buffer<_ARG1 ,_ARG2> &data) {
		write (data) ;
		return DEREF[this] ;
	}

	void write (const Binder &data) {
		data.friend_write (DEREF[this]) ;
	}

	inline TextWriter &operator<< (const Binder &data) {
		write (data) ;
		return DEREF[this] ;
	}

	void write (const DEF<void (TextWriter &)> &proc) {
		const auto r1x = Function<void (TextWriter &)> (proc) ;
		r1x (DEREF[this]) ;
	}

	inline TextWriter &operator<< (const DEF<void (TextWriter &)> &proc) {
		write (proc) ;
		return DEREF[this] ;
	}

	void prints () {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1 ,class... _ARGS>
	void prints (const _ARG1 &list_one ,const _ARGS &...list_rest) {
		write (list_one) ;
		prints (list_rest...) ;
	}

	void write (const DEF<decltype (CLS)> &) {
		reset () ;
	}

	inline TextWriter &operator<< (const DEF<decltype (CLS)> &proc) {
		write (proc) ;
		return DEREF[this] ;
	}

	void write (const DEF<decltype (BOM)> &) {
		template_write_bom (ARGV<REAL>::null) ;
	}

	inline TextWriter &operator<< (const DEF<decltype (BOM)> &proc) {
		write (proc) ;
		return DEREF[this] ;
	}

	void write (const DEF<decltype (GAP)> &) {
		auto rax = share () ;
		_DYNAMIC_ASSERT_ (rax.length () + 2 < rax.size ()) ;
		rax << REAL ('\r') << REAL ('\n') ;
		DEREF[this] = rax.share () ;
	}

	inline TextWriter &operator<< (const DEF<decltype (GAP)> &proc) {
		write (proc) ;
		return DEREF[this] ;
	}

	void write (const DEF<decltype (EOS)> &) {
		const auto r1x = attr () ;
		auto rax = share () ;
		rax << r1x.varify_ending_item () ;
		DEREF[this] = rax.share () ;
	}

	inline TextWriter &operator<< (const DEF<decltype (EOS)> &proc) {
		write (proc) ;
		return DEREF[this] ;
	}

private:
	void compute_write_number (const VAR64 &data ,const PhanBuffer<REAL> &out ,INDEX &out_iw) {
		const auto r1x = attr () ;
		auto rax = data ;
		INDEX iw = out_iw ;
		auto fax = TRUE ;
		if switch_once (fax) {
			if (!(data > 0))
				discard ;
			while (TRUE) {
				if (rax == 0)
					break ;
				out[--iw] = r1x.convert_number_w (rax % r1x.varify_radix ()) ;
				rax /= r1x.varify_radix () ;
			}
		}
		if switch_once (fax) {
			if (!(data < 0))
				discard ;
			while (TRUE) {
				if (rax == 0)
					break ;
				out[--iw] = r1x.convert_number_w (-rax % r1x.varify_radix ()) ;
				rax /= r1x.varify_radix () ;
			}
			out[--iw] = REAL ('-') ;
		}
		if switch_once (fax) {
			if (!(data == 0))
				discard ;
			out[--iw] = r1x.convert_number_w (0) ;
		}
		out_iw = iw ;
	}

	void compute_write_number (const VAL64 &data ,const LENGTH &precision ,const PhanBuffer<REAL> &out ,INDEX &out_iw) {
		const auto r1x = attr () ;
		INDEX iw = out_iw ;
		const auto r2x = MathProc::ieee754_decode (data) ;
		auto rax = MathProc::ieee754_e2_e10 (r2x) ;
		const auto r3x = log_of_number (rax[0] ,r1x.varify_radix ()) ;
		if switch_once (TRUE) {
			const auto r4x = r3x - precision ;
			for (auto &&i : _RANGE_ (0 ,r4x - 1)) {
				_STATIC_UNUSED_ (i) ;
				rax[0] /= r1x.varify_radix () ;
				rax[1]++ ;
			}
			if (r4x <= 0)
				discard ;
			rax[0] = MathProc::round (rax[0] ,r1x.varify_radix ()) / r1x.varify_radix () ;
			rax[1]++ ;
		}
		const auto r5x = log_of_number (rax[0] ,r1x.varify_radix ()) ;
		auto fax = TRUE ;
		if switch_once (fax) {
			//@info: case '0'
			if (!(rax[0] == 0))
				discard ;
			out[--iw] = r1x.convert_number_w (0) ;
		}
		if switch_once (fax) {
			//@info: case 'x.xxxExxx'
			const auto r6x = r5x - 1 + rax[1] ;
			if (!(MathProc::abs (r6x) >= precision))
				discard ;
			compute_write_number (r6x ,out ,iw) ;
			if (r6x > 0)
				out[--iw] = REAL ('+') ;
			out[--iw] = REAL ('e') ;
			const auto r7x = MathProc::maxof ((r5x - 1 - precision) ,VAR_ZERO) ;
			for (auto &&i : _RANGE_ (0 ,r7x)) {
				_STATIC_UNUSED_ (i) ;
				rax[0] /= r1x.varify_radix () ;
			}
			INDEX ix = iw - 1 ;
			for (auto &&i : _RANGE_ (r7x ,r5x - 1)) {
				_STATIC_UNUSED_ (i) ;
				out[--iw] = r1x.convert_number_w (rax[0] % r1x.varify_radix ()) ;
				iw += _EBOOL_ (out[ix] == r1x.convert_number_w (0)) ;
				rax[0] /= r1x.varify_radix () ;
			}
			out[--iw] = REAL ('.') ;
			iw += _EBOOL_ (out[ix] == REAL ('.')) ;
			out[--iw] = r1x.convert_number_w (rax[0] % r1x.varify_radix ()) ;
			rax[0] /= r1x.varify_radix () ;
		}
		if switch_once (fax) {
			//@info: case 'xxx000'
			if (!(rax[1] >= 0))
				discard ;
			for (auto &&i : _RANGE_ (0 ,LENGTH (rax[1]))) {
				_STATIC_UNUSED_ (i) ;
				out[--iw] = r1x.convert_number_w (0) ;
			}
			for (auto &&i : _RANGE_ (0 ,r5x)) {
				_STATIC_UNUSED_ (i) ;
				out[--iw] = r1x.convert_number_w (rax[0] % r1x.varify_radix ()) ;
				rax[0] /= r1x.varify_radix () ;
			}
		}
		if switch_once (fax) {
			//@info: case 'xxx.xxx'
			if (!(rax[1] >= 1 - r5x))
				discard ;
			if (!(rax[1] < 0))
				discard ;
			const auto r8x = MathProc::maxof (LENGTH (-rax[1] - precision) ,VAR_ZERO) ;
			for (auto &&i : _RANGE_ (0 ,r8x)) {
				_STATIC_UNUSED_ (i) ;
				rax[0] /= r1x.varify_radix () ;
			}
			INDEX ix = iw - 1 ;
			for (auto &&i : _RANGE_ (r8x ,LENGTH (-rax[1]))) {
				_STATIC_UNUSED_ (i) ;
				out[--iw] = r1x.convert_number_w (rax[0] % r1x.varify_radix ()) ;
				iw += _EBOOL_ (out[ix] == r1x.convert_number_w (0)) ;
				rax[0] /= r1x.varify_radix () ;
			}
			out[--iw] = REAL ('.') ;
			iw += _EBOOL_ (out[ix] == REAL ('.')) ;
			for (auto &&i : _RANGE_ (0 ,LENGTH (r5x + rax[1]))) {
				_STATIC_UNUSED_ (i) ;
				out[--iw] = r1x.convert_number_w (rax[0] % r1x.varify_radix ()) ;
				rax[0] /= r1x.varify_radix () ;
			}
		}
		if switch_once (fax) {
			//@info: case '0.000xxx'
			if (!(rax[1] < 1 - r5x))
				discard ;
			if (!(rax[1] < 0))
				discard ;
			const auto r9x = MathProc::maxof (LENGTH (-rax[1] - precision) ,VAR_ZERO) ;
			for (auto &&i : _RANGE_ (0 ,r9x)) {
				_STATIC_UNUSED_ (i) ;
				rax[0] /= r1x.varify_radix () ;
			}
			INDEX ix = iw - 1 ;
			for (auto &&i : _RANGE_ (r9x ,r5x)) {
				_STATIC_UNUSED_ (i) ;
				out[--iw] = r1x.convert_number_w (rax[0] % r1x.varify_radix ()) ;
				iw += _EBOOL_ (out[ix] == r1x.convert_number_w (0)) ;
				rax[0] /= r1x.varify_radix () ;
			}
			const auto r10x = MathProc::maxof (r9x ,r5x) ;
			for (auto &&i : _RANGE_ (r10x ,LENGTH (-rax[1]))) {
				_STATIC_UNUSED_ (i) ;
				out[--iw] = r1x.convert_number_w (0) ;
				iw += _EBOOL_ (out[ix] == r1x.convert_number_w (0)) ;
			}
			out[--iw] = REAL ('.') ;
			iw += _EBOOL_ (out[ix] == REAL ('.')) ;
			out[--iw] = r1x.convert_number_w (0) ;
		}
		if (rax[2] != 0)
			out[--iw] = REAL ('-') ;
		out_iw = iw ;
	}

	LENGTH log_of_number (const VAR64 &val ,const LENGTH &radix) const {
		LENGTH ret = 0 ;
		auto rax = VAR64 (1) ;
		while (TRUE) {
			if (rax > val)
				break ;
			ret++ ;
			rax *= radix ;
		}
		return _MOVE_ (ret) ;
	}

	template <class _ARG1>
	void template_write_bom (const ARGVF<_ARG1> &) {
		_STATIC_WARNING_ ("noop") ;
	}

	void template_write_bom (const ARGVF<STRU8> &) {
		static constexpr auto M_BOM = PACK<STRU8[3]> ({
			STRU8 (0XEF) ,STRU8 (0XBB) ,STRU8 (0XBF)}) ;
		auto rax = share () ;
		rax << PhanBuffer<const STRU8>::make (M_BOM.mP1) ;
		DEREF[this] = rax.share () ;
	}

	void template_write_bom (const ARGVF<STRU16> &) {
		static constexpr auto M_BOM = PACK<STRU16[1]> ({
			STRU16 (0XFEFF)}) ;
		auto rax = share () ;
		rax << PhanBuffer<const STRU16>::make (M_BOM.mP1) ;
		DEREF[this] = rax.share () ;
	}

	void template_write_bom (const ARGVF<STRU32> &) {
		static constexpr auto M_BOM = PACK<STRU32[1]> ({
			STRU32 (0X0000FEFF)}) ;
		auto rax = share () ;
		rax << PhanBuffer<const STRU32>::make (M_BOM.mP1) ;
		DEREF[this] = rax.share () ;
	}

	void template_write_bom (const ARGVF<STRW> &) {
		auto rax = share () ;
		_CAST_ (ARGV<TextWriter<STRUW>>::null ,rax).template_write_bom (ARGV<STRUW>::null) ;
		DEREF[this] = rax.share () ;
	}
} ;

template <class REAL>
template <class BASE>
class TextWriter<REAL>::Private::Attribute
	:private Proxy {
private:
	PhanRef<BASE> mBase ;

public:
	implicit Attribute () = delete ;

	explicit Attribute (PhanRef<BASE> &&base) {
		mBase = _MOVE_ (base) ;
	}

	REAL varify_ending_item () const {
		return REAL ('\0') ;
	}

	VAR64 varify_radix () const {
		return 10 ;
	}

	LENGTH varify_val32_precision () const {
		return 6 ;
	}

	LENGTH varify_val64_precision () const {
		_STATIC_WARNING_ ("mark") ;
		return 13 ;
	}

	BOOL varify_number_item (const REAL &item) const {
		if (!(item >= REAL ('0') && item <= REAL ('9')))
			return FALSE ;
		return TRUE ;
	}

	REAL convert_number_w (const VAR64 &number) const {
		return REAL (VAR64 ('0') + number) ;
	}

	void enable_escape (const BOOL &flag) const {
		mBase->mHeap->mEscapeFlag = flag ;
	}

	REAL varify_escape_item () const {
		return REAL ('\\') ;
	}

	BOOL varify_escape_w (const REAL &key) const {
		if (!mBase->mHeap->mEscapeFlag)
			return FALSE ;
		if (mBase->mHeap->mEscapeMappingSet.find (key) == VAR_NONE)
			return FALSE ;
		return TRUE ;
	}

	void modify_escape_w (const REAL &str_a ,const REAL &str_e) const {
		_DEBUG_ASSERT_ (str_a != varify_ending_item ()) ;
		INDEX ix = mBase->mHeap->mEscapeMappingSet.map (str_e) ;
		_DEBUG_ASSERT_ (ix == VAR_NONE) ;
		ix = mBase->mHeap->mEscape.insert () ;
		mBase->mHeap->mEscapeMappingSet.add (str_e ,ix) ;
		mBase->mHeap->mEscape[ix] = str_a ;
	}

	REAL convert_escape_w (const REAL &str_e) const {
		INDEX ix = mBase->mHeap->mEscapeMappingSet.map (str_e) ;
		_DYNAMIC_ASSERT_ (ix != VAR_NONE) ;
		return mBase->mHeap->mEscape[ix] ;
	}

	BOOL varify_space (const REAL &item) const {
		if (!(item == REAL ('\r') || item == REAL ('\n')))
			return FALSE ;
		return TRUE ;
	}

	BOOL varify_control (const REAL &item) const {
		if (!(item >= REAL (0) && item <= REAL (32)))
			if (item != REAL (127))
				return FALSE ;
		if (varify_space (item))
			return FALSE ;
		return TRUE ;
	}
} ;

template <class REAL>
inline void TextWriter<REAL>::CLS (const ARGVF<ARGC<1>> &) {}

template <class REAL>
inline void TextWriter<REAL>::BOM (const ARGVF<ARGC<2>> &) {}

template <class REAL>
inline void TextWriter<REAL>::GAP (const ARGVF<ARGC<3>> &) {}

template <class REAL>
inline void TextWriter<REAL>::EOS (const ARGVF<ARGC<4>> &) {}

class RegularReader {
public:
	static DEF<void (const ARGVF<ARGC<1>> &)> HINT_IDENTIFIER ;
	static DEF<void (const ARGVF<ARGC<2>> &)> HINT_VALUE ;
	static DEF<void (const ARGVF<ARGC<3>> &)> HINT_STRING ;
	static DEF<void (const ARGVF<ARGC<4>> &)> HINT_NEWGAP ;
	static DEF<void (const ARGVF<ARGC<5>> &)> HINT_NEWLINE ;
	static DEF<void (const ARGVF<ARGC<6>> &)> SKIP_GAP ;
	static DEF<void (const ARGVF<ARGC<7>> &)> SKIP_GAP_SPACE ;
	static DEF<void (const ARGVF<ARGC<8>> &)> SKIP_GAP_ENDLINE ;
	static DEF<void (const ARGVF<ARGC<9>> &)> SKIP_LINE ;

private:
	struct HEAP_PACK {
		TextReader<STRU8> mReader ;
	} ;

private:
	SharedRef<HEAP_PACK> mHeap ;
	PhanRef<TextReader<STRU8>> mReader ;
	Array<STRU8> mCache ;
	INDEX mPeek ;
	BOOL mHintStringTextFlag ;
	LENGTH mHintNextTextSize ;

public:
	implicit RegularReader () {
		mPeek = 0 ;
		mHintStringTextFlag = FALSE ;
		mHintNextTextSize = 0 ;
	}

	explicit RegularReader (PhanRef<TextReader<STRU8>> &&reader ,const LENGTH &ll_len) {
		mReader = _MOVE_ (reader) ;
		const auto r1x = mReader->attr () ;
		r1x.modify_space (STRU8 (' ') ,1) ;
		r1x.modify_space (STRU8 ('\t') ,1) ;
		r1x.modify_space (STRU8 ('\v') ,1) ;
		r1x.modify_space (STRU8 ('\r') ,2) ;
		r1x.modify_space (STRU8 ('\n') ,2) ;
		r1x.modify_space (STRU8 ('\f') ,2) ;
		r1x.modify_escape_r (STRU8 ('t') ,STRU8 ('\t')) ;
		r1x.modify_escape_r (STRU8 ('v') ,STRU8 ('\v')) ;
		r1x.modify_escape_r (STRU8 ('r') ,STRU8 ('\r')) ;
		r1x.modify_escape_r (STRU8 ('n') ,STRU8 ('\n')) ;
		r1x.modify_escape_r (STRU8 ('f') ,STRU8 ('\f')) ;
		r1x.modify_escape_r (STRU8 ('\"') ,STRU8 ('\"')) ;
		r1x.modify_escape_r (STRU8 ('/') ,STRU8 ('/')) ;
		r1x.modify_escape_r (STRU8 ('\\') ,STRU8 ('\\')) ;
		_STATIC_WARNING_ ("mark") ;
		//@info: disable default escape-str convertion
		r1x.enable_escape (FALSE) ;
		mReader.self >> TextReader<STRU8>::BOM ;
		mCache = Array<STRU8> (ll_len) ;
		for (auto &&i : _RANGE_ (0 ,mCache.length ()))
			mReader.self >> mCache[i] ;
		mPeek = 0 ;
		mHintStringTextFlag = FALSE ;
		mHintNextTextSize = 0 ;
	}

	RegularReader share () leftvalue {
		RegularReader ret ;
		ret.mHeap = SharedRef<HEAP_PACK>::make () ;
		ret.mHeap->mReader = mReader->share () ;
		ret.mReader = PhanRef<TextReader<STRU8>>::make (ret.mHeap->mReader) ;
		ret.mCache = mCache ;
		ret.mPeek = mPeek ;
		ret.mHintStringTextFlag = FALSE ;
		ret.mHintNextTextSize = 0 ;
		return _MOVE_ (ret) ;
	}

	const STRU8 &get (const INDEX &index) const leftvalue {
		_DEBUG_ASSERT_ (index >= 0 && index < mCache.length ()) ;
		_DEBUG_ASSERT_ (mPeek >= 0 && mPeek < mCache.length ()) ;
		return mCache[(mPeek + index) % mCache.length ()] ;
	}

	inline const STRU8 &operator[] (const INDEX &index) const leftvalue {
		return get (index) ;
	}

	void read () {
		mReader.self >> mCache[mPeek] ;
		mPeek = (mPeek + 1) % mCache.length () ;
	}

	inline void operator++ (VAR32) {
		read () ;
	}

	void read (const Plain<STRU8> &data) {
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
		for (auto &&i : _RANGE_ (0 ,data.size ())) {
			_DYNAMIC_ASSERT_ (get (0) == data.self[i]) ;
			read () ;
		}
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic pop
#endif
	}

	inline RegularReader &operator>> (const Plain<STRU8> &data) {
		read (data) ;
		return DEREF[this] ;
	}

	void read (const DEF<decltype (HINT_IDENTIFIER)> &) {
		mHintStringTextFlag = FALSE ;
		mHintNextTextSize = 0 ;
		auto rax = share () ;
		while (TRUE) {
			const auto r1x = BOOL (rax[0] >= STRU8 ('A') && rax[0] <= STRU8 ('Z')) ;
			const auto r2x = BOOL (rax[0] >= STRU8 ('a') && rax[0] <= STRU8 ('z')) ;
			const auto r3x = BOOL (rax[0] == STRU8 ('_')) ;
			if (mHintNextTextSize == 0)
				_DYNAMIC_ASSERT_ (r1x || r2x || r3x) ;
			if (!r1x && !r2x && !r3x)
				if (!(rax[0] >= STRU8 ('0') && rax[0] <= STRU8 ('9')))
					if (!(rax[0] == STRU8 ('-') || rax[0] == STRU8 ('.') || rax[0] == STRU8 (':')))
						break ;
			rax++ ;
			mHintNextTextSize++ ;
		}
	}

	inline RegularReader &operator>> (const DEF<decltype (HINT_IDENTIFIER)> &) {
		read (HINT_IDENTIFIER) ;
		return DEREF[this] ;
	}

	void read (const DEF<decltype (HINT_VALUE)> &) {
		mHintStringTextFlag = FALSE ;
		mHintNextTextSize = 0 ;
		auto rax = share () ;
		if switch_once (TRUE) {
			if (!(rax[0] == STRU8 ('+') || rax[0] == STRU8 ('-')))
				discard ;
			rax++ ;
			mHintNextTextSize++ ;
		}
		const auto r1x = rax[0] ;
		_DYNAMIC_ASSERT_ (r1x >= STRU8 ('0') && r1x <= STRU8 ('9')) ;
		rax++ ;
		mHintNextTextSize++ ;
		while (TRUE) {
			if (r1x == STRU8 ('0'))
				break ;
			if (!(rax[0] >= STRU8 ('0') && rax[0] <= STRU8 ('9')))
				break ;
			rax++ ;
			mHintNextTextSize++ ;
		}
		if switch_once (TRUE) {
			if (rax[0] != STRU8 ('.'))
				discard ;
			rax++ ;
			mHintNextTextSize++ ;
			while (TRUE) {
				if (!(rax[0] >= STRU8 ('0') && rax[0] <= STRU8 ('9')))
					break ;
				rax++ ;
				mHintNextTextSize++ ;
			}
		}
		if switch_once (TRUE) {
			if (!(rax[0] == STRU8 ('e') || rax[0] == STRU8 ('E')))
				discard ;
			rax++ ;
			mHintNextTextSize++ ;
			if switch_once (TRUE) {
				if (!(rax[0] == STRU8 ('+') || rax[0] == STRU8 ('-')))
					discard ;
				rax++ ;
				mHintNextTextSize++ ;
			}
			_DYNAMIC_ASSERT_ (rax[0] >= STRU8 ('0') && rax[0] <= STRU8 ('9')) ;
			rax++ ;
			mHintNextTextSize++ ;
			while (TRUE) {
				if (!(rax[0] >= STRU8 ('0') && rax[0] <= STRU8 ('9')))
					break ;
				rax++ ;
				mHintNextTextSize++ ;
			}
		}
	}

	inline RegularReader &operator>> (const DEF<decltype (HINT_VALUE)> &) {
		read (HINT_VALUE) ;
		return DEREF[this] ;
	}

	void read (const DEF<decltype (HINT_STRING)> &) {
		mHintStringTextFlag = TRUE ;
		mHintNextTextSize = 0 ;
		auto rax = share () ;
		const auto r1x = mReader->attr () ;
		auto rbx = STRU8 () ;
		_DYNAMIC_ASSERT_ (rax[0] == STRU8 ('\"')) ;
		rax++ ;
		while (TRUE) {
			if (rax[0] == STRU8 ('\0'))
				break ;
			if (rax[0] == STRU8 ('\"'))
				break ;
			auto fax = TRUE ;
			if switch_once (fax) {
				rbx = rax[0] ;
				rax++ ;
				if (!(rbx == r1x.varify_escape_item ()))
					discard ;
				rbx = rax[0] ;
				rax++ ;
				rbx = r1x.convert_escape_r (rbx) ;
				mHintNextTextSize++ ;
			}
			if switch_once (fax) {
				const auto r2x = r1x.varify_control (rbx) ;
				_DYNAMIC_ASSERT_ (!r2x) ;
				mHintNextTextSize++ ;
			}
		}
		_DYNAMIC_ASSERT_ (rax[0] == STRU8 ('\"')) ;
		rax++ ;
	}

	inline RegularReader &operator>> (const DEF<decltype (HINT_STRING)> &) {
		read (HINT_STRING) ;
		return DEREF[this] ;
	}

	void read (const DEF<decltype (HINT_NEWGAP)> &) {
		mHintStringTextFlag = FALSE ;
		mHintNextTextSize = 0 ;
		auto rax = share () ;
		const auto r1x = mReader->attr () ;
		while (TRUE) {
			if (rax[0] == r1x.varify_ending_item ())
				break ;
			if (r1x.varify_space (rax[0]))
				break ;
			_DYNAMIC_ASSERT_ (!r1x.varify_control (rax[0])) ;
			rax++ ;
			mHintNextTextSize++ ;
		}
	}

	inline RegularReader &operator>> (const DEF<decltype (HINT_NEWGAP)> &) {
		read (HINT_NEWGAP) ;
		return DEREF[this] ;
	}

	void read (const DEF<decltype (HINT_NEWLINE)> &) {
		mHintStringTextFlag = FALSE ;
		mHintNextTextSize = 0 ;
		auto rax = share () ;
		const auto r1x = mReader->attr () ;
		while (TRUE) {
			if (rax[0] == r1x.varify_ending_item ())
				break ;
			if (r1x.varify_space (rax[0] ,2))
				break ;
			_DYNAMIC_ASSERT_ (!r1x.varify_control (rax[0])) ;
			rax++ ;
			mHintNextTextSize++ ;
		}
	}

	inline RegularReader &operator>> (const DEF<decltype (HINT_NEWLINE)> &) {
		read (HINT_NEWLINE) ;
		return DEREF[this] ;
	}

	void read (const DEF<decltype (SKIP_GAP)> &) {
		const auto r1x = mReader->attr () ;
		while (TRUE) {
			if (!r1x.varify_space (get (0)))
				break ;
			read () ;
		}
	}

	inline RegularReader &operator>> (const DEF<decltype (SKIP_GAP)> &) {
		read (SKIP_GAP) ;
		return DEREF[this] ;
	}

	void read (const DEF<decltype (SKIP_GAP_SPACE)> &) {
		const auto r1x = mReader->attr () ;
		while (TRUE) {
			if (!r1x.varify_space (get (0) ,1))
				break ;
			read () ;
		}
	}

	inline RegularReader &operator>> (const DEF<decltype (SKIP_GAP_SPACE)> &) {
		read (SKIP_GAP_SPACE) ;
		return DEREF[this] ;
	}

	void read (const DEF<decltype (SKIP_GAP_ENDLINE)> &) {
		const auto r1x = mReader->attr () ;
		while (TRUE) {
			if (!r1x.varify_space (get (0) ,2))
				break ;
			read () ;
		}
	}

	inline RegularReader &operator>> (const DEF<decltype (SKIP_GAP_ENDLINE)> &) {
		read (SKIP_GAP_ENDLINE) ;
		return DEREF[this] ;
	}

	void read (const DEF<decltype (SKIP_LINE)> &) {
		auto rax = STRU8 () ;
		while (TRUE) {
			rax = get (0) ;
			const auto r1x = BOOL (rax == STRU8 ('\r') || rax == STRU8 ('\n') || rax == STRU8 ('\f')) ;
			if (r1x)
				break ;
			read () ;
		}
		if (rax != STRU8 ('\r'))
			return ;
		const auto r2x = get (0) ;
		if (r2x != STRU8 ('\n'))
			return ;
		read () ;
	}

	inline RegularReader &operator>> (const DEF<decltype (SKIP_LINE)> &) {
		read (SKIP_LINE) ;
		return DEREF[this] ;
	}

	void read (String<STRU8> &data) {
		const auto r1x = mReader->attr () ;
		const auto r2x = mHintStringTextFlag ;
		const auto r3x = mHintNextTextSize ;
		mHintStringTextFlag = FALSE ;
		mHintNextTextSize = 0 ;
		if (data.size () < r3x)
			data = String<STRU8> (r3x) ;
		data.clear () ;
		auto rax = STRU8 () ;
		if switch_once (TRUE) {
			if (!r2x)
				discard ;
			_DYNAMIC_ASSERT_ (get (0) == STRU8 ('\"')) ;
			read () ;
		}
		for (auto &&i : _RANGE_ (0 ,r3x)) {
			auto fax = TRUE ;
			if switch_once (fax) {
				rax = get (0) ;
				read () ;
				const auto r4x = BOOL (rax == r1x.varify_escape_item ()) ;
				if (!r4x)
					discard ;
				rax = get (0) ;
				read () ;
				rax = r1x.convert_escape_r (rax) ;
				data[i] = rax ;
			}
			if switch_once (fax) {
				const auto r5x = r1x.varify_control (rax) ;
				_DYNAMIC_ASSERT_ (!r5x) ;
				data[i] = rax ;
			}
		}
		if switch_once (TRUE) {
			if (!r2x)
				discard ;
			_DYNAMIC_ASSERT_ (get (0) == STRU8 ('\"')) ;
			read () ;
		}
	}

	inline RegularReader &operator>> (String<STRU8> &data) {
		read (data) ;
		return DEREF[this] ;
	}
} ;

inline void RegularReader::HINT_IDENTIFIER (const ARGVF<ARGC<1>> &) {}

inline void RegularReader::HINT_VALUE (const ARGVF<ARGC<2>> &) {}

inline void RegularReader::HINT_STRING (const ARGVF<ARGC<3>> &) {}

inline void RegularReader::HINT_NEWGAP (const ARGVF<ARGC<4>> &) {}

inline void RegularReader::HINT_NEWLINE (const ARGVF<ARGC<5>> &) {}

inline void RegularReader::SKIP_GAP (const ARGVF<ARGC<6>> &) {}

inline void RegularReader::SKIP_GAP_SPACE (const ARGVF<ARGC<7>> &) {}

inline void RegularReader::SKIP_GAP_ENDLINE (const ARGVF<ARGC<8>> &) {}

inline void RegularReader::SKIP_LINE (const ARGVF<ARGC<9>> &) {}
} ;