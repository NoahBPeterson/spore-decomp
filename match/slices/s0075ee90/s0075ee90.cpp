// Slice s0075ee90: EASTL container helpers for SP::cRenderer render-job lists and
// cLayerInfoExtra (SP::cLayerInfoExtra = the 0x14-byte Elem below).
// /O2, SSE (/arch:SSE2).
#include "types.h"

struct RNode {
    virtual void AddRef();    // vtable slot 0
    virtual void Release();   // vtable slot 1
};

struct Elem {          // 0x14 bytes (SP::cLayerInfoExtra)
    RNode* p;          // +0x00
    int    b;          // +0x04
    int    c;          // +0x08
    int    d;          // +0x0c
    float  f;          // +0x10
    Elem* Copy(Elem* src);
};

// EA::Thread::Mutex (only the 4-byte handle is ever touched here)
struct EA_Mutex {
    int mData;                 // +0x00
};

// eastl::list<SP::cRenderer::cRenderJob> sentinel (intrusive, next/prev at +0/+4)
struct JobList {
    void* mpNext;              // +0x00
    void* mpPrev;              // +0x04
    int   mField08;            // +0x08
};

// SP::cRenderer render-job linked-list node
struct RenderJob {
    RenderJob* mpNext;         // +0x00
    RenderJob* mpPrev;         // +0x04
    RNode*     mpObject;       // +0x08
    int        mField0c;       // +0x0c
    uint32_t   mJobId;         // +0x10 (sRenderJobId value; compared as an integer)
};

// SP::cRenderer.  Only the fields this slice touches are named; everything else is padN.
struct cRenderer {
    void*    mVtbl0;           // +0x00
    void*    mVtbl1;           // +0x04
    char     pad08[0x28 - 0x08];
    EA_Mutex mMutex;           // +0x28
    char     pad2c[0x8c - 0x2c];
    void*    mpNodesA;         // +0x8c  (render-node array)
    char     pad90[0x324 - 0x90];
    JobList  mPostJobs;        // +0x324
    JobList  mPreJobs;         // +0x330
    char     pad33c[0x34c - 0x33c];
    void*    mpNodesB;         // +0x34c (render-node array)
    char     pad350[0x63c - 0x350];
    void*    mpShaderDebug;    // +0x63c
    bool RemovePostRenderJob(uint32_t id);
    bool RemovePreRenderJob(uint32_t id);
};

// eastl::vector<SP::cLayerInfoExtra> (fixed_vector_allocator carries an inline buffer)
struct ElemVec {
    Elem* mpBegin;             // +0x00
    Elem* mpEnd;               // +0x04
    Elem* mpCapacity;          // +0x08
    int   mField0c;            // +0x0c
    Elem* mpInlineBuffer;      // +0x10
};

// ---------------------------------------------------------------- external helpers / data
extern "C" void* EASTL_allocator_allocate(unsigned n, const char* name, int a, int b,
                                          const char* file, int line);       // @ 0x00f473a0
extern "C" void  EASTL_deallocate(void* p);                                  // @ 0x00f47380
extern void  DestroyElemRange(void* first, void* last);                      // @ 0x0075e6a0
extern void  RelocateElemRange(void* first, void* last, void* mem);          // @ 0x0075e7f0
extern void  CopyRenderNode(void* dst, void* src);                           // @ 0x0075ed50
extern void  FreeRenderNodeArray(void* p);                                   // @ 0x0075eda0
extern void* MakeRenderSubObject(void* list, void* job);                     // @ 0x0075e750
extern void  RenderJobListErase(void* list);                                 // @ 0x0075f3f0
extern void  EAMutexLock(void* m, unsigned int pTimeoutMS);                  // @ 0x009221b0
extern void  EAMutexUnlock(void* m);                                         // @ 0x00922270
extern void  EAMutexDtor(void* m);                                           // @ 0x00922130
extern int   sRenderJobId;                                                   // @ 0x0162fc64
extern const unsigned int g_mutexInfiniteWait;                               // @ 0x0140dca0
extern char  g_vtbl_cRenderer;                                               // @ 0x0140dce8
extern char  g_vtbl_cRenderer1;                                              // @ 0x0140dce4
extern char  g_vtbl_dtorBase0;                                               // @ 0x013eb938
extern char  g_vtbl_dtorBase1;                                               // @ 0x013ef094

// The EASTL allocator source path baked into the originals.
static const char kAllocatorH[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// @ 0x0075ee90
Elem* Elem::Copy(Elem* src)
{
    Elem* dst = this;
    RNode* p = src->p;
    dst->p = p;
    if (p != 0)
        ((void (__thiscall*)(void*))*(void**)(*(int*)p))(p);
    dst->b = src->b;
    dst->c = src->c;
    dst->d = src->d;
    dst->f = src->f;
    return dst;
}

// @ 0x0075eed0  (SP::CopyElemRange: uninitialized copy of a 0x14-byte element range)
void* CopyElemRange(void* first, void* last, void* dst)
{
    Elem* f = (Elem*)first;
    Elem* l = (Elem*)last;
    Elem* d = (Elem*)dst;
    while (f != l) {
        if (d != 0) {
            RNode* p = f->p;
            d->p = p;
            if (p != 0)
                ((void (__thiscall*)(void*))*(void**)(*(int*)p))(p);
            d->b = f->b;
            d->c = f->c;
            d->d = f->d;
            d->f = f->f;
        }
        f++;
        d++;
    }
    return d;
}

// @ 0x0075ef80  (construct a range into an array whose write cursor is *pDst)
void* ConstructElemArrayImpl(void* pDst, void* first, void* last, void* mem)
{
    Elem** pd = (Elem**)pDst;
    Elem* f = (Elem*)first;
    Elem* l = (Elem*)last;
    *pd = (Elem*)mem;
    while (f != l) {
        Elem* d = *pd;
        if (d != 0) {
            RNode* p = f->p;
            d->p = p;
            if (p != 0)
                ((void (__thiscall*)(void*))*(void**)(*(int*)p))(p);
            d->b = f->b;
            d->c = f->c;
            d->d = f->d;
            d->f = f->f;
        }
        *pd = (Elem*)((char*)*pd + 0x14);
        f++;
    }
    return pd;
}

// @ 0x0075f430  (copy_backward, EASTL uninitialized/relocate flavour)
Elem* CopyBackward(Elem* first, Elem* last, Elem* dest)
{
    if (last == first)
        return dest;
    do {
        last--;
        dest--;
        RNode* np = last->p;
        RNode* dp = dest->p;
        if (np != dp) {
            if (np != 0)
                ((void (__thiscall*)(void*))*(void**)(*(int*)np))(np);
            dest->p = np;
            if (dp != 0)
                ((void (__thiscall*)(void*))*(void**)(*(int*)dp + 4))(dp);
        }
        dest->b = last->b;
        dest->c = last->c;
        dest->d = last->d;
        dest->f = last->f;
    } while (last != first);
    return dest;
}

// @ 0x0075f4a0  (copy forward)
Elem* CopyForward(Elem* first, Elem* last, Elem* dest)
{
    if (first == last)
        return dest;
    do {
        RNode* np = first->p;
        RNode* dp = dest->p;
        if (np != dp) {
            if (np != 0)
                ((void (__thiscall*)(void*))*(void**)(*(int*)np))(np);
            dest->p = np;
            if (dp != 0)
                ((void (__thiscall*)(void*))*(void**)(*(int*)dp + 4))(dp);
        }
        dest->b = first->b;
        dest->c = first->c;
        dest->d = first->d;
        dest->f = first->f;
        first++;
        dest++;
    } while (first != last);
    return dest;
}

// @ 0x0075f510  (SP::cRenderer::AddPostRenderJob: build a render job, link it under the lock)
unsigned int AddPostRenderJob(void* self_, void* layer_, int a3, void* info_)
{
    cRenderer* self = (cRenderer*)self_;

    char job[0x38];
    int* jd = (int*)job;
    for (int i = 0; i < 0x38 / 4; ++i)
        jd[i] = 0;

    if (layer_ != 0) {
        ((void (__thiscall*)(void*))*(void**)(*(int*)layer_))(layer_);   // AddRef
        jd[0] = (int)layer_;
    }
    jd[1] = a3;
    jd[2] = sRenderJobId++;
    for (int i = 0; i < 0xb; ++i)
        jd[3 + i] = ((int*)info_)[i];

    EAMutexLock(&self->mMutex, (unsigned int)&g_mutexInfiniteWait);
    RenderJob* node = (RenderJob*)MakeRenderSubObject(&self->mPostJobs, job);
    node->mpNext = (RenderJob*)&self->mPostJobs;
    node->mpPrev = (RenderJob*)self->mPostJobs.mpPrev;
    ((RenderJob*)self->mPostJobs.mpPrev)->mpNext = node;
    self->mPostJobs.mpPrev = node;
    EAMutexUnlock(&self->mMutex);

    if (jd[0] != 0)
        ((void (__thiscall*)(void*))*(void**)(*(int*)jd[0] + 4))((void*)jd[0]);   // Release
    return (unsigned int)jd[2];
}

// @ 0x0075f640  (SP::cRenderer::AddPreRenderJob: same, queued on the pre-render list)
unsigned int AddPreRenderJob(void* self_, void* layer_, int a3, void* info_)
{
    cRenderer* self = (cRenderer*)self_;

    char job[0x38];
    int* jd = (int*)job;
    for (int i = 0; i < 0x38 / 4; ++i)
        jd[i] = 0;

    if (layer_ != 0) {
        ((void (__thiscall*)(void*))*(void**)(*(int*)layer_))(layer_);   // AddRef
        jd[0] = (int)layer_;
    }
    jd[1] = a3;
    jd[2] = sRenderJobId++;
    for (int i = 0; i < 0xb; ++i)
        jd[3 + i] = ((int*)info_)[i];

    EAMutexLock(&self->mMutex, (unsigned int)&g_mutexInfiniteWait);
    RenderJob* node = (RenderJob*)MakeRenderSubObject(&self->mPreJobs, job);
    node->mpNext = (RenderJob*)&self->mPreJobs;
    node->mpPrev = (RenderJob*)self->mPreJobs.mpPrev;
    ((RenderJob*)self->mPreJobs.mpPrev)->mpNext = node;
    self->mPreJobs.mpPrev = node;
    EAMutexUnlock(&self->mMutex);

    if (jd[0] != 0)
        ((void (__thiscall*)(void*))*(void**)(*(int*)jd[0] + 4))((void*)jd[0]);   // Release
    return (unsigned int)jd[2];
}

// @ 0x0075f770
void* AllocElemArray(unsigned count, void* dst, void* src)
{
    void* mem;
    if (count == 0)
        mem = 0;
    else
        mem = EASTL_allocator_allocate(count * 0x14, "Graphics", 0, 0, kAllocatorH, 0xd1);
    ConstructElemArrayImpl(&count, dst, src, mem);
    return mem;
}

// @ 0x0075f7e0  (SP::cRenderer::~cRenderer: tear the render-job lists and owned nodes down)
void* DestroyRenderJobList(void* self_)
{
    cRenderer* self = (cRenderer*)self_;
    self->mVtbl0 = &g_vtbl_cRenderer;
    self->mVtbl1 = &g_vtbl_cRenderer1;
    if (self->mpShaderDebug != 0)
        ((void (__thiscall*)(void*))*(void**)(*(int*)self->mpShaderDebug + 4))(self->mpShaderDebug);
    FreeRenderNodeArray(self->mpNodesB);
    RenderJobListErase(&self->mPreJobs);
    RenderJobListErase(&self->mPostJobs);
    FreeRenderNodeArray(self->mpNodesA);
    EAMutexDtor(&self->mMutex);
    self->mVtbl1 = &g_vtbl_dtorBase1;
    self->mVtbl0 = &g_vtbl_dtorBase0;
    return self;
}

// @ 0x0075f8a0  (SP::cRenderer::RemovePostRenderJob)
bool cRenderer::RemovePostRenderJob(uint32_t id)
{
    void* self = this;
    char* sentinel = (char*)self + 0x324;
    RenderJob* n = *(RenderJob**)((char*)self + 0x324);
    if (n == (RenderJob*)sentinel)
        return false;
    while (n->mJobId != id) {
        n = n->mpNext;
        if (n == (RenderJob*)sentinel)
            return false;
    }
    // The original advances to n->next before testing the id and then recovers the
    // node as next->prev; that is the node actually unlinked (and differs from n
    // when the list links are inconsistent).
    RenderJob* target = n->mpNext->mpPrev;
    target->mpPrev->mpNext = target->mpNext;
    target->mpNext->mpPrev = target->mpPrev;
    if (target->mpObject != 0)
        ((void (__thiscall*)(void*))*(void**)(*(int*)target->mpObject + 4))(target->mpObject);
    EASTL_deallocate(target);
    return true;
}

// @ 0x0075f900  (SP::cRenderer::RemovePreRenderJob)
bool cRenderer::RemovePreRenderJob(uint32_t id)
{
    void* self = this;
    char* sentinel = (char*)self + 0x330;
    RenderJob* n = *(RenderJob**)((char*)self + 0x330);
    if (n == (RenderJob*)sentinel)
        return false;
    while (n->mJobId != id) {
        n = n->mpNext;
        if (n == (RenderJob*)sentinel)
            return false;
    }
    RenderJob* target = n->mpNext->mpPrev;
    target->mpPrev->mpNext = target->mpNext;
    target->mpNext->mpPrev = target->mpPrev;
    if (target->mpObject != 0)
        ((void (__thiscall*)(void*))*(void**)(*(int*)target->mpObject + 4))(target->mpObject);
    EASTL_deallocate(target);
    return true;
}

// @ 0x0075fc70  (eastl::vector<cLayerInfoExtra>::insert(pos, value))
void* InsertElemN(void* self_, void* pos_, void* value_)
{
    ElemVec* v = (ElemVec*)self_;
    Elem* pos = (Elem*)pos_;
    Elem* value = (Elem*)value_;
    Elem* end = v->mpEnd;

    if (end != v->mpCapacity) {
        if (pos <= value && value < end)
            value++;
        if (end != 0) {
            RNode* p = end[-1].p;
            end->p = p;
            if (p != 0)
                ((void (__thiscall*)(void*))*(void**)(*(int*)p))(p);
            end->b = end[-1].b;
            end->c = end[-1].c;
            end->d = end[-1].d;
            end->f = end[-1].f;
        }
        CopyBackward(pos, end - 1, end);
        CopyRenderNode(pos, value);
        v->mpEnd = end + 1;
        return self_;
    }

    unsigned off = (unsigned)(((char*)end - (char*)v->mpBegin) / 0x14);
    unsigned newCap = off ? off * 2 : 1;
    Elem* newData = 0;
    if (newCap != 0)
        newData = (Elem*)EASTL_allocator_allocate(newCap * 0x14, "Graphics", 0, 0, kAllocatorH, 0xd1);

    Elem* p = (Elem*)CopyElemRange(v->mpBegin, pos, newData);
    RelocateElemRange(v->mpBegin, pos, newData);
    if (p != 0) {
        RNode* q = value->p;
        p->p = q;
        if (q != 0)
            ((void (__thiscall*)(void*))*(void**)(*(int*)q))(q);
        p->b = value->b;
        p->c = value->c;
        p->d = value->d;
        p->f = value->f;
    }

    Elem* last = v->mpEnd;
    Elem* newEnd = (Elem*)CopyElemRange(pos, last, p + 1);
    RelocateElemRange(pos, last, p + 1);

    if (v->mpBegin != 0 && v->mpBegin != v->mpInlineBuffer)
        EASTL_deallocate(v->mpBegin);

    v->mpEnd = newEnd;
    v->mpBegin = newData;
    v->mpCapacity = (Elem*)((char*)newData + newCap * 0x14);
    return self_;
}

// @ 0x0075fe50  (eastl::vector<cLayerInfoExtra>::DoAssignFromIterator(first, last))
void* ResizeElemArray(void* self_, void* first_, void* last_)
{
    ElemVec* v = (ElemVec*)self_;
    Elem* first = (Elem*)first_;
    Elem* last = (Elem*)last_;
    Elem* begin = v->mpBegin;
    unsigned n = (unsigned)(((char*)last - (char*)first) / 0x14);

    if ((unsigned)(((char*)v->mpCapacity - (char*)begin) / 0x14) < n) {
        Elem* newData = (Elem*)AllocElemArray(n, first, last);
        DestroyElemRange(v->mpBegin, v->mpEnd);
        if (v->mpBegin != 0 && v->mpBegin != v->mpInlineBuffer)
            EASTL_deallocate(v->mpBegin);
        Elem* newEnd = (Elem*)((char*)newData + n * 0x14);
        v->mpBegin = newData;
        v->mpEnd = newEnd;
        v->mpCapacity = newEnd;
        return self_;
    }

    unsigned have = (unsigned)(((char*)v->mpEnd - (char*)begin) / 0x14);
    if (n <= have) {
        Elem* r = CopyForward(first, last, begin);
        DestroyElemRange(r, v->mpEnd);
        v->mpEnd = r;
        return self_;
    }

    Elem* mid = (Elem*)((char*)first + have * 0x14);
    CopyForward(first, mid, begin);
    ConstructElemArrayImpl(&last, mid, last, v->mpEnd);
    v->mpEnd = last;
    return self_;
}

// ---------------------------------------------------------------- not yet reconstructed
// ===========================================================================
// SP::cRenderer::Start (0x0075f030).
// Reads the six renderer app properties, runs the rw::graphics::Device startup
// handshake (canvas device -> default params -> callbacks -> StartInternal) and,
// on success, pushes the device parameters and screen info into the renderer and
// initialises the shaders.
// ===========================================================================

// SP::cDirectPropertyList (used through its vtable: slot 0x1c = HasProperty,
// slot 0x14 = SetProperty(Variant)).
struct cPropertyListBase {
    virtual void v00();                               // +0x00
    virtual void v04();                               // +0x04
    virtual void v08();                               // +0x08
    virtual void v0c();                               // +0x0c
    virtual void v10();                               // +0x10
    virtual void SetProp(unsigned int key, void* v);  // +0x14
    virtual void v18();                               // +0x18
    virtual bool HasProperty(unsigned int key);       // +0x1c
};
struct PropListFull {
    cPropertyListBase* mVtbl;                         // +0x00
    int  GetIntProperty(unsigned int key) const;      // 0x006a2660
    bool GetDescription(unsigned int key) const;      // 0x006a25a0
};

extern PropListFull* g_appProperties015fd918;         // 0x015fd918 (_sAppProperties_SP_...)
extern int  g_renderParam0_015d07c0;                  // 0x015d07c0
extern int  g_renderParam1_015d07c4;                  // 0x015d07c4
extern float g_one_01485720;                          // 0x01485720

extern void  FUN_011f8110(void* device);              // 0x011f8110
extern void  DeviceGetDefaultParameters(int which);   // 0x011f8340
extern void  FUN_011f8240(void* fn);                  // 0x011f8240
extern void  FUN_011f8250(void* fn);                  // 0x011f8250
extern void  FUN_011f8260(void* fn);                  // 0x011f8260
extern int   DeviceStartInternal(void* params);       // 0x011f8680
extern void* FUN_00689590();                          // 0x00689590
extern void  FUN_00689560(void* token);               // 0x00689560
extern void  DeviceShutdownD3D();                     // 0x011f7fa0
extern void* Canvas();                                // 0x0067dcf0
extern void  RenderSettings(int flag);                // 0x0075de80
extern bool  RenderStageReady(int x);                 // 0x0075e620
extern void  BuildPaletteTable(float v);              // 0x0075dc20
extern bool  cRendererInitShaders();                  // 0x0075dca0
extern void  FUN_0075d930();                          // 0x0075d930
extern void  DeviceRelease();                         // 0x0075d950
extern void  PaintSystemInit();                       // 0x0075d990

struct DeviceParams {                                  // 0x3c-byte rw device parameter block
    int   mField00;
    int   mField04;
    int   mField08;
    int   mField0c;
    int   mField10;
    int   mField14;
    int   mField18;
    int   mField1c;
    int   mField20;
    int   mField24;
    int   mField28;
    int   mField2c;
    int   mField30;
    int   mField34;
    int   mField38;
};

extern DeviceParams g_deviceParams;                     // 0x01712444
extern int  FUN_00689590_token;                         // (opaque start token)

// ===========================================================================
// SP::cRenderer constructor rebuild (0x0075f960).
// The slice's cRenderer struct above only carries the fields the other helpers
// touch; the constructor writes a much larger, exact layout, so it uses this
// separate byte-accurate view (member names are by role where known).
// ===========================================================================

struct MutexObj {                                     // EA::Thread::Mutex
    void ctor(const void* params, bool b);            // 0x009222a0
    int mData;
};

struct StopwatchObj {                                 // EA::Stopwatch, 0x18 bytes
    void ctor(int a, bool b);                         // 0x0093a560
    int mData[6];
};

struct FixedVecLayers {                               // eastl fixed_vector with inline pool
    void* mSlot00;                                    // +0x00
    void* mSlot04;                                    // +0x04
    void* mSlot08;                                    // +0x08
    void* mSlot0c;                                    // +0x0c
    void* mSlot10;                                    // +0x10
    char  pad14[4];
    char  mBuffer[0x280];                             // +0x18
};

struct ShaderDataDebugPS {
    char  mDebugInfo[0x10];                           // +0x00
    void* mField10;                                   // +0x10
    void* mField14;                                   // +0x14
    float mField18;                                   // +0x18
    void* mField1c;                                   // +0x1c
    void* mField20;                                   // +0x20
    void* mField24;                                   // +0x24
    void  RenderStageReady();                         // 0x0075e620
};

struct RenderStats {
    float mRenderTime;                                // +0x00
    float mLayers;                                    // +0x04
    float mJobs;                                      // +0x08
    float mJobsQueued;                                // +0x0c
    float mVertices;                                  // +0x10
    float mIndices;                                   // +0x14
    float mPrimitives;                                // +0x18
};

struct JobList8 {                                     // intrusive eastl::list sentinel (8 bytes)
    void* mpNext;                                     // +0x00
    void* mpPrev;                                     // +0x04
};

struct ScreenInfoBlock {                              // +0x05c .. +0x08b
    int mWidth;                                       // +0x00  (0x5c)
    int mHeight;                                      // +0x04  (0x60)
    int mField08;                                     // +0x08  (0x64)
    int mField0c;                                     // +0x0c  (0x68)
    int mField10;                                     // +0x10  (0x6c, low byte written)
    int mField14;                                     // +0x14  (0x70)
    int mField18;                                     // +0x18  (0x74)
    int mField1c;                                     // +0x1c  (0x78)
    int mViewers[4];                                  // +0x20  (0x7c..0x88)
};

struct cRendererLayout {
    void* mVtbl0;                                     // +0x000
    void* mVtbl1;                                     // +0x004
    int   mRefCount;                                  // +0x008
    bool  mInitialized;                               // +0x00c
    bool  mDeviceStarted;                             // +0x00d
    char  pad00e[2];                                  // +0x00e
    int   mRenderJobBudget;                           // +0x010
    int   mDefaultRenderJobBudget;                    // +0x014
    bool  mDumpShaderData;                            // +0x018
    bool  mDisableFill;                               // +0x019
    bool  mFlushGPUPipeline;                          // +0x01a
    bool  mField1b;                                   // +0x01b
    bool  mField1c;                                   // +0x01c
    char  pad01d[3];                                  // +0x01d
    int   mMutexData;                                 // +0x020
    char  pad024[4];                                  // +0x024
    MutexObj mMutex;                                  // +0x028
    char  pad02c[0x58 - 0x2c];                        // +0x02c
    int   mField58;                                   // +0x058
    ScreenInfoBlock mScreenInfo;                      // +0x05c
    FixedVecLayers mLayers;                           // +0x08c
    JobList8 mPostJobs;                               // +0x324
    char  pad32c[4];                                  // +0x32c
    JobList8 mPreJobs;                                // +0x330
    char  pad338[4];                                  // +0x338
    int   mFrameViewers[4];                           // +0x33c
    FixedVecLayers mFrameLayers;                      // +0x34c
    char  pad5e4[4];                                  // +0x5e4
    StopwatchObj mTimer;                              // +0x5e8
    RenderStats mRenderStats;                         // +0x600
    int   mField61c;                                  // +0x61c
    int   mField620;                                  // +0x620
    int   mField624;                                  // +0x624
    int   mField628;                                  // +0x628
    int   mField62c;                                  // +0x62c
    int   mField630;                                  // +0x630
    bool  mFPSStatsAdded;                             // +0x634
    bool  mShowRenderStats;                           // +0x635
    bool  mIsPerfHUDActive;                           // +0x636
    char  pad637;                                     // +0x637
    ShaderDataDebugPS mDbgPS;                         // +0x638

    void RenderSettings(int flag);                    // 0x0075de80
    void BuildPaletteTable(float value);              // 0x0075dc20
    bool InitShaders();                               // 0x0075dca0
};

struct cRendererInitView {
    void* RenderJobListCtor();                         // 0x0075f960
};

extern float g_zero_13eb1bc;                          // 0x013eb1bc
extern char  g_vtbl_dtorBase2;                        // 0x013ef094

struct RenderNodeInit {                               // thiscall target of InitRenderNode (0x0075ee10)
    void* InitRenderNode(void* owner, int id, float f);
};

// @ 0x0075f960  SP::cRenderer::cRenderer
void* cRendererInitView::RenderJobListCtor()
{
    cRendererLayout* self = (cRendererLayout*)this;

    self->mVtbl1 = &g_vtbl_dtorBase2;                 // intermediate base vtable
    self->mRefCount = 0;
    const int five = 5;
    self->mVtbl0 = &g_vtbl_cRenderer;
    self->mVtbl1 = &g_vtbl_cRenderer1;
    self->mInitialized = false;
    self->mDeviceStarted = false;
    self->mRenderJobBudget = five;
    self->mDefaultRenderJobBudget = five;
    self->mDumpShaderData = false;
    self->mDisableFill = false;
    self->mFlushGPUPipeline = false;
    self->mField1b = false;
    self->mField1c = false;
    self->mMutexData = 0;
    self->mMutex.ctor(0, true);

    self->mField58 = 0;
    int zero = 0;
    self->mScreenInfo.mWidth = zero;
    self->mScreenInfo.mHeight = zero;
    self->mScreenInfo.mField08 = zero;
    self->mScreenInfo.mField0c = zero;
    self->mScreenInfo.mField10 = zero;
    self->mScreenInfo.mField14 = zero;
    self->mScreenInfo.mField18 = zero;
    self->mScreenInfo.mField1c = zero;

    char* buf = self->mLayers.mBuffer;
    self->mLayers.mSlot10 = buf;
    self->mLayers.mSlot04 = buf;
    self->mLayers.mSlot00 = buf;
    self->mLayers.mSlot08 = buf + 0x280;

    self->mPostJobs.mpNext = &self->mPostJobs;
    self->mPostJobs.mpPrev = &self->mPostJobs;
    self->mPreJobs.mpNext = &self->mPreJobs;
    self->mPreJobs.mpPrev = &self->mPreJobs;

    char* buf2 = self->mFrameLayers.mBuffer;
    self->mFrameLayers.mSlot10 = buf2;
    self->mFrameLayers.mSlot04 = buf2;
    self->mFrameLayers.mSlot00 = buf2;
    self->mFrameLayers.mSlot08 = buf2 + 0x280;

    self->mTimer.ctor(4, false);

    self->mRenderStats.mRenderTime = 0.0f;
    self->mRenderStats.mLayers = 0.0f;
    self->mRenderStats.mJobs = 0.0f;
    self->mRenderStats.mJobsQueued = 0.0f;
    self->mRenderStats.mVertices = 0.0f;
    self->mRenderStats.mIndices = 0.0f;
    self->mRenderStats.mPrimitives = 0.0f;
    self->mField61c = 0;
    self->mField620 = 0;
    self->mField624 = 0;
    self->mField628 = 0;
    self->mField62c = 0;
    self->mField630 = 0;
    self->mFPSStatsAdded = false;
    self->mShowRenderStats = false;
    self->mIsPerfHUDActive = false;
    RenderNodeInit* init = (RenderNodeInit*)&self->mDbgPS;
    init->InitRenderNode(g_appProperties015fd918, 0x48e2cb7, 1.0f);
    self->mDbgPS.mField14 = 0;
    self->mDbgPS.mField1c = 0;
    self->mDbgPS.mField20 = 0;
    self->mDbgPS.mField24 = 0;
    self->mDbgPS.mField18 = g_zero_13eb1bc;
    self->mDbgPS.mField10 = 0;

    int zero2 = 0;
    self->mScreenInfo.mWidth = zero2;
    self->mScreenInfo.mHeight = zero2;
    self->mScreenInfo.mField08 = zero2;
    self->mScreenInfo.mField0c = zero2;
    self->mScreenInfo.mField10 = zero2;
    self->mScreenInfo.mField14 = zero2;
    self->mScreenInfo.mField18 = zero2;
    self->mScreenInfo.mField1c = zero2;
    self->mScreenInfo.mViewers[0] = zero2;
    self->mScreenInfo.mViewers[1] = zero2;
    self->mScreenInfo.mViewers[2] = zero2;
    self->mScreenInfo.mViewers[3] = zero2;
    self->mFrameViewers[0] = zero2;
    self->mFrameViewers[1] = zero2;
    self->mFrameViewers[2] = zero2;
    self->mFrameViewers[3] = zero2;
    return self;
}

struct cRendererStartView {
    bool Start(int arg1, int arg2, unsigned char arg3, int arg4);   // 0x0075f030
};

// @ 0x0075f030  SP::cRenderer::Start
bool cRendererStartView::Start(int arg1, int arg2, unsigned char arg3, int arg4)
{
    cRendererLayout* self = (cRendererLayout*)this;
    PropListFull* props = g_appProperties015fd918;
    (void)arg4;

    // Renderer tuning properties, kept in two globals.
    if (props->mVtbl->HasProperty(0xc8ba45aa))
        g_renderParam0_015d07c0 = props->GetIntProperty(0xc8ba45aa);
    if (props->mVtbl->HasProperty(0x97541329))
        g_renderParam1_015d07c4 = props->GetIntProperty(0x97541329);
    if (props->mVtbl->HasProperty(0x1d48bf8f))
        g_renderParam0_015d07c0 = props->GetIntProperty(0x1d48bf8f);
    if (props->mVtbl->HasProperty(0x53c20f30))
        g_renderParam1_015d07c4 = props->GetIntProperty(0x53c20f30);

    // Feature flag 0xd77e97 defaults to true; when absent it is written back.
    char feature97 = 1;
    if (props->mVtbl->HasProperty(0xd77e97))
        feature97 = props->GetDescription(0xd77e97) ? 1 : 0;
    else
        props->mVtbl->SetProp(0xd77e97, &feature97);

    int  quality = 0;
    int  mode = 0;
    int  extra = 0;
    char flag9a = 0, flag9b = 0, flag9c = 0, flag9d = 0, flag9e = 0;
    if (props->mVtbl->HasProperty(0xd77e99)) {
        quality = props->GetIntProperty(0xd77e98);
        mode    = props->GetIntProperty(0xd77e99);
        flag9a  = props->GetDescription(0xd77e9a) ? 0 : 1;
        flag9b  = props->GetDescription(0xd77e9b) ? 1 : 0;
        flag9c  = props->GetDescription(0xd77e9c) ? 1 : 0;
        flag9d  = props->GetDescription(0xd77e9d) ? 1 : 0;
        flag9e  = props->GetDescription(0xd77e9e) ? 1 : 0;
        extra   = props->GetIntProperty(0x5c97448);
    }
    (void)mode;

    // Bring up the rw::graphics::Device.
    void* canvas = Canvas();
    FUN_011f8110(*(void**)(*(int*)canvas + 0x94));
    DeviceGetDefaultParameters(2);

    DeviceParams params;
    params.mField00 = quality;
    params.mField04 = (flag9a == 0 ? 1 : 0) + 1;
    params.mField08 = arg1;
    params.mField0c = arg2;
    params.mField10 = 0x3c;
    params.mField14 = 0x16;
    params.mField18 = 0x15;
    params.mField1c = 0x4b;
    params.mField20 = feature97;
    params.mField24 = arg3;
    params.mField28 = flag9b == 0 ? 1 : 0;
    params.mField2c = flag9c == 0 ? 1 : 0;
    params.mField30 = flag9d == 0 ? 1 : 0;
    params.mField34 = flag9e == 0 ? 1 : 0;
    params.mField38 = extra;

    FUN_011f8240((void*)&FUN_0075d930);
    FUN_011f8250((void*)&DeviceRelease);
    FUN_011f8260((void*)&PaintSystemInit);

    void* token = FUN_00689590();
    g_deviceParams = params;
    bool started = DeviceStartInternal(&params) != 0;
    self->mDeviceStarted = started;
    FUN_00689560(token);

    if (!started) {
        DeviceShutdownD3D();
        return false;
    }

    DeviceParams actual = g_deviceParams;
    self->mScreenInfo.mWidth   = actual.mField08;
    self->mScreenInfo.mHeight  = actual.mField0c;
    self->mScreenInfo.mField10 = arg3;
    self->RenderSettings(1);

    float* shaderFlag = &self->mDbgPS.mField18;          // cShaderDataDebugPS value
    self->mDbgPS.RenderStageReady();
    if (*shaderFlag != g_one_01485720) {
        self->mDbgPS.RenderStageReady();
        self->BuildPaletteTable(*shaderFlag);
    }
    return self->InitShaders() != false;
}
