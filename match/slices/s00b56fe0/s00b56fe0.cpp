// s00b56fe0 : build a constraint between two physics entities (type pair dispatch)
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

struct __declspec(align(16)) V4 {
    float x, y, z, w;
    V4() {}
    void set(const V4& o) { x = o.x; y = o.y; z = o.z; w = o.w; }
};

struct Motion {
    char pad0[0x40];
    V4 rot;           // +0x40
    char pad1[0xd0 - 0x50];
    V4 vec;           // +0xd0
    float getMass() const; // 0x01088270
};

struct ListNode { ListNode* end; };

struct PropPair { int v; int w; };

struct Ent {
    char pad0[0xc];
    void* handle;       // +0x0c
    char pad1[0x4c - 0x10];
    int propBase;       // +0x4c (array, 16-byte entries)
    int propCount;      // +0x50
    char pad2[0x58 - 0x54];
    Motion* motion;     // +0x58
    PropPair* getProp(PropPair* out, int id); // 0x00496140
};

struct Pair { Ent* a; Ent* b; };

struct Src {
    char pad0[0xc];
    char* list;         // +0x0c
    struct { char pad[0xe]; uint8_t strength; }* info; // +0x10
};

extern const float kOne; // 0x01485720
extern const float kMinusOne; // 0x013eb1bc
extern const float kStrengthScale; // 0x0146150c

float BuildAnchor(const V4* q, float scale, const V4* v, float mass, V4* out); // 0x00b4d670
void  Reject(const V4* q); // 0x00b4da40
void  AddA(void* h, int which, int flag, const V4* q); // 0x00b4e820
void  AddB(void* h0, void* h1, int prop, int which, int flag, const V4* q); // 0x00b4e980
void  AddC(void* h0, void* h1, int flag, const V4* q); // 0x00b4ead0

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)
static inline float Len3(const V4* v)
{
    double s = (double)v->z * v->z;
    s += (double)v->y * v->y;
    s += (double)v->x * v->x;
    return (float)sqrt(s);
}

struct Work {
    V4 q;             // 0x20
    V4 q2;            // 0x30
    V4 vecA;          // 0x40
    V4 vecB;          // 0x50
    V4 rotA;          // 0x60
    V4 rotB;          // 0x70
    float massA, massB, scale;
    bool fa, fb;
    float res;
    float pad[3];
    V4 out0;
    V4 out1;
    float len;
};

void __stdcall BuildConstraint(Pair* p, unsigned flag, Src* src)
{
    Ent* a = p->a;
    Ent* b = p->b;
    if (!b || !a) return;
    Work w;
    V4 neg;
    PropPair t1;
    w.scale = kOne;
    w.res = 0.0f;
    Motion* ma = a->motion;
    Motion* mb = b->motion;
    w.vecA.set(ma->vec);
    w.vecB.set(mb->vec);
    w.massA = a->motion->getMass();
    w.massB = b->motion->getMass();
    w.rotA.set(a->motion->rot);
    w.rotB.set(b->motion->rot);
    PropPair* r;
    r = a->getProp(&t1, 9);
    w.fa = r->v != 0;
    r = b->getProp(&t1, 9);
    w.fb = r->v != 0;
    if ((char)flag != 0 && src != 0) {
        ListNode* n = (ListNode*)src->list;
        if (((int)((char*)n->end - (char*)n) - 0x30) / 0x30 > 0) {
            V4* e = (V4*)((char*)n + 0x30);
            w.q.set(e[1]);
            w.q2.set(e[0]);
            w.scale = (float)src->info->strength * kStrengthScale;
        } else {
            *(char*)&flag = 0;
        }
    }
    PropPair* ta = a->getProp(&t1, 0);
    PropPair* tb = b->getProp((PropPair*)&neg, 0);
    int typeB = tb->v;
    int typeA = ta->v;
    switch (typeA) {
    case 1:
        if (typeB == 3) {
            if ((char)flag) {
                neg.x = w.q.x * kMinusOne; neg.y = w.q.y * kMinusOne; neg.z = w.q.z * kMinusOne; neg.w = w.q.w * kMinusOne;
                w.res = BuildAnchor(&neg, w.scale, &w.vecB, w.massB, &w.out1);
                w.len = Len3(&w.vecB);
            }
            AddA(b->handle, 0, flag, &w.q);
        }
        break;
    case 2:
        if (typeB == 3) {
            if ((char)flag) {
                neg.x = w.q.x * kMinusOne; neg.y = w.q.y * kMinusOne; neg.z = w.q.z * kMinusOne; neg.w = w.q.w * kMinusOne;
                w.res = BuildAnchor(&neg, w.scale, &w.vecB, w.massB, &w.out1);
                w.len = Len3(&w.vecB);
            }
            PropPair* pr = a->getProp(&t1, 5);
            AddB(b->handle, a->handle, pr->v, 0, flag, &w.q);
            return;
        }
        break;
    case 3:
        switch (typeB) {
        case 1:
            if ((char)flag) {
                w.res = BuildAnchor(&w.q, w.scale, &w.vecA, w.massA, &w.out0);
                w.len = Len3(&w.vecA);
            }
            AddA(a->handle, 1, flag, &w.q);
            return;
        case 2:
            if ((char)flag) {
                w.res = BuildAnchor(&w.q, w.scale, &w.vecA, w.massA, &w.out0);
                w.len = Len3(&w.vecA);
            }
            {
                PropPair* pr = b->getProp((PropPair*)&neg, 5);
                AddB(a->handle, b->handle, pr->v, 1, flag, &w.q);
            }
            return;
        case 3:
            if ((char)flag) {
                if (w.massB == 0.0f) {
                    w.res = BuildAnchor(&w.q, w.scale, &w.vecA, w.massA, &w.out0);
                    w.len = Len3(&w.vecA);
                } else if (w.massA == 0.0f) {
                    neg.x = w.q.x * kMinusOne; neg.y = w.q.y * kMinusOne; neg.z = w.q.z * kMinusOne; neg.w = w.q.w * kMinusOne;
                    w.res = BuildAnchor(&neg, w.scale, &w.vecB, w.massB, &w.out1);
                    w.len = Len3(&w.vecB);
                } else {
                    Reject(&w.q);
                }
            }
            AddC(a->handle, b->handle, flag, &w.q);
            return;
        }
        break;
    }
}
