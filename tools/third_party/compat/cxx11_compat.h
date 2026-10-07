// Force-included (after eabase_compat.h) for the b5more target of build_ea_libs.py: macro stand-ins
// for C++11 keywords and library functions VS2008 lacks. The rest of the C++11/17 syntax is
// text-rewritten by downlevel_cxx11() in build_ea_libs.py.
#pragma once
#ifdef B5_NO_ALIGNAS  // retry mode: VS2008 cannot pass over-aligned types by value (C2719)
  #define alignas(n)
#else
  #define alignas(n) __declspec(align(n))
#endif
#define alignof(t) __alignof(t)
#define static_assert(...)
#define final
#define noexcept
#define thread_local __declspec(thread)
#ifdef __cplusplus
#include <stdio.h>
#include <math.h>
#define snprintf _snprintf
namespace std {
  using ::_snprintf;
  inline double fmax(double a, double b) { return a > b ? a : b; }
  inline float fmax(float a, float b) { return a > b ? a : b; }
  inline double fma(double a, double b, double c) { return a * b + c; }
  inline float fma(float a, float b, float c) { return a * b + c; }
  inline bool signbit(double x) { return _copysign(1.0, x) < 0; }
  inline double fmin(double a, double b) { return a < b ? a : b; }
  inline float fmin(float a, float b) { return a < b ? a : b; }
}
#endif
