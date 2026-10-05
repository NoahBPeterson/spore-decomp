// Slice s006f7430: cFilterChain render-state wrappers, uninitialized_copy of a 0x28-byte
// element and filter-chain teardown/registration helpers.
// Region 0x6f7430-0x6f8370. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"
#include <intrin.h>

// ---- external callees -------------------------------------------------------------------
void  __cdecl FUN_0077ca20(int a, float b, float c, float d, float e);
void  __cdecl FUN_0070f520(void* b, void* e);
void  __cdecl FUN_006f6910();
void* __cdecl FUN_006f43e0(void* a, void* b, void* c);
void  __cdecl FUN_00892970();
void  __cdecl FUN_00420660();
void  __cdecl FUN_00576620();
void* __cdecl FUN_006f6630(void* p);
void  __cdecl FUN_006f4500();
void  __cdecl FUN_006f44c0();
void  __cdecl Hashtable_DoFreeNodes(void* b, void* e);
void  __cdecl Hashtable_DoAllocateBuckets(void* b, void* e);

void __fastcall FUN_006f54a0_(void* self, int p2, int p3, int p4, int p5,
                               int p6, int p7, int p8, int p9, int p10);

struct cVecBool {
    void Assign(void* src);   // 0x6f6770
};

// @ 0x006f8140  (uninitialized_copy of 0x28-byte elements)
char* FUN_006f8140(char* first, char* last, char* dest) {
    if (first != last) {
        do {
            dest[0] = first[0];
            dest[1] = first[1];
            *(int*)(dest + 8) = *(int*)(first + 8);
            *(int*)(dest + 0xc) = *(int*)(first + 0xc);
            ((cVecBool*)(dest + 0x10))->Assign(first + 0x10);
            first += 0x28;
            dest += 0x28;
        } while (first != last);
    }
    return dest;
}

// @ 0x006f8190
void __fastcall FUN_006f8190(int self) {
    FUN_006f6910();
    int* v = (int*)(self + 0x78);
    unsigned i = 0;
    if ((*(int*)(self + 0x7c) - *v) >> 2 != 0) {
        do {
            int* p = (int*)(*v + i * 4);
            int obj = *p;
            if (obj != 0) {
                *p = 0;
                volatile long* rc = (volatile long*)(obj + 8);
                _InterlockedExchangeAdd(rc, -1);
                long c = _InterlockedExchangeAdd(rc, 0);
                if (c < 1) _InterlockedExchangeAdd(rc, 1);
            }
            i++;
        } while (i < (unsigned)(*(int*)(self + 0x7c) - *v >> 2));
    }
    int begin = *v;
    int end = *(int*)(self + 0x7c);
    void* r = FUN_006f43e0((void*)end, (void*)end, (void*)begin);
    FUN_0070f520(r, *(void**)(self + 0x7c));
    *(int*)(self + 0x7c) = *(int*)(self + 0x7c) + (end - begin >> 2) * -4;
    Hashtable_DoAllocateBuckets(*(void**)(self + 0x10), *(void**)(self + 0x14));
    *(void**)(self + 0x18) = 0;
    Hashtable_DoFreeNodes(*(void**)(self + 0x30), *(void**)(self + 0x34));
    *(void**)(self + 0x38) = 0;
}

// @ 0x006f8260
int FUN_006f8260(int self, unsigned a, unsigned b) { (void)self; (void)a; (void)b; return 0; }

// ---- large wrappers: skeletons (see partial.txt) -----------------------------------------
// @ 0x006f7430
void FUN_006f7430(void* self, void* ctx, int p3, int p4, int p5, int p6, int p7) {
    (void)self; (void)ctx; (void)p3; (void)p4; (void)p5; (void)p6; (void)p7;
}
// @ 0x006f7680
void FUN_006f7680(void* self, void* ctx, int p3, int p4, int p5, int p6, int p7) {
    (void)self; (void)ctx; (void)p3; (void)p4; (void)p5; (void)p6; (void)p7;
}
// @ 0x006f79a0
void FUN_006f79a0(void* self, void* a, void* b, int p4, int p5, int p6, int p7, int p8) {
    (void)self; (void)a; (void)b; (void)p4; (void)p5; (void)p6; (void)p7; (void)p8;
}
// @ 0x006f7f70
void SP_cFilterChain_ApplyStrengthFilter(void* self, void* a, void* b, int p4, int p5,
                                         int p6, int p7, int p8) {
    (void)self; (void)a; (void)b; (void)p4; (void)p5; (void)p6; (void)p7; (void)p8;
}
