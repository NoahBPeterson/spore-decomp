// Slice s01005800 (batch gold6, worker 44). Region 0x01005800-0x010066e0.
// SP::cSPSimulatorSpaceGame satellite cluster: planet/tool refresh helpers
// (FUN_01005800, FUN_01005d80), a property getter (FUN_01005c60), the
// cSPSimulatorSpaceGame::ConfigUpdated listener, eastl vector/string move
// helpers, and the cSPSimulatorSpaceGame constructor (FUN_010066e0).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;
typedef          short s16;
typedef          char  s8;

// ---- external callees (address in comment) ------------------------------
void* __cdecl operator_new(u32 size, const char* file, int, int, int, int); // 0xf473a0
void  __cdecl operator_delete_(void*);                                      // 0xf47380
void  __cdecl operator_delete_array(void*);                                 // 0xf47380
void* __cdecl SP_PropertyManager();            // 0x0067de30 SP::PropertyManager()
void* __cdecl SP_NounManager();                // 0x00b3d300 SP::NounManager()
void* __cdecl SP_GetUFOSimulator();            // 0x00ffbe50 SP::GetUFOSimulator()
void* __cdecl SP_PlanetModel();                // 0x00b3d350 SP::PlanetModel()
void* __cdecl SP_GetActivePlanet();            // 0x01021260 ?FUN_01021260@@YAPAXXZ
void* __cdecl SP_GetUFOSim_2();                // 0x01021300 ?FUN_01021300@@YAPAXXZ
void* __cdecl FUN_00b5b6c0(void* self);        // 0x00b5b6c0 cGonzagoSimulator ctor
void* __cdecl FUN_00b63890(void* self);        // 0x00b63890 cGonzagoTimer ctor
void  __cdecl FUN_00bc30f0(void* self);        // 0x00bc30f0 cSPTimer::Start
void* __cdecl FUN_00fe68a0(void* self);        // 0x00fe68a0 (sub-object ctor)
// All four are __thiscall (this in ecx, no stack args).
static void* TC_b5b6c0(void* s){ return ((void*(__thiscall*)(void*))FUN_00b5b6c0)(s); }
static void* TC_b63890(void* s){ return ((void*(__thiscall*)(void*))FUN_00b63890)(s); }
static void  TC_bc30f0(void* s){ ((void(__thiscall*)(void*))FUN_00bc30f0)(s); }
static void* TC_fe68a0(void* s){ return ((void*(__thiscall*)(void*))FUN_00fe68a0)(s); }
void* __cdecl FUN_00760c00(void* self);        // 0x00760c00 (sub-object ctor)
void* __cdecl FUN_00b60070(void* self);        // 0x00b60070 (sub-object ctor)
void  __cdecl FUN_0061df40(void*);             // 0x0061df40 AutoRefCount ctor
void* __cdecl FUN_00572660(void* dst, void* src); // 0x00572660 AutoRefCount ctor
void* __cdecl FUN_00ac9480(void* dst, void* src); // 0x00ac9480 AutoRefCount ctor
void* __cdecl FUN_00454cb0(void* dst, void* src); // 0x00454cb0 eastl string assign (2-arg form)
// Real ABI: string::assign(this=dst, begin, end) -> ecx=dst, two stack args.
static void StrAssign(void* self, void* begin, void* end) {
  ((void(__thiscall*)(void*, void*, void*))FUN_00454cb0)(self, begin, end);
}
void  __cdecl FUN_00475ab0(void* self, u32 n);    // 0x00475ab0 eastl string RangeInitialize (this=+0, n on stack)
void* __cdecl memcpy(void* dst, const void* src, u32 n); // 0x011e0744 memcpy
void* __cdecl FUN_0067dd50();                  // 0x0067dd50 singleton
void* __cdecl FUN_0067dd60();                  // 0x0067dd60 singleton
void* __cdecl FUN_0067ddb0();                  // 0x0067ddb0 singleton
void* __cdecl FUN_0067cab0();                  // 0x0067cab0 singleton
void* __cdecl FUN_00675250(u32 id);            // 0x00675250 Achievements::Controller()
bool  __cdecl FUN_00675e80(void* self, u32 id);// 0x00675e80 Achievement has-check
void  __cdecl FUN_00676710(void* self, u32 id);// 0x00676710 AwardAchievement
void* __cdecl FUN_00556440(void*, void*, void*, void*); // 0x00556440
void  __cdecl FUN_00c75cc0(u32, void*);        // 0x00c75cc0
void  __cdecl FUN_00e39ab0(u32, u32, void*, void*, u32, u32, void*, void*); // 0x00e39ab0
bool  __cdecl FUN_00685520(int);               // 0x00685520 IsWorldLayoutFlagSet
void* __cdecl FUN_00fd9c60();                  // 0x00fd9c60
void  __cdecl FUN_00fde3e0(void* self);        // 0x00fde3e0 TransitionFromPlanetToSolar
void  __cdecl FUN_00fdbf90(void* self);        // 0x00fdbf90 AwardSpaceAchievements
void  __cdecl FUN_00801360(void* self);        // 0x00801360 Show
void  __cdecl FUN_00801380(void* self);        // 0x00801380 Hide
bool  __cdecl FUN_01044920();                  // 0x01044920
bool  __cdecl FUN_00ffc5b0(void* self);        // 0x00ffc5b0
void  __cdecl FUN_00b7daf0(void* self);        // 0x00b7daf0
void* __cdecl FUN_00b3d360(void* p);           // 0x00b3d360
float __cdecl FUN_00b7e4d0(void* self);        // 0x00b7e4d0
float __cdecl FUN_00ffda80(void* self);        // 0x00ffda80 CalculateMaxEnergy
float __cdecl FUN_00ffd8e0(void* self);        // 0x00ffd8e0 CalculateMaxHealth
void* __cdecl FUN_00c30c80(void* self);        // 0x00c30c80
void* __cdecl FUN_00c707e0(void* self);        // 0x00c707e0 cPlanet::GetName
void* __cdecl FUN_00b3d390(void* a, void* b);  // 0x00b3d390 vector::erase
bool  __cdecl FUN_0104e340(void* self, u32 id); // 0x0104e340 CreateToolFromToolID
void* __cdecl FUN_00f67d90(void* self);        // 0x00f67d90 GetCurrentTerrainSphere
void* __cdecl FUN_00555e80(void* a, void* b);  // 0x00555e80 vector append
void  __cdecl FUN_00760fd0(void* self, u32 a, u32 b, u32 c); // 0x00760fd0 listener add
void* __cdecl FUN_00576650_(void* a, void* b); // 0x00576650 GetImageResource
void* __cdecl FUN_00576440(void* a, void* b, void* c, void* d); // 0x00556440
void* __cdecl FUN_00576650(void* self, void* a); // 0x00576650 GetImageResource
void* __cdecl FUN_0093c570(void* a, void* b);  // 0x0093c570 EA::ConvertToString8
void* __cdecl FUN_00ac9480b(void* a);          // 0x00ac9480 (1-arg variant)
void* __cdecl FUN_00e39ab0b(void* a, void* b, void* c, void* d, void* e, void* f, void* g, void* h);
void* __cdecl FUN_01021260();                  // 0x01021260 ?FUN_01021260@@YAPAXXZ
void* __cdecl FUN_01021300();                  // 0x01021300 ?FUN_01021300@@YAPAXXZ
void* __cdecl FUN_01021260b();

// Member helpers on other classes (vtable thunks handled inline).
void* __cdecl FUN_0040cf10(u32 a, u32 b, void* out); // 0x0040cf10 SP::GetPropertyT<int>
void* __cdecl FUN_0041ea70();                  // 0x0041ea70 Property::GetFloat

// ---- globals (named via typed accessors) -------------------------------
extern u32 DAT_016dc648, DAT_016dc64c, DAT_016dc650, DAT_016dc654, DAT_016dc658,
    DAT_016dc65c, DAT_016dc660, DAT_016dc664, DAT_016dc668, DAT_016dc66c,
    DAT_016dc670, DAT_016dc674, DAT_016dc678, DAT_016dc67c, DAT_016dc680,
    DAT_016dc684, DAT_016dc688, DAT_016dc68c, DAT_016dc690, DAT_016dc694,
    DAT_016dc698, DAT_016dc69c, DAT_016dc6a0, DAT_016dc6a4, DAT_016dc6a8,
    DAT_016dc6ac, DAT_016dc6b0;
extern u32 DAT_016dc794;      // initialised flag
extern u32 DAT_016dc728[30];  // 10 tool ids * 3 u32 = 0x78 bytes
extern float DAT_01485720;    // _HK_REAL_ONE = 1.0f
extern float DAT_01495378;    // degrees->radians

// ======================================================================
// FUN_01005800 - refresh the active planet's tool tray from the terrain
// sphere's tool-id list; `this` in ecx (thiscall). Writes a u32 tool-flag
// word at +0xc4. Register-arg static helper; equivalence-only.
// ======================================================================

// @ 0x01005800
void __fastcall FUN_01005800(void* self, void* /*edx*/, void* outVec) {
  char* p = (char*)self;
  // vector accumulators: local_14/10/c are the begin/end/cap of a u32 vector
  u32* vecBegin = 0;
  u32  vecEnd   = 0;
  u32  vecCap   = 0;

  if ((DAT_016dc794 & 1) == 0) {
    DAT_016dc794 |= 1;
    DAT_016dc728[0]  = DAT_016dc648;  DAT_016dc728[1]  = DAT_016dc64c;
    DAT_016dc728[2]  = DAT_016dc650;  DAT_016dc728[3]  = DAT_016dc654;
    DAT_016dc728[4]  = DAT_016dc658;  DAT_016dc728[5]  = DAT_016dc65c;
    DAT_016dc728[6]  = DAT_016dc660;  DAT_016dc728[7]  = DAT_016dc664;
    DAT_016dc728[8]  = DAT_016dc668;  DAT_016dc728[9]  = DAT_016dc66c;
    DAT_016dc728[10] = DAT_016dc670;  DAT_016dc728[11] = DAT_016dc674;
    DAT_016dc728[12] = DAT_016dc678;  DAT_016dc728[13] = DAT_016dc67c;
    DAT_016dc728[14] = DAT_016dc680;  DAT_016dc728[15] = DAT_016dc684;
    DAT_016dc728[16] = DAT_016dc688;  DAT_016dc728[17] = DAT_016dc68c;
    DAT_016dc728[18] = DAT_016dc690;  DAT_016dc728[19] = DAT_016dc694;
    DAT_016dc728[20] = DAT_016dc698;  DAT_016dc728[21] = DAT_016dc69c;
    DAT_016dc728[22] = DAT_016dc6a0;  DAT_016dc728[23] = DAT_016dc6a4;
    DAT_016dc728[24] = DAT_016dc6a8;  DAT_016dc728[25] = DAT_016dc6ac;
    DAT_016dc728[26] = DAT_016dc6b0;
  }

  char* sphere = (char*)FUN_00f67d90(SP_NounManager());
  u32* sf = (u32*)sphere;
  FUN_00555e80((void*)sf[0x10fc / 4], &vecBegin);
  FUN_00555e80((void*)sf[0x1100 / 4], &vecBegin);
  FUN_00555e80((void*)sf[0x1104 / 4], &vecBegin);
  FUN_00555e80((void*)sf[0x1108 / 4], &vecBegin);
  FUN_00555e80((void*)sf[0x110c / 4], &vecBegin);

  s32 n = (s32)(vecEnd - (u32)vecBegin) >> 2;
  s32 i = 0;
  *(u32*)(p + 0xc4) = 0;
  s32 cur = -1;
  if (n > 0) {
    s32 prev = cur;
    do {
      u32 id = vecBegin[i];
      cur = prev;
      switch (id) {
      case 0x9afd99c1: cur = 1; break;
      case 0x92d11083: *(u32*)(p + 0xc4) |= 8;    break;
      case 0xa08d482a: *(u32*)(p + 0xc4) |= 0x200; break;
      case 0xa7b3defa: *(u32*)(p + 0xc4) |= 0x10; break;
      case 0xb27471c6: *(u32*)(p + 0xc4) |= 0x40; break;
      case 0xbce4ad98: cur = 2; break;
      case 0xcf7f7780: *(u32*)(p + 0xc4) |= 0x800; break;
      case 0xd6b2c7f0: *(u32*)(p + 0xc4) |= 2;   break;
      case 0xed489b99: cur = 7; break;
      case 0xf0db6039: *(u32*)(p + 0xc4) |= 4;   break;
      case 0xf42be530: *(u32*)(p + 0xc4) |= 0x100; break;
      case 0x496d884f: *(u32*)(p + 0xc4) |= 0x80;  break;
      case 0x0d7dbbe1: cur = 4; break;
      case 0x0b7b9820: cur = 0; break;
      case 0x0bc14e8f: *(u32*)(p + 0xc4) |= 0x20;  break;
      case 0x2ac5df1f: cur = 6; break;
      case 0x46aff0dc: *(u32*)(p + 0xc4) |= 0x400; break;
      case 0x69073562: cur = 3; break;
      case 0x622280f4: cur = 8; break;
      case 0x629ee549: cur = 5; break;
      case 0x714e0388: *(u32*)(p + 0xc4) |= 1;     break;
      default: break;
      }
      i++;
      prev = cur;
    } while (i < n);
  }

  // Rebuild the tool tray: clear each of the 10 slots, then create the tool.
  u32* slot = DAT_016dc728;
  s32 k = 10;
  do {
    void* mgr = *(void**)(p + 0x40);
    void* existing = ((void*(__thiscall*)(void*, u32*))(*(void***)mgr)[0x68 / 4])(mgr, slot);
    if (existing != 0) {
      ((void(__thiscall*)(void*, void*))(*(void***)mgr)[0x78 / 4])(mgr, existing);
    }
    slot += 3;
  } while (--k != 0);

  if (cur != -1) {
    void* erased;
    u32* dstSlot = &DAT_016dc728[cur * 3];
    erased = FUN_00b3d390(dstSlot, &outVec);              // vector::erase
    void* toolmgr = (void*)((char*)p + 0x40);
    (void)toolmgr;
    FUN_0104e340(p + 0x40, (u32)erased);                  // CreateToolFromToolID
    void* tok = outVec;
    if (tok != 0) {
      void* mgr = *(void**)(p + 0x40);
      ((void(__thiscall*)(void*, void*, int, int))(*(void***)mgr)[0x80 / 4])(mgr, tok, 0, 1);
      if (tok != 0) {
        ((void(__thiscall*)(void*))(*(void***)tok)[8 / 4])(tok);
      }
    }
  }

  if (FUN_00685520(2)) {
    void* u = FUN_00fd9c60();
    FUN_00fdbf90(u);
  }
  {
    void* u = SP_GetUFOSimulator();
    float e = FUN_00ffda80(u);
    (void)e;
  }
  {
    void* u = SP_GetUFOSimulator();
    float h = FUN_00ffd8e0(u);
    (void)h;
  }

  if (vecBegin != 0 && *(u32*)((char*)vecBegin - 4) != 0) {
    operator_delete_(vecBegin);
  }
}

// ======================================================================
// FUN_01005c60 - property getter returning a float; `ret 4` (one stack arg
// passed on the caller's stack). Reads PropertyManager().GetPropertyT<int>()
// with per-value property-id selectors and returns it as a float.
// ======================================================================

// @ 0x01005c60
float __stdcall FUN_01005c60(u32 selector) {
  void* pm = SP_PropertyManager();
  void* holder = 0;
  {
    void* mgr = pm;
    ((void(__thiscall*)(void*, u32, u32, void**))(*(void***)mgr)[0x2c / 4])(
        mgr, 0x8da597e4, 0x2ae0c7e, &holder);
  }
  u32 propId;
  switch (selector) {
  case 0x3:  propId = 0x2f5c9502; break;
  case 0x0:  propId = 0xdc13b0ec; break;
  case 0xa:  propId = 0x7492aef4; break;
  case 0x1: case 0x2: case 0x6: case 0x8:
             propId = 0xee6cc96d; break;
  case 0x5:  propId = 0x97b7d5cb; break;
  case 0x9:  propId = 0x2da66ec8; break;
  case 0xb:  propId = 0x7c945213; break;
  default:   goto done;
  }
  {
    float value = 1.0f;
    FUN_0040cf10(0x2ae0c7e, propId, &value);
    (void)value;
  }
done:
  if (holder != 0) {
    ((void(__thiscall*)(void*))(*(void***)holder)[4 / 4])(holder);
  }
  return DAT_01485720;
}

// ======================================================================
// FUN_01005d80 - award planet achievements after a tool/planet change;
// `this` in ecx, two stack args (char flag, u32 param). `ret 8`.
// ======================================================================

// @ 0x01005d80
void __fastcall FUN_01005d80(void* /*ecx*/, void* /*edx*/, u8 flag, u32 param) {
  FUN_00c30c80(FUN_01021300());
  void* sphere = (void*)FUN_00f67d90(SP_NounManager());
  u32* sf = (u32*)sphere;

  u32 handle;
  if (flag == 0) {
    handle = sf[0x110c / 4];
  } else {
    handle = (u32)FUN_00556440((void*)sf[0x10fc / 4], (void*)sf[0x1100 / 4],
                               (void*)sf[0x1104 / 4], (void*)sf[0x1108 / 4]);
  }

  u32 awardId = 0;
  u32 eventId = 0;
  u32 counter = param;
  if (handle != 0) {
    FUN_00c75cc0(0x2db6dad3, (void*)handle);
    u32 tier = 0x11;
    switch (handle) {
    case 0x0d832b059: break;
    case 0xa6cb4c9f: tier = 0xc; awardId = 0x7afcb267; eventId = 0xa6cb4c9f; break;
    case 0x7bceaa86: tier = 0x10; awardId = 0xda2fec0e; eventId = 0x7bceaa86; break;
    case 0x6cd9ec7b: awardId = 0xae94ffe3; eventId = 0x6cd9ec7b; break;
    case 0xcdb3696f: tier = 0xf; awardId = 0x59bf4bc7; eventId = 0xcdb3696f; break;
    case 0xd536c91d: tier = 10; awardId = 0x23752db5; eventId = 0xd536c91d; break;
    case 0x980e43f2: tier = 0x12; awardId = 0x5ae3a08a; eventId = 0x980e43f2; break;
    case 0xe0bc9d45: tier = 9;  awardId = 0x2b54d82d; eventId = 0xe0bc9d45; break;
    case 0xa0973374: tier = 0xe; awardId = 0xcb7d6d3c; eventId = 0xa0973374; break;
    case 0x5fcf28d0: tier = 0xd; awardId = 0x7d7b59e8; eventId = 0x5fcf28d0; break;
    default: eventId = 0; break;
    }
    (void)eventId;
    FUN_01021300();  // player empire accessor (logged value unused here)
    *(u32*)((char*)SP_GetActivePlanet() + 0x58) = tier;

    if (flag != 0) {
      void* ctrl = FUN_00675250(awardId);
      FUN_00676710(ctrl, awardId);
      u32 scratch[12] = {0};
      FUN_00e39ab0(counter, 0, &scratch[3], &scratch[0], 0, 0, &scratch[6], &scratch[9]);
      static const u32 chain[] = {
          0x7d7b59e8, 0xda2fec0e, 0xcb7d6d3c, 0x59bf4bc7, 0x3e06ba31,
          0x23752db5, 0x7afcb267, 0x2b54d82d, 0xae94ffe3, 0x5ae3a08a };
      for (u32 ci = 0; ci < 10; ci++) {
        void* c = FUN_00675250(chain[ci]);
        if (!FUN_00675e80(c, chain[ci])) return;
      }
      void* c = FUN_00675250(0x99bb05bb);
      FUN_00676710(c, 0x99bb05bb);
    }
  }

  FUN_01005800(0, 0, (void*)0);
  (void)param;

  if (flag != 0) {
    void* s2 = (void*)FUN_00f67d90(SP_NounManager());
    u32* s2f = (u32*)s2;
    if (s2f[0x10fc / 4] != 0 && s2f[0x1100 / 4] != 0 &&
        s2f[0x1104 / 4] != 0 && s2f[0x1108 / 4] != 0) {
      void* c = FUN_00675250(0xaf2819b8);
      FUN_00676710(c, 0xaf2819b8);
    }
  }
}

// ======================================================================
// SP::cSPSimulatorSpaceGame::ConfigUpdated - reload config values from the
// PropertyManager. `this` in ecx, no stack args.
// Named fields on the retail layout:
//   +0x34 float mfContextSwitchTimer.mTime;
//   +0x38 float mSpaceUI.mValue;
//   +0x3c float mRaresUI.mRotation (degrees -> radians).
// ======================================================================

// @ 0x010060d0
void __fastcall SP_cSPSimulatorSpaceGame_ConfigUpdated(void* self, void* /*edx*/) {
  char* p = (char*)self;
  void* holder = 0;
  void* pm = SP_PropertyManager();
  void* pmv = pm;
  if (holder != 0) {
    holder = 0;
    ((void(__thiscall*)(void*))(*(void***)pmv)[4 / 4])(pmv);
  }
  ((void(__thiscall*)(void*, u32, u32, void**))(*(void***)pmv)[0x2c / 4])(
      pmv, 0x521d0174, 0x2ae0c7e, &holder);

  if (holder != 0) {
    // float property 0x5820b5e -> mContextSwitchTimer.mTime (+0x34)
    if (((bool(__thiscall*)(void*, u32, void**))(*(void***)holder)[0x24 / 4])(holder, 0x5820b5e, (void**)(p + 0x34))) {
      u32* prop = *(u32**)(p + 0x34);
      if (prop != 0 && ((u16*)prop)[9] == 0xd) {
        void* fv = FUN_0041ea70();
        (void)fv;
      }
    }
    // float property 0x5820b65 -> mSpaceUI.mValue (+0x38)
    if (((bool(__thiscall*)(void*, u32, void**))(*(void***)holder)[0x24 / 4])(holder, 0x5820b65, (void**)(p + 0x38))) {
      u32* prop = *(u32**)(p + 0x38);
      if (prop != 0 && ((u16*)prop)[9] == 0xd) {
        void* fv = FUN_0041ea70();
        (void)fv;
      }
    }
    *(float*)(p + 0x3c) = 1.0f;
    // float property 0x195a065 -> mRaresUI.mRotation (+0x3c)
    if (((bool(__thiscall*)(void*, u32, void**))(*(void***)holder)[0x24 / 4])(holder, 0x195a065, (void**)(p + 0x3c))) {
      u32* prop = *(u32**)(p + 0x3c);
      if (prop != 0 && ((u16*)prop)[9] == 0xd) {
        void* fv = FUN_0041ea70();
        (void)fv;
      }
    }
    *(float*)(p + 0x3c) = *(float*)(p + 0x3c) * DAT_01495378;
    if (holder != 0) {
      ((void(__thiscall*)(void*))(*(void***)holder)[4 / 4])(holder);
    }
  }
}

// ======================================================================
// eastl vector/string move helpers (0x1c-byte elements:
// eastl::basic_string<char> + 3 scalars).
// ======================================================================

// @ 0x01006280
void* __cdecl FUN_01006280(char* first, char* last, char* dst) {
  while (first != last) {
    if (first != dst) {
      StrAssign(dst, *(void**)first, *(void**)(first + 4));
    }
    *(u32*)(dst + 0x10) = *(u32*)(first + 0x10);
    *(float*)(dst + 0x14) = *(float*)(first + 0x14);
    *(u32*)(dst + 0x18) = *(u32*)(first + 0x18);
    first += 0x1c;
    dst   += 0x1c;
  }
  return dst;
}

// @ 0x010062d0
void __cdecl FUN_010062d0(char* first, char* last, char* dst) {
  while (first != last) {
    if (dst != 0) {
      *(u32*)(dst + 4) = 0x013ec458;   // ??_7ContentValidationSummarizer@@6B@
      *(u32*)(dst + 8) = 0;
      *(u32*)(dst + 0) = 0x01495400;
      *(u32*)(dst + 4) = 0x0149bad8;
      *(u32*)(dst + 0xc)  = *(u32*)(first + 0xc);
      *(u32*)(dst + 0x10) = *(u32*)(first + 0x10);
    }
    first += 0x14;
    dst   += 0x14;
  }
}

// @ 0x01006320
void* __cdecl FUN_01006320(char* first, char* last, char* dst) {
  if (last == first) return dst;
  char* si = last;
  char* di = dst;
  do {
    si -= 0x1c;
    di -= 0x1c;
    if (si != di) {
      StrAssign(di, *(void**)si, *(void**)(si + 4));
    }
    *(u32*)(di + 0x10) = *(u32*)(si + 0x10);
    *(float*)(di + 0x14) = *(float*)(si + 0x14);
    *(u32*)(di + 0x18) = *(u32*)(si + 0x18);
  } while (si != first);
  return di;
}

// ======================================================================
// FUN_01006370 - per-frame space-game update; `this` in ecx. Shows/hides
// the space UI and drives planet<->solar transitions. Fields:
//   +0x48 AutoRefCount<SP::cSPUISpaceTrading> mSpaceTradingUI;
//   +0x4c eModelType mCurrentShoppingModelType; +0x4d bool transCtrl;
//   +0x4e bool mIsCapturingImpostor; +0x4f bool mImpostorCaptured;
//   +0x77 bool mSpaceGameActive.
// ======================================================================

// @ 0x01006370
void __fastcall FUN_01006370(void* self, void* /*edx*/) {
  char* p = (char*)self;
  if (!FUN_01044920()) goto lab_d8;
  {
    void* ufo = SP_GetUFOSimulator();
    if (!FUN_00ffc5b0(ufo)) goto lab_d8;
  }
  {
    void* pm = SP_PlanetModel();
    void* obj = *(void**)((char*)pm + 0x24);
    if (!((bool(__thiscall*)(void*))(*(void***)obj)[0x50 / 4])(obj)) goto lab_72;
  }

  if (*(u8*)(p + 0x4e) == 0) {
    if (*(u8*)(p + 0x4c) == 0) {
      if (*(u8*)(p + 0x4f) == 0) {
        // Create the space tool tray and its listener UI.
        {
          void* a = operator_new(0x2c, "Simulator", 0, 0, 0, 0);
          if (a) a = FUN_00b60070(a);
          FUN_0061df40(a);
        }
        void* listener;
        {
          void* b = operator_new(0x20, "Simulator", 0, 0, 0, 0);
          if (b) listener = FUN_00760c00(b);
          else   listener = 0;
        }
        void* refHolder;
        FUN_00572660(&refHolder, listener);
        void* reg = FUN_0067dd50();
        s32 cnt = ((s32(__thiscall*)(void*))(*(void***)reg)[0x68 / 4])(reg);
        for (s32 i = 0; i < cnt; i++) {
          void* r = FUN_0067dd50();
          u32* rec = (u32*)((u32(__thiscall*)(void*, s32))(*(void***)r)[0x70 / 4])(r, i);
          u32 kind = rec[1];
          if (kind == 7 || kind == 8 || kind == 0xa) {
            FUN_00760fd0((void*)refHolder, rec[0], kind, rec[2]);
          }
        }
        void* planet = (void*)FUN_01021260();  // active planet
        void* reg2 = FUN_0067dd60();
        u32 res = ((u32(__thiscall*)(void*, const char*, const char*, int, int, int, int, int))
                       (*(void***)reg2)[0x3c / 4])(reg2, (const char*)0x5fe9b92,
                        (const char*)0x5fe9b97, 0x80, 0x80, 1, 0x208, 0x15);
        u32 img = (u32)FUN_00576650(p + 0x48, (void*)res);
        void* name = FUN_00c707e0(planet);
        void* str = FUN_0093c570(&name, name);
        (void)str;
        (void)img;
      } else {
        goto lab_8c;
      }
    }
  } else {
lab_8c:
    if (*(u8*)(p + 0x4c) == 0 && *(u8*)(p + 0x4f) != 0) {
      void* planet = (void*)FUN_01021260();
      void* e = (void*)FUN_00b3d360(planet);
      FUN_00b7daf0(e);
      *(u8*)(p + 0x4f) = 0;
      *(u8*)(p + 0x4e) = 0;
      *(u8*)(p + 0x4c) = 1;
      *(u8*)(p + 0x4d) = 0;
      goto lab_72;
    }
  }
  if (*(u8*)(p + 0x4d) != 0) {
    *(u8*)(p + 0x4d) = 0;
    *(u8*)(p + 0x4c) = 0;
    void* am = FUN_00fd9c60();
    FUN_00fde3e0(am);
  }
lab_d8:
  if (*(u8*)(p + 0x77) == 0) return;
  *(u8*)(p + 0x77) = 0;
  {
    void* s = FUN_0067cab0();
    FUN_00801380(s);
  }
  return;
lab_72:
  if (*(u8*)(p + 0x77) != 0) return;
  *(u8*)(p + 0x77) = 1;
  {
    void* s = FUN_0067cab0();
    FUN_00801360(s);
  }
}

// ======================================================================
// remainder: small helpers + ctor
// ======================================================================

// @ 0x01006600
bool __cdecl FUN_01006600(void* dst, void** src) {
  u32 v = 0;
  if (*src != 0) {
    void* o = (char*)*src + 8;
    v = ((u32(__thiscall*)(void*, u32))(*(void***)o)[0xc / 4])(o, 0x179c807);
  }
  ((void(__thiscall*)(void*, u32))(*(void***)dst)[0x2c / 4])(dst, v);
  return true;
}

// @ 0x01006630
void* __fastcall FUN_01006630(void* self, void* /*edx*/, void* src) {
  u32* d = (u32*)self;
  u32* s = (u32*)src;
  d[0] = 0; d[1] = 0; d[2] = 0;
  char* sBegin = (char*)s[0];
  char* sEnd   = (char*)s[1];
  u32  n       = (u32)(sEnd - sBegin);
  FUN_00475ab0(d, n + 1);
  char* dBegin = (char*)d[0];
  memcpy(dBegin, sBegin, n);
  char* dEnd = dBegin + n;
  d[1] = (u32)dEnd;
  *dEnd = 0;
  *(u32*)((char*)d + 0x10) = *(u32*)((char*)s + 0x10);
  *(float*)((char*)d + 0x14) = *(float*)((char*)s + 0x14);
  *(u32*)((char*)d + 0x18) = *(u32*)((char*)s + 0x18);
  return d;
}

// @ 0x010066e0
void* __fastcall FUN_010066e0(void* self, void* /*edx*/) {
  char* p = (char*)self;
  TC_b5b6c0(self);                        // cGonzagoSimulator base ctor
  *(u32*)(p + 0x10) = 0x013eb384;         // ??_7cListenerBase@@6B@
  *(u32*)(p + 0x00) = 0x0149544c;
  *(u32*)(p + 0x08) = 0x01495428;
  *(u32*)(p + 0x10) = 0x01495418;
  *(u32*)(p + 0x14) = 0;
  *(u32*)(p + 0x18) = 0;
  *(u32*)(p + 0x1c) = 0xffffffff;
  *(u32*)(p + 0x20) = 0;
  *(u32*)(p + 0x24) = 0;
  *(u32*)(p + 0x28) = 0;
  void* sub = operator_new(0x108, "Simulator", 0, 0, 0, 0);
  if (sub) sub = TC_fe68a0(sub);
  else     sub = 0;
  *(u32*)(p + 0x30) = (u32)sub;
  *(float*)(p + 0x34) = 0.0f;
  *(float*)(p + 0x38) = 0.0f;
  *(u32*)(p + 0x40) = 0;
  *(u32*)(p + 0x44) = 0;
  *(u32*)(p + 0x48) = 0;
  *(u8*)(p + 0x4c) = 0;
  *(u8*)(p + 0x4d) = 0;
  *(u8*)(p + 0x4e) = 0;
  *(u8*)(p + 0x4f) = 0;
  *(u32*)(p + 0x50) = 0;
  *(u32*)(p + 0x54) = 0;
  *(u32*)(p + 0x58) = 0;
  *(u32*)(p + 0x5c) = 0;
  *(u32*)(p + 0x60) = 0;
  *(u32*)(p + 0x64) = 0;
  *(u32*)(p + 0x68) = 0;
  *(u8*)(p + 0x6c) = 0;
  *(u32*)(p + 0x70) = 0;
  *(u8*)(p + 0x74) = 0;
  *(u8*)(p + 0x75) = 1;
  *(u8*)(p + 0x76) = 0;
  *(u8*)(p + 0x77) = 0;
  *(u32*)(p + 0x78) = 0;
  *(u32*)(p + 0x7c) = 0;
  *(u32*)(p + 0x80) = 0;
  TC_b63890(p + 0x90);                    // cGonzagoTimer ctor
  *(u32*)(p + 0xb0) = 0;
  *(u32*)(p + 0xb4) = 0;
  *(u32*)(p + 0xb8) = 0;
  *(u32*)(p + 0xbc) = 0;
  *(u32*)(p + 0xc0) = 0;
  *(u32*)(p + 0xc4) = 0;
  *(u32*)(p + 0xc8) = 0;
  *(u32*)(p + 0xcc) = 0;
  *(u32*)(p + 0xd0) = 0;
  *(u32*)(p + 0xdc) = 0;
  *(u32*)(p + 0xe0) = 0;
  *(u32*)(p + 0xe4) = 0;
  *(u32*)0x016dc0fc = (u32)self;          // singleton
  {
    u32* r = (u32*)(p + 0x28);
    u32 obj = *r;
    if (obj != 0) {
      *r = 0;
      void* o = (void*)obj;
      ((void(__thiscall*)(void*))(*(void***)o)[4 / 4])(o);
    }
  }
  *(u32*)(p + 0xc4) = 0;
  TC_bc30f0(p + 0x90);                    // cSPTimer::Start
  return self;
}
