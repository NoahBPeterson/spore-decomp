// src/game/SPGonzago/SPGameNounManager.cpp -- migrated from slice(s) s00b24740, s00b21e60, s00b1fd50, s00b1d870 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameNounManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.
// The slices' `typedef char va_list` (s00b1fd50, used by FormatAppend / VA_START) must win over <vadefs.h>:
// a later slice's `#include <new>` pulls <vadefs.h> in, which would redefine `va_list` as `char*` (C2040).
// Claim the guard first so <vadefs.h> leaves the slices' spelling alone.  HAND EDIT (see report_s00b21e60.md);
// rewrite.py preserves it because it keeps the other slices' blocks verbatim.
#define _VA_LIST_DEFINED

#include "game/types.h"
#include "SP/cGameNounManager.h"
#include "EA/COM/IUnknown32.h"
#include "SP/cArtilleryProjectile.h"
#include "SP/cGameData.h"
#include "EA/UTFWin/Window.h"
#include "SP/cVehicleGroupOrder.h"
#include <new>

// unnamed retail callees and globals (address in the comment)
extern void* gVtblPressureA;
extern void* gVtblPressureB;
extern void* gVtblPressureC;

// ---- items of slice s00b1d870 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
int GetCurrentGameMode();   // 0x00b5b800
int GetPlayerEmpireID();    // 0x1021090
struct cGenericPressureEvent { void ctor(); };
extern void* gVtblPressureA;
extern void* gVtblPressureB;
extern void* gVtblPressureC;
namespace UTFWin {
struct Window { bool Initialize(); };
}
// ---- items of slice s00b1d870 end

// ---- items of slice s00b1fd50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memset(void*, int, unsigned);
extern "C" void* __cdecl memmove(void*, const void*, unsigned);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
extern char gEmptyChar;  // 0x01667bac
extern void* gArtilleryVtbl;                      // 0x0145dca8
extern void* gArtVtbl0; extern void* gArtVtbl1; extern void* gArtVtbl2;
extern void* gArtVtbl3; extern void* gArtVtbl4;
extern int  __cdecl eastlCompare(const char*, const char*, unsigned n);  // 0x005f7870
extern bool __cdecl StringLess(const void*, const void*);               // 0x00812210
extern void __cdecl RangeInitialize(void* self, unsigned n);           // 0x00475ab0
extern void __cdecl DoInsertValueC(void* dst, const void* src, unsigned n);  // 0x011e0744
extern void __cdecl FormatResize(void* self, unsigned n);  // 0xb20610
#pragma intrinsic(memset, memmove, memcpy)
typedef unsigned int  uint;
typedef char          va_list;
#define ALLOC_FILE \
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
void* __cdecl opnew(unsigned size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
void  __cdecl opdel(void* p);                                                                     // 0x00f47380
#define SPORE_NEW(n) opnew((n), "Simulator", 0, 0, ALLOC_FILE, 0xd1)
struct cGameData;
struct cGameData {
    virtual int  AddRef();                 // +0x00
    virtual int  Release();                // +0x04
    virtual void gv08();                   // +0x08
    virtual int  Match(unsigned id);       // +0x0c
    virtual void gv10(); virtual void gv14(); virtual void gv18();
    virtual cGameData* gv1c();             // +0x1c
    virtual cGameData* gv20();             // +0x20
    virtual void gv24(); virtual void gv28();
    virtual bool gv2c();                   // +0x2c
    virtual void gv30(); virtual void gv34(); virtual void gv38(); virtual void gv3c();
    virtual void gv40();
    virtual void gv44();                   // +0x44
    virtual void gv48(); virtual void gv4c(); virtual void gv50(); virtual void gv54();
    virtual void gv58(); virtual void gv5c(); virtual void gv60(); virtual void gv64();   // gv64 = +0x64
    virtual void gv68(); virtual void gv6c(); virtual void gv70(); virtual void gv74();
    virtual void gv78(); virtual void gv7c(); virtual void gv80(); virtual void gv84();
    virtual void gv88(); virtual void gv8c(); virtual void gv90(); virtual void gv94();
    virtual void gv98(); virtual void gv9c(); virtual void gva0();
    virtual void gva4();                   // +0xa4
    char      pad_b58[0xb58 - 4];
    unsigned  mFlags;                      // +0xb58
};
struct IRefObject {
    virtual int   AddRef();                // +0x00
    virtual int   Release();               // +0x04
    virtual void  gv08();                  // +0x08
    virtual int   Match(unsigned id);      // +0x0c
};
struct ARCData {
    cGameData* p;
    ARCData(cGameData* q) : p(q) { if (p) p->AddRef(); }
    ARCData(const ARCData& o) : p(o.p) { if (p) p->AddRef(); }
    ~ARCData() { if (p) p->Release(); }
    ARCData& operator=(cGameData* np) {
        cGameData* old = p;
        if (np != old) { if (np) np->AddRef(); p = np; if (old) old->Release(); }
        return *this;
    }
};
struct NounMgr {
    char     pad54[0x54];
    ARCData  mAvatar;                      // +0x54
    void SetAvatar(cGameData* p);          // 0x00b1fd50
};
struct ByteString {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    char* mpField0c;    // +0x0c
    char* mpBase;       // +0x10

    void  __thiscall allocate(unsigned n);            // 0xb1ffd0
    void  __thiscall changeCapacity(unsigned n);      // 0xb230b0
    ByteString& __thiscall append(unsigned n, unsigned char c);     // 0xb1ff30
    void  __thiscall resize(unsigned n);              // 0xb20610
    void  Assign(const char* s);                      // 0x006a4380
    void  Assign(const char* b, const char* e);       // 0x00454cb0
};
struct RBNode {
    RBNode* mpNodeRight;  // +0
    RBNode* mpNodeLeft;   // +4
    RBNode* mpNodeParent; // +8
    char    mColor;       // +0xc
};
extern RBNode* __cdecl RBTreeIncrement(RBNode* p);   // 0x00921580
extern void    __cdecl RBTreeNuke(RBNode* p);        // 0x009a9600
struct RBTreeHeader {
    int     mPad;
    RBNode  mAnchor;   // +4
    uint    mnSize;    // +0x0c
    void** Find(void** out, const void* key);  // 0x00e5c780, returns `out`
};
struct ISerializer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10();
    virtual void* GetStream();          // +0x18
    virtual void* Slot1c();
    virtual void s20(); virtual void s24(); virtual void s28();
    virtual void SerializeObj(cGameData* o);  // +0x2c
};
struct GameDataBig {
    char     pad00[0x58];
    cGameData** mVecBegin;   // +0x58
    cGameData** mVecEnd;     // +0x5c
    cGameData** mVecCap;     // +0x60
    char     pad64[0x10];
    RBNode   mList;          // +0x74
    RBNode   mList2;         // +0x80
    char     pad88[0x0c];
    RBTreeHeader mFeedback;  // +0x94  (anchor +0x98)
    char     padA4[0x30];
    RBTreeHeader mFeedback2; // +0xd4

    void Write(ISerializer* ser);                    // 0xb20280
    void RemoveVecItem(cGameData* p);                // 0xb203e0
    int  CountList(cGameData* p);                    // 0xb20470
    cGameData* FindList(unsigned key);               // 0xb204d0
    void MarkFeedback(cGameData* p);                 // 0xb201a0
};
struct ListNode2 { ListNode2* next; ListNode2* prev; };
struct ListObj {
    virtual void n0(); virtual void n1(); virtual void n2(); virtual void n3();
    virtual void n4(); virtual void n5(); virtual void n6();
    virtual void n1c(void* arg);       // +0x1c
    char pad08[8];
    ListNode2 node;                    // +0x0c
};
struct SerObj { void Set(); void Set2(); void DtorBody(); };
struct GameDataDtor { void DtorBody(); };
struct ArtilleryBase {
    virtual void b0();
    char pad[0x524 - 4];
    cGameData* m524;      // +0x524
    char pad528[0x534 - 0x528];
    cGameData* m534;      // +0x534
    char pad538[4];
    cGameData* m53c;      // +0x53c
    void Dtor();          // 0xb20120
};
struct SmallObj {
    char d[0x14];
    cGameData* m14;   // +0x14
    int  m18;         // +0x18
};
struct ArtCtorObj;
struct cArtilleryProjectile {
    virtual void a0(); virtual void a4();
    char pad[0x540 - 8];
    static cArtilleryProjectile* Create();   // 0xb20660
};
struct ArtCtorObj { void Ctor(); };           // 0x00cb6ed0
struct FlushMgr {
    char pad[0xb4];
    RBNode mAnchor;    // +0xb4
    RBNode* mRoot;     // +0xc0
    char   mFlag;      // +0xc4
    void*  mC8;        // +0xc8
    void Flush();      // 0xb206d0
};
struct FeedbackMgr {
    char pad[0xd0];
    RBTreeHeader mTree;   // +0xd0
    void* GetFeedback(unsigned id);   // 0xb20750
    int   ClassifyById(unsigned id);  // 0xb20790
};
extern cGameData* __cdecl StarManager();               // 0x00b3d2a0
struct StarMgrObj { cGameData* GetEmpireByID(unsigned id); };  // 0x00ba9370 (thiscall)
struct MapStrFind {
    int mPad; RBNode mAnchor; uint mSize;
    void Find(void** out, void* key);   // 0xb20930
};
struct StringBase { void RangeInitialize(unsigned n); };   // 0x00475ab0 (thiscall)
struct String4 {
    void* ctor(void* a, void* b);   // 0xb209f0
};
struct NodeDtor { void D(); };   // 0x00a21bf0
extern int __cdecl Vsnprintf8(char* buf, unsigned n, const char* fmt, va_list args);  // 0x00938400
#define VA_START(ap, v) ((ap) = (va_list)((char*)&(v) + sizeof(v)))
struct StringC {
    void* ctor(void* a);   // 0xb20b90
};
struct StringAlloc {
    void* ctor(void* a);   // 0xb20c00
};
// ---- items of slice s00b1fd50 end

// ---- items of slice s00b21e60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void __cdecl operator_delete__(void* p);   // 0x00f47380
extern const float kFloat1, kFloat2;
extern bool __cdecl GetBoolProperty(void* p, unsigned id, bool* out);   // 0x00407190
extern bool __cdecl GetPropertyAsUint32(void* p, unsigned id, unsigned* out);   // 0x004af210
extern bool __cdecl GetFloatProperty(void* p, unsigned id, float* out);   // 0x0040cf10
extern const float kFloat1;
extern void* vtbl_UIMessageBase[];   // 0x013eb90c
extern void* vtbl_UIMessage[];   // 0x013eb844
struct IRefCount {
    virtual int AddRef();
    virtual int Release();
    virtual int Slot2();
    virtual void* Cast(unsigned id);
};
template <class T> struct ARC {
    T* p;
    ARC(T* q) : p(q) { if (p) p->AddRef(); }
    ARC(const ARC& o) : p(o.p) { if (p) p->AddRef(); }
    ~ARC() { if (p) p->Release(); }
    bool operator==(T* o) const { return p == o; }
    ARC& operator=(T* np) { T* old = p; if (old != np) { if (np) np->AddRef(); p = np; if (old) old->Release(); } return *this; }
};
struct ListNode { ListNode* next; ListNode* prev; };
struct cNoun {                       // cGameData seen through its refcount base
    virtual int AddRef();            // 0
    virtual int Release();           // 1
    virtual int Slot2();             // 2
    virtual void* Cast(unsigned id); // 3
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual int GetType();           // 8  (+0x20)
    virtual bool Init(void* desc, void* a, void* b); // 9 (+0x24)
    char pad04[8];
    ListNode node;                   // +0x0c
    char pad14[0xc];
    bool removed;                    // +0x20
    static cNoun* FromNode(ListNode* n) { return n ? (cNoun*)((char*)n - 0xc) : 0; }
};
struct NounVec {
    cNoun** begin; cNoun** end; cNoun** cap;
    void __thiscall DoInsertValue(cNoun** pos, ARC<cNoun>* v);   // 0x00aea5d0
    void push_back(ARC<cNoun>& v)
    {
        if (end < cap) {
            cNoun** p = end++;
            if (p) { *p = v.p; if (v.p) v.p->AddRef(); }
        } else {
            DoInsertValue(end, &v);
        }
    }
    void erase(cNoun** first, cNoun** last);
};
extern cNoun** __cdecl do_copy(cNoun** last, cNoun** end, cNoun** first);   // 0x006782c0
void NounVec::erase(cNoun** first, cNoun** last)
{
    cNoun** pos = do_copy(last, end, first);
    for (cNoun** q = pos; q < end; q++) if (*q) (*q)->Release();
    end -= (last - first);
}
struct StaticNounVec : NounVec {
    StaticNounVec() { begin = 0; end = 0; cap = 0; }
    ~StaticNounVec();   // 0x00ae6970
};
struct IMapFn { char d[0x1c]; void __thiscall Fn(void* other); };   // Fn: 0x00b21da0
struct cGameNounManager {
    char pad0[0x58];
    ARC<cNoun> mAvatarHerd;          // +0x58
    char pad5c[0x1c];
    ListNode mNouns;                 // +0x78
    NounVec mTempNouns;              // +0x80
    char pad8c[0xc];
    IMapFn mapA;                     // +0x98
    char mapB[0x10];                 // +0xb4
    char padc4[0x48];
    ListNode mPending;               // +0x10c

    void __thiscall FlushTemp();                  // 0xb206d0
    void __thiscall PostRemove(cNoun* n);         // 0xb20d30
    void __thiscall PostRemove2(cNoun* n);        // 0xb201a0
    cNoun* __thiscall CreateNoun(unsigned id);    // 0xb20c60
    void __thiscall RemoveNoun(cNoun* n);
    void __thiscall RemoveHerd(cNoun* herd);
    void __thiscall RemoveNounsOfType(int type);
    void __thiscall RemoveNounsWithInterface(unsigned id);
    void __thiscall Cleanup();
    void __thiscall Update();
    void __thiscall Dummy225b0();
    cNoun* __thiscall CreateAndInit(struct NounDesc* d, void* a2, void* a3, void* a4);
};
struct RawVec {
    cNoun** begin; cNoun** end; cNoun** cap;
    void __thiscall DoInsertValue(cNoun** pos, cNoun** v);   // 0x00b96600
    ~RawVec() { if (begin && ((int*)begin)[-1]) operator_delete__(begin); }
};
struct IProps;
struct NounDesc { unsigned id; int pad[2]; IProps* props; };
struct cNounData {                    // result of Cast(0x1186577)
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual void SetA(void* a);       // 14 (0x38)
    virtual void SetB(void* b);       // 15 (0x3c)
    char pad04[0x54];
    unsigned f58;                     // +0x58
    char pad5c[0x15];
    bool b71;                         // +0x71
    char pad72[0x1a];
    float f8c;                        // +0x8c
};
extern bool __cdecl GetBoolProperty(IProps* p, unsigned id, bool* out);   // 0x00407190
extern bool __cdecl GetPropertyAsUint32(IProps* p, unsigned id, unsigned* out);   // 0x004af210
extern bool __cdecl GetFloatProperty(IProps* p, unsigned id, float* out);   // 0x0040cf10
struct SPVecARC { void** begin; void** end; void** cap; void __thiscall erase(void** f, void** l); void __thiscall DoInsertValue(void** pos, void** v); };
struct VecHolder { int pad; SPVecARC vec; };
#define V4(n) virtual void n##a(); virtual void n##b(); virtual void n##c(); virtual void n##d();
struct IObj47 {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual IObj47* Cast(unsigned id);   // 3
    V4(a) V4(b) V4(c) V4(d) V4(e) V4(f) V4(g) V4(h) V4(i) V4(j)   // 4..43
    virtual void p44(); virtual void p45(); virtual void p46();
    virtual void AddRefX();              // 47 (+0xbc)
    virtual void ReleaseX();             // 48 (+0xc0)
};
struct VecHolder2 { int pad; struct { IObj47** begin; IObj47** end; IObj47** cap;
    void __thiscall DoInsertValue(IObj47** pos, IObj47** v); } vec; };
struct SysGui { void __thiscall SetSerializer(); };   // 0x00c2e4e0
struct ModelMgr {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6();
    virtual IRefCount* Lookup(unsigned id);   // 7 (+0x1c)
};
extern ModelMgr* __cdecl GetModelManager();   // 0x0067dd80
struct IPending {                       // result of Cast(0x1186577)
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12();
    virtual float f13();                // +0x34
    virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void s22(); virtual void s23(); virtual void s24();
    virtual void Apply(void* data, float f); // 25 (+0x64)
    virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
    virtual void s34(); virtual void s35();
    virtual bool HasCtx();              // 36 (+0x90)
    virtual void s37(); virtual void s38(); virtual void s39();
    virtual bool BindCtx(IRefCount* ctx); // 40 (+0xa0)
    virtual void s41(); virtual void s42();
    virtual struct PInfo* GetInfo();    // 43 (+0xac)
    char pad04[0x4c];
    unsigned flags;                     // +0x50
};
struct PInfo { int pad; unsigned f4; char pad8[0x68]; char data[1]; };  // data at +0x70
struct PNode { PNode* next; PNode* prev; IRefCount* value; };
struct UIMessage {
    void __thiscall Destruct();   // 0x00421cf0
    void** vptr; int rc; int d0; int padc; void* d1; char pad14[0x1c]; int id; char pad34[4]; int flags;
};
struct MsgServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void Post(unsigned type, UIMessage* m, int flag);   // 5 (+0x14)
};
extern MsgServer* __cdecl GetMessageServer();   // 0x0067dcc0
struct cGNM2 {
    char pad[0x80];
    NounVec mTempNouns;     // +0x80
    char pad8c[0x80];
    PNode mPending;         // +0x10c
    void __thiscall FlushTemp();   // 0x00b206d0
    void __thiscall ProcessPending();
};
// ---- items of slice s00b21e60 end

// ---- items of slice s00b24740 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace Simulator {
class cGameData_s00b2_4740;
}
namespace Simulator {
typedef cGameData_s00b2_4740* (*NounCreateFunction)();
}
namespace Simulator {
void RegisterNounType(uint32_t nounID, uint32_t typeID, const char* name);
}
namespace Simulator {
cGameData_s00b2_4740* Create_cCheatObject();  // 0xb1e550
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionFetch();  // 0xb1e580
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionHappinessEvent();  // 0xb1fc30
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionMakeAlly();  // 0xb1e5b0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cRaidPlunderEvent();  // 0xb1e5e0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cRaidEvent();  // 0xb1e610
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionColonize();  // 0xb1e640
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionEradicate();  // 0xb1e670
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionExplore();  // 0xb1e6a0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionWar();  // 0xb1e6d0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionScan();  // 0xb1e700
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionTerraform();  // 0xb1e730
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionTrade();  // 0xb1e760
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionTradeRoute();  // 0xb1e790
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionMultiDelivery();  // 0xb1e7c0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionBiosphere();  // 0xb1e7f0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cGenericPressureEvent();  // 0xb1e820
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionMultiStep();  // 0xb1e870
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionBalance();  // 0xb1e8a0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionFindAliens();  // 0xb1e8d0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionFlight101();  // 0xb1e900
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionUseTool();  // 0xb1e930
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionStory201();  // 0xb1e960
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionChangeArchetype();  // 0xb1e990
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionTrackBadge();  // 0xb1e9c0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMissionAdventure();  // 0xb1e9f0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cPlayer();  // 0xb1ea20
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMilitaryAttackCityOrder();  // 0xb23740
}
namespace Simulator {
cGameData_s00b2_4740* Create_cCulturalConvertCityOrder();  // 0xb23770
}
namespace Simulator {
cGameData_s00b2_4740* Create_cGameTerrainCursor();  // 0xb1ea50
}
namespace Simulator {
cGameData_s00b2_4740* Create_cBuildingCityHall();  // 0xb1ea80
}
namespace Simulator {
cGameData_s00b2_4740* Create_cBuildingIndustry();  // 0xb1eab0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cBuildingHouse();  // 0xb1eae0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cBuildingEntertainment();  // 0xb1eb10
}
namespace Simulator {
cGameData_s00b2_4740* Create_cBuildingScenario();  // 0xb1eb40
}
namespace Simulator {
cGameData_s00b2_4740* Create_cTurret();  // 0xb1eb70
}
namespace Simulator {
cGameData_s00b2_4740* Create_cCelestialBody();  // 0xb1eba0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cGameBundle();  // 0xb1ebd0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cCulturalTarget();  // 0xb1ec00
}
namespace Simulator {
cGameData_s00b2_4740* Create_cCity();  // 0xb1ec30
}
namespace Simulator {
cGameData_s00b2_4740* Create_cGameBundleGroundContainer();  // 0xb1ec60
}
namespace Simulator {
cGameData_s00b2_4740* Create_cVehicle();  // 0xb1ec90
}
namespace Simulator {
cGameData_s00b2_4740* Create_cVehicleGroupOrder();  // 0xb23180
}
namespace Simulator {
cGameData_s00b2_4740* Create_cCityWalls();  // 0xb1ecc0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cCityTerritory();  // 0xb1ecf0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cPlaceholderColonyEditorCursorAttachment();  // 0xb1ed20
}
namespace Simulator {
cGameData_s00b2_4740* Create_cPlanetaryArtifact();  // 0xb1ed50
}
namespace Simulator {
cGameData_s00b2_4740* Create_cToolObject();  // 0xb1ed80
}
namespace Simulator {
cGameData_s00b2_4740* Create_cCivilization();  // 0xb1edb0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cCreatureAnimal();  // 0xb1ede0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cCreatureCitizen();  // 0xb1ee10
}
namespace Simulator {
cGameData_s00b2_4740* Create_cObstacle();  // 0xb1ee40
}
namespace Simulator {
cGameData_s00b2_4740* Create_cGamePlant();  // 0xb1ee70
}
namespace Simulator {
cGameData_s00b2_4740* Create_cFruit();  // 0xb1eea0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cFruitGroup();  // 0xb1eed0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cNest();  // 0xb1ef00
}
namespace Simulator {
cGameData_s00b2_4740* Create_cHerd();  // 0xb1ef30
}
namespace Simulator {
cGameData_s00b2_4740* Create_cEgg();  // 0xb1ef60
}
namespace Simulator {
cGameData_s00b2_4740* Create_cInteractiveOrnament();  // 0xb1ef90
}
namespace Simulator {
cGameData_s00b2_4740* Create_cGameplayMarker();  // 0xb1efc0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cOrnament();  // 0xb1eff0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cAnimalTrap();  // 0xb1f020
}
namespace Simulator {
cGameData_s00b2_4740* Create_cTotemPole();  // 0xb1f050
}
namespace Simulator {
cGameData_s00b2_4740* Create_cTribeFoodMat();  // 0xb1f080
}
namespace Simulator {
cGameData_s00b2_4740* Create_cRock();  // 0xb1f0b0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cCommodityNode();  // 0xb1f0e0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMovableDestructibleOrnament();  // 0xb1f110
}
namespace Simulator {
cGameData_s00b2_4740* Create_cSolarHitSphere();  // 0xb1f140
}
namespace Simulator {
cGameData_s00b2_4740* Create_cHitSphere();  // 0xb1f170
}
namespace Simulator {
cGameData_s00b2_4740* Create_cInterCityRoad();  // 0xb1f1a0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cTribe();  // 0xb1f1d0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cTribeTool();  // 0xb1f200
}
namespace Simulator {
cGameData_s00b2_4740* Create_cSpear();  // 0xb20660
}
namespace Simulator {
cGameData_s00b2_4740* Create_cArtilleryProjectile();  // 0xb1f230
}
namespace Simulator {
cGameData_s00b2_4740* Create_cFlakProjectile();  // 0xb1f260
}
namespace Simulator {
cGameData_s00b2_4740* Create_cDefaultToolProjectile();  // 0xb1f290
}
namespace Simulator {
cGameData_s00b2_4740* Create_cDeepSpaceProjectile();  // 0xb1f2c0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cSpaceDefenseMissile();  // 0xb1f2f0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cDefaultBeamProjectile();  // 0xb1f320
}
namespace Simulator {
cGameData_s00b2_4740* Create_cDefaultAoEArea();  // 0xb1f350
}
namespace Simulator {
cGameData_s00b2_4740* Create_cCulturalProjectile();  // 0xb1f380
}
namespace Simulator {
cGameData_s00b2_4740* Create_cResourceProjectile();  // 0xb1f3b0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cICBM();  // 0xb1f3e0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cSoundLoopObject();  // 0xb1f410
}
namespace Simulator {
cGameData_s00b2_4740* Create_cRotationRing();  // 0xb1f440
}
namespace Simulator {
cGameData_s00b2_4740* Create_cRotationBall();  // 0xb1f470
}
namespace Simulator {
cGameData_s00b2_4740* Create_cMorphHandle();  // 0xb1f4a0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cTargetMorphHandle();  // 0xb1f4d0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cArrowMorphHandle();  // 0xb1f500
}
namespace Simulator {
cGameData_s00b2_4740* Create_cSimpleRotationRing();  // 0xb1f530
}
namespace Simulator {
cGameData_s00b2_4740* Create_cSimpleRotationBall();  // 0xb1f560
}
namespace Simulator {
cGameData_s00b2_4740* Create_cPlanet();  // 0xb1f590
}
namespace Simulator {
cGameData_s00b2_4740* Create_cVisiblePlanet();  // 0xb1f5d0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cStar();  // 0xb1f610
}
namespace Simulator {
cGameData_s00b2_4740* Create_cSolarSystem();  // 0xb1f640
}
namespace Simulator {
cGameData_s00b2_4740* Create_cSimPlanetLowLOD();  // 0xb1f670
}
namespace Simulator {
cGameData_s00b2_4740* Create_cEmpire();  // 0xb1f6a0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cSpaceInventory();  // 0xb1f6d0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cPlayerInventory();  // 0xb1f700
}
namespace Simulator {
cGameData_s00b2_4740* Create_cGameDataUFO();  // 0xb1f730
}
namespace Simulator {
cGameData_s00b2_4740* Create_cTribeHut();  // 0xb1f760
}
namespace Simulator {
cGameData_s00b2_4740* Create_cTribePlanner();  // 0xb1f790
}
namespace Simulator {
cGameData_s00b2_4740* Create_cCreatureSpeciesMission();  // 0xb1f7c0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cCreatureTutorialMission();  // 0xb1f7f0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cTribeToTribeMission();  // 0xb1f820
}
namespace Simulator {
cGameData_s00b2_4740* Create_cFindMission();  // 0xb1f850
}
namespace Simulator {
cGameData_s00b2_4740* Create_cNanoDrone();  // 0xb1f880
}
namespace Simulator {
cGameData_s00b2_4740* Create_cPlaceableSound();  // 0xb1f8b0
}
namespace Simulator {
cGameData_s00b2_4740* Create_cPlaceableEffect();  // 0xb1f8e0
}
namespace eastl {
template <class K, class V>
struct hash_map_s00b2_4740 {
    V& operator[](const K& key);
    uint32_t mData[8];
};
}
namespace Simulator {
class NounCreateMap {
public:
    // Claude-coined name for 0x00b24740 (registration of every built-in noun).
    void RegisterNounClasses();

    inline NounCreateFunction& operator[](uint32_t key) { return classMap[key]; }

protected:
    uint32_t mFactoryBase[4];                                    // +0x00 ISPClassFactory part
    eastl::hash_map_s00b2_4740<uint32_t, NounCreateFunction> classMap;     // +0x10
};
}
// ---- items of slice s00b24740 end

// @ 0x00b1f9d0
int GetPlayerEmpireOrMinus1()
{
    int id = -1;
    switch (GetCurrentGameMode()) {
    case 0x1654c01:
    case 0x1654c02:
    case 0x1654c04:
    case 0x1654c05:
    case 0x1654c10:
        id = GetPlayerEmpireID();
        break;
    }
    return id;
}






// @ 0x00b1fbf0
bool UTFWin::Window::Initialize()
{ return true; }






// @ 0x00b1fc30
void* New_cMissionHappinessEvent()
{
    cGenericPressureEvent* p = (cGenericPressureEvent*)operator new(0x1f0, "Simulator/cMissionHappinessEvent", 0, 0, 0, 0);
    if (p) {
        p->ctor();
        *(void**)p = &gVtblPressureA;
        *(void**)((char*)p + 4) = &gVtblPressureB;
        *(void**)((char*)p + 0x34) = &gVtblPressureC;
        return p;
    }
    return 0;
}





// @ 0x00b1fd50
void __thiscall NounMgr::SetAvatar(cGameData* p)
{
    cGameData* old = mAvatar.p;
    if (old) old->mFlags &= 0xfffffdff;
    if (p) p->mFlags |= 0x200;
    mAvatar = p;
}




// @ 0x00b1fe40
int __cdecl ClassifyA(IRefObject* p)
{
    if (p) {
        if (p->Match(0x4f396a66)) return 0;
        if (p->Match(0xee9b2232)) return 1;
        if (p->Match(0x901f1362)) return 2;
        if (p->Match(0x1805e75))  return 3;
    }
    return -1;
}




// @ 0x00b1feb0
int __stdcall ClassifyB(IRefObject* p)
{
    if (!p) return 0;
    if (p->Match(0x901f1362)) return 4;
    if (p->Match(0x4f396a66)) return 2;
    int a = p->Match(0xd0036e08);
    int b = p->Match(0x1b92b27);
    if (a || b) return 1;
    return 0;
}




// @ 0x00b1ffd0
void __thiscall ByteString::allocate(unsigned n)
{
    if (n > 1) {
        char* p = (char*)SPORE_NEW(n);
        mpBegin = p;
        mpEnd   = p;
        mpCapacity = p + n;
    } else {
        mpBegin = &gEmptyChar;
        mpEnd   = &gEmptyChar;
        mpCapacity = &gEmptyChar + 1;
    }
}




// @ 0x00b20120
void __thiscall ArtilleryBase::Dtor()
{
    if (m53c) m53c->gv64();
    if (m534) m534->gv08();
    if (m524) m524->gv64();
    *(void**)((char*)this + 0x504) = &gArtilleryVtbl;
    ((SerObj*)((char*)this + 0x34))->Set2();
    ((GameDataDtor*)this)->DtorBody();
}




// @ 0x00b201a0
void __thiscall GameDataBig::MarkFeedback(cGameData* p)
{
    if (!p) return;
    unsigned id = (unsigned)p->gv20();
    void* found;
    RBNode* node = (RBNode*)*mFeedback.Find(&found, &id);
    if (node != (RBNode*)&mFeedback.mAnchor) {
        *(char*)(*(int*)((char*)node + 0x14)) = 1;
    }
    RBNode* it = mFeedback.mAnchor.mpNodeLeft;
    RBNode* end = (RBNode*)&mFeedback.mAnchor;
    while (it != end) {
        char* flag = *(char**)((char*)it + 0x14);
        if (*flag == 0) {
            if (p->Match(*(unsigned*)((char*)it + 0x10))) *flag = 1;
        }
        it = RBTreeIncrement(it);
    }
}




// @ 0x00b20230
bool __cdecl IterateList(void* arg, ListNode2* anchor)
{
    ListObj* it = anchor->next ? (ListObj*)((char*)anchor->next - 0xc) : 0;
    ListObj* last = (ListObj*)((char*)anchor - 0xc);
    while (it != last) {
        it->n1c(arg);
        it = it->node.next ? (ListObj*)((char*)it->node.next - 0xc) : 0;
    }
    return true;
}




// @ 0x00b203e0
void __thiscall GameDataBig::RemoveVecItem(cGameData* p)
{
    if (!p) return;
    cGameData** vecBegin = *(cGameData***)((char*)this + 0x5c);
    cGameData** vecEnd = *(cGameData***)((char*)this + 0x60);
    int n = (int)(vecEnd - vecBegin);
    if (n <= 0) return;
    for (int i = 0; i < n; i++) {
        if (vecBegin[i] == p) {
            p->mFlags &= 0xfffffeff;
            cGameData* old = vecBegin[i];
            cGameData* src = vecEnd[-1];
            if (src != old) {
                if (src) src->AddRef();
                vecBegin[i] = src;
                if (old) old->Release();
            }
            vecEnd--;
            *(cGameData***)((char*)this + 0x60) = vecEnd;
            if (*vecEnd) (*vecEnd)->Release();
            return;
        }
    }
}




// @ 0x00b20470
int __thiscall GameDataBig::CountList(cGameData* p)
{
    int n = 0;
    char* head = *(char**)((char*)this + 0x78);
    RBNode* it = head ? (RBNode*)(head - 0xc) : (RBNode*)0;
    RBNode* last = (RBNode*)((char*)this + 0x6c);
    while (it != last) {
        if ((cGameData*)((cGameData*)it)->gv20() == p) n++;
        char* nx = *(char**)((char*)it + 0xc);
        it = nx ? (RBNode*)(nx - 0xc) : (RBNode*)0;
    }
    return n;
}




// @ 0x00b204d0
cGameData* __thiscall GameDataBig::FindList(unsigned key)
{
    char* head = *(char**)((char*)this + 0x78);
    char* it = head ? head - 0xc : 0;
    char* last = (char*)this + 0x6c;
    while (it != last) {
        if (*(unsigned*)(it + 0x24) == key) return (cGameData*)it;
        char* nx = *(char**)(it + 0xc);
        it = nx ? nx - 0xc : 0;
    }
    return 0;
}




// @ 0x00b205a0
SmallObj* __stdcall AllocSmallObj(SmallObj* src)
{
    SmallObj* p = (SmallObj*)SPORE_NEW(0x20);
    if (p) {
        memcpy(p->d, src->d, 0x14);
        p->m14 = src->m14;
        if (p->m14) p->m14->AddRef();
    }
    p->m18 = 0;
    return p;
}




// @ 0x00b20610
void __thiscall ByteString::resize(unsigned n)
{
    unsigned size = (unsigned)(mpEnd - mpBegin);
    if (n < size) {
        char* p = mpBegin + n;
        if (p != mpEnd) {
            memmove(p, mpEnd, 1);
            mpEnd += p - mpEnd;
        }
    } else if (size < n) {
        append(n - size, 0);
    }
}




// @ 0x00b20660
cArtilleryProjectile* __cdecl cArtilleryProjectile::Create()
{
    cArtilleryProjectile* p = (cArtilleryProjectile*)opnew(0x540, "Simulator/cSpear", 0, 0, 0, 0);
    if (p) {
        ((ArtCtorObj*)p)->Ctor();
        *(void**)((char*)p + 0x00) = &gArtVtbl0;
        *(void**)((char*)p + 0x04) = &gArtVtbl1;
        *(void**)((char*)p + 0x34) = &gArtVtbl2;
        *(void**)((char*)p + 0x108) = &gArtVtbl3;
        *(void**)((char*)p + 0x504) = &gArtVtbl4;
        *(void**)((char*)p + 0x53c) = 0;
        return p;
    }
    return 0;
}




// @ 0x00b206d0
void __thiscall FlushMgr::Flush()
{
    RBNode* end = (RBNode*)((char*)this + 0xb8);
    for (RBNode* it = *(RBNode**)((char*)this + 0xbc); it != end; it = RBTreeIncrement(it)) {
        void* p = *(void**)((char*)it + 0x14);
        if (p) opdel(p);
    }
    RBNode* p = *(RBNode**)((char*)this + 0xc0);
    while (p) {
        RBTreeNuke(*(RBNode**)p);
        RBNode* next = *(RBNode**)((char*)p + 4);
        opdel(p);
        p = next;
    }
    char* base = (char*)this + 0xb4;
    *(RBNode**)(base + 8) = (RBNode*)(base + 4);
    *(uint*)(base + 0xc) = 0;
    *(char*)(base + 0x10) = 0;
    *(void**)(base + 0x14) = 0;
    *(RBNode**)(base + 4) = (RBNode*)(base + 4);
}




// @ 0x00b20750
void* __thiscall FeedbackMgr::GetFeedback(unsigned id)
{
    void* found;
    RBNode* node = (RBNode*)*mTree.Find(&found, &id);
    if (node != (RBNode*)&mTree.mAnchor) return *(void**)((char*)node + 0x14);
    return 0;
}




// @ 0x00b20790
int __thiscall FeedbackMgr::ClassifyById(unsigned id)
{
    void* found;
    RBNode* node = (RBNode*)*mTree.Find(&found, &id);
    if (node != (RBNode*)&mTree.mAnchor) {
        void* v = *(void**)((char*)node + 0x14);
        if (v) return ClassifyB((IRefObject*)v);
    }
    unsigned r = (unsigned)((StarMgrObj*)StarManager())->GetEmpireByID(id);
    return r ? 5 : 0;
}




// @ 0x00b20930
void __thiscall MapStrFind::Find(void** out, void* key)
{
    char* node = (char*)*(void**)((char*)this + 0xc);
    char* lower = (char*)this + 4;
    char* result = lower;
    const char* kb = *(const char**)key;
    int kLen = (int)(*(char**)((char*)key + 4) - kb);
    while (node) {
        const char* nb = *(const char**)(node + 0x10);
        int nLen = (int)(*(char**)(node + 0x14) - nb);
        int minLen = nLen < kLen ? nLen : kLen;
        int r = eastlCompare(nb, kb, (unsigned)minLen);
        if (!r) {
            if (nLen < kLen) r = -1;
            else r = nLen > kLen ? 1 : 0;
        }
        if (r < 0) {
            node = *(char**)node;
        } else {
            result = node;
            node = *(char**)(node + 4);
        }
    }
    if (result != lower && !StringLess(key, result + 0x10)) {
        *out = result;
        return;
    }
    *out = lower;
}




// @ 0x00b209f0
void* __thiscall String4::ctor(void* a, void* b)
{
    void* self = this;
    *(void**)self = *(void**)a;
    *(void**)((char*)self + 4) = 0;
    *(void**)((char*)self + 8) = 0;
    *(void**)((char*)self + 0xc) = 0;
    int iVar1 = *(int*)((char*)b + 4);
    const char* src = *(const char**)b;
    unsigned size = (unsigned)(iVar1 - (int)src);
    ((StringBase*)((char*)self + 4))->RangeInitialize(size + 1);
    char* dst = *(char**)((char*)self + 4);
    DoInsertValueC(dst, src, size);
    char* end = dst + size;
    *(char**)((char*)self + 8) = end;
    *end = 0;
    return self;
}




// @ 0x00b20a50
void __stdcall FreeBucketNodes(void** buckets, uint n)
{
    for (uint i = 0; i < n; i++) {
        char* p = (char*)buckets[i];
        if (p) {
            do {
                char* cur = p;
                p = *(char**)(cur + 0x18);
                ((NodeDtor*)(cur + 8))->D();
                opdel(cur);
            } while (p);
        }
        buckets[i] = 0;
    }
}




// @ 0x00b20aa0
void* __cdecl FormatAppend(void* self, const char* fmt, ...)
{
    va_list args;
    int base = *(int*)((char*)self + 4);
    int iVar3 = base - *(int*)self;
    int cap = *(int*)self == (int)&gEmptyChar ? 0
              : *(int*)((char*)self + 8) - base;
    VA_START(args, fmt);
    int n = Vsnprintf8((char*)base, (unsigned)cap, fmt, args);
    if (n < *(int*)((char*)self + 8) - *(int*)((char*)self + 4)) {
        if (n < 0) {
            uint grow = 7;
            uint cur = (uint)((*(int*)((char*)self + 4) - *(int*)self) * 2);
            uint chosen = cur < 8 ? grow : cur;
            for (;;) {
                if (chosen >= 0xf4240) break;
                FormatResize(self, chosen);
                n = Vsnprintf8((char*)(*(int*)self + iVar3),
                               (chosen - (uint)iVar3) + 1, fmt, args);
                chosen *= 2;
                if (n >= 0) break;
            }
        }
    } else {
        FormatResize(self, (unsigned)(n + iVar3));
        n = Vsnprintf8((char*)(*(int*)self + iVar3), (unsigned)(n + 1), fmt, args);
    }
    if (n >= 0) *(int*)((char*)self + 4) = *(int*)self + n + iVar3;
    return self;
}




// @ 0x00b20b90
void* __thiscall StringC::ctor(void* a)
{
    void* self = this;
    *(void**)self = *(void**)a;
    *(void**)((char*)self + 4) = 0;
    *(void**)((char*)self + 8) = 0;
    *(void**)((char*)self + 0xc) = 0;
    int iVar1 = *(int*)((char*)a + 8);
    const char* src = *(const char**)((char*)a + 4);
    unsigned size = (unsigned)(iVar1 - (int)src);
    ((StringBase*)((char*)self + 4))->RangeInitialize(size + 1);
    char* dst = *(char**)((char*)self + 4);
    DoInsertValueC(dst, src, size);
    char* end = dst + size;
    *(char**)((char*)self + 8) = end;
    *end = 0;
    return self;
}




// @ 0x00b20c00
void* __thiscall StringAlloc::ctor(void* a)
{
    void* self = this;
    *(void**)self = 0;
    *(void**)((char*)self + 4) = 0;
    *(void**)((char*)self + 8) = 0;
    *(void**)((char*)self + 0x10) = *(void**)((char*)a + 0x10);
    int iVar1 = *(int*)((char*)a + 4);
    const char* src = *(const char**)a;
    unsigned size = (unsigned)(iVar1 - (int)src);
    ((ByteString*)self)->allocate(size + 1);
    char* dst = *(char**)self;
    DoInsertValueC(dst, src, size);
    char* end = dst + size;
    *(char**)((char*)self + 4) = end;
    *end = 0;
    return self;
}



// @ 0x00b225b0
void __thiscall cGameNounManager::Dummy225b0()
{
    FlushTemp();
    mapA.Fn(mapB);
}


// @ 0x00b225d0
void __thiscall cGameNounManager::RemoveNoun(cNoun* n)
{
    n->removed = true;
    ARC<cNoun> a(n);
    mTempNouns.push_back(a);
    PostRemove(n);
    PostRemove2(n);
}


// @ 0x00b22650
void __thiscall cGameNounManager::RemoveNounsOfType(int type)
{
    static StaticNounVec found;
    for (cNoun* it = cNoun::FromNode(mNouns.next); it != cNoun::FromNode(&mNouns); it = cNoun::FromNode(it->node.next)) {
        if (it->GetType() == type) {
            ARC<cNoun> a(it);
            found.push_back(a);
        }
    }
    for (uint i = 0; i < (uint)(found.end - found.begin); i++) RemoveNoun(found.begin[i]);
    found.erase(found.begin, found.end);
}


// @ 0x00b227c0
void __thiscall cGameNounManager::RemoveNounsWithInterface(unsigned id)
{
    static StaticNounVec found;
    for (cNoun* it = cNoun::FromNode(mNouns.next); it != cNoun::FromNode(&mNouns); it = cNoun::FromNode(it->node.next)) {
        if (it->Cast(id)) {
            ARC<cNoun> a(it);
            found.push_back(a);
        }
    }
    for (uint i = 0; i < (uint)(found.end - found.begin); i++) RemoveNoun(found.begin[i]);
    found.erase(found.begin, found.end);
}


// @ 0x00b22930
void __thiscall cGameNounManager::RemoveHerd(cNoun* herd)
{
    RemoveNoun(herd);
    if (mAvatarHerd == herd) mAvatarHerd = 0;
}


// @ 0x00b22960
void __thiscall cGNM2::ProcessPending()
{
    ((SysGui*)0x0167c988)->SetSerializer();
    IRefCount* ctx = GetModelManager()->Lookup(0xeb9968);
    if (ctx) ctx->AddRef();
    PNode* node = mPending.next;
    while (node != &mPending) {
        IRefCount* obj = node->value;
        bool keep = false;
        IPending* d = 0;
        if (obj) d = (IPending*)obj->Cast(0x1186577);
        PInfo* info = 0;
        bool erase = false;
        if (!d) {
            erase = true;
        } else {
            info = d->GetInfo();
            if (!info) {
                if (!d->HasCtx() || !d->BindCtx(ctx) || !(info = d->GetInfo())) erase = true;
            }
        }
        if (!erase) {
            unsigned fl = d->flags;
            if (!(fl & 0x20)) {
                if (info->f4 >> 14 & 1) {
                    d->flags = fl & ~0x10u;
                    d->Apply(info->data, d->f13());
                    keep = false;
                } else {
                    d->flags = fl | 0x10;
                    keep = true;
                }
            }
            if (info && (d->flags & 0x8000)) {
                if ((info->f4 >> 14 & 1) && !(info->f4 >> 18 & 1)) {
                    d->Apply(info->data, d->f13());
                    erase = true;
                } else {
                    node = node->next;
                    continue;
                }
            } else if (keep) {
                node = node->next;
                continue;
            } else {
                erase = true;
            }
        }
        // erase the node and broadcast a removal message
        PNode* next = node->next;
        PNode* dead = next->prev;
        dead->prev->next = dead->next;
        dead->next->prev = dead->prev;
        if (dead->value) dead->value->Release();
        operator_delete__(dead);
        UIMessage msg;
        msg.id = 0;
        msg.rc = 0;
        msg.vptr = vtbl_UIMessageBase;
        msg.vptr = vtbl_UIMessage;
        msg.flags = 0;
        msg.d0 = 3;
        msg.d1 = obj;
        GetMessageServer()->Post(0x1a0219e, &msg, 0);
        msg.Destruct();
        node = next;
    }
    FlushTemp();
    mTempNouns.erase(mTempNouns.begin, mTempNouns.end);
    if (ctx) ctx->Release();
}


// @ 0x00b22bc0
void __thiscall cGameNounManager::Cleanup()
{
    FlushTemp();
    mapA.Fn(mapB);
    cNoun* it = cNoun::FromNode(mNouns.next);
    cNoun* last = cNoun::FromNode(&mNouns);
    RawVec v = { 0, 0, 0 };
    for (; it != last; it = cNoun::FromNode(it->node.next)) {
        if (it && it->Cast(0xce9f6639)) {
            cNoun* tmp = it;
            if (v.end < v.cap) {
                cNoun** p = v.end++;
                if (p) *p = it;
            } else {
                v.DoInsertValue(v.end, &tmp);
            }
        }
    }
    int n = v.end - v.begin;
    for (int i = 0; i < n; i++) PostRemove(v.begin[i]);
}


// @ 0x00b22cc0
cNoun* __thiscall cGameNounManager::CreateAndInit(NounDesc* d, void* a2, void* a3, void* a4)
{
    cNoun* n = CreateNoun(d->id);
    if (n) {
        cNounData* x = (cNounData*)n->Cast(0x1186577);
        if (x) {
            if (a3) x->SetA(a3);
            if (a4) x->SetB(a4);
            if (d->props) {
                bool b = false;
                if (GetBoolProperty(d->props, 0x3d08e15, &b)) x->b71 = b;
                unsigned u = 0;
                if (GetPropertyAsUint32(d->props, 0x93336c12, &u)) x->f58 = u;
                float f = kFloat1;
                if (GetFloatProperty(d->props, 0x4a0ca460, &f)) x->f8c = f;
            }
        }
        if (!n->Init(d, a2, a3)) {
            RemoveNoun(n);
            return 0;
        }
    }
    return n;
}


// @ 0x00b22e80
void __cdecl ClearHolderVec(VecHolder* h)
{
    SPVecARC* v = &h->vec;
    v->erase(v->begin, v->end);
}


// @ 0x00b22ea0
void __cdecl PushBackCast(VecHolder2* h, IObj47* obj)
{
    IObj47* x = obj ? obj->Cast(0x1186577) : 0;
    if (x) x->AddRefX();
    IObj47** p = h->vec.end;
    if (p < h->vec.cap) {
        h->vec.end = p + 1;
        if (p) {
            *p = x;
            if (x) x->AddRefX();
        }
    } else {
        h->vec.DoInsertValue(p, &x);
    }
    if (x) x->ReleaseX();
}

// @ 0x00b24740
namespace Simulator {
void NounCreateMap::RegisterNounClasses()
{
    RegisterNounType(0x2a37e35, 0x2a37e34, "cCheatObject");
    (*this)[0x2a37e35] = &Create_cCheatObject;
    RegisterNounType(0x2afd284, 0x2afd27e, "cMissionFetch");
    (*this)[0x2afd284] = &Create_cMissionFetch;
    RegisterNounType(0x4f3bde9, 0x4f3bde8, "cMissionHappinessEvent");
    (*this)[0x4f3bde9] = &Create_cMissionHappinessEvent;
    RegisterNounType(0x4f77499, 0x4f77498, "cMissionMakeAlly");
    (*this)[0x4f77499] = &Create_cMissionMakeAlly;
    RegisterNounType(0x397bff3, 0x397bff2, "cRaidPlunderEvent");
    (*this)[0x397bff3] = &Create_cRaidPlunderEvent;
    RegisterNounType(0x3960c0e, 0x3960c0a, "cRaidEvent");
    (*this)[0x3960c0e] = &Create_cRaidEvent;
    RegisterNounType(0x2ba2a0e, 0x2ba2a01, "cMissionColonize");
    (*this)[0x2ba2a0e] = &Create_cMissionColonize;
    RegisterNounType(0x2f99994, 0x2f9998c, "cMissionEradicate");
    (*this)[0x2f99994] = &Create_cMissionEradicate;
    RegisterNounType(0x32a12f1, 0x32a12f0, "cMissionExplore");
    (*this)[0x32a12f1] = &Create_cMissionExplore;
    RegisterNounType(0x330fc49, 0x330fc43, "cMissionWar");
    (*this)[0x330fc49] = &Create_cMissionWar;
    RegisterNounType(0x347092d, 0x3470926, "cMissionScan");
    (*this)[0x347092d] = &Create_cMissionScan;
    RegisterNounType(0x35988f4, 0x35988ee, "cMissionTerraform");
    (*this)[0x35988f4] = &Create_cMissionTerraform;
    RegisterNounType(0x2adedff, 0x2aeefff, "cMissionTrade");
    (*this)[0x2adedff] = &Create_cMissionTrade;
    RegisterNounType(0x447092d, 0x4470926, "cMissionTradeRoute");
    (*this)[0x447092d] = &Create_cMissionTradeRoute;
    RegisterNounType(0x35ed8f6, 0x35ed8f0, "cMissionMultiDelivery");
    (*this)[0x35ed8f6] = &Create_cMissionMultiDelivery;
    RegisterNounType(0x437444b, 0x437443d, "cMissionBiosphere");
    (*this)[0x437444b] = &Create_cMissionBiosphere;
    RegisterNounType(0x317afcc, 0x317afcb, "cGenericPressureEvent");
    (*this)[0x317afcc] = &Create_cGenericPressureEvent;
    RegisterNounType(0x4222283, 0x422227c, "cMissionMultiStep");
    (*this)[0x4222283] = &Create_cMissionMultiStep;
    RegisterNounType(0x347092e, 0x3470927, "cMissionBalance");
    (*this)[0x347092e] = &Create_cMissionBalance;
    RegisterNounType(0x347092f, 0x3470928, "cMissionFindAliens");
    (*this)[0x347092f] = &Create_cMissionFindAliens;
    RegisterNounType(0x4222284, 0x422227d, "cMissionFlight101");
    (*this)[0x4222284] = &Create_cMissionFlight101;
    RegisterNounType(0x2adedee, 0x2aeeeee, "cMissionUseTool");
    (*this)[0x2adedee] = &Create_cMissionUseTool;
    RegisterNounType(0x4222285, 0x422227e, "cMissionStory201");
    (*this)[0x4222285] = &Create_cMissionStory201;
    RegisterNounType(0x4622285, 0x462227e, "cMissionChangeArchetype");
    (*this)[0x4622285] = &Create_cMissionChangeArchetype;
    RegisterNounType(0x4633285, 0x463327e, "cMissionTrackBadge");
    (*this)[0x4633285] = &Create_cMissionTrackBadge;
    RegisterNounType(0x46332a5, 0x463329e, "cMissionAdventure");
    (*this)[0x46332a5] = &Create_cMissionAdventure;
    RegisterNounType(0x2c21781, 0x2c216ed, "cPlayer");
    (*this)[0x2c21781] = &Create_cPlayer;
    RegisterNounType(0x2e9ae6c, 0x2e9ae69, "cMilitaryAttackCityOrder");
    (*this)[0x2e9ae6c] = &Create_cMilitaryAttackCityOrder;
    RegisterNounType(0x3df2cc5, 0x3df2cb9, "cCulturalConvertCityOrder");
    (*this)[0x3df2cc5] = &Create_cCulturalConvertCityOrder;
    RegisterNounType(0x18c40bc, 0x14a4edc, "cGameTerrainCursor");
    (*this)[0x18c40bc] = &Create_cGameTerrainCursor;
    RegisterNounType(0x18ea1eb, 0x1007ae63, "cBuildingCityHall");
    (*this)[0x18ea1eb] = &Create_cBuildingCityHall;
    RegisterNounType(0x18ea2cc, 0xecade42, "cBuildingIndustry");
    (*this)[0x18ea2cc] = &Create_cBuildingIndustry;
    RegisterNounType(0x18eb106, 0xff10521, "cBuildingHouse");
    (*this)[0x18eb106] = &Create_cBuildingHouse;
    RegisterNounType(0x1a56aba, 0x1a55e4d, "cBuildingEntertainment");
    (*this)[0x1a56aba] = &Create_cBuildingEntertainment;
    RegisterNounType(0x70703b3, 0x70704db, "cBuildingScenario");
    (*this)[0x70703b3] = &Create_cBuildingScenario;
    RegisterNounType(0x436f342, 0x436f315, "cTurret");
    (*this)[0x436f342] = &Create_cTurret;
    RegisterNounType(0x38cfb6b, 0x38cfb68, "cCelestialBody");
    (*this)[0x38cfb6b] = &Create_cCelestialBody;
    RegisterNounType(0x18c431c, 0x4ffcdeda, "cGameBundle");
    (*this)[0x18c431c] = &Create_cGameBundle;
    RegisterNounType(0x3d5c325, 0x3d5c477, "cCulturalTarget");
    (*this)[0x3d5c325] = &Create_cCulturalTarget;
    RegisterNounType(0x18c43e8, 0xee9b2232, "cCity");
    (*this)[0x18c43e8] = &Create_cCity;
    RegisterNounType(0x1906183, 0xeef202b7, "cGameBundleGroundContainer");
    (*this)[0x1906183] = &Create_cGameBundleGroundContainer;
    RegisterNounType(0x18c6de8, 0x137e8e0, "cVehicle");
    (*this)[0x18c6de8] = &Create_cVehicle;
    RegisterNounType(0x2e98ab7, 0x2e98ab4, "cVehicleGroupOrder");
    (*this)[0x2e98ab7] = &Create_cVehicleGroupOrder;
    RegisterNounType(0x18c7c97, 0xed7fc07, "cCityWalls");
    (*this)[0x18c7c97] = &Create_cCityWalls;
    RegisterNounType(0x244fb08, 0x2450023, "cCityTerritory");
    (*this)[0x244fb08] = &Create_cCityTerritory;
    RegisterNounType(0x2c5c93a, 0x2c5c935, "cPlaceholderColonyEditorCursorAttachment");
    (*this)[0x2c5c93a] = &Create_cPlaceholderColonyEditorCursorAttachment;
    RegisterNounType(0x2dd8c42, 0x2dd8c33, "cPlanetaryArtifact");
    (*this)[0x2dd8c42] = &Create_cPlanetaryArtifact;
    RegisterNounType(0x4e3fab5, 0x4e3faaf, "cToolObject");
    (*this)[0x4e3fab5] = &Create_cToolObject;
    RegisterNounType(0x18c816a, 0x901f1362, "cCivilization");
    (*this)[0x18c816a] = &Create_cCivilization;
    RegisterNounType(0x18eb45e, 0xd0036e08, "cCreatureAnimal");
    (*this)[0x18eb45e] = &Create_cCreatureAnimal;
    RegisterNounType(0x18eb4b7, 0x4f176642, "cCreatureCitizen");
    (*this)[0x18eb4b7] = &Create_cCreatureCitizen;
    RegisterNounType(0x3ed8573, 0x3ed590d, "cObstacle");
    (*this)[0x3ed8573] = &Create_cObstacle;
    RegisterNounType(0x18c84a9, 0xaeb336b4, "cGamePlant");
    (*this)[0x18c84a9] = &Create_cGamePlant;
    RegisterNounType(0x2c9cc91, 0x2c9cc8e, "cFruit");
    (*this)[0x2c9cc91] = &Create_cFruit;
    RegisterNounType(0x2e96892, 0x2e9688e, "cFruitGroup");
    (*this)[0x2e96892] = &Create_cFruitGroup;
    RegisterNounType(0x52aa6122, 0x1b92b27, "cNest");
    (*this)[0x52aa6122] = &Create_cNest;
    RegisterNounType(0x1be418e, 0x52aa6117, "cHerd");
    (*this)[0x1be418e] = &Create_cHerd;
    RegisterNounType(0x2a034cd, 0x2a0349a, "cEgg");
    (*this)[0x2a034cd] = &Create_cEgg;
    RegisterNounType(0x3a2511e, 0x3a25119, "cInteractiveOrnament");
    (*this)[0x3a2511e] = &Create_cInteractiveOrnament;
    RegisterNounType(0x36be27e, 0x36be278, "cGameplayMarker");
    (*this)[0x36be27e] = &Create_cGameplayMarker;
    RegisterNounType(0x18c88e4, 0x175cdc9, "cOrnament");
    (*this)[0x18c88e4] = &Create_cOrnament;
    RegisterNounType(0x61494be, 0x61494bd, "cAnimalTrap");
    (*this)[0x61494be] = &Create_cAnimalTrap;
    RegisterNounType(0x55cf865, 0x55cf8e3, "cTotemPole");
    (*this)[0x55cf865] = &Create_cTotemPole;
    RegisterNounType(0x629bafe, 0x629baec, "cTribeFoodMat");
    (*this)[0x629bafe] = &Create_cTribeFoodMat;
    RegisterNounType(0x2a8fb3f, 0x2a8fe3c, "cRock");
    (*this)[0x2a8fb3f] = &Create_cRock;
    RegisterNounType(0x403df5c, 0x403df5f, "cCommodityNode");
    (*this)[0x403df5c] = &Create_cCommodityNode;
    RegisterNounType(0x283ddb1, 0x283d961, "cMovableDestructibleOrnament");
    (*this)[0x283ddb1] = &Create_cMovableDestructibleOrnament;
    RegisterNounType(0x32f9778, 0x32f9777, "cSolarHitSphere");
    (*this)[0x32f9778] = &Create_cSolarHitSphere;
    RegisterNounType(0x2e72cae, 0x2e71a5a, "cHitSphere");
    (*this)[0x2e72cae] = &Create_cHitSphere;
    RegisterNounType(0x2b8a4e7, 0x2bca14b, "cInterCityRoad");
    (*this)[0x2b8a4e7] = &Create_cInterCityRoad;
    RegisterNounType(0x18c6d19, 0x4f396a66, "cTribe");
    (*this)[0x18c6d19] = &Create_cTribe;
    RegisterNounType(0x18c8f0c, 0x116d858, "cTribeTool");
    (*this)[0x18c8f0c] = &Create_cTribeTool;
    RegisterNounType(0x24270c9, 0x24270c8, "cSpear");
    (*this)[0x24270c9] = &Create_cSpear;
    RegisterNounType(0x18c9380, 0x1428a48, "cArtilleryProjectile");
    (*this)[0x18c9380] = &Create_cArtilleryProjectile;
    RegisterNounType(0x240e3bf, 0x240e3b7, "cFlakProjectile");
    (*this)[0x240e3bf] = &Create_cFlakProjectile;
    RegisterNounType(0x24270c5, 0x24270c4, "cDefaultToolProjectile");
    (*this)[0x24270c5] = &Create_cDefaultToolProjectile;
    RegisterNounType(0x24270c7, 0x24270c6, "cDeepSpaceProjectile");
    (*this)[0x24270c7] = &Create_cDeepSpaceProjectile;
    RegisterNounType(0x244d3c8, 0x244d3c0, "cSpaceDefenseMissile");
    (*this)[0x244d3c8] = &Create_cSpaceDefenseMissile;
    RegisterNounType(0x24630d7, 0x24630ce, "cDefaultBeamProjectile");
    (*this)[0x24630d7] = &Create_cDefaultBeamProjectile;
    RegisterNounType(0x4167186, 0x4167194, "cDefaultAoEArea");
    (*this)[0x4167186] = &Create_cDefaultAoEArea;
    RegisterNounType(0x4f76f0d, 0x4f76f08, "cCulturalProjectile");
    (*this)[0x4f76f0d] = &Create_cCulturalProjectile;
    RegisterNounType(0x5776a2c, 0x5776a28, "cResourceProjectile");
    (*this)[0x5776a2c] = &Create_cResourceProjectile;
    RegisterNounType(0x49cec61, 0x49cec5c, "cICBM");
    (*this)[0x49cec61] = &Create_cICBM;
    RegisterNounType(0x18eb641, 0x903c3ea3, "cSoundLoopObject");
    (*this)[0x18eb641] = &Create_cSoundLoopObject;
    RegisterNounType(0x2ee8ce8, 0x2ee8eeb, "cRotationRing");
    (*this)[0x2ee8ce8] = &Create_cRotationRing;
    RegisterNounType(0x7292112, 0x7292112, "cRotationBall");
    (*this)[0x7292112] = &Create_cRotationBall;
    RegisterNounType(0x7a30a12, 0x7a309fb, "cMorphHandle");
    (*this)[0x7a30a12] = &Create_cMorphHandle;
    RegisterNounType(0x76f6e64, 0x76c67df, "cTargetMorphHandle");
    (*this)[0x76f6e64] = &Create_cTargetMorphHandle;
    RegisterNounType(0x771ad6f, 0x771ad6a, "cArrowMorphHandle");
    (*this)[0x771ad6f] = &Create_cArrowMorphHandle;
    RegisterNounType(0x7a81829, 0x7a81824, "cSimpleRotationRing");
    (*this)[0x7a81829] = &Create_cSimpleRotationRing;
    RegisterNounType(0x7abdd91, 0x7abdd8d, "cSimpleRotationBall");
    (*this)[0x7abdd91] = &Create_cSimpleRotationBall;
    RegisterNounType(0x3275728, 0x3275872, "cPlanet");
    (*this)[0x3275728] = &Create_cPlanet;
    RegisterNounType(0x44462a6, 0x44462a6, "cVisiblePlanet");
    (*this)[0x44462a6] = &Create_cVisiblePlanet;
    RegisterNounType(0x355c93a, 0x355c8df, "cStar");
    (*this)[0x355c93a] = &Create_cStar;
    RegisterNounType(0x38cf94c, 0x38cf949, "cSolarSystem");
    (*this)[0x38cf94c] = &Create_cSolarSystem;
    RegisterNounType(0x3572e72, 0x3572e6c, "cSimPlanetLowLOD");
    (*this)[0x3572e72] = &Create_cSimPlanetLowLOD;
    RegisterNounType(0x18eb9d2, 0x1805e75, "cEmpire");
    (*this)[0x18eb9d2] = &Create_cEmpire;
    RegisterNounType(0x21ffa3f, 0xb075dec5, "cSpaceInventory");
    (*this)[0x21ffa3f] = &Create_cSpaceInventory;
    RegisterNounType(0x2265fdc, 0x9073163b, "cPlayerInventory");
    (*this)[0x2265fdc] = &Create_cPlayerInventory;
    RegisterNounType(0x18ebadc, 0xb033b403, "cGameDataUFO");
    (*this)[0x18ebadc] = &Create_cGameDataUFO;
    RegisterNounType(0x1e4daae, 0xee02c7, "cTribeHut");
    (*this)[0x1e4daae] = &Create_cTribeHut;
    RegisterNounType(0x3098af98, 0x9098aeb2, "cTribePlanner");
    (*this)[0x3098af98] = &Create_cTribePlanner;
    RegisterNounType(0x1406a572, 0x7406a570, "cCreatureSpeciesMission");
    (*this)[0x1406a572] = &Create_cCreatureSpeciesMission;
    RegisterNounType(0x34066dba, 0xd4066db3, "cCreatureTutorialMission");
    (*this)[0x34066dba] = &Create_cCreatureTutorialMission;
    RegisterNounType(0x5436411a, 0x34364118, "cTribeToTribeMission");
    (*this)[0x5436411a] = &Create_cTribeToTribeMission;
    RegisterNounType(0x14d9597f, 0x14d9597c, "cFindMission");
    (*this)[0x14d9597f] = &Create_cFindMission;
    RegisterNounType(0x6ef0f11, 0x6ef0ec9, "cNanoDrone");
    (*this)[0x6ef0f11] = &Create_cNanoDrone;
    RegisterNounType(0x74e0069, 0x74e0069, "cPlaceableSound");
    (*this)[0x74e0069] = &Create_cPlaceableSound;
    RegisterNounType(0x7b38ba7, 0x7b38ba7, "cPlaceableEffect");
    (*this)[0x7b38ba7] = &Create_cPlaceableEffect;
}
}  // namespace Simulator
