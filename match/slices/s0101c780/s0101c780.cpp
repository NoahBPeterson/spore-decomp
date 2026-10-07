// Slice s0101c780: SP::cSPSpacePlanetCameraController member at 0x0101c780 (2469 bytes, mixed SSE + x87).
// PARTIAL skeleton. Thiscall (this = ecx, saved in ebp), 8 stack dwords (ret 0x20).
#include "types.h"

#pragma pack(push, 4)

namespace SP {

class cSPSpacePlanetCameraController {
public:
    // Offsets touched by 0x0101c780 (per asm): +0x6c/+0x70/+0x78 (float), +0x84/+0x90 (float),
    // +0x94 (vec3, written from FUN_0059aed0 result), +0x198 (flags, OR 1), +0x1a4/+0x1a8 float args.
    void FUN_0101c780(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3,
                      uint32_t a4, uint32_t a5, uint32_t a6, uint32_t a7);
};

// @ 0x0101c780
// PARTIAL skeleton: not yet implemented.
//
// Open questions for the next pass (see the notes in the agent report):
//  - The five call sites of 0x00799320 (0101cb5f, 0101ccc7, c05523, c0558c, 799784 callers in
//    other functions) push NO stack arguments before the call, yet the callee reads [esp+4] and
//    [esp+8] (out, in) and returns its out pointer in eax. At 0101cb5f the only pushes on the
//    stack are the callee-saved ebx/edi pushed at 0101c7ee/0101c7ef on this path, so the
//    convention for this helper is not yet understood. It blocks byte-exact and equivalence.
//  - 0x0101c7ee pushes ebx/edi only on the path past the early exit (jbe 0x101d11a); the
//    register-save shape needs to be reproduced exactly.
//  - Stack-arg roles: [esp+0x188] is the first pointer (esi), [esp+0x194] is edi (pointer),
//    [esp+0x198] is eax (pointer), [esp+0x18c]/[esp+0x19c]/[esp+0x1a4]/[esp+0x1a8] are floats.
//    Ghidra's signature (param_2 float, param_3..5 pointers) disagrees with the asm; trust the asm.
//  - Callees with confirmed conventions from call sites: SP::PlanetModel (0xb3d350, free),
//    0xb7e4d0 (thiscall, returns float), SP::App (0x67dd10, free), 0xffbe50 SP::GetUFOSimulator (free),
//    0xa1ad60 cSPSimulatorSpaceGame::GetPlayerInventory (thiscall),
//    0x1017b70 cSPSpacePlanetCameraController::GetUFOPosition (thiscall, returns float*),
//    0x1019950 UpdateCameraPitchRotation (thiscall, 2 floats, ret 8),
//    0xb17790 (thiscall, 1 int arg), 0xb16dc0 (thiscall, 1 arg, ret 4),
//    0xb182f0 PathOrSerializationCheck / 0xb181d0 WaterClearance (free cdecl, add esp 8),
//    0xb17c10 / 0xb17810 / 0xb16450 / 0xb16490 / 0xb16e50 (free cdecl, add esp 8).
//    0x59aed0 is stdcall-like with 3 stack args and returns its result pointer in eax (no add esp).
//    0xad92d0 is a thiscall vector dtor; 0xf47380 is operator_delete (cdecl, add esp 4).
void cSPSpacePlanetCameraController::FUN_0101c780(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3,
                                                  uint32_t a4, uint32_t a5, uint32_t a6, uint32_t a7)
{
    (void)a0; (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6; (void)a7;
}

} // namespace SP

#pragma pack(pop)
