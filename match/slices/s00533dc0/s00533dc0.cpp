// Slice s00533dc0: Swarm distribute sample vector + colour packing helpers.
// 00533dc0 is a 2713-byte effect algorithm (partial: stub only).
// 00534860/005348e0 pack/clamp colours; 005349f0/00534a70 are
// eastl::vector<EA::Swarm::cDistributeSample,eastl::sp_vector_allocator>::push_back /
// DoInsertValue (element stride 0x1c). Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE
// /fp:fast.
#include "types.h"

typedef unsigned int size_t;
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags);   // 0x0042dee0
extern "C" void EASTL_allocator_deallocate(void* p);                        // 0x00f47380
extern "C" void* memmove(void* dst, const void* src, size_t n);             // 0x13cc480

// ---------------------------------------------------------------- @ 0x00533dc0
// Large distribution algorithm (2713 bytes); skeleton only -- see partial.txt.
void DistributeSamplesStub()
{
}

// ---------------------------------------------------------------- @ 0x005348e0
inline uint8_t PackComponent(float v)
{
    float f = 0.0f;
    if (0.0f <= v)
        f = v;
    f = f * 255.0f;
    if (255.0f <= f)
        f = 255.0f;
    return (uint8_t)(int)f;
}

// @ 0x005348e0
uint32_t PackColor(float* v)
{
    uint8_t a = PackComponent(v[3]);
    uint8_t b = PackComponent(v[2]);
    uint8_t g = PackComponent(v[1]);
    uint8_t r = PackComponent(v[0]);
    return (uint32_t)((a << 24) | (r << 16) | (g << 8) | b);
}

// ---------------------------------------------------------------- @ 0x00534860
void PackColorWrapper(float* v, float w)
{
    float t[4];
    t[0] = v[0];
    t[1] = v[1];
    t[2] = v[2];
    t[3] = w;
    PackColor(t);
}

// ---------------------------------------------------------------- distribute sample vector
struct Sample {
    uint32_t d[7];
};
struct VectorSample {
    Sample* mpBegin;
    Sample* mpEnd;
    Sample* mpCapacity;
    uint32_t mAlloc[2];
    VectorSample() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void push_back(const Sample& value);                 // @ 0x005349f0
    void DoInsertValue(Sample* position, const Sample& value);   // @ 0x00534a70
};

// @ 0x005349f0
void VectorSample::push_back(const Sample& value)
{
    if (mpEnd < mpCapacity) {
        *mpEnd = value;
        mpEnd = mpEnd + 1;
    } else {
        DoInsertValue(mpEnd, value);
    }
}

// @ 0x00534a70
void VectorSample::DoInsertValue(Sample* position, const Sample& value)
{
    if (mpEnd != mpCapacity) {
        // shift [position, end) right by one
        for (Sample* p = mpEnd; p != position; --p)
            *(p) = *(p - 1);
        *position = value;
        mpEnd = mpEnd + 1;
        return;
    }
    uint32_t nOld = (uint32_t)(mpEnd - mpBegin);
    uint32_t nNewCapacity = (nOld > 0) ? nOld * 2 : 1;
    Sample* pNew = (nNewCapacity == 0)
                       ? 0
                       : (Sample*)EASTL_Allocate(mAlloc, nNewCapacity * 0x1c, 4, 0);
    Sample* p = pNew;
    uint32_t nIndex = (uint32_t)(position - mpBegin);
    for (uint32_t i = 0; i < nIndex; ++i)
        *p++ = mpBegin[i];
    *p++ = value;
    for (uint32_t i = nIndex; i < nOld; ++i)
        *p++ = mpBegin[i];
    if (mpBegin != 0 && ((uint32_t*)mpBegin)[-1] != 0)
        EASTL_allocator_deallocate(mpBegin);
    mpBegin = pNew;
    mpEnd = p;
    mpCapacity = pNew + nNewCapacity;
}
