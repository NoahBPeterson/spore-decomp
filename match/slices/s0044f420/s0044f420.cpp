// slice s0044f420 -- cSPEditorBlock split / rebuild driver.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /GS- module.  Not byte-exact.
#include "types.h"

struct Vector3 { float v[3]; };

struct AutoRefBlockVec {
    unsigned int w[15];            // 0x3c-byte local
    void Ctor(const char* name);   // 0x00540470
    void Func();                   // 0x00453770
    void Dtor();                   // 0x00453eb0
};

struct cSPEditorBlock;
struct ModelObj {
    bool FUN_004adc40();           // 0x004adc40
};
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
    void FUN_0043f230(cSPEditorBlock* self);      // 0x0043f230
    void FUN_004388b0(cSPEditorBlock* block);     // 0x004388b0
    char FUN_004a7e60(cSPEditorBlock* self);      // 0x004a7e60
    void TrackerGetOffsetA(float* out, int one);  // 0x00438120
    void TrackerGetOffsetB(float* out, int one);  // 0x004381e0
    void TrackerPlace(Vector3 a, Vector3 b);      // 0x00437b00
    cSPEditorBlock* BuildBlock(int type, cSPEditorBlock* src, AutoRefBlockVec& a, AutoRefBlockVec& b); // 0x0044f7c0
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
    vA.Ctor(nameA);
    vA.Func();
    AutoRefBlockVec vB;
    vB.Ctor(nameB);
    vB.Func();

    cSPEditorBlock* nb = BuildBlock(type, this, vA, vB);
    if (nb != 0) {
        nb->FUN_0043f230(this);
        if (type == 2 || type == 3) {
            FUN_00448e90((char*)this + 0x48, 0);
            FUN_00449420((char*)this + 0xa8, 0);
            nb->CalculateSymmetrySign();
            if (mModel != 0) {
                cSPEditorBlock* sc = mSocket;
                if (sc != 0) {
                    cSPEditorBlock* linked = sc->mLinked;
                    if (linked != 0 && ((ModelObj*)mModel)->FUN_004adc40()) {
                        sc->mLinked->FUN_004388b0(nb);
                    } else {
                        if (mSocket->FUN_004a7e60(mSocket))
                            mSocket->FUN_004388b0(nb);
                        else
                            mSocket->FUN_004388b0(nb);
                    }
                }
            }
            bool f = GetFlag(0xc);
            nb->SetFlag(0xc, f ? 1 : 0);
            if (type == 3) {
                Vector3 a;
                Vector3 b;
                TrackerGetOffsetA(a.v, 1);
                a.v[0] = a.v[0] * g_negOne;
                TrackerGetOffsetB(b.v, 1);
                b.v[0] = b.v[0] * g_negOne;
                nb->TrackerPlace(b, a);
            } else {
                Vector3 b;
                Vector3 a;
                TrackerGetOffsetB(b.v, 1);
                TrackerGetOffsetA(a.v, 1);
                nb->TrackerPlace(a, b);
            }
        }
    }
    vB.Dtor();
    vA.Dtor();
    return nb;
}
