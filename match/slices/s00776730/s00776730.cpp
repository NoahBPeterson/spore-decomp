// slice s00776730: shader-profile / cRuntimeModelBuilder helpers.  Only
// VSProfileFromVersion is reconstructed; the rest are EH/loop-heavy routines
// kept as skeletons (partial).
#include "types.h"

// @ 0x007776c0  SP::VSProfileFromVersion
extern char g_vsProfile[];   // 0x01539eb8 ("vs_x_x")
char* VSProfileFromVersion(unsigned int version) {
    int lo = (int)(version & 0xff);
    g_vsProfile[3] = (char)(version >> 8) + '0';
    char c = (char)lo;
    if (lo < 10)
        c = c + '0';
    g_vsProfile[5] = c;
    return g_vsProfile;
}

// ---------------------------------------------------------------------------
// Skeletons (partial).
// ---------------------------------------------------------------------------
void FUN_00776730(int a) { (void)a; }
void FUN_00776920(int a, int b) { (void)a; (void)b; }
int  FUN_00776a60(int a) { (void)a; return 0; }
void FUN_00776e60(int a, int b) { (void)a; (void)b; }
void FUN_00776f40(int a, int b, int c) { (void)a; (void)b; (void)c; }
void FUN_00777060(int a) { (void)a; }
void FUN_00777130(int a, int b) { (void)a; (void)b; }
void FUN_007771f0(int a) { (void)a; }
int  FUN_00777290(int a) { (void)a; return 0; }
void FUN_007773c0(int a, int b) { (void)a; (void)b; }
void FUN_007775a0(int a) { (void)a; }
