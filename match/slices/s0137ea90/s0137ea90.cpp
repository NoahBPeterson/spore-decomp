// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "types.h"
extern float g_16b39cc;
extern float g_15a7b88;
extern float g_140f334;
extern float g_140f32c;
float g_16b39d0;
// @ 0x0137ea90
void FUN_0137ea90() {
  float x = g_16b39cc * g_15a7b88 * g_140f334;
  g_16b39d0 = g_140f32c / x;
}
