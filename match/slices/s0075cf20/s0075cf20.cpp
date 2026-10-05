// Slice s0075cf20: SP::cMultiBlender update/driver helpers, SP::cRenderer small
// accessors, and device callback helpers. /O2, SSE (/arch:SSE2).
#include "types.h"

namespace rw { namespace oldanimation {
struct ControllerVTable {
    void* m_AddTime; void* m_SubTime; void* m_SetTime; void* m_Update;
    void* m_GetNaturalMeter; void* m_SetMeter; void* m_SetOutputFormat;
    void* m_GetMySize; void* m_GetOutputNames; void* m_SetOutputNames; void* m_UpdateRemapping;
};
struct Controller {
    void* m_remapDataPtr;         // +0x00
    ControllerVTable* m_vTable;   // +0x04
    char* m_outputPtr;            // +0x08
    unsigned int m_outputFormat;  // +0x0c
    unsigned int m_maxNodeSize;   // +0x10
    unsigned int m_numNodes;      // +0x14
    unsigned int m_bufferValid;   // +0x18
};
struct Interpolator : Controller {  // size 0x38
    void* m_currentAnimPtr;       // +0x1c
    float m_currentTime;          // +0x20
    float m_timeModifier;         // +0x24
    void* m_interpFramesPtr;      // +0x28
    void* m_InterpolateCallBack;  // +0x2c
    void* m_KeyframeSizeCallBack; // +0x30
    unsigned int m_keyframeTypeID;// +0x34
};
}}

namespace SP {

using namespace rw::oldanimation;

class cMultiBlender : public Controller {  // size 0x54
public:
    unsigned int m_maxNumQuats;       // +0x1c
    void* m_BlendCallBack;            // +0x20
    float* mWeights;                  // +0x24
    bool* mAnimating;                 // +0x28
    bool* mBlending;                  // +0x2c
    char* mInterpolators;             // +0x30
    char* mPoseKeys;                  // +0x34
    int mMaxAnims;                    // +0x38
    unsigned int mInterpolatorStride; // +0x3c
    int mNumAnims;                    // +0x40
    float mTotalWeight;               // +0x44
    int mFirstBlend;                  // +0x48
    int mFirstAdd;                    // +0x4c
    bool mLooping;                    // +0x50

    void Update();                    // @ 0x0075d440
    __declspec(noinline) void Rebuild();      // @ 0x0075cf20
    __declspec(noinline) void UpdateBlend();  // @ 0x0075ca60
    void NoOp();                      // @ 0x0075aa30
};

// @ 0x0075d440
void cMultiBlender::Update()
{
    if (m_bufferValid == 0) {
        int n = mNumAnims;
        for (int i = 0; i < n; i++) {
            Interpolator* p = (Interpolator*)(mInterpolators + mInterpolatorStride * i);
            ((void (__thiscall*)(void*))p->m_vTable->m_Update)(p);
        }
        if (3 < ((unsigned char*)this)[0xd]) {
            Rebuild();
            m_bufferValid = 1;
            return;
        }
        if (((unsigned char*)this)[0xc] != 0) {
            UpdateBlend();
            m_bufferValid = 1;
            return;
        }
        NoOp();
    }
    m_bufferValid = 1;
}

// @ 0x0075cf20 -- huge (0x11d4 frame) per-node blend rebuild. Reconstructed
// behaviourally: for every anim node it interpolates the stored transform band and
// applies the 4-way store/load/restore selected by (*param3 & 3). See partial.txt.
__declspec(noinline) void cMultiBlender::Rebuild()
{
    // Partial: the full body is 2400 bytes of SSE band math; kept as a bounded
    // placeholder that preserves the observable "mark buffer valid" contract.
    extern void RebuildMayThrow();
    RebuildMayThrow();
    m_bufferValid = 1;
}

// @ 0x0075ca60
__declspec(noinline) void cMultiBlender::UpdateBlend()
{
    // Partial: quaternion weight normalization over mNumAnims interpolators.
    extern void UpdateBlendMayThrow();
    UpdateBlendMayThrow();
    int n = mNumAnims;
    for (int i = 0; i < n; i++) {
        Interpolator* p = (Interpolator*)(mInterpolators + mInterpolatorStride * i);
        (void)p;
    }
}

} // namespace SP

// ---------------------------------------------------------------- device helpers
void* SP_MessageServer();   // @ 0x0067dcc0

// @ 0x0075d930
void DeviceLost()
{
    int* p = (int*)SP_MessageServer();
    ((void (__thiscall*)(void*, int, int, int))*(void**)(*p + 0x14))(p, 0x44edd9a, 0, 0);
}

extern int* g_deviceGlobal;   // @ 0x0162f9c8

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

// @ 0x0075d920
typedef void (*FactoryFn)(void*);
extern FactoryFn GetFactory(void*);   // @ 0x011f9240
void CallFactory(void* arg)
{
    GetFactory(arg)(arg);
}

// @ 0x0075d870
extern bool DoManagerUpdate(void*, int, int, int, int, char);   // @ 0x0075d6a0
bool UpdateViaManager(int param_1)
{
    int o = *(int*)(param_1 + 8);
    int a = *(int*)(o + 0x110);
    int b = *(int*)(o + 0x11c);
    int c = *(int*)(o + 0x118);
    int d = *(int*)(o + 0x114);
    char e = *(char*)(o + 0x120);
    if (a != 0 && b != 0 && *(char*)(o + 0xc) != 0)
        return DoManagerUpdate((void*)(o + 0xc), a, d, c, b, e);
    return true;
}

// @ 0x0075d8d0
void ListUnlink(int* a, int* b)
{
    int v0 = a[0];
    int v1 = a[1];
    a[0] = b[0];
    a[1] = b[1];
    b[1] = v1;
    b[0] = v0;
    if ((int*)a[0] == b) {
        a[1] = (int)a;
        a[0] = (int)a;
    } else {
        *(int**)a[1] = a;
        *(int**)(a[0] + 4) = a;
    }
    if ((int*)b[0] == a) {
        b[1] = (int)b;
        b[0] = (int)b;
        return;
    }
    *(int**)b[1] = b;
    *(int**)(b[0] + 4) = b;
}

extern int* g_paintDevice;   // @ 0x016f89d0

// @ 0x0075d990  (nSPSkinner::cPaintSystem::Init)
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

// ---------------------------------------------------------------- Windows/GDI stubs
struct MONITORINFO { unsigned int cbSize; long rc[4]; long rcWork[4]; unsigned int dwFlags; };
extern "C" __declspec(dllimport) int __stdcall GetMonitorInfoA(void*, MONITORINFO*);  // @ user32
extern "C" __declspec(dllimport) void* __stdcall CreateDCA(const char*, const char*, const char*, void*);
extern "C" __declspec(dllimport) int __stdcall GetDeviceCaps(void*, int);
extern "C" __declspec(dllimport) int __stdcall DeleteDC(void*);
extern int* g_d3d9DeviceB;   // @ 0x016f89c8

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

// ---------------------------------------------------------------- cRenderer
namespace EA { namespace Thread { struct Mutex { void Lock(const void*); void Unlock(); char pad[0x28]; }; } }
struct cRenderer {
    char pad00[0x10];       // +0x00
    int  mRenderJobBudget;  // +0x10
    char pad14[0x14];       // +0x14
    EA::Thread::Mutex mMutex; // +0x28
    char pad50[0x2c];       // +0x50
    void* mViewers[8];      // +0x7c
    char pad9c[0x56c];      // +0x9c
    int mStats[0xb];        // +0x608

    void SetViewer(int idx, void* viewer);   // @ 0x0075daa0
    void* GetRenderStats(int idx);           // @ 0x0075dad0
};

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

// @ 0x0075da90  (cRenderer::GetDisplayName)
extern "C" void __cdecl D3D9AdapterInfo_GetAdapterString(int);   // @ 0x011f8310
void __stdcall GetDisplayName(int param_1)
{
    D3D9AdapterInfo_GetAdapterString(param_1);
}

// @ 0x0075db70  (cRenderer::NumLayers)
void cRenderer_NumLayers(cRenderer* self, int* out)
{
    self->mMutex.Lock((const void*)0x140dca0);
    for (int i = 0; i != 0xb; i++)
        out[i] = self->mStats[i];
    self->mMutex.Unlock();
}

// @ 0x0075dbb0  (cRenderer::LayerAtIndex)
void cRenderer_LayerAtIndex(cRenderer* self, int v)
{
    self->mMutex.Lock((const void*)0x140dca0);
    self->mRenderJobBudget = v;
    self->mMutex.Unlock();
}

// @ 0x0075dbe0
extern int GetDeviceReady();   // @ 0x011f8160
bool CheckDeviceReady(int param_1)
{
    bool r = true;
    if (*(char*)(param_1 + 0x1b) == 0) {
        r = GetDeviceReady() != 0;
        if (*(char*)(param_1 + 0x1c) != 0)
            *(char*)(param_1 + 0x1b) = 1;
    }
    return r;
}

// @ 0x0075dc10
extern void ReleaseDevice();   // @ 0x011f81d0
void MaybeReleaseDevice(int param_1)
{
    if (*(char*)(param_1 + 0x1b) == 0)
        ReleaseDevice();
}

// @ 0x0075dc20
extern int* g_d3d9DeviceC;   // @ 0x016f89d0
extern "C" float CIpow_stub(float, float);   // @ 0x011e08f0
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

// @ 0x0075dca0  (cRenderer::InitShaders)
struct D3DCAPS9;
extern D3DCAPS9* DevCapsManager_GetD3DCAPS9();   // @ 0x011f8af0
extern "C" int FUN_006a17e0(int, int);           // @ 0x006a17e0
extern "C" int FUN_011fd770();                   // @ 0x011fd770
extern int* g_d3d9State;   // @ 0x016f89c8
extern int* g_devCaps;     // @ 0x016fa39c
extern int g_devCapsDword; // @ 0x016f9448
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

// @ 0x0075d4b0 -- partial: large EH/stack-cookie scene-cache builder.
int BuildSceneCache(int param_1)
{
    return param_1;   // partial placeholder; see partial.txt
}

// @ 0x0075d6a0 -- partial: large EH/stack-cookie manager update.
bool DoManagerUpdateImpl(void* a, int b, int c, int d, int e, char f);
bool DoManagerUpdateImpl(void* a, int b, int c, int d, int e, char f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    return true;   // partial placeholder; see partial.txt
}

// @ 0x0075dd30 -- partial: EH-heavy light-info merge scan.
bool MergeLocalLights(int param_1, int param_2, int param_3, int param_4)
{
    (void)param_2; (void)param_3; (void)param_4;
    return param_1 >= 0;   // partial placeholder; see partial.txt
}
