// src/game/SPEngine/SPGraphicsEffectUtilities.cpp -- migrated from slice(s) s006f3410 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsEffectUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cViewer.h"

// unnamed retail callees and globals (address in the comment)
extern float g_153415c;   // 0x153415c
#include <math.h>

// ---- items of slice s006f3410 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_153415c;   // 0x153415c
struct IVertexSink {
    virtual int  Lock(int wanted, char** pDst, int* pStride);   // returns how many it granted
    virtual void Unlock();
};
class cModelInstanceSet {
public:
    virtual void v0(IVertexSink* pSink);         // 0x6f3410
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
    float* p = (float*)mTBegin;
    int n = (int)(((char*)mTEnd - (char*)mTBegin) / 0x38);
    while (n-- > 0) {
        UpdateBounds(b, p);
        UpdateRadius(&radius, p);
        p += 0x38 / 4;
    }
    (*(void (__thiscall**)(void*, int, float*, float))(Vt(mRenderer) + 13))(mRenderer, mSetID, b, radius);
}
