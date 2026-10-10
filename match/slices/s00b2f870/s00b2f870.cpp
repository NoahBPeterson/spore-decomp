// Slice s00b2f870 - Simulator::cGameTerrainCursor and neighbours.
// Reconstructed from the Ghidra decompilation + disassembly. No assembly is transcribed.

extern "C" float sqrtf(float);

typedef void* (__thiscall *TCP0)(void*);
typedef void* (__thiscall *TCP1)(void*, int);
typedef void* (__thiscall *TCP2)(void*, int, int);
typedef int   (__thiscall *TCI0)(void*);
typedef int   (__thiscall *TCI1)(void*, int);
typedef int   (__thiscall *TCI2)(void*, int, int);
typedef void  (__thiscall *TCV0)(void*);
typedef void  (__thiscall *TCV1)(void*, int);
typedef void  (__thiscall *TCV2)(void*, int, int);
typedef void  (__thiscall *TCV3)(void*, int, int, int);
typedef int   (__thiscall *TCIp)(void*, void*);
typedef bool  (__thiscall *TCB)(void*);
typedef char  (__thiscall *TCC0)(void*);
#define VTO(o) (*(void***)(o))
#define SELOBJ(i) ((*(void***)(*(void***)((char*)this + 0x164)))[i])

// ---- globals addressed by absolute VA --------------------------------------
#define DAT_0167e7a4 (*(int**)0x0167e7a4u)
#define DAT_0167e898 (*(int**)0x0167e898u)
#define F_0167e770   (*(float*)0x0167e770u)
#define F_0167e76c   (*(float*)0x0167e76cu)
#define F_0167e768   (*(float*)0x0167e768u)
#define F_0167e74c   (*(float*)0x0167e74cu)
#define F_0167e774   (*(float*)0x0167e774u)
#define F_0167e778   (*(float*)0x0167e778u)
#define F_0167e77c   (*(float*)0x0167e77cu)
#define F_0167e7b4   (*(float*)0x0167e7b4u)
#define F_0167e7b8   (*(float*)0x0167e7b8u)
#define F_0167e7bc   (*(float*)0x0167e7bcu)

struct Vector3 { float x, y, z; };
struct Vector4 { float x, y, z, w; };

struct VarMap {
  void  SetVar(const char* name, float value);   // 0x007f25c0 (ret 8)
  float GetVar(const char* name);                // 0x007f2590 (ret 4)
};
#define g_VarMap ((VarMap*)0x0167e7e0u)

// ---- free helpers ----------------------------------------------------------
void* __cdecl FUN_0067ddc0();                    // 0x0067ddc0  ActiveCamera
void* __cdecl FUN_0067dcc0();                    // 0x0067dcc0  MessageServer
void* __cdecl FUN_0067d10();                     // 0x0067d10   App
void* __cdecl FUN_00b3d240();                    // 0x00b3d240
void* __cdecl FUN_00b3d280();                    // 0x00b3d280
void* __cdecl FUN_00b3d350();                    // 0x00b3d350  PlanetModel
void* __stdcall FUN_00b3d300(void*);             // 0x00b3d300  NounManager
void  __cdecl FUN_00b2fbe0();                    // 0x00b2fbe0
char  __stdcall FUN_00b301c0(int, void*);        // 0x00b301c0
void  __cdecl FUN_0093aa70(void*, void*, int, int);   // 0x0093aa70 EA::IO::WriteUint32
void  __cdecl FUN_0093a780(void*, void*, int, int);   // 0x0093a780 EA::IO::ReadInt32
void  __cdecl FUN_00409930();                    // 0x00409930 Transform_Ctor
void* __cdecl FUN_00fb8db0(void*);               // 0x00fb8db0

struct CVLS { char b[0xa00]; };                  // cVarListSerializer storage

struct S {
  // helper members (this-call, bodies supplied by the original; declared only)
  void* FUN_00c884f0(void*);                     // 0x00c884f0
  void* FUN_00b18460(void*);                     // 0x00b18460
  void  FUN_00c8a420();                          // 0x00c8a420
  void  FUN_00b184c0();                          // 0x00b184c0
  void  FUN_00b18660();                          // 0x00b18660  cGameData::cGameData
  void  FUN_00c89630();                          // 0x00c89630  cSpatialObject::cSpatialObject
  bool  FUN_00b18590(void*);                     // 0x00b18590  cGameData::Write
  bool  FUN_00b18600(void*);                     // 0x00b18600  cGameData::Read
  bool  FUN_00c88a90(void*);                     // 0x00c88a90  cSpatialObject::Write
  bool  FUN_00c88b00(void*);                     // 0x00c88b00
  void  FUN_00692f90(void*, int);                // 0x00692f90  cVarListSerializer::ctor
  bool  FUN_00692900(void*);                     // 0x00692900  cVarListSerializer::Serialize
  bool  FUN_00693e10(void*);                     // 0x00693e10  cVarListSerializer::Serialize
  void  FUN_00b0f240(void*, void*, void*);       // 0x00b0f240  InputHost::GetAnglesB
  void  FUN_00b22650();                          // 0x00b22650  RemoveNounsOfType
  void  FUN_007c40f0(void*);                     // 0x007c40f0
  void  FUN_007f20d0(const char*);               // 0x007f20d0
  void  FUN_008d2f30(void*, void*);              // 0x008d2f30
  int   FUN_00b3d240();                          // (unused placeholder)

  void FUN_00b2f870(void*);
  void* FUN_00b2fa00(void*);
  void FUN_00b2fa80(void*);
  void FUN_00b2fc60();
  void FUN_00b2fd90(void*);
  void FUN_00b2fdd0(void*);
  void FUN_00b2fe10(void*);
  void FUN_00b2fe90();
  int  FUN_00b2ff10();
  int  FUN_00b2ff20(void*);
  int  FUN_00b2ffb0();
  char FUN_00b30010(void*);
  char FUN_00b300c0(void*);
  void* FUN_00b30240();
  void FUN_00b30360();
  void FUN_00b303e0();
  void FUN_00b30550();
  void FUN_00b307e0(void*, void*);
};

// ---------------------------------------------------------------------------
// @ 0x00b2f870
// ---------------------------------------------------------------------------
void S::FUN_00b2f870(void* param_2) {
  void* piVar1 = FUN_0067ddc0();
  if (piVar1 == 0) return;
  if (((TCI0)(VTO(piVar1))[0x4c / 4])(piVar1) != *(int*)this) return;

  float* p = (float*)param_2;
  float f50 = p[0];
  float f4c = p[1];
  float f48 = p[2];
  float inv = 1.0f / sqrtf(f50 * f50 + f4c * f4c + f48 * f48 + 1e-8f);
  f50 = f50 * inv;
  f4c = f4c * inv;
  f48 = f48 * inv;
  ((TCV2)(VTO(piVar1))[0x38 / 4])(piVar1, (int)param_2, (int)&f50);

  void* app = FUN_0067d10();
  void* app2 = ((TCP0)(VTO(app))[0x50 / 4])(app);
  int* r = (int*)((TCP0)(VTO(app2))[0x1c / 4])(app2);
  if (r != 0) {
    FUN_00409930();
    ((S*)r)->FUN_007c40f0((void*)0);
    ((TCV1)(VTO(piVar1))[0x3c / 4])(piVar1, (int)&f50);
  }
  int* pm = (int*)FUN_00b3d350();
  void* sub = ((TCP0)(VTO(*(void**)((char*)pm + 0x24)))[0x10 / 4])(*(void**)((char*)pm + 0x24));
  FUN_00fb8db0(sub);
  ((TCV1)(VTO(piVar1))[0x30 / 4])(piVar1, (int)&f50);
  ((TCV0)(VTO(piVar1))[0x0c / 4])(piVar1);
}

// ---------------------------------------------------------------------------
// @ 0x00b2fa00  Object::Cast
// ---------------------------------------------------------------------------
void* S::FUN_00b2fa00(void* param_2) {
  if (param_2 != (void*)0x14a4edc) {
    void* r = ((S*)((char*)this + 0x34))->FUN_00c884f0(param_2);
    if (r == 0)
      r = ((S*)this)->FUN_00b18460(param_2);
    return r;
  }
  return this;
}

// ---------------------------------------------------------------------------
// @ 0x00b2fa80  Simulator::cGameTerrainCursor::SetAnchor
// ---------------------------------------------------------------------------
void S::FUN_00b2fa80(void* param_2) {
  *(Vector3*)((char*)this + 0x114) = *(Vector3*)param_2;
  *(char*)((char*)this + 0x160) = 1;
}

// ---------------------------------------------------------------------------
// @ 0x00b2fbe0
// ---------------------------------------------------------------------------
void __cdecl FUN_00b2fbe0() {
  if (DAT_0167e898 != 0) {
    void* ms = FUN_0067dcc0();
    ((TCV3)(VTO(ms))[0x2c / 4])(ms, (int)DAT_0167e898, 0x1a0219e, (int)0xffffd8f1u);
    int* p = DAT_0167e898;
    if (p != 0) {
      DAT_0167e898 = 0;
      ((TCV0)(VTO(p))[0x0c / 4])(p);
    }
  }
  if (DAT_0167e7a4 != 0) {
    void* nm = FUN_00b3d300((void*)0x18c40bc);
    ((S*)nm)->FUN_00b22650();
    int* p = DAT_0167e7a4;
    if (p != 0) {
      DAT_0167e7a4 = 0;
      ((TCV0)(VTO(p))[0x04 / 4])(p);
    }
  }
}

// ---------------------------------------------------------------------------
// @ 0x00b2fc60  cGameTerrainCursor destructor
// ---------------------------------------------------------------------------
void S::FUN_00b2fc60() {
  *(void**)this = (void*)0x145fff0;
  *(void**)((char*)this + 4) = (void*)0x145ffdc;
  *(void**)((char*)this + 0x34) = (void*)0x145ff18;

  int* p = DAT_0167e7a4;
  if (p == (int*)this && p != 0) {
    DAT_0167e7a4 = 0;
    ((TCV0)(VTO(p))[0x04 / 4])(p);
  }
  if (DAT_0167e898 != 0) {
    void* ms = FUN_0067dcc0();
    if (ms != 0)
      ((TCV3)(VTO(ms))[0x2c / 4])(ms, (int)DAT_0167e898, 0x1a0219e, (int)0xffffd8f1u);
  }
  void* o = *(void**)((char*)this + 0x168);
  if (o != 0)
    ((TCV0)(VTO(o))[0xc0 / 4])(o);
  ((S*)((char*)this + 0x34))->FUN_00c8a420();
  ((S*)this)->FUN_00b184c0();
}

// ---------------------------------------------------------------------------
// @ 0x00b2fd90
// ---------------------------------------------------------------------------
void S::FUN_00b2fd90(void* param_2) {
  int* p = (int*)param_2;
  *(int*)((char*)this + 0xd4) = p[0];
  *(int*)((char*)this + 0xd8) = p[1];
  *(int*)((char*)this + 0xdc) = p[2];
  void* o = *(void**)((char*)this + 0x134);
  if (o != 0)
    ((TCV1)(VTO(o))[0x38 / 4])(o, (int)param_2);
}

// ---------------------------------------------------------------------------
// @ 0x00b2fdd0
// ---------------------------------------------------------------------------
void S::FUN_00b2fdd0(void* param_2) {
  int* p = (int*)param_2;
  *(int*)((char*)this + 0x104) = p[0];
  *(int*)((char*)this + 0x108) = p[1];
  *(int*)((char*)this + 0x10c) = p[2];
  *(int*)((char*)this + 0x110) = p[3];
  void* o = *(void**)((char*)this + 0x134);
  if (o != 0)
    ((TCV1)(VTO(o))[0x3c / 4])(o, (int)param_2);
}

// ---------------------------------------------------------------------------
// @ 0x00b2fe10  funcD0h_
// ---------------------------------------------------------------------------
void S::FUN_00b2fe10(void* param_2) {
  void* old = *(void**)((char*)this + 0x168);
  if (param_2 != old) {
    if (param_2 != 0)
      ((TCV0)(VTO(param_2))[0xbc / 4])(param_2);
    *(void**)((char*)this + 0x168) = param_2;
    if (old != 0)
      ((TCV0)(VTO(old))[0xc0 / 4])(old);
  }
  if (param_2 != 0) {
    ((TCV1)(VTO(param_2))[0x38 / 4])(param_2, (int)((char*)this + 0x108));
    ((TCV1)(VTO(param_2))[0x3c / 4])(param_2, (int)((char*)this + 0x138));
  }
}

// ---------------------------------------------------------------------------
// @ 0x00b2fe90  func64h_
// ---------------------------------------------------------------------------
void S::FUN_00b2fe90() {
  bool anySel = false;
  void* mp = *(void**)((char*)this + 0x164);
  if (mp != 0) {
    unsigned n = (*(int*)((char*)mp + 4) - *(int*)mp) >> 2;
    for (unsigned i = 0; i < n; i++) {
      anySel = anySel || ((TCB)(VTO(SELOBJ(i)))[0x50 / 4])(SELOBJ(i));
      ((TCV1)(VTO(SELOBJ(i)))[0x54 / 4])(SELOBJ(i), 0);
    }
  }
  *(int*)((char*)this + 0x15c) = 0;
  if (anySel) {
    void* ms = FUN_0067dcc0();
    ((TCV3)(VTO(ms))[0x14 / 4])(ms, 0x52f1544, 0, 0);
  }
}

// ---------------------------------------------------------------------------
// @ 0x00b2ff10  GetObjectsCount
// ---------------------------------------------------------------------------
int S::FUN_00b2ff10() {
  int* p = *(int**)((char*)this + 0x164);
  return (*(int*)((char*)p + 4) - *(int*)p) >> 2;
}

// ---------------------------------------------------------------------------
// @ 0x00b2ff20  GetObjectTypeCount
// ---------------------------------------------------------------------------
int S::FUN_00b2ff20(void* param_2) {
  int count = 0;
  void* mp = *(void**)((char*)this + 0x164);
  if (mp != 0) {
    unsigned n = (*(int*)((char*)mp + 4) - *(int*)mp) >> 2;
    for (unsigned i = 0; i < n; i++) {
      if (((TCB)(VTO(SELOBJ(i)))[0x50 / 4])(SELOBJ(i))) {
        if (((TCIp)(VTO(SELOBJ(i)))[0xb8 / 4])(SELOBJ(i), param_2) != 0) count++;
      }
    }
  }
  return count;
}

// ---------------------------------------------------------------------------
// @ 0x00b2ffb0  UpdateSelectedObjectCount
// ---------------------------------------------------------------------------
int S::FUN_00b2ffb0() {
  *(int*)((char*)this + 0x15c) = 0;
  void* mp = *(void**)((char*)this + 0x164);
  if (mp != 0) {
    unsigned n = (*(int*)((char*)mp + 4) - *(int*)mp) >> 2;
    for (unsigned i = 0; i < n; i++) {
      void* o = SELOBJ(i);
      if (((TCB)(VTO(o))[0x50 / 4])(o))
        *(int*)((char*)this + 0x15c) += 1;
    }
  }
  return *(int*)((char*)this + 0x15c);
}

// ---------------------------------------------------------------------------
// @ 0x00b30010  ISimulatorSerializable::Write
// ---------------------------------------------------------------------------
char S::FUN_00b30010(void* param_2) {
  int* piVar4 = (int*)((TCP0)(VTO(param_2))[0x20 / 4])(param_2);
  void* local = (void*)0x14a4edc;
  void* uVar5 = ((TCP0)(VTO(piVar4))[0x18 / 4])(piVar4);
  FUN_0093aa70(uVar5, &local, 1, 0);
  char cVar2 = ((S*)this)->FUN_00b18590(param_2);
  char cVar3 = ((S*)((char*)this + 0x34))->FUN_00c88a90(param_2);
  bool bv = !(cVar3 == 0 || cVar2 == 0);

  CVLS cvs;
  ((S*)&cvs)->FUN_00692f90(this, 0x1a80d26);
  char cVar4 = ((S*)&cvs)->FUN_00692900(param_2);
  (void)0x1568e18;
  if (cVar4 != 0 && bv) return 1;
  return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00b300c0  ISimulatorSerializable::Read
// ---------------------------------------------------------------------------
char S::FUN_00b300c0(void* param_2) {
  int* piVar5 = (int*)((TCP0)(VTO(param_2))[0x20 / 4])(param_2);
  int local = 0;
  void* uVar6 = ((TCP0)(VTO(piVar5))[0x18 / 4])(piVar5);
  FUN_0093a780(uVar6, &local, 1, 0);
  char cVar3 = ((S*)this)->FUN_00b18600(param_2);
  char cVar4 = ((S*)((char*)this + 0x34))->FUN_00c88b00(param_2);
  bool bv = !(cVar4 == 0 || cVar3 == 0);

  CVLS cvs;
  ((S*)&cvs)->FUN_00692f90(this, 0x1a80d26);
  char cVar5 = ((S*)&cvs)->FUN_00693e10(param_2);
  (void)0x1568e18;
  int* prev = DAT_0167e7a4;
  bool ok = !(cVar5 == 0 || !bv);
  if ((void*)this != (void*)DAT_0167e7a4) {
    if (this != 0)
      ((TCV0)(VTO(this))[0x0c / 4])(this);   // AddRef
    DAT_0167e7a4 = (int*)this;
    if (prev != 0)
      ((TCV0)(VTO(prev))[0x04 / 4])(prev);   // Release
  }
  return ok ? 1 : 0;
}

// ---------------------------------------------------------------------------
// @ 0x00b301c0
// ---------------------------------------------------------------------------
char __stdcall FUN_00b301c0(int param_1, void* param_2) {
  if (param_1 == 0x1a0219e && *(int*)((char*)param_2 + 8) == 0) {
    void* nm = FUN_00b3d300((void*)0x18c40bc);
    ((S*)nm)->FUN_00b22650();
    int* p = DAT_0167e7a4;
    if (p != 0) {
      DAT_0167e7a4 = 0;
      ((TCV0)(VTO(p))[0x04 / 4])(p);
    }
  }
  return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00b30240  Simulator::cGameTerrainCursor::cGameTerrainCursor
// ---------------------------------------------------------------------------
void* S::FUN_00b30240() {
  ((S*)this)->FUN_00b18660();
  ((S*)((char*)this + 0x34))->FUN_00c89630();

  *(void**)this = (void*)0x145fff0;
  *(void**)((char*)this + 4) = (void*)0x145ffdc;
  *(void**)((char*)this + 0x34) = (void*)0x145ff18;

  *(float*)((char*)this + 0x108) = 0.0f;
  *(float*)((char*)this + 0x10c) = 0.0f;
  *(float*)((char*)this + 0x110) = 0.0f;
  *(float*)((char*)this + 0x114) = 0.0f;
  *(float*)((char*)this + 0x118) = 0.0f;
  *(float*)((char*)this + 0x11c) = 0.0f;
  *(float*)((char*)this + 0x120) = 0.0f;
  *(float*)((char*)this + 0x124) = 0.0f;
  *(float*)((char*)this + 0x128) = 0.0f;
  *(float*)((char*)this + 0x12c) = 0.0f;
  *(float*)((char*)this + 0x130) = 0.0f;
  *(float*)((char*)this + 0x134) = 0.0f;
  *(float*)((char*)this + 0x138) = 0.0f;
  *(float*)((char*)this + 0x13c) = 0.0f;
  *(float*)((char*)this + 0x140) = 0.0f;
  *(float*)((char*)this + 0x144) = 1.0f;
  *(int*)((char*)this + 0x154) = 0;
  *(char*)((char*)this + 0x158) = 0;
  *(char*)((char*)this + 0x159) = 0;
  *(int*)((char*)this + 0x15c) = 0;
  *(char*)((char*)this + 0x160) = 0;
  *(int*)((char*)this + 0x164) = 0;
  *(float*)((char*)this + 0x148) = 1.0f;
  *(float*)((char*)this + 0x14c) = 1.0f;
  *(char*)((char*)this + 0x150) = 1;
  *(char*)((char*)this + 0x15a) = 1;
  *(int*)((char*)this + 0x168) = 0;
  return this;
}

// ---------------------------------------------------------------------------
// @ 0x00b30360  ResetAnchors
// ---------------------------------------------------------------------------
void S::FUN_00b30360() {
  if (*(char*)((char*)this + 0x150) != 0)
    ((TCV2)(VTO(this))[0x7c / 4])(this, 1, 0);
  Vector3 zero = { 0.0f, 0.0f, 0.0f };
  *(Vector3*)((char*)this + 0x12c) = zero;
  *(Vector3*)((char*)this + 0x120) = zero;
  *(Vector3*)((char*)this + 0x114) = zero;
  *(char*)((char*)this + 0x160) = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00b303e0  UpdateSelectedObjects
// ---------------------------------------------------------------------------
void S::FUN_00b303e0() {
  void* mp = *(void**)((char*)this + 0x164);
  if (mp == 0) {
    ((TCV0)(VTO(this))[0x70 / 4])(this);
    return;
  }
  float radius = *(float*)((char*)this + 0x148) + 0.2f;
  Vector3 origin;
  ((TCV1)(VTO((char*)this + 0x34))[0x2c / 4])((char*)this + 0x34, (int)&origin);
  float rsq = radius * radius;

  bool touched = false;
  int* begin = *(int**)mp;
  int* end = (int*)*((int**)mp + 1);
  for (int* it = begin; it != end; it++) {
    void* o = (void*)*it;
    if (!((TCB)(VTO(o))[0x50 / 4])(o)) {
      Vector3 pos;
      ((TCV1)(VTO(o))[0x2c / 4])(o, (int)&pos);
      float dz = pos.z - origin.z;
      float dy = pos.y - origin.y;
      float dx = pos.x - origin.x;
      if ((dz * dz + dy * dy) + dx * dx < rsq) {
        ((TCV1)(VTO(o))[0x54 / 4])(o, 1);
        touched = true;
        int* col = (int*)FUN_00b3d240();
        Vector3 gp;
        ((TCV1)(VTO(o))[0x2c / 4])(o, (int)&gp);
        ((TCV2)(VTO(*(void**)col))[0x60 / 4])(col, 0x903427bf, (int)&gp);
      }
    }
  }
  if (touched) {
    ((TCV0)(VTO(this))[0x74 / 4])(this);
    ((TCV0)(VTO(this))[0xc8 / 4])(this);
    void* ms = FUN_0067dcc0();
    ((TCV3)(VTO(ms))[0x14 / 4])(ms, 0x52f1544, 0, 0);
  }
  ((TCV0)(VTO(this))[0x70 / 4])(this);
}

// ---------------------------------------------------------------------------
// @ 0x00b30550  funcC8h_
// ---------------------------------------------------------------------------
void S::FUN_00b30550() {
  int* piVar4 = (int*)FUN_00b3d240();
  float vx = F_0167e774, vy = F_0167e778, vz = F_0167e77c;
  Vector3 out;
  ((TCV1)(VTO(piVar4))[0x38 / 4])(piVar4, (int)&out);
  float d2 = out.x * out.x + out.y * out.y + out.z * out.z;
  if (d2 <= *(float*)0x01485378u) return;

  int sel = ((TCI0)(VTO(this))[0x70 / 4])(this);
  float fsel = (float)sel;
  float dx = out.x - F_0167e7b4;
  F_0167e7b4 = out.x;
  float dy = out.y - F_0167e7b8;
  F_0167e7b8 = out.y;
  float dz = out.z - F_0167e7bc;
  F_0167e7bc = out.z;
  F_0167e770 = sqrtf((dz * dz + dy * dy) + dx * dx) + F_0167e770;

  // elapsed time (seconds) since the selection timer started
  long long t = 0;   // placeholder captured by GetElapsedTime at a fixed address
  float secs = (float)(t & 0x7fffffffffffffffULL) * 0.001f;

  float zx = 0.0f, zy = 0.0f;
  Vector3 dummy;
  ((S*)&dummy)->FUN_008d2f30(&zx, (void*)&vy);
  float ax = (float)((int)vx - *(int*)0x0167e76cu);
  float ay = (float)((int)vy - *(int*)0x0167e768u);
  float dist = (float)((int)ax * (int)ax) + (float)((int)ay * (int)ay);

  g_VarMap->SetVar("num_selected_creatures", fsel);
  g_VarMap->SetVar("total_cursor_travel_distance", F_0167e770);
  g_VarMap->SetVar("total_selection_time", secs);
  g_VarMap->SetVar("cursor_distance_from_start", sqrtf(dist));
  ((S*)g_VarMap)->FUN_007f20d0("tune_selection_cursor");

  void* cam = FUN_00b3d280();
  if (cam == 0) return;
  float a0, a1, a2;
  ((S*)cam)->FUN_00b0f240(&a0, &a1, &a2);
  g_VarMap->SetVar("camera_zoom_distance", a2);
  float cr = g_VarMap->GetVar("cursor_radius");
  if (cr < 1.0f) cr = 1.0f;
  float alpha = g_VarMap->GetVar("alpha");
  ((TCV1)(VTO(this))[0xac / 4])(this, (int)&cr);
  ((TCV1)(VTO(this))[0xb0 / 4])(this, (int)&alpha);
}

// ---------------------------------------------------------------------------
// @ 0x00b307e0  func80h_
// ---------------------------------------------------------------------------
void S::FUN_00b307e0(void* param_2, void* param_3) {
  int* arr = (int*)param_2;
  int* p = (int*)arr[0];
  int* end = (int*)arr[1];
  char touched = *(char*)&param_3;
  bool anyTouched = false;
  void* self = this;
  for (; p != end; p++) {
    void* mp = *(void**)((char*)self + 0x164);
    int* b = *(int**)mp;
    int* e = (int*)*((int**)mp + 1);
    void* obj = (void*)*p;
    int* it = b;
    while (it != e && (void*)*it != obj) it++;
    if (it == e) continue;
    if (touched) {
      bool sel = ((TCB)(VTO(obj))[0x50 / 4])(obj);
      anyTouched = true;
      ((TCV1)(VTO(obj))[0x54 / 4])(obj, !sel);
    } else {
      if (!anyTouched) {
        bool sel = ((TCB)(VTO(obj))[0x50 / 4])(obj);
        if (sel) {
          anyTouched = true;
          ((TCV1)(VTO(obj))[0x54 / 4])(obj, 1);
        } else {
          ((TCV1)(VTO(obj))[0x54 / 4])(obj, 1);
        }
      } else {
        ((TCV1)(VTO(obj))[0x54 / 4])(obj, 1);
      }
    }
    int* col = (int*)FUN_00b3d240();
    Vector3 gp;
    ((TCV1)(VTO(obj))[0x2c / 4])(obj, (int)&gp);
    ((TCV2)(VTO(*(void**)col))[0x60 / 4])(col, 0x903427bf, (int)&gp);
  }
  ((TCV0)(VTO(self))[0x74 / 4])(self);
  if (anyTouched) {
    void* ms = FUN_0067dcc0();
    ((TCV3)(VTO(ms))[0x14 / 4])(ms, 0x52f1544, 0, 0);
  }
  *(char*)&param_3 = touched;
}
