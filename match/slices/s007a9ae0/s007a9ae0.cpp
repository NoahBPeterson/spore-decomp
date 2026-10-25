// slice s007a9ae0  --  texture-manager deque/allocator internals.
// Reconstructed C++ (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP).
#include "types.h"

extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line); // 0x00f473a0
extern "C" void  EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" long  _InterlockedExchangeAdd(volatile long* addend, long value);
#pragma intrinsic(_InterlockedExchangeAdd)
extern "C" long  _InterlockedExchange(volatile long* target, long value);
#pragma intrinsic(_InterlockedExchange)
extern "C" void  memmove(void*, const void*, unsigned int);
extern "C" void* VectorDoInsertValue(void*, void*, unsigned int);
// 0x00690120 is the thiscall member ?Release@cJob@@QAEHXZ (this in ecx, no stack args).
extern "C" void  FUN_00690_120_GetStatus(void*);
typedef int (__thiscall* cJobReleaseFn)(void*);

// thiscall members of the job / editor / thread / texture subsystems. They are declared
// address-only (the resolver binds them by the 0x... hex in the identifier) and invoked
// through __thiscall typedefs, which MSVC 2008 accepts on function pointers.
extern "C" void  FUN_006913c0_AddWeakDep(void*);            // 0x006913c0  cJob::AddWeakDependency
extern "C" void  FUN_006926b0_Cancel(void*);                // 0x006926b0  cJob::Cancel
extern "C" void  FUN_006909b0_Refresh(void*);               // 0x006909b0  Editor::Refresh
extern "C" void  FUN_00576650_Assign(void*);                // 0x00576650  cAtomicRefPtr::operator=
extern "C" void  FUN_00630540_Assign(void*);                // 0x00630540  JobRef::operator=
extern "C" void  FUN_009221b0_Lock(void*);                  // 0x009221b0  Mutex::Lock
extern "C" void  FUN_00922270_Unlock(void*);                // 0x00922270  Mutex::Unlock
extern "C" void  FUN_00921440_Needed(void*);                // 0x00921440  RehashPolicy::Needed
extern "C" void  FUN_011ef750_Open(void*);                  // 0x011ef750  texture Open
extern "C" void  FUN_011ef880_Close(void*);                 // 0x011ef880  texture Close
extern "C" void  FUN_007a99d0_Rehash(void*);                // 0x007a99d0  hashtable rehash

extern "C" void* FUN_0067dd60();                            // 0x0067dd60  GetItemManager
extern "C" void* FUN_0067dcd0();                            // 0x0067dcd0  GetFactory
extern "C" void* FUN_0067dd50();                            // 0x0067dd50  JobManager
extern "C" void* FUN_0067dcc0();                            // 0x0067dcc0  MessageManager
extern "C" void* FUN_0068f4d0();                            // 0x0068f4d0  GetJobManager
extern "C" void  FUN_006ac040_SetCachingType(int, void*);   // 0x006ac040
extern "C" unsigned int FUN_00932e80_hash(const char*, unsigned int, int);  // 0x00932e80
extern "C" void* FUN_00761b40();                            // 0x00761b40
extern "C" void* FUN_00761c00();                            // 0x00761c00
extern "C" int*  FUN_0041e990_GetInt();                     // 0x0041e990
extern "C" int   FUN_00926650_AddCore(void*, int, int);     // 0x00926650
extern "C" void* g_15fd918;                                 // 0x015fd918

// __thiscall call-site typedefs (MSVC 2008 rejects __thiscall on free functions).
typedef void (__thiscall* FnV0)(void*);
typedef void (__thiscall* FnV1)(void*, int);
typedef void (__thiscall* FnV2)(void*, int, int);
typedef void (__thiscall* FnVP)(void*, void*);
typedef void (__thiscall* FnVPP)(void*, void*, void*);
typedef bool (__thiscall* FnB1)(void*, void*);
typedef bool (__thiscall* FnB2)(void*, void*, int);
typedef void*(__thiscall* FnP1)(void*, int);
typedef int  (__thiscall* FnI1)(void*, int);
typedef int  (__thiscall* FnI3)(void*, int, int, void*);
typedef void (__thiscall* FnV4)(void*, void*, int, int);
typedef void (__thiscall* FnV6)(void*, void*, int, int, int, int);
typedef void*(__thiscall* FnP8)(void*, unsigned, int, int, int, int, int, int, int);

// ---- deque map (eastl::deque storage) ----------------------------------------
// eastl::DequeIterator<int>: points into a 64-int subarray; mpCurrentArrayPtr walks
// the map array of subarray base pointers (same layout as s004a9920 / s00513930).
struct DequeIterator {
    int*  mpCurrent;         // +0x00
    int*  mpBegin;           // +0x04
    int*  mpEnd;             // +0x08
    int** mpCurrentArrayPtr; // +0x0c
};

struct DequeMap {
    int*  mpBegin;      // +0x00
    int   mCapacity;    // +0x04
    int*  mFirst;       // +0x0c
    int*  mLast;        // +0x10
    int*  mCur;         // +0x14
    int*  mNextBegin;   // +0x18
    int*  mNextLast;    // +0x1c / +0x18?
    int*  mTailFirst;   // +0x20
    int*  mTailLast;    // +0x24
    void InsertAt(int count, int zero);
    void PushBack(int* value);
    void ReverseCopyTo(int* out, int* end);
};

struct Chunk {
    Chunk* mpNext;      // +0x00
    int    pad04;
    int    pad08;
    char   m0c;
    long   mRef;        // +0x10
    int    pad14[2];
    int    pad1c;
    int    pad20;
    int    pad24;
    int    pad28;
    int    pad2c;
};

struct cNodeAllocator {
    int   pad00[4];
    Chunk* mpHeadChunk; // +0x10
    Chunk* Create();
};

// @ 0x007a9ae0
void DequeMap::InsertAt(int count, int zero)
{
    int* first = this->mCur;
    int used = ((char*)this->mTailLast - (char*)first) >> 2;
    int n = used + 1;
    int need = n + count;
    unsigned int cap = (unsigned int)this->mCapacity;
    if ((unsigned int)(need * 2) < cap) {
        int* dst = (int*)((char*)this->mpBegin +
            ((int)((cap - need) >> 1) + (~-(unsigned)(zero != 0) & count)) * 4);
        if (dst < first)
            VectorDoInsertValue(dst, first, (used + 1) * 4);
        else
            memmove(dst + (n - (((used + 1) * 4) >> 2)), first, (used + 1) * 4);
    }
    else {
        int cap2 = (this->mCapacity < count) ? count : this->mCapacity;
        int total = cap2 + 2 + (int)cap;
        int* nb = (int*)EASTL_allocator_allocate(total * 4, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        int* src = (int*)this->mCur;
        int* dst = (int*)((char*)nb + ((((char*)src - (char*)this->mpBegin) >> 2) +
                          (~-(unsigned)(zero != 0) & count)) * 4);
        if (this->mpBegin)
            VectorDoInsertValue(dst, src, this->mTailLast - src + 1);
        if (this->mpBegin)
            EASTL_allocator_deallocate(this->mpBegin);
        this->mpBegin = nb;
        this->mCapacity = total;
    }
    this->mCur = 0;
}

// @ 0x007a9d70  eastl deque copy_backward: move [first, last) to end at last2.
// The three iterators are passed by value (4 dwords each) and the function returns
// the new destination begin, so all 13 stack dwords of the original are consumed.
DequeIterator* FUN_007a9d70(DequeIterator* result, DequeIterator first,
                            DequeIterator last, DequeIterator last2)
{
    while (last.mpCurrent != first.mpCurrent) {
        if (last.mpCurrent == last.mpBegin) {
            --last.mpCurrentArrayPtr;
            last.mpBegin = *last.mpCurrentArrayPtr;
            last.mpEnd = last.mpBegin + 0x40;      // EASTL subarray = 64 ints
        }
        --last.mpCurrent;
        if (last2.mpCurrent == last2.mpBegin) {
            --last2.mpCurrentArrayPtr;
            last2.mpBegin = *last2.mpCurrentArrayPtr;
            last2.mpEnd = last2.mpBegin + 0x40;
        }
        --last2.mpCurrent;
        *last2.mpCurrent = *last.mpCurrent;
    }
    result->mpCurrent = last2.mpCurrent;
    result->mpBegin = last2.mpBegin;
    result->mpEnd = last2.mpEnd;
    result->mpCurrentArrayPtr = last2.mpCurrentArrayPtr;
    return result;
}

// @ 0x007a9e10  Editor::cPropertyList-like ctor
extern "C" char VT_PropertyListA[];   // 0x013ebcdc
extern "C" char VT_PropertyListB[];   // 0x01453eac
extern "C" char VT_PropertyListB2[];  // 0x013ebcb8
extern "C" char VT_PropertyListC[];   // 0x0140fef4
void* FUN_007a9e10(void* self, int w, int h)
{
    *(void**)self = (void*)VT_PropertyListA;
    *(void**)((char*)self + 4) = 0;
    *(void**)((char*)self + 8) = 0;
    *(void**)((char*)self + 0xc) = 0;
    *(void**)((char*)self + 0x10) = 0;
    *(void**)((char*)self + 0x14) = 0;
    *(void**)((char*)self + 0x18) = (void*)VT_PropertyListB;
    *(int*)((char*)self + 0x1c) = w;
    *(int*)((char*)self + 0x20) = h;
    *(int*)((char*)self + 0x24) = -1;
    *(void**)((char*)self + 0x28) = 0;
    *(void**)self = (void*)VT_PropertyListC;
    *(void**)((char*)self + 0x18) = (void*)VT_PropertyListB2;
    void* buf = EASTL_allocator_allocate((unsigned)(w * h), "Graphics", 0, 0, 0, 0);
    *(void**)((char*)self + 0x28) = buf;
    *(int*)((char*)self + 0x24) = 1;
    return self;
}

// @ 0x007a9eb0
extern "C" char VT_ArenaResource[];   // 0x013eb938
void FUN_007a9eb0(int* self)
{
    if (self[4])
        ((void(__thiscall*)(void*))((void**)self[4])[2])((void*)self[4]);
    if (self[2])
        _InterlockedExchangeAdd((volatile long*)((char*)self[2] + 8), -1);
    *(void**)self = (void*)VT_ArenaResource;
}

// ---- texture-manager / job subsystem layouts --------------------------------
struct Mutex {                      // EA::Thread::Mutex (0x009221b0 Lock, 0x00922270 Unlock)
    int mData[6];
};

struct TexManager {
    void**        mpVT;             // +0x00
    int           mField04;         // +0x04
    int           mField08;         // +0x08
    unsigned char mInitFlag;        // +0x0c
    void*         mField10;         // +0x10
    void*         mField14;         // +0x14
    void*         mNormalMap;       // +0x18  placeholder normal-map ref (cAtomicRefPtr)
    void*         mSpecGlossMap;    // +0x1c  placeholder spec/gloss ref (cAtomicRefPtr)
    Mutex         mMutex;           // +0x20
    unsigned char mPad[0xcc - 0x20 - sizeof(Mutex)];
    int           mFieldCC;         // +0xcc
    void*         mFieldD0;         // +0xd0
    TexManager*   mSelfD4;          // +0xd4
};

// @ 0x007a9f30  one-time init: build the two placeholder textures (normal map and
// spec/gloss map) through the texture manager's own vtable.
extern "C" bool __fastcall FUN_007a9f30(TexManager* self, int dummy)
{
    (void)dummy;
    if (self->mInitFlag) return false;
    self->mInitFlag = 1;
    self->mField10 = FUN_00761b40();
    self->mField14 = FUN_00761c00();
    if (g_15fd918) {
        int out = 0;
        if (((bool(__thiscall*)(void*, int, void*))(*(void***)g_15fd918)[9])(g_15fd918, 0x2840048, &out)
            && *(short*)((char*)out + 0x12) == 9)
            self->mFieldCC = *FUN_0041e990_GetInt();
    }
    self->mSelfD4 = self;

    unsigned h1 = FUN_00932e80_hash("PlaceholderNormalMap", 0x811c9dc5, 1);
    void* o1 = ((FnP8)(*(void***)self)[15])(self, h1, 0x40002700, 1, 1, 1, 8, 0x15, 0);
    ((void(__thiscall*)(void*, void*))FUN_00576650_Assign)(&self->mNormalMap, o1);
    {
        void* o = self->mNormalMap;
        if (!(*(unsigned char*)((char*)o + 4) & 1)) {
            void* im = FUN_0067dd60();
            ((FnVP)(*(void***)im)[13])(im, o);
        }
    }
    {
        void* o = self->mNormalMap;
        int out = 0;
        if (((int(__thiscall*)(void*, int, int, void*))FUN_011ef750_Open)(*(void**)o, 2, 0, &out)) {
            *(int*)out = 0x7f7fff;
            void* o2 = self->mNormalMap;
            if (!(*(unsigned char*)((char*)o2 + 4) & 1)) {
                void* im = FUN_0067dd60();
                ((FnVP)(*(void***)im)[13])(im, o2);
            }
            ((void(__thiscall*)(void*, void*))FUN_011ef880_Close)(*(void**)o2, &out);
        }
    }
    unsigned h2 = FUN_00932e80_hash("PlaceholderSpecGlossMap", 0x811c9dc5, 1);
    void* o3 = ((FnP8)(*(void***)self)[15])(self, h2, 0x40002700, 1, 1, 1, 8, 0x15, 0);
    ((void(__thiscall*)(void*, void*))FUN_00576650_Assign)(&self->mSpecGlossMap, o3);
    {
        void* o = self->mSpecGlossMap;
        if (!(*(unsigned char*)((char*)o + 4) & 1)) {
            void* im = FUN_0067dd60();
            ((FnVP)(*(void***)im)[13])(im, o);
        }
    }
    {
        void* o = self->mSpecGlossMap;
        int out = 0;
        if (((int(__thiscall*)(void*, int, int, void*))FUN_011ef750_Open)(*(void**)o, 2, 0, &out)) {
            *(int*)out = 0x806464;
            void* o2 = self->mSpecGlossMap;
            if (!(*(unsigned char*)((char*)o2 + 4) & 1)) {
                void* im = FUN_0067dd60();
                ((FnVP)(*(void***)im)[13])(im, o2);
            }
            ((void(__thiscall*)(void*, void*))FUN_011ef880_Close)(*(void**)o2, &out);
        }
    }
    return true;
}

struct JobSlots {
    void Clear();      // 007aa320
    char Transfer(int param_2);   // 007aa3a0 (returns in al)
};

// @ 0x007aa320
void JobSlots::Clear()
{
    int* self = (int*)this;
    if (self[1]) {
        void* old = (void*)self[1];
        self[1] = 0;
        ((cJobReleaseFn)FUN_00690_120_GetStatus)(old);      // thiscall: this in ecx
    }
    if (self[0]) {
        volatile long* rc = (volatile long*)((char*)self[0] + 0x10);
        self[0] = 0;
        _InterlockedExchangeAdd(rc, -1);
        long cur = _InterlockedExchangeAdd(rc, 0);
        if (cur < 1) _InterlockedExchangeAdd(rc, 1); else _InterlockedExchangeAdd(rc, 0);
    }
    if (self[2]) {
        int* p = (int*)self[2];
        self[2] = 0;
        void** vt = *(void***)p;                            // vtable at *p, slot 1
        ((void(__thiscall*)(void*))vt[1])(p);
    }
    if (self[3]) {
        int* p = (int*)self[3];
        self[3] = 0;
        void** vt = *(void***)p;
        ((void(__thiscall*)(void*))vt[1])(p);
    }
}

// @ 0x007aa3a0
char JobSlots::Transfer(int param_2)
{
    int self = (int)this;
    int* a = *(int**)(self + 0xc);
    if (a && *(int*)(self + 8) == 0) {
        int* b = *(int**)(self + 8);
        if (b) {
            *(int*)(self + 8) = 0;
            void** vt = *(void***)b;
            ((void(__thiscall*)(void*))vt[1])(b);
        }
        void** vt = *(void***)a;                            // slot 5 with &self[2]
        ((void(__thiscall*)(void*, int*))vt[0x14 / 4])(a, (int*)(self + 8));
    }
    int* c = *(int**)(self + 0xc);
    if (c) {
        *(int*)(self + 0xc) = 0;
        void** vt = *(void***)c;
        ((void(__thiscall*)(void*))vt[1])(c);
    }
    int* d = *(int**)(self + 8);
    if (d && d[6]) {
        void (*cb)(int) = *(void(**)(int))(param_2 + 0x24);
        int old = *(int*)(param_2 + 0x20);
        *(int*)(param_2 + 0x20) = d[6];
        *(int*)(param_2 + 0x24) = 0;
        if (cb) cb(old);
        return 1;
    }
    return 0;
}

// ---- texture-manager / job subsystem layouts --------------------------------
// a job-slot container: four intrusive references (slot0 refcounts at +0x10,
// slot1 is a cJob released through 0x00690120, slot2/slot3 release through vtable[1]).
struct JobSlotGroup {
    void* mSlot0;                   // +0x00
    void* mSlot1;                   // +0x04
    void* mSlot2;                   // +0x08
    void* mSlot3;                   // +0x0c
};

// the cJob object a slot points at (the slot stores &job->mField08).
struct JobObject {
    void*         mpVT;             // +0x00
    int           mField04;         // +0x04
    void*         mField08;         // +0x08
    unsigned char mState0C;         // +0x0c
    unsigned char mPad0D[3];
    void*         mField10;         // +0x10
    void*         mField14;         // +0x14
    void*         mField18;         // +0x18
    int           mField1C;         // +0x1c
    void*         mField20;         // +0x20
    void*         mField24;         // +0x24
    unsigned char mFlags28;         // +0x28
    unsigned char mPad29[3];
    void*         mField2C;         // +0x2c
};

// the object 007aa530 / 007aaa00 run on ("this" in ecx).
struct TextureJob {
    void** mpVT;                    // +0x00
    int    mField04;                // +0x04
    void*  mField08;                // +0x08
    void*  mField0C;                // +0x0c
    void*  mField10;                // +0x10
};

// eastl::hashtable (insert target of 007aa710).
struct RehashResult { bool doRehash; unsigned newBucketCount; };
struct HashTable {
    int      mField00;              // +0x00
    void**   mTable;                // +0x04
    unsigned mBucketCount;          // +0x08
    unsigned mCount;                // +0x0c
    int      mPolicy[4];            // +0x10
};

// job descriptor handed to the job manager (0x007aaa00's stack local).
struct JobDesc {
    int           mField00;         // +0x00
    int           mField04;         // +0x04
    unsigned char mFlag08;          // +0x08  (only this byte is written)
    unsigned char mPad09;           // +0x09  (left uninitialised, as in the original)
    unsigned char mPad0A;           // +0x0a
    unsigned char mPad0B;           // +0x0b
    int           mField0C;         // +0x0c
    int           mField10;         // +0x10
    int           mField14;         // +0x14
    int           mField18;         // +0x18
    int           mField1C;         // +0x1c
    int           mField20;         // +0x20
    int           mField24;         // +0x24
    int           mField28;         // +0x28
};

static inline void AddRef(void* p)  { if (p) ((FnV0)(*(void***)p)[0])(p); }
static inline void Release(void* p) { if (p) ((FnV0)(*(void***)p)[1])(p); }
static inline void ReleaseAt10(void* p)
{
    if (!p) return;
    volatile long* rc = (volatile long*)((char*)p + 0x10);
    _InterlockedExchangeAdd(rc, -1);
    long cur = _InterlockedExchangeAdd(rc, 0);
    if (cur < 1) _InterlockedExchangeAdd(rc, 1); else _InterlockedExchangeAdd(rc, 0);
}

// @ 0x007aa430  commit a pending job into the editor slot
extern "C" void __fastcall FUN_007aa430(TexManager* self, int dummy, JobSlotGroup* slots)
{
    (void)dummy;
    JobObject* job = (JobObject*)slots->mSlot0;
    if (!(job->mState0C & 1)) {
        void* ed = slots->mSlot1;
        void* p = 0;
        if (ed) {
            ((FnV0)FUN_006926b0_Cancel)(ed);
            p = *(void**)((char*)slots->mSlot1 + 0x20);
        }
        if (p) {
            if (!(job->mFlags28 & 4)) {
                void* q = *(void**)((char*)p + 4);
                if (((unsigned char)(unsigned)q & 0x1f) == 8) {
                    void* r = *(void**)((char*)p + 8);
                    ((FnV2)(*(void***)r)[11])(r, self->mFieldCC, (int)q);
                }
            }
            job->mField08 = p;
            void* nv = slots->mSlot2;
            void* ov = job->mField24;
            if (nv != ov) {
                AddRef(nv);
                job->mField24 = nv;
                Release(ov);
            }
            if (!(job->mFlags28 & 8)) {
                void* t = slots->mSlot2;
                int arg = t ? ((FnI1)(*(void***)t)[3])(t, 0x355d6f5) : 0;
                FUN_006ac040_SetCachingType(5, (void*)arg);
            }
        } else {
            job->mField08 = self->mField10;
            job->mState0C |= 4;
        }
        job->mState0C |= 1;
    }
    {
        void* r = job->mField2C;
        if (r) {
            ((FnV0)FUN_006909b0_Refresh)(r);
            r = job->mField2C;
            if (r) { job->mField2C = 0; ((FnV0)FUN_00690_120_GetStatus)(r); }
        }
    }
    ((JobSlots*)slots)->Clear();
}

// @ 0x007aa530  publish a new texture job to the item manager and message manager
extern "C" void __fastcall FUN_007aa530(TextureJob* self, int dummy, int a1, int a2, int a3, int a4)
{
    (void)dummy; (void)a1; (void)a2; (void)a3; (void)a4;
    void* f8 = self->mField08;
    void* x;
    if (f8) {
        if (!(*(unsigned char*)((char*)f8 + 4) & 1)) {
            void* im0 = FUN_0067dd60();
            ((FnVP)(*(void***)im0)[13])(im0, f8);
        }
        x = *(void**)f8;
    } else {
        x = self->mField0C;
    }
    void* tmp = 0;
    void* im = FUN_0067dd60();
    Release(tmp);
    ((void(__thiscall*)(void*, void*, void*, int, int))(*(void***)im)[22])(im, x, &tmp, 0, 0);
    void* f10 = self->mField10;
    void* t = tmp;
    if ((*(int*)((char*)f10 + 0x38) & 1) && *(void**)((char*)f10 + 8))
        Release(*(void**)((char*)f10 + 8));
    *(void**)((char*)f10 + 8) = t;
    AddRef(t);
    *(int*)((char*)f10 + 0x38) |= 1;
    *(void**)((char*)f10 + 0x20) = x;
    void* mm = FUN_0067dcc0();
    void* f10b = self->mField10;
    ((void(__thiscall*)(void*, void*, void*, int, int))(*(void***)mm)[6])(
        mm, *(void**)((char*)f10b + 0x30), f10b, 0, 0);
    Release(tmp);
}

// @ 0x007aa620
struct Empty16 { int a, b, c, d; Empty16(); };
Empty16::Empty16()
{
    Empty16* self = this;
    self->a = 0; self->b = 0; self->c = 0; self->d = 0;
}

// @ 0x007aa660  release every reference held by a job-slot container (destructor tail)
extern "C" void __fastcall FUN_007aa660(JobSlotGroup* self, int dummy)
{
    (void)dummy;
    Release(self->mSlot3);
    Release(self->mSlot2);
    if (self->mSlot1) ((FnV0)FUN_00690_120_GetStatus)(self->mSlot1);
    ReleaseAt10(self->mSlot0);
}

// @ 0x007aa710  eastl::hashtable::insert(out, key, unused) -- find-or-insert by key.
// The original returns the `out` slot pointer in eax (it falls out of both paths).
extern "C" void* __fastcall FUN_007aa710(HashTable* self, int dummy, int* out, int* key, int unused)
{
    (void)dummy; (void)unused;
    unsigned k = (unsigned)*key;
    unsigned idx = k % self->mBucketCount;
    void* node = self->mTable[idx];
    while (node) {
        if (*(unsigned*)node == k) {
            out[0] = (int)node;
            out[1] = (int)&self->mTable[idx];
            ((unsigned char*)out)[8] = 0;
            return out;
        }
        node = *(void**)((char*)node + 4);
    }
    RehashResult rr;
    rr.doRehash = false; rr.newBucketCount = 0;
    ((void(__thiscall*)(void*, void*, int, int, int))FUN_00921440_Needed)(
        &self->mPolicy, &rr, (int)self->mBucketCount, (int)self->mCount, 1);
    void* n = EASTL_allocator_allocate(8, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if (n) *(unsigned*)n = k;
    *(void**)((char*)n + 4) = 0;
    if (rr.doRehash) {
        idx = k % rr.newBucketCount;
        ((void(__thiscall*)(void*, int))FUN_007a99d0_Rehash)(self, (int)rr.newBucketCount);
    }
    *(void**)((char*)n + 4) = self->mTable[idx];
    self->mTable[idx] = n;
    self->mCount++;
    out[0] = (int)n;
    out[1] = (int)&self->mTable[idx];
    ((unsigned char*)out)[8] = 1;
    return out;
}

struct FixedAllocatorBase { bool AddCore(int, int); };

// @ 0x007aa800  SP::cNodeAllocator<...>::Create
Chunk* cNodeAllocator::Create()
{
    while (this->mpHeadChunk == 0) {
        if (!((FixedAllocatorBase*)this)->AddCore(0, 0))
            return 0;
    }
    Chunk* p = this->mpHeadChunk;
    this->mpHeadChunk = p->mpNext;
    *(int*)((char*)p + 4) = 0;
    *(int*)((char*)p + 0) = 0;
    *(int*)((char*)p + 8) = 0;
    *(unsigned char*)((char*)p + 0xc) = 0;
    _InterlockedExchange(&p->mRef, 1);          // retail: xchg [p+0x10], 1 (not add)
    *(int*)((char*)p + 0x18) = 0;
    *(int*)((char*)p + 0x1c) = 0;
    *(int*)((char*)p + 0x20) = 0;
    *(int*)((char*)p + 0x24) = 0;
    *(int*)((char*)p + 0x2c) = 0;
    return p;
}

// @ 0x007aa850  deque push_back with block allocation
void DequeMap::PushBack(int* value)
{
    int* self = (int*)this;
    int v = *value;
    if (self[1] <= ((self[9] - *self) >> 2) + 1)
        ((DequeMap*)self)->InsertAt(1, 1);
    int* buf = (int*)EASTL_allocator_allocate(0x100, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    *(int*)(self[9] + 4) = (int)buf;
    if (self[6]) *(int*)self[6] = v;
    int t = self[9];
    self[9] = t + 4;
    int base = *(int*)(t + 4);
    self[7] = base;
    self[8] = base + 0x100;
    self[6] = self[7];
}

// @ 0x007aaa00  build a job descriptor and submit it to the job manager.
// Stack arguments (ret 0x10): slot pointer, ref argument, flag byte, kind.
// The PDB symbol is ?FUN_007aaa00@@YAXPAH@Z (void return); the `mov al,1` the
// compiler leaves on the success path is incidental.
extern "C" void __fastcall FUN_007aaa00(TextureJob* self, int dummy, JobSlotGroup* slots,
                                        void* refArg, int flag, int kind)
{
    (void)dummy;
    JobObject* obj = slots ? (JobObject*)((char*)slots - 8) : 0;
    if (!(unsigned char)flag) {
        if (!(obj->mState0C & 1))
            ((FnVP)(*(void***)self)[13])(self, (char*)obj + 8);
        ((void(__thiscall*)(void*, void*, void*, int, int))(*(void***)self)[22])(
            self, *(void**)((char*)obj + 8), refArg, 0, 0);
        return;
    }
    if (!kind) kind = 0x522264d;
    void* j = EASTL_allocator_allocate(0x40, "Graphics", 0, 0, 0, 0);
    if (j) {
        *(int*)((char*)j + 0x30) = kind;
        *(void**)j = (void*)0x13eb90c;
        _InterlockedExchange((volatile long*)((char*)j + 4), 0);
        *(void**)j = (void*)0x13eb844;
        *(int*)((char*)j + 0x38) = 0;
    }
    *(void**)((char*)j + 0x10) = *(void**)((char*)obj + 0x20);
    *(void**)((char*)j + 0x18) = *(void**)((char*)obj + 0x18);
    void* k = EASTL_allocator_allocate(0x14, "Graphics", 0, 0, 0, 0);
    if (k) {
        *(void**)k = (void*)0x140faa8;
        _InterlockedExchange((volatile long*)((char*)k + 4), 0);
        *(void**)k = (void*)0x140fab8;
        *(int*)((char*)k + 8) = 0;
        *(int*)((char*)k + 0xc) = 0;
        *(int*)((char*)k + 0x10) = 0;
    }
    AddRef(k);
    {
        void* ov = *(void**)((char*)k + 0x10);
        if (j != ov) {
            Release(j);
            *(void**)((char*)k + 0x10) = j;
            if (ov) ((FnV0)(*(void***)ov)[2])(ov);
        }
    }
    ((void(__thiscall*)(void*, void*))FUN_00576650_Assign)((char*)k + 8, slots);
    *(int*)((char*)k + 0xc) = 0;
    {
        JobDesc desc;
        desc.mField00 = 4;
        desc.mField04 = 0;
        desc.mFlag08  = 1;
        desc.mField0C = 0;
        desc.mField10 = 0;
        desc.mField14 = 0;
        desc.mField18 = 0;
        desc.mField1C = 0;
        desc.mField20 = 0;
        desc.mField24 = 0;
        desc.mField28 = 0;
        void* jm = FUN_0067dd50();
        ((void(__thiscall*)(void*, void*, int, void*))(*(void***)jm)[0x78 / 4])(jm, k, 0, &desc);
    }
    Release(k);
}

// @ 0x007aa0d0  attach a texture-load dependency job to a job slot
extern "C" bool __fastcall FUN_007aa0d0(TexManager* self, int dummy, JobSlotGroup* slots, void* mgr)
{
    (void)dummy;
    JobObject* obj = slots ? (JobObject*)((char*)slots - 8) : 0;
    if (obj->mState0C & 1) return true;
    void* dep = obj->mField2C;
    if (dep) {
        ((FnVP)FUN_006913c0_AddWeakDep)(mgr, dep);
        return true;
    }
    void* job = 0;
    void* jm = FUN_0068f4d0();
    if (job) Release(job);
    if (!((FnB1)(*(void***)jm)[4])(jm, &job)) {
        Release(job);
        return false;
    }
    ((FnV1)FUN_009221b0_Lock)(&self->mMutex, 0x140fa10);
    if (!obj->mField2C && !(obj->mState0C & 1))
        ((void(__thiscall*)(void*, void*))FUN_00630540_Assign)(&obj->mField2C, job);
    ((FnV0)FUN_00922270_Unlock)(&self->mMutex);
    if (!(obj->mState0C & 1)) {
        void* d = obj->mField2C;
        if (!d) { Release(job); return false; }
        ((FnVP)FUN_006913c0_AddWeakDep)(mgr, d);
    }
    Release(job);
    return true;
}

// @ 0x007aa200  reload a texture job's backing object from the resource factory
extern "C" bool __fastcall FUN_007aa200(TexManager* self, int dummy, JobSlotGroup* slots)
{
    (void)dummy;
    JobObject* obj = slots ? (JobObject*)((char*)slots - 8) : 0;
    void* old = obj->mField24;
    if (!old) return false;
    int s08 = *(int*)((char*)old + 8);
    int s0C = *(int*)((char*)old + 0xc);
    int s10 = *(int*)((char*)old + 0x10);
    (void)s08; (void)s0C; (void)s10;
    void* saved = obj->mField24;
    obj->mField24 = 0;
    void* factory = FUN_0067dcd0();
    Release(obj->mField24);
    if (((bool(__thiscall*)(void*, void*, void*, int, int, int, int))(*(void***)factory)[3])(
            factory, &obj->mField24, 0, 0, 0, 0, 0)) {
        ((FnV1)FUN_009221b0_Lock)(&self->mMutex, 0x140fa10);
        void* nv = obj->mField24;
        obj->mField08 = *(void**)((char*)nv + 0x18);
        ((FnV0)FUN_00922270_Unlock)(&self->mMutex);
        Release(saved);
        return true;
    }
    obj->mField24 = saved;
    return false;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
