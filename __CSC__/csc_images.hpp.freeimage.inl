﻿#pragma once

#ifndef __CSC_IMAGES__
#error "∑(っ°Д° ;)っ : require 'csc_images.hpp'"
#endif

#ifdef __CSC__
#pragma push_macro ("self")
#pragma push_macro ("implicit")
#pragma push_macro ("side_effects")
#pragma push_macro ("leftvalue")
#pragma push_macro ("rightvalue")
#pragma push_macro ("imports")
#pragma push_macro ("exports")
#pragma push_macro ("switch_once")
#pragma push_macro ("discard")
#undef self
#undef implicit
#undef side_effects
#undef leftvalue
#undef rightvalue
#undef imports
#undef exports
#undef switch_once
#undef discard
#endif

#ifdef __CSC_DEPRECATED__
#pragma region
#pragma warning (push)
#ifdef __CSC_COMPILER_MSVC__
#pragma warning (disable :26477)
#endif
#include <freeimage.h>
#pragma warning (pop)
#pragma endregion
#endif

#ifndef FREEIMAGE_H
#error "∑(っ°Д° ;)っ : require 'freeimage.h'"
#endif

#ifdef __CSC_DEPRECATED__
#ifdef __CSC_COMPILER_MSVC__
#ifndef use_comment_lib_freeimage
#define use_comment_lib_freeimage "freeimage.lib"
#endif
#pragma comment (lib ,use_comment_lib_freeimage)
#undef use_comment_lib_freeimage
#endif
#endif

#ifdef __CSC__
#pragma pop_macro ("self")
#pragma pop_macro ("implicit")
#pragma pop_macro ("side_effects")
#pragma pop_macro ("leftvalue")
#pragma pop_macro ("rightvalue")
#pragma pop_macro ("imports")
#pragma pop_macro ("exports")
#pragma pop_macro ("switch_once")
#pragma pop_macro ("discard")
#endif

namespace CSC {
namespace api {
using ::FIMEMORY ;

using ::FreeImage_GetBits ;
using ::FreeImage_GetWidth ;
using ::FreeImage_GetHeight ;
using ::FreeImage_Allocate ;
using ::FreeImage_Unload ;
using ::FreeImage_FillBackground ;
using ::FreeImage_OpenMemory ;
using ::FreeImage_CloseMemory ;
using ::FreeImage_GetFileTypeFromMemory ;
using ::FreeImage_LoadFromMemory ;
using ::FreeImage_GetImageType ;
using ::FreeImage_SaveToMemory ;
using ::FreeImage_AcquireMemory ;
using ::FreeImage_GetFileType ;
using ::FreeImage_Load ;
using ::FreeImage_GetBPP ;
using ::FreeImage_ConvertTo24Bits ;
using ::FreeImage_Save ;
using ::FreeImage_ConvertTo32Bits ;
} ;

template <class>
class AbstractImage_Engine_FREEIMAGE ;

template <>
class AbstractImage_Engine_FREEIMAGE<COLOR_BGR>
	:public AbstractImage<COLOR_BGR>::Abstract {
public:
	using HFIBITMAP = PTR<FIBITMAP> ;
	using NATIVE_THIS = UniqueRef<HFIBITMAP> ;

public:
 	implicit AbstractImage_Engine_FREEIMAGE () {
		_STATIC_ASSERT_ (_SIZEOF_ (DEF<decltype (DEREF[this])>) == _SIZEOF_ (Interface)) ;
		_STATIC_ASSERT_ (_ALIGNOF_ (DEF<decltype (DEREF[this])>) == _ALIGNOF_ (Interface)) ;
	}

	void compute_layout (AnyRef<void> &holder ,AbstractImage<COLOR_BGR>::LAYOUT &layout) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		const auto r2x = api::FreeImage_GetBits (r1x) ;
		auto &r3x = _LOAD_UNSAFE_ (ARGV<ARR<COLOR_BGR>>::null ,_ADDRESS_ (r2x)) ;
		layout.mImage = DEPTR[r3x] ;
		layout.mCX = LENGTH (api::FreeImage_GetWidth (r1x)) ;
		layout.mCY = LENGTH (api::FreeImage_GetHeight (r1x)) ;
		layout.mCW = layout.mCX ;
		layout.mCK = 0 ;
	}

	void compute_load_data (AnyRef<void> &holder ,const LENGTH &cx_ ,const LENGTH &cy_) const override {
		const auto r1x = cx_ * cy_ * 3 ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x >= 0 && r1x < VAR32_MAX) ;
		auto tmp = UniqueRef<HFIBITMAP> ([&] (HFIBITMAP &me) {
			me = api::FreeImage_Allocate (VAR32 (cx_) ,VAR32 (cy_) ,24) ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
		} ,[] (HFIBITMAP &me) {
			api::FreeImage_Unload (me) ;
		}) ;
		const auto r2x = COLOR_BGR {0 ,0 ,0} ;
		api::FreeImage_FillBackground (tmp.self ,DEPTR[r2x] ,0) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (tmp)) ;
	}

	void compute_load_data (AnyRef<void> &holder ,const AutoBuffer<BYTE> &data) const override {
		using HFIMEMORY = PTR<api::FIMEMORY> ;
		auto tmp = UniqueRef<HFIBITMAP> ([&] (HFIBITMAP &me) {
			const auto r1x = UniqueRef<PACK<HFIMEMORY ,AutoBuffer<BYTE>>> ([&] (PACK<HFIMEMORY ,AutoBuffer<BYTE>> &me) {
				me.mP2 = data ;
				me.mP1 = api::FreeImage_OpenMemory (me.mP2.self ,VARY (me.mP2.size ())) ;
				_DYNAMIC_ASSERT_ (me.mP1 != NULL) ;
			} ,[] (PACK<HFIMEMORY ,AutoBuffer<BYTE>> &me) {
				api::FreeImage_CloseMemory (me.mP1) ;
			}) ;
			const auto r2x = api::FreeImage_GetFileTypeFromMemory (r1x->mP1) ;
			me = api::FreeImage_LoadFromMemory (r2x ,r1x->mP1) ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
			const auto r3x = api::FreeImage_GetImageType (me) ;
			_DYNAMIC_ASSERT_ (r3x == FIT_BITMAP) ;
		} ,[] (HFIBITMAP &me) {
			api::FreeImage_Unload (me) ;
		}) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (tmp)) ;
	}

	void compute_save_data (const AnyRef<void> &holder ,AutoBuffer<BYTE> &data ,const AnyRef<void> &option) const override {
		using HFIMEMORY = PTR<api::FIMEMORY> ;
		_DEBUG_ASSERT_ (!option.exist ()) ;
		const auto r1x = UniqueRef<HFIMEMORY> ([&] (HFIMEMORY &me) {
			me = api::FreeImage_OpenMemory () ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
		} ,[] (HFIMEMORY &me) {
			api::FreeImage_CloseMemory (me) ;
		}) ;
		const auto r2x = holder.rebind (ARGV<NATIVE_THIS>::null)->self ;
		const auto r3x = api::FreeImage_SaveToMemory (FIF_BMP ,r2x ,r1x.self) ;
		_DYNAMIC_ASSERT_ (r3x) ;
		auto rax = PACK<PTR<BYTE> ,VARY> () ;
		rax.mP1 = NULL ;
		rax.mP2 = VARY (0) ;
		const auto r4x = api::FreeImage_AcquireMemory (r1x.self ,DEPTR[rax.mP1] ,DEPTR[rax.mP2]) ;
		_DYNAMIC_ASSERT_ (r4x) ;
		if switch_once (TRUE) {
			if (LENGTH (rax.mP2) == 0)
				discard ;
			_DYNAMIC_ASSERT_ (rax.mP1 != NULL) ;
			_DYNAMIC_ASSERT_ (LENGTH (rax.mP2) >= 0 && LENGTH (rax.mP2) < VAR32_MAX) ;
		}
		data = AutoBuffer<BYTE> (LENGTH (rax.mP2)) ;
		BasicProc::mem_move (data.self ,PTRTOARR[rax.mP1] ,data.size ()) ;
	}

	void compute_load_data_file (AnyRef<void> &holder ,const String<STR> &file) const override {
		const auto r1x = StringProc::build_strs (ARGV<STRA>::null ,file) ;
		auto tmp = UniqueRef<HFIBITMAP> ([&] (HFIBITMAP &me) {
			const auto r2x = api::FreeImage_GetFileType (r1x.raw ().self) ;
			_DYNAMIC_ASSERT_ (r2x != FIF_UNKNOWN) ;
			me = api::FreeImage_Load (r2x ,r1x.raw ().self) ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
		} ,[] (HFIBITMAP &me) {
			api::FreeImage_Unload (me) ;
		}) ;
		if (api::FreeImage_GetBPP (tmp.self) == 24)
			return ;
		tmp = UniqueRef<HFIBITMAP> ([&] (HFIBITMAP &me) {
			me = api::FreeImage_ConvertTo24Bits (tmp.self) ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
		} ,[] (HFIBITMAP &me) {
			api::FreeImage_Unload (me) ;
		}) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (tmp)) ;
	}

	void compute_save_data_file (const AnyRef<void> &holder ,const String<STR> &file ,const AnyRef<void> &option) const override {
		_DEBUG_ASSERT_ (!option.exist ()) ;
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		const auto r2x = StringProc::build_strs (ARGV<STRA>::null ,file) ;
		const auto r3x = api::FreeImage_Save (FIF_JPEG ,r1x ,r2x.raw ().self) ;
		_DYNAMIC_ASSERT_ (r3x) ;
	}
} ;

template <>
class AbstractImage_Engine_FREEIMAGE<COLOR_BGRA>
	:public AbstractImage<COLOR_BGRA>::Abstract {
public:
	using HFIBITMAP = PTR<FIBITMAP> ;
	using NATIVE_THIS = UniqueRef<HFIBITMAP> ;

public:
 	implicit AbstractImage_Engine_FREEIMAGE () {
		_STATIC_ASSERT_ (_SIZEOF_ (DEF<decltype (DEREF[this])>) == _SIZEOF_ (Interface)) ;
		_STATIC_ASSERT_ (_ALIGNOF_ (DEF<decltype (DEREF[this])>) == _ALIGNOF_ (Interface)) ;
	}

	void compute_layout (AnyRef<void> &holder ,AbstractImage<COLOR_BGRA>::LAYOUT &layout) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		const auto r2x = api::FreeImage_GetBits (r1x) ;
		auto &r3x = _LOAD_UNSAFE_ (ARGV<ARR<COLOR_BGRA>>::null ,_ADDRESS_ (r2x)) ;
		layout.mImage = DEPTR[r3x] ;
		layout.mCX = LENGTH (api::FreeImage_GetWidth (r1x)) ;
		layout.mCY = LENGTH (api::FreeImage_GetHeight (r1x)) ;
		layout.mCW = layout.mCX ;
		layout.mCK = 0 ;
	}

	void compute_load_data (AnyRef<void> &holder ,const LENGTH &cx_ ,const LENGTH &cy_) const override {
		const auto r1x = cx_ * cy_ * 4 ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x >= 0 && r1x < VAR32_MAX) ;
		auto tmp = UniqueRef<HFIBITMAP> ([&] (HFIBITMAP &me) {
			me = api::FreeImage_Allocate (VAR32 (cx_) ,VAR32 (cy_) ,32) ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
		} ,[] (HFIBITMAP &me) {
			api::FreeImage_Unload (me) ;
		}) ;
		const auto r2x = COLOR_BGRA {0 ,0 ,0 ,0} ;
		api::FreeImage_FillBackground (tmp.self ,DEPTR[r2x] ,0) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (tmp)) ;
	}

	void compute_load_data (AnyRef<void> &holder ,const AutoBuffer<BYTE> &data) const override {
		using HFIMEMORY = PTR<api::FIMEMORY> ;
		auto tmp = UniqueRef<HFIBITMAP> ([&] (HFIBITMAP &me) {
			const auto r1x = UniqueRef<PACK<HFIMEMORY ,AutoBuffer<BYTE>>> ([&] (PACK<HFIMEMORY ,AutoBuffer<BYTE>> &me) {
				me.mP2 = data ;
				me.mP1 = api::FreeImage_OpenMemory (me.mP2.self ,VARY (me.mP2.size ())) ;
				_DYNAMIC_ASSERT_ (me.mP1 != NULL) ;
			} ,[] (PACK<HFIMEMORY ,AutoBuffer<BYTE>> &me) {
				api::FreeImage_CloseMemory (me.mP1) ;
			}) ;
			const auto r2x = api::FreeImage_GetFileTypeFromMemory (r1x->mP1) ;
			me = api::FreeImage_LoadFromMemory (r2x ,r1x->mP1) ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
			const auto r3x = api::FreeImage_GetImageType (me) ;
			_DYNAMIC_ASSERT_ (r3x == FIT_BITMAP) ;
		} ,[] (HFIBITMAP &me) {
			api::FreeImage_Unload (me) ;
		}) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (tmp)) ;
	}

	void compute_save_data (const AnyRef<void> &holder ,AutoBuffer<BYTE> &data ,const AnyRef<void> &option) const override {
		using HFIMEMORY = PTR<api::FIMEMORY> ;
		_DEBUG_ASSERT_ (!option.exist ()) ;
		const auto r1x = UniqueRef<HFIMEMORY> ([&] (HFIMEMORY &me) {
			me = api::FreeImage_OpenMemory () ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
		} ,[] (HFIMEMORY &me) {
			api::FreeImage_CloseMemory (me) ;
		}) ;
		const auto r2x = holder.rebind (ARGV<NATIVE_THIS>::null)->self ;
		const auto r3x = api::FreeImage_SaveToMemory (FIF_BMP ,r2x ,r1x.self) ;
		_DYNAMIC_ASSERT_ (r3x) ;
		auto rax = PACK<PTR<BYTE> ,VARY> () ;
		rax.mP1 = NULL ;
		rax.mP2 = VARY (0) ;
		const auto r4x = api::FreeImage_AcquireMemory (r1x.self ,DEPTR[rax.mP1] ,DEPTR[rax.mP2]) ;
		_DYNAMIC_ASSERT_ (r4x) ;
		if switch_once (TRUE) {
			if (LENGTH (rax.mP2) == 0)
				discard ;
			_DYNAMIC_ASSERT_ (rax.mP1 != NULL) ;
			_DYNAMIC_ASSERT_ (LENGTH (rax.mP2) >= 0 && LENGTH (rax.mP2) < VAR32_MAX) ;
		}
		data = AutoBuffer<BYTE> (LENGTH (rax.mP2)) ;
		BasicProc::mem_move (data.self ,PTRTOARR[rax.mP1] ,data.size ()) ;
	}

	void compute_load_data_file (AnyRef<void> &holder ,const String<STR> &file) const override {
		const auto r1x = StringProc::build_strs (ARGV<STRA>::null ,file) ;
		auto tmp = UniqueRef<HFIBITMAP> ([&] (HFIBITMAP &me) {
			const auto r2x = api::FreeImage_GetFileType (r1x.raw ().self) ;
			_DYNAMIC_ASSERT_ (r2x != FIF_UNKNOWN) ;
			me = api::FreeImage_Load (r2x ,r1x.raw ().self) ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
		} ,[] (HFIBITMAP &me) {
			api::FreeImage_Unload (me) ;
		}) ;
		if (api::FreeImage_GetBPP (tmp.self) == 32)
			return ;
		tmp = UniqueRef<HFIBITMAP> ([&] (HFIBITMAP &me) {
			me = api::FreeImage_ConvertTo32Bits (tmp.self) ;
			_DYNAMIC_ASSERT_ (me != NULL) ;
		} ,[] (HFIBITMAP &me) {
			api::FreeImage_Unload (me) ;
		}) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (tmp)) ;
	}

	void compute_save_data_file (const AnyRef<void> &holder ,const String<STR> &file ,const AnyRef<void> &option) const override {
		_DEBUG_ASSERT_ (!option.exist ()) ;
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		const auto r2x = StringProc::build_strs (ARGV<STRA>::null ,file) ;
		const auto r3x = api::FreeImage_Save (FIF_JPEG ,r1x ,r2x.raw ().self) ;
		_DYNAMIC_ASSERT_ (r3x) ;
	}
} ;
} ;