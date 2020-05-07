﻿#pragma once

#ifndef __CSC_SERIALIZATION__
#define __CSC_SERIALIZATION__
#endif

#include "csc.hpp"
#include "csc_basic.hpp"
#include "csc_array.hpp"
#include "csc_math.hpp"
#include "csc_stream.hpp"
#include "csc_string.hpp"

namespace CSC {
class XmlParser {
private:
	static constexpr auto NODE_CLAZZ_TABLE = EFLAG (1) ;
	static constexpr auto NODE_CLAZZ_OBJECT = EFLAG (2) ;
	static constexpr auto NODE_CLAZZ_ARRAY = EFLAG (3) ;
	static constexpr auto NODE_CLAZZ_FINAL = EFLAG (4) ;

	class Node {
	private:
		friend XmlParser ;
		String<STRU8> mName ;
		Deque<String<STRU8>> mAttributeList ;
		SoftSet<String<STRU8>> mAttributeMappingSet ;
		SoftSet<INDEX> mMemberSet ;
		SoftSet<String<STRU8>> mObjectSet ;
		INDEX mParent ;
		INDEX mBrother ;
		INDEX mChild ;

	public:
		inline Node () = default ;
	} ;

private:
	struct Detail ;
	SharedRef<FixedBuffer<Node>> mHeap ;
	INDEX mIndex ;

public:
	XmlParser () {
		mIndex = VAR_NONE ;
	}

	BOOL exist () const {
		if (!mHeap.exist ())
			return FALSE ;
		if (mIndex == VAR_NONE)
			return FALSE ;
		return TRUE ;
	}

	XmlParser root () const {
		if (!exist ())
			return XmlParser (mHeap ,VAR_NONE) ;
		return XmlParser (mHeap ,0) ;
	}

	XmlParser parent () const {
		if (!exist ())
			return XmlParser (mHeap ,VAR_NONE) ;
		return XmlParser (mHeap ,mHeap.self[mIndex].mParent) ;
	}

	XmlParser brother () const {
		if (!exist ())
			return XmlParser (mHeap ,VAR_NONE) ;
		return XmlParser (mHeap ,mHeap.self[mIndex].mBrother) ;
	}

	XmlParser child () const {
		if (!exist ())
			return XmlParser (mHeap ,VAR_NONE) ;
		return XmlParser (mHeap ,mHeap.self[mIndex].mChild) ;
	}

	XmlParser child (const String<STRU8> &name) const {
		if (!exist ())
			return XmlParser (mHeap ,VAR_NONE) ;
		INDEX ix = mHeap.self[mIndex].mObjectSet.map (name) ;
		return XmlParser (mHeap ,ix) ;
	}

	Array<XmlParser> child_array () const {
		Array<XmlParser> ret ;
		if switch_case (TRUE) {
			if (!exist ())
				discard ;
			ret = Array<XmlParser> (mHeap.self[mIndex].mMemberSet.length ()) ;
			INDEX iw = 0 ;
			for (auto &&i : mHeap.self[mIndex].mMemberSet)
				ret[iw++] = XmlParser (mHeap ,i.mapx) ;
			_DEBUG_ASSERT_ (iw == ret.length ()) ;
		}
		return std::move (ret) ;
	}

	Array<XmlParser> child_array (LENGTH fixed_len) const {
		Array<XmlParser> ret = Array<XmlParser> (fixed_len) ;
		INDEX iw = 0 ;
		if switch_case (TRUE) {
			if (!exist ())
				discard ;
			for (auto &&i : mHeap.self[mIndex].mMemberSet) {
				INDEX ix = iw++ ;
				if (ix >= ret.size ())
					continue ;
				ret[ix] = XmlParser (mHeap ,i.mapx) ;
			}
		}
		return std::move (ret) ;
	}

	BOOL equal (const XmlParser &that) const {
		if (!exist ())
			if (!that.exist ())
				return TRUE ;
		if (!exist ())
			return FALSE ;
		if (!that.exist ())
			return FALSE ;
		if (&mHeap.self != &that.mHeap.self)
			return FALSE ;
		if (mIndex != that.mIndex)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const XmlParser &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const XmlParser &that) const {
		return !equal (that) ;
	}

	const String<STRU8> &name () const & {
		_DYNAMIC_ASSERT_ (exist ()) ;
		return mHeap.self[mIndex].mName ;
	}

	auto name () && ->void = delete ;

	const String<STRU8> &attribute (const String<STRU8> &tag) const & {
		auto &r1x = _CACHE_ ([&] () {
			return String<STRU8> () ;
		}) ;
		if (!exist ())
			return r1x ;
		INDEX ix = mHeap.self[mIndex].mAttributeMappingSet.map (tag) ;
		if (ix == VAR_NONE)
			return r1x ;
		return mHeap.self[mIndex].mAttributeList[ix] ;
	}

	auto attribute (const String<STRU8> &) && ->void = delete ;

	template <class _ARG1>
	_ARG1 attribute (const String<STRU8> &tag ,const _ARG1 &def ,const Function<_ARG1 (const String<STRU8> &)> &convert) const {
		_ARG1 ret ;
		_CALL_TRY_ ([&] () {
			ret = convert (attribute (tag)) ;
		} ,[&] () {
			ret = def ;
		}) ;
		return std::move (ret) ;
	}

	BOOL attribute (const String<STRU8> &tag ,const BOOL &def) const {
		const auto r1x = Function<BOOL (const String<STRU8> &)> (&_PARSEBOOLS_<STRU8>) ;
		return attribute (tag ,def ,r1x) ;
	}

	VAR32 attribute (const String<STRU8> &tag ,const VAR32 &def) const {
		const auto r1x = Function<VAR32 (const String<STRU8> &)> (&_PARSEVAR32S_<STRU8>) ;
		return attribute (tag ,def ,r1x) ;
	}

	VAR64 attribute (const String<STRU8> &tag ,const VAR64 &def) const {
		const auto r1x = Function<VAR64 (const String<STRU8> &)> (&_PARSEVAR64S_<STRU8>) ;
		return attribute (tag ,def ,r1x) ;
	}

	VAL32 attribute (const String<STRU8> &tag ,const VAL32 &def) const {
		const auto r1x = Function<VAL32 (const String<STRU8> &)> (&_PARSEVAL32S_<STRU8>) ;
		return attribute (tag ,def ,r1x) ;
	}

	VAL64 attribute (const String<STRU8> &tag ,const VAL64 &def) const {
		const auto r1x = Function<VAL64 (const String<STRU8> &)> (&_PARSEVAL64S_<STRU8>) ;
		return attribute (tag ,def ,r1x) ;
	}

	String<STRU8> attribute (const String<STRU8> &tag ,const String<STRU8> &def) const {
		const auto r1x = Function<String<STRU8> (const String<STRU8> &)> (&_COPY_<String<STRU8>>) ;
		return attribute (tag ,def ,r1x) ;
	}

	String<STRU16> attribute (const String<STRU8> &tag ,const String<STRU16> &def) const {
		const auto r1x = Function<String<STRU16> (const String<STRU8> &)> (&_U8STOU16S_) ;
		return attribute (tag ,def ,r1x) ;
	}

	String<STRU32> attribute (const String<STRU8> &tag ,const String<STRU32> &def) const {
		const auto r1x = Function<String<STRU32> (const String<STRU8> &)> (&_U8STOU32S_) ;
		return attribute (tag ,def ,r1x) ;
	}

	String<STRA> attribute (const String<STRU8> &tag ,const String<STRA> &def) const {
		const auto r1x = Function<String<STRA> (const String<STRU8> &)> (&_U8STOAS_) ;
		return attribute (tag ,def ,r1x) ;
	}

	String<STRW> attribute (const String<STRU8> &tag ,const String<STRW> &def) const {
		const auto r1x = Function<String<STRW> (const String<STRU8> &)> (&_U8STOWS_) ;
		return attribute (tag ,def ,r1x) ;
	}

	PTR<const VOID> attribute (const String<STRU8> & ,const PTR<const VOID> &) const = delete ;

	const String<STRU8> &value () const & {
		_DYNAMIC_ASSERT_ (exist ()) ;
		_DYNAMIC_ASSERT_ (mHeap.self[mIndex].mMemberSet.size () == 0) ;
		_DYNAMIC_ASSERT_ (mHeap.self[mIndex].mAttributeList.length () == 1) ;
		INDEX ix = mHeap.self[mIndex].mAttributeList.head () ;
		return mHeap.self[mIndex].mAttributeList[ix] ;
	}

	auto value () && ->void = delete ;

	template <class _ARG1>
	_ARG1 value (const _ARG1 &def ,const Function<_ARG1 (const String<STRU8> &)> &convert) const {
		_ARG1 ret ;
		_CALL_TRY_ ([&] () {
			ret = convert (value ()) ;
		} ,[&] () {
			ret = def ;
		}) ;
		return std::move (ret) ;
	}

	BOOL value (const BOOL &def) const {
		const auto r1x = Function<BOOL (const String<STRU8> &)> (&_PARSEBOOLS_<STRU8>) ;
		return value (def ,r1x) ;
	}

	PTR<const VOID> value (const PTR<const VOID> &) const = delete ;

	VAR32 value (const VAR32 &def) const {
		const auto r1x = Function<VAR32 (const String<STRU8> &)> (&_PARSEVAR32S_<STRU8>) ;
		return value (def ,r1x) ;
	}

	VAR64 value (const VAR64 &def) const {
		const auto r1x = Function<VAR64 (const String<STRU8> &)> (&_PARSEVAR64S_<STRU8>) ;
		return value (def ,r1x) ;
	}

	VAL32 value (const VAL32 &def) const {
		const auto r1x = Function<VAL32 (const String<STRU8> &)> (&_PARSEVAL32S_<STRU8>) ;
		return value (def ,r1x) ;
	}

	VAL64 value (const VAL64 &def) const {
		const auto r1x = Function<VAL64 (const String<STRU8> &)> (&_PARSEVAL64S_<STRU8>) ;
		return value (def ,r1x) ;
	}

	String<STRU8> value (const String<STRU8> &def) const {
		const auto r1x = Function<String<STRU8> (const String<STRU8> &)> (&_COPY_<String<STRU8>>) ;
		return value (def ,r1x) ;
	}

	String<STRU16> value (const String<STRU16> &def) const {
		const auto r1x = Function<String<STRU16> (const String<STRU8> &)> (&_U8STOU16S_) ;
		return value (def ,r1x) ;
	}

	String<STRU32> value (const String<STRU32> &def) const {
		const auto r1x = Function<String<STRU32> (const String<STRU8> &)> (&_U8STOU32S_) ;
		return value (def ,r1x) ;
	}

	String<STRA> value (const String<STRA> &def) const {
		const auto r1x = Function<String<STRA> (const String<STRU8> &)> (&_U8STOAS_) ;
		return value (def ,r1x) ;
	}

	String<STRW> value (const String<STRW> &def) const {
		const auto r1x = Function<String<STRW> (const String<STRU8> &)> (&_U8STOWS_) ;
		return value (def ,r1x) ;
	}

	void friend_write (TextWriter<STRU8> &writer) const ;

public:
	inline static XmlParser make (const PhanBuffer<const STRU8> &data) {
		XmlParser ret ;
		ret.initialize (data) ;
		return std::move (ret) ;
	}

	inline static XmlParser make (const Array<XmlParser> &sequence) {
		XmlParser ret ;
		ret.initialize (sequence) ;
		return std::move (ret) ;
	}

private:
	explicit XmlParser (const SharedRef<FixedBuffer<Node>> &heap ,INDEX index)
		:mHeap (heap) ,mIndex (index) {}

private:
	void initialize (const PhanBuffer<const STRU8> &data) ;

	void initialize (const Array<XmlParser> &sequence) ;
} ;

struct XmlParser::Detail {
	class RecursiveCounter
		:private Wrapped<LENGTH> {
	public:
		inline void lock () {
			_DYNAMIC_ASSERT_ (RecursiveCounter::mSelf <= DEFAULT_RECURSIVE_SIZE::value) ;
			RecursiveCounter::mSelf++ ;
		}

		inline void unlock () {
			RecursiveCounter::mSelf-- ;
		}
	} ;

	struct FOUND_NODE {
		String<STRU8> mName ;
		Deque<String<STRU8>> mAttributeList ;
		SoftSet<String<STRU8>> mAttributeMappingSet ;
		EFLAG mClazz ;
		Deque<XmlParser> mBaseNode ;
	} ;

	struct STACK_NODE {
		Deque<XmlParser> mBaseNode ;
		EFLAG mClazz ;
		INDEX mParent ;
	} ;
} ;

inline exports void XmlParser::friend_write (TextWriter<STRU8> &writer) const {
	static constexpr auto M_NODE_X1 = EFLAG (1) ;
	static constexpr auto M_NODE_X2 = EFLAG (2) ;
	auto rax = Deque<PACK<INDEX ,EFLAG>> () ;
	auto rbx = Deque<PACK<INDEX ,EFLAG>> () ;
	rax.add (PACK<INDEX ,EFLAG> {mIndex ,M_NODE_X1}) ;
	while (TRUE) {
		if (rax.empty ())
			break ;
		const auto r1x = rax[rax.tail ()] ;
		rax.pop () ;
		auto fax = TRUE ;
		if switch_case (fax) {
			//@info: case '<?xml ...>'
			if (!(r1x.P1 != VAR_NONE))
				discard ;
			if (!mHeap.self[r1x.P1].mName.empty ())
				discard ;
			if (!(r1x.P2 == M_NODE_X1))
				discard ;
			auto &r2x = mHeap.self[r1x.P1] ;
			writer << _PCSTRU8_ ("<?xml version=\"1.0\" encoding=\"utf-8\" ?>") ;
			writer << _GAP_ ;
			rbx.clear () ;
			for (INDEX i = r2x.mChild ,it ; i != VAR_NONE ; i = it) {
				it = mHeap.self[i].mBrother ;
				rbx.add (PACK<INDEX ,EFLAG> {i ,M_NODE_X1}) ;
			}
			while (TRUE) {
				if (rbx.empty ())
					break ;
				rax.add (rbx[rbx.tail ()]) ;
				rbx.pop () ;
			}
		}
		if switch_case (fax) {
			//@info: case '<xxx ("xxx"="xxx"( "xxx"="xxx")?)?/>'
			if (!(r1x.P1 != VAR_NONE))
				discard ;
			if (!(mHeap.self[r1x.P1].mChild == VAR_NONE))
				discard ;
			if (!(r1x.P2 == M_NODE_X1))
				discard ;
			auto &r3x = mHeap.self[r1x.P1] ;
			writer << _PCSTRU8_ ("<") << r3x.mName << _PCSTRU8_ (" ") ;
			for (auto &&i : r3x.mAttributeMappingSet) {
				writer << i.key ;
				writer << _PCSTRU8_ ("=\"") ;
				writer << r3x.mAttributeList[i.mapx] << _PCSTRU8_ ("\" ") ;
			}
			writer << _PCSTRU8_ ("/>") ;
		}
		if switch_case (fax) {
			//@info: case '<xxx ("xxx"="xxx"( "xxx"="xxx")?)?>'
			if (!(r1x.P1 != VAR_NONE))
				discard ;
			if (!(mHeap.self[r1x.P1].mChild != VAR_NONE))
				discard ;
			if (!(r1x.P2 == M_NODE_X1))
				discard ;
			auto &r4x = mHeap.self[r1x.P1] ;
			writer << _PCSTRU8_ ("<") << r4x.mName << _PCSTRU8_ (" ") ;
			for (auto &&i : r4x.mAttributeMappingSet) {
				writer << i.key ;
				writer << _PCSTRU8_ ("=\"") ;
				writer << r4x.mAttributeList[i.mapx] << _PCSTRU8_ ("\" ") ;
			}
			writer << _PCSTRU8_ (">") ;
			rbx.clear () ;
			for (INDEX i = r4x.mChild ,it ; i != VAR_NONE ; i = it) {
				it = mHeap.self[i].mBrother ;
				rbx.add (PACK<INDEX ,EFLAG> {i ,M_NODE_X1}) ;
			}
			rbx.add (PACK<INDEX ,EFLAG> {r1x.P1 ,M_NODE_X2}) ;
			while (TRUE) {
				if (rbx.empty ())
					break ;
				rax.add (rbx[rbx.tail ()]) ;
				rbx.pop () ;
			}
		}
		if switch_case (fax) {
			//@info: case '</xxx>'
			if (!(r1x.P1 != VAR_NONE))
				discard ;
			if (!(r1x.P2 == M_NODE_X2))
				discard ;
			writer << _PCSTRU8_ ("</") << mHeap.self[r1x.P1].mName << _PCSTRU8_ (">") ;
		}
	}
}

inline exports void XmlParser::initialize (const PhanBuffer<const STRU8> &data) {
	using RecursiveCounter = typename Detail::RecursiveCounter ;
	class Lambda final
		:private Proxy {
	private:
		XmlParser &mContext ;

		TextReader<STRU8> mTextReader ;
		RegularReader mRis ;
		LENGTH mRecursiveCounter ;
		INDEX mLatestIndex ;
		String<STRU8> mLatestString ;

		SoftSet<String<STRU8>> mAttributeMappingSoftSet ;
		SoftSet<INDEX> mMemberSoftSet ;
		SoftSet<String<STRU8>> mObjectSoftSet ;
		Allocator<Node ,SAUTO> mNodeHeap ;
		SharedRef<FixedBuffer<Node>> mHeap ;
		INDEX mRoot ;

	public:
		inline explicit Lambda (XmlParser &context_ ,const PhanBuffer<const STRU8> &data)
			: mContext (context_) ,mTextReader (data) {}

		inline void operator() () {
			prepare () ;
			generate () ;
			refresh () ;
		}

	private:
		inline void prepare () {
			mRis = RegularReader (PhanRef<TextReader<STRU8>>::make (mTextReader) ,2) ;
			mRecursiveCounter = 0 ;
			mAttributeMappingSoftSet = SoftSet<String<STRU8>> (0) ;
			mMemberSoftSet = SoftSet<INDEX> (0) ;
			mObjectSoftSet = SoftSet<String<STRU8>> (0) ;
			mNodeHeap = Allocator<Node ,SAUTO> () ;
			mHeap = SharedRef<FixedBuffer<Node>> () ;
			mRoot = VAR_NONE ;
		}

		inline void generate () {
			/*
			*	$0->$8 $7 $9
			*	$1->${identity}
			*	$2->"${string}"
			*	$3->$1 = $2
			*	$4->${eps}|$3 $4
			*	$5-><$1 $4 />|<$1 $4 > $7 </$1 >
			*	$6-><!--comment-->
			*	$7->${eps}|$5 $7|$6 $7
			*	$8->${eps}|<?xml version = "1.0" ?>|<?xml version = "1.0" encoding = "utf-8" ?>
			*	$9->${end}
			*/
			update_shift_e0 () ;
			_DEBUG_ASSERT_ (mLatestIndex == 0) ;
			mRoot = mLatestIndex ;
			update_heap () ;
		}

		//@info: $0->$8 $7 $9
		inline void update_shift_e0 () {
			update_shift_e8 () ;
			mRis >> RegularReader::SKIP_GAP ;
			INDEX ix = mNodeHeap.alloc () ;
			mNodeHeap[ix].mMemberSet = mMemberSoftSet.share () ;
			mNodeHeap[ix].mObjectSet = mObjectSoftSet.share () ;
			mNodeHeap[ix].mParent = VAR_NONE ;
			update_shift_e7 (ix) ;
			mNodeHeap[ix].mChild = mLatestIndex ;
			mNodeHeap[ix].mBrother = VAR_NONE ;
			mRis >> RegularReader::SKIP_GAP ;
			update_shift_e9 () ;
			mLatestIndex = ix ;
		}

		//@info: $1->${identity}
		inline void update_shift_e1 () {
			mRis >> RegularReader::HINT_IDENTIFIER_TEXT >> mLatestString ;
		}

		//@info: $2->"${string}"
		inline void update_shift_e2 () {
			mRis >> RegularReader::HINT_STRING_TEXT >> mLatestString ;
		}

		//@info: $3->$1 = $2
		inline void update_shift_e3 (INDEX curr) {
			update_shift_e1 () ;
			INDEX ix = mNodeHeap[curr].mAttributeMappingSet.map (mLatestString) ;
			_DYNAMIC_ASSERT_ (ix == VAR_NONE) ;
			ix = mNodeHeap[curr].mAttributeList.insert () ;
			mNodeHeap[curr].mAttributeMappingSet.add (std::move (mLatestString) ,ix) ;
			mRis >> RegularReader::SKIP_GAP ;
			mRis >> _PCSTRU8_ ("=") ;
			mRis >> RegularReader::SKIP_GAP ;
			update_shift_e2 () ;
			mNodeHeap[curr].mAttributeList[ix] = std::move (mLatestString) ;
		}

		//@info: $4->${eps}|$3 $4
		inline void update_shift_e4 (INDEX curr) {
			while (TRUE) {
				if (!(mRis[0] >= STRU8 ('A') && mRis[0] <= STRU8 ('Z')))
					if (!(mRis[0] >= STRU8 ('a') && mRis[0] <= STRU8 ('z')))
						if (!(mRis[0] == STRU8 ('_')))
							break ;
				update_shift_e3 (curr) ;
				mRis >> RegularReader::SKIP_GAP ;
			}
		}

		//@info: $5-><$1 $4 />|<$1 $4 > $7 </$1 >
		inline void update_shift_e5 (INDEX curr) {
			ScopedGuard<RecursiveCounter> ANONYMOUS (_CAST_<RecursiveCounter> (mRecursiveCounter)) ;
			mRis >> _PCSTRU8_ ("<") ;
			INDEX ix = mNodeHeap.alloc () ;
			update_shift_e1 () ;
			mNodeHeap[ix].mName = std::move (mLatestString) ;
			mNodeHeap[ix].mAttributeList = Deque<String<STRU8>> () ;
			mNodeHeap[ix].mAttributeMappingSet = mAttributeMappingSoftSet.share () ;
			mNodeHeap[ix].mParent = curr ;
			mNodeHeap[ix].mBrother = VAR_NONE ;
			mNodeHeap[ix].mChild = VAR_NONE ;
			mRis >> RegularReader::SKIP_GAP ;
			update_shift_e4 (ix) ;
			mRis >> RegularReader::SKIP_GAP ;
			auto fax = TRUE ;
			if switch_case (fax) {
				if (!(mRis[0] == STRU8 ('>')))
					discard ;
				mRis++ ;
				mRis >> RegularReader::SKIP_GAP ;
				mNodeHeap[ix].mMemberSet = mMemberSoftSet.share () ;
				mNodeHeap[ix].mObjectSet = mObjectSoftSet.share () ;
				update_shift_e7 (ix) ;
				mNodeHeap[ix].mChild = mLatestIndex ;
				mRis >> RegularReader::SKIP_GAP ;
				mRis >> _PCSTRU8_ ("</") ;
				update_shift_e1 () ;
				_DYNAMIC_ASSERT_ (mNodeHeap[ix].mName == mLatestString) ;
				mRis >> RegularReader::SKIP_GAP ;
				mRis >> _PCSTRU8_ (">") ;
			}
			if switch_case (fax) {
				mRis >> _PCSTRU8_ ("/>") ;
			}
			mLatestIndex = ix ;
		}

		//@info: $6-><!--${comment}-->
		inline void update_shift_e6 () {
			mRis >> _PCSTRU8_ ("<!--") ;
			while (TRUE) {
				if (mRis[0] == STRU8 ('\0'))
					break ;
				if (mRis[0] == STRU8 ('-'))
					if (mRis[1] == STRU8 ('-'))
						break ;
				mRis++ ;
			}
			mRis >> _PCSTRU8_ ("-->") ;
		}

		//@info: $7->${eps}|$5 $7|$6 $7
		inline void update_shift_e7 (INDEX curr) {
			ScopedGuard<RecursiveCounter> ANONYMOUS (_CAST_<RecursiveCounter> (mRecursiveCounter)) ;
			INDEX ix = VAR_NONE ;
			INDEX iy = VAR_NONE ;
			while (TRUE) {
				const auto r1x = BOOL (mRis[0] == STRU8 ('<') && mRis[1] == STRU8 ('!')) ;
				const auto r2x = BOOL (mRis[0] == STRU8 ('<') && mRis[1] != STRU8 ('/')) ;
				if (!r1x && !r2x)
					break ;
				auto fax = TRUE ;
				if switch_case (fax) {
					if (!r1x)
						discard ;
					update_shift_e6 () ;
				}
				if switch_case (fax) {
					if (!r2x)
						discard ;
					update_shift_e5 (curr) ;
					const auto r3x = mNodeHeap[curr].mMemberSet.length () ;
					mNodeHeap[curr].mMemberSet.add (r3x ,mLatestIndex) ;
					mNodeHeap[curr].mObjectSet.add (mNodeHeap[mLatestIndex].mName ,mLatestIndex) ;
					auto &r4x = _SWITCH_ (
						(ix == VAR_NONE) ? ix :
						mNodeHeap[iy].mBrother) ;
					r4x = mLatestIndex ;
					iy = mLatestIndex ;
				}
				mRis >> RegularReader::SKIP_GAP ;
			}
			mLatestIndex = ix ;
		}

		//@info: $8->${eps}|<?xml version = "1.0" ?>|<?xml version = "1.0" encoding = "utf-8" ?>
		inline void update_shift_e8 () {
			if (mRis[0] != STRU8 ('<'))
				return ;
			if (mRis[1] != STRU8 ('?'))
				return ;
			mRis++ ;
			mRis++ ;
			mRis >> _PCSTRU8_ ("xml") ;
			mRis >> RegularReader::SKIP_GAP ;
			mRis >> _PCSTRU8_ ("version") ;
			mRis >> RegularReader::SKIP_GAP ;
			mRis >> _PCSTRU8_ ("=") ;
			mRis >> RegularReader::SKIP_GAP ;
			mRis >> _PCSTRU8_ ("\"1.0\"") ;
			mRis >> RegularReader::SKIP_GAP ;
			if switch_case (TRUE) {
				if (mRis[0] == STRU8 ('?'))
					discard ;
				mRis >> _PCSTRU8_ ("encoding") ;
				mRis >> RegularReader::SKIP_GAP ;
				mRis >> _PCSTRU8_ ("=") ;
				mRis >> RegularReader::SKIP_GAP ;
				mRis >> _PCSTRU8_ ("\"utf-8\"") ;
				mRis >> RegularReader::SKIP_GAP ;
			}
			mRis >> _PCSTRU8_ ("?>") ;
		}

		//@info: $9->${end}
		inline void update_shift_e9 () {
			_DYNAMIC_ASSERT_ (mRis[0] == STRU8 ('\0')) ;
		}

		inline void update_heap () {
			mAttributeMappingSoftSet.clean () ;
			mObjectSoftSet.clean () ;
			mHeap = SharedRef<FixedBuffer<Node>>::make (mNodeHeap.length ()) ;
			INDEX iw = 0 ;
			for (auto &&i : _RANGE_ (0 ,mNodeHeap.size ())) {
				if (!mNodeHeap.used (i))
					continue ;
				mHeap.self[iw++] = std::move (mNodeHeap[i]) ;
			}
			_DEBUG_ASSERT_ (iw == mHeap->size ()) ;
		}

		inline void refresh () {
			mContext.mHeap = std::move (mHeap) ;
			mContext.mIndex = mRoot ;
		}
	} ;
	_CALL_ (Lambda ((*this) ,data)) ;
}

inline exports void XmlParser::initialize (const Array<XmlParser> &sequence) {
	using FOUND_NODE = typename Detail::FOUND_NODE ;
	using STACK_NODE = typename Detail::STACK_NODE ;
	class Lambda final
		:private Proxy {
	private:
		XmlParser &mContext ;
		const Array<XmlParser> &mSequence ;
		const String<STRU8> mClazzString ;
		const String<STRU8> mTableClazzString ;
		const String<STRU8> mObjectClazzString ;
		const String<STRU8> mArrayClazzString ;
		const String<STRU8> mFinalClazzString ;

		Deque<STACK_NODE> mNodeStack ;
		Array<Function<DEF<void (const XmlParser &)> NONE::*>> mFoundNodeProc ;
		Set<EFLAG> mFoundNodeProcMappingSet ;
		SoftSet<String<STRU8>> mAttributeMappingSoftSet ;
		SoftSet<INDEX> mMemberSoftSet ;
		SoftSet<String<STRU8>> mObjectSoftSet ;
		Allocator<Node ,SAUTO> mNodeHeap ;
		Deque<FOUND_NODE> mFoundNode ;
		Set<String<STRU8>> mFoundNodeMappingSet ;
		SharedRef<FixedBuffer<Node>> mHeap ;
		INDEX mRoot ;

		Deque<Deque<XmlParser>> mFoundNodeBaseNodeHeap ;
		STACK_NODE mTempNode ;

	public:
		inline explicit Lambda (XmlParser &context_ ,const Array<XmlParser> &sequence)
			: mContext (context_) ,mSequence (sequence) ,mClazzString (_PCSTRU8_ ("type")) ,mTableClazzString (_PCSTRU8_ ("table")) ,mObjectClazzString (_PCSTRU8_ ("object")) ,mArrayClazzString (_PCSTRU8_ ("array")) ,mFinalClazzString (_PCSTRU8_ ("final")) {}

		inline void operator() () {
			prepare () ;
			generate () ;
			refresh () ;
		}

	private:
		inline void prepare () {
			mNodeStack = Deque<STACK_NODE> () ;
			//@error: fuck g++4.8
			mFoundNodeProc = Array<Function<DEF<void (const XmlParser &)> NONE::*>> (3) ;
			mFoundNodeProcMappingSet.add (EFLAG (NODE_CLAZZ_TABLE) ,0) ;
			mFoundNodeProcMappingSet.add (EFLAG (NODE_CLAZZ_OBJECT) ,1) ;
			mFoundNodeProcMappingSet.add (EFLAG (NODE_CLAZZ_ARRAY) ,2) ;
			mFoundNodeProcMappingSet.add (EFLAG (NODE_CLAZZ_FINAL) ,0) ;
			mFoundNodeProc[0] = Function<DEF<void (const XmlParser &)> NONE::*> (PhanRef<Lambda>::make ((*this)) ,&Lambda::update_found_table_node) ;
			mFoundNodeProc[1] = Function<DEF<void (const XmlParser &)> NONE::*> (PhanRef<Lambda>::make ((*this)) ,&Lambda::update_found_object_node) ;
			mFoundNodeProc[2] = Function<DEF<void (const XmlParser &)> NONE::*> (PhanRef<Lambda>::make ((*this)) ,&Lambda::update_found_array_node) ;
			mAttributeMappingSoftSet = SoftSet<String<STRU8>> (0) ;
			mMemberSoftSet = SoftSet<INDEX> (0) ;
			mObjectSoftSet = SoftSet<String<STRU8>> (0) ;
			mNodeHeap = Allocator<Node ,SAUTO> () ;
			mRoot = mNodeHeap.alloc () ;
			mNodeHeap[mRoot].mMemberSet = mMemberSoftSet.share () ;
			mNodeHeap[mRoot].mObjectSet = mObjectSoftSet.share () ;
			mNodeHeap[mRoot].mParent = VAR_NONE ;
			mNodeHeap[mRoot].mChild = VAR_NONE ;
			mNodeHeap[mRoot].mBrother = VAR_NONE ;
			mFoundNode = Deque<FOUND_NODE> () ;
		}

		inline EFLAG node_type (const XmlParser &node) const {
			auto &r1x = node.attribute (mClazzString) ;
			if (r1x == mTableClazzString)
				return NODE_CLAZZ_TABLE ;
			if (r1x == mObjectClazzString)
				return NODE_CLAZZ_OBJECT ;
			if (r1x == mArrayClazzString)
				return NODE_CLAZZ_ARRAY ;
			if (r1x == mFinalClazzString)
				return NODE_CLAZZ_FINAL ;
			_DYNAMIC_ASSERT_ (r1x.empty ()) ;
			return NODE_CLAZZ_TABLE ;
		}

		inline void generate () {
			update_root_node () ;
			while (TRUE) {
				if (mNodeStack.empty ())
					break ;
				mTempNode = std::move (mNodeStack[mNodeStack.tail ()]) ;
				mNodeStack.pop () ;
				for (auto &&i : mTempNode.mBaseNode) {
					INDEX ix = mFoundNodeProcMappingSet.map (mTempNode.mClazz) ;
					mFoundNodeProc[ix] (i) ;
				}
				update_merge_found_node (mTempNode.mParent) ;
				mFoundNodeBaseNodeHeap.add (std::move (mTempNode.mBaseNode)) ;
			}
			update_heap () ;
		}

		inline void update_root_node () {
			INDEX ix = find_normal_node () ;
			if (ix == VAR_NONE)
				return ;
			INDEX jx = mNodeStack.insert () ;
			mNodeStack[jx].mBaseNode = Deque<XmlParser> (mSequence.length ()) ;
			for (auto &&i : mSequence) {
				if (!i.exist ())
					continue ;
				mNodeStack[jx].mBaseNode.add (i) ;
			}
			mNodeStack[jx].mClazz = NODE_CLAZZ_OBJECT ;
			mNodeStack[jx].mParent = mRoot ;
		}

		inline INDEX find_normal_node () const {
			for (auto &&i : mSequence)
				if (i.exist ())
					return mSequence.at (i) ;
			return VAR_NONE ;
		}

		inline void update_found_table_node (const XmlParser &node) {
			for (XmlParser i = node ,it ; i.exist () ; i = it) {
				it = i.brother () ;
				INDEX ix = mFoundNode.insert () ;
				mFoundNode[ix].mName = i.name () ;
				mFoundNode[ix].mClazz = node_type (i) ;
				mFoundNode[ix].mAttributeList = Deque<String<STRU8>> () ;
				mFoundNode[ix].mAttributeMappingSet = mAttributeMappingSoftSet.share () ;
				mFoundNode[ix].mAttributeList.appand (i.mHeap.self[i.mIndex].mAttributeList) ;
				mFoundNode[ix].mAttributeMappingSet.appand (i.mHeap.self[i.mIndex].mAttributeMappingSet) ;
				if (mFoundNodeBaseNodeHeap.empty ())
					mFoundNodeBaseNodeHeap.add (Deque<XmlParser> ()) ;
				mFoundNodeBaseNodeHeap.take (mFoundNode[ix].mBaseNode) ;
				mFoundNode[ix].mBaseNode.clear () ;
				mFoundNode[ix].mBaseNode.add (i.child ()) ;
			}
		}

		inline void update_found_object_node (const XmlParser &node) {
			for (XmlParser i = node ,it ; i.exist () ; i = it) {
				it = i.brother () ;
				const auto r1x = i.name () ;
				const auto r2x = node_type (i) ;
				INDEX ix = mFoundNodeMappingSet.map (r1x) ;
				if switch_case (TRUE) {
					if (ix == VAR_NONE)
						discard ;
					_DYNAMIC_ASSERT_ (mFoundNode[ix].mClazz == r2x) ;
					_DYNAMIC_ASSERT_ (r2x != NODE_CLAZZ_FINAL) ;
				}
				INDEX iy = ix ;
				if switch_case (TRUE) {
					if (ix != VAR_NONE)
						discard ;
					iy = mFoundNode.insert () ;
					mFoundNodeMappingSet.add (r1x ,iy) ;
					mFoundNode[iy].mName = r1x ;
					mFoundNode[iy].mClazz = r2x ;
					mFoundNode[iy].mAttributeList = Deque<String<STRU8>> () ;
					mFoundNode[iy].mAttributeMappingSet = mAttributeMappingSoftSet.share () ;
					if (mFoundNodeBaseNodeHeap.empty ())
						mFoundNodeBaseNodeHeap.add (Deque<XmlParser> ()) ;
					mFoundNodeBaseNodeHeap.take (mFoundNode[iy].mBaseNode) ;
					mFoundNode[iy].mBaseNode.clear () ;
				}
				mFoundNode[iy].mAttributeList.appand (i.mHeap.self[i.mIndex].mAttributeList) ;
				mFoundNode[iy].mAttributeMappingSet.appand (i.mHeap.self[i.mIndex].mAttributeMappingSet) ;
				mFoundNode[iy].mBaseNode.add (i.child ()) ;
			}
		}

		inline void update_found_array_node (const XmlParser &node) {
			for (XmlParser i = node ,it ; i.exist () ; i = it) {
				it = i.brother () ;
				const auto r1x = i.name () ;
				const auto r2x = node_type (i) ;
				INDEX ix = mFoundNode.head () ;
				if switch_case (TRUE) {
					if (ix == VAR_NONE)
						discard ;
					_DYNAMIC_ASSERT_ (mFoundNode[ix].mName == r1x) ;
					_DYNAMIC_ASSERT_ (r2x != NODE_CLAZZ_FINAL) ;
				}
				INDEX iy = mFoundNode.insert () ;
				mFoundNodeMappingSet.add (r1x ,iy) ;
				mFoundNode[iy].mName = r1x ;
				mFoundNode[iy].mClazz = r2x ;
				mFoundNode[iy].mAttributeList = Deque<String<STRU8>> () ;
				mFoundNode[iy].mAttributeMappingSet = mAttributeMappingSoftSet.share () ;
				mFoundNode[iy].mAttributeList.appand (i.mHeap.self[i.mIndex].mAttributeList) ;
				mFoundNode[iy].mAttributeMappingSet.appand (i.mHeap.self[i.mIndex].mAttributeMappingSet) ;
				if (mFoundNodeBaseNodeHeap.empty ())
					mFoundNodeBaseNodeHeap.add (Deque<XmlParser> ()) ;
				mFoundNodeBaseNodeHeap.take (mFoundNode[iy].mBaseNode) ;
				mFoundNode[iy].mBaseNode.clear () ;
				mFoundNode[iy].mBaseNode.add (i.child ()) ;
			}
		}

		inline void update_merge_found_node (INDEX curr) {
			INDEX ix = VAR_NONE ;
			INDEX iy = VAR_NONE ;
			for (auto &&i : mFoundNode) {
				iy = ix ;
				ix = mNodeHeap.alloc () ;
				mNodeHeap[ix].mName = std::move (i.mName) ;
				mNodeHeap[ix].mAttributeList = std::move (i.mAttributeList) ;
				mNodeHeap[ix].mAttributeMappingSet = std::move (i.mAttributeMappingSet) ;
				mNodeHeap[ix].mParent = curr ;
				if switch_case (TRUE) {
					INDEX jx = mNodeHeap[ix].mParent ;
					if (jx == VAR_NONE)
						discard ;
					if (mNodeHeap[jx].mChild == VAR_NONE)
						mNodeHeap[jx].mChild = ix ;
					if switch_case (TRUE) {
						if (mNodeHeap[jx].mMemberSet.size () > 0)
							discard ;
						mNodeHeap[jx].mMemberSet = mMemberSoftSet.share () ;
						mNodeHeap[jx].mObjectSet = mObjectSoftSet.share () ;
					}
					const auto r1x = mNodeHeap[jx].mMemberSet.length () ;
					mNodeHeap[jx].mMemberSet.add (r1x ,ix) ;
					mNodeHeap[jx].mObjectSet.add (mNodeHeap[ix].mName ,ix) ;
				}
				mNodeHeap[ix].mBrother = VAR_NONE ;
				mNodeHeap[ix].mChild = VAR_NONE ;
				if (iy != VAR_NONE)
					mNodeHeap[iy].mBrother = ix ;
				if (mRoot == VAR_NONE)
					mRoot = ix ;
				INDEX jy = mNodeStack.insert () ;
				mNodeStack[jy].mBaseNode = std::move (i.mBaseNode) ;
				mNodeStack[jy].mClazz = i.mClazz ;
				mNodeStack[jy].mParent = ix ;
			}
			mFoundNodeMappingSet.clear () ;
			mFoundNode.clear () ;
		}

		inline void update_heap () {
			mAttributeMappingSoftSet.clean () ;
			mObjectSoftSet.clean () ;
			mHeap = SharedRef<FixedBuffer<Node>>::make (mNodeHeap.length ()) ;
			INDEX iw = 0 ;
			for (auto &&i : _RANGE_ (0 ,mNodeHeap.size ())) {
				if (!mNodeHeap.used (i))
					continue ;
				mHeap.self[iw++] = std::move (mNodeHeap[i]) ;
			}
			_DEBUG_ASSERT_ (iw == mHeap->size ()) ;
		}

		inline void refresh () {
			mContext.mHeap = std::move (mHeap) ;
			mContext.mIndex = mRoot ;
		}
	} ;
	_CALL_ (Lambda ((*this) ,sequence)) ;
}

class JsonParser {
private:
	static constexpr auto NODE_CLAZZ_NULL = EFLAG (1) ;
	static constexpr auto NODE_CLAZZ_STRING = EFLAG (2) ;
	static constexpr auto NODE_CLAZZ_ARRAY = EFLAG (3) ;
	static constexpr auto NODE_CLAZZ_OBJECT = EFLAG (4) ;

	class Node {
	private:
		friend JsonParser ;
		AnyRef<void> mValue ;
		EFLAG mClazz ;
		INDEX mParent ;
		INDEX mBrother ;
		INDEX mChild ;

	public:
		inline Node () = default ;
	} ;

private:
	struct Detail ;
	SharedRef<FixedBuffer<Node>> mHeap ;
	INDEX mIndex ;

public:
	JsonParser () {
		mIndex = VAR_NONE ;
	}

	BOOL exist () const {
		if (!mHeap.exist ())
			return FALSE ;
		if (mIndex == VAR_NONE)
			return FALSE ;
		if (mHeap.self[mIndex].mClazz == NODE_CLAZZ_NULL)
			return FALSE ;
		return TRUE ;
	}

	BOOL string_type () const {
		if (mHeap.self[mIndex].mClazz != NODE_CLAZZ_STRING)
			return FALSE ;
		return TRUE ;
	}

	BOOL array_type () const {
		if (mHeap.self[mIndex].mClazz != NODE_CLAZZ_ARRAY)
			return FALSE ;
		return TRUE ;
	}

	BOOL object_type () const {
		if (mHeap.self[mIndex].mClazz != NODE_CLAZZ_OBJECT)
			return FALSE ;
		return TRUE ;
	}

	JsonParser root () const {
		if (!exist ())
			return JsonParser (mHeap ,VAR_NONE) ;
		return JsonParser (mHeap ,0) ;
	}

	JsonParser parent () const {
		if (!exist ())
			return JsonParser (mHeap ,VAR_NONE) ;
		return JsonParser (mHeap ,mHeap.self[mIndex].mParent) ;
	}

	JsonParser brother () const {
		if (!exist ())
			return JsonParser (mHeap ,VAR_NONE) ;
		return JsonParser (mHeap ,mHeap.self[mIndex].mBrother) ;
	}

	JsonParser child () const {
		if (!exist ())
			return JsonParser (mHeap ,VAR_NONE) ;
		return JsonParser (mHeap ,mHeap.self[mIndex].mChild) ;
	}

	JsonParser child (const String<STRU8> &key) const {
		if (!exist ())
			return JsonParser (mHeap ,VAR_NONE) ;
		if (!object_type ())
			return JsonParser (mHeap ,VAR_NONE) ;
		auto &r1x = mHeap.self[mIndex].mValue.rebind<SoftSet<String<STRU8>>> ().self ;
		INDEX ix = r1x.map (key) ;
		return JsonParser (mHeap ,ix) ;
	}

	Array<JsonParser> child_array () const {
		Array<JsonParser> ret ;
		if switch_case (TRUE) {
			if (!exist ())
				discard ;
			if (!array_type ())
				discard ;
			auto &r1x = mHeap.self[mIndex].mValue.rebind<SoftSet<INDEX>> ().self ;
			ret = Array<JsonParser> (r1x.length ()) ;
			INDEX iw = 0 ;
			for (auto &&i : r1x)
				ret[iw++] = JsonParser (mHeap ,i.mapx) ;
			_DEBUG_ASSERT_ (iw == ret.length ()) ;
		}
		return std::move (ret) ;
	}

	Array<JsonParser> child_array (LENGTH fixed_len) const {
		Array<JsonParser> ret = Array<JsonParser> (fixed_len) ;
		INDEX iw = 0 ;
		if switch_case (TRUE) {
			if (!exist ())
				discard ;
			if (!array_type ())
				discard ;
			auto &r1x = mHeap.self[mIndex].mValue.rebind<SoftSet<INDEX>> ().self ;
			for (auto &&i : r1x) {
				INDEX ix = iw++ ;
				if (ix >= ret.size ())
					continue ;
				ret[ix] = JsonParser (mHeap ,i.mapx) ;
			}
		}
		return std::move (ret) ;
	}

	BOOL equal (const JsonParser &that) const {
		if (!exist ())
			if (!that.exist ())
				return TRUE ;
		if (!exist ())
			return FALSE ;
		if (!that.exist ())
			return FALSE ;
		if (&mHeap.self != &that.mHeap.self)
			return FALSE ;
		if (mIndex != that.mIndex)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const JsonParser &that) const {
		return equal (that) ;
	}

	inline BOOL operator!= (const JsonParser &that) const {
		return !equal (that) ;
	}

	const String<STRU8> &value () const & {
		_DYNAMIC_ASSERT_ (exist ()) ;
		_DYNAMIC_ASSERT_ (string_type ()) ;
		return mHeap.self[mIndex].mValue.rebind<String<STRU8>> () ;
	}

	auto value () && ->void = delete ;

	template <class _ARG1>
	_ARG1 value (const _ARG1 &def ,const Function<_ARG1 (const String<STRU8> &)> &convert) const {
		_ARG1 ret ;
		_CALL_TRY_ ([&] () {
			ret = convert (value ()) ;
		} ,[&] () {
			ret = def ;
		}) ;
		return std::move (ret) ;
	}

	BOOL value (const BOOL &def) const {
		const auto r1x = Function<BOOL (const String<STRU8> &)> (&_PARSEBOOLS_<STRU8>) ;
		return value (def ,r1x) ;
	}

	PTR<const VOID> value (const PTR<const VOID> &) const = delete ;

	VAR32 value (const VAR32 &def) const {
		const auto r1x = Function<VAR32 (const String<STRU8> &)> (&_PARSEVAR32S_<STRU8>) ;
		return value (def ,r1x) ;
	}

	VAR64 value (const VAR64 &def) const {
		const auto r1x = Function<VAR64 (const String<STRU8> &)> (&_PARSEVAR64S_<STRU8>) ;
		return value (def ,r1x) ;
	}

	VAL32 value (const VAL32 &def) const {
		const auto r1x = Function<VAL32 (const String<STRU8> &)> (&_PARSEVAL32S_<STRU8>) ;
		return value (def ,r1x) ;
	}

	VAL64 value (const VAL64 &def) const {
		const auto r1x = Function<VAL64 (const String<STRU8> &)> (&_PARSEVAL64S_<STRU8>) ;
		return value (def ,r1x) ;
	}

	String<STRU8> value (const String<STRU8> &def) const {
		const auto r1x = Function<String<STRU8> (const String<STRU8> &)> (&_COPY_<String<STRU8>>) ;
		return value (def ,r1x) ;
	}

	String<STRU16> value (const String<STRU16> &def) const {
		const auto r1x = Function<String<STRU16> (const String<STRU8> &)> (&_U8STOU16S_) ;
		return value (def ,r1x) ;
	}

	String<STRU32> value (const String<STRU32> &def) const {
		const auto r1x = Function<String<STRU32> (const String<STRU8> &)> (&_U8STOU32S_) ;
		return value (def ,r1x) ;
	}

	String<STRA> value (const String<STRA> &def) const {
		const auto r1x = Function<String<STRA> (const String<STRU8> &)> (&_U8STOAS_) ;
		return value (def ,r1x) ;
	}

	String<STRW> value (const String<STRW> &def) const {
		const auto r1x = Function<String<STRW> (const String<STRU8> &)> (&_U8STOWS_) ;
		return value (def ,r1x) ;
	}

	void friend_write (TextWriter<STRU8> &writer) const ;

public:
	inline static JsonParser make (const PhanBuffer<const STRU8> &data) {
		JsonParser ret ;
		ret.initialize (data) ;
		return std::move (ret) ;
	}

private:
	explicit JsonParser (const SharedRef<FixedBuffer<Node>> &heap ,INDEX index)
		:mHeap (heap) ,mIndex (index) {}

private:
	void initialize (const PhanBuffer<const STRU8> &data) ;

	Set<PTR<const String<STRU8>>> object_key_adress_set () const {
		Set<PTR<const String<STRU8>>> ret = Set<PTR<const String<STRU8>>> (mHeap->size ()) ;
		for (auto &&i : _RANGE_ (0 ,mHeap->size ())) {
			if (mHeap.self[i].mClazz != NODE_CLAZZ_OBJECT)
				continue ;
			auto &r1x = mHeap.self[i].mValue.rebind<SoftSet<String<STRU8>>> ().self ;
			for (auto &&j : r1x)
				ret.add (&j.key) ;
		}
		return std::move (ret) ;
	}
} ;

struct JsonParser::Detail {
	class RecursiveCounter
		:private Wrapped<LENGTH> {
	public:
		inline void lock () {
			_DYNAMIC_ASSERT_ (RecursiveCounter::mSelf <= DEFAULT_RECURSIVE_SIZE::value) ;
			RecursiveCounter::mSelf++ ;
		}

		inline void unlock () {
			RecursiveCounter::mSelf-- ;
		}
	} ;
} ;

inline exports void JsonParser::friend_write (TextWriter<STRU8> &writer) const {
	static constexpr auto M_NODE_X1 = EFLAG (1) ;
	static constexpr auto M_NODE_X2 = EFLAG (2) ;
	static constexpr auto M_NODE_X3 = EFLAG (3) ;
	static constexpr auto M_NODE_X4 = EFLAG (4) ;
	static constexpr auto M_NODE_X5 = EFLAG (5) ;
	static constexpr auto M_NODE_X6 = EFLAG (6) ;
	static constexpr auto M_NODE_X7 = EFLAG (7) ;
	static constexpr auto M_NODE_X8 = EFLAG (8) ;
	static constexpr auto M_NODE_X9 = EFLAG (9) ;
	auto rax = Deque<PACK<INDEX ,EFLAG>> () ;
	auto rbx = Deque<PACK<INDEX ,EFLAG>> () ;
	rax.add (PACK<INDEX ,EFLAG> {mIndex ,M_NODE_X1}) ;
	const auto r1x = object_key_adress_set () ;
	while (TRUE) {
		if (rax.empty ())
			break ;
		const auto r2x = rax[rax.tail ()] ;
		rax.pop () ;
		auto fax = TRUE ;
		if switch_case (fax) {
			//@info: case 'null'
			if (!(r2x.P1 != VAR_NONE))
				discard ;
			if (!(mHeap.self[r2x.P1].mClazz == NODE_CLAZZ_NULL))
				discard ;
			if (!(r2x.P2 == M_NODE_X1))
				discard ;
			writer << _PCSTRU8_ ("null") ;
		}
		if switch_case (fax) {
			//@info: case '"xxx"'
			if (!(r2x.P1 != VAR_NONE))
				discard ;
			if (!(mHeap.self[r2x.P1].mClazz == NODE_CLAZZ_STRING))
				discard ;
			if (!(r2x.P2 == M_NODE_X1))
				discard ;
			auto &r3x = mHeap.self[r2x.P1].mValue.rebind<String<STRU8>> ().self ;
			writer << _PCSTRU8_ ("\"") ;
			writer << r3x ;
			writer << _PCSTRU8_ ("\"") ;
		}
		if switch_case (fax) {
			//@info: case '[(yyy(,yyy)*)?]'
			if (!(r2x.P1 != VAR_NONE))
				discard ;
			if (!(mHeap.self[r2x.P1].mClazz == NODE_CLAZZ_ARRAY))
				discard ;
			if (!(r2x.P2 == M_NODE_X1))
				discard ;
			auto &r4x = mHeap.self[r2x.P1].mValue.rebind<SoftSet<INDEX>> ().self ;
			rbx.clear () ;
			rbx.add (PACK<INDEX ,EFLAG> {VAR_NONE ,M_NODE_X3}) ;
			INDEX ir = 0 ;
			for (auto &&i : r4x) {
				if (ir > 0)
					rbx.add (PACK<INDEX ,EFLAG> {VAR_NONE ,M_NODE_X4}) ;
				ir++ ;
				rbx.add (PACK<INDEX ,EFLAG> {i.mapx ,M_NODE_X1}) ;
			}
			rbx.add (PACK<INDEX ,EFLAG> {VAR_NONE ,M_NODE_X5}) ;
			while (TRUE) {
				if (rbx.empty ())
					break ;
				rax.add (rbx[rbx.tail ()]) ;
				rbx.pop () ;
			}
		}
		if switch_case (fax) {
			//@info: case '{("xxx":yyy(,"xxx":yyy)*)?}'
			if (!(r2x.P1 != VAR_NONE))
				discard ;
			if (!(mHeap.self[r2x.P1].mClazz == NODE_CLAZZ_OBJECT))
				discard ;
			if (!(r2x.P2 == M_NODE_X1))
				discard ;
			auto &r5x = mHeap.self[r2x.P1].mValue.rebind<SoftSet<String<STRU8>>> ().self ;
			rbx.clear () ;
			rbx.add (PACK<INDEX ,EFLAG> {VAR_NONE ,M_NODE_X6}) ;
			INDEX ir = 0 ;
			for (auto &&i : r5x) {
				if (ir > 0)
					rbx.add (PACK<INDEX ,EFLAG> {VAR_NONE ,M_NODE_X7}) ;
				ir++ ;
				INDEX ix = r1x.find (&i.key) ;
				rbx.add (PACK<INDEX ,EFLAG> {ix ,M_NODE_X2}) ;
				rbx.add (PACK<INDEX ,EFLAG> {VAR_NONE ,M_NODE_X8}) ;
				rbx.add (PACK<INDEX ,EFLAG> {i.mapx ,M_NODE_X1}) ;
			}
			rbx.add (PACK<INDEX ,EFLAG> {VAR_NONE ,M_NODE_X9}) ;
			while (TRUE) {
				if (rbx.empty ())
					break ;
				rax.add (rbx[rbx.tail ()]) ;
				rbx.pop () ;
			}
		}
		if switch_case (fax) {
			if (!(r2x.P1 != VAR_NONE))
				discard ;
			if (!(r2x.P2 == M_NODE_X2))
				discard ;
			writer << _PCSTRU8_ ("\"") ;
			auto &r6x = (*r1x[r2x.P1].key) ;
			writer << r6x ;
			writer << _PCSTRU8_ ("\"") ;
		}
		if switch_case (fax) {
			if (!(r2x.P1 == VAR_NONE))
				discard ;
			if (!(r2x.P2 == M_NODE_X3))
				discard ;
			writer << _PCSTRU8_ ("[") ;
		}
		if switch_case (fax) {
			if (!(r2x.P1 == VAR_NONE))
				discard ;
			if (!(r2x.P2 == M_NODE_X4))
				discard ;
			writer << _PCSTRU8_ (",") ;
		}
		if switch_case (fax) {
			if (!(r2x.P1 == VAR_NONE))
				discard ;
			if (!(r2x.P2 == M_NODE_X5))
				discard ;
			writer << _PCSTRU8_ ("]") ;
		}
		if switch_case (fax) {
			if (!(r2x.P1 == VAR_NONE))
				discard ;
			if (!(r2x.P2 == M_NODE_X6))
				discard ;
			writer << _PCSTRU8_ ("{") ;
		}
		if switch_case (fax) {
			if (!(r2x.P1 == VAR_NONE))
				discard ;
			if (!(r2x.P2 == M_NODE_X7))
				discard ;
			writer << _PCSTRU8_ (",") ;
		}
		if switch_case (fax) {
			if (!(r2x.P1 == VAR_NONE))
				discard ;
			if (!(r2x.P2 == M_NODE_X8))
				discard ;
			writer << _PCSTRU8_ (":") ;
		}
		if switch_case (fax) {
			if (!(r2x.P1 == VAR_NONE))
				discard ;
			if (!(r2x.P2 == M_NODE_X9))
				discard ;
			writer << _PCSTRU8_ ("}") ;
		}
	}
}

inline exports void JsonParser::initialize (const PhanBuffer<const STRU8> &data) {
	using RecursiveCounter = typename Detail::RecursiveCounter ;
	class Lambda final
		:private Proxy {
	private:
		JsonParser &mContext ;

		TextReader<STRU8> mTextReader ;
		RegularReader mRis ;
		LENGTH mRecursiveCounter ;
		INDEX mLatestIndex ;
		String<STRU8> mLatestString ;

		SoftSet<INDEX> mArraySoftSet ;
		SoftSet<String<STRU8>> mObjectSoftSet ;
		Allocator<Node ,SAUTO> mNodeHeap ;
		SharedRef<FixedBuffer<Node>> mHeap ;
		INDEX mRoot ;

	public:
		inline explicit Lambda (JsonParser &context_ ,const PhanBuffer<const STRU8> &data)
			: mContext (context_) ,mTextReader (data) {}

		inline void operator() () {
			prepare () ;
			generate () ;
			refresh () ;
		}

	private:
		inline void prepare () {
			mRis = RegularReader (PhanRef<TextReader<STRU8>>::make (mTextReader) ,2) ;
			mRecursiveCounter = 0 ;
			mArraySoftSet = SoftSet<INDEX> (0) ;
			mObjectSoftSet = SoftSet<String<STRU8>> (0) ;
			mNodeHeap = Allocator<Node ,SAUTO> () ;
			mHeap = SharedRef<FixedBuffer<Node>> () ;
			mRoot = VAR_NONE ;
		}

		inline void generate () {
			/*
			*	$0->$11 $10 $12
			*	$1->${value}
			*	$2->true|TRUE|false|FALSE
			*	$2x->null
			*	$3->"${string}"
			*	$4->$1|$2|$2x|$3|$6|$9
			*	$5->$4|$4 , $5
			*	$6->[ ]|[ $5 ]
			*	$7->$3 : $4
			*	$8->$7|$7 , $8
			*	$9->{ }|{ $8 }
			*	$10->${eps}|$4
			*	$11->${eps}
			*	$12->${end}
			*/
			update_shift_e0 () ;
			_DEBUG_ASSERT_ (mLatestIndex == 0) ;
			mRoot = mLatestIndex ;
			update_heap () ;
		}

		//@info: $0->$11 $10 $12
		inline void update_shift_e0 () {
			update_shift_e11 () ;
			mRis >> RegularReader::SKIP_GAP ;
			update_shift_e10 () ;
			INDEX ix = mLatestIndex ;
			mRis >> RegularReader::SKIP_GAP ;
			update_shift_e12 () ;
			mLatestIndex = ix ;
		}

		//@info: $1->${value}
		inline void update_shift_e1 () {
			mRis >> RegularReader::HINT_VALUE_TEXT >> mLatestString ;
		}

		//@info: $2->true|TRUE|false|FALSE
		inline void update_shift_e2 () {
			auto fax = TRUE ;
			if switch_case (fax) {
				if (!(mRis[0] == STRU8 ('t')))
					discard ;
				mRis >> _PCSTRU8_ ("true") ;
				mLatestString = _PCSTRU8_ ("true") ;
			}
			if switch_case (fax) {
				if (!(mRis[0] == STRU8 ('T')))
					discard ;
				mRis >> _PCSTRU8_ ("TRUE") ;
				mLatestString = _PCSTRU8_ ("TRUE") ;
			}
			if switch_case (fax) {
				if (!(mRis[0] == STRU8 ('f')))
					discard ;
				mRis >> _PCSTRU8_ ("false") ;
				mLatestString = _PCSTRU8_ ("false") ;
			}
			if switch_case (fax) {
				if (!(mRis[0] == STRU8 ('F')))
					discard ;
				mRis >> _PCSTRU8_ ("FALSE") ;
				mLatestString = _PCSTRU8_ ("FALSE") ;
			}
			if switch_case (fax) {
				_DYNAMIC_ASSERT_ (FALSE) ;
			}
		}

		//@info: $2x->null
		inline void update_shift_e2x () {
			mRis >> _PCSTRU8_ ("null") ;
			mLatestString = String<STRU8> () ;
		}

		//@info: $3->"${string}"
		inline void update_shift_e3 () {
			mRis >> RegularReader::HINT_STRING_TEXT >> mLatestString ;
		}

		//@info: $4->$1|$2|$2x|$3|$6|$9
		inline void update_shift_e4 (INDEX curr) {
			ScopedGuard<RecursiveCounter> ANONYMOUS (_CAST_<RecursiveCounter> (mRecursiveCounter)) ;
			INDEX ix = VAR_NONE ;
			auto fax = TRUE ;
			if switch_case (fax) {
				if (!(mRis[0] == STRU8 ('+') || mRis[0] == STRU8 ('-')))
					if (!(mRis[0] >= STRU8 ('0') && mRis[0] <= STRU8 ('9')))
						discard ;
				ix = mNodeHeap.alloc () ;
				update_shift_e1 () ;
				mNodeHeap[ix].mValue = AnyRef<String<STRU8>>::make (std::move (mLatestString)) ;
				mNodeHeap[ix].mClazz = NODE_CLAZZ_STRING ;
				mNodeHeap[ix].mParent = curr ;
				mNodeHeap[ix].mBrother = VAR_NONE ;
				mNodeHeap[ix].mChild = VAR_NONE ;
			}
			if switch_case (fax) {
				if (!(mRis[0] == STRU8 ('t') || mRis[0] == STRU8 ('T')))
					if (!(mRis[0] == STRU8 ('f') || mRis[0] == STRU8 ('F')))
						discard ;
				ix = mNodeHeap.alloc () ;
				update_shift_e2 () ;
				mNodeHeap[ix].mValue = AnyRef<String<STRU8>>::make (std::move (mLatestString)) ;
				mNodeHeap[ix].mClazz = NODE_CLAZZ_STRING ;
				mNodeHeap[ix].mParent = curr ;
				mNodeHeap[ix].mBrother = VAR_NONE ;
				mNodeHeap[ix].mChild = VAR_NONE ;
			}
			if switch_case (fax) {
				if (!(mRis[0] == STRU8 ('n')))
					discard ;
				ix = mNodeHeap.alloc () ;
				update_shift_e2x () ;
				mNodeHeap[ix].mClazz = NODE_CLAZZ_NULL ;
				mNodeHeap[ix].mParent = curr ;
				mNodeHeap[ix].mBrother = VAR_NONE ;
				mNodeHeap[ix].mChild = VAR_NONE ;
			}
			if switch_case (fax) {
				if (!(mRis[0] == STRU8 ('\"')))
					discard ;
				ix = mNodeHeap.alloc () ;
				update_shift_e3 () ;
				mNodeHeap[ix].mValue = AnyRef<String<STRU8>>::make (std::move (mLatestString)) ;
				mNodeHeap[ix].mClazz = NODE_CLAZZ_STRING ;
				mNodeHeap[ix].mParent = curr ;
				mNodeHeap[ix].mBrother = VAR_NONE ;
				mNodeHeap[ix].mChild = VAR_NONE ;
			}
			if switch_case (fax) {
				if (!(mRis[0] == STRU8 ('[')))
					discard ;
				update_shift_e6 (curr) ;
				ix = mLatestIndex ;
			}
			if switch_case (fax) {
				if (!(mRis[0] == STRU8 ('{')))
					discard ;
				update_shift_e9 (curr) ;
				ix = mLatestIndex ;
			}
			if switch_case (fax) {
				_DYNAMIC_ASSERT_ (FALSE) ;
			}
			mLatestIndex = ix ;
		}

		//@info: $5->$4|$4 , $5
		inline void update_shift_e5 (INDEX curr) {
			INDEX ix = VAR_NONE ;
			INDEX iy = VAR_NONE ;
			while (TRUE) {
				update_shift_e4 (curr) ;
				auto &r1x = mNodeHeap[curr].mValue.rebind<SoftSet<INDEX>> ().self ;
				const auto r2x = r1x.length () ;
				r1x.add (r2x ,mLatestIndex) ;
				auto &r3x = _SWITCH_ (
					(ix == VAR_NONE) ? ix :
					mNodeHeap[iy].mBrother) ;
				r3x = mLatestIndex ;
				iy = mLatestIndex ;
				mRis >> RegularReader::SKIP_GAP ;
				if (mRis[0] != STRU8 (','))
					break ;
				mRis++ ;
				mRis >> RegularReader::SKIP_GAP ;
			}
			mLatestIndex = ix ;
		}

		//@info: $6->[ ]|[ $5 ]
		inline void update_shift_e6 (INDEX curr) {
			ScopedGuard<RecursiveCounter> ANONYMOUS (_CAST_<RecursiveCounter> (mRecursiveCounter)) ;
			mRis >> _PCSTRU8_ ("[") ;
			INDEX ix = mNodeHeap.alloc () ;
			mNodeHeap[ix].mValue = AnyRef<SoftSet<INDEX>>::make (mArraySoftSet.share ()) ;
			mNodeHeap[ix].mClazz = NODE_CLAZZ_ARRAY ;
			mNodeHeap[ix].mParent = curr ;
			mNodeHeap[ix].mBrother = VAR_NONE ;
			mNodeHeap[ix].mChild = VAR_NONE ;
			mRis >> RegularReader::SKIP_GAP ;
			if switch_case (TRUE) {
				if (mRis[0] == STRU8 (']'))
					discard ;
				update_shift_e5 (ix) ;
				mNodeHeap[ix].mChild = mLatestIndex ;
				mRis >> RegularReader::SKIP_GAP ;
			}
			mRis >> _PCSTRU8_ ("]") ;
			mLatestIndex = ix ;
		}

		//@info: $7->$3 : $4
		inline void update_shift_e7 (INDEX curr) {
			update_shift_e3 () ;
			const auto r1x = std::move (mLatestString) ;
			mRis >> RegularReader::SKIP_GAP ;
			mRis >> _PCSTRU8_ (":") ;
			mRis >> RegularReader::SKIP_GAP ;
			update_shift_e4 (curr) ;
			auto &r2x = mNodeHeap[curr].mValue.rebind<SoftSet<String<STRU8>>> ().self ;
			r2x.add (r1x ,mLatestIndex) ;
		}

		//@info: $8->$7|$7 , $8
		inline void update_shift_e8 (INDEX curr) {
			INDEX ix = VAR_NONE ;
			INDEX iy = VAR_NONE ;
			while (TRUE) {
				update_shift_e7 (curr) ;
				auto &r1x = _SWITCH_ (
					(ix == VAR_NONE) ? ix :
					mNodeHeap[iy].mBrother) ;
				r1x = mLatestIndex ;
				iy = mLatestIndex ;
				mRis >> RegularReader::SKIP_GAP ;
				if (mRis[0] != STRU8 (','))
					break ;
				mRis++ ;
				mRis >> RegularReader::SKIP_GAP ;
			}
			mLatestIndex = ix ;
		}

		//@info: $9->{ }|{ $8 }
		inline void update_shift_e9 (INDEX curr) {
			ScopedGuard<RecursiveCounter> ANONYMOUS (_CAST_<RecursiveCounter> (mRecursiveCounter)) ;
			mRis >> _PCSTRU8_ ("{") ;
			INDEX ix = mNodeHeap.alloc () ;
			mNodeHeap[ix].mValue = AnyRef<SoftSet<String<STRU8>>>::make (mObjectSoftSet.share ()) ;
			mNodeHeap[ix].mClazz = NODE_CLAZZ_OBJECT ;
			mNodeHeap[ix].mParent = curr ;
			mNodeHeap[ix].mBrother = VAR_NONE ;
			mNodeHeap[ix].mChild = VAR_NONE ;
			mRis >> RegularReader::SKIP_GAP ;
			if switch_case (TRUE) {
				if (mRis[0] == STRU8 ('}'))
					discard ;
				update_shift_e8 (ix) ;
				mNodeHeap[ix].mChild = mLatestIndex ;
				mRis >> RegularReader::SKIP_GAP ;
			}
			mRis >> _PCSTRU8_ ("}") ;
			mLatestIndex = ix ;
		}

		//@info: $10->${eps}|$4
		inline void update_shift_e10 () {
			INDEX ix = VAR_NONE ;
			if switch_case (TRUE) {
				if (mRis[0] == STRU8 ('\0'))
					discard ;
				update_shift_e4 (VAR_NONE) ;
				ix = mLatestIndex ;
			}
			mLatestIndex = ix ;
		}

		//@info: $11->${eps}
		inline void update_shift_e11 () {
			_STATIC_WARNING_ ("noop") ;
		}

		//@info: $12->${end}
		inline void update_shift_e12 () {
			_DYNAMIC_ASSERT_ (mRis[0] == STRU8 ('\0')) ;
		}

		inline void update_heap () {
			mArraySoftSet.clean () ;
			mObjectSoftSet.clean () ;
			mHeap = SharedRef<FixedBuffer<Node>>::make (mNodeHeap.length ()) ;
			INDEX iw = 0 ;
			for (auto &&i : _RANGE_ (0 ,mNodeHeap.size ())) {
				if (!mNodeHeap.used (i))
					continue ;
				mHeap.self[iw++] = std::move (mNodeHeap[i]) ;
			}
			_DEBUG_ASSERT_ (iw == mHeap->size ()) ;
		}

		inline void refresh () {
			mContext.mHeap = std::move (mHeap) ;
			mContext.mIndex = mRoot ;
		}
	} ;
	_CALL_ (Lambda ((*this) ,data)) ;
}

class CommandParser {
private:
	Set<String<STRU8>> mOptionSet ;
	Deque<String<STRU8>> mAttributeList ;
	Set<String<STRU8>> mAttributeMappingSet ;
	Array<String<STRU8>> mCommand ;

public:
	CommandParser () = delete ;

	explicit CommandParser (const PhanBuffer<const STRU8> &data) {
		initialize (data) ;
	}

	explicit CommandParser (VAR32 argc ,PTR<const PTR<STRA>> argv) {
		const auto r1x = _CALL_ ([&] () {
			String<STRU8> ret = String<STRU8>::make () ;
			auto wos = TextWriter<STRU8> (ret.raw ()) ;
			for (auto &&i : _RANGE_ (1 ,LENGTH (argc))) {
				wos << _ASTOU8S_ (PTRTOARR[argv[i]]) ;
				wos << _PCSTRU8_ (" ") ;
			}
			wos << _EOS_ ;
			return std::move (ret) ;
		}) ;
		initialize (r1x.raw ()) ;
	}

	BOOL option (const String<STRU8> &tag) const {
		INDEX ix = mOptionSet.find (tag) ;
		if (ix == VAR_NONE)
			return FALSE ;
		return TRUE ;
	}

	const String<STRU8> &attribute (const String<STRU8> &tag) const & {
		auto &r1x = _CACHE_ ([&] () {
			return String<STRU8> () ;
		}) ;
		INDEX ix = mAttributeMappingSet.map (tag) ;
		if (ix == VAR_NONE)
			return r1x ;
		return mAttributeList[ix] ;
	}

	auto attribute (const String<STRU8> &) && ->void = delete ;

	template <class _ARG1>
	_ARG1 attribute (const String<STRU8> &tag ,const _ARG1 &def ,const Function<_ARG1 (const String<STRU8> &)> &convert) const {
		_ARG1 ret ;
		_CALL_TRY_ ([&] () {
			ret = convert (attribute (tag)) ;
		} ,[&] () {
			ret = def ;
		}) ;
		return std::move (ret) ;
	}

	BOOL attribute (const String<STRU8> &tag ,const BOOL &def) const {
		const auto r1x = Function<BOOL (const String<STRU8> &)> (&_PARSEBOOLS_<STRU8>) ;
		return attribute (tag ,def ,r1x) ;
	}

	PTR<const VOID> attribute (const String<STRU8> & ,const PTR<const VOID> &) const = delete ;

	VAR32 attribute (const String<STRU8> &tag ,const VAR32 &def) const {
		const auto r1x = Function<VAR32 (const String<STRU8> &)> (&_PARSEVAR32S_<STRU8>) ;
		return attribute (tag ,def ,r1x) ;
	}

	VAR64 attribute (const String<STRU8> &tag ,const VAR64 &def) const {
		const auto r1x = Function<VAR64 (const String<STRU8> &)> (&_PARSEVAR64S_<STRU8>) ;
		return attribute (tag ,def ,r1x) ;
	}

	VAL32 attribute (const String<STRU8> &tag ,const VAL32 &def) const {
		const auto r1x = Function<VAL32 (const String<STRU8> &)> (&_PARSEVAL32S_<STRU8>) ;
		return attribute (tag ,def ,r1x) ;
	}

	VAL64 attribute (const String<STRU8> &tag ,const VAL64 &def) const {
		const auto r1x = Function<VAL64 (const String<STRU8> &)> (&_PARSEVAL64S_<STRU8>) ;
		return attribute (tag ,def ,r1x) ;
	}

	String<STRU8> attribute (const String<STRU8> &tag ,const String<STRU8> &def) const {
		const auto r1x = Function<String<STRU8> (const String<STRU8> &)> (&_COPY_<String<STRU8>>) ;
		return attribute (tag ,def ,r1x) ;
	}

	String<STRU16> attribute (const String<STRU8> &tag ,const String<STRU16> &def) const {
		const auto r1x = Function<String<STRU16> (const String<STRU8> &)> (&_U8STOU16S_) ;
		return attribute (tag ,def ,r1x) ;
	}

	String<STRU32> attribute (const String<STRU8> &tag ,const String<STRU32> &def) const {
		const auto r1x = Function<String<STRU32> (const String<STRU8> &)> (&_U8STOU32S_) ;
		return attribute (tag ,def ,r1x) ;
	}

	String<STRA> attribute (const String<STRU8> &tag ,const String<STRA> &def) const {
		const auto r1x = Function<String<STRA> (const String<STRU8> &)> (&_U8STOAS_) ;
		return attribute (tag ,def ,r1x) ;
	}

	String<STRW> attribute (const String<STRU8> &tag ,const String<STRW> &def) const {
		const auto r1x = Function<String<STRW> (const String<STRU8> &)> (&_U8STOWS_) ;
		return attribute (tag ,def ,r1x) ;
	}

	const Array<String<STRU8>> &command () const & {
		return mCommand ;
	}

	auto command () && ->void = delete ;

private:
	void initialize (const PhanBuffer<const STRU8> &data) ;
} ;

inline exports void CommandParser::initialize (const PhanBuffer<const STRU8> &data) {
	class Lambda final
		:private Proxy {
	private:
		CommandParser &mContext ;

		TextReader<STRU8> mTextReader ;
		RegularReader mRis ;
		String<STRU8> mLatestString ;

		Set<String<STRU8>> mOptionSet ;
		Deque<String<STRU8>> mAttributeList ;
		Set<String<STRU8>> mAttributeMappingSet ;
		SList<String<STRU8>> mCommandList ;
		Array<String<STRU8>> mCommand ;

	public:
		inline explicit Lambda (CommandParser &context_ ,const PhanBuffer<const STRU8> &data)
			: mContext (context_) ,mTextReader (data) {}

		inline void operator() () {
			prepare () ;
			generate () ;
			refresh () ;
		}

	private:
		inline void prepare () {
			mRis = RegularReader (PhanRef<TextReader<STRU8>>::make (mTextReader) ,2) ;
			mOptionSet = Set<String<STRU8>> () ;
			mAttributeList = Deque<String<STRU8>> () ;
			mAttributeMappingSet = Set<String<STRU8>> () ;
			mCommandList = SList<String<STRU8>> () ;
		}

		inline void generate () {
			/*
			*	$0->$8 $7 $9
			*	$1->${identity}
			*	$2->"${string}"
			*	$3->${newgap}
			*	$4->/$1
			*	$5->-$1|-$1=$2|-$1=$3
			*	$6->$2|$3
			*	$7->${eps}|$4 $7|$5 $7|$6 $7
			*	$8->${eps}
			*	$9->${end}
			*/
			update_shift_e0 () ;
			update_command () ;
		}

		//@info: $0->$8 $7 $9
		inline void update_shift_e0 () {
			update_shift_e8 () ;
			mRis >> RegularReader::SKIP_GAP_SPACE_ONLY ;
			update_shift_e7 () ;
			mRis >> RegularReader::SKIP_GAP_SPACE_ONLY ;
			update_shift_e9 () ;
		}

		//@info: $1->${identity}
		inline void update_shift_e1 () {
			mRis >> RegularReader::HINT_IDENTIFIER_TEXT >> mLatestString ;
		}

		//@info: $2->"${string}"
		inline void update_shift_e2 () {
			mRis >> RegularReader::HINT_STRING_TEXT >> mLatestString ;
		}

		//@info: $3->${newgap}
		inline void update_shift_e3 () {
			mRis >> RegularReader::HINT_NEWGAP_TEXT >> mLatestString ;
		}

		//@info: $4->/$1
		inline void update_shift_e4 () {
			mRis >> _PCSTRU8_ ("/") ;
			update_shift_e1 () ;
			mOptionSet.add (std::move (mLatestString)) ;
		}

		//@info: $5->-$1|-$1=$2|-$1=$3
		inline void update_shift_e5 () {
			mRis >> _PCSTRU8_ ("-") ;
			update_shift_e1 () ;
			INDEX ix = mAttributeMappingSet.map (mLatestString) ;
			_DYNAMIC_ASSERT_ (ix == VAR_NONE) ;
			ix = mAttributeList.insert () ;
			mAttributeMappingSet.add (std::move (mLatestString) ,ix) ;
			auto fax = TRUE ;
			if switch_case (fax) {
				if (!(mRis[0] == STRU8 ('=')))
					discard ;
				if (!(mRis[1] == STRU8 ('\"')))
					discard ;
				mRis >> _PCSTRU8_ ("=") ;
				update_shift_e2 () ;
				mAttributeList[ix] = std::move (mLatestString) ;
			}
			if switch_case (fax) {
				if (!(mRis[0] == STRU8 ('=')))
					discard ;
				mRis >> _PCSTRU8_ ("=") ;
				update_shift_e3 () ;
				mAttributeList[ix] = std::move (mLatestString) ;
			}
			if switch_case (fax) {
				mAttributeList[ix] = _PCSTRU8_ ("TRUE") ;
			}
		}

		//@info: $6->$2|$3
		inline void update_shift_e6 () {
			auto fax = TRUE ;
			if switch_case (fax) {
				if (!(mRis[0] == STRU8 ('\"')))
					discard ;
				update_shift_e2 () ;
			}
			if switch_case (fax) {
				update_shift_e3 () ;
			}
			mCommandList.add (std::move (mLatestString)) ;
		}

		//@info: $7->${eps}|$4 $7|$5 $7|$6 $7
		inline void update_shift_e7 () {
			while (TRUE) {
				if (mRis[0] == STRU8 ('\0'))
					break ;
				auto fax = TRUE ;
				if switch_case (fax) {
					if (!(mRis[0] == STRU8 ('/')))
						discard ;
					update_shift_e4 () ;
				}
				if switch_case (fax) {
					if (!(mRis[0] == STRU8 ('-')))
						discard ;
					update_shift_e5 () ;
				}
				if switch_case (fax) {
					update_shift_e6 () ;
				}
				mRis >> RegularReader::SKIP_GAP_SPACE_ONLY ;
			}
		}

		//@info: $8->${eps}
		inline void update_shift_e8 () {
			_STATIC_WARNING_ ("noop") ;
		}

		//@info: $9->${end}
		inline void update_shift_e9 () {
			_DYNAMIC_ASSERT_ (mRis[0] == STRU8 ('\0')) ;
		}

		inline void update_command () {
			mCommand = Array<String<STRU8>> (mCommandList.length ()) ;
			for (auto &&i : _RANGE_ (0 ,mCommandList.length ()))
				mCommand[i] = std::move (mCommandList[mCommandList.access (i)]) ;
		}

		inline void refresh () {
			mContext.mOptionSet = std::move (mOptionSet) ;
			mContext.mAttributeList = std::move (mAttributeList) ;
			mContext.mAttributeMappingSet = std::move (mAttributeMappingSet) ;
			mContext.mCommand = std::move (mCommand) ;
		}
	} ;
	_CALL_ (Lambda ((*this) ,data)) ;
}
} ;