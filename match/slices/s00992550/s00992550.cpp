// 0x00992550: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/WatchGraph.cpp, match/slices/s00992480/s00992480.cpp.

extern "C" unsigned char g_01445f58[];
extern "C" unsigned char g_01446078[];
struct C_00620230 { void FUN_00620230(); };
extern "C" void __cdecl FUN_00951330(...);
struct C_00962740 { void FUN_00962740(); };
struct C_00991f90 { void FUN_00991f90(); };

// @ 0x00992550
extern "C" int __fastcall FUN_00992550(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1006;
    int t1010;
    unsigned char t4;
    int t1017;
    t1002 = (int)((int)(self));
    *(int*)((char*)(t1002)) = (int)((int)g_01446078);
    *(int*)((char*)(t1002) + 4) = (int)((int)g_01445f58);
    ((C_00991f90*)((int)(self)))->FUN_00991f90();
    t1006 = (int)(t1002 + (int)524);
    ((C_00620230*)(t1006))->FUN_00620230();
    t1010 = (int)(t1002);
    ((C_00962740*)(t1010))->FUN_00962740();
    t4 = (unsigned char)((unsigned char)(a4) & (unsigned char)1);
    if (t4 != (unsigned char)0) {
        FUN_00951330((unsigned int)(t1002));
    }
    t1017 = (int)(t1002);
    return (int)(t1017);
}
