﻿#pragma once

#ifndef __CSC_IMAGES__
#error "∑(っ°Д° ;)っ : require 'csc_images.hpp'"
#endif

#ifdef __CSC__
#pragma push_macro ("self")
#pragma push_macro ("implicit")
#pragma push_macro ("leftvalue")
#pragma push_macro ("rightvalue")
#pragma push_macro ("imports")
#pragma push_macro ("exports")
#pragma push_macro ("switch_once")
#pragma push_macro ("discard")
#undef self
#undef implicit
#undef leftvalue
#undef rightvalue
#undef imports
#undef exports
#undef switch_once
#undef discard
#endif

#ifdef __CSC_DEPRECATED__
#ifdef _HAS_AUTO_PTR_ETC
#if (_HAS_AUTO_PTR_ETC == 0)
#include <random>
#include <algorithm>
#pragma push_macro ("random_shuffle")
#undef random_shuffle
#define random_shuffle(...) shuffle(_UNW_ (__VA_ARGS__) ,std::random_device ())
#endif
#endif
#endif

#ifdef __CSC_DEPRECATED__
#ifdef __CSC_COMPILER_MSVC__
#pragma warning (push)
#pragma warning (disable :4265)
#pragma warning (disable :4266)
#pragma warning (disable :4435)
#pragma warning (disable :4711)
#pragma warning (disable :4819)
#pragma warning (disable :4946)
#pragma warning (disable :4996)
#pragma warning (disable :6011)
#pragma warning (disable :6201)
#pragma warning (disable :6269)
#pragma warning (disable :6294)
#pragma warning (disable :6297)
#pragma warning (disable :6385)
#pragma warning (disable :26401)
#pragma warning (disable :26408)
#pragma warning (disable :26409)
#pragma warning (disable :26415)
#pragma warning (disable :26417)
#pragma warning (disable :26418)
#pragma warning (disable :26426)
#pragma warning (disable :26429)
#pragma warning (disable :26432)
#pragma warning (disable :26433)
#pragma warning (disable :26434)
#pragma warning (disable :26436)
#pragma warning (disable :26439)
#pragma warning (disable :26440)
#pragma warning (disable :26443)
#pragma warning (disable :26446)
#pragma warning (disable :26447)
#pragma warning (disable :26451)
#pragma warning (disable :26455)
#pragma warning (disable :26456)
#pragma warning (disable :26461)
#pragma warning (disable :26471)
#pragma warning (disable :26472)
#pragma warning (disable :26474)
#pragma warning (disable :26475)
#pragma warning (disable :26476)
#pragma warning (disable :26477)
#pragma warning (disable :26481)
#pragma warning (disable :26482)
#pragma warning (disable :26485)
#pragma warning (disable :26486)
#pragma warning (disable :26489)
#pragma warning (disable :26490)
#pragma warning (disable :26493)
#pragma warning (disable :26494)
#pragma warning (disable :26495)
#pragma warning (disable :26496)
#pragma warning (disable :26497)
#endif
#include <opencv2/opencv.hpp>
#ifdef __CSC_COMPILER_MSVC__
#pragma warning (pop)
#endif
#endif

#ifdef __CSC_DEPRECATED__
#ifdef _HAS_AUTO_PTR_ETC
#if (_HAS_AUTO_PTR_ETC == 0)
#undef random_shuffle
#pragma pop_macro ("random_shuffle")
#endif
#endif
#endif

#ifndef __OPENCV_ALL_HPP__
#ifndef OPENCV_ALL_HPP
#error "∑(っ°Д° ;)っ : require 'opencv2/opencv.hpp'"
#endif
#endif

#ifdef __CSC_DEPRECATED__
#ifdef __CSC_COMPILER_MSVC__
#ifndef use_comment_lib_opencv_world
#ifdef __CSC_DEBUG__
#define use_comment_lib_opencv_world "opencv_world" _STR_ (CV_MAJOR_VERSION) _STR_ (CV_MINOR_VERSION) _STR_ (CV_SUBMINOR_VERSION) "d.lib"
#endif
#endif

#ifndef use_comment_lib_opencv_world
#ifndef __CSC_DEBUG__
#define use_comment_lib_opencv_world "opencv_world" _STR_ (CV_MAJOR_VERSION) _STR_ (CV_MINOR_VERSION) _STR_ (CV_SUBMINOR_VERSION) ".lib"
#endif
#endif
#pragma comment (lib ,use_comment_lib_opencv_world)
#undef use_comment_lib_opencv_world
#endif
#endif

#ifdef __CSC__
#pragma pop_macro ("self")
#pragma pop_macro ("implicit")
#pragma pop_macro ("leftvalue")
#pragma pop_macro ("rightvalue")
#pragma pop_macro ("imports")
#pragma pop_macro ("exports")
#pragma pop_macro ("switch_once")
#pragma pop_macro ("discard")
#endif

namespace CSC {
namespace api {
using std::vector ;

using cv::Mat ;
using cv::_InputArray ;
using cv::IMREAD_COLOR ;
using cv::IMREAD_UNCHANGED ;
using cv::IMREAD_GRAYSCALE ;
using cv::IMREAD_REDUCED_GRAYSCALE_4 ;
using cv::IMREAD_REDUCED_GRAYSCALE_8 ;

using cv::imread ;
using cv::imwrite ;
using cv::imencode ;
using cv::imdecode ;
} ;

template <class>
class AbstractImage_Engine_OPENCV ;

template <>
class AbstractImage_Engine_OPENCV<COLOR_BGR>
	:public AbstractImage<COLOR_BGR>::Abstract {
private:
	using NATIVE_THIS = api::Mat ;
	using LAYOUT_PACK = typename AbstractImage<COLOR_BGR>::LAYOUT_PACK ;

public:
	implicit AbstractImage_Engine_OPENCV () = default ;

	void compute_layout (AnyRef<> &holder ,LAYOUT_PACK &layout) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		const auto r2x = _ADDRESS_ (r1x.data) ;
		const auto r3x = _UNSAFE_POINTER_CAST_ (ARGV<ARR<COLOR_BGR>>::null ,r2x) ;
		layout.mImage = r3x ;
		layout.mCX = LENGTH (r1x.cols) ;
		layout.mCY = LENGTH (r1x.rows) ;
		_DEBUG_ASSERT_ (r1x.step.p != NULL) ;
		layout.mCW = LENGTH (r1x.step.p[0]) / _SIZEOF_ (COLOR_BGR) ;
		layout.mCK = 0 ;
	}

	void compute_load_data (AnyRef<> &holder ,const LENGTH &cx_ ,const LENGTH &cy_) const override {
		const auto r1x = cx_ * cy_ * _SIZEOF_ (COLOR_BGR) ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x >= 0 && r1x < VAR32_MAX) ;
		auto rax = api::Mat (api::Mat::zeros (VAR32 (cy_) ,VAR32 (cx_) ,CV_8UC3)) ;
		_DYNAMIC_ASSERT_ (!rax.empty ()) ;
		_DYNAMIC_ASSERT_ (rax.type () == CV_8UC3) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (rax)) ;
	}

	void compute_load_data (AnyRef<> &holder ,const AutoBuffer<BYTE> &data) const override {
		_DEBUG_ASSERT_ (data.size () < VAR32_MAX) ;
		const auto r1x = api::_InputArray (data.self ,VAR32 (data.size ())) ;
		auto rax = api::imdecode (r1x ,api::IMREAD_COLOR) ;
		_DYNAMIC_ASSERT_ (!rax.empty ()) ;
		_DYNAMIC_ASSERT_ (rax.type () == CV_8UC3) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (rax)) ;
	}

	void compute_save_data (const AnyRef<> &holder ,AutoBuffer<BYTE> &data ,const AnyRef<> &option) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		auto rax = AutoRef<api::vector<uchar>>::make () ;
		const auto r2x = api::vector<VAR32> () ;
		auto &r3x = _SWITCH_ (
			(option.exist ()) ? option.rebind (ARGV<api::vector<VAR32>>::null).self :
			r2x) ;
		api::imencode (_PCSTRA_ ("bmp").self ,r1x ,rax.self ,r3x) ;
		_DYNAMIC_ASSERT_ (rax->size () < VAR32_MAX) ;
		data = AutoBuffer<BYTE> (rax->size ()) ;
		for (auto &&i : _RANGE_ (0 ,data.size ()))
			data[i] = BYTE (rax.self[i]) ;
	}

	void compute_load_data_file (AnyRef<> &holder ,const String<STR> &file) const override {
		const auto r1x = StringProc::build_strs (ARGV<STRA>::null ,file) ;
		auto rax = api::imread (r1x.raw ().self ,api::IMREAD_COLOR) ;
		_DYNAMIC_ASSERT_ (!rax.empty ()) ;
		_DYNAMIC_ASSERT_ (rax.type () == CV_8UC3) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (rax)) ;
	}

	void compute_save_data_file (const AnyRef<> &holder ,const String<STR> &file ,const AnyRef<> &option) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		const auto r2x = StringProc::build_strs (ARGV<STRA>::null ,file) ;
		const auto r3x = api::vector<VAR32> () ;
		auto &r4x = _SWITCH_ (
			(option.exist ()) ? option.rebind (ARGV<api::vector<VAR32>>::null).self :
			r3x) ;
		const auto r5x = api::imwrite (r2x.raw ().self ,r1x ,r4x) ;
		_DYNAMIC_ASSERT_ (r5x) ;
	}
} ;

template <>
class AbstractImage_Engine_OPENCV<COLOR_BGRA>
	:public AbstractImage<COLOR_BGRA>::Abstract {
private:
	using NATIVE_THIS = api::Mat ;
	using LAYOUT_PACK = typename AbstractImage<COLOR_BGRA>::LAYOUT_PACK ;

public:
	implicit AbstractImage_Engine_OPENCV () = default ;

	void compute_layout (AnyRef<> &holder ,LAYOUT_PACK &layout) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		const auto r2x = _ADDRESS_ (r1x.data) ;
		const auto r3x = _UNSAFE_POINTER_CAST_ (ARGV<ARR<COLOR_BGRA>>::null ,r2x) ;
		layout.mImage = r3x ;
		layout.mCX = LENGTH (r1x.cols) ;
		layout.mCY = LENGTH (r1x.rows) ;
		_DEBUG_ASSERT_ (r1x.step.p != NULL) ;
		layout.mCW = LENGTH (r1x.step.p[0]) / _SIZEOF_ (COLOR_BGRA) ;
		layout.mCK = 0 ;
	}

	void compute_load_data (AnyRef<> &holder ,const LENGTH &cx_ ,const LENGTH &cy_) const override {
		const auto r1x = cx_ * cy_ * _SIZEOF_ (COLOR_BGRA) ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x >= 0 && r1x < VAR32_MAX) ;
		auto rax = api::Mat (api::Mat::zeros (VAR32 (cy_) ,VAR32 (cx_) ,CV_8UC4)) ;
		_DYNAMIC_ASSERT_ (!rax.empty ()) ;
		_DYNAMIC_ASSERT_ (rax.type () == CV_8UC4) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (rax)) ;
	}

	void compute_load_data (AnyRef<> &holder ,const AutoBuffer<BYTE> &data) const override {
		_DEBUG_ASSERT_ (data.size () < VAR32_MAX) ;
		const auto r1x = api::_InputArray (data.self ,VAR32 (data.size ())) ;
		auto rax = api::imdecode (r1x ,api::IMREAD_COLOR) ;
		_DYNAMIC_ASSERT_ (!rax.empty ()) ;
		_DYNAMIC_ASSERT_ (rax.type () == CV_8UC4) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (rax)) ;
	}

	void compute_save_data (const AnyRef<> &holder ,AutoBuffer<BYTE> &data ,const AnyRef<> &option) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		auto rax = AutoRef<api::vector<uchar>>::make () ;
		const auto r2x = api::vector<VAR32> () ;
		auto &r3x = _SWITCH_ (
			(option.exist ()) ? option.rebind (ARGV<api::vector<VAR32>>::null).self :
			r2x) ;
		api::imencode (_PCSTRA_ ("bmp").self ,r1x ,rax.self ,r3x) ;
		_DYNAMIC_ASSERT_ (rax->size () < VAR32_MAX) ;
		data = AutoBuffer<BYTE> (rax->size ()) ;
		for (auto &&i : _RANGE_ (0 ,data.size ()))
			data[i] = BYTE (rax.self[i]) ;
	}

	void compute_load_data_file (AnyRef<> &holder ,const String<STR> &file) const override {
		const auto r1x = StringProc::build_strs (ARGV<STRA>::null ,file) ;
		auto rax = api::imread (r1x.raw ().self ,api::IMREAD_UNCHANGED) ;
		_DYNAMIC_ASSERT_ (!rax.empty ()) ;
		_DYNAMIC_ASSERT_ (rax.type () == CV_8UC4) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (rax)) ;
	}

	void compute_save_data_file (const AnyRef<> &holder ,const String<STR> &file ,const AnyRef<> &option) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		const auto r2x = StringProc::build_strs (ARGV<STRA>::null ,file) ;
		const auto r3x = api::vector<VAR32> () ;
		auto &r4x = _SWITCH_ (
			(option.exist ()) ? option.rebind (ARGV<api::vector<VAR32>>::null).self :
			r3x) ;
		const auto r5x = api::imwrite (r2x.raw ().self ,r1x ,r4x) ;
		_DYNAMIC_ASSERT_ (r5x) ;
	}
} ;

template <>
class AbstractImage_Engine_OPENCV<COLOR_GRAY>
	:public AbstractImage<COLOR_GRAY>::Abstract {
private:
	using NATIVE_THIS = api::Mat ;
	using LAYOUT_PACK = typename AbstractImage<COLOR_GRAY>::LAYOUT_PACK ;

public:
	implicit AbstractImage_Engine_OPENCV () = default ;

	void compute_layout (AnyRef<> &holder ,LAYOUT_PACK &layout) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		const auto r2x = _ADDRESS_ (r1x.data) ;
		const auto r3x = _UNSAFE_POINTER_CAST_ (ARGV<ARR<COLOR_GRAY>>::null ,r2x) ;
		layout.mImage = r3x ;
		layout.mCX = LENGTH (r1x.cols) ;
		layout.mCY = LENGTH (r1x.rows) ;
		_DEBUG_ASSERT_ (r1x.step.p != NULL) ;
		layout.mCW = LENGTH (r1x.step.p[0]) / _SIZEOF_ (COLOR_GRAY) ;
		layout.mCK = 0 ;
	}

	void compute_load_data (AnyRef<> &holder ,const LENGTH &cx_ ,const LENGTH &cy_) const override {
		const auto r1x = cx_ * cy_ * _SIZEOF_ (COLOR_GRAY) ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x >= 0 && r1x < VAR32_MAX) ;
		auto rax = api::Mat (api::Mat::zeros (VAR32 (cy_) ,VAR32 (cx_) ,CV_8UC1)) ;
		_DYNAMIC_ASSERT_ (!rax.empty ()) ;
		_DYNAMIC_ASSERT_ (rax.type () == CV_8UC1) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (rax)) ;
	}

	void compute_load_data (AnyRef<> &holder ,const AutoBuffer<BYTE> &data) const override {
		_DEBUG_ASSERT_ (data.size () < VAR32_MAX) ;
		const auto r1x = api::_InputArray (data.self ,VAR32 (data.size ())) ;
		auto rax = api::imdecode (r1x ,api::IMREAD_COLOR) ;
		_DYNAMIC_ASSERT_ (!rax.empty ()) ;
		_DYNAMIC_ASSERT_ (rax.type () == CV_8UC1) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (rax)) ;
	}

	void compute_save_data (const AnyRef<> &holder ,AutoBuffer<BYTE> &data ,const AnyRef<> &option) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		auto rax = AutoRef<api::vector<uchar>>::make () ;
		const auto r2x = api::vector<VAR32> () ;
		auto &r3x = _SWITCH_ (
			(option.exist ()) ? option.rebind (ARGV<api::vector<VAR32>>::null).self :
			r2x) ;
		api::imencode (_PCSTRA_ ("bmp").self ,r1x ,rax.self ,r3x) ;
		_DYNAMIC_ASSERT_ (rax->size () < VAR32_MAX) ;
		data = AutoBuffer<BYTE> (rax->size ()) ;
		for (auto &&i : _RANGE_ (0 ,data.size ()))
			data[i] = BYTE (rax.self[i]) ;
	}

	void compute_load_data_file (AnyRef<> &holder ,const String<STR> &file) const override {
		const auto r1x = StringProc::build_strs (ARGV<STRA>::null ,file) ;
		auto rax = api::imread (r1x.raw ().self ,api::IMREAD_GRAYSCALE) ;
		_DYNAMIC_ASSERT_ (!rax.empty ()) ;
		_DYNAMIC_ASSERT_ (rax.type () == CV_8UC1) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (rax)) ;
	}

	void compute_save_data_file (const AnyRef<> &holder ,const String<STR> &file ,const AnyRef<> &option) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		const auto r2x = StringProc::build_strs (ARGV<STRA>::null ,file) ;
		const auto r3x = api::vector<VAR32> () ;
		auto &r4x = _SWITCH_ (
			(option.exist ()) ? option.rebind (ARGV<api::vector<VAR32>>::null).self :
			r3x) ;
		const auto r5x = api::imwrite (r2x.raw ().self ,r1x ,r4x) ;
		_DYNAMIC_ASSERT_ (r5x) ;
	}
} ;

template <>
class AbstractImage_Engine_OPENCV<COLOR_GRAY32>
	:public AbstractImage<COLOR_GRAY32>::Abstract {
private:
	using NATIVE_THIS = api::Mat ;
	using LAYOUT_PACK = typename AbstractImage<COLOR_GRAY32>::LAYOUT_PACK ;

public:
	implicit AbstractImage_Engine_OPENCV () = default ;

	void compute_layout (AnyRef<> &holder ,LAYOUT_PACK &layout) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		const auto r2x = _ADDRESS_ (r1x.data) ;
		const auto r3x = _UNSAFE_POINTER_CAST_ (ARGV<ARR<COLOR_GRAY32>>::null ,r2x) ;
		layout.mImage = r3x ;
		layout.mCX = LENGTH (r1x.cols) ;
		layout.mCY = LENGTH (r1x.rows) ;
		_DEBUG_ASSERT_ (r1x.step.p != NULL) ;
		layout.mCW = LENGTH (r1x.step.p[0]) / _SIZEOF_ (COLOR_GRAY32) ;
		layout.mCK = 0 ;
	}

	void compute_load_data (AnyRef<> &holder ,const LENGTH &cx_ ,const LENGTH &cy_) const override {
		const auto r1x = cx_ * cy_ * _SIZEOF_ (COLOR_GRAY32) ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x >= 0 && r1x < VAR32_MAX) ;
		auto rax = api::Mat (api::Mat::zeros (VAR32 (cy_) ,VAR32 (cx_) ,CV_32FC1)) ;
		_DYNAMIC_ASSERT_ (!rax.empty ()) ;
		_DYNAMIC_ASSERT_ (rax.type () == CV_32FC1) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (rax)) ;
	}

	void compute_load_data (AnyRef<> &holder ,const AutoBuffer<BYTE> &data) const override {
		_DEBUG_ASSERT_ (data.size () < VAR32_MAX) ;
		const auto r1x = api::_InputArray (data.self ,VAR32 (data.size ())) ;
		auto rax = api::imdecode (r1x ,api::IMREAD_COLOR) ;
		_DYNAMIC_ASSERT_ (!rax.empty ()) ;
		_DYNAMIC_ASSERT_ (rax.type () == CV_32FC1) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (rax)) ;
	}

	void compute_save_data (const AnyRef<> &holder ,AutoBuffer<BYTE> &data ,const AnyRef<> &option) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		auto rax = AutoRef<api::vector<uchar>>::make () ;
		const auto r2x = api::vector<VAR32> () ;
		auto &r3x = _SWITCH_ (
			(option.exist ()) ? option.rebind (ARGV<api::vector<VAR32>>::null).self :
			r2x) ;
		api::imencode (_PCSTRA_ ("bmp").self ,r1x ,rax.self ,r3x) ;
		_DYNAMIC_ASSERT_ (rax->size () < VAR32_MAX) ;
		data = AutoBuffer<BYTE> (rax->size ()) ;
		for (auto &&i : _RANGE_ (0 ,data.size ()))
			data[i] = BYTE (rax.self[i]) ;
	}

	void compute_load_data_file (AnyRef<> &holder ,const String<STR> &file) const override {
		const auto r1x = StringProc::build_strs (ARGV<STRA>::null ,file) ;
		auto rax = api::imread (r1x.raw ().self ,api::IMREAD_REDUCED_GRAYSCALE_4) ;
		_DYNAMIC_ASSERT_ (!rax.empty ()) ;
		_DYNAMIC_ASSERT_ (rax.type () == CV_32FC1) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (rax)) ;
	}

	void compute_save_data_file (const AnyRef<> &holder ,const String<STR> &file ,const AnyRef<> &option) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		const auto r2x = StringProc::build_strs (ARGV<STRA>::null ,file) ;
		const auto r3x = api::vector<VAR32> () ;
		auto &r4x = _SWITCH_ (
			(option.exist ()) ? option.rebind (ARGV<api::vector<VAR32>>::null).self :
			r3x) ;
		const auto r5x = api::imwrite (r2x.raw ().self ,r1x ,r4x) ;
		_DYNAMIC_ASSERT_ (r5x) ;
	}
} ;

template <>
class AbstractImage_Engine_OPENCV<COLOR_GRAY64>
	:public AbstractImage<COLOR_GRAY64>::Abstract {
private:
	using NATIVE_THIS = api::Mat ;
	using LAYOUT_PACK = typename AbstractImage<COLOR_GRAY64>::LAYOUT_PACK ;

public:
	implicit AbstractImage_Engine_OPENCV () = default ;

	void compute_layout (AnyRef<> &holder ,LAYOUT_PACK &layout) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		const auto r2x = _ADDRESS_ (r1x.data) ;
		const auto r3x = _UNSAFE_POINTER_CAST_ (ARGV<ARR<COLOR_GRAY64>>::null ,r2x) ;
		layout.mImage = r3x ;
		layout.mCX = LENGTH (r1x.cols) ;
		layout.mCY = LENGTH (r1x.rows) ;
		_DEBUG_ASSERT_ (r1x.step.p != NULL) ;
		layout.mCW = LENGTH (r1x.step.p[0]) / _SIZEOF_ (COLOR_GRAY64) ;
		layout.mCK = 0 ;
	}

	void compute_load_data (AnyRef<> &holder ,const LENGTH &cx_ ,const LENGTH &cy_) const override {
		const auto r1x = cx_ * cy_ * _SIZEOF_ (COLOR_GRAY64) ;
		_STATIC_UNUSED_ (r1x) ;
		_DEBUG_ASSERT_ (r1x >= 0 && r1x < VAR32_MAX) ;
		auto rax = api::Mat (api::Mat::zeros (VAR32 (cy_) ,VAR32 (cx_) ,CV_64FC1)) ;
		_DYNAMIC_ASSERT_ (!rax.empty ()) ;
		_DYNAMIC_ASSERT_ (rax.type () == CV_64FC1) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (rax)) ;
	}

	void compute_load_data (AnyRef<> &holder ,const AutoBuffer<BYTE> &data) const override {
		_DEBUG_ASSERT_ (data.size () < VAR32_MAX) ;
		const auto r1x = api::_InputArray (data.self ,VAR32 (data.size ())) ;
		auto rax = api::imdecode (r1x ,api::IMREAD_COLOR) ;
		_DYNAMIC_ASSERT_ (!rax.empty ()) ;
		_DYNAMIC_ASSERT_ (rax.type () == CV_64FC1) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (rax)) ;
	}

	void compute_save_data (const AnyRef<> &holder ,AutoBuffer<BYTE> &data ,const AnyRef<> &option) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		auto rax = AutoRef<api::vector<uchar>>::make () ;
		const auto r2x = api::vector<VAR32> () ;
		auto &r3x = _SWITCH_ (
			(option.exist ()) ? option.rebind (ARGV<api::vector<VAR32>>::null).self :
			r2x) ;
		api::imencode (_PCSTRA_ ("bmp").self ,r1x ,rax.self ,r3x) ;
		_DYNAMIC_ASSERT_ (rax->size () < VAR32_MAX) ;
		data = AutoBuffer<BYTE> (rax->size ()) ;
		for (auto &&i : _RANGE_ (0 ,data.size ()))
			data[i] = BYTE (rax.self[i]) ;
	}

	void compute_load_data_file (AnyRef<> &holder ,const String<STR> &file) const override {
		const auto r1x = StringProc::build_strs (ARGV<STRA>::null ,file) ;
		auto rax = api::imread (r1x.raw ().self ,api::IMREAD_REDUCED_GRAYSCALE_8) ;
		_DYNAMIC_ASSERT_ (!rax.empty ()) ;
		_DYNAMIC_ASSERT_ (rax.type () == CV_64FC1) ;
		holder = AnyRef<NATIVE_THIS>::make (_MOVE_ (rax)) ;
	}

	void compute_save_data_file (const AnyRef<> &holder ,const String<STR> &file ,const AnyRef<> &option) const override {
		auto &r1x = holder.rebind (ARGV<NATIVE_THIS>::null).self ;
		const auto r2x = StringProc::build_strs (ARGV<STRA>::null ,file) ;
		const auto r3x = api::vector<VAR32> () ;
		auto &r4x = _SWITCH_ (
			(option.exist ()) ? option.rebind (ARGV<api::vector<VAR32>>::null).self :
			r3x) ;
		const auto r5x = api::imwrite (r2x.raw ().self ,r1x ,r4x) ;
		_DYNAMIC_ASSERT_ (r5x) ;
	}
} ;
} ;