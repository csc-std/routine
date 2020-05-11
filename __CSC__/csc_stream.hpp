﻿#pragma once

#ifndef __CSC_STREAM__
#define __CSC_STREAM__
#endif

#include "csc.hpp"
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
	_STATIC_ASSERT_ (std::is_same<REAL ,BYTE>::value) ;

public:
	exports class Binder
		:public Interface {
	public:
		virtual void friend_read (ByteReader &reader) = 0 ;
	} ;

	static DEF<void (const ARGV<ARGC<1>> &)> CLS ;
	static DEF<void (const ARGV<ARGC<3>> &)> GAP ;
	static DEF<void (const ARGV<ARGC<4>> &)> EOS ;

private:
	class Heap {
	private:
		friend ByteReader ;
		BOOL mEndianFlag ;
	} ;

private:
	struct Detail ;
	SharedRef<Heap> mHeap ;
	PhanBuffer<const REAL> mStream ;
	INDEX mRead ;
	INDEX mWrite ;

public:
	ByteReader () {
		reset () ;
	}

	explicit ByteReader (const PhanBuffer<const REAL> &stream) {
		mHeap = SharedRef<Heap>::make () ;
		mStream = PhanBuffer<const REAL>::make (stream) ;
		reset () ;
	}

	DEF<typename Detail::template Attribute<ByteReader>> attr () leftvalue {
		using Attribute = typename Detail::template Attribute<ByteReader> ;
		return Attribute (_DEREF_ (this)) ;
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

	void reset (INDEX read_ ,INDEX write_) {
		_DEBUG_ASSERT_ (mHeap.exist ()) ;
		_DEBUG_ASSERT_ (read_ >= 0 && read_ < mStream.size ()) ;
		_DEBUG_ASSERT_ (write_ >= 0 && write_ < mStream.size ()) ;
		_DEBUG_ASSERT_ (read_ <= write_) ;
		mRead = read_ ;
		mWrite = write_ ;
	}

	ByteReader copy () popping {
		ByteReader ret ;
		ret.mHeap = mHeap ;
		ret.mStream = PhanBuffer<const REAL>::make (mStream) ;
		ret.mRead = mRead ;
		ret.mWrite = mWrite ;
		return std::move (ret) ;
	}

	template <class _RET>
	_RET read () popping {
		_STATIC_ASSERT_ (!std::is_reference<_RET>::value) ;
		_RET ret ;
		read (ret) ;
		return std::move (ret) ;
	}

	void read (BYTE &data) {
		const auto r1x = attr () ;
		auto fax = TRUE ;
		if switch_case (fax) {
			if (!(mRead < mWrite))
				discard ;
			data = BYTE (mStream[mRead]) ;
			mRead++ ;
		}
		if switch_case (fax) {
			data = r1x.varify_ending_item () ;
		}
	}

	inline ByteReader &operator>> (BYTE &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	void read (WORD &data) {
		const auto r1x = WORD (0X0001) ;
		auto &r2x = _CAST_<BYTE[_SIZEOF_ (WORD)]> (r1x) ;
		auto &r3x = _CAST_<BYTE[_SIZEOF_ (WORD)]> (data) ;
		for (auto &&i : _RANGE_ (0 ,_COUNTOF_ (decltype (r3x))))
			read (r3x[r2x[i]]) ;
	}

	inline ByteReader &operator>> (WORD &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	void read (CHAR &data) {
		const auto r1x = CHAR (0X00010203) ;
		auto &r2x = _CAST_<BYTE[_SIZEOF_ (CHAR)]> (r1x) ;
		auto &r3x = _CAST_<BYTE[_SIZEOF_ (CHAR)]> (data) ;
		for (auto &&i : _RANGE_ (0 ,_COUNTOF_ (decltype (r3x))))
			read (r3x[r2x[i]]) ;
	}

	inline ByteReader &operator>> (CHAR &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	void read (DATA &data) {
		const auto r1x = DATA (0X0001020304050607) ;
		auto &r2x = _CAST_<BYTE[_SIZEOF_ (DATA)]> (r1x) ;
		auto &r3x = _CAST_<BYTE[_SIZEOF_ (DATA)]> (data) ;
		for (auto &&i : _RANGE_ (0 ,_COUNTOF_ (decltype (r3x))))
			read (r3x[r2x[i]]) ;
	}

	inline ByteReader &operator>> (DATA &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	void read (BOOL &data) {
		read (_CAST_<U::BYTE_BASE_TYPE<BOOL>> (data)) ;
	}

	inline ByteReader &operator>> (BOOL &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	void read (VAR32 &data) {
		read (_CAST_<U::BYTE_BASE_TYPE<VAR32>> (data)) ;
	}

	inline ByteReader &operator>> (VAR32 &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	void read (VAR64 &data) {
		read (_CAST_<U::BYTE_BASE_TYPE<VAR64>> (data)) ;
	}

	inline ByteReader &operator>> (VAR64 &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	void read (VAL32 &data) {
		read (_CAST_<U::BYTE_BASE_TYPE<VAL32>> (data)) ;
	}

	inline ByteReader &operator>> (VAL32 &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	void read (VAL64 &data) {
		read (_CAST_<U::BYTE_BASE_TYPE<VAL64>> (data)) ;
	}

	inline ByteReader &operator>> (VAL64 &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	template <class _ARG1 ,class _ARG2>
	void read (Array<_ARG1 ,_ARG2> &data) {
		const auto r1x = LENGTH (read<VAR32> ()) ;
		_DYNAMIC_ASSERT_ (r1x >= 0 && r1x < VAR32_MAX) ;
		if (data.size () < r1x)
			data = Array<_ARG1 ,_ARG2> (r1x) ;
		for (auto &&i : _RANGE_ (0 ,r1x))
			read (data[i]) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline ByteReader &operator>> (Array<_ARG1 ,_ARG2> &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	template <class _ARG1>
	void read (const Plain<_ARG1> &data) {
#pragma GCC diagnostic push
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
		auto rax = REAL () ;
		for (auto &&i : _RANGE_ (0 ,data.size ())) {
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == data.self[i]) ;
		}
#pragma GCC diagnostic pop
	}

	template <class _ARG1>
	inline ByteReader &operator>> (const Plain<_ARG1> &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	template <class _ARG1 ,class _ARG2>
	void read (String<_ARG1 ,_ARG2> &data) {
		_STATIC_ASSERT_ (stl::is_str_xyz<_ARG1>::value) ;
		const auto r1x = LENGTH (read<VAR32> ()) ;
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
		return _DEREF_ (this) ;
	}

	template <class _ARG1 ,class _ARG2>
	void read (Buffer<_ARG1 ,_ARG2> &data) {
		for (auto &&i : _RANGE_ (0 ,data.size ()))
			read (data[i]) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline ByteReader &operator>> (Buffer<_ARG1 ,_ARG2> &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	void read (Binder &data) {
		data.friend_read (_DEREF_ (this)) ;
	}

	inline ByteReader &operator>> (Binder &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	void read (const PTR<void (ByteReader &)> &proc) {
		const auto r1x = Function<void (ByteReader &)> (proc) ;
		r1x (_DEREF_ (this)) ;
	}

	inline ByteReader &operator>> (const PTR<void (ByteReader &)> &proc) {
		read (proc) ;
		return _DEREF_ (this) ;
	}

	void scans () {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1 ,class... _ARGS>
	void scans (_ARG1 &list_one ,_ARGS &...list_rest) {
		read (list_one) ;
		scans (list_rest...) ;
	}

	void read (const PTR<decltype (CLS)> &) {
		reset () ;
	}

	inline ByteReader &operator>> (const PTR<decltype (CLS)> &proc) {
		read (proc) ;
		return _DEREF_ (this) ;
	}

	void read (const PTR<decltype (GAP)> &) {
		const auto r1x = attr () ;
		auto ris = copy () ;
		auto rax = REAL () ;
		ris >> rax ;
		_DYNAMIC_ASSERT_ (rax == r1x.varify_space_item ()) ;
		ris >> rax ;
		_DYNAMIC_ASSERT_ (rax == r1x.varify_space_item ()) ;
		_DEREF_ (this) = ris.copy () ;
	}

	inline ByteReader &operator>> (const PTR<decltype (GAP)> &proc) {
		read (proc) ;
		return _DEREF_ (this) ;
	}

	void read (const PTR<decltype (EOS)> &) {
		const auto r1x = attr () ;
		auto ris = copy () ;
		auto rax = REAL () ;
		while (TRUE) {
			if (ris.length () == 0)
				break ;
			ris >> rax ;
			_DYNAMIC_ASSERT_ (rax == r1x.varify_ending_item ()) ;
		}
		_DEREF_ (this) = ris.copy () ;
	}

	inline ByteReader &operator>> (const PTR<decltype (EOS)> &proc) {
		read (proc) ;
		return _DEREF_ (this) ;
	}
} ;

template <class REAL>
struct ByteReader<REAL>::Detail {
	template <class BASE>
	class Attribute final
		:private Proxy {
	private:
		friend ByteReader ;
		BASE &mBase ;

	public:
		inline Attribute () = delete ;

		inline REAL varify_ending_item () const {
			return REAL (0X00) ;
		}

		inline REAL varify_space_item () const {
			return REAL (0X00) ;
		}

	private:
		inline explicit Attribute (BASE &base)
			:mBase (base) {}
	} ;
} ;

template <class REAL>
inline void ByteReader<REAL>::CLS (const ARGV<ARGC<1>> &) {}
template <class REAL>
inline void ByteReader<REAL>::GAP (const ARGV<ARGC<3>> &) {}
template <class REAL>
inline void ByteReader<REAL>::EOS (const ARGV<ARGC<4>> &) {}

template <class REAL>
class ByteWriter {
	_STATIC_ASSERT_ (std::is_same<REAL ,BYTE>::value) ;

public:
	exports class Binder
		:public Interface {
	public:
		virtual void friend_write (ByteWriter &writer) const = 0 ;
	} ;

	static DEF<void (const ARGV<ARGC<1>> &)> CLS ;
	static DEF<void (const ARGV<ARGC<3>> &)> GAP ;
	static DEF<void (const ARGV<ARGC<4>> &)> EOS ;

private:
	class Heap {
	private:
		friend ByteWriter ;
		SharedRef<FixedBuffer<REAL>> mBuffer ;
	} ;

private:
	struct Detail ;
	SharedRef<Heap> mHeap ;
	PhanBuffer<REAL> mStream ;
	INDEX mRead ;
	INDEX mWrite ;

public:
	ByteWriter () {
		reset () ;
	}

	explicit ByteWriter (const PhanBuffer<REAL> &stream) {
		mHeap = SharedRef<Heap>::make () ;
		mStream = PhanBuffer<REAL>::make (stream) ;
		reset () ;
	}

	explicit ByteWriter (SharedRef<FixedBuffer<REAL>> &&stream) {
		mHeap = SharedRef<Heap>::make () ;
		mHeap->mBuffer = std::move (stream) ;
		mStream = PhanBuffer<REAL>::make (mHeap->mBuffer.self) ;
		reset () ;
	}

	DEF<typename Detail::template Attribute<ByteWriter>> attr () leftvalue {
		using Attribute = typename Detail::template Attribute<ByteWriter> ;
		return Attribute (_DEREF_ (this)) ;
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

	void reset (INDEX read_ ,INDEX write_) {
		_DEBUG_ASSERT_ (mHeap.exist ()) ;
		_DEBUG_ASSERT_ (read_ >= 0 && read_ < mStream.size ()) ;
		_DEBUG_ASSERT_ (write_ >= 0 && write_ < mStream.size ()) ;
		_DEBUG_ASSERT_ (read_ <= write_) ;
		mRead = read_ ;
		mWrite = write_ ;
	}

	ByteWriter copy () popping {
		ByteWriter ret ;
		ret.mHeap = mHeap ;
		ret.mStream = PhanBuffer<REAL>::make (mStream) ;
		ret.mRead = mRead ;
		ret.mWrite = mWrite ;
		return std::move (ret) ;
	}

	void write (const BYTE &data) {
		_DYNAMIC_ASSERT_ (mWrite < mStream.size ()) ;
		mStream[mWrite] = REAL (data) ;
		mWrite++ ;
	}

	inline ByteWriter &operator<< (const BYTE &data) {
		write (data) ;
		return _DEREF_ (this) ;
	}

	void write (const WORD &data) {
		const auto r1x = WORD (0X0001) ;
		auto &r2x = _CAST_<BYTE[_SIZEOF_ (WORD)]> (r1x) ;
		auto &r3x = _CAST_<BYTE[_SIZEOF_ (WORD)]> (data) ;
		for (auto &&i : _RANGE_ (0 ,_COUNTOF_ (decltype (r3x))))
			write (r3x[r2x[i]]) ;
	}

	inline ByteWriter &operator<< (const WORD &data) {
		write (data) ;
		return _DEREF_ (this) ;
	}

	void write (const CHAR &data) {
		const auto r1x = CHAR (0X00010203) ;
		auto &r2x = _CAST_<BYTE[_SIZEOF_ (CHAR)]> (r1x) ;
		auto &r3x = _CAST_<BYTE[_SIZEOF_ (CHAR)]> (data) ;
		for (auto &&i : _RANGE_ (0 ,_COUNTOF_ (decltype (r3x))))
			write (r3x[r2x[i]]) ;
	}

	inline ByteWriter &operator<< (const CHAR &data) {
		write (data) ;
		return _DEREF_ (this) ;
	}

	void write (const DATA &data) {
		const auto r1x = DATA (0X0001020304050607) ;
		auto &r2x = _CAST_<BYTE[_SIZEOF_ (DATA)]> (r1x) ;
		auto &r3x = _CAST_<BYTE[_SIZEOF_ (DATA)]> (data) ;
		for (auto &&i : _RANGE_ (0 ,_COUNTOF_ (decltype (r3x))))
			write (r3x[r2x[i]]) ;
	}

	inline ByteWriter &operator<< (const DATA &data) {
		write (data) ;
		return _DEREF_ (this) ;
	}

	void write (const BOOL &data) {
		const auto r1x = _CAST_<U::BYTE_BASE_TYPE<BOOL>> (data) ;
		write (r1x) ;
	}

	inline ByteWriter &operator<< (const BOOL &data) {
		write (data) ;
		return _DEREF_ (this) ;
	}

	void write (const PTR<const VOID> &) = delete ;

	inline ByteWriter &operator<< (const PTR<const VOID> &) = delete ;

	void write (const VAR32 &data) {
		const auto r1x = _CAST_<U::BYTE_BASE_TYPE<VAR32>> (data) ;
		write (r1x) ;
	}

	inline ByteWriter &operator<< (const VAR32 &data) {
		write (data) ;
		return _DEREF_ (this) ;
	}

	void write (const VAR64 &data) {
		const auto r1x = _CAST_<U::BYTE_BASE_TYPE<VAR64>> (data) ;
		write (r1x) ;
	}

	inline ByteWriter &operator<< (const VAR64 &data) {
		write (data) ;
		return _DEREF_ (this) ;
	}

	void write (const VAL32 &data) {
		const auto r1x = _CAST_<U::BYTE_BASE_TYPE<VAL32>> (data) ;
		write (r1x) ;
	}

	inline ByteWriter &operator<< (const VAL32 &data) {
		write (data) ;
		return _DEREF_ (this) ;
	}

	void write (const VAL64 &data) {
		const auto r1x = _CAST_<U::BYTE_BASE_TYPE<VAL64>> (data) ;
		write (r1x) ;
	}

	inline ByteWriter &operator<< (const VAL64 &data) {
		write (data) ;
		return _DEREF_ (this) ;
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
		return _DEREF_ (this) ;
	}

	template <class _ARG1>
	void write (const Plain<_ARG1> &data) {
#pragma GCC diagnostic push
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
		for (auto &&i : _RANGE_ (0 ,data.size ()))
			write (data.self[i]) ;
#pragma GCC diagnostic pop
	}

	template <class _ARG1>
	inline ByteWriter &operator<< (const Plain<_ARG1> &data) {
		write (data) ;
		return _DEREF_ (this) ;
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
		return _DEREF_ (this) ;
	}

	template <class _ARG1 ,class _ARG2>
	void write (const Buffer<_ARG1 ,_ARG2> &data) {
		for (auto &&i : _RANGE_ (0 ,data.size ()))
			write (data[i]) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline ByteWriter &operator<< (const Buffer<_ARG1 ,_ARG2> &data) {
		write (data) ;
		return _DEREF_ (this) ;
	}

	void write (const Binder &data) {
		data.friend_write (_DEREF_ (this)) ;
	}

	inline ByteWriter &operator<< (const Binder &data) {
		write (data) ;
		return _DEREF_ (this) ;
	}

	void write (const PTR<void (ByteWriter &)> &proc) {
		const auto r1x = Function<void (ByteWriter &)> (proc) ;
		r1x (_DEREF_ (this)) ;
	}

	inline ByteWriter &operator<< (const PTR<void (ByteWriter &)> &proc) {
		write (proc) ;
		return _DEREF_ (this) ;
	}

	void prints () {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1 ,class... _ARGS>
	void prints (const _ARG1 &list_one ,const _ARGS &...list_rest) {
		write (list_one) ;
		prints (list_rest...) ;
	}

	void write (const PTR<decltype (CLS)> &) {
		reset () ;
	}

	inline ByteWriter &operator<< (const PTR<decltype (CLS)> &proc) {
		write (proc) ;
		return _DEREF_ (this) ;
	}

	void write (const PTR<decltype (GAP)> &) {
		const auto r1x = attr () ;
		auto wos = copy () ;
		wos << r1x.varify_space_item () ;
		wos << r1x.varify_space_item () ;
		_DEREF_ (this) = wos.copy () ;
	}

	inline ByteWriter &operator<< (const PTR<decltype (GAP)> &proc) {
		write (proc) ;
		return _DEREF_ (this) ;
	}

	void write (const PTR<decltype (EOS)> &) {
		const auto r1x = attr () ;
		auto wos = copy () ;
		for (auto &&i : _RANGE_ (0 ,wos.size () - wos.length ())) {
			wos << r1x.varify_ending_item () ;
			_STATIC_UNUSED_ (i) ;
		}
		_DEREF_ (this) = wos.copy () ;
	}

	inline ByteWriter &operator<< (const PTR<decltype (EOS)> &proc) {
		write (proc) ;
		return _DEREF_ (this) ;
	}
} ;

template <class REAL>
struct ByteWriter<REAL>::Detail {
	template <class BASE>
	class Attribute final
		:private Proxy {
	private:
		friend ByteWriter ;
		BASE &mBase ;

	public:
		inline Attribute () = delete ;

		inline REAL varify_ending_item () const {
			return REAL (0X00) ;
		}

		inline REAL varify_space_item () const {
			return REAL (0X00) ;
		}

	private:
		inline explicit Attribute (BASE &base)
			:mBase (base) {}
	} ;
} ;

template <class REAL>
inline void ByteWriter<REAL>::CLS (const ARGV<ARGC<1>> &) {}
template <class REAL>
inline void ByteWriter<REAL>::GAP (const ARGV<ARGC<3>> &) {}
template <class REAL>
inline void ByteWriter<REAL>::EOS (const ARGV<ARGC<4>> &) {}

template <class REAL>
class TextReader {
	_STATIC_ASSERT_ (stl::is_str_xyz<REAL>::value) ;

public:
	exports class Binder
		:public Interface {
	public:
		virtual void friend_read (TextReader &reader) = 0 ;
	} ;

	static DEF<void (const ARGV<ARGC<1>> &)> CLS ;
	static DEF<void (const ARGV<ARGC<2>> &)> BOM ;
	static DEF<void (const ARGV<ARGC<3>> &)> GAP ;
	static DEF<void (const ARGV<ARGC<4>> &)> EOS ;

private:
	class Heap {
	private:
		friend TextReader ;
		BOOL mEndianFlag ;
		BOOL mEscapeFlag ;
		Deque<REAL> mEscapeList ;
		HashSet<REAL> mEscapeMappingSet ;
		Deque<PACK<REAL ,FLAG>> mSpaceList ;
		HashSet<REAL> mSpaceMappingSet ;
	} ;

private:
	template <class>
	friend class TextReader ;
	struct Detail ;
	SharedRef<Heap> mHeap ;
	PhanBuffer<const REAL> mStream ;
	INDEX mRead ;
	INDEX mWrite ;

public:
	TextReader () {
		reset () ;
	}

	explicit TextReader (const PhanBuffer<const REAL> &stream) {
		const auto r1x = attr () ;
		mHeap = SharedRef<Heap>::make () ;
		r1x.enable_endian (FALSE) ;
		r1x.enable_escape (FALSE) ;
		mStream = PhanBuffer<const REAL>::make (stream) ;
		reset () ;
	}

	DEF<typename Detail::template Attribute<TextReader>> attr () leftvalue {
		using Attribute = typename Detail::template Attribute<TextReader> ;
		return Attribute (_DEREF_ (this)) ;
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

	void reset (INDEX read_ ,INDEX write_) {
		_DEBUG_ASSERT_ (mHeap.exist ()) ;
		_DEBUG_ASSERT_ (read_ >= 0 && read_ < mStream.size ()) ;
		_DEBUG_ASSERT_ (write_ >= 0 && write_ < mStream.size ()) ;
		_DEBUG_ASSERT_ (read_ <= write_) ;
		mRead = read_ ;
		mWrite = write_ ;
	}

	TextReader copy () popping {
		TextReader ret ;
		ret.mHeap = mHeap ;
		ret.mStream = PhanBuffer<const REAL>::make (mStream) ;
		ret.mRead = mRead ;
		ret.mWrite = mWrite ;
		return std::move (ret) ;
	}

	template <class _RET>
	_RET read () popping {
		_STATIC_ASSERT_ (!std::is_reference<_RET>::value) ;
		_RET ret ;
		read (ret) ;
		return std::move (ret) ;
	}

	void read (REAL &data) {
		const auto r1x = attr () ;
		auto fax = TRUE ;
		if switch_case (fax) {
			if (!(mRead < mWrite))
				discard ;
			if switch_case (TRUE) {
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
		if switch_case (fax) {
			data = r1x.varify_ending_item () ;
		}
	}

	inline TextReader &operator>> (REAL &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	void read (BOOL &data) {
		auto rax = REAL () ;
		read (rax) ;
		auto fax = TRUE ;
		if switch_case (fax) {
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
		if switch_case (fax) {
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
		if switch_case (fax) {
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
		if switch_case (fax) {
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
		if switch_case (fax) {
			_DYNAMIC_ASSERT_ (FALSE) ;
		}
	}

	inline TextReader &operator>> (BOOL &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	void read (VAR32 &data) {
		const auto r1x = read<VAR64> () ;
		_DYNAMIC_ASSERT_ (r1x >= VAR32_MIN && r1x <= VAR32_MAX) ;
		data = VAR32 (r1x) ;
	}

	inline TextReader &operator>> (VAR32 &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	void read (VAR64 &data) {
		auto rax = REAL () ;
		read (rax) ;
		const auto r1x = BOOL (rax == REAL ('-')) ;
		if (rax == REAL ('+') || r1x)
			read (rax) ;
		compute_read_number (data ,rax) ;
		if (!r1x)
			return ;
		data = -data ;
	}

	inline TextReader &operator>> (VAR64 &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	void read (VAL32 &data) {
		const auto r1x = read<VAL64> () ;
		if switch_case (TRUE) {
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
		return _DEREF_ (this) ;
	}

	void read (VAL64 &data) {
		const auto r1x = attr () ;
		auto rax = REAL () ;
		read (rax) ;
		const auto r2x = BOOL (rax == REAL ('-')) ;
		if (rax == REAL ('+') || r2x)
			read (rax) ;
		auto fax = TRUE ;
		if switch_case (fax) {
			if (!(rax == REAL ('i')))
				discard ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('n')) ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('f')) ;
			data = VAL64_INF ;
		}
		if switch_case (fax) {
			if (!(rax == REAL ('I')))
				discard ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('N')) ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('F')) ;
			data = VAL64_INF ;
		}
		if switch_case (fax) {
			if (!(rax == REAL ('n')))
				discard ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('a')) ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('n')) ;
			data = VAL64_NAN ;
		}
		if switch_case (fax) {
			if (!(rax == REAL ('N')))
				discard ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('A')) ;
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == REAL ('N')) ;
			data = VAL64_NAN ;
		}
		if switch_case (fax) {
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
		return _DEREF_ (this) ;
	}

	template <class _ARG1 ,class _ARG2>
	void read (Array<_ARG1 ,_ARG2> &data) {
		_DEBUG_ASSERT_ (FALSE) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline TextReader &operator>> (Array<_ARG1 ,_ARG2> &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	void read (const Plain<REAL> &data) {
#pragma GCC diagnostic push
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
		auto rax = REAL () ;
		for (auto &&i : _RANGE_ (0 ,data.size ())) {
			read (rax) ;
			_DYNAMIC_ASSERT_ (rax == data.self[i]) ;
		}
#pragma GCC diagnostic pop
}

	inline TextReader &operator>> (const Plain<REAL> &data) {
		read (data) ;
		return _DEREF_ (this) ;
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
		return _DEREF_ (this) ;
	}

	template <class _ARG1 ,class _ARG2>
	void read (Buffer<_ARG1 ,_ARG2> &data) {
		for (auto &&i : _RANGE_ (0 ,data.size ()))
			read (data[i]) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline TextReader &operator>> (Buffer<_ARG1 ,_ARG2> &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	void read (Binder &data) {
		data.friend_read (_DEREF_ (this)) ;
	}

	inline TextReader &operator>> (Binder &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	void read (const PTR<void (TextReader &)> &proc) {
		const auto r1x = Function<void (TextReader &)> (proc) ;
		r1x (_DEREF_ (this)) ;
	}

	inline TextReader &operator>> (const PTR<void (TextReader &)> &proc) {
		read (proc) ;
		return _DEREF_ (this) ;
	}

	void scans () {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1 ,class... _ARGS>
	void scans (_ARG1 &list_one ,_ARGS &...list_rest) {
		read (list_one) ;
		scans (list_rest...) ;
	}

	void read (const PTR<decltype (CLS)> &) {
		reset () ;
	}

	inline TextReader &operator>> (const PTR<decltype (CLS)> &proc) {
		read (proc) ;
		return _DEREF_ (this) ;
	}

	void read (const PTR<decltype (BOM)> &) {
		template_read_bom (_NULL_<ARGV<REAL>> ()) ;
	}

	inline TextReader &operator>> (const PTR<decltype (BOM)> &proc) {
		read (proc) ;
		return _DEREF_ (this) ;
	}

	void read (const PTR<decltype (GAP)> &) {
		const auto r1x = attr () ;
		auto ris = copy () ;
		auto rax = REAL () ;
		ris >> rax ;
		while (TRUE) {
			if (!r1x.varify_space (rax))
				break ;
			_DEREF_ (this) = ris.copy () ;
			ris >> rax ;
		}
	}

	inline TextReader &operator>> (const PTR<decltype (GAP)> &proc) {
		read (proc) ;
		return _DEREF_ (this) ;
	}

	void read (const PTR<decltype (EOS)> &) {
		const auto r1x = attr () ;
		auto ris = copy () ;
		auto rax = REAL () ;
		ris.read (rax) ;
		_DYNAMIC_ASSERT_ (rax == r1x.varify_ending_item ()) ;
		_DEREF_ (this) = ris.copy () ;
	}

	inline TextReader &operator>> (const PTR<decltype (EOS)> &proc) {
		read (proc) ;
		return _DEREF_ (this) ;
	}

private:
	LENGTH next_string_size () popping {
		const auto r1x = attr () ;
		LENGTH ret = 0 ;
		auto ris = copy () ;
		auto rax = REAL () ;
		ris.read (rax) ;
		while (TRUE) {
			if (rax == r1x.varify_ending_item ())
				break ;
			if (r1x.varify_space (rax))
				break ;
			ret++ ;
			ris.read (rax) ;
		}
		return std::move (ret) ;
	}

	void compute_read_number (VAR64 &data ,REAL &top) {
		const auto r1x = attr () ;
		_DEBUG_ASSERT_ (r1x.varify_number_item (top)) ;
		auto ris = copy () ;
		data = r1x.convert_number_r (top) ;
		ris.read (top) ;
		while (TRUE) {
			if (!r1x.varify_number_item (top))
				break ;
			const auto r2x = data * r1x.varify_radix () + r1x.convert_number_r (top) ;
			_DYNAMIC_ASSERT_ (data <= r2x) ;
			data = r2x ;
			_DEREF_ (this) = ris.copy () ;
			ris.read (top) ;
		}
	}

	void compute_read_number (VAL64 &data ,REAL &top) {
		const auto r1x = attr () ;
		_DEBUG_ASSERT_ (r1x.varify_number_item (top)) ;
		auto ris = copy () ;
		while (TRUE) {
			if (r1x.convert_number_r (top) != 0)
				break ;
			_DEREF_ (this) = ris.copy () ;
			ris.read (top) ;
		}
		auto rax = ARRAY3<VAR64> {0 ,0 ,0} ;
		if switch_case (TRUE) {
			if (!r1x.varify_number_item (top))
				discard ;
			rax[0] = r1x.convert_number_r (top) ;
			_DEREF_ (this) = ris.copy () ;
			ris.read (top) ;
			while (TRUE) {
				if (!r1x.varify_number_item (top))
					break ;
				auto fax = TRUE ;
				if switch_case (fax) {
					const auto r2x = rax[0] * r1x.varify_radix () + r1x.convert_number_r (top) ;
					if (!(rax[0] < r2x))
						discard ;
					rax[0] = r2x ;
				}
				if switch_case (fax) {
					rax[1]++ ;
				}
				_DEREF_ (this) = ris.copy () ;
				ris.read (top) ;
			}
		}
		if switch_case (TRUE) {
			if (top != REAL ('.'))
				discard ;
			_DEREF_ (this) = ris.copy () ;
			ris.read (top) ;
			_DYNAMIC_ASSERT_ (r1x.varify_number_item (top)) ;
			while (TRUE) {
				if (!r1x.varify_number_item (top))
					break ;
				if switch_case (TRUE) {
					const auto r3x = rax[0] * r1x.varify_radix () + r1x.convert_number_r (top) ;
					if (rax[0] > r3x)
						discard ;
					rax[0] = r3x ;
					rax[1]-- ;
				}
				_DEREF_ (this) = ris.copy () ;
				ris.read (top) ;
			}
		}
		if switch_case (TRUE) {
			if (!(top == REAL ('e') || top == REAL ('E')))
				discard ;
			const auto r4x = ris.template read<VAR32> () ;
			rax[1] += r4x ;
			_DEREF_ (this) = ris.copy () ;
		}
		if switch_case (TRUE) {
			if (rax[0] >= 0)
				discard ;
			rax[0] = -rax[0] ;
			rax[2] = -1 ;
			if (rax[0] >= 0)
				discard ;
			rax[0] = -(rax[0] / r1x.varify_radix ()) ;
			rax[1]++ ;
		}
		const auto r5x = MathProc::ieee754_e10_e2 (rax) ;
		data = MathProc::ieee754_encode (r5x) ;
	}

	template <class _ARG1>
	void template_read_bom (const ARGV<_ARG1> &) {
		_STATIC_WARNING_ ("noop") ;
	}

	void template_read_bom (const ARGV<STRU8> &) {
		static constexpr auto M_BOM = PACK<STRU8[3]> ({
			STRU8 (0XEF) ,STRU8 (0XBB) ,STRU8 (0XBF)}) ;
		const auto r1x = attr () ;
		auto ris = copy () ;
		auto rax = STRU8 () ;
		ris >> rax ;
		if (rax != M_BOM.P1[0])
			return ;
		ris >> rax ;
		if (rax != M_BOM.P1[1])
			return ;
		ris >> rax ;
		if (rax != M_BOM.P1[2])
			return ;
		r1x.enable_endian (FALSE) ;
		_DEREF_ (this) = ris.copy () ;
	}

	void template_read_bom (const ARGV<STRU16> &) {
		static constexpr auto M_BOM = PACK<STRU16[2]> ({
			STRU16 (0XFEFF) ,STRU16 (0XFFFE)}) ;
		const auto r1x = attr () ;
		auto ris = copy () ;
		auto rax = STRU16 () ;
		ris >> rax ;
		if (!(rax == M_BOM.P1[0] || rax == M_BOM.P1[1]))
			return ;
		const auto r2x = BOOL (rax != M_BOM.P1[0]) ;
		r1x.enable_endian (r2x) ;
		_DEREF_ (this) = ris.copy () ;
	}

	void template_read_bom (const ARGV<STRU32> &) {
		static constexpr auto M_BOM = PACK<STRU32[2]> ({
			STRU32 (0X0000FEFF) ,STRU32 (0XFFFE0000)}) ;
		const auto r1x = attr () ;
		auto ris = copy () ;
		auto rax = STRU32 () ;
		ris >> rax ;
		if (!(rax == M_BOM.P1[0] || rax == M_BOM.P1[1]))
			return ;
		const auto r2x = BOOL (rax != M_BOM.P1[0]) ;
		r1x.enable_endian (r2x) ;
		_DEREF_ (this) = ris.copy () ;
	}

	void template_read_bom (const ARGV<STRW> &) {
		auto ris = copy () ;
		_CAST_<TextReader<STRUW>> (ris).template_read_bom (_NULL_<ARGV<STRUW>> ()) ;
		_DEREF_ (this) = ris.copy () ;
	}
} ;

template <class REAL>
struct TextReader<REAL>::Detail {
	template <class BASE>
	class Attribute final
		:private Proxy {
	private:
		friend TextReader ;
		BASE &mBase ;

	public:
		inline Attribute () = delete ;

		inline REAL varify_ending_item () const {
			return REAL ('\0') ;
		}

		inline void enable_endian (BOOL flag) const {
			_STATIC_ASSERT_ (!std::is_const<BASE>::value) ;
			mBase.mHeap->mEndianFlag = flag ;
		}

		inline REAL convert_endian (const REAL &item) const {
			if (!mBase.mHeap->mEndianFlag)
				return item ;
			U::BYTE_BASE_TYPE<REAL> ret ;
			auto &r1x = _CAST_<BYTE[_SIZEOF_ (REAL)]> (item) ;
			ByteReader<BYTE> (PhanBuffer<const BYTE>::make (r1x)) >> ret ;
			return std::move (_CAST_<REAL> (ret)) ;
		}

		inline VAR64 varify_radix () const {
			return 10 ;
		}

		inline LENGTH varify_val32_precision () const {
			return 6 ;
		}

		inline LENGTH varify_val64_precision () const {
			_STATIC_WARNING_ ("mark") ;
			return 13 ;
		}

		inline BOOL varify_number_item (const REAL &item) const {
			if (!(item >= REAL ('0') && item <= REAL ('9')))
				return FALSE ;
			return TRUE ;
		}

		inline VAR64 convert_number_r (const REAL &item) const {
			return VAR64 (item) - VAR64 ('0') ;
		}

		inline void enable_escape (BOOL flag) const {
			_STATIC_ASSERT_ (!std::is_const<BASE>::value) ;
			mBase.mHeap->mEscapeFlag = flag ;
		}

		inline REAL varify_escape_item () const {
			return REAL ('\\') ;
		}

		inline BOOL varify_escape_r (const REAL &item) const {
			if (!mBase.mHeap->mEscapeFlag)
				return FALSE ;
			if (item != varify_escape_item ())
				return FALSE ;
			return TRUE ;
		}

		inline void modify_escape_r (const REAL &str_a ,const REAL &str_e) const {
			_STATIC_ASSERT_ (!std::is_const<BASE>::value) ;
			_DEBUG_ASSERT_ (str_e != varify_ending_item ()) ;
			INDEX ix = mBase.mHeap->mEscapeMappingSet.map (str_a) ;
			_DEBUG_ASSERT_ (ix == VAR_NONE) ;
			ix = mBase.mHeap->mEscapeList.insert () ;
			mBase.mHeap->mEscapeMappingSet.add (str_a ,ix) ;
			mBase.mHeap->mEscapeList[ix] = str_e ;
		}

		inline REAL convert_escape_r (const REAL &str_a) const {
			INDEX ix = mBase.mHeap->mEscapeMappingSet.map (str_a) ;
			_DYNAMIC_ASSERT_ (ix != VAR_NONE) ;
			return mBase.mHeap->mEscapeList[ix] ;
		}

		inline BOOL varify_space (const REAL &item) const {
			INDEX ix = mBase.mHeap->mSpaceMappingSet.map (item) ;
			if (ix == VAR_NONE)
				return FALSE ;
			return TRUE ;
		}

		inline BOOL varify_space (const REAL &item ,VAR32 group) const {
			INDEX ix = mBase.mHeap->mSpaceMappingSet.map (item) ;
			if (ix == VAR_NONE)
				return FALSE ;
			if (mBase.mHeap->mSpaceList[ix].P2 != group)
				return FALSE ;
			return TRUE ;
		}

		inline void modify_space (const REAL &item ,VAR32 group) const {
			_STATIC_ASSERT_ (!std::is_const<BASE>::value) ;
			_DEBUG_ASSERT_ (item != varify_ending_item ()) ;
			INDEX ix = mBase.mHeap->mSpaceMappingSet.map (item) ;
			_DEBUG_ASSERT_ (ix == VAR_NONE) ;
			ix = mBase.mHeap->mSpaceList.insert () ;
			mBase.mHeap->mSpaceMappingSet.add (item ,ix) ;
			mBase.mHeap->mSpaceList[ix].P1 = item ;
			mBase.mHeap->mSpaceList[ix].P2 = group ;
		}

		inline BOOL varify_control (const REAL &item) const {
			if (!(item >= REAL (0) && item <= REAL (32)))
				if (item != REAL (127))
					return FALSE ;
			if (varify_space (item))
				return FALSE ;
			return TRUE ;
		}

	private:
		inline explicit Attribute (BASE &base)
			:mBase (base) {}
	} ;
} ;

template <class REAL>
inline void TextReader<REAL>::CLS (const ARGV<ARGC<1>> &) {}
template <class REAL>
inline void TextReader<REAL>::BOM (const ARGV<ARGC<2>> &) {}
template <class REAL>
inline void TextReader<REAL>::GAP (const ARGV<ARGC<3>> &) {}
template <class REAL>
inline void TextReader<REAL>::EOS (const ARGV<ARGC<4>> &) {}

template <class REAL>
class TextWriter {
	_STATIC_ASSERT_ (stl::is_str_xyz<REAL>::value) ;

public:
	exports class Binder
		:public Interface {
	public:
		virtual void friend_write (TextWriter &writer) const = 0 ;
	} ;

	static DEF<void (const ARGV<ARGC<1>> &)> CLS ;
	static DEF<void (const ARGV<ARGC<2>> &)> BOM ;
	static DEF<void (const ARGV<ARGC<3>> &)> GAP ;
	static DEF<void (const ARGV<ARGC<4>> &)> EOS ;

private:
	class Heap {
	private:
		friend TextWriter ;
		SharedRef<FixedBuffer<REAL>> mBuffer ;
		BOOL mEscapeFlag ;
		Deque<REAL> mEscapeList ;
		HashSet<REAL> mEscapeMappingSet ;
	} ;

private:
	template <class>
	friend class TextWriter ;
	struct Detail ;
	SharedRef<Heap> mHeap ;
	PhanBuffer<REAL> mStream ;
	INDEX mRead ;
	INDEX mWrite ;

public:
	TextWriter () {
		reset () ;
	}

	explicit TextWriter (const PhanBuffer<REAL> &stream) {
		const auto r1x = attr () ;
		mHeap = SharedRef<Heap>::make () ;
		r1x.enable_escape (FALSE) ;
		mStream = PhanBuffer<REAL>::make (stream) ;
		reset () ;
	}

	explicit TextWriter (SharedRef<FixedBuffer<REAL>> &&stream) {
		const auto r1x = attr () ;
		mHeap = SharedRef<Heap>::make () ;
		mHeap->mBuffer = std::move (stream) ;
		r1x.enable_escape (FALSE) ;
		mStream = PhanBuffer<REAL>::make (mHeap->mBuffer.self) ;
		reset () ;
	}

	DEF<typename Detail::template Attribute<TextWriter>> attr () leftvalue {
		using Attribute = typename Detail::template Attribute<TextWriter> ;
		return Attribute (_DEREF_ (this)) ;
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

	void reset (INDEX read_ ,INDEX write_) {
		_DEBUG_ASSERT_ (mHeap.exist ()) ;
		_DEBUG_ASSERT_ (read_ >= 0 && read_ < mStream.size ()) ;
		_DEBUG_ASSERT_ (write_ >= 0 && write_ < mStream.size ()) ;
		_DEBUG_ASSERT_ (read_ <= write_) ;
		mRead = read_ ;
		mWrite = write_ ;
	}

	TextWriter copy () popping {
		TextWriter ret ;
		ret.mHeap = mHeap ;
		ret.mStream = PhanBuffer<REAL>::make (mStream) ;
		ret.mRead = mRead ;
		ret.mWrite = mWrite ;
		return std::move (ret) ;
	}

	void write (const REAL &data) {
		const auto r1x = attr () ;
		auto fax = TRUE ;
		if switch_case (fax) {
			if (!r1x.varify_escape_w (data))
				discard ;
			_DYNAMIC_ASSERT_ (mWrite + 1 < mStream.size ()) ;
			mStream[mWrite] = r1x.varify_escape_item () ;
			mWrite++ ;
			const auto r2x = r1x.convert_escape_w (data) ;
			mStream[mWrite] = r2x ;
			mWrite++ ;
		}
		if switch_case (fax) {
			_DYNAMIC_ASSERT_ (mWrite < mStream.size ()) ;
			mStream[mWrite] = data ;
			mWrite++ ;
		}
	}

	inline TextWriter &operator<< (const REAL &data) {
		write (data) ;
		return _DEREF_ (this) ;
	}

	void write (const BOOL &data) {
		static constexpr auto M_TRUE = PACK<REAL[4]> ({
			REAL ('t') ,REAL ('r') ,REAL ('u') ,REAL ('e')}) ;
		static constexpr auto M_FALSE = PACK<REAL[5]> ({
			REAL ('f') ,REAL ('a') ,REAL ('l') ,REAL ('s') ,REAL ('e')}) ;
		const auto r1x = _CALL_ ([&] () {
			if (data)
				return PhanBuffer<const REAL>::make (M_TRUE.P1) ;
			return PhanBuffer<const REAL>::make (M_FALSE.P1) ;
		}) ;
		write (r1x) ;
	}

	inline TextWriter &operator<< (const BOOL &data) {
		write (data) ;
		return _DEREF_ (this) ;
	}

	void write (const PTR<const VOID> &) = delete ;

	inline TextWriter &operator<< (const PTR<const VOID> &) = delete ;

	void write (const VAR32 &data) {
		write (VAR64 (data)) ;
	}

	inline TextWriter &operator<< (const VAR32 &data) {
		write (data) ;
		return _DEREF_ (this) ;
	}

	void write (const VAR64 &data) {
		auto rax = Buffer<REAL ,ARGC<128>> () ;
		INDEX ix = rax.size () ;
		compute_write_number (data ,PhanBuffer<REAL>::make (rax) ,ix) ;
		write (PhanBuffer<const REAL>::make (PTRTOARR[&rax.self[ix]] ,(rax.size () - ix))) ;
	}

	inline TextWriter &operator<< (const VAR64 &data) {
		write (data) ;
		return _DEREF_ (this) ;
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
		if switch_case (fax) {
			if (!MathProc::is_nan (data))
				discard ;
			write (PhanBuffer<const REAL>::make (M_NAN.P1)) ;
		}
		if switch_case (fax) {
			if (!MathProc::is_infinite (data))
				discard ;
			if (!(data > 0))
				discard ;
			write (PhanBuffer<const REAL>::make (M_INF.P1)) ;
		}
		if switch_case (fax) {
			if (!MathProc::is_infinite (data))
				discard ;
			if (!(data < 0))
				discard ;
			write (PhanBuffer<const REAL>::make (M_SINF.P1)) ;
		}
		if switch_case (fax) {
			auto rax = Buffer<REAL ,ARGC<256>> () ;
			INDEX ix = rax.size () ;
			const auto r2x = r1x.varify_val32_precision () ;
			compute_write_number (data ,r2x ,PhanBuffer<REAL>::make (rax) ,ix) ;
			write (PhanBuffer<const REAL>::make (PTRTOARR[&rax.self[ix]] ,(rax.size () - ix))) ;
		}
	}

	inline TextWriter &operator<< (const VAL32 &data) {
		write (data) ;
		return _DEREF_ (this) ;
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
		if switch_case (fax) {
			if (!MathProc::is_nan (data))
				discard ;
			write (PhanBuffer<const REAL>::make (M_NAN.P1)) ;
		}
		if switch_case (fax) {
			if (!MathProc::is_infinite (data))
				discard ;
			if (!(data > 0))
				discard ;
			write (PhanBuffer<const REAL>::make (M_INF.P1)) ;
		}
		if switch_case (fax) {
			if (!MathProc::is_infinite (data))
				discard ;
			if (!(data < 0))
				discard ;
			write (PhanBuffer<const REAL>::make (M_SINF.P1)) ;
		}
		if switch_case (fax) {
			auto rax = Buffer<REAL ,ARGC<256>> () ;
			INDEX ix = rax.size () ;
			const auto r2x = r1x.varify_val64_precision () ;
			compute_write_number (data ,r2x ,PhanBuffer<REAL>::make (rax) ,ix) ;
			write (PhanBuffer<const REAL>::make (PTRTOARR[&rax.self[ix]] ,(rax.size () - ix))) ;
		}
	}

	inline TextWriter &operator<< (const VAL64 &data) {
		write (data) ;
		return _DEREF_ (this) ;
	}

	template <class _ARG1 ,class _ARG2>
	void write (const Array<_ARG1 ,_ARG2> &data) {
		_DEBUG_ASSERT_ (FALSE) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline TextWriter &operator<< (const Array<_ARG1 ,_ARG2> &data) {
		write (data) ;
		return _DEREF_ (this) ;
	}

	void write (const Plain<REAL> &data) {
#pragma GCC diagnostic push
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
		for (auto &&i : _RANGE_ (0 ,data.size ()))
			write (data.self[i]) ;
#pragma GCC diagnostic pop
}

	inline TextWriter &operator<< (const Plain<REAL> &data) {
		write (data) ;
		return _DEREF_ (this) ;
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
		return _DEREF_ (this) ;
	}

	template <class _ARG1 ,class _ARG2>
	void write (const Buffer<_ARG1 ,_ARG2> &data) {
		for (auto &&i : _RANGE_ (0 ,data.size ()))
			write (data[i]) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline TextWriter &operator<< (const Buffer<_ARG1 ,_ARG2> &data) {
		write (data) ;
		return _DEREF_ (this) ;
	}

	void write (const Binder &data) {
		data.friend_write (_DEREF_ (this)) ;
	}

	inline TextWriter &operator<< (const Binder &data) {
		write (data) ;
		return _DEREF_ (this) ;
	}

	void write (const PTR<void (TextWriter &)> &proc) {
		const auto r1x = Function<void (TextWriter &)> (proc) ;
		r1x (_DEREF_ (this)) ;
	}

	inline TextWriter &operator<< (const PTR<void (TextWriter &)> &proc) {
		write (proc) ;
		return _DEREF_ (this) ;
	}

	void prints () {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class _ARG1 ,class... _ARGS>
	void prints (const _ARG1 &list_one ,const _ARGS &...list_rest) {
		write (list_one) ;
		prints (list_rest...) ;
	}

	void write (const PTR<decltype (CLS)> &) {
		reset () ;
	}

	inline TextWriter &operator<< (const PTR<decltype (CLS)> &proc) {
		write (proc) ;
		return _DEREF_ (this) ;
	}

	void write (const PTR<decltype (BOM)> &) {
		template_write_bom (_NULL_<ARGV<REAL>> ()) ;
	}

	inline TextWriter &operator<< (const PTR<decltype (BOM)> &proc) {
		write (proc) ;
		return _DEREF_ (this) ;
	}

	void write (const PTR<decltype (GAP)> &) {
		auto wos = copy () ;
		_DYNAMIC_ASSERT_ (wos.length () + 2 < wos.size ()) ;
		wos << REAL ('\r') << REAL ('\n') ;
		_DEREF_ (this) = wos.copy () ;
	}

	inline TextWriter &operator<< (const PTR<decltype (GAP)> &proc) {
		write (proc) ;
		return _DEREF_ (this) ;
	}

	void write (const PTR<decltype (EOS)> &) {
		const auto r1x = attr () ;
		auto wos = copy () ;
		wos << r1x.varify_ending_item () ;
		_DEREF_ (this) = wos.copy () ;
	}

	inline TextWriter &operator<< (const PTR<decltype (EOS)> &proc) {
		write (proc) ;
		return _DEREF_ (this) ;
	}

private:
	void compute_write_number (const VAR64 &data ,const PhanBuffer<REAL> &out ,INDEX &out_i) {
		const auto r1x = attr () ;
		auto rax = data ;
		INDEX iw = out_i ;
		auto fax = TRUE ;
		if switch_case (fax) {
			if (!(data > 0))
				discard ;
			while (TRUE) {
				if (rax == 0)
					break ;
				out[--iw] = r1x.convert_number_w (rax % r1x.varify_radix ()) ;
				rax /= r1x.varify_radix () ;
			}
		}
		if switch_case (fax) {
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
		if switch_case (fax) {
			if (!(data == 0))
				discard ;
			out[--iw] = r1x.convert_number_w (0) ;
		}
		out_i = iw ;
	}

	void compute_write_number (const VAL64 &data ,LENGTH precision ,const PhanBuffer<REAL> &out ,INDEX &out_i) {
		const auto r1x = attr () ;
		INDEX iw = out_i ;
		const auto r2x = MathProc::ieee754_decode (data) ;
		auto rax = MathProc::ieee754_e2_e10 (r2x) ;
		const auto r3x = log_of_number (rax[0] ,r1x.varify_radix ()) ;
		if switch_case (TRUE) {
			const auto r4x = r3x - precision ;
			for (auto &&i : _RANGE_ (0 ,r4x - 1)) {
				rax[0] /= r1x.varify_radix () ;
				rax[1]++ ;
				_STATIC_UNUSED_ (i) ;
			}
			if (r4x <= 0)
				discard ;
			rax[0] = MathProc::round (rax[0] ,r1x.varify_radix ()) / r1x.varify_radix () ;
			rax[1]++ ;
		}
		const auto r5x = log_of_number (rax[0] ,r1x.varify_radix ()) ;
		auto fax = TRUE ;
		if switch_case (fax) {
			//@info: case '0'
			if (!(rax[0] == 0))
				discard ;
			out[--iw] = r1x.convert_number_w (0) ;
		}
		if switch_case (fax) {
			//@info: case 'x.xxxExxx'
			const auto r6x = r5x - 1 + rax[1] ;
			if (!(_ABS_ (r6x) >= precision))
				discard ;
			compute_write_number (r6x ,out ,iw) ;
			if (r6x > 0)
				out[--iw] = REAL ('+') ;
			out[--iw] = REAL ('e') ;
			const auto r7x = _MAX_ ((r5x - 1 - precision) ,VAR_ZERO) ;
			for (auto &&i : _RANGE_ (0 ,r7x)) {
				rax[0] /= r1x.varify_radix () ;
				_STATIC_UNUSED_ (i) ;
			}
			INDEX ix = iw - 1 ;
			for (auto &&i : _RANGE_ (r7x ,r5x - 1)) {
				out[--iw] = r1x.convert_number_w (rax[0] % r1x.varify_radix ()) ;
				iw += _EBOOL_ (out[ix] == r1x.convert_number_w (0)) ;
				rax[0] /= r1x.varify_radix () ;
				_STATIC_UNUSED_ (i) ;
			}
			out[--iw] = REAL ('.') ;
			iw += _EBOOL_ (out[ix] == REAL ('.')) ;
			out[--iw] = r1x.convert_number_w (rax[0] % r1x.varify_radix ()) ;
			rax[0] /= r1x.varify_radix () ;
		}
		if switch_case (fax) {
			//@info: case 'xxx000'
			if (!(rax[1] >= 0))
				discard ;
			for (auto &&i : _RANGE_ (0 ,LENGTH (rax[1]))) {
				out[--iw] = r1x.convert_number_w (0) ;
				_STATIC_UNUSED_ (i) ;
			}
			for (auto &&i : _RANGE_ (0 ,r5x)) {
				out[--iw] = r1x.convert_number_w (rax[0] % r1x.varify_radix ()) ;
				rax[0] /= r1x.varify_radix () ;
				_STATIC_UNUSED_ (i) ;
			}
		}
		if switch_case (fax) {
			//@info: case 'xxx.xxx'
			if (!(rax[1] >= 1 - r5x))
				discard ;
			if (!(rax[1] < 0))
				discard ;
			const auto r8x = _MAX_ (LENGTH (-rax[1] - precision) ,VAR_ZERO) ;
			for (auto &&i : _RANGE_ (0 ,r8x)) {
				rax[0] /= r1x.varify_radix () ;
				_STATIC_UNUSED_ (i) ;
			}
			INDEX ix = iw - 1 ;
			for (auto &&i : _RANGE_ (r8x ,LENGTH (-rax[1]))) {
				out[--iw] = r1x.convert_number_w (rax[0] % r1x.varify_radix ()) ;
				iw += _EBOOL_ (out[ix] == r1x.convert_number_w (0)) ;
				rax[0] /= r1x.varify_radix () ;
				_STATIC_UNUSED_ (i) ;
			}
			out[--iw] = REAL ('.') ;
			iw += _EBOOL_ (out[ix] == REAL ('.')) ;
			for (auto &&i : _RANGE_ (0 ,LENGTH (r5x + rax[1]))) {
				out[--iw] = r1x.convert_number_w (rax[0] % r1x.varify_radix ()) ;
				rax[0] /= r1x.varify_radix () ;
				_STATIC_UNUSED_ (i) ;
			}
		}
		if switch_case (fax) {
			//@info: case '0.000xxx'
			if (!(rax[1] < 1 - r5x))
				discard ;
			if (!(rax[1] < 0))
				discard ;
			const auto r9x = _MAX_ (LENGTH (-rax[1] - precision) ,VAR_ZERO) ;
			for (auto &&i : _RANGE_ (0 ,r9x)) {
				rax[0] /= r1x.varify_radix () ;
				_STATIC_UNUSED_ (i) ;
			}
			INDEX ix = iw - 1 ;
			for (auto &&i : _RANGE_ (r9x ,r5x)) {
				out[--iw] = r1x.convert_number_w (rax[0] % r1x.varify_radix ()) ;
				iw += _EBOOL_ (out[ix] == r1x.convert_number_w (0)) ;
				rax[0] /= r1x.varify_radix () ;
				_STATIC_UNUSED_ (i) ;
			}
			for (auto &&i : _RANGE_ (_MAX_ (r9x ,r5x) ,LENGTH (-rax[1]))) {
				out[--iw] = r1x.convert_number_w (0) ;
				iw += _EBOOL_ (out[ix] == r1x.convert_number_w (0)) ;
				_STATIC_UNUSED_ (i) ;
			}
			out[--iw] = REAL ('.') ;
			iw += _EBOOL_ (out[ix] == REAL ('.')) ;
			out[--iw] = r1x.convert_number_w (0) ;
		}
		if (rax[2] != 0)
			out[--iw] = REAL ('-') ;
		out_i = iw ;
	}

	LENGTH log_of_number (VAR64 val ,LENGTH radix) const {
		LENGTH ret = 0 ;
		auto rax = VAR64 (1) ;
		while (TRUE) {
			if (rax > val)
				break ;
			ret++ ;
			rax *= radix ;
		}
		return std::move (ret) ;
	}
	
	template <class _ARG1>
	void template_write_bom (const ARGV<_ARG1> &) {
		_STATIC_WARNING_ ("noop") ;
	}

	void template_write_bom (const ARGV<STRU8> &) {
		static constexpr auto M_BOM = PACK<STRU8[3]> ({
			STRU8 (0XEF) ,STRU8 (0XBB) ,STRU8 (0XBF)}) ;
		auto wos = copy () ;
		wos << PhanBuffer<const STRU8>::make (M_BOM.P1) ;
		_DEREF_ (this) = wos.copy () ;
	}

	void template_write_bom (const ARGV<STRU16> &) {
		static constexpr auto M_BOM = PACK<STRU16[1]> ({
			STRU16 (0XFEFF)}) ;
		auto wos = copy () ;
		wos << PhanBuffer<const STRU16>::make (M_BOM.P1) ;
		_DEREF_ (this) = wos.copy () ;
	}

	void template_write_bom (const ARGV<STRU32> &) {
		static constexpr auto M_BOM = PACK<STRU32[1]> ({
			STRU32 (0X0000FEFF)}) ;
		auto wos = copy () ;
		wos << PhanBuffer<const STRU32>::make (M_BOM.P1) ;
		_DEREF_ (this) = wos.copy () ;
	}

	void template_write_bom (const ARGV<STRW> &) {
		auto wos = copy () ;
		_CAST_<TextWriter<STRUW>> (wos).template_write_bom (_NULL_<ARGV<STRUW>> ()) ;
		_DEREF_ (this) = wos.copy () ;
	}
} ;

template <class REAL>
struct TextWriter<REAL>::Detail {
	template <class BASE>
	class Attribute final
		:private Proxy {
	private:
		friend TextWriter ;
		BASE &mBase ;

	public:
		inline Attribute () = delete ;

		inline REAL varify_ending_item () const {
			return REAL ('\0') ;
		}

		inline VAR64 varify_radix () const {
			return 10 ;
		}

		inline LENGTH varify_val32_precision () const {
			return 6 ;
		}

		inline LENGTH varify_val64_precision () const {
			_STATIC_WARNING_ ("mark") ;
			return 13 ;
		}

		inline BOOL varify_number_item (const REAL &item) const {
			if (!(item >= REAL ('0') && item <= REAL ('9')))
				return FALSE ;
			return TRUE ;
		}

		inline REAL convert_number_w (VAR64 number) const {
			return REAL (VAR64 ('0') + number) ;
		}

		inline void enable_escape (BOOL flag) const {
			mBase.mHeap->mEscapeFlag = flag ;
		}

		inline REAL varify_escape_item () const {
			return REAL ('\\') ;
		}

		inline BOOL varify_escape_w (const REAL &key) const {
			if (!mBase.mHeap->mEscapeFlag)
				return FALSE ;
			if (mBase.mHeap->mEscapeMappingSet.find (key) == VAR_NONE)
				return FALSE ;
			return TRUE ;
		}

		inline void modify_escape_w (const REAL &str_a ,const REAL &str_e) const {
			_DEBUG_ASSERT_ (str_a != varify_ending_item ()) ;
			INDEX ix = mBase.mHeap->mEscapeMappingSet.map (str_e) ;
			_DEBUG_ASSERT_ (ix == VAR_NONE) ;
			ix = mBase.mHeap->mEscapeList.insert () ;
			mBase.mHeap->mEscapeMappingSet.add (str_e ,ix) ;
			mBase.mHeap->mEscapeList[ix] = str_a ;
		}

		inline REAL convert_escape_w (const REAL &str_e) const {
			INDEX ix = mBase.mHeap->mEscapeMappingSet.map (str_e) ;
			_DYNAMIC_ASSERT_ (ix != VAR_NONE) ;
			return mBase.mHeap->mEscapeList[ix] ;
		}

		inline BOOL varify_space (const REAL &item) const {
			if (!(item == REAL ('\r') || item == REAL ('\n')))
				return FALSE ;
			return TRUE ;
		}

		inline BOOL varify_control (const REAL &item) const {
			if (!(item >= REAL (0) && item <= REAL (32)))
				if (item != REAL (127))
					return FALSE ;
			if (varify_space (item))
				return FALSE ;
			return TRUE ;
		}

	private:
		inline explicit Attribute (BASE &base)
			:mBase (base) {}
	} ;
} ;

template <class REAL>
inline void TextWriter<REAL>::CLS (const ARGV<ARGC<1>> &) {}
template <class REAL>
inline void TextWriter<REAL>::BOM (const ARGV<ARGC<2>> &) {}
template <class REAL>
inline void TextWriter<REAL>::GAP (const ARGV<ARGC<3>> &) {}
template <class REAL>
inline void TextWriter<REAL>::EOS (const ARGV<ARGC<4>> &) {}

class RegularReader {
public:
	static DEF<void (const ARGV<ARGC<1>> &)> HINT_IDENTIFIER ;
	static DEF<void (const ARGV<ARGC<2>> &)> HINT_VALUE ;
	static DEF<void (const ARGV<ARGC<3>> &)> HINT_STRING ;
	static DEF<void (const ARGV<ARGC<4>> &)> HINT_NEWGAP ;
	static DEF<void (const ARGV<ARGC<5>> &)> HINT_NEWLINE ;
	static DEF<void (const ARGV<ARGC<6>> &)> SKIP_GAP ;
	static DEF<void (const ARGV<ARGC<7>> &)> SKIP_GAP_SPACE ;
	static DEF<void (const ARGV<ARGC<8>> &)> SKIP_GAP_ENDLINE ;
	static DEF<void (const ARGV<ARGC<9>> &)> SKIP_LINE ;

private:
	TextReader<STRU8> mShadowReader ;
	PhanRef<TextReader<STRU8>> mReader ;
	Array<STRU8> mCache ;
	INDEX mPeek ;
	BOOL mHintStringTextFlag ;
	LENGTH mHintNextTextSize ;

public:
	RegularReader () {
		mPeek = 0 ;
		mHintStringTextFlag = FALSE ;
		mHintNextTextSize = 0 ;
	}

	explicit RegularReader (const PhanRef<TextReader<STRU8>> &reader ,LENGTH ll_len) {
		_DEBUG_ASSERT_ (reader.exist ()) ;
		mReader = PhanRef<TextReader<STRU8>>::make (reader) ;
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

	RegularReader copy () popping {
		return RegularReader (mReader->copy () ,mCache ,mPeek) ;
	}

	const STRU8 &get (INDEX index) const leftvalue {
		_DEBUG_ASSERT_ (index >= 0 && index < mCache.length ()) ;
		_DEBUG_ASSERT_ (mPeek >= 0 && mPeek < mCache.length ()) ;
		return mCache[(mPeek + index) % mCache.length ()] ;
	}

	inline const STRU8 &operator[] (INDEX index) const leftvalue {
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
#pragma GCC diagnostic push
#ifdef __CSC_COMPILER_GNUC__
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
		for (auto &&i : _RANGE_ (0 ,data.size ())) {
			_DYNAMIC_ASSERT_ (get (0) == data.self[i]) ;
			read () ;
		}
#pragma GCC diagnostic pop
}

	inline RegularReader &operator>> (const Plain<STRU8> &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

	void read (const PTR<decltype (HINT_IDENTIFIER)> &) {
		mHintStringTextFlag = FALSE ;
		mHintNextTextSize = next_identifier_size () ;
	}

	inline RegularReader &operator>> (const PTR<decltype (HINT_IDENTIFIER)> &) {
		read (HINT_IDENTIFIER) ;
		return _DEREF_ (this) ;
	}

	void read (const PTR<decltype (HINT_VALUE)> &) {
		mHintStringTextFlag = FALSE ;
		mHintNextTextSize = next_value_size () ;
	}

	inline RegularReader &operator>> (const PTR<decltype (HINT_VALUE)> &) {
		read (HINT_VALUE) ;
		return _DEREF_ (this) ;
	}

	void read (const PTR<decltype (HINT_STRING)> &) {
		mHintStringTextFlag = TRUE ;
		mHintNextTextSize = next_string_size () ;
	}

	inline RegularReader &operator>> (const PTR<decltype (HINT_STRING)> &) {
		read (HINT_STRING) ;
		return _DEREF_ (this) ;
	}

	void read (const PTR<decltype (HINT_NEWGAP)> &) {
		mHintStringTextFlag = FALSE ;
		mHintNextTextSize = next_newgap_text_size () ;
	}

	inline RegularReader &operator>> (const PTR<decltype (HINT_NEWGAP)> &) {
		read (HINT_NEWGAP) ;
		return _DEREF_ (this) ;
	}

	void read (const PTR<decltype (HINT_NEWLINE)> &) {
		mHintStringTextFlag = FALSE ;
		mHintNextTextSize = next_newline_text_size () ;
	}

	inline RegularReader &operator>> (const PTR<decltype (HINT_NEWLINE)> &) {
		read (HINT_NEWLINE) ;
		return _DEREF_ (this) ;
	}

	void read (const PTR<decltype (SKIP_GAP)> &) {
		const auto r1x = mReader->attr () ;
		while (TRUE) {
			if (!r1x.varify_space (get (0)))
				break ;
			read () ;
		}
	}

	inline RegularReader &operator>> (const PTR<decltype (SKIP_GAP)> &) {
		read (SKIP_GAP) ;
		return _DEREF_ (this) ;
	}

	void read (const PTR<decltype (SKIP_GAP_SPACE)> &) {
		const auto r1x = mReader->attr () ;
		while (TRUE) {
			if (!r1x.varify_space (get (0) ,1))
				break ;
			read () ;
		}
	}

	inline RegularReader &operator>> (const PTR<decltype (SKIP_GAP_SPACE)> &) {
		read (SKIP_GAP_SPACE) ;
		return _DEREF_ (this) ;
	}

	void read (const PTR<decltype (SKIP_GAP_ENDLINE)> &) {
		const auto r1x = mReader->attr () ;
		while (TRUE) {
			if (!r1x.varify_space (get (0) ,2))
				break ;
			read () ;
		}
	}

	inline RegularReader &operator>> (const PTR<decltype (SKIP_GAP_ENDLINE)> &) {
		read (SKIP_GAP_ENDLINE) ;
		return _DEREF_ (this) ;
	}

	void read (const PTR<decltype (SKIP_LINE)> &) {
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

	inline RegularReader &operator>> (const PTR<decltype (SKIP_LINE)> &) {
		read (SKIP_LINE) ;
		return _DEREF_ (this) ;
	}

	void read (String<STRU8> &data) {
		const auto r1x = mReader->attr () ;
		const auto r2x = _EXCHANGE_ (mHintStringTextFlag ,FALSE) ;
		const auto r3x = _EXCHANGE_ (mHintNextTextSize ,VAR_ZERO) ;
		if (data.size () < r3x)
			data = String<STRU8> (r3x) ;
		data.clear () ;
		auto rax = STRU8 () ;
		if switch_case (TRUE) {
			if (!r2x)
				discard ;
			_DYNAMIC_ASSERT_ (get (0) == STRU8 ('\"')) ;
			read () ;
		}
		for (auto &&i : _RANGE_ (0 ,r3x)) {
			auto fax = TRUE ;
			if switch_case (fax) {
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
			if switch_case (fax) {
				const auto r5x = r1x.varify_control (rax) ;
				_DYNAMIC_ASSERT_ (!r5x) ;
				data[i] = rax ;
			}
		}
		if switch_case (TRUE) {
			if (!r2x)
				discard ;
			_DYNAMIC_ASSERT_ (get (0) == STRU8 ('\"')) ;
			read () ;
		}
	}

	inline RegularReader &operator>> (String<STRU8> &data) {
		read (data) ;
		return _DEREF_ (this) ;
	}

private:
	explicit RegularReader (TextReader<STRU8> &&reader ,const Array<STRU8> &cache ,INDEX peek) {
		mShadowReader = std::move (reader) ;
		mReader = PhanRef<TextReader<STRU8>>::make (mShadowReader) ;
		mCache = cache ;
		mPeek = peek ;
		mHintStringTextFlag = FALSE ;
		mHintNextTextSize = 0 ;
	}

private:
	LENGTH next_identifier_size () popping {
		LENGTH ret = 0 ;
		auto ris = copy () ;
		while (TRUE) {
			const auto r1x = BOOL (ris[0] >= STRU8 ('A') && ris[0] <= STRU8 ('Z')) ;
			const auto r2x = BOOL (ris[0] >= STRU8 ('a') && ris[0] <= STRU8 ('z')) ;
			const auto r3x = BOOL (ris[0] == STRU8 ('_')) ;
			if (ret == 0)
				_DYNAMIC_ASSERT_ (r1x || r2x || r3x) ;
			if (!r1x && !r2x && !r3x)
				if (!(ris[0] >= STRU8 ('0') && ris[0] <= STRU8 ('9')))
					if (!(ris[0] == STRU8 ('-') || ris[0] == STRU8 ('.') || ris[0] == STRU8 (':')))
						break ;
			ris++ ;
			ret++ ;
		}
		return std::move (ret) ;
	}

	LENGTH next_value_size () popping {
		LENGTH ret = 0 ;
		auto ris = copy () ;
		if switch_case (TRUE) {
			if (!(ris[0] == STRU8 ('+') || ris[0] == STRU8 ('-')))
				discard ;
			ris++ ;
			ret++ ;
		}
		const auto r1x = ris[0] ;
		_DYNAMIC_ASSERT_ (r1x >= STRU8 ('0') && r1x <= STRU8 ('9')) ;
		ris++ ;
		ret++ ;
		while (TRUE) {
			if (r1x == STRU8 ('0'))
				break ;
			if (!(ris[0] >= STRU8 ('0') && ris[0] <= STRU8 ('9')))
				break ;
			ris++ ;
			ret++ ;
		}
		if switch_case (TRUE) {
			if (ris[0] != STRU8 ('.'))
				discard ;
			ris++ ;
			ret++ ;
			while (TRUE) {
				if (!(ris[0] >= STRU8 ('0') && ris[0] <= STRU8 ('9')))
					break ;
				ris++ ;
				ret++ ;
			}
		}
		if switch_case (TRUE) {
			if (!(ris[0] == STRU8 ('e') || ris[0] == STRU8 ('E')))
				discard ;
			ris++ ;
			ret++ ;
			if switch_case (TRUE) {
				if (!(ris[0] == STRU8 ('+') || ris[0] == STRU8 ('-')))
					discard ;
				ris++ ;
				ret++ ;
			}
			_DYNAMIC_ASSERT_ (ris[0] >= STRU8 ('0') && ris[0] <= STRU8 ('9')) ;
			ris++ ;
			ret++ ;
			while (TRUE) {
				if (!(ris[0] >= STRU8 ('0') && ris[0] <= STRU8 ('9')))
					break ;
				ris++ ;
				ret++ ;
			}
		}
		return std::move (ret) ;
	}

	LENGTH next_string_size () popping {
		const auto r1x = mReader->attr () ;
		LENGTH ret = 0 ;
		auto ris = copy () ;
		auto rax = STRU8 () ;
		_DYNAMIC_ASSERT_ (ris[0] == STRU8 ('\"')) ;
		ris++ ;
		while (TRUE) {
			if (ris[0] == STRU8 ('\0'))
				break ;
			if (ris[0] == STRU8 ('\"'))
				break ;
			auto fax = TRUE ;
			if switch_case (fax) {
				rax = ris[0] ;
				ris++ ;
				if (!(rax == r1x.varify_escape_item ()))
					discard ;
				rax = ris[0] ;
				ris++ ;
				rax = r1x.convert_escape_r (rax) ;
				ret++ ;
			}
			if switch_case (fax) {
				const auto r2x = r1x.varify_control (rax) ;
				_DYNAMIC_ASSERT_ (!r2x) ;
				ret++ ;
			}
		}
		_DYNAMIC_ASSERT_ (ris[0] == STRU8 ('\"')) ;
		ris++ ;
		return std::move (ret) ;
	}

	LENGTH next_newgap_text_size () popping {
		LENGTH ret = 0 ;
		auto ris = copy () ;
		const auto r1x = mReader->attr () ;
		while (TRUE) {
			if (ris[0] == r1x.varify_ending_item ())
				break ;
			if (r1x.varify_space (ris[0]))
				break ;
			_DYNAMIC_ASSERT_ (!r1x.varify_control (ris[0])) ;
			ris++ ;
			ret++ ;
		}
		return std::move (ret) ;
	}

	LENGTH next_newline_text_size () popping {
		LENGTH ret = 0 ;
		auto ris = copy () ;
		const auto r1x = mReader->attr () ;
		while (TRUE) {
			if (ris[0] == r1x.varify_ending_item ())
				break ;
			if (r1x.varify_space (ris[0] ,2))
				break ;
			_DYNAMIC_ASSERT_ (!r1x.varify_control (ris[0])) ;
			ris++ ;
			ret++ ;
		}
		return std::move (ret) ;
	}
} ;

inline void RegularReader::HINT_IDENTIFIER (const ARGV<ARGC<1>> &) {}
inline void RegularReader::HINT_VALUE (const ARGV<ARGC<2>> &) {}
inline void RegularReader::HINT_STRING (const ARGV<ARGC<3>> &) {}
inline void RegularReader::HINT_NEWGAP (const ARGV<ARGC<4>> &) {}
inline void RegularReader::HINT_NEWLINE (const ARGV<ARGC<5>> &) {}
inline void RegularReader::SKIP_GAP (const ARGV<ARGC<6>> &) {}
inline void RegularReader::SKIP_GAP_SPACE (const ARGV<ARGC<7>> &) {}
inline void RegularReader::SKIP_GAP_ENDLINE (const ARGV<ARGC<8>> &) {}
inline void RegularReader::SKIP_LINE (const ARGV<ARGC<9>> &) {}
} ;