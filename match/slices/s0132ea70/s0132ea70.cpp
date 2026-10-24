// s0132ea70.cpp - reconstructed slice
// Compiler: MSVC 2008 SP1 (x86)
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
// ---------------------------------------------------------------------------------------------
// Types
// ---------------------------------------------------------------------------------------------
typedef unsigned char      u8;
typedef unsigned int       u32;
typedef int                i32;

// ---------------------------------------------------------------------------------------------
// Globals
// ---------------------------------------------------------------------------------------------
struct cRbtreeSentinel;

// The global serializer-list block populated by InitSerializerList (0x156fa30, 0x3c bytes).
struct cSerializerInit {
    void* mField00;                     // 0x00 = "mModelTypeToKeyMap"
    void* mField04;                     // 0x04
    void* mField08;                     // 0x08
    u8    mPad0c[0x18 - 0x0c];          // 0x0c
    void* mField18;                     // 0x18
    void* mField1c;                     // 0x1c
    void* mField20;                     // 0x20
    void* mField24;                     // 0x24
    void* mField28;                     // 0x28
    void* mField2c;                     // 0x2c
    void* mField30;                     // 0x30
    void* mField34;                     // 0x34
    void* mField38;                     // 0x38
};

extern "C" cSerializerInit g_serializerList;   // 0x156fa30

// ---------------------------------------------------------------------------------------------
// Opaque extern callees referenced by absolute address.
// ---------------------------------------------------------------------------------------------
void __cdecl atexit_external(void* fn);  // 0x011e07ef

// ---------------------------------------------------------------------------------------------
// Definitions
// ---------------------------------------------------------------------------------------------
// @ 0x0132ff90
// Initializes the three rbtree sentinel nodes and registers a static destructor.
struct cRbtreeSentinel {
    void* mpSelf;                       // 0x00
    void* mpNext;                       // 0x04
    u32   mField08;                     // 0x08
    union {
        u32 mField0c;                   // 0x0c
        u8  mField0cB;                  // 0x0c
    };
    void* mpField10;                    // 0x10
    u8    mPad14[0x1c - 0x14];          // 0x14
};

extern "C" cRbtreeSentinel g_rbtreeSentinels[3]; // 0x168caf4

void __cdecl InitRbtreeSentinels()
{
    cRbtreeSentinel* node = (cRbtreeSentinel*)0x0168caf4;
    i32 i = 2;
    do {
        node->mField0c = 0;
        node->mpSelf = node;
        node->mpNext = node;
        node->mField08 = 0;
        node->mField0cB = 0;
        node->mpField10 = 0;
        node += 1;
    } while (--i >= 0);
    atexit_external((void*)0x013c33a0);
}

// @ 0x0132ffd0
// Populates the global serializer-list block from a local initializer.
void __cdecl InitSerializerList()
{
    cSerializerInit local;
    local.mField00 = (void*)0x014694a0;
    local.mField04 = (void*)0x03acc32f;
    local.mField18 = 0;
    local.mField1c = 0;
    local.mField20 = (void*)0x00692ca0;
    local.mField24 = (void*)0x00bf34f0;
    local.mField28 = (void*)0x00bf1bc0;
    local.mField2c = (void*)0x00c2e4e0;
    local.mField30 = (void*)0x00692fb0;
    local.mField34 = (void*)0x00d011e0;
    local.mField38 = (void*)0x00bf3d40;
    local.mField08 = 0;
    g_serializerList = local;
}

// @ 0x0132ea70
// Static initializer: fills the model-type serializer descriptor table
// (8 entries of 0x3c bytes each at 0x156f588) from per-entry local blocks.
struct cSerializerDesc {
    const char* mpName;                 // 0x00
    u32         mTag;                   // 0x04
    u32         mSize;                  // 0x08
    u8          mPad0c[0x18 - 0x0c];    // 0x0c (uninitialized in original)
    void*       mpField18;              // 0x18
    void*       mpField1c;              // 0x1c
    void*       mpFn20;                 // 0x20
    void*       mpFn24;                 // 0x24
    void*       mpFn28;                 // 0x28
    void*       mpFn2c;                 // 0x2c
    void*       mpFn30;                 // 0x30
    void*       mpFn34;                 // 0x34
    void*       mpFn38;                 // 0x38
};

extern "C" cSerializerDesc g_serializerDescs[8];   // 0x156f588

// Distinct symbol stubs so every address is an (unfoldable, relocatable) reference,
// matching the original's direct memory-immediate stores.
extern "C" char g_name_mCenterAxis[];   // 0x014691f0
extern "C" char g_name_mpCity[];        // 0x01467e44
extern "C" char g_name_mpDock[];        // 0x014691e8
extern "C" char g_name_mWallSize[];     // 0x014691dc
extern "C" char g_name_mStyle[];        // 0x014691d4
extern "C" char g_name_mLevel[];        // 0x014691cc
extern "C" char g_name_mAppliedStamp[]; // 0x014691bc
extern "C" char g_name_mWallOffset[];   // 0x014691b0

// Each field position gets its own symbol so MSVC cannot CSE repeated addresses
// into callee-saved registers (the original stores every address as a memory
// immediate). Relocations are masked during comparison, so the names are free.
extern "C" char g_fn692ca0[];   // 0x00692ca0 (shared: entries 0-2 f20)
extern "C" char e0_f24[];   // 0x00b6e3a0
extern "C" char e0_f28[];   // 0x00ac88c0
extern "C" char e0_f2c[];   // 0x006930f0
extern "C" char e0_f30[];   // 0x00695010
extern "C" char e0_f34[];   // 0x00b1fbf0
extern "C" char e0_f38[];   // 0x00acbba0
extern "C" char e1_f24[];   // 0x00ae9e00
extern "C" char e1_f28[];   // 0x00bca960
extern "C" char e1_f2c[];   // 0x00c2e4e0
extern "C" char e1_f30[];   // 0x00692fb0
extern "C" char e1_f34[];   // 0x00b6f550
extern "C" char e1_f38[];   // 0x00ac8050
extern "C" char e2_f24[];   // 0x00bed160
extern "C" char e2_f28[];   // 0x00bca960
extern "C" char e2_f2c[];   // 0x00c2e4e0
extern "C" char e2_f30[];   // 0x00692fb0
extern "C" char e2_f34[];   // 0x00b6f550
extern "C" char e2_f38[];   // 0x00ac8050
extern "C" char e3_f20[];   // 0x00572810
extern "C" char e3_f24[];   // 0x00572840
extern "C" char e3_f28[];   // 0x00692ff0
extern "C" char e3_f2c[];   // 0x00694ee0
extern "C" char e3_f30[];   // 0x00b1fbf0
extern "C" char e3_f34[];   // 0x0057cde0
extern "C" char e3_f38[];   // 0x00572810
extern "C" char e4_f20[];   // 0x00572810
extern "C" char e4_f24[];   // 0x00572840
extern "C" char e4_f28[];   // 0x00693090
extern "C" char e4_f2c[];   // 0x00694f00
extern "C" char e4_f30[];   // 0x00b1fbf0
extern "C" char e4_f34[];   // 0x00675ca0
extern "C" char e4_f38[];   // 0x00572810
extern "C" char e5_f20[];   // 0x00572810
extern "C" char e5_f24[];   // 0x00572840
extern "C" char e5_f28[];   // 0x00693090
extern "C" char e5_f2c[];   // 0x00694f00
extern "C" char e5_f30[];   // 0x00b1fbf0
extern "C" char e5_f34[];   // 0x00675ca0
extern "C" char e5_f38[];   // 0x00572810
extern "C" char e6_f20[];   // 0x00ac8750
extern "C" char e6_f24[];   // 0x00ac8780
extern "C" char e6_f28[];   // 0x00693090
extern "C" char e6_f2c[];   // 0x00694fa0
extern "C" char e6_f30[];   // 0x00b1fbf0
extern "C" char e6_f34[];   // 0x0057ce00
extern "C" char e6_f38[];   // 0x00ac8750
extern "C" char e7_f20[];   // 0x00572810
extern "C" char e7_f24[];   // 0x00572840
extern "C" char e7_f28[];   // 0x00692ff0
extern "C" char e7_f2c[];   // 0x00694ee0
extern "C" char e7_f30[];   // 0x00b1fbf0
extern "C" char e7_f34[];   // 0x0057cde0
extern "C" char e7_f38[];   // 0x00572810

#include <string.h>

#define DESC_ENTRY(idx, name, tag, size, f20, f24, f28, f2c, f30, f34, f38)  \
    {                                                                        \
        u32 local[15];                                                       \
        local[0] = (u32)(name);                                              \
        local[1] = (tag);                                                    \
        local[6] = 0;                                                        \
        local[7] = 0;                                                        \
        local[8] = defaultOffset;                                            \
        local[9] = (u32)(f24);                                               \
        local[10] = (u32)(f28);                                              \
        local[11] = (u32)(f2c);                                              \
        local[12] = (u32)(f30);                                              \
        local[13] = (u32)(f34);                                              \
        local[14] = (u32)(f38);                                              \
        local[2] = (size);                                                   \
        memcpy(&g_serializerDescs[idx], local, 0x3c);                        \
    }

void __cdecl InitSerializerDescs()
{
    u32 defaultOffset = (u32)g_fn692ca0;
    DESC_ENTRY(0, g_name_mCenterAxis, 0x02f1a511, 0x338, g_fn692ca0, e0_f24, e0_f28, e0_f2c, e0_f30, e0_f34, e0_f38)
    DESC_ENTRY(1, g_name_mpCity, 0x02f1a512, 0x264, g_fn692ca0, e1_f24, e1_f28, e1_f2c, e1_f30, e1_f34, e1_f38)
    DESC_ENTRY(2, g_name_mpDock, 0x06567f8d, 0x10c, g_fn692ca0, e2_f24, e2_f28, e2_f2c, e2_f30, e2_f34, e2_f38)
    DESC_ENTRY(3, g_name_mWallSize, 0x0474ea17, 0x254, e3_f20, e3_f24, e3_f28, e3_f2c, e3_f30, e3_f34, e3_f38)
    DESC_ENTRY(4, g_name_mStyle, 0x0474ea18, 0x344, e4_f20, e4_f24, e4_f28, e4_f2c, e4_f30, e4_f34, e4_f38)
    DESC_ENTRY(5, g_name_mLevel, 0x0474ea19, 0x348, e5_f20, e5_f24, e5_f28, e5_f2c, e5_f30, e5_f34, e5_f38)
    DESC_ENTRY(6, g_name_mAppliedStamp, 0x04dacb55, 0x350, e6_f20, e6_f24, e6_f28, e6_f2c, e6_f30, e6_f34, e6_f38)
    DESC_ENTRY(7, g_name_mWallOffset, 0x050793d5, 0x34c, e7_f20, e7_f24, e7_f28, e7_f2c, e7_f30, e7_f34, e7_f38)
}
