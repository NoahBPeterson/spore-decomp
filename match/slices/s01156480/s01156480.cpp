// 0x01156480: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s011559a0/s011559a0.cpp.

extern "C" int DAT_015c3828;
extern "C" int DAT_015c382c;
extern "C" int DAT_015c3830;
extern "C" int DAT_015c3834;
extern "C" int DAT_015c3838;
extern "C" int DAT_015c383c;
extern "C" int DAT_016f16d4;
extern "C" int DAT_016f16d8;
extern "C" int DAT_016f16dc;
extern "C" int DAT_016f16e0;
extern "C" int DAT_016f16e4;
extern "C" int DAT_016f16e8;

// @ 0x01156480
extern "C" int __cdecl FUN_01156480(int value)
{
    int value2 = DAT_015c3828;
    int value3 = DAT_015c382c;
    int value4 = value2 + value;
    int value5 = value3 + value;
    DAT_016f16d4 = value4;
    int value6 = DAT_015c3830;
    DAT_016f16d8 = value5;
    int value7 = DAT_015c3834;
    int value8 = value6 + value;
    int value9 = value7 + value;
    DAT_016f16dc = value8;
    int value10 = DAT_015c3838;
    DAT_016f16e0 = value9;
    int value11 = DAT_015c383c;
    int value12 = value10 + value;
    int value13 = value11 + value;
    DAT_016f16e4 = value12;
    DAT_016f16e8 = value13;
    return value;
}
