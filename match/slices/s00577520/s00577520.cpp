// 0x00577520: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEditors/SPAppModeEditorBase.cpp, match/slices/s00577130/s00577130.cpp.

struct C_0047e6c0 { int FUN_0047e6c0(); };
struct C_00573c00 { int FUN_00573c00(unsigned int, unsigned int); };
struct C_00573d70 { int FUN_00573d70(unsigned int, unsigned int); };

// @ 0x00577520
extern "C" int __fastcall FUN_00577520(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1004;
    unsigned char t2;
    int t1007;
    int t1010;
    int t1011;
    int t1014;
    int t1015;
    unsigned char t11;
    int t1016;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 204));
    if (t1003 != (int)0) {
        t1004 = (int)(*(int*)((char*)(t1003) + 3528));
        t1003 = (int)((unsigned int)(t1004) >> (int)1);
        t2 = (unsigned char)((unsigned char)(t1003) & (unsigned char)1);
        if (t2 != (unsigned char)0) {
            t1003 = (int)((C_00573c00*)((int)(self)))->FUN_00573c00((unsigned int)((int)0), (unsigned int)((int)(-1)));
        }
    }
    t1007 = (int)(*(int*)((char*)(t1002) + 228));
    if (t1007 != (int)0) {
        t1010 = (int)((C_0047e6c0*)(t1007))->FUN_0047e6c0();
        if (t1010 != (int)0) {
            t1011 = (int)(*(int*)((char*)(t1002) + 228));
            t1003 = (int)((C_0047e6c0*)(t1011))->FUN_0047e6c0();
            t1014 = (int)(*(int*)((char*)(t1003) + 3528));
            t1015 = (int)((unsigned int)(t1014) >> (int)1);
            t11 = (unsigned char)((unsigned char)(t1015) & (unsigned char)1);
            if (t11 == (unsigned char)0) goto L577578;
        }
        t1016 = (int)(t1002);
        t1003 = (int)((C_00573d70*)(t1016))->FUN_00573d70((unsigned int)((int)0), (unsigned int)((int)1));
    }
    L577578:;
    return (int)(t1003);
}
