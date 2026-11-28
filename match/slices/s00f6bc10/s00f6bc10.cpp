// 0x00f6bc10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPTerrain/SPTerrainEditor.cpp, match/slices/s00f6b9a0/s00f6b9a0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual int s12();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
};

extern "C" unsigned char g_015b0e48[];
extern "C" unsigned char g_015b0e4c[];
struct C_00f6b7c0 { int FUN_00f6b7c0(); };

// @ 0x00f6bc10
extern "C" void __fastcall FUN_00f6bc10(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1009;
    int t1012;
    int t1015;
    int t1021;
    float t1026;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 116));
    if (t1003 != (int)0) {
        ((il2c_vc0*)(t1003))->s13();
        t1009 = (int)(*(int*)((char*)(t1002) + 116));
        t1012 = (int)((il2c_vc1*)(t1009))->s12();
        if ((unsigned char)(t1012) == (unsigned char)0) {
            t1015 = (int)(*(int*)((char*)(t1002) + 116));
            ((il2c_vc2*)(t1015))->s15();
        }
    }
    t1021 = (int)((int)g_015b0e48);
    ((C_00f6b7c0*)(t1021))->FUN_00f6b7c0();
    t1026 = (float)((float)0);
    *(int*)g_015b0e48 = (int)((int)g_015b0e48);
    *(int*)g_015b0e4c = (int)((int)g_015b0e48);
    *(float*)((char*)(t1002) + 224) = (float)(t1026);
    *(float*)((char*)(t1002) + 228) = (float)(t1026);
    *(float*)((char*)(t1002) + 232) = (float)(t1026);
    *(float*)((char*)(t1002) + 236) = (float)(t1026);
    *(float*)((char*)(t1002) + 240) = (float)(t1026);
    *(float*)((char*)(t1002) + 244) = (float)(t1026);
    *(float*)((char*)(t1002) + 248) = (float)(t1026);
    *(float*)((char*)(t1002) + 252) = (float)(t1026);
    *(float*)((char*)(t1002) + 256) = (float)(t1026);
    *(float*)((char*)(t1002) + 260) = (float)(t1026);
    *(float*)((char*)(t1002) + 264) = (float)(t1026);
    *(float*)((char*)(t1002) + 268) = (float)(t1026);
    *(float*)((char*)(t1002) + 272) = (float)(t1026);
    *(float*)((char*)(t1002) + 276) = (float)(t1026);
    *(float*)((char*)(t1002) + 280) = (float)(t1026);
    *(float*)((char*)(t1002) + 284) = (float)(t1026);
    *(float*)((char*)(t1002) + 288) = (float)(t1026);
    *(float*)((char*)(t1002) + 292) = (float)(t1026);
    *(float*)((char*)(t1002) + 296) = (float)(t1026);
    *(float*)((char*)(t1002) + 300) = (float)(t1026);
    *(float*)((char*)(t1002) + 304) = (float)(t1026);
    *(float*)((char*)(t1002) + 308) = (float)(t1026);
    *(float*)((char*)(t1002) + 312) = (float)(t1026);
    *(float*)((char*)(t1002) + 316) = (float)(t1026);
    return;
}
