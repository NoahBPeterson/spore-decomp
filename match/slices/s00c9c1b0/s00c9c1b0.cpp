// Slice s00c9c1b0 -- SP::cTribeTool / Simulator helpers.
//   0x00c9c1b0  cTribeTool::RemoveOwner
//   0x00c9c250  cTribeTool::SetOwnerIface
//   0x00c9c2c0  FUN_00c9c2c0            (clear a growable byte buffer)
//   0x00c9c2e0  FUN_00c9c2e0            (fetch tool noun via owner)
//   0x00c9c310  cTribeTool::Serialize_Write
//   0x00c9c3c0  cTribeTool::Serialize_Read
//   0x00c9c500  cTribeTool::SetupTribeHut
//   0x00c9c5e0  cTribeTool::GetToolPosition
//   0x00c9c680  cTribeHut::RefreshModelProps
//   0x00c9cec0  FUN_00c9cec0            (tribe tool data table)
//   0x00c9cee0  cTribeTool::AsInterface
//   0x00c9cf70  cTribeToolData::IsNotType10
//   0x00c9cf90  FUN_00c9cf90            (strike point counter)
//   0x00c9cfd0  cTribeTool::SpawnToolIcon
//   0x00c9d030  cTribeTool::ReleaseToolIcon
//   0x00c9d090  cTribeTool::GetToolTypeAsCharStar
//   0x00c9d110  cTribeTool::GetToolIconKey
//   0x00c9d160  cTribeTool::GetTimeSinceCreation
//   0x00c9d1c0  cTribeTool::GetTimeSinceLastUse
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc)
#include "types.h"

// ------------------------------------------------------------------ EA IO
namespace EA { namespace IO {
    void WriteUint32(void* pStream, const void* pData, int count, int flags);  // 0093aa70
    void ReadInt32(void* pStream, const void* pData, int count, int flags);    // 0093a780
} }

// ------------------------------------------------------------------ ref counted iface
struct IRefCounted {
    virtual void AddRef();                           // +0x00
    virtual void Release();                          // +0x04
};

// ------------------------------------------------------------------ spatial object
struct cSpatialObject {
    uint8_t pad00[0x98];
    virtual const void* GetModelKey();               // +0x98 0x00c9c680 slot
};

// ------------------------------------------------------------------ combatant
struct cCombatant {
    uint8_t pad00[0x120];
};

// ------------------------------------------------------------------ Property system
struct ResourceKey {
    uint32_t instance, type, group;
};

// Property: type word at +0x12, flags word at +0x10 (0x30 = external pointer).
struct Property {
    void*    mpData;                                 // +0x00
    uint32_t pad04[3];
    uint16_t mnFlags;                                // +0x10
    uint16_t mnType;                                 // +0x12
    void* GetValuePtr()
    {
        if (mnFlags & 0x30)
            return mpData;
        if (mnType != 0)
            return this;
        return 0;
    }
};

struct PropertyList {
    virtual int AddRef();                            // +0x00
    virtual int Release();                           // +0x04
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool HasProperty(uint32_t id);           // +0x1c
    virtual void v8(); virtual void v9();
    virtual Property* GetProperty(uint32_t id);      // +0x28
};

struct IPropManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppOut); // +0x2c
};

// ------------------------------------------------------------------ serializers
struct cVarListSerializer {
    uint8_t pad00[0xa10];
    cVarListSerializer(void* owner, const void* key, uint32_t group);          // 00692f90
    bool Serialize(void* pStream);                                              // 00692900
    bool Read(void* pStream);                                                   // 00693e10
};

// An I/O serializer: slot 0x18 returns the byte-stream writer, slot 0x20 returns
// the sub-serializer used to obtain it.
struct IStreamWriter {
    virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
    virtual void w04(); virtual void w05();
    virtual void* GetWriter();                       // +0x18
};

struct ISerializerStream {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual IStreamWriter* GetWriterSerializer();    // +0x20
};

// Game-data base serializers (thiscall members of the game-data base object).
struct cGameDataBase {
    bool Write(void* pStream);                       // 00b18590
    bool Read(void* pStream);                        // 00b18600
};
struct cSpatialObjectBase {
    bool Write(void* pStream);                       // 00c88a90
    bool Read(void* pStream);                        // 00c88b00
};
struct cCombatantBase {
    bool Write(void* pStream);                       // 00bfc4a0
    bool Read(void* pStream);                        // 00bfc540
};

// Spatial-object interface used by Serialize_Read tail.
struct ISpatialRef {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s0a();
    virtual void* v2c();                             // +0x2c
    virtual void s0c(); virtual void s0d();
    virtual void  v38(void* arg);                    // +0x38
    virtual void s0f(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s1a();
    virtual void s1b(); virtual void s1c(); virtual void s1d(); virtual void s1e();
    virtual void s1f(); virtual void s20(); virtual void s21(); virtual void s22();
    virtual void s23(); virtual void s24(); virtual void s25();
    virtual const ResourceKey* GetModelKey();        // +0x98
};

// ------------------------------------------------------------------ timers
struct cSPTimer {
    uint8_t pad00[0x10];
    bool  IsRunning();                                                          // 00feba90
    unsigned long long GetElapsedTime();                                        // 00bc3190
};

// ------------------------------------------------------------------ globals
extern const uint32_t kHutDamageHi;                  // 0157c3a0
extern const uint32_t kHutDamageMd;                  // 0157c39c
extern const uint32_t kHutDamageLo;                  // 0157c398
extern const ResourceKey gDefaultResourceKey;        // 01699a04 (default position)
extern ResourceKey gSerializableKey;                 // 0157c3d0
extern float g_13f9428;                              // 0.001
extern float g_14745d8;                              // FLT_MAX
extern void** g_13f94d4;                             // cCombatant interface id (address)
extern const uint32_t kGameModeHut;                  // 01654c04

struct cTribeToolData {
    uint8_t  pad00[0x10];
    int      mField10;                               // +0x10
    int      mField14;                               // +0x14
    uint8_t  pad18[0x38 - 0x18];
    int      mField38;                               // +0x38
    bool IsNotType10();                              // 00c9cf70
};
extern cTribeToolData* gTribeTools[12];              // 01699a14

// ------------------------------------------------------------------ external helpers
float   FUN_00bfc490(void* p);                      // 00bfc490
void  FUN_00bfc720(void* p);                         // 00bfc720
void  FUN_00c3f2d0(void* p);                         // 00c3f2d0
void* FUN_00ac0450(void* p);                         // 00ac0450
void  FUN_00c8b2e0(void* p);                         // 00c8b2e0
void  FUN_00c987b0(void);                            // 00c987b0
void  FUN_00c3f160(void* pObj, int id);              // 00c3f160  SetEffectId
void* FUN_0059aed0(void* pOut, const void* pKey, void* pIn);  // 0059aed0
bool  FUN_0059ab70(const void* p);                   // 0059ab70
void* FUN_006bb640();                                // 006bb640
void* FUN_00b18460(void* p);                         // 00b18460
uint32_t FUN_011e0810(float f);                      // 011e0810
void* GetCurrentGameMode();                          // 00b5b800
void* NounManager();                                 // 00b3d300
void* PlanetModel();                                 // 00b3d350
void* PropertyManager();                             // 0067de30

struct cGameNounManager {
    void* CreateNoun(const void* key);               // 00b20c60
    void  RemoveNoun(void* pNoun);                   // 00b225d0
};

// Community view of the tool object (base at +0x0).
struct cCommunity {
    void func54h(int arg);                           // 00c88670
};

// ------------------------------------------------------------------ tool object
// Slot indices are expressed as virtual functions so that call offsets (0x48,
// 0x4c, 0x58, 0x5c, 0x98) land correctly.
class cTribeTool {
public:
    // --- vtable (this+0x00)
    virtual void     v00(); // +0x00
    virtual void     v01(); virtual void     v02(); virtual void     v03();
    virtual void     v04(); virtual void     v05(); virtual void     v06();
    virtual void     v07(); virtual void     v08(); virtual void     v09();
    virtual void     v0a(); virtual void     v0b();
    virtual uint32_t GetPositionKey();               // +0x30
    virtual void     v0d(); virtual void     v0e(); virtual void     v0f();
    virtual void     v10(); virtual void     v11();
    virtual void     SetOwnerKey(uint32_t key);      // +0x48
    virtual uint32_t GetOwnerKey();                  // +0x4c
    virtual void     v14(); virtual void     v15();
    virtual uint32_t GetToolType();                  // +0x58
    virtual const void* GetModelKey();               // +0x5c
    virtual void     v18(); virtual void     v19();

    // --- data
    uint8_t  pad04[0x2c - 0x04];
    IRefCounted* mpOwner2C;                          // +0x2c
    uint8_t  pad30[0x34 - 0x30];
    uint8_t  mSpatial[0x108 - 0x34];                 // +0x34 spatial object
    uint8_t  pad108[0x120 - 0x108];
    uint8_t  mCombatant[0x1e8 - 0x120];              // +0x120 combatant sub-object
    union {
        struct {
            int      mDamageHi;                      // +0x1e8
            int      mDamageHiP1;                    // +0x1ec
            int      mDamageHiP2;                    // +0x1f0
            int      mDamageMd;                      // +0x1f4
            int      mDamageMdP1;                    // +0x1f8
            int      mDamageMdP2;                    // +0x1fc
            int      mDamageLo;                      // +0x200
            int      mDamageLoP1;                    // +0x204
            int      mDamageLoP2;                    // +0x208
            int      mDamageHiQ1;                    // +0x20c
            int      mDamageHiQ2;                    // +0x210
            int      mDamageHiQ3;                    // +0x214
            uint8_t  pad218[0x220 - 0x218];
        };
        struct {
            uint8_t  pad1e8[0x200 - 0x1e8];
            cSPTimer mTimer200;                      // +0x200  (creation timer)
            uint8_t  pad210[0x220 - 0x210];
        };
    };
    cSPTimer mTimer220;                              // +0x220  (last-use timer)
    void*    mpNoun;                                 // +0x230
    void*    mpOwner234;                             // +0x234
    uint8_t  pad238[0x240 - 0x238];
    int      mStrikeCount240;                        // +0x240
    int      mStrikeCount244;                        // +0x244
    void*    mpField248;                             // +0x248

    // --- methods
    void  RemoveOwner();                             // 00c9c1b0
    void  SetOwnerIface(void* p);                    // 00c9c250
    bool  Serialize_Write(void* pStream);            // 00c9c310
    bool  Serialize_Read(void* pStream);             // 00c9c3c0
    void  SetupTribeHut(int arg);                    // 00c9c500
    uint32_t GetToolPosition(void* pOut);            // 00c9c5e0
    bool  HasToolNoun();                             // 00c9c2e0
    void  RefreshModelProps();                       // 00c9c680
    void* AsInterface(void* pIID);                   // 00c9cee0
    void  AddStrikePoint(bool b);                    // 00c9cf90
    uint32_t SpawnToolIcon();                        // 00c9cfd0
    void  ReleaseToolIcon();                         // 00c9d030
    const char* GetToolTypeAsCharStar();             // 00c9d090
    uint32_t GetToolIconKey();                       // 00c9d110
    float GetTimeSinceCreation();                    // 00c9d160
    float GetTimeSinceLastUse();                     // 00c9d1c0
};

// A separate object with +0x5c returning a uint (noun spawner).
struct cToolNounSpawner {
    virtual void n00(); virtual void n01(); virtual void n02(); virtual void n03();
    virtual void n04(); virtual void n05(); virtual void n06(); virtual void n07();
    virtual void n08(); virtual void n09(); virtual void n0a(); virtual void n0b();
    virtual void n0c(); virtual void n0d(); virtual void n0e(); virtual void n0f();
    virtual void n10(); virtual void n11(); virtual void n12(); virtual void n13();
    virtual void n14(); virtual void n15(); virtual void n16(); virtual void n17();
    virtual void n18(); virtual void n19(); virtual void n1a(); virtual void n1b();
    virtual void n1c(); virtual void n1d(); virtual void n1e(); virtual void n1f();
    virtual void n20(); virtual void n21(); virtual void n22(); virtual void n23();
    virtual void n24(); virtual void n25(); virtual void n26(); virtual void n27();
    virtual void n28(); virtual void n29(); virtual void n2a(); virtual void n2b();
    virtual void n2c(); virtual void n2d(); virtual void n2e(); virtual uint32_t GetOwnerNoun(); // +0x5c
};

// A growable byte buffer: begin/end pointers.
struct cByteBuffer {
    uint8_t* mpBegin;                                // +0x00
    uint8_t* mpEnd;                                  // +0x04
};

// @ 0x00c9c2c0
void __stdcall FUN_00c9c2c0(cByteBuffer* pBuf)
{
    if (pBuf->mpBegin != pBuf->mpEnd) {
        *pBuf->mpBegin = 0;
        pBuf->mpEnd = pBuf->mpBegin;
    }
}

// @ 0x00c9c2e0
bool cTribeTool::HasToolNoun()
{
    if (mDamageMdP2 == 0)                            // +0x1fc (tool type)
        return false;
    cToolNounSpawner* spawner = (cToolNounSpawner*)((uint8_t*)this - 0x34);
    uint32_t noun = spawner->GetOwnerNoun();         // vtable +0x5c
    return ((cTribeTool*)noun)->GetToolType() != 0;  // vtable +0x58 on noun+0x120
}

// ==================================================================
// @ 0x00c9c1b0
void cTribeTool::RemoveOwner()
{
    if (mpNoun != 0) {
        IRefCounted* p = (IRefCounted*)mpNoun;
        mpNoun = 0;
        p->Release();
    }
    FUN_00bfc720(mCombatant);
    if (mpOwner234 != 0) {
        FUN_00c3f2d0(0);
        ((cGameNounManager*)NounManager())->RemoveNoun(mpOwner234);
        void* p = mpOwner234;
        mpOwner234 = 0;
        if (p != 0)
            ((IRefCounted*)p)->Release();
    }
    if (mpOwner2C != 0) {
        IRefCounted* p = mpOwner2C;
        mpOwner2C = 0;
        p->Release();
    }
    FUN_00ac0450(mSpatial + (0x108 - 0x34));
    FUN_00c8b2e0(mSpatial);
}

// @ 0x00c9c250
void cTribeTool::SetOwnerIface(void* p)
{
    void* old = mpNoun;
    if (p != old) {
        if (p != 0)
            ((IRefCounted*)p)->AddRef();
        mpNoun = p;
        if (old != 0)
            ((IRefCounted*)old)->Release();
    }
    if (mpNoun != 0) {
        uint32_t key = ((cTribeTool*)mpNoun)->GetOwnerKey();
        SetOwnerKey(key);
    }
}

// @ 0x00c9c310
bool cTribeTool::Serialize_Write(void* pStream)
{
    IStreamWriter* pWriter = ((ISerializerStream*)pStream)->GetWriterSerializer();
    uint32_t version = 0xee02c7;
    void* pIO = pWriter->GetWriter();
    EA::IO::WriteUint32(pIO, &version, 1, 0);
    bool ok = ((cGameDataBase*)this)->Write(pStream)
           && ((cSpatialObjectBase*)mSpatial)->Write(pStream)
           && ((cCombatantBase*)mCombatant)->Write(pStream);
    cVarListSerializer vs(this, &gSerializableKey, 0x1a80d26);
    if (ok) {
        if (vs.Serialize(pStream))
            return true;
    }
    return false;
}

// @ 0x00c9c3c0
bool cTribeTool::Serialize_Read(void* pStream)
{
    IStreamWriter* pWriter = ((ISerializerStream*)pStream)->GetWriterSerializer();
    void* pIO = pWriter->GetWriter();
    uint32_t version = 0;
    EA::IO::ReadInt32(pIO, &version, 1, 0);
    bool ok = ((cGameDataBase*)this)->Read(pStream)
           && ((cSpatialObjectBase*)mSpatial)->Read(pStream)
           && ((cCombatantBase*)mCombatant)->Read(pStream);
    cVarListSerializer vs(this, &gSerializableKey, 0x1a80d26);
    if (ok) {
        if (vs.Read(pStream)) {
            ok = true;
            goto done;
        }
    }
    ok = false;
done:
    {
        void* pm = PlanetModel();
        if (*(void**)((uint8_t*)pm + 0x24) != 0) {
            ISpatialRef* pSpatial = (ISpatialRef*)mSpatial;
            pSpatial->v38(pSpatial->v2c());
        }
    }
    return ok;
}

// @ 0x00c9c500
void cTribeTool::SetupTribeHut(int arg)
{
    if (GetCurrentGameMode() == &kGameModeHut && mStrikeCount240 == 0) {
        void* pNoun = ((cGameNounManager*)NounManager())->CreateNoun((const void*)0x2e72cae);
        void* pHut = 0;
        if (pNoun != 0)
            pHut = (void*)((void* (*)(void*, int))(*(void**)((uint8_t*)*(void**)pNoun + 0xc)))(pNoun, 0x2e71a5a);
        mpNoun = pHut;
        if (mpNoun != 0)
            FUN_00c3f2d0(mSpatial);
    }
    ((cCommunity*)this)->func54h(arg);
    if (GetCurrentGameMode() == &kGameModeHut) {
        FUN_00c3f160(mpNoun, 0);
    }
    if (mDamageMdP2 != 0) {
        FUN_00c987b0();
    }
}

// @ 0x00c9c5e0
uint32_t cTribeTool::GetToolPosition(void* pOut)
{
    uint32_t key = GetPositionKey();                 // vtable +0x30
    (void)key;
    float v[3];
    float* p = (float*)FUN_0059aed0(&v[0], &gDefaultResourceKey, (void*)key);
    v[0] = p[0]; v[1] = p[1]; v[2] = p[2];
    float* dst = (float*)pOut;
    if (FUN_0059ab70(&v[0])) {
        dst[0] = v[0]; dst[1] = v[1]; dst[2] = v[2];
    } else {
        dst[0] = ((const float*)&gDefaultResourceKey)[0];
        dst[1] = ((const float*)&gDefaultResourceKey)[1];
        dst[2] = ((const float*)&gDefaultResourceKey)[2];
    }
    return 0;
}

// @ 0x00c9c680
void cTribeTool::RefreshModelProps()
{
    const ResourceKey* pKey = ((ISpatialRef*)mSpatial)->GetModelKey();  // vtable +0x98
    uint32_t key0 = ((const uint32_t*)pKey)[0];
    uint32_t key1 = ((const uint32_t*)pKey)[1];
    uint32_t key2 = ((const uint32_t*)pKey)[2];
    mDamageLo  = key0; mDamageMd  = key0; mDamageHi  = key0; mDamageHiQ1 = key0;
    mDamageLoP1 = key1; mDamageMdP1 = key1; mDamageHiP1 = key1; mDamageHiQ2 = key1;
    mDamageLoP2 = key2; mDamageMdP2 = key2; mDamageHiP2 = key2; mDamageHiQ3 = key2;

    PropertyList* pList = 0;
    IPropManager* pm = (IPropManager*)PropertyManager();
    if (!pm->GetPropertyList(key0, key2, &pList))
        goto done;

    if (pList->HasProperty(kHutDamageHi)) {
        Property* p = pList->GetProperty(kHutDamageHi);
        uint32_t* v = (uint32_t*)p->GetValuePtr();
        mDamageLo = v[0]; mDamageLoP1 = v[1]; mDamageLoP1 = 0xb1b104; mDamageLoP2 = 0x2be764e2;
    }
    if (pList->HasProperty(kHutDamageMd)) {
        Property* p = pList->GetProperty(kHutDamageMd);
        uint32_t* v = (uint32_t*)p->GetValuePtr();
        mDamageMd = v[0]; mDamageMdP1 = v[1]; mDamageMdP1 = 0xb1b104; mDamageMdP2 = 0x2be764e2;
    }
    if (pList->HasProperty(kHutDamageLo)) {
        Property* p = pList->GetProperty(kHutDamageLo);
        uint32_t* v = (uint32_t*)p->GetValuePtr();
        mDamageHi = v[0]; mDamageHiP1 = v[1]; mDamageHiP1 = 0xb1b104; mDamageHiP2 = 0x2be764e2;
    }
done:
    if (pList != 0)
        pList->Release();
}

// @ 0x00c9cee0
void* cTribeTool::AsInterface(void* pIID)
{
    if ((int)pIID <= (int)g_13f94d4) {
        if (pIID == (void*)g_13f94d4) {
            if (this != 0)
                return mCombatant + (0x1e8 - 0x120);
            return 0;
        }
        if (pIID == (void*)0xe89adf71) {
            if (this != 0)
                return mCombatant + (0x120 - 0x120);
            return 0;
        }
        if (pIID != (void*)0x0116d858) {
            void* p = FUN_00b18460(pIID);
            if (p != 0)
                return p;
            return 0;
        }
        return this;
    }
    if (pIID == (void*)0x102a041a) {
        if (this != 0)
            return mSpatial + (0x108 - 0x34);
        return 0;
    }
    {
        void* p = FUN_00b18460(pIID);
        if (p != 0)
            return p;
    }
    return 0;
}

// @ 0x00c9cf90
void cTribeTool::AddStrikePoint(bool b)
{
    if (b) {
        mStrikeCount240++;
        mStrikeCount244++;
    } else {
        mStrikeCount240--;
        mStrikeCount244--;
    }
}

// @ 0x00c9cfd0
uint32_t cTribeTool::SpawnToolIcon()
{
    (void)0;
    int type = mDamageMdP2;                          // +0x1fc (tool type)
    cTribeToolData* data;
    if ((unsigned)(type - 1) <= 0xa)
        data = gTribeTools[type];
    else
        data = gTribeTools[0];
    float t = 1.0f - FUN_00bfc490(mCombatant);
    float v = t * (float)data->mField38;
    return FUN_011e0810(v * g_13f9428);
}

// @ 0x00c9d030
void cTribeTool::ReleaseToolIcon()
{
    IRefCounted* p = 0;
    if (PlanetModel() != 0)
        p = *(IRefCounted**)((uint8_t*)PlanetModel() + 0x24);
    if (p != 0 && mpField248 != 0) {
        void* vt = *(void**)p;
        ((void (*)(void*, int))(*(void**)((uint8_t*)vt + 0x58)))(mpField248, 1);
        mpField248 = 0;
    }
}
// @ 0x00c9d090
const char* cTribeTool::GetToolTypeAsCharStar()
{
    switch (mDamageMdP2) {                           // +0x1fc (tool type)
    case 1:  return "Torch Tool";
    case 2:  return "Axe Tool";
    case 3:  return "Spear Tool";
    case 4:  return "Recruiting Horn";
    case 5:  return "Recruiting Shakable Percussion Instrument";
    case 6:  return "Recruiting Didgeridoo";
    case 7:  return "Heal Tool";
    case 8:  return "Gather Tool";
    case 9:  return "Firepit - Throw Party $5";
    case 10: return "Fish Tool";
    default: return "";
    }
}

// @ 0x00c9d110
uint32_t cTribeTool::GetToolIconKey()
{
    uint32_t type = GetToolType();
    cTribeToolData* data;
    if ((unsigned)(type - 1) <= 0xa)
        data = gTribeTools[type];
    else
        data = gTribeTools[0];
    return (uint32_t)data->mField10;
}

// @ 0x00c9d160
float cTribeTool::GetTimeSinceCreation()
{
    if (mTimer200.IsRunning()) {
        unsigned long long t = mTimer200.GetElapsedTime();
        return (float)t * g_13f9428;
    }
    return g_14745d8;
}

// @ 0x00c9d1c0
float cTribeTool::GetTimeSinceLastUse()
{
    if (mTimer220.IsRunning()) {
        unsigned long long t = mTimer220.GetElapsedTime();
        return (float)t * g_13f9428;
    }
    return 0.0f;
}

// ==================================================================
// @ 0x00c9cec0
uint32_t FUN_00c9cec0(int i)
{
    if ((unsigned)(i - 1) <= 0xa)
        return (uint32_t)gTribeTools[i];
    return (uint32_t)gTribeTools[0];
}

// @ 0x00c9cf70
bool cTribeToolData::IsNotType10()
{
    return mField14 != 10;
}
