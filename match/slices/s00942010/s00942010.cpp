// 0x00942010: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/HTTPClient.cpp, match/slices/s009413d0/s009413d0.cpp.

extern "C" int __cdecl FUN_00941bb0(...);

// @ 0x00942010
extern "C" bool __stdcall FUN_00942010(int a4, int a8)
{
    int t1001;
    int t1005;
    bool t1006;
    int t1008;
    int t1009;
    int t1010;
    bool t1011;
    t1001 = (int)((int)(a4));
    if ((int)*(int*)((char*)(t1001) + 12) > (int)0) {
        t1005 = (int)FUN_00941bb0();
        if (t1005 > (int)*(int*)((char*)(t1001) + 12)) {
            t1006 = true;
            return (bool)(t1006);
        }
        t1008 = (int)((int)(a8));
        if ((int)*(int*)((char*)(t1008)) > (int)0) {
            t1009 = (int)(*(int*)((char*)(t1001) + 8));
            t1010 = (int)(t1009 + t1005);
            *(int*)((char*)(t1001) + 12) = (int)(t1010);
            *(int*)((char*)(t1008)) = (int)((int)0);
        }
    }
    t1011 = false;
    return (bool)(t1011);
}
