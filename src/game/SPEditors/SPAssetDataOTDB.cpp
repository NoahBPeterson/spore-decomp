// src/game/SPEditors/SPAssetDataOTDB.cpp -- migrated from slice(s) s006414e0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPAssetDataOTDB.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/Manager.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cSPAssetData.h"

// ---- items of slice s006414e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey() {}
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
struct IRefCounted { virtual int AddRef(); virtual int Release(); };
struct cAssetMetadata : IRefCounted {
    uint64_t* FUN_005507a0();     // 0x005507A0
    uint64_t* FUN_00550840();     // 0x00550840
    uint64_t* FUN_00550860();     // 0x00550860
    uint64_t  FUN_005508a0();     // 0x005508A0
    bool      FUN_00550970();     // 0x00550970
};
struct cSPAssetData {
virtual int v00();
virtual int v01();
virtual int v02();
virtual int v03();
virtual int v04();
virtual int v05();
virtual int v06();
virtual int v07();
virtual int v08();
    virtual uint32_t GetAssetType();   // +0x24
};
struct cSPAssetDataOTDB : cSPAssetData {
    uint32_t mKeyInstance;       // +4
    uint32_t mTypeID;            // +8
    uint32_t mKeyGroup;          // +0xC
    uint32_t pad10[3];
    cAssetMetadata* mMetadata;   // +0x1C

    ResourceKey* GetKey(ResourceKey* out);
    int FUN_00641780();
    bool GetMetadataKey(uint64_t* out);
    uint64_t FUN_00641830();
    uint64_t FUN_00641870();
    uint64_t FUN_00641890();
    bool FUN_006418b0();
    int FUN_006418e0();
    ResourceKey* GetThumbnailBackdrop(ResourceKey* out);
};
// ---- items of slice s006414e0 end

// @ 0x00641500
ResourceKey* cSPAssetDataOTDB::GetThumbnailBackdrop(ResourceKey* out)
{
    out->instanceID = 0;
    out->typeID = 0x2f7d0004;
    out->groupID = 0xca14de92;
    switch (GetAssetType()) {
    case 0x2090a11b:
        out->instanceID = 0x14585a1f;
        break;
    case 0x1f2a25b6:
        out->instanceID = 0x71981adc;
        break;
    case 0x1a4e0708:
        out->instanceID = 0x188ebff2;
        break;
    case 0x2a5147a9:
        out->instanceID = 0x062b8bc1;
        break;
    case 0x37148141:
        out->instanceID = 0xda273036;
        break;
    case 0x372e2c04:
        out->instanceID = 0x3f185edb;
        break;
    case 0x4178b8e8:
        out->instanceID = 0x5983fbdf;
        break;
    case 0x449c040f:
        out->instanceID = 0xe4d0e7f3;
        break;
    case 0x441cd3e6:
        out->instanceID = 0xe7792790;
        break;
    case 0x47c10953:
        out->instanceID = 0x62e861d9;
        break;
    case 0x4e3f7777:
    case 0xbdd15f3d:
        out->instanceID = 0x8c1f0aa3;
        break;
    case 0x65672ade:
        out->instanceID = 0x89b74761;
        break;
    case 0x72c49181:
        out->instanceID = 0xd1376095;
        break;
    case 0xbc1041e6:
        out->instanceID = 0xa0cc166e;
        break;
    case 0x8f963dcb:
        out->instanceID = 0xc2d3ce6f;
        break;
    case 0x98e03c0d:
        out->instanceID = 0x7609745a;
        break;
    case 0x99e92f05:
        out->instanceID = 0xb390f699;
        break;
    case 0x9ad7d4aa:
        out->instanceID = 0xb6dc61a6;
        break;
    case 0x9ea3031a:
        out->instanceID = 0xe04dd8b1;
        break;
    case 0xb8669ec9:
        out->instanceID = 0x9fe7f178;
        break;
    case 0x7d433fad:
    case 0xc0b74287:
        out->instanceID = 0x6920384d;
        break;
    case 0xbcd73e89:
        out->instanceID = 0xf56244d2;
        break;
    case 0xc15695da:
        out->instanceID = 0xf6eb7174;
        break;
    case 0xccc35c46:
        out->instanceID = 0xdc1b3879;
        break;
    case 0xdfad9f51:
        out->instanceID = 0xb49e7fb2;
        break;
    case 0xf670aa43:
        out->instanceID = 0xf5f1b0d7;
        break;
    }
    return out;
}
