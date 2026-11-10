// Slice s008914c0 -- EA::Text T2K (Type 2000) font kerning pair.
//
// Reads the pair's kern value for the current glyph (sfnt kern table, swapped keys
// when the flags carry either of the two direction bits) and converts the two
// resulting FUnit values to float (FUnits * 0x142ea58).  Everything runs under the
// font mutex at +0x28; when the sfnt has no kern table or the glyph is the
// missing-glyph sentinel (+0xc0 == 1), both outputs are zeroed and false is
// returned.
// Callees: 0x008cd810 (sfnt kern lookup) and 0x008bfdb0 (T2K_TransformXFunits).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

typedef int32_t  int32;
typedef uint16_t uint16;

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void* cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);

// 0x008cd810 -- kern lookup(sfnt, keyA, keyB, &outA, &outB); both out pointers are
// caller-popped and the return value is the kern value (0 when it has no pair).
// It is a local helper of the original object, so it carries the custom
// ecx = sfnt / dx = keyB convention of its callers.
int GetSfntClassKernValue_008cd810(
    void* sfnt, int keyA, int keyB, int* outA, int* outB);

// 0x008bfdb0 -- T2K_TransformXFunits(t, units, outScaled, outRounded).
extern "C" void __cdecl T2K_TransformXFunits_008bfdb0(
    void* t, int units, int* outScaled, int* outRounded);

extern float g_142ea58;   // 0x0142ea58

struct cachedGlyph_008914c0 {
    char pad_000[0x184];
    void* mpSfnt;               // +0x184
};

struct Font_008914c0 {
    char                  pad_000[0x28];
    unsigned              mMutex[6];       // +0x028  CRITICAL_SECTION
    char                  pad_040[0xc0 - 0x40];
    int                   mbMissingGlyph;  // +0x0c0
    char                  pad_0c4[0x15c - 0xc4];
    cachedGlyph_008914c0* mpGlyph;         // +0x15c

    bool GetKerningPair(int a, int b, float* outA, float* outB, int flags);
};

// @ 0x008914c0
bool Font_008914c0::GetKerningPair(int a, int b, float* outA, float* outB, int flags)
{
    EnterCriticalSection(mMutex);

    cachedGlyph_008914c0* glyph = mpGlyph;
    bool ok = false;
    if (*(int*)((char*)glyph->mpSfnt + 0x74) == 0 || mbMissingGlyph == 1) {
        *outA = 0.0f;
        *outB = 0.0f;
    } else {
        int keyA, keyB;
        if (flags & 0x80000001) {
            keyA = b;
            keyB = a;
        } else {
            keyA = (unsigned short)a;
            keyB = (unsigned short)b;
        }
        int out1 = 0;
        int out2 = 0;
        int kern = GetSfntClassKernValue_008cd810(glyph->mpSfnt, keyA, keyB, &out1, &out2);
        if (kern != 0) {
            int scaled = 0;
            int rounded = 0;
            T2K_TransformXFunits_008bfdb0(mpGlyph, kern, &scaled, &rounded);
            *outA = (float)rounded * g_142ea58;
            *outB = (float)out2 * g_142ea58;
            ok = true;
        }
    }

    LeaveCriticalSection(mMutex);
    return ok;
}