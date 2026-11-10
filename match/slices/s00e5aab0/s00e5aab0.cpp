// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
struct Vec3 { float x,y,z; };
struct Pool { char* Get(unsigned id); };
extern Pool* g_16b3c04; // base; retail adds 0x1c
// @ 0x00e5aab0
Vec3* FUN_00e5aab0(Vec3* out, unsigned id) {
  char* base = (char*)g_16b3c04;
  Pool* pool = (Pool*)(base + 0x1c);
  char* row = pool->Get(id);
  float* src = (float*)(row + 0x4c);
  out->x = src[0];
  out->y = src[1];
  out->z = src[2];
  return out;
}
