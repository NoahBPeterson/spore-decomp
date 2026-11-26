// 0x006a27d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPPropertyList.cpp, match/slices/s006a22a0/s006a22a0.cpp.

struct C_006a2470 { int FUN_006a2470(unsigned int); };

// @ 0x006a27d0
extern "C" int __fastcall FUN_006a27d0(char* self, int edx_unused, int a4)
{
    int t1000;
    int t1004;
    int t1005;
    int t1006;
    t1000 = (int)((int)(a4));
    if ((unsigned int)(t1000) > (unsigned int)0) {
        if ((unsigned int)(t1000) < (unsigned int)*(int*)((char*)((int)(self)) + 56)) goto L6a27ec;
    }
    t1004 = (int)((C_006a2470*)((int)(self)))->FUN_006a2470((unsigned int)(t1000));
    if ((unsigned char)(t1004) == (unsigned char)0) {
        t1005 = (int)((int)0);
        return (int)(t1005);
    }
    L6a27ec:;
    t1006 = (int)((int)1);
    return (int)(t1006);
}
