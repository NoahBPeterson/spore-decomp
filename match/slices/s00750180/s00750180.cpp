// Slice s00750180: cModelWorld occluder/preload helpers (~0x00750180-0x00750780).
// /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "../../include/types.h"

// ---------------------------------------------------------------------------
// @ 0x00750780  SP::cModelWorld::AddOccluder
// ---------------------------------------------------------------------------
struct cOccluderInfo { int f0; int x, y, z; float r; };

struct SlotVector {
    cOccluderInfo* mBegin;   // +0x00
    char pad0[0x18];
    int create(void* out);   // 00750030
};

struct MW6 {
    char pad[0x2bc];
    SlotVector vec;          // +0x2bc
    void AddOccluder(int* src, float f);
};

void MW6::AddOccluder(int* src, float f)
{
    uint32_t tmp[4];
    int idx = vec.create(tmp);
    char* base = (char*)vec.mBegin;
    int off = idx * 0x14;
    *(int*)(base + off + 4) = src[0];
    *(int*)(base + off + 8) = src[1];
    *(int*)(base + off + 0xc) = src[2];
    *(float*)((char*)vec.mBegin + off + 0x10) = f;
}

// ---------------------------------------------------------------------------
// @ 0x00750180  helper   (partial: 386B)
// ---------------------------------------------------------------------------
void helper_50180(void* self) { (void)self; }

// ---------------------------------------------------------------------------
// @ 0x00750310  destructor helper   (partial: 131B EH)
// ---------------------------------------------------------------------------
void dtor_50310(void* self) { (void)self; }

// ---------------------------------------------------------------------------
// @ 0x007503A0  SP::cModelWorld::~cModelWorld   (partial: 415B)
// ---------------------------------------------------------------------------
void dtor_503a0(void* self) { (void)self; }

// ---------------------------------------------------------------------------
// @ 0x007505A0  SP::cModelWorld::PreloadModels   (partial: 479B)
// ---------------------------------------------------------------------------
void preload_505a0(void* self) { (void)self; }
