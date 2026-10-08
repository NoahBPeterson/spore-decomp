// Slice s013894f0: initializer of the Simulator::cScenarioClassAct attribute table (0x0138a710, 2420 bytes).
//
// Builds 25 Simulator::Attribute records (60 bytes each, globals 0x15adf20..0x15ae4fc) through the
// inline Attribute constructor; cl builds every element in one stack temporary and copies it into
// the table with `rep movsd` (15 dwords). Offsets are cScenarioClassAct member offsets (ModAPI
// cScenarioClassAct.h). The original is a compiler-generated dynamic initializer; this plain function with
// per-element assignments is shape-equivalent (same bytes), so a relinked build must run it at startup.
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
