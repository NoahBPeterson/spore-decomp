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
