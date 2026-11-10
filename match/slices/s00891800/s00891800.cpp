// Slice s00891800: EA::Text outline-font state update under the font mutex.
// Calls virtual slot 0x4c with a local {0,0,0,w} vector, then stores w into two
// cached fields on success.  Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void* cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);

struct Vec4 { float x, y, z, w; };

// Font interface: the update entry point is virtual slot 19 (offset 0x4c).
struct IFont {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual bool UpdateState(float x, float y, float z, float w);   // slot 19, +0x4c
};

struct OutlineFont {
    uint32_t pad000[0x0a];       // +0x000 .. +0x027
    uint32_t mMutex[6];          // +0x028  CRITICAL_SECTION
    uint32_t pad040[0x12];       // +0x040 .. +0x087
    float    mField88;           // +0x088
    uint32_t pad08c[0x0c];       // +0x08c .. +0x0bb
    float    mFieldBC;           // +0x0bc

    bool SetState(float w, int a, int b);   // 0x00891800
};

// @ 0x00891800
bool OutlineFont::SetState(float w, int, int)
{
    EnterCriticalSection(mMutex);
    bool ok = ((IFont*)this)->UpdateState(w, 0.0f, 0.0f, w);
    if (ok) {
        mField88 = w;
        mFieldBC = w;
        LeaveCriticalSection(mMutex);
        return true;
    }
    LeaveCriticalSection(mMutex);
    return false;
}
