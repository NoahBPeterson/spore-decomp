// src/game/SPEngine/SPGraphicsEffectUtilities.cpp -- migrated from slice(s) s006f3410 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsEffectUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cViewer.h"

// unnamed retail callees and globals (address in the comment)
extern float g_153415c;   // 0x153415c
#include <math.h>

// ---- items of slice s006f3410 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl EASTL_allocator_deallocate(void* p) throw();                                  // 0xf47380
extern float g_153415c;   // 0x153415c
struct IVertexSink {
    virtual int  Lock(int wanted, char** pDst, int* pStride);   // returns how many it granted
    virtual void Unlock();
};
struct ModelSetVector {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    unsigned mAllocator[2];
    ModelSetVector() {}
    ~ModelSetVector() {
        if (mpBegin && ((int*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
    }
};
class cModelInstanceSet {
public:
    virtual void v0(IVertexSink* pSink);         // 0x6f3410
    virtual void v1();                           // 0x6f3dd0

    unsigned int mModelInstance;                 // +0x4
    unsigned int mModelGroup;                    // +0x8
    ModelSetVector mTransforms;                 // +0x0c
    ModelSetVector mColors;                     // +0x20
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
static __declspec(noinline) void UpdateBounds(float* b, const float* p) {
    if (b[0] > p[1]) b[0] = p[1];
    if (b[3] < p[1]) b[3] = p[1];
    if (b[1] > p[2]) b[1] = p[2];
    if (b[4] < p[2]) b[4] = p[2];
    if (b[2] > p[3]) b[2] = p[3];
    if (b[5] < p[3]) b[5] = p[3];
}
static __declspec(noinline) void UpdateRadius(float* r, const float* p) {
    if (*r < p[4]) *r = p[4];
}
// ---- items of slice s006f3410 end

// @ 0x006f3b70
void cModelInstanceSet::Update()
{
    if (mSetID < 0) return;
    float b[6];
    b[0] = g_153415c; b[1] = g_153415c; b[2] = g_153415c;
    b[3] = -g_153415c; b[4] = -g_153415c; b[5] = -g_153415c;
    float radius = 0.0f;
    float* p = (float*)mTransforms.mpBegin;
    int n = (int)(((char*)mTransforms.mpEnd - (char*)mTransforms.mpBegin) / 0x38);
    while (n-- > 0) {
        UpdateBounds(b, p);
        UpdateRadius(&radius, p);
        p += 0x38 / 4;
    }
    (*(void (__thiscall**)(void*, int, float*, float))(Vt(mRenderer) + 13))(mRenderer, mSetID, b, radius);
}

// @ 0x006f3df0
void cModelInstanceSet::AddToRenderer(void* pRenderer)
{
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
        if ((*(char (__thiscall**)(void*, void*, int*, int*))(Vt(mRenderer) + 11))(mRenderer, this, &m38, &mSetID)) {
            (*(void (__thiscall**)(void*, int, int*))(Vt(mRenderer) + 4))(mRenderer, 9, &m5c);
            (*(void (__thiscall**)(void*, int, int))(Vt(mRenderer) + 14))(mRenderer, mSetID, 1);
            Update();
        }
    }
}
