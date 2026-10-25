// Slice s0075de80: SP::cRenderer layer/info accessors, render settings, and related
// engine helpers. /O2, SSE (/arch:SSE2).  Functions 0075e090/130/1e0/290 carry MSVC
// EH frames around the mutex; the reconstructions keep the behavior but not the frame.
#include "types.h"
#include <intrin.h>

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned debugFlags,
                                          const char* file, int line); // 0x00f473a0
struct RefObj; // refcounted interface (AddRef at vtbl +0x00, Release at vtbl +0x04)
struct SubObj {
    RefObj* m0;       // +0x00
    int m4;           // +0x04
    int m8;           // +0x08
    int m_0c_3c[0xb];
};

namespace EA { namespace Thread {
class Mutex { public: void Lock(const void*); void Unlock(); char pad[0x28]; };
}}

struct LayerDrawArg;

struct RenderLayerArray {
    char* mpBegin;                 // +0
    char* mpEnd;                   // +4
};

struct cRenderer {
    char pad00[0x28];              // +0x00
    EA::Thread::Mutex mMutex;      // +0x28
    char pad50[0x3c];              // +0x50
    char pad8c[0x33c - 0x8c];      // +0x8c
    char mExtra[0x34c - 0x33c];    // +0x33c
    RenderLayerArray mLayers;      // +0x34c
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
    void LayerInfoAt_Draw(LayerDrawArg* arg, int unused);  // @ 0x0075e3f0
    int BuildRenderTree(char refresh, int w, int h, int budget);  // @ 0x0075e900
    int InitRenderSubsystem();          // @ 0x0075e4f0
    bool InitRenderGlobals();           // @ 0x0075e830
    void InitShaderGlobals(int arg);    // @ 0x0075eca0
};

static inline char* LayerBegin(cRenderer* r) { return *(char**)((char*)r + 0x8c); }
static inline char* LayerEnd(cRenderer* r)   { return *(char**)((char*)r + 0x90); }

// @ 0x0075e330
int cRenderer::NumLayers()
{
    mMutex.Lock((const void*)0x140dca0);
    int n = (int)((LayerEnd(this) - LayerBegin(this)) / 0x14);
    mMutex.Unlock();
    return n;
}

// @ 0x0075e370
void* cRenderer::LayerInfoAt(int idx)
{
    mMutex.Lock((const void*)0x140dca0);
    void* r = *(void**)(LayerBegin(this) + idx * 0x14);
    mMutex.Unlock();
    return r;
}

// @ 0x0075e3b0
void* cRenderer::LayerInfoAtIndex(int idx)
{
    mMutex.Lock((const void*)0x140dca0);
    void* r = LayerBegin(this) + idx * 0x14;
    mMutex.Unlock();
    return r;
}

// @ 0x0075e090
void* cRenderer::Layer(unsigned id)
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
unsigned cRenderer::SetInfoFlags(unsigned id, unsigned f)
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
unsigned cRenderer::ClearInfoFlags(unsigned id, unsigned f)
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
unsigned cRenderer::GetInfoFlags(unsigned id)
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

// @ 0x0075dff0
void cRenderer::SubRender(int a, int lo, int hi, void* extra, char flag, unsigned orbits)
{
    cRenderer* self = this;
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

// ---------------------------------------------------------------- render settings
extern int* g_sAppProperties;   // @ 0x015fd918
extern float* Property_GetFloat();   // @ 0x0041ea70
extern bool  Property_GetBool();     // @ 0x0041e920
extern float ScreenAspectRatio(int); // @ 0x0075d9e0

// @ 0x0075de80
void cRenderer::RenderSettings(char useProps)
{
    cRenderer* self = this;
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
extern void Canvas_GetRect(int*, int*);   // @ 0x008d2f30
extern int* SP_Canvas();                  // @ 0x0067dcf0
extern int g_screenW;   // @ 0x0171244c
extern int g_screenH;   // @ 0x01712450
void cRenderer::ResizeFromCanvas()
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

// ---------------------------------------------------------------- render node / layer records
// A refcounted render-node handle record: slot 0 is a refcounted interface pointer, slots 1..3
// are copied verbatim.  Element stride of the owning array is 0x14 (5 slots).
struct RefObj {
    virtual void AddRef();          // vtbl +0x00
    virtual void Release();         // vtbl +0x04
};
struct RenderNode {
    RefObj* m0;
    int m4;
    int m8;
    int mC;
    float m10;
    RenderNode* operator=(RenderNode* other);   // @ 0x0075ed50
};
struct RenderNodeArray {
    RenderNode* mBegin;             // +0x00
    RenderNode* mEnd;               // +0x04
    char pad08[8];                  // +0x08
    RenderNode* mAlloc;             // +0x10
    void Free();                    // @ 0x0075eda0
};

// @ 0x0075ed50
RenderNode* RenderNode::operator=(RenderNode* other)
{
    RefObj* const old = m0;
    RefObj* const src = other->m0;
    if (src != old) {
        if (src != 0)
            src->AddRef();
        m0 = src;
        if (old != 0)
            old->Release();
    }
    m4 = other->m4;
    m8 = other->m8;
    mC = other->mC;
    m10 = other->m10;
    return this;
}

// @ 0x0075eda0
void RenderNodeArray::Free()
{
    RenderNode* p = mBegin;
    for (; p < mEnd; p += 1) {
        if (p->m0 != 0)
            p->m0->Release();
    }
    RenderNode* const first = mBegin;
    if (first != 0 && first != mAlloc)
        EASTL_allocator_deallocate(first);
}

// ---------------------------------------------------------------- layer info builder
// The info record passed to LayerInfoAt_Draw; member layout matches 0075e3f0's offsets.
struct DrawSink {              // the object at this+0x58 (a render sink)
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void Pick14(int obj, int rel, int z);   // vtbl +0x14
    virtual void Pick18(int obj, int rel, int z);   // vtbl +0x18
};
struct DrawIfc {               // arg->m0 : has a Draw at vtbl +0x0c
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void Draw(int a, unsigned flags, int* rect, int b);   // vtbl +0x0c
};
struct RefCnt {                // arg->m1c / arg->m24 : vtbl +0x08 ref
    virtual void r00();
    virtual void r04();
    virtual void Ref();
};
struct LayerDrawArg {
    DrawIfc* m0;                // +0x00
    int m4;
    int m8;
    int mC;
    int m10;                    // +0x10
    char m14;                   // +0x14  selects vtbl +0x14 / +0x18
    char pad15[3];
    int m18;                    // +0x18  primary render object
    int m1c;                    // +0x1c  ref target
    int m20;                    // +0x20  secondary render object
    int m24;                    // +0x24
    int m28;                    // +0x28
    int m2c;
    int m30;
    int m34;
};

// @ 0x0075e3f0
void cRenderer::LayerInfoAt_Draw(LayerDrawArg* arg, int param_3)
{
    cRenderer* const self = this;
    DrawSink* sink;
    if (arg->m18 != 0 && (sink = *(DrawSink**)((char*)self + 0x58)) != 0) {
        if (arg->m14 != 0)
            sink->Pick18(arg->m18, arg->m1c, 0);
        else
            sink->Pick14(arg->m18, arg->m1c, 0);
        ((RefCnt*)arg->m1c)->Ref();
    }
    int a = arg->m28;
    if (a == 0) a = *(int*)((char*)self + 0x33c);
    int b = arg->m2c;
    if (b == 0) b = *(int*)((char*)self + 0x340);
    int c = arg->m30;
    if (c == 0) c = *(int*)((char*)self + 0x344);
    int d = arg->m34;
    if (d == 0) d = *(int*)((char*)self + 0x348);
    int rect[4];
    rect[0] = a;
    rect[1] = b;
    rect[2] = c;
    rect[3] = d;
    arg->m0->Draw(arg->m10, 0x80000000u, rect, param_3);
    if (arg->m20 != 0 && (sink = *(DrawSink**)((char*)self + 0x58)) != 0) {
        if (arg->m14 != 0)
            sink->Pick18(arg->m20, arg->m24, 0);
        else
            sink->Pick14(arg->m20, arg->m24, 0);
        ((RefCnt*)arg->m24)->Ref();
    }
    *(int*)((char*)param_3 + 0x18) += 1;
}

// ---------------------------------------------------------------- stage/property caches
extern "C" int __fastcall FUN_006237a0(int x);   // 0x006237a0  (arg in ecx) -> ticks
extern "C" float* __fastcall FUN_004e4230(int x); // 0x004e4230 (arg in ecx) -> float*

struct Stage {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual bool Probe(int a, int* out);       // vtbl +0x24
    char pad04[0x2c];
    int m30;                                   // +0x30
    int m34;                                   // +0x34
};

struct StageCache {
    float m0;                                  // +0x00
    Stage* m4;                                 // +0x04
    int m8;                                    // +0x08
    int mC;                                    // +0x0c
    bool Ready();                              // @ 0x0075e620
    void Step(Stage* arg);                     // @ 0x0075e6d0
};

// @ 0x0075e620
bool StageCache::Ready() {
    Stage* const s = m4;
    if (s != 0) {
        int e = s->m30 ? FUN_006237a0(s->m30) : 0;
        if (mC != s->m34 + e) {
            int e2 = s->m30 ? FUN_006237a0(s->m30) : 0;
            mC = s->m34 + e2;
            int t;
            if (s->Probe(m8, &t)) {
                float* p = FUN_004e4230(t);
                float f = *p;
                if (m0 != f) {
                    m0 = f;
                    return true;
                }
            }
        }
    }
    return false;
}

// @ 0x0075e6d0
void StageCache::Step(Stage* arg) {
    int t;
    if (arg->Probe(m8, &t)) {
        short ty = *(short*)(t + 0x12);
        int* src;
        if (ty == 0xd || ty == 0x10) {
            if ((*(unsigned char*)(t + 0x10) & 0x30) == 0)
                src = (ty != 0) ? 0 : (int*)t;
            else
                src = *(int**)t;
        } else {
            src = (int*)0x15d9c6c;
        }
        m0 = *(float*)src;
    }
    Stage* const s = m4;
    if (s->m30 != 0) {
        mC = s->m34 + FUN_006237a0(s->m30);
        return;
    }
    mC = s->m34;
}

// @ 0x0075e750
void* __stdcall MakeRenderSubObject(SubObj* src)
{
    SubObj* dst = (SubObj*)((char*)EASTL_allocator_allocate(0x40,
        "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1) + 8);
    if (dst != 0) {
        dst->m0 = src->m0;
        if (src->m0 != 0)
            src->m0->AddRef();
        dst->m4 = src->m4;
        dst->m8 = src->m8;
        int* d = (int*)((char*)dst + 0xC);
        int* s = (int*)((char*)src + 0xC);
        for (int i = 0xb; i != 0; --i)
            *d++ = *s++;
    }
    return (char*)dst - 8;
}

// ---------------------------------------------------------------- render subsystem / globals
// rw global device parameters (_m_parameters_Device_graphics_rw__0VParameters_123_A, 15 dwords @ 0x1712444).
struct RWDeviceParams { int m[0xf]; };
extern RWDeviceParams g_rwDeviceParams;   // 0x01712444
extern int g_spMemPool;                    // 0x016C8B44 (cSPMemPool singleton)

// Raw engine entry points used by the subsystem registration chain (each carries its VA).
extern "C" void* __cdecl FUN_00928a30(int pool, unsigned len, unsigned align, int, int, int, int, int); // 0x00928A30
extern "C" void* __cdecl FUN_011e3100();                          // 0x011E3100 AtomTableSingleton
extern "C" void  __cdecl FUN_011e4130(void* a, unsigned n, void* t); // 0x011E4130 rwArenaOpen
extern "C" void  __cdecl FUN_011f0820();                          // 0x011F0820
extern "C" void  __cdecl FUN_011ed9e0();                          // 0x011ED9E0
extern "C" void  __cdecl FUN_011fa2a0();                          // 0x011FA2A0
extern "C" void  __cdecl FUN_011f4250();                          // 0x011F4250
extern "C" void  __cdecl FUN_006c12a0();                          // 0x006C12A0
extern "C" void  __cdecl FUN_011fa280();                          // 0x011FA280
extern "C" void  __cdecl FUN_011f3480();                          // 0x011F3480
extern "C" void  __cdecl FUN_011f38c0();                          // 0x011F38C0
extern "C" void  __cdecl FUN_011f4e70();                          // 0x011F4E70
extern "C" void  __cdecl FUN_011f51b0();                          // 0x011F51B0
extern "C" void  __cdecl FUN_011f9540();                          // 0x011F9540
extern "C" void  __cdecl FUN_011fa210();                          // 0x011FA210
extern "C" void  __cdecl FUN_01205800();                          // 0x01205800
extern "C" int   __cdecl FUN_011e22c0(unsigned t);                // 0x011E22C0 ArenaTypeRegGetType
extern "C" void  __cdecl FUN_01205740();                          // 0x01205740
extern "C" void  __cdecl FUN_01200900();                          // 0x01200900
extern "C" void  __cdecl FUN_012010a0();                          // 0x012010A0
extern "C" void  __cdecl FUN_011fd950();                          // 0x011FD950
extern "C" void  __cdecl FUN_01201010();                          // 0x01201010
extern "C" void  __cdecl FUN_01200f60();                          // 0x01200F60
extern "C" void  __cdecl FUN_01200a70();                          // 0x01200A70
extern "C" void  __cdecl FUN_011fe710();                          // 0x011FE710
extern "C" void  __cdecl FUN_011ff9f0(void* p);                   // 0x011FF9F0
extern "C" void* __cdecl FUN_011ffa40(int x);                     // 0x011FFA40
extern "C" void  __cdecl FUN_0075b830();                          // 0x0075B830
extern "C" void  __cdecl FUN_007c56e0();                          // 0x007C56E0
extern "C" void  __cdecl FUN_007c5720();                          // 0x007C5720
extern "C" void  __cdecl FUN_007c57c0();                          // 0x007C57C0
extern "C" void  __cdecl FUN_01200920();                          // 0x01200920
extern "C" void  __cdecl FUN_012010c0();                          // 0x012010C0
extern "C" void  __cdecl FUN_011fd970();                          // 0x011FD970
extern "C" void  __cdecl FUN_01200a90();                          // 0x01200A90
extern "C" void  __cdecl FUN_007c5700();                          // 0x007C5700
extern "C" void  __cdecl FUN_007c5740();                          // 0x007C5740
extern "C" void  __cdecl FUN_01201030();                          // 0x01201030
extern "C" void  __cdecl FUN_012056a0();                          // 0x012056A0
extern "C" void  __cdecl FUN_012056f0();                          // 0x012056F0
extern "C" int   g_015d09c4; extern "C" int g_015d09ac;           // 0x015D09C4 / 0x015D09AC

// cRenderer::Init helpers.
extern "C" void  __cdecl FUN_005d60f0();                          // 0x005D60F0
extern "C" void  __cdecl FUN_00900b10();                          // 0x00900B10
extern "C" void  __cdecl FUN_00f47410(void*);                     // 0x00F47410 operator delete
extern "C" void  __cdecl FUN_0075d920();                          // 0x0075D920
extern "C" void  __cdecl FUN_011f8ae0(void* p);                   // 0x011F8AE0
extern "C" int   __cdecl FUN_011f84b0();                          // 0x011F84B0 rw::graphics::Device::Initialize
extern "C" void  __cdecl FUN_012057a0();                          // 0x012057A0
extern "C" int   __cdecl FUN_00410370(int* props, unsigned id, unsigned* out);  // 0x00410370
extern "C" int   __cdecl FUN_0067dcc0();                          // 0x0067DCC0 MessageServer
extern "C" void  __cdecl FUN_006926f0(void* p);                   // 0x006926F0
extern "C" void  __cdecl FUN_011e43c0();                          // 0x011E43C0 rwArenaClose
extern "C" void  __cdecl FUN_009276c0(void* p);                   // 0x009276C0 BindPool::Free
extern "C" __declspec(dllimport) unsigned int __stdcall timeBeginPeriod(unsigned int);  // winmm!timeBeginPeriod
extern "C" void  __cdecl FUN_00435480(void* sw);                  // 0x00435480 Timer::StartIfUnset

// cRenderer::Update helpers.
extern "C" void  __cdecl FUN_0075dc20(float v);                   // 0x0075DC20 BuildPaletteTable
struct PropList { bool GetDescription(unsigned id); };            // 0x006A25A0 (thiscall member)
extern unsigned char g_016fa3bd;                                  // 0x016FA3BD
extern int g_016f9530[1];                                         // 0x016F9530 (samplerStateDirty)
extern int g_016f9574[1];                                         // 0x016F9574 (end of samplerStateDirty)
extern int g_016f9ff0[1];                                         // 0x016F9FF0 (sampler flags, stride 0x38)
extern int g_016fa38c;                                            // 0x016FA38C
extern int g_016f9248;                                            // 0x016F9248

// @ 0x0075e4f0 — reset + register the whole arena subsystem (a long chain of global registrations).
int cRenderer::InitRenderSubsystem()
{
    void* p = FUN_00928a30(g_spMemPool, 0x400, 0x10, 0, 0, 0, 0, 0);
    *(void**)((char*)this + 0x20) = p;
    FUN_011e4130(p, 0x400, FUN_011e3100());
    FUN_011f0820();
    FUN_011ed9e0();
    FUN_011fa2a0();
    FUN_011f4250();
    FUN_006c12a0();
    FUN_011fa280();
    FUN_011f3480();
    FUN_011f38c0();
    FUN_011f4e70();
    FUN_011f51b0();
    FUN_011f9540();
    FUN_011fa210();
    FUN_01205800();
    FUN_01205800();
    int* t = (int*)FUN_011e22c0(0x80003);
    *(void**)((char*)t + 0xc) = (void*)FUN_01205740;
    FUN_01200900();
    FUN_012010a0();
    FUN_011fd950();
    FUN_01201010();
    FUN_01200f60();
    FUN_01200a70();
    FUN_011fe710();
    FUN_011ff9f0(&g_015d09c4);
    FUN_011ff9f0(&g_015d09ac);
    int* u = (int*)FUN_011ffa40(1);
    *(void**)((char*)u + 4) = (void*)FUN_0075b830;
    FUN_007c56e0();
    FUN_007c5720();
    FUN_007c57c0();
    FUN_01200920();
    FUN_012010c0();
    FUN_011fd970();
    FUN_01200a90();
    FUN_007c5700();
    FUN_007c5740();
    FUN_01201030();
    int* v = (int*)FUN_011e22c0(0x80003);
    *(void**)((char*)v + 4) = (void*)FUN_012056a0;
    *(void**)((char*)v + 8) = (void*)FUN_012056f0;
    return 1;
}

// @ 0x0075e830 — cRenderer::Init: one-time global init guarded by this+0xc.
bool cRenderer::InitRenderGlobals()
{
    if (*(char*)((char*)this + 0xc) != 0)
        return false;

    *(void**)0x016F4AE4 = (void*)FUN_005d60f0;
    *(void**)0x016F4AE8 = (void*)FUN_00900b10;
    *(void**)0x016F4AEC = (void*)FUN_00f47410;

    if (!InitRenderSubsystem())
        return false;

    FUN_011f8ae0((void*)FUN_0075d920);
    if (FUN_011f84b0() != 0) {
        FUN_012057a0();
        *(char*)((char*)this + 0xc) = 1;
        FUN_00410370(g_sAppProperties, 0x2a82464, (unsigned*)((char*)this + 0x10));
        *(int*)((char*)this + 0x14) = *(int*)((char*)this + 0x10);
        *(int*)((char*)this + 0x58) = FUN_0067dcc0();
        FUN_006926f0((void*)__readfsdword(0x18));
        timeBeginPeriod(1);
        FUN_00435480((char*)this + 0x5e8);
        return true;
    }
    if (*(void**)((char*)this + 0x20) != 0) {
        FUN_011e43c0();
        FUN_009276c0(*(void**)((char*)this + 0x20));
        *(void**)((char*)this + 0x20) = 0;
    }
    return false;
}

// @ 0x0075eca0 — cRenderer::Update(int): refresh screen info, palette table and sampler state.
void cRenderer::InitShaderGlobals(int arg)
{
    StageCache* sc = (StageCache*)((char*)this + 0x638);
    RWDeviceParams p = g_rwDeviceParams;
    p.m[2] = arg;

    *(int*)((char*)this + 0x5c) = p.m[2];
    *(int*)((char*)this + 0x60) = p.m[3];
    ((void(__thiscall*)(cRenderer*))(*(void***)this)[0x38 / 4])(this);

    if (sc->Ready())
        FUN_0075dc20(sc->m0);

    unsigned char b = (unsigned char)((PropList*)g_sAppProperties)->GetDescription(0x5c9621f);
    g_016fa3bd = b;
    int v = b ? 8 : 1;
    int* pd = g_016f9530;
    int* pf = g_016f9ff0;
    do {
        *pd |= 0x200;
        *pf = v;
        ++pd;
        pf += 0xe;
    } while (pd < g_016f9574);
    g_016fa38c |= 0x80000;
    g_016f9248 = 0;
}

// @ 0x0075ee10 — cPropertyInfo<float> constructor (thiscall, 3 stack args, SEH prolog).
struct PropertyRef {
    virtual void AddRef();  // vtbl +0
    virtual void Release(); // vtbl +4
};
struct PropertyInfo {
    float mValue;           // +0
    PropertyRef* mpList;    // +4
    unsigned mPropertyID;   // +8
    int mModCount;          // +0xc
    PropertyInfo(PropertyRef* list, unsigned id, float value);  // @ 0x0075ee10
};
PropertyInfo::PropertyInfo(PropertyRef* list, unsigned id, float value)
{
    StageCache* sc = (StageCache*)(void*)this;
    mValue = value;
    mpList = list;
    if (list != 0)
        list->AddRef();
    mPropertyID = id;
    mModCount = 0;
    if (list != 0)
        sc->Step((Stage*)list);
}
// ---------------------------------------------------------------- BuildRenderTree (0x0075e900)
// Device state save/restore blocks live in a global 0x20-byte-strided array.
struct DevElem { int m[8]; };                     // 0x20 stride
extern DevElem g_devElems[1];                     // 0x016FA5E8 (0x800 elements)
extern "C" void  __cdecl FUN_011f7fd0(void* p);   // 0x011F7FD0 Device::Reset
extern "C" void  __cdecl FUN_011f7f10();          // 0x011F7F10 Device::Stop
extern "C" void  __cdecl FUN_011f8680(void* p);   // 0x011F8680 Device::StartInternal
extern "C" void  __cdecl FUN_011f8270(void* out); // 0x011F8270 D3D9GetDesktopDisplayMode
extern "C" void* __cdecl FUN_0067dd70();          // 0x0067DD70 MaterialManager
extern "C" int   __cdecl FUN_00689590();          // 0x00689590
extern "C" void  __cdecl FUN_00689560(int);       // 0x00689560
extern "C" int*  __cdecl FUN_0067dcf0();          // 0x0067DCF0 Device
extern "C" bool  __cdecl FUN_0075dd30(int, int, int, int);  // 0x0075DD30 MergeLocalLights
extern "C" int   __cdecl FUN_006a2660(void* props, unsigned id);  // 0x006A2660 GetIntProperty

// @ 0x0075e900 — cRenderer::Flip(char refresh, int w, int h, int budget): reconfigure the device and
// hand the new viewport to the canvas.
int cRenderer::BuildRenderTree(char refresh, int w, int h, int budget)
{
    // Large scratch buffer the original keeps for the device-state snapshot.
    int scratch[0x800 * 8];

    RWDeviceParams params = g_rwDeviceParams;
    if (w < 0) w = params.m[2];
    if (h < 0) h = params.m[3];
    if (budget < 0) budget = params.m[0];

    int prevBudget = FUN_006a2660(g_sAppProperties, 0xd77e98);
    bool refresh2 = ((PropList*)g_sAppProperties)->GetDescription(0x5dd4647) != 0;
    bool useRefresh = refresh2 || refresh != 0;

    int mode[4];
    FUN_011f8270(mode);

    bool haveScratch;
    if (useRefresh) {
        if (!FUN_0075dd30(budget, w, h, prevBudget))
            useRefresh = false;
        haveScratch = params.m[9] != 0;
    } else {
        haveScratch = params.m[9] != 0;
        if (haveScratch) {
            if (mode[0] < w)
                return 0;
            if (mode[1] < h)
                return 0;
        }
    }

    char scratchFlag = haveScratch ? 1 : 0;
    char sizeChanged = (params.m[2] != w || params.m[3] != h) ? 1 : 0;

    params.m[9] = (int)(unsigned char)useRefresh;
    params.m[2] = w;
    params.m[3] = h;
    params.m[4] = prevBudget;

    if (*(char*)((char*)this + 0x636) == 0 && budget >= 0 && params.m[0] != budget) {
        params.m[0] = budget;
        void* mm = FUN_0067dd70();
        if (mm != 0) {
            ((void(__thiscall*)(void*))(*(void***)mm)[0x68 / 4])(mm);
            for (int i = 0; i < 0x800; ++i) {
                int* s = &scratch[i * 8];
                s[0] = g_devElems[i].m[1];
                s[2] = g_devElems[i].m[3];
                s[3] = g_devElems[i].m[4];
                s[4] = g_devElems[i].m[5];
                s[5] = g_devElems[i].m[6];
                s[6] = g_devElems[i].m[7];
            }
        }
        FUN_011f7f10();
        g_rwDeviceParams = params;
        FUN_011f8680(&params);
        if (mm != 0) {
            for (int i = 0; i < 0x800; ++i) {
                int* s = &scratch[i * 8];
                g_devElems[i].m[0] = (short)i;
                g_devElems[i].m[1] = s[0];
                g_devElems[i].m[7] = s[6];
                g_devElems[i].m[4] = s[3];
                g_devElems[i].m[5] = s[4];
                g_devElems[i].m[6] = s[5];
                *(unsigned char*)&g_devElems[i].m[2] = 0;
                *((unsigned char*)&g_devElems[i].m[2] + 1) = 0;
            }
            ((void(__thiscall*)(void*))(*(void***)mm)[0x6c / 4])(mm);
        }
    } else {
        int t = FUN_00689590();
        FUN_011f7fd0(&params);
        FUN_00689560(t);
    }

    *(int*)((char*)this + 0x5c) = w;
    *(int*)((char*)this + 0x60) = h;
    *(char*)((char*)this + 0x6c) = (char)useRefresh;
    (void)scratchFlag;

    float ratio;
    bool ok = false;
    if (g_sAppProperties != 0) {
        void* prop;
        ok = ((bool(__thiscall*)(void*, unsigned, void**))(*(void***)g_sAppProperties)[0x24 / 4])
                 (g_sAppProperties, 0x54d9bc3, &prop);
        if (ok && *(short*)((char*)prop + 0x12) == 1) {
            char* p = (char*)prop;
            if ((p[0x10] & 0x30) != 0)
                p = *(char**)p;
            if (*p != 0 && *(char*)((char*)this + 0x6c) != 0 &&
                *(float*)((char*)this + 0x74) > 0.0f) {
                ratio = *(float*)((char*)this + 0x74) /
                        ((float)*(int*)((char*)this + 0x5c) / (float)*(int*)((char*)this + 0x60));
                goto storeRatio;
            }
        }
    }
    ratio = 1.0f;
storeRatio:
    *(float*)((char*)this + 0x78) = ratio;
    {
        int* canvas = FUN_0067dcf0();
        ((void(__thiscall*)(void*, int, int, int))(*(void***)canvas)[0x58 / 4])
            (canvas, (int)useRefresh, params.m[2], params.m[3]);
        int a, b;
        if (!useRefresh) {
            if (scratchFlag == 0 && sizeChanged == 0)
                return 0;
            if (w < mode[0] && h < mode[1]) {
                a = 0x7fffffff; b = 0x7fffffff;
            } else {
                a = 0x28; b = 10;
            }
        } else {
            a = 0; b = 0;
        }
        ((void(__thiscall*)(void*, int, int, int, int, int))(*(void***)canvas)[0x40 / 4])
            (canvas, b, a, w, h, (int)useRefresh);
    }
    return 0;
}
