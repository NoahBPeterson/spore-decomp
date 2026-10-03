#include "types.h"
// Editor / creature-ability "bake sprites" support. Built /Od /Ob1 /MD /Gy /TP /GS- (no EH).
extern "C" long _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)
void __fastcall MemberInit(void* m);   // 0x0041d3c0
void __fastcall MemberDtor(void* m);   // 0x004b5440
void __cdecl Dealloc(void*);           // 0x00f47380 EASTL_allocator_deallocate
extern void* vtEditorResource[];       // 0x013eb938
extern void* vtAbility[];              // 0x013ef094

struct P { virtual void p0(); };
struct A : P { virtual void p0(); };
struct RefCount { long rc; RefCount() { _InterlockedExchange(&rc, 0); } };
struct Ability { virtual void a0(); RefCount rc; };
// Editor bake-sprites ability object (0xc4 bytes), allocated under the tag "Editor".
struct D : A, Ability {
    char member[0xb8];
    D();
    D* Destroy(unsigned flags);
};
// @ 0x0041a980
D::D() { uint32_t t; (void)t; MemberInit(member); }
// @ 0x0041a9f0
D* D::Destroy(unsigned flags) {
    uint32_t t[5]; (void)t;
    MemberDtor(member);
    *(void***)((char*)this + 4) = vtAbility;
    *(void***)this = vtEditorResource;
    if (flags & 1) Dealloc(this);
    return this;
}

inline void* operator new(unsigned, void* p) { return p; }

// Editor: after a creature-editor part edit, rebuild the three property lists (0x71xx, 0x62xx, 0x1006200 variants of the
// resource key bitfield), copy properties between them, post a BehaviorMessage (0xf62def) and register an
// "Editor" ability with the creature.
struct ResKey {
    uint32_t a : 8;
    uint32_t type : 8;     // bits 8..15: 0x71 / 0x62
    uint32_t b : 8;
    uint32_t c : 5;        // bits 24..28: 1 for the third key
    uint32_t d : 3;
    inline ResKey WithType(int t) const { ResKey r = *this; r.type = t; return r; }
    inline ResKey WithC(int v) const { ResKey r = *this; r.c = v; return r; }
};
struct PropList;
struct Value { uint32_t a, b, c; };

struct PropList {
    virtual void v0();
    virtual void Release();          // +4
    virtual void v2(); virtual void v3();
    virtual void SetProp(uint32_t id, void* v);   // +0x14 (index 5)
    virtual void v6();
    virtual bool HasProp(uint32_t id);            // +0x1c (index 7)
    virtual void v8(); virtual void v9();
    virtual void* GetProp(uint32_t id);           // +0x28 (index 10)
    virtual void CopyFrom(PropList* o);           // +0x2c (index 11)
};
struct ResMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void GetResource(uint32_t group, uint32_t key, void** out);   // +0x2c
};
struct Dispatcher {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool Load(Value* v, void** out, int, int, int, int);  // +0xc
};
struct MsgDispatcher {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Post(uint32_t msgid, void* msg, int);   // +0x14
};
struct MsgArg { uint32_t v, pad; };
struct BehaviorMessage {
    void* vtbl; uint32_t pad4;
    MsgArg args[3];
    uint32_t pad20[4];
    uint32_t msgId;          // +0x30
    uint32_t pad34;
    uint32_t field38;
    inline MsgArg& Arg(int i) { return args[i]; }
};
struct Variant { char data[16]; uint16_t flags; uint16_t type; };
struct AbilityIface { virtual void v0(); virtual void Release(); };

extern void* vtMsg[]; extern void* vtBehavior[];
ResMgr* __cdecl GetResMgr();                 // 0x0067de30
void** __fastcall OutPtr(void** pp);         // 0x0041d870
bool __cdecl PropGet(void* list, uint32_t id, void* out);    // 0x006a1250
bool __cdecl IsUserCreature();               // 0x00461510 (placeholder name)
Dispatcher* __cdecl GetLoader();             // 0x0067dcd0
void* __cdecl Deref(void** pp);              // 0x00422ab0
void __fastcall CopyIt(void* dst, void* src);// 0x004535d0
void __fastcall MsgInit(void* m, uint32_t id);   // 0x00423110
MsgDispatcher* __cdecl GetMsgs();            // 0x0067dcc0
void __fastcall ValueCopy(void* dst, void* src); // 0x00422f40
void __fastcall ValueFree(void* v, int);     // 0x0093db80
void __fastcall BehInit(void* m);            // 0x0040fd50
void __fastcall MsgFree(void* m);            // 0x00421cf0
bool __fastcall IsBusy(void* p);             // 0x00526430
void* __cdecl Alloc(uint32_t sz, const char* name, int, int, int, int);  // 0x00f473a0
void __fastcall Register(AbilityIface* a, uint32_t id, uint32_t key);   // 0x00418500
void* __cdecl Fun401010(void* a, void* b, void* c);   // 0x00401010
void __fastcall Fun4147b0(void* r);          // 0x004147b0

struct EditorBake {
    EditorBake();
    virtual void AddRef();
    virtual void Release();
};

struct Part {
    char pad0[0x10];
    uint32_t id;          // +0x10
    char pad1[4];
    ResKey key;           // +0x18
    char pad2[4];
    uint16_t flags;       // +0x20
    char pad3[2];
    void* owner;          // +0x24
    bool Bake();
};

// @ 0x0041a0c0
bool Part::Bake()
{
    PropList* A; PropList* B; PropList* C;
    EditorBake* ed;
    ResKey k71 = key.WithType(0x71);
    ResKey k62 = key.WithType(0x62);
    ResKey k3 = k62.WithC(1);
    if (!(flags & 0x10)) {
        A = 0; B = 0; C = 0;
        GetResMgr()->GetResource(id, *(uint32_t*)&k71, OutPtr((void**)&A));
        GetResMgr()->GetResource(id, *(uint32_t*)&k62, OutPtr((void**)&B));
        GetResMgr()->GetResource(id, *(uint32_t*)&k3, OutPtr((void**)&C));
        if (B && A) {
            if (IsUserCreature()) {
                PropList* X = 0; PropList* Y = 0;
                Value v = {0, 0, 0};
                if (PropGet(B, 0xf9efbb, &v)) {
                    if (GetLoader()->Load(&v, OutPtr((void**)&X), 0, 0, 0, 0)) {
                        if (PropGet(A, 0xf9efbb, &v)) {
                            if (GetLoader()->Load(&v, OutPtr((void**)&Y), 0, 0, 0, 0)) {
                                char* r1 = (char*)Deref((void**)&X);
                                char* r2 = (char*)Deref((void**)&Y);
                                if (r1 && r2)
                                    CopyIt(r2 + 0x13c, *(void**)(r1 + 0x13c));
                            }
                        }
                    }
                }
                if (Y) Y->Release();
                if (X) X->Release();
            }
            for (int i = 0; i < 4; i++) {
                if (A->HasProp(i + 0xf9efbb))
                    B->SetProp(i + 0xf9efbb, A->GetProp(i + 0xf9efbb));
            }
            BehaviorMessage m1;
            MsgInit(&m1, 0xf62def);
            m1.vtbl = vtMsg;
            m1.field38 = 0;
            m1.Arg(0).v = 0xb1b104;
            m1.Arg(1).v = *(uint32_t*)&k62;
            m1.Arg(2).v = id;
            GetMsgs()->Post(0xf62def, &m1, 0);
            if (C) {
                Value arr[4];
                for (int j = 0; j < 4; j++) { arr[j].a = 0; arr[j].b = 0; arr[j].c = 0; }
                char found[4];
                for (int j = 0; j < 4; j++)
                    found[j] = PropGet(C, j + 0xf9efbb, &arr[j]);
                C->CopyFrom(B);
                for (int j = 0; j < 4; j++) {
                    if (A->HasProp(j + 0xf9efbb)) {
                        C->SetProp(j + 0xf9efbb, A->GetProp(j + 0xf9efbb));
                    } else if (found[j]) {
                        Variant t;
                        t.flags = 0; t.type = 0; t.type = 0x20; t.flags = 2;
                        ValueCopy(&t, &arr[j]);
                        C->SetProp(j + 0xf9efbb, &t);
                        if (t.flags & 4) ValueFree(&t, 0);
                    }
                }
                BehaviorMessage m2;
                BehInit(&m2);
                m2.msgId = 0xf62def;
                m2.vtbl = vtBehavior; m2.vtbl = vtMsg;
                m2.field38 = 0;
                m2.Arg(0).v = 0xb1b104;
                m2.Arg(1).v = *(uint32_t*)&k3;
                m2.Arg(2).v = id;
                GetMsgs()->Post(0xf62def, &m2, 0);
                MsgFree(&m2);
            }
            MsgFree(&m1);
        }
        if (C) C->Release();
        if (B) B->Release();
        if (A) A->Release();
    }
    if (IsBusy((char*)(*(char**)((char*)owner + 8)) + 0x98))
        return true;
    void* mem = Alloc(0xc4, "Editor", 0, 0, 0, 0);
    ed = mem ? new (mem) EditorBake() : 0;
    if (ed) ed->AddRef();
    Register((AbilityIface*)ed, id, *(uint32_t*)&k62);
    Register((AbilityIface*)ed, id, *(uint32_t*)&k3);
    Fun4147b0(Fun401010(owner, (char*)this + 0x1c, ed));
    if (ed) ed->Release();
    return true;
}
