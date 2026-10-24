// s013277d0.cpp -- gold6 batch, worker 25
// Reconstructed from the annotated disassembly + Ghidra decompiles in
// work/match/scratch_s013277d0_cards.txt.  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
typedef unsigned int   uint32_t;
typedef unsigned char  uint8_t;

// A 60-byte (0x3c) simulator attribute descriptor.  Fields 0x0c/0x10/0x14 are never
// assigned by the original and are copied as-is (the local is reused for every row).
struct SimAttr {
    const char* name;    // +0x00
    uint32_t    key;     // +0x04
    uint32_t    offset;  // +0x08
    uint32_t    r0c;     // +0x0c  (never assigned)
    uint32_t    r10;     // +0x10  (never assigned)
    uint32_t    r14;     // +0x14  (never assigned)
    uint32_t    z18;     // +0x18
    uint32_t    z1c;     // +0x1c
    void*       dflt;    // +0x20  Simulator::Attribute::DefaultOffset (0x692ca0)
    void*       w24;     // +0x24
    void*       w28;     // +0x28
    void*       w2c;     // +0x2c
    void*       w30;     // +0x30
    void*       w34;     // +0x34  0xb1fbf0 UTFWin::Window::Initialize
    void*       w38;     // +0x38
};

// One descriptor row: the statement order mirrors the original store order.
#define ROW(dst, nm, ky, of, f24, f28, f2c, f30, f38)   \
    attr.name   = (const char*)(nm);                     \
    attr.key    = (uint32_t)(ky);                        \
    attr.z18    = 0;                                     \
    attr.z1c    = 0;                                     \
    attr.dflt   = (void*)0x692ca0;                       \
    attr.w24    = (void*)(f24);                          \
    attr.w28    = (void*)(f28);                          \
    attr.w2c    = (void*)(f2c);                          \
    attr.w30    = (void*)(f30);                          \
    attr.offset = (uint32_t)(of);                        \
    attr.w34    = (void*)0xb1fbf0;                       \
    attr.w38    = (void*)(f38);                          \
    *(SimAttr*)(dst) = attr;

// ===========================================================================
// 0x013277d0 - register the save-game class attribute table (14 rows)
// ===========================================================================
// @ 0x013277d0
void __cdecl FUN_013277d0(void) {
    SimAttr attr;
    ROW(0x156cb70, 0x1465750, 0x3d58bf2, 0x70, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156cbac, 0x145bc18, 0x3d58bf1, 0x3c, 0xb6e3a0, 0xac88c0, 0x6930f0, 0x695010, 0xacbba0)
    ROW(0x156cbe8, 0x14665d4, 0x3e95e04, 0x48, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0x57cde0)
    ROW(0x156cc24, 0x14665c8, 0x3d58bf6, 0x4c, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0x57cde0)
    ROW(0x156cc60, 0x1411e88, 0x3d58bf4, 0x60, 0xac87c0, 0xac87f0, 0x694c80, 0x694c10, 0xacbbc0)
    ROW(0x156cc9c, 0x145ca9c, 0x3d58bf3, 0x5c, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156ccd8, 0x14665b4, 0x3d58bf5, 0x74, 0xae3430, 0xae3450, 0x693150, 0x695080, 0xae5720)
    ROW(0x156cd14, 0x14665a4, 0x3d58bf7, 0x58, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156cd50, 0x1466598, 0x3f1389b, 0x54, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156cd8c, 0x1466584, 0x3f1389a, 0x0c, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156cdc8, 0x1466570, 0x3f1389c, 0x18, 0xb26970, 0xb26990, 0xc2e4e0, 0x692fb0, 0xac8050)
    ROW(0x156ce04, 0x1466558, 0x3f1389d, 0x10, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156ce40, 0x1466540, 0x3f1389e, 0x14, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156ce7c, 0x1466534, 0x51a1188, 0xac, 0xbb9cd0, 0xbb9d00, 0x693070, 0x694f80, 0x595a50)
}

// Same descriptor template, but with an explicit +0x34 slot (it is not always
// the shared 0xb1fbf0 Initialize@Window in the second/third routines).
#define ROWF(dst, nm, ky, of, f24, f28, f2c, f30, f34, f38) \
    attr.name   = (const char*)(nm);                         \
    attr.key    = (uint32_t)(ky);                            \
    attr.z18    = 0;                                         \
    attr.z1c    = 0;                                         \
    attr.dflt   = (void*)0x692ca0;                           \
    attr.w24    = (void*)(f24);                              \
    attr.w28    = (void*)(f28);                              \
    attr.w2c    = (void*)(f2c);                              \
    attr.w30    = (void*)(f30);                              \
    attr.offset = (uint32_t)(of);                            \
    attr.w34    = (void*)(f34);                              \
    attr.w38    = (void*)(f38);                              \
    *(SimAttr*)(dst) = attr;

// ===========================================================================
// 0x01328ee0 - register the space-agent / artifact attribute table (8 rows)
// ===========================================================================
// @ 0x01328ee0
void __cdecl FUN_01328ee0(void) {
    SimAttr attr;
    ROWF(0x156cfe0, 0x14667b8, 0x4e3b373, 0x00, 0x572810, 0x572840, 0x693090, 0x694f00, 0xb1fbf0, 0x675ca0)
    ROWF(0x156d01c, 0x14667a8, 0x4e3b37d, 0x04, 0xb6e3a0, 0xac88c0, 0x6930f0, 0x695010, 0xb1fbf0, 0xacbba0)
    ROWF(0x156d058, 0x145ca9c, 0x4e3b37e, 0x28, 0xbb9cd0, 0xbb9d00, 0x693070, 0x694f80, 0xb1fbf0, 0x595a50)
    ROWF(0x156d094, 0x1466798, 0x4e3b37f, 0x12, 0xbb9cd0, 0xbb9d00, 0x693070, 0x694f80, 0xb1fbf0, 0x595a50)
    ROWF(0x156d0d0, 0x1466790, 0x4e3b380, 0x10, 0xbc3270, 0xff05d0, 0x693030, 0x694f40, 0xb1fbf0, 0xbc3470)
    ROWF(0x156d10c, 0x1466788, 0x5c41511, 0x14, 0x572810, 0xac88f0, 0x6930b0, 0x694fc0, 0xb1fbf0, 0xacbb80)
    ROWF(0x156d148, 0x1466778, 0x5d0f859, 0x18, 0x572810, 0x572840, 0x693090, 0x694f00, 0xb1fbf0, 0x675ca0)
    ROWF(0x156d184, 0x1465750, 0x5de82a2, 0x1c, 0xae3430, 0xae3450, 0x693150, 0x695080, 0xb1fbf0, 0xae5720)
}

// ===========================================================================
// 0x01329420 - register the agent-order / data-serializer attribute table (9 rows)
// ===========================================================================
// @ 0x01329420
void __cdecl FUN_01329420(void) {
    SimAttr attr;
    ROWF(0x156d2a8, 0x14665d4, 0x4bfec52, 0x00, 0x572810, 0x572840, 0x693090, 0x694f00, 0xb1fbf0, 0x675ca0)
    ROWF(0x156d2e4, 0x145fcb4, 0x57a4efc, 0x08, 0xae3470, 0xae3490, 0xc2e4e0, 0x692fb0, 0xae3310, 0xac8050)
    ROWF(0x156d320, 0x14669f8, 0x4bfec53, 0x28, 0xbca770, 0xbca960, 0xc2e4e0, 0x692fb0, 0xbca7e0, 0xac8050)
    ROWF(0x156d35c, 0x14669ec, 0x4bfec54, 0x39, 0xbca2e0, 0xbca2e0, 0xc2e4e0, 0x692fb0, 0xb1fbf0, 0xac8050)
    ROWF(0x156d398, 0x14669e0, 0x4bfec55, 0x4d, 0xbca2e0, 0xbca2e0, 0xc2e4e0, 0x692fb0, 0xb1fbf0, 0xac8050)
    ROWF(0x156d3d4, 0x14669d4, 0x4bfec56, 0x61, 0xbca2e0, 0xbca2e0, 0xc2e4e0, 0x692fb0, 0xb1fbf0, 0xac8050)
    ROWF(0x156d410, 0x14669c8, 0x4bfec57, 0x75, 0xbca2e0, 0xbca2e0, 0xc2e4e0, 0x692fb0, 0xb1fbf0, 0xac8050)
    ROWF(0x156d44c, 0x14669bc, 0x4bfec58, 0x38, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00)
    ROWF(0x156d488, 0x14669a8, 0x4bfec59, 0x2c, 0xb6e3a0, 0xac88c0, 0x6930f0, 0x695010, 0xb1fbf0, 0xacbba0)
}