// Slice s00cf93b0 -- SP::cCivModeStrategy::StartTechHint (243 bytes).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Reconstructed from the retail instruction stream; relocations are masked by
// the matcher, so helpers reached by absolute address are declared with the
// argument shape observed at each call site.  The stand-in classes follow the
// real layouts: cCityHall's spatial object sits at +0x34, cCameraMessage is
// 0x30 bytes with its distance float at +0x20.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_1478984[];

typedef unsigned int uint32_t;

extern "C" void* __cdecl SP_NounManager();            // 0x00b3d300
extern "C" void* __cdecl SP_MessageManager();         // 0x00b3d4d0

struct Vector3 { float x, y, z; };

struct ISpatialObject {
    uint32_t mPad0;
};

// Civ-mode camera message (0x00ad79d0/0x00ad7a30 ctors, 0x00ad7b70 target
// getter, 0x00ad7ad0 dtor); the distance float sits at +0x20.
struct cCameraMessage {
    uint32_t mData[8];                                // +0x00
    float    mDistance;                               // +0x20
    uint32_t mPad24[3];                               // +0x24
    cCameraMessage(void* target);                     // 0x00ad7a30
    cCameraMessage(const Vector3& pos, void* from);   // 0x00ad79d0
    ~cCameraMessage();                                // 0x00ad7ad0
    void* GetTarget();                                // 0x00ad7b70
};

struct cCityHall {
    uint32_t       mPad0[13];
    ISpatialObject mSpatial;                          // +0x34
};

struct cCity {
    cCityHall* GetCityHall();                              // 0x00bd9b40
    void       GetCameraSetup(Vector3& pos, float& distance);   // 0x00bd7f70
};

struct cCivilization {
    uint32_t mPad0[0x44c / 4];
    cCity*   mpCity;                                  // +0x44c
};

struct cGameNounManager {
    cCivilization* GetPlayerCivilization();           // 0x00b25fb0
    void*          GetCurrentTerrainSphere();         // 0x00f67d90
};

struct cTerrainSphere {
    char Query(uint32_t flag);                        // 0x00c772c0
    void AddFlag(uint32_t flag);                      // 0x00c77bf0
};

struct cMessageManager {
    void PostMessage(uint32_t id, void* msg, int a);           // 0x00ae09b0
    void PostString(uint32_t id, int a, int b, int c, int d, int e);  // 0x00ae0930
};

struct Strat {
    void StartTechHint();
};

// @ 0x00cf93b0  (243 bytes)
void __thiscall Strat::StartTechHint()
{
    cCivilization* civ = ((cGameNounManager*)SP_NounManager())->GetPlayerCivilization();
    cCity* city = civ->mpCity;
    cCityHall* hall = city->GetCityHall();
    cCameraMessage target(hall ? (void*)&hall->mSpatial : 0);
    ((cMessageManager*)SP_MessageManager())->PostMessage(0x115fa309, &target, 0);

    float distance;
    Vector3 pos;
    city->GetCameraSetup(pos, distance);
    cCameraMessage locator(pos, target.GetTarget());
    locator.mDistance = distance;
    ((cMessageManager*)SP_MessageManager())->PostMessage(0x3f04cafe, &locator, 0);

    cTerrainSphere* terrain =
        (cTerrainSphere*)((cGameNounManager*)SP_NounManager())->GetCurrentTerrainSphere();
    if (!terrain->Query(0x50a2e65)) {
        terrain->AddFlag(0x50a2e65);
        ((cMessageManager*)SP_MessageManager())->PostString((int)g_1478984, 1, 0, 0, 0, 0);
    }
}
