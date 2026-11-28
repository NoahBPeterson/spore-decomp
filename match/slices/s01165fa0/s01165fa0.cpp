// 0x01165fa0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s01165820/s01165820.cpp.

// @ 0x01165fa0
extern "C" void __cdecl FUN_01165fa0(int obj, int obj2)
{
    int value;
    int value2;
    int cursor;
    int cursor2;
    int count;
    float f;
    float f2;
    float f3;
    float f4;
    float f5;
    float f6;
    float f7;
    float f8;
    float f9;
    float f10;
    float f11;
    float f12;
    float f13;
    float f14;
    float f15;
    float f16;
    float f17;
    float f18;
    float f19;
    float f20;
    float f21;
    float f22;
    float f23;
    float f24;
    value = obj + 72;
    if ((unsigned int)obj < (unsigned int)value) {
        value2 = (unsigned int)(value - obj - 1) >> 2;
        cursor = obj2 + 8;
        cursor2 = obj + 144;
        count = value2 + 1;
        goto again;
        again:
        f = *(float*)((char*)cursor2 - 0x48);
        f2 = *(float*)cursor2;
        f3 = *(float*)((char*)cursor2 + 0x48);
        *(float*)((char*)cursor - 8) = *(float*)((char*)cursor2 - 0x90);
        *(float*)((char*)cursor - 4) = f;
        *(float*)cursor = f2;
        *(float*)((char*)cursor + 4) = f3;
        f4 = *(float*)((char*)cursor2 + 0xd8);
        f5 = *(float*)((char*)cursor2 + 0x120);
        f6 = *(float*)((char*)cursor2 + 0x168);
        *(float*)((char*)cursor + 0x118) = *(float*)((char*)cursor2 + 0x90);
        *(float*)((char*)cursor + 0x11c) = f4;
        *(float*)((char*)cursor + 0x120) = f5;
        *(float*)((char*)cursor + 0x124) = f6;
        f7 = *(float*)((char*)cursor2 + 0x1f8);
        f8 = *(float*)((char*)cursor2 + 0x240);
        f9 = *(float*)((char*)cursor2 + 0x288);
        *(float*)((char*)cursor + 0x238) = *(float*)((char*)cursor2 + 0x1b0);
        *(float*)((char*)cursor + 0x23c) = f7;
        *(float*)((char*)cursor + 0x240) = f8;
        *(float*)((char*)cursor + 0x244) = f9;
        f10 = *(float*)((char*)cursor2 + 0x318);
        f11 = *(float*)((char*)cursor2 + 0x360);
        f12 = *(float*)((char*)cursor2 + 0x3a8);
        *(float*)((char*)cursor + 0x358) = *(float*)((char*)cursor2 + 0x2d0);
        *(float*)((char*)cursor + 0x35c) = f10;
        *(float*)((char*)cursor + 0x360) = f11;
        *(float*)((char*)cursor + 0x364) = f12;
        f13 = *(float*)((char*)cursor2 + 0x438);
        f14 = *(float*)((char*)cursor2 + 0x480);
        f15 = *(float*)((char*)cursor2 + 0x4c8);
        *(float*)((char*)cursor + 0x478) = *(float*)((char*)cursor2 + 0x3f0);
        *(float*)((char*)cursor + 0x47c) = f13;
        *(float*)((char*)cursor + 0x480) = f14;
        *(float*)((char*)cursor + 0x484) = f15;
        f16 = *(float*)((char*)cursor2 + 0x558);
        f17 = *(float*)((char*)cursor2 + 0x5a0);
        f18 = *(float*)((char*)cursor2 + 0x5e8);
        *(float*)((char*)cursor + 0x598) = *(float*)((char*)cursor2 + 0x510);
        *(float*)((char*)cursor + 0x59c) = f16;
        *(float*)((char*)cursor + 0x5a0) = f17;
        *(float*)((char*)cursor + 0x5a4) = f18;
        f19 = *(float*)((char*)cursor2 + 0x678);
        f20 = *(float*)((char*)cursor2 + 0x6c0);
        f21 = *(float*)((char*)cursor2 + 0x708);
        *(float*)((char*)cursor + 0x6b8) = *(float*)((char*)cursor2 + 0x630);
        *(float*)((char*)cursor + 0x6bc) = f19;
        *(float*)((char*)cursor + 0x6c0) = f20;
        *(float*)((char*)cursor + 0x6c4) = f21;
        f22 = *(float*)((char*)cursor2 + 0x798);
        f23 = *(float*)((char*)cursor2 + 0x7e0);
        f24 = *(float*)((char*)cursor2 + 0x828);
        *(float*)((char*)cursor + 0x7d8) = *(float*)((char*)cursor2 + 0x750);
        *(float*)((char*)cursor + 0x7dc) = f22;
        *(float*)((char*)cursor + 0x7e0) = f23;
        *(float*)((char*)cursor + 0x7e4) = f24;
        cursor += 16;
        cursor2 += 4;
        --count;
        if (count != 0) goto again;
    }
    return;
}
