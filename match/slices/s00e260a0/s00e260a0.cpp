// 0x00e260a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPUIPosse.cpp, match/slices/s00e25710/s00e25710.cpp.

struct C_00e25fa0 { int FUN_00e25fa0(unsigned int); };

// @ 0x00e260a0
extern "C" void __fastcall FUN_00e260a0(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1004;
    unsigned char t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003) + 292));
    if (t1004 != (int)*(int*)((char*)(t1003) + 296)) {
        t1006 = (unsigned char)((unsigned char)(a4));
        do {
            t1007 = (int)(*(int*)((char*)(t1004)));
            t1008 = (int)(t1004 + (int)4);
            t1004 = (int)(t1004 + (int)16);
            if (t1006 == (unsigned char)0) {
                t1009 = (int)(*(int*)((char*)(t1008) + 8));
                if ((unsigned int)(t1009) <= (unsigned int)0) goto Le260da;
                if ((unsigned int)*(int*)((char*)(t1003) + 180) <= (unsigned int)(t1009)) goto Le260da;
            }
            t1010 = (int)(t1003);
            t1009 = (int)((C_00e25fa0*)(t1010))->FUN_00e25fa0((unsigned int)(t1007));
            Le260da:;
        } while (t1004 != (int)*(int*)((char*)(t1003) + 296));
    }
    return;
}
