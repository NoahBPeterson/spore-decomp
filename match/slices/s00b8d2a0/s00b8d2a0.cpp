// 0x00b8d2a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPPlanetModel.cpp, match/slices/s00b8d190/s00b8d190.cpp.

struct C_00b8c330 { int FUN_00b8c330(unsigned int, unsigned int, unsigned int); };

// @ 0x00b8d2a0
extern "C" bool __fastcall FUN_00b8d2a0(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    bool t1002;
    bool t1003;
    int t1004;
    int t1005;
    bool t1009;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)28653541) {
        if (t1000 != (int)71583981) {
            if (t1000 != (int)73394578) goto Lb8d2cd;
            *(unsigned char*)((char*)((int)(self)) + 120) = (unsigned char)((int)1);
            t1002 = false;
            return (bool)(t1002);
        }
        *(unsigned char*)((char*)((int)(self)) + 234) = (unsigned char)((int)1);
        *(unsigned char*)((char*)((int)(self)) + 120) = (unsigned char)((int)1);
        Lb8d2cd:;
        t1003 = false;
        return (bool)(t1003);
    }
    t1004 = (int)((int)(a8));
    t1005 = (int)((int)0);
    if (t1004 != (int)0) {
        t1005 = (int)(*(int*)((char*)(t1004) + 8));
    }
    ((C_00b8c330*)((int)(self)))->FUN_00b8c330((unsigned int)((int)0), (unsigned int)((int)1), (unsigned int)(t1005));
    t1009 = true;
    return (bool)(t1009);
}
