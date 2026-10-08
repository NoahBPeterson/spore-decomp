// Slice s00b6ca10: FUN_00b6cde0 (VA 00b6cde0, 396 bytes, cdecl, args (P, int, float*, float), plain ret).
//
// Classifies two queries on P->mpA into a mode (-1 = none, 0..3), drives P->mpB with that mode, then
// runs the tail helpers and the string temporary's destructor.
//
// Status: calling convention of three callees (FUN_00b686a0, FUN_00b6a720) is partly register-based
// (EAX = P->vptr, EDI = P, EAX = pair pointer), which C++ cannot express; stand-ins take the stack args only.
#include "types.h"

#define P4(n) virtual void n##0(); virtual void n##1(); virtual void n##2(); virtual void n##3();

struct IMode {                       // result of P->mpA->Query(...); Mode() at +0x20
    P4(a) P4(b)
    virtual int Mode();
};
struct IQuery {                      // P->mpA; Query() at +0x0c
    virtual void a0(); virtual void a1(); virtual void a2();
    virtual IMode* Query(uint32_t id);
};
struct IApply {                      // Query() result of P->mpB; Apply() at +0x7c
    P4(a) P4(b) P4(c) P4(d) P4(e) P4(f) P4(g)
    virtual void h0(); virtual void h1(); virtual void h2();
    virtual void Apply(int a, int b);
};
struct IObjB {                       // P->mpB; Query() at +0x0c, Notify() at +0x14
    virtual void a0(); virtual void a1(); virtual void a2();
    virtual IApply* Query(uint32_t id);
    virtual void a4();
    virtual void Notify(int mode);
};

struct cCtx {                        // P (polymorphic: P->vptr is read by the 0xb686a0 path)
    virtual void v0();
    IQuery* mpA;                     // +0x04
    uint8_t pad08[0xb4 - 0x08];
    IObjB* mpB;                      // +0xb4
};

// Helpers (cdecl: plain ret; the caller's pops are batched, so there is no add after each call).
uint32_t* FUN_00b6baf0(void* tmpStr, void* a);                    // 0x00b6baf0
void FUN_00b677e0(float* out3, void* a);                          // 0x00b677e0
float FUN_00b685e0(void* a);                                      // 0x00b685e0
int FUN_00b682a0(void* a);                                        // 0x00b682a0
int FUN_00b67b90(void* a);                                        // 0x00b67b90
char FUN_00b69010(float f, float g);                              // 0x00b69010
void FUN_00b686a0();                                              // 0x00b686a0
void FUN_00b6a720(int param2, uint32_t v, float* out3, int b1, int b2);   // 0x00b6a720

// eastl::basic_string<wchar_t>-style temporary: begin, end, capacity, allocator, then a sentinel dword.
struct TmpStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    uint32_t mSentinel;
};
void operator_delete_array(void* p);                              // 0x00f47380

void FUN_00b6cde0(cCtx* p, int param2, float* param3, float param4)
{
    IMode* m1 = p->mpA ? p->mpA->Query(0xe9cb8ba) : 0;
    IMode* m2 = p->mpA ? p->mpA->Query(0x436f315) : 0;

    if (m1 || m2) {
        int mode = -1;
        int r = m1 ? m1->Mode() : m2->Mode();
        if (r > 0x1a56aba) {
            if (r == 0x436f342) mode = 0;
            else if (r == 0x70703b3) mode = 1;
        } else {
            if (r == 0x1a56aba) mode = 2;
            else if (r == 0x18ea2cc) mode = 3;
            else if (r == 0x18eb106) mode = 1;
        }
        IObjB* b = p->mpB;
        IApply* ap = b ? b->Query(0xeeee8218) : 0;
        if (mode == -1) {
            ap->Apply(1, 0);
        } else {
            ap->Apply(1, 1);
            b->Notify(mode);
        }
    }

    TmpStr str;
    float out3[3];
    uint32_t v = *FUN_00b6baf0(&str, p->mpA);
    FUN_00b677e0(out3, p->mpA);
    float f = FUN_00b685e0(p->mpA);
    int b1 = FUN_00b682a0(p->mpA);
    int b2 = FUN_00b67b90(p->mpA);
    if (!FUN_00b69010(f, param4)) {
        FUN_00b686a0();
    } else {
        FUN_00b6a720(param2, v, out3, b1, b2);
    }
    if ((((int)((uint32_t)str.mpCapacity - (uint32_t)str.mpBegin)) & ~1) > 2 &&
        str.mpBegin && (uint32_t)str.mpBegin != str.mSentinel)
        operator_delete_array(str.mpBegin);
}
