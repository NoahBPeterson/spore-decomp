// Slice s00a6ff50 (SSE object): EA::Swarm cEffectsWorld - update/stop/LOD/ctor/dtor,
// VectorEffect allocation and the SP parameter-vector helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /fp:fast /arch:SSE
#include "types.h"

// ---------------------------------------------------------------------------
// external helpers / globals
extern "C" void  operator_delete__(void* p);                                    // 0xf47380
extern "C" void* EAAllocate(unsigned size, const char* file, int a, int b, int c, int d); // 0xf473a0
extern "C" void* __cdecl memmove_nd(void* dst, const void* src, unsigned n);    // 0x11e0744
extern "C" void  __stdcall ehvec_ctor(void* dst, void* src, unsigned size, int count, void* ctor); // 0x406540
extern "C" void* __stdcall arrElemCopy(void* dst, void* src);                   // 0xac8980

extern int  gEmptyString16;      // 0x1667bac
extern int  gGmeRefCountVtbl;    // 0x13ef094
extern int  gWorldVtblA;         // 0x1455fb8
extern int  gWorldVtblB;         // 0x1455fb4

struct M33 {
    float m[9];
    void Assign(const void* src);    // 0x41cb40
};
struct M44 {
    float m[16];
    void Ctor(const void* src);      // 0x45dca0
};
struct Vec3 { float x, y, z; };

// polymorphic element base of the vector-effect table: primary vtable at +0
struct IVEBase {
    virtual void AddRef();            // 0x00
    virtual void ReleasePrimary();    // 0x04
    virtual void v08();               // 0x08
    virtual void Stop(int code);      // 0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
};
// secondary (refcounted) base of a vector effect: vtable at +4
struct IVERef {
    virtual void Init(void* world, void* manager, int flags);   // 0x00
    virtual void Release();                                     // 0x04
    virtual void v08(); virtual void v0c();
};

struct cVisualEffect : IVEBase, IVERef {
    int   m08;        // +0x08
    int   m0c;        // +0x0c
    int   m10;        // +0x10 state
    int   m14;        // +0x14
    int   m18;        // +0x18
    int   m1c;        // +0x1c
    int   m20;        // +0x20
    int   m24;        // +0x24
    int   m28;        // +0x28
    int   mFlags;     // +0x2c
    cVisualEffect* Ctor();                          // 0xa83c00
    bool  CheckIfStopped();                         // 0xa82430
    void  SetDescription(const void* desc);         // 0xa82370
};

struct IntVec {
    int* mpBegin;
    int* mpEnd;
    int* mpCap;
    void DoInsertValue(int* pos, const int& v);     // 0x4558a0
    void CtorGrow(int count, const int* fill);      // 0x4aa350
    void Add(const int& v)
    {
        if (mpEnd < mpCap) {
            int* e = mpEnd;
            mpEnd = e + 1;
            if (e) *e = v;
        }
        else {
            DoInsertValue(mpEnd, v);
        }
    }
    void EraseAdd(int* first, int* last)
    {
        memmove_nd(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= last - first;
    }
};

struct VEVec {
    cVisualEffect** mpBegin;
    cVisualEffect** mpEnd;
    cVisualEffect** mpCap;
    void DoInsertValue(cVisualEffect** pos, cVisualEffect* const& v);   // 0xa0a360
    void Dtor();                                                      // 0xae6970
    void erase(cVisualEffect** first, cVisualEffect** last);          // 0xe25bd0
    void Add(cVisualEffect* const& v)
    {
        if (mpEnd < mpCap) {
            cVisualEffect** e = mpEnd;
            mpEnd = e + 1;
            if (e) *e = v;
        }
        else {
            DoInsertValue(mpEnd, v);
        }
    }
};

struct EString {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
};

struct GmeRefCount {
    virtual void AddRef();
    virtual void Release();
    int mnRefCount;
    GmeRefCount() : mnRefCount(0) {}
};

struct IWorldVtbl {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c(int code);
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c(void*, void*, int);
};

// a class owning a vector of 0xc-byte points (UpdateComponentLODs)
struct LODWorld {
    char pad[0x40];
    unsigned char mBase;   // +0x40
    unsigned char pad41[3];
    Vec3* mpPoints;        // +0x44
    Vec3* mpPointsEnd;     // +0x48
};
// the object whose +0x38 member is handed the six floats
struct LODComponent {
    char pad[0x38];
    void* mpRenderer;      // +0x38
};

struct cEffectsWorld : public IWorldVtbl, public GmeRefCount {
    bool   mInitialized;        // +0x0c
    unsigned char pad0d[3];
    int    m10;                 // +0x10
    void*  mManager;            // +0x14
    void*  mGlobalParams;       // +0x18
    void*  mpRenderer;          // +0x1c
    int    m20;                 // +0x20
    bool   mUpdating;           // +0x24
    unsigned char pad25[3];
    int    mState;              // +0x28
    int    m2c;                 // +0x2c
    VEVec  mVE;                 // +0x30
    int    m3c;                 // +0x3c
    int    m40;                 // +0x40
    IntVec mFree;               // +0x44
    int    m50;                 // +0x50
    int    m54;                 // +0x54
    IntVec mActive;             // +0x58
    int    m64;                 // +0x64
    int    m68;                 // +0x68
    IntVec mNew;                // +0x6c
    int    m78;                 // +0x78
    int    m7c;                 // +0x7c
    int    m80;                 // +0x80
    int    m84;                 // +0x84
    float  m88;                 // +0x88
    int    m8c;                 // +0x8c
    int    m90;                 // +0x90
    EString mDebugName;         // +0x94

    void StopStopped();                                  // 0x00a70330
    void ForEachActive(void (*fn)(cVisualEffect*, void*), void* user, int mode); // 00a70370
    cVisualEffect* NewVisualEffect();                    // 00a70bb0
    void DeactivateUnusedVisualEffects();                // 00a70a40
    void DeactivateAll();                                // 00a70af0
    bool Teardown();                                     // 00a709e0
    void SetRenderer(void* renderer);                    // 00a70da0
    static void __stdcall UpdateComponentLODs(LODWorld* self, void* h, int index);  // 00a70400
    void* CreateInternalEffect(unsigned a, unsigned b, const void* params); // 00a70ec0
    cEffectsWorld(unsigned flags, const void* params);   // 00a70780
    ~cEffectsWorld();                                    // 00a70870
};

struct ParamElem;

// SP parameter block, 0x5c bytes (copied by 00a70cc0, destroyed by 00a70730/00a70980)
struct IParamRef {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30();
    virtual void AddRefI();    // slot 13 (0x34)
    virtual void ReleaseI();   // slot 14 (0x38)
};
struct ParamElem {
    unsigned short f00;    // +0x00
    unsigned short f02;    // +0x02
    float f04;             // +0x04
    float f08;             // +0x08
    float f0c;             // +0x0c
    float f10;             // +0x10
    M33   m14;             // +0x14
    IParamRef* mp38;       // +0x38
    int   f3c;             // +0x3c
    float f40;             // +0x40
    int   f44;             // +0x44
    IntVec vec;            // +0x48
    int   f54;             // +0x54
    int   f58;             // +0x58
};

// 0x58-byte description record (00a70910)
struct Desc58 {
    unsigned short f0;     // +0x00
    unsigned short f2;     // +0x02
    float f4;              // +0x04
    float f8;              // +0x08
    float fc;              // +0x0c
    float f10;             // +0x10
    M33   m14;             // +0x14
    int   f38;             // +0x38
    int   f3c;             // +0x3c
    int   f40;             // +0x40
    int   f44;             // +0x44
    int   f48;             // +0x48
    int   f4c;             // +0x4c
    int   f50;             // +0x50
    int   f54;             // +0x54
    Desc58* Ctor();        // 00a70910
};

extern float gDescF4;      // 0x1676b2c
extern float gDescF8;      // 0x1676b30
extern float gDescFC;      // 0x1676b34
extern float gOneF;        // 0x1485720
extern M33   gDescM33;     // 0x1676bd8

// manager subscriber used by CreateInternalEffect
struct cEffectsManagerRef {
    int GetEffectIndex(unsigned a, unsigned b);   // 0xa6d7b0
};

struct EffectParams {
    EffectParams* Clone(const EffectParams* src);   // 0x00a70df0
};
struct cGlobalParams;

// defined in the x87 translation unit
cGlobalParams* CreateGlobalParams(void* mem, const void* params);   // 0x00a704b0

// ---------------------------------------------------------------------------
// @ 0x00a70330
void cEffectsWorld::StopStopped()
{
    mUpdating = true;
    int* it = mActive.mpBegin;
    if (it != mActive.mpEnd) {
        do {
            cVisualEffect* ve = mVE.mpBegin[*it];
            if (ve->m10 == 1)
                ve->Stop(1);
            ++it;
        } while (it != mActive.mpEnd);
    }
    mUpdating = false;
}

// @ 0x00a70370
void cEffectsWorld::ForEachActive(void (*fn)(cVisualEffect*, void*), void* user, int mode)
{
    int count = (int)(mActive.mpEnd - mActive.mpBegin);
    unsigned i = 0;
    if (count != 0) {
        do {
            int id = mActive.mpBegin[i];
            if (mode < 2 && ((mVE.mpBegin[id]->mFlags >> 5) & 1))
                goto next;
            if (mode < 1 && ((mVE.mpBegin[id]->mFlags >> 6) & 1))
                goto next;
            if (mode < 2 && !((mVE.mpBegin[id]->mFlags >> 9) & 1))
                goto next;
            {
                cVisualEffect* ve = mVE.mpBegin[id];
                if (ve->m20 >= 0)
                    fn(ve, user);
            }
        next:
            ++i;
        } while (i < (unsigned)count);
    }
}

// @ 0x00a70400
void __stdcall cEffectsWorld::UpdateComponentLODs(LODWorld* self, void* h, int index)
{
    if (self->mpPoints == self->mpPointsEnd)
        return;
    int i0, i1;
    if ((int)(self->mpPointsEnd - self->mpPoints) == 1) {
        i0 = 0;
        i1 = 0;
    }
    else {
        i0 = index - self->mBase;
        i1 = i0 + 1;
    }
    float pts[6];
    pts[0] = self->mpPoints[i0].x;
    pts[1] = self->mpPoints[i0].y;
    pts[2] = self->mpPoints[i0].z;
    pts[3] = self->mpPoints[i1].x;
    pts[4] = self->mpPoints[i1].y;
    pts[5] = self->mpPoints[i1].z;
    ((IWorldVtbl*)((LODComponent*)h)->mpRenderer)->v1c((void*)0x101, pts, 6);
}

// @ 0x00a70730
ParamElem* CopyRange(ParamElem* first, ParamElem* last, ParamElem* dest)
{
    if (first != last) {
        do {
            int* buf = first->vec.mpBegin;
            if (buf != 0 && *(buf - 1) != 0)
                operator_delete__(buf);
            IParamRef* r = first->mp38;
            if (r != 0)
                r->ReleaseI();
            ++first;
            ++dest;
        } while (first != last);
    }
    return dest;
}

// @ 0x00a70780
cEffectsWorld::cEffectsWorld(unsigned flags, const void* params)
{
    mInitialized = false;
    m10 = 0;
    mManager = (void*)flags;
    void* mem = EAAllocate(0x120, "Swarm", 0, 0, 0, 0);
    mGlobalParams = mem != 0 ? (void*)CreateGlobalParams(mem, params) : 0;
    mpRenderer = 0;
    m20 = 0;
    mUpdating = false;
    m2c = 0;
    mState = 1;
    mVE.mpBegin = 0;
    mVE.mpEnd = 0;
    mVE.mpCap = 0;
    mFree.mpBegin = 0;
    mFree.mpEnd = 0;
    mFree.mpCap = 0;
    mActive.mpBegin = 0;
    mActive.mpEnd = 0;
    mActive.mpCap = 0;
    mNew.mpBegin = 0;
    mNew.mpEnd = 0;
    mNew.mpCap = 0;
    m80 = 1;
    m84 = 1;
    m90 = 0;
    m88 = 1.0f;
    mDebugName.mpBegin = (char*)&gEmptyString16;
    mDebugName.mpEnd = (char*)&gEmptyString16;
    mDebugName.mpCap = (char*)&gEmptyString16 + 1;
}

// @ 0x00a70870
cEffectsWorld::~cEffectsWorld()
{
    *(int*)((char*)this + 0) = (int)&gWorldVtblA;
    *(int*)((char*)this + 4) = (int)&gWorldVtblB;
    operator_delete__(mGlobalParams);
    if ((int)(mDebugName.mpCap - mDebugName.mpBegin) > 1 && mDebugName.mpBegin)
        operator_delete__(mDebugName.mpBegin);
    {
        int* p = mNew.mpBegin;
        if (p != 0 && *(p - 1) != 0)
            operator_delete__(p);
    }
    {
        int* p = mActive.mpBegin;
        if (p != 0 && *(p - 1) != 0)
            operator_delete__(p);
    }
    {
        int* p = mFree.mpBegin;
        if (p != 0 && *(p - 1) != 0)
            operator_delete__(p);
    }
    mVE.Dtor();
    if (mpRenderer != 0)
        ((GmeRefCount*)mpRenderer)->Release();
    *(int*)((char*)this + 4) = (int)&gGmeRefCountVtbl;
}

// @ 0x00a70910
Desc58* Desc58::Ctor()
{
    f0 = 0;
    f2 = 0;
    f4 = gDescF4;
    f8 = gDescF8;
    fc = gDescFC;
    f10 = 1.0f;
    m14.Assign(&gDescM33);
    f38 = 0;
    f44 = 0;
    f48 = 0;
    f4c = 0;
    f50 = 0;
    return this;
}

// @ 0x00a70980
void __stdcall DestroyRange(ParamElem* first, ParamElem* last)
{
    for (; first < last; first += 1) {
        int* buf = first->vec.mpBegin;
        if (buf != 0 && *(buf - 1) != 0)
            operator_delete__(buf);
        IParamRef* r = first->mp38;
        if (r != 0)
            r->ReleaseI();
    }
}

// @ 0x00a709e0
bool cEffectsWorld::Teardown()
{
    if (!mInitialized)
        return true;
    v0c(5);
    mInitialized = false;
    cVisualEffect** it = mVE.mpBegin;
    if (it != mVE.mpEnd) {
        do {
            cVisualEffect* ve = *it;
            ve->Release();
            if (ve) {
                *it = 0;
                ve->ReleasePrimary();
            }
            ++it;
        } while (it != mVE.mpEnd);
    }
    mVE.erase(mVE.mpBegin, mVE.mpEnd);
    return true;
}

// @ 0x00a70a40
void cEffectsWorld::DeactivateUnusedVisualEffects()
{
    int* src = mActive.mpBegin;
    int* dst = src;
    m90 = 0;
    mUpdating = true;
    if (src != mActive.mpEnd) {
        do {
            int id = *src;
            if (mVE.mpBegin[id]->CheckIfStopped() && mVE.mpBegin[id]->m10 == 1) {
                mVE.mpBegin[id]->Release();
                mNew.Add(*src);
            }
            else {
                m90 = m90 + 1;
                *dst = *src;
                ++dst;
            }
            ++src;
        } while (src != mActive.mpEnd);
    }
    mActive.EraseAdd(dst, mActive.mpEnd);
    mUpdating = false;
}

// @ 0x00a70af0
void cEffectsWorld::DeactivateAll()
{
    cVisualEffect** it = mVE.mpBegin;
    if (it != mVE.mpEnd) {
        do {
            cVisualEffect* ve = *it;
            ve->Stop(1);
            ve->Release();
            if (ve) {
                *it = 0;
                ve->ReleasePrimary();
            }
            ++it;
        } while (it != mVE.mpEnd);
    }
    mActive.EraseAdd(mActive.mpBegin, mActive.mpEnd);
    mNew.EraseAdd(mNew.mpBegin, mNew.mpEnd);
    mVE.erase(mVE.mpBegin, mVE.mpEnd);
    mFree.EraseAdd(mFree.mpBegin, mFree.mpEnd);
}

// @ 0x00a70bb0
cVisualEffect* cEffectsWorld::NewVisualEffect()
{
    if (mNew.mpBegin != mNew.mpEnd) {
        mFree.Add(*(mNew.mpEnd - 1));
        --mNew.mpEnd;
        return mVE.mpBegin[*(mFree.mpEnd - 1)];
    }
    cVisualEffect* ve = 0;
    void* mem = EAAllocate(0x188, "Swarm/VisualEffect", 0, 0, 0, 0);
    if (mem != 0)
        ve = ((cVisualEffect*)mem)->Ctor();
    mFree.Add((int)(mVE.mpEnd - mVE.mpBegin));
    if (ve)
        ve->AddRef();
    mVE.Add(ve);
    if (ve)
        ve->ReleasePrimary();
    return ve;
}

// @ 0x00a70da0
void cEffectsWorld::SetRenderer(void* renderer)
{
    if (mpRenderer != 0)
        DeactivateAll();
    void* old = mpRenderer;
    if ((cVisualEffect*)renderer != (cVisualEffect*)old) {
        if (renderer != 0)
            ((GmeRefCount*)renderer)->AddRef();
        mpRenderer = renderer;
        if (old != 0)
            ((GmeRefCount*)old)->Release();
    }
}

// @ 0x00a70ec0
void* cEffectsWorld::CreateInternalEffect(unsigned a, unsigned b, const void* params)
{
    int index = ((cEffectsManagerRef*)mManager)->GetEffectIndex(a, b);
    if (index < 0)
        return 0;
    cVisualEffect* ve = NewVisualEffect();
    ve->Init(this, mManager, 0);
    ve->mFlags |= 0x40;
    if (params != 0) {
        EffectParams* mem = (EffectParams*)EAAllocate(0xd8, "Swarm/EffectParams", 0, 0, 0, 0);
        EffectParams* copy = 0;
        if (mem != 0)
            copy = mem->Clone((const EffectParams*)params);
        *(EffectParams**)((char*)ve + 0x17c) = copy;
    }
    ve->m20 = index;
    {
        int idx = index;
        char* desc = *(char**)(*(char**)((char*)mManager + 0x2c) + ((idx >> 24) * 4));
        ve->SetDescription(*(char**)(desc + 0x34) + (idx & 0xffffff) * 0x58);
    }
    return ve;
}
