// Slice s00f52df0 -- SPEngine/SPAppCloudDescription.obj: cCloudDescription dtor + default ctor.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <stddef.h>

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
};

void operator delete(void* p);
inline void* operator new(size_t, void* p) throw() { return p; }

namespace SP {
template <class T> struct SimpleVector {                        // eastl::vector<T, sp_vector_allocator>
    T*       mpBegin;                                            // +0x00
    T*       mpEnd;                                              // +0x04
    T*       mpCapacity;                                         // +0x08
    uint32_t mAllocator[2];                                      // +0x0c

    void DoInsertValue(T* pos, const T& value);                  // 0x00455660
    void AllocateCopy(int count, const void* allocator);          // 0x004aa350
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void FreeRange(T* first, T* last);                           // 0x00a87300
};

template <class T> struct Vector {                               // out-of-line DoInsertValue
    T*       mpBegin;                                            // +0x00
    T*       mpEnd;                                              // +0x04
    T*       mpCapacity;                                         // +0x08
    uint32_t mAllocator[2];                                      // +0x0c

    void DoInsertValue(T* pos, const T& value);                  // 0x007ed1b0
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
}  // namespace SP

// Data constants whose runtime values are established elsewhere in the image.
extern const float g_16c9234;   // 0x016c9234
extern const float g_16c9238;   // 0x016c9238
extern const float g_16c923c;   // 0x016c923c

// ---------------------------------------------------------------------------
// cCloudDescription -- 0x268-byte cloud description/command block.
// ---------------------------------------------------------------------------
struct cCloudDescription {
    void*    mVtbl;                 // +0x000
    void*    mParser;               // +0x004
    uint32_t m08;                   // +0x008
    float    f0c, f10, f14, f18, f1c, f20, f24;                       // +0x00c .. +0x027
    float    f28, f2c, f30, f34, f38, f3c;                            // +0x028 .. +0x03f
    float    f40, f44, f48, f4c, f50, f54, f58, f5c, f60;             // +0x040 .. +0x063
    SP::SimpleVector<float> v64;    // +0x064
    float    f78;                   // +0x078
    uint16_t w7c;                   // +0x07c
    uint8_t  pad7e[2];              // +0x07e (uninitialised)
    float    f80;                   // +0x080
    SP::SimpleVector<float> v84;    // +0x084
    float    f98;                   // +0x098
    SP::SimpleVector<float> v9c;    // +0x09c
    float    fb0;                   // +0x0b0
    SP::SimpleVector<float> vb4;    // +0x0b4
    float    fc8;                   // +0x0c8
    float    fcc;                   // +0x0cc
    SP::Vector<Vec3> d0;            // +0x0d0
    float    fe4, fe8, fec;         // +0x0e4 .. +0x0ec
    SP::SimpleVector<float> vf0;    // +0x0f0
    float    f104;                  // +0x104
    int32_t  a108;                  // +0x108
    int32_t  a10c;                  // +0x10c
    uint8_t  b110;                  // +0x110
    uint8_t  b111;                  // +0x111
    uint8_t  b112;                  // +0x112
    uint8_t  b113;                  // +0x113
    uint16_t w114;                  // +0x114
    uint8_t  pad116[2];             // +0x116 (uninitialised)
    float    f118;                  // +0x118
    uint8_t  pad11c[4];             // +0x11c (uninitialised)
    int32_t  a120;                  // +0x120
    int32_t  a124;                  // +0x124
    uint8_t  b128;                  // +0x128
    uint8_t  b129;                  // +0x129
    uint8_t  b12a;                  // +0x12a
    uint8_t  b12b;                  // +0x12b
    uint8_t  b12c;                  // +0x12c
    uint8_t  b12d;                  // +0x12d
    uint8_t  b12e;                  // +0x12e
    uint8_t  b12f;                  // +0x12f
    float    f130[13];              // +0x130 .. +0x163
    SP::SimpleVector<float> s164;   // +0x164
    uint8_t  b178;                  // +0x178
    uint8_t  b179;                  // +0x179
    uint8_t  b17a;                  // +0x17a
    uint8_t  b17b;                  // +0x17b
    uint8_t  pad17c[4];             // +0x17c (uninitialised)
    SP::SimpleVector<float> s180;   // +0x180
    SP::SimpleVector<float> v194;   // +0x194
    SP::SimpleVector<float> s1a8;   // +0x1a8
    float    f1bc[9];               // +0x1bc .. +0x1df
    int32_t  a1e0[6];               // +0x1e0 .. +0x1f7
    float    a1f8[7];               // +0x1f8 .. +0x213
    SP::SimpleVector<float> v214;   // +0x214
    uint8_t  b228;                  // +0x228
    uint8_t  pad229[3];             // +0x229 (uninitialised)
    float    f22c;                  // +0x22c
    float    f230;                  // +0x230
    float    f234;                  // +0x234
    SP::SimpleVector<float> v238;   // +0x238
    float    f24c;                  // +0x24c
    float    f250;                  // +0x250
    SP::SimpleVector<float> s254;   // +0x254

    cCloudDescription();
    ~cCloudDescription();
};

typedef char chk_size[(sizeof(cCloudDescription) == 0x268) ? 1 : -1];
typedef char chk_v64[((char*)&((cCloudDescription*)0)->v64 - (char*)0 == 0x064) ? 1 : -1];
typedef char chk_d0 [((char*)&((cCloudDescription*)0)->d0  - (char*)0 == 0x0d0) ? 1 : -1];
typedef char chk_f0 [((char*)&((cCloudDescription*)0)->vf0 - (char*)0 == 0x0f0) ? 1 : -1];
typedef char chk_254[((char*)&((cCloudDescription*)0)->s254 - (char*)0 == 0x254) ? 1 : -1];

// Counted-allocation release used by the destructor.
static inline void FreeCounted(void* p) {
    if (p) {
        if (((int*)p)[-1] != 0)
            operator delete(p);
    }
}

// @ 0x00f53420
cCloudDescription::~cCloudDescription()
{
    FreeCounted(s254.mpBegin);
    FreeCounted(v238.mpBegin);
    FreeCounted(v214.mpBegin);
    s1a8.FreeRange(s1a8.mpBegin, s1a8.mpEnd);
    FreeCounted(s1a8.mpBegin);
    FreeCounted(v194.mpBegin);
    FreeCounted(s180.mpBegin);
    FreeCounted(s164.mpBegin);
    FreeCounted(vf0.mpBegin);
    FreeCounted(d0.mpBegin);
    FreeCounted(vb4.mpBegin);
    FreeCounted(v9c.mpBegin);
    FreeCounted(v84.mpBegin);
    FreeCounted(v64.mpBegin);
    mVtbl = (void*)0x13ef094;
}

// @ 0x00f53590
cCloudDescription::cCloudDescription()
{
    mParser = 0;
    mVtbl = (void*)0x148e910;
    m08 = 0;

    f0c = 2.0f;
    f10 = 2.0f;
    f14 = 0.0f;
    f18 = -1.0f;
    f1c = -1.0f;
    f20 = -1.0f;
    f24 = -1.0f;
    f28 = 0.0f;
    f2c = 0.0f;
    f30 = 1.0f;
    f34 = 0.0f;
    f38 = 0.0f;
    f3c = 1.0f;
    f40 = 0.0f; f44 = 0.0f; f48 = 0.0f; f4c = 0.0f;
    f50 = 0.0f; f54 = 0.0f; f58 = 0.0f; f5c = 0.0f;
    f60 = -1.0f;

    v64.mpBegin = 0; v64.mpEnd = 0; v64.mpCapacity = 0;
    f78 = 1.0f;
    w7c = 0;
    f80 = 0.0f;
    v84.mpBegin = 0; v84.mpEnd = 0; v84.mpCapacity = 0;
    f98 = 0.0f;
    v9c.mpBegin = 0; v9c.mpEnd = 0; v9c.mpCapacity = 0;
    fb0 = 0.0f;
    vb4.mpBegin = 0; vb4.mpEnd = 0; vb4.mpCapacity = 0;
    fc8 = 0.0f;
    fcc = 0.0f;
    d0.mpBegin = 0; d0.mpEnd = 0; d0.mpCapacity = 0;

    fe4 = g_16c9234;
    fe8 = g_16c9238;
    fec = g_16c923c;

    vf0.mpBegin = 0; vf0.mpEnd = 0; vf0.mpCapacity = 0;
    f104 = 0.0f;

    a108 = -1;
    a10c = -1;
    b110 = 0; b111 = 0; b112 = 0; b113 = 0;
    w114 = 0;
    f118 = 0.0f;
    a120 = -1;
    a124 = -1;
    b128 = 0; b129 = 0;
    b12c = 0; b12d = 0; b12e = 0; b12f = 0;
    f130[0] = 0.0f;
    b12a = 1; b12b = 1;

    f130[1] = g_16c9234;
    f130[2] = g_16c9238;
    f130[3] = g_16c923c;
    f130[4] = 0.0f; f130[5] = 0.0f; f130[6] = 0.0f;
    f130[7] = g_16c9234;
    f130[8] = g_16c9238;
    f130[9] = g_16c923c;
    f130[10] = 0.0f; f130[11] = 0.0f; f130[12] = 0.0f;

    s164.mpBegin = 0; s164.mpEnd = 0; s164.mpCapacity = 0;
    b178 = 0; b17a = 0;
    b179 = 0xff; b17b = 0xff;
    s180.mpBegin = 0; s180.mpEnd = 0; s180.mpCapacity = 0;
    v194.mpBegin = 0; v194.mpEnd = 0; v194.mpCapacity = 0;
    s1a8.mpBegin = 0; s1a8.mpEnd = 0; s1a8.mpCapacity = 0;

    f1bc[5] = -1.0e9f;
    f1bc[0] = 1.0f;
    f1bc[1] = 0.0f; f1bc[2] = 0.0f; f1bc[3] = 0.0f; f1bc[4] = 0.0f;
    f1bc[6] = 0.0f;
    f1bc[7] = -10000.0f;
    f1bc[8] = 10000.0f;

    a1e0[0] = -1; a1e0[1] = -1; a1e0[2] = -1;
    a1e0[3] = -1; a1e0[4] = -1; a1e0[5] = -1;

    a1f8[0] = 5.0f; a1f8[1] = 5.0f;
    a1f8[2] = 0.0f; a1f8[3] = 0.0f;
    a1f8[4] = 0.25f;
    a1f8[5] = 0.0f; a1f8[6] = 0.0f;

    v214.mpBegin = 0; v214.mpEnd = 0; v214.mpCapacity = 0;
    b228 = 2;
    f22c = g_16c9234;
    f230 = g_16c9238;
    f234 = g_16c923c;
    v238.mpBegin = 0; v238.mpEnd = 0; v238.mpCapacity = 0;
    f24c = 1.0f;
    f250 = 0.0f;
    s254.mpBegin = 0; s254.mpEnd = 0; s254.mpCapacity = 0;

    v64.push_back(30.0f);
    d0.push_back(Vec3(1.0f, 1.0f, 1.0f));
    vf0.push_back(1.0f);
    v84.push_back(1.0f);
    v9c.push_back(1.0f);
    vb4.push_back(0.0f);
}

// ---------------------------------------------------------------------------
// WriteSettings (0x00f52df0): serialises a cCloudDescription-sized (0x268) object; restored from before the gold7
// rewrite. Built with /O2 /MD /Gy /EHsc /TP /arch:SSE (no /fp:fast; see manifest). Vec3 is the one declared above.
// ---------------------------------------------------------------------------
struct IStream {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual int Read(void* data, uint32_t size);                  // +0x30
    virtual void v13();
    virtual bool Write(const void* data, uint32_t size);          // +0x38
};
bool WriteUint16(IStream* s, const uint16_t* p, uint32_t count, int endian);  // 0x0093a9d0
bool WriteUint32(IStream* s, const uint32_t* p, uint32_t count, int endian);  // 0x0093aa70
bool WriteUint64(IStream* s, const uint64_t* p, uint32_t count, int endian);  // 0x0093ab10
bool WriteBool8(IStream* s, const bool* p, uint32_t count);                   // 0x0093a9a0

struct Vec2 { float x, y; };
struct FloatVector { float* mpBegin; float* mpEnd; float* mpCapacity; uint32_t mAllocator[2]; };  // 0x14 bytes

// nested members, each with its own writer
struct SubA { uint32_t d[5]; };                                        // 0x14 bytes
struct SubB { uint32_t d[8]; };                                        // 0x20 bytes
struct SubC { uint32_t d[5]; };                                        // 0x14 bytes
struct SubD { uint32_t d[5]; };                                        // 0x14 bytes
struct SubE { uint32_t d[5]; };                                        // 0x14 bytes
struct SubF { uint32_t d[13]; };                                       // 0x34 bytes
struct SubG { uint32_t d[7]; };                                        // 0x1c bytes
struct SubH { uint32_t d[5]; };                                        // 0x14 bytes
IStream* WriteFloatVector(IStream* s, const FloatVector* v);           // 0x007d0250
IStream* WriteSubA(IStream* s, const SubA* v);                         // 0x007ec580
void     WriteSubB(IStream* s, const SubB* v);                         // 0x00a85a20
IStream* WriteSubC(IStream* s, const SubC* v);                         // 0x00a99290
IStream* WriteSubD(IStream* s, const SubD* v);                         // 0x00a871e0
void     WriteSubF(IStream* s, const SubF* v);                         // 0x00a7a3b0
IStream* WriteSubG(IStream* s, const SubG* v);                         // 0x00a7a450
IStream* WriteSubH(IStream* s, const SubH* v);                         // 0x00a992f0

struct Settings {
    uint32_t pad00[2];
    uint32_t mId;            // +0x08
    Vec2 v0c;                // +0x0c
    float f14;
    Vec2 v18;
    Vec2 v20;
    Vec3 box28[2];           // +0x28 (min, max)
    Vec2 v40;
    Vec3 box48[2];           // +0x48
    float f60;
    FloatVector vec64;       // +0x64
    float f78;
    uint16_t u7c;
    uint16_t pad7e;
    float f80;
    FloatVector vec84;
    float f98;
    FloatVector vec9c;
    float fb0;
    FloatVector vecb4;
    float fc8;
    float fcc;
    SubA subd0;              // +0xd0
    Vec3 ve4;                // +0xe4
    FloatVector vecf0;
    float f104;
    SubB sub108;             // +0x108
    bool b128, b129, b12a, b12b, b12c, b12d, b12e, b12f;
    float f130;
    Vec3 v134;
    float f140, f144, f148;
    Vec3 v14c;
    float f158, f15c, f160;
    SubC sub164;             // +0x164
    bool b178, b179, b17a, b17b;
    uint32_t pad17c;
    SubA sub180;             // +0x180
    FloatVector vec194;
    SubD sub1a8;             // +0x1a8
    float f1bc, f1c0, f1c4, f1c8, f1cc, f1d0, f1d4;
    Vec2 v1d8;
    uint64_t q1e0, q1e8, q1f0;
    SubF sub1f8;             // +0x1f8
    Vec3 v22c;
    SubG sub238;             // +0x238
    SubH sub254;             // +0x254
};

// Scalar writers: the value is a by-value parameter whose address is passed on.
inline void PutU32(IStream* s, uint32_t v) { WriteUint32(s, &v, 1, 0); }
inline void PutF32(IStream* s, float v) { WriteUint32(s, (const uint32_t*)&v, 1, 0); }
inline void PutU16(IStream* s, uint16_t v) { WriteUint16(s, &v, 1, 0); }
inline void PutU64(IStream* s, uint64_t v) { WriteUint64(s, &v, 1, 0); }
inline void PutBool(IStream* s, bool v) { WriteBool8(s, &v, 1); }

// @ 0x00f52df0
void WriteSettings(IStream* s, const Settings* o)
{
    PutU32(s, o->mId);
    s->Write(&o->v0c, 8);
    PutF32(s, o->f14);
    s->Write(&o->v18, 8);
    s->Write(&o->v20, 8);
    const Vec3* p28 = &o->box28[0];
    s->Write(p28, 0xc);
    p28++;
    s->Write(p28, 0xc);
    s->Write(&o->v40, 8);
    const Vec3* p48 = &o->box48[0];
    s->Write(p48, 0xc);
    p48++;
    s->Write(p48, 0xc);
    PutF32(s, o->f60);
    WriteFloatVector(s, &o->vec64);
    PutF32(s, o->f78);
    PutU16(s, o->u7c);
    PutF32(s, o->f80);
    WriteFloatVector(s, &o->vec84);
    PutF32(s, o->f98);
    WriteFloatVector(s, &o->vec9c);
    PutF32(s, o->fb0);
    PutF32(s, o->fc8);
    PutF32(s, o->fcc);
    WriteFloatVector(s, &o->vecb4);
    WriteFloatVector(s, &o->vecf0);
    PutF32(s, o->f104);
    WriteSubA(s, &o->subd0);
    s->Write(&o->ve4, 0xc);
    WriteSubB(s, &o->sub108);
    PutBool(s, o->b128);
    PutBool(s, o->b129);
    PutBool(s, o->b12a);
    PutBool(s, o->b12b);
    PutBool(s, o->b12c);
    PutF32(s, o->f130);
    PutBool(s, o->b12d);
    PutBool(s, o->b12e);
    PutBool(s, o->b12f);
    s->Write(&o->v134, 0xc);
    PutF32(s, o->f140);
    PutF32(s, o->f144);
    PutF32(s, o->f148);
    s->Write(&o->v14c, 0xc);
    PutF32(s, o->f158);
    PutF32(s, o->f15c);
    PutF32(s, o->f160);
    WriteSubC(s, &o->sub164);
    PutBool(s, o->b178);
    PutBool(s, o->b179);
    PutBool(s, o->b17a);
    PutBool(s, o->b17b);
    WriteSubA(s, &o->sub180);
    WriteFloatVector(s, &o->vec194);
    WriteSubD(s, &o->sub1a8);
    PutF32(s, o->f1bc);
    PutF32(s, o->f1c0);
    PutF32(s, o->f1c4);
    PutF32(s, o->f1c8);
    PutF32(s, o->f1cc);
    PutF32(s, o->f1d0);
    PutF32(s, o->f1d4);
    s->Write(&o->v1d8, 8);
    PutU64(s, o->q1e0);
    PutU64(s, o->q1e8);
    PutU64(s, o->q1f0);
    WriteSubF(s, &o->sub1f8);
    s->Write(&o->v22c, 0xc);
    WriteSubG(s, &o->sub238);
    WriteSubH(s, &o->sub254);
}
