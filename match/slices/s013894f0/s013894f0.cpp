// Slice s013894f0. Five compiler-generated dynamic initializers:
//   0x013894f0  "Simulator/ScearioMode/UI" global object (new + ctor) and an auxiliary
//               object at 0x015ad328, plus an atexit destructor registration.
//   0x01389680  global array of 10 list/vector heads at 0x016c7df0 (stride 0x20), heads zeroed.
//   0x0138a250  4-record attribute table at 0x015adbd0 (mKey / mMachineId / mServerId / mModelType).
//   0x0138a400  8-record attribute table at 0x015add00 (SensorTag condition/action fields).
//   0x0138a710  25-record Simulator::cScenarioClassAct attribute table at 0x015adf20 (2420 bytes).
//
// Builds Attribute records (60 bytes each) through the inline Attribute constructor; cl builds
// every element in one stack temporary and copies it into the table with `rep movsd` (15 dwords).
// Offsets are member offsets from the matching ModAPI headers. The originals are compiler-generated
// dynamic initializers; these plain functions with per-element assignments are shape-equivalent
// (same bytes), so a relinked build must run them at startup.
//
// The callbacks are separate extern symbols per attribute type group (u64/int, float-like double, bool):
// the retail linker folded identical template instances to one address (e.g. 0xb1fbf0 serves all three
// groups), but in the object files they are distinct symbols. That is why cl hoists only DefaultOffset
// and the u64 group's last two callbacks into edx/ebp/ebx.
#include "types.h"

typedef bool (*ReadFn)(void*, void*);
typedef bool (*WriteFn)(void*, void*);
typedef void (*ReadTextFn)(const void*, void*);
typedef void (*WriteTextFn)(char*, void*);
typedef bool (*UnkFn)();
typedef bool (*Unk2Fn)(void*, const char*, int);
struct Attribute;
typedef void* (*OffsetFn)(Attribute*);

void* DefaultOffset(Attribute*);                       // 0x692ca0
// reading / writing / text callbacks (addresses of the originals)
bool  rd_00572810(void*, void*);
bool  wr_00572840(void*, void*);
void  rt_00692ff0(const void*, void*);
void  wt_00694ee0(char*, void*);
bool  uk_00b1fbf0();                                   // shared "return true" stub
bool  u2_0057cde0(void*, const char*, int);

bool  wr_00ac88f0(void*, void*);
void  rt_006930b0(const void*, void*);
void  wt_00694fc0(char*, void*);
bool  u2_00acbb80(void*, const char*, int);

bool  rd_00ac8750(void*, void*);
bool  wr_00ac8780(void*, void*);
void  rt_00693090(const void*, void*);
void  wt_00694fa0(char*, void*);
bool  u2_0057ce00(void*, const char*, int);

bool  rd_00f2c950(void*, void*);
bool  wr_00f268f0(void*, void*);
void  rt_00c2e4e0(const void*, void*);
void  wt_00692fb0(char*, void*);
bool  uk_00f26990();
bool  u2_00f29410(void*, const char*, int);

bool  rd_00f293f0(void*, void*);
bool  wr_00f268b0(void*, void*);
bool  uk_00f25b60();
bool  u2_00f28880(void*, const char*, int);

bool  rd_00f29560(void*, void*);
bool  wr_00f269d0(void*, void*);
bool  uk_00f26a60();
bool  u2_00f29650(void*, const char*, int);

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
  Attribute(const char* n, uint32_t i, unsigned o, ReadFn r, WriteFn w, ReadTextFn rt,
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

// per-group callback symbols (the linker folds identical ones to a single address)
bool rd_00572810_g1(void*, void*);
bool rd_00572810_g2(void*, void*);
bool rd_00ac8750_g3(void*, void*);
void rt_00692ff0_g1(const void*, void*);
void rt_00693090_g3(const void*, void*);
void rt_006930b0_g2(const void*, void*);
bool u2_0057cde0_g1(void*, const char*, int);
bool u2_0057ce00_g3(void*, const char*, int);
bool u2_00acbb80_g2(void*, const char*, int);
bool uk_00b1fbf0_g1();
bool uk_00b1fbf0_g2();
bool uk_00b1fbf0_g3();
bool wr_00572840_g1(void*, void*);
bool wr_00ac8780_g3(void*, void*);
bool wr_00ac88f0_g2(void*, void*);
void wt_00694ee0_g1(char*, void*);
void wt_00694fa0_g3(char*, void*);
void wt_00694fc0_g2(char*, void*);

// ---------------------------------------------------------------------------
// 0x013894f0: dynamic initializer of the "Simulator/ScearioMode/UI" global
// object at 0x015ad334 and of an auxiliary object at 0x015ad328.
// ---------------------------------------------------------------------------
void* operator_new(unsigned size, const char* name, int, int, int, int);   // 0x00f473a0
extern "C" int atexit(void (__cdecl*)(void));                             // 0x011e07ef
void AtExit013c9070();                                                    // 0x013c9070

extern void* g_spScenarioModeUI;    // 0x015ad334 (the constructed UI object)
extern char  g_spScenarioModeAux[]; // 0x015ad328 (0x0c bytes before the UI pointer)

// The retail constructor returns `this` in EAX after consuming it in ECX
// (thiscall); modelling it as a returning member reproduces the `mov ecx,eax;
// call; mov <global>,eax` sequence.
struct SceneModeUI { void* Construct(); };        // 0x00f2aac0
struct SceneModeAux { void  Init(); };            // 0x00f03290

// @ 0x013894f0
void InitScenarioModeUI() {
  SceneModeUI* p = (SceneModeUI*)operator_new(0x234, "Simulator/ScearioMode/UI", 0, 0, 0, 0);
  g_spScenarioModeUI = p ? p->Construct() : 0;
  ((SceneModeAux*)g_spScenarioModeAux)->Init();
  atexit(&AtExit013c9070);
}

// ---------------------------------------------------------------------------
// 0x01389680: dynamic initializer of a global array of 10 list/vector heads at
// 0x016c7df0 (stride 0x20). Only the two leading pointer members of each head
// are cleared; a static destructor is registered afterwards.
// ---------------------------------------------------------------------------
struct ListHead { void* mpBegin; void* mpEnd; char pad[0x18]; };
extern ListHead g_spHeadArray[10];   // 0x016c7df0
void AtExit013c9140();               // 0x013c9140

// @ 0x01389680
void InitHeadArray() {
  for (int i = 0; i < 10; ++i) {
    g_spHeadArray[i].mpBegin = 0;
    g_spHeadArray[i].mpEnd = 0;
  }
  atexit(&AtExit013c9140);
}

// @ 0x0138a710
Attribute gScenarioClassActAttributes[25];

void InitScenarioClassActAttributes() {
  gScenarioClassActAttributes[0] = Attribute("teamBehavior", 0x7114ed5, 0x4a8, rd_00572810_g1, wr_00572840_g1, rt_00692ff0_g1, wt_00694ee0_g1, uk_00b1fbf0_g1, u2_0057cde0_g1);
  gScenarioClassActAttributes[1] = Attribute("stanceBehavior", 0x7114ed6, 0x4ac, rd_00572810_g1, wr_00572840_g1, rt_00692ff0_g1, wt_00694ee0_g1, uk_00b1fbf0_g1, u2_0057cde0_g1);
  gScenarioClassActAttributes[2] = Attribute("pickupBehavior", 0x7114ed7, 0x4b0, rd_00572810_g1, wr_00572840_g1, rt_00692ff0_g1, wt_00694ee0_g1, uk_00b1fbf0_g1, u2_0057cde0_g1);
  gScenarioClassActAttributes[3] = Attribute("giveBehavior", 0x73923ef, 0x4b4, rd_00572810_g1, wr_00572840_g1, rt_00692ff0_g1, wt_00694ee0_g1, uk_00b1fbf0_g1, u2_0057cde0_g1);
  gScenarioClassActAttributes[4] = Attribute("movementBehavior", 0x7114ed8, 0x4b8, rd_00572810_g1, wr_00572840_g1, rt_00692ff0_g1, wt_00694ee0_g1, uk_00b1fbf0_g1, u2_0057cde0_g1);
  gScenarioClassActAttributes[5] = Attribute("pickupTargetClassIndex", 0x7114ed9, 0x4bc, rd_00572810_g1, wr_00572840_g1, rt_00692ff0_g1, wt_00694ee0_g1, uk_00b1fbf0_g1, u2_0057cde0_g1);
  gScenarioClassActAttributes[6] = Attribute("giveTargetClassIndex", 0x73b8345, 0x4c0, rd_00572810_g1, wr_00572840_g1, rt_00692ff0_g1, wt_00694ee0_g1, uk_00b1fbf0_g1, u2_0057cde0_g1);
  gScenarioClassActAttributes[7] = Attribute("trackTargetClassIndex", 0x7114eda, 0x4c4, rd_00572810_g1, wr_00572840_g1, rt_00692ff0_g1, wt_00694ee0_g1, uk_00b1fbf0_g1, u2_0057cde0_g1);
  gScenarioClassActAttributes[8] = Attribute("awareness", 0x7114edb, 0x484, rd_00572810_g2, wr_00ac88f0_g2, rt_006930b0_g2, wt_00694fc0_g2, uk_00b1fbf0_g2, u2_00acbb80_g2);
  gScenarioClassActAttributes[9] = Attribute("damageMultiplier", 0x7cc8d8a, 0x494, rd_00572810_g2, wr_00ac88f0_g2, rt_006930b0_g2, wt_00694fc0_g2, uk_00b1fbf0_g2, u2_00acbb80_g2);
  gScenarioClassActAttributes[10] = Attribute("speedMultiplier", 0x7cc8d8f, 0x490, rd_00572810_g2, wr_00ac88f0_g2, rt_006930b0_g2, wt_00694fc0_g2, uk_00b1fbf0_g2, u2_00acbb80_g2);
  gScenarioClassActAttributes[11] = Attribute("health_DEPRECATED", 0x7114edc, 0x488, rd_00572810_g2, wr_00ac88f0_g2, rt_006930b0_g2, wt_00694fc0_g2, uk_00b1fbf0_g2, u2_00acbb80_g2);
  gScenarioClassActAttributes[12] = Attribute("healthMultiplier", 0x7cf7330, 0x48c, rd_00572810_g2, wr_00ac88f0_g2, rt_006930b0_g2, wt_00694fc0_g2, uk_00b1fbf0_g2, u2_00acbb80_g2);
  gScenarioClassActAttributes[13] = Attribute("damageTuning", 0x7cf7430, 0x49c, rd_00572810_g2, wr_00ac88f0_g2, rt_006930b0_g2, wt_00694fc0_g2, uk_00b1fbf0_g2, u2_00acbb80_g2);
  gScenarioClassActAttributes[14] = Attribute("radiusTuning", 0x7cf7530, 0x498, rd_00572810_g2, wr_00ac88f0_g2, rt_006930b0_g2, wt_00694fc0_g2, uk_00b1fbf0_g2, u2_00acbb80_g2);
  gScenarioClassActAttributes[15] = Attribute("jumpTuning", 0x7cf7630, 0x4a0, rd_00572810_g2, wr_00ac88f0_g2, rt_006930b0_g2, wt_00694fc0_g2, uk_00b1fbf0_g2, u2_00acbb80_g2);
  gScenarioClassActAttributes[16] = Attribute("spawnDelay_", 0x7114fdd, 0x4a4, rd_00572810_g1, wr_00572840_g1, rt_00692ff0_g1, wt_00694ee0_g1, uk_00b1fbf0_g1, u2_0057cde0_g1);
  gScenarioClassActAttributes[17] = Attribute("invulnerable", 0x75f7aa0, 0x1, rd_00ac8750_g3, wr_00ac8780_g3, rt_00693090_g3, wt_00694fa0_g3, uk_00b1fbf0_g3, u2_0057ce00_g3);
  gScenarioClassActAttributes[18] = Attribute("isDead", 0x75f7aa1, 0x2, rd_00ac8750_g3, wr_00ac8780_g3, rt_00693090_g3, wt_00694fa0_g3, uk_00b1fbf0_g3, u2_0057ce00_g3);
  gScenarioClassActAttributes[19] = Attribute("visible", 0x7114ede, 0x0, rd_00ac8750_g3, wr_00ac8780_g3, rt_00693090_g3, wt_00694fa0_g3, uk_00b1fbf0_g3, u2_0057ce00_g3);
  gScenarioClassActAttributes[20] = Attribute("dialogs_chatter", 0x7114ee1, 0x4, rd_00f2c950, wr_00f268f0, rt_00c2e4e0, wt_00692fb0, uk_00f26990, u2_00f29410);
  gScenarioClassActAttributes[21] = Attribute("dialogs_inspect", 0x7114ee3, 0x170, rd_00f2c950, wr_00f268f0, rt_00c2e4e0, wt_00692fb0, uk_00f26990, u2_00f29410);
  gScenarioClassActAttributes[22] = Attribute("descriptionDEPRECATED", 0x7114edf, 0x448, rd_00f293f0, wr_00f268b0, rt_00c2e4e0, wt_00692fb0, uk_00f25b60, u2_00f28880);
  gScenarioClassActAttributes[23] = Attribute("customBehavior", 0x7b787ea, 0x4c8, rd_00ac8750_g3, wr_00ac8780_g3, rt_00693090_g3, wt_00694fa0_g3, uk_00b1fbf0_g3, u2_0057ce00_g3);
  gScenarioClassActAttributes[24] = Attribute("customBehaviorEntries", 0x7b787fd, 0x4cc, rd_00f29560, wr_00f269d0, rt_00c2e4e0, wt_00692fb0, uk_00f26a60, u2_00f29650);
}

// ---------------------------------------------------------------------------
// 0x0138a250: dynamic initializer of a 4-record attribute table at 0x015adbd0
// (records 0x3c bytes apart: 015adbd0, 015adc0c, 015adc48, 015adc84).
//   idx0 mKey       off 0x00 KEY_ATTR
//   idx1 mMachineId off 0x0c u32
//   idx2 mServerId  off 0x10 i64
//   idx3 mModelType off 0x18 u32
// ---------------------------------------------------------------------------
Attribute gServerIdAttributes[4];   // 0x015adbd0

// Per-record callback aliases: distinct object symbols stop cl from hoisting a
// shared callback into a callee-saved register (retail keeps every callback as a
// direct memory immediate and hoists only DefaultOffset).
bool rd_00ae3430_r0(void*, void*);
bool wr_00ae3450_r0(void*, void*);
void rt_00693150_r0(const void*, void*);
void wt_00695080_r0(char*, void*);
bool uk_00b1fbf0_r0();
bool u2_00ae5720_r0(void*, const char*, int);

bool rd_00572810_r1(void*, void*);
bool wr_00572840_r1(void*, void*);
void rt_00693090_r1(const void*, void*);
void wt_00694f00_r1(char*, void*);
bool uk_00b1fbf0_r1();
bool u2_00675ca0_r1(void*, const char*, int);

bool rd_00aff840_r2(void*, void*);
bool wr_00aff870_r2(void*, void*);
void rt_00692fd0_r2(const void*, void*);
void wt_00694ec0_r2(char*, void*);
bool uk_00b1fbf0_r2();
bool u2_00595a70_r2(void*, const char*, int);

bool rd_00572810_r3(void*, void*);
bool wr_00572840_r3(void*, void*);
void rt_00693090_r3(const void*, void*);
void wt_00694f00_r3(char*, void*);
bool uk_00b1fbf0_r3();
bool u2_00675ca0_r3(void*, const char*, int);

// @ 0x0138a250
void InitServerIdAttributes() {
  gServerIdAttributes[0] = Attribute("mKey",       0x62b74270, 0x00, rd_00ae3430_r0, wr_00ae3450_r0, rt_00693150_r0, wt_00695080_r0, uk_00b1fbf0_r0, u2_00ae5720_r0);
  gServerIdAttributes[1] = Attribute("mMachineId", 0x62b74271, 0x0c, rd_00572810_r1, wr_00572840_r1, rt_00693090_r1, wt_00694f00_r1, uk_00b1fbf0_r1, u2_00675ca0_r1);
  gServerIdAttributes[2] = Attribute("mServerId",  0x62b74272, 0x10, rd_00aff840_r2, wr_00aff870_r2, rt_00692fd0_r2, wt_00694ec0_r2, uk_00b1fbf0_r2, u2_00595a70_r2);
  gServerIdAttributes[3] = Attribute("mModelType", 0x62b74273, 0x18, rd_00572810_r3, wr_00572840_r3, rt_00693090_r3, wt_00694f00_r3, uk_00b1fbf0_r3, u2_00675ca0_r3);
}

// ---------------------------------------------------------------------------
// 0x0138a400: dynamic initializer of an 8-record attribute table at 0x015add00
// (records 0x3c bytes apart: 015add00 .. 015adea4). All rows share the int
// u64/u32 callback pair; offsets 0x00,0x04,0x08,0x0c,0x10,0x14,0x18,0x1c.
// ---------------------------------------------------------------------------
Attribute gSensorTagAttributes[8];   // 0x015add00

// @ 0x0138a400
void InitSensorTagAttributes() {
  gSensorTagAttributes[0] = Attribute("condition.conditionType",       0x7b78783, 0x00, rd_00572810, wr_00572840, rt_00692ff0, wt_00694ee0, uk_00b1fbf0, u2_0057cde0);
  gSensorTagAttributes[1] = Attribute("condition.target.type",         0x7b7a2f2, 0x04, rd_00572810, wr_00572840, rt_00692ff0, wt_00694ee0, uk_00b1fbf0, u2_0057cde0);
  gSensorTagAttributes[2] = Attribute("condition.target.value",        0x7b7a2f3, 0x08, rd_00572810, wr_00572840, rt_00692ff0, wt_00694ee0, uk_00b1fbf0, u2_0057cde0);
  gSensorTagAttributes[3] = Attribute("action.actionType",             0x7b78786, 0x0c, rd_00572810, wr_00572840, rt_00692ff0, wt_00694ee0, uk_00b1fbf0, u2_0057cde0);
  gSensorTagAttributes[4] = Attribute("action.target.type",            0x7bd3fae, 0x10, rd_00572810, wr_00572840, rt_00692ff0, wt_00694ee0, uk_00b1fbf0, u2_0057cde0);
  gSensorTagAttributes[5] = Attribute("action.target.value",           0x7bd3fb4, 0x14, rd_00572810, wr_00572840, rt_00692ff0, wt_00694ee0, uk_00b1fbf0, u2_0057cde0);
  gSensorTagAttributes[6] = Attribute("action.secondaryTarget.type",   0x7bd3fb8, 0x18, rd_00572810, wr_00572840, rt_00692ff0, wt_00694ee0, uk_00b1fbf0, u2_0057cde0);
  gSensorTagAttributes[7] = Attribute("action.secondaryTarget.value",  0x7bd3fbd, 0x1c, rd_00572810, wr_00572840, rt_00692ff0, wt_00694ee0, uk_00b1fbf0, u2_0057cde0);
}
