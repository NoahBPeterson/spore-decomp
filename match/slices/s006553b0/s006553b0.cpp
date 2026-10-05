// slice s006553b0: SP::cSPUIAssetGrid update/animation methods.
// UI module: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" void FUN_00654050(void*, void*, void*);   // 0x00654050 (local vector ctor)
extern "C" int  FUN_006536e0(void*, void*, void*, void*, void*, void*, void*);  // filter
extern "C" int  FUN_00653780(int*, void*, int*, void*, void*, void*, int);      // copy_if
extern "C" void EASTL_allocator_deallocate(void*);   // 0xf47380

// @ 0x006553b0  cSPUIAssetGrid animation/update step (PARTIAL: 1158-byte body).
void FUN_006553b0(void* self) { (void)self; }

// @ 0x00655840  cSPUIAssetGrid layout step (PARTIAL: 691-byte body).
void FUN_00655840(void* self) { (void)self; }

// @ 0x00655b00  cSPUIAssetGrid load step (PARTIAL: 968-byte body).
void FUN_00655b00(void* self) { (void)self; }

// @ 0x00655ed0  SP::cSPUIAssetGrid::Update (PARTIAL: 880-byte per-frame update).
void FUN_00655ed0(void* self) { (void)self; }

// @ 0x00656240  filter-then-copy_if over 0x10-byte records
int FUN_00656240(int* first, int* last, int* keysBegin, int* keysEnd, void* attr) {
    char local[0x94];
    FUN_00654050(keysBegin, keysEnd, first);           // build temp key vector
    int* pos = (int*)FUN_006536e0((void*)first, (void*)last, local, local, 0, 0, 0);
    if (pos != last) {
        FUN_00654050(keysBegin, keysEnd, first);
        pos = (int*)FUN_00653780(pos + 4, last, pos, local, local, 0, 0);
    }
    if (keysBegin && keysBegin != (int*)attr)
        EASTL_allocator_deallocate(keysBegin);
    return (int)pos;
}
