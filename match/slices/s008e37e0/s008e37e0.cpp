// 0x008e37e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s008e2dd0/s008e2dd0.cpp, src/game/UTFSpore_Win32/Document.cpp.

extern "C" unsigned char g_01436e7c[];
struct C_008e2f30 { void FUN_008e2f30(unsigned int, unsigned int, unsigned int, unsigned int); };
struct C_008e3660 { void FUN_008e3660(unsigned int); };
struct C_008e4480 { int FUN_008e4480(unsigned int, unsigned int); };
struct C_00e25bd0 { void FUN_00e25bd0(unsigned int, unsigned int); };

// @ 0x008e37e0
extern "C" int __fastcall FUN_008e37e0(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1004;
    int t1006;
    int t1007;
    int t1011;
    int v_l4;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1019;
    int t1023;
    int t1024;
    int t1028;
    t1002 = (int)((int)(self));
    if ((unsigned char)*(unsigned char*)((char*)(t1002) + 44) != (unsigned char)0) {
        t1003 = (int)(*(int*)((char*)(t1002) + 84));
        t1004 = (int)(*(int*)((char*)(t1002) + 80));
        t1006 = (int)(t1002 + (int)80);
        t1007 = (int)(t1006);
        ((C_00e25bd0*)(t1007))->FUN_00e25bd0((unsigned int)(t1004), (unsigned int)(t1003));
        t1011 = (int)(v_l4);
        t1012 = (int)(*(int*)((char*)(t1002) + 172));
        t1013 = (int)(*(int*)((char*)(t1002) + 168));
        t1014 = (int)(*(int*)((char*)(t1002) + 84));
        t1015 = (int)(t1006);
        ((C_008e2f30*)(t1015))->FUN_008e2f30((unsigned int)(t1014), (unsigned int)(t1013), (unsigned int)(t1012), (unsigned int)(t1011));
        t1019 = (int)(*(int*)((char*)(t1002) + 64));
        if (t1019 != (int)0) {
            t1023 = (int)((C_008e4480*)(t1019))->FUN_008e4480((unsigned int)((int)g_01436e7c), (unsigned int)((int)0));
            if (t1023 != (int)0) {
                t1024 = (int)(t1002);
                ((C_008e3660*)(t1024))->FUN_008e3660((unsigned int)(t1023));
            }
        }
        *(unsigned char*)((char*)(t1002) + 44) = (unsigned char)((int)0);
    }
    t1028 = (int)(t1002 + (int)80);
    return (int)(t1028);
}
