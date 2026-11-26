// 0x00b02350: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPPlanet.cpp, match/slices/s00b01690/s00b01690.cpp.

struct C_00702da0 { int FUN_00702da0(unsigned int); };
struct C_00703d50 { int FUN_00703d50(float, unsigned int, unsigned int); };
struct C_00b02120 { int FUN_00b02120(); };

// @ 0x00b02350
extern "C" void __fastcall FUN_00b02350(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1010;
    int t1011;
    int t1012;
    int t1015;
    int t1018;
    int t1019;
    t1001 = (int)((int)(a8));
    t1004 = (int)((int)(self));
    if (t1001 != (int)0) {
        t1005 = (int)(*(int*)((char*)(t1004) + 91392));
        if (t1005 != (int)0) {
            t1006 = (int)(*(int*)((char*)(t1005) + 36));
            if (t1006 == (int)*(int*)((char*)(t1005) + 40)) {
                t1007 = (int)(t1004);
                t1005 = (int)((C_00b02120*)(t1007))->FUN_00b02120();
            }
            if ((unsigned char)(a4) != (unsigned char)0) {
                if ((int)*(int*)((char*)(t1001) + 120) != (int)(-1)) goto Lb023cb;
                t1010 = (int)(*(int*)((char*)(t1004) + 91392));
                t1011 = (int)(*(int*)((char*)(t1010) + 36));
                if (t1011 == (int)*(int*)((char*)(t1010) + 40)) goto Lb023cb;
                t1012 = (int)(t1001 + (int)16);
                t1015 = (int)((C_00703d50*)(t1010))->FUN_00703d50((float)(*(float*)((char*)(t1001) + 108)), (unsigned int)(t1012), (unsigned int)(t1001));
                *(int*)((char*)(t1001) + 120) = (int)(t1015);
                return;
            }
            t1005 = (int)(*(int*)((char*)(t1001) + 120));
            if (t1005 >= (int)0) {
                t1018 = (int)(*(int*)((char*)(t1004) + 91392));
                t1019 = (int)(*(int*)((char*)(t1018) + 36));
                if (t1019 != (int)*(int*)((char*)(t1018) + 40)) {
                    t1005 = (int)((C_00702da0*)(t1018))->FUN_00702da0((unsigned int)(t1005));
                }
                *(int*)((char*)(t1001) + 120) = (int)((int)(-1));
            }
        }
    }
    Lb023cb:;
    return;
}
