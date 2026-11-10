// Slice s008911f0: one setter pair of an EA::Text font-like object (UTFSpore manager2.obj family,
// /O2 /MD /Gy /TP /arch=SSE /fp=fast, no /EHsc).
#include "types.h"

struct ValueSink {                 // 0x00fcc140: stores its argument at +8
    uint32_t pad0000[2];
    uint32_t mValue08;             // +0x08
    void Set(uint32_t v);
};

struct TailSink {                  // 0x0089ed60: stores its argument at +0x15c
    uint32_t pad0000[0x15c / 4];
    uint32_t mValue15c;            // +0x15c
    void Set(uint32_t v);
};

struct FontHolder {
    uint32_t pad0000[0x11c / 4];   // +0x000
    uint32_t mValue11c;            // +0x11c
    uint32_t pad0120[0x48 / 4];    // +0x120 .. +0x167
    uint32_t mCtx168;              // +0x168

    void SetValue(uint32_t value);
};

// @ 0x008911f0
void FontHolder::SetValue(uint32_t value)
{
    ((ValueSink*)this)->Set(value);
    mValue11c = value;
    ((TailSink*)((char*)this + 0x168))->Set(value);
}
