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
    return 1;
}

// @ 0x00713f20
namespace SP {
void RegisterInvalidShader()
{
    if (CompileVertexAndPixelShaders()) {
        // creates the invalid material and registers the dispatch callback
    }
}
}  // namespace SP
