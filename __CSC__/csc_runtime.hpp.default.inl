#pragma once

#ifndef __CSC_RUNTIME__
#error "��(�á㧥�� ;)�� : require 'csc_runtime.hpp'"
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
#error "��(�á㧥�� ;)�� : require 'Windows.h'"
#endif
#endif

#ifdef __CSC_SYSTEM_LINUX__
#ifdef __CSC_DEPRECATED__
#include <unistd.h>
#include <sys/syscall.h>
#endif
#endif

#ifdef __CSC_DEPRECATED__
#pragma region
#pragma warning (push)
#ifdef __CSC_COMPILER_MSVC__
#pragma warning (disable :5039)
#endif
#include <cstdlib>
#include <locale>
#include <chrono>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <cmath>
#include <random>

#include <setjmp.h>
#pragma warning (pop)
#pragma endregion
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
using std::mutex ;
using std::recursive_mutex ;
using std::memory_order ;
using std::atomic ;
using std::unique_lock ;
using std::condition_variable ;
using std::thread ;
using std::random_device ;
using std::mt19937 ;

namespace chrono {
using std::chrono::duration ;
using std::chrono::time_point ;
using std::chrono::hours ;
using std::chrono::minutes ;
using std::chrono::seconds ;
using std::chrono::milliseconds ;
using std::chrono::microseconds ;
using std::chrono::nanoseconds ;
using std::chrono::system_clock ;

using std::chrono::duration_cast ;
using std::chrono::time_point_cast ;
} ;

namespace this_thread {
using std::this_thread::sleep_for ;
using std::this_thread::sleep_until ;
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

class Duration::Implement {
private:
	friend GlobalRuntime ;
	friend ConditionLock ;
	friend TimePoint ;
	api::chrono::system_clock::duration mDuration ;

public:
	Implement () = delete ;

	explicit Implement (const LENGTH &milliseconds_) {
		const auto r1x = api::chrono::milliseconds (milliseconds_) ;
		mDuration = api::chrono::duration_cast<api::chrono::system_clock::duration> (r1x) ;
	}

	explicit Implement (const ARRAY6<LENGTH> &time_) {
		const auto r1x = api::chrono::hours (time_[0]) ;
		const auto r2x = api::chrono::minutes (time_[1]) ;
		const auto r3x = api::chrono::seconds (time_[2]) ;
		const auto r4x = api::chrono::milliseconds (time_[3]) ;
		const auto r5x = api::chrono::microseconds (time_[4]) ;
		const auto r6x = api::chrono::nanoseconds (time_[5]) ;
		const auto r7x = r1x + r2x + r3x + r4x + r5x + r6x ;
		mDuration = api::chrono::duration_cast<api::chrono::system_clock::duration> (r7x) ;
	}

	explicit Implement (const api::chrono::system_clock::duration &time_) {
		mDuration = api::chrono::duration_cast<api::chrono::system_clock::duration> (time_) ;
	}

	LENGTH hours () const {
		const auto r1x = api::chrono::duration_cast<api::chrono::hours> (mDuration) ;
		return r1x.count () ;
	}

	LENGTH minutes () const {
		const auto r1x = api::chrono::duration_cast<api::chrono::minutes> (mDuration) ;
		return r1x.count () ;
	}

	LENGTH seconds () const {
		const auto r1x = api::chrono::duration_cast<api::chrono::seconds> (mDuration) ;
		return r1x.count () ;
	}

	LENGTH miliseconds () const {
		const auto r1x = api::chrono::duration_cast<api::chrono::seconds> (mDuration) ;
		return r1x.count () ;
	}

	LENGTH microseconds () const {
		const auto r1x = api::chrono::duration_cast<api::chrono::microseconds> (mDuration) ;
		return r1x.count () ;
	}

	LENGTH nanoseconds () const {
		const auto r1x = api::chrono::duration_cast<api::chrono::nanoseconds> (mDuration) ;
		return r1x.count () ;
	}

	Duration add (const Implement &that) const {
		const auto r1x = mDuration + that.mDuration ;
		const auto r2x = api::chrono::duration_cast<api::chrono::system_clock::duration> (r1x) ;
		const auto r3x = StrongRef<Duration::Implement>::make (r2x) ;
		return Duration (r3x) ;
	}

	Duration sub (const Implement &that) const {
		const auto r1x = mDuration - that.mDuration ;
		const auto r2x = api::chrono::duration_cast<api::chrono::system_clock::duration> (r1x) ;
		const auto r3x = StrongRef<Duration::Implement>::make (r2x) ;
		return Duration (r3x) ;
	}
} ;

inline exports Duration::Duration (const LENGTH &milliseconds_) {
	mThis = StrongRef<Implement>::make (milliseconds_) ;
}

inline exports Duration::Duration (const ARRAY6<LENGTH> &time_) {
	mThis = StrongRef<Implement>::make (time_) ;
}

inline exports Duration::Duration (const StrongRef<Implement> &this_) {
	mThis = _MOVE_ (this_) ;
}

inline exports LENGTH Duration::hours () const {
	return mThis->hours () ;
}

inline exports LENGTH Duration::minutes () const {
	return mThis->minutes () ;
}

inline exports LENGTH Duration::seconds () const {
	return mThis->seconds () ;
}

inline exports LENGTH Duration::miliseconds () const {
	return mThis->miliseconds () ;
}

inline exports LENGTH Duration::microseconds () const {
	return mThis->microseconds () ;
}

inline exports LENGTH Duration::nanoseconds () const {
	return mThis->nanoseconds () ;
}

inline exports Duration Duration::add (const Duration &that) const {
	return mThis->add (that.mThis) ;
}

inline exports Duration Duration::sub (const Duration &that) const {
	return mThis->sub (that.mThis) ;
}

class TimePoint::Implement {
private:
	friend GlobalRuntime ;
	friend ConditionLock ;
	api::chrono::system_clock::time_point mTimePoint ;

public:
	Implement () = delete ;

	explicit Implement (const ARRAY8<LENGTH> &time_) {
		auto rax = api::tm () ;
		_ZERO_ (rax) ;
		const auto r1x = _EBOOL_ (time_[0] > 0) * (time_[0] - 1900) ;
		rax.tm_year = VAR32 (r1x) ;
		const auto r2x = _EBOOL_ (time_[1] > 0) * (time_[1] - 1) ;
		rax.tm_mon = VAR32 (r2x) ;
		rax.tm_mday = VAR32 (time_[2]) ;
		const auto r3x = _EBOOL_ (time_[3] > 0) * (time_[3] - 1) ;
		rax.tm_wday = VAR32 (r3x) ;
		const auto r4x = _EBOOL_ (time_[4] > 0) * (time_[4] - 1) ;
		rax.tm_yday = VAR32 (r4x) ;
		rax.tm_hour = VAR32 (time_[5]) ;
		rax.tm_min = VAR32 (time_[6]) ;
		rax.tm_sec = VAR32 (time_[7]) ;
		const auto r5x = api::mktime (DEPTR[rax]) ;
		mTimePoint = api::chrono::system_clock::from_time_t (r5x) ;
	}

	explicit Implement (const api::chrono::system_clock::time_point &time_) {
		mTimePoint = api::chrono::time_point_cast<api::chrono::system_clock::duration> (time_) ;
	}

#ifdef __CSC_COMPILER_MSVC__
	ARRAY8<LENGTH> calendar () const {
		ARRAY8<LENGTH> ret ;
		ret.fill (0) ;
		const auto r1x = api::time_t (api::chrono::system_clock::to_time_t (mTimePoint)) ;
		auto rax = api::tm () ;
		_ZERO_ (rax) ;
		api::localtime_s (DEPTR[rax] ,DEPTR[r1x]) ;
		ret[0] = rax.tm_year + 1900 ;
		ret[1] = rax.tm_mon + 1 ;
		ret[2] = rax.tm_mday ;
		ret[3] = rax.tm_wday + 1 ;
		ret[4] = rax.tm_yday + 1 ;
		ret[5] = rax.tm_hour ;
		ret[6] = rax.tm_min ;
		ret[7] = rax.tm_sec ;
		return _MOVE_ (ret) ;
	}
#endif

#ifndef __CSC_COMPILER_MSVC__
	ARRAY8<LENGTH> calendar () const {
		ARRAY8<LENGTH> ret ;
		ret.fill (0) ;
		const auto r1x = api::time_t (api::chrono::system_clock::to_time_t (mTimePoint)) ;
		auto rax = api::tm () ;
		_ZERO_ (rax) ;
		//@warn: not thread-safe due to internel storage
		const auto r2x = api::localtime (DEPTR[r1x]) ;
		_DEBUG_ASSERT_ (r2x != NULL) ;
		rax = DEREF[r2x] ;
		ret[0] = rax.tm_year + 1900 ;
		ret[1] = rax.tm_mon + 1 ;
		ret[2] = rax.tm_mday ;
		ret[3] = rax.tm_wday + 1 ;
		ret[4] = rax.tm_yday + 1 ;
		ret[5] = rax.tm_hour ;
		ret[6] = rax.tm_min ;
		ret[7] = rax.tm_sec ;
		return _MOVE_ (ret) ;
	}
#endif

	TimePoint add (const Duration::Implement &that) const {
		const auto r1x = mTimePoint + that.mDuration ;
		const auto r2x = api::chrono::time_point_cast<api::chrono::system_clock::duration> (r1x) ;
		const auto r3x = StrongRef<TimePoint::Implement>::make (r2x) ;
		return TimePoint (r3x) ;
	}

	Duration sub (const TimePoint::Implement &that) const {
		const auto r1x = mTimePoint - that.mTimePoint ;
		const auto r2x = api::chrono::duration_cast<api::chrono::system_clock::duration> (r1x) ;
		const auto r3x = StrongRef<Duration::Implement>::make (r2x) ;
		return Duration (r3x) ;
	}
} ;

inline exports TimePoint::TimePoint (const ARRAY8<LENGTH> &time_) {
	mThis = StrongRef<Implement>::make (time_) ;
}

inline exports TimePoint::TimePoint (const StrongRef<Implement> &this_) {
	mThis = _MOVE_ (this_) ;
}

inline exports ARRAY8<LENGTH> TimePoint::calendar () const {
	return mThis->calendar () ;
}

inline exports TimePoint TimePoint::add (const Duration &that) const {
	return mThis->add (that.mThis) ;
}

inline exports Duration TimePoint::sub (const TimePoint &that) const {
	return mThis->sub (that.mThis) ;
}

class Atomic::Implement {
private:
	api::atomic<VAR> mAtomic ;

public:
	Implement () {
		mAtomic = 0 ;
	}

	VAR fetch () const {
		return mAtomic.load (api::memory_order::memory_order_seq_cst) ;
	}

	VAR compare_exchange (const VAR &expect ,const VAR &data) popping {
		VAR ret = expect ;
		const auto r1x = mAtomic.compare_exchange_strong (ret ,data ,api::memory_order::memory_order_seq_cst) ;
		if (r1x)
			ret = data ;
		return std::move (ret) ;
	}

	void store (const VAR &data) {
		mAtomic.store (data ,api::memory_order::memory_order_seq_cst) ;
	}

	VAR increase () popping {
		const auto r1x = mAtomic.fetch_add (1 ,api::memory_order::memory_order_seq_cst) ;
		return r1x + 1 ;
	}

	VAR decrease () popping {
		const auto r1x = mAtomic.fetch_sub (1 ,api::memory_order::memory_order_seq_cst) ;
		return r1x - 1 ;
	}
} ;

inline exports Atomic::Atomic () {
	mThis = StrongRef<Implement>::make () ;
}

inline exports VAR Atomic::fetch () const {
	return mThis->fetch () ;
}

inline exports VAR Atomic::compare_exchange (const VAR &expect ,const VAR &data) popping {
	return mThis->compare_exchange (expect ,data) ;
}

inline exports void Atomic::store (const VAR &data) {
	return mThis->store (data) ;
}

inline exports VAR Atomic::increase () popping {
	return mThis->increase () ;
}

inline exports VAR Atomic::decrease () popping {
	return mThis->decrease () ;
}

class Mutex::Implement {
private:
	friend UniqueLock ;
	api::mutex mMutex ;

public:
	Implement () = default ;

	void lock () {
		mMutex.lock () ;
	}

	BOOL try_lock () popping {
		return mMutex.try_lock () ;
	}

	void unlock () {
		mMutex.unlock () ;
	}
} ;

inline exports Mutex::Mutex () {
	mThis = StrongRef<Implement>::make () ;
}

inline exports void Mutex::lock () {
	mThis->lock () ;
}

inline exports BOOL Mutex::try_lock () popping {
	return mThis->try_lock () ;
}

inline exports void Mutex::unlock () {
	mThis->unlock () ;
}

class RecursiveMutex::Implement {
private:
	api::recursive_mutex mMutex ;

public:
	Implement () = default ;

	void lock () {
		mMutex.lock () ;
	}

	BOOL try_lock () popping {
		return mMutex.try_lock () ;
	}

	void unlock () {
		mMutex.unlock () ;
	}
} ;

inline exports RecursiveMutex::RecursiveMutex () {
	mThis = StrongRef<Implement>::make () ;
}

inline exports void RecursiveMutex::lock () {
	mThis->lock () ;
}

inline exports BOOL RecursiveMutex::try_lock () popping {
	return mThis->try_lock () ;
}

inline exports void RecursiveMutex::unlock () {
	mThis->unlock () ;
}

class UniqueLock::Implement {
private:
	friend ConditionLock ;
	struct Detail ;
	PhanRef<Mutex> mMutex ;
	PhanRef<ConditionLock> mCondition ;
	api::unique_lock<api::mutex> mUniqueLock ;

public:
	Implement () = delete ;

	explicit Implement (Mutex &mutex_ ,ConditionLock &condition) {
		mMutex = PhanRef<Mutex>::make (mutex_) ;
		mCondition = PhanRef<ConditionLock>::make (condition) ;
	}

	void lock () {
		auto &r1x = mMutex->native () ;
		mUniqueLock = api::unique_lock<api::mutex> (r1x.mMutex) ;
	}

	void unlock () {
		mUniqueLock = api::unique_lock<api::mutex> () ;
	}
} ;

inline exports UniqueLock::UniqueLock (Mutex &mutex_ ,ConditionLock &condition) {
	mThis = StrongRef<Implement>::make (mutex_ ,condition) ;
}

inline exports void UniqueLock::lock () const {
	mThis->lock () ;
}

inline exports void UniqueLock::unlock () const {
	mThis->unlock () ;
}

class ConditionLock::Implement {
private:
	api::condition_variable mCondition ;

public:
	Implement () = default ;

	void wait (const UniqueLock &lock_) {
		mCondition.wait (lock_.native ().mUniqueLock) ;
	}

	void wait (const UniqueLock &lock_ ,const TimePoint &time_) {
		auto &r1x = time_.native () ;
		mCondition.wait_until (lock_.native ().mUniqueLock ,r1x.mTimePoint) ;
	}

	void wait (const UniqueLock &lock_ ,const Duration &time_) {
		auto &r1x = time_.native () ;
		mCondition.wait_for (lock_.native ().mUniqueLock ,r1x.mDuration) ;
	}

	void yield (const UniqueLock &lock_) {
		const auto r1x = api::chrono::milliseconds (0) ;
		mCondition.wait_for (lock_.native ().mUniqueLock ,r1x) ;
	}

	void notify () {
		mCondition.notify_all () ;
	}
} ;

inline exports ConditionLock::ConditionLock () {
	mThis = StrongRef<Implement>::make () ;
}

inline exports void ConditionLock::wait (const UniqueLock &lock_) {
	mThis->wait (lock_) ;
}

inline exports void ConditionLock::wait (const UniqueLock &lock_ ,const TimePoint &time_) {
	mThis->wait (lock_ ,time_) ;
}

inline exports void ConditionLock::wait (const UniqueLock &lock_ ,const Duration &time_) {
	mThis->wait (lock_ ,time_) ;
}

inline exports void ConditionLock::yield (const UniqueLock &lock_) {
	mThis->yield (lock_) ;
}

inline exports void ConditionLock::notify () {
	mThis->notify () ;
}

class Thread::Implement {
private:
	StrongRef<Binder> mRunnable ;
	api::thread mThread ;

public:
	Implement () = delete ;

	explicit Implement (const StrongRef<Binder> &runnable) {
		mRunnable = runnable ;
		const auto r1x = PhanRef<Binder>::make (mRunnable.self) ;
		mThread = api::thread (Detail::Runnable (r1x)) ;
	}

	void join () {
		mThread.join () ;
	}
} ;

inline exports Thread::Thread (const StrongRef<Binder> &runnable) {
	mThis = StrongRef<Implement>::make (runnable) ;
}

inline exports void Thread::join () {
	mThis->join () ;
}

inline exports TimePoint GlobalRuntime::clock_now () {
	using Implement = REMOVE_CVR_TYPE<DEF<decltype (_NULL_<TimePoint> ().native ())>> ;
	const auto r1x = api::chrono::system_clock::now () ;
	const auto r2x = StrongRef<Implement>::make (r1x) ;
	return TimePoint (r2x) ;
}

inline exports TimePoint GlobalRuntime::clock_epoch () {
	using Implement = REMOVE_CVR_TYPE<DEF<decltype (_NULL_<TimePoint> ().native ())>> ;
	const auto r1x = api::chrono::system_clock::duration::zero () ;
	const auto r2x = api::chrono::system_clock::time_point (r1x) ;
	const auto r3x = StrongRef<Implement>::make (r2x) ;
	return TimePoint (r3x) ;
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

inline exports void GlobalRuntime::thread_sleep (const Duration &time_) {
	auto &r1x = time_.native () ;
	api::this_thread::sleep_for (r1x.mDuration) ;
}

inline exports void GlobalRuntime::thread_sleep (const TimePoint &time_) {
	auto &r1x = time_.native () ;
	api::this_thread::sleep_until (r1x.mTimePoint) ;
}

inline exports void GlobalRuntime::thread_yield () {
	api::this_thread::yield () ;
}

inline exports LENGTH GlobalRuntime::thread_concurrency () {
	return LENGTH (api::thread::hardware_concurrency ()) ;
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

inline exports Buffer<BYTE ,ARGC<128>> GlobalRuntime::process_info (const FLAG &pid) {
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

inline exports Buffer<BYTE ,ARGC<128>> GlobalRuntime::process_info (const FLAG &pid) {
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
	imports_static void init_break_point (const PTR<AnyRef<void>> &bp) {
		auto tmp = BREAKPOINT () ;
		_ZERO_ (tmp) ;
		tmp.mStackPoint[0] = _ADDRESS_ (DEPTR[bp]) ;
		tmp.mStackPoint[1] = 0 ;
		tmp.mStackPoint[2] = 0 ;
		DEREF[bp] = AnyRef<BREAKPOINT>::make (_MOVE_ (tmp)) ;
	}

	imports_static void store_break_point (const PTR<AnyRef<void>> &bp) noexcept {
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

	imports_static void goto_break_point (const PTR<AnyRef<void>> &bp) noexcept {
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

	void reset_seed (const VAR &seed_) override {
		mRandomDevice = AutoRef<api::mt19937>::make (CHAR (seed_)) ;
	}

	VAR random_value () popping override {
		return VAR (mRandomDevice.self ()) ;
	}

	void random_skip (const LENGTH &len) override {
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