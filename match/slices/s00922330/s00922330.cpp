// 0x00922330: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s009215c0/s009215c0.cpp.

struct C_00921e00 { void FUN_00921e00(unsigned int, unsigned int); };
struct C_00921e60 { int FUN_00921e60(unsigned int); };
struct C_00922150 { void FUN_00922150(unsigned int); };

// @ 0x00922330
extern "C" bool __fastcall FUN_00922330(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int v_l20[5];
    int t1010;
    int t1011;
    int t1015;
    int t1016;
    int v_l40[5];
    int t1020;
    int t1021;
    int t1025;
    int t1026;
    bool t1031;
    bool t1035;
    t1002 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    if (t1002 != (int)0) {
        t1005 = (int)(*(unsigned char*)((char*)(t1002)));
        t1006 = (int)((int)&v_l20);
        ((C_00921e00*)(t1006))->FUN_00921e00((unsigned int)(t1005), (unsigned int)((int)0));
        t1010 = (int)((int)&v_l20);
        t1011 = (int)(t1004 + (int)16);
        ((C_00922150*)(t1011))->FUN_00922150((unsigned int)(t1010));
        t1015 = (int)(*(unsigned char*)((char*)(t1002)));
        t1016 = (int)((int)&v_l40);
        ((C_00921e00*)(t1016))->FUN_00921e00((unsigned int)(t1015), (unsigned int)((int)0));
        t1020 = (int)((int)&v_l40);
        t1021 = (int)(t1004 + (int)64);
        ((C_00921e60*)(t1021))->FUN_00921e60((unsigned int)(t1020));
        t1025 = (int)((int)&v_l40);
        t1026 = (int)(t1004 + (int)160);
        ((C_00921e60*)(t1026))->FUN_00921e60((unsigned int)(t1025));
        t1031 = true;
        return (bool)(t1031);
    }
    t1035 = false;
    return (bool)(t1035);
}
