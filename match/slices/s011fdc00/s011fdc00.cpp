// 0x011fdc00: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s011fd3a0/s011fd3a0.cpp.

struct C_011fe180 { void FUN_011fe180(unsigned int); };

// @ 0x011fdc00
extern "C" void __fastcall FUN_011fdc00(char* self, int edx_unused, float a4)
{
    float t1001;
    float t1003;
    float t1004;
    float t1005;
    t1001 = (float)(*(float*)((char*)((int)(self)) + 68));
    t1003 = (float)((float)0);
    if (t1001 > t1003) {
        t1004 = (float)(*(float*)((char*)((int)(self)) + 32));
        t1005 = (float)(t1004 + (float)(a4));
        if (t1005 > (float)*(float*)((char*)((int)(self)) + 68)) {
            *(float*)((char*)((int)(self)) + 68) = (float)(t1003);
        }
    }
    ((C_011fe180*)((int)(self)))->FUN_011fe180((unsigned int)((int)(*(int*)&a4)));
    return;
}
