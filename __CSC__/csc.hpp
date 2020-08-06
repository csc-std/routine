﻿#pragma once

#ifndef __CSC__
#define __CSC__
#endif

#ifdef _DEBUG
#define __CSC_DEBUG__
#endif

#ifdef _UNITTEST
#define __CSC_UNITTEST__
#endif

#ifdef _DEPRECATED
#define __CSC_DEPRECATED__
#endif

#ifdef __clang__
#define __CSC_COMPILER_CLANG__
#elif defined __GNUC__
#define __CSC_COMPILER_GNUC__
#elif defined _MSC_VER
#define __CSC_COMPILER_MSVC__
#else
#error "∑(っ°Д° ;)っ : unsupported"
#endif

#if defined (linux) || defined (__linux) || defined (__linux__)
#define __CSC_SYSTEM_LINUX__
#elif defined (WIN32) || defined (_WIN32) || defined (__WIN32__)
#define __CSC_SYSTEM_WINDOWS__
#else
#error "∑(っ°Д° ;)っ : unsupported"
#endif

#if defined (_M_IX86) || defined (__i386__) || defined (__i386)
#define __CSC_PLATFORM_X86__
#elif defined (_M_X64) || defined (_M_AMD64) || defined (__x86_64) || defined (__amd64)
#define __CSC_PLATFORM_X64__
#elif defined (_M_ARM) || defined (__arm__)
#define __CSC_PLATFORM_ARM__
#elif defined (_M_ARM64) || defined (__aarch64__)
#define __CSC_PLATFORM_ARM64__
#elif defined (_M_IA64) || defined (__ia64__)
#define __CSC_PLATFORM_IA64__
#else
#error "∑(っ°Д° ;)っ : unsupported"
#endif

#ifdef _WINEXE
#define __CSC_TARGET_EXE__
#elif defined _WINDLL
#define __CSC_TARGET_DLL__
#elif defined _WINLIB
#define __CSC_TARGET_LIB__
#else
#define __CSC_TARGET_EXE__
#endif

#ifdef _WIN64
#define __CSC_CONFIG_VAR64__
#define __CSC_CONFIG_VAL64__
#elif defined _WIN32
#define __CSC_CONFIG_VAR32__
#define __CSC_CONFIG_VAL32__
#else
#define __CSC_CONFIG_VAR64__
#define __CSC_CONFIG_VAL64__
#endif

#ifdef _UNICODE
#define __CSC_CONFIG_STRW__
#elif defined _MBCS
#define __CSC_CONFIG_STRA__
#else
#define __CSC_CONFIG_STRA__
#endif

#ifdef __CSC_COMPILER_MSVC__
#pragma warning (disable :4068) //@info: warning C4068: unknown pragma
#pragma warning (disable :4065) //@info: warning C4065: switch statement contains 'default' but no 'case' labels
#pragma warning (disable :4619) //@info: warning C4619: #pragma warning: there is no warning number 'xxx'
#pragma warning (disable :4100) //@info: warning C4100: 'xxx': unreferenced formal parameter
#pragma warning (disable :4180) //@info: warning C4180: qualifier applied to function type has no meaning; ignored
#pragma warning (disable :4365) //@info: warning C4365: 'xxx': conversion from 'xxx' to 'xxx', signed/unsigned mismatch
#pragma warning (disable :4371) //@info: warning C4371: 'xxx': layout of class may have changed from a previous version of the compiler due to better packing of member 'xxx'
#pragma warning (disable :4435) //@info: warning C4435: 'xxx': Object layout under /vd2 will change due to virtual base 'xxx'
#pragma warning (disable :4464) //@info: warning C4464: relative include path contains '..'
#pragma warning (disable :4505) //@info: warning C4505: 'xxx': unreferenced local function has been removed
#pragma warning (disable :4514) //@info: warning C4514: 'xxx': unreferenced inline function has been removed
#pragma warning (disable :4571) //@info: warning C4571: Informational: catch(...) semantics changed since Visual C++ 7.1; structured exceptions (SEH) are no longer caught
#pragma warning (disable :4574) //@info: warning C4574: 'xxx' is defined to be '0': did you mean to use '#if xxx'?
#pragma warning (disable :4668) //@info: warning C4668: 'xxx' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
#pragma warning (disable :4710) //@info: warning C4710: 'xxx': function not inlined
#pragma warning (disable :4711) //@info: warning C4711: function 'xxx' selected for automatic inline expansion
#pragma warning (disable :4738) //@info: warning C4738: storing 32-bit float result in memory, possible loss of performance
#pragma warning (disable :4774) //@info: warning C4774: 'xxx' : format string expected in argument ? is not a string literal
#pragma warning (disable :4324) //@info: warning C4324: 'xxx': structure was padded due to alignment specifier
#pragma warning (disable :4820) //@info: warning C4820: 'xxx': 'xxx' bytes padding added after data member 'xxx'
#pragma warning (disable :4623) //@info: warning C4623: 'xxx': default constructor was implicitly defined as deleted
#pragma warning (disable :4624) //@info: warning C4624: 'xxx': destructor was implicitly defined as deleted
#pragma warning (disable :4625) //@info: warning C4625: 'xxx': copy constructor was implicitly defined as deleted
#pragma warning (disable :4626) //@info: warning C4626: 'xxx': assignment operator was implicitly defined as deleted
#pragma warning (disable :5026) //@info: warning C5026: 'xxx': move constructor was implicitly defined as deleted
#pragma warning (disable :5027) //@info: warning C5027: 'xxx': move assignment operator was implicitly defined as deleted
#pragma warning (disable :5045) //@info: warning C5045: Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
#endif

#ifdef __CSC_DEPRECATED__
#ifdef __CSC_COMPILER_MSVC__
//@info: see also 'https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md'
#pragma warning (default :26401) //@info: warning C26401: Do not delete a raw pointer that is not an owner<T> (i.11).
#pragma warning (default :26403) //@info: warning C26403: Reset or explicitly delete an owner<T> pointer 'xxx' (r.3).
#pragma warning (default :26406) //@info: warning C26406: Do not assign a raw pointer to an owner<T> (r.3).
#pragma warning (default :26409) //@info: warning C26409: Avoid calling new and delete explicitly, use stl::make_unique<T> instead (r.11).
#pragma warning (default :26410) //@info: warning C26410: The parameter 'xxx' is a reference to const unique pointer, use const T* or const T& instead (r.32).
#pragma warning (default :26411) //@info: warning C26411: The parameter 'xxx' is a reference to unique pointer and it is never reassigned or reset, use T* or T& instead (r.33).
#pragma warning (default :26415) //@info: warning C26415: Smart pointer parameter 'xxx' is used only to access contained pointer. Use T* or T& instead (r.30).
#pragma warning (default :26416) //@info: warning C26416: Shared pointer parameter 'xxx' is passed by rvalue reference. Pass by value instead (r.34).
#pragma warning (default :26426) //@info: warning C26426: Global initializer calls a non-constexpr function 'xxx' (i.22).
#pragma warning (default :26429) //@info: warning C26429: Symbol 'xxx' is never tested for nullness, it can be marked as not_null (f.23).
#pragma warning (default :26432) //@info: warning C26432: If you define or delete any default operation in the type 'xxx', define or delete them all (c.21).
#pragma warning (default :26434) //@info: warning C26434: Function 'xxx' hides a non-virtual function 'xxx' (c.128).
#pragma warning (default :26435) //@info: warning C26435: Function 'xxx' should specify exactly one of 'virtual', 'override', or 'final' (c.128).
#pragma warning (default :26439) //@info: warning C26439: This kind of function may not throw. Declare it 'noexcept' (f.6).
#pragma warning (default :26440) //@info: warning C26440: Function 'xxx' can be declared 'noexcept' (f.6).
#pragma warning (default :26443) //@info: warning C26443: Overriding destructor should not use explicit 'override' or 'virtual' specifiers (c.128).
#pragma warning (default :26446) //@info: warning C26446: Prefer to use gsl::at() instead of unchecked subscript operator (bounds.4).
#pragma warning (default :26447) //@info: warning C26447: The function is declared 'noexcept' but calls function 'xxx' which may throw exceptions (f.6).
#pragma warning (default :26455) //@info: warning C26455: Default constructor may not throw. Declare it 'noexcept' (f.6).
#pragma warning (default :26460) //@info: warning C26460: The reference argument 'xxx' for function 'xxx' can be marked as const (con.3).
#pragma warning (default :26466) //@info: warning C26466: Don't use static_cast downcasts. A cast from a polymorphic type should use dynamic_cast (type.2).
#pragma warning (default :26471) //@info: warning C26471: Don't use reinterpret_cast. A cast from void* can use static_cast (type.1).
#pragma warning (default :26473) //@info: warning C26473: Don't cast between pointer types where the source type and the target type are the same (type.1).
#pragma warning (default :26475) //@info: warning C26475: Do not use function style C-casts (es.49).
#pragma warning (default :26481) //@info: warning C26481: Don't use pointer arithmetic. Use span instead (bounds.1).
#pragma warning (default :26482) //@info: warning C26482: Only index into arrays using constant expressions (bounds.2).
#pragma warning (default :26485) //@info: warning C26485: Expression 'xxx': No array to pointer decay (bounds.3).
#pragma warning (default :26486) //@info: warning C26486: Don't pass a pointer that may be invalid to a function. Parameter ? 'xxx' in call to 'xxx' may be invalid (lifetime.1).
#pragma warning (default :26487) //@info: warning C26487: Don't return a pointer that may be invalid (lifetime.1).
#pragma warning (default :26489) //@info: warning C26489: Don't dereference a pointer that may be invalid: 'xxx'. 'xxx' may have been invalidated at line ? (lifetime.1).
#pragma warning (default :26490) //@info: warning C26490: Don't use reinterpret_cast (type.1).
#pragma warning (default :26491) //@info: warning C26491: Don't use static_cast downcasts (type.2).
#pragma warning (default :26493) //@info: warning C26493: Don't use C-style casts (type.4).
#pragma warning (default :26495) //@info: warning C26495: Variable 'xxx' is uninitialized. Always initialize a member variable (type.6).
#pragma warning (default :26496) //@info: warning C26496: The variable 'xxx' is assigned only once, mark it as const (con.4).
#endif
#endif

#include <yvals.h>

#ifdef __CSC__
#ifdef self
#error "∑(っ°Д° ;)っ : defined 'self'"
#endif
#define self to ()

#ifdef implicit
#error "∑(っ°Д° ;)っ : defined 'implicit'"
#endif
#define implicit

#ifdef side_effects
#error "∑(っ°Д° ;)っ : defined 'side_effects'"
#endif
#define side_effects

#ifdef leftvalue
#error "∑(っ°Д° ;)っ : defined 'leftvalue'"
#endif
#define leftvalue &

#ifdef rightvalue
#error "∑(っ°Д° ;)っ : defined 'leftvalue'"
#endif
#define rightvalue &&

#ifdef imports
#error "∑(っ°Д° ;)っ : defined 'imports'"
#endif
#define imports static

#ifdef exports
#error "∑(っ°Д° ;)っ : defined 'exports'"
#endif
#define exports

#ifdef switch_once
#error "∑(っ°Д° ;)っ : defined 'switch_once'"
#endif
#define switch_once _SWITCH_ONCE_

#ifdef discard
#error "∑(っ°Д° ;)っ : defined 'discard'"
#endif
#define discard break
#endif

#ifdef _HAS_CXX17
#if _HAS_CXX17
#define __CSC_CXX_LATEST__
#endif
#endif

namespace CSC {
/*
*	MIT License
*
*	Copyright (c) 2018 csc-std
*
*	Permission is hereby granted, free of charge, to any person obtaining a copy
*	of this software and associated documentation files (the "Software"), to deal
*	in the Software without restriction, including without limitation the rights
*	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*	copies of the Software, and to permit persons to whom the Software is
*	furnished to do so, subject to the following conditions:
*
*	The above copyright notice and this permission notice shall be included in all
*	copies or substantial portions of the Software.
*
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*	SOFTWARE.
*/

#define M_DATE __DATE__
#define M_HOUR __TIME__
#define M_FILE __FILE__
#define M_LINE _STR_ (__LINE__)

#ifdef __CSC_COMPILER_MSVC__
#define M_FUNC __FUNCSIG__
#endif

#ifdef __CSC_COMPILER_GNUC__
#define M_FUNC __PRETTY_FUNCTION__
#endif

#ifdef __CSC_COMPILER_CLANG__
#define M_FUNC __PRETTY_FUNCTION__
#endif

#ifdef __CSC_COMPILER_MSVC__
#define DLLABI_IMPORT __declspec (dllimport)
#define DLLABI_EXPORT __declspec (dllexport)
#define DLLABI_API __stdcall
#define DLLABI_NATIVE extern "C"
#endif

#ifdef __CSC_COMPILER_GNUC__
#define DLLABI_IMPORT
#define DLLABI_EXPORT __attribute__ ((visibility ("default")))
#define DLLABI_API
#define DLLABI_NATIVE extern "C"
#endif

#ifdef __CSC_COMPILER_CLANG__
#define DLLABI_IMPORT
#define DLLABI_EXPORT __attribute__ ((visibility ("default")))
#define DLLABI_API
#define DLLABI_NATIVE extern "C"
#endif

#define _UNWIND_IMPL_(...) __VA_ARGS__
#define _UNW_(...) _UNWIND_IMPL_(__VA_ARGS__)
#define _STRINGIZE_IMPL_(...) #__VA_ARGS__
#define _STR_(...) _STRINGIZE_IMPL_(__VA_ARGS__)
#define _CONCAT_IMPL_(arg ,arg_) arg##arg_
#define _CAT_(arg ,arg_) _CONCAT_IMPL_(arg ,arg_)

#define _STATIC_ASSERT_(...) static_assert ((_UNW_ (__VA_ARGS__)) ,"static_assert failed : " _STR_ (__VA_ARGS__))

#define _STATIC_WARNING_(...)

#define _STATIC_UNUSED_(...) (void) _UNW_ (__VA_ARGS__) ;

#ifdef __CSC_COMPILER_MSVC__
#define _DYNAMIC_ASSERT_(...) do { if (!(_UNW_ (__VA_ARGS__))) CSC::Exception (_PCSTR_ ("dynamic_assert failed : " _STR_ (__VA_ARGS__) " : at " M_FUNC " in " M_FILE " ," M_LINE)).raise () ; } while (FALSE)
#endif

#ifdef __CSC_COMPILER_GNUC__
#define _DYNAMIC_ASSERT_(...) do { struct ARGVPL ; if (!(_UNW_ (__VA_ARGS__))) CSC::Exception (CSC::Plain<CSC::STR> (CSC::ARGV<ARGVPL>::null ,"dynamic_assert failed : " _STR_ (__VA_ARGS__) " : at " ,M_FUNC ," in " ,M_FILE ," ," ,M_LINE)).raise () ; } while (FALSE)
#endif

#ifdef __CSC_COMPILER_CLANG__
#define _DYNAMIC_ASSERT_(...) do { struct ARGVPL ; if (!(_UNW_ (__VA_ARGS__))) CSC::Exception (CSC::Plain<CSC::STR> (CSC::ARGV<ARGVPL>::null ,"dynamic_assert failed : " _STR_ (__VA_ARGS__) " : at " ,M_FUNC ," in " ,M_FILE ," ," ,M_LINE)).raise () ; } while (FALSE)
#endif

#ifdef __CSC_DEBUG__
#ifdef __CSC_COMPILER_MSVC__
#define _DEBUG_ASSERT_(...) do { if (!(_UNW_ (__VA_ARGS__))) __debugbreak () ; } while (FALSE)
#endif

#ifdef __CSC_COMPILER_GNUC__
#define _DEBUG_ASSERT_(...) do { if (!(_UNW_ (__VA_ARGS__))) __builtin_trap () ; } while (FALSE)
#endif

#ifdef __CSC_COMPILER_CLANG__
#define _DEBUG_ASSERT_(...) do { if (!(_UNW_ (__VA_ARGS__))) assert (FALSE) ; } while (FALSE)
#endif
#endif

#ifndef __CSC_DEBUG__
#ifdef __CSC_UNITTEST__
#define _DEBUG_ASSERT_ _DYNAMIC_ASSERT_
#endif
#endif

#ifndef _DEBUG_ASSERT_
#define _DEBUG_ASSERT_(...) do {} while (FALSE)
#endif

#ifdef __CSC_UNITTEST__
#ifdef __CSC_COMPILER_MSVC__
#define _UNITTEST_WATCH_(...) do { struct ARGVPL ; CSC::GlobalWatch::done (CSC::ARGV<ARGVPL>::null ,_PCSTR_ (_STR_ (__VA_ARGS__)) ,(_UNW_ (__VA_ARGS__))) ; } while (FALSE)
#endif
#endif

#ifndef _UNITTEST_WATCH_
#define _UNITTEST_WATCH_(...) do {} while (FALSE)
#endif

#define ANONYMOUS _CAT_ (_anonymous_ ,__LINE__)

#define _SWITCH_ONCE_(arg) (arg) goto ANONYMOUS ; while (CSC::U::OPERATOR_ONCE::invoke (arg)) ANONYMOUS:

#ifdef FALSE
#undef FALSE
#endif
#define FALSE false

#ifdef TRUE
#undef TRUE
#endif
#define TRUE true

#define _SIZEOF_(...) CSC::LENGTH (sizeof (CSC::U::REMOVE_CVR_TYPE<_UNW_ (__VA_ARGS__)>))
#define _ALIGNOF_(...) CSC::LENGTH (alignof (CSC::U::REMOVE_CVR_TYPE<CSC::U::REMOVE_ARRAY_TYPE<_UNW_ (__VA_ARGS__)>>))
#define _COUNTOF_(...) CSC::LENGTH (CSC::U::COUNT_OF_TYPE<_UNW_ (__VA_ARGS__)>::value)
#define _CAPACITYOF_(...) CSC::LENGTH (CSC::U::CAPACITY_OF_TYPE<_UNW_ (__VA_ARGS__)>::value)

#ifdef VOID
#undef VOID
#endif

#ifdef NONE
#undef NONE
#endif

#ifdef NULL
#undef NULL
#endif
#define NULL nullptr

//@error: fuck std
#define _PCSTRU8_(arg) CSC::Plain<CSC::STRU8> (_CAST_ (ARGV<STRU8[_COUNTOF_ (DEF<decltype (_CAT_ (u8 ,arg))>)]>::null ,_CAT_ (u8 ,arg)))
#define _PCSTRU16_(arg) CSC::Plain<CSC::STRU16> (_CAT_ (u ,arg))
#define _PCSTRU32_(arg) CSC::Plain<CSC::STRU32> (_CAT_ (U ,arg))
#define _PCSTRA_(arg) CSC::Plain<CSC::STRA> (_UNW_ (arg))
#define _PCSTRW_(arg) CSC::Plain<CSC::STRW> (_CAT_ (L ,arg))

#ifdef __CSC_CONFIG_STRA__
#define _PCSTR_ _PCSTRA_
#endif

#ifdef __CSC_CONFIG_STRW__
#define _PCSTR_ _PCSTRW_
#endif
} ;