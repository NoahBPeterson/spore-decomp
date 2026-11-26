// 0x0089ed90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" int __cdecl FUN_0093a700(...);

// @ 0x0089ed90
extern "C" void __fastcall FUN_0089ed90(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    int t1001;
    int t1003;
    t1000 = (int)((int)(a8));
    t1001 = (int)((int)(a4));
    t1003 = (int)(*(int*)((char*)((int)(self)) + 308));
    FUN_0093a700((unsigned int)(t1003), (unsigned int)(t1001), (unsigned int)(t1000), (unsigned int)((int)0));
    return;
}
