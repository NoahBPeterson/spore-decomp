// 0x00a0f610: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPCreatureAnim/SPCreatureAnimManager.cpp, match/slices/s00a0f350/s00a0f350.cpp.

extern "C" void __cdecl FUN_00f62add(...);
extern "C" unsigned char g_0166c084[];
extern "C" int __cdecl FUN_009a37a0(...);
extern "C" void __cdecl FUN_009a4020(...);
struct C_009ab540 { int FUN_009ab540(unsigned int, unsigned int); };
struct C_00a08ba0 { int FUN_00a08ba0(); };
struct C_00a0f080 { int FUN_00a0f080(unsigned int); };

// @ 0x00a0f610
extern "C" bool __fastcall FUN_00a0f610(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    int t1001;
    int t1002;
    bool t1004;
    int t1005;
    int t1006;
    int t1008;
    int t1011;
    int t1015;
    bool t1018;
    int t1020;
    bool t1024;
    bool t1027;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)&FUN_00f62add) {
        if (t1000 != (int)36510428) goto La0f693;
        t1001 = (int)((int)(a8));
        t1002 = (int)(*(int*)((char*)(t1001) + 8));
        *(int*)((char*)((int)(self)) + 120) = (int)(t1002);
        t1004 = false;
        return (bool)(t1004);
    }
    t1005 = (int)((int)(a8));
    t1000 = (int)(*(int*)((char*)(t1005) + 8));
    t1006 = (int)(*(int*)((char*)(t1005) + 24));
    if (t1000 != (int)635371794) {
        if (t1000 != (int)1256942534) {
            if (t1000 != (int)(-300431699)) goto La0f693;
            t1008 = (int)FUN_009a37a0((unsigned int)(t1006));
            t1011 = (int)(t1008);
            if (t1011 != (int)0) {
                FUN_009a4020((unsigned int)(t1011), (unsigned int)((int)(-1)));
                t1015 = (int)((int)(*(int*)g_0166c084));
                t1008 = (int)((C_009ab540*)(t1015))->FUN_009ab540((unsigned int)(t1011), (unsigned int)((int)(-1)));
            }
            t1018 = true;
            return (bool)(t1018);
        }
        t1020 = (int)((int)(self) + (int)(-4));
        ((C_00a0f080*)(t1020))->FUN_00a0f080((unsigned int)((int)1));
        t1024 = false;
        return (bool)(t1024);
    }
    t1000 = (int)((C_00a08ba0*)((int)(self)))->FUN_00a08ba0();
    La0f693:;
    t1027 = false;
    return (bool)(t1027);
}
