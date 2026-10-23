// Slice s00e7dd90 -- SPGonzago/SPCellGame.obj (cell stage): cell-object registry helpers,
// the per-cell state machine sDoEnd (0xe7e130) and the interaction tick sUpdateInteraction.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (cell TU; no /EHsc)
//
// The originals pass several of their subject pointers in registers (EAX for
// sUpdateInteraction, EDI for sDoEnd, ESI for FUN_00e7e020): they are static helpers that
// cl gave a register calling convention.  Here they are ordinary functions that take the
// subject as their first (stack) parameter, which is behaviourally identical once the whole
// translation unit is recompiled together.
#include "types.h"

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

// ---------------------------------------------------------------- raw offset accessors
#define I(p,o) (*(int*)((char*)(p) + (o)))
#define U(p,o) (*(uint32*)((char*)(p) + (o)))
#define F(p,o) (*(float*)((char*)(p) + (o)))
#define P(p,o) (*(void**)((char*)(p) + (o)))
#define B(p,o) (*(uint8*)((char*)(p) + (o)))

// ---------------------------------------------------------------- globals
extern char* gspCellGame;             // 0x016b3c04
extern float kLevelSize[];            // 0x01483bd0
extern int   gVal;                    // (unused placeholder for symmetry)

// The cell registry lives at gspCellGame + 0x1c, the event/action manager at gspCellGame + 0x54.
struct Registry {                       // thiscall members
    void* Get(int id);                  // 0x00b721d0
    void* Find(int id);                 // 0x00b72210
};

struct Manager {                        // thiscall members
    void Remove(int id);                // 0x00b72260
    void* Next(int* cursor);            // 0x00b72230
    int   GetPriority();                // 0x00e31100
};

static Registry* registry() { return (Registry*)(gspCellGame + 0x1c); }
static Manager*  manager()  { return (Manager*)(gspCellGame + 0x54); }

// ---------------------------------------------------------------- callees
void  FUN_00e7d760(int a, float b);                             // 0x00e7d760
void  FUN_00e59200(void* p);                                    // 0x00e59200
void* FUN_00e62200(int a, float b);                             // 0x00e62200
int   FUN_00e58980(void* a, void* b);                           // 0x00e58980
void  FUN_00e576f0(int a);                                      // 0x00e576f0
void  FUN_00e7a770(int a, int b, int c, int d, int e, float f); // 0x00e7a770
void  FUN_00e67d30(void* out, void* p, int a);                  // 0x00e67d30
void  FUN_00e72530(void* p, int a, void* v);                    // 0x00e72530
char  FUN_00e56f20(int a);                                      // 0x00e56f20
void  FUN_00e780a0(int a, int b, float c, int d);               // 0x00e780a0
char  FUN_00e57460(void* a, void* b);                           // 0x00e57460
float FUN_00e6d200(void* a, int b, int c, int d);               // 0x00e6d200
void  FUN_00e51ee0(int a, float b, int c, int d, int e, int f, int g, int h,
                   int i, int j, int k, int l, int m, int n, int o, int p); // 0x00e51ee0
void  FUN_00e528d0(void (*fp)(void));                           // 0x00e528d0
void  FUN_00e528f0(int a, float b);                             // 0x00e528f0
void  FUN_00e69a90(int a, int b, float c, int d);               // 0x00e69a90
void  FUN_00e7db80(void);                                       // 0x00e7db80
char  FUN_00e59c10(void* self, float dt);                       // 0x00e59c10
char  FUN_00e7b540(void* self, int i, float dt);                 // 0x00e7b540
char  FUN_00e7ba30(void* self, float dt);                       // 0x00e7ba30
void  operator_delete__(void* p);                               // 0x00e59200-style delete

// sDoEnd case helpers (0xe7e130)
void  FUN_00e7d800(int a, int b, int c, int d, float e);        // 0x00e7d800
void  FUN_00e7add0(int a, int b, float c);                      // 0x00e7add0
void  FUN_00e59150(int a, float b);                             // 0x00e59150
void  FUN_00e7b410(int a, int b, int c);                        // 0x00e7b410
void  FUN_00e7df40(int a, int b, int c, float d);               // 0x00e7df40
void  FUN_00e7dd90(int a, int b, int c, int d, float e);        // 0x00e7dd90
void  FUN_00e7dbd0(int a, int b, int c, int d, float e);        // 0x00e7dbd0
void  FUN_00e7a160(int a);                                      // 0x00e7a160
void  FUN_00e7cbb0(int a, int b);                               // 0x00e7cbb0
void  FUN_00e50400(int a);                                      // 0x00e50400
void  FUN_00e50940(float a, int b);                             // 0x00e50940
void  FUN_00e72ac0(void);                                       // 0x00e72ac0
void  FUN_00e62440(void);                                       // 0x00e62440
void  sDigestion_End(int a, float b);                           // 0x00e7a4a0 (SP::sDigestion_End)
void  FUN_00e5ed20(int a, void* b);                             // 0x00e5ed20
void  FUN_00e794f0(int a, int b, float c, int d);               // 0x00e794f0
void  FUN_00e7cb90(void);                                       // 0x00e7cb90
void  FUN_00e59ab0(int a);                                      // 0x00e59ab0
void  FUN_00e7b9b0(int a, int b, float c);                      // 0x00e7b9b0
void  FUN_00e7b240(int a, float b);                             // 0x00e7b240
void  FUN_00e7d720(uint8 a);                                    // 0x00e7d720
void  FUN_00e567c0(void);                                       // 0x00e567c0
void  FUN_00e78de0(void);                                       // 0x00e78de0
void  FUN_00e53c20(void);                                       // 0x00e53c20
void  FUN_00e5daf0(void);                                       // 0x00e5daf0
void  FUN_00e56950(void);                                       // 0x00e56950
void  FUN_00e57d10(int a, int b, int c);                        // 0x00e57d10

void  sDoEnd(void* self, float dt, int a2, int a3);             // 0x00e7e130
void  sUpdateInteraction(void* self, float dt);                 // 0x00e7e6c0

// @ 0x00e7dd90
void FUN_00e7dd90(int a1, int a2, int a3, int a4, float a5)
{
    void* p = registry()->Get(a1);
    if (p != 0) {
        FUN_00e7d760(a4, a5);
        if (I(p, 0x168) != 0) {
            FUN_00e59200(P(p, 0x168));
            I(p, 0x168) = 0;
        }
        void* q = registry()->Get(a2);
        if (q != 0) {
            if ((I(gspCellGame, 0x411c) == a1) || (I(gspCellGame, 0x411c) == a2)) {
                float f = (float)I(q, 0x244) * 0.16666667f;
                if (I(q, 0x248) != 0) {
                    void* r = FUN_00e62200(I(q, 0), f);
                    if (r != 0)
                        I(r, 0x24) = 0x3f000000;
                }
            }
            int* pi = (int*)((char*)q + 0x244);
            int r = FUN_00e58980(p, q);
            *pi -= r;
            int zero = 0;
            int* sel = pi;
            if (*pi < 1)
                sel = &zero;
            *pi = *sel;

            FUN_00e576f0(a1);
            FUN_00e7a770(a2, I(p, 0), I(p, 0x108), I(gspCellGame, 0x411c) == a1, 6, a5);

            uint32 v[3];
            FUN_00e67d30(v, p, a3);
            FUN_00e72530(q, a3, v);
            v[0] ^= 0x80000000u;
            v[1] ^= 0x80000000u;
            v[2] ^= 0x80000000u;
            FUN_00e72530(p, -1, v);
        }
    }
}

// @ 0x00e7df40
void FUN_00e7df40(int a1, int a2, int a3, float a4)
{
    void* p = registry()->Get(a1);
    if (p != 0) {
        FUN_00e7d760(a3, a4);
        if (I(p, 0x168) != 0) {
            FUN_00e59200(P(p, 0x168));
            I(p, 0x168) = 0;
        }
    }
    void* q = registry()->Get(a2);
    if (q != 0) {
        int e = I(q, 0x358);
        int d = e - 1;
        if (FUN_00e56f20(d) == 0) {
            FUN_00e780a0(I(q, 0), 1, 0.0f, 0);
            return;
        }
        F(q, 0xb4) = (kLevelSize[d] / kLevelSize[e]) * F(q, 0xb4);
        I(q, 0x358) = d;
        if (0.0f < F(q, 0x1f0))
            F(q, 0x1f0) = 0.0f;
    }
}

// @ 0x00e7e020
int FUN_00e7e020(void* self, void* p, int a2, int a3)
{
    if (B(self, 0x179) == 0) {
        if (B(self, 0x111) == 1 || B(self, 0x17b) != 0 || B(p, 0x178) != 0 ||
            FUN_00e57460(p, self))
            return 0;
        int u = (a3 == 2) ? 0xc : 0xb;
        void* r = registry()->Find(I(p, 0));
        float f = FUN_00e6d200(r, 0, u, I(r, 0x1b0));
        FUN_00e51ee0(1, f, I(p, 0), I(self, 0), a2, -1, a3, I(self, 0x108),
                     0, 0, 0, 0, 0, 0, 0, 0);
        FUN_00e528d0(FUN_00e7db80);
        FUN_00e528f0(0, 0.33333334f * f);
        FUN_00e69a90(I(self, 0), a3, 0.33333334f * f, 0);
    }
    return 1;
}

// @ 0x00e7e130  SP::sDoEnd  (self in EDI in the original)
void sDoEnd(void* self, float dt, int a2, int a3)
{
    if (B(self, 8) == 0 && P(self, 4) != 0 && (int8_t)a3 == 0) {
        ((void (*)(void*, float))P(self, 4))(self, dt);
        B(self, 8) = 1;
    }

    switch (I(self, 0x24)) {
    case 1:
        FUN_00e7d800(I(self, 0x28), I(self, 0x38), I(self, 0x3c), B(self, 8), dt);
        manager()->Remove(I(self, 0));
        return;
    case 2:
        FUN_00e7a770(I(self, 0x28), I(self, 0x2c), I(self, 0x3c), B(self, 0x74),
                     I(self, 0x38), dt);
        manager()->Remove(I(self, 0));
        return;
    case 5: {
        int u = I(self, 0x28);
        manager()->Remove(I(self, 0));
        FUN_00e7add0(u, a2, dt);
        return;
    }
    case 6:
        FUN_00e59150(I(self, 0x28), dt);
        manager()->Remove(I(self, 0));
        return;
    case 7: {
        int u1 = I(self, 0x28);
        int u2 = I(self, 0x3c);
        manager()->Remove(I(self, 0));
        FUN_00e7b410(u1, a2, u2);
        return;
    }
    case 0xf:
        registry()->Get(I(self, 0x28));
        manager()->Remove(I(self, 0));
        return;
    case 0x10: {
        void* h = P(self, 0x70);
        if (h != 0) {
            int inner = I(h, 0x10);
            if (inner != 0 && inner != I(h, 0x20))
                operator_delete__((void*)inner);
            operator_delete__(h);
            manager()->Remove(I(self, 0));
            return;
        }
        break;
    }
    case 0x12:
        FUN_00e7df40(I(self, 0x28), I(self, 0x2c), I(self, 0x3c), dt);
        manager()->Remove(I(self, 0));
        return;
    case 0x13:
        FUN_00e7dd90(I(self, 0x28), I(self, 0x2c), I(self, 0x30), I(self, 0x3c), dt);
        manager()->Remove(I(self, 0));
        return;
    case 0x14:
        FUN_00e7dbd0(I(self, 0x28), I(self, 0x2c), I(self, 0x30), I(self, 0x3c), dt);
        manager()->Remove(I(self, 0));
        return;
    case 0x1a:
        FUN_00e7a160(I(self, 0x28));
        manager()->Remove(I(self, 0));
        return;
    case 0x1b:
        FUN_00e7cbb0(a2, a3);
        manager()->Remove(I(self, 0));
        return;
    case 0x1c:
        FUN_00e50400(a2);
        manager()->Remove(I(self, 0));
        return;
    case 0x1d:
        manager()->Remove(I(self, 0));
        FUN_00e50940(dt, a2);
        return;
    case 0x1e:
        FUN_00e72ac0();
        manager()->Remove(I(self, 0));
        return;
    case 0x1f:
        FUN_00e62440();
        manager()->Remove(I(self, 0));
        return;
    case 0x21:
        sDigestion_End(I(self, 0x28), dt);
        manager()->Remove(I(self, 0));
        return;
    case 0x22:
        FUN_00e5ed20(I(self, 0x28), (char*)self + 0x60);
        manager()->Remove(I(self, 0));
        return;
    case 0x24:
        FUN_00e794f0(I(self, 0x28), I(self, 0x2c), dt, a2);
        manager()->Remove(I(self, 0));
        return;
    case 0x25:
        FUN_00e7cb90();
        manager()->Remove(I(self, 0));
        return;
    case 0x28:
        FUN_00e59ab0(I(self, 0x28));
        manager()->Remove(I(self, 0));
        return;
    case 0x29:
        FUN_00e7b9b0(I(self, 0x28), I(self, 0x2c), dt);
        manager()->Remove(I(self, 0));
        return;
    case 0x2a:
        FUN_00e7b240(I(self, 0x28), dt);
        manager()->Remove(I(self, 0));
        return;
    case 0x2b:
        FUN_00e7d720(B(self, 0x74));
        manager()->Remove(I(self, 0));
        return;
    case 0x2c:
        FUN_00e567c0();
        manager()->Remove(I(self, 0));
        return;
    case 0x2d:
        FUN_00e78de0();
        manager()->Remove(I(self, 0));
        return;
    case 0x2f:
        FUN_00e53c20();
        manager()->Remove(I(self, 0));
        return;
    case 0x30:
        FUN_00e5daf0();
        manager()->Remove(I(self, 0));
        return;
    case 0x31:
        FUN_00e56950();
        manager()->Remove(I(self, 0));
        return;
    case 0x32:
        FUN_00e57d10(I(self, 0x28), I(self, 0x40), I(self, 0x44));
        manager()->Remove(I(self, 0));
        return;
    default:
        break;
    }
    manager()->Remove(I(self, 0));
}

// @ 0x00e7e6c0  SP::sUpdateInteraction  (self in EAX in the original)
void sUpdateInteraction(void* self, float dt)
{
    F(self, 0x1c) = F(self, 0x1c) - dt;
    if (FUN_00e59c10(self, dt) == 0) {
        sDoEnd(self, dt, 0, 0);
        return;
    }
    for (int i = 0; i < 4; i++) {
        float* pf = (float*)((char*)self + 0xc) + i;
        if (0.0f < *pf) {
            float f = *pf - dt;
            *pf = f;
            if (f < 0.0f) {
                *pf = 0.0f;
                if (FUN_00e7b540(self, i, dt) == 0)
                    goto end;
            }
        }
    }
    if (0.0f < F(self, 0x1c) || I(gspCellGame, 0x5198) == I(self, 0)) {
        if (FUN_00e7ba30(self, dt) != 0)
            return;
    } else {
        F(self, 0x1c) = 0.0f;
    }
end:
    sDoEnd(self, dt, 0, 0);
}

// @ 0x00e7e7a0
void FUN_00e7e7a0(float dt)
{
    int local = manager()->GetPriority();
    void* it = manager()->Next(&local);
    while (it != 0) {
        sUpdateInteraction(it, dt);
        it = manager()->Next(&local);
    }
}
