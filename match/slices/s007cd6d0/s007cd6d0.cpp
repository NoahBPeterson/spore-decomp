// Slice s007cd6d0: cConfigManager startup/configure + eastl pair copy helpers + draw/animation.
// Flags: /O2 /MD /Gy /EHsc /TP /GS-

#include "../s007ca950/s007ca950.h"

namespace EA { namespace ArgScript {
class cArguments { public: void** MainArguments(int n); void** OptionArguments(const char* pName, int n); };
}}
namespace EA { namespace CommandLine {
struct cCommandLine { int FindSwitch(const wchar_t* pName, int a, int b, int c); };
}}

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

typedef eastl::pair<uint64, EA::AutoRefCount<SP::cPropertyList> > PropPair;

// ---------------------------------------------------------------- eastl pair helpers
namespace eastl {
// @ 0x007cd9d0
template <>
PropPair* uninitialized_copy_ptr<PropPair>(const PropPair* first, const PropPair* last, PropPair* result) {
    PropPair* d = result;
    for (; first != last; ++first, ++d)
        ::new ((void*)d) PropPair(*first);
    return d;
}
// @ 0x007cde80
template <> template <>
PropPair* copy_backward_impl<0, std::random_access_iterator_tag>::do_copy<PropPair*, PropPair*>(PropPair* first, PropPair* last, PropPair* result) {
    while (last != first) {
        --last;
        --result;
        ((uint32*)result)[0] = ((const uint32*)last)[0];
        ((uint32*)result)[1] = ((const uint32*)last)[1];
        SP::cPropertyList* pNew = last->second.mpObject;
        _ReadWriteBarrier();
        SP::cPropertyList* pOld = result->second.mpObject;
        if (pNew != pOld) {
            if (pNew) pNew->AddRef();
            result->second.mpObject = pNew;
            if (pOld) pOld->Release();
        }
    }
    return result;
}
}  // namespace eastl

// ---------------------------------------------------------------- externals
extern "C" void* _sAppProperties;                                    // 0x15fd918
void __cdecl    FUN_008476b0(void*, void*);                          // 0x008476b0
void __cdecl    FUN_006bb1c0(const char*, unsigned, unsigned, const char*); // 0x006bb1c0
void* __cdecl   CheatManager();                                      // 0x0067de20
namespace EA { namespace Messaging { void* __cdecl GetServer(); } }  // 0x00883860

// External __thiscall methods, modelled as members of placeholder classes.
struct ExtConfig {
    void Reset();                          // 0x007ccc30
    void LoadOptionSetup();                // 0x007cd340
    void AddResolutionOption();            // 0x007cccc0
    void LoadResolutionOptions();          // 0x007cce50
    void ApplyAllOptions();                // 0x007c9680
    void GatherInformation();              // 0x007cb590
    int  GetIntProperty(unsigned);         // 0x006a2660
    void SetIntProperty(unsigned, int);    // 0x006a1880
};
struct ExtCommandBase { void Ctor(); };                              // 0x0083c800
struct ExtCheatManager { void Register(const char*, void*, int); };  // vtable slot 0x18
struct ExtRandom {
    double RandomDoubleUniform();                                    // 0x009360d0
};

// The "option" cheat object built by SetupParser: allocated with the EA
// allocator, base-constructed, then the derived vtable/owner are stored.
struct cCommandBase {
    int mPad[4];
    cCommandBase();
};
struct cOptionCheat : cCommandBase {
    int mParser;
    cOptionCheat(void* parser);
    static void* operator new(unsigned size, const char* name, int flags, unsigned debugFlags, const char* file, int line) {
        return ::operator new(size, name, flags, debugFlags, file, line);
    }
};
cOptionCheat::cOptionCheat(void* parser) : cCommandBase() {
    *(void**)this = (void*)0x14114c4;
    mParser = (int)parser;
}

struct cConfigManagerS {
    void Initialize();
    bool SetupParser(void* cmd, bool p3);
    void TryConfigure();
    bool Configure();
    void Unnamed960();
    void Unnamed990();
    bool Unnamed9C0();
    void UnnamedA70(float* v);
};

#define VTOBJ(p)      (*(void***)(p))
#define VTCALL0(p, s) ((void(__thiscall*)(void*))VTOBJ(p)[(s) / 4])

// ---------------------------------------------------------------- bespoke config startup
// @ 0x007cd6d0
void cConfigManagerS::Initialize()
{
    int* self = (int*)this;
    ((ExtConfig*)((char*)self + 0x20))->Reset();
    if (self[3] != 0) {                                              // +0x0c mFileParser
        ((ExtConfig*)self)->AddResolutionOption();
        ((ExtConfig*)self)->LoadResolutionOptions();
        VTCALL0((void*)self[3], 0x20)((void*)self[3]);
    } else {
        ((ExtConfig*)self)->LoadOptionSetup();
        ((ExtConfig*)self)->AddResolutionOption();
        ((ExtConfig*)self)->LoadResolutionOptions();
        FUN_008476b0((void*)self[4], (char*)self + 0x14);
    }
    char* pc = (char*)((void*(__thiscall*)(void*))VTOBJ((void*)self[4])[0x58 / 4])((void*)self[4]);
    if (((char*)self)[0x61] == 0 && *pc != 0)
        FUN_006bb1c0((const char*)0x1411ad8, 0x7d0, 1, 0);
    if (self[0xa8 / 4] >= 0) {
        int v = ((ExtConfig*)self[0xb0 / 4])->GetIntProperty(0x1a34e253u);
        int cur = self[0xa8 / 4];
        if (v > cur) ((ExtConfig*)self[0xb0 / 4])->SetIntProperty(0x1a34e253u, cur);
    }
    ((ExtConfig*)self)->ApplyAllOptions();
    if (!((char*)self)[0xac]) VTCALL0(self, 0x3c)(self);
    else                      VTCALL0(self, 0x40)(self);
}

// @ 0x007cd7a0
bool cConfigManagerS::SetupParser(void* cmd, bool param3)
{
    int* self = (int*)this;
    void* newProps = _sAppProperties;
    void* oldProps = (void*)self[0xb0 / 4];
    if (newProps != oldProps) {
        if (newProps) VTCALL0(newProps, 0x00)(newProps);
        self[0xb0 / 4] = (int)newProps;
        if (oldProps) VTCALL0(oldProps, 0x04)(oldProps);
    }
    if (((EA::CommandLine::cCommandLine*)cmd)->FindSwitch( L"safe", 0, 0, 0) != -1)
        ((char*)self)[0xac] = 1;
    if (((EA::CommandLine::cCommandLine*)cmd)->FindSwitch( L"showConfigAlerts", 0, 0, 0) != -1)
        ((char*)self)[0xad] = 1;
    ((char*)self)[0x60] = (char)param3;
    cOptionCheat* p = new ("App", 0, 0u, (const char*)0, 0) cOptionCheat(self);
    void* cm = CheatManager();
    ((ExtCheatManager*)cm)->Register("option", p, 0);
    ((ExtConfig*)self)->AddResolutionOption();
    ((ExtConfig*)self)->LoadResolutionOptions();
    return true;
}

// @ 0x007cd8b0
void cConfigManagerS::TryConfigure()
{
    int* self = (int*)this;
    void* fp = (void*)self[3];
    if (fp != 0) {
        if (((bool(__thiscall*)(void*))VTOBJ(fp)[0x28 / 4])(fp))
            Initialize();
    }
}

// @ 0x007cd8d0
bool cConfigManagerS::Configure()
{
    int* self = (int*)this;
    void* pl = (void*)self[4];
    if (pl != 0) {
        const char* v1 = ((char*)self)[0xac] ? "1" : "0";
        ((void(__thiscall*)(void*, const char*, const char*))VTOBJ(pl)[0x74 / 4])(pl, "safeMode", v1);
        const char* v2 = ((char*)self)[0xad] ? "1" : "0";
        pl = (void*)self[4];
        ((void(__thiscall*)(void*, const char*, const char*))VTOBJ(pl)[0x74 / 4])(pl, "showConfigAlerts", v2);
        ((ExtConfig*)((char*)self + 0x20))->GatherInformation();
        Initialize();
        return ((char*)self)[0x61] == 0;
    }
    ((ExtConfig*)self)->LoadOptionSetup();
    ((ExtConfig*)self)->AddResolutionOption();
    ((ExtConfig*)self)->LoadResolutionOptions();
    return true;
}

// @ 0x007cd960
void cConfigManagerS::Unnamed960()
{
    char* self = (char*)this;
    if (self[4] == 0) {
        void* s = EA::Messaging::GetServer();
        ((void(__thiscall*)(void*, char*, int))VTOBJ(s)[0x24 / 4])(s, self, *(int*)(self + 0x1c));
        self[4] = 1;
    }
}

// @ 0x007cd990
void cConfigManagerS::Unnamed990()
{
    char* self = (char*)this;
    if (self[4] != 0) {
        void* s = EA::Messaging::GetServer();
        ((void(__thiscall*)(void*, char*, int, int))VTOBJ(s)[0x2c / 4])(s, self, *(int*)(self + 0x1c), 0xffffd8f1);
        *(int*)(self + 0x1c) = 0;
        self[4] = 0;
    }
}

// @ 0x007cd9c0
bool cConfigManagerS::Unnamed9C0()
{
    int* p = *(int**)this;
    return *p == 0;
}

// @ 0x007cda70
void cConfigManagerS::UnnamedA70(float* v)
{
    unsigned char* self = (unsigned char*)this;
    float x = v[0] - *(float*)(self + 4);
    float y = v[1] - *(float*)(self + 8);
    float z = v[2] - *(float*)(self + 0xc);
    v[0] = x; v[1] = y; v[2] = z;
    float s = *(float*)(self + 0x10);
    if (s != 1.0f) {
        float inv = 1.0f / s;
        v[0] = x * inv; v[1] = y * inv; v[2] = z * inv;
    }
    if (self[0] & 2) {
        float a = v[0], b = v[1], c = v[2];
        v[0] = *(float*)(self + 0x1c) * c + *(float*)(self + 0x18) * b + *(float*)(self + 0x14) * a;
        v[1] = *(float*)(self + 0x28) * c + *(float*)(self + 0x24) * b + *(float*)(self + 0x20) * a;
        v[2] = *(float*)(self + 0x34) * c + *(float*)(self + 0x30) * b + *(float*)(self + 0x2c) * a;
    }
}

// @ 0x007cdb90
__declspec(noinline) double __cdecl cConfigManagerUnnamedB90(float* param_1)
{
    double lo = param_1[0];
    double hi = param_1[1];
    double v = ((ExtRandom*)0x16778dc)->RandomDoubleUniform() * (hi - lo) + lo;
    if (v >= hi) return hi;
    if (v < lo) return lo;
    return v;
}
// @ 0x007cdbe0
float* __cdecl cConfigManagerUnnamedBE0(float* param_1, void* param_2)
{
    float* dst = param_1;
    float* src = (float*)param_2;
    double lo, hi, v;

    lo = src[0]; hi = src[3];
    v = ((ExtRandom*)0x16778dc)->RandomDoubleUniform() * (hi - lo) + lo;
    if (v >= hi) v = hi;
    else if (v < lo) v = lo;
    dst[0] = (float)v;

    lo = src[1]; hi = src[4];
    v = ((ExtRandom*)0x16778dc)->RandomDoubleUniform() * (hi - lo) + lo;
    if (v >= hi) v = hi;
    else if (v < lo) v = lo;
    dst[1] = (float)v;

    lo = src[2]; hi = src[5];
    v = ((ExtRandom*)0x16778dc)->RandomDoubleUniform() * (hi - lo) + lo;
    if (v >= hi) v = hi;
    else if (v < lo) v = lo;
    dst[2] = (float)v;
    return dst;
}
// @ 0x007cdcd0
void UpdateFromGroundCoverConfig(void*) {}
// @ 0x007cdd80
void cConfigManagerUnnamedD80(void*) {}
// @ 0x007cddc0
void cConfigManagerUnnamedDC0(void*) {}
// @ 0x007cde30
void cConfigManagerUnnamedE30(void*) {}
// @ 0x007cdee0
void TransformVectorByMatrix(void*, float*) {}
// ---------------------------------------------------------------- draw/animation
struct Vec3f { float x, y, z; };

struct cAnimElemData {              // element payload
    unsigned int mask;              // +0x00
    char         pad04[0x20 - 4];
    float        scale;             // +0x20
};

struct cAnimElem {                  // 0x18-byte entry in the +0x1e4 vector
    void*         obj;              // +0x00
    cAnimElemData* data;            // +0x04
    int           flag;             // +0x08
    int           offset;           // +0x0c
    int           pad10[2];         // +0x10
};

// Grid/volume the animation position is interpolated in.
struct cAnimGrid {
    char          pad00[0xcc];
    Vec3f         base;             // +0xcc
    char          padD8[0x1b4 - 0xd8];
    void*         iface1;           // +0x1b4
    void*         iface2;           // +0x1b8
    char          pad1BC[1];        // +0x1bc
    unsigned char b1bd;             // +0x1bd
    unsigned char b1be;             // +0x1be
    char          pad1BF[1];        // +0x1bf
    Vec3f         lo;               // +0x1c0
    Vec3f         hi;               // +0x1cc
    char          pad1D8[0x1e4 - 0x1d8];
    cAnimElem*    vecBegin;         // +0x1e4
    cAnimElem*    vecEnd;           // +0x1e8
    char          pad1EC[0x1fc - 0x1ec];
    int           f1fc;             // +0x1fc
    char          pad200[0x210 - 0x200];
    unsigned char b210;             // +0x210
};

// Third argument: per-call flags/parameters.
struct cAnimInput {
    char          pad00[0x08];
    unsigned int  flags8;           // +0x08
    char          pad0C[0x64 - 0x0c];
    float         f64;              // +0x64
};

// The state object updated by UpdateFloatAnim.
struct cFloatAnim {
    char   pad00[0x08];
    float  time;                    // +0x08
    float  duration;                // +0x0c
    Vec3f  pos;                     // +0x10
    char   pad1C[0x18];             // +0x1c .. +0x33
    float  f34;                     // +0x34
    float  f38;                     // +0x38
    float  f3c;                     // +0x3c
    float  f40;                     // +0x40
};

// Out-of-line thiscall transforms on the two subobjects of cAnimGrid.
struct cAnimXformA { void Apply(float* v); };   // 0x007cda70
struct cAnimXformB { void Apply(float* v); };   // 0x007cdee0

typedef bool  (__thiscall* FnElem)(void*, void*, void*, void*, int, int, int);
typedef bool  (__thiscall* FnCheck)(void*, void*);
typedef float (__thiscall* FnGet)(void*, void*);
typedef void  (__thiscall* FnOut)(void*, void*, void*);

// @ 0x007cdff0
bool __cdecl UpdateFloatAnim(cFloatAnim* self, float dt, cAnimInput* in, cAnimGrid* grid)
{
    float t = self->time + dt;
    self->time = t;
    if (t >= self->duration)
        return false;

    Vec3f& pos = self->pos;
    float nx = (pos.x - grid->base.x - grid->lo.x) / (grid->hi.x - grid->lo.x);
    float ny = (pos.y - grid->base.y - grid->lo.y) / (grid->hi.y - grid->lo.y);
    float nz = (pos.z - grid->base.z - grid->lo.z) / (grid->hi.z - grid->lo.z);

    int ix = (int)nx; if (nx < (float)ix) --ix;
    int iy = (int)ny; if (ny < (float)iy) --iy;
    int iz = (int)nz; if (nz < (float)iz) --iz;

    if (ix != 0 || iy != 0 || iz != 0) {
        float fx = nx - (float)ix;
        float fy = ny - (float)iy;
        float fz = nz - (float)iz;

        float lx = grid->lo.x + (grid->hi.x - grid->lo.x) * fx;
        float ly = grid->lo.y + (grid->hi.y - grid->lo.y) * fy;
        float lz = grid->lo.z + (grid->hi.z - grid->lo.z) * fz;

        pos.x = grid->base.x + lx;
        pos.y = grid->base.y + ly;
        pos.z = grid->base.z + lz;
        // The original reuses this stack slot as the iface2 output buffer, so
        // its contents survive until that call.
        Vec3f interp = pos;
        bool  rangeStored = false;
        self->f34 = *(float*)0x1485720;

        if (grid->b210 != 0) {
            cAnimElem* e = grid->vecBegin;
            cAnimElem* end = grid->vecEnd;
            int base = grid->f1fc;
            while (e != end) {
                if ((e->data->mask & *(unsigned int*)0x153d634) != 0) {
                    int arg = (e->flag == 0) ? 0 : e->offset + base;
                    FnElem fn = (FnElem)(*(void***)e->obj)[0x10 / 4];
                    if (fn(e->obj, &pos, &pos, &lx, 0, arg, 0)) {
                        float scale = e->data->scale;
                        if (scale != *(float*)0x1485378) {
                            pos.x += scale * lx;
                            pos.y += scale * ly;
                            pos.z += scale * lz;
                        }
                        break;
                    }
                }
                ++e;
            }
        }

        if (((in->flags8 >> 5) & 1) != 0 && grid->iface1 != 0) {
            Vec3f v = pos;
            if (grid->b1bd != 0)
                ((cAnimXformB*)((char*)grid + 0x100))->Apply((float*)&v);
            else
                ((cAnimXformA*)((char*)grid + 0xc8))->Apply((float*)&v);

            FnCheck chk = (FnCheck)(*(void***)grid->iface1)[0x18 / 4];
            if (chk(grid->iface1, &v)) {
                FnGet get = (FnGet)(*(void***)grid->iface1)[0x20 / 4];
                v.z = get(grid->iface1, &v);
                float range[2] = { grid->lo.z, grid->hi.z };
                double r = cConfigManagerUnnamedB90(range);
                v.z = (float)(r + v.z);
                rangeStored = true;
                if (grid->b1bd != 0)
                    ((cAnimXformA*)((char*)grid + 0x100))->Apply((float*)&v);
                else
                    ((cAnimXformB*)((char*)grid + 0xc8))->Apply((float*)&v);
                pos = v;
            }
        }

        if (grid->iface2 != 0) {
            Vec3f v = pos;
            if (grid->b1be != 0)
                ((cAnimXformB*)((char*)grid + 0x100))->Apply((float*)&v);
            else
                ((cAnimXformA*)((char*)grid + 0xc8))->Apply((float*)&v);

            FnCheck chk = (FnCheck)(*(void***)grid->iface2)[0x18 / 4];
            if (chk(grid->iface2, &v)) {
                float out[4];
                if (rangeStored) {
                    out[0] = grid->lo.z;
                    out[1] = grid->hi.z;
                    out[2] = interp.z;
                } else {
                    out[0] = interp.x;
                    out[1] = interp.y;
                    out[2] = interp.z;
                }
                FnOut outfn = (FnOut)(*(void***)grid->iface2)[0x2c / 4];
                outfn(grid->iface2, out, &v);
                self->f38 = out[0];
                self->f3c = out[1];
                self->f40 = out[2];
                self->f34 = out[3] * self->f34;
            }
        }
    }
    return true;
}
