#pragma once

#ifndef __CSC_DEBUGGER__
#error "∑(っ°Д° ;)っ : require 'csc_debugger.hpp'"
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
#include <cstdio>

#include <signal.h>
#include <unistd.h>
#include <execinfo.h>
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
using ::signal ;
using ::backtrace ;
using ::free ;
using ::backtrace_symbols ;
} ;

class ConsoleService::Implement
	:public ConsoleService::Abstract {
private:
	TextWriter<STR> mConWriter ;
	TextWriter<STR> mLogWriter ;
	LENGTH mBufferSize ;
	Set<EFLAG> mOptionSet ;
	UniqueRef<VAR32> mConsole ;
	String<STR> mLogPath ;
	AutoRef<StreamLoader> mLogFileStream ;

	BOOL mTempState ;

public:
	Implement () {
		const auto r1x = DEFAULT_HUGESTRING_SIZE::value + 1 ;
		mConWriter = TextWriter<STR> (SharedRef<FixedBuffer<STR>>::make (r1x)) ;
		mLogWriter = TextWriter<STR> (SharedRef<FixedBuffer<STR>>::make (r1x)) ;
		mBufferSize = mLogWriter.size () - DEFAULT_LONGSTRING_SIZE::value ;
		mOptionSet = Set<EFLAG> (128) ;
		mLogPath = String<STR> () ;
	}

	LENGTH buffer_size () const override {
		return mBufferSize ;
	}

	void enable_option (EFLAG option) override {
		if (option == OPTION_DEFAULT)
			mOptionSet.clear () ;
		mOptionSet.add (option) ;
	}

	void disable_option (EFLAG option) override {
		mOptionSet.erase (option) ;
	}

#ifdef __CSC_CONFIG_STRA__
	void print (const Binder &msg) override {
		if (mOptionSet.find (EFLAG (OPTION_NO_PRINT)) != VAR_NONE)
			return ;
		write_con_buffer (msg) ;
		attach_console () ;
		std::printf (_PCSTR_ ("%s\n") ,mConWriter.raw ().self) ;
		if (mLogPath.empty ())
			return ;
		const auto r1x = PhanBuffer<const STR>::make (mConWriter.raw () ,(mConWriter.length () - 1)) ;
		log (_PCSTR_ ("PRINT") ,r1x) ;
	}
#endif

#ifdef __CSC_CONFIG_STRW__
	void print (const Binder &msg) override {
		if (mOptionSet.find (EFLAG (OPTION_NO_PRINT)) != VAR_NONE)
			return ;
		write_con_buffer (msg) ;
		attach_console () ;
		std::wprintf (_PCSTR_ ("%ls\n") ,mConWriter.raw ().self) ;
		if (mLogPath.empty ())
			return ;
		const auto r1x = PhanBuffer<const STR>::make (mConWriter.raw () ,(mConWriter.length () - 1)) ;
		log (_PCSTR_ ("PRINT") ,r1x) ;
	}
#endif

#ifdef __CSC_CONFIG_STRA__
	void fatal (const Binder &msg) override {
		if (mOptionSet.find (EFLAG (OPTION_NO_FATAL)) != VAR_NONE)
			return ;
		write_con_buffer (msg) ;
		attach_console () ;
		std::printf (_PCSTR_ ("\033[1;34m%s\033[0m\n") ,mConWriter.raw ().self) ;
		if (mLogPath.empty ())
			return ;
		const auto r1x = PhanBuffer<const STR>::make (mConWriter.raw () ,(mConWriter.length () - 1)) ;
		log (_PCSTR_ ("FATAL") ,r1x) ;
	}
#endif

#ifdef __CSC_CONFIG_STRW__
	void fatal (const Binder &msg) override {
		if (mOptionSet.find (EFLAG (OPTION_NO_FATAL)) != VAR_NONE)
			return ;
		write_con_buffer (msg) ;
		attach_console () ;
		std::wprintf (_PCSTR_ ("\033[1;34m%ls\033[0m\n") ,mConWriter.raw ().self) ;
		if (mLogPath.empty ())
			return ;
		const auto r1x = PhanBuffer<const STR>::make (mConWriter.raw () ,(mConWriter.length () - 1)) ;
		log (_PCSTR_ ("FATAL") ,r1x) ;
	}
#endif

#ifdef __CSC_CONFIG_STRA__
	void error (const Binder &msg) override {
		if (mOptionSet.find (EFLAG (OPTION_NO_ERROR)) != VAR_NONE)
			return ;
		write_con_buffer (msg) ;
		attach_console () ;
		std::printf (_PCSTR_ ("\033[1;31m%s\033[0m\n") ,mConWriter.raw ().self) ;
		if (mLogPath.empty ())
			return ;
		const auto r1x = PhanBuffer<const STR>::make (mConWriter.raw () ,(mConWriter.length () - 1)) ;
		log (_PCSTR_ ("ERROR") ,r1x) ;
	}
#endif

#ifdef __CSC_CONFIG_STRW__
	void error (const Binder &msg) override {
		if (mOptionSet.find (EFLAG (OPTION_NO_ERROR)) != VAR_NONE)
			return ;
		write_con_buffer (msg) ;
		attach_console () ;
		std::wprintf (_PCSTR_ ("\033[1;31m%ls\033[0m\n") ,mConWriter.raw ().self) ;
		if (mLogPath.empty ())
			return ;
		const auto r1x = PhanBuffer<const STR>::make (mConWriter.raw () ,(mConWriter.length () - 1)) ;
		log (_PCSTR_ ("ERROR") ,r1x) ;
	}
#endif

#ifdef __CSC_CONFIG_STRA__
	void warn (const Binder &msg) override {
		if (mOptionSet.find (EFLAG (OPTION_NO_WARN)) != VAR_NONE)
			return ;
		write_con_buffer (msg) ;
		attach_console () ;
		std::printf (_PCSTR_ ("\033[1;33m%s\033[0m\n") ,mConWriter.raw ().self) ;
		if (mLogPath.empty ())
			return ;
		const auto r1x = PhanBuffer<const STR>::make (mConWriter.raw () ,(mConWriter.length () - 1)) ;
		log (_PCSTR_ ("WARN") ,r1x) ;
	}
#endif

#ifdef __CSC_CONFIG_STRW__
	void warn (const Binder &msg) override {
		if (mOptionSet.find (EFLAG (OPTION_NO_WARN)) != VAR_NONE)
			return ;
		write_con_buffer (msg) ;
		attach_console () ;
		std::wprintf (_PCSTR_ ("\033[1;33m%ls\033[0m\n") ,mConWriter.raw ().self) ;
		if (mLogPath.empty ())
			return ;
		const auto r1x = PhanBuffer<const STR>::make (mConWriter.raw () ,(mConWriter.length () - 1)) ;
		log (_PCSTR_ ("WARN") ,r1x) ;
	}
#endif

#ifdef __CSC_CONFIG_STRA__
	void info (const Binder &msg) override {
		if (mOptionSet.find (EFLAG (OPTION_NO_INFO)) != VAR_NONE)
			return ;
		write_con_buffer (msg) ;
		attach_console () ;
		std::printf (_PCSTR_ ("\033[1;32m%s\033[0m\n") ,mConWriter.raw ().self) ;
		if (mLogPath.empty ())
			return ;
		const auto r1x = PhanBuffer<const STR>::make (mConWriter.raw () ,(mConWriter.length () - 1)) ;
		log (_PCSTR_ ("INFO") ,r1x) ;
	}
#endif

#ifdef __CSC_CONFIG_STRW__
	void info (const Binder &msg) override {
		if (mOptionSet.find (EFLAG (OPTION_NO_INFO)) != VAR_NONE)
			return ;
		write_con_buffer (msg) ;
		attach_console () ;
		std::wprintf (_PCSTR_ ("\033[1;32m%ls\033[0m\n") ,mConWriter.raw ().self) ;
		if (mLogPath.empty ())
			return ;
		const auto r1x = PhanBuffer<const STR>::make (mConWriter.raw () ,(mConWriter.length () - 1)) ;
		log (_PCSTR_ ("INFO") ,r1x) ;
	}
#endif

#ifdef __CSC_CONFIG_STRA__
	void debug (const Binder &msg) override {
		if (mOptionSet.find (EFLAG (OPTION_NO_DEBUG)) != VAR_NONE)
			return ;
		write_con_buffer (msg) ;
		attach_console () ;
		std::printf (_PCSTR_ ("\033[1;36m%s\033[0m\n") ,mConWriter.raw ().self) ;
		if (mLogPath.empty ())
			return ;
		const auto r1x = PhanBuffer<const STR>::make (mConWriter.raw () ,(mConWriter.length () - 1)) ;
		log (_PCSTR_ ("DEBUG") ,r1x) ;
	}
#endif

#ifdef __CSC_CONFIG_STRW__
	void debug (const Binder &msg) override {
		if (mOptionSet.find (EFLAG (OPTION_NO_DEBUG)) != VAR_NONE)
			return ;
		write_con_buffer (msg) ;
		attach_console () ;
		std::wprintf (_PCSTR_ ("\033[1;36m%ls\033[0m\n") ,mConWriter.raw ().self) ;
		if (mLogPath.empty ())
			return ;
		const auto r1x = PhanBuffer<const STR>::make (mConWriter.raw () ,(mConWriter.length () - 1)) ;
		log (_PCSTR_ ("DEBUG") ,r1x) ;
	}
#endif

#ifdef __CSC_CONFIG_STRA__
	void verbose (const Binder &msg) override {
		if (mOptionSet.find (EFLAG (OPTION_NO_VERBOSE)) != VAR_NONE)
			return ;
		write_con_buffer (msg) ;
		attach_console () ;
		std::printf (_PCSTR_ ("\033[1;37m%s\033[0m\n") ,mConWriter.raw ().self) ;
		if (mLogPath.empty ())
			return ;
		const auto r1x = PhanBuffer<const STR>::make (mConWriter.raw () ,(mConWriter.length () - 1)) ;
		log (_PCSTR_ ("VERBOSE") ,r1x) ;
	}
#endif

#ifdef __CSC_CONFIG_STRW__
	void verbose (const Binder &msg) override {
		if (mOptionSet.find (EFLAG (OPTION_NO_VERBOSE)) != VAR_NONE)
			return ;
		write_con_buffer (msg) ;
		attach_console () ;
		std::wprintf (_PCSTR_ ("\033[1;37m%ls\033[0m\n") ,mConWriter.raw ().self) ;
		if (mLogPath.empty ())
			return ;
		const auto r1x = PhanBuffer<const STR>::make (mConWriter.raw () ,(mConWriter.length () - 1)) ;
		log (_PCSTR_ ("VERBOSE") ,r1x) ;
	}
#endif

	void attach_log (const String<STR> &path) override {
		const auto r1x = FileSystemProc::absolute_path (path) ;
		if switch_case (TRUE) {
			if (mLogPath == r1x)
				discard ;
			if (!mLogFileStream.exist ())
				discard ;
			mLogFileStream->flush () ;
			mLogFileStream = AutoRef<StreamLoader> () ;
		}
		mLogPath = r1x ;
	}

	void log (const Plain<STR> &tag ,const PhanBuffer<const STR> &msg) {
		using ImplBinder = typename Detail::template ImplBinder<PhanBuffer<const STR>> ;
		log (PhanBuffer<const STR>::make (tag.self ,tag.size ()) ,ImplBinder (msg)) ;
	}

	void log (const PhanBuffer<const STR> &tag ,const Binder &msg) override {
		write_log_buffer (tag ,msg) ;
#ifdef __CSC_DEBUG__
		write_debugger () ;
#endif
		write_log_file () ;
	}

	void show () override {
		mConsole = UniqueRef<VAR32>::make (1) ;
	}

	void hide () override {
		mConsole = UniqueRef<VAR32> () ;
	}

	void pause () override {
		if (!mConsole.exist ())
			return ;
		std::printf (_PCSTR_ ("press any key to continue...\n")) ;
		const auto r1x = std::getchar () ;
		_STATIC_UNUSED_ (r1x) ;
	}

	void clear () override {
		if (!mConsole.exist ())
			return ;
		std::printf (_PCSTR_ ("\f\f")) ;
	}

private:
	void write_con_buffer (const Binder &msg) {
		mConWriter << TextWriter<STR>::CLS ;
		mConWriter << msg ;
		mConWriter << TextWriter<STR>::EOS ;
	}

	void attach_console () {
		if (mConsole.exist ())
			return ;
		mConsole = UniqueRef<VAR32>::make (0) ;
	}

	void write_log_buffer (const PhanBuffer<const STR> &tag ,const Binder &msg) {
		mLogWriter << TextWriter<STR>::CLS ;
		mLogWriter << _PCSTR_ ("[") ;
		mLogWriter << StringProc::build_hours (std::chrono::system_clock ().now ()) ;
		mLogWriter << _PCSTR_ ("][") ;
		mLogWriter << tag ;
		mLogWriter << _PCSTR_ ("] : ") ;
		mLogWriter << msg ;
		mLogWriter << TextWriter<STR>::GAP ;
		mLogWriter << TextWriter<STR>::EOS ;
	}

	void write_debugger () {
		_STATIC_WARNING_ ("noop") ;
	}

	void write_log_file () {
		if (mLogPath.empty ())
			return ;
		const auto r1x = PhanBuffer<const STR>::make (mLogWriter.raw ().self ,(mLogWriter.length () - 1)) ;
		const auto r2x = PhanBuffer<const BYTE>::make (r1x) ;
		mTempState = FALSE ;
		_CALL_TRY_ ([&] () {
			if (mTempState)
				return ;
			if (!mLogFileStream.exist ())
				return ;
			mLogFileStream->write (r2x) ;
			mTempState = TRUE ;
		} ,[&] () {
			mLogFileStream = AutoRef<StreamLoader> () ;
			mTempState = FALSE ;
		}) ;
		_CALL_TRY_ ([&] () {
			if (mTempState)
				return ;
			attach_log_file () ;
			mLogFileStream->write (r2x) ;
			mTempState = TRUE ;
		} ,[&] () {
			mLogFileStream = AutoRef<StreamLoader> () ;
			mTempState = FALSE ;
		}) ;
		if (mOptionSet.find (EFLAG (OPTION_ALWAYS_FLUSH)) == VAR_NONE)
			return ;
		if (!mLogFileStream.exist ())
			return ;
		mLogFileStream->flush () ;
	}

	void attach_log_file () {
		const auto r1x = mLogPath + _PCSTR_ ("console.log") ;
		const auto r2x = mLogPath + _PCSTR_ ("console.old.log") ;
		FileSystemProc::erase_file (r2x) ;
		FileSystemProc::move_file (r2x ,r1x) ;
		mLogFileStream = AutoRef<StreamLoader>::make (r1x) ;
		const auto r3x = String<STR>::make (TextWriter<STR>::BOM) ;
		mLogFileStream->write (PhanBuffer<const BYTE>::make (r3x.raw ())) ;
	}
} ;

inline exports ConsoleService::ConsoleService () {
	mThis = StrongRef<Implement>::make () ;
}

class DebuggerService::Implement
	:public DebuggerService::Abstract {
public:
	void abort_once_invoked_exit (BOOL flag) override {
		_DEBUG_ASSERT_ (flag) ;
		const auto r1x = _XVALUE_<PTR<void ()>> ([] () noexcept {
			GlobalRuntime::process_abort () ;
		}) ;
		const auto r2x = _XVALUE_<PTR<void (VAR32)>> ([] (VAR32) noexcept {
			GlobalRuntime::process_abort () ;
		}) ;
		const auto r3x = _XVALUE_<PTR<void (VAR32)>> ([] (VAR32) noexcept {
			GlobalRuntime::process_abort () ;
		}) ;
		const auto r4x = _XVALUE_<PTR<void (VAR32)>> ([] (VAR32) noexcept {
			GlobalRuntime::process_abort () ;
		}) ;
		std::atexit (r1x) ;
		api::signal (SIGFPE ,r2x) ;
		api::signal (SIGILL ,r3x) ;
		api::signal (SIGSEGV ,r4x) ;
	}

	void output_memory_leaks_report (BOOL flag) override {
		_DEBUG_ASSERT_ (flag) ;
		_STATIC_WARNING_ ("unimplemented") ;
		_DYNAMIC_ASSERT_ (FALSE) ;
	}

	Array<LENGTH> captrue_stack_trace () popping override {
		auto rax = AutoBuffer<PTR<VOID>> (DEFAULT_RECURSIVE_SIZE::value) ;
		const auto r1x = api::backtrace (rax.self ,VAR32 (rax.size ())) ;
		Array<LENGTH> ret = Array<LENGTH> (r1x) ;
		for (auto &&i : _RANGE_ (0 ,ret.length ()))
			ret[i] = _ADDRESS_ (rax[i]) ;
		return std::move (ret) ;
	}

	Array<String<STR>> symbol_from_address (const Array<LENGTH> &list) popping override {
		_DEBUG_ASSERT_ (list.length () < VAR32_MAX) ;
		const auto r1x = _CALL_ ([&] () {
			Array<PTR<VOID>> ret = Array<PTR<VOID>> (list.length ()) ;
			for (auto &&i : _RANGE_ (0 ,ret.length ())) {
				const auto r2x = _XVALUE_<PTR<VOID>> (&_NULL_<BYTE> () + i) ;
				ret[i] = r2x ;
			}
			return std::move (ret) ;
		}) ;
		const auto r3x = UniqueRef<PTR<PTR<STRA>>> ([&] (PTR<PTR<STRA>> &me) {
			me = api::backtrace_symbols (r1x.raw ().self ,VAR32 (r1x.length ())) ;
		} ,[&] (PTR<PTR<STRA>> &me) {
			if (me == NULL)
				return ;
			api::free (me) ;
		}) ;
		auto &r4x = PTRTOARR[r3x.self] ;
		Array<String<STR>> ret = Array<String<STR>> (list.length ()) ;
		INDEX iw = 0 ;
		for (auto &&i : _RANGE_ (0 ,ret.length ())) {
			const auto r5x = StringProc::build_hex16s (list[i]) ;
			const auto r6x = StringProc::parse_strs (String<STRA> (PTRTOARR[r4x[i]])) ;
			ret[iw++] = String<STR>::make (_PCSTR_ ("[") ,r5x ,_PCSTR_ ("] : ") ,r6x) ;
		}
		_DEBUG_ASSERT_ (iw == ret.length ()) ;
		return std::move (ret) ;
	}
} ;

inline exports DebuggerService::DebuggerService () {
	mThis = StrongRef<Implement>::make () ;
}
} ;