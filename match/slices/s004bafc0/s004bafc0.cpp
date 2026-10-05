// Slice s004bafc0 (creature-editor model type helpers).
// Module flags: /Od /Ob1 /MD /Gy /TP (unoptimized; no C++ EH, no SSE).
#include "types.h"

// ---------------------------------------------------------------------------
// SP::EditorUtils::ComputeVerbIcons (0x004bafc0) and its object model stubs.
// ---------------------------------------------------------------------------
struct ResourceKey { uint32_t id; uint32_t type; uint32_t group; };

struct IRefCounted {
    virtual void v0();       // +0
    virtual void Release();  // +4
};

struct IResourceManager {
    virtual void v0();       // +0
    virtual void v4();       // +4
    virtual void v8();       // +8
    virtual bool FindCached(ResourceKey* out, void* handle, int a, int b, int c, int d);  // +0xc
};

struct cEditorResource : IRefCounted {
    uint8_t pad[0x14];       // +4 .. +0x17
    uint32_t mType;          // +0x18
};

struct cEditorCreature : IRefCounted {
    uint32_t pad4;           // +4
    uint32_t f8;             // +8
    uint32_t fC;             // +0xc
    uint32_t f10;            // +0x10
};

struct cPropertyList {
    bool GetDescription(uint32_t id);
};

extern void* GetManager();                                                   // 0x67dcd0
extern void* FUN_0041d870(void* key);                                        // 0x41d870
extern void* EditorAlloc(uint32_t size, const char* name, int, int, int, int);// 0xf473a0
extern cEditorCreature* FUN_0046a630(cEditorCreature* self, IRefCounted* a); // 0x46a630
extern void MakeBabyRuntimeCreature(cEditorCreature* c);                     // 0x46a8a0
extern cEditorResource* InterfaceCast(IRefCounted** p);                      // 0x421eb0
extern cEditorCreature* FUN_004b9da0(cEditorCreature* self);                 // 0x4b9da0
extern bool FUN_0046d840(cEditorResource* res, cEditorCreature* c);          // 0x46d840
extern void SetCachingType(int, cEditorCreature* c);                         // 0x6ac040
extern void FUN_006ad010(cEditorCreature* c);                                // 0x6ad010
extern void FUN_006b2000(cEditorCreature* c, int v);                         // 0x6b2000
extern void* LoadCreatureData(IRefCounted** p);                              // 0x4bbf60
extern cPropertyList* g_propertyList;                                        // 0x15fd918

static inline void ReleaseRef(IRefCounted* p) {
    if (p)
        p->Release();
}

// 004bafc0
bool FUN_004bafc0(int* param_1, int* param_2) {
    IResourceManager* manager = (IResourceManager*)GetManager();
    ResourceKey key;
    key.id = param_1[0];
    key.type = 0xf43029a;
    key.group = param_1[2];
    if ((((uint32_t)param_1[2] >> 0x18) & 0x1f) == 1) {
        ResourceKey sub;
        sub.id = param_1[0];
        sub.type = param_1[1];
        sub.group = param_1[2] & 0xe0ffffff;
        IRefCounted* tmp = 0;
        void* handle = FUN_0041d870(&tmp);
        if (!FUN_004bafc0((int*)&sub, (int*)handle)) {
            ReleaseRef(tmp);
            return false;
        }
        cEditorCreature* c = (cEditorCreature*)EditorAlloc(0x128, "Editor", 0, 0, 0, 0);
        if (c)
            c = FUN_0046a630(c, tmp);
        if (c)
            c->v0();
        MakeBabyRuntimeCreature(c);
        c->f8 = key.id;
        c->fC = key.type;
        c->f10 = key.group;
        *param_2 = (int)c;
        ReleaseRef(tmp);
        return true;
    }

    IRefCounted* local18 = 0;
    void* h1 = FUN_0041d870(&local18);
    if (manager->FindCached(&key, h1, 0, 0, 0, 0)) {
        void* r = LoadCreatureData(&local18);
        if (r) {
            *param_2 = (int)r;
            ReleaseRef(local18);
            return true;
        }
        ReleaseRef(local18);
        return false;
    }

    void* h2 = FUN_0041d870(&local18);
    if (manager->FindCached((ResourceKey*)param_1, h2, 0, 0, 0, 0)) {
        cEditorResource* res = InterfaceCast(&local18);
        if (!res) {
            ReleaseRef(local18);
            return false;
        }
        uint32_t t = res->mType;
        if (t != 0xdfad9f51 && t != 0x9ea3031a && t != 0x372e2c04 &&
            t != 0xccc35c46 && t != 0x65672ade && t != 0x4178b8e8 &&
            t != 0x37148141 && t != 0xb8669ec9 && t != 0xbcd73e89 &&
            t != 0x6d5c48c) {
            ReleaseRef(local18);
            return false;
        }
        cEditorCreature* c = (cEditorCreature*)EditorAlloc(0x128, "Editor", 0, 0, 0, 0);
        if (c)
            c = FUN_004b9da0(c);
        if (c)
            c->v0();
        if (FUN_0046d840(res, c)) {
            c->f8 = key.id;
            c->fC = key.type;
            c->f10 = key.group;
            SetCachingType(0xb, c);
            FUN_006ad010(c);
            if (g_propertyList->GetDescription(0x26cd3c9))
                FUN_006b2000(c, 1);
            *param_2 = (int)c;
            ReleaseRef(local18);
            return true;
        }
        ReleaseRef(c);
        ReleaseRef(local18);
        return false;
    }

    ReleaseRef(local18);
    return false;
}

// Wide-string / value lookups keyed on Spore model-type hashes.

// 004bb490
const wchar_t* FUN_004bb490(uint32_t type) {
    switch (type) {
    case 0x2399be55: return L"bld";
    case 0x24682294: return L"vcl";
    case 0x2b978c46: return L"crt";
    case 0x3d97a8e4: return L"cll";
    case 0x476a98c7: return L"ufo";
    case 0x438f6347: return L"flr";
    default: return 0;
    }
}

// 004bb510
const wchar_t* FUN_004bb510(int type) {
    switch (type) {
    case (int)0xdfad9f51: return L"Cell"; break;
    case (int)0x9ea3031a: return L"AnimalCreature"; break;
    case 0x372e2c04: return L"TribeCreature"; break;
    case (int)0xccc35c46: return L"CivCreature"; break;
    case 0x65672ade: return L"SpaceCreature"; break;
    case 0x4178b8e8: return L"AdventurerCreature"; break;
    case (int)0x99e92f05: return L"BuildingCityHall"; break;
    case 0x4e3f7777: return L"BuildingHouse"; break;
    case (int)0xbdd15f3d: return L"BuildingFarm"; break;
    case 0x47c10953: return L"BuildingFactory"; break;
    case 0x72c49181: return L"BuildingEntertainment"; break;
    case 0x7d433fad: return L"VehicleMilitaryLand"; break;
    case (int)0x8f963dcb: return L"VehicleMilitaryWater"; break;
    case 0x441cd3e6: return L"VehicleMilitaryAir"; break;
    case (int)0xf670aa43: return L"VehicleEconomicLand"; break;
    case 0x2a5147a9: return L"VehicleEconomicWater"; break;
    case 0x1a4e0708: return L"VehicleEconomicAir"; break;
    case (int)0x9ad7d4aa: return L"VehicleCulturalLand"; break;
    case 0x1f2a25b6: return L"VehicleCulturalWater"; break;
    case 0x449c040f: return L"VehicleCulturalAir"; break;
    case (int)0xbc1041e6: return L"VehicleColonyLand"; break;
    case (int)0xc15695da: return L"VehicleColonyWater"; break;
    case 0x2090a11b: return L"VehicleColonyAir"; break;
    case (int)0xc0b74287: return L"VehicleHarvester"; break;
    case (int)0x98e03c0d: return L"UFO"; break;
    case (int)0xbcd73e89: return L"FloraSmall"; break;
    case (int)0xb8669ec9: return L"FloraMedium"; break;
    case 0x37148141: return L"FloraLarge"; break;
    default: return L"UnknownModelType"; break;
    }
    return 0;
}

// 004bb860 -- SP::cSPUIAssetView::InitVerbCollection (PDB name): model type -> verb type.
uint32_t FUN_004bb860(uint32_t type) {
    switch (type) {
    case 0xdfad9f51: return 0x3d97a8e4;
    case 0x4178b8e8:
    case 0x372e2c04:
    case 0xccc35c46:
    case 0x9ea3031a:
    case 0x65672ade: return 0x2b978c46;
    case 0x72c49181:
    case 0x47c10953:
    case 0x4e3f7777:
    case 0xbdd15f3d:
    case 0x99e92f05: return 0x2399be55;
    case 0x2a5147a9:
    case 0x1a4e0708:
    case 0x1f2a25b6:
    case 0x2090a11b:
    case 0x441cd3e6:
    case 0x449c040f:
    case 0x7d433fad:
    case 0x8f963dcb:
    case 0x9ad7d4aa:
    case 0xc0b74287:
    case 0xf670aa43:
    case 0xbc1041e6:
    case 0xc15695da: return 0x24682294;
    case 0x98e03c0d: return 0x476a98c7;
    case 0x37148141:
    case 0xb8669ec9:
    case 0xbcd73e89: return 0x438f6347;
    default: return 0;
    }
}

// 004bba50 -- model type hash -> verb collection index.
extern uint32_t g_modelTypeVerbDefault;  // 0x015d81a4
uint32_t FUN_004bba50(int type) {
    switch (type) {
    case (int)0x99e92f05: return 2;
    case 0x4e3f7777: return 3;
    case (int)0xbdd15f3d: return 4;
    case 0x47c10953: return 5;
    case 0x72c49181: return 7;
    case 0x7d433fad: return 2;
    case (int)0x8f963dcb: return 3;
    case 0x441cd3e6: return 4;
    case (int)0xf670aa43: return 5;
    case 0x2a5147a9: return 6;
    case 0x1a4e0708: return 7;
    case (int)0x9ad7d4aa: return 8;
    case 0x1f2a25b6: return 9;
    case 0x449c040f: return 10;
    case (int)0xbc1041e6: return 0xb;
    case (int)0xc15695da: return 0xc;
    case 0x2090a11b: return 0xd;
    case (int)0xc0b74287: return 1;
    case (int)0xbcd73e89: return 1;
    case (int)0xb8669ec9: return 2;
    case 0x37148141: return 3;
    default: return 0;
    }
    return g_modelTypeVerbDefault;
}

// 004bbc70
uint32_t FUN_004bbc70(uint32_t type, uint8_t useSpecial) {
    if (useSpecial && type == 0x366a930d)
        return 0x8a;
    switch (type) {
    case 0x3d97a8e4: return 0x61;
    case 0x2b978c46: return 0x62;
    case 0x2399be55: return 0x63;
    case 0x24682294: return 0x64;
    case 0x476a98c7: return 0x65;
    case 0x438f6347: return 0x66;
    case 0x04f684a4: return 0xc0;
    default: return 1;
    }
}

// 004bbd20 -- SP::EditorEntityToResourceType
uint32_t GetTypeForCategory(uint32_t code, uint8_t useSpecial) {
    if (useSpecial && code == 0x8a)
        return 0x366a930d;
    switch (code) {
    case 0x61: return 0x3d97a8e4;
    case 0x62: return 0x2b978c46;
    case 0x63: return 0x2399be55;
    case 0x64: return 0x24682294;
    case 0x65: return 0x476a98c7;
    case 0x66: return 0x438f6347;
    case 0xc0: return 0x04f684a4;
    default: return (uint32_t)-1;
    }
}

// 004bbe20 -- SP::cSPAssetDataList::SetAssetData (used as a type predicate)
bool IsBakeableType(uint32_t type, uint8_t useSpecial) {
    if (useSpecial && type == 0x366a930d)
        return true;
    switch (type) {
    case 0x3d97a8e4:
    case 0x2399be55:
    case 0x24682294:
    case 0x2b978c46:
    case 0x438f6347:
    case 0x476a98c7:
        return true;
    default:
        return false;
    }
}

// 004bbe90 -- SP::cSPEditorPaintTheme::ExtractSkinPaintData
bool FUN_004bbe90(uint32_t type) {
    switch (type) {
    case 0x2b978c46:
    case 0x3d97a8e4:
    case 0x438f6347:
        return true;
    default:
        return false;
    }
}

// 004bbed0
bool FUN_004bbed0(uint32_t type) {
    switch (type) {
    case 0x2399be55:
    case 0x24682294:
    case 0x476a98c7:
        return true;
    default:
        return false;
    }
}

// 004bbf10
bool FUN_004bbf10(int type) {
    switch (type) {
    case 0x4178b8e8:
    case 0xccc35c46:
    case 0x372e2c04:
    case 0x65672ade:
        return true;
    default:
        return false;
    }
}
