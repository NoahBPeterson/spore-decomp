// src/game/SPEngine/SPGraphicsRenderer.cpp -- migrated from slice(s) s0075ee90, s0075de80, s0075cf20 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsRenderer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cRenderer.h"

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
void* SP_MessageServer();   // @ 0x0067dcc0
extern int* g_deviceGlobal;   // @ 0x0162f9c8
extern int* g_paintDevice;   // @ 0x016f89d0
struct MONITORINFO { unsigned int cbSize; long rc[4]; long rcWork[4]; unsigned int dwFlags; };
extern "C" __declspec(dllimport) int __stdcall GetMonitorInfoA(void*, MONITORINFO*);  // @ user32
extern "C" __declspec(dllimport) void* __stdcall CreateDCA(const char*, const char*, const char*, void*);
extern "C" __declspec(dllimport) int __stdcall GetDeviceCaps(void*, int);
extern "C" __declspec(dllimport) int __stdcall DeleteDC(void*);
extern int* g_d3d9DeviceB;   // @ 0x016f89c8
namespace EA {
namespace Thread {
 struct Mutex_s0075_cf20 { void Lock(const void*); void Unlock(); char pad[0x28]; }; 
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
extern "C" void __cdecl D3D9AdapterInfo_GetAdapterString(int);   // @ 0x011f8310
extern int GetDeviceReady();   // @ 0x011f8160
struct DevLatch {
    bool CheckDeviceReady();
    void MaybeReleaseDevice();
};
extern int* g_d3d9DeviceC;   // @ 0x016f89d0
extern "C" float CIpow_stub(float, float);   // @ 0x011e08f0
struct D3DCAPS9;
extern D3DCAPS9* DevCapsManager_GetD3DCAPS9();   // @ 0x011f8af0
extern "C" int FUN_006a17e0(int, int);           // @ 0x006a17e0
extern "C" int FUN_011fd770();                   // @ 0x011fd770
extern int* g_d3d9State;   // @ 0x016f89c8
extern int* g_devCaps;     // @ 0x016fa39c
extern int g_devCapsDword; // @ 0x016f9448
// ---- items of slice s0075cf20 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" __declspec(dllimport) int __stdcall GetMonitorInfoA(void*, MONITORINFO*);  // @ user32
extern void ReleaseDevice();   // @ 0x011f81d0
extern D3DCAPS9* DevCapsManager_GetD3DCAPS9();   // @ 0x011f8af0

// ---- items of slice s0075de80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int* g_sAppProperties;   // @ 0x015fd918
extern float* Property_GetFloat();   // @ 0x0041ea70
extern bool  Property_GetBool();     // @ 0x0041e920
extern float ScreenAspectRatio(int); // @ 0x0075d9e0
namespace EA {
namespace Thread {
struct Mutex_s0075_de80 { void Lock(const void*); void Unlock(); char pad[0x28]; };
}
}
struct cRenderer_s0075_de80 {
    char pad00[0x28];              // +0x00
    EA::Thread::Mutex_s0075_de80 mMutex;      // +0x28
    char pad50[0x3c];              // +0x50
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
    bool RemovePostRenderJob(float id);  // 0x0075f8a0 (cRenderer::RemovePostRenderJob)
    bool RemovePreRenderJob(float id);  // 0x0075f900 (cRenderer::RemovePreRenderJob)
};
struct RenderJob {
    RenderJob* next;   // +0x00
    RenderJob* prev;   // +0x04
    RNode*     obj;    // +0x08
    int        pad;    // +0x0c
    float      id;     // +0x10
};
// ---- items of slice s0075ee90 end

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


// @ 0x0075de80
void cRenderer_s0075_de80::RenderSettings(char useProps)
{
    cRenderer_s0075_de80* self = this;
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


// @ 0x0075e370
void* cRenderer_s0075_de80::LayerInfoAt(int idx)
{
    mMutex.Lock((const void*)0x140dca0);
    void* r = *(void**)(LayerBegin(this) + idx * 0x14);
    mMutex.Unlock();
    return r;
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

// @ 0x0075f8a0
bool cRenderer_s0075_ee90::RemovePostRenderJob(float id)
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
    n->prev->next = n->next;
    n->next->prev = n->prev;
    if (n->obj != 0)
        ((void (__thiscall*)(void*))*(void**)(*(int*)n->obj + 4))(n->obj);
    EASTL_deallocate(n);
    return true;
}

// @ 0x0075f900
bool cRenderer_s0075_ee90::RemovePreRenderJob(float id)
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
    n->prev->next = n->next;
    n->next->prev = n->prev;
    if (n->obj != 0)
        ((void (__thiscall*)(void*))*(void**)(*(int*)n->obj + 4))(n->obj);
    EASTL_deallocate(n);
    return true;
}
