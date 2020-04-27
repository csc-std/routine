﻿#pragma once

#ifndef __CSC_NETWORK__
#define __CSC_NETWORK__
#endif

#include "csc.hpp"
#include "csc_basic.hpp"
#include "csc_extend.hpp"
#include "csc_array.hpp"
#include "csc_math.hpp"
#include "csc_stream.hpp"
#include "csc_string.hpp"
#include "csc_runtime.hpp"
#include "csc_thread.hpp"

namespace CSC {
class TCPSocket {
public:
	class Listener ;

private:
	class Implement ;
	AnyRef<void> mThis ;

public:
	TCPSocket () = delete ;

	explicit TCPSocket (const String<STRU8> &ip_addr) ;

	String<STRU8> sock_name () const ;

	String<STRU8> peer_sock_name () const ;

	template <class _RET = NONE>
	auto listener () popping
		->DEF<DEPENDENT_TYPE<Listener ,ARGVS<_RET>>> {
		struct Dependent ;
		_DEBUG_ASSERT_ (mThis.exist ()) ;
		return DEPENDENT_TYPE<Listener ,Dependent> (mThis) ;
	}

	void link (const String<STRU8> &ip_addr) ;

	void modify_buffer (LENGTH rcv_len ,LENGTH snd_len) ;

	void modify_timeout (LENGTH timeout) ;

	void read (const PhanBuffer<BYTE> &data) ;

	template <class _ARG1>
	void read (Buffer<BYTE ,_ARG1> &data) {
		read (PhanBuffer<BYTE>::make (data)) ;
	}

	template <class _ARG1>
	inline TCPSocket &operator>> (Buffer<BYTE ,_ARG1> &data) {
		read (data) ;
		return (*this) ;
	}

	void read (const PhanBuffer<BYTE> &data ,INDEX &out_i ,LENGTH timeout) ;

	void write (const PhanBuffer<const BYTE> &data) ;

	template <class _ARG1>
	void write (const Buffer<BYTE ,_ARG1> &data) {
		write (PhanBuffer<const BYTE>::make (data)) ;
	}

	template <class _ARG1>
	inline TCPSocket &operator<< (const Buffer<BYTE ,_ARG1> &data) {
		write (data) ;
		return (*this) ;
	}

public:
	static String<STRU8> http_get (const String<STRU8> &ip_addr ,const String<STRU8> &site ,const String<STRU8> &msg ,LENGTH buffer_len ,LENGTH timeout) popping ;

	static String<STRU8> http_post (const String<STRU8> &ip_addr ,const String<STRU8> &site ,const String<STRU8> &msg ,LENGTH buffer_len ,LENGTH timeout) popping ;
} ;

class TCPSocket::Listener {
private:
	friend TCPSocket ;
	class Implement ;
	AnyRef<void> mThis ;

public:
	Listener () = delete ;

	void wait_linker () ;

	void accept () ;

private:
	explicit Listener (const AnyRef<void> &socket_) ;
} ;

class UDPSocket {
private:
	class Implement ;
	AnyRef<void> mThis ;

public:
	UDPSocket () = delete ;

	explicit UDPSocket (const String<STRU8> &ip_addr) ;

	String<STRU8> sock_name () const ;

	String<STRU8> peer_sock_name () const ;

	void link (const String<STRU8> &ip_addr) ;

	void modify_timeout (LENGTH timeout) ;

	void read (const PhanBuffer<BYTE> &data) ;

	template <class _ARG1>
	void read (Buffer<BYTE ,_ARG1> &data) {
		read (PhanBuffer<BYTE>::make (data)) ;
	}

	template <class _ARG1>
	inline UDPSocket &operator>> (Buffer<BYTE ,_ARG1> &data) {
		read (data) ;
		return (*this) ;
	}

	void read (const PhanBuffer<BYTE> &data ,INDEX &out_i ,LENGTH timeout) ;

	void write (const PhanBuffer<const BYTE> &data) ;

	template <class _ARG1>
	void write (const Buffer<BYTE ,_ARG1> &data) {
		write (PhanBuffer<const BYTE>::make (data)) ;
	}

	template <class _ARG1>
	inline UDPSocket &operator<< (const Buffer<BYTE ,_ARG1> &data) {
		write (data) ;
		return (*this) ;
	}
} ;

class NetworkService final
	:private Proxy {
private:
	exports class Abstract
		:public Interface {
	public:
		virtual void startup () = 0 ;
		virtual void shutdown () = 0 ;
		virtual String<STRU8> localhost_name () const = 0 ;
		virtual String<STRU8> localhost_addr () const = 0 ;
		virtual String<STRU8> broadcast_addr () const = 0 ;
		virtual LENGTH pref_timeout () const = 0 ;
	} ;

private:
	class Implement ;
	friend Singleton<NetworkService> ;
	Monostate<std::recursive_mutex> mMutex ;
	StrongRef<Abstract> mThis ;

public:
	void startup () {
		ScopedGuard<std::recursive_mutex> ANONYMOUS (mMutex) ;
		mThis->startup () ;
	}

	void shutdown () {
		ScopedGuard<std::recursive_mutex> ANONYMOUS (mMutex) ;
		mThis->shutdown () ;
	}

	String<STRU8> localhost_name () const {
		ScopedGuard<std::recursive_mutex> ANONYMOUS (mMutex) ;
		return mThis->localhost_name () ;
	}

	String<STRU8> localhost_addr () const {
		ScopedGuard<std::recursive_mutex> ANONYMOUS (mMutex) ;
		return mThis->localhost_addr () ;
	}

	String<STRU8> broadcast_addr () const {
		ScopedGuard<std::recursive_mutex> ANONYMOUS (mMutex) ;
		return mThis->broadcast_addr () ;
	}

	LENGTH pref_timeout () const {
		ScopedGuard<std::recursive_mutex> ANONYMOUS (mMutex) ;
		return mThis->pref_timeout () ;
	}

private:
	NetworkService () ;
} ;
} ;