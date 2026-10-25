// slice s00709cf0: cLightingWorld shutdown / state helpers and the local light
// deque destructor.  /O2 + SSE region.
#include <new>
#include <intrin.h>
#include "types.h"

void __cdecl EastlFree(void* p);                       // 0x00F47380

struct Alloc {
    void Destroy(void* p);
};
extern Alloc* g_pAlloc;                                // 0x016C8B44

// ===========================================================================
// spstl::simple_deque<slot_vector_entry<cLocalLightInfo>>::ClearImpl
// ===========================================================================
struct ClearDeque {
    void** mpBegin;     // +0x00
    void** mpEnd;       // +0x04
    char pad8[0xc];
    int mField14;       // +0x14
    void ClearImpl(int unused);
};

// @ 0x0070a1f0
void ClearDeque::ClearImpl(int)
{
    while (mpBegin != mpEnd) {
        char* e = (char*)(mField14 * 0xc4 + *(int*)((char*)mpEnd - 4));
        if (((*(int*)e >> 31) & 1) == 0) {
            void* x = *(void**)(e + 0x2c);
            if (x && x != *(void**)(e + 0x3c))
                EastlFree(x);
        }
        if (mField14 == 0) {
            g_pAlloc->Destroy(*(void**)((char*)mpEnd - 4));
            mpEnd -= 1;
            mField14 = 0x7f;
        } else {
            --mField14;
        }
    }
}

// ===========================================================================
// cLightingWorld state helpers
// ===========================================================================
struct StateSource {
    void* Create(void* state);          // 0x705af0
};

// External helpers called by the lighting-world entry points.
void* __cdecl VectorAdjust(void* begin, void* end, uint32_t count);       // 0x011e0744
void  __cdecl VectorEraseTo(void* dst, void* end);                      // 0x00707a00
bool  __cdecl GetPropertyAsColorRGB(void* props, int id, float* out);   // 0x006a11b0
bool  __cdecl GetPropertyAsVector3(void* props, int id, float* out);    // 0x006a1110
void  __cdecl ScaleSH(float scale, int bands, int data);                // 0x00783410
void  __cdecl MirrorSHInZ(int bands, int data);                         // 0x00783c90
void  __cdecl RotateSHAboutZ(int end, int count, float* value);         // 0x00707b70
void  __cdecl FinalSH(int bands, float* coeffs, int data, float* dst);  // 0x00783f40
uint32_t* __cdecl FNV1_String8();                                         // 0x0041e990
void  __cdecl VectorInitA(uint32_t count, void* alloc);                   // 0x00706af0
void  __cdecl VectorInitB(uint32_t count, void* alloc);                   // 0x004aa350
void  __cdecl CopyRange(void** srcPtr, void* begin, void* end,
                        void* dst, void* src);                          // 0x00705c40
extern float g_shScale;                                                 // 0x016299f8

struct cLightingWorld;

// Small vector/deque shapes used by the shutdown / constructor paths.
struct SlotDeque {
    void*  mpBegin;      // +0x00
    void*  mpEnd;        // +0x04
    char   pad08[0x10];
    uint32_t mLast;        // +0x18
    uint32_t mFirst;       // +0x1c

    void Pop();          // 0x00707f40
};

struct FloatVector {
    void* mpBegin;       // +0x00
    void* mpEnd;         // +0x04
    char  pad08[8];

    void Fill(void* end, uint32_t count, const uint32_t* value);  // 0x004cea40
};

struct EnvCacheArea {
    char   pad00[0x18];
    uint32_t field18;      // +0x18
    uint32_t field1C;      // +0x1c
    void*  mpBegin;      // +0x20
    void*  mpEnd;        // +0x24
    char   pad28[0xc];
    uint32_t field34;      // +0x34
    uint8_t  field38;      // +0x38
    char   pad39[3];
    uint32_t field3C;      // +0x3c
    char   pad40[0x2c];
    void*  mListNode;    // +0x6c
    void*  mListEnd;     // +0x70

    void Destroy(cLightingWorld* owner);   // 0x007075e0
};

struct LocalCacheArea {
    char       pad00[0x18];
    uint32_t     field18;      // +0x18
    uint32_t     field1C;      // +0x1c
    void*      mpBegin;      // +0x20
    void*      mpEnd;        // +0x24
    char       pad28[0xc];
    SlotDeque  mSlots;       // +0x34
    uint32_t     field54;      // +0x54
    uint8_t      field58;      // +0x58
    char       pad59[0x27];

    void Destroy(cLightingWorld* owner);   // 0x007075e0
};

struct cLightingWorld {
    char   pad000[0xc];
    void*  mDebugBegin;      // 0x00c
    void*  mDebugEnd;        // 0x010
    void*  mDebugCap;        // 0x014
    char   pad018[0x1c];
    uint32_t mHash;            // 0x034
    uint32_t mHashSq;          // 0x038
    uint32_t mField3C;         // 0x03c
    char   pad040[0x40c];
    char   mDeque44C[0x2c];  // 0x44c
    void*  mVec478;          // 0x478
    void*  mVec47C;          // 0x47c
    char   pad480[0x110];
    uint8_t  mField590;        // 0x590
    char   pad591[3];
    EnvCacheArea   mEnvCache;    // 0x594
    LocalCacheArea mLocalCache;  // 0x608

    void SetLightingState(void* state);
    void Update();                       // 0x7094c0
    void PreUpdate();                    // 0x7087a0
    bool Shutdown();
    bool ConfigFromProperties();           // 0x70a2a0
};

// @ 0x0070a560
void cLightingWorld::SetLightingState(void* state)
{
    if (*(void**)((char*)this + 0x14) != state) {
        if (state) {
            void* v = ((StateSource*)*(void**)((char*)this + 0xc))->Create(state);
            *(void**)((char*)this + 0x10) = v;
            _ReadWriteBarrier();
            *(void**)((char*)this + 0x14) = state;
            Update();
        } else {
            *(void**)((char*)this + 0x10) = 0;
            *(void**)((char*)this + 0x14) = state;
            Update();
        }
    }
}

// ===========================================================================
// remaining cLightingWorld entry points
// ===========================================================================
// @ 0x00709cf0
void __cdecl FUN_00709cf0(int param_1, int param_2, int param_3,
                          void* param_4, int param_5)
{
    uint32_t n = (uint32_t)(param_3 * param_3);
    bool mirrored = false;
    float color[3];

    if (GetPropertyAsColorRGB(param_4, param_5, color)) {
        float* p = (float*)param_2;
        for (uint32_t i = 0; i < n; ++i) {
            p[0] *= color[0];
            p[1] *= color[1];
            p[2] *= color[2];
            p += 4;
        }
    }

    float vec[3];
    if (GetPropertyAsVector3(param_4, param_5 + 1, vec)) {
        if (vec[0] != 0.0f)
            ScaleSH(vec[0] * g_shScale, param_3, param_2);
        if (0.0f < vec[1])
            MirrorSHInZ(param_3, param_2);
        mirrored = true;
        if (vec[2] == 0.0f)
            mirrored = false;
    }

    float* coeffBegin = *(float**)(param_1 + 0xbc);
    float* coeffEnd = *(float**)(param_1 + 0xc0);
    int current = (int)((char*)coeffEnd - (char*)coeffBegin) >> 4;
    if (current < (int)n) {
        float zero[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        if ((int)n < current || n - (uint32_t)current == 0)
            VectorEraseTo((char*)coeffBegin + n * 0x10, coeffEnd);
        else
            RotateSHAboutZ((int)coeffEnd, (int)(n - (uint32_t)current), zero);
    }

    if (!mirrored) {
        for (uint32_t i = 0; i < n; ++i) {
            float* dst = coeffBegin + i * 4;
            float* src = (float*)param_2 + i * 4;
            dst[0] += src[0];
            dst[1] += src[1];
            dst[2] += src[2];
            dst[3] += src[3];
        }
        return;
    }

    float local[199];
    for (uint32_t i = 0; i < n * 4; ++i)
        local[i] = coeffBegin[i];
    FinalSH(param_3, local, param_2, coeffBegin);
}

// @ 0x0070a070
void __fastcall FUN_0070a070(SlotDeque* self)
{
    while (self->mpBegin != self->mpEnd)
        self->Pop();
    if (self->mpBegin)
        EastlFree(self->mpBegin);
}

// ---------------------------------------------------------------------------
// fixed sample vector constructed at 0x0070a0d0
// ---------------------------------------------------------------------------
struct SampleVec {
    void*  mpBegin;      // +0x00
    void*  mpEnd;        // +0x04
    void*  mpCap;        // +0x08
    char   pad0C[4];
    void*  mpPool;       // +0x10
    char   pad14[4];
    char   mInline[0x80];// +0x18 .. +0x97

    void Build(int n);   // 0x00708e60
    SampleVec* Construct(int n);
};

// @ 0x0070a0d0
SampleVec* SampleVec::Construct(int n)
{
    void* inlineBuffer = mInline;
    mpPool = inlineBuffer;
    mpEnd = inlineBuffer;
    mpBegin = inlineBuffer;
    mpCap = (char*)this + 0x98;
    Build(n);
    return this;
}

// ---------------------------------------------------------------------------
// lighting-config copy constructor at 0x0070a130
// ---------------------------------------------------------------------------
struct LightCfgCopy {
    void* mpBegin0;      // +0x00
    void* mpEnd0;        // +0x04
    char  pad08[4];
    void* mpField0C;     // +0x0c
    void* mpField10;     // +0x10
    void* mpBegin5;      // +0x14
    void* mpEnd6;        // +0x18
    char  pad1C[4];
    void* mpField20;     // +0x20
    char  pad24[4];
    void* mpField28;     // +0x28

    LightCfgCopy* CopyFrom(LightCfgCopy* src);
};

// @ 0x0070a130
LightCfgCopy* LightCfgCopy::CopyFrom(LightCfgCopy* src)
{
    uint32_t count0 = (uint32_t)((char*)src->mpEnd0 - (char*)src->mpBegin0) >> 5;
    VectorInitA(count0, &src->mpField0C);
    CopyRange((void**)&src, src->mpBegin0, src->mpEnd0, mpBegin0, src);
    mpEnd0 = src;

    uint32_t count1 = (uint32_t)((char*)src->mpEnd6 - (char*)src->mpBegin5) >> 2;
    VectorInitB(count1, &src->mpField20);
    uint32_t bytes = (uint32_t)((char*)src->mpEnd6 - (char*)src->mpBegin5);
    void* end = VectorAdjust(mpBegin5, src->mpBegin5, bytes);
    mpEnd6 = (char*)end + (bytes >> 2) * 4;
    mpField28 = src->mpField28;
    return this;
}

// ---------------------------------------------------------------------------
// app-property driven config resize at 0x0070a2a0
// ---------------------------------------------------------------------------
struct AppProps {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual bool Query(uint32_t id, void** out);   // +0x24
};

struct AppCfg {
    char   pad00[0x12];
    uint16_t mType;        // +0x12
};

extern AppProps* g_appProps;   // 0x015fd918

// @ 0x0070a2a0
bool cLightingWorld::ConfigFromProperties()
{
    AppProps* props = g_appProps;
    if (props != 0) {
        AppCfg* cfg = 0;
        if (props->Query(0x641a468, (void**)&cfg) && cfg != 0 && cfg->mType == 9) {
            uint32_t hash = *FNV1_String8();
            mHash = hash;
            mHashSq = hash * hash;
        }
        AppCfg* cfg2 = 0;
        if (props->Query(0x641a467, (void**)&cfg2) && cfg2 != 0 && cfg2->mType == 9)
            mField3C = *FNV1_String8();
    }

    FloatVector* env = (FloatVector*)&mEnvCache.mpBegin;
    uint32_t envCount = (uint32_t)((char*)mEnvCache.mpEnd - (char*)mEnvCache.mpBegin) >> 2;
    uint32_t fill = 0xffffffff;
    if (envCount < 0x1800) {
        env->Fill(mEnvCache.mpEnd, 0x1800 - envCount, &fill);
    } else {
        void* end = (char*)mEnvCache.mpBegin + 0x6000;
        VectorAdjust(end, mEnvCache.mpEnd, 0);
        mEnvCache.mpEnd = end;
    }

    FloatVector* local = (FloatVector*)&mLocalCache.mpBegin;
    uint32_t localCount = (uint32_t)((char*)mLocalCache.mpEnd - (char*)mLocalCache.mpBegin) >> 2;
    if (localCount < 0x600) {
        local->Fill(mLocalCache.mpEnd, 0x600 - localCount, &fill);
    } else {
        void* end = (char*)mLocalCache.mpBegin + 0x1800;
        VectorAdjust(end, mLocalCache.mpEnd, 0);
        mLocalCache.mpEnd = end;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// cLightingWorld::Shutdown at 0x0070a3f0
// ---------------------------------------------------------------------------
struct IntrusiveNode {
    IntrusiveNode* mpNext;   // +0x00
    IntrusiveNode* mpPrev;   // +0x04
};

void __cdecl DequeClear(void* deque);   // 0x00996460

// @ 0x0070a3f0
bool cLightingWorld::Shutdown()
{
    PreUpdate();
    mDebugEnd = 0;
    mField590 = 0;

    mEnvCache.Destroy(this);
    mEnvCache.field18 = 0x3fffffff;
    mEnvCache.field1C = 0x3fffffff;
    VectorAdjust(mEnvCache.mpBegin, mEnvCache.mpEnd, 0);
    mEnvCache.mpEnd = mEnvCache.mpBegin;
    mEnvCache.field34 = 0xffffffff;
    mEnvCache.field38 = 0;

    mLocalCache.Destroy(this);
    mLocalCache.field18 = 0x3fffffff;
    mLocalCache.field1C = 0x3fffffff;
    VectorAdjust(mLocalCache.mpBegin, mLocalCache.mpEnd, 0);
    mLocalCache.mpEnd = mLocalCache.mpBegin;

    while (mLocalCache.mSlots.mpBegin != mLocalCache.mSlots.mpEnd)
        mLocalCache.mSlots.Pop();
    mLocalCache.mSlots.mLast = 0x3fffffff;
    mLocalCache.mSlots.mFirst = 0x3fffffff;
    mLocalCache.field54 = 0xffffffff;
    mLocalCache.field58 = 0;
    mEnvCache.field3C = 0;

    IntrusiveNode* sentinel = (IntrusiveNode*)&mEnvCache.mListNode;
    IntrusiveNode* node = (IntrusiveNode*)mEnvCache.mListNode;
    while (node != sentinel) {
        IntrusiveNode* next = node->mpNext;
        node->mpPrev = 0;
        node->mpNext = 0;
        node = next;
    }
    mEnvCache.mListEnd = sentinel;
    mEnvCache.mListNode = sentinel;

    DequeClear(mDeque44C);
    VectorAdjust(mVec478, mVec47C, 0);
    mVec47C = mVec478;
    return true;
}

