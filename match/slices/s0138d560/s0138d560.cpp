// Slice s0138d560 -- shared-allocator bootstrap and zero-fill initializers.
typedef unsigned int uint32_t;

extern "C" int atexit(void (__cdecl*)());
extern char InitSharedAllocator();
extern void FUN_013c9950(void);
extern void FUN_013c9dd0(void);
extern void FUN_013c9e00(void);

// @ 0x0138e640
void init_16c8b40()
{
    if (*(int*)0x16c8b40 == 0) {
        char ok = InitSharedAllocator();
        *(char*)0x16c8b48 = 1;
        if (!ok)
            *(char*)0x16c8b48 = 0;
    } else {
        *(char*)0x16c8b48 = 0;
    }
    atexit(&FUN_013c9950);
}

// @ 0x01390c90
void init_16c9b8c()
{
    int c = 0x803000;
    *(int*)0x16c9b8c = c;
    *(int*)0x16c9b90 = 0;
}

// @ 0x01390cb0
void init_16c9b94()
{
    int c = 0xe0;
    *(int*)0x16c9b94 = c;
    *(int*)0x16c9b98 = 0;
}

// @ 0x01391740
void init_16ca3d4()
{
    *(int*)0x16ca3d4 = -1;
    *(int*)0x16ca3d8 = -1;
    *(int*)0x16ca3dc = -1;
    *(int*)0x16ca3e0 = -1;
    *(int*)0x16ca3e4 = -1;
    *(int*)0x16ca3e8 = -1;
    *(int*)0x16ca3ec = -1;
    *(int*)0x16ca3f0 = -1;
    *(int*)0x16ca3f4 = -1;
    *(int*)0x16ca3f8 = -1;
    *(int*)0x16ca3fc = -1;
    *(int*)0x16ca400 = -1;
}

// @ 0x01391bc0
void init_16d6d30()
{
    *(int*)0x16d6d30 = 0;
    *(int*)0x16d6d34 = 0;
    *(int*)0x16d6d38 = 0;
    *(int*)0x16d6d3c = 0;
    *(int*)0x16d6d40 = 0;
    *(int*)0x16d6d44 = 0;
    *(int*)0x16d6d48 = 0;
    *(int*)0x16d6d4c = 0;
    *(int*)0x16d6d50 = 0;
    *(int*)0x16d6d54 = 0;
    *(int*)0x16d6d58 = 0;
    *(int*)0x16d6d5c = 0;
    *(int*)0x16d6d60 = 0;
    *(int*)0x16d6d64 = 0;
    *(int*)0x16d6d68 = 0;
    *(int*)0x16d6d6c = 0;
    atexit(&FUN_013c9dd0);
}

// @ 0x01391c20
void init_16d6d70()
{
    *(int*)0x16d6d70 = 0;
    *(int*)0x16d6d74 = 0;
    *(int*)0x16d6d78 = 0;
    *(int*)0x16d6d7c = 0;
    *(int*)0x16d6d80 = 0;
    *(int*)0x16d6d84 = 0;
    *(int*)0x16d6d88 = 0;
    *(int*)0x16d6d8c = 0;
    *(int*)0x16d6d90 = 0;
    *(int*)0x16d6d94 = 0;
    *(int*)0x16d6d98 = 0;
    *(int*)0x16d6d9c = 0;
    *(int*)0x16d6da0 = 0;
    *(int*)0x16d6da4 = 0;
    *(int*)0x16d6da8 = 0;
    *(int*)0x16d6dac = 0;
    atexit(&FUN_013c9e00);
}

// ---------------------------------------------------------------------------
// Large property-descriptor table initializers.  Each entry is a 15-dword
// record: name string VA, hash, byte size, three dwords that the original
// leaves untouched (+0x0c..+0x14), two zero dwords (+0x18/+0x1c) and seven
// function pointers (+0x20..+0x38).  The original builds one record in a
// 0x3c-byte stack temporary and rep-movsd's it into the global table.
// ---------------------------------------------------------------------------
struct PropertyDesc {
    unsigned int name;   // +0x00  const char* (VA)
    unsigned int hash;   // +0x04
    unsigned int size;   // +0x08  byte size of the value
    unsigned int unk0c;  // +0x0c  uninitialised in the original
    unsigned int unk10;  // +0x10  uninitialised in the original
    unsigned int unk14;  // +0x14  uninitialised in the original
    unsigned int fn0;    // +0x18
    unsigned int fn1;    // +0x1c
    unsigned int fn2;    // +0x20
    unsigned int fn3;    // +0x24
    unsigned int fn4;    // +0x28
    unsigned int fn5;    // +0x2c
    unsigned int fn6;    // +0x30
    unsigned int fn7;    // +0x34
    unsigned int fn8;    // +0x38
};

// @ 0x0138d560  0x15afd38: 9 records, 0x3c stride
void init_15afd38()
{
    static const PropertyDesc desc[9] = {
        { 0x148cd30, 0x7905d42, 0x130,  0,0,0, 0,0,
          0x692ca0, 0xf26be0, 0xf26c20, 0xc2e4e0, 0x692fb0, 0xf25b80, 0xf2a510 },
        { 0x148cdcc, 0x7734a68, 0x175,  0,0,0, 0,0,
          0x692ca0, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00 },
        { 0x148cda0, 0x7905d3c, 0x238,  0,0,0, 0,0,
          0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0 },
        { 0x148cd88, 0x7905d3e, 0xb8,   0,0,0, 0,0,
          0x692ca0, 0xf293f0, 0xf268b0, 0xc2e4e0, 0x692fb0, 0xf25b60, 0xf28880 },
        { 0x148cd7c, 0x7905d3f, 0xf4,   0,0,0, 0,0,
          0x692ca0, 0xf293f0, 0xf268b0, 0xc2e4e0, 0x692fb0, 0xf25b60, 0xf28880 },
        { 0x148cd70, 0x7905d40, 0x7c,   0,0,0, 0,0,
          0x692ca0, 0xf293f0, 0xf268b0, 0xc2e4e0, 0x692fb0, 0xf25b60, 0xf28880 },
        { 0x1412cf4, 0x7905d41, 0x78,   0,0,0, 0,0,
          0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0 },
        { 0x148ca9c, 0x7be36ef, 0x23c,  0,0,0, 0,0,
          0x692ca0, 0xf2f4f0, 0xf27010, 0xc2e4e0, 0x692fb0, 0xf270b0, 0xf29e30 },
        { 0x148cd98, 0x7be710b, 0x2bf4, 0,0,0, 0,0,
          0x692ca0, 0xf2f6c0, 0xf27ee0, 0xc2e4e0, 0x692fb0, 0xf26fd0, 0xf29ce0 },
    };
    PropertyDesc* dst = (PropertyDesc*)0x15afd38;
    for (int i = 0; i < 9; ++i)
        dst[i] = desc[i];
}

// The table at 0x16d6fa8 is a 72-float basis-matrix block built from
// +1/sqrt(2), -1/sqrt(2), +0.0 and -0.0 (0x3f3504f3, 0xbf3504f3, 0, 0x80000000).
// @ 0x013921c0
void init_16d6fa8()
{
    *(float*)0x016d6fa8 = 0.0f;
    *(float*)0x016d6fac = -0.70710678f;
    *(float*)0x016d6fb0 = 0.70710678f;
    *(float*)0x016d6fb4 = 0.70710678f;
    *(float*)0x016d6fb8 = 0.0f;
    *(float*)0x016d6fbc = 0.70710678f;
    *(float*)0x016d6fc0 = 0.0f;
    *(float*)0x016d6fc4 = 0.70710678f;
    *(float*)0x016d6fc8 = 0.70710678f;
    *(float*)0x016d6fcc = -0.70710678f;
    *(float*)0x016d6fd0 = 0.0f;
    *(float*)0x016d6fd4 = 0.70710678f;
    *(float*)0x016d6fd8 = 0.0f;
    *(float*)0x016d6fdc = -0.70710678f;
    *(float*)0x016d6fe0 = -0.70710678f;
    *(float*)0x016d6fe4 = 0.70710678f;
    *(float*)0x016d6fe8 = 0.0f;
    *(float*)0x016d6fec = -0.70710678f;
    *(float*)0x016d6ff0 = 0.0f;
    *(float*)0x016d6ff4 = 0.70710678f;
    *(float*)0x016d6ff8 = -0.70710678f;
    *(float*)0x016d6ffc = -0.70710678f;
    *(float*)0x016d7000 = 0.0f;
    *(float*)0x016d7004 = -0.70710678f;
    *(float*)0x016d7008 = 0.70710678f;
    *(float*)0x016d700c = -0.70710678f;
    *(float*)0x016d7010 = 0.0f;
    *(float*)0x016d7014 = 0.70710678f;
    *(float*)0x016d7018 = 0.0f;
    *(float*)0x016d701c = 0.70710678f;
    *(float*)0x016d7020 = 0.70710678f;
    *(float*)0x016d7024 = 0.70710678f;
    *(float*)0x016d7028 = 0.0f;
    *(float*)0x016d702c = 0.70710678f;
    *(float*)0x016d7030 = 0.0f;
    *(float*)0x016d7034 = -0.70710678f;
    *(float*)0x016d7038 = -0.70710678f;
    *(float*)0x016d703c = -0.70710678f;
    *(float*)0x016d7040 = 0.0f;
    *(float*)0x016d7044 = -0.70710678f;
    *(float*)0x016d7048 = 0.0f;
    *(float*)0x016d704c = 0.70710678f;
    *(float*)0x016d7050 = -0.70710678f;
    *(float*)0x016d7054 = 0.70710678f;
    *(float*)0x016d7058 = 0.0f;
    *(float*)0x016d705c = -0.70710678f;
    *(float*)0x016d7060 = 0.0f;
    *(float*)0x016d7064 = -0.70710678f;
    *(float*)0x016d7068 = -0.70710678f;
    *(float*)0x016d706c = 0.70710678f;
    *(float*)0x016d7070 = 0.0f;
    *(float*)0x016d7074 = -0.0f;
    *(float*)0x016d7078 = 0.70710678f;
    *(float*)0x016d707c = 0.70710678f;
    *(float*)0x016d7080 = 0.70710678f;
    *(float*)0x016d7084 = 0.70710678f;
    *(float*)0x016d7088 = 0.0f;
    *(float*)0x016d708c = 0.0f;
    *(float*)0x016d7090 = 0.70710678f;
    *(float*)0x016d7094 = -0.70710678f;
    *(float*)0x016d7098 = -0.70710678f;
    *(float*)0x016d709c = -0.70710678f;
    *(float*)0x016d70a0 = 0.0f;
    *(float*)0x016d70a4 = 0.0f;
    *(float*)0x016d70a8 = -0.70710678f;
    *(float*)0x016d70ac = 0.70710678f;
    *(float*)0x016d70b0 = 0.70710678f;
    *(float*)0x016d70b4 = -0.70710678f;
    *(float*)0x016d70b8 = 0.0f;
    *(float*)0x016d70bc = 0.0f;
    *(float*)0x016d70c0 = -0.70710678f;
    *(float*)0x016d70c4 = -0.70710678f;
}

// @ 0x01396110  0x15b4568: 5 records, 0x3c stride
void init_15b4568()
{
    static const PropertyDesc desc[5] = {
        { 0x1494424, 0x374176b, 0x00,  0,0,0, 0,0,
          0x692ca0, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00 },
        { 0x1494414, 0x3741796, 0x04,  0,0,0, 0,0,
          0x692ca0, 0xb6e3a0, 0xac88c0, 0x6930f0, 0x695010, 0xb1fbf0, 0xacbba0 },
        { 0x1494404, 0x3741811, 0x10,  0,0,0, 0,0,
          0x692ca0, 0x572810, 0xac88f0, 0x6930b0, 0x694fc0, 0xb1fbf0, 0xacbb80 },
        { 0x14943f8, 0x374181f, 0x14,  0,0,0, 0,0,
          0x692ca0, 0xb6e3a0, 0xac88c0, 0x6930f0, 0x695010, 0xb1fbf0, 0xacbba0 },
        { 0x14943f0, 0x374182d, 0x20,  0,0,0, 0,0,
          0x692ca0, 0x572810, 0xac88f0, 0x6930b0, 0x694fc0, 0xb1fbf0, 0xacbb80 },
    };
    PropertyDesc* dst = (PropertyDesc*)0x15b4568;
    for (int i = 0; i < 5; ++i)
        dst[i] = desc[i];
}

// @ 0x01396440  0x15b47b8: 6 records, 0x3c stride
void init_15b47b8()
{
    static const PropertyDesc desc[6] = {
        { 0x1494838, 0x42a2fbd, 0x38,  0,0,0, 0,0,
          0x692ca0, 0xaff840, 0xaff870, 0x692fd0, 0x694ec0, 0xb1fbf0, 0x595a70 },
        { 0x149481c, 0x5a5bc48, 0x40,  0,0,0, 0,0,
          0x692ca0, 0xaff840, 0xaff870, 0x692fd0, 0x694ec0, 0xb1fbf0, 0x595a70 },
        { 0x1494808, 0x54ffe6e, 0x58,  0,0,0, 0,0,
          0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0 },
        { 0x14947f8, 0x54ffe6d, 0x5c,  0,0,0, 0,0,
          0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0 },
        { 0x14947ec, 0x57e1d98, 0x48,  0,0,0, 0,0,
          0x692ca0, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00 },
        { 0x14947d8, 0x66b6169, 0x49,  0,0,0, 0,0,
          0x692ca0, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00 },
    };
    PropertyDesc* dst = (PropertyDesc*)0x15b47b8;
    for (int i = 0; i < 6; ++i)
        dst[i] = desc[i];
}
