// Slice s00e5dba0 -- SP::sInitGfx (0x00E5DBA0, 1809 bytes): Cell game graphics set-up.
// Cell-game module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
//
// Resets the physics/viewer, then creates the cell stage's render worlds and keeps them as
// reference-counted members of the global cCellGfx (0x016b3c08): the lighting rig, the skybox,
// background, beach, main and foreground effects worlds, the background/beach/main model worlds,
// the three layers ("CellGame-Background", "CellGame-Main") and the per-layer cameras, each sized
// to the application window.  Finally the particle slots are cleared and the skybox effect is
// created.  Member and class names are Claude-coined; layouts come from the retail disassembly.
#include "types.h"

extern "C" void* __cdecl memset(void*, int, unsigned int);

#define VPAD(n) virtual void vpad##n()

struct IRefObj {
    virtual int AddRef();    // +0x00
    virtual int Release();   // +0x04
};

// Intrusive smart pointer: assignment AddRef()s the new object before releasing the old one.
template <class T> struct ARC {
    T* mp;
    ARC& operator=(T* p)
    {
        T* old = mp;
        if (p != old) {
            if (p)
                p->AddRef();
            mp = p;
            if (old)
                old->Release();
        }
        return *this;
    }
    T* operator->() const { return mp; }
    operator T*() const { return mp; }
    void Reset()
    {
        T* old = mp;
        if (old) {
            mp = 0;
            old->Release();
        }
    }
};

// ---------------------------------------------------------------- engine interfaces
struct ILight : IRefObj {
    VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10); VPAD(11);
    virtual void SetEnvironment(uint32_t id);                             // +0x30
};
struct ILightingManager {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5);
    virtual ILight* GetLightRig(uint32_t id, int a, int b);               // +0x18
};
struct IApp {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19);
    virtual int GetWindowWidth();                                         // +0x50
    VPAD(21);
    virtual int GetWindowHeight();                                        // +0x58
};
struct ICamera : IRefObj {
    VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10); VPAD(11);
    VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19); VPAD(20); VPAD(21);
    VPAD(22); VPAD(23); VPAD(24); VPAD(25); VPAD(26); VPAD(27); VPAD(28); VPAD(29); VPAD(30); VPAD(31); VPAD(32);
    virtual void SetViewport(int a, int b);                               // +0x84 (index 33)
};
struct IEffectsWorld : IRefObj {
    VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6);
    virtual void AttachCamera(ICamera* camera);                            // +0x1c
};
struct IEffectsManager {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18);
    virtual IEffectsWorld* CreateWorld(uint32_t id, const char* name);     // +0x4c
};
struct IModelWorld : IRefObj {
    VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10); VPAD(11);
    VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19); VPAD(20); VPAD(21);
    VPAD(22); VPAD(23); VPAD(24); VPAD(25); VPAD(26); VPAD(27); VPAD(28); VPAD(29); VPAD(30); VPAD(31);
    VPAD(32); VPAD(33); VPAD(34); VPAD(35); VPAD(36); VPAD(37); VPAD(38); VPAD(39); VPAD(40); VPAD(41);
    VPAD(42); VPAD(43); VPAD(44); VPAD(45); VPAD(46);
    virtual void SetFarClip(float f);                                      // +0xbc (index 47)
    VPAD(48); VPAD(49); VPAD(50); VPAD(51); VPAD(52); VPAD(53); VPAD(54); VPAD(55); VPAD(56); VPAD(57);
    VPAD(58); VPAD(59); VPAD(60); VPAD(61); VPAD(62); VPAD(63); VPAD(64); VPAD(65); VPAD(66); VPAD(67);
    VPAD(68); VPAD(69); VPAD(70); VPAD(71); VPAD(72); VPAD(73); VPAD(74); VPAD(75); VPAD(76); VPAD(77);
    VPAD(78); VPAD(79);
    virtual void SetLighting(ILight* light, int a, int b);                 // +0x140 (index 80)
};
struct IModelManager {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4);
    virtual IModelWorld* CreateWorld(uint32_t id, const char* name, int flags);   // +0x14
};
struct ILayer : IRefObj {
    VPAD(2); VPAD(3); VPAD(4); VPAD(5);
    virtual void AddEffectsWorld(IEffectsWorld* world);                    // +0x18
    virtual void AddModelWorld(IModelWorld* world, int a, int b, int c, int d);   // +0x1c
};
struct ILayerManager {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7);
    virtual ILayer* GetLayer(const wchar_t* name);                         // +0x20
};

// ---------------------------------------------------------------- globals and helpers
struct cViewerPhysics { void Init(int flag); };                            // 0x007c4dd0 (global 0x016b42b8)
extern cViewerPhysics gEditorPhysicsWorld;                                 // 0x016b42b8

struct EffectSlots {
    uint32_t s[4];
};

struct cCellViewport {
    uint32_t pad[(0x161a0 - 0x168) / 4];
    void Init(int w, int h);
};                         // 0x00b72080 (ret 8)

struct cCellGfx {
    uint32_t pad000[0x4c / 4];
    float mScale;                                // +0x04c
    uint32_t pad050[(0x15c - 0x50) / 4];
    ARC<IRefObj> mpSkyboxEffect;                 // +0x15c
    uint32_t pad160[(0x168 - 0x160) / 4];
    cCellViewport mViewport;                     // +0x168 .. 0x161a0
    ARC<ILight> mpLighting;                      // +0x161a0
    ARC<ICamera> mpBeachCamera;                  // +0x161a4
    ARC<IModelWorld> mpBeachModels;              // +0x161a8
    ARC<IEffectsWorld> mpBeachEffects;           // +0x161ac
    ARC<ICamera> mpSkyCamera;                    // +0x161b0
    ARC<IEffectsWorld> mpSkyEffects;             // +0x161b4
    ARC<ICamera> mpBackCamera;                   // +0x161b8
    ARC<IEffectsWorld> mpBackEffects;            // +0x161bc
    ARC<IModelWorld> mpBackModels;               // +0x161c0
    ARC<ILayer> mpBackLayer;                     // +0x161c4
    ARC<IEffectsWorld> mpMainEffects;            // +0x161c8
    ARC<IModelWorld> mpMainModels;               // +0x161cc
    ARC<ILayer> mpMainLayer;                     // +0x161d0
    ARC<IEffectsWorld> mpFgEffects;              // +0x161d4
    ARC<ICamera> mpFgCamera;                     // +0x161d8
    uint32_t pad161dc[(0x161f0 - 0x161dc) / 4];
    uint32_t mEffectCount;                       // +0x161f0
    EffectSlots mEffectSlots;                    // +0x161f4
    uint8_t mFlag16204;                          // +0x16204
    uint8_t mFlag16205;                          // +0x16205
};
extern cCellGfx* gspCellGfx;                                               // 0x016b3c08

namespace SP {
ILightingManager* __cdecl LightingManager();                               // 0x0067dd90
IApp*             __cdecl App();                                           // 0x0067dd10
IEffectsManager*  __cdecl EffectsManager();                                // 0x0067ddd0
IModelManager*    __cdecl ModelManager();                                  // 0x0067dd80
ILayerManager*    __cdecl LayerManager();                                  // 0x0067cb20
ICamera*          __cdecl GetLayerCamera(int layer);                       // 0x00e82730
void __cdecl CreateEffectSafe(IEffectsWorld* world, uint32_t effectId, int a, ARC<IRefObj>* out);   // 0x00628450

// @ 0x00E5DBA0
void sInitGfx()
{
    gEditorPhysicsWorld.Init(0);
    gspCellGfx->mFlag16204 = 0;
    gspCellGfx->mFlag16205 = 0;
    gspCellGfx->mViewport.Init(200, 256);
    gspCellGfx->mScale = 1.0f;

    gspCellGfx->mpLighting = LightingManager()->GetLightRig(0x4a4d97f, 0, 0);
    gspCellGfx->mpLighting->SetEnvironment(0xa426730b);

    int width = App()->GetWindowWidth();
    int height = App()->GetWindowHeight();

    gspCellGfx->mpSkyEffects = EffectsManager()->CreateWorld(0x1010000, "CellSkyboxEffectsWorld");
    gspCellGfx->mpSkyCamera = GetLayerCamera(2);
    gspCellGfx->mpSkyCamera->SetViewport(height, width);
    gspCellGfx->mpSkyEffects->AttachCamera(gspCellGfx->mpSkyCamera);

    gspCellGfx->mpBackEffects = EffectsManager()->CreateWorld(0x1010011, "CellBackgroundEffectsWorld");
    gspCellGfx->mpBackCamera = GetLayerCamera(1);
    gspCellGfx->mpBackCamera->SetViewport(height, width);
    gspCellGfx->mpBackEffects->AttachCamera(gspCellGfx->mpBackCamera);

    gspCellGfx->mpBackModels = ModelManager()->CreateWorld(0x1010010, "CellBackgroundModelWorld", 0);
    gspCellGfx->mpBackModels->SetLighting(gspCellGfx->mpLighting, 0, 1);
    gspCellGfx->mpBackModels->SetFarClip(8.0f);

    gspCellGfx->mpBackLayer = LayerManager()->GetLayer(L"CellGame-Background");
    gspCellGfx->mpBackLayer->AddModelWorld(gspCellGfx->mpBackModels, 1, 1, 0, 1);
    gspCellGfx->mpBackLayer->AddEffectsWorld(gspCellGfx->mpBackEffects);

    gspCellGfx->mpBeachEffects = EffectsManager()->CreateWorld(0x1010016, "CellBeachEffectsWorld");
    gspCellGfx->mpBeachModels = ModelManager()->CreateWorld(0x1010015, "CellBeachModelWorld", 0);
    gspCellGfx->mpBeachModels->SetLighting(gspCellGfx->mpLighting, 0, 1);
    gspCellGfx->mpBeachCamera = GetLayerCamera(0);
    gspCellGfx->mpBeachCamera->SetViewport(height, width);
    gspCellGfx->mpBeachEffects->AttachCamera(gspCellGfx->mpBeachCamera);

    gspCellGfx->mpMainEffects = EffectsManager()->CreateWorld(0x1010021, "CellEffectsWorld");
    gspCellGfx->mpMainModels = ModelManager()->CreateWorld(0x1010020, "CellModelWorld", 0);
    gspCellGfx->mpMainModels->SetLighting(gspCellGfx->mpLighting, 0, 1);

    gspCellGfx->mpMainLayer = LayerManager()->GetLayer(L"CellGame-Main");
    gspCellGfx->mpMainLayer->AddModelWorld(gspCellGfx->mpMainModels, 1, 1, 0, 1);
    gspCellGfx->mpMainLayer->AddEffectsWorld(gspCellGfx->mpMainEffects);

    gspCellGfx->mpFgEffects = EffectsManager()->CreateWorld(0x1010031, "CellForegroundEffectsWorld");
    gspCellGfx->mpFgCamera = GetLayerCamera(4);
    gspCellGfx->mpFgCamera->SetViewport(height, width);
    gspCellGfx->mpFgEffects->AttachCamera(gspCellGfx->mpFgCamera);

    memset(&gspCellGfx->mEffectSlots, 0, sizeof(EffectSlots));
    gspCellGfx->mEffectCount = 0;

    ARC<IRefObj>* pEffect = &gspCellGfx->mpSkyboxEffect;
    pEffect->Reset();
    CreateEffectSafe(gspCellGfx->mpSkyEffects, 0x5c7a4d0, 0, pEffect);
}

}  // namespace SP
