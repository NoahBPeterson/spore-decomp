// Slice s0137e100: compiler-generated dynamic initializers (??__E...) for static reflection
// tables: FieldDesc arrays and the ClassDesc objects that register them (cSPAttachment, structure).
// Listed VAs other than 0x0137E100 are interior addresses of these initializers; the real
// starts are 0x0137E1B0, 0x0137E1F0, 0x0137E310 and 0x0137E350.
#include "types.h"

uint32_t FNVHash(const char* s, uint32_t seed, int mode);    // 0x00932E80
uint32_t HashName(const char* s);                            // 0x00E4A9D0
uint32_t TypeArg(uint32_t v);                                // 0x00E4A9C0 (identity)

struct FieldDesc {
  const char* name;
  uint32_t hash;
  int offset;
  int size;
  uint32_t type;
  uint32_t type2;
  int flags;
  uint32_t type3;
  int kind;
  int extra;
};

struct ClassDesc {
  char pad[0x2c];
  ClassDesc(const char* name, FieldDesc* fields, uint32_t hash, int a, int b,
            int c, int d, int e, int f, int g);       // 0x00E4A7D0
};

extern char g_desc_16ad640[], g_desc_16ad534[], g_desc_16ad4dc[], g_desc_16b0aac[],
    g_desc_16ad508[], g_desc_16b0d54[], g_desc_16b1140[];
extern float g_default_15a5dfc[];

// @ 0x0137E100
FieldDesc g_fields_16b1530[] = {
  {0, HashName(0), 4, 0, TypeArg(5), TypeArg(0), 0, TypeArg(5), 8, 0},
  {0, HashName(0), -1, 0, TypeArg(0), TypeArg(0), 0, TypeArg(0), 0, 0},
};

extern FieldDesc cSPAttachment_fields[];
// @ 0x0137E1B0
ClassDesc cSPAttachment_desc("cSPAttachment", cSPAttachment_fields,
    FNVHash("cSPAttachment", 0x811c9dc5, 1), 0x28, 0, 0, 0, 0, 0, 0);

// @ 0x0137E1F0
FieldDesc cSPAttachment_fields[] = {
  {0, HashName(0), 4, 0, TypeArg(5), TypeArg(0), 0, TypeArg(6), 8, 0},
  {"color", HashName("color"), 0x1c, 0, TypeArg(8), TypeArg(0), 0, TypeArg((uint32_t)g_default_15a5dfc), 2, 0},
  {0, HashName(0), -1, 0, TypeArg(0), TypeArg(0), 0, TypeArg(0), 0, 0},
};

extern FieldDesc structure_fields[];
// @ 0x0137E310
ClassDesc structure_desc("structure", structure_fields,
    FNVHash("structure", 0x811c9dc5, 1), 0x1c, 1, 0, 0, 0, 0, 0);

#define T(x) TypeArg((uint32_t)(x))
// @ 0x0137E350
FieldDesc structure_fields[] = {
  {"structure", HashName("structure"), 0x14, 0x18, T(g_desc_16ad640), T(4), 0, T(0), 4, 0},
  {"model", HashName("model"), 0x14, 0x18, T(g_desc_16ad534), T(4), 0, T(0), 4, 0},
  {"effect", HashName("effect"), 0x14, 0x18, T(g_desc_16ad4dc), T(4), 0, T(0), 4, 0},
  {"creature", HashName("creature"), 0x14, 0x18, T(g_desc_16b0aac), T(4), 0, T(0), 4, 0},
  {"random_creature", HashName("random_creature"), 0x14, 0x18, T(g_desc_16ad508), T(4), 0, T(0), 4, 0},
  {"player_creature", HashName("player_creature"), 0x14, 0x18, T(g_desc_16b0d54), T(4), 0, T(0), 4, 0},
  {"debug", HashName("debug"), 0x14, 0x18, T(g_desc_16b1140), T(4), 0, T(0), 4, 0},
  {"onDeath", HashName("onDeath"), 0, 0, T(7), T(0), 0, T(0), 6, 0},
  {"onDeathSmall", HashName("onDeathSmall"), 4, 4, T(7), T(0), 0, T(0), 6, 0},
  {"onDeathLarge", HashName("onDeathLarge"), 8, 8, T(7), T(0), 0, T(0), 6, 0},
  {"onHatch", HashName("onHatch"), 0xc, 0xc, T(7), T(0), 0, T(0), 6, 0},
  {"onStartHatch", HashName("onStartHatch"), 0x10, 0x10, T(7), T(0), 0, T(0), 6, 0},
  {0, HashName(0), -1, 0, T(0), T(0), 0, T(0), 0, 0},
};
