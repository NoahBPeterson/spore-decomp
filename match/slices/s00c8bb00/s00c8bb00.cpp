// match/slices/s00c8bb00/s00c8bb00.cpp
// Object file: Simulator/... (SP::DoEvolutionSim and the star / city-size helpers).
//
// Targets: 00c8bb00 00c8bc10 00c8be70 00c8bee0 00c8bff0 00c8c0f0
//          00c8c2a0 00c8c420 00c8c550 00c8c5d0 00c8c7f0
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//   Scalar float work is SSE; every int<->float conversion that feeds an x87
//   division and the double exp() sequence use x87 (fild / fdivr / fldl2e),
//   which is what VS2008 emits under /arch:SSE with /fp:fast.
//
// The simulator / noun / tribe layouts are recovered by role only: every member
// below is named after what the code does with it and the eastl containers keep
// their real three-pointer shape, so the rbtree map<unsigned int, float> and
// the refcounted pointer vectors stay readable.

#include <string.h>
#include <math.h>

typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;
typedef unsigned short u16;

// ---------------------------------------------------------------------------
// vtables (addressed by hand: only the class's own vptr stores are modelled)
// ---------------------------------------------------------------------------
extern void* vtStarMain[];       // 0x01473990
extern void* vtStarAux[];        // 0x0147397c

// ---------------------------------------------------------------------------
// eastern rbtree map<u32, float>
//   map     = { u32 mPad_00; Node mAnchor_04; }
//   Node    = { right@0, left@4, parent@8, color@0xc, key@0x10, value@0x14 }
// ---------------------------------------------------------------------------
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

// out-of-line red-black helpers
MapNodeF* __cdecl RBTreeIncrement(MapNodeF* node);            // 0x00921580
void      __cdecl DoNukeSubtree(MapNodeF* node);              // 0x009a9600
void      __cdecl operator_delete_array(void* p);             // 0x00f47380

// ---------------------------------------------------------------------------
// Reference-counted interface objects addressed through their vtable.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// Simulator / nouns / districts / buildings
// ---------------------------------------------------------------------------
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

struct cNounVec {                // eastl::vector<cNoun*> with intrusive refcounts
  cNoun** mpBegin_00;
  cNoun** mpEnd_04;
  cNoun** mpCap_08;
  void Grow(cNoun** value);                     // 0x00aea5d0
  void Push(cNoun* item) {
    if (mpEnd_04 < mpCap_08) {
      cNoun** slot = mpEnd_04++;
      if (slot) {
        *slot = item;
        if (item)
          item->AddRef();
      }
    } else {
      Grow(&item);
    }
  }
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
unsigned __int64 __cdecl aulldiv(unsigned __int64 a, unsigned __int64 b);  // 0x011e0970

// random numbers
struct RandomLCG {
  double NextDouble();                           // 0x009360d0
  u32    NextUint32(u32 range);                  // 0x00a68fb0
};
extern RandomLCG gMathRandom;                    // 0x01601760

// ---------------------------------------------------------------------------
// Property bag (vtable slot 0x2c = GetProperty, 0x24 = GetValue by key)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// Loc strings (GenerateNewStarName)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// Tribes (ReduceCitySize)
// ---------------------------------------------------------------------------
struct cCombatant {
  u32 GetDamageState();          // 0x008e7f80
};

struct cMember {
  void**      mpVtbl_00;         // 0x00
  u8          mPad_04[0x11c];
  cCombatant  mCombat_120;       // 0x120
  void Release() { ((void (__thiscall*)(cMember*))mpVtbl_00[1])(this); }
};

struct MemberPool {              // SP::cTribe::GetMembers() result
  cMember** mpBegin_00;
  cMember** mpEnd_04;
  u32       mPad_08;
  void*     mpAlloc_0c;          // 0x0c
};

struct MemberVec {               // temporary refcounted pointer vector
  cMember** mpBegin_00;
  cMember** mpEnd_04;
  cMember** mpCap_08;
  void Init(s32 count, void* alloc);             // 0x00b93c60
};

struct cTribe {
  s32      GetSizeY();           // 0x00bd9b70
  s32      GetSizeX();           // 0x00bd9bb0
  void*    GetCityHall();        // 0x00bd9b40
  void     FUN_00be2070(s32 a, s32 b);           // 0x00be2070
  MemberPool* GetMembers();      // 0x00c8e810
};

struct CityHall {
  void** mpVtbl_00;
  void*  GetMayor(u32 role);     // vtable slot 0x0c
};

void __cdecl FUN_00829110(MemberVec* out, cMember** begin, cMember** end,
                          cMember** pool, void* hall);     // 0x00829110
void __cdecl FUN_00be33e0(cMember* member);                // 0x00be33e0

// ===========================================================================
// 0x00c8bb00 - true when the player owns a building in a live noun that is
// worth something (used to decide whether the evolution sim has anything to do)
// ===========================================================================
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

// ===========================================================================
// 0x00c8bc10 - SP::DoEvolutionSim: one minute of noun evolution
// ===========================================================================
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

// ===========================================================================
// 0x00c8be70 - cStar destructor body (the class dtor chains into cGameData)
// ===========================================================================
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

// ===========================================================================
// 0x00c8bee0 - pick the most valuable key of a star map and return the
// (clamped) average value of the remaining ones
// ===========================================================================
template <class T> const T& MaxRef(const T& a, const T& b) { return a < b ? b : a; }

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

// ===========================================================================
// 0x00c8bff0 - SP::GenerateNewStarName
// ===========================================================================
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

// ===========================================================================
// 0x00c8c0f0 - SP::ReduceCitySize
// ===========================================================================
// @ 0x00c8c0f0
void FUN_00c8c0f0(cTribe* tribe, float frac, s32 minKeep)
{
  s32 total = tribe->GetSizeX() + tribe->GetSizeY() - 1;
  if (total <= 0)
    return;

  float totalf = (float)total;
  s32 cut = (s32)(totalf * frac);
  s32 keep = total - cut;
  if (total - keep < minKeep)
    keep = total - minKeep;

  float keepY = (float)(tribe->GetSizeY() * keep) / totalf;
  s32 roomY = tribe->GetSizeY() - (s32)keepY;
  float keepX = (float)((tribe->GetSizeX() - 1) * keep) / totalf;
  s32 roomX = tribe->GetSizeX() - (s32)keepX - 1;

  void* hall = 0;
  CityHall* cityHall = (CityHall*)tribe->GetCityHall();
  if (cityHall)
    hall = ((void* (__thiscall*)(CityHall*, u32))
        cityHall->mpVtbl_00[3])(cityHall, 0xe9cb8ba);

  for (s32 i = 0; i < roomY; ++i)
    tribe->FUN_00be2070(0, 0);

  MemberPool* members = tribe->GetMembers();
  MemberVec pool;
  pool.Init(members->mpEnd_04 - members->mpBegin_00, members->mpAlloc_0c);

  MemberVec kept;
  FUN_00829110(&kept, members->mpBegin_00, members->mpEnd_04,
               pool.mpBegin_00, hall);

  s32 index = kept.mpEnd_04 - kept.mpBegin_00;
  while (--index >= 0 && roomX > 0) {
    cMember* member = kept.mpBegin_00[index];
    if (member != hall && member->mCombat_120.GetDamageState() == 0) {
      FUN_00be33e0(member);
      --roomX;
    }
  }

  for (cMember** p = kept.mpBegin_00; p < kept.mpEnd_04; ++p) {
    if (*p)
      (*p)->Release();
  }
  if (kept.mpBegin_00 && kept.mpBegin_00[-1])
    operator_delete_array(kept.mpBegin_00);
}

// ===========================================================================
// 0x00c8c2a0 - reset every noun's simulation state before re-running the sim
// ===========================================================================
// @ 0x00c8c2a0
void FUN_00c8c2a0(cSim* sim)
{
  sim->FUN_00bb9ad0(1);
  sim->FUN_00a16a90(-1);
  sim->FUN_00bb9b00(4, 0);

  PtrVec* nouns = sim->GetNouns();
  s32 nounCount = nouns->mpEnd - nouns->mpBegin;
  for (s32 i = 0; i < nounCount; ++i) {
    cNoun* noun = (cNoun*)nouns->mpBegin[i];
    noun->FUN_00b8d920(0);
    if (noun->GetMode() > 1) {
      noun->mFlag_194 = 1;

      s32 districtCount = noun->mpDistricts_160 - noun->mpDistricts_15c;
      for (s32 d = 0; d < districtCount; ++d) {
        cDistrict* district = noun->mpDistricts_15c[d];
        district->FUN_00ff2d80();
        if (district) {
          district->FUN_00ff2e30();
          operator_delete_array(district);
        }
      }
      memcpy(noun->mpDistricts_15c, noun->mpDistricts_160,
             (char*)noun->mpDistricts_160 - (char*)noun->mpDistricts_160);
      noun->mpDistricts_160 = noun->mpDistricts_15c;

      s32 fieldCount = noun->mpFields_174 - noun->mpFields_170;
      for (s32 f = 0; f < fieldCount; ++f) {
        cFieldObject* field = noun->mpFields_170[f];
        if (field) {
          field->FUN_00c2e4e0();
          operator_delete_array(field);
        }
      }
      memcpy(noun->mpFields_170, noun->mpFields_174,
             (char*)noun->mpFields_174 - (char*)noun->mpFields_174);
      noun->mpFields_174 = noun->mpFields_170;
    }
  }
}

// ===========================================================================
// 0x00c8c420 - pick a random noun in mode 5
// ===========================================================================
// @ 0x00c8c420
cNoun* FUN_00c8c420(cSim* sim)
{
  PtrVec* nouns = sim->GetNouns();
  s32 nounCount = nouns->mpEnd - nouns->mpBegin;

  cNounVec picked;
  picked.mpBegin_00 = 0;
  picked.mpEnd_04 = 0;
  picked.mpCap_08 = 0;

  for (s32 i = 0; i < nounCount; ++i) {
    cNoun* noun = (cNoun*)nouns->mpBegin[i];
    if (noun->GetMode() == 5 && !noun->FUN_00b8d970())
      picked.Push(noun);
  }

  if (picked.mpBegin_00 != picked.mpEnd_04) {
    u32 index = gMathRandom.NextUint32((u32)(picked.mpEnd_04 - picked.mpBegin_00));
    cNoun* noun = picked.mpBegin_00[index];
    for (cNoun** p = picked.mpBegin_00; p < picked.mpEnd_04; ++p) {
      if (*p)
        (*p)->Release();
    }
    if (picked.mpBegin_00 && picked.mpBegin_00[-1])
      operator_delete_array(picked.mpBegin_00);
    return noun;
  }
  if (picked.mpBegin_00 && picked.mpBegin_00[-1])
    operator_delete_array(picked.mpBegin_00);
  return 0;
}

// ===========================================================================
// 0x00c8c550 - map<u32,float> find-or-insert (returns the mapped value)
// ===========================================================================
// @ 0x00c8c550
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

// @ 0x00c8c550 (inline sibling used by the two accumulators below)
float* FloatMap::Find(const u32& key)
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
  return 0;
}

// ===========================================================================
// 0x00c8c5d0 - value of every building owned by each empire (all nouns)
// ===========================================================================
// @ 0x00c8c5d0
float FUN_00c8c5d0(cSim* sim, s32* outKey)
{
  PtrVec* nouns = sim->GetNouns();
  FloatMap map;
  map.mAnchor_04.mpParent_08 = 0;
  map.mAnchor_04.mpLeft_04 = &map.mAnchor_04;
  map.mAnchor_04.mpRight_00 = &map.mAnchor_04;
  map.mAnchor_04.mColor_0c = 0;
  map.mAnchor_04.mKey_10 = 0;

  float fNounCount = (float)(s32)(nouns->mpEnd - nouns->mpBegin);
  s32 total = 0;
  for (s32 i = 0; i < (s32)fNounCount; ++i) {
    cNoun* noun = (cNoun*)nouns->mpBegin[i];
    if (noun->mKind_28 == 1 || noun->mKind_28 == 0)
      continue;
    if (noun->FUN_00b8d970())
      continue;
    s32 districtCount = noun->mpDistricts_160 - noun->mpDistricts_15c;
    for (s32 d = 0; d < districtCount; ++d) {
      cDistrict* district = noun->GetDistrict(d);
      s32 buildingCount = district->mpEnd_40 - district->mpBegin_3c;
      total += buildingCount;
      for (s32 b = 0; b < buildingCount; ++b) {
        cBuilding* building = district->mpBegin_3c[b];
        if (building->GetEmpireID() != -1) {
          float* slot = map.Find(building->GetEmpireID());
          if (!slot)
            slot = map.Insert(building->GetEmpireID());
          *slot = *slot + (float)building->GetValue();
        }
      }
    }
  }

  s32 key = -1;
  float result = FUN_00c8bee0(&map, total, &key);
  *outKey = key;

  MapNodeF* node = map.mAnchor_04.mpParent_08;
  while (node) {
    DoNukeSubtree(node->mpRight_00);
    MapNodeF* next = node->mpLeft_04;
    operator_delete_array(node);
    node = next;
  }
  return result;
}

// ===========================================================================
// 0x00c8c7f0 - value of every building owned by each empire (one noun)
// ===========================================================================
// @ 0x00c8c7f0
float FUN_00c8c7f0(cNoun* noun, s32* outKey)
{
  FloatMap map;
  map.mAnchor_04.mpParent_08 = 0;
  map.mAnchor_04.mpLeft_04 = &map.mAnchor_04;
  map.mAnchor_04.mpRight_00 = &map.mAnchor_04;
  map.mAnchor_04.mColor_0c = 0;
  map.mAnchor_04.mKey_10 = 0;

  s32 total = 0;
  if (noun->mKind_28 != 1 && noun->mKind_28 != 0 && !noun->FUN_00b8d970()) {
    float fDistrictCount = (float)(s32)(noun->mpDistricts_160 - noun->mpDistricts_15c);
    for (s32 d = 0; d < (s32)fDistrictCount; ++d) {
      cDistrict* district = noun->GetDistrict(d);
      s32 buildingCount = district->mpEnd_40 - district->mpBegin_3c;
      total += buildingCount;
      for (s32 b = 0; b < buildingCount; ++b) {
        cBuilding* building = district->mpBegin_3c[b];
        if (building->GetEmpireID() != -1) {
          float* slot = map.Find(building->GetEmpireID());
          if (!slot)
            slot = map.Insert(building->GetEmpireID());
          *slot = *slot + (float)building->GetValue();
        }
      }
    }
  }

  s32 key = -1;
  float result = FUN_00c8bee0(&map, total, &key);
  *outKey = key;

  MapNodeF* node = map.mAnchor_04.mpParent_08;
  while (node) {
    DoNukeSubtree(node->mpRight_00);
    MapNodeF* next = node->mpLeft_04;
    operator_delete_array(node);
    node = next;
  }
  return result;
}
