// Slice s0072d5a0: 0x0072d5a0 (refcounted KD-tree wrapper, PARTIAL) and 0x0072d6a0
// (MergeIntoModels: groups meshes sharing a vertex group into GmeModel objects).
// Flags: /O2 /MD /Gy /EHsc /TP /GS-
#include <new>
#include "types.h"

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

extern "C" long __cdecl _InterlockedIncrement(long volatile*);
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile*, long);
extern "C" long __cdecl _InterlockedDecrement(long volatile*);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement, _InterlockedExchange)

void* operator new(size_t size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
void operator delete[](void* p);  // 0x00f47380

struct IRC {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(const AutoRefCount& x)
    {
        T* const pObject = x.mpObject;
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    AutoRefCount& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};

// ---- vertex / index buffer views and the material list ---------------------------------
struct MatList : IRC {
    u32 pad04[2];
    u32* mpBegin;  // +0x0c
    u32* mpEnd;
    void Remove(IRC* old);  // 0x00714050
};

struct VBView {
    u32 mGroup;
    u32 mOffset;
    u16 mSize;
    u16 mStride;
    AutoRefCount<IRC> mVB;
    VBView() : mGroup(0), mOffset(0), mSize(0), mStride(0) {}
    VBView(u32 g, u32 o, u16 s, u16 st, const AutoRefCount<IRC>& vb)
        : mGroup(g), mOffset(o), mSize(s), mStride(st), mVB(vb) {}
};

struct Elem32 {
    u32 mType;
    u32 mUsage;
    u32 mFormat;
    u32 mCategory;
    VBView mView;
    Elem32() {}
    Elem32(u32 a, u32 b, u32 c, u32 d, const VBView& v) : mType(a), mUsage(b), mFormat(c), mCategory(d), mView(v) {}
};

struct Elem20 {
    u32 mKind;
    u32 mSection;
    u32 mStart;
    u32 mEnd;
    u32 mIndex;
};

struct Elem32Vec {
    Elem32* mpBegin;
    Elem32* mpEnd;
    Elem32* mpCapacity;
    u32 mAlloc[2];
    Elem32Vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void Resize(u32 n);              // 0x00475260
    void PushBack(const Elem32& e);  // 0x0041f7d0
};

struct Elem20Vec {
    Elem20* mpBegin;
    Elem20* mpEnd;
    Elem20* mpCapacity;
    u32 mAlloc[2];
    Elem20Vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoInsertValue(Elem20* pos, const Elem20& v);  // 0x00428900
    void push_back(const Elem20& v)
    {
        if (mpEnd < mpCapacity) {
            ::new ((void*)mpEnd) Elem20(v);
            ++mpEnd;
        } else
            DoInsertValue(mpEnd, v);
    }
};

struct U32Vec {
    u32* mpBegin;
    u32* mpEnd;
    u32* mpCapacity;
    u32 mAlloc[2];
    U32Vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void Insert(u32* pos, u32 n, const u32& v);  // 0x0071e870
};

struct Section {
    VBView mIB;       // +0x00
    u32 mGroupId;     // +0x10
    U32Vec mV;        // +0x14
    u32 pad28[(0x8c - 0x28) / 4];
};

struct SectionVec {
    Section* mpBegin;
    Section* mpEnd;
    Section* mpCapacity;
    u32 mAlloc[2];
    SectionVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void PushDefault();  // 0x00475430
};

// ---- GmeModel (0x58 bytes) and its pointer type ----------------------------------------
struct GmeRefCount {
    virtual ~GmeRefCount() {}
    volatile long mRef;
    GmeRefCount() { _InterlockedExchange(&mRef, 0); }
};

struct GmeModel : GmeRefCount {
    Elem32Vec mElems;      // +0x08
    SectionVec mSections;  // +0x1c
    Elem20Vec mRanges;     // +0x30
    U32Vec mSpare;         // +0x44
    void AddRef() { _InterlockedExchangeAdd(&mRef, 1); }
    void Release()
    {
        if (_InterlockedDecrement(&mRef) == 0) {
            _InterlockedExchange(&mRef, 1);
            delete this;
        }
    }
};

struct GmePtr {
    GmeModel* mp;
    GmePtr(GmeModel* p) : mp(p) { if (mp) mp->AddRef(); }
    GmePtr(const GmePtr& x) : mp(x.mp) { if (mp) mp->AddRef(); }
    ~GmePtr() { if (mp) mp->Release(); }
};

struct GmePtrVec {
    GmePtr* mpBegin;
    GmePtr* mpEnd;
    GmePtr* mpCapacity;
    void DoInsertValue(GmePtr* pos, const GmePtr& v);  // 0x00424430
    void push_back(const GmePtr& v)
    {
        if (mpEnd < mpCapacity) {
            ::new ((void*)mpEnd) GmePtr(v);
            ++mpEnd;
        } else
            DoInsertValue(mpEnd, v);
    }
};

struct SimpleU32Vec {
    u32* mpBegin;
    u32* mpEnd;
    u32* mpCapacity;
    u32 mAlloc[2];
    SimpleU32Vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoInsertValue(u32* pos, const u32& v);  // 0x004558a0
    void push_back(const u32& v)
    {
        if (mpEnd < mpCapacity) {
            ::new ((void*)mpEnd) u32(v);
            ++mpEnd;
        } else
            DoInsertValue(mpEnd, v);
    }
};

struct GmeRefCount2 {
    virtual ~GmeRefCount2() {}
    volatile long mRef;
    GmeRefCount2() { _InterlockedExchange(&mRef, 0); }
};

struct GmeRes : IRC, GmeRefCount2 {
    SimpleU32Vec mIds;  // +0x0c
    u32 m20;
    GmeRes() : m20(0) {}
    int AddRef() { return _InterlockedIncrement(&mRef); }
    int Release() { return 0; }
    VBView GetView();  // 0x004728e0
};

// ---- source data ---------------------------------------------------------------------
#pragma pack(push, 1)
struct VElem {  // 12-byte vertex element record at hdr + 0x1a
    u16 mOffset;
    u8 mKind;
    u8 b3, b4;
    u8 mUsage;
    u32 mFormat;
    u16 pad;
};
#pragma pack(pop)

struct VHdr {
    char pad0[0xc];
    u16 mCount;      // +0x0c
    char pad0e;
    u8 mStream;      // +0x0f
    char pad10[0xa];
    VElem mElems[1]; // +0x1a
};

struct Group {
    VHdr* mHdr;
    u32 pad04[2];
    u32 mId;  // +0x0c
};

struct Src {
    u32 pad0[2];
    u32 mHandle;  // +0x08
    u32 pad0c[2];
    u32 mPrim;    // +0x14
};

struct Item {
    u32 pad0[2];
    Src* mSrc;       // +0x08
    u32 pad0c[2];
    int mStart;      // +0x14
    int mCount;      // +0x18
    u32 pad1c[2];
    Group* mGroup;   // +0x24
};

struct FixedBoolVec {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    u32 mAlloc;
    char* mpFixed;
    u32 pad;
    char mBuffer[16];
    FixedBoolVec(int n, const char& v);  // 0x0072c1e0
    ~FixedBoolVec() { if (mpBegin && mpBegin != mpFixed) operator delete[](mpBegin); }
};

extern "C" {
    int __cdecl FUN_00729b20(Group* g, void* dev, AutoRefCount<IRC>* out);
    int __cdecl FUN_00729bd0(Src* s, void* dev, AutoRefCount<IRC>* out);
    int __cdecl FUN_00729430(int a);
    int __cdecl FUN_007294d0(int a);
    void __cdecl FUN_00714260(u32* ids, int n, AutoRefCount<MatList>* out);
}

struct Pair16 { u16 lo, hi; };

// @ 0x0072d6a0
void FUN_0072d6a0(int n, Item** items, u32* ids, GmePtrVec* out, void* dev)
{
    char zero = 0;
    FixedBoolVec done(n, zero);
    for (int i = 0; i < n; ++i) {
        if (done.mpBegin[i]) continue;
        Item* first = items[i];
        Src* src0 = first->mSrc;
        Group* grp = first->mGroup;
        if (!grp || !src0) continue;

        GmeModel* model = new ("Graphics", 0, 0, 0, 0) GmeModel;
        GmePtr pModel(model);
        GmeRes* res = new ("Graphics", 0, 0, 0, 0) GmeRes;
        AutoRefCount<GmeRes> pRes(res);

        AutoRefCount<IRC> vb;
        int k = 0;
        int base = FUN_00729b20(grp, dev, &vb);
        VHdr* hdr = grp->mHdr;
        model->mElems.Resize(hdr->mCount);
        u32 grpId = grp->mId;
        u32 stream = hdr->mStream;
        int count = hdr->mCount;
        if (count > 0) {
            const u8* q = (const u8*)hdr + 0x1f;
            int off = 0;
            do {
                u8 sz;
                switch (q[-3]) {
                case 0: case 4: case 5: case 6: case 8: case 9: case 0xb: case 0xd: case 0xe: case 0xf:
                    sz = 4; break;
                case 1: case 7: case 10: case 0xc: case 0x10:
                    sz = 8; break;
                case 2: sz = 0xc; break;
                case 3: sz = 0x10; break;
                default: sz = 0;
                }
                Elem32* e = (Elem32*)((char*)model->mElems.mpBegin + off);
                e->mView = VBView(grpId, (u32) * (const u16*)(q - 5) + base, sz, (u16)stream, vb);
                e = (Elem32*)((char*)model->mElems.mpBegin + off);
                e->mType = FUN_00729430(*(const u32*)(q + 1));
                e = (Elem32*)((char*)model->mElems.mpBegin + off);
                e->mUsage = *q;
                e->mFormat = FUN_007294d0(q[-3]);
                u32 cat;
                switch (((Elem32*)((char*)model->mElems.mpBegin + off))->mType) {
                case 1: case 9: case 10: case 0xc: cat = 0; break;
                case 2: case 0xd: cat = 1; break;
                case 3: case 4: case 5: case 8: case 0x10: case 0x11: cat = 2; break;
                default: cat = 0xe;
                }
                ((Elem32*)((char*)model->mElems.mpBegin + off))->mCategory = cat;
                q += 12;
                off += 0x20;
            } while (--count);
        }

        for (int j = i; j < n; ++j) {
            if (done.mpBegin[j]) continue;
            Item* itj = items[j];
            if (itj->mGroup != grp) continue;
            Src* src = itj->mSrc;
            if (!src) continue;

            unsigned secIdx = model->mSections.mpEnd - model->mSections.mpBegin;
            model->mSections.PushDefault();
            Section* sec = model->mSections.mpBegin + secIdx;
            unsigned need = model->mElems.mpEnd - model->mElems.mpBegin;
            unsigned have = sec->mV.mpEnd - sec->mV.mpBegin;
            if (need > have) {
                Pair16 z = {0, 0};
                sec->mV.Insert(sec->mV.mpEnd, need - have, *(u32*)&z);
            } else {
                sec->mV.mpEnd = sec->mV.mpBegin + need;
            }
            if ((int)need > 0) {
                Pair16 pr;
                pr.hi = 0xffff;
                for (int m = 0; m < (int)need; ++m) {
                    pr.lo = (u16)m;
                    sec->mV.mpBegin[m] = *(u32*)&pr;
                }
            }

            u32 handle = src->mHandle;
            AutoRefCount<IRC> vb2;
            int base2 = FUN_00729bd0(src, dev, &vb2);
            sec->mGroupId = grp->mId;
            sec->mIB = VBView(handle, base2, 2, 2, vb2);
            for (int m = j; m < n; ++m) {
                Item* itm = items[m];
                if (!done.mpBegin[m] && itm->mSrc == src && itm->mGroup == grp) {
                    u32 kind;
                    switch (src->mPrim) {
                    case 1: kind = 1; break;
                    case 2: kind = 2; break;
                    case 3: kind = 3; break;
                    default: kind = 4; break;
                    case 5: kind = 5; break;
                    case 6: kind = 6; break;
                    }
                    Elem20 e;
                    e.mKind = kind;
                    e.mSection = secIdx;
                    e.mStart = itm->mStart;
                    e.mEnd = itm->mCount + itm->mStart;
                    e.mIndex = k++;
                    model->mRanges.push_back(e);
                    res->mIds.push_back(ids[m]);
                    done.mpBegin[m] = 1;
                }
            }
        }

        if (model->mRanges.mpBegin != model->mRanges.mpEnd) {
            model->mElems.PushBack(Elem32(0x15, 0, 6, 8, res->GetView()));
            Elem32* last = model->mElems.mpEnd - 1;
            AutoRefCount<MatList> mat;
            FUN_00714260(res->mIds.mpBegin, res->mIds.mpEnd - res->mIds.mpBegin, &mat);
            if (mat.mpObject) {
                mat.mpObject->Remove(last->mView.mVB.mpObject);
                last->mView.mVB = mat.mpObject;
            }
            out->push_back(pModel);
        }
    }
}

// @ 0x0072d5a0  refcounted wrapper that runs FUN_0072c270 (PARTIAL)
int FUN_0072d5a0(void* self, int a, int b, int c, int d)
{
    (void)self; (void)a; (void)b; (void)c; (void)d;
    return 0;
}
