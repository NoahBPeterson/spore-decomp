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
// {name, hash, size, 0, 0, 7 x function pointer} record copied to a global
// table; only the first records were reconstructed.
// ---------------------------------------------------------------------------

// @ 0x0138d560  PARTIAL: 15-dword descriptor table (6 records)
void init_15afd38() { }

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

// @ 0x01396110  PARTIAL: 15-dword descriptor table
void init_15b4568() { }

// @ 0x01396440  PARTIAL: 15-dword descriptor table
void init_15b47b8() { }
