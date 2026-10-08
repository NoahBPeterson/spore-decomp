// Slice s00eede20 -- creature/vehicle noun factory helpers (large inlined dispatch).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// NOTE: 0x00eede20 is complete. The other four functions in this slice (222-560 bytes of inlined
// noun-creation dispatch) are still partial stubs.

struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey() {}
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
struct Vector3 { float x, y, z; };
struct Quaternion;

#define SLOT(n) virtual void s##n();

// cSpatialObject-like subobject (lives at noun+0x34 and is what Cast(0x1186577) returns).
struct Spatial {
    SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10)
    virtual int GetV2c();                                      // +0x2c
    virtual int GetV30();                                      // +0x30
    SLOT(13)
    virtual void SetPosition(const Vector3* p);                // +0x38
    virtual void SetOrientation(const Quaternion* q);          // +0x3c
    virtual void SetScale(float f);                            // +0x40
    SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26)
    SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36)
    virtual void SetModelKey(const ResourceKey* k);            // +0x94
    virtual const ResourceKey* GetModelKey();                  // +0x98
    uint32_t pad4[0x4c / 4 - 0];                               // +0x04..+0x50
    uint32_t mFlags;                                           // +0x50
    uint32_t pad54[(0xa4 - 0x54) / 4];                         // to +0xa4
    uint8_t mPadA4[3];
    uint8_t mbFlagA7;                                          // +0xa7
    uint8_t mDataA8[4];                                        // +0xa8
};

struct Noun {
    virtual int AddRef();                                      // +0
    virtual int Release();                                     // +4
    SLOT(2)
    virtual void* Cast(uint32_t typeId);                       // +0xc
    SLOT(4) SLOT(5) SLOT(6) SLOT(7)
    virtual uint32_t GetNounID();                              // +0x20
    SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20)
    virtual void SetFlag54(int v);                             // +0x54
    uint32_t pad4[(0x18 - 4) / 4];
    int mField18;                                              // +0x18
    int mField1c;                                              // +0x1c
    uint32_t pad20[(0x34 - 0x20) / 4];
    Spatial mSpatial;                                          // +0x34
    void* FUN_00b18530();                                      // cGameData helper (model/world lookup)
    void FUN_00c6f770(int a, int b, int c);                    // ret 0xc
    void FUN_00eab830(const ResourceKey* k);                   // copies key to +0x108 (ret 4)
    void FUN_00eac530();
    void FUN_00f0d8b0();
};

struct Vehicle : public Noun {
    void Init(int purpose, int locomotion, ResourceKey key);   // 0x00ca6630 (ret 0x14)
};

struct Herd {
    uint32_t pad0[0x88 / 4];
    uint32_t mField88;                                         // +0x88
    uint32_t pad8c[(0xf0 - 0x8c) / 4];
    uint32_t mFieldF0;                                         // +0xf0
    uint32_t padf4[(0x108 - 0xf4) / 4];
    float mField108;                                           // +0x108
    void FUN_00c6ace0(int b);                                  // ret 4
};
struct HerdPos {
    void SetPosition(const Vector3* p);                        // 0x00c6ba20 (ret 4)
};
struct Creature {
    HerdPos* FUN_00c04590();                                   // plain thiscall
};
struct Ufo {
    void FUN_00c3aa40(int a, int b);                           // ret 8
};
struct SpeciesProfile;
struct SpeciesMgr {
    SpeciesProfile* GetProfile(const ResourceKey* k);          // 0x004df550 (ret 4)
};
struct NounMgr {
    Noun* CreateInstance(uint32_t nounId);                                                    // 0x00b20c60
    Noun* FUN_00b23650(uint32_t type, uint32_t inst, int z, const Vector3* p, const Quaternion* q);  // ret 0x14
    Herd* CreateHerd(const Vector3* p, SpeciesProfile* prof, int size, bool owned, int pers, int nest);  // ret 0x18
    void* GetAvatar();                                                                        // 0x00b1fdb0
    Noun* FUN_00bbd160();
    void FUN_00b22960();
};
struct IPropList {
    virtual void v0();
    virtual int Release();
};
template<typename T>
struct IntrusivePtr {
    T* mpObject;
    IntrusivePtr() : mpObject(0) {}
    ~IntrusivePtr() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T** operator&() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};
struct PropMgr {
    SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10)
    virtual void GetPropertyList(uint32_t instance, uint32_t group, IPropList** out);  // +0x2c
};
struct GameState { char pad[0xcc]; int mMode; };

NounMgr* __cdecl NounManager();                                  // 0x00b3d300
SpeciesMgr* __cdecl FUN_00401090();                              // species manager
PropMgr* __cdecl FUN_0067de30();                                 // PropertyManager
void __cdecl FUN_00eeca60(ResourceKey* out, const ResourceKey* in);
Spatial* __cdecl FUN_00b18e00(void* noun);                       // Cast(0x1186577) or 0
Noun* __cdecl FUN_00c9f060(void* obj);
Noun* __cdecl FUN_00eec0b0(void* noun);                          // Cast(0x74e0069) or 0
void* __cdecl FUN_00eecba0(ResourceKey* k);
int __cdecl FUN_00c9ed00(void* p);
int __cdecl FUN_00c9ed80(void* p);
void __cdecl FUN_00d996b0(int a9, int a7, const Vector3* pos, void* where);
void* __cdecl FUN_00c099e0(const Vector3* p, SpeciesProfile* prof, int n, Herd* herd, int a, int b);
void __cdecl FUN_00d2e580();
Noun* __cdecl FUN_00f213f0(IPropList* list, int a7, int a6);
void __cdecl FUN_00eeccb0(void* herdish);
char __cdecl FUN_005b1c80(const Quaternion* q, const void* ref);
void __cdecl FUN_00eed720(int a7, Spatial* sp, void* dst);
float __cdecl FUN_00eec5c0(Noun* n);
struct FlagHolder { char FUN_00f254d0(); };
struct ObjTail {
    char FUN_00f25330();
    void FUN_00f924e0(float f);                                  // ret 4
};
extern GameState* gpGameState;       // 0x016c7aa4
extern Vector3 gVec3Zero;            // 0x016c78cc
extern char gQuatRef[];              // 0x015ac960

// @ 0x00eede20
Noun* __cdecl FUN_00eede20(const ResourceKey* key, const Vector3* pos, const Quaternion* ori, float scale,
                           bool bOwned, int a6, int a7, int a8, int a9)
{
    ResourceKey out;
    ResourceKey k;
    Noun* result = 0;
    Spatial* sp;
    FUN_00eeca60(&out, key);
    bool bFlag = true;

    switch (out.typeID) {
    case 0x3a2511e:
    case 0x2a8fb3f:
        result = NounManager()->FUN_00b23650(out.typeID, out.instanceID, 0, pos, ori);
        result->mField1c = a6;
        if (result->FUN_00b18530()) {
            if (!((FlagHolder*)result->FUN_00b18530())->FUN_00f254d0()) {
                Spatial* const fs = FUN_00b18e00(result);
                fs->mFlags = fs->mFlags & 0xfffffdff;
            }
        }
        break;
    case 0x18c88e4:
        {
            Noun* obj = NounManager()->CreateInstance(0x18c88e4);
            obj->FUN_00c6f770(0x2ae5ba7, 0, out.instanceID);
            result = FUN_00c9f060(obj);
        }
        break;
    case 0x403df5c:
        {
            Noun* obj = NounManager()->FUN_00bbd160();
            if (obj) obj->AddRef();
            k.instanceID = out.instanceID;
            k.groupID = out.groupID;
            k.typeID = 0x2f4e681b;
            obj->mSpatial.SetModelKey(&k);
            result = (Noun*)obj->Cast(0x17f243b);
            obj->Release();
        }
        break;
    case 0x74e0069:
        {
            Noun* obj = NounManager()->CreateInstance(0x74e0069);
            if (obj) {
                obj->FUN_00eab830(key);
                obj->FUN_00eac530();
                sp = FUN_00b18e00(obj);
                if (sp) {
                                    k.instanceID = out.instanceID;
                    k.groupID = out.groupID;
                    k.typeID = 0x2f4e681b;
                    sp->SetModelKey(&k);
                }
                result = FUN_00eec0b0(obj);
            }
            bFlag = false;
        }
        break;
    case 0x7b38ba7:
        {
            Noun* obj = NounManager()->CreateInstance(0x7b38ba7);
            if (obj) {
                obj->FUN_00eab830(key);
                obj->FUN_00f0d8b0();
                sp = (Spatial*)obj->Cast(0x1186577);
                        k.instanceID = out.instanceID;
                k.groupID = out.groupID;
                k.typeID = 0x2f4e681b;
                sp->SetModelKey(&k);
                result = (Noun*)obj->Cast(0x7b38ba7);
            }
            bFlag = false;
        }
        break;
    case 0x2b978c46:
        {
            SpeciesProfile* prof = FUN_00401090()->GetProfile(&out);
            if (prof) {
                Herd* herd = NounManager()->CreateHerd(pos, prof, 1, bOwned, 0xb, 0);
                if (herd) {
                    herd->FUN_00c6ace0(1);
                    herd->mField88 = 0xdada0591;
                    herd->mFieldF0 = 0;
                    herd->mField108 = 128.0f;
                    void* who = NounManager()->GetAvatar();
                    if (!bOwned) {
                        who = FUN_00c099e0(pos, prof, 1, herd, 0, 0);
                        if (a7 != 0 && gpGameState->mMode == 2)
                            FUN_00d996b0(a9, a7, pos, (char*)who + 0x1648);
                    }
                    result = FUN_00c9f060(who);
                    if (bOwned) FUN_00d2e580();
                }
            }
            bFlag = false;
        }
        break;
    case 0x2399be55:
        {
            result = NounManager()->CreateInstance(0x70703b3);
            result->SetFlag54(0);
            result->mSpatial.SetModelKey(&out);
            result = (Noun*)result->Cast(0x17f243b);
        }
        break;
    case 0x24682294:
        {
            Vehicle* veh = (Vehicle*)NounManager()->CreateInstance(0x18c6de8);
            result = FUN_00c9f060(veh);
            Spatial* const vs = &veh->mSpatial;
            vs->SetModelKey(&out);
            void* const pDef = FUN_00eecba0(&out);
            int const purpose = FUN_00c9ed00(pDef);
            int const locomotion = FUN_00c9ed80(pDef);
            result->mField1c = a6;
            veh->Init(purpose, locomotion, *vs->GetModelKey());
            if (a7 != 0 && gpGameState->mMode == 2)
                FUN_00d996b0(a9, a7, pos, (char*)veh + 0xb00);
        }
        break;
    case 0x476a98c7:
        {
            Vehicle* veh = (Vehicle*)NounManager()->CreateInstance(0x18c6de8);
            if (veh)
                result = (Noun*)veh->Cast(0x17f243b);
            else
                result = 0;
            result->mField1c = a6;
            veh->Init(2, 0, out);
        }
        break;
    case 0xf0000001:
        {
            IntrusivePtr<IPropList> plist;
            PropMgr* pm = FUN_0067de30();
            pm->GetPropertyList(key->instanceID, key->groupID, &plist);
            result = FUN_00f213f0(plist, a7, a6);
        }
        break;
    default:
        {
            result = NounManager()->CreateInstance(0x18c88e4);
            result->FUN_00c6f770(0x750f022, -1, 0);
        }
        break;
    }

    if (result) {
        sp = (Spatial*)result->Cast(0x1186577);
        if (bFlag) sp->mFlags |= 0x8000;
        sp->SetPosition(pos);
        sp->SetOrientation(ori);
        sp->SetScale(scale);
        uint32_t nounId = result->GetNounID();
        switch (nounId) {
        case 0x18eb45e:
            {
                Creature* cr = (Creature*)result->Cast(0xd0036e08);
                cr->FUN_00c04590()->SetPosition(pos);
                FUN_00eeccb0(cr);
            }
            break;
        case 0x18ebadc:
            {
                Ufo* ufo = (Ufo*)result->Cast(0xb033b403);
                if ((pos->x != gVec3Zero.x || pos->y != gVec3Zero.y || pos->z != gVec3Zero.z) &&
                    FUN_005b1c80(ori, gQuatRef)) {
                    Spatial* const us = (Spatial*)((char*)ufo + 0x34);
                    ufo->FUN_00c3aa40(us->GetV2c(), us->GetV30());
                }
            }
            break;
        case 0x403df5c:
            {
                Noun* cn = (Noun*)result->Cast(0x403df5f);
                cn->mSpatial.SetScale(5.0f);
            }
            break;
        }
        result->mField1c = a6;
        result->mField18 = a7;
        if (a7) {
            FUN_00eed720(a7, sp, sp->mDataA8);
            sp->mbFlagA7 = 1;
        }
        ObjTail* tail = (ObjTail*)result->Cast(0x13f94d4);
        if (tail && result->FUN_00b18530() && ((ObjTail*)result->FUN_00b18530())->FUN_00f25330())
            tail->FUN_00f924e0(FUN_00eec5c0(result));
    }
    NounManager()->FUN_00b22960();
    return result;
}

// ================================================================ 0x00eee530
void __cdecl FUN_00eee530(void)
{
}

// ================================================================ 0x00eee760
void __cdecl FUN_00eee760(void)
{
}

// ================================================================ 0x00eee970
int __stdcall FUN_00eee970(int a, int b, int c)
{
    (void)a; (void)b; (void)c;
    return 0;
}

// ================================================================ 0x00eeea50
void __cdecl FUN_00eeea50(void)
{
}
