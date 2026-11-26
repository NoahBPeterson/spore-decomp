// 0x00b2b6d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00b2a8d0/s00b2a8d0.cpp.

struct C_00a057f0 { int FUN_00a057f0(unsigned int, unsigned int); };

// @ 0x00b2b6d0
extern "C" int __fastcall FUN_00b2b6d0(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1002;
    int t1004;
    int t1011;
    int t1013;
    int t1015;
    int t1016;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 12));
    t1002 = (int)((int)(a8));
    t1004 = (int)((int)(self) + (int)4);
    if (t1001 != (int)0) {
        do {
            if ((unsigned __int64)*(__int64*)((char*)(t1002)) < (unsigned __int64)*(__int64*)((char*)(t1001) + 16)) {
                t1004 = (int)(t1001);
                t1001 = (int)(*(int*)((char*)(t1001) + 4));
            } else {
                t1001 = (int)(*(int*)((char*)(t1001)));
            }
        } while (t1001 != (int)0);
    }
    t1011 = (int)((int)&a8);
    t1013 = (int)((C_00a057f0*)((int)(self)))->FUN_00a057f0((unsigned int)(t1011), (unsigned int)(t1002));
    t1015 = (int)(*(int*)((char*)(t1013)));
    t1016 = (int)((int)(a4));
    *(int*)((char*)(t1016) + 4) = (int)(t1004);
    *(int*)((char*)(t1016)) = (int)(t1015);
    return (int)(t1016);
}
