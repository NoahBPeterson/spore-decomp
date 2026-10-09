// Slice s00a44bb0 - SP::Audio::cSystem: message dispatch, command handlers,
// symbol-list / hashtable helpers.  (EAPD audio subsystem)
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int   uint32;
typedef unsigned short uint16;
typedef unsigned char  byte;

// ---------------------------------------------------------------------------
// A minimal view of the EASTL hashtable used at cSystem +0x320 / +0x15bf38.
// find() is 0x00b41b30 (thiscall, ret 8): it writes an 8-byte iterator
// { mpNode, mpBucket } through the first (pointer) argument.
// ---------------------------------------------------------------------------
struct Iterator {
    void* mpNode;
    void* mpBucket;
    Iterator() {}
    Iterator(const Iterator& o) { mpNode = o.mpNode; mpBucket = o.mpBucket; }
};

struct HashTable {
    char     pad0[4];
    void**   mpBucketArray;    // +0x04
    uint32   mnBucketCount;    // +0x08
    void  hashFind(Iterator* out, const void* pKey);      // 0xb41b30
    Iterator erase(Iterator it);                      // 0xa443c0
    void     eraseVoid(Iterator it);                  // 0xa443c0
};

struct RefCounted {
    virtual void AddRef();        // +0x00
    virtual void Release();       // +0x04
    virtual void v08();           // +0x08
};

struct IHandler6 {                // any object with a vtable slot at +0x14
    virtual void h00();
    virtual void h04();
    virtual void h08();
    virtual void h0c();
    virtual void h10();
    virtual void h14();           // +0x14
};

// object placed at cSystem - 4 (the primary base subobject of the complete
// audio object); only its virtual interface and one field are used.
struct BaseObj {
    virtual void v00();
    virtual void v01();                    // +0x04
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14(int id);              // +0x38
    virtual void v15();
    virtual void v16(int id, int val);     // +0x40
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();                    // +0x58
    char   pad0[0x15bc38 - 0x5c];
    int    mField15bc38;                   // +0x15bc38
};

// small embedded object at cSystem +0x15bc14 (vtable + vtable slot +4)
struct Obj15bc14 {
    virtual void o00();
    virtual void o04(int);                 // +0x04
};

struct Server {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14(int id, void* msg, int flags);   // +0x14
};

// ---------------------------------------------------------------------------
// The cSystem object.  Fields are laid out relative to the pointer received in
// ECX (the IHandlerRC subobject; the primary base sits at this-4).
// ---------------------------------------------------------------------------
struct cSystem {
    char        pad00[0x93];
    byte        mb93;                    // +0x93
    byte        mb94;                    // +0x94
    char        pad01[0x320 - 0x95];
    HashTable   mTable320;               // +0x320
    char        pad02[0x118a78 - (0x320 + sizeof(HashTable))];
    HashTable   mSymbolTable;            // +0x118a78
    char        pad03[0x15bc14 - (0x118a78 + sizeof(HashTable))];
    Obj15bc14   mObj15bc14;              // +0x15bc14
    char        pad04[0x15bc34 - (0x15bc14 + sizeof(Obj15bc14))];
    int         mField15bc34;            // +0x15bc34
    char        pad05[0x15bc3d - (0x15bc34 + 4)];
    byte        mbFlag15bc3d;            // +0x15bc3d
    char        pad06[0x15bc70 - (0x15bc3d + 1)];
    RefCounted* mp15bc70;                // +0x15bc70
    char        pad07[0x15bc78 - (0x15bc70 + 4)];
    RefCounted* mpEventModifier;         // +0x15bc78
    RefCounted* mp15bc7c;                // +0x15bc7c
    RefCounted* mp15bc80;                // +0x15bc80
    char        pad08[0x15bcd8 - (0x15bc80 + 4)];
    float       mf15bcd8;                // +0x15bcd8
    float       mf15bcdc;                // +0x15bcdc
    RefCounted* mpSocket15bce0;          // +0x15bce0
    char        pad09[0x15bf38 - (0x15bce0 + 4)];
    HashTable   mTable15bf38;            // +0x15bf38

    BaseObj*   base() { return (BaseObj*)((char*)this - 4); }

    void HandleMessage(uint32 msgId, int* pData);   // 0xa44bb0
    void FUN_00a44e80(uint32 key);                  // 0xa44e80
    void FUN_00a44f70(int key);                     // 0xa44f70
    void FUN_00a45610(int a, int b);                // 0xa45610
    void DoCommandMainThread(void* cmd);            // 0xa45780
    void FUN_00a458b0(char* s, char* t);            // 0xa458b0
    bool FUN_00a45130();                            // 0xa45130

    void SetCurrentContext(int ctx);                // 0xa426f0
    void AddSymbolList(uint32 id);                  // 0xa43580
    void System_HandleMessage(uint32 msgId, int* pData);  // 0xa21710
};

// ---- extern helpers --------------------------------------------------------
extern "C" Server* EA_Messaging_GetServer();                 // 0x883860
extern "C" void*   SP_MessageServer();                       // 0x67dcc0
extern "C" void*   EA_ResourceMan_GetManager();              // 0x67dcd0
extern "C" RefCounted* Eapd_Debug_ObjectError();             // 0x8de1a0
extern "C" IHandler6*  Eapd_ISystem_GetSingletonPtr();       // 0xa67c60
extern "C" void*   operator_new6(int size, const char* name, int a, int b, int c, int d); // 0xf473a0
extern "C" void    operator_delete(void* p);                 // 0xf47380
extern "C" void*   ZoneObject_operator_new6(int size, const char* name, int a, int b, int c, int d); // 0x926020

extern "C" void SP_Pixie_Register();       // 0xa3edb0
extern "C" void SP_Mixer_Register();       // 0xa3d380
extern "C" void SP_Trixie_Register();      // 0xa40e80
extern "C" void SP_SendGame_Register();    // 0xa3f000
extern "C" void* SP_ConstructcEmitterModelSound();        // 0xa465b0
extern "C" void* SP_ConstructcEmitterSndPlayer();         // 0xa398d0
extern "C" int   FUN_00a68e90(void* p);                   // 0xa68e90
extern "C" void  FUN_00a466d0(void* p);                   // 0xa466d0
extern "C" void  FUN_0092b1d0(void* self);                // 0x92b1d0
extern "C" void  FUN_005d7450(void* self);                // 0x5d7450
extern "C" void  FUN_00a31f20(void* cmd);                 // 0xa31f20
extern "C" int   FUN_00a34dc0(void* msg, void* node);     // 0xa34dc0
extern "C" int   FUN_00fc7e50(void* node);                // 0xfc7e50 (Node::Type)
extern "C" int   FUN_00a0fab0(void* cmd, uint32 id, uint32* out); // 0xa0fab0 GetUint32
extern "C" int   FUN_00a43580_helper();                   // 0xa43580
extern "C" int   FUN_00a41fc0();                          // 0xa41fc0
extern "C" int   FUN_00a31170(void* self);                // 0xa31170 cSystem::InitAT
extern "C" long  atol(const char*);                       // msvcr90
extern "C" char* strchr(const char*, int);                // msvcr90
extern "C" uint32 EA_Sockets_IPAddress_LookupName(void* self, int flags); // 0x94c1b0

extern void cSystem_SetCurrentContext(cSystem* self, int ctx);
void cSystem_SetCurrentContext(cSystem* self, int ctx);  // 0xa426f0

extern void* EA_ResourceMan_Manager_v38(void* mgr, void* out, void* key, int zero);
extern void cEventModifier_Init(void* m);
extern void EA_ResourceMan_Resource_Init(void* r);

// ---------------------------------------------------------------------------
// temporary message used in the 0xf62ade case
// ---------------------------------------------------------------------------
struct LocaleChangeMessage {
    void*  mpVtbl;            // +0x00
    char   pad0[0x08 - 4];
    int    mf08;              // +0x08
    char   pad1[0x10 - 0x0c];
    int    mf10;              // +0x10
    char   pad2[0x18 - 0x14];
    int    mf18;              // +0x18
    char   pad3[0x80 - 0x1c];
    uint32 mId;               // +0x80
    uint32 mFlags;            // +0x84
    uint32 mFlags2;           // +0x88
};

extern "C" void FUN_00a227a0(LocaleChangeMessage* self, uint32 id);  // 0xa227a0

// ===========================================================================
// @ 0x00a44bb0
// ===========================================================================
void cSystem::HandleMessage(uint32 msgId, int* pData)
{
    switch (msgId) {
    case 0x1ee1006:
    case 0x1ee100e:
        if (mbFlag15bc3d) mb94 = 0;
        break;
    case 0x1ee1007:
    case 0x1ee1008:
    case 0x1ee100f:
        if (mbFlag15bc3d) mb94 = 1;
        break;

    case 0xf62ade: {
        LocaleChangeMessage msg;
        FUN_00a227a0(&msg, 0x2b0c259);
        msg.mf08 = pData[2];
        msg.mf10 = pData[4];
        msg.mf18 = pData[6];
        msg.mFlags2 |= 7;
        Server* srv = EA_Messaging_GetServer();
        srv->s14(0x2b0c259, &msg, 0);
        if (mp15bc70) ((IHandler6*)mp15bc70)->h14();
        BaseObj* b = base();
        b->v14(0x436201e);
        b->v16(0x4362059, msg.mf08);
        b->v16(0x4362049, msg.mf10);
        b->v16(0x3475385, msg.mf18);
        b->v22();
        msg.mpVtbl = (void*)0x13eb918;          // &BaseA2 vtable (unwind restore)
        break;
    }

    case 0x279a5da: {
        BaseObj* b = base();
        b->mField15bc38 = 1;
        b->v14(0x43390fd);
        b->v16(0x433911b, 1);
        b->v22();
        break;
    }

    case 0x279a67c: cSystem_SetCurrentContext(this, 2); break;
    case 0x279a680: cSystem_SetCurrentContext(this, 3); break;

    case 0x44edd9a: if (mbFlag15bc3d) mb93 = 1; break;
    case 0x44edd9c: if (mbFlag15bc3d) mb93 = 0; break;

    case 0x6e0aae1: {
        BaseObj* b = base();
        b->v01();
        char tmp[0x34];
        FUN_0092b1d0(tmp);
        mObj15bc14.o04(0);
        FUN_005d7450(tmp);
        Server* srv = (Server*)SP_MessageServer();
        srv->s14(0x578f803, 0, 0);
        break;
    }
    default:
        break;
    }

    System_HandleMessage(msgId, pData);
}

// ===========================================================================
// @ 0x00a44e80
// ===========================================================================
void cSystem::FUN_00a44e80(uint32 key)
{
    HashTable& t = mTable320;
    Iterator it;
    t.hashFind(&it, &key);
    if (it.mpNode == t.mpBucketArray[t.mnBucketCount]) {
        uint32 built = 0;
        FUN_00a43580_helper();
        (void)built;
    }
}

// ===========================================================================
// @ 0x00a44f70
// ===========================================================================
void cSystem::FUN_00a44f70(int key)
{
    HashTable& t = mTable15bf38;
    Iterator it;
    t.hashFind(&it, &key);
    if (it.mpNode != t.mpBucketArray[t.mnBucketCount]) {
        it = t.erase(it);
    }
}

// ===========================================================================
struct FixedHashtable {
    char  pad0[8];
    int   m08;                 // +0x08
    int   m0c;                 // +0x0c
    int   m10;                 // +0x10
    int   m14;                 // +0x14
    int   m18;                 // +0x18
    char  pad1[0x34 - 0x1c];
    int   m34;                 // +0x34
    char  pad2[0x8c - 0x38];
    void* mpPool;              // +0x8c (fixed pool, 0x140 bytes)
    char  pad3[0x140];
    char* mpEnd;               // +0x1cc
    void* ctor(int a, int b);  // 0xa44fc0
    void  erase(int n);        // 0xa42e90
};

struct FixedPoolBase {
    void* mpHead;              // +0x00
    void* mpNext;              // +0x04
    void* mpEnd;               // +0x08
    int   mNodeSize;           // +0x0c
};

extern "C" void  eastl_fixed_pool_base_init(void* self, void* p, int n, int size, int a, int b); // 0x921260
extern "C" void* FUN_00921340(int n);            // 0x921340
extern "C" uint32 FUN_009213c0(uint32 n);          // 0x9213c0
extern "C" void  eastl_hashtable_ctor(void* self, void* poolEnd, int a, void* b, void* c, void* d, void* e); // 0xa43690

// @ 0x00a44fc0
static void* FixedHashtable_ctor(FixedHashtable* self, int a, int b)
{
    FixedPoolBase pool;
    pool.mpHead = 0;
    eastl_fixed_pool_base_init(&pool, (char*)self + 0x8c, 0x140, 0x10, 4, 0);
    void* this8c = (char*)self + 0x8c;
    void* this34 = (char*)self + 0x34;
    void* poolEnd = (char*)self + 0x8c + 0x140;
    void* p = FUN_00921340(0x15);
    eastl_hashtable_ctor(self, poolEnd, 0x10, this34, this8c, p, (void*)0);
    self->m10 = 0x461c4000;
    self->m14 = 0x40000000;
    self->m18 = 0;
    uint32 n = FUN_009213c0(self->m0c);
    if ((uint32)self->m08 < n) self->erase(n);
    return self;
}

// ===========================================================================
struct FixedString {
    char* mpBegin;         // +0x00
    char* mpEnd;           // +0x04
    char* mpCapEnd;        // +0x08
    int   mAllocator;      // +0x0c
    char* mpLocal;         // +0x10
    char  mBuf[0x80];      // +0x14
    FixedString(const char* p, int len);        // 0xa450c0
    ~FixedString();                              // inline
    void assign(const char* first, const char* last);   // 0x942e50
};

// @ 0x00a450c0
FixedString::FixedString(const char* p, int len)
{
    mpLocal   = mBuf;
    mpCapEnd  = mBuf + 0x80;
    mpEnd     = mBuf;
    mpBegin   = mBuf;
    mBuf[0]   = 0;
    assign(p, p + len);
}

FixedString::~FixedString() { assign(0, 0); }

// ===========================================================================
// @ 0x00a45610
// ===========================================================================
void cSystem::FUN_00a45610(int a, int b)
{
    HashTable& t = mTable15bf38;
    Iterator it;
    t.hashFind(&it, &a);
    int node = (int)it.mpNode;
    if (node != (int)t.mpBucketArray[t.mnBucketCount]) {
        *(int*)(node + 8) = b;
        double d = (double)FUN_00a41fc0();
        *(double*)(node + 0x10) = d;
        node = *(int*)(node + 8);
        int t1 = 0xb1b104;
        int t2 = 0x61ad433;
        RefCounted* dbg = Eapd_Debug_ObjectError();
        RefCounted* pold = *(RefCounted**)(node + 0x24);
        if (pold) {
            *(void**)(node + 0x24) = 0;
            pold->Release();
        }
        (void)dbg->v08();
        (void)t1; (void)t2;
    }
}

// ===========================================================================
// @ 0x00a45780
// ===========================================================================
void cSystem::DoCommandMainThread(void* cmd)
{
    int type = FUN_00fc7e50(cmd);
    if (type == 0x3a0fcce) {
        uint32 key;
        if (FUN_00a0fab0(cmd, 0x3475385, &key)) {
            HashTable& t = mTable15bf38;
            Iterator it;
            t.hashFind(&it, &key);
            if (it.mpNode != t.mpBucketArray[t.mnBucketCount]) {
                uint32 sub = 0, val = 0;
                FUN_00a0fab0(cmd, 0x3a0fce5, &sub);
                FUN_00a0fab0(cmd, 0x39e3c9f, &val);
                if (sub == 0x3a0fd6e) {
                    FUN_00a44f70(key);
                } else if (sub == 0x617208b) {
                    FUN_00a45610((int)it.mpNode, val);
                    FUN_00a31f20(cmd);
                    return;
                }
            }
        }
    } else if (type == 0x40fdf2f) {
        Server* srv = EA_Messaging_GetServer();
        if (srv) {
            char msg[0x20];
            if (FUN_00a34dc0(msg, cmd)) {
                srv->s14(0x41638ca, msg, 0);
                FUN_00a31f20(cmd);
                return;
            }
        }
    }
    FUN_00a31f20(cmd);
}

// ===========================================================================
// @ 0x00a458b0
// ===========================================================================
void cSystem::FUN_00a458b0(char* s, char* t)
{
    if (mpSocket15bce0 == 0) return;
    char* colon = strchr(s, 0x3a);
    if (!colon || colon == s || colon[1] == 0) return;
    FixedString str(s, (int)(colon - s));
    uint32 addr = EA_Sockets_IPAddress_LookupName(&str, -1);
    long port = atol(colon + 1);
    struct { uint16 family; uint16 port; uint32 addr; } sa;
    sa.family = 2;
    sa.port = (uint16)(((uint16)port << 8) | ((uint16)port >> 8));
    sa.addr = addr;
    void* sock = *(void**)((char*)mpSocket15bce0 + 0x80);
    int n = 0;
    while (t[n]) n++;
    typedef void (__thiscall *SendFn)(void*, char*, int, void*, int);
    SendFn fn = *(SendFn*)((char*)sock + 0x1c);
    fn((char*)sock - 0x80, t, n + 1, &sa, 0);
    if (str.mpBegin != 0 && (int)(str.mpCapEnd - str.mpBegin) > 1 && str.mpBegin != str.mBuf) {
        operator_delete(str.mpBegin);
    }
}

// ===========================================================================
struct ResKey { uint32 id; uint32 group; uint32 extra; };

struct FixedVector3 { ResKey* mpBegin; ResKey* mpEnd; ResKey* mpCapEnd; };

struct EA_ResourceMan_Manager {
    virtual void r00(); virtual void r04(); virtual void r08(); virtual void r0c();
    virtual void r10(); virtual void r14(); virtual void r18(); virtual void r1c();
    virtual void r20(); virtual void r24(); virtual void r28(); virtual void r2c();
    virtual void r30(); virtual void r34();
    virtual void r38(void* out, void* key, int c);   // +0x38
};

struct EmitterModel {
    void* mpPool; // placeholder
};

struct EAPD_System {
    virtual void y00(); virtual void y04(); virtual void y08(); virtual void y0c();
    virtual void y10(); virtual void y14(float); virtual void y18(float);
};

struct ResourceObj {
    virtual void pf00();
    virtual void pf04();
};

struct DatagramSocket {
    virtual void d00(); virtual void d04(); virtual void d08();
    virtual void d0c(); virtual void d10(); virtual void d14();
    virtual void d18(); virtual void d1c(); virtual void d20();
    virtual void d24();                 // +0x24
};

extern "C" void* Eapd_Debug_ObjectError2();          // 0x8de1a0
extern "C" void* SP_MessageServer();

struct cEventModifierStub {
    void Init();      // 0xa3a180
};

// @ 0x00a45130
bool cSystem::FUN_00a45130()
{
    if (!FUN_00a31170(this)) return false;

    FixedVector3 list;
    list.mpBegin = 0; list.mpEnd = 0; list.mpCapEnd = 0;

    ResKey key;
    key.id    = 0x1402ee0;
    key.group = *(uint32*)0x15541dc;
    key.extra = 0;

    EA_ResourceMan_Manager* mgr = (EA_ResourceMan_Manager*)EA_ResourceMan_GetManager();
    mgr->r38(&list, &key, 0);

    for (ResKey* it = list.mpBegin; it != list.mpEnd; it += 1) {
        this->AddSymbolList(it->id);
    }

    mpEventModifier = (RefCounted*)operator_new6(0x38, "Audio", 0, 0, 0, 0);
    if (mpEventModifier) cEventModifier_Init(mpEventModifier);

    // register emitter constructors
    uint32 ids[3] = { 0x1a527db, 0x22d2c83, 0x7c05b331 };
    void*   fns[3] = { (void*)0xa420d0, (void*)0xa42130, SP_ConstructcEmitterModelSound };
    for (int i = 0; i < 3; i++) {
        Iterator it;
        mSymbolTable.hashFind(&it, &ids[i]);
        *(void**)((char*)it.mpNode + 4) = fns[i];
    }

    mp15bc80 = (RefCounted*)operator_new6(0x2c, "Audio", 0, 0, 0, 0);
    if (mp15bc80) FUN_00a466d0(mp15bc80);

    char cfg[0x40];
    for (int i = 0; i < 0x40; i++) cfg[i] = 0;
    bool ok = FUN_00a68e90(&mField15bc34) != 0;

    if (ok) {
        EAPD_System* sys = (EAPD_System*)Eapd_ISystem_GetSingletonPtr();
        if (sys) {
            sys->y14(mf15bcd8);
            sys->y18(mf15bcdc);
            SP_Pixie_Register();
            SP_Mixer_Register();
            SP_Trixie_Register();
            SP_SendGame_Register();
            ResourceObj* res = (ResourceObj*)ZoneObject_operator_new6(8, "Audio", 0, 0, 0, 0);
            if (res) { }
            mp15bc7c = (RefCounted*)res;
            ((IHandler6*)Eapd_Debug_ObjectError2())->h14();
            DatagramSocket* sock = (DatagramSocket*)operator_new6(0x84, "Audio", 0, 0, 0, 0);
            mpSocket15bce0 = (RefCounted*)sock;
            if (sock) sock->d24();
            return true;
        }
    }
    return false;
}
