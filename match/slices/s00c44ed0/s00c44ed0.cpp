// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
struct Obj00c44ed0 {
  virtual void pad(); // many
  char padbytes[0x18c - 4]; // rough
  unsigned char mFlag;
  void Set(unsigned char v);
};
// Better layout:
struct Obj2 {
  void** vt;
  char pad[0x18c - 4];
  unsigned char mFlag;
  void Set(unsigned char v);
};
// @ 0x00c44ed0
void Obj2::Set(unsigned char v) {
  if (mFlag) {
    if (!v)
      ((void (__thiscall*)(void*, int))(vt[0x1a0/4]))(this, 1);
    mFlag = v;
  } else {
    mFlag = v;
  }
}
