// 0x00920c20: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/_at_00920000.cpp, match/slices/s009205e0/s009205e0.cpp.

// @ 0x00920c20
extern "C" bool __cdecl FUN_00920c20(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    bool t1004;
    bool t1005;
    t1000 = (int)((int)(a4));
    t1001 = (int)((int)(a8));
    if ((unsigned int)(t1000) < (unsigned int)(t1001)) {
        L920c30:;
        t1002 = (int)(*(unsigned short*)((char*)(t1000)));
        if ((unsigned short)(t1002) == (unsigned short)58) goto L920c52;
        t1003 = (int)((unsigned short)(t1002));
        if ((unsigned short)(t1003) != (unsigned short)92) {
            if ((unsigned short)(t1003) != (unsigned short)47) {
                t1000 = (int)(t1000 + (int)2);
                if ((unsigned int)(t1000) < (unsigned int)(t1001)) goto L920c30;
            }
        }
    }
    t1004 = false;
    return (bool)(t1004);
    L920c52:;
    t1005 = true;
    return (bool)(t1005);
}
