// 0x00f30800: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00f30800/s00f30800.cpp.

// @ 0x00f30800
extern "C" int __fastcall FUN_00f30800(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    unsigned char t1006;
    unsigned char t1007;
    t1001 = (int)((int)(self));
    t1002 = (int)((int)(a4));
    t1003 = (int)(*(int*)((char*)(t1002)));
    *(int*)((char*)(t1001)) = (int)(t1003);
    *(float*)((char*)(t1001) + 4) = (float)(*(float*)((char*)(t1002) + 4));
    *(float*)((char*)(t1001) + 8) = (float)(*(float*)((char*)(t1002) + 8));
    *(float*)((char*)(t1001) + 12) = (float)(*(float*)((char*)(t1002) + 12));
    *(float*)((char*)(t1001) + 16) = (float)(*(float*)((char*)(t1002) + 16));
    *(float*)((char*)(t1001) + 20) = (float)(*(float*)((char*)(t1002) + 20));
    *(float*)((char*)(t1001) + 24) = (float)(*(float*)((char*)(t1002) + 24));
    *(float*)((char*)(t1001) + 28) = (float)(*(float*)((char*)(t1002) + 28));
    *(float*)((char*)(t1001) + 32) = (float)(*(float*)((char*)(t1002) + 32));
    *(float*)((char*)(t1001) + 36) = (float)(*(float*)((char*)(t1002) + 36));
    *(float*)((char*)(t1001) + 40) = (float)(*(float*)((char*)(t1002) + 40));
    *(float*)((char*)(t1001) + 44) = (float)(*(float*)((char*)(t1002) + 44));
    *(float*)((char*)(t1001) + 48) = (float)(*(float*)((char*)(t1002) + 48));
    *(float*)((char*)(t1001) + 52) = (float)(*(float*)((char*)(t1002) + 52));
    *(float*)((char*)(t1001) + 56) = (float)(*(float*)((char*)(t1002) + 56));
    *(float*)((char*)(t1001) + 60) = (float)(*(float*)((char*)(t1002) + 60));
    *(float*)((char*)(t1001) + 64) = (float)(*(float*)((char*)(t1002) + 64));
    *(float*)((char*)(t1001) + 68) = (float)(*(float*)((char*)(t1002) + 68));
    *(float*)((char*)(t1001) + 72) = (float)(*(float*)((char*)(t1002) + 72));
    *(float*)((char*)(t1001) + 76) = (float)(*(float*)((char*)(t1002) + 76));
    *(float*)((char*)(t1001) + 80) = (float)(*(float*)((char*)(t1002) + 80));
    *(float*)((char*)(t1001) + 84) = (float)(*(float*)((char*)(t1002) + 84));
    *(float*)((char*)(t1001) + 88) = (float)(*(float*)((char*)(t1002) + 88));
    *(float*)((char*)(t1001) + 92) = (float)(*(float*)((char*)(t1002) + 92));
    *(float*)((char*)(t1001) + 96) = (float)(*(float*)((char*)(t1002) + 96));
    *(float*)((char*)(t1001) + 100) = (float)(*(float*)((char*)(t1002) + 100));
    t1004 = (int)(*(int*)((char*)(t1002) + 104));
    *(int*)((char*)(t1001) + 104) = (int)(t1004);
    t1005 = (int)(*(int*)((char*)(t1002) + 108));
    *(int*)((char*)(t1001) + 108) = (int)(t1005);
    *(float*)((char*)(t1001) + 112) = (float)(*(float*)((char*)(t1002) + 112));
    *(float*)((char*)(t1001) + 116) = (float)(*(float*)((char*)(t1002) + 116));
    t1006 = (unsigned char)(*(unsigned char*)((char*)(t1002) + 120));
    *(unsigned char*)((char*)(t1001) + 120) = (unsigned char)(t1006);
    t1007 = (unsigned char)(*(unsigned char*)((char*)(t1002) + 121));
    *(unsigned char*)((char*)(t1001) + 121) = (unsigned char)(t1007);
    return (int)(t1001);
}
