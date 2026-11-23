// Slice s01278530: compiler-generated dynamic initializers for setting globals.
// Each one registers a named setting and stores the resulting id:
//     g_<addr> = FUN_00932e80("<name>", 0x811c9dc5, 1);
// 0x811c9dc5 is the FNV-1a offset basis, the last argument the register flag.
// One exception: 0x0129dbe0 registers a wide name through FNV1_String16
// (0x00932f30, movzx word ptr — the narrow FUN_00932e80 reads movzx byte ptr).
// Built /O2 /MD /Gy /EHsc /TP.

unsigned int FUN_00932e80(const char* s, unsigned int seed, int flag);
unsigned int FNV1_String16(const wchar_t* s, unsigned int seed, int flag);   // 0x00932f30 EA::Hash::FNV1_String16

extern unsigned int g_015e523c;
extern unsigned int g_015e51d4;
extern unsigned int g_015e54b4;
extern unsigned int g_015e544c;
extern unsigned int g_015e572c;
extern unsigned int g_015e56c4;
extern unsigned int g_015e59a4;
extern unsigned int g_015e593c;
extern unsigned int g_015e5c30;
extern unsigned int g_015e5bc8;
extern unsigned int g_015e5eac;
extern unsigned int g_015e5e44;
extern unsigned int g_015e6124;
extern unsigned int g_015e60bc;
extern unsigned int g_015e639c;
extern unsigned int g_015e6334;
extern unsigned int g_015e6614;
extern unsigned int g_015e65ac;
extern unsigned int g_015e688c;
extern unsigned int g_015e6824;
extern unsigned int g_015e6b04;
extern unsigned int g_015e6a9c;
extern unsigned int g_015e6d84;
extern unsigned int g_015e6d1c;
extern unsigned int g_015e6ffc;
extern unsigned int g_015e6f94;
extern unsigned int g_015e7274;
extern unsigned int g_015e720c;
extern unsigned int g_015e74ec;
extern unsigned int g_015e7484;
extern unsigned int g_015e7764;
extern unsigned int g_015e76fc;
extern unsigned int g_015e79dc;
extern unsigned int g_015e7974;
extern unsigned int g_015e7c54;
extern unsigned int g_015e7bec;
extern unsigned int g_015e7ecc;
extern unsigned int g_015e7e64;
extern unsigned int g_015e8144;
extern unsigned int g_015e80dc;
extern unsigned int g_015e83bc;
extern unsigned int g_015e8354;
extern unsigned int g_015e8634;
extern unsigned int g_015e85cc;
extern unsigned int g_015e88b8;
extern unsigned int g_015e8850;
extern unsigned int g_015e8b3c;
extern unsigned int g_015e8ad4;
extern unsigned int g_015e8db4;
extern unsigned int g_015e8d4c;
extern unsigned int g_015e902c;
extern unsigned int g_015e8fc4;
extern unsigned int g_015e92a4;
extern unsigned int g_015e923c;
extern unsigned int g_015e951c;
extern unsigned int g_015e94b4;
extern unsigned int g_015e9794;
extern unsigned int g_015e972c;
extern unsigned int g_015e9a0c;
extern unsigned int g_015e99a4;
extern unsigned int g_015e9c84;
extern unsigned int g_015e9c1c;
extern unsigned int g_015e9efc;
extern unsigned int g_015e9e94;
extern unsigned int g_015ea174;
extern unsigned int g_015ea10c;
extern unsigned int g_015ea3ec;
extern unsigned int g_015ea384;
extern unsigned int g_015ea668;
extern unsigned int g_015ea600;
extern unsigned int g_015ea8e4;
extern unsigned int g_015ea87c;
extern unsigned int g_015eab5c;
extern unsigned int g_015eaaf4;
extern unsigned int g_015eadd4;
extern unsigned int g_015ead6c;
extern unsigned int g_015eb04c;
extern unsigned int g_015eafe4;
extern unsigned int g_015eb2c4;
extern unsigned int g_015eb25c;
extern unsigned int g_015eb53c;
extern unsigned int g_015eb4d4;
extern unsigned int g_015eb7b4;
extern unsigned int g_015eb74c;
extern unsigned int g_015eba3c;
extern unsigned int g_015eb9d4;
extern unsigned int g_015ebcb4;
extern unsigned int g_015ebc4c;
extern unsigned int g_015ebf2c;
extern unsigned int g_015ebec4;
extern unsigned int g_015ec1a4;
extern unsigned int g_015ec13c;
extern unsigned int g_015ec41c;
extern unsigned int g_015ec3b4;
extern unsigned int g_015ec694;
extern unsigned int g_015ec62c;
extern unsigned int g_015ec90c;
extern unsigned int g_015ec8a4;
extern unsigned int g_015ecb84;
extern unsigned int g_015ecb1c;
extern unsigned int g_015ecdfc;
extern unsigned int g_015ecd94;
extern unsigned int g_015ed074;
extern unsigned int g_015ed00c;
extern unsigned int g_015ed2ec;
extern unsigned int g_015ed284;
extern unsigned int g_015ed564;
extern unsigned int g_015ed4fc;
extern unsigned int g_015ed7dc;
extern unsigned int g_015ed774;
extern unsigned int g_015eda54;
extern unsigned int g_015ed9ec;
extern unsigned int g_015edccc;
extern unsigned int g_015edc64;
extern unsigned int g_015edf44;
extern unsigned int g_015ededc;
extern unsigned int g_015ee1bc;
extern unsigned int g_015ee154;
extern unsigned int g_015ee440;
extern unsigned int g_015ee3d8;
extern unsigned int g_015ee6bc;
extern unsigned int g_015ee654;
extern unsigned int g_015ee940;
extern unsigned int g_015ee8cc;
extern unsigned int g_015eebd4;
extern unsigned int g_015eeb6c;
extern unsigned int g_015eee5c;
extern unsigned int g_015eedf4;
extern unsigned int g_015ef0d4;
extern unsigned int g_015ef06c;
extern unsigned int g_015ef34c;
extern unsigned int g_015ef2e4;
extern unsigned int g_015ef5c4;
extern unsigned int g_015ef55c;
extern unsigned int g_015ef83c;
extern unsigned int g_015ef7d4;
extern unsigned int g_015efab4;
extern unsigned int g_015efa4c;
extern unsigned int g_015efd2c;
extern unsigned int g_015efcc4;
extern unsigned int g_015effb4;
extern unsigned int g_015eff4c;
extern unsigned int g_015f0234;
extern unsigned int g_015f01cc;
extern unsigned int g_015f04bc;
extern unsigned int g_015f0454;
extern unsigned int g_015f0734;
extern unsigned int g_015f06cc;
extern unsigned int g_015f09ac;
extern unsigned int g_015f0944;
extern unsigned int g_015f0c34;
extern unsigned int g_015f0bcc;
extern unsigned int g_015f0eac;
extern unsigned int g_015f0e44;
extern unsigned int g_015f1124;
extern unsigned int g_015f10bc;
extern unsigned int g_015f139c;
extern unsigned int g_015f1334;
extern unsigned int g_015f1614;
extern unsigned int g_015f15ac;
extern unsigned int g_015f188c;
extern unsigned int g_015f1824;
extern unsigned int g_015f1b04;
extern unsigned int g_015f1a9c;
extern unsigned int g_015f1d7c;
extern unsigned int g_015f1d14;
extern unsigned int g_015f1ff8;
extern unsigned int g_015f1f90;
extern unsigned int g_015f226c;
extern unsigned int g_015f2204;
extern unsigned int g_015f24e4;
extern unsigned int g_015f247c;
extern unsigned int g_015f275c;
extern unsigned int g_015f26f4;
extern unsigned int g_015f29e4;
extern unsigned int g_015f297c;
extern unsigned int g_015f2c5c;
extern unsigned int g_015f2bf4;
extern unsigned int g_015f2ed4;
extern unsigned int g_015f2e6c;
extern unsigned int g_015f314c;
extern unsigned int g_015f30e4;
extern unsigned int g_015f33cc;
extern unsigned int g_015f3364;
extern unsigned int g_015f3658;
extern unsigned int g_015f35f0;
extern unsigned int g_015f35e8;
extern unsigned int g_015f386c;
extern unsigned int g_015f3b4c;
extern unsigned int g_015f3ae4;
extern unsigned int g_015f3dc4;
extern unsigned int g_015f3d5c;
extern unsigned int g_015f4040;
extern unsigned int g_015f3fd8;
extern unsigned int g_015f42c0;
extern unsigned int g_015f4258;
extern unsigned int g_015f453c;
extern unsigned int g_015f44d4;
extern unsigned int g_015f47b4;
extern unsigned int g_015f474c;
extern unsigned int g_015f4a3c;
extern unsigned int g_015f49d4;
extern unsigned int g_015f4cb4;
extern unsigned int g_015f4c4c;
extern unsigned int g_015f4f44;
extern unsigned int g_015f4edc;
extern unsigned int g_015f522c;
extern unsigned int g_015f51a4;
extern unsigned int g_015f56e8;
extern unsigned int g_015f5680;
extern unsigned int g_015f598c;
extern unsigned int g_015f5920;
extern unsigned int g_015f5c34;
extern unsigned int g_015f5b9c;
extern unsigned int g_015f5eb0;
extern unsigned int g_015f5e48;
extern unsigned int g_015f6130;
extern unsigned int g_015f60c8;
extern unsigned int g_015f640c;
extern unsigned int g_015f63a4;
extern unsigned int g_015f6694;
extern unsigned int g_015f662c;
extern unsigned int g_015f690c;
extern unsigned int g_015f68a4;
extern unsigned int g_015f6b8c;
extern unsigned int g_015f6b24;
extern unsigned int g_015f6e04;
extern unsigned int g_015f6d9c;
extern unsigned int g_015f7084;
extern unsigned int g_015f701c;
extern unsigned int g_015f72fc;
extern unsigned int g_015f7294;
extern unsigned int g_015f7574;
extern unsigned int g_015f750c;
extern unsigned int g_015f77ec;
extern unsigned int g_015f7784;
extern unsigned int g_015f7a64;
extern unsigned int g_015f79fc;
extern unsigned int g_015f7cdc;
extern unsigned int g_015f7c74;
extern unsigned int g_015f7f5c;
extern unsigned int g_015f7ef4;
extern unsigned int g_015f81d4;
extern unsigned int g_015f816c;
extern unsigned int g_015f8454;
extern unsigned int g_015f83ec;
extern unsigned int g_015f86cc;
extern unsigned int g_015f8664;
extern unsigned int g_015f8944;
extern unsigned int g_015f88dc;
extern unsigned int g_015f8bc4;
extern unsigned int g_015f8b5c;
extern unsigned int g_015f8e3c;
extern unsigned int g_015f8dd4;
extern unsigned int g_015f90b4;
extern unsigned int g_015f904c;
extern unsigned int g_015f932c;
extern unsigned int g_015f92c4;
extern unsigned int g_015f95a8;
extern unsigned int g_015f9540;
extern unsigned int g_015f9890;
extern unsigned int g_015f9828;
extern unsigned int g_015f9b0c;
extern unsigned int g_015f9aa4;
extern unsigned int g_015f9d84;
extern unsigned int g_015f9d1c;
extern unsigned int g_015fa000;
extern unsigned int g_015f9f98;
extern unsigned int g_015fa298;
extern unsigned int g_015fa228;
extern unsigned int g_015fa528;
extern unsigned int g_015fa4c0;
extern unsigned int g_015fa7a4;
extern unsigned int g_015fa73c;
extern unsigned int g_015faa1c;
extern unsigned int g_015fa9b4;
extern unsigned int g_015fac94;
extern unsigned int g_015fac2c;
extern unsigned int g_015faf0c;
extern unsigned int g_015faea4;
extern unsigned int g_015fb198;
extern unsigned int g_015fb11c;
extern unsigned int g_015fb424;
extern unsigned int g_015fb3bc;
extern unsigned int g_015fb69c;
extern unsigned int g_015fb634;
extern unsigned int g_015fb918;
extern unsigned int g_015fb8b0;
extern unsigned int g_015fbb98;
extern unsigned int g_015fbb30;
extern unsigned int g_015fbe14;
extern unsigned int g_015fbdac;
extern unsigned int g_015fc090;
extern unsigned int g_015fc028;
extern unsigned int g_015fc314;
extern unsigned int g_015fc2a8;
extern unsigned int g_015fc58c;
extern unsigned int g_015fc524;
extern unsigned int g_015fc808;
extern unsigned int g_015fc7a0;
extern unsigned int g_015fc810;
extern unsigned int g_015fc834;
extern unsigned int g_015fc824;
extern unsigned int g_015fca8c;
extern unsigned int g_015fca24;

// @ 0x01278530
void FUN_01278530() { g_015e523c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01278550
void FUN_01278550() { g_015e51d4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01278ce0
void FUN_01278ce0() { g_015e54b4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01278d00
void FUN_01278d00() { g_015e544c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01279360
void FUN_01279360() { g_015e572c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01279380
void FUN_01279380() { g_015e56c4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012799f0
void FUN_012799f0() { g_015e59a4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01279a10
void FUN_01279a10() { g_015e593c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0127a070
void FUN_0127a070() { g_015e5c30 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0127a090
void FUN_0127a090() { g_015e5bc8 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0127a6d0
void FUN_0127a6d0() { g_015e5eac = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0127a6f0
void FUN_0127a6f0() { g_015e5e44 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0127ad30
void FUN_0127ad30() { g_015e6124 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0127ad50
void FUN_0127ad50() { g_015e60bc = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0127b3c0
void FUN_0127b3c0() { g_015e639c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0127b3e0
void FUN_0127b3e0() { g_015e6334 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0127ba20
void FUN_0127ba20() { g_015e6614 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0127ba40
void FUN_0127ba40() { g_015e65ac = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0127c080
void FUN_0127c080() { g_015e688c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0127c0a0
void FUN_0127c0a0() { g_015e6824 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0127c710
void FUN_0127c710() { g_015e6b04 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0127c730
void FUN_0127c730() { g_015e6a9c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0127cdb0
void FUN_0127cdb0() { g_015e6d84 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0127cdd0
void FUN_0127cdd0() { g_015e6d1c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0127d420
void FUN_0127d420() { g_015e6ffc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0127d440
void FUN_0127d440() { g_015e6f94 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0127da80
void FUN_0127da80() { g_015e7274 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0127daa0
void FUN_0127daa0() { g_015e720c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0127e0e0
void FUN_0127e0e0() { g_015e74ec = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0127e100
void FUN_0127e100() { g_015e7484 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0127e740
void FUN_0127e740() { g_015e7764 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0127e760
void FUN_0127e760() { g_015e76fc = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0127eda0
void FUN_0127eda0() { g_015e79dc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0127edc0
void FUN_0127edc0() { g_015e7974 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0127f420
void FUN_0127f420() { g_015e7c54 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0127f440
void FUN_0127f440() { g_015e7bec = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0127fa80
void FUN_0127fa80() { g_015e7ecc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0127faa0
void FUN_0127faa0() { g_015e7e64 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012800e0
void FUN_012800e0() { g_015e8144 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01280100
void FUN_01280100() { g_015e80dc = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01280740
void FUN_01280740() { g_015e83bc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01280760
void FUN_01280760() { g_015e8354 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01280db0
void FUN_01280db0() { g_015e8634 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01280dd0
void FUN_01280dd0() { g_015e85cc = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01281420
void FUN_01281420() { g_015e88b8 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01281440
void FUN_01281440() { g_015e8850 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01281b20
void FUN_01281b20() { g_015e8b3c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01281b40
void FUN_01281b40() { g_015e8ad4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01282180
void FUN_01282180() { g_015e8db4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012821a0
void FUN_012821a0() { g_015e8d4c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012827e0
void FUN_012827e0() { g_015e902c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01282800
void FUN_01282800() { g_015e8fc4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01282e40
void FUN_01282e40() { g_015e92a4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01282e60
void FUN_01282e60() { g_015e923c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012834b0
void FUN_012834b0() { g_015e951c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012834d0
void FUN_012834d0() { g_015e94b4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01283b10
void FUN_01283b10() { g_015e9794 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01283b30
void FUN_01283b30() { g_015e972c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01284170
void FUN_01284170() { g_015e9a0c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01284190
void FUN_01284190() { g_015e99a4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012847d0
void FUN_012847d0() { g_015e9c84 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012847f0
void FUN_012847f0() { g_015e9c1c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01284e30
void FUN_01284e30() { g_015e9efc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01284e50
void FUN_01284e50() { g_015e9e94 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012854b0
void FUN_012854b0() { g_015ea174 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012854d0
void FUN_012854d0() { g_015ea10c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01285b10
void FUN_01285b10() { g_015ea3ec = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01285b30
void FUN_01285b30() { g_015ea384 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01286170
void FUN_01286170() { g_015ea668 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01286190
void FUN_01286190() { g_015ea600 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012867d0
void FUN_012867d0() { g_015ea8e4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012867f0
void FUN_012867f0() { g_015ea87c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01286e30
void FUN_01286e30() { g_015eab5c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01286e50
void FUN_01286e50() { g_015eaaf4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012874b0
void FUN_012874b0() { g_015eadd4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012874d0
void FUN_012874d0() { g_015ead6c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01287b10
void FUN_01287b10() { g_015eb04c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01287b30
void FUN_01287b30() { g_015eafe4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01288170
void FUN_01288170() { g_015eb2c4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01288190
void FUN_01288190() { g_015eb25c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012887d0
void FUN_012887d0() { g_015eb53c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012887f0
void FUN_012887f0() { g_015eb4d4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01288e30
void FUN_01288e30() { g_015eb7b4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01288e50
void FUN_01288e50() { g_015eb74c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01289520
void FUN_01289520() { g_015eba3c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01289540
void FUN_01289540() { g_015eb9d4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01289b80
void FUN_01289b80() { g_015ebcb4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01289ba0
void FUN_01289ba0() { g_015ebc4c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0128a210
void FUN_0128a210() { g_015ebf2c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0128a230
void FUN_0128a230() { g_015ebec4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0128a870
void FUN_0128a870() { g_015ec1a4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0128a890
void FUN_0128a890() { g_015ec13c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0128aed0
void FUN_0128aed0() { g_015ec41c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0128aef0
void FUN_0128aef0() { g_015ec3b4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0128b530
void FUN_0128b530() { g_015ec694 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0128b550
void FUN_0128b550() { g_015ec62c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0128bb90
void FUN_0128bb90() { g_015ec90c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0128bbb0
void FUN_0128bbb0() { g_015ec8a4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0128c1f0
void FUN_0128c1f0() { g_015ecb84 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0128c210
void FUN_0128c210() { g_015ecb1c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0128c850
void FUN_0128c850() { g_015ecdfc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0128c870
void FUN_0128c870() { g_015ecd94 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0128ceb0
void FUN_0128ceb0() { g_015ed074 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0128ced0
void FUN_0128ced0() { g_015ed00c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0128d510
void FUN_0128d510() { g_015ed2ec = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0128d530
void FUN_0128d530() { g_015ed284 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0128db70
void FUN_0128db70() { g_015ed564 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0128db90
void FUN_0128db90() { g_015ed4fc = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0128e1d0
void FUN_0128e1d0() { g_015ed7dc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0128e1f0
void FUN_0128e1f0() { g_015ed774 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0128e830
void FUN_0128e830() { g_015eda54 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0128e850
void FUN_0128e850() { g_015ed9ec = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0128ee90
void FUN_0128ee90() { g_015edccc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0128eeb0
void FUN_0128eeb0() { g_015edc64 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0128f520
void FUN_0128f520() { g_015edf44 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0128f540
void FUN_0128f540() { g_015ededc = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0128fbb0
void FUN_0128fbb0() { g_015ee1bc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0128fbd0
void FUN_0128fbd0() { g_015ee154 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01290250
void FUN_01290250() { g_015ee440 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01290270
void FUN_01290270() { g_015ee3d8 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012908d0
void FUN_012908d0() { g_015ee6bc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012908f0
void FUN_012908f0() { g_015ee654 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01290f30
void FUN_01290f30() { g_015ee940 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01290f50
void FUN_01290f50() { g_015ee8cc = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01291650
void FUN_01291650() { g_015eebd4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01291670
void FUN_01291670() { g_015eeb6c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01291cf0
void FUN_01291cf0() { g_015eee5c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01291d10
void FUN_01291d10() { g_015eedf4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01292390
void FUN_01292390() { g_015ef0d4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012923b0
void FUN_012923b0() { g_015ef06c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012929f0
void FUN_012929f0() { g_015ef34c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01292a10
void FUN_01292a10() { g_015ef2e4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01293050
void FUN_01293050() { g_015ef5c4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01293070
void FUN_01293070() { g_015ef55c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012936b0
void FUN_012936b0() { g_015ef83c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012936d0
void FUN_012936d0() { g_015ef7d4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01293d40
void FUN_01293d40() { g_015efab4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01293d60
void FUN_01293d60() { g_015efa4c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012943c0
void FUN_012943c0() { g_015efd2c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012943e0
void FUN_012943e0() { g_015efcc4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01294a20
void FUN_01294a20() { g_015effb4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01294a40
void FUN_01294a40() { g_015eff4c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012950d0
void FUN_012950d0() { g_015f0234 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012950f0
void FUN_012950f0() { g_015f01cc = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01295730
void FUN_01295730() { g_015f04bc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01295750
void FUN_01295750() { g_015f0454 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01295dc0
void FUN_01295dc0() { g_015f0734 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01295de0
void FUN_01295de0() { g_015f06cc = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01296420
void FUN_01296420() { g_015f09ac = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01296440
void FUN_01296440() { g_015f0944 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01296aa0
void FUN_01296aa0() { g_015f0c34 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01296ac0
void FUN_01296ac0() { g_015f0bcc = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01297130
void FUN_01297130() { g_015f0eac = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01297150
void FUN_01297150() { g_015f0e44 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01297790
void FUN_01297790() { g_015f1124 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012977b0
void FUN_012977b0() { g_015f10bc = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01297df0
void FUN_01297df0() { g_015f139c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01297e10
void FUN_01297e10() { g_015f1334 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01298450
void FUN_01298450() { g_015f1614 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01298470
void FUN_01298470() { g_015f15ac = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01298ab0
void FUN_01298ab0() { g_015f188c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01298ad0
void FUN_01298ad0() { g_015f1824 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01299110
void FUN_01299110() { g_015f1b04 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01299130
void FUN_01299130() { g_015f1a9c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012997a0
void FUN_012997a0() { g_015f1d7c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012997c0
void FUN_012997c0() { g_015f1d14 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01299e00
void FUN_01299e00() { g_015f1ff8 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01299e20
void FUN_01299e20() { g_015f1f90 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0129a4c0
void FUN_0129a4c0() { g_015f226c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0129a4e0
void FUN_0129a4e0() { g_015f2204 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0129ab20
void FUN_0129ab20() { g_015f24e4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0129ab40
void FUN_0129ab40() { g_015f247c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0129b1b0
void FUN_0129b1b0() { g_015f275c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0129b1d0
void FUN_0129b1d0() { g_015f26f4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0129b810
void FUN_0129b810() { g_015f29e4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0129b830
void FUN_0129b830() { g_015f297c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0129be70
void FUN_0129be70() { g_015f2c5c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0129be90
void FUN_0129be90() { g_015f2bf4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0129c500
void FUN_0129c500() { g_015f2ed4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0129c520
void FUN_0129c520() { g_015f2e6c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0129cb60
void FUN_0129cb60() { g_015f314c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0129cb80
void FUN_0129cb80() { g_015f30e4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0129d1c0
void FUN_0129d1c0() { g_015f33cc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0129d1e0
void FUN_0129d1e0() { g_015f3364 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0129d820
void FUN_0129d820() { g_015f3658 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0129d840
void FUN_0129d840() { g_015f35f0 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0129dbe0
void FUN_0129dbe0() { g_015f35e8 = FNV1_String16(L"login", 0x811c9dc5, 1); }
// @ 0x0129df30
void FUN_0129df30() { g_015f386c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0129e590
void FUN_0129e590() { g_015f3b4c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0129e5b0
void FUN_0129e5b0() { g_015f3ae4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0129ebf0
void FUN_0129ebf0() { g_015f3dc4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0129ec10
void FUN_0129ec10() { g_015f3d5c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0129f250
void FUN_0129f250() { g_015f4040 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0129f270
void FUN_0129f270() { g_015f3fd8 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0129f8e0
void FUN_0129f8e0() { g_015f42c0 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0129f900
void FUN_0129f900() { g_015f4258 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0129ff70
void FUN_0129ff70() { g_015f453c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0129ff90
void FUN_0129ff90() { g_015f44d4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a05d0
void FUN_012a05d0() { g_015f47b4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a05f0
void FUN_012a05f0() { g_015f474c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a0c30
void FUN_012a0c30() { g_015f4a3c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a0c50
void FUN_012a0c50() { g_015f49d4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a12c0
void FUN_012a12c0() { g_015f4cb4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a12e0
void FUN_012a12e0() { g_015f4c4c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a1930
void FUN_012a1930() { g_015f4f44 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a1950
void FUN_012a1950() { g_015f4edc = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a1fb0
void FUN_012a1fb0() { g_015f522c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a1fd0
void FUN_012a1fd0() { g_015f51a4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a29e0
void FUN_012a29e0() { g_015f56e8 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a2a00
void FUN_012a2a00() { g_015f5680 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a3160
void FUN_012a3160() { g_015f598c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a3180
void FUN_012a3180() { g_015f5920 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a37f0
void FUN_012a37f0() { g_015f5c34 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a3810
void FUN_012a3810() { g_015f5b9c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a3e70
void FUN_012a3e70() { g_015f5eb0 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a3e90
void FUN_012a3e90() { g_015f5e48 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a44e0
void FUN_012a44e0() { g_015f6130 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a4500
void FUN_012a4500() { g_015f60c8 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a4dc0
void FUN_012a4dc0() { g_015f640c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a4de0
void FUN_012a4de0() { g_015f63a4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a5430
void FUN_012a5430() { g_015f6694 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a5450
void FUN_012a5450() { g_015f662c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a5a90
void FUN_012a5a90() { g_015f690c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a5ab0
void FUN_012a5ab0() { g_015f68a4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a6110
void FUN_012a6110() { g_015f6b8c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a6130
void FUN_012a6130() { g_015f6b24 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a6770
void FUN_012a6770() { g_015f6e04 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a6790
void FUN_012a6790() { g_015f6d9c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a6e20
void FUN_012a6e20() { g_015f7084 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a6e40
void FUN_012a6e40() { g_015f701c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a7480
void FUN_012a7480() { g_015f72fc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a74a0
void FUN_012a74a0() { g_015f7294 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a7ae0
void FUN_012a7ae0() { g_015f7574 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a7b00
void FUN_012a7b00() { g_015f750c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a8170
void FUN_012a8170() { g_015f77ec = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a8190
void FUN_012a8190() { g_015f7784 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a8800
void FUN_012a8800() { g_015f7a64 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a8820
void FUN_012a8820() { g_015f79fc = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a8ed0
void FUN_012a8ed0() { g_015f7cdc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a8ef0
void FUN_012a8ef0() { g_015f7c74 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a9570
void FUN_012a9570() { g_015f7f5c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a9590
void FUN_012a9590() { g_015f7ef4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012a9c00
void FUN_012a9c00() { g_015f81d4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012a9c20
void FUN_012a9c20() { g_015f816c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012aa280
void FUN_012aa280() { g_015f8454 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012aa2a0
void FUN_012aa2a0() { g_015f83ec = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012aa8e0
void FUN_012aa8e0() { g_015f86cc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012aa900
void FUN_012aa900() { g_015f8664 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012aaf40
void FUN_012aaf40() { g_015f8944 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012aaf60
void FUN_012aaf60() { g_015f88dc = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012ab600
void FUN_012ab600() { g_015f8bc4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012ab620
void FUN_012ab620() { g_015f8b5c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012abce0
void FUN_012abce0() { g_015f8e3c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012abd00
void FUN_012abd00() { g_015f8dd4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012ac360
void FUN_012ac360() { g_015f90b4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012ac380
void FUN_012ac380() { g_015f904c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012ac9c0
void FUN_012ac9c0() { g_015f932c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012ac9e0
void FUN_012ac9e0() { g_015f92c4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012ad020
void FUN_012ad020() { g_015f95a8 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012ad040
void FUN_012ad040() { g_015f9540 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012ad6b0
void FUN_012ad6b0() { g_015f9890 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012ad6d0
void FUN_012ad6d0() { g_015f9828 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012add40
void FUN_012add40() { g_015f9b0c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012add60
void FUN_012add60() { g_015f9aa4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012ae3f0
void FUN_012ae3f0() { g_015f9d84 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012ae410
void FUN_012ae410() { g_015f9d1c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012aea50
void FUN_012aea50() { g_015fa000 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012aea70
void FUN_012aea70() { g_015f9f98 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012af100
void FUN_012af100() { g_015fa298 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012af120
void FUN_012af120() { g_015fa228 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012af8b0
void FUN_012af8b0() { g_015fa528 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012af8d0
void FUN_012af8d0() { g_015fa4c0 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012aff70
void FUN_012aff70() { g_015fa7a4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012aff90
void FUN_012aff90() { g_015fa73c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012b05d0
void FUN_012b05d0() { g_015faa1c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012b05f0
void FUN_012b05f0() { g_015fa9b4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012b0c30
void FUN_012b0c30() { g_015fac94 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012b0c50
void FUN_012b0c50() { g_015fac2c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012b1290
void FUN_012b1290() { g_015faf0c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012b12b0
void FUN_012b12b0() { g_015faea4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012b1920
void FUN_012b1920() { g_015fb198 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012b1940
void FUN_012b1940() { g_015fb11c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012b1fb0
void FUN_012b1fb0() { g_015fb424 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012b1fd0
void FUN_012b1fd0() { g_015fb3bc = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012b2640
void FUN_012b2640() { g_015fb69c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012b2660
void FUN_012b2660() { g_015fb634 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012b2cd0
void FUN_012b2cd0() { g_015fb918 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012b2cf0
void FUN_012b2cf0() { g_015fb8b0 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012b3360
void FUN_012b3360() { g_015fbb98 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012b3380
void FUN_012b3380() { g_015fbb30 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012b39f0
void FUN_012b39f0() { g_015fbe14 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012b3a10
void FUN_012b3a10() { g_015fbdac = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012b4050
void FUN_012b4050() { g_015fc090 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012b4070
void FUN_012b4070() { g_015fc028 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012b46e0
void FUN_012b46e0() { g_015fc314 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012b4700
void FUN_012b4700() { g_015fc2a8 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012b4f40
void FUN_012b4f40() { g_015fc58c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012b4f60
void FUN_012b4f60() { g_015fc524 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012b55b0
void FUN_012b55b0() { g_015fc808 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012b55d0
void FUN_012b55d0() { g_015fc7a0 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x012b5940
void FUN_012b5940() { g_015fc810 = FUN_00932e80("CalloutSample", 0x811c9dc5, 1); }
// @ 0x012b5960
void FUN_012b5960() { g_015fc834 = FUN_00932e80("CalloutSample1", 0x811c9dc5, 1); }
// @ 0x012b5980
void FUN_012b5980() { g_015fc824 = FUN_00932e80("CalloutSample2", 0x811c9dc5, 1); }
// @ 0x012b5c70
void FUN_012b5c70() { g_015fca8c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x012b5c90
void FUN_012b5c90() { g_015fca24 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
