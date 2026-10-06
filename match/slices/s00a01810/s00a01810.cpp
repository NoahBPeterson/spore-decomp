// Slice s00a01810 - SP::cAnimatingCreature / Anim::anim_qb helpers.
// anim_query/anim_qb layout from the ModAPI 2017 header (offsets match retail).
#include "types.h"

struct AnimReference {
    uint32_t animID;        // +0x00
    float    duration;      // +0x04
    float    durationScale; // +0x08
};

class RefObj;
class anim_qb;
class anim_query {
public:
    RefObj*      field_0;       // +0x00
    RefObj*      field_4;       // +0x04
    AnimReference anims[8];     // +0x08
    int          field_68;      // +0x68
    int          field_6C;      // +0x6C
    float        field_70;      // +0x70
    float        field_74;      // +0x74
    float        field_78;      // +0x78
    bool         field_7C;      // +0x7C
    int          mode;          // +0x80
    bool         idle;          // +0x84
    float        blendInTime;   // +0x88
    float        field_8C;      // +0x8C
    float        field_90;      // +0x90
    float        field_94;      // +0x94
    float        field_98;      // +0x98
    bool         field_9C;      // +0x9C
    bool         field_9D;      // +0x9D
    float        field_A0;      // +0xA0
    int          field_A4;      // +0xA4
    double       field_A8;      // +0xA8
    int          field_B0;      // +0xB0
    int          field_B4;      // +0xB4
    float        field_B8;      // +0xB8
    int          field_BC;      // +0xBC
    int          field_C0;      // +0xC0
    float        field_C4;      // +0xC4
    float        field_C8;      // +0xC8
    float        field_CC;      // +0xCC
    float        field_D0;      // +0xD0
    bool         field_D4;      // +0xD4
    uint32_t     animID;        // +0xD8
    int          field_DC;      // +0xDC
    int          field_E0;      // +0xE0
    int          field_E4;      // +0xE4
    int          field_E8;      // +0xE8
    int          field_EC;      // +0xEC

    void  Reset();              // 0xa00490
    char  Test();               // 0x9ff020
    void  Set670(int a, int b); // 0xa00670
};

class CObj {
public:
    char pad[0x400];
    void T660();
    void T060();
    void T0b0();
};

class RefObj {
public:
    char pad[0x1000];
    void  Rel9ae1c0();
    void  Rel9a3630();
    void  Rel9c4cc0();
    float Ac2b0(void* p, RefObj* f0, float v, int a, int b, int c);
    void  Acac0(float v);
};

class anim_qb {
public:
    int          field_0;        // +0x00
    int          field_4;        // +0x04
    anim_query   queries[16];    // +0x08
    int          field_F08;      // +0xF08
    unsigned int field_F0C[16];  // +0xF0C
    int          field_F4C[16];  // +0xF4C
    int          field_F8C;
    int          field_F90;
    int          field_F94;
    int          field_F98;
    int          field_F9C;
    unsigned int field_FA0;
    unsigned int field_FA4;
    unsigned int field_FA8;
    bool         field_FAC;      // +0xFAC
    float        field_FB0;
    float        field_FB4;
    float        field_FB8;
    void*        p_anim_cid;     // +0xFBC
    int          field_FC0;
    float        field_FC4;
    float        field_FC8;
    bool         field_FCC;

    anim_qb();                                   // 0xa01c10
    ~anim_qb();                                  // 0xa01c70
    void UpdateQuery(uint32_t id, float delta);  // 0xa01cd0
    void Foo(int, int);                          // 0xa01f10
    void Update(float dt, bool b, int a, int c); // 0xa01f40
    bool Bar(int);                               // 0xa02440
    void Reset(int flag);                        // 0xa007d0
    void Commit();                               // 0xa00980
    void Remove(int index);                      // 0xa00f10
    void Ret(anim_query* q, int a);              // 0xa00f90
    void D50(int a, int b);                      // 0xa00d50
};

extern "C" {
    extern const float g_1485720;
    extern const float g_13eb1bc;
    extern const float g_13f6a3c;
    extern const float g_13ec480;
    extern const float g_1550b78;
    extern const float g_1550b74;
    extern const float g_15517d0;
    extern const float g_1485378;
    extern const float g_1471064;
    extern const float g_13f11c8;
    extern const float g_13f51ac;
    extern const float g_13eb8b0;
    extern const float g_14488fc;

    void  __stdcall  vci(void* dst, int size, int count, void* ctor);
    void  __cdecl    animref_ctor();
    int   __cdecl    qb_free_slot(anim_qb* qb);
    char  __cdecl    qb_find2(anim_qb* qb, anim_query* q);
    void  __cdecl    qb_add(anim_qb* qb, anim_query* q, int a, int b);
    void  __cdecl    q_swap(anim_query* a, anim_query* b);
    anim_query* __cdecl qb_get(anim_qb* qb, int id);
    void  __cdecl    qb_get2(anim_query** out, anim_qb* qb, int id);
    float __cdecl    f_9b01e0(float a, float b, float c);
    void  __cdecl    f_9b3bc0(void* a);
    void  __cdecl    f_9bb910(void* a);
    float __cdecl    f_9a2c90(void* a, float b, char c, int d);
    char  __cdecl    f_9a38f0(void* a, int b, void* c);
    int   __cdecl    f_9a4430(int a, int b, int c);
    int   __cdecl    f_9a4550(void* a, int b);
    void  __cdecl    f_99e110(float a, void* b, RefObj* c, int d, int e, int f);
}

// ---------------------------------------------------------------------------
// SP::cAnimatingCreature orientation helpers  (@ 0xa02710 / 0xa02740)
// ---------------------------------------------------------------------------
class cAnimatingCreature {
public:
    char pad[0x1000];
    bool IsOrientStartAnim(uint32_t animID);
    bool IsOrientStopAnim(uint32_t animID);
};

bool cAnimatingCreature::IsOrientStartAnim(uint32_t animID)   // @ 0xa02710
{
    if (animID == 0x4866d8e || animID == 0x452b634 || animID == 0x5cb2176)
        return true;
    return false;
}

bool cAnimatingCreature::IsOrientStopAnim(uint32_t animID)    // @ 0xa02740
{
    if (animID == 0x4866db9 || animID == 0x4866dc3 || animID == 0x4866dcb || animID == 0x4866dd4 ||
        animID == 0x5cb21ae || animID == 0x5cb21af || animID == 0x5cb21b0 || animID == 0x452b651 ||
        animID == 0x4482911 || animID == 0x4482918 || animID == 0x448291f)
        return true;
    return false;
}

// ---------------------------------------------------------------------------
// anim_qb
// ---------------------------------------------------------------------------

// @ 0xa01c10
anim_qb::anim_qb()
{
    anim_query* p = queries;
    for (int i = 15; i >= 0; --i) {
        anim_query& q = *p;
        AnimReference* a = q.anims;
        q.field_0 = 0;
        q.field_4 = 0;
        vci(a, sizeof(AnimReference), 8, (void*)animref_ctor);
        q.Reset();
        ++p;
    }
    p_anim_cid = 0;
    Reset(1);
}

// @ 0xa01c70
anim_qb::~anim_qb()
{
    Reset(1);
    if (p_anim_cid)
        ((RefObj*)p_anim_cid)->Rel9c4cc0();
    anim_query* p = &queries[16];
    for (int i = 15; i >= 0; --i) {
        anim_query& q = *--p;
        q.Reset();
        if (q.field_4)
            q.field_4->Rel9ae1c0();
        if (q.field_0)
            q.field_0->Rel9a3630();
    }
}

// @ 0xa01f10
void anim_qb::Foo(int a, int b)
{
    anim_query* q = qb_get(this, a);
    if (q)
        Ret(q, b);
}

// @ 0xa01810  (free cdecl helper)
void qb_set_query(anim_qb* qb, int index, int mode, bool idle)
{
    if (mode == 0 && qb->field_FA0 == -1) {
        int i = qb->field_FA4;
        if (i >= 16) {
            mode = 1;
        } else if (qb->field_F0C[i] < 16) {
            int v = qb->field_F0C[i];
            if (v == qb->field_FA8 || *(int*)((char*)qb + v * 0xf0 + 0xc8) == 3)
                mode = 1;
        }
    }

    switch (mode) {
    case 0: {
        int n = qb->field_F9C + 1;
        n = n % 16;
        if (qb->field_FA0 >= 16) {
            qb->field_FA0 = n;
            qb->field_F9C = n;
            qb->field_F4C[n] = index;
            return;
        }
        if (qb->field_FA0 != n) {
            qb->field_F9C = n;
            qb->field_F4C[n] = index;
        }
        break;
    }
    case 1: {
        if (qb->field_FA4 < 16) {
            int a = qb->field_F0C[qb->field_FA4];
            if (a < 16) {
                anim_query* qA = &qb->queries[a];
                anim_query* qB = &qb->queries[index];
                q_swap(qB, qA);
                if (qA->field_C0 == 0) {
                    int cur = qb->field_F0C[qb->field_FA4];
                    int old = qb->field_FA8;
                    qb->field_F0C[qb->field_FA4] = -1;
                    if (cur != old || idle)
                        qA->Reset();
                }
            }
        }
        int i;
        for (i = 0; i < 16; ++i)
            if (qb->field_F0C[i] == -1)
                break;
        if (i < 16) {
            qb->field_F0C[i] = index;
            qb->field_FA4 = i;
            if (idle) {
                unsigned int old = qb->field_FA8;
                if (old < 16 && old != (unsigned int)index) {
                    if (qb->queries[old].Test())
                        qb->queries[old].Set670(1, 0);
                }
                qb->field_FA8 = index;
            }
        }
        qb->Commit();
        break;
    }
    case 2: {
        int i;
        for (i = 0; i < 16; ++i)
            if (qb->field_F0C[i] == -1)
                break;
        if (i < 16)
            qb->field_F0C[i] = index;
        break;
    }
    }
}

// @ 0xa01a00  (free cdecl helper)
int qb_add_query(anim_qb* qb, int param_2, AnimReference* refs, unsigned int param_4)
{
    if (param_2 == 0)
        return 0;
    unsigned int slot = qb_free_slot(qb);
    if (slot >= 16)
        return 0;
    anim_query* q = &qb->queries[slot];
    q->Reset();
    unsigned int n = param_4 < 9 ? param_4 : 8;
    if (n != 0) {
        AnimReference* dst = (AnimReference*)((char*)q + 8);
        do {
            *dst = *refs;
            ++refs;
            ++dst;
            --n;
        } while (n != 0);
    }
    q->field_A8 = 0.0;
    q->field_B0 = 0;
    q->field_70 = 0.0f;
    q->field_74 = g_13f6a3c;
    q->field_D4 = false;
    q->field_BC = 0;
    q->animID = 0;
    q->field_7C = false;
    q->idle = false;
    q->field_8C = g_1485720;
    q->field_A0 = g_1485720;
    q->field_78 = g_13ec480;
    q->field_CC = g_13eb1bc;
    q->field_D0 = g_1485720;
    q->blendInTime = g_13ec480;
    q->mode = 1;
    q->field_B4 = qb->field_0;
    unsigned int id = (unsigned int)qb->field_0 * 256 + 1 + (slot & 0xff);
    if (!qb_find2(qb, q))
        qb_add(qb, q, id, param_2);
    return id;
}

// @ 0xa01b50  (free cdecl helper)
bool qb_enable(anim_qb* qb, int animID)
{
    if (animID != 0) {
        anim_query* found[2];
        qb_get2(found, qb, animID);
        if (found[1] != 0) {
            anim_query* p = found[1];
            qb_set_query(qb, (int)(((char*)p - (char*)qb) - 8) / 0xf0, p->mode, p->idle);
            found[0]->field_7C = true;
            p->field_7C = true;
            return true;
        }
        anim_query* p = found[0];
        qb_set_query(qb, (int)(((char*)p - (char*)qb) - 8) / 0xf0, p->mode, p->idle);
        p->field_7C = true;
        return true;
    }
    return false;
}

// @ 0xa01cd0
void anim_qb::UpdateQuery(uint32_t param_1, float param_2)
{
    unsigned int idx = (param_1 & 0xff) - 1;
    if (idx >= 16)
        return;
    anim_query* q = &queries[idx];
    if (q->field_B4 != (int)(param_1 >> 8))
        return;

    float v = q->field_C8 - param_2;
    int otherIdx = (q->field_6C & 0xff) - 1;
    anim_query* other = &queries[otherIdx];
    q->field_C8 = v;

    if (q->field_C0 != 0)
        return;
    if (q->field_0 == 0) {
        if (other->field_C0 == 3)
            return;
        if (!qb_find2(this, q))
            return;
        if (q->field_0 == 0)
            return;
    }
    if (!(v <= 0.0f))
        return;
    if (other->field_C0 != 3) {
        ((unsigned char*)q->field_0)[0xad] = q->field_D4;
        float a = other->field_C4;
        if (a >= 0.0f) {
            q->field_C4 = a;
            q->field_B8 = a;
        } else {
            int i = q->field_68 + 1;
            float b = *(float*)((char*)q + i * 12);
            if (b >= 0.0f) {
                q->field_C4 = b;
                q->field_B8 = b;
            }
        }
        float c = other->field_D0;
        if (c == g_1485720) {
            int i = q->field_68 + 1;
            float d = *(float*)((char*)q + i * 12 + 0x10);
            if (d != g_1485720) {
                q->field_D0 = d;
                q->field_B8 *= d;
            }
        } else {
            q->field_D0 = c;
            q->field_B8 *= c;
        }
    }
    q->field_B8 = q->field_C8 * g_13eb1bc;
    q->field_A8 = other->field_A8;

    int i;
    for (i = 0; i < 16; ++i)
        if (field_F0C[i] == -1)
            break;
    if (i < 16) {
        int val = (int)idx;
        field_F0C[i] = val;
        int old = field_FA4;
        if (field_F0C[old] == otherIdx)
            field_FA4 = i;
        if (q->idle && field_FA8 == otherIdx)
            field_FA8 = val;
    }

    q->field_6C = 0;
    q->field_6C = 0;
    if (other->field_C0 == 0) {
        for (int k = 0; k < 16; ++k) {
            int v2 = field_F0C[k] * 0xf0;
            if (other == (anim_query*)((char*)this + v2 + 8))
                Remove(k);
        }
    } else {
        other->Set670(q->idle ? 0 : 1, 0);
    }
}

// @ 0xa01f40
void anim_qb::Update(float dt, bool b, int a, int c)
{
    field_FB4 = 0.0f;
    field_FB8 = 0.0f;
    float w = field_FC4;
    float notW = 0.0f;
    if (b) {
        w = w - dt;
        if (w < 0.0f)
            w = 0.0f;
        field_FC4 = w;
    } else {
        w = w + dt;
        if (w > g_1550b78)
            w = g_1550b78;
        field_FC4 = w;
    }
    if (g_1550b78 > 0.0f && dt > 0.0f) {
        float t = f_9b01e0(0.0f, g_1550b78, w);
        notW = 1.0f - t;
        field_FAC = (notW > 0.0f);
    } else {
        if (!b) {
            field_FC4 = g_1550b78;
            field_FAC = true;
        } else {
            field_FC4 = 0.0f;
            field_FAC = false;
        }
    }

    if (p_anim_cid == 0)
        return;
    if (*(char*)((char*)p_anim_cid + 0x261) == 0) {
        float x = field_FC8 + dt;
        if (x > g_1550b74)
            x = g_1550b74;
        field_FC8 = x;
    } else {
        field_FC8 = 0.0f;
    }
    field_FB0 = f_9b01e0(0.0f, g_1550b74, field_FC8);

    field_F8C = 0;
    field_F90 = 0;
    field_F94 = 0;
    field_F98 = 0;

    for (int i = 0; i < 16; ++i) {
        int qi = field_F0C[i];
        if ((unsigned)qi < 16) {
            anim_query& qq = queries[qi];
            if (qq.field_0 != 0 ||
                (qq.field_68 < 8 && qq.anims[qq.field_68].animID != 0)) {
                qq.field_94 = 0.0f;
                qq.field_98 = 0.0f;
                if (qq.field_6C != 0)
                    UpdateQuery(qq.field_6C, dt);
                if (qq.field_0 != 0) {
                    if (qq.field_C0 == 0)
                        D50(i, c);
                    if (qq.field_C0 != 0) {
                        float f = 1.0f;
                        if (qq.field_C0 == 1) {
                            float x = qq.blendInTime;
                            f = (x > 0.0f) ? f_9b01e0(0.0f, x, qq.field_B4) : 0.0f;
                            f = 1.0f - f;
                        } else if (qq.field_C0 == 3) {
                            float x = qq.field_70;
                            f = (x > 0.0f) ? f_9b01e0(0.0f, x, qq.field_B4) : 0.0f;
                        }
                        f = qq.field_90 * qq.field_8C * f;
                        if (f < g_15517d0)
                            f = 0.0f;
                        qq.field_94 = f;
                        qq.field_98 = f * notW;
                        field_FB4 += f;
                        field_FB8 += qq.field_98;
                        float r = f_9a2c90(qq.field_0, dt, field_FAC, 1);
                        qq.field_B8 = r;
                        qq.field_A8 = qq.field_A8 + dt;
                    }
                }
            } else {
                Remove(i);
            }
        } else {
            Remove(i);
        }
    }

    f_9b3bc0(p_anim_cid);

    for (int i = 0; i < 16; ++i) {
        int qi = field_F0C[i];
        if ((unsigned)qi < 16) {
            anim_query& qq = queries[qi];
            if (qq.field_0 != 0 && qq.field_C0 != 0) {
                if (!field_FAC || qq.field_94 <= 0.0f) {
                    qq.field_9C = false;
                } else {
                    f_99e110(qq.field_94, p_anim_cid, qq.field_0, 1, 0, qq.field_9C ? 0 : 1);
                    qq.field_9C = true;
                }
                if (!c || qq.field_98 <= 0.0f || qq.field_4 == 0) {
                    qq.field_9D = false;
                } else {
                    float r = qq.field_4->Ac2b0(p_anim_cid, qq.field_0, qq.field_98, 1, 0,
                                                qq.field_9D ? 0 : 1);
                    qq.field_4->Acac0(r * qq.field_B8);
                    qq.field_9D = true;
                }
            }
        }
    }

    f_9bb910(p_anim_cid);
}

// @ 0xa02440
bool anim_qb::Bar(int param)
{
    anim_query* q = qb_get(this, param);
    if (q != 0) {
        if (q->field_6C == 0)
            return true;
        while ((unsigned int)q->field_68 < 8) {
            void* p = *(void**)((char*)q + 8 + q->field_68 * 12);
            int out = 0;
            if (!f_9a38f0(*(void**)p_anim_cid, (int)p, &out)) {
                int r = f_9a4430(0, (int)p, 0);
                if (r != 0) {
                    ((CObj*)r)->T660();
                    int r2 = f_9a4550(*(void**)p_anim_cid, r);
                    if (r2 != 0) {
                        ((CObj*)r)->T060();
                        if (out != 0)
                            ((CObj*)out)->T0b0();
                        UpdateQuery((uint32_t)param, 0.0f);
                        return true;
                    }
                    ((CObj*)r)->T060();
                }
            } else if (out != 0) {
                ((CObj*)out)->T0b0();
                UpdateQuery((uint32_t)param, 0.0f);
                return true;
            }
            q->field_68 = q->field_68 + 1;
            if (out != 0)
                ((CObj*)out)->T0b0();
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0xa02530  ray / box slab intersection helper (free cdecl)
// ---------------------------------------------------------------------------
extern "C" int __cdecl RaySlab(float* p, float* d, float* o, float* m, float ex, float ey, float ez,
                               float* tMax, float* nrm)
{
    float half[3];
    half[0] = ex * 0.5f;
    half[1] = ey * 0.5f;
    half[2] = ez * 0.5f;
    float tFar = -3.402823466e+38F;
    float tNear = 3.402823466e+38F;
    for (unsigned int j = 0; j < 6; ++j) {
        unsigned int ax = j >> 1;
        float sgn = (j & 1) ? 1.0f : -1.0f;
        float m0 = m[ax] * sgn;
        float m1 = m[3 + ax] * sgn;
        float m2 = m[6 + ax] * sgn;
        float denom = d[2] * m2 + d[1] * m1 + d[0] * m0;
        float t;
        if (denom > -1e-06f && denom < 1e-06f) {
            t = 3.402823466e+38F;
        } else {
            t = (((o[2] * m2 + o[1] * m1 + o[0] * m0) -
                  (p[2] * m2 + p[1] * m1 + p[0] * m0)) +
                 (half[ax] * sgn)) * (-1.0f / denom);
        }
        if (denom <= 0.0f) {
            if (t < tNear)
                tNear = t;
        } else {
            if (tFar < t) {
                tFar = t;
                if (nrm) {
                    nrm[0] = -m0;
                    nrm[1] = -m1;
                    nrm[2] = -m2;
                }
            }
        }
    }
    if (tMax)
        *tMax = tFar;
    return (tNear - tFar) > 1e-06f;
}