// @ 0x00d7cd60
// cdecl with six arguments: calls the thiscall method 0xc12190 (ret 0xc) on the first
// argument with (0x7c7a9f7, 1, -1), stores the result through the sixth argument and
// returns true.
struct ThisX_00d7cd60 {
    int Callee_00c12190(int a, int b, int c);       // 0xc12190 (__thiscall, ret 0xc)
};

bool FUN_00d7cd60(ThisX_00d7cd60* a, int b, int c, int d, int e, int* out)
{
    *out = a->Callee_00c12190(0x7c7a9f7, 1, -1);
    return true;
}
