// src/game/SPGonzago/SPStar.cpp -- migrated from slice(s) s01353d90, s00c8aa60, s00c8bb00 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPStar.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cBuilding.h"
#include "SP/cCombatant.h"
#include "SP/cGameData.h"
#include "SP/cStar.h"
#include "SP/cString.h"
#include "SP/cTribe.h"

// unnamed retail callees and globals (address in the comment)
extern void* vtStarMain[];       // 0x01473990
extern void* vtStarAux[];        // 0x0147397c
#include <string.h>
#include <math.h>
#include "EA/Text/Font.h"
#include "SP/cVarListSerializer.h"
#include "SP/cSolarSystem.h"
#include <stddef.h>

// ---- items of slice s00c8bb00 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;
typedef unsigned short u16;
extern void* vtStarMain[];       // 0x01473990
extern void* vtStarAux[];        // 0x0147397c
struct MapNodeF {
  MapNodeF* mpRight_00;          // 0x00
  MapNodeF* mpLeft_04;           // 0x04
  MapNodeF* mpParent_08;         // 0x08
  u32       mColor_0c;           // 0x0c
  u32       mKey_10;             // 0x10
  float     mValue_14;           // 0x14
};
struct KeyFloat {                // the value_type passed to DoInsertValue
  u32   mKey_00;
  float mValue_04;
};
struct InsertRet {               // pair<Node*, bool> returned in memory
  MapNodeF* mpNode_00;
  u32       mIsNew_04;
};
struct FloatMap {                // eastl::map<u32, float>
  u32       mPad_00;             // 0x00
  MapNodeF  mAnchor_04;          // 0x04
  MapNodeF* Beg()  { return mAnchor_04.mpLeft_04; }
  MapNodeF* End()  { return &mAnchor_04; }
  MapNodeF* Root() { return mAnchor_04.mpParent_08; }
  InsertRet DoInsertValue(MapNodeF* pos, const KeyFloat* value, bool flag);  // 0x00baa660
  float*    Insert(const u32& key);        // 0x00c8c550
  float*    Find(const u32& key);
};
MapNodeF* __cdecl RBTreeIncrement(MapNodeF* node);            // 0x00921580
void      __cdecl operator_delete_array(void* p);             // 0x00f47380
struct StarPartVtbl {
  void* mSlot_00;
  void* mSlot_04;                // Release
  void* mSlot_08;                // Destroy
};
struct StarPart {
  StarPartVtbl* mpVtbl_00;
  void FUN_00c86e50();
  void Release() { ((void (__thiscall*)(StarPart*))mpVtbl_00->mSlot_04)(this); }
  void Destroy() { ((void (__thiscall*)(StarPart*))mpVtbl_00->mSlot_08)(this); }
};
struct StarMgrPart {             // argument-less star manager entry point
  void FUN_00ba92e0(u32 id);
};
StarMgrPart* __cdecl StarManager();                           // 0x00b3d2a0
struct cBuilding {
  s32    GetEmpireID();          // 0x00a1ad10
  double GetValue();             // 0x00b7e0a0
};
struct cDistrict {
  u8         mPad_00[0x3c];
  cBuilding** mpBegin_3c;        // 0x3c  eastl::vector<cBuilding*>
  cBuilding** mpEnd_40;          // 0x40
  cBuilding** mpCap_44;          // 0x44
  void FUN_00ff2d80();           // 0x00ff2d80
  void FUN_00ff2e30();           // 0x00ff2e30
};
struct cFieldObject {            // elements of the +0x170 vector
  void FUN_00c2e4e0();           // 0x00c2e4e0
};
struct cNoun {
  void**        mpVtbl_00;       // 0x00
  u8            mPad_04[0x24];
  u32           mKind_28;        // 0x28  kind/class (1 and 0 are skipped)
  u8            mPad_2c[0x130];
  cDistrict**   mpDistricts_15c; // 0x15c eastl::vector<cDistrict*>
  cDistrict**   mpDistricts_160; // 0x160
  cDistrict**   mpDistricts_164; // 0x164
  u8            mPad_168[0x08];
  cFieldObject** mpFields_170;   // 0x170 eastl::vector<cFieldObject*>
  cFieldObject** mpFields_174;   // 0x174
  cFieldObject** mpFields_178;   // 0x178
  u8            mPad_17c[0x18];
  u32           mFlag_194;       // 0x194
  bool          FUN_00b8d970();            // 0x00b8d970
  s32           GetMode();                 // 0x00b8dab0
  void          FUN_00b8d920(u32 mode);    // 0x00b8d920
  cDistrict*    GetDistrict(u32 index);    // 0x00b8dec0
  void          FUN_00b8de60();            // 0x00b8de60
  void          FUN_00b8df20();            // 0x00b8df20
  u32*          FUN_00b8e090();            // 0x00b8e090
  void          AddRef() { ((void (__thiscall*)(cNoun*))mpVtbl_00[0])(this); }
  void          Release() { ((void (__thiscall*)(cNoun*))mpVtbl_00[1])(this); }
};
struct PtrVec {                  // eastl::vector<T*> (simulator noun list)
  void** mpBegin;
  void** mpEnd;
  void** mpCap;
};
struct cSim {
  u8      mPad_00[0x0c];
  u32     mLastMinute_0c;        // 0x0c  last processed game minute
  u8      mPad_10[0x4f4];
  u8      mBuffer_504[1];        // 0x504 pointer passed to FUN_00bb9b90
  PtrVec* GetNouns();            // 0x00bba790
  bool    FUN_00bb9c30();        // 0x00bb9c30
  s32     FUN_00bb9ae0();        // 0x00bb9ae0
  void    FUN_00bb9ad0(s32 a);   // 0x00bb9ad0
  void    FUN_00bb9b00(s32 a, s32 b);  // 0x00bb9b00
  void    FUN_00bb9b90(void* p); // 0x00bb9b90
  void    FUN_00a16a90(s32 a);   // 0x00a16a90
};
s32 __cdecl GetPlayerEmpireID();                 // 0x01021090
void __cdecl SetPlanetTechLevel(cNoun* noun, s32 level);  // 0x00c706d0
void __cdecl FUN_00b96f40(cNoun* noun, s32 level);        // 0x00b96f40
struct GameTimeMgr {
  unsigned __int64 FUN_00b316c0();               // 0x00b316c0
};
GameTimeMgr* __cdecl GameTimeManager();          // 0x00b3d380
struct RandomLCG {
  double NextDouble();                           // 0x009360d0
  u32    NextUint32(u32 range);                  // 0x00a68fb0
};
extern RandomLCG gMathRandom;                    // 0x01601760
struct PropValue {
  u8  mPad_00[0x12];
  u16 mType_12;                  // 0x12  type tag (0xd = float)
  float* GetFloat();             // 0x0041ea70
};
struct PropertyVtbl {
  void* mSlot_00;
  void* mSlot_04;
  void* mSlot_08;
  void* mSlot_0c;
  void* mSlot_10;
  void* mSlot_14;
  void* mSlot_18;
  void* mSlot_1c;
  void* mSlot_20;
  void* mValueByKey_24;          // bool (u32 key, PropValue* out)
  void* mSlot_28;
  void* mGetProperty_2c;         // (u32 key, u32 group, Property** out)
};
struct Property {
  PropertyVtbl* mpVtbl_00;
};
struct PropertyMgr {
  PropertyVtbl* mpVtbl_00;
};
PropertyMgr* __cdecl PropertyManager();          // 0x0067de30
struct WString {
  u16* mpBegin_00;
  u16* mpEnd_04;
  u16* mpCap_08;
  void append(const wchar_t* text);              // 0x005c3d90
  void assign(const u16* first, const u16* last);  // 0x00423650
};
struct cString {                 // SP::cString
  u16* mpBegin_00;
  u16* mpEnd_04;
  u16* mpCap_08;
  cString(u32 table, u32 text, const wchar_t* def);  // 0x006b5770
  const wchar_t* GetText();                          // 0x006b55c0
  ~cString();                                        // 0x006b5240
};
struct cTextRef {                // SP::cTextRef (localized text reference)
  u16* mpBegin_00;
  u16* mpEnd_04;
  u16* mpCap_08;
  cTextRef* Make(cTextRef* self, u32 key);       // 0x004010a0
  WString*  GetString();                         // 0x005ecf80
};
struct cStar {
  void**     mpVtbl_00;          // 0x00
  void**     mpVtbl2_04;         // 0x04
  u8         mPad_08[0x24];
  StarPart*  mpPart_2c;          // 0x2c  refcounted part
  u8         mPad_30[0x10];
  StarPart*  mpPart_40;          // 0x40  refcounted part
  u8         mPad_44[0x04];
  u32        mField_48;          // 0x48  star id
  u8         mPad_4c[0x14];
  WString    mName_60;           // 0x60
  s32        GetNameKind();      // 0x00801920
  void       Destroy();          // 0x00c8be70
};
struct cGameData {
  void DestroyGameData();        // 0x00b184c0
};
void SP_GenerateNewStarName(cStar* star);        // 0x00c8bff0
void* __cdecl FUN_00b3d450(u32 key);             // 0x00b3d450
template <class T> const T& MaxRef(const T& a, const T& b) { return a < b ? b : a; }
float* FloatMap::Insert(const u32& key)
{
  MapNodeF* node = mAnchor_04.mpParent_08;
  MapNodeF* lower = &mAnchor_04;
  while (node) {
    if (node->mKey_10 < key)
      node = node->mpRight_00;
    else {
      lower = node;
      node = node->mpLeft_04;
    }
  }
  if (lower != &mAnchor_04 && !(key < lower->mKey_10))
    return &lower->mValue_14;

  KeyFloat value;
  value.mKey_00 = key;
  value.mValue_04 = 0.0f;
  return &DoInsertValue(lower, &value, false).mpNode_00->mValue_14;
}
// ---- items of slice s00c8bb00 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern RandomLCG gMathRandom;                    // 0x01601760

// ---- items of slice s00c8aa60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl operator_new(int size, const char* name, int a, int b, int c, int d); // 0x00f473a0
extern "C" int __cdecl FUN_00801920(void* a, void* b);
extern "C" void* __cdecl cSolarSystem_ctor(void* p);
extern "C" void  __cdecl sub_c86760(void* p);
extern float g_13ec4d0;   // 0x013ec4d0 = 100.0f
#pragma optimize("", off)
struct Sub48 {
    void sub_bb9af0(int v);   // 0x00bb9af0
    void sub_bb9b90(int v);   // 0x00bb9b90
    void sub_bb9ad0(int v);   // 0x00bb9ad0
    void sub_a16a90(void* p); // 0x00a16a90
    int  sub_801920();        // 0x00801920
};
struct Font {
    void SetUserData(void* p); // 0x00fd9450
};
struct Obj48 {
    char pad_00[0x34];
    int  mField34;           // +0x34
    int  mField38;           // +0x38
    char pad_3c[4];
    Font* mpFont;            // +0x40
    char pad_44[4];
    Sub48* mp48;             // +0x48
    int   mField4c;          // +0x4c

    void sub_b560();               // 0x00c8b560
    void sub_b570(int param);      // 0x00c8b570
    void sub_b5c0(void* p);        // 0x00c8b5c0
    void sub_b7d0();               // 0x00c8b7d0
    bool sub_b7e0();               // 0x00c8b7e0
    bool sub_b800();               // 0x00c8b800
    void sub_b6d0(void* param);    // 0x00c8b6d0
};
struct cGameDataStub { void ctor(); };
struct cStar_s00c8_aa60 {
    void** vftable;              // +0x00
    void** vftable2;             // +0x04
    char pad_08[0x34 - 0x08];
    int  mField34;               // +0x34
    int  mField38;               // +0x38
    u8   mFlag3c;                // +0x3c
    char pad_3d[3];
    void* mpSolarSystem;         // +0x40
    u8   mFlag44;                // +0x44
    char pad_45[3];
    void* mpStarRecord;          // +0x48
    int  mKey;                   // +0x4c
    cStar_s00c8_aa60();
    bool Read(int param);        // 0x00c8b3e0
};
struct cSolarSystem { char pad[0x54]; };
struct Owner40 {
    char pad_00[0x40];
    cSolarSystem* mpSolar;       // +0x40
    void sub_b700();
};
struct OwnerObj { void sub_c86e50(); };
struct cGameData_s00c8_aa60 {
    char pad_00[0x2c];
    void* mpOwner2c;             // +0x2c
    char pad_30[0x10];
    OwnerObj* mpOwner40;         // +0x40
    void RemoveOwner();  // 0x00cbb790 (cGameData::RemoveOwner)
};
struct Vec2 { void** pBegin; void** pEnd; };
struct ItemObj {
    u8    pad_00[0x38];
    int   mId;        // +0x38
    float mValue;     // +0x3c
    int   GetId();            // 0x00a1ad10
    void  SetId(int id);      // 0x00ff03b0
    void  SetValue(float v);  // 0x00ff03c0
    float GetValue();         // 0x00b7e0a0
};
struct Obj2 {
    u8        pad_00[0x3c];
    ItemObj** pItems;         // +0x3c
    ItemObj** pItemsEnd;      // +0x40
};
struct Node2 {
    u8      pad_00[0x28];
    int     mKind;            // +0x28
    u8      pad_2c[0x130];
    Obj2**  pObjs;            // +0x15c
    Obj2**  pObjsEnd;         // +0x160
    u8      pad_164[0x30];
    int     mType;            // +0x194
    int     GetType();        // 0x00b8dab0
    char    IsFlagged();      // 0x00b8d970
    Obj2*   GetObj(int i);    // 0x00b8dec0
};
struct View2 {
    Vec2* GetList();          // 0x00bba790
};
// ---- items of slice s00c8aa60 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __cdecl c8b470(int k, int* b, int* c);  // 0x00c8b470 (stays in the slice: not this object's)

// ---- items of slice s01353d90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void DefaultOffset();            // 0x00692ca0  Simulator::Attribute::DefaultOffset
extern void Read4Int();                 // 0x00572810  Simulator::Read4<int>
extern void Write4();                   // 0x00572840  Simulator::Write4
extern void ParseLong();                // 0x00692ff0
extern void WriteTextLong();            // 0x00694ee0
extern void AlwaysValid();              // 0x00b1fbf0
extern void ToXmlInt();                 // 0x0057cde0
extern void ReadULong();                // 0x00ac8750
extern void WriteULong();               // 0x00ac8780
extern void ParseULong();               // 0x00693090
extern void WriteTextULong();           // 0x00694fa0
extern void ToXmlULong();               // 0x0057ce00
extern void WriteTextKey();             // 0x00694f00
extern void ToXmlKey();                 // 0x00675ca0
extern void ReadSolarSystem();          // 0x00c8bfa0
extern void WriteSolarSystem();         // 0x01006600
extern void ReadTextSolarSystem();      // 0x00c2e4e0
extern void WriteTextSolarSystem();     // 0x00692fb0
extern void ValidSolarSystem();         // 0x00fd9e80
extern void ToXmlSolarSystem();         // 0x00ac8050
typedef void (*AttrFn)();
struct cAttributeDesc {
    const char* mpName;                 // +0x00
    const char* mpKey;                  // +0x04
    int mOffset;                        // +0x08
    int mUnk0c;                         // +0x0c  (left indeterminate by the constructor)
    int mUnk10;                         // +0x10
    int mUnk14;                         // +0x14
    int mUnk18;                         // +0x18
    int mUnk1c;                         // +0x1c
    AttrFn mpDefaultOffset;             // +0x20  Simulator::Attribute::DefaultOffset
    AttrFn mpRead;                      // +0x24
    AttrFn mpWrite;                     // +0x28
    AttrFn mpParse;                     // +0x2c
    AttrFn mpTextWrite;                 // +0x30
    AttrFn mpValid;                     // +0x34
    AttrFn mpToXml;                     // +0x38
};
cAttributeDesc gAttributeTable[6];      // 0x0157a828
typedef bool (*ReadFn)(void*, void*);
typedef bool (*WriteFn)(void*, void*);
typedef void (*ReadTextFn)(const void*, void*);
typedef void (*WriteTextFn)(char*, void*);
typedef bool (*UnkFn)();
typedef bool (*Unk2Fn)(void*, const char*, int);
struct Attribute;
typedef void* (*OffsetFn)(Attribute*);
void* DefaultOffset(Attribute*);                       // 0x692ca0
struct Attribute {
  const char* name;
  uint32_t id;
  unsigned offset;
  int field_0C, field_10, field_14;
  void* pCurrentObject;
  int field_1C;
  OffsetFn offsetFunction;
  ReadFn readFunction;
  WriteFn writeFunction;
  ReadTextFn readTextFunction;
  WriteTextFn writeTextFunction;
  UnkFn field_34;
  Unk2Fn field_38;

  Attribute() {}
  __forceinline Attribute(const char* n, uint32_t i, unsigned o, ReadFn r, WriteFn w, ReadTextFn rt,
                          WriteTextFn wt, UnkFn u, Unk2Fn u2) {
    name = n;
    id = i;
    pCurrentObject = 0;
    field_1C = 0;
    offsetFunction = DefaultOffset;
    readFunction = r;
    writeFunction = w;
    readTextFunction = rt;
    writeTextFunction = wt;
    field_34 = u;
    field_38 = u2;
    offset = o;
  }
};
// ---- items of slice s01353d90 end

// @ 0x00c8b450
bool __cdecl c8b450(int k)
{
    if (k == 0) return false;
    if (k <= 6) return false;
    if (k > 0xc) return false;
    return true;
}

// @ 0x00c8b520
bool __cdecl c8b520(int k)
{
    if (k == 0) return false;
    if (k <= 0) return true;
    if (k <= 3) return false;
    return true;
}

// @ 0x00c8b640
cStar_s00c8_aa60::cStar_s00c8_aa60()
{
    ((cGameDataStub*)this)->ctor();
    mField34 = 0;
    mField38 = 0;
    mFlag3c = 0;
    vftable = (void**)0x1473990;
    vftable2 = (void**)0x147397c;
    mpSolarSystem = 0;
    mpStarRecord = 0;
    mFlag44 = 1;
    mKey = -1;
}

// @ 0x00c8b6d0
#pragma optimize("", off)
void Obj48::sub_b6d0(void* param)
{
    mp48 = (Sub48*)param;
    mField4c = *(int*)((char*)param + 0x70);
    int* a = &mField34;
    int* b = &mField38;
    int v = ((int (__fastcall*)(void*))FUN_00801920)(param);
    c8b470(v, a, b);
}
#pragma optimize("", on)

// @ 0x00c8b700
void Owner40::sub_b700()
{
    if (mpSolar) return;
    void* p = operator_new(0x54, "Simulator/cSolarSystem", 0, 0, 0, 0);
    cSolarSystem* n = p ? (cSolarSystem*)cSolarSystem_ctor(p) : 0;
    cSolarSystem* old = mpSolar;
    if (n != old) {
        if (n) ((void(__thiscall*)(void*))(*(void***)n)[4 / 4])(n);
        mpSolar = n;
        if (old) ((void(__thiscall*)(void*))(*(void***)old)[8 / 4])(old);
    }
    sub_c86760(this);
}

// @ 0x00c8b790
void cGameData_s00c8_aa60::RemoveOwner()
{
    if (mpOwner40) {
        mpOwner40->sub_c86e50();
        OwnerObj* b = mpOwner40;
        if (b) {
            mpOwner40 = 0;
            ((void(__thiscall*)(void*))(*(void***)b)[8 / 4])(b);
        }
    }
    void* c = mpOwner2c;
    if (c) {
        mpOwner2c = 0;
        ((void(__thiscall*)(void*))(*(void***)c)[4 / 4])(c);
    }
}

// @ 0x00c8b7d0
void Obj48::sub_b7d0()
{
    if (mpFont) mpFont->SetUserData(this);
}

// @ 0x00c8b7e0
bool Obj48::sub_b7e0()
{
    int k = mp48->sub_801920();
    if (k != 0) { unsigned int v = (unsigned int)(k - 7); return v <= 5u; }
    return false;
}

// @ 0x00c8b800
bool Obj48::sub_b800()
{
    int k = mp48->sub_801920();
    if (k != 0) { unsigned int v = (unsigned int)(k - 1); return v > 2u; }
    return false;
}

// @ 0x00c8b820
void __cdecl c8b820(void* view, int id)
{
    Vec2* list = ((View2*)view)->GetList();
    int n = (int)(list->pEnd - list->pBegin);
    for (int i = 0; i < n; ++i) {
        Node2* node = (Node2*)list->pBegin[i];
        int kind = node->mKind;
        if (kind == 1 || kind == 0) continue;
        if (node->IsFlagged()) continue;
        int j = 0;
        int n2 = (int)(node->pObjsEnd - node->pObjs);
        for (; j < n2; ++j) {
            Obj2* obj = node->GetObj(j);
            int n3 = (int)(obj->pItemsEnd - obj->pItems);
            for (int k = 0; k < n3; ++k) {
                ItemObj* item = obj->pItems[k];
                if (item->GetId() == id) {
                    item->SetId(-1);
                    item->SetValue(0.0f);
                }
            }
        }
    }
}

// @ 0x00c8b920
bool __cdecl c8b920(void* view, int id)
{
    Node2* node = (Node2*)view;
    if (node->GetType() == 5) {
        int kind = node->mKind;
        if (kind != 1 && kind != 0 && !node->IsFlagged()) {
            int j = 0;
            int n2 = (int)(node->pObjsEnd - node->pObjs);
            for (; j < n2; ++j) {
                Obj2* obj = node->GetObj(j);
                int n3 = (int)(obj->pItemsEnd - obj->pItems);
                for (int k = 0; k < n3; ++k) {
                    ItemObj* item = obj->pItems[k];
                    if (item->GetId() != id) return false;
                    if (item->GetValue() < g_13ec4d0) return false;
                }
            }
            if (node->pObjs != node->pObjsEnd) return true;
        }
    }
    return false;
}

// @ 0x00c8ba00
bool __cdecl c8ba00(void* view)
{
    Node2* node = (Node2*)view;
    if (node->GetType() == 5) {
        int kind = node->mKind;
        if (kind != 1 && kind != 0 && !node->IsFlagged()) {
            int first = -1;
            int j = 0;
            int n2 = (int)(node->pObjsEnd - node->pObjs);
            for (; j < n2; ++j) {
                Obj2* obj = node->GetObj(j);
                int n3 = (int)(obj->pItemsEnd - obj->pItems);
                for (int k = 0; k < n3; ++k) {
                    ItemObj* item = obj->pItems[k];
                    if (item->GetValue() != g_13ec4d0) return false;
                    if (first == -1) first = item->GetId();
                    if (first != item->GetId()) return false;
                }
            }
            if (node->pObjs != node->pObjsEnd) return true;
        }
    }
    return false;
}

// @ 0x00c8bb00
bool FUN_00c8bb00(cSim* sim)
{
  PtrVec* nouns = sim->GetNouns();
  s32 nounCount = nouns->mpEnd - nouns->mpBegin;
  for (s32 i = 0; i < nounCount; ++i) {
    cNoun* noun = (cNoun*)nouns->mpBegin[i];
    if (noun->mKind_28 == 1 || noun->mKind_28 == 0)
      continue;
    if (noun->FUN_00b8d970())
      continue;
    for (s32 d = 0, districtCount = noun->mpDistricts_160 - noun->mpDistricts_15c;
         d < districtCount; ++d) {
      cDistrict* district = noun->GetDistrict(d);
      s32 buildingCount = district->mpEnd_40 - district->mpBegin_3c;
      for (s32 b = 0; b < buildingCount; ++b) {
        cBuilding* building = district->mpBegin_3c[b];
        if (building->GetEmpireID() == GetPlayerEmpireID()
            && building->GetValue() > 0.0)
          return true;
      }
    }
  }
  return false;
}

// @ 0x00c8bc10
void FUN_00c8bc10(cSim* sim)
{
  if (sim->FUN_00bb9c30())
    return;
  s32 mode = sim->FUN_00bb9ae0();
  if (mode == 0 || mode == 5)
    return;

  PtrVec* nouns = sim->GetNouns();
  s32 nounCount = nouns->mpEnd - nouns->mpBegin;
  cNoun* noun = 0;
  for (s32 i = 0; i < nounCount; ++i) {
    cNoun* candidate = (cNoun*)nouns->mpBegin[i];
    if (candidate->GetMode() == mode && candidate->mKind_28 > 2) {
      noun = candidate;
      break;
    }
  }
  if (!noun)
    return;

  unsigned __int64 stamp = GameTimeManager()->FUN_00b316c0() / 60000;
  if (sim->mLastMinute_0c == 0)
    sim->mLastMinute_0c = (u32)stamp;
  s32 elapsed = (s32)((u32)stamp - sim->mLastMinute_0c);
  if (elapsed <= 0)
    return;
  sim->mLastMinute_0c = (u32)stamp;

  Property* prop = 0;
  PropertyMgr* mgr = PropertyManager();
  if (prop) {
    Property* old = prop;
    prop = 0;
    ((void (__thiscall*)(Property*))((void**)old->mpVtbl_00)[1])(old);
  }
  ((void (__thiscall*)(PropertyMgr*, u32, u32, Property**))
      mgr->mpVtbl_00->mGetProperty_2c)(mgr, 0x249e8357, 0x2ae0c7e, &prop);

  float rate = 240.0f;
  if (prop) {
    PropValue value;
    bool found = ((bool (__thiscall*)(Property*, u32, PropValue*))
        prop->mpVtbl_00->mValueByKey_24)(prop, 0x5ff5b59, &value);
    if (found && value.mType_12 == 0xd) {
      rate = *value.GetFloat();
      if (rate <= 0.0f)
        rate = 240.0f;
    }
  }

  if (gMathRandom.NextDouble() > 1.0 - exp((double)elapsed / rate * -0.30103f)) {
    noun->FUN_00b8de60();
    noun->FUN_00b8df20();
    switch (noun->GetMode()) {
    case 1:
      SetPlanetTechLevel(noun, 2);
      if (*noun->FUN_00b8e090() == 0) {
        void* manager = FUN_00b3d450(0x876201aa);
        void* world = ((void* (__thiscall*)(void*))0x00ac10a0)(manager);
        if (world)
          sim->FUN_00bb9b90((char*)world + 0x504);
      }
      FUN_00b96f40(noun, 2);
      break;
    case 2:
      if (gMathRandom.NextDouble() <= 0.5) {
        SetPlanetTechLevel(noun, 1);
      } else {
        SetPlanetTechLevel(noun, 4);
        FUN_00b96f40(noun, 4);
      }
      break;
    case 4:
      SetPlanetTechLevel(noun, 2);
      FUN_00b96f40(noun, 2);
      break;
    }
  }

  if (prop) {
    Property* old = prop;
    prop = 0;
    ((void (__thiscall*)(Property*))((void**)old->mpVtbl_00)[1])(old);
  }
}

// @ 0x00c8be70
void cStar::Destroy()
{
  u32 starId = mField_48;
  mpVtbl_00 = vtStarMain;
  mpVtbl2_04 = vtStarAux;
  StarManager()->FUN_00ba92e0(starId);
  if (mpPart_40) {
    mpPart_40->FUN_00c86e50();
    StarPart* part = mpPart_40;
    if (part) {
      mpPart_40 = 0;
      part->Destroy();
    }
  }
  if (mpPart_2c) {
    StarPart* part = mpPart_2c;
    mpPart_2c = 0;
    part->Release();
  }
  if (mpPart_40) {
    StarPart* part = mpPart_40;
    part->Destroy();
  }
  ((cGameData*)this)->DestroyGameData();
}

// @ 0x00c8bee0
float FUN_00c8bee0(FloatMap* map, s32 count, s32* outKey)
{
  float current = -1.0f;
  float sum = 0.0f;
  for (MapNodeF* node = map->Beg(); node != map->End();
       node = RBTreeIncrement(node)) {
    if (node->mValue_14 > current) {
      if (*outKey != -1)
        sum = sum + current;
      *outKey = (s32)node->mKey_10;
      current = node->mValue_14;
    } else {
      sum = node->mValue_14 + sum;
    }
  }
  if (*outKey != -1)
    return MaxRef(current - sum, 0.0f) / count;
  return current;
}

// @ 0x00c8bff0
void SP_GenerateNewStarName(cStar* star)
{
  switch (star->GetNameKind()) {
  case 1: {
    cString text(0x2db6dad3, 0x591bd91, 0);
    star->mName_60.append(text.GetText());
    text.~cString();
    return;
  }
  case 2: {
    cTextRef ref;
    WString* name = ref.Make(&ref, 0xdeb2d943)->GetString();
    if (name != &star->mName_60)
      star->mName_60.assign(name->mpBegin_00, name->mpEnd_04);
    if ((((u32)ref.mpEnd_04 - (u32)ref.mpBegin_00) & ~1u) > 2 && ref.mpBegin_00)
      operator_delete_array(ref.mpBegin_00);
    return;
  }
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 11:
  case 12: {
    cTextRef ref;
    WString* name = ref.Make(&ref, 0x7cab064c)->GetString();
    if (name != &star->mName_60)
      star->mName_60.assign(name->mpBegin_00, name->mpEnd_04);
    if ((((u32)ref.mpEnd_04 - (u32)ref.mpBegin_00) & ~1u) > 2 && ref.mpBegin_00)
      operator_delete_array(ref.mpBegin_00);
    return;
  }
  }
}

// @ 0x013547b0
void InitAttributeTable()
{
    cAttributeDesc d;

    d.mpName = (const char*)0x01473a38;
    d.mpKey = (const char*)0x041f80ad;
    d.mUnk18 = 0;
    d.mUnk1c = 0;
    d.mpDefaultOffset = &DefaultOffset;
    d.mpRead = &Read4Int;
    d.mpWrite = &Write4;
    d.mpParse = &ParseLong;
    d.mpTextWrite = &WriteTextLong;
    d.mpValid = &AlwaysValid;
    d.mpToXml = &ToXmlInt;
    d.mOffset = 0x34;
    gAttributeTable[0] = d;

    d.mpName = (const char*)0x01473a28;
    d.mpKey = (const char*)0x041f80b0;
    d.mUnk18 = 0;
    d.mUnk1c = 0;
    d.mpDefaultOffset = &DefaultOffset;
    d.mpRead = &Read4Int;
    d.mpWrite = &Write4;
    d.mpParse = &ParseLong;
    d.mpTextWrite = &WriteTextLong;
    d.mpValid = &AlwaysValid;
    d.mpToXml = &ToXmlInt;
    d.mOffset = 0x38;
    gAttributeTable[1] = d;

    d.mpName = (const char*)0x01473a14;
    d.mpKey = (const char*)0x03755020;
    d.mUnk18 = 0;
    d.mUnk1c = 0;
    d.mpDefaultOffset = &DefaultOffset;
    d.mpRead = &ReadULong;
    d.mpWrite = &WriteULong;
    d.mpParse = &ParseULong;
    d.mpTextWrite = &WriteTextULong;
    d.mpValid = &AlwaysValid;
    d.mpToXml = &ToXmlULong;
    d.mOffset = 0x3c;
    gAttributeTable[2] = d;

    d.mpName = (const char*)0x01465750;
    d.mpKey = (const char*)0x0355fa98;
    d.mUnk18 = 0;
    d.mUnk1c = 0;
    d.mpDefaultOffset = &DefaultOffset;
    d.mpRead = &Read4Int;
    d.mpWrite = &Write4;
    d.mpParse = &ParseULong;
    d.mpTextWrite = &WriteTextKey;
    d.mpValid = &AlwaysValid;
    d.mpToXml = &ToXmlKey;
    d.mOffset = 0x4c;
    gAttributeTable[3] = d;

    d.mpName = (const char*)0x01473a04;
    d.mpKey = (const char*)0x039d4a3f;
    d.mUnk18 = 0;
    d.mUnk1c = 0;
    d.mpDefaultOffset = &DefaultOffset;
    d.mpRead = &ReadSolarSystem;
    d.mpWrite = &WriteSolarSystem;
    d.mpParse = &ReadTextSolarSystem;
    d.mpTextWrite = &WriteTextSolarSystem;
    d.mpValid = &ValidSolarSystem;
    d.mpToXml = &ToXmlSolarSystem;
    d.mOffset = 0x40;
    gAttributeTable[4] = d;

    d.mpName = (const char*)0x014739f0;
    d.mpKey = (const char*)0x056cfe97;
    d.mUnk18 = 0;
    d.mUnk1c = 0;
    d.mpDefaultOffset = &DefaultOffset;
    d.mpRead = &ReadULong;
    d.mpWrite = &WriteULong;
    d.mpParse = &ParseULong;
    d.mpTextWrite = &WriteTextULong;
    d.mpValid = &AlwaysValid;
    d.mpToXml = &ToXmlULong;
    d.mOffset = 0x44;
    gAttributeTable[5] = d;
}
