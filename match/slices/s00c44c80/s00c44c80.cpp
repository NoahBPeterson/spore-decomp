// Slice s00c44c80 -- stub object predicate.
// MSVC 2008 /O2, plain __thiscall: one field compare against 3.
//
// The original returns 'xor eax,eax; cmp [ecx+0x84],3; sete al; ret'.

struct CStub {
    char  pad00[0x84];
    int   m84;                                              // +0x84
    bool  FUN_00c44c80();                                   // 0x00c44c80
};

// @ 0x00c44c80
bool CStub::FUN_00c44c80()
{
    return m84 == 3;
}
