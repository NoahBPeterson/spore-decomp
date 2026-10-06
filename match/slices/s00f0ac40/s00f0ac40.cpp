// Slice s00f0ac40 — Simulator/creator UI list and container helpers.
// /O2 /MD /Gy /EHsc /TP region.
//
// The originals are editor UI update/list-management routines whose byte-exact
// reconstruction needs the full container element type (0x44-byte records) and
// scene-graph layouts; these are behavioural summaries (partial).
#include "types.h"

struct VObj {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3(unsigned);
    virtual void* s4(unsigned);
};

extern int g_16c7d90;  // container/global list base
extern "C" void* FUN_00dfb930(void*, void*, void*);  // eastl::copy
extern "C" void* FUN_00f280f0(void);
extern "C" void* FUN_00f26380(void);
extern "C" void* FUN_00f28b30(void);
extern "C" void* FUN_00f0b420(int);
extern "C" void FUN_00f0b150(void*, int, void*);
extern "C" void FUN_00f0b690(void*);
extern "C" void FUN_00f0b4d0(void*);

// @ 0x00f0b0e0
void FUN_00f0b0e0(void* this_, void* a, void* b) {
    (void)this_; (void)a; (void)b;
}

// @ 0x00f0b390
void FUN_00f0b390(void* this_, int param_2) {
    (void)this_; (void)param_2;
}

// @ 0x00f0b420
void FUN_00f0b420(void* this_, int a) { (void)this_; (void)a; }

// @ 0x00f0b8b0
void FUN_00f0b8b0() {
    if (g_16c7d90 == 0)
        return;
    // WindowManager()->GetWindowList(0); for each 0x10-byte entry call
    // FUN_00f0b420/FUN_00f26380 then FUN_00f0b690 or FUN_00f0b4d0.
    for (int i = 0; i < 0x50; i += 0x10) {
        FUN_00f0b420(*(int*)((char*)&g_16c7d90 + i + 0x14));
    }
}

// @ 0x00f0ac40
void FUN_00f0ac40(void* this_, int a, int b, int c) {
    (void)this_; (void)a; (void)b; (void)c;
}
// @ 0x00f0b150
void FUN_00f0b150(void* this_, int a, int b) { (void)this_; (void)a; (void)b; }
// @ 0x00f0b4d0
void FUN_00f0b4d0(void* this_, int a) { (void)this_; (void)a; }
// @ 0x00f0b690
void FUN_00f0b690(void* this_, int a) { (void)this_; (void)a; }
// @ 0x00f0b940
void FUN_00f0b940(void* this_, int a, int b) { (void)this_; (void)a; (void)b; }
// @ 0x00f0ba10
void FUN_00f0ba10(void* this_, int a, int b) { (void)this_; (void)a; (void)b; }