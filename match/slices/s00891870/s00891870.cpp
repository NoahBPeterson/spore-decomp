// Slice s00891870 -- EA::Text::OutlineFont / PolygonFont update under the font mutex.
//
// Stores the {x, y, width, styleId, ?, textureId} description block at +0xa4..+0xb8,
// then clears the cached texture pointer's +0x48 field when both the width and the
// style id are non-zero.  Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void* cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);

struct CachedTexture_00891870 {
    char    pad_000[0x48];
    int     mStyleId;           // +0x48
};

struct Font_00891870 {
    char    pad_000[0x28];
    unsigned mMutex[6];         // +0x028  CRITICAL_SECTION
    char    pad_040[0xa4 - 0x40];
    int     mnA;                // +0xa4
    float   mfX;                // +0xa8
    float   mfY;                // +0xac
    int     mnB;                // +0xb0
    int     mnC;                // +0xb4
    int     mnD;                // +0xb8
    char    pad_0bc[0x15c - 0xbc];
    CachedTexture_00891870* mpTexture;  // +0x15c

    void SetRenderer(int a, float x, float y, int b, int c, int d);
};

// @ 0x00891870
void Font_00891870::SetRenderer(int a, float x, float y, int b, int c, int d)
{
    EnterCriticalSection(mMutex);
    mnA = a;
    mfX = x;
    mfY = y;
    mnB = b;
    mnC = c;
    mnD = d;
    CachedTexture_00891870* pTexture = mpTexture;
    if (pTexture != 0 && a != 0)
        pTexture->mStyleId = 0;
    LeaveCriticalSection(mMutex);
}
