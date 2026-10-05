// Slice s0073afb0 — SP::cModelInstance methods (2008 retail offsets).
//
// Optimized /O2 (no frame pointer).  Retail member offsets differ from the 2008 dev PDB and the
// 2017 ModAPI; offsets below are those observed in the disassembly, gaps are pad.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast.

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef short int16_t;

#include <intrin.h>

namespace SP {

// 8-byte animation/bone group record.
struct cAnimGroupInfo {
    char  mBindingIdx;      // +0
    char  mBoneCount;       // +1
    short mBoneOffset;      // +2
    char  mAnimCount;       // +4
    char  mAnimFirstDeform; // +5
    short mAnimOffset;      // +6
};

// 0xc4-byte material record (only the callback fields used here).
struct cMaterial {
    char  pad0[0xb8];
    void* f_b8;             // +0xb8
    void* f_bc;             // +0xbc
    void* f_c0;             // +0xc0
};

class cModelInstance {
public:
    char pad0[0xc];                 // +0x00
    int mFieldC;                    // +0x0c
    void* mField10;                 // +0x10
    cAnimGroupInfo* mGroupBegin;    // +0x14
    cAnimGroupInfo* mGroupEnd;      // +0x18
    char pad1c[0x28 - 0x1c];
    cMaterial* mMaterials;          // +0x28
    char pad2c[0x30 - 0x2c];
    int mField30;                   // +0x30 (address forwarded to a virtual call)
    char pad34[0x90 - 0x34];
    long long mCounter;             // +0x90
    char pad98[0xc8 - 0x98];
    unsigned short mFlags;          // +0xc8
    char padca[0xec - 0xca];
    void* mDynDraw;                 // +0xec
    char padec[0x8];
    char padf4[0x60];

public:
    // @ 0x0073B7E0
    int GetNumBones();
    // @ 0x0073B800
    void SetBoneTable(int a, void* b);
    // @ 0x0073B840
    void SetBoneCallback(int boneIndex, void* a2, void* a3, void* a4);
    // @ 0x0073B8E0
    void SetDynamicDraw(void* p, bool flag);
};

// @ 0x0073B7E0 — number of bones = last group's bone count + bone offset.
int cModelInstance::GetNumBones()
{
    if (mGroupBegin == mGroupEnd)
        return 0;
    return (int)mGroupEnd[-1].mBoneCount + (int)mGroupEnd[-1].mBoneOffset;
}

// @ 0x0073B800
void cModelInstance::SetBoneTable(int a, void* b)
{
    cAnimGroupInfo* p = mGroupBegin;
    if (p != mGroupEnd && (int)p->mBoneCount < a)
        mFieldC = (int)p->mBoneCount;
    else
        mFieldC = a;
    mField10 = b;
    mCounter += 1;
}

// @ 0x0073B840
void cModelInstance::SetBoneCallback(int boneIndex, void* a2, void* a3, void* a4)
{
    if (boneIndex == -1) {
        if (mGroupBegin == mGroupEnd)
            return;
        cAnimGroupInfo* p = mGroupBegin;
        do {
            char idx = p->mBindingIdx;
            if (idx >= 0) {
                cMaterial* m = &mMaterials[idx];
                m->f_b8 = a3;
                m->f_c0 = a4;
                m->f_bc = a2;
            }
            p = (cAnimGroupInfo*)((char*)p + 8);
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
    cMaterial* m = &mMaterials[idx];
    m->f_b8 = a3;
    m->f_c0 = a4;
    m->f_bc = a2;
}

// @ 0x0073B8E0 — set the dynamic-draw object and its flag bit.
struct DynDrawObj {
    void** vftable;                 // +0
    int mnRefCount;                 // +4
};

void cModelInstance::SetDynamicDraw(void* pv, bool flag)
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

} // namespace SP

// ---------------------------------------------------------------------------
// @ 0x0073BDC0 — release a refcounted object stored at this+0xc.
// ---------------------------------------------------------------------------
struct RefObjR {
    void** vftable;                 // +0
    int mnRefCount;                 // +4
};

struct RefHolderC {
    char pad0[0xc];
    void* mpObj;                    // +0xc
    void Release();
};

void RefHolderC::Release()
{
    RefObjR* p = (RefObjR*)mpObj;
    if (p != 0) {
        int n = (*(volatile int*)&p->mnRefCount += -1);
        if (n == 0) {
            (*(volatile int*)&p->mnRefCount) = 1;
            _ReadWriteBarrier();
            ((void(__thiscall*)(RefObjR*, int))p->vftable[0])(p, 1);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x0073BD60 — collect textures and materials into a manager.
// ---------------------------------------------------------------------------
struct Model47;                                    // fwd
extern "C" void TextureCollect(void* tex, void* a, void* b);   // 0x007140E0
extern "C" void MaterialCollect(void* mat, void* a, void* b);  // 0x00713E20

struct Model47 {
    char pad0[0x30];
    void** mTexBegin;               // +0x30
    void** mTexEnd;                 // +0x34
    char pad38[0xc];
    void** mMatBegin;               // +0x44
    void** mMatEnd;                 // +0x48
    void Collect(void* a, void* b);
};

void Model47::Collect(void* a, void* b)
{
    void** p = mMatBegin;
    while (p != mMatEnd) {
        if (*p != 0)
            TextureCollect(*p, a, b);
        ++p;
    }
    void** q = mTexBegin;
    while (q != mTexEnd) {
        MaterialCollect(*q, a, b);
        ++q;
    }
}

// ---------------------------------------------------------------------------
// Remaining slice functions: large animation drivers and helpers.
// ---------------------------------------------------------------------------
// @ 0x0073AFB0 — SP::cModelInstance::Animate (480 bytes)
void AnimateStub() {}
// @ 0x0073B190 — SP::cModelInstance::MoveToTime (927 bytes)
void MoveToTimeStub() {}
// @ 0x0073B530 — SP::cModelInstance::SetWeight (404 bytes)
void SetWeightStub() {}
// @ 0x0073B6D0 — SP::cModelInstance::GetAnimationRange (265 bytes)
void GetAnimationRangeStub() {}
// @ 0x0073B980 — query a packed-file allocator (195 bytes)
void QueryAllocatorStub() {}
// @ 0x0073BA50 — reseat a resource (85 bytes)
void ReseatStub() {}
// @ 0x0073BAB0 — notify binding lists (142 bytes)
void NotifyStub() {}
// @ 0x0073BB40 — animation driver (529 bytes)
void AnimDriverStub() {}
// @ 0x0073BDF0 — bone lookup (277 bytes)
void BoneLookupStub() {}
