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

// 0x1c-byte container iterator returned by the slot map (420270 / 420120 / find_if).
struct Iter28 { uint32_t v[7]; };

// 0x30-byte keyed record stored in the slot map: v[0..2] key, v[3] info->id,
// v[4] flags|index<<16, v[5..11] refcounted pointers (all zero unless set below).
struct KeyedRecord { uint32_t v[12]; };

// External helpers (addresses are relocations in the original).  The container helpers take
// `this` in ECX and pop their stack arguments themselves (ret N), which is what __fastcall +
// an unused EDX filler produces from plain C++.
extern void* EASTL_allocator_allocate(uint32_t size, const char* name, uint32_t, uint32_t, uint32_t, uint32_t);  // @ 0x00f473a0
extern void  __fastcall FUN_004036e0(void* self);                                   // KeyedRecord ctor
extern void* __fastcall FUN_00401e40(void* self);                                   // 0x18-byte modifier ctor
extern void  __fastcall FUN_00401ef0(void* self, int, const ResourceKey* key);      // set key (ret 4)
extern void  __fastcall FUN_00401f20(void* self);                                   // KeyedRecord dtor
extern void* __fastcall FUN_005658b0(void* self);                                   // *(void**)self
extern void  __fastcall FUN_004063d0(void* self, int, const KeyedRecord* src);      // KeyedRecord copy ctor (ret 4)
extern void  __fastcall FUN_00453540(void* self);                                   // release a refcounted object
extern bool  FUN_00401d90(const ResourceKey* k);                                  // cdecl, 1 arg
extern void* __fastcall FUN_00423110(void* self, int, uint32_t);                  // ctor (ret 4)
extern void* __fastcall FUN_00421c80(void* self, int, uint32_t);                  // ctor (ret 4)
extern bool  __fastcall FUN_006a25a0(void* self, int, uint32_t);                  // ret 4
extern void  FUN_0068c700(ResourceKey* k, int);
extern void  FUN_0068c6d0(ResourceKey* k, uint32_t, int);
extern void* g_Manager;   // 0x15fd918

struct Notifier {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual void Post(uint32_t msg, void* payload, int, int); // slot 6 (+0x18)
};
Notifier* GetNotifier();     // FUN_0067dcc0  @ 0x0067dcc0

struct Messenger {           // FUN_0067de30 result; vtable slot 11 (+0x2c) = send
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void Send(uint32_t id, uint32_t tagged, RefCounted** outRef);
};
Messenger* GetMessenger();   // FUN_0067de30  @ 0x0067de30

struct SlotMap {};           // lives at EditorList+0xc8
// Container helpers: ECX = this, arguments on the stack, callee pops them (ret N).
extern void  __fastcall FUN_00420270(void* self, int, Iter28* out, uint32_t idx);             // upper_bound (ret 8)
extern void  __fastcall FUN_00420120(void* self, int, Iter28* out, uint32_t idx);             // lower_bound (ret 8)
extern void  __fastcall FUN_004204f0(void* self, int, const KeyedRecord* rec, uint32_t idx);  // push front (ret 8)
extern void  __fastcall FUN_004204d0(void* self, int, const KeyedRecord* rec, uint32_t idx);  // replace (ret 8)
extern void  __fastcall FUN_00420390(void* self, int, Iter28 it, void* out);                  // assign (ret 0x20)
extern Iter28* FUN_00422140(Iter28* out, Iter28 first, Iter28 last, const KeyFlags* info,
                            const ResourceKey* key);                                          // find_if

struct EditorList {
    char pad[0xc4];          // vptr + 0xc4 == slots at +0xc8
    SlotMap slots;
    void ApplyEntry(const ResourceKey* key, const KeyFlags* info);   // @ 0x0040a170
    bool HandleKey(const ResourceKey* key, const KeyFlags* info);    // @ 0x0040a590
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool Accept(const ResourceKey* k, bool extra);   // slot 7 (+0x1c)
};
extern void  __fastcall EditorList_Prepare(EditorList* self, int, ResourceKey* k);                 // FUN_00407280 (ret 4)
extern void  __fastcall EditorList_Forward(EditorList* self, int, ResourceKey* k, const void* extra); // FUN_004157d0 (ret 8)
extern void  EditorList_ForwardKeyed(EditorList* self, ResourceKey* k, const KeyFlags* i); // FUN_0040a170 callee style

// @ 0x0040a170
void EditorList::ApplyEntry(const ResourceKey* key, const KeyFlags* info)
{
    Iter28 last, first, cur, endIter;
    void* sm = &slots;

    FUN_00420270(sm, 0, &last, info->index);        // upper_bound(idx)
    FUN_00420120(sm, 0, &first, info->index);       // lower_bound(idx)
    FUN_00422140(&cur, first, last, info, key);     // find_if over [first,last)
    FUN_00420270(sm, 0, &endIter, info->index);     // upper_bound(idx) again (the "end")

    bool exists = (cur.v[0] == endIter.v[0]) &&
                  (cur.v[0] == cur.v[6] || cur.v[1] == endIter.v[1]);
    if (exists) {
        KeyedRecord rec;
        FUN_004036e0(&rec);                         // KeyedRecord ctor (tag, zeroed refs)
        void* mem = EASTL_allocator_allocate(0x18, "Editor", 0, 0, 0, 0);
        void* mod = mem ? FUN_00401e40(mem) : 0;
        // inline intrusive-ptr assign into rec.v[5]
        if (mod != (void*)rec.v[5]) {
            if (mod) ++*(uint32_t*)((char*)mod + 4);
            void* old = (void*)rec.v[5];
            rec.v[5] = (uint32_t)mod;
            if (old) FUN_00453540(old);
        }
        FUN_00401ef0(mod, 0, key);                  // modifier takes a copy of the key
        rec.v[0] = key->instance;
        rec.v[1] = key->type;
        rec.v[2] = key->group;
        rec.v[3] = info->id;
        rec.v[4] = info->flags | ((uint32_t)info->index << 16);
        Messenger* m = GetMessenger();
        m->Send(key->instance, (key->group & 0xffff00ffu) | (0x62u << 8), (RefCounted**)&rec.v[9]);
        m = GetMessenger();
        m->Send(key->instance, (key->group & 0xffff00ffu) | (0x7eu << 8), (RefCounted**)&rec.v[10]);
        if (info->flags & 1)
            FUN_004204f0(sm, 0, &rec, info->index);
        else
            FUN_004204d0(sm, 0, &rec, info->index);
        FUN_00401f20(&rec);
    } else {
        if (info->flags & 0x100) {
            KeyedRecord* e = (KeyedRecord*)FUN_005658b0(&cur.v[1]);
            *(uint16_t*)&e->v[4] |= 0x100;
        }
        if (info->flags & 1) {
            KeyedRecord* e = (KeyedRecord*)FUN_005658b0(&cur.v[1]);
            KeyedRecord rec;
            FUN_004063d0(&rec, 0, e);               // copy the slot's record
            uint32_t dst;
            FUN_00420390(sm, 0, cur, &dst);         // assign at the found iterator
            FUN_004204f0(sm, 0, &rec, info->index);
            FUN_00401f20(&rec);
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
    bool needNotify;
    if (((key->group >> 30) & 3) != 1)
        needNotify = true;
    else
        needNotify = FUN_00401d90(key);

    if (needNotify) {
        uint32_t* msg = (uint32_t*)EASTL_allocator_allocate(0x40, "Editor", 0, 0, 0, 0);
        if (msg) {
            FUN_00423110(msg, 0, 0x695e243);
            msg[0]  = 0x13eb844;   // message vtable
            msg[14] = 0;           // +0x38
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
        EditorList_Forward(this, 0, &k, &ki);
        return true;
    }

    ResourceKey k = *key;
    if (((key->group >> 8) & 0xff) == 0x7e) FUN_0068c6d0(&k, 0x62, 0);

    bool handled = false;
    if (!(info->flags & 0x20) && FUN_006a25a0(g_Manager, 0, 0x26cd3a5))
        handled = Accept(&k, (info->flags & 0x100) != 0);

    if (handled) {
        uint32_t* msg = (uint32_t*)EASTL_allocator_allocate(0x40, "Editor", 0, 0, 0, 0);
        if (msg) msg = (uint32_t*)FUN_00421c80(msg, 0, 0x695e243);
        msg[2]  = key->instance;
        msg[4]  = key->group;
        msg[6]  = key->type;
        msg[8]  = info->id;
        msg[10] = 0;
        GetNotifier()->Post(0x695e243, msg, 0, 0);
        return true;
    }
    EditorList_Prepare(this, 0, &k);
    ApplyEntry(&k, info);
    return true;
}
