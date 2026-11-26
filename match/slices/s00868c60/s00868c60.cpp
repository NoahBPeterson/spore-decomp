// 0x00868c60: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

// @ 0x00868c60
extern "C" int __cdecl FUN_00868c60(int a4)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    t1000 = (int)((int)(a4));
    t1001 = (int)((int)0);
    if (t1000 != t1001) {
        t1002 = (int)(*(int*)((char*)(t1000) + 28));
        if (t1002 != t1001) {
            *(int*)((char*)(t1002) + 28) = (int)(t1001);
            *(int*)((char*)(t1000) + 20) = (int)(t1001);
            *(int*)((char*)(t1000) + 8) = (int)(t1001);
            *(int*)((char*)(t1000) + 24) = (int)(t1001);
            *(int*)((char*)(t1000) + 48) = (int)((int)1);
            *(int*)((char*)(t1002)) = (int)(t1001);
            *(int*)((char*)(t1002) + 4) = (int)(t1001);
            *(int*)((char*)(t1002) + 12) = (int)(t1001);
            *(int*)((char*)(t1002) + 32) = (int)(t1001);
            *(int*)((char*)(t1002) + 40) = (int)(t1001);
            *(int*)((char*)(t1002) + 44) = (int)(t1001);
            *(int*)((char*)(t1002) + 48) = (int)(t1001);
            *(int*)((char*)(t1002) + 56) = (int)(t1001);
            *(int*)((char*)(t1002) + 60) = (int)(t1001);
            t1003 = (int)(t1002 + (int)1328);
            *(int*)((char*)(t1002) + 20) = (int)((int)32768);
            *(int*)((char*)(t1002) + 108) = (int)(t1003);
            *(int*)((char*)(t1002) + 80) = (int)(t1003);
            *(int*)((char*)(t1002) + 76) = (int)(t1003);
            t1004 = (int)((int)0);
            return (int)(t1004);
        }
    }
    t1005 = (int)((int)(-2));
    return (int)(t1005);
}
