// Slice s00f347e0: EASTL vector<cSPTransform> and vector<V4> out-of-line template members
// (erase / insert / push_back) plus three members of a planet-layout class.
// Built /O2 (no frame pointer, sar/shl strength-reduced divisions, SSE element copies).
// All the vector ops and the class ops are __thiscall members (ecx = this).
#include "types.h"
#include <new>

typedef unsigned int uint;
void* EAAllocate(unsigned int bytes, const char* name, int a, int b, int c, int d);  // 0x00f473a0
void  EAFree(void* p);                                                                 // 0x00f47380
void* operator new(unsigned int n);
void  operator delete(void* p);

// ---------------------------------------------------------------------------
// 0x38-byte element: cSPTransform. Real copy ctor (0x00538000), trivial dtor.
// ---------------------------------------------------------------------------
struct cSPTransform {
    unsigned short mFlags;          // +0x00
    unsigned short mModCount;       // +0x02
    float mTranslation[3];          // +0x04
    float mScale;                   // +0x10
    float mRotation[9];             // +0x14
    cSPTransform();
    cSPTransform(const cSPTransform& other) throw();      // 0x00538000
    cSPTransform& operator=(const cSPTransform& other);   // 0x00537dc0
    cSPTransform* Assign(const void* src);                // 0x00537dc0
};

cSPTransform* CopyT38(const cSPTransform* first, const cSPTransform* last, cSPTransform* dest);   // 0x005f4d00
cSPTransform* CopyBackT38(cSPTransform* first, cSPTransform* last, cSPTransform* dest);           // 0x00f33a80
cSPTransform* MoveT38(cSPTransform* first, cSPTransform* last, cSPTransform* dest);               // 0x00f337a0
cSPTransform* MoveT38b(cSPTransform* first, cSPTransform* last, cSPTransform* dest);              // 0x00f338c0
void MoveRangeT38(cSPTransform* first, cSPTransform* last, cSPTransform* dest);                   // 0x00f33f60

// ---------------------------------------------------------------------------
// 0x10-byte refcounted element (a transform-ops slot): { obj, a, b, scale }.
// ---------------------------------------------------------------------------
struct IV4Ref {
    virtual int AddRef();
    virtual int Release();
};
struct V4 {
    IV4Ref* mpObj;                  // +0x00
    unsigned int mA;                // +0x04
    unsigned int mB;                // +0x08
    float mScale;                   // +0x0c
    void Assign(const V4* o) throw();       // V4::assign 0x00f00b00
};
// Copy-construct a V4 into raw storage the way the retail build does it: plain
// field stores plus an AddRef vtable call, with no exception frame.
inline V4* V4ConstructAt(V4* dst, const V4* src)
{
    if (dst) {
        dst->mpObj = src->mpObj;
        if (dst->mpObj)
            dst->mpObj->AddRef();
        dst->mA = src->mA;
        dst->mB = src->mB;
        dst->mScale = src->mScale;
    }
    return dst;
}
// Destroy one element in place: release the referenced object if any.
inline void V4DestroyOne(V4* p)
{
    if (p->mpObj)
        p->mpObj->Release();
}

V4* CopyT10(V4* first, V4* last, V4* dest) throw();          // 0x00f33a10
V4* CopyBackT10(V4* first, V4* last, V4* dest) throw();      // 0x00f33ac0
V4* RelocateT10(V4* first, V4* last, V4* dest) throw();      // 0x00f32ac0
void DestroyT10(V4* first, V4* last) throw();                // 0x00f32b10

// ---------------------------------------------------------------------------
// vector<cSPTransform, sp_vector_allocator>  (stamped vecT38).
// ---------------------------------------------------------------------------
struct vecT38 {
    cSPTransform* mpBegin;          // +0x00
    cSPTransform* mpEnd;            // +0x04
    cSPTransform* mpCapacity;       // +0x08
    void* mAllocator;               // +0x0c
    cSPTransform* DoAllocate(uint n) { return n ? (cSPTransform*)EAAllocate(n * 0x38, "Simulator", 0, 0, 0x13ebb38, 0xd1) : 0; }
    void DoFree(cSPTransform* p) { if (p && ((int*)p)[-1]) EAFree(p); }
    cSPTransform* erase(cSPTransform* first, cSPTransform* last);   // 0x00f34cb0
    void insert(cSPTransform* position, const cSPTransform* value); // 0x00f34dd0
    void insert(cSPTransform* position, uint n, const cSPTransform* value); // 0x00f350c0
};

// @ 0x00f34cb0
cSPTransform* vecT38::erase(cSPTransform* first, cSPTransform* last)
{
    cSPTransform* newEnd = CopyT38(last, mpEnd, first);
    mpEnd -= (last - first);
    (void)newEnd;
    return first;
}

// @ 0x00f34dd0
void vecT38::insert(cSPTransform* position, const cSPTransform* value)
{
    if (mpEnd != mpCapacity) {
        const cSPTransform* v = value;
        if (value >= position && value < mpEnd)
            v = value + 1;
        if (mpEnd)
            new(mpEnd) cSPTransform(*(mpEnd - 1));
        CopyBackT38(position, mpEnd - 1, mpEnd);
        position->Assign(v);
        mpEnd += 1;
        return;
    }
    uint oldSize = (uint)(mpEnd - mpBegin);
    uint newSize = oldSize ? oldSize * 2 : 1;
    cSPTransform* pNewData = DoAllocate(newSize);
    cSPTransform* p = CopyT38(mpBegin, position, pNewData);
    if (p) new(p) cSPTransform(*value);
    cSPTransform* pNewEnd = CopyT38(position, mpEnd, p + 1);
    DoFree(mpBegin);
    mpBegin = pNewData;
    mpEnd = pNewEnd;
    mpCapacity = pNewData + newSize;
}

// @ 0x00f350c0
void vecT38::insert(cSPTransform* position, uint n, const cSPTransform* value)
{
    uint cap = (uint)(mpCapacity - mpEnd);
    if (n > cap) {
        uint oldSize = (uint)(mpEnd - mpBegin);
        uint newSize = oldSize * 2;
        if (newSize == 0) newSize = 1;
        if (newSize < oldSize + n) newSize = oldSize + n;
        cSPTransform* pNewData = DoAllocate(newSize);
        cSPTransform* p = CopyT38(mpBegin, position, pNewData);
        MoveT38(p, p + n, position);
        cSPTransform* pMid = CopyT38(value, value + 1, p + n);
        cSPTransform* pNewEnd = CopyT38(position, mpEnd, pMid);
        DoFree(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + newSize;
        return;
    }
    if (n == 0)
        return;
    cSPTransform tmp(*value);
    uint elemsAfterPos = (uint)(mpEnd - position);
    if (n < elemsAfterPos) {
        MoveT38b(mpEnd - n, mpEnd, mpEnd);
        mpEnd += n;
        MoveRangeT38(position, mpEnd - 2 * n, mpEnd - n);
        tmp = *value;
        MoveRangeT38(&tmp, &tmp + 1, position);
    } else {
        MoveRangeT38(position, mpEnd, mpEnd);
        mpEnd += n;
        MoveRangeT38(&tmp, &tmp + 1, position + elemsAfterPos);
    }
}

// ---------------------------------------------------------------------------
// vector<V4, sp_vector_allocator>  (stamped vecV4).
// ---------------------------------------------------------------------------
struct vecV4 {
    V4* mpBegin;                    // +0x00
    V4* mpEnd;                      // +0x04
    V4* mpCapacity;                 // +0x08
    void* mAllocator;               // +0x0c
    V4* DoAllocate(uint n) { return n ? (V4*)EAAllocate(n * 0x10, "Simulator", 0, 0, 0x13ebb38, 0xd1) : 0; }
    void DoFree(V4* p) { if (p && ((int*)p)[-1]) EAFree(p); }
    V4* erase(V4* position);                    // 0x00f34d00
    V4* erase(V4* first, V4* last);             // 0x00f34ef0
    void insert(V4* position, const V4* value); // 0x00f34f50
    void push_back(const V4* value);            // 0x00f35560
};

// @ 0x00f34d00
V4* vecV4::erase(V4* position)
{
    if (position + 1 < mpEnd)
        CopyT10(position + 1, mpEnd, position);
    mpEnd -= 1;
    V4DestroyOne(mpEnd);
    return position;
}

// @ 0x00f34ef0
V4* vecV4::erase(V4* first, V4* last)
{
    V4* newEnd = CopyT10(last, mpEnd, first);
    V4* end = mpEnd;
    V4* p = newEnd;
    while (p < end) {
        V4DestroyOne(p);
        ++p;
    }
    mpEnd -= (last - first);
    return newEnd;
}

// @ 0x00f34f50
void vecV4::insert(V4* position, const V4* value)
{
    if (mpEnd != mpCapacity) {
        const V4* v = value;
        if (value >= position && value < mpEnd)
            v = value + 1;
        if (mpEnd)
            V4ConstructAt(mpEnd, mpEnd - 1);
        CopyBackT10(position, mpEnd - 1, mpEnd);
        position->Assign(v);
        mpEnd += 1;
        return;
    }
    uint oldSize = (uint)(mpEnd - mpBegin);
    uint newSize = oldSize ? oldSize * 2 : 1;
    V4* pNewData = DoAllocate(newSize);
    V4* p = RelocateT10(mpBegin, position, pNewData);
    V4* pMid = V4ConstructAt(p, value);
    V4* pNewEnd = RelocateT10(position, mpEnd, pMid + 1);
    DestroyT10(position, mpEnd);
    DoFree(mpBegin);
    mpBegin = pNewData;
    mpEnd = pNewEnd;
    mpCapacity = pNewData + newSize;
}

// @ 0x00f35560
void vecV4::push_back(const V4* value)
{
    if (mpEnd < mpCapacity) {
        V4* pEnd = mpEnd;
        mpEnd = pEnd + 1;
        if (pEnd)
            V4ConstructAt(pEnd, value);
    } else {
        insert(mpEnd, value);
    }
}

// ---------------------------------------------------------------------------
// 00f34d40: typed-property copy helper.
// ---------------------------------------------------------------------------
struct IPropertySource {
    virtual bool f00(); virtual bool f04(); virtual bool f08(); virtual bool f0c();
    virtual bool f10(); virtual bool f14(); virtual bool f18(); virtual bool f1c();
    virtual bool f20(); virtual bool GetProperty(void* pOut, unsigned int key) = 0;  // slot 9 (0x24)
};
struct TInfo {
    char pad[0x10];
    unsigned short mFlags;   // +0x10
    unsigned short mKind;    // +0x12
};
void  CopyInfoRaw(TInfo* dst, unsigned int n);             // 0x004548d0
TInfo* DoCopyInfo(TInfo* first, TInfo* last, TInfo* dest); // 0x00b84c80

// @ 0x00f34d40
bool CopySelectedInfo(IPropertySource* src, TInfo** pOut, unsigned int arg2, unsigned int arg3)
{
    if (!src)
        return false;
    if (!src->GetProperty(pOut, arg3))
        return false;
    TInfo* info = *pOut;
    if (info->mKind != (unsigned short)arg3)
        return false;
    if ((info->mFlags & 0x10) == 0)
        return false;

    unsigned int n;
    if ((info->mFlags & 0x30) != 0)
        n = arg2;
    else
        n = (arg3 != 0);
    TInfo* srcPtr = ((info->mFlags & 0x30) != 0) ? info : (n ? info : 0);
    CopyInfoRaw(srcPtr, n);
    DoCopyInfo(srcPtr, srcPtr + n * 1, srcPtr);
    return true;
}

// ---------------------------------------------------------------------------
// Planet-layout class owning the two vectors above.
// ---------------------------------------------------------------------------
void* PlanetModel();                    // 0x00b3d350
void* TerraformingManager();            // 0x00b3d430
void* NounManager();                    // 0x00b3d300
void  LayoutChanged(vecT38* v);         // 0x00bbd6c0
void  RemoveNoun(void* mgr, void* noun); // 0x00b225d0

struct CLayoutObj {
    char pad0[0x160];
    int m160;                    // +0x160
    vecT38 mTransforms;          // +0x164
    char pad1[0x190 - 0x16c];
    void* mpModel;               // +0x190
    void* mpCur;                 // +0x198
    V4* mV4begin;                // +0x19c
    V4* mV4end;                  // +0x1a0
    char pad2[0x1b0 - 0x1a4];
    void* mpNoun;                // +0x1b0
    unsigned int mIdx;           // +0x1b4
    unsigned char mFlag;         // +0x1b8
    void Rebuild();              // 0x00f34660
    void SetField(int value);    // 0x00f352c0
    void Refresh();              // 0x00f347e0
    void Remove();               // 0x00f352e0
};

// @ 0x00f352c0
void CLayoutObj::SetField(int value)
{
    m160 = value;
    Rebuild();
}

// @ 0x00f347e0
void CLayoutObj::Refresh()
{
    mTransforms.erase(mTransforms.mpBegin, mTransforms.mpEnd);
    mpCur = 0;
}

// @ 0x00f352e0
void CLayoutObj::Remove()
{
    if (!mpNoun)
        return;
    if (mFlag) {
        RemoveNoun(NounManager(), mpNoun);
        if (*(unsigned char*)(*(int*)((int)mpNoun + 4) + 0x68) == 0) {
            vecV4* pv = (vecV4*)((char*)this + 0x19c);
            pv->erase(mV4begin + mIdx);
        } else {
            mV4end -= 1;
            DestroyT10(mV4end, mV4end + 1);
        }
        return;
    }
    mV4end -= 1;
    DestroyT10(mV4end, mV4end + 1);
}
