// src/game/SPGonzago/SPRelationshipSimulator.cpp -- migrated from slice(s) s0135d100, s00d06710, s00d058a0, s00d04750, s00d03860, s00d026d0, s00d01f50, s00d00ee0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPRelationshipSimulator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cRelationshipManager.h"
#include "SP/cGameNounManager.h"
#include "SP/cStarManager.h"
#include "SP/cVarListSerializer.h"
#include "SP/cEmpire.h"
#include "SP/cTerrainSphere.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  __cdecl EaFree(void* p);                                     // 0x00f47380
extern "C" void* __cdecl MemCopyThunk(void* d, const void* s, unsigned n);    // 0x011e0744
extern "C" void  __cdecl WriteUint32(void* stream, const uint32_t* v, int count, int endian); // 0x0093aa70
extern "C" void  __cdecl NormalizePair(uint32_t* a, uint32_t* b);             // 0x00d009a0
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
extern char kVarListDescB[];   // 0x01581f50
extern char kEmptyStr[];         // 0x01667bac
extern char vtbl_UI_BehaviorMessage[];   // 0x013eb90c
extern char vtbl_SlotMessage[];          // 0x013eb844
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(memcpy)
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(fabs)

// ---- items of slice s00d00ee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl EaFree(void* p);                                     // 0x00f47380
extern "C" void* __cdecl MemCopyThunk(void* d, const void* s, unsigned n);    // 0x011e0744
extern "C" void  __cdecl WriteUint32(void* stream, const uint32_t* v, int count, int endian); // 0x0093aa70
extern "C" void  __cdecl NormalizePair(uint32_t* a, uint32_t* b);             // 0x00d009a0
struct IStream {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual void* GetRaw();               // slot 6 (+0x18)
};
struct ISerializer {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual void EndRecord();             // slot 7 (+0x1c)
    virtual IStream* GetStream();         // slot 8 (+0x20)
};
struct cVarListSerializer {
    char buf[0xa00];
    cVarListSerializer(const void* list, const void* desc, uint32_t id);  // 0x00692f90
    void Serialize(ISerializer* s);                                       // 0x00692900
};
extern char kVarListDescB[];   // 0x01581f50
inline void PutU32(ISerializer* ser, uint32_t value)
{
    IStream* st = ser->GetStream();
    uint32_t tmp = value;
    void* raw = st->GetRaw();
    WriteUint32(raw, &tmp, 1, 0);
}
struct RBNode { RBNode* right; RBNode* left; RBNode* parent; uint8_t color; uint8_t pad[3]; };
struct RelData { float value; union { uint32_t flags; struct { uint8_t bit0 : 1; uint8_t bit1 : 1; }; }; uint32_t pad[4]; };      // 0x18
struct RelValue { uint32_t k0, k1; RelData data; };                    // 0x20
struct Iter {
    RBNode* node;
    Iter() {}
    Iter(RBNode* n) { node = n; }
    Iter(const Iter& o) { node = o.node; }
};
struct InsRes {
    Iter it; bool inserted;
    InsRes() {}
    InsRes(const Iter& i, bool b) : it(i) { inserted = b; }
    InsRes(const InsRes& o) : it(o.it) { inserted = o.inserted; }
};
struct TrueTag {};
struct RelTree {
    uint32_t alloc; RBNode anchor; uint32_t size;
    __declspec(noinline) RBNode** find(RBNode** out, const uint32_t* key);                                   // 0x00d00f80
    __declspec(noinline) Iter InsertImpl(RBNode* parent, const RelValue* value, bool forceLeft);             // 0x00d012a0
    __declspec(noinline) InsRes Insert(const RelValue* value, TrueTag tag);                                  // 0x00d01340
    __declspec(noinline) Iter InsertHint(Iter hint, const RelValue* value, TrueTag tag);                     // 0x00d01920
};
struct Noun {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
    virtual uint32_t GetID();    // slot 19 (+0x4c)
    char pad[0x80];
    uint32_t mId;                // +0x84
    char pad2[1];
    uint8_t mFlag89;             // +0x89
    void NotifyOther(Noun* o);   // 0x00c32830
    void Finish();               // 0x00c31c50
    float GetPower();            // 0x00c31990
};
extern char kEmptyStr[];         // 0x01667bac
struct String {
    char* b; char* e; char* c;
    String() { b = kEmptyStr; e = kEmptyStr; c = kEmptyStr + 1; }
    __forceinline String(const char* p) {
        b = 0; e = 0; c = 0;
        unsigned n = 0;
        while (p[n]) ++n;
        RangeInitialize(n + 1);
        char* d = b;
        MemCopyThunk(d, p, n);
        e = d + n;
        *d = 0;
    }
    ~String() { if ((c - b) > 1 && b) EaFree(b); }
    String& sprintf(const char* fmt, ...);        // 0x00472fe0 (cdecl, this pushed)
    void assign(const char* f, const char* l);    // 0x00454cb0
    void RangeInitialize(unsigned n);             // 0x00475ab0
};
struct cGameNounManager {
    Noun* GetPlayerCivilization();                 // 0x00b25fb0
    void* GetNoun(uint32_t id);                    // 0x00b20790
    String UpdateDebugUI(void* noun);              // 0x00b20ee0
};
cGameNounManager* NounManager();                   // 0x00b3d300
Noun* GetPlayerEmpire();                           // 0x01021300
struct IMessageServer {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void Post(uint32_t type, void* msg, int arg);   // slot 5 (+0x14)
};
namespace EA {
namespace Messaging {
 IMessageServer* GetServer(); 
}  // 0x00883860
}
extern char vtbl_UI_BehaviorMessage[];   // 0x013eb90c
extern char vtbl_SlotMessage[];          // 0x013eb844
struct BehaviorMsg {
    const void* vptr; volatile long refCount; uint32_t slot0; uint32_t padA; uint32_t slot1; uint32_t body[7]; uint32_t arg; uint32_t padB; uint32_t mask; uint32_t padC;
    void Destruct();                         // 0x00421cf0
};
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
struct Tuning { float base, scale, lo, hi, pad, asym; };    // asym at +0x14
struct RecItem { uint32_t key; RelTree tree; uint32_t pad; };   // 0x20
struct RelBook {
    char pad0[0x24];
    RelTree mEmpty;                 // +0x24
    char pad1[0x9c - 0x24 - sizeof(RelTree)];
    RecItem* mBegin;                // +0x9c
    RecItem* mEnd;                  // +0xa0
    char pad2[0xb0 - 0xa4];
    uint8_t mFlag;                  // +0xb0

    __declspec(noinline) RelTree* A1ab0(uint32_t a, uint32_t b);
    __declspec(noinline) bool  A1b50(uint32_t a, uint32_t b);
    __declspec(noinline) float A1b80(uint32_t a, uint32_t b, uint32_t key);
    __declspec(noinline) String A1bb0(uint32_t a, uint32_t b);
    __declspec(noinline) String A1db0(Noun* a, Noun* b);
    __declspec(noinline) void  A1e30(Noun* a, Noun* b);
    __declspec(noinline) bool A1f20(uint32_t a, uint32_t b);
    float GetRel(uint32_t a, uint32_t b, int flag);   // 0x00d00a10
    __declspec(noinline) RelData* FindRel(RelTree* t, uint32_t a, uint32_t b);  // 0x00d01410 (this unused)
    __declspec(noinline) float FindRelFeedback(RelTree* t, uint32_t a, uint32_t b, uint32_t key);    // 0x00d01470
    __declspec(noinline) float FindRelScaled(RelTree* t, uint32_t a, uint32_t b, uint32_t key, Tuning* p); // 0x00d015d0
};
struct RelWriter {
    char pad[0x90];
    char* mBegin;   // +0x90
    char* mEnd;     // +0x94
    __declspec(noinline) void A14e0(ISerializer* ser);
};
__declspec(noinline) void __cdecl WriteVarMap(ISerializer* ser, RelTree* t);
// ---- items of slice s00d00ee0 end

// ---- items of slice s00d01f50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" const wchar_t g_emptyW[1] = { 0 };
typedef unsigned int   u32;
typedef unsigned char  u8;
typedef          int   s32;
struct cEmpire {
  u32 pad000[33];                  // 0x000 .. 0x083
  u32 f84;                         // 0x084 empire id
};
struct cRelObj {
  u32 pad00;                       // 0x000
  bool bit0 : 1;                   // 0x004 flag bit 0
  bool bit1 : 1;                   // 0x004 flag bit 1
  u32  rest : 30;                  // 0x004 remaining flag bits
};
struct cRelObj32 {
  u32 pad00;                       // 0x000
  u32 f04;                         // 0x004
};
struct cRelationshipManager {
  u32  FUN_00d01ab0(u32 a, u32 b, u32 c, u32 d);   // 0x00d01ab0
  void* FUN_00d01410(u32 x);                       // 0x00d01410
  float FUN_00d01470(u32 x, u32 kind);             // 0x00d01470
};
cEmpire* __cdecl GetPlayerEmpire_s00d0_1f50();                // 0x01021300
struct cTerrainSphere {
  u32 FUN_00c75420();                            // 0x00c75420
};
struct cNounManager {
  cTerrainSphere* GetCurrentTerrainSphere();     // 0x00f67d90
};
cNounManager* __cdecl NounManager_s00d0_1f50();             // 0x00b3d300
struct cRel {
  virtual void v00();                            // 0x00
  virtual void v04();                            // 0x04
  virtual void v08();                            // 0x08
  virtual void v0c();                            // 0x0c
  virtual void v10();                            // 0x10
  virtual void v14();                            // 0x14
  virtual void v18();                            // 0x18
  virtual void v1c();                            // 0x1c
  virtual void v20();                            // 0x20
  virtual void v24();                            // 0x24
  virtual void v28();                            // 0x28
  virtual void v2c();                            // 0x2c
  virtual void v30();                            // 0x30
  virtual void v34();                            // 0x34
  virtual void v38();                            // 0x38
  virtual void v3c();                            // 0x3c
  virtual void v40();                            // 0x40
  virtual void v44();                            // 0x44
  virtual void v48();                            // 0x48
  virtual void* v4c();                           // 0x4c
  u8  pad04[0x85];                               // 0x04 .. 0x88
  u8  f89;                                       // 0x89
  u8  f8a;                                       // 0x8a
  s32 FUN_00bf0f40();                            // 0x00bf0f40
};
void __cdecl FUN_00d009a0(void** a, void** b);   // 0x00d009a0
extern "C" float g_relNeg2 = -2.0f;
extern "C" float g_relNeg1 = -1.0f;
extern "C" float g_rel1    =  1.0f;
extern "C" float g_rel2    =  2.0f;
extern "C" float g_rel3    =  3.0f;
extern "C" float g_rel4    =  4.0f;
struct cWString {
  const wchar_t* mpBegin;                        // 0x00
  const wchar_t* mpEnd;                          // 0x04
  const wchar_t* mpCapacity;                     // 0x08
  void RangeInitialize(const wchar_t* p);        // 0x00579a90
  void CopyConstruct(const cWString& src);       // 0x0056e2d0
};
void __cdecl ConvertToString16(cWString* out, const char* src, int len);  // 0x0093c5a0
void __cdecl FreeStringBuffer(void* p);                                   // 0x00f47380
static void FreeWString(cWString* s)
{
  if (s->mpBegin != 0 &&
      ((u32)((const char*)s->mpEnd - (const char*)s->mpBegin) & 0xfffffffeu) > 2)
    FreeStringBuffer((void*)s->mpBegin);
}
struct cCmdCtx {
  virtual void v00(const wchar_t* s);            // 0x00
  virtual void v04(const wchar_t* s);            // 0x04
};
struct cTree;
void* __cdecl RBTreeIncrement(void* node);       // 0x00921580
u8    __cdecl FUN_00ac8050(void* ctx, u32 a, void* node);   // 0x00ac8050
u8    __cdecl FUN_00acabe0(void* ctx, u32 a, void* node,
                            const wchar_t* type);           // 0x00acabe0
void  __cdecl EA_IO_ReadInt32(void* stream, void* dst, u32 count, u32 flag); // 0x0093a780
struct cTree {
  u32 pad000;                                    // 0x00
  void* head;                                    // 0x04
  void* root;                                    // 0x08
  u32 count;                                     // 0x0c
  u8  pad10;                                     // 0x10
  u8  pad11[3];                                  // 0x11
  u32 f14;                                       // 0x14
  void DoNukeSubtree(void* node);                // 0x009a9600
  void FUN_00ba8420(void* out, void* in, u32 flag);  // 0x00ba8420
};
struct cStreamInner {
  virtual void v00();                            // 0x00
  virtual void v04();                            // 0x04
  virtual void v08();                            // 0x08
  virtual void v0c();                            // 0x0c
  virtual void v10();                            // 0x10
  virtual void v14();                            // 0x14
  virtual void* v18();                           // 0x18
};
struct cStream {
  virtual void v00();                            // 0x00
  virtual void v04();                            // 0x04
  virtual void v08();                            // 0x08
  virtual void v0c();                            // 0x0c
  virtual void v10();                            // 0x10
  virtual void v14();                            // 0x14
  virtual void v18();                            // 0x18
  virtual void v1c();                            // 0x1c  (separator)
  virtual cStreamInner* v20();                   // 0x20
};
struct cWorldIn {
  float value;                                   // 0x00
  u8    flag;                                    // 0x04
  u8    pad05[3];                                // 0x05
  u32   id;                                      // 0x08
  u32   pad0c;                                   // 0x0c
};
struct cWorldOut {
  u32   pad00;                                   // 0x00
  u32   pad04;                                   // 0x04
  void* node;                                    // 0x08
  u8    added;                                   // 0x0c
  u8    pad0d[3];                                // 0x0d
};
// ---- items of slice s00d01f50 end

// ---- items of slice s00d026d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IdVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    void reserve(int n);                          // FUN_00d01790
    void DoInsertValue(uint32_t* pos, const uint32_t& v);  // FUN_00b96600
    void push_back(const uint32_t& v) {
        if (mpEnd < mpCapacity) { uint32_t* p = mpEnd++; if (p) *p = v; }
        else DoInsertValue(mpEnd, v);
    }
};
extern IdVec gRelationshipEvents;  // 0x169d410
// ---- items of slice s00d026d0 end

// ---- items of slice s00d03860 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
namespace SP {
struct tRelNode;
}
namespace SP {
struct tRelSub {
    uint32_t   mSecond;                                 // +0x00 (entry +0x04)
    uint8_t    pad004[0x04];                            // +0x04 .. +0x07
    uint32_t   mValue;                                  // +0x08 (entry +0x0c)
    tRelNode*  mpNode;                                  // +0x0c (entry +0x10)

    void FUN_00d03b10(tRelNode* pNode);
};
}
namespace SP {
struct tRelEntry {
    uint32_t mId;                                       // +0x00
    tRelSub  mSub;                                      // +0x04
    uint32_t mPad014;                                   // +0x14
    uint32_t mPad018;                                   // +0x18
    uint32_t mPad01c;                                   // +0x1c
};
}
namespace SP {
struct tRelChild {
    uint32_t   mId;                                     // +0x00
    tRelChild* mpNext;                                  // +0x04
};
}
namespace SP {
struct tRelChainSub {
    uint8_t pad000[0x0c];                               // +0x00 .. +0x0b

    void DoNukeSubtree(uint32_t id);                     // 0x009a9600
};
}
namespace SP {
struct tRelNode {
    tRelNode*     mpFirst;                              // +0x00
    tRelNode*     mpNext;                               // +0x04
    uint8_t       pad008[0x18];                         // +0x08 .. +0x1f
    tRelChainSub  mSub;                                 // +0x20
    tRelChild*    mpChildList;                          // +0x2c
};
}
// ---- items of slice s00d03860 end

// ---- items of slice s00d04750 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Sub04 {
  uint8_t mData[0x0c];                                   // +0x04 .. +0x0f
  void FUN_00d03b10(void* arg);                          // 0x00d03b10 (ecx=this, stack arg)
  void FUN_00d048a0(void* src);                          // 0x00d048a0 (ecx=this, stack arg)
};
struct Elem20 {                                          // 0x20-byte vector element
  int      mKey;        // +0x00
  Sub04    mSub;        // +0x04
  void*    mField10;    // +0x10
  uint8_t  mTail[0x0c]; // +0x14 .. +0x1f
};
struct Pair { uint32_t mKey; };                          // key/value pair passed to vec ops
Elem20* FUN_00d04f90(void* a, Elem20* end, void* b);      // 0x00d04f90 (cdecl)
Elem20* FUN_00d01210(Elem20* begin, Elem20* end, Pair* key, uint8_t flag); // 0x00d01210 (cdecl)
struct Vec20 {
  Elem20*  mpBegin;     // +0x00
  Elem20*  mpEnd;       // +0x04
  Elem20*  mpCap;       // +0x08
  uint32_t mField0c;    // +0x0c
  uint32_t mField10;    // +0x10
  uint8_t  mField14;    // +0x14

  int   FUN_00d051e0(void* a1, void* a2);                // 0x00d051e0
  void  FUN_00d05240(Elem20* pos, Pair* value);          // 0x00d05240
  Elem20* FUN_00d05380(Elem20* pos, Pair* value);        // 0x00d05380
  int   FUN_00d05560(Pair* key);                         // 0x00d05560
};
struct RefCountHeader { int mCount; };                   // mCount at -4 from the object
// ---- items of slice s00d04750 end

// ---- items of slice s00d058a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cRelationshipManager_s00d0_58a0 {
public:
    int  RecordEvent(int event);                                       // 0x00d05d90
    void RecordEvent(int a1, int a2, int a3, float weight);            // 0x00d06240
    void RecordFoughtEnemyEvent();  // 0x00d06270 (SP::cRelationshipManager::RecordFoughtEnemyEvent)
    int  CalculateRelationshipAbsolute();  // 0x00d05a20 (SP::cRelationshipManager::CalculateRelationshipAbsolute)
    void FUN_00d058a0();
    void FUN_00d06030();
    void FUN_00d06400();
    void FUN_00d064b0();
    void FUN_00d065a0();
};
}
// ---- items of slice s00d058a0 end

// ---- items of slice s00d06710 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cRefCounted {
public:
    virtual void r00();                                  // +0x00 add reference
    virtual void Release();                              // +0x04
    virtual void Destroy();                              // +0x08
};
}
namespace SP {
class cCountedSlot {
public:
    void* volatile          mpVtbl;                      // +0x00
    cRefCounted*            mpField4;                    // +0x04
    cRefCounted* volatile   mpField8;                    // +0x08

    cCountedSlot* FUN_00d06eb0(cRefCounted* p);
    void*         FUN_00d070b0(uint32_t flags);

    void FUN_00d06a50(int value);                        // 0x00d06a50
    void FUN_00d06c30(int first, int value);
};
}
// ---- items of slice s00d06710 end

// ---- items of slice s0135d100 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void fn_00692ca0();
extern "C" void fn_00b1fbf0();
extern "C" void fn_00c2e4e0();
extern "C" void fn_00692fb0();
extern "C" void fn_00d022e0();
extern "C" void fn_00d04aa0();
extern "C" void fn_00d00ff0();
extern "C" void fn_00d00c00();
extern "C" void fn_00d03a40();
extern "C" void fn_00c761c0();
extern "C" void fn_00eafe40();
typedef void (__cdecl *fp)();
struct T {
    const char* name;
    unsigned hash;
    int off;
    int p3, p4, p5;
    int z0, z1;
    fp f[7];
    T() {}
    T(const char* n, unsigned h, int o, fp f0, fp f1, fp f2, fp f3,
      fp f4, fp f5, fp f6)
        : name(n), hash(h), z0(0), z1(0) {
        f[0] = f0; f[1] = f1; f[2] = f2; f[3] = f3;
        f[4] = f4; f[5] = f5; f[6] = f6;
        off = o;
    }
};
extern T g_01581f50, g_01581f8c;
// ---- items of slice s0135d100 end

// @ 0x00d01210
extern "C" int* __cdecl Fd01210(int* first, int* last, int* value)
{
    int n = (int)((char*)last - (char*)first) >> 5;
    if (n > 0) {
        unsigned v = *(unsigned*)value;
        do {
            int half = n >> 1;
            int* mid = (int*)((char*)first + (half << 5));
            if (*(unsigned*)mid < v) {
                first = (int*)((char*)mid + 0x20);
                n -= half + 1;
            } else {
                n = half;
            }
        } while (n > 0);
    }
    return first;
}

// @ 0x00d01410
RelData* RelBook::FindRel(RelTree* t, uint32_t a, uint32_t b)
{
    NormalizePair(&a, &b);
    uint32_t key[2] = { a, b };
    RBNode* it;
    t->find(&it, key);
    RelData* r = 0;
    if (it != &t->anchor)
        r = (RelData*)((char*)it + 0x18);
    return r;
}

// @ 0x00d014e0
void RelWriter::A14e0(ISerializer* ser)
{
    PutU32(ser, 0x301b5d9f);
    PutU32(ser, (uint32_t)(mEnd - mBegin) >> 5);
    char* end = mEnd;
    for (char* it = mBegin; it != end; it += 0x20) {
        PutU32(ser, *(uint32_t*)it);
        WriteVarMap(ser, (RelTree*)(it + 4));
    }
    cVarListSerializer vs((char*)this - 0xc, kVarListDescB, 0x1a80d26);
    vs.Serialize(ser);
}

// @ 0x00d01bb0
String RelBook::A1bb0(uint32_t a, uint32_t b)
{
    String result;
    cGameNounManager* nm = NounManager();
    bool same = (a == b);
    if (same) {
        String name = nm->UpdateDebugUI(nm->GetNoun(a));
        RelData* d = FindRel(A1ab0(a, b), a, b);
        if (d)
            result.sprintf("%s 0x%08x -> self = %.1f", name.b, a, (double)d->value);
        else
            result.sprintf("%s 0x%08x -> self = none", name.b, a);
        return result;
    }
    NormalizePair(&a, &b);
    String nameA = nm->UpdateDebugUI(nm->GetNoun(a));
    String nameB = nm->UpdateDebugUI(nm->GetNoun(b));
    String val;
    bool has = FindRel(A1ab0(a, b), a, b) != 0;
    if (has)
        val.sprintf("%.1f", (double)GetRel(a, b, 1));
    else
        val.assign("none", "none" + 4);
    result.sprintf("%s 0x%08x -> %s 0x%08x = %s", nameA.b, a, nameB.b, b, val.b);
    return result;
}

// @ 0x00d01db0
String RelBook::A1db0(Noun* a, Noun* b)
{
    if (a && b) {
        uint32_t ida = a->GetID();
        uint32_t idb = b->GetID();
        return A1bb0(ida, idb);
    }
    return String("");
}

// @ 0x00d01e30
void RelBook::A1e30(Noun* a, Noun* b)
{
    Noun* player = GetPlayerEmpire();
    if (b == 0)
        b = player;
    uint32_t idA = a->mId;
    uint32_t idB = b->mId;
    RelData* d = FindRel(A1ab0(idA, idB), idA, idB);
    if (d)
        d->flags &= ~2u;
    if (b != player) {
        d = FindRel(A1ab0(idB, idA), idB, idA);
        if (d)
            d->flags &= ~2u;
    }
    a->NotifyOther(b);
    b->NotifyOther(a);
    if (b == player) {
        BehaviorMsg msg;
        msg.arg = 0;
        msg.vptr = vtbl_UI_BehaviorMessage;
        _InterlockedExchange(&msg.refCount, 0);
        msg.vptr = vtbl_SlotMessage;
        msg.mask = 0;
        msg.slot0 = (uint32_t)a;
        msg.slot1 = (uint32_t)b;
        EA::Messaging::GetServer()->Post(0x4445d44, &msg, 0);
        msg.Destruct();
    }
    a->Finish();
    b->Finish();
}

// @ 0x00d01f20
bool RelBook::A1f20(uint32_t a, uint32_t b)
{
    RelData* d = FindRel(A1ab0(a, b), a, b);
    if (d)
        return d->bit0;
    return false;
}

// @ 0x00d01f50
u8 __fastcall FUN_00d01f50(cRelationshipManager* self, void* dummy, cEmpire* a, cEmpire* b)
{
  cEmpire* player = GetPlayerEmpire_s00d0_1f50();
  cEmpire* p1 = a;
  cEmpire* p2 = b;
  if (p1 == player && p2 != 0) {
    p1 = p2;
    p2 = player;
  }
  if (p2 == 0)
    p2 = player;
  u32 x = self->FUN_00d01ab0(p1->f84, p2->f84, p1->f84, p2->f84);
  cRelObj* y = (cRelObj*)self->FUN_00d01410(x);
  if (y != 0)
    return (u8)y->bit0;
  return 0;
}

// @ 0x00d01fb0
u8 __fastcall FUN_00d01fb0(cRelationshipManager* self, void* dummy, cEmpire* a, cEmpire* b)
{
  u32 x = self->FUN_00d01ab0((u32)a, (u32)b, (u32)a, (u32)b);
  cRelObj32* y = (cRelObj32*)self->FUN_00d01410(x);
  if (y != 0) {
    u8 v = (u8)(y->f04 >> 1);
    v &= 1;
    return v;
  }
  return 0;
}

// @ 0x00d01ff0
u8 __fastcall FUN_00d01ff0(cRelationshipManager* self, void* dummy, cEmpire* a, cEmpire* b)
{
  cEmpire* player = GetPlayerEmpire_s00d0_1f50();
  cEmpire* p1 = a;
  cEmpire* p2 = b;
  if (p1 == player && p2 != 0) {
    p1 = p2;
    p2 = player;
  }
  if (p2 == 0)
    p2 = player;
  u32 x = self->FUN_00d01ab0(p1->f84, p2->f84, p1->f84, p2->f84);
  cRelObj32* y = (cRelObj32*)self->FUN_00d01410(x);
  if (y != 0) {
    u8 v = (u8)(y->f04 >> 1);
    v &= 1;
    return v;
  }
  return 0;
}

// @ 0x00d02050
float __fastcall FUN_00d02050(cRelationshipManager* self, void* dummy, cRel* p1, cRel* p2)
{
  if (p1->f8a != 0) {
    void* a = p1->v4c();
    void* b = p2->v4c();
    FUN_00d009a0(&a, &b);
    float f = self->FUN_00d01470(
        self->FUN_00d01ab0((u32)a, (u32)b, (u32)a, (u32)b), 0x526e501);
    if (!(f > 0.0f)) {
      f = self->FUN_00d01470(
          self->FUN_00d01ab0((u32)a, (u32)b, (u32)a, (u32)b), 0x526e504);
      if (!(f > 0.0f))
        return g_rel3;
    }
  }
  if (p1->f8a != 0)
    return 0.0f;
  if (p2->f8a != 0)
    return 0.0f;
  float r = 0.0f;
  switch (p1->FUN_00bf0f40()) {
  case 0:
    switch (p2->FUN_00bf0f40()) {
    case 0: r = g_relNeg2; break;
    case 1: r = g_rel1; break;
    case 2: r = g_relNeg1; break;
    }
    break;
  case 1:
    switch (p2->FUN_00bf0f40()) {
    case 0: r = g_rel1; break;
    case 1: r = g_rel4; break;
    case 2: r = g_rel3; break;
    }
    break;
  case 2:
    switch (p2->FUN_00bf0f40()) {
    case 0: r = g_relNeg1; break;
    case 1: r = g_rel2; break;
    case 2: r = 0.0f; break;
    }
    break;
  }
  if (p2->f89 != 0) {
    u32 t = NounManager_s00d0_1f50()->GetCurrentTerrainSphere()->FUN_00c75420();
    if (t == 0) {
      r += g_rel2;
    } else if (t == 2) {
      r -= g_rel1;
      if (p2->FUN_00bf0f40() == 1)
        return r - g_rel1;
    }
  }
  return r;
}

// @ 0x00d022e0
u8 __cdecl FUN_00d022e0(cCmdCtx* ctx, u32 key, cTree* tree)
{
  u8 result = 1;
  if (tree->f14 == 0)
    return result;

  cWString tmp;
  if (key == 0) {
    tmp.mpBegin = 0;
    tmp.mpEnd = 0;
    tmp.mpCapacity = 0;
    tmp.RangeInitialize(0);
  } else {
    ConvertToString16(&tmp, (const char*)key, -1);
  }
  cWString str;
  str.CopyConstruct(tmp);
  FreeWString(&tmp);

  ctx->v00(str.mpBegin == str.mpEnd ? g_emptyW : str.mpBegin);

  u8 flag = 1;
  char* end = (char*)tree + 4;
  for (char* n = (char*)tree->root; n != end; n = (char*)RBTreeIncrement(n)) {
    if (flag != 0) {
      flag = 1;
      if (FUN_00ac8050(ctx, 0, n + 0x18) == 0)
        flag = 0;
    } else {
      flag = 0;
    }
  }

  ctx->v04(str.mpBegin == str.mpEnd ? g_emptyW : str.mpBegin);
  FreeWString(&str);
  return flag;
}

// @ 0x00d02440
void __cdecl FUN_00d02440(cStream* stream, cTree* tree)
{
  tree->DoNukeSubtree((void*)tree->count);
  void** head = (void**)((char*)tree + 4);
  *head = head;
  tree->root = head;
  tree->count = 0;
  tree->pad10 = 0;
  tree->f14 = 0;

  s32 count = 0;
  EA_IO_ReadInt32(stream->v20()->v18(), &count, 1, 0);

  u32 i = 0;
  while (i < (u32)count) {
    s32 id;
    EA_IO_ReadInt32(stream->v20()->v18(), &id, 1, 0);
    stream->v1c();

    s32 value;
    EA_IO_ReadInt32(stream->v20()->v18(), &value, 1, 0);
    stream->v1c();

    cWorldIn in;
    in.value = *(float*)&id;
    in.flag = 0;
    in.id = (u32)value;
    cWorldOut out;
    tree->FUN_00ba8420(&out, &in, 0);
    if (out.added == 0)
      *(float*)((char*)out.node + 0x14) = *(float*)&id;

    i++;
  }
  stream->v1c();
}

// @ 0x00d02570
u8 __cdecl FUN_00d02570(cCmdCtx* ctx, u32 key, cTree* tree)
{
  u8 result = 1;
  if (tree->f14 == 0)
    return result;

  cWString tmp;
  if (key == 0) {
    tmp.mpBegin = 0;
    tmp.mpEnd = 0;
    tmp.mpCapacity = 0;
    tmp.RangeInitialize(0);
  } else {
    ConvertToString16(&tmp, (const char*)key, -1);
  }
  cWString str;
  str.CopyConstruct(tmp);
  FreeWString(&tmp);

  ctx->v00(str.mpBegin == str.mpEnd ? g_emptyW : str.mpBegin);

  u8 flag = 1;
  char* end = (char*)tree + 4;
  for (char* n = (char*)tree->root; n != end; n = (char*)RBTreeIncrement(n)) {
    if (flag != 0) {
      FUN_00acabe0(ctx, 0, n + 0x14, L"float");
      flag = 1;
    } else {
      flag = 0;
    }
  }

  ctx->v04(str.mpBegin == str.mpEnd ? g_emptyW : str.mpBegin);
  FreeWString(&str);
  return flag;
}

// @ 0x00d026d0
IdVec* GetRelationshipEvents()
{
    uint32_t id;
    if (gRelationshipEvents.mpBegin == gRelationshipEvents.mpEnd) {
        gRelationshipEvents.reserve(0x40);
        id = 0x526e4e5; gRelationshipEvents.push_back(id);
        id = 0x526e4ee; gRelationshipEvents.push_back(id);
        id = 0x526e4f2; gRelationshipEvents.push_back(id);
        id = 0x526e4f5; gRelationshipEvents.push_back(id);
        id = 0x526e4f8; gRelationshipEvents.push_back(id);
        id = 0x526e4fb; gRelationshipEvents.push_back(id);
        id = 0x526e4fe; gRelationshipEvents.push_back(id);
        id = 0x526e501; gRelationshipEvents.push_back(id);
        id = 0x526e504; gRelationshipEvents.push_back(id);
        id = 0x526e50a; gRelationshipEvents.push_back(id);
        id = 0x526e50e; gRelationshipEvents.push_back(id);
        id = 0x526e512; gRelationshipEvents.push_back(id);
        id = 0x5adb0aa; gRelationshipEvents.push_back(id);
        id = 0x5776d99; gRelationshipEvents.push_back(id);
        id = 0x5da8036; gRelationshipEvents.push_back(id);
        id = 0x530cf00; gRelationshipEvents.push_back(id);
        id = 0x530cf01; gRelationshipEvents.push_back(id);
        id = 0x530cf02; gRelationshipEvents.push_back(id);
        id = 0x530cf03; gRelationshipEvents.push_back(id);
        id = 0x530cf04; gRelationshipEvents.push_back(id);
        id = 0x530cf05; gRelationshipEvents.push_back(id);
        id = 0x530cf06; gRelationshipEvents.push_back(id);
        id = 0x530cf07; gRelationshipEvents.push_back(id);
        id = 0x530cf08; gRelationshipEvents.push_back(id);
        id = 0x530cf09; gRelationshipEvents.push_back(id);
        id = 0x530cf0a; gRelationshipEvents.push_back(id);
        id = 0x530cf0b; gRelationshipEvents.push_back(id);
        id = 0x54eab4b3; gRelationshipEvents.push_back(id);
        id = 0x526e519; gRelationshipEvents.push_back(id);
        id = 0x526e51c; gRelationshipEvents.push_back(id);
        id = 0x526e51d; gRelationshipEvents.push_back(id);
        id = 0x526e51e; gRelationshipEvents.push_back(id);
        id = 0x526e51f; gRelationshipEvents.push_back(id);
        id = 0x526e521; gRelationshipEvents.push_back(id);
        id = 0x526e524; gRelationshipEvents.push_back(id);
        id = 0x5f8a1ad; gRelationshipEvents.push_back(id);
        id = 0x526e527; gRelationshipEvents.push_back(id);
        id = 0x526e52a; gRelationshipEvents.push_back(id);
        id = 0x667af08; gRelationshipEvents.push_back(id);
        id = 0x526e52d; gRelationshipEvents.push_back(id);
        id = 0x526e531; gRelationshipEvents.push_back(id);
        id = 0x526e535; gRelationshipEvents.push_back(id);
        id = 0x526e537; gRelationshipEvents.push_back(id);
        id = 0x526e53c; gRelationshipEvents.push_back(id);
        id = 0x526e542; gRelationshipEvents.push_back(id);
        id = 0x526e545; gRelationshipEvents.push_back(id);
        id = 0x526e56a; gRelationshipEvents.push_back(id);
        id = 0x526e5cf; gRelationshipEvents.push_back(id);
        id = 0x526e5d4; gRelationshipEvents.push_back(id);
        id = 0x526e5d8; gRelationshipEvents.push_back(id);
        id = 0x526e5dc; gRelationshipEvents.push_back(id);
        id = 0x526e5f3; gRelationshipEvents.push_back(id);
        id = 0x55165f5; gRelationshipEvents.push_back(id);
        id = 0x5590199; gRelationshipEvents.push_back(id);
        id = 0x55901b3; gRelationshipEvents.push_back(id);
        id = 0x5661a77; gRelationshipEvents.push_back(id);
        id = 0x5661a7c; gRelationshipEvents.push_back(id);
        id = 0x577909a; gRelationshipEvents.push_back(id);
        id = 0x577909b; gRelationshipEvents.push_back(id);
        id = 0x57b9100; gRelationshipEvents.push_back(id);
        id = 0x57b4514; gRelationshipEvents.push_back(id);
        id = 0x57e4fe3; gRelationshipEvents.push_back(id);
        id = 0x580e23b; gRelationshipEvents.push_back(id);
        id = 0x591f833; gRelationshipEvents.push_back(id);
        id = 0x594afff; gRelationshipEvents.push_back(id);
        id = 0x594b017; gRelationshipEvents.push_back(id);
        id = 0x5b6fcc9; gRelationshipEvents.push_back(id);
        id = 0x5b6fcd4; gRelationshipEvents.push_back(id);
        id = 0x5b942d0; gRelationshipEvents.push_back(id);
        id = 0x5b6cf09; gRelationshipEvents.push_back(id);
        id = 0x5f62736; gRelationshipEvents.push_back(id);
        id = 0x5b6ce81; gRelationshipEvents.push_back(id);
        id = 0x526e5f4; gRelationshipEvents.push_back(id);
        id = 0x5ff85b3; gRelationshipEvents.push_back(id);
        id = 0x5ff85b2; gRelationshipEvents.push_back(id);
        id = 0x601df2a; gRelationshipEvents.push_back(id);
        id = 0x68b2938; gRelationshipEvents.push_back(id);
        id = 0x68b2971; gRelationshipEvents.push_back(id);
    }
    return &gRelationshipEvents;
}

// @ 0x00d038e0
void SP::cRelationshipManager::StartPeace(SP::cEmpire * civilizationA, SP::cEmpire * civilizationB)
{
    uint32_t civilizationB_v = (uint32_t)civilizationB;
    uint32_t civilizationA_v = (uint32_t)civilizationA;
    (void)civilizationA_v;
    (void)civilizationB_v;
}

// @ 0x00d03b10
namespace SP {
void __thiscall tRelSub::FUN_00d03b10(tRelNode* pNode)
{
    while (pNode) {
        FUN_00d03b10(pNode->mpFirst);
        tRelChild* pChild = pNode->mpChildList;
        tRelNode* pNext = pNode->mpNext;
        while (pChild) {
            pNode->mSub.DoNukeSubtree(pChild->mId);
            tRelChild* pChildNext = pChild->mpNext;
            delete[] pChild;
            pChild = pChildNext;
        }
        delete[] pNode;
        pNode = pNext;
    }
}
}  // namespace SP

// @ 0x00d03b80
namespace SP {
void __cdecl GetPropertyListForPersonality(uint32_t personalityId, void* pOut)
{
    (void)personalityId;
    (void)pOut;
}
}  // namespace SP

// @ 0x00d041d0
namespace SP {
tRelEntry* __cdecl FUN_00d041d0(tRelEntry* pFirst, tRelEntry* pLast, tRelEntry* pDest)
{
    if (pFirst == pLast)
        return pDest;

    tRelEntry* pOut = pDest;
    do {
        pFirst->mSub.FUN_00d03b10(pFirst->mSub.mpNode);
        ++pFirst;
        ++pOut;
    } while (pFirst != pLast);
    return pOut;
}
}  // namespace SP

// @ 0x00d04e60
int __fastcall AddRef(RefCountHeader* p)
{
  int n = (p - 1)->mCount;
  ++n;
  (p - 1)->mCount = n;
  return n;
}

// @ 0x00d051e0
int Vec20::FUN_00d051e0(void* a1, void* a2)
{
  Elem20* e = FUN_00d04f90(a2, mpEnd, a1);
  if (e < mpEnd) {
    unsigned n = (((unsigned)((char*)mpEnd - (char*)e)) - 1 >> 5) + 1;
    Elem20* p = e;
    do {
      p->mSub.FUN_00d03b10(p->mField10);
      ++p;
    } while (--n);
  }
  int d = (int)a2 - (int)a1;
  d >>= 5;
  d = -d;
  d <<= 5;
  mpEnd = (Elem20*)((char*)mpEnd + d);
  return (int)a1;
}

// @ 0x00d05380
Elem20* Vec20::FUN_00d05380(Elem20* pos, Pair* value)
{
  Elem20* end = mpEnd;
  int idx = (int)((char*)pos - (char*)mpBegin) >> 5;
  if (pos == end && end != mpCap) {
    mpEnd = end + 1;
    if (end != 0) {
      end->mKey = value->mKey;
      end->mSub.FUN_00d048a0(value + 1);
      return mpBegin + idx;
    }
  } else {
    FUN_00d05240(pos, value);
  }
  return mpBegin + idx;
}

// @ 0x00d05560
int Vec20::FUN_00d05560(Pair* key)
{
  Elem20* end = mpEnd;
  Elem20* p = FUN_00d01210(mpBegin, end, key, mField14);
  if (p == end || key->mKey < p->mKey || p == p + 1)
    p = end;
  if (p != end) {
    if (p + 1 < end)
      FUN_00d04f90(p + 1, end, p);
    mpEnd = mpEnd - 1;
    Elem20* q = mpEnd;
    q->mSub.FUN_00d03b10(q->mField10);
    return 1;
  }
  return 0;
}

// @ 0x00d058a0
namespace SP {
void __thiscall cRelationshipManager_s00d0_58a0::FUN_00d058a0()
{
}
}  // namespace SP

// @ 0x00d05a20
float SP::cRelationshipManager::CalculateRelationshipAbsolute(unsigned int a1, unsigned int a2)
{
    return 0;
}

// @ 0x00d05d90
float SP::cRelationshipManager::RecordEvent(unsigned int event, unsigned int a2, SP::eRelationshipEvents a3, float a4)
{
    (void)event;
    return 0;
}

// @ 0x00d06030
namespace SP {
void __thiscall cRelationshipManager_s00d0_58a0::FUN_00d06030()
{
}
}  // namespace SP

// @ 0x00d06270
namespace SP {
void __thiscall cRelationshipManager_s00d0_58a0::RecordFoughtEnemyEvent()
{
}
}  // namespace SP

// @ 0x00d06400
namespace SP {
void __thiscall cRelationshipManager_s00d0_58a0::FUN_00d06400()
{
}
}  // namespace SP

// @ 0x00d064b0
namespace SP {
void __thiscall cRelationshipManager_s00d0_58a0::FUN_00d064b0()
{
}
}  // namespace SP

// @ 0x00d065a0
namespace SP {
void __thiscall cRelationshipManager_s00d0_58a0::FUN_00d065a0()
{
}
}  // namespace SP

// @ 0x00d06710
namespace SP {
void __fastcall FUN_00d06710(void* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00d068c0
namespace SP {
void __fastcall FUN_00d068c0(void* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00d06920
void SP::cRelationshipManager::StartAlliance(SP::cEmpire * pOther, SP::cEmpire * allianceId)
{
    uint32_t allianceId_v = (uint32_t)allianceId;
    (void)pOther;
    (void)allianceId_v;
}

// @ 0x00d06c30
namespace SP {
void __thiscall cCountedSlot::FUN_00d06c30(int first, int value)
{
    (void)first;
    FUN_00d06a50(value);
}
}  // namespace SP

// @ 0x013621a0
void FUN_013621a0()
{
    g_01581f50 = T("mRelationships", 0x56920bau, 0x24, fn_00692ca0, fn_00d04aa0, fn_00d00ff0, fn_00c2e4e0, fn_00692fb0, fn_00d00c00, fn_00d022e0);
    g_01581f8c = T("mEmpiresToDecayPending", 0x6538767u, 0x60, fn_00692ca0, fn_00d03a40, fn_00c761c0, fn_00c2e4e0, fn_00692fb0, fn_00b1fbf0, fn_00eafe40);
}
