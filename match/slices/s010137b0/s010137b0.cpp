// match/slices/s010137b0/s010137b0.cpp
// Object file: Simulator/SPGrobShock.obj  (SP::cSimulatorUniverse, the GrobShock
// record helpers and the GrobTeaseRaidEvent raid hooks).
//
// Targets: 010137b0 01013a70 01013ba0 01013d20 01013ec0 01013f20 01014090
//          01014220 010143d0 010144c0 01014540
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2
//   Scalar float work is SSE (movss / maxss / minss) while the unsigned __int64
//   to float conversion still uses the x87 fild sequence, which VS2008 emits
//   with /arch:SSE2 as well.
//
// The simulator-universe layout is only partly recovered: every member below is
// named by role and the containers keep their real three-pointer shape so that
// the eastl idioms (find / operator[] / erase / DoInsertValue) stay readable.

typedef unsigned int       u32;
typedef int                s32;
typedef unsigned char      u8;
typedef unsigned __int64   u64;

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------------------
// Allocator entry points (declared only).
// ---------------------------------------------------------------------------
void* __cdecl EAAlloc(u32 size, const char* area, s32 a, s32 b,
                      const char* file, s32 line);     // operator_new overload
void  __cdecl EAFree(void* p);                         // operator_delete

// ---------------------------------------------------------------------------
// Containers
// ---------------------------------------------------------------------------
struct U32Vec {                          // eastl::vector<unsigned int>
  u32* mpBegin;                          // 0x00
  u32* mpEnd;                            // 0x04
  u32* mpCap;                            // 0x08
};

struct StarVec {                         // SPVector<unsigned int> (with alloc)
  u32*  mpBegin;                         // 0x00
  u32*  mpEnd;                           // 0x04
  u32*  mpCap;                           // 0x08
  void* mpAlloc;                         // 0x0c
};

struct cStarRefVec {                     // vector<EA::AutoRefCount<cStarRecord>>
  void* mpBegin;                         // 0x00
  void* mpEnd;                           // 0x04
  void* mpCap;                           // 0x08
  void* FUN_01011cc0(StarVec* stars);    // 0x01011cc0
};

// ---------------------------------------------------------------------------
// Terrain / star / empire objects
// ---------------------------------------------------------------------------
struct cTerrainSphere {
  float GetTerrainRadius();              // 0x00c75c30
  u8    FUN_00c77410();                  // 0x00c77410
};

struct cTerrainEditor {
  cTerrainSphere* GetCurrentTerrainSphere(u32 key);  // 0x00f67d90
};

struct cEmpire {
  u8  mPad_00[0x50];                     // 0x00
  u32 mFlags_50;                         // 0x50
  u8  mPad_54[0x30];                     // 0x54
  u32 mId_84;                            // 0x84
  u32 GetHomePlanet();                   // SP::cEmpire::GetHomePlanet
  s32 HasDemandForTributeExpired();      // SP::cEmpire::HasDemandForTributeExpired
  s32 FUN_00c31bf0(u32 empire);          // 0x00c31bf0
  void FUN_00c30bb0();                   // 0x00c30bb0
  s32 FUN_00c30b30();                    // 0x00c30b30
  s32 FUN_00c32610();                    // 0x00c32610
};

struct cStarRecord {
  u8        mPad_00[0x14];               // 0x00
  cEmpire*  mpOwner_14;                  // 0x14
};

struct cStarManager {
  s32      FUN_00885c90();               // 0x00885c90
  void*    FUN_00ba6430();               // 0x00ba6430 (the star map)
  cEmpire* GetEmpireByID(u32 id);        // 0x00ba9370
};

struct cStarTable {
  u8      mPad_00[0x18];                 // 0x00
  StarVec mStars_18;                     // 0x18
  u8      mPad_28[4];                    // 0x28
  StarVec mStars2_2c;                    // 0x2c
};

// ---------------------------------------------------------------------------
// Red-black map nodes.  The tree keeps its begin pointer in the anchor's right
// child and its root in the anchor's parent, as the decompiled walks show.
// ---------------------------------------------------------------------------
struct MapNode {
  MapNode* mpLeft;                       // 0x00
  MapNode* mpRight;                      // 0x04
  MapNode* mpParent;                     // 0x08
  u32      mColor;                       // 0x0c
  u32      mKey;                         // 0x10
  cEmpire* mpEmpire;                     // 0x14
  u64      mStamp;                       // 0x18
};

struct EmpireMap {                       // eastl::map<u32, pair<cEmpire*,u64>>
  u8       mPad_00[4];                   // 0x00
  MapNode  mAnchor_04;                   // 0x04
  MapNode* Begin() { return mAnchor_04.mpRight; }
  MapNode* End()   { return &mAnchor_04; }
  MapNode* Root()  { return mAnchor_04.mpParent; }
  u64*     Index(u32 key);               // 0x01012c20
};

struct FloatMap {                        // eastl::map<u32, float>
  u8       mPad_00[4];                   // 0x00
  MapNode  mAnchor_04;                   // 0x04
  MapNode* Begin() { return mAnchor_04.mpRight; }
  MapNode* End()   { return &mAnchor_04; }
  MapNode* Find(const float* key);       // 0x00e5c780
  float*   Index(const float* key);      // 0x00c8c550
};

// ---------------------------------------------------------------------------
// cGonzagoTimer: the 0x20-byte timer embedded at tGrobShockData+8.  Its first
// two dwords are not part of the element copy (see DoInsertValue).
// ---------------------------------------------------------------------------
struct cGonzagoTimer {
  void* mpTable_00;                      // 0x00 (not copied)
  u32   mPad_04;                         // 0x04 (not copied)
  u32   mA_08;                           // 0x08
  u32   mB_0c;                           // 0x0c
  u32   mC_10;                           // 0x10
  u32   mD_14;                           // 0x14
  u8    mFlag_18;                        // 0x18
  u32   mE_1c;                           // 0x1c
  ~cGonzagoTimer();                      // 0x00b638b0
};

// SP::cSimulatorUniverse::tGrobShockData  (0x28 bytes)
struct tGrobShockData {
  u32           mId_00;                  // 0x00
  u32           mField_04;               // 0x04
  cGonzagoTimer mTimer_08;               // 0x08
};

typedef bool (__cdecl* ShockCompare)(const tGrobShockData&, const tGrobShockData&);

struct ShockVec {                        // eastl::vector<tGrobShockData>
  tGrobShockData* mpBegin;               // 0x00
  tGrobShockData* mpEnd;                 // 0x04
  tGrobShockData* mpCap;                 // 0x08
  tGrobShockData* erase(tGrobShockData* first, tGrobShockData* last);
  void  DoInsertValue(tGrobShockData* pos, const tGrobShockData& value);
};

// ---------------------------------------------------------------------------
// Mission / raid interfaces
// ---------------------------------------------------------------------------
struct cShockObj {                       // the objects held by the shock records
  virtual u32  v00();                    // 0x00
  virtual s32  v04(u32 id, U32Vec* out);// 0x04
  virtual u32  v08();                    // 0x08
  virtual u32  v0c();                    // 0x0c
};

struct cMissionIface {                   // the mission face passed to the raids
  virtual u32 v00();                     // 0x00
  virtual u32 v04(u32 id, u32 param);    // 0x04
};

struct cSPMission {
  virtual void  v00();                   // 0x00
  virtual void  v04();                   // 0x04
  virtual void* v08(u32);                // 0x08
  virtual void* v0c(u32);                // 0x0c
  u8     mPad_04[0x130];                 // 0x04
  U32Vec mVec_134;                       // 0x134
  u8     mPad_140[0xc0];                 // 0x140
  u32    mMissionID_200;                 // 0x200
  u32    mElapsedTimeMS_204;             // 0x204
  void   Accept();                       // 0x00c485b0
};

struct cSPRaidEvent : cSPMission {
  s32 GenerateBomberCount();             // 0x00c5b530
  s32 GeneratePirateCount();             // 0x00c5b510
};

struct cSPMissionManager {
  cSPMission* CreateMissionFromID(u32 id, void* mission, cEmpire* empire,
                                  u32 flags);            // 0x00fec590
};

struct cSpaceGame {
  u8          mPad_00[0x30];             // 0x00
  cStarTable* mpStars_30;                // 0x30
};

struct cSpaceTokenTranslator {
  u8    mPad_00[0xc];                    // 0x00
  void* mpMission_0c;                    // 0x0c
};

struct cGameData {
  u32 GetGameDataOwner();                // Simulator::cGameData::GetGameDataOwner
};

struct cCivData {
  Vec3* GetCities();                     // 0x005c65e0
};

struct cGameNounManager {
  void* GetAvatar();                     // 0x00b1fdb0
  Vec3* GetCities();                     // 0x005c65e0
};

struct cNounBase {                       // `anonymous_namespace'::BioProtectorSort
  cGameNounManager* BioProtectorSort();  // 0x00b8de30 (this = the noun)
};

struct cSPUIEventLog {
  u32 PostFeedbackEvent(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g);
};

struct RandomLinearCongruential {
  u32 RandomUint32Uniform(u32 range);    // 0x00a68fb0
};

// ---------------------------------------------------------------------------
// cSimulatorUniverse
// ---------------------------------------------------------------------------
struct cSimulatorUniverse {
  u8        mPad_00[4];                  // 0x00
  u32       mField_04;                   // 0x04
  u8        mPad_08[0x10];               // 0x08
  EmpireMap mEmpireMap_18;               // 0x18
  u8        mPad_3c[0xbc];               // 0x3c
  u32*      mpShockBegin_f8;             // 0xf8
  u32*      mpShockEnd_fc;               // 0xfc
  u8        mPad_100[0x3c];              // 0x100
  float     mClampLo_13c;                // 0x13c
  float     mClampHi_140;                // 0x140
  u8        mPad_144[8];                 // 0x144
  float     mClampCap_14c;               // 0x14c
  u8        mPad_150[4];                 // 0x150
  float     mPlayerRate_154;             // 0x154
  u32       mAwareness_158;              // 0x158
  u8        mPad_15c[4];                 // 0x15c
  float     mClampLoB_160;               // 0x160
  float     mClampHiB_164;               // 0x164
  u8        mPad_168[8];                 // 0x168
  float     mClampCapB_170;              // 0x170
  u8        mPad_174[4];                 // 0x174
  float     mOtherRate_178;              // 0x178
  FloatMap  mFloatMap_17c;               // 0x17c

  void UpdateEmpires(u64 elapsed);                        // 0x010137b0
  s32  FUN_010107b0(float key);                           // 0x010107b0
  void FUN_01013a70(float key, float scale);              // 0x01013a70
  void UpdateAwareness(u32 elapsedLo, u32 elapsedHi);     // 0x01013ba0
  u32  FUN_01013d20(u32 id);                              // 0x01013d20
  u32  FUN_01014220(cMissionIface* iface, u32 param);     // 0x01014220
  void UpdateEmpireAlliancesAndWars(cEmpire* empire, float dt);
};

struct GrobTeaseRaidEvent {
  u8   mPad_00[8];                       // 0x00
  s32  mTimerLo_08;                      // 0x08
  s32  mTimerHi_0c;                      // 0x0c
  u32  TryCreateMission(cMissionIface* iface, u32 param); // 0x010143d0
};

// ---------------------------------------------------------------------------
// Imported helpers
// ---------------------------------------------------------------------------
void* __cdecl SpaceGameGet();                          // 0x01002bd0
u64   __cdecl GameTimeGet();                           // 0x00b316c0
void* __cdecl RelationshipManager();                   // 0x00b3d2c0
u32   __cdecl GetPlayerEmpireID();                     // 0x01021090
cEmpire* __cdecl GetPlayerEmpire();                    // SP::cSPLivingUniverse
cStarManager* __cdecl StarManager();                   // 0x00b3d2a0
cTerrainEditor* __cdecl NounManager();                 // 0x00b3d300
void* __cdecl GetMissionManager();                     // 0x00feb9f0
void* __cdecl EventLog(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f); // 0x00b3d3e0
MapNode* __cdecl RBTreeIncrement(MapNode* node);       // 0x00921580
void  __cdecl FUN_010129c0(U32Vec* out);               // 0x010129c0
bool  __cdecl FUN_00d01b50(u32 empire, u32 player);    // 0x00d01b50
s32   __cdecl FUN_0100e970(U32Vec* list);              // 0x0100e970
bool  __cdecl FUN_0100fb00(u32 id);                    // 0x0100fb00
void  __cdecl FUN_0100d960();                          // the shock comparator
void* __cdecl FUN_0107bcb0();                          // 0x0107bcb0
u32   __cdecl FUN_00c702f0(u32 planet);                // 0x00c702f0
void  __cdecl FUN_01024df0(u32* first, u32* last, void* cmp);   // 0x01024df0
void  __cdecl FUN_00829110(U32Vec* out, u32* a, u32* b, u32* c, void* d);
void  __cdecl FUN_00b93c60(U32Vec* self, s32 count, void* alloc); // 0x00b93c60
void  __cdecl FUN_00ae6970(void* vec);                 // 0x00ae6970
void  __cdecl FUN_010144c0(void* self, cStarRefVec* refs);       // 0x010144c0
void  __cdecl FUN_01012d70(void* a, void* b, Vec3 pos);          // 0x01012d70
void  __cdecl FUN_00c47180(void* ev);                            // 0x00c47180
void  __cdecl FUN_00aea5d0(void* end, void* value);              // 0x00aea5d0
void  __cdecl FUN_004558a0(U32Vec* self, u32* pos, u32* value);  // SPVector insert

// ===========================================================================
// 0x010137b0  cSimulatorUniverse::UpdateEmpires
// ---------------------------------------------------------------------------
// Walk every empire, refresh its alliance/war state with the elapsed time and
// timestamp it; then sweep the star manager's empire map (at most 100 entries
// per call, wrapping around) and refresh the empires whose stored timestamp
// differs from the current game time.
// ===========================================================================
static MapNode* LowerBoundKey(MapNode* node, MapNode* end, u32 key)
{
  MapNode* best = end;
  while (node != 0) {
    if (node->mKey < key) {
      node = node->mpLeft;
    } else {
      best = node;
      node = node->mpRight;
    }
  }
  return best;
}

// @ 0x010137b0
void cSimulatorUniverse::UpdateEmpires(u64 elapsed)
{
  float dt = (float)elapsed * 0.001f;
  u64 now = GameTimeGet();
  u32 playerEmpire = GetPlayerEmpireID();

  U32Vec empires;
  empires.mpBegin = 0;
  empires.mpEnd = 0;
  empires.mpCap = 0;
  FUN_010129c0(&empires);

  s32 count = (s32)(empires.mpEnd - empires.mpBegin);
  for (s32 i = 0; i < count; i++) {
    cEmpire* empire = (cEmpire*)empires.mpBegin[i];
    UpdateEmpireAlliancesAndWars(empire, dt);
    *mEmpireMap_18.Index(empire->mId_84) = now;
  }

  RelationshipManager();
  cStarManager* stars = StarManager();
  EmpireMap* starMap = (EmpireMap*)stars->FUN_00ba6430();
  if ((*(u32*)0x16dcd50 & 1) == 0) {
    *(u32*)0x16dcd4c = starMap->Begin()->mpEmpire->mId_84;
    *(u32*)0x16dcd50 |= 1;
  }

  s32 processed = 0;
  MapNode* end = starMap->End();
  MapNode* node = LowerBoundKey(starMap->Root(), end, *(u32*)0x16dcd4c);
  if (node == end || *(u32*)0x16dcd4c < node->mKey)
    node = end;

  for (;;) {
    if (node != end) {
      for (;;) {
        if (processed > 99)
          goto done;
        cEmpire* empire = node->mpEmpire;
        if (((empire->mFlags_50 >> 6) & 1) == 0) {
          u32 id = empire->mId_84;
          if (FUN_00d01b50(id, playerEmpire)) {
            MapNode* hit = LowerBoundKey(mEmpireMap_18.Root(), mEmpireMap_18.End(), id);
            if (hit == mEmpireMap_18.End() || hit->mKey != id) {
              u64* slot = mEmpireMap_18.Index(id);
              slot[0] = now;
            } else {
              u64 delta = now - hit->mStamp;
              UpdateEmpireAlliancesAndWars(empire, (float)delta * 0.001f);
              hit->mStamp = now;
            }
          }
        }
        processed++;
        node = RBTreeIncrement(node);
        if (node == starMap->End())
          break;
      }
    }
    node = starMap->Begin();
    *(u32*)0x16dcd4c = node->mpEmpire->mId_84;
    if (processed > 99)
      break;
  }
done:
  if (empires.mpBegin != 0)
    EAFree(empires.mpBegin);
}

// ===========================================================================
// 0x01013a70  cSimulatorUniverse::FUN_01013a70
// ---------------------------------------------------------------------------
// Clamp one empire's influence value in the float map: the value grows by the
// sphere radius times the scale, is floored by the low bound and capped by the
// high one.
// ===========================================================================
// @ 0x01013a70
void cSimulatorUniverse::FUN_01013a70(float key, float scale)
{
  bool isPlayer = key == (float)StarManager()->FUN_00885c90();
  FUN_010107b0(key);

  if (mFloatMap_17c.Find(&key) == mFloatMap_17c.End())
    *mFloatMap_17c.Index(&key) = 0.0f;
  float* slot = mFloatMap_17c.Index(&key);

  float hi, lo, cap;
  if (isPlayer) {
    hi  = mClampHi_140;
    lo  = mClampLo_13c;
    cap = mClampCap_14c;
  } else {
    hi  = mClampHiB_164;
    lo  = mClampLoB_160;
    cap = mClampCapB_170;
  }

  float radius =
      ((cTerrainSphere*)NounManager()->GetCurrentTerrainSphere(0x24446c70))->GetTerrainRadius();
  if (*slot < hi)
    hi = lo;
  float v = *slot + radius * scale;
  if (v <= hi)
    v = hi;
  if (cap <= v)
    v = cap;
  *slot = v;
}

// ===========================================================================
// 0x01013ba0  cSimulatorUniverse::UpdateAwareness
// ---------------------------------------------------------------------------
// Update the player's awareness and, when the terrain sphere allows it, the
// awareness of every other empire in the float map.
// ===========================================================================
// @ 0x01013ba0
void cSimulatorUniverse::UpdateAwareness(u32 elapsedLo, u32 elapsedHi)
{
  u64 elapsed = ((u64)elapsedHi << 32) | elapsedLo;
  float dt = (float)elapsed * 0.001f;

  s32 id = StarManager()->FUN_00885c90();
  u32 playerEmpire = GetPlayerEmpireID();
  float rate = mPlayerRate_154;

  FUN_010107b0((float)id);
  FUN_01013a70((float)id, -(dt * rate));

  s32 state = FUN_010107b0((float)id);
  if (state == 2 || state == 3)
    mAwareness_158 += elapsedLo;
  else
    mAwareness_158 = 0;

  cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere(0x24446c70);
  u8 allow = sphere->FUN_00c77410();

  FloatMap* map = &mFloatMap_17c;
  for (MapNode* node = map->Begin(); node != map->End(); node = RBTreeIncrement(node)) {
    u32 empireId = node->mKey;
    if (empireId == (u32)id || empireId == playerEmpire)
      continue;
    FUN_01013a70((float)empireId, -(mOtherRate_178 * dt));
    if (!allow)
      continue;
    cEmpire* empire = StarManager()->GetEmpireByID(empireId);
    if (empire == 0)
      continue;
    if (empire->FUN_00c31bf0(playerEmpire))
      empire->FUN_00c30bb0();
    if (!empire->FUN_00c30b30())
      continue;
    if (!empire->HasDemandForTributeExpired())
      continue;
    empire->FUN_00c32610();
  }
}

// ===========================================================================
// 0x01013d20  cSimulatorUniverse::FUN_01013d20
// ---------------------------------------------------------------------------
// Find the shock record whose object reports the given id; build the id list of
// that record's elements, ask the record to pick one and release the picked
// objects again.
// ===========================================================================
// @ 0x01013d20
u32 cSimulatorUniverse::FUN_01013d20(u32 id)
{
  u32* rec = mpShockBegin_f8;
  for (; rec != mpShockEnd_fc; rec += 6) {
    cShockObj* obj = (cShockObj*)rec[0];
    if (obj->v0c() != id)
      continue;

    u32* first = (u32*)rec[1];
    u32* last  = (u32*)rec[2];
    s32 n = (s32)(last - first);
    u32* list = 0;
    if (n != 0) {
      list = (u32*)EAAlloc(n * 4, "Simulator", 0, 0,
              "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
              0xd1);
    }
    for (s32 k = 0; k < n; k++)
      list[k] = 0;
    for (s32 k = 0; k < n; k++)
      list[k] = ((cShockObj*)first[k])->v08();

    U32Vec ids;
    ids.mpBegin = list;
    ids.mpEnd = list + n;
    ids.mpCap = list + n;
    s32 pick = FUN_0100e970(&ids);
    u32 result = 0;
    if (pick < n) {
      U32Vec out;
      out.mpBegin = 0;
      out.mpEnd = 0;
      out.mpCap = 0;
      s32 released = obj->v04(first[pick], &out);
      if (released > 0) {
        for (u32* p = out.mpBegin; p < out.mpEnd; p++) {
          if (*p != 0)
            ((cShockObj*)*p)->v04(0, 0);
        }
        if (out.mpBegin != 0)
          EAFree(out.mpBegin);
        result = 1;
      }
      if (out.mpBegin != 0)
        EAFree(out.mpBegin);
    }
    if (list != 0)
      EAFree(list);
    return result;
  }
  return 0;
}

// ===========================================================================
// 0x01013ec0  ShockVec::erase
// ---------------------------------------------------------------------------
// Move the tail down over the erased range and destroy the trailing timers.
// ===========================================================================
tGrobShockData* __cdecl ShockCopy(tGrobShockData* first, tGrobShockData* last,
                                  tGrobShockData* result);   // 0x01010bb0

// @ 0x01013ec0
tGrobShockData* ShockVec::erase(tGrobShockData* first, tGrobShockData* last)
{
  tGrobShockData* newEnd = ShockCopy(last, mpEnd, first);
  tGrobShockData* end = mpEnd;
  for (tGrobShockData* p = newEnd; p < end; p++)
    p->mTimer_08.~cGonzagoTimer();
  mpEnd += last - first;
  return first;
}

// ===========================================================================
// 0x01013f20  ShockVec::DoInsertValue
// ---------------------------------------------------------------------------
// Copy one element into the slot `pos`; grow geometrically (at least one, then
// doubling) when the buffer is full.
// ===========================================================================
void  __cdecl ConstructCopy(tGrobShockData* dst, const tGrobShockData& src); // 0x01010870
void* __cdecl MoveElements(tGrobShockData* first, tGrobShockData* last,
                           tGrobShockData* dst);  // 0x01010b30 / 0x01010e30
void  __cdecl DestroyRange(tGrobShockData* first, tGrobShockData* last); // 0x0100daa0

static void CopyShockFields(tGrobShockData* dst, const tGrobShockData* src)
{
  dst->mId_00 = src->mId_00;
  dst->mField_04 = src->mField_04;
  dst->mTimer_08.mA_08 = src->mTimer_08.mA_08;
  dst->mTimer_08.mB_0c = src->mTimer_08.mB_0c;
  dst->mTimer_08.mC_10 = src->mTimer_08.mC_10;
  dst->mTimer_08.mD_14 = src->mTimer_08.mD_14;
  dst->mTimer_08.mFlag_18 = src->mTimer_08.mFlag_18;
  dst->mTimer_08.mE_1c = src->mTimer_08.mE_1c;
}

// @ 0x01013f20
void ShockVec::DoInsertValue(tGrobShockData* pos, const tGrobShockData& value)
{
  if (mpEnd != mpCap) {
    tGrobShockData* oldEnd = mpEnd;
    mpEnd = mpEnd + 1;
    if (pos == oldEnd) {
      ConstructCopy(oldEnd, value);
    } else {
      ConstructCopy(oldEnd, *(oldEnd - 1));
      MoveElements(pos, oldEnd, oldEnd + 1);
      CopyShockFields(pos, &value);
    }
    return;
  }

  s32 used = (s32)(mpEnd - mpBegin);
  s32 grow;
  tGrobShockData* buffer;
  if (used == 0) {
    grow = 1;
    buffer = (tGrobShockData*)EAAlloc(0x28, "Simulator", 0, 0,
              "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
              0xd1);
  } else {
    grow = used * 2;
    if (grow == 0) {
      buffer = 0;
    } else {
      buffer = (tGrobShockData*)EAAlloc(grow * 0x28, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
    }
  }

  tGrobShockData* mid = (tGrobShockData*)MoveElements(mpBegin, pos, buffer);
  DestroyRange(mpBegin, pos);
  if (mid != 0)
    ConstructCopy(mid, value);
  tGrobShockData* newEnd = (tGrobShockData*)MoveElements(pos, mpEnd, mid + 1);
  DestroyRange(pos, mpEnd);
  if (mpBegin != 0)
    EAFree(mpBegin);
  mpEnd = newEnd;
  mpBegin = buffer;
  mpCap = buffer + grow;
}

// ===========================================================================
// 0x01014090  eastl::quick_sort_impl<tGrobShockData*, ...>
// ---------------------------------------------------------------------------
// A range under 0x1d elements (or an exhausted depth budget) ends the
// recursion; the pivot is the median of begin, begin+n/2 and end-1; the right
// half recurses and the left half is handled by tail iteration.
// ===========================================================================
void __cdecl ShockPartialSort(tGrobShockData* first, tGrobShockData* last,
                              tGrobShockData* dst, ShockCompare cmp);
tGrobShockData* __cdecl ShockPartition(tGrobShockData* begin, tGrobShockData* end,
                                       const tGrobShockData* pivot,
                                       ShockCompare cmp);

// @ 0x01014090
void ShockQuickSort(tGrobShockData* begin, tGrobShockData* end, s32 depth,
                    ShockCompare cmp)
{
  s32 n = (s32)((u8*)end - (u8*)begin);
  for (;;) {
    if (n / 0x28 < 0x1d || depth < 1) {
      if (depth == 0)
        ShockPartialSort(begin, end, end, cmp);
      return;
    }
    tGrobShockData* mid = begin + (n / 0x50);
    const tGrobShockData* pivot;
    if (cmp(*begin, *mid)) {
      pivot = mid;
      if (cmp(*mid, *(end - 1))) {
        pivot = end - 1;
        if (!cmp(*begin, *pivot))
          pivot = begin;
      }
    } else {
      pivot = begin;
      if (!cmp(*begin, *(end - 1))) {
        pivot = end - 1;
        if (!cmp(*mid, *pivot))
          pivot = mid;
      }
    }
    tGrobShockData* split = ShockPartition(begin, end, pivot, cmp);
    depth--;
    ShockQuickSort(split, end, depth, cmp);
    n = (s32)((u8*)split - (u8*)begin);
    end = split;
  }
}

// ===========================================================================
// 0x01014220  cSimulatorUniverse::FUN_01014220
// ---------------------------------------------------------------------------
// Build the candidate star list from the player's star table, sort it, start at
// a random index and take the first star that is not the home planet (or whose
// owner outranks the home planet's owner); hand it to the mission face.
// ===========================================================================
// @ 0x01014220
u32 cSimulatorUniverse::FUN_01014220(cMissionIface* iface, u32 param)
{
  mField_04 = 0;

  cEmpire* player = GetPlayerEmpire();
  u32 homePlanet = player->GetHomePlanet();

  cStarTable* stars = ((cSpaceGame*)SpaceGameGet())->mpStars_30;
  U32Vec tmp;
  tmp.mpBegin = 0;
  tmp.mpEnd = 0;
  tmp.mpCap = 0;
  FUN_00b93c60(&tmp, (s32)(stars->mStars2_2c.mpEnd - stars->mStars2_2c.mpBegin),
               &stars->mStars2_2c.mpAlloc);

  U32Vec merged;
  merged.mpBegin = 0;
  merged.mpEnd = 0;
  merged.mpCap = 0;
  FUN_00829110(&merged, stars->mStars2_2c.mpBegin, stars->mStars2_2c.mpEnd,
               tmp.mpBegin, iface);
  FUN_01024df0(tmp.mpBegin, merged.mpBegin, (void*)FUN_0100d960);

  s32 n = (s32)(merged.mpBegin - tmp.mpBegin);
  s32 start = (s32)((RandomLinearCongruential*)0x1601760)->RandomUint32Uniform(
                        n > 2 ? 3 : n);

  u32 found = 0;
  s32 i = start;
  for (s32 tries = 0; tries < n; tries++) {
    u32 candidate;
    if (tmp.mpBegin[i] == homePlanet) {
      cGameData* gd = (cGameData*)FUN_0107bcb0();
      u32 owner = gd->GetGameDataOwner();
      if (owner <= FUN_00c702f0(homePlanet))
        candidate = tmp.mpBegin[i];
      else
        candidate = 0;
    } else {
      candidate = tmp.mpBegin[i];
    }
    if (candidate != 0) {
      found = candidate;
      break;
    }
    i = (i + 1) % n;
  }

  u32 result = 0;
  if (found != 0 && FUN_0100fb00(found))
    result = iface->v04(found, param);

  for (u32* p = tmp.mpBegin; p < merged.mpBegin; p++) {
    if (*p != 0)
      ((cShockObj*)*p)->v04(0, 0);
  }
  if (tmp.mpBegin != 0)
    EAFree(tmp.mpBegin);
  return result;
}

// ===========================================================================
// 0x010143d0  GrobTeaseRaidEvent::TryCreateMission
// ---------------------------------------------------------------------------
// Reset the cooldown, build and sort the star list and hand one random star out
// of the first three to the mission face.
// ===========================================================================
// @ 0x010143d0
u32 GrobTeaseRaidEvent::TryCreateMission(cMissionIface* iface, u32 param)
{
  mTimerLo_08 = 0;
  mTimerHi_0c = 0;

  cStarTable* stars = ((cSpaceGame*)SpaceGameGet())->mpStars_30;
  U32Vec src;
  src.mpBegin = 0;
  src.mpEnd = 0;
  src.mpCap = 0;
  FUN_00b93c60(&src, (s32)(stars->mStars_18.mpEnd - stars->mStars_18.mpBegin),
               &stars->mStars_18.mpAlloc);

  U32Vec out;
  out.mpBegin = 0;
  out.mpEnd = 0;
  out.mpCap = 0;
  FUN_00829110(&out, stars->mStars_18.mpBegin, stars->mStars_18.mpEnd,
               src.mpBegin, iface);
  FUN_01024df0(src.mpBegin, out.mpBegin, (void*)FUN_0100d960);

  s32 n = (s32)(out.mpBegin - src.mpBegin);
  u32 result = 0;
  if (n != 0) {
    s32 k = n < 3 ? n : 3;
    s32 idx = (s32)((RandomLinearCongruential*)0x1601760)->RandomUint32Uniform(k);
    u32 candidate = src.mpBegin[idx];
    if (candidate != 0 && FUN_0100fb00(candidate))
      result = iface->v04(candidate, param);
  }
  FUN_00ae6970(&out);
  return result;
}

// ===========================================================================
// 0x010144c0  FUN_010144c0
// ---------------------------------------------------------------------------
// Fill the raid's star-reference list from the star table and record the
// mission city into it.
// ===========================================================================
// @ 0x010144c0
void __cdecl FUN_010144c0(void* self, cStarRefVec* refs)
{
  cStarTable* stars = ((cSpaceGame*)SpaceGameGet())->mpStars_30;
  refs->FUN_01011cc0(&stars->mStars2_2c);

  cGameNounManager* nouns = ((cNounBase*)self)->BioProtectorSort();
  Vec3* cities = nouns->GetCities();
  Vec3 pos;
  pos.x = cities->x;
  pos.y = cities->y;
  pos.z = cities->z;
  FUN_01012d70(refs->mpBegin, refs->mpEnd, pos);
}

// ===========================================================================
// 0x01014540  cSimulatorUniverse::CreateNewRaidPlunder
// ---------------------------------------------------------------------------
// Create the plunder mission, fill in its raid counts and push it onto the
// mission's accepted list.
// ===========================================================================
// @ 0x01014540
s32 __cdecl FUN_01014540(void* mission)
{
  cSPMissionManager* managers = (cSPMissionManager*)GetMissionManager();
  if (mission == 0)
    return 0;

  cGameNounManager* nouns = ((cNounBase*)mission)->BioProtectorSort();
  u32 avatar = (u32)nouns->GetAvatar();
  cEmpire* empire = StarManager()->GetEmpireByID(avatar);

  cSPMission* m = managers->CreateMissionFromID(0xc4956aa7, mission, empire, 0);
  if (m == 0)
    return 0;

  cSPRaidEvent* ev = (cSPRaidEvent*)m->v0c(0x397bff2);
  if (ev == 0)
    return 0;

  u32 bomber = (u32)ev->GenerateBomberCount();
  u32 pirate = (u32)ev->GeneratePirateCount();

  cStarRefVec refs;
  refs.mpBegin = 0;
  refs.mpEnd = 0;
  refs.mpCap = 0;
  FUN_010144c0(mission, &refs);

  ((cSpaceTokenTranslator*)*(u32*)0x16e0d08)->mpMission_0c = mission;

  cSPUIEventLog* log = (cSPUIEventLog*)EventLog(0x31df9ac0, 0x131a9f54, 0, 0, 1, 0);
  u32 evt = log->PostFeedbackEvent(0x31df9ac0, 0x131a9f54, 0, 0, 1, 0, 0);

  if (m->mVec_134.mpEnd < m->mVec_134.mpCap) {
    *m->mVec_134.mpEnd++ = evt;
  } else {
    FUN_004558a0(&m->mVec_134, m->mVec_134.mpEnd, &evt);
  }

  FUN_00c47180(ev);
  ev->mMissionID_200 = pirate;
  ev->mElapsedTimeMS_204 = bomber;
  ev->Accept();

  m->v00();
  U32Vec* accepted = (U32Vec*)((u8*)mission + 4);
  if (accepted->mpEnd < accepted->mpCap) {
    *accepted->mpEnd++ = (u32)m;
    m->v00();
  } else {
    FUN_00aea5d0(accepted->mpEnd, &m);
  }
  m->v04();
  FUN_00ae6970(&refs);
  return 1;
}
