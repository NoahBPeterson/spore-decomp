typedef unsigned int u32;

struct PropDesc {
    const char* mName;   // +0x00
    u32 mHash;   // +0x04
    u32 mType;   // +0x08
    u32 mPad0C;   // +0x0c
    u32 mPad10;   // +0x10
    u32 mPad14;   // +0x14
    u32 mZero18;   // +0x18
    u32 mZero1C;   // +0x1c
    void* mDefault;   // +0x20
    void* mFn24;   // +0x24
    void* mFn28;   // +0x28
    void* mFn2C;   // +0x2c
    void* mFn30;   // +0x30
    void* mFn34;   // +0x34
    void* mFn38;   // +0x38
};

extern void S3800_F34A();   // 0x00b1fbf0
extern void S3800_F34B();   // 0x00b1fbf0
extern void S3800_F38A();   // 0x0057cde0
extern void S3800_F38B();   // 0x00675ca0
extern void SAE0_F2CB();   // 0x00c2e4e0
extern void SAE0_F30B();   // 0x00692fb0
extern void SAE0_F34A();   // 0x00b1fbf0
extern void SAE0_F38A();   // 0x00b8e840
extern void SE60_F34();   // 0x00b1fbf0
extern void SE60_F38();   // 0x0057cde0
extern void U_01351ae0_0_24();   // 0x00bb9cd0
extern void U_01351ae0_0_28();   // 0x00bb9d00
extern void U_01351ae0_0_34();   // 0x00b1fbf0
extern void U_01351ae0_1_24();   // 0x00bb9cd0
extern void U_01351ae0_1_28();   // 0x00bb9d00
extern void U_01351ae0_1_2c();   // 0x00693050
extern void U_01351ae0_1_30();   // 0x00694f60
extern void U_01351ae0_2_24();   // 0x00bb9cd0
extern void U_01351ae0_2_28();   // 0x00bb9d00
extern void U_01351ae0_2_2c();   // 0x00693050
extern void U_01351ae0_2_30();   // 0x00694f60
extern void U_01351ae0_3_24();   // 0x00c7b390
extern void U_01351ae0_3_28();   // 0x00c76250
extern void U_01351ae0_3_34();   // 0x00b1fbf0
extern void U_01351ae0_3_38();   // 0x00c79290
extern void U_01351ae0_4_24();   // 0x00c7b390
extern void U_01351ae0_4_28();   // 0x00c76250
extern void U_01351ae0_4_34();   // 0x00b1fbf0
extern void U_01351ae0_4_38();   // 0x00c79290
extern void U_01351ae0_5_24();   // 0x00c7b390
extern void U_01351ae0_5_28();   // 0x00c76250
extern void U_01351ae0_5_34();   // 0x00b1fbf0
extern void U_01351ae0_5_38();   // 0x00c79290
extern void U_01351ae0_6_24();   // 0x00c7b390
extern void U_01351ae0_6_28();   // 0x00c76250
extern void U_01351ae0_6_34();   // 0x00b1fbf0
extern void U_01351ae0_6_38();   // 0x00c79290
extern void U_01351ae0_7_34();   // 0x00b1fbf0
extern void U_01351e60_0_24();   // 0x00572810
extern void U_01351e60_0_28();   // 0x00572840
extern void U_01351e60_0_34();   // 0x00b1fbf0
extern void U_01351e60_2_24();   // 0x00572810
extern void U_01351e60_2_28();   // 0x00572840
extern void U_01351e60_2_2c();   // 0x00692ff0
extern void U_01351e60_2_30();   // 0x00694ee0
extern void U_01351e60_3_24();   // 0x00572810
extern void U_01351e60_3_28();   // 0x00572840
extern void U_01351e60_3_2c();   // 0x00692ff0
extern void U_01351e60_3_30();   // 0x00694ee0
extern void U_01351e60_4_24();   // 0x00572810
extern void U_01351e60_4_28();   // 0x00572840
extern void U_01351e60_4_2c();   // 0x00692ff0
extern void U_01351e60_4_30();   // 0x00694ee0
extern void U_01351e60_5_24();   // 0x00572810
extern void U_01351e60_5_28();   // 0x00572840
extern void U_01351e60_5_2c();   // 0x00692ff0
extern void U_01351e60_5_30();   // 0x00694ee0
extern void U_01352460_0_34();   // 0x00b1fbf0
extern void U_01352460_0_38();   // 0x00b1fbf0
extern void U_01353800_0_34();   // 0x00b1fbf0
extern void U_01353800_1_24();   // 0x00572810
extern void U_01353800_1_28();   // 0x00572840
extern void U_01353800_1_2c();   // 0x00692ff0
extern void U_01353800_1_30();   // 0x00694ee0
extern void U_01353800_2_24();   // 0x00572810
extern void U_01353800_2_28();   // 0x00572840
extern void U_01353800_2_2c();   // 0x00692ff0
extern void U_01353800_2_30();   // 0x00694ee0
extern void U_01353800_3_24();   // 0x00572810
extern void U_01353800_3_28();   // 0x00572840
extern void U_01353800_3_2c();   // 0x00693090
extern void U_01353800_3_30();   // 0x00694f00
extern void U_01353800_4_24();   // 0x00ac8750
extern void U_01353800_4_28();   // 0x00ac8780
extern void U_01353800_4_2c();   // 0x00693090
extern void U_01353800_4_30();   // 0x00694fa0
extern void U_01353800_4_34();   // 0x00b1fbf0
extern void U_01353800_4_38();   // 0x0057ce00
extern void U_01353800_6_24();   // 0x00572810
extern void U_01353800_6_28();   // 0x00572840
extern void U_01353800_6_2c();   // 0x00693090
extern void U_01353800_6_30();   // 0x00694f00
extern void U_01353800_7_24();   // 0x00572810
extern void U_01353800_7_28();   // 0x00572840
extern void U_01353800_7_2c();   // 0x00693090
extern void U_01353800_7_30();   // 0x00694f00
extern void U_01353800_8_24();   // 0x00ac8750
extern void U_01353800_8_28();   // 0x00ac8780
extern void U_01353800_8_2c();   // 0x00693090
extern void U_01353800_8_30();   // 0x00694fa0
extern void U_01353800_8_34();   // 0x00b1fbf0
extern void U_01353800_8_38();   // 0x0057ce00

// @ 0x01351ae0
void FUN_01351ae0(void)
{
    PropDesc d;
    d.mName = (const char*)0x1473124;
    d.mHash = 0x5626ed3;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351ae0_0_24;
    d.mFn28 = (void*)U_01351ae0_0_28;
    d.mFn2C = (void*)0x693070;
    d.mFn30 = (void*)0x694f80;
    d.mFn34 = (void*)U_01351ae0_0_34;
    d.mFn38 = (void*)0x595a50;
    d.mType = 0xa2;
    *(PropDesc*)0x1579600 = d;

    d.mName = (const char*)0x1473110;
    d.mHash = 0x6282444;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351ae0_1_24;
    d.mFn28 = (void*)U_01351ae0_1_28;
    d.mFn2C = (void*)U_01351ae0_1_2c;
    d.mFn30 = (void*)U_01351ae0_1_30;
    d.mFn34 = (void*)SAE0_F34A;
    d.mFn38 = (void*)SAE0_F38A;
    d.mType = 0xa1;
    *(PropDesc*)0x157963c = d;

    d.mName = (const char*)0x1473104;
    d.mHash = 0x6282445;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351ae0_2_24;
    d.mFn28 = (void*)U_01351ae0_2_28;
    d.mFn2C = (void*)U_01351ae0_2_2c;
    d.mFn30 = (void*)U_01351ae0_2_30;
    d.mFn34 = (void*)SAE0_F34A;
    d.mFn38 = (void*)SAE0_F38A;
    d.mType = 0xa0;
    *(PropDesc*)0x1579678 = d;

    d.mName = (const char*)0x14730f0;
    d.mHash = 0x5d2741e;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351ae0_3_24;
    d.mFn28 = (void*)U_01351ae0_3_28;
    d.mFn2C = (void*)SAE0_F2CB;
    d.mFn30 = (void*)SAE0_F30B;
    d.mFn34 = (void*)U_01351ae0_3_34;
    d.mFn38 = (void*)U_01351ae0_3_38;
    d.mType = 0x8;
    *(PropDesc*)0x15796b4 = d;

    d.mName = (const char*)0x14730dc;
    d.mHash = 0x5d27422;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351ae0_4_24;
    d.mFn28 = (void*)U_01351ae0_4_28;
    d.mFn2C = (void*)SAE0_F2CB;
    d.mFn30 = (void*)SAE0_F30B;
    d.mFn34 = (void*)U_01351ae0_4_34;
    d.mFn38 = (void*)U_01351ae0_4_38;
    d.mType = 0x20;
    *(PropDesc*)0x15796f0 = d;

    d.mName = (const char*)0x14730c8;
    d.mHash = 0x5d27426;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351ae0_5_24;
    d.mFn28 = (void*)U_01351ae0_5_28;
    d.mFn2C = (void*)SAE0_F2CB;
    d.mFn30 = (void*)SAE0_F30B;
    d.mFn34 = (void*)U_01351ae0_5_34;
    d.mFn38 = (void*)U_01351ae0_5_38;
    d.mType = 0x38;
    *(PropDesc*)0x157972c = d;

    d.mName = (const char*)0x14730b8;
    d.mHash = 0x5d2742a;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351ae0_6_24;
    d.mFn28 = (void*)U_01351ae0_6_28;
    d.mFn2C = (void*)SAE0_F2CB;
    d.mFn30 = (void*)SAE0_F30B;
    d.mFn34 = (void*)U_01351ae0_6_34;
    d.mFn38 = (void*)U_01351ae0_6_38;
    d.mType = 0x50;
    *(PropDesc*)0x1579768 = d;

    d.mName = (const char*)0x147309c;
    d.mHash = 0x5f0de1b;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xc7b510;
    d.mFn28 = (void*)0xc76300;
    d.mFn2C = (void*)SAE0_F2CB;
    d.mFn30 = (void*)SAE0_F30B;
    d.mFn34 = (void*)U_01351ae0_7_34;
    d.mFn38 = (void*)0xc793e0;
    d.mType = 0x68;
    *(PropDesc*)0x15797a4 = d;

    d.mName = (const char*)0x1473080;
    d.mHash = 0x689821d;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xae3470;
    d.mFn28 = (void*)0xae3490;
    d.mFn2C = (void*)SAE0_F2CB;
    d.mFn30 = (void*)SAE0_F30B;
    d.mFn34 = (void*)0xae3310;
    d.mFn38 = (void*)0xac8050;
    d.mType = 0x80;
    *(PropDesc*)0x15797e0 = d;
}

// @ 0x01351e60
void FUN_01351e60(void)
{
    PropDesc d;
    d.mName = (const char*)0x14731a0;
    d.mHash = 0x5626da6;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351e60_0_24;
    d.mFn28 = (void*)U_01351e60_0_28;
    d.mFn2C = (void*)0x693090;
    d.mFn30 = (void*)0x694f00;
    d.mFn34 = (void*)U_01351e60_0_34;
    d.mFn38 = (void*)0x675ca0;
    d.mType = 0x8;
    *(PropDesc*)0x1579858 = d;

    d.mName = (const char*)0x147318c;
    d.mHash = 0x57a0b60;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xae3470;
    d.mFn28 = (void*)0xae3490;
    d.mFn2C = (void*)0xc2e4e0;
    d.mFn30 = (void*)0x692fb0;
    d.mFn34 = (void*)0xae3310;
    d.mFn38 = (void*)0xac8050;
    d.mType = 0x10;
    *(PropDesc*)0x1579894 = d;

    d.mName = (const char*)0x1473174;
    d.mHash = 0x5626dae;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351e60_2_24;
    d.mFn28 = (void*)U_01351e60_2_28;
    d.mFn2C = (void*)U_01351e60_2_2c;
    d.mFn30 = (void*)U_01351e60_2_30;
    d.mFn34 = (void*)SE60_F34;
    d.mFn38 = (void*)SE60_F38;
    d.mType = 0x30;
    *(PropDesc*)0x15798d0 = d;

    d.mName = (const char*)0x147315c;
    d.mHash = 0x5626ec6;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351e60_3_24;
    d.mFn28 = (void*)U_01351e60_3_28;
    d.mFn2C = (void*)U_01351e60_3_2c;
    d.mFn30 = (void*)U_01351e60_3_30;
    d.mFn34 = (void*)SE60_F34;
    d.mFn38 = (void*)SE60_F38;
    d.mType = 0x34;
    *(PropDesc*)0x157990c = d;

    d.mName = (const char*)0x1473144;
    d.mHash = 0x5626eca;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351e60_4_24;
    d.mFn28 = (void*)U_01351e60_4_28;
    d.mFn2C = (void*)U_01351e60_4_2c;
    d.mFn30 = (void*)U_01351e60_4_30;
    d.mFn34 = (void*)SE60_F34;
    d.mFn38 = (void*)SE60_F38;
    d.mType = 0x38;
    *(PropDesc*)0x1579948 = d;

    d.mName = (const char*)0x1473130;
    d.mHash = 0x5626ece;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351e60_5_24;
    d.mFn28 = (void*)U_01351e60_5_28;
    d.mFn2C = (void*)U_01351e60_5_2c;
    d.mFn30 = (void*)U_01351e60_5_30;
    d.mFn34 = (void*)SE60_F34;
    d.mFn38 = (void*)SE60_F38;
    d.mType = 0x3c;
    *(PropDesc*)0x1579984 = d;
}

// @ 0x01352460
void FUN_01352460(void)
{
    PropDesc d;
    d.mName = (const char*)0x147342c;
    d.mHash = 0x603498b;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xc7e9f0;
    d.mFn28 = (void*)0xcd44e0;
    d.mFn2C = (void*)0xc2e4e0;
    d.mFn30 = (void*)0x692fb0;
    d.mFn34 = (void*)U_01352460_0_34;
    d.mFn38 = (void*)U_01352460_0_38;
    d.mType = 0x0;
    *(PropDesc*)0x1579c58 = d;
}

// @ 0x013526b0
void FUN_013526b0(void)
{
    PropDesc d;
    d.mName = (const char*)0x147351c;
    d.mHash = 0x38cfa88;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xc86560;
    d.mFn28 = (void*)0xc43790;
    d.mFn2C = (void*)0xc2e4e0;
    d.mFn30 = (void*)0x692fb0;
    d.mFn34 = (void*)0xb6f860;
    d.mFn38 = (void*)0xc6c390;
    d.mType = 0x10;
    *(PropDesc*)0x1579d78 = d;

    d.mName = (const char*)0x1473508;
    d.mHash = 0x38cfad9;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xc85460;
    d.mFn28 = (void*)0xaca730;
    d.mFn2C = (void*)0xc2e4e0;
    d.mFn30 = (void*)0x692fb0;
    d.mFn34 = (void*)0xb6f860;
    d.mFn38 = (void*)0xc6c390;
    d.mType = 0x24;
    *(PropDesc*)0x1579db4 = d;

    d.mName = (const char*)0x1473500;
    d.mHash = 0x38cfae4;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xc843f0;
    d.mFn28 = (void*)0xbca960;
    d.mFn2C = (void*)0xc2e4e0;
    d.mFn30 = (void*)0x692fb0;
    d.mFn34 = (void*)0xb6f550;
    d.mFn38 = (void*)0xac8050;
    d.mType = 0x38;
    *(PropDesc*)0x1579df0 = d;

    d.mName = (const char*)0x14734f8;
    d.mHash = 0x38cfafe;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xc843f0;
    d.mFn28 = (void*)0xbca960;
    d.mFn2C = (void*)0xc2e4e0;
    d.mFn30 = (void*)0x692fb0;
    d.mFn34 = (void*)0xb6f550;
    d.mFn38 = (void*)0xac8050;
    d.mType = 0x3c;
    *(PropDesc*)0x1579e2c = d;
}

// @ 0x01353800
void FUN_01353800(void)
{
    PropDesc d;
    d.mName = (const char*)0x1473734;
    d.mHash = 0x223eb9d;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xae3430;
    d.mFn28 = (void*)0xae3450;
    d.mFn2C = (void*)0x693150;
    d.mFn30 = (void*)0x695080;
    d.mFn34 = (void*)U_01353800_0_34;
    d.mFn38 = (void*)0xae5720;
    d.mType = 0x5c;
    *(PropDesc*)0x1579f50 = d;

    d.mName = (const char*)0x1473728;
    d.mHash = 0x223eb9e;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01353800_1_24;
    d.mFn28 = (void*)U_01353800_1_28;
    d.mFn2C = (void*)U_01353800_1_2c;
    d.mFn30 = (void*)U_01353800_1_30;
    d.mFn34 = (void*)S3800_F34A;
    d.mFn38 = (void*)S3800_F38A;
    d.mType = 0x10;
    *(PropDesc*)0x1579f8c = d;

    d.mName = (const char*)0x147371c;
    d.mHash = 0x362aeb9;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01353800_2_24;
    d.mFn28 = (void*)U_01353800_2_28;
    d.mFn2C = (void*)U_01353800_2_2c;
    d.mFn30 = (void*)U_01353800_2_30;
    d.mFn34 = (void*)S3800_F34A;
    d.mFn38 = (void*)S3800_F38A;
    d.mType = 0x14;
    *(PropDesc*)0x1579fc8 = d;

    d.mName = (const char*)0x1473710;
    d.mHash = 0x362aeba;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01353800_3_24;
    d.mFn28 = (void*)U_01353800_3_28;
    d.mFn2C = (void*)U_01353800_3_2c;
    d.mFn30 = (void*)U_01353800_3_30;
    d.mFn34 = (void*)S3800_F34B;
    d.mFn38 = (void*)S3800_F38B;
    d.mType = 0x18;
    *(PropDesc*)0x157a004 = d;

    d.mName = (const char*)0x1473704;
    d.mHash = 0x362aebb;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01353800_4_24;
    d.mFn28 = (void*)U_01353800_4_28;
    d.mFn2C = (void*)U_01353800_4_2c;
    d.mFn30 = (void*)U_01353800_4_30;
    d.mFn34 = (void*)U_01353800_4_34;
    d.mFn38 = (void*)U_01353800_4_38;
    d.mType = 0x1c;
    *(PropDesc*)0x157a040 = d;

    d.mName = (const char*)0x14736f8;
    d.mHash = 0x223eba1;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xc87630;
    d.mFn28 = (void*)0xbd1780;
    d.mFn2C = (void*)0xc2e4e0;
    d.mFn30 = (void*)0x692fb0;
    d.mFn34 = (void*)0xc87090;
    d.mFn38 = (void*)0xac8050;
    d.mType = 0x2c;
    *(PropDesc*)0x157a07c = d;

    d.mName = (const char*)0x14736e8;
    d.mHash = 0x5d28f83;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01353800_6_24;
    d.mFn28 = (void*)U_01353800_6_28;
    d.mFn2C = (void*)U_01353800_6_2c;
    d.mFn30 = (void*)U_01353800_6_30;
    d.mFn34 = (void*)S3800_F34B;
    d.mFn38 = (void*)S3800_F38B;
    d.mType = 0x20;
    *(PropDesc*)0x157a0b8 = d;

    d.mName = (const char*)0x14736d8;
    d.mHash = 0x61d7ac0;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01353800_7_24;
    d.mFn28 = (void*)U_01353800_7_28;
    d.mFn2C = (void*)U_01353800_7_2c;
    d.mFn30 = (void*)U_01353800_7_30;
    d.mFn34 = (void*)S3800_F34B;
    d.mFn38 = (void*)S3800_F38B;
    d.mType = 0x24;
    *(PropDesc*)0x157a0f4 = d;

    d.mName = (const char*)0x14736cc;
    d.mHash = 0x61d7ac9;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01353800_8_24;
    d.mFn28 = (void*)U_01353800_8_28;
    d.mFn2C = (void*)U_01353800_8_2c;
    d.mFn30 = (void*)U_01353800_8_30;
    d.mFn34 = (void*)U_01353800_8_34;
    d.mFn38 = (void*)U_01353800_8_38;
    d.mType = 0x28;
    *(PropDesc*)0x157a130 = d;
}

