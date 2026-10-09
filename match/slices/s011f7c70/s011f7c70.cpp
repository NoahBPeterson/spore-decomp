// slice s011f7c70 -- RenderWare D3D9 graphics device (rwgdrvgraph.cpp and friends).
// Module flags: /O2 /MD /Gy /TP.  See manifest.txt / nonmatching.txt / partial.txt.
//
// D3D9 COM interface calls are __stdcall with `this` as the first stack argument; the
// compiler keeps the vtable in ecx.  Generic callers are written through function-pointer
// casts against the global interface pointer.
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;

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
extern int   g_present[15];     // 0x016f8b9c D3DPRESENT_PARAMETERS
extern void* g_16f6564;         // current vertex-shader descriptor
extern void* g_deviceInfo;      // 0x015d0930
extern char  DAT_0170ee48;
extern char* g_1711ef8;         // 0x01711ef8 current descriptor string
extern char  DAT_01711fd0;      // adapter identifier buffer
extern char  DAT_017121d0;
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
void __cdecl FUN_011eff60();
void __cdecl FUN_011f7d00(int* p);
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
    void GetDefaultParameters(int which);
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
void Device::GetDefaultParameters(int which)
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
    FUN_011eff60();
    FUN_011eff60();
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
void __cdecl FUN_011f7d00(int* p)
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
    g_present[6] = (int)g_window;
    g_present[7] = (p[9] == 0) ? 1 : 3;
    g_present[8] = (p[9] == 0);
    g_present[9] = 1;
    g_present[10] = p[7];
    g_present[11] = (p[7] == 0x46 || p[7] == 0x52 || p[10] == 1) ? 1 : 0;
    g_present[12] = (p[9] != 0) ? p[4] : 0;
    g_present[13] = (-(p[8] != 0) & 0x80000001) + 0x80000000;
}

// ---------------------------------------------------------------------------
// @ 0x011f7de0  (rwg_D3D9ResetAndRestoreDevice) -- partial, see partial.txt
// ---------------------------------------------------------------------------
void __cdecl FUN_011f7de0(int param_1)
{
    (void)param_1;
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
// @ 0x011f84b0  (Device::Initialize) -- partial, see partial.txt
// ---------------------------------------------------------------------------
int __cdecl FUN_011f84b0(void)
{
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x011f8680  (Device::StartInternal) -- partial, see partial.txt
// ---------------------------------------------------------------------------
int __cdecl FUN_011f8680(int* p)
{
    (void)p;
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x011f88c0  (adapter/format enumeration) -- partial, see partial.txt
// ---------------------------------------------------------------------------
void* __cdecl FUN_011f88c0(void** p, int n)
{
    (void)p; (void)n;
    return 0;
}
// --- equivalence checker address annotations
    void DevCapsManager_GetD3DCAPS9(...); // 0x011f8af0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
