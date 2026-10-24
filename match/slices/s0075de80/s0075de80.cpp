// Slice s0075de80: SP::cRenderer layer/info accessors, render settings, and related
// engine helpers. /O2, SSE (/arch:SSE2).  Functions 0075e090/130/1e0/290 carry MSVC
// EH frames around the mutex; the reconstructions keep the behavior but not the frame.
#include "types.h"

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

// ---------------------------------------------------------------- remaining (partial)
// @ 0x0075e4f0
int InitRenderSubsystem()
{
    return 1;       // partial placeholder
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
// @ 0x0075ee10
void* InitRenderNode(void* p, int a, int b)
{
    (void)a; (void)b; return p;   // partial placeholder
}
