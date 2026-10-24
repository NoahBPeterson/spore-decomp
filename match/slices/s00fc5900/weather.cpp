// Slice s00fc5900 (part b) -- the two cWeatherManager methods that the slice
// targets (the committed s00fc5900.cpp holds the non-target 0x00fc5f80):
//   00fc5900  ?Init@cWeatherManager@SP@@QAE_NPAVcTerrainSphere@2@@Z  weather init
//   00fc5de0  FUN_00fc5de0  stop / tear down the active weather effects
//
// Retail cWeatherManager layout (subset used here), offsets from the disassembly.
#include <stddef.h>
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

struct Vec4 { float x, y, z, w; };

// interface objects (AddRef +0, Release +4)
struct IRef { virtual void AddRef(); virtual void Release(); };

// bean / effect handle: vtbl[4]=Release, vtbl[8]=set-active, vtbl[0x48]=bind
struct EffectBean {
    virtual void b00();
    virtual void Release();                                          // +0x04
    virtual void Call08(int active);                                 // +0x08
    virtual void b0c(); virtual void b10(); virtual void b14(); virtual void b18(); virtual void b1c();
    virtual void b20(); virtual void b24(); virtual void b28(); virtual void b2c();
    virtual void b30(); virtual void b34(); virtual void b38(); virtual void b3c();
    virtual void b40(); virtual void b44();
    virtual void Call48(int a, void* vec, int b);                    // +0x48
};

// the effects container at manager +0x0c
struct EffectContainer {
    virtual void c00(); virtual void c04();
    virtual bool Lookup(uint32_t key, uint32_t b, void** out);        // +0x08
};

// cWeatherManager (subset)
class cWeatherManager {
public:
    virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c();
    virtual void w10(); virtual void w14(); virtual void w18(); virtual void w1c();
    virtual void w20(); virtual void w24(); virtual void w28(); virtual void w2c();
    virtual void w30(); virtual void w34(); virtual void w38(); virtual void w3c();
    virtual void w40(); virtual void w44(); virtual void w48(); virtual void w4c();
    virtual void w50(); virtual void w54(); virtual void w58(); virtual void w5c();
    virtual void w60(); virtual void w64(); virtual void w68(); virtual void w6c();
    virtual void w70(); virtual void w74(); virtual void w78(); virtual void w7c();
    virtual void w80(); virtual void w84(); virtual void w88(); virtual void w8c();
    virtual void w90(); virtual void w94(); virtual void w98(); virtual void w9c();
    virtual void wa0(); virtual void wa4(); virtual void wa8();
    uint32_t  m04;                                                   // +0x04
    uint32_t  m08;                                                   // +0x08
    EffectContainer* mpContainer;                                    // +0x0c
    uint32_t  m10;                                                   // +0x10
    EffectBean* mpEffect14;                                          // +0x14
    EffectBean* mpEffect18;                                          // +0x18
    EffectBean* mpEffect1c;                                          // +0x1c
    EffectBean* mpEffect20;                                          // +0x20
    EffectBean* mpEffect24;                                          // +0x24
    uint32_t  pad28[(0x38 - 0x28) / 4];
    uint32_t  mKey38;                                                // +0x38
    uint32_t  mKey3c;                                                // +0x3c
    uint32_t  mKey40;                                                // +0x40
    uint32_t  m44;                                                   // +0x44
    uint32_t  mKey48;                                                // +0x48
    uint32_t  mKey4c;                                                // +0x4c
    uint32_t  pad50[(0x68 - 0x50) / 4];
    uint32_t  m68;                                                   // +0x68
    uint32_t  pad6c[(0xac - 0x6c) / 4];
    bool      mbAc;                                                  // +0xac
    bool      mbAd;                                                  // +0xad
    uint8_t   pad_ae[0xc0 - 0xae];
    bool      mbC0;                                                  // +0xc0
    uint8_t   pad_c1[0xd4 - 0xc1];
    void*     mpStateMgr;                                            // +0xd4
    void*     mpTerrainMapSet;                                       // +0xd8
    float     mTemperature;                                          // +0xdc
    void*     mpAtmoPtr;                                             // +0xe0
    void*     mpEffectsHelper0;                                      // +0xe4
    float     mEffectsHelper1;                                       // +0xe8  (also used as an int handle)
    float     mPreviousAtmo;                                         // +0xec
    float     mPreviousTerraformState;                               // +0xf0
    float     mCurrentTerraformState;                                // +0xf4
    uint8_t   pad_f8[0x148 - 0xf8];
    uint32_t  m148;                                                  // +0x148
    uint32_t  m14c;                                                  // +0x14c
    uint32_t  m150;                                                  // +0x150
    uint32_t  m154;                                                  // +0x154
    uint8_t   pad_158[0x164 - 0x158];
    void*     mpJetStreamMidRes;                                     // +0x164
    uint8_t   pad_168[0x188 - 0x168];
    void*     mpLoopBoxAmbientEffect;                                // +0x188

    bool Init(void* terrainSphere);                                  // 0x00fc5900
    void FUN_00fc5de0();                                             // 0x00fc5de0
};

// --- external calls used by Init (0x00fc5900) -------------------------------
// Addresses in comments are the original VAs.

// Simple ref-counted object whose first two vtable slots are AddRef/Release
// for the App/ModelManager families (Release = slot 1 for the +0x14..0x24
// family and slot 2 for the container family).
struct RefObj { virtual void AddRef(); virtual void Release(); };
struct MapObject;

// the cTerrainMapSet family: AddRef = slot 2 (+0x08), Release = slot 3 (+0x0c),
// FetchEffectsWorld = slot 19 (+0x4c), RegisterMap = slot 34 (+0x88).
struct TerrainMapSet {
    virtual void t00(); virtual void t04();
    virtual void AddRef();                                   // +0x08
    virtual void Release();                                  // +0x0c
    virtual void t10(); virtual void t14(); virtual void t18(); virtual void t1c();
    virtual void t20(); virtual void t24(); virtual void t28(); virtual void t2c();
    virtual void t30(); virtual void t34(); virtual void t38(); virtual void t3c();
    virtual void t40(); virtual void t44(); virtual void t48();
    virtual void* FetchEffectsWorld(int id, int a);          // +0x4c
    virtual void t50(); virtual void t54(); virtual void t58(); virtual void t5c();
    virtual void t60(); virtual void t64(); virtual void t68(); virtual void t6c();
    virtual void t70(); virtual void t74(); virtual void t78(); virtual void t7c();
    virtual void t80(); virtual void t84();
    virtual void RegisterMap(float lo, float hi, MapObject* map); // +0x88
};

struct MapObject {                     // the 0x38-byte map object (cJetStreamMap)
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    void SetValuesPressure(float a, float b, float c);               // 0x00fc3150
    void SetValues(float a, float b, float c);                       // 0x00fc3000
    float field0c, field10, field14, field18, field1c, field20;
    uint32_t f28, f2c, f30, f34;
};

struct AppObj { virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0c();
                virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1c();
                virtual void a20(); virtual void a24(); virtual void a28(); virtual void a2c();
                virtual void a30(); virtual void a34(); virtual void a38(); virtual void a3c();
                virtual void a40(); virtual void a44(); virtual void a48(); virtual void a4c();
                virtual void a50(); virtual void a54(); virtual float a58();
                uint32_t f5c, f60, f64;
                virtual void a68(); virtual void a6c(); virtual void a70(); virtual void a74();
                virtual void a78(); virtual void a7c(); virtual void a80(); virtual void a84();
                virtual void a88(); };

struct ModelMgr { virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
                  virtual void m10(); virtual void* m14(int id, int a, int b);
                  virtual void m18(); virtual void* m1c(int id); };

struct PropMgr { virtual void p00(); virtual void p04(); virtual void p08(); virtual void p0c();
                 virtual void p10(); virtual void p14(); virtual void p18(); virtual void p1c();
                 virtual void p20(); virtual void p24(); virtual void p28();
                 virtual bool p2c(uint32_t a, uint32_t b, void** out); };

struct MsgServer { virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
                   virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
                   virtual bool s20(void* handler, int id); };

struct CWMHelper {                                   // the +0xe4 helper object
    virtual void h00(); virtual void h04(); virtual void h08();
    virtual float h0c();                             // water level
    virtual float h10();                             // previous temp
};

// free externals, called with the original argument order
extern void* EffectsManager();                                       // 0x67ddd0
extern AppObj* App();                                                // 0x67dd10
extern void* CheatManager();                                         // 0x67de20
extern bool  PropListGetDescription(void* list, uint32_t id);        // 0x6a25a0
extern void  SetKeywordName(int idx, const char* name);              // 0xaa2fd0
extern void  RegKeywordFunc(int idx, void* fn);                      // 0xaa7fa0
extern void  SetCloudKeyword(int idx, const char* name);             // 0xf52b70
extern void  SetCloudGlobal(int idx, void* fn);                      // 0xf58230
extern ModelMgr* ModelManager();                                     // 0x67dd80
extern PropMgr*  PropertyManager();                                  // 0x67de30
extern MapObject* AllocMap(int size, const char* name, int a, int b, int c, int d); // 0xf473a0
extern float FUN_00fb8a00(CWMHelper* self);                          // 0x00fb8a00
extern float QuadOneMinusSplit(CWMHelper* self);                     // 0x00fb7b90
extern float FUN_00fd9400(CWMHelper* self);                          // 0x00fd9400
extern void  UpdateProperties0xfc31f0(void* self);                   // 0x00fc31f0
extern void  FUN_00fc3f30(void* self);                               // 0x00fc3f30
extern void  MapInit0xf8eed0(void* self);                            // 0x00f8eed0
extern void  FUN_00f92280(int a);                                    // 0x00f92280
extern void  FUN_00fc5480();                                         // 0x00fc5480
extern MsgServer* MessageServer();                                   // 0x67dcc0

extern void*   s_pAppProperties;                                     // 0x15fd918
extern float   s_fMapLo;                                             // 0x1440738
extern float   s_fMapHi;                                             // 0x13ec5b4
extern float   s_fGlobal0, s_fGlobal1, s_fGlobal2, s_fGlobal3, s_fGlobal4, s_fGlobal5;
extern void*   s_ApVtbl;                                             // 0x13ef094

// @ 0x00fc5900
bool cWeatherManager::Init(void* terrainSphere)
{
    if (mbAd != 0)
        return false;

    mbAd = 1;

    // 1. terrain map set (ref-counted swap: AddRef new, Release old)
    TerrainMapSet* pNew = (TerrainMapSet*)EffectsManager();
    TerrainMapSet* pOld = (TerrainMapSet*)mpTerrainMapSet;
    if (pNew != pOld) {
        if (pNew != 0)
            pNew->AddRef();
        mpTerrainMapSet = pNew;
        if (pOld != 0)
            pOld->Release();
    }

    // 2. temperature from App, plus two property ids
    mTemperature = App()->a58();
    m148 = 0x599ec0ab;
    m14c = 0;

    // 3. cheat keywords
    CheatManager();
    if (!PropListGetDescription(s_pAppProperties, 0xd8349603)) {
        SetKeywordName(6, "writeForce");
        RegKeywordFunc(6, (void*)0x00fc4eb0);
    }
    if (!PropListGetDescription(s_pAppProperties, 0xc8cf2af5)) {
        SetCloudKeyword(3, "coriolis");
        SetCloudGlobal(3, (void*)0x00fc5480);
    }

    // 4. atmosphere source: pointer + two cached scalars
    mpAtmoPtr = terrainSphere;
    CWMHelper* helper = (CWMHelper*)terrainSphere;
    mpEffectsHelper0 = (void*)(int)helper->h10();
    mEffectsHelper1 = helper->h0c();

    // 5. model manager -> state manager (retry with a different factory call)
    ModelMgr* mm = ModelManager();
    RefObj* pState = (RefObj*)mm->m1c(0x611c912);
    if (pState != (RefObj*)mpStateMgr) {
        if (pState != 0)
            pState->AddRef();
        mpStateMgr = pState;
        if (pState != 0)
            pState->Release();
    }
    if (mpStateMgr == 0) {
        mm = ModelManager();
        pState = (RefObj*)mm->m14(0x611c912, 0, 0);
        if (pState != (RefObj*)mpStateMgr) {
            if (pState != 0)
                pState->AddRef();
            mpStateMgr = pState;
            if (pState != 0)
                pState->Release();
        }
    }
    ((void(*)(int))((void**)*(void**)mpStateMgr)[0x134 / 4])(1);

    // 6. re-acquire the loop-box ambient effect via the property manager
    PropMgr* pm = PropertyManager();
    RefObj* pLoop = (RefObj*)mpLoopBoxAmbientEffect;
    if (pLoop != 0) {
        mpLoopBoxAmbientEffect = 0;
        pLoop->Release();
    }
    if (pm->p2c(0x12e95823, 0x243ad2b, &mpLoopBoxAmbientEffect))
        UpdateProperties0xfc31f0(this);

    // 7. jet stream map (0x38 bytes) + pressure values
    MapObject* pMap = AllocMap(0x38, "Terrain/WeatherManager/cJetStreamMap", 0, 0, 0, 0);
    if (pMap != 0) {
        pMap->field0c = s_fMapLo; pMap->field10 = s_fMapLo; pMap->field14 = s_fMapLo;
        pMap->field18 = s_fMapHi; pMap->field1c = s_fMapHi; pMap->field20 = s_fMapHi;
        pMap->f28 = 0; pMap->f2c = 0; pMap->f30 = 0; pMap->f34 = 0;
    }
    pMap->SetValuesPressure(mEffectsHelper1, s_fGlobal0, s_fGlobal1);
    ((TerrainMapSet*)mpTerrainMapSet)->RegisterMap(s_fGlobal0, s_fGlobal1, pMap);

    // 8. pressure map (same layout, SetValues)
    pMap = AllocMap(0x38, "Terrain/WeatherManager/cPressureMap", 0, 0, 0, 0);
    if (pMap != 0) {
        pMap->field0c = s_fMapLo; pMap->field10 = s_fMapLo; pMap->field14 = s_fMapLo;
        pMap->field18 = s_fMapHi; pMap->field1c = s_fMapHi; pMap->field20 = s_fMapHi;
        pMap->f28 = 0; pMap->f2c = 0; pMap->f30 = 0; pMap->f34 = 0;
    }
    pMap->SetValues(mEffectsHelper1, s_fGlobal2, s_fGlobal3);
    ((TerrainMapSet*)mpTerrainMapSet)->RegisterMap(s_fGlobal2, s_fGlobal3, pMap);

    // 9. cloud emit map (same layout, SetValues)
    pMap = AllocMap(0x38, "Terrain/WeatherManager/cCloudEmitMap", 0, 0, 0, 0);
    if (pMap != 0) {
        pMap->field0c = s_fMapLo; pMap->field10 = s_fMapLo; pMap->field14 = s_fMapLo;
        pMap->field18 = s_fMapHi; pMap->field1c = s_fMapHi; pMap->field20 = s_fMapHi;
        pMap->f28 = 0; pMap->f2c = 0; pMap->f30 = 0; pMap->f34 = 0;
    }
    pMap->SetValues(mEffectsHelper1, s_fGlobal4, s_fGlobal5);
    ((TerrainMapSet*)mpTerrainMapSet)->RegisterMap(s_fGlobal4, s_fGlobal5, pMap);

    // 10. helper scalars -> previous atmo / terraform states
    mPreviousAtmo = FUN_00fb8a00((CWMHelper*)mpEffectsHelper0);
    mPreviousTerraformState = (int)QuadOneMinusSplit((CWMHelper*)mpEffectsHelper0);
    mCurrentTerraformState = (int)FUN_00fd9400((CWMHelper*)mpEffectsHelper0);

    // 11. effects world swap
    RefObj* pWorld = (RefObj*)((TerrainMapSet*)mpTerrainMapSet)->FetchEffectsWorld(0x3618bef, 0);
    RefObj* pOldWorld = (RefObj*)mpContainer;
    if (pWorld != pOldWorld) {
        if (pWorld != 0)
            pWorld->AddRef();
        mpContainer = (EffectContainer*)pWorld;
        if (pOldWorld != 0)
            pOldWorld->Release();
    }

    // 12. jet-stream mid-res map (0x24 bytes) -> +0x164
    RefObj* pMidRes = (RefObj*)AllocMap(0x24, "Terrain/WeatherManager/mJetStreamMidRes", 0, 0, 0, 0);
    if (pMidRes != 0) {
        MapInit0xf8eed0(pMidRes);
    }
    RefObj* pOldMid = (RefObj*)mpJetStreamMidRes;
    if (pMidRes != pOldMid) {
        if (pMidRes != 0)
            ((int*)pMidRes)[1] += 1;                   // inline refcount increment
        mpJetStreamMidRes = pMidRes;
        if (pOldMid != 0) {
            int c = ((int*)pOldMid)[1] - 1;
            ((int*)pOldMid)[1] = c;
            if (c == 0) {
                ((int*)pOldMid)[1] = 1;
                ((void(*)(int))((void**)*(void**)pOldMid)[0])(1);
            }
        }
    }

    // 13. loop-box warm ambient id + message-server subscription + finish
    FUN_00f92280(0x40);
    m68 = 0x39faa0f;
    MessageServer()->s20(&m08, 0xf62def);
    FUN_00fc3f30(this);

    return true;
}

// @ 0x00fc5de0
void cWeatherManager::FUN_00fc5de0()
{
    mbAc = 1;
    if (!mbAd || !mbC0)
        return;

    // +0x14 : key 0x38
    EffectContainer* pc = mpContainer;
    if (mKey38 != 0) {
        EffectBean* old = mpEffect14;
        if (old != 0) { mpEffect14 = 0; old->Release(); }
        if (pc->Lookup(mKey38, 0, (void**)&mpEffect14)) {
            mpEffect14->Call48(1, &m148, 1);
            mpEffect14->Call08(0);
        }
    }
    // +0x18 : key 0x3c
    if (mKey3c != 0) {
        EffectBean* old = mpEffect18;
        if (old != 0) { mpEffect18 = 0; old->Release(); }
        if (pc->Lookup(mKey3c, 0, (void**)&mpEffect18)) {
            mpEffect18->Call48(1, &m148, 1);
            mpEffect18->Call08(0);
        }
    }
    // +0x1c : key 0x40
    if (mKey40 != 0) {
        EffectBean* old = mpEffect1c;
        if (old != 0) { mpEffect1c = 0; old->Release(); }
        if (pc->Lookup(mKey40, 0, (void**)&mpEffect1c)) {
            mpEffect1c->Call08(0);
        }
    }
    // +0x20 : key 0x48
    if (mKey48 != 0) {
        EffectBean* old = mpEffect20;
        if (old != 0) { mpEffect20 = 0; old->Release(); }
        if (pc->Lookup(mKey48, 0, (void**)&mpEffect20)) {
            mpEffect20->Call08(0);
        }
    }
    // +0x24 : key 0x4c
    if (mKey4c != 0) {
        EffectBean* old = mpEffect24;
        if (old != 0) { mpEffect24 = 0; old->Release(); }
        if (pc->Lookup(mKey4c, 0, (void**)&mpEffect24)) {
            mpEffect24->Call08(0);
        }
    }
}
