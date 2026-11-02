// src/game/SPAudio/SPAudioSystem.cpp -- migrated from slice(s) s00a459d0, s00a43d30, s00a41c40, s00a44bb0, s00a42cb0 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioSystem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/System.h"
#include "SP/Audio/cSystem.h"
#include "SP/Audio/cEventModifier.h"
#include <math.h>
#include "EA/CommandLine.h"
#include "EA/Messaging/IHandler.h"
#include "EA/Audio/Command.h"

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
extern "C" void*   SP_MessageServer();                       // 0x67dcc0
extern "C" void*   EA_ResourceMan_GetManager();              // 0x67dcd0
extern "C" void*   operator_new6(int size, const char* name, int a, int b, int c, int d); // 0xf473a0
extern "C" void    operator_delete(void* p);                 // 0xf47380
extern "C" void*   ZoneObject_operator_new6(int size, const char* name, int a, int b, int c, int d); // 0x926020
extern "C" void SP_Pixie_Register();       // 0xa3edb0
extern "C" void SP_Mixer_Register();       // 0xa3d380
extern "C" void SP_Trixie_Register();      // 0xa40e80
extern "C" void SP_SendGame_Register();    // 0xa3f000
extern "C" void* SPAudioVoiceManagerEAPD_ctor(void* self); // 0xa465b0
extern "C" void* __fastcall SP_ConstructcEmitterSndPlayer(void* self); // 0xa398d0
extern "C" void* __fastcall FUN_0092b1d0(void* self);     // 0x92b1d0
extern "C" void  __fastcall FUN_005d7450(void* self);     // 0x5d7450
extern "C" bool  __fastcall FUN_00a31170(void* self);     // 0xa31170 cSystem::InitAT
extern "C" long  atol(const char*);                       // msvcr90
extern "C" char* strchr(const char*, int);                // msvcr90
extern "C" const float g_fSoundMapRate;   // 0x1453edc  (14.285714f)
extern "C" int FUN_00921340(unsigned n);          // 0x921340
extern "C" void* __fastcall UTF_Sockets_Sockets_ctor(void* self);       // 0x94e920
extern "C" void  __fastcall FUN_00a466d0(void* self);                   // 0xa466d0
extern "C" void  __fastcall cEventModifier_Init(void* self);            // 0xa3a180
typedef unsigned int   uint32;
typedef unsigned short uint16;
typedef unsigned char  byte;
typedef unsigned char  uint8;
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
    void  find(Iterator* out, const void* pKey);          // 0x645ed0
    void  insert(Iterator* out, const void* value, uint32 extra);  // 0xa43bd0
    void  insertSymbol(Iterator* out, const void* value, bool flag); // 0xa26ce0
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
struct Command {
    uint32 Type();                                // 0xfc7e50 (Node::Type)
    bool   GetUint32(uint32 id, uint32* out);     // 0xa0fab0
};
struct cEapdMessage {
    Command* mCommand;                            // +0x00
    uint32   m04;                                 // +0x04
    uint32   m08;                                 // +0x08
    uint32   m0c;                                 // +0x0c
    bool   Init(Command* cmd);                    // 0xa34dc0
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
    bool SysDoCommandMainThread(void* cmd);         // 0xa31f20
};
struct DbgObject {
    virtual void d00();
    virtual void d04();
    virtual void d08();
    virtual bool CreateObject(int* a, void** out, int c, int d, int e, int f); // +0x0c
    virtual void d10();
    virtual void d14();
    virtual void d18();
    virtual void d1c();
    virtual void d20();
    virtual void d24();
    virtual void d28();
    virtual void d2c();
    virtual void d30();
    virtual void d34();
    virtual void d38();
    virtual void d3c();
    virtual void d40();
    virtual void d44(int a, void* b, int c);       // +0x44
};
struct NodeObject {
    virtual void o00();
    virtual void Release();                   // +0x04
    virtual void o08();
    virtual void o0c();
    virtual void o10();
    virtual void o14();
    virtual void o18();
    virtual void o1c();
    virtual void o20();
    virtual bool GetProperty(uint32 id, void** out);   // +0x24
};
struct PropertyValue {
    char   pad00[0x12];
    uint16 mType;                             // +0x12
    uint32* GetUInt();                        // 0x41ea00
    float* GetFloat();                        // 0x41ea70
};
struct Node15bf38 {
    uint32      mId;                          // +0x00
    uint32      mPad04;                       // +0x04
    int         mValue08;                     // +0x08
    uint32      mPad0c;                       // +0x0c
    double      mTimestamp10;                 // +0x10
    float       mField18;                     // +0x18
    float       mField1c;                     // +0x1c
    float       mField20;                     // +0x20
    NodeObject* mpObject;                     // +0x24
};
extern "C" Server* EA_Messaging_GetServer();                 // 0x883860
extern "C" DbgObject* Eapd_Debug_ObjectError();              // 0x8de1a0
extern "C" IHandler6*  Eapd_ISystem_GetSingletonPtr();       // 0xa67c60
struct SoundConfig {
    uint32 m00;            // +0x00
    uint32 m04;            // +0x04
    uint32 m08;            // +0x08
    uint32 m0c;            // +0x0c
    uint32 m10;            // +0x10
    uint32 m14;            // +0x14
    uint8  m18;            // +0x18
    char   pad19[3];
    uint32 m1c;            // +0x1c
    uint8  m20;            // +0x20
    char   pad21[3];
    uint32 m24;            // +0x24
    void*  m28;            // +0x28
    uint32 m2c;            // +0x2c
    void*  m30;            // +0x30
    uint32 m34;            // +0x34
    uint32 m38;            // +0x38
    uint32 m3c;            // +0x3c
};
extern "C" int   FUN_00a68e90(void* dest, SoundConfig cfg); // 0xa68e90
extern "C" uint32 EA_Sockets_IPAddress_LookupName(void* self, int flags); // 0x94c1b0
extern void cSystem_SetCurrentContext(cSystem* self, int ctx);
void cSystem_SetCurrentContext(cSystem* self, int ctx);  // 0xa426f0
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
struct SoundMapValue {
    uint32      mKey;       // +0x00
    uint32      mPad04;     // +0x04
    uint32      mField08;   // +0x08
    uint32      mPad0c;     // +0x0c
    double      mField10;   // +0x10
    float       mField18;   // +0x18
    float       mField1c;   // +0x1c
    float       mField20;   // +0x20
    RefCounted* mpObject;   // +0x24
};
struct FixedPoolBase {
    void*  mpHead;             // +0x00
    void*  mpTail;             // +0x04
    void*  mpBlock;            // +0x08
    void*  mpBlockEnd;         // +0x0c
    uint32 mNodeSize;          // +0x10
    void*  mpOwner;            // +0x14
    void   init(void* p, unsigned count, unsigned blockSize, unsigned align, unsigned extra); // 0x921260
};
struct PrimeRehashPolicy {
    float  mfMaxLoadFactor;    // +0x00
    float  mfGrowthFactor;     // +0x04
    uint32 mnNextResize;       // +0x08
    uint32 GetBucketCount(uint32 n);   // 0x9213c0
};
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
    // eastl::hashtable constructor (thiscall, seven stack arguments)
    void  hashtableCtor(int bucketCount, int a, int* pb1, int* pb2, int b, int* pb3,
                        FixedPoolBase* pool);                 // 0xa43690
};
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
extern "C" uint32 g_resourceGroupId;   // 0x15541dc
struct ResKey { uint32 id; uint32 group; uint32 extra; };
struct ResKeyList { ResKey* mpBegin; ResKey* mpEnd; ResKey* mpCapEnd; };
struct AllocBlockHeader { int32_t mRefCount; };
struct EA_ResourceMan_Manager {
virtual void r00();
virtual void r04();
virtual void r08();
virtual void r0c();
virtual void r10();
virtual void r14();
virtual void r18();
virtual void r1c();
virtual void r20();
virtual void r24();
virtual void r28();
virtual void r2c();
virtual void r30();
virtual void r34();
    virtual void r38(void* out, void* key, int c);   // +0x38
};
struct RefCounted4 {
    virtual void v00();
    virtual void AddRef();      // +0x04
    virtual void Release();     // +0x08
};
struct VoiceManager {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void AddRef();
    virtual void Release();                        // +0x28
};
struct SockSub {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
};
struct DatagramSocketObj {
    char    pad00[8];
    SockSub mSub;                                  // +0x08
};
struct EAPD_System {
virtual void y00();
virtual void y04();
virtual void y08();
virtual void y0c();
virtual void y10();
virtual void y14(float);
virtual void y18(float);
};
struct ResourceObj {
    void* mpVtbl;      // +0x00
    int   mRefCount;   // +0x04
};
// ---- items of slice s00a44bb0 end

// ---- items of slice s00a41c40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kEpsilon;    // 0x013ec4b8
extern char gEmptyString16[];   // 0x01667bac
extern double gSecondsPerTick;      // 0x0166f398
extern int gTimerFlags;             // 0x0166f3a8
extern void* gFn1675f58;                            // 0x01675f58
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(pad_, __COUNTER__)();
#define VP4 VP VP VP VP
#define VP8 VP4 VP4
#define VP16 VP8 VP8
void* operator new(unsigned int, const char*, int, int, const char*, int);
void* operator new(unsigned int);
void operator delete(void*);
void operator delete[](void*);
struct Vector3
{
    float x;    // +0x00
    float y;    // +0x04
    float z;    // +0x08
};
struct CurveDesc;
union LARGE_INTEGER
{
    struct
    {
        unsigned int LowPart;   // +0x00
        int HighPart;           // +0x04
    };
    unsigned __int64 QuadPart;
};
unsigned __int64 GetStopwatchFrequency();                                   // 0x0093a470
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER*);
extern LARGE_INTEGER gStart;        // 0x0166f3a0
namespace EA {
namespace Audio {
class ResponseCurve_s00a4_1c40
{
public:
    ResponseCurve_s00a4_1c40();                                        // 0x00a1aa50
    ~ResponseCurve_s00a4_1c40() throw();
    float GetOutputValue(float value) const;                // 0x00a1a110

    void* mpData;               // +0x00
    char mPad_04[0x0c];         // +0x04
    void* mpAllocation;         // +0x10
    char mPad_14[0x350];        // +0x14  (sizeof == 0x364)
};
}
}
namespace EA {
namespace Audio {
ResponseCurve_s00a4_1c40::~ResponseCurve_s00a4_1c40() throw()
{
    if (mpData && mpData != mpAllocation)
        operator delete(mpData);
}
}
}
namespace EA {
namespace Audio {
class Sound_s00a4_1c40
{
public:
    Sound_s00a4_1c40();                                                // 0x00a1fbb0
    virtual ~Sound_s00a4_1c40();                                       // 0x00a1f4d0
    void CommitAllProperties();                             // 0x00a1d080
};
}
}
struct TeString
{
    const void* mpBegin;        // +0x00
    const void* mpEnd;          // +0x04
    const void* mpCapacity;     // +0x08

    TeString()
        : mpBegin(gEmptyString16),
          mpEnd(gEmptyString16),
          mpCapacity((char*)gEmptyString16 + 1)
    {
    }
    ~TeString() throw();
};
TeString::~TeString() throw()
{
    if ((const char*)mpCapacity - (const char*)mpBegin > 1 && mpBegin)
        operator delete((void*)mpBegin);
}
namespace SP {
namespace Audio {
struct __declspec(novtable) CurveSource
{
    VP VP VP
    virtual void Slot0c(unsigned int id, float value, int flag);   // +0x0c
    virtual bool Slot10(unsigned int id, float* pOut);             // +0x10
};
}
}
namespace SP {
namespace Audio {
struct __declspec(novtable) ThirdBase
{
    VP VP
};
}
}
namespace SP {
namespace Audio {
class cSound : public EA::Audio::Sound_s00a4_1c40, public CurveSource, public ThirdBase
{
public:
    static void* operator new(unsigned int size);           // 0x00a41cc0

    cSound();
    ~cSound();

    float ComputeGainAttenuation(float a, float b, float c, float d, float e);  // 0x00a41c40
    void CommitAllProperties();                             // 0x00a41d30

    char mPad_0c[0x44 - 0x0c];      // +0x0c
    void* mpObj44;                  // +0x44
    char mPad_48[0xce4 - 0x48];     // +0x48
    unsigned int mFlags;            // +0xce4
    char mPad_ce8[0x1e10 - 0xce8];  // +0xce8
    EA::Audio::ResponseCurve_s00a4_1c40 mCurve1e10;    // +0x1e10
    EA::Audio::ResponseCurve_s00a4_1c40 mCurve2174;    // +0x2174
    EA::Audio::ResponseCurve_s00a4_1c40 mCurve24d8;    // +0x24d8
    EA::Audio::ResponseCurve_s00a4_1c40 mCurve283c;    // +0x283c
    int mStartContext;              // +0x2ba0
    bool mb2ba4;                    // +0x2ba4
    bool mb2ba5;                    // +0x2ba5
    TeString mName;                 // +0x2ba8
    int mPad_2bb4;                  // +0x2bb4  (sizeof == 0x2bb8)
};
}
}
namespace SP {
namespace Audio {
class cAudioSystem
{
public:
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP     // 0x00..0x34
    virtual void V38(unsigned int id);             // +0x38
    VP                                             // +0x3c
    virtual void V40(unsigned int id, int value);  // +0x40
    VP VP VP VP VP                                 // +0x44..0x54
    virtual void V58();                            // +0x58
    VP16 VP16 VP16 VP16                            // +0x5c..0x158
    virtual int V15c(int arg);                     // +0x15c

    // data (the vptr lives at +0, these follow it)
    char mPad_04[0x29 - 0x04];          // +0x04
    bool mbNoFocus;                     // +0x29
    char mPad_2a[0x60 - 0x2a];          // +0x2a
    void* mp60;                         // +0x60
    char mPad_64[0x94 - 0x64];          // +0x64
    bool mb94;                          // +0x94
    char mPad_95[0xa4 - 0x95];          // +0x95
    void* mpA4;                         // +0xa4
    char mPad_a8[0x128aec - 0xa8];      // +0xa8
    int mn128aec;                       // +0x128aec
    char mPad_128af0[0x132814 - 0x128af0];
    int mn132814;                       // +0x132814
    char mPad_132818[0x15bbe4 - 0x132818];
    Vector3 mCameraPos;                 // +0x15bbe4
    bool mb15bbf0;                      // +0x15bbf0
    char mPad_15bbf1[0x15bc38 - 0x15bbf1];
    void* mpCurrentContext;             // +0x15bc38
    int mn15bc3c;                       // +0x15bc3c
    unsigned char mb15bc40;             // +0x15bc40
    char mPad_15bc41[0x15bc42 - 0x15bc41];
    bool mb15bc42;                      // +0x15bc42
    char mPad_15bc43[0x15bc44 - 0x15bc43];
    Vector3 mV44;                       // +0x15bc44
    Vector3 mV50;                       // +0x15bc50
    Vector3 mV5c;                       // +0x15bc5c
    Vector3 mV68;                       // +0x15bc68
    void* mp15bc74;                     // +0x15bc74
    void* mp15bc78;                     // +0x15bc78
    char mPad_15bc7c[0x15bc80 - 0x15bc7c];
    void* mp15bc80;                     // +0x15bc80
    int mn15bc84;                       // +0x15bc84
    int mn15bc88;                       // +0x15bc88
    int mn15bc8c;                       // +0x15bc8c
    int mn15bc90;                       // +0x15bc90
    int mn15bc94;                       // +0x15bc94
    int mn15bc98;                       // +0x15bc98
    int mn15bc9c;                       // +0x15bc9c
    int mn15bca0;                       // +0x15bca0
    char mPad_15bca4[0x15bce4 - 0x15bca4];
    void* mp15bce4;                     // +0x15bce4
    char mPad_15bce8[0x15bcec - 0x15bce8];
    void* mp15bcec;                     // +0x15bcec
    char mPad_15bcf0[0x15bf24 - 0x15bcf0];
    int mn15bf24;                       // +0x15bf24

    bool PreInit(void* pCommandLine);                   // 0x00a42220
    void SetupTypePriorities();                         // 0x00a42310
    void SetTypePriority(unsigned int id, float value); // 0x00a42360
    int ResolveCurve(struct CurveDesc* d);              // 0x00a423a0
    void ResetCurveIds();                               // 0x00a424b0
    bool UpdateAndTestRunTimePolyphonyForSound(void* snd, int count);   // 0x00a424e0
    bool GetProperty(unsigned int id, float* out);      // 0x00a42640
    void SetCurrentContext(void* ctx);                  // 0x00a426f0
    int GetContextId();                                 // 0x00a42740
    void GetListenerVectors(Vector3* a, Vector3* b, Vector3* c, Vector3* d);   // 0x00a42750
    void RegisterModules();                             // 0x00a427e0
    void Update(float dt);                              // 0x00a428a0
    void CommandResolve(void* cmd);                     // 0x00a429a0
    bool OnEventModifier(void* cmd);                    // 0x00a42aa0
    float GetDistance(Vector3* p);                      // 0x00a42ad0
    bool RegisterHandler(unsigned int index, void* obj);    // 0x00a42c10
    bool UnregisterHandler(unsigned int index);             // 0x00a42c30

    // non-virtual callees (bodies outside this object file)
    bool Map_266e0(unsigned int id, float value);       // 0x00a266e0
    void Map_26530();                                   // 0x00a26530
    void UpdateInternal(float dt);                      // 0x00a25c40
    void RegisterBuiltInModules();                      // 0x00a21170
};
}
}
namespace SP {
namespace Audio {
struct cSystem_s00a4_1c40
{
    char mPad_00[0x29];             // +0x000
    bool mb29;                      // +0x029
    char mPad_2a[0x30c - 0x2a];     // +0x02a
    int mn30c;                      // +0x30c

    cAudioSystem* Engine() { return (cAudioSystem*)((char*)this - 0x15bc18); }
    void SetupContext();            // 0x00a422c0
};
}
}
using SP::Audio::cAudioSystem;
using SP::Audio::cSound;
using SP::Audio::cSystem_s00a4_1c40;
namespace EA {
struct WString
{
    wchar_t* mpBegin;       // +0x00
    wchar_t* mpEnd;         // +0x04
    wchar_t* mpCapacity;    // +0x08
    void* mAlloc;           // +0x0c
};
}
namespace EA {
struct CommandLine_s00a4_1c40
{
    unsigned int FindSwitch(const wchar_t* pSwitch, bool exact, WString* pOut, unsigned int start);  // 0x0092b300 (EA::CommandLine::FindSwitch)
};
}
class ResourceManager
{
public:
    VP16 VP4 VP VP
    virtual int V58(void* pDesc);                   // +0x58
};
ResourceManager* GetManager();                      // 0x0067dcd0
void FUN_00a3cdb0();                                // 0x00a3cdb0
void FUN_00a3cea0();                                // 0x00a3cea0
void FUN_00a37680();                                // 0x00a37680
namespace EA {
namespace Audio {
namespace Eapd {
namespace Debug {
class EapdObj
{
public:
    VP16 VP8 VP4
    virtual void V70(int a, void* desc);                // +0x70
};
}
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
namespace Debug {
class EapdEvent
{
public:
    EapdEvent(unsigned int id) : mId(id) {}
    virtual ~EapdEvent() {}     // user dtor: registers the EH cleanup (0x1219d80-style)
    unsigned int mId;   // +0x04
};
}
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
namespace Debug {
EapdObj* ObjectError();                                 // 0x008de1a0
}
}
}
}
namespace EA {
namespace Audio {
class SystemAT
{
public:
    VP16 VP16 VP16 VP8 VP4 VP
    virtual unsigned int SymbolToId(const char* name);      // +0xf4
};
}
}
namespace EA {
namespace Audio {
SystemAT* GetSystemAT();                                    // 0x00a206f0
}
}
namespace SP {
namespace Audio {
class cEmitterModelSound
{
public:
    static void* operator new(unsigned int size);   // 0x00a37f70
    cEmitterModelSound();                           // 0x00a38c70
    char mData[0xe18];
};
}
}
class Command_s00a4_1c40
{
public:
    int Type();                                     // 0x00fc7e50
    bool SetT(unsigned int id, int a, int b);       // 0x00a0fa50
    char* GetString8(unsigned int id);              // 0x00a0fb60
    bool GetBool(unsigned int id, void* out);       // 0x00a0fa70
    void SetUint64(unsigned int id, unsigned int value);        // 0x00a0fcf0
};
class cEventModifier_s00a4_1c40
{
public:
    bool ModifyEvent(Command_s00a4_1c40* cmd);                 // 0x00a39620
};
class EventMod
{
public:
    VP VP
    virtual unsigned int V08(float* pValue);        // +0x08
};
class HandlerTable
{
public:
    bool Register(unsigned int index, void* obj);   // 0x00a39280
    bool Unregister(unsigned int index);            // 0x00a392d0
};
class SoundInit
{
public:
    virtual void V00();
};
class cTypeMapHolder
{
public:
    void SetTypePriority(unsigned int id, unsigned int priority);  // 0x00a2f180
};
class RwVoiceList
{
public:
    void RegisterBuiltIn();             // 0x0112dca0
};
class RwDecoderRegistry
{
public:
    void RegisterBuiltInPlugIns();      // 0x0112dbd0
};
class RwAudioSystem
{
public:
    RwVoiceList* GetVoiceList();            // 0x0112ce00
    RwDecoderRegistry* GetDecoderRegistry();    // 0x0112dc80
};
class SoundObj
{
public:
    VP VP VP VP VP VP VP VP
    virtual bool V20(int a, int b);                 // +0x20
    VP VP VP VP VP VP VP VP
    virtual int V44(int arg);                       // +0x44

    int FUN_00a1b3f0();                             // 0x00a1b3f0
    int FUN_00a1ad70();                             // 0x00a1ad70
    int FUN_00a1ad80();                             // 0x00a1ad80
    int FUN_00a1ad90();                             // 0x00a1ad90
    int FUN_00a1ada0();                             // 0x00a1ada0
};
struct CurveDesc
{
    char m00;               // +0x00
    char m01;               // +0x01
    char m02;               // +0x02
    char m03;               // +0x03
    char mPad_04[0x20];     // +0x04
    unsigned int m24;       // +0x24
    unsigned int m28;       // +0x28
    unsigned int m2c;       // +0x2c
    unsigned int m30;       // +0x30
    unsigned int m34;       // +0x34
    unsigned int m38;       // +0x38
    unsigned int m3c;       // +0x3c
    unsigned int m40;       // +0x40
    unsigned int m44;       // +0x44
};
// ---- items of slice s00a41c40 end

// ---- items of slice s00a43d30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double modf(double value, double* pIntPart);
extern "C" double pow(double base, double exponent);
extern "C" double sqrt(double value);
extern "C" double fabs(double value);
extern char* gpCheatInvulnerable;                   // 0x01553fac
extern char* gpCheatAllPowerups;                    // 0x01553fb0
extern char* gpCheatUsermusic;                      // 0x01553fb8
#ifndef NULL
#endif
void* operator new(unsigned int size, const char* pName, int flags = 0, unsigned int debugFlags = 0,
                   const char* pFile = 0, int line = 0);   // 0x00f473a0
namespace SP {
struct Sys
{
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
virtual void vc0();
virtual void vc4();
virtual void vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
virtual void vdc();
virtual void ve0();
virtual void ve4();
virtual void ve8();
virtual void vec();
virtual void vf0();
virtual void vf4();
virtual void vf8();
    virtual void ConfigureSpeakerMode(unsigned int id, float value);   // +0xfc
virtual void v100();
virtual void v104();
virtual void v108();
virtual void v10c();
virtual void v110();
virtual void v114();
virtual void v118();
virtual void v11c();
virtual void v120();
virtual void v124();
virtual void v128();
virtual void v12c();
virtual void v130();
virtual void v134();
virtual void v138();
virtual void v13c();
virtual void v140();
virtual void v144();
virtual void v148();
virtual void v14c();
virtual void v150();
virtual void v154();
virtual void v158();
    virtual int  GetSoundFromHandle(int handle, int unused);           // +0x15c
virtual void v160();
virtual void v164();
virtual void v168();
virtual void v16c();
virtual void v170();
virtual void v174();
    virtual bool GetSoundDefinition(int definition, unsigned int* pOut);  // +0x178
virtual void v17c();
virtual void v180();
virtual void v184();
    virtual bool FindSoundInstance(unsigned int* pKey, int* pOut);     // +0x188
    virtual bool GetSoundInstance(unsigned int* pKey, void** pOut);    // +0x18c
virtual void v190();
virtual void v194();
virtual void v198();
virtual void v19c();
    virtual void v1a0();
    virtual int  StartSoundDefinition(int definition);                 // +0x1a4

    bool Init();            // 0x00a252b0  System::Init
    bool Shutdown();        // 0x00a207d0  ?Shutdown@Sys@@QAE_NXZ
};
}
namespace SP {
float GetPropertyAsFloatArray(void* pConfiguration, unsigned int name, float** ppValues,
                              int* pnValues);   // 0x006a08b0
}
namespace EA {
namespace Messaging {
struct IHandler_s00a4_3d30
{
    virtual void v00();
    virtual void v04();
};
}
}
namespace EA {
namespace Messaging {
struct Server_s00a4_3d30
{
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20();
    virtual void AddHandler(IHandler_s00a4_3d30* pHandler, unsigned int messageID);   // +0x24
};
}
}
namespace EA {
namespace Messaging {
Server_s00a4_3d30* GetServer();                                                     // 0x00883860
}
}
namespace EA {
namespace Messaging {
void RemoveHandler(Server_s00a4_3d30* pServer, IHandler_s00a4_3d30* pHandler, const unsigned int* pIDs,
                   unsigned int count, int priority);                     // 0x00571db0
}
}
struct RefCounted_s00a4_3d30
{
    virtual void v00(int);
    int mnRefCount;                     // +0x04
    int AddRef() { return ++mnRefCount; }
    void Release()
    {
        if (--mnRefCount == 0) {
            mnRefCount = 1;
            v00(1);
        }
    }
};
struct IRefCounted
{
    virtual void v00();                 // +0x00
    virtual void AddRef();              // +0x04
    virtual void Release();             // +0x08
    virtual void v0c();                 // +0x0c
};
struct IVirtualRelease
{
    virtual void v00();                 // +0x00
    virtual void Release();             // +0x04
    virtual void v08();                 // +0x08
    virtual void v0c();                 // +0x0c
    // These objects are only ever add-ref'd by their own interface; RefPtr's add-ref branch is
    // never taken (it is only used to clear the pointers), so it stays empty.
    void AddRef() {}
};
template <class T>
struct RefPtr
{
    T* mpObject;
    RefPtr& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pOld = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pOld)
                pOld->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
struct IHandlerRC_s00a4_3d30
{
    virtual void v00();                 // +0x00  deleting destructor
    virtual void v04();                 // +0x04
    virtual void v08();                 // +0x08  AddRef
    virtual void v0c();                 // +0x0c  Release
    virtual void v10();
};
class ModelManager
{
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual void SetListener(void* pListener);      // +0x2c
    virtual void ClearListener(void* pListener);    // +0x30
};
ModelManager* GetModelManager();                    // 0x0067dd80
class cProperty;
class cPropertyList_s00a4_3d30
{
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(unsigned int name, cProperty** ppProperty);   // +0x24
};
extern cPropertyList_s00a4_3d30* gpAppPreferences;             // 0x015fd91c
class cProperty
{
public:
    unsigned int* GetUInt();                        // 0x0041ea00
    bool* GetBool();                                // 0x0041e920
    char mPad_00[0x12];
    unsigned short mnType;                          // +0x12
};
class ConfigManager
{
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
    virtual unsigned int GetValue(unsigned int name);   // +0x30
};
ConfigManager* GetConfigManager();                  // 0x0067dd30
class CheatManager
{
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual void Execute(char* pCommand);           // +0x1c
};
CheatManager* GetCheatManager();                    // 0x0067de20
void SetGlobalProperty(unsigned int name, float value);   // 0x005ca880
class AudioAT
{
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20();
    virtual int  GetVoiceHandle();                  // +0x24
    virtual void v28();
    virtual void SetGroupActive(void* pGroup);      // +0x2c
    virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
    virtual Vector3* GetListener(int index);        // +0x7c
};
namespace EA {
namespace Audio {
AudioAT* GetSystemAT_s00a4_3d30();                             // 0x00a206f0
}
}
namespace EA {
namespace Audio {
void AudioSetListener3(void* pGroup, float x, float y, float z);   // 0x009fbc50
}
}
void ReleaseGroupRef(void* pGroup, int unused);     // 0x00572020
int* GetSoundHandle(unsigned int name);             // 0x005727b0  returns the handle slot
int  GetPlaybackHandle();                           // 0x00a34e90
void Start3dSoundByName(void* pSound, int nVoice, float x, float y, float z);  // 0x00571f80
struct WString_s00a4_3d30
{
    wchar_t* mpBegin;       // +0x00
    wchar_t* mpEnd;         // +0x04
    wchar_t* mpCapacity;    // +0x08
    void* mAlloc;           // +0x0c
    void assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
};
namespace EA {
struct CommandLine_s00a4_3d30
{
    virtual void v00();
    WString_s00a4_3d30* at(unsigned int index);                                   // 0x0092b1b0
    unsigned int FindSwitch(const wchar_t* pSwitch, bool exact, WString_s00a4_3d30* pOut, unsigned int start);  // 0x0092b300 (EA::CommandLine::FindSwitch)
};
}
namespace EA {
namespace IO {
class FilePath
{
public:
    wchar_t mPath[520];                             // +0x000
    wchar_t* Set(const wchar_t* pPath);             // 0x00930f60
    unsigned int GetDriveAndDirectory(wchar_t* pBuffer, unsigned int maxLen);   // 0x00930d20
};
}
}
namespace EA {
namespace IO {
bool EnsureTrailingPathSeparator(wchar_t* pPath, int maxLen);       // 0x0092fe00
}
}
class SoundMap
{
public:
    // Owner of a curve's property configuration (erase releases it through vtable slot +0x04).
    struct ConfigRef
    {
        virtual void v00();             // +0x00
        virtual void Release();         // +0x04
    };

    struct Node
    {
        unsigned int mnName;            // +0x00  symbol key
        char mKeyPad_04[0x0c];          // +0x04
        double mf10;                    // +0x10
        float mf18;                     // +0x18
        float mf1c;                     // +0x1c
        float mf20;                     // +0x20
        ConfigRef* mpConfig;            // +0x24
        Node* mpNext;                   // +0x28
    };

    struct iterator
    {
        Node* mpNode;                   // +0x00
        Node** mpBucket;                // +0x04
    };

    unsigned int mFunctors;             // +0x00
    Node** mpBucketArray;               // +0x04
    unsigned int mnBucketCount;         // +0x08
    unsigned int mnElementCount;        // +0x0c
    char mRehashPolicy[0x0c];           // +0x10
    char mAllocator[0x08];              // +0x1c

    iterator find(const unsigned int* pName) const;                     // 0x00b41b30
    iterator erase(iterator position);                                  // 0x00a443c0
    bool isEnd(const iterator& it) const
    {
        return mpBucketArray[mnBucketCount] == it.mpNode;
    }
    void DoFreeNodes(Node** pBucketArray, unsigned int nBucketCount);   // 0x00a43c90
    void clear()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
};
struct Playing
{
    void* mpGroup;                      // +0x00  owning group object
    void* mpSound;                      // +0x04
    int mnVoice;                        // +0x08
};
class GroupMap
{
public:
    struct Node
    {
        unsigned int mnName;            // +0x00  symbol key
        char mPad_04[0x04];             // +0x04
        void* mpGroup;                  // +0x08
        Node* mpNext;                   // +0x0c
    };

    struct iterator
    {
        Node* mpNode;                   // +0x00
        Node** mpBucket;                // +0x04
    };

    unsigned int mFunctors;             // +0x00
    Node** mpBucketArray;               // +0x04
    unsigned int mnBucketCount;         // +0x08
    unsigned int mnElementCount;        // +0x0c

    iterator find(const unsigned int* pName) const;     // 0x00685f30
    iterator erase(iterator position);                  // 0x00b51cc0
    iterator insert(const Playing& value);                      // 0x00a44390
    iterator insertPlaying(const Playing& value, bool bForce);  // 0x00a43b10
    bool isEnd(const iterator& it) const
    {
        return mpBucketArray[mnBucketCount] == it.mpNode;
    }
};
class IConfiguration_s00a4_3d30;
struct EapdGroupParam
{
    unsigned int mnName;                // +0x00
    char mPad_04[0x08];                 // +0x04
    Vector3 mPosition;                  // +0x0c
    char mPad_18[0x90 - 0x18];          // +0x18
    IConfiguration_s00a4_3d30* mpConfig;           // +0x90
};
class Eapd_s00a4_3d30
{
public:
    void Remove(unsigned int name);                                     // 0x00a441b0
    void SetListener(const EapdGroupParam* pGroup);                     // 0x00a44230
    float GetCurveValue(unsigned int name);                             // 0x00a44290
    void Play(const EapdGroupParam* pGroup);                            // 0x00a449a0
    void PlayOrStop(const EapdGroupParam* pGroup, bool bStart);         // 0x00a44a80

    char mPad_000[0xd4];                // +0x000
    GroupMap mGroups;                   // +0x0d4
    char mPad_0e4[0x320 - 0x0e4];       // +0x0e4
    SoundMap mCurves;                   // +0x320
};
struct cSystem_s00a4_3d30
{
    void* mpUnused00;                       // +0x000
    IHandlerRC_s00a4_3d30 mModelListener;              // +0x004
    void* mUnused08;                        // +0x008

    struct MessageRegistration
    {
        EA::Messaging::Server_s00a4_3d30* mpServer;    // +0x00 (cSystem +0x08)
        EA::Messaging::IHandler_s00a4_3d30* mpHandler; // +0x04
        const unsigned int* mpIDArray;      // +0x08
        unsigned int mnIDCount;             // +0x0c
        int mnPriority;                     // +0x10
    } mMessageReg;                          // +0x008
    char mPad_01c[0x5c - 0x1c];             // +0x01c

    RefPtr<IVirtualRelease> mpGroupList;    // +0x05c
    char mPad_060[0xcc - 0x60];             // +0x060

    RefPtr<struct AudioCache> mpCache;       // +0x0cc
    RefPtr<struct cAudioPreferences> mpPreferences;   // +0x0d0
    RefPtr<IVirtualRelease> mpGroupHandle;  // +0x0d4
    char mPad_0d8[0x310 - 0xd8];            // +0x0d8

    WString_s00a4_3d30 mAppDir;                        // +0x310
    SoundMap mPlaying;                      // +0x320

    bool Init(EA::CommandLine_s00a4_3d30* pCommandLine);   // 0x00a43d30
};
struct AudioCache : RefCounted_s00a4_3d30
{
    AudioCache();                           // 0x00a3c970
    void Initialize();                      // 0x00a3c710
    void Stop();                            // 0x00a3bb60
    char mData[0x734 - 0x08];               // sizeof(AudioCache) == 0x734
};
struct cAudioPreferences : IRefCounted
{
    cAudioPreferences();                    // 0x00a41000
    void Init();                            // 0x00a41010
    int mnValue;                            // +0x04
};
class cAudioSystem_s00a4_3d30 : public SP::Sys
{
public:
    IHandlerRC_s00a4_3d30 mHandler;                    // +0x004
    char mPad_014[0x96 - 0x14];             // +0x014
    bool mbSilent;                          // +0x096
    char mPad_097[0x99 - 0x97];             // +0x097
    bool mbPropertyBool;                    // +0x099
    char mPad_09a[0x1fc - 0x9a];            // +0x09a
    bool mbVerboseAudio;                    // +0x1fc
    char mPad_1fd[0x200 - 0x1fd];           // +0x1fd
    unsigned int mnSampleRate;              // +0x200
    char mPad_204[0x15b774 - 0x204];        // +0x204
    bool mbNoSampleCache;                   // +0x15b774
    char mPad_15b775[0x15bc18 - 0x15b775];  // +0x15b775
    cSystem_s00a4_3d30 mSystem;                        // +0x15bc18

    bool ShutdownSystem();                                          // 0x00a44440
    bool InitCurve(void* pCurve, int nDefault, int nCurve,
                   void* pConfiguration, const Vector3* pPosition);  // 0x00a445a0
};
cAudioSystem_s00a4_3d30* gpAudioSystem;                // 0x0166f118
static const unsigned int knEngineOffset = 0x15bc18;
inline cAudioSystem_s00a4_3d30* GetAudioSystem(cSystem_s00a4_3d30* pSystem)
{
    return (cAudioSystem_s00a4_3d30*)((char*)pSystem - knEngineOffset);
}
inline void PublishAudioSystem(cAudioSystem_s00a4_3d30* pSystem)
{
    if (gpAudioSystem)
        gpAudioSystem->mHandler.v0c();
    gpAudioSystem = pSystem;
    if (pSystem)
        pSystem->mHandler.v08();
}
static const unsigned int kanAudioMessageIDs[15] = {
    0x1453f30, 0x1453f34, 0x1453f38, 0x1453f3c, 0x1453f40, 0x1453f44, 0x1453f48, 0x1453f4c,
    0x1453f50, 0x1453f54, 0x1453f58, 0x1453f5c, 0x1453f60, 0x1453f64, 0x1453f68
};
namespace EA {
namespace Audio {
class ResponseCurve_s00a4_3d30
{
public:
    ResponseCurve_s00a4_3d30();                                            // 0x00a1aa50
    ~ResponseCurve_s00a4_3d30();
    bool InitFromConfiguration(void* pConfiguration, unsigned int name);   // 0x00a1a9d0
    float GetOutputValue(float value);                          // 0x00a1a110

    void* mpData;                   // +0x00
    char mPad_04[0x0c];             // +0x04
    void* mpAllocation;             // +0x10
    char mPad_14[0x04];             // +0x14
};
}
}
namespace EA {
namespace Audio {
ResponseCurve_s00a4_3d30::~ResponseCurve_s00a4_3d30()
{
    if (mpData && mpData != mpAllocation)
        operator delete(mpData);
}
}
}
class IConfiguration_s00a4_3d30
{
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual bool GetString(unsigned int name, unsigned int* pOut);      // +0x20
    virtual bool GetProperty(unsigned int name, void* pOut);            // +0x24
    virtual void v28();
    virtual bool GetInt(unsigned int name, int* pOut);                  // +0x2c
    virtual bool GetFloat(unsigned int name, float* pOut);              // +0x30
    virtual void v34();
    virtual bool GetUInt(unsigned int name, unsigned int* pOut);        // +0x38
};
struct CurveData
{
    bool mbEnabled;         // +0x00
    bool mbFlag1;           // +0x01
    bool mbFlag2;           // +0x02
    char mPad_03[0x01];     // +0x03
    float mf04;             // +0x04  max distance
    float mf08;             // +0x08  min distance
    float mf0c;             // +0x0c  output
    float mf10;             // +0x10  gain
    int mn14;               // +0x14
    int mn18;               // +0x18
    int mn1c;               // +0x1c
    unsigned int mn20;      // +0x20  sound name
    unsigned int mn24;      // +0x24
    int mn28;               // +0x28  sound handle
    int mn2c;               // +0x2c
    int mn30;               // +0x30  instance handle
    char mPad_34[0x08];     // +0x34
    int mn3c;               // +0x3c  play mode
};
struct SoundInstance
{
    char mPad_00[0x14];
    int mnHandle;           // +0x14
};
namespace EA {
namespace Audio {
float GetCurrentVolume();       // 0x00a41fc0
}
}
// ---- items of slice s00a43d30 end

// ---- items of slice s00a459d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl EASTL_deallocate(void* p);   // 0x00f47380
extern "C" void __fastcall Base_System_ctor(void*);                    // 0x00a33600
extern "C" void __fastcall Sub_44fc0(void*, void*, void*);             // 0x00a44fc0
extern "C" void __fastcall Sub_43c90(void*, void*, void*);             // 0x00a43c90
extern "C" void __fastcall Sub_42fe0(void*, void*, void*);             // 0x00a42fe0
extern "C" void __fastcall SystemDtor_Destroy(void*);                  // 0x00a32550
extern "C" void __cdecl    Msg_RemoveHandler(int, int, int, int, int); // 0x00571db0
extern char DAT_01453e60[], DAT_01453eac[], DAT_01454028[], DAT_01454014[];
extern char DAT_01453fc8[], DAT_01453fb4[], DAT_01452a18[], DAT_01667bac[];
extern char DAT_01667bae[], DAT_01403934[], DAT_0145433c[];
extern float DAT_0166f130, DAT_0166f134, DAT_0166f138, DAT_013eb960;
extern float DAT_01485720, DAT_01470f1c;
class RefC {
public:
    virtual void AddRef();       // +0x00
    virtual void Release();      // +0x04
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void M14();          // +0x14
};
class Holder {
public:
    char  pad[0x5c];
    RefC* mp;                    // +0x5c
    void  Set(RefC* p);          // @ 0xa45cb0
};
struct VMNode { unsigned key; unsigned val; VMNode* next; };   // eastl pair node: key, value, next
extern VMNode* gEmptyBucketArray[2];   // 0x154df28
void* operator new(unsigned, const char*, int, int, int, int);         // 0x00f473a0
static inline void VCall0(void* p, int off) {
    typedef void (__thiscall *F)(void*);
    (*(F*)(*(char**)p + off))(p);
}
static inline void VCallN(void* p, int off, int a) {
    typedef void (__thiscall *F)(void*, int);
    (*(F*)(*(char**)p + off))(p, a);
}
struct ASys {
    ASys();
    ~ASys();
    char m_pad[0x15bf58];
};
// ---- items of slice s00a459d0 end

// @ 0x00a41ed0
namespace SP { namespace Audio {
cSound::cSound()
: mStartContext(0), mb2ba4(0), mb2ba5(0)
{
}
}}  // namespace SP::Audio

// @ 0x00a41fc0
double FUN_00a41fc0()
{
    LARGE_INTEGER li;
    if (!(gTimerFlags & 1)) {
        gTimerFlags |= 1;
        QueryPerformanceCounter(&li);
        gStart = li;
    }
    if (!(gTimerFlags & 2)) {
        gTimerFlags |= 2;
        unsigned __int64 freq = GetStopwatchFrequency();
        gSecondsPerTick = 1.0 / (double)freq;
    }
    QueryPerformanceCounter(&li);
    return (double)(li.QuadPart - gStart.QuadPart) * gSecondsPerTick;
}

// @ 0x00a42190
SP::Audio::cEmitterModelSound* ConstructcEmitterModelSound()
{
    SP::Audio::cEmitterModelSound* p = new SP::Audio::cEmitterModelSound();
    return p ? (SP::Audio::cEmitterModelSound*)((char*)p + 4) : 0;
}

// @ 0x00a42200
namespace SP {
namespace Audio {
unsigned int StaticConvertSymbolToId(char const * name)
{
    return EA::Audio::GetSystemAT()->SymbolToId(name);
}
}
}  // namespace SP::Audio

// @ 0x00a42220
bool SP::Audio::cAudioSystem::PreInit(void* pCommandLine)
{
    EA::CommandLine_s00a4_1c40* pCmd = (EA::CommandLine_s00a4_1c40*)pCommandLine;
    FUN_00a3cdb0();
    if (pCmd->FindSwitch(L"noSound", false, 0, 0) != (unsigned int)-1)
        return false;
    if (pCmd->FindSwitch(L"nofocus", false, 0, 0) != (unsigned int)-1)
        mbNoFocus = false;
    unsigned int desc[3];
    desc[0] = 0xe611314a;
    desc[1] = 0x2b9f662;
    desc[2] = 0x21407ee;
    if (GetManager()->V58(desc) == 0)
        return false;
    FUN_00a3cea0();
    gFn1675f58 = (void*)&FUN_00a37680;
    return true;
}

// @ 0x00a422c0
namespace SP { namespace Audio {
void cSystem_s00a4_1c40::SetupContext()
{
    cAudioSystem* pEngine = Engine();
    pEngine->V38(0x44888b0);
    pEngine->V40(0x34753a0, 1);
    pEngine->V58();
    mn30c = 0x14;
}
}}  // namespace SP::Audio

// @ 0x00a42310
void SP::Audio::cSystem::SetupTypePriorities()
{
    ((cTypeMapHolder*)this)->SetTypePriority(0x3055f61, 0);
    ((cTypeMapHolder*)this)->SetTypePriority(0x2b9f662, 1);
    ((cTypeMapHolder*)this)->SetTypePriority(0x1a527db, 2);
    ((cTypeMapHolder*)this)->SetTypePriority(0x22d2c83, 3);
}

// @ 0x00a423a0
int SP::Audio::cAudioSystem::ResolveCurve(CurveDesc* d)
{
    unsigned int magic = d->m3c;
    if (magic == 0xa852cbd1)
        return 5;
    if (d->m02 != 0)
        return 5;
    switch (d->m30) {
    case 0:
    case 4:
        d->m34 = mn15bc88;
        d->m38 = mn15bc98;
        break;
    case 1:
    case 5:
    case 6:
    case 7:
        d->m34 = mn15bc84;
        d->m38 = mn15bc94;
        break;
    default:
        return 1;
    }
    switch (magic) {
    case 0x20681cd4: d->m40 = mn15bc8c; d->m44 = mn15bc9c; break;
    case 0x6f394b77: d->m40 = mn15bc90; d->m44 = mn15bca0; break;
    default: d->m40 = 0; d->m44 = 0xffffffff; break;
    }
    if (d->m28 < d->m2c && d->m34 < d->m38 && d->m40 < d->m44)
        return 5;
    if (d->m01 != 0)
        return 3;
    if (d->m28 >= d->m2c && d->m24 == 0xee8347b0)
        return 2;
    return 4;
}

// @ 0x00a424b0
void SP::Audio::cAudioSystem::ResetCurveIds()
{
    Map_26530();
    mn15bc84 = 0;
    mn15bc88 = 0;
    mn15bc8c = 0;
    mn15bc90 = 0;
}

// @ 0x00a424e0
bool SP::Audio::cAudioSystem::UpdateAndTestRunTimePolyphonyForSound(void* pSound, int count)
{
    SoundObj* snd = (SoundObj*)pSound;
    if (snd->FUN_00a1b3f0())
        return true;
    unsigned int diff = (unsigned int)(V15c(snd->V44(count)) - count);
    unsigned int q = snd->FUN_00a1ad70();
    unsigned int* p2 = 0;
    unsigned int limit2;
    if (snd->FUN_00a1ad90() == 0x20681cd4) {
        p2 = (unsigned int*)&mn15bc8c;
        limit2 = (unsigned int)mn15bc9c;
    } else if (snd->FUN_00a1ad90() == 0x6f394b77) {
        p2 = (unsigned int*)&mn15bc90;
        limit2 = (unsigned int)mn15bca0;
    }
    unsigned int limit1;
    unsigned int* p1 = 0;
    if (!snd->V20(-1, 0)) {
        switch (snd->FUN_00a1ad80()) {
        case 0:
        case 4:
            limit1 = (unsigned int)mn15bc98;
            p1 = (unsigned int*)&mn15bc88;
            break;
        case 1:
        case 5:
        case 6:
        case 7:
            limit1 = (unsigned int)mn15bc94;
            p1 = (unsigned int*)&mn15bc84;
            break;
        default:
            limit1 = (unsigned int)count;
            break;
        }
    } else {
        limit1 = (unsigned int)count;
    }
    if (count >= 0) {
        if (diff >= q)
            return false;
        if (p1 && *p1 >= limit1)
            return false;
        if (p2 && *p2 >= limit2)
            return false;
    }
    if (count != 0) {
        if (p1)
            *p1 += snd->FUN_00a1ada0() * count;
        if (p2)
            *p2 += count;
    }
    return true;
}

// @ 0x00a42640
bool SP::Audio::cAudioSystem::GetProperty(unsigned int id, float* out)
{
    bool result = true;
    if (id != 0x5ac702f0)
        result = false;
    else
        *out = (float)mb15bc40;
    return result;
}

// @ 0x00a42670
bool __stdcall CreateSound(cSound** ppOut)
{
    if (ppOut == 0)
        return false;
    cSound* p = new cSound();
    *ppOut = p;
    ((SoundInit*)p)->V00();
    return true;
}

// @ 0x00a426f0
void SP::Audio::cAudioSystem::SetCurrentContext(void* ctx)
{
    mpCurrentContext = ctx;
    V38(0x43390fd);
    V40(0x433911b, (int)ctx);
    V58();
}

// @ 0x00a42740
int SP::Audio::cAudioSystem::GetContextId()
{
    return mn15bc3c;
}

// @ 0x00a42750
void SP::Audio::cAudioSystem::GetListenerVectors(Vector3* a, Vector3* b, Vector3* c, Vector3* d)
{
    if (a)
        *a = mV44;
    if (b)
        *b = mV50;
    if (c)
        *c = mV5c;
    if (d)
        *d = mV68;
}

// @ 0x00a427e0
void SP::Audio::cAudioSystem::RegisterModules()
{
    RegisterBuiltInModules();
    if (mpA4) {
        ((RwAudioSystem*)mpA4)->GetVoiceList()->RegisterBuiltIn();
        ((RwAudioSystem*)mpA4)->GetDecoderRegistry()->RegisterBuiltInPlugIns();
    }
}

// @ 0x00a42830
bool FUN_00a42830()
{
    EA::Audio::Eapd::Debug::EapdObj* obj = EA::Audio::Eapd::Debug::ObjectError();
    if (obj) {
        EA::Audio::Eapd::Debug::EapdEvent ev(0x22d2c83);
        obj->V70(0, &ev);
    }
    return obj != 0;
}

// @ 0x00a429a0
void SP::Audio::cAudioSystem::CommandResolve(void* pCommand)
{
    Command_s00a4_1c40* cmd = (Command_s00a4_1c40*)pCommand;
    if (cmd->Type() != 0x3475365)
        return;
    if (!cmd->SetT(0x347537e, 0, 0))
        return;
    char* s = cmd->GetString8(0x347537e);
    if (!s || s[0] != 'f' || s[1] != 'o' || s[2] != 'o' || s[3] != 't')
        return;
    if (!mp15bcec)
        return;
    float a, b, c;
    cmd->GetBool(0x3475391, &a);
    cmd->GetBool(0x3475395, &b);
    cmd->GetBool(0x3475398, &c);
    float tmp[3];
    tmp[0] = a;
    tmp[1] = b;
    tmp[2] = c;
    unsigned int r = ((EventMod*)mp15bcec)->V08(tmp);
    cmd->SetUint64(0x39fa376, r);
}

// @ 0x00a42aa0
bool SP::Audio::cAudioSystem::OnEventModifier(void* pCommand)
{
    if (mp15bc78)
        return ((cEventModifier_s00a4_1c40*)mp15bc78)->ModifyEvent((Command_s00a4_1c40*)pCommand);
}

// @ 0x00a42ad0
float SP::Audio::cAudioSystem::GetDistance(Vector3* p)
{
    if (!mb15bbf0)
        return 0.0f;
    if (mb15bc42) {
        float len = sqrtf(mCameraPos.x * mCameraPos.x + mCameraPos.y * mCameraPos.y
                          + mCameraPos.z * mCameraPos.z);
        float px = p->x;
        float py = p->y;
        float pz = p->z;
        float sq = px * px + py * py + pz * pz + kEpsilon;
        float inv = 1.0f / sqrtf(sq);
        float dx = mCameraPos.x - px * inv * len;
        float dy = mCameraPos.y - py * inv * len;
        float dz = mCameraPos.z - pz * inv * len;
        return sqrtf(dx * dx + dy * dy + dz * dz);
    }
    float dx = mCameraPos.x - p->x;
    float dy = mCameraPos.y - p->y;
    float dz = mCameraPos.z - p->z;
    return sqrtf(dx * dx + dy * dy + dz * dz);
}

// @ 0x00a42c10
bool SP::Audio::cAudioSystem::RegisterHandler(unsigned int index, void* obj)
{
    if (mp60)
        return ((HandlerTable*)mp60)->Register(index, obj);
    return false;
}

// @ 0x00a42c30
bool SP::Audio::cAudioSystem::UnregisterHandler(unsigned int index)
{
    if (mp60)
        return ((HandlerTable*)mp60)->Unregister(index);
    return false;
}

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

// @ 0x00a43d30
bool cSystem_s00a4_3d30::Init(EA::CommandLine_s00a4_3d30* pCommandLine)
{
    cAudioSystem_s00a4_3d30* pAudioSystem = GetAudioSystem(this);
    wchar_t appPath[0x104];
    EA::IO::FilePath filePath;
    filePath.Set(pCommandLine->at(0)->mpBegin);
    filePath.GetDriveAndDirectory(appPath, 0x104);
    EA::IO::EnsureTrailingPathSeparator(appPath, -1);

    wchar_t* pEnd = appPath;
    while (*pEnd)
        ++pEnd;
    mAppDir.assign(appPath, pEnd);

    if (pCommandLine->FindSwitch(L"nosamplecache", false, 0, 0) != (unsigned int)-1)
        pAudioSystem->mbNoSampleCache = true;
    if (pCommandLine->FindSwitch(L"verboseaudio", false, 0, 0) != (unsigned int)-1)
        pAudioSystem->mbVerboseAudio = true;

    bool bHaveChannelMode = false;
    cProperty* pProperty = 0;
    if (gpAppPreferences && gpAppPreferences->GetProperty(0x49d4c74d, &pProperty) &&
        pProperty->mnType == 0x0a) {
        unsigned int nChannelMode = *pProperty->GetUInt();
        float fMode;
        if (nChannelMode == 4)
            fMode = 2.0f;
        else if (nChannelMode == 5)
            fMode = 3.0f;
        else
            fMode = 1.0f;
        pAudioSystem->ConfigureSpeakerMode(0x435b383, fMode);
        bHaveChannelMode = true;
    }
    if (!bHaveChannelMode) {
        float fMode;
        if (pCommandLine->FindSwitch(L"mono", false, 0, 0) != (unsigned int)-1)
            fMode = 0.0f;
        else if (pCommandLine->FindSwitch(L"stereo", false, 0, 0) != (unsigned int)-1)
            fMode = 1.0f;
        else if (pCommandLine->FindSwitch(L"quad", false, 0, 0) != (unsigned int)-1)
            fMode = 2.0f;
        else if (pCommandLine->FindSwitch(L"surround", false, 0, 0) != (unsigned int)-1)
            fMode = 3.0f;
        else
            goto noChannelMode;
        pAudioSystem->ConfigureSpeakerMode(0x435b383, fMode);
    }
noChannelMode:

    if (pCommandLine->FindSwitch(L"silent", false, 0, 0) != (unsigned int)-1)
        pAudioSystem->mbSilent = true;

    pAudioSystem->mnSampleRate = GetConfigManager()->GetValue(0x7d8ed666);

    if (gpAppPreferences && gpAppPreferences->GetProperty(0x899eb157, &pProperty) &&
        pProperty->mnType == 1)
        pAudioSystem->mbPropertyBool = *pProperty->GetBool();

    if (!pAudioSystem->Init())
        return false;

    PublishAudioSystem(pAudioSystem);

    EA::Messaging::Server_s00a4_3d30* pServer = EA::Messaging::GetServer();
    mMessageReg.mpServer = pServer;
    mMessageReg.mpHandler = (EA::Messaging::IHandler_s00a4_3d30*)&pAudioSystem->mHandler;
    mMessageReg.mpIDArray = kanAudioMessageIDs;
    mMessageReg.mnIDCount = 15;
    mMessageReg.mnPriority = 0;
    if (pServer && mMessageReg.mpHandler) {
        for (unsigned int i = 0; i < 15; ++i)
            pServer->AddHandler(mMessageReg.mpHandler, kanAudioMessageIDs[i]);
    }

    mpCache = new ("Audio") AudioCache;
    mpCache->Initialize();

    if (pCommandLine->FindSwitch(L"nodefaultvox", false, 0, 0) != (unsigned int)-1)
        SetGlobalProperty(0x5ac702f0, 0.0f);

    mpPreferences = new ("Audio") cAudioPreferences;
    mpPreferences->Init();

    GetModelManager()->SetListener(&pAudioSystem->mSystem.mModelListener);
    return true;
}

// @ 0x00a441b0
void Eapd_s00a4_3d30::Remove(unsigned int name)
{
    unsigned int key = name;
    GroupMap::iterator it = mGroups.find(&key);
    if (!mGroups.isEnd(it)) {
        GroupMap::Node* pNode = it.mpNode;
        if (pNode->mpGroup) {
            ReleaseGroupRef(pNode->mpGroup, 0);
            AudioAT* pAudioAT = EA::Audio::GetSystemAT_s00a4_3d30();
            if (pAudioAT)
                pAudioAT->SetGroupActive(pNode->mpGroup);
        }
        mGroups.erase(it);
    }
}

// @ 0x00a44230
void Eapd_s00a4_3d30::SetListener(const EapdGroupParam* pGroup)
{
    unsigned int key = (unsigned int)pGroup;
    GroupMap::iterator it = mGroups.find(&key);
    if (!mGroups.isEnd(it)) {
        EA::Audio::AudioSetListener3(it.mpNode->mpGroup, pGroup->mPosition.x,
                                     pGroup->mPosition.y, pGroup->mPosition.z);
    }
}

// @ 0x00a44290
float Eapd_s00a4_3d30::GetCurveValue(unsigned int name)
{
    SoundMap::iterator it = mCurves.find(&name);
    if (mCurves.isEnd(it))
        return 0.0f;

    SoundMap::Node* pNode = it.mpNode;
    if (!pNode->mpConfig)
        return 0.0f;

    float* pValues;
    int nValues;
    if (!SP::GetPropertyAsFloatArray(pNode->mpConfig, 0xe888e2af, &pValues, &nValues))
        return 0.0f;

    double dIntPart;
    double dFraction = modf((EA::Audio::GetCurrentVolume() - pNode->mf10) * pNode->mf18,
                            &dIntPart);
    int nIndex = (int)dIntPart;

    float fValue;
    if (nIndex < nValues - 1)
        fValue = (float)(pValues[nIndex] +
                         (pValues[nIndex + 1] - pValues[nIndex]) * dFraction);
    else
        fValue = pValues[nValues - 1];

    if (pNode->mf20 != 0.0f)
        fValue = pNode->mf20 * fValue;
    if (pNode->mf1c != 0.0f)
        fValue = (float)pow(fValue, pNode->mf1c);
    return fValue;
}

// @ 0x00a443c0
SoundMap::iterator SoundMap::erase(iterator position)
{
    Node* pNode = position.mpNode;
    iterator result;
    result.mpBucket = position.mpBucket;
    result.mpNode = pNode->mpNext;
    while (!result.mpNode) {
        ++result.mpBucket;
        result.mpNode = *result.mpBucket;
    }

    if (*position.mpBucket == pNode) {
        *position.mpBucket = pNode->mpNext;
    } else {
        Node* pPrev = *position.mpBucket;
        while (pPrev->mpNext != pNode)
            pPrev = pPrev->mpNext;
        pPrev->mpNext = pNode->mpNext;
    }

    if (pNode->mpConfig)
        pNode->mpConfig->Release();
    operator delete(pNode);
    --mnElementCount;
    return result;
}

// @ 0x00a44440
bool cAudioSystem_s00a4_3d30::ShutdownSystem()
{
    cAudioSystem_s00a4_3d30* pAudioSystem = GetAudioSystem(&mSystem);

    if (GetModelManager())
        GetModelManager()->ClearListener(&pAudioSystem->mSystem.mModelListener);

    if (mSystem.mMessageReg.mpServer) {
        EA::Messaging::Server_s00a4_3d30* pServer = mSystem.mMessageReg.mpServer;
        EA::Messaging::RemoveHandler(pServer, mSystem.mMessageReg.mpHandler,
                                     mSystem.mMessageReg.mpIDArray,
                                     mSystem.mMessageReg.mnIDCount,
                                     mSystem.mMessageReg.mnPriority);
        mSystem.mMessageReg.mpServer = 0;
    }

    if (mSystem.mpCache) {
        mSystem.mpCache->Stop();
        mSystem.mpCache = 0;
    }

    CheatManager* pCheats = GetCheatManager();
    if (pCheats) {
        pCheats->Execute(gpCheatInvulnerable);
        pCheats->Execute(gpCheatAllPowerups);
        pCheats->Execute(gpCheatUsermusic);
    }

    if (mSystem.mpGroupList) {
        mSystem.mpGroupList->v0c();
        mSystem.mpGroupList = 0;
    }

    mSystem.mpGroupHandle = 0;

    mSystem.mPlaying.clear();

    Sys::Shutdown();

    if (gpAudioSystem)
        gpAudioSystem->mHandler.v0c();
    gpAudioSystem = 0;
    return true;
}

// @ 0x00a445a0
bool cAudioSystem_s00a4_3d30::InitCurve(void* pCurveData, int nDefault, int nCurve, void* pConfiguration, const Vector3* pPosition)
{
    CurveData* pCurve = (CurveData*)pCurveData;
    IConfiguration_s00a4_3d30* pConfig = (IConfiguration_s00a4_3d30*)pConfiguration;
    pCurve->mn14 = nDefault;
    pCurve->mn18 = nCurve;
    pConfig->GetProperty(0x12d2a4d4, &pCurve->mbEnabled);
    pConfig->GetProperty(0x6dd08218, &pCurve->mbFlag1);
    pConfig->GetProperty(0xba134192, &pCurve->mbFlag2);

    if (pCurve->mbEnabled) {
        if (!pConfig->GetFloat(0xf616b72, &pCurve->mf08))
            return false;
        if (!pConfig->GetFloat(0x3593710, &pCurve->mf04))
            return false;
        if (!pPosition)
            return false;

        int nListener = 0;
        pConfig->GetInt(0xed1f36d5, &nListener);
        Vector3* pListenerPos = EA::Audio::GetSystemAT_s00a4_3d30()->GetListener(nListener);

        float dx = pPosition->x - pListenerPos->x;
        float dy = pPosition->y - pListenerPos->y;
        float dz = pPosition->z - pListenerPos->z;
        float fDistanceSq = dx * dx + dy * dy + dz * dz;
        float fDistance = fabs(sqrt(fDistanceSq));

        if (!pCurve->mbFlag1 && fDistance > pCurve->mf04)
            return false;

        float fGain = 1.0f;
        pConfig->GetFloat(0x2406a047, &fGain);
        float fOutputScale = 1.0f;
        pConfig->GetFloat(0x25df0108, &fOutputScale);

        float fValue;
        if (pCurve->mf08 > fDistance || fGain == 0.0f) {
            fValue = 1.0f;
        } else if (fDistance > pCurve->mf04) {
            fValue = 0.0f;
        } else {
            EA::Audio::ResponseCurve_s00a4_3d30 response;
            response.InitFromConfiguration(pConfig, 0x1e4db1eb);
            fValue = response.GetOutputValue((fDistance - pCurve->mf08) /
                                             (pCurve->mf04 - pCurve->mf08));
        }
        pCurve->mf0c = fValue * fOutputScale;
    }

    pCurve->mf10 = 1.0f;
    pConfig->GetFloat(0x393f7f7d, &pCurve->mf10);
    pCurve->mn1c = 1;
    pConfig->GetInt(0xd9ec19d6, &pCurve->mn1c);
    pCurve->mn24 = 0xee8347b0;
    pConfig->GetUInt(0x7f28acc, &pCurve->mn24);
    pCurve->mn28 = GetSoundFromHandle(nDefault, 0);
    pCurve->mn2c = 2;
    pConfig->GetInt(0xbaf7f4f9, &pCurve->mn2c);
    pConfig->GetInt(0x51997db2, &pCurve->mn3c);
    if (pCurve->mn3c == 0) {
        unsigned int nDefinition = 0;
        if (GetSoundDefinition(pCurve->mn14, &nDefinition) && nDefinition == 0x22d2c83)
            pCurve->mn3c = 0xa852cbd1;
    }
    pConfig->GetUInt(0x701ed91e, &pCurve->mn20);
    if (pCurve->mn20 == 0)
        pCurve->mn20 = nDefault;
    pCurve->mn30 = -1;
    if (pCurve->mn3c != 0xa852cbd1) {
        unsigned int key[3];
        key[0] = pCurve->mn20;
        key[1] = 0x3055f61;
        key[2] = 0x21407ee;
        int nInstance = 0;
        if (FindSoundInstance(key, &nInstance)) {
            void* pInstance = 0;
            if (GetSoundInstance(key, &pInstance))
                pCurve->mn30 = ((SoundInstance*)pInstance)->mnHandle;
        } else {
            pCurve->mn30 = StartSoundDefinition(pCurve->mn20);
        }
    }
    return true;
}

// @ 0x00a449a0
void Eapd_s00a4_3d30::Play(const EapdGroupParam* pGroup)
{
    unsigned int key = (unsigned int)pGroup;
    GroupMap::iterator it = mGroups.find(&key);
    if (!mGroups.isEnd(it))
        return;

    unsigned int nSoundName = 0;
    if (!pGroup || !pGroup->mpConfig)
        return;
    if (!pGroup->mpConfig->GetString(0x4a5b8d2, &nSoundName))
        return;

    void* pSound = (void*)(unsigned int)*GetSoundHandle(nSoundName);
    int nVoice = 0;
    AudioAT* pAudioAT = EA::Audio::GetSystemAT_s00a4_3d30();
    if (pAudioAT)
        nVoice = pAudioAT->GetVoiceHandle();
    Start3dSoundByName(pSound, nVoice, pGroup->mPosition.x, pGroup->mPosition.y,
                       pGroup->mPosition.z);

    Playing playing;
    playing.mpGroup = (void*)pGroup;
    playing.mpSound = pSound;
    playing.mnVoice = nVoice;
    mGroups.insertPlaying(playing, false);
}

// @ 0x00a44a80
void Eapd_s00a4_3d30::PlayOrStop(const EapdGroupParam* pGroup, bool bStart)
{
    unsigned int key = (unsigned int)pGroup;
    GroupMap::iterator it = mGroups.find(&key);
    if (!bStart) {
        if (!mGroups.isEnd(it)) {
            GroupMap::Node* pNode = it.mpNode;
            if (pNode->mpGroup) {
                ReleaseGroupRef(pNode->mpGroup, 0);
                AudioAT* pAudioAT = EA::Audio::GetSystemAT_s00a4_3d30();
                if (pAudioAT)
                    pAudioAT->SetGroupActive(pNode->mpGroup);
            }
            mGroups.erase(it);
        }
        return;
    }

    if (!mGroups.isEnd(it))
        return;

    unsigned int nSoundName = 0;
    if (!pGroup || !pGroup->mpConfig)
        return;
    if (!pGroup->mpConfig->GetString(0x4a5b8d2, &nSoundName))
        return;

    void* pSound = (void*)(unsigned int)*GetSoundHandle(nSoundName);
    int nVoice = GetPlaybackHandle();

    Playing playing;
    playing.mpGroup = (void*)pGroup;
    playing.mpSound = pSound;
    playing.mnVoice = nVoice;
    mGroups.insert(playing);

    Start3dSoundByName(pSound, nVoice, pGroup->mPosition.x, pGroup->mPosition.y,
                       pGroup->mPosition.z);
}

// @ 0x00a44bb0
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
        void* p = FUN_0092b1d0(tmp);
        mObj15bc14.o04((int)p);
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

// @ 0x00a44e80
void cSystem::FUN_00a44e80(uint32 key)
{
    HashTable& t = mTable320;
    Iterator it;
    t.hashFind(&it, &key);
    if (it.mpNode == t.mpBucketArray[t.mnBucketCount]) {
        SoundMapValue v;
        v.mKey     = key;
        v.mField08 = 0;
        v.mField10 = 0.0;
        v.mField18 = g_fSoundMapRate;
        v.mField1c = 0.0f;
        v.mField20 = 0.0f;
        v.mpObject = 0;
        t.insert(&it, &v, key & 0xffffff00);
        if (v.mpObject)
            v.mpObject->Release();
    }
}

// @ 0x00a44f70
void cSystem::FUN_00a44f70(int key)
{
    HashTable& t = mTable15bf38;
    Iterator it;
    t.hashFind(&it, &key);
    if (it.mpNode != t.mpBucketArray[t.mnBucketCount]) {
        it = t.erase(it);
    }
}

// @ 0x00a44fc0
void* FixedHashtable::ctor(int a, int b)
{
    FixedPoolBase pool;
    pool.mpHead = 0;
    pool.init((char*)this + 0x8c, 0x140, 0x10, 4, 0);
    pool.mpBlock    = (char*)this + 0x8c;
    pool.mpBlockEnd = (char*)this + 0x1cc;
    pool.mNodeSize  = 0x10;
    pool.mpOwner    = (char*)this + 0x34;
    int bucketCount = FUN_00921340(0x15);
    hashtableCtor(bucketCount, a, &b, &b, b, &b, &pool);
    m10 = 0x461c4000;   // 10000.0f
    m14 = 0x40000000;   // 2.0f
    m18 = 0;
    PrimeRehashPolicy policy;
    policy.mfMaxLoadFactor = 10000.0f;
    policy.mfGrowthFactor  = 2.0f;
    policy.mnNextResize    = 0;
    uint32 n = policy.GetBucketCount((uint32)m0c);
    if ((uint32)m08 < n) erase((int)n);
    return this;
}

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

// @ 0x00a45130
bool cSystem::FUN_00a45130()
{
    if (!FUN_00a31170(this)) return false;

    ResKeyList list;
    list.mpBegin = 0; list.mpEnd = 0; list.mpCapEnd = 0;

    ResKey key;
    key.id    = 0x1402ee0;
    key.group = g_resourceGroupId;
    key.extra = 0;

    EA_ResourceMan_Manager* mgr = (EA_ResourceMan_Manager*)EA_ResourceMan_GetManager();
    mgr->r38(&list, &key, 0);

    for (ResKey* p = list.mpBegin; p != list.mpEnd; ++p)
        this->AddSymbolList(p->id);

    RefCounted4* em = (RefCounted4*)operator_new6(0x38, "Audio", 0, 0, 0, 0);
    if (em) em = (RefCounted4*)SP_ConstructcEmitterSndPlayer(em);
    RefCounted4* oldEm = (RefCounted4*)mpEventModifier;
    if (em != oldEm) {
        if (em) em->AddRef();
        mpEventModifier = (RefCounted*)em;
        if (oldEm) oldEm->Release();
    }
    cEventModifier_Init(mpEventModifier);

    // register the three emitter constructors in the symbol table
    uint32 ids[3] = { 0x1a527db, 0x22d2c83, 0x7c05b331 };
    uint32 fns[3] = { 0xa420d0, 0xa42130, 0xa42190 };
    for (int i = 0; i < 3; i++) {
        Iterator it;
        mSymbolTable.find(&it, &ids[i]);
        if (it.mpNode == mSymbolTable.mpBucketArray[mSymbolTable.mnBucketCount]) {
            uint32 kv[2] = { ids[i], 0 };
            mSymbolTable.insertSymbol(&it, kv, false);
        }
        *(uint32*)((char*)it.mpNode + 4) = fns[i];
    }

    VoiceManager* vm = (VoiceManager*)operator_new6(0x2c, "Audio", 0, 0, 0, 0);
    if (vm) vm = (VoiceManager*)SPAudioVoiceManagerEAPD_ctor(vm);
    VoiceManager* oldVm = (VoiceManager*)mp15bc80;
    if (vm != oldVm) {
        if (vm) vm->AddRef();
        mp15bc80 = (RefCounted*)vm;
        if (oldVm) oldVm->Release();
    }
    FUN_00a466d0(mp15bc80);

    SoundConfig cfg;
    cfg.m00 = 0x80;
    cfg.m04 = 0x400;
    cfg.m08 = 0x80;
    cfg.m0c = 0x100;
    cfg.m10 = 0x100;
    cfg.m14 = 0x2000;
    cfg.m18 = 1;
    cfg.m1c = 0;
    cfg.m20 = 1;
    cfg.m24 = 0x20;
    cfg.m28 = mp15bc80;
    cfg.m2c = 0;
    cfg.m30 = (void*)0xa42200;      // StaticConvertSymbolToId
    cfg.m34 = 0;
    cfg.m38 = 0;
    cfg.m3c = 0;
    bool ok = FUN_00a68e90(&mField15bc34, cfg) != 0;

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
            if (res) {
                res->mpVtbl = (void*)0x1453ee0;
                res->mRefCount = 0;
            }
            ResourceObj* oldRes = (ResourceObj*)mp15bc7c;
            if (res != oldRes) {
                if (res) {
                    typedef void (__thiscall *Fn)(void*);
                    Fn add = *(Fn*)((char*)res->mpVtbl + 4);
                    add(res);
                }
                mp15bc7c = (RefCounted*)res;
                if (oldRes) {
                    typedef void (__thiscall *Fn)(void*);
                    Fn rel = *(Fn*)((char*)oldRes->mpVtbl + 8);
                    rel(oldRes);
                }
            }
            Eapd_Debug_ObjectError()->d44(1, mp15bc7c, 0);

            DatagramSocketObj* sock = (DatagramSocketObj*)operator_new6(0x84, "Audio", 0, 0, 0, 0);
            if (sock) sock = (DatagramSocketObj*)UTF_Sockets_Sockets_ctor(sock);
            DatagramSocketObj* oldSock = (DatagramSocketObj*)mpSocket15bce0;
            if (sock != oldSock) {
                if (sock) sock->mSub.s00();
                mpSocket15bce0 = (RefCounted*)sock;
                if (oldSock) oldSock->mSub.s04();
            }
            ((DatagramSocketObj*)mpSocket15bce0)->mSub.s24();

            if (list.mpBegin) {
                AllocBlockHeader* hdr = (AllocBlockHeader*)list.mpBegin - 1;
                if (hdr->mRefCount != 0)
                    operator_delete(list.mpBegin);
            }
            return true;
        }
    }
    if (list.mpBegin) {
        AllocBlockHeader* hdr = (AllocBlockHeader*)list.mpBegin - 1;
        if (hdr->mRefCount != 0)
            operator_delete(list.mpBegin);
    }
    return false;
}

// @ 0x00a45610
void cSystem::FUN_00a45610(int a, int b)
{
    HashTable& t = mTable15bf38;
    Iterator it;
    t.hashFind(&it, &a);
    Node15bf38* node = (Node15bf38*)it.mpNode;
    if (node != (Node15bf38*)t.mpBucketArray[t.mnBucketCount]) {
        node->mValue08 = b;
        node->mTimestamp10 = FUN_00a41fc0();
        int keybuf[3];
        keybuf[0] = node->mValue08;
        keybuf[1] = 0xb1b104;
        keybuf[2] = 0x61ad433;
        DbgObject* dbg = Eapd_Debug_ObjectError();
        NodeObject* old = node->mpObject;
        if (old) {
            node->mpObject = 0;
            old->Release();
        }
        bool ok = dbg->CreateObject(keybuf, (void**)&node->mpObject, 0, 0, 0, 0);
        if (!ok) {
            FUN_00a44f70(a);
        } else {
            uint32 n = 0x46;
            PropertyValue* prop = 0;
            if (node->mpObject &&
                node->mpObject->GetProperty(0x332c289d, (void**)&prop) &&
                prop->mType == 10)
                n = *prop->GetUInt();
            float f = (float)n;
            node->mField18 = 1.0f / (f * 0.001f);
            if (node->mpObject &&
                node->mpObject->GetProperty(0xf61ba344, (void**)&prop) &&
                prop->mType == 0xd)
                node->mField1c = *prop->GetFloat();
            if (node->mpObject &&
                node->mpObject->GetProperty(0xce5935c5, (void**)&prop) &&
                prop->mType == 0xd)
                node->mField20 = *prop->GetFloat();
        }
    }
}

// @ 0x00a45780
void cSystem::DoCommandMainThread(void* cmdRaw)
{
    Command* cmd = (Command*)cmdRaw;
    uint32 type = cmd->Type();
    if (type == 0x3a0fcce) {
        uint32 key;
        if (cmd->GetUint32(0x3475385, &key)) {
            HashTable& t = mTable15bf38;
            Iterator it;
            t.hashFind(&it, &key);
            if (it.mpNode != t.mpBucketArray[t.mnBucketCount]) {
                uint32 sub, val;
                cmd->GetUint32(0x3a0fce5, &sub);
                cmd->GetUint32(0x39e3c9f, &val);
                if (sub == 0x3a0fd6e) {
                    FUN_00a44f70((int)key);
                } else if (sub == 0x617208b) {
                    FUN_00a45610((int)key, (int)val);
                    SysDoCommandMainThread(cmdRaw);
                    return;
                }
            }
        }
    } else if (type == 0x40fdf2f) {
        cEapdMessage msg;
        msg.mCommand = 0;
        Server* srv = EA_Messaging_GetServer();
        if (srv) {
            if (msg.Init(cmd)) {
                srv->s14(0x41638ca, &msg, 0);
                SysDoCommandMainThread(cmdRaw);
                return;
            }
        }
    }
    SysDoCommandMainThread(cmdRaw);
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

// @ 0x00a459d0
ASys::ASys()
{
    char* s = (char*)this;
    Base_System_ctor(this);
    *(void**)(s + 0x15bc18) = DAT_01453e60;
    *(void**)(s + 0x15bc1c) = DAT_01453eac;
    *(void**)(s + 0x00)      = DAT_01454028;
    *(void**)(s + 0x04)      = DAT_01454014;
    *(void**)(s + 0x15bc18) = DAT_01453fc8;
    *(void**)(s + 0x15bc1c) = DAT_01453fb4;
    *(unsigned*)(s + 0x15bc20) = 0;
    *(unsigned*)(s + 0x15bc24) = 0;
    *(unsigned*)(s + 0x15bc28) = 0;
    *(unsigned*)(s + 0x15bc2c) = 0;
    *(unsigned*)(s + 0x15bc30) = 0;
    *(void**)(s + 0x15bc34) = DAT_01452a18;
    *(unsigned*)(s + 0x15bc38) = 0;
    *(unsigned*)(s + 0x15bc3c) = 0;
    *(unsigned char*)(s + 0x15bc40) = 1;
    *(unsigned char*)(s + 0x15bc41) = 1;
    *(unsigned char*)(s + 0x15bc42) = 0;
    *(float*)(s + 0x15bc44) = DAT_0166f130;
    *(float*)(s + 0x15bc48) = DAT_0166f134;
    *(float*)(s + 0x15bc4c) = DAT_0166f138;
    *(float*)(s + 0x15bc50) = DAT_0166f130;
    *(float*)(s + 0x15bc54) = DAT_0166f134;
    *(float*)(s + 0x15bc58) = DAT_0166f138;
    *(float*)(s + 0x15bc5c) = DAT_0166f130;
    *(float*)(s + 0x15bc60) = DAT_0166f134;
    *(float*)(s + 0x15bc64) = DAT_0166f138;
    *(float*)(s + 0x15bc68) = DAT_0166f130;
    *(float*)(s + 0x15bc6c) = DAT_0166f134;
    *(float*)(s + 0x15bc70) = DAT_0166f138;
    *(unsigned*)(s + 0x15bc74) = 0;
    *(unsigned*)(s + 0x15bc78) = 0;
    *(unsigned*)(s + 0x15bc7c) = 0;
    *(unsigned*)(s + 0x15bc80) = 0;
    *(float*)(s + 0x15bcd8) = 0.0f;
    *(unsigned*)(s + 0x15bc84) = 0;
    *(unsigned*)(s + 0x15bc88) = 0;
    *(unsigned*)(s + 0x15bc8c) = 0;
    *(unsigned*)(s + 0x15bc90) = 0;
    *(unsigned*)(s + 0x15bc94) = 0xffffffffu;
    *(unsigned*)(s + 0x15bc98) = 0xffffffffu;
    *(unsigned*)(s + 0x15bc9c) = 0xffffffffu;
    *(unsigned*)(s + 0x15bca0) = 0xffffffffu;
    *(float*)(s + 0x15bcdc) = DAT_013eb960;
    *(unsigned*)(s + 0x15bce0) = 0;
    *(unsigned*)(s + 0x15bce4) = 0;
    *(unsigned*)(s + 0x15bce8) = 0;
    *(unsigned*)(s + 0x15bcec) = 0;
    {
        char tmp;
        Sub_44fc0(s + 0x15bcf0, &tmp, &tmp);
    }
    *(unsigned*)(s + 0x15bf24) = 0;
    *(void**)(s + 0x15bf28) = DAT_01667bac;
    *(void**)(s + 0x15bf2c) = DAT_01667bac;
    *(void**)(s + 0x15bf30) = DAT_01667bae;
    *(float*)(s + 0x15bf48) = DAT_01485720;
    *(float*)(s + 0x15bf4c) = DAT_01470f1c;
    *(unsigned*)(s + 0x15bf44) = 0;
    *(unsigned*)(s + 0x15bf50) = 0;
    *(unsigned*)(s + 0x15bf40) = 1;
    *(void**)(s + 0x15bf3c) = (void*)gEmptyBucketArray;
}

// @ 0x00a45cb0
void Holder::Set(RefC* p)
{
    RefC* old = mp;
    if (p != old) {
        if (p)
            p->AddRef();
        mp = p;
        if (old)
            old->Release();
    }
    if (mp)
        mp->M14();
}

// @ 0x00a45d10
ASys::~ASys()
{
    char* s = (char*)this;
    Sub_43c90(s + 0x15bf38, *(void**)(s + 0x15bf3c), (void*)*(unsigned*)(s + 0x15bf40));
    *(unsigned*)(s + 0x15bf44) = 0;
    if (*(unsigned*)(s + 0x15bf40) > 1)
        EASTL_deallocate(*(void**)(s + 0x15bf3c));
    int nBegin = *(int*)(s + 0x15bf28);
    if (((*(int*)(s + 0x15bf30) - nBegin) & 0xfffffffe) > 2 && nBegin != 0)
        EASTL_deallocate((void*)nBegin);
    Sub_42fe0(s + 0x15bcf0, *(void**)(s + 0x15bcf4), (void*)*(unsigned*)(s + 0x15bcf8));
    void* d = *(void**)(s + 0x15bcf4);
    *(unsigned*)(s + 0x15bcfc) = 0;
    if (*(unsigned*)(s + 0x15bcf8) > 1 && d != *(void**)(s + 0x15bd20)) {
        if (d < *(void**)(s + 0x15bd14) || *(void**)(s + 0x15bd18) <= d) {
            EASTL_deallocate(d);
        } else {
            *(void**)d = *(void**)(s + 0x15bd0c);
            *(void**)(s + 0x15bd0c) = d;
        }
    }
    if (*(void**)(s + 0x15bcec))
        VCall0(*(void**)(s + 0x15bcec), 4);
    if (*(void**)(s + 0x15bce8))
        VCall0(*(void**)(s + 0x15bce8), 8);
    {
        void* r = *(void**)(s + 0x15bce4);
        if (r) {
            int c = *(int*)((char*)r + 4) - 1;
            *(int*)((char*)r + 4) = c;
            if (c == 0) {
                *(int*)((char*)r + 4) = 1;
                VCallN(r, 0, 1);
            }
        }
    }
    {
        void* q = *(void**)(s + 0x15bce0);
        if (q)
            VCall0(*(void**)((char*)q + 8), 4);
    }
    if (*(void**)(s + 0x15bc80))
        VCall0(*(void**)(s + 0x15bc80), 0x28);
    if (*(void**)(s + 0x15bc7c))
        VCall0(*(void**)(s + 0x15bc7c), 8);
    if (*(void**)(s + 0x15bc78))
        VCall0(*(void**)(s + 0x15bc78), 8);
    if (*(void**)(s + 0x15bc74))
        VCall0(*(void**)(s + 0x15bc74), 4);
    *(void**)(s + 0x15bc34) = DAT_01403934;
    {
        int h = *(int*)(s + 0x15bc20);
        if (h) {
            *(unsigned*)(s + 0x15bc20) = 0;
            Msg_RemoveHandler(h, *(int*)(s + 0x15bc24), *(int*)(s + 0x15bc28),
                              *(int*)(s + 0x15bc2c), *(int*)(s + 0x15bc30));
        }
    }
    SystemDtor_Destroy(this);
}

// @ 0x00a45f30
extern "C" void* __cdecl AudioSystem_Create()
{
    ASys* o = new("Audio", 0, 0, 0, 0) ASys;
    if (!o)
        return 0;
    return (void*)((char*)o + 0x15bc18);
}
