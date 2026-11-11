// sse_helpers.h -- the reviewed inline-assembly float helpers (2026-11-11).
//
// Spore's /arch:SSE modules use a handful of tiny SSE helpers that VC++ 2008 does not emit from C++: a plain cast
// calls _ftol2 (truncating, out of line), and fminf/fmaxf are calls. Retail has them inlined as these exact
// instruction sequences, the shape of EA's own inline-asm math helpers. They were copy-pasted under many names
// (Clamp, ClampF, ClampSSE, RoundToInt, FloatToInt, FloorToInt, ...); this header is the one reviewed copy.
//
// A function counts as byte-exact when its only inline assembly comes from this header (tools/matching/asm_audit.py,
// VETTED). Any other __asm needs a maintainer's approval (AGENTS.md, Rules). Do not add to this file without one.
#ifndef MATCH_SSE_HELPERS_H
#define MATCH_SSE_HELPERS_H

#pragma warning(push)
#pragma warning(disable : 4035)  // no return value: the result is left in eax

// round to nearest (cvtss2si under the default rounding mode)
__forceinline int SseRoundToInt(float f)
{
    __asm cvtss2si eax, f
}

// truncate toward zero, what a C cast means, without the _ftol2 call
__forceinline int SseTruncToInt(float f)
{
    __asm cvttss2si eax, f
}

// floor: round to nearest, then step down when the rounded value is above f
__forceinline int SseFloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

// ceiling: round to nearest, then step up when the rounded value is below f
__forceinline int SseCeilToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        add      ecx, 1
        ucomiss  xmm1, xmm0
        cmovb    eax, ecx
    }
}

#pragma warning(pop)

// max(x, lo), then min(.., hi)
__forceinline float SseClamp(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}

// max(x, lo)
__forceinline float SseMax(float x, float lo)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        movss x, xmm0
    }
    return x;
}

// max(x, 0)
__forceinline float SseMaxZero(float x)
{
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, x
        movss x, xmm0
    }
    return x;
}

// min(max(x, 0), hi)
__forceinline float SseSaturate(float x, float hi)
{
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, x
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}

// min(max(x, 0), 1)
__forceinline float SseClamp01(float x)
{
    float one = 1.0f;
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, x
        minss xmm0, one
        movss x, xmm0
    }
    return x;
}

// round to nearest into 64 bits on the x87 stack (fld; fistp qword), what retail does where a C cast of a float to
// __int64 would call _ftol2 (truncating)
__forceinline __int64 X87RoundToInt64(float f)
{
    __declspec(align(8)) __int64 r;
    __asm {
        fld   dword ptr [f]
        fistp qword ptr [r]
    }
    return r;
}

#endif  // MATCH_SSE_HELPERS_H
