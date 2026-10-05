// Slice s004604f0: creature-material / mesh helpers of the second module.
// /Od /Ob1 /MD /Gy /TP /arch:SSE.
#include "types.h"

extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedIncrement)

extern char g_sentinel2;   // 0x01667bac

// =====================================================================
// @ 0x461290  intrusive AddRef (thread-safe)
// =====================================================================
struct RefCounted {
    char         pad[8];
    volatile long mnRefCount;
    int AddRef();
};

int RefCounted::AddRef()
{
    return _InterlockedIncrement(&mnRefCount);
}

// =====================================================================
// @ 0x461400  initialise three string-like sub-objects
// =====================================================================
struct Sub {
    void* b;
    void* e;
    void* c;
};

struct C461400 {
    char  pad0[4];
    Sub   sub1;       // +0x04
    char  pad1[0x18];
    Sub   sub2;       // +0x28
    char  pad2[8];
    void* p3c;        // +0x3c
    void* p40;        // +0x40
    C461400* Ctor();
};

C461400* C461400::Ctor()
{
    Sub* s1 = &sub1;
    s1->b = 0;
    s1->e = 0;
    s1->c = 0;
    s1->b = &g_sentinel2;
    s1->e = s1->b;
    s1->c = (char*)s1->b + 2;
    Sub* s2 = &sub2;
    s2->b = 0;
    s2->e = 0;
    s2->c = 0;
    void** p3 = &p3c;
    *p3 = 0;
    void** p4 = &p40;
    *p4 = 0;
    return this;
}

// =====================================================================
// @ 0x460a80  recursive primitive-batch reorder, returns consumed count
// =====================================================================
int FUN_00460a80(int verts, int target, int* ids, int count)
{
    int out = 0;
    int i = 0;
    while (i < count) {
        if (target == *(short*)(verts + ids[i] * 4)) {
            int id = ids[i];
            ids[i] = ids[out];
            ids[out] = id;
            out = out + 1;
            int n = FUN_00460a80(verts, id, ids + out, count - out);
            out = n + out;
        }
        int nxt = i + 1;
        int* chosen;
        if (nxt < out) {
            chosen = &out;
        } else {
            chosen = &nxt;
        }
        i = *chosen;
    }
    return out;
}

// =====================================================================
// @ 0x460b50  recursive influence gather (PARTIAL)
// =====================================================================
void FUN_00460b50(int a, int b, int c, int d, int e, int f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    return;
}

// The remaining functions of this slice are large mesh builders; skeletons keep the
// slice compiling.
void FUN_004604f0() { return; }   // PartBuildCreatureMaterialInfo @0x4604f0
void FUN_00460bf0() { return; }   // @0x460bf0
void FUN_00460d40() { return; }   // @0x460d40
void FUN_00460f80() { return; }   // @0x460f80
void FUN_004610c0() { return; }   // @0x4610c0
void FUN_004612e0() { return; }   // @0x4612e0
