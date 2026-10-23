// Slice s00f57590 -- SPEngine/SPAppCloudDescription.obj (cloud description + cloud command state).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

struct Vec3 { float x, y, z; };

extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);

namespace SP {
template <class T> struct SimpleVector {                       // eastl::vector<T, sp_vector_allocator>
    T*       mpBegin;
    T*       mpEnd;
    T*       mpCapacity;
    uint32_t mAllocator[2];

    void operator=(const SimpleVector& src);                    // 0x0050d4e0
    void DoInsertValue(T* pos, const T& value);                 // 0x00a87d20
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            *mpEnd++ = value;
        else
            DoInsertValue(mpEnd, value);
    }
    void clear() { mpEnd = mpBegin; }
};
}  // namespace SP

namespace EA {
namespace ArgScript {

#define PV(n) virtual void pv##n();
class cIParser { public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34)
    virtual void pv35(void* obj);
    PV(36) PV(37)
    virtual float GetFloat(const char* text);                   // +0x98
    PV(39) PV(40) PV(41) PV(42) PV(43)
    virtual Vec3 GetVector2(const char* text);                  // +0xb0
};
#undef PV

class cArguments { public:
    const char** MainArguments(int* count, int minCount, int maxCount);                     // 0x00838020
    const char** MainArguments(int count);                                                  // 0x00838320
    const char** OptionArguments(const char* name, int count);                              // 0x00838330
    const char** OptionArguments(const char* name, int* count, int minCount, int maxCount); // 0x00838130
    bool         HasFlag(const char* flag);                                                 // 0x008380b0
    const char*  operator[](int index);                                                     // 0x00837f20
};

}  // namespace ArgScript
}  // namespace EA

// ---------------------------------------------------------------------------
// cCloudDescription -- the 0x268-byte description block.
// ---------------------------------------------------------------------------
struct SubD0  { uint32_t w[5]; void AssignFrom(const SubD0& s); };    // 0x006f50f0
struct Sub164 { uint32_t w[5]; void AssignFrom(const Sub164& s); };   // 0x00a9a310
struct Sub180 { uint32_t w[5]; void AssignFrom(const Sub180& s); };   // 0x006f50f0
struct Sub1a8 { uint32_t w[5]; void AssignFrom(const Sub1a8& s); };   // 0x00a87920
struct Sub254 { uint32_t w[5]; void AssignFrom(const Sub254& s); };   // 0x00a9a500

struct cCloudDescription {
    void*    mVtbl;                 // +0x000
    void*    mParser;               // +0x004
    uint32_t m08;                   // +0x008
    float    f0c, f10, f14, f18, f1c, f20, f24;      // +0x00c .. +0x027
    float    f28, f2c, f30, f34, f38, f3c;           // +0x028 .. +0x03f
    float    f40, f44, f48, f4c, f50, f54, f58, f5c, f60;  // +0x040 .. +0x063
    SP::SimpleVector<float> v64;    // +0x064
    float    f78;                   // +0x078
    uint16_t w7c;                   // +0x07c
    float    f80;                   // +0x080
    SP::SimpleVector<float> v84;    // +0x084
    float    f98;                   // +0x098
    SP::SimpleVector<float> v9c;    // +0x09c
    float    fb0;                   // +0x0b0
    SP::SimpleVector<float> vb4;    // +0x0b4
    float    fc8;                   // +0x0c8
    float    fcc;                   // +0x0cc
    SubD0    d0;                    // +0x0d0
    float    fe4, fe8, fec;         // +0x0e4 .. +0x0ec
    SP::SimpleVector<float> vf0;    // +0x0f0
    float    f104;                  // +0x104
    uint32_t blob108[8];            // +0x108
    uint8_t  b128[8];               // +0x128
    float    f130[13];              // +0x130 .. +0x15f
    Sub164   s164;                  // +0x164
    uint8_t  b178[5];               // +0x178
    Sub180   s180;                  // +0x180
    SP::SimpleVector<float> v194;   // +0x194
    Sub1a8   s1a8;                  // +0x1a8
    float    f1bc[9];               // +0x1bc .. +0x1df
    uint32_t a1e0[6];               // +0x1e0 .. +0x1f7
    uint32_t a1f8[7];               // +0x1f8 .. +0x213
    SP::SimpleVector<float> v214;   // +0x214
    uint8_t  b228;                  // +0x228
    float    f22c;                  // +0x22c
    float    f230;                  // +0x230
    float    f234;                  // +0x234
    SP::SimpleVector<float> v238;   // +0x238
    float    f24c;                  // +0x24c
    float    f250;                  // +0x250
    Sub254   s254;                  // +0x254

    cCloudDescription();                                    // 0x00f53590
    ~cCloudDescription();                                   // 0x00f53420
    cCloudDescription& operator=(const cCloudDescription& src);
};

// ---------------------------------------------------------------------------
// Archive reader used by ReadDescription (00f57c50).
// ---------------------------------------------------------------------------
struct Archive {
    virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3();
    virtual void r4(); virtual void r5(); virtual void r6(); virtual void r7();
    virtual void r8(); virtual void r9(); virtual void r10(); virtual void r11();
    virtual void Read(void* dst, int size);                     // vtable +0x30
};

void __cdecl ReadInt32 (Archive* ar, void* out, int count, int flags);  // 0x0093a780
void __cdecl ReadByte  (Archive* ar, void* out, int count);             // 0x0093a6c0
void __cdecl ReadU32a  (Archive* ar, void* out, int count, int flags);  // 0x0093a700
void __cdecl ReadU32b  (Archive* ar, void* out, int count, int flags);  // 0x0093a800
void __cdecl ReadVecF  (Archive* ar, void* v);                          // 0x007d27d0
void __cdecl ReadSubA  (Archive* ar, void* v);                          // 0x007ed920
void __cdecl ReadSubB  (Archive* ar, void* v);                          // 0x00a9a870
void __cdecl ReadSubC  (Archive* ar, void* v);                          // 0x00a87f50
void __cdecl ReadBlob  (Archive* ar, void* v);                          // 0x00a85b00
void __cdecl ReadSubD  (Archive* ar, void* v);                          // 0x00a7b9a0
void __cdecl ReadSubE  (Archive* ar, void* v);                          // 0x00a7ba10
void __cdecl ReadSubF  (Archive* ar, void* v);                          // 0x00a9a8d0

// ---------------------------------------------------------------------------
// cCloudCmdState -- the shared cloud command "state" (command +0xc points here).
// ---------------------------------------------------------------------------
struct CmdSink3;
struct CmdSink2;

struct CmdSink {                                    // object returned by mOwner->slot8
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(unsigned char a, void* b);              // +0x10
    virtual CmdSink3* v5();                                 // +0x14
    virtual char v6(void* a, void* b, void* c);             // +0x18
    virtual void v7(int a);                                 // +0x1c
    virtual void v8();                                      // +0x20
    virtual void v9(int a, int b);                          // +0x24
    virtual void v10();                                     // +0x28
    virtual char v11(void* a, void* b, void* c);            // +0x2c
    virtual void v12(int a);                                // +0x30
    virtual void v13();                                     // +0x34
    virtual void v14(int a, int b);                         // +0x38
};

struct CmdSink2 {
    virtual void q0(); virtual void q1(); virtual void q2(); virtual void q3(); virtual void q4();
    virtual CmdSink3* q5();                                 // +0x14
};

struct CmdSink3 {
    virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3();
    virtual void r4(); virtual void r5(); virtual void r6(); virtual void r7(); virtual void r8();
    virtual char r9(int a, int b, int c);                   // +0x24
};

struct CmdOwner {
    virtual void o0(); virtual void o1(); virtual void o2(); virtual void o3();
    virtual void o4(); virtual void o5(); virtual void o6(); virtual void o7();
    virtual CmdSink*  o8();                                 // +0x20
    virtual void o9(); virtual void o10(); virtual void o11();
    virtual CmdSink2* o12();                                // +0x30
};

struct cCloudCmdState {
    char     pad00[0xc];
    uint8_t  b0c;                   // +0x0c
    char     pad0d;
    uint8_t  b0e;                   // +0x0e
    char     pad0f[0x1c - 0x0f];
    char*    p1c;                   // +0x1c
    char     pad20[0x28 - 0x20];
    CmdOwner* mOwner;               // +0x28
    char     pad2c[0xcc - 0x2c];
    uint32_t fcc, fd0, fd4;         // +0xcc, +0xd0, +0xd4
    char     padD8[0x138 - 0xd8];
    uint32_t f138, f13c, f140;      // +0x138, +0x13c, +0x140
    char     pad144[0x180 - 0x144];
    int      i180;                  // +0x180
    char     pad184[0x1d8 - 0x184];
    int      i1d8;                  // +0x1d8
    int      i1dc;                  // +0x1dc
    char     pad1e0[0x230 - 0x1e0];
    int      i230;                  // +0x230
    int      i234;                  // +0x234
    char     b238[4];               // +0x238
    uint8_t  b23c;                  // +0x23c

    bool Process(int mode, int* args, int argc);    // 0x00f58240
    void SetEnabled(char flag);                     // 0x00f58520
};

// ---------------------------------------------------------------------------
// cCloudEffect -- the "cloud" ArgScript command object (0x2c8 bytes).
// ---------------------------------------------------------------------------
struct cEffectsParser {
    const char** GetInheritedDescription(const char** argv, int count, int type);  // 0x00a6f090
};

struct EaString {
    const char* mpBegin;            // +0x00
    const char* mpEnd;              // +0x04
    void*       mpCapacity;         // +0x08
    uint32_t    mPad;               // +0x0c
    void assign(const char* first, const char* last);       // 0x00454cb0
};

struct cCloudEffect {
    char     pad00[0x04];
    EA::ArgScript::cIParser* mParser;   // +0x04
    char     pad08[0x30 - 0x08];
    cEffectsParser* mOwner;             // +0x30
    char     pad34[0x40 - 0x34];
    cCloudDescription mCmd;             // +0x40
    char     pad2a8[0x2b0 - 0x2a8];
    EaString mStr;                      // +0x2b0
    uint8_t  b2c0;                      // +0x2c0
    uint8_t  b2c1;                      // +0x2c1

    void Execute(EA::ArgScript::cArguments& args);   // 0x00f57ba0
};

// ---------------------------------------------------------------------------
// cCloudSurfaceCommand -- the "surface" cloud command.
// ---------------------------------------------------------------------------
struct SurfaceInfo {
    uint32_t m00;                                       // +0x00
    uint32_t m04, m08, m0c, m10, m14, m18, m1c;         // +0x04 .. +0x1f
    uint32_t m20, m24, m28, m2c, m30, m34, m38, m3c;    // +0x20 .. +0x3f
    uint32_t m40, m44, m48, m4c, m50, m54;              // +0x40 .. +0x57
};

struct CloudBigState {
    char     pad00[0x10];
    uint32_t mFlags;                                    // +0x10
    char     pad14[0x1b0 - 0x14];
    SP::SimpleVector<SurfaceInfo> mSurfaces;            // +0x1b0
    char     pad1c4[0x270 - 0x1c4];
    void*    mParser270;                                // +0x270
};

void __cdecl ParseSurfaceOptions(const char* name, EA::ArgScript::cArguments* args,
                                 void* out, void* parser);           // 0x00a7d280

struct cCloudSurfaceCommand {
    char     pad00[0x0c];
    CloudBigState* mState;                              // +0x0c
    void Execute(EA::ArgScript::cArguments& args);      // 0x00f57a30
};

// ===========================================================================
// Function bodies.
// ===========================================================================

// @ 0x00f57590
cCloudDescription& cCloudDescription::operator=(const cCloudDescription& src)
{
    m08 = src.m08;
    f0c = src.f0c;
    f10 = src.f10;
    f14 = src.f14;
    f18 = src.f18;
    f1c = src.f1c;
    f20 = src.f20;
    f24 = src.f24;
    f34 = src.f34;
    f38 = src.f38;
    f3c = src.f3c;
    f28 = src.f28;
    f2c = src.f2c;
    f30 = src.f30;
    f40 = src.f40;
    f44 = src.f44;
    f54 = src.f54;
    f58 = src.f58;
    f5c = src.f5c;
    f48 = src.f48;
    f4c = src.f4c;
    f50 = src.f50;
    f60 = src.f60;
    v64 = src.v64;
    f78 = src.f78;
    w7c = src.w7c;
    f80 = src.f80;
    v84 = src.v84;
    f98 = src.f98;
    v9c = src.v9c;
    fb0 = src.fb0;
    vb4 = src.vb4;
    fc8 = src.fc8;
    fcc = src.fcc;
    d0.AssignFrom(src.d0);
    fe4 = src.fe4;
    fe8 = src.fe8;
    fec = src.fec;
    vf0 = src.vf0;
    f104 = src.f104;
    for (int i = 0; i < 8; ++i)  blob108[i] = src.blob108[i];
    for (int i = 0; i < 8; ++i)  b128[i] = src.b128[i];
    for (int i = 0; i < 13; ++i) f130[i] = src.f130[i];
    s164.AssignFrom(src.s164);
    for (int i = 0; i < 5; ++i)  b178[i] = src.b178[i];
    s180.AssignFrom(src.s180);
    v194 = src.v194;
    s1a8.AssignFrom(src.s1a8);
    for (int i = 0; i < 9; ++i)  f1bc[i] = src.f1bc[i];
    for (int i = 0; i < 6; ++i)  a1e0[i] = src.a1e0[i];
    for (int i = 0; i < 7; ++i)  a1f8[i] = src.a1f8[i];
    v214 = src.v214;
    b228 = src.b228;
    f22c = src.f22c;
    f230 = src.f230;
    f234 = src.f234;
    v238 = src.v238;
    f24c = src.f24c;
    f250 = src.f250;
    s254.AssignFrom(src.s254);
    return *this;
}

// @ 0x00f57a30
void cCloudSurfaceCommand::Execute(EA::ArgScript::cArguments& args)
{
    const char** argv = args.MainArguments(1);

    SurfaceInfo info;
    info.m00 = 0;
    info.m04 = 0;
    info.m08 = 0;
    info.m0c = 0xffffffff;
    info.m10 = 0xffffffff;
    info.m14 = 0x3f800000;
    info.m18 = 0x3f800000;
    info.m1c = 0;
    info.m20 = 0;
    info.m24 = 0;
    info.m28 = 0x3f800000;
    info.m2c = 0;
    info.m30 = 0;
    info.m34 = 0;
    info.m38 = 0xce6e6b28;
    info.m3c = 0xffffffff;
    info.m40 = 0xffffffff;
    info.m44 = 0;
    info.m48 = 0;
    info.m4c = 0;

    if (args.HasFlag("reset"))
        mState->mSurfaces.clear();

    ParseSurfaceOptions(argv[0], &args, (char*)&info + 4, mState->mParser270);
    mState->mSurfaces.push_back(info);
    mState->mFlags |= 0x1000;
}

// @ 0x00f57ba0
void cCloudEffect::Execute(EA::ArgScript::cArguments& args)
{
    int count;
    const char** argv = args.MainArguments(&count, 1, 3);

    const char* p = argv[0];
    while (*p) ++p;
    mStr.assign(argv[0], p);

    cCloudDescription tmp;
    mCmd = tmp;
    tmp.~cCloudDescription();

    b2c0 = 0;
    b2c1 = 0;
    if (count > 1) {
        const char* inh = (const char*)mOwner->GetInheritedDescription(argv, count, 0x2b);
        if (inh)
            mCmd = *(const cCloudDescription*)inh;
    }
    mParser->pv35(this);
}

// @ 0x00f57c50
void ReadDescription(Archive* ar, int /*version*/, cCloudDescription* desc)
{
    int tmp;
    ReadInt32(ar, &tmp, 1, 0);
    desc->m08 = (uint32_t)tmp;

    ar->Read(&desc->f0c, 8);
    ReadInt32(ar, &desc->f14, 1, 0);
    ar->Read(&desc->f18, 8);
    ar->Read(&desc->f20, 8);
    ar->Read(&desc->f28, 0xc);
    ar->Read(&desc->f34, 0xc);
    ar->Read(&desc->f40, 8);
    ar->Read(&desc->f48, 0xc);
    ar->Read(&desc->f54, 0xc);
    ReadInt32(ar, &desc->f60, 1, 0);
    ReadVecF(ar, &desc->v64);
    ReadInt32(ar, &desc->f78, 1, 0);
    ReadU32a(ar, &desc->w7c, 1, 0);
    ReadInt32(ar, &desc->f80, 1, 0);
    ReadVecF(ar, &desc->v84);
    ReadInt32(ar, &desc->f98, 1, 0);
    ReadVecF(ar, &desc->v9c);
    ReadInt32(ar, &desc->fb0, 1, 0);
    ReadInt32(ar, &desc->fc8, 1, 0);
    ReadInt32(ar, &desc->fcc, 1, 0);
    ReadVecF(ar, &desc->vb4);
    ReadVecF(ar, &desc->vf0);
    ReadInt32(ar, &desc->f104, 1, 0);
    ReadSubA(ar, &desc->d0);
    ar->Read(&desc->fe4, 0xc);
    ReadBlob(ar, desc->blob108);
    ReadByte(ar, &desc->b128[0], 1);
    ReadByte(ar, &desc->b128[1], 1);
    ReadByte(ar, &desc->b128[2], 1);
    ReadByte(ar, &desc->b128[3], 1);
    ReadByte(ar, &desc->b128[4], 1);
    ReadByte(ar, &desc->b128[5], 1);
    ReadByte(ar, &desc->b128[6], 1);
    ReadByte(ar, &desc->b128[7], 1);
    ReadInt32(ar, &desc->f130[0], 1, 0);
    ar->Read(&desc->f130[1], 0xc);
    ReadInt32(ar, &desc->f130[4], 1, 0);
    ReadInt32(ar, &desc->f130[5], 1, 0);
    ReadInt32(ar, &desc->f130[6], 1, 0);
    ar->Read(&desc->f130[7], 0xc);
    ReadInt32(ar, &desc->f130[10], 1, 0);
    ReadInt32(ar, &desc->f130[11], 1, 0);
    ReadInt32(ar, &desc->f130[12], 1, 0);
    ReadSubB(ar, &desc->s164);
    ReadByte(ar, &desc->b178[0], 1);
    ReadByte(ar, &desc->b178[1], 1);
    ReadByte(ar, &desc->b178[2], 1);
    ReadByte(ar, &desc->b178[3], 1);
    ReadSubA(ar, &desc->s180);
    ReadVecF(ar, &desc->v194);
    ReadSubC(ar, &desc->s1a8);
    ReadInt32(ar, &desc->f1bc[0], 1, 0);
    ReadInt32(ar, &desc->f1bc[1], 1, 0);
    ReadInt32(ar, &desc->f1bc[2], 1, 0);
    ReadInt32(ar, &desc->f1bc[3], 1, 0);
    ReadInt32(ar, &desc->f1bc[4], 1, 0);
    ReadInt32(ar, &desc->f1bc[5], 1, 0);
    ReadInt32(ar, &desc->f1bc[6], 1, 0);
    ar->Read(&desc->f1bc[7], 8);
    ReadU32b(ar, &desc->a1e0[0], 1, 0);
    ReadU32b(ar, &desc->a1e0[2], 1, 0);
    ReadU32b(ar, &desc->a1e0[4], 1, 0);
    ReadSubD(ar, &desc->a1f8[0]);
    ar->Read(&desc->a1f8[4], 0xc);
    ReadSubE(ar, &desc->v238);
    ReadSubF(ar, &desc->s254);
}

// @ 0x00f58120
struct CloudAdvance {
    char  pad00[0x08];
    float f08;                      // +0x08
    float f0c;                      // +0x0c
    float f10, f14, f18;            // +0x10 .. +0x18
    float f1c, f20, f24;            // +0x1c .. +0x24
};

bool __cdecl AdvanceCloud(CloudAdvance* o, float dt, char* p3, char* p4)
{
    float nv = dt + o->f08;
    o->f08 = nv;
    if (o->f0c <= nv)
        return 0;

    float f4 = o->f20;
    float f1 = o->f24;
    float f2 = o->f1c;

    float f6 = *(float*)(p4 + 0x70) * dt + f4;
    float f7 = f1 + *(float*)(p4 + 0x74) * dt;
    float f5 = f2 + *(float*)(p4 + 0x6c) * dt;
    o->f20 = f6;
    o->f24 = f7;
    o->f1c = f5;

    float half = dt * 0.5f;
    float damp = 1.0f - *(float*)(p3 + 0x158) * dt;

    f5 = f5 * damp;
    o->f1c = f5;
    f6 = f6 * damp;
    o->f20 = f6;
    f7 = f7 * damp;
    o->f24 = f7;

    o->f10 = o->f10 + (f5 + f2) * half;
    o->f14 = o->f14 + (f6 + f4) * half;
    o->f18 = o->f18 + (f7 + f1) * half;
    return 1;
}

// @ 0x00f58230
extern int DAT_015b0c00[];          // 0x015b0c00

void __cdecl SetCloudGlobal(int index, int value)
{
    DAT_015b0c00[index] = value;
}

// @ 0x00f58240
bool cCloudCmdState::Process(int mode, int* args, int argc)
{
    if (mode == 0) {
        if (argc > 1 && args[1] != (int)(uint8_t)p1c[0x129])
            return 1;
        int v = args[0];
        if (i1d8 == v && i1dc == (v >> 31))
            return 1;
        i1d8 = v;
        i1dc = v >> 31;
        if (i230 < 0)
            return 1;

        CmdSink* p = mOwner->o8();
        p->v12(i230);

        uint32_t local[8];
        memcpy(local, p1c + 0x108, 0x20);
        ((uint8_t*)local)[8] = 9;
        if (((uint8_t*)local)[9] == 0x0f) {
            CmdSink2* q = mOwner->o12();
            CmdSink3* r = q->q5();
            ((uint8_t*)local)[8] = (uint8_t)r->r9((int)local[6], (int)local[7], 9);
        }

        char* arg = ((char*)this - 8) ? ((char*)this - 4) : 0;
        if (p->v11(arg, local, &i230)) {
            b23c = ((uint8_t*)local)[8];
            p->v4(b23c, b238);
            if (!b0c)
                return 1;
            if (!b0e)
                return 1;
            p->v14(i230, 1);
            return 1;
        }
        i230 = -1;
        return 1;
    }
    if (mode == 1) {
        if (argc > 1 && args[1] != (int)(uint8_t)p1c[0x129])
            return 1;
        int v = args[0];
        if (i1d8 == v && i1dc == (v >> 31))
            return 1;
        i1d8 = v;
        i1dc = v >> 31;
        if (i234 < 0)
            return 1;

        CmdSink* p = mOwner->o8();
        p->v7(i234);

        uint32_t local[8];
        memcpy(local, p1c + 0x108, 0x20);
        ((uint8_t*)local)[8] = 0;
        if (((uint8_t*)local)[9] == 0x0f) {
            CmdSink2* q = mOwner->o12();
            CmdSink3* r = q->q5();
            ((uint8_t*)local)[8] = (uint8_t)r->r9((int)local[0], (int)local[1], 0);
        }

        if (p->v6((char*)this - 8, local, &i234)) {
            b23c = ((uint8_t*)local)[8];
            p->v4(b23c, b238);
            if (!b0c)
                return 1;
            if (!b0e)
                return 1;
            p->v9(i234, 1);
            return 1;
        }
        i234 = -1;
        return 1;
    }
    if (mode == 2) {
        i180 = args[0];
        return 1;
    }
    return 0;
}

// @ 0x00f58520
void cCloudCmdState::SetEnabled(char flag)
{
    b0e = (uint8_t)flag;
    if (flag) {
        f138 = fcc;
        f13c = fd0;
        f140 = fd4;
    }
    if (b0c) {
        if (i234 >= 0) {
            CmdSink* p = mOwner->o8();
            p->v9(i234, b0e);
            return;
        }
        if (i230 >= 0) {
            CmdSink* p = mOwner->o8();
            p->v14(i230, b0e);
        }
    }
}
