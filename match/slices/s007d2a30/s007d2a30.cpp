// SWARM game-model description vector instantiations (element strides 0x2c and
// 0x68) and cGameModelEffectCommand::OnEndBlock.
//
// These are eastl::vector<T, sp_vector_allocator> instantiations: reserve /
// DoInsertValue / insert-at-position / operator= / resize, plus the description
// assignment operator.  The originals are the 2008 EASTL implementation.
//
// Flags: /O2 /MD /Gy /TP (no EH cookie; the x87 float copies use the FPU).
#include "types.h"

void* operator new[](size_t size);
void  operator delete[](void* p);
void* operator new(size_t size, const char* pName, int a, int b, const char* file, int line);  // 0xf473a0
void  operator delete(void* p);                                                  // 0xf47380

// ----------------------------------------------------------- element types
struct FloatVec {                       // eastl::vector<float, sp_vector_allocator>
    float* mpBegin; float* mpEnd; float* mpCapacity; void* mAlloc1; void* mAlloc2;
    void destroy() { if (mpBegin) operator delete[](mpBegin); mpBegin = mpEnd = mpCapacity = 0; }
    void copy_from(const FloatVec& o) {
        unsigned n = (unsigned)(o.mpEnd - o.mpBegin);
        destroy();
        if (n) {
            mpBegin = new float[n]; mpEnd = mpBegin + n; mpCapacity = mpBegin + n;
            for (unsigned i = 0; i < n; ++i) mpBegin[i] = o.mpBegin[i];
        }
    }
    FloatVec& operator=(const FloatVec& o) { if (this != &o) copy_from(o); return *this; }
};

struct cAnimationCurve {                // size 0x2c
    float mX;
    float mY;
    FloatVec mCurve;                    // +0x08
    float mA;                           // +0x1c
    float mB;                           // +0x20
    float mC;                           // +0x24
    uint8_t mMode;                      // +0x28
};

struct cSPTransform {                   // size 0x38
    float m[0x38 / 4];
    cSPTransform& operator=(const cSPTransform& o) {
        for (int i = 0; i < 0x38 / 4; ++i) m[i] = o.m[i];
        return *this;
    }
};

struct cSplitController {               // size 0x68
    uint8_t mFlags;                     // +0x00
    uint32_t mType;                     // +0x04
    cSPTransform mTransform;            // +0x08
    uint32_t m40, m44, m48;             // +0x40
    FloatVec mCurve;                    // +0x4c
};

template <class T> struct Vec {
    T* mpBegin; T* mpEnd; T* mpCapacity; void* mAlloc1; void* mAlloc2;
};

// description (retail layout, matches slice s007d19c0)
struct cGameModelDescription {
    void* vtbl; int mRefCount; int mStateID; uint32_t mFlags;
    float mSize; float mColourX, mColourY, mColourZ; float mAlpha;
    uint32_t mInstanceID, mGroupID, mWorldID;
    Vec<cAnimationCurve> mAnimationCurves;   // +0x30
    Vec<cSplitController> mModelSplitters;   // +0x44
    Vec<cSplitController> mSplitControllers; // +0x58
    Vec<float> mGroups;                      // +0x6c
    uint32_t mFlagsToSet; uint8_t mPickLevel, mOverrideSet, pad86[2]; uint32_t field88;
};

// --------------------------------------------------------------- helpers
// range primitives of the 2008 EASTL vector implementation
void  AnimRangeDtor(cAnimationCurve* first, cAnimationCurve* last);              // 0x7d08e0
cAnimationCurve* AnimRangeCopyCtor(cAnimationCurve* dst, cAnimationCurve* first, cAnimationCurve* last); // 0x7d1230
void  AnimRangeAssign(cAnimationCurve* first, cAnimationCurve* last, cAnimationCurve* dst);   // 0x7d0630
void  AnimMoveRange(cAnimationCurve* dst, cAnimationCurve* src, cAnimationCurve* srcEnd);     // 0x7d1450
void  AnimFill(cAnimationCurve* first, unsigned n, const cAnimationCurve* value);            // 0x7d1380
cAnimationCurve* AnimAllocate(unsigned n);                                                  // 0x7d2610
void  AnimMoveBackward(cAnimationCurve* dst, cAnimationCurve* first, cAnimationCurve* last); // 0x7d13d0
void  AnimUninitCopy(cAnimationCurve** dst, cAnimationCurve* first, cAnimationCurve* last,
                     cAnimationCurve* pos, cAnimationCurve* junk);               // 0x7d11b0

void  SplitRangeDtor(cSplitController* first, cSplitController* last);           // 0x7d0b30
cSplitController* SplitRangeCopyCtor(cSplitController* dst, cSplitController* first, cSplitController* last); // 0x7d0e50
void  SplitRangeAssign(cSplitController* first, cSplitController* last, cSplitController* dst);   // 0x7d0a00
void  SplitMoveRange(cSplitController* dst, cSplitController* src, cSplitController* srcEnd);     // 0x7d1510
void  SplitFill(cSplitController* first, unsigned n, const cSplitController* value);             // 0x7d14b0
cSplitController* SplitAllocate(unsigned n);                                                 // 0x7d2500
void  SplitMoveBackward(cSplitController* dst, cSplitController* first, cSplitController* last); // 0x7d0ee0
void  SplitUninitCopy(cSplitController** dst, cSplitController* first, cSplitController* last,
                      cSplitController* pos, cSplitController* junk);            // 0x7d0dd0
void  SplitVecDtor(cSplitController* p);                                         // 0x7d0d60

void  FloatVecAssign(void* dst, void* src);                                      // 0x50d4e0
void  CopyState(void* dst, void* src);                                           // 0x7d2830
void  AddDescription(void* a, void* b, int c, void* d);                          // 0xa6f9c0

// =========================================================== implementations
// @ 0x007d2a30  cAnimationCurve vector reserve/DoInsertValue(n, value)
void AnimDoInsertValue(Vec<cAnimationCurve>* v, cAnimationCurve* pos, unsigned n, cAnimationCurve* value) {
    unsigned cap = (unsigned)((v->mpEnd - v->mpBegin));
    if (cap >= n) {
        if (n) {
            unsigned count = (unsigned)((v->mpEnd - pos) / 1);
            (void)count;
        }
        return;
    }
    unsigned oldN = (unsigned)(v->mpEnd - v->mpBegin);
    unsigned newCap = oldN * 2; if (oldN == 0) newCap = 1;
    unsigned need = oldN + n; if (need > newCap) newCap = need; else if (newCap < need) newCap = need;
    cAnimationCurve* buf = newCap ? (cAnimationCurve*)(void*)operator new(newCap * sizeof(cAnimationCurve), "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    cAnimationCurve* mid = AnimRangeCopyCtor(buf, v->mpBegin, pos);
    AnimRangeAssign(pos, v->mpEnd, mid);
    AnimFill(mid, n, value);
    cAnimationCurve* end = AnimRangeCopyCtor(mid + n, pos, v->mpEnd);
    if (v->mpBegin) operator delete[](v->mpBegin);
    v->mpBegin = buf; v->mpEnd = end; v->mpCapacity = buf + newCap;
}

// @ 0x007d2c70  cSplitController vector reserve/DoInsertValue(n, value)
void SplitDoInsertValue(Vec<cSplitController>* v, cSplitController* pos, unsigned n, cSplitController* value) {
    unsigned cap = (unsigned)(v->mpEnd - v->mpBegin);
    if (cap >= n) {
        if (n) {
            unsigned count = (unsigned)(v->mpEnd - pos);
            (void)count;
        }
        return;
    }
    unsigned oldN = (unsigned)(v->mpEnd - v->mpBegin);
    unsigned newCap = oldN * 2; if (oldN == 0) newCap = 1;
    unsigned need = oldN + n; if (need > newCap) newCap = need;
    cSplitController* buf = newCap ? (cSplitController*)(void*)operator new(newCap * sizeof(cSplitController), "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    cSplitController* mid = SplitRangeCopyCtor(buf, v->mpBegin, pos);
    SplitRangeAssign(pos, v->mpEnd, mid);
    SplitFill(mid, n, value);
    cSplitController* end = SplitRangeCopyCtor(mid + n, pos, v->mpEnd);
    if (v->mpBegin) operator delete[](v->mpBegin);
    v->mpBegin = buf; v->mpEnd = end; v->mpCapacity = buf + newCap;
}

// @ 0x007d2ee0  cGameModelEffectCommand::OnEndBlock(bool)
struct cGameModelEffectCommand {
    char pad[0x30];
    void* mField30;        // +0x30
    char  mState[0x94];    // +0x34
    uint8_t* mStringBegin; // +0xc8
    uint8_t* mStringEnd;   // +0xcc
    void OnEndBlock(char b);
};
void cGameModelEffectCommand::OnEndBlock(char b) {
    if (b == 0) {
        void* s = operator new(0x8c, "Swarm", 0, 0, 0, 0);
        if (s) CopyState(s, &mState[4]);
        else s = 0;
        AddDescription(mField30, mStringBegin, 0x25, s);
    }
    if (mStringBegin != mStringEnd) {
        *mStringBegin = 0;
        mStringEnd = mStringBegin;
    }
}

// @ 0x007d2f90  eastl::vector<cAnimationCurve>::operator=
Vec<cAnimationCurve>* AnimVecAssign(Vec<cAnimationCurve>* self, Vec<cAnimationCurve>* src) {
    if (src == self) return self;
    unsigned n = (unsigned)(src->mpEnd - src->mpBegin);
    unsigned cap = (unsigned)(self->mpCapacity - self->mpBegin);
    if (cap < n) {
        cAnimationCurve* buf = (cAnimationCurve*)AnimAllocate(n);
        AnimRangeDtor(self->mpBegin, self->mpEnd);
        if (self->mpBegin) operator delete[](self->mpBegin);
        self->mpBegin = buf; self->mpEnd = buf + n; self->mpCapacity = buf + n;
        return self;
    }
    unsigned m = (unsigned)(self->mpEnd - self->mpBegin);
    if (m < n) {
        AnimRangeAssign(src->mpBegin, src->mpBegin + m, self->mpBegin);
        AnimUninitCopy(&src->mpEnd, src->mpBegin + m, src->mpEnd, self->mpEnd, src->mpEnd);
        self->mpEnd = self->mpBegin + n;
    } else {
        AnimRangeAssign(src->mpBegin, src->mpEnd, self->mpBegin);
        AnimRangeDtor(self->mpBegin + n, self->mpEnd);
        self->mpEnd = self->mpBegin + n;
    }
    return self;
}

// @ 0x007d30d0  eastl::vector<cSplitController>::operator=
Vec<cSplitController>* SplitVecAssign(Vec<cSplitController>* self, Vec<cSplitController>* src) {
    if (src == self) return self;
    unsigned n = (unsigned)(src->mpEnd - src->mpBegin);
    unsigned cap = (unsigned)(self->mpCapacity - self->mpBegin);
    if (cap < n) {
        cSplitController* buf = (cSplitController*)SplitAllocate(n);
        SplitRangeDtor(self->mpBegin, self->mpEnd);
        if (self->mpBegin) operator delete[](self->mpBegin);
        self->mpBegin = buf; self->mpEnd = buf + n; self->mpCapacity = buf + n;
        return self;
    }
    unsigned m = (unsigned)(self->mpEnd - self->mpBegin);
    if (m < n) {
        SplitRangeAssign(src->mpBegin, src->mpBegin + m, self->mpBegin);
        SplitUninitCopy(&src->mpEnd, src->mpBegin + m, src->mpEnd, self->mpEnd, src->mpEnd);
        self->mpEnd = self->mpBegin + n;
    } else {
        SplitRangeAssign(src->mpBegin, src->mpEnd, self->mpBegin);
        SplitRangeDtor(self->mpBegin + n, self->mpEnd);
        self->mpEnd = self->mpBegin + n;
    }
    return self;
}

// @ 0x007d3210  cAnimationCurve vector insert(position, value)
void AnimVecInsert(Vec<cAnimationCurve>* v, cAnimationCurve* pos, cAnimationCurve* value) {
    if (v->mpEnd != v->mpCapacity) {
        cAnimationCurve* p = (pos <= value && value < v->mpEnd) ? value + 1 : value;
        if (v->mpEnd) AnimRangeDtor(v->mpEnd - 1, v->mpEnd);
        AnimMoveRange(pos, v->mpEnd - 1, v->mpEnd);
        *pos = *p; pos->mCurve = p->mCurve; pos->mA = p->mA; pos->mB = p->mB; pos->mC = p->mC; pos->mMode = p->mMode;
        v->mpEnd = v->mpEnd + 1;
        return;
    }
    unsigned oldN = (unsigned)(v->mpEnd - v->mpBegin);
    unsigned newCap = oldN ? oldN * 2 : 1;
    cAnimationCurve* buf = newCap ? (cAnimationCurve*)(void*)operator new(newCap * sizeof(cAnimationCurve), "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    cAnimationCurve* mid = AnimRangeCopyCtor(buf, v->mpBegin, pos);
    AnimRangeAssign(pos, v->mpEnd, mid);
    *mid = *value; mid->mCurve = value->mCurve; mid->mA = value->mA; mid->mB = value->mB; mid->mC = value->mC; mid->mMode = value->mMode;
    cAnimationCurve* end = AnimRangeCopyCtor(mid + 1, pos, v->mpEnd);
    if (v->mpBegin) operator delete[](v->mpBegin);
    v->mpBegin = buf; v->mpEnd = end; v->mpCapacity = buf + newCap;
}

// @ 0x007d33e0  cSplitController vector insert(position, value)
void SplitVecInsert(Vec<cSplitController>* v, cSplitController* pos, cSplitController* value) {
    if (v->mpEnd != v->mpCapacity) {
        cSplitController* p = (pos <= value && value < v->mpEnd) ? value + 1 : value;
        if (v->mpEnd) SplitVecDtor(v->mpEnd - 1);
        SplitMoveRange(pos, v->mpEnd - 1, v->mpEnd);
        pos->mFlags = p->mFlags; pos->mType = p->mType; pos->mTransform = p->mTransform;
        pos->m40 = p->m40; pos->m44 = p->m44; pos->m48 = p->m48; pos->mCurve = p->mCurve;
        v->mpEnd = v->mpEnd + 1;
        return;
    }
    unsigned oldN = (unsigned)(v->mpEnd - v->mpBegin);
    unsigned newCap = oldN ? oldN * 2 : 1;
    cSplitController* buf = newCap ? (cSplitController*)(void*)operator new(newCap * sizeof(cSplitController), "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    cSplitController* mid = SplitRangeCopyCtor(buf, v->mpBegin, pos);
    SplitRangeAssign(pos, v->mpEnd, mid);
    mid->mFlags = value->mFlags; mid->mType = value->mType; mid->mTransform = value->mTransform;
    mid->m40 = value->m40; mid->m44 = value->m44; mid->m48 = value->m48; mid->mCurve = value->mCurve;
    cSplitController* end = SplitRangeCopyCtor(mid + 1, pos, v->mpEnd);
    if (v->mpBegin) operator delete[](v->mpBegin);
    v->mpBegin = buf; v->mpEnd = end; v->mpCapacity = buf + newCap;
}

// @ 0x007d35b0  SP::cGameModelDescription::operator=
cGameModelDescription* DescriptionAssign(cGameModelDescription* self, cGameModelDescription* src) {
    self->mStateID = src ? src->mStateID : 0;
    self->mFlags = src->mFlags;
    self->mSize = src->mSize;
    self->mColourX = src->mColourX; self->mColourY = src->mColourY; self->mColourZ = src->mColourZ;
    self->mAlpha = src->mAlpha;
    self->mInstanceID = src->mInstanceID;
    self->mGroupID = src->mGroupID;
    self->mWorldID = src->mWorldID;
    AnimVecAssign(&self->mAnimationCurves, &src->mAnimationCurves);
    SplitVecAssign(&self->mModelSplitters, &src->mModelSplitters);
    SplitVecAssign(&self->mSplitControllers, &src->mSplitControllers);
    FloatVecAssign(&self->mGroups, &src->mGroups);
    self->mFlagsToSet = src->mFlagsToSet;
    self->mPickLevel = src->mPickLevel;
    self->mOverrideSet = src->mOverrideSet;
    self->field88 = src->field88;
    return self;
}

// @ 0x007d3770  eastl::vector<cAnimationCurve>::resize(n)
void AnimVecResize(Vec<cAnimationCurve>* v, unsigned n) {
    cAnimationCurve* begin = v->mpBegin;
    cAnimationCurve* end = v->mpEnd;
    if ((unsigned)(end - begin) < n) {
        cAnimationCurve tmp;
        unsigned i;
        tmp.mX = 0; tmp.mY = 0;
        tmp.mCurve.mpBegin = tmp.mCurve.mpEnd = tmp.mCurve.mpCapacity = 0; tmp.mCurve.mAlloc1 = tmp.mCurve.mAlloc2 = 0;
        tmp.mA = 0; tmp.mB = 0; tmp.mC = 0; tmp.mMode = 0;
        AnimDoInsertValue(v, end, n - (unsigned)(end - begin), &tmp);
        tmp.mCurve.destroy();
    }
}

// @ 0x007d3860  eastl::vector<cSplitController>::resize(n)
void SplitVecResize(Vec<cSplitController>* v, unsigned n) {
    cSplitController* begin = v->mpBegin;
    cSplitController* end = v->mpEnd;
    if ((unsigned)(end - begin) < n) {
        cSplitController tmp;
        tmp.mFlags = 0; tmp.mType = 0;
        for (int i = 0; i < 0x38 / 4; ++i) tmp.mTransform.m[i] = 0;
        tmp.m40 = tmp.m44 = tmp.m48 = 0;
        tmp.mCurve.mpBegin = tmp.mCurve.mpEnd = tmp.mCurve.mpCapacity = 0; tmp.mCurve.mAlloc1 = tmp.mCurve.mAlloc2 = 0;
        SplitDoInsertValue(v, end, n - (unsigned)(end - begin), &tmp);
        tmp.mCurve.destroy();
    } else {
        // shrink: destroy [begin+n, end)
    }
}
