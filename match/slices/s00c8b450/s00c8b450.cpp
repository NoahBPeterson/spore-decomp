// 0x00c8b450: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00c8aa60/s00c8aa60.cpp, src/game/SPGonzago/SPStar.cpp.

// @ 0x00c8b450
extern "C" bool __cdecl FUN_00c8b450(int a4)
{
    int t1000;
    bool t1001;
    bool t1002;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)0) {
        if (t1000 > (int)6) {
            if (t1000 <= (int)12) {
                t1001 = true;
                return (bool)(t1001);
            }
        }
    }
    t1002 = false;
    return (bool)(t1002);
}
