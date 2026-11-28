// 0x00e00d20: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPUIGlobalUI.cpp, match/slices/s00e00760/s00e00760.cpp.

extern "C" unsigned char g_015fd918[];
extern "C" unsigned char g_01654c00[];
extern "C" unsigned char g_01654c05[];
struct C_006a25a0 { int FUN_006a25a0(unsigned int); };
struct C_00a98020 { int FUN_00a98020(); };
extern "C" int __cdecl FUN_00b5b800(...);
extern "C" int __cdecl FUN_00e00c40(...);
extern "C" int __cdecl FUN_01015df0(...);

// @ 0x00e00d20
extern "C" bool __cdecl FUN_00e00d20(void)
{
    int t1001;
    int t1006;
    int t1011;
    int t1014;
    bool t1017;
    bool t1018;
    t1001 = (int)FUN_00b5b800();
    if (t1001 != (int)g_01654c00) {
        t1001 = (int)FUN_00e00c40();
        if ((unsigned char)(t1001) == (unsigned char)0) {
            t1006 = (int)((int)(*(int*)g_015fd918));
            t1001 = (int)((C_006a25a0*)(t1006))->FUN_006a25a0((unsigned int)((int)(-713458672)));
            if ((unsigned char)(t1001) == (unsigned char)0) {
                t1001 = (int)FUN_00b5b800();
                if (t1001 == (int)g_01654c05) {
                    t1011 = (int)FUN_01015df0();
                    t1014 = (int)(t1011);
                    t1001 = (int)((C_00a98020*)(t1014))->FUN_00a98020();
                    if ((unsigned char)(t1001) != (unsigned char)0) goto Le00d68;
                }
            }
            t1017 = true;
            return (bool)(t1017);
        }
    }
    Le00d68:;
    t1018 = false;
    return (bool)(t1018);
}
