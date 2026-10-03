// Editor-side resource key remapping helpers (module built /Od /Ob1 /arch:SSE).
#include "types.h"
#include <new>
#include <math.h>

struct GroupId {
    uint32_t value;
    uint32_t GetKind() const { return (value >> 16) & 0xff; }
    uint32_t GetSub() const { return (value >> 24) & 0x1f; }
    void SetSub(uint32_t s) { value = (value & 0xe0ffffff) | ((s & 0x1f) << 24); }
};

struct ResourceKey {
    uint32_t instance;
    uint32_t type;
    GroupId group;
};

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

struct RefCounted {
    virtual void AddRef();
    virtual void Release();
};

struct PropertyHolder : RefCounted {
    uint32_t pad[11];
    uint32_t extra;         // +0x30
    uint32_t GetExtra() const { return extra; }
};

struct PropRef {
    PropertyHolder* p;
    PropRef() : p(0) {}
    PropertyHolder** operator&() {
        if (p) { PropertyHolder* t = p; p = 0; t->Release(); }
        return &p;
    }
    PropertyHolder* operator->() const { return p; }
};

struct cPropertyList : RefCounted {
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual void LoadImpl(PropertyHolder* props);   // +0x2c
    uint32_t pad[13];
    cPropertyList();
    void Init(uint32_t extra);                       // 0x6A1710
    void Load(PropertyHolder* props) { LoadImpl(props); }
};

inline void* operator new(size_t size, const char* tag, int a, int b, int c, int d);

struct ResourceManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9();
    virtual bool HasResource(uint32_t instance, uint32_t group);                          // +0x28
    virtual bool OpenProperties(uint32_t instance, uint32_t group, PropertyHolder** out); // +0x2c
    virtual void v12();
    virtual void StoreProperties(cPropertyList* list, uint32_t instance, uint32_t group); // +0x34
};

ResourceManager* GetResourceManager();                                  // 0x67DE30
void GetBoolProperty(PropertyHolder* p, uint32_t id, bool* out);        // 0x407190
void* AllocateTagged(uint32_t size, const char* name, int, int, int, int); // 0xF473A0
inline void* operator new(size_t size, const char* tag, int a, int b, int c, int d)
{
    return AllocateTagged(size, tag, a, b, c, d);
}
void SavePropertyList(cPropertyList* l, int flag);                      // 0x6B2090

struct WorldObject {
    uint32_t pad[4];
    int flag;                                        // +0x10
    int GetFlag() const { return flag; }
    void GetPosition(Vector3* out, int a, int b, int c);   // 0x44AE00
};
struct World {
    int GetObjectCount();                            // 0x4ACCF0
    WorldObject* GetObject(int index);               // 0x4ACCB0
};
struct ObjectVector {
    WorldObject** begin; WorldObject** end; WorldObject** cap;
    void Resize(int n);                              // 0x4207E0
    void Remove(WorldObject** it);                   // 0x422380
    int Size() const { return (int)(end - begin); }
};
struct Notifier { void Notify(void* who); };         // 0x422280
void GetWorldCenter(Vector3* out, World* w);         // 0x46BFD0
void SetWorldCenter(World* w, Vector3 v, int flag);  // 0x4934D0
void UpdateWorld(World* w);                          // 0x4B7660
Vector3 VectorSub(const Vector3& a, const Vector3& b);  // 0x41DB10
float VectorLength(const Vector3* v);

struct NearbyObjectList {
    char pad0[0x228]; uint32_t m_unk228;
    char pad1[4];     uint32_t m_unk230;
    char pad2[0x334 - 0x234]; World* m_world;
    char pad3[0x430 - 0x338]; float m_maxDistance;
    char pad4[0xd80 - 0x434]; int m_count;
    char pad5[0xd8c - 0xd84]; ObjectVector m_objects;
    char pad6[0x10f4 - 0xd98]; uint32_t m_dirty;
    void Refresh(void* listener);
};

struct KeyCopier {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool CanCopy(const ResourceKey* key, int flag);                 // +0x1c
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual bool CopyKey(const ResourceKey* src, const ResourceKey* dst);   // +0x50

    bool Copy(const ResourceKey* src, const ResourceKey* dst);
    void RefreshList();
};

// @ 0x0040A9C0
bool KeyCopier::Copy(const ResourceKey* src, const ResourceKey* dst)
{
    if (!CanCopy(src, 0))
        return false;
    if (src->type != dst->type || src->group.value != dst->group.value)
        return false;

    ResourceManager* mgr = GetResourceManager();
    if (mgr->HasResource(dst->instance, dst->group.value))
        return false;

    bool copied = false;
    PropRef props;

    if (mgr->OpenProperties(src->instance, src->group.value, &props)) {
        bool flag = false;
        GetBoolProperty(props.p, 0x66FADBD, &flag);
        if (flag) {
            cPropertyList* list = new ("Editor", 0, 0, 0, 0) cPropertyList();
            if (list) list->AddRef();
            list->Init(props->extra);
            list->Load(props.p);
            mgr->StoreProperties(list, dst->instance, dst->group.value);
            SavePropertyList(list, 1);
            copied = true;
            if (list) list->Release();
        }
    }
    if (src->group.GetKind() == 0x62 && src->group.GetSub() == 0) {
        ResourceKey a = *src;
        ResourceKey b = *dst;
        a.group.SetSub(1);
        b.group = a.group;
        if (copied && CopyKey(&a, &b))
            copied = true;
        else
            copied = false;
    }
    bool result = copied;
    if (props.p) props.p->Release();
    return result;
}

// @ 0x0040AC70
void NearbyObjectList::Refresh(void* listener)
{
    World* world = m_world;
    uint32_t unusedA = m_unk228;       // dead copies kept by the original
    uint32_t unusedB = m_unk230;
    Vector3 center;
    GetWorldCenter(&center, world);
    SetWorldCenter(world, center, 0);
    UpdateWorld(world);

    int* pCount = &m_count;
    *pCount = world->GetObjectCount();
    ObjectVector* list = &m_objects;
    list->Resize(*pCount);

    float maxDist = m_maxDistance;
    for (int i = 0; i < *pCount; i++) {
        WorldObject* obj = world->GetObject(i);
        if (obj) {
            int flag = obj->GetFlag();
            Vector3 objPos;
            obj->GetPosition(&objPos, 1, 0, 0);
            Vector3 origin;
            Vector3 delta = VectorSub(origin, objPos);
            float dist = VectorLength(&delta);
            if (flag && dist >= maxDist)
                list->Remove(&obj);
        }
    }
    *pCount = list->Size();
    m_dirty = 0;
    ((Notifier*)listener)->Notify(this);
}

// @ 0x0040AE50
float VectorLength(const Vector3* v)
{
    return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
}
