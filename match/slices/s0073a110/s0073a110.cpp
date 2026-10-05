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

class cModelInstance {
public:
    char pad0[0xc];                 // +0x00
    int  mFieldC;                   // +0x0c
    int  mField10;                  // +0x10
    cAnimGroupInfo* mAnimGroupBegin;// +0x14
    cAnimGroupInfo* mAnimGroupEnd;  // +0x18
    char pad1c[0x78 - 0x1c];
    int* mControllers;              // +0x78
    char pad7c[0x154 - 0x7c];
public:
    // @ 0x0073ABB0
    int GetAnimationMoveToTimes(int animID, int* dst, char bEnd);
    // @ 0x0073AC20
    void SetActive(int index, int value);
};

int cModelInstance::GetAnimationMoveToTimes(int animID, int* dst, char bEnd)
{
    if (animID < 0)
        return 0;
    const int nGroups = (int)((char*)mAnimGroupEnd - (char*)mAnimGroupBegin) >> 3;
    if (animID >= nGroups)
        return 0;
    cAnimGroupInfo* e = &mAnimGroupBegin[animID];
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
// @ 0x0073AC20 — SP::cModelInstance::SetActive (large; behavior reconstructed below).
// ---------------------------------------------------------------------------
namespace SP {
void cModelInstance::SetActive(int index, int value)
{
    (void)index; (void)value;
    // Large activate/animate dispatch; body summarised (see partial.txt).
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

// @ 0x0073AA70 — ability-object constructor setting two vtables (81 bytes).
void AbilityCtorB(void* self, void* a, void* b, void* c, void* d)
{
    (void)self; (void)a; (void)b; (void)c; (void)d;
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

// @ 0x0073AF20 — small model helper (134 bytes).
void ModelHelper(void* self)
{
    (void)self;
}
