// VS2008 stub for <xatomic.h> (VS2012+). EAThread's atomics header expects the newer intrinsics;
// VS2008 has the 32-bit ones in <intrin.h>. The 16-bit and 64-bit helpers below are portable
// compare-exchange loops: Spore-era code shouldn't use them, they only need to exist to compile.
#pragma once
#include <intrin.h>
#pragma intrinsic(_InterlockedCompareExchange16, _InterlockedCompareExchange64)
static __inline short _InterlockedExchange16(short volatile* p, short v)
{ short o; do { o = *p; } while (_InterlockedCompareExchange16(p, v, o) != o); return o; }
static __inline short _InterlockedExchangeAdd16(short volatile* p, short v)
{ short o; do { o = *p; } while (_InterlockedCompareExchange16(p, (short)(o + v), o) != o); return o; }
static __inline __int64 _InterlockedExchange64_INLINE(__int64 volatile* p, __int64 v)
{ __int64 o; do { o = *p; } while (_InterlockedCompareExchange64(p, v, o) != o); return o; }
static __inline __int64 _InterlockedExchangeAdd64_INLINE(__int64 volatile* p, __int64 v)
{ __int64 o; do { o = *p; } while (_InterlockedCompareExchange64(p, o + v, o) != o); return o; }
static __inline __int64 _InterlockedAnd64_INLINE(__int64 volatile* p, __int64 v)
{ __int64 o; do { o = *p; } while (_InterlockedCompareExchange64(p, o & v, o) != o); return o; }
static __inline __int64 _InterlockedOr64_INLINE(__int64 volatile* p, __int64 v)
{ __int64 o; do { o = *p; } while (_InterlockedCompareExchange64(p, o | v, o) != o); return o; }
static __inline __int64 _InterlockedXor64_INLINE(__int64 volatile* p, __int64 v)
{ __int64 o; do { o = *p; } while (_InterlockedCompareExchange64(p, o ^ v, o) != o); return o; }
