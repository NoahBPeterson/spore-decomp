// Slice s00e38ce0 - SP::cSPUITimeline UI animation helpers.
// Reconstructed from annotated disassembly + Ghidra decompiles.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;
typedef          short s16;
typedef          char  s8;
typedef unsigned long long u64;
typedef          long long s64;

// ---- vtable-call signature typedefs (all thiscall) -----------------------
typedef void*  (__thiscall *TFp0)(void*);
typedef void   (__thiscall *TFv0)(void*);
typedef void   (__thiscall *TFv1)(void*, s32);
typedef void   (__thiscall *TFv2)(void*, s32, s32);

// ---- external functions -------------------------------------------------
struct cSPUILayout;
struct cSPUIAnimator;
struct AnimRaw;
struct AssetDir;
struct Pool;

cSPUILayout* __cdecl FUN_0067de90();          // 0x0067de90 - active layout
void*        __cdecl FUN_0067cb30();          // 0x0067cb30
void*        __cdecl SP_GetCurrentGameMode(); // 0x00b5b800
void*        __cdecl SP_GameTimeManager();    // 0x00b3d380
void*        __cdecl SPUIHelpers_GetMainWindowArea(void* out); // 0x00805ea0
float        __cdecl SPUIHelpers_GetElapsedSeconds(float a, s32 b, void* c, s32 d); // 0x00805080
float        __cdecl RandomFloatRange(float lo, float hi);     // 0x00572a10
AnimRaw*     __cdecl SPUICreateWindowAnimationTargetPosition(AnimRaw* buf, void* wnd,
                                                             float a, float b, float c,
                                                             float d, s32 e); // 0x007f80d0
void         __cdecl FUN_00571e80(void* stopwatch);            // 0x00571e80

s32   __cdecl Time_Current();        // 0x00e5c520
float __cdecl Time_SourceLevel();    // 0x00e5c530
float __cdecl Time_TimelineForest(); // 0x00d386a0
float __cdecl Time_TimelineSpace();  // 0x00cdb8b0

// ---- structs ------------------------------------------------------------
struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };

// Scratch buffer filled by SPUICreateWindowAnimationTargetPosition (0x68 bytes).
struct AnimRaw { u32 w[0x1a]; };

struct Wnd {
  void* GetRect();                       // 0x38
  void  SetRect(float a, float b);       // 0x64
  void  SetText(const u16* s);           // 0x80
  bool  IsVisible();                     // 0x00810070
};

// Virtual interface of the UI window class: only the slots we call are
// declared, the rest are placeholders to keep the slot offsets right.
struct WndVt {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13();
  virtual void* GetRect();               // 0x38
  virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
  virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
  virtual void v23(); virtual void v24();
  virtual void SetRect(float a, float b); // 0x64
  virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
  virtual void v30();
  virtual void SetVisible(s32 a, s32 b);  // 0x7c
  virtual void SetText(const u16* s);     // 0x80
};

struct cSPUILayout {
  Wnd* FindWindowByID(u32 id, s32 flag); // 0x008105b0
};

struct cSPUIAnimator {
  u8   RemoveAnimation(void* wnd, s32 id);            // 0x007f6210
  void AddAnimation(void* target, void* ref, s32 a);  // 0x007f8d10
};

struct Stopwatch { u8 pad[0x08]; };

// IntVector-like node returned by the layout pool.
struct IVec {
  u8    pad00[0x0c];
  u32*  data;                            // +0x0c
  void  resize(u32 n);                   // 0x007eb820
};

struct Pool {
  IVec* New(u32 size, u32 flags);        // 0x007ec160
};

struct AssetDir {
  u8 GetServerId(void* key, u64* out, u8 flag); // 0x0054e530
};

struct AssetOwner {
  u8        pad00[0x58];
  AssetDir* dir;                         // +0x58
};

struct GameTimeMgr {
  u64 GetTicks();                        // 0x00b316c0
};

// SP::cSPUITimeline (partial layout; only members touched here).
struct Timeline {
  u8          pad00[0x30];
  Wnd*        p30;                       // +0x030
  u8          pad34[0x348 - 0x34];
  cSPUILayout* p348;                     // +0x348
  cSPUILayout* p34c;                     // +0x34c
  u8          pad350[0x370 - 0x350];
  u8          b370;                      // +0x370
  u8          pad371[0x458 - 0x371];
  cSPUIAnimator* anim;                   // +0x458
  u8          pad45c[0x488 - 0x45c];
  u32         n488;                      // +0x488
  u8          pad48c[0x4a8 - 0x48c];
  Stopwatch   sw4a8;                     // +0x4a8
  float       f4c0;                      // +0x4c0
  u8          pad4c4[0x4e8 - 0x4c4];
  u8          b4e8;                      // +0x4e8
  u8          pad4e9[0x530 - 0x4e9];
  Stopwatch   sw530;                     // +0x530
};

// sp::cString (SP::cString_s006b_47a0) - only the API we touch.
struct CString {
  u8          mData[0x24];
  void        ctor();                    // 0x006b5060
  void        dtor();                    // 0x006b5240
  u8          Load(u32 id, u32 value, s32 a); // 0x006b54b0
  const u16*  GetText();                 // 0x006b55c0
};

struct Rand {
  u32 RandomUint32Uniform(u32 n);        // 0x00a68fb0
};

// ---- absolute globals ---------------------------------------------------
#define G_RAND          ((Rand*)0x01601760)
#define G_LAST_RANDOM   (*(u32*)0x016acc60)
#define G_MAIN_AREA     ((Vec4*)0)

static const u32 kLastRandom = 0x016acc60;
static const u32 kTimeConst   = 0x01471064;   // 0.5f

static u32 NowMs(void)
{
  GameTimeMgr* m = (GameTimeMgr*)SP_GameTimeManager();
  u64 t = m->GetTicks();
  return (u32)(t / 1000);
}

// ======================================================================
// 0x00e38ce0 - play the "space-mode enter/exit" UI animation
// ======================================================================
// @ 0x00e38ce0
void __fastcall FUN_00e38ce0(Timeline* self, void* dummy, u32 mode)
{
  (void)dummy;
  Wnd* w1 = self->p348->FindWindowByID(0x06456c48u, 1);
  Wnd* w2 = (self->p34c != 0) ? self->p34c->FindWindowByID(0x06456c48u, 1) : 0;
  ((WndVt*)w1)->SetVisible(1, 1);
  if (self->anim == 0) return;

  self->anim->RemoveAnimation(w1, -1);
  if (w2 != 0) self->anim->RemoveAnimation(w2, -1);

  const u32* table;
  u32 n;
  if (mode == 0x01654c02u) { table = (const u32*)0x01481d04; n = 9; }
  else if (mode == 0x01654c04u) { table = (const u32*)0x01481d28; n = 0x0b; }
  else if (mode == 0x01654c05u) { table = (const u32*)0x01481d54; n = 0x0c; }
  else { table = (const u32*)0x01481cd4; n = 0x0c; }

  CString str;
  str.ctor();
  u32 idx;
  do {
    idx = G_RAND->RandomUint32Uniform(n);
  } while (idx == G_LAST_RANDOM);
  G_LAST_RANDOM = idx;
  str.Load(0x8c509d6cu, table[idx], 0);

  ((WndVt*)w1)->SetText(str.GetText());
  if (w2 != 0) ((WndVt*)w2)->SetText(str.GetText());

  Vec4 area;
  SPUIHelpers_GetMainWindowArea(&area);
  float h = area.w - area.y;

  float* r1 = (float*)((WndVt*)w1)->GetRect();
  float ry = r1[1];
  float rx = r1[0];
  float rz = r1[2];
  ((WndVt*)w1)->SetRect(h, ry);
  if (w2 != 0) ((WndVt*)w2)->SetRect(h, ry);

  float off = ((area.x - rz) - (rx - h)) * 0.5f;

  float t1 = SPUIHelpers_GetElapsedSeconds(self->f4c0, 2, w1, 0);
  AnimRaw buf1;
  AnimRaw* a1 = SPUICreateWindowAnimationTargetPosition(&buf1, w1, off, ry, t1, 0.0f, 0);
  self->anim->AddAnimation(a1, w1, 0);

  if (w2 != 0) {
    AnimRaw buf2;
    float t2 = SPUIHelpers_GetElapsedSeconds(self->f4c0, 2, w2, 0);
    AnimRaw* a2 = SPUICreateWindowAnimationTargetPosition(&buf2, w2, off, ry, t2, 0.0f, 0);
    self->anim->AddAnimation(a2, w2, 0);
  }

  FUN_00571e80(&self->sw4a8);
  ((WndVt*)w1)->SetVisible(1, 2);
  if (w2 != 0) ((WndVt*)w2)->SetVisible(1, 2);
  self->b4e8 = 1;
  str.dtor();
}

// ======================================================================
// 0x00e38fd0 - slide the panel in
// ======================================================================
// @ 0x00e38fd0
void __fastcall FUN_00e38fd0(Timeline* self, void* dummy)
{
  (void)dummy;
  Wnd* w = self->p348->FindWindowByID(0x06456c48u, 1);
  if (self->anim == 0 || w == 0) return;

  self->anim->RemoveAnimation(w, -1);

  float* r = (float*)((WndVt*)w)->GetRect();
  float ry = r[1];
  float rx = r[0];
  float rz = r[2];
  ((WndVt*)w)->SetRect(-(rz - rx), ry);

  float t = SPUIHelpers_GetElapsedSeconds(self->f4c0, 1, w, 0);
  AnimRaw buf;
  AnimRaw* a = SPUICreateWindowAnimationTargetPosition(&buf, w, -(rz - rx), ry, t, 0.0f, 0);
  self->anim->AddAnimation(a, w, 0);

  FUN_00571e80(&self->sw4a8);
}

// ======================================================================
// 0x00e390d0 - slide the panel out
// ======================================================================
// @ 0x00e390d0
void __fastcall FUN_00e390d0(Timeline* self, void* dummy)
{
  (void)dummy;
  Wnd* w = self->p348->FindWindowByID(0x064db520u, 1);
  ((WndVt*)w)->SetVisible(1, 1);
  if (self->anim == 0) return;

  self->anim->RemoveAnimation(w, -1);

  Vec4 area;
  SPUIHelpers_GetMainWindowArea(&area);
  Wnd* ref = self->p348->FindWindowByID(0x064d0819u, 1);
  float* rr = (float*)((WndVt*)ref)->GetRect();
  float ry = rr[1];
  float* r = (float*)((WndVt*)w)->GetRect();
  float rx = r[0];
  float rz = r[2];
  ((WndVt*)w)->SetRect(-(rz - rx), ry);

  float t = SPUIHelpers_GetElapsedSeconds(10.0f, 2, w, 0);
  AnimRaw buf;
  AnimRaw* a = SPUICreateWindowAnimationTargetPosition(&buf, w, 10.0f, ry, t, 0.0f, 0);
  self->anim->AddAnimation(a, w, 0);

  FUN_00571e80(&self->sw530);
}

// ======================================================================
// 0x00e39200 - slide the panel back to the centre
// ======================================================================
// @ 0x00e39200
void __fastcall FUN_00e39200(Timeline* self, void* dummy)
{
  (void)dummy;
  Wnd* w = self->p348->FindWindowByID(0x064db520u, 1);
  if (self->anim == 0 || w == 0) return;

  self->anim->RemoveAnimation(w, -1);

  Vec4 area;
  SPUIHelpers_GetMainWindowArea(&area);
  float* r = (float*)((WndVt*)w)->GetRect();
  float ry = r[1];
  float dx = -(area.z - area.x);
  ((WndVt*)w)->SetRect(dx, ry);

  float t = SPUIHelpers_GetElapsedSeconds(10.0f, 1, w, 0);
  AnimRaw buf;
  AnimRaw* a = SPUICreateWindowAnimationTargetPosition(&buf, w, dx, ry, t, 0.0f, 0);
  self->anim->AddAnimation(a, w, 0);

  FUN_00571e80(&self->sw530);
}

// ======================================================================
// 0x00e39300 - set one mode value on all known windows
// ======================================================================
// @ 0x00e39300
void __fastcall FUN_00e39300(Timeline* self, void* dummy, s32 v)
{
  (void)dummy;
  for (s32 addr = 0x015a5a54; addr < 0x015a5a68; addr += 4) {
    Wnd* w = (Wnd*)self->p348->FindWindowByID(*(u32*)addr, 1);
    if (w != 0) ((WndVt*)w)->SetVisible(1, v);
  }
}

// ======================================================================
// 0x00e39350 - SP::cSPUITimeline::InitGonzagoSubsystem
// ======================================================================
// @ 0x00e39350
void __fastcall FUN_00e39350(Timeline* self, void* dummy, s32 v)
{
  (void)dummy;
  for (u32 i = 0; i < self->n488; ++i) {
    Wnd* w = (Wnd*)self->p348->FindWindowByID(0x05db9a70u + i, 1);
    if (w != 0) ((WndVt*)w)->SetVisible(1, v);
  }
}

// ======================================================================
// 0x00e393b0 - is the timeline panel visible?
// ======================================================================
// @ 0x00e393b0
s32 __fastcall FUN_00e393b0(Timeline* self, void* dummy)
{
  (void)dummy;
  if (self->b370 != 0) goto ret1;
  if (self->p30 != 0 && self->p30->IsVisible() != 0) goto ret1;
  return 0;
ret1:
  return 1;
}

// ======================================================================
// 0x00e393e0 - write a Vec3 (x/y swapped) into the node data
// ======================================================================
// @ 0x00e393e0
void FUN_00e393e0(void* node, s32 idx, Vec3* v)
{
  if (node == 0) return;
  ((IVec*)node)->data[idx]     = *(u32*)&v->y;
  ((IVec*)node)->data[idx + 1] = *(u32*)&v->x;
  ((IVec*)node)->data[idx + 2] = *(u32*)&v->z;
}

// ======================================================================
// 0x00e39420 - read a Vec3 (x/y swapped) back out of the node data
// ======================================================================
// @ 0x00e39420
void FUN_00e39420(void* node, s32 idx, Vec3* v)
{
  if (node == 0) return;
  *(u32*)&v->y = ((IVec*)node)->data[idx];
  *(u32*)&v->x = ((IVec*)node)->data[idx + 1];
  *(u32*)&v->z = ((IVec*)node)->data[idx + 2];
}

// ======================================================================
// 0x00e39450 - attach pollinator server ids to a node
// ======================================================================
// @ 0x00e39450
void FUN_00e39450(void* node, void* key1, void* key2)
{
  AssetOwner* owner = (AssetOwner*)FUN_0067cb30();
  AssetDir* dir = owner->dir;
  if (dir == 0) return;

  u64 id = (u64)-1;
  if (dir->GetServerId(key1, &id, 0) && id != (u64)-1) {
    ((IVec*)node)->data[3] = ((u32*)&id)[1];
    ((IVec*)node)->data[4] = ((u32*)&id)[0];
  }
  if (dir->GetServerId(key2, &id, 0) && id != (u64)-1) {
    ((IVec*)node)->data[5] = ((u32*)&id)[1];
    ((IVec*)node)->data[6] = ((u32*)&id)[0];
  }
}

// ======================================================================
// 0x00e394f0 - build a forest-mode UI log entry pair
// ======================================================================
// @ 0x00e394f0
IVec* FUN_00e394f0(u32 id, Vec3* p2, Vec3* p3, Vec3* p4, Vec3* p5)
{
  IVec* first = 0;
  u8 b1 = (SP_GetCurrentGameMode() == (void*)0x01654c00) ||
          (SP_GetCurrentGameMode() == (void*)0x00dbdba1);

  Pool* pool = (Pool*)FUN_0067de90();
  if (pool == 0) goto done;

  first = pool->New(0x0c, 0);
  first->resize(0x1b);

  ((IVec*)first)->data[0] = id;
  float t = b1 ? Time_SourceLevel() : RandomFloatRange(-0.15f, 0.15f);
  *(float*)&((IVec*)first)->data[1] = t;
  ((IVec*)first)->data[2] = b1 ? (u32)(Time_Current() / 1000) : NowMs();

  ((IVec*)first)->data[3] = *(u32*)&p2->y;
  ((IVec*)first)->data[4] = *(u32*)&p2->x;
  ((IVec*)first)->data[5] = *(u32*)&p2->z;
  ((IVec*)first)->data[6] = *(u32*)&p3->y;
  ((IVec*)first)->data[7] = *(u32*)&p3->x;
  ((IVec*)first)->data[8] = *(u32*)&p3->z;
  ((IVec*)first)->data[0x10] = *(u32*)&p4->y;
  ((IVec*)first)->data[0x11] = *(u32*)&p4->x;
  ((IVec*)first)->data[0x12] = *(u32*)&p4->z;
  ((IVec*)first)->data[0x0d] = *(u32*)&p5->y;
  ((IVec*)first)->data[0x0e] = *(u32*)&p5->x;
  ((IVec*)first)->data[0x0f] = *(u32*)&p5->z;

  IVec* second = pool->New(6, 0);
  second->resize(0x18);
  ((IVec*)second)->data[0] = id;
  *(float*)&((IVec*)second)->data[1] = t;
  ((IVec*)second)->data[2] = b1 ? (u32)(Time_Current() / 1000) : NowMs();

  FUN_00e39450(second, p2, p3);
  ((IVec*)second)->data[0x0e] = *(u32*)&p4->y;
  ((IVec*)second)->data[0x0f] = *(u32*)&p4->x;
  ((IVec*)second)->data[0x10] = *(u32*)&p4->z;
  ((IVec*)second)->data[0x0b] = *(u32*)&p5->y;
  ((IVec*)second)->data[0x0c] = *(u32*)&p5->x;
  ((IVec*)second)->data[0x0d] = *(u32*)&p5->z;

done:
  return first;
}

// ======================================================================
// 0x00e39710 - build a forest-timeline UI log entry pair
// ======================================================================
// @ 0x00e39710
IVec* FUN_00e39710(u32 id, Vec3* p2, Vec3* p3, Vec3* p4, Vec3* p5)
{
  IVec* first = 0;
  u8 b1 = (SP_GetCurrentGameMode() == (void*)0x01654c01) ||
          (SP_GetCurrentGameMode() == (void*)0x00dbdba1);

  Pool* pool = (Pool*)FUN_0067de90();
  if (pool == 0) goto done;

  first = pool->New(0x0c, 0);
  first->resize(0x1b);

  ((IVec*)first)->data[0] = id;
  float t = b1 ? Time_TimelineForest() : RandomFloatRange(-0.15f, 0.15f);
  *(float*)&((IVec*)first)->data[1] = t;
  ((IVec*)first)->data[2] = NowMs();

  ((IVec*)first)->data[3] = *(u32*)&p2->y;
  ((IVec*)first)->data[4] = *(u32*)&p2->x;
  ((IVec*)first)->data[5] = *(u32*)&p2->z;
  ((IVec*)first)->data[6] = *(u32*)&p3->y;
  ((IVec*)first)->data[7] = *(u32*)&p3->x;
  ((IVec*)first)->data[8] = *(u32*)&p3->z;
  ((IVec*)first)->data[0x10] = *(u32*)&p4->y;
  ((IVec*)first)->data[0x11] = *(u32*)&p4->x;
  ((IVec*)first)->data[0x12] = *(u32*)&p4->z;
  ((IVec*)first)->data[0x0d] = *(u32*)&p5->y;
  ((IVec*)first)->data[0x0e] = *(u32*)&p5->x;
  ((IVec*)first)->data[0x0f] = *(u32*)&p5->z;

  IVec* second = pool->New(6, 0);
  second->resize(0x18);
  ((IVec*)second)->data[0] = id;
  *(float*)&((IVec*)second)->data[1] = t;
  ((IVec*)second)->data[2] = NowMs();

  FUN_00e39450(second, p2, p3);
  ((IVec*)second)->data[0x0e] = *(u32*)&p4->y;
  ((IVec*)second)->data[0x0f] = *(u32*)&p4->x;
  ((IVec*)second)->data[0x10] = *(u32*)&p4->z;
  ((IVec*)second)->data[0x0b] = *(u32*)&p5->y;
  ((IVec*)second)->data[0x0c] = *(u32*)&p5->x;
  ((IVec*)second)->data[0x0d] = *(u32*)&p5->z;

done:
  return first;
}

// ======================================================================
// 0x00e398e0 - build a space-mode UI log entry pair
// ======================================================================
// @ 0x00e398e0
IVec* FUN_00e398e0(u32 id, Vec3* p2, Vec3* p3, Vec3* p4, u32 v1, u32 v2, u32 v3)
{
  IVec* first = 0;
  u8 b1 = (SP_GetCurrentGameMode() == (void*)0x01654c02) ||
          (SP_GetCurrentGameMode() == (void*)0x00dbdba1);

  Pool* pool = (Pool*)FUN_0067de90();
  if (pool == 0) goto done;

  first = pool->New(0x0c, 0);
  first->resize(0x1b);

  ((IVec*)first)->data[0] = id;
  float t = b1 ? Time_TimelineSpace() : RandomFloatRange(-0.15f, 0.15f);
  *(float*)&((IVec*)first)->data[1] = t;
  ((IVec*)first)->data[2] = NowMs();

  ((IVec*)first)->data[3] = *(u32*)&p2->y;
  ((IVec*)first)->data[4] = *(u32*)&p2->x;
  ((IVec*)first)->data[5] = *(u32*)&p2->z;
  ((IVec*)first)->data[6] = *(u32*)&p3->y;
  ((IVec*)first)->data[7] = *(u32*)&p3->x;
  ((IVec*)first)->data[8] = *(u32*)&p3->z;
  ((IVec*)first)->data[0x10] = *(u32*)&p4->y;
  ((IVec*)first)->data[0x11] = *(u32*)&p4->x;
  ((IVec*)first)->data[0x12] = *(u32*)&p4->z;
  ((IVec*)first)->data[0x0b] = v1;
  ((IVec*)first)->data[0x0c] = v2;
  ((IVec*)first)->data[0x1a] = v3;

  IVec* second = pool->New(6, 0);
  second->resize(0x18);
  ((IVec*)second)->data[0] = id;
  *(float*)&((IVec*)second)->data[1] = t;
  ((IVec*)second)->data[2] = NowMs();

  FUN_00e39450(second, p2, p3);
  ((IVec*)second)->data[0x0e] = *(u32*)&p4->y;
  ((IVec*)second)->data[0x0f] = *(u32*)&p4->x;
  ((IVec*)second)->data[0x10] = *(u32*)&p4->z;
  ((IVec*)second)->data[9]  = v1;
  ((IVec*)second)->data[0x0a] = v2;
  ((IVec*)second)->data[0x17] = v3;

done:
  return first;
}
