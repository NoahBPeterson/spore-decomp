// Slice s007d2a30.  Region flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE2
//
// SWARM game-model vectors whose elements are 0x2c bytes (cAnimationCurve) and
// 0x68 bytes (cSplitController): the capacity-growth core of the 2008 EASTL
// vector -- reserve/DoInsertValue(n, value), insert(position, value), resize(n),
// erase(first, last), copy-assign -- plus cGameModelDescription::operator= and
// cGameModelEffectCommand::OnEndBlock.
//
// The originals receive the vector in ECX and the element ranges on the stack
// (ret 0x4 / 0x8 / 0xc), so every vector operation below is modelled as a
// member function of the owning 0x14-byte vector object; the element range
// primitives remain free (cdecl) helpers, exactly as the originals call them.
#include "types.h"

// ------------------------------------------------------------------ allocation
void* __cdecl EAlloc(uint32_t size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
// The deallocator at 0x00f47380 is the global operator delete[]; declaring it `throw()` (the
// nothrow view) is what lets MSVC omit the EH trylevel reset before inlined destructor bodies
// (same trick as slice s00841370).  Byte-identical call sites either way.
void  __cdecl EFree(void* p) throw();                                                             // 0x00f47380
inline void* operator new(unsigned int, void* p) { return p; }

// ------------------------------------------------- 0x2c element: animation curve
struct SVec {                          // eastl::vector<float, sp_vector_allocator>: 0x10 bytes
    float*   mpBegin;                  // +0x00
    float*   mpEnd;                    // +0x04
    float*   mpCapacity;               // +0x08
    uint32_t mAllocator;               // +0x0c  never touched by this slice
    SVec& operator=(const SVec& src);                                        // 0x0050d4e0
    ~SVec() { if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0) EFree(mpBegin); }
};

struct cAnimationCurve {               // 0x2c bytes
    float   mX;                        // +0x00
    float   mY;                        // +0x04
    SVec    mCurve;                    // +0x08
    int     mPad18;                    // +0x18  never copied, never initialised
    float   mA;                        // +0x1c
    float   mB;                        // +0x20
    int     mC;                        // +0x24
    uint8_t mMode;                     // +0x28
    char    mPad29[3];                 // +0x29
    cAnimationCurve() {
        mX = 0.0f;
        mY = 0.0f;
        mCurve.mpBegin = 0;
        mCurve.mpEnd = 0;
        mCurve.mpCapacity = 0;
        mA = 0.0f;
        mB = 0.0f;
        mC = 0;
        mMode = 0;
    }
    cAnimationCurve(const cAnimationCurve& src);                             // 0x007d1140
};

// ----------------------------------------------- 0x68 element: split controller
struct cSPTransform {                  // 0x38 bytes (cSPTransformOps storage)
    uint8_t mData[0x38];
    cSPTransform& operator=(const cSPTransform& src);                        // 0x00537dc0
};

struct TreeThing {                     // eastl::rbtree<...>: 0x1c bytes
    void*    mp0;                      // +0x00
    void*    mpBegin;                  // +0x04
    void*    mpEnd;                    // +0x08
    void*    mpRoot;                   // +0x0c
    uint8_t  mFlag;                    // +0x10
    char     mPad11[3];                // +0x11
    uint32_t mCount;                   // +0x14
    uint32_t mPad18;                   // +0x18
    TreeThing& operator=(const TreeThing& src);                              // 0x007d0b80
    void DoNukeSubtree(void* node);                                          // 0x009a9600
    ~TreeThing() { DoNukeSubtree(mpRoot); }
};

struct cSplitController {              // 0x68 bytes
    uint8_t      mFlags;               // +0x00
    char         mPad1[3];             // +0x01
    uint32_t     mType;                // +0x04
    cSPTransform mTransform;           // +0x08
    uint32_t     m40;                  // +0x40
    uint32_t     m44;                  // +0x44
    uint32_t     m48;                  // +0x48
    TreeThing    mTree;                // +0x4c
    cSplitController();                                                      // 0x007d0670
    cSplitController(const cSplitController& src);                           // 0x007d0d60
};

// ------------------------------------------------------------ free range helpers
// 0x2c element primitives (all cdecl: the caller pops the stack arguments).
cAnimationCurve* AnimUninitCopy(cAnimationCurve* first, cAnimationCurve* last,
                                cAnimationCurve* dst);                       // 0x007d1230
cAnimationCurve* AnimDestroyRange3(cAnimationCurve* first, cAnimationCurve* last,
                                   cAnimationCurve* dst);                    // 0x007d0630
void  AnimAssignRange(cAnimationCurve* first, cAnimationCurve* last,
                      const cAnimationCurve* src);                           // 0x007d1380
void  AnimFillConstruct(cAnimationCurve* dst, unsigned n, const cAnimationCurve* src,
                        cAnimationCurve* a4);                                // 0x007d13d0
cAnimationCurve* AnimCopyBack(cAnimationCurve* first, cAnimationCurve* last,
                              cAnimationCurve* dstEnd);                      // 0x007d1450
cAnimationCurve** AnimUninitCopyBack(cAnimationCurve** cursor, cAnimationCurve* first,
                                     cAnimationCurve* last, cAnimationCurve* dst,
                                     void* a5);                              // 0x007d11b0
cAnimationCurve* AnimCopyRange12C0(cAnimationCurve* first, cAnimationCurve* last,
                                   cAnimationCurve* dst);                    // 0x007d12c0

// 0x68 element primitives.
cSplitController* SplitUninitCopy(cSplitController* first, cSplitController* last,
                                  cSplitController* dst);                    // 0x007d0e50
cSplitController* SplitDestroyRange3(cSplitController* first, cSplitController* last,
                                     cSplitController* dst);                 // 0x007d0a00
void  SplitAssignRange(cSplitController* first, cSplitController* last,
                       const cSplitController* src);                         // 0x007d14b0
void  SplitFillConstruct(cSplitController* dst, unsigned n, const cSplitController* src,
                         cSplitController* a4);                              // 0x007d0ee0
cSplitController* SplitCopyBack(cSplitController* first, cSplitController* last,
                                cSplitController* dstEnd);                   // 0x007d1510
cSplitController** SplitUninitCopyBack(cSplitController** cursor, cSplitController* first,
                                       cSplitController* last, cSplitController* dst,
                                       void* a5);                            // 0x007d0dd0
cSplitController* SplitCopyRange1320(cSplitController* first, cSplitController* last,
                                     cSplitController* dst);                 // 0x007d1320

// ------------------------------------------------------------- owning vector types
struct FloatVec {                      // eastl::vector<float, ...>: 0x14 bytes
    float*   mpBegin;                  // +0x00
    float*   mpEnd;                    // +0x04
    float*   mpCapacity;               // +0x08
    uint32_t mAlloc1;                  // +0x0c
    uint32_t mAlloc2;                  // +0x10
    FloatVec& operator=(const FloatVec& src);                                // 0x0050d4e0
};

struct LabelVec {                      // eastl::vector<cArithmeticaProgram::tLabel, ...>: 0x14 bytes
    void*    mpBegin;                  // +0x00
    void*    mpEnd;                    // +0x04
    void*    mpCapacity;               // +0x08
    uint32_t mAlloc1;                  // +0x0c
    uint32_t mAlloc2;                  // +0x10
    LabelVec& assign(const LabelVec& src);                                   // 0x007f1ac0
};

struct AnimVec {                       // eastl::vector<cAnimationCurve, ...>: 0x14 bytes
    cAnimationCurve* mpBegin;          // +0x00
    cAnimationCurve* mpEnd;            // +0x04
    cAnimationCurve* mpCapacity;       // +0x08
    uint32_t         mAlloc1;          // +0x0c
    uint32_t         mAlloc2;          // +0x10
    void  DoInsertValue(cAnimationCurve* position, unsigned n, const cAnimationCurve& value);  // 0x007d2a30
    void  Insert(cAnimationCurve* position, const cAnimationCurve& value);                     // 0x007d3210
    void  Resize(unsigned n);                                                                  // 0x007d3770
    cAnimationCurve* Erase(cAnimationCurve* first, cAnimationCurve* last);                     // 0x007d2990
    void  DestroyRange(cAnimationCurve* first, cAnimationCurve* last);                         // 0x007d08e0
    cAnimationCurve* Allocate(unsigned n, cAnimationCurve* first, cAnimationCurve* last);      // 0x007d2610
    // the original is the copy-assignment operator (??4AnimVec); named here so the
    // slice tooling can bind its `// @` marker.  Same ABI, same VA, same call site.
    AnimVec& AssignCopy(const AnimVec& src);                                                   // 0x007d2f90
};

struct SplitVec {                      // eastl::vector<cSplitController, ...>: 0x14 bytes
    cSplitController* mpBegin;         // +0x00
    cSplitController* mpEnd;           // +0x04
    cSplitController* mpCapacity;      // +0x08
    uint32_t          mAlloc1;         // +0x0c
    uint32_t          mAlloc2;         // +0x10
    void  DoInsertValue(cSplitController* position, unsigned n, const cSplitController& value);  // 0x007d2c70
    void  Insert(cSplitController* position, const cSplitController& value);                     // 0x007d33e0
    void  Resize(unsigned n);                                                                    // 0x007d3860
    cSplitController* Erase(cSplitController* first, cSplitController* last);                    // 0x007d29e0
    void  DestroyRange(cSplitController* first, cSplitController* last);                         // 0x007d0b30
    cSplitController* Allocate(unsigned n, cSplitController* first, cSplitController* last);     // 0x007d2500
    // copy-assignment operator (??4SplitVec), see AnimVec::AssignCopy.
    SplitVec& AssignCopy(const SplitVec& src);                                                   // 0x007d30d0
};

// ---------------------------------------------- game-model description / command
struct cColour {                       // +0x14 in cGameModelDescription
    float x;                           // +0x00
    float y;                           // +0x04
    float z;                           // +0x08
};

struct cGameModelDescription {         // retail layout (see slice s007d19c0)
    void*    vtbl;                     // +0x00
    int      mRefCount;                // +0x04
    int      mStateID;                 // +0x08
    uint32_t mFlags;                   // +0x0c
    float    mSize;                    // +0x10
    cColour  mColour;                  // +0x14
    float    mAlpha;                   // +0x20
    uint32_t mInstanceID;              // +0x24
    uint32_t mGroupID;                 // +0x28
    uint32_t mWorldID;                 // +0x2c
    AnimVec  mAnimationCurves;         // +0x30
    LabelVec mModelSplitters;          // +0x44
    SplitVec mSplitControllers;        // +0x58
    FloatVec mGroups;                  // +0x6c
    uint32_t mFlagsToSet;              // +0x80
    uint8_t  mPickLevel;               // +0x84
    uint8_t  mOverrideSet;             // +0x85
    char     mPad86[2];                // +0x86
    uint32_t field88;                  // +0x88
    cGameModelDescription* Assign(cGameModelDescription* src);                               // 0x007d35b0
};

void CopyState(void* dst, void* src);                                    // 0x007d2830
void AddDescription(void* a, void* b, int c, void* d);                   // 0x00a6f9c0

struct cGameModelEffectCommand {
    char     mPad0[0x30];              // +0x00
    void*    mField30;                 // +0x30
    char     mState[0x94];             // +0x34
    uint8_t* mStringBegin;             // +0xc8
    uint8_t* mStringEnd;               // +0xcc
    void OnEndBlock(char b);                                                 // 0x007d2ee0
};

// =========================================================== implementations

// @ 0x007d2a30
void AnimVec::DoInsertValue(cAnimationCurve* position, unsigned n, const cAnimationCurve& value) {
    if (n <= (unsigned)(mpCapacity - mpEnd)) {
        if (n == 0) return;

        cAnimationCurve tmp(value);
        cAnimationCurve* oldEnd     = mpEnd;
        unsigned         countAfter = (unsigned)(mpEnd - position);
        if (n < countAfter) {
            cAnimationCurve* split = oldEnd - n;
            cAnimationCurve* cursor;
            AnimUninitCopyBack(&cursor, split, oldEnd, oldEnd, position);
            mpEnd += n;
            AnimCopyBack(position, split, oldEnd);
            AnimAssignRange(position, position + n, &tmp);
        } else {
            AnimFillConstruct(oldEnd, n - countAfter, &tmp, position);
            mpEnd += n - countAfter;
            cAnimationCurve* cursor;
            AnimUninitCopyBack(&cursor, position, oldEnd, mpEnd, position);
            mpEnd += countAfter;
            AnimAssignRange(position, oldEnd, &tmp);
        }
        return;
    }

    unsigned oldSize = (unsigned)(mpEnd - mpBegin);
    unsigned newCap  = oldSize ? oldSize * 2 : 1;
    unsigned need    = oldSize + n;
    if (newCap <= need) newCap = need;
    cAnimationCurve* buf = newCap ? (cAnimationCurve*)EAlloc(newCap * 0x2c, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    cAnimationCurve* mid = AnimUninitCopy(mpBegin, position, buf);
    AnimDestroyRange3(mpBegin, position, buf);
    AnimFillConstruct(mid, n, &value, mid);
    cAnimationCurve* end = AnimUninitCopy(position, mpEnd, mid + n);
    AnimDestroyRange3(position, mpEnd, mid + n);
    if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0) EFree(mpBegin);
    mpBegin    = buf;
    mpEnd      = end;
    mpCapacity = buf + newCap;
}

// @ 0x007d2c70
void SplitVec::DoInsertValue(cSplitController* position, unsigned n, const cSplitController& value) {
    if (n <= (unsigned)(mpCapacity - mpEnd)) {
        if (n == 0) return;

        cSplitController tmp(value);
        cSplitController* oldEnd     = mpEnd;
        unsigned          countAfter = (unsigned)(mpEnd - position);
        if (n < countAfter) {
            cSplitController* split = oldEnd - n;
            cSplitController* cursor;
            SplitUninitCopyBack(&cursor, split, oldEnd, oldEnd, position);
            mpEnd += n;
            SplitCopyBack(position, split, oldEnd);
            SplitAssignRange(position, position + n, &tmp);
        } else {
            SplitFillConstruct(oldEnd, n - countAfter, &tmp, position);
            mpEnd += n - countAfter;
            cSplitController* cursor;
            SplitUninitCopyBack(&cursor, position, oldEnd, mpEnd, position);
            mpEnd += countAfter;
            SplitAssignRange(position, oldEnd, &tmp);
        }
        return;
    }

    unsigned oldSize = (unsigned)(mpEnd - mpBegin);
    unsigned newCap  = oldSize ? oldSize * 2 : 1;
    unsigned need    = oldSize + n;
    if (newCap <= need) newCap = need;
    cSplitController* buf = newCap ? (cSplitController*)EAlloc(newCap * 0x68, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    cSplitController* mid = SplitUninitCopy(mpBegin, position, buf);
    SplitDestroyRange3(mpBegin, position, buf);
    SplitFillConstruct(mid, n, &value, mid);
    cSplitController* end = SplitUninitCopy(position, mpEnd, mid + n);
    SplitDestroyRange3(position, mpEnd, mid + n);
    if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0) EFree(mpBegin);
    mpBegin    = buf;
    mpEnd      = end;
    mpCapacity = buf + newCap;
}

// @ 0x007d3210
void AnimVec::Insert(cAnimationCurve* position, const cAnimationCurve& value) {
    if (mpEnd != mpCapacity) {
        const cAnimationCurve* p = &value;
        if (position <= &value && &value < mpEnd) p = &value + 1;
        if (mpEnd != 0) new (mpEnd) cAnimationCurve(*(mpEnd - 1));
        AnimCopyBack(position, mpEnd - 1, mpEnd);
        position->mX     = p->mX;
        position->mY     = p->mY;
        position->mCurve = p->mCurve;
        position->mA     = p->mA;
        position->mB     = p->mB;
        position->mC     = p->mC;
        position->mMode  = p->mMode;
        mpEnd += 1;
        return;
    }

    unsigned oldSize = (unsigned)(mpEnd - mpBegin);
    unsigned newCap  = oldSize ? oldSize * 2 : 1;
    cAnimationCurve* buf = newCap ? (cAnimationCurve*)EAlloc(newCap * 0x2c, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    cAnimationCurve* mid = AnimUninitCopy(mpBegin, position, buf);
    AnimDestroyRange3(mpBegin, position, buf);
    if (mid != 0) new (mid) cAnimationCurve(value);
    cAnimationCurve* end = AnimUninitCopy(position, mpEnd, mid + 1);
    AnimDestroyRange3(position, mpEnd, mid + 1);
    if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0) EFree(mpBegin);
    mpBegin    = buf;
    mpEnd      = end;
    mpCapacity = buf + newCap;
}

// @ 0x007d33e0
void SplitVec::Insert(cSplitController* position, const cSplitController& value) {
    if (mpEnd != mpCapacity) {
        const cSplitController* p = &value;
        if (position <= &value && &value < mpEnd) p = &value + 1;
        if (mpEnd != 0) new (mpEnd) cSplitController(*(mpEnd - 1));
        SplitCopyBack(position, mpEnd - 1, mpEnd);
        position->mFlags     = p->mFlags;
        position->mType      = p->mType;
        position->mTransform = p->mTransform;
        position->m40        = p->m40;
        position->m44        = p->m44;
        position->m48        = p->m48;
        position->mTree      = p->mTree;
        mpEnd += 1;
        return;
    }

    unsigned oldSize = (unsigned)(mpEnd - mpBegin);
    unsigned newCap  = oldSize ? oldSize * 2 : 1;
    cSplitController* buf = newCap ? (cSplitController*)EAlloc(newCap * 0x68, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    cSplitController* mid = SplitUninitCopy(mpBegin, position, buf);
    SplitDestroyRange3(mpBegin, position, buf);
    if (mid != 0) new (mid) cSplitController(value);
    cSplitController* end = SplitUninitCopy(position, mpEnd, mid + 1);
    SplitDestroyRange3(position, mpEnd, mid + 1);
    if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0) EFree(mpBegin);
    mpBegin    = buf;
    mpEnd      = end;
    mpCapacity = buf + newCap;
}

// @ 0x007d3770
void AnimVec::Resize(unsigned n) {
    if (n > (unsigned)(mpEnd - mpBegin)) {
        DoInsertValue(mpEnd, n - (unsigned)(mpEnd - mpBegin), cAnimationCurve());
    } else {
        Erase(mpBegin + n, mpEnd);
    }
}

// @ 0x007d3860
void SplitVec::Resize(unsigned n) {
    if (n > (unsigned)(mpEnd - mpBegin)) {
        DoInsertValue(mpEnd, n - (unsigned)(mpEnd - mpBegin), cSplitController());
    } else {
        Erase(mpBegin + n, mpEnd);
    }
}

// @ 0x007d2f90
AnimVec& AnimVec::AssignCopy(const AnimVec& src) {
    if (this == &src) return *this;

    unsigned n = (unsigned)(src.mpEnd - src.mpBegin);
    if (n > (unsigned)(mpCapacity - mpBegin)) {
        cAnimationCurve* buf = Allocate(n, src.mpBegin, src.mpEnd);
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0) EFree(mpBegin);
        mpBegin    = buf;
        mpEnd      = buf + n;
        mpCapacity = buf + n;
        return *this;
    }

    unsigned m = (unsigned)(mpEnd - mpBegin);
    if (m < n) {
        AnimCopyRange12C0(src.mpBegin, src.mpBegin + m, mpBegin);
        cAnimationCurve* cursor;
        AnimUninitCopyBack(&cursor, src.mpBegin + m, src.mpEnd, mpEnd, src.mpEnd);
        mpEnd = mpBegin + n;
    } else {
        AnimCopyRange12C0(src.mpBegin, src.mpEnd, mpBegin);
        DestroyRange(mpBegin + n, mpEnd);
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x007d30d0
SplitVec& SplitVec::AssignCopy(const SplitVec& src) {
    if (this == &src) return *this;

    unsigned n = (unsigned)(src.mpEnd - src.mpBegin);
    if (n > (unsigned)(mpCapacity - mpBegin)) {
        cSplitController* buf = Allocate(n, src.mpBegin, src.mpEnd);
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0) EFree(mpBegin);
        mpBegin    = buf;
        mpEnd      = buf + n;
        mpCapacity = buf + n;
        return *this;
    }

    unsigned m = (unsigned)(mpEnd - mpBegin);
    if (m < n) {
        SplitCopyRange1320(src.mpBegin, src.mpBegin + m, mpBegin);
        cSplitController* cursor;
        SplitUninitCopyBack(&cursor, src.mpBegin + m, src.mpEnd, mpEnd, src.mpEnd);
        mpEnd = mpBegin + n;
    } else {
        SplitCopyRange1320(src.mpBegin, src.mpEnd, mpBegin);
        DestroyRange(mpBegin + n, mpEnd);
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x007d2610
cAnimationCurve* AnimVec::Allocate(unsigned n, cAnimationCurve* first, cAnimationCurve* last) {
    cAnimationCurve* buf = n ? (cAnimationCurve*)EAlloc(n * 0x2c, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    cAnimationCurve* cursor;
    AnimUninitCopyBack(&cursor, first, last, buf, (void*)n);
    return buf;
}

// @ 0x007d2500
cSplitController* SplitVec::Allocate(unsigned n, cSplitController* first, cSplitController* last) {
    cSplitController* buf = n ? (cSplitController*)EAlloc(n * 0x68, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    cSplitController* cursor;
    SplitUninitCopyBack(&cursor, first, last, buf, (void*)n);
    return buf;
}

// @ 0x007d35b0
cGameModelDescription* cGameModelDescription::Assign(cGameModelDescription* src) {
    mStateID = src ? src->mStateID : 0;
    mFlags   = src->mFlags;
    mSize    = src->mSize;
    mColour  = src->mColour;
    mAlpha   = src->mAlpha;
    mInstanceID = src->mInstanceID;
    mGroupID    = src->mGroupID;
    mWorldID    = src->mWorldID;
    mAnimationCurves.AssignCopy(src->mAnimationCurves);
    mModelSplitters.assign(src->mModelSplitters);
    mSplitControllers.AssignCopy(src->mSplitControllers);
    mGroups = src->mGroups;
    mFlagsToSet  = src->mFlagsToSet;
    mPickLevel   = src->mPickLevel;
    mOverrideSet = src->mOverrideSet;
    field88      = src->field88;
    return this;
}

// @ 0x007d2ee0
void cGameModelEffectCommand::OnEndBlock(char b) {
    if (b == 0) {
        void* s = EAlloc(0x8c, "Swarm", 0, 0, (const char*)0, 0);
        if (s) CopyState(s, &mState[4]);
        else s = 0;
        AddDescription(mField30, mStringBegin, 0x25, s);
    }
    if (mStringBegin != mStringEnd) {
        *mStringBegin = 0;
        mStringEnd = mStringBegin;
    }
}