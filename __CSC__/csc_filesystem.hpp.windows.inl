﻿#pragma once

#ifndef __CSC_FILESYSTEM__
#error "∑(っ°Д° ;)っ : require 'csc_filesystem.hpp'"
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

#ifndef _INC_WINDOWS
#error "∑(っ°Д° ;)っ : require 'Windows.h'"
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
using ::HANDLE ;
using ::WIN32_FIND_DATA ;
using ::MEMORY_BASIC_INFORMATION ;

using ::CreateFile ;
using ::CloseHandle ;
using ::GetFileSize ;
using ::ReadFile ;
using ::WriteFile ;
using ::CreateFileMapping ;
using ::MapViewOfFile ;
using ::UnmapViewOfFile ;
} ;

inline exports AutoBuffer<BYTE> FileSystemProc::load_file (const String<STR> &file) side_effects {
	const auto r1x = UniqueRef<api::HANDLE> ([&] (api::HANDLE &me) {
		me = api::CreateFile (file.raw ().self ,GENERIC_READ ,FILE_SHARE_READ ,NULL ,OPEN_EXISTING ,FILE_ATTRIBUTE_NORMAL ,NULL) ;
		if (me == INVALID_HANDLE_VALUE)
			me = NULL ;
		_DYNAMIC_ASSERT_ (me != NULL) ;
	} ,[] (api::HANDLE &me) {
		api::CloseHandle (me) ;
	}) ;
	const auto r2x = LENGTH (api::GetFileSize (r1x.self ,NULL)) ;
	_DYNAMIC_ASSERT_ (r2x >= 0 && r2x < VAR32_MAX) ;
	AutoBuffer<BYTE> ret = AutoBuffer<BYTE> (r2x) ;
	auto rax = VARY () ;
	rax = VARY (0) ;
	const auto r3x = api::ReadFile (r1x.self ,ret.self ,VARY (r2x) ,DEPTR[rax] ,NULL) ;
	_DYNAMIC_ASSERT_ (r3x) ;
	return _MOVE_ (ret) ;
}

inline exports void FileSystemProc::load_file (const String<STR> &file ,const PhanBuffer<BYTE> &data) {
	const auto r1x = UniqueRef<api::HANDLE> ([&] (api::HANDLE &me) {
		me = api::CreateFile (file.raw ().self ,GENERIC_READ ,FILE_SHARE_READ ,NULL ,OPEN_EXISTING ,FILE_ATTRIBUTE_NORMAL ,NULL) ;
		if (me == INVALID_HANDLE_VALUE)
			me = NULL ;
		_DYNAMIC_ASSERT_ (me != NULL) ;
	} ,[] (api::HANDLE &me) {
		api::CloseHandle (me) ;
	}) ;
	const auto r2x = LENGTH (api::GetFileSize (r1x.self ,NULL)) ;
	_DYNAMIC_ASSERT_ (r2x > 0 && r2x <= data.size ()) ;
	auto rax = VARY () ;
	rax = VARY (0) ;
	const auto r3x = api::ReadFile (r1x.self ,data.self ,VARY (r2x) ,DEPTR[rax] ,NULL) ;
	_DYNAMIC_ASSERT_ (r3x) ;
	BasicProc::mem_fill (PTRTOARR[DEPTR[data.self[r2x]]] ,(data.size () - r2x) ,BYTE (0X00)) ;
}

inline exports void FileSystemProc::save_file (const String<STR> &file ,const PhanBuffer<const BYTE> &data) {
	_DEBUG_ASSERT_ (data.size () < VAR32_MAX) ;
	const auto r1x = UniqueRef<api::HANDLE> ([&] (api::HANDLE &me) {
		me = api::CreateFile (file.raw ().self ,GENERIC_WRITE ,0 ,NULL ,CREATE_ALWAYS ,FILE_ATTRIBUTE_NORMAL ,NULL) ;
		if (me == INVALID_HANDLE_VALUE)
			me = NULL ;
		_DYNAMIC_ASSERT_ (me != NULL) ;
	} ,[] (api::HANDLE &me) {
		api::CloseHandle (me) ;
	}) ;
	auto rax = VARY () ;
	rax = VARY (0) ;
	const auto r2x = api::WriteFile (r1x.self ,data.self ,VARY (data.size ()) ,DEPTR[rax] ,NULL) ;
	_DYNAMIC_ASSERT_ (r2x) ;
}

inline exports PhanBuffer<const BYTE> FileSystemProc::load_assert_file (const FLAG &resource) side_effects {
	const auto r1x = FindResource (NULL ,MAKEINTRESOURCE (resource) ,_PCSTR_ ("BIN")) ;
	_DYNAMIC_ASSERT_ (r1x != NULL) ;
	const auto r2x = LoadResource (NULL ,r1x) ;
	_DYNAMIC_ASSERT_ (r2x != NULL) ;
	const auto r3x = LockResource (r2x) ;
	_DYNAMIC_ASSERT_ (r3x != NULL) ;
	const auto r4x = LENGTH (SizeofResource (NULL ,r1x)) ;
	_DYNAMIC_ASSERT_ (r4x >= 0) ;
	const auto r5x = _POINTER_CAST_ (ARGV<ARR<BYTE>>::null ,r3x) ;
	return PhanBuffer<const BYTE>::make (DEREF[r5x] ,r4x) ;
}

inline exports BOOL FileSystemProc::find_file (const String<STR> &file) side_effects {
	const auto r1x = GetFileAttributes (file.raw ().self) ;
	if (r1x == INVALID_FILE_ATTRIBUTES)
		return FALSE ;
	if ((r1x & FILE_ATTRIBUTE_DIRECTORY) != 0)
		return FALSE ;
	return TRUE ;
}

inline exports void FileSystemProc::erase_file (const String<STR> &file) {
	DeleteFile (file.raw ().self) ;
}

inline exports void FileSystemProc::copy_file (const String<STR> &dst_file ,const String<STR> &src_file) {
	const auto r1x = FileSystemProc::find_file (dst_file) ;
	_DYNAMIC_ASSERT_ (!r1x) ;
	CopyFile (src_file.raw ().self ,dst_file.raw ().self ,TRUE) ;
}

inline exports void FileSystemProc::move_file (const String<STR> &dst_file ,const String<STR> &src_file) {
	const auto r1x = FileSystemProc::find_file (dst_file) ;
	_DYNAMIC_ASSERT_ (!r1x) ;
	MoveFile (src_file.raw ().self ,dst_file.raw ().self) ;
}

inline exports void FileSystemProc::link_file (const String<STR> &dst_file ,const String<STR> &src_file) {
	const auto r1x = FileSystemProc::find_file (dst_file) ;
	_DYNAMIC_ASSERT_ (!r1x) ;
	CreateHardLink (dst_file.raw ().self ,src_file.raw ().self ,NULL) ;
}

inline exports BOOL FileSystemProc::identical_file (const String<STR> &file1 ,const String<STR> &file2) side_effects {
	auto rax = ARRAY2<BY_HANDLE_FILE_INFORMATION> () ;
	const auto r1x = UniqueRef<api::HANDLE> ([&] (api::HANDLE &me) {
		me = api::CreateFile (file1.raw ().self ,GENERIC_READ ,FILE_SHARE_READ ,NULL ,OPEN_EXISTING ,FILE_ATTRIBUTE_NORMAL ,NULL) ;
		if (me == INVALID_HANDLE_VALUE)
			me = NULL ;
	} ,[] (api::HANDLE &me) {
		if (me == NULL)
			return ;
		api::CloseHandle (me) ;
	}) ;
	_ZERO_ (rax[0]) ;
	const auto r2x = GetFileInformationByHandle (r1x.self ,DEPTR[rax[0]]) ;
	if (r2x == 0)
		return FALSE ;
	if (rax[0].nNumberOfLinks == 0)
		return FALSE ;
	const auto r3x = UniqueRef<api::HANDLE> ([&] (api::HANDLE &me) {
		me = api::CreateFile (file2.raw ().self ,GENERIC_READ ,FILE_SHARE_READ ,NULL ,OPEN_EXISTING ,FILE_ATTRIBUTE_NORMAL ,NULL) ;
		if (me == INVALID_HANDLE_VALUE)
			me = NULL ;
	} ,[] (api::HANDLE &me) {
		if (me == NULL)
			return ;
		api::CloseHandle (me) ;
	}) ;
	_ZERO_ (rax[1]) ;
	const auto r4x = GetFileInformationByHandle (r3x.self ,DEPTR[rax[1]]) ;
	if (r4x == 0)
		return FALSE ;
	if (rax[1].nNumberOfLinks == 0)
		return FALSE ;
	if (rax[0].dwVolumeSerialNumber != rax[1].dwVolumeSerialNumber)
		return FALSE ;
	if (rax[0].nFileIndexHigh != rax[1].nFileIndexHigh)
		return FALSE ;
	if (rax[0].nFileIndexLow != rax[1].nFileIndexLow)
		return FALSE ;
	return TRUE ;
}

inline exports String<STR> FileSystemProc::parse_path_name (const String<STR> &file) {
	String<STR> ret = String<STR> (DEFAULT_FILEPATH_SIZE::value) ;
	const auto r1x = file.length () ;
	const auto r2x = file.raw () ;
	const auto r3x = BasicProc::mem_rchr (r2x.self ,r1x ,STR ('\\')) ;
	const auto r4x = BasicProc::mem_rchr (r2x.self ,r1x ,STR ('/')) ;
	const auto r5x = MathProc::maxof (r3x ,r4x ,VAR_ZERO) ;
	BasicProc::mem_copy (ret.raw ().self ,r2x.self ,r5x) ;
	return _MOVE_ (ret) ;
}

inline exports String<STR> FileSystemProc::parse_file_name (const String<STR> &file) {
	String<STR> ret = String<STR> (DEFAULT_FILEPATH_SIZE::value) ;
	const auto r1x = file.length () ;
	const auto r2x = file.raw () ;
	const auto r3x = BasicProc::mem_rchr (r2x.self ,r1x ,STR ('\\')) ;
	const auto r4x = BasicProc::mem_rchr (r2x.self ,r1x ,STR ('/')) ;
	const auto r5x = MathProc::maxof (r3x ,r4x) + 1 ;
	BasicProc::mem_copy (ret.raw ().self ,PTRTOARR[DEPTR[r2x.self[r5x]]] ,(r1x - r5x)) ;
	return _MOVE_ (ret) ;
}

inline exports Deque<String<STR>> FileSystemProc::decouple_path_name (const String<STR> &file) {
	Deque<String<STR>> ret ;
	if switch_once (TRUE) {
		if (file.empty ())
			discard ;
		auto rax = TextReader<STR> (file.raw ()) ;
		const auto r2x = rax.attr () ;
		r2x.modify_space (STR ('\\') ,0) ;
		r2x.modify_space (STR ('/') ,0) ;
		auto rbx = STR () ;
		INDEX ix = ret.insert () ;
		rax.share () >> rbx ;
		if (r2x.varify_space (rbx))
			rax >> rbx ;
		while (TRUE) {
			rax >> ret[ix] ;
			if (ret[ix].empty ())
				break ;
			ix = ret.insert () ;
			rax >> rbx ;
			if (rbx == r2x.varify_ending_item ())
				break ;
			_DYNAMIC_ASSERT_ (r2x.varify_space (rbx)) ;
		}
		ret.pop () ;
		rax >> TextReader<STR>::EOS ;
	}
	return _MOVE_ (ret) ;
}

inline exports String<STR> FileSystemProc::working_path () {
	String<STR> ret = String<STR> (DEFAULT_FILEPATH_SIZE::value) ;
	GetCurrentDirectory (VARY (ret.size ()) ,ret.raw ().self) ;
	ret += _PCSTR_ ("\\") ;
	return _MOVE_ (ret) ;
}

class FileSystemStaticProc
	:private Wrapped<> {
public:
	imports Deque<INDEX> static_relative_path_name (const Deque<String<STR>> &path_name) ;
} ;

inline exports Deque<INDEX> FileSystemStaticProc::static_relative_path_name (const Deque<String<STR>> &path_name) {
	Deque<INDEX> ret = Deque<INDEX> (path_name.length ()) ;
	for (auto &&i : _RANGE_ (0 ,path_name.length ())) {
		INDEX ix = path_name.access (i) ;
		if (path_name[ix] == _PCSTR_ ("."))
			continue ;
		auto fax = TRUE ;
		if switch_once (fax) {
			if (ret.empty ())
				discard ;
			if (!(path_name[ix] == _PCSTR_ ("..")))
				discard ;
			if (!(path_name[ret[ret.tail ()]] != _PCSTR_ ("..")))
				discard ;
			ret.pop () ;
		}
		if switch_once (fax) {
			ret.add (ix) ;
		}
	}
	return _MOVE_ (ret) ;
}

inline exports String<STR> FileSystemProc::absolute_path (const String<STR> &path) {
	String<STR> ret = String<STR> (DEFAULT_FILEPATH_SIZE::value) ;
	auto rax = FileSystemProc::decouple_path_name (path) ;
	auto fax = TRUE ;
	if switch_once (fax) {
		if (path.size () < 1)
			discard ;
		if (path[0] != STR ('\\'))
			if (path[0] != STR ('/'))
				discard ;
		ret += _PCSTR_ ("\\") ;
	}
	if switch_once (fax) {
		if (rax.length () < 1)
			discard ;
		INDEX ix = rax.access (0) ;
		if (rax[ix] != _PCSTR_ ("."))
			if (rax[ix] != _PCSTR_ (".."))
				discard ;
		const auto r1x = FileSystemProc::working_path () ;
		if switch_once (TRUE) {
			auto rbx = FileSystemProc::decouple_path_name (r1x) ;
			rbx.appand (_MOVE_ (rax)) ;
			rax = _MOVE_ (rbx) ;
		}
		if (r1x.size () < 0)
			discard ;
		if (r1x[0] != STR ('\\'))
			if (r1x[0] != STR ('/'))
				discard ;
		ret += _PCSTR_ ("\\") ;
	}
	const auto r2x = FileSystemStaticProc::static_relative_path_name (rax) ;
	for (auto &&i : _RANGE_ (0 ,r2x.length ())) {
		INDEX ix = r2x.access (i) ;
		if (i > 0)
			ret += _PCSTR_ ("\\") ;
		ret += rax[r2x[ix]] ;
	}
	if switch_once (TRUE) {
		const auto r3x = ret.length () ;
		if (r3x < 1)
			discard ;
		if (ret[r3x - 1] == STR ('\\'))
			discard ;
		if (ret[r3x - 1] == STR ('/'))
			discard ;
		ret += _PCSTR_ ("\\") ;
	}
	return _MOVE_ (ret) ;
}

inline exports const String<STR> &FileSystemProc::module_file_path () side_effects {
	return _CACHE_ ([&] () {
		String<STR> ret = String<STR> (DEFAULT_FILEPATH_SIZE::value) ;
		GetModuleFileName (NULL ,ret.raw ().self ,VARY (ret.size ())) ;
		ret = FileSystemProc::parse_path_name (ret) ;
		ret += _PCSTR_ ("\\") ;
		return _MOVE_ (ret) ;
	}) ;
}

inline exports const String<STR> &FileSystemProc::module_file_name () side_effects {
	return _CACHE_ ([&] () {
		String<STR> ret = String<STR> (DEFAULT_FILEPATH_SIZE::value) ;
		GetModuleFileName (NULL ,ret.raw ().self ,VARY (ret.size ())) ;
		ret = FileSystemProc::parse_file_name (ret) ;
		return _MOVE_ (ret) ;
	}) ;
}

inline exports BOOL FileSystemProc::find_directory (const String<STR> &dire) side_effects {
	const auto r1x = GetFileAttributes (dire.raw ().self) ;
	if (r1x == INVALID_FILE_ATTRIBUTES)
		return FALSE ;
	if ((r1x & FILE_ATTRIBUTE_DIRECTORY) == 0)
		return FALSE ;
	return TRUE ;
}

inline exports BOOL FileSystemProc::lock_directory (const String<STR> &dire) side_effects {
	BOOL ret = FALSE ;
	const auto r1x = String<STR>::make (dire ,_PCSTR_ ("\\") ,_PCSTR_ (".lockdirectory")) ;
	const auto r2x = GlobalRuntime::process_pid () ;
	const auto r3x = GlobalRuntime::process_info (r2x) ;
	auto fax = TRUE ;
	if switch_once (fax) {
		const auto r4x = FileSystemProc::find_file (r1x) ;
		if (!r4x)
			discard ;
		const auto r5x = FileSystemProc::load_file (r1x) ;
		if (r5x.size () != r3x.size ())
			discard ;
		const auto r6x = GlobalRuntime::process_info_pid (PhanBuffer<const STRU8>::make (r5x)) ;
		const auto r7x = GlobalRuntime::process_info (r6x) ;
		_DEBUG_ASSERT_ (r7x.size () == r5x.size ()) ;
		const auto r8x = BasicProc::mem_compr (r7x.self ,r5x.self ,r5x.size ()) ;
		if (r8x != 0)
			discard ;
		ret = CSC::BOOL (r2x == r6x) ;
	}
	if switch_once (fax) {
		auto &r9x = _CACHE_ ([&] () {
			return UniqueRef<String<STR>> ([&] (String<STR> &me) {
				me = r1x ;
				FileSystemProc::save_file (r1x ,PhanBuffer<const CSC::BYTE>::make (r3x)) ;
			} ,[] (String<STR> &me) {
				FileSystemProc::erase_file (me) ;
			}) ;
		}) ;
		_STATIC_UNUSED_ (r9x) ;
		ret = TRUE ;
	}
	return _MOVE_ (ret) ;
}

inline exports void FileSystemProc::build_directory (const String<STR> &dire) {
	if (FileSystemProc::find_directory (dire))
		return ;
	auto rax = String<STR> (DEFAULT_FILEPATH_SIZE::value) ;
	const auto r1x = FileSystemProc::absolute_path (dire) ;
	const auto r2x = FileSystemProc::decouple_path_name (r1x) ;
	_DEBUG_ASSERT_ (r2x.length () >= 1) ;
	if switch_once (TRUE) {
		if (dire.size () < 1)
			discard ;
		if (dire[0] != STR ('\\'))
			if (dire[0] != STR ('/'))
				discard ;
		rax += _PCSTR_ ("\\") ;
	}
	for (auto &&i : _RANGE_ (0 ,r2x.length ())) {
		INDEX ix = r2x.access (i) ;
		if (i > 0)
			rax += _PCSTR_ ("\\") ;
		rax += r2x[ix] ;
		const auto r3x = r2x[ix].length () ;
		if (r3x > 1)
			if (r2x[ix][r3x - 1] == STR (':'))
				continue ;
		CreateDirectory (rax.raw ().self ,NULL) ;
	}
}

inline exports void FileSystemProc::erase_directory (const String<STR> &dire) {
	RemoveDirectory (dire.raw ().self) ;
}

//@warn: recursive call with junction(const symbolic &link) may cause endless loop
inline exports void FileSystemProc::enum_directory (const String<STR> &dire ,Deque<String<STR>> &file_list ,Deque<String<STR>> &dire_list) {
	auto rax = String<STR> (DEFAULT_FILEPATH_SIZE::value) ;
	rax += dire ;
	rax += _PCSTR_ ("\\") ;
	const auto r1x = rax.length () ;
	auto rbx = api::WIN32_FIND_DATA () ;
	const auto r2x = UniqueRef<api::HANDLE> ([&] (api::HANDLE &me) {
		rax += _PCSTR_ ("*.*") ;
		_ZERO_ (rbx) ;
		me = FindFirstFile (rax.raw ().self ,DEPTR[rbx]) ;
		if (me == INVALID_HANDLE_VALUE)
			me = NULL ;
		rax[r1x] = 0 ;
	} ,[] (api::HANDLE &me) {
		if (me == NULL)
			return ;
		FindClose (me) ;
	}) ;
	if (r2x.self == NULL)
		return ;
	while (TRUE) {
		if (rbx.cFileName[0] == 0)
			break ;
		if switch_once (TRUE) {
			const auto r3x = String<STR> (PTRTOARR[rbx.cFileName]) ;
			if (r3x == _PCSTR_ ("."))
				discard ;
			if (r3x == _PCSTR_ (".."))
				discard ;
			auto &r4x = _SWITCH_ (
				((rbx.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) ? dire_list :
				file_list) ;
			rax += r3x ;
			r4x.add (rax) ;
		}
		rax[r1x] = 0 ;
		rbx.cFileName[0] = 0 ;
		FindNextFile (r2x.self ,DEPTR[rbx]) ;
	}
}

inline exports void FileSystemProc::clear_directory (const String<STR> &dire) {
	auto rax = Deque<PACK<String<STR> ,BOOL>> () ;
	auto rbx = ARRAY2<Deque<String<STR>>> () ;
	rbx[0].clear () ;
	rbx[1].clear () ;
	FileSystemProc::enum_directory (dire ,rbx[0] ,rbx[1]) ;
	for (auto &&i : rbx[0])
		FileSystemProc::erase_file (i) ;
	for (auto &&i : rbx[1])
		rax.add (PACK<String<STR> ,BOOL> {i ,FALSE}) ;
	_DYNAMIC_ASSERT_ (rax.length () <= DEFAULT_DIRECTORY_SIZE::value) ;
	while (TRUE) {
		if (rax.empty ())
			break ;
		INDEX ix = rax.tail () ;
		FileSystemProc::erase_directory (rax[ix].mP1) ;
		auto fax = TRUE ;
		if switch_once (fax) {
			if (!rax[ix].mP2)
				discard ;
			rax.pop () ;
		}
		if switch_once (fax) {
			rbx[0].clear () ;
			rbx[1].clear () ;
			FileSystemProc::enum_directory (rax[ix].mP1 ,rbx[0] ,rbx[1]) ;
			for (auto &&i : rbx[0])
				FileSystemProc::erase_file (i) ;
			for (auto &&i : rbx[1])
				rax.add (PACK<String<STR> ,BOOL> {i ,FALSE}) ;
			_DYNAMIC_ASSERT_ (rax.length () <= DEFAULT_DIRECTORY_SIZE::value) ;
			rax[ix].mP2 = TRUE ;
		}
	}
}

class StreamLoader::Private::Implement
	:public Abstract {
private:
	UniqueRef<api::HANDLE> mReadFile ;
	UniqueRef<api::HANDLE> mWriteFile ;

public:
	implicit Implement () = delete ;

	explicit Implement (const String<STR> &file) {
		mWriteFile = UniqueRef<api::HANDLE> ([&] (api::HANDLE &me) {
			const auto r1x = VAR32 (FILE_SHARE_READ | FILE_SHARE_WRITE) ;
			me = api::CreateFile (file.raw ().self ,GENERIC_WRITE ,r1x ,NULL ,OPEN_ALWAYS ,FILE_FLAG_SEQUENTIAL_SCAN ,NULL) ;
			if (me == INVALID_HANDLE_VALUE)
				me = NULL ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
			SetFilePointer (me ,0 ,NULL ,FILE_END) ;
		} ,[] (api::HANDLE &me) {
			api::CloseHandle (me) ;
		}) ;
		mReadFile = UniqueRef<api::HANDLE> ([&] (api::HANDLE &me) {
			const auto r1x = VAR32 (FILE_SHARE_READ | FILE_SHARE_WRITE) ;
			me = api::CreateFile (file.raw ().self ,GENERIC_READ ,r1x ,NULL ,OPEN_ALWAYS ,FILE_FLAG_SEQUENTIAL_SCAN ,NULL) ;
			if (me == INVALID_HANDLE_VALUE)
				me = NULL ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
		} ,[] (api::HANDLE &me) {
			api::CloseHandle (me) ;
		}) ;
	}

	void read (const PhanBuffer<BYTE> &data) override {
		_DEBUG_ASSERT_ (data.size () < VAR32_MAX) ;
		auto rax = VARY () ;
		rax = VARY (0) ;
		const auto r1x = api::ReadFile (mReadFile ,data.self ,VARY (data.size ()) ,DEPTR[rax] ,NULL) ;
		const auto r2x = LENGTH (rax) * _EBOOL_ (r1x != 0) ;
		//@info: state of 'this' has been changed
		_DYNAMIC_ASSERT_ (r2x >= 0 && r2x < VAR32_MAX) ;
		if (data.size () - r2x == 0)
			return ;
		BasicProc::mem_fill (PTRTOARR[DEPTR[data[r2x]]] ,(data.size () - r2x) ,BYTE (0X00)) ;
	}

	void write (const PhanBuffer<const BYTE> &data) override {
		_DEBUG_ASSERT_ (data.size () < VAR32_MAX) ;
		auto rax = VARY () ;
		rax = VARY (0) ;
		const auto r1x = api::WriteFile (mWriteFile ,data.self ,VARY (data.size ()) ,DEPTR[rax] ,NULL) ;
		const auto r2x = LENGTH (rax) * _EBOOL_ (r1x != 0) ;
		//@info: state of 'this' has been changed
		_DYNAMIC_ASSERT_ (r2x == data.size ()) ;
	}

	void flush () override {
		FlushFileBuffers (mWriteFile) ;
	}
} ;

inline exports StreamLoader::StreamLoader (const String<STR> &file) {
	using Implement = typename Private::Implement ;
	mThis = StrongRef<Implement>::make (file) ;
}

class BufferLoader::Private::Implement
	:public Abstract {
private:
	struct SELF_PACK {
		UniqueRef<api::HANDLE> mFile ;
		UniqueRef<api::HANDLE> mMapping ;
		UniqueRef<PhanBuffer<BYTE>> mBuffer ;
	} ;

private:
	UniqueRef<SharedRef<SELF_PACK>> mThis ;

public:
	implicit Implement () = delete ;

	explicit Implement (const String<STR> &file) {
		mThis = UniqueRef<SharedRef<SELF_PACK>> ([&] (SharedRef<SELF_PACK> &me) {
			me = SharedRef<SELF_PACK>::make () ;
		} ,[] (SharedRef<SELF_PACK> &me) {
			me->mBuffer = UniqueRef<PhanBuffer<BYTE>> () ;
			me->mMapping = UniqueRef<api::HANDLE> () ;
			me->mFile = UniqueRef<api::HANDLE> () ;
		}) ;
		mThis->self.mFile = UniqueRef<api::HANDLE> ([&] (api::HANDLE &me) {
			me = api::CreateFile (file.raw ().self ,GENERIC_READ ,FILE_SHARE_READ ,NULL ,OPEN_EXISTING ,FILE_ATTRIBUTE_NORMAL ,NULL) ;
			if (me == INVALID_HANDLE_VALUE)
				me = NULL ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
		} ,[] (api::HANDLE &me) {
			api::CloseHandle (me) ;
		}) ;
		const auto r1x = LENGTH (api::GetFileSize (mThis->self.mFile.self ,NULL)) ;
		_DYNAMIC_ASSERT_ (r1x >= 0 && r1x < VAR32_MAX) ;
		mThis->self.mMapping = UniqueRef<api::HANDLE> ([&] (api::HANDLE &me) {
			me = api::CreateFileMapping (mThis->self.mFile.self ,NULL ,PAGE_READONLY ,0 ,VARY (r1x) ,NULL) ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
		} ,[] (api::HANDLE &me) {
			api::CloseHandle (me) ;
		}) ;
		mThis->self.mBuffer = UniqueRef<PhanBuffer<BYTE>> ([&] (PhanBuffer<BYTE> &me) {
			const auto r2x = api::MapViewOfFile (mThis->self.mMapping.self ,FILE_MAP_READ ,0 ,0 ,r1x) ;
			_DYNAMIC_ASSERT_ (r2x != NULL) ;
			const auto r3x = _POINTER_CAST_ (ARGV<ARR<BYTE>>::null ,r2x) ;
			me = PhanBuffer<BYTE>::make (DEREF[r3x] ,r1x) ;
		} ,[] (PhanBuffer<BYTE> &me) {
			api::UnmapViewOfFile (me.self) ;
		}) ;
	}

	explicit Implement (const String<STR> &file ,const LENGTH &file_len) {
		_DEBUG_ASSERT_ (file_len >= 0 && file_len < VAR32_MAX) ;
		mThis = UniqueRef<SharedRef<SELF_PACK>> ([&] (SharedRef<SELF_PACK> &me) {
			me = SharedRef<SELF_PACK>::make () ;
		} ,[] (SharedRef<SELF_PACK> &me) {
			me->mBuffer = UniqueRef<PhanBuffer<BYTE>> () ;
			me->mMapping = UniqueRef<api::HANDLE> () ;
			me->mFile = UniqueRef<api::HANDLE> () ;
		}) ;
		mThis->self.mFile = UniqueRef<api::HANDLE> ([&] (api::HANDLE &me) {
			const auto r1x = CSC::CHAR (GENERIC_READ | GENERIC_WRITE) ;
			me = api::CreateFile (file.raw ().self ,r1x ,0 ,NULL ,CREATE_ALWAYS ,FILE_ATTRIBUTE_NORMAL ,NULL) ;
			if (me == INVALID_HANDLE_VALUE)
				me = NULL ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
		} ,[] (api::HANDLE &me) {
			api::CloseHandle (me) ;
		}) ;
		mThis->self.mMapping = UniqueRef<api::HANDLE> ([&] (api::HANDLE &me) {
			me = api::CreateFileMapping (mThis->self.mFile.self ,NULL ,PAGE_READWRITE ,0 ,VARY (file_len) ,NULL) ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
		} ,[] (api::HANDLE &me) {
			api::CloseHandle (me) ;
		}) ;
		mThis->self.mBuffer = UniqueRef<PhanBuffer<BYTE>> ([&] (PhanBuffer<BYTE> &me) {
			const auto r1x = VAR32 (FILE_MAP_READ | FILE_MAP_WRITE) ;
			const auto r2x = api::MapViewOfFile (mThis->self.mMapping.self ,r1x ,0 ,0 ,file_len) ;
			_DYNAMIC_ASSERT_ (r2x != NULL) ;
			const auto r3x = _POINTER_CAST_ (ARGV<ARR<BYTE>>::null ,r2x) ;
			me = PhanBuffer<BYTE>::make (DEREF[r3x] ,file_len) ;
		} ,[] (PhanBuffer<BYTE> &me) {
			api::UnmapViewOfFile (me.self) ;
		}) ;
	}

	explicit Implement (const String<STR> &file ,const BOOL &cache) {
		_DEBUG_ASSERT_ (cache) ;
		mThis = UniqueRef<SharedRef<SELF_PACK>> ([&] (SharedRef<SELF_PACK> &me) {
			me = SharedRef<SELF_PACK>::make () ;
		} ,[] (SharedRef<SELF_PACK> &me) {
			me->mBuffer = UniqueRef<PhanBuffer<BYTE>> () ;
			me->mMapping = UniqueRef<api::HANDLE> () ;
			me->mFile = UniqueRef<api::HANDLE> () ;
		}) ;
		mThis->self.mMapping = UniqueRef<api::HANDLE> ([&] (api::HANDLE &me) {
			me = OpenFileMapping (FILE_MAP_READ ,FALSE ,file.raw ().self) ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
		} ,[] (api::HANDLE &me) {
			api::CloseHandle (me) ;
		}) ;
		mThis->self.mBuffer = UniqueRef<PhanBuffer<BYTE>> ([&] (PhanBuffer<BYTE> &me) {
			const auto r1x = UniqueRef<PhanBuffer<BYTE>> ([&] (PhanBuffer<BYTE> &me) {
				const auto r2x = api::MapViewOfFile (mThis->self.mMapping.self ,FILE_MAP_READ ,0 ,0 ,0) ;
				_DYNAMIC_ASSERT_ (r2x != NULL) ;
				const auto r3x = _POINTER_CAST_ (ARGV<ARR<BYTE>>::null ,r2x) ;
				me = PhanBuffer<BYTE>::make (DEREF[r3x] ,1) ;
			} ,[] (PhanBuffer<BYTE> &me) {
				api::UnmapViewOfFile (me.self) ;
			}) ;
			auto rax = api::MEMORY_BASIC_INFORMATION () ;
			_ZERO_ (rax) ;
			const auto r4x = VirtualQuery (r1x->self ,DEPTR[rax] ,_SIZEOF_ (api::MEMORY_BASIC_INFORMATION)) ;
			_DYNAMIC_ASSERT_ (r4x == _SIZEOF_ (api::MEMORY_BASIC_INFORMATION)) ;
			const auto r5x = api::MapViewOfFile (mThis->self.mMapping.self ,FILE_MAP_READ ,0 ,0 ,rax.RegionSize) ;
			_DYNAMIC_ASSERT_ (r5x != NULL) ;
			const auto r6x = _POINTER_CAST_ (ARGV<ARR<BYTE>>::null ,r5x) ;
			me = PhanBuffer<BYTE>::make (DEREF[r6x] ,LENGTH (rax.RegionSize)) ;
		} ,[] (PhanBuffer<BYTE> &me) {
			api::UnmapViewOfFile (me.self) ;
		}) ;
	}

	explicit Implement (const String<STR> &file ,const LENGTH &file_len ,const BOOL &cache) {
		_DEBUG_ASSERT_ (file_len >= 0 && file_len < VAR32_MAX) ;
		_DEBUG_ASSERT_ (cache) ;
		mThis = UniqueRef<SharedRef<SELF_PACK>> ([&] (SharedRef<SELF_PACK> &me) {
			me = SharedRef<SELF_PACK>::make () ;
		} ,[] (SharedRef<SELF_PACK> &me) {
			me->mBuffer = UniqueRef<PhanBuffer<BYTE>> () ;
			me->mMapping = UniqueRef<api::HANDLE> () ;
			me->mFile = UniqueRef<api::HANDLE> () ;
		}) ;
		mThis->self.mMapping = UniqueRef<api::HANDLE> ([&] (api::HANDLE &me) {
			me = api::CreateFileMapping (INVALID_HANDLE_VALUE ,NULL ,PAGE_READWRITE ,0 ,VARY (file_len) ,file.raw ().self) ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
		} ,[] (api::HANDLE &me) {
			api::CloseHandle (me) ;
		}) ;
		mThis->self.mBuffer = UniqueRef<PhanBuffer<BYTE>> ([&] (PhanBuffer<BYTE> &me) {
			const auto r1x = VAR32 (FILE_MAP_READ | FILE_MAP_WRITE) ;
			const auto r2x = api::MapViewOfFile (mThis->self.mMapping.self ,r1x ,0 ,0 ,file_len) ;
			_DYNAMIC_ASSERT_ (r2x != NULL) ;
			const auto r3x = _POINTER_CAST_ (ARGV<ARR<BYTE>>::null ,r2x) ;
			me = PhanBuffer<BYTE>::make (DEREF[r3x] ,file_len) ;
		} ,[] (PhanBuffer<BYTE> &me) {
			api::UnmapViewOfFile (me.self) ;
		}) ;
	}

	PhanBuffer<BYTE> watch () leftvalue override {
		_DEBUG_ASSERT_ (mThis.exist ()) ;
		return PhanBuffer<BYTE>::make (mThis->self.mBuffer.self) ;
	}

	PhanBuffer<const BYTE> watch () const leftvalue override {
		_DEBUG_ASSERT_ (mThis.exist ()) ;
		return PhanBuffer<const BYTE>::make (mThis->self.mBuffer.self) ;
	}

	void flush () override {
		_DEBUG_ASSERT_ (mThis.exist ()) ;
		FlushViewOfFile (mThis->self.mBuffer->self ,mThis->self.mBuffer->size ()) ;
	}
} ;

inline exports BufferLoader::BufferLoader (const String<STR> &file) {
	using Implement = typename Private::Implement ;
	mThis = StrongRef<Implement>::make (file) ;
}

inline exports BufferLoader::BufferLoader (const String<STR> &file ,const LENGTH &file_len) {
	using Implement = typename Private::Implement ;
	mThis = StrongRef<Implement>::make (file ,file_len) ;
}

inline exports BufferLoader::BufferLoader (const String<STR> &file ,const BOOL &cache) {
	using Implement = typename Private::Implement ;
	mThis = StrongRef<Implement>::make (file ,cache) ;
}

inline exports BufferLoader::BufferLoader (const String<STR> &file ,const LENGTH &file_len ,const BOOL &cache) {
	using Implement = typename Private::Implement ;
	mThis = StrongRef<Implement>::make (file ,file_len ,cache) ;
}

class FileSystemService::Private::Implement
	:public FileSystemService::Abstract {
public:
	implicit Implement () = default ;

	void startup () override {
		_STATIC_WARNING_ ("noop") ;
	}

	void shutdown () override {
		_STATIC_WARNING_ ("noop") ;
	}
} ;

inline exports FileSystemService::FileSystemService (const ARGVF<Singleton<FileSystemService>> &) {
	using Implement = typename Private::Implement ;
	mThis = StrongRef<Implement>::make () ;
}
} ;