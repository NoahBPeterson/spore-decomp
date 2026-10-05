// Slice s0071d550: SP mesh/cluster helper methods (some small accessors, some large
// emitters).  Optimized module: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast.
#include "types.h"

// A generic object holding a base pointer at +0x1c and arrays at +0x30 etc.
struct Obj13 {
    char pad_00[0x1c];
    char* mBase;        // +0x1c
    bool func_dc90(int idx);
    int  findShort(int idx, int key);
};

struct Vec20 {              // 0x20-byte entry
    uint32_t mA;            // +0x00
    uint32_t mB;            // +0x04
    uint32_t mC;            // +0x08
    uint32_t mKey;          // +0x0c
    uint32_t mVal;          // +0x10
    uint32_t mD, mE, mF;    // +0x14..
};
struct VecDescr {
    char pad_00[8];
    char* mpBegin;          // +0x08
    char* mpEnd;            // +0x0c
    char* mpCapacity;       // +0x10
};

// @ 0x0071dc90
bool Obj13::func_dc90(int idx)
{
    int* p = (int*)(mBase + idx * 0x8c + 0x44);
    return p[0] != p[1];
}

// @ 0x0071dd80
int Vec20_find(const VecDescr* v, uint32_t key)
{
    int n = (int)((v->mpEnd - v->mpBegin) >> 5);
    const char* begin = v->mpBegin;
    for (int i = 0; i < n; ++i)
        if (*(const uint32_t*)(begin + i * 0x20 + 0xc) == key)
            return *(const int*)(begin + i * 0x20 + 0x10);
    return 0;
}

// @ 0x0071e040
int Obj13_findShort(Obj13* self, int idx, int key)
{
    int* p = (int*)(self->mBase + idx * 0x8c + 0x14);
    const short* q = (const short*)p[0];
    int n = (int)((p[1] - (int)q) >> 2);
    const short* ps = q;
    for (int i = 0; i < n; ++i, ps += 2)
        if (*ps == key)
            return i;
    return -1;
}

// ---------------------------------------------------------------------------
// Remaining functions: skeletons (partial).  Signatures follow the observed
// calling conventions.
// ---------------------------------------------------------------------------
// @ 0x0071d550
void Obj13_d550(void* self) { (void)self; }
// @ 0x0071d960
void Obj13_d960(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }
// @ 0x0071dbf0
bool Obj13_dbf0(void* self, void* writer) { (void)self; (void)writer; return true; }
// @ 0x0071dcc0
int Obj13_dcc0(void* self) { (void)self; return 0; }
// @ 0x0071ddc0
void Obj13_ddc0(const void* v, uint32_t a) { (void)v; (void)a; }
// @ 0x0071de40
void Obj13_de40(void* self, void* a) { (void)self; (void)a; }
// @ 0x0071ded0
void Obj13_ded0(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }
// @ 0x0071e090
void Obj13_e090(void* self, void* a) { (void)self; (void)a; }
// @ 0x0071e110
void Obj13_e110(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }
// @ 0x0071e230
bool Obj13_e230(const void* v, int limit, const int* keys, int* out)
{
    (void)v; (void)limit; (void)keys; (void)out;
    return false;
}
// @ 0x0071e290
void Obj13_e290(void* self, void* a) { (void)self; (void)a; }
// @ 0x0071e320
void Obj13_e320(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }
