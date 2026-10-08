// Slice s0075ff50 : SP::cRenderer (retail layout) + small render-list helpers.
// Region is /O2 /MD /Gy /EHsc /TP. Callees / globals are masked relocations, so only
// the call shapes and field offsets matter.
#include "types.h"
#include <intrin.h>
#include <new>
#include <stddef.h>
extern "C" void* __cdecl memset(void*, int, size_t);
#pragma function(memset)

extern "C" {
void* __cdecl operator_new(unsigned int size, int align, const char* name);
void  __cdecl operator_delete_(void* p);
}

void __cdecl ResetGlobalState();    // @ 0x7618e0
void* __cdecl SP_Canvas();          // @ 0x67dcf0
void* __cdecl SP_AppSystem();       // @ 0x67dd00
void __cdecl ClearJobList(void* list);
void __cdecl CloseArena();
void __cdecl DevStop1();
void __cdecl DevStop2();
void __cdecl DevStop3();
void __cdecl timeEndPeriod_(int);
float __cdecl StopwatchElapsed(void* stopwatch);
unsigned int __cdecl ReadCounter(void* out);

namespace EA { namespace Thread {
struct Mutex {
    void Lock(const char* name);   // @ 0x9221b0
    void Lock(const unsigned int* pTimeout);   // @ 0x9221b0 (EA::Thread::Mutex::Lock(const ThreadTime*))
    void Unlock();                 // @ 0x922270
};
}}

namespace SP {

// ---------------------------------------------------------------- shared types
struct cILayer {                       // reference-counted interface
    virtual void AddRef();             // +0x0
    virtual void Release();            // +0x4
};

struct cLayerInfo {                    // size 0x14
    cILayer*     mLayer;               // +0x0
    unsigned int mLayerNumber;         // +0x4
    unsigned int mLayerFlags;          // +0x8
    unsigned int mInfoFlags;           // +0xc
    float        mTimeMS;              // +0x10
    void operator=(const cLayerInfo& o);   // @ 0x75ed50
    cLayerInfo(const cLayerInfo& o);       // @ 0x75ee90
    cLayerInfo() {}
};

struct LayerVector {                   // `this` points at mpBegin
    cLayerInfo* mpBegin;               // +0x0
    cLayerInfo* mpEnd;                 // +0x4
    cLayerInfo* mpCapacity;            // +0x8
    void erase(cLayerInfo* first, cLayerInfo* last);                  // @ 0x75fc00
    void DoInsertValue(cLayerInfo* position, const cLayerInfo& value);// @ 0x75fc70
    void DoAssignFromIterator(cLayerInfo* first, cLayerInfo* last, unsigned int tag); // @ 0x75fe50
    cLayerInfo* insert(cLayerInfo* position, const cLayerInfo& value);// @ 0x760030
};

void __cdecl copy_layers(cLayerInfo* first, cLayerInfo* last, cLayerInfo* dest); // @ 0x75f4a0

struct MutexLock {
    EA::Thread::Mutex* mMutex;
    MutexLock(EA::Thread::Mutex* m) : mMutex(m) { mMutex->Lock("Renderer"); }
    ~MutexLock() { mMutex->Unlock(); }
};

struct cRenderJob;
struct cRenderStats;

class cRenderer {
public:
    char mData[0x660];

    bool ClearLayer(unsigned int layerNumber);             // @ 0x75ff50
    bool Shutdown();                                       // @ 0x7600d0
    void SetLayer(cILayer* layer, unsigned int layerNumber, unsigned int flags); // @ 0x7602a0
    void ClearAllLayers();                                  // @ 0x7603e0
    void Render(unsigned int flags);                        // @ 0x760450
    void ExecuteJob(cRenderJob* job, cRenderStats* stats);  // @ 0x75e3f0
};

// @ 0x760030
cLayerInfo* LayerVector::insert(cLayerInfo* position, const cLayerInfo& value)
{
    int idx = (int)(position - mpBegin);
    if (position == mpEnd && mpEnd != mpCapacity) {
        mpEnd = mpEnd + 1;
        if (position)
            new (position) cLayerInfo(value);
    } else {
        DoInsertValue(position, value);
    }
    return mpBegin + idx;
}

// --------------------------------------------------------------------- 0x760ac0
struct AcInner {
    void AcMethod(int v);              // thiscall, @ 0x7c3c50
};

void __stdcall sub_760ac0(void* a, void* b, AcInner** c, void* d)
{
    (*c)->AcMethod(7);
}

// --------------------------------------------------------------- render list 0x760ad0
struct IJob {
    virtual void j0();
    virtual void j1();
    virtual void j2();
    virtual void Run(void* p2, void* p1, void* a2, void* a3);
};
struct JobEntry { IJob* p0; void* p1; void* p2; };
struct JobList {
    char pad[0xc];
    JobEntry* mpBegin;                 // +0xc
    JobEntry* mpEnd;                   // +0x10
    void Dispatch(void* a0, void* a1, void* a2, void* a3);   // @ 0x760ad0
};

void JobList::Dispatch(void* a0, void* a1, void* a2, void* a3)
{
    JobEntry* it = mpBegin;
    if (it != mpEnd) {
        do {
            it->p0->Run(it->p2, it->p1, a2, a3);
            it++;
        } while (it != mpEnd);
    }
}

// ------------------------------------------------------------- ref triple (0x760b50)
struct RefObj {
    virtual void AddRef();             // +0x0
    virtual void Release();            // +0x4
};
struct RefTriple {
    RefObj* p;                         // +0x0
    int     a;                         // +0x4
    int     b;                         // +0x8
    RefTriple* operator=(const RefTriple& o);   // @ 0x760b50
};

RefTriple* RefTriple::operator=(const RefTriple& o)
{
    RefObj* old = p;
    RefObj* src = o.p;
    if (src != old) {
        if (src) src->AddRef();
        p = src;
        if (old) old->Release();
    }
    a = o.a;
    b = o.b;
    return this;
}

// @ 0x760ba0
RefTriple* copy_triples(RefTriple* first, RefTriple* last, RefTriple* dest)
{
    for (; first != last; first++, dest++) {
        RefObj* s = first->p;
        RefObj* d = dest->p;
        if (s != d) {
            if (s) s->AddRef();
            dest->p = s;
            if (d) d->Release();
        }
        dest->a = first->a;
        dest->b = first->b;
    }
    return dest;
}

// --------------------------------------------------------------- 0x760c00 (ctor)
struct Base2 {
    virtual void b0();
    int x, y, z, w;
    Base2() : x(0), y(0), z(0), w(0) {}
};
struct Base1 {
    virtual void a0();
};
struct Poly2 : Base1, Base2 {
    Poly2();
};
Poly2::Poly2() {}

// ---------------------------------------------------------------- 0x760c40 (erase)
struct RefCountedAt8 {
    virtual void r0();
    int r1;
    int mRefCount;                     // +0x8
    void AddRef();
    void Release();
};
struct Elem3 {
    RefCountedAt8* p;                  // +0x0
    void* a;                           // +0x4
    void* b;                           // +0x8
};
void __cdecl move_elems(Elem3* dest, Elem3* last, Elem3* src);    // @ 0x6f43e0
Elem3* __cdecl move_elems2(Elem3* dest, Elem3* last, Elem3* src);  // @ 0x77fb10
void __cdecl destroy_range(Elem3* first, Elem3* last);            // @ 0x760b10
void __cdecl uninit_move(Elem3* first, Elem3* last, Elem3* dest); // @ 0x780a50
void __cdecl move_ptrs(RefCountedAt8** dest, RefCountedAt8** last, RefCountedAt8** src); // @ 0x6f43e0

struct PtrVec {
    RefCountedAt8** mpBegin;           // +0x0
    RefCountedAt8** mpEnd;             // +0x4
    RefCountedAt8** mpCapacity;        // +0x8
    RefCountedAt8** erase(RefCountedAt8** position);   // @ 0x760c40
};

struct Vec3 {
    Elem3* mpBegin;                    // +0x0
    Elem3* mpEnd;                      // +0x4
    Elem3* mpCapacity;                 // +0x8
    Elem3* insert(Elem3* position, const Elem3& value); // @ 0x760ca0
};

RefCountedAt8** PtrVec::erase(RefCountedAt8** position)
{
    if (position + 1 < mpEnd)
        move_ptrs(position + 1, mpEnd, position);
    mpEnd = mpEnd - 1;
    RefCountedAt8* p = *mpEnd;
    if (p) {
        volatile long* rc = (volatile long*)((char*)p + 8);
        _InterlockedExchangeAdd(rc, -1);
        if (_InterlockedExchangeAdd(rc, 0) < 1) {
            _InterlockedExchangeAdd(rc, 1);
            return position;
        }
    }
    return position;
}

Elem3* Vec3::insert(Elem3* position, const Elem3& value)
{
    if (mpEnd != mpCapacity) {
        Elem3* end = mpEnd;
        if (position < end) {
            Elem3* p = end;
            while (p != position) {
                Elem3* prev = p - 1;
                p->p = prev->p;
                if (p->p) p->p->AddRef();
                p->a = prev->a;
                p->b = prev->b;
                p = prev;
            }
        }
        *position = value;
        if (position->p) position->p->AddRef();
        mpEnd = end + 1;
        return position;
    }
    int count = (int)(mpEnd - mpBegin);
    int cap = (count == 0) ? 1 : count * 2;
    Elem3* newBuf = cap ? (Elem3*)operator_new(cap * 0xc, 0, "Graphics") : 0;
    Elem3* newPos = move_elems2(newBuf, position, 0);
    destroy_range(newBuf, position);
    if (newPos) { *newPos = value; if (newPos->p) newPos->p->AddRef(); }
    Elem3* newEnd = move_elems2(position, mpEnd, newPos + 1);
    destroy_range(position, mpEnd);
    if (mpBegin && *(int*)((char*)mpBegin - 4) != 0) operator_delete_(mpBegin);
    mpEnd = newEnd;
    mpBegin = newBuf;
    mpCapacity = newBuf + cap;
    return newPos;
}

// ============================================================== cRenderer methods
// @ 0x75ff50
bool cRenderer::ClearLayer(unsigned int layerNumber)
{
    char* self = (char*)this;
    EA::Thread::Mutex* m = (EA::Thread::Mutex*)(self + 0x28);
    MutexLock lock(m);
    LayerVector* v = (LayerVector*)(self + 0x8c);
    cLayerInfo* it = v->mpBegin;
    cLayerInfo* last = v->mpEnd;
    unsigned int n = layerNumber;
    while (it != last) {
        if (n <= it->mLayerNumber) break;
        it = (cLayerInfo*)((char*)it + 0x14);
    }
    if (it != last && n == it->mLayerNumber) {
        if ((char*)(it + 1) < (char*)v->mpEnd)
            copy_layers(it + 1, v->mpEnd, it);
        v->mpEnd = (cLayerInfo*)((char*)v->mpEnd - 0x14);
        cLayerInfo* e = v->mpEnd;
        if (e->mLayer) e->mLayer->Release();
        return true;
    }
    return false;
}

// @ 0x7600d0
bool cRenderer::Shutdown()
{
    char* self = (char*)this;
    if (!*(char*)(self + 0xc)) return false;
    EA::Thread::Mutex* m = (EA::Thread::Mutex*)(self + 0x28);
    *(char*)(self + 0xc) = 0;
    MutexLock lock(m);
    *(int*)(self + 0x7c) = 0;
    *(int*)(self + 0x80) = 0;
    *(int*)(self + 0x84) = 0;
    *(int*)(self + 0x88) = 0;
    LayerVector* v = (LayerVector*)(self + 0x8c);
    v->erase(v->mpBegin, v->mpEnd);
    *(int*)(self + 0x33c) = 0;
    *(int*)(self + 0x340) = 0;
    *(int*)(self + 0x344) = 0;
    *(int*)(self + 0x348) = 0;
    LayerVector* v2 = (LayerVector*)(self + 0x34c);
    v2->erase(v2->mpBegin, v2->mpEnd);
    ClearJobList(self + 0x330);
    ClearJobList(self + 0x324);
    if (*(char*)(self + 0xd)) {
        DevStop1();
        if (*(char*)(self + 0xd)) {
            DevStop2();
            *(char*)(self + 0xd) = 0;
            DevStop3();
        }
    }
    if (*(int*)(self + 0x20)) {
        CloseArena();
        *(int*)(self + 0x20) = 0;
    }
    *(int*)(self + 0x58) = 0;
    timeEndPeriod_(1);
    return true;
}

// @ 0x7602a0
void cRenderer::SetLayer(cILayer* layer, unsigned int layerNumber, unsigned int flags)
{
    char* self = (char*)this;
    EA::Thread::Mutex* m = (EA::Thread::Mutex*)(self + 0x28);
    MutexLock lock(m);
    LayerVector* v = (LayerVector*)(self + 0x8c);
    cLayerInfo* it = v->mpBegin;
    cLayerInfo* last = v->mpEnd;
    cLayerInfo* found = 0;
    while (it != last) {
        if (layerNumber <= it->mLayerNumber) break;
        it = (cLayerInfo*)((char*)it + 0x14);
    }
    if (it != last && layerNumber == it->mLayerNumber)
        found = it;
    cLayerInfo info;
    info.mLayer = layer;
    if (layer) layer->AddRef();
    info.mLayerNumber = layerNumber;
    info.mLayerFlags = flags;
    info.mInfoFlags = 1;
    info.mTimeMS = 0.0f;
    if (found)
        found->operator=(info);
    else
        v->insert(it, info);
    if (info.mLayer) info.mLayer->Release();
}

// @ 0x7603e0
void cRenderer::ClearAllLayers()
{
    char* self = (char*)this;
    EA::Thread::Mutex* m = (EA::Thread::Mutex*)(self + 0x28);
    MutexLock lock(m);
    LayerVector* v = (LayerVector*)(self + 0x8c);
    v->erase(v->mpBegin, v->mpEnd);
}

// ======================================================================= 0x760450
// SP::cRenderer::Render(flags): one frame. Under the "Renderer" mutex it takes the pending pre/post
// render-job lists (swapped into locals) and snapshots viewers + layers, then runs the pre jobs, every
// layer of the snapshot and the post jobs (each job group limited to a time budget), updates the frame
// timing / render stats, hands the leftover jobs back and clears the layer snapshot.
void __cdecl EA_Free(void* p) throw();                    // @ 0xf47380
void __cdecl ShaderDataSet(unsigned short id, void* v, char force);   // @ 0x777ae0
struct Raster;
void __cdecl ShowRaster(Raster* r);                       // @ 0x11f8120 (rw::graphics::Device::ShowRaster)
void __cdecl RestoreVertexShader();                       // @ 0x11f81d0
extern Raster* g_defaultCameraRaster;                     // @ 0x15d0838
extern unsigned g_renderThreadId;                         // @ 0x1600778
extern char g_shaderActiveState[0x40];                    // @ 0x16f65a8
extern char g_shaderDirtyBits[0x57];                      // @ 0x16f67a8
extern char g_shaderStack[0x40];                          // @ 0x16f68a8
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64*);   // @ 0x13cc2b8

// one frame's render stats (11 dwords, copied to cRenderer+0x608)
struct cRenderStats {
    float mLastFrameMS, mLastFPS, mSmoothedMS, mSmoothedFPS, mReserved;
    int   mLayersRendered, mN6, mJobCount, mN8, mN9, mN10;
    cRenderStats()
        : mLastFrameMS(0.0f), mLastFPS(0.0f), mSmoothedMS(0.0f), mSmoothedFPS(0.0f), mReserved(0.0f),
          mLayersRendered(0), mN6(0), mJobCount(0), mN8(0), mN9(0), mN10(0) {}
};

// a layer as the renderer sees it: Release() at slot 1, Render at slot 3
struct cIRenderLayer {
    virtual void AddRef();
    virtual void Release();
    virtual void s2();
    virtual void Render(unsigned int flags, unsigned int layerNumber, void* viewers, cRenderStats* stats);
};

struct cRenderJob {                    // size 0x38 (eastl::list node value)
    cIRenderLayer* mLayer;             // +0x0 (AutoRefCount)
    int            mPriority;          // +0x4
    unsigned int   mID;                // +0x8
    int            mCost;              // +0xc
    unsigned int   pad10[(0x38 - 0x10) / 4];
};

struct RenderJobNode {                 // eastl::list node
    RenderJobNode* mpNext;
    RenderJobNode* mpPrev;
    cRenderJob     mValue;             // +0x8
};

// eastl::list<cRenderJob>: anchor node only (next/prev); size() walks the list
struct RenderJobList {
    RenderJobNode* mpNext;
    RenderJobNode* mpPrev;
    RenderJobList() { mpNext = 0; mpPrev = 0; mpNext = (RenderJobNode*)this; mpPrev = (RenderJobNode*)this; }
    ~RenderJobList() { clear(); }
    void clear()
    {
        RenderJobNode* pNode = mpNext;
        while (pNode != (RenderJobNode*)this) {
            RenderJobNode* pTemp = pNode;
            pNode = pNode->mpNext;
            cIRenderLayer* layer = pTemp->mValue.mLayer;
            if (layer) layer->Release();
            EA_Free(pTemp);
        }
    }
    int size() const
    {
        int n = 0;
        for (const RenderJobNode* p = mpNext; p != (const RenderJobNode*)this; p = p->mpNext) ++n;
        return n;
    }
    void pop_front()
    {
        RenderJobNode* pNode = mpNext;
        pNode->mpPrev->mpNext = pNode->mpNext;
        pNode->mpNext->mpPrev = pNode->mpPrev;
        cIRenderLayer* layer = pNode->mValue.mLayer;
        if (layer) layer->Release();
        EA_Free(pNode);
    }
    // eastl::list::splice(position, x): move all of x in front of position
    void splice(RenderJobNode* position, RenderJobList& x)
    {
        if ((RenderJobNode*)&x != x.mpNext) {
            RenderJobNode* first = x.mpNext;
            RenderJobNode* last = (RenderJobNode*)&x;
            last->mpPrev->mpNext = position;
            first->mpPrev->mpNext = last;
            position->mpPrev->mpNext = first;
            RenderJobNode* pTemp = position->mpPrev;
            position->mpPrev = last->mpPrev;
            last->mpPrev = first->mpPrev;
            first->mpPrev = pTemp;
        }
    }
};
void __cdecl SwapRenderJobLists(RenderJobList* a, RenderJobList* b);   // @ 0x75d8d0 (intrusive list swap)

struct cStopwatch {                    // at cRenderer+0x5e8
    unsigned int mStartLo, mStartHi;   // +0x0 start tick
    unsigned int mStopLo, mStopHi;     // +0x8
    int          mMode;                // +0x10 (1 = rdtsc, otherwise QueryPerformanceCounter)
    float        mMsPerTick;           // +0x14
    __int64 GetElapsedTicks();         // @ 0x93a3a0
    void Start()
    {
        if (mMode == 1) {
            unsigned __int64 t = __rdtsc();
            mStartLo = (unsigned int)t; mStartHi = (unsigned int)(t >> 32);
        } else {
            __int64 t;
            QueryPerformanceCounter(&t);
            mStartLo = (unsigned int)t; mStartHi = (unsigned int)((unsigned __int64)t >> 32);
        }
        mStopLo = 0; mStopHi = 0;
    }
};

extern const unsigned int kTimeoutNone;                 // @ 0x140dca0 (EA::Thread::kTimeoutNone, 0xffffffff)
struct RenderLock {
    EA::Thread::Mutex* mMutex;
    RenderLock(EA::Thread::Mutex* m) : mMutex(m) { mMutex->Lock(&kTimeoutNone); }
    ~RenderLock() { mMutex->Unlock(); }
};

template <class T> inline T& Fld(void* self, int off) { return *(T*)((char*)self + off); }

// per-pass shader-state reset (three times per frame)
__forceinline void ResetRenderPassState(void* dbgData)
{
    ResetGlobalState();
    memset(g_shaderActiveState, 0, 0x40);
    memset(g_shaderDirtyBits, 0, 0x57);
    memset(g_shaderStack, 0, 0x40);
    ShaderDataSet(0x24e, dbgData, 0);
}

// @ 0x760450 : SP::cRenderer::Render
void cRenderer::Render(unsigned int flags)
{
    char* self = (char*)this;
    if (Fld<char>(self, 0x6c) && SP_Canvas()) {
        void* c = SP_Canvas();
        if (!(*(bool(__thiscall**)(void*))(*(char**)c + 0x44))(c))
            return;
    }
    RenderJobList preJobs;                       // swapped in from +0x330
    RenderJobList postJobs;                      // swapped in from +0x324
    EA::Thread::Mutex* m = (EA::Thread::Mutex*)(self + 0x28);
    int budget;
    {
        RenderLock lock(m);
        if (!Fld<int>(self, 0x7c))
            return;
        Fld<int>(self, 0x33c) = Fld<int>(self, 0x7c);
        Fld<int>(self, 0x340) = Fld<int>(self, 0x80);
        Fld<int>(self, 0x344) = Fld<int>(self, 0x84);
        Fld<int>(self, 0x348) = Fld<int>(self, 0x88);
        LayerVector* layers = (LayerVector*)(self + 0x8c);
        LayerVector* frameLayers = (LayerVector*)(self + 0x34c);
        if (frameLayers != layers) {
            frameLayers->erase(frameLayers->mpBegin, frameLayers->mpEnd);
            frameLayers->DoAssignFromIterator(layers->mpBegin, layers->mpEnd, flags);
        }
        SwapRenderJobLists(&preJobs, (RenderJobList*)(self + 0x330));
        SwapRenderJobLists(&postJobs, (RenderJobList*)(self + 0x324));
        budget = Fld<int>(self, 0x10);
    }
    {
        void* app = SP_AppSystem();
        if ((*(bool(__thiscall**)(void*))(*(char**)app + 0x44))(app)) {
            int def = Fld<int>(self, 0x14) * 3;
            if (budget < def)
                budget = def;
        }
    }
    bool onRenderThread = (g_renderThreadId == __readfsdword(0x18));
    cRenderStats stats;
    stats.mJobCount = postJobs.size() + preJobs.size();
    if (Fld<char>(self, 0x1b)) {
        RestoreVertexShader();
        Fld<char>(self, 0x1b) = 0;
    }
    ShowRaster(g_defaultCameraRaster);
    if ((*(bool(__thiscall**)(void*))(*(char**)self + 0x88))(self)) {
        ResetRenderPassState(self + 0x648);
        int done = 0;
        while (preJobs.mpNext != (RenderJobNode*)&preJobs && done < budget) {
            cRenderJob* job = &preJobs.mpNext->mValue;
            ExecuteJob(job, &stats);
            done += job->mCost;
            preJobs.pop_front();
        }
        ResetRenderPassState(self + 0x648);
        unsigned int mask = 0x10001, want = 1;
        if (!onRenderThread) {
            mask = 0x10005;
            want = 5;
        }
        LayerVector* frameLayers = (LayerVector*)(self + 0x34c);
        cLayerInfo* sel = frameLayers->mpBegin;
        for (cLayerInfo* p = frameLayers->mpBegin; p != frameLayers->mpEnd; ++p)
            if (p->mInfoFlags & 2) sel = p;
        if (sel != frameLayers->mpEnd) {
            cLayerInfo* p = sel;
            do {
                if ((p->mInfoFlags & mask) == want) {
                    unsigned int id = p->mLayerNumber;
                    Fld<unsigned int>(self, 0x654) = id;
                    ResetGlobalState();
                    ((cIRenderLayer*)p->mLayer)->Render(p->mLayerFlags | flags, id, self + 0x33c, &stats);
                    ++stats.mLayersRendered;
                }
                p->mInfoFlags &= 0xfffeffff;
                ++p;
            } while (p != frameLayers->mpEnd);
        }
        ResetRenderPassState(self + 0x648);
        done = 0;
        while (postJobs.mpNext != (RenderJobNode*)&postJobs && done < budget) {
            cRenderJob* job = &postJobs.mpNext->mValue;
            ExecuteJob(job, &stats);
            done += job->mCost;
            postJobs.pop_front();
        }
        Fld<char>(self, 0x18) = 0;
        (*(void(__thiscall**)(void*))(*(char**)self + 0x8c))(self);
    }
    cStopwatch* sw = (cStopwatch*)(self + 0x5e8);
    float ms = (float)sw->GetElapsedTicks() * sw->mMsPerTick;
    Fld<float>(self, 0x600) = ms;
    Fld<float>(self, 0x604) = Fld<float>(self, 0x604) * 0.9f + ms * 0.1f;
    sw->Start();
    stats.mLastFrameMS = Fld<float>(self, 0x600);
    stats.mSmoothedMS = Fld<float>(self, 0x604);
    stats.mLastFPS = 1000.0f / stats.mLastFrameMS;
    stats.mSmoothedFPS = 1000.0f / stats.mSmoothedMS;
    m->Lock(&kTimeoutNone);
    RenderJobNode* preHead = Fld<RenderJobNode*>(self, 0x330);
    Fld<cRenderStats>(self, 0x608) = stats;
    ((RenderJobList*)(self + 0x330))->splice(preHead, preJobs);
    ((RenderJobList*)(self + 0x324))->splice(Fld<RenderJobNode*>(self, 0x324), postJobs);
    Fld<int>(self, 0x10) = Fld<int>(self, 0x14);
    m->Unlock();
    LayerVector* fl = (LayerVector*)(self + 0x34c);
    fl->erase(fl->mpBegin, fl->mpEnd);
}

} // namespace SP
