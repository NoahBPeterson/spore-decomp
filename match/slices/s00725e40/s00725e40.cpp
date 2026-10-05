// Slice s00725e40 — mesh connectivity helpers.
//   00725e40: giant /O2 builder with EH (partial).
//   007269b0: eastl::vector<SP::cClusterInfo, sp_vector_allocator>::DoInsertValues
//             (element stride 0x64) — reconstructed from the decompile.
#include "types.h"

extern "C" {
    int   FUN_0071ddc0(void* p, int a, int b, int c, int d);
    int   FUN_0071e040(void* p, int idx, int id);
    void  FUN_007249f0(void* p);
    void  FUN_00725130(void* p);
    void* FUN_00f473a0(unsigned n, const char* name, int f, int df, const char* file, int line);
    void  FUN_00f47380(void* p);
    int   FUN_00721f50(int src, int srcEnd, int dst);
    void  FUN_00720e60(int src, int srcEnd, int dst);
    void  FUN_00721ed0(int dst, unsigned n, int value, int dst2);
    void  FUN_00721d80(int value);
    void  FUN_00721e50(void* p, ...);
    void  FUN_00722ac0(int src, int srcEnd, int dst);
    void  FUN_00723bf0(int first, int last, int tmp);
}

// @ 0x00725e40  (PARTIAL — giant /O2 connectivity builder)
void FUN_00725e40(void* param_1)
{
    // The original resolves a job via FUN_0071ddc0, walks the 0x8c mesh records and
    // rebuilds the edge/adjacency structures. Not reconstructed.
    (void)param_1;
}

// @ 0x007269b0
// eastl::vector<SP::cClusterInfo, eastl::sp_vector_allocator>::DoInsertValues(position, n, value)
// (element size 100, vector header = begin/end/cap).
void FUN_007269b0(int* param_1, int param_2, unsigned param_3, int param_4)
{
    if ((unsigned)((param_1[2] - param_1[1]) / 100) < param_3) {
        int   count = (param_1[1] - *param_1) / 100;   // current size
        unsigned cap = count * 2;
        if (count == 0)
            cap = 1;
        unsigned need = count + param_3;
        if (need < cap)
            need = cap;
        int newBuf;
        if (need == 0)
            newBuf = 0;
        else
            newBuf = (int)FUN_00f473a0(need * 100, "Graphics", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        int oldEnd = param_1[1];
        int oldBeg = *param_1;
        int mid = FUN_00721f50(oldBeg, param_2, newBuf);
        FUN_00720e60(oldBeg, param_2, newBuf);
        FUN_00721ed0(mid, param_3, param_4, mid);      // fill n values
        int afterFill = param_3 * 100 + mid;
        int pos = param_1[1];
        FUN_00721f50(pos, oldEnd, afterFill);          // relocate [pos,end)
        FUN_00720e60(pos, oldEnd, afterFill);
        (void)oldEnd;
        if (oldBeg && *(int*)(oldBeg - 4) != 0)
            FUN_00f47380((void*)oldBeg);
        param_1[1] = afterFill;
        *param_1 = newBuf;
        param_1[2] = need * 100 + newBuf;
    } else if (param_3 != 0) {
        FUN_00721d80(param_4);
        int   end  = param_1[1];
        unsigned old = (unsigned)((param_1[1] - param_2) / 100);
        if (param_3 < old) {
            int cut = end + param_3 * -100;
            FUN_00721e50(&param_4, cut, end, end);
            int oldPos = param_2;
            param_1[1] = param_1[1] + param_3 * 100;
            FUN_00722ac0(param_2, cut, end);
            FUN_00723bf0(oldPos, param_3 * 100 + oldPos, 0);
        } else {
            FUN_00721ed0(end, param_3 - old, 0, param_2);
            int oldPos = param_2;
            param_1[1] = param_1[1] + (param_3 - old) * 100;
            FUN_00721e50(&param_2, param_2, end, param_1[1], param_2);
            param_1[1] = param_1[1] + old * 100;
            FUN_00723bf0(oldPos, end, 0);
        }
    }
}
