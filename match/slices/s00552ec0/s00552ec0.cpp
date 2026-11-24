// Same shape as s004202f0's SmallBuffer::SmallBuffer (0x004209f0): initialise the
// params block, then either the fixed empty buffer (n < 2) or allocate.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE

extern const float kOne_00552ec0;                 // 0x01485720
extern const float kTwo_00552ec0;                 // 0x01470f1c
extern unsigned int g_EmptyBuffer_00552ec0[];     // 0x0154df28

struct BufferParams_00552ec0 {
    float growth;       // +0x10
    float scale;        // +0x14
    int   offset;       // +0x18
    unsigned int AllocateCapacity(unsigned int n);   // 0x00921360
};

struct Pad24_00552ec0 { unsigned int w[6]; };

struct SmallBuffer_00552ec0 {
    unsigned int pad0;
    unsigned int* mpData;     // +4
    unsigned int mnCapacity;  // +8
    unsigned int mnCount;     // +0xc
    BufferParams_00552ec0 mParams;   // +0x10
    unsigned int pad1c;       // +0x1c
    SmallBuffer_00552ec0(unsigned int n, Pad24_00552ec0 unused);
    unsigned int* Allocate(unsigned int n);   // 0x00554410
};

// @ 0x000552ec0
SmallBuffer_00552ec0::SmallBuffer_00552ec0(unsigned int n, Pad24_00552ec0 unused)
    : mnCapacity(0), mnCount(0)
{
    BufferParams_00552ec0* p = &mParams;
    p->growth = kOne_00552ec0;
    p->scale = kTwo_00552ec0;
    p->offset = 0;
    if (n < 2) {
        mnCapacity = 1;
        mpData = g_EmptyBuffer_00552ec0;
        mnCount = 0;
        mParams.offset = 0;
    } else {
        mnCapacity = mParams.AllocateCapacity(n);
        mpData = Allocate(mnCapacity);
    }
}
