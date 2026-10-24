// Slice s00d01f50 - SP::cRelationshipManager relationship helpers, the
// personality calculation and the cSPUILayoutManager world (de)serialisers.
// Reconstructed from annotated disassembly + Ghidra decompiles.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned int   u32;
typedef unsigned char  u8;
typedef          int   s32;

// ---------------------------------------------------------------------------
// Empire / relationship records.
// ---------------------------------------------------------------------------
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

// Dword view of the same record (used by the bit-1 accessor).
struct cRelObj32 {
  u32 pad00;                       // 0x000
  u32 f04;                         // 0x004
};

struct cRelationshipManager {
  u32  FUN_00d01ab0(u32 a, u32 b, u32 c, u32 d);   // 0x00d01ab0
  void* FUN_00d01410(u32 x);                       // 0x00d01410
  float FUN_00d01470(u32 x, u32 kind);             // 0x00d01470
};

cEmpire* __cdecl GetPlayerEmpire();                // 0x01021300

// ---------------------------------------------------------------------------
// 0x00d01f50 - bit 0 of the relationship flags between two empires, with the
// "player empire" arguments normalised first.
// ---------------------------------------------------------------------------
// @ 0x00d01f50
u8 __fastcall FUN_00d01f50(cRelationshipManager* self, void* dummy,
                           cEmpire* a, cEmpire* b)
{
  cEmpire* player = GetPlayerEmpire();
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

// ---------------------------------------------------------------------------
// 0x00d01fb0 - bit 1 of the relationship flags between two empires.
// ---------------------------------------------------------------------------
// @ 0x00d01fb0
u8 __fastcall FUN_00d01fb0(cRelationshipManager* self, void* dummy,
                           cEmpire* a, cEmpire* b)
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

// ---------------------------------------------------------------------------
// 0x00d01ff0 - bit 1 of the relationship flags, with the player empire
// arguments normalised first.
// ---------------------------------------------------------------------------
// @ 0x00d01ff0
u8 __fastcall FUN_00d01ff0(cRelationshipManager* self, void* dummy,
                           cEmpire* a, cEmpire* b)
{
  cEmpire* player = GetPlayerEmpire();
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

// ---------------------------------------------------------------------------
// Personality calculation dependencies.
// ---------------------------------------------------------------------------
struct cTerrainSphere {
  u32 FUN_00c75420();                            // 0x00c75420
};

struct cNounManager {
  cTerrainSphere* GetCurrentTerrainSphere();     // 0x00f67d90
};

cNounManager* __cdecl NounManager();             // 0x00b3d300

// Relationship record used by CalculateRelationshipPersonality.
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

extern "C" {
float g_relNeg2 = -2.0f;
float g_relNeg1 = -1.0f;
float g_rel1    =  1.0f;
float g_rel2    =  2.0f;
float g_rel3    =  3.0f;
float g_rel4    =  4.0f;
}

// ---------------------------------------------------------------------------
// 0x00d02050 - SP::cRelationshipManager::CalculateRelationshipPersonality
// ---------------------------------------------------------------------------
// @ 0x00d02050
float __fastcall FUN_00d02050(cRelationshipManager* self, void* dummy,
                              cRel* p1, cRel* p2)
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
    u32 t = NounManager()->GetCurrentTerrainSphere()->FUN_00c75420();
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

// ---------------------------------------------------------------------------
// eastl::wstring helpers used by the cSPUILayoutManager world serialisers.
// ---------------------------------------------------------------------------
struct cWString {
  const wchar_t* mpBegin;                        // 0x00
  const wchar_t* mpEnd;                          // 0x04
  const wchar_t* mpCapacity;                     // 0x08
  void RangeInitialize(const wchar_t* p);        // 0x00579a90
  void CopyConstruct(const cWString& src);       // 0x0056e2d0
};

void __cdecl ConvertToString16(cWString* out, const char* src, int len);  // 0x0093c5a0
void __cdecl FreeStringBuffer(void* p);                                   // 0x00f47380

extern "C" const wchar_t g_emptyW[1] = { 0 };

static void FreeWString(cWString* s)
{
  if (s->mpBegin != 0 &&
      ((u32)((const char*)s->mpEnd - (const char*)s->mpBegin) & 0xfffffffeu) > 2)
    FreeStringBuffer((void*)s->mpBegin);
}

// ---------------------------------------------------------------------------
// Layout-manager command context: two vtable entry points.
// ---------------------------------------------------------------------------
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

// The rbtree container embedded in cSPUILayoutManager::cWorld.
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

// Serialisation stream wrapper.
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

// ---------------------------------------------------------------------------
// 0x00d022e0 - write the string for a world key, then walk the tree emitting
// each world record; the returned flag reports whether the walk stayed valid.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00d02440 - clear the world tree and read every world record from the
// stream, inserting it back into the tree.
// ---------------------------------------------------------------------------
// @ 0x00d02440
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

// ---------------------------------------------------------------------------
// 0x00d02570 - same string prologue as the writer above, but emits the world
// records through the script interface.
// ---------------------------------------------------------------------------
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
