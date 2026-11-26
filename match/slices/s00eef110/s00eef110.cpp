// 0x00eef110: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00eeebd0/s00eeebd0.cpp.

// lifted by il2c_lift + l2c_search (ref@t1001); CI scorer MATCH; corpus status nonmatching/residual
struct C_00eeefb0 { int FUN_00eeefb0(unsigned int, unsigned int); };

// @ 0x00eef110
extern "C" int __fastcall FUN_00eef110(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 4));
    int& t1001_r = t1001;
    if ((unsigned int)(t1001_r) < (unsigned int)*(int*)((char*)((int)(self)) + 8)) {
        t1002 = (int)(t1001_r + (int)32);
        *(int*)((char*)((int)(self)) + 4) = (int)(t1002);
        if (t1001_r == (int)0) goto Leef162;
        t1003 = (int)((int)(a4));
        t1004 = (int)(*(int*)((char*)(t1003)));
        *(float*)((char*)(t1001_r) + 4) = (float)(*(float*)((char*)(t1003) + 4));
        *(int*)((char*)(t1001_r)) = (int)(t1004);
        *(float*)((char*)(t1001_r) + 8) = (float)(*(float*)((char*)(t1003) + 8));
        *(float*)((char*)(t1001_r) + 12) = (float)(*(float*)((char*)(t1003) + 12));
        *(float*)((char*)(t1001_r) + 16) = (float)(*(float*)((char*)(t1003) + 16));
        *(float*)((char*)(t1001_r) + 20) = (float)(*(float*)((char*)(t1003) + 20));
        *(float*)((char*)(t1001_r) + 24) = (float)(*(float*)((char*)(t1003) + 24));
        *(float*)((char*)(t1001_r) + 28) = (float)(*(float*)((char*)(t1003) + 28));
        return (int)(t1001_r);
    }
    t1005 = (int)((int)(a4));
    t1001_r = (int)((C_00eeefb0*)((int)(self)))->FUN_00eeefb0((unsigned int)(t1001_r), (unsigned int)(t1005));
    Leef162:;
    return (int)(t1001_r);
}
