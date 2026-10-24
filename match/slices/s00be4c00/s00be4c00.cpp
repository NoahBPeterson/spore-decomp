// Slice s00be4c00 - cRaidBehavior (space-stage raid event behaviour): teardown,
// tag dispatch, agent/target handling, the "move to circle" helpers and the
// load/save routine.
// Reconstructed from annotated disassembly + Ghidra decompiles.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned int       u32;
typedef unsigned short     u16;
typedef unsigned char      u8;
typedef          int       s32;

// Float constants read with `fld dword ptr [addr]`.
extern "C" float g_float20;   // 0x01468460 == 20.0f
extern "C" float g_float4;    // 0x01468468 ==  4.0f

struct Vec3 { float x, y, z; };

struct Vec3Span {             // begin/end of a contiguous Vec3 array
  Vec3* begin;                // 0x00
  Vec3* end;                  // 0x04
};

// ---------------------------------------------------------------------------
// Sub-object embedded at noun+0x34; only vtable slot 0x38 is ever called.
// ---------------------------------------------------------------------------
struct cSub34 {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
  virtual void v30(); virtual void v34();
  virtual void v38(void* arg);        // slot 0x38
};

// Combat surface embedded at noun+0x120; only the +0x34 getter is used.
struct cCombatant {
  u32 pad00[13];                      // 0x00 .. 0x33
  u32 GetDamageState();               // 0x008e7f80, returns *(this+0x34)
};

// ---------------------------------------------------------------------------
// Generic game noun: vtable slots 0x00..0xc0, +0x34 sub-object, +0x120 combat.
// ---------------------------------------------------------------------------
struct cNoun {
  virtual void  v00();                // 0x00
  virtual void  v04();                // 0x04
  virtual void  v08();                // 0x08
  virtual void* v0c(u32 tag);         // 0x0c
  virtual void  v10();                // 0x10
  virtual void  v14();                // 0x14
  virtual void  v18();                // 0x18
  virtual void  v1c();                // 0x1c
  virtual void* v20();                // 0x20
  virtual void  v24();                // 0x24
  virtual void  v28();                // 0x28
  virtual void  v2c();                // 0x2c
  virtual void  v30();                // 0x30
  virtual void  v34();                // 0x34
  virtual void  v38();                // 0x38
  virtual void  v3c();                // 0x3c
  virtual void  v40();                // 0x40
  virtual void  v44();                // 0x44
  virtual void  v48();                // 0x48
  virtual void* v4c();                // 0x4c
  virtual void  v50();                // 0x50
  virtual void  v54(void* p);         // 0x54
  virtual void  v58();                // 0x58
  virtual void  v5c(u32 tag);         // 0x5c
  virtual void  v60();                // 0x60
  virtual void  v64();                // 0x64
  virtual void  v68();                // 0x68
  virtual void  v6c();                // 0x6c
  virtual void  v70();                // 0x70
  virtual void  v74();                // 0x74
  virtual void  v78();                // 0x78
  virtual void  v7c();                // 0x7c
  virtual void  v80();                // 0x80
  virtual void  v84();                // 0x84
  virtual void  v88();                // 0x88
  virtual void  v8c();                // 0x8c
  virtual void  v90();                // 0x90
  virtual void  v94();                // 0x94
  virtual void  v98();                // 0x98
  virtual void  v9c();                // 0x9c
  virtual void  va0();                // 0xa0
  virtual void  va4();                // 0xa4
  virtual void  va8();                // 0xa8
  virtual void  vac();                // 0xac
  virtual void  vb0();                // 0xb0
  virtual void  vb4();                // 0xb4
  virtual void  vb8();                // 0xb8
  virtual void  vbc();                // 0xbc
  virtual void  vc0();                // 0xc0

  u32          pad04[12];             // 0x04 .. 0x33
  cSub34       sub34;                 // 0x34
  u32          pad38[58];             // 0x38 .. 0x11f
  cCombatant   combat;                // 0x120
};

struct cGameNounManager {
  cNoun* CreateNoun(u32 type);        // 0x00b20c60
  void   RemoveNoun(void* n);         // 0x00b225d0
};

cGameNounManager* __cdecl NounManager();          // 0x00b3d300

// ---------------------------------------------------------------------------
// The planet / "living universe" view object stored at self+0x120.
// ---------------------------------------------------------------------------
struct cObj120 {
  virtual void  v00(); virtual void  v04(); virtual void  v08(); virtual void  v0c();
  virtual void  v10(); virtual void  v14(); virtual void  v18(); virtual void  v1c();
  virtual void  v20(); virtual void  v24(); virtual void  v28();
  virtual void* v2c();                // 0x2c
  virtual void  v30(); virtual void  v34(); virtual void  v38(); virtual void  v3c();
  virtual void  v40(); virtual void  v44(); virtual void  v48(); virtual void  v4c();
  virtual void  v50(); virtual void  v54(); virtual void  v58();
  virtual void* v5c(Vec3* out);       // 0x5c
  void FUN_00c88b00(void* stream);    // 0x00c88b00
};

// ---------------------------------------------------------------------------
// tSlot reachable through self+0x43c (inside circle3ec).
// ---------------------------------------------------------------------------
struct tSlot43c {
  u32 f00;                            // 0x00
  u32 f04;                            // 0x04
  u32 f08;                            // 0x08
  u32 f0c;                            // 0x0c
  void Reserve(void* data);           // 0x00afa030
};

// ---------------------------------------------------------------------------
// cActionCircle: agent ring used by the movement helpers (0x64 bytes).
// ---------------------------------------------------------------------------
struct cActionCircle {
  void RemoveAgent(void* agent);                                     // 0x00afae50
  u32  CountFreeSlots();                                             // 0x00af9f60
  void SetAtCenter(void* center, float radius, void* facing,
                   float altitude);                                  // 0x00af9cf0
  void EmitCopy(void* span, float f);                                // 0x00afec00
  void FUN_00afaec0();                                               // 0x00afaec0
  u8        pad00[0x50];
  tSlot43c* slot;                                                    // 0x50
  u8        pad54[0x10];
};

// Target agent at self+0x324 (radius lives at +0x258).
struct cObj324 {
  u32   pad00[150];                   // 0x000 .. 0x257
  float f258;                         // 0x258
};

// eastl-style vector of slots living at self+0x354.
struct cSlotVec {
  u32* begin;                         // 0x00
  u32* end;                           // 0x04
  u32* cap;                           // 0x08
  void erase(u32* first, u32* last);                  // 0x00e25bd0
  void Insert3(u32* first, u32* last, void* v);       // 0x00bdf600
};

// Self object base: only vtable slot 0x84 (post-load hook) is called.
struct cRaidBehBase {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
  virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
  virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
  virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
  virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
  virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
  virtual void v80();
  virtual void v84();                // 0x84
};

// Timer object used by the load routine.
struct cGonzagoTimer {
  u32 pad00[8];                       // 0x00 .. 0x1f
  cGonzagoTimer();                    // 0x00b63890
  ~cGonzagoTimer();                   // 0x00b638b0
  void Load(void* stream);            // 0x00b63930
};

struct cGonzagoTimerA : cGonzagoTimer {
  u32 extra[2];                       // 0x20 .. 0x27
};

// Object at self+0x5f8: timer followed by the 0x80-byte block vector.
struct cBlockOwner {
  cGonzagoTimer timer;                // 0x00 .. 0x1f
  u32*          begin;                // 0x20 (self+0x618)
  u32*          end;                  // 0x24 (self+0x61c)
  u32           pad28[3];             // 0x28 .. 0x33
  u32*          p62c;                 // 0x34
  u32*          p630;                 // 0x38
  u32           pad3c[8];             // 0x3c .. 0x5b
  u32           p654;                 // 0x5c (self+0x654)
  u32           p658;                 // 0x60 (self+0x658)
  u32           pad64[17];            // 0x64 .. 0xa7
};

// Wide-string object at self+0x34.
struct cWideStr {
  virtual void      Assign(const void* s);    // 0x00
  virtual const u16* Chars();                 // 0x04
  u8 pad08[0x30];                             // 0x08 .. 0x33
};

struct cRaidBeh : cRaidBehBase {
  u32          pad004[12];            // 0x004 .. 0x033
  cWideStr     obj34;                 // 0x034
  u32          pad068[26];            // 0x068 .. 0x0cf
  u32          d0;                    // 0x0d0
  u32          d4;                    // 0x0d4
  u32          pad0d8[18];            // 0x0d8 .. 0x11f
  cObj120      v120;                  // 0x120
  u32          pad124[52];            // 0x124 .. 0x1f3
  u32          o1f4;                  // 0x1f4
  u32          pad1f8[5];             // 0x1f8 .. 0x20b
  u32          o20c;                  // 0x20c
  u32          pad210[54];            // 0x210 .. 0x2e7
  u32          p2e8;                  // 0x2e8
  u32          p2ec;                  // 0x2ec
  u32          p2f0;                  // 0x2f0
  u32          pad2f4[5];             // 0x2f4 .. 0x307
  cNoun**      p308;                  // 0x308
  cNoun**      p30c;                  // 0x30c
  u32          pad310[4];             // 0x310 .. 0x31f
  cNoun*       p320;                  // 0x320
  cObj324*     p324;                  // 0x324
  cNoun*       p328;                  // 0x328
  u32          pad32c[5];             // 0x32c .. 0x33f
  cNoun**      p340;                  // 0x340
  cNoun**      p344;                  // 0x344
  u32          pad348[3];             // 0x348 .. 0x353
  cSlotVec     slot354;               // 0x354
  u32          pad360[35];            // 0x360 .. 0x3eb
  cActionCircle circle3ec;            // 0x3ec
  cActionCircle circle450;            // 0x450
  cActionCircle circle4b4;            // 0x4b4
  u8           b518;                  // 0x518
  u8           pad519[0x2f];          // 0x519 .. 0x547
  u32          p548;                  // 0x548
  u32          p54c;                  // 0x54c
  u32          pad550[16];            // 0x550 .. 0x58f
  void*        p590;                  // 0x590
  u32          pad594[25];            // 0x594 .. 0x5f7
  cBlockOwner  blocks;                // 0x5f8 (vector of 0x80-byte blocks at +0x20)
  cGonzagoTimerA timer6a0;            // 0x6a0
  cGonzagoTimer  timer6c8;            // 0x6c8
  cGonzagoTimer  timer6e8;            // 0x6e8
  cGonzagoTimer  timer708;            // 0x708
  cGonzagoTimer  timer728;            // 0x728
  u32          pad748[29];            // 0x748 .. 0x7bb
  u32          p7bc;                  // 0x7bc (tree sentinel)
  u32          p7c0;                  // 0x7c0 (tree root)
  u32          pad7c4[4];             // 0x7c4 .. 0x7d3
  void*        p7d4;                  // 0x7d4
  u32          pad7d8[14];            // 0x7d8 .. 0x80f
  void*        p810;                  // 0x810

  // intra-slice thiscall helpers (bodies defined below)
  void FUN_00be5180();                // 0x00be5180
  u32  FUN_00be3420(u32 str, u32 tag);            // 0x00be3420

  // behaviour hooks (declaration only)
  void  FUN_00bdb7f0(void* noun, void* arg);      // 0x00bdb7f0
  void* FUN_00bdb590(u32 a, u32 b);               // 0x00bdb590
  u8    FUN_00be3500(void* noun, u8 flag);        // 0x00be3500
  void  FUN_00be1ef0(void* noun, u32 v);          // 0x00be1ef0
  void  FUN_00be33e0(void* noun);                 // 0x00be33e0
  void  FUN_00bd9660(void* noun);                 // 0x00bd9660
  void  FUN_00c8b2e0(void* p);                    // 0x00c8b2e0
  void  FUN_00bda0a0();                           // 0x00bda0a0
  void  Read(void* stream);                       // 0x00b18600
  void  FUN_00c00530(void* stream);               // 0x00c00530
  void  FUN_00bd8000(void* stream);               // 0x00bd8000
};

struct cObjFCC {
  cNoun* FUN_00fcc210();              // 0x00fcc210
};

// 0x00be3420: tag -> string lookup helper, thiscall with two stack arguments.
// 0x00be2440: final "detach" pass.
void __cdecl FUN_00be2440(cRaidBeh* self, u32 a, u32 b);   // 0x00be2440

// ===========================================================================
// 0x00be5130 - map a noun tag to its display string.
// ===========================================================================
// @ 0x00be5130
u32 __fastcall FUN_00be5130(cRaidBeh* self, void* dummy, u32 tag)
{
  switch (tag) {
  case 0x1a55e4d:
    return self->FUN_00be3420(0x1a56aba, tag);
  case 0xecade42:
    return self->FUN_00be3420(0x18ea2cc, tag);
  default:
    return self->FUN_00be3420(0x18eb106, tag);
  }
}

// ===========================================================================
// 0x00be5180 - clear the behaviour's agents.
// ===========================================================================
// @ 0x00be5180
void __fastcall FUN_00be5180(cRaidBeh* self, void* dummy)
{
  s32 n1 = self->p344 - self->p340;
  s32 n2 = self->p30c - self->p308;

  self->b518 = 0;
  if (self->p320 != 0) {
    self->circle3ec.slot->Reserve(self->p320);
    self->p320->sub34.v38(&self->circle3ec.slot->f0c);
  }

  for (s32 i = 0; i < n1; i++) {
    cNoun* a = self->p340[i];
    if (a == self->p320)
      continue;
    if (a->v0c(0x436f315) != 0)
      continue;
    self->circle3ec.RemoveAgent(self->p340[i]);
    self->FUN_00be3500(self->p340[i], 0);
  }

  for (s32 i = 0; i < n2; i++) {
    self->circle450.RemoveAgent(self->p308[i]);
    self->FUN_00bd9660(self->p308[i]);
  }

  FUN_00be2440(self, 0, 0);
}

// ===========================================================================
// 0x00be5280 - pull the target into the 0x3ec circle when enough points.
// ===========================================================================
// @ 0x00be5280
void __fastcall FUN_00be5280(cRaidBeh* self, void* dummy, Vec3Span* p)
{
  if (p->end - p->begin > 4) {
    Vec3 buf;
    float r = self->p324->f258;
    self->circle3ec.SetAtCenter(self->v120.v2c(), r,
                                (void*)self->v120.v5c(&buf), 0.0f);
    self->circle3ec.EmitCopy(p, g_float20);
    self->circle3ec.FUN_00afaec0();
    self->FUN_00be5180();
  }
}

// ===========================================================================
// 0x00be5320 - same, unconditional, on the 0x450 circle.
// ===========================================================================
// @ 0x00be5320
void __fastcall FUN_00be5320(cRaidBeh* self, void* dummy, Vec3Span* p)
{
  Vec3 buf;
  float r = self->p324->f258;
  self->circle450.SetAtCenter(self->v120.v2c(), r,
                              (void*)self->v120.v5c(&buf), 0.0f);
  self->circle450.EmitCopy(p, g_float4);
  self->circle450.FUN_00afaec0();
  self->FUN_00be5180();
}

// ===========================================================================
// 0x00be53b0 - spawn a noun, attach it to the behaviour and register it.
// ===========================================================================
// @ 0x00be53b0
void* __fastcall FUN_00be53b0(cRaidBeh* self, void* dummy, u32 type, void* arg2)
{
  cNoun* n = NounManager()->CreateNoun(type);
  cNoun* noun = n ? (cNoun*)n->v0c(0xe9cb8ba) : 0;

  self->FUN_00bdb7f0(noun, arg2);
  noun->v54(self);
  void* x = self->FUN_00bdb590((u32)noun->v20(), 0);
  if (x != 0) {
    void* g = ((cObjFCC*)x)->FUN_00fcc210();
    if (g != 0) {
      cNoun* o = (cNoun*)((cNoun*)g)->v0c(0xe9cb8ba);
      if (o != 0) {
        if (o->combat.GetDamageState() == 2)
          self->FUN_00be33e0(o);
      }
    }
    noun->sub34.v38((u8*)x + 0xc);
  }

  self->circle3ec.RemoveAgent(noun);
  if (self->b518 != 0)
    self->FUN_00be5180();
  else if (self->circle3ec.CountFreeSlots() == 0)
    self->FUN_00be5180();

  if (self->FUN_00be3500(noun, 1)) {
    self->FUN_00be1ef0(noun, 0);
    return noun;
  }
  NounManager()->RemoveNoun(noun);
  return 0;
}

// ===========================================================================
// 0x00be5700 - replace the behaviour's 0x354 slot vector.
// ===========================================================================
// @ 0x00be5700
void __fastcall FUN_00be5700(cRaidBeh* self, void* dummy, cSlotVec* v)
{
  cSlotVec* s = &self->slot354;
  if (v == s)
    return;
  v->erase(v->begin, v->end);
  v->Insert3(s->begin, s->end, v);
}

// ---------------------------------------------------------------------------
// External plumbing used by the teardown (0x00be4c00) and load (0x00be54c0)
// routines.
// ---------------------------------------------------------------------------
struct cMessageServer {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10();
  virtual void v14(u32 id, void* msg, u32 arg);      // 0x14
  virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
  virtual void v28();
  virtual void v2c(void* obj, u32 id, u32 arg);      // 0x2c
};
cMessageServer* __cdecl MessageServer();

struct MessageBasicRC5 {
  u32 mId;                            // 0x00
  u32 vtbl;                           // 0x04
  u32 mRCFlags;                       // 0x08
  u32 mRefCount;                      // 0x0c
  u32 data0;                          // 0x10
  u32 pad14[11];                      // 0x14 .. 0x3f
};
void __cdecl MsgBasicRC5Dtor(MessageBasicRC5* msg);

struct cPlanetInner {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
  virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
  virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
  virtual void v50(); virtual void v54();
  virtual void v58(void* a, void* b);                // 0x58
};

struct cPlanetModel {
  u32           pad00[9];             // 0x00 .. 0x23
  cPlanetInner* inner;                // 0x24
  u32  FUN_00b7ea80(u32 v);           // 0x00b7ea80
  void DoInsertValue(u32 v, u32 a, u32 b);           // 0x00b841a0
};
cPlanetModel* __cdecl PlanetModel();

struct cGameCtx {
  void* FUN_01067e60();               // 0x01067e60
};
cGameCtx* __cdecl FUN_010666a0();     // 0x010666a0

struct cSPUIMinimapWin {
  void RemoveIcon(void* owner, u32 a, u32 b);        // 0x01067e60 caller side
};

void* __cdecl GetUniverseContext();                 // cSPLivingUniverse::GetUniverseContext
void  __cdecl GetActivePlanet(u32 planet);          // cSPLivingUniverse::GetActivePlanet
u32   __cdecl GetCurrentGameMode();                 // 0x00b5b800
void* __cdecl SpaceGameGet();                       // 0x01002bd0
void  __cdecl FUN_00ff5b90();
void  __cdecl FUN_00c711e0(u32 planet);
void  __cdecl FUN_00d5aae0(void* a, void* b, void* c);
void  __cdecl FUN_00ae6e70(u32 a, u32 b);
void* __cdecl FUN_00b25ca0();
void* __cdecl FUN_00bdf9e0(void* v);                 // 0x00bdf9e0
void  __cdecl FUN_00be3350(void* noun);              // 0x00be3350
void  __cdecl FUN_00c01e80(cRaidBeh* self);          // 0x00c01e80
void  __cdecl FUN_00bf45f0(cRaidBeh* self, u32 v);   // 0x00bf45f0
u32   __cdecl FUN_00bdd600(u32* a, u32* b, u32* c);  // 0x00bdd600
void  __cdecl FUN_00bda710(void* a, u32* b);         // 0x00bda710

struct cBlockVec {                    // value returned by FUN_00b25ca0
  u32* begin;                         // 0x00
  u32* end;                           // 0x04
};

struct cObj1f4 {
  u32 pad00[1];
  void FUN_00ac0450();                // 0x00ac0450
};

// ---------------------------------------------------------------------------
// 0x00be4c00 - full teardown of the raid behaviour.
// ---------------------------------------------------------------------------
// @ 0x00be4c00
void __fastcall FUN_00be4c00(cRaidBeh* self, void* dummy)
{
  cRaidBeh* o = self;
  cPlanetModel* pm;
  cNoun* r;
  cGameNounManager* mgr;

  o->v120.v2c();
  pm = PlanetModel();
  u32 v = pm->FUN_00b7ea80((u32)o->v120.v2c());
  pm = PlanetModel();
  pm->DoInsertValue(v, 0xffffffff, 0);

  if (GetUniverseContext() == 0 && o->p2f0 != 0) {
    MessageBasicRC5 msg;
    msg.mId = 0;
    msg.vtbl = 0x013eb844;
    msg.mRCFlags = 0;
    msg.mRefCount = 0;
    msg.data0 = (u32)o;
    MessageServer()->v14(0x3337cbb, &msg, 0);
    MsgBasicRC5Dtor(&msg);
  }

  o->FUN_00bda0a0();

  r = (cNoun*)o->p810;
  o->p810 = 0;
  if (r != 0)
    r->v04();

  if (GetCurrentGameMode() == 0x01654c05 && SpaceGameGet() != 0
      && FUN_010666a0() != 0) {
    cSPUIMinimapWin* win = (cSPUIMinimapWin*)FUN_010666a0()->FUN_01067e60();
    if (win != 0)
      win->RemoveIcon(o, 1, 0);
  }

  r = (cNoun*)o->p7d4;
  if (r != 0) {
    r->v0c(1);
    r = (cNoun*)o->p7d4;
    if (r != 0) {
      o->p7d4 = 0;
      r->v04();
    }
  }

  mgr = NounManager();
  for (s32 i = 0; i < 0x200; i += 0x80) {
    r = (cNoun*)*(u32*)(i + 0x70 + (u32)o->blocks.begin);
    if (r != 0) {
      *(u32*)(i + 0x70 + (u32)o->blocks.begin) = 0;
      r->vc0();
    }
    u32* slot = (u32*)(i + 0x78 + (u32)o->blocks.begin);
    cNoun* r2 = (cNoun*)*slot;
    if (r2 != 0) {
      *slot = 0;
      r2->vc0();
    }
  }

  while (o->blocks.p62c != o->blocks.p630) {
    o->blocks.p630--;
    u32 id = *o->blocks.p630;
    cNoun* n = (cNoun*)*o->blocks.p630;
    if (n != 0)
      n->v04();
    mgr->RemoveNoun((void*)id);
  }

  if (o->p324 != 0) {
    ((cNoun*)o->p324)->v44();
    mgr->RemoveNoun(o->p324);
    r = (cNoun*)o->p324;
    if (r != 0) {
      o->p324 = 0;
      r->v04();
    }
  }

  if (o->p328 != 0) {
    mgr->RemoveNoun(o->p328);
    r = (cNoun*)o->p328;
    if (r != 0) {
      o->p328 = 0;
      r->v04();
    }
  }

  while (o->p340 != o->p344) {
    cNoun* n = (cNoun*)*o->p340;
    if (n != 0) {
      n->v00();
      NounManager()->RemoveNoun(n);
      FUN_00be3350(n);
      n->v04();
    }
  }

  while (o->slot354.begin != o->slot354.end) {
    u32 el = *o->slot354.begin;
    u32 tmp = el;
    if (o->slot354.begin != o->slot354.end && el != 0) {
      o->circle4b4.RemoveAgent((void*)el);
      NounManager()->RemoveNoun((void*)el);
      FUN_00d5aae0(&o->slot354.begin, &tmp, &o->v120);
    }
  }

  r = o->p320;
  if (r != 0) {
    o->p320 = 0;
    r->v04();
  }

  FUN_00bdd600((u32*)o->d0, (u32*)o->d4, 0);

  while (o->p308 != o->p30c) {
    o->p30c--;
    cNoun* n = (cNoun*)*o->p30c;
    if (*o->p30c != 0)
      ((cNoun*)*o->p30c)->v04();
    n->v44();
    mgr->RemoveNoun(n);
  }

  if (o->p590 != 0) {
    FUN_00bf45f0(o, 0);
    r = (cNoun*)o->p590;
    if (r != 0) {
      o->p590 = 0;
      r->v04();
    }
  }

  ((cObj1f4*)&o->o1f4)->FUN_00ac0450();
  FUN_00ae6e70(o->p548, o->p54c);

  NounManager();
  cBlockVec* bv = (cBlockVec*)FUN_00b25ca0();
  s32 n = (s32)(bv->end - bv->begin);
  for (s32 i = 0; i < n; i++) {
    cNoun* n2 = (cNoun*)bv->begin[i];
    if (n2 != 0)
      FUN_00bdf9e0(n2->v4c());
  }

  if (GetUniverseContext() == 0 && o->p2f0 != 0) {
    SpaceGameGet();
    FUN_00ff5b90();
    void* flag = 0;
    if (o->p2e8 != 0) {
      cPlanetModel* p = PlanetModel();
      p->inner->v58((void*)o->p2e8, flag);
    }
    if (o->p2ec != 0) {
      cPlanetModel* p = PlanetModel();
      p->inner->v58((void*)o->p2ec, flag);
    }
    GetActivePlanet(o->p2f0);
    FUN_00c711e0(o->p2f0);
  }

  o->p2f0 = 0;
  o->blocks.p654 = 0;

  MessageServer()->v2c(&o->o20c, 0x5416d55, 0xffffd8f1);
  MessageServer()->v2c(&o->o20c, 0x56e50f1, 0xffffd8f1);
  MessageServer()->v2c(&o->o20c, 0x40fafdf, 0xffffd8f1);
  MessageServer()->v2c(&o->o20c, 0x5f74817, 0xffffd8f1);
  MessageServer()->v2c(&o->o20c, 0x6787056, 0xffffd8f1);

  FUN_00c01e80(o);
  o->FUN_00c8b2e0(&o->v120);
}

// ---------------------------------------------------------------------------
// Stream plumbing for the load routine (0x00be54c0).
// ---------------------------------------------------------------------------
struct cIO {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14();
  virtual cIO* v18();                                 // 0x18
};

struct cBlockVector;                                  // self+0x618

struct cStream {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual cIO* v20();                                 // 0x20
  virtual void v24();
  virtual void v28(u32 id, void* p, u32 v);           // 0x28
  virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
  virtual u32  v3c();                                 // 0x3c
};

void __cdecl EA_IO_ReadInt32(void* io, void* dst, u32 count, u32 hint);

struct cTempWideStr {
  const u16* begin;                                   // 0x00
  u32        pad04;                                   // 0x04
  const u16* end;                                     // 0x08
  u32        pad0c;                                   // 0x0c
};

cTempWideStr* __cdecl FUN_004010a0(cTempWideStr* buf, u32 id);
void __fastcall FUN_005ecf80(cTempWideStr* s, void* dummy);
void __cdecl operator_delete_array(void* p);

void __fastcall FUN_00bda710(void* vec, void* dummy, void* a, void* b);

struct cSpeciesMgr {
  void* GetProfile(void* key);                        // 0x004df550
};
void* __cdecl FUN_00401090(void* key);                // 0x00401090
void* __cdecl RBTreeIncrement(void* node);            // 0x00921580

struct cVarListSerializer {
  u32 pad[0x288];                                     // 0xa20 bytes
  cVarListSerializer(void* owner, void* name, u32 hash);
  u8  Serialize(void* stream);
};

static s32 WideCmp(const u16* a, const u16* b)
{
  while (*a != 0 && *a == *b) {
    a++;
    b++;
  }
  return (s32)*a - (s32)*b;
}

// ---------------------------------------------------------------------------
// 0x00be54c0 - load the raid behaviour state from a stream.
// ---------------------------------------------------------------------------
// @ 0x00be54c0
u8 __fastcall FUN_00be54c0(cRaidBeh* self, void* dummy, cStream* stream)
{
  s32 pad;
  cIO* io = stream->v20()->v18();
  EA_IO_ReadInt32(io, &pad, 1, 0);

  self->Read(stream);
  self->v120.FUN_00c88b00(stream);
  self->FUN_00c00530(stream);

  if (WideCmp(self->obj34.Chars(), *(const u16**)0x151ac94) == 0) {
    cTempWideStr tmp;
    FUN_005ecf80(FUN_004010a0(&tmp, 0x58f4c251), 0);
    self->obj34.Assign(tmp.begin);
    if ((((s32)(tmp.end) - (s32)(tmp.begin)) & 0xfffffffe) > 2 && tmp.begin != 0)
      operator_delete_array((void*)tmp.begin);
  }

  u32* newEnd = (u32*)FUN_00bdd600(self->blocks.end, self->blocks.end,
                                   self->blocks.begin);
  FUN_00bda710(&self->blocks.begin, 0, newEnd, self->blocks.end);
  self->blocks.end = newEnd;

  if (self->p590 != 0) {
    self->p590 = 0;
    ((cNoun*)self->p590)->v04();
  }
  stream->v28(0x901f1362, &self->p590, 0);

  self->blocks.timer.Load(stream);

  if (stream->v3c() < 0x1c000e) {
    cGonzagoTimer tmp;
    tmp.Load(stream);
  }

  self->timer6a0.Load(stream);
  self->timer6c8.Load(stream);
  self->timer6e8.Load(stream);
  self->timer708.Load(stream);
  self->timer728.Load(stream);

  cVarListSerializer ser(self, (void*)0x156ea28, 0x1a80d26);
  u8 ok = ser.Serialize(stream);

  if (self->blocks.p658 != 0) {
    cSpeciesMgr* mgr = (cSpeciesMgr*)FUN_00401090(&self->blocks.p658);
    self->blocks.p654 = (u32)mgr->GetProfile(&self->blocks.p658);
  }

  void* head = &self->p7bc;
  for (void* n = (void*)self->p7c0; n != head; n = RBTreeIncrement(n)) {
  }

  self->v84();
  self->FUN_00bd8000(stream);
  return ok;
}
