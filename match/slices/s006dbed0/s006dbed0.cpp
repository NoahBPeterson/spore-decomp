// Slice s006dbed0: PARTIAL.
// 0x006dbed0 is a single 4,988-byte mesh/attribute bake pipeline driver. The
// entry validation, refcount protocol and the top-level element-table lookups
// are reconstructed here; the main build/loop body (element iteration, vertex
// stream assembly, primitive finding, material/shader binding and the calls to
// the 0x006dxxxx bake entry points) is not reconstructed. See partial.txt.

#include "../s006ccf50/s006ccf50.h"

struct PipelineObj
{
    virtual void slot0();
    virtual void Release(int flags);   // +0x04 vtable slot

    uint32_t mRefCount;    // +4
    uint32_t mPad8;
    uint32_t mBase;        // +8   element table base
    uint32_t mPadC;
    uint32_t mPad10;
    uint32_t mPad14;
    uint32_t mBegin7;      // +1c  element array begin
    uint32_t mEnd8;        // +20  element array end

    void AddRef();
};

int __cdecl FUN_0071ddc0(void* obj, int code, int a, int b, int c);

void FUN_006dbed0(PipelineObj* obj, int param_2, void* param_3)   // @ 0x006dbed0
{
    if (obj != 0)
        obj->AddRef();

    int iVar7 = FUN_0071ddc0(obj, 0x15, 0, 6, 8);
    int iVar8 = FUN_0071ddc0(obj, 0x14, 0, 6, 8);
    int iVarC = FUN_0071ddc0(obj, 1, 0, 3, 0xe);

    if (iVar7 < 0 || iVar8 < 0 || iVarC < 0 || obj->mBegin7 == obj->mEnd8)
    {
        if (obj != 0)
            obj->Release(1);
        return;
    }

    // NOTE: main pipeline body omitted (partial reconstruction).
    (void)param_2;
    (void)param_3;

    if (obj != 0)
        obj->Release(1);
}
