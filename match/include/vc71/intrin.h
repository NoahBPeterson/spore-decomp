/* Stand-in for <intrin.h> (VS2005+) when compiling with VC .NET 2003 (cl71.sh puts this directory
 * on the include path; VS2008 never sees it). Supplies the intrinsics our sources use that 7.1
 * lacks or only declares elsewhere. Havok 3.1 itself used inline asm for rdtsc. */
#pragma once
#include <stdlib.h>      /* _byteswap_*, _rotl */
#include <xmmintrin.h>   /* SSE, MMX */
#ifdef __cplusplus
extern "C" {
#endif
long __cdecl _InterlockedIncrement(long volatile*);
long __cdecl _InterlockedDecrement(long volatile*);
long __cdecl _InterlockedExchange(long volatile*, long);
long __cdecl _InterlockedExchangeAdd(long volatile*, long);
long __cdecl _InterlockedCompareExchange(long volatile*, long, long);
#ifdef __cplusplus
}
#endif
#pragma intrinsic(_InterlockedIncrement, _InterlockedDecrement, _InterlockedExchange, \
                  _InterlockedExchangeAdd, _InterlockedCompareExchange)
static __forceinline unsigned __int64 __rdtsc(void) { __asm rdtsc }
