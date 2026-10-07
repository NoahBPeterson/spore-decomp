// slice s00db6e60: SP::MOVE_Tick (0x00db7190, 2500 bytes), __cdecl, 8 stack args.
// arg1 = creature (esi), arg5 = flags (bit 2 and bit 3 read), arg6 = float* position (edi),
// arg8 = float dt. Args 2, 3, 4 and 7 are not read by the original.
// PARTIAL: translation of the control flow from the asm and the Ghidra decompile. Field accesses are
// raw offsets; callee conventions come from the call sites. See partial.txt.
#include "types.h"

#define FIELD(p, off, T) (*(T*)((char*)(p) + (off)))

struct CreatureBase;   // opaque: only raw offsets are used

// Thiscall members of cSPCreatureBase, declared but not defined here.
struct CreatureBaseFns {
    void Hover(int);                                       // 0x00c13a30
    void SetSprinting(int);                                // 0x00c1ad10
    void InterruptAnimation(int, int, int);                // 0x00c12310 (guid, -1, 0)
    void PlayAnimation(int, int, int);                     // 0x00c12190 (guid, 1, -1)
    void TryJumpToTarget(int, const void*, const void*, int, int);  // 0x00c190e0
    unsigned PlayIdleAnimation(int, int);                  // 0x00bc96a0 (on mgr+8)
    unsigned GetCurrentAnimationGUID();                    // 0x00c0e040
    bool IsNearGoal();                                     // 0x00c42e20 (on +0xc0)
    bool IsEligible(int);                                  // 0x00c0c0e0 (returns bool)
};

// Free callees (cdecl unless noted in partial.txt).
bool   Vector3NotEqual(const float* a, const float* b);    // 0x0041dd30
float  Vec3Length(const float* v);                         // 0x004df2d0 returns float (fstp)
unsigned ChildOfPool(int idx);                             // pool GetObject, 0x00db3c40 (thiscall on 0x0159d548)

namespace SP {

// The retail function. Returns the value the original leaves in eax.
int MOVE_Tick(void* self, int a2, int a3, int a4, unsigned flags, float* pos, int a7, float dt)
{
    (void)a2; (void)a3; (void)a4; (void)a7;
    // dt-subtract timer on pos[0]; if it goes negative, reset to 1.0 and try a path step.
    float* pf = pos;
    pf[0] = pf[0] - dt;
    if (pf[0] < 0.0f) {
        pf[0] = 1.0f;
        // ... path/goal step (FUN_00bca2a0, FUN_00bcb510, pool GetObject, FUN_00db6fa0 / FUN_00db6ef0)
    }
    pf[1] = pf[1] - dt;
    pf[2] = pf[2] - dt;
    if (FIELD(self, 0x137, unsigned char) == 0 || (FIELD(self, 0x110, unsigned) & 0x1000) != 0)
        pf[3] = pf[3] + dt;
    (void)flags;
    return 1;   // TODO: remaining paths (IsNearGoal, animation/hover branches, hashtable find, return values)
}

} // namespace SP
