// src/game/SPGonzago/SPGameNounManager.cpp -- migrated from slice(s) s00b25c30, s00b23e60, s00b230b0, s00b20fb0, s00b24740, s00b21e60, s00b1fd50, s00b1d870 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameNounManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#define _VA_LIST_DEFINED   // the slices' own va_list typedef wins over <vadefs.h> (rewrite.py)
#include "game/types.h"
#include "SP/cGameNounManager.h"
#include "EA/Audio/IPrimitive.h"
#include "SP/cArtilleryProjectile.h"
#include "SP/cGameData.h"
#include "SP/cVarListSerializer.h"
#include "EA/UTFWin/ISerializer.h"
#include "EA/UTFWin/Window.h"
#include "SP/cVehicleGroupOrder.h"
#include <new>
#include <intrin.h>
#include "SP/cCulturalConvertCityOrder.h"
#include "SP/cGonzagoSubsystem.h"
#include "SP/cMilitaryAttackCityOrder.h"
#include "SP/cPlanetModel.h"
#include "SP/cCity.h"
#include "SP/cCivilization.h"
#include "SP/cEmpire.h"
#include "SP/cGonzagoSimulator.h"
#include "SP/cIGonzagoSubsystem.h"
#include "SP/cISerializableObject.h"
#include "SP/cStarManager.h"

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
#define _VA_LIST_DEFINED   // the slices' own va_list typedef wins over <vadefs.h> (rewrite.py)
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

// ---- items of slice s00b20fb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ListNode_s00b2_0fb0 {
  void* mField00;                                         // +0x00
  void* mField04;                                         // +0x04
  void* mField08;                                         // +0x08
};
struct ListSeg {
  uint8_t mUnused00[4];
  void*   mField04;                                       // +0x04  anchor.next
  void*   mField08;                                       // +0x08  anchor.prev
  void*   mField0c;                                       // +0x0c  last element
  uint8_t mUnused10[4];
  void*   mField14;                                       // +0x14
  void    FUN_00b21da0(ListSeg* other);
};
// ---- items of slice s00b20fb0 end

// ---- items of slice s00b230b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl EASTL_allocate(uint32_t nSize, const char* pName, int32_t nA, int32_t nB,
                             const char* pFile, int32_t nLine);                     // 0x00f473a0
void* __cdecl operator new(uint32_t nSize, const char* pName, int32_t nA, int32_t nB,
                           const char* pFile, int32_t nLine);                       // 0x00f473a0
void* __cdecl operator new(uint32_t nSize, void* pWhere);                           // placement new
void  __cdecl operator_delete(void* pBlock);                                        // 0x00f47380
void* __cdecl SP_memcpy(void* pDst, const void* pSrc, uint32_t nSize);              // 0x011e0744
uint8_t g_vtableMACOrderPrimary;        // 0x0145ef78 Simulator::cMilitaryAttackCityOrder
uint8_t g_vtableMACOrderSecondary;      // 0x0145ef64 Simulator::cMilitaryAttackCityOrder
uint8_t g_vtableConvertOrderPrimary;    // 0x0145efe8 Simulator::cCulturalConvertCityOrder
uint8_t g_vtableConvertOrderSecondary;  // 0x0145efd8 Simulator::cCulturalConvertCityOrder
uint8_t g_vtableListenerA;              // 0x013eb384 cListenerBase
uint8_t g_vtableListenerPrimary;        // 0x0145ef10 cListenerBase
uint8_t g_vtableListenerGonzago;        // 0x0145eec0 SP::cGonzagoSubsystem
uint8_t g_vtableListenerTail;           // 0x0145eeb8 cListenerBase
uint32_t g_listenerNameTable;           // 0x0154df28 the listener's event-name table
uint8_t  g_funB21080;                   // 0x00b21080 game-data vector callback
uint8_t  g_funB22E80;                   // 0x00b22e80 ClearHolderVec
uint8_t  g_funB22EA0;                   // 0x00b22ea0 PushBackCast
uint8_t  g_funB1E520;                   // 0x00b1e520 game-data vector callback
uint8_t  g_funCD7D10;                   // 0x00cd7d10 game-data vector callback
uint8_t  g_funD3D420;                   // 0x00d3d420 game-data vector callback
uint8_t  g_funACCBB0;                   // 0x00accbb0 game-data vector callback
uint8_t  g_funB1E500;                   // 0x00b1e500 game-data vector callback
uint8_t  g_classKey18c6d19;             // 0x018c6d19 the class the noun lookup walks
uint8_t  g_gameModeAssembling;          // 0x01654c01
uint8_t  g_gameModeAdventuring;         // 0x01654c02
void*    __cdecl PlanetModel();                                     // 0x00b3d350
void*    __cdecl GetCurrentGameMode_s00b2_30b0();                              // 0x00b5b800
void     __cdecl FUN_00b215a0();                                    // 0x00b215a0
void     __cdecl FUN_00c6ace0(void* pNoun, int32_t nMode);          // 0x00c6ace0
void     __stdcall FUN_00aea5d0(void* pEnd, const void* pValue);    // 0x00aea5d0
int32_t  __cdecl ClassifyA(void* pObject);                          // 0x00b1fe40
void     __cdecl rbtree_node_dtor(void* pNode);                     // 0x00d0c930
void     __cdecl EA_Messaging_RemoveHandler(uint32_t nHandler, uint32_t nA, uint32_t nB,
                                            uint32_t nC, uint32_t nD);  // 0x0571db0
void*    __stdcall GetGameDataVector(void* pF1, void* pF2, void* pF3, void* pF4,
                                     void* pKey);                   // 0x00b21340
class cRefObj {
public:
    virtual void* v00();                        // +0x00 AddRef
    virtual void  v04();                        // +0x04 Release
};
class cNoun_s00b2_30b0 {
public:
    virtual void* v00();                        // +0x000 AddRef
    virtual void  v04();                        // +0x004 Release
    virtual void* v08();                        // +0x008
    virtual void* v0c();                        // +0x00c
    virtual void* v10();                        // +0x010
    virtual void* v14();                        // +0x014
    virtual void* v18();                        // +0x018
    virtual void* v1c();                        // +0x01c
    virtual void* v20();                        // +0x020
    virtual void* v24();                        // +0x024
    virtual void* v28();                        // +0x028
    virtual void* v2c();                        // +0x02c
    virtual void* v30();                        // +0x030
    virtual void* v34();                        // +0x034
    virtual void* v38();                        // +0x038
    virtual void* v3c();                        // +0x03c
    virtual void* v40();                        // +0x040
    virtual void* v44();                        // +0x044
    virtual void* v48();                        // +0x048
    virtual void* v4c();                        // +0x04c
    virtual void* v50();                        // +0x050
    virtual void  v54();                        // +0x054

    uint32_t  mPad004[12];                      // +0x004 .. +0x033
    float     mf34;                             // +0x034 position
    float     mf38;                             // +0x038
    float     mf3c;                             // +0x03c
    uint32_t  mPad040[0x11];                    // +0x040 .. +0x083
    uint8_t   mb084;                            // +0x084
    uint8_t   mPad085[0x1f];                    // +0x085 .. +0x0a3
    uint32_t  mn0a4;                            // +0x0a4
    uint32_t  mPad0a8[0x2ac];                   // +0x0a8 .. +0x0b57
    uint32_t  mn0b58;                           // +0x0b58 flags
    uint32_t  mPad0b5c[0x66];                   // +0x0b5c .. +0x0f3
    uint32_t  mn0f4;                            // +0x0f4
    uint32_t  mPad0f8[0x19];                    // +0x0f8 .. +0x15b
    uint32_t  mn15c;                            // +0x15c
    void*     mp160;                            // +0x160
};
class cAutoRef {
public:
    cNoun_s00b2_30b0* mpObject;                            // +0x00

    cAutoRef(cNoun_s00b2_30b0* pObject);
    ~cAutoRef();
    cAutoRef& operator=(cNoun_s00b2_30b0* pObject);
    cAutoRef& Set(cNoun_s00b2_30b0* pObject);              // 0x00b5f950 the out-of-line assignment
};
cAutoRef::cAutoRef(cNoun_s00b2_30b0* pObject)
{
    mpObject = pObject;
    pObject->v00();
}
cAutoRef::~cAutoRef()
{
    if (mpObject != 0)
        mpObject->v04();
}
cAutoRef& cAutoRef::operator=(cNoun_s00b2_30b0* pObject)
{
    cNoun_s00b2_30b0* pOld = mpObject;
    if (pObject != pOld)
    {
        if (pObject != 0)
            pObject->v00();
        mpObject = pObject;
        if (pOld != 0)
            pOld->v04();
    }
    return *this;
}
class cRefVector {
public:
    cAutoRef* mpBegin;                          // +0x00
    cAutoRef* mpEnd;                            // +0x04
    cAutoRef* mpEndAlloc;                       // +0x08

    void erase(void* pFirst, void* pLast);      // 0x00e25bd0
    void push_back(cAutoRef& ref);
};
void cRefVector::push_back(cAutoRef& ref)
{
    if (mpEnd < mpEndAlloc)
    {
        cAutoRef* pSlot = mpEnd;
        mpEnd = pSlot + 1;
        if (pSlot != 0)
        {
            pSlot->mpObject = ref.mpObject;
            ref.mpObject->v00();
        }
    }
    else
    {
        FUN_00aea5d0(mpEnd, &ref);
    }
}
class cListHead;
class cListNode {
public:
    cListNode* mpNext;                          // +0x00
    cListNode* mpPrev;                          // +0x04
};
class cListHead {
public:
    cListNode* mpNext;                          // +0x00
    cListNode* mpPrev;                          // +0x04

    void Init()
    {
        mpNext = (cListNode*)this;
        mpPrev = (cListNode*)this;
    }
    void InitReversed()
    {
        mpPrev = (cListNode*)this;
        mpNext = (cListNode*)this;
    }
    void ClearNodes()
    {
        for (cListNode* pNode = mpNext; pNode != (cListNode*)this; )
        {
            cListNode* pNext = pNode->mpNext;
            pNode->mpPrev = 0;
            pNode->mpNext = 0;
            pNode = pNext;
        }
        mpPrev = (cListNode*)this;
        mpNext = (cListNode*)this;
    }
};
class cRBTree {
public:
    void* volatile    mp00;                     // +0x00
    void* volatile    mp04;                     // +0x04 anchor/end node
    void* volatile    mp08;                     // +0x08
    void* volatile    mp0c;                     // +0x0c root node
    union {
        struct {
            uint8_t  volatile mb10;             // +0x10 the root node's colour
            uint8_t  mPad11[3];                 // +0x11 .. +0x13
        };
        uint32_t volatile mn10Word;             // +0x10 the same four bytes as one word
    };
    uint32_t volatile mn14;                     // +0x14

    void** find(void** ppOut, const void* pKey);            // 0x00e5c780
    cAutoRef* insert(const void* pKey);                     // 0x00dd85c0
    void clear();
};
void cRBTree::clear()
{
    rbtree_node_dtor(mp0c);
    mp08 = (void*)&mp04;
    mp0c = 0;
    mb10 = 0;
    mn14 = 0;
    mp04 = (void*)&mp04;
}
class cRefNode {
public:
    cAutoRef  mObject;                          // +0x00 the counted handle
    uint32_t  mPad04[4];                        // +0x04 .. +0x13
    cNoun_s00b2_30b0*    mp14;                             // +0x14 the node's key payload
};
class cBucketMap {
public:
    uint32_t mPad00;                            // +0x00
    void*    mp04;                              // +0x04
    void*    mp08;                              // +0x08
    uint32_t mn0c;                              // +0x0c

    void FreeBucketNodes(void* pBegin, void* pEnd);         // 0x00b20a50
};
class cFlushList {
public:
    uint32_t mPad00[5];                         // +0x00 .. +0x13

    void FUN_00b21da0(void* pArg);                          // 0x00b21da0
};
class cGameNounManager_s00b2_30b0;
struct tPlanetEventMsg;
class cGNMPart {
public:
    uint32_t   mPad000[7];                      // +0x000 .. +0x01b
    cBucketMap mBucket1c;                       // +0x01c the class-set buckets
    uint32_t   mPad02c[4];                      // +0x02c .. +0x03b
    uint32_t   mn03c;                           // +0x03c message handler
    uint32_t   mn040;                           // +0x040
    uint32_t   mn044;                           // +0x044
    uint32_t   mn048;                           // +0x048
    uint32_t   mn04c;                           // +0x04c
    cAutoRef   mRef050;                         // +0x050
    cAutoRef   mRef054;                         // +0x054 the avatar's herd
    cRefVector mPosse058;                       // +0x058
    uint32_t   mPad064[2];                      // +0x064 .. +0x06b
    cAutoRef   mRef06c;                         // +0x06c
    cAutoRef   mRef070;                         // +0x070
    cListHead  mHead074;                        // +0x074
    cRefVector mVec07c;                         // +0x07c
    uint32_t   mPad088[2];                      // +0x088 .. +0x08f
    uint32_t   mn090;                           // +0x090
    cFlushList mFlush094;                       // +0x094
    uint32_t   mPad0a8[2];                      // +0x0a8 .. +0x0af
    uint32_t   mn0b0;                           // +0x0b0 flush list body
    uint32_t   mPad0b4[6];                      // +0x0b4 .. +0x0cb
    cRBTree    mTree0cc;                        // +0x0cc
    uint32_t   mPad0e4;                         // +0x0e4
    cRBTree    mTree0e8;                        // +0x0e8
    uint32_t   mPad100[2];                      // +0x100 .. +0x107
    cListHead  mHead108;                        // +0x108

    void FUN_00b237d0();                                    // 0x00b237d0
};
class cGameNounManager_s00b2_30b0 {
public:
    uint32_t  mn000;                            // +0x000
    cGNMPart  mPart;                            // +0x004

    void      RemoveNoun(cNoun_s00b2_30b0* pNoun);                     // 0x00b225d0
    void      ProcessPending();                             // 0x00b22960
    cNoun_s00b2_30b0*    CreateAndInit(void* pDesc, void* pA, void* pB, void* pC); // 0x00b22cc0
    cNoun_s00b2_30b0*    CreateNoun(uint32_t nClassId);                // 0x00b20c60
    cNoun_s00b2_30b0*    CreateDebugNoun(void* pPosition, cNoun_s00b2_30b0* pOwner);          // 0x00b20e40
    void*     FUN_00b21000(void* pA, void* pB);             // 0x00b21000
    void      ClearPosseMembers();                          // 0x00b234c0
    void      ValidateClassSets();                          // 0x00b222a0
    void      Flush();                                      // 0x00b206d0

    void      FUN_00b23450(cNoun_s00b2_30b0* pObject);                 // 0x00b23450
    void      FUN_00b23510();                               // 0x00b23510
    void      FUN_00b23610();                               // 0x00b23610
    cNoun_s00b2_30b0*    FUN_00b23650(void* pDesc, void* pB, void* pC, void* pD, void* pE); // 0x00b23650
    void*     FUN_00b23690(uint32_t nArg);                  // 0x00b23690
    cNoun_s00b2_30b0*    FUN_00b23940(float* pPosition, uint32_t nSpecies, uint32_t nGeneration,
                            uint8_t bOwner, float fHitpoint, uint8_t bDebug);     // 0x00b23940
    cNoun_s00b2_30b0*    FUN_00b23a40(uint32_t nID);                   // 0x00b23a40
    uint8_t   FUN_00b23ab0(uint32_t nMsgId, tPlanetEventMsg* pMsg);          // 0x00b23ab0
};
inline cGameNounManager_s00b2_30b0* ManagerOfPart(cGNMPart* pPart)
{
    return (cGameNounManager_s00b2_30b0*)((uint8_t*)pPart - 4);
}
class cObjectVector {
public:
    cRefObj** mpBegin;                          // +0x00
    cRefObj** mpEnd;                            // +0x04
    cRefObj** mpEndAlloc;                       // +0x08
};
class cVectorHolder {
public:
    uint32_t      mn000;                        // +0x00
    cObjectVector mVec;                         // +0x04
};
class cOrderVector {
public:
    void* volatile mpBegin;                     // +0x00
    void* volatile mpEnd;                       // +0x04
    void* volatile mpEndAlloc;                  // +0x08

    ~cOrderVector();                            // 0x00ae6930
};
class cCulturalConvertCityOrder;
class cMilitaryAttackCityOrder;
class cMilitaryAttackCityOrder {
public:
    void* volatile mpVtable00;                  // +0x000
    void* volatile mpVtable04;                  // +0x004
    uint32_t      mPad008[0x23];                // +0x008 .. +0x093
    void* volatile mp094;                       // +0x094
    uint32_t      mPad098;                      // +0x098
    cOrderVector  mVec09c;                      // +0x09c
    uint32_t      mPad0a8[2];                   // +0x0a8 .. +0x0af
    cOrderVector  mVec0b0;                      // +0x0b0

    void BaseCtor();                            // 0x00b22100 cVehicleGroupOrder::cVehicleGroupOrder
    void DtorBody();                            // 0x00b22180 its teardown body

    cMilitaryAttackCityOrder();                             // 0x00b231b0
    cMilitaryAttackCityOrder* FUN_00b23260(uint8_t nFlags); // 0x00b23260
};
class cCulturalConvertCityOrder {
public:
    void* volatile mpVtable00;                  // +0x000
    void* volatile mpVtable04;                  // +0x004
    uint32_t      mPad008[0x23];                // +0x008 .. +0x093
    void* volatile mp094;                       // +0x094
    uint32_t      mPad098;                      // +0x098
    cOrderVector  mVec09c;                      // +0x09c
    uint32_t      mPad0a8[2];                   // +0x0a8 .. +0x0af

    void BaseCtor();                            // 0x00b22100 cVehicleGroupOrder::cVehicleGroupOrder

    cCulturalConvertCityOrder()
    {
        BaseCtor();
        void* pNull = 0;
        mpVtable00 = &g_vtableConvertOrderPrimary;
        mpVtable04 = &g_vtableConvertOrderSecondary;
        mp094 = pNull;
        mVec09c.mpBegin = pNull;
        mVec09c.mpEnd = pNull;
        mVec09c.mpEndAlloc = pNull;
    }
};
cCulturalConvertCityOrder* FUN_00b23770();      // 0x00b23770
class cInteractable;
class cGonzagoSubsystem {
public:
    uint32_t mPad00[8];                         // +0x00 .. +0x1f

    void BaseCtor();                            // 0x00b5b960
};
union cListUnit {
    cListHead          mHead;                   // both words
    uint32_t volatile  mWords[2];               // the same two words seen as dwords
};
union cFlagWord {
    uint32_t volatile mnDword;
    uint8_t  volatile mnByte;
};
class cListenerBase {
public:
    void*     volatile mpVtable00;              // +0x000
    void*     volatile mpVtable04;              // +0x004
    void*     volatile mpVtable08;              // +0x008
    uint32_t  volatile mPad00c[6];              // +0x00c .. +0x023
    uint32_t  volatile mp024;                   // +0x024 the listener's name table
    uint32_t  volatile mn028;                   // +0x028
    uint32_t  volatile mn02c;                   // +0x02c
    float     volatile mf030;                   // +0x030
    float     volatile mf034;                   // +0x034
    uint32_t  volatile mn038;                   // +0x038
    uint32_t  volatile mPad03c;                 // +0x03c
    uint32_t  volatile mPad040[10];             // +0x040 .. +0x067
    uint32_t  volatile mPad068[2];              // +0x068 .. +0x06f
    uint32_t  volatile mn070;                   // +0x070
    uint32_t  volatile mn074;                   // +0x074
    cListUnit          mUnit078;                // +0x078
    uint32_t  volatile mn080;                   // +0x080
    uint32_t  volatile mn084;                   // +0x084
    uint32_t  volatile mn088;                   // +0x088
    uint32_t  volatile mPad08c[2];              // +0x08c .. +0x093
    uint32_t  volatile mn094;                   // +0x094
    uint32_t  volatile mPad098;                 // +0x098
    cListUnit          mUnit09c;                // +0x09c
    cFlagWord          mFlag0a4;                // +0x0a4
    cFlagWord          mFlag0a8;                // +0x0a8
    uint32_t  volatile mn0ac;                   // +0x0ac
    uint32_t  volatile mPad0b0[2];              // +0x0b0 .. +0x0b7
    cListUnit          mUnit0b8;                // +0x0b8
    uint32_t  volatile mn0c0;                   // +0x0c0
    cFlagWord          mFlag0c4;                // +0x0c4
    uint32_t  volatile mn0c8;                   // +0x0c8
    uint32_t  volatile mPad0cc;                 // +0x0cc .. +0x0cf
    cRBTree            mTree0d0;                // +0x0d0 .. +0x0e7
    uint32_t  volatile mPad0e8[2];              // +0x0e8 .. +0x0ef
    cListUnit          mUnit0f0;                // +0x0f0
    uint32_t  volatile mn0f8;                   // +0x0f8
    cFlagWord          mFlag0fc;                // +0x0fc
    uint32_t  volatile mn100;                   // +0x100
    uint32_t  volatile mPad104;                 // +0x104
    uint32_t  volatile mn108;                   // +0x108
    cListUnit          mUnit10c;                // +0x10c
    uint32_t  volatile mPad114;                 // +0x114
    uint32_t  volatile mn118;                   // +0x118

    cListenerBase();                                        // 0x00b232b0
    void FUN_00b23560(cInteractable* pObject);              // 0x00b23560
};
struct tVec3 {
    float x;                                    // +0x00
    float y;                                    // +0x04
    float z;                                    // +0x08
};
class cPlanetModel {
public:
    uint32_t mPad00[9];                         // +0x000 .. +0x023
    void*    mp024;                             // +0x024 the terrain sphere

    tVec3* DirectionToSurfacePosition(tVec3* pOut, const tVec3& vDir);  // 0x00b815a0
};
class cInteractable {
public:
    virtual void* v00();                        // +0x000
    virtual void* v04();                        // +0x004
    virtual void* v08();                        // +0x008
    virtual void* v0c();                        // +0x00c
    virtual void* v10();                        // +0x010
    virtual void* v14();                        // +0x014
    virtual void* v18();                        // +0x018
    virtual void* v1c();                        // +0x01c
    virtual void* v20();                        // +0x020
    virtual void* v24();                        // +0x024
    virtual void* v28();                        // +0x028
    virtual void* v2c();                        // +0x02c the object's position
    virtual void* v30();                        // +0x030
    virtual void* v34();                        // +0x034
    virtual void* v38();                        // +0x038
    virtual void* v3c();                        // +0x03c
    virtual void* v40();                        // +0x040
    virtual void* v44();                        // +0x044
    virtual void* v48();                        // +0x048
    virtual void* v4c();                        // +0x04c the object's id
    virtual void* v50();                        // +0x050
    virtual void* v54();                        // +0x054
    virtual void* v58();                        // +0x058
    virtual void* v5c();                        // +0x05c
    virtual void* v60();                        // +0x060
    virtual void* v64();                        // +0x064
    virtual void* v68();                        // +0x068
    virtual void* v6c();                        // +0x06c
    virtual void* v70();                        // +0x070
    virtual void* v74();                        // +0x074
    virtual void* v78();                        // +0x078
    virtual void* v7c();                        // +0x07c
    virtual void  v80();                        // +0x080 wake the object
    virtual void* v84();                        // +0x084
    virtual void* v88();                        // +0x088
    virtual void* v8c();                        // +0x08c
    virtual void* v90();                        // +0x090
    virtual void* v94();                        // +0x094
    virtual void* v98();                        // +0x098
    virtual void* v9c();                        // +0x09c
    virtual void* va0();                        // +0x0a0
    virtual void* va4();                        // +0x0a4
    virtual void* va8();                        // +0x0a8
    virtual void* vac();                        // +0x0ac
    virtual void* vb0();                        // +0x0b0
    virtual void* vb4();                        // +0x0b4
    virtual void* vb8(uint32_t nKey);           // +0x0b8
};
struct tPlanetEventMsg {
    uint32_t mn00;                              // +0x00
    uint32_t mn04;                              // +0x04
    float    mf08;                              // +0x08
    uint32_t mn0c;                              // +0x0c
    float    mf10;                              // +0x10
    uint32_t mn14;                              // +0x14
    float    mf18;                              // +0x18
    uint32_t mn1c;                              // +0x1c
    float    mf20;                              // +0x20
    uint32_t mn24;                              // +0x24
    uint32_t mn28;                              // +0x28
};
class cEAString {
public:
    uint8_t* mpBegin;                           // +0x00
    uint8_t* mpEnd;                             // +0x04
    uint8_t* mpEndAlloc;                        // +0x08
    uint32_t mPad0c;                            // +0x0c
    uint8_t* mpInline;                          // +0x10

    void resize(uint32_t nSize);                // 0x00b20610
    void Assign(const cEAString& pOther);       // 0x00b20c00
    void swap(cEAString& pOther);               // 0x00b22060
    void FUN_00b230b0(uint32_t nSize);          // 0x00b230b0
};
class cGNMThunk {
public:
    uint32_t mPad00;                            // +0x00

    void FUN_00b23640(uint32_t nA, uint32_t nB);            // 0x00b23640
};
// ---- items of slice s00b230b0 end

// ---- items of slice s00b23e60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gEmptyString8[1];                                             // 0x01667bac
extern const char gAllocatorName[];                                       // 0x013ebb38
void* operator_new(uint32_t nSize, const char* pFile, uint32_t nA,
                   uint32_t nB, const char* pAllocator, uint32_t nLine);  // 0x00f473a0
class cEAString8 {
public:
    cEAString8() { mpBegin = gEmptyString8; mpEnd = gEmptyString8 + 1; }
    cEAString8(const char* pStr);
    cEAString8(const cEAString8& src);
    ~cEAString8()
    {
        if (mpEnd - mpBegin > 1 && mpBegin != 0)
            operator_delete((void*)mpBegin);
    }

    const char* mpBegin;                                        // 0x00
    const char* mpEnd;                                          // 0x04
};
cEAString8::cEAString8(const char* pStr)
{
    uint32_t nLen = 0;
    while (pStr[nLen] != '\0')
        ++nLen;
    if (nLen + 1 > 1) {
        char* pBuffer = (char*)operator_new(nLen + 1, "Simulator", 0, 0,
                                           gAllocatorName, 0xd1);
        mpBegin = pBuffer;
        mpEnd = pBuffer + nLen + 1;
    } else {
        mpBegin = gEmptyString8;
        mpEnd = gEmptyString8 + 1;
    }
    memcpy((void*)mpBegin, pStr, nLen);
    *(char*)(mpEnd - 1) = '\0';
}
cEAString8::cEAString8(const cEAString8& src)
{
    uint32_t nLen = (uint32_t)(src.mpEnd - src.mpBegin) - 1;
    if (nLen + 1 > 1) {
        char* pBuffer = (char*)operator_new(nLen + 1, "Simulator", 0, 0,
                                           gAllocatorName, 0xd1);
        mpBegin = pBuffer;
        mpEnd = pBuffer + nLen + 1;
    } else {
        mpBegin = gEmptyString8;
        mpEnd = gEmptyString8 + 1;
    }
    memcpy((void*)mpBegin, src.mpBegin, nLen);
    *(char*)(mpEnd - 1) = '\0';
}
class cNounTypeRegistry {
public:
    void AddNounType(const cEAString8* pName, uint32_t nFlags,
                     uint32_t nUnk);                             // 0x00b1aba0
};
class cNounTypeTable {
public:
    uint32_t FindNounType(const cEAString8* pName);               // 0x00b209f0
    void SetNounTypeName(const cEAString8* pName, uint32_t nFound,
                         uint32_t nFlags);                        // 0x00b23020
};
extern cNounTypeRegistry gNounTypeRegistry;                       // 0x01568514
extern cNounTypeTable gNounTypeTable;                             // 0x0156851c
// ---- items of slice s00b23e60 end

// ---- items of slice s00b25c30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_uiModeToken;                 // 0x0167e04c (set to 6 when a UI mode is entered)
extern int32_t  g_modeArg;                     // 0x0167dfa8 (passed by address to the mode switch)
extern const uint32_t g_timelineEvents[];      // 0x0145f82c (three registered event ids)
extern uint32_t g_classRegistryGuard;          // 0x0167c3c0 (one bit per lazily built registry)
extern "C" unsigned __int64 __rdtsc(void);
#pragma intrinsic(__rdtsc)
struct cSPVector3_s00b2_5c30 {
    float x, y, z;
};
int   __cdecl FUN_011e07ef(void (__cdecl* pfn)(void));           // 0x011e07ef lib_crt::atexit
void* __cdecl EA_Messaging_GetServer();                          // 0x00883860
class cGameData_s00b2_5c30;
struct tGameDataVector {
    uint32_t    mPad00;                 // +0x00
    cGameData_s00b2_5c30** mpBegin;                // +0x04
    cGameData_s00b2_5c30** mpEnd;                  // +0x08
    uint32_t    mPad0c;                 // +0x0c
};
typedef tGameDataVector* (__cdecl* tVectorCreateFn)(void);
typedef void (__cdecl* tVectorClearFn)(tGameDataVector*);
typedef void (__cdecl* tVectorAddFn)(tGameDataVector*, cGameData_s00b2_5c30*);
typedef bool (__cdecl* tVectorMatchFn)(cGameData_s00b2_5c30*, uint32_t);
class cLocatable {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
    virtual const cSPVector3_s00b2_5c30* GetPosition();                     // +0x2c
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
    virtual bool IsActive();                                     // +0x58
};
class cGameData_s00b2_5c30 {
public:
    virtual void v00();
    virtual void Release();                                      // +0x04
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
virtual void v0b();
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
    virtual uint32_t GetPoliticalID();                           // +0x4c
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v1a();
virtual void v1b();
virtual void v1c();
virtual void v1d();
virtual void v1e();
virtual void v1f();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v2a();
virtual void v2b();
virtual void v2c();
virtual void v2d();
    virtual cGameData_s00b2_5c30* Cast(uint32_t typeID);                    // +0xb8
    uint32_t pad04[(0x120 - 0x04) / 4];                          // +0x04
    cLocatable mLocation;                                        // +0x120
    uint32_t pad124[(0x714 - 0x124) / 4];                        // +0x124
    int32_t  mObjectState;                                       // +0x714
    uint32_t pad718[(0xb58 - 0x718) / 4];                        // +0x718
    uint32_t mFlagsB58;                                          // +0xb58 (0x100 = in a posse)
    void ClearPosseMemberFlag()                                  // inline in the original
    {
        mFlagsB58 &= ~0x100u;
    }
};
class cEmpire {
public:
    uint32_t mPad00[0x84 / 4];                                   // +0x00
    uint32_t mCivilizationID;                                    // +0x84
};
cEmpire* GetPlayerEmpire();                                      // 0x01021300
class cRefCounted {
public:
    virtual void AddRef();                                       // +0x00
    virtual void Release();                                      // +0x04
    virtual void Activate(int a);                                // +0x08
    virtual void Dismiss(int a);                                 // +0x0c
};
struct tAutoRefCount {
    cRefCounted* mpObject;                                       // +0x00
    ~tAutoRefCount()                                             // inline in the original
    {
        if (mpObject != 0)
            mpObject->Release();
    }
    void Reset()                                                 // inline in the original
    {
        if (mpObject != 0) {
            cRefCounted* pOld = mpObject;
            mpObject = 0;
            pOld->Release();
        }
    }
};
struct tNounVector {
    cGameData_s00b2_5c30** mpBegin;                // +0x00
    cGameData_s00b2_5c30** mpEnd;                  // +0x04
    cGameData_s00b2_5c30** mpCapacity;             // +0x08
    uint32_t    mPad0c;                 // +0x0c
    uint32_t    mPad10;                 // +0x10
};
struct tRBNode {
    tRBNode* mpLeft;                    // +0x00
    tRBNode* mpRight;                   // +0x04
    tRBNode* mpParent;                  // +0x08
    uint8_t  mColor;                    // +0x0c
    uint8_t  mPad0d[3];                 // +0x0d
};
struct tRBTree {
    uint32_t mPad00;                    // +0x00
    tRBNode  mAnchor;                   // +0x04
    uint32_t mnSize;                    // +0x14
    void FUN_00d0c930(tRBNode* pRoot);  // 0x00d0c930 (destroy the subtree below pRoot)
    void swap(tRBTree& other);          // 0x00b21da0
    void clear()                        // inline: retail inlines it at both call sites
    {
        FUN_00d0c930(mAnchor.mpParent);
        mAnchor.mpLeft = &mAnchor;
        mAnchor.mpRight = &mAnchor;
        mAnchor.mpParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
};
struct tNounMap {
    uint32_t mPad00;                    // +0x00
    tRBTree  mTree;                     // +0x04
};
struct tNounManagerHandler {
    void*    mpServer;                  // +0x00
    void*    mpOwner;                   // +0x04
    const uint32_t* mpEventNames;       // +0x08
    uint32_t mEventCount;               // +0x0c
    uint32_t mPad10;                    // +0x10
};
class cGameNounManager_s00b2_5c30;
class cNounManagerMessaging;                                     // sub-object at cGameNounManager+0x04
class cGameNounManager_s00b2_5c30 {
public:
    uint32_t mPad00[0x40 / 4];                   // +0x00 (vptr, definition map)
    tNounManagerHandler mAutoHandler;           // +0x40
    tAutoRefCount mAvatar;                      // +0x54
    tAutoRefCount mAvatarHerd;                  // +0x58
    tNounVector   mPosseMembers;                // +0x5c
    tAutoRefCount mPlayerTribe;                 // +0x70
    tAutoRefCount mpPlayer;                     // +0x74
    void*         mNounListNext;                // +0x78 (intrusive list anchor)
    void*         mNounListPrev;                // +0x7c
    tNounVector   mTempNouns;                   // +0x80
    tNounMap      mGameDataVectorMap;           // +0x94
    tNounMap      mGameDataVectorMapDeleted;    // +0xb0
    tNounMap      mPoliticalMap;                // +0xcc
    tNounMap      mPlanetaryContextPoliticalMap; // +0xe8
    uint32_t      mLastPoliticalID;             // +0x104
    uint32_t      mPad108[(0x118 - 0x108) / 4]; // +0x108 (pending list, damage display)

    tGameDataVector* GetGameDataVector(tVectorCreateFn fnCreate, tVectorClearFn fnClear,
                                       tVectorAddFn fnAdd, tVectorMatchFn fnMatch,
                                       uint32_t classID);        // 0x00b21340
    void FUN_00b21410(cGameData_s00b2_5c30* pNoun);                         // 0x00b21410
    void FUN_00b215a0();                                         // 0x00b215a0
    void RegisterNounClasses();                                  // 0x00b24740
    void FUN_00692850();                                         // 0x00692850
    bool IsRegistered();                                         // 0x00ab30c0
    void RemoveNoun(cGameData_s00b2_5c30* pNoun);                           // 0x00b225d0
    void RemoveNounsOfType(uint32_t classID);                    // 0x00b22650
    void ProcessPending();                                       // 0x00b22960
    void ValidateClassSets();                                    // 0x00b222a0
    void Flush();                                                // 0x00b206d0
    void ClearPosseMembers();                                    // 0x00b234c0
    cGameData_s00b2_5c30* FindNounByEmpireID(uint32_t civID);               // 0x00b25f40
    class cCivilization* GetPlayerCivilization();                // 0x00b25fb0
    class cCity* GetPlayerCityAtPosition(const cSPVector3_s00b2_5c30& position); // 0x00b262c0
    cGameData_s00b2_5c30* FUN_00b25c30();
    void FUN_00b25ee0();
    void FUN_00b25fe0();
    void FUN_00b26320();
    void FUN_00b26600();
};
cGameNounManager_s00b2_5c30* GetStaticObj();                                // 0x00b22210
void RegisterDramaEventsFactories();                             // 0x00d4b5a0
void FUN_00b23c60(uint32_t classID, const char* pClassName);     // 0x00b23c60
void FUN_00b25cd0();                                             // 0x00b25cd0
void FUN_0102c340(cGameData_s00b2_5c30* pNoun, int a);                      // 0x0102c340
void __cdecl FUN_013c2030(void);                                 // 0x013c2030 (registry destructors)
void __cdecl FUN_013c2020(void);                                 // 0x013c2020
void __cdecl FUN_013c2010(void);                                 // 0x013c2010
void __cdecl FUN_013c2000(void);                                 // 0x013c2000
class cRegNode {
public:
    cRegNode* Construct(void* pArg);                             // 0x00692f60
    bool IsRegistered();                                         // 0x00ab30c0
    void Build();                                                // 0x00692850
    uint32_t mVtbl;                                              // +0x00
};
extern cRegNode g_classRegistry0;                                // 0x0167c3ac
extern cRegNode g_classRegistry1;                                // 0x0167c398
extern cRegNode g_classRegistry2;                                // 0x0167c384
extern cRegNode g_classRegistry3;                                // 0x0167c370
inline void InitClassRegistry(cRegNode* pNode, uint32_t maskBit, uint32_t vtable,
                              void (__cdecl* pDestructor)())
{
    if ((g_classRegistryGuard & maskBit) == 0) {
        g_classRegistryGuard |= maskBit;
        pNode->Construct(0);
        pNode->mVtbl = vtable;
        FUN_011e07ef(pDestructor);
    }
    if (!pNode->IsRegistered())
        pNode->Build();
}
class cMessagingListener {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual void v08();
    virtual void AddHandler(void* pOwner, uint32_t eventID);     // +0x24
};
class cNounManagerMessaging {
public:
    cGameNounManager_s00b2_5c30* Owner()
    {
        return (cGameNounManager_s00b2_5c30*)((char*)this - 4);
    }
    void FUN_00b25e80();
    uint32_t mPad00[(0x3c - 0x00) / 4];  // +0x00
    void*    mpMessageServer;            // +0x3c
    void*    mpOwner;                    // +0x40
    const uint32_t* mpEventNames;        // +0x44 (0x0145f82c, three ids)
    uint32_t mEventCount;                // +0x48
    uint32_t mPad4c;                     // +0x4c
};
class cCivilization;
class cCity;
class cCivilizationBase {
public:
    int    GetCityCount();                                       // 0x00bf01e0
    cCity* GetCityNearestTo(const cSPVector3_s00b2_5c30& position, int a);  // 0x00befee0
};
class cCivilization : public cCivilizationBase {
public:
    bool CanReach(const cSPVector3_s00b2_5c30& position);                   // 0x00bd9c00
};
class cCity {
public:
    bool CanReach(const cSPVector3_s00b2_5c30& position);                   // 0x00bd9c00
};
class cGroundEditor {
public:
    void* GetContainer();                                        // 0x00ac79d0
    void  DrainNouns(void* pContainer);                          // 0x00ac7a40
};
class cGroundEditorSource {
public:
    cGroundEditor* GetEditor();                                  // 0x00b3d2b0
};
cGroundEditorSource* FUN_00b3d2b0();                             // 0x00b3d2b0
class cModeOwner {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
    virtual void SetModeArgument(void* pArgument);                // +0x10
};
class cTimelineModeStarter {
public:
    cModeOwner* mpModeOwner;                                     // +0x00
    void FUN_00b26710();
};
// ---- items of slice s00b25c30 end

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

// @ 0x00b21da0
void ListSeg::FUN_00b21da0(ListSeg* other)
{
  void* t = mField14;
  mField14 = other->mField14;
  other->mField14 = t;
  if (mField0c != 0) {
    if (other->mField0c != 0) {
      void* a = mField04; mField04 = other->mField04; other->mField04 = a;
      void* b = mField08; mField08 = other->mField08; other->mField08 = b;
      void* c = mField0c; mField0c = other->mField0c; other->mField0c = c;
      ((ListNode_s00b2_0fb0*)mField0c)->mField08 = &mField04;
      ((ListNode_s00b2_0fb0*)other->mField0c)->mField08 = &other->mField04;
      return;
    }
    if (mField0c != 0) {
      other->mField04 = mField04;
      other->mField08 = mField08;
      void* c = mField0c;
      other->mField0c = c;
      ((ListNode_s00b2_0fb0*)c)->mField08 = &other->mField04;
      mField0c = 0;
      mField04 = &mField04;
      mField08 = &mField04;
      return;
    }
  }
  if (other->mField0c != 0) {
    mField04 = other->mField04;
    mField08 = other->mField08;
    void* c = other->mField0c;
    mField0c = c;
    ((ListNode_s00b2_0fb0*)c)->mField08 = &mField04;
    other->mField04 = &other->mField04;
    other->mField0c = 0;
    other->mField08 = &other->mField04;
  }
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

// @ 0x00b230b0
void cEAString::FUN_00b230b0(uint32_t nSize)
{
    if (nSize != 0xffffffff && nSize > (uint32_t)(mpEnd - mpBegin))
    {
        uint8_t* pNew = (uint8_t*)EASTL_allocate(nSize, "Simulator", 0, 0,
                                                 "EASTL/allocator.h", 0xd1);
        uint32_t nOld = (uint32_t)(mpEnd - mpBegin);
        SP_memcpy(pNew, mpBegin, nOld);
        uint8_t* pNewEnd = pNew + nOld;
        *pNewEnd = 0;
        if ((int32_t)(mpEndAlloc - mpBegin) > 1 && mpBegin != 0 && mpBegin != mpInline)
            operator_delete(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpEndAlloc = pNew + nSize;
        return;
    }
    if (nSize < (uint32_t)(mpEnd - mpBegin))
        resize(nSize);
    cEAString tmp;
    tmp.Assign(*this);
    swap(tmp);
    if ((int32_t)(tmp.mpEndAlloc - tmp.mpBegin) > 1 && tmp.mpBegin != 0
        && tmp.mpBegin != tmp.mpInline)
        operator_delete(tmp.mpBegin);
}

// @ 0x00b231b0
cMilitaryAttackCityOrder::cMilitaryAttackCityOrder()
{
    BaseCtor();
    mpVtable00 = &g_vtableMACOrderPrimary;
    mpVtable04 = &g_vtableMACOrderSecondary;
    mp094 = 0;
    mVec09c.mpBegin = 0;
    mVec09c.mpEnd = 0;
    mVec09c.mpEndAlloc = 0;
    mVec0b0.mpBegin = 0;
    mVec0b0.mpEnd = 0;
    mVec0b0.mpEndAlloc = 0;
}

// @ 0x00b23260
cMilitaryAttackCityOrder* cMilitaryAttackCityOrder::FUN_00b23260(uint8_t nFlags)
{
    mVec0b0.~cOrderVector();
    mVec09c.~cOrderVector();
    cRefObj* pRef = (cRefObj*)mp094;
    if (pRef != 0)
        pRef->v04();
    DtorBody();
    if ((nFlags & 1) != 0)
        operator_delete(this);
    return this;
}

// @ 0x00b232b0
cListenerBase::cListenerBase()
{
    cGonzagoSubsystem* pSubsystem = (cGonzagoSubsystem*)((uint8_t*)this + 4);
    mpVtable00 = &g_vtableListenerA;
    pSubsystem->BaseCtor();

    mpVtable04 = &g_vtableListenerGonzago;
    mpVtable00 = &g_vtableListenerPrimary;
    mpVtable08 = &g_vtableListenerTail;

    mf030 = 1.0f;
    mf034 = 2.0f;
    mn02c = 0;
    mn038 = 0;
    mn028 = 1;
    mp024 = (uint32_t)&g_listenerNameTable;

    mPad040[0] = 0;
    mPad040[1] = 0;
    mPad040[2] = 0;
    mPad040[3] = 0;
    mPad040[4] = 0;
    mPad040[5] = 0;
    mPad040[6] = 0;
    mPad040[7] = 0;
    mPad040[8] = 0;
    mPad040[9] = 0;
    mn070 = 0;
    mn074 = 0;

    mUnit078.mHead.InitReversed();
    mn080 = 0;
    mn084 = 0;
    mn088 = 0;
    mn094 = 0;

    mUnit09c.mWords[1] = 0;
    mFlag0a4.mnDword = 0;
    mFlag0a8.mnDword = 0;
    mFlag0a4.mnDword = 0;
    mFlag0a8.mnByte = 0;
    mn0ac = 0;
    mUnit09c.mWords[0] = (uint32_t)&mUnit09c.mHead;
    mUnit09c.mWords[1] = (uint32_t)&mUnit09c.mHead;

    mUnit0b8.mWords[1] = 0;
    mn0c0 = 0;
    mFlag0c4.mnDword = 0;
    mn0c0 = 0;
    mFlag0c4.mnByte = 0;
    mn0c8 = 0;
    mUnit0b8.mWords[0] = (uint32_t)&mUnit0b8.mHead;
    mUnit0b8.mWords[1] = (uint32_t)&mUnit0b8.mHead;

    mTree0d0.mp08 = 0;
    mTree0d0.mp0c = 0;
    mTree0d0.mn10Word = 0;
    mTree0d0.mp04 = (void*)&mTree0d0.mp04;
    mTree0d0.mp08 = (void*)&mTree0d0.mp04;
    mTree0d0.mp0c = 0;
    mTree0d0.mb10 = 0;
    mTree0d0.mn14 = 0;

    mUnit0f0.mWords[1] = 0;
    mn0f8 = 0;
    mFlag0fc.mnDword = 0;
    mUnit0f0.mWords[0] = (uint32_t)&mUnit0f0.mHead;
    mUnit0f0.mWords[1] = (uint32_t)&mUnit0f0.mHead;
    mn0f8 = 0;
    mFlag0fc.mnByte = 0;
    mn100 = 0;

    mn108 = 0;
    mUnit10c.mHead.Init();
    mn118 = 0;
}

// @ 0x00b23450
void cGameNounManager_s00b2_30b0::FUN_00b23450(cNoun_s00b2_30b0* pObject)
{
    if (pObject == 0)
        return;
    pObject->mn0b58 |= 0x100;
    cAutoRef ref(pObject);
    mPart.mPosse058.push_back(ref);
}

// @ 0x00b234c0
void cGameNounManager_s00b2_30b0::ClearPosseMembers()
{
    cRefVector* pPosse = &mPart.mPosse058;
    int32_t nCount = (int32_t)(pPosse->mpEnd - pPosse->mpBegin);
    int32_t i = 0;
    while (i < nCount)
    {
        cNoun_s00b2_30b0* pMember = pPosse->mpBegin[i].mpObject;
        pMember->mn0b58 &= 0xfffffeff;
        ++i;
    }
    pPosse->erase(pPosse->mpBegin, pPosse->mpEnd);
}

// @ 0x00b23510
void cGameNounManager_s00b2_30b0::FUN_00b23510()
{
    cNoun_s00b2_30b0* pOld = mPart.mRef054.mpObject;
    if (pOld == 0)
        return;
    RemoveNoun(pOld);
    if (mPart.mRef054.mpObject == pOld)
        mPart.mRef054 = (cNoun_s00b2_30b0*)0;
    mPart.mRef054 = (cNoun_s00b2_30b0*)0;
}

// @ 0x00b23560
void cListenerBase::FUN_00b23560(cInteractable* pObject)
{
    uint32_t nKey = (uint32_t)pObject->v4c();
    if (nKey == 0xffffffff)
        return;

    cRefNode* pNode;
    mTree0d0.find((void**)&pNode, &nKey);
    if (pNode != (cRefNode*)&mTree0d0.mp04)
    {
        if (ClassifyA(pObject) > ClassifyA(pNode->mp14))
            mTree0d0.insert(&nKey)->Set((cNoun_s00b2_30b0*)pObject);
    }
    else
    {
        cRefNode* pNew = (cRefNode*)mTree0d0.insert(&nKey);
        pNew->mObject = (cNoun_s00b2_30b0*)pObject;
    }
}

// @ 0x00b23610
void cGameNounManager_s00b2_30b0::FUN_00b23610()
{
    cNoun_s00b2_30b0* pOld = mPart.mRef070.mpObject;
    if (pOld == 0)
        return;
    RemoveNoun(pOld);
    ProcessPending();
    mPart.mRef070 = (cNoun_s00b2_30b0*)0;
}

// @ 0x00b23640
void cGNMThunk::FUN_00b23640(uint32_t nA, uint32_t nB)
{
    cGameNounManager_s00b2_30b0* pManager = (cGameNounManager_s00b2_30b0*)((uint8_t*)this - 4);
    pManager->ProcessPending();
}

// @ 0x00b23650
cNoun_s00b2_30b0* cGameNounManager_s00b2_30b0::FUN_00b23650(void* pDesc, void* pB, void* pC, void* pD, void* pE)
{
    void* pFound = FUN_00b21000(pDesc, pB);
    return pFound != 0 ? CreateAndInit(pFound, pC, pD, pE) : 0;
}

// @ 0x00b23690
void* cGameNounManager_s00b2_30b0::FUN_00b23690(uint32_t nArg)
{
    cVectorHolder* pHolder = (cVectorHolder*)GetGameDataVector(
        &g_funB21080, &g_funB22E80, &g_funB22EA0, &g_funB1E520, (void*)nArg);
    return &pHolder->mVec;
}

// @ 0x00b23770
cCulturalConvertCityOrder* FUN_00b23770()
{
    return new ("Simulator/cCulturalConvertCityOrder", 0, 0, 0, 0) cCulturalConvertCityOrder;
}

// @ 0x00b237d0
void cGNMPart::FUN_00b237d0()
{
    cGameNounManager_s00b2_30b0* pManager = ManagerOfPart(this);

    if (mn03c != 0)
    {
        uint32_t nHandler = mn03c;
        mn03c = 0;
        EA_Messaging_RemoveHandler(nHandler, mn040, mn044, mn048, mn04c);
    }
    mRef050 = (cNoun_s00b2_30b0*)0;
    mRef054 = (cNoun_s00b2_30b0*)0;
    pManager->ClearPosseMembers();
    mRef06c = (cNoun_s00b2_30b0*)0;

    cNoun_s00b2_30b0* pOld = mRef070.mpObject;
    if (pOld != 0)
    {
        pManager->RemoveNoun(pOld);
        pManager->ProcessPending();
        mRef070 = (cNoun_s00b2_30b0*)0;
    }

    mTree0cc.clear();
    mTree0e8.clear();

    mBucket1c.FreeBucketNodes(mBucket1c.mp04, mBucket1c.mp08);
    mBucket1c.mn0c = 0;
    pManager->ValidateClassSets();

    mHead074.ClearNodes();
    mVec07c.erase(mVec07c.mpBegin, mVec07c.mpEnd);
    pManager->Flush();
    mFlush094.FUN_00b21da0(&mn0b0);
    pManager->Flush();
    mFlush094.FUN_00b21da0(&mn0b0);
    mHead108.ClearNodes();
}

// @ 0x00b23940
cNoun_s00b2_30b0* cGameNounManager_s00b2_30b0::FUN_00b23940(float* pPosition, uint32_t nSpecies, uint32_t nGeneration, uint8_t bOwner, float fHitpoint, uint8_t bDebug)
{
    if (nSpecies == 0)
        return 0;

    cNoun_s00b2_30b0* pNoun = CreateNoun(0x1be418e);
    pNoun->mn0f4 = nGeneration;
    pNoun->mn15c = *(uint32_t*)&fHitpoint;
    pNoun->mn0a4 = nSpecies;
    pNoun->mf34 = pPosition[0];
    pNoun->mf38 = pPosition[1];
    pNoun->mf3c = pPosition[2];
    pNoun->mb084 = bOwner;

    if (bDebug != 0)
    {
        cNoun_s00b2_30b0* pDebug = CreateDebugNoun(pPosition, pNoun);
        if (pDebug != (cNoun_s00b2_30b0*)pNoun->mp160)
        {
            if (pDebug != 0)
                pDebug->v00();
            ((cAutoRef*)&pNoun->mp160)->mpObject = pDebug;
            if (pNoun->mp160 != 0)
                ((cNoun_s00b2_30b0*)pNoun->mp160)->v04();
        }
    }

    pNoun->v54();

    if (bOwner != 0)
    {
        if (mPart.mRef054.mpObject != 0)
            FUN_00b23510();
        mPart.mRef054 = pNoun;
    }

    void* pMode = GetCurrentGameMode_s00b2_30b0();
    if (pMode == &g_gameModeAssembling || pMode == &g_gameModeAdventuring)
        FUN_00c6ace0(pNoun, 0);

    return pNoun;
}

// @ 0x00b23a40
cNoun_s00b2_30b0* cGameNounManager_s00b2_30b0::FUN_00b23a40(uint32_t nID)
{
    cVectorHolder* pHolder = (cVectorHolder*)GetGameDataVector(
        &g_funCD7D10, &g_funD3D420, &g_funACCBB0, &g_funB1E500, &g_classKey18c6d19);
    cObjectVector* pVector = &pHolder->mVec;
    uint32_t nCount = (uint32_t)(pVector->mpEnd - pVector->mpBegin);
    for (uint32_t i = 0; i < nCount; ++i)
    {
        cNoun_s00b2_30b0* pNoun = (cNoun_s00b2_30b0*)pVector->mpBegin[i];
        if ((uint32_t)pNoun->v4c() == nID)
            return pNoun;
    }
    return 0;
}

// @ 0x00b23ab0
uint8_t cGameNounManager_s00b2_30b0::FUN_00b23ab0(uint32_t nMsgId, tPlanetEventMsg* pMsg)
{
    if (nMsgId == 0xf62def)
    {
        if (*(const uint32_t*)&pMsg->mf10 == 0x2e9c426)
            FUN_00b215a0();
        return 0;
    }
    if (nMsgId != 0x182c582)
        return 0;

    cPlanetModel* pModel = (cPlanetModel*)PlanetModel();
    if (pModel == 0 || pModel->mp024 == 0)
        return 0;

    tVec3 vPosition;
    vPosition.x = pMsg->mf08;
    vPosition.y = pMsg->mf10;
    vPosition.z = pMsg->mf18;
    if (vPosition.x * vPosition.x + vPosition.z * vPosition.z + vPosition.y * vPosition.y > 0.001f)
    {
        tVec3 vSurface;
        tVec3* pSurface = pModel->DirectionToSurfacePosition(&vSurface, vPosition);
        vPosition.x = pSurface->x;
        vPosition.y = pSurface->y;
        vPosition.z = pSurface->z;
    }

    float fRadius = pMsg->mf20;
    float fRadiusSq = fRadius * fRadius;
    uint32_t nValue = pMsg->mn28;

    cObjectVector* pVector = (cObjectVector*)this->FUN_00b23690(0x1186577);
    for (cRefObj** ppObject = pVector->mpBegin; ppObject != pVector->mpEnd; ++ppObject)
    {
        cInteractable* pObject = (cInteractable*)*ppObject;
        if (pObject == 0)
            continue;
        if (pObject->vb8(0x17f243b) != 0)
        {
            if (pObject->v2c())
                continue;
        }
        tVec3* pObjectPos = (tVec3*)pObject->v2c();
        float dx = pObjectPos->x - vPosition.x;
        float dy = pObjectPos->y - vPosition.y;
        float dz = pObjectPos->z - vPosition.z;
        if (fRadiusSq > dz * dz + dy * dy + dx * dx)
            pObject->v80();
    }

    this->mPart.mn090 = nValue;
    return 0;
}

// @ 0x00b23e60
void RegisterNounType(uint32_t nId, uint32_t nFlags, const char* pName)
{
    cEAString8 name(pName);
    cEAString8 copy(name);
    gNounTypeRegistry.AddNounType(&copy, nId, nFlags);

    cEAString8 name2(pName);
    cEAString8 copy2(name2);
    gNounTypeRegistry.AddNounType(&copy2, nFlags, nId);

    cEAString8 name3(pName);
    uint32_t nFound = gNounTypeTable.FindNounType(&name3);
    gNounTypeTable.SetNounTypeName(&name3, nFound, nId);

    cEAString8 name4(pName);
    uint32_t nFound2 = gNounTypeTable.FindNounType(&name4);
    gNounTypeTable.SetNounTypeName(&name4, nFound2, nFlags);
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

// @ 0x00b25c30
cGameData_s00b2_5c30* cGameNounManager_s00b2_5c30::FUN_00b25c30()
{
    tGameDataVector* pVector = GetGameDataVector((tVectorCreateFn)0x00cd7d10, (tVectorClearFn)0x00d3d420,
                                                 (tVectorAddFn)0x00acdff0, (tVectorMatchFn)0x00b1e500,
                                                 0x018c43e8);
    uint32_t count = (uint32_t)(pVector->mpEnd - pVector->mpBegin);
    for (uint32_t i = 0; i < count; ++i) {
        if (pVector->mpBegin[i]->mLocation.IsActive())
            return pVector->mpBegin[i];
    }
    return 0;
}

// @ 0x00b25cd0
void FUN_00b25cd0()
{
    GetStaticObj()->RegisterNounClasses();
    GetStaticObj()->FUN_00692850();
    RegisterDramaEventsFactories();
    InitClassRegistry(&g_classRegistry0, 1, 0x0145ea00, FUN_013c2030);
    FUN_00b23c60(0x01186577, "cSpatialObject");
    FUN_00b23c60(0xef3da0d7, "cCreatureTribeMember");
    FUN_00b23c60(0x0e9cb8ba, "cBuilding");
    FUN_00b23c60(0xce9f6639, "cCreatureBase");
    FUN_00b23c60(0x013f94d4, "cCombatant");
    InitClassRegistry(&g_classRegistry1, 2, 0x0145ea48, FUN_013c2020);
    InitClassRegistry(&g_classRegistry2, 4, 0x0145ea80, FUN_013c2010);
    InitClassRegistry(&g_classRegistry3, 8, 0x0145eac8, FUN_013c2000);
}

// @ 0x00b25e80
void cNounManagerMessaging::FUN_00b25e80()
{
    FUN_00b25cd0();
    Owner()->FUN_00b215a0();
    mpMessageServer = EA_Messaging_GetServer();
    mpOwner = Owner();
    mpEventNames = g_timelineEvents;
    mEventCount = 3;
    mPad4c = 0;
    if (mpMessageServer != 0 && mpOwner != 0) {
        for (uint32_t i = 0; i < 3; ++i)
            ((cMessagingListener*)mpMessageServer)->AddHandler(mpOwner, mpEventNames[i]);
    }
}

// @ 0x00b25ee0
void cGameNounManager_s00b2_5c30::FUN_00b25ee0()
{
    tGameDataVector* pVector = GetGameDataVector((tVectorCreateFn)0x00b21080, (tVectorClearFn)0x00d3d420,
                                                 (tVectorAddFn)0x00b236c0, (tVectorMatchFn)0x00b1e500,
                                                 0x018c816a);
    int count = (int)(pVector->mpEnd - pVector->mpBegin);
    for (int i = 0; i < count; ++i) {
        FUN_00b21410(pVector->mpBegin[i]);
        RemoveNoun(pVector->mpBegin[i]);
    }
}

// @ 0x00b25f40
cGameData_s00b2_5c30* cGameNounManager_s00b2_5c30::FindNounByEmpireID(uint32_t civID)
{
    tGameDataVector* pVector = GetGameDataVector((tVectorCreateFn)0x00b21080, (tVectorClearFn)0x00d3d420,
                                                 (tVectorAddFn)0x00b236c0, (tVectorMatchFn)0x00b1e500,
                                                 0x018c816a);
    int count = (int)(pVector->mpEnd - pVector->mpBegin);
    for (int i = 0; i < count; ++i) {
        cGameData_s00b2_5c30* pNoun = pVector->mpBegin[i];
        if (pNoun->GetPoliticalID() == civID)
            return pVector->mpBegin[i];
    }
    return 0;
}

// @ 0x00b25fb0
cCivilization* cGameNounManager_s00b2_5c30::GetPlayerCivilization()
{
    cCivilization* pCiv = (cCivilization*)this;
    cEmpire* pEmpire = GetPlayerEmpire();
    if (pEmpire != 0)
        return (cCivilization*)FindNounByEmpireID(pEmpire->mCivilizationID);
    return pCiv;
}

// @ 0x00b25fe0
void cGameNounManager_s00b2_5c30::FUN_00b25fe0()
{
    ProcessPending();
    RemoveNounsOfType(0x018eb45e);
    RemoveNounsOfType(0x2c9cc91);
    RemoveNounsOfType(0x2e96892);
    RemoveNounsOfType(0x018c84a9);
    RemoveNounsOfType(0x1be418e);
    mAvatarHerd.Reset();
    RemoveNounsOfType(0x2a8fb3f);
    RemoveNounsOfType(0x2a034cd);
    RemoveNounsOfType(0x018c6de8);
    RemoveNounsOfType(0x018c88e4);
    RemoveNounsOfType(0x3a2511e);
    RemoveNounsOfType(0x403df5c);
    RemoveNounsOfType(0x61494be);
    RemoveNounsOfType(0x629bafe);
    FUN_00b3d2b0()->GetEditor()->DrainNouns(FUN_00b3d2b0()->GetEditor()->GetContainer());

    tGameDataVector* pVector = GetGameDataVector((tVectorCreateFn)0x00cd7d10, (tVectorClearFn)0x00d3d420,
                                                 (tVectorAddFn)0x00ad48b0, (tVectorMatchFn)0x00b1e500,
                                                 0x018ebadc);
    tNounVector local;
    local.mpBegin = pVector->mpBegin;
    local.mpEnd = pVector->mpEnd;
    local.mpCapacity = pVector->mpEnd;
    local.mPad0c = 0;
    local.mPad10 = 0;
    for (cGameData_s00b2_5c30** pp = local.mpBegin; pp != local.mpEnd; ++pp) {
        int32_t state = (*pp)->mObjectState;
        if (state != 0 && state != 8 && state != 3)
            FUN_0102c340(*pp, 0);
    }
    RemoveNounsOfType(0x2dd8c42);
    RemoveNounsOfType(0x4e3fab5);
    RemoveNounsOfType(0x018c6d19);
    RemoveNounsOfType(0x24270c9);
    RemoveNounsOfType(0x018c43e8);
    RemoveNounsOfType(0x018eb4b7);
    FUN_00b25ee0();
}

// @ 0x00b262c0
cCity* cGameNounManager_s00b2_5c30::GetPlayerCityAtPosition(const cSPVector3_s00b2_5c30& position)
{
    // the inlined GetPlayerCivilization body; with no player empire yet the position argument's
    // slot is what the standalone function returns as `this`, and that is what the original keeps
    cCivilization* pCiv;
    cEmpire* pEmpire = GetPlayerEmpire();
    if (pEmpire != 0)
        pCiv = (cCivilization*)FindNounByEmpireID(pEmpire->mCivilizationID);
    else
        pCiv = (cCivilization*)&position;
    if (pCiv != 0) {
        if (pCiv->GetCityCount() > 0) {
            cCity* pCity = pCiv->GetCityNearestTo(position, 0);
            if (pCity != 0) {
                if (pCity->CanReach(position))
                    return pCity;
            }
        }
    }
    return 0;
}

// @ 0x00b26600
void cGameNounManager_s00b2_5c30::FUN_00b26600()
{
    FUN_00b25fe0();
    if (mpPlayer.mpObject != 0) {
        RemoveNoun((cGameData_s00b2_5c30*)mpPlayer.mpObject);
        ProcessPending();
        if (mpPlayer.mpObject != 0) {
            cRefCounted* pOld = mpPlayer.mpObject;
            mpPlayer.mpObject = 0;
            pOld->Release();
        }
    }
    mPlanetaryContextPoliticalMap.mTree.clear();
    mAvatar.Reset();
    mAvatarHerd.Reset();
    ClearPosseMembers();
    mPlayerTribe.Reset();
    mpPlayer.Reset();
    Flush();
    mGameDataVectorMap.mTree.swap(mGameDataVectorMapDeleted.mTree);
    Flush();
    mGameDataVectorMap.mTree.swap(mGameDataVectorMapDeleted.mTree);
    RemoveNounsOfType(0x3ed8573);
    RemoveNounsOfType(0x2e72cae);
    RemoveNounsOfType(0x32f9778);
}

// @ 0x00b26710
void cTimelineModeStarter::FUN_00b26710()
{
    mpModeOwner->SetModeArgument(&g_modeArg);
    g_uiModeToken = 6;
}
