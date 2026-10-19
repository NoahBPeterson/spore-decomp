// Slice s0073a110 — graphics/model helpers (SP::cModelInstance and Simulator ability classes).
//
// Optimized /O2 module (no frame pointer).  Retail layout differs from the 2008 dev PDB and the
// 2017 ModAPI, so member offsets below are placed at the offsets observed in the disassembly; gaps
// are pad.  Flags: /O2 /MD /Gy /EHsc /TP /GS- (no stack cookie in these small functions).

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef short int16_t;

#include <intrin.h>

// ---------------------------------------------------------------------------
// Shared refcounted object: vtable at +0, refcount at +4.
// ---------------------------------------------------------------------------
class RefObj {
public:
    virtual void vfunc0(int) = 0;   // slot 0
    virtual void vfunc1() = 0;      // slot 1
    int mnRefCount;                 // +4
};

struct RefPtr {
    RefObj* mpObj;                  // +0
    // @ 0x0073A820
    void Release();
};

void RefPtr::Release()
{
    RefObj* p = mpObj;
    if (p != 0) {
        int n = (*(volatile int*)&p->mnRefCount += -1);
        if (n == 0) {
            (*(volatile int*)&p->mnRefCount) = 1;
            _ReadWriteBarrier();
            p->vfunc0(1);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x0073A800 — set two flag bits (bit0 from arg1, bit1 from arg2) on a +8 dword.
// ---------------------------------------------------------------------------
struct FlagObj {
    char pad[8];
    uint32_t mFlags;                // +8
    void SetFlags(bool a, bool b);
};

void FlagObj::SetFlags(bool a, bool b)
{
    if (a)
        mFlags |= 1;
    if (b)
        mFlags |= 2;
}

// ---------------------------------------------------------------------------
// @ 0x0073A7A0 — copy a 0x24-byte matrix block to *out, then return true.
// ---------------------------------------------------------------------------
struct Mat24 { int d[9]; };

struct MatOwner {
    char pad0[0x14];
    Mat24 mMat;                     // +0x14
    bool GetMat(Mat24* out);
};

bool MatOwner::GetMat(Mat24* out)
{
    for (int i = 0; i < 9; ++i)
        out->d[i] = 0;
    for (int i = 0; i < 9; ++i)
        out->d[i] = mMat.d[i];
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x0073A850 — scale the upper-left 3x3 of a packed 3x3 source by src->scale
// into a padded 4x4 destination and copy the translation.
// ---------------------------------------------------------------------------
struct Mat43In {
    int f0;             // +0
    float tx, ty, tz;   // +4
    float scale;        // +0x10
    float r[3][3];      // +0x14 (packed, stride 3)
    // +0x38 ...
};

struct Mat44Out {
    float r[3][4];      // +0..+0x2c (padded, stride 4)
    float tx, ty, tz;   // +0x30
};

void ScaleMat(const Mat43In* src, Mat44Out* dst)
{
    const float s = src->scale;
    dst->r[0][0] = src->r[0][0] * s;
    dst->r[0][1] = src->r[0][1] * s;
    dst->r[0][2] = src->r[0][2] * s;
    dst->r[1][0] = src->r[1][0] * s;
    dst->r[1][1] = src->r[1][1] * s;
    dst->r[1][2] = src->r[1][2] * s;
    dst->r[2][0] = src->r[2][0] * s;
    dst->r[2][1] = src->r[2][1] * s;
    dst->r[2][2] = src->r[2][2] * s;
    dst->tx = src->tx;
    dst->ty = src->ty;
    dst->tz = src->tz;
}

// ---------------------------------------------------------------------------
// SP::cModelInstance — retail member offsets observed in the disassembly.
// ---------------------------------------------------------------------------
namespace SP {

// 8-byte animation/bone group record (cAnimGroupInfo).
struct cAnimGroupInfo {
    char  mBindingIdx;      // +0
    char  mBoneCount;       // +1
    short mBoneOffset;      // +2
    char  mAnimCount;       // +4
    char  mAnimFirstDeform; // +5
    short mAnimOffset;      // +6
};

struct cAnimDef { char pad0[8]; int mId; char pad0c[0x14]; float mLength; };   // KeyframeAnimation (id +8, length +0x20)
struct cIdObj { char pad0[0x10]; int mId; };           // +0x10 id
struct cBindInfo {
    char pad0[0xc];
    cIdObj* m0c;                                       // +0x0c
    cIdObj* m10;                                       // +0x10
    char pad14[4];
    int m18;                                           // +0x18
};
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
struct cBinding {                                      // 12-byte binding record
    cBlender* mBlender;                                // +0
    bool mActive;                                      // +4
    bool mLoop;                                        // +5
    short pad6;
    cBindInfo* mInfo;                                  // +8
};
struct cMaterial {                                     // 0xc4-byte record, same prefix as cBinding
    cBlender* mBlender;
    bool mActive;
    bool mLoop;
    short pad6;
    cBindInfo* mInfo;
    char pad0c[0xc4 - 0xc];
};
struct cCtrlEntry { int mKey; cAnimDef* mDef; };       // 8 bytes

struct AnimGroupVec {
    cAnimGroupInfo* mpBegin;
    cAnimGroupInfo* mpEnd;
    cAnimGroupInfo* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
    cAnimGroupInfo& operator[](int i) { return mpBegin[i]; }
};

class cModelInstance {
public:
    char pad0[8];                   // +0x00
    unsigned mFlags8;               // +0x08 (bit 0x20: multi-blender mode)
    int  mFieldC;                   // +0x0c
    int  mField10;                  // +0x10
    AnimGroupVec mAnimGroups;       // +0x14 (begin/end/cap; size() and operator[] stay inline calls)
    char pad20[0x28 - 0x20];
    cMaterial* mMaterials;          // +0x28
    cMaterial* mMaterialsEnd;       // +0x2c
    char pad30[0x3c - 0x30];
    cBinding* mBindABegin;          // +0x3c
    cBinding* mBindAEnd;            // +0x40
    char pad44[0x50 - 0x44];
    cBinding* mBindCBegin;          // +0x50
    cBinding* mBindCEnd;            // +0x54
    char pad58[0x78 - 0x58];
    int* mControllers;              // +0x78
    char pad7c[0x154 - 0x7c];
public:
    // @ 0x0073ABB0
    int GetAnimationMoveToTimes(int animID, int* dst, char bEnd);
    bool SetActive(int key, int groupIdx, bool animating, float t, bool loop);
    bool AdvanceBinding(cBinding* b, float dt);
    bool IsValidGroup(int i) {
        return i >= 0 && i < mAnimGroups.size();
    }
};

int cModelInstance::GetAnimationMoveToTimes(int animID, int* dst, char bEnd)
{
    if (!IsValidGroup(animID))
        return 0;
    cAnimGroupInfo* e = &mAnimGroups[animID];
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

} // namespace SP

// ---------------------------------------------------------------------------
// SP::cModelInstance::SetActive: activate / deactivate every binding whose controller matches `key`.
namespace SP {
static __forceinline void ApplyBinding(cModelInstance* mi, cBinding* b, cAnimDef* target, bool animating, float t, bool loop)
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
}

// @ 0x0073AC20
bool cModelInstance::SetActive(int key, int groupIdx, bool animating, float t, bool loop)
{
    if (!IsValidGroup(groupIdx))
        return false;
    cAnimGroupInfo* g = &mAnimGroups[groupIdx];
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
            cBinding* b = &mBindABegin[k];
            b->mLoop = loop;
            if (b->mInfo->m10->mId == target->mId) {
                ApplyBinding(this, b, target, animating, t, loop);
                result = true;
            }
        }
        for (int j = bidx; j < bend; ++j) {
            cBinding* b = (cBinding*)&mMaterials[j];
            b->mLoop = loop;
            if (b->mInfo->m0c->mId == target->mId) {
                ApplyBinding(this, b, target, animating, t, loop);
                result = true;
            }
        }
        const int nC = (int)(mBindCEnd - mBindCBegin);
        for (int k = 0; k < nC; ++k) {
            cBinding* b = &mBindCBegin[k];
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
} // namespace SP

// ---------------------------------------------------------------------------
// The remaining functions in this slice belong to other classes in the same
// region (Simulator ability objects and mesh helpers).  They are reconstructed
// below / summarised; see partial.txt and nonmatching.txt for status.
// ---------------------------------------------------------------------------

// @ 0x0073A110 — large model update pass (927 bytes).
void ModelUpdatePass(void* self)
{
    (void)self;
}

// @ 0x0073A4B0 — eastl::vector<SP::cQuadric,sp_vector_allocator>::resize (556 bytes).
void QuadricVectorResize(void* self, uint32_t n)
{
    (void)self; (void)n;
}

// @ 0x0073A6E0 — ability-object constructor (130 bytes).
struct __declspec(align(16)) Vec4a { float x, y, z, w; };

class __declspec(align(16)) BigObj {
public:
    int f00, f04, f08, f0c;     // +0x00
    int f10;                    // +0x10
    int f14;                    // +0x14
    int f18;                    // +0x18
    int f1c;                    // +0x1c
    Vec4a v20;                  // +0x20
    Vec4a v30;                  // +0x30
    char pad40[0x10];           // +0x40
    int f50;                    // +0x50
    char pad54[0x7c];           // +0x54
    int fd0;                    // +0xd0
    char padd4[0x8];            // +0xd4
    int fdc;                    // +0xdc
    char pade0[0x8];            // +0xe0
    int fe8;                    // +0xe8
    char padec[0x4];            // +0xec
    int ff0;                    // +0xf0
    char padf4[0x4];            // +0xf4
    int ff8;                    // +0xf8
    float ffc;                  // +0xfc
    int f100;                   // +0x100
    int f104;                   // +0x104
    char f108;                  // +0x108
    void Ctor(int a, int b, int c, Vec4a* p4, Vec4a* p5);
};

// @ 0x0073a6e0
void BigObj::Ctor(int a, int b, int c, Vec4a* p4, Vec4a* p5)
{
    f00 = a; f04 = b; f08 = c; f0c = 0;
    fd0 = 0; fdc = 0; f50 = 0;
    ff0 = 0; ff8 = 0; f14 = 0; fe8 = 0;
    v20 = *p4;
    v30 = *p5;
    int t = f1c;
    ffc = 1.0f;
    f100 = 0;
    f18 = t;
    f104 = 0;
    f108 = 0;
}

// @ 0x0073A900 — release a bound render resource (203 bytes).
void ReleaseBoundResource(void* self, void* p)
{
    (void)self; (void)p;
}

// @ 0x0073A9E0 — destructor that resets two vtables and releases a ref (108 bytes).
void AbilityDtorBase(void* self)
{
    (void)self;
}

// Ability object constructor setting two vtables (81 bytes).
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

// @ 0x0073AA70
AbilityB::AbilityB(AbHeld* h, int v, int a, int b) : AbilityA(h, v), mB18(a), mB1c(b)
{
}

// @ 0x0073AAE0 — ability-object destructor (95 bytes).
void AbilityDtorB(void* self)
{
    (void)self;
}

// @ 0x0073AB40 — assign a refcounted controller field and refresh two words (96 bytes).
struct CtrlObj {
    void** vftable;                 // +0
    int mnRefCount;                 // +4
    char pad8[0x90 - 8];            // +8 .. +0x90
    long long mCounter;             // +0x90
};

struct CtrlHolder {
    char pad0[0xf0];
    CtrlObj* mCtrl;                 // +0xf0
    long long mCounter2;            // +0xf8
    void SetController(CtrlObj* p);
};

void CtrlHolder::SetController(CtrlObj* p)
{
    CtrlObj* old = mCtrl;
    if (p != old) {
        if (p != 0)
            ++p->mnRefCount;
        mCtrl = p;
        if (old != 0) {
            int n = (*(volatile int*)&old->mnRefCount += -1);
            if (n == 0) {
                (*(volatile int*)&old->mnRefCount) = 1;
                _ReadWriteBarrier();
                ((void(__thiscall*)(CtrlObj*, int))old->vftable[0])(old, 1);
            }
        }
    }
    mCounter2 = p->mCounter - 1;
}

// Advance one binding's blender by dt (clamped at the animation end for looping bindings).
namespace SP {
// @ 0x0073AF20
bool cModelInstance::AdvanceBinding(cBinding* b, float dt)
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
} // namespace SP
