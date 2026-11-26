// 0x00886db0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

struct C_00899480 { int FUN_00899480(unsigned int, unsigned int); };

// @ 0x00886db0
extern "C" int __fastcall FUN_00886db0(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 4));
    if ((unsigned int)(t1001) < (unsigned int)*(int*)((char*)((int)(self)) + 8)) {
        t1002 = (int)(t1001 + (int)4);
        *(int*)((char*)((int)(self)) + 4) = (int)(t1002);
        if (t1001 == (int)0) goto L886dd8;
        t1003 = (int)((int)(a4));
        t1004 = (int)(*(int*)((char*)(t1003)));
        *(int*)((char*)(t1001)) = (int)(t1004);
        return (int)(t1001);
    }
    t1005 = (int)((int)(a4));
    t1001 = (int)((C_00899480*)((int)(self)))->FUN_00899480((unsigned int)(t1001), (unsigned int)(t1005));
    L886dd8:;
    return (int)(t1001);
}
