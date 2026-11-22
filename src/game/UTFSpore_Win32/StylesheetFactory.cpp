// src/game/UTFSpore_Win32/StylesheetFactory.cpp -- migrated from slice(s) s008ff610, s00900410 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/StylesheetFactory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/MemoryStream.h"
#include <new>
#include "EA/Allocator/ICoreAllocator.h"
#include <string.h>
#include <intrin.h>

// ---- items of slice s008ff610 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IStream {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual void SetPosition(int a, int b);   // +0x28
    virtual void v11();
    virtual int Read(void* buf, unsigned n);  // +0x30
};
struct CharVec {
    char* mpBegin;
    char* mpEnd;
    void DoInsertValues(char* pos, unsigned n, const char& v);   // 0x004c10e0
};
struct EncodingSniffer {
    char pad[8];
    CharVec buf;    // +8
    int Detect(IStream* s);
};
int __cdecl DetectEncoding(const char* p, unsigned n, int a, int b);   // 0x0093c730
// ---- items of slice s008ff610 end

// @ 0x00900370
int EncodingSniffer::Detect(IStream* s)
{
    unsigned sz = buf.mpEnd - buf.mpBegin;
    if (sz < 0x40) {
        char fill = 0;
        buf.DoInsertValues(buf.mpEnd, 0x40 - sz, fill);
    } else {
        char* nf = buf.mpBegin + 0x40;
        char* last = buf.mpEnd;
        memcpy(nf, last, last - last);
        buf.mpEnd += nf - last;
    }
    s->SetPosition(0, 0);
    if (s->Read(buf.mpBegin, 0x40) != 0) {
        s->SetPosition(0, 0);
        return DetectEncoding(buf.mpBegin, 0x40, 0, 0);
    }
    return 0;
}

// @ 0x00900410
int CreateResource(void* self, int a2, int* a3, void* req)
{
    (void)self; (void)a2; (void)a3; (void)req;
    return 3;
}
