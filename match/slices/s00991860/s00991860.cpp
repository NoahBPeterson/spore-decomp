// 0x00991860: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/TreeView.cpp, match/slices/s009913d0/s009913d0.cpp.

struct C_00991520 { int FUN_00991520(unsigned int, unsigned int); };

// @ 0x00991860
extern "C" int __fastcall FUN_00991860(char* self, int edx_unused)
{
    int t1001;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1010;
    t1001 = (int)((int)(self) + (int)36);
    if (t1001 != (int)0) {
        t1004 = (int)(t1001 + (int)(-12));
    } else {
        t1004 = (int)((int)0);
    }
    t1005 = (int)(*(int*)((char*)(t1001)));
    if (t1005 != (int)0) {
        t1006 = (int)(t1005 + (int)(-12));
    } else {
        t1006 = (int)((int)0);
    }
    if (t1006 != t1004) {
        do {
            t1007 = (int)(t1006);
            t1005 = (int)((C_00991520*)(t1007))->FUN_00991520((unsigned int)((int)1), (unsigned int)((int)0));
            t1010 = (int)(*(int*)((char*)(t1006) + 12));
            if (t1010 != (int)0) {
                t1006 = (int)(t1010 + (int)(-12));
            } else {
                t1006 = (int)((int)0);
            }
        } while (t1006 != t1004);
    }
    return (int)(t1005);
}
