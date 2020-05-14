#pragma once

#ifndef __CSC_RUNTIME__
#error "б╞(д├бузебу ;)д├ : require 'csc_runtime.hpp'"
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

#ifdef __CSC_SYSTEM_WINDOWS__
#ifndef _INC_WINDOWS
#error "б╞(д├бузебу ;)д├ : require 'Windows.h'"
#endif
#endif

#ifdef __CSC_SYSTEM_LINUX__
#ifdef __CSC_DEPRECATED__
#include <unistd.h>
#include <sys/syscall.h>
#endif
#endif

#ifdef __CSC_DEPRECATED__
#include <cstdlib>
#include <cmath>
#include <random>

#include <setjmp.h>
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
using std::random_device ;
using std::mt19937 ;
using std::memory_order ;

namespace this_thread {
using std::this_thread::sleep_for ;
using std::this_thread::yield ;
} ;

using std::atomic_thread_fence ;

#ifndef __CSC_COMPILER_GNUC__
//@error: fuck g++4.8
using std::quick_exit ;
#endif

using std::exit ;
using std::terminate ;

using ::setlocale ;
using ::longjmp ;

#ifdef __CSC_SYSTEM_WINDOWS__
using ::GetCurrentThreadId ;
using ::GetCurrentProcessId ;
using ::OpenProcess ;
using ::CloseHandle ;
using ::GetProcessTimes ;
#endif

#ifdef __CSC_SYSTEM_LINUX__
using ::pid_t ;
using ::getpgid ;
using ::getsid ;
#endif
} ;

inline exports stl::chrono::system_clock::time_point GlobalRuntime::clock_now () {
	return stl::chrono::system_clock::now () ;
}

inline exports stl::chrono::steady_clock::time_point GlobalRuntime::clock_tick () {
	return stl::chrono::steady_clock::now () ;
}

#ifdef __CSC_SYSTEM_WINDOWS__
inline exports FLAG GlobalRuntime::thread_tid () {
	return _XVALUE_<FLAG> (api::GetCurrentThreadId ()) ;
}
#endif

#ifdef __CSC_SYSTEM_LINUX__
inline exports FLAG GlobalRuntime::thread_tid () {
	return _XVALUE_<FLAG> (syscall (SYS_gettid)) ;
}
#endif

template <class _ARG1 ,class _ARG2>
inline exports void GlobalRuntime::thread_sleep (const stl::chrono::duration<_ARG1 ,_ARG2> &time_) {
	api::this_thread::sleep_for (time_) ;
}

template <class _ARG1 ,class _ARG2>
inline exports void GlobalRuntime::thread_sleep (const stl::chrono::time_point<_ARG1 ,_ARG2> &time_) {
	api::this_thread::sleep_for (time_) ;
}

inline exports void GlobalRuntime::thread_sleep () {
	api::this_thread::yield () ;
}

inline exports LENGTH GlobalRuntime::thread_concurrency () {
	return LENGTH (stl::thread::hardware_concurrency ()) ;
}

inline exports void GlobalRuntime::thread_fence () {
	api::atomic_thread_fence (api::memory_order::memory_order_seq_cst) ;
}

inline exports void GlobalRuntime::locale_init (const Plain<STRA> &locale_) {
	api::setlocale (LC_ALL ,locale_.self) ;
}

#ifdef __CSC_SYSTEM_WINDOWS__
inline exports FLAG GlobalRuntime::process_pid () {
	return _XVALUE_<FLAG> (api::GetCurrentProcessId ()) ;
}

inline exports Buffer<BYTE ,ARGC<128>> GlobalRuntime::process_info (FLAG pid) {
	Buffer<BYTE ,ARGC<128>> ret ;
	auto rax = ByteWriter<BYTE> (PhanBuffer<BYTE>::make (ret)) ;
	if switch_case (TRUE) {
		const auto r1x = UniqueRef<HANDLE> ([&] (HANDLE &me) {
			me = api::OpenProcess (PROCESS_QUERY_INFORMATION ,FALSE ,VARY (pid)) ;
		} ,[] (HANDLE &me) {
			if (me == NULL)
				return ;
			api::CloseHandle (me) ;
		}) ;
		if (r1x == NULL)
			discard ;
		rax << VAR64 (pid) ;
		rax << ByteWriter<BYTE>::GAP ;
		rax << _PCSTRU8_ ("windows") ;
		rax << ByteWriter<BYTE>::GAP ;
		auto rbx = ARRAY4<FILETIME> () ;
		_ZERO_ (rbx[0]) ;
		_ZERO_ (rbx[1]) ;
		_ZERO_ (rbx[2]) ;
		_ZERO_ (rbx[3]) ;
		api::GetProcessTimes (r1x ,DEPTR[rbx[0]] ,DEPTR[rbx[1]] ,DEPTR[rbx[2]] ,DEPTR[rbx[3]]) ;
		const auto r2x = (VAR64 (rbx[0].dwHighDateTime) << 32) | VAR64 (rbx[0].dwLowDateTime) ;
		rax << VAR64 (r2x) ;
		rax << ByteWriter<BYTE>::GAP ;
	}
	rax << ByteWriter<BYTE>::EOS ;
	return _MOVE_ (ret) ;
}

inline exports FLAG GlobalRuntime::process_info_pid (const PhanBuffer<const STRU8> &info) {
	_DEBUG_ASSERT_ (info.size () == 128) ;
	auto rax = ByteReader<BYTE> (info) ;
	const auto r1x = rax.template read<VAR64> () ;
	_DYNAMIC_ASSERT_ (r1x >= VAR32_MIN && r1x <= VAR32_MAX) ;
	return FLAG (r1x) ;
}
#endif

#ifdef __CSC_SYSTEM_LINUX__
inline exports FLAG GlobalRuntime::process_pid () {
	return _XVALUE_<FLAG> (syscall (SYS_getpid)) ;
}

inline exports Buffer<BYTE ,ARGC<128>> GlobalRuntime::process_info (FLAG pid) {
	Buffer<BYTE ,ARGC<128>> ret ;
	auto rax = ByteWriter<BYTE> (PhanBuffer<BYTE>::make (ret)) ;
	if switch_case (TRUE) {
		const auto r1x = api::getpgid (api::pid_t (pid)) ;
		if (r1x < 0)
			discard ;
		rax << VAR64 (pid) ;
		rax << ByteWriter<BYTE>::GAP ;
		rax << _PCSTRU8_ ("linux") ;
		rax << ByteWriter<BYTE>::GAP ;
		rax << VAR64 (r1x) ;
		rax << ByteWriter<BYTE>::GAP ;
		const auto r2x = api::getsid (api::pid_t (pid)) ;
		rax << VAR64 (r2x) ;
		rax << ByteWriter<BYTE>::GAP ;
	}
	rax << ByteWriter<BYTE>::EOS ;
	return _MOVE_ (ret) ;
}

inline exports FLAG GlobalRuntime::process_info_pid (const PhanBuffer<const STRU8> &info) {
	_DEBUG_ASSERT_ (info.size () == 128) ;
	auto rax = ByteReader<BYTE> (info) ;
	const auto r1x = rax.template read<VAR64> () ;
	_DYNAMIC_ASSERT_ (r1x >= VAR32_MIN && r1x <= VAR32_MAX) ;
	return FLAG (r1x) ;
}
#endif

#ifndef __CSC_COMPILER_GNUC__
inline exports void GlobalRuntime::process_exit[[noreturn]] () {
	api::quick_exit (EXIT_FAILURE) ;
}
#endif

#ifdef __CSC_COMPILER_GNUC__
inline exports void GlobalRuntime::process_exit[[noreturn]] () {
	//@error: fuck g++4.8
	api::exit (EXIT_FAILURE) ;
}
#endif

inline exports void GlobalRuntime::process_abort[[noreturn]] () {
	api::terminate () ;
}

#ifdef __CSC_DEPRECATED__
template <class CONT>
class Coroutine<CONT>::Implement {
private:
	struct CONTEXT_EBP {
		jmp_buf mEbp ;
	} ;

	static constexpr auto CONTEXT_EBP_SIZE = _ALIGNOF_ (CONTEXT_EBP) - 1 + _SIZEOF_ (CONTEXT_EBP) ;
	static constexpr auto STACK_FRAME_SIZE = 65536 ;

	struct BREAKPOINT {
		DEF<BYTE[CONTEXT_EBP_SIZE]> mContextEbp ;
		ARRAY3<LENGTH> mStackPoint ;
		DEF<BYTE[STACK_FRAME_SIZE]> mStackFrame ;
	} ;

private:
	friend Coroutine<CONT> ;

public:
	imports_static void init_break_point (PTR<AnyRef<void>> bp) {
		auto tmp = BREAKPOINT () ;
		_ZERO_ (tmp) ;
		tmp.mStackPoint[0] = _ADDRESS_ (DEPTR[bp]) ;
		tmp.mStackPoint[1] = 0 ;
		tmp.mStackPoint[2] = 0 ;
		DEREF[bp] = AnyRef<BREAKPOINT>::make (_MOVE_ (tmp)) ;
	}

	imports_static void store_break_point (PTR<AnyRef<void>> bp) noexcept {
		auto &r1x = bp->rebind<BREAKPOINT> ().self ;
		_DEBUG_ASSERT_ (r1x.mStackPoint[0] != 0) ;
		r1x.mStackPoint[1] = _ADDRESS_ (DEPTR[bp]) ;
		const auto r2x = r1x.mStackPoint[1] - r1x.mStackPoint[0] ;
		_DEBUG_ASSERT_ (_ABS_ (r2x) <= _SIZEOF_ (decltype (r1x.mStackFrame))) ;
		const auto r3x = _EBOOL_ (r2x < 0) ;
		auto &r4x = _LOAD_UNSAFE_<ARR<BYTE>> (r1x.mStackPoint[r3x]) ;
		BasicProc::mem_copy (PTRTOARR[r1x.mStackFrame] ,r4x ,_ABS_ (r2x)) ;
		auto &r5x = load_context_ebp (r1x.mContextEbp) ;
		const auto r6x = setjmp (r5x.mEbp) ;
		_STATIC_UNUSED_ (r6x) ;
	}

	imports_static void goto_break_point (PTR<AnyRef<void>> bp) noexcept {
		auto &r1x = bp->rebind<BREAKPOINT> ().self ;
		_DEBUG_ASSERT_ (r1x.mStackPoint[0] != 0) ;
		_DEBUG_ASSERT_ (r1x.mStackPoint[1] != 0) ;
		r1x.mStackPoint[2] = _ADDRESS_ (DEPTR[bp]) ;
		_STATIC_WARNING_ ("mark") ;
		_DEBUG_ASSERT_ (r1x.mStackPoint[2] == r1x.mStackPoint[1]) ;
		const auto r2x = r1x.mStackPoint[1] - r1x.mStackPoint[0] ;
		_DEBUG_ASSERT_ (_ABS_ (r2x) <= _SIZEOF_ (decltype (r1x.mStackFrame))) ;
		const auto r3x = _EBOOL_ (r2x < 0) ;
		auto &r4x = _LOAD_UNSAFE_<ARR<BYTE>> (r1x.mStackPoint[r3x]) ;
		BasicProc::mem_copy (r4x ,PTRTOARR[r1x.mStackFrame] ,_ABS_ (r2x)) ;
		auto &r5x = load_context_ebp (r1x.mContextEbp) ;
		api::longjmp (r5x.mEbp ,1) ;
	}

	imports_static CONTEXT_EBP &load_context_ebp (DEF<BYTE[CONTEXT_EBP_SIZE]> &ebp) noexcept {
		const auto r1x = _ALIGNAS_ (_ADDRESS_ (DEPTR[ebp]) ,_ALIGNOF_ (CONTEXT_EBP)) ;
		return _LOAD_UNSAFE_<CONTEXT_EBP> (r1x) ;
	}
} ;

template <class CONT>
inline exports void Coroutine<CONT>::init_break_point (AnyRef<void> &bp) {
	Implement::init_break_point (DEPTR[bp]) ;
}

template <class CONT>
inline exports void Coroutine<CONT>::store_break_point (AnyRef<void> &bp) noexcept {
	Implement::store_break_point (DEPTR[bp]) ;
}

template <class CONT>
inline exports void Coroutine<CONT>::goto_break_point (AnyRef<void> &bp) noexcept {
	Implement::goto_break_point (DEPTR[bp]) ;
}
#endif

class RandomService::Implement
	:public RandomService::Abstract {
private:
	SharedRef<api::random_device> mRandomSeed ;
	AutoRef<api::mt19937> mRandomDevice ;

public:
	Implement () {
		mRandomSeed = SharedRef<api::random_device>::make () ;
		mRandomDevice = AutoRef<api::mt19937>::make (CHAR (mRandomSeed.self ())) ;
	}

	VAR entropy () const override {
		return VAR (mRandomSeed->entropy ()) ;
	}

	void reset_seed (VAR seed_) override {
		mRandomDevice = AutoRef<api::mt19937>::make (CHAR (seed_)) ;
	}

	VAR random_value () popping override {
		return VAR (mRandomDevice.self ()) ;
	}

	void random_skip (LENGTH len) override {
#pragma push_macro ("discard")
#undef discard
		mRandomDevice->discard (len) ;
#pragma pop_macro ("discard")
	}
} ;

inline exports RandomService::RandomService () {
	mThis = StrongRef<Implement>::make () ;
}
} ;