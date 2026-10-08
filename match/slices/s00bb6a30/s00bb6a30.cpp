// Slice s00bb6a30 -- 0x00bb6a30: a StarManager-style system Init(): resolves two lazy static handles,
// registers a record factory, loads two PropertyLists, hooks 12 message callbacks, registers a
// cheat/command object, (re)registers the message-server listener set, reads tuning properties
// into members and into file-scope tuning globals.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc)
#include "types.h"
#include <intrin.h>

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(_p, __COUNTER__)();
#define VP4 VP VP VP VP

// ---- property system -----------------------------------------------------------------------
struct Property {
    uint32_t pad0[4];
    uint16_t pad10;
    uint16_t mnType;            // +0x12: 1 bool, 9 int32, 0xd float
    char*     GetBool();        // 0x0041e920
    uint32_t* GetInt();         // 0x0041e990
    float*    GetFloat();       // 0x0041ea70
};

struct PropertyList {
    virtual void AddRef();
    virtual void Release();
    VP VP VP VP VP VP VP
    virtual bool GetProperty(uint32_t id, Property*& out);   // +0x24
};

struct cPropertyManager {
    VP4 VP4 VP VP VP
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList*& out);   // +0x2c
};
cPropertyManager* PropertyManager();                          // 0x0067de30

struct Vec2 { float x, y; };
void GetPropertyAsVector2(PropertyList* list, uint32_t id, Vec2* out);   // 0x006a10c0 (cdecl)

static inline void ResetList(PropertyList*& sp)
{
    PropertyList* const pTemp = sp;
    if (pTemp) {
        sp = 0;
        pTemp->Release();
    }
}

static inline void ReadFloat(PropertyList* list, uint32_t id, float& dst)
{
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 0xd)
        dst = *prop->GetFloat();
}
static inline void ReadInt(PropertyList* list, uint32_t id, uint32_t& dst)
{
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 9)
        dst = *prop->GetInt();
}
static inline void ReadBool(PropertyList* list, uint32_t id, char& dst)
{
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 1)
        dst = *prop->GetBool();
}

// ---- file-scope tuning values ---------------------------------------------------------------
extern uint32_t g_TuneA;      // 0x0156c508
extern float    g_TuneB;      // 0x0156c50c
extern float    g_TuneC;      // 0x0156c510
extern float    g_TuneD;      // 0x0156c514
extern uint32_t g_TuneE;      // 0x0156c518
extern float    g_TuneF;      // 0x0156c51c
extern float    g_TuneG;      // 0x0156c520
extern char     g_TuneFlag;   // 0x01689648
extern uint32_t g_MsgIds[5];  // 0x0156cb54

// ---- lazy static handles (function-local statics) -----------------------------------------
struct LazyHandle {
    virtual ~LazyHandle() {}
    LazyHandle* mpNext;
    int         mArg;
    char        mResolved;
    LazyHandle(int a);          // 0x00692f60 (links into a global list)
    bool IsResolved();          // 0x00ab30c0
    bool Resolve();             // 0x00692850
};
struct LazyHandleA : LazyHandle {
    LazyHandleA() : LazyHandle(0) {}
    virtual ~LazyHandleA() {}   // vtable 0x01465fd0
};
struct LazyHandleB : LazyHandle {
    LazyHandleB() : LazyHandle(0) {}
    virtual ~LazyHandleB() {}   // vtable 0x01465fe0
};

// ---- allocation / registration ------------------------------------------------------------
void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
struct ZoneObject {
    static void* operator new(unsigned n, const char* name, int a, int b, int c, int d);   // 0x00926020
    static void operator delete(void*, const char*, int, int, int, int) {}
};
struct ZoneRC : ZoneObject {
    virtual int AddRef();
    virtual int Release();
    long rc;
    ZoneRC() { _InterlockedExchange(&rc, 0); }
};
struct cPlanetRecordFactory : ZoneRC {
    virtual int Release();      // vtable 0x01465ff0
};
struct ResMan {
    VP4 VP4 VP4 VP VP VP VP VP
    virtual void AddFactory(int kind, cPlanetRecordFactory* f, int c);   // +0x44
};
ResMan* GetResMan();                                           // 0x0067dcd0

struct IMessageListener { virtual void pv0(); };
struct MessageServer {
    VP4 VP4 VP
    virtual void AddListener(IMessageListener* h, uint32_t id);                                  // +0x24
    virtual void AddCallback(void (*fn)(), int n, uint32_t id, int a, int b);                    // +0x28
};
MessageServer* GetMessageServer();                             // 0x0067dcc0 (SP::MessageServer)
void RemoveHandler(MessageServer* srv, IMessageListener* h, uint32_t* ids, int count, int arg);   // 0x00571db0 (cdecl)
void MsgCallback();                                            // 0x00bb5d80

struct cCommandBase {
    cCommandBase();                                            // 0x0083c800
    virtual ~cCommandBase();
};
struct cStarManagerCommand : cCommandBase {                    // vtable 0x01465f64
    virtual ~cStarManagerCommand();
};
struct CheatMgr;
CheatMgr* GetCheatManager();                                   // 0x0067de20 (SP::CheatManager)
struct Registry {
    VP4 VP VP VP
    virtual void Register(int hash, const wchar_t* name, int flag);   // +0x1c
};
Registry* GetRegistry();                                       // 0x006895b0

// ---- the system object ---------------------------------------------------------------------
struct IRC { virtual void v0(); virtual void v1(); virtual void AddRef(); virtual void Release(); };
struct cSimObj {                                               // 0x100 bytes, ctor 0x00d05010
    virtual void v0();
    virtual void Init();                                       // +4 (slot 1)
    int pad4;
    IRC rc;                                                    // +8
    cSimObj();
};

struct Base0 {
    virtual ~Base0();
    uint32_t pad[6];
};
struct StarSystem : Base0, IMessageListener {
    char                pad1[0xb4 - 0x20];
    MessageServer*      mpServer;       // +0xb4
    IMessageListener*   mpHandler;      // +0xb8
    uint32_t*           mpIds;          // +0xbc
    int                 mnIds;          // +0xc0
    int                 mArg;           // +0xc4
    char                pad2[0x1a0 - 0xc8];
    PropertyList*       mpListA;        // +0x1a0
    PropertyList*       mpListB;        // +0x1a4
    uint32_t            mA8, mAC, mB0, mB4, mB8;   // +0x1a8..
    float               mBC, mC0;       // +0x1bc, +0x1c0
    uint32_t            mC4;            // +0x1c4
    float               mC8;            // +0x1c8
    Vec2                mCC;            // +0x1cc
    char                pad3[0x204 - 0x1d4];
    cSimObj*            mpSim;          // +0x204
    void Init();
};

// @ 0x00bb6a30
void StarSystem::Init()
{
    static LazyHandleA sA;
    if (!sA.IsResolved())
        sA.Resolve();
    static LazyHandleB sB;
    if (!sB.IsResolved())
        sB.Resolve();

    cPlanetRecordFactory* factory = new ("App/PlanetRecordFactory", 0, 0, 0, 0) cPlanetRecordFactory();
    GetResMan()->AddFactory(1, factory, 0);

    cPropertyManager* pmA = PropertyManager();
    ResetList(mpListA);
    pmA->GetPropertyList(0xcdf8d12f, 0x2ae0c7e, mpListA);
    cPropertyManager* pmB = PropertyManager();
    ResetList(mpListB);
    pmB->GetPropertyList(0x1106d054, 0x2ae0c7e, mpListB);

    GetMessageServer()->AddCallback(MsgCallback, 4, 0x35b2b15, 0, 0);
    GetMessageServer()->AddCallback(MsgCallback, 5, 0x36998ae, 0, 0);
    GetMessageServer()->AddCallback(MsgCallback, 6, 0x3757942, 0, 0);
    GetMessageServer()->AddCallback(MsgCallback, 2, 0x36ad255, 0, 0);
    GetMessageServer()->AddCallback(MsgCallback, 3, 0x36ad784, 0, 0);
    GetMessageServer()->AddCallback(MsgCallback, 1, 0x3d1deba, 0, 0);
    GetMessageServer()->AddCallback(MsgCallback, 7, 0x3dff99f, 0, 0);
    GetMessageServer()->AddCallback(MsgCallback, 8, 0x3dff9a9, 0, 0);
    GetMessageServer()->AddCallback(MsgCallback, 9, 0x3dff9b1, 0, 0);
    GetMessageServer()->AddCallback(MsgCallback, 10, 0x3dff9ba, 0, 0);
    GetMessageServer()->AddCallback(MsgCallback, 11, 0x3dff9c1, 0, 0);
    GetMessageServer()->AddCallback(MsgCallback, 12, 0x3dff9c6, 0, 0);

    cStarManagerCommand* cmd = new ("App/cStarManagerCommand", 0, 0, 0, 0) cStarManagerCommand();
    (void)cmd;
    GetCheatManager();
    GetRegistry()->Register(0x4404670, L"StarManager", 0);

    if (mpServer) {
        MessageServer* srv = mpServer;
        IMessageListener* h = mpHandler;
        uint32_t* ids = mpIds;
        int n = mnIds;
        int arg = mArg;
        mpServer = 0;
        RemoveHandler(srv, h, ids, n, arg);
    }
    IMessageListener* self = this;
    MessageServer* server = GetMessageServer();
    mpServer = server;
    mpHandler = self;
    mpIds = g_MsgIds;
    mnIds = 5;
    mArg = 0;
    if (server && self) {
        for (int i = 0; i < 5; i++)
            server->AddListener(self, g_MsgIds[i]);
    }

    ReadFloat(mpListA, 0x2f827d6, mC0);
    ReadInt(mpListA, 0x4ab1bb7, mA8);
    ReadInt(mpListA, 0x4ab1bc0, mAC);
    ReadInt(mpListA, 0x4ab1bc8, mB0);
    ReadInt(mpListA, 0x4ab1bce, mB4);
    ReadInt(mpListA, 0x4ab1bcf, mB8);
    ReadFloat(mpListA, 0x195e034, mBC);
    ReadInt(mpListB, 0x589c626, mC4);
    ReadFloat(mpListB, 0x5f76a83, mC8);
    GetPropertyAsVector2(mpListB, 0x5f76a90, &mCC);

    cSimObj* sim = new ("Simulator", 0, 0, 0, 0) cSimObj();
    cSimObj* old = mpSim;
    if (sim != old) {
        if (sim)
            sim->rc.AddRef();
        mpSim = sim;
        if (old)
            old->rc.Release();
    }
    mpSim->Init();

    PropertyList* list = 0;
    cPropertyManager* pmC = PropertyManager();
    ResetList(list);
    if (pmC->GetPropertyList(0x288cfa78, 0, list)) {
        ReadInt(list, 0x7544c8df, g_TuneA);
        ReadInt(list, 0x4aaf12f1, g_TuneE);
        ReadFloat(list, 0xd2125fba, g_TuneB);
        ReadFloat(list, 0x745db9d0, g_TuneD);
        ReadFloat(list, 0xdfd59afc, g_TuneC);
        ReadFloat(list, 0x15939a97, g_TuneF);
        ReadFloat(list, 0xc9f15b65, g_TuneG);
        ReadBool(list, 0x37863077, g_TuneFlag);
    }
    if (list)
        list->Release();
}
