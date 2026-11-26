// 0x00c15150: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureBase.cpp, match/slices/s00c14350/s00c14350.cpp.

struct C_009cab60 { int FUN_009cab60(unsigned int); };
struct C_009cb460 { int FUN_009cb460(unsigned int); };
struct C_00c12080 { void FUN_00c12080(unsigned int, unsigned int); };

// @ 0x00c15150
extern "C" bool __fastcall FUN_00c15150(char* self, int edx_unused, int a4, int a8)
{
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1010;
    int t1011;
    int t1012;
    int t1016;
    int t1017;
    bool t1022;
    bool t1025;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003) + 2900));
    if (t1004 != (int)0) {
        t1005 = (int)((int)(a4));
        t1006 = (int)(*(int*)((char*)(t1004) + 380));
        t1007 = (int)(t1006);
        t1004 = (int)((C_009cab60*)(t1007))->FUN_009cab60((unsigned int)(t1005));
        t1010 = (int)(t1004);
        if (t1010 != (int)0) {
            t1011 = (int)((int)(a8));
            t1012 = (int)(t1003);
            ((C_00c12080*)(t1012))->FUN_00c12080((unsigned int)(t1010), (unsigned int)(t1011));
            t1016 = (int)(*(int*)((char*)(t1003) + 2900));
            t1017 = (int)(*(int*)((char*)(t1016) + 380));
            ((C_009cb460*)(t1017))->FUN_009cb460((unsigned int)(t1010));
            t1022 = true;
            return (bool)(t1022);
        }
    }
    t1025 = false;
    return (bool)(t1025);
}
