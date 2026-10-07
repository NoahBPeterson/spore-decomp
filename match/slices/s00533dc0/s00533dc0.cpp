// Slice s00533dc0: Swarm distribute sample vector + colour packing helpers.
// 00533dc0 builds the distribute sample list from the paint mesh (complete; /EHsc for its
// remap vector's unwind entry).
// 00534860/005348e0 pack/clamp colours; 005349f0/00534a70 are
// eastl::vector<EA::Swarm::cDistributeSample,eastl::sp_vector_allocator>::push_back /
// DoInsertValue (element stride 0x1c). Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE
// /fp:fast /EHsc.
#include "types.h"

typedef unsigned int size_t;
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags);   // 0x0042dee0
extern "C" void EASTL_allocator_deallocate(void* p);                        // 0x00f47380
extern "C" void* memmove(void* dst, const void* src, size_t n);             // 0x13cc480

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
uint32_t PackColorWrapper(float* v, float w)
{
    float t[4];
    t[0] = v[0];
    t[1] = v[1];
    t[2] = v[2];
    t[3] = w;
    return PackColor(t);
}

// ---------------------------------------------------------------- distribute sample vector
struct Vector2 { float x, y; };
struct Sample {              // EA::Swarm::cDistributeSample (0x1c bytes)
    Vector2 uv;              // +0x00
    uint32_t color;          // +0x08 packed RGB from HSV + alpha
    uint32_t tint;           // +0x0c packed BGRA bytes
    Vector2 st;              // +0x10
    float weight;            // +0x18
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

// ---------------------------------------------------------------- @ 0x00533dc0
// Rebuilds the distribute sample list: walks the paint mesh triangles, evaluates the paint
// variables once per unique vertex (remap table), and appends one cDistributeSample per corner,
// starting a new batch every 12000 triangles.
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& v);                  // 0x004098a0 (rw Vector3Template copy)
    float& operator[](int i) { return (&x)[i]; }
};
struct Vector4 {
    float x, y, z, w;
    Vector4(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
    float operator[](int i) const { return (&x)[i]; }
};
struct ColorBGRA { uint8_t b, g, r, a; };

extern cSPVector3 gPaletteColors[];                   // 0x015df204
extern Vector2 gDefaultSampleST;                      // 0x015e1820
struct PaintValues { float v[19]; };                  // nSPSkinner paint variable values
extern const PaintValues kDefaultPaintValues;         // 0x013f2720

float FracPart(float x, float* pInt);                                 // 0x004fa520
cSPVector3* HSVToRGB(cSPVector3* result, cSPVector3 hsv);             // 0x0052a030

// maxss/minss clamp to [0, 1] (an __asm helper in the original).
__forceinline float clamp_unit(float x)
{
    float one = 1.0f;
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, x
        minss xmm0, one
        movss x, xmm0
    }
    return x;
}
// clamp to [0, 1], scale to [0, 255] and round with cvtss2si (an __asm helper in the original).
__forceinline uint8_t UnitToByte(float x)
{
    float k = 255.0f;
    int r;
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, x
        mulss xmm0, k
        minss xmm0, k
        cvtss2si eax, xmm0
        mov r, eax
    }
    return (uint8_t)r;
}
__forceinline ColorBGRA ToColor(const Vector4& c)
{
    uint8_t a = UnitToByte(c[3]);
    uint8_t b = UnitToByte(c[2]);
    uint8_t g = UnitToByte(c[1]);
    uint8_t r = UnitToByte(c[0]);
    ColorBGRA out;
    out.b = b;
    out.g = g;
    out.r = r;
    out.a = a;
    return out;
}

namespace nSPSkinner {
struct cPaintVarEvalList {
    void Apply(float* const values, float age, const cSPVector3& pos, const cSPVector3& normal,
               uint32_t index) const;                 // 0x00515710
};
}

struct DefaultAlloc { DefaultAlloc() {} };
struct IntIterator {
    int* p;
    IntIterator(int* q) : p(q) {}
    IntIterator(const IntIterator& o) : p(o.p) {}
};
IntIterator uninitialized_fill_n(IntIterator first, uint32_t n, const int& value);  // 0x004ab450

struct IntVectorBase {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    uint32_t mAlloc[2];
    IntVectorBase(uint32_t n, const DefaultAlloc& allocator);   // 0x004aa350
    ~IntVectorBase();                                           // 0x00425990
};
struct IntVector : IntVectorBase {
    __forceinline IntVector(uint32_t n, const int& value, const DefaultAlloc& allocator = DefaultAlloc())
        : IntVectorBase(n, allocator)
    {
        uninitialized_fill_n(IntIterator(mpBegin), n, value);
        mpEnd = mpBegin + n;
    }
    ~IntVector()
    {
        for (int* p = mpBegin; p < mpEnd; ++p) {
        }
    }
    int& operator[](int i) { return mpBegin[i]; }
};

template<class T> struct MeshVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAlloc[2];
    int size() const { return (int)(mpEnd - mpBegin); }
};
template<class T> struct UIntVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAlloc[2];
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};

struct SampleBatch {                                  // 0x18 bytes
    int mFirstSample;
    uint32_t mVertexCount;
    uint8_t mColor[3];
    bool mbUseMeshColor;
    int mReserved[3];
};
struct BatchVector {
    SampleBatch* mpBegin;
    SampleBatch* mpEnd;
    SampleBatch* mpCapacity;
    uint32_t mAlloc[2];
    SampleBatch& push_back();                         // 0x00513d20
    SampleBatch& back() { return *(mpEnd - 1); }
};
struct SampleOutput {
    VectorSample mSamples;                            // +0x00
    BatchVector mBatches;                             // +0x14
};
struct PaintTarget {
    uint32_t pad0[2];
    SampleOutput* mpOutput;                           // +0x08
};
struct PaintMesh {
    uint32_t pad0[2];
    MeshVector<cSPVector3> mPositions;                // +0x08
    MeshVector<cSPVector3> mNormals;                  // +0x1c
    MeshVector<Vector2> mTexCoords;                   // +0x30
    MeshVector<int> mUnused44;                        // +0x44
    UIntVector<int> mIndices0;                        // +0x58
    UIntVector<int> mIndices1;                        // +0x6c
    UIntVector<int> mIndices2;                        // +0x80
};
struct PaintSystem {
    uint32_t pad0[3];
    PaintTarget* mpTarget;                            // +0x0c
    PaintMesh* mpMesh;                                // +0x10
};
PaintSystem* GetPaintSystem();                        // 0x00401080

struct cDistributeEffect {
    void* vtable;
    uint32_t pad04[2];
    uint8_t* mpDesc;                                  // +0x0c: +0x08 paint vars, +0x48 HSV,
                                                      // +0x54 palette index, +0x58 RGB bytes
    bool mbNeedsRebuild;                              // +0x10
    void RebuildSamples(uint32_t a, uint32_t b, uint32_t c);
};

// @ 0x00533dc0
void cDistributeEffect::RebuildSamples(uint32_t, uint32_t, uint32_t)
{
    if (!mbNeedsRebuild)
        return;

    PaintSystem* system = GetPaintSystem();
    PaintTarget* target = system->mpTarget;
    SampleOutput* output = target->mpOutput;
    PaintSystem* meshSystem = GetPaintSystem();
    PaintMesh* paintMesh = meshSystem->mpMesh;
    PaintMesh* mesh = paintMesh;

    int unused = -1;
    MeshVector<cSPVector3>& positions = mesh->mPositions;
    int vertexCount = positions.size();
    IntVector remap(vertexCount, unused);

    cSPVector3 hsv;
    if (*(int*)(mpDesc + 0x54) < 0) {
        hsv = *(cSPVector3*)(mpDesc + 0x48);
    } else {
        int paletteIndex = *(int*)(mpDesc + 0x54);
        hsv = cSPVector3(gPaletteColors[paletteIndex]);
    }

    int* indices0 = mesh->mIndices0.mpBegin;
    int* indices1 = mesh->mIndices1.mpBegin;
    int* indices2 = mesh->mIndices2.mpBegin;
    cSPVector3* pos = mesh->mPositions.mpBegin;
    cSPVector3* normals = mesh->mNormals.mpBegin;
    Vector2* uvs = mesh->mTexCoords.mpBegin;
    UIntVector<int>& tris = mesh->mIndices0;
    uint32_t triCount = tris.size() / 3;
    uint32_t batchTris = 12000;

    for (uint32_t tri = 0; tri < triCount; ++tri, ++batchTris) {
        if (batchTris >= 12000) {
            batchTris = 0;
            output->mBatches.push_back();
            SampleBatch& batch = output->mBatches.back();
            batch.mFirstSample = (int)(output->mSamples.mpEnd - output->mSamples.mpBegin);
            uint32_t maxTris = 12000;
            uint32_t remaining = triCount - tri;
            const uint32_t& n = (maxTris < remaining) ? maxTris : remaining;
            batch.mVertexCount = n * 3;
            batch.mColor[0] = mpDesc[0x58];
            batch.mColor[1] = mpDesc[0x59];
            batch.mColor[2] = mpDesc[0x5a];
            batch.mbUseMeshColor = *(int*)(mpDesc + 0x54) == -2;
            for (int k = 0; k < 3; ++k)
                batch.mReserved[k] = 0;
        }

        int* i0 = indices0 + tri * 3;
        int* i1 = indices1 + tri * 3;
        int* i2 = indices2 + tri * 3;
        for (int corner = 0; corner < 3; ++corner, ++i0, ++i1, ++i2) {
            int& sampleIndex = remap[*i0];
            if (sampleIndex == -1) {
                sampleIndex = (int)(output->mSamples.mpEnd - output->mSamples.mpBegin);
                PaintValues values = kDefaultPaintValues;
                values.v[7] = hsv[0];
                values.v[8] = hsv[1];
                values.v[9] = hsv[2];
                ((nSPSkinner::cPaintVarEvalList*)(mpDesc + 8))
                    ->Apply(values.v, 0.0f, pos[*i0], normals[*i1], *i0);

                float intPart;
                float hue = FracPart(values.v[7] / 360.0f, &intPart) * 360.0f;
                float sat = clamp_unit(values.v[8]);
                float val = values.v[9];
                Vector4 tintColor(values.v[13], values.v[14] * values.v[6], values.v[11],
                                  values.v[12] * values.v[6]);
                ColorBGRA tint = ToColor(tintColor);

                cSPVector3 rgb;
                uint32_t color = PackColorWrapper(&HSVToRGB(&rgb, cSPVector3(hue, sat, val))->x,
                                                  values.v[10] * values.v[6]);

                Vector2& uv = uvs[*i2];
                Sample sample;
                sample.uv.x = uv.x;
                sample.uv.y = uv.y;
                sample.color = color;
                sample.tint = *(uint32_t*)&tint;
                Vector2* st = &sample.st;
                st->x = gDefaultSampleST.x;
                st->y = gDefaultSampleST.y;
                sample.weight = 1.0f;
                output->mSamples.push_back(sample);
            } else {
                output->mSamples.push_back(output->mSamples.mpBegin[sampleIndex]);
                output->mSamples.mpEnd[-1].uv = uvs[*i2];
            }
        }
    }
    mbNeedsRebuild = false;
}
