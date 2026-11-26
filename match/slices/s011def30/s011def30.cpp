// 0x011def30: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_014f5ce8[];
extern "C" int __cdecl FUN_011815d0(...);
extern "C" int __cdecl FUN_011835c0(...);
extern "C" void __cdecl FUN_01191780(...);
extern "C" void __cdecl FUN_01197530(...);
extern "C" void __cdecl FUN_01199db0(...);

// @ 0x011def30
extern "C" void __cdecl FUN_011def30(int a4)
{
    int t1001;
    int t1002;
    int t1006;
    int t1007;
    int t1011;
    int t1015;
    int t1019;
    t1001 = (int)((int)(a4));
    if (t1001 != (int)0) {
        t1002 = (int)(t1001 + (int)48);
        t1006 = (int)FUN_011815d0((unsigned int)(t1002), (unsigned int)((int)(-1)), (unsigned int)((int)5), (unsigned int)((int)g_014f5ce8), (unsigned int)((int)133));
        if (t1006 <= (int)0) {
            t1007 = (int)(*(int*)((char*)(t1001) + 4));
            if (t1007 != (int)0) {
                FUN_01197530((unsigned int)(t1007));
            }
            t1011 = (int)(*(int*)((char*)(t1001) + 8));
            if (t1011 != (int)0) {
                FUN_01199db0((unsigned int)(t1011));
            }
            t1015 = (int)(*(int*)((char*)(t1001) + 12));
            if (t1015 != (int)0) {
                FUN_01191780((unsigned int)(t1015));
            }
            t1019 = (int)(*(int*)((char*)(t1001) + 20));
            if (t1019 != (int)0) {
                if ((int)*(int*)((char*)(t1001) + 24) != (int)0) {
                    FUN_011835c0((unsigned int)(t1019));
                }
            }
            t1006 = (int)FUN_011835c0((unsigned int)(t1001));
        }
    }
    return;
}
