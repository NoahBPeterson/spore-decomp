// 0x0096f240: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/FrameDrawable.cpp, match/slices/s0096e3a0/s0096e3a0.cpp.

struct C_00951240 { int FUN_00951240(unsigned int); };

// @ 0x0096f240
extern "C" int __fastcall FUN_0096f240(char* self, int edx_unused, int a4)
{
    int t1000;
    int t5;
    int t1002;
    int t1003;
    int t1004;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)51205292) {
        if (t1000 != (int)(-289045630)) {
            *(int*)&(a4) = (int)(t1000);
            t5 = (int)((C_00951240*)((int)(self)))->FUN_00951240((unsigned int)((int)(a4)));
            return (int)(t5);
        }
        if ((int)(self) != (int)0) {
            t1002 = (int)((int)(self) + (int)4);
            return (int)(t1002);
        }
        t1003 = (int)((int)0);
        return (int)(t1003);
    }
    t1004 = (int)((int)(self));
    return (int)(t1004);
}
