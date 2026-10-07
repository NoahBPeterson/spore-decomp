// SP::cWalkAroundInputStrategy::Init: registers the walk-around state machine states, input
// transitions and message subscriptions.
#include "types.h"
#include <string.h>

void __cdecl operator delete[](void*);

extern char g_BoolVecBuf[2];      // 0x01667bac: static storage of a fixed_vector<bool,1>
extern char g_BoolVecDefault[];   // 0x013ec47c: default (empty) vector<bool> prototype

struct BoolVec
{
    char* b;
    char* e;
    char* cap;
    void CopyCtor(const void* src);   // FUN_0057cc10
};

struct StateMachine;

struct StateBuilder
{
    uint32_t pad[4];
    int* field;
    StateBuilder(StateMachine* sm);   // FUN_00b198d0
    void AddState(int idx, const char* name);   // FUN_00b1c080
    void AddTransition(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j,
                       BoolVec* v, int k);      // FUN_00b1c8d0
    ~StateBuilder();                  // 0x0083c750 EA::ArgScript::cCommandBase::~cCommandBase
};

struct Entry { uint32_t id, z, w; };
struct EntryVec
{
    Entry* b;
    Entry* e;
    Entry* cap;
    void DoInsertValue(Entry* pos, const Entry* v);   // FUN_00b535d0
    void Push(uint32_t id)
    {
        Entry t = { id, 0, 100 };
        if (e < cap) { Entry* p = e; e = e + 1; if (p) *p = t; }
        else DoInsertValue(e, &t);
    }
};

struct Server;
struct Connector { void Init(Server* s, void* h, const char* name, int n); };   // Connector::Init 0x4db620
Server* GetServer();   // EA::Messaging::GetServer 0x883860
struct Dispatcher { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void Apply(EntryVec* v, int n); };
Dispatcher* GetDispatcher();   // FUN_00b3d240
extern char g_ConnName[];      // 0x0149c750

extern "C" void* __cdecl FUN_011e0744(void*, const void*, unsigned);

static inline void MakeA(BoolVec& v)
{
    char* p = g_BoolVecBuf;
    v.b = p; v.cap = p + 1;
    FUN_011e0744(p, g_BoolVecDefault, 0);
    *(v.e = g_BoolVecBuf) = 0;
}
static inline void MakeB(BoolVec& v)
{
    v.b = 0; v.e = 0; v.cap = 0;
    v.CopyCtor(g_BoolVecDefault);
}

struct cWalkAroundInputStrategy
{
    char pad0[4];
    StateMachine* sm() { return (StateMachine*)((char*)this + 4); }
    char pad1[0x44];
    char handler[0xBC];
    char connector[16];
    void Init();
};

// @ 0x0107c4b0
void cWalkAroundInputStrategy::Init()
{
    StateBuilder b(sm());
    b.AddState(0, "Walk around: neutral");
    b.AddState(1, "Walk around: mouse moving");
    b.AddState(2, "Walk around: ban");
    b.AddState(3, "Walk around: inspect");
    { BoolVec v; MakeA(v); b.AddTransition(0, 10, 0x3ff, 0x16, 0, 0, 0x19edcf3, 0, 1, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(1, 0xb, 0x3ff, 0x16, -1, 0, 0xd02dcc68, 0, 0, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(0, 0xb, 0x3ff, 0x12345678, -1, 0, 0xd02dcc68, 0, 0, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x16, 0xd0036e08, 2, 0x1a53705, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x16, 0x4f176642, 0, 0x1a53705, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x16, 0x3ed590d, 0, 0x3f3eb2c, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x16, 0xd0036e08, 1, 0x17dab3f, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x16, 0x2dd8c33, 0, 0x2df01f2, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x16, -1, 0, 0x1c38e3b, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 0xb, 0x3ff, 0x16, -1, 0, 0x1c38e3b, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x18, -1, 0, 0x35f7b83, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 0xb, 0x3ff, 0x18, -1, 0, 0x35f7b83, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 1, 0x3ff, 0x3ea, -1, 0, 0x6493c83, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 3, 0x3ff, 0x3ea, -1, 0, 0x6493c83, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 1, 0x3ff, 0x3e9, -1, 0, 0x6493c83, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 3, 0x3ff, 0x3e9, -1, 0, 0x6493c83, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x14, -1, 0, 0x50567351, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 1, -1, 0, 0x27c7119, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 2, -1, 0, 0x27c7119, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 3, -1, 0, 0x27c67ea, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 4, -1, 0, 0x27c67ea, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x10, -1, 0, 0x705673e1, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 0xb, 0x3ff, 0x10, -1, 0, 0x705673e1, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x11, -1, 0, 0x705673e9, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 0xb, 0x3ff, 0x11, -1, 0, 0x705673e9, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x13, -1, 0, 0x25db76f, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 0xb, 0x3ff, 0x13, -1, 0, 0x25db76f, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 10, 0x3ff, 0x12, -1, 0, 0x25db76a, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeA(v); b.AddTransition(-1, 0xb, 0x3ff, 0x12, -1, 0, 0x25db76a, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(-1, 10, 0x3ff, 0x16, -1, 0, 0x2c4bfde, 1, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(-1, 0xb, 0x3ff, 0x16, -1, 0, 0x2c4bfde, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(-1, 10, 0x3ff, 0x15, -1, 0, 0x1c41da1, 0, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(2, 1, 0x3ff, 1000, -1, 0, 0xb332763d, -1, 2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(2, 4, 0x3ff, 0x1b, -1, 0, 0xf3327645, 0, 0, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(2, 6, 0x3ff, -1, -1, 0, 0x639939b, -1, 2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(2, 1, 0x3ff, 0x3ea, -1, 0, 0x6493c83, 1, 2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(2, 3, 0x3ff, 0x3ea, -1, 0, 0x6493c83, 0, 2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(3, 1, 0x3ff, 1000, -1, 0, 0x62663dc, -1, 3, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(3, 4, 0x3ff, 0x1b, -1, 0, 0x62663dd, 0, 0, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(3, 1, 0x3ff, 0x3ea, -1, 0, 0x6493c83, 1, 3, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(3, 3, 0x3ff, 0x3ea, -1, 0, 0x6493c83, 0, 3, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }
    { BoolVec v; MakeB(v); b.AddTransition(-1, 10, 0x3ff, -1717986926, -1, 0, 0x274847c, 0x29a, -2, 0, &v, 0); if (v.cap - v.b > 1 && v.b) operator delete[](v.b); }

    Server* srv = GetServer();
    Connector* c = (Connector*)((char*)this + 0x108);
    c->Init(srv, this ? (char*)this + 0x48 : 0, g_ConnName, 0x15);
    EntryVec vec = { 0, 0, 0 };
    vec.Push(0x23a6ccd);
    vec.Push(0x23a7919);
    vec.Push(0x2dd8c33);
    vec.Push(0x116d858);
    vec.Push(0x23a6cc8);
    GetDispatcher()->Apply(&vec, 1);
    if (vec.b && ((int*)vec.b)[-1] != 0) operator delete[](vec.b);
    if (b.field && b.field[-1] != 0) operator delete[](b.field);
}
