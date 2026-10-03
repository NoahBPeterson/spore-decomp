// Editor panel: listener/handler lookup against a ResourceKey (+ id) and activation.
// Built /Od /Ob1 /MD /Gy /EHsc /TP /arch:SSE (frame pointer, all locals in memory).
#include "types.h"

struct GroupBits { uint32_t lo : 16; uint32_t tag : 8; uint32_t flags : 5; uint32_t hi : 3; };
struct ResourceKey {
    uint32_t instance, type;
    union { uint32_t group; GroupBits bits; };
};

// Bit helpers inlined from small by-value functions.
void __cdecl ResourceKey_SetFlags(ResourceKey* k, int flags);   // 0x0068c700

inline uint32_t BitsTag(uint32_t v) { uint32_t r = v; return (r >> 16) & 0xff; }
inline uint32_t BitsClearFlags(uint32_t v, uint32_t n) { ((GroupBits*)&v)->flags = n; return v; }
struct Entry {
    ResourceKey key;
    int id;
    inline bool KeyEquals(const ResourceKey& o) const
    {
        return key.instance == o.instance && key.type == o.type && key.group == o.group;
    }
};

struct IterSub {
    int w[4];
    IterSub() {}
    IterSub(const IterSub& o);   // 0x00420050
    Entry* __fastcall Deref();   // 0x005658b0 (ecx = &sub)
    inline bool operator==(const IterSub& o) const { return w[0] == o.w[0]; }
};

struct Iter {
    int cur;
    IterSub sub;
    int f5, f6;
    Iter() {}
    Iter(const Iter& o) : cur(o.cur), sub(o.sub), f5(o.f5), f6(o.f6) {}
    bool operator==(const Iter& o) const
    {
        return cur == o.cur && (cur == f6 || sub == o.sub);
    }
    inline bool operator!=(const Iter& o) const { return !(*this == o); }
    inline Entry* operator->() { return sub.Deref(); }
    Iter& Next();                // 0x00421f00
};

struct EntryList {
    int pad[1];
    Iter* Begin(Iter* out);          // 0x00420200
    Iter* End(Iter* out);            // 0x00420350
    Iter Erase(Iter it);             // 0x00420390
};

void* __cdecl EASTL_allocator_allocate(unsigned sz, const char* name, int a, int b, int c, int d); // 0x00f473a0

struct Message {
    Message(int type);               // 0x00423110
    virtual void vf0();
    int pad[13];
};
struct EditorMessage : Message {
    int unk38;
    int pad3c;
    static inline void* operator new(unsigned sz, const char* name, int a, int b, int c, int d)
    {
        return EASTL_allocator_allocate(sz, name, a, b, c, d);
    }
    EditorMessage(int type) : Message(type) { unk38 = 0; }
    virtual void vf0();
    inline void SetField(unsigned i, int v) { *(int*)((char*)this + i * 8 + 8) = v; }
};

struct Dispatcher {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void Post(int type, Message* msg, int a, int b);
};
Dispatcher* GetDispatcher();                                    // 0x0067dcc0
struct Manager { void __thiscall Method(void* p); };           // 0x00522a40
Manager* GetManager();                                          // 0x00401080

struct EditorPanel {
    char pad0[0xc8];
    EntryList entries;          // 0xc8
    char pad1[0x228 - 0xc8 - 4];
    ResourceKey activeKey;      // 0x228
    int activeId;               // 0x234
    char pad2[0x240 - 0x238];
    void* target;               // 0x240
    char pad3[0x259 - 0x244];
    bool flagA;                 // 0x259
    char pad4[0x2c4 - 0x25a];
    bool flagB;                 // 0x2c4

    inline void* GetTarget() { return target; }
    bool HasHandler(ResourceKey* k, int id);
    bool HasId(int id);
    bool HasHandlerNormalized(ResourceKey* k);
    bool Activate(ResourceKey* k, int id);
    void __thiscall CommitAndReset(int a);   // 0x00411890
};

// @ 0x00416180
bool EditorPanel::HasHandler(ResourceKey* k, int id)
{
    ResourceKey key = *k;
    if (BitsTag(key.group) == 0x62) {
        ResourceKey_SetFlags(&key, 0);
    }
    if (flagA || flagB) {
        if (((Entry*)&activeKey)->KeyEquals(key) && activeId == id)
            return true;
    }
    {
    Iter it, end;
    entries.Begin(&it);
    entries.End(&end);
    for (; it != end; it.Next()) {
        if (it->KeyEquals(key) && it->id == id)
            return true;
    }
    }
    return false;
}

// @ 0x00416320
bool EditorPanel::HasId(int id)
{
    if ((flagA || flagB) && activeId == id)
        return true;
    Iter it, end;
    entries.Begin(&it);
    entries.End(&end);
    for (; it != end; it.Next()) {
        if (it->id == id)
            return true;
    }
    return false;
}

// @ 0x004163f0
bool EditorPanel::HasHandlerNormalized(ResourceKey* k)
{
    ResourceKey key = *k;
    {
    Iter it, end;
    bool isSpecial = (key.type == 0x2b978c46 || key.type == 0x438f6347 || key.type == 0x3d97a8e4);
    if (isSpecial) {
        key.group = BitsClearFlags(key.group, 0);
    }
    if (flagA || flagB) {
        if (((Entry*)&activeKey)->KeyEquals(key))
            return true;
    }
    entries.Begin(&it);
    entries.End(&end);
    for (; it != end; it.Next()) {
        if (it->KeyEquals(key))
            return true;
    }
    }
    return false;
}

// @ 0x004165a0
bool EditorPanel::Activate(ResourceKey* k, int id)
{
    if (flagB || flagA) {
        Entry* e = (Entry*)&activeKey;
        if (e->KeyEquals(*k) && activeId == id) {
            if (flagB) {
                CommitAndReset(1);
                return true;
            }
            if (flagA && GetTarget()) {
                GetManager()->Method(GetTarget());
                CommitAndReset(1);
                return true;
            }
            return false;
        }
    }
    Iter it, end;
    entries.Begin(&it);
    entries.End(&end);
    while (it != end) {
        Entry* e = it.operator->();
        if (e->KeyEquals(*k) && it->id == id) {
            EditorMessage* msg = new ("Editor", 0, 0, 0, 0) EditorMessage(0x695e243);
            msg->SetField(0, it->key.instance);
            msg->SetField(1, it->key.group);
            msg->SetField(2, it->key.type);
            msg->SetField(3, it->id);
            msg->SetField(4, 2);
            GetDispatcher()->Post(0x695e243, msg, 0, 0);
            it = entries.Erase(it);
            return true;
        } else {
            it.Next();
        }
    }
    return false;
}
