// Slice s00f52df0: serialization (Write) of a large settings/description object into an IStream.
// Optimized module: /O2 /MD /Gy /EHsc /TP /arch:SSE.
//
// 0x00f52df0 (cdecl): writes every field of the object in order: scalars (float/uint through
// WriteUint32/WriteUint16/WriteUint64, bools through WriteBool8), small POD vectors straight
// through IStream::Write (vtable +0x38), and nested members through their own writers.
#include "types.h"

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
struct Vec3 { float x, y, z; };
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
