// Slice s007d67e0 (batch w2g5): EASTL vector/copy helpers for
// SP::cSplitManager::cSplitInstanceList and EA::Swarm::cEffectParams, plus the
// cSplitManager::AddSplitInstance method and a Swarm effect method.
// Retail module flags: /O2 /MD /Gy /EHsc /TP   (007d6c10 additionally needs /arch:SSE)
#include "types.h"
#include <math.h>

typedef unsigned int size_type;
typedef int ptrdiff_t;

// ---------------------------------------------------------------------------
// EA allocator / operator new (masked relocations; any declaration works).
// ---------------------------------------------------------------------------
#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define ALLOC_NAME "App"

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
void operator delete(void* p);
inline void* operator new(size_t, void* p) { return p; }

// the real EA allocator symbols (relocations are masked)
void ea_free(void* p);                                   // 0x00f47380

// ---------------------------------------------------------------------------
// helpers defined in neighbouring slices (relocations masked).
// ---------------------------------------------------------------------------
struct cElement;
cElement* AllocElementArray(size_type n, cElement* first, cElement* last);          // 0x007d61f0
cElement* AssignElements(cElement* dest, cElement* destEnd, const cElement* src);   // 0x007d6250
cElement* UninitCopyElements(cElement* first, cElement* last, cElement* dest, void* alloc); // 0x007d5aa0
void      DestroyElementRange(cElement* first, cElement* last);                     // 0x007d4940
void      ResizeFloatVector(void* vec, int n);                                      // 0x007d65a0
void      Sub_7d5e60(void* self);                                                   // 0x007d5e60
int       Sub_79ff40(void* list, const void* value);                                // 0x0079ff40 (cSplitInstanceList::insert)
void      Sub_7d7280(void* first, void* last);                                      // 0x007d7280 (erase)
void      Sub_478db0(int value);                                                    // 0x00478db0
int       Sub_79ac10(int a, int b, int c);                                          // 0x0079ac10
void      Sub_007d4a40(void* out, int a, void* xform, int b);                       // 0x007d4a40
void*     RandomLCG_Swarm();                                                        // returns &sRandom
double    RandomDoubleUniform(void* rng);                                           // 0x009360d0

// ---------------------------------------------------------------------------
// types
// ---------------------------------------------------------------------------
struct cSPVector3 { float x, y, z; };
struct cSPMatrix3 { float m[9]; };
struct cSPTransform {                    // size 0x38
    unsigned short mFlags;               // +0x00
    unsigned short mModificationCount;   // +0x02
    cSPVector3     mTranslation;         // +0x04
    float          mScale;               // +0x10
    cSPMatrix3     mRotation;            // +0x14
};
struct cSplitInstance {                  // size 0x74
    unsigned char mFlags;                // +0x00
    char _pad[3];
    cSPTransform  mInstanceTransform;    // +0x04
    cSPTransform  mFinalTransform;       // +0x3c
    cSplitInstance(int a, const cSPTransform& x, int b);   // @ 0x007d4a40 (defined in slice s007d4a40)
};
struct cElement {                        // size 0x78
    int           mNextFree;             // +0x00
    cSplitInstance mData;                // +0x04
};

// eastl::vector<cElement, sp_vector_allocator> viewed as three pointers.
struct CElementVector {
    cElement* mpBegin;    // +0x00
    cElement* mpEnd;      // +0x04
    cElement* mpCapacity; // +0x08
    CElementVector& operator=(const CElementVector& x);   // @ 0x007d7080
};

// SP::cSplitManager::cSplitInstanceList (retail stride 0x1c).
struct cSplitInstanceList {
    int             mNextFree;      // +0x00
    CElementVector  mDataArray;     // +0x04
    int             mUnk10;         // +0x10
    int             mUnk14;         // +0x14
    int             mExtra;         // +0x18

    cSplitInstanceList()
        : mNextFree(-1), mUnk10(0), mUnk14(0), mExtra(0)
    { mDataArray.mpBegin = 0; mDataArray.mpEnd = 0; mDataArray.mpCapacity = 0; }

    __forceinline cSplitInstanceList(const cSplitInstanceList& x);  // inline deep copy
    int insert(const cSplitInstance& value);              // @ 0x0079ff40 (defined in slice s007d4a40)
    ~cSplitInstanceList();                                // inline element teardown
};

__forceinline cSplitInstanceList::cSplitInstanceList(const cSplitInstanceList& x) {
    mNextFree = x.mNextFree;
    const size_type nBytes = (size_type)((char*)x.mDataArray.mpEnd - (char*)x.mDataArray.mpBegin);
    const size_type nCount = nBytes / sizeof(cElement);
    cElement* buf = nCount
        ? (cElement*)operator new[](nCount * sizeof(cElement), ALLOC_NAME, 0, 0, ALLOC_FILE, 0xd1)
        : 0;
    mDataArray.mpBegin = buf;
    mDataArray.mpEnd = buf;
    mDataArray.mpCapacity = buf + nCount;
    mDataArray.mpEnd = UninitCopyElements(x.mDataArray.mpBegin, x.mDataArray.mpEnd, buf,
                                          (void*)((char*)x.mDataArray.mpBegin + 0xc));
    mExtra = x.mExtra;
}

inline cSplitInstanceList::~cSplitInstanceList() {
    if (mDataArray.mpBegin != 0) {
        DestroyElementRange(mDataArray.mpBegin, mDataArray.mpEnd);
        if (((int*)mDataArray.mpBegin)[-1] != 0)
            ea_free(mDataArray.mpBegin);
    }
}

// A cSplitInstanceList vector (mSplitClientList), only begin/end/cap used.
struct ListVector {
    cSplitInstanceList* mpBegin;
    cSplitInstanceList* mpEnd;
    cSplitInstanceList* mpCapacity;
    void DoInsertValues(cSplitInstanceList* position, size_type n, const cSplitInstanceList& value); // @ 0x007d72e0
    void resize(size_type n);                                                                         // @ 0x007d7560
};

// ---------------------------------------------------------------------------
// 0x007d7080  eastl::vector<cElement,sp_vector_allocator>::operator=
// ---------------------------------------------------------------------------
// @ 0x007d7080
CElementVector& CElementVector::operator=(const CElementVector& x) {
    if (this != &x) {
        size_type n = (size_type)(x.mpEnd - x.mpBegin);
        if ((size_type)(mpCapacity - mpBegin) < n) {
            cElement* pNew = AllocElementArray(n, x.mpBegin, x.mpEnd);
            if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
                ea_free(mpBegin);
            mpBegin = pNew;
            mpCapacity = pNew + n;
        } else if ((size_type)(mpEnd - mpBegin) < n) {
            size_type nOld = (size_type)(mpEnd - mpBegin);
            AssignElements(mpBegin, mpBegin + nOld, x.mpBegin);
            UninitCopyElements(x.mpBegin + nOld, x.mpEnd, mpEnd, mpEnd);
        } else {
            AssignElements(mpBegin, x.mpEnd, x.mpBegin);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// ---------------------------------------------------------------------------
// 0x007d67e0  uninitialized_copy of cSplitInstanceList into a caller pointer
// ---------------------------------------------------------------------------
// @ 0x007d67e0
cSplitInstanceList** CopyConstructToPtr(cSplitInstanceList** pDest, const cSplitInstanceList* first,
                                        const cSplitInstanceList* last, cSplitInstanceList* dest) {
    *pDest = dest;
    for (; first != last; ++first) {
        ::new (*pDest) cSplitInstanceList(*first);
        *pDest += 1;
    }
    return pDest;
}

// ---------------------------------------------------------------------------
// 0x007d68f0  uninitialized_fill_n of cSplitInstanceList
// ---------------------------------------------------------------------------
// @ 0x007d68f0
void FillConstructN(cSplitInstanceList* dest, size_type n, const cSplitInstanceList* value) {
    for (; n != 0; --n, ++dest)
        ::new (dest) cSplitInstanceList(*value);
}

// ---------------------------------------------------------------------------
// 0x007d69f0  uninitialized_copy of cSplitInstanceList
// ---------------------------------------------------------------------------
// @ 0x007d69f0
cSplitInstanceList* CopyConstructRange(const cSplitInstanceList* first, const cSplitInstanceList* last,
                                       cSplitInstanceList* dest) {
    for (; first != last; ++first, ++dest)
        ::new (dest) cSplitInstanceList(*first);
    return dest;
}

// ---------------------------------------------------------------------------
// 0x007d6b00  EA::Swarm::cEffectParams::operator=
// ---------------------------------------------------------------------------
struct cParamRec { unsigned short mOffset; unsigned short mCount; };

struct IUnknown32 { void** vftable; };
struct AutoRefCountIUnknown {
    IUnknown32* mpObject;
    AutoRefCountIUnknown& operator=(const AutoRefCountIUnknown& x) {
        if (mpObject != x.mpObject) {
            if (x.mpObject != 0)
                ((void(__thiscall*)(IUnknown32*))x.mpObject->vftable[0])(x.mpObject);
            IUnknown32* pOld = mpObject;
            mpObject = x.mpObject;
            if (pOld != 0)
                ((void(__thiscall*)(IUnknown32*))pOld->vftable[1])(pOld);
        }
        return *this;
    }
};

struct FloatVec { float* mpBegin; float* mpEnd; float* mpCapacity; int mAlloc; FloatVec& operator=(const FloatVec&); };
struct IntVec   { int*   mpBegin; int*   mpEnd; int*   mpCapacity; int mAlloc; IntVec& operator=(const IntVec&); };

struct cEffectParams {                    // retail size 0xd8 (dev PDB 0xcc)
    cParamRec mFloatParams[25];           // +0x00
    FloatVec  mFloatParamStorage;         // +0x64
    char      mPad74[4];                  // +0x74
    cParamRec mIntParams[9];              // +0x78
    int       mUnk9c;                     // +0x9c
    IntVec    mIntParamStorage;           // +0xa0
    char      mPadB0[4];                  // +0xb0
    AutoRefCountIUnknown mUnknownParams[9]; // +0xb4
    cEffectParams& operator=(const cEffectParams& x);
};

// @ 0x007d6b00
cEffectParams& cEffectParams::operator=(const cEffectParams& x) {
    for (int i = 0; i < 25; ++i)
        mFloatParams[i] = x.mFloatParams[i];
    mFloatParamStorage = x.mFloatParamStorage;
    for (int i = 0; i < 9; ++i)
        mIntParams[i] = x.mIntParams[i];
    mUnk9c = x.mUnk9c;
    mIntParamStorage = x.mIntParamStorage;
    for (int i = 0; i < 9; ++i)
        mUnknownParams[i] = x.mUnknownParams[i];
    return *this;
}

// ---------------------------------------------------------------------------
// 0x007d71b0  copy (assignment flavour) of cSplitInstanceList forward
// ---------------------------------------------------------------------------
// @ 0x007d71b0
cSplitInstanceList* CopyAssignForward(const cSplitInstanceList* first, const cSplitInstanceList* last,
                                      cSplitInstanceList* dest) {
    for (; first != last; ++first, ++dest) {
        dest->mNextFree = first->mNextFree;
        dest->mDataArray = first->mDataArray;
        dest->mExtra = first->mExtra;
    }
    return dest;
}

// ---------------------------------------------------------------------------
// 0x007d71f0  copy (assignment flavour) of cSplitInstanceList backward
// ---------------------------------------------------------------------------
// @ 0x007d71f0
cSplitInstanceList* CopyAssignBackward(const cSplitInstanceList* first, const cSplitInstanceList* last,
                                       cSplitInstanceList* dest) {
    while (last != first) {
        --last;
        --dest;
        dest->mNextFree = last->mNextFree;
        dest->mDataArray = last->mDataArray;
        dest->mExtra = last->mExtra;
    }
    return dest;
}

// ---------------------------------------------------------------------------
// 0x007d7240  assign a value across an uninitialized range
// ---------------------------------------------------------------------------
// @ 0x007d7240
void AssignValueRange(cSplitInstanceList* first, cSplitInstanceList* last, const cSplitInstanceList* value) {
    for (; first != last; ++first) {
        first->mNextFree = value->mNextFree;
        first->mDataArray = value->mDataArray;
        first->mExtra = value->mExtra;
    }
}

// ---------------------------------------------------------------------------
// 0x007d72e0  vector<cSplitInstanceList>::DoInsertValues
// ---------------------------------------------------------------------------
// @ 0x007d72e0
void ListVector::DoInsertValues(cSplitInstanceList* position, size_type n, const cSplitInstanceList& value) {
    if (n > (size_type)(mpCapacity - mpEnd)) {
        const size_type nPrevSize = (size_type)(mpEnd - mpBegin);
        const size_type nPositionIndex = (size_type)(position - mpBegin);
        size_type nNewCapacity = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        const size_type nNewSize = nPrevSize + n;
        if (nNewSize > nNewCapacity)
            nNewCapacity = nNewSize;
        cSplitInstanceList* pNewData = (cSplitInstanceList*)
            operator new[](nNewCapacity * sizeof(cSplitInstanceList), ALLOC_NAME, 0, 0, ALLOC_FILE, 0xd1); // 0x00f473a0
        cSplitInstanceList* pNewEnd = CopyConstructRange(mpBegin, position, pNewData);
        FillConstructN(pNewEnd, n, &value);
        cSplitInstanceList* pNewEnd2 = CopyConstructRange(position, mpEnd, pNewEnd + n);
        DestroyElementRange((cElement*)mpBegin, (cElement*)position);
        DestroyElementRange((cElement*)position, (cElement*)mpEnd);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            ea_free(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd2;
        mpCapacity = pNewData + nNewCapacity;
    } else if (n != 0) {
        cSplitInstanceList tmp(value);
        const size_type nElemsAfter = (size_type)(mpEnd - position);
        if (n < nElemsAfter) {
            cSplitInstanceList* pOldEnd = mpEnd;
            cSplitInstanceList* pSplit = mpEnd - n;
            CopyConstructToPtr(&pOldEnd, pSplit, mpEnd, mpEnd);
            mpEnd = mpEnd + n;
            CopyAssignBackward(position, pSplit, pOldEnd);
            AssignValueRange(position, position + n, &tmp);
        } else {
            FillConstructN(mpEnd, n - nElemsAfter, &tmp);
            cSplitInstanceList* pOldEnd = mpEnd;
            mpEnd = mpEnd + (n - nElemsAfter);
            CopyConstructToPtr(&pOldEnd, position, pOldEnd, mpEnd);
            mpEnd = mpEnd + nElemsAfter;
            AssignValueRange(position, pOldEnd, &tmp);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x007d7560  vector<cSplitInstanceList>::resize
// ---------------------------------------------------------------------------
// @ 0x007d7560
void ListVector::resize(size_type n) {
    const size_type nSize = (size_type)(mpEnd - mpBegin);
    if (n > nSize) {
        cSplitInstanceList value;
        DoInsertValues(mpEnd, n - nSize, value);
    } else {
        Sub_7d7280(mpBegin + n, mpEnd);
    }
}

// ---------------------------------------------------------------------------
// 0x007d7640  SP::cSplitManager::AddSplitInstance
// ---------------------------------------------------------------------------
struct cSplitInstanceRef { int mSplitID; int mKey; };

struct cSplitManager {
    char            pad00[4];
    int             mRefCount;              // +0x04
    cSPTransform    mComponentTransform;    // +0x08
    ListVector      mSplitClientList;       // +0x40
    void AddSplitInstance(cSplitInstanceRef* out, int index, int a, int b); // @ 0x007d7640
};

// @ 0x007d7640
void cSplitManager::AddSplitInstance(cSplitInstanceRef* out, int index, int a, int b) {
    ListVector& list = mSplitClientList;
    if ((int)(list.mpEnd - list.mpBegin) <= index)
        list.resize((size_type)index + 1);
    cSplitInstanceList* pList = list.mpBegin + index;
    int key = pList->insert(cSplitInstance(a, mComponentTransform, b));
    out->mSplitID = index;
    out->mKey = key;
}

// ---------------------------------------------------------------------------
// 0x007d6c10  Swarm effect method (random sample setup)
// ---------------------------------------------------------------------------
struct cSwarmParams {
    char     pad00[0x0c];
    unsigned mFlags;          // +0x0c
    char     pad10[0x20];
    int*     mV30;            // +0x30
    int*     mV34;            // +0x34
    char     pad38[0x34];
    int*     mV6c;            // +0x6c
    int*     mV70;            // +0x70
    char     pad74[0x0c];
    unsigned mFlags80;        // +0x80
    unsigned char mByte84;    // +0x84
};

struct cSwarmThis {
    void**   vftable;         // +0x00
    char     pad04[0x08];
    cSwarmParams* mParams;    // +0x0c
    char     pad10[0x04];
    unsigned char mFlag14;    // +0x14
    unsigned char mFlag15;    // +0x15
    unsigned char mFlag16;    // +0x16
    char     pad17;
    int      mArg18;          // +0x18
    int      mArg1c;          // +0x1c
    char     pad20[0x10];
    float    mFloat30;        // +0x30
    char     pad34[0x04];
    void*    mRec;            // +0x38
    unsigned short mCount3e;  // +0x3e
    float    mF40;            // +0x40
    float    mF44;            // +0x44
    float    mF48;            // +0x48
    float    mF4c;            // +0x4c
    char     pad50[0x40];
    void*    mFloatVec;       // +0x90
    char     pad94[0x10];
    int*     mA4;             // +0xa4
    int*     mA8;             // +0xa8
    char*    mB0;             // +0xac  (begin of 0x40-byte records)
    char*    mB4;             // +0xb0
    char     padB4[0x0c];
    IUnknown32* mC0;          // +0xc0
    IUnknown32* mC4;          // +0xc4

    void Sub_7d6c10(int arg);
};

// @ 0x007d6c10
void cSwarmThis::Sub_7d6c10(int arg) {
    cSwarmParams* params = mParams;
    if (mC4 != 0 && mRec == 0) {
        unsigned local = 0;
        if (params->mV30 == params->mV34)
            local = 1;
        else if (1 < (unsigned)((int)((char*)params->mV34 - (char*)params->mV30) / 0x2c))
            local = 2;
        if ((params->mFlags >> 5) & 1)
            local |= 8;
        int r = ((int(__thiscall*)(IUnknown32*, int, int, int))mC4->vftable[3])(mC4, mArg18, mArg1c, local);
        Sub_478db0(r);
        void* rec = mRec;
        mFlag16 = 0;
        if (rec != 0) {
            if (mFlag15 == 0)
                *(unsigned*)((char*)rec + 4) &= ~1u;
            else
                *(unsigned*)((char*)rec + 4) |= 1u;
            if ((params->mFlags >> 4) & 1) {
                float dx = *(float*)((char*)rec + 0x7c) - *(float*)((char*)rec + 0x70);
                float dy = *(float*)((char*)rec + 0x80) - *(float*)((char*)rec + 0x74);
                float dz = *(float*)((char*)rec + 0x84) - *(float*)((char*)rec + 0x78);
                float d = (float)sqrt((double)(dx * dx + dy * dy + dz * dz));
                d *= *(float*)((char*)rec + 0x18);
                if (0.0f < d) {
                    d = mFloat30 / d;
                    mFloat30 = d;
                    mCount3e = (unsigned short)(mCount3e + 1);
                    mF4c = d;
                }
            }
            if (mA4 != 0) {
                ((void(__thiscall*)(IUnknown32*, void*))mC4->vftable[0x58 / 4])(mC4, rec);
                int v = Sub_79ac10((int)mA4, (int)mA8, 1);
                ((void(__thiscall*)(IUnknown32*, void*, int))mC4->vftable[0xac / 4])(mC4, rec, v);
            }
            unsigned h = ((unsigned(__thiscall*)(IUnknown32*, unsigned, int))mC0->vftable[0x28 / 4])(mC0, 0x73cb32c9, 0);
            if (h < 0x40) {
                unsigned* w = (unsigned*)((char*)rec + 0x44 + (h >> 5) * 4);
                *w |= 1u << (h & 0x1f);
            }
            if (params->mV6c != params->mV70) {
                int cnt = (int)((char*)params->mV70 - (char*)params->mV6c) >> 2;
                for (int i = 0; i < cnt; ++i) {
                    unsigned hh = ((unsigned(__thiscall*)(IUnknown32*, int, int))mC0->vftable[0x28 / 4])(mC0, params->mV6c[i], 0);
                    if (hh < 0x40) {
                        unsigned* w = (unsigned*)((char*)rec + 0x44 + (hh >> 5) * 4);
                        *w |= 1u << (hh & 0x1f);
                    }
                }
            }
            *(unsigned*)((char*)rec + 4) |= params->mFlags80;
            *(unsigned char*)((char*)rec + 0x5d) = (unsigned char)params->mByte84;
            void** rvt = *(void***)rec;
            ((void(__thiscall*)(void*, int))rvt[0x16c / 4])(rec, 0);
        }
    }
    if ((params->mFlags >> 3) & 1)
        Sub_7d5e60(this);
    if (mFlag14 == 0 && mRec != 0) {
        mFlag14 = 1;
        int n = (int)(mB4 - mB0) >> 6;
        for (int i = 0; i < n; ++i) {
            void* o = *(void**)(mB0 + i * 0x40 + 0x3c);
            ((void(__thiscall*)(void*, int))((*(void***)o)[2]))(o, arg);
        }
        int cnt = (int)((char*)params->mV34 - (char*)params->mV30) / 0x2c;
        ResizeFloatVector(&mFloatVec, cnt);
        if (cnt != 0) {
            float* out = (float*)mFloatVec;
            int i = 0;
            int off = 0;
            int remaining = cnt;
            do {
                out[i] = 0.0f;
                float* p = (float*)((char*)params->mV30 + off);
                float lo = p[0];
                float hi = p[1];
                double r = RandomDoubleUniform(RandomLCG_Swarm());
                float v = (float)(r * (double)(hi - lo) + (double)lo);
                if (v >= hi) v = hi;
                else if (v < lo) v = lo;
                if (v <= 0.0f) out[i + 1] = 0.0f;
                else out[i + 1] = 1.0f / v;
                float c = *(float*)((char*)params->mV30 + off + 0x1c);
                double r2 = RandomDoubleUniform(RandomLCG_Swarm());
                float upper = c + 1.0f;
                float lower = 1.0f - c;
                float v2 = (float)(r2 * (double)(upper - lower) + (double)lower);
                if (v2 >= upper) v2 = upper;
                else if (v2 < lower) v2 = lower;
                off += 0x2c;
                out[i + 2] = v2;
                i += 3;
            } while (--remaining);
        }
        *(float*)((char*)this + 0x74) = mF40;
        *(float*)((char*)this + 0x78) = mF44;
        *(float*)((char*)this + 0x7c) = mF48;
    }
}
// --- equivalence checker address annotations
    void* operator new[](unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
