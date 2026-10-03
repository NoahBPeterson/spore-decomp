// Message handlers of a UI/game-mode object (unoptimized module: /Od /Ob1).
// Flags for the manifest: /Od /Ob1 /MD /Gy /EHsc /TP
#include "types.h"

// ---- stub interfaces (vtable slots only) ----
struct Releasable {
    virtual void v0();
    virtual void Release();                 // slot 1
};
struct Msg {                                // FUN_0067dcc0() result: message dispatcher
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Post(uint32_t id, int a, int b);                 // slot 5
    virtual void Post4(uint32_t id, int a, int b, int c);         // slot 6
};
struct Sink {                               // FUN_0067de30() result
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual void Set(uint32_t v);                                 // slot 11
};
struct PathProvider {                       // returned by slot 11 of the app object
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15();
    virtual void* GetName();                                      // slot 16 (0x40)
    virtual uint32_t Lookup(uint32_t key, Releasable** out);      // slot 17 (0x44)
};
struct App {                                // FUN_0067dd10() result
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual PathProvider* GetPathProvider();                      // slot 11 (0x2c)
    virtual void v12(); virtual void v13();
    virtual uint32_t GetKind();                                   // slot 14 (0x38)
};
struct Dir {                                // FUN_006b1f90() result
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual const wchar_t* GetDirName();                          // slot 10 (0x28)
};
struct Prop {                               // object queried through slot 9 (0x24)
    char pad[0x12];
    uint16_t type;
};
struct Provider {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProp(uint32_t id, Prop** out);                // slot 9 (0x24)
};

// ---- external functions ----
App* GetApp();                    // FUN_0067dd10
Sink* GetSink();                  // FUN_0067de30
Msg* GetMsgManager();             // FUN_0067dcc0
extern uint32_t g_SomeKey;        // 0x015D13E8
bool __cdecl QueryInterfaceRaw(Releasable* obj, uint32_t id, void** out);   // FUN_006a12e0
Dir* __cdecl GetDir(void* p);                                               // FUN_006b1f90
void __cdecl FormatPath(wchar_t* dst, const wchar_t* fmt, ...);             // FUN_0041e050
void __cdecl ReleaseBlock(void* p);                                         // EASTL_allocator_deallocate
void __cdecl ProcessLayout(void*, uint32_t, uint32_t, uint32_t, void*, void*, void*, void*); // FUN_0042ff00

struct PathNameRef { wchar_t* GetString(); };   // FUN_004ae000 (thiscall on GetName() result)
struct ValueRef { uint32_t* Get(); };           // FUN_0041e990 (thiscall)

struct RefPtr {
    Releasable* p;
    inline Releasable** Reset() {
        if (p) {
            Releasable* t = p;
            p = 0;
            t->Release();
        }
        return &p;
    }
};
inline bool Query(Releasable* obj, void** out) {
    uint32_t scratch[24];
    const uint32_t id = 0x70104290;      // interface id
    return QueryInterfaceRaw(obj, id, out);
}

struct Str {                                    // FUN_00406ac0 target
    char pad[4];
    void Assign(uint32_t v);
};
struct BigScratch {                             // 0xccc-byte stack object (FUN_00418120 / FUN_00418240)
    uint32_t data[0x333];
    uint32_t Init();
    void Done();
};
struct Range {                                  // 16-byte-element vector (begin/end)
    char* begin;
    char* end;
    void Erase(char* first, char* last);        // FUN_00548690
    inline int size() const { return (end - begin) >> 4; }
    inline void clear() { uint32_t scratch[6]; Erase(begin, end); }
};
struct Range2 {
    char* begin;
    char* end;
    void Clear(char* first, char* last);        // FUN_00426280
    inline void clear() { uint32_t scratch[11]; Clear(begin, end); }
};
struct Flags { char pad[4]; uint16_t flags; };

struct Obj {
    char p0[0x228];
    uint32_t f228;
    char p1[4];
    uint32_t f230;
    Flags opts;                                 // 0x234
    char p2[0x24c - 0x23c];
    Provider* provider;                         // 0x24c
    char p3[0x338 - 0x250];
    char lay338[0x14];                          // 0x338
    Range2 r34c;                                // 0x34c
    char p5[0x374 - 0x354];
    char f374[0x28];
    char f39c[0x14];
    char f3b0[0x18];
    char f3c8[0x30];
    uint32_t f3f8;
    uint32_t f3fc;
    wchar_t path[8];                            // 0x400
    Range vec;                                  // 0x410
    char p6[0x42c - 0x418];
    Str str42c;                                 // 0x42c

    bool OnClear(int arg);      // 0x40e9c0 (message 0x029D252F)
    bool OnReset(int arg);      // 0x40eab0 (message 0x02458018)
    bool OnA(int arg);          // 0x40e5b0
    bool Fn40eb70();
    bool Fn40f110();
    bool Fn40f3f0(int);
    bool Fn40f4a0(int);
    bool Fn40f820(int);
    bool Fn40fc00(int);
    bool Fn40fe00(int);
    bool Fn4103c0(int);
    bool Fn410dd0(int);
    bool Fn410f90(int);
};

// @ 0x0040e5b0
bool Obj::OnA(int)
{
    Flags* o = &opts;
    if (o->flags & 4) {
        RefPtr res;
        wchar_t* name = L"unknown";
        res.p = 0;
        void* dirOwner;
        if (GetApp()->GetKind() == 0xDBDBA1) {
            PathProvider* pp = GetApp()->GetPathProvider();
            name = ((PathNameRef*)pp->GetName())->GetString();
            GetSink()->Set(pp->Lookup(g_SomeKey, res.Reset()));
        }
        if (Query(res.p, &dirOwner) && GetDir(dirOwner)) {
            FormatPath(path, L"%ls/%ls.zpr", GetDir(dirOwner)->GetDirName(), name);
        } else {
            FormatPath(path, L"%ls.zpr", name);
        }
        if (res.p)
            res.p->Release();
    }
    BigScratch scratch;
    str42c.Assign(scratch.Init());
    scratch.Done();
    GetMsgManager()->Post(0x29D252F, 0, 0);
    return true;
}

// @ 0x0040e800
struct Dispatcher {   // this = Obj + 4 (second base)
    char pad[0x255];
    uint8_t enabled;
    bool Handle(uint32_t id, int arg);
};
bool Dispatcher::Handle(uint32_t id, int arg)
{
#define OBJ ((Obj*)((char*)this - 4))
    switch (id) {
    case 0x29D252F: return OBJ->OnClear(arg);
    case 0x2458018: return OBJ->OnReset(arg);
    case 0x67B65F1: return OBJ->Fn40eb70();
    case 0x67B65F2: return OBJ->Fn40f110();
    case 0x245801E: return OBJ->Fn40f3f0(arg);
    case 0x522264D: return OBJ->Fn40f4a0(arg);
    case 0x52DEB99: return OBJ->Fn40f820(arg);
    case 0x5302B02: return OBJ->Fn40fc00(arg);
    case 0x530781E: return OBJ->Fn40fe00(arg);
    case 0x52DEB9E: return OBJ->Fn4103c0(arg);
    case 0x29D3C4C: return OBJ->Fn410dd0(arg);
    case 0x29D57F4:
        if (enabled)
            return OBJ->Fn410f90(arg);
        else
            return false;
        break;
    }
    return false;
#undef OBJ
}

// @ 0x0040e9c0
bool Obj::OnClear(int)
{
    int i = 0;
    int count = vec.size();
    for (; i < count; i = i + 1) {
        void* p = *(void**)(vec.begin + i * 16 + 0xc);
        ReleaseBlock(p);
    }
    vec.clear();
    f3f8 = 0;
    ProcessLayout(lay338, f228, f230, f3f8, f39c, f3b0, f3c8, f374);
    return true;
}

// @ 0x0040eab0
bool Obj::OnReset(int)
{
    r34c.clear();
    f3f8 = 0;
    f3fc = 0x10;
    Provider* prov = provider;
    if (prov) {
        Prop* prop;
        if (prov->GetProp(0x67B804D, &prop) && prop->type == 9) {
            f3fc = *((ValueRef*)prop)->Get();
        }
    }
    GetMsgManager()->Post4(0x67B65F1, 0, 0, 0);
    return true;
}
