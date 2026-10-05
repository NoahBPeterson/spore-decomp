// Slice s007403c0 (0x007403c0-0x007411b0): SP::cModelInstance bone/region accessors.
// Region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar floats, EH frames).
#include "types.h"

// External callees (masked relocations).
extern "C" void FUN_007c5490();
extern "C" void FUN_01200940();
extern "C" void FUN_0042dd00();          // eastl rb-tree LowerBound
extern "C" void FUN_011e0744();          // eastl::vector<bool>::DoInsertValue
extern "C" void FUN_00a11310();
void __cdecl EASTL_allocator_deallocate(void* p);   // 0xf47380
extern "C" void* __cdecl operator_new_ea(unsigned size, const char*, int, int, const char*, int);

// ---------------------------------------------------------------------------
// @ 0x007411b0  eastl::vector<12-byte POD>::push_back
// ---------------------------------------------------------------------------
struct Vec12 { int a, b, c; };

struct Vec12Vector {
    Vec12* mpBegin;                  // +0x0
    Vec12* mpEnd;                    // +0x4
    Vec12* mpCapacity;               // +0x8
    void push_back(const Vec12& value);
    void DoInsertValue(Vec12* pos, const Vec12& value);   // 0x7409d0
};

void Vec12Vector::push_back(const Vec12& value)
{
    Vec12* p = mpEnd;
    if (p < mpCapacity) {
        mpEnd = p + 1;
        if (p != 0) {
            p->a = value.a;
            p->b = value.b;
            p->c = value.c;
        }
        return;
    }
    DoInsertValue(p, value);
}

// ===========================================================================
// Remaining bone/region/destructor functions (large; reconstruction in progress).
// ===========================================================================
struct cModelInstance_Bones {
    char pad[0x154];
    int  GetBoneTransforms(int a2, int a3);            // 0x740550
    int  GetBoneIDs(void* a2);                          // 0x740740
    void BoneSub3c0(int a2);                            // 0x7403c0
    void BoneSub7d0(int a2, int a3);                    // 0x7407d0
    void BoneSub9d0(void* a2, void* a3);                // 0x7409d0
    void Dtor();                                        // 0x740b00
    void Subcc0(int a2);                                // 0x740cc0
    void Sube90(int a2);                                // 0x740e90
    void DispatchRegion();                              // 0x741040
    void* GetRegionMaterialInfo(int a2);                // 0x741150
};

// @ 0x007403c0
void cModelInstance_Bones::BoneSub3c0(int a2) { (void)a2; }

// @ 0x00740550
int cModelInstance_Bones::GetBoneTransforms(int a2, int a3) { (void)a2; (void)a3; return 0; }

// @ 0x00740740
int cModelInstance_Bones::GetBoneIDs(void* a2) { (void)a2; return 0; }

// @ 0x007407d0
void cModelInstance_Bones::BoneSub7d0(int a2, int a3) { (void)a2; (void)a3; }

// @ 0x007409d0
void cModelInstance_Bones::BoneSub9d0(void* a2, void* a3) { (void)a2; (void)a3; }

// @ 0x00740b00
void cModelInstance_Bones::Dtor() {}

// @ 0x00740cc0
void cModelInstance_Bones::Subcc0(int a2) { (void)a2; }

// @ 0x00740e90
void cModelInstance_Bones::Sube90(int a2) { (void)a2; }

// @ 0x00741040
void cModelInstance_Bones::DispatchRegion() {}

// @ 0x00741150
void* cModelInstance_Bones::GetRegionMaterialInfo(int a2) { (void)a2; return 0; }
