// Slice 10: nSPSkinner paint-system tick predicates and message handling helpers.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

void AtomicRefCounted_Release(void* p);   // 0x00402420
void FUN_00525d90(void* p, void* v);      // 0x00525d90

struct TickState {
    bool ShouldTick();
    void ClearPtr100();
};

// @ 0x00522720
bool TickState::ShouldTick()
{
    bool result = true;
    if (*(unsigned char*)((char*)this + 0x62) == 0) {
        int* p = (int*)((char*)this + 0x94);
        if (((p[1] - p[0]) >> 3) <= *(int*)((char*)this + 0xec)) {
            int v = *(int*)((char*)this + 0xf0);
            if (v == 0 && *(unsigned char*)((char*)this + 0x61) == 0 &&
                *(unsigned char*)((char*)this + 0x60) == 0)
                result = false;
        }
    }
    return result;
}

// @ 0x005227a0
void TickState::ClearPtr100()
{
    int** p = (int**)((char*)this + 0x100);
    if (*p != 0) {
        int* old = *p;
        *p = 0;
        if (old != 0)
            AtomicRefCounted_Release(old);
    }
}

// @ 0x005218e0 -- PARTIAL skeleton (239-byte /Od body not reconstructed)
void FUN_005218e0(void* self) { (void)self; }
// @ 0x005219d0 -- PARTIAL skeleton (455-byte /Od body not reconstructed)
void FUN_005219d0(void* self) { (void)self; }
// @ 0x00521ba0 -- PARTIAL skeleton (457-byte /Od body not reconstructed)
void FUN_00521ba0(void* self) { (void)self; }
// @ 0x00521d70 nSPSkinner::cPaintSystem::HandleUpdateMessage -- PARTIAL skeleton
void FUN_00521d70(void* self) { (void)self; }
