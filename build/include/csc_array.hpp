﻿#pragma once

#ifndef __CSC_ARRAY__
#define __CSC_ARRAY__
#endif

#include "csc.hpp"

namespace CSC {
template <class BASE>
class ForwardIterator final {
private:
	using ITERATOR = DEF<decltype (_NULL_<const BASE> ().ibegin ())> ;
	using ITEM_TYPE = DEF<decltype (_NULL_<BASE> ().get (_NULL_<const ITERATOR> ()))> ;

private:
	BASE &mBase ;
	ITERATOR mIndex ;

public:
	inline ForwardIterator () = delete ;

	inline ForwardIterator (const ForwardIterator &) = delete ;
	inline ForwardIterator &operator= (const ForwardIterator &) = delete ;

	inline ForwardIterator (ForwardIterator &&) noexcept = default ;
	inline ForwardIterator &operator= (ForwardIterator &&) = delete ;

	inline BOOL operator!= (const ForwardIterator &right) const {
		if (mIndex == right.mIndex)
			return FALSE ;
		return TRUE ;
	}

	inline ITEM_TYPE operator* () const {
		return mBase.get (mIndex) ;
	}

	inline void operator++ () {
		mIndex = _XVALUE_<const BASE> (mBase).inext (mIndex) ;
	}

private:
	inline explicit ForwardIterator (BASE &base ,ITERATOR &&index) popping : mBase (base) ,mIndex (std::move (index)) {}

public:
	inline static ForwardIterator friend_begin (BASE &base) popping {
		return ForwardIterator (base ,_XVALUE_<const BASE> (base).ibegin ()) ;
	}

	inline static ForwardIterator friend_end (BASE &base) popping {
		return ForwardIterator (base ,_XVALUE_<const BASE> (base).iend ()) ;
	}
} ;

inline namespace S {
template <class _ARG1 ,class = ENABLE_TYPE<!std::is_reference<decltype (_NULL_<const _ARG1> ().ibegin ())>::value>>
inline ForwardIterator<REMOVE_REFERENCE_TYPE<_ARG1>> begin (_ARG1 &&arg1) popping {
	return ForwardIterator<REMOVE_REFERENCE_TYPE<_ARG1>>::friend_begin (arg1) ;
}

template <class _ARG1 ,class = ENABLE_TYPE<!std::is_reference<decltype (_NULL_<const _ARG1> ().iend ())>::value>>
inline ForwardIterator<REMOVE_REFERENCE_TYPE<_ARG1>> end (_ARG1 &&arg1) popping {
	return ForwardIterator<REMOVE_REFERENCE_TYPE<_ARG1>>::friend_end (arg1) ;
}
} ;

namespace U {
struct OPERATOR_SORT {
	template <class _ARG1 ,class _ARG2>
	inline static void compute_insert_sort (const _ARG1 &array ,_ARG2 &out ,INDEX seg_a ,INDEX seg_b) {
		for (INDEX i = seg_a + 1 ,ie = seg_b + 1 ; i < ie ; i++) {
			INDEX ix = i ;
			auto rax = std::move (out[ix]) ;
			while (TRUE) {
				if (ix - 1 < seg_a)
					break ;
				if (!(array[rax] < array[out[ix - 1]]))
					break ;
				out[ix] = std::move (out[ix - 1]) ;
				ix-- ;
			}
			out[ix] = std::move (rax) ;
		}
	}

	template <class _ARG1 ,class _ARG2>
	inline static void compute_quick_sort_partition (const _ARG1 &array ,_ARG2 &out ,INDEX seg_a ,INDEX seg_b ,INDEX &it) {
		INDEX ix = seg_a ;
		INDEX iy = seg_b ;
		auto rax = std::move (out[ix]) ;
		while (TRUE) {
			while (ix < iy && array[rax] < array[out[iy]])
				iy-- ;
			if (ix >= iy)
				break ;
			out[ix++] = std::move (out[iy]) ;
			while (ix < iy && array[out[ix]] < array[rax])
				ix++ ;
			if (ix >= iy)
				break ;
			out[iy--] = std::move (out[ix]) ;
		}
		out[ix] = std::move (rax) ;
		it = ix ;
	}

	template <class _ARG1 ,class _ARG2>
	inline static void compute_quick_sort (const _ARG1 &array ,_ARG2 &out ,INDEX seg_a ,INDEX seg_b ,LENGTH ideal) {
		INDEX ix = seg_a ;
		while (TRUE) {
			if (ix >= seg_b)
				break ;
			if (ideal <= 0)
				break ;
			ideal = ideal / 2 + ideal / 4 ;
			INDEX jx = VAR_NONE ;
			compute_quick_sort_partition (array ,out ,ix ,seg_b ,jx) ;
			compute_quick_sort (array ,out ,ix ,(jx - 1) ,ideal) ;
			ix = jx + 1 ;
		}
		if (ix >= seg_b)
			return ;
		compute_insert_sort (array ,out ,ix ,seg_b) ;
	}

	template <class _ARG1 ,class _ARG2>
	inline static void invoke (const _ARG1 &array ,_ARG2 &out ,INDEX seg ,LENGTH seg_len) {
		compute_quick_sort (array ,out ,seg ,(seg + seg_len - 1) ,seg_len) ;
	}

	class ForwardArray :private Wrapped<ARGV<NONE>> {
	public:
		template <class _ARG1>
		inline _ARG1 &operator[] (_ARG1 &arg1) const {
			return arg1 ;
		}
	} ;

	template <class _ARG1>
	inline static void invoke (_ARG1 &out ,INDEX seg ,LENGTH seg_len) {
		invoke (_CAST_<ForwardArray> (ARGV_NONE) ,out ,seg ,seg_len) ;
	}
} ;
} ;

namespace U {
struct OPERATOR_HASH {
	template <class _ARG1>
	inline static FLAG template_hash (const _ARG1 &left ,const ARGV<ENABLE_TYPE<std::is_same<DEF<decltype (_NULL_<const _ARG1> ().hash ())> ,FLAG>::value>> & ,const DEF<decltype (ARGVP2)> &) {
		return left.hash () ;
	}

	template <class _ARG1>
	inline static FLAG template_hash (const _ARG1 &left ,const ARGV<ENABLE_TYPE<std::is_pod<_ARG1>::value>> & ,const DEF<decltype (ARGVP1)> &) {
		return _MEMHASH_ (_CAST_<BYTE[_SIZEOF_ (_ARG1)]> (left)) ;
	}

	template <class _ARG1>
	inline static FLAG invoke (const _ARG1 &left) {
		FLAG ret = template_hash (left ,ARGV_VOID ,ARGVP9) ;
		ret &= VAR_MAX ;
		return std::move (ret) ;
	}
} ;
} ;

template <class ITEM ,class SIZE = SAUTO>
class Array ;

template <class ITEM ,class SIZE>
class Array {
private:
	Buffer<ITEM ,SIZE> mArray ;

public:
	Array () = default ;

	explicit Array (LENGTH len) :mArray (len) {}

	implicit Array (const std::initializer_list<ITEM> &right) : Array (right.size ()) {
		_DEBUG_ASSERT_ (size () == LENGTH (right.size ())) ;
		INDEX iw = 0 ;
		for (auto &&i : right)
			mArray[iw++] = i ;
		_DEBUG_ASSERT_ (iw == mArray.size ()) ;
	}

	LENGTH size () const {
		return mArray.size () ;
	}

	LENGTH length () const {
		return size () ;
	}

	PhanBuffer<ITEM> raw () & {
		_DYNAMIC_ASSERT_ (mArray.size () > 0) ;
		return PhanBuffer<ITEM>::make (mArray ,size ()) ;
	}

	PhanBuffer<const ITEM> raw () const & {
		_DYNAMIC_ASSERT_ (mArray.size () > 0) ;
		return PhanBuffer<const ITEM>::make (mArray ,length ()) ;
	}

	PhanBuffer<ITEM> raw () && = delete ;

	ITEM &get (INDEX index) & {
		return mArray[index] ;
	}

	inline ITEM &operator[] (INDEX index) & {
		return get (index) ;
	}

	const ITEM &get (INDEX index) const & {
		return mArray[index] ;
	}

	inline const ITEM &operator[] (INDEX index) const & {
		return get (index) ;
	}

	ITEM &get (INDEX) && = delete ;

	inline ITEM &operator[] (INDEX) && = delete ;

	INDEX at (const ITEM &item) const {
		return mArray.at (item) ;
	}

	INDEX ibegin () const {
		return 0 ;
	}

	INDEX iend () const {
		return length () ;
	}

	INDEX inext (INDEX index) const {
		return index + 1 ;
	}

	BOOL equal (const Array &right) const {
		if (mArray != right.mArray)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const Array &right) const {
		return equal (right) ;
	}

	inline BOOL operator!= (const Array &right) const {
		return !equal (right) ;
	}

	BOOL less (const Array &right) const {
		if (mArray >= right.mArray)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator< (const Array &right) const {
		return less (right) ;
	}

	inline BOOL operator>= (const Array &right) const {
		return !less (right) ;
	}

	inline BOOL operator> (const Array &right) const {
		return right.less (*this) ;
	}

	inline BOOL operator<= (const Array &right) const {
		return !right.less (*this) ;
	}

	INDEX find (const ITEM &item) const {
		for (INDEX i = ibegin () ,ie = iend () ; i != ie ; i = inext (i))
			if (get (i) == item)
				return i ;
		return VAR_NONE ;
	}

	void sort () {
		U::OPERATOR_SORT::invoke (mArray ,0 ,mArray.size ()) ;
	}

	void fill (const ITEM &val) {
		for (INDEX i = 0 ; i < mArray.size () ; i++)
			mArray[i] = val ;
	}
} ;

template <class TYPE>
using ARRAY1 = Array<TYPE ,ARGC<1>> ;
template <class TYPE>
using ARRAY2 = Array<TYPE ,ARGC<2>> ;
template <class TYPE>
using ARRAY3 = Array<TYPE ,ARGC<3>> ;
template <class TYPE>
using ARRAY4 = Array<TYPE ,ARGC<4>> ;
template <class TYPE>
using ARRAY5 = Array<TYPE ,ARGC<5>> ;
template <class TYPE>
using ARRAY6 = Array<TYPE ,ARGC<6>> ;
template <class TYPE>
using ARRAY7 = Array<TYPE ,ARGC<7>> ;
template <class TYPE>
using ARRAY8 = Array<TYPE ,ARGC<8>> ;
template <class TYPE>
using ARRAY9 = Array<TYPE ,ARGC<9>> ;
template <class TYPE>
using ARRAY10 = Array<TYPE ,ARGC<10>> ;
template <class TYPE>
using ARRAY11 = Array<TYPE ,ARGC<11>> ;
template <class TYPE>
using ARRAY12 = Array<TYPE ,ARGC<12>> ;
template <class TYPE>
using ARRAY13 = Array<TYPE ,ARGC<13>> ;
template <class TYPE>
using ARRAY14 = Array<TYPE ,ARGC<14>> ;
template <class TYPE>
using ARRAY15 = Array<TYPE ,ARGC<15>> ;
template <class TYPE>
using ARRAY16 = Array<TYPE ,ARGC<16>> ;

template <class ITEM ,class SIZE = SAUTO>
class String ;

template <class ITEM ,class SIZE>
class String {
private:
	inline static constexpr LENGTH expr_size (LENGTH len) {
		return (len <= 0) ? len : (len + 1) ;
	}

private:
	Buffer<ITEM ,ARGC<expr_size (SIZE::value)>> mString ;

public:
	String () {
		clear () ;
	}

	explicit String (LENGTH len) :String (ARGVP0 ,expr_size (len)) {
		clear () ;
	}

	implicit String (const std::initializer_list<ITEM> &right) : String (right.size ()) {
		_DEBUG_ASSERT_ (size () == LENGTH (right.size ())) ;
		INDEX iw = 0 ;
		for (auto &&i : right)
			mString[iw++] = i ;
		mString[iw++] = ITEM (0) ;
		_DEBUG_ASSERT_ (iw == mString.size ()) ;
	}

	implicit String (const ARR<ITEM> &right) :String (raw_string_length (right)) {
		_MEMCOPY_ (mString.self ,right ,size ()) ;
	}

	template <LENGTH _VAL1>
	implicit String (const DEF<ITEM[_VAL1]> &right) : String (_VAL1 - 1) {
		_STATIC_ASSERT_ (stl::is_literals<ITEM>::value) ;
		_MEMCOPY_ (mString.self ,PTRTOARR[right] ,size ()) ;
	}

	LENGTH size () const {
		if (mString.size () == 0)
			return 0 ;
		return mString.size () - 1 ;
	}

	LENGTH length () const {
		if (mString.size () == 0)
			return 0 ;
		return _MEMCHR_ (mString.self ,mString.size () ,ITEM (0)) ;
	}

	PhanBuffer<ITEM> raw () & {
		_DYNAMIC_ASSERT_ (mString.size () > 0) ;
		return PhanBuffer<ITEM>::make (mString ,size ()) ;
	}

	PhanBuffer<const ITEM> raw () const & {
		_DYNAMIC_ASSERT_ (mString.size () > 0) ;
		return PhanBuffer<const ITEM>::make (mString ,length ()) ;
	}

	PhanBuffer<ITEM> raw () && = delete ;

	void clear () {
		if (mString.size () == 0)
			return ;
		_MEMFILL_ (mString.self ,mString.size () ,ITEM (0)) ;
	}

	ITEM &get (INDEX index) & {
		_DEBUG_ASSERT_ (index >= 0 && index < size ()) ;
		return mString[index] ;
	}

	inline ITEM &operator[] (INDEX index) & {
		return get (index) ;
	}

	const ITEM &get (INDEX index) const & {
		_DEBUG_ASSERT_ (index >= 0 && index < size ()) ;
		return mString[index] ;
	}

	inline const ITEM &operator[] (INDEX index) const & {
		return get (index) ;
	}

	ITEM &get (INDEX) && = delete ;

	inline ITEM &operator[] (INDEX) && = delete ;

	INDEX at (const ITEM &item) const {
		INDEX ret = mString.at (item) ;
		if (!(ret >= 0 && ret < size ()))
			ret = VAR_NONE ;
		return std::move (ret) ;
	}

	INDEX ibegin () const {
		return 0 ;
	}

	INDEX iend () const {
		return length () ;
	}

	INDEX inext (INDEX index) const {
		return index + 1 ;
	}

	template <LENGTH _VAL1>
	BOOL equal (const DEF<ITEM[_VAL1]> &right) const {
		_STATIC_ASSERT_ (stl::is_literals<ITEM>::value) ;
		if (mString.size () < _VAL1)
			return FALSE ;
		if (!_MEMEQUAL_ (mString.self ,right))
			return FALSE ;
		return TRUE ;
	}

	template <LENGTH _VAL1>
	inline BOOL operator== (const DEF<ITEM[_VAL1]> &right) const {
		return equal (right) ;
	}

	template <LENGTH _VAL1>
	inline BOOL operator!= (const DEF<ITEM[_VAL1]> &right) const {
		return !equal (right) ;
	}

	BOOL equal (const String &right) const {
		if (size () == 0 && right.size () == 0)
			return TRUE ;
		if (size () == 0 || right.size () == 0)
			return FALSE ;
		INDEX ix = 0 ;
		while (mString[ix] != ITEM (0) && mString[ix] == right.mString[ix])
			ix++ ;
		if (mString[ix] != right.mString[ix])
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const String &right) const {
		return equal (right) ;
	}

	inline BOOL operator!= (const String &right) const {
		return !equal (right) ;
	}

	BOOL less (const String &right) const {
		if (size () == 0 && right.size () == 0)
			return FALSE ;
		if (size () == 0)
			return TRUE ;
		if (right.size () == 0)
			return FALSE ;
		INDEX ix = 0 ;
		while (mString[ix] != ITEM (0) && mString[ix] == right.mString[ix])
			ix++ ;
		if (!(mString[ix] < right.mString[ix]))
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator< (const String &right) const {
		return less (right) ;
	}

	inline BOOL operator>= (const String &right) const {
		return !less (right) ;
	}

	inline BOOL operator> (const String &right) const {
		return right.less (*this) ;
	}

	inline BOOL operator<= (const String &right) const {
		return !right.less (*this) ;
	}

	BOOL empty () const {
		if (mString.size () == 0)
			return TRUE ;
		if (mString[0] != ITEM (0))
			return FALSE ;
		return TRUE ;
	}

	String app (const String &right) const {
		const auto r1x = length () ;
		const auto r2x = right.length () ;
		String ret = String (r1x + r2x) ;
		_MEMCOPY_ (ret.mString.self ,mString.self ,r1x) ;
		_MEMCOPY_ (PTRTOARR[&ret.mString.self[r1x]] ,right.mString.self ,r2x) ;
		return std::move (ret) ;
	}

	inline String operator+ (const String &right) const {
		return app (right) ;
	}

	inline String operator- (const String &right) const {
		return right.app (*this) ;
	}

	inline String &operator+= (const String &right) {
		*this = app (right) ;
		return *this ;
	}

	inline String &operator-= (const String &right) {
		*this = right.app (*this) ;
		return *this ;
	}

	template <LENGTH _VAL1>
	void appto (const DEF<ITEM[_VAL1]> &right) {
		_STATIC_ASSERT_ (stl::is_literals<ITEM>::value) ;
		_CALL_ONE_ ([&] (BOOL &if_context) {
			if (mString.size () == 0)
				discard ;
			const auto r1x = length () ;
			const auto r2x = _VAL1 - 1 ;
			if (r1x + r2x > size ())
				discard ;
			_MEMCOPY_ (PTRTOARR[&mString.self[r1x]] ,PTRTOARR[right] ,r2x) ;
			mString[r1x + r2x] = ITEM (0) ;
		} ,[&] (BOOL &if_context) {
			*this = app (right) ;
		}) ;
	}

	template <LENGTH _VAL1>
	inline String &operator+= (const DEF<ITEM[_VAL1]> &right) {
		appto (right) ;
		return *this ;
	}

	String segment (INDEX seg ,LENGTH seg_len) const {
		_DEBUG_ASSERT_ (seg >= 0 && seg + seg_len <= size ()) ;
		String ret = String (seg_len) ;
		for (INDEX i = 0 ; i < ret.size () ; i++)
			ret.get (i) = get (seg + i) ;
		return std::move (ret) ;
	}

private:
	explicit String (const DEF<decltype (ARGVP0)> & ,LENGTH len) :mString (len) {}

private:
	inline static LENGTH raw_string_length (const ARR<ITEM> &src) {
		LENGTH ret = _MEMCHR_ (src ,DEFAULT_HUGEBUFFER_SIZE::value ,ITEM (0)) ;
		_DYNAMIC_ASSERT_ (ret >= 0 && ret < DEFAULT_HUGEBUFFER_SIZE::value) ;
		return std::move (ret) ;
	}

public:
	//@info: the function is incompleted without 'csc_string.hpp'
	template <class... _ARGS>
	inline static String make (const _ARGS &...args) ;
} ;

template <class ITEM ,class SIZE = SAUTO>
class Stack ;

template <class ITEM ,class SIZE>
class Stack {
private:
	class AccessArray :private Wrapped<Stack> {
	public:
		inline ITEM &operator[] (INDEX index) {
			return AccessArray::mSelf[AccessArray::mSelf.access (index)] ;
		}

		inline const ITEM &operator[] (INDEX index) const {
			return AccessArray::mSelf[AccessArray::mSelf.access (index)] ;
		}
	} ;

	inline static constexpr LENGTH expr_size (LENGTH len) {
		return (len <= 0) ? len : (len + 1) ;
	}

private:
	Buffer<ITEM ,ARGC<expr_size (SIZE::value)>> mStack ;
	INDEX mRead ;
	INDEX mWrite ;

public:
	Stack () {
		clear () ;
	}

	explicit Stack (LENGTH len) :Stack (ARGVP0 ,expr_size (len)) {
		clear () ;
	}

	implicit Stack (const std::initializer_list<ITEM> &right) : Stack (right.size ()) {
		for (auto &&i : right)
			add (i) ;
	}

	LENGTH size () const {
		if (mStack.size () == 0)
			return 0 ;
		return mStack.size () - 1 ;
	}

	LENGTH length () const {
		if (mStack.size () == 0)
			return 0 ;
		return mWrite ;
	}

	void clear () {
		mRead = 0 ;
		mWrite = 0 ;
	}

	ITEM &get (INDEX index) & {
		_DEBUG_ASSERT_ (index >= 0 && index < mWrite) ;
		return mStack[index] ;
	}

	inline ITEM &operator[] (INDEX index) & {
		return get (index) ;
	}

	const ITEM &get (INDEX index) const & {
		_DEBUG_ASSERT_ (index >= 0 && index < mWrite) ;
		return mStack[index] ;
	}

	inline const ITEM &operator[] (INDEX index) const & {
		return get (index) ;
	}

	ITEM &get (INDEX) && = delete ;

	inline ITEM &operator[] (INDEX) && = delete ;

	INDEX at (const ITEM &item) const {
		INDEX ret = mStack.at (item) ;
		if (!(ret >= 0 && ret < mWrite))
			ret = VAR_NONE ;
		return std::move (ret) ;
	}

	INDEX access (INDEX pos) const {
		_DEBUG_ASSERT_ (pos >= 0 && pos < length ()) ;
		return pos ;
	}

	INDEX ibegin () const {
		if (mStack.size () == 0)
			return VAR_NONE ;
		return mWrite - 1 ;
	}

	INDEX iend () const {
		return VAR_NONE ;
	}

	INDEX inext (INDEX index) const {
		return index - 1 ;
	}

	BOOL equal (const Stack &right) const {
		if (length () != right.length ())
			return FALSE ;
		if (!_MEMEQUAL_ (mStack ,right.mStack ,length ()))
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const Stack &right) const {
		return equal (right) ;
	}

	inline BOOL operator!= (const Stack &right) const {
		return !equal (right) ;
	}

	BOOL empty () const {
		if (mWrite > 0)
			return FALSE ;
		return TRUE ;
	}

	BOOL full () const {
		if (mWrite < mStack.size ())
			return FALSE ;
		return TRUE ;
	}

	void add (const ITEM &item) {
		reserve (1) ;
		mStack[mWrite] = std::move (item) ;
		update_resize () ;
	}

	inline Stack &operator<< (const ITEM &item) {
		add (std::move (item)) ;
		return *this ;
	}

	void add (ITEM &&item) {
		reserve (1) ;
		mStack[mWrite] = std::move (item) ;
		update_resize () ;
	}

	inline Stack &operator<< (ITEM &&item) {
		add (std::move (item)) ;
		return *this ;
	}

	template <class _ARG1>
	void appand (const _ARG1 &src) {
		reserve (src.length ()) ;
		for (auto &&i : src)
			add (std::move (i)) ;
	}

	template <class _ARG1>
	void appand (_ARG1 &&src) {
		reserve (src.length ()) ;
		for (auto &&i : src)
			add (std::move (i)) ;
	}

	void take () {
		_DEBUG_ASSERT_ (!empty ()) ;
		mWrite-- ;
	}

	void take (ITEM &item) popping {
		_DEBUG_ASSERT_ (!empty ()) ;
		item = std::move (mStack[mWrite - 1]) ;
		mWrite-- ;
	}

	inline Stack &operator>> (ITEM &item) popping {
		take (item) ;
		return *this ;
	}

	INDEX peek () const {
		_DEBUG_ASSERT_ (!empty ()) ;
		return mWrite - 1 ;
	}

	INDEX insert () popping {
		reserve (1) ;
		INDEX ret = mWrite ;
		update_resize () ;
		return std::move (ret) ;
	}

	INDEX insert_sort (const ITEM &item) popping {
		reserve (1) ;
		INDEX ret = mWrite ;
		while (TRUE) {
			if (ret - 1 < 0)
				break ;
			if (!(mStack[ret - 1] < item))
				break ;
			mStack[ret] = std::move (mStack[ret - 1]) ;
			ret-- ;
		}
		mStack[ret] = std::move (item) ;
		update_resize () ;
		return std::move (ret) ;
	}

	INDEX insert_sort (ITEM &&item) popping {
		reserve (1) ;
		INDEX ret = mWrite ;
		while (TRUE) {
			if (ret - 1 < 0)
				break ;
			if (mStack[ret - 1] >= item)
				break ;
			mStack[ret] = std::move (mStack[ret - 1]) ;
			ret-- ;
		}
		mStack[ret] = std::move (item) ;
		update_resize () ;
		return std::move (ret) ;
	}

	void pop () {
		_DEBUG_ASSERT_ (!empty ()) ;
		mWrite-- ;
	}

	Array<INDEX> esort () const {
		Array<INDEX> ret = Array<INDEX> (length ()) ;
		INDEX iw = 0 ;
		for (INDEX i = ibegin () ,ie = iend () ; i != ie ; i = inext (i))
			ret[iw++] = i ;
		_DEBUG_ASSERT_ (iw == ret.length ()) ;
		U::OPERATOR_SORT::invoke (*this ,ret ,0 ,ret.length ()) ;
		return std::move (ret) ;
	}

	void sort () {
		U::OPERATOR_SORT::invoke (_CAST_<AccessArray> (*this) ,0 ,length ()) ;
	}

	void reverse () {
		_MEMRCOPY_ (mStack.self ,mStack.self ,mWrite) ;
	}

private:
	explicit Stack (const DEF<decltype (ARGVP0)> & ,LENGTH len) :mStack (len) {}

private:
	void reserve (LENGTH len) {
		const auto r1x = _MAX_ (len - (mStack.size () - length ()) ,VAR_ZERO) ;
		if (r1x == 0)
			return ;
		auto rax = mStack.expand (mStack.size () + r1x) ;
		_MEMMOVE_ (rax.self ,mStack.self ,mStack.size ()) ;
		mStack.swap (rax) ;
	}

	void update_resize () {
		_DEBUG_ASSERT_ (mWrite >= 0 && mWrite < mStack.size ()) ;
		mWrite++ ;
		if (mWrite < mStack.size ())
			return ;
		auto rax = mStack.expand () ;
		_MEMMOVE_ (rax.self ,mStack.self ,mStack.size ()) ;
		mStack.swap (rax) ;
	}
} ;

template <class ITEM ,class SIZE = SAUTO>
class Queue ;

template <class ITEM ,class SIZE>
class Queue {
private:
	class AccessArray :private Wrapped<Queue> {
	public:
		inline ITEM &operator[] (INDEX index) {
			return AccessArray::mSelf[AccessArray::mSelf.access (index)] ;
		}

		inline const ITEM &operator[] (INDEX index) const {
			return AccessArray::mSelf[AccessArray::mSelf.access (index)] ;
		}
	} ;

	inline static constexpr LENGTH expr_size (LENGTH len) {
		return (len <= 0) ? len : (len + 1) ;
	}

private:
	Buffer<ITEM ,ARGC<expr_size (SIZE::value)>> mQueue ;
	INDEX mRead ;
	INDEX mWrite ;

public:
	Queue () {
		clear () ;
	}

	explicit Queue (LENGTH len) :Queue (ARGVP0 ,expr_size (len)) {
		clear () ;
	}

	implicit Queue (const std::initializer_list<ITEM> &right) : Queue (right.size ()) {
		for (auto &&i : right)
			add (i) ;
	}

	LENGTH size () const {
		if (mQueue.size () == 0)
			return 0 ;
		return mQueue.size () - 1 ;
	}

	LENGTH length () const {
		if (mQueue.size () == 0)
			return 0 ;
		return (mWrite - mRead + mQueue.size ()) % mQueue.size () ;
	}

	void clear () {
		mRead = 0 ;
		mWrite = 0 ;
	}

	//@warn: index would be no longer valid once resized
	ITEM &get (INDEX index) & {
		_DEBUG_ASSERT_ (ensure_index (index)) ;
		return mQueue[index] ;
	}

	inline ITEM &operator[] (INDEX index) & {
		return get (index) ;
	}

	//@warn: index would be no longer valid once resized
	const ITEM &get (INDEX index) const & {
		_DEBUG_ASSERT_ (ensure_index (index)) ;
		return mQueue[index] ;
	}

	inline const ITEM &operator[] (INDEX index) const & {
		return get (index) ;
	}

	ITEM &get (INDEX) && = delete ;

	inline ITEM &operator[] (INDEX) && = delete ;

	INDEX at (const ITEM &item) const {
		INDEX ret = mQueue.at (item) ;
		if (!ensure_index (ret))
			ret = VAR_NONE ;
		return std::move (ret) ;
	}

	INDEX access (INDEX pos) const {
		_DEBUG_ASSERT_ (pos >= 0 && pos < length ()) ;
		return (mRead + pos) % mQueue.size () ;
	}

	INDEX ibegin () const {
		if (mQueue.size () == 0)
			return VAR_NONE ;
		return mRead ;
	}

	INDEX iend () const {
		if (mQueue.size () == 0)
			return VAR_NONE ;
		return mWrite ;
	}

	INDEX inext (INDEX index) const {
		return (index + 1) % mQueue.size () ;
	}

	BOOL equal (const Queue &right) const {
		if (length () != right.length ())
			return FALSE ;
		INDEX ir = ibegin () ;
		INDEX ie = iend () ;
		INDEX jr = right.ibegin () ;
		INDEX je = right.iend () ;
		while (TRUE) {
			if (ir == ie)
				break ;
			if (jr == je)
				break ;
			if (get (ir) != right.get (jr))
				break ;
			ir = inext (ir) ;
			jr = right.inext (jr) ;
		}
		if (ir != ie)
			return FALSE ;
		if (jr != je)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const Queue &right) const {
		return equal (right) ;
	}

	inline BOOL operator!= (const Queue &right) const {
		return !equal (right) ;
	}

	BOOL empty () const {
		if (mRead != mWrite)
			return FALSE ;
		return TRUE ;
	}

	BOOL full () const {
		if (mQueue.size () == 0)
			return TRUE ;
		if (mRead != (mWrite + 1) % mQueue.size ())
			return FALSE ;
		return TRUE ;
	}

	void add (const ITEM &item) {
		reserve (1) ;
		mQueue[mWrite] = std::move (item) ;
		update_resize () ;
	}

	inline Queue &operator<< (const ITEM &item) {
		add (std::move (item)) ;
		return *this ;
	}

	void add (ITEM &&item) {
		reserve (1) ;
		mQueue[mWrite] = std::move (item) ;
		update_resize () ;
	}

	inline Queue &operator<< (ITEM &&item) {
		add (std::move (item)) ;
		return *this ;
	}

	template <class _ARG1>
	void appand (const _ARG1 &src) {
		reserve (src.length ()) ;
		for (auto &&i : src)
			add (std::move (i)) ;
	}

	template <class _ARG1>
	void appand (_ARG1 &&src) {
		reserve (src.length ()) ;
		for (auto &&i : src)
			add (std::move (i)) ;
	}

	void take () {
		_DEBUG_ASSERT_ (!empty ()) ;
		mRead = (mRead + 1) % mQueue.size () ;
	}

	void take (ITEM &item) popping {
		_DEBUG_ASSERT_ (!empty ()) ;
		item = std::move (mQueue[mRead]) ;
		mRead = (mRead + 1) % mQueue.size () ;
	}

	inline Queue &operator>> (ITEM &item) popping {
		take (item) ;
		return *this ;
	}

	INDEX peek () const {
		_DEBUG_ASSERT_ (!empty ()) ;
		return mRead ;
	}

	INDEX insert () popping {
		reserve (1) ;
		INDEX ret = mWrite ;
		update_resize () ;
		return std::move (ret) ;
	}

	void pop () {
		_DEBUG_ASSERT_ (!empty ()) ;
		mWrite = (mWrite - 1 + mQueue.size ()) % mQueue.size () ;
	}

	Array<INDEX> esort () const {
		Array<INDEX> ret = Array<INDEX> (length ()) ;
		INDEX iw = 0 ;
		for (INDEX i = ibegin () ,ie = iend () ; i != ie ; i = inext (i))
			ret[iw++] = i ;
		_DEBUG_ASSERT_ (iw == ret.length ()) ;
		U::OPERATOR_SORT::invoke (*this ,ret ,0 ,ret.length ()) ;
		return std::move (ret) ;
	}

	void sort () {
		U::OPERATOR_SORT::invoke (_CAST_<AccessArray> (*this) ,0 ,length ()) ;
	}

private:
	explicit Queue (const DEF<decltype (ARGVP0)> & ,LENGTH len) :mQueue (len) {}

private:
	BOOL ensure_index (INDEX index) const {
		const auto r1x = BOOL (index >= mRead && index < mWrite) ;
		if (mRead <= mWrite && !r1x)
			return FALSE ;
		const auto r2x = BOOL (index >= 0 && index < mWrite) ;
		const auto r3x = BOOL (index >= mRead && index < mQueue.size ()) ;
		if (mRead > mWrite && !r2x && !r3x)
			return FALSE ;
		return TRUE ;
	}

	void reserve (LENGTH len) {
		const auto r1x = _MAX_ (len - (mQueue.size () - length ()) ,VAR_ZERO) ;
		if (r1x == 0)
			return ;
		_CALL_ONE_ ([&] (BOOL &if_context) {
			if (mRead > mWrite)
				discard ;
			auto rax = mQueue.expand (mQueue.size () + r1x) ;
			_MEMMOVE_ (PTRTOARR[&rax.self[mRead]] ,PTRTOARR[&mQueue.self[mRead]] ,(mWrite - mRead)) ;
			mQueue.swap (rax) ;
		} ,[&] (BOOL &if_context) {
			auto rax = mQueue.expand (mQueue.size () + r1x) ;
			_MEMMOVE_ (rax.self ,mQueue.self ,mWrite) ;
			INDEX ix = mRead + rax.size () - mQueue.size () ;
			_MEMMOVE_ (PTRTOARR[&rax.self[ix]] ,PTRTOARR[&mQueue.self[mRead]] ,(mQueue.size () - mRead)) ;
			mQueue.swap (rax) ;
			mRead = ix ;
		}) ;
	}

	void update_resize () {
		_DEBUG_ASSERT_ (mWrite >= 0 && mWrite < mQueue.size ()) ;
		mWrite = (mWrite + 1) % mQueue.size () ;
		if (mRead != mWrite)
			return ;
		auto rax = mQueue.expand () ;
		_MEMMOVE_ (rax.self ,mQueue.self ,mWrite) ;
		INDEX ix = 0 ;
		INDEX iy = mQueue.size () ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (mRead == 0)
				continue ;
			ix = mRead + rax.size () - mQueue.size () ;
			iy = mWrite ;
		}
		_MEMMOVE_ (PTRTOARR[&rax.self[ix]] ,PTRTOARR[&mQueue.self[mRead]] ,(mQueue.size () - mRead)) ;
		mQueue.swap (rax) ;
		mRead = ix ;
		mWrite = iy ;
	}
} ;

template <class KEY ,class ITEM = void ,class SIZE = SAUTO>
class Priority ;

template <class KEY ,class ITEM ,class SIZE>
class Priority<KEY ,SPECIALIZATION<ITEM> ,SIZE> {
private:
	using SPECIALIZATION_TYPE = Priority<KEY ,ITEM ,SIZE> ;

	class Node {
	private:
		friend Priority ;
		friend SPECIALIZATION_TYPE ;
		KEY mKey ;
		ITEM mItem ;

	public:
		inline Node () = default ;
	} ;

	using ITEM_TYPE = PACK<KEY ,ITEM> ;

	template <class BASE>
	class Pair {
	public:
		friend Priority ;
		friend SPECIALIZATION_TYPE ;
		const KEY &key ;
		CAST_TRAITS_TYPE<ITEM ,BASE> &item ;

	public:
		inline Pair () = delete ;

		inline Pair (const Pair &) = delete ;

		//@info: be careful about key's lifetime
		inline Pair (Pair &&) noexcept = default ;

		inline implicit operator const KEY & () && {
			return key ;
		}

	private:
		inline explicit Pair (BASE &base ,INDEX index) popping : key (base.mPriority[index].mKey) ,item (base.mPriority[index].mItem) {}
	} ;

	using Pair_BASE = Pair<SPECIALIZATION_TYPE> ;
	using Pair_const_BASE = Pair<const SPECIALIZATION_TYPE> ;

	inline static constexpr LENGTH expr_size (LENGTH len) {
		return (len <= 0) ? len : (len + 1) ;
	}

private:
	friend SPECIALIZATION_TYPE ;
	Buffer<Node ,ARGC<expr_size (SIZE::value)>> mPriority ;
	INDEX mWrite ;
	INDEX mTop ;

public:
	Priority () {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->clear () ;
	}

	explicit Priority (LENGTH len) :Priority (ARGVP0 ,expr_size (len)) {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->clear () ;
	}

	void add (const KEY &key ,const ITEM &item) {
		add (std::move (key) ,_COPY_ (item)) ;
	}

	void add (const KEY &key ,ITEM &&item) {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->reserve (1) ;
		INDEX ix = mWrite ;
		mPriority[ix].mKey = std::move (key) ;
		mPriority[ix].mItem = std::move (item) ;
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_resize () ;
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_insert (ix) ;
	}

	void add (const ITEM_TYPE &item) {
		add (item.key ,std::move (item)) ;
	}

	void add (KEY &&key ,const ITEM &item) {
		add (std::move (key) ,_COPY_ (item)) ;
	}

	void add (KEY &&key ,ITEM &&item) {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->reserve (1) ;
		INDEX ix = mWrite ;
		mPriority[ix].mKey = std::move (key) ;
		mPriority[ix].mItem = std::move (item) ;
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_resize () ;
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_insert (ix) ;
	}

	void add (ITEM_TYPE &&item) {
		add (std::move (item.P1) ,std::move (item.P2)) ;
	}

	template <class _ARG1>
	void appand (const _ARG1 &src) {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->reserve (src.length ()) ;
		for (auto &&i : src)
			add (i.key ,std::move (i.item)) ;
	}

	template <class _ARG1>
	void appand (_ARG1 &&src) {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->reserve (src.length ()) ;
		for (auto &&i : src)
			add (i.key ,std::move (i.item)) ;
	}

private:
	explicit Priority (const DEF<decltype (ARGVP0)> & ,LENGTH len) :mPriority (len) {}
} ;

template <class KEY ,class SIZE>
class Priority<KEY ,SPECIALIZATION<void> ,SIZE> {
private:
	using SPECIALIZATION_TYPE = Priority<KEY ,void ,SIZE> ;

	class Node {
	private:
		friend Priority ;
		friend SPECIALIZATION_TYPE ;
		KEY mKey ;

	public:
		inline Node () = default ;
	} ;

	using ITEM_TYPE = PACK<KEY> ;

	template <class BASE>
	class Pair {
	public:
		friend Priority ;
		friend SPECIALIZATION_TYPE ;
		const KEY &key ;

	public:
		inline Pair () = delete ;

		inline Pair (const Pair &) = delete ;

		//@info: be careful about key's lifetime
		inline Pair (Pair &&) noexcept = default ;

		inline implicit operator const KEY & () && {
			return key ;
		}

	private:
		inline explicit Pair (BASE &base ,INDEX index) popping : key (base.mPriority[index].mKey) {}
	} ;

	using Pair_BASE = Pair<SPECIALIZATION_TYPE> ;
	using Pair_const_BASE = Pair<const SPECIALIZATION_TYPE> ;

	inline static constexpr LENGTH expr_size (LENGTH len) {
		return (len <= 0) ? len : (len + 1) ;
	}

private:
	friend SPECIALIZATION_TYPE ;
	Buffer<Node ,ARGC<expr_size (SIZE::value)>> mPriority ;
	INDEX mWrite ;
	INDEX mTop ;

public:
	Priority () {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->clear () ;
	}

	explicit Priority (LENGTH len) :Priority (ARGVP0 ,expr_size (len)) {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->clear () ;
	}

	void add (const KEY &key) {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->reserve (1) ;
		INDEX ix = mWrite ;
		mPriority[ix].mKey = std::move (key) ;
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_resize () ;
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_insert (ix) ;
	}

	void add (const ITEM_TYPE &item) {
		add (std::move (item.P1)) ;
	}

	void add (KEY &&key) {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->reserve (1) ;
		INDEX ix = mWrite ;
		mPriority[ix].mKey = std::move (key) ;
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_resize () ;
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_insert (ix) ;
	}

	void add (ITEM_TYPE &&item) {
		add (std::move (item.P1)) ;
	}

	template <class _ARG1>
	void appand (const _ARG1 &src) {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->reserve (src.length ()) ;
		for (auto &&i : src)
			add (i.key) ;
	}

	template <class _ARG1>
	void appand (_ARG1 &&src) {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->reserve (src.length ()) ;
		for (auto &&i : src)
			add (i.key) ;
	}

private:
	explicit Priority (const DEF<decltype (ARGVP0)> & ,LENGTH len) :mPriority (len) {}
} ;

template <class KEY ,class ITEM ,class SIZE>
class Priority :private Priority<KEY ,SPECIALIZATION<ITEM> ,SIZE> {
private:
	using SPECIALIZATION_BASE = Priority<KEY ,SPECIALIZATION<ITEM> ,SIZE> ;
	using Node = typename SPECIALIZATION_BASE::Node ;
	using ITEM_TYPE = typename SPECIALIZATION_BASE::ITEM_TYPE ;
	template <class _ARG1>
	using Pair = typename SPECIALIZATION_BASE::template Pair<_ARG1> ;

private:
	friend SPECIALIZATION_BASE ;
	using SPECIALIZATION_BASE::mPriority ;
	using SPECIALIZATION_BASE::mWrite ;
	using SPECIALIZATION_BASE::mTop ;

public:
	Priority () = default ;

	explicit Priority (LENGTH len) :SPECIALIZATION_BASE (len) {}

	implicit Priority (const std::initializer_list<ITEM_TYPE> &right) : Priority (right.size ()) {
		for (auto &&i : right)
			add (i) ;
	}

	LENGTH size () const {
		if (mPriority.size () == 0)
			return 0 ;
		return mPriority.size () - 1 ;
	}

	LENGTH length () const {
		if (mPriority.size () == 0)
			return 0 ;
		return mWrite ;
	}

	void clear () {
		mWrite = 0 ;
	}

	//@warn: index would be no longer valid every time revised
	Pair<Priority> get (INDEX index) & {
		_DEBUG_ASSERT_ (index >= 0 && index < mWrite) ;
		return Pair<Priority> (*this ,index) ;
	}

	inline Pair<Priority> operator[] (INDEX index) & {
		return get (index) ;
	}

	//@warn: index would be no longer valid every time revised
	Pair<const Priority> get (INDEX index) const & {
		_DEBUG_ASSERT_ (index >= 0 && index < mWrite) ;
		return Pair<const Priority> (*this ,index) ;
	}

	inline Pair<const Priority> operator[] (INDEX index) const & {
		return get (index) ;
	}

	Pair<Priority> get (INDEX) && = delete ;

	inline Pair<Priority> operator[] (INDEX) && = delete ;

	INDEX at (const Pair<Priority> &item) const {
		INDEX ret = mPriority.at (_OFFSET_ (&Node::mKey ,item.key)) ;
		if (!(ret >= 0 && ret < mWrite))
			ret = VAR_NONE ;
		return std::move (ret) ;
	}

	//@info: the same as 'const Pair<const X> &' but acceptable in vs2015
	INDEX at (const typename SPECIALIZATION_BASE::Pair_const_BASE &item) const {
		INDEX ret = mPriority.at (_OFFSET_ (&Node::mKey ,item.key)) ;
		if (!(ret >= 0 && ret < mWrite))
			ret = VAR_NONE ;
		return std::move (ret) ;
	}

	INDEX ibegin () const {
		return 0 ;
	}

	INDEX iend () const {
		return length () ;
	}

	INDEX inext (INDEX index) const {
		return index + 1 ;
	}

	BOOL equal (const Priority &right) const {
		if (length () != right.length ())
			return FALSE ;
		if (!_MEMEQUAL_ (mPriority ,right.mPriority ,length ()))
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const Priority &right) const {
		return equal (right) ;
	}

	inline BOOL operator!= (const Priority &right) const {
		return !equal (right) ;
	}

	BOOL empty () const {
		if (mWrite > 0)
			return FALSE ;
		return TRUE ;
	}

	BOOL full () const {
		if (mWrite < mPriority.size ())
			return FALSE ;
		return TRUE ;
	}

	using SPECIALIZATION_BASE::add ;

	inline Priority &operator<< (const ITEM_TYPE &item) {
		add (std::move (item)) ;
		return *this ;
	}

	inline Priority &operator<< (ITEM_TYPE &&item) {
		add (std::move (item)) ;
		return *this ;
	}

	using SPECIALIZATION_BASE::appand ;

	void take () {
		_DEBUG_ASSERT_ (!empty ()) ;
		mPriority[0] = std::move (mPriority[mWrite - 1]) ;
		mWrite-- ;
		update_insert (0) ;
	}

	void take (ITEM_TYPE &item) popping {
		_DEBUG_ASSERT_ (!empty ()) ;
		item = std::move (mPriority[0]) ;
		mPriority[0] = std::move (mPriority[mWrite - 1]) ;
		mWrite-- ;
		update_insert (0) ;
	}

	inline Priority &operator>> (ITEM_TYPE &item) popping {
		take (item) ;
		return *this ;
	}

	INDEX peek () const {
		_DEBUG_ASSERT_ (!empty ()) ;
		return 0 ;
	}

	INDEX insert (const KEY &key) popping {
		reserve (1) ;
		INDEX ret = mWrite ;
		mPriority[ret].mKey = std::move (key) ;
		update_resize () ;
		update_insert (ret) ;
		ret = mTop ;
		return std::move (ret) ;
	}

	INDEX insert (KEY &&key) popping {
		reserve (1) ;
		INDEX ret = mWrite ;
		mPriority[ret].mKey = std::move (key) ;
		update_resize () ;
		update_insert (ret) ;
		ret = mTop ;
		return std::move (ret) ;
	}

	void remove (INDEX index) {
		_DEBUG_ASSERT_ (index >= 0 && index < mWrite) ;
		mPriority[index] = std::move (mPriority[mWrite - 1]) ;
		mWrite-- ;
		update_insert (index) ;
	}

	Array<INDEX> esort () const {
		Array<INDEX> ret = Array<INDEX> (length ()) ;
		INDEX iw = 0 ;
		for (INDEX i = ibegin () ,ie = iend () ; i != ie ; i = inext (i))
			ret[iw++] = i ;
		_DEBUG_ASSERT_ (iw == ret.length ()) ;
		INDEX ix = ret.length () ;
		while (TRUE) {
			if (ix - 1 < 1)
				break ;
			_SWAP_ (ret[0] ,ret[ix - 1]) ;
			compute_esort (ret ,ix - 1) ;
			ix-- ;
		}
		if (ret.size () > 0)
			_MEMRCOPY_ (ret.raw ().self ,ret.raw ().self ,ret.size ()) ;
		return std::move (ret) ;
	}

private:
	void reserve (LENGTH len) {
		const auto r1x = _MAX_ (len - (mPriority.size () - length ()) ,VAR_ZERO) ;
		if (r1x == 0)
			return ;
		auto rax = mPriority.expand (mPriority.size () + r1x) ;
		_MEMMOVE_ (rax.self ,mPriority.self ,mPriority.size ()) ;
		mPriority.swap (rax) ;
	}

	void update_resize () {
		_DEBUG_ASSERT_ (mWrite >= 0 && mWrite < mPriority.size ()) ;
		mWrite++ ;
		if (mWrite < mPriority.size ())
			return ;
		auto rax = mPriority.expand () ;
		_MEMMOVE_ (rax.self ,mPriority.self ,mPriority.size ()) ;
		mPriority.swap (rax) ;
	}

	void update_insert (INDEX it) {
		INDEX ix = it ;
		auto rax = std::move (mPriority[ix]) ;
		while (TRUE) {
			//@info: '(0 - 1) >> 1' is not the same as '(0 - 1) / 2'
			INDEX iy = (ix - 1) >> 1 ;
			if (iy < 0)
				break ;
			if (!(rax.mKey < mPriority[iy].mKey))
				break ;
			mPriority[ix] = std::move (mPriority[iy]) ;
			ix = iy ;
		}
		while (TRUE) {
			INDEX iy = ix * 2 + 1 ;
			if (iy >= mWrite)
				break ;
			INDEX jx = ix ;
			if (mPriority[iy].mKey < rax.mKey)
				jx = iy ;
			iy++ ;
			auto &r1 = (jx != ix) ? (mPriority[jx].mKey) : (rax.mKey) ;
			if (iy < mWrite && r1 > mPriority[iy].mKey)
				jx = iy ;
			if (jx == ix)
				break ;
			mPriority[ix] = std::move (mPriority[jx]) ;
			ix = jx ;
		}
		mPriority[ix] = std::move (rax) ;
		mTop = ix ;
	}

	void compute_esort (Array<INDEX> &out ,LENGTH len) const {
		INDEX ix = 0 ;
		const auto r1x = out[ix] ;
		while (TRUE) {
			INDEX iy = ix * 2 + 1 ;
			if (iy >= len)
				break ;
			INDEX jx = ix ;
			if (mPriority[out[iy]].mKey < mPriority[r1x].mKey)
				jx = iy ;
			iy++ ;
			auto &r1 = (jx != ix) ? (mPriority[out[jx]].mKey) : (mPriority[r1x].mKey) ;
			if (iy < len && r1 > mPriority[out[iy]].mKey)
				jx = iy ;
			if (jx == ix)
				break ;
			out[ix] = out[jx] ;
			ix = jx ;
		}
		out[ix] = r1x ;
	}
} ;

template <class ITEM ,class SIZE = SAUTO>
class Deque ;

template <class ITEM ,class SIZE>
class Deque {
private:
	class Node {
	private:
		friend Deque ;
		ITEM mItem ;
		INDEX mHead ;

	public:
		inline Node () = delete ;

		inline explicit Node (INDEX head) :mHead (head) {}

		inline explicit Node (const ITEM &item ,INDEX head) : mItem (std::move (item)) ,mHead (head) {}

		inline explicit Node (ITEM &&item ,INDEX head) : mItem (std::move (item)) ,mHead (head) {}
	} ;

private:
	Allocator<Node ,SIZE> mList ;
	Buffer<Buffer<INDEX ,ARGC<2>> ,SIZE> mDeque ;
	INDEX mRead ;
	INDEX mWrite ;

public:
	Deque () {
		clear () ;
	}

	explicit Deque (LENGTH len) :Deque (ARGVP0 ,len) {
		clear () ;
	}

	implicit Deque (const std::initializer_list<ITEM> &right) : Deque (right.size ()) {
		for (auto &&i : right)
			add (i) ;
	}

	LENGTH size () const {
		return mList.size () ;
	}

	LENGTH length () const {
		return mList.length () ;
	}

	void clear () {
		const auto r1x = Buffer<INDEX ,ARGC<2>> ({VAR_NONE ,VAR_ZERO}) ;
		_MEMFILL_ (mDeque.self ,mDeque.size () ,r1x) ;
		mRead = 0 ;
		mWrite = 0 ;
	}

	ITEM &get (INDEX index) & {
		return mList[index].mItem ;
	}

	inline ITEM &operator[] (INDEX index) & {
		return get (index) ;
	}

	const ITEM &get (INDEX index) const & {
		return mList[index].mItem ;
	}

	inline const ITEM &operator[] (INDEX index) const & {
		return get (index) ;
	}

	ITEM &get (INDEX) && = delete ;

	inline ITEM &operator[] (INDEX) && = delete ;

	INDEX at (const ITEM &item) const {
		return mList.at (_OFFSET_ (&Node::mItem ,item)) ;
	}

	INDEX access (INDEX pos) const {
		_DEBUG_ASSERT_ (pos >= 0 && pos < length ()) ;
		if (mWrite - mRead + 1 == mList.length ())
			return mDeque[mRead + pos][0] ;
		if (mWrite - mRead == mList.length () && mDeque[mWrite][0] == VAR_NONE)
			return mDeque[mRead + pos][0] ;
		if (mWrite - mRead == mList.length () && mDeque[mRead][0] == VAR_NONE)
			return mDeque[mRead + pos + 1][0] ;
		return access (pos ,mRead ,(mWrite - mRead + 1)) ;
	}

	INDEX ibegin () const {
		if (mDeque.size () == 0)
			return VAR_NONE ;
		for (INDEX i = mRead ,ie = mWrite + 1 ; i < ie ; i++)
			if (mDeque[i][0] != VAR_NONE)
				return mDeque[i][0] ;
		return VAR_NONE ;
	}

	INDEX iend () const {
		return VAR_NONE ;
	}

	INDEX inext (INDEX index) const {
		for (INDEX i = mList[index].mHead + 1 ,ie = mWrite + 1 ; i < ie ; i++)
			if (mDeque[i][0] != VAR_NONE)
				return mDeque[i][0] ;
		return VAR_NONE ;
	}

	BOOL equal (const Deque &right) const {
		if (length () != right.length ())
			return FALSE ;
		INDEX ir = ibegin () ;
		INDEX ie = iend () ;
		INDEX jr = right.ibegin () ;
		INDEX je = right.iend () ;
		while (TRUE) {
			if (ir == ie)
				break ;
			if (jr == je)
				break ;
			if (get (ir) != right.get (jr))
				break ;
			ir = inext (ir) ;
			jr = right.inext (jr) ;
		}
		if (ir != ie)
			return FALSE ;
		if (jr != je)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const Deque &right) const {
		return equal (right) ;
	}

	inline BOOL operator!= (const Deque &right) const {
		return !equal (right) ;
	}

	BOOL empty () const {
		if (mList.length () > 0)
			return FALSE ;
		return TRUE ;
	}

	BOOL full () const {
		if (mList.length () < mList.size ())
			return FALSE ;
		return TRUE ;
	}

	void add (const ITEM &item) {
		INDEX ix = mList.alloc (std::move (item) ,VAR_NONE) ;
		update_resize (ix) ;
		update_compress_left (mWrite ,ix) ;
	}

	inline Deque &operator<< (const ITEM &item) {
		add (std::move (item)) ;
		return *this ;
	}

	void add (ITEM &&item) {
		INDEX ix = mList.alloc (std::move (item) ,VAR_NONE) ;
		update_resize (ix) ;
		update_compress_left (mWrite ,ix) ;
	}

	inline Deque &operator<< (ITEM &&item) {
		add (std::move (item)) ;
		return *this ;
	}

	template <class _ARG1>
	void appand (const _ARG1 &src) {
		mList.reserve (src.length ()) ;
		for (auto &&i : src)
			add (std::move (i)) ;
	}

	template <class _ARG1>
	void appand (_ARG1 &&src) {
		mList.reserve (src.length ()) ;
		for (auto &&i : src)
			add (std::move (i)) ;
	}

	void take () {
		_DEBUG_ASSERT_ (!empty ()) ;
		while (mDeque[mRead][0] == VAR_NONE)
			mRead++ ;
		INDEX ix = mDeque[mRead][0] ;
		deque_remove (ix) ;
		mList.free (ix) ;
	}

	void take (ITEM &item) popping {
		_DEBUG_ASSERT_ (!empty ()) ;
		while (mDeque[mRead][0] == VAR_NONE)
			mRead++ ;
		INDEX ix = mDeque[mRead][0] ;
		item = std::move (mList[ix].mItem) ;
		deque_remove (mRead) ;
		mList.free (ix) ;
	}

	inline Deque &operator>> (ITEM &item) popping {
		take (item) ;
		return *this ;
	}

	INDEX insert () popping {
		INDEX ret = mList.alloc (VAR_NONE) ;
		update_resize (ret) ;
		update_compress_left (mWrite ,ret) ;
		return std::move (ret) ;
	}

	INDEX insert_before (INDEX index) popping {
		INDEX ret = mList.alloc (VAR_NONE) ;
		update_resize (ret) ;
		const auto r1x = (index != VAR_NONE) ? (mList[index].mHead) : mWrite ;
		update_compress_left (r1x ,ret) ;
		return std::move (ret) ;
	}

	INDEX insert_after (INDEX index) popping {
		INDEX ret = mList.alloc (VAR_NONE) ;
		update_resize (ret) ;
		const auto r1x = (index != VAR_NONE) ? (mList[index].mHead + 1) : mRead ;
		update_compress_left (r1x ,ret) ;
		return std::move (ret) ;
	}

	void pop () {
		_DEBUG_ASSERT_ (!empty ()) ;
		while (mDeque[mWrite][0] == VAR_NONE)
			mWrite-- ;
		INDEX ix = mDeque[mWrite][0] ;
		deque_remove (mWrite) ;
		mList.free (ix) ;
	}

	void swap (INDEX index1 ,INDEX index2) {
		if (index1 == index2)
			return ;
		deque_rewrite (mList[index1].mHead ,index2) ;
		deque_rewrite (mList[index2].mHead ,index1) ;
	}

	void splice_before (INDEX index ,INDEX seg) {
		deque_remove (mList[seg].mHead) ;
		const auto r1x = insert_before (index ,seg) ;
		(void) r1x ;
	}

	void splice_after (INDEX index ,INDEX seg) {
		deque_remove (mList[seg].mHead) ;
		const auto r1x = insert_after (index ,seg) ;
		(void) r1x ;
	}

	void remove (INDEX index) {
		deque_remove (mList[index].mHead) ;
		mList.free (index) ;
	}

	INDEX find (const ITEM &item) const {
		for (INDEX i = ibegin () ,ie = iend () ; i != ie ; i = inext (i))
			if (get (i) == item)
				return i ;
		return VAR_NONE ;
	}

	void erase (const ITEM &item) {
		for (INDEX i = ibegin () ,ir ,ie = iend () ; i != ie ; i = ir) {
			ir = inext (i) ;
			if (!(get (i) == item))
				continue ;
			remove (i) ;
		}
	}

	Array<INDEX> esort () const {
		Array<INDEX> ret = Array<INDEX> (length ()) ;
		INDEX iw = 0 ;
		for (INDEX i = ibegin () ,ie = iend () ; i != ie ; i = inext (i))
			ret[iw++] = i ;
		_DEBUG_ASSERT_ (iw == ret.length ()) ;
		U::OPERATOR_SORT::invoke (*this ,ret ,0 ,ret.length ()) ;
		return std::move (ret) ;
	}

	void sort () {
		if (length () < 2)
			return ;
		const auto r1x = esort () ;
		for (INDEX i = 0 ; i < r1x.length () ; i++)
			deque_rewrite (i ,r1x[i]) ;
		for (INDEX i = r1x.length () ; i < mDeque.size () ; i++)
			deque_remove (i) ;
		mRead = 0 ;
		mWrite = _MAX_ ((r1x.length () - 1) ,VAR_ZERO) ;
	}

	void reverse () {
		if (mDeque.size () == 0)
			return ;
		INDEX ix = mRead ;
		INDEX iy = mWrite ;
		while (TRUE) {
			while (ix < iy && mDeque[ix] != VAR_NONE)
				ix++ ;
			if (ix >= iy)
				break ;
			while (ix < iy && mDeque[iy] != VAR_NONE)
				iy-- ;
			if (ix >= iy)
				break ;
			const auto r1x = mDeque[ix] ;
			const auto r2x = mDeque[iy] ;
			deque_rewrite (ix ,r2x) ;
			deque_rewrite (iy ,r1x) ;
		}
	}

private:
	explicit Deque (const DEF<decltype (ARGVP0)> & ,LENGTH len) :mList (len) ,mDeque (len) {}

private:
	INDEX access (INDEX pos ,INDEX seg ,LENGTH seg_len) const {
		_DEBUG_ASSERT_ (seg_len > 0) ;
		INDEX ret = VAR_NONE ;
		INDEX ix = seg ;
		INDEX iy = seg + seg_len - 1 ;
		while (TRUE) {
			if (ix > iy)
				break ;
			ret = ix + (iy - ix + 1) / 2 ;
			INDEX jx = position_before (ret) ;
			if (jx == pos && mDeque[ret][0] != VAR_NONE)
				break ;
			auto &r1 = (jx < pos) ? ix : iy ;
			const auto r1x = (jx < pos) ? (ret + 1) : (ret - 1) ;
			r1 = r1x ;
		}
		_DEBUG_ASSERT_ (ret != VAR_NONE) ;
		ret = mDeque[ret][0] ;
		return std::move (ret) ;
	}

	INDEX position_before (INDEX it) const {
		INDEX ret = 0 ;
		INDEX ix = it ;
		while (TRUE) {
			if (ix < 0)
				break ;
			ret += mDeque[ix][1] ;
			ix -= (ix + 1) & -(ix + 1) ;
		}
		ret-- ;
		return std::move (ret) ;
	}

	void update_resize (INDEX it) {
		if (mDeque.size () == mList.size ())
			return ;
		auto rax = mDeque.expand (mList.size ()) ;
		const auto r1x = Buffer<INDEX ,ARGC<2>> ({VAR_NONE ,VAR_ZERO}) ;
		_MEMFILL_ (rax.self ,rax.size () ,r1x) ;
		for (INDEX i = 0 ; i < mList.size () ; i++) {
			if (i == it)
				continue ;
			if (!mList.used (i))
				continue ;
			deque_rewrite (mList[i].mHead ,i) ;
		}
		mDeque.swap (rax) ;
	}

	void update_compress_left (INDEX it ,INDEX jt) {
		_CALL_ONE_ ([&] (BOOL &if_context) {
			if (mDeque[it][0] != VAR_NONE)
				discard ;
			deque_rewrite (it ,jt) ;
			mWrite = _MIN_ ((it + 1) ,(mDeque.size () - 1)) ;
		} ,[&] (BOOL &if_context) {
			INDEX ix = it + 1 ;
			if (ix >= mDeque.size ())
				discard ;
			if (mDeque[ix][0] != VAR_NONE)
				discard ;
			deque_rewrite (ix ,jt) ;
			mWrite = _MIN_ ((ix + 1) ,(mDeque.size () - 1)) ;
		} ,[&] (BOOL &if_context) {
			update_compress_left_force (it ,jt) ;
		}) ;
	}

	void update_compress_left_force (INDEX it ,INDEX jt) {
		INDEX ix = it ;
		INDEX iy = jt ;
		for (INDEX i = 0 ; i < mList.length () ; i++) {
			while (mRead != ix && mDeque[mRead][0] == VAR_NONE)
				mRead++ ;
			const auto r1x = mDeque[i][0] ;
			_CALL_ONE_ ([&] (BOOL &if_context) {
				if (mRead != ix)
					discard ;
				if (r1x != VAR_NONE)
					discard ;
				deque_rewrite (i ,iy) ;
				iy = r1x ;
				ix = VAR_NONE ;
			} ,[&] (BOOL &if_context) {
				if (mRead != ix)
					discard ;
				if (r1x == VAR_NONE)
					discard ;
				deque_rewrite (i ,iy) ;
				iy = r1x ;
				ix++ ;
			} ,[&] (BOOL &if_context) {
				if (mRead == i)
					discard ;
				deque_rewrite (i ,mDeque[mRead][0]) ;
				deque_remove (mRead) ;
			}) ;
			mRead++ ;
		}
		mRead = 0 ;
		mWrite = _MIN_ (mList.length () ,(mDeque.size () - 1)) ;
	}

	void update_compress_right (INDEX it ,INDEX jt) {
		_CALL_ONE_ ([&] (BOOL &if_context) {
			if (mDeque[it][0] != VAR_NONE)
				discard ;
			deque_rewrite (it ,jt) ;
			mRead = _MAX_ ((it - 1) ,VAR_ZERO) ;
		} ,[&] (BOOL &if_context) {
			INDEX ix = it - 1 ;
			if (ix < 0)
				discard ;
			if (mDeque[ix][0] != VAR_NONE)
				discard ;
			deque_rewrite (ix ,jt) ;
			mRead = _MAX_ ((ix - 1) ,VAR_ZERO) ;
		} ,[&] (BOOL &if_context) {
			update_compress_right_force (it ,jt) ;
		}) ;
	}

	void update_compress_right_force (INDEX it ,INDEX jt) {
		INDEX ix = it ;
		INDEX iy = jt ;
		for (INDEX i = 0 ; i < mList.length () ; i++) {
			INDEX jx = mDeque.size () + ~i ;
			while (mWrite != ix && mDeque[mWrite][0] == VAR_NONE)
				mWrite-- ;
			const auto r1x = mDeque[jx][0] ;
			_CALL_ONE_ ([&] (BOOL &if_context) {
				if (mWrite != ix)
					discard ;
				if (r1x != VAR_NONE)
					discard ;
				deque_rewrite (jx ,iy) ;
				iy = r1x ;
				ix = VAR_NONE ;
			} ,[&] (BOOL &if_context) {
				if (mWrite != ix)
					discard ;
				if (r1x == VAR_NONE)
					discard ;
				deque_rewrite (jx ,iy) ;
				iy = r1x ;
				ix-- ;
			} ,[&] (BOOL &if_context) {
				if (mWrite == jx)
					discard ;
				deque_rewrite (jx ,mDeque[mWrite][0]) ;
				deque_remove (mWrite) ;
			}) ;
			mWrite-- ;
		}
		mRead = _MAX_ (mDeque.size () - 1 - mList.length () ,VAR_ZERO) ;
		mWrite = mDeque.size () - 1 ;
	}

	void deque_rewrite (INDEX it ,INDEX jt) {
		_DEBUG_ASSERT_ (jt != VAR_NONE) ;
		INDEX ix = it ;
		const auto r1x = mDeque[it][0] ;
		mDeque[ix][0] = jt ;
		mList[jt].mHead = ix ;
		if (r1x != VAR_NONE)
			return ;
		while (TRUE) {
			if (ix >= mDeque.size ())
				break ;
			mDeque[ix][1]++ ;
			ix += (ix + 1) & -(ix + 1) ;
		}
	}

	void deque_remove (INDEX it) {
		INDEX ix = it ;
		mDeque[ix][0] = VAR_NONE ;
		while (TRUE) {
			if (ix >= mDeque.size ())
				break ;
			mDeque[ix][1]-- ;
			ix += (ix + 1) & -(ix + 1) ;
		}
	}
} ;

template <class ITEM ,class SIZE = SAUTO>
class QList ;

template <class ITEM ,class SIZE>
class QList {
private:
	class Node {
	private:
		friend QList ;
		ITEM mItem ;
		INDEX mLeft ;
		INDEX mRight ;

	public:
		inline Node () = delete ;

		inline explicit Node (INDEX left ,INDEX right) :mLeft (left) ,mRight (right) {}

		inline explicit Node (const ITEM &item ,INDEX left ,INDEX right) : mItem (std::move (item)) ,mLeft (left) ,mRight (right) {}

		inline explicit Node (ITEM &&item ,INDEX left ,INDEX right) : mItem (std::move (item)) ,mLeft (left) ,mRight (right) {}
	} ;

private:
	Allocator<Node ,SIZE> mList ;
	INDEX mFirst ;
	INDEX mLast ;

public:
	QList () {
		clear () ;
	}

	explicit QList (LENGTH len) :QList (ARGVP0 ,len) {
		clear () ;
	}

	implicit QList (const std::initializer_list<ITEM> &right) : QList (right.size ()) {
		for (auto &&i : right)
			add (i) ;
	}

	LENGTH size () const {
		return mList.size () ;
	}

	LENGTH length () const {
		return mList.length () ;
	}

	void clear () {
		mList.clear () ;
		mFirst = VAR_NONE ;
		mLast = VAR_NONE ;
	}

	ITEM &get (INDEX index) & {
		return mList[index].mItem ;
	}

	inline ITEM &operator[] (INDEX index) & {
		return get (index) ;
	}

	const ITEM &get (INDEX index) const & {
		return mList[index].mItem ;
	}

	inline const ITEM &operator[] (INDEX index) const & {
		return get (index) ;
	}

	ITEM &get (INDEX) && = delete ;

	inline ITEM &operator[] (INDEX) && = delete ;

	INDEX at (const ITEM &item) const {
		return mList.at (_OFFSET_ (&Node::mItem ,item)) ;
	}

	INDEX ibegin () const {
		return mFirst ;
	}

	INDEX iend () const {
		return VAR_NONE ;
	}

	INDEX inext (INDEX index) const {
		return mList[index].mRight ;
	}

	Array<INDEX> range () const {
		Array<INDEX> ret = Array<INDEX> (length ()) ;
		INDEX iw = 0 ;
		for (INDEX i = ibegin () ,ie = iend () ; i != ie ; i = inext (i))
			ret[iw++] = i ;
		return std::move (ret) ;
	}

	BOOL equal (const QList &right) const {
		if (length () != right.length ())
			return FALSE ;
		INDEX ir = ibegin () ;
		INDEX ie = iend () ;
		INDEX jr = right.ibegin () ;
		INDEX je = right.iend () ;
		while (TRUE) {
			if (ir == ie)
				break ;
			if (jr == je)
				break ;
			if (get (ir) != right.get (jr))
				break ;
			ir = inext (ir) ;
			jr = right.inext (jr) ;
		}
		if (ir != ie)
			return FALSE ;
		if (jr != je)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const QList &right) const {
		return equal (right) ;
	}

	inline BOOL operator!= (const QList &right) const {
		return !equal (right) ;
	}

	BOOL empty () const {
		if (mList.length () > 0)
			return FALSE ;
		return TRUE ;
	}

	BOOL full () const {
		if (mList.length () < mList.size ())
			return FALSE ;
		return TRUE ;
	}

	void add (const ITEM &item) {
		INDEX ix = mList.alloc (std::move (item) ,mLast ,VAR_NONE) ;
		auto &r1 = (mLast != VAR_NONE) ? (mList[mLast].mRight) : mFirst ;
		r1 = ix ;
		mLast = ix ;
	}

	inline QList &operator<< (const ITEM &item) {
		add (std::move (item)) ;
		return *this ;
	}

	void add (ITEM &&item) {
		INDEX ix = mList.alloc (std::move (item) ,mLast ,VAR_NONE) ;
		auto &r1 = (mLast != VAR_NONE) ? (mList[mLast].mRight) : mFirst ;
		r1 = ix ;
		mLast = ix ;
	}

	inline QList &operator<< (ITEM &&item) {
		add (std::move (item)) ;
		return *this ;
	}

	template <class _ARG1>
	void appand (const _ARG1 &src) {
		mList.reserve (src.length ()) ;
		for (auto &&i : src)
			add (std::move (i)) ;
	}

	template <class _ARG1>
	void appand (_ARG1 &&src) {
		mList.reserve (src.length ()) ;
		for (auto &&i : src)
			add (std::move (i)) ;
	}

	void take () {
		_DEBUG_ASSERT_ (!empty ()) ;
		INDEX ix = mFirst ;
		mFirst = mList[ix].mRight ;
		auto &r1 = (mFirst != VAR_NONE) ? (mList[mFirst].mLeft) : mLast ;
		r1 = VAR_NONE ;
		mList.free (ix) ;
	}

	void take (ITEM &item) popping {
		_DEBUG_ASSERT_ (!empty ()) ;
		INDEX ix = mFirst ;
		item = std::move (mList[ix].mItem) ;
		mFirst = mList[ix].mRight ;
		auto &r1 = (mFirst != VAR_NONE) ? (mList[mFirst].mLeft) : mLast ;
		r1 = VAR_NONE ;
		mList.free (ix) ;
	}

	inline QList &operator>> (ITEM &item) popping {
		take (item) ;
		return *this ;
	}

	INDEX peek () const {
		_DEBUG_ASSERT_ (!empty ()) ;
		return mFirst ;
	}

	INDEX insert () popping {
		INDEX ret = mList.alloc (mLast ,VAR_NONE) ;
		auto &r1 = (mLast != VAR_NONE) ? (mList[mLast].mRight) : mFirst ;
		r1 = ret ;
		mLast = ret ;
		return std::move (ret) ;
	}

	INDEX insert_before (INDEX index) popping {
		INDEX ret = mList.alloc (VAR_NONE ,index) ;
		auto &r1 = (index != VAR_NONE) ? (mList[index].mLeft) : mLast ;
		mList[ret].mLeft = r1 ;
		auto &r2 = (r1 != VAR_NONE) ? (mList[r1].mRight) : mFirst ;
		r2 = ret ;
		r1 = ret ;
		return std::move (ret) ;
	}

	INDEX insert_after (INDEX index) popping {
		const auto r1x = (index != VAR_NONE) ? (mList[index].mRight) : mFirst ;
		return insert_before (r1x) ;
	}

	void pop () {
		_DEBUG_ASSERT_ (!empty ()) ;
		INDEX ix = mLast ;
		mLast = mList[ix].mLeft ;
		auto &r1 = (mLast != VAR_NONE) ? (mList[mLast].mRight) : mFirst ;
		r1 = VAR_NONE ;
		mList.free (ix) ;
	}

	void swap (INDEX index1 ,INDEX index2) {
		if (index1 == index2)
			return ;
		auto &r1 = prev_next (index1) ;
		auto &r2 = prev_next (index2) ;
		auto &r3 = next_prev (index1) ;
		auto &r4 = next_prev (index2) ;
		r1 = index2 ;
		r2 = index1 ;
		r3 = index2 ;
		r4 = index1 ;
		_SWAP_ (mList[index1].mLeft ,mList[index2].mLeft) ;
		_SWAP_ (mList[index1].mRight ,mList[index2].mRight) ;
	}

	void splice_before (INDEX index ,INDEX seg) {
		prev_next (seg) = mList[seg].mRight ;
		next_prev (seg) = mList[seg].mLeft ;
		auto &r1 = (index != VAR_NONE) ? (mList[index].mLeft) : mLast ;
		mList[seg].mLeft = r1 ;
		auto &r2 = (r1 != VAR_NONE) ? (mList[r1].mRight) : mFirst ;
		r2 = seg ;
		r1 = seg ;
	}

	void splice_after (INDEX index ,INDEX seg) {
		const auto r1x = (index != VAR_NONE) ? (mList[index].mRight) : mFirst ;
		splice_before (r1x ,seg) ;
	}

	void remove (INDEX index) {
		prev_next (index) = mList[index].mRight ;
		next_prev (index) = mList[index].mLeft ;
		mList.free (index) ;
	}

	INDEX find (const ITEM &item) const {
		for (INDEX i = ibegin () ,ie = iend () ; i != ie ; i = inext (i))
			if (get (i) == item)
				return i ;
		return VAR_NONE ;
	}

	void erase (const ITEM &item) {
		for (INDEX i = ibegin () ,ir ,ie = iend () ; i != ie ; i = ir) {
			ir = inext (i) ;
			if (!(get (i) == item))
				continue ;
			remove (i) ;
		}
	}

	Array<INDEX> esort () const {
		Array<INDEX> ret = Array<INDEX> (length ()) ;
		INDEX iw = 0 ;
		for (INDEX i = ibegin () ,ie = iend () ; i != ie ; i = inext (i))
			ret[iw++] = i ;
		_DEBUG_ASSERT_ (iw == ret.length ()) ;
		U::OPERATOR_SORT::invoke (*this ,ret ,0 ,ret.length ()) ;
		return std::move (ret) ;
	}

	void sort () {
		if (length () < 2)
			return ;
		const auto r1x = esort () ;
		_DEBUG_ASSERT_ (r1x.length () >= 2) ;
		for (INDEX i = 0 ; i < 1 ; i++) {
			mList[r1x[i]].mLeft = VAR_NONE ;
			mList[r1x[i]].mRight = r1x[i + 1] ;
			mFirst = r1x[i] ;
		}
		for (INDEX i = 1 ,ie = r1x.length () - 1 ; i < ie ; i++) {
			mList[r1x[i]].mLeft = r1x[i - 1] ;
			mList[r1x[i]].mRight = r1x[i + 1] ;
		}
		for (INDEX i = r1x.length () - 1 ; i < r1x.length () ; i++) {
			mList[r1x[i]].mLeft = r1x[i - 1] ;
			mList[r1x[i]].mRight = VAR_NONE ;
			mLast = r1x[i] ;
		}
	}

private:
	explicit QList (const DEF<decltype (ARGVP0)> & ,LENGTH len) :mList (len) {}

private:
	INDEX &prev_next (INDEX it) & {
		if (mList[it].mLeft == VAR_NONE)
			return mFirst ;
		return mList[mList[it].mLeft].mRight ;
	}

	INDEX &prev_next (INDEX) && = delete ;

	INDEX &next_prev (INDEX it) & {
		if (mList[it].mRight == VAR_NONE)
			return mLast ;
		return mList[mList[it].mRight].mLeft ;
	}

	INDEX &next_prev (INDEX) && = delete ;
} ;

template <class SIZE = SAUTO>
class BitSet ;

template <class SIZE>
class BitSet {
private:
	inline static constexpr LENGTH expr_size (LENGTH len) {
		return (len <= 0) ? len : ((len + 7) / 8) ;
	}

	template <class BASE>
	class Bit {
	private:
		friend BitSet ;
		BASE &mBase ;
		INDEX mIndex ;

	public:
		inline Bit () = delete ;

		inline Bit (const Bit &) = delete ;

		inline Bit (Bit &&) noexcept = default ;

		inline explicit operator BOOL () const & = delete ;

		inline implicit operator BOOL () && {
			const auto r1x = mBase.mSet[mIndex / 8] & (BYTE (0X01) << (mIndex % 8)) ;
			if (r1x == 0)
				return FALSE ;
			return TRUE ;
		}

#ifdef __CSC_CONFIG_VAR32__
		inline implicit operator VAR32 () const & {
			return VAR32 (mIndex) ;
		}

		inline explicit operator VAR32 () && = delete ;

		inline explicit operator VAR64 () const & {
			return VAR64 (mIndex) ;
		}

		inline explicit operator VAR64 () && = delete ;
#elif defined __CSC_CONFIG_VAR64__
		inline explicit operator VAR32 () const & {
			return VAR32 (mIndex) ;
		}

		inline explicit operator VAR32 () && = delete ;

		inline implicit operator VAR64 () const & {
			return VAR64 (mIndex) ;
		}

		inline explicit operator VAR64 () && = delete ;
#endif

		inline void operator= (const BOOL &right) && {
			const auto r1x = mBase.mSet[mIndex / 8] ;
			const auto r2x = right ? (~r1x) : r1x ;
			const auto r3x = BYTE (r2x & (BYTE (0X01) << (mIndex % 8))) ;
			mBase.mSet[mIndex / 8] = BYTE (r1x ^ r3x) ;
		}

		inline void operator= (Bit<BitSet> &&right) && {
			const auto r1x = BOOL (std::move (right)) ;
			std::move (*this) = r1x ;
		}

		inline void operator= (Bit<const BitSet> &&right) && {
			const auto r1x = BOOL (std::move (right)) ;
			std::move (*this) = r1x ;
		}

	private:
		inline explicit Bit (BASE &base ,INDEX index) popping : mBase (base) ,mIndex (index) {}
	} ;

private:
	Buffer<BYTE ,ARGC<expr_size (SIZE::value)>> mSet ;
	LENGTH mWidth ;

public:
	BitSet () :BitSet (ARGVP0) {
		clear () ;
	}

	explicit BitSet (LENGTH len) :BitSet (ARGVP0 ,expr_size (len) ,expr_width (len)) {
		clear () ;
	}

	implicit BitSet (const std::initializer_list<INDEX> &right) : BitSet (expr_size (right)) {
		for (auto &&i : right)
			get (i) = TRUE ;
	}

	LENGTH size () const {
		if (mSet.size () == 0)
			return 0 ;
		return mWidth ;
	}

	LENGTH length () const {
		static constexpr auto M_TABLE = PACK<VAR32[256]> ({
			0 ,1 ,1 ,2 ,1 ,2 ,2 ,3 ,1 ,2 ,2 ,3 ,2 ,3 ,3 ,4 ,
			1 ,2 ,2 ,3 ,2 ,3 ,3 ,4 ,2 ,3 ,3 ,4 ,3 ,4 ,4 ,5 ,
			1 ,2 ,2 ,3 ,2 ,3 ,3 ,4 ,2 ,3 ,3 ,4 ,3 ,4 ,4 ,5 ,
			2 ,3 ,3 ,4 ,3 ,4 ,4 ,5 ,3 ,4 ,4 ,5 ,4 ,5 ,5 ,6 ,
			1 ,2 ,2 ,3 ,2 ,3 ,3 ,4 ,2 ,3 ,3 ,4 ,3 ,4 ,4 ,5 ,
			2 ,3 ,3 ,4 ,3 ,4 ,4 ,5 ,3 ,4 ,4 ,5 ,4 ,5 ,5 ,6 ,
			2 ,3 ,3 ,4 ,3 ,4 ,4 ,5 ,3 ,4 ,4 ,5 ,4 ,5 ,5 ,6 ,
			3 ,4 ,4 ,5 ,4 ,5 ,5 ,6 ,4 ,5 ,5 ,6 ,5 ,6 ,6 ,7 ,
			1 ,2 ,2 ,3 ,2 ,3 ,3 ,4 ,2 ,3 ,3 ,4 ,3 ,4 ,4 ,5 ,
			2 ,3 ,3 ,4 ,3 ,4 ,4 ,5 ,3 ,4 ,4 ,5 ,4 ,5 ,5 ,6 ,
			2 ,3 ,3 ,4 ,3 ,4 ,4 ,5 ,3 ,4 ,4 ,5 ,4 ,5 ,5 ,6 ,
			3 ,4 ,4 ,5 ,4 ,5 ,5 ,6 ,4 ,5 ,5 ,6 ,5 ,6 ,6 ,7 ,
			2 ,3 ,3 ,4 ,3 ,4 ,4 ,5 ,3 ,4 ,4 ,5 ,4 ,5 ,5 ,6 ,
			3 ,4 ,4 ,5 ,4 ,5 ,5 ,6 ,4 ,5 ,5 ,6 ,5 ,6 ,6 ,7 ,
			3 ,4 ,4 ,5 ,4 ,5 ,5 ,6 ,4 ,5 ,5 ,6 ,5 ,6 ,6 ,7 ,
			4 ,5 ,5 ,6 ,5 ,6 ,6 ,7 ,5 ,6 ,6 ,7 ,6 ,7 ,7 ,8}) ;
		LENGTH ret = 0 ;
		for (INDEX i = 0 ; i < mSet.size () ; i++)
			ret += M_TABLE.P1[mSet[i]] ;
		if (mWidth % 8 != 0)
			ret -= M_TABLE.P1[mSet[mWidth / 8] & ~((VAR (1) << (mWidth % 8)) - 1)] ;
		return std::move (ret) ;
	}

	void clear () {
		fill (BYTE (0X00)) ;
	}

	//@info: 'Bit &&' convert to 'BOOL' implicitly while 'const Bit &' convert to 'VAR' implicitly
	Bit<BitSet> get (INDEX index) & {
		_DEBUG_ASSERT_ (index >= 0 && index < mWidth) ;
		return Bit<BitSet> (*this ,index) ;
	}

	inline Bit<BitSet> operator[] (INDEX index) & {
		return get (index) ;
	}

	//@info: 'Bit &&' convert to 'BOOL' implicitly while 'const Bit &' convert to 'VAR' implicitly
	Bit<const BitSet> get (INDEX index) const & {
		_DEBUG_ASSERT_ (index >= 0 && index < mWidth) ;
		return Bit<const BitSet> (*this ,index) ;
	}

	inline Bit<const BitSet> operator[] (INDEX index) const & {
		return get (index) ;
	}

	Bit<BitSet> get (INDEX) && = delete ;

	inline Bit<BitSet> operator[] (INDEX) && = delete ;

	INDEX at (const Bit<BitSet> &item) const {
		if (this != &item.mBase)
			return VAR_NONE ;
		return INDEX (item) ;
	}

	INDEX at (const Bit<const BitSet> &item) const {
		if (this == &item.mBase)
			return VAR_NONE ;
		return INDEX (item) ;
	}

	INDEX access (INDEX pos) const {
		_DEBUG_ASSERT_ (pos >= 0 && pos < length ()) ;
		INDEX ret = ibegin () ;
		INDEX ie = iend () ;
		INDEX ix = 0 ;
		while (TRUE) {
			if (ix == ie)
				break ;
			if (ix >= pos)
				break ;
			ret = inext (ret) ;
			ix++ ;
		}
		return std::move (ret) ;
	}

	INDEX ibegin () const {
		for (INDEX i = 0 ; i < size () ; i++)
			if (get (i))
				return i ;
		return VAR_NONE ;
	}

	INDEX iend () const {
		return VAR_NONE ;
	}

	INDEX inext (INDEX index) const {
		for (INDEX i = index + 1 ; i < size () ; i++)
			if (get (i))
				return i ;
		return VAR_NONE ;
	}

	Array<INDEX> range () const {
		Array<INDEX> ret = Array<INDEX> (length ()) ;
		INDEX iw = 0 ;
		for (INDEX i = ibegin () ,ie = iend () ; i != ie ; i = inext (i))
			ret[iw++] = i ;
		return std::move (ret) ;
	}

	BOOL equal (const BitSet &right) const {
		_DEBUG_ASSERT_ (size () == right.size ()) ;
		INDEX ix = mSet.size () - 1 ;
		if (ix < 0)
			return TRUE ;
		for (INDEX i = 0 ; i < ix ; i++)
			if (mSet[i] != right.mSet[i])
				return FALSE ;
		const auto r1x = mSet[ix] & (mWidth % 8 - 1) ;
		const auto r2x = right.mSet[ix] & (mWidth % 8 - 1) ;
		if (r1x != r2x)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const BitSet &right) const {
		return equal (right) ;
	}

	inline BOOL operator!= (const BitSet &right) const {
		return !equal (right) ;
	}

	BOOL less (const BitSet &right) const {
		_DEBUG_ASSERT_ (size () == right.size ()) ;
		INDEX ix = mSet.size () - 1 ;
		if (ix < 0)
			return FALSE ;
		const auto r1x = _MEMLESS_ (mSet ,right.mSet ,ix) ;
		if (r1x < 0)
			return TRUE ;
		if (r1x > 0)
			return FALSE ;
		const auto r2x = mSet[ix] & (mWidth % 8 - 1) ;
		const auto r3x = right.mSet[ix] & (mWidth % 8 - 1) ;
		if (r2x >= r3x)
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator< (const BitSet &right) const {
		return less (right) ;
	}

	inline BOOL operator>= (const BitSet &right) const {
		return !less (right) ;
	}

	inline BOOL operator> (const BitSet &right) const {
		return right.less (*this) ;
	}

	inline BOOL operator<= (const BitSet &right) const {
		return !right.less (*this) ;
	}

	void add (INDEX item) {
		_DYNAMIC_ASSERT_ (item >= 0 && item < mWidth) ;
		get (item) = TRUE ;
	}

	inline BitSet &operator<< (INDEX item) {
		add (item) ;
		return *this ;
	}

	void erase (INDEX item) {
		_DYNAMIC_ASSERT_ (item >= 0 && item < mWidth) ;
		get (item) = FALSE ;
	}

	BitSet band (const BitSet &right) const {
		_DEBUG_ASSERT_ (size () == right.size ()) ;
		BitSet ret = BitSet (mWidth) ;
		for (INDEX i = 0 ; i < mSet.size () ; i++)
			ret.mSet[i] = mSet[i] & right.mSet[i] ;
		return std::move (ret) ;
	}

	inline BitSet operator& (const BitSet &right) const {
		return band (right) ;
	}

	void bandto (const BitSet &right) {
		_DEBUG_ASSERT_ (size () == right.size ()) ;
		for (INDEX i = 0 ; i < mSet.size () ; i++)
			mSet[i] &= right.mSet[i] ;
	}

	inline BitSet &operator&= (const BitSet &right) {
		bandto (right) ;
		return *this ;
	}

	BitSet bor (const BitSet &right) const {
		_DEBUG_ASSERT_ (size () == right.size ()) ;
		BitSet ret = BitSet (mWidth) ;
		for (INDEX i = 0 ; i < mSet.size () ; i++)
			ret.mSet[i] = mSet[i] | right.mSet[i] ;
		return std::move (ret) ;
	}

	inline BitSet operator| (const BitSet &right) const {
		return bor (right) ;
	}

	void borto (const BitSet &right) {
		_DEBUG_ASSERT_ (size () == right.size ()) ;
		for (INDEX i = 0 ; i < mSet.size () ; i++)
			mSet[i] |= right.mSet[i] ;
	}

	inline BitSet &operator|= (const BitSet &right) {
		borto (right) ;
		return *this ;
	}

	BitSet bxor (const BitSet &right) const {
		_DEBUG_ASSERT_ (size () == right.size ()) ;
		BitSet ret = BitSet (mWidth) ;
		for (INDEX i = 0 ; i < mSet.size () ; i++)
			ret.mSet[i] = mSet[i] ^ right.mSet[i] ;
		return std::move (ret) ;
	}

	inline BitSet operator^ (const BitSet &right) const {
		return bxor (right) ;
	}

	void bxorto (const BitSet &right) {
		_DEBUG_ASSERT_ (size () == right.size ()) ;
		for (INDEX i = 0 ; i < mSet.size () ; i++)
			mSet[i] ^= right.mSet[i] ;
	}

	inline BitSet &operator^= (const BitSet &right) {
		bxorto (right) ;
		return *this ;
	}

	BitSet bsub (const BitSet &right) const {
		_DEBUG_ASSERT_ (size () == right.size ()) ;
		BitSet ret = BitSet (mWidth) ;
		for (INDEX i = 0 ; i < mSet.size () ; i++)
			ret.mSet[i] = mSet[i] & ~right.mSet[i] ;
		return std::move (ret) ;
	}

	inline BitSet operator- (const BitSet &right) const {
		return bsub (right) ;
	}

	void bsubto (const BitSet &right) {
		_DEBUG_ASSERT_ (size () == right.size ()) ;
		for (INDEX i = 0 ; i < mSet.size () ; i++)
			mSet[i] &= ~right.mSet[i] ;
	}

	inline BitSet &operator-= (const BitSet &right) {
		bsubto (right) ;
		return *this ;
	}

	BitSet bnot () const {
		BitSet ret = BitSet (mWidth) ;
		for (INDEX i = 0 ; i < mSet.size () ; i++)
			ret.mSet[i] = ~mSet[i] ;
		return std::move (ret) ;
	}

	inline BitSet operator~ () const {
		return bnot () ;
	}

	Array<INDEX> esort () const {
		Array<INDEX> ret = Array<INDEX> (length ()) ;
		INDEX iw = 0 ;
		for (INDEX i = ibegin () ,ie = iend () ; i != ie ; i = inext (i))
			ret[iw++] = i ;
		_DEBUG_ASSERT_ (iw == ret.length ()) ;
		return std::move (ret) ;
	}

	void fill (const BYTE &val) {
		for (INDEX i = 0 ; i < mSet.size () ; i++)
			mSet[i] = val ;
	}

private:
	explicit BitSet (const DEF<decltype (ARGVP0)> &) :mWidth (0) {}

	explicit BitSet (const DEF<decltype (ARGVP0)> & ,LENGTH len ,LENGTH width) :mSet (len) ,mWidth (width) {}

private:
	inline static LENGTH expr_size (const std::initializer_list<INDEX> &right) {
		LENGTH ret = VAR_NONE ;
		for (auto &&i : right)
			ret = _MAX_ (ret ,i) ;
		_DEBUG_ASSERT_ (ret >= 0) ;
		ret++ ;
		return std::move (ret) ;
	}

	inline static LENGTH expr_width (LENGTH width) {
		_DEBUG_ASSERT_ (width >= 0 && width < VAR32_MAX) ;
		return width ;
	}
} ;

template <class KEY ,class ITEM = void ,class SIZE = SAUTO>
class Set ;

template <class KEY ,class ITEM ,class SIZE>
class Set<KEY ,SPECIALIZATION<ITEM> ,SIZE> {
private:
	using SPECIALIZATION_TYPE = Set<KEY ,ITEM ,SIZE> ;

	class Node {
	private:
		friend Set ;
		friend SPECIALIZATION_TYPE ;
		KEY mKey ;
		ITEM mItem ;
		BOOL mRed ;
		INDEX mUp ;
		INDEX mLeft ;
		INDEX mRight ;

	public:
		inline Node () = delete ;

		inline explicit Node (const KEY &key ,BOOL red ,INDEX up ,INDEX left ,INDEX right) :mKey (std::move (key)) ,mRed (red) ,mUp (up) ,mLeft (left) ,mRight (right) {}

		inline explicit Node (KEY &&key ,BOOL red ,INDEX up ,INDEX left ,INDEX right) :mKey (std::move (key)) ,mRed (red) ,mUp (up) ,mLeft (left) ,mRight (right) {}

		inline explicit Node (const KEY &key ,ITEM &&item ,BOOL red ,INDEX up ,INDEX left ,INDEX right) : mKey (std::move (key)) ,mItem (std::move (item)) ,mRed (red) ,mUp (up) ,mLeft (left) ,mRight (right) {}

		inline explicit Node (KEY &&key ,ITEM &&item ,BOOL red ,INDEX up ,INDEX left ,INDEX right) : mKey (std::move (key)) ,mItem (std::move (item)) ,mRed (red) ,mUp (up) ,mLeft (left) ,mRight (right) {}
	} ;

	using ITEM_TYPE = PACK<KEY ,ITEM> ;

	template <class BASE>
	class Pair {
	public:
		friend Set ;
		friend SPECIALIZATION_TYPE ;
		const KEY &key ;
		CAST_TRAITS_TYPE<ITEM ,BASE> &item ;

	public:
		inline Pair () = delete ;

		inline Pair (const Pair &) = delete ;

		//@info: be careful about key's lifetime
		inline Pair (Pair &&) noexcept = default ;

		inline implicit operator const KEY & () && {
			return key ;
		}

	private:
		inline explicit Pair (BASE &base ,INDEX index) popping : key (base.mSet[index].mKey) ,item (base.mSet[index].mItem) {}
	} ;

	using Pair_BASE = Pair<SPECIALIZATION_TYPE> ;
	using Pair_const_BASE = Pair<const SPECIALIZATION_TYPE> ;

private:
	friend SPECIALIZATION_TYPE ;
	Allocator<Node ,SIZE> mSet ;
	INDEX mRoot ;
	INDEX mTop ;

public:
	Set () {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->clear () ;
	}

	explicit Set (LENGTH len) :Set (ARGVP0 ,len) {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->clear () ;
	}

	void add (const KEY &key ,const ITEM &item) {
		add (std::move (key) ,_COPY_ (item)) ;
	}

	void add (const KEY &key ,ITEM &&item) {
		INDEX ix = static_cast<PTR<SPECIALIZATION_TYPE>> (this)->find (key) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (ix != VAR_NONE)
				continue ;
			ix = mSet.alloc (std::move (key) ,std::move (item) ,TRUE ,VAR_NONE ,VAR_NONE ,VAR_NONE) ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_emplace (mRoot ,ix) ;
			mRoot = mTop ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_insert (ix) ;
		}
		mTop = ix ;
	}

	void add (const ITEM_TYPE &item) {
		add (std::move (item.P1) ,std::move (item.P2)) ;
	}

	void add (KEY &&key ,const ITEM &item) {
		add (std::move (key) ,_COPY_ (item)) ;
	}

	void add (KEY &&key ,ITEM &&item) {
		INDEX ix = static_cast<PTR<SPECIALIZATION_TYPE>> (this)->find (key) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (ix != VAR_NONE)
				continue ;
			ix = mSet.alloc (std::move (key) ,std::move (item) ,TRUE ,VAR_NONE ,VAR_NONE ,VAR_NONE) ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_emplace (mRoot ,ix) ;
			mRoot = mTop ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_insert (ix) ;
		}
		mTop = ix ;
	}

	void add (ITEM_TYPE &&item) {
		add (std::move (item.P1) ,std::move (item.P2)) ;
	}

	template <class _ARG1>
	void appand (const _ARG1 &src) {
		mSet.reserve (src.length ()) ;
		for (auto &&i : src)
			add (i.key ,std::move (i.item)) ;
	}

	template <class _ARG1>
	void appand (_ARG1 &&src) {
		mSet.reserve (src.length ()) ;
		for (auto &&i : src)
			add (i.key ,std::move (i.item)) ;
	}

private:
	explicit Set (const DEF<decltype (ARGVP0)> & ,LENGTH len) :mSet (len) {}
} ;

template <class KEY ,class SIZE>
class Set<KEY ,SPECIALIZATION<void> ,SIZE> {
private:
	using SPECIALIZATION_TYPE = Set<KEY ,void ,SIZE> ;

	class Node {
	private:
		friend Set ;
		friend SPECIALIZATION_TYPE ;
		KEY mKey ;
		BOOL mRed ;
		INDEX mUp ;
		INDEX mLeft ;
		INDEX mRight ;

	public:
		inline Node () = delete ;

		inline explicit Node (const KEY &key ,BOOL red ,INDEX up ,INDEX left ,INDEX right) :mKey (std::move (key)) ,mRed (red) ,mUp (up) ,mLeft (left) ,mRight (right) {}

		inline explicit Node (KEY &&key ,BOOL red ,INDEX up ,INDEX left ,INDEX right) : mKey (std::move (key)) ,mRed (red) ,mUp (up) ,mLeft (left) ,mRight (right) {}
	} ;

	using ITEM_TYPE = PACK<KEY> ;

	template <class BASE>
	class Pair {
	public:
		friend Set ;
		friend SPECIALIZATION_TYPE ;
		const KEY &key ;

	public:
		inline Pair () = delete ;

		inline Pair (const Pair &) = delete ;

		//@info: be careful about key's lifetime
		inline Pair (Pair &&) noexcept = default ;

		inline implicit operator const KEY & () && {
			return key ;
		}

	private:
		inline explicit Pair (BASE &base ,INDEX index) popping : key (base.mSet[index].mKey) {}
	} ;

	using Pair_BASE = Pair<SPECIALIZATION_TYPE> ;
	using Pair_const_BASE = Pair<const SPECIALIZATION_TYPE> ;

private:
	friend SPECIALIZATION_TYPE ;
	Allocator<Node ,SIZE> mSet ;
	INDEX mRoot ;
	INDEX mTop ;

public:
	Set () {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->clear () ;
	}

	explicit Set (LENGTH len) :Set (ARGVP0 ,len) {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->clear () ;
	}

	void add (const KEY &key) {
		INDEX ix = static_cast<PTR<SPECIALIZATION_TYPE>> (this)->find (key) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (ix != VAR_NONE)
				continue ;
			ix = mSet.alloc (std::move (key) ,TRUE ,VAR_NONE ,VAR_NONE ,VAR_NONE) ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_emplace (mRoot ,ix) ;
			mRoot = mTop ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_insert (ix) ;
		}
		mTop = ix ;
	}

	void add (const ITEM_TYPE &item) {
		add (std::move (item.P1)) ;
	}

	void add (KEY &&key) {
		INDEX ix = static_cast<PTR<SPECIALIZATION_TYPE>> (this)->find (key) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (ix != VAR_NONE)
				continue ;
			ix = mSet.alloc (std::move (key) ,TRUE ,VAR_NONE ,VAR_NONE ,VAR_NONE) ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_emplace (mRoot ,ix) ;
			mRoot = mTop ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_insert (ix) ;
		}
		mTop = ix ;
	}

	void add (ITEM_TYPE &&item) {
		add (std::move (item.P1)) ;
	}

	template <class _ARG1>
	void appand (const _ARG1 &src) {
		mSet.reserve (src.length ()) ;
		for (auto &&i : src)
			add (i.key) ;
	}

	template <class _ARG1>
	void appand (_ARG1 &&src) {
		mSet.reserve (src.length ()) ;
		for (auto &&i : src)
			add (i.key) ;
	}

private:
	explicit Set (const DEF<decltype (ARGVP0)> & ,LENGTH len) :mSet (len) {}
} ;

template <class KEY ,class ITEM ,class SIZE>
class Set :private Set<KEY ,SPECIALIZATION<ITEM> ,SIZE> {
private:
	using SPECIALIZATION_BASE = Set<KEY ,SPECIALIZATION<ITEM> ,SIZE> ;
	using Node = typename SPECIALIZATION_BASE::Node ;
	using ITEM_TYPE = typename SPECIALIZATION_BASE::ITEM_TYPE ;
	template <class _ARG1>
	using Pair = typename SPECIALIZATION_BASE::template Pair<_ARG1> ;

private:
	friend SPECIALIZATION_BASE ;
	using SPECIALIZATION_BASE::mSet ;
	using SPECIALIZATION_BASE::mRoot ;
	using SPECIALIZATION_BASE::mTop ;

public:
	Set () = default ;

	explicit Set (LENGTH len) :SPECIALIZATION_BASE (len) {}

	implicit Set (const std::initializer_list<ITEM_TYPE> &right) : Set (right.size ()) {
		for (auto &&i : right)
			add (i) ;
	}

	LENGTH size () const {
		return mSet.size () ;
	}

	LENGTH length () const {
		return mSet.length () ;
	}

	void clear () {
		mSet.clear () ;
		mRoot = VAR_NONE ;
	}

	Pair<Set> get (INDEX index) & {
		return Pair<Set> (*this ,index) ;
	}

	inline Pair<Set> operator[] (INDEX index) & {
		return get (index) ;
	}

	Pair<const Set> get (INDEX index) const & {
		return Pair<const Set> (*this ,index) ;
	}

	inline Pair<const Set> operator[] (INDEX index) const & {
		return get (index) ;
	}

	Pair<Set> get (INDEX) && = delete ;

	inline Pair<Set> operator[] (INDEX) && = delete ;

	INDEX at (const Pair<Set> &item) const {
		return mSet.at (_OFFSET_ (&Node::mKey ,item.key)) ;
	}

	//@info: the same as 'const Pair<const X> &' but acceptable in vs2015
	INDEX at (const typename SPECIALIZATION_BASE::Pair_const_BASE &item) const {
		return mSet.at (_OFFSET_ (&Node::mKey ,item.key)) ;
	}

	INDEX ibegin () const {
		for (INDEX i = 0 ; i < size () ; i++)
			if (mSet.used (i))
				return i ;
		return VAR_NONE ;
	}

	INDEX iend () const {
		return VAR_NONE ;
	}

	INDEX inext (INDEX index) const {
		for (INDEX i = index + 1 ; i < size () ; i++)
			if (mSet.used (i))
				return i ;
		return VAR_NONE ;
	}

	Array<INDEX> range () const {
		Array<INDEX> ret = Array<INDEX> (length ()) ;
		INDEX iw = 0 ;
		for (INDEX i = ibegin () ,ie = iend () ; i != ie ; i = inext (i))
			ret[iw++] = i ;
		return std::move (ret) ;
	}

	BOOL equal (const Set &right) const {
		return equal_each (right ,mRoot ,right.mRoot) ;
	}

	inline BOOL operator== (const Set &right) const {
		return equal (right) ;
	}

	inline BOOL operator!= (const Set &right) const {
		return !equal (right) ;
	}

	using SPECIALIZATION_BASE::add ;

	inline Set &operator<< (const ITEM_TYPE &item) {
		add (std::move (item)) ;
		return *this ;
	}

	inline Set &operator<< (ITEM_TYPE &&item) {
		add (std::move (item)) ;
		return *this ;
	}

	using SPECIALIZATION_BASE::appand ;

	INDEX insert (const KEY &key) popping {
		INDEX ret = find (key) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (ret != VAR_NONE)
				continue ;
			ret = mSet.alloc (std::move (key) ,TRUE ,VAR_NONE ,VAR_NONE ,VAR_NONE) ;
			update_emplace (mRoot ,ret) ;
			mRoot = mTop ;
			update_insert (ret) ;
		}
		mTop = ret ;
		return std::move (ret) ;
	}

	INDEX insert (KEY &&key) popping {
		INDEX ret = find (key) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (ret != VAR_NONE)
				continue ;
			ret = mSet.alloc (std::move (key) ,TRUE ,VAR_NONE ,VAR_NONE ,VAR_NONE) ;
			update_emplace (mRoot ,ret) ;
			mRoot = mTop ;
			update_insert (ret) ;
		}
		mTop = ret ;
		return std::move (ret) ;
	}

	void remove (INDEX index) {
		if (mSet[index].mLeft != VAR_NONE && mSet[index].mRight != VAR_NONE)
			swap (index ,successor_one (index)) ;
		INDEX ix = mSet[index].mLeft ;
		if (ix == VAR_NONE)
			ix = mSet[index].mRight ;
		prev_next (index) = ix ;
		if (ix != VAR_NONE)
			mSet[ix].mUp = mSet[index].mUp ;
		if (!mSet[index].mRed)
			update_remove (ix ,mSet[index].mUp) ;
		mSet.free (index) ;
	}

	INDEX min_one () const {
		for (INDEX i = mRoot ; i != VAR_NONE ; i = mSet[i].mLeft)
			if (mSet[i].mLeft == VAR_NONE)
				return i ;
		return VAR_NONE ;
	}

	INDEX max_one () const {
		for (INDEX i = mRoot ; i != VAR_NONE ; i = mSet[i].mRight)
			if (mSet[i].mRight == VAR_NONE)
				return i ;
		return VAR_NONE ;
	}

	INDEX find (const KEY &key) const {
		INDEX ret = mRoot ;
		while (TRUE) {
			if (ret == VAR_NONE)
				break ;
			const auto r1x = BOOL (key < mSet[ret].mKey) ;
			if (!r1x && !(mSet[ret].mKey < key))
				break ;
			const auto r2x = r1x ? (mSet[ret].mLeft) : (mSet[ret].mRight) ;
			ret = r2x ;
		}
		return std::move (ret) ;
	}

	void erase (const KEY &key) {
		INDEX ix = find (key) ;
		if (ix == VAR_NONE)
			return ;
		remove (ix) ;
	}

	Array<INDEX> esort () const {
		Array<INDEX> ret = Array<INDEX> (length ()) ;
		INDEX iw = 0 ;
		compute_esort (mRoot ,ret ,iw) ;
		_DEBUG_ASSERT_ (iw == ret.length ()) ;
		return std::move (ret) ;
	}

private:
	BOOL equal_each (const Set &right ,INDEX it ,INDEX jt) const {
		if (it == VAR_NONE && jt == VAR_NONE)
			return TRUE ;
		if (it == VAR_NONE || jt == VAR_NONE)
			return FALSE ;
		if (!equal_each (right ,mSet[it].mLeft ,right.mSet[jt].mLeft))
			return FALSE ;
		if (mSet[it].mKey != right.mSet[jt].mKey)
			return FALSE ;
		if (!equal_each (right ,mSet[it].mRight ,right.mSet[jt].mRight))
			return FALSE ;
		return TRUE ;
	}

	void update_emplace (INDEX it ,INDEX jt) {
		_CALL_ONE_ ([&] (BOOL &if_context) {
			if (it != VAR_NONE)
				discard ;
			mTop = jt ;
		} ,[&] (BOOL &if_context) {
			mSet[jt].mUp = it ;
			auto &r1 = (mSet[jt].mKey < mSet[it].mKey) ? (mSet[it].mLeft) : (mSet[it].mRight) ;
			update_emplace (r1 ,jt) ;
			r1 = mTop ;
			mTop = it ;
		}) ;
	}

	void update_insert (INDEX it) {
		INDEX ix = it ;
		while (TRUE) {
			INDEX jx = mSet[ix].mUp ;
			if (jx == VAR_NONE)
				break ;
			if (!mSet[jx].mRed)
				break ;
			const auto r1x = (jx == mSet[mSet[jx].mUp].mLeft) ? (&Set::update_insert_left) : (&Set::update_insert_right) ;
			(this->*r1x) (ix) ;
			ix = mTop ;
		}
		mSet[mRoot].mRed = FALSE ;
	}

	void update_insert_left (INDEX it) {
		INDEX ix = mSet[it].mUp ;
		INDEX iy = mSet[ix].mUp ;
		_CALL_ONE_ ([&] (BOOL &if_context) {
			if (mSet[iy].mRight == VAR_NONE)
				discard ;
			if (!mSet[mSet[iy].mRight].mRed)
				discard ;
			mSet[mSet[iy].mRight].mRed = FALSE ;
			mSet[ix].mRed = FALSE ;
			mSet[iy].mRed = TRUE ;
			mTop = iy ;
		} ,[&] (BOOL &if_context) {
			if (it != mSet[ix].mRight)
				discard ;
			auto &r1 = mSet[iy].mLeft ;
			rotate_left (r1) ;
			r1 = mTop ;
			mSet[it].mRed = FALSE ;
			mSet[iy].mRed = TRUE ;
			auto &r2 = prev_next (iy) ;
			rotate_right (r2) ;
			r2 = mTop ;
			mTop = ix ;
		} ,[&] (BOOL &if_context) {
			if (it != mSet[ix].mLeft)
				discard ;
			mSet[ix].mRed = FALSE ;
			mSet[iy].mRed = TRUE ;
			auto &r3 = prev_next (iy) ;
			rotate_right (r3) ;
			r3 = mTop ;
			mTop = it ;
		}) ;
	}

	void update_insert_right (INDEX it) {
		INDEX ix = mSet[it].mUp ;
		INDEX iy = mSet[ix].mUp ;
		_CALL_ONE_ ([&] (BOOL &if_context) {
			if (mSet[iy].mLeft == VAR_NONE)
				discard ;
			if (!mSet[mSet[iy].mLeft].mRed)
				discard ;
			mSet[mSet[iy].mLeft].mRed = FALSE ;
			mSet[ix].mRed = FALSE ;
			mSet[iy].mRed = TRUE ;
			mTop = iy ;
		} ,[&] (BOOL &if_context) {
			if (it != mSet[ix].mLeft)
				discard ;
			auto &r1 = mSet[iy].mRight ;
			rotate_right (r1) ;
			r1 = mTop ;
			mSet[it].mRed = FALSE ;
			mSet[iy].mRed = TRUE ;
			auto &r2 = prev_next (iy) ;
			rotate_left (r2) ;
			r2 = mTop ;
			mTop = ix ;
		} ,[&] (BOOL &if_context) {
			if (it != mSet[ix].mRight)
				discard ;
			mSet[ix].mRed = FALSE ;
			mSet[iy].mRed = TRUE ;
			auto &r3 = prev_next (iy) ;
			rotate_left (r3) ;
			r3 = mTop ;
			mTop = it ;
		}) ;
	}

	void update_remove (INDEX it ,INDEX jt) {
		INDEX ix = it ;
		INDEX iy = jt ;
		while (TRUE) {
			if (iy == VAR_NONE)
				break ;
			if (ix != VAR_NONE && mSet[ix].mRed)
				break ;
			const auto r1x = (ix == mSet[iy].mLeft) ? (&Set::update_remove_left) : (&Set::update_remove_right) ;
			(this->*r1x) (ix ,iy) ;
			ix = mTop ;
			iy = mSet[ix].mUp ;
		}
		if (ix == VAR_NONE)
			return ;
		mSet[ix].mRed = FALSE ;
	}

	void update_remove_left (INDEX it ,INDEX jt) {
		auto &r1 = mSet[jt].mRight ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (!mSet[r1].mRed)
				continue ;
			mSet[r1].mRed = FALSE ;
			mSet[jt].mRed = TRUE ;
			auto &r2 = prev_next (jt) ;
			rotate_left (r2) ;
			r2 = mTop ;
		}
		const auto r1x = BOOL (mSet[r1].mLeft != VAR_NONE && mSet[mSet[r1].mLeft].mRed) ;
		const auto r2x = BOOL (mSet[r1].mRight != VAR_NONE && mSet[mSet[r1].mRight].mRed) ;
		_CALL_ONE_ ([&] (BOOL &if_context) {
			if (r1x)
				discard ;
			if (r2x)
				discard ;
			mSet[r1].mRed = TRUE ;
			mTop = jt ;
		} ,[&] (BOOL &if_context) {
			if (r2x)
				discard ;
			mSet[mSet[r1].mLeft].mRed = FALSE ;
			mSet[r1].mRed = TRUE ;
			rotate_right (r1) ;
			r1 = mTop ;
			mSet[r1].mRed = mSet[jt].mRed ;
			mSet[jt].mRed = FALSE ;
			mSet[mSet[r1].mRight].mRed = FALSE ;
			auto &r3 = prev_next (jt) ;
			rotate_left (r3) ;
			r3 = mTop ;
			mTop = mRoot ;
		} ,[&] (BOOL &if_context) {
			mSet[r1].mRed = mSet[jt].mRed ;
			mSet[jt].mRed = FALSE ;
			mSet[mSet[r1].mRight].mRed = FALSE ;
			auto &r4 = prev_next (jt) ;
			rotate_left (r4) ;
			r4 = mTop ;
			mTop = mRoot ;
		}) ;
	}

	void update_remove_right (INDEX it ,INDEX jt) {
		auto &r1 = mSet[jt].mLeft ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (!mSet[r1].mRed)
				continue ;
			mSet[r1].mRed = FALSE ;
			mSet[jt].mRed = TRUE ;
			auto &r2 = prev_next (jt) ;
			rotate_right (r2) ;
			r2 = mTop ;
		}
		const auto r1x = BOOL (mSet[r1].mRight != VAR_NONE && mSet[mSet[r1].mRight].mRed) ;
		const auto r2x = BOOL (mSet[r1].mLeft != VAR_NONE && mSet[mSet[r1].mLeft].mRed) ;
		_CALL_ONE_ ([&] (BOOL &if_context) {
			if (r1x)
				discard ;
			if (r2x)
				discard ;
			mSet[r1].mRed = TRUE ;
			mTop = jt ;
		} ,[&] (BOOL &if_context) {
			if (r2x)
				discard ;
			mSet[mSet[r1].mRight].mRed = FALSE ;
			mSet[r1].mRed = TRUE ;
			rotate_left (r1) ;
			r1 = mTop ;
			mSet[r1].mRed = mSet[jt].mRed ;
			mSet[jt].mRed = FALSE ;
			mSet[mSet[r1].mLeft].mRed = FALSE ;
			auto &r3 = prev_next (jt) ;
			rotate_right (r3) ;
			r3 = mTop ;
			mTop = mRoot ;
		} ,[&] (BOOL &if_context) {
			mSet[r1].mRed = mSet[jt].mRed ;
			mSet[jt].mRed = FALSE ;
			mSet[mSet[r1].mLeft].mRed = FALSE ;
			auto &r4 = prev_next (jt) ;
			rotate_right (r4) ;
			r4 = mTop ;
			mTop = mRoot ;
		}) ;
	}

	void rotate_left (INDEX it) {
		INDEX ix = mSet[it].mRight ;
		mSet[it].mRight = mSet[ix].mLeft ;
		if (mSet[ix].mLeft != VAR_NONE)
			mSet[mSet[ix].mLeft].mUp = it ;
		mSet[ix].mLeft = it ;
		mSet[ix].mUp = mSet[it].mUp ;
		mSet[it].mUp = ix ;
		mTop = ix ;
	}

	void rotate_right (INDEX it) {
		INDEX ix = mSet[it].mLeft ;
		mSet[it].mLeft = mSet[ix].mRight ;
		if (mSet[ix].mRight != VAR_NONE)
			mSet[mSet[ix].mRight].mUp = it ;
		mSet[ix].mRight = it ;
		mSet[ix].mUp = mSet[it].mUp ;
		mSet[it].mUp = ix ;
		mTop = ix ;
	}

	INDEX &prev_next (INDEX it) & {
		if (mSet[it].mUp == VAR_NONE)
			return mRoot ;
		if (mSet[mSet[it].mUp].mLeft == it)
			return mSet[mSet[it].mUp].mLeft ;
		return mSet[mSet[it].mUp].mRight ;
	}

	INDEX &prev_next (INDEX) && = delete ;

	INDEX successor_one (INDEX index) const {
		for (INDEX i = mSet[index].mRight ; i != VAR_NONE ; i = mSet[i].mLeft)
			if (mSet[i].mLeft == VAR_NONE)
				return i ;
		return VAR_NONE ;
	}

	void swap (INDEX index1 ,INDEX index2) {
		if (index1 == index2)
			return ;
		auto &r1 = prev_next (index2) ;
		auto &r2 = (mSet[index2].mLeft != VAR_NONE) ? (mSet[mSet[index2].mLeft].mUp) : index1 ;
		auto &r3 = (mSet[index2].mRight != VAR_NONE) ? (mSet[mSet[index2].mRight].mUp) : index1 ;
		auto &r4 = prev_next (index1) ;
		auto &r5 = (mSet[index1].mLeft != VAR_NONE) ? (mSet[mSet[index1].mLeft].mUp) : index2 ;
		auto &r6 = (mSet[index1].mRight != VAR_NONE) ? (mSet[mSet[index1].mRight].mUp) : index2 ;
		r1 = index1 ;
		r2 = index1 ;
		r3 = index1 ;
		r4 = index2 ;
		r5 = index2 ;
		r6 = index2 ;
		_SWAP_ (mSet[index1].mRed ,mSet[index2].mRed) ;
		_SWAP_ (mSet[index1].mUp ,mSet[index2].mUp) ;
		_SWAP_ (mSet[index1].mLeft ,mSet[index2].mLeft) ;
		_SWAP_ (mSet[index1].mRight ,mSet[index2].mRight) ;
	}

	void compute_esort (INDEX it ,Array<INDEX> &out ,INDEX &jt) const {
		if (it == VAR_NONE)
			return ;
		INDEX iw = jt ;
		compute_esort (mSet[it].mLeft ,out ,iw) ;
		out[iw++] = it ;
		compute_esort (mSet[it].mRight ,out ,iw) ;
		jt = iw ;
	}
} ;

template <class KEY ,class ITEM = void ,class SIZE = SAUTO>
class HashSet ;

template <class KEY ,class ITEM ,class SIZE>
class HashSet<KEY ,SPECIALIZATION<ITEM> ,SIZE> {
private:
	using SPECIALIZATION_TYPE = HashSet<KEY ,ITEM ,SIZE> ;

	class Node {
	private:
		friend HashSet ;
		friend SPECIALIZATION_TYPE ;
		KEY mKey ;
		ITEM mItem ;
		FLAG mHash ;
		INDEX mNext ;

	public:
		inline Node () = delete ;

		inline explicit Node (const KEY &key ,FLAG hash ,INDEX next) :mKey (std::move (key)) ,mHash (hash) ,mNext (next) {}

		inline explicit Node (KEY &&key ,FLAG hash ,INDEX next) : mKey (std::move (key)) ,mHash (hash) ,mNext (next) {}

		inline explicit Node (const KEY &key ,ITEM &&item ,FLAG hash ,INDEX next) : mKey (std::move (key)) ,mItem (std::move (item)) ,mHash (hash) ,mNext (next) {}

		inline explicit Node (KEY &&key ,ITEM &&item ,FLAG hash ,INDEX next) : mKey (std::move (key)) ,mItem (std::move (item)) ,mHash (hash) ,mNext (next) {}
	} ;

	using ITEM_TYPE = PACK<KEY ,ITEM> ;

	template <class BASE>
	class Pair {
	public:
		friend HashSet ;
		friend SPECIALIZATION_TYPE ;
		const KEY &key ;
		CAST_TRAITS_TYPE<ITEM ,BASE> &item ;

	public:
		inline Pair () = delete ;

		inline Pair (const Pair &) = delete ;

		//@info: be careful about key's lifetime
		inline Pair (Pair &&) noexcept = default ;

		inline implicit operator const KEY & () && {
			return key ;
		}

	private:
		inline explicit Pair (BASE &base ,INDEX index) popping : key (base.mSet[index].mKey) ,item (base.mSet[index].mItem) {}
	} ;

	using Pair_BASE = Pair<SPECIALIZATION_TYPE> ;
	using Pair_const_BASE = Pair<const SPECIALIZATION_TYPE> ;

private:
	friend SPECIALIZATION_TYPE ;
	Allocator<Node ,SIZE> mSet ;
	Buffer<INDEX ,SIZE> mHead ;
	INDEX mTop ;

public:
	HashSet () {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->clear () ;
	}

	explicit HashSet (LENGTH len) :HashSet (ARGVP0 ,len) {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->clear () ;
	}

	void add (const KEY &key ,const ITEM &item) {
		add (std::move (key) ,_COPY_ (item)) ;
	}

	void add (const KEY &key ,ITEM &&item) {
		INDEX ix = static_cast<PTR<SPECIALIZATION_TYPE>> (this)->find (key) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (ix != VAR_NONE)
				continue ;
			const auto r1x = U::OPERATOR_HASH::invoke (key) ;
			ix = mSet.alloc (std::move (key) ,std::move (item) ,r1x ,VAR_NONE) ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_resize (ix) ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_insert (ix) ;
		}
		mTop = ix ;
	}

	void add (const ITEM_TYPE &item) {
		add (std::move (item.P1) ,std::move (item.P2)) ;
	}

	void add (KEY &&key ,const ITEM &item) {
		add (std::move (key) ,_COPY_ (item)) ;
	}

	void add (KEY &&key ,ITEM &&item) {
		INDEX ix = static_cast<PTR<SPECIALIZATION_TYPE>> (this)->find (key) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (ix != VAR_NONE)
				continue ;
			const auto r1x = U::OPERATOR_HASH::invoke (key) ;
			ix = mSet.alloc (std::move (key) ,std::move (item) ,r1x ,VAR_NONE) ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_resize (ix) ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_insert (ix) ;
		}
		mTop = ix ;
	}

	void add (ITEM_TYPE &&item) {
		add (std::move (item.P1) ,std::move (item.P2)) ;
	}

	template <class _ARG1>
	void appand (const _ARG1 &src) {
		mSet.reserve (src.length ()) ;
		for (auto &&i : src)
			add (i.key ,std::move (i.item)) ;
	}

	template <class _ARG1>
	void appand (_ARG1 &&src) {
		mSet.reserve (src.length ()) ;
		for (auto &&i : src)
			add (i.key ,std::move (i.item)) ;
	}

private:
	explicit HashSet (const DEF<decltype (ARGVP0)> & ,LENGTH len) :mSet (len) ,mHead (len) {}

private:
	BOOL equal_each (const HashSet &right ,INDEX it) const {
		INDEX ix = right.find (mSet[it].mKey) ;
		if (ix == VAR_NONE)
			return FALSE ;
		if (mSet[it].mItem != right.mSet[ix].mItem)
			return FALSE ;
		return TRUE ;
	}
} ;

template <class KEY ,class SIZE>
class HashSet<KEY ,SPECIALIZATION<void> ,SIZE> {
private:
	using SPECIALIZATION_TYPE = HashSet<KEY ,void ,SIZE> ;

	class Node {
	private:
		friend HashSet ;
		friend SPECIALIZATION_TYPE ;
		KEY mKey ;
		FLAG mHash ;
		INDEX mNext ;

	public:
		inline Node () = delete ;

		inline explicit Node (const KEY &key ,FLAG hash ,INDEX next) :mKey (std::move (key)) ,mHash (hash) ,mNext (next) {}

		inline explicit Node (KEY &&key ,FLAG hash ,INDEX next) : mKey (std::move (key)) ,mHash (hash) ,mNext (next) {}
	} ;

	using ITEM_TYPE = PACK<KEY> ;

	template <class BASE>
	class Pair {
	public:
		friend HashSet ;
		friend SPECIALIZATION_TYPE ;
		const KEY &key ;

	public:
		inline Pair () = delete ;

		inline Pair (const Pair &) = delete ;

		//@info: be careful about key's lifetime
		inline Pair (Pair &&) noexcept = default ;

		inline implicit operator const KEY & () && {
			return key ;
		}

	private:
		inline explicit Pair (BASE &base ,INDEX index) popping : key (base.mSet[index].mKey) {}
	} ;

	using Pair_BASE = Pair<SPECIALIZATION_TYPE> ;
	using Pair_const_BASE = Pair<const SPECIALIZATION_TYPE> ;

private:
	friend SPECIALIZATION_TYPE ;
	Allocator<Node ,SIZE> mSet ;
	Buffer<INDEX ,SIZE> mHead ;
	INDEX mTop ;

public:
	HashSet () {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->clear () ;
	}

	explicit HashSet (LENGTH len) :HashSet (ARGVP0 ,len) {
		static_cast<PTR<SPECIALIZATION_TYPE>> (this)->clear () ;
	}

	void add (const KEY &key) {
		INDEX ix = static_cast<PTR<SPECIALIZATION_TYPE>> (this)->find (key) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (ix != VAR_NONE)
				continue ;
			const auto r1x = U::OPERATOR_HASH::invoke (key) ;
			ix = mSet.alloc (std::move (key) ,r1x ,VAR_NONE) ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_resize (ix) ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_insert (ix) ;
		}
		mTop = ix ;
	}

	void add (const ITEM_TYPE &item) {
		add (std::move (item.P1)) ;
	}

	void add (KEY &&key) {
		INDEX ix = static_cast<PTR<SPECIALIZATION_TYPE>> (this)->find (key) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (ix != VAR_NONE)
				continue ;
			const auto r1x = U::OPERATOR_HASH::invoke (key) ;
			ix = mSet.alloc (std::move (key) ,r1x ,VAR_NONE) ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_resize (ix) ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_insert (ix) ;
		}
		mTop = ix ;
	}

	void add (ITEM_TYPE &&item) {
		add (std::move (item.P1) ,std::move (item.P2)) ;
	}

	template <class _ARG1>
	void appand (const _ARG1 &src) {
		mSet.reserve (src.length ()) ;
		for (auto &&i : src)
			add (i.key) ;
	}

	template <class _ARG1>
	void appand (_ARG1 &&src) {
		mSet.reserve (src.length ()) ;
		for (auto &&i : src)
			add (i.key) ;
	}

private:
	explicit HashSet (const DEF<decltype (ARGVP0)> & ,LENGTH len) :mSet (len) ,mHead (len) {}

private:
	BOOL equal_each (const HashSet &right ,INDEX it) const {
		INDEX ix = right.find (mSet[it].mKey) ;
		if (ix == VAR_NONE)
			return FALSE ;
		return TRUE ;
	}
} ;

template <class KEY ,class ITEM ,class SIZE>
class HashSet :private HashSet<KEY ,SPECIALIZATION<ITEM> ,SIZE> {
private:
	using SPECIALIZATION_BASE = HashSet<KEY ,SPECIALIZATION<ITEM> ,SIZE> ;
	using Node = typename SPECIALIZATION_BASE::Node ;
	using ITEM_TYPE = typename SPECIALIZATION_BASE::ITEM_TYPE ;
	template <class _ARG1>
	using Pair = typename SPECIALIZATION_BASE::template Pair<_ARG1> ;

private:
	friend SPECIALIZATION_BASE ;
	using SPECIALIZATION_BASE::mSet ;
	using SPECIALIZATION_BASE::mHead ;
	using SPECIALIZATION_BASE::mTop ;

public:
	HashSet () = default ;

	explicit HashSet (LENGTH len) :SPECIALIZATION_BASE (len) {}

	implicit HashSet (const std::initializer_list<ITEM_TYPE> &right) : HashSet (right.size ()) {
		for (auto &&i : right)
			add (i) ;
	}

	LENGTH size () const {
		return mSet.size () ;
	}

	LENGTH length () const {
		return mSet.length () ;
	}

	void clear () {
		mSet.clear () ;
		_MEMFILL_ (mHead.self ,mHead.size () ,VAR_NONE) ;
	}

	Pair<HashSet> get (INDEX index) & {
		return Pair<HashSet> (*this ,index) ;
	}

	inline Pair<HashSet> operator[] (INDEX index) & {
		return get (index) ;
	}

	Pair<const HashSet> get (INDEX index) const & {
		return Pair<const HashSet> (*this ,index) ;
	}

	inline Pair<const HashSet> operator[] (INDEX index) const & {
		return get (index) ;
	}

	Pair<HashSet> get (INDEX) && = delete ;

	inline Pair<HashSet> operator[] (INDEX) && = delete ;

	INDEX at (const Pair<HashSet> &item) const {
		return mSet.at (_OFFSET_ (&Node::mKey ,item.key)) ;
	}

	//@info: the same as 'const Pair<const X> &' but acceptable in vs2015
	INDEX at (const typename SPECIALIZATION_BASE::Pair_const_BASE &item) const {
		return mSet.at (_OFFSET_ (&Node::mKey ,item.key)) ;
	}

	INDEX ibegin () const {
		for (INDEX i = 0 ; i < size () ; i++)
			if (mSet.used (i))
				return i ;
		return VAR_NONE ;
	}

	INDEX iend () const {
		return VAR_NONE ;
	}

	INDEX inext (INDEX index) const {
		for (INDEX i = index + 1 ; i < size () ; i++)
			if (mSet.used (i))
				return i ;
		return VAR_NONE ;
	}

	Array<INDEX> range () const {
		Array<INDEX> ret = Array<INDEX> (length ()) ;
		INDEX iw = 0 ;
		for (INDEX i = ibegin () ,ie = iend () ; i != ie ; i = inext (i))
			ret[iw++] = i ;
		return std::move (ret) ;
	}

	BOOL equal (const HashSet &right) const {
		if (length () != right.length ())
			return FALSE ;
		for (INDEX i = ibegin () ,ie = iend () ; i != ie ; i = inext (i))
			if (!equal_each (right ,i))
				return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const HashSet &right) const {
		return equal (right) ;
	}

	inline BOOL operator!= (const HashSet &right) const {
		return !equal (right) ;
	}

	using SPECIALIZATION_BASE::add ;

	inline HashSet &operator<< (const ITEM_TYPE &item) {
		add (std::move (item)) ;
		return *this ;
	}

	inline HashSet &operator<< (ITEM_TYPE &&item) {
		add (std::move (item)) ;
		return *this ;
	}

	using SPECIALIZATION_BASE::appand ;

	INDEX insert (const KEY &key) popping {
		INDEX ret = find (key) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (ret != VAR_NONE)
				continue ;
			const auto r1x = U::OPERATOR_HASH::invoke (key) ;
			ret = mSet.alloc (std::move (key) ,r1x ,VAR_NONE) ;
			update_resize (ret) ;
			update_insert (ret) ;
		}
		mTop = ret ;
		return std::move (ret) ;
	}

	INDEX insert (KEY &&key) popping {
		INDEX ret = find (key) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (ret != VAR_NONE)
				continue ;
			const auto r1x = U::OPERATOR_HASH::invoke (key) ;
			ret = mSet.alloc (std::move (key) ,r1x ,VAR_NONE) ;
			update_resize (ret) ;
			update_insert (ret) ;
		}
		mTop = ret ;
		return std::move (ret) ;
	}

	void remove (INDEX index) {
		prev_next (index) = mSet[index].mNext ;
		mSet.free (index) ;
	}

	INDEX find (const KEY &key) const {
		INDEX ret = VAR_NONE ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (size () == 0)
				continue ;
			const auto r1x = U::OPERATOR_HASH::invoke (key) ;
			_DEBUG_ASSERT_ (r1x >= 0) ;
			ret = mHead[r1x % mHead.size ()] ;
			while (TRUE) {
				if (ret == VAR_NONE)
					break ;
				if (mSet[ret].mHash == r1x && mSet[ret].mKey == key)
					break ;
				ret = mSet[ret].mNext ;
			}
		}
		return std::move (ret) ;
	}

	void erase (const KEY &key) {
		INDEX ix = find (key) ;
		if (ix == VAR_NONE)
			return ;
		remove (ix) ;
	}

private:
	using SPECIALIZATION_BASE::equal_each ;

	void update_resize (INDEX it) {
		if (mHead.size () == mSet.size ())
			return ;
		auto rax = mHead.expand (mSet.size ()) ;
		_MEMFILL_ (rax.self ,rax.size () ,VAR_NONE) ;
		for (INDEX i = 0 ; i < mSet.size () ; i++) {
			if (i == it)
				continue ;
			if (!mSet.used (i))
				continue ;
			INDEX ix = mSet[i].mHash % rax.size () ;
			mSet[i].mNext = rax[ix] ;
			rax[ix] = i ;
		}
		mHead.swap (rax) ;
	}

	void update_insert (INDEX it) {
		INDEX ix = mSet[it].mHash % mHead.size () ;
		mSet[it].mNext = mHead[ix] ;
		mHead[ix] = it ;
	}

	INDEX &prev_next (INDEX it) & {
		INDEX ix = mSet[it].mHash % mHead.size () ;
		if (mHead[ix] == it)
			return mHead[ix] ;
		ix = mHead[ix] ;
		while (TRUE) {
			if (mSet[ix].mNext == VAR_NONE)
				break ;
			if (mSet[ix].mNext == it)
				break ;
			ix = mSet[ix].mNext ;
		}
		_DEBUG_ASSERT_ (mSet[ix].mNext == it) ;
		return mSet[ix].mNext ;
	}

	INDEX &prev_next (INDEX) && = delete ;
} ;

template <class KEY ,class ITEM = void ,class SIZE = SAUTO>
class SoftSet ;

template <class KEY ,class ITEM ,class SIZE>
class SoftSet<KEY ,SPECIALIZATION<ITEM> ,SIZE> {
private:
	using SPECIALIZATION_TYPE = SoftSet<KEY ,ITEM ,SIZE> ;

	class Node {
	private:
		friend SoftSet ;
		friend SPECIALIZATION_TYPE ;
		KEY mKey ;
		ITEM mItem ;
		LENGTH mWeight ;
		INDEX mLeft ;
		INDEX mRight ;
		INDEX mNext ;

	public:
		inline Node () = delete ;

		inline explicit Node (const KEY &key ,LENGTH weight ,INDEX left ,INDEX right ,INDEX next) :mKey (std::move (key)) ,mWeight (weight) ,mLeft (left) ,mRight (right) ,mNext (next) {}

		inline explicit Node (KEY &&key ,LENGTH weight ,INDEX left ,INDEX right ,INDEX next) : mKey (std::move (key)) ,mWeight (weight) ,mLeft (left) ,mRight (right) ,mNext (next) {}

		inline explicit Node (const KEY &key ,ITEM &&item ,LENGTH weight ,INDEX left ,INDEX right ,INDEX next) : mKey (std::move (key)) ,mItem (std::move (item)) ,mWeight (weight) ,mLeft (left) ,mRight (right) ,mNext (next) {}

		inline explicit Node (KEY &&key ,ITEM &&item ,LENGTH weight ,INDEX left ,INDEX right ,INDEX next) : mKey (std::move (key)) ,mItem (std::move (item)) ,mWeight (weight) ,mLeft (left) ,mRight (right) ,mNext (next) {}
	} ;

	using ITEM_TYPE = PACK<KEY ,ITEM> ;

	template <class BASE>
	class Pair {
	public:
		friend SoftSet ;
		friend SPECIALIZATION_TYPE ;
		const KEY &key ;
		CAST_TRAITS_TYPE<ITEM ,BASE> &item ;

	public:
		inline Pair () = delete ;

		inline Pair (const Pair &) = delete ;

		//@info: be careful about key's lifetime
		inline Pair (Pair &&) noexcept = default ;

		inline implicit operator const KEY & () && {
			return key ;
		}

	private:
		inline explicit Pair (BASE &base ,INDEX index) popping : key (base.mSet.self[index].mKey) ,item (base.mSet.self[index].mItem) {}
	} ;

	using Pair_BASE = Pair<SPECIALIZATION_TYPE> ;
	using Pair_const_BASE = Pair<const SPECIALIZATION_TYPE> ;

	class Holder {
	private:
		friend SoftSet ;
		friend SPECIALIZATION_TYPE ;
		SharedRef<Allocator<Node ,SIZE>> mHeap ;
		LENGTH mLength ;
		INDEX mFirst ;
		INDEX mLast ;
		INDEX mRoot ;
		INDEX mTop ;
	} ;

private:
	friend SPECIALIZATION_TYPE ;
	SharedRef<Holder> mThis ;
	PhanRef<Allocator<Node ,SIZE>> mSet ;

public:
	SoftSet () = default ;

	explicit SoftSet (LENGTH len) {
		mThis = SharedRef<Holder>::make () ;
		mThis->mHeap = SharedRef<Allocator<Node ,SIZE>>::make (len) ;
		mThis->mLength = 0 ;
		mThis->mFirst = VAR_NONE ;
		mThis->mLast = VAR_NONE ;
		mThis->mRoot = VAR_NONE ;
		mSet = PhanRef<Allocator<Node ,SIZE>>::make (mThis->mHeap.self) ;
	}

	void add (const KEY &key ,const ITEM &item) {
		add (std::move (key) ,_COPY_ (item)) ;
	}

	void add (const KEY &key ,ITEM &&item) {
		_DEBUG_ASSERT_ (mThis.exist ()) ;
		INDEX ix = static_cast<PTR<SPECIALIZATION_TYPE>> (this)->find (key) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (ix != VAR_NONE)
				continue ;
			ix = mSet->alloc (std::move (key) ,std::move (item) ,1 ,VAR_NONE ,VAR_NONE ,VAR_NONE) ;
			auto &r1 = (mThis->mLast != VAR_NONE) ? (mSet.self[mThis->mLast].mNext) : (mThis->mFirst) ;
			r1 = ix ;
			mThis->mLast = ix ;
			mThis->mLength++ ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_insert (mThis->mRoot) ;
			mThis->mRoot = mThis->mTop ;
		}
		mThis->mTop = ix ;
	}

	void add (const ITEM_TYPE &item) {
		add (std::move (item.P1) ,std::move (item.P2)) ;
	}

	void add (KEY &&key ,const ITEM &item) {
		add (std::move (key) ,_COPY_ (item)) ;
	}

	void add (KEY &&key ,ITEM &&item) {
		_DEBUG_ASSERT_ (mThis.exist ()) ;
		INDEX ix = static_cast<PTR<SPECIALIZATION_TYPE>> (this)->find (key) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (ix != VAR_NONE)
				continue ;
			ix = mSet->alloc (std::move (key) ,std::move (item) ,1 ,VAR_NONE ,VAR_NONE ,VAR_NONE) ;
			auto &r1 = (mThis->mLast != VAR_NONE) ? (mSet.self[mThis->mLast].mNext) : (mThis->mFirst) ;
			r1 = ix ;
			mThis->mLast = ix ;
			mThis->mLength++ ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_insert (mThis->mRoot) ;
			mThis->mRoot = mThis->mTop ;
		}
		mThis->mTop = ix ;
	}

	void add (ITEM_TYPE &&item) {
		add (std::move (item.P1) ,std::move (item.P2)) ;
	}

	template <class _ARG1>
	void appand (const _ARG1 &src) {
		_DEBUG_ASSERT_ (mThis.exist ()) ;
		mSet->reserve (src.length ()) ;
		for (auto &&i : src)
			add (i.key ,std::move (i.item)) ;
	}

	template <class _ARG1>
	void appand (_ARG1 &&src) {
		_DEBUG_ASSERT_ (mThis.exist ()) ;
		mSet->reserve (src.length ()) ;
		for (auto &&i : src)
			add (i.key ,std::move (i.item)) ;
	}
} ;

template <class KEY ,class SIZE>
class SoftSet<KEY ,SPECIALIZATION<void> ,SIZE> {
private:
	using SPECIALIZATION_TYPE = SoftSet<KEY ,void ,SIZE> ;

	class Node {
	private:
		friend SoftSet ;
		friend SPECIALIZATION_TYPE ;
		KEY mKey ;
		LENGTH mWeight ;
		INDEX mLeft ;
		INDEX mRight ;
		INDEX mNext ;

	public:
		inline Node () = delete ;

		inline explicit Node (const KEY &key ,LENGTH weight ,INDEX left ,INDEX right ,INDEX next) :mKey (std::move (key)) ,mWeight (weight) ,mLeft (left) ,mRight (right) ,mNext (next) {}

		inline explicit Node (KEY &&key ,LENGTH weight ,INDEX left ,INDEX right ,INDEX next) : mKey (std::move (key)) ,mWeight (weight) ,mLeft (left) ,mRight (right) ,mNext (next) {}
	} ;

	using ITEM_TYPE = PACK<KEY> ;

	template <class BASE>
	class Pair {
	public:
		friend SoftSet ;
		friend SPECIALIZATION_TYPE ;
		const KEY &key ;

	public:
		inline Pair () = delete ;

		inline Pair (const Pair &) = delete ;

		//@info: be careful about key's lifetime
		inline Pair (Pair &&) noexcept = default ;

		inline implicit operator const KEY & () && {
			return key ;
		}

	private:
		inline explicit Pair (BASE &base ,INDEX index) popping : key (base.mSet.self[index].mKey) {}
	} ;

	using Pair_BASE = Pair<SPECIALIZATION_TYPE> ;
	using Pair_const_BASE = Pair<const SPECIALIZATION_TYPE> ;

	class Holder {
	private:
		friend SoftSet ;
		friend SPECIALIZATION_TYPE ;
		SharedRef<Allocator<Node ,SIZE>> mHeap ;
		LENGTH mLength ;
		INDEX mFirst ;
		INDEX mLast ;
		INDEX mRoot ;
		INDEX mTop ;
	} ;

private:
	friend SPECIALIZATION_TYPE ;
	SharedRef<Holder> mThis ;
	PhanRef<Allocator<Node ,SIZE>> mSet ;

public:
	SoftSet () = default ;

	explicit SoftSet (LENGTH len) {
		mThis = SharedRef<Holder>::make () ;
		mThis->mHeap = SharedRef<Allocator<Node ,SIZE>>::make (len) ;
		mThis->mLength = 0 ;
		mThis->mFirst = VAR_NONE ;
		mThis->mLast = VAR_NONE ;
		mThis->mRoot = VAR_NONE ;
		mSet = PhanRef<Allocator<Node ,SIZE>>::make (mThis->mHeap.self) ;
	}

	void add (const KEY &key) {
		_DEBUG_ASSERT_ (mThis.exist ()) ;
		INDEX ix = static_cast<PTR<SPECIALIZATION_TYPE>> (this)->find (key) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (ix != VAR_NONE)
				continue ;
			ix = mSet->alloc (std::move (key) ,1 ,VAR_NONE ,VAR_NONE ,VAR_NONE) ;
			auto &r1 = (mThis->mLast != VAR_NONE) ? (mSet.self[mThis->mLast].mNext) : (mThis->mFirst) ;
			r1 = ix ;
			mThis->mLast = ix ;
			mThis->mLength++ ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_insert (mThis->mRoot) ;
			mThis->mRoot = mThis->mTop ;
		}
		mThis->mTop = ix ;
	}

	void add (const ITEM_TYPE &item) {
		add (std::move (item.P1)) ;
	}

	void add (KEY &&key) {
		_DEBUG_ASSERT_ (mThis.exist ()) ;
		INDEX ix = static_cast<PTR<SPECIALIZATION_TYPE>> (this)->find (key) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (ix != VAR_NONE)
				continue ;
			ix = mSet->alloc (std::move (key) ,1 ,VAR_NONE ,VAR_NONE ,VAR_NONE) ;
			auto &r1 = (mThis->mLast != VAR_NONE) ? (mSet.self[mThis->mLast].mNext) : (mThis->mFirst) ;
			r1 = ix ;
			mThis->mLast = ix ;
			mThis->mLength++ ;
			static_cast<PTR<SPECIALIZATION_TYPE>> (this)->update_insert (mThis->mRoot) ;
			mThis->mRoot = mThis->mTop ;
		}
		mThis->mTop = ix ;
	}

	void add (ITEM_TYPE &&item) {
		add (std::move (item.P1)) ;
	}

	template <class _ARG1>
	void appand (const _ARG1 &src) {
		_DEBUG_ASSERT_ (mThis.exist ()) ;
		mSet->reserve (src.length ()) ;
		for (auto &&i : src)
			add (i.key) ;
	}

	template <class _ARG1>
	void appand (_ARG1 &&src) {
		_DEBUG_ASSERT_ (mThis.exist ()) ;
		mSet->reserve (src.length ()) ;
		for (auto &&i : src)
			add (i.key) ;
	}
} ;

template <class KEY ,class ITEM ,class SIZE>
class SoftSet :private SoftSet<KEY ,SPECIALIZATION<ITEM> ,SIZE> {
private:
	using SPECIALIZATION_BASE = SoftSet<KEY ,SPECIALIZATION<ITEM> ,SIZE> ;
	using Node = typename SPECIALIZATION_BASE::Node ;
	using ITEM_TYPE = typename SPECIALIZATION_BASE::ITEM_TYPE ;
	template <class _ARG1>
	using Pair = typename SPECIALIZATION_BASE::template Pair<_ARG1> ;
	using Holder = typename SPECIALIZATION_BASE::Holder ;

private:
	friend SPECIALIZATION_BASE ;
	using SPECIALIZATION_BASE::mThis ;
	using SPECIALIZATION_BASE::mSet ;

public:
	SoftSet () = default ;

	explicit SoftSet (LENGTH len) :SPECIALIZATION_BASE (len) {}

	LENGTH capacity () const {
		if (!mThis.exist ())
			return 0 ;
		return mSet->size () ;
	}

	LENGTH size () const {
		if (!mThis.exist ())
			return 0 ;
		return mSet->size () - (mSet->length () - mThis->mLength) ;
	}

	LENGTH length () const {
		if (!mThis.exist ())
			return 0 ;
		return mThis->mLength ;
	}

	void reset () {
		if (!mThis.exist ())
			return ;
		auto rax = SharedRef<Holder>::make () ;
		rax->mHeap = mThis->mHeap ;
		rax->mLength = 0 ;
		rax->mFirst = VAR_NONE ;
		rax->mLast = VAR_NONE ;
		rax->mRoot = VAR_NONE ;
		mThis = std::move (rax) ;
		mSet = PhanRef<Allocator<Node ,SIZE>>::make (mThis->mHeap.self) ;
	}

	SoftSet copy () popping {
		SoftSet ret ;
		ret.mThis = mThis ;
		ret.mSet = PhanRef<Allocator<Node ,SIZE>>::make (mSet) ;
		return std::move (ret) ;
	}

	Pair<SoftSet> get (INDEX index) & {
		_DEBUG_ASSERT_ (mThis.exist ()) ;
		return Pair<SoftSet> (*this ,index) ;
	}

	inline Pair<SoftSet> operator[] (INDEX index) & {
		return get (index) ;
	}

	Pair<const SoftSet> get (INDEX index) const & {
		_DEBUG_ASSERT_ (mThis.exist ()) ;
		return Pair<const SoftSet> (*this ,index) ;
	}

	inline Pair<const SoftSet> operator[] (INDEX index) const & {
		return get (index) ;
	}

	Pair<SoftSet> get (INDEX) && = delete ;

	inline Pair<SoftSet> operator[] (INDEX) && = delete ;

	INDEX at (const Pair<SoftSet> &item) const {
		return mSet->at (_OFFSET_ (&Node::mKey ,item.key)) ;
	}

	//@info: the same as 'const Pair<const X> &' but acceptable in vs2015
	INDEX at (const typename SPECIALIZATION_BASE::Pair_const_BASE &item) const {
		return mSet->at (_OFFSET_ (&Node::mKey ,item.key)) ;
	}

	INDEX ibegin () const {
		if (!mThis.exist ())
			return VAR_NONE ;
		return mThis->mFirst ;
	}

	INDEX iend () const {
		return VAR_NONE ;
	}

	INDEX inext (INDEX index) const {
		return mSet.self[index].mNext ;
	}

	Array<INDEX> range () const {
		Array<INDEX> ret = Array<INDEX> (length ()) ;
		INDEX iw = 0 ;
		for (INDEX i = ibegin () ,ie = iend () ; i != ie ; i = inext (i))
			ret[iw++] = i ;
		return std::move (ret) ;
	}

	BOOL equal (const SoftSet &right) const {
		if (!mThis.exist () && !right.mThis.exist ())
			return TRUE ;
		if (!mThis.exist () || !right.mThis.exist ())
			return FALSE ;
		if (!equal_each (right ,mThis->mRoot ,right.mThis->mRoot))
			return FALSE ;
		return TRUE ;
	}

	inline BOOL operator== (const SoftSet &right) const {
		return equal (right) ;
	}

	inline BOOL operator!= (const SoftSet &right) const {
		return !equal (right) ;
	}

	using SPECIALIZATION_BASE::add ;

	inline SoftSet &operator<< (const ITEM_TYPE &item) {
		add (std::move (item)) ;
		return *this ;
	}

	inline SoftSet &operator<< (ITEM_TYPE &&item) {
		add (std::move (item)) ;
		return *this ;
	}

	using SPECIALIZATION_BASE::appand ;

	INDEX insert (const KEY &key) popping {
		_DEBUG_ASSERT_ (mThis.exist ()) ;
		INDEX ret = find (key) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (ret != VAR_NONE)
				continue ;
			ret = mSet->alloc (std::move (key) ,1 ,VAR_NONE ,VAR_NONE ,VAR_NONE) ;
			auto &r1 = (mThis->mLast != VAR_NONE) ? (mSet.self[mThis->mLast].mNext) : (mThis->mFirst) ;
			r1 = ret ;
			mThis->mLast = ret ;
			mThis->mLength++ ;
			update_insert (mThis->mRoot) ;
			mThis->mRoot = mThis->mTop ;
		}
		mThis->mTop = ret ;
		return std::move (ret) ;
	}

	INDEX insert (KEY &&key) popping {
		_DEBUG_ASSERT_ (mThis.exist ()) ;
		INDEX ret = find (key) ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (ret != VAR_NONE)
				continue ;
			ret = mSet->alloc (std::move (key) ,1 ,VAR_NONE ,VAR_NONE ,VAR_NONE) ;
			auto &r1 = (mThis->mLast != VAR_NONE) ? (mSet.self[mThis->mLast].mNext) : (mThis->mFirst) ;
			r1 = ret ;
			mThis->mLast = ret ;
			mThis->mLength++ ;
			update_insert (mThis->mRoot) ;
			mThis->mRoot = mThis->mTop ;
		}
		mThis->mTop = ret ;
		return std::move (ret) ;
	}

	INDEX min_one () const {
		if (!mThis.exist ())
			return VAR_NONE ;
		for (INDEX i = mThis->mRoot ; i != VAR_NONE ; i = mSet.self[i].mLeft)
			if (mSet.self[i].mLeft == VAR_NONE)
				return i ;
		return VAR_NONE ;
	}

	INDEX max_one () const {
		if (!mThis.exist ())
			return VAR_NONE ;
		for (INDEX i = mThis->mRoot ; i != VAR_NONE ; i = mSet.self[i].mRight)
			if (mSet.self[i].mRight == VAR_NONE)
				return i ;
		return VAR_NONE ;
	}

	INDEX find (const KEY &key) const {
		INDEX ret = VAR_NONE ;
		if (mThis.exist ())
			ret = mThis->mRoot ;
		while (TRUE) {
			if (ret == VAR_NONE)
				break ;
			const auto r1x = BOOL (key < mSet.self[ret].mKey) ;
			if (!r1x && !(mSet.self[ret].mKey < key))
				break ;
			const auto r2x = r1x ? (mSet.self[ret].mLeft) : (mSet.self[ret].mRight) ;
			ret = r2x ;
		}
		return std::move (ret) ;
	}

	void clean () {
		if (!mThis.exist ())
			return ;
		mSet->clean () ;
	}

private:
	BOOL equal_each (const SoftSet &right ,INDEX it ,INDEX jt) const {
		if (it == VAR_NONE && jt == VAR_NONE)
			return TRUE ;
		if (it == VAR_NONE || jt == VAR_NONE)
			return FALSE ;
		if (!equal_each (right ,mSet.self[it].mLeft ,right.mSet.self[jt].mLeft))
			return FALSE ;
		if (mSet.self[it].mKey != right.mSet.self[jt].mKey)
			return FALSE ;
		if (!equal_each (right ,mSet.self[it].mRight ,right.mSet.self[jt].mRight))
			return FALSE ;
		return TRUE ;
	}

	void update_insert (INDEX it) {
		INDEX ix = it ;
		_CALL_ONE_ ([&] (BOOL &if_context) {
			if (ix != VAR_NONE)
				discard ;
			mThis->mTop = mThis->mLast ;
		} ,[&] (BOOL &if_context) {
			mSet.self[ix].mWeight++ ;
			const auto r1x = BOOL (mSet.self[mThis->mLast].mKey < mSet.self[ix].mKey) ;
			auto &r2 = r1x ? (mSet.self[ix].mLeft) : (mSet.self[ix].mRight) ;
			update_insert (r2) ;
			r2 = mThis->mTop ;
			const auto r2x = r1x ? (&SoftSet::update_insert_left) : (&SoftSet::update_insert_right) ;
			(this->*r2x) (ix) ;
			ix = mThis->mTop ;
			mThis->mTop = ix ;
		}) ;
	}

	void update_insert_left (INDEX it) {
		INDEX ix = it ;
		mThis->mTop = ix ;
		if (mSet.self[ix].mLeft == VAR_NONE)
			return ;
		const auto r1x = node_weight (mSet.self[ix].mRight) ;
		const auto r2x = node_weight (mSet.self[mSet.self[ix].mLeft].mLeft) ;
		const auto r3x = node_weight (mSet.self[mSet.self[ix].mLeft].mRight) ;
		mThis->mTop = ix ;
		if (r1x >= r2x && r1x >= r3x)
			return ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (r1x < r2x)
				continue ;
			auto &r1 = mSet.self[ix].mLeft ;
			rotate_left (r1) ;
			r1 = mThis->mTop ;
		}
		rotate_right (ix) ;
		ix = mThis->mTop ;
		auto &r2 = mSet.self[ix].mLeft ;
		update_insert_left (r2) ;
		r2 = mThis->mTop ;
		auto &r3 = mSet.self[ix].mRight ;
		update_insert_right (r3) ;
		r3 = mThis->mTop ;
		update_insert_left (ix) ;
		ix = mThis->mTop ;
		update_insert_right (ix) ;
		ix = mThis->mTop ;
		mThis->mTop = ix ;
	}

	void update_insert_right (INDEX it) {
		INDEX ix = it ;
		mThis->mTop = ix ;
		if (mSet.self[ix].mRight == VAR_NONE)
			return ;
		const auto r1x = node_weight (mSet.self[ix].mLeft) ;
		const auto r2x = node_weight (mSet.self[mSet.self[ix].mRight].mRight) ;
		const auto r3x = node_weight (mSet.self[mSet.self[ix].mRight].mLeft) ;
		mThis->mTop = ix ;
		if (r1x >= r2x && r1x >= r3x)
			return ;
		for (FOR_ONCE_DO_WHILE_FALSE) {
			if (r1x < r2x)
				continue ;
			auto &r1 = mSet.self[ix].mRight ;
			rotate_right (r1) ;
			r1 = mThis->mTop ;
		}
		rotate_left (ix) ;
		ix = mThis->mTop ;
		auto &r2 = mSet.self[ix].mLeft ;
		update_insert_left (r2) ;
		r2 = mThis->mTop ;
		auto &r3 = mSet.self[ix].mRight ;
		update_insert_right (r3) ;
		r3 = mThis->mTop ;
		update_insert_left (ix) ;
		ix = mThis->mTop ;
		update_insert_right (ix) ;
		ix = mThis->mTop ;
		mThis->mTop = ix ;
	}

	void rotate_left (INDEX it) {
		INDEX ix = mSet.self[it].mRight ;
		mSet.self[it].mRight = mSet.self[ix].mLeft ;
		mSet.self[ix].mLeft = it ;
		mSet.self[ix].mWeight = mSet.self[it].mWeight ;
		const auto r1x = node_weight (mSet.self[it].mLeft) ;
		const auto r2x = node_weight (mSet.self[it].mRight) ;
		mSet.self[it].mWeight = r1x + r2x + 1 ;
		mThis->mTop = ix ;
	}

	void rotate_right (INDEX it) {
		INDEX ix = mSet.self[it].mLeft ;
		mSet.self[it].mLeft = mSet.self[ix].mRight ;
		mSet.self[ix].mRight = it ;
		mSet.self[ix].mWeight = mSet.self[it].mWeight ;
		const auto r1x = node_weight (mSet.self[it].mLeft) ;
		const auto r2x = node_weight (mSet.self[it].mRight) ;
		mSet.self[it].mWeight = r1x + r2x + 1 ;
		mThis->mTop = ix ;
	}

	LENGTH node_weight (INDEX it) const {
		if (it == VAR_NONE)
			return 0 ;
		return mSet.self[it].mWeight ;
	}
} ;
} ;