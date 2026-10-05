// Slice s0052d460: cSPSkinPaintClearCommand::Execute and small IO/string helpers.
#include "types.h"
#include <stdarg.h>

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}
inline void* operator new(unsigned int, void* p) { return p; }

// @ 0x0052d460  `anonymous namespace'::cSPSkinPaintClearCommand::Execute  (PARTIAL)
void cSPSkinPaintClearCommand_Execute(void* arg, void* args)
{
    // TODO: reconstruct the ArgScript option parsing body (2763-byte /Od function).
    (void)arg; (void)args;
}

// ---------------------------------------------------------------- error string builder
extern uint8_t DAT_015dfa30[0x800];
extern void*   DAT_01667bac;
int  Vsnprintf8(char* buf, uint32_t n, const char* fmt, ...);          // 0x00938400
void EastlStringAssign(void* str, const char* first, const char* last); // 0x00454cb0

// @ 0x0052df30  cError/cError(const char* fmt, ...)
int* ErrorStringCtor(int* out, const char* fmt, ...)
{
    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    out[0] = (int)&DAT_01667bac;
    out[1] = out[0];
    out[2] = out[0] + 1;
    va_list ap;
    va_start(ap, fmt);
    Vsnprintf8((char*)DAT_015dfa30, 0x800, fmt, ap);
    va_end(ap);
    char* p = (char*)DAT_015dfa30;
    while (*p)
        p++;
    EastlStringAssign(out, (const char*)DAT_015dfa30, p);
    return out;
}

// @ 0x0052dfe0  vector range constructor (3 words zeroed, then assign [first,last))
struct SVec3 {
    void* p0;
    void* p1;
    void* p2;
    void RangeAssign(void* first, void* last);   // 0x0047d390
    SVec3(void** range);                          // 0x0052dfe0
};
SVec3::SVec3(void** range)
{
    p0 = 0;
    p1 = 0;
    p2 = 0;
    RangeAssign(range[0], range[1]);
}

// ---------------------------------------------------------------- IO read
int  ReadInt32(void* self, void* dst, int count, int flags);   // EA::IO::ReadInt32
void FUN_0093ac80(void* self, void* dst);                      // 0x0093ac80
void FUN_0093a800(void* self, void* dst, int count, int flags); // 0x0093a800

struct IStream {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(int*, int);   // +0x30
};

// @ 0x0052e030
void ReadSkinPaintData(IStream* self, int version, int data)
{
    ReadInt32(self, (void*)(data + 8), 1, 0);
    self->v12((int*)(data + 0xc), 0xc);
    self->v12((int*)(data + 0x18), 0xc);
    if (version >= 2)
        ReadInt32(self, (void*)(data + 0x24), 1, 0);
    if (version >= 3)
        ReadInt32(self, (void*)(data + 0x28), 1, 0);
    ReadInt32(self, (void*)(data + 0x2c), 1, 0);
    ReadInt32(self, (void*)(data + 0x30), 1, 0);
    ReadInt32(self, (void*)(data + 0x34), 1, 0);
    ReadInt32(self, (void*)(data + 0x38), 1, 0);
    ReadInt32(self, (void*)(data + 0x3c), 1, 0);
    ReadInt32(self, (void*)(data + 0x40), 1, 0);
    ReadInt32(self, (void*)(data + 0x44), 1, 0);
    ReadInt32(self, (void*)(data + 0x48), 1, 0);
    ReadInt32(self, (void*)(data + 0x4c), 1, 0);
    ReadInt32(self, (void*)(data + 0x50), 1, 0);
    FUN_0093ac80(self, (void*)(data + 0x54));
    FUN_0093a800(self, (void*)(data + 0x58), 1, 0);
    FUN_0093a800(self, (void*)(data + 0x60), 1, 0);
    ReadInt32(self, (void*)(data + 0x68), 1, 0);
}
