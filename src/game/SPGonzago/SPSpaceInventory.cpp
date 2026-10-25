// src/game/SPGonzago/SPSpaceInventory.cpp -- migrated from slice(s) s01351ae0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpaceInventory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void S3800_F34A();   // 0x00b1fbf0
extern void S3800_F34B();   // 0x00b1fbf0
extern void S3800_F38A();   // 0x0057cde0
extern void S3800_F38B();   // 0x00675ca0
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

// ---- items of slice s01351ae0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
// ---- items of slice s01351ae0 end

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
