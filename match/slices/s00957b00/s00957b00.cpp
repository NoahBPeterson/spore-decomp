// 0x00957b00: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/Image.cpp, match/slices/s009579f0/s009579f0.cpp.

extern "C" void __cdecl FUN_013c1110(...);
extern "C" unsigned char g_0166b130[];
extern "C" unsigned char g_0166b140[];
extern "C" unsigned char g_0166b170[];
extern "C" unsigned char g_0166b174[];
extern "C" unsigned char g_0166b178[];
extern "C" unsigned char g_0166b188[];
struct C_009222a0 { void FUN_009222a0(unsigned int, unsigned int); };
extern "C" void __cdecl FUN_011e07ef(...);

// @ 0x00957b00
extern "C" int __cdecl FUN_00957b00(void)
{
    int t1000;
    int t1001;
    unsigned char t2;
    int t1002;
    t1000 = (int)((int)(*(int*)g_0166b130));
    if (t1000 == (int)0) {
        t1001 = (int)((int)1);
        t2 = (unsigned char)((unsigned char)(*(unsigned char*)g_0166b188) & (unsigned char)(t1001));
        if (t2 == (unsigned char)0) {
            *(int*)g_0166b188 = (int)((int)(*(int*)g_0166b188) | t1001);
            t1002 = (int)((int)g_0166b140);
            ((C_009222a0*)(t1002))->FUN_009222a0((unsigned int)((int)0), (unsigned int)(t1001));
            *(int*)g_0166b170 = (int)((int)0);
            *(int*)g_0166b174 = (int)((int)0);
            *(int*)g_0166b178 = (int)((int)0);
            FUN_011e07ef((unsigned int)((int)&FUN_013c1110));
        }
        t1000 = (int)((int)g_0166b140);
        *(int*)g_0166b130 = (int)(t1000);
    }
    return (int)(t1000);
}
