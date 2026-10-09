// Slice s00de7200 -- 0x00de76b0: constructor body of a Simulator UI/editor controller. It builds a
// std::map<int, Handler*> of per-mode handlers (key -> handler, each handler's vtable slot 11 is an
// init hook), clears a 3x3 table of collectable-item refs, creates six cCollectableItems inventories,
// reads a byte option and registers a message-id table with the MessageServer.
// Built /O2 /MD /Gy /EHsc /TP.
typedef unsigned int  uint;
typedef unsigned char uchar;
typedef unsigned long long u64;

void* operator new(unsigned int, const char*, int, int, int, int);  // 0x00F473A0 (EA allocator)

struct Handler {
    virtual int  AddRef();
    virtual int  Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void Init();   // 0x2c
};

// 8-byte handlers: base ctor 0x00e00630, then derived vtable.
struct HandlerBase : Handler { int f; HandlerBase(); };
struct HandlerA : HandlerBase { virtual void Init(); };   // vtable 0x147dec8
struct HandlerB : HandlerBase { virtual void Init(); };   // vtable 0x147df38
struct HandlerC : HandlerBase { virtual void Init(); };   // vtable 0x147dfc0

struct H0  : Handler { char pad[0x28]; H0(); };           // 0x2c, ctor 0x00dea500
struct H2  : Handler { char pad[0xa4]; H2(); };           // 0xa8, ctor 0x00e008e0 (cSPUIGlobalUIRootWinProc)
struct H3  : Handler { char pad[0xe4]; H3(); };           // 0xe8, ctor 0x00de2d00
struct H11 : Handler { char pad[0x4c]; H11(); };          // 0x50, ctor 0x00de3370
struct H12 : Handler { char pad[0xc]; H12(); };           // 0x10, ctor 0x00deb670
struct H4  : Handler { char pad[0x14]; H4(); };           // 0x18, ctor 0x00dee320
struct H13 : Handler { char pad[0x174]; H13(); };         // 0x178, ctor 0x00dfb9c0

// Simulator::cCollectableItems (0x6dac bytes, ctor 0x00597e00); also SP::cSpaceInventory
struct Items {
    virtual int  AddRef();
    virtual int  Release();
    char pad[0x6da4 + 4];
    Items();
    void Configure(uint a, uint b, uint c);      // 0x00599440 ret 0xc
    void SetPair(u64 v);                         // 0x00596d70 ret 8
};
u64  FUN_00593980(uint a, uint b);               // cdecl, returns edx:eax
void FUN_00de4f50(Items* it, int n);             // cdecl
bool FUN_00685520(int n);                        // cdecl

struct HMap { Handler** Slot(int* key); };       // 0x00de7630 ret 4 (std::map<int,Handler*>::operator[])

struct Prop {
    void* data;       // +0
    char  pad[0xc];
    uchar flags;      // +0x10
    uchar pad2;
    short type;       // +0x12
};
struct PropList { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                  virtual void v8();
                  virtual bool Get(uint id, Prop** out); };   // 0x24
extern PropList* sAppProperties;                  // 0x015fd918

struct MsgServer { virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
                   virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
                   virtual void m8();
                   virtual void AddListener(void* target, uint msg); };   // 0x24
struct LayerMgr  { virtual void l0(); virtual void l1(); virtual void l2(); virtual void l3();
                   virtual void l4(); virtual void l5(); virtual void l6(); virtual void l7();
                   virtual void l8(); virtual void l9(); virtual void l10();
                   virtual void Set(uint id, int v); };                   // 0x2c
MsgServer* SP_MessageServer();                    // 0x0067dcc0
LayerMgr*  SP_LayerManager();                     // 0x0067cb20
extern char* kGUI_PanelIDs;                        // 0x016a1344
extern uint DAT_015a3b90[0x25];

struct Ctl {
    char   pad0[0x10];
    MsgServer* mServer;      // +0x10
    void*      mTarget;      // +0x14
    uint*      mTable;       // +0x18
    uint       mCount;       // +0x1c
    uint       mZero;        // +0x20
    char   pad1[0xd0];
    uchar  mOpt;             // +0xf4
    char   pad2[0x2f];
    HMap   mHandlers;        // +0x124
    char   pad3[0x8c];
    Items* mGrid[9];         // +0x1b4 .. +0x1d4
    char   pad4[0x14];
    int    m1ec;             // +0x1ec

    void Base();             // 0x00de63e0
    void Ctor();             // 0x00de76b0
};

static inline void Assign(Items*& slot, Items* p)
{
    Items* old = slot;
    if (p != old) {
        if (p) p->AddRef();
        slot = p;
        if (old) old->Release();
    }
}

// @ 0x00de76b0
void Ctl::Ctor()
{
    union { int key; Prop* p; } u;
    Base();
    m1ec = 0;

    H0* h0 = new ("Simulator", 0, 0, 0, 0) H0();
    h0->Init();
    u.key = 0;  *mHandlers.Slot(&u.key) = h0;
    u.key = 1;  *mHandlers.Slot(&u.key) = h0;
    u.key = 8;  *mHandlers.Slot(&u.key) = h0;
    u.key = 9;  *mHandlers.Slot(&u.key) = h0;

    H2* h2 = new ("Simulator", 0, 0, 0, 0) H2();
    h2->Init();
    u.key = 2;  *mHandlers.Slot(&u.key) = h2;

    H3* h3 = new ("Simulator", 0, 0, 0, 0) H3();
    h3->Init();
    u.key = 3;  *mHandlers.Slot(&u.key) = h3;
    u.key = 5;  *mHandlers.Slot(&u.key) = h3;

    HandlerA* ha = new ("Simulator", 0, 0, 0, 0) HandlerA();
    ha->Init();
    u.key = 6;  *mHandlers.Slot(&u.key) = ha;

    HandlerB* hb = new ("Simulator", 0, 0, 0, 0) HandlerB();
    hb->Init();
    u.key = 7;  *mHandlers.Slot(&u.key) = hb;

    HandlerC* hc = new ("Simulator", 0, 0, 0, 0) HandlerC();
    hc->Init();
    u.key = 10; *mHandlers.Slot(&u.key) = hc;

    H11* h11 = new ("Simulator", 0, 0, 0, 0) H11();
    h11->Init();
    u.key = 11; *mHandlers.Slot(&u.key) = h11;

    H12* h12 = new ("Simulator", 0, 0, 0, 0) H12();
    h12->Init();
    u.key = 12; *mHandlers.Slot(&u.key) = h12;

    H4* h4 = new ("Simulator", 0, 0, 0, 0) H4();
    h4->Init();
    u.key = 4;  *mHandlers.Slot(&u.key) = h4;

    if (FUN_00685520(2)) {
        H13* h13 = new ("Simulator", 0, 0, 0, 0) H13();
        h13->Init();
        u.key = 13; *mHandlers.Slot(&u.key) = h13;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Items* it = mGrid[i * 3 + j];
            if (it) {
                mGrid[i * 3 + j] = 0;
                it->Release();
            }
        }
    }

    Assign(mGrid[6], new ("Simulator", 0, 0, 0, 0) Items());
    mGrid[6]->Configure(0xad56080c, 0x4a5c4493, 0x40626000);
    FUN_00de4f50(mGrid[6], 3);

    Assign(mGrid[7], new ("Simulator", 0, 0, 0, 0) Items());
    mGrid[7]->Configure(0xad56080c, 0x4a5c4493, 0x40626000);
    FUN_00de4f50(mGrid[7], 6);

    Assign(mGrid[8], new ("Simulator", 0, 0, 0, 0) Items());
    mGrid[8]->Configure(0xad56080c, 0x4a5c4493, 0x40626000);
    FUN_00de4f50(mGrid[8], 5);

    Assign(mGrid[3], new ("Simulator", 0, 0, 0, 0) Items());
    mGrid[3]->Configure(0, 0, 0x40616000);

    Assign(mGrid[3], new ("Simulator", 0, 0, 0, 0) Items());
    mGrid[3]->Configure(0, 0, 0x40616000);
    { Items* t = mGrid[3]; t->SetPair(FUN_00593980(0x40626000, 0x32ac9620)); }
    { Items* t = mGrid[3]; t->SetPair(FUN_00593980(0x40626000, 0x3a3c49a5)); }

    Assign(mGrid[4], new ("Simulator", 0, 0, 0, 0) Items());
    mGrid[4]->Configure(0, 0, 0x40616000);
    { Items* t = mGrid[4]; t->SetPair(FUN_00593980(0x40626000, 0x32ac9620)); }
    { Items* t = mGrid[4]; t->SetPair(FUN_00593980(0x40626000, 0xfe534766)); }

    Assign(mGrid[5], new ("Simulator", 0, 0, 0, 0) Items());
    mGrid[5]->Configure(0, 0, 0x40616000);
    { Items* t = mGrid[5]; t->SetPair(FUN_00593980(0x40626000, 0xfe534766)); }
    { Items* t = mGrid[5]; t->SetPair(FUN_00593980(0x40626000, 0x3a3c49a5)); }

    if (sAppProperties) {
        if (sAppProperties->Get(0x64a44a8, &u.p) && u.p->type == 1) {
            Prop* p = u.p;
            uchar* d = (uchar*)p;
            if (p->flags & 0x30) d = *(uchar**)p;
            mOpt = *d;
        }
    }

    void* panel = kGUI_PanelIDs ? kGUI_PanelIDs + 8 : 0;
    MsgServer* ms = SP_MessageServer();
    mServer = ms;
    mTarget = panel;
    mTable  = DAT_015a3b90;
    mCount  = 0x25;
    mZero   = 0;
    if (ms && panel) {
        uint off = 0;
        do {
            ms->AddListener(panel, *(uint*)((char*)DAT_015a3b90 + off));
            off += 4;
        } while (off < 0x94);
    }

    SP_LayerManager()->Set(0x5807346, 0);
    SP_LayerManager()->Set(0x5807345, 0);
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}

namespace __equiv_ann1 {   // address annotations for the equivalence checker; never referenced
struct H0 {
    H0();   // 0x00dea500 (equiv t3)
};
struct H11 {
    H11();   // 0x00de3370 (equiv t3)
};
struct H12 {
    H12();   // 0x00deb670 (equiv t3)
};
struct H13 {
    H13();   // 0x00dfb9c0 (equiv t3)
};
struct H2 {
    H2();   // 0x00e008e0 (equiv t3)
};
struct H3 {
    H3();   // 0x00de2d00 (equiv t3)
};
struct H4 {
    H4();   // 0x00dee320 (equiv t3)
};
struct HMap {
    void Slot();   // 0x00de7630 (equiv t3)
};
struct HandlerBase {
    HandlerBase();   // 0x00e00630 (equiv t3)
};
}
