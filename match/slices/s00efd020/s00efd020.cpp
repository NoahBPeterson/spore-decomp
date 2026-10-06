// Slice s00efd020 — Simulator camera/selection helpers and editor UI update.
// /O2 /MD /Gy /EHsc /TP region.
#include "types.h"

struct VObj {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void* s3(unsigned);
};

struct SelCtx {
    bool FUN_00efde90(int param_2);
};

// @ 0x00efde90
bool SelCtx::FUN_00efde90(int param_2) {
    int* base = (int*)param_2;
    int* p = *(int**)((char*)base + 0x20);
    if (*(char*)((char*)p + 0x18) == 1) {
        int* q = (int*)((char*)p + *(int*)((char*)p + 0x10));
        if (q != 0) {
            int* piVar1 = (int*)q[3];
            if (piVar1 != 0 && *(char*)((char*)this + 4) != 0) {
                if (((VObj*)piVar1)->s3(0x137e8e0) != 0)
                    return false;
            }
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// Below: behavioural summaries (partial).  The originals pass their return
// buffer and vector arguments in EAX/ESI/EDI (compiler custom conventions), so
// byte-exact reconstruction needs the full cViewer/App layouts.
// ---------------------------------------------------------------------------
// @ 0x00efd6e0
bool FUN_00efd6e0(float* out) {
    (void)out;
    return false;
}

// @ 0x00efd830
void FUN_00efd830(float* a, float* b) {
    (void)a; (void)b;
}

// @ 0x00efd8e0
void FUN_00efd8e0(float* out) {
    (void)out;
}

// @ 0x00efd020
void FUN_00efd020(void* this_, int a, int b, int c, int d) {
    (void)this_; (void)a; (void)b; (void)c; (void)d;
}

// @ 0x00efd970
void FUN_00efd970(void* this_, int a, int b) { (void)this_; (void)a; (void)b; }

// @ 0x00efdc00
void FUN_00efdc00(void* this_, int a, int b) { (void)this_; (void)a; (void)b; }