// 0x004a2180: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004a1a70/s004a1a70.cpp, src/game/SPBake/SPEditorManipulationUtilities.cpp.

extern "C" unsigned char g_013ef578[];
extern "C" unsigned char g_01485378[];
struct C_004098a0 { void FUN_004098a0(unsigned int); };
extern "C" int __cdecl FUN_0041daf0(...);
struct C_00429360 { void FUN_00429360(unsigned int); };
struct C_0043f050 { void FUN_0043f050(unsigned int); };
struct C_0044ae00 { int FUN_0044ae00(unsigned int, unsigned int, unsigned int, unsigned int); };
struct C_0044c0e0 { void FUN_0044c0e0(unsigned int, unsigned int, unsigned int); };
struct C_00453eb0 { void FUN_00453eb0(); };
extern "C" void __cdecl FUN_0048c790(...);
#pragma pack(push, 1)
struct Fr0_004a2180 {
    int dead0[46];
};
#pragma pack(pop)

// @ 0x004a2180
extern "C" int __cdecl FUN_004a2180(int a4, int a8, int a12)
{
    Fr0_004a2180 fb;
    ((C_0044c0e0*)a12)->FUN_0044c0e0((unsigned int)(int)((int*)((char*)&fb + 140)), (unsigned int)(int)((int*)((char*)&fb + 156)), (unsigned int)(int)((int*)((char*)&fb + 180)));
    ((C_0044ae00*)a8)->FUN_0044ae00((unsigned int)(int)((int*)((char*)&fb + 68)), (unsigned int)1, (unsigned int)0, (unsigned int)0);
    (*((int*)((char*)&fb + 160))) = 0;
    (*((int*)((char*)&fb + 164))) = 0;
    (*((int*)((char*)&fb + 168))) = 0;
    ((C_00429360*)(int)((int*)((char*)&fb + 172)))->FUN_00429360((unsigned int)(int)((int*)((char*)&fb + 59)));
    FUN_0048c790((unsigned int)a8, (unsigned int)(int)((int*)((char*)&fb + 160)), (unsigned int)0);
    (*((int*)((char*)&fb + 64))) = 0;
    (*((int*)((char*)&fb + 60))) = (*((int*)((char*)&fb + 164))) - (*((int*)((char*)&fb + 160))) >> 2;
    for (; (*((int*)((char*)&fb + 64))) < (*((int*)((char*)&fb + 60))); (*((int*)((char*)&fb + 64))) = (*((int*)((char*)&fb + 64))) + 1) {
        (*((int*)((char*)&fb + 16))) = (*((int*)((char*)&fb + 160))) + ((*((int*)((char*)&fb + 64))) << 2);
        (*((int*)((char*)&fb + 12))) = (int)(int)*(int*)(char*)(*((int*)((char*)&fb + 16)));
        ((C_0043f050*)(int)((int*)((char*)&fb + 68)))->FUN_0043f050((unsigned int)((C_0044ae00*)(*((int*)((char*)&fb + 12))))->FUN_0044ae00((unsigned int)(int)((int*)((char*)&fb + 32)), (unsigned int)1, (unsigned int)0, (unsigned int)0));
    }
    ((C_004098a0*)(int)((int*)((char*)&fb + 144)))->FUN_004098a0((unsigned int)(int)((int*)((char*)&fb + 68)));
    ((C_0044ae00*)a12)->FUN_0044ae00((unsigned int)(int)((int*)((char*)&fb + 92)), (unsigned int)1, (unsigned int)0, (unsigned int)0);
    ((C_004098a0*)(int)&((int*)((char*)&fb + 116))[3])->FUN_004098a0((unsigned int)(int)((int*)((char*)&fb + 104)));
    *(float*)&((int*)((char*)&fb + 116))[0] = (float)*(float*)g_01485378;
    *(float*)&((int*)((char*)&fb + 116))[1] = (float)*(float*)g_01485378;
    *(float*)&((int*)((char*)&fb + 116))[2] = (float)*(float*)g_01485378;
    (*((int*)((char*)&fb + 8))) = (int)((int*)((char*)&fb + 144)) + ((*((int*)((char*)&fb + 156))) << 2);
    (*((int*)((char*)&fb + 4))) = (int)&((int*)((char*)&fb + 116))[3] + ((*((int*)((char*)&fb + 156))) << 2);
    *(float*)((char*)(int)((int*)((char*)&fb + 116)) + (*((int*)((char*)&fb + 156))) * 4) = (float)((float)(*(float*)(char*)(*((int*)((char*)&fb + 8))) - (float)*(float*)(char*)(*((int*)((char*)&fb + 4)))) * (float)*(float*)g_013ef578);
    (*((int*)((char*)&fb + 0))) = (int)(int)FUN_0041daf0((unsigned int)(int)((int*)((char*)&fb + 20)), (unsigned int)(int)((int*)((char*)&fb + 116)), (unsigned int)(a12 + 96));
    *(float*)&((int*)((char*)&fb + 116))[0] = *(float*)(char*)(*((int*)((char*)&fb + 0)));
    *(float*)&((int*)((char*)&fb + 116))[1] = *(float*)((char*)(*((int*)((char*)&fb + 0))) + 4);
    *(float*)&((int*)((char*)&fb + 116))[2] = *(float*)((char*)(*((int*)((char*)&fb + 0))) + 8);
    ((C_004098a0*)a4)->FUN_004098a0((unsigned int)(int)((int*)((char*)&fb + 116)));
    ((C_00453eb0*)(int)((int*)((char*)&fb + 160)))->FUN_00453eb0();
    return a4;
}
