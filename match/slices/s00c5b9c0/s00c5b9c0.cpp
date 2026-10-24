// Slice s00c5b9c0 - Simulator raid/plunder mission events.
//   SP::cSPRaidEvent::OnComplete / OnFail / OnAccept, the cRaidEvent and
//   cRaidPlunderEvent constructors/destructors and the 0x20-byte mission
//   element vector helpers used by the "place turret" sim tasks.
// Reconstructed from annotated disassembly + Ghidra decompiles.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned int       u32;
typedef unsigned short     u16;
typedef unsigned char      u8;
typedef          int       s32;
typedef          short     s16;
typedef unsigned long long u64;

struct Vec3 {
  float x, y, z;
  Vec3& operator=(const Vec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

// ---------------------------------------------------------------------------
// 0x20-byte element of the mission-element vector (vtable 0x0146f688).
// ---------------------------------------------------------------------------
struct MissionElem {
  u32   vtbl;      // 0x00
  s32   id;        // 0x04
  Vec3  pos;       // 0x08
  float f14;       // 0x14
  float f18;       // 0x18
  s32   i1c;       // 0x1c
};

struct MissionElem;
struct ElemVec {
  MissionElem* begin;   // 0x00
  MissionElem* end;     // 0x04
  MissionElem* cap;     // 0x08

  void Insert(MissionElem* pos, MissionElem* val);   // 0x00c5bf80
  void PushDefault();                                // 0x00c5c240
};

MissionElem* __cdecl CopyMissionElementsForward(MissionElem* first, MissionElem* last,
                                                MissionElem* dst);       // 0x00c5b450
MissionElem* __cdecl CopyMissionElementsBackward(MissionElem* first, MissionElem* last,
                                                 MissionElem* dst);      // 0x00c5b4b0
MissionElem* __cdecl FUN_00c5bbc0(MissionElem* first, MissionElem* last, MissionElem* dst);

void* __cdecl operator_new(u32 size, const char* name, s32 a, s32 b,
                           const char* file, s32 line);                  // 0x00f473a0
void  __cdecl operator_delete_array(void* p);                            // 0x00f47380

// ---------------------------------------------------------------------------
// Small helpers / external types.
// ---------------------------------------------------------------------------
struct IRef {
  virtual void v0();
  virtual void Release();          // vtable slot 4
};

struct MissionObjVt {              // property bag stored at cSPMission+0x180
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void v08();
  virtual u8   GetProperty(u32 id, void** out);    // vtable slot 0x24
};

struct Property {
  float* GetFloat();                               // 0x0041ea70
};

struct cEntity {
  u32 pad000[0x21];
  u32 empireID;                    // 0x084
};

// list owner reached through cPlanet+0x13c
struct cPlaceList {
  u32 pad000[0x4d];                // 0x000
  u32 pl134Begin;                  // 0x134
  u32 pl134End;                    // 0x138
  u32 pl134Cap;                    // 0x13c
  Vec3*       GetCitiesPos();      // 0x005c65e0 (no arg form)
  void*       GetCitiesRef(void* ref); // 0x005c65e0 (query form)
  void*       FUN_00b8de30();      // 0x00b8de30
  u8          FUN_00b8e040(u32);   // 0x00b8e040
  void*       GetCommContext(void*);// 0x00ce6950
};

struct cPlanet {
  u32 pad000[0x4f];                // 0x000
  cPlaceList* p13c;                // 0x13c
  cEntity*    FUN_00c71e30();      // 0x00c71e30
};

struct cCivObject {                // cEmpire / cCivData shared surface
  u32  pad000[0x1b];
  u32  f06c;                       // 0x06c
  u32  f070;                       // 0x070
  void*  FUN_00c30c80();           // 0x00c30c80
  void*  FUN_00c30c60();           // 0x00c30c60
  Vec3*  GetCitiesPos();           // 0x005c65e0 (no arg form)
  void*  GetCitiesRef(void* ref);  // 0x005c65e0 (query form)
  Vec3*  GetUFOKey();              // 0x00c326b0
  u8     FUN_00c31bc0(void*);      // 0x00c31bc0
  void*  FUN_00b8de30();           // 0x00b8de30
  void*  FUN_00bb0e90(void*);      // 0x00bb0e90
};

struct cGameData2 {
  void FUN_00fe5430();             // 0x00fe5430
};
struct cSpaceGame {
  cGameData2* SetGameDataOwner2(); // 0x00fe53b0
};

struct cRelMgr {
  void RecordEvent(u32 a, u32 b, u32 ev, float v);   // 0x00d06240
  u8   FUN_00d01fb0(u32 a, u32 b);                   // 0x00d01fb0
  u8   FUN_00d01ff0(void* a, u32 b);                 // 0x00d01ff0
};

struct cStarMgr {
  cCivObject* GetEmpireByID(u32 id);                 // 0x00ba9370
  void*       FUN_00bb0e90(void* q);                 // 0x00bb0e90
};

struct cEventLog {
  void* PostFeedbackEvent(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f); // 0x00dd8640
  void  ModifyEventText(void* ev, void* text);                       // 0x00dd6df0
  void  EventDoNotAddToHistory(void* ev, u32 flag);                  // 0x00dd67d0
};

struct cCommMgr {
  void* FUN_00aeb3e0(u32 a, void* b);                // 0x00aeb3e0
};

struct cSpaceCombatTuning {
  s32   GetWeaponLevel(Vec3 v);                      // 0x0102a360
  float GetBackgroundUberTurretDPS();                // 0x01029e70
  float GetUFOHealth(s32 a, s32 b);                  // 0x0102a630
};

struct cNounMgr {
  void* GetCurrentTerrainSphere();                   // 0x00f67d90
  void* GetAvatar();                                 // 0x00b1fdb0
  void  FUN_00bb9b00(s32 a, s32 b);                  // 0x00bb9b00
};

struct cMsgServerVt {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void Notify(void* sub, void* tag);         // vtable slot 0x20
};

struct cMissionVt {                                  // primary vtable of cSPMission
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
  virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
  virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
  virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
  virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
  virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
  virtual void v40();
  virtual void* GetCommContext(u32 tag, s32 mode, void* self, s32 flag); // 0xa4
};

// Float defaults used by the mission-element / event initialisers.  Declared as
// extern objects (not absolute-address casts) so MSVC 2008 picks the SSE moves.
extern "C" {
  extern float g_elemPosX;      // 0x01691fc8
  extern float g_elemPosY;      // 0x01691fcc
  extern float g_elemPosZ;      // 0x01691fd0
  extern float g_elemNegOne;    // 0x013eb1bc
}

u32   __cdecl GetPlayerEmpireID();                   // 0x01021090
void* __cdecl GetUniverseContext();                  // 0x01021080
void* __cdecl GetActivePlanet();                     // 0x01021260
void* __cdecl GetPlayerEmpire();                     // 0x01021300
void  __cdecl ReleaseCreaturePosse(void* p);         // 0x0102c0c0
void  __cdecl GetPropertyT(void* obj, u32 id, void* out); // 0x0040cf10
cSpaceGame* __stdcall SpaceGameGet(s32 a, s32 b);    // 0x01002bd0
cRelMgr* __cdecl RelationshipManager();              // 0x00b3d2c0
cStarMgr* __cdecl StarManager();                     // 0x00b3d2a0
cEventLog* __cdecl EventLog();                       // 0x00b3d3e0
cCommMgr* __cdecl CommManager();                     // 0x00b3d4a0
cNounMgr* __cdecl NounManager();                     // 0x00b3d300
cSpaceCombatTuning* __cdecl GetSpaceCombatTuning();  // 0x01029940
void* __cdecl MessageServer();                       // 0x0067dcc0
void* __cdecl FUN_00401010();                        // 0x00401010
void* __cdecl FUN_00fe3b10(cPlanet* p);              // 0x00fe3b10
Vec3* __cdecl FUN_00c75770();                        // 0x00c75770
s32   __cdecl FUN_00c70420(void* p);                 // 0x00c70420
void  __cdecl WStr_Format(void* out, const u16* fmt, u32 v); // 0x0041e050
float __cdecl RandomDoubleUniform();                 // 0x009360d0

struct SPVecU32 {
  u32* begin; u32* end; u32* cap;
  void DoInsertValue(u32* pos, const u32* val);      // 0x004558a0
};

// ---------------------------------------------------------------------------
// SP::cSPMission / event classes.
// ---------------------------------------------------------------------------
struct cSPMission {
  u32   vtbl000;                   // 0x000
  u32   vtbl004;                   // 0x004
  u32   pad008[11];                // 0x008
  u32   vtbl034;                   // 0x034
  u32   pad038[23];                // 0x038
  u32   targetEmpireID;            // 0x094
  u32   pad098[39];                // 0x098
  SPVecU32 ev134;                  // 0x134
  u32   pad140[16];                // 0x140
  void* p180;                      // 0x180
  u32   pad184[24];                // 0x184
  void* p1e4;                      // 0x1e4
  u32   pad1e8[2];                 // 0x1e8

  void  InitGeneric();             // 0x00c48e90
  void  Destroy();                 // 0x00c47680
  void* GetTargetPlanet();         // 0x00970b30
  u32   GetMissionID();            // 0x01030e10
  void  GetText(u32 tag, void* out);            // 0x00c487d0
  u8    GetTagString(u32 tag, void* out);       // 0x00c491c0
  void  OnAcceptBase();                         // 0x00c47a10
  void  HandlerComplete();                      // 0x00c46b80
  void  HandlerFail();                          // 0x00c469f0
};

struct cRaidPlunderEvent : cSPMission {
  u32   f1f0, f1f4, f1f8;
  u8    b1fc; u8 pad1fd[3];
  u32   f200, f204, f208;
  float f20c, f210;
  u32   f214, f218, f21c;
};

struct cRaidEvent : cSPMission {
  void* p1f0;
  u32   f1f4, f1f8, f1fc, f200, f204, f208;
  float f20c, f210;
  u8    b214, b215;
  u16   pad216;
  u32   f218;
  u8    b21c, b21d, b21e; u8 pad21f;
  u32   f220;
  Vec3  v224;
  u32   f230;
  u8    b234; u8 pad235[3];
  u32   f238, f23c, f240;
};

// 0x1c-byte star/city query descriptor used by OnAccept.
struct cStarRef {
  u32   flags;      // 0x00
  s32   mode;       // 0x04
  u32   f08;        // 0x08
  float f0c;        // 0x0c
  float f10;        // 0x10
  u32   f14;        // 0x14
  float f18;        // 0x18
};

// small string header handed to GetText (begin/end/capacity).
struct WStr {
  u16* begin; u16* end; u16* cap;
};

// ===========================================================================
// 0x00c5b9c0 - SP::cSPRaidEvent::OnComplete
// ===========================================================================
// @ 0x00c5b9c0
void __fastcall FUN_00c5b9c0(cRaidEvent* self, void* dummy)
{
  (void)dummy;
  float val;
  void* prop;

  if (self->b21c != 0) goto done;
  if (self->p180 == 0) goto done;
  val = 0.0f;
  prop = 0;
  if (((MissionObjVt*)self->p180)->GetProperty(0x39787b3, &prop) != 0 &&
      *(u16*)((char*)prop + 0x12) == 0xd) {
    val = *((Property*)prop)->GetFloat();
  }
  {
    cPlanet* planet = (cPlanet*)self->GetTargetPlanet();
    if (planet != 0) {
      cEntity* ent = planet->FUN_00c71e30();
      if (ent == 0) goto done;
      {
        u32 other = ent->empireID;
        u32 me = GetPlayerEmpireID();
        if (other != me) {
          RelationshipManager()->RecordEvent(other, me, 0x526e519, val);
          if (RelationshipManager()->FUN_00d01fb0(other, me) == 0)
            goto done;
        }
        SpaceGameGet(0x12, 1)->SetGameDataOwner2()->FUN_00fe5430();
      }
    }
  }
done:
  ReleaseCreaturePosse(self->GetTargetPlanet());
  self->HandlerComplete();
}

// ===========================================================================
// 0x00c5bab0 - SP::cSPRaidEvent::OnFail
// ===========================================================================
// @ 0x00c5bab0
void __fastcall FUN_00c5bab0(cRaidEvent* self, void* dummy)
{
  (void)dummy;
  ReleaseCreaturePosse(self->GetTargetPlanet());
  if (GetUniverseContext() == 0) {
    if (self->GetTargetPlanet() == GetActivePlanet()) {
      self->HandlerComplete();
      return;
    }
  }
  if (self->p180 != 0) {
    u32 other = self->targetEmpireID;
    if (other != GetPlayerEmpireID()) {
      cCivObject* emp = StarManager()->GetEmpireByID(other);
      if (emp != 0) {
        if (RelationshipManager()->FUN_00d01ff0(emp, 0) != 0) {
          float f = 0.0f;
          GetPropertyT(self->p180, 0x39787ae, &f);
          float v = (float)(f < 0.0f ? -f : f);
          RelationshipManager()->RecordEvent(other, GetPlayerEmpireID(), 0x526e51c, v);
        }
      }
    }
  }
  self->HandlerFail();
}

// ===========================================================================
// 0x00c5bbc0 - copy a range of MissionElement, forcing the vtable on dst
// ===========================================================================
// @ 0x00c5bbc0
MissionElem* __cdecl FUN_00c5bbc0(MissionElem* first, MissionElem* last, MissionElem* dst)
{
  if (first != last) {
    do {
      if (dst != 0) {
        dst->vtbl = 0x0146f688;
        dst->id    = first->id;
        dst->pos   = first->pos;
        dst->f14   = first->f14;
        dst->f18   = first->f18;
        dst->i1c   = first->i1c;
      }
      first++;
      dst++;
    } while (first != last);
  }
  return dst;
}

// ===========================================================================
// 0x00c5bc30 - Simulator::cRaidPlunderEvent::cRaidPlunderEvent
// ===========================================================================
// @ 0x00c5bc30
cRaidPlunderEvent* __fastcall FUN_00c5bc30(cRaidPlunderEvent* self, void* dummy)
{
  (void)dummy;
  self->InitGeneric();
  self->vtbl000 = 0x0146f6b0;
  self->vtbl004 = 0x0146f6a0;
  self->vtbl034 = 0x0146f690;
  self->f1f0 = 0;
  self->f1f4 = 0;
  self->f1f8 = 0;
  self->b1fc = 0;
  self->f200 = 0;
  self->f204 = 0;
  self->f208 = 0;
  self->f20c = 0.0f;
  self->f210 = 0.0f;
  self->f214 = 0;
  self->f218 = 0;
  self->f21c = 0;
  return self;
}

// ===========================================================================
// 0x00c5bd00 - cRaidPlunderEvent scalar deleting destructor
// ===========================================================================
// @ 0x00c5bd00
void* __fastcall FUN_00c5bd00(cRaidPlunderEvent* self, void* dummy, u32 flags)
{
  (void)dummy;
  if (self->f214 != 0 && ((u32*)self->f214)[-1] != 0)
    operator_delete_array((void*)self->f214);
  self->Destroy();
  if ((flags & 1) != 0)
    operator_delete_array(self);
  return self;
}

// ===========================================================================
// 0x00c5bd40 - Simulator::cRaidEvent::cRaidEvent
// ===========================================================================
// @ 0x00c5bd40
cRaidEvent* __fastcall FUN_00c5bd40(cRaidEvent* self, void* dummy)
{
  (void)dummy;
  self->InitGeneric();
  self->vtbl000 = 0x0146f898;
  self->vtbl004 = 0x0146f888;
  self->vtbl034 = 0x0146f878;
  self->p1f0 = 0;
  self->f1f4 = 0;
  self->f1f8 = 0;
  self->f1fc = 0;
  self->f200 = 0;
  self->f204 = 0;
  self->f208 = 0;
  self->f20c = 0.0f;
  self->f210 = 0.0f;
  self->b214 = 0;
  self->f218 = 0;
  self->b21c = 0;
  self->b21d = 0;
  self->f220 = 0;
  {
    void* sub = &self->vtbl034;
    self->b215 = self->b21e = 1;
    self->v224.x = g_elemPosX;
    self->v224.y = g_elemPosY;
    self->v224.z = g_elemPosZ;
    self->f230 = 0xffffffff;
    self->b234 = 0;
    self->f238 = 0;
    self->f23c = 0;
    self->f240 = 0;
    ((cMsgServerVt*)MessageServer())->Notify(sub, (void*)0x01622184);
  }
  return self;
}

// ===========================================================================
// 0x00c5bea0 - cRaidEvent scalar deleting destructor
// ===========================================================================
// @ 0x00c5bea0
void* __fastcall FUN_00c5bea0(cRaidEvent* self, void* dummy, u32 flags)
{
  (void)dummy;
  if (self->f238 != 0 && ((u32*)self->f238)[-1] != 0)
    operator_delete_array((void*)self->f238);
  {
    IRef* ref = (IRef*)self->p1f0;
    if (ref != 0)
      ref->Release();
  }
  self->Destroy();
  if ((flags & 1) != 0)
    operator_delete_array(self);
  return self;
}

// ===========================================================================
// 0x00c5bf80 - insert one MissionElement at the given position
// ===========================================================================
// @ 0x00c5bf80
void __fastcall FUN_00c5bf80(ElemVec* vec, void* dummy, MissionElem* pos, MissionElem* val)
{
  (void)dummy;
  MissionElem* p = vec->end;

  if (p != vec->cap) {
    if (val >= pos && val < p)
      val++;
    if (p != 0) {
      p->vtbl  = 0x0146f688;
      p->id    = p[-1].id;
      p->pos.x = p[-1].pos.x;
      p->pos.y = p[-1].pos.y;
      p->pos.z = p[-1].pos.z;
      p->f14   = p[-1].f14;
      p->f18   = p[-1].f18;
      p->i1c   = p[-1].i1c;
    }
    CopyMissionElementsBackward(pos, p - 1, p);
    pos->id    = val->id;
    pos->pos.x = val->pos.x;
    pos->pos.y = val->pos.y;
    pos->pos.z = val->pos.z;
    pos->f14   = val->f14;
    pos->f18   = val->f18;
    pos->i1c   = val->i1c;
    ++vec->end;
    return;
  }

  {
    s32 n = (s32)(vec->end - vec->begin);
    s32 cap = n ? n * 2 : 1;
    MissionElem* buf;
    MissionElem* mid;

    if (cap != 0)
      buf = (MissionElem*)operator_new((u32)(cap * 0x20), "Simulator", 0, 0,
                                       (const char*)0x013ebb38, 0xd1);
    else
      buf = 0;

    mid = FUN_00c5bbc0(vec->begin, pos, buf);
    if (mid != 0) {
      mid->vtbl  = 0x0146f688;
      mid->id    = val->id;
      mid->pos.x = val->pos.x;
      mid->pos.y = val->pos.y;
      mid->pos.z = val->pos.z;
      mid->f14   = val->f14;
      mid->f18   = val->f18;
      mid->i1c   = val->i1c;
    }
    vec->end = FUN_00c5bbc0(pos, vec->end, mid + 1);
    if (vec->begin != 0 && ((u32*)vec->begin)[-1] != 0)
      operator_delete_array(vec->begin);
    vec->cap = buf + cap;
    vec->begin = buf;
  }
}

// ===========================================================================
// 0x00c5c0f0 - grow/shrink the turret element list against a health budget
// ===========================================================================
// @ 0x00c5c0f0
void __cdecl FUN_00c5c0f0(ElemVec* vec, cPlanet* planet, s32* count,
                           u32 unused, float* out, s32 n)
{
  (void)unused;
  if (FUN_00fe3b10(planet) != 0)
    return;

  {
    cPlaceList* pl = planet->p13c;
    cPlaceList* city = (cPlaceList*)pl->FUN_00b8de30();
    if (pl == 0)
      return;
    if (pl->FUN_00b8e040(*(u32*)0x016922ac) == 0)
      return;

    {
      cSpaceCombatTuning* tun = GetSpaceCombatTuning();
      Vec3* cityPos = city->GetCitiesPos();
      s32 level = tun->GetWeaponLevel(*cityPos);
      float dps = tun->GetBackgroundUberTurretDPS();
      float hp  = tun->GetUFOHealth(5, level);
      float total = (float)n;
      MissionElem* it;
      float remain;

      if (n < 0)
        total += 4294967296.0f;
      total = total * 0.001f * dps + *out;
      *out = 0.0f;

      for (it = vec->begin; it != vec->end && it->id != 5; ++it)
        ;
      remain = total;
      while (*count > 0 && hp <= remain && it != vec->end) {
        if (it->id == 5) {
          if (it + 1 < vec->end)
            CopyMissionElementsForward(it + 1, vec->end, it);
          vec->end -= 1;
          *count -= 1;
          remain -= hp;
        }
      }
      *out = remain;
    }
  }
}

// ===========================================================================
// 0x00c5c240 - push_back a default MissionElement
// ===========================================================================
// @ 0x00c5c240
void __fastcall FUN_00c5c240(ElemVec* vec, void* dummy)
{
  (void)dummy;
  MissionElem* e = vec->end;

  if (e < vec->cap) {
    vec->end = e + 1;
    if (e != 0) {
      e->vtbl  = 0x0146f688;
      e->id    = -1;
      e->pos.x = g_elemPosX;
      e->pos.y = g_elemPosY;
      e->pos.z = g_elemPosZ;
      {
        float n = g_elemNegOne;
        e->f14 = n;
        e->f18 = n;
      }
      e->i1c   = -1;
    }
    return;
  }

  {
    MissionElem tmp;
    tmp.vtbl  = 0x0146f688;
    tmp.id    = -1;
    tmp.pos.x = g_elemPosX;
    tmp.pos.y = g_elemPosY;
    tmp.pos.z = g_elemPosZ;
    {
      float n = g_elemNegOne;
      tmp.f14 = n;
      tmp.f18 = n;
    }
    tmp.i1c   = -1;
    vec->Insert(e, &tmp);
  }
}

// ===========================================================================
// 0x00c5c310 - populate the element list with 4/5/2-type entries
// ===========================================================================
// @ 0x00c5c310
void __cdecl FUN_00c5c310(ElemVec* vec, s32* p2, s32* p3, s32* p4, s32 lo, s32 hi)
{
  if (*p2 != 0 || *p4 != 0) {
    *p3 = 0;

    {
      s32 i;
      for (i = 0; i < *p2; ++i) {
        vec->PushDefault();
        vec->end[-1].id = i + 4;
      }
    }

    {
      s32 i;
      for (i = 0; i < *p2; ++i) {
        float fbuf[1];
        fbuf[0] = RandomDoubleUniform() * (float)(hi - lo) + (float)lo;
        s32 n = (s32)fbuf[0];
        if (n > 5)
          n = 5;
        if (n > 0) {
          s32 k = n;
          do {
            vec->PushDefault();
            MissionElem* e = vec->end - 1;
            e->id  = 2;
            e->i1c = i;
          } while (--k != 0);
        }
        *p3 += n;
      }
    }

    {
      s32 i;
      for (i = 0; i < *p4; ++i) {
        vec->PushDefault();
        vec->end[-1].id = 5;
      }
    }
  }
}

// ===========================================================================
// 0x00c5c410 - tag string / "place turret" mission text
// ===========================================================================
// @ 0x00c5c410
u8 __fastcall FUN_00c5c410(cRaidEvent* self, void* dummy, u32 tag, void* out)
{
  (void)dummy;
  if (tag == 0x21eb4188) {
    if (self->f230 != 0xffffffff) {
      cCivObject* emp = StarManager()->GetEmpireByID(self->f230);
      if (emp != 0) {
        emp->FUN_00c30c80();
        WStr_Format(out, (const u16*)0x013f5c04, *(u32*)emp->GetCitiesPos());
      }
    }
    return 1;
  }
  return self->GetTagString(tag, out);
}

// ===========================================================================
// 0x00c5c470 - SP::cSPRaidEvent::OnAccept
// ===========================================================================
// @ 0x00c5c470
void __fastcall FUN_00c5c470(cRaidEvent* self, void* dummy)
{
  (void)dummy;
  self->OnAcceptBase();

  if (self->b21e != 0 && self->GetMissionID() != 0xbbae6b99) {
    cPlanet* planet = (cPlanet*)self->GetTargetPlanet();
    *(void**)(*(u32*)0x016e0d08 + 0xc) = planet->p13c;

    {
      WStr text;
      text.begin = text.end = (u16*)0x01667bac;
      text.cap = (u16*)0x01667bae;
      self->GetText(0xa3139d, &text);

      {
        u32 ev = (u32)EventLog()->PostFeedbackEvent(0x6c0fa994, 0x131a9f54, 0, 0, 1, 0);
        EventLog()->ModifyEventText((void*)ev, text.begin);
        EventLog()->EventDoNotAddToHistory((void*)ev, 1);
        if (self->ev134.end < self->ev134.cap) {
          u32* p = self->ev134.end;
          self->ev134.end = p + 1;
          if (p != 0)
            *p = ev;
        } else {
          self->ev134.DoInsertValue(self->ev134.end, &ev);
        }
      }

      if ((((u32)text.cap - (u32)text.begin) & 0xfffffffeu) > 2 && text.begin != 0)
        operator_delete_array(text.begin);
    }

    {
      cPlanet* p = (cPlanet*)self->GetTargetPlanet();
      if (p != 0) {
        cEntity* ent = ((cPlanet*)self->GetTargetPlanet())->FUN_00c71e30();
        void* me = GetPlayerEmpire();
        if (ent != 0 && (ent == (cEntity*)me ||
                         ((cCivObject*)ent)->FUN_00c31bc0(me) != 0)) {
          cPlaceList* pl1 = ((cPlanet*)self->GetTargetPlanet())->p13c;
          cPlaceList* pl2 = ((cPlanet*)self->GetTargetPlanet())->p13c;
          u32 flag = (ent == (cEntity*)me);
          u32 empID = ent->empireID;

          {
            void* ctx = ((cMissionVt*)self->vtbl000)->GetCommContext(0x8b756f4b, 2, self, (s32)flag);
            void* comm = pl2->FUN_00b8de30();
            void* res = CommManager()->FUN_00aeb3e0(empID,
                          (void*)((cPlaceList*)pl1)->GetCommContext(ctx));
            void* old = self->p1e4;
            (void)comm;
            if (res != old) {
              if (res != 0)
                (*(void(__thiscall**)(void*))*(void**)res)(res);
              self->p1e4 = res;
              if (old != 0)
                ((IRef*)old)->Release();
            }
          }
        }
      }
    }

    {
      cPlaceList* pl = ((cPlanet*)self->GetTargetPlanet())->p13c;
      s32 n = (s32)((pl->pl134End - pl->pl134Begin) / 0x2c);
      s32 cnt = 0;
      if (n > 0) {
        u32* e = (u32*)pl->pl134Begin;
        s32 k = n;
        do {
          if (((u8*)e)[0x28] & 1) {
            if (*e != *(u32*)0x016922ac)
              cnt++;
          }
          e += 0xb;
        } while (--k != 0);
      }
      {
        float ratio = (float)cnt / (float)(FUN_00c70420(pl) + cnt);
        if (ratio >= RandomDoubleUniform())
          self->b214 = 1;
      }
    }
  }

  self->b21d = 1;

  {
    cPlaceList* pl = ((cPlanet*)self->GetTargetPlanet())->p13c;
    void* mgr = pl->FUN_00b8de30();
    cCivObject* emp;

    ((cNounMgr*)mgr)->FUN_00bb9b00(0x200, 1);
    self->targetEmpireID = (u32)((cNounMgr*)mgr)->GetAvatar();
    emp = StarManager()->GetEmpireByID(self->f230);

    if (emp != 0) {
      Vec3* c = emp->GetUFOKey();
      self->v224 = *c;
    } else {
      cNounMgr* nm = NounManager();
      Vec3* c = (Vec3*)nm->GetCurrentTerrainSphere();
      self->v224 = *(Vec3*)((u32*)c ? FUN_00c75770() : 0);
    }

    {
      void* obj = FUN_00401010();
      u8 ok = (*(u8(__thiscall**)(void*, Vec3*, s32))*(void**)(*(u32*)obj + 0x1c))(obj, &self->v224, 0);
      if (ok == 0) {
        cStarRef ref;
        obj = FUN_00401010();
        ref.flags = 0x1ff1;
        ref.mode  = 0x1e;
        ref.f08   = 0;
        ref.f0c   = 0.0f;
        ref.f10   = *(float*)0x013eecd8;
        ref.f14   = 0;
        ref.f18   = -1.0f;
        (*(void(__thiscall**)(void*, Vec3*, cStarRef*))*(void**)(*(u32*)obj + 0x4c))(obj, &self->v224, &ref);
      }
    }

    if (emp != 0) {
      cCivObject* c = (cCivObject*)emp->FUN_00c30c60();
      self->f1f4 = c->f070;
    } else {
      cNounMgr* nm2 = NounManager();
      (void)nm2;
      {
        cPlaceList* plx = ((cPlanet*)self->GetTargetPlanet())->p13c;
        cStarRef ref;
        ref.flags = 0x1ff1;
        ref.mode  = 0x1e;
        ref.f08   = 0;
        ref.f0c   = 0.0f;
        ref.f10   = *(float*)0x013eecd8;
        ref.f14   = 0;
        ref.f18   = -1.0f;
        void* r = StarManager()->FUN_00bb0e90(plx->GetCitiesRef(&ref));
        if (r == 0) {
          ref.flags |= 0x20;
          r = StarManager()->FUN_00bb0e90(plx->GetCitiesRef(&ref));
        }
        self->f1f4 = *(u32*)((char*)r + 0x70);
      }
    }
  }
}
