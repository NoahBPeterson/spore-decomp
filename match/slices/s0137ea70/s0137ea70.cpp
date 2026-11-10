// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "types.h"
extern float g_15a7b98;
float g_16b39cc;
// @ 0x0137ea70
void FUN_0137ea70() {
  float v = g_15a7b98;
  g_16b39cc = v * v * v;
}
