// src/game/SPEngine/SPGraphicsModelInstance.cpp -- migrated from slice(s) s0073bf20, s00742b30, s00741b10, s00741210, s007403c0, s0073f320, s0073e410, s0073d6b0, s0073cdf0, s0073afb0, s0073a110 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsModelInstance.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cModelInstance.h"
#include <intrin.h>
#include "SP/cMaterial.h"
#include "SP/cMDBoneTransform.h"
#include <xmmintrin.h>
#include "SP/cBoneRange.h"
#include "cSPTransform.h"
#include "cSPBoundingBox.h"
#include "rw/core/arena/Arena.h"
#include <new>
#include <math.h>
#include "rw/graphics/EmbeddedState.h"

// ---- items of slice s0073a110 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cAnimGroupInfo_s0073_a110 {
    char  mBindingIdx;      // +0
    char  mBoneCount;       // +1
    short mBoneOffset;      // +2
    char  mAnimCount;       // +4
    char  mAnimFirstDeform; // +5
    short mAnimOffset;      // +6
};
}
namespace SP {
struct cAnimDef { char pad0[8]; int mId; char pad0c[0x14]; float mLength; };   // KeyframeAnimation (id +8, length +0x20)
}
namespace SP {
struct cIdObj { char pad0[0x10]; int mId; };           // +0x10 id
}
namespace SP {
struct cBindInfo {
    char pad0[0xc];
    cIdObj* m0c;                                       // +0x0c
    cIdObj* m10;                                       // +0x10
    char pad14[4];
    int m18;                                           // +0x18
};
}
namespace SP {
struct cBlender {                                      // cMultiBlender-like player
    char pad0[4];
    void** mVptr4;                                     // +0x04 (vtable of the played interface)
    char pad8[0x14];
    cAnimDef* mDef;                                    // +0x1c
    float mTime;                                       // +0x20
    bool AnyAnimating();                               // 0x0075a6e0 cMultiBlender::AnyAnimating
    void SetAnimating(cAnimDef* a, bool v);            // 0x0075b6e0 cMultiBlender::SetAnimating
    void SetLooping(bool v);                           // 0x0075a770 (byte at +0x50)
    void SetAnim(cAnimDef* a, float start);            // 0x011fdba0
};
}
namespace SP {
struct cBinding_s0073_a110 {                                      // 12-byte binding record
    cBlender* mBlender;                                // +0
    bool mActive;                                      // +4
    bool mLoop;                                        // +5
    short pad6;
    cBindInfo* mInfo;                                  // +8
};
}
namespace SP {
struct cMaterial_s0073_a110 {                                     // 0xc4-byte record, same prefix as cBinding
    cBlender* mBlender;
    bool mActive;
    bool mLoop;
    short pad6;
    cBindInfo* mInfo;
    char pad0c[0xc4 - 0xc];
};
}
namespace SP {
struct cCtrlEntry { int mKey; cAnimDef* mDef; };       // 8 bytes
}
namespace SP {
struct AnimGroupVec {
    cAnimGroupInfo_s0073_a110* mpBegin;
    cAnimGroupInfo_s0073_a110* mpEnd;
    cAnimGroupInfo_s0073_a110* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
    cAnimGroupInfo_s0073_a110& operator[](int i) { return mpBegin[i]; }
};
}
namespace SP {
class cModelInstance_s0073_a110 {
public:
    char pad0[8];                   // +0x00
    unsigned mFlags8;               // +0x08 (bit 0x20: multi-blender mode)
    int  mFieldC;                   // +0x0c
    int  mField10;                  // +0x10
    AnimGroupVec mAnimGroups;       // +0x14 (begin/end/cap; size() and operator[] stay inline calls)
    char pad20[0x28 - 0x20];
    cMaterial_s0073_a110* mMaterials;          // +0x28
    cMaterial_s0073_a110* mMaterialsEnd;       // +0x2c
    char pad30[0x3c - 0x30];
    cBinding_s0073_a110* mBindABegin;          // +0x3c
    cBinding_s0073_a110* mBindAEnd;            // +0x40
    char pad44[0x50 - 0x44];
    cBinding_s0073_a110* mBindCBegin;          // +0x50
    cBinding_s0073_a110* mBindCEnd;            // +0x54
    char pad58[0x78 - 0x58];
    int* mControllers;              // +0x78
    char pad7c[0x154 - 0x7c];
public:
    // @ 0x0073ABB0
    int GetAnimationMoveToTimes(int animID, int* dst, char bEnd);  // 0x0073abb0 (SP::cModelInstance::GetAnimationMoveToTimes)
    bool SetActive(int key, int groupIdx, bool animating, float t, bool loop);  // 0x0073ac20 (SP::cModelInstance::SetActive)
    bool AdvanceBinding(cBinding_s0073_a110* b, float dt);
    bool IsValidGroup(int i) {
        return i >= 0 && i < mAnimGroups.size();
    }
};
}
namespace SP {
static __forceinline void ApplyBinding(cModelInstance_s0073_a110* mi, cBinding_s0073_a110* b, cAnimDef* target, bool animating, float t, bool loop)
{
    if (mi->mFlags8 & 0x20) {
        cBlender* bl = b->mBlender;
        bl->SetAnimating(target, animating);
        bl->SetLooping(!loop);
        b->mActive = true;
    } else {
        cBlender* bl = b->mBlender;
        if (animating) {
            if (target != bl->mDef || !b->mActive) {
                if (target != bl->mDef)
                    bl->SetAnim(target, t);
                b->mActive = true;
            }
        } else if (target == bl->mDef) {
            b->mActive = false;
        }
    }
}  // namespace SP
}
struct AbIface { virtual void ifn0(); };
struct AbRC { AbRC() : mRC(0) {} virtual void rcfn0(); virtual void rcfn1(); int mRC; };
struct AbHeld { virtual void dtor(int) = 0; int mnRefCount; };
struct AbilityA : AbIface, AbRC {
    AbilityA(AbHeld* h, int v) { mHeld = h; if (h) ++h->mnRefCount; mVal = v; }
    virtual void a0();
    virtual void a1();
    AbHeld* mHeld;      // +0xc
    int mVal;           // +0x10
};
struct AbPtr { AbHeld* p; AbPtr() : p(0) {} };
struct AbilityB : AbilityA {
    AbilityB(AbHeld* h, int v, int a, int b);
    virtual void b0();
    virtual void b1();
    AbPtr mHeld2;       // +0x14
    int mB18;           // +0x18
    int mB1c;           // +0x1c
};
// ---- items of slice s0073a110 end

// ---- items of slice s0073afb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
bool IsFinite(float f);                // 0x0059ab10 cdecl
}
namespace SP {
void NotifyAdd(void* info, void* blender, void* other, int arg);   // 0x006c1cd0 cdecl
}
namespace SP {
void NotifyAlloc();                    // 0x007c5490
}
namespace SP {
struct cBindInfo_s0073_afb0;
}
namespace SP {
void __fastcall FinishNotify(cBindInfo_s0073_afb0* info);   // 0x01200940 (thiscall, no args)
}
namespace SP {
struct cAnimGroupInfo_s0073_afb0 {
    char  mBindingIdx;      // +0
    char  mBoneCount;       // +1
    short mBoneOffset;      // +2
    char  mAnimCount;       // +4
    char  mAnimFirstDeform; // +5
    short mAnimOffset;      // +6
};
}
namespace SP {
struct cBindInfo_s0073_afb0 {                  // per-binding info (three layouts of the same record are read)
    char    pad0[0xc];
    cIdObj* m0c;                    // +0x0c
    cIdObj* m10;                    // +0x10
    char    pad14[4];
    int     m18;                    // +0x18
};
}
namespace SP {
struct cBlender_s0073_afb0 {                   // animation player / cMultiBlender; vptr of the played interface at +4
    int     pad0;
    void**  mVptr4;                 // +0x04
    char    pad8[0x14];
    cAnimDef* mDef;                 // +0x1c
    float   mTime;                  // +0x20
    bool AnyAnimating();                            // 0x0075a6e0 cMultiBlender::AnyAnimating
    void SetWeight(cAnimDef* d, float w);           // 0x0075b630 cMultiBlender::SetWeight
    void SetAnimTime(cAnimDef* d, float t);         // 0x0075b5d0 cMultiBlender::SetAnimTime
    void SetAllTime(float t);                       // 0x0075a690
    void SetAnim(cAnimDef* d, float start);         // 0x011fdba0
    void SetTime(float t);                          // 0x011fe600
};
}
namespace SP {
struct cBinding_s0073_afb0 {                   // 12-byte binding record
    cBlender_s0073_afb0*  mBlender;            // +0
    bool       mActive;             // +4
    bool       mLoop;               // +5
    short      pad6;
    cBindInfo_s0073_afb0* mInfo;               // +8
};
}
namespace SP {
struct cAnimEntry { int mKey; cAnimDef* mDef; };   // 8 bytes
}
namespace SP {
struct cMaterial_s0073_afb0 {
    cBlender_s0073_afb0*  mBlender;            // +0 (same prefix as cBinding)
    bool       mActive;             // +4
    bool       mLoop;               // +5
    short      pad6;
    cBindInfo_s0073_afb0* mInfo;               // +8
    char  pad0[0xb8 - 0xc];
    void* f_b8;             // +0xb8
    void* f_bc;             // +0xbc
    void* f_c0;             // +0xc0
};
}
namespace SP {
class cModelInstance_s0073_afb0 {
public:
    char pad0[8];                   // +0x00
    unsigned mFlags8;               // +0x08 (bit 0x20: multi-blender mode)
    int mFieldC;                    // +0x0c
    void* mField10;                 // +0x10
    cAnimGroupInfo_s0073_afb0* mGroupBegin;    // +0x14
    cAnimGroupInfo_s0073_afb0* mGroupEnd;      // +0x18
    char pad1c[0x28 - 0x1c];
    cMaterial_s0073_afb0* mMaterials;          // +0x28
    cMaterial_s0073_afb0* mMaterialsEnd;       // +0x2c
    int mField30;                   // +0x30 (address forwarded to a virtual call)
    char pad34[0x3c - 0x34];
    cBinding_s0073_afb0* mBindABegin;          // +0x3c
    cBinding_s0073_afb0* mBindAEnd;            // +0x40
    char pad44[0x50 - 0x44];
    cBinding_s0073_afb0* mBindCBegin;          // +0x50
    cBinding_s0073_afb0* mBindCEnd;            // +0x54
    char pad58[0x64 - 0x58];
    cBlender_s0073_afb0** mBlendBegin;         // +0x64
    cBlender_s0073_afb0** mBlendEnd;           // +0x68
    char pad6c[0x78 - 0x6c];
    cAnimEntry* mEntryBegin;        // +0x78
    cAnimEntry* mEntryEnd;          // +0x7c
    char pad80[0x90 - 0x80];
    long long mCounter;             // +0x90
    char pad98[0xc8 - 0x98];
    unsigned short mFlags;          // +0xc8
    char padca[0xec - 0xca];
    void* mDynDraw;                 // +0xec
    char padec[0x8];
    char padf4[0x60];

public:
    bool UpdateBinding(cBinding_s0073_afb0* e, float dt);       // 0x0073af20
    void Animate(float dt);  // 0x0073afb0 (SP::cModelInstance::Animate)
    void MoveToTime(int key, int grp, float t);  // 0x0073b190 (SP::cModelInstance::MoveToTime)
    void SetWeight(int key, int grp, float w);  // 0x0073b530 (SP::cModelInstance::SetWeight)
    bool GetAnimationRange(int key, int grp, float* pMin, float* pMax);  // 0x0073b6d0 (SP::cModelInstance::GetAnimationRange)
    void Notify(struct cNotifyOther* other);
    // @ 0x0073B7E0
    int GetNumBones();  // 0x0073b7e0 (SP::cModelInstance::GetNumBones)
    // @ 0x0073B800
    void SetBoneTable(int a, void* b);  // 0x0073b800 (SP::cModelInstance::SetBoneTable)
    // @ 0x0073B840
    void SetBoneCallback(int boneIndex, void* a2, void* a3, void* a4);  // 0x0073b840 (SP::cModelInstance::SetBoneCallback)
    // @ 0x0073B8E0
    void SetDynamicDraw(void* p, bool flag);  // 0x0073b8e0 (SP::cModelInstance::SetDynamicDraw)
};
}
namespace SP {
struct DynDrawObj {
    void** vftable;                 // +0
    int mnRefCount;                 // +4
};
}
namespace SP {
struct cNotifyOther { char pad0[0x40]; int mField40; };
}
namespace SP {
static __forceinline void StepBinding(cModelInstance_s0073_afb0* self, cBinding_s0073_afb0* e, float dt, bool& any)
{
    float t = dt;
    cBlender_s0073_afb0* b = e->mBlender;
    if (b != 0 && e->mActive) {
        if (self->mFlags8 & 0x20) {
            if (!b->AnyAnimating())
                return;
            ((void(__thiscall*)(cBlender_s0073_afb0*, float))e->mBlender->mVptr4[0])(e->mBlender, dt);
        } else {
            float end = b->mDef->mLength;
            float cur = b->mTime;
            if (e->mLoop && cur + dt >= end) {
                t = end - cur;
                e->mActive = false;
            }
            ((void(__thiscall*)(cBlender_s0073_afb0*, float))b->mVptr4[0])(b, t);
        }
        any = true;
    }
}
}
// ---- items of slice s0073afb0 end

// ---- items of slice s0073cdf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float* __cdecl OrthogonalVector(float* out, const float* v);   // 0x006985b0
struct ArenaResource {
    virtual void  v0();
    virtual void  v1();
    virtual void  v2();
    virtual void* v3(uint32_t id);
};
struct ArenaElem {                 // element stride 0x7c
    char pad74[0x74];
    int  field74;                  // +0x74
    char pad78[4];
};
struct ArenaHolder {               // value returned by ArenaResource::v3 for the mesh set
    char    pad108[0x108];
    ArenaElem* begin;              // +0x108
    ArenaElem* end;                // +0x10c
};
struct cModelInstance_GetArenaResource {
    char pad[0xc4];
    ArenaResource* mResource;   // +0xc4
    int GetArenaResource();
};
struct BaseResourceDescriptor {
    uint32_t m_size, m_alignment;
    BaseResourceDescriptor();         // 0x006c0fa0
    ~BaseResourceDescriptor();        // 0x00c2e4e0
};
struct RwResource { uint32_t a, b, c, d; };
struct ExportedObj {
    uint32_t  type;    // +0x0  (0xff0000 == exported mesh)
    void*     data;    // +0x4
    RwResource resource;               // +0x8
    BaseResourceDescriptor desc[4];    // +0x18
    ExportedObj() {
        resource.a = 0; resource.b = 0; resource.c = 0; resource.d = 0;
        type = 0; data = 0;
        desc[0].m_size = 0; desc[0].m_alignment = 1;
    }
};
struct Arena_s0073_cdf0 {
    int  GetNumExportedObjects();                                  // 0x011e23a0
    void GetExportedObjectByIndex(int index, ExportedObj* out);   // 0x011e28e0
};
struct ExportedMesh {
    uint32_t id;           // +0x0
    uint32_t pad4;
    double   d[6];         // +0x8 .. +0x30
    float    f38;          // +0x38
};
struct DeformHandle {
    int       mZero;       // +0x0
    uint16_t  mFlags;      // +0x4
    uint16_t  mVersion;    // +0x6
    float     mPos[3];     // +0x8
    uint32_t  pad14;
    float     mRot[9];     // +0x18
    uint32_t  mId;         // +0x3c
    float     mP0[3];      // +0x40
    float     mP1[3];      // +0x4c
    float     mF58;        // +0x58
};
struct cModelInstance_Deform {
    char pad14[0x14];
    void* m14;              // +0x14
    void* m18;              // +0x18
    int*  m1c;              // +0x1c
    char pad1c[0xd0];
    void* mDynamicDraw;     // +0xf0
    char pad2[4];

    int GetArenaResource();                       // 0x73d160
    bool  FillTransform(float* out);              // 0x73cdf0
    int   GetDeformationHandles(DeformHandle* dst, int maxCount);  // 0x73d1e0
};
// ---- items of slice s0073cdf0 end

// ---- items of slice s0073d6b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kOne;                                              // _DAT_01485720
struct __declspec(align(16)) Mat4 {
    __m128 r[4];        // rows; rows 0-2 are the 3x3 part, row 3 the translation
    Mat4() {}
    Mat4(const Mat4& o) { r[0] = o.r[0]; r[1] = o.r[1]; r[2] = o.r[2]; r[3] = o.r[3]; }
    Mat4& operator=(const Mat4& o) { r[0] = o.r[0]; r[1] = o.r[1]; r[2] = o.r[2]; r[3] = o.r[3]; return *this; }
};
static __forceinline bool AffineInverse(Mat4& o, const float* m)
{
    const __m128 Z = _mm_set1_ps(0.0f);
    const __m128 O = _mm_set1_ps(1.0f);
#define E(k) _mm_set1_ps(m[k])
#define MUL _mm_mul_ps
#define SUB _mm_sub_ps
#define ADD _mm_add_ps
    __m128 det = ADD(ADD(MUL(SUB(MUL(E(5), E(10)), MUL(E(6), E(9))), E(0)),
                         MUL(SUB(MUL(E(6), E(8)), MUL(E(10), E(4))), E(1))),
                     MUL(SUB(MUL(E(9), E(4)), MUL(E(5), E(8))), E(2)));
    if (_mm_movemask_ps(_mm_cmpeq_ps(det, Z)) == 0xf)
        return false;

    __m128 i32 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(5), E(2)), MUL(E(6), E(1))), E(12)),
                                    MUL(SUB(MUL(E(6), E(0)), MUL(E(4), E(2))), E(13))),
                                MUL(SUB(MUL(E(4), E(1)), MUL(E(5), E(0))), E(14))), det);
    __m128 i31 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(13), E(2)), MUL(E(14), E(1))), E(8)),
                                    MUL(SUB(MUL(E(14), E(0)), MUL(E(12), E(2))), E(9))),
                                MUL(SUB(MUL(E(12), E(1)), MUL(E(13), E(0))), E(10))), det);
    __m128 i30 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(13), E(10)), MUL(E(9), E(14))), E(4)),
                                    MUL(SUB(MUL(E(14), E(8)), MUL(E(10), E(12))), E(5))),
                                MUL(SUB(MUL(E(9), E(12)), MUL(E(13), E(8))), E(6))), det);
    __m128 i22 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(1), Z), MUL(E(5), Z)), E(12)),
                                    MUL(SUB(MUL(E(5), E(0)), MUL(E(4), E(1))), O)),
                                MUL(SUB(MUL(E(4), Z), MUL(E(0), Z)), E(13))), det);
    __m128 i21 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(1), O), MUL(E(13), Z)), E(8)),
                                    MUL(SUB(MUL(E(13), E(0)), MUL(E(12), E(1))), Z)),
                                MUL(SUB(MUL(E(12), Z), MUL(E(0), O)), E(9))), det);
    __m128 i20 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(13), E(8)), MUL(E(9), E(12))), Z),
                                    MUL(SUB(MUL(E(9), O), MUL(E(13), Z)), E(4))),
                                MUL(SUB(MUL(E(12), Z), MUL(E(8), O)), E(5))), det);
    __m128 i12 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(4), E(2)), MUL(E(6), E(0))), O),
                                    MUL(SUB(MUL(E(0), Z), MUL(E(4), Z)), E(14))),
                                MUL(SUB(MUL(E(6), Z), MUL(E(2), Z)), E(12))), det);
    __m128 i11 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(12), E(2)), MUL(E(14), E(0))), Z),
                                    MUL(SUB(MUL(E(0), O), MUL(E(12), Z)), E(10))),
                                MUL(SUB(MUL(E(14), Z), MUL(E(2), O)), E(8))), det);
    __m128 i10 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(10), E(12)), MUL(E(14), E(8))), Z),
                                    MUL(SUB(MUL(E(8), O), MUL(E(12), Z)), E(6))),
                                MUL(SUB(MUL(E(14), Z), MUL(E(10), O)), E(4))), det);
    __m128 i02 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(2), Z), MUL(E(6), Z)), E(13)),
                                    MUL(SUB(MUL(E(5), Z), MUL(E(1), Z)), E(14))),
                                MUL(SUB(MUL(E(6), E(1)), MUL(E(5), E(2))), O)), det);
    __m128 i01 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(2), O), MUL(E(14), Z)), E(9)),
                                    MUL(SUB(MUL(E(13), Z), MUL(E(1), O)), E(10))),
                                MUL(SUB(MUL(E(14), E(1)), MUL(E(13), E(2))), Z)), det);
    __m128 i00 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(10), O), MUL(E(14), Z)), E(5)),
                                    MUL(SUB(MUL(E(13), Z), MUL(E(9), O)), E(6))),
                                MUL(SUB(MUL(E(9), E(14)), MUL(E(13), E(10))), Z)), det);
#undef E
#undef MUL
#undef SUB
#undef ADD
    o.r[0] = _mm_unpacklo_ps(_mm_unpacklo_ps(i00, i02), _mm_unpacklo_ps(i01, i00));
    o.r[1] = _mm_unpacklo_ps(_mm_unpacklo_ps(i10, i12), _mm_unpacklo_ps(i11, i10));
    o.r[2] = _mm_unpacklo_ps(_mm_unpacklo_ps(i20, i22), _mm_unpacklo_ps(i21, i20));
    o.r[3] = _mm_unpacklo_ps(_mm_unpacklo_ps(i30, i32), _mm_unpacklo_ps(i31, i30));
    return true;
}
struct cSPTransformP {
    uint16_t mFlags;
    uint16_t mModificationCount;
    float    mTranslation[3];
    float    mScale;
    float    mRotation[9];
    void BackTransformPoint(__m128* p);                    // 0x004ff6d0 (thiscall)
};
static __forceinline float Lane(__m128 v, int k) { return ((const float*)&v)[k]; }
struct BoneRow {
    float x, y, z, w;
};
struct cMDBoneTransform {
    BoneRow m[3];
};
struct cSkinPalette {
    Mat4*        mpMatrices;  // +0x0  per-bone 4x4 (bind) matrices
    unsigned int mnBones;     // +0x4
};
struct cPoseOwner {
    uint32_t      pad0[4];
    cSkinPalette* mpSkin;     // +0x10
};
struct cModelInstance_Pose {
    uint32_t pad0[10];
    cPoseOwner** mpMaterialsBegin;  // +0x28 cModelResourceInfo::mMaterials.mpBegin
    cPoseOwner** mpMaterialsEnd;    // +0x2c
    uint32_t pad30[(0x154 - 0x30) / 4];

    // @ 0x0073d6b0  SP::cModelInstance::GetPoseTransforms
    int GetPoseTransforms(cMDBoneTransform* dst, bool original);

    // SP::cModelInstance::PickLineWithHit (PDB candidate; marker at the definition below)
    bool PickLineWithHit(const float* pLine, const float* pDir, cSPTransformP* pTransform,
                         float* pOut);
};
struct BaseResDesc {                     // rw::BaseResourceDescriptor {size, alignment}
    unsigned mSize, mAlign;
    BaseResDesc();                       // 0x006c0fa0
    ~BaseResDesc();                      // 0x00c2e4e0
};
struct ResDesc4 { BaseResDesc d[4]; };
struct ResDescCombined { unsigned raw[4]; };
extern ResDesc4 FUN_01201660_t(int a, int b);                         // 0x01201660 (cdecl, hidden return)
extern void*    FUN_006c1c80_t(ResDescCombined* out, ResDesc4* in);   // 0x006c1c80 (cdecl)
extern void*    FUN_012016d0_t(ResDescCombined* desc, int a, int b);  // 0x012016d0 (cdecl)
struct HitRec_s0073_d6b0 {                          // 0xd0-byte ray-hit record
    char  pad0[0x40];
    float mDist;                         // +0x40
    char  pad44[0xd0 - 0x44];
};
struct PickCtx {                         // cached pick/traversal context (global singleton)
    char     pad0[0x10];
    HitRec_s0073_d6b0*  mpHits;                     // +0x10
    int      mnHits;                     // +0x14
    char     pad18[0xe8 - 0x18];
    int      mE8;                        // +0xe8
    char     padec[0x100 - 0xec];
    int      mMode;                      // +0x100
    void Init(void** ppBuf, int a, int b, const __m128* pOrigin, const __m128* pDir);   // 0x0073a6e0 (thiscall)
};
extern PickCtx* g_pPickCtx;              // 0x0162eaec
struct XformBlock {                      // three scaled rotation rows + translation row
    float r0[4], r1[4], r2[4];
    float t[4];
};
struct Vec3S {
    float x, y, z;
    Vec3S() {}
    Vec3S(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3S operator*(float s) const { return Vec3S(x * s, y * s, z * s); }
};
struct DbObj {                           // result of GetAllocator(): object with a vtable pointer at +0x20
    char pad[0x20];
    void** mpVtbl2;
};
struct DatabasePackedFileT {
    DbObj* GetAllocator();                                            // 0x007f54d0 (thiscall)
};
// ---- items of slice s0073d6b0 end

// ---- items of slice s0073e410 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_01200940();          // 0x1200940
extern "C" void  FUN_00730210(int, int);  // 0x730210
extern "C" void  FUN_0072fff0(int, int);  // 0x72fff0
extern "C" void  __cdecl PushShaderDataNull();                         // 0x777bf0
extern "C" void  __cdecl ShaderSet(int slot, const void* data, int n); // 0x777ae0
extern "C" void  __cdecl ShaderEnd();                                  // 0x777c10
extern "C" int   __cdecl VertexDescriptor_AreEqual(const void*, const void*);   // 0x11f2e70
extern struct { char pad[0x3c]; struct { char pad[0x58]; int f58; }* f3c; }* g_AppProps;   // 0x15fd918
extern char  g_sh_62b870[];     // 0x162b870
extern char* g_sh_62e880;       // 0x162e880
extern int   g_sh_62e874;       // 0x162e874
extern char  g_sh_62e870[];     // 0x162e870
extern char  g_sh_5377cc[];     // 0x15377cc
extern char  g_sh_5379d8;       // 0x15379d8
extern int   g_primType;        // 0x16f85a8
extern const void* g_vertDesc;  // 0x16f65a0
extern unsigned g_softState;    // 0x16f9110
extern "C" void  __cdecl FUN_007c5490b();                      // rw_AllocSerialized @0x7c5490
extern unsigned g_dirty;           // 0x16f9528
extern int      g_xfType;          // 0x16f96a0
extern "C" int   __cdecl FUN_01201660b(void* buf, int a, int b);          // @0x1201660
extern "C" void  __cdecl FUN_006c1c80b(void* buf, int v);                 // @0x6c1c80
extern "C" void  __stdcall ehvec_dtor(void* p, unsigned size, int cnt, void (__thiscall* d)(void*));  // 0x11e0b22
extern "C" void  __cdecl Elem8Dtor();                                      // 0xc2e4e0
struct Vec3A { float x, y, z, w; };
struct AABB  { Vec3A mn, mx; };
struct BBoxTest {
    AABB box;
    bool Test(const AABB* other);   // 0x73f110
};
struct RC {
    virtual void v0(int mode);
    virtual void v1();
    volatile int mnRefCount;         // +0x4
};
struct RCItem {
    char pad0[0xc];
    RC*  mpObject;                   // +0xc
    char pad10[0xb4];
};
struct V3 { float x, y, z; };
struct __declspec(align(16)) V3A {
    float x, y, z, pad;
    V3A(const V3* p) { _mm_store_ps(&x, _mm_set_ps(p->x, p->z, p->y, p->x)); }
    void set(const V3& v) { x = v.x; y = v.y; z = v.z; }
};
struct Matrix33 {
    float m[9];
    Matrix33(const Matrix33& o);       // @0x41cb40 (thiscall, ret 4)
};
struct cSPTransform_s0073_e410 {
    unsigned short mFlags;             // +0x00
    unsigned short mModificationCount; // +0x02
    float tx, ty, tz;                  // +0x04 mTranslation
    float mScale;                      // +0x10
    Matrix33 mRotation;                // +0x14
    cSPTransform_s0073_e410(const cSPTransform_s0073_e410& o)
        : mFlags(o.mFlags), mModificationCount(o.mModificationCount),
          tx(o.tx), ty(o.ty), tz(o.tz), mScale(o.mScale), mRotation(o.mRotation) {}
    cSPTransform_s0073_e410& operator=(const cSPTransform_s0073_e410& o);   // @0x537dc0
    void Invert();                                    // @0x40efa0
    void BackTransformPoint(void* p);                 // @0x4ff6d0 (thiscall, ret 4)
};
struct RCObj { void** vt; int mnRefCount; };       // refcount at +4, slot 0 = deleting dtor
struct PTBase {
    int mField0;                                   // +0x00
    union { int mField4; struct { char a, b; } mFlagBytes; };   // +0x04 (two bytes; copied as a dword)
    int mField8;                                   // +0x08
    RCObj* mpObject;                               // +0x0c (refcounted, refcount at +4)
    PTBase(int a1, RCObj* obj)
    {
        mField8 = a1;
        mField0 = 0;
        mFlagBytes.a = 0;
        mFlagBytes.b = 0;
        mpObject = obj;
        if (mpObject)
            mpObject->mnRefCount++;
    }
    PTBase(const PTBase& o)
    {
        mField0 = o.mField0;
        mField4 = o.mField4;
        mField8 = o.mField8;
        mpObject = o.mpObject;
        if (mpObject)
            mpObject->mnRefCount++;
    }
};
struct PartTransform : PTBase {
    cSPTransform_s0073_e410 mXf;                  // +0x10
    cSPTransform_s0073_e410 mXf2;                 // +0x48
    cSPTransform_s0073_e410 mInverse;             // +0x80
    int mTail0, mTail1, mTail2;        // +0xb8..+0xc0

    PartTransform(int a1, RCObj* obj, const cSPTransform_s0073_e410* t1, const cSPTransform_s0073_e410* t2);
    PartTransform(const PartTransform& o);
};
struct DynDrawElem { void* p0; void* p4; void** p8; };      // 12 bytes
struct ElemVec {
    DynDrawElem* begin;
    DynDrawElem* end;
    int size() const { return (int)(end - begin); }
};
struct DynDraw {
    char pad0[0xc];
    int f0c;                           // +0x0c
    char* f10;                         // +0x10 (stride-0x30 records)
    char pad14[0x3c];
    ElemVec mElems;                    // +0x50
};
struct Pair8 { unsigned a, b; };
struct CompiledState { void Dispatch(); };                  // rw::graphics::CompiledState::Dispatch @0x11ee580
struct ShaderDataObj {
    void Push();                                            // 0x7789d0 rw::graphics::ShaderDataState_Push
};
struct VertDesc {
    char pad0[0xc];
    unsigned short count;              // +0x0c
    char pad0e[2];
    unsigned flags;                    // +0x10
    char pad14[4];
    // +0x18: elements of 0xc bytes (kind at +4, id at +8)
    void FUN_11f2bc0();                // @0x11f2bc0
};
struct MeshCtx {                       // the object passed as arg 4 of DispatchMesh
    char pad0[0x44];
    ShaderDataObj* f44;                // +0x44
    char b48;                          // +0x48
    char pad49[3];
    int f4c;                           // +0x4c
    int refcount50;                    // +0x50
};
struct MeshDrawObj {                   // arg 1 of DispatchMesh
    char pad0[8];
    struct { char pad[0x14]; int primType; }* f08;   // +0x08
    char pad0c[0x18];
    VertDesc** f24;                   // +0x24
    void FUN_11f9710();                // @0x11f9710
};
extern "C" void  __cdecl SetShaderDataC(CompiledState*);               // 0x777b50 SP::SetShaderData
struct HullObj { void** vt; };
struct IfaceObj { void** vt; };
struct cModelInstance {
    char pad0[0x1c];
    Pair8* v1c_begin;                  // +0x1c
    Pair8* v1c_end;                    // +0x20
    char pad24[0xc];
    void** v30_begin;                  // +0x30  (elements: object with CompiledState* at +4)
    void** v30_end;                    // +0x34
    char pad38[0xc];
    RCObj** v44_begin;                 // +0x44
    RCObj** v44_end;                   // +0x48
    char pad4c[0x78];
    IfaceObj* mpIface;                 // +0xc4
    char padc8[4];
    void* mpResource;                  // +0xcc
    void* mpD0;                        // +0xd0
    char padd4[0x18];
    HullObj* mpHull;                   // +0xec
    DynDraw* mpDynDraw;                // +0xf0

    bool GetMeshes(void* a);                                   // @0x73eb90
    bool RayCast(const V3* p0, const V3* p1, cSPTransform_s0073_e410* xf, float* outT,
                 V3* outPos, V3* outNormal, int* outA, int* outB);   // @0x73e410
    void DispatchMesh(MeshDrawObj* obj, unsigned idx, int unused, MeshCtx* ctx);  // @0x73ede0
    void SetDrawTransform(const void* src, void* out);         // @0x73eca0
};
struct ElemRelease { void FUN_01200940(); };                    // @0x1200940 (thiscall)
struct __declspec(align(16)) M44Raw { float m[16]; };
struct OutM : M44Raw { int type; };
extern M44Raw*  g_xfPtr;           // 0x16fa380
extern M44Raw   g_xfLocal;         // 0x16fa4f0
struct DrawXfSrc {                 // layout of the source (a cSPTransform-like block)
    unsigned short flags; unsigned short pad2;
    V3 t;
    float s;
    float r[9];
};
struct DynDrawSink { void FUN_73bab0(void* m); };               // @0x73bab0 (thiscall, ret 4)
struct HitRec {                        // stride 0xd0
    char pad0[0x10];
    V3 pos;                            // +0x10
    char pad1c[4];
    V3 dir;                            // +0x20
    char pad2c[0x14];
    float t;                           // +0x40
    char pad44[0x8c];
};
struct IdRec { char pad[0x58]; int id; char pad5c[4]; };   // stride 0x60
struct RayCache {
    char pad0[0x10];
    HitRec* hits;                      // +0x10
    int count;                         // +0x14
    char pad18[0xcc];
    IdRec* ids;                        // +0xe4
    int fE8;                           // +0xe8
    char padec[0x14];
    int f100;                          // +0x100
    void FUN_73a6e0(void* buf, int a, int b, const V3A* p0, const V3A* p1);   // @0x73a6e0
};
struct XfBuf { void* p; };
struct AllocObj { void** vt; };
struct ResObj { AllocObj* GetAllocator(); };                              // @0x7f54d0
struct IdLookup { int FUN_729ad0(int id); };                              // @0x729ad0
extern RayCache* g_rayCache;                                              // 0x162eaf0
extern "C" RayCache* __cdecl FUN_012016d0b(void* buf, int a, int b);      // @0x12016d0
struct __declspec(align(16)) Mat4L { float r0[4], r1[4], r2[4], t[4]; };
static const float kFltMax = 3.4028234663852886e+38f;
// ---- items of slice s0073e410 end

// ---- items of slice s0073f320 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kRay0;                          // 0x153782c
extern const float kRay1;                          // 0x1537830
extern const float kRay2;                          // 0x1537834
void __cdecl EASTL_allocator_deallocate(void* p);   // 0xf47380
void __cdecl operator_delete__(void* p) throw();    // 0xf47380 (same function, nothrow view)
struct RC_s0073_f320 {
    virtual void v0(int mode);
    virtual void v1();
    int mnRefCount;                  // +0x4
};
inline void RcAddRef(RC_s0073_f320* p) { _InterlockedIncrement((volatile long*)&p->mnRefCount); }
inline void RcRelease(RC_s0073_f320* p) {
    long r = _InterlockedDecrement((volatile long*)&p->mnRefCount);
    if (r == 0) { _InterlockedExchange((volatile long*)&p->mnRefCount, 1); p->v0(1); }
}
struct T8 { int a, b; };
struct RefPair {
    int value;                       // +0x0
    RC_s0073_f320* p;                           // +0x4
};
struct DynArray {
    void* first;                     // +0x0
};
struct ArrayHolder {
    char pad[0xd0];
    DynArray* mArray;                // +0xd0
    void SetArray(DynArray* p);
};
struct cSPTransformS {
    uint16_t mFlags;
    uint16_t mModificationCount;
    float    mTranslation[3];
    float    mScale;
    float    mRotation[9];           // +0x14
    cSPTransformS& operator=(const cSPTransformS& o);   // 0x537dc0
};
struct cSkinBinding {
    int f0, f4, f8;
    RC_s0073_f320* p0c;                         // +0xc
    cSPTransformS t10;               // +0x10
    cSPTransformS t48;               // +0x48
    cSPTransformS t80;               // +0x80
    int b8, bc, c0;
    cSkinBinding& operator=(const cSkinBinding& o);
};
struct cSPTransform_s0073_f320 {                              // 0x38 bytes
    uint16_t mFlags;                               // bit 1/2: has rotation/translation
    uint16_t mModificationCount;
    float mTranslation[3];
    float mScale;                                  // +0x10
    float mRotation[9];                            // +0x14 (3 rows of 3)
    cSPTransform_s0073_f320& operator=(const cSPTransform_s0073_f320& o);   // 0x537dc0 (out of line)
    void BackTransformPoint(float* p) const;       // 0x4ff6d0
};
struct Mesh8 { signed char mat; char pad[7]; };
struct Material { char pad0[0x48]; cSPTransform_s0073_f320 src; cSPTransform_s0073_f320 dst; char pad_[0xc4 - 0xb8]; };
cSPTransform_s0073_f320& translateTransform(cSPTransform_s0073_f320& out, const cSPTransform_s0073_f320& in, const cSPTransform_s0073_f320& delta); // 0x6271a0
struct ModelInstanceAnim {
    char pad0[0x14];
    Mesh8* mMeshesBegin;   // +0x14
    Mesh8* mMeshesEnd;     // +0x18
    char pad1c[0x28 - 0x1c];
    Material* mMaterials;  // +0x28
    void SetAnimationGroupTransform(int idx, const cSPTransform_s0073_f320& t);
};
struct __declspec(align(16)) DispatchCtx { int d[0x11]; int arg3; int p48, p4c; int result; };
struct Listener { virtual void v0(); virtual void v1(); virtual void v2(); virtual void OnDispatch(void* inst, DispatchCtx* c, int a2); };
struct Processor { void Process(DispatchCtx* c); };   // 0x73bb40
struct Mesh;
struct ModelInstanceDispatch {
    char pad0[8];
    Mesh** mMeshesBegin;  // +8
    Mesh** mMeshesEnd;    // +0xc
    char pad10[0x70 - 0x10];
    char sub70[0x58];
    uint32_t mFlags;      // +0xc8
    char pad_cc[0xec - 0xcc];
    Listener* mListener;  // +0xec
    Processor* mProc;     // +0xf0
    void Setup(void* sub, DispatchCtx* c);              // 0x73eca0
    void DispatchMesh(Mesh* m, int i, int a2, DispatchCtx* c);   // 0x73ede0
    int  Dispatch(int a2, int a3);
};
inline void RcReleaseChecked(RC_s0073_f320* p) {
    long r = _InterlockedDecrement((volatile long*)&p->mnRefCount);
    if (r == 0) { _InterlockedExchange((volatile long*)&p->mnRefCount, 1); if (p) p->v0(1); }
}
struct MeshPtr { RC_s0073_f320* p; };
struct MeshVec {
    MeshPtr* b; MeshPtr* e; MeshPtr* c; int alloc[2];
    MeshVec() { b = 0; e = 0; c = 0; }
    void DestroyRange(MeshPtr* first, MeshPtr* last);   // 0x4243e0
    ~MeshVec() {
        DestroyRange(b, e);
        if (b && ((int*)b)[-1] != 0) operator_delete__(b);
    }
};
struct ModelInstanceMeshes { void GetMeshes(MeshVec& out); };   // 0x73eb90
struct BindQuery {
    RC_s0073_f320* p; int a, b, count, c, d;
    BindQuery() : p(0), a(-1), b(-1), count(0), c(-1), d(0) {}
    ~BindQuery() { if (p) RcReleaseChecked(p); }
    bool Check(void* item, int n, int i, int x, int y);      // 0x73c290
};
bool __cdecl BuildQuery(BindQuery* q, MeshVec* meshes, int arg);        // 0x732220
bool __cdecl CheckEntry(BindQuery* q, int i, void* a, void* b);         // 0x73c4b0
inline void BindFreeBuf(int* b) { if (b && b[-1] != 0) operator_delete__(b); }
struct BindPodVec {
    int* b; int* e; int* c; int alloc[2];
    BindPodVec() { b = 0; e = 0; c = 0; }
    ~BindPodVec() { BindFreeBuf(b); }
};
struct BindRcObj { virtual void v0(); virtual void Release(); };
struct BindSmartPtr { BindRcObj* p; BindSmartPtr() { p = 0; } ~BindSmartPtr() { if (p) p->Release(); } };
struct BindRefVec {
    int* b; int* e; int* c; int alloc[2];
    BindRefVec() { b = 0; e = 0; c = 0; }
    void DestroyRange(int* first, int* last);              // 0x73f2e0
    ~BindRefVec() { DestroyRange(b, e); BindFreeBuf(b); }
};
struct BindingBase { virtual void v0(); int f4; BindingBase() { f4 = 0; } virtual ~BindingBase() {} };
struct BindingSet : BindingBase {
    uint32_t mFlags; int f0c, f10;     // +8
    BindPodVec pv14;
    BindRefVec rv28;
    BindPodVec pv3c;
    BindPodVec pv50;
    BindPodVec elems;                      // +0x64
    BindPodVec pv78;
    int pad8c;
    int f90, f94;
    BindSmartPtr p98;
    BindingSet();
    ~BindingSet();
    virtual void v0();
};
struct IdPtrVec { int d[5]; ~IdPtrVec(); };       // 0x421190
struct RefVector { int d[5]; ~RefVector(); };     // 0x41eb80
struct ContPodVec {
    int* b; int* e; int* c; int alloc[2];
    ~ContPodVec() throw() { if (b && b[-1] != 0) operator_delete__(b); }
};
struct BindingContainer {
    ContPodVec a, b, c;
    RefVector refs;    // +0x3c
    IdPtrVec ids;      // +0x50
    ~BindingContainer();
};
struct V4 { float x, y, z, w; };
struct M4 { V4 r0, r1, r2, t; };                   // 3 basis rows + translation row
struct cSPBoundingBox_s0073_f320 { float mMin[3]; float mMax[3];
    void Transform(const void* m);                 // 0x409dd0
};
struct PartTransform64 {                           // 0x40-byte matrix helper
    char d[0x40];
    void Construct(const cSPTransform_s0073_f320& t);         // 0x40ce80 (the constructor; thiscall, ret 4)
    void Invert();                                 // 0x40efa0
};
struct QueryItem {                                 // 0x60 bytes
    char pad0[0x44];
    uint32_t mFlags;                               // +0x44, bit 0 = visited
    char pad48[0x60 - 0x48];
    int Test(int a, int b, const void* arg);       // 0x12022b0 (ret 0xc)
};
struct BoxPair {                                   // (min, max) as 4-lane vectors
    V4 mMin, mMax;
    int Overlaps(const void* arg);                 // 0x73f110 (ret 4)
};
struct __declspec(align(16)) QueryState {          // 0xf4 bytes, global singleton
    void**     mppScratch;                         // +0x00
    int        f04, f08, f0c;
    V4         mMin;                               // +0x10
    V4         mMax;                               // +0x20
    char       pad30[0x10];
    int        f40;                                // +0x40
    char       pad44[0xc0 - 0x44];
    int        fc0;
    char       pad_c4[8];
    int        fcc;
    char       pad_d0[4];
    QueryItem* mItems;                             // +0xd4
    uint32_t   mItemCount;                         // +0xd8
    char       pad_dc[4];
    int        fe0;
    char       pad_e4[4];
    int        fe8;
    int        fec;
    char       ff0;
};
struct QueryAlloc;
struct QueryAllocVT { char pad[0x18]; int (__thiscall *Query)(QueryAlloc* self, QueryState* q, const void* basis); };
struct QueryAlloc { char pad[0x20]; QueryAllocVT* vt; };
struct ExternalTable { QueryAlloc* GetAllocator(); };      // 0x7f54d0
void* __cdecl QueryStage1(void* buf, int a, int b);                       // 0x1204110
void  __cdecl QueryStage2(void* dst, void* src);                          // 0x6c1c80
QueryState* __cdecl QueryStage3(void* tmp, int a, int b);                 // 0x1204180
void  __stdcall EhVecDtor(void* p, unsigned size, int count, void* dtor);  // 0x11e0b22 (__ehvec_dtor)
extern char Elem8Dtor_s0073_f320;                                                    // 0xc2e4e0
extern QueryState* gPickQuery;                                            // 0x162eaf4
extern QueryState* gSphereQuery;                                          // 0x162eaf8
static int RunQuery(ExternalTable* table, QueryState* q, const void* basis)
{
    QueryAlloc* a = table->GetAllocator();
    return a->vt->Query(a, q, basis);
}
static QueryState* GetQuery(QueryState*& slot)
{
    if (slot == 0) {
        char scratch[32];
        char tmp[0x10];
        void* t = QueryStage1(scratch, 8, 8);
        QueryStage2(tmp, t);
        EhVecDtor(scratch, 8, 4, &Elem8Dtor_s0073_f320);
        slot = QueryStage3(tmp, 8, 8);
    }
    return slot;
}
static void InitQuery(QueryState* q, void** scratchSlot, const V4& mn, const V4& mx)
{
    q->mppScratch = scratchSlot;
    q->f04 = 0;
    q->f08 = 1;
    q->f0c = 0;
    q->fc0 = 0;
    q->fcc = 0;
    q->f40 = 0;
    q->fe0 = 0;
    q->fe8 = 0;
    q->mItemCount = 0;
    q->mMin = mn;
    q->mMax = mx;
    q->fec = 0;
    q->ff0 = 0;
}
struct cModelInstanceQ {
    char pad0[0xcc];
    ExternalTable* mExternalBoneTable;             // +0xcc
    bool PickLine(const float* origin, float len, const cSPTransform_s0073_f320* xf, bool firstHitOnly);
    bool IntersectsSphere(const cSPBoundingBox_s0073_f320* box, const cSPTransform_s0073_f320* xf, bool firstHitOnly);
};
// ---- items of slice s0073f320 end

// ---- items of slice s007403c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_f01485720;                                    // 1.0f
extern const float g_f0162e88c;     // 0x0162e88c
extern const float g_f0162e890;     // 0x0162e890
extern const float g_f0162e894;     // 0x0162e894
extern const float g_fNeg1;         // 0x013eb1bc  -1.0f
extern const float g_fMax;          // 0x0140d56c  FLT_MAX
extern const float g_fMin;          // 0x013f51ac  -FLT_MAX
extern char vtbl_GmeRefCount[];        // 0x013ef094  ??_7GmeRefCount@@6B@
extern char vtbl_cModelInstance[];     // 0x0140d638
struct Vec12 { int a, b, c; };
struct Vec12Vector {
    Vec12* mpBegin;                  // +0x0
    Vec12* mpEnd;                    // +0x4
    Vec12* mpCapacity;               // +0x8
    void push_back(const Vec12& value);
    void DoInsertValue(Vec12* pos, const Vec12& value);   // 0x7409d0
};
#define kEastlFile \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
void* operator new(unsigned int, const char*, int, int, const char*, int);   // 0x00f473a0
void* operator new(unsigned int, const char*, int, int, int, int);          // 0x00f473a0 (no matching delete)
struct Elem { uint32_t a, b; Elem(); ~Elem(); };               // 0x006c0fa0 / 0x00c2e4e0
struct ExpObj { uint32_t type; void* obj; uint32_t z0, z1, z2, z3; Elem arr[4];
    ExpObj() : type(0), obj(0), z0(0), z1(0), z2(0), z3(0) { arr[0].a = 0; arr[0].b = 1; }
};
struct Arena {
    int GetNumExportedObjects();                           // 0x011e23a0
    void GetExportedObjectByIndex(int idx, ExpObj* out);   // 0x011e28e0
};
struct ArenaOwner { char pad[0x18]; Arena* arena; };
struct RefIface { virtual void AddRef(); virtual void Release(); };
struct BoneTable : RefIface { char pad[0x48]; BoneTable(ExpObj* e, ArenaOwner* src); };   // 0x00762250, 0x4c bytes
struct PtrArr { void* begin; };
void operator delete[](void* p);                           // 0x00f47380
void operator delete(void* p, const char*, int, int, const char*, int);
struct cModelInstanceBones {
    char pad[0xcc];
    RefIface* mBones;            // +0xcc
    PtrArr* mHull;               // +0xd0
    void LoadExportedBoneTable(ArenaOwner* src);
};
struct BoneRange { uint8_t mat; int8_t count; int16_t start; uint32_t pad; };   // 8 bytes
struct Mat12 { float m[12]; };                                                  // 3x4 bone transform, 0x30 bytes
struct MatAux { uint32_t pad[2]; Mat12*** pm; };
struct IdSet { uint32_t pad[2]; uint32_t* data; uint32_t count; };              // +8 data, +0xc count
struct MatAux2 { uint32_t pad[3]; IdSet* ids; };                                // +0xc
struct Material_s0074_03c0 {                                                               // 0xc4 bytes
    uint32_t pad0[2];
    union { MatAux* aux; MatAux2* aux2; };                                      // +8
    uint32_t pad[0xc4 / 4 - 3];
};
void MaterialPrepare(Material_s0074_03c0* m, int z);                          // 0x0073a900 (cdecl)
void CopyMats(Mat12* first, Mat12* last, Mat12* out);              // 0x0073fe20 (cdecl)
void CopyWords(void* dst, void* src, unsigned bytes);              // 0x011e0744 (cdecl)
template <class T> inline const T& Min(const T& a, const T& b) { return (a < b) ? a : b; }
template <class T> inline const T& Max(const T& a, const T& b) { return (b < a) ? a : b; }
struct cModelResourceInfo {
    uint32_t pad0[3];
    int      mClamp;                  // +0x0c
    Mat12*   mClampTable;             // +0x10
    BoneRange* mRangesBegin;          // +0x14
    BoneRange* mRangesEnd;            // +0x18
    uint32_t pad1[3];
    Material_s0074_03c0* mMats;                  // +0x28
    uint32_t pad2[0x64 / 4 - 0x2c / 4];
    void* mAnimBegin;                 // +0x64
    void* mAnimEnd;                   // +0x68
    int GetBoneTransforms(Mat12* out);      // 0x740550
    int GetBoneIDs(uint32_t* dst);          // 0x740740
};
struct P8 { uint32_t a, b; };
void* H_uninit_copy12(void* first, void* last, void* dest);              // 0x00a11310 (cdecl)
void* H_uninit_copy8(void* first, void* last, void* dest);               // 0x0099efa0 (cdecl)
void* H_copy8(void* first, void* last, void* dest);                      // 0x004554f0 (cdecl)
void  H_move8(void* out, void* a, void* b, void* c, void* d);            // 0x0076ffd0 (cdecl, 5 args)
void  H_copy_backward8(void* first, void* last, void* destEnd);          // 0x0073fe50 (cdecl)
void  H_fill8(void* first, void* last, const P8* value);                 // 0x00a52da0 (cdecl)
void  H_fill_n8(void* dest, uint32_t n, const P8* value);                // 0x006ac440 (cdecl)
void  H_copy8b(void* first, void* last, void* dest);                     // 0x00ac4440 (cdecl)
struct Vec8Vector {
    P8* mpBegin; P8* mpEnd; P8* mpCapacity;
    void DoInsertValues(P8* pos, uint32_t n, const P8& value);               // 0x740b00
    void DoInsertRange(P8* pos, P8* first, P8* last, int tag);               // 0x740cc0
};
struct Binding : RefIface {
    uint32_t pad[3];
    uint32_t mKey;           // +0x10
    RefIface* mTarget;       // +0x14
    uint32_t pad2[2];
};
struct Owner { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
               virtual bool Validate(uint32_t key, RefIface** target); };   // vtable slot 8 (+0x20)
struct ResRef {
    uint32_t pad[10];
    void* v28Begin; void* v28End;            // +0x28 / +0x2c
    uint32_t pad2[8];
    void* v50Begin; void* v50End;            // +0x50 / +0x54
};
struct T20 : Binding { T20(void* mi, uint32_t a2, void* v1, void* v2); };   // 0x0073aa70, 0x20 bytes
struct T9c : RefIface { uint32_t pad[0x98 / 4]; T9c(void* mi, uint32_t a2, void* v1); };               // 0x0073cb40
struct T38 : RefIface { uint32_t pad[0x34 / 4]; T38(void* mi, uint32_t a2); };                         // 0x0073cac0
bool __fastcall ValidateB(T9c* p);       // 0x0073ffb0
bool __fastcall ValidateA(T38* p);       // 0x0073fe80
template <class T> struct Hold {
    T* p;
    explicit Hold(T* q) : p(q) { if (p) p->AddRef(); }
    ~Hold() { if (p) p->Release(); }
};
struct cModelInstanceB {
    uint32_t pad[0xec / 4];
    Owner* mOwner;           // +0xec
    ResRef* mRes;            // +0xf0
    bool CreateBinding(uint32_t a2, RefIface** out);       // 0x7407d0
};
struct Matrix3 { float m[9]; Matrix3(const Matrix3& src); };   // 0x0041cb40
extern const Matrix3 g_Matrix0162e9cc;
struct Vec3 { float x, y, z; Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };
struct Xf {
    uint16_t a, b; float f0, f1, f2, w; Matrix3 m;
    Xf() : m(g_Matrix0162e9cc) { f0 = g_f0162e88c; f1 = g_f0162e890; f2 = g_f0162e894; a = 0; b = 0; w = g_f01485720; }
};
struct Cell { uint32_t nameA, nameB; uint32_t mpBegin, mpEnd, mpCap; Cell() : mpBegin(0), mpEnd(0), mpCap(0) {} };
struct BindingContainer_s0074_03c0 {
    uint32_t w8, wc, w10;
    Cell cells[4];                       // 0x14, 0x28, 0x3c, 0x50
    uint32_t w64, w68;
    uint8_t  flag6c; uint8_t pad6d[3];
    BindingContainer_s0074_03c0() : w8(0), wc(0), w10(0) {}
    ~BindingContainer_s0074_03c0();                 // 0x007402e0
};
struct RCBase {                        // GmeRefCount: vptr kept as a plain field (no vtable is built here)
    void* vt;
    int mRefCount;
    RCBase() : mRefCount(0) { vt = vtbl_GmeRefCount; }
    ~RCBase() { vt = vtbl_GmeRefCount; }
};
template <class T> struct ARC {
    T* p;
    ARC() : p(0) {}
    ~ARC() { if (p) p->Release(); }
};
struct RCObj_s0074_03c0 { virtual ~RCObj_s0074_03c0() {} int rc; };
struct IPtr {
    RCObj_s0074_03c0* p;
    IPtr() : p(0) {}
    ~IPtr() { RCObj_s0074_03c0* q = p; if (q) { int t = q->rc; q->rc = t - 1; if (t - 1 == 0) { q->rc = 1; delete q; } } }
};
struct HullData { void* begin; };
struct BBox { Vec3 mn, mx; BBox() : mn(g_fNeg1, g_fNeg1, g_fNeg1), mx(g_f01485720, g_f01485720, g_f01485720) {} };
struct cModelInstance_s0074_03c0 : RCBase {
    BindingContainer_s0074_03c0 bc;                 // +0x08
    Xf       mTransform;                 // +0x70
    BBox     mBox;                       // +0xa8
    float    mRadius;                    // +0xc0
    ARC<RefIface> mResource;             // +0xc4
    uint16_t mFlags;                     // +0xc8
    ARC<RefIface> mBones;                // +0xcc
    HullData* mHull;                     // +0xd0
    Vec3     mHullMin, mHullMax;         // +0xd4 / +0xe0
    ARC<RefIface> mDynamicDraw;          // +0xec
    IPtr     mRes;                       // +0xf0
    uint32_t padf4;
    int      mF8, mFC;                   // +0xf8 / +0xfc

    cModelInstance_s0074_03c0();                    // 0x740e90
    ~cModelInstance_s0074_03c0();                   // 0x741040
    void* GetRegionMaterialInfo(int region);    // 0x741150
};
struct Matrix3Place { float m[9]; void Assign(const Matrix3& src); };   // 0x0041cb40
struct MInit : RCBase {
    uint32_t w[0x3e];
    MInit();                            // 0x740e90
};
struct KeyPair { int key; void* value; };
KeyPair* RegionLowerBound(KeyPair* first, KeyPair* last, const int* key, unsigned flag);   // 0x0042dd00 (cdecl)
struct cModelInstanceR {
    uint32_t pad0[0x30 / 4];
    void* v30Begin; void* v30End;        // +0x30 / +0x34
    uint32_t pad1[(0x44 - 0x38) / 4];
    void* v44Begin; void* v44End;        // +0x44 / +0x48
    uint32_t pad2[(0x58 - 0x4c) / 4];
    KeyPair* mapBegin; KeyPair* mapEnd;  // +0x58 / +0x5c
    uint32_t pad3[(0x6c - 0x60) / 4];
    uint8_t  flag;                       // +0x6c
    void* GetRegionMaterialInfo(int region);
};
// ---- items of slice s007403c0 end

// ---- items of slice s00741210 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EASTL_memmove(void* dst, const void* src, unsigned int n);   // 0x011e0744
extern wchar_t gEmptyString16[2];                          // 0x01667bac
#pragma intrinsic(sqrt)
struct ResBase {
    virtual void v0();
    virtual void v1();
};
struct cMI_Construct {
    char    pad0[8];
    void*   mBegin8;                  // +0x8
    void*   mEndc;                    // +0xc
    char    pad10[0xc4 - 0x10];
    ResBase* mResource;               // +0xc4

    void AddGeometryFromArena(ResBase* p);          // 0x741210
    bool ConstructFromArenaResource(ResBase* p);    // 0x741a40
    void Sub3c0(ResBase* p);                        // 0x7403c0
};
struct RefCounted {
    virtual void v0();
    virtual void v1();
    volatile int mnRefCount;         // +0x4
};
struct RefPair8 {
    int         value;               // +0x0
    RefCounted* p;                   // +0x4
    RefPair8& operator=(const RefPair8& o);               // 0x0042f8b0 (thiscall, ret 4)
};
RefPair8* __cdecl CopyPairs(RefPair8* first, RefPair8* last, RefPair8* dst);      // 0x0073c410
RefPair8* __cdecl ReleasePairs(RefPair8* first, RefPair8* last, RefPair8* dst);   // 0x0073c450
RefPair8* __cdecl copy_backward_ref(RefPair8* first, RefPair8* last, RefPair8* result);   // 0x0073f440
void* __cdecl EASTL_allocator_allocate(unsigned n, const char* name, int flags, int debugFlags, const char* file, int line);   // 0x00f473a0
struct Vec8 {
    RefPair8* mpBegin;               // +0x0
    RefPair8* mpEnd;                 // +0x4
    RefPair8* mpCapacity;            // +0x8
    RefPair8* insert(RefPair8* pos, const RefPair8* v);
    __declspec(noinline) void DoInsertValue(RefPair8* pos, const RefPair8* v);   // 0x7418f0
};
struct UIntVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    void DoInsertValue(uint32_t* pos, const uint32_t& v);   // 0x004558a0
    void erase(uint32_t* first, uint32_t* last)
    {
        EASTL_memmove(first, last, (unsigned)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const uint32_t& v)
    {
        if (mpEnd < mpCapacity) {
            uint32_t* p = mpEnd++;
            if (p)
                *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};
struct ShaderOwner {
    char pad0[8];
    uint32_t mDirty;                                // +0x8
    const uint32_t* D3D9GetShaderData(int id);      // 0x011edcf0
};
struct LoadedModel {
    char pad0[4];
    ShaderOwner* mOwner;                            // +0x4
};
struct cLoadQueueS {
    char pad0[0x30];
    LoadedModel** mpBegin;                          // +0x30
    LoadedModel** mpEnd;                            // +0x34
    void StallUntilLoaded(UIntVec* out);
};
__declspec(noinline) Elem::Elem() { a = 0; b = 1; }
__declspec(noinline) Elem::~Elem() {}
struct ResKey { unsigned instanceID, typeID, groupID; };
struct SrcModel {
    char pad0[8];
    ResKey mKey;                                           // +0x08 resource key
    char pad14[4];
    Arena* arena;                                          // +0x18
};
struct EString16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    unsigned mAllocator;
    EString16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
    ~EString16() {
        if ((int)(((unsigned)mpCapacity - (unsigned)mpBegin) & 0xfffffffe) > 2 && mpBegin)
            operator delete[](mpBegin);
    }
};
#define V4_s0074_1210(a) virtual void a##0(); virtual void a##1(); virtual void a##2(); virtual void a##3();
struct ResManager {
    V4_s0074_1210(p0) V4_s0074_1210(p1) V4_s0074_1210(p2) V4_s0074_1210(p3) V4_s0074_1210(p4) V4_s0074_1210(p5) V4_s0074_1210(p6)
virtual void q28();
virtual void q29();
virtual void q30();
    virtual void KeyToName(const ResKey* key, EString16* out);   // +0x7c
};
ResManager* __cdecl GetManager();                          // 0x0067dcd0
struct MatInfo;
struct MatRes;
struct MaterialManager {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9();
    virtual MatInfo* Wrap(MatRes* r);                      // +0x28
virtual void m11();
virtual void m12();
virtual void m13();
virtual void m14();
virtual void m15();
    virtual MatRes* Create(unsigned id, SrcModel* src);    // +0x40
};
MaterialManager* __cdecl GetMaterialManager();             // 0x0067dd70
struct PtrVec {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    void DoInsertValue(void** pos, void* const& v);        // 0x006ec4a0
    void push_back(void* const& v)
    {
        void** p = mpEnd;
        if (p < mpCapacity) {
            mpEnd = p + 1;
            if (p)
                *p = v;
        } else {
            DoInsertValue(p, v);
        }
    }
};
struct Vec3_s0074_1210 { float x, y, z; Vec3_s0074_1210() {} Vec3_s0074_1210(float a, float b, float c) : x(a), y(b), z(c) {} };
struct BBox3 { Vec3_s0074_1210 mMin, mMax; BBox3() {} BBox3(const Vec3_s0074_1210& a, const Vec3_s0074_1210& b) : mMin(a), mMax(b) {} };
struct ASrcBox {
    __m128 mn, mx;
    __m128 GetMin() const { return mn; }
    __m128 GetMax() const { return mx; }
};
template <class T> inline const T& MaxRef(const T& a, const T& b) { return (b < a) ? a : b; }
struct cMI_Geo {
    char pad0[8];
    PtrVec mMeshes;                 // +0x08
    char pad14[0x30 - 0x14];
    PtrVec mMats;                   // +0x30
    char pad3c[0xa8 - 0x3c];
    BBox3 mBox;                     // +0xa8
    float mRadius;                  // +0xc0
    void AddGeometryFromArena(SrcModel* src);
};
// ---- items of slice s00741210 end

// ---- items of slice s00742b30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kFltMax;                                  // 0x0140d56c
extern const float kNegFltMax;                               // 0x013f51ac
#define AT(T, off) (*(T*)((char*)this + (off)))
struct RC_s0074_2b30 {                       // virtual add-ref / release object
    virtual void AddRef();
    virtual void Release();
};
template <class T> static inline void SetRC(T*& dst, T* v)
{
    T* old = dst;
    if (v != old) {
        if (v) v->AddRef();
        dst = v;
        if (old) old->Release();
    }
}
struct VecInt {                   // eastl vector<int> range insert
    int* mpBegin; int* mpEnd; int* mpCap;
    void insert_range(int* pos, const int* first, const int* last, void* src);   // 0x00715ec0
};
struct VecInt2 {                  // second vector flavour at +0x1c
    int* mpBegin; int* mpEnd; int* mpCap;
    void insert_range(int* pos, const int* first, const int* last, void* src);   // 0x00740cc0
};
struct RefVec { void Assign(const void* src); };                                  // 0x0041ebe0
struct Obj138 : RC_s0074_2b30 {
    virtual RC_s0074_2b30* Get();            // slot 2
};
struct ObjEC : RC_s0074_2b30 {
    virtual void s2();
    virtual void s3();
    virtual void Apply(void* p);  // slot 4
};
struct E8 { uint8_t a, b; uint16_t c; uint8_t d, e; uint16_t f; };
struct VecE8 {
    E8* mpBegin; E8* mpEnd; E8* mpCap;
    void Grow(E8* pos, const E8& v);                    // 0x006ec390
    void push(const E8& v) {
        if (mpEnd < mpCap) {
            E8* p = mpEnd;
            mpEnd = p + 1;
            if (p) *p = v;
        } else {
            Grow(mpEnd, v);
        }
    }
};
struct RefCounted_s0074_2b30 {
    virtual void* Del(unsigned flags);       // slot 0: scalar deleting destructor
    volatile long mnRefCount;     // +4
    void Release() {
        long r = _InterlockedDecrement(&mnRefCount);
        if (r == 0) {
            _InterlockedExchange(&mnRefCount, 1);
            Del(1);
        }
    }
};
struct AR {                      // intrusive smart pointer to RefCounted
    RefCounted_s0074_2b30* p;
    AR() : p(0) {}
    AR(const AR& o) : p(o.p) { if (p) _InterlockedIncrement(&p->mnRefCount); }
    ~AR() { if (p) p->Release(); }
};
struct RefPair8_s0074_2b30 {
    int value;
    AR second;
    RefPair8_s0074_2b30(int v, const AR& s) : value(v), second(s) {}
};
extern RefPair8_s0074_2b30* __cdecl LowerBoundB41ea0(RefPair8_s0074_2b30* first, RefPair8_s0074_2b30* last, const RefPair8_s0074_2b30* v, uint8_t flag);  // 0x00b41ea0
extern RefPair8_s0074_2b30* __cdecl LowerBound42dd00(RefPair8_s0074_2b30* first, RefPair8_s0074_2b30* last, const int* key, uint8_t flag);     // 0x0042dd00
struct Map8 {
    RefPair8_s0074_2b30* mpBegin; RefPair8_s0074_2b30* mpEnd; RefPair8_s0074_2b30* mpCap; uint32_t pad[2];
    uint8_t flag;                                       // +0x14
    RefPair8_s0074_2b30* insert(RefPair8_s0074_2b30* pos, const RefPair8_s0074_2b30* v); // 0x00741aa0
    RefPair8_s0074_2b30* MapInsert(RefPair8_s0074_2b30* pos, RefPair8_s0074_2b30* value);// 0x00742ca0
    AR* GetOrAdd(const int* key);              // 0x00742f60
};
struct Src : RC_s0074_2b30 {                 // source model resource (retail offsets)
    uint32_t pad04[5];
    int* v18; int* v1c;           // +0x18
    char pad20[0xb8 - 0x20];
    int* vb8; int* vbc;
    char padc0[0xe0 - 0xc0];
    int* ve0; int* ve4;
    char pade8[0xf4 - 0xe8];
    char rv_f4[0x11c - 0xf4];
    int i11c, i120, i124, i128, i12c, i130;
    float f134;
    Obj138* o138;
    void* p13c;
};
struct cMI {
    void AddAnimationsFromArena(RC_s0074_2b30* arena, int a, uint16_t* b, uint16_t* c);   // 0x00741b10
    void Fn7403c0(void* p);                                                     // 0x007403c0
    void Sub2b30(Src* src);
    void SetAnimationResource(RC_s0074_2b30* p);
    void ConstructFromGameModelResource(char* src);
};
struct FixedVec64 {
    int* mpBegin; int* mpEnd; int* mpCap;
    uint32_t mFlags; void* mpPool; uint32_t mReserved;
    int mBuffer[64];
    FixedVec64(uint32_t n, int value);                           // 0x00422740
    ~FixedVec64() throw() {
        if (mpBegin && mpBegin != mpPool)
            EASTL_allocator_deallocate(mpBegin);
    }
    void DoPushBackAux(int* pos, const int& v);                  // 0x004281d0
    void push_back(const int& v) {
        if (mpEnd < mpCap)
            ::new (mpEnd++) int(v);
        else
            DoPushBackAux(mpEnd, v);
    }
};
struct BoneInfo { uint32_t* flags; uint32_t pad[4]; int count; };      // flags +0, count +0x14
struct MatEntry { uint32_t pad[3]; BoneInfo* info; };                    // info +0xc
struct cMI2 {
    int GetBoneParents(int* out);                                        // 0x00743030
    void Sub3150(int tag, RefCounted_s0074_2b30* mat);                              // 0x00743150
};
struct ES {                                   // rw::graphics::EmbeddedState view
    uint32_t pad[2]; uint32_t flags;
    int* D3D9GetShaderData(int id);           // 0x011edcf0
};
struct Item2 { uint32_t pad; ES* es; };       // +4
struct RefVecMat { void resize(int n); };     // 0x0041ee90
static __forceinline void AssignAR(AR& dst, RefCounted_s0074_2b30* v)
{
    RefCounted_s0074_2b30* old = dst.p;
    if (v != old) {
        if (v) _InterlockedIncrement(&v->mnRefCount);
        dst.p = v;
        if (old) old->Release();
    }
}
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);   // 0x00f473a0
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
struct TObj {                              // GmeRefCount: virtual ref-counted base
    virtual void* Del(unsigned flags);
    volatile long mnRefCount;
    TObj() { _InterlockedExchange(&mnRefCount, 0); }
};
struct Ref {
    TObj* p;
    Ref(TObj* o) : p(o) { if (p) _InterlockedIncrement(&p->mnRefCount); }
    Ref(const Ref& o) : p(o.p) { if (p) _InterlockedIncrement(&p->mnRefCount); }
    ~Ref() {
        if (p) {
            long r = _InterlockedDecrement(&p->mnRefCount);
            if (r == 0) {
                _InterlockedExchange(&p->mnRefCount, 1);
                p->Del(1);
            }
        }
    }
};
struct RefVecL {
    Ref* mpBegin; Ref* mpEnd; Ref* mpCap; uint32_t alloc;
    RefVecL() : mpBegin(0), mpEnd(0), mpCap(0) {}
    ~RefVecL();                                              // 0x0041eb80
    void DoInsertValue(Ref* pos, const Ref& v);              // 0x00424430
    void push_back(const Ref& v) {
        if (mpEnd < mpCap)
            ::new (mpEnd++) Ref(v);
        else
            DoInsertValue(mpEnd, v);
    }
};
struct MeshVec_s0074_2b30 {                                             // local vector of mesh refs
    Ref* mpBegin; Ref* mpEnd; Ref* mpCap; uint32_t alloc;
    MeshVec_s0074_2b30() : mpBegin(0), mpEnd(0), mpCap(0) {}
    void DestroyRange(Ref* first, Ref* last);                // 0x004243e0
    ~MeshVec_s0074_2b30() {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
    }
};
struct VecA {
    int* a; int* b; int* c;
    VecA() : a(0), b(0), c(0) {}
    VecA& operator=(const VecA& x);                         // 0x00735dd0
};
struct VecB {
    int* a; int* b; int* c;
    VecB() : a(0), b(0), c(0) {}
    VecB& operator=(const VecB& x);                         // 0x00738d10
};
struct VecC {
    int* a; int* b; int* c;
    VecC() : a(0), b(0), c(0) {}
    VecC& operator=(const VecC& x);                         // 0x00715120
};
struct VecD {
    int* a; int* b; int* c;
    VecD() : a(0), b(0), c(0) {}
    VecD& operator=(const VecD& x);                         // 0x00735260
};
struct Obj58 : TObj {
    VecA v8; uint32_t pad14[2];
    VecB v1c; uint32_t pad28[2];
    VecC v30; uint32_t pad3c[2];
    VecD v44; uint32_t pad50[2];
    virtual void* Del(unsigned flags);
};
struct MeshSrc {                                             // a mesh record (retail offsets)
    uint32_t pad0[2];
    VecA v8; uint32_t pad14[2];
    VecB v1c; uint32_t pad28[2];
    VecC v30; uint32_t pad3c[2];
    VecD v44;
};
struct Xf_s0074_2b30 {
    uint16_t a, b; float f0, f1, f2, w; Matrix3 m;
    Xf_s0074_2b30() : a(0), b(0), f0(g_f0162e88c), f1(g_f0162e890), f2(g_f0162e894), w(g_f01485720), m(g_Matrix0162e9cc) {}
};
struct Elem_s0074_2b30 {
    uint32_t a, b;
    Elem_s0074_2b30();                                                 // 0x006c0fa0
    ~Elem_s0074_2b30();                                                // 0x00c2e4e0
};
struct BoneProv {
    int GetBoneTransforms(void* buf);                       // 0x00740550
};
bool __cdecl SkinMesh(void* bones, MeshSrc* mesh, Obj58* obj);   // 0x0073a110
void __cdecl Fn734d00(Xf_s0074_2b30* a2, Obj58* obj);                       // 0x00734d00
struct cMI3 {
    bool GetMeshes(MeshVec_s0074_2b30* out);                            // 0x0073eb90
    bool Sub3270(Xf_s0074_2b30* a2, RefVecL* out);
    bool Sub34b0(float* out);
};
struct V3_s0074_2b30 {
    float x, y, z;
    V3_s0074_2b30(float a) : x(a), y(a), z(a) {}
    V3_s0074_2b30(float a, float b, float c) : x(a), y(b), z(c) {}
};
struct Obj90 { uint32_t pad[0x24]; int w90; int w94; };      // +0x90 / +0x94
struct KDZ { uint32_t z[6]; KDZ() { z[0] = 0; z[1] = 0; z[2] = 0; z[3] = 0; z[4] = 0; z[5] = 0; } };
struct KD : KDZ { Elem_s0074_2b30 arr[4]; };
struct DynArr { uint32_t a, b, c; uint32_t pad[2]; DynArr() : a(0), b(0), c(0) {} };
struct KDObj : RC_s0074_2b30 {
    uint32_t pad[18];
    KDObj(KD* kd, int z);                                   // 0x00762250
};
int __cdecl MakeKDTree(RefVecL* meshes, float* extent, DynArr* arr, int leaf, KD* kd);   // 0x0072c270
void __cdecl AccumBounds(TObj* mesh, V3_s0074_2b30* bounds);            // 0x00732a30
struct ArrHolder {
    void SetArray(DynArr* a);                               // 0x00740370
};
static inline const float& MaxRef_s0074_2b30(const float& a, const float& b) { return (a < b) ? b : a; }
// ---- items of slice s00742b30 end

// ---- items of slice s0073bf20 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RefObjV {
    void** vftable;                 // +0
    int mnRefCount;                 // +4
};
struct AbilityP0 { virtual void p0(); };
struct AbilityGmeRC { virtual void g0(); int rc; AbilityGmeRC() : rc(0) {} };
struct AbilityBase : AbilityP0, AbilityGmeRC {
    RefObjV* m; int x;
    AbilityBase(RefObjV* a, int b) : m(a) { if (a) ++a->mnRefCount; x = b; }
virtual void p0();
virtual void g0();
};
struct AbilityD : AbilityBase {
    int pad[(0x98 - 0x14) / 4];
    int y;
    AbilityD(RefObjV* a, int b, int c);
virtual void p0();
virtual void g0();
};
// ---- items of slice s0073bf20 end

// @ 0x0073aa70
AbilityB::AbilityB(AbHeld* h, int v, int a, int b)
: AbilityA(h, v), mB18(a), mB1c(b)
{
}

// @ 0x0073abb0
namespace SP {
int cModelInstance_s0073_a110::GetAnimationMoveToTimes(int animID, int* dst, char bEnd)
{
    if (!IsValidGroup(animID))
        return 0;
    cAnimGroupInfo_s0073_a110* e = &mAnimGroups[animID];
    int start = e->mAnimOffset;
    int n = e->mAnimCount;
    if (bEnd) {
        start += e->mAnimFirstDeform;
        n -= e->mAnimFirstDeform;
    }
    if (dst != 0 && n > 0) {
        const char* p = (const char*)mControllers + start * 8;
        int i = 0;
        do {
            dst[i] = *(const int*)p;
            ++i;
            p += 8;
        } while (i < n);
    }
    return n;
}
}  // namespace SP

// @ 0x0073ac20
namespace SP {
bool cModelInstance_s0073_a110::SetActive(int key, int groupIdx, bool animating, float t, bool loop)
{
    if (!IsValidGroup(groupIdx))
        return false;
    cAnimGroupInfo_s0073_a110* g = &mAnimGroups[groupIdx];
    const int start = g->mAnimOffset;
    const int end = start + g->mAnimCount;
    const int bidx = g->mBindingIdx;
    int bend;
    if (g->mBindingIdx != (char)-1)
        bend = bidx + 1;
    else
        bend = bidx;
    bool result = false;
    for (int i = start; i < end; ++i) {
        if (((cCtrlEntry*)mControllers)[i].mKey == key) {
        cAnimDef* target = ((cCtrlEntry*)mControllers)[i].mDef;
        const int nA = (int)(mBindAEnd - mBindABegin);
        for (int k = 0; k < nA; ++k) {
            cBinding_s0073_a110* b = &mBindABegin[k];
            b->mLoop = loop;
            if (b->mInfo->m10->mId == target->mId) {
                ApplyBinding(this, b, target, animating, t, loop);
                result = true;
            }
        }
        for (int j = bidx; j < bend; ++j) {
            cBinding_s0073_a110* b = (cBinding_s0073_a110*)&mMaterials[j];
            b->mLoop = loop;
            if (b->mInfo->m0c->mId == target->mId) {
                ApplyBinding(this, b, target, animating, t, loop);
                result = true;
            }
        }
        const int nC = (int)(mBindCEnd - mBindCBegin);
        for (int k = 0; k < nC; ++k) {
            cBinding_s0073_a110* b = &mBindCBegin[k];
            b->mLoop = loop;
            if (b->mInfo->m18 == target->mId) {
                ApplyBinding(this, b, target, animating, t, loop);
                result = true;
            }
        }
        }
    }
    return result;
}
}  // namespace SP

// @ 0x0073af20
namespace SP {
bool cModelInstance_s0073_a110::AdvanceBinding(cBinding_s0073_a110* b, float dt)
{
    cBlender* bl = b->mBlender;
    if (bl != 0 && b->mActive) {
        if (mFlags8 & 0x20) {
            if (bl->AnyAnimating()) {
                cBlender* c = b->mBlender;
                ((void(__thiscall*)(cBlender*, float))c->mVptr4[0])(c, dt);
                return true;
            }
        } else {
            float len = bl->mDef->mLength;
            if (b->mLoop && len <= bl->mTime + dt) {
                dt = len - bl->mTime;
                b->mActive = false;
            }
            ((void(__thiscall*)(cBlender*, float))bl->mVptr4[0])(bl, dt);
            return true;
        }
    }
    return false;
}
}  // namespace SP

// @ 0x0073afb0
namespace SP {
void cModelInstance_s0073_afb0::Animate(float dt)
{
    bool any = false;
    int n = (int)(mBindAEnd - mBindABegin);
    for (int i = 0; i < n; i++) {
        if (UpdateBinding(mBindABegin + i, dt))
            any = true;
    }
    n = (int)(mMaterialsEnd - mMaterials);
    for (int i = 0; i < n; i++)
        StepBinding(this, (cBinding_s0073_afb0*)(mMaterials + i), dt, any);
    n = (int)(mBindCEnd - mBindCBegin);
    for (int i = 0; i < n; i++)
        StepBinding(this, mBindCBegin + i, dt, any);
    if (any)
        mCounter += 1;
}
}  // namespace SP

// @ 0x0073b190
namespace SP {
void cModelInstance_s0073_afb0::MoveToTime(int key, int grp, float t)
{
    if (grp >= 0 && grp < (int)(mGroupEnd - mGroupBegin) && mBlendBegin != mBlendEnd
        && !(fabsf(t) > 10000.0f) && IsFinite(t)) {
        cAnimGroupInfo_s0073_afb0* g = &mGroupBegin[grp];
        int last = g->mAnimCount + g->mAnimOffset;
        int first = g->mAnimOffset;
        int b0 = g->mBindingIdx;
        int b1;
        if (g->mBindingIdx != -1)
            b1 = b0 + 1;
        else
            b1 = b0;
        if (mFlags8 & 0x20) {
            if (key == 0) {
                int n = (int)(mBlendEnd - mBlendBegin);
                for (int i = 0; i < n; i++)
                    mBlendBegin[i]->SetAllTime(t);
            } else {
                for (int i = first; i < last; i++) {
                    if (mEntryBegin[i].mKey == key) {
                        cAnimDef* d = mEntryBegin[i].mDef;
                        int n = (int)(mBindAEnd - mBindABegin);
                        for (int j = 0; j < n; j++) {
                            cBinding_s0073_afb0* e = mBindABegin + j;
                            if (e->mInfo->m10->mId == d->mId)
                                e->mBlender->SetAnimTime(d, t);
                        }
                        for (int m = b0; m < b1; m++) {
                            cMaterial_s0073_afb0* mat = mMaterials + m;
                            if (mat->mInfo->m0c->mId == d->mId)
                                mat->mBlender->SetAnimTime(d, t);
                        }
                        n = (int)(mBindCEnd - mBindCBegin);
                        for (int j = 0; j < n; j++) {
                            cBinding_s0073_afb0* e = mBindCBegin + j;
                            if (e->mInfo->m18 == d->mId)
                                e->mBlender->SetAnimTime(d, t);
                        }
                    }
                }
            }
        } else {
            for (int i = first; i < last; i++) {
                if (mEntryBegin[i].mKey == key) {
                    cAnimDef* d = mEntryBegin[i].mDef;
                    int n = (int)(mBindAEnd - mBindABegin);
                    for (int j = 0; j < n; j++) {
                        cBinding_s0073_afb0* e = mBindABegin + j;
                        if (e->mInfo->m10->mId == d->mId) {
                            cBlender_s0073_afb0* b = e->mBlender;
                            if (d != b->mDef)
                                b->SetAnim(d, 0.0f);
                            b->SetTime(t);
                            e->mActive = false;
                        }
                    }
                    for (int m = b0; m < b1; m++) {
                        cMaterial_s0073_afb0* mat = mMaterials + m;
                        if (mat->mInfo->m0c->mId == d->mId) {
                            cBlender_s0073_afb0* b = mat->mBlender;
                            if (d != b->mDef)
                                b->SetAnim(d, 0.0f);
                            b->SetTime(t);
                            mat->mActive = false;
                        }
                    }
                    n = (int)(mBindCEnd - mBindCBegin);
                    for (int j = 0; j < n; j++) {
                        cBinding_s0073_afb0* e = mBindCBegin + j;
                        if (e->mInfo->m18 == d->mId) {
                            cBlender_s0073_afb0* b = e->mBlender;
                            if (d != b->mDef)
                                b->SetAnim(d, 0.0f);
                            b->SetTime(t);
                            e->mActive = false;
                        }
                    }
                }
            }
        }
        mCounter += 1;
    }
}
}  // namespace SP

// @ 0x0073b530
namespace SP {
void cModelInstance_s0073_afb0::SetWeight(int key, int grp, float w)
{
    if (grp >= 0 && grp < (int)(mGroupEnd - mGroupBegin) && mEntryBegin != mEntryEnd && (mFlags8 & 0x20)) {
        cAnimGroupInfo_s0073_afb0* g = &mGroupBegin[grp];
        int last = g->mAnimCount + g->mAnimOffset;
        int first = g->mAnimOffset;
        int b0 = g->mBindingIdx;
        int b1 = b0;
        if (g->mBindingIdx != -1)
            b1 = b0 + 1;
        for (int i = first; i < last; i++) {
            if (mEntryBegin[i].mKey == key) {
                cAnimDef* d = mEntryBegin[i].mDef;
                int n = (int)(mBindAEnd - mBindABegin);
                for (int j = 0; j < n; j++) {
                    cBinding_s0073_afb0* e = mBindABegin + j;
                    if (e->mInfo->m10->mId == d->mId)
                        e->mBlender->SetWeight(d, w);
                }
                for (int m = b0; m < b1; m++) {
                    cMaterial_s0073_afb0* mat = mMaterials + m;
                    if (mat->mInfo->m0c->mId == d->mId)
                        mat->mBlender->SetWeight(d, w);
                }
                n = (int)(mBindCEnd - mBindCBegin);
                for (int j = 0; j < n; j++) {
                    cBinding_s0073_afb0* e = mBindCBegin + j;
                    if (e->mInfo->m18 == d->mId)
                        e->mBlender->SetWeight(d, w);
                }
            }
        }
        mCounter += 1;
    }
}
}  // namespace SP

// @ 0x0073b6d0
namespace SP {
bool cModelInstance_s0073_afb0::GetAnimationRange(int key, int grp, float* pMin, float* pMax)
{
    if (grp >= 0 && grp < (int)(mGroupEnd - mGroupBegin)) {
        cAnimGroupInfo_s0073_afb0* g = mGroupBegin + grp;
        int first = g->mAnimOffset;
        int last = g->mAnimCount + first;
        float mx = 0.0f;
        for (int i = first; i < last; i++) {
            if (mEntryBegin[i].mKey == key && mx < mEntryBegin[i].mDef->mLength)
                mx = mEntryBegin[i].mDef->mLength;
        }
        *pMin = 0.0f;
        *pMax = mx;
        if (mx > 0.0f)
            return true;
        return false;
    }
    return false;
}
}  // namespace SP

// @ 0x0073b7e0
namespace SP {
int cModelInstance_s0073_afb0::GetNumBones()
{
    if (mGroupBegin == mGroupEnd)
        return 0;
    return (int)mGroupEnd[-1].mBoneCount + (int)mGroupEnd[-1].mBoneOffset;
}
}  // namespace SP

// @ 0x0073b800
namespace SP {
void cModelInstance_s0073_afb0::SetBoneTable(int a, void* b)
{
    cAnimGroupInfo_s0073_afb0* p = mGroupBegin;
    if (p != mGroupEnd && (int)p->mBoneCount < a)
        mFieldC = (int)p->mBoneCount;
    else
        mFieldC = a;
    mField10 = b;
    mCounter += 1;
}
}  // namespace SP

// @ 0x0073b840
namespace SP {
void cModelInstance_s0073_afb0::SetBoneCallback(int boneIndex, void* a2, void* a3, void* a4)
{
    if (boneIndex == -1) {
        if (mGroupBegin == mGroupEnd)
            return;
        cAnimGroupInfo_s0073_afb0* p = mGroupBegin;
        do {
            char idx = p->mBindingIdx;
            if (idx >= 0) {
                cMaterial_s0073_afb0* m = &mMaterials[idx];
                m->f_b8 = a3;
                m->f_c0 = a4;
                m->f_bc = a2;
            }
            p = (cAnimGroupInfo_s0073_afb0*)((char*)p + 8);
        } while (p != mGroupEnd);
        return;
    }
    if (boneIndex < 0)
        return;
    if (boneIndex >= (int)(mGroupEnd - mGroupBegin))
        return;
    char idx = mGroupBegin[boneIndex].mBindingIdx;
    if (idx < 0)
        return;
    cMaterial_s0073_afb0* m = &mMaterials[idx];
    m->f_b8 = a3;
    m->f_c0 = a4;
    m->f_bc = a2;
}
}  // namespace SP

// @ 0x0073b8e0
namespace SP {
void cModelInstance_s0073_afb0::SetDynamicDraw(void* pv, bool flag)
{
    DynDrawObj* p = (DynDrawObj*)pv;
    mFlags = mFlags & 0xfffb;
    if (p != 0) {
        if (flag)
            mFlags |= 4;
        DynDrawObj* dd = (DynDrawObj*)((void*(__thiscall*)(DynDrawObj*))p->vftable[2])(p);
        DynDrawObj* old = (DynDrawObj*)mDynDraw;
        if (dd != old) {
            if (dd != 0)
                ((void(__thiscall*)(DynDrawObj*))dd->vftable[0])(dd);
            mDynDraw = dd;
            if (old != 0)
                ((void(__thiscall*)(DynDrawObj*))old->vftable[1])(old);
        }
        ((void(__thiscall*)(DynDrawObj*, void*))((DynDrawObj*)mDynDraw)->vftable[4])((DynDrawObj*)mDynDraw, &mField30);
        return;
    }
    DynDrawObj* old = (DynDrawObj*)mDynDraw;
    if (old != 0) {
        mDynDraw = 0;
        ((void(__thiscall*)(DynDrawObj*))old->vftable[1])(old);
    }
}
}  // namespace SP

// @ 0x0073bab0
namespace SP {
void cModelInstance_s0073_afb0::Notify(cNotifyOther* other)
{
    if (mBlendBegin != mBlendEnd) {
        cBinding_s0073_afb0* e = mBindABegin;
        cBinding_s0073_afb0* end = mBindAEnd;
        for (; e != end; e++) {
            if (e->mBlender != 0) {
                ((void(__thiscall*)(cBlender_s0073_afb0*))e->mBlender->mVptr4[3])(e->mBlender);
                NotifyAdd(e->mInfo, e->mBlender, other, other->mField40);
            }
        }
        cBinding_s0073_afb0* f = mBindCBegin;
        cBinding_s0073_afb0* fend = mBindCEnd;
        for (; f != fend; f++) {
            if (f->mInfo != 0) {
                cBlender_s0073_afb0* bl = f->mBlender;
                if (bl != 0) {
                    ((void(__thiscall*)(cBlender_s0073_afb0*))bl->mVptr4[3])(bl);
                    *(cBlender_s0073_afb0**)f->mInfo = f->mBlender;
                    FinishNotify(f->mInfo);
                } else {
                    NotifyAlloc();
                }
            }
        }
    }
}
}  // namespace SP

// @ 0x0073cb40
AbilityD::AbilityD(RefObjV* a, int b, int c)
: AbilityBase(a, b), y(c) {}

// @ 0x0073d160
int cModelInstance_GetArenaResource::GetArenaResource()
{
    int result = 0;
    ArenaResource* p = mResource;
    if (p) {
        result = (int)p->v3(0x2f4e681b);
        if (result)
            return result;
    }
    p = mResource;
    if (p) {
        ArenaHolder* h = (ArenaHolder*)p->v3(0xe6bce5);
        if (h) {
            if (h->end - h->begin == 1)
                return h->begin->field74;
        }
    }
    return result;
}

// @ 0x0073d1e0
int cModelInstance_Deform::GetDeformationHandles(DeformHandle* dst, int maxCount)
{
    if ((((uint8_t*)mDynamicDraw)[8] & 8) == 0)
        return 0;
    int p = GetArenaResource();
    if (p == 0)
        return 0;
    Arena_s0073_cdf0* arena = *(Arena_s0073_cdf0**)(p + 0x18);
    int count = 0;
    int num = arena->GetNumExportedObjects();
    for (int i = 0; i < num; ++i) {
        ExportedObj obj;
        arena->GetExportedObjectByIndex(i, &obj);
        if (obj.type != 0xff0000)
            continue;
        ExportedMesh* m = (ExportedMesh*)obj.data;
        int j = 0;
        for (; j < count; ++j)
            if (dst[j].mId == m->id)
                break;
        if (j < count)
            continue;
        if (count >= maxCount)
            continue;
        DeformHandle* h = &dst[j];
        h->mId = m->id;
        h->mZero = 0;
        struct V3 { float x, y, z; };
        V3 a0; a0.x = (float)m->d[0]; a0.y = (float)m->d[1]; a0.z = (float)m->d[2];
        *(V3*)h->mP0 = a0;
        V3 a1; a1.x = (float)m->d[3]; a1.y = (float)m->d[4]; a1.z = (float)m->d[5];
        *(V3*)h->mP1 = a1;
        h->mF58 = m->f38;

        float org[3] = { h->mP0[0], h->mP0[1], h->mP0[2] };
        float vx = h->mP1[0] - h->mP0[0];
        float vy = h->mP1[1] - h->mP0[1];
        float vz = h->mP1[2] - h->mP0[2];
        if (vx * vx + vy * vy + vz * vz < 0.001f) {
            vx = 1.0f; vy = 0.0f; vz = 0.0f;
        }
        float len = (float)sqrt((double)(vz * vz + (vx * vx + vy * vy)));
        float inv = 1.0f / len;
        float n[3] = { vx * inv, vy * inv, vz * inv };

        float tmp[3];
        float* o = OrthogonalVector(tmp, n);
        float ux = o[0], uy = o[1], uz = o[2];
        float ulen = (float)sqrt((double)((ux * ux + uy * uy) + uz * uz));
        float uinv = 1.0f / ulen;
        ux *= uinv; uy *= uinv; uz *= uinv;

        float rot[9];
        rot[0] = n[0]; rot[1] = n[1]; rot[2] = n[2];
        rot[3] = ux;   rot[4] = uy;   rot[5] = uz;
        rot[6] = n[1] * uz - n[2] * uy;
        rot[7] = n[2] * ux - uz * n[0];
        rot[8] = uy * n[0] - n[1] * ux;

        h->mFlags |= 4;
        h->mVersion += 1;
        h->mPos[0] = org[0]; h->mPos[1] = org[1]; h->mPos[2] = org[2];
        h->mFlags |= 2;
        h->mVersion += 1;
        for (int k = 0; k < 9; ++k)
            h->mRot[k] = rot[k];
        ++count;
    }
    return count;
}

// @ 0x0073d6b0
int cModelInstance_Pose::GetPoseTransforms(cMDBoneTransform* dst, bool original)
{
    if (mpMaterialsBegin == mpMaterialsEnd)
        return 0;
    cPoseOwner** materials = mpMaterialsBegin;
    if (!materials[2] || !materials[2]->mpSkin || !materials[2]->mpSkin->mpMatrices)
        return 0;

    for (unsigned int i = 0; i < materials[2]->mpSkin->mnBones; ++i)
    {
        Mat4 m = materials[2]->mpSkin->mpMatrices[i];
        if (!original)
        {
            Mat4 inv;   // left untouched (uninitialized) when the matrix is singular
            AffineInverse(inv, (const float*)&m);
            m = inv;
        }
        // Transposed 3x4 store.
        for (int c = 0; c < 3; ++c)
        {
            BoneRow row;
            row.x = Lane(m.r[0], c);
            row.y = Lane(m.r[1], c);
            row.z = Lane(m.r[2], c);
            row.w = Lane(m.r[3], c);
            dst[i].m[c] = row;
        }
    }
    return materials[2]->mpSkin->mnBones;
}

// @ 0x0073e080
bool cModelInstance_Pose::PickLineWithHit(const float* pLine, const float* pDir, cSPTransformP* pTransform, float* pOut)
{
    if (*(void**)((char*)this + 0xcc) == 0)
        return false;

    __m128 origin = _mm_set_ps(pLine[0], pLine[2], pLine[1], pLine[0]);
    __m128 dir    = _mm_set_ps(pDir[0], pDir[2], pDir[1], pDir[0]);
    cModelInstance_Pose* self = this;
    XformBlock xf;
    if (pTransform->mScale != kOne) {
        pTransform->BackTransformPoint(&origin);
        pTransform->BackTransformPoint(&dir);
        _mm_store_ps(xf.t, _mm_setzero_ps());
        _mm_store_ps(xf.r2, _mm_set_ps(0.0f, kOne, 0.0f, 0.0f));
        _mm_store_ps(xf.r1, _mm_set_ps(0.0f, 0.0f, kOne, 0.0f));
        _mm_store_ps(xf.r0, _mm_set_ps(0.0f, 0.0f, 0.0f, kOne));
    } else {
        float s = pTransform->mScale;
        *(Vec3S*)xf.t = *(Vec3S*)pTransform->mTranslation;
        xf.r0[0] = pTransform->mRotation[0] * s; xf.r0[1] = pTransform->mRotation[1] * s; xf.r0[2] = pTransform->mRotation[2] * s;
        xf.r1[0] = pTransform->mRotation[3] * s; xf.r1[1] = pTransform->mRotation[4] * s; xf.r1[2] = pTransform->mRotation[5] * s;
        xf.r2[0] = pTransform->mRotation[6] * s; xf.r2[1] = pTransform->mRotation[7] * s; xf.r2[2] = pTransform->mRotation[8] * s;
    }

    PickCtx* ctx = g_pPickCtx;
    if (ctx == 0) {
        ResDescCombined desc;
        {
            ResDesc4 tmp = FUN_01201660_t(4, 4);
            FUN_006c1c80_t(&desc, &tmp);
        }
        ctx = (PickCtx*)FUN_012016d0_t(&desc, 4, 4);
        g_pPickCtx = ctx;
    }
    uint32_t scratch[25];
    void* pScratch = scratch;
    ctx->Init(&pScratch, 0, 1, &origin, &dir);
    ctx->mMode = 2;
    float minDist = kFltMax;
    int n;
    bool miss;
    do {
        ctx->mnHits = 0;
        ctx->mE8 = 0;
        DbObj* db = (*(DatabasePackedFileT**)((char*)self + 0xcc))->GetAllocator();
        typedef int (__thiscall *TraverseFn)(DbObj*, PickCtx*, XformBlock*);
        int r = ((TraverseFn)db->mpVtbl2[5])(db, ctx, &xf);
        ctx = g_pPickCtx;
        n = ctx->mnHits;
        miss = (r == 0);
        for (int i = 0; i < n; i++) {
            float d = ctx->mpHits[i].mDist;
            if (d < minDist)
                minDist = d;
        }
    } while (pOut != 0 && (unsigned)n > 0u && miss);

    if (kFltMax > minDist) {
        if (pOut != 0)
            *pOut = minDist;
        return true;
    }
    return false;
}

// @ 0x0073e410
bool cModelInstance::RayCast(const V3* p0, const V3* p1, cSPTransform_s0073_e410* xf, float* outT, V3* outPos, V3* outNormal, int* outA, int* outB)
{
    if (!mpResource)
        return false;
    V3A a0(p0);
    V3A a1(p1);
    float scale = xf->mScale;
    Mat4L mat;
    bool needXform;
    if (scale == 1.0f) {
        mat.t[0] = xf->tx; mat.t[1] = xf->ty; mat.t[2] = xf->tz;
        mat.r0[0] = xf->mRotation.m[0] * scale; mat.r0[1] = xf->mRotation.m[1] * scale; mat.r0[2] = xf->mRotation.m[2] * scale;
        mat.r1[0] = xf->mRotation.m[3] * scale; mat.r1[1] = xf->mRotation.m[4] * scale; mat.r1[2] = xf->mRotation.m[5] * scale;
        mat.r2[0] = xf->mRotation.m[6] * scale; mat.r2[1] = xf->mRotation.m[7] * scale; mat.r2[2] = xf->mRotation.m[8] * scale;
        needXform = false;
    } else {
        needXform = true;
        xf->BackTransformPoint(&a0);
        xf->BackTransformPoint(&a1);
        mat.t[0] = 0; mat.t[1] = 0; mat.t[2] = 0; mat.t[3] = 0;
        mat.r2[0] = 0; mat.r2[1] = 0; mat.r2[2] = 1.0f; mat.r2[3] = 0;
        mat.r0[0] = 1.0f; mat.r0[1] = 0; mat.r0[2] = 0; mat.r0[3] = 0;
        mat.r1[0] = 0; mat.r1[1] = 1.0f; mat.r1[2] = 0; mat.r1[3] = 0;
    }
    needXform = scale != 1.0f;
    if (g_rayCache == 0) {
        char arr[32];
        char tmp[16];
        int r = FUN_01201660b(arr, 4, 4);
        FUN_006c1c80b(tmp, r);
        ehvec_dtor(arr, 8, 4, (void (__thiscall*)(void*))Elem8Dtor);
        g_rayCache = FUN_012016d0b(tmp, 4, 4);
    }
    RayCache* cache = g_rayCache;
    char buf[100];
    XfBuf xb;
    xb.p = buf;
    cache->FUN_73a6e0(&xb, 0, 1, &a0, &a1);
    cache->f100 = 2;
    float best = kFltMax;
    int bestId = -1;
    bool again;
    do {
        cache->count = 0;
        cache->fE8 = 0;
        AllocObj* al = ((ResObj*)mpResource)->GetAllocator();
        void** iface = *(void***)((char*)al + 0x20);
        int r = ((int (__thiscall*)(void*, RayCache*, Mat4L*))iface[0x14 / 4])(al, cache, &mat);
        cache = g_rayCache;
        again = (r == 0);
        for (int i = 0; i < cache->count; ++i) {
            HitRec* h = &cache->hits[i];
            if (best > h->t) {
                a1.set(h->pos);
                best = h->t;
                a0.set(h->dir);
                bestId = cache->ids[i].id;
            }
        }
    } while (cache->count != 0 && again);
    if (!(best < kFltMax))
        return false;
    if (outT)
        *outT = best;
    if (outPos) {
        outPos->x = a1.x; outPos->y = a1.y; outPos->z = a1.z;
        if (needXform) {
            if (xf->mFlags & 2) {
                float y = outPos->y, z = outPos->z, x = outPos->x;
                const float* r = xf->mRotation.m;
                outPos->x = (r[3] * y + r[6] * z) + x * r[0];
                outPos->y = (r[1] * x + r[4] * y) + r[7] * z;
                outPos->z = (r[2] * x + r[5] * y) + r[8] * z;
            }
            float s = xf->mScale;
            float z = outPos->z, x = outPos->x, y = outPos->y;
            outPos->y = s * y;
            outPos->z = z * s;
            outPos->x = x * s;
            outPos->x = x * s + xf->tx;
            outPos->y = xf->ty + s * y;
            outPos->z = xf->tz + z * s;
        }
    }
    if (outNormal) {
        outNormal->x = a0.x; outNormal->y = a0.y; outNormal->z = a0.z;
        if (needXform && (xf->mFlags & 2)) {
            float y = outNormal->y, z = outNormal->z, x = outNormal->x;
            const float* r = xf->mRotation.m;
            outNormal->x = (r[3] * y + r[6] * z) + r[0] * x;
            outNormal->y = (r[1] * x + r[4] * y) + r[7] * z;
            outNormal->z = (r[2] * x + r[5] * y) + r[8] * z;
        }
    }
    if (outA || outB) {
        int v;
        if (mpD0) {
            v = ((IdLookup*)mpD0)->FUN_729ad0(bestId);
        } else {
            v = -1;
            bestId = -1;
        }
        if (outA) *outA = v;
        if (outB) *outB = bestId;
    }
    return true;
}

// @ 0x0073eb90
bool cModelInstance::GetMeshes(void* a)
{
    if (mpHull) {
        int n = mpDynDraw->mElems.size();
        for (int i = 0; i < n; ++i) {
            DynDrawElem* e = &mpDynDraw->mElems.begin[i];
            if (e->p8) {
                if (e->p0) {
                    void** vt2 = *(void***)((char*)e->p0 + 4);
                    ((void (__thiscall*)(void*))vt2[3])(e->p0);
                    *e->p8 = e->p0;
                    ((ElemRelease*)e->p8)->FUN_01200940();
                } else {
                    FUN_007c5490b();
                }
            }
        }
        if (((bool (__thiscall*)(void*, void*))mpHull->vt[0x18 / 4])(mpHull, a))
            return true;
    }
    IfaceObj* i1 = mpIface;
    if (i1) {
        int r = ((int (__thiscall*)(void*, unsigned))i1->vt[0xc / 4])(i1, 0xe6bce5);
        if (r) {
            FUN_00730210(r, (int)a);
            return true;
        }
    }
    IfaceObj* i2 = mpIface;
    if (i2) {
        int r = ((int (__thiscall*)(void*, unsigned))i2->vt[0xc / 4])(i2, 0x2f4e681b);
        if (r) {
            FUN_0072fff0(r, (int)a);
            return true;
        }
    }
    return false;
}

// @ 0x0073eca0
void cModelInstance::SetDrawTransform(const void* srcv, void* outv)
{
    const DrawXfSrc* p = (const DrawXfSrc*)srcv;
    OutM* out = (OutM*)outv;
    float s = p->s;
    out->m[0] = p->r[0] * s;
    out->m[1] = p->r[1] * s;
    out->m[2] = p->r[2] * s;
    out->m[4] = p->r[3] * s;
    out->m[5] = p->r[4] * s;
    out->m[6] = p->r[5] * s;
    out->m[8] = s * p->r[6];
    out->m[9] = p->r[7] * s;
    out->m[10] = p->r[8] * s;
    *(V3*)&out->m[12] = p->t;
    if (p->s == 1.0f && (p->flags & 6) == 0)
        out->type = 4;
    else if (p->s == 1.0f)
        out->type = 3;
    else
        out->type = 2;
    g_dirty |= 1;
    g_xfType = out->type;
    g_xfPtr = &g_xfLocal;
    g_xfLocal = *out;
    ((DynDrawSink*)mpDynDraw)->FUN_73bab0(out);
}

// @ 0x0073ede0
void cModelInstance::DispatchMesh(MeshDrawObj* obj, unsigned idx, int, MeshCtx* ctx)
{
    ctx->refcount50++;
    PushShaderDataNull();
    CompiledState* cs = 0;
    if (idx < (unsigned)(v30_end - v30_begin) && v30_begin[idx])
        cs = *(CompiledState**)((char*)v30_begin[idx] + 4);
    ShaderDataObj* sd = 0;
    if (idx < (unsigned)(v44_end - v44_begin))
        sd = (ShaderDataObj*)v44_begin[idx];
    if (cs) {
        SetShaderDataC(cs);
        cs->Dispatch();
    }
    VertDesc* vd = *obj->f24;
    if (((vd->flags >> 14) & 1) && !ctx->b48 && g_AppProps->f3c->f58 == 0) {
        if (ctx->f4c) {
            if (mpDynDraw->f0c == ctx->f4c)
                g_sh_62e880 = mpDynDraw->f10;
            else
                g_sh_62e880 = g_sh_62b870;
            if (v1c_begin == v1c_end) {
                g_sh_62e874 = ctx->f4c;
            } else {
                g_sh_62e880 = g_sh_62e880 + v1c_begin[idx].a * 0x30;
                g_sh_62e874 = v1c_begin[idx].b;
            }
            ShaderSet(4, g_sh_62e870, 1);
            ShaderSet(3, g_sh_5377cc, 0);
        }
    } else {
        ShaderSet(3, 0, 0);
        ShaderSet(4, 0, 0);
    }
    if (vd->flags & 4) {
        unsigned n = vd->count;
        unsigned i = 0;
        if (n) {
            char* e = (char*)vd + 0x18;
            do {
                if (*(int*)(e + 8) == 2) {
                    if (e[4] == 5 && g_sh_5379d8)
                        ShaderSet(0x22c, &g_sh_5379d8, 0);
                    break;
                }
                ++i;
                e += 0xc;
            } while (i < n);
        }
    }
    g_primType = obj->f08->primType;
    if (g_vertDesc == 0 || !VertexDescriptor_AreEqual(g_vertDesc, vd))
        g_softState |= 0x100000;
    g_vertDesc = vd;
    vd->FUN_11f2bc0();
    if (sd) sd->Push();
    if (ctx->f44) ctx->f44->Push();
    obj->FUN_11f9710();
    ShaderEnd();
}

// @ 0x0073f000
PartTransform::PartTransform(int a1, RCObj* obj, const cSPTransform_s0073_e410* t1, const cSPTransform_s0073_e410* t2)
: PTBase(a1, obj), mXf(*t1), mXf2(*t2), mInverse(*t2)
{
    mTail0 = 0;
    mTail1 = 0;
    mTail2 = 0;
    mInverse = mXf;
    mInverse.Invert();
}

// @ 0x0073f110
bool BBoxTest::Test(const AABB* other)
{
    if (box.mn.x <= other->mx.x)
        if (other->mn.x <= box.mx.x)
            if (box.mn.y <= other->mx.y)
                if (other->mn.y <= box.mx.y)
                    if (box.mn.z <= other->mx.z)
                        if (other->mn.z <= box.mx.z)
                            return true;
    return false;
}

// @ 0x0073f1c0
PartTransform::PartTransform(const PartTransform& o)
: PTBase(o), mXf(o.mXf), mXf2(o.mXf2), mInverse(o.mInverse)
{
    mTail0 = o.mTail0;
    mTail1 = o.mTail1;
    mTail2 = o.mTail2;
}

// @ 0x0073f2e0
void __stdcall ReleaseRange(RCItem* first, RCItem* last)
{
    for (; first < last; ++first) {
        RC* p = first->mpObject;
        if (p) {
            int n = (p->mnRefCount += -1);
            if (n == 0) {
                p->mnRefCount = 1;
                _ReadWriteBarrier();
                p->v0(1);
            }
        }
    }
}

// @ 0x0073f320
cSkinBinding& cSkinBinding::operator=(const cSkinBinding& o)
{
    f0 = o.f0;
    f4 = o.f4;
    f8 = o.f8;
    if (o.p0c != p0c) {
        RC_s0073_f320* p = o.p0c;
        RC_s0073_f320* old = p0c;
        if (p)
            ++p->mnRefCount;
        p0c = p;
        if (old) {
            int n = (old->mnRefCount += -1);
            if (n == 0) {
                old->mnRefCount = 1;
                _ReadWriteBarrier();
                old->v0(1);
            }
        }
    }
    t10 = o.t10;
    t48 = o.t48;
    t80 = o.t80;
    b8 = o.b8;
    bc = o.bc;
    c0 = o.c0;
    return *this;
}

// @ 0x0073f440
RefPair* __cdecl copy_backward_ref(RefPair* first, RefPair* last, RefPair* result)
{
    while (last != first) {
        --last; --result;
        result->value = last->value;
        RC_s0073_f320* p = last->p;
        RC_s0073_f320* old = result->p;
        if (p != old) {
            if (p) RcAddRef(p);
            result->p = p;
            if (old) RcRelease(old);
        }
    }
    return result;
}

// @ 0x0073f4b0
void ModelInstanceAnim::SetAnimationGroupTransform(int idx, const cSPTransform_s0073_f320& t)
{
    if (idx >= 0 && idx < (int)(mMeshesEnd - mMeshesBegin)) {
        signed char m = mMeshesBegin[idx].mat;
        if (m >= 0) {
            Material& mat = mMaterials[m];
            cSPTransform_s0073_f320& src = mat.src;
            if (src.mScale == 1.0f && (src.mFlags & 6) == 0) {
                mat.dst = t;
            } else {
                cSPTransform_s0073_f320 tmp;
                mat.dst = translateTransform(tmp, src, t);
            }
        }
    }
}

// @ 0x0073f540
bool cModelInstanceQ::PickLine(const float* origin, float len, const cSPTransform_s0073_f320* xf, bool firstHitOnly)
{
    if (!mExternalBoneTable)
        return false;
    float p[3] = { origin[0], origin[1], origin[2] };
    M4 basis;
    if (xf->mScale == 1.0f) {
        const float s = xf->mScale;
        basis.r0.x = xf->mRotation[0] * s; basis.r0.y = xf->mRotation[1] * s; basis.r0.z = xf->mRotation[2] * s;
        basis.r1.x = xf->mRotation[3] * s; basis.r1.y = xf->mRotation[4] * s; basis.r1.z = xf->mRotation[5] * s;
        basis.r2.x = s * xf->mRotation[6]; basis.r2.y = xf->mRotation[7] * s; basis.r2.z = xf->mRotation[8] * s;
        basis.t.x = xf->mTranslation[0]; basis.t.y = xf->mTranslation[1]; basis.t.z = xf->mTranslation[2];
    } else {
        xf->BackTransformPoint(p);
        len = len / xf->mScale;
        basis.r0.x = 1.0f; basis.r0.y = 0.0f; basis.r0.z = 0.0f; basis.r0.w = 0.0f;
        basis.r1.x = 0.0f; basis.r1.y = 1.0f; basis.r1.z = 0.0f; basis.r1.w = 0.0f;
        basis.r2.x = 0.0f; basis.r2.y = 0.0f; basis.r2.z = 1.0f; basis.r2.w = 0.0f;
        basis.t.x = 0.0f; basis.t.y = 0.0f; basis.t.z = 0.0f; basis.t.w = 0.0f;
    }
    V4 mx, mn;
    mx.x = kRay0 * len + p[0];
    mx.y = p[1] + kRay1 * len;
    mx.z = p[2] + kRay2 * len;
    mx.w = mx.x;
    mn.x = p[0] - kRay0 * len;
    mn.y = p[1] - kRay1 * len;
    mn.z = p[2] - kRay2 * len;
    mn.w = mn.x;
    char stackBuf[100];
    void* stackBufPtr = stackBuf;
    QueryState* q = GetQuery(gPickQuery);
    InitQuery(q, &stackBufPtr, mn, mx);
    BoxPair box; box.mMin = mn; box.mMax = mx;
    ExternalTable* table = mExternalBoneTable;
    for (int r = RunQuery(table, q, &basis); r == 0; r = RunQuery(mExternalBoneTable, gPickQuery, &basis)) {
        if (firstHitOnly)
            return true;
        uint32_t i = 0;
        if (gPickQuery->mItemCount != 0) {
            int off = 0;
            do {
                QueryItem* it = (QueryItem*)((char*)gPickQuery->mItems + off);
                it->mFlags &= ~1u;
                if (it->Test(0, 0, &mx) && box.Overlaps(&mx))
                    return true;
                ++i;
                off += 0x60;
            } while (i < gPickQuery->mItemCount);
        }
    }
    return false;
}

// @ 0x0073f910
bool cModelInstanceQ::IntersectsSphere(const cSPBoundingBox_s0073_f320* box, const cSPTransform_s0073_f320* xf, bool firstHitOnly)
{
    if (!mExternalBoneTable)
        return false;
    M4 basis;
    PartTransform64 inv;   // only built when the scale is not 1; the item tests below read it either way
    V4 mn, mx;
    if (xf->mScale == 1.0f) {
        mx.x = box->mMax[0]; mx.y = box->mMax[1]; mx.z = box->mMax[2]; mx.w = box->mMax[0];
        mn.x = box->mMin[0]; mn.y = box->mMin[1]; mn.z = box->mMin[2]; mn.w = box->mMin[0];
        const float s = xf->mScale;
        basis.t.x = xf->mTranslation[0]; basis.t.y = xf->mTranslation[1]; basis.t.z = xf->mTranslation[2];
        basis.r0.x = s * xf->mRotation[0]; basis.r0.y = xf->mRotation[1] * s; basis.r0.z = xf->mRotation[2] * s;
        basis.r1.x = xf->mRotation[3] * s; basis.r1.y = xf->mRotation[4] * s; basis.r1.z = xf->mRotation[5] * s;
        basis.r2.x = s * xf->mRotation[6]; basis.r2.y = xf->mRotation[7] * s; basis.r2.z = xf->mRotation[8] * s;
    } else {
        inv.Construct(*xf);
        inv.Invert();
        cSPBoundingBox_s0073_f320 bb = *box;
        bb.Transform(&inv);
        mn.x = bb.mMin[0]; mn.y = bb.mMin[1]; mn.z = bb.mMin[2]; mn.w = bb.mMin[0];
        mx.x = bb.mMax[0]; mx.y = bb.mMax[1]; mx.z = bb.mMax[2]; mx.w = bb.mMax[0];
        basis.r0.x = 1.0f; basis.r0.y = 0.0f; basis.r0.z = 0.0f; basis.r0.w = 0.0f;
        basis.r1.x = 0.0f; basis.r1.y = 1.0f; basis.r1.z = 0.0f; basis.r1.w = 0.0f;
        basis.r2.x = 0.0f; basis.r2.y = 0.0f; basis.r2.z = 1.0f; basis.r2.w = 0.0f;
        basis.t.x = 0.0f; basis.t.y = 0.0f; basis.t.z = 0.0f; basis.t.w = 0.0f;
    }
    char stackBuf[100];
    void* stackBufPtr = stackBuf;
    QueryState* q = GetQuery(gSphereQuery);
    InitQuery(q, &stackBufPtr, mn, mx);
    BoxPair bp; bp.mMin = mn; bp.mMax = mx;
    ExternalTable* table = mExternalBoneTable;
    for (int r = RunQuery(table, q, &basis); r == 0; r = RunQuery(mExternalBoneTable, gSphereQuery, &basis)) {
        if (firstHitOnly)
            return true;
        uint32_t i = 0;
        if (gSphereQuery->mItemCount != 0) {
            int off = 0;
            do {
                QueryItem* it = (QueryItem*)((char*)gSphereQuery->mItems + off);
                it->mFlags &= ~1u;
                if (it->Test(0, 0, &inv) && bp.Overlaps(&inv))
                    return true;
                ++i;
                off += 0x60;
            } while (i < gSphereQuery->mItemCount);
        }
    }
    return false;
}

// @ 0x0073fd20
int ModelInstanceDispatch::Dispatch(int a2, int a3)
{
    DispatchCtx c;
    int i = 0;
    c.result = 0;
    c.arg3 = a3;
    Setup(sub70, &c);
    mProc->Process(&c);
    if (!(mFlags & 4)) {
        int n = (int)(mMeshesEnd - mMeshesBegin);
        if (n > 0) {
            do {
                DispatchMesh(mMeshesBegin[i], i, a2, &c);
                ++i;
            } while (i < n);
        }
    }
    Listener* l = mListener;
    if (l)
        l->OnDispatch(this, &c, a2);
    return c.result;
}

// @ 0x0073fe50
void __cdecl copy_backward8(T8* first, T8* last, T8* result)
{
    while (last != first) {
        *--result = *--last;
    }
}

// @ 0x0073fe80
bool __fastcall ValidateA(char* self)
{
    bool ok = false;
    MeshVec meshes;
    (*(ModelInstanceMeshes**)(self + 0xc))->GetMeshes(meshes);
    BindQuery q;
    if (BuildQuery(&q, &meshes, *(int*)(self + 0x10)) && q.count == 3) {
        ok = true;
        self += 0x14;
        for (int i = 0; i < 3; ++i) {
            if (ok && q.Check(self, 3, i, 1, -1)) ok = true;
            else ok = false;
            self += 0xc;
        }
    }
    return ok;
}

// @ 0x0073ffb0
bool __fastcall ValidateB(char* self)
{
    bool ok = false;
    MeshVec meshes;
    (*(ModelInstanceMeshes**)(self + 0xc))->GetMeshes(meshes);
    BindQuery q;
    if (BuildQuery(&q, &meshes, *(int*)(self + 0x10)) && q.count == 3) {
        ok = true;
        self += 0x30;
        for (int i = 0; i < 3; ++i) {
            if (ok && q.Check(self - 0x1c, 3, i, 1, -1) && CheckEntry(&q, i, self - 0x10, self)) ok = true;
            else ok = false;
            self += 0x2c;
        }
    }
    return ok;
}

// @ 0x007400f0
BindingSet::BindingSet()
: mFlags(0), f0c(0), f10(0), f90(0), f94(0) {}

// @ 0x007402e0
BindingContainer::~BindingContainer()
{}

// @ 0x00740370
void ArrayHolder::SetArray(DynArray* p)
{
    DynArray* old = mArray;
    if (old) {
        void* first = old->first;
        if (first && *(int*)((char*)first - 4) != 0)
            EASTL_allocator_deallocate(first);
        EASTL_allocator_deallocate(old);
    }
    mArray = p;
}

// @ 0x007403c0
void cModelInstanceBones::LoadExportedBoneTable(ArenaOwner* src)
{
    Arena* arena = src->arena;
    int n = arena->GetNumExportedObjects();
    for (int i = 0; i < n; ++i) {
        ExpObj x;
        arena->GetExportedObjectByIndex(i, &x);
        if (x.type == 0x80003) {
            BoneTable* t = new("Graphics", 0, 0, (const char*)0, 0) BoneTable(&x, src);
            RefIface* old = mBones;
            if (t != old) {
                if (t) t->AddRef();
                mBones = t;
                if (old) old->Release();
            }
            PtrArr* h = mHull;
            if (h) {
                void* b = h->begin;
                if (b && ((int*)b)[-1] != 0) operator delete[](b);
                operator delete[](h);
            }
            mHull = 0;
        }
    }
}

// @ 0x00740550
int cModelResourceInfo::GetBoneTransforms(Mat12* out)
{
    if (mAnimBegin == mAnimEnd || mRangesBegin == mRangesEnd)
        return 0;
    if (mClampTable != 0 && mClamp != 0) {
        int total = (mRangesBegin == mRangesEnd) ? 0 : mRangesEnd[-1].count + mRangesEnd[-1].start;
        int n = Min(mClamp, total);
        CopyMats(mClampTable, mClampTable + n, out);
    }
    Mat12 ident;
    ident.m[0] = g_f01485720; ident.m[1] = 0; ident.m[2] = 0; ident.m[3] = 0;
    ident.m[4] = 0; ident.m[5] = g_f01485720; ident.m[6] = 0; ident.m[7] = 0;
    ident.m[8] = 0; ident.m[9] = 0; ident.m[10] = g_f01485720; ident.m[11] = 0;
    int numRanges = (int)(mRangesEnd - mRangesBegin);
    for (int i = 0; i < numRanges; ++i) {
        BoneRange* r = mRangesBegin + i;
        int lo = 0;
        if (mClampTable != 0) {
            int t = mClamp - r->start;
            lo = Max(t, 0);
            if (lo >= r->count) continue;
        }
        Mat12* dst = out + r->start;
        if (r->mat == 0xff) {
            for (Mat12* p = dst + lo; p != dst + r->count; ++p)
                *p = ident;
        } else {
            Material_s0074_03c0* m = mMats + (int8_t)r->mat;
            MaterialPrepare(m, 0);
            Mat12* src = **m->aux->pm;
            Mat12* d = dst + lo;
            for (Mat12* p = src + lo; p != src + r->count; ++p, ++d)
                *d = *p;
        }
    }
    return mRangesEnd[-1].count + mRangesEnd[-1].start;
}

// @ 0x00740740
int cModelResourceInfo::GetBoneIDs(uint32_t* dst)
{
    if (mAnimBegin == mAnimEnd || mRangesBegin == mRangesEnd)
        return 0;
    BoneRange* r = mRangesBegin;
    uint32_t n = 0;
    if (r->mat != 0xff) {
        Material_s0074_03c0* m = mMats + (int8_t)r->mat;
        uint32_t cnt = (uint32_t)(int)r->count;
        IdSet* ids = m->aux2->ids;
        uint32_t* data = ids->data;
        n = Min(ids->count, cnt);
        CopyWords(dst, data, n * 4);
    }
    uint32_t* end = dst + r->count;
    for (uint32_t* p = dst + n; p != end; ++p)
        *p = 0;
    return r->count;
}

// @ 0x007407d0
bool cModelInstanceB::CreateBinding(uint32_t a2, RefIface** out)
{
    ResRef* B = mRes;
    void* c = B->v28Begin;
    if (mOwner) {
        void* v1;
        if (c == B->v28End) v1 = 0; else v1 = c;
        void* v2;
        if (B->v50Begin == B->v50End) v2 = 0; else v2 = B->v50Begin;
        Binding* b = new("Graphics", 0, 0, 0, 0) T20(this, a2, v1, v2);
        Hold<Binding> h(b);
        Owner* o = mOwner;
        RefIface* old = b->mTarget;
        if (old) { b->mTarget = 0; old->Release(); }
        if (o->Validate(b->mKey, &b->mTarget)) {
            b->AddRef();
            *out = b;
            return true;
        }
        return false;
    }
    if (c != B->v28End) {
        T9c* t = new("Graphics", 0, 0, 0, 0) T9c(this, a2, c);
        Hold<T9c> h(t);
        if (ValidateB(t)) {
            t->AddRef();
            *out = t;
            return true;
        }
    }
    T38* t = new("Graphics", 0, 0, 0, 0) T38(this, a2);
    Hold<T38> h(t);
    if (ValidateA(t)) {
        t->AddRef();
        *out = t;
        return true;
    }
    return false;
}

// @ 0x007409d0
void Vec12Vector::DoInsertValue(Vec12* pos, const Vec12& value)
{
    Vec12* end = mpEnd;
    if (end != mpCapacity) {
        const Vec12* v = &value;
        if (!(v < pos) && v < end) v += 1;
        if (end) { end->a = end[-1].a; end->b = end[-1].b; end->c = end[-1].c; }
        Vec12* dst = mpEnd;
        Vec12* src = mpEnd - 1;
        while (src != pos) {
            --src; --dst;
            dst->a = src->a; dst->b = src->b; dst->c = src->c;
        }
        pos->a = v->a; pos->b = v->b; pos->c = v->c;
        mpEnd = mpEnd + 1;
        return;
    }
    int n = (int)(end - mpBegin);
    int newCap;
    Vec12* nd;
    if (n != 0) {
        newCap = n * 2;
        if (newCap == 0) { nd = 0; goto haveBuf; }
    } else {
        newCap = 1;
    }
    nd = (Vec12*)operator new(newCap * 12, "Graphics", 0, 0, kEastlFile, 0xd1);
haveBuf:
    Vec12* r = (Vec12*)H_uninit_copy12(mpBegin, pos, nd);
    if (r) { r->a = value.a; r->b = value.b; r->c = value.c; }
    Vec12* ne = (Vec12*)H_uninit_copy12(pos, mpEnd, r + 1);
    if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete[](mpBegin);
    mpBegin = nd;
    mpEnd = ne;
    mpCapacity = nd + newCap;
}

// @ 0x00740b00
void Vec8Vector::DoInsertValues(P8* pos, uint32_t n, const P8& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            P8 tmp = value;
            P8* oldEnd = mpEnd;
            uint32_t after = (uint32_t)(oldEnd - pos);
            if (n < after) {
                P8* mid = oldEnd - n;
                P8* t;
                H_move8(&t, mid, oldEnd, oldEnd, mid);
                mpEnd += n;
                H_copy_backward8(pos, mid, oldEnd);
                H_fill8(pos, pos + n, &tmp);
            } else {
                uint32_t extra = n - after;
                P8* t;
                H_fill_n8(oldEnd, extra, &tmp);
                mpEnd += extra;
                H_move8(&t, pos, oldEnd, mpEnd, (void*)after);
                mpEnd += after;
                H_fill8(pos, oldEnd, &tmp);
            }
        }
    } else {
        uint32_t prev = (uint32_t)(mpEnd - mpBegin);
        uint32_t grow = prev > 0 ? prev * 2 : 1;
        uint32_t newCap = prev + n;
        if (!(newCap > grow)) newCap = grow;
        P8* nd = 0;
        if (newCap) nd = (P8*)operator new(newCap * 8, "Graphics", 0, 0, kEastlFile, 0xd1);
        P8* np = (P8*)H_uninit_copy8(mpBegin, pos, nd);
        P8* q = np;
        for (uint32_t i = n; i > 0; --i) {
            if (q) { q->a = value.a; q->b = value.b; }
            ++q;
        }
        P8* ne = (P8*)H_uninit_copy8(pos, mpEnd, np + n);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete[](mpBegin);
        mpBegin = nd;
        mpEnd = ne;
        mpCapacity = nd + newCap;
    }
}

// @ 0x00740cc0
void Vec8Vector::DoInsertRange(P8* pos, P8* first, P8* last, int tag)
{
    (void)tag;
    if (first == last) return;
    uint32_t n = (uint32_t)(last - first);
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        P8* oldEnd = mpEnd;
        uint32_t after = (uint32_t)(oldEnd - pos);
        if (n < after) {
            P8* mid = oldEnd - n;
            P8* t;
            H_move8(&t, mid, oldEnd, oldEnd, first);
            mpEnd += n;
            H_copy_backward8(pos, mid, oldEnd);
            H_copy8b(first, last, pos);
        } else {
            P8* mid = first + after;
            P8* t;
            H_move8(&t, mid, last, oldEnd, first);
            mpEnd += n - after;
            H_move8(&t, pos, oldEnd, mpEnd, first);
            mpEnd += after;
            H_copy_backward8(first, mid, pos + after);
        }
    } else {
        uint32_t prev = (uint32_t)(mpEnd - mpBegin);
        uint32_t newCap = prev * 2;
        if (prev == 0) newCap = 1;
        if (!(newCap > prev + n)) newCap = prev + n;
        P8* nd = 0;
        if (newCap) nd = (P8*)operator new(newCap * 8, "Graphics", 0, 0, kEastlFile, 0xd1);
        P8* np = (P8*)H_copy8(mpBegin, pos, nd);
        P8* t;
        H_move8(&t, first, last, np, first);
        P8* ne = (P8*)H_copy8(pos, mpEnd, np);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete[](mpBegin);
        mpBegin = nd;
        mpEnd = ne;
        mpCapacity = nd + newCap;
    }
}

// @ 0x00740e90
MInit::MInit()
{
    vt = vtbl_cModelInstance;
    w[0] = 0; w[1] = 0; w[2] = 0;
    w[5] = 0; w[6] = 0; w[7] = 0;
    w[0xa] = 0; w[0xb] = 0; w[0xc] = 0;
    w[0xf] = 0; w[0x10] = 0; w[0x11] = 0;
    w[0x14] = 0; w[0x15] = 0; w[0x16] = 0;
    *(uint16_t*)((char*)this + 0x72) = 0;
    *(uint16_t*)((char*)this + 0x70) = 0;
    float* f = (float*)this;
    f[0x1d] = g_f0162e88c;
    f[0x1e] = g_f0162e890;
    f[0x1f] = g_f0162e894;
    f[0x20] = g_f01485720;
    ((Matrix3Place*)((char*)this + 0x84))->Assign(g_Matrix0162e9cc);
    f[0x2a] = g_fNeg1;
    f[0x2b] = g_fNeg1;
    f[0x2c] = g_fNeg1;
    f[0x2d] = g_f01485720;
    f[0x2e] = g_f01485720;
    f[0x2f] = g_f01485720;
    f[0x30] = g_f01485720;
    ((uint32_t*)this)[0x31] = 0;
    *(uint16_t*)((char*)this + 0xc8) = 0;
    ((uint32_t*)this)[0x33] = 0; ((uint32_t*)this)[0x34] = 0;
    Vec3 mn(g_fMax, g_fMax, g_fMax);
    *(Vec3*)((char*)this + 0xd4) = mn;
    Vec3 mx(g_fMin, g_fMin, g_fMin);
    *(Vec3*)((char*)this + 0xe0) = mx;
    ((uint32_t*)this)[0x3b] = 0; ((uint32_t*)this)[0x3c] = 0;
    ((uint32_t*)this)[0x3e] = (uint32_t)-1; ((uint32_t*)this)[0x3f] = (uint32_t)-1;
}

// @ 0x00741040
cModelInstance_s0074_03c0::~cModelInstance_s0074_03c0()
{
    vt = vtbl_cModelInstance;
    HullData* h = mHull;
    if (h) {
        void* b = h->begin;
        if (b && ((int*)b)[-1] != 0) operator delete[](b);
        operator delete[](h);
    }
    mHull = 0;
    if (mBones.p) {
        RefIface* bones = mBones.p;
        mBones.p = 0;
        bones->Release();
    }
}

// @ 0x00741150
void* cModelInstanceR::GetRegionMaterialInfo(int region)
{
    if (v44Begin == v44End || v30Begin == v30End)
        return 0;
    KeyPair* end = mapEnd;
    KeyPair* it = RegionLowerBound(mapBegin, end, &region, flag);
    if (it == end || region < it->key || it == it + 1)
        it = end;
    if (it != end)
        return it->value;
    return 0;
}

// @ 0x007411b0
void Vec12Vector::push_back(const Vec12& value)
{
    Vec12* p = mpEnd;
    if (p < mpCapacity) {
        mpEnd = p + 1;
        if (p != 0) {
            p->a = value.a;
            p->b = value.b;
            p->c = value.c;
        }
        return;
    }
    DoInsertValue(p, value);
}

// @ 0x00741210
void cMI_Geo::AddGeometryFromArena(SrcModel* src)
{
    Arena* arena = src->arena;
    int n = arena->GetNumExportedObjects();
    mBox.mMin = Vec3_s0074_1210(g_fMax, g_fMax, g_fMax);
    mBox.mMax = Vec3_s0074_1210(g_fMin, g_fMin, g_fMin);
    MaterialManager* mm = GetMaterialManager();
    for (int i = 0; i < n; ++i) {
        ExpObj x;
        arena->GetExportedObjectByIndex(i, &x);
        switch (x.type) {
        case 0x2000c: {
            ResKey key = src->mKey;
            EString16 name;
            GetManager()->KeyToName(&key, &name);
            break;
        }
        case 0x2001a: {
            void* mesh = *(void**)x.obj;
            mMeshes.push_back(mesh);
            MatRes* r = mm->Create(((unsigned*)x.obj)[2], src);
            void* mat = mm->Wrap(r);
            mMats.push_back(mat);
            break;
        }
        case 0x80005: {
            const ASrcBox* sb = (const ASrcBox*)x.obj;
            BBox3 b(Vec3_s0074_1210(sb->GetMin().m128_f32[0], sb->GetMin().m128_f32[1], sb->GetMin().m128_f32[2]),
                    Vec3_s0074_1210(sb->GetMax().m128_f32[0], sb->GetMax().m128_f32[1], sb->GetMax().m128_f32[2]));
            if (mBox.mMin.x > mBox.mMax.x) {
                mBox = b;
            } else {
                if (mBox.mMin.x > b.mMin.x) mBox.mMin.x = b.mMin.x;
                if (b.mMax.x > mBox.mMax.x) mBox.mMax.x = b.mMax.x;
                if (mBox.mMin.y > b.mMin.y) mBox.mMin.y = b.mMin.y;
                if (b.mMax.y > mBox.mMax.y) mBox.mMax.y = b.mMax.y;
                if (mBox.mMin.z > b.mMin.z) mBox.mMin.z = b.mMin.z;
                if (b.mMax.z > mBox.mMax.z) mBox.mMax.z = b.mMax.z;
            }
            break;
        }
        }
    }
    if (mBox.mMin.x > mBox.mMax.x) {
        mBox.mMin = Vec3_s0074_1210(g_f0162e88c - 1.0f, g_f0162e890 - 1.0f, g_f0162e894 - 1.0f);
        mBox.mMax = Vec3_s0074_1210(g_f0162e88c + 1.0f, g_f0162e890 + 1.0f, g_f0162e894 + 1.0f);
    }
    Vec3_s0074_1210 neg(-mBox.mMin.x, -mBox.mMin.y, -mBox.mMin.z);
    const float& rz = MaxRef(mBox.mMax.z, neg.z);
    const float& ry = MaxRef(mBox.mMax.y, neg.y);
    const float& rx = MaxRef(mBox.mMax.x, neg.x);
    mRadius = (float)sqrt(rx * rx + ry * ry + rz * rz);
}

// @ 0x00741710
void cLoadQueueS::StallUntilLoaded(UIntVec* out)
{
    out->clear();
    const int n = (int)(mpEnd - mpBegin);
    for (int i = 0; i < n; ++i) {
        ShaderOwner* o = mpBegin[i]->mOwner;
        if (o && (o->mDirty & 8)) {
            const uint32_t* d = o->D3D9GetShaderData(0x20f);
            if (d)
                out->push_back(*d);
        }
    }
}

// @ 0x007418f0
void Vec8::DoInsertValue(RefPair8* pos, const RefPair8* v)
{
    RefPair8* end = mpEnd;
    if (end != mpCapacity) {
        const RefPair8* pv = v;
        if (v >= pos && v < end)
            ++pv;
        if (end != 0) {
            end->value = end[-1].value;
            RefCounted* r = end[-1].p;
            end->p = r;
            if (r)
                _InterlockedIncrement((volatile long*)&r->mnRefCount);
        }
        copy_backward_ref(pos, mpEnd - 1, mpEnd);
        *pos = *pv;
        ++mpEnd;
        return;
    }
    unsigned n = (unsigned)(end - mpBegin);
    unsigned newCap = (n > 0) ? n * 2 : 1;
    RefPair8* newBegin = newCap ?
        (RefPair8*)EASTL_allocator_allocate(newCap * sizeof(RefPair8), "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    RefPair8* oldBegin = mpBegin;
    RefPair8* newPos = CopyPairs(oldBegin, pos, newBegin);
    ReleasePairs(oldBegin, pos, newBegin);
    if (newPos) {
        newPos->value = v->value;
        RefCounted* r = v->p;
        newPos->p = r;
        if (r)
            _InterlockedIncrement((volatile long*)&r->mnRefCount);
    }
    RefPair8* oldEnd = mpEnd;
    RefPair8* newEnd = CopyPairs(pos, oldEnd, newPos + 1);
    ReleasePairs(pos, oldEnd, newPos + 1);
    if (mpBegin)
        EASTL_allocator_deallocate(mpBegin);
    mpBegin = newBegin;
    mpEnd = newEnd;
    mpCapacity = newBegin + newCap;
}

// @ 0x00741a40
bool cMI_Construct::ConstructFromArenaResource(ResBase* p)
{
    ResBase* old = mResource;
    if (p != old) {
        if (p)
            p->v0();
        mResource = p;
        if (old)
            old->v1();
    }
    AddGeometryFromArena(p);
    if (mBegin8 == mEndc)
        return false;
    Sub3c0(p);
    return true;
}

// @ 0x00741aa0
RefPair8* Vec8::insert(RefPair8* pos, const RefPair8* v)
{
    RefPair8* p = mpEnd;
    int idx = (int)(pos - mpBegin);
    if (pos == p && p != mpCapacity) {
        mpEnd = p + 1;
        if (p != 0) {
            p->value = v->value;
            RefCounted* r = v->p;
            p->p = r;
            if (r) {
                _InterlockedIncrement((volatile long*)&r->mnRefCount);
            }
        }
    } else {
        DoInsertValue(pos, v);
    }
    return mpBegin + idx;
}

// @ 0x00742b30
void cMI::Sub2b30(Src* src)
{
    SetRC(AT(RC_s0074_2b30*, 0xc4), (RC_s0074_2b30*)src);
    AT(int, 0xb4) = src->i128;
    AT(int, 0xb8) = src->i12c;
    AT(int, 0xbc) = src->i130;
    AT(int, 0xa8) = src->i11c;
    AT(int, 0xac) = src->i120;
    AT(int, 0xb0) = src->i124;
    AT(float, 0xc0) = src->f134;
    Obj138* o = src->o138;
    if (o) {
        SetRC(AT(ObjEC*, 0xec), (ObjEC*)o->Get());
        AT(ObjEC*, 0xec)->Apply((char*)this + 0x30);
    }
    ((RefVec*)((char*)this + 0x44))->Assign(&src->rv_f4);
    if (src->v18 != src->v1c) {
        ((VecInt*)((char*)this + 8))->insert_range(AT(int*, 8), src->v18, src->v1c, src);
        ((VecInt*)((char*)this + 0x30))->insert_range(AT(int*, 0x30), src->vb8, src->vbc, src);
    }
    if (src->ve0 != src->ve4)
        ((VecInt2*)((char*)this + 0x1c))->insert_range(AT(int*, 0x1c), src->ve0, src->ve4, src);
    if (src->p13c)
        Fn7403c0(src->p13c);
}

// @ 0x00742ca0
__declspec(noinline) RefPair8_s0074_2b30* Map8::MapInsert(RefPair8_s0074_2b30* pos, RefPair8_s0074_2b30* value)
{
    RefPair8_s0074_2b30* end = mpEnd;
    RefPair8_s0074_2b30* r;
    if (pos != end && value->value < pos->value)
        r = LowerBoundB41ea0(mpBegin, pos, value, flag);
    else
        r = LowerBoundB41ea0(pos, end, value, flag);
    if (r == end || value->value < r->value)
        r = insert(r, value);
    return r;
}

// @ 0x00742cf0
void cMI::SetAnimationResource(RC_s0074_2b30* p)
{
    SetRC(AT(RC_s0074_2b30*, 0x98), p);
    if (!(AT(uint32_t, 8) & 1)) {
        AddAnimationsFromArena(p, 0, 0, 0);
        return;
    }
    E8 e = { 0xff, 0, 0, 0, 0, 0 };
    ((VecE8*)((char*)this + 0x14))->push(e);
}

// @ 0x00742db0
void cMI::ConstructFromGameModelResource(char* src)
{
    SetRC(AT(RC_s0074_2b30*, 0x98), (RC_s0074_2b30*)src);
    int* mb = *(int**)(src + 0x108);
    int* me = *(int**)(src + 0x10c);
    E8 e;
    uint32_t flags;
    if (mb != me && !((flags = AT(uint32_t, 8)) & 1)) {
        int sum = 0;
        if ((uint32_t)(((char*)*(int**)(src + 0x10c) - (char*)*(int**)(src + 0x108)) / 0x7c) > 1)
            AT(uint32_t, 8) = flags | 2;
        int n = (int)(((char*)*(int**)(src + 0x10c) - (char*)*(int**)(src + 0x108)) / 0x7c);
        for (int off = 0; n > 0; n--, off += 0x7c) {
            char* m = (char*)*(int**)(src + 0x108) + off;
            RC_s0074_2b30* arena = *(RC_s0074_2b30**)(m + 0x74);
            if (!arena) {
                e.a = 0xff;
                e.b = *(uint8_t*)(m + 0x70);
                e.c = (uint16_t)sum;
                e.d = 0; e.e = 0; e.f = 0;
                ((VecE8*)((char*)this + 0x14))->push(e);
            } else {
                AddAnimationsFromArena(arena, *(int*)(m + 0x78), (uint16_t*)m, (uint16_t*)(m + 0x38));
            }
            sum += *(char*)(AT(char*, 0x18) - 7);
        }
        return;
    }
    e.a = 0xff; e.b = 0; e.c = 0; e.d = 0; e.e = 0; e.f = 0;
    ((VecE8*)((char*)this + 0x14))->push(e);
}

// @ 0x00742f60
AR* Map8::GetOrAdd(const int* key)
{
    RefPair8_s0074_2b30* r = LowerBound42dd00(mpBegin, mpEnd, key, flag);
    if (r == mpEnd || *key < r->value) {
        AR def;
        RefPair8_s0074_2b30 tmp(*key, def);
        r = MapInsert(r, &tmp);
    }
    return &r->second;
}

// @ 0x00743030
int SP::cModelInstance::GetBoneParents(int * out)
{
    MatEntry** mats = AT(MatEntry**, 0x28);
    if (mats != AT(MatEntry**, 0x2c)) {
        MatEntry* m = mats[2];
        if (m && m->info) {
            BoneInfo* info = m->info;
            FixedVec64 stack(1, -1);
            int cur = -1;
            for (int i = 0; i < info->count; i++) {
                out[i] = cur;
                switch (info->flags[i] & 3) {
                case 0:
                    cur = i;
                    break;
                case 1:
                    cur = stack.mpEnd[-1];
                    stack.mpEnd -= 1;
                    break;
                case 2:
                    stack.push_back(cur);
                    cur = i;
                    break;
                }
            }
            return info->count;
        }
    }
    return 0;
}

// @ 0x00743150
void cMI2::Sub3150(int tag, RefCounted_s0074_2b30* mat)
{
    if (AT(int, 0x30) == AT(int, 0x34))
        return;
    if (AT(int, 0x44) == AT(int, 0x48))
        ((RefVecMat*)((char*)this + 0x44))->resize((AT(int, 0x34) - AT(int, 0x30)) >> 2);
    int n = (AT(int, 0x34) - AT(int, 0x30)) >> 2;
    for (int i = 0; i < n; i++) {
        ES* es = (*(Item2**)(AT(int, 0x30) + i * 4))->es;
        if (es && (es->flags & 8)) {
            int* d = es->D3D9GetShaderData(0x20f);
            if (d && *d == tag)
                AssignAR(*(AR*)(AT(int, 0x44) + i * 4), mat);
        }
    }
    AssignAR(*((Map8*)((char*)this + 0x58))->GetOrAdd(&tag), mat);
}

// @ 0x00743270
bool cMI3::Sub3270(Xf_s0074_2b30* a2, RefVecL* out)
{
    MeshVec_s0074_2b30 meshes;
    GetMeshes(&meshes);
    if (meshes.mpBegin == meshes.mpEnd)
        return false;
    uint32_t buf[0x2ffc / 4];
    int bones = AT(BoneProv*, 0xf0)->GetBoneTransforms(buf);
    int n = (int)(meshes.mpEnd - meshes.mpBegin);
    for (int i = 0; i < n; i++) {
        Ref obj(new ("Graphics", 0, 0, 0, 0) Obj58);
        if (!bones || !SkinMesh(buf, (MeshSrc*)meshes.mpBegin[i].p, (Obj58*)obj.p)) {
            Obj58* o = (Obj58*)obj.p;
            MeshSrc* mesh = (MeshSrc*)meshes.mpBegin[i].p;
            o->v8 = mesh->v8;
            o->v1c = mesh->v1c;
            o->v30 = mesh->v30;
            o->v44 = mesh->v44;
        }
        Fn734d00(a2, (Obj58*)obj.p);
        out->push_back(obj);
    }
    return true;
}

// @ 0x007434b0
bool cMI3::Sub34b0(float* out)
{
    Obj90* o = AT(Obj90*, 0xf0);
    if (o->w90 == AT(int, 0xf8) && o->w94 == AT(int, 0xfc)) {
        if (out) {
            ((uint32_t*)out)[3] = AT(uint32_t, 0xe0); ((uint32_t*)out)[4] = AT(uint32_t, 0xe4); ((uint32_t*)out)[5] = AT(uint32_t, 0xe8);
            ((uint32_t*)out)[0] = AT(uint32_t, 0xd4); ((uint32_t*)out)[1] = AT(uint32_t, 0xd8); ((uint32_t*)out)[2] = AT(uint32_t, 0xdc);
        }
        return true;
    }
    AT(int, 0xf8) = o->w90;
    AT(int, 0xfc) = o->w94;
    RefVecL meshes;
    Xf_s0074_2b30 xf;
    Sub3270(&xf, &meshes);
    AT(V3_s0074_2b30, 0xd4) = V3_s0074_2b30(kFltMax);
    AT(V3_s0074_2b30, 0xe0) = V3_s0074_2b30(kNegFltMax);
    int n = (int)(meshes.mpEnd - meshes.mpBegin);
    for (int i = 0; i < n; i++)
        AccumBounds(meshes.mpBegin[i].p, &AT(V3_s0074_2b30, 0xd4));
    if (out) {
        ((uint32_t*)out)[3] = AT(uint32_t, 0xe0); ((uint32_t*)out)[4] = AT(uint32_t, 0xe4); ((uint32_t*)out)[5] = AT(uint32_t, 0xe8);
        ((uint32_t*)out)[0] = AT(uint32_t, 0xd4); ((uint32_t*)out)[1] = AT(uint32_t, 0xd8); ((uint32_t*)out)[2] = AT(uint32_t, 0xdc);
    }
    if (meshes.mpBegin == meshes.mpEnd)
        return false;
    DynArr* arr = new ("Graphics", 0, 0, 0, 0) DynArr;
    KD kd;
    kd.arr[0].a = 0;
    kd.arr[0].b = 1;
    int ok = MakeKDTree(&meshes, &AT(float, 0xa8), arr, 0x10, &kd);
    V3_s0074_2b30 neg(-AT(float, 0xa8), -AT(float, 0xac), -AT(float, 0xb0));
    const float& zz = MaxRef_s0074_2b30(neg.z, AT(float, 0xbc));
    const float& yy = MaxRef_s0074_2b30(neg.y, AT(float, 0xb8));
    const float& xx = MaxRef_s0074_2b30(neg.x, AT(float, 0xb4));
    AT(float, 0xc0) = sqrtf(xx * xx + yy * yy + zz * zz);
    if (ok) {
        SetRC(AT(RC_s0074_2b30*, 0xcc), (RC_s0074_2b30*)0);
        KDObj* ko = new ("Graphics", 0, 0, 0, 0) KDObj(&kd, 0);
        SetRC(AT(RC_s0074_2b30*, 0xcc), (RC_s0074_2b30*)ko);
        ((ArrHolder*)this)->SetArray(arr);
        return true;
    }
    if (arr) {
        if (arr->a && ((int*)arr->a)[-1])
            EASTL_allocator_deallocate((void*)arr->a);
        EASTL_allocator_deallocate(arr);
    }
    return false;
}
