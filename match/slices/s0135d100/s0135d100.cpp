// Slice s0135d100 -- property-descriptor dynamic initializers.
// Flags: /O2 /MD /Gy /EHsc /TP

typedef void (__cdecl *fp)();

struct T {
    const char* name;
    unsigned hash;
    int off;
    int p3, p4, p5;
    int z0, z1;
    fp f[7];
    T() {}
    T(const char* n, unsigned h, int o, fp f0, fp f1, fp f2, fp f3,
      fp f4, fp f5, fp f6)
        : name(n), hash(h), z0(0), z1(0) {
        f[0] = f0; f[1] = f1; f[2] = f2; f[3] = f3;
        f[4] = f4; f[5] = f5; f[6] = f6;
        off = o;
    }
};

extern T g_0157ea38, g_0157ea74, g_0157eab0, g_0157eaec, g_0157eb28;
extern T g_0157ee90, g_0157eecc;
extern T g_0157f290, g_0157f2cc, g_0157f308, g_0157f344, g_0157f380,
         g_0157f3bc, g_0157f3f8, g_0157f434, g_0157f470, g_0157f4ac;
extern T g_01580de0, g_01580e1c, g_01580e58, g_01580e94, g_01580ed0,
         g_01580f0c, g_01580f48, g_01580f84;
extern T g_01581d40, g_01581d7c, g_01581db8, g_01581df4, g_01581e30;
extern T g_01581f50, g_01581f8c;
extern T g_015829b8, g_015829f4, g_01582a30, g_01582a6c, g_01582aa8,
         g_01582ae4, g_01582b20;
extern unsigned char g_01582786, g_0169defc;

extern "C" {
void fn_00692ca0(); void fn_00ae3470(); void fn_00ae3490(); void fn_00ae3310();
void fn_00ac8050(); void fn_00572810(); void fn_00572840(); void fn_00693090();
void fn_00694f00(); void fn_00b1fbf0(); void fn_00675ca0(); void fn_00cc5d40();
void fn_00cc54f0(); void fn_00c2e4e0(); void fn_00692fb0(); void fn_00cc5010();
void fn_00d022e0(); void fn_00c95780(); void fn_00c6adc0(); void fn_00c6c4e0();
void fn_00cd36c0(); void fn_00bca960(); void fn_00b6f550(); void fn_00cd37b0();
void fn_00b6fc90(); void fn_00cd36f0(); void fn_00cd3920();
void fn_00cdb000(); void fn_00cd58d0(); void fn_00cd5940(); void fn_00ca8710();
void fn_00cdb4c0(); void fn_00cd5980(); void fn_00cd92f0(); void fn_00acdf10();
void fn_00aca730(); void fn_00b6f860(); void fn_00c6c390(); void fn_00ac88f0();
void fn_006930b0(); void fn_00694fc0(); void fn_00acbb80(); void fn_00c78020();
void fn_00ac9f70(); void fn_00cd6630(); void fn_00c78a50(); void fn_00ba8250();
void fn_00cd6680(); void fn_00cd6f60(); void fn_00ac8750(); void fn_00ac8780();
void fn_00694fa0(); void fn_0057ce00(); void fn_00ce26c0(); void fn_0057cde0();
void fn_00aca060(); void fn_00ae9e00(); void fn_00692ff0(); void fn_00694ee0();
void fn_00b6e3a0(); void fn_00ac88c0(); void fn_006930f0(); void fn_00695010();
void fn_00acbba0(); void fn_00d04aa0(); void fn_00d00ff0(); void fn_00d00c00();
void fn_00d03a40(); void fn_00c761c0(); void fn_00eafe40(); void fn_00aff840();
void fn_00aff870(); void fn_00692fd0(); void fn_00694ec0(); void fn_00595a70();
void fn_00c143c0(); void fn_00c143e0();
}

// @ 0x0135d100
void FUN_0135d100() {
    g_0157ea38 = T("mPostTutorialDelayTimer_Mating", 0x5ee5e11u, 0x10, fn_00692ca0, fn_00ae3470, fn_00ae3490, fn_00c2e4e0, fn_00692fb0, fn_00ae3310, fn_00ac8050);
    g_0157ea74 = T("mPostTutorialDelayTimer_Food", 0x66a2038u, 0x30, fn_00692ca0, fn_00ae3470, fn_00ae3490, fn_00c2e4e0, fn_00692fb0, fn_00ae3310, fn_00ac8050);
    g_0157eab0 = T("mTribeAppearanceProperty", 0x629a22du, 0xfc, fn_00692ca0, fn_00572810, fn_00572840, fn_00693090, fn_00694f00, fn_00b1fbf0, fn_00675ca0);
    g_0157eaec = T("mBabyGrowthTimers", 0x57a481eu, 0x60, fn_00692ca0, fn_00cc5d40, fn_00cc54f0, fn_00c2e4e0, fn_00692fb0, fn_00cc5010, fn_00d022e0);
    g_0157eb28 = T("mNPCTribeSpeciesKeys", 0x600dd49u, 0x7c, fn_00692ca0, fn_00c95780, fn_00c6adc0, fn_00c2e4e0, fn_00692fb0, fn_00b1fbf0, fn_00c6c4e0);
}

// @ 0x0135d720
void FUN_0135d720() {
    g_0157ee90 = T("mpTribeToTribeMission", 0xb43c938eu, 0x74, fn_00692ca0, fn_00cd36c0, fn_00bca960, fn_00c2e4e0, fn_00692fb0, fn_00b6f550, fn_00ac8050);
    g_0157eecc = T("mTribeToTribeMissionMap", 0x743c9504u, 0x78, fn_00692ca0, fn_00cd37b0, fn_00b6fc90, fn_00c2e4e0, fn_00692fb0, fn_00cd36f0, fn_00cd3920);
}

// @ 0x0135db90
void FUN_0135db90() {
    g_0157f290 = T("mGoalProgressHistory", 0x55ce8d1u, 0x40, fn_00692ca0, fn_00cdb000, fn_00cd58d0, fn_00c2e4e0, fn_00692fb0, fn_00cd5940, fn_00ca8710);
    g_0157f2cc = T("mFullHealsPerPerTribeMember", 0x5ee744au, 0x7c, fn_00692ca0, fn_00cdb4c0, fn_00cd5980, fn_00c2e4e0, fn_00692fb0, fn_00b1fbf0, fn_00cd92f0);
    g_0157f308 = T("mTotalTimeInTribe", 0x5ee6f2fu, 0x78, fn_00692ca0, fn_00572810, fn_00572840, fn_00693090, fn_00694f00, fn_00b1fbf0, fn_00675ca0);
    g_0157f344 = T("mEnchantedAnimals", 0x608904du, 0x94, fn_00692ca0, fn_00acdf10, fn_00aca730, fn_00c2e4e0, fn_00692fb0, fn_00b6f860, fn_00c6c390);
    g_0157f380 = T("mEnchantedAnimalsTimer", 0x60892b0u, 0x1a0, fn_00692ca0, fn_00572810, fn_00ac88f0, fn_006930b0, fn_00694fc0, fn_00b1fbf0, fn_00acbb80);
    g_0157f3bc = T("mUnlockedTools", 0x68c869au, 0xa8, fn_00692ca0, fn_00c78020, fn_00ac9f70, fn_00c2e4e0, fn_00692fb0, fn_00cd6630, fn_00c78a50);
    g_0157f3f8 = T("mpAccessories", 0x625716fu, 0x19c, fn_00692ca0, fn_00ba8250, fn_00bca960, fn_00c2e4e0, fn_00692fb0, fn_00b6f550, fn_00ac8050);
    g_0157f434 = T("mPlayerSpearOrnaments", 0x681efbau, 0x258, fn_00692ca0, fn_00cd6680, fn_00cd6f60, fn_00c2e4e0, fn_00692fb0, fn_00b6f550, fn_00ac8050);
    g_0157f470 = T("mNPCSpearOrnaments", 0x681efbbu, 0x2a8, fn_00692ca0, fn_00cd6680, fn_00cd6f60, fn_00c2e4e0, fn_00692fb0, fn_00b6f550, fn_00ac8050);
    g_0157f4ac = T("mbMatingAllowed", 0x68c86b2u, 0x3a3, fn_00692ca0, fn_00ac8750, fn_00ac8780, fn_00693090, fn_00694fa0, fn_00b1fbf0, fn_0057ce00);
}

// @ 0x0135e000
void FUN_0135e000() {
    T t;
    t.name = "mID"; t.hash = 0x58b5360u; t.z0 = 0; t.z1 = 0;
    t.f[0]=fn_00692ca0; t.f[1]=fn_00572810; t.f[2]=fn_00572840; t.f[3]=fn_00693090; t.f[4]=fn_00694f00; t.f[5]=fn_00b1fbf0; t.f[6]=fn_00675ca0; t.off=0;
    g_01580de0 = t;
    t.name = "mState"; t.hash = 0x58b5361u; t.z0 = 0; t.z1 = 0;
    t.f[0]=fn_00692ca0; t.f[1]=fn_00572810; t.f[2]=fn_00572840; t.f[3]=fn_00693090; t.f[4]=fn_00694f00; t.f[5]=fn_00b1fbf0; t.f[6]=fn_00675ca0; t.off=0x4;
    g_01580e1c = t;
    t.name = "mFrequency"; t.hash = 0x58b5362u; t.z0 = 0; t.z1 = 0;
    t.f[0]=fn_00692ca0; t.f[1]=fn_00572810; t.f[2]=fn_00572840; t.f[3]=fn_00693090; t.f[4]=fn_00694f00; t.f[5]=fn_00b1fbf0; t.f[6]=fn_00675ca0; t.off=0x8;
    g_01580e58 = t;
    t.name = "mCheckTime"; t.hash = 0x58b5363u; t.z0 = 0; t.z1 = 0;
    t.f[0]=fn_00692ca0; t.f[1]=fn_00572810; t.f[2]=fn_00ac88f0; t.f[3]=fn_006930b0; t.f[4]=fn_00694fc0; t.f[5]=fn_00b1fbf0; t.f[6]=fn_00acbb80; t.off=0xc;
    g_01580e94 = t;
    t.name = "mFoodRequired"; t.hash = 0x58b5364u; t.z0 = 0; t.z1 = 0;
    t.f[0]=fn_00692ca0; t.f[1]=fn_00572810; t.f[2]=fn_00572840; t.f[3]=fn_00692ff0; t.f[4]=fn_00694ee0; t.f[5]=fn_00b1fbf0; t.f[6]=fn_0057cde0; t.off=0x10;
    g_01580ed0 = t;
    t.name = "mFoodAccumulated"; t.hash = 0x58b5365u; t.z0 = 0; t.z1 = 0;
    t.f[0]=fn_00692ca0; t.f[1]=fn_00572810; t.f[2]=fn_00ac88f0; t.f[3]=fn_006930b0; t.f[4]=fn_00694fc0; t.f[5]=fn_00b1fbf0; t.f[6]=fn_00acbb80; t.off=0x14;
    g_01580f0c = t;
    t.name = "mbCheck"; t.hash = 0x58b5366u; t.z0 = 0; t.z1 = 0;
    t.f[0]=fn_00692ca0; t.f[1]=fn_00ac8750; t.f[2]=fn_00ac8780; t.f[3]=fn_00693090; t.f[4]=fn_00694fa0; t.f[5]=fn_00b1fbf0; t.f[6]=fn_0057ce00; t.off=0x18;
    g_01580f48 = t;
    t.name = "mWorkers"; t.hash = 0x58b536fu; t.z0 = 0; t.z1 = 0;
    t.f[0]=fn_00692ca0; t.f[1]=fn_00ce26c0; t.f[2]=fn_00aca730; t.f[3]=fn_00c2e4e0; t.f[4]=fn_00692fb0; t.f[5]=fn_00b6f860; t.f[6]=fn_00c6c390; t.off=0x1c;
    g_01580f84 = t;
}

// @ 0x01361ef0
void FUN_01361ef0() {
    g_01581d40 = T("mpSource", 0x4473680u, 0xc, fn_00692ca0, fn_00aca060, fn_00bca960, fn_00c2e4e0, fn_00692fb0, fn_00b6f550, (fp)0xac8050);
    g_01581d7c = T("mpTarget", 0x4473681u, 0x10, fn_00692ca0, fn_00ae9e00, fn_00bca960, fn_00c2e4e0, fn_00692fb0, fn_00b6f550, fn_00ac8050);
    g_01581db8 = T("mCommFileID", 0x4473682u, 0x14, fn_00692ca0, fn_00572810, fn_00572840, fn_00692ff0, fn_00694ee0, fn_00b1fbf0, fn_0057cde0);
    g_01581df4 = T("mCommGroupID", 0x4473683u, 0x18, fn_00692ca0, fn_00572810, fn_00572840, fn_00692ff0, fn_00694ee0, fn_00b1fbf0, fn_0057cde0);
    g_01581e30 = T("mPosition", 0x44dd929u, 0x1c, fn_00692ca0, fn_00b6e3a0, fn_00ac88c0, fn_006930f0, fn_00695010, fn_00b1fbf0, fn_00acbba0);
}

// @ 0x013621a0
void FUN_013621a0() {
    g_01581f50 = T("mRelationships", 0x56920bau, 0x24, fn_00692ca0, fn_00d04aa0, fn_00d00ff0, fn_00c2e4e0, fn_00692fb0, fn_00d00c00, fn_00d022e0);
    g_01581f8c = T("mEmpiresToDecayPending", 0x6538767u, 0x60, fn_00692ca0, fn_00d03a40, fn_00c761c0, fn_00c2e4e0, fn_00692fb0, fn_00b1fbf0, fn_00eafe40);
}

// @ 0x01363fe0
void FUN_01363fe0() {
    g_0169defc = g_01582786;
}

// @ 0x01364240
void FUN_01364240() {
    g_015829b8 = T("mCurrentBrainLevel", 0xb4177e0eu, 0x0, fn_00692ca0, (fp)0x572810, fn_00572840, fn_00692ff0, fn_00694ee0, fn_00b1fbf0, (fp)0x57cde0);
    g_015829f4 = T("mAvatarNormalizingScale", 0x61afd98u, 0x4, fn_00692ca0, (fp)0x572810, fn_00ac88f0, fn_006930b0, fn_00694fc0, fn_00b1fbf0, fn_00acbb80);
    g_01582a30 = T("mNumFlapsAllowed", 0x61afd99u, 0x8, fn_00692ca0, (fp)0x572810, fn_00572840, fn_00692ff0, fn_00694ee0, fn_00b1fbf0, (fp)0x57cde0);
    g_01582a6c = T("mAbilityMode", 0xb4177e0fu, 0x24, fn_00692ca0, (fp)0x572810, fn_00572840, fn_00693090, fn_00694f00, fn_00b1fbf0, fn_00675ca0);
    g_01582aa8 = T("mEvolutionPoints", 0x7220206fu, 0x28, fn_00692ca0, (fp)0x572810, fn_00ac88f0, fn_006930b0, fn_00694fc0, fn_00b1fbf0, fn_00acbb80);
    g_01582ae4 = T("DEPRECATED_mLearnedAbilities", 0xb4177e0du, 0x30, fn_00692ca0, fn_00aff840, fn_00aff870, fn_00692fd0, fn_00694ec0, fn_00b1fbf0, fn_00595a70);
    g_01582b20 = T("mLearnedAbilities", 0x76b6609u, 0x38, fn_00692ca0, fn_00c143c0, fn_00c143e0, fn_00c2e4e0, fn_00692fb0, fn_00b1fbf0, fn_00ac8050);
}
