// Editor panel (continued): activation by id / by key, press counter, entry counting,
// and snapshot of all pending entries into a sink; plus a float lookup by key tag.
// Built /Od /Ob1 /MD /Gy /EHsc /TP /arch:SSE (frame pointer, all locals in memory).
#include "types.h"

struct ResourceKey { uint32_t instance, type, group; };

struct Payload { int id, extra; };

struct Entry {
    ResourceKey key;
    union { Payload val; struct { int id, extra; }; };
    Entry() {}
    Entry(const ResourceKey& k, const Payload& p) : key(k), val(p) {}
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
    Iter* Begin(Iter* out);            // 0x00420200
    Iter* End(Iter* out);              // 0x00420350
    Iter* BeginC(Iter* out);           // 0x004201a0
    Iter* EndC(Iter* out);             // 0x004202f0
    Iter EndCV();
    Iter* Erase(Iter* out, Iter it);   // 0x00420390
    Iter ErasePV(Iter it);
    int Size();                        // 0x00420480
};

struct Message {
    Message(int type);               // 0x00423110
    virtual void vf0();
    int pad[13];
};
struct EditorMessage : Message {
    int unk38;
    int unk3c;
    EditorMessage(int type) : Message(type) { unk38 = 0; }
    virtual void vf0();
    inline void SetField(unsigned i, int v) { *(int*)((char*)this + i * 8 + 8) = v; }
};
void* __cdecl operator new(unsigned sz, const char* name, int a, int b, int c, int d);  // 0x00f473a0

struct Dispatcher {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void Post(int type, Message* msg, int a, int b);
};
Dispatcher* GetDispatcher();                                    // 0x0067dcc0
void* __cdecl EASTL_allocator_allocate(unsigned sz, const char* name, int a, int b, int c, int d); // 0x00f473a0

struct EntrySink { void __thiscall Add(const Entry* e); };      // 0x004227f0

// Per-slot hash map used by the float lookup (slot stride 0x20).
struct HIter {
    int* node;
    int** bucket;
    HIter() {}
    HIter(int* n, int** b) : node(n), bucket(b) {}
    inline bool operator!=(const HIter& o) const { return node != o.node; }
};
struct Slot {
    int pad0;
    int** buckets;     // +4
    int bucketIdx;     // +8
    char pad1[0x20 - 12];
    void __thiscall Find(HIter* out, const ResourceKey* key);   // 0x00421950
    inline HIter End()
    {
        int** p = buckets + bucketIdx;
        return HIter(*p, p);
    }
};

// Incoming event whose resource key lives at +8.
struct KeyedEvent { int pad[2]; ResourceKey key; };
inline int KeyGroupTag(uint32_t v) { return (v >> 16) & 0xff; }

struct EditorPanel {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16();
    virtual bool OnActivate(Entry* e, int id);   // +0x44

    char pad0[0xc0 - 4];
    bool noEntries;             // 0xc0
    char pad0b[3];
    int pressCount;             // 0xc4
    EntryList entries;          // 0xc8
    char pad1[0x228 - 0xc8 - 4];
    Entry active;               // 0x228 (key 0x228, id 0x234, extra 0x238)
    char pad2[0x259 - 0x23c];
    bool flagA;                 // 0x259
    char pad4[0x2c4 - 0x25a];
    bool flagB;                 // 0x2c4
    char pad5[0x1184 - 0x2c5];
    Slot slots[6];              // 0x1184

    bool ActivateById(int id);
    bool ActivateByKey(ResourceKey* k);
    void AdjustPressCount(bool release);
    int CountPending();
    int CountWithId(int id);
    bool GetActiveKey(ResourceKey* out);
    void CollectAll(EntrySink* out);
    float GetSlotValue(KeyedEvent* ev);
};

// @ 0x00416990
bool EditorPanel::ActivateById(int id)
{
    bool found = false;
    if ((flagB || flagA) && active.id == id) {
        found = OnActivate(&active, active.id);
    }
    Iter iter, end;
    entries.Begin(&iter);
    entries.End(&end);
    while (iter != end) {
        if (iter->id == id) {
            EditorMessage* msg = new ("Editor", 0, 0, 0, 0) EditorMessage(0x695e243);
            msg->SetField(0, iter->key.instance);
            msg->SetField(1, iter->key.group);
            msg->SetField(2, iter->key.type);
            msg->SetField(3, iter->id);
            msg->SetField(4, 2);
            GetDispatcher()->Post(0x695e243, msg, 0, 0);
            iter = entries.ErasePV(iter);
            found = true;
        } else {
            iter.Next();
        }
    }
    return found;
}

// @ 0x00416c60
bool EditorPanel::ActivateByKey(ResourceKey* k)
{
    Iter iter, end;
    bool found = false;
    if (flagA || flagB) {
        if (active.KeyEquals(*k)) {
            found = OnActivate(&active, active.id);
        }
    }
    entries.Begin(&iter);
    entries.End(&end);
    while (iter != end) {
        if (iter->KeyEquals(*k)) {
            iter = entries.ErasePV(iter);
            found = true;
        } else {
            iter.Next();
        }
    }
    return found;
}

// @ 0x00416c60

// @ 0x00416e30
void EditorPanel::AdjustPressCount(bool release)
{
    if (!release) {
        pressCount++;
    } else {
        pressCount--;
        if (pressCount < 0)
            pressCount = 0;
    }
    noEntries = pressCount == 0;
}

// @ 0x00416eb0
int EditorPanel::CountPending()
{
    return entries.Size() + ((flagA || flagB) ? 1 : 0);
}

// @ 0x00416f00
int EditorPanel::CountWithId(int id)
{
    int count = 0;
    Iter begin, end;
    entries.Begin(&begin);
    entries.End(&end);
    for (; begin != end; begin.Next()) {
        if (begin->id == id)
            count++;
    }
    return count;
}

// @ 0x00416fb0
bool EditorPanel::GetActiveKey(ResourceKey* out)
{
    if (flagA || flagB) {
        if (out) {
            *out = active.key;
        }
        return true;
    }
    return false;
}

// @ 0x00417010
void EditorPanel::CollectAll(EntrySink* out)
{
    if (flagA || flagB) {
        out->Add(&Entry(active.key, active.val));
    }
    Iter it;
    entries.BeginC(&it);
    for (; it != entries.EndCV(); it.Next()) {
        out->Add(&Entry(it->key, it->val));
    }
}

// @ 0x00417150
float EditorPanel::GetSlotValue(KeyedEvent* ev)
{
    ResourceKey* key = &ev->key;
    int tag = KeyGroupTag(key->group);
    if (tag >= 0x61 && tag <= 0x66) {
        HIter found;
        slots[tag - 0x61].Find(&found, key);
        if (found != slots[tag - 0x61].End())
            return *(float*)((char*)found.node + 4);
    }
    return 0.0f;
}
