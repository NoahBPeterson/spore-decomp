// SP::cSPSpaceGfx::InitForGame (2233 bytes)
//
// One-time setup of the space-game graphics: loads the space property list, initialises the
// three editor physics worlds, creates the effects worlds / renderers from the effects manager
// (trail, money, Ptolemaic, solar background, galaxy, ...), spawns the effect handles they own
// (comets, background dust, sky box, galaxy layers, travel line, ...), and reads the
// travel-line colour/size properties.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the AutoRefCount locals have no EH frame).
// Field offsets are the retail ones read from the disassembly (the 2008 PDB layout agrees up to
// +0xb4 and then shifts by 0x10).  Several PDB member types are wrong in retail (e.g. +0xac is an
// effects world, not an effect), so the types here follow the vtable slots the code uses.
#include "types.h"

#define PV(n) virtual void _v##n();

struct Eff {                              // visual effect handle
  virtual int AddRef();                   // 0x00
  virtual int Release();                  // 0x04
  virtual bool Play(int n);               // 0x08
};

struct World {                            // effects world / renderer / planet-like owners
  virtual int AddRef();                   // 0x00
  virtual int Release();                  // 0x04
  virtual bool Create(uint32_t id, int flags, Eff** out);   // 0x08: spawn effect `id` into *out
  virtual void SetState(int n);           // 0x0c
  PV(4) PV(5) PV(6)
  virtual void Attach(World* other);      // 0x1c
  PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
  PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
  virtual void SetMode(int n);            // 0x78
  PV(31) PV(32)
  virtual void SetView(int a, int b);     // 0x84
};

namespace EA {
template <class T> class AutoRefCount {
public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  AutoRefCount& operator=(T* p)
  {
    if (p != mpObject) {
      T* const pTemp = mpObject;
      if (p)
        p->AddRef();
      mpObject = p;
      if (pTemp)
        pTemp->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
  T** AsPPTypeParam()
  {
    if (mpObject) {
      T* const p = mpObject;
      mpObject = 0;
      p->Release();
    }
    return &mpObject;
  }
};
}  // namespace EA
using EA::AutoRefCount;

struct Vec3 {
  float x, y, z;
  Vec3() {}
  Vec3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};

struct Property {
  char pad[0x12];
  int16_t type;                           // +0x12
  uint32_t* GetUInt();                    // 0x0041ea00
};
struct PropertyList {
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, Property** out);   // 0x24
};
struct PropertyManagerT {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void GetPropertyList(uint32_t group, uint32_t id, PropertyList** out);   // 0x2c
};
struct EffectsManagerT {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18)
  virtual World* Create(uint32_t id, int flags);           // 0x4c
};
struct AppT {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
  virtual void* GetViewA();               // 0x50
  PV(21)
  virtual void* GetViewB();               // 0x58
};
struct PhysWorld {
  void Init(bool b);                      // 0x007c4dd0 cSPEditorPhysicsWorld::Init
};

PropertyManagerT* PropertyManager();      // 0x0067de30
EffectsManagerT* EffectsManager();        // 0x0067ddd0
AppT* App();                              // 0x0067dd10
World* NewWorld();                        // 0x006eea10
void ModelManager();                      // 0x0067dd80 (returns the manager; only the tail call matters here)
void GetPropertyAsVector3(PropertyList* props, uint32_t id, Vec3* out);   // 0x006a1110

extern PhysWorld g_PhysWorldA;            // 0x015b7844
extern PhysWorld g_PhysWorldB;            // 0x015b79b8
extern PhysWorld g_PhysWorldC;            // 0x015b7b2c
extern float g_SpaceCullNear;             // 0x015b7ca0
extern float g_SpaceCullFar;              // 0x015b7ca4
extern float g_SpaceFov;                  // 0x015b7ca8

class cSPSpaceGfx {
public:
  void InitForGame();                     // 0x01035900
  void InitSub();                         // 0x010346e0

  char pad0[0x1c];
  AutoRefCount<Eff> mGalaxyCrossfadeEffect;     // +0x1c
  AutoRefCount<Eff> mGalaxyEffect;              // +0x20
  AutoRefCount<Eff> mGalaxyScreenEffect;        // +0x24
  AutoRefCount<Eff> mGalaxyAmbienceEffect;      // +0x28
  AutoRefCount<Eff> mGalaxyBackgroundGalaxies;  // +0x2c
  AutoRefCount<Eff> mTraveLineEffect;           // +0x30
  AutoRefCount<Eff> mSporepediaPlotPathEffect;  // +0x34
  void* mTravelLineStar;                        // +0x38
  char pad3c[0x5c - 0x3c];
  int mPlanetScreenEffect;                      // +0x5c
  AutoRefCount<Eff> mLavaPlanetScreenEffect;    // +0x60
  AutoRefCount<Eff> mSkyboxEffect;              // +0x64
  AutoRefCount<Eff> mSolarScreenEffect;         // +0x68
  AutoRefCount<Eff> mSolarClouds;               // +0x6c
  AutoRefCount<Eff> mSolarLoopbox;              // +0x70
  AutoRefCount<Eff> mSolarBackgroundEffect;     // +0x74
  AutoRefCount<Eff> mSolarBackgroundDustEffect; // +0x78
  AutoRefCount<Eff> mPlanetBackgroundEffect;    // +0x7c
  AutoRefCount<Eff> mPlanetBackgroundDustEffect;// +0x80
  AutoRefCount<Eff> mSolarComets;               // +0x84
  AutoRefCount<Eff> mpMeaningOfLifeEffect;      // +0x88
  char pad8c[0x94 - 0x8c];
  AutoRefCount<World> mTrailEffectsWorld;       // +0x94
  AutoRefCount<World> mPtolemaicEffectsWorld;   // +0x98
  AutoRefCount<World> mPtolemaicEffectsRenderer;// +0x9c
  AutoRefCount<World> mSolarBackgroundEffectsWorld; // +0xa0
  AutoRefCount<World> mSolarBackgroundRenderer; // +0xa4
  AutoRefCount<World> mGalaxyEffectsWorld;      // +0xa8
  AutoRefCount<World> mMoneyEffect;             // +0xac
  AutoRefCount<World> mMoneyEffectPlanet;       // +0xb0
  AutoRefCount<World> mMoneyEffectUFO;          // +0xb4
  char padb8[0x100 - 0xb8];
  bool mInitedForGame;                          // +0x100
  char pad101[3];
  Vec3 mVecA;                                   // +0x104
  Vec3 mVecB;                                   // +0x110
  Vec3 mVecC;                                   // +0x11c
  char pad128[4];
  uint32_t mTravelLineValue;                    // +0x12c
  Vec3 mTravelLineVec;                          // +0x130
  AutoRefCount<PropertyList> mProps;            // +0x13c (placed below)
};


// @ 0x01035900
void cSPSpaceGfx::InitForGame()
{
  if (mInitedForGame)
    return;
  mInitedForGame = true;

  PropertyManager()->GetPropertyList(0xa0cb680a, 0x2ae0c7e, mProps.AsPPTypeParam());
  InitSub();
  g_PhysWorldA.Init(false);
  g_PhysWorldB.Init(false);
  g_PhysWorldC.Init(false);
  g_SpaceCullNear = 50000.0f;
  g_SpaceCullFar = 200000.0f;
  g_SpaceFov = 90.0f;

  mTrailEffectsWorld = EffectsManager()->Create(0x17f40c7, 0);
  mTrailEffectsWorld->SetState(2);
  mMoneyEffect = EffectsManager()->Create(0x17f40c9, 0);
  mMoneyEffect->SetState(2);
  mPtolemaicEffectsWorld = EffectsManager()->Create(0x17f40c8, 0);
  mPtolemaicEffectsWorld->SetState(2);
  mPtolemaicEffectsRenderer = EffectsManager()->Create(0x26f8fcb, 0);

  mSolarBackgroundEffectsWorld = NewWorld();
  mSolarBackgroundEffectsWorld->SetMode(7);
  mSolarBackgroundEffectsWorld->SetView((int)App()->GetViewB(), (int)App()->GetViewA());
  mPtolemaicEffectsRenderer->Attach(mSolarBackgroundEffectsWorld);
  {
    World* r = mPtolemaicEffectsRenderer;
    r->Create(0x3ebf4ae, 0, mSolarComets.AsPPTypeParam());
  }
  {
    World* r = mPtolemaicEffectsRenderer;
    r->Create(0x3ebf4b5, 0, mpMeaningOfLifeEffect.AsPPTypeParam());
  }

  mMoneyEffectPlanet = EffectsManager()->Create(0x67247e6, 0);
  mMoneyEffectPlanet->SetState(2);
  mMoneyEffectUFO = NewWorld();
  mMoneyEffectUFO->SetMode(0);
  mMoneyEffectUFO->SetView((int)App()->GetViewB(), (int)App()->GetViewA());
  mMoneyEffectPlanet->Attach(mMoneyEffectUFO);

  mSolarBackgroundRenderer = EffectsManager()->Create(0x284e479, 0);
  mGalaxyEffectsWorld = NewWorld();
  mGalaxyEffectsWorld->SetMode(4);
  mGalaxyEffectsWorld->SetView((int)App()->GetViewB(), (int)App()->GetViewA());
  mSolarBackgroundRenderer->Attach(mGalaxyEffectsWorld);
  {
    World* r = mSolarBackgroundRenderer;
    r->Create(0x3eac08a, 0, mPlanetBackgroundEffect.AsPPTypeParam());
  }
  {
    World* r = mSolarBackgroundRenderer;
    r->Create(0x3eaf98c, 0, mPlanetBackgroundDustEffect.AsPPTypeParam());
  }

  {
    World* w = mTrailEffectsWorld;
    mPlanetScreenEffect = 1;
    w->Create(0x275fdf3d, 0, mSolarClouds.AsPPTypeParam());
  }
  { World* w = mTrailEffectsWorld; w->Create(0x4cab5702, 0, mLavaPlanetScreenEffect.AsPPTypeParam()); }
  { World* w = mTrailEffectsWorld; w->Create(0x4e7a261f, 0, mSkyboxEffect.AsPPTypeParam()); }
  { World* w = mTrailEffectsWorld; w->Create(0xc150010a, 0, mSolarScreenEffect.AsPPTypeParam()); }
  { World* w = mTrailEffectsWorld; w->Create(0xf1f7d4dc, 0, mSolarLoopbox.AsPPTypeParam()); }
  { World* w = mTrailEffectsWorld; w->Create(0xbf4763d8, 0, mSolarBackgroundEffect.AsPPTypeParam()); }
  { World* w = mTrailEffectsWorld; w->Create(0xa0c77d6f, 0, mSolarBackgroundDustEffect.AsPPTypeParam()); }

  {
    World* w = mMoneyEffect;
    if (w->Create(0x803132fa, 0, mGalaxyCrossfadeEffect.AsPPTypeParam()))
      mGalaxyCrossfadeEffect->Play(1);
  }
  {
    World* w = mMoneyEffect;
    if (w->Create(0x5c830352, 0, mGalaxyEffect.AsPPTypeParam()))
      mGalaxyEffect->Play(1);
  }
  {
    World* w = mMoneyEffect;
    if (w->Create(0x61609a45, 0, mGalaxyAmbienceEffect.AsPPTypeParam()))
      mGalaxyAmbienceEffect->Play(1);
  }
  { World* w = mMoneyEffect; w->Create(0xc467b744, 0, mGalaxyBackgroundGalaxies.AsPPTypeParam()); }
  { World* w = mMoneyEffect; w->Create(0xbbc2a565, 0, mGalaxyScreenEffect.AsPPTypeParam()); }
  { World* w = mTrailEffectsWorld; w->Create(0x840cea6, 0, mTraveLineEffect.AsPPTypeParam()); }
  {
    World* w = mTrailEffectsWorld;
    mTravelLineStar = 0;
    w->Create(0x45846142, 0, mSporepediaPlotPathEffect.AsPPTypeParam());
  }

  mMoneyEffect->SetState(2);
  mTrailEffectsWorld->SetState(0);
  mPtolemaicEffectsWorld->SetState(0);
  mPtolemaicEffectsRenderer->SetState(0);
  mSolarBackgroundRenderer->SetState(0);
  mMoneyEffectPlanet->SetState(0);

  Vec3 zero(0.0f, 0.0f, 0.0f);
  mVecB = zero;
  mVecA = zero;
  mVecC = zero;

  Property* prop;
  if (mProps && mProps->GetProperty(0x68c45d1, &prop) && prop->type == 10)
    mTravelLineValue = *prop->GetUInt();
  GetPropertyAsVector3(mProps, 0x68c4614, &mTravelLineVec);
  ModelManager();
}
