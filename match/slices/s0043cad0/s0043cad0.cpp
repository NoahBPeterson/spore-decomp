// SP::cSPEditorBlock — model-slot management (unoptimized /Od /Ob1 /arch:SSE /fp:fast).
#include "types.h"

namespace SP {

struct Vec3 { float x, y, z; };

// cSPBoundingBox — PDB size 0x18 (mMin / mMax).
struct cSPBoundingBox {
    Vec3  mMin;                                            // +0x00
    Vec3  mMax;                                            // +0x0c
    Vec3* FUN_00409B90(Vec3* out);                         // 0x00409B90 (BoundingBox_GetCenter)
};

// cSPTransform — PDB size 0x38 (mFlags / mModificationCount / mTranslation / mScale / mRotation).
struct cSPTransform {
    unsigned short mFlags;                                 // +0x00
    unsigned short mModificationCount;                     // +0x02
    Vec3           mTranslation;                           // +0x04
    float          mScale;                                 // +0x10
    float          mRotation[9];                           // +0x14 (cSPMatrix3)
    cSPTransform*  FUN_0040CE80(const cSPTransform& src);  // 0x0040CE80 (assign)
    void           FUN_0040CCB0(const cSPTransform& m);    // 0x0040CCB0 (compose)
    void           FUN_0040CD80(void* p);                  // 0x0040CD80
    void           FUN_00409930();                         // 0x00409930 (ctor)
    cSPTransform*  FUN_00537DC0(const void* src);          // 0x00537DC0 (cSPTransformOps::Assign)
};

// eastl vector of 0x30-byte elements (used by the effect-bone pipeline).
struct Vec48 {
    void* begin;                                           // +0x00
    void* end;                                             // +0x04
    void* cap;                                             // +0x08
    void  FUN_0041D510(void* src);                         // 0x0041D510 (init from source data)
    void  FUN_00428130();                                  // 0x00428130 (free storage)
};

// cMWModel head: base_cMWObject keeps its cSPTransform at +0x08 (PDB).
struct cMWModel {
    char         pad00[0x08];
    cSPTransform mTransform;                               // +0x08
};

// cSPEditorModel — the editor-model node stored at cSPEditorBlock+0x28.
struct cSPEditorModel {
    bool FUN_004adb80();                                   // 0x004ADB80
    bool FUN_004adbc0();                                   // 0x004ADBC0
};

// Slot objects held in the +0x154 array (indexed model part).
struct Blk {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void SetState(int a, int b);                   // vtbl +0x30
};

// cIModelWorld virtual layout; only slots 0x84 / 0x8C / 0x108 are used here.
#define SV(n) virtual void sv##n();
struct cIModelWorld {
    SV(00) SV(01) SV(02) SV(03) SV(04) SV(05) SV(06) SV(07) SV(08) SV(09) SV(10) SV(11)
    SV(12) SV(13) SV(14) SV(15) SV(16) SV(17) SV(18) SV(19) SV(20) SV(21) SV(22) SV(23)
    SV(24) SV(25) SV(26) SV(27) SV(28) SV(29) SV(30) SV(31) SV(32)
    virtual void* f84(void* model);                        // +0x84
    SV(34)
    virtual void  f8C(void* model, void* begin);           // +0x8C
    SV(36) SV(37) SV(38) SV(39) SV(40) SV(41) SV(42) SV(43) SV(44) SV(45) SV(46) SV(47)
    SV(48) SV(49) SV(50) SV(51) SV(52) SV(53) SV(54) SV(55) SV(56) SV(57) SV(58) SV(59)
    SV(60) SV(61) SV(62) SV(63) SV(64) SV(65)
    virtual void* f108(void* model);                       // +0x108
};
#undef SV

// cSPEditorBlock — the +0x14C.. members carry an extra 8 bytes in retail, so the
// offsets below are the retail ones (PDB dev offsets +8, verified against the image).
class cSPEditorBlock { public:
    char             pad00[0x10];
    cMWModel*        mModel;                 // +0x10
    char             pad14[0x18 - 0x14];
    cIModelWorld*    mModelWorld;            // +0x18
    char             pad1c[0x28 - 0x1c];
    cSPEditorModel*  mEditorModel;           // +0x28
    char             pad2c[0x154 - 0x2c];
    Blk*             slots[3];               // +0x154
    Blk*             slot160;                // +0x160
    char             pad164[0x1B0 - 0x164];
    int              f1b0;                   // +0x1B0
    char             pad1b4[0x24C - 0x1B4];
    cSPTransform     mEffectBoneRestPose;    // +0x24C (PDB +0x244)
    cSPTransform     mEffectBoneTransform;   // +0x284 (PDB +0x27C)
    int              mEffectBoneIndex;       // +0x2BC (PDB +0x2B4)
    char             pad2c0[0x2F8 - 0x2C0];
    // Retail folds PDB's mPinningOrientationOffset + mTrianglePickDirection into one
    // cSPTransform here; the pick-direction read lands on its mTranslation (+0x2FC).
    cSPTransform     mPinningOrientationOffset;  // +0x2F8
    char             pad330[0x3EC - 0x330];
    void*            p3ec;                   // +0x3EC
    char             pad3f0[0x6CC - 0x3F0];
    void**           vec6cc;                 // +0x6CC
    void**           vec6d0;                 // +0x6D0
    char             pad6d4[0xDC8 - 0x6D4];
    uint32_t         flags0;                 // +0xDC8 (cSPEditorBlock::mFlags word 0)
    uint32_t         flags1;                 // +0xDCC (cSPEditorBlock::mFlags word 1)

    Blk* GetSlot(int i);                     // 0043CE00
    void F3cad0();                           // 0043CAD0
    void F3ce40();                           // 0043CE40
    void F3cfc0(int p2, char p3);            // 0043CFC0
    Vec3* F3d240(Vec3* out, char p3);        // 0043D240
    void F3d420();                           // 0043D420
    cSPBoundingBox FUN_0044AE00(int a, bool b, bool c);  // 0044AE00 (GetBBox)
};

void* Sub_401060();                        // 00401060 (app/manager singleton)
bool  Sub_4A6120(void* self);              // 004A6120
void  Sub_4A6660(void* self, uint8_t v);   // 004A6660
void  Sub_4A88D0(int id);                  // 004A88D0
// Vector3 __cdecl operator*(const Vector3&, const float&): hidden result buffer first.
void  FUN_0041DCA0(Vec3* out, const Vec3* v, const float* s);  // 0041DCA0
void  FUN_00732270(void* dst, const void* src);                 // 00732270

// @ 0x0043CE00
Blk* cSPEditorBlock::GetSlot(int i)
{
    if (i >= 0 && i < 3) {
        Blk* p = slots[i];
        return p;
    }
    return 0;
}

// @ 0x0043CAD0
void cSPEditorBlock::F3cad0()
{
    bool f6 = false, f5 = false;
    if (mEditorModel != 0) {
        f6 = mEditorModel->FUN_004adb80();
        f5 = mEditorModel->FUN_004adbc0();
    }
    bool changed = false;
    if (!f6) F3ce40();
    if ((flags0 & 0x2000000u) == 0) {
        for (int i = 0; i < 3; i++) {
            Blk* b = slots[i];
            if (b != 0 && (*(uint8_t*)((char*)b + 0x92) == 0 || f6)) {
                b->SetState(3, 1);
                changed = true;
            }
        }
        if (slot160 != 0 && (*(uint8_t*)((char*)slot160 + 0x5D) == 0 || f6)) {
            slot160->SetState(3, 1);
            changed = true;
        }
    }
    if ((flags0 & 0x1000000u) == 0) {
        int skip = -1;
        if ((flags0 & 0x800u) != 0 && !f5) skip = f1b0;
        int count = (int)(vec6d0 - vec6cc);
        for (int i = 0; i < count; i++) {
            Blk* b = *(Blk**)((char*)vec6cc + i * 4);
            if (i != skip && (*(uint8_t*)((char*)b + 0x1D4) == 0 || f6)) {
                b->SetState(3, 1);
                changed = true;
            }
        }
    }
    if (changed) Sub_4A88D0(0xD0A55625);
}

// @ 0x0043CE40
void cSPEditorBlock::F3ce40()
{
    if (Sub_401060() == 0) return;
    for (int i = 0; i < 3; i++) {
        Blk* b = slots[i];
        if (b != 0 && *(uint8_t*)((char*)b + 0x92) != 0) b->SetState(1, 1);
    }
    if (slot160 != 0 && *(uint8_t*)((char*)slot160 + 0x5D) != 0) slot160->SetState(1, 1);
    int count = (int)(vec6d0 - vec6cc);
    for (int i = 0; i < count; i++) {
        Blk* b = *(Blk**)((char*)vec6cc + i * 4);
        if (*(uint8_t*)((char*)b + 0x1D4) != 0) b->SetState(1, 1);
    }
}

// @ 0x0043CFC0
void cSPEditorBlock::F3cfc0(int p2, char p3)
{
    if (Sub_401060() == 0) return;
    if ((flags0 & 0x2000000u) == 0) {
        for (int i = 0; i < 3; i++) {
            Blk* b = slots[i];
            if (b != 0 && (void*)b != (void*)p2) b->SetState(1, 1);
        }
        if (slot160 != 0 && (void*)slot160 != (void*)p2) slot160->SetState(1, 1);
    }
    if (p3 != 0 && Sub_4A6120(this)) {
        uint8_t d = 0;
        if (p2 != 0 && (void*)p2 == p3ec) d = 1;
        Sub_4A6660(this, d);
    }
    if ((flags0 & 0x1000000u) == 0) {
        int count = (int)(vec6d0 - vec6cc);
        for (int i = 0; i < count; i++) {
            void* e = *(void**)((char*)vec6cc + i * 4);
            if ((void*)p2 != e) ((Blk*)e)->SetState(1, 1);
        }
    }
}

// @ 0x0043D240
Vec3* cSPEditorBlock::F3d240(Vec3* out, char p3)
{
    if ((flags1 & 0x400000u) != 0) {
        if (p3 == 0) {
            float key = mModel->mTransform.mScale;
            Vec3 picked;
            FUN_0041DCA0(&picked, &mPinningOrientationOffset.mTranslation, &key);
            out->x = picked.x;
            out->y = picked.y;
            out->z = picked.z;
        } else {
            cSPTransform a;
            a.FUN_0040CE80(mModel->mTransform);
            a.FUN_0040CCB0(mPinningOrientationOffset);
            cSPTransform b;
            b.FUN_0040CE80(a);
            out->x = b.mTranslation.x;
            out->y = b.mTranslation.y;
            out->z = b.mTranslation.z;
        }
    } else if (p3 == 0) {
        FUN_0044AE00(1, false, false).FUN_00409B90(out);
    } else {
        FUN_0044AE00(0, false, false).FUN_00409B90(out);
    }
    return out;
}

// @ 0x0043D420
void cSPEditorBlock::F3d420()
{
    if (mModel == 0) return;
    if ((flags1 & 0x80u) == 0) return;
    if (mEffectBoneIndex == -1) return;

    void* bone = mModelWorld->f84(mModel);
    cSPTransform xf;
    xf.FUN_00409930();
    Vec48 vec;
    vec.FUN_0041D510(bone);
    mModelWorld->f8C(mModel, vec.begin);
    FUN_00732270((char*)vec.begin + mEffectBoneIndex * 0x30, &xf);
    xf.FUN_0040CCB0(mEffectBoneRestPose);
    bone = mModelWorld->f108(mModel);
    xf.FUN_0040CD80(bone);
    xf.mScale = 1.0f;
    xf.mModificationCount = (unsigned short)(xf.mModificationCount + 1);
    mEffectBoneTransform.FUN_00537DC0(&xf);
    for (char* p = (char*)vec.begin; p < (char*)vec.end; p += 0x30) { }
    vec.FUN_00428130();
}

} // namespace SP