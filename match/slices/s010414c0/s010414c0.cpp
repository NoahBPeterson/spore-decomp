// Slice s010414c0: {anonymous}::RegisterShaderDataInfo (0x010414c0, 1737 bytes).
// Rebuilds the list of shader data infos (vector of 0x54-byte records at +0x18 of the manager):
// every property list in the shader-info group becomes one record (keys, usage flags, sampler
// mode, tuning floats and bools).
// Flags: /O2 /MD /Gy /TP (no EH frame is emitted).
#include "types.h"

void __cdecl operator_delete__(void* p);   // 0x00f47380

struct RefCounted {
    virtual int AddRef();
    virtual int Release();
};

template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T** AsPPointer() {
        if (mpObject) {
            T* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};

struct Property {
    char pad0[0x10];
    uint16_t flags;     // +0x10 (0x30 = value is a pointer)
    uint16_t type;      // +0x12 (1 bool, 0xd float)
    float* GetFloat() { return (flags & 0x30) ? *(float**)this : (float*)this; }
    bool* GetBool() { return (flags & 0x30) ? *(bool**)this : (bool*)this; }
};

struct PropertyList : RefCounted {
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8();
    virtual bool Get(uint32_t id, Property** out);   // +0x24
};

struct ResourceKey { uint32_t instanceID, typeID, groupID; };

struct UIntVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAllocator[2];  // sp_vector_allocator (left uninitialized)
    UIntVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~UIntVector() {
        if (mpBegin && ((int*)mpBegin)[-1])
            operator_delete__(mpBegin);
    }
};

struct cPropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool GetPropertyList(uint32_t id, uint32_t group, PropertyList** ppOut);   // +0x2c
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18();
    virtual bool GetAllPropertyListIDs(uint32_t group, UIntVector* out);              // +0x4c
};

cPropertyManager* PropertyManager();                     // 0x0067de30
struct GameMode;
GameMode* GetCurrentGameMode();                          // 0x00b5b800
extern GameMode g_DefaultGameMode;                       // 0x01654c10
bool GetPropertyAsKeyInstance(PropertyList* pl, uint32_t id, uint32_t* out);          // 0x006a12a0
bool GetPropertyAsKeyArray(PropertyList* pl, uint32_t id, int* count, ResourceKey** out);  // 0x006a0ae0

struct ShaderDataInfo {
    uint32_t mKey0, mKey1, mKey2, mKey3;   // +0x00
    uint32_t mUsageFlags;                  // +0x10
    uint32_t mMode;                        // +0x14
    float mF18, mF1C, mF20, mF24, mF28, mF2C, mF30, mF34, mF38;   // +0x18
    bool mB3C, mB3D;                       // +0x3c
    float mF40, mF44, mF48, mF4C;          // +0x40
    bool mB50, mB51, mB52;                 // +0x50
};

struct ShaderInfoVector {
    ShaderDataInfo* mpBegin;
    ShaderDataInfo* mpEnd;
    ShaderDataInfo* mpCapacity;
    ShaderDataInfo* erase(ShaderDataInfo* first, ShaderDataInfo* last);   // 0x01041220
    void reserve(uint32_t n);                                             // 0x01041170
    void push_back();                                                     // 0x010413b0
    void clear() { erase(mpBegin, mpEnd); }
};

struct cShaderManager {
    char pad0[0x18];
    ShaderInfoVector mInfos;    // +0x18
};

inline void ReadFloat(PropertyList* pl, uint32_t id, float* dst) {
    Property* p;
    if (pl && pl->Get(id, &p) && p->type == 0xd)
        *dst = *p->GetFloat();
}
inline void ReadBool(PropertyList* pl, uint32_t id, bool* dst) {
    Property* p;
    if (pl && pl->Get(id, &p) && p->type == 1)
        *dst = *p->GetBool();
}

namespace {

// @ 0x010414c0
void __fastcall RegisterShaderDataInfo(cShaderManager* mgr)
{
    uint32_t group = (GetCurrentGameMode() != &g_DefaultGameMode) ? 0xf0bf332c : 0x073a7400;
    UIntVector ids;
    PropertyManager()->GetAllPropertyListIDs(group, &ids);
    mgr->mInfos.clear();
    mgr->mInfos.reserve((uint32_t)(ids.mpEnd - ids.mpBegin));

    for (uint32_t* it = ids.mpBegin; it != ids.mpEnd; ++it) {
        AutoRefCount<PropertyList> list;
        uint32_t id = *it;
        PropertyManager()->GetPropertyList(id, group, list.AsPPointer());
        if (!list)
            continue;

        mgr->mInfos.push_back();
        ShaderDataInfo* info = mgr->mInfos.mpEnd - 1;

        uint32_t key;
        GetPropertyAsKeyInstance(list, 0x5e7c551, &info->mKey0);
        GetPropertyAsKeyInstance(list, 0x5e7c589, &info->mKey1);
        GetPropertyAsKeyInstance(list, 0x6932a26, &info->mKey2);
        GetPropertyAsKeyInstance(list, 0x7a13cca, &info->mKey3);
        if (GetPropertyAsKeyInstance(list, 0x5e7c598, &key)) {
            switch (key) {
            case 0x4a5daa3: info->mMode = 0; break;
            case 0x3e9c273b: info->mMode = 1; break;
            case 0xa076618: info->mMode = 2; break;
            case 0x96b84350: info->mMode = 3; break;
            }
        }
        if (GetPropertyAsKeyInstance(list, 0x5e7c5d6, &key)) {
            switch (key) {
            case 0x28346586: info->mUsageFlags |= 8; break;
            case 0x419c2c6e:
            case 0x5dfe4d8c: info->mUsageFlags |= 0x18; break;
            case 0x9e3c3dfa: info->mUsageFlags |= 0x10; break;
            }
        }

        int count;
        ResourceKey* keys;
        if (GetPropertyAsKeyArray(list, 0x5e7c5ab, &count, &keys)) {
            for (int i = 0; i < count; i++) {
                switch (keys[i].instanceID) {
                case 0x408ae13a: info->mUsageFlags |= 1; break;
                case 0x998a3717: info->mUsageFlags |= 2; break;
                case 0xdbc59db3: info->mUsageFlags |= 4; break;
                case 0x419c2c6e:
                case 0x5dfe4d8c: info->mUsageFlags |= 7; break;
                }
            }
        }
        if (GetPropertyAsKeyArray(list, 0x60a0704, &count, &keys)) {
            for (int i = 0; i < count; i++) {
                switch (keys[i].instanceID) {
                case 0x2f57018a: info->mUsageFlags |= 0x20; break;
                case 0xcc9c4f70: info->mUsageFlags |= 0x40; break;
                case 0xdc86b714: info->mUsageFlags |= 0x80; break;
                case 0x419c2c6e:
                case 0x5dfe4d8c: info->mUsageFlags |= 0xe0; break;
                }
            }
        }

        ReadFloat(list, 0x5e7c63d, &info->mF18);
        ReadFloat(list, 0x5e7c648, &info->mF1C);
        ReadFloat(list, 0x6121b4f, &info->mF20);
        ReadFloat(list, 0x6121282, &info->mF24);
        ReadFloat(list, 0x61215a4, &info->mF28);
        ReadFloat(list, 0x61215ac, &info->mF2C);
        ReadFloat(list, 0x5e7c654, &info->mF30);
        ReadFloat(list, 0x5e7c65f, &info->mF34);
        ReadFloat(list, 0x61329ab, &info->mF38);
        ReadBool(list, 0x7a143d4, &info->mB3C);
        ReadBool(list, 0x7a143d8, &info->mB3D);
        ReadFloat(list, 0x7a143db, &info->mF40);
        ReadFloat(list, 0x7a14405, &info->mF44);
        ReadFloat(list, 0x609e03a, &info->mF48);
        ReadFloat(list, 0x60b0498, &info->mF4C);
        ReadBool(list, 0x609e078, &info->mB50);
        ReadBool(list, 0x60b0488, &info->mB51);
    }
}

}

// Forces emission of the file-local function (the original is reached from a caller in another TU).
void (__fastcall* g_RegisterShaderDataInfo)(cShaderManager*) = RegisterShaderDataInfo;

// ===========================================================================
// Minimap icon handlers / space-app transition helpers (claimed batch).
// ===========================================================================

struct VtblTable { void* mSlots[0x100]; };
typedef void* (__thiscall *VfnP)(void*);
typedef int   (__thiscall *VfnI)(void*);
typedef void  (__thiscall *VfnV)(void*);
typedef void  (__thiscall *VfnVUI)(void*, void*, uint32_t);
typedef bool  (__thiscall *VfnBU)(void*, uint32_t);

struct Vec3f { float x, y, z; };
struct Color4f { float r, g, b, a; };
struct Civilization;

struct MinimapWin {
    void RemoveIcon(void* icon, int a, int b);
    void AddIcon(void* owner, void* data, int a, int b);
};

// 0x24-byte icon record handed to cSPUIMinimapWin::AddIcon
struct MinimapIconData {
    uint32_t mColor;      // +0x00
    Vec3f    mPos;        // +0x04
    uint32_t mType;       // +0x10
    void*    mpRef;       // +0x14
    float    mF18;        // +0x18
    uint32_t mField1C;    // +0x1c
    uint32_t mField20;    // +0x20
};

// minimal cSpatialObject sub-object: GetPosition is vtable slot 0x2c
struct SpatialSub { VtblTable* mpVtbl; };
inline const Vec3f* GetSpatialPosition(SpatialSub* s)
{
    return (const Vec3f*)((VfnP)s->mpVtbl->mSlots[0x2c / 4])(s);
}

// generic ref-counted object: slot 0 = AddRef, slot 1 = Release
inline void RefAdd(void* o) { ((VfnV)(*(void***)o)[0])(o); }
inline void RefRelease(void* o) { ((VfnV)(*(void***)o)[1])(o); }

// source object shared by the minimap-icon callbacks
struct MinimapSource {
    uint8_t  mPad00[0x34];
    SpatialSub mSpatial34;          // +0x034 (CreateMinimapIcon)
    uint8_t  mPad38[0x120 - 0x38];
    SpatialSub mSpatial120;         // +0x120 (city / planet icon)
    uint8_t  mPad124[0x234 - 0x124];
    void*    mpField234;            // +0x234 (colour holder)
    uint8_t  mPad238[0x608 - 0x238];
    uint32_t mField608;             // +0x608

    Civilization* GetCivilization();   // 0x00bd9bf0 (cCity)
};

extern const float g_minusOne;      // 0x013eb1bc  -1.0f
extern const float g_byteScale;     // 0x013f2100  255.0f
extern const float g_one;           // 0x01485720  1.0f
extern const float g_channelR;      // 0x01572b54
extern const float g_channelG;      // 0x01572b58
extern const float g_channelB;      // 0x01572b5c

// ---- external game helpers -------------------------------------------------
void  __cdecl RemoveHandler(void* h, void* self, void* cb, uint32_t msg, uint32_t ud); // 0x00571db0
void* __cdecl MessageServer();                                                        // 0x0067dcc0
void* __cdecl GetTriggerMgr();                                                        // 0x00b3d4d0
void* __cdecl NounManager();                                                          // 0x00b3d300
void* __cdecl StarManager();                                                          // 0x00b3d2a0
void* __cdecl App();                                                                  // 0x0067dd10
void* __cdecl GetUFOSimulator();                                                      // 0x00ffbe50
void* __cdecl SpaceGameGet();                                                          // 0x01002bd0
void* __cdecl FUN_01021240();                                                          // 0x01021240
void* __stdcall FUN_01021300(void* out);                                               // 0x01021300
void* __cdecl CommManager();                                                           // 0x00b3d4a0
void* __cdecl GameTimeManager();                                                       // 0x00b3d380
void* __stdcall NounManagerArg(uint32_t id);                                           // 0x00b3d300 (callee pops)
void* __stdcall StarManagerArg(int id);                                                // 0x00b3d2a0 (callee pops)
bool  __cdecl FUN_00c772c0(void* self, void* arg);                                     // 0x00c772c0
bool  __cdecl FUN_00c77bf0(void* self, void* arg);                                     // 0x00c77bf0
void* __cdecl FUN_00b6f0c0(void* arg);                                                 // 0x00b6f0c0
uint32_t __cdecl ColorRGBAToU32(const Color4f* c);                                     // 0x004580c0
void* __cdecl FUN_010666a0();                                                          // 0x010666a0
bool  __cdecl FUN_01068350(void* self);                                                // 0x01068350
bool  __cdecl FUN_00ff3bf0(void* self);                                                // 0x00ff3bf0

struct TriggerMgr {
    uint8_t  mPad00[0x2c];
    uint32_t mField2c;             // +0x2c
    int  PostTrigger(int a, int b, int c, int d, int e, int f);   // callee pops 0x18
};
struct TerrainSphere {
    bool IsInTerrainSphere(void* arg);   // 0x00c772c0 (callee pops the argument)
    bool HasFlagOrInsert(void* arg);     // 0x00c77bf0
};
struct TerrainEditor {
    void* GetCurrentTerrainSphere();
};
struct CommScreen {
    bool IsActive();
};
struct GameTimeMgr {
    uint8_t mPad00[0x48];
    uint8_t mFlags48;
};
struct GameObj74 {
    void* mPad00;
    VtblTable* mpVtbl;             // not used: methods called directly
    bool FUN_01068350();
    bool FUN_00ff3bf0();
};
struct Empire {
    Color4f GetColor();                // returned by value through a hidden buffer
};
struct StarMgr {
    int FUN_00885c90();
    Empire* GetEmpireByID();          // id already consumed by StarManagerArg
};
struct CivPart {
    uint32_t FUN_00b6f310();
};
struct Civilization {
    VtblTable* mpVtbl;
};
inline int GetCivilizationID(Civilization* civ)
{
    return ((VfnI)civ->mpVtbl->mSlots[0x4c / 4])(civ);
}
struct UFOSim {
    void* GetPlayerInventory();
};
struct UFOData {
    int AddRef();
};
struct Inventory {
    uint8_t mPad00[0x74c];
    uint8_t mFlag74C;              // +0x74c
    bool CanEnterPlanetContext();
    bool FUN_00ff3bf0();
};
typedef bool (__thiscall *VfnBUI)(void* self, uint32_t arg);
inline bool InvHasWormhole(Inventory* inv)
{
    return ((VfnBUI)(*(void***)inv)[0x74 / 4])(inv, 0x16dfbc4);
}
typedef int (__thiscall *VfnIUI)(void* self, uint32_t arg);

// message handler wrapper for the shader-data registration callbacks
struct ShaderMsgHandler {
    uint32_t mPad00;               // +0x00
    void*    mHandler;             // +0x04
    void*    mSelf;                // +0x08
    void*    mCallback;            // +0x0c
    uint32_t mMsg;                 // +0x10
    uint32_t mUserData;            // +0x14
    uint8_t  mPad18[0x18];         // +0x18 mInfos (owned by RegisterShaderDataInfo)

    bool OnMessage(int msg, void* obj);   // 0x01041b90
};

// 0x01041bc0 re-registers the handler; the original keeps the explicit non-null self test.
void __fastcall ShaderMsgHandler_Init(ShaderMsgHandler* self);

// @ 0x01041b90
bool ShaderMsgHandler::OnMessage(int msg, void* obj)
{
    if (msg == 0xf62def) {
        uint32_t group = *(uint32_t*)((uint8_t*)obj + 0x10);
        if (group == 0xf0bf332c || group == 0x073a7400)
            RegisterShaderDataInfo((cShaderManager*)this);
    }
    return false;
}

// @ 0x01041bc0
void __fastcall ShaderMsgHandler_Init(ShaderMsgHandler* self)
{
    void* handler = self->mHandler;
    if (handler != 0) {
        self->mHandler = 0;
        RemoveHandler(handler, self->mSelf, self->mCallback, self->mMsg, self->mUserData);
    }
    void* server = MessageServer();
    self->mHandler = server;
    self->mSelf = self;
    self->mCallback = (void*)0x1499ca8;
    self->mMsg = 1;
    self->mUserData = 0;
    if (server != 0 && self != 0)
        ((VfnVUI)(*(void***)server)[0x24 / 4])(server, self, 0xf62def);
    RegisterShaderDataInfo((cShaderManager*)self);
}

// @ 0x01041c30
void __cdecl FUN_01041c30(void* icon, MinimapWin* win)
{
    if (icon != 0 && win != 0)
        win->RemoveIcon(icon, 1, 0);
}

// @ 0x01041c50
uint32_t __cdecl FUN_01041c50(int a, void* obj, int flag)
{
    uint32_t result = 0;
    if (flag != 1) {
        TriggerMgr* tm = (TriggerMgr*)GetTriggerMgr();
        if (tm->mField2c == 1 || tm->mField2c == 2)
            return result;
    }
    TerrainSphere* sphere = (TerrainSphere*)((TerrainEditor*)NounManager())->GetCurrentTerrainSphere();
    if (sphere == 0)
        return result;
    if (!sphere->IsInTerrainSphere(obj)) {
        sphere->HasFlagOrInsert(obj);
        return ((TriggerMgr*)GetTriggerMgr())->PostTrigger(a, 1, 1, 0, 0, 0);
    }
    return result;
}

// @ 0x01041cd0
float __cdecl FUN_01041cd0(float a, float b, float c)
{
    return (c - a) / ((b - a) + 1.52587890625e-05f);
}

struct SimplePropertyList {
    bool GetDescription(uint32_t id) const;
};
extern SimplePropertyList* g_spAppProperties;   // 0x015fd918

// @ 0x01041cf0
void __cdecl FUN_01041cf0()
{
    g_spAppProperties->GetDescription(0x23ba1fb);
}

// @ 0x01041d10
void __cdecl FUN_01041d10()
{
    g_spAppProperties->GetDescription(0x23ba1fc);
}

// @ 0x01041d30
int __cdecl FUN_01041d30(MinimapSource* src)
{
    return (int)(-(uint32_t)(src->mField608 != 0) & 0x6103d89bu) + (int)0xef2601ca;
}

static void AssignIconRef(MinimapIconData& data, void* src)
{
    void* old = data.mpRef;
    if (src != old) {
        RefAdd(src);
        data.mpRef = src;
        if (old != 0)
            RefRelease(old);
    }
}

// @ 0x01041d50
void __cdecl FUN_01041d50(MinimapSource* src, MinimapWin* win)
{
    if (src == 0 || win == 0)
        return;

    MinimapIconData data;
    data.mColor = 0;
    data.mPos.x = 0.0f;
    data.mPos.y = 0.0f;
    data.mPos.z = g_minusOne;
    data.mpRef = 0;
    data.mF18 = 0.0f;
    data.mField1C = 0;
    data.mField20 = 0;
    data.mType = 1;

    data.mPos = *GetSpatialPosition(&src->mSpatial120);

    Civilization* civ = src->GetCivilization();
    int currentID = ((StarMgr*)StarManager())->FUN_00885c90();
    if (GetCivilizationID(civ) == currentID) {
        uint32_t r = (uint32_t)(int)(g_channelR * g_byteScale) | 0xffffff00u;
        uint32_t g = (uint32_t)(int)(g_channelG * g_byteScale) & 0xff;
        uint32_t b = (uint32_t)(int)(g_channelB * g_byteScale) & 0xff;
        data.mColor = (r << 8 | g) << 8 | b;
    } else {
        data.mColor = ((CivPart*)((uint8_t*)src->GetCivilization() + 0x3c))->FUN_00b6f310();
    }

    AssignIconRef(data, src);
    win->AddIcon(src, &data, 0, 0);
    if (data.mpRef != 0)
        RefRelease(data.mpRef);
}

// @ 0x01041f00
void __cdecl FUN_01041f00(MinimapSource* src, MinimapWin* win)
{
    if (src == 0 || win == 0)
        return;

    MinimapIconData data;
    data.mColor = 0;
    data.mPos.x = 0.0f;
    data.mPos.y = 0.0f;
    data.mPos.z = g_minusOne;
    data.mpRef = 0;
    data.mF18 = 0.0f;
    data.mField1C = 0;
    data.mField20 = 0;
    data.mType = 2;

    data.mPos = *GetSpatialPosition(&src->mSpatial120);

    const float* color = (const float*)FUN_00b6f0c0(src->mpField234);
    uint32_t r = (uint32_t)(int)(color[0] * g_byteScale) | 0xffffff00u;
    uint32_t g = (uint32_t)(int)(color[1] * g_byteScale) & 0xff;
    uint32_t b = (uint32_t)(int)(color[2] * g_byteScale) & 0xff;
    data.mColor = (r << 8 | g) << 8 | b;

    AssignIconRef(data, src);
    win->AddIcon(src, &data, 0, 0);
    if (data.mpRef != 0)
        RefRelease(data.mpRef);
}

// @ 0x01042080
void __cdecl CreateMinimapIcon(MinimapSource* src, MinimapWin* win)
{
    if (src == 0 || win == 0)
        return;

    MinimapIconData data;
    data.mColor = 0;
    data.mPos.x = 0.0f;
    data.mPos.y = 0.0f;
    data.mPos.z = g_minusOne;
    data.mpRef = 0;
    data.mF18 = 0.0f;
    data.mField1C = 0;
    data.mField20 = 0;
    data.mType = 0x10;

    data.mPos = *GetSpatialPosition(&src->mSpatial34);

    Empire* empire = ((StarMgr*)StarManagerArg(GetCivilizationID((Civilization*)src)))->GetEmpireByID();
    if (empire != 0) {
        Color4f color;
        color = empire->GetColor();
        color.a = g_one;
        data.mColor = ColorRGBAToU32(&color);
    } else {
        data.mColor = 0xffcecece;
    }

    AssignIconRef(data, src);
    win->RemoveIcon(src, 1, 0);
    win->AddIcon(src, &data, 0, 0);
    if (data.mpRef != 0)
        RefRelease(data.mpRef);
}

// @ 0x010421c0
void __cdecl FUN_010421c0(MinimapSource* src, MinimapWin* win)
{
    if (src == 0 || win == 0)
        return;

    MinimapIconData data;
    data.mColor = 0;
    data.mPos.x = 0.0f;
    data.mPos.y = 0.0f;
    data.mPos.z = g_minusOne;
    data.mpRef = 0;
    data.mF18 = 0.0f;
    data.mField1C = 0;
    data.mField20 = 0;
    data.mType = 0x40000;

    data.mPos = *GetSpatialPosition(&src->mSpatial34);

    Color4f buffer;
    Empire* empire = (Empire*)FUN_01021300(&buffer);
    Color4f color;
    color = empire->GetColor();
    color.a = g_one;
    data.mColor = ColorRGBAToU32(&color);

    AssignIconRef(data, src);
    win->RemoveIcon(src, 1, 0);
    win->AddIcon(src, &data, 0, 0);
    if (data.mpRef != 0)
        RefRelease(data.mpRef);
}

inline bool InTerrainSphere(uint32_t id)
{
    TerrainSphere* sphere =
        (TerrainSphere*)((TerrainEditor*)NounManagerArg(id))->GetCurrentTerrainSphere();
    return sphere->IsInTerrainSphere((void*)id);
}

// @ 0x010422e0
bool __cdecl TransitionFromSolarToGalaxy()
{
    void* app = App();
    void* mode = ((VfnP)(*(void***)app)[0x50 / 4])(app);
    void* obj = ((VfnP)(*(void***)mode)[0x38 / 4])(mode);
    int advanceID = obj != 0 ? ((VfnIUI)(*(void***)obj)[0xc / 4])(obj, 0x303154cc) : 0;

    Inventory* inv = (Inventory*)((UFOSim*)GetUFOSimulator())->GetPlayerInventory();
    bool canEnter = (inv->mFlag74C != 0 && inv->CanEnterPlanetContext()) ||
                    (((UFOData*)FUN_01021240())->AddRef() == 2 &&
                     InvHasWormhole((Inventory*)((UFOSim*)SpaceGameGet())->GetPlayerInventory())) ||
                    (((UFOData*)FUN_01021240())->AddRef() == 1 && !InTerrainSphere(0x681c28e));

    if (advanceID != 0 && canEnter &&
        !((CommScreen*)CommManager())->IsActive() &&
        (((GameTimeMgr*)GameTimeManager())->mFlags48 & 1) == 0 &&
        !((GameObj74*)FUN_010666a0())->FUN_01068350())
        return true;
    return false;
}

// @ 0x010423d0
bool __cdecl FUN_010423d0()
{
    void* app = App();
    void* mode = ((VfnP)(*(void***)app)[0x50 / 4])(app);
    void* obj = ((VfnP)(*(void***)mode)[0x38 / 4])(mode);
    if (obj != 0 && ((VfnIUI)(*(void***)obj)[0xc / 4])(obj, 0x303154cc) != 0 &&
        !((CommScreen*)CommManager())->IsActive() &&
        (((GameTimeMgr*)GameTimeManager())->mFlags48 & 1) == 0 &&
        ((Inventory*)((UFOSim*)SpaceGameGet())->GetPlayerInventory())->FUN_00ff3bf0() &&
        ((Inventory*)((UFOSim*)GetUFOSimulator())->GetPlayerInventory())->mFlag74C != 0)
        return true;
    return false;
}

