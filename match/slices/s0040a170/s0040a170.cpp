// Editor module: object-key bookkeeping for the editor's resource list.
// Both functions are /Od-style (frame pointer, all locals in memory) code with heavy
// inlining of smart-pointer / EASTL helper templates. Written as behaviorally
// equivalent source; not byte-exact.

typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

struct ResourceKey {
    uint32_t instance;   // +0
    uint32_t type;       // +4
    uint32_t group;      // +8; byte 1 / byte 2 hold sub-type tags
};

struct KeyFlags {
    uint32_t id;         // +0
    uint16_t flags;      // +4: 0x1 = add, 0x20 = skip, 0x100 = extra
    uint16_t index;      // +6
};

struct RefCounted {
    virtual void Dummy0();
    virtual void Release();   // slot 1
};

struct EntryRec {
    uint32_t a, b, c;
    uint16_t pad;
    uint16_t flags;           // +0x10
};

struct Entry18 { uint32_t v[6]; };

// External helpers (addresses are relocations in the original).
extern void* EASTL_allocator_allocate(uint32_t size, const char* name, uint32_t, uint32_t, uint32_t, uint32_t);
extern void  FUN_004036e0(void* self);
extern void* FUN_00401e40(void* self);
extern void  FUN_00401ef0(void* self, void* p);
extern void  FUN_00401f20(void* self);
extern void* FUN_005658b0(void* self);
extern void  FUN_004063d0(void* self, void* p);
extern bool  FUN_00401d90(const ResourceKey* k);
extern void* FUN_00423110(void* self, uint32_t);
extern void* FUN_00421c80(void* self, uint32_t);
extern bool  FUN_006a25a0(void* self, uint32_t);
extern void  FUN_0068c700(ResourceKey* k, int);
extern void  FUN_0068c6d0(ResourceKey* k, uint32_t, int);
extern void* g_Manager;   // 0x15fd918

struct Notifier {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual void Post(uint32_t msg, void* payload, int, int); // slot 6 (+0x18)
};
Notifier* GetNotifier();     // FUN_0067dcc0

struct Messenger {           // FUN_0067de30 result; vtable slot 11 (+0x2c) = send
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void Send(uint32_t id, uint32_t tagged, RefCounted** outRef);
};
Messenger* GetMessenger();   // FUN_0067de30

struct SlotMap {};           // lives at EditorList+0xc8
extern void  SlotMap_Lookup(SlotMap* m, void* outIter, uint32_t idx);        // FUN_00420270
extern void  SlotMap_Locate(SlotMap* m, void* outIter, uint32_t idx);        // FUN_00420120
extern void  SlotMap_Insert(SlotMap* m, void* rec, uint32_t idx);            // FUN_004204f0
extern void  SlotMap_Replace(SlotMap* m, void* rec, uint32_t idx);           // FUN_004204d0
extern void  SlotMap_Commit(SlotMap* m, void* it);                           // FUN_00420390

struct EditorList {
    char pad[0xc8];
    SlotMap slots;
    // @ 0x0040a170
    void ApplyEntry(const ResourceKey* key, const KeyFlags* info);
    // @ 0x0040a590
    bool HandleKey(const ResourceKey* key, const KeyFlags* info);
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool Accept(const ResourceKey* k, bool extra);   // slot 7 (+0x1c)
};
extern void  EditorList_Prepare(EditorList* self, ResourceKey* k);           // FUN_00407280
extern void  EditorList_Forward(EditorList* self, ResourceKey* k, const void* extra); // FUN_004157d0
extern void  EditorList_ForwardKeyed(EditorList* self, ResourceKey* k, const KeyFlags* i); // FUN_0040a170 callee style

// @ 0x0040a170
void EditorList::ApplyEntry(const ResourceKey* key, const KeyFlags* info)
{
    struct Iter { uint32_t a, b; } it, found;
    SlotMap_Lookup(&slots, &it, info->index);
    SlotMap_Locate(&slots, &found, info->index);
    (void)key;
    bool exists = (it.a == found.a);
    if (exists) {
        ResourceKey rec = *key;
        RefCounted* out = 0;
        Messenger* m = GetMessenger();
        m->Send(key->instance, (key->group & 0xffff00ffu) | (0x62u << 8), &out);
        if (out) { RefCounted* r = out; out = 0; r->Release(); }
        m = GetMessenger();
        m->Send(key->instance, (key->group & 0xffff00ffu) | (0x7eu << 8), 0);
        if (info->flags & 1)
            SlotMap_Insert(&slots, &rec, info->index);
        else
            SlotMap_Replace(&slots, &rec, info->index);
    } else {
        if (info->flags & 0x100) {
            EntryRec* e = (EntryRec*)FUN_005658b0(&found);
            e->flags |= 0x100;
        }
        if (info->flags & 1) {
            // copy-construct a record and insert it
            ResourceKey rec = *key;
            SlotMap_Commit(&slots, &rec);
            SlotMap_Insert(&slots, &rec, info->index);
        }
    }
}

static inline bool IsEditorType(const ResourceKey* k)
{
    return k->type == 0x2b978c46 || k->type == 0x438f6347 || k->type == 0x3d97a8e4;
}

// @ 0x0040a590
bool EditorList::HandleKey(const ResourceKey* key, const KeyFlags* info)
{
    bool needNotify = false;
    if (((key->group >> 30) & 3) == 0)
        needNotify = true;
    else if (FUN_00401d90(key))
        needNotify = true;

    if (needNotify) {
        uint32_t* msg = (uint32_t*)EASTL_allocator_allocate(0x40, "Editor", 0, 0, 0, 0);
        if (msg) {
            FUN_00423110(msg, 0x695e243);
            msg[2] = 0; // fields written below
        }
        msg[2]  = key->instance;
        msg[4]  = key->group;
        msg[6]  = key->type;
        msg[8]  = info->id;
        msg[10] = 1;
        GetNotifier()->Post(0x695e243, msg, 0, 0);
        return false;
    }

    if (IsEditorType(key)) {
        struct { uint32_t id; uint16_t f; uint16_t i; } ki = { info->id, info->flags, info->index };
        ResourceKey k = *key;
        if (((key->group >> 16) & 0xff) == 0x6b) ki.f |= 0x10;
        if (((k.group >> 16) & 0xff) == 0x62) FUN_0068c700(&k, 0);
        EditorList_Forward(this, &k, &ki);
        return true;
    }

    ResourceKey k = *key;
    if (((key->group >> 8) & 0xff) == 0x7e) FUN_0068c6d0(&k, 0x62, 0);

    bool handled = false;
    if (!(info->flags & 0x20) && FUN_006a25a0(g_Manager, 0x26cd3a5))
        handled = Accept(&k, (info->flags & 0x100) != 0);

    if (handled) {
        uint32_t* msg = (uint32_t*)EASTL_allocator_allocate(0x40, "Editor", 0, 0, 0, 0);
        if (msg) FUN_00421c80(msg, 0x695e243);
        msg[2]  = key->instance;
        msg[4]  = key->group;
        msg[6]  = key->type;
        msg[8]  = info->id;
        msg[10] = 0;
        GetNotifier()->Post(0x695e243, msg, 0, 0);
        return true;
    }
    EditorList_Prepare(this, &k);
    ApplyEntry(&k, info);
    return true;
}
