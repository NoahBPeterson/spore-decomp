// Slice 35: cdecl(ar, CElementVector* s) at 0x00be6180, frame 0xa98.
// Trims s->e by whole 0x80-byte CElement records, then reads a count from ar's stream and
// serialises that many CElement records through a per-iteration cVarListSerializer.
#include "types.h"

// SP::cGonzagoTimer's ctor/dtor (0x00b63890 / 0x00b638b0); this in ecx, no stack arguments.
struct Timer {
    char d[0x20];
    void Ctor();   // 0x00b63890
    void Dtor();   // 0x00b638b0
};

// The 0x80-byte record the vector holds: two embedded cGonzagoTimer sub-objects at
// +0x30/+0x50 and two owned pointers at +0x70/+0x78.  CopyConstructFrom (0x00bdd380)
// copies a record field by field and AddRefs the source's pointers through vtable slot
// 0xbc; the destructor below releases them through slot 0xc0.
struct CElement {
    uint32_t pad00[12];                      // +0x00
    Timer    timeA;                          // +0x30
    Timer    timeB;                          // +0x50
    void*    ptr70;                          // +0x70
    uint32_t pad74;                          // +0x74
    void*    ptr78;                          // +0x78
    uint32_t pad7c;                          // +0x7c
    void CopyConstructFrom(CElement* src);   // 0x00bdd380 (thiscall, ret 4)
};

// The 0xa14-byte serializer object the loop builds once per record: Init stores the
// context at +0xa0c, the data serializer at +0xa10 and the id at +0xa08 (and clears the
// two words before them); everything before that is the serializer's own state.  It is
// exactly as large as the gap between the record temporary and the top of the frame.
struct cVarListSerializer {
    uint32_t pad00[0xa00 / 4];               // +0x000
    uint32_t nA00;                           // +0xa00
    uint32_t nA04;                           // +0xa04
    uint32_t id;                             // +0xa08
    void*    context;                        // +0xa0c
    void*    dataSerializer;                 // +0xa10
    void Init(void* ctx, void* ser, unsigned id);   // 0x00692f90 (thiscall, ret 0xc)
    void Read(void* ar);                            // 0x00693e10 (thiscall, ret 4)
};

// The vector object itself (byte pointers into a 0x80-byte element array) and the three
// out-of-line element routines it calls.
struct CElementVector {
    char* b;                                             // +0
    char* e;                                             // +4
    char* c;                                             // +8
    void FUN_00bda710(uint32_t first, char* last);       // 0x00bda710 (thiscall, ret 8)
    void FUN_00be0cd0(uint32_t n);                       // 0x00be0cd0 (thiscall, ret 4)
    void FUN_00be30e0(char* oldEnd, CElement* value);    // 0x00be30e0 (thiscall, ret 8)
};

extern "C" {
uint32_t __cdecl FUN_00bdd600(char* first, char* last, char* dst);    // 0x00bdd600 (cdecl, 3 args)
void __cdecl FUN_0093a780(void* stream, uint32_t* out, int n, int z); // 0x0093a780 (cdecl, 4 args)
}

typedef void* (__thiscall *GetFn)(void*);
typedef void (__thiscall *VoidFn)(void*);

static inline void* VCallGet(void* self, int slot)
{
    void** vt = *(void***)self;
    return ((GetFn)vt[slot / 4])(self);
}

static inline void VCallVoid(void* self, int slot)
{
    void** vt = *(void***)self;
    ((VoidFn)vt[slot / 4])(self);
}

// @ 0x00be6180
void FUN_00be6180(void* ar, CElementVector* s)
{
    char* b0 = s->b;
    char* e0 = s->e;
    uint32_t r = FUN_00bdd600(e0, e0, b0);
    s->FUN_00bda710(r, s->e);
    s->e = s->e + ((e0 - b0) >> 7) * -0x80;

    void* stream = VCallGet(ar, 0x20);
    uint32_t count = 0;
    void* rd = VCallGet(stream, 0x18);
    FUN_0093a780(rd, &count, 1, 0);
    s->FUN_00be0cd0(count);

    for (uint32_t i = 0; i < count; ++i) {
        CElement tmp;
        tmp.timeA.Ctor();
        tmp.timeB.Ctor();
        tmp.ptr70 = 0;
        tmp.ptr78 = 0;

        cVarListSerializer vl;
        vl.Init(&tmp, (void*)0x0156e448, 0x1a80d26);
        vl.Read(ar);

        char* oldEnd = s->e;
        if (oldEnd < s->c) {
            s->e = oldEnd + 0x80;
            if (oldEnd != 0)
                ((CElement*)oldEnd)->CopyConstructFrom(&tmp);
        } else {
            s->FUN_00be30e0(oldEnd, &tmp);
        }

        if (tmp.ptr78) VCallVoid(tmp.ptr78, 0xc0);
        if (tmp.ptr70) VCallVoid(tmp.ptr70, 0xc0);

        tmp.timeB.Dtor();
        tmp.timeA.Dtor();
    }

    VCallVoid(ar, 0x1c);
}