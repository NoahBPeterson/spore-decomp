// 0x009600a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0095ff20/s0095ff20.cpp, src/game/UTFSpore_Win32/Window.cpp.

struct C_00958820 { int FUN_00958820(unsigned int); };

// @ 0x009600a0
extern "C" int __fastcall FUN_009600a0(char* self, int edx_unused)
{
    int t1001;
    unsigned char t1002;
    unsigned char t1;
    unsigned char t3;
    unsigned char t5;
    int t1003;
    int t1004;
    t1001 = (int)((int)(self));
    t1002 = (unsigned char)(*(unsigned char*)((char*)(t1001) + 44));
    t1 = (unsigned char)(t1002 & (unsigned char)4);
    if (t1 == (unsigned char)0) {
        t3 = (unsigned char)(t1002 & (unsigned char)1);
        if (t3 == (unsigned char)0) {
            t5 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1001) + 40) & (unsigned char)1);
            if (t5 == (unsigned char)0) goto L9600c5;
        }
        t1003 = (int)(*(int*)((char*)(t1001) + 48));
        if (t1003 != (int)0) {
            t1004 = (int)(t1001 + (int)(-4));
            t1001 = (int)((C_00958820*)(t1003))->FUN_00958820((unsigned int)(t1004));
        }
    }
    L9600c5:;
    return (int)(t1001);
}
