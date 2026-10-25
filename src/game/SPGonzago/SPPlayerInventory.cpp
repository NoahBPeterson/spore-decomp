// src/game/SPGonzago/SPPlayerInventory.cpp -- migrated from slice(s) s01399700, s00ff4d50, s00ff4120, s00ff3190 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPPlayerInventory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  __cdecl FUN_00f47380(void* p);        // operator delete[]
extern "C" void* __cdecl FUN_00b3d390();               // global tool manager (0x0167eb08)
extern "C" void* __cdecl FUN_0102f810();               // SP::GetSpaceEconomyTuning()
extern "C" void* __cdecl FUN_0067dcc0();               // MessageServer() -> global singleton
extern "C" void  __cdecl FUN_0093aa70(void* stream, const void* src, int count, int a); // EA::IO::WriteUint32
#include <math.h>
#include <intrin.h>
#include <xmmintrin.h>
#include "SP/cCity.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlayer.h"
#include "SP/cTribe.h"
#include "SP/cDataSerializationInfo.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cPropertyList.h"
#include "SP/cVarListSerializer.h"
#include <string.h>
#pragma warning(disable : 4100)

// ---- items of slice s00ff3190 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  u32;
typedef unsigned char u8;
extern "C" void  __cdecl FUN_00f47380(void* p);        // operator delete[]
extern "C" void* __cdecl FUN_00b3d390();               // global tool manager (0x0167eb08)
extern "C" void* __cdecl FUN_0102f810();               // SP::GetSpaceEconomyTuning()
extern "C" void* __cdecl FUN_0067dcc0();               // MessageServer() -> global singleton
extern "C" void  __cdecl FUN_0093aa70(void* stream, const void* src, int count, int a); // EA::IO::WriteUint32
struct cVarListSerializer
{
    u32  mData[0xa14 / 4];                          // +0x000
    void Ctor(void* inst, void* dat, int tag);      // 0x692f90
    char Serialize(void* stream);                   // 0x692900
    int  GetFields(void* fieldVec);                 // 0x695960
};
struct VecPtr { void* mBegin; void* mEnd; void* mCap; void Destroy(); };   // 0x5c7f10
struct ToolObj                                     // ref-counted tool instance
{
    void* mpVtbl;                     // +0x00
    u8    pad04[0x28 - 0x04];
    u8    mb28;                       // +0x28
};
struct ToolInst                                    // cSPToolInstance-like
{
    void* mpVtbl;                     // +0x00
    u8    pad04[0x7c - 0x04];
    int   m7C;                        // +0x7c
    int   GetCount();                 // 0x104c110 (ret 0)
    char  HasFlag();                  // 0x104cbc0 (ret 0)
};
struct InvItem                                     // a sub-object with a +0x0c vtable
{
    void* mpVtbl0;                    // +0x00
    u8    pad04[0x0c - 0x04];
    void* mpVtblC;                    // +0x0c
};
struct Inv
{
    void*   mpVtbl0;                  // +0x00
    void*   mpVtbl1;                  // +0x04
    u8      pad08[0x34 - 0x08];
    VecPtr  m34;                      // +0x34
    u8      pad40[0x4c - 0x40];
    VecPtr  m4C;                      // +0x4c
    u8      pad58[0x60 - 0x58];
    VecPtr  m60;                      // +0x60
    u8      pad6c[0x74 - 0x6c];
    void*   m74;                      // +0x74
    void*   m78;                      // +0x78
    u8      pad7c[0x88 - 0x7c];
    ToolObj* m88;                     // +0x88
    ToolObj* m8c;                     // +0x8c
    ToolObj* m90;                     // +0x90

    char BaseWrite(void* host);       // 0xc874f0 (ret 4)
    void BaseDestroy();               // 0xc87be0 (ret 0)
    void BaseAddCargoSlots(int n);    // 0xc88310 (ret 4)
    void BaseFunc54h();               // 0xc86fe0 (ret 0)
};
struct Tuning  { int GetMaxCargo(); };// 0x102ff00
struct ToolMgr { void Remove(void* obj); };   // 0x104fc10 (ret 4)
struct MsgServer { void* mpVtbl; };                 // MessageServer instance
struct GameData  { int GetFieldValues(void* host); };// 0xb18420 (ret 4)
// ---- items of slice s00ff3190 end

// ---- items of slice s00ff4120 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short u16;
void* SP_MessageServer();     // 0x0067dcc0
void* SP_PropertyManager();   // 0x0067de30
void* SP_ToolManager();       // 0x00b3d390 (decompiler labels it eastl::vector::erase)
void* SP_EventLog();          // 0x00b3d3e0
void* SP_SpaceGameGet();      // 0x01002bd0
void* SP_GetUFOSimulator();   // 0x00ffbe50
void* EA_COM_interface_cast(void* p);            // 0x00c87070
void  FUN_0062ffd0(void* a, void* b, void* c);   // 0x0062ffd0 eastl copy_impl::do_copy
struct cInvItem;
struct cFillEntry;
struct cProperty;
struct cItemSub {                       // embedded sub-object at cInvItem+0x0c
    virtual void  s00();
    virtual void  s04();
    virtual void  s08();
    virtual void* s0c(u32 id);          // 0x0c  -> tool for the key
    u32 m10;
};
struct cSubObj30 {                      // object pointed to by cInvItem+0x30
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
    virtual void s20();
    virtual u8   s24(u32 id, void** out);   // 0x24
};
struct cInvItem {
    virtual void  v00();                // 0x00
    virtual void  v04();                // 0x04  AddRef
    virtual void  v08();                // 0x08  Release
    virtual void  v0c();                // 0x0c
    virtual void  v10();                // 0x10
    virtual void  v14();                // 0x14
    virtual u32*  v18();                // 0x18  item id / key (pointer to a 12-byte key)
    virtual void  v1c();                // 0x1c
    virtual u8    v20();                // 0x20  predicate
    virtual void  v24();                // 0x24
    virtual void  v28();                // 0x28
    u8          pad04[0x0c - 0x04];
    cItemSub    m0c;                    // +0x0c
    u32         m14;                    // +0x14
    u8          pad18[0x24 - 0x18];
    u32         m24;                    // +0x24
    u8          m28;                    // +0x28
    u8          pad29[0x30 - 0x29];
    cSubObj30*  m30;                    // +0x30
    // direct (non-virtual) member callees
    u8    FUN_0104feb0();               // 0x0104feb0
    u8    FUN_0104ccd0();               // 0x0104ccd0
    u32   FUN_0104bd80();               // 0x0104bd80
    u32*  FUN_0104be80(u32* out);       // 0x0104be80
};
struct cProperty {
virtual void p00();
virtual void p04();
virtual void p08();
virtual void p0c();
virtual void p10();
virtual void p14();
virtual void p18();
    virtual u8   p1c(u32 id);           // 0x1c
virtual void p20();
virtual void p24();
    virtual void* p28_(u32 id);         // 0x28  (container for the id)
    u8*  GetBool();                     // 0x0041e920
};
struct cPropMgr {
virtual void q00();
virtual void q04();
virtual void q08();
virtual void q0c();
virtual void q10();
virtual void q14();
virtual void q18();
virtual void q1c();
virtual void q20();
virtual void q24();
virtual void q28();
    virtual void q2c(u32 a, u32 b, void** out);  // 0x2c
};
struct cToolMgr {                       // singleton from SP_ToolManager()
    virtual void r00();                 // AddRef
    virtual void r04();                 // Release
    u8   CreateToolFromToolID(const void* entry, void** out);   // 0x0104e340
    void ActivateTool(void* tool);                              // 0x0104fbb0
    void DeactivateTool(void* tool);                            // 0x0104fc10
};
struct cMsgServer {
virtual void m00();
virtual void m04();
virtual void m08();
virtual void m0c();
    virtual void m10();
    virtual void m14(u32 a, u32 b, u32 c);              // 0x14
    virtual void m18(u32 a, u32 b, u32 c, u32 d);       // 0x18
};
struct cAutoRef {                       // AutoRefCount<T> (a single owned pointer)
    cInvItem* mp;                       // +0x00
    void Push(cInvItem* p);             // 0x00572620
};
struct cItemVec {                       // sp_ref_vector<T>
    cInvItem** mBegin;                  // +0x00
    cInvItem** mEnd;                    // +0x04
    cInvItem** mCap;                    // +0x08
    void FUN_00d01790(u32 n);                               // 0x00d01790
    void FUN_00f14270(cInvItem** end, cInvItem** val);      // 0x00f14270
    void FUN_005c2170(cInvItem** first, cInvItem** last);   // 0x005c2170
};
struct cFillEntry {                     // 12-byte FillEntry
    void* m0; u32 m4; u32 m8;
};
struct cFillVec {                       // SpVector<FillEntry> at +0x74
    void* mBegin; void* mEnd; void* mCap;
    void push_back(const cFillEntry& v);    // 0x004e19a0
};
struct cSSO {                           // sp_vector-like SSO container returned by v28(id)
    void* mpHeapBegin;                  // +0x00  (also the SSO storage base)
    u32   m04;                          // +0x04
    int   mSize;                        // +0x08
    u32   m0c;                          // +0x0c
    u16   mFlags;                       // +0x10
    u16   mSSOCount;                    // +0x12
};
struct cTranslator { u8 pad00[0x14]; void* m14; };
struct cEventLog {
    void PostFeedbackEvent(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f);  // 0x00dd8640
};
struct cVecElem { u8 pad00[0x1c]; u32 m1c; u32 m20; };
struct cVec { u8 pad00[0x0c]; cVecElem* mpElems; void resize(u32 n); };  // IntVector
struct cSimGame { void* FUN_01005180(u32 n); };                     // 0x01005180
struct cToolSetObj { void Assign(void* src); };                     // 0x00c70110
struct cObj508 {
virtual void a00();
virtual void a04();
    virtual void* a08();                // 0x08
};
struct cPlayerInventory {
    u8 pad00[0x508];
    cObj508 m508;                       // +0x508
};
struct cUFOSim { cPlayerInventory* GetPlayerInventory(); };         // 0x00a1ad60
struct cSpaceInvBase {
virtual void w00();
virtual void w04();
virtual void w08();
virtual void w0c();
virtual void w10();
virtual void w14();
virtual void w18();
virtual void w1c();
virtual void w20();
virtual void w24();
virtual void w28();
virtual void w2c();
virtual void w30();
virtual void w34();
virtual void w38();
virtual void w3c();
virtual void w40();
virtual void w44();
virtual void w48();
virtual void w4c();
virtual void w50();
virtual void w54();
virtual void w58();
virtual void w5c();
    virtual void w60();
    virtual int   w64(u32 a, void* b);                              // 0x64
    virtual void* w68(u32 a);                                       // 0x68
    virtual void  w6c();
    virtual u8    w70(u32 a, void* b);                              // 0x70
    virtual void  w74();
    virtual void  w78(void* a);                                     // 0x78
    virtual void  w7c();
    virtual void  w80(void* a, u32 b, u32 c);                       // 0x80
virtual void  w84();
virtual void w88();
virtual void w8c();
    virtual void  w90();
    virtual void  w94(u32 a);                                       // 0x94
    // non-virtual callees implemented in the base classes
    u8 RemoveItemBase(void* item);                                 // 0x00c87d80
    u8 TakeFromInventory(u32 idx, u32 a, u32 b);                   // 0x00c87df0
    u8 AddToInventoryBase(void* item, u32 a, u32 b);               // 0x00c88060
};
struct cSPPlayerInventory : cSpaceInvBase {
    u8        pad04[0x34 - 0x04];
    cItemVec  mInventoryItems;      // +0x34
    u8        pad40[0x4c - 0x40];
    cItemVec  mToolSet;             // +0x4c
    u8        pad58[0x74 - 0x58];
    cFillVec  mFillStack;           // +0x74
    u8        pad80[0x88 - 0x80];
    cAutoRef  mTool88;              // +0x88
    cAutoRef  mTool8c;              // +0x8c
    cAutoRef  mTool90;              // +0x90
    u8        m94;                  // +0x94

    u8   RemoveItem(void* item);                       // 0x00ff4120
    u8   func7Ch(u32 idx, u32 a, u32 b);               // 0x00ff4200
    void FUN_00ff4310();                               // 0x00ff4310
    void FUN_00ff4470(cInvItem* item);                 // 0x00ff4470
    void FUN_00ff4540(cInvItem* item);                 // 0x00ff4540
    void FUN_00ff45e0(cFillEntry* entry);              // 0x00ff45e0
    void FUN_00ff46e0();                               // 0x00ff46e0
    u8   FUN_00ff4840(void* key);                      // 0x00ff4840
    u8   AddToInventory(void* item, u32 a, bool flag); // 0x00ff48d0
    void FUN_00ff4b10(cInvItem* item);                 // 0x00ff4b10
    void UseToolSet(u32 set);                          // 0x00ff4b90
    // callees living elsewhere in the class
    void  SetActiveTool();                             // 0x00ff3e80
    void* GetToolFromToolID(u32* key);                 // 0x00ff3d40
};
extern cTranslator* gTokenTranslator;   // 0x016e0d08
extern u32 gToolKey[3];                 // 0x016dadec
extern u32 gCargoKey[3];                // 0x016daedc
// ---- items of slice s00ff4120 end

// ---- items of slice s00ff4d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_15b5ed8;      // [0x015b5ed8] variable-list table used when reading
struct VObj { void** vt; };
typedef void* (__thiscall *FnVp0)(void*);
struct IStream;
bool __cdecl EA_IO_ReadInt32(void* s, void* p, uint32_t n, int endian);         // 0x0093a780
struct cDataSerializationInfo { char d[0x14]; };
class cVarListSerializer_s00ff_4d50 {
public:
    cDataSerializationInfo mInfos[128];  // +0x0000
    int      mSerializableVarCount;      // +0x0a00
    int      mSerializedVarCount;        // +0x0a04
    uint32_t mSignature;                 // +0x0a08
    void*    mpObject;                   // +0x0a0c
    void*    mpSerializerList;           // +0x0a10

    cVarListSerializer_s00ff_4d50(void* obj, void* list, uint32_t sig); // 0x00692f90
    bool __thiscall Serialize(IStream* s);                   // 0x00692900
    bool __thiscall SerializeRead(IStream* s);               // 0x00693e10
};
static inline void* StreamWriter(IStream* s) {
    return ((FnVp0)((VObj*)s)->vt[0x20 / 4])(s);
}
static inline void* WriterValue(void* w) {
    return ((FnVp0)((VObj*)w)->vt[0x18 / 4])(w);
}
struct cRefCounted;
struct ToolVector {
    cRefCounted* mpBegin;                                    // +0x00
    cRefCounted* mpEnd;                                      // +0x04
    cRefCounted* mpCapacity;                                 // +0x08
    cRefCounted* __thiscall erase(cRefCounted* first, cRefCounted* last); // 0x005c2170
    void __thiscall Append(cRefCounted* tool);               // 0x00f14270
};
struct cRefCounted {
    virtual void Dtor();                 // vt[0]
    virtual void AddRef();               // vt[4]
    virtual void Release();              // vt[8]
};
struct cPropertyList {
    void** mpVtbl;                                       // +0x00
    char   pad04[0x38 - 0x04];
    cRefCounted* mItems;                                 // +0x38
    cRefCounted* mItemsEnd;                              // +0x3c
    cRefCounted* mItemsCap;                              // +0x40

    bool __thiscall HasProperty(int key);                // vt[0x1c]
    cPropertyList* __thiscall GetSubList(int key);       // vt[0x28]
    void __thiscall QueryKeys(cPropertyList** out, int a, int b); // vt[0x2c]
    void __thiscall Release();                           // vt[0]
};
struct cSPToolManager {
    void** mpVtbl;                                              // +0x00
    bool __thiscall CreateToolFromToolID(cRefCounted** out, cRefCounted* spec); // 0x0104e340
    cPropertyList* __thiscall TakePropertyList(cPropertyList* p);               // 0x00b3d390
    void __thiscall QueryKeys(cPropertyList** out, int a, int b);               // vt[0x2c]
};
struct cPlayerInventory_s00ff_4d50 {
    void*  mpVtbl0;                       // +0x00
    void*  mpVtbl1;                       // +0x04
    char   pad08[0x4c - 0x08];
    ToolVector mUnlockableTools;          // +0x4c
    char   pad58[0x60 - 0x58];
    ToolVector mTransitionRewardTools;    // +0x60
    char   pad6c[0x74 - 0x6c];
    ToolVector mDecorationTools;          // +0x74
    char   pad80[0x88 - 0x80];
    ToolVector mProjectileTools;          // +0x88
    char   mb94;                          // +0x94

    cPlayerInventory_s00ff_4d50* __thiscall ctor();          // 0x00ff5190
    void __thiscall LoadToolData();               // 0x00ff4d50
    bool __thiscall Read(IStream* s);             // 0x00ff50f0
    void __thiscall BaseCtor();                   // 0x00c87b20
    char __thiscall ReadBase(IStream* s);         // 0x00c883d0
};
// ---- items of slice s00ff4d50 end

// ---- items of slice s01399700 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned char g_didInit;   // 0x16daddc (01399700 sets it to 1)
typedef unsigned int uint;
struct PropDesc {
    const char* name;    // +0x00
    uint        hash;    // +0x04
    uint        offset;  // +0x08
    uint        f0c;     // +0x0c  (uninitialised in the original)
    uint        f10;     // +0x10  (uninitialised in the original)
    uint        f14;     // +0x14  (uninitialised in the original)
    void*       f18;     // +0x18
    void*       f1c;     // +0x1c
    void*       f20;     // +0x20
    void*       f24;     // +0x24
    void*       f28;     // +0x28
    void*       f2c;     // +0x2c
    void*       f30;     // +0x30
    void*       f34;     // +0x34
    void*       f38;     // +0x38
};
extern PropDesc g_props_99700[7];   // 0x15b5ed8  (stride 0x3c)
void FUN_00692ca0();
void FUN_00692fb0();
void FUN_00692ff0();
void FUN_00693090();
void FUN_00572810();
void FUN_00572840();
void FUN_0057cde0();
void FUN_0057ce00();
void FUN_00694ee0();
void FUN_00694fa0();
void FUN_00ac8050();
void FUN_00ac8750();
void FUN_00ac8780();
void FUN_00b1fbf0();
void FUN_00bceb00();
void FUN_00bd1780();
void FUN_00c2e4e0();
void FUN_00c6adc0();
void FUN_00c6c390();
void FUN_00c6c4e0();
void FUN_00c87090();
void FUN_00c875f0();
void FUN_00c87630();
void FUN_00c87c00();
void FUN_00c87f80();
void FUN_00c95780();
void FUN_00ff3cf0();
// ---- items of slice s01399700 end

// @ 0x00ff3b30
void __fastcall FUN_00ff3b30(Inv* ecx_this, void* edx, int n)
{
    ecx_this->BaseAddCargoSlots(n);
    int count = (int)((u32(__thiscall*)(void*))(*(void***)ecx_this)[0x88 / 4])(ecx_this);
    int local = count;
    MsgServer* ms = (MsgServer*)FUN_0067dcc0();
    ((void(__thiscall*)(void*, u32, void*, int))(*(void***)ms)[0x14 / 4])(ms, 0x5e793b4, &local, 0);
}

// @ 0x00ff3b70
void __fastcall FUN_00ff3b70(Inv* ecx_this)
{
    ecx_this->BaseFunc54h();
    void** pVtbl = *(void***)ecx_this;
    Tuning* t = (Tuning*)FUN_0102f810();
    int max = t->GetMaxCargo();
    ((void(__thiscall*)(void*, int))pVtbl[0x58 / 4])(ecx_this, max);
}

// @ 0x00ff3d40
void* __fastcall FUN_00ff3d40(Inv* ecx_this, void* edx, const u32* pId)
{
    for (void** p = (void**)ecx_this->m34.mBegin; p != (void**)ecx_this->m34.mEnd; ++p) {
        InvItem* o = (InvItem*)*p;
        u32* pid = ((u32*(__thiscall*)(void*))(*(void***)o)[0x18 / 4])(o);
        if (pid[0] == pId[0] && pid[1] == pId[1] && pid[2] == pId[2]) {
            if (o == 0) {
                return 0;
            }
            return ((void*(__thiscall*)(void*, u32))((void**)o->mpVtblC)[0xc / 4])(&o->mpVtblC, 0x707459f0);
        }
    }
    for (void** p = (void**)ecx_this->m4C.mBegin; p != (void**)ecx_this->m4C.mEnd; ++p) {
        InvItem* o = (InvItem*)*p;
        u32* pid = ((u32*(__thiscall*)(void*))(*(void***)o)[0x18 / 4])(o);
        if (pid[0] == pId[0] && pid[1] == pId[1] && pid[2] == pId[2]) {
            if (o == 0) {
                return 0;
            }
            return ((void*(__thiscall*)(void*, u32))((void**)o->mpVtblC)[0xc / 4])(&o->mpVtblC, 0x707459f0);
        }
    }
    return 0;
}

// @ 0x00ff3df0
void __fastcall FUN_00ff3df0(Inv* ecx_this)
{
    void** end = (void**)ecx_this->m60.mEnd;
    for (void** p = (void**)ecx_this->m60.mBegin; p != end; ++p) {
        InvItem* o = (InvItem*)*p;
        ToolInst* t = 0;
        if (o != 0) {
            t = (ToolInst*)((void*(__thiscall*)(void*, u32))((void**)o->mpVtblC)[0xc / 4])(&o->mpVtblC, 0x707459f0);
            if (t != 0) {
                ((void(__thiscall*)(void*))(*(void***)t)[0x04 / 4])(t);
            }
        }
        if (t->GetCount() > 0) {
            if (t->HasFlag() != 0) {
                t->m7C = t->GetCount();
            }
            ((void(__thiscall*)(void*, void*, int, int))(*(void***)ecx_this)[0x80 / 4])(ecx_this, t, 0, 1);
        }
        if (t != 0) {
            ((void(__thiscall*)(void*))(*(void***)t)[0x08 / 4])(t);
        }
    }
}

// @ 0x00ff3e80
void __fastcall FUN_00ff3e80(Inv* ecx_this)
{
    ToolObj* p = ecx_this->m90;
    if (p != 0) {
        p->mb28 = 0;
        ToolObj* q = ecx_this->m90;
        if (q != 0) {
            ecx_this->m90 = 0;
            ((void(__thiscall*)(void*))(*(void***)q)[0x08 / 4])(q);
        }
    }
    if (ecx_this->m8c != 0) {
        MsgServer* ms = (MsgServer*)FUN_0067dcc0();
        ((void(__thiscall*)(void*, u32, void*, int))(*(void***)ms)[0x14 / 4])(ms, 0x61dae65, ecx_this->m8c, 0);
        ToolObj* q = ecx_this->m8c;
        if (q != 0) {
            ecx_this->m8c = 0;
            ((void(__thiscall*)(void*))(*(void***)q)[0x08 / 4])(q);
        }
        ((ToolMgr*)FUN_00b3d390())->Remove(q);
        q->mb28 = 0;
    }
}

// @ 0x00ff3f20
bool __fastcall FUN_00ff3f20(Inv* ecx_this, void* edx, void* host)
{
    void* obj = ((void*(__thiscall*)(void*))(*(void***)host)[0x20 / 4])(host);
    void* fn = ((void**)*(void***)obj)[0x18 / 4];
    u32 tag = 0x9073163b;
    void* ch = ((void*(__thiscall*)(void*))fn)(obj);
    FUN_0093aa70(ch, &tag, 1, 0);

    char ok = ecx_this->BaseWrite(host);
    cVarListSerializer ser;
    ser.Ctor(ecx_this, (void*)0x15b5ed8, 0x1a80d26);
    if (ok != 0) {
        if (ser.Serialize(host) != 0) {
            return true;
        }
    }
    return false;
}

// @ 0x00ff3fb0
u32 __fastcall FUN_00ff3fb0(Inv* ecx_this, void* edx, void* host)
{
    char c = ((char(__thiscall*)(void*))(*(void***)host)[0x20 / 4])(host);
    if (c != 0) {
        return (u32)ecx_this->m88;
    }
    return ((u32(__thiscall*)(void*, u32))(*(void***)((char*)host + 0xc))[0xc / 4])((char*)host + 0xc, 0x707459f0);
}

// @ 0x00ff3ff0
void __fastcall FUN_00ff3ff0(Inv* ecx_this)
{
    ecx_this->mpVtbl0 = (void*)0x1494d68;
    ecx_this->mpVtbl1 = (void*)0x1494d54;
    _ReadWriteBarrier();
    ToolObj* p;
    p = ecx_this->m90;
    if (p != 0) {
        ((void(__thiscall*)(void*))(*(void***)p)[0x08 / 4])(p);
    }
    p = ecx_this->m8c;
    if (p != 0) {
        ((void(__thiscall*)(void*))(*(void***)p)[0x08 / 4])(p);
    }
    p = ecx_this->m88;
    if (p != 0) {
        ((void(__thiscall*)(void*))(*(void***)p)[0x08 / 4])(p);
    }
    void* buf = ecx_this->m74;
    if (buf != 0) {
        if (*(int*)((char*)buf - 4) != 0) {
            FUN_00f47380(buf);
        }
    }
    ecx_this->m60.Destroy();
    ecx_this->m4C.Destroy();
    ecx_this->BaseDestroy();
}

// @ 0x00ff4090
int __fastcall FUN_00ff4090(GameData* ecx_this, void* edx, void* host)
{
    int a = ecx_this->GetFieldValues(host);

    cVarListSerializer s1;
    s1.Ctor(ecx_this, (void*)0x1579ed8, 0x1a80d26);
    int b = s1.GetFields(host);
    int ab = a + b;

    cVarListSerializer s2;
    s2.Ctor(ecx_this, (void*)0x15b5ed8, 0x1a80d26);
    int c = s2.GetFields(host);

    return c + ab;
}

// @ 0x00ff4120
u8 cSPPlayerInventory::RemoveItem(void* item)
{
    cInvItem* p = (cInvItem*)item;
    if (p != 0) p->v04();
    u8 r = cSpaceInvBase::RemoveItemBase(p);
    if (r != 0) {
        if (mTool88.mp == p) {
            cInvItem* old = mTool88.mp;
            if (old != 0) {
                mTool88.mp = 0;
                old->v08();
            }
        }
        if (mTool8c.mp == p) SetActiveTool();
        if (mTool90.mp == p) {
            cInvItem* old = mTool90.mp;
            if (old != 0) {
                mTool90.mp = 0;
                old->v08();
            }
        }
        ((cMsgServer*)SP_MessageServer())->m14(0x5e793ad, (u32)p, 0);
        ((cMsgServer*)SP_MessageServer())->m18(0x57f3749, 0, 0, 0);
        if (p != 0) p->v08();
        return 1;
    }
    if (p != 0) p->v08();
    return 0;
}

// @ 0x00ff4200
u8 cSPPlayerInventory::func7Ch(u32 idx, u32 a, u32 b)
{
    cInvItem* it = mInventoryItems.mBegin[idx];
    if (it != 0) it->v04();
    u8 r = cSpaceInvBase::TakeFromInventory(idx, a, b);
    if (r != 0) {
        void* id = it->v18();
        u8 has = w70(it->m14, id);
        if (has != 0) {
            ((cMsgServer*)SP_MessageServer())->m14(0x635ae7e, (u32)it, 0);
        } else {
            if (mTool88.mp == it) {
                cInvItem* old = mTool88.mp;
                if (old != 0) {
                    mTool88.mp = 0;
                    old->v08();
                }
            }
            if (mTool8c.mp == it) SetActiveTool();
            if (mTool90.mp == it) {
                cInvItem* old = mTool90.mp;
                if (old != 0) {
                    mTool90.mp = 0;
                    old->v08();
                }
            }
            ((cMsgServer*)SP_MessageServer())->m14(0x5e793ad, (u32)it, 0);
        }
        ((cMsgServer*)SP_MessageServer())->m18(0x57f3749, 0, 0, 0);
        it->v08();
        return 1;
    }
    if (it != 0) it->v08();
    return 0;
}

// @ 0x00ff4310
void cSPPlayerInventory::FUN_00ff4310()
{
    cProperty* prop = 0;
    void* pm = SP_PropertyManager();
    if (prop != 0) {
        cProperty* old = prop;
        prop = 0;
        old->p04();
    }
    ((cPropMgr*)pm)->q2c(0x59252ee9, 0x30608f0b, (void**)&prop);
    void* tm = SP_ToolManager();
    if (tm != 0) ((cToolMgr*)tm)->r00();
    void* out = 0;
    if (prop != 0 && prop->p1c(0x6553d45) != 0) {
        cSSO* vec = (cSSO*)prop->p28_(0x6553d45);
        u16 f = vec->mFlags;
        cFillEntry* data;
        int count;
        if ((f & 0x30) != 0) {
            data = (cFillEntry*)vec->mpHeapBegin;
            count = vec->mSize;
        } else {
            data = vec->mSSOCount ? (cFillEntry*)vec : 0;
            count = vec->mSSOCount ? 1 : 0;
        }
        if (count > 0) {
            do {
                cFillEntry entry;
                entry.m0 = *(void**)data;
                entry.m4 = 0;
                entry.m8 = 0;
                if (out != 0) {
                    cInvItem* old = (cInvItem*)out;
                    out = 0;
                    old->v08();
                }
                ((cToolMgr*)tm)->CreateToolFromToolID(&entry, &out);
                if (out != 0) ((cSpaceInvBase*)this)->w80(out, 0, 1);
                data = data + 1;
                count = count - 1;
            } while (count != 0);
        }
    }
    if (out != 0) ((cInvItem*)out)->v08();
    if (tm != 0) ((cToolMgr*)tm)->r04();
    if (prop != 0) {
        cProperty* old = prop;
        prop = 0;
        old->p04();
    }
}

// @ 0x00ff4470
void cSPPlayerInventory::FUN_00ff4470(cInvItem* item)
{
    void* id = item->v18();
    int i = w64(item->m14, id);
    if (i < 0) return;
    cInvItem* tool = mInventoryItems.mBegin[i];
    cInvItem* target;
    if (tool->v20() != 0) target = mTool88.mp;
    else target = (cInvItem*)tool->m0c.s0c(0x707459f0);
    if (target == 0) return;
    u8 one = 1;
    if (target->FUN_0104feb0() == 0 && target->FUN_0104ccd0() == 0) {
        SetActiveTool();
        mTool8c.Push(target);
        if (tool->v20() != 0) {
            mTool90.Push(tool);
            tool->m28 = one;
        }
    }
    target->m28 = one;
    ((cMsgServer*)SP_MessageServer())->m14(0x61dae5c, (u32)target, 0);
    ((cToolMgr*)SP_ToolManager())->ActivateTool(target);
}

// @ 0x00ff4540
void cSPPlayerInventory::FUN_00ff4540(cInvItem* item)
{
    void* id = item->v18();
    int i = w64(item->m14, id);
    if (i < 0) return;
    cInvItem* tool = mInventoryItems.mBegin[i];
    cInvItem* target;
    if (tool->v20() != 0) target = mTool88.mp;
    else target = (cInvItem*)tool->m0c.s0c(0x707459f0);
    if (target == 0) return;
    if (target == mTool8c.mp) {
        SetActiveTool();
        return;
    }
    ((cMsgServer*)SP_MessageServer())->m14(0x61dae65, (u32)target, 0);
    ((cToolMgr*)SP_ToolManager())->DeactivateTool(target);
    target->m28 = 0;
}

// @ 0x00ff45e0
void cSPPlayerInventory::FUN_00ff45e0(cFillEntry* entry)
{
    cInvItem* local = 0;
    ((cToolMgr*)SP_ToolManager())->CreateToolFromToolID(entry, (void**)&local);
    if (local == 0) return;
    ((cSpaceInvBase*)this)->w80(local, 0, 1);
    cSubObj30* sub = local->m30;
    void* prop = 0;
    if (sub == 0
        || sub->s24(0x6723e59, &prop) == 0
        || *(u16*)((u8*)prop + 0x12) != 1
        || *((cProperty*)prop)->GetBool() != 0) {
        gTokenTranslator->m14 = local;
        ((cEventLog*)SP_EventLog())->PostFeedbackEvent(0x15e1a624, 0x131a9f54, 0, 0, 1, 0);
    }
    cVec* vec = (cVec*)((cSimGame*)SP_SpaceGameGet())->FUN_01005180(0xf);
    vec->resize(9);
    vec->mpElems->m1c = (u32)entry->m0;
    vec->mpElems->m20 = 0;
    if (local != 0) local->v08();
}

// @ 0x00ff46e0
void cSPPlayerInventory::FUN_00ff46e0()
{
    cProperty* prop = 0;
    void* pm = SP_PropertyManager();
    if (prop != 0) {
        cProperty* old = prop;
        prop = 0;
        old->p04();
    }
    ((cPropMgr*)pm)->q2c(0x59252ee9, 0x30608f0b, (void**)&prop);
    void* tm = SP_ToolManager();
    if (tm != 0) ((cToolMgr*)tm)->r00();
    if (prop != 0 && prop->p1c(0xf0609ec3) != 0) {
        cSSO* vec = (cSSO*)prop->p28_(0xf0609ec3);
        u16 f = vec->mFlags;
        cFillEntry* data;
        int count;
        if ((f & 0x30) != 0) {
            data = (cFillEntry*)vec->mpHeapBegin;
            count = vec->mSize;
        } else {
            data = vec->mSSOCount ? (cFillEntry*)vec : 0;
            count = vec->mSSOCount ? 1 : 0;
        }
        void* out = 0;
        mInventoryItems.FUN_00d01790(count);
        if (count > 0) {
            do {
                cFillEntry entry;
                entry.m0 = *(void**)data;
                entry.m4 = 0;
                entry.m8 = 0;
                if (out != 0) {
                    cInvItem* old = (cInvItem*)out;
                    out = 0;
                    old->v08();
                }
                ((cToolMgr*)tm)->CreateToolFromToolID(&entry, &out);
                if (out != 0) ((cSpaceInvBase*)this)->w80(out, 0, 1);
                data = data + 1;
                count = count - 1;
            } while (count != 0);
        }
        if (out != 0) ((cInvItem*)out)->v08();
    }
    if (tm != 0) ((cToolMgr*)tm)->r04();
    if (prop != 0) {
        cProperty* old = prop;
        prop = 0;
        old->p04();
    }
}

// @ 0x00ff4840
u8 cSPPlayerInventory::FUN_00ff4840(void* key)
{
    cInvItem** it = mToolSet.mBegin;
    cInvItem** end = mToolSet.mEnd;
    if (it == end) return 0;
    do {
        u32* k = it[0]->v18();
        if (k[0] == ((u32*)key)[0] && k[1] == ((u32*)key)[1] && k[2] == ((u32*)key)[2]) {
            ((cSpaceInvBase*)this)->w80(it[0], 0, 1);
            cInvItem** e = mToolSet.mEnd;
            cInvItem** src = it + 1;
            if (src < e) FUN_0062ffd0(src, e, it);
            mToolSet.mEnd = (cInvItem**)((u8*)mToolSet.mEnd - 4);
            cInvItem* last = *(cInvItem**)mToolSet.mEnd;
            if (last != 0) last->v08();
            return 1;
        }
        it = it + 1;
    } while (it != end);
    return 0;
}

// @ 0x00ff48d0
u8 cSPPlayerInventory::AddToInventory(void* item_, u32 a, bool flag)
{
    cInvItem* item = (cInvItem*)item_;
    cInvItem* tool = 0;
    if (item != 0) tool = (cInvItem*)item->m0c.s0c(0x707459f0);
    cInvItem* found = 0;
    if (tool != 0) {
        u32 buf[3];
        u32* k = tool->FUN_0104be80(buf);
        if (k[0] != gToolKey[0] || k[1] != gToolKey[1] || k[2] != gToolKey[2]) {
            u32 buf2[3];
            u32* k2 = tool->FUN_0104be80(buf2);
            found = (cInvItem*)GetToolFromToolID(k2);
            if (found == 0) return 0;
        }
    }
    int idx = w64(item->m14, item->v18());
    u8 r = cSpaceInvBase::AddToInventoryBase(item, a, (u32)flag);
    if (r == 0) return 0;
    if (tool != 0) {
        if (flag) {
            if (tool->FUN_0104bd80() == 0xa8cfdbda) ((cSpaceInvBase*)this)->w94(5);
            if (tool->FUN_0104feb0() != 0) FUN_00ff4470(tool);
        }
        void* ufo = SP_GetUFOSimulator();
        if (ufo != 0) {
            cPlayerInventory* inv = ((cUFOSim*)ufo)->GetPlayerInventory();
            if (inv != 0) {
                void* src = inv->m508.a08();
                ((cToolSetObj*)((u8*)tool + 0x114))->Assign(src);
            }
        }
        if (flag && found != 0) {
            if (mTool8c.mp == found) FUN_00ff4470(tool);
            item->m24 = found->m24;
            mFillStack.push_back(*(cFillEntry*)found->v18());
            ((cSpaceInvBase*)this)->w78(found);
        }
    }
    if (flag) {
        m94 = 1;
        if (idx < 0) {
            ((cMsgServer*)SP_MessageServer())->m14(0x5e793a6, (u32)item, 0);
            u32* id = item->v18();
            if (id[0] == gCargoKey[0] && id[1] == gCargoKey[1] && id[2] == gCargoKey[2]) {
                void* t = ((cSpaceInvBase*)this)->w68((u32)gCargoKey);
                mTool88.Push((cInvItem*)EA_COM_interface_cast(t));
            }
        } else {
            ((cMsgServer*)SP_MessageServer())->m14(0x635ae73, (u32)mInventoryItems.mBegin[idx], 0);
        }
    }
    ((cMsgServer*)SP_MessageServer())->m18(0x57f3749, 0, 0, 0);
    return 1;
}

// @ 0x00ff4b10
void cSPPlayerInventory::FUN_00ff4b10(cInvItem* item)
{
    cInvItem** p = mToolSet.mBegin;
    cInvItem** e = mToolSet.mEnd;
    if (p != e) {
        do {
            if (*p == item) return;
            p = p + 1;
        } while (p != e);
    }
    cInvItem* local = item;
    cItemVec& v = mToolSet;
    if (item != 0) item->v04();
    if (v.mEnd < v.mCap) {
        cInvItem** slot = v.mEnd;
        v.mEnd = slot + 1;
        if (slot != 0) {
            *slot = item;
            if (item != 0) item->v04();
        }
        if (local != 0) local->v08();
    } else {
        v.FUN_00f14270(v.mEnd, &local);
        if (local != 0) local->v08();
    }
}

// @ 0x00ff4b90
void cSPPlayerInventory::UseToolSet(u32 set)
{
    cProperty* prop = 0;
    void* pm = SP_PropertyManager();
    if (prop != 0) {
        cProperty* old = prop;
        prop = 0;
        old->p04();
    }
    ((cPropMgr*)pm)->q2c(0x59252ee9, 0x30608f0b, (void**)&prop);
    if (prop == 0) return;
    if (prop->p1c(set) == 0) return;
    mInventoryItems.FUN_005c2170(mInventoryItems.mBegin, mInventoryItems.mEnd);
    ((cSpaceInvBase*)this)->w94(10);
    void* tm = SP_ToolManager();
    if (tm != 0) ((cToolMgr*)tm)->r00();
    cSSO* vec = (cSSO*)prop->p28_(set);
    u16 f = vec->mFlags;
    cFillEntry* data;
    int count;
    if ((f & 0x30) != 0) {
        data = (cFillEntry*)vec->mpHeapBegin;
        count = vec->mSize;
    } else {
        data = vec->mSSOCount ? (cFillEntry*)vec : 0;
        count = vec->mSSOCount ? 1 : 0;
    }
    void* out = 0;
    if (count > 0) {
        do {
            cFillEntry entry;
            entry.m0 = *(void**)data;
            entry.m4 = 0;
            entry.m8 = 0;
            if (out != 0) {
                cInvItem* old = (cInvItem*)out;
                out = 0;
                old->v08();
            }
            ((cToolMgr*)tm)->CreateToolFromToolID(&entry, &out);
            if (out != 0) {
                cInvItem* made = (cInvItem*)out;
                made->v04();
                if (mToolSet.mEnd < mToolSet.mCap) {
                    cInvItem** slot = mToolSet.mEnd;
                    mToolSet.mEnd = slot + 1;
                    if (slot != 0) {
                        *slot = made;
                        made->v04();
                    }
                } else {
                    mToolSet.FUN_00f14270(mToolSet.mEnd, &made);
                }
                if (made != 0) made->v08();
            }
            data = data + 1;
            count = count - 1;
        } while (count != 0);
    }
    if (out != 0) ((cInvItem*)out)->v08();
    if (tm != 0) ((cToolMgr*)tm)->r04();
    if (prop != 0) {
        cProperty* old = prop;
        prop = 0;
        old->p04();
    }
}

// @ 0x00ff4d50
void __thiscall cPlayerInventory_s00ff_4d50::LoadToolData()
{
    cPropertyList* pToolList = 0;
    cSPToolManager* toolMgr = (cSPToolManager*)SP_PropertyManager();
    toolMgr->QueryKeys(&pToolList, 0x59252ee9, 0x30608f0b);
    pToolList = toolMgr->TakePropertyList(pToolList);
    if (pToolList == 0)
        return;

    if (pToolList->HasProperty(0xf0609ec3)) {
        cPropertyList* ids = pToolList->GetSubList(0x63aa10b);
        cRefCounted* created = 0;
        toolMgr->CreateToolFromToolID(&created, (cRefCounted*)ids);
        mUnlockableTools.Append(created);
    }
    if (pToolList->HasProperty((int)0x2c08e1e)) {
        cPropertyList* ids = pToolList->GetSubList(0x4ed333f);
        cRefCounted* created = 0;
        toolMgr->CreateToolFromToolID(&created, (cRefCounted*)ids);
        mTransitionRewardTools.Append(created);
    }
    if (pToolList->HasProperty(0x30608f0b)) {
        cPropertyList* ids = pToolList->GetSubList(0x59252ee9);
        cRefCounted* created = 0;
        toolMgr->CreateToolFromToolID(&created, (cRefCounted*)ids);
        mDecorationTools.Append(created);
    }
    pToolList->Release();
}

// @ 0x00ff50f0
bool __thiscall cPlayerInventory_s00ff_4d50::Read(IStream* s)
{
    int id;
    mUnlockableTools.erase(mUnlockableTools.mpBegin, mUnlockableTools.mpEnd);

    void* stream = StreamWriter(s);
    void* value = WriterValue(stream);
    EA_IO_ReadInt32(value, &id, 1, 0);

    char ok = ReadBase(s);
    cVarListSerializer_s00ff_4d50 ser(this, &g_15b5ed8, 0x1a80d26);
    if (ok && ser.SerializeRead(s))
        return true;
    return false;
}

// @ 0x01399700
void PropTableInit_99700()
{
    PropDesc d;
    d.name = "mUnlockableTools"; d.hash = 0x3851188u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00c87f80;
    d.f28 = (void*)&FUN_00c87c00; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00c875f0;
    d.f38 = (void*)&FUN_00c6c390;
    d.offset = 0x4cu;
    g_props_99700[0] = d;

    d.name = "mUpgradedToolIds"; d.hash = 0x6786ec4u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00c95780;
    d.f28 = (void*)&FUN_00c6adc0; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00c6c4e0;
    d.offset = 0x74u;
    g_props_99700[1] = d;

    d.name = "mpDropCargoTool"; d.hash = 0x61c7e21u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00bceb00;
    d.f28 = (void*)&FUN_00bd1780; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00c87090;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 0x88u;
    g_props_99700[2] = d;

    d.name = "mpActiveTool"; d.hash = 0x61c7e4au;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00bceb00;
    d.f28 = (void*)&FUN_00bd1780; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00c87090;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 0x8cu;
    g_props_99700[3] = d;

    d.name = "mpActiveCargoItem"; d.hash = 0x61c7e5du;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00c87630;
    d.f28 = (void*)&FUN_00bd1780; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00c87090;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 0x90u;
    g_props_99700[4] = d;

    d.name = "mMaxItemCountPerItem"; d.hash = 0x649014bu;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00572840; d.f2c = (void*)&FUN_00692ff0;
    d.f30 = (void*)&FUN_00694ee0; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_0057cde0;
    d.offset = 0x48u;
    g_props_99700[5] = d;

    d.name = "mbHasAddedItem"; d.hash = 0x68398c2u;
    d.f18 = 0; d.f1c = (void*)&FUN_00ff3cf0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00ac8750;
    d.f28 = (void*)&FUN_00ac8780; d.f2c = (void*)&FUN_00693090;
    d.f30 = (void*)&FUN_00694fa0; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_0057ce00;
    d.offset = 0x94u;
    g_props_99700[6] = d;

    g_didInit = 1;
}
