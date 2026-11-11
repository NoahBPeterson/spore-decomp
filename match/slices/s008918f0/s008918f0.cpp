// Slice s008918f0: EA::Text::OutlineFont cached-glyph purge.
// Built /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast (UTFSpore manager2.obj family, no /EHsc).
#include "types.h"

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void* cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);
extern "C" void __cdecl T2K_PurgeMemory(char* data, int mode, int* out);   // 0x008c0710

namespace EA { namespace Text {

// The T2K (TrueType) rasteriser state owned by the outline font.
struct T2KState {
    uint32_t pad000[0x46];       // +0x000 .. +0x117
    int32_t  field118;           // +0x118
    int32_t  field11c;           // +0x11c
};

// OutlineFont: EA::Text::Font (0x48 bytes, includes the futex at +0x28).
struct OutlineFont {
    uint32_t pad000[0x0a];       // +0x000 .. +0x027
    uint32_t mMutex[6];          // +0x028  CRITICAL_SECTION (EA::Thread::Futex)
    uint32_t pad040[0x47];       // +0x040 .. +0x15b
    T2KState* mpT2KState;        // +0x15c
    int32_t   mT2KStateFlag;     // +0x160

    void RefreshGlyphCache(int unused);   // 0x008918f0
};

// @ 0x008918f0
void OutlineFont::RefreshGlyphCache(int)
{
    EnterCriticalSection(mMutex);
    if (mpT2KState != 0) {
        T2K_PurgeMemory((char*)mpT2KState, 1, &mT2KStateFlag);
        mpT2KState->field118 = 0;
        mpT2KState->field11c = 0;
    }
    LeaveCriticalSection(mMutex);
}

}}  // namespace EA::Text
