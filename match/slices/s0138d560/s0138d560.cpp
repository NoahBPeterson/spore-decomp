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

// @ 0x013921c0  PARTIAL: large float basis-matrix constant table
void init_16d6fa8() { }

// @ 0x01396110  PARTIAL: 15-dword descriptor table
void init_15b4568() { }

// @ 0x01396440  PARTIAL: 15-dword descriptor table
void init_15b47b8() { }
