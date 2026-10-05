// slice s00775760: SP::cRuntimeModelBuilder mesh / bone accessors and the
// constructor/destructor pair for a resource model.  Small accessors are
// reconstructed; the large EH-framed routines are skeletons (partial).
#include "types.h"

__declspec(noinline) int FUN_00776320(int a, int b, int c, int d, int e);   // @ 0x00776320

// @ 0x007763b0  SP::cRuntimeModelBuilder::GetRuntimeMeshes
bool GetRuntimeMeshes(int param_1, int param_2, int param_3, int param_4, int param_5) {
    return FUN_00776320(param_1, param_2, param_3, param_4, param_5) == 0;
}

struct cRuntimeModelBuilder {
    char pad[0x140];

    // @ 0x007763f0
    char setFlagA(int key, int unused);
    // @ 0x00776470
    char setFlagB(int key, int unused);
    // @ 0x007764c0
    void setBoneA(int unused, const float* v, float w, int unused2);
    // @ 0x00776520
    void setBoneB(int unused, const float* v, float w, int unused2);
};

char cRuntimeModelBuilder::setFlagA(int key, int unused) {
    (void)unused;
    if (key == 0x692ea61) {
        if (*(char*)((char*)this + 0x133) != 0) {
            *(char*)((char*)this + 0x133) = 0;
            *(char*)((char*)this + 0x132) = 1;
        }
        return 1;
    }
    return 0;
}

char cRuntimeModelBuilder::setFlagB(int key, int unused) {
    (void)unused;
    if (key == 0x692ea61) {
        if (*(char*)((char*)this + 0x135) != 0) {
            *(char*)((char*)this + 0x135) = 0;
            *(char*)((char*)this + 0x134) = 1;
        }
        return 1;
    }
    return 0;
}

void cRuntimeModelBuilder::setBoneA(int unused, const float* v, float w, int unused2) {
    (void)unused;
    (void)unused2;
    *(float*)((char*)this + 0x120) = v[0];
    *(float*)((char*)this + 0x124) = v[1];
    *(float*)((char*)this + 0x128) = v[2];
    *(float*)((char*)this + 0x12c) = w;
}

void cRuntimeModelBuilder::setBoneB(int unused, const float* v, float w, int unused2) {
    (void)unused;
    (void)unused2;
    *(float*)((char*)this + 0x12c) = v[0];
    *(float*)((char*)this + 0x130) = v[1];
    *(float*)((char*)this + 0x134) = v[2];
    *(float*)((char*)this + 0x138) = w;
}

// ---------------------------------------------------------------------------
// Large EH-framed routines -- skeletons (partial).
// @ 0x00775760, 0x007760a0, 0x00776320, 0x00776590, 0x00776680
// ---------------------------------------------------------------------------
int FUN_00776320(int a, int b, int c, int d, int e) {
    (void)a; (void)b; (void)c; (void)d; (void)e;
    return 1;
}
void FUN_00775760(int a, int b, int c, int d) {
    (void)a; (void)b; (void)c; (void)d;
}
int FUN_007760a0(int a, void* b, int c, int d, int e) {
    (void)a; (void)b; (void)c; (void)d; (void)e;
    return 0;
}
void FUN_00776590(int* p) {
    (void)p;
}
void FUN_00776680(int* p) {
    (void)p;
}
