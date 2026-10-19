// src/game/SPAudio/SPAudioSystem.cpp -- migrated from slice(s) s00a44bb0, s00a42cb0 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioSystem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/System.h"
#include "SP/Audio/cSystem.h"
#include "SP/Audio/cEventModifier.h"

// ---- items of slice s00a42cb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
extern uint32_t gTuningGroupID;                 // 0x015541dc (no PDB name)
}
namespace SP {
struct ResourceKey { uint32_t instanceID; uint32_t typeID; uint32_t groupID; };
}
namespace SP {
struct EAAudioSystemTuning {                    // EA::Audio::System base at this+0; only ReadTuningValues is used here
    bool ReadTuningValues(const ResourceKey* key);   // 0x00a29be0, thiscall, ret 4
};
}
namespace SP {
struct EAPDSystemTuning {                       // EA::Audio::Eapd::ISystem (singleton)
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void SetValue5(float v);            // vtable +0x14
    virtual void SetValue6(float v);            // vtable +0x18
    static EAPDSystemTuning* GetSingletonPtr(); // 0x00a67c60, no args
};
}
namespace SP {
struct TuningReaderStub {                       // object at cSystem +0x1f8
    virtual void slot0();  virtual void slot1();  virtual void slot2();  virtual void slot3();
    virtual void slot4();  virtual void slot5();  virtual void slot6();  virtual void slot7();
    virtual void slot8();  virtual void slot9();  virtual void slot10(); virtual void slot11();
    virtual void ReadFloatById(uint32_t id, float* out);   // vtable +0x30, ret 8
};
}
namespace SP {
struct EventModifierTuning {
    void ReadTuningValues(const ResourceKey* key);         // 0x00a39f90, thiscall, ret 4
};
}
namespace SP {
struct cSystemTuning {                          // SP::Audio::cSystem, only the fields this function touches
    EAAudioSystemTuning base;                   // +0x0 (empty placeholder, size 1)
    char pad0[0x1f8 - 1];
    TuningReaderStub* mpTuningReader;           // +0x1f8
    char pad1[0x15bc78 - 0x1fc];
    EventModifierTuning* mpEventModifier;       // +0x15bc78
    char pad2[0x15bcd8 - 0x15bc7c];
    float mTuneA;                               // +0x15bcd8
    float mTuneB;                               // +0x15bcdc

    void AddSymbolList(uint32_t id);            // 0x00a43580, thiscall, ret 4
    void ReadPolyphonyCounters();               // 0x00a42cb0, thiscall, no args
    bool ReadTuningValues(const ResourceKey* key);
};
}
// ---- items of slice s00a42cb0 end

// ---- items of slice s00a44bb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void*   EA_ResourceMan_GetManager();              // 0x67dcd0
extern "C" void*   operator_new6(int size, const char* name, int a, int b, int c, int d); // 0xf473a0
extern "C" void    operator_delete(void* p);                 // 0xf47380
extern "C" void*   ZoneObject_operator_new6(int size, const char* name, int a, int b, int c, int d); // 0x926020
extern "C" void SP_Pixie_Register();       // 0xa3edb0
extern "C" void SP_Mixer_Register();       // 0xa3d380
extern "C" void SP_Trixie_Register();      // 0xa40e80
extern "C" void SP_SendGame_Register();    // 0xa3f000
extern "C" void* SP_ConstructcEmitterModelSound();        // 0xa465b0
extern "C" int   FUN_00a68e90(void* p);                   // 0xa68e90
extern "C" void  FUN_00a466d0(void* p);                   // 0xa466d0
extern "C" void  FUN_00a31f20(void* cmd);                 // 0xa31f20
extern "C" int   FUN_00a34dc0(void* msg, void* node);     // 0xa34dc0
extern "C" int   FUN_00fc7e50(void* node);                // 0xfc7e50 (Node::Type)
extern "C" int   FUN_00a43580_helper();                   // 0xa43580
extern "C" int   FUN_00a31170(void* self);                // 0xa31170 cSystem::InitAT
extern "C" long  atol(const char*);                       // msvcr90
extern "C" char* strchr(const char*, int);                // msvcr90
extern void cEventModifier_Init(void* m);
extern "C" void* Eapd_Debug_ObjectError2();          // 0x8de1a0
typedef unsigned int   uint32;
typedef unsigned short uint16;
typedef unsigned char  byte;
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
extern "C" Server* EA_Messaging_GetServer();                 // 0x883860
extern "C" IHandler6*  Eapd_ISystem_GetSingletonPtr();       // 0xa67c60
extern "C" int   FUN_00a0fab0(void* cmd, uint32 id, uint32* out); // 0xa0fab0 GetUint32
extern "C" uint32 EA_Sockets_IPAddress_LookupName(void* self, int flags); // 0x94c1b0
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
FixedString::~FixedString() { assign(0, 0); }
struct ResKey { uint32 id; uint32 group; uint32 extra; };
struct FixedVector3 { ResKey* mpBegin; ResKey* mpEnd; ResKey* mpCapEnd; };
struct EA_ResourceMan_Manager {
    virtual void r00(); virtual void r04(); virtual void r08(); virtual void r0c();
    virtual void r10(); virtual void r14(); virtual void r18(); virtual void r1c();
    virtual void r20(); virtual void r24(); virtual void r28(); virtual void r2c();
    virtual void r30(); virtual void r34();
    virtual void r38(void* out, void* key, int c);   // +0x38
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
// ---- items of slice s00a44bb0 end

// @ 0x00a43a50
namespace SP {
bool cSystemTuning::ReadTuningValues(const ResourceKey* key)
{
    if (!base.ReadTuningValues(key)) return false;
    if (key->groupID == gTuningGroupID) AddSymbolList(key->instanceID);
    if (mpEventModifier) mpEventModifier->ReadTuningValues(key);
    ReadPolyphonyCounters();
    mTuneA = 0.0f;
    mpTuningReader->ReadFloatById(0xdacee1bd, &mTuneA);
    mTuneB = 0.01f;
    mpTuningReader->ReadFloatById(0x1c05b1a7, &mTuneB);
    EAPDSystemTuning* sys = EAPDSystemTuning::GetSingletonPtr();
    if (sys) {
        sys->SetValue5(mTuneA);
        sys->SetValue6(mTuneB);
    }
    return true;
}
}  // namespace SP

// @ 0x00a44e80
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

// @ 0x00a45780
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

// @ 0x00a458b0
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
