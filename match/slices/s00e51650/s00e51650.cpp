// 0x00e51650: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e50810/s00e50810.cpp.

extern "C" unsigned char g_016b3c04[];
extern "C" int __stdcall FUN_0067de90(unsigned int, unsigned int);
struct C_007eb820 { void FUN_007eb820(unsigned int); };
struct C_007ec160 { int FUN_007ec160(); };

// @ 0x00e51650
extern "C" int __cdecl FUN_00e51650(void)
{
    int t1000;
    int t1005;
    int t1006;
    int t1009;
    int t1010;
    int t1011;
    int t1015;
    int t1016;
    int t1017;
    t1000 = (int)((int)(*(int*)g_016b3c04));
    if ((unsigned char)*(unsigned char*)((char*)(t1000) + 20840) == (unsigned char)0) {
        t1005 = (int)FUN_0067de90((unsigned int)((int)0), (unsigned int)((int)4));
        t1006 = (int)(t1005);
        t1009 = (int)((C_007ec160*)(t1006))->FUN_007ec160();
        t1010 = (int)(t1009);
        t1011 = (int)(t1010);
        ((C_007eb820*)(t1011))->FUN_007eb820((unsigned int)((int)1));
        t1015 = (int)((int)(*(int*)g_016b3c04));
        t1016 = (int)(*(int*)((char*)(t1015) + 20880));
        t1000 = (int)(*(int*)((char*)(t1010) + 12));
        t1017 = (int)(*(int*)((char*)(t1016) + 116));
        *(int*)((char*)(t1000)) = (int)(t1017);
    }
    return (int)(t1000);
}
