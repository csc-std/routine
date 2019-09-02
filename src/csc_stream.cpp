﻿#include "util.h"

#ifdef __CSC_STREAM__
namespace UNITTEST {
TEST_CLASS (UNITTEST_CSC_STREAM) {
public:
	TEST_METHOD (TEST_CSC_STREAM) {
		const auto r1x = CSC::CHAR (0X11223344) ;
		auto &r1 = _CAST_<EndianBytes<CSC::CHAR>> (r1x) ;
		_UNITTEST_ASSERT_ (r1[0] == CSC::BYTE (0X11)) ;
		_UNITTEST_ASSERT_ (r1[1] == CSC::BYTE (0X22)) ;
		_UNITTEST_ASSERT_ (r1[2] == CSC::BYTE (0X33)) ;
		_UNITTEST_ASSERT_ (r1[3] == CSC::BYTE (0X44)) ;
	}

	TEST_METHOD (TEST_CSC_STREAM_BYTEREADER) {
		auto rax = PACK<CSC::BYTE[12]> () ;
		auto ris = ByteReader (PhanBuffer<const CSC::BYTE>::make (rax.P1)) ;
		auto rbx = Buffer<int ,ARGC<4>> () ;
		ris >> rbx ;
	}

	TEST_METHOD (TEST_CSC_STREAM_BYTEWRITER) {
		auto rax = Buffer<int ,ARGC<4>> () ;
		auto wos = ByteWriter (SharedRef<FixedBuffer<CSC::BYTE>>::make (DEFAULT_SHORTSTRING_SIZE::value)) ;
		wos << rax ;
	}

	TEST_METHOD (TEST_CSC_STREAM_TEXTREADER) {
		struct wrapped_int :private Wrapped<int> {
			inline void friend_read (TextReader<STRU8> &reader) popping {
				reader >> wrapped_int::mSelf >> _GAP_ ;
			}
		} ;
		auto rax = Buffer<int ,ARGC<4>> () ;
		auto rbx = Buffer<STRU8 ,ARGC<10>> () ;
		auto ris = TextReader<STRU8> (PhanBuffer<const STRU8>::make (rbx)) ;
		ris.attr ().modify_space (STRU8 (' ') ,0) ;
		rbx[0] = STRU8 ('0') ;
		rbx[1] = STRU8 (' ') ;
		rbx[2] = STRU8 ('0') ;
		rbx[3] = STRU8 (' ') ;
		rbx[4] = STRU8 ('0') ;
		rbx[5] = STRU8 (' ') ;
		rbx[6] = STRU8 ('0') ;
		rbx[7] = STRU8 (' ') ;
		rbx[8] = STRU8 ('0') ;
		rbx[9] = ris.attr ().varify_ending_item () ;
		for (FOR_ONCE_DO_WHILE) {
			auto &r1 = _CAST_<Buffer<wrapped_int ,ARGC<4>>> (rax) ;
			ris >> r1 ;
			//@info: see also std::launder
			rax = std::move (_CAST_<Buffer<int ,ARGC<4>>> (r1)) ;
		}
	}

	TEST_METHOD (TEST_CSC_STREAM_TEXTWRITER) {
		auto rax = Buffer<int ,ARGC<4>> () ;
		auto wos = TextWriter<STRU8> (SharedRef<FixedBuffer<STRU8>>::make (DEFAULT_SHORTSTRING_SIZE::value)) ;
		wos << rax ;
	}
} ;
} ;
#endif