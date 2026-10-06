// Force-included when compiling modern EA code (EAThread, BurnoutDecomp reconstructions) against the
// ~2010 EABase (EAWebKit bundle) with VS2008: defines the newer EABase macros they use.
#pragma once
#include <EABase/eabase.h>
#ifndef EA_DISABLE_VC_WARNING
  #define EA_DISABLE_VC_WARNING(w)  __pragma(warning(push)) __pragma(warning(disable:w))
  #define EA_RESTORE_VC_WARNING()   __pragma(warning(pop))
#endif
#ifndef EA_DISABLE_ALL_VC_WARNINGS
  #define EA_DISABLE_ALL_VC_WARNINGS() __pragma(warning(push, 0))
  #define EA_RESTORE_ALL_VC_WARNINGS() __pragma(warning(pop))
#endif
#ifndef EA_DISABLE_CLANG_WARNING
  #define EA_DISABLE_CLANG_WARNING(w)
  #define EA_RESTORE_CLANG_WARNING()
#endif
#ifndef EA_DISABLE_GCC_WARNING
  #define EA_DISABLE_GCC_WARNING(w)
  #define EA_RESTORE_GCC_WARNING()
#endif
#ifndef EA_UNUSED
  #define EA_UNUSED(x) (void)x
#endif
#ifndef EA_NOEXCEPT
  #define EA_NOEXCEPT
#endif
#ifndef EA_CONSTEXPR
  #define EA_CONSTEXPR
#endif
#ifndef EA_CPP14_CONSTEXPR
  #define EA_CPP14_CONSTEXPR
#endif
#ifndef EA_OVERRIDE
  #define EA_OVERRIDE
#endif
#ifndef EA_NON_COPYABLE
  #define EA_NON_COPYABLE(T) private: T(const T&); T& operator=(const T&);
#endif
#ifndef EA_OFFSETOF
  #define EA_OFFSETOF(s, m) offsetof(s, m)
#endif
#ifndef EA_ALIGN_OF
  #define EA_ALIGN_OF(t) __alignof(t)
#endif
#ifndef EA_PREPROCESSOR_JOIN
  #define EA_PREPROCESSOR_JOIN(a, b)  EA_PREPROCESSOR_JOIN1(a, b)
  #define EA_PREPROCESSOR_JOIN1(a, b) EA_PREPROCESSOR_JOIN2(a, b)
  #define EA_PREPROCESSOR_JOIN2(a, b) a##b
#endif
#ifndef EA_STATIC_ASSERT
  #define EA_STATIC_ASSERT(e) typedef char EA_PREPROCESSOR_JOIN(ea_static_assert_, __LINE__)[(e) ? 1 : -1]
#endif
#ifndef EA_COMPILETIME_ASSERT
  #define EA_COMPILETIME_ASSERT(e) EA_STATIC_ASSERT(e)
#endif
#ifndef EA_FORCE_INLINE
  #define EA_FORCE_INLINE __forceinline
#endif
#ifndef EA_NO_INLINE
  #define EA_NO_INLINE __declspec(noinline)
#endif
#ifndef EA_UNLIKELY
  #define EA_UNLIKELY(x) (x)
  #define EA_LIKELY(x) (x)
#endif
#ifndef EA_PLATFORM_WINDOWS
  #define EA_PLATFORM_WINDOWS 1
#endif
#ifndef EA_PLATFORM_MICROSOFT
  #define EA_PLATFORM_MICROSOFT 1
#endif
#ifndef EA_PLATFORM_DESKTOP
  #define EA_PLATFORM_DESKTOP 1
#endif
#ifndef EA_WINAPI_FAMILY_PARTITION
  #define EA_WINAPI_FAMILY_PARTITION(p) 1
#endif
#ifndef EA_PLATFORM_PTR_SIZE
  #define EA_PLATFORM_PTR_SIZE 4
#endif
#ifndef EA_PLATFORM_WORD_SIZE
  #define EA_PLATFORM_WORD_SIZE 4
#endif
#ifndef EA_CACHE_LINE_SIZE
  #define EA_CACHE_LINE_SIZE 64
#endif
#ifndef EA_THREAD_LOCAL
  #define EA_THREAD_LOCAL __declspec(thread)
#endif
#ifndef EA_PREFIX_ALIGN
  #define EA_PREFIX_ALIGN(n) __declspec(align(n))
  #define EA_POSTFIX_ALIGN(n)
#endif
#ifndef EA_ALIGNED
  #define EA_ALIGNED(t, v, n) __declspec(align(n)) t v
#endif
#ifndef EA_COMPILER_NO_NULLPTR
  #define nullptr NULL
#endif
// old EABase defines EA_COMPILER_MSVC with no value; EAThread tests `EA_COMPILER_MSVC >= 1400`
#if defined(EA_COMPILER_MSVC)
  #undef EA_COMPILER_MSVC
  #define EA_COMPILER_MSVC _MSC_VER
#endif
