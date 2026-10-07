// Slice s00d522c0: SP::cSpaceInventoryItem / cPosseSimulator helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast
#include "types.h"

// ---- external module entry points ----
extern "C" void* __cdecl FUN_00b3d300();          // 0xb3d300
extern "C" int*  __cdecl FUN_00b1f9c0();         // GetItemID (thiscall body)
extern "C" int*  __cdecl FUN_00b1fdb0();         // GetAvatar (thiscall body)
extern "C" int   __cdecl FUN_00d52df0();
extern float     g_145c4ac;

// ===========================================================================
// @ 0x00d52c90  __cdecl compare by float at +8
// ===========================================================================
extern "C" int __cdecl F52c90(int a, int b)
{
    return *(float*)(b + 8) > *(float*)(a + 8);
}

// ===========================================================================
// @ 0x00d52cb0  __cdecl heap-sift (adjust) with comparator
// ===========================================================================
typedef char (__cdecl* Cmp)(int, int);

void __cdecl F52cb0(int* arr, int start, int hole, int value, Cmp cmp)
{
    if (hole <= start) {
        arr[hole] = value;
        return;
    }
    int parent;
    do {
        parent = (hole - 1) >> 1;
        if (!cmp(arr[parent], value))
            break;
        arr[hole] = arr[parent];
        hole = parent;
    } while (start < parent);
    arr[hole] = value;
}

// ===========================================================================
// @ 0x00d52d80  SP::cPosseSimulator::Write
// ===========================================================================
void __fastcall F52d80(void* self, int, int* stream)
{
    (void)self; (void)stream;
}

// ===========================================================================
// @ 0x00d52df0  inventory item count
// ===========================================================================
int __fastcall F52df0(void* self)
{
    void* m = FUN_00b3d300();
    int* v = ((int*(__thiscall*)(void*))FUN_00b1f9c0)(m);
    return ((v[1] - v[0]) >> 2) - *(int*)((char*)self + 0x1c);
}

// ===========================================================================
// @ 0x00d52e10  avatar lookup
// ===========================================================================
int __fastcall F52e10(void* self)
{
    int result = 0;
    void* m = FUN_00b3d300();
    int r = ((int(__thiscall*)(void*))FUN_00b1fdb0)(m);
    if (r != 0) {
        int* p = (int*)((char*)self + 0x18);
        if (*(unsigned int*)((char*)self + 0x18) > 3)
            p = (int*)&g_145c4ac;
        result = *p;
    }
    return result;
}

// ===========================================================================
// @ 0x00d52e40  notify all inventory items
// ===========================================================================
void __fastcall F52e40(void* self, int, int arg)
{
    (void)self; (void)arg;
}

// ===========================================================================
// @ 0x00d522c0  SP::cSPDramaManager::Update(uint64 t)  thiscall, ret 8
// ===========================================================================
#define FLD(T, p, off) (*(T*)((char*)(p) + (off)))

extern "C" int   __cdecl FUN_00b5b800();                          // 0xb5b800
extern "C" void* __cdecl FUN_00b3d300();                                 // 0xb3d300
extern "C" void* __cdecl FUN_00d539d0();
extern "C" void* __cdecl FUN_00b3d4c0();                              // 0xb3d4c0
extern "C" void* __cdecl FUN_00b3d4d0();                              // 0xb3d4d0                               // 0xd539d0
extern "C" void* __cdecl FUN_00b3d350();                              // 0xb3d350
extern "C" void* __cdecl FUN_0067dd10();                                      // 0x67dd10
extern "C" void* __cdecl FUN_00ac8960(void* p);                          // 0xac8960
extern "C" void* __cdecl FUN_00b60a50(void* p);                         // 0xb60a50
extern "C" void* __cdecl FUN_00d40b40(int);                              // 0xd40b40
extern "C" void* __cdecl FUN_00d99500(int handle);                          // 0xd99500
extern "C" void* __cdecl GetStalkerCell(int handle);                    // 0xd99500 (same callee, cell form)
extern "C" void  FUN_00d52df0_unused();
extern "C" void* __cdecl FUN_00449c20(void* out, void* v);            // 0x449c20
extern "C" void  FUN_00cd7d10(); extern "C" void FUN_00d3d420();
extern "C" void  FUN_00accc30(); extern "C" void FUN_00b1e500();
extern "C" void* __cdecl ClassifyNoun(void* s, void* a, void* b);       // unused alias

// thiscall callees (ecx = this, dummy edx)
extern "C" int    __fastcall FUN_00d4b860_unused(void*, int);
extern "C" void   __fastcall FUN_00d4b860(void* self, int, float f);   // 0xd4b860
extern "C" void   __fastcall FUN_00d4e4a0(void* self, int, float f);           // 0xd4e4a0
extern "C" int    __fastcall FUN_00d4b2f0(void* self, int, void* obj);         // 0xd4b2f0
extern "C" void   __fastcall FUN_00d4b1d0(void* self, int, void* obj);           // 0xd4b1d0
extern "C" int    __fastcall FUN_00d4cad0(void* self, int, int a, int b);   // 0xd4cad0
extern "C" float  __fastcall PosseFloat(void* self, int);                     // 0xd2e360 (ignored)
extern "C" int    __fastcall FUN_00c0b770(void* o, int);                          // 0xc0b770 (bool)
extern "C" int    __fastcall FUN_00c04590(void* o, int);                           // 0xc04590
extern "C" int    __fastcall FUN_00c02c70(void* o, int);                           // 0xc02c70
extern "C" unsigned char __fastcall FUN_00c6a020(void* o, int);                    // 0xc6a020
extern "C" float* __fastcall FUN_00c6acc0(void* o, int);                            // 0xc6acc0
extern "C" void   __fastcall FUN_00b5f950(void* cell, int, void* obj);       // 0xb5f950
extern "C" int*   __fastcall FUN_00b21340(void* nm, int, void* a, void* b, void* c, void* d, unsigned e); // 0xb21340
extern "C" void   __fastcall FUN_00b41a40(void* it, int, void* range, void* unused);  // 0xb41a40
extern "C" void   __fastcall FUN_00b3d850(void* it, int);                       // 0xb3d850
extern "C" int    __fastcall FUN_00ba3f90(void* s, int, void* a, void* b, void* c); // 0xba3f90
extern "C" void   __fastcall FUN_00b82970(void* pm, int, float* out, void* pos, int zero); // 0xb82970
extern "C" void   __fastcall FUN_00bc97f0(void* obj, int, int a, unsigned b, float f, int d);       // 0xbc97f0
extern "C" void*  __fastcall FUN_00d20600(void* o, int);                               // 0xd20600
extern "C" void*  __fastcall FUN_0108db30(void* o, int);                              // 0x108db30
extern "C" void*  __cdecl FUN_00c099e0(void* out, void* avatarPos, int, void* herd, int, int); // 0xc099e0

// vtable helpers
static void RefAddRef(void* o)  { if (o) ((void(__fastcall*)(void*, int))((void**)*(void**)o)[0])(o, 0); }
static void RefRelease(void* o) { if (o) ((void(__fastcall*)(void*, int))((void**)*(void**)o)[1])(o, 0); }
// virtual pos accessor: thiscall on the address of the AutoRef-like slot, slot 0x2c
static float* VirtPosAt(void* addr)
{
    void* obj = *(void**)addr;
    return ((float*(__fastcall*)(void*, int))((void**)*(void**)obj)[0x2c / 4])(addr, 0);
}
static float Dist2(const float* a, const float* b)
{
    float d0 = a[0] - b[0];
    float d1 = a[1] - b[1];
    float d2 = a[2] - b[2];
    return (d0 * d0 + d2 * d2) + d1 * d1;
}
#define LOADF(p, off) (*(float*)((char*)(p) + (off)))

extern "C" float __cdecl FUN_00d2e360();                                // 0xd2e360 (float, discarded)

static void* VCall0(void* obj, int off)
{
    return ((void*(__fastcall*)(void*, int))((void**)*(void**)obj)[off / 4])(obj, 0);
}

// 0xd52c0a: mate-reset path (clear flags, release mate, timer = 5.0)
static void MateResetPath(void* self, void** mateSlot)
{
    (void)self;
    void* m = *mateSlot;
    if (!m)
        return;
    *(unsigned*)((char*)m + 0xb58) &= ~0x10u;
    char* b4c = *(char**)((char*)m + 0xb4c);
    *(unsigned*)(b4c + 0x5fc) &= ~0x4000u;
    if (m != *mateSlot)
        return;
    void* old = *mateSlot;
    if (old) {
        *mateSlot = 0;
        RefRelease(old);
    }
    *(float*)((char*)mateSlot + 4) = 5.0f;     // mCheckForMateTimer (+0x3c)
}

// 0xd52a54 / 0xd52a6f: set 0x4000 on mate->+0xb4c->+0x5fc and 0x10 on mate->+0xb58
static void PostMateFlags(void** mateSlot)
{
    void* m = *mateSlot;
    if (!m)
        return;
    char* b4c = *(char**)((char*)m + 0xb4c);
    *(unsigned*)(b4c + 0x5fc) |= 0x4000u;
    *(unsigned*)((char*)m + 0xb58) |= 0x10u;
}

// 0xd527b5 .. 0xd52908 and placement: timer branch when state == 2
static void MateTimerBody(void* self, void* avatar, void** mateSlot, float fDt)
{
    float* timer = (float*)((char*)mateSlot + 4);
    if (*timer > 0.0f) {
        *timer -= fDt;
        return;
    }
    *timer = 5.0f;

    void* herd = FUN_00d40b40(1);
    int flag = (*mateSlot == 0);
    float* hp = FUN_00c6acc0(herd, 0);

    void* mateNow = *mateSlot;
    bool skipFlagCheck = false;
    if (mateNow != 0) {
        if ((void*)(size_t)FUN_00c04590(mateNow, 0) != herd) {
            FUN_00d4b1d0(self, 0, mateNow);
            skipFlagCheck = true;
        }
    }
    if (!skipFlagCheck && flag == 0)
        return;

    float dFar = Dist2(hp, (float*)0x167ea30);
    if (!(10000.0f > dFar))
        return;

    char** cur = *(char***)((char*)herd + 0x40);
    char** end = *(char***)((char*)herd + 0x44);
    for (; cur != end; ++cur) {
        void* cell = *cur;
        if (FUN_00d4b2f0(self, 0, cell)) {
            float* cp = VirtPosAt((char*)cell + 0xc0);
            float dd = Dist2(cp, hp);
            if (225.0f > dd) {
                FUN_00b5f950(mateSlot, 0, cell);
                break;
            }
        }
    }

    if (*mateSlot != 0)
        return;

    // Herd placement: result is only used for the gate, the mate pick follows.
    void* app = FUN_0067dd10();
    void* r = VCall0(app, 0x50);
    void* s = VCall0(r, 0x38);
    void* av2 = FUN_00b60a50(s);
    if (av2 != 0) {
        float* p48 = (float*)FUN_00d20600(av2, 0);
        float vout[3];
        FUN_00b82970(FUN_00b3d350(), 0, vout, p48, 0);
        if (625.0f > Dist2(vout, hp)) {
            float tmp[3];
            float* n = (float*)FUN_00449c20(tmp, FUN_0108db30(av2, 0));
            (void)n;
        }
    }

    void* avatarId = (void*)(size_t)*(int*)((char*)avatar + 0xb20);
    float out[3];
    void* pick = FUN_00c099e0(out, avatarId, 1, herd, 0, 1);
    FUN_00b5f950(mateSlot, 0, pick);
}

// 0xd52a9c: state 1 (mate pick from avatar range, else mate pick from FUN_0108db30 diff)
static void MateCaseOne(void* self, void* avatar, void** mateSlot)
{
    if (*mateSlot != 0) {
        *(unsigned*)((char*)*mateSlot + 0xb58) |= 0x10u;
        return;
    }
    char* it[2];
    unsigned unused = 0;
    FUN_00b41a40(it, 0, (char*)avatar + 0x1124, &unused);
    if (it[0] != it[1]) {
        do {
            void* cand = FUN_00ac8960(*(void**)(*(char**)it[0] + 8));
            if (FUN_00d4b2f0(self, 0, cand)) {
                FUN_00b5f950(mateSlot, 0, cand);
                *(unsigned*)((char*)*mateSlot + 0xb58) |= 0x10u;
                break;
            }
            FUN_00b3d850(it, 0);
        } while (it[0] != it[1]);
    }
    if (*mateSlot != 0)
        return;

    void* app = FUN_0067dd10();
    void* r = VCall0(app, 0x50);
    void* s = VCall0(r, 0x38);
    void* av2 = FUN_00b60a50(s);
    if (!av2)
        return;
    float tmp[3];
    float* n = (float*)FUN_00449c20(tmp, FUN_0108db30(av2, 0));
    float vec2[3] = { n[0] * 2.0f, n[1] * 2.0f, n[2] * 2.0f };
    float* p = (float*)FUN_00d20600(av2, 0);
    float D[3] = { p[0] - vec2[0], p[1] - vec2[1], p[2] - vec2[2] };
    void* mm = (void*)(size_t)FUN_00c04590(avatar, 0);
    void* avatarId = (void*)(size_t)*(int*)((char*)avatar + 0xb20);
    void* pick = FUN_00c099e0(D, avatarId, 1, mm, 1, 0);
    FUN_00b5f950(mateSlot, 0, pick);
    *(unsigned*)((char*)*mateSlot + 0xb58) |= 0x10u;
}

// Frame-literal mirror of asm: keeps the same stack-slot roles for the stalker search.
void __fastcall FUN_00d522c0(void* self, int, unsigned long long t)
{
    char* S = (char*)self;
    float fDt = (float)t * 0.001f;
    int mode = FUN_00b5b800();
    if (mode != 0x1654c01) {
        if (mode == 0x1654c02)
            FUN_00d4e4a0(self, 0, fDt);
        return;
    }

    void* avatar = ((void*(__fastcall*)(void*, int))FUN_00b1fdb0)(FUN_00b3d300(), 0);
    if (!avatar)
        return;

    void* posse = FUN_00d539d0();
    if ((int)F52df0(posse) > 0)
        FUN_00d4b860(self, 0, fDt);

    if (S[0x10] != 0 && FUN_00d99500(*(int*)(S + 0x4c)) == 0) {
        // Drop the current stalker, then search the avatar range for a new one.
        void* old = *(void**)(S + 0x4c);
        *(void**)(S + 0x4c) = FUN_00d99500(*(int*)(S + 0x4c)); // eax == 0 here
        RefRelease(old);

        char* it[2];                       // PosseIter-like {cur, end}
        unsigned unused = 0;
        FUN_00b41a40(it, 0, (char*)avatar + 0x1124, &unused);
        if (it[0] != it[1]) {
            do {
                char* elem = *(char**)it[0];
                void* cand = FUN_00d99500(*(int*)(elem + 8));
                if (cand && *(int*)((char*)cand + 0xb20) != *(int*)((char*)avatar + 0xb20) &&
                    FUN_00c0b770(cand, 0)) {
                    void* sing = FUN_00b3d4c0();
                    if (FUN_00ba3f90(sing, 0, (char*)cand + 0xb28, avatar, cand) == 3) {
                        FUN_00b5f950(S + 0x4c, 0, cand);
                        char* st = *(char**)(S + 0x4c);
                        FUN_00bc97f0(*(char**)(st + 0xb4c) + 8, 0, 0, 0x80000000u, 3.402823466e38f, 0);
                        break;
                    }
                }
                FUN_00b3d850(it, 0);
            } while (it[0] != it[1]);
        }

        if (*(void**)(S + 0x4c) == 0) {
            // Nearest-candidate search over the game-data vector.
            float bestDist = 3.402823466e38f;
            void* best = 0;
            int* gv = FUN_00b21340(FUN_00b3d300(), 0, (void*)FUN_00cd7d10,
                                     (void*)FUN_00d3d420, (void*)FUN_00accc30,
                                     (void*)FUN_00b1e500, 0x1be418e);
            char** cur = (char**)gv[1];
            char** end = (char**)gv[2];
            for (; cur != end; ++cur) {
                char* cell = *cur;
                if (!FUN_00c6a020(cell, 0))
                    continue;
                if (*(char**)(cell + 0x40) == *(char**)(cell + 0x44))
                    continue;
                if (*(int*)(cell + 0x98) != *(int*)((char*)avatar + 0xb28) ||
                    *(int*)(cell + 0x9c) != *(int*)((char*)avatar + 0xb2c) ||
                    *(int*)(cell + 0xa0) != *(int*)((char*)avatar + 0xb30)) {
                    void* last = *(void**)(*(char**)(cell + 0x44) - 4);
                    void* sing = FUN_00b3d4c0();
                    if (FUN_00ba3f90(sing, 0, cell + 0x98, avatar, last) != 3)
                        continue;
                } else {
                    continue;
                }
                float* cp = FUN_00c6acc0(cell, 0);
                float* ap = VirtPosAt((char*)avatar + 0xc0);
                float dist = Dist2(ap, cp);
                if (best == 0 || dist < bestDist) {
                    best = cell;
                    bestDist = dist;
                }
            }
            if (best) {
                // Second pass: pick the closest flagged entry in best's vector.
                char** cur2 = (char**)*(char**)((char*)best + 0x40);
                char** end2 = (char**)*(char**)((char*)best + 0x44);
                void* pick = 0;
                float pickDist = 3.402823466e38f;
                for (; cur2 != end2; ++cur2) {
                    void* cand = FUN_00d99500(*(int*)cur2);
                    if (cand && FUN_00c0b770(cand, 0)) {
                        float* cp = VirtPosAt((char*)cand + 0xc0);
                        float* ap = VirtPosAt((char*)avatar + 0xc0);
                        float dist = Dist2(ap, cp);
                        if (pick == 0 || pickDist > dist) {
                            pick = cand;
                            pickDist = dist;
                        }
                    }
                }
                if (pick) {
                    void* old2 = *(void**)(S + 0x4c);
                    if (pick != old2) {
                        RefAddRef(pick);
                        *(void**)(S + 0x4c) = pick;
                        RefRelease(old2);
                    }
                    char* st = *(char**)(S + 0x4c);
                    FUN_00bc97f0(*(char**)(st + 0xb4c) + 8, 0, 0, 0x80000000u, 3.402823466e38f, 0);
                }
            }
        }
    }

    // ---- tail: posse update, then mate logic keyed on posse state ----
    FUN_00d4e4a0(self, 0, fDt);

    void** mateSlot = (void**)(S + 0x38);
    void* mateSrc = (void*)(size_t)FUN_00c04590(avatar, 0);
    bool gateOk = (FUN_00c0b770(avatar, 0) != 0) &&
                  (*(unsigned char*)((char*)avatar + 0xb5e) == 0) &&
                  (*(int*)((char*)mateSrc + 0x160) != 0);
    if (gateOk) {
        void* pm = FUN_00b3d4d0();
        int ev = *(int*)((char*)pm + 0x2c);
        if (ev == 1 || ev == 2)
            gateOk = false;
    }
    if (gateOk && FUN_00d4cad0(self, 0, 3, 1) != 0)
        gateOk = false;
    if (!gateOk) {
        MateResetPath(self, mateSlot);
        return;
    }

    (void)FUN_00d2e360();
    int state = (FUN_00c02c70(avatar, 0) > 0) ? 0 : 2;

    if (*mateSlot != 0) {
        if (!FUN_00d4b2f0(self, 0, *mateSlot) ||
            ((*(unsigned*)((char*)*mateSlot + 0xb58) >> 4) & 1) == 0)
            FUN_00d4b1d0(self, 0, *mateSlot);
    }

    if (state == 1) {
        MateCaseOne(self, avatar, mateSlot);
        return;
    }
    if (state != 2)
        return;
    MateTimerBody(self, avatar, mateSlot, fDt);
    PostMateFlags(mateSlot);
}
