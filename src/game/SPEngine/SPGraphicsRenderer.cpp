// src/game/SPEngine/SPGraphicsRenderer.cpp -- migrated from slice(s) s0075ff50, s0075ee90, s0075de80, s0075cf20 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsRenderer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cRenderer.h"
#include "EA/Thread/Mutex.h"
#include "SP/cILayer.h"
#include "SP/cLayerInfo.h"
#include "SP/cRenderStats.h"
#include "EA/Stopwatch.h"
#include <intrin.h>
#include <new>
#include <stddef.h>

// unnamed retail callees and globals (address in the comment)
extern int* g_deviceGlobal;   // @ 0x0162f9c8
extern int* g_paintDevice;   // @ 0x016f89d0
extern "C" __declspec(dllimport) void* __stdcall CreateDCA(const char*, const char*, const char*, void*);
extern "C" __declspec(dllimport) int __stdcall GetDeviceCaps(void*, int);
extern "C" __declspec(dllimport) int __stdcall DeleteDC(void*);
extern int* g_d3d9DeviceB;   // @ 0x016f89c8
extern "C" void __cdecl D3D9AdapterInfo_GetAdapterString(int);   // @ 0x011f8310
extern int GetDeviceReady();   // @ 0x011f8160
extern int* g_d3d9DeviceC;   // @ 0x016f89d0
extern "C" float CIpow_stub(float, float);   // @ 0x011e08f0
extern "C" int FUN_006a17e0(int, int);           // @ 0x006a17e0
extern "C" int FUN_011fd770();                   // @ 0x011fd770
extern int* g_d3d9State;   // @ 0x016f89c8
extern int* g_devCaps;     // @ 0x016fa39c
extern int g_devCapsDword; // @ 0x016f9448

// ---- items of slice s0075cf20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl EAThreadSleep(unsigned int* t);   // @ 0x00921df0
extern int  GetAdapterCount();                               // @ 0x011f8300
extern void GetFormats(unsigned int* out, int count);        // @ 0x011f8a40
void* SP_MessageServer();   // @ 0x0067dcc0
struct MONITORINFO { unsigned int cbSize; long rc[4]; long rcWork[4]; unsigned int dwFlags; };
extern "C" __declspec(dllimport) int __stdcall GetMonitorInfoA(void*, MONITORINFO*);  // @ user32
namespace EA {
namespace Thread {
 struct Mutex_s0075_cf20 {
     void Lock(const void*);  // 0x009221b0 (EA::Thread::Mutex::Lock)
     void Unlock();  // 0x00922270 (EA::Thread::Mutex::Unlock)
     char pad[0x28];
 };
}
}
struct cRenderer {
    char pad00[0x10];       // +0x00
    int  mRenderJobBudget;  // +0x10
    char pad14[0x14];       // +0x14
    EA::Thread::Mutex_s0075_cf20 mMutex; // +0x28
    char pad50[0x2c];       // +0x50
    void* mViewers[8];      // +0x7c
    char pad9c[0x56c];      // +0x9c
    int mStats[0xb];        // +0x608

    void SetViewer(int idx, void* viewer);   // @ 0x0075daa0
    void* GetRenderStats(int idx);           // @ 0x0075dad0
    void NumLayers(int* out);                // @ 0x0075db70
    void LayerAtIndex(int v);                // @ 0x0075dbb0
};
struct DevLatch {
    bool CheckDeviceReady();
    void MaybeReleaseDevice();
};
struct D3DCAPS9;
extern D3DCAPS9* DevCapsManager_GetD3DCAPS9();   // @ 0x011f8af0
struct SPAllocPool {
    void* LockedAligned(unsigned int size, int a, int b, int c,
                        int d, int e, int f, int g);         // @ 0x00928a30 (ret 0x20)
    void Free(void* elem);                                   // @ 0x009276c0 (ret 4)
};
extern SPAllocPool* g_pAllocPool;                            // @ 0x016c8b44
struct AdapterSet { void* p; unsigned int a, b, c; };
extern void* GetAdapterInfo(AdapterSet* set, int count);     // @ 0x011f88c0
struct LightFormat { unsigned int a, b; ~LightFormat() {} }; // empty dtor (0x00c2e4e0)
extern void ReleaseDevice();   // @ 0x011f81d0
// ---- items of slice s0075cf20 end

// unnamed retail callees and globals that name local stubs (address in the comment)

// ---- items of slice s0075de80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int* g_sAppProperties;   // @ 0x015fd918
extern float* Property_GetFloat();   // @ 0x0041ea70
extern bool  Property_GetBool();     // @ 0x0041e920
extern float ScreenAspectRatio(int); // @ 0x0075d9e0
namespace EA {
namespace Thread {
struct Mutex_s0075_de80 {
    void Lock(const void*);  // 0x009221b0 (EA::Thread::Mutex::Lock)
    void Unlock();  // 0x00922270 (EA::Thread::Mutex::Unlock)
    char pad[0x28];
};
}
}
struct RenderLayerArray_s0075_de80 {
    char* mpBegin;                 // +0
    char* mpEnd;                   // +4
};

struct cRenderer_s0075_de80 {
    char pad00[0x28];              // +0x00
    EA::Thread::Mutex_s0075_de80 mMutex;      // +0x28
    char pad50[0x3c];              // +0x50
    char pad8c[0x33c - 0x8c];      // +0x8c
    char mExtra[0x34c - 0x33c];    // +0x33c
    RenderLayerArray_s0075_de80 mLayers; // +0x34c
    // layers: begin pointer at +0x8c, end pointer at +0x90 (stride 0x14)
    int NumLayers();               // @ 0x0075e330
    void* LayerInfoAt(int idx);    // @ 0x0075e370
    void* LayerInfoAtIndex(int i); // @ 0x0075e3b0
    void* Layer(unsigned id);      // @ 0x0075e090
    unsigned SetInfoFlags(unsigned id, unsigned f);   // @ 0x0075e130
    unsigned ClearInfoFlags(unsigned id, unsigned f); // @ 0x0075e1e0
    unsigned GetInfoFlags(unsigned id);               // @ 0x0075e290
    void RenderSettings(char useProps); // @ 0x0075de80
    void ResizeFromCanvas();            // @ 0x0075df60
    void SubRender(int a, int lo, int hi, void* extra, char flag, unsigned orbits); // @ 0x0075dff0
};
static inline char* LayerBegin(cRenderer_s0075_de80* r) { return *(char**)((char*)r + 0x8c); }
static inline char* LayerEnd(cRenderer_s0075_de80* r)   { return *(char**)((char*)r + 0x90); }
extern void Canvas_GetRect(int*, int*);   // @ 0x008d2f30
extern int* SP_Canvas();                  // @ 0x0067dcf0
extern int g_screenW;   // @ 0x0171244c
extern int g_screenH;   // @ 0x01712450
// ---- items of slice s0075de80 end

// ---- items of slice s0075ee90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EASTL_allocator_allocate(unsigned n, const char* name, int a, int b,
                                           const char* file, int line);   // @ 0x00f473a0
extern "C" void EASTL_deallocate(void* p);   // @ 0x00f47380
extern void ConstructElemArray(void* a, void* b, void* c, void* d, unsigned n); // @ 0x0075ef80
struct RNode {
    virtual void AddRef();    // vtable slot 0
    virtual void Release();   // vtable slot 1
};
struct Elem {          // 0x14 bytes
    RNode* p;          // +0x00
    int    b;          // +0x04
    int    c;          // +0x08
    int    d;          // +0x0c
    float  f;          // +0x10
    Elem* Copy(Elem* src);
};
struct cRenderer_s0075_ee90 {
    char pad[0x324];
    bool RemovePostRenderJob(unsigned int id);  // 0x0075f8a0 (cRenderer::RemovePostRenderJob)
    bool RemovePreRenderJob(unsigned int id);  // 0x0075f900 (cRenderer::RemovePreRenderJob)
};
struct RenderJob {
    RenderJob* next;   // +0x00
    RenderJob* prev;   // +0x04
    RNode*     obj;    // +0x08
    int        pad;    // +0x0c
    unsigned int id;   // +0x10 (render-job id from sRenderJobId, compared as an integer)
};
// ---- items of slice s0075ee90 end

// ---- items of slice s0075ff50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memset(void*, int, size_t);
extern "C" void* __cdecl operator_new(unsigned int size, int align, const char* name);
extern "C" void  __cdecl operator_delete_(void* p);
#pragma function(memset)
void __cdecl ResetGlobalState();    // @ 0x7618e0
void* __cdecl SP_Canvas_s0075_ff50();          // @ 0x67dcf0
void* __cdecl SP_AppSystem();       // @ 0x67dd00
void __cdecl ClearJobList(void* list);
void __cdecl CloseArena();
void __cdecl DevStop1();
void __cdecl DevStop2();
void __cdecl DevStop3();
void __cdecl timeEndPeriod_(int);
namespace EA {
namespace Thread {
struct Mutex_s0075_ff50 {
    void Lock(const char* name);   // @ 0x9221b0
    void Lock(const unsigned int* pTimeout);   // @ 0x9221b0 (EA::Thread::Mutex::Lock(const ThreadTime*))
    void Unlock();                 // @ 0x922270
};
}
}
namespace SP {
struct cILayer_s0075_ff50 {                       // reference-counted interface
    virtual void AddRef();             // +0x0
    virtual void Release();            // +0x4
};
}
namespace SP {
struct cLayerInfo_s0075_ff50 {                    // size 0x14
    cILayer_s0075_ff50*     mLayer;               // +0x0
    unsigned int mLayerNumber;         // +0x4
    unsigned int mLayerFlags;          // +0x8
    unsigned int mInfoFlags;           // +0xc
    float        mTimeMS;              // +0x10
    void operator=(const cLayerInfo_s0075_ff50& o);   // @ 0x75ed50
    cLayerInfo_s0075_ff50(const cLayerInfo_s0075_ff50& o);       // @ 0x75ee90
    cLayerInfo_s0075_ff50() {}
};
}
namespace SP {
struct LayerVector {                   // `this` points at mpBegin
    cLayerInfo_s0075_ff50* mpBegin;               // +0x0
    cLayerInfo_s0075_ff50* mpEnd;                 // +0x4
    cLayerInfo_s0075_ff50* mpCapacity;            // +0x8
    void erase(cLayerInfo_s0075_ff50* first, cLayerInfo_s0075_ff50* last);                  // @ 0x75fc00
    void DoInsertValue(cLayerInfo_s0075_ff50* position, const cLayerInfo_s0075_ff50& value);// @ 0x75fc70
    void DoAssignFromIterator(cLayerInfo_s0075_ff50* first, cLayerInfo_s0075_ff50* last, unsigned int tag); // @ 0x75fe50
    cLayerInfo_s0075_ff50* insert(cLayerInfo_s0075_ff50* position, const cLayerInfo_s0075_ff50& value);// @ 0x760030
};
}
namespace SP {
void __cdecl copy_layers(cLayerInfo_s0075_ff50* first, cLayerInfo_s0075_ff50* last, cLayerInfo_s0075_ff50* dest); // @ 0x75f4a0
}
namespace SP {
struct MutexLock {
    EA::Thread::Mutex_s0075_ff50* mMutex;
    MutexLock(EA::Thread::Mutex_s0075_ff50* m) : mMutex(m) { mMutex->Lock("Renderer"); }
    ~MutexLock() { mMutex->Unlock(); }
};
}
namespace SP {
struct cRenderJob_s0075_ff50;
}
namespace SP {
struct cRenderStats_s0075_ff50;
}
namespace SP {
class cRenderer_s0075_ff50 {
public:
    char mData[0x660];

    bool ClearLayer(unsigned int layerNumber);             // @ 0x75ff50
    bool Shutdown();                                       // @ 0x7600d0
    void SetLayer(cILayer_s0075_ff50* layer, unsigned int layerNumber, unsigned int flags); // @ 0x7602a0
    void ClearAllLayers();                                  // @ 0x7603e0
    void Render(unsigned int flags);                        // @ 0x760450
    void ExecuteJob(cRenderJob_s0075_ff50* job, cRenderStats_s0075_ff50* stats);  // @ 0x75e3f0
};
}
namespace SP {
struct RefObj {
    virtual void AddRef();             // +0x0
    virtual void Release();            // +0x4
};
}
namespace SP {
struct RefTriple {
    RefObj* p;                         // +0x0
    int     a;                         // +0x4
    int     b;                         // +0x8
    RefTriple* operator=(const RefTriple& o);   // @ 0x760b50
};
}
namespace SP {
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
}
namespace SP {
struct RefCountedAt8 {
    virtual void r0();
    int r1;
    int mRefCount;                     // +0x8
    void AddRef();
    void Release();
};
}
namespace SP {
struct Elem3 {
    RefCountedAt8* p;                  // +0x0
    void* a;                           // +0x4
    void* b;                           // +0x8
};
}
namespace SP {
Elem3* __cdecl move_elems2(Elem3* dest, Elem3* last, Elem3* src);  // @ 0x77fb10
}
namespace SP {
void __cdecl destroy_range(Elem3* first, Elem3* last);            // @ 0x760b10
}
namespace SP {
void __cdecl move_ptrs(RefCountedAt8** dest, RefCountedAt8** last, RefCountedAt8** src); // @ 0x6f43e0
}
namespace SP {
struct PtrVec {
    RefCountedAt8** mpBegin;           // +0x0
    RefCountedAt8** mpEnd;             // +0x4
    RefCountedAt8** mpCapacity;        // +0x8
    RefCountedAt8** erase(RefCountedAt8** position);   // @ 0x760c40
};
}
namespace SP {
struct Vec3 {
    Elem3* mpBegin;                    // +0x0
    Elem3* mpEnd;                      // +0x4
    Elem3* mpCapacity;                 // +0x8
    Elem3* insert(Elem3* position, const Elem3& value); // @ 0x760ca0
};
}
namespace SP {
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
}
namespace SP {
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
}
namespace SP {
void __cdecl EA_Free(void* p) throw();                    // @ 0xf47380
}
namespace SP {
void __cdecl ShaderDataSet(unsigned short id, void* v, char force);   // @ 0x777ae0
}
namespace SP {
struct Raster;
}
namespace SP {
void __cdecl ShowRaster(Raster* r);                       // @ 0x11f8120 (rw::graphics::Device::ShowRaster)
}
namespace SP {
void __cdecl RestoreVertexShader();                       // @ 0x11f81d0
}
namespace SP {
extern Raster* g_defaultCameraRaster;                     // @ 0x15d0838
}
namespace SP {
extern unsigned g_renderThreadId;                         // @ 0x1600778
}
namespace SP {
extern char g_shaderActiveState[0x40];                    // @ 0x16f65a8
}
namespace SP {
extern char g_shaderDirtyBits[0x57];                      // @ 0x16f67a8
}
namespace SP {
extern char g_shaderStack[0x40];                          // @ 0x16f68a8
}
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64*);   // @ 0x13cc2b8
namespace SP {
struct cRenderStats_s0075_ff50 {
    float mLastFrameMS, mLastFPS, mSmoothedMS, mSmoothedFPS, mReserved;
    int   mLayersRendered, mN6, mJobCount, mN8, mN9, mN10;
    cRenderStats_s0075_ff50()
        : mLastFrameMS(0.0f), mLastFPS(0.0f), mSmoothedMS(0.0f), mSmoothedFPS(0.0f), mReserved(0.0f),
          mLayersRendered(0), mN6(0), mJobCount(0), mN8(0), mN9(0), mN10(0) {}
};
}
namespace SP {
struct cIRenderLayer {
    virtual void AddRef();
    virtual void Release();
    virtual void s2();
    virtual void Render(unsigned int flags, unsigned int layerNumber, void* viewers, cRenderStats_s0075_ff50* stats);
};
}
namespace SP {
struct cRenderJob_s0075_ff50 {                    // size 0x38 (eastl::list node value)
    cIRenderLayer* mLayer;             // +0x0 (AutoRefCount)
    int            mPriority;          // +0x4
    unsigned int   mID;                // +0x8
    int            mCost;              // +0xc
    unsigned int   pad10[(0x38 - 0x10) / 4];
};
}
namespace SP {
struct RenderJobNode {                 // eastl::list node
    RenderJobNode* mpNext;
    RenderJobNode* mpPrev;
    cRenderJob_s0075_ff50     mValue;             // +0x8
};
}
namespace SP {
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
}
namespace SP {
void __cdecl SwapRenderJobLists(RenderJobList* a, RenderJobList* b);   // @ 0x75d8d0 (intrusive list swap)
}
namespace SP {
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
}
namespace SP {
extern const unsigned int kTimeoutNone;                 // @ 0x140dca0 (EA::Thread::kTimeoutNone, 0xffffffff)
}
namespace SP {
struct RenderLock {
    EA::Thread::Mutex_s0075_ff50* mMutex;
    RenderLock(EA::Thread::Mutex_s0075_ff50* m) : mMutex(m) { mMutex->Lock(&kTimeoutNone); }
    ~RenderLock() { mMutex->Unlock(); }
};
}
namespace SP {
template <class T> inline T& Fld(void* self, int off) { return *(T*)((char*)self + off); }
}
namespace SP {
__forceinline void ResetRenderPassState(void* dbgData)
{
    ResetGlobalState();
    memset(g_shaderActiveState, 0, 0x40);
    memset(g_shaderDirtyBits, 0, 0x57);
    memset(g_shaderStack, 0, 0x40);
    ShaderDataSet(0x24e, dbgData, 0);
}
}
// ---- items of slice s0075ff50 end

// @ 0x0075d950
void DeviceRelease()
{
    int* g = g_deviceGlobal;
    if (g != 0) {
        ((void (__stdcall*)(void*))*(void**)(*g + 8))(g);
        g_deviceGlobal = 0;
    }
    int* p = (int*)SP_MessageServer();
    ((void (__thiscall*)(void*, int, int, int))*(void**)(*p + 0x14))(p, 0x44edd9b, 0, 0);
}

// @ 0x0075d990
void PaintSystemInit()
{
    int dev = (int)g_paintDevice;
    int vt = *(int*)dev;
    int r = ((int (__thiscall*)(void*, int, int))*(void**)(vt + 0x1d8))((void*)vt, 8, 0);
    if (r >= 0)
        ((int (__thiscall*)(void*, int, void**))*(void**)(vt + 0x1d8))((void*)vt, 8, (void**)&g_deviceGlobal);
    int* p = (int*)SP_MessageServer();
    ((void (__thiscall*)(void*, int, int, int))*(void**)(*p + 0x14))(p, 0x44edd9c, 0, 0);
}

// @ 0x0075d9e0
float ScreenAspectRatio(float param_1)
{
    MONITORINFO mi;
    float result = param_1;
    mi.cbSize = 0;
    int dev = (int)g_d3d9DeviceB;
    int vt = *(int*)dev;
    void* mon = ((void* (__thiscall*)(void*, float))*(void**)(vt + 0x3c))((void*)vt, param_1);
    mi.cbSize = 0x48;
    GetMonitorInfoA(mon, &mi);
    char buf[40];
    void* dc = CreateDCA(buf, buf, 0, 0);
    if (dc != 0) {
        int x = GetDeviceCaps(dc, 4);
        int y = GetDeviceCaps(dc, 6);
        result = (float)x / (float)y;
        DeleteDC(dc);
    }
    return result;
}

// @ 0x0075da90
void __stdcall GetDisplayName(int param_1)
{
    D3D9AdapterInfo_GetAdapterString(param_1);
}

// @ 0x0075daa0
void cRenderer::SetViewer(int idx, void* viewer)
{
    mMutex.Lock((const void*)0x140dca0);
    mViewers[idx] = viewer;
    mMutex.Unlock();
}

// @ 0x0075dad0
void* cRenderer::GetRenderStats(int idx)
{
    mMutex.Lock((const void*)(int*)0x140dca0);
    void* r = mViewers[idx];
    mMutex.Unlock();
    return r;
}

// @ 0x0075db00
void __stdcall RendererFlush(bool noSleep)
{
    int* d = g_deviceGlobal;
    if (d != 0) {
        ((void (__stdcall*)(void*, int))*(void**)(*d + 0x18))(d, 1);
        while (((int (__stdcall*)(void*, int, int, int))*(void**)(*g_deviceGlobal + 0x1c))(g_deviceGlobal, 0, 0, 1) == 1) {
            if (!noSleep) {
                unsigned int t = 0;
                EAThreadSleep(&t);
            }
        }
    }
}

// @ 0x0075db70
void cRenderer::NumLayers(int* out)
{
    cRenderer* self = this;
    self->mMutex.Lock((const void*)0x140dca0);
    for (int i = 0; i != 0xb; i++)
        out[i] = self->mStats[i];
    self->mMutex.Unlock();
}

// @ 0x0075dbb0
void cRenderer::LayerAtIndex(int v)
{
    cRenderer* self = this;
    self->mMutex.Lock((const void*)0x140dca0);
    self->mRenderJobBudget = v;
    self->mMutex.Unlock();
}

// @ 0x0075dbe0
bool DevLatch::CheckDeviceReady()
{
    int param_1 = (int)this;
    bool r = true;
    if (*(char*)(param_1 + 0x1b) == 0) {
        r = GetDeviceReady() != 0;
        if (*(char*)(param_1 + 0x1c) != 0)
            *(char*)(param_1 + 0x1b) = 1;
    }
    return r;
}

// @ 0x0075dc10
void SP::cRenderer::slot_35()
{
    int param_1 = (int)this;
    if (*(char*)(param_1 + 0x1b) == 0)
        ReleaseDevice();
}

// @ 0x0075dc20
void BuildPaletteTable(float param_1)
{
    unsigned short table[3 * 256];
    for (int i = 0; i < 0x100; i++) {
        float v = (float)CIpow_stub((float)i, param_1) * 65535.0f;
        unsigned short u = (unsigned short)(int)v;
        table[i] = u;
        table[256 + i] = u;
        table[512 + i] = u;
    }
    int dev = (int)g_d3d9DeviceC;
    int vt = *(int*)dev;
    ((void (__thiscall*)(void*, int, int, void*))*(void**)(vt + 0x54))((void*)vt, 0, 0, table);
}

// @ 0x0075dca0
bool cRenderer_InitShaders()
{
    int caps = (int)DevCapsManager_GetD3DCAPS9();
    int local = 0;
    if (*(unsigned int*)(caps + 0xc4) < 0xfffe0300u) {
        int dev = (int)g_d3d9State;
        int vt = *(int*)dev;
        int r = ((int (__thiscall*)(void*, int, int, int, int, int, int))*(void**)(vt + 0x28))
                    ((void*)vt, 0, 1, 0x16, 0, 1, 0x54534e49);
        if (r == 0) {
            g_devCaps = (int*)((int)g_devCaps | 0x80000);
            g_devCapsDword = 0x54534e49;
            local = 1;
        }
    } else {
        local = 1;
    }
    if ((*(unsigned char*)(caps + 0xd4) & 1) == 0)
        local = 0;
    FUN_006a17e0(0x668d4fa1, local);
    return FUN_011fd770() != 0;
}

// @ 0x0075dd30
bool MergeLocalLights(int param_1, int param_2, int param_3, int param_4)
{
    int count = GetAdapterCount();
    if (param_1 < 0 || param_1 >= count)
        return false;

    LightFormat info[4];
    GetFormats((unsigned int*)info, count);

    AdapterSet set;
    set.p = g_pAllocPool->LockedAligned(info[0].a, (int)info[0].b, 0, 0, 0, 0, 0, 0);
    set.a = 0;
    set.b = 0;
    set.c = 0;

    char* base = (char*)GetAdapterInfo(&set, count);
    base += param_1 * 0x44;

    bool found = false;
    unsigned int n = *(unsigned int*)(base + 0x10);
    if (n != 0) {
        char* mode = base + 0x14;
        unsigned int c = n;
        do {
            int type = *(int*)mode;
            if (type == 0x15 || type == 0x16 || type == 0x21) {
                unsigned int m = *(unsigned int*)(mode + 4);
                if (m != 0) {
                    int* res = *(int**)(mode + 8);
                    for (unsigned int i = 0; i < m; i++, res += 4) {
                        if (res[0] == param_2 && res[1] == param_3 && res[2] == param_4) {
                            found = true;
                            break;
                        }
                    }
                }
            }
            mode += 0xc;
        } while (--c);
    }

    g_pAllocPool->Free(set.p);
    return found;
}

// @ 0x0075de80
void cRenderer_s0075_de80::RenderSettings(char useProps)
{
    cRenderer_s0075_de80* self = this;
    int* props = g_sAppProperties;
    if (useProps) {
        if (props != 0) {
            void* prop;
            bool ok = ((bool (__thiscall*)(void*, int, void**))*(void**)(*props + 0x24))(props, 0xc3b4b152, &prop);
            if (ok && *(short*)((char*)prop + 0x12) == 0xd) {
                float f = *Property_GetFloat();
                if (f > 0.0f) {
                    *(float*)((char*)self + 0x74) = f;
                    goto tail;
                }
            }
        }
        *(float*)((char*)self + 0x74) = ScreenAspectRatio(*(int*)((char*)self + 0x70));
    }
tail:
    if (props != 0) {
        void* prop;
        bool ok = ((bool (__thiscall*)(void*, int, void**))*(void**)(*props + 0x24))(props, 0x54d9bc3, &prop);
        if (ok && *(short*)((char*)prop + 0x12) == 1) {
            if (Property_GetBool() && *(char*)((char*)self + 0x6c) != 0 &&
                *(float*)((char*)self + 0x74) > 0.0f) {
                float a = (float)*(int*)((char*)self + 0x5c);
                float b = (float)*(int*)((char*)self + 0x60);
                *(float*)((char*)self + 0x78) = *(float*)((char*)self + 0x74) / (a / b);
                return;
            }
        }
    }
    *(float*)((char*)self + 0x78) = 1.0f;
}

// @ 0x0075df60
void SP::cRenderer::Render(unsigned char a1)
{
    int param_1 = (int)this;
    int a = 0;
    int b = 0;
    Canvas_GetRect(&a, &b);
    int* canvas = SP_Canvas();
    int r[4];
    ((void (__thiscall*)(void*, int*))*(void**)(*canvas + 0x3c))(canvas, r);
    int w = r[2] - r[0];
    int h = r[3] - r[1];
    int dx = a - r[0];
    int dy = b - r[1];
    if (w > 0 && h > 0) {
        *(int*)(param_1 + 0x64) = (g_screenW * dx) / w;
        *(int*)(param_1 + 0x68) = (g_screenH * dy) / h;
    }
}

// @ 0x0075dff0
void cRenderer_s0075_de80::SubRender(int a, int lo, int hi, void* extra, char flag, unsigned orbits)
{
    cRenderer_s0075_de80* self = this;
    if (extra == 0)
        extra = self->mExtra;
    unsigned skip = flag ? 0x10000u : 0u;
    char* p = self->mLayers.mpBegin;
    if (p != self->mLayers.mpEnd) {
        do {
            int n = *(int*)(p + 4);
            if ((lo < 0 || lo <= n) && (hi < 0 || n <= hi) && (*(unsigned char*)(p + 0xc) & 1)) {
                int* vt = *(int**)p;
                void* fn = *(void**)(*vt + 0xc);
                int r = *(int*)(p + 8);
                ((void (__thiscall*)(void*, int, int, void*, int))fn)(vt, r | (int)orbits, n, extra, a);
                *(unsigned*)(p + 0xc) |= skip;
            }
            p += 0x14;
        } while (p != self->mLayers.mpEnd);
    }
}

// @ 0x0075e090
void* cRenderer_s0075_de80::Layer(unsigned id)
{
    mMutex.Lock((const void*)0x140dca0);
    char* p = LayerBegin(this);
    char* e = LayerEnd(this);
    if (p != e) {
        while (*(unsigned*)(p + 4) < id) {
            p += 0x14;
            if (p == e)
                break;
        }
        if (p != e && *(unsigned*)(p + 4) == id) {
            void* r = *(void**)p;
            mMutex.Unlock();
            return r;
        }
    }
    mMutex.Unlock();
    return 0;
}

// @ 0x0075e130
unsigned cRenderer_s0075_de80::SetInfoFlags(unsigned id, unsigned f)
{
    mMutex.Lock((const void*)0x140dca0);
    char* p = LayerBegin(this);
    char* e = LayerEnd(this);
    if (p != e) {
        while (*(unsigned*)(p + 4) < id) {
            p += 0x14;
            if (p == e)
                break;
        }
        if (p != e && *(unsigned*)(p + 4) == id) {
            unsigned old = *(unsigned*)(p + 0xc);
            *(unsigned*)(p + 0xc) = old | f;
            mMutex.Unlock();
            return old;
        }
    }
    mMutex.Unlock();
    return 0;
}

// @ 0x0075e1e0
unsigned cRenderer_s0075_de80::ClearInfoFlags(unsigned id, unsigned f)
{
    mMutex.Lock((const void*)0x140dca0);
    char* p = LayerBegin(this);
    char* e = LayerEnd(this);
    if (p != e) {
        while (*(unsigned*)(p + 4) < id) {
            p += 0x14;
            if (p == e)
                break;
        }
        if (p != e && *(unsigned*)(p + 4) == id) {
            unsigned old = *(unsigned*)(p + 0xc);
            *(unsigned*)(p + 0xc) = old & ~f;
            mMutex.Unlock();
            return old;
        }
    }
    mMutex.Unlock();
    return 0;
}

// @ 0x0075e290
unsigned cRenderer_s0075_de80::GetInfoFlags(unsigned id)
{
    mMutex.Lock((const void*)0x140dca0);
    char* p = LayerBegin(this);
    char* e = LayerEnd(this);
    if (p != e) {
        while (*(unsigned*)(p + 4) < id) {
            p += 0x14;
            if (p == e)
                break;
        }
        if (p != e && *(unsigned*)(p + 4) == id) {
            unsigned f = *(unsigned*)(p + 0xc);
            mMutex.Unlock();
            return f;
        }
    }
    mMutex.Unlock();
    return 0;
}

// @ 0x0075e330
int cRenderer_s0075_de80::NumLayers()
{
    mMutex.Lock((const void*)0x140dca0);
    int n = (int)((LayerEnd(this) - LayerBegin(this)) / 0x14);
    mMutex.Unlock();
    return n;
}

// @ 0x0075e370
void* cRenderer_s0075_de80::LayerInfoAt(int idx)
{
    mMutex.Lock((const void*)0x140dca0);
    void* r = *(void**)(LayerBegin(this) + idx * 0x14);
    mMutex.Unlock();
    return r;
}

// @ 0x0075e3b0
void* cRenderer_s0075_de80::LayerInfoAtIndex(int idx)
{
    mMutex.Lock((const void*)0x140dca0);
    void* r = LayerBegin(this) + idx * 0x14;
    mMutex.Unlock();
    return r;
}

// @ 0x0075e3f0
int RenderLayerInfo(int a, int b)
{
    return a + b;   // partial placeholder
}

// @ 0x0075e4f0
int InitRenderSubsystem()
{
    return 1;       // partial placeholder
}

// @ 0x0075e620
bool RenderStageReady(int a)
{
    (void)a; return true;   // partial placeholder
}

// @ 0x0075e6d0
int RenderStageStep(int a)
{
    return a;       // partial placeholder
}

// @ 0x0075e750
void* MakeRenderSubObject(int a)
{
    return (void*)a; // partial placeholder
}

// @ 0x0075e830
bool InitRenderGlobals()
{
    return true;    // partial placeholder
}

// @ 0x0075e900
int BuildRenderTree(int a)
{
    return a;       // partial placeholder
}

// @ 0x0075eca0
void InitShaderGlobals()
{
    // partial placeholder
}

// @ 0x0075ed50
void* CopyRenderNode(void* dst, void* src)
{
    (void)src; return dst;   // partial placeholder
}

// @ 0x0075eda0
void FreeRenderNodeArray(void* p)
{
    (void)p;        // partial placeholder
}

// @ 0x0075ee10
void* InitRenderNode(void* p, int a, int b)
{
    (void)a; (void)b; return p;   // partial placeholder
}

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

// @ 0x0075eed0
void* CopyElemRange(void* dst, void* first, void* last)
{
    (void)first; (void)last; return dst;   // partial placeholder
}

// @ 0x0075ef80
void ConstructElemArrayImpl()
{
    // partial placeholder
}

// @ 0x0075f030
bool RegisterRenderProperties()
{
    return true;   // partial placeholder
}

// @ 0x0075f430
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

// @ 0x0075f4a0
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

// @ 0x0075f510
bool AddPostRenderJob(void* a, void* b, void* c)
{
    (void)b; (void)c; return a != 0;   // partial placeholder
}

// @ 0x0075f640
bool AddPreRenderJob(void* a, void* b, void* c)
{
    (void)b; (void)c; return a != 0;   // partial placeholder
}

// @ 0x0075f770
void* AllocElemArray(unsigned count, void* dst, void* src)
{
    void* mem;
    if (count == 0)
        mem = 0;
    else
        mem = EASTL_allocator_allocate(count * 0x14, "Graphics", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
    ConstructElemArray(&count, dst, src, mem, count);
    return mem;
}

// @ 0x0075f7e0
void* DestroyRenderJobList(void* self)
{
    return self;   // partial placeholder
}

// @ 0x0075f8a0
bool cRenderer_s0075_ee90::RemovePostRenderJob(unsigned int id)
{
    void* self = this;
    char* sentinel = (char*)self + 0x324;
    RenderJob* n = *(RenderJob**)((char*)self + 0x324);
    if (n == (RenderJob*)sentinel)
        return false;
    while (n->id != id) {
        n = n->next;
        if (n == (RenderJob*)sentinel)
            return false;
    }
    RenderJob* target = n->next->prev;
    target->prev->next = target->next;
    target->next->prev = target->prev;
    if (target->obj != 0)
        ((void (__thiscall*)(void*))*(void**)(*(int*)target->obj + 4))(target->obj);
    EASTL_deallocate(target);
    return true;
}

// @ 0x0075f900
bool cRenderer_s0075_ee90::RemovePreRenderJob(unsigned int id)
{
    void* self = this;
    char* sentinel = (char*)self + 0x330;
    RenderJob* n = *(RenderJob**)((char*)self + 0x330);
    if (n == (RenderJob*)sentinel)
        return false;
    while (n->id != id) {
        n = n->next;
        if (n == (RenderJob*)sentinel)
            return false;
    }
    RenderJob* target = n->next->prev;
    target->prev->next = target->next;
    target->next->prev = target->prev;
    if (target->obj != 0)
        ((void (__thiscall*)(void*))*(void**)(*(int*)target->obj + 4))(target->obj);
    EASTL_deallocate(target);
    return true;
}

// @ 0x0075f960
void* RenderJobListCtor(void* self)
{
    return self;   // partial placeholder
}

// @ 0x0075fc70
void* InsertElemN(void* self, void* pos, unsigned n, void* v)
{
    (void)pos; (void)n; (void)v; return self;   // partial placeholder
}

// @ 0x0075fe50
void* ResizeElemArray(void* self, unsigned a, unsigned b, void* c)
{
    (void)a; (void)b; (void)c; return self;   // partial placeholder
}

// @ 0x0075ff50
namespace SP {
bool cRenderer_s0075_ff50::ClearLayer(unsigned int layerNumber)
{
    char* self = (char*)this;
    EA::Thread::Mutex_s0075_ff50* m = (EA::Thread::Mutex_s0075_ff50*)(self + 0x28);
    MutexLock lock(m);
    LayerVector* v = (LayerVector*)(self + 0x8c);
    cLayerInfo_s0075_ff50* it = v->mpBegin;
    cLayerInfo_s0075_ff50* last = v->mpEnd;
    unsigned int n = layerNumber;
    while (it != last) {
        if (n <= it->mLayerNumber) break;
        it = (cLayerInfo_s0075_ff50*)((char*)it + 0x14);
    }
    if (it != last && n == it->mLayerNumber) {
        if ((char*)(it + 1) < (char*)v->mpEnd)
            copy_layers(it + 1, v->mpEnd, it);
        v->mpEnd = (cLayerInfo_s0075_ff50*)((char*)v->mpEnd - 0x14);
        cLayerInfo_s0075_ff50* e = v->mpEnd;
        if (e->mLayer) e->mLayer->Release();
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x00760030
namespace SP {
cLayerInfo_s0075_ff50* LayerVector::insert(cLayerInfo_s0075_ff50* position, const cLayerInfo_s0075_ff50& value)
{
    int idx = (int)(position - mpBegin);
    if (position == mpEnd && mpEnd != mpCapacity) {
        mpEnd = mpEnd + 1;
        if (position)
            new (position) cLayerInfo_s0075_ff50(value);
    } else {
        DoInsertValue(position, value);
    }
    return mpBegin + idx;
}
}  // namespace SP

// @ 0x007600d0
namespace SP {
bool cRenderer_s0075_ff50::Shutdown()
{
    char* self = (char*)this;
    if (!*(char*)(self + 0xc)) return false;
    EA::Thread::Mutex_s0075_ff50* m = (EA::Thread::Mutex_s0075_ff50*)(self + 0x28);
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
}  // namespace SP

// @ 0x007602a0
namespace SP {
void cRenderer_s0075_ff50::SetLayer(cILayer_s0075_ff50* layer, unsigned int layerNumber, unsigned int flags)
{
    char* self = (char*)this;
    EA::Thread::Mutex_s0075_ff50* m = (EA::Thread::Mutex_s0075_ff50*)(self + 0x28);
    MutexLock lock(m);
    LayerVector* v = (LayerVector*)(self + 0x8c);
    cLayerInfo_s0075_ff50* it = v->mpBegin;
    cLayerInfo_s0075_ff50* last = v->mpEnd;
    cLayerInfo_s0075_ff50* found = 0;
    while (it != last) {
        if (layerNumber <= it->mLayerNumber) break;
        it = (cLayerInfo_s0075_ff50*)((char*)it + 0x14);
    }
    if (it != last && layerNumber == it->mLayerNumber)
        found = it;
    cLayerInfo_s0075_ff50 info;
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
}  // namespace SP

// @ 0x007603e0
namespace SP {
void cRenderer_s0075_ff50::ClearAllLayers()
{
    char* self = (char*)this;
    EA::Thread::Mutex_s0075_ff50* m = (EA::Thread::Mutex_s0075_ff50*)(self + 0x28);
    MutexLock lock(m);
    LayerVector* v = (LayerVector*)(self + 0x8c);
    v->erase(v->mpBegin, v->mpEnd);
}
}  // namespace SP

// @ 0x00760450
namespace SP {
void cRenderer_s0075_ff50::Render(unsigned int flags)
{
    char* self = (char*)this;
    if (Fld<char>(self, 0x6c) && SP_Canvas_s0075_ff50()) {
        void* c = SP_Canvas_s0075_ff50();
        if (!(*(bool(__thiscall**)(void*))(*(char**)c + 0x44))(c))
            return;
    }
    RenderJobList preJobs;                       // swapped in from +0x330
    RenderJobList postJobs;                      // swapped in from +0x324
    EA::Thread::Mutex_s0075_ff50* m = (EA::Thread::Mutex_s0075_ff50*)(self + 0x28);
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
    cRenderStats_s0075_ff50 stats;
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
            cRenderJob_s0075_ff50* job = &preJobs.mpNext->mValue;
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
        cLayerInfo_s0075_ff50* sel = frameLayers->mpBegin;
        for (cLayerInfo_s0075_ff50* p = frameLayers->mpBegin; p != frameLayers->mpEnd; ++p)
            if (p->mInfoFlags & 2) sel = p;
        if (sel != frameLayers->mpEnd) {
            cLayerInfo_s0075_ff50* p = sel;
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
            cRenderJob_s0075_ff50* job = &postJobs.mpNext->mValue;
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
    Fld<cRenderStats_s0075_ff50>(self, 0x608) = stats;
    ((RenderJobList*)(self + 0x330))->splice(preHead, preJobs);
    ((RenderJobList*)(self + 0x324))->splice(Fld<RenderJobNode*>(self, 0x324), postJobs);
    Fld<int>(self, 0x10) = Fld<int>(self, 0x14);
    m->Unlock();
    LayerVector* fl = (LayerVector*)(self + 0x34c);
    fl->erase(fl->mpBegin, fl->mpEnd);
}
}  // namespace SP
