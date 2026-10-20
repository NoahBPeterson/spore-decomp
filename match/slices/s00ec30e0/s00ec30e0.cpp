// Slice s00ec30e0 -- SP creature behavior: jump / move-to-target action helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ---------------------------------------------------------------- helpers
// Virtual call through the object's vtable (vptr at object start).
#define VFN(p, off)     (((void**)*(void**)(p))[(off) / 4])
#define VC0(p, off)     ((int(__thiscall*)(void*))VFN(p, off))(p)
#define VCB0(p, off)    ((char(__thiscall*)(void*))VFN(p, off))(p)
#define VC1(p, off, a)  ((int(__thiscall*)(void*, int))VFN(p, off))(p, (int)(a))
#define VCB1(p, off, a) ((char(__thiscall*)(void*, int))VFN(p, off))(p, (int)(a))
#define VCF2(p, off, a, b) ((void*(__thiscall*)(void*, float, float))VFN(p, off))(p, a, b)
#define VC3(p, off, a, b, c) ((int(__thiscall*)(void*, int, int, int))VFN(p, off))(p, (int)(a), (int)(b), (int)(c))

extern "C" double __cdecl sqrt(double);

struct Vec3 { float x, y, z; };
struct Key3 { uint32_t a, b, c; };
struct Vec8 { uint32_t d[8]; };
struct Msg { uint32_t id; uint32_t type; uint32_t value; };

// Creature entry points used by this slice (retail class is SP::cSPCreatureBase).
struct CCreature {
    char pad0[0x330];
    uint32_t flags330;                                                     // +0x330
    char pad1[0x674 - 0x334];
    char* entries;                                                         // +0x674
    char pad678[0x10];
    char state688[0x20];                                                   // +0x688
    char pad2[0xb20 - 0x6a8];
    char* ptr_b20;                                                         // +0xb20
    void MoveToPointAtSpeed(int state, Vec3 const* pos, float a, float b); // 0x00c1c1d0
    bool Hover(bool on);                                                   // 0x00c13a30
    bool TryJumpToTarget(Vec3 const* a, Vec3 const* b);                    // 0x00c190e0
    void MoveStop(int);                                                    // 0x00c14750
    bool IsBehaving();                                                     // 0x00c0e420
};
struct CSpatial {
    void* GetSomething();                    // 0x00c41ec0
};

// Methods that are __thiscall in the original but whose class is unnamed here.
struct Holder;
struct CObj20 {
    char pad[0x20];
    void* p20;                               // +0x20
    void Kick();
};
struct CObj8 {
    char pad[8];
    int n8;                                  // +0x08
    int GetKind();
};
struct CNode {
    void** vptr;                             // +0x00
    char pad[4];
    uint32_t key;                            // +0x08
    void Send(int a, int b);
    void SendForce(int a, int b);
    uint32_t Compare(Holder* a, Holder* b, bool ascending);
};

// An interface holder: +0xc holds an object whose vtable sits at +0x10.
struct Holder { char pad[0xc]; char* obj; };

static void* QueryInterface(Holder* h, uint32_t id) {
    char* o = h->obj;
    return o ? ((void*(__thiscall*)(void*, uint32_t))(((void**)(*(void**)(o + 0x10)))[3]))(o + 0x10, id) : 0;
}

// ---------------------------------------------------------------- globals
extern float g_16c74a0;                 // 0x016c74a0  cSPVector3 gZero
extern float g_16c74a4;                 // 0x016c74a4
extern float g_16c74a8;                 // 0x016c74a8
extern char* g_16a1344;                 // 0x016a1344  kGUI_PanelIDs
extern char* g_16c7aa4;                 // 0x016c7aa4

extern const float kNegSix;             // 0x01489004
extern const float kNegTwo;             // 0x013ef61c
extern const float kTwo;                // 0x01470f1c
extern const float kSix;                // 0x0147b9f0
extern const float k0_2;                // 0x013ec480
extern const float k3_5;                // 0x01414a84
extern const float k80;                 // 0x014763c4
extern const float k90;                 // 0x013ec4d8
extern const float k1;                  // 0x01485720

// ---------------------------------------------------------------- callees
void __cdecl FUN_00ec02e0(void* creature);                    // 0x00ec02e0
void* __cdecl FUN_00ec2f30(void* creature);                    // 0x00ec2f30
bool __cdecl FUN_00ec0d00(void* creature, void* entry);        // 0x00ec0d00
void __cdecl FUN_00c14750(void* creature, int);                // 0x00c14750
void __cdecl FUN_00c0cff0(int);                                // 0x00c0cff0
void* __cdecl FUN_00b3d290(void*);                              // 0x00b3d290
void __cdecl FUN_00ac4ef0(void*);                              // 0x00ac4ef0
void* __cdecl FUN_00c41ec0(void);                              // 0x00c41ec0
char __cdecl FUN_00c0e420(void* creature);                     // 0x00c0e420
void* __cdecl SP_AppSystem();                                  // 0x0067dd00
void* __cdecl SP_PlanetModel();                                // 0x00b3d350
void* __cdecl FUN_004b5ad0(void* pos, void* val);              // 0x004b5ad0
void* __cdecl FUN_00b81630(void* a, void* b);                  // 0x00b81630
void __cdecl FUN_00510350(void*, int, int, void*);             // 0x00510350
void __cdecl FUN_00eec760(void*, void*);                       // 0x00eec760

// External __thiscall callees (ECX = self).
struct CExt {
    char Check();                         // 0x00641410
    void Kick();                          // 0x00641e10
    void Dispatch(Msg* msg);              // 0x00642530
};
void __cdecl FUN_00f47380(void* p);                            // 0x00f47380
double __cdecl RandUniform(void* rng);                         // 0x009360d0
void* __cdecl FUN_006c0200(void* self);                        // 0x006c0200
void* __cdecl FUN_00c04750(void* self);                        // 0x00c04750
char __cdecl FUN_006135d0(uint32_t id, float* out);            // 0x006135d0
char __cdecl FUN_00613660(uint32_t id, float* out);            // 0x00613660
int __cdecl GetFileCount(void* res);                           // 0x008e7f80
int __cdecl GetDamageState(void* c);                           // 0x0041e0d0
void* __cdecl AssignTarget(void* self, void* obj);             // 0x00c70110

extern char g_1601760;                  // 0x01601760  sMathRandom
struct RandObj { double Next(); };
extern void* g_13f94d4;                 // 0x013f94d4

// The "jump command" settings object (bytes 0x78..0x7c hold the goal flags).
struct JumpFlags {
    void** vptr;                          // +0x0
    char pad[0x74];
    bool b78;                             // +0x78
    bool b79;                             // +0x79
    bool b7a;                             // +0x7a
    bool b7b;                             // +0x7b
    bool b7c;                             // +0x7c
    char pad2[3];

    bool IsIdle();
    bool HasOtherKind();
    bool ShouldRun();
    void HandleMessage(Msg* msg);
};

// Behavior state block (0x30 bytes) initialised by FUN_00ec3520.
struct State {
    void* p00;                            // +0x00
    void* p04;                            // +0x04
    void* p08;                            // +0x08
    char pad0c[8];
    void* p14;                            // +0x14
    bool b18;                             // +0x18
    char pad19[3];
    float f1c;                            // +0x1c
    void* p20;                            // +0x20
    bool b24;                             // +0x24
    char pad25[3];
    float f28;                            // +0x28
    int p2c;                              // +0x2c

    State* Init();
};

// Result collector used by the jump actions.
struct Collector {
    Vec3* begin;                          // +0x00
    Vec3* end;                            // +0x04
    Vec3* cap;                            // +0x08
    char pad0c[8];
    int n14;                              // +0x14
    bool b18;                             // +0x18
    char pad19[3];
    float f1c;                            // +0x1c
    int n20;                              // +0x20
    bool b24;                             // +0x24
    char pad25[3];
    float f28;                            // +0x28
    int n2c;                              // +0x2c
    Collector* Init();
};

// Navigation / move request built on the stack by the jump setup action.
struct GoalRequest {
    char raw[0xd4];
    GoalRequest* Init();
    char* p50() const { return *(char**)(raw + 0x50); }
};

extern int tmp_dummy;                     // scratch for FUN_00b81630

// Per-node jump state used by the jump command.
struct JumpState {
    void* p00;                            // +0x00  current target (AutoRefCount<cCombatant>)
    float f04;                            // +0x04
    float f08;                            // +0x08
    bool b0c;                             // +0x0c
    bool b0d;                             // +0x0d
    char pad0e[2];
    Vec3 v10;                             // +0x10
    char pad1c[0x30 - 0x1c];
};

// ---------------------------------------------------------------- 0x00ec3520
// @ 0x00EC3520
State* State::Init() {
    p00 = 0;
    p04 = 0;
    p08 = 0;
    p14 = 0;
    b18 = true;
    f1c = 0.0f;
    p20 = 0;
    b24 = false;
    double d = ((RandObj*)&g_1601760)->Next() + 1.0;
    double r;
    if (d < 2.0) {
        if (d < 1.0)
            r = 1.0;
        else
            r = d;
    } else {
        r = 2.0;
    }
    p2c = 0;
    f28 = (float)r;
    return this;
}

// ---------------------------------------------------------------- 0x00ec3580
// @ 0x00EC3580
void __cdecl FUN_00ec3580(int, int, int, int, int, void** pp) {
    if (pp != 0 && *pp != 0 && ((unsigned int*)*pp)[-1] != 0) {
        FUN_00f47380(*pp);
    }
}

// ---------------------------------------------------------------- 0x00ec37f0
// @ 0x00EC37F0
float __cdecl FUN_00ec37f0(CCreature* c, int, int, int, int, int, void* desc) {
    char* entry = c->entries + *(unsigned short*)((char*)desc + 0x12) * 0x20;
    if (!FUN_00ec0d00(c, entry))
        return 0.0f;
    Vec8 saved = *(Vec8*)c->state688;
    *(Vec8*)c->state688 = *(Vec8*)entry;
    if (FUN_00ec2f30(c))
        return 1.0f;
    *(Vec8*)c->state688 = saved;
    return 0.0f;
}

// ---------------------------------------------------------------- 0x00ec3b20
// @ 0x00EC3B20
void __stdcall FUN_00ec3b20(Key3* out) {
    out->a = 0x315cbc7e;
    out->b = 0x2f7d0004;
    out->c = 0xca14de92;
}

// ---------------------------------------------------------------- 0x00ec3b40
// @ 0x00EC3B40
bool JumpFlags::IsIdle() {
    if (b78 && !VCB0(this, 0x74))
        return true;
    return false;
}

// ---------------------------------------------------------------- 0x00ec3b60
// @ 0x00EC3B60
bool JumpFlags::HasOtherKind() {
    if (VC0(this, 0x24) == 0x24720859)
        return false;
    return true;
}

// ---------------------------------------------------------------- 0x00ec3b70
// @ 0x00EC3B70
bool JumpFlags::ShouldRun() {
    bool b;
    if (*(int*)(g_16a1344 + 0x1f8) == 0) {
        void* app = SP_AppSystem();
        if (VCB0(app, 0x54))
            goto yes;
        b = false;
        goto done;
    }
yes:
    b = true;
done:
    if (((CExt*)this)->Check() && b)
        return true;
    return false;
}

// ---------------------------------------------------------------- 0x00ec3bc0
// @ 0x00EC3BC0
void CObj20::Kick() {
    ((CExt*)this)->Kick();
    if (p20 != 0) {
        FUN_00eec760(p20, (char*)this + 0x80);
    }
}

// ---------------------------------------------------------------- 0x00ec3be0
// @ 0x00EC3BE0
void JumpFlags::HandleMessage(Msg* msg) {
    ((CExt*)this)->Dispatch(msg);
    switch (msg->id) {
    case 0x15e8afc8:
        if (msg->type == 0x2e1a75d)
            b78 = msg->value == 1;
        return;
    case 0x5a3584a7:
        if (msg->type == 0x2e1a75d)
            b79 = msg->value == 1;
        return;
    case 0xb91fba14:
        if (msg->type == 0x2e1a75d)
            b7a = msg->value == 1;
        return;
    case 0xd22f5e35:
        if (msg->type == 0x2e1a75d)
            b7b = msg->value == 1;
        return;
    case 0xdb4675dd:
        if (msg->type == 0x2e1a75d)
            b7c = msg->value == 1;
        return;
    }
}

// ---------------------------------------------------------------- 0x00ec3ca0
// @ 0x00EC3CA0
int __cdecl FUN_00ec3ca0(float v) {
    if (-6.0f > v)
        return 0;
    if (-2.0f > v)
        return 1;
    if (2.0f > v)
        return 2;
    if (6.0f > v)
        return 3;
    return 4;
}

// ---------------------------------------------------------------- 0x00ec3d20
// @ 0x00EC3D20
uint32_t __stdcall FUN_00ec3d20(Holder* a, Holder* b) {
    int ia = (int)QueryInterface(a, 0x8d021ce9);
    int ib = (int)QueryInterface(b, 0x8d021ce9);
    uint32_t* va = ia != 0 ? (uint32_t*)(ia + 0x80) : 0;
    uint32_t* vb = ib != 0 ? (uint32_t*)(ib + 0x80) : 0;
    if (va != 0) {
        if (vb != 0) {
            uint32_t ua = *va;
            if (ua != 0xffffffff) {
                uint32_t ub = *vb;
                if (ub != 0xffffffff) {
                    if (ub == ua)
                        return 0;
                    return ub < ua ? 0xffffffff : 1;
                }
                return 0xffffffff;
            }
            return *vb != 0xffffffff;
        }
        return 0xffffffff;
    }
    return vb != 0;
}

// ---------------------------------------------------------------- 0x00ec3dd0
// @ 0x00EC3DD0
uint32_t __stdcall FUN_00ec3dd0(Holder* a, Holder* b) {
    int ia = (int)QueryInterface(a, 0x8d021ce9);
    int ib = (int)QueryInterface(b, 0x8d021ce9);
    if (ia != 0) {
        if (ib != 0) {
            if (*(char*)(ia + 0x79) == *(char*)(ib + 0x79))
                return 0;
            return *(char*)(ia + 0x79) == 0 ? 1 : 0xffffffff;
        }
        return 0xffffffff;
    }
    return ib != 0;
}

// ---------------------------------------------------------------- 0x00ec3e50
// @ 0x00EC3E50
int CObj8::GetKind() {
    switch (n8) {
    case 0x11576eea:
        return 0xa5512560;
    case 0x190e18aa:
        return 0x5be9e960;
    case 0x35c95bc4:
        return 0xdaf06606;
    case 0x5bd7a6a4:
        return 0x7c4e631f;
    }
    return 0;
}

// ---------------------------------------------------------------- 0x00ec3e90
// @ 0x00EC3E90
void CNode::Send(int a, int b) {
    VC3(this, 0x20, a, b, 0);
}

// ---------------------------------------------------------------- 0x00ec3eb0
// @ 0x00EC3EB0
void CNode::SendForce(int a, int b) {
    VC3(this, 0x20, a, b, 1);
}

// ---------------------------------------------------------------- 0x00ec3ed0
// @ 0x00EC3ED0
uint32_t CNode::Compare(Holder* a, Holder* b, bool ascending) {
    char* pa = (char*)QueryInterface(a, 0x13d55dc8);
    char* pb = (char*)QueryInterface(b, 0x13d55dc8);
    int va = pa ? VC0(pa, 0x9c) : 0;
    int vb = pb ? VC0(pb, 0x9c) : 0;
    if (va == 0)
        return vb != 0;
    if (vb == 0)
        return 0xffffffff;
    switch (key) {
    case 0x190e18aa: {
        float x = 0.0f;
        float y = 0.0f;
        char ca = ((char(__cdecl*)(uint32_t, float*))FUN_006135d0)(0x190e18aa, &x);
        char cb = ((char(__cdecl*)(uint32_t, float*))FUN_006135d0)(key, &y);
        if (ca) {
            if (!cb)
                return 0xffffffff;
            if (!ascending) {
                if (x == y)
                    return 0;
                return x <= y ? 1 : 0xffffffff;
            }
            if (x == y)
                return 0;
            return x < y ? 0xffffffff : 1;
        }
        return cb != 0;
    }
    case 0x11576eea:
    case 0x35c95bc4:
    case 0x5bd7a6a4: {
        float x = 0.0f;
        float y = 0.0f;
        char ca = ((char(__cdecl*)(uint32_t, float*))FUN_00613660)(key, &x);
        char cb = ((char(__cdecl*)(uint32_t, float*))FUN_00613660)(key, &y);
        if (ca) {
            if (!cb)
                return 0xffffffff;
            if (!ascending) {
                if (x != y)
                    return (int)x <= (int)y ? 0xffffffff : 1;
            } else if (x != y) {
                return (int)y <= (int)x ? 0xffffffff : 1;
            }
            return 0;
        }
        return cb != 0;
    }
    }
    return 0;
}

// ---------------------------------------------------------------- 0x00ec30e0
// @ 0x00EC30E0
uint32_t __cdecl FUN_00ec30e0(void*, CCreature* c, void*, void*, void*, JumpState* s, void*, float dt) {
    char* sp = (char*)c + 0xc0;
    s->f04 += dt;
    bool bFlag = ((c->flags330 >> 2) & 1) != 0;
    if (!bFlag)
        s->f08 += dt;
    FUN_00ec02e0(c);
    if (s->p00) {
        char* o = (char*)VC1(s->p00, 0xb8, 0x17f243b);
        if (!VCB0(o, 0x2c)) {
            void* dmg = (void*)VC1(o, 0xc, (int)&g_13f94d4);
            if (dmg != 0 && GetDamageState(dmg) == 2) {
                void* old = s->p00;
                s->p00 = 0;
                VC0(old, 0xc0);
                VC0(sp, 0xec);
                s->b0c = true;
            }
        } else {
            void* old = s->p00;
            s->p00 = 0;
            VC0(old, 0xc0);
        }
    }
    if (s->b0d && s->p00 == 0)
        return 0;
    if (s->f04 > 2.0f && !s->b0d) {
        void* t = FUN_00ec2f30(c);
        if (t != 0 && t != s->p00) {
            if (s->p00) {
                Vec3* a = (Vec3*)VC0(sp, 0x2c);
                Vec3* b = (Vec3*)VC0(t, 0x2c);
                float dx = b->x - a->x;
                float dy = b->y - a->y;
                float dz = b->z - a->z;
                float d = (float)sqrt((double)(dz * dz + (dy * dy + dx * dx)));
                if (d >= 32.0f)
                    goto after_move;
            }
            AssignTarget(s, t);
            s->v10.x = g_16c74a0;
            s->v10.y = g_16c74a4;
            s->v10.z = g_16c74a8;
            bFlag = false;
        }
    after_move:
        s->f04 = 0.0f;
    }
    if (s->p00 == 0 || (s->f08 <= 0.2f && !bFlag))
        goto done;
    {
        void* tgt = s->p00;
        Vec3* pos = (Vec3*)VC0(sp, 0x2c);
        Vec3* tpos = (Vec3*)VC0(tgt, 0x2c);
        float dx = tpos->x - pos->x;
        float dy = tpos->y - pos->y;
        float dz = tpos->z - pos->z;
        float dist = (float)sqrt((double)(dz * dz + (dy * dy + dx * dx)));
        float d = dist - *(float*)VC0(tgt, 0x74) - *(float*)VC0(sp, 0x74);
        if (d >= 3.5f) {
            Vec3* p2 = (Vec3*)VC0(tgt, 0x2c);
            float lx = p2->x - s->v10.x;
            float ly = p2->y - s->v10.y;
            float lz = p2->z - s->v10.z;
            float f21 = (float)sqrt((double)(lz * lz + (ly * ly + lx * lx)));
            void* em = ((CSpatial*)sp)->GetSomething();
            bool b1 = bFlag ? (f21 > 80.0f) : (f21 > 1.0f);
            bool b2 = bFlag && (d < 90.0f);
            if (*(int*)((char*)em + 0x5c) != 0 && !b1) {
                if (!b2)
                    goto clear_timer;
            }
            {
                void* q = (void*)((char*)c + 0x194);
                FUN_00ac4ef0(FUN_00b3d290(q));
            }
            {
                char* tp = (char*)s->p00;
                float f21 = (float)(*(float*)VC0(sp, 0x74) + *(float*)VC0(tp, 0x74)) + 3.0f;
                if (*(char*)(tp + 0x77) == 0 && (*(uint32_t*)(tp + 0x50) & 0x1000) == 0 &&
                    *(char*)((char*)c + 0x137) != 0 && *(int*)(c->ptr_b20 + 0x610) > 0) {
                    if (*(int*)(c->ptr_b20 + 0x61c) == 0) {
                        Vec3* v = (Vec3*)VC1(s->p00, 0x2c, 0);
                        c->TryJumpToTarget(0, v);
                    } else {
                        float f4 = *(float*)VC0(sp, 0x74) + f21;
                        Vec3* v = (Vec3*)VCF2(s->p00, 0x2c, f21, f4);
                        c->MoveToPointAtSpeed(2, v, f21, f4);
                        c->Hover(true);
                    }
                } else {
                    c->Hover(false);
                    float sum = (float)(*(float*)VC0(sp, 0x74) + *(float*)VC0(s->p00, 0x74)) + 3.0f;
                    float f4 = *(float*)VC0(sp, 0x74) + sum;
                    Vec3* v = (Vec3*)VCF2(s->p00, 0x2c, sum, f4);
                    c->MoveToPointAtSpeed(2, v, sum, f4);
                    c->MoveStop(0);
                }
                s->b0c = false;
                s->v10 = *(Vec3*)VC0(s->p00, 0x2c);
            }
            goto clear_timer;
        } else if (!s->b0c) {
            VC0(sp, 0xec);
            s->b0c = true;
            if (s->b0d)
                return 0;
        }
    }
clear_timer:
    s->f08 = 0.0f;
done:
    if (s->b0c && !FUN_00c0e420(c)) {
        c->MoveStop(0);
    }
    return 1;
}

// ---------------------------------------------------------------- 0x00ec35a0 (partial)
// @ 0x00EC35A0
uint32_t __cdecl FUN_00ec35a0(CCreature* c, int, int, int, void** out) {
    char* sp = (char*)c + 0xc0;
    GoalRequest goal;
    goal.Init();
    VC1(sp, 0xdc, (int)&goal);
    char* str = goal.p50();
    if (str != 0 && ((unsigned int*)str)[-1] != 0) {
        FUN_00f47380(str);
    }
    FUN_00c0cff0(0);
    FUN_00c14750(c, 0);
    *out = 0;
    return 1;
}

// ---------------------------------------------------------------- 0x00ec3880
// @ 0x00EC3880
uint32_t __cdecl FUN_00ec3880(CCreature* c, int, int, int, unsigned char flags, Collector* col) {
    char* sp = (char*)c + 0xc0;
    if (col != 0) {
        col->Init();
    }
    VC0(sp, 0xec);
    void* pm = FUN_006c0200(c);
    if (pm == 0) {
        Vec3* v = (Vec3*)VC0(sp, 0x2c);
        if (col->end < col->cap) {
            Vec3* dst = col->end;
            col->end = dst + 1;
            if (dst != 0)
                *dst = *v;
        } else {
            FUN_004b5ad0(col->end, v);
        }
        Vec3* o = (Vec3*)VC0(sp, 0x5c);
        Vec3 tmp;
        tmp.x = o->x * 32.0f;
        tmp.y = o->y * 32.0f;
        tmp.z = o->z * 32.0f;
        Vec3* p = (Vec3*)VC0(sp, 0x2c);
        tmp.x += p->x;
        tmp.y += p->y;
        tmp.z += p->z;
        if (col->end < col->cap) {
            Vec3* dst = col->end;
            col->end = dst + 1;
            if (dst != 0)
                *dst = tmp;
        } else {
            FUN_004b5ad0(col->end, &tmp);
        }
    } else {
        SP_PlanetModel();
        if (col->end < col->cap) {
            Vec3* dst = col->end;
            col->end = dst + 1;
            if (dst != 0) {
                dst->x = *(float*)((char*)c + 0x1654);
                dst->y = *(float*)((char*)c + 0x1658);
                dst->z = *(float*)((char*)c + 0x165c);
            }
        } else {
            FUN_004b5ad0(col->end, (char*)c + 0x1654);
        }
        int idx = *(int*)(*(char**)(g_16c7aa4 + 0x78) + 0xb8) * 0x34;
        char* rec = (char*)pm + idx + 0x28;
        FUN_00510350(col->end, *(int*)(rec + 0x1c), *(int*)(rec + 0x20), c);
        int n = (int)(col->end - col->begin);
        for (int i = 0; i < n; i++) {
            Vec3* p = col->begin + i;
            Vec3* r = (Vec3*)FUN_00b81630(&tmp_dummy, p);
            *p = *r;
        }
        char* m = (char*)FUN_00c04750(c);
        if (m[0x4c8] != 0) {
            col->n14 = flags & 1;
            goto set_done;
        }
        if (*(int*)(m + 0x4b8) == 4) {
            col->n14 = (*(int*)(m + 0x30 + 0x28) == 2) ? 2 : 0;
            goto set_done;
        }
        if (*(int*)(m + 0x4b8) == 6) {
            col->n14 = 1;
            goto set_done;
        }
    }
    col->n14 = 0;
set_done:
    col->b18 = true;
    col->n20 = 0;
    return 1;
}
