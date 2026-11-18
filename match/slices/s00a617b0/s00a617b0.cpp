// Slice s00a617b0: a free accessor returning the 32-bit field at +0x2c of its argument.

struct Obj_s00a6_17b0 {
    char pad00[0x2c];
    int mField2c;  // +0x2c
};

// @ 0x00a617b0
int FUN_00a617b0(Obj_s00a6_17b0* p)
{
    return p->mField2c;
}
