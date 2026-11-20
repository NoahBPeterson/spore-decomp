// Slice s01300280, /Od part -- type-registry-style static initializers.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_141a7fc[];
extern "C" char g_1440af0[];
extern "C" char g_1440afc[];
extern "C" char g_1440b6c[];
extern "C" char g_1440e14[];
extern "C" char g_14452e0[];
extern "C" char g_154ed8c[];
extern "C" char g_154ed90[];
extern "C" char g_154ed94[];
extern "C" char g_154ed98[];
extern "C" char g_154ed9c[];
extern "C" char g_154eda0[];
extern "C" char g_154eda4[];
extern "C" char g_154eda8[];
extern "C" char g_154edac[];
extern "C" char g_154edb0[];
extern "C" char g_154edb4[];
extern "C" char g_154edb8[];
extern "C" char g_154edbc[];
extern "C" char g_154edc0[];
extern "C" char g_154edc4[];
extern "C" char g_154edc8[];
extern "C" char g_154edcc[];
extern "C" char g_154edd0[];
extern "C" char g_154edd4[];
extern "C" char g_154f00c[];
extern "C" char g_154f010[];
extern "C" char g_154f014[];
extern "C" char g_154f018[];
extern "C" char g_154f01c[];
extern "C" char g_154f020[];
extern "C" char g_154f024[];
extern "C" char g_154f028[];
extern "C" char g_154f02c[];
extern "C" char g_154f030[];
extern "C" char g_154f034[];
extern "C" char g_154f038[];
extern "C" char g_154f03c[];
extern "C" char g_154f040[];
extern "C" char g_154f044[];
extern "C" char g_154f048[];
extern "C" char g_154f04c[];
extern "C" char g_154f050[];
extern "C" char g_154f054[];
extern "C" char g_154f058[];
extern "C" char g_154f05c[];
extern "C" char g_154f060[];
extern "C" char g_154f064[];
extern "C" char g_154f068[];
extern "C" char g_154f06c[];
extern "C" char g_154f070[];
extern "C" char g_154f074[];
extern "C" char g_154f078[];
extern "C" char g_154f07c[];
extern "C" char g_154f080[];
extern "C" char g_154f084[];
extern "C" char g_154f088[];
extern "C" char g_154f08c[];
extern "C" char g_154f090[];
extern "C" char g_154f094[];
extern "C" char g_154f098[];
extern "C" char g_154f09c[];
extern "C" char g_154f0a0[];
extern "C" char g_154f0a4[];
extern "C" char g_154f0a8[];
extern "C" char g_154f0ac[];
extern "C" char g_154f0b0[];
extern "C" char g_154f0b4[];
extern "C" char g_154f2d4[];
extern "C" char g_154f2d8[];
extern "C" char g_154f2dc[];
extern "C" char g_154f2e0[];
extern "C" char g_154f2e4[];
extern "C" char g_154f2e8[];
extern "C" char g_154f2ec[];
extern "C" char g_154f4dc[];
extern "C" char g_154f4e0[];
extern "C" char g_154f4e4[];
extern "C" char g_154f4e8[];
extern "C" char g_154f4ec[];
extern "C" char g_154f4f0[];
extern "C" char g_154f4f4[];
extern "C" char g_154f4f8[];
extern "C" char g_154f4fc[];
extern "C" char g_154f500[];
extern "C" char g_154f504[];
extern "C" char g_154f508[];
extern "C" char g_154f50c[];
extern "C" char g_154f714[];
extern "C" char g_154f718[];
extern "C" char g_154f71c[];
extern "C" char g_154f720[];
extern "C" char g_154f724[];
extern "C" char g_154f728[];
extern "C" char g_154f72c[];
extern "C" char g_154f94c[];
extern "C" char g_154f950[];
extern "C" char g_154f954[];
extern "C" char g_154f958[];
extern "C" char g_154f95c[];
extern "C" char g_154f960[];
extern "C" char g_154f964[];
extern "C" char g_154fbe4[];
extern "C" char g_154fbe8[];
extern "C" char g_154fbec[];
extern "C" char g_154fbf0[];
extern "C" char g_154fbf4[];
extern "C" char g_154fbf8[];
extern "C" char g_154fbfc[];
extern "C" char g_154fc00[];
extern "C" char g_154fc04[];
extern "C" char g_154fc08[];
extern "C" char g_154fc0c[];
extern "C" char g_154fc10[];
extern "C" char g_154fc14[];
extern "C" char g_154fc18[];
extern "C" char g_154fc1c[];
extern "C" char g_154fc20[];
extern "C" char g_154fc24[];
extern "C" char g_154fc28[];
extern "C" char g_154fc2c[];
extern "C" char g_154fc30[];
extern "C" char g_154fc34[];
extern "C" char g_154fc38[];
extern "C" char g_154fc3c[];
extern "C" char g_154fc40[];
extern "C" char g_154fc44[];
extern "C" char g_154fc48[];
extern "C" char g_154fc4c[];
extern "C" char g_154fc50[];
extern "C" char g_154fc54[];
extern "C" char g_154fc58[];
extern "C" char g_154fc5c[];
extern "C" char g_154fc60[];
extern "C" char g_154fc64[];
extern "C" char g_154fc68[];
extern "C" char g_154fc6c[];
extern "C" char g_154fc70[];
extern "C" char g_154fc74[];

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

extern "C" int atexit(void (__cdecl*)());
extern int FUN_00957a60(void* a, void* b);
extern int FUN_00957880(void* a, void* b);
extern void FUN_009577b0(void);
extern void FUN_009577f0(void);
extern void FUN_005ed340(void);
extern void FUN_00957790(void);

// @ 0x013004a0
void init_154ed8c()
{
    *(int*)g_154ed8c = 1;
    *(int*)g_154ed90 = 0;
    *(int*)g_154ed94 = FUN_00957a60(&FUN_009577b0, &FUN_009577f0);
    *(int*)g_154ed98 = 0x1be0002;
    *(short*)g_154ed9c = 0x10;
    *(int*)g_154eda0 = 0;
    *(int*)g_154eda4 = 1;
    *(int*)g_154eda8 = 0;
    *(int*)g_154edac = FUN_00957880(&FUN_005ed340, &FUN_00957790);
    *(int*)g_154edb0 = 0x1be0003;
    *(short*)g_154edb4 = 0xf;
    *(int*)g_154edb8 = 0;
    *(int*)g_154edbc = 1;
    *(int*)g_154edc0 = 0;
    *(int*)g_154edc4 = 0;
    *(int*)g_154edc8 = 0x1be0004;
    *(short*)g_154edcc = 9;
    *(int*)g_154edd0 = 0x24;
    *(int*)g_154edd4 = 1;
}

// @ 0x013005a0
void init_154f00c()
{
    *(int*)g_154f00c = 1;
    *(int*)g_154f010 = 0;
    *(int*)g_154f014 = 0;
    *(int*)g_154f018 = 0xeec1b008;
    *(short*)g_154f01c = 0xd;
    *(int*)g_154f020 = 0xc4;
    *(int*)g_154f024 = 1;
    *(int*)g_154f028 = 0;
    *(int*)g_154f02c = 0;
    *(int*)g_154f030 = 0xeec1b009;
    *(short*)g_154f034 = 9;
    *(int*)g_154f038 = 0xa8;
    *(int*)g_154f03c = 1;
    *(int*)g_154f040 = 0;
    *(int*)g_154f044 = 0;
    *(int*)g_154f048 = 0xeec1b00a;
    *(short*)g_154f04c = 0x12;
    *(int*)g_154f050 = 0xb0;
    *(int*)g_154f054 = 1;
    *(int*)g_154f058 = 0;
    *(void**)g_154f05c = (void*)g_1440af0;
    *(int*)g_154f060 = 0xeec1b00b;
    *(unsigned short*)g_154f064 = 0x8013;
    *(int*)g_154f068 = 0x3c;
    *(int*)g_154f06c = 1;
    *(int*)g_154f070 = 0;
    *(void**)g_154f074 = (void*)g_1440afc;
    *(int*)g_154f078 = 0xeec1b00c;
    *(unsigned short*)g_154f07c = 0x8013;
    *(int*)g_154f080 = 0x64;
    *(int*)g_154f084 = 1;
    *(int*)g_154f088 = 0;
    *(void**)g_154f08c = (void*)g_1440b6c;
    *(int*)g_154f090 = 0xeec1b00d;
    *(short*)g_154f094 = 0x13;
    *(int*)g_154f098 = 0x1e4;
    *(int*)g_154f09c = 1;
    *(int*)g_154f0a0 = 0;
    *(int*)g_154f0a4 = 0;
    *(int*)g_154f0a8 = 0xeec1b00e;
    *(short*)g_154f0ac = 9;
    *(int*)g_154f0b0 = 0xc0;
    *(int*)g_154f0b4 = 1;
}

// @ 0x013008b0
void init_154f2d4()
{
    *(int*)g_154f2d4 = 1;
    *(int*)g_154f2d8 = 0;
    *(void**)g_154f2dc = (void*)g_141a7fc;
    *(int*)g_154f2e0 = 0x39a69e6;
    *(short*)g_154f2e4 = 0x14;
    *(int*)g_154f2e8 = 0x290;
    *(int*)g_154f2ec = 1;
}

// @ 0x01300950
void init_154f4dc()
{
    *(int*)g_154f4dc = 0xa;
    *(int*)g_154f4e0 = 0;
    *(int*)g_154f4e4 = 0;
    *(int*)g_154f4e8 = 0x2f42e1a2;
    *(short*)g_154f4ec = 9;
    *(int*)g_154f4f0 = 0x10;
    *(int*)g_154f4f4 = 1;
    *(int*)g_154f4f8 = 0;
    *(int*)g_154f4fc = 0;
    *(int*)g_154f500 = 0x2f42e1a3;
    *(short*)g_154f504 = 9;
    *(int*)g_154f508 = 0x14;
    *(int*)g_154f50c = 1;
}

// @ 0x01300a70
void init_154f714()
{
    *(int*)g_154f714 = 1;
    *(int*)g_154f718 = 0;
    *(void**)g_154f71c = (void*)g_141a7fc;
    *(int*)g_154f720 = 0x39a69e6;
    *(short*)g_154f724 = 0x14;
    *(int*)g_154f728 = 0x28;
    *(int*)g_154f72c = 1;
}

// @ 0x01300b20
void init_154f94c()
{
    *(int*)g_154f94c = 1;
    *(int*)g_154f950 = 0;
    *(int*)g_154f954 = 0;
    *(int*)g_154f958 = 0xeec2c011;
    *(short*)g_154f95c = 0xb;
    *(int*)g_154f960 = 0x340;
    *(int*)g_154f964 = 1;
}

// @ 0x01300c50
void init_154fbe4()
{
    *(int*)g_154fbe4 = 8;
    *(int*)g_154fbe8 = 0;
    *(int*)g_154fbec = 0;
    *(int*)g_154fbf0 = 0xef3c000a;
    *(short*)g_154fbf4 = 9;
    *(int*)g_154fbf8 = 0x30;
    *(int*)g_154fbfc = 1;
    *(int*)g_154fc00 = 0;
    *(int*)g_154fc04 = 0;
    *(int*)g_154fc08 = 0xef3c000b;
    *(short*)g_154fc0c = 0x11;
    *(int*)g_154fc10 = 0x44;
    *(int*)g_154fc14 = 1;
    *(int*)g_154fc18 = 0;
    *(void**)g_154fc1c = (void*)g_1440e14;
    *(int*)g_154fc20 = 0xef3c000c;
    *(short*)g_154fc24 = 0x14;
    *(int*)g_154fc28 = 0x34;
    *(int*)g_154fc2c = 1;
    *(int*)g_154fc30 = 0;
    *(void**)g_154fc34 = (void*)g_14452e0;
    *(int*)g_154fc38 = 0xf3c000d;
    *(short*)g_154fc3c = 0x13;
    *(int*)g_154fc40 = 0x4c;
    *(int*)g_154fc44 = 1;
    *(int*)g_154fc48 = 0;
    *(int*)g_154fc4c = 0;
    *(int*)g_154fc50 = 0xf3c000e;
    *(short*)g_154fc54 = 0xb;
    *(int*)g_154fc58 = 0x50;
    *(int*)g_154fc5c = 1;
    *(int*)g_154fc60 = 0;
    *(void**)g_154fc64 = (void*)g_141a7fc;
    *(int*)g_154fc68 = 0x39a69e6;
    *(short*)g_154fc6c = 0x14;
    *(int*)g_154fc70 = 0x54;
    *(int*)g_154fc74 = 1;
}

// @ 0x01300e00
void init_154fe1c()
{
    *(int*)0x154fe1c = 1;
    *(int*)0x154fe20 = 0;
    *(void**)0x154fe24 = (void*)0x1418fd8;
    *(int*)0x154fe28 = 0xff1173c;
    *(short*)0x154fe2c = 0x13;
    *(int*)0x154fe30 = 0x14 + 0x584;
    *(int*)0x154fe34 = 1;
}

// @ 0x01300e90
void init_154ff0c()
{
    *(int*)0x154ff0c = 1;
    *(int*)0x154ff10 = 0;
    *(void**)0x154ff14 = (void*)0x1418fd8;
    *(int*)0x154ff18 = 0x302a0006;
    *(short*)0x154ff1c = 0x13;
    *(int*)0x154ff20 = 0x2b4;
    *(int*)0x154ff24 = 1;
    *(int*)0x154ff28 = 0;
    *(int*)0x154ff2c = 0;
    *(int*)0x154ff30 = 0x302a0007;
    *(short*)0x154ff34 = 9;
    *(int*)0x154ff38 = 0x2b8;
    *(int*)0x154ff3c = 1;
    *(int*)0x154ff40 = 0;
    *(int*)0x154ff44 = 0;
    *(int*)0x154ff48 = 0x302a0008;
    *(short*)0x154ff4c = 9;
    *(int*)0x154ff50 = 0x2bc;
    *(int*)0x154ff54 = 1;
    *(int*)0x154ff58 = 0;
    *(int*)0x154ff5c = 0;
    *(int*)0x154ff60 = 0x302a0009;
    *(short*)0x154ff64 = 9;
    *(int*)0x154ff68 = 0x2c0;
    *(int*)0x154ff6c = 1;
    *(int*)0x154ff70 = 0;
    *(int*)0x154ff74 = 0;
    *(int*)0x154ff78 = 0x302a000a;
    *(short*)0x154ff7c = 9;
    *(int*)0x154ff80 = 0x2c4;
    *(int*)0x154ff84 = 1;
    *(int*)0x154ff88 = 0;
    *(void**)0x154ff8c = (void*)0x14455f4;
    *(int*)0x154ff90 = 0x302a000b;
    *(short*)0x154ff94 = 9;
    *(int*)0x154ff98 = 0x2fc;
    *(int*)0x154ff9c = 1;
    *(int*)0x154ffa0 = 0;
    *(void**)0x154ffa4 = (void*)0x14455f4;
    *(int*)0x154ffa8 = 0x302a000c;
    *(short*)0x154ffac = 9;
    *(int*)0x154ffb0 = 0x14 + 0x2fc;
    *(int*)0x154ffb4 = 1;
    *(int*)0x154ffb8 = 0;
    *(void**)0x154ffbc = (void*)0x1441580;
    *(int*)0x154ffc0 = 0x302a000d;
    *(short*)0x154ffc4 = 0x13;
    *(int*)0x154ffc8 = 0x2f8;
    *(int*)0x154ffcc = 1;
    *(int*)0x154ffd0 = 0;
    *(void**)0x154ffd4 = (void*)0x1441580;
    *(int*)0x154ffd8 = 0x302a000e;
    *(short*)0x154ffdc = 0x13;
    *(int*)0x154ffe0 = 0x14 + 0x2f8;
    *(int*)0x154ffe4 = 1;
}

// @ 0x01301110
void init_15501e4()
{
    *(int*)0x15501e4 = 1;
    *(int*)0x15501e8 = 0;
    *(void**)0x15501ec = (void*)0x1441580;
    *(int*)0x15501f0 = 0xff1173c;
    *(short*)0x15501f4 = 0x13;
    *(int*)0x15501f8 = 0x14 + 0xa890;
    *(int*)0x15501fc = 1;
}
