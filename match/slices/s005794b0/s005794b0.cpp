// slice s005794b0
// Mixed editor helpers (render settings, camera, cheats, eastl strings).
// Optimized module (/O2 /arch:SSE /fp:fast).
#include <new>
#include <string.h>
#include "types.h"

namespace SP {
class cAppModeEditorBase {
public:
    char pad[0x458];
    void UpdateRenderSettings();                  // 0x5794b0
    void SetCurrentConfig(int);                   // 0x579720
    void SwitchToEditorCamera();                  // 0x5798f0
    void SavePreferenceSomething();               // 0x5799a0
    bool HasSameMask();                           // 0x579a20
    bool SomeFinder();                            // 0x579af0
    void CheatCommand(void* args);                // 0x579d40
};
}

using SP::cAppModeEditorBase;

// ---------------------------------------------------------------------------
// eastl::basic_string<wchar_t> helper
// ---------------------------------------------------------------------------
struct cWString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    void AllocateSelf(uint32_t n);                // 0x429760
    void RangeInitialize(const wchar_t* s);       // 0x579a90
};

extern unsigned g_mask[4];                        // 0x15da7c4

// @ 0x00579a20
bool cAppModeEditorBase::HasSameMask()
{
    void* p = *(void**)((char*)this + 0x1cc);
    if (p == 0)
        return false;
    unsigned local[4];
    local[0] = *(unsigned*)((char*)p + 0x24) & g_mask[0];
    local[1] = *(unsigned*)((char*)p + 0x28) & g_mask[1];
    local[2] = *(unsigned*)((char*)p + 0x2c) & g_mask[2];
    local[3] = *(unsigned*)((char*)p + 0x30) & g_mask[3];
    for (unsigned i = 0; i < 16; i += 4) {
        if (*(unsigned*)((char*)local + i) != *(unsigned*)((char*)g_mask + i))
            return false;
    }
    return true;
}

// @ 0x00579a90
void cWString::RangeInitialize(const wchar_t* s)
{
    const wchar_t* e = s;
    while (*e != 0)
        ++e;
    uint32_t len = (uint32_t)(e - s);
    uint32_t nSize = len * 2;
    AllocateSelf(len + 1);
    memcpy(mpBegin, s, nSize);
    mpEnd = (wchar_t*)((char*)mpBegin + nSize);
    *mpEnd = 0;
}

// ---------------------------------------------------------------------------
// eastl::basic_string<char> assignment
// ---------------------------------------------------------------------------
struct cString8 {
    char* mpBegin;
    char* mpEnd;
    void assign(const char* first, const char* last);   // 0x454cb0
    cString8& operator=(const cString8& other);          // 0x579c60
};

// @ 0x00579c60
cString8& cString8::operator=(const cString8& other)
{
    if (&other != this)
        assign(other.mpBegin, other.mpEnd);
    return *this;
}

// ---------------------------------------------------------------------------
// Placeholders (see partial.txt)
// ---------------------------------------------------------------------------
void cAppModeEditorBase::UpdateRenderSettings() {}
void cAppModeEditorBase::SetCurrentConfig(int) {}
void cAppModeEditorBase::SwitchToEditorCamera() {}
void cAppModeEditorBase::SavePreferenceSomething() {}
bool cAppModeEditorBase::SomeFinder() { return false; }
void cAppModeEditorBase::CheatCommand(void*) {}

struct CheatObject {
    char pad[0x100];
    CheatObject();       // 0x579c80
    ~CheatObject();      // 0x579ce0
};
CheatObject::CheatObject() {}
CheatObject::~CheatObject() {}
