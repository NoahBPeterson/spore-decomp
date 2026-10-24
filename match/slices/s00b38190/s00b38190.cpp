// Slice s00b38190 — SP eastl vector/sort helpers over 8-byte {ref-counted handle, float} pairs,
// plus the two intrusive-list walkers that count list keys into an eastl::map<unsigned,unsigned>.
// Rebuilt from the retail disassembly (32-bit MSVC 2008 SP1 build, /O2).
//   0x00b38190  intrusive-list walk, increments the caller's map                (196 B, thiscall, ret 4)
//   0x00b38260  Vec8Ins::push_back                                             ( 49 B, thiscall, ret 4)
//   0x00b382a0  model-world filter, list at this+0x2c -> AutoRefCount vector    (384 B, thiscall, ret 0x18)
//   0x00b38420  model-world filter with a 16-slot inline hit buffer             (429 B, thiscall, ret 0x10)
//   0x00b385d0  SortCmp::FUN_00b385d0 comparator (set membership, then value)   (179 B, thiscall, ret 8)
//   0x00b38690  RefPair vector insert (reallocating overload)                   (528 B, thiscall, ret 0xc)
//   0x00b388a0  insertion sort of RefPair                                       (331 B, cdecl)
//   0x00b38b40  partition used by the sort                                      (163 B, cdecl)
//   0x00b38bf0  sift-up / push-heap                                             (271 B, cdecl)
//   0x00b38d00  intrusive-list walk into a local map                            (308 B, thiscall, ret 0)
// flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// Skip N virtual slots.  Every use needs a unique prefix p.
#define VS1(p)  virtual void p##_a();
#define VS2(p)  VS1(p##0) VS1(p##1)
#define VS4(p)  VS2(p##0) VS2(p##1)
#define VS8(p)  VS4(p##0) VS4(p##1)
#define VS16(p) VS8(p##0) VS8(p##1)
#define VS32(p) VS16(p##0) VS16(p##1)
#define VS64(p) VS32(p##0) VS32(p##1)

extern "C" {
void* EAAllocate(unsigned int size, const char* name, int a, int b, int c, int d); // 0xf473a0
void  operator_delete(void* p);                                                    // 0xf47380
}

// ------------------------------------------------------------------ ref-counted handle model
// A handle's first field points at its owner object; the owner's wide vtable has the release
// entry at slot 0x170.  The handle's +4 flags word carries the "destroy" bit in bit 31 and the
// reference count lives at +0x40.
struct RefHandle;
struct RefOwner {
    VS64(v0) VS16(v1) VS8(v2) VS4(v3)
    virtual void Release(RefHandle* obj, bool sign);        // +0x170
};
struct RefHandle {
    RefOwner* mpOwner;      // +0x00
    int       mFlags;       // +0x04
    int       mPad08[14];   // +0x08 .. +0x3f
    int       mRefCount;    // +0x40

    void Decrement() {
        if (mRefCount > 1) {
            --mRefCount;
        } else {
            mpOwner->Release(this, (bool)(((unsigned int)mFlags) >> 31));
        }
    }
};

// The 8-byte element worked on by every helper in this slice.  It is a plain pair: retain and
// release are always written out explicitly at the use sites, so the copy below is the
// "copy-assign with reference transfer" that the original inlines everywhere.
struct RefPair {
    RefHandle* mpHandle;    // +0x00
    float      mValue;      // +0x04

    void Assign(const RefPair& r) {
        RefHandle* nv = r.mpHandle;
        RefHandle* ov = mpHandle;
        if (nv != ov) {
            if (nv) ++nv->mRefCount;
            mpHandle = nv;
            if (ov) ov->Decrement();
        }
        mValue = r.mValue;
    }
};

// ------------------------------------------------------------------ comparators / sorting
struct SortCmp {
    int mState;             // +0x00 (unused by the comparison itself)
    bool FUN_00b385d0(RefPair* a, RefPair* b) const;        // 0x00b385d0
};

extern unsigned int* g_setBegin;                            // 0x0167ea68
extern unsigned int* g_setEnd;                              // 0x0167ea6c
extern unsigned char g_setFlag;                             // 0x0167ea7c
extern unsigned int* eastl_lower_bound(unsigned int* first, unsigned int* last,
                                       const unsigned int* key, unsigned char cmp);  // 0x00555a20
extern void* __stdcall SP_GonzagoModelWorld();              // 0x00b3d520
extern void FUN_00b36610(RefPair* a, RefPair* b);           // 0x00b36610 (swap)
extern RefPair* FUN_00b38b40(RefPair* first, RefPair* last, RefPair pivot, SortCmp cmp);
extern void FUN_00b38bf0(RefPair* base, int first, int hole, RefPair value, SortCmp cmp);

// ------------------------------------------------------------------ Vec8Ins (0x00b38260)
// The push_back instantiation copies the 8-byte element field-for-field and never touches the
// FPU/SSE unit, so its element is modelled as a pair whose second field is the raw value bits.
struct Vec8Pair {
    RefHandle* mpHandle;    // +0x00
    int32_t    mValueBits;  // +0x04
};
struct Vec8Ins {
    Vec8Pair* mpBegin;      // +0x00
    Vec8Pair* mpEnd;        // +0x04
    Vec8Pair* mpCapacity;   // +0x08
    void Insert(void* pos, const void* value);              // 0x0074bf10
    void FUN_00b38260(const Vec8Pair* p);
};

// ------------------------------------------------------------------ AutoRefCount vectors (filters)
struct AutoRefVec {
    void** mpBegin;         // +0x00
    void** mpEnd;           // +0x04
    void** mpCapacity;      // +0x08
    void**  erase(void** first, void** last);               // 0x00b48e40
    void    SetCapacity(unsigned int count);                // 0x00d01790
    void    GrowPush(void** pos, void** value);             // 0x00bab900
};

// A created object: the +0x64 member is asked for interface 0x01186577 through its slot 0x0c.
struct IQuerySource {
    virtual void  q00();                                    // +0x00
    virtual void  q04();                                    // +0x04
    virtual void  q08();                                    // +0x08
    virtual void* QueryInterface(unsigned int id);          // +0x0c
};
struct HitObject {
    unsigned int  mPad00[25];                               // +0x00 .. +0x63
    IQuerySource* mpHolder;                                 // +0x64
};

// The object handed back by QueryInterface; referenced through slots 0xbc / 0xc0.
struct IRefCountedObj {
    VS32(a) VS8(b) VS4(c) VS2(d) VS1(e)                     // 47 slots: +0x00 .. +0xb8
    virtual void AddRef();                                  // +0xbc
    virtual void Release();                                 // +0xc0
};

// 24-byte filter description handed to the model world.
struct FilterSpec {
    unsigned int  mField00;                                 // +0x00
    unsigned int  mField04;                                 // +0x04
    unsigned int  mField08;                                 // +0x08
    unsigned int  mField0c;                                 // +0x0c
    unsigned int  mField10;                                 // +0x10
    unsigned char mFlag;                                    // +0x14
    unsigned char mPad15;                                   // +0x15
};

// The world returns its hits into a vector; slots 0x00/0x04 are the get/release pair.
struct IModelWorld {
    virtual void Lock();                                    // +0x00
    virtual void Unlock();                                  // +0x04
    VS8(w0) VS4(w1)                                         // +0x08 .. +0x34
    virtual bool Filter38(void* a1, float f, void* hits, FilterSpec* spec);   // +0x38
};
struct IModelWorld30 {
    virtual void Lock();                                    // +0x00
    virtual void Unlock();                                  // +0x04
    VS8(x0) VS2(x1)                                         // +0x08 .. +0x2c
    virtual bool Filter30(void* a1, void* a2, void* hits, FilterSpec* spec, float f);  // +0x30
};

struct PtrVec {                 // hit list held by the owner object (4-byte entries)
    HitObject** mpBegin;    // +0x00
    HitObject** mpEnd;      // +0x04
    HitObject** mpCapacity; // +0x08
};
struct WorldHit {               // one entry of the world filter's 8-byte hit buffer
    HitObject* mpObject;    // +0x00
    float      mDistance;   // +0x04
};
struct HitVec {
    WorldHit* mpBegin;      // +0x00
    WorldHit* mpEnd;        // +0x04
    WorldHit* mpCapacity;   // +0x08
};

struct FilterOwner {
    unsigned int mPad00[0x2c / 4];                          // +0x00 .. +0x2b
    PtrVec       mHitList;                                  // +0x2c
    unsigned int mPad38[(0xe4 - 0x38) / 4];                 // +0x38 .. +0xe3
    IModelWorld* mpWorld;                                   // +0xe4

    bool FUN_00b382a0(void* a1, float f, AutoRefVec* out, unsigned char flag,
                      bool (*fn)(void*, void*), void* ctx);
    bool FUN_00b38420(void* a1, void* a2, AutoRefVec* out, unsigned char flag);
};

// ------------------------------------------------------------------ RefPair vector (0x00b38690)
struct RefPairVec {
    RefPair* mpBegin;       // +0x00
    RefPair* mpEnd;         // +0x04
    RefPair* mpCapacity;    // +0x08
    unsigned int mPad0c;    // +0x0c
    RefPair* mpBuffer;      // +0x10 (inline buffer, freed only when mpBegin differs)
    void FUN_00b38690(RefPair* pos, unsigned int n, const RefPair* value);
};

// ------------------------------------------------------------------ intrusive-list walkers
// The list sentinel is embedded at this+0x20 (the nodes' link fields sit at +0x24).  Every node
// stores, at node+4, the address of the next node's link field, so the walk converts a link back
// to a node by subtracting 4.  Both walkers query each node (slot 0x0c -> slot 0x38/0x20) and
// count the resulting key into an eastl::map<unsigned int,unsigned int>, whose red-black
// lower_bound walk the original inlined.  That walk is not reconstructed here.
struct SpatialObjectSet {
    unsigned int mPad00[0x20 / 4];                          // +0x00 .. +0x1f
    unsigned int mHeadLink;                                 // +0x20
    unsigned int mFirstLink;                                // +0x24

    void FUN_00b38190(void* pMap);
    void FUN_00b38d00();
};

// ------------------------------------------------------------------ 0x00b38190 (stub)
// @ 0x00b38190
void SpatialObjectSet::FUN_00b38190(void*)
{
}

// ------------------------------------------------------------------ 0x00b38260
// @ 0x00b38260
void Vec8Ins::FUN_00b38260(const Vec8Pair* p)
{
    Vec8Pair* e = mpEnd;
    if (e < mpCapacity) {
        mpEnd = e + 1;
        if (e != 0) {
            e->mpHandle = p->mpHandle;
            e->mValueBits = p->mValueBits;
            return;
        }
    } else {
        Insert(mpEnd, p);
    }
}

// ------------------------------------------------------------------ 0x00b382a0
// @ 0x00b382a0
bool FilterOwner::FUN_00b382a0(void* a1, float f, AutoRefVec* out, unsigned char flag,
                               bool (*fn)(void*, void*), void* ctx)
{
    out->erase(out->mpBegin, out->mpEnd);
    out->SetCapacity(0x80);

    FilterSpec spec;
    spec.mField00 = 0;
    spec.mField04 = 0;
    spec.mField08 = 0;
    spec.mField0c = 0;
    spec.mField10 = 0;
    spec.mFlag = flag;
    spec.mPad15 = 0;

    IModelWorld* world = (IModelWorld*)SP_GonzagoModelWorld();
    bool ok = false;
    if (world != 0) {
        world->Lock();
        ok = world->Filter38(a1, f, &mHitList, &spec);
    }
    if (!ok) {
        ok = ((IModelWorld*)mpWorld)->Filter38(a1, f, &mHitList, &spec);
    }
    if (ok) {
        HitObject** it = mHitList.mpBegin;
        HitObject** end = mHitList.mpEnd;
        while (it != end) {
            HitObject* p = *it;
            IRefCountedObj* q = 0;
            if (p->mpHolder != 0) {
                q = (IRefCountedObj*)((IQuerySource*)p->mpHolder)->QueryInterface(0x01186577);
            }
            if (q != 0 && (fn == 0 || fn(p, ctx))) {
                q->AddRef();
                IRefCountedObj* tmp = q;
                if ((void**)out->mpEnd < out->mpCapacity) {
                    IRefCountedObj** slot = (IRefCountedObj**)out->mpEnd;
                    out->mpEnd = (void**)(slot + 1);
                    if (slot != 0) {
                        *slot = q;
                        q->AddRef();
                    }
                } else {
                    out->GrowPush(out->mpEnd, (void**)&tmp);
                    q = tmp;
                }
                if (q != 0) q->Release();
            }
            ++it;
        }
    }
    bool result = (out->mpBegin != out->mpEnd);
    if (world != 0) world->Unlock();
    return result;
}

// ------------------------------------------------------------------ 0x00b38420
// @ 0x00b38420
bool FilterOwner::FUN_00b38420(void* a1, void* a2, AutoRefVec* out, unsigned char flag)
{
    out->erase(out->mpBegin, out->mpEnd);
    out->SetCapacity(0x80);

    WorldHit buffer[16];
    HitVec hits;
    hits.mpBegin = buffer;
    hits.mpEnd = buffer;
    hits.mpCapacity = buffer + 16;

    FilterSpec spec;
    spec.mField00 = 0;
    spec.mField04 = 0;
    spec.mField08 = 0;
    spec.mField0c = 0;
    spec.mField10 = 0;
    spec.mFlag = flag;
    spec.mPad15 = 0;

    IModelWorld30* world = (IModelWorld30*)SP_GonzagoModelWorld();
    bool ok = false;
    if (world != 0) {
        world->Lock();
        ok = world->Filter30(a1, a2, &hits, &spec, 0.0f);
    }
    if (!ok) {
        ok = ((IModelWorld30*)mpWorld)->Filter30(a1, a2, &hits, &spec, 0.0f);
    }
    if (ok) {
        WorldHit* it = hits.mpBegin;
        WorldHit* end = hits.mpEnd;
        if (it != end) {
            do {
                HitObject* p = it->mpObject;
                IRefCountedObj* q = 0;
                if (p->mpHolder != 0) {
                    q = (IRefCountedObj*)((IQuerySource*)p->mpHolder)->QueryInterface(0x01186577);
                }
                if (q != 0) {
                    q->AddRef();
                    IRefCountedObj* tmp = q;
                    if ((void**)out->mpEnd < out->mpCapacity) {
                        IRefCountedObj** slot = (IRefCountedObj**)out->mpEnd;
                        out->mpEnd = (void**)(slot + 1);
                        if (slot != 0) {
                            *slot = q;
                            q->AddRef();
                        }
                    } else {
                        out->GrowPush(out->mpEnd, (void**)&tmp);
                        q = tmp;
                    }
                    if (q != 0) q->Release();
                }
                ++it;
            } while (it != end);
        }
    }
    bool result = (out->mpBegin != out->mpEnd);
    if (world != 0) world->Unlock();
    if (hits.mpBegin != 0 && hits.mpBegin != buffer) operator_delete(hits.mpBegin);
    return result;
}

// ------------------------------------------------------------------ 0x00b385d0
// @ 0x00b385d0
bool SortCmp::FUN_00b385d0(RefPair* a, RefPair* b) const
{
    unsigned int keyA = (unsigned int)a->mpHandle;
    unsigned int* itA = eastl_lower_bound(g_setBegin, g_setEnd, &keyA, g_setFlag);
    if (itA == g_setEnd || keyA < *itA) itA = g_setEnd;
    bool inA = (itA != g_setEnd);

    unsigned int keyB = (unsigned int)b->mpHandle;
    unsigned int* itB = eastl_lower_bound(g_setBegin, g_setEnd, &keyB, g_setFlag);
    if (itB == g_setEnd || keyB < *itB) itB = g_setEnd;
    bool inB = (itB != g_setEnd);

    if (inA != inB) return inA;
    return a->mValue > b->mValue;
}

// ------------------------------------------------------------------ 0x00b38690 (stub)
// @ 0x00b38690
void RefPairVec::FUN_00b38690(RefPair*, unsigned int, const RefPair*)
{
}

// ------------------------------------------------------------------ 0x00b388a0
// @ 0x00b388a0
void FUN_00b388a0(RefPair* first, RefPair* last, SortCmp cmp)
{
    if (first == last) return;
    for (RefPair* i = first + 1; i != last; ++i) {
        RefPair temp;
        temp.mpHandle = i->mpHandle;
        if (temp.mpHandle) ++temp.mpHandle->mRefCount;
        temp.mValue = i->mValue;

        RefPair* j = i;
        while (j != first) {
            if (!cmp.FUN_00b385d0(&temp, j - 1)) break;
            j->Assign(*(j - 1));
            j -= 1;
        }
        j->Assign(temp);
        if (temp.mpHandle) temp.mpHandle->Decrement();
    }
}

// ------------------------------------------------------------------ 0x00b38b40
// The original peels "last -= 8" into the second loop (do/while shape) exactly as written here;
// this form reproduces the original's 163-byte body size.
// @ 0x00b38b40
RefPair* FUN_00b38b40(RefPair* first, RefPair* last, RefPair pivot, SortCmp cmp)
{
    for (;;) {
        while (cmp.FUN_00b385d0(first, &pivot)) ++first;
        do {
            --last;
        } while (cmp.FUN_00b385d0(&pivot, last));
        if (last <= first) break;
        FUN_00b36610(first, last);
        ++first;
    }
    if (pivot.mpHandle) pivot.mpHandle->Decrement();
    return first;
}

// ------------------------------------------------------------------ 0x00b389f0
// The hk2 batch lists this function under the same slice id; the reconstruction is carried over
// from the earlier attempt for that batch (same source family as 0x00b388a0/0x00b38b40).
// @ 0x00b389f0
void FUN_00b389f0(RefPair* first, RefPair* last, SortCmp cmp)
{
    for (RefPair* cur = first; cur != last; ++cur) {
        RefHandle* keyH = cur->mpHandle;
        if (keyH != 0) ++keyH->mRefCount;
        RefPair key;
        key.mpHandle = keyH;
        key.mValue = cur->mValue;

        RefPair* h = cur;
        if (cmp.FUN_00b385d0(&key, cur - 1)) {
            bool c;
            do {
                RefPair* prev = h - 1;
                RefHandle* a = prev->mpHandle;
                RefHandle* b = h->mpHandle;
                if (a != b) {
                    if (a != 0) ++a->mRefCount;
                    h->mpHandle = a;
                    if (b != 0) b->Decrement();
                }
                h = prev;
                (h + 1)->mValue = h->mValue;
                c = cmp.FUN_00b385d0(&key, h - 1);
            } while (c);
        }
        RefHandle* hp = h->mpHandle;
        if (keyH != hp) {
            if (keyH != 0) ++keyH->mRefCount;
            h->mpHandle = keyH;
            if (hp != 0) hp->Decrement();
        }
        h->mValue = key.mValue;
        if (keyH != 0) keyH->Decrement();
    }
}

// ------------------------------------------------------------------ 0x00b38bf0
// @ 0x00b38bf0
void FUN_00b38bf0(RefPair* base, int first, int hole, RefPair value, SortCmp cmp)
{
    while (first < hole) {
        int parent = (hole - 1) >> 1;
        if (!cmp.FUN_00b385d0(base + parent, &value)) break;
        base[hole].Assign(base[parent]);
        hole = parent;
    }
    base[hole].Assign(value);
    if (value.mpHandle) value.mpHandle->Decrement();
}

// ------------------------------------------------------------------ 0x00b38d00 (stub)
// @ 0x00b38d00
void SpatialObjectSet::FUN_00b38d00()
{
}