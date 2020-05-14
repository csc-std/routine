﻿#pragma once

#ifndef __CSC_NETWORK__
#error "∑(っ°Д° ;)っ : require 'csc_network.hpp'"
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

#ifndef _INC_WINDOWS
#error "∑(っ°Д° ;)っ : require 'Windows.h'"
#endif

#ifdef _WINSOCKAPI_
#ifndef _WINSOCK2API_
#error "∑(っ°Д° ;)っ : require 'WIN32_LEAN_AND_MEAN' before 'Windows.h'"
#endif
#endif

#ifdef __CSC_DEPRECATED__
#include <winsock2.h>
#endif

#ifndef _WINSOCKAPI_
#error "∑(っ°Д° ;)っ : require 'winsock.h'"
#endif

#ifdef __CSC_DEPRECATED__
#ifdef __CSC_COMPILER_MSVC__
#ifndef use_comment_lib_ws2_32
#define use_comment_lib_ws2_32 "ws2_32.lib"
#endif
#pragma comment (lib ,use_comment_lib_ws2_32)
#undef use_comment_lib_ws2_32
#endif
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
using ::fd_set ;

using ::bind ;
using ::select ;
using ::socket ;
using ::closesocket ;
using ::ioctlsocket ;
using ::setsockopt ;
using ::getsockopt ;
using ::listen ;
using ::accept ;
using ::connect ;
using ::recv ;
using ::send ;
using ::recvfrom ;
using ::sendto ;
using ::getsockname ;
using ::getpeername ;
using ::gethostname ;
} ;

namespace U {
inline TIMEVAL static_make_timeval (LENGTH val) {
	_DEBUG_ASSERT_ (val >= 0) ;
	TIMEVAL ret ;
	ret.tv_sec = VAR32 (val / 1000) ;
	ret.tv_usec = VAR32 ((val % 1000) * 1000) ;
	return _MOVE_ (ret) ;
}

inline String<STRU8> static_make_ipv4s (const SOCKADDR &val) {
	_STATIC_ASSERT_ (_SIZEOF_ (SOCKADDR) == _SIZEOF_ (SOCKADDR_IN)) ;
	const auto r1x = _BITWISE_CAST_<SOCKADDR_IN> (val) ;
	const auto r2x = _CALL_ ([&] () {
		PACK<WORD ,CHAR> ret ;
		auto &r3x = _CAST_<CSC::BYTE[_SIZEOF_ (WORD)]> (r1x.sin_port) ;
		auto &r4x = _CAST_<CSC::BYTE[_SIZEOF_ (CHAR)]> (r1x.sin_addr.S_un.S_addr) ;
		ByteReader<BYTE> (PhanBuffer<const CSC::BYTE>::make (r3x)) >> ret.P1 ;
		ByteReader<BYTE> (PhanBuffer<const CSC::BYTE>::make (r4x)) >> ret.P2 ;
		return _MOVE_ (ret) ;
	}) ;
	return StringProc::build_ipv4s<STRU8> (r2x) ;
}

inline SOCKADDR static_make_socket_addr (const String<STRU8> &val) {
	_STATIC_ASSERT_ (_SIZEOF_ (SOCKADDR) == _SIZEOF_ (SOCKADDR_IN)) ;
	const auto r1x = _CALL_ ([&] () {
		SOCKADDR_IN ret ;
		_ZERO_ (ret) ;
		ret.sin_family = AF_INET ;
		const auto r2x = StringProc::parse_ipv4s (val) ;
		auto &r3x = _CAST_<CSC::BYTE[_SIZEOF_ (WORD)]> (ret.sin_port) ;
		auto &r4x = _CAST_<CSC::BYTE[_SIZEOF_ (CHAR)]> (ret.sin_addr.S_un.S_addr) ;
		ByteWriter<BYTE> (PhanBuffer<CSC::BYTE>::make (r3x)) << r2x.P1 ;
		ByteWriter<BYTE> (PhanBuffer<CSC::BYTE>::make (r4x)) << r2x.P2 ;
		return _MOVE_ (ret) ;
	}) ;
	return _BITWISE_CAST_<SOCKADDR> (r1x) ;
}

inline void static_socket_bind (const SOCKET &socket_ ,const String<STRU8> &ip_addr) {
	const auto r1x = static_make_socket_addr (ip_addr) ;
	const auto r2x = api::bind (socket_ ,DEPTR[r1x] ,VAR32 (_SIZEOF_ (SOCKADDR))) ;
	_DYNAMIC_ASSERT_ (r2x != SOCKET_ERROR) ;
}

inline ARRAY2<api::fd_set> static_socket_select (const SOCKET &socket_ ,LENGTH timeout) {
#pragma warning (push)
#ifdef __CSC_COMPILER_MSVC__
#pragma warning (disable :4548)
#endif
	ARRAY2<api::fd_set> ret ;
	FD_ZERO (DEPTR[ret[0]]) ;
	FD_ZERO (DEPTR[ret[1]]) ;
	FD_SET (socket_ ,DEPTR[ret[0]]) ;
	FD_SET (socket_ ,DEPTR[ret[1]]) ;
	auto rax = static_make_timeval (timeout) ;
	while (TRUE) {
		const auto r1x = api::select (FD_SETSIZE ,DEPTR[ret[0]] ,DEPTR[ret[1]] ,NULL ,DEPTR[rax]) ;
		if (r1x >= 0)
			break ;
		_STATIC_WARNING_ ("noop") ;
	}
	_ZERO_ (rax) ;
	return _MOVE_ (ret) ;
#pragma warning (pop)
}
} ;

class TCPSocket::Implement {
private:
	class Pack {
	private:
		friend Implement ;
		friend Listener::Implement ;
		UniqueRef<SOCKET> mSocket ;
		SOCKADDR mPeer ;
		LENGTH mTimeout ;
	} ;

private:
	friend Listener::Implement ;
	SharedRef<Pack> mThis ;

public:
	Implement () = delete ;

	explicit Implement (const String<STRU8> &ip_addr) {
		mThis = SharedRef<Pack>::make () ;
		mThis->mSocket = UniqueRef<SOCKET> ([&] (SOCKET &me) {
			me = api::socket (AF_INET ,SOCK_STREAM ,IPPROTO_TCP) ;
			_DYNAMIC_ASSERT_ (me != INVALID_SOCKET) ;
		} ,[] (SOCKET &me) {
			api::closesocket (me) ;
		}) ;
		if (!ip_addr.empty ())
			U::static_socket_bind (mThis->mSocket ,ip_addr) ;
		_ZERO_ (mThis->mPeer) ;
		mThis->mTimeout = 30000 ;
	}

	String<STRU8> sock_name () const {
		auto rax = PACK<SOCKADDR ,VAR32> () ;
		_ZERO_ (rax.P1) ;
		rax.P2 = VAR32 (_SIZEOF_ (SOCKADDR)) ;
		api::getsockname (mThis->mSocket ,DEPTR[rax.P1] ,DEPTR[rax.P2]) ;
		//@info: ipv6 is not supported
		_DYNAMIC_ASSERT_ (rax.P2 == _SIZEOF_ (SOCKADDR)) ;
		return U::static_make_ipv4s (rax.P1) ;
	}

	String<STRU8> peer_sock_name () const {
		return U::static_make_ipv4s (mThis->mPeer) ;
	}

	void link (const String<STRU8> &ip_addr) {
		mThis->mPeer = U::static_make_socket_addr (ip_addr) ;
		auto rax = ULONG () ;
		rax = ULONG (1) ;
		api::ioctlsocket (mThis->mSocket ,FIONBIO ,DEPTR[rax]) ;
		const auto r1x = api::connect (mThis->mSocket ,DEPTR[mThis->mPeer] ,VAR32 (_SIZEOF_ (SOCKADDR))) ;
		rax = ULONG (0) ;
		api::ioctlsocket (mThis->mSocket ,FIONBIO ,DEPTR[rax]) ;
		if (r1x == 0)
			return ;
		//@info: state of 'this' has been changed
		if switch_case (TRUE) {
			if (r1x >= 0)
				discard ;
			const auto r2x = errno ;
			if (r2x == 0)
				discard ;
			_DYNAMIC_ASSERT_ (r2x == EINPROGRESS || r2x == EWOULDBLOCK) ;
		}
		link_confirm () ;
	}

	void modify_buffer (LENGTH rcv_len ,LENGTH snd_len) {
		_DEBUG_ASSERT_ (rcv_len >= 0 && rcv_len < VAR32_MAX) ;
		_DEBUG_ASSERT_ (snd_len >= 0 && snd_len < VAR32_MAX) ;
		const auto r1x = VAR32 (rcv_len) ;
		api::setsockopt (mThis->mSocket ,SOL_SOCKET ,SO_RCVBUF ,_CAST_<STRA[_SIZEOF_ (VAR32)]> (r1x) ,VAR32 (_SIZEOF_ (VAR32))) ;
		const auto r2x = VAR32 (snd_len) ;
		api::setsockopt (mThis->mSocket ,SOL_SOCKET ,SO_SNDBUF ,_CAST_<STRA[_SIZEOF_ (VAR32)]> (r2x) ,VAR32 (_SIZEOF_ (VAR32))) ;
	}

	void modify_timeout (LENGTH timeout) {
		mThis->mTimeout = timeout ;
	}

	void read (const PhanBuffer<BYTE> &data) {
		_DEBUG_ASSERT_ (data.size () < VAR32_MAX) ;
		const auto r1x = U::static_make_timeval (mThis->mTimeout) ;
		api::setsockopt (mThis->mSocket ,SOL_SOCKET ,SO_RCVTIMEO ,_CAST_<STRA[_SIZEOF_ (TIMEVAL)]> (r1x) ,VAR32 (_SIZEOF_ (TIMEVAL))) ;
		const auto r2x = api::recv (mThis->mSocket ,_LOAD_<ARR<STRA>> (DEPTR[data.self]) ,VAR32 (data.size ()) ,0) ;
		const auto r3x = U::static_make_timeval (0) ;
		api::setsockopt (mThis->mSocket ,SOL_SOCKET ,SO_RCVTIMEO ,_CAST_<STRA[_SIZEOF_ (TIMEVAL)]> (r3x) ,VAR32 (_SIZEOF_ (TIMEVAL))) ;
		//@info: state of 'this' has been changed
		if switch_case (TRUE) {
			if (r2x >= 0)
				discard ;
			const auto r4x = errno ;
			if (r4x == 0)
				discard ;
			_DYNAMIC_ASSERT_ (r4x == EINPROGRESS || r4x == EWOULDBLOCK) ;
		}
		_DYNAMIC_ASSERT_ (r2x == data.size ()) ;
	}

	void read (const PhanBuffer<BYTE> &data ,INDEX &out_i ,LENGTH timeout) {
		out_i = VAR_NONE ;
		_DEBUG_ASSERT_ (data.size () < VAR32_MAX) ;
		const auto r1x = U::static_make_timeval (timeout) ;
		api::setsockopt (mThis->mSocket ,SOL_SOCKET ,SO_RCVTIMEO ,_CAST_<STRA[_SIZEOF_ (TIMEVAL)]> (r1x) ,VAR32 (_SIZEOF_ (TIMEVAL))) ;
		const auto r2x = api::recv (mThis->mSocket ,_LOAD_<ARR<STRA>> (DEPTR[data.self]) ,VAR32 (data.size ()) ,0) ;
		const auto r3x = U::static_make_timeval (0) ;
		api::setsockopt (mThis->mSocket ,SOL_SOCKET ,SO_RCVTIMEO ,_CAST_<STRA[_SIZEOF_ (TIMEVAL)]> (r3x) ,VAR32 (_SIZEOF_ (TIMEVAL))) ;
		//@info: state of 'this' has been changed
		if switch_case (TRUE) {
			if (r2x >= 0)
				discard ;
			const auto r4x = errno ;
			if (r4x == 0)
				discard ;
			_DYNAMIC_ASSERT_ (r4x == EINPROGRESS || r4x == EWOULDBLOCK) ;
		}
		out_i = r2x ;
	}

	void write (const PhanBuffer<const BYTE> &data) {
		_DEBUG_ASSERT_ (data.size () < VAR32_MAX) ;
		const auto r1x = U::static_make_timeval (mThis->mTimeout) ;
		api::setsockopt (mThis->mSocket ,SOL_SOCKET ,SO_SNDTIMEO ,_CAST_<STRA[_SIZEOF_ (TIMEVAL)]> (r1x) ,VAR32 (_SIZEOF_ (TIMEVAL))) ;
		const auto r2x = api::send (mThis->mSocket ,_LOAD_<ARR<STRA>> (DEPTR[data.self]) ,VAR32 (data.size ()) ,0) ;
		const auto r3x = U::static_make_timeval (0) ;
		api::setsockopt (mThis->mSocket ,SOL_SOCKET ,SO_SNDTIMEO ,_CAST_<STRA[_SIZEOF_ (TIMEVAL)]> (r3x) ,VAR32 (_SIZEOF_ (TIMEVAL))) ;
		//@info: state of 'this' has been changed
		if switch_case (TRUE) {
			if (r2x >= 0)
				discard ;
			const auto r4x = errno ;
			if (r4x == 0)
				discard ;
			_DYNAMIC_ASSERT_ (r4x == EINPROGRESS || r4x == EWOULDBLOCK) ;
		}
		_DYNAMIC_ASSERT_ (r2x == data.size ()) ;
	}

private:
	void link_confirm () {
		const auto r1x = U::static_socket_select (mThis->mSocket ,mThis->mTimeout) ;
		//@info: state of 'this' has been changed
		_DYNAMIC_ASSERT_ (FD_ISSET (mThis->mSocket ,DEPTR[r1x[1]]) != 0) ;
		auto rax = PACK<STRA[_SIZEOF_ (VAR32)] ,VAR32> () ;
		_ZERO_ (rax.P1) ;
		rax.P2 = VAR32 (_SIZEOF_ (VAR32)) ;
		api::getsockopt (mThis->mSocket ,SOL_SOCKET ,SO_ERROR ,PTRTOARR[rax.P1] ,DEPTR[rax.P2]) ;
		const auto r2x = _BITWISE_CAST_<VAR32> (rax.P1) ;
		//@info: state of 'this' has been changed
		_DYNAMIC_ASSERT_ (r2x == 0) ;
	}
} ;

inline exports TCPSocket::TCPSocket (const String<STRU8> &ip_addr) {
	mThis = StrongRef<Implement>::make (ip_addr) ;
}

inline exports String<STRU8> TCPSocket::sock_name () const {
	return mThis->sock_name () ;
}

inline exports String<STRU8> TCPSocket::peer_sock_name () const {
	return mThis->peer_sock_name () ;
}

inline exports void TCPSocket::link (const String<STRU8> &ip_addr) {
	mThis->link (ip_addr) ;
}

inline exports void TCPSocket::modify_buffer (LENGTH rcv_len ,LENGTH snd_len) {
	mThis->modify_buffer (rcv_len ,snd_len) ;
}

inline exports void TCPSocket::modify_timeout (LENGTH timeout) {
	mThis->modify_timeout (timeout) ;
}

inline exports void TCPSocket::read (const PhanBuffer<BYTE> &data) {
	mThis->read (data) ;
}

inline exports void TCPSocket::read (const PhanBuffer<BYTE> &data ,INDEX &out_i ,LENGTH timeout) {
	mThis->read (data ,out_i ,timeout) ;
}

inline exports void TCPSocket::write (const PhanBuffer<const BYTE> &data) {
	mThis->write (data) ;
}

inline exports String<STRU8> TCPSocket::http_get (const String<STRU8> &ip_addr ,const String<STRU8> &site ,const String<STRU8> &msg ,LENGTH buffer_len ,LENGTH timeout) popping {
	String<STRU8> ret = String<STRU8> (buffer_len) ;
	INDEX iw = 0 ;
	auto rax = TCPSocket (_PCSTRU8_ ("")) ;
	rax.link (ip_addr) ;
	const auto r1x = TextWriter<STRU8>::GAP ;
	const auto r2x = String<STRU8>::make (_PCSTRU8_ ("GET ") ,site ,_PCSTRU8_ ("?") ,msg ,_PCSTRU8_ (" HTTP/1.1") ,r1x ,_PCSTRU8_ ("HOST: ") ,ip_addr ,r1x ,r1x) ;
	rax.write (PhanBuffer<const BYTE>::make (r2x.raw ())) ;
	rax.read (PhanBuffer<BYTE>::make (ret.raw ()) ,iw ,timeout) ;
	_DYNAMIC_ASSERT_ (iw >= 0 && iw < ret.size ()) ;
	if (iw < ret.size ())
		ret[iw] = 0 ;
	return _MOVE_ (ret) ;
}

inline exports String<STRU8> TCPSocket::http_post (const String<STRU8> &ip_addr ,const String<STRU8> &site ,const String<STRU8> &msg ,LENGTH buffer_len ,LENGTH timeout) popping {
	String<STRU8> ret = String<STRU8> (buffer_len) ;
	INDEX iw = 0 ;
	auto rax = TCPSocket (_PCSTRU8_ ("")) ;
	rax.link (ip_addr) ;
	const auto r1x = TextWriter<STRU8>::GAP ;
	const auto r2x = String<STRU8>::make (_PCSTRU8_ ("POST ") ,site ,_PCSTRU8_ (" HTTP/1.1") ,r1x ,_PCSTRU8_ ("HOST: ") ,ip_addr ,r1x ,_PCSTRU8_ ("Content-Length: ") ,msg.length () ,r1x ,r1x ,msg) ;
	rax.write (PhanBuffer<const BYTE>::make (r2x.raw ())) ;
	rax.read (PhanBuffer<BYTE>::make (ret.raw ()) ,iw ,timeout) ;
	_DYNAMIC_ASSERT_ (iw >= 0 && iw < ret.size ()) ;
	if (iw < ret.size ())
		ret[iw] = 0 ;
	return _MOVE_ (ret) ;
}

class TCPSocket::Listener::Implement {
private:
	SharedRef<TCPSocket::Implement::Pack> mThis ;
	UniqueRef<SOCKET> mListener ;
	UniqueRef<SOCKET> mLinker ;

public:
	Implement () = delete ;

	explicit Implement (const StrongRef<TCPSocket::Implement> &socket_) {
		mThis = socket_->mThis ;
		mListener = _MOVE_ (mThis->mSocket) ;
		const auto r1x = api::listen (mListener ,5) ;
		_DYNAMIC_ASSERT_ (r1x != SOCKET_ERROR) ;
	}

	void wait_linker () {
		const auto r1x = U::static_socket_select (mListener ,mThis->mTimeout) ;
		//@info: state of 'this' has been changed
		_DYNAMIC_ASSERT_ (FD_ISSET (mListener ,DEPTR[r1x[0]]) != 0) ;
		mLinker = UniqueRef<SOCKET> ([&] (SOCKET &me) {
			me = api::accept (mListener ,NULL ,NULL) ;
			_DYNAMIC_ASSERT_ (me != INVALID_SOCKET) ;
		} ,[] (SOCKET &me) {
			api::closesocket (me) ;
		}) ;
	}

	void accept () {
		mThis->mSocket = _MOVE_ (mLinker) ;
		auto rax = PACK<SOCKADDR ,VAR32> () ;
		_ZERO_ (rax.P1) ;
		rax.P2 = VAR32 (_SIZEOF_ (SOCKADDR)) ;
		api::getpeername (mThis->mSocket ,DEPTR[rax.P1] ,DEPTR[rax.P2]) ;
		_DYNAMIC_ASSERT_ (rax.P2 == _SIZEOF_ (SOCKADDR)) ;
		mThis->mPeer = rax.P1 ;
	}
} ;

inline exports void TCPSocket::Listener::wait_linker () {
	mThis->wait_linker () ;
}

inline exports void TCPSocket::Listener::accept () {
	mThis->accept () ;
}

inline exports TCPSocket::Listener::Listener (const StrongRef<TCPSocket::Implement> &socket_) {
	mThis = StrongRef<Implement>::make (socket_) ;
}

class UDPSocket::Implement {
private:
	class Pack {
	private:
		friend Implement ;
		UniqueRef<SOCKET> mSocket ;
		SOCKADDR mPeer ;
		LENGTH mTimeout ;
	} ;

private:
	SharedRef<Pack> mThis ;

public:
	Implement () = delete ;

	explicit Implement (const String<STRU8> &ip_addr) {
		mThis->mSocket = UniqueRef<SOCKET> ([&] (SOCKET &me) {
			me = api::socket (AF_INET ,SOCK_DGRAM ,IPPROTO_UDP) ;
			_DYNAMIC_ASSERT_ (me != INVALID_SOCKET) ;
			const auto r1x = VAR32 (1) ;
			api::setsockopt (me ,SOL_SOCKET ,SO_REUSEADDR ,_CAST_<STRA[_SIZEOF_ (VAR32)]> (r1x) ,VAR32 (_SIZEOF_ (VAR32))) ;
			api::setsockopt (me ,SOL_SOCKET ,SO_BROADCAST ,_CAST_<STRA[_SIZEOF_ (VAR32)]> (r1x) ,VAR32 (_SIZEOF_ (VAR32))) ;
		} ,[] (SOCKET &me) {
			api::closesocket (me) ;
		}) ;
		if (!ip_addr.empty ())
			U::static_socket_bind (mThis->mSocket ,ip_addr) ;
		_ZERO_ (mThis->mPeer) ;
		mThis->mTimeout = 30000 ;
	}

	String<STRU8> sock_name () const {
		auto rax = PACK<SOCKADDR ,VAR32> () ;
		_ZERO_ (rax.P1) ;
		rax.P2 = VAR32 (_SIZEOF_ (SOCKADDR)) ;
		api::getsockname (mThis->mSocket ,DEPTR[rax.P1] ,DEPTR[rax.P2]) ;
		//@info: ipv6 is not supported
		_DYNAMIC_ASSERT_ (rax.P2 == _SIZEOF_ (SOCKADDR)) ;
		return U::static_make_ipv4s (rax.P1) ;
	}

	String<STRU8> peer_sock_name () const {
		return U::static_make_ipv4s (mThis->mPeer) ;
	}

	void link (const String<STRU8> &ip_addr) {
		mThis->mPeer = U::static_make_socket_addr (ip_addr) ;
	}

	void modify_timeout (LENGTH timeout) {
		mThis->mTimeout = timeout ;
	}

	void read (const PhanBuffer<BYTE> &data) {
		_DEBUG_ASSERT_ (data.size () < VAR32_MAX) ;
		const auto r1x = U::static_socket_select (mThis->mSocket ,mThis->mTimeout) ;
		//@info: state of 'this' has been changed
		_DYNAMIC_ASSERT_ (FD_ISSET (mThis->mSocket ,DEPTR[r1x[0]]) != 0) ;
		auto rax = PACK<SOCKADDR ,VAR32> () ;
		_ZERO_ (rax.P1) ;
		rax.P2 = VAR32 (_SIZEOF_ (SOCKADDR)) ;
		const auto r2x = api::recvfrom (mThis->mSocket ,_LOAD_<ARR<STRA>> (DEPTR[data.self]) ,VAR32 (data.size ()) ,0 ,DEPTR[rax.P1] ,DEPTR[rax.P2]) ;
		//@info: state of 'this' has been changed
		_DYNAMIC_ASSERT_ (rax.P2 == _SIZEOF_ (SOCKADDR)) ;
		_DYNAMIC_ASSERT_ (r2x == data.size ()) ;
		mThis->mPeer = rax.P1 ;
	}

	void read (const PhanBuffer<BYTE> &data ,INDEX &out_i ,LENGTH timeout) {
		_DEBUG_ASSERT_ (data.size () < VAR32_MAX) ;
		out_i = VAR_NONE ;
		const auto r1x = U::static_socket_select (mThis->mSocket ,timeout) ;
		//@info: state of 'this' has been changed
		_DYNAMIC_ASSERT_ (FD_ISSET (mThis->mSocket ,DEPTR[r1x[0]]) != 0) ;
		auto rax = PACK<SOCKADDR ,VAR32> () ;
		_ZERO_ (rax.P1) ;
		rax.P2 = VAR32 (_SIZEOF_ (SOCKADDR)) ;
		const auto r2x = api::recvfrom (mThis->mSocket ,_LOAD_<ARR<STRA>> (DEPTR[data.self]) ,VAR32 (data.size ()) ,0 ,DEPTR[rax.P1] ,DEPTR[rax.P2]) ;
		//@info: state of 'this' has been changed
		_DYNAMIC_ASSERT_ (rax.P2 == _SIZEOF_ (SOCKADDR)) ;
		mThis->mPeer = rax.P1 ;
		out_i = r2x ;
	}

	void write (const PhanBuffer<const BYTE> &data) {
		_DEBUG_ASSERT_ (data.size () < VAR32_MAX) ;
		const auto r1x = U::static_socket_select (mThis->mSocket ,mThis->mTimeout) ;
		//@info: state of 'this' has been changed
		_DYNAMIC_ASSERT_ (FD_ISSET (mThis->mSocket ,DEPTR[r1x[1]]) != 0) ;
		const auto r2x = api::sendto (mThis->mSocket ,_LOAD_<ARR<STRA>> (DEPTR[data.self]) ,VAR32 (data.size ()) ,0 ,DEPTR[mThis->mPeer] ,VAR32 (_SIZEOF_ (SOCKADDR))) ;
		//@info: state of 'this' has been changed
		_DYNAMIC_ASSERT_ (r2x == data.size ()) ;
	}
} ;

inline exports UDPSocket::UDPSocket (const String<STRU8> &ip_addr) {
	mThis = StrongRef<Implement>::make (ip_addr) ;
}

inline exports String<STRU8> UDPSocket::sock_name () const {
	return mThis->sock_name () ;
}

inline exports String<STRU8> UDPSocket::peer_sock_name () const {
	return mThis->peer_sock_name () ;
}

inline exports void UDPSocket::link (const String<STRU8> &ip_addr) {
	mThis->link (ip_addr) ;
}

inline exports void UDPSocket::modify_timeout (LENGTH timeout) {
	mThis->modify_timeout (timeout) ;
}

inline exports void UDPSocket::read (const PhanBuffer<BYTE> &data) {
	mThis->read (data) ;
}

inline exports void UDPSocket::read (const PhanBuffer<BYTE> &data ,INDEX &out_i ,LENGTH timeout) {
	mThis->read (data ,out_i ,timeout) ;
}

inline exports void UDPSocket::write (const PhanBuffer<const BYTE> &data) {
	mThis->write (data) ;
}

class NetworkService::Implement
	:public NetworkService::Abstract {
private:
	UniqueRef<void> mService ;

public:
	void startup () override {
		if (mService.exist ())
			return ;
		mService = UniqueRef<void> ([&] () {
			auto rax = WSADATA () ;
			_ZERO_ (rax) ;
			const auto r1x = WORD ((WORD (2) << 8) | WORD (2)) ;
			const auto r2x = WSAStartup (r1x ,DEPTR[rax]) ;
			_DYNAMIC_ASSERT_ (r2x == 0) ;
		} ,[] () {
			WSACleanup () ;
		}) ;
	}

	void shutdown () override {
		mService = UniqueRef<void> () ;
	}

	String<STRU8> localhost_name () const override {
		auto rax = String<STRA> (127) ;
		api::gethostname (rax.raw ().self ,VAR32 (rax.size ())) ;
		return StringProc::cvt_as_u8s (rax) ;
	}

	String<STRU8> localhost_addr () const override {
		return String<STRU8> (_PCSTRU8_ ("127.0.0.1")) ;
	}

	String<STRU8> broadcast_addr () const override {
		return String<STRU8> (_PCSTRU8_ ("255.255.255.255")) ;
	}

	LENGTH pref_timeout () const override {
		return 30000 ;
	}
} ;

inline exports NetworkService::NetworkService () {
	mThis = StrongRef<Implement>::make () ;
}
} ;