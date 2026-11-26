// 0x005c7f50: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEditors/SPEditorPalettePage.cpp, match/slices/s005c7500/s005c7500.cpp.

// lifted by il2c_lift + l2c_search (ref@t1003); CI scorer MATCH; corpus status nonmatching/residual
extern "C" unsigned char g_013f1ab0[];
extern "C" unsigned char g_013f828c[];
extern "C" unsigned char g_013f829c[];
extern "C" unsigned char g_01485720[];

// @ 0x005c7f50
extern "C" int __fastcall FUN_005c7f50(char* self, int edx_unused)
{
    float t1001;
    int t1003;
    int t1004;
    float t1005;
    t1001 = (float)((float)0);
    t1003 = (int)((int)(self));
    int& t1003_r = t1003;
    t1004 = (int)((int)0);
    *(int*)((char*)(t1003_r) + 4) = (int)(t1004);
    *(int*)((char*)(t1003_r) + 8) = (int)((int)g_013f1ab0);
    *(float*)((char*)(t1003_r) + 20) = (float)(t1001);
    *(float*)((char*)(t1003_r) + 24) = (float)(t1001);
    *(float*)((char*)(t1003_r) + 28) = (float)(t1001);
    *(float*)((char*)(t1003_r) + 32) = (float)(t1001);
    *(float*)((char*)(t1003_r) + 36) = (float)(t1001);
    *(float*)((char*)(t1003_r) + 40) = (float)(t1001);
    t1005 = (float)((float)(*(float*)g_01485720));
    *(int*)((char*)(t1003_r)) = (int)((int)g_013f829c);
    *(int*)((char*)(t1003_r) + 8) = (int)((int)g_013f828c);
    *(int*)((char*)(t1003_r) + 12) = (int)((int)(-671062521));
    *(int*)((char*)(t1003_r) + 16) = (int)(t1004);
    *(unsigned char*)((char*)(t1003_r) + 44) = (unsigned char)((unsigned char)(t1004));
    *(unsigned char*)((char*)(t1003_r) + 45) = (unsigned char)((unsigned char)(t1004));
    *(unsigned char*)((char*)(t1003_r) + 72) = (unsigned char)((unsigned char)(t1004));
    *(unsigned char*)((char*)(t1003_r) + 73) = (unsigned char)((unsigned char)(t1004));
    *(unsigned char*)((char*)(t1003_r) + 74) = (unsigned char)((unsigned char)(t1004));
    *(float*)((char*)(t1003_r) + 76) = (float)(t1005);
    *(int*)((char*)(t1003_r) + 80) = (int)(t1004);
    *(int*)((char*)(t1003_r) + 84) = (int)(t1004);
    *(int*)((char*)(t1003_r) + 88) = (int)(t1004);
    *(int*)((char*)(t1003_r) + 92) = (int)(t1004);
    *(int*)((char*)(t1003_r) + 96) = (int)((int)(-1));
    *(int*)((char*)(t1003_r) + 100) = (int)(t1004);
    *(int*)((char*)(t1003_r) + 104) = (int)(t1004);
    *(int*)((char*)(t1003_r) + 108) = (int)(t1004);
    *(int*)((char*)(t1003_r) + 112) = (int)(t1004);
    *(int*)((char*)(t1003_r) + 116) = (int)(t1004);
    *(int*)((char*)(t1003_r) + 120) = (int)(t1004);
    return (int)(t1003_r);
}
