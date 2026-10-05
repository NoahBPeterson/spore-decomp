// Slice s006f3410: SP::cModelInstanceSet (Update / AddToRenderer / ctor / dtor), the
// renderable model-instance class (message handler, viewer setup, per-instance effect state)
// and a Graphics hash-bucket rebuild helper.
// Region 0x6f3410-0x6f4330. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE (SSE scalar floats).
#include "types.h"
#include <math.h>

// ---- external callees (bodies live elsewhere; addresses masked) -------------------------
void  __cdecl EASTL_allocator_deallocate(void* p);                                  // 0xf47380
void* __cdecl EASTL_allocator_allocate(unsigned size, const char* name, int a, int b,
                                       const char* file, int line);                 // 0xf473a0
void  __cdecl memset_thunk(void* dst, int value, unsigned size);                    // 0x11e073e
void* __cdecl FUN_0067dd60();                                                       // 0x67dd60
void  __cdecl FUN_007c3cb0(void* p);                                                // 0x7c3cb0
void  __cdecl FUN_007c3ce0(int a, int b);                                           // 0x7c3ce0
void  __cdecl FUN_007c3c20(void* p);                                                // 0x7c3c20
void  __cdecl FUN_007c3c50(int a);                                                  // 0x7c3c50
void  __cdecl FUN_007c4be0(void* p, int a);                                         // 0x7c4be0

extern float g_153415c;   // 0x153415c
extern char  g_15342b0;   // 0x15342b0
extern char  g_1619530;   // 0x1619530

// -----------------------------------------------------------------------------------------
// SP::cModelInstanceSet
// -----------------------------------------------------------------------------------------
class cModelInstanceSet {
public:
    virtual void v0(void* pRenderer);            // 0x6f3410
    virtual void v1();                           // 0x6f3dd0

    unsigned int mModelInstance;                 // +0x4
    unsigned int mModelGroup;                    // +0x8
    void* mTBegin;                               // +0xc
    void* mTEnd;                                 // +0x10
    void* mTCap;                                 // +0x14
    int   m18;                                   // +0x18
    void* mRBegin;                               // +0x1c
    void* mREnd;                                 // +0x20
    void* mRCap;                                 // +0x24
    int   m28;                                   // +0x28
    int   m2c;                                   // +0x2c
    int   m30;                                   // +0x30
    void* mRenderer;                             // +0x34
    int   m38;                                   // +0x38
    int   m3c;                                   // +0x3c
    unsigned char m40;                           // +0x40
    unsigned char m41, m42, m43;                 // +0x41..0x43
    unsigned short m44;                          // +0x44
    char  pad46[2];                              // +0x46
    float m48;                                   // +0x48
    char  pad4c[4];                              // +0x4c
    int   m50;                                   // +0x50
    int   m54;                                   // +0x54
    int   mSetID;                                // +0x58
    int   m5c;                                   // +0x5c

    cModelInstanceSet();
    ~cModelInstanceSet();
    void AddToRenderer(void* pRenderer);
    void Update();
};

static inline void** Vt(void* p) { return *(void***)p; }
static inline void  Call2(void* p, int slot, int a, int b) {
    (*(void (__thiscall**)(void*, int, int))(Vt(p) + slot))(p, a, b);
}

// @ 0x006f3d00
cModelInstanceSet::cModelInstanceSet()
    : mModelInstance(0), mModelGroup(0), mTBegin(0), mTEnd(0), mTCap(0),
      mREnd(0), mRCap(0), m28(0), mRenderer(0),
      m38(-1), m3c(-1), m40(0), m41(0), m42(0), m43(0),
      m44(0), m48(0.0f), m50(-1), m54(-1), mSetID(-1) {
}

// @ 0x006f3d50
cModelInstanceSet::~cModelInstanceSet() {
    if (mRenderer) (*(void (__thiscall**)(void*))(Vt(mRenderer) + 1))(mRenderer);
    if (mREnd && ((int*)mREnd)[-1]) EASTL_allocator_deallocate(mREnd);
    if (mTBegin && ((int*)mTBegin)[-1]) EASTL_allocator_deallocate(mTBegin);
}

// @ 0x006f3b70
void cModelInstanceSet::Update() {
    if (mSetID < 0) return;
    float minx = g_153415c, miny = g_153415c, minz = g_153415c;
    float maxx = -g_153415c, maxy = -g_153415c, maxz = -g_153415c;
    float radius = 0.0f;
    int n = (int)(((char*)mTEnd - (char*)mTBegin) / 0x38);
    for (int i = 0; i < n; i++) {
        float* p = (float*)((char*)mTBegin + i * 0x38);
        if (minx > p[1]) minx = p[1];
        if (maxx < p[1]) maxx = p[1];
        if (miny > p[2]) miny = p[2];
        if (maxy < p[2]) maxy = p[2];
        if (minz > p[3]) minz = p[3];
        if (maxz < p[3]) maxz = p[3];
        if (radius < p[4]) radius = p[4];
    }
    (*(void (__thiscall**)(void*, int, float*, float))(Vt(mRenderer) + 13))(mRenderer, mSetID, &minx, radius);
}

// @ 0x006f3df0
void cModelInstanceSet::AddToRenderer(void* pRenderer) {
    if (mSetID >= 0) {
        void* old = mRenderer;
        if (old == pRenderer) return;
        (*(void (__thiscall**)(void*, int))(Vt(old) + 12))(old, mSetID);
        if (mRenderer) {
            void* r = mRenderer;
            mRenderer = 0;
            (*(void (__thiscall**)(void*))(Vt(r) + 1))(r);
        }
        mSetID = -1;
    }
    m38 = (int)mModelInstance;
    m3c = (int)mModelGroup;
    m40 = 9;
    void* old = mRenderer;
    if (old != pRenderer) {
        if (pRenderer) (*(void (__thiscall**)(void*))(Vt(pRenderer) + 0))(pRenderer);
        mRenderer = pRenderer;
        if (old) (*(void (__thiscall**)(void*))(Vt(old) + 1))(old);
    }
    if (mRenderer) {
        if ((*(char (__thiscall**)(void*, void*, int*, int*))(Vt(mRenderer) + 11))(mRenderer, &m38, &mSetID, 0)) {
            (*(void (__thiscall**)(void*, int, int*))(Vt(mRenderer) + 4))(mRenderer, 9, &m5c);
            (*(void (__thiscall**)(void*, int, int))(Vt(mRenderer) + 14))(mRenderer, mSetID, 1);
            Update();
        }
    }
}

// @ 0x006f3410  (large vertex-buffer builder; skeleton, see partial.txt)
void cModelInstanceSet::v0(void* pRenderer) {
    (void)pRenderer;
}

// -----------------------------------------------------------------------------------------
// Renderable model-instance class (viewer + per-instance effect state).
// -----------------------------------------------------------------------------------------
struct cViewer {
    void Copy(void* src, int a, int b);   // 0x7c50b0
    void f3cb0(void* p);                  // 0x7c3cb0
    void f3ce0(int a, int b);             // 0x7c3ce0
    void f3c20(void* p);                  // 0x7c3c20
    void f3c50(int a);                    // 0x7c3c50
    void f4be0(void* p, int a);           // 0x7c4be0
};

class cRenderInstanceSet {
public:
    virtual bool OnMessage(int id, int arg);          // slot 0  0x6f3ec0
    virtual void v1();                                // slot 1
    virtual void v2();                                // slot 2
    virtual void v3();                                // slot 3
    virtual void v4();                                // slot 4
    virtual void v5();                                // slot 5
    virtual void v6();                                // slot 6
    virtual void v7();                                // slot 7
    virtual void v8(int count);                       // slot 8
    virtual void v9();                                // slot 9
    virtual void SetColor(int a, const float* rgb, float alpha, int b); // slot 10 0x6f4100
    virtual void v11();                               // slot 11

    char  pad04[0x110 - 0x4];
    float mColorR;       // +0x110
    float mColorG;       // +0x114
    float mColorB;       // +0x118
    float mColorA;       // +0x11c
    int   mRangeBegin;   // +0x120
    int   mRangeEnd;     // +0x124
    char  pad128[0x130 - 0x128];
    unsigned char mFlag130;                             // +0x130
    char  pad131[0x138 - 0x131];
    void* mModelArray;   // +0x138  (array of 2 model pointers)
    char  pad13c[0x154 - 0x13c];
    float mF154;         // +0x154
    char  pad158[0x168 - 0x158];
    void* mRenderer168;  // +0x168
    char  pad16c[0x174 - 0x16c];
    cViewer* mViewer174; // +0x174
    cViewer* mViewer178; // +0x178
    cViewer* mViewer17c; // +0x17c
    cViewer* mViewer180; // +0x180
    char  pad184[0x1a8 - 0x184];
    float mF1a8;         // +0x1a8
    float mF1ac;         // +0x1ac
    float mF1b0;         // +0x1b0
    int   mArr1b4[2];    // +0x1b4
    unsigned char mFlags1bc[12]; // +0x1bc
    float mValues1c8[12];        // +0x1c8

    bool CopyTo174(void* src);
    cViewer* Setup178(void* src);
    cViewer* Setup180(void* src);
    void Tick154(int dt);
    bool IsRangeEmpty() const;
    void GetRange(int* out);
    cViewer* RenderRange(void* src);
    void SetElement(int idx, float value);
    void ClearElements();
    void UpdateEffects(int dt);
};

// @ 0x006f3ec0
bool cRenderInstanceSet::OnMessage(int id, int arg) {
    (void)arg;
    if (id == 0x044EDD9C) {
        mFlag130 = 1;
        return true;
    }
    return false;
}

// @ 0x006f3ee0
bool cRenderInstanceSet::CopyTo174(void* src) {
    mViewer17c->Copy(src, 0, 0);
    return true;
}

// @ 0x006f3f20
cViewer* cRenderInstanceSet::Setup178(void* src) {
    mViewer178->Copy(src, 0, 0);
    void* r = (*(void* (__thiscall**)(void*))(Vt(mRenderer168) + 29))(mRenderer168);
    if (((*(unsigned char*)r) & 0) == 0) {
        if (((*(unsigned char*)((char*)r + 4)) & 1) == 0) {
            void* o = FUN_0067dd60();
            (*(void (__thiscall**)(void*, void*))(Vt(o) + 13))(o, r);
        }
    }
    mViewer178->f3cb0(*(void**)r);
    mViewer178->f3ce0(0xb, 0);
    mViewer178->f3c20(&g_15342b0);
    mViewer178->f3c50(7);
    return mViewer178;
}

// @ 0x006f3fb0
cViewer* cRenderInstanceSet::Setup180(void* src) {
    mViewer180->Copy(src, 0, 0);
    return mViewer180;
}

// @ 0x006f4020
void cRenderInstanceSet::Tick154(int dt) {
    float old = mF154;
    float target = mF1a8;
    if (old != target) {
        mF154 = (target - old) * mF1ac + old;
        mF1ac = fabsf((float)(unsigned int)dt * mF1b0 * 0.001f) + mF1ac;
        if (mF1ac < 1.0f) return;
        mF154 = target;
    }
    mF1ac = 0.0f;
}

// @ 0x006f40b0
void cRenderInstanceSet::SetElement(int idx, float value) {
    mFlags1bc[idx] = 1;
    mValues1c8[idx] = value;
}

// @ 0x006f40d0
void cRenderInstanceSet::ClearElements() {
    for (unsigned int i = 0; i < 12; i++) {
        mFlags1bc[i] = 0;
        mValues1c8[i] = 0.0f;
    }
}

// @ 0x006f4100
void cRenderInstanceSet::SetColor(int a, const float* rgb, float alpha, int b) {
    (void)a; (void)b;
    mColorR = rgb[0] * 255.0f;
    mColorG = rgb[1] * 255.0f;
    mColorB = rgb[2] * 255.0f;
    mColorA = alpha * 255.0f;
}

// @ 0x006f4170
bool cRenderInstanceSet::IsRangeEmpty() const {
    return mRangeBegin == mRangeEnd;
}

// @ 0x006f4190
void cRenderInstanceSet::GetRange(int* out) {
    unsigned int uVar2 = 0;
    int* piVar3 = mArr1b4;
    do {
        if (*piVar3 >= 0) {
            if ((int)uVar2 >= 0) {
                int* iVar1 = ((int**)mModelArray)[uVar2];
                unsigned short idx = *(unsigned short*)((char*)iVar1 + 8);
                void* base = *(void**)((char*)iVar1 + 0x4c);
                out[0] = *(int*)((char*)base + idx * 8);
                out[1] = *(int*)((char*)base + idx * 8 + 4);
                return;
            }
            break;
        }
        uVar2++;
        piVar3++;
    } while (uVar2 < 2);
    out[0] = -1;
    out[1] = -1;
}

// @ 0x006f41e0
cViewer* cRenderInstanceSet::RenderRange(void* src) {
    int i = 0;
    while (i < 2 && mArr1b4[i] < 0) i++;
    if (i >= 2) return 0;
    int* m = (int*)((void**)mModelArray)[i];
    if (*(unsigned short*)((char*)m + 8) == 0xffff) return 0;
    mViewer174->Copy(src, 0, 0);
    unsigned short idx = *(unsigned short*)((char*)m + 8);
    void* base = *(void**)((char*)m + 0x4c);
    mViewer174->f4be0((char*)base + idx * 8, 1);
    mViewer174->f3c20(&g_1619530);
    mViewer174->f3c50(7);
    return mViewer174;
}

// @ 0x006f4280
void cRenderInstanceSet::UpdateEffects(int dt) {
    Tick154(dt);
    for (int i = 0; i < 2; i++) {
        float* p = ((float**)mModelArray)[i];
        if (*p > 0.0f) {
            *p = *p - (float)(unsigned int)dt * 0.001f;
            if (*p < 0.0f) {
                if (p[1] == 1) {
                    v8((mRangeEnd - mRangeBegin) / 120);
                }
                *p = 0.0f;
            }
        }
    }
}

// -----------------------------------------------------------------------------------------
// Graphics hash-bucket rebuild helper.
// -----------------------------------------------------------------------------------------
struct cGraphicsHash {
    void* m0;            // +0x0
    void** mBuckets;     // +0x4
    unsigned int mCount; // +0x8
    void Resize(unsigned int newSize);
};

// @ 0x006f4330
void cGraphicsHash::Resize(unsigned int newSize) {
    unsigned int bytes = newSize * 4;
    void* p = EASTL_allocator_allocate(bytes + 4, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    memset_thunk(p, 0, bytes);
    *(int*)((char*)p + bytes) = -1;
    for (unsigned int i = 0; i < mCount; i++) {
        void* node = mBuckets[i];
        while (node) {
            unsigned short key = *(unsigned short*)node;
            mBuckets[i] = *(void**)((char*)node + 8);
            unsigned int idx = key % newSize;
            *(void**)((char*)node + 8) = *(void**)((char*)p + idx * 4);
            *(void**)((char*)p + idx * 4) = node;
            node = mBuckets[i];
        }
    }
    if (mCount > 1) EASTL_allocator_deallocate(mBuckets);
    mBuckets = (void**)p;
    mCount = newSize;
}
