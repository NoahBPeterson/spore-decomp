// Slice s00e52a00: SP::cCellGame cell-command list shuffle.
// Optimised: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
//
// The caller (0x00e71520) leaves the element count in EAX and the array base in EDI
// before `call 0x00e52a00`, so this is a TU-local static helper with the compiler's
// register convention (arg1 EAX, arg2 kept in a callee-saved register across the RNG
// call). A same-TU stand-in caller keeps it out of line.
typedef unsigned int uint32_t;

class RandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(uint32_t limit);   // 0x00a68fb0
};

extern RandomLinearCongruential sMathRandom;        // 0x01601760

// @ 0x00e52a00
static __declspec(noinline) void ShuffleCells(int count, int* cells)
{
    if (count <= 1)
        return;
    int limit = count - 1;
    int* p = cells + count - 1;
    int n = limit;
    do {
        int j = (int)sMathRandom.RandomUint32Uniform(limit);
        int tmp = *p;
        int old = cells[j];
        cells[j] = tmp;
        *p = old;
        --p;
    } while (--n);
}

// stand-in caller: keeps ShuffleCells out of line and gives it the register convention
void ShuffleCellsCaller(int count, int* cells)
{
    ShuffleCells(count, cells);
}
