// @ 0x00ec00c0
// reads the argument into ecx and calls the thiscall method 0xb18530 (no stack
// arguments); returns 0.0f when it returned nonzero, 1.0f when zero.
// Flags: /O2 /MD /Gy /TP /fp:fast
struct S_00ec00c0 {
    int F_00b18530();                            // 0xb18530 (__thiscall, no args)
};

float FUN_00ec00c0(S_00ec00c0* p)
{
    if (!p->F_00b18530())
        return 1.0f;
    return 0.0f;
}
