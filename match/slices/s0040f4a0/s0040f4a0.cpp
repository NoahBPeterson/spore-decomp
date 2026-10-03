// Message handlers of a UI/game-mode object (unoptimized module: /Od /Ob1), tail of the
// handler set whose first half lives in slice s0040e5b0 (dispatcher 0x0040e800).
// Flags for the manifest: /Od /Ob1 /MD /Gy /EHsc /TP
#include "types.h"
#include <new>

extern "C" long _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)

#define PAD10(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); \
                 virtual void p##4(); virtual void p##5(); virtual void p##6(); virtual void p##7(); \
                 virtual void p##8(); virtual void p##9();

// ---- external functions ----
void* __cdecl operator new(size_t size, const char* tag, int, int, int, int) throw();  // EASTL_allocator_allocate
void  __cdecl FreeBlock(void* p);                                                  // EASTL_allocator_deallocate

extern void* vtMsgBase[];      // 0x013EB918  (base message class vtable)
extern void* vtMsgRef[];       // 0x013EB90C  (refcounted message vtable)
extern void* vtMsgOut[];       // 0x013EB844  (concrete 0x40-byte message vtable)
extern const char g_GraphicsTag[];  // "Graphics" @ 0x013EB8A4 (used inline as a literal below)

// ---- message objects ----
struct Variant { uint32_t value; uint32_t tag; };       // 8-byte argument slot

// Argument block living at +8 of every message.
struct ArgList {
    Variant v[1];
    void Set(int i, uint32_t x) { v[i].value = x; }
};

// Incoming message: arguments are 8-byte slots starting at +8.
struct MsgIn {
    void* vptr;
    long refs;
    Variant args[4];
    uint32_t Arg(int i) { return args[i].value; }
};

struct MsgIdBlock {                                     // embedded id holder at +8
    char pad[0x28];
    uint32_t id;                                        // msg + 0x30
    void Set(uint32_t x) { id = x; }
};
// FUN_0040fd50: base constructor shared by the message classes.
struct MsgRefInit { void** vptr; long refs; MsgRefInit* Ctor(); };

// Outgoing message core (0x38 bytes). Constructor is FUN_00423110 (out of line).
// The vtable is addressed by hand: slot 1 = AddRef, slot 2 = Release.
struct MsgCore {
    void** vptr;
    long refs;                                          // +4
    ArgList args;                                       // +8
    char argsPad[0x30 - 0x08 - sizeof(ArgList)];
    uint32_t id;                                        // +0x30
    uint32_t pad34;
    MsgCore(uint32_t id);                               // FUN_00423110
};
struct MsgOut : MsgCore {                               // 0x40 bytes
    uint32_t f38;                                       // +0x38
    uint32_t pad3c;
    MsgOut(uint32_t i) : MsgCore(i) { vptr = vtMsgOut; f38 = 0; }
    void AddRef()  { ((void (__thiscall*)(MsgOut*))vptr[1])(this); }
    void Release() { ((void (__thiscall*)(MsgOut*))vptr[2])(this); }
};
// Same message with the whole constructor chain expanded inline (used by 0x0040FC00).
struct MsgOutInl {
    void** vptr;
    long refs;
    ArgList args;
    char argsPad[0x30 - 0x08 - sizeof(ArgList)];
    uint32_t id;
    uint32_t pad34;
    uint32_t f38;
    uint32_t pad3c;
    MsgOutInl(uint32_t newId) {
        MsgIdBlock* h = (MsgIdBlock*)((char*)this + 8);
        h->Set(newId);
        ((MsgRefInit*)this)->Ctor();
        vptr = vtMsgRef;
        vptr = vtMsgOut;
        f38 = 0;
    }
    void AddRef()  { ((void (__thiscall*)(MsgOutInl*))vptr[1])(this); }
    void Release() { ((void (__thiscall*)(MsgOutInl*))vptr[2])(this); }
};

// ---- BakeSprites (0x20 bytes, intrusive refcount: slot0 AddRef, slot1 Release) ----
struct SpriteItem;
int __fastcall LookupOffset(SpriteItem* elem);          // FUN_0041d870 (ecx = element)
struct SpriteItem {
    uint32_t v;
    operator uint32_t() { return v; }
    int Offset() { return LookupOffset(this); }
};
struct SpriteList {                                     // begin/end of a pointer vector at +0xC
    SpriteItem* begin;
    SpriteItem* end;
    int Size() { return (int)(end - begin); }
    SpriteItem& operator[](int i) { return begin[i]; }
    void Prepare(int n);                                // FUN_00421bf0
};
struct BakeSprites {
    virtual void AddRef();
    virtual void Release();
    uint32_t pad04;
    uint32_t pad08;
    SpriteList list;                                    // +0xC
    uint32_t pad14, pad18, pad1c;
    BakeSprites();                                      // Graphics::BakeSprites::BakeSprites (0x7B00F0)
};

// ---- smart pointer used for the sprite baker / services ----
template <class T>
struct RefPtr {
    T* p;
    RefPtr(T* x) : p(x) { if (p) p->AddRef(); }
    RefPtr(const RefPtr& o) : p(o.p) { if (p) p->AddRef(); }
    ~RefPtr() { if (p) p->Release(); }
    T* operator->() { return p; }
    T* get() { return p; }
    void Assign(T* x) {
        if (x != p) {
            T* old = p;
            if (x) x->AddRef();
            p = x;
            if (old) old->Release();
        }
    }
};
struct IMsg {                                           // refcounted message interface
    virtual void v0();
    virtual void AddRef();                              // slot 1
    virtual void Release();                             // slot 2
};
struct MsgPtr {                                         // intrusive ptr to a message
    IMsg* p;
    IMsg* get() { return p; }
    MsgPtr(IMsg* x) : p(x) { if (p) p->AddRef(); }
    ~MsgPtr() { if (p) p->Release(); }
    IMsg* operator->() { return p; }
};

// ---- service stubs ----
struct DeviceInfo {                                     // FUN_0067dd40() result
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    PAD10(a) PAD10(b) PAD10(c) PAD10(d)
    virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
    virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58();
    virtual void GetKinds(int which, uint32_t* out3);   // slot 59 (0xEC)
};
struct Dispatcher {                                     // FUN_0067dcc0() result
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Post(uint32_t id, void* msg, int flag);  // slot 5 (0x14)
};
struct SpriteService {                                  // FUN_0068f4d0() result
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7();
    virtual void AddRef();                              // slot 8 (0x20)
    virtual void Release();                             // slot 9 (0x24)
};
struct SvcRef {                                         // non-null-checked reference holder
    SpriteService* p;
    SvcRef(SpriteService* x) : p(x) { uint32_t scratch[3]; p->AddRef(); }
    ~SvcRef() { p->Release(); }
};
struct Prop {
    char pad[0x12];
    uint16_t type;
    int* AsInt();                                       // FUN_0041e990
    bool* AsBool();                                     // FUN_0041e920
};
struct Provider {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProp(uint32_t id, Prop** out);      // slot 9 (0x24)
};

DeviceInfo* GetDeviceInfo();                            // FUN_0067dd40
Dispatcher* GetDispatcher();                            // FUN_0067dcc0
SpriteService* GetSpriteService();                      // FUN_0068f4d0
void __cdecl BakeOne(uint32_t item, int off, int kind, int index, uint32_t msgId, void* msg);   // FUN_007b06c0
void __cdecl BakeMain(uint32_t a, void* list, uint32_t msgId, void* msg);   // FUN_007b1710
void __cdecl BakeAlt(uint32_t a, void* list, uint32_t msgId, void* msg);    // FUN_007b1830

// ---- the handler object ----
inline SpriteList* ListPtr(RefPtr<BakeSprites>& r)
{
    BakeSprites* lp_init;
    BakeSprites* lp_t = lp_init;
    lp_t = r.get();
    return lp_t ? &lp_t->list : 0;
}
struct KindInfo {                                       // 3 ids returned by DeviceInfo::GetKinds + a selector
    uint32_t id[3];
    uint32_t sel;
};
struct PtrHolder {
    void* p;
    void* get() { return p; }
};
struct Obj {
    char p0[0x23c];
    PtrHolder holder23c;
    char p1[0x24c - 0x240];
    Provider* provider;                                 // 0x24c
    char p2[0x259 - 0x250];
    bool flag259;
    char p3[0x117c - 0x25a];
    RefPtr<BakeSprites> bake;                                       // 0x117c
    uint8_t counter;                                    // 0x1180

    // Reads an integer property of the given type through the provider (inlined helper).
    inline bool ReadIntProp(uint32_t id, int type, int* out)
    {
        Provider* pr = provider;
        Prop* q;
        if (pr) {
            if (pr->GetProp(id, &q) && q->type == type) {
                *out = *q->AsInt();
                return true;
            }
        }
        return false;
    }

    // Reads a boolean property through the provider (inlined helper).
    inline void ReadBoolProp(uint32_t id, int type, bool* out)
    {
        Provider* pr = provider;
        Prop* q;
        if (pr) {
            if (pr->GetProp(id, &q) && q->type == type)
                *out = *q->AsBool();
        }
    }

    bool Fn40f4a0(MsgIn* in);
    bool Fn40f820(MsgIn* in);
    bool Fn40fc00(MsgIn* in);
};

// @ 0x0040f4a0
bool Obj::Fn40f4a0(MsgIn* in)
{
    if (!(flag259 && holder23c.get() != 0))
        return false;
    uint32_t cat2[3] = { 0, 0, 0 };
    uint32_t kind[3] = { 0, 0, 0 };
    uint32_t layer[3] = { 0, 0, 0 };
    GetDeviceInfo()->GetKinds(2, cat2);
    GetDeviceInfo()->GetKinds(4, kind);
    GetDeviceInfo()->GetKinds(3, layer);
    MsgIn* param = in;
    uint32_t aux = param->Arg(1);
    uint32_t selKind = param->Arg(2);
    if (selKind == cat2[0] || selKind == kind[0] || selKind == layer[0]) {
        bool useAlt;
        uint32_t outMsgId;
        uint32_t arg0 = param->Arg(0);
        outMsgId = 0x530781E;
        if (selKind == cat2[0] || selKind == kind[0])
            outMsgId = 0x52DEB99;
        bake.Assign(new ("Graphics", 0, 0, 0, 0) BakeSprites());
        MsgPtr outMsg((IMsg*)new ("Graphics", 0, 0, 0, 0) MsgOut(outMsgId));
        ((MsgOut*)outMsg.p)->args.Set(1, selKind);
        useAlt = false;
        ReadBoolProp(0x680A2B1, 1, &useAlt);
        if (useAlt) {
            BakeAlt(arg0, ListPtr(bake), outMsgId, outMsg.p);
        } else {
            BakeMain(arg0, ListPtr(bake), outMsgId, outMsg.p);
        }
        return true;
    }
    return false;
}

// @ 0x0040f820
bool Obj::Fn40f820(MsgIn* in)
{
    MsgIn* m = in;
    uint32_t kind = m->Arg(1);
    MsgPtr msg((IMsg*)new ("Graphics", 0, 0, 0, 0) MsgOut(0x5302B02));
    ((MsgOut*)msg.p)->args.Set(1, kind);
    int val;
    if (ReadIntProp(0x52F7B17, 9, &val)) {
        int cat = -1;
        int idx = -1;
        if (val >= 500) {
            cat = 6;
            idx = val - 500;
        } else if (val >= 300) {
            cat = 5;
            idx = val - 300;
        } else if (val >= 100) {
            cat = 4;
            idx = val - 100;
        }
        if (idx >= 0 && idx < 100) {
            RefPtr<BakeSprites> bs(bake);
            bake.Assign(new ("Graphics", 0, 0, 0, 0) BakeSprites());
            bake->list.Prepare(bs->list.Size());
            SvcRef svc(GetSpriteService());
            for (int i = 0, n = bake->list.Size(); i < n; i++) {
                BakeOne(bs->list[i], bake->list[i].Offset(), cat, idx, 0x5302B02, msg.get());
            }
            return true;
        }
    }
    GetDispatcher()->Post(0x530781E, msg.p, 0);
    return true;
}

// @ 0x0040fc00
bool Obj::Fn40fc00(MsgIn* in)
{
    counter++;
    if (counter == bake->list.Size()) {
        counter = 0;
        MsgIn* m = in;
        uint32_t kind = m->Arg(1);
        MsgPtr msg((IMsg*)new ("Graphics", 0, 0, 0, 0) MsgOutInl(0x530781E));
        ((MsgOutInl*)msg.p)->args.Set(1, kind);
        GetDispatcher()->Post(0x530781E, msg.p, 0);
    }
    return true;
}

// @ 0x0040fd50
MsgRefInit* MsgRefInit::Ctor()
{
    vptr = vtMsgBase;
    vptr = vtMsgRef;
    volatile long* p = &refs;
    _InterlockedExchange(p, 0);
    return this;
}

// @ 0x0040fd90, 0x0040fdc0: scalar-deleting destructors of the two message classes
struct MsgDel {
    void** vptr;
    MsgDel* DelBase(uint32_t flags);
    MsgDel* DelRef(uint32_t flags);
};
// @ 0x0040fd90
MsgDel* MsgDel::DelBase(uint32_t flags)
{
    vptr = vtMsgBase;
    if (flags & 1) FreeBlock(this);
    return this;
}
// @ 0x0040fdc0
MsgDel* MsgDel::DelRef(uint32_t flags)
{
    vptr = vtMsgRef;
    vptr = vtMsgBase;
    if (flags & 1) FreeBlock(this);
    return this;
}

