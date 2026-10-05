// Slice s0075de80: SP::cRenderer layer/info accessors, render settings, and related
// engine helpers. /O2, SSE (/arch:SSE2).  Functions 0075e090/130/1e0/290 carry MSVC
// EH frames around the mutex; the reconstructions keep the behavior but not the frame.
#include "types.h"

namespace EA { namespace Thread {
struct Mutex { void Lock(const void*); void Unlock(); char pad[0x28]; };
}}

struct cRenderer {
    char pad00[0x28];              // +0x00
    EA::Thread::Mutex mMutex;      // +0x28
    char pad50[0x3c];              // +0x50
    // layers: begin pointer at +0x8c, end pointer at +0x90 (stride 0x14)
    int NumLayers();               // @ 0x0075e330
    void* LayerInfoAt(int idx);    // @ 0x0075e370
    void* LayerInfoAtIndex(int i); // @ 0x0075e3b0
    void* Layer(unsigned id);      // @ 0x0075e090
    unsigned SetInfoFlags(unsigned id, unsigned f);   // @ 0x0075e130
    unsigned ClearInfoFlags(unsigned id, unsigned f); // @ 0x0075e1e0
    unsigned GetInfoFlags(unsigned id);               // @ 0x0075e290
    void SubRender(int a, int lo, int hi, void* extra, char flag, unsigned orbits); // @ 0x0075dff0
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
    if (extra == 0)
        extra = (char*)this + 0x33c;
    unsigned skip = flag ? 0x10000u : 0u;
    char* p = LayerBegin(this);
    char* e = LayerEnd(this);
    if (p != e) {
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
        } while (p != e);
    }
}

// ---------------------------------------------------------------- render settings
extern int* g_sAppProperties;   // @ 0x015fd918
extern float* Property_GetFloat();   // @ 0x0041ea70
extern bool  Property_GetBool();     // @ 0x0041e920
extern float ScreenAspectRatio(int); // @ 0x0075d9e0

// @ 0x0075de80
void RenderSettings(cRenderer* self, char useProps)
{
    int* props = g_sAppProperties;
    if (useProps) {
        if (props != 0) {
            void* prop = 0;
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
        void* prop = 0;
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
void ResizeFromCanvas(int param_1)
{
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

// ---------------------------------------------------------------- remaining (partial)
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
