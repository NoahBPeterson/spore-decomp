// Slice s00a6f110 (cl2 #179): EA::Swarm::cEffectsParser::ParseDescRecOptions (0x00a6f110, 2075 bytes).
//
// Parses the optional arguments of one visual-effect component description record
// (offset, rotate*, scale, lod/lodRange, emitScale/sizeScale/alphaScale, prob, timeScale,
// flags, "flag" bits) into a cDescriptionRec.  Retail layouts recovered from the asm:
//   cEffectsParser: +0x14 mParser (cIParser*, vtable 0x94 ParseBool, 0x98 ParseFloat, 0x9c ParseInt,
//                   0xa0 ParseUInt/byte, 0xa8 ParseVector3 (sret))
//   cDescriptionRec: +4 flags, +8 cTransform (u16 flags, u16 count, pos +0xc, scale +0x18),
//                   +0x40/+0x41 LOD begin/end, +0x44 vector<cLODScales>, +0x70/+0x74 app flags,
//                   +0x7a selection chance, +0x7c time scale.
#include "types.h"
#include <xmmintrin.h>

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

inline void* operator new(unsigned int, void* p) { return p; }

extern "C" void op_del_arr(void* p);   // 0xf47380 operator_delete__

struct Vec3 { float x, y, z; };

// ---- ArgScript -----------------------------------------------------------------
struct cArguments {
    int* OptionArguments(const char* name, int count);                              // 0x838330 ret 8
    int* OptionArguments(const char* name, int* outCount, int minCount, int maxCount); // 0x838130 ret 0x10
    bool HasFlag(const char* name);                                                  // 0x8380b0 ret 4
};

// ---- simple float vector (SP::SimpleVector<float>) ------------------------------------
struct FVec {
    float* b; float* e; float* c;
    void DoInsertValue(float* pos, const float& v);      // 0x455660 thiscall ret 8
    void push_back(const float& v)
    {
        if (e < c) { new (e) float(v); ++e; }
        else DoInsertValue(e, v);
    }
    ~FVec() { if (b && ((int*)b)[-1]) op_del_arr(b); }
};

// ---- description record ---------------------------------------------------------------
struct LodScale { float emit, size, alpha; };
struct LodVec {
    LodScale* b; LodScale* e; LodScale* c;
    void resize(int n);                                  // 0xa6f010 thiscall ret 4
};
struct cTransform {
    u16 flags;
    u16 count;
    Vec3 pos;                                            // +0xc in the record
    float scale;                                         // +0x18
    void RotateZ(float a);                               // 0x7d1ac0 ret 4
    void RotateY(float a);                               // 0x6b9050 ret 4 (MatX::Rotate)
    void PreRotateX(float a);                            // 0x5a2d90 ret 4
};
struct DescRec {
    int type;
    u32 flags;                                           // +4
    cTransform xf;                                       // +8
    char pad[0x40 - 8 - sizeof(cTransform)];
    u8 lodBegin;                                         // +0x40
    u8 lodEnd;                                           // +0x41
    char pad1[2];
    LodVec lod;                                          // +0x44
    char pad2[0x70 - 0x50];
    u32 appFlags;                                        // +0x70
    u32 appFlagsMask;                                    // +0x74
    char pad3[2];
    u16 chance;                                          // +0x7a
    float timeScale;                                     // +0x7c
};

extern float g_degToRad;                                 // 0x1676aa4

template <class R> inline R PV0(void* o, int off, int a) { return ((R (__thiscall *)(void*, int))(*(void***)o)[off / 4])(o, a); }
template <class R> inline R PV1(void* o, int off, void* ret, int a) { return ((R (__thiscall *)(void*, void*, int))(*(void***)o)[off / 4])(o, ret, a); }

static inline const int& imax(const int& a, const int& b) { return (a < b) ? b : a; }

struct cEffectsParser {
    char pad[0x14];
    void* mParser;                                       // +0x14

    float ParseFloat(int tok) { return PV0<float>(mParser, 0x98, tok); }
    u8    ParseByte(int tok) { return PV0<u8>(mParser, 0xa0, tok); }
    int   ParseInt(int tok) { return PV0<int>(mParser, 0x9c, tok); }
    bool  ParseBool(int tok) { return PV0<bool>(mParser, 0x94, tok); }

    // @ 0x00a6f110
    void ParseDescRecOptions(cArguments* args, DescRec* rec);
};

void cEffectsParser::ParseDescRecOptions(cArguments* args, DescRec* rec)
{
    int* p = args->OptionArguments("offset", 1);
    if (p) {
        Vec3 tmp;
        Vec3* v = (Vec3*)PV1<Vec3*>(mParser, 0xa8, &tmp, p[0]);
        float vy = v->y, vz = v->z, vx = v->x;
        rec->xf.pos.y = vy + rec->xf.pos.y;
        rec->xf.pos.z = vz + rec->xf.pos.z;
        rec->xf.pos.x = vx + rec->xf.pos.x;
        rec->xf.flags |= 4;
        rec->xf.count += 1;
    }

    p = args->OptionArguments("rotateZ", 1);
    if (p) rec->xf.RotateZ(ParseFloat(p[0]) * g_degToRad);
    p = args->OptionArguments("rotateY", 1);
    if (p) rec->xf.RotateY(ParseFloat(p[0]) * g_degToRad);
    p = args->OptionArguments("rotateX", 1);
    if (p) rec->xf.PreRotateX(ParseFloat(p[0]) * g_degToRad);

    p = args->OptionArguments("rotateXYZ", 3);
    if (p) {
        cTransform* xf = &rec->xf;
        xf->RotateZ(ParseFloat(p[2]) * g_degToRad);
        xf->RotateY(ParseFloat(p[1]) * g_degToRad);
        xf->PreRotateX(ParseFloat(p[0]) * g_degToRad);
    }
    p = args->OptionArguments("rotateZXY", 3);
    if (p) {
        cTransform* xf = &rec->xf;
        xf->RotateY(ParseFloat(p[2]) * g_degToRad);
        xf->PreRotateX(ParseFloat(p[1]) * g_degToRad);
        xf->RotateZ(ParseFloat(p[0]) * g_degToRad);
    }

    p = args->OptionArguments("scale", 1);
    if (p) {
        float s = ParseFloat(p[0]) * rec->xf.scale;
        rec->xf.flags |= 1;
        rec->xf.count += 1;
        rec->xf.scale = s;
    }

    int lodCount;
    p = args->OptionArguments("lodRange", 2);
    if (p) {
        rec->lodBegin = ParseByte(p[0]);
        rec->lodEnd = ParseByte(p[1]);
        lodCount = (int)rec->lodEnd - (int)rec->lodBegin + 1;
    } else {
        p = args->OptionArguments("lod", 1);
        if (p) {
            u8 b = ParseByte(p[0]);
            rec->lodBegin = b;
            rec->lodEnd = b + 1;
            lodCount = 2;
        } else {
            rec->lodBegin = 1;
            rec->lodEnd = 0xff;
            lodCount = 1;
        }
    }

    FVec emit = { 0, 0, 0 };
    FVec size = { 0, 0, 0 };
    FVec alpha = { 0, 0, 0 };
    int nLods = 0;
    int n;
    int* arr;

    arr = args->OptionArguments("emitScale", &n, 1, 0x7fffffff);
    if (arr) {
        nLods = imax(nLods, n);
        for (int i = 0; i < n; ++i) {
            float v = ParseFloat(arr[i]);
            emit.push_back(v);
        }
    }
    arr = args->OptionArguments("sizeScale", &n, 1, 0x7fffffff);
    if (arr) {
        nLods = imax(nLods, n);
        for (int i = 0; i < n; ++i) {
            float v = ParseFloat(arr[i]);
            size.push_back(v);
        }
    }
    arr = args->OptionArguments("alphaScale", &n, 1, 0x7fffffff);
    if (arr) {
        nLods = imax(nLods, n);
        for (int i = 0; i < n; ++i) {
            float v = ParseFloat(arr[i]);
            alpha.push_back(v);
        }
    }

    if (nLods != 0) {
        if (nLods != 1) nLods = lodCount;
        rec->lod.resize(nLods);
        int nE = (int)(emit.e - emit.b);
        int nS = (int)(size.e - size.b);
        int nA = (int)(alpha.e - alpha.b);
        float step = 0.0f;
        if (nLods > 1) step = 1.0f / (float)(nLods - 1);
        for (int i = 0; i < nLods; ++i) {
            float v;
            if (nE == 0) v = 1.0f;
            else if (nE == 1) v = emit.b[0];
            else if (nE == 2) v = (emit.b[1] - emit.b[0]) * (float)i * step + emit.b[0];
            else v = emit.b[i];
            rec->lod.b[i].emit = v;
            if (nS == 0) v = 1.0f;
            else if (nS == 1) v = size.b[0];
            else if (nS == 2) v = (size.b[1] - size.b[0]) * (float)i * step + size.b[0];
            else v = size.b[i];
            rec->lod.b[i].size = v;
            if (nA == 0) v = 1.0f;
            else if (nA == 1) v = alpha.b[0];
            else if (nA == 2) v = (alpha.b[1] - alpha.b[0]) * (float)i * step + alpha.b[0];
            else v = alpha.b[i];
            rec->lod.b[i].alpha = v;
        }
    }

    p = args->OptionArguments("prob", 1);
    if (p) {
        float f = ParseFloat(p[0]) * 65535.0f;
        rec->chance = (u16)_mm_cvtss_si32(_mm_set_ss(f));
    }
    p = args->OptionArguments("timeScale", 1);
    if (p) rec->timeScale = ParseFloat(p[0]);

    if (args->HasFlag("ignoreLength")) rec->flags |= 1;
    if (args->HasFlag("respectLength")) rec->flags &= ~1u;
    if (args->HasFlag("ignoreParams")) rec->flags |= 0x20;
    if (args->HasFlag("rigid")) rec->flags |= 0x40;

    p = args->OptionArguments("flag", 2);
    while (p) {
        int bit = ParseInt(p[0]);
        bool on = ParseBool(p[1]);
        u32 mask = 1u << bit;
        rec->appFlagsMask |= mask;
        if (on) rec->appFlags |= mask;
        p = args->OptionArguments("flag", 2);
    }
}
