// Slice s00f455e0 -- partial skeletons for 0x00f45c30 and 0x00f46020.
// Kept in a separate translation unit so the matched wrappers in s00f455e0.cpp keep their
// out-of-line calls (a same-TU empty definition is inlined away by /O2).
#include "types.h"

struct Scenario9Part {
    char  pad00[0x10];
    void* mpManager;   // +0x10

    // @ 0x00f45c30
    void f45c30(int a, int b, int c, int d);
    // @ 0x00f46020
    int  f46020(int a, int b, int c, int d, int e);
};

// @ 0x00f45c30
// Scenario action-table update helper (916 bytes); not reconstructed.
void Scenario9Part::f45c30(int a, int b, int c, int d)
{
    (void)a; (void)b; (void)c; (void)d;
}

// @ 0x00f46020
// Scenario action-table update helper (997 bytes); not reconstructed.
int Scenario9Part::f46020(int a, int b, int c, int d, int e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    return 0;
}
