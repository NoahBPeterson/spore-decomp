// Slice 35: cdecl(ar, Vec128* s) at 0x00be6180, frame 0xa98.
// Trims s->e by whole 0x80-byte records, then reads a count from ar's stream and
// serializes that many 0x80-byte records through a per-iteration VarList.
#include "types.h"

struct Timer {
    char d[0x20];
    void Ctor();   // 0x00b63890 (thiscall, no args)
    void Dtor();   // 0x00b638b0 (thiscall)
};

struct VarList {
    void* f0;
    void* f8;
    void Init(int a, int b, int** ref);   // 0x00692f90 (thiscall, ret 0xc)
    void Serialize(void* ar);             // 0x00693e10 (thiscall, ret 4)
};

struct Vec128 {
    char* b;
    char* e;
    char* c;
    void FUN_00bda710(uint32_t a, char* n);        // 0x00bda710 (thiscall, ret 8)
    void FUN_00be0cd0(uint32_t n);                 // 0x00be0cd0 (thiscall, ret 4)
    void FUN_00be30e0(char* oldEnd, int* tmp);     // 0x00be30e0 (thiscall, ret 8)
};

extern "C" {
uint32_t __cdecl FUN_00bdd600(char* a, char* b, char* c);   // 0x00bdd600 (cdecl, 3 args)
void __stdcall FUN_00bdd380(int* p);                        // 0x00bdd380 (stdcall, ret 4)
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
void FUN_00be6180(void* ar, Vec128* s)
{
    char* b0 = s->b;
    char* e0 = s->e;
    uint32_t r = FUN_00bdd600(e0, e0, b0);
    s->FUN_00bda710(r, s->e);
    s->e = s->e + ((e0 - b0) >> 7) * -0x80;

    uint32_t count = 0;
    void* stream = VCallGet(ar, 0x20);
    void* rd = VCallGet(stream, 0x18);
    FUN_0093a780(rd, &count, 1, 0);
    s->FUN_00be0cd0(count);

    for (uint32_t i = 0; i < count; ++i) {
        Timer t1, t2;
        t1.Ctor();
        t2.Ctor();

        void* pA = 0;
        void* pB = 0;
        int* ref = 0;
        VarList vl;
        vl.f0 = 0;
        vl.f8 = 0;
        vl.Init(0x1a80d26, 0x156e448, &ref);
        vl.Serialize(ar);

        char* oldEnd = s->e;
        if (oldEnd < s->c) {
            s->e = oldEnd + 0x80;
            if (oldEnd != 0) {
                int tmp = 0;
                FUN_00bdd380(&tmp);
            }
        } else {
            int tmp = 0;
            s->FUN_00be30e0(oldEnd, &tmp);
        }

        if (pB) VCallVoid(pB, 0xc0);
        if (pA) VCallVoid(pA, 0xc0);

        t2.Dtor();
        t1.Dtor();
    }

    VCallVoid(ar, 0x1c);
}
