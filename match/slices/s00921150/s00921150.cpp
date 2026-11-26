// 0x00921150: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/_at_00920000.cpp, match/slices/s009205e0/s009205e0.cpp.

extern "C" unsigned char g_01667b88[];
struct C_00672750 { void FUN_00672750(unsigned int, unsigned int); };
struct C_008e3f10 { void FUN_008e3f10(unsigned int); };
extern "C" int __cdecl FUN_00920c20(...);

// @ 0x00921150
extern "C" int __cdecl FUN_00921150(int a4, int a8, int a12)
{
    int t1001;
    int t1003;
    int t1004;
    int t1006;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1019;
    int t1023;
    int t1027;
    int t1028;
    int t1029;
    int t1033;
    int t1037;
    t1001 = (int)((int)(a12));
    t1003 = (int)((int)(a8));
    if (t1001 == (int)(*(int*)g_01667b88)) {
        t1004 = (int)(t1003);
        if ((unsigned short)*(unsigned short*)((char*)(t1003)) != (unsigned short)0) {
            do {
                t1004 = (int)(t1004 + (int)2);
            } while ((unsigned short)*(unsigned short*)((char*)(t1004)) != (unsigned short)0);
        }
        t1001 = (int)(t1004);
    }
    if (t1003 == t1001) {
        t1006 = (int)((int)(a4));
        return (int)(t1006);
    }
    if ((unsigned int)(t1003) < (unsigned int)(t1001)) {
        t1013 = (int)FUN_00920c20((unsigned int)(t1003), (unsigned int)(t1001));
        if ((unsigned char)(t1013) == (unsigned char)0) {
            if ((unsigned int)(t1001) <= (unsigned int)(t1003)) goto L9211d0;
            t1014 = (int)(*(unsigned short*)((char*)(t1003)));
            if ((unsigned short)(t1014) != (unsigned short)92) {
                if ((unsigned short)(t1014) != (unsigned short)47) goto L9211d0;
            }
        }
        t1015 = (int)((int)(a4));
        t1016 = (int)(*(int*)((char*)(t1015)));
        if (t1016 == (int)*(int*)((char*)(t1015) + 4)) goto L9211f4;
        t1017 = (int)((int)0);
        *(unsigned short*)((char*)(t1016)) = (unsigned short)((unsigned short)(t1017));
        t1018 = (int)(*(int*)((char*)(t1015)));
        t1019 = (int)(t1015);
        *(int*)((char*)(t1015) + 4) = (int)(t1018);
        ((C_00672750*)(t1019))->FUN_00672750((unsigned int)(t1003), (unsigned int)(t1001));
        t1023 = (int)(t1015);
        return (int)(t1023);
    }
    L9211d0:;
    t1015 = (int)((int)(a4));
    t1027 = (int)(*(int*)((char*)(t1015) + 4));
    if ((int)*(int*)((char*)(t1015)) != t1027) {
        t1028 = (int)(*(unsigned short*)((char*)(t1027) - 2));
        if ((unsigned short)(t1028) == (unsigned short)92) goto L9211f4;
        if ((unsigned short)(t1028) == (unsigned short)47) goto L9211f4;
    }
    t1029 = (int)(t1015);
    ((C_008e3f10*)(t1029))->FUN_008e3f10((unsigned int)((int)92));
    L9211f4:;
    t1033 = (int)(t1015);
    ((C_00672750*)(t1033))->FUN_00672750((unsigned int)(t1003), (unsigned int)(t1001));
    t1037 = (int)(t1015);
    return (int)(t1037);
}
