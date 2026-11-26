// 0x00ea55b0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPAudio/SPAudioMixMode.cpp, match/slices/s00ea5000/s00ea5000.cpp.

// lifted by il2c_lift + l2c_search (ref@t1003); CI scorer MATCH; corpus status nonmatching/residual
extern "C" unsigned char g_013eb384[];
extern "C" unsigned char g_013ef094[];
extern "C" unsigned char g_01486110[];
extern "C" unsigned char g_0148737c[];
extern "C" unsigned char g_0148738c[];
extern "C" unsigned char g_01487a48[];
extern "C" unsigned char g_01667bac[];
extern "C" unsigned char g_01667bad[];

// @ 0x00ea55b0
extern "C" int __fastcall FUN_00ea55b0(char* self, int edx_unused)
{
    float t1001;
    int t1003;
    int t1004;
    float t1005;
    int t1006;
    t1001 = (float)((float)0);
    t1003 = (int)((int)(self));
    int& t1003_r = t1003;
    *(int*)((char*)(t1003_r) + 4) = (int)((int)g_013eb384);
    *(int*)((char*)(t1003_r) + 8) = (int)((int)g_013ef094);
    t1004 = (int)((int)0);
    *(int*)((char*)(t1003_r) + 12) = (int)(t1004);
    *(float*)((char*)(t1003_r) + 20) = (float)(t1001);
    t1005 = (float)((float)(*(float*)g_01486110));
    *(unsigned char*)((char*)(t1003_r) + 16) = (unsigned char)((int)1);
    *(int*)((char*)(t1003_r) + 24) = (int)(t1004);
    *(int*)((char*)(t1003_r) + 28) = (int)(t1004);
    *(int*)((char*)(t1003_r) + 32) = (int)(t1004);
    *(int*)((char*)(t1003_r)) = (int)((int)g_0148738c);
    *(int*)((char*)(t1003_r) + 4) = (int)((int)g_0148737c);
    *(int*)((char*)(t1003_r) + 8) = (int)((int)g_01487a48);
    t1006 = (int)((int)g_01667bac);
    *(int*)((char*)(t1003_r) + 36) = (int)(t1006);
    *(int*)((char*)(t1003_r) + 40) = (int)(t1006);
    *(int*)((char*)(t1003_r) + 44) = (int)((int)g_01667bad);
    *(int*)((char*)(t1003_r) + 52) = (int)(t1004);
    *(float*)((char*)(t1003_r) + 68) = (float)(t1005);
    return (int)(t1003_r);
}
