// 0x008eaa20: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s008ea290/s008ea290.cpp, src/game/UTFSpore_Win32/Table.cpp, match/slices/s008f0740/s008f0740_g7.cpp.

struct C_008e9e30 { int FUN_008e9e30(unsigned int, float); };
struct C_008fba80 { int FUN_008fba80(); };
struct C_00928ba0 { int FUN_00928ba0(unsigned int); };

// @ 0x008eaa20
extern "C" void __fastcall FUN_008eaa20(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1004;
    int t1005;
    int t1008;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1017;
    int t1018;
    int t1020;
    int t1021;
    t1001 = (int)((int)(a8));
    t1004 = (int)((int)(self));
    if ((int)*(int*)((char*)(t1004) + 64) == (int)0) {
        t1005 = (int)(t1001);
        t1008 = (int)((C_008fba80*)(t1005))->FUN_008fba80();
        if ((unsigned char)(t1008) != (unsigned char)0) {
            t1010 = (int)(*(int*)((char*)(t1004) + 12));
            t1011 = (int)(*(int*)((char*)(t1010) + 8));
            t1012 = (int)(t1011 - (int)*(int*)((char*)(t1010) + 12));
            t1013 = (int)(t1012 - (int)56);
            if (t1013 < (int)0) {
                t1014 = (int)(t1010);
                t1017 = (int)((C_00928ba0*)(t1014))->FUN_00928ba0((unsigned int)((int)56));
                if ((unsigned char)(t1017) == (unsigned char)0) goto L8eaa65;
            }
            t1008 = (int)(*(int*)((char*)(t1010) + 12));
            t1018 = (int)(t1008 + (int)56);
            *(int*)((char*)(t1010) + 12) = (int)(t1018);
            *(int*)((char*)(t1010) + 16) = (int)(t1018);
            if (t1008 != (int)0) goto L8eaa67;
            L8eaa65:;
            t1008 = (int)((int)0);
            L8eaa67:;
            *(int*)((char*)(t1004) + 64) = (int)(t1008);
        }
    }
    t1020 = (int)(*(int*)((char*)(t1004) + 64));
    if (t1020 != (int)0) {
        t1021 = (int)((int)(a4));
        t1008 = (int)((C_008e9e30*)(t1020))->FUN_008e9e30((unsigned int)(t1001), (float)(*(float*)((char*)(t1021) + 1336)));
    }
    return;
}
