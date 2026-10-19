// src/game/UTFSpore_Win32/EAString.cpp -- migrated from slice(s) s0093b9e0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAString.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/IStream.h"
#include "EA/IO/MemoryStream.h"
#include "EA/IO/SharedPointer.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* MemCpyThunk(void* dst, const void* src, size_t n);          // 0x011e0744
extern "C" void  EASTL_deallocate(void* p);                                  // 0x00f47380
extern "C" void* EASTL_allocate(size_t n, const char*, int, int, int, int);  // 0x00f473a0
#include <intrin.h>
#include <new>

// ---- items of slice s0093b9e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* MemCpyThunk(void* dst, const void* src, size_t n);          // 0x011e0744
extern "C" void  EASTL_deallocate(void* p);                                  // 0x00f47380
extern "C" void* EASTL_allocate(size_t n, const char*, int, int, int, int);  // 0x00f473a0
namespace EA {
namespace Text {
int ConvertEncoding(const void* src, size_t srcCount, int srcEnc, void* dst, int* dstLen, int dstEnc); // 0x0093c950
}
}
namespace EA {
struct EAString {
    void* mpBegin;   // +0
    void* mpEnd;     // +4
    void* mpCap;     // +8
};  // EA::Text
}
// ---- items of slice s0093b9e0 end

// @ 0x0093c440
namespace EA {
void ConvertToString8Impl(void* outp, const wchar_t* src, unsigned count)
{
    EAString* out = (EAString*)outp;
    if (count == 0xffffffff) {
        const wchar_t* p = src;
        while (*p) p++;
        count = (unsigned)(p - src);
    }
    char buf[512];
    int len = 0x200;
    unsigned n = (unsigned)EA::Text::ConvertEncoding(src, count, 0x10, buf, &len, 8);
    if (count > n) {
        // did not fit: redo with an exact-size buffer
        char* heap = (char*)EASTL_allocate(count * 4, 0, 0, 0, 0, 0);
        len = count * 4;
        EA::Text::ConvertEncoding(src, count, 0x10, heap, &len, 8);
        out->mpBegin = 0; out->mpEnd = 0; out->mpCap = 0;
        char* data = (char*)EASTL_allocate((size_t)len + 1, 0, 0, 0, 0, 0);
        MemCpyThunk(data, heap, len);
        data[len] = 0;
        out->mpBegin = data; out->mpEnd = data + len; out->mpCap = data + len + 1;
        EASTL_deallocate(heap);
        return;
    }
    out->mpBegin = 0; out->mpEnd = 0; out->mpCap = 0;
    char* data = (char*)EASTL_allocate((size_t)len + 1, 0, 0, 0, 0, 0);
    MemCpyThunk(data, buf, len);
    data[len] = 0;
    out->mpBegin = data; out->mpEnd = data + len; out->mpCap = data + len + 1;
}
}  // namespace EA

// @ 0x0093c570
namespace EA {
void* ConvertToString8(void* out, const int* range)
{
    ConvertToString8Impl(out, (const wchar_t*)range[0], (unsigned)((range[1] - range[0]) >> 1));
    return out;
}
}  // namespace EA

// @ 0x0093c5a0
namespace EA {
void ConvertToString16Impl(void* outp, const char* src, unsigned count)
{
    EAString* out = (EAString*)outp;
    if (count == 0xffffffff) {
        const char* p = src;
        while (*p) p++;
        count = (unsigned)(p - src);
    }
    wchar_t buf[512];
    int len = 0x200;
    unsigned n = (unsigned)EA::Text::ConvertEncoding(src, count, 8, buf, &len, 0x10);
    if (count <= n) {
        out->mpBegin = 0; out->mpEnd = 0; out->mpCap = 0;
        wchar_t* data = (wchar_t*)EASTL_allocate(((size_t)len + 1) * 2, 0, 0, 0, 0, 0);
        MemCpyThunk(data, buf, (size_t)len * 2);
        data[len] = 0;
        out->mpBegin = data; out->mpEnd = data + len; out->mpCap = data + len + 1;
        return;
    }
    wchar_t* heap = (wchar_t*)EASTL_allocate(((size_t)count * 2), 0, 0, 0, 0, 0);
    len = count * 2;
    EA::Text::ConvertEncoding(src, count, 8, heap, &len, 0x10);
    out->mpBegin = 0; out->mpEnd = 0; out->mpCap = 0;
    wchar_t* data = (wchar_t*)EASTL_allocate(((size_t)len + 1) * 2, 0, 0, 0, 0, 0);
    MemCpyThunk(data, heap, (size_t)len * 2);
    data[len] = 0;
    out->mpBegin = data; out->mpEnd = data + len; out->mpCap = data + len + 1;
    EASTL_deallocate(heap);
}
}  // namespace EA

// @ 0x0093c6d0
namespace EA {
void* ConvertToString16(void* out, const int* range)
{
    ConvertToString16Impl(out, (const char*)range[0], (unsigned)(range[1] - range[0]));
    return out;
}
}  // namespace EA
