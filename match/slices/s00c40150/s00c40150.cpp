// 0x00c40150: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPOrnament.cpp, match/slices/s00c3ee20/s00c3ee20.cpp.

extern "C" unsigned char g_013f94d4[];
struct C_00c3f850 { int FUN_00c3f850(unsigned int); };

// @ 0x00c40150
extern "C" int __fastcall FUN_00c40150(char* self, int edx_unused, int a4)
{
    int t1000;
    int t6;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)g_013f94d4) {
        if (t1000 != (int)60969241) {
            if (t1000 != (int)137786407) {
                *(int*)&(a4) = (int)(t1000);
                t6 = (int)((C_00c3f850*)((int)(self)))->FUN_00c3f850((unsigned int)((int)(a4)));
                return (int)(t6);
            }
            if ((int)(self) == (int)0) goto Lc40191;
            t1002 = (int)((int)(self) + (int)304);
            return (int)(t1002);
        }
        t1003 = (int)((int)(self));
        return (int)(t1003);
    }
    if ((int)(self) != (int)0) {
        t1004 = (int)((int)(self) + (int)368);
        return (int)(t1004);
    }
    Lc40191:;
    t1005 = (int)((int)0);
    return (int)(t1005);
}
