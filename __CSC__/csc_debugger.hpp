﻿#pragma once

#ifndef __CSC_DEBUGGER__
#define __CSC_DEBUGGER__
#endif

#include "csc.hpp"
#include "csc_core.hpp"
#include "csc_basic.hpp"
#include "csc_extend.hpp"
#include "csc_array.hpp"
#include "csc_math.hpp"
#include "csc_images.hpp"
#include "csc_geometry.hpp"
#include "csc_stream.hpp"
#include "csc_string.hpp"
#include "csc_runtime.hpp"
#include "csc_thread.hpp"
#include "csc_graphics.hpp"
#include "csc_filesystem.hpp"
#include "csc_network.hpp"
#include "csc_database.hpp"

namespace CSC {
class ConsoleService
	:private Proxy {
public:
	static constexpr auto OPTION_DEFAULT = EFLAG (0) ;
	static constexpr auto OPTION_NO_PRINT = EFLAG (1) ;
	static constexpr auto OPTION_NO_FATAL = EFLAG (2) ;
	static constexpr auto OPTION_NO_ERROR = EFLAG (3) ;
	static constexpr auto OPTION_NO_WARN = EFLAG (4) ;
	static constexpr auto OPTION_NO_INFO = EFLAG (5) ;
	static constexpr auto OPTION_NO_DEBUG = EFLAG (6) ;
	static constexpr auto OPTION_NO_VERBOSE = EFLAG (7) ;
	static constexpr auto OPTION_ALWAYS_FLUSH = EFLAG (8) ;
	static constexpr auto OPTION_TESTING = EFLAG (9) ;

private:
	using Binder = typename TextWriter<STR>::Binder ;

	exports class Abstract
		:public Interface {
	public:
		virtual LENGTH buffer_size () const = 0 ;
		virtual void enable_option (const EFLAG &option) = 0 ;
		virtual void disable_option (const EFLAG &option) = 0 ;
		virtual void print (const Binder &msg) = 0 ;
		virtual void fatal (const Binder &msg) = 0 ;
		virtual void error (const Binder &msg) = 0 ;
		virtual void warn (const Binder &msg) = 0 ;
		virtual void info (const Binder &msg) = 0 ;
		virtual void debug (const Binder &msg) = 0 ;
		virtual void verbose (const Binder &msg) = 0 ;
		virtual void attach_log (const String<STR> &path) = 0 ;
		virtual void log (const PhanBuffer<const STR> &tag ,const Binder &msg) = 0 ;
		virtual void show () = 0 ;
		virtual void hide () = 0 ;
		virtual void pause () = 0 ;
		virtual void clear () = 0 ;
	} ;

	struct Private {
		template <class...>
		class ImplBinder ;

		class Implement ;
	} ;

	using Implement = typename Private::Implement ;

private:
	friend Singleton<ConsoleService> ;
	Monostate<RecursiveMutex> mMutex ;
	StrongRef<Abstract> mThis ;

public:
	LENGTH buffer_size () const {
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		return mThis->buffer_size () ;
	}

	void enable_option (const EFLAG &option) {
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		mThis->enable_option (option) ;
	}

	void disable_option (const EFLAG &option) {
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		mThis->disable_option (option) ;
	}

	template <class... _ARGS>
	void print (const _ARGS &...msg) {
		struct Dependent ;
		using ImplBinder = DEPENDENT_TYPE<DEF<typename Private::template ImplBinder<_ARGS...>> ,Dependent> ;
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		mThis->print (ImplBinder (msg...)) ;
	}

	template <class... _ARGS>
	void fatal (const _ARGS &...msg) {
		struct Dependent ;
		using ImplBinder = DEPENDENT_TYPE<DEF<typename Private::template ImplBinder<_ARGS...>> ,Dependent> ;
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		mThis->fatal (ImplBinder (msg...)) ;
	}

	template <class... _ARGS>
	void error (const _ARGS &...msg) {
		struct Dependent ;
		using ImplBinder = DEPENDENT_TYPE<DEF<typename Private::template ImplBinder<_ARGS...>> ,Dependent> ;
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		mThis->error (ImplBinder (msg...)) ;
	}

	template <class... _ARGS>
	void warn (const _ARGS &...msg) {
		struct Dependent ;
		using ImplBinder = DEPENDENT_TYPE<DEF<typename Private::template ImplBinder<_ARGS...>> ,Dependent> ;
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		mThis->warn (ImplBinder (msg...)) ;
	}

	template <class... _ARGS>
	void info (const _ARGS &...msg) {
		struct Dependent ;
		using ImplBinder = DEPENDENT_TYPE<DEF<typename Private::template ImplBinder<_ARGS...>> ,Dependent> ;
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		mThis->info (ImplBinder (msg...)) ;
	}

	template <class... _ARGS>
	void debug (const _ARGS &...msg) {
		struct Dependent ;
		using ImplBinder = DEPENDENT_TYPE<DEF<typename Private::template ImplBinder<_ARGS...>> ,Dependent> ;
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		mThis->debug (ImplBinder (msg...)) ;
	}

	template <class... _ARGS>
	void verbose (const _ARGS &...msg) {
		struct Dependent ;
		using ImplBinder = DEPENDENT_TYPE<DEF<typename Private::template ImplBinder<_ARGS...>> ,Dependent> ;
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		mThis->verbose (ImplBinder (msg...)) ;
	}

	void attach_log (const String<STR> &path) {
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		mThis->attach_log (path) ;
	}

	template <class... _ARGS>
	void log (const String<STR> &tag ,const _ARGS &...msg) {
		struct Dependent ;
		using ImplBinder = DEPENDENT_TYPE<DEF<typename Private::template ImplBinder<_ARGS...>> ,Dependent> ;
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		mThis->log (tag.raw () ,ImplBinder (msg...)) ;
	}

	void show () {
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		mThis->show () ;
	}

	void pause () {
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		mThis->pause () ;
	}

	void clear () {
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		mThis->clear () ;
	}

	void hide () {
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		mThis->hide () ;
	}

private:
	ConsoleService () ;
} ;

template <class... UNITS>
class ConsoleService::Private::ImplBinder
	:public Binder {
private:
	TupleBinder<const UNITS...> mBinder ;

public:
	explicit ImplBinder (const UNITS &...initval)
		:mBinder (initval...) {}

	void friend_write (TextWriter<STR> &writer) const override {
		template_write (writer ,mBinder) ;
	}

private:
	void template_write (TextWriter<STR> &writer ,const Tuple<> &binder) const {
		_STATIC_WARNING_ ("noop") ;
	}

	template <class... _ARGS>
	void template_write (TextWriter<STR> &writer ,const Tuple<_ARGS...> &binder) const {
		writer << binder.one () ;
		template_write (writer ,binder.rest ()) ;
	}
} ;

class DebuggerService
	:private Proxy {
private:
	exports class Abstract
		:public Interface {
	public:
		virtual void abort_once_invoked_exit (const BOOL &flag) = 0 ;
		virtual void output_memory_leaks_report (const BOOL &flag) = 0 ;
		virtual Array<LENGTH> captrue_stack_trace () side_effects = 0 ;
		virtual Array<String<STR>> symbol_from_address (const Array<LENGTH> &list) side_effects = 0 ;
	} ;

	struct Private {
		class Implement ;
	} ;

	using Implement = typename Private::Implement ;

private:
	friend Singleton<DebuggerService> ;
	Monostate<RecursiveMutex> mMutex ;
	StrongRef<Abstract> mThis ;

public:
	void abort_once_invoked_exit (const BOOL &flag) {
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		mThis->abort_once_invoked_exit (flag) ;
	}

	void output_memory_leaks_report (const BOOL &flag) {
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		mThis->output_memory_leaks_report (flag) ;
	}

	Array<LENGTH> captrue_stack_trace () side_effects {
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		return mThis->captrue_stack_trace () ;
	}

	Array<String<STR>> symbol_from_address (const Array<LENGTH> &list) side_effects {
		ScopedGuard<RecursiveMutex> ANONYMOUS (mMutex) ;
		return mThis->symbol_from_address (list) ;
	}

private:
	DebuggerService () ;
} ;
} ;