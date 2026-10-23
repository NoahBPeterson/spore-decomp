// Slice s00e7b0a0 -- SPGonzago/SPCellGame.obj (cell stage): interaction/attachment dispatch
// helpers plus the two cCellMessage action switches (0xe7b540, 0xe7ba30).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (cell TU; no /EHsc)
//
// Several originals are static helpers that cl gave a register calling convention (subject in
// ESI/EAX/EBX, one float in XMM0).  They are emitted here as ordinary functions taking the
// subject as a stack parameter, which is behaviourally identical once the whole TU is rebuilt.
#include "types.h"

typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t  uint8;
typedef int8_t   int8;

// ---------------------------------------------------------------- raw offset accessors
#define I(p,o) (*(int*)((char*)(p) + (o)))
#define U(p,o) (*(uint32*)((char*)(p) + (o)))
#define F(p,o) (*(float*)((char*)(p) + (o)))
#define P(p,o) (*(void**)((char*)(p) + (o)))
#define B(p,o) (*(uint8*)((char*)(p) + (o)))

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------- globals
extern char*  gspCellGame;       // 0x016b3c04
extern char*  gspCellGfx;        // 0x016b3c08
extern char*  gspCellUI;         // 0x016b3c0c
extern Vec3   gCellWorldCenter;  // 0x016b3c28
extern float  g_15a7c4c[4];      // 0x015a7c4c (0,0,0,1)
extern float  g_13eb8b0;         // 0x013eb8b0  -0.0f (sign mask)
extern float  g_1471064;         // 0x01471064  0.5f
extern float  g_14007f4;         // 0x014007f4  15.0f
extern float  g_1477fc0;         // 0x01477fc0  300.0f

// ---------------------------------------------------------------- pools
struct cObjectPool {                    // cSPObjectPoolT<T,N>
    void* GetSafe(int h);               // 0x00b721d0  (thiscall, ret 4)
    void* Get(int h);                   // 0x00b72210  (thiscall, ret 4)
    int   Alloc();                      // 0x00b72160  (thiscall, ret)
    void  Free(int h);                  // 0x00b72260  (thiscall, ret 4)
};

static cObjectPool* cells() { return (cObjectPool*)(gspCellGame + 0x1c); }
static cObjectPool* msgs()  { return (cObjectPool*)(gspCellGame + 0x54); }

// cCellMessage / interaction record (the 0xe7b540 / 0xe7ba30 subject).
struct cCellMessage {
    void*   vptr;      // +0x00
    void*   cb;        // +0x04  callback
    uint8   st8;       // +0x08
    uint8   pad09[3];
    float   f0c;       // +0x0c
    float   f10;       // +0x10
    uint8   pad14[8];
    float   f1c;       // +0x1c
    float   f20;       // +0x20
    int     type;      // +0x24  message id
    int     a28;       // +0x28
    int     a2c;       // +0x2c
    int     a30;       // +0x30
    int     a34;       // +0x34
    int     a38;       // +0x38
    int     a3c;       // +0x3c
    float   f40;       // +0x40
    float   f44;       // +0x44
    Vec3    v48;       // +0x48
    Vec3    v54;       // +0x54
    Vec3    v60;       // +0x60
    int     a6c;       // +0x6c
    int     a70;       // +0x70
    uint8   b74;       // +0x74
    uint8   pad75[3];
    int     a78;       // +0x78
};

// list whose first slot is claimed by FUN_00e65840
struct cOccupancy { int* Claim(); };    // 0x00e65840 (thiscall)

struct cTriggerMgr { void setModal(int); };   // 0x00ad7e40 (thiscall, ret 4)
cTriggerMgr* GetTriggerMgr();                 // 0x00b3d4d0

// ---------------------------------------------------------------- callees
int   __fastcall sGetSourceLevel(void* unused, int level);          // 0x00e4ee60 (level in EDX)
void* FUN_00e4cce0(int id);                                        // 0x00e4cce0 LayerCatalog_GetEntry
void* FUN_00e4cc40(int id, void* out);                             // 0x00e4cc40 -> 0x00e823a0
int   FUN_00e57340(void* p);                                       // 0x00e57340 cell age
bool  FUN_00e52960();                                              // 0x00e52960
int   FUN_00e58980(void* a, void* b);                              // 0x00e58980
bool  FUN_00e57460(void* a, void* b);                              // 0x00e57460
float FUN_00e6d200(void* a, int b, int c, int d);                  // 0x00e6d200
void  FUN_00e7a7c0(void* a, void* b, void* dir, int c, int d, float t); // 0x00e7a7c0
void  FUN_00e7aee0(void* a, void* b, float t);                     // 0x00e7aee0
void  FUN_00e7a4a0(void* cell, int a, int b, int c, int d, float t); // 0x00e7a4a0
void  FUN_00e76af0(void* cell, void* pos, int level, void* entry, int a5); // 0x00e76af0
void  FUN_00e780a0(int id, int a, float b, int c);                 // 0x00e780a0
void  FUN_00e51ee0(int a, float b, int c, int d, int e, int f, int g, int h,
                   int i, int j, int k, int l, int m, int n, int o, int p); // 0x00e51ee0
void  FUN_00e528d0(void (*fp)(void));                              // 0x00e528d0
bool  FUN_00e59560(int a, int b);                                  // 0x00e59560
void  FUN_00e59200(void* p);                                       // 0x00e59200
void  FUN_00e59a70(int id);                                        // 0x00e59a70
void  FUN_00743b50(void* p);                                       // 0x00743b50
void  FUN_00e82130(void* p);                                       // 0x00e82130
int   FUN_00e87260(int group, void* pos, float radius, int* out, int max, int mask); // 0x00e87260
void  FUN_00e77ac0(void* cell, void* a, void* b, float t);         // 0x00e77ac0 sDropPieces
void  FUN_00e61b90(int flag, int zero, void* pos, int* key);       // 0x00e61b90
void  FUN_00e5d7b0(int p);                                         // 0x00e5d7b0

bool  FUN_00e7b280(void* m, float t);                              // forward (used by 0xe7b470)

// 0xe7ba30 case callees (custom register conventions in the original)
void  FUN_00e69a90(int a, int b, int c, int d, float e, float f);
void  FUN_00e59010(int a, int b, int c, int d, float e, void* f);
void  FUN_00e76360(void* a, int b, int c, int d, void* e, void* f, void* g,
                   int h, float i, int j, int k, float l);
void  FUN_00e59170(int a, float b);
void  FUN_00e576f0(int a);
void  FUN_00e59260(int a);
void  FUN_00e59500(int a);
void  FUN_00e57c30(int a, int b, int c, float t);
void  FUN_00e57a60(int a, int b, int c, int d, void* e);
void  FUN_00e592f0(int a, int b, int c, void* d, void* e);
void  FUN_00e57b50(int a, int b, int c, void* d);
void  FUN_00e579c0(int a, int b);
void  FUN_00e57c90(int a, int b);
void  FUN_00e593b0(int a, int b, int c, void* d);
void  FUN_00e599b0(int a);
int   FUN_00e7b8a0(void* p, float a, float b);
void  FUN_00e58890(int a, int b, int c);
void  FUN_00e69e00(int a, int b, int c, float d, float t);
void  FUN_00e69c10(int a, int b, int c, float d, float t);
void  FUN_00e59710(int a, int b, int c, float d, float e, float t);
void  FUN_00e59640(int a, int b, int c, int d, void* e);
void  FUN_00e58ae0(int a);
void  FUN_00e58bf0(int a, float b, float c);
void  FUN_00e5ec70(int a, float b);
void  FUN_00e5ec10(int a);
void  FUN_00e591c0(int a, float t);
void  FUN_00e598e0(int a, float b);
void  FUN_00e59a30();
void  FUN_00e571f0(int a, int b);
void  FUN_00e5ed50(int a, void* b, void* c, float d, float e);
void  FUN_00e5f160(int a, int b, void* c, float t);
void  FUN_00e59b50(int a, int b, void* c);
void  FUN_00e59af0(int a, int b);
void  FUN_00e6a090(int a, int b, int c, float d, float t);
void  FUN_00e59470(int a);
void  FUN_00e532e0(void* a, float b);
void  FUN_00e56820(float a, float b);
void  FUN_00e75c30(float t);
void  FUN_00e53d50(float a, float b);
void  FUN_00e53c70(void* a, float b, float t);
void  FUN_00e569b0();
void  FUN_00e57dc0(int a);
void  FUN_00e7b7c0(void* list, void* x, void* pos, float t);       // forward

// ------------------------------------------------------------------ 0x00e7b0a0
// Try to attach cell hB to cell hA (drop an "eat"/"leak" interaction).  Returns whether it fired.
// @ 0x00e7b0a0
bool FUN_00e7b0a0(int hA, int hB, void* p3, float* dir, int e, float t)
{
    void* pa = cells()->GetSafe(hA);
    if (pa == 0)
        return false;
    void* pb = cells()->GetSafe(hB);
    if (pb == 0)
        return false;
    B(pa, 0x178) = 1;
    B(pb, 0x178) = 1;
    Vec3 d;
    if (FUN_00e57340(pb) >= 3) {
        if (FUN_00e52960()) {
            Vec3 tv = { dir[0], dir[1], dir[2] };
            d.x = -tv.x;
            d.y = -tv.y;
            d.z = -tv.z;
            FUN_00e7a7c0(pb, pa, &d, 4, e, t);
            void* unused;
            int level = sGetSourceLevel(unused, I(I(gspCellGame, 0x5190), 0x1c));
            FUN_00e76af0(pb, p3, level, FUN_00e4cce0(0x1b), -1);
            return true;
        }
        return false;
    }
    if (FUN_00e52960()) {
        if (I(pb, 0x244) > FUN_00e58980(pa, pb)) {
            Vec3 tv = { dir[0], dir[1], dir[2] };
            d.x = -tv.x;
            d.y = -tv.y;
            d.z = -tv.z;
            FUN_00e7a7c0(pb, pa, &d, 4, e, t);
            return true;
        }
    }
    FUN_00e7aee0(pb, pa, t);
    return true;
}

// ------------------------------------------------------------------ 0x00e7b240
// @ 0x00e7b240
void FUN_00e7b240(int h, float t)
{
    void* c = cells()->GetSafe(h);
    if (c != 0)
        FUN_00e7a4a0(c, 0, 0, 1, 3, t);
}

// ------------------------------------------------------------------ 0x00e7b280
// Same as 0xe7b0a0 but the subject/source positions come from the message record m.
// @ 0x00e7b280
bool FUN_00e7b280(void* m, float t)
{
    void* pa = cells()->GetSafe(I(m, 0x28));
    void* pb = cells()->GetSafe(I(m, 0x2c));
    if (pa == 0)
        return false;
    if (pb == 0)
        return false;
    if (B(pa, 0x17f) != 0)
        return false;
    if (B(pb, 0x17c) != 0)
        return false;
    Vec3 d;
    if (FUN_00e57340(pb) >= 3) {
        if (FUN_00e52960()) {
            Vec3 tv = { F(m, 0x48), F(m, 0x4c), F(m, 0x50) };
            d.x = -tv.x;
            d.y = -tv.y;
            d.z = -tv.z;
            FUN_00e7a7c0(pb, pa, &d, 5, 1, t);
            int level = sGetSourceLevel(gspCellGame, I(I(gspCellGame, 0x5190), 0x1c));
            FUN_00e76af0(pb, (char*)m + 0x54, level, FUN_00e4cce0(0x1b), -1);
            return true;
        }
        return false;
    }
    if (FUN_00e52960()) {
        if (I(pb, 0x244) > FUN_00e58980(pa, pb)) {
            Vec3 tv = { F(m, 0x48), F(m, 0x4c), F(m, 0x50) };
            d.x = -tv.x;
            d.y = -tv.y;
            d.z = -tv.z;
            FUN_00e7a7c0(pb, pa, &d, 5, 1, t);
            return true;
        }
    }
    FUN_00e7aee0(pb, pa, t);
    return true;
}

// ------------------------------------------------------------------ 0x00e7b410
// Modal-toggle for the avatar cell; other cells just get an interaction reset.
// @ 0x00e7b410
void FUN_00e7b410(int h, char b)
{
    if (h == I(gspCellGame, 0x411c)) {
        GetTriggerMgr()->setModal(0);
        B(gspCellUI, 0x936) = 0;
        B(gspCellGame, 0x51d8) = 1;
        B(gspCellGame, 0x51d9) = b;
        return;
    }
    FUN_00e780a0(h, 1, 0.0f, 0);
}

// ------------------------------------------------------------------ 0x00e7b470
// Original: self in ESI/EAX, other in EBX, a2 in EBP, a3 on the stack.
// @ 0x00e7b470
void FUN_00e7b470(void* self, void* other, int a2, void* a3)
{
    if (B(other, 0x17c) != 0)
        return;
    if (B(other, 0x17b) != 0)
        return;
    if (B(self, 0x178) != 0)
        return;
    if (B(self, 0x17f) != 0)
        return;
    if (FUN_00e57460(self, other))
        return;
    void* r = cells()->Get(I(self, 0));
    float f = FUN_00e6d200(r, 0, 5, I(r, 0x1b0));
    FUN_00e51ee0(4, f, I(self, 0), I(other, 0), a2, -1, 0, 0, 0.0f, 0.0f,
                 (int)self, (int)a3, 0, 0, 0, 0);
    FUN_00e528d0((void (*)(void))FUN_00e7b280);
    FUN_00e59560(I(other, 0), a2);
}

// ------------------------------------------------------------------ 0x00e7b540
// Original: __fastcall(m in ECX, a in EDX, t on the stack).
// @ 0x00e7b540
bool __fastcall FUN_00e7b540(cCellMessage* m, int a, float t)
{
    switch (m->type) {
    case 10:
        if (a == 0)
            return FUN_00e7b0a0(m->a28, m->a2c, (char*)m + 0x48, (float*)((char*)m + 0x54),
                                m->a38, t);
        break;
    case 0x12:
    case 0x13:
    case 0x14:
        break;
    default:
        break;
    }
    return true;
}

// ------------------------------------------------------------------ 0x00e7b5d0
// Original: arg1 = cell A on the stack, cell B in ESI.
// @ 0x00e7b5d0
void FUN_00e7b5d0(void* a, void* b)
{
    if (B(a, 0x112) == 1 || B(a, 0x113) == 1)
        return;
    {
        char buf[0x18];
        FUN_00743b50(buf);
        FUN_00e4cc40(I(b, 0x108), buf);
        FUN_00e780a0(I(b, 0), 1, 0.0f, 0);
        FUN_00e82130(buf);
    }
}

// ------------------------------------------------------------------ 0x00e7b630
// Original: self in ESI, other in EBP.
// @ 0x00e7b630
void FUN_00e7b630(void* self, void* other)
{
    if (B(self, 0x112) == 1 || B(self, 0x113) == 1)
        return;
    if (B(self, 0x178) != 0 || B(self, 0x17f) != 0 || B(other, 0x17b) != 0)
        return;
    void* r = cells()->Get(I(self, 0));
    float f = FUN_00e6d200(r, 0, 0x31, I(r, 0x1b0));
    int mh = msgs()->Alloc();
    cCellMessage* m = (cCellMessage*)msgs()->Get(mh);
    m->f1c = f;
    m->f20 = f;
    m->type = 0x20;
    m->a28 = I(self, 0);
    m->a2c = 0;
    m->a30 = -1;
    m->a34 = -1;
    m->a38 = 0;
    m->a3c = 0;
    m->f40 = 0.0f;
    m->f44 = 0.0f;
    m->v48.x = gCellWorldCenter.x;
    m->v48.y = gCellWorldCenter.y;
    m->v48.z = gCellWorldCenter.z;
    m->v54.x = gCellWorldCenter.x;
    m->v54.y = gCellWorldCenter.y;
    m->v54.z = gCellWorldCenter.z;
    m->v60.x = g_15a7c4c[0];
    m->v60.y = g_15a7c4c[1];
    m->v60.z = g_15a7c4c[2];
    m->a6c = (int)g_15a7c4c[3];
    m->a70 = 0;
    m->b74 = 0;
    m->a78 = 0;
    m->cb = 0;
    m->st8 = 0;
    {
        char buf[0x18];
        FUN_00743b50(buf);
        void* def = FUN_00e4cc40(I(other, 0x108), buf);
        FUN_00e5d7b0(I(def, 0xb8));
        FUN_00e780a0(I(other, 0), 1, 0.0f, 0);
        FUN_00e59a70(I(self, 0));
        FUN_00e82130(buf);
    }
}

// ------------------------------------------------------------------ 0x00e7b7c0
// Original: the occupancy list in EAX, pos in EBX, the cell in ESI, t on the stack.
// Record a cell as spawned, drop its pieces, then fire its drop event.
// @ 0x00e7b7c0
void FUN_00e7b7c0(void* list, void* x, void* pos, float t)
{
    int* r = ((cOccupancy*)list)->Claim();
    *r = I(x, 0);
    if (I(x, 0) == I(gspCellGame, 0x516c))
        return;
    if (I(x, 0xfc) != 0) {
        FUN_00e77ac0(x, pos, FUN_00e4cce0(7), t);
    } else {
        char buf[0x18];
        FUN_00743b50(buf);
        void* def = FUN_00e4cc40(I(x, 0x108), buf);
        FUN_00e77ac0(x, pos, P(def, 0xd8), t);
        FUN_00e82130(buf);
    }
    int key = 0xf620401c;
    FUN_00e61b90(I(x, 0x35c) != I(gspCellGame, 0x40fc), 0, (char*)x + 0x4c, &key);
    FUN_00e780a0(I(x, 0), 1, t, 0);
}

// ------------------------------------------------------------------ 0x00e7b8a0
// Original: first float in XMM0, record pointer and second float on the stack.
// Query nearby cells and drop the pieces of each not already in the record's list.
// @ 0x00e7b8a0
int FUN_00e7b8a0(void* p, float a, float b)
{
    int buf[0x200];
    int n = FUN_00e87260(I(p, 0), (char*)p + 4, (0.5f - (a + b)) * 15.0f, buf, 0x200, 0);
    for (int i = 0; i < n; i++) {
        int key = buf[i];
        int* base = (int*)I(p, 0x10);
        int* end = (int*)I(p, 0x14);
        int* it = base;
        int cnt = (int)((char*)end - (char*)base) >> 3;
        while (cnt > 0) {
            int half = cnt >> 1;
            int* mid = it + half * 2;
            if (*mid < key) {
                it = mid + 2;
                cnt -= half + 1;
            } else {
                cnt = half;
            }
        }
        if (it != end && key >= *it)
            continue;
        FUN_00e7b7c0((char*)p + 0x10, cells()->Get(key), (char*)p + 4, b);
    }
    return 1;
}

// ------------------------------------------------------------------ 0x00e7b9b0
// @ 0x00e7b9b0
void FUN_00e7b9b0(int hA, int hB, float t)
{
    FUN_00e780a0(hB, 1, t, 0);
    void* c = cells()->GetSafe(hA);
    if (c != 0) {
        if (I(c, 0x168) != 0) {
            FUN_00e59200(P(c, 0x168));
            I(c, 0x168) = 0;
        }
        I(c, 0x220) = I(gspCellGame, 0x411c);
        F(c, 0x21c) = 300.0f;
    }
}

// ------------------------------------------------------------------ 0x00e7ba30
// Original: subject in EAX, t on the stack.  Dispatch one cCellMessage action.
// @ 0x00e7ba30
int FUN_00e7ba30(void* m, float t)
{
    switch (I(m, 0x24)) {
    case 1:
        FUN_00e69a90(I(m, 0x28), I(m, 0x2c), I(m, 0x30), I(m, 0x38), F(m, 0xc), t);
        break;
    case 2:
        FUN_00e59010(I(m, 0x28), I(m, 0x2c), I(m, 0x38), F(m, 0xc) <= 0.0f,
                     F(m, 0x20) - F(m, 0x1c), (char*)m + 0x48);
        break;
    case 3:
        FUN_00e76360((char*)m + 0x28, I(m, 0x38), I(m, 0x70), I(m, 0x3c),
                     (char*)m + 0x48, (char*)m + 0x54, (char*)m + 0x60, I(m, 0x40),
                     F(m, 0x20) - F(m, 0x1c), I(m, 0x44), I(m, 0x78), t);
        break;
    case 4:
        FUN_00e59560(I(m, 0x2c), I(m, 0x30));
        break;
    case 5:
        FUN_00e59260(I(m, 0x28));
        break;
    case 6:
        FUN_00e59170(I(m, 0x28), t);
        break;
    case 7:
        FUN_00e59500(I(m, 0x28));
        break;
    case 8:
        FUN_00e57c30(I(m, 0x28), I(m, 0x2c), I(m, 0x38), t);
        break;
    case 9:
        FUN_00e57a60(I(m, 0x28), I(m, 0x2c), I(m, 0x30), I(m, 0x38), (char*)m + 0x48);
        break;
    case 10:
        FUN_00e592f0(I(m, 0x28), I(m, 0x2c), I(m, 0x30), (char*)m + 0x48, (char*)m + 0x54);
        break;
    case 11:
        FUN_00e57b50(I(m, 0x28), I(m, 0x30), I(m, 0x38), (char*)m + 0x48);
        break;
    case 12:
        FUN_00e579c0(I(m, 0x28), I(m, 0x2c));
        break;
    case 13:
        FUN_00e57c90(I(m, 0x28), I(m, 0x2c));
        break;
    case 14:
        FUN_00e593b0(I(m, 0x28), I(m, 0x2c), I(m, 0x30), (char*)m + 0x48);
        break;
    case 15:
        FUN_00e599b0(I(m, 0x28));
        break;
    case 16:
        FUN_00e7b8a0((char*)m + 0x70, F(m, 0x1c), t);
        break;
    case 17:
        FUN_00e58890(I(m, 0x28), I(m, 0x2c), I(m, 0x30));
        break;
    case 18:
        FUN_00e69e00(I(m, 0x28), I(m, 0x2c), I(m, 0x30), F(m, 0xc), t);
        break;
    case 19:
        FUN_00e69c10(I(m, 0x28), I(m, 0x2c), I(m, 0x30), F(m, 0xc), t);
        break;
    case 20:
        FUN_00e59710(I(m, 0x28), I(m, 0x2c), I(m, 0x30), F(m, 0xc), F(m, 0x10), t);
        break;
    case 21:
        FUN_00e59640(I(m, 0x28), I(m, 0x2c), I(m, 0x30), I(m, 0x38), (char*)m + 0x48);
        break;
    case 25:
        FUN_00e58ae0(I(m, 0x28));
        break;
    case 26:
        FUN_00e58bf0(I(m, 0x28), F(m, 0x20) - F(m, 0x1c), F(m, 0x20));
        break;
    case 27:
        FUN_00e5ec70(I(m, 0x28), F(m, 0x1c));
        break;
    case 28:
        FUN_00e5ec10(I(m, 0x28));
        break;
    case 29:
        FUN_00e591c0(I(m, 0x28), t);
        break;
    case 30:
        FUN_00e598e0(I(m, 0x28), F(m, 0x1c));
        break;
    case 31:
        FUN_00e59a30();
        break;
    case 32:
        FUN_00e59a70(I(m, 0x28));
        break;
    case 33:
        FUN_00e571f0(I(m, 0x28), I(m, 0x38));
        break;
    case 34:
        FUN_00e5ed50(I(m, 0x28), (char*)m + 0x48, (char*)m + 0x60, F(m, 0x1c), F(m, 0x20));
        break;
    case 36:
        FUN_00e5f160(I(m, 0x28), I(m, 0x2c), m, t);
        break;
    case 38:
        FUN_00e59b50(I(m, 0x28), I(m, 0x30), (char*)m + 0x48);
        break;
    case 39:
        FUN_00e59af0(I(m, 0x28), I(m, 0x30));
        break;
    case 40:
        FUN_00e59af0(I(m, 0x28), I(m, 0x30));
        break;
    case 41:
        FUN_00e6a090(I(m, 0x28), I(m, 0x2c), I(m, 0x30), F(m, 0xc), t);
        break;
    case 42:
        FUN_00e59470(I(m, 0x28));
        break;
    case 43:
        FUN_00e532e0((char*)m + 0x74, F(m, 0x20) - F(m, 0x1c));
        break;
    case 44:
        FUN_00e56820(F(m, 0x20) - F(m, 0x1c), F(m, 0x20));
        break;
    case 45:
        FUN_00e75c30(t);
        break;
    case 46:
        FUN_00e53d50(F(m, 0x20) - F(m, 0x1c), F(m, 0xc));
        break;
    case 47:
        FUN_00e53c70(m, F(m, 0x1c), t);
        break;
    case 48:
        FUN_00e569b0();
        break;
    case 49:
        FUN_00e569b0();
        break;
    case 50:
        FUN_00e57dc0(I(m, 0x28));
        break;
    default:
        break;
    }
    return 1;
}
