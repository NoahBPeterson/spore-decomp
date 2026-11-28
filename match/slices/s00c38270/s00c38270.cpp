// 0x00c38270: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00c37a90/s00c37a90.cpp.

struct C_00b8d970 { int FUN_00b8d970(); };
struct C_00c70880 { int FUN_00c70880(); };
struct C_00c71e30 { int FUN_00c71e30(); };
struct C_01021260 { int FUN_01021260(); };
extern "C" int __cdecl FUN_01021300(...);
extern "C" int __cdecl FUN_0102adf0(...);

// @ 0x00c38270
// @ 0x00c38270
extern "C" bool __fastcall FUN_00c38270(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1007;
    int t1008;
    int t1011;
    float t1015;
    int t1016;
    int t1017;
    int t1020;
    bool t1026;
    bool t1029;
    t1003 = (int)((int)(self));
    t1004 = (int)((C_01021260*)((int)(self)))->FUN_01021260();
    t1007 = (int)(t1004);
    if (t1007 != (int)0) {
        t1008 = (int)(t1007);
        t1004 = (int)((C_00c70880*)(t1008))->FUN_00c70880();
        if (t1004 != (int)1) {
            t1011 = (int)(*(int*)((char*)(t1007) + 316));
            if (t1011 != (int)0) {
                t1004 = (int)((C_00b8d970*)(t1011))->FUN_00b8d970();
                if ((unsigned char)(t1004) != (unsigned char)0) goto Lc382d7;
            }
            if ((unsigned char)*(unsigned char*)((char*)(t1003) + 1868) != (unsigned char)0) {
                t1015 = (float)((float)0);
                if (t1015 >= (float)*(float*)((char*)(t1003) + 1344)) {
                    t1016 = (int)(t1007);
                    t1017 = (int)((C_00c71e30*)(t1016))->FUN_00c71e30();
                    t1020 = (int)(t1017);
                    t1004 = (int)FUN_01021300();
                    if (t1020 != t1004) goto Lc382d7;
                    t1004 = (int)FUN_0102adf0((unsigned int)(t1007));
                    if ((unsigned char)(t1004) != (unsigned char)0) goto Lc382d7;
                }
                t1026 = true;
                return (bool)(t1026);
            }
        }
    }
    Lc382d7:;
    t1029 = false;
    return (bool)(t1029);
}
