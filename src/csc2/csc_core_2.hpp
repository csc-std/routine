#pragma once

#ifndef __CSC_CORE__
#define __CSC_CORE__
#endif

#include "csc.hpp"

namespace CSC {
namespace U {
struct FUNCTION_noop {
	inline void operator() () const {
		return ;
	}
} ;
} ;

static constexpr auto noop = U::FUNCTION_noop () ;

namespace U {
#ifdef __CSC_DEBUG__
#ifdef __CSC_COMPILER_MSVC__
struct FUNCTION_abort {
	inline void operator()[[noreturn]] () const {
		__debugbreak () ;
		std::terminate () ;
	}
} ;
#endif

#ifdef __CSC_COMPILER_GNUC__
struct FUNCTION_abort {
	inline void operator()[[noreturn]] () const {
		std::terminate () ;
	}
} ;
#endif

#ifdef __CSC_COMPILER_CLANG__
struct FUNCTION_abort {
	inline void operator()[[noreturn]] () const {
		std::terminate () ;
	}
} ;
#endif
#endif

#ifdef __CSC_UNITTEST__
struct FUNCTION_abort {
	inline void operator()[[noreturn]] () const {
		dynamic_assert (FALSE) ;
	}
} ;
#endif
} ;

static constexpr auto abort = U::FUNCTION_abort () ;

namespace U {
struct FUNCTION_address {
	template <class ARG1>
	inline auto operator() (CREF<ARG1> arg1) const
		->LENGTH {
		return LENGTH (&(reinterpret_cast<CREF<BOOL>> (arg1))) ;
	}
} ;
} ;

static constexpr auto address = U::FUNCTION_address () ;

namespace U {
struct FUNCTION_bitwise {
	template <class ARG1>
	inline auto operator() (CREF<ARG1> arg1) const noexcept
		->BYTE_TRAIT<SIZEOF<ARG1> ,ALIGNOF<ARG1>> {
		using R1X = typeof (arg1) ;
		using R2X = BYTE_TRAIT<SIZEOF<R1X> ,ALIGNOF<R1X>> ;
		return reinterpret_cast<CREF<R2X>> (arg1) ;
	}
} ;
} ;

static constexpr auto bitwise = U::FUNCTION_bitwise () ;

namespace U {
#ifdef __CSC_COMPILER_MSVC__
using FUNCTION_barrier = FUNCTION_noop ;
#endif

#ifdef __CSC_COMPILER_GNUC__
struct FUNCTION_barrier {
	inline void operator() () const noexcept {
		asm volatile ("" ::: "memory") ;
	}
} ;
#endif

#ifdef __CSC_COMPILER_CLANG__
struct FUNCTION_barrier {
	inline void operator() () const noexcept {
		asm volatile ("" ::: "memory") ;
	}
} ;
#endif
} ;

static constexpr auto unsafe_barrier = U::FUNCTION_barrier () ;

namespace U {
struct FUNCTION_property {
	template <class ARG1>
	inline auto operator[] (CREF<DEF<ARG1 *>> arg1) const noexcept
		->VREF<ARG1> {
		return (*arg1) ;
	}
} ;
} ;

static constexpr auto property = U::FUNCTION_property () ;

namespace U {
struct FUNCTION_pointer {
	template <class ARG1>
	inline auto operator[] (VREF<ARG1> arg1) const noexcept
		->UNSAFE_PTR<ARG1> {
		return (&arg1) ;
	}
} ;
} ;

static constexpr auto unsafe_pointer = U::FUNCTION_pointer () ;

namespace U {
struct FUNCTION_deref {
	template <class ARG1>
	inline auto operator[] (VREF<ARG1> tmp) const noexcept
		->VREF<REMOVE_TEMP<REMOVE_ALL<ARG1>>> {
		using R1X = typeof (tmp) ;
		using R2X = REMOVE_TEMP<R1X> ;
		require (IS_SAME<R1X ,TEMP<R2X>>) ;
		return reinterpret_cast<VREF<R2X>> (tmp) ;
	}
} ;
} ;

static constexpr auto unsafe_deref = U::FUNCTION_deref () ;

namespace U {
struct FUNCTION_deptr {
	template <class ARG1>
	inline auto operator[] (VREF<ARG1> tmp) const noexcept
		->VREF<TEMP<ARG1>> {
		using R1X = typeof (tmp) ;
		return reinterpret_cast<VREF<TEMP<R1X>>> (tmp) ;
	}
} ;
} ;

static constexpr auto unsafe_deptr = U::FUNCTION_deptr () ;

namespace U {
struct FUNCTION_swap {
	template <class ARG1 ,class ARG2>
	inline void operator() (VREF<ARG1> arg1 ,VREF<ARG2> arg2) const noexcept {
		using R1X = typeof (arg1) ;
		using R2X = typeof (arg2) ;
		require (IS_SAME<R1X ,R2X>) ;
		auto rax = unsafe_deptr[arg1] ;
		unsafe_deptr[arg1] = unsafe_deptr[arg2] ;
		unsafe_deptr[arg2] = rax ;
		unsafe_barrier () ;
	}
} ;
} ;

static constexpr auto swap = U::FUNCTION_swap () ;

namespace U {
struct FUNCTION_forward {
	template <class ARG1>
	inline auto operator[] (CREF<ARG1> arg1) const
		->CREF<REMOVE_ALL<ARG1>> {
		using R1X = typeof (arg1) ;
		return static_cast<CREF<R1X>> (arg1) ;
	}

	template <class ARG1>
	inline auto operator[] (VREF<ARG1> arg1) const
		->RREF<REMOVE_ALL<ARG1>> {
		using R1X = typeof (arg1) ;
		return static_cast<RREF<R1X>> (arg1) ;
	}
} ;
} ;

static constexpr auto forward = U::FUNCTION_forward () ;

namespace U {
struct FUNCTION_create {
	template <class ARG1 ,class...ARGS>
	inline void operator() (VREF<ARG1> tmp ,RREF<ARGS>...args) const {
		using R1X = typeof (tmp) ;
		using R2X = REMOVE_TEMP<R1X> ;
		require (IS_SAME<R1X ,TEMP<R2X>>) ;
		new (unsafe_pointer[tmp]) R2X (forward[args]...) ;
	}
} ;
} ;

static constexpr auto unsafe_create = U::FUNCTION_create () ;

namespace U {
struct FUNCTION_recreate {
	template <class ARG1>
	inline void operator() (VREF<ARG1> tmp ,RREF<ARG1> obj) const noexcept {
		using R1X = typeof (tmp) ;
		tmp.~R1X () ;
		new (unsafe_pointer[tmp]) R1X (forward[obj]) ;
	}
} ;
} ;

static constexpr auto unsafe_recreate = U::FUNCTION_recreate () ;

namespace U {
struct FUNCTION_destroy {
	template <class ARG1>
	inline void operator() (VREF<ARG1> tmp) const noexcept {
		using R1X = typeof (tmp) ;
		using R2X = REMOVE_TEMP<R1X> ;
		require (IS_SAME<R1X ,TEMP<R2X>>) ;
		unsafe_deref[tmp].~R2X () ;
	}
} ;
} ;

static constexpr auto unsafe_destroy = U::FUNCTION_destroy () ;

namespace U {
struct FUNCTION_zeroize {
	template <class ARG1>
	inline void operator() (VREF<ARG1> arg1) const noexcept {
		using R1X = typeof (arg1) ;
		require (IS_TRIVIAL<R1X>) ;
		unsafe_deptr[arg1] = {0} ;
		unsafe_barrier () ;
	}
} ;
} ;

static constexpr auto unsafe_zeroize = U::FUNCTION_zeroize () ;

namespace U {
struct FUNCTION_alignax {
	inline auto operator() (CREF<LENGTH> base ,CREF<LENGTH> align) const
		->LENGTH {
		const auto r1x = align - base % align ;
		return base + r1x % align ;
	}
} ;
} ;

static constexpr auto alignax = U::FUNCTION_alignax () ;

namespace U {
struct FUNCTION_between {
	inline auto operator() (CREF<INDEX> index ,CREF<INDEX> begin ,CREF<INDEX> end) const
		->BOOL {
		if ifnot (index >= begin)
			return FALSE ;
		if ifnot (index < end)
			return FALSE ;
		return TRUE ;
	}
} ;
} ;

static constexpr auto between = U::FUNCTION_between () ;

namespace U {
struct FUNCTION_abs {
	template <class ARG1>
	inline auto operator() (CREF<ARG1> arg1) const
		->REMOVE_ALL<ARG1> {
		using R1X = typeof (arg1) ;
		if (arg1 < R1X (ZERO))
			return -arg1 ;
		return +arg1 ;
	}
} ;
} ;

static constexpr auto abs = U::FUNCTION_abs () ;

namespace U {
struct FUNCTION_min {
	template <class ARG1>
	inline auto operator() (CREF<ARG1> arg1 ,CREF<ARG1> arg2) const
		->REMOVE_ALL<ARG1> {
		if (arg1 < arg2)
			return arg1 ;
		return arg2 ;
	}
} ;
} ;

static constexpr auto min = U::FUNCTION_min () ;

namespace U {
struct FUNCTION_max {
	template <class ARG1>
	inline auto operator() (CREF<ARG1> arg1 ,CREF<ARG1> arg2) const
		->REMOVE_ALL<ARG1> {
		if (arg1 < arg2)
			return arg2 ;
		return arg1 ;
	}
} ;
} ;

static constexpr auto max = U::FUNCTION_max () ;

namespace S0 {
template <class UNIT1>
struct FUNCTION_compr {
	inline auto operator() (CREF<UNIT1> arg1 ,CREF<UNIT1> arg2) const
		->FLAG {
		if (arg1 < arg2)
			return FLAG (-1) ;
		if (arg2 < arg1)
			return FLAG (+1) ;
		return ZERO ;
	}
} ;
} ;

namespace S1 {
template <class UNIT1>
struct FUNCTION_compr {
	inline auto operator() (CREF<UNIT1> arg1 ,CREF<UNIT1> arg2) const
		->FLAG {
		return arg1.compr (arg2) ;
	}
} ;
} ;

namespace U {
template <class...>
trait FUNCTION_COMPR_HELP ;

template <class ARG1>
trait FUNCTION_COMPR_HELP<ARG1 ,REQUIRE<IS_BASIC<ARG1>>> {
	using RET = S0::FUNCTION_compr<ARG1> ;
} ;

template <class ARG1>
trait FUNCTION_COMPR_HELP<ARG1 ,REQUIRE<IS_CLASS<ARG1>>> {
	using RET = S1::FUNCTION_compr<ARG1> ;
} ;

struct FUNCTION_compr {
	template <class ARG1>
	inline auto operator() (CREF<ARG1> arg1 ,CREF<ARG1> arg2) const
		->FLAG {
		using R1X = typeof (arg1) ;
		using R2X = typename FUNCTION_COMPR_HELP<R1X ,void>::RET ;
		static constexpr auto M_INVOKE = R2X () ;
		return M_INVOKE (arg1 ,arg2) ;
	}
} ;
} ;

static constexpr auto operator_compr = U::FUNCTION_compr () ;

namespace S0 {
template <class UNIT1>
struct FUNCTION_hash {
	inline auto operator() (CREF<UNIT1> arg1) const
		->FLAG {
		return FLAG (bitwise (arg1)) ;
	}
} ;
} ;

namespace S1 {
template <class UNIT1>
struct FUNCTION_hash {
	inline auto operator() (CREF<UNIT1> arg1) const
		->FLAG {
		return arg1.hash () ;
	}
} ;
} ;

namespace U {
template <class...>
trait FUNCTION_HASH_HELP ;

template <class ARG1>
trait FUNCTION_HASH_HELP<ARG1 ,REQUIRE<IS_BASIC<ARG1>>> {
	using RET = S0::FUNCTION_hash<ARG1> ;
} ;

template <class ARG1>
trait FUNCTION_HASH_HELP<ARG1 ,REQUIRE<IS_CLASS<ARG1>>> {
	using RET = S1::FUNCTION_hash<ARG1> ;
} ;

struct FUNCTION_hash {
	template <class ARG1>
	inline auto operator() (CREF<ARG1> arg1) const
		->FLAG {
		using R1X = typeof (arg1) ;
		using R2X = typename FUNCTION_HASH_HELP<R1X ,void>::RET ;
		static constexpr auto M_INVOKE = R2X () ;
		return M_INVOKE (arg1) ;
	}
} ;
} ;

static constexpr auto operator_hash = U::FUNCTION_hash () ;

namespace U {
struct FUNCTION_hashcode {
	inline auto operator() () const
		->FLAG {
		const auto r1x = VAR64 (-3750763034362895579) ;
		const auto r2x = VAR64 (FEAT (r1x) & FEAT (VAR64_MAX)) ;
		return FLAG (r2x) ;
	}

	inline auto operator() (CREF<FLAG> arg1 ,CREF<FLAG> arg2) const
		->FLAG {
		const auto r1x = VAR64 (FEAT (arg1) ^ FEAT (arg2)) ;
		const auto r2x = r1x * VAR64 (1099511628211) ;
		const auto r3x = VAR64 (FEAT (r2x) & FEAT (VAR64_MAX)) ;
		return FLAG (r3x) ;
	}
} ;
} ;

static constexpr auto hashcode = U::FUNCTION_hashcode () ;

namespace U {
template <class UNIT1>
struct CABI_VPTR :private Interface {} ;

struct FUNCTION_cabi {
	template <class ARG1>
	inline auto operator() (CREF<ARG1> nid) const
		->FLAG {
		using R1X = typeof (nid) ;
		using R2X = CABI_VPTR<R1X> ;
		require (ENUM_EQUAL<SIZEOF<VAR> ,SIZEOF<R2X>>) ;
		require (ENUM_EQUAL<ALIGNOF<VAR> ,ALIGNOF<R2X>>) ;
		return FLAG (bitwise (R2X ())) ;
	}
} ;
} ;

static constexpr auto operator_cabi = U::FUNCTION_cabi () ;

namespace S0 {
struct ANY_DETAIL {
	struct Holder ;
	struct NULLOPT ;

	struct BLOCK ;
	struct SLOT ;
	class AnyHeap ;
} ;

struct ANY_DETAIL::Holder :public Interface {
	virtual void destroy () = 0 ;
	virtual LENGTH unsafe_addr () = 0 ;
	virtual FLAG type_cabi () const = 0 ;
} ;

struct ANY_DETAIL::NULLOPT {} ;

class Any {
private:
	using Holder = typename ANY_DETAIL::Holder ;
	using NULLOPT = typename ANY_DETAIL::NULLOPT ;

private:
	UNSAFE_PTR<Holder> mPointer ;

public:
	implicit Any () = delete ;

	template <class ARG1 ,class = ENABLE<ENUM_NOT<ENUM_ANY<IS_SAME<REMOVE_ALL<ARG1> ,Any> ,IS_SAME<REMOVE_ALL<ARG1> ,NULLOPT>>>>>
	explicit Any (RREF<ARG1> that) :Any (NULLOPT ()) {
		using R1X = typeof (that) ;
		using R2X = typename ANY_IMPLHOLDER_HELP<R1X>::EXTERN ;
		mPointer = R2X::create (forward[that]) ;
	}

	implicit ~Any () noexcept {
		if (mPointer == NULL)
			return ;
		mPointer->destroy () ;
		mPointer = NULL ;
	}

	implicit Any (CREF<Any>) = delete ;

	inline void operator= (CREF<Any>) = delete ;

	implicit Any (RREF<Any> that) noexcept :Any (NULLOPT ()) {
		auto &&thiz = property[this] ;
		swap (thiz ,that) ;
	}

	inline void operator= (RREF<Any>) = delete ;

	template <class ARG1>
	auto poll (CREF<ARG1> nid)
		->REMOVE_ALL<ARG1> {
		using R1X = typeof (nid) ;
		using R2X = typename ANY_IMPLHOLDER_HELP<R1X>::ImplHolder ;
		assert (mPointer != NULL) ;
		const auto r1x = operator_cabi (TYPEAS<R2X>::id) ;
		const auto r2x = mPointer->type_cabi () ;
		assert (r1x == r2x) ;
		const auto r3x = mPointer->unsafe_addr () ;
		const auto r4x = reinterpret_cast<UNSAFE_PTR<R1X>> (r3x) ;
		return forward[property[r4x]] ;
	}

	template <class ARG1>
	inline explicit operator ARG1 () rightvalue {
		using R1X = typeof (ARG1 ()) ;
		return poll (TYPEAS<R1X>::id) ;
	}

private:
	explicit Any (CREF<NULLOPT>) noexcept :mPointer (NULL) {}
} ;
} ;

namespace U {
template <class...>
trait ANY_HELP ;

template <>
trait ANY_HELP<> {
	using RET = S0::Any ;
} ;

template <class...>
trait ANY_IMPLHOLDER_HELP ;

template <class ARG1>
trait ANY_IMPLHOLDER_HELP<ARG1> {
	using DETAIL = typename S0::ANY_DETAIL ;
	using Holder = typename DETAIL::Holder ;

	class ImplHolder ;

	struct EXTERN ;
} ;

template <class UNIT1>
struct ANY_IMPLHOLDER_HELP<UNIT1>::
	EXTERN {
	imports UNSAFE_PTR<Holder> create (RREF<UNIT1> that) ;
} ;
} ;

using Any = typename U::ANY_HELP<>::RET ;

namespace U {
struct FUNCTION_bad {
	template <class ARG1>
	inline auto operator() (CREF<ARG1> nid) const
		->REMOVE_ALL<ARG1> {
		using R1X = typeof (nid) ;
		assert (FALSE) ;
		return R1X (Any (ZERO)) ;
	}
} ;
} ;

static constexpr auto bad = U::FUNCTION_bad () ;

namespace U {
template <class...>
trait BOX_HELP ;

template <class ARG1>
trait BOX_HELP<ARG1> {
	struct DETAIL {
		struct Holder ;
	} ;
} ;

template <class ARG1>
trait BOX_HELP<ARG1 ,REQUIRE<IS_INTERFACE<ARG1>>> {
	using DETAIL = typename BOX_HELP<ARG1>::DETAIL ;

	class Box ;
} ;

template <class UNIT1>
struct BOX_HELP<UNIT1>::DETAIL::Holder :public Interface {
	virtual void destroy () = 0 ;
	virtual VREF<UNIT1> to () leftvalue = 0 ;
	virtual CREF<UNIT1> to () const leftvalue = 0 ;
} ;

template <class...>
trait BOX_IMPLHOLDER_HELP ;

template <class ARG1 ,class ARG2>
trait BOX_IMPLHOLDER_HELP<ARG1 ,ARG2> {
	using DETAIL = typename BOX_HELP<ARG1>::DETAIL ;
	using Holder = typename DETAIL::Holder ;

	class ImplHolder ;

	struct EXTERN ;
} ;

template <class UNIT1 ,class UNIT2>
struct BOX_IMPLHOLDER_HELP<UNIT1 ,UNIT2>::
	EXTERN {
	imports UNSAFE_PTR<Holder> create (RREF<UNIT2> that) ;
} ;

template <class UNIT1>
class BOX_HELP<UNIT1 ,REQUIRE<IS_INTERFACE<UNIT1>>>::
	Box {
private:
	using Holder = typename DETAIL::Holder ;

private:
	UNSAFE_PTR<Holder> mPointer ;

public:
	implicit Box () noexcept :mPointer (NULL) {}

	template <class ARG1>
	imports auto make (RREF<ARG1> that)
		->Box {
		using R1X = typeof (that) ;
		require (IS_EXTEND<UNIT1 ,R1X>) ;
		using R2X = typename BOX_IMPLHOLDER_HELP<UNIT1 ,R1X>::EXTERN ;
		Box ret ;
		ret.mPointer = R2X::create (forward[that]) ;
		return forward[ret] ;
	}

	implicit ~Box () noexcept {
		if (mPointer == NULL)
			return ;
		mPointer->destroy () ;
		mPointer = NULL ;
	}

	implicit Box (CREF<Box>) = delete ;

	inline void operator= (CREF<Box>) = delete ;

	implicit Box (RREF<Box> that) noexcept :Box () {
		auto &&thiz = property[this] ;
		swap (thiz ,that) ;
	}

	inline void operator= (RREF<Box> that) noexcept {
		auto &&thiz = property[this] ;
		if (address (thiz) == address (that))
			return ;
		unsafe_destroy (unsafe_deptr[thiz]) ;
		unsafe_create (unsafe_deptr[thiz] ,forward[that]) ;
		unsafe_barrier () ;
	}

	auto exist () const
		->BOOL {
		return mPointer != NULL ;
	}

	inline auto operator== (CREF<typeof (NULL)>) const
		->BOOL {
		return ifnot (exist ()) ;
	}

	inline auto operator!= (CREF<typeof (NULL)>) const
		->BOOL {
		return exist () ;
	}

	auto to () leftvalue
		->VREF<UNIT1> {
		assert (exist ()) ;
		return mPointer->self ;
	}

	inline implicit operator VREF<UNIT1> () leftvalue {
		return self ;
	}

	inline auto operator-> () leftvalue
		->UNSAFE_PTR<VREF<UNIT1>> {
		return unsafe_pointer[self] ;
	}

	auto to () const leftvalue
		->CREF<UNIT1> {
		assert (exist ()) ;
		return mPointer->self ;
	}

	inline implicit operator CREF<UNIT1> () const leftvalue {
		return self ;
	}

	inline auto operator-> () const leftvalue
		->UNSAFE_PTR<CREF<UNIT1>> {
		return unsafe_pointer[self] ;
	}
} ;

template <class ARG1>
trait BOX_HELP<ARG1 ,REQUIRE<ENUM_NOT<IS_INTERFACE<ARG1>>>> {
	using DETAIL = typename BOX_HELP<ARG1>::DETAIL ;

	class Box ;
} ;

template <class UNIT1>
class BOX_HELP<UNIT1 ,REQUIRE<ENUM_NOT<IS_INTERFACE<UNIT1>>>>::
	Box {
private:
	using Holder = typename DETAIL::Holder ;

private:
	UNSAFE_PTR<Holder> mPointer ;

public:
	implicit Box () noexcept :mPointer (NULL) {}

	template <class...ARGS>
	imports auto make (RREF<ARGS>...that)
		->Box {
		using R2X = typename BOX_IMPLHOLDER_HELP<UNIT1 ,UNIT1>::EXTERN ;
		Box ret ;
		ret.mPointer = R2X::create (UNIT1 (forward[that]...)) ;
		return forward[ret] ;
	}

	implicit ~Box () noexcept {
		if (mPointer == NULL)
			return ;
		mPointer->destroy () ;
		mPointer = NULL ;
	}

	implicit Box (CREF<Box>) = delete ;

	inline void operator= (CREF<Box>) = delete ;

	implicit Box (RREF<Box> that) noexcept :Box () {
		auto &&thiz = property[this] ;
		swap (thiz ,that) ;
	}

	inline void operator= (RREF<Box> that) noexcept {
		auto &&thiz = property[this] ;
		if (address (thiz) == address (that))
			return ;
		unsafe_destroy (unsafe_deptr[thiz]) ;
		unsafe_create (unsafe_deptr[thiz] ,forward[that]) ;
		unsafe_barrier () ;
	}

	auto exist () const
		->BOOL {
		return mPointer != NULL ;
	}

	inline auto operator== (CREF<typeof (NULL)>) const
		->BOOL {
		return ifnot (exist ()) ;
	}

	inline auto operator!= (CREF<typeof (NULL)>) const
		->BOOL {
		return exist () ;
	}

	auto to () leftvalue
		->VREF<UNIT1> {
		assert (exist ()) ;
		return mPointer->self ;
	}

	inline implicit operator VREF<UNIT1> () leftvalue {
		return self ;
	}

	inline auto operator-> () leftvalue
		->UNSAFE_PTR<VREF<UNIT1>> {
		return unsafe_pointer (self) ;
	}

	auto to () const leftvalue
		->CREF<UNIT1> {
		assert (exist ()) ;
		return mPointer->self ;
	}

	inline implicit operator CREF<UNIT1> () const leftvalue {
		return self ;
	}

	inline auto operator-> () const leftvalue
		->UNSAFE_PTR<CREF<UNIT1>> {
		return unsafe_pointer (self) ;
	}
} ;
} ;

template <class UNIT1>
using Box = typename U::BOX_HELP<UNIT1 ,void>::Box ;

namespace U {
template <class...>
trait CELL_HELP ;

template <class ARG1>
trait CELL_HELP<ARG1 ,REQUIRE<IS_CLONEABLE<ARG1>>> {
	class Cell ;
} ;

template <class UNIT1>
class CELL_HELP<UNIT1 ,REQUIRE<IS_CLONEABLE<UNIT1>>>::
	Cell {
private:
	mutable TEMP<UNIT1> mValue ;
	BOOL mExist ;

public:
	implicit Cell () noexcept :mExist (FALSE) {}

	template <class...ARGS>
	imports auto make (RREF<ARGS>...that)
		->Cell {
		Cell ret ;
		unsafe_create (ret.mValue ,UNIT1 (forward[that]...)) ;
		ret.mExist = TRUE ;
		return forward[ret] ;
	}

	implicit ~Cell () noexcept {
		if ifnot (mExist)
			return ;
		unsafe_destroy (mValue) ;
		mExist = FALSE ;
	}

	implicit Cell (CREF<Cell> that) :Cell () {
		auto &&thiz = property[this] ;
		if ifnot (that.exist ())
			return ;
		thiz = Cell::make (that.fetch ()) ;
	}

	inline void operator= (CREF<Cell> that) {
		auto &&thiz = property[this] ;
		if (address (thiz) == address (that))
			return ;
		unsafe_destroy (unsafe_deptr[thiz]) ;
		unsafe_create (unsafe_deptr[thiz] ,forward[that]) ;
		unsafe_barrier () ;
	}

	implicit Cell (RREF<Cell> that) noexcept :Cell () {
		auto &&thiz = property[this] ;
		swap (thiz ,that) ;
	}

	inline void operator= (RREF<Cell> that) noexcept {
		auto &&thiz = property[this] ;
		if (address (thiz) == address (that))
			return ;
		unsafe_destroy (unsafe_deptr[thiz]) ;
		unsafe_create (unsafe_deptr[thiz] ,forward[that]) ;
		unsafe_barrier () ;
	}

	auto exist () const
		->BOOL {
		return mExist ;
	}

	inline auto operator== (CREF<typeof (NULL)>) const
		->BOOL {
		return ifnot (exist ()) ;
	}

	inline auto operator!= (CREF<typeof (NULL)>) const
		->BOOL {
		return exist () ;
	}

	auto fetch () const
		->UNIT1 {
		assert (exist ()) ;
		return m_fake () ;
	}

	auto value (RREF<UNIT1> obj) const
		->UNIT1 {
		if ifnot (exist ())
			return forward[obj] ;
		return m_fake () ;
	}

	void store (RREF<UNIT1> obj) const {
		assert (exist ()) ;
		m_fake () = forward[obj] ;
	}

	auto exchange (RREF<UNIT1> obj) const
		->UNIT1 {
		assert (exist ()) ;
		UNIT1 ret = m_fake () ;
		m_fake () = forward[obj] ;
		return forward[ret] ;
	}

	auto change (VREF<UNIT1> expect ,RREF<UNIT1> obj) const
		->BOOL {
		assert (exist ()) ;
		if ifswitch (TRUE) {
			if (m_fake () == expect)
				discard ;
			expect = m_fake () ;
			return FALSE ;
		}
		m_fake () = forward[obj] ;
		return TRUE ;
	}

private:
	auto m_fake () const leftvalue
		->VREF<UNIT1> {
		return unsafe_deref[mValue] ;
	}
} ;
} ;

template <class UNIT1>
using Cell = typename U::CELL_HELP<UNIT1 ,void>::Cell ;

namespace U {
template <class...>
trait RC_HELP ;

template <class ARG1>
trait RC_HELP<ARG1> {
	struct DETAIL {
		struct Holder ;
	} ;

	class RC ;
} ;

template <class UNIT1>
struct RC_HELP<UNIT1>::DETAIL::Holder :public Interface {
	virtual void destroy () = 0 ;
	virtual CREF<UNIT1> to () const leftvalue = 0 ;
	virtual LENGTH increase () = 0 ;
	virtual LENGTH decrease () = 0 ;
} ;

template <class...>
trait RC_IMPLHOLDER_HELP ;

template <class ARG1>
trait RC_IMPLHOLDER_HELP<ARG1> {
	using DETAIL = typename RC_HELP<ARG1>::DETAIL ;
	using Holder = typename DETAIL::Holder ;

	class ImplHolder ;

	struct EXTERN ;
} ;

template <class UNIT1>
struct RC_IMPLHOLDER_HELP<UNIT1>::
	EXTERN {
	imports UNSAFE_PTR<Holder> create (RREF<UNIT1> that) ;
} ;

template <class UNIT1>
class RC_HELP<UNIT1>::
	RC {
private:
	using Holder = typename DETAIL::Holder ;

private:
	UNSAFE_PTR<Holder> mPointer ;

public:
	implicit RC () noexcept :mPointer (NULL) {}

	template <class...ARGS>
	imports auto make (RREF<ARGS>...that)
		->RC {
		using R1X = typeof (that) ;
		require (IS_SAME<UNIT1 ,R1X>) ;
		using R2X = typename RC_IMPLHOLDER_HELP<R1X>::EXTERN ;
		RC ret ;
		ret.mPointer = R2X::create (UNIT1 (forward[that]...)) ;
		const auto r1x = property[ret.mPointer].increase () ;
		assert (r1x == 1) ;
		return forward[ret] ;
	}

	implicit ~RC () noexcept {
		if (mPointer == NULL)
			return ;
		if ifswitch (TRUE) {
			const auto r1x = mPointer->decrease () ;
			if (r1x > ZERO)
				discard ;
			mPointer->destroy () ;
		}
		mPointer = NULL ;
	}

	implicit RC (CREF<RC> that) :RC () {
		if ifnot (that.exist ())
			return ;
		mPointer = that.mPointer ;
		const auto r1x = mPointer->increase () ;
		assert (r1x >= 2) ;
	}

	inline void operator= (CREF<RC> that) {
		auto &&thiz = property[this] ;
		if (address (thiz) == address (that))
			return ;
		unsafe_destroy (unsafe_deptr[thiz]) ;
		unsafe_create (unsafe_deptr[thiz] ,forward[that]) ;
		unsafe_barrier () ;
	}

	implicit RC (RREF<RC> that) noexcept :RC () {
		auto &&thiz = property[this] ;
		swap (thiz ,that) ;
	}

	inline void operator= (RREF<RC> that) noexcept {
		auto &&thiz = property[this] ;
		if (address (thiz) == address (that))
			return ;
		unsafe_destroy (unsafe_deptr[thiz]) ;
		unsafe_create (unsafe_deptr[thiz] ,forward[that]) ;
		unsafe_barrier () ;
	}

	auto exist () const
		->BOOL {
		return mPointer != NULL ;
	}

	inline auto operator== (CREF<typeof (NULL)>) const
		->BOOL {
		return ifnot (exist ()) ;
	}

	inline auto operator!= (CREF<typeof (NULL)>) const
		->BOOL {
		return exist () ;
	}

	auto to () const leftvalue
		->CREF<UNIT1> {
		assert (exist ()) ;
		return mPointer->self ;
	}

	inline implicit operator CREF<UNIT1> () const leftvalue {
		return self ;
	}

	inline auto operator-> () const leftvalue
		->UNSAFE_PTR<CREF<UNIT1>> {
		return unsafe_pointer (self) ;
	}
} ;
} ;

template <class UNIT1>
using RC = typename U::RC_HELP<UNIT1>::RC ;

namespace U {
template <class...>
trait ITERATOR_HELP ;

template <>
trait ITERATOR_HELP<> {
	class IteratorRange ;

	class Iterator ;
} ;

class ITERATOR_HELP<>::Iterator {
private:
	INDEX mCurr ;

public:
	implicit Iterator () = delete ;

	explicit Iterator (CREF<INDEX> curr) {
		mCurr = curr ;
	}

	inline auto operator!= (CREF<Iterator> that) const
		->BOOL {
		return mCurr != that.mCurr ;
	}

	inline void operator++ () {
		mCurr = mCurr + 1 ;
	}

	inline auto operator* () const leftvalue
		->CREF<INDEX> {
		return mCurr ;
	}
} ;

class ITERATOR_HELP<>::IteratorRange {
private:
	INDEX mBegin ;
	INDEX mEnd ;

public:
	implicit IteratorRange () = delete ;

	explicit IteratorRange (CREF<INDEX> begin_ ,CREF<INDEX> end_) {
		mBegin = begin_ ;
		mEnd = max (begin_ ,end_) ;
	}

	auto begin () const
		->Iterator {
		return Iterator (mBegin) ;
	}

	auto end () const
		->Iterator {
		return Iterator (mEnd) ;
	}
} ;
} ;

namespace U {
struct FUNCTION_range {
	using IteratorRange = typename U::ITERATOR_HELP<>::IteratorRange ;

	inline auto operator() (CREF<INDEX> begin ,CREF<INDEX> end) const
		->IteratorRange {
		return IteratorRange (begin ,end) ;
	}
} ;
} ;

static constexpr auto range = U::FUNCTION_range () ;

namespace U {
template <class...>
trait SLICE_HELP ;

template <class ARG1>
trait SLICE_HELP<ARG1> {
	struct DETAIL {
		struct Holder ;
	} ;
} ;

template <class ARG1>
trait SLICE_HELP<ARG1 ,REQUIRE<IS_STR<ARG1>>> {
	using DETAIL = typename SLICE_HELP<ARG1>::DETAIL ;

	class Slice ;
} ;

template <class UNIT1>
struct SLICE_HELP<UNIT1>::DETAIL::Holder :public Interface {
	virtual LENGTH size () const = 0 ;
	virtual CREF<UNIT1> at (CREF<INDEX> index) const = 0 ;
} ;

template <class...>
trait SLICE_IMPLHOLDER_HELP ;

template <class ARG1 ,class ARG2>
trait SLICE_IMPLHOLDER_HELP<ARG1 ,ARG2> {
	using DETAIL = typename SLICE_HELP<ARG1 ,void>::DETAIL ;
	using Holder = typename DETAIL::Holder ;

	class ImplHolder ;
} ;

template <class UNIT1>
class SLICE_HELP<UNIT1 ,REQUIRE<IS_STR<UNIT1>>>::
	Slice {
private:
	using Holder = typename DETAIL::Holder ;

private:
	RC<Box<Holder>> mPointer ;

public:
	implicit Slice () = default ;

	auto size () const
		->LENGTH {
		if (mPointer == NULL)
			return ZERO ;
		return mPointer.self->size () ;
	}

	auto addr () const
		->LENGTH {
		if (mPointer == NULL)
			return ZERO ;
		return address (mPointer.self->at[0]) ;
	}

	auto at (CREF<INDEX> index) const
		->UNIT1 {
		assert (between (index ,0 ,size ())) ;
		return mPointer.self->at (index) ;
	}

	inline auto operator[] (CREF<INDEX> index) const
		->UNIT1 {
		return at (index) ;
	}

	auto equal (CREF<Slice> that) const
		->BOOL {
		if (size () != that.size ())
			return FALSE ;
		for (auto &&i : range (0 ,size ())) {
			if (mPointer.self->at (i) != that.mPointer.self->at (i))
				return FALSE ;
		}
		return TRUE ;
	}

	inline auto operator== (CREF<Slice> that) const
		->BOOL {
		return equal (that) ;
	}

	inline auto operator!= (CREF<Slice> that) const
		->BOOL {
		return ifnot (equal (that)) ;
	}

	auto compr (CREF<Slice> that) const
		->FLAG {
		const auto r1x = min (size () ,that.size ()) ;
		for (auto &&i : range (0 ,r1x)) {
			const auto r2x = operator_compr (mPointer.self->at (i) ,that.mPointer.self->at (i)) ;
			if (r2x != ZERO)
				return r2x ;
		}
		return operator_compr (size () ,that.size ()) ;
	}

	inline auto operator< (CREF<Slice> that) const
		->BOOL {
		return compr (that) < ZERO ;
	}

	inline auto operator<= (CREF<Slice> that) const
		->BOOL {
		return compr (that) <= ZERO ;
	}

	inline auto operator> (CREF<Slice> that) const
		->BOOL {
		return compr (that) > ZERO ;
	}

	inline auto operator>= (CREF<Slice> that) const
		->BOOL {
		return compr (that) >= ZERO ;
	}

	auto hash () const
		->FLAG {
		FLAG ret = hashcode () ;
		for (auto &&i : range (0 ,size ())) {
			const auto r1x = FLAG (mPointer.self->at (i)) ;
			ret = hashcode (ret ,r1x) ;
		}
		return forward[ret] ;
	}
} ;
} ;

template <class UNIT1>
using Slice = typename U::SLICE_HELP<UNIT1 ,void>::Slice ;

namespace S0 {
struct CLAZZ_DETAIL {
	struct Holder ;
} ;

struct CLAZZ_DETAIL::Holder :public Interface {
	virtual LENGTH type_size () const = 0 ;
	virtual LENGTH type_align () const = 0 ;
	virtual FLAG type_cabi () const = 0 ;
	virtual Slice<STR> type_name () const = 0 ;
} ;

class Clazz {
private:
	using Holder = typename CLAZZ_DETAIL::Holder ;

private:
	RC<Box<Holder>> mPointer ;

public:
	implicit Clazz () = default ;

	auto type_size () const
		->LENGTH {
		if (mPointer == NULL)
			return ZERO ;
		return mPointer.self->type_size () ;
	}

	auto type_align () const
		->LENGTH {
		if (mPointer == NULL)
			return ZERO ;
		return mPointer.self->type_size () ;
	}

	auto type_cabi () const
		->FLAG {
		if (mPointer == NULL)
			return ZERO ;
		return mPointer.self->type_size () ;
	}

	auto type_name () const
		->Slice<STR> {
		if (mPointer == NULL)
			return Slice<STR> () ;
		return mPointer.self->type_name () ;
	}

	auto equal (CREF<Clazz> that) const
		->BOOL {
		if (type_cabi () == that.type_cabi ())
			return TRUE ;
		return type_name () == that.type_name () ;
	}

	inline auto operator== (CREF<Clazz> that) const
		->BOOL {
		return equal (that) ;
	}

	inline auto operator!= (CREF<Clazz> that) const
		->BOOL {
		return ifnot (equal (that)) ;
	}

	auto compr (CREF<Clazz> that) const
		->FLAG {
		if (type_cabi () == that.type_cabi ())
			return ZERO ;
		return operator_compr (type_name () ,that.type_name ()) ;
	}

	inline auto operator< (CREF<Clazz> that) const
		->BOOL {
		return compr (that) < ZERO ;
	}

	inline auto operator<= (CREF<Clazz> that) const
		->BOOL {
		return compr (that) <= ZERO ;
	}

	inline auto operator> (CREF<Clazz> that) const
		->BOOL {
		return compr (that) > ZERO ;
	}

	inline auto operator>= (CREF<Clazz> that) const
		->BOOL {
		return compr (that) >= ZERO ;
	}

	auto hash () const
		->FLAG {
		if (type_cabi () == ZERO)
			return ZERO ;
		const auto r1x = type_name () ;
		return r1x.hash () ;
	}
} ;
} ;

namespace U {
template <class...>
trait CLAZZ_HELP ;

template <>
trait CLAZZ_HELP<> {
	using RET = S0::Clazz ;
} ;
} ;

using Clazz = typename U::CLAZZ_HELP<>::RET ;

namespace S0 {
class Exception {
private:
	Slice<STR> mWhat ;

public:
	implicit Exception () = default ;

	explicit Exception (CREF<Slice<STR>> what) :mWhat (what) {}

	auto what () const leftvalue
		->CREF<Slice<STR>> {
		return mWhat ;
	}

	void raise[[noreturn]] () {
		auto &&thiz = property[this] ;
		throw thiz ;
	}
} ;
} ;

namespace U {
template <class...>
trait EXCEPTION_HELP ;

template <>
trait EXCEPTION_HELP<> {
	using RET = S0::Exception ;
} ;
} ;

using Exception = typename U::EXCEPTION_HELP<>::RET ;
} ;

/*
trait ANY_HELP<ARG1> {
	class Any {
		interface Holder ;
		class ImplHolder ;

		UNSAFE_PTR<Holder> mPointer ;
	} ;

	interface Any::Holder {
		function type_cabi = () :LENGTH => virtual ;
	} ;
} ;

*/