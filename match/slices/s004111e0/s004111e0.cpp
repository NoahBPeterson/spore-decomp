// Editor UI panel (strings "Editor", UI::BehaviorMessage): two selection-message routines.
// Built unoptimized, no EH, no /GS: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS-
// Both functions are behaviorally-equivalent best attempts, NOT byte-exact (see nonmatching.txt).
#include "types.h"

namespace SendSel {

extern void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, uint32_t a, uint32_t b, uint32_t c, uint32_t d);

struct Variant {
    uint8_t data[16];
    uint16_t flags;
    uint16_t type;
    void SetFlags(uint16_t f) { flags = f; }
    void SetType(uint16_t t) { type = t; }
    void Construct(const bool* b);
    void Free(int);
    Variant(const bool* b) { SetFlags(0); SetType(0); SetType(1); SetFlags(2); Construct(b); }
    ~Variant() { if (flags & 4) Free(0); }
};

struct Id {
    uint32_t raw;
    uint32_t Type() const { return (raw >> 16) & 0xff; }
    void SetClass(uint32_t v) { raw = (raw & 0xe0ffffff) | ((v & 0x1f) << 24); }
};
inline Id WithClass(Id i, uint32_t c) { i.SetClass(c); return i; }
inline uint32_t TypeOf(uint32_t raw) { return (raw >> 16) & 0xff; }

struct Slots {
    struct Slot { uint32_t v, pad; } slot[5];
    uint32_t id30;
    uint32_t pad34;
    void Set(int i, uint32_t v) { slot[i].v = v; }
    void SetF(int i, float v) { *(float*)&slot[i].v = v; }
};
struct Msg {
    void* vtbl;
    uint32_t pad4;
    Slots s;
    uint32_t f38;
    uint32_t pad3c;
    Msg(uint32_t id);        // 0x423110
    void Base2Init();        // 0x40fd50
    void Destroy();          // 0x421cf0
    void Set(int i, uint32_t v) { s.Set(i, v); }
    void SetF(int i, float v) { s.SetF(i, v); }
};

struct MsgMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void Post(uint32_t id, Msg* m, uint32_t a, uint32_t b);
};

struct Target {
    virtual void v0();
    virtual void Release();                         // +4
    virtual void v2(); virtual void v3(); virtual void v4();
    virtual void SetProp(uint32_t id, Variant* v);  // +0x14
    virtual void v6();
    virtual bool Has(uint32_t id);                  // +0x1c
};

struct TRef {
    Target* p;
    Target** Out();                 // 0x41d870
    bool Has(uint32_t id) { return p->Has(id); }
    void SetBool(uint32_t id, bool b) { Variant v(&b); p->SetProp(id, &v); }
};

struct Lookup {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void Find(uint32_t a, uint32_t b, Target** out);   // +0x2c
};

struct Params { uint32_t a, b, c; };

extern MsgMgr* __cdecl GetMsgMgr();
extern Lookup* __cdecl GetLookup();
extern void __cdecl FreeTarget(Target* t, int);

struct Panel {
    uint8_t pad0[0x234];
    uint32_t arg234;
    uint16_t flags238;
    uint8_t pad23a[0x258 - 0x23a];
    uint8_t sentFlag;

    void PostSelectionMessages(Params* p, float f1, float f2);
};

#define NEW_HMSG(var, idv) \
    Msg* tmp##var; \
    void* raw##var = EASTL_allocator_allocate(0x40, "Editor", 0, 0, 0, 0); \
    if (raw##var) { \
        Slots* sl = (Slots*)((char*)raw##var + 8); \
        sl->id30 = idv; \
        ((Msg*)raw##var)->Base2Init(); \
        ((Msg*)raw##var)->vtbl = (void*)0x13eb90c; \
        ((Msg*)raw##var)->vtbl = (void*)0x13eb844; \
        ((Msg*)raw##var)->f38 = 0; \
        tmp##var = (Msg*)raw##var; \
    } else tmp##var = 0; \
    var = tmp##var;

// @ 0x004111e0
void Panel::PostSelectionMessages(Params* p, float f1, float f2)
{
    Msg* mm;
    Msg* m2;
    bool owns = !(flags238 & 2);
    TRef target;
    target.p = 0;
    GetLookup()->Find(p->a, p->c, target.Out());
    if (target.p) {
        if (target.Has(0x3704e55)) {
            target.SetBool(0x3704e55, true);
            Msg m(0xf62def);
            m.vtbl = (void*)0x13eb844;
            m.f38 = 0;
            m.Set(0, 0xb1b104);
            m.Set(1, p->c);
            m.Set(2, p->a);
            GetMsgMgr()->Post(0xf62def, &m, 0, 0);
            if (owns) FreeTarget(target.p, 1);
            m.Destroy();
        }
    }
    uint32_t idc = p->c;
    if (TypeOf(idc) == 0x62) {
        Id id2 = WithClass(*(Id*)&p->c, 1);
        GetLookup()->Find(p->a, id2.raw, target.Out());
        if (target.p) {
            if (target.Has(0x3704e55)) {
                target.SetBool(0x3704e55, true);
                Msg m(0xf62def);
                m.vtbl = (void*)0x13eb844;
                m.f38 = 0;
                m.Set(0, 0xb1b104);
                m.Set(1, id2.raw);
                m.Set(2, p->a);
                GetMsgMgr()->Post(0xf62def, &m, 0, 0);
                if (owns) FreeTarget(target.p, 1);
                m.Destroy();
            }
        }
    }
    NEW_HMSG(mm, 0x4d18324)
    mm->Set(0, p->a);
    mm->Set(1, p->c);
    mm->Set(2, p->b);
    mm->SetF(3, f1);
    mm->SetF(4, f2);
    GetMsgMgr()->Post(0x4d18324, mm, 0, 0);
    NEW_HMSG(m2, 0x695e243)
    m2->Set(0, p->a);
    m2->Set(1, p->c);
    m2->Set(2, p->b);
    m2->Set(3, arg234);
    m2->Set(4, 0);
    GetMsgMgr()->Post(0x695e243, m2, 0, 0);
    sentFlag = 1;
    if (target.p) target.p->Release();
}

}

namespace ResetSel {

struct TmpA { uint32_t d[12]; TmpA* Init(); void Fini(); };
struct TmpB { uint32_t d[0xdd0/4]; TmpB* Init(); void Fini(); };
struct Preloader { void Reset(); };
struct Obj330 { void Release(int); void Free(); };
struct SPtr {
    Obj330* p;
    Obj330* Get() { return p; }
    Obj330* operator->() { return p; }
    void Reset() {
        if (p) {
            Obj330* o = p;
            p = 0;
            if (o) o->Free();
        }
    }
};
struct Sel { void Set(const TmpA*); };
struct PtrHolder { void Set(const TmpB*); };

struct Msg {
    void* vtbl;
    uint32_t pad4;
    struct Slot { uint32_t v, pad; } slot[5];
    uint32_t id30;
    uint32_t pad34;
    uint32_t f38;
    uint32_t pad3c;
    Msg(uint32_t id);
    static void* operator new(unsigned size, const char* name);
    void Set(int i, uint32_t v) { slot[i].v = v; }
};

struct BMsg : Msg {
    BMsg(uint32_t id) : Msg(id) { vtbl = (void*)0x13eb844; f38 = 0; }
};
extern void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, uint32_t a, uint32_t b, uint32_t c, uint32_t d);
inline void* Msg::operator new(unsigned size, const char* name) { return EASTL_allocator_allocate(size, name, 0, 0, 0, 0); }

struct MsgMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void Post(uint32_t id, Msg* m, uint32_t a, uint32_t b);
};

struct Panel {
    uint8_t pad0[0x228];
    uint32_t selId;      // 0x228
    uint32_t arg22c;
    uint32_t arg230;
    uint32_t arg234;
    uint8_t pad238[0x258 - 0x238];
    uint8_t sentFlag;    // 0x258
    uint8_t flag259;
    uint8_t pad25a[2];
    Preloader preloader; // 0x25c
    uint8_t pad25d[0x2c4 - 0x25d];
    uint8_t flag2c4;
    uint8_t pad2c5[0x330 - 0x2c5];
    SPtr obj330;      // 0x330

    void CommitAndReset(bool flag);
};

extern void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, uint32_t a, uint32_t b, uint32_t c, uint32_t d);
extern MsgMgr* __cdecl GetMsgMgr();

// @ 0x00411890
void Panel::CommitAndReset(bool flag)
{
    TmpB b;
    if ((flag2c4 || flag259) && !sentFlag && selId != 0 && selId != (uint32_t)-1) {
        Msg* m = new ("Editor") BMsg(0x695e243);
        m->Set(0, selId);
        m->Set(1, arg230);
        m->Set(2, arg22c);
        m->Set(3, arg234);
        m->Set(4, (flag != 0) + 1);
        GetMsgMgr()->Post(0x695e243, m, 0, 0);
    }
    preloader.Reset();
    { TmpA a; ((Sel*)&selId)->Set(a.Init()); a.Fini(); }
    if (obj330.Get()) {
        obj330->Release(1);
        obj330.Reset();
    }
    ((PtrHolder*)&obj330)->Set(b.Init()); b.Fini();
    flag2c4 = 0;
    flag259 = 0;
    sentFlag = 0;
}

}
