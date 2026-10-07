// Slice s00e35370: one function
//   0x00E35370  cSPUITCCCursorStrategy::UpdateCursorStrategy   (3530 bytes, __thiscall, ret 4)
// Dev-build symbol: ?UpdateCursorStrategy@cSPUITCCCursorStrategy@@UAE_NI@Z
// Civ/space (TCC) cursor strategy: picks the cursor for the object under the mouse (city halls,
// buildings, vehicles, turrets, commodity nodes, creatures, terrain) given the vehicles
// currently selected, and shows/hides the city and selection rollovers.
// The retail layout of cSPUITCCCursorStrategy differs from the 2008 PDB (flags at +0x20..+0x22).
// Most callees have no recovered name; they are declared with the conventions read from the
// call sites (cdecl helpers, thiscall members, vtable slots).
// Flags: /O2 /MD /Gy /TP /arch:SSE (no EH frame although vector locals have destructors).
#include "types.h"

#define PAD_VIRT(n) virtual void _v##n()

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Rectangle { float x1, y1, x2, y2; };

bool __cdecl Vector3NotEqual(const Vector3& a, const Vector3& b);   // 0x0041DD30
bool __cdecl Vector3Equal(const Vector3& a, const Vector3& b);      // 0x004232C0
extern "C" int __cdecl atexit(void (__cdecl* fn)(void));

namespace eastl {
struct sp_vector_allocator {
    sp_vector_allocator() {}
    const char* mpName;
};
template <class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vector();                                         // 0x00AD92D0 (out of line)
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    T* erase(T* first, T* last);                       // 0x00B48E40
};
}

// ---------------------------------------------------------------- game objects
// Secondary base of spatial objects (cSpatialObject view of buildings, vehicles, ...)
struct ISpatial {
    PAD_VIRT(00); PAD_VIRT(04); PAD_VIRT(08); PAD_VIRT(0c);
    PAD_VIRT(10); PAD_VIRT(14); PAD_VIRT(18); PAD_VIRT(1c);
    PAD_VIRT(20); PAD_VIRT(24); PAD_VIRT(28);
    /* 2ch */ virtual const Vector3& GetPosition();
    PAD_VIRT(30); PAD_VIRT(34); PAD_VIRT(38); PAD_VIRT(3c);
    PAD_VIRT(40); PAD_VIRT(44); PAD_VIRT(48); PAD_VIRT(4c);
    PAD_VIRT(50); PAD_VIRT(54);
    /* 58h */ virtual bool IsPlayerOwned();
};

struct cCombatant {
    int GetDamageState();                              // 0x008E7F80
};

struct cGameObject;
struct cGameObject {
    PAD_VIRT(00); PAD_VIRT(04); PAD_VIRT(08);
    /* 0ch */ virtual void* Cast(uint32_t typeID);
    /* 10h */ virtual bool IsActive();
    PAD_VIRT(14); PAD_VIRT(18); PAD_VIRT(1c);
    PAD_VIRT(20); PAD_VIRT(24); PAD_VIRT(28); PAD_VIRT(2c);
    PAD_VIRT(30); PAD_VIRT(34); PAD_VIRT(38); PAD_VIRT(3c);
    PAD_VIRT(40); PAD_VIRT(44); PAD_VIRT(48);
    /* 4ch */ virtual int GetPoliticalID();
    PAD_VIRT(50); PAD_VIRT(54);
    /* 58h */ virtual struct cEmpireInfo* GetEmpire();
    PAD_VIRT(5c); PAD_VIRT(60); PAD_VIRT(64); PAD_VIRT(68); PAD_VIRT(6c);
    PAD_VIRT(70); PAD_VIRT(74); PAD_VIRT(78); PAD_VIRT(7c); PAD_VIRT(80);
    /* 84h */ virtual cGameObject* GetOwner();
};

struct cEmpireInfo { uint8_t pad[0x557]; bool mbFlag557; };

// spatial view at +0x34
struct cSpatial34 : cGameObject { uint32_t pad04[(0x34 - 4) / 4]; ISpatial mSpatial; };
// spatial view at +0x70
struct cSpatial70 : cGameObject { uint32_t pad04[(0x70 - 4) / 4]; ISpatial mSpatial; };

struct cBuilding : cGameObject {                 // interface_cast<cBuilding*>
    uint32_t pad04[(0x34 - 4) / 4];
    ISpatial mSpatial;                           // +0x34
    uint32_t pad38[(0x120 - 0x38) / 4];
    cCombatant mCombatant;                       // +0x120
};
struct cTurret : cGameObject {
    uint32_t pad04[(0x34 - 4) / 4];
    ISpatial mSpatial;                           // +0x34
    uint32_t pad38[(0x588 - 0x38) / 4];
    cCombatant mCombatant;                       // +0x588
    cGameObject* GetTarget();                    // 0x00BCE5C0
};
struct cCity : cGameObject {                     // owner of a city hall
    uint32_t pad04[(0x120 - 4) / 4];
    ISpatial mSpatial;                           // +0x120
    void ShowRollover(struct cRolloverCityHall* rollover);   // 0x00BDDE70
};
struct cTarget {
    const Vector3& GetPosition();                // 0x00FA0E00
};
struct cAnimal { uint8_t pad[0xb5e]; bool mbFlagB5E; };
struct cVehicleInfo {                            // FUN_00bd8440 result
    uint8_t pad[0xb1c];
    int mLocomotion;                             // +0xb1c
    int mPurpose;                                // +0xb20
    bool CanOccupyTerrain(const Vector3& pos);   // 0x00C9E960
};
struct cHoverVehicle : cGameObject {             // FUN_00e34ef0 result
    uint32_t pad04[(0x100 - 4) / 4];
    ISpatial mSpatial;                           // +0x100
    uint32_t pad104[(0x1d8 - 0x104) / 4];
    int mState;                                  // +0x1d8
    bool IsMoving();                             // 0x00BD8630
    void UpdateHover();                          // 0x00BD84E0
};
struct cCivilization : cGameObject {};

typedef cGameObject* ObjectRef;                  // EA::AutoRefCount<cSpatialObject>

cVehicleInfo* __cdecl GetVehicle(ObjectRef* ref);                 // 0x00BD8440
cGameObject*  __cdecl GetSelectable(cGameObject* obj);            // 0x00C9F060
cAnimal*      __cdecl CastAnimal(cGameObject* obj);               // 0x00AC8960
cSpatial34*   __cdecl CastUFO(cGameObject* obj);                  // 0x00B676E0
cSpatial34*   __cdecl CastCityWall(cGameObject* obj);             // 0x00AE6760
cBuilding*    __cdecl CastBuilding(cGameObject* obj);             // 0x00B67720
cSpatial70*   __cdecl CastPlant(cGameObject* obj);                // 0x00BD8460
cHoverVehicle* __cdecl CastHoverVehicle(cGameObject* obj);        // 0x00E34EF0
cSpatial34*   __cdecl CastCityHall(cGameObject* obj);             // 0x00CF7D20
cSpatial34*   __cdecl CastCommodityNode(cGameObject* obj);        // 0x00E34F10
cTurret*      __cdecl CastTurret(cGameObject* obj);               // 0x00B18720
void*         __cdecl CastGameBundle(cGameObject* obj);           // 0x00CCE8F0
void*         __cdecl GetObjectInfo(cGameObject* obj);            // 0x00AE6740
void          __cdecl GetActivePlanet();                          // 0x01021260

bool __cdecl IsTributeObject(cGameObject* obj);                   // 0x00B673C0
bool __cdecl IsPieMenuOpen();                                     // 0x00B7C780
bool __cdecl IsCreature(cGameObject* obj);                        // 0x00B188B0
bool __cdecl IsTribe(cGameObject* obj);                           // 0x00B18740
bool __cdecl IsTribeMember(cGameObject* obj);                     // 0x00B18760
bool __cdecl IsCity(cGameObject* obj);                            // 0x00B187B0
bool __cdecl IsVehicle(cGameObject* obj);                         // 0x00B18790
bool __cdecl IsBuilding(cGameObject* obj);                        // 0x00B187F0
void __cdecl PlayRolloverSound(cGameObject* obj);                 // 0x00B69990

bool __cdecl IsSpaceToolActive();                                 // 0x00E09540
bool __cdecl CanUseSpaceTool(void* obj);                          // 0x00E09AD0
bool __cdecl IsBanToolActive();                                   // 0x00DD1230
bool __cdecl CanBan(cGameObject* obj);                            // 0x00DD18B0
void __cdecl PositionRollover(ISpatial* object, const Rectangle& area, float* x, float* y,
                              int* flipped, float offset);       // 0x00E2EAB0
int  __cdecl GetRecorderState();                                  // 0x00435E90
void __cdecl PlayAudio(uint32_t id, int state);                   // 0x00435ED0
bool __cdecl IsPieMenuWindow(struct IWindow* window);             // 0x00B7C870
void __cdecl HideUTFMenu(int hide);                               // 0x00B7C810

// ---------------------------------------------------------------- UI
struct IWindow {
    /* 00h */ virtual int AddRef();
    /* 04h */ virtual int Release();
    PAD_VIRT(08); PAD_VIRT(0c);
    PAD_VIRT(10); PAD_VIRT(14); PAD_VIRT(18); PAD_VIRT(1c);
    PAD_VIRT(20); PAD_VIRT(24); PAD_VIRT(28); PAD_VIRT(2c); PAD_VIRT(30);
    /* 34h */ virtual const Rectangle& GetArea();
    PAD_VIRT(38); PAD_VIRT(3c);
    PAD_VIRT(40); PAD_VIRT(44); PAD_VIRT(48); PAD_VIRT(4c);
    PAD_VIRT(50); PAD_VIRT(54); PAD_VIRT(58); PAD_VIRT(5c); PAD_VIRT(60);
    /* 64h */ virtual void SetLocation(float x, float y);
    PAD_VIRT(68); PAD_VIRT(6c); PAD_VIRT(70); PAD_VIRT(74); PAD_VIRT(78);
    /* 7ch */ virtual void SetFlag(int flag, bool value);
    PAD_VIRT(80); PAD_VIRT(84); PAD_VIRT(88); PAD_VIRT(8c);
    PAD_VIRT(90); PAD_VIRT(94); PAD_VIRT(98); PAD_VIRT(9c);
    PAD_VIRT(a0); PAD_VIRT(a4); PAD_VIRT(a8); PAD_VIRT(ac);
    PAD_VIRT(b0); PAD_VIRT(b4); PAD_VIRT(b8); PAD_VIRT(bc);
    PAD_VIRT(c0); PAD_VIRT(c4); PAD_VIRT(c8); PAD_VIRT(cc);
    PAD_VIRT(d0); PAD_VIRT(d4); PAD_VIRT(d8); PAD_VIRT(dc);
    PAD_VIRT(e0); PAD_VIRT(e4); PAD_VIRT(e8); PAD_VIRT(ec);
    PAD_VIRT(f0); PAD_VIRT(f4);
    /* f8h */ virtual bool IsAncestorOf(const IWindow* child);
};

struct IWindowManager {
    PAD_VIRT(00); PAD_VIRT(04); PAD_VIRT(08); PAD_VIRT(0c);
    PAD_VIRT(10); PAD_VIRT(14); PAD_VIRT(18); PAD_VIRT(1c);
    PAD_VIRT(20); PAD_VIRT(24); PAD_VIRT(28); PAD_VIRT(2c);
    PAD_VIRT(30); PAD_VIRT(34); PAD_VIRT(38); PAD_VIRT(3c);
    PAD_VIRT(40); PAD_VIRT(44);
    /* 48h */ virtual IWindow* GetFocusWindow(int flags);
};
IWindowManager* __cdecl WindowManager();                          // 0x0067CAA0

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (p) p->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
};

struct cCursorManager {
    void SetLocalCursor(uint32_t id);            // 0x00801BB0
    void SetWindow(IWindow* window);             // 0x008017F0
    bool IsDefaultCursor();                      // 0x00801400
    void* GetAttachment();                       // 0x00801920
};
cCursorManager* __cdecl CursorManager();                          // 0x0067CAB0

struct cRolloverCityHall {
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24();
    /* 28h */ virtual void SetLayout(uint32_t id);
    uint32_t pad04[(0x44 - 4) / 4];
    bool mbVisible;                              // +0x44
    uint32_t pad48[(0xa8 - 0x48) / 4];
    cGameObject* mpCity;                         // +0xa8
    void Update();                               // 0x00E2B9D0
    IWindow* GetRootWindow();                    // 0x00828100 (cSPUIPropertyLayout)
};
struct cRolloverVehicle {
    uint32_t pad[0x78 / 4];
    uint32_t mAttachment;                        // +0x78 (cursor attachment base)
};
struct cRolloverSelectionVerb {
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18();
    /* 1ch */ virtual void Show();
    /* 20h */ virtual void Hide();
    void SetObject(cGameObject* obj);            // 0x00E077D0
};

struct ITerrainCursor {
    PAD_VIRT(00); PAD_VIRT(04); PAD_VIRT(08); PAD_VIRT(0c);
    PAD_VIRT(10); PAD_VIRT(14); PAD_VIRT(18); PAD_VIRT(1c);
    PAD_VIRT(20); PAD_VIRT(24); PAD_VIRT(28); PAD_VIRT(2c);
    PAD_VIRT(30); PAD_VIRT(34); PAD_VIRT(38); PAD_VIRT(3c);
    PAD_VIRT(40); PAD_VIRT(44); PAD_VIRT(48); PAD_VIRT(4c);
    PAD_VIRT(50); PAD_VIRT(54); PAD_VIRT(58);
    /* 5ch */ virtual void GetSelectedVehicles(eastl::vector<ObjectRef>* out);
    /* 60h */ virtual void GetSelection(eastl::vector<ObjectRef>& out, uint32_t typeID);
    PAD_VIRT(64); PAD_VIRT(68);
    /* 6ch */ virtual int CountSelected(uint32_t typeID);
    /* 70h */ virtual int GetSelectionCount();
    /* 74h */ virtual void UpdateSelection();
    PAD_VIRT(78); PAD_VIRT(7c);
    PAD_VIRT(80); PAD_VIRT(84); PAD_VIRT(88); PAD_VIRT(8c);
    PAD_VIRT(90); PAD_VIRT(94); PAD_VIRT(98); PAD_VIRT(9c);
    PAD_VIRT(a0); PAD_VIRT(a4);
    /* a8h */ virtual bool IsDragging();
};
ITerrainCursor* __cdecl GetGameTerrainCursor();                   // 0x00B30D70

struct IGameView {
    PAD_VIRT(00); PAD_VIRT(04); PAD_VIRT(08); PAD_VIRT(0c);
    PAD_VIRT(10); PAD_VIRT(14); PAD_VIRT(18); PAD_VIRT(1c);
    PAD_VIRT(20); PAD_VIRT(24); PAD_VIRT(28); PAD_VIRT(2c); PAD_VIRT(30);
    /* 34h */ virtual cGameObject* GetHoveredObject();
    /* 38h */ virtual void GetTerrainPoint(Vector3* out, int flags, Vector3 screenPos);
    PAD_VIRT(3c);
    PAD_VIRT(40); PAD_VIRT(44); PAD_VIRT(48); PAD_VIRT(4c);
    PAD_VIRT(50); PAD_VIRT(54); PAD_VIRT(58); PAD_VIRT(5c);
    /* 60h */ virtual void PlayEffect(uint32_t id, const Vector3* pos, const Vector3* dir);
};
IGameView* __cdecl GameView();                                    // 0x00B3D240

struct cGameState { uint32_t pad[0x2c / 4]; int mMode; };
cGameState* __cdecl GameState();                                  // 0x00B3D4D0
struct cInputState { bool IsBusy(); };                            // 0x00B5CA60
cInputState* __cdecl InputState();                                // 0x00B3D230

uint32_t __cdecl GetCurrentGameMode();                            // 0x00B5B800
enum { kGameCiv = 0x1654C04 };

struct cCivToolInfo { bool IsToolActive(); bool IsTargetTool(); };  // 0x00CF0FE0 / 0x00CF0E10
struct cCivModeStrategy {
    uint8_t pad[0x148];
    bool mbFlag148;
    cCivToolInfo* GetToolInfo();                 // 0x00CF74F0
};
cCivModeStrategy* __cdecl CivModeStrategy();                      // 0x00CF74C0

struct cGameNounManager {
    void* GetCurrentCityInfo();                  // 0x00B25C30
    cCivilization* GetPlayerCivilization();      // 0x00B25FB0
};
cGameNounManager* __cdecl NounManager();                          // 0x00B3D300
struct cCityInfo { bool IsArrowHidden(int); };                    // 0x00BDC4A0

struct cPlanetModel { void UpdateTerrainPoint(Vector3* pos); };   // 0x00B88590
cPlanetModel* __cdecl PlanetModel();                              // 0x00B3D350

extern Vector3 gInvalidScreenPos;                                 // 0x016AC67C
extern Vector3 gEffectDirection;                                  // 0x016ACC38
void __cdecl DestroySelectedVehicles();                           // 0x013C7910 (atexit)

// ---------------------------------------------------------------- the strategy
class cSPUITCCCursorStrategy {
public:
    bool UpdateCursorStrategy(uint32_t flags);
    void HideCityRollover();                     // 0x00E352C0
    void HideRollovers();                        // 0x00E35350

    uint32_t vtable;                             // +0x00
    uint32_t pad04[2];
    bool mbTerrainEffectShown;                   // +0x0c
    cRolloverCityHall* mpCityRollover;           // +0x10
    cRolloverVehicle* mpVehicleRollover;         // +0x14
    uint32_t pad18;
    cRolloverSelectionVerb* mpSelectionVerbCursor;   // +0x1c
    bool mbCityHallArrowWasHidden;               // +0x20
    bool mbDisabled;                             // +0x21
    bool mbMineralMode;                          // +0x22
    void* mpMineralBar;                          // +0x24
};

// 0x00E34E00: static helper (argument in esi)
static __declspec(noinline) void ShowObjectRollover(cGameObject* obj)
{
    if (!obj || !IsTributeObject(obj) || IsPieMenuOpen())
        return;
    int mode = GameState()->mMode;
    if (mode == 1 || mode == 2)
        return;
    if (GetCurrentGameMode() == kGameCiv) {
        if (IsCreature(obj))
            return;
        if (IsTribe(obj) && !IsTribeMember(obj))
            return;
        if (IsCity(obj) || IsVehicle(obj) || IsBuilding(obj))
            return;
    }
    PlayRolloverSound(obj);
}

// @ 0x00e35370
bool cSPUITCCCursorStrategy::UpdateCursorStrategy(uint32_t flags)
{
    if (mpCityRollover->mbVisible)
        mpCityRollover->Update();

    bool inTutorial;
    int gameMode = GameState()->mMode;
    if (gameMode == 1 || gameMode == 2)
        inTutorial = true;
    else
        inTutorial = false;

    if (!mbDisabled && !InputState()->IsBusy() && !inTutorial) {
        cGameObject* obj = GameView()->GetHoveredObject();
        cCursorManager* cursorMgr = CursorManager();

        if (IsSpaceToolActive()) {
            void* p;
            if (obj && (p = obj->Cast(0x17f243b)) != 0 && CanUseSpaceTool(p)) {
                cursorMgr->SetLocalCursor(0xf6879190);
                return true;
            }
            cursorMgr->SetLocalCursor(0x5ecbdffd);
            return true;
        }
        if (IsBanToolActive()) {
            cGameObject* selectable = GetSelectable(obj);
            if (selectable && CanBan(selectable)) {
                cursorMgr->SetLocalCursor(0xf212a38b);
                return true;
            }
            cursorMgr->SetLocalCursor(0x5ecbdffd);
            return true;
        }

        if (!mbDisabled && cursorMgr->IsDefaultCursor()) {
            cursorMgr->SetLocalCursor(0x1002);
            int selectionMode = 0;
            ITerrainCursor* terrainCursor = GetGameTerrainCursor();
            if (terrainCursor) {
                if (terrainCursor->GetSelectionCount())
                    selectionMode = terrainCursor->CountSelected(0x137e8e0) ? 1 : 2;
                if (terrainCursor->IsDragging())
                    return false;
            }

            cGameObject* selectable = GetSelectable(obj);
            if (selectable)
                ShowObjectRollover(selectable);

            bool isCiv = GetCurrentGameMode() == kGameCiv;
            if (isCiv && CivModeStrategy()->GetToolInfo()->IsToolActive()) {
                cursorMgr->SetLocalCursor(0x600cd69);
                return true;
            }
            if (!cursorMgr || !mpCityRollover || !mpVehicleRollover)
                return false;

            GetObjectInfo(obj);

            bool anyColonists = false;
            bool anyMilitary = false;
            bool anyNotLand = false;
            if (selectionMode == 1) {
                eastl::vector<ObjectRef> selection;
                terrainCursor->GetSelection(selection, 0x137e8e0);
                for (ObjectRef* it = selection.begin(); it != selection.end(); ++it) {
                    if (anyColonists && anyMilitary && anyNotLand)
                        break;
                    cVehicleInfo* vehicle = GetVehicle(it);
                    anyColonists = anyColonists || vehicle->mPurpose == 0;
                    anyMilitary = anyMilitary || vehicle->mPurpose == 1;
                    anyNotLand = anyNotLand || vehicle->mLocomotion != 1;
                }
            }

            if (isCiv && CivModeStrategy()->GetToolInfo()->IsTargetTool()) {
                cursorMgr->SetLocalCursor(0x3febe41);
                cursorMgr->SetWindow(0);
                HideCityRollover();
                return true;
            }

            cAnimal* animal = CastAnimal(obj);
            cSpatial34* ufo = CastUFO(obj);
            cSpatial34* cityWall = CastCityWall(obj);
            cBuilding* building = CastBuilding(obj);
            cSpatial70* plant = CastPlant(obj);
            GetActivePlanet();
            cHoverVehicle* hoverVehicle = CastHoverVehicle(obj);
            if (hoverVehicle) {
                bool moving = hoverVehicle->mState == 2 && !hoverVehicle->IsMoving();
                hoverVehicle->UpdateHover();
                if (selectionMode == 1 && anyMilitary && !hoverVehicle->mSpatial.IsPlayerOwned()) {
                    if (moving)
                        cursorMgr->SetLocalCursor(0x3a204b0);
                    else
                        cursorMgr->SetLocalCursor(0x3570021);
                }
            }

            cSpatial34* cityHall = CastCityHall(obj);
            if (cityHall) {
                if (isCiv && CivModeStrategy()->mbFlag148)
                    return true;
                cCity* city = (cCity*)cityHall->GetOwner();
                if (city) {
                    if (!mpCityRollover->mbVisible) {
                        cCityInfo* info = (cCityInfo*)NounManager()->GetCurrentCityInfo();
                        if (info)
                            mbCityHallArrowWasHidden = info->IsArrowHidden(0);
                    }
                    float x = 0.0f;
                    float y = 0.0f;
                    mpCityRollover->SetLayout(0xe9f70df9);
                    if (city->mSpatial.IsPlayerOwned())
                        mpCityRollover->mpCity = city;
                    city->ShowRollover(mpCityRollover);
                    IWindow* window = mpCityRollover->GetRootWindow();
                    int flipped;
                    PositionRollover(&cityHall->mSpatial, window->GetArea(), &x, &y, &flipped, 0.0f);
                    window->SetLocation(x, y);
                    window->SetFlag(1, true);
                    if (!city->mSpatial.IsPlayerOwned()) {
                        cursorMgr->SetLocalCursor(0x3febe41);
                        cursorMgr->SetWindow(0);
                    }
                }
                return true;
            }

            if (!(building && building->mSpatial.IsPlayerOwned() && mpCityRollover->mpCity == building->GetOwner())
                && !(plant && plant->mSpatial.IsPlayerOwned()))
                HideCityRollover();

            if (cityWall) {
                if (selectionMode == 1 && !cityWall->mSpatial.IsPlayerOwned() && (anyColonists || anyMilitary))
                    cursorMgr->SetLocalCursor(0x3570021);
                return true;
            }

            cSpatial34* commodity = CastCommodityNode(obj);
            if (commodity) {
                mpSelectionVerbCursor->SetObject(commodity);
                mpSelectionVerbCursor->Show();
                if (selectionMode == 1) {
                    eastl::vector<ObjectRef> selection;
                    terrainCursor->GetSelection(selection, 0x137e8e0);
                    Vector3 pos = commodity->mSpatial.GetPosition();
                    int nodeOwner = commodity->GetPoliticalID();
                    int playerID = -1;
                    cCivilization* civ = NounManager()->GetPlayerCivilization();
                    if (civ)
                        playerID = civ->GetPoliticalID();
                    bool unclaimed = nodeOwner == -1;
                    bool ownNode = playerID == nodeOwner;
                    bool anyCanReach = false;
                    bool landCanReach = false;
                    bool airCanReach = false;
                    for (ObjectRef* it = selection.begin(); it != selection.end(); ++it) {
                        cVehicleInfo* vehicle = GetVehicle(it);
                        if (vehicle->mLocomotion != 2) {
                            bool canReach = vehicle->CanOccupyTerrain(pos);
                            int purpose = vehicle->mPurpose;
                            if (anyCanReach || canReach)
                                anyCanReach = true;
                            if (purpose == 1 || purpose == 0)
                                landCanReach = landCanReach || canReach;
                            else if (purpose == 2)
                                airCanReach = airCanReach || canReach;
                        }
                    }
                    if (unclaimed) {
                        if (anyCanReach) {
                            cursorMgr->SetLocalCursor(0x5d53800);
                            return true;
                        }
                    } else {
                        if (ownNode)
                            return true;
                        if (airCanReach) {
                            cursorMgr->SetLocalCursor(0x3febe41);
                            return true;
                        }
                        if (landCanReach) {
                            cursorMgr->SetLocalCursor(0x3570021);
                            return true;
                        }
                    }
                    cursorMgr->SetLocalCursor(0x3a204b0);
                    return true;
                }
            } else {
                mpSelectionVerbCursor->Hide();
                mpSelectionVerbCursor->SetObject(0);
            }

            if (ufo && GetCurrentGameMode() == kGameCiv && selectionMode == 1) {
                eastl::vector<ObjectRef> selection;
                terrainCursor->GetSelection(selection, 0x137e8e0);
                Vector3 pos = ufo->mSpatial.GetPosition();
                bool canReach = false;
                for (ObjectRef* it = selection.begin(); it != selection.end(); ++it)
                    canReach = GetVehicle(it)->CanOccupyTerrain(pos);
                if (canReach && !ufo->GetEmpire()->mbFlag557)
                    cursorMgr->SetLocalCursor(0x56e3a22);
                else
                    cursorMgr->SetLocalCursor(0x3a204b0);
                return true;
            }

            GetGameTerrainCursor()->UpdateSelection();
            int count = GetGameTerrainCursor()->GetSelectionCount();
            cTurret* turret = CastTurret(obj);
            if (count > 0) {

                if (selectionMode == 1 && (anyColonists || anyMilitary)) {
                    cGameObject* target;
                    if (building && !building->mSpatial.IsPlayerOwned() && building->mCombatant.GetDamageState() != 2)
                        target = building->GetOwner();
                    else if (turret && !turret->mSpatial.IsPlayerOwned() && turret->mCombatant.GetDamageState() != 2)
                        target = turret->GetTarget();
                    else
                        goto noTarget;
                    if (target) {
                        bool moved = Vector3NotEqual(((cTarget*)target)->GetPosition(), gInvalidScreenPos);
                        if (anyNotLand || moved)
                            cursorMgr->SetLocalCursor(0x3570021);
                    }
                }
        noTarget:
                CastGameBundle(obj);
                if (!building || !building->mSpatial.IsPlayerOwned()) {
                    Vector3 pos;
                    if (animal) {
                        if ((anyColonists || anyMilitary) && !animal->mbFlagB5E)
                            cursorMgr->SetLocalCursor(0x3570021);
                        if (mbTerrainEffectShown)
                            return true;
                        mbTerrainEffectShown = true;
                        GameView()->GetTerrainPoint(&pos, 1, gInvalidScreenPos);
                        PlayAudio(0xab355c8f, GetRecorderState());
                        GameView()->PlayEffect(0x37ac469, &pos, &gEffectDirection);
                        return true;
                    }
                    GameView()->GetTerrainPoint(&pos, 0, gInvalidScreenPos);
                    if (!Vector3Equal(pos, gInvalidScreenPos) && !building && !turret && !commodity) {
                        PlanetModel()->UpdateTerrainPoint(&pos);
                        bool canReach = false;
                        static eastl::vector<ObjectRef> sVehicles;
                        terrainCursor->GetSelectedVehicles(&sVehicles);
                        for (int i = 0; i < sVehicles.size() && !canReach; i++) {
                            cVehicleInfo* vehicle = GetVehicle(&sVehicles[i]);
                            if (vehicle && vehicle->CanOccupyTerrain(pos))
                                canReach = true;
                        }
                        sVehicles.erase(sVehicles.mpBegin, sVehicles.mpEnd);
                        cursorMgr->SetLocalCursor(canReach ? 0x1002 : 0x3a204b0);
                    }
                }
                mbTerrainEffectShown = false;
                return true;
            }
            void* attachment = mpVehicleRollover ? &mpVehicleRollover->mAttachment : 0;
            if (cursorMgr->GetAttachment() == attachment)
                cursorMgr->SetWindow(0);
            return false;
        }
        HideRollovers();
        mpSelectionVerbCursor->Hide();
        mpSelectionVerbCursor->SetObject(0);
        return false;
    }

    if (mbMineralMode) {
        bool canMine = false;
        if (mpMineralBar) {
            cGameObject* obj = GameView()->GetHoveredObject();
            if (obj) {
                cGameObject* resource = (cGameObject*)obj->Cast(0xe89adf71);
                cSpatial34* a = (cSpatial34*)obj->Cast(0xe9cb8ba);
                cSpatial34* b = (cSpatial34*)obj->Cast(0x137e8e0);
                cSpatial34* c = (cSpatial34*)obj->Cast(0x436f315);
                cSpatial70* d = (cSpatial70*)obj->Cast(0x175cdc9);
                if (!resource || resource->IsActive()) {
                    ISpatial* spatial = 0;
                    if (a)
                        spatial = &a->mSpatial;
                    else if (b)
                        spatial = &b->mSpatial;
                    else if (c)
                        spatial = &c->mSpatial;
                    else if (d)
                        spatial = &d->mSpatial;
                    if (spatial && spatial->IsPlayerOwned())
                        canMine = true;
                }
            }
        }
        cCursorManager* cursorMgr = CursorManager();
        if (!cursorMgr)
            return false;
        if (canMine) {
            cursorMgr->SetLocalCursor(0x648fbf1);
            return false;
        }
        cursorMgr->SetLocalCursor(0x1002);
        return false;
    }

    if (mpCityRollover->mbVisible || IsPieMenuOpen()) {
        AutoRefCount<IWindow> focus(WindowManager()->GetFocusWindow(1));
        IWindow* root = mpCityRollover->GetRootWindow();
        if (root && !root->IsAncestorOf(focus))
            HideCityRollover();
        if (!IsPieMenuWindow(focus))
            HideUTFMenu(1);
    }
    cCursorManager* cursorMgr = CursorManager();
    if (cursorMgr)
        cursorMgr->SetLocalCursor(0x1002);
    mpSelectionVerbCursor->Hide();
    mpSelectionVerbCursor->SetObject(0);
    return false;
}
