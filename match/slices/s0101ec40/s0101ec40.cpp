// s0101ec40.cpp — SporeApp space-game player-camera update region.
// Reconstructed from the Ghidra decompile + disassembly.
//
// cl rejects __thiscall on free functions, so the __thiscall entry point is
// declared as a member of S (methods keep the FUN_ names so run_all's substring
// match finds them).

#include <stddef.h>

inline void* VFn(void* o, int byteoff) { return (*(void***)o)[byteoff / 4]; }

// ---- globals ---------------------------------------------------------------
extern "C" float DAT_016dd444;   // 0x16dd444  invalid-position sentinel x
extern "C" float DAT_016dd448;   // 0x16dd448  invalid-position sentinel y
extern "C" float DAT_016dd44c;   // 0x16dd44c  invalid-position sentinel z

// ---- callees ---------------------------------------------------------------
extern "C" void* FUN_00ffbe50();                     // 0xffbe50  SP::GetUFOSimulator
extern "C" void* FUN_00a1ad60();                     // 0xa1ad60  cSPSimulatorSpaceGame::GetPlayerInventory (thiscall)
extern "C" void* FUN_00b3d380();                     // 0xb3d380  SP::GameTimeManager
extern "C" void  FUN_0101d130();                     // 0x101d130 (thiscall, 2 args, ret 8)
extern "C" void  FUN_01043580(void*, void*, void*, void*); // 0x1043580 (cdecl, 4 args)
extern "C" void  FUN_007c4ba0();                     // 0x7c4ba0  cViewer::FUN_007c4ba0 (thiscall, 1 arg, ret 4)
extern "C" void  FUN_007c4bc0();                     // 0x7c4bc0  cViewer::FUN_007c4bc0 (thiscall, 1 arg, ret 4)
extern "C" void  FUN_007c5350();                     // 0x7c5350  cViewer::SetViewAngle (thiscall, 1 arg, ret 4)
extern "C" void  FUN_007c4c40();                     // 0x7c4c40  cViewer::SetCameraToWorld (thiscall, 1 arg, ret 4)
extern "C" void  FUN_0101ad50();                     // 0x101ad50 (thiscall, 0 args)
extern "C" void  FUN_01042480(void*, void*);         // 0x1042480 (cdecl, 2 args)
extern "C" void* FUN_00b3d280();                     // 0xb3d280  GetCameraCtl
extern "C" void  FUN_00b10540();                     // 0xb10540  cTerrainCameraController::FUN_00b10540 (thiscall, 3 args, ret 0xc)

struct S {
  void FUN_0101ec40(void* param_2, void* param_3);   // 0x101ec40
};

// ===========================================================================
// @ 0x0101ec40
void S::FUN_0101ec40(void* param_2, void* param_3)
{
  char* self = (char*)this;

  void* ufo = FUN_00ffbe50();
  void* inv = ((void* (__thiscall*)(void*))FUN_00a1ad60)(ufo);

  int iVar2;
  if (*(char*)((char*)inv + 0x74c) != 0) {
    void* gt = FUN_00b3d380();
    if ((*(unsigned char*)((char*)gt + 0x48) & 1) == 0) {
      iVar2 = (int)inv + 0x750;
      goto L_ec80;
    }
  }
  {
    char* o = (char*)inv + 0x34;
    iVar2 = (*(int (__thiscall**)(void*))((char*)*(void**)o + 0x2c))(o);
  }

L_ec80:
  float* pf = (float*)(self + 0xb4);
  if (pf[0] == DAT_016dd444 && pf[1] == DAT_016dd448 && pf[2] == DAT_016dd44c) {
    self[0x68] = 1;
    ((void (__thiscall*)(void*, void*, void*))FUN_0101d130)(this, param_2, param_3);
  }

  float local_40[16];
  FUN_01043580(pf, (void*)iVar2, pf, local_40);

  ((void (__thiscall*)(void*, float))FUN_007c4ba0)(param_3, 2.0f);
  ((void (__thiscall*)(void*, float))FUN_007c4bc0)(param_3, 3000.0f);
  ((void (__thiscall*)(void*, float))FUN_007c5350)(param_3, *(float*)(self + 0x70));
  ((void (__thiscall*)(void*, float*))FUN_007c4c40)(param_3, local_40);

  ((void (__thiscall*)(void*))FUN_0101ad50)(this);

  float local_4c[3];
  FUN_01042480(local_4c, pf);

  if (FUN_00b3d280() != 0) {
    ((void (__thiscall*)(void*, float, float, float))FUN_00b10540)(FUN_00b3d280(), local_4c[1], local_4c[2], local_4c[0] * 0.5f);
  }
}
