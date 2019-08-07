#pragma once

#ifndef __CSC_USE_TRAITS__
#error "б╞(д├бузебу ;)д├ : this file is only for 'csc.hpp'"
#endif

namespace U {
template <class>
struct ENABLE ;

template <>
struct ENABLE<ARGC<TRUE>> {
	using TYPE = VOID ;
} ;

template <BOOL _VAL1>
using ENABLE_TYPE = typename stl::enable_if<_VAL1 ,VOID>::type ;
} ;

namespace U {
template <class ,class ,class>
struct CONDITIONAL ;

template <class _ARG1 ,class _ARG2>
struct CONDITIONAL<ARGC<TRUE> ,_ARG1 ,_ARG2> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1 ,class _ARG2>
struct CONDITIONAL<ARGC<FALSE> ,_ARG1 ,_ARG2> {
	using TYPE = _ARG2 ;
} ;

template <BOOL _VAL1 ,class _ARG1 ,class _ARG2>
using CONDITIONAL_TYPE = typename stl::conditional<_VAL1 ,_ARG1 ,_ARG2>::type ;
} ;

namespace U {
template <class _ARG1>
struct REMOVE_REFERENCE {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
struct REMOVE_REFERENCE<_ARG1 &> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
struct REMOVE_REFERENCE<_ARG1 &&> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using REMOVE_REFERENCE_TYPE = typename stl::remove_reference<_ARG1>::type ;
} ;

namespace U {
template <class _ARG1>
struct REMOVE_CONST {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
struct REMOVE_CONST<const _ARG1> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using REMOVE_CONST_TYPE = typename stl::remove_const<_ARG1>::type ;
} ;

namespace U {
template <class _ARG1>
struct REMOVE_VOLATILE {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
struct REMOVE_VOLATILE<volatile _ARG1> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using REMOVE_VOLATILE_TYPE = typename stl::remove_volatile<_ARG1>::type ;
} ;

namespace U {
template <class _ARG1>
using REMOVE_CVR_TYPE = REMOVE_CONST_TYPE<REMOVE_VOLATILE_TYPE<REMOVE_REFERENCE_TYPE<_ARG1>>> ;
} ;

namespace U {
template <class _ARG1>
struct REMOVE_POINTER {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
struct REMOVE_POINTER<PTR<_ARG1>> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using REMOVE_POINTER_TYPE = typename stl::remove_pointer<_ARG1>::type ;
} ;

namespace U {
template <class _ARG1>
struct REMOVE_ARRAY {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
struct REMOVE_ARRAY<ARR<_ARG1>> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1 ,LENGTH _VAL1>
struct REMOVE_ARRAY<_ARG1[_VAL1]> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using REMOVE_ARRAY_TYPE = typename stl::remove_extent<_ARG1>::type ;
} ;

namespace U {
template <class _ARG1>
struct REMOVE_TEMP {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
struct REMOVE_TEMP<TEMP<_ARG1>> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using REMOVE_TEMP_TYPE = typename REMOVE_TEMP<REMOVE_CVR_TYPE<_ARG1>>::TYPE ;
} ;

namespace U {
template <class>
struct REMOVE_MEMFUNC ;

template <class _ARG1 ,class... _ARGS>
struct REMOVE_MEMFUNC<_ARG1 (_ARGS...)> {
	using TYPE = DEF<_ARG1 (_ARGS...)> ;
} ;

template <class _ARG1 ,class... _ARGS>
struct REMOVE_MEMFUNC<_ARG1 (_ARGS...) const> {
	using TYPE = DEF<_ARG1 (_ARGS...)> ;
} ;

template <class _ARG1 ,class... _ARGS>
struct REMOVE_MEMFUNC<_ARG1 (_ARGS...) volatile> {
	using TYPE = DEF<_ARG1 (_ARGS...)> ;
} ;

template <class _ARG1 ,class... _ARGS>
struct REMOVE_MEMFUNC<_ARG1 (_ARGS...) const volatile> {
	using TYPE = DEF<_ARG1 (_ARGS...)> ;
} ;

#if _HAS_CXX17
template <class _ARG1 ,class... _ARGS>
struct REMOVE_MEMFUNC<_ARG1 (_ARGS...) noexcept> {
	using TYPE = DEF<_ARG1 (_ARGS...)> ;
} ;

template <class _ARG1 ,class... _ARGS>
struct REMOVE_MEMFUNC<_ARG1 (_ARGS...) const noexcept> {
	using TYPE = DEF<_ARG1 (_ARGS...)> ;
} ;

template <class _ARG1 ,class... _ARGS>
struct REMOVE_MEMFUNC<_ARG1 (_ARGS...) volatile noexcept> {
	using TYPE = DEF<_ARG1 (_ARGS...)> ;
} ;

template <class _ARG1 ,class... _ARGS>
struct REMOVE_MEMFUNC<_ARG1 (_ARGS...) const volatile noexcept> {
	using TYPE = DEF<_ARG1 (_ARGS...)> ;
} ;
#endif

template <class _ARG1>
using REMOVE_MEMFUNC_TYPE = typename REMOVE_MEMFUNC<_ARG1>::TYPE ;
} ;

namespace U {
template <class>
struct MEMBER_TO ;

template <class _ARG1 ,class _ARG2>
struct MEMBER_TO<_ARG1 _ARG2::*> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using MEMBER_TO_TYPE = typename MEMBER_TO<_ARG1>::TYPE ;
} ;

namespace U {
template <class>
struct MEMBER_OF ;

template <class _ARG1 ,class _ARG2>
struct MEMBER_OF<_ARG1 _ARG2::*> {
	using TYPE = _ARG2 ;
} ;

template <class _ARG1>
using MEMBER_OF_TYPE = typename MEMBER_OF<_ARG1>::TYPE ;
} ;

namespace U {
template <class>
struct INVOKE_OF ;

template <class _ARG1 ,class... _ARGS>
struct INVOKE_OF<_ARG1 (_ARGS...)> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using INVOKE_OF_TYPE = typename INVOKE_OF<_ARG1>::TYPE ;
} ;

namespace U {
template <class>
struct INVOKE_TO ;

template <class _ARG1 ,class... _ARGS>
struct INVOKE_TO<_ARG1 (_ARGS...)> {
	using TYPE = ARGVS<_ARGS...> ;
} ;

template <class _ARG1>
using INVOKE_TO_TYPE = typename INVOKE_TO<_ARG1>::TYPE ;
} ;

namespace U {
template <class ,class ,class>
struct RESULT_OF ;

#ifdef __CSC_COMPILER_CLANG__
template <class _ARG1 ,class _ARG2 ,class _ARG3>
struct RESULT_OF {
	using TYPE = NONE ;
} ;
#endif

template <class _ARG1 ,class _ARG2 ,class... _ARGS>
struct RESULT_OF<_ARG1 (_ARGS...) ,ARGVS<_ARGS...> ,_ARG2> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1 ,class _ARG2>
struct RESULT_OF<_ARG1 ,_ARG2 ,ENABLE_TYPE<(_SIZEOF_ (decltype (&_ARG1::operator())) > 0)>> {
	using TYPE = typename RESULT_OF<REMOVE_MEMFUNC_TYPE<MEMBER_TO_TYPE<decltype (&_ARG1::operator())>> ,_ARG2 ,VOID>::TYPE ;
} ;

template <class _ARG1 ,class _ARG2>
using RESULT_OF_TYPE = typename RESULT_OF<REMOVE_CVR_TYPE<REMOVE_POINTER_TYPE<_ARG1>> ,_ARG2 ,VOID>::TYPE ;
} ;

namespace U {
template <class>
struct COUNTOF_TRAITS ;

template <class _ARG1>
struct COUNTOF_TRAITS<ARR<_ARG1>> {
	using TYPE = ARGC<0> ;
} ;

template <class _ARG1 ,LENGTH _VAL1>
struct COUNTOF_TRAITS<_ARG1[_VAL1]> {
	using TYPE = ARGC<_VAL1> ;
} ;

template <class _ARG1>
using COUNTOF_TRAITS_TYPE = typename COUNTOF_TRAITS<_ARG1>::TYPE ;
} ;

namespace U {
template <class _ARG1>
struct FORWARD_TRAITS {
	using TYPE = const _ARG1 & ;
} ;

template <class _ARG1>
struct FORWARD_TRAITS<_ARG1 &> {
	using TYPE = _ARG1 & ;
} ;

template <class _ARG1>
struct FORWARD_TRAITS<_ARG1 &&> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1>
using FORWARD_TRAITS_TYPE = typename FORWARD_TRAITS<_ARG1>::TYPE ;
} ;

namespace U {
template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS {
	using TYPE = REMOVE_REFERENCE_TYPE<_ARG1> ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,const _ARG2> {
	using TYPE = const REMOVE_REFERENCE_TYPE<_ARG1> ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,volatile _ARG2> {
	using TYPE = volatile REMOVE_REFERENCE_TYPE<_ARG1> ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,const volatile _ARG2> {
	using TYPE = const volatile REMOVE_REFERENCE_TYPE<_ARG1> ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,_ARG2 &> {
	using TYPE = REMOVE_REFERENCE_TYPE<_ARG1> & ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,const _ARG2 &> {
	using TYPE = const REMOVE_REFERENCE_TYPE<_ARG1> & ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,volatile _ARG2 &> {
	using TYPE = volatile REMOVE_REFERENCE_TYPE<_ARG1> & ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,const volatile _ARG2 &> {
	using TYPE = const volatile REMOVE_REFERENCE_TYPE<_ARG1> & ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,_ARG2 &&> {
	using TYPE = REMOVE_REFERENCE_TYPE<_ARG1> && ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,const _ARG2 &&> {
	using TYPE = const REMOVE_REFERENCE_TYPE<_ARG1> && ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,volatile _ARG2 &&> {
	using TYPE = volatile REMOVE_REFERENCE_TYPE<_ARG1> && ;
} ;

template <class _ARG1 ,class _ARG2>
struct CAST_TRAITS<_ARG1 ,const volatile _ARG2 &&> {
	using TYPE = const volatile REMOVE_REFERENCE_TYPE<_ARG1> && ;
} ;

template <class _ARG1 ,class _ARG2>
using CAST_TRAITS_TYPE = typename CAST_TRAITS<_ARG1 ,_ARG2>::TYPE ;
} ;

namespace U {
template <class ,class ,class>
struct LOAD_CHECK {
	using TYPE = ARGC<FALSE> ;
} ;

template <class _ARG1 ,class _ARG2>
struct LOAD_CHECK<_ARG1 ,_ARG2 ,ARGC<1>> {
	using TYPE = typename LOAD_CHECK<_ARG1 ,_ARG2 ,ARGC<2>>::TYPE ;
} ;

template <class _ARG1>
struct LOAD_CHECK<_ARG1 ,TEMP<_ARG1> ,ARGC<1>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
struct LOAD_CHECK<TEMP<_ARG1> ,_ARG1 ,ARGC<1>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
struct LOAD_CHECK<ARR<_ARG1> ,ARR<TEMP<_ARG1>> ,ARGC<1>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
struct LOAD_CHECK<ARR<TEMP<_ARG1>> ,ARR<_ARG1> ,ARGC<1>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
struct LOAD_CHECK<_ARG1 ,NONE ,ARGC<1>> {
	using TYPE = ARGC<stl::is_class<_ARG1>::value> ;
} ;

template <class _ARG1>
struct LOAD_CHECK<NONE ,_ARG1 ,ARGC<1>> {
	using TYPE = ARGC<stl::is_class<_ARG1>::value> ;
} ;

template <>
struct LOAD_CHECK<ARR<BYTE> ,VOID ,ARGC<2>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <>
struct LOAD_CHECK<ARR<BYTE> ,ARR<STRU8> ,ARGC<2>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <>
struct LOAD_CHECK<ARR<BYTE> ,ARR<STRU16> ,ARGC<2>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <>
struct LOAD_CHECK<ARR<BYTE> ,ARR<STRU32> ,ARGC<2>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <>
struct LOAD_CHECK<ARR<BYTE> ,ARR<STRA> ,ARGC<2>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <>
struct LOAD_CHECK<ARR<BYTE> ,ARR<STRW> ,ARGC<2>> {
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1>
struct LOAD_CHECK<_ARG1 ,BYTE ,ARGC<2>> {
	//@info: not recommend
	using TYPE = ARGC<TRUE> ;
} ;

template <class _ARG1 ,class _ARG2>
using LOAD_CHECK_TYPE = typename LOAD_CHECK<_ARG1 ,_ARG2 ,ARGC<1>>::TYPE ;
} ;

namespace U {
template <class ,class ,class>
struct INDEX_OF {
	using TYPE = ARGC<VAR_NONE> ;
} ;

template <class _ARG1 ,class _ARG2 ,class... _ARGS>
struct INDEX_OF<_ARG1 ,REMOVE_CVR_TYPE<_ARG2> ,ARGVS<_ARG2 ,_ARGS...>> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1 ,class _ARG2 ,class _ARG3 ,class... _ARGS>
struct INDEX_OF<_ARG1 ,_ARG2 ,ARGVS<_ARG3 ,_ARGS...>> {
	using TYPE = typename INDEX_OF<ARGC<_ARG1::value + 1> ,_ARG2 ,ARGVS<_ARGS...>>::TYPE ;
} ;

template <class _ARG1 ,class _ARG2>
using INDEX_OF_TYPE = typename INDEX_OF<ARGC<0> ,REMOVE_CVR_TYPE<_ARG1> ,_ARG2>::TYPE ;
} ;

namespace U {
template <class ,class>
struct VISIT_OF ;

template <class _ARG1 ,class... _ARGS>
struct VISIT_OF<ARGC<0> ,ARGVS<_ARG1 ,_ARGS...>> {
	using TYPE = _ARG1 ;
} ;

template <class _ARG1 ,class _ARG2 ,class... _ARGS>
struct VISIT_OF<_ARG1 ,ARGVS<_ARG2 ,_ARGS...>> {
	_STATIC_ASSERT_ (_ARG1::value > 0) ;
	using TYPE = typename VISIT_OF<ARGC<_ARG1::value - 1> ,ARGVS<_ARGS...>>::TYPE ;
} ;

template <class _ARG1 ,class _ARG2>
using VISIT_OF_TYPE = typename VISIT_OF<_ARG1 ,_ARG2>::TYPE ;
} ;

namespace U {
template <class ,class>
struct is_arithmetic_help :public stl::false_type {} ;

template <>
struct is_arithmetic_help<VAR32 ,VOID> :public stl::true_type {} ;

template <>
struct is_arithmetic_help<VAR64 ,VOID> :public stl::true_type {} ;

template <class _ARG1>
struct is_arithmetic_help<_ARG1 ,ENABLE_TYPE<std::is_same<_ARG1 ,VARX>::value && !std::is_same<_ARG1 ,VAR32>::value && !std::is_same<_ARG1 ,VAR64>::value>> :public stl::true_type {} ;

template <class _ARG1>
struct is_arithmetic_help<_ARG1 ,ENABLE_TYPE<std::is_same<_ARG1 ,VARY>::value && !std::is_same<_ARG1 ,CHAR>::value && !std::is_same<_ARG1 ,DATA>::value>> :public stl::true_type {} ;

template <>
struct is_arithmetic_help<VAL32 ,VOID> :public stl::true_type {} ;

template <>
struct is_arithmetic_help<VAL64 ,VOID> :public stl::true_type {} ;

template <class _ARG1>
struct is_arithmetic_help<_ARG1 ,ENABLE_TYPE<std::is_same<_ARG1 ,VALX>::value && !std::is_same<_ARG1 ,VAL32>::value && !std::is_same<_ARG1 ,VAL64>::value>> :public stl::true_type {} ;

template <class _ARG1>
using is_arithmetic = is_arithmetic_help<_ARG1 ,VOID> ;
} ;

namespace U {
template <class>
struct is_plain_strx :public stl::false_type {} ;

template <>
struct is_plain_strx<STRU8> :public stl::true_type {} ;

template <>
struct is_plain_strx<STRU16> :public stl::true_type {} ;

template <>
struct is_plain_strx<STRU32> :public stl::true_type {} ;

template <>
struct is_plain_strx<STRA> :public stl::true_type {} ;

template <>
struct is_plain_strx<STRW> :public stl::true_type {} ;
} ;

namespace U {
template <class ,class>
struct is_complete_type_help :public stl::false_type {} ;

template <class _ARG1>
struct is_complete_type_help<_ARG1 ,ENABLE_TYPE<(_SIZEOF_ (_ARG1) > 0)>> :public stl::true_type {} ;

template <class _ARG1>
using is_complete_type = is_complete_type_help<_ARG1 ,VOID> ;
} ;

namespace U {
template <class ,class ,class>
struct is_interface_type_help :public stl::false_type {} ;

template <class _ARG1 ,class _ARG2>
struct is_interface_type_help<_ARG1 ,_ARG2 ,ENABLE_TYPE<_SIZEOF_ (_ARG1) == _SIZEOF_ (_ARG2) && _ALIGNOF_ (_ARG1) == _ALIGNOF_ (_ARG2)>> :public stl::is_base_of<_ARG2 ,_ARG1> {} ;

template <class _ARG1 ,class _ARG2>
using is_interface_type = is_interface_type_help<_ARG1 ,_ARG2 ,VOID> ;
} ;

namespace U {
template <class ,class ,class>
struct is_always_base_of_help :public stl::false_type {} ;

template <class _ARG1 ,class _ARG2>
struct is_always_base_of_help<_ARG1 ,_ARG2 ,ENABLE_TYPE<(_SIZEOF_ (_ARG1) > 0 && _SIZEOF_ (_ARG2) > 0)>> :public stl::is_base_of<_ARG1 ,_ARG2> {} ;

template <class _ARG1 ,class _ARG2>
using is_always_base_of = is_always_base_of_help<_ARG1 ,_ARG2 ,VOID> ;
} ;

namespace U {
template <class...>
struct is_all_same_help :public stl::false_type {} ;

template <class _ARG1>
struct is_all_same_help<_ARG1> :public stl::true_type {} ;

template <class _ARG1>
struct is_all_same_help<_ARG1 ,_ARG1> :public stl::true_type {} ;

template <class _ARG1 ,class... _ARGS>
struct is_all_same_help<_ARG1 ,_ARG1 ,_ARGS...> :public is_all_same_help<_ARG1 ,_ARGS...> {} ;

template <class... _ARGS>
using is_all_same = is_all_same_help<_ARGS...> ;
} ;

namespace U {
template <class...>
struct is_any_same_help :public stl::false_type {} ;

template <class _ARG1>
struct is_any_same_help<_ARG1> :public stl::false_type {} ;

template <class _ARG1 ,class... _ARGS>
struct is_any_same_help<_ARG1 ,_ARG1 ,_ARGS...> :public stl::true_type {} ;

template <class _ARG1 ,class _ARG2 ,class... _ARGS>
struct is_any_same_help<_ARG1 ,_ARG2 ,_ARGS...> :public CONDITIONAL_TYPE<(is_any_same_help<_ARG1 ,_ARGS...>::value && is_any_same_help<_ARG2 ,_ARGS...>::value) ,stl::true_type ,stl::false_type> {} ;

template <class... _ARGS>
using is_any_same = is_any_same_help<_ARGS...> ;
} ;

namespace U {
template <template <class...> class ,class>
struct is_template_of_help :public stl::false_type {} ;

template <template <class...> class _ARGT ,class... _ARGS>
struct is_template_of_help<_ARGT ,_ARGT<_ARGS...>> :public stl::true_type {} ;

template <template <class...> class _ARGT ,class _ARG1>
using is_template_of = is_template_of_help<_ARGT ,_ARG1> ;
} ;

namespace U {
template <class>
struct TEMPLATE_TO ;

template <template <class...> class _ARGT ,class... _ARGS>
struct TEMPLATE_TO<_ARGT<_ARGS...>> {
	using TYPE = ARGVS<_ARGS...> ;
} ;

template <class _ARG1>
using TEMPLATE_TO_TYPE = typename TEMPLATE_TO<_ARG1>::TYPE ;
} ;