// s0046b8e0

struct Tbfd {
    int m();
};

extern "C" int FUN_0046b8e0(int, int, int);

// @ 0x0046bfd0
int FUN_0046bfd0(int a, int b)
{
    FUN_0046b8e0(a, b, ((Tbfd*)b)->m());
    return a;
}

// @ 0x0046b8e0
void F_0046b8e0() {}
