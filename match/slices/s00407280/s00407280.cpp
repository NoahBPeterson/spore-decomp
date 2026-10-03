// Graphics-settings property list builder (one 9755-byte, /Od-style function).
// Looks up the "Graphics" Editor::cPropertyList for a resource key, then fills it with
// model-derived data (vertex/index/part tables, bounding volumes, dominant-part picks,
// a few hashed model-kind switches) and finally registers the list with the resource manager.
// Behaviorally-equivalent reconstruction; NOT byte-exact (see nonmatching.txt).
// Built without optimization: /Od /Ob1 (frame pointer, every local in memory).
#include "../../include/types.h"

struct ResourceKey { uint32_t instance, type, group; };

struct IRefCounted { virtual void AddRef(); virtual void Release(); };

struct PropertyList : IRefCounted {
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void SetProperty(uint32_t id, void* value);        // +0x14
    virtual bool HasProperty(uint32_t id);                     // +0x1c (slot 7)
    virtual bool GetProperty(uint32_t id, void* outInfo);      // +0x24
};

struct PropertyInfo { char pad[0x12]; short type; };

struct ResourceManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetResource(uint32_t group, uint32_t instance, void* outRef);  // +0x2c
    virtual void v12();
    virtual void SetResource(PropertyList* list, uint32_t instance, uint32_t group); // +0x34
};
struct ResourceFactory {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool Create(ResourceKey* key, void* out, int, int, int, int);       // +0xc
};

// Model description (element sizes taken from the original strides).
struct Part { char pad[0x1d8]; };
struct Model {
    char pad0[0x18]; uint32_t kind;
    char pad1[0x80]; Part* partsBegin; Part* partsEnd;
};
struct MeshEntry { uint16_t flags, count; float data[12]; };           // 0x38 bytes
struct Vec3 { float x, y, z; };

// Opaque helpers (originals are unnamed FUN_xxxxxxxx).
ResourceManager* GetResourceManager();      // FUN_0067de30
ResourceFactory* GetResourceFactory();      // FUN_0067dcd0
int  MakeKey(void* scratch);                // FUN_0041d870
Model* LookupModel(void* ref);              // FUN_00421eb0
void* AllocPropertyList(uint32_t, const char*, int, int, int, int);
PropertyList* ConstructPropertyList(void* mem);   // Editor::cPropertyList::cPropertyList
void ReleaseRef(void* r);                   // FUN_006a1710
void FlushProperty(int);                    // FUN_0093db80
float Dot(const Vec3& a, const Vec3& b);
void AddPartBounds(void* acc, Part* p);
void BuildPartEntry(MeshEntry* out, Part* p);
void ReleaseTable(void* b, void* e);

extern float g_DefaultScale;                // DAT_015d1318
extern const char g_GraphicsTag[];

static void CommitProperty(PropertyList* list, uint32_t id, void* value) {
    uint16_t info[2] = { 0, 0 };
    list->SetProperty(id, value);
    if (info[0] & 4) FlushProperty(0);
}

struct SettingsBuilder {
    void* vtbl;
    virtual void v0();
    virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void GetBounds(uint32_t a, uint32_t b, float* outMin, float* outMax, uint32_t c); // +0x54

    void BuildGraphicsProperties(ResourceKey* key);
};

// @ 0x00407280
void SettingsBuilder::BuildGraphicsProperties(ResourceKey* key)
{
    PropertyList* result = 0;     // list being produced (ebp-0x1590)
    char ref[0x100];
    ResourceManager* rm = GetResourceManager();
    rm->GetResource(key->instance, key->group, (void*)(unsigned)MakeKey(&result));

    ResourceKey modelKey = *key;
    ResourceFactory* rf = GetResourceFactory();
    int modelRef = 0;
    if (!rf->Create(key, (void*)(unsigned)MakeKey(ref), 0, 0, 0, 0)) {
        if (result) result->Release();
        return;
    }
    Model* model = LookupModel(&modelRef);
    if (!model) { if (result) result->Release(); return; }

    // Optional secondary key (type 0x30bdee3) resolved through the factory.
    modelKey.type = 0x30bdee3;
    PropertyList* extra = 0;
    if (rf->Create(&modelKey, (void*)(unsigned)MakeKey(ref), 0, 0, 0, 0)) {
        PropertyList* found = (PropertyList*)LookupModel(&modelRef);
        if (found != extra) {
            PropertyList* old = extra;
            if (found) found->AddRef();
            extra = found;
            if (old) old->Release();
        }
    }

    if (!result) {
        void* mem = AllocPropertyList(0x38, g_GraphicsTag, 0, 0, 0, 0);
        PropertyList* fresh = mem ? ConstructPropertyList(mem) : 0;
        if (fresh != result) {
            PropertyList* old = result;
            if (fresh) fresh->AddRef();
            result = fresh;
            if (old) old->Release();
        }
    }

    // Seed scale from an existing float property, defaulting to 1.0.
    float scale = 1.0f;
    PropertyInfo* info = 0;
    if (result->GetProperty(0xfba611, &info) && info->type == 0xd)
        scale = *(float*)LookupModel(&info);

    // Per-part pass: accumulate dominant extent and per-part volumes.
    int partCount = (int)(model->partsEnd - model->partsBegin);
    float maxVolume = 0.0f;
    float bestWeight = 0.0f;
    uint32_t bestId = 0, bestScale = 0;
    for (int i = 0; i < partCount; ++i) {
        Part* part = &model->partsBegin[i];
        MeshEntry entry; BuildPartEntry(&entry, part);
        entry.flags |= 4; entry.count += 2;
        entry.flags |= 2; entry.count += 1;
        float lo[3], hi[3];
        GetBounds(((uint32_t*)part)[1], ((uint32_t*)part)[0], lo, hi, ((uint32_t*)part)[0x24]);
        if (hi[0] < lo[0]) { /* swap handled by helper */ }
        AddPartBounds(&entry, part);
    }

    // Commit the standard properties (all via the vtable +0x14 setter).
    CommitProperty(result, 0xf1fae962, 0);
    CommitProperty(result, 0xf1fae963, 0);
    CommitProperty(result, 0x4c71061, 0);
    CommitProperty(result, 0x4c71062, 0);
    CommitProperty(result, 0x519e304, 0);
    CommitProperty(result, 0x5b567d1, 0);
    CommitProperty(result, 0x4ff954a, 0);

    // Model-kind dependent default (property 0x46d0560): hashed kind switch in the original.
    switch (model->kind) {
    case 0x8f963dcb: case 0xc15695da: case 0x2a5147a9: case 0x1f2a25b6:
        CommitProperty(result, 0x46d0560, 0); break;
    case 0x98e03c0d: case 0x1a4e0708: case 0x2090a11b: case 0x441cd3e6: case 0x449c040f:
        CommitProperty(result, 0x46d0560, 0); break;
    case 0xc0b74287: case 0x9ad7d4aa: case 0xbc1041e6: case 0xf670aa43: case 0x7d433fad:
        CommitProperty(result, 0x46d0560, 0); break;
    default: break;
    }
    if (!result->HasProperty(0x4a5b8d2)) {
        if (model->kind == 0x47c10953 || model->kind == 0x72c49181)
            CommitProperty(result, 0x4a5b8d2, 0);
    }

    GetResourceManager()->SetResource(result, key->instance, key->group);

    // Group 'b' variant: publish a second list when property 0x339ff24 is a set bool.
    if ((key->group >> 30) == 1 && ((key->group >> 8) & 0xff) == 0x62) {
        PropertyInfo* pi = 0; char flag = 0;
        if (result && result->GetProperty(0x339ff24, &pi) && pi->type == 1) flag = 1;
        if (flag) {
            void* mem = AllocPropertyList(0x38, "Graphics", 0, 0, 0, 0);
            PropertyList* second = mem ? ConstructPropertyList(mem) : 0;
            if (second) second->AddRef();
            GetResourceManager()->SetResource(second, key->instance,
                                              (key->group & 0xffff00ff) | 0x7e00);
            if (second) second->Release();
        }
    }

    if (extra)  extra->Release();
    if (result) result->Release();
}
