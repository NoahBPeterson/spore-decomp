// Slice s00903390: a free setter storing a pair of 32-bit values at +0x64 / +0x68 of its first argument.

struct Obj_s0090_3390 {
    char pad00[0x64];
    int mField64;  // +0x64
    int mField68;  // +0x68
};

// @ 0x00903390
void FUN_00903390(Obj_s0090_3390* p, int a, int b)
{
    p->mField64 = a;
    p->mField68 = b;
}
