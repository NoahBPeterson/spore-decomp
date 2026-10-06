// Slice s00f455e0 -- unnamed scenario/action system, slice 9 of bfs1.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

struct Mgr {
    void FUN_b22960();     // 0x00b22960
};
void* __cdecl SP_NounManager();   // 0x00b3d300

struct Scenario9 {
    char  pad00[0x10];
    void* mpManager;                                 // +0x10
    char  pad14[0x18 - 0x14];
    int   mField18;                                  // +0x18
    char  pad1c[0x2c - 0x1c];
    char  mField2C;                                  // +0x2c
    char  pad2d[0x3c - 0x2d];
    int   mField3C;                                  // +0x3c

    void Sub41300();                                 // 0x00f41300
    void Sub3cf10(int);                              // 0x00f3cf10
    int  f44fe0();                                   // 0x00f44fe0
    void f45c30(int a, int b, int c, int d);         // 0x00f45c30 (defined in _partial.cpp)
    int  f46020(int a, int b, int c, int d, int e);  // 0x00f46020 (defined in _partial.cpp)

    void f455e0(int a);                              // 0x00f455e0
    void f45970();                                   // 0x00f45970
    void f45a80();                                   // 0x00f45a80
    int  f45b50();                                   // 0x00f45b50
    void f45fd0(int a, int b, char c);               // 0x00f45fd0
    void f46410(int a, int b, int c);                // 0x00f46410
    int  f46450(int a);                              // 0x00f46450
};

// @ 0x00f45fd0
void Scenario9::f45fd0(int a, int b, char c)
{
    if (c == 0)
        Sub41300();
    f45c30(a, b, 1, 1);
    ((Mgr*)SP_NounManager())->FUN_b22960();
    f45c30(a, b, 0, 0);
}

// @ 0x00f46410
void Scenario9::f46410(int a, int b, int c)
{
    f46020(a, b, c, 1, 1);
    ((Mgr*)SP_NounManager())->FUN_b22960();
    f46020(a, b, c, 0, 0);
}

// ---------------------------------------------------------------- large routines (partial skeletons)
// @ 0x00f455e0
void Scenario9::f455e0(int a)
{
    (void)a;
}

// @ 0x00f45970
void Scenario9::f45970()
{
}

// @ 0x00f45a80
void Scenario9::f45a80()
{
}

// @ 0x00f45b50
int Scenario9::f45b50()
{
    return 0;
}

// 0x00f45c30 and 0x00f46020 are partial skeletons defined in s00f455e0_partial.cpp; they are
// intentionally left undefined here so the matched 0x00f45fd0 / 0x00f46410 wrappers keep their
// out-of-line calls.

// @ 0x00f46450
int Scenario9::f46450(int a)
{
    (void)a;
    return -1;
}
