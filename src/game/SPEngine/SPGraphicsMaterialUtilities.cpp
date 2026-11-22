// src/game/SPEngine/SPGraphicsMaterialUtilities.cpp -- migrated from slice(s) s00713e40, s00712e10 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsMaterialUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cIFileParser.h"
#include "EA/Thread/Mutex.h"
#include "SP/cMaterialManager.h"
#include "SP/cMaterialScriptState.h"

// unnamed retail callees and globals (address in the comment)
extern void** gD3DDevice;                                  // 0x016F89D0 (IDirect3DDevice9*)
extern void* gVertexShaderOut;                             // 0x0162A218
extern void* gPixelShaderOut;                              // 0x0162A21C
#include <new>
#include <string.h>
#include <intrin.h>
#include <math.h>

// ---- items of slice s00712e10 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl GetMaterialManager();                      // 0x0067DD70
struct ID3DXBufferLite {
    virtual void QueryInterface();
    virtual void AddRef();
    virtual void Release();                // +8
    virtual void* GetBufferPointer();      // +0xC
};
extern void** gD3DDevice;                                  // 0x016F89D0 (IDirect3DDevice9*)
extern void* gVertexShaderOut;                             // 0x0162A218
extern void* gPixelShaderOut;                              // 0x0162A21C
const char* __stdcall D3DXGetVertexShaderProfile(void* dev);  // 0x011E1FE0
const char* __stdcall D3DXGetPixelShaderProfile(void* dev);   // 0x011E1FDA
int __stdcall D3DXCompileShader(const char* src, uint32_t len, const void* defines,
                                const void* include, const char* fn, const char* profile,
                                uint32_t flags, ID3DXBufferLite** shader,
                                ID3DXBufferLite** errors, void** constants);   // 0x011E1FD4
static const char* const kVertexShaderSource =
    "float4x4 clipSpaceMatrix : register(c0);float4   frameTime       : register(c4);"
    "struct tVertexIn{    float3 position   : POSITION0;};"
    "struct tVertexOut{    float4 clipPosition  : POSITION;    float4 color         : COLOR0;};"
    "tVertexOut main(tVertexIn vertIn){    tVertexOut vertOut;    "
    "float4 hPos = float4(vertIn.position, 1);    "
    "vertOut.clipPosition = mul(hPos, clipSpaceMatrix);    "
    "vertOut.color = float4(frac(frameTime[0]), 0, 0, 1);    return vertOut;}";
static const char* const kPixelShaderSource =
    "struct tFrag{    float4 color : COLOR0;};tFrag main(tFrag fragIn){    return fragIn;}";
typedef int(__stdcall* CreateShaderFn)(void* dev, const void* code, void** out);
// ---- items of slice s00712e10 end

// ---- items of slice s00713e40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_13ef094[];
extern "C" char g_140cca0[];
extern "C" char g_140cca4[];
extern void*    g_spRenderDevice;                       // 0x16F89D0
extern uint32_t g_spVSShader;                           // 0x162A218
extern uint32_t g_spVSShaderCur;                        // 0x16F6564
extern uint32_t g_spPSShader;                           // 0x162A21C
extern uint32_t g_spPSShaderCur;                        // 0x16F89CC
extern const float* g_spClipMatrix;                     // 0x16F85AC
extern float    g_spFrameTime;                          // 0x162A3B4
extern float    g_spTimeScale;                          // 0x15362C8
extern float    g_spClipMatrixB[16];                    // 0x16F8BE0
int  __cdecl CompileVertexAndPixelShaders_s0071_3e40();            // 0x713CB0
void __cdecl D3DXMatrixMultiplyTranspose(float* out, const float* a, const float* b); // 0x11E1FE6
__int64 __cdecl GameTime();                             // 0x93A3A0
void __cdecl FUN_11f7850();                             // 0x11F7850
void __cdecl FUN_11f6920();                             // 0x11F6920
int  __cdecl FUN_11fa000(int a);                        // 0x11FA000
void __cdecl FUN_11f4440(void* self, int a, int b, int c, int d, int e, int f, int g, int h); // 0x11F4440
void __fastcall FUN_11f44f0(void* self);                // 0x11F44F0
void __fastcall FUN_435480(void* self);                 // 0x435480
struct Adapter20 {
    void* mVt0;      // +0x00
    void* mVt4;      // +0x04
    uint32_t m8, mC, m10, m14;
    void* Init();
};
struct ADI0_713fd0 { virtual void a0(); ~ADI0_713fd0() { (void)this; } };
struct ADI1_713fd0 { virtual void b0(); ~ADI1_713fd0() { (void)this; } };
struct ADSub_713fd0 { void* d[6]; ~ADSub_713fd0(); };   // 0xa23920
struct AdapterBaseView_713fd0 : ADI0_713fd0, ADI1_713fd0 {
    uint32_t m8;
    ADSub_713fd0 mSub;    // +0x0c
    ~AdapterBaseView_713fd0();
};
extern char g_spIndexObj;                               // 0x162A2E8
extern char g_spAdapterObj;                             // 0x162A3A0
extern void* g_spDispatchCallback;                      // 0x162A2FC
bool __cdecl CompileVertexAndPixelShaders();            // 0x713CB0
// ---- items of slice s00713e40 end

// @ 0x00713cb0
bool __cdecl CompileVertexAndPixelShaders()
{
    ID3DXBufferLite* shader;
    ID3DXBufferLite* errors;

    const char* profile = D3DXGetVertexShaderProfile(gD3DDevice);
    int hr = D3DXCompileShader(kVertexShaderSource, (uint32_t)strlen(kVertexShaderSource), 0, 0,
                               "main", profile, 0, &shader, &errors, 0);
    if (errors)
        errors->Release();
    if (hr >= 0) {
        CreateShaderFn create = (CreateShaderFn)(*(void***)gD3DDevice)[0x16c / 4];
        hr = create(gD3DDevice, shader->GetBufferPointer(), &gVertexShaderOut);
        if (shader)
            shader->Release();
        if (hr < 0)
            return false;
    }

    profile = D3DXGetPixelShaderProfile(gD3DDevice);
    hr = D3DXCompileShader(kPixelShaderSource, (uint32_t)strlen(kPixelShaderSource), 0, 0,
                           "main", profile, 0, &shader, &errors, 0);
    if (errors)
        errors->Release();
    if (hr >= 0) {
        CreateShaderFn create = (CreateShaderFn)(*(void***)gD3DDevice)[0x1a8 / 4];
        hr = create(gD3DDevice, shader->GetBufferPointer(), &gPixelShaderOut);
        if (shader)
            shader->Release();
        if (hr < 0)
            return false;
    }
    return true;
}

// @ 0x00713e20
void __cdecl ForwardToMaterialManager(uint32_t a, uint32_t b, uint32_t c)
{
    void* manager = GetMaterialManager();
    void* fn = (*(void***)manager)[0x3c / 4];
    ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t))fn)(manager, a, b, c);
}

// @ 0x00713e40
int __cdecl InvalidMaterialDispatchCallback()
{
    float mat[4][4];
    float* pmat;
    const float* clipA;
    uint32_t vs = g_spVSShader;
    if (g_spVSShaderCur != g_spVSShader) {
        void** vt = *(void***)g_spRenderDevice;
        ((void(__thiscall*)(void*, uint32_t))vt[0x170 / 4])(g_spRenderDevice, g_spVSShader);
        g_spVSShaderCur = vs;
    }
    pmat = mat[0];
    clipA = g_spClipMatrix;

    // 0.5 is a float constant here, unlike the 1.0 which is a double.
    extern const float g_halfConst;                     // 0x1471064
    D3DXMatrixMultiplyTranspose(pmat, clipA, g_spClipMatrixB);
    __int64 t = GameTime();
    float x = (float)t * g_spFrameTime;
    float zero = 0.0f;
    float y = x * g_spTimeScale;
    float sn = (float)sin((double)y + (double)y);
    float s = (float)(((double)sn + 1.0) * g_halfConst);
    void* dev = g_spRenderDevice;
    void** vt = *(void***)dev;
    struct { float m0, m1, m2, m3; } consts;
    consts.m0 = x;
    consts.m2 = zero;
    consts.m3 = zero;
    consts.m1 = s;
    ((void(__thiscall*)(void*, uint32_t, void*, uint32_t))vt[0x178 / 4])(dev, 0, &consts, 5);
    uint32_t ps = g_spPSShader;
    if (g_spPSShaderCur != g_spPSShader) {
        void** vt2 = *(void***)g_spRenderDevice;
        ((void(__thiscall*)(void*, uint32_t))vt2[0x1AC / 4])(g_spRenderDevice, g_spPSShader);
        g_spPSShaderCur = ps;
    }
    FUN_11f7850();
    FUN_11f6920();
    return 1;
}

// @ 0x00713f20
namespace SP {
void RegisterInvalidShader()
{
    if (FUN_11fa000(0x7ffffffe))
        return;
    if (!CompileVertexAndPixelShaders_s0071_3e40())
        return;
    FUN_11f4440(&g_spIndexObj, 0x7ffffffe, 0, 0, 0,
                (int)0xfffe0101, (int)0xfffe0200, (int)0xffff0100, (int)0xffff0200);
    FUN_11f44f0(&g_spIndexObj);
    g_spDispatchCallback = (void*)&InvalidMaterialDispatchCallback;
    FUN_435480(&g_spAdapterObj);
}
}  // namespace SP

// @ 0x00713f90
void* Adapter20::Init()
{
    // The original keeps BOTH stores at +0x04 (a base vtable, then the final one); a plain
    // pair of stores lets MSVC drop the first as dead. The volatile qualifier pins it.
    void* self = this;
    void* v = 0;
    *(void* volatile*)((char*)self + 4) = (void*)g_13ef094;
    *(void**)((char*)self + 8) = v;
    *(void**)self = (void*)g_140cca4;
    *(void**)((char*)self + 4) = (void*)g_140cca0;
    *(void**)((char*)self + 0xc) = v;
    *(void**)((char*)self + 0x10) = v;
    *(void**)((char*)self + 0x14) = v;
    return self;
}

// @ 0x00713fd0
AdapterBaseView_713fd0::~AdapterBaseView_713fd0()
{
}
