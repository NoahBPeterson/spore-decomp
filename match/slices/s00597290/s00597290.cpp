// 0x00597290: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00597230/s00597230.cpp.

extern "C" unsigned char g_013eb430[];
extern "C" unsigned char g_013ebb38[];
struct C_005965e0 { void FUN_005965e0(unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00597290
extern "C" int __fastcall FUN_00597290(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1004;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1015;
    t1002 = (int)(*(int*)((char*)((int)(self)) + 28));
    if (t1002 != (int)0) {
        t1003 = (int)(*(int*)((char*)(t1002)));
        *(int*)((char*)((int)(self)) + 28) = (int)(t1003);
    } else {
        t1004 = (int)(*(int*)((char*)((int)(self)) + 44));
        t1007 = (int)FUN_00f473a0((unsigned int)(t1004), (unsigned int)((int)g_013eb430), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)g_013ebb38), (unsigned int)((int)209));
        t1002 = (int)(t1007);
    }
    if (t1002 != (int)0) {
        t1008 = (int)((int)(a4));
        t1009 = (int)(*(int*)((char*)(t1008)));
        t1010 = (int)(t1008 + (int)4);
        *(int*)((char*)(t1002)) = (int)(t1009);
        t1011 = (int)(t1002 + (int)4);
        ((C_005965e0*)(t1011))->FUN_005965e0((unsigned int)(t1010));
    }
    t1015 = (int)(t1002);
    *(int*)((char*)(t1002) + 224) = (int)((int)0);
    return (int)(t1015);
}
