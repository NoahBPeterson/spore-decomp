// 0x00b2bf90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00b2b8a0/s00b2b8a0.cpp.

struct C_00b2b720 { void FUN_00b2b720(unsigned int, unsigned int, unsigned int, unsigned int); };

// @ 0x00b2bf90
extern "C" int __fastcall FUN_00b2bf90(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1001;
    int t1004;
    int t1005;
    int t1010;
    int t1015;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 12));
    t1004 = (int)((int)(a8));
    t1005 = (int)((int)(self) + (int)4);
    if (t1001 != (int)0) {
        do {
            t1005 = (int)(t1001);
            if ((unsigned __int64)*(__int64*)((char*)(t1004)) < (unsigned __int64)*(__int64*)((char*)(t1001) + 16)) {
                t1001 = (int)(*(int*)((char*)(t1001) + 4));
            } else {
                t1001 = (int)(*(int*)((char*)(t1001)));
            }
        } while (t1001 != (int)0);
    }
    t1010 = (int)((int)(a4));
    ((C_00b2b720*)((int)(self)))->FUN_00b2b720((unsigned int)(t1010), (unsigned int)(t1005), (unsigned int)(t1004), (unsigned int)((int)0));
    t1015 = (int)(t1010);
    return (int)(t1015);
}
