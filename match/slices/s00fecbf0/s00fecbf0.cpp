// 0x00fecbf0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00fec590/s00fec590.cpp, src/game/SPGonzago/SPMissionManager.cpp.

extern "C" int __cdecl FUN_00685520(...);
struct C_00e5c780 { int FUN_00e5c780(unsigned int, unsigned int); };

// @ 0x00fecbf0
extern "C" int __fastcall FUN_00fecbf0(char* self, int edx_unused)
{
    int t1002;
    int t1005;
    int t1006;
    int v_l8;
    int t1007;
    int v_l4;
    int t1008;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1016;
    t1002 = (int)((int)(self));
    t1005 = (int)FUN_00685520((unsigned int)((int)2));
    if ((unsigned char)(t1005) != (unsigned char)0) {
        t1006 = (int)((int)&v_l8);
        t1007 = (int)((int)&v_l4);
        t1008 = (int)(t1002 + (int)92);
        v_l8 = (int)((int)716537772);
        t1011 = (int)((C_00e5c780*)(t1008))->FUN_00e5c780((unsigned int)(t1007), (unsigned int)(t1006));
        t1012 = (int)(*(int*)((char*)(t1011)));
        t1013 = (int)(t1002 + (int)96);
        if (t1012 != t1013) {
            if ((int)*(int*)((char*)(t1012) + 20) == (int)1) goto Lfecc37;
        }
        t1014 = (int)((int)1);
        return (int)(t1014);
    }
    Lfecc37:;
    t1016 = (int)((int)0);
    return (int)(t1016);
}
