// Slice s00f585b0 -- EA::Swarm particle-field helpers.
//
//  0x00f585b0  cSwarmField::Generate(void* out)
//  0x00f58620  cSwarmField::AddNode(cListLink*)
//  0x00f58640  SnapListPoint(void* a, float t, const void* src, const void* owner)
//  0x00f58740  cSwarmField::Release()
//  0x00f58820  cSwarmField::Reset(int)
//  0x00f589e0  cSwarmField::SetObject(void*)
//  0x00f58a60  cSwarmField::Update(void* p, void* arg)
//  0x00f58b70  cSwarmField::SetPoint(float*)
//  0x00f58ed0  WarpPoint(void* state, const void* unused, Vec3* pt, Vec3* mul)

typedef unsigned char byte;
#include <math.h>

// ------------------------------------------------------------------ types
struct Vec3 {
    float x, y, z;
};

struct KeyDesc;

struct Vector2_s004d_f2d0 {
    float lo, hi;
};

namespace SP {
    float RandomInRange(const Vector2_s004d_f2d0& r);   // 0x004df2d0
}

class cRWState {
public:
    void Init(const KeyDesc*, const Vec3*, bool);       // 0x00a79430
};

extern "C" void __cdecl FUN_00a81a20(const float* in, float* out);  // basis from dir
extern "C" void __cdecl FUN_00a7f5a0(void* a1, void* a2, void* a3, int a4,
                                     float a5, void* a6, void* a7, void* a8,
                                     int a9, void* a10, int a11);
extern "C" void __cdecl FUN_00a79f60(void* a1, float a2, void* a3,
                                     const void* a4, const void* a5, void* a6);
extern "C" void __cdecl FUN_007cdbe0(void* out, const void* in);

// ------------------------------------------------------------- field class
struct cListLink {
    cListLink* prev;    // +0
    cListLink* next;    // +4
};

struct cSwarmField;

struct cSwarmField {
    void*           m_vtbl;            // 0x000
    char            m_pad04[0x0c - 0x04];
    byte            m_0c;              // 0x0c
    byte            m_0d;              // 0x0d
    byte            m_0e;              // 0x0e
    char            m_pad0f[0x16 - 0x0f];
    byte            m_16;              // 0x16
    char            m_pad17[0x18 - 0x17];
    cListLink       m_head;            // 0x18
    int             m_count;           // 0x20
    void*           m_owner;           // 0x24
    void*           m_sys;             // 0x28
    void*           m_2c;              // 0x2c
    void*           m_30;              // 0x30
    double          m_38;              // 0x38 (pad 0x34)
    byte            m_40;              // 0x40
    char            m_pad41[0x48 - 0x41];
    double          m_48;              // 0x48
    int             m_50;              // 0x50
    char            m_pad54[0x60 - 0x54];
    float           m_60;              // 0x60
    float           m_64;              // 0x64
    float           m_68;              // 0x68
    float           m_6c;              // 0x6c
    float           m_70;              // 0x70
    float           m_74;              // 0x74
    char            m_pad78[0x9c - 0x78];
    float           m_9c;              // 0x9c
    char            m_padA0[0xcc - 0xa0];
    int             m_cc;              // 0xcc
    int             m_d0;              // 0xd0
    int             m_d4;              // 0xd4
    int             m_d8;              // 0xd8
    int             m_dc;              // 0xdc
    float           m_e0;              // 0xe0
    float           m_e4, m_e8, m_ec;  // 0xe4
    float           m_f0, m_f4, m_f8;  // 0xf0
    float           m_fc, m_100, m_104;// 0xfc
    byte            m_108;             // 0x108
    char            m_pad109[0x10c - 0x109];
    float           m_10c;             // 0x10c
    float           m_110;             // 0x110
    float           m_114;             // 0x114
    float           m_118;             // 0x118
    float           m_11c;             // 0x11c
    float           m_120;             // 0x120
    float           m_124;             // 0x124
    float           m_128;             // 0x128
    float           m_12c;             // 0x12c
    float           m_130;             // 0x130
    float           m_134;             // 0x134
    float           m_138;             // 0x138
    float           m_13c;             // 0x13c
    int             m_140;             // 0x140
    char            m_pad144[0x14c - 0x144];
    unsigned short  m_14c;             // 0x14c
    char            m_pad14e[0x168 - 0x14e];
    float           m_168;             // 0x168
    char            m_pad16c[0x180 - 0x16c];
    Vec3*           m_vecBegin;        // 0x180
    Vec3*           m_vecEnd;          // 0x184
    char            m_pad188[0x194 - 0x188];
    float*          m_fltBegin;        // 0x194
    float*          m_fltEnd;          // 0x198
    float           m_19c;             // 0x19c
    char            m_pad1a0[0x1b0 - 0x1a0];
    void*           m_1b0;             // 0x1b0
    void*           m_1b4;             // 0x1b4
    void*           m_1b8;             // 0x1b8
    char            m_pad1bc[0x1c8 - 0x1bc];
    float           m_1c8, m_1cc, m_1d0, m_1d4, m_1d8, m_1dc;
    char            m_pad1e0[0x1ec - 0x1e0];
    char            m_1ec[0x204 - 0x1ec];
    int             m_204;             // 0x204
    char            m_pad208[0x228 - 0x208];
    cSwarmField*    m_228;             // 0x228
    char            m_pad22c[0x230 - 0x22c];
    int             m_230;             // 0x230
    int             m_234;             // 0x234
    char            m_pad238[0x240 - 0x238];
    char            m_240[4];          // 0x240
    byte            m_244;             // 0x244

    void Generate(void* out);
    void AddNode(cListLink* n);
    void Release();
    void Reset(int arg);
    void SetObject(void* obj);
    void Update(void* p, void* arg);
    void SetPoint(float* p);
};

typedef void (__cdecl *GenFn)(void*, void*, void*);

extern "C" GenFn g_FnGen[64];    // 0x016c9308
extern "C" GenFn g_FnGen2[64];   // 0x016c9388

// @ 0x00f585b0
void cSwarmField::Generate(void* out)
{
    if (*(int*)((char*)this + 0x28) != *(int*)((char*)this + 0x24)) {
        GenFn f = g_FnGen[m_244];
        f(this, out, m_240);
    }
    else {
        GenFn f = g_FnGen2[m_244];
        if (f != 0)
            f(this, out, m_240);
    }
    m_14c = (unsigned short)(m_14c + 1);
}

// @ 0x00f58620
void cSwarmField::AddNode(cListLink* n)
{
    cListLink* head = &m_head;
    n->next = head->next;
    n->prev = head;
    head->next = n;
    n->next->prev = n;
    m_count = m_count + 1;
}

// @ 0x00f58640
void __cdecl FUN_00f58640(void* a1, float t, void* a3, void* a4)
{
    char* src = (char*)a3;
    char* own = (char*)a4;
    void* list = own + 0x21c;
    float scale;
    float sx, sy, sz;
    float ox, oy, oz;
    Vec3  pos;
    Vec3  off;

    if (*(int*)(own + 0x21c) == *(int*)(own + 0x220))
        list = src + 0x254;

    void* p = a1 ? (void*)((char*)a1 + 8) : 0;

    scale = *(float*)(src + 0x40);
    sx = (*(float*)(src + 0x34) + *(float*)(src + 0x28)) * 0.5f;
    sy = (*(float*)(src + 0x38) + *(float*)(src + 0x2c)) * 0.5f;
    sz = (*(float*)(src + 0x3c) + *(float*)(src + 0x30)) * 0.5f;
    pos.x = scale * sx;
    pos.y = scale * sy;
    pos.z = scale * sz;

    ox = (*(float*)(src + 0x48) + *(float*)(src + 0x54)) * 0.5f;
    oy = (*(float*)(src + 0x58) + *(float*)(src + 0x4c)) * 0.5f;
    oz = (*(float*)(src + 0x5c) + *(float*)(src + 0x50)) * 0.5f;
    off.x = ox;
    off.y = oy;
    off.z = oz;

    FUN_00a79f60(p, t, list, &off, &pos, own + 0xd0);
}

// @ 0x00f58740
void cSwarmField::Release()
{
    if (m_0c != 0) {
        void* v = *(void**)this;
        (*(void (__thiscall**)(void*, int))((char*)v + 0x0c))(this, 1);
    }

    if (m_230 >= 0) {
        void* sys = m_sys;
        void* v = *(void**)sys;
        void* (__thiscall* f)(void*) = *(void* (__thiscall**)(void*))((char*)v + 0x20);
        void* r = f(sys);
        void* rv = *(void**)r;
        (*(void (__thiscall**)(void*, int))((char*)rv + 0x30))(r, m_230);
    }
    if (m_234 >= 0) {
        void* sys = m_sys;
        void* v = *(void**)sys;
        void* (__thiscall* f)(void*) = *(void* (__thiscall**)(void*))((char*)v + 0x20);
        void* r = f(sys);
        void* rv = *(void**)r;
        (*(void (__thiscall**)(void*, int))((char*)rv + 0x1c))(r, m_234);
    }

    if (m_1b0 != 0) {
        void* v = *(void**)m_1b0;
        (*(void (__thiscall**)(void*))((char*)v + 0x0c))(m_1b0);
        if (m_1b0 != 0) {
            void* o = m_1b0;
            m_1b0 = 0;
            void* ov = *(void**)o;
            (*(void (__thiscall**)(void*))((char*)ov + 0x04))(o);
        }
    }
    if (m_1b4 != 0) {
        void* v = *(void**)m_1b4;
        (*(void (__thiscall**)(void*))((char*)v + 0x0c))(m_1b4);
        if (m_1b4 != 0) {
            void* o = m_1b4;
            m_1b4 = 0;
            void* ov = *(void**)o;
            (*(void (__thiscall**)(void*))((char*)ov + 0x04))(o);
        }
    }
    if (m_1b8 != 0) {
        void* v = *(void**)m_1b8;
        (*(void (__thiscall**)(void*))((char*)v + 0x0c))(m_1b8);
        if (m_1b8 != 0) {
            void* o = m_1b8;
            m_1b8 = 0;
            void* ov = *(void**)o;
            (*(void (__thiscall**)(void*))((char*)ov + 0x04))(o);
        }
    }

    m_head.next = 0;
    m_count = 0;
    m_sys = 0;
}

// @ 0x00f58820
void cSwarmField::Reset(int arg)
{
    char* info = *(char**)((char*)this + 0x1c);

    if (arg == 0)
        goto reset;
    if (*(unsigned short*)(info + 0x7c) == 0)
        goto reset;
    if ((*(unsigned int*)(info + 8) >> 2) & 1)
        goto reset;
    if ((*(unsigned int*)(info + 8) >> 0x1c) & 1)
        goto reset;
    return;

reset:
    if (m_0c == 0 || m_0d != 0) {
        m_0d = 0;
        m_0c = 1;
    }
    m_48 = 0.0;
    m_38 = 0.0;
    *(int*)((char*)this + 0x138) = m_cc;
    *(int*)((char*)this + 0x13c) = m_d0;
    *(int*)((char*)this + 0x140) = m_d4;
    m_50 = 0;
    m_60 = 0.0f;
    m_64 = *(float*)(info + 0x134);
    m_68 = *(float*)(info + 0x138);
    m_6c = *(float*)(info + 0x13c);

    if ((*(unsigned int*)(info + 8) >> 0x13) & 1) {
        Vec3 v;
        unsigned int flags = *(unsigned int*)(info + 8);
        FUN_007cdbe0(&v, info + 0x28);
        ((cRWState*)((char*)this + 0x70))->Init((const KeyDesc*)(info + 0x1f8),
                                                &v, (bool)((flags >> 0x14) & 1));
    }

    info = *(char**)((char*)this + 0x1c);
    if (*(float*)(info + 0x18) < 0.0f) {
        if (*(float*)(info + 0x20) < 0.0f) {
            m_9c = 0.0f;
        }
        else {
            Vector2_s004d_f2d0 r;
            r.lo = *(float*)(info + 0x20);
            r.hi = *(float*)(info + 0x24);
            m_9c = SP::RandomInRange(r);
        }
    }
    else {
        Vector2_s004d_f2d0 r;
        r.lo = *(float*)(info + 0x18);
        r.hi = *(float*)(info + 0x1c);
        m_9c = SP::RandomInRange(r);
    }

    m_40 = (arg != 0) ? 1 : 0;
    if (m_234 >= 0) {
        void* sys = m_sys;
        void* v = *(void**)sys;
        void* (__thiscall* f)(void*) = *(void* (__thiscall**)(void*))((char*)v + 0x20);
        void* r = f(sys);
        void* rv = *(void**)r;
        (*(void (__thiscall**)(void*, int, byte))((char*)rv + 0x24))(r, m_234, m_0e);
        return;
    }
    if (m_230 >= 0) {
        void* sys = m_sys;
        void* v = *(void**)sys;
        void* (__thiscall* f)(void*) = *(void* (__thiscall**)(void*))((char*)v + 0x20);
        void* r = f(sys);
        void* rv = *(void**)r;
        (*(void (__thiscall**)(void*, int, byte))((char*)rv + 0x38))(r, m_230, m_0e);
    }
}

// @ 0x00f589e0
void cSwarmField::SetObject(void* obj)
{
    cSwarmField* n = obj ? (cSwarmField*)((char*)obj - 8) : 0;
    cSwarmField* old = m_228;

    if (n == old) {
        *(byte*)((char*)old + 0x234) = 1;
        return;
    }
    if (n != 0) {
        void* vt = *(void**)((char*)n + 8);
        (*(void (__thiscall**)(void*))((char*)vt + 0x34))((char*)n + 8);
    }
    m_228 = n;
    if (old != 0) {
        void* vt = *(void**)((char*)old + 8);
        (*(void (__thiscall**)(void*))((char*)vt + 0x38))((char*)old + 8);
        *(byte*)((char*)m_228 + 0x234) = 1;
        return;
    }
    *(byte*)((char*)n + 0x234) = 1;
}

// @ 0x00f58a60
void cSwarmField::Update(void* p, void* arg)
{
    char*  info = *(char**)((char*)this + 0x24);
    float* arr  = *(float**)(info + 0x84);
    float  v    = m_19c * *(float*)((char*)p + 0x28);

    if (arr != *(float**)(info + 0x88)) {
        unsigned n = (unsigned)((*(int*)(info + 0x88) - (int)arr) >> 2) - 1;
        float r;
        if (n == 0) {
            r = *arr;
        }
        else {
            float u = (float)n * (*(float*)((char*)p + 8) / *(float*)((char*)p + 0xc));
            int   i = (int)u;
            float f = u - (float)i;
            float* a = *(float**)(info + 0x84);
            if (f <= 0.0f)
                r = a[i];
            else
                r = (a[i + 1] - a[i]) * f + a[i];
        }
        v = r * v;
    }

    FUN_00a7f5a0(m_2c, m_30, m_1ec, m_204, m_118 * v, arg,
                 (char*)p + 0x10, (char*)p + 0x1c, m_16 == 0,
                 (char*)this + 0x108, 0);
}

// @ 0x00f58b70
void cSwarmField::SetPoint(float* p)
{
    float x = p[0] - m_10c;
    float y = p[1] - m_110;
    float z = p[2] - m_114;

    if (m_118 != 1.0f) {
        float r = 1.0f / m_118;
        x = r * x;
        y = y * r;
        z = z * r;
    }

    float ax = x, ay = y, az = z;
    if ((m_108 & 2) != 0) {
        ax = (m_124 * z + m_120 * y) + m_11c * x;
        ay = (m_130 * z + m_12c * y) + m_128 * x;
        az = (m_13c * z + m_138 * y) + m_134 * x;
    }

    ax = ax - *(float*)&m_d4;
    ay = ay - *(float*)&m_d8;
    az = az - *(float*)&m_dc;

    if (m_e0 != 1.0f) {
        float r = 1.0f / m_e0;
        ax = r * ax;
        ay = ay * r;
        az = az * r;
    }

    float bx = ax, by = ay, bz = az;
    if ((m_d0 & 2) != 0) {
        bx = (m_ec * az + m_e8 * ay) + bx * m_e4;
        by = (m_f8 * az + m_f4 * ay) + m_f0 * ax;
        bz = (m_104 * az + m_100 * ay) + ax * m_fc;
    }

    char* info = *(char**)((char*)this + 0x24);
    float radius = (*(float*)(info + 0x10) + *(float*)(info + 0xc)) * 0.5f;
    float s = (radius * radius) * 0.5f;
    bz = bz - m_74 * s;
    by = by - m_70 * s;
    bx = bx - m_6c * s;

    float len = (float)sqrt((double)(bx * bx + (by * by + bz * bz)));
    if (len > 0.0f) {
        float r = 1.0f / len;
        bx = r * bx;
        by = by * r;
        bz = bz * r;
    }

    Vec3  dir;
    float basis[9];
    dir.x = bx;
    dir.y = by;
    dir.z = bz;
    FUN_00a81a20(&dir.x, basis);
    *(unsigned short*)&m_d0 |= 2;
    *(unsigned short*)((char*)this + 0xd2) =
        (unsigned short)(*(unsigned short*)((char*)this + 0xd2) + 1);
    float* dst = &m_e4;
    for (int i = 0; i < 9; i++)
        dst[i] = basis[i];

    m_168 = ((1.0f / radius) /
            ((*(float*)(info + 0x44) + *(float*)(info + 0x40)) * 0.5f)) * len;
}

// @ 0x00f58ed0
void __cdecl FUN_00f58ed0(void* st, float* unused, Vec3* pt, Vec3* mul)
{
    char* s = (char*)st;

    float fx = ((pt->x - *(float*)(s + 0xd4)) - *(float*)(s + 0x1c8)) /
               (*(float*)(s + 0x1d4) - *(float*)(s + 0x1c8));
    float fy = ((pt->y - *(float*)(s + 0xd8)) - *(float*)(s + 0x1cc)) /
               (*(float*)(s + 0x1d8) - *(float*)(s + 0x1cc));
    float fz = ((pt->z - *(float*)(s + 0xdc)) - *(float*)(s + 0x1d0)) /
               (*(float*)(s + 0x1dc) - *(float*)(s + 0x1d0));

    int ix = (int)fx;
    if (fx < (float)ix) ix--;
    int iy = (int)fy;
    if (fy < (float)iy) iy--;
    int iz = (int)fz;
    if (fz < (float)iz) iz--;

    float t = ((*(float*)(s + 0xf8) * ((fz - (float)iz) - 0.5f) +
                *(float*)(s + 0xf4) * ((fy - (float)iy) - 0.5f)) +
               *(float*)(s + 0xf0) * ((fx - (float)ix) - 0.5f)) + 0.5f;
    float u = t;
    if (u < 0.0f) u = 0.0f;
    if (u > 1.0f) u = 1.0f;

    Vec3* vb = *(Vec3**)(s + 0x180);
    Vec3* ve = *(Vec3**)(s + 0x184);
    if (vb != ve) {
        int n = (int)(ve - vb) - 1;
        Vec3 r;
        if (n == 0) {
            r = *vb;
        }
        else {
            float fn = (float)n;
            int   i  = (int)(fn * u);
            float f  = fn * u - (float)i;
            Vec3* e  = *(Vec3**)(s + 0x180) + i;
            if (f <= 0.0f) {
                r = *e;
            }
            else {
                r.x = e->x + (e[1].x - e->x) * f;
                r.y = e->y + (e[1].y - e->y) * f;
                r.z = e->z + (e[1].z - e->z) * f;
            }
        }
        mul->x = mul->x * r.x;
        mul->y = mul->y * r.y;
        mul->z = mul->z * r.z;
    }

    float* fb = *(float**)(s + 0x194);
    float* fe = *(float**)(s + 0x198);
    if (fb != fe) {
        int n = (int)(fe - fb) - 1;
        if (n == 0) {
            mul->x = *fb * mul->x;
        }
        else {
            float fn = (float)n;
            int   i  = (int)(fn * u);
            float f  = fn * u - (float)i;
            float* a = *(float**)(s + 0x194);
            if (f <= 0.0f) {
                mul->x = a[i] * mul->x;
            }
            else {
                float v = a[i];
                mul->x = ((a[i + 1] - v) * f + v) * mul->x;
            }
        }
    }

    pt->x = *(float*)(s + 0xd4) +
            (*(float*)(s + 0x1c8) + (*(float*)(s + 0x1d4) - *(float*)(s + 0x1c8)) * (fx - (float)ix));
    pt->y = *(float*)(s + 0xd8) +
            (*(float*)(s + 0x1cc) + (*(float*)(s + 0x1d8) - *(float*)(s + 0x1cc)) * (fy - (float)iy));
    pt->z = *(float*)(s + 0xdc) +
            (*(float*)(s + 0x1d0) + (*(float*)(s + 0x1dc) - *(float*)(s + 0x1d0)) * (fz - (float)iz));
}
