// 0x005ce060: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEditors/SPEditorSpine.cpp, match/slices/s005cdd00/s005cdd00.cpp.

struct C_005cdd00 { int FUN_005cdd00(float, unsigned int); };
struct C_01082ee0 { void FUN_01082ee0(unsigned int, unsigned int); };
struct C_01088c90 { void FUN_01088c90(unsigned int); };
struct C_0109ae60 { void FUN_0109ae60(); };

// @ 0x005ce060
extern "C" int __fastcall FUN_005ce060(char* self, int edx_unused, int a4, float a8, int a12)
{
    int t1001;
    int t1002;
    int t1004;
    int t1006;
    int t1009;
    int t1010;
    int t1014;
    int t1018;
    int t1019;
    int t1023;
    int t1024;
    int t1026;
    t1001 = (int)((int)(a4));
    t1002 = (int)((int)0);
    *(int*)((char*)(t1001)) = (int)(t1002);
    *(int*)((char*)(t1001) + 4) = (int)(t1002);
    *(int*)((char*)(t1001) + 8) = (int)(t1002);
    *(int*)((char*)(t1001) + 12) = (int)(t1002);
    t1004 = (int)((int)(a12));
    t1006 = (int)((int)(self));
    t1009 = (int)((C_005cdd00*)((int)(self)))->FUN_005cdd00((float)((float)(a8)), (unsigned int)(t1004));
    t1010 = (int)(*(int*)((char*)(t1006) + 20));
    *(int*)((char*)(t1001)) = (int)(t1009);
    ((C_01082ee0*)(t1010))->FUN_01082ee0((unsigned int)(t1009), (unsigned int)((int)1));
    t1014 = (int)(*(int*)((char*)(t1001)));
    ((C_0109ae60*)(t1014))->FUN_0109ae60();
    t1018 = (int)(*(int*)((char*)(t1006) + 24));
    t1019 = (int)(*(int*)((char*)(t1001)));
    ((C_01088c90*)(t1019))->FUN_01088c90((unsigned int)(t1018));
    t1023 = (int)(*(int*)((char*)(t1001)));
    t1024 = (int)((int)0);
    *(unsigned short*)((char*)(t1023) + 150) = (unsigned short)((unsigned short)(t1024));
    t1026 = (int)(t1001);
    return (int)(t1026);
}
