// 0x0112e1e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0112dca0/s0112dca0.cpp, src/game/plugins/sndplayer1.cpp.cpp.

struct C_011e7b70 { int FUN_011e7b70(); };

// @ 0x0112e1e0
extern "C" int __stdcall FUN_0112e1e0(int a4)
{
    int t1001;
    int t1002;
    int t1003;
    t1001 = (int)((int)(a4));
    *(unsigned short*)((char*)(t1001) + 24) -= (unsigned short)1;
    t1002 = (int)(*(unsigned short*)((char*)(t1001) + 24));
    if ((unsigned short)(t1002) == (unsigned short)0) {
        t1003 = (int)(*(int*)((char*)(t1001) + 20));
        t1002 = (int)((C_011e7b70*)(t1003))->FUN_011e7b70();
        *(unsigned char*)((char*)(t1001) + 26) = (unsigned char)((int)0);
    }
    return (int)(t1002);
}
