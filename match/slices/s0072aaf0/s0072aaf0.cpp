// Slice s0072aaf0 — SP::cTriToRegionMap and mesh streaming helpers.
//   AddRegion reconstructed; the rest are partial.
#include "types.h"

void operator_delete(void* p);   // 0x00f47380

extern "C" {
    void* FUN_00f473a0(unsigned size, const char* name, int f, int df, const char* file, int line);
    void  FUN_007409d0(void* pos, void* value);
    void  FUN_0072a1a0();
    void  FUN_0072aa80();
}

struct TriRegionEntry {
    int mRegionId;   // +0
    int mBegin;      // +4
    int mEnd;        // +8
};

struct TriRegionVec {
    TriRegionEntry* mpBegin;
    TriRegionEntry* mpEnd;
    TriRegionEntry* mpCap;
};

struct cTriToRegionMap {
    TriRegionVec mRegions;
    void AddRegion(int begin, int end, int id);
};

// @ 0x0072b560  SP::cTriToRegionMap::AddRegion
void cTriToRegionMap::AddRegion(int param_2, int param_3, int param_4)
{
    if (param_4 != -1) {
    if (param_2 != param_3) {
        TriRegionEntry* p   = mRegions.mpBegin;
        TriRegionEntry* end = mRegions.mpEnd;
        int n = ((int)end - (int)p) / 0xc;
        int i = 0;
        if (0 < n) {
            do {
                if (p->mRegionId == param_4) {
                    if (p->mBegin == param_3) {
                        p->mBegin = param_2;
                        return;
                    }
                    if (p->mEnd == param_2) {
                        p->mEnd = param_3;
                        return;
                    }
                }
                i++;
                p++;
            } while (i < n);
        }

        TriRegionEntry tmp;
        tmp.mBegin = param_2;
        tmp.mEnd = param_3;
        tmp.mRegionId = param_4;
        if (end < mRegions.mpCap) {
            mRegions.mpEnd = end + 1;
            if (end != 0) {
                end->mRegionId = param_4;
                end->mBegin = param_2;
                end->mEnd = param_3;
                return;
            }
        } else {
            FUN_007409d0(end, &tmp);
        }
    }
    }
}

// @ 0x0072ac10  (PARTIAL)
void FUN_0072ac10(void* a, void* b)
{
    (void)a; (void)b;
}

// @ 0x0072ac60  (PARTIAL: refcounted ctor with EH)
void FUN_0072ac60(void* a, int b)
{
    (void)a; (void)b;
}

// @ 0x0072aaf0  (PARTIAL: vector insert with EH)
void FUN_0072aaf0(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// @ 0x0072ace0  SP::StreamMeshToRw  (PARTIAL)
void FUN_0072ace0(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}
