// 0x00e4fd30: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e4f860/s00e4f860.cpp.

// @ 0x00e4fd30
extern "C" int __cdecl FUN_00e4fd30(int a4)
{
    int t1000;
    int t1001;
    int t1003;
    int t1004;
    int t1005;
    int t1007;
    t1000 = (int)((int)(a4));
    t1001 = (int)((int)(-2));
    t1003 = (int)(t1001 - t1000);
    t1004 = (int)((int)13);
    do {
        t1005 = (int)(t1003 + t1000);
        switch ((unsigned int)(t1005)) { case 0: case 2: case 3: case 4: case 5: case 6: case 8: goto Le4fd57; case 1: case 7: goto Le4fd5c; default: goto Le4fd5c; }
        goto Le4fd57;
        goto Le4fd5c;
        Le4fd57:;
        *(unsigned char*)((char*)(t1000)) = (unsigned char)((int)1);
        goto Le4fd5f;
        Le4fd5c:;
        *(unsigned char*)((char*)(t1000)) = (unsigned char)((int)0);
        Le4fd5f:;
        t1000 = (int)(t1000 + (int)1);
        t1004 = (int)(t1004 - (int)1);
    } while (t1004 != (int)0);
    t1007 = (int)(t1004 + (int)13);
    return (int)(t1007);
}
