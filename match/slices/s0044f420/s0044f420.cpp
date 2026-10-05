// slice s0044f420 -- cSPEditorBlock split / rebuild driver.
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast module.  Not byte-exact.
#include "types.h"

struct AutoRefBlockVec { unsigned int w[15]; };   // 0x3c-byte local

struct cSPEditorBlock;
extern void VecCtor(AutoRefBlockVec* v, const char* name);   // 0x00540470
extern void VecFunc(AutoRefBlockVec* v);                     // 0x00453770
extern void VecDtor(AutoRefBlockVec* v);                     // 0x00453eb0
extern void FUN_0043f230(cSPEditorBlock* block, cSPEditorBlock* self);
extern bool FUN_004adc40(void* p);
extern void FUN_004388b0(void* p, cSPEditorBlock* block);
extern char FUN_004a7e60(void* p);
extern void TrackerGetOffsetA(cSPEditorBlock* self, float* out, int one);  // 0x00438120
extern void TrackerGetOffsetB(cSPEditorBlock* self, float* out, int one);  // 0x004381e0
extern void TrackerPlace(cSPEditorBlock* self, float* a, float* b);        // 0x00437b00
extern const float g_negOne;   // 0x013eb1bc = -1.0f

struct cSPEditorBlock {
    char   pad0[0x28];
    void*  mModel;        // +0x28
    char   pad2c[0x33c - 0x2c];
    cSPEditorBlock* mSocket;  // +0x33c
    char   pad340[0x3e0 - 0x340];
    cSPEditorBlock* mLinked;  // +0x3e0
    char   pad3e4[0xdc8 - 0x3e4];
    unsigned int mFlags[2];   // +0xdc8

    bool GetFlag(unsigned int n) const {
        unsigned int tmp;
        bool t14;
        if (n < 60u) {
            tmp = mFlags[n / 32];
            t14 = (tmp & (1u << (n % 32))) != 0;
        } else {
            t14 = false;
        }
        return t14;
    }

    int  CalculateSymmetrySign();                 // 0x0044f240
    void SetFlag(int id, int value);              // 0x00435a10
    cSPEditorBlock* BuildBlock(int type, AutoRefBlockVec& a, AutoRefBlockVec& b); // 0x0044f7c0
    void FUN_00448e90(void* p, int a);            // 0x00448e90
    void FUN_00449420(void* p, int a);            // 0x00449420

    cSPEditorBlock* Split(int type);              // 0x0044f420
};

// @ 0x0044f420
cSPEditorBlock* cSPEditorBlock::Split(int type) {
    char nameA[8];
    char nameB[8];
    nameA[0] = 0;
    nameB[0] = 0;

    AutoRefBlockVec vA;
    VecCtor(&vA, nameA);
    VecFunc(&vA);
    AutoRefBlockVec vB;
    VecCtor(&vB, nameB);
    VecFunc(&vB);

    cSPEditorBlock* nb = BuildBlock(type, vA, vB);
    if (nb != 0) {
        FUN_0043f230(nb, this);
        if (type == 2 || type == 3) {
            FUN_00448e90((char*)this + 0x48, 0);
            FUN_00449420((char*)this + 0xa8, 0);
            nb->CalculateSymmetrySign();
            if (mModel != 0) {
                cSPEditorBlock* sc = mSocket;
                if (sc != 0) {
                    cSPEditorBlock* linked = sc->mLinked;
                    if (linked != 0 && FUN_004adc40(mModel)) {
                        FUN_004388b0(sc->mLinked, nb);
                    } else {
                        if (FUN_004a7e60(mSocket))
                            FUN_004388b0(mSocket, nb);
                        else
                            FUN_004388b0(mSocket, nb);
                    }
                }
            }
            bool f = GetFlag(0xc);
            nb->SetFlag(0xc, f ? 1 : 0);
            if (type == 3) {
                float a[3];
                float b[3];
                TrackerGetOffsetA(this, a, 1);
                a[0] = a[0] * g_negOne;
                TrackerGetOffsetB(this, b, 1);
                b[0] = b[0] * g_negOne;
                TrackerPlace(nb, b, a);
            } else {
                float b[3];
                float a[3];
                TrackerGetOffsetB(this, b, 1);
                TrackerGetOffsetA(this, a, 1);
                TrackerPlace(nb, a, b);
            }
        }
    }
    VecDtor(&vB);
    VecDtor(&vA);
    return nb;
}
