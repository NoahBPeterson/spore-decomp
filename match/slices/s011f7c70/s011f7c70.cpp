// slice s011f7c70 -- RenderWare D3D9 graphics device (rwgdrvgraph.cpp and friends).
// Module flags: /O2 /MD /Gy /TP.  See manifest.txt / nonmatching.txt / partial.txt.
//
// D3D9 COM interface calls are __stdcall with `this` as the first stack argument; the
// compiler keeps the vtable in ecx.  Generic callers are written through function-pointer
// casts against the global interface pointer.
#include "types.h"
#include <xmmintrin.h>

typedef unsigned int   u32;
typedef unsigned short u16;

// ---- D3D9 / D3DX entry points ----------------------------------------------
extern "C" __declspec(dllimport) void* __stdcall Direct3DCreate9(u32 sdkVersion);
extern "C" __declspec(dllimport) int   __stdcall D3DXCheckVersion(u32 d3dVersion, u32 d3dxVersion);

// ---- interfaces / globals (addresses from the card) ------------------------
extern void* g_d3d9;            // 0x016f89c8 IDirect3D9*
extern void* g_d3d9dev;         // 0x016f89d0 IDirect3DDevice9*
extern void* g_shader0;         // 0x016f9118
extern void* g_shader1;         // 0x016f911c
extern void* g_shaders[3];      // 0x016f9114
extern int   g_n16f8cf8;        // 0x016f8cf8
extern void* g_window;          // 0x016f658c
extern void* g_rasterA;         // 0x015d0838
extern void* g_rasterB;         // 0x015d083c
extern int   g_adapterCount;    // 0x01712438
extern int   g_state;           // 0x0171243c
extern int   g_params[15];      // 0x01712444
extern int   g_presentW;        // 0x0171244c
extern int   g_presentH;        // 0x01712450
extern int   g_1712470;
extern int   g_1712474;
extern int   g_1712478;
extern int   g_171247c;
extern int   g_171241c, g_1712420, g_1712424, g_1712428;
extern void* g_1712430;         // 0x01712430 optional device-reset callback
extern void* g_1712434;         // 0x01712434 optional device-post-reset callback
extern void* g_171242c;         // 0x0171242c optional pre-reset callback
extern int   g_presentFlags;    // 0x016f8bc4 D3DPRESENT_PARAMETERS::Flags
extern void* g_16f9128;         // 0x016f9128 LARGE_INTEGER performance counter
extern int   g_present[15];     // 0x016f8b9c D3DPRESENT_PARAMETERS
extern void* g_16f6564;         // current vertex-shader descriptor
extern void* g_deviceInfo;      // 0x015d0930
extern char  DAT_0170ee48;
extern char* g_1711ef8;         // 0x01711ef8 current descriptor string
extern char  DAT_01711fd0;      // adapter identifier buffer
extern char  DAT_017121d0;
extern int   DAT_015d0814[9];
extern int   DAT_015d07e0[4];
extern int   DAT_015d07ec[4];

// ---- callees ---------------------------------------------------------------
void __cdecl rwg_D3D9ResetAndRestoreDevice();
void __cdecl FUN_011fb220();
void __cdecl FUN_011f60c0();
void __cdecl FUN_011f5950();
void __cdecl FUN_011f45a0();
void __cdecl FUN_011f5630();
void __cdecl FUN_011f5ee0();
void __cdecl FUN_011f5270();
void __cdecl FUN_011f5b10();
void __cdecl FUN_011fa0b0();
void __cdecl FUN_011f3900();
void __cdecl FUN_011f3990();
void __cdecl FUN_011f0840();     // 0x011f0840 device-init prologue
void __cdecl FUN_011efa70();     // 0x011efa70 teardown helper
void __cdecl FUN_011f5980();     // 0x011f5980 teardown helper
void __cdecl FUN_011f6110();     // 0x011f6110 teardown helper
void __cdecl FUN_011f77d0();     // 0x011f77d0 teardown helper
void __cdecl FUN_011f68c0();     // 0x011f68c0 teardown helper
void __cdecl FUN_011f1d70();     // 0x011f1d70 GlobalState::D3D9Reset
void __cdecl FUN_011f00a0();     // 0x011f00a0 restore helper
void __cdecl FUN_011f59c0();     // 0x011f59c0 restore helper
void __cdecl FUN_011f6270();     // 0x011f6270 restore helper
void __cdecl FUN_011f7800();     // 0x011f7800 restore helper
void __cdecl FUN_011f68f0();     // 0x011f68f0 restore helper
void __cdecl FUN_011f2bb0();     // 0x011f2bb0 start helper
void __cdecl FUN_011f9f90();     // 0x011f9f90 start helper
int  __cdecl FUN_011f5ac0();     // 0x011f5ac0 start helper
int  __cdecl FUN_011f5220();     // 0x011f5220 start helper
int  __cdecl FUN_011f6180();     // 0x011f6180 start helper
int  __cdecl FUN_011f5a40();     // 0x011f5a40 start helper
void __cdecl FUN_011f4630();     // 0x011f4630 start helper
int  __cdecl FUN_011f94a0(int which); // 0x011f94a0 select present parameters

// Raster::Initialize writes `raster` into the first field of its output record.
struct RasterInit {
    void* raster;
    u32   pad04[5];
};
int __cdecl FUN_011efeb0(RasterInit* init, u16 width, u16 height, int a, int b, int c);

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(void* counter);
// FUN_011eff60 is a thiscall with no stack arguments (plain `ret`); VC7.1 cannot spell __thiscall
// in a pointer cast, so it is declared as a member of a receiver stub class.
struct RasterReceiver { void FUN_011eff60(); };
int  __cdecl FUN_011f7d00(int* p);
int  __cdecl FUN_011f7b20(void* s);
int  __cdecl DevCapsManager_GetD3DCAPS9(); // 0x011f8af0
void __cdecl DocMessage_Send(void* a, int b, const char* fmt, ...);

extern "C" __declspec(dllimport) int __stdcall GetVersionExA(void*);

struct OSVERSIONINFOA {
    u32 dwOSVersionInfoSize;
    u32 dwMajorVersion;
    u32 dwMinorVersion;
    u32 dwBuildNumber;
    u32 dwPlatformId;
    char szCSDVersion[128];
};
struct DEVINFO {
    char pad000[0x168];
    u32 major, minor, build, platform;  // +0x168
    u16 sp0, sp1;                       // +0x178
    char csd[0x80];                     // +0x17c
};

#define VTD(p) (*(void***)(p))

// thiscall members live on a stub Device class
struct Device {
    void Reset(int* p);
    void* GetDefaultParameters(int which);   // returns `this` (the D3DPRESENT_PARAMETERS block) in eax
    int  StartInternal(int* p);
};

// ---------------------------------------------------------------------------
// @ 0x011f7fa0
// ---------------------------------------------------------------------------
void __cdecl FUN_011f7fa0(void)
{
    void* d = g_d3d9;
    ((void(__stdcall*)(void*))VTD(d)[2])(d);
    g_d3d9 = 0;
    FUN_011fb220();
    g_state = 0;
}

// ---------------------------------------------------------------------------
// @ 0x011f8270
// ---------------------------------------------------------------------------
void __cdecl FUN_011f8270(int* p)
{
    int* q = p;
    q[0] = g_171241c;
    q[1] = g_1712420;
    q[2] = g_1712424;
    q[3] = g_1712428;
}

// ---------------------------------------------------------------------------
// @ 0x011f8310
// ---------------------------------------------------------------------------
u32 __cdecl FUN_011f8310(int param_1)
{
    void* d = g_d3d9;
    int r = ((int(__stdcall*)(void*, int, int, void*))VTD(d)[5])(d, param_1, 0, &DAT_01711fd0);
    return (u32)((r < 0) - 1) & 0x17121d0;
}

// ---------------------------------------------------------------------------
// @ 0x011f8120
// ---------------------------------------------------------------------------
void __cdecl FUN_011f8120(int param_1)
{
    int* p = *(int**)(param_1 + 0x18);
    int r;
    if (p == 0) {
        void* d = g_d3d9dev;
        r = ((int(__stdcall*)(void*, int, int, int, int))VTD(d)[0x44 / 4])(d, 0, 0, 0, 0);
    } else {
        r = ((int(__stdcall*)(void*, int))VTD(p)[3])(p, 0);
    }
    if (r == (int)0x88760868)
        rwg_D3D9ResetAndRestoreDevice();
    FUN_011f60c0();
    FUN_011f5950();
}

// ---------------------------------------------------------------------------
// @ 0x011f81d0
// ---------------------------------------------------------------------------
void __cdecl FUN_011f81d0(void)
{
    void* d = g_d3d9dev;
    ((void(__stdcall*)(void*))VTD(d)[0xa8 / 4])(d);
    if (g_shader1 != 0) {
        void* s = g_shader1;
        ((void(__stdcall*)(void*))VTD(s)[2])(s);
    }
    g_shader1 = g_shader0;
    if (g_171247c <= 2) {
        void* d2 = g_d3d9dev;
        int r = ((int(__stdcall*)(void*, int, void**))VTD(d2)[0x1d8 / 4])(d2, 8, &g_shader0);
        if (r >= 0) {
            void* s = g_shader0;
            ((void(__stdcall*)(void*, int))VTD(s)[6])(s, 1);
            g_n16f8cf8++;
            return;
        }
    } else {
        g_shader0 = 0;
    }
    g_n16f8cf8++;
}

// ---------------------------------------------------------------------------
// @ 0x011f8160
// ---------------------------------------------------------------------------
int __cdecl FUN_011f8160(void)
{
    u32 u = (u32)g_171247c;
    if (u < 3 && g_shaders[u] != 0) {
        int r;
        do {
            void* s = g_shaders[u];
            r = ((int(__stdcall*)(void*, int, int, int))VTD(s)[0x1c / 4])(s, 0, 0, 1);
        } while (r == 1);
        void* s2 = g_shaders[u];
        ((void(__stdcall*)(void*))VTD(s2)[2])(s2);
        g_shaders[u] = 0;
    }
    void* d = g_d3d9dev;
    int r = ((int(__stdcall*)(void*))VTD(d)[0xa4 / 4])(d);
    return r >= 0;
}

// ---------------------------------------------------------------------------
// @ 0x011f82a0
// ---------------------------------------------------------------------------
int __cdecl FUN_011f82a0(int a, int b, int c, int d, int e)
{
    void* p = g_d3d9;
    int r = ((int(__stdcall*)(void*, int, int, int, int, int, int))VTD(p)[0x28 / 4])(p, a, b, c, 2, 1, e);
    if (r >= 0) {
        r = ((int(__stdcall*)(void*, int, int, int, int, int))VTD(p)[0x30 / 4])(p, a, b, c, d, e);
        if (r >= 0)
            return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x011f8b00  (DevCapsManager::GetNonD3DDeviceInfo)
// ---------------------------------------------------------------------------
void __cdecl FUN_011f8b00(void)
{
    OSVERSIONINFOA info;
    u32* q = (u32*)&info;
    for (int i = 0; i < 0x27; ++i)
        q[i] = 0;
    info.dwOSVersionInfoSize = 0x9c;
    GetVersionExA(&info);
    DEVINFO* d = (DEVINFO*)g_deviceInfo;
    d->major = info.dwMajorVersion;
    d->minor = info.dwMinorVersion;
    d->build = info.dwBuildNumber;
    d->platform = info.dwPlatformId;
    d->sp0 = *(u16*)((char*)&info + 0x9c);
    d->sp1 = *(u16*)((char*)&info + 0x9e);
    char* src = info.szCSDVersion;
    u32* dst = (u32*)((char*)d + 0x17c);
    for (int i = 0x20; i != 0; --i)
        *dst++ = *(u32*)src, src += 4;
}

// ---------------------------------------------------------------------------
// @ 0x011f8340
// ---------------------------------------------------------------------------
void* Device::GetDefaultParameters(int which)
{
    int* p = (int*)this;
    for (int i = 0; i < 15; ++i)
        p[i] = g_params[i];
    switch (which) {
    case 0: p[2] = 0x640; p[3] = 0x4b0; break;
    case 1: p[2] = 0x500; p[3] = 0x400; break;
    case 2: p[2] = 0x400; p[3] = 0x300; break;
    case 3: p[2] = 800;   p[3] = 600;   break;
    case 4: p[2] = 0x280; p[3] = 0x1e0; break;
    case 5: p[2] = 0;     p[3] = 0;     break;
    }
    p[0] = 0;
    p[1] = 1;
    p[4] = 0;
    p[8] = 0;
    p[9] = 0;
    p[11] = 0;
    p[12] = 0;
    p[13] = 0;
    p[14] = 2;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x011f7f10
// ---------------------------------------------------------------------------
void __cdecl FUN_011f7f10(void)
{
    FUN_011f45a0();
    FUN_011f5630();
    FUN_011f5ee0();
    FUN_011f5270();
    FUN_011f5b10();
    FUN_011fa0b0();
    if (g_shader0 != 0) {
        void* s = g_shader0;
        ((void(__stdcall*)(void*))VTD(s)[2])(s);
        g_shader0 = 0;
    }
    if (g_shader1 != 0) {
        void* s = g_shader1;
        ((void(__stdcall*)(void*))VTD(s)[2])(s);
        g_shader1 = 0;
    }
    FUN_011f3900();
    ((RasterReceiver*)g_rasterA)->FUN_011eff60();
    ((RasterReceiver*)g_rasterB)->FUN_011eff60();
    void* d = g_d3d9dev;
    ((void(__stdcall*)(void*))VTD(d)[2])(d);
    g_d3d9dev = 0;
    g_state = 1;
}

// ---------------------------------------------------------------------------
// @ 0x011f7fd0  (Device::Reset)
// ---------------------------------------------------------------------------
void Device::Reset(int* p)
{
    int changed = 0;
    if ((g_presentW != p[2]) || (g_presentH != p[3]))
        changed = 1;
    int local[15];
    for (int i = 0; i < 15; ++i)
        g_params[i] = p[i];
    for (int i = 0; i < 15; ++i)
        local[i] = p[i];
    FUN_011f7d00(local);
    rwg_D3D9ResetAndRestoreDevice();
    if (changed) {
        *(u16*)((char*)g_rasterA + 0xc) = (u16)p[2];
        *(u16*)((char*)g_rasterA + 0xe) = (u16)p[3];
        *(u16*)((char*)g_rasterB + 0xc) = (u16)p[2];
        *(u16*)((char*)g_rasterB + 0xe) = (u16)p[3];
    }
}

// ---------------------------------------------------------------------------
// @ 0x011f8070  (Device::D3D9WindowResize)
// ---------------------------------------------------------------------------
void __cdecl FUN_011f8070(void* hwnd, u16 w, u16 h)
{
    if (g_state != 2)
        return;
    if (hwnd == g_window) {
        if (g_presentW == (int)w && g_presentH == (int)h) {
            void* d = g_d3d9dev;
            int r = ((int(__stdcall*)(void*))VTD(d)[3])(d);
            if (r != (int)0x88760869)
                return;
        }
        g_presentW = w;
        g_presentH = h;
        FUN_011f7d00(g_params);
    }
    rwg_D3D9ResetAndRestoreDevice();
    if (hwnd == g_window) {
        *(u16*)((char*)g_rasterA + 0xc) = w;
        *(u16*)((char*)g_rasterA + 0xe) = h;
        *(u16*)((char*)g_rasterB + 0xc) = w;
        *(u16*)((char*)g_rasterB + 0xe) = h;
    }
}

// ---------------------------------------------------------------------------
// @ 0x011f8400  (Device::D3D9GetMaxSamplerStage)
// ---------------------------------------------------------------------------
int __cdecl FUN_011f8400(u32 fmt)
{
    if (fmt > 0xffff0000u) {
        if (fmt == 0xffff0101 || fmt == 0xffff0102 || fmt == 0xffff0103)
            return 4;
        if (fmt == 0xffff0104)
            return 6;
        if (fmt == 0xffff0200 || fmt == 0xffff0261 || fmt == 0xffff0300)
            return 0x10;
        char* file = "\\Spore\\SporeEP1ML\\Core\\RenderWare\\platform\\src\\graphics\\core\\device\\target\\dx9\\rwgdrvgraph.cpp";
        int line = 0xcca;
        int caps = DevCapsManager_GetD3DCAPS9();
        DocMessage_Send(&file, 0,
            "Unable to identity pixel shader version 0x%x - using MaxTextureBlendStages (%d)",
            fmt, *(int*)(caps + 0x94));
    }
    int caps = DevCapsManager_GetD3DCAPS9();
    return *(int*)(caps + 0x94);
}

// ---------------------------------------------------------------------------
// @ 0x011f8a40
// ---------------------------------------------------------------------------
void __cdecl FUN_011f8a40(int* out, int param_2)
{
    int total = 0;
    for (u32 a = 0; a < (u32)g_adapterCount; ++a) {
        for (u32 f = 0; f < 0x10; f += 4) {
            void* d = g_d3d9;
            int n = ((int(__stdcall*)(void*, int, int))VTD(d)[0x18 / 4])(d, a, DAT_015d07ec[f / 4]);
            total += n;
        }
    }
    out[0] = 0;
    out[2] = 0;
    out[1] = 1;
    out[3] = 1;
    out[4] = 0;
    out[5] = 1;
    out[6] = 0;
    out[7] = 1;
    out[0] = param_2 * 0x44 + total * 0x10;
    out[1] = 1;
}

// ---------------------------------------------------------------------------
// @ 0x011f7d00  (anonymous namespace rwg_SetPresent)
// ---------------------------------------------------------------------------
int __cdecl FUN_011f7d00(int* p)
{
    g_present[0] = p[2];
    g_present[1] = p[3];
    if (g_present[0] == 0)
        g_present[0] = 1;
    if (g_present[1] == 0)
        g_present[1] = 1;
    g_present[2] = p[6];
    g_present[3] = 1;
    g_present[4] = 0;
    g_present[5] = 0;
    g_present[6] = (p[9] == 0) ? 3 : 1;
    g_present[7] = (int)g_window;
    g_present[8] = (p[9] == 0);
    g_present[9] = 1;
    g_present[10] = p[7];
    g_present[11] = (p[7] == 0x46 || p[7] == 0x52 || p[10] == 1) ? 1 : 0;
    g_present[12] = (p[9] != 0) ? p[4] : 0;
    // The HRESULT is both stored as the 14th dword and returned in eax.
    int hr = (-(p[8] != 0) & 0x80000001) + 0x80000000;
    g_present[13] = hr;
    return hr;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// @ 0x011f7de0  (rwg_D3D9ResetAndRestoreDevice)
// ---------------------------------------------------------------------------
// D3D9 device reset/restore.  First drains TestCooperativeLevel until the device
// is no longer in the "device lost" state, then (once) tears down all the cached
// shaders/rasters, resets the device, restores global D3D state and rebuilds the
// two default rasters from the fresh render-target/state blocks.
void __cdecl FUN_011f7de0(void)
{
    int first = 1;
    if (g_171242c != 0)
        ((void(__cdecl*)())g_171242c)();
    for (;;) {
        for (;;) {
            void* d = g_d3d9dev;
            int hr = ((int(__stdcall*)(void*))VTD(d)[3])(d);   // TestCooperativeLevel
            if (hr != (int)0x88760868)
                break;
        }

        if (first) {
            if (g_1712430 != 0)
                ((void(__cdecl*)())g_1712430)();
            if (g_shader0 != 0) {
                void* s = g_shader0;
                ((void(__stdcall*)(void*))VTD(s)[2])(s);
                g_shader0 = 0;
            }
            if (g_shader1 != 0) {
                void* s = g_shader1;
                ((void(__stdcall*)(void*))VTD(s)[2])(s);
                g_shader1 = 0;
            }
            FUN_011f3900();
            FUN_011efa70();
            FUN_011f5980();
            FUN_011f6110();
            FUN_011f77d0();
            FUN_011f68c0();
            ((RasterReceiver*)g_rasterA)->FUN_011eff60();
            ((RasterReceiver*)g_rasterB)->FUN_011eff60();
            first = 0;
        }

        {
            void* d = g_d3d9dev;
            int hr = ((int(__stdcall*)(void*, void*))VTD(d)[0x40 / 4])(d, g_present);
            if (hr == 0)
                break;
        }
    }

    FUN_011f1d70();
    if (g_1712434 != 0)
        ((void(__cdecl*)())g_1712434)();

    {
        void* d = g_d3d9dev;
        void* renderTarget;
        ((int(__stdcall*)(void*, int, void**))VTD(d)[0x98 / 4])(d, 0, &renderTarget);
        *(void**)((char*)g_rasterA + 8) = renderTarget;
    }
    {
        void* d = g_d3d9dev;
        void* stateBlock;
        ((int(__stdcall*)(void*, void**))VTD(d)[0xa0 / 4])(d, &stateBlock);
        *(void**)((char*)g_rasterB + 8) = stateBlock;
    }

    FUN_011f3990();
    FUN_011f00a0();
    FUN_011f59c0();
    FUN_011f6270();
    FUN_011f7800();
    FUN_011f68f0();
}

// ---------------------------------------------------------------------------
// @ 0x011f7c70  (D3D9VertexShaderDescriptor::DefaultLoadAndSelect)
// ---------------------------------------------------------------------------
void __cdecl FUN_011f7c70(void)
{
    char* a = g_1711ef8;
    char* b = &DAT_0170ee48;
    int r;
    for (;;) {
        char ca = *a, cb = *b;
        if (ca != cb) { r = (ca < cb) ? -1 : 1; break; }
        if (ca == 0) { r = 0; break; }
        char ca2 = a[1], cb2 = b[1];
        if (ca2 != cb2) { r = (ca2 < cb2) ? -1 : 1; break; }
        a += 2; b += 2;
        if (ca2 == 0) { r = 0; break; }
    }
    void* sh;
    if (r == 0) {
        *(int*)(g_1711ef8 + 0x24) = g_n16f8cf8;
        sh = *(void**)(g_1711ef8 + 0x20);
    } else {
        sh = (void*)FUN_011f7b20(&DAT_0170ee48);
    }
    if (g_16f6564 != sh) {
        void* d = g_d3d9dev;
        ((void(__stdcall*)(void*, void*))VTD(d)[0x170 / 4])(d, sh);
        g_16f6564 = sh;
    }
}

// ---------------------------------------------------------------------------
// @ 0x011f84b0  (Device::Initialize)
// ---------------------------------------------------------------------------
// Creates the IDirect3D9 object, validates the D3DX version, enumerates adapters
// with a HAL device type (falling back to adapter 0 / REF), records the desktop
// display mode and the device-selection parameters, then sets the MXCSR
// flush-to-zero bit and selects the final present parameters.
int __cdecl FUN_011f84b0(void)
{
    FUN_011f0840();

    void* d3d = ((void*(__stdcall*)(u32))Direct3DCreate9)(0x20);
    g_d3d9 = d3d;
    if (d3d == 0)
        return 0;

    if (D3DXCheckVersion(0x20, 0x1b) == 0) {
        void* d = g_d3d9;
        ((void(__stdcall*)(void*))VTD(d)[2])(d);
        g_d3d9 = 0;
        return 0;
    }

    {
        void* d = g_d3d9;
        g_adapterCount = ((int(__stdcall*)(void*))VTD(d)[0x10 / 4])(d);  // GetAdapterCount
    }

    u32 adapter = 0;
    int mode = 1;
    unsigned char caps[0x130];

    if ((u32)g_adapterCount > 0) {
        for (;;) {
            void* d = g_d3d9;
            int hr = ((int(__stdcall*)(void*, u32, int, void*))VTD(d)[0x38 / 4])(d, adapter, 1, caps);
            if (hr >= 0)
                break;
            ++adapter;
            if (adapter >= (u32)g_adapterCount)
                break;
        }
    }

    if ((u32)g_adapterCount == 0 || adapter >= (u32)g_adapterCount) {
        void* d = g_d3d9;
        if (((int(__stdcall*)(void*, u32, int, void*))VTD(d)[0x38 / 4])(d, 0, 2, caps) < 0) {
            ((void(__stdcall*)(void*))VTD(d)[2])(d);
            g_d3d9 = 0;
            return 0;
        }
        adapter = 0;
        mode = 2;
    }

    {
        void* d = g_d3d9;
        if (((int(__stdcall*)(void*, u32, void*))VTD(d)[0x20 / 4])(d, adapter, &g_171241c) < 0) {
            ((void(__stdcall*)(void*))VTD(d)[2])(d);
            g_d3d9 = 0;
            return 0;
        }
    }

    int selectedFormat = 0;
    for (int i = 0; i < 9; ++i) {
        if (FUN_011f82a0(adapter, mode, g_1712428, g_1712428, DAT_015d0814[i]) != 0) {
            selectedFormat = DAT_015d0814[i];
            goto selected;
        }
    }
    {
        void* d = g_d3d9;
        ((void(__stdcall*)(void*))VTD(d)[2])(d);
        g_d3d9 = 0;
        return 0;
    }

selected:
    g_params[0] = 0;
    g_params[1] = 1;
    g_params[2] = g_171241c;
    g_params[3] = g_1712420;
    g_params[4] = g_1712424;
    g_params[5] = g_1712428;
    g_params[6] = g_1712428;
    g_params[7] = selectedFormat;
    g_params[8] = 0;
    g_params[9] = 0;

    {
        unsigned int mxcsr = _mm_getcsr();
        mxcsr |= 0x8000;
        _mm_setcsr(mxcsr);
    }

    g_params[11] = 0;
    g_params[12] = 0;
    g_params[13] = 0;
    g_params[14] = 2;
    g_state = 1;
    FUN_011f94a0(0);
    return 1;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// @ 0x011f8680  (Device::StartInternal)
// ---------------------------------------------------------------------------
// Points the two default rasters at the built-in camera/zbuffer raster objects,
// builds the present parameters, creates the D3D9 device, initializes both
// rasters, captures the render-target/state-block objects, runs the start-up
// helpers and finally records a performance-counter baseline.
int __cdecl FUN_011f8680(int* p)
{
    g_rasterA = (void*)0x1712480;
    g_rasterB = (void*)0x17124a0;

    FUN_011f7d00(p);

    {
        void* d = g_d3d9;
        unsigned char caps[0x130];
        int hr = ((int(__stdcall*)(void*, int, int, void*))VTD(d)[0x38 / 4])(d, p[0], p[1], caps);
        if (hr < 0)
            return 0;
    }

    int flags = 0;
    if (g_1712478 != 0)
        flags = 4;
    if (g_1712474 != 0) {
        if ((p[14] & 0x10000) != 0)
            flags |= 0x80;
    } else if (g_1712470 == 0 && (p[14] & 0x10000) != 0) {
        if ((p[14] & 0x100000) == 0)
            flags |= 0x40;
        else
            flags |= 0x50;
    } else {
        flags |= 0x20;
    }

    {
        void* d = g_d3d9;
        int hr = ((int(__stdcall*)(void*, int, int, void*, int, void*, void**))VTD(d)[0x40 / 4])
                     (d, p[0], p[1], g_window, flags, g_present, &g_d3d9dev);
        if (hr < 0)
            return 0;
    }

    if (g_1712470 != 0 && g_1712474 != 0) {
        void* d = g_d3d9dev;
        ((int(__stdcall*)(void*, int))VTD(d)[0x134 / 4])(d, 1);
    }

    FUN_011f94a0(0);

    RasterInit cameraInit;
    cameraInit.raster = g_rasterA;
    for (int i = 1; i < 6; ++i)
        cameraInit.pad04[i - 1] = 0;
    if (FUN_011efeb0(&cameraInit, (u16)p[2], (u16)p[3], 0, 1, p[6]) == 0)
        return 0;

    {
        void* d = g_d3d9dev;
        void* renderTarget;
        if (((int(__stdcall*)(void*, int, void**))VTD(d)[0x98 / 4])(d, 0, &renderTarget) < 0)
            return 0;
        *(void**)((char*)g_rasterA + 8) = renderTarget;
    }

    RasterInit zbufferInit;
    zbufferInit.raster = g_rasterB;
    for (int i = 1; i < 6; ++i)
        zbufferInit.pad04[i - 1] = 0;
    if (FUN_011efeb0(&zbufferInit, (u16)p[2], (u16)p[3], 0, 2, g_presentFlags) == 0)
        return 0;

    {
        void* d = g_d3d9dev;
        void* stateBlock;
        if (((int(__stdcall*)(void*, void**))VTD(d)[0xa0 / 4])(d, &stateBlock) < 0)
            return 0;
        *(void**)((char*)g_rasterB + 8) = stateBlock;
    }

    FUN_011f3990();
    FUN_011f2bb0();
    FUN_011f9f90();
    if (FUN_011f5ac0() == 0)
        return 0;
    if (FUN_011f5220() == 0)
        return 0;
    if (FUN_011f6180() == 0)
        return 0;
    if (FUN_011f5a40() == 0)
        return 0;
    FUN_011f4630();

    QueryPerformanceCounter(&g_16f9128);
    g_state = 2;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x011f88c0  (adapter/format enumeration)
// ---------------------------------------------------------------------------
// Fills `param_2` 0x44-byte adapter records at *p, then appends every display
// mode of every supported format as 0x10-byte D3DDISPLAYMODE copies.  Record
// layout: +0x00 accepted device-type count, +0x04..+0x0c the accepted
// D3DDEVTYPE values, +0x10 the number of format entries, then four
// {format,count,modes} entries at +0x14, each 0x0c bytes.
struct D3DDISPLAYMODE {
    u32 width;
    u32 height;
    u32 refreshRate;
    u32 format;
};

void* __cdecl FUN_011f88c0(void** p, int n)
{
    unsigned char* base = (unsigned char*)*p;
    unsigned char* modeData = base + n * 0x44;

    for (int i = 0; i < n * 0x44; ++i)
        base[i] = 0;

    if (g_adapterCount == 0)
        return base;

    int adapter = 0;
    int adapterDwords = 0;
    unsigned char* record = base;

    do {
        int deviceTypeCount = 0;
        for (int t = 0; t < 3; ++t) {
            void* d = g_d3d9;
            unsigned char caps[0x130];
            int hr = ((int(__stdcall*)(void*, int, int, void*))VTD(d)[0x38 / 4])
                         (d, adapter, DAT_015d07e0[t], caps);
            if (hr >= 0) {
                *(u32*)(base + (adapterDwords + deviceTypeCount) * 4 + 4) = DAT_015d07e0[t];
                ++deviceTypeCount;
            }
        }
        *(u32*)(base + adapterDwords * 4) = deviceTypeCount;

        int formatCount = 0;
        u32* entry = (u32*)(record + 0x14);
        for (int f = 0; f < 4; ++f) {
            u32 format = DAT_015d07ec[f];
            void* d = g_d3d9;
            int count = ((int(__stdcall*)(void*, int, u32))VTD(d)[0x18 / 4])(d, adapter, format);
            if (count != 0) {
                entry[0] = format;
                entry[1] = (u32)count;
                entry[2] = (u32)modeData;
                for (int m = 0; m < count; ++m) {
                    void* d2 = g_d3d9;
                    ((int(__stdcall*)(void*, int, u32, int, void*))VTD(d2)[0x1c / 4])
                        (d2, adapter, format, m, modeData);
                    modeData += 0x10;
                }
                ++formatCount;
                entry += 3;
            }
        }
        *(u32*)(record + 0x10) = formatCount;

        record += 0x44;
        ++adapter;
        adapterDwords += 0x11;
    } while (adapter < g_adapterCount);

    return base;
}
// --- equivalence checker address annotations
    void DevCapsManager_GetD3DCAPS9(...); // 0x011f8af0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
