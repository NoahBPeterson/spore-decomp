// ===========================================================================
// slice s01001700 -- registry / entry-container cluster (module 0x0100xxxx).
// Reconstructed from work/SporeApp.analysis.bin.
//
//   0x01001700  FUN_01001700   unlink an entry by key + property push
//   0x010019a0  FUN_010019a0   per-frame scalar refresh
//   0x01001b60  FUN_01001b60   find the nearest entry within a radius
//   0x01001cd0  FUN_01001cd0   per-frame target / clearage update
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
// ===========================================================================

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#pragma warning(disable: 4100 4189 4244 4311 4312 4244)

#include <math.h>

// ---- cdecl / free callees ------------------------------------------------
void  FUN_00f47380(void* p);                          // 0x00f47380
u32   FUN_01021090();                                 // 0x01021090
u32   FUN_01021080();                                 // 0x01021080
void* FUN_01021300();                                 // 0x01021300
void* FUN_01021260();                                 // 0x01021260
void* FUN_010066a0(void* p);                          // 0x010666a0
void* FUN_01002bd0(u32 n);                            // 0x01002bd0
void* FUN_0102f810(u32 a, u32 b);                     // 0x0102f810
void* FUN_00ebbb40(void* pOut);                       // 0x00ebbb40
void* FUN_00c37360();                                 // 0x00c37360
void* FUN_0067dd10();                                 // 0x0067dd10
void* FUN_00a206f0();                                 // 0x00a206f0
void* FUN_00b3d300();                                 // 0x00b3d300  global manager E
void* FUN_00b3d2a0(u32 a);                            // 0x00b3d2a0
void* FUN_00b3d380();                                 // 0x00b3d380
bool  FUN_0102af80(void* a, void* b);                 // 0x0102af80
u8    FUN_00cb6960(void* a, void* b, void* c, void* d, void* e,
                   void* f, void* g, void* h);        // 0x00cb6960

// ---- thiscall callees (ecx = the receiver passed as pSelf) ----------------
struct CalleeSet {
    void* FUN_00c71e30();                             // 0x00c71e30
    u32   FUN_01030b70();                             // 0x01030b70
    void  FUN_00c31a00(int n);                        // 0x00c31a00
    void  FUN_00bfd1a0(float f);                      // 0x00bfd1a0
    void* FUN_01005180();                             // 0x01005180
    void  FUN_007eb820(int n);                        // 0x007eb820
    void  FUN_00c3bfe0(void* pOut);                   // 0x00c3bfe0
    void  FUN_00c37270();                             // 0x00c37270
    void* FUN_00f67d90();                             // 0x00f67d90
    u8    FUN_00c75620();                             // 0x00c75620
    void  FUN_00c755f0();                             // 0x00c755f0
    void* FUN_00b21340(void* a, void* b, void* c, void* d, void* e);  // 0x00b21340
    void* FUN_00ba9370();                             // 0x00ba9370
    void* FUN_00a1ad60();                             // 0x00a1ad60
    void* FUN_00ff3f00();                             // 0x00ff3f00
    u8    FUN_0104cce0();                             // 0x0104cce0
    void  FUN_00ffc2e0(u32 a);                        // 0x00ffc2e0
    float FUN_00c37430();                             // 0x00c37430
    float FUN_0102a450();                             // 0x0102a450
    void  FUN_00ffd710(u32 a, u32 b);                 // 0x00ffd710
    void  FUN_00ffc330();                             // 0x00ffc330
    u32   FUN_0102fbf0();                             // 0x0102fbf0
    float FUN_0102fc60();                             // 0x0102fc60
    void  FUN_00c389f0(float f);                      // 0x00c389f0
    void  FUN_01000eb0();                             // 0x01000eb0
    void  FUN_01000dc0();                             // 0x01000dc0
    void  FUN_010682a0();                             // 0x010682a0
    void  FUN_007c4900(void* a, void* b);             // 0x007c4900
};
#define SELF(o) ((CalleeSet*)(o))

// ---- vtable dispatch through a member pointer (thiscall) ------------------
struct VtblObj {
    void  C0(); void  C1(void*); void  C2(void*, void*); void  C3(void*, void*, void*);
    void* R0(); void* R1(void*); void* R2(void*, void*); void* R3(void*, void*, void*);
    u8    B0(); float FR0(); float FR1(void*);
};
typedef void  (VtblObj::*PMF0)();
typedef void  (VtblObj::*PMF1)(void*);
typedef void* (VtblObj::*PMR0)();
typedef void* (VtblObj::*PMR1)(void*);
typedef void* (VtblObj::*PMR2)(void*, void*);
typedef void* (VtblObj::*PMR3)(void*, void*, void*);
typedef u8    (VtblObj::*PMB0)();
typedef float (VtblObj::*PMFR0)();

inline void  VCall1(void* p, u32 o, void* a)                  { (((VtblObj*)p)->*(*(PMF1*)((u8*)*(void**)p + o)))(a); }
inline void* VRet0(void* p, u32 o)                            { return (((VtblObj*)p)->*(*(PMR0*)((u8*)*(void**)p + o)))(); }
inline void* VRet1(void* p, u32 o, void* a)                   { return (((VtblObj*)p)->*(*(PMR1*)((u8*)*(void**)p + o)))(a); }
inline void* VRet2(void* p, u32 o, void* a, void* b)          { return (((VtblObj*)p)->*(*(PMR2*)((u8*)*(void**)p + o)))(a, b); }
inline u8    VBool0(void* p, u32 o)                           { return (((VtblObj*)p)->*(*(PMB0*)((u8*)*(void**)p + o)))(); }
inline float VFRet0(void* p, u32 o)                           { return (((VtblObj*)p)->*(*(PMFR0*)((u8*)*(void**)p + o)))(); }

struct Vec3 { float x, y, z; };

// a doubly-linked list node in the +0x70 registry ring
struct ListNode { ListNode* pNext; ListNode* pPrev; u32 mKey; };

// the registry / container object this cluster lives on
struct CReg {
    u8      mGap00[0x40];
    void*   mp40;              // +0x040
    u8      mGap44[0x2c];
    void*   mp70;              // +0x070  registry ring sentinel
    u8      mGap74[0x58];
    u32     mWcc;              // +0x0cc
    void*   mpD0;              // +0x0d0
    void*   mpD4;              // +0x0d4
    void*   mpD8;              // +0x0d8
    void*   mpDc;              // +0x0dc

    void  FUN_01001700(u32 key, u8 flag);
    void  FUN_010019a0();
    void* FUN_01001b60();
    void  FUN_01001cd0(u32 a, float b);
};

// fields reached through an entry pointer
struct Entry {
    u8      mGap00[0x68c];
    u32     mW68c;             // +0x68c
    u8      mGap690[0x84];
    u32     mW714;             // +0x714
};

// @ 0x01001700
void CReg::FUN_01001700(u32 key, u8 flag)
{
    ListNode* head = (ListNode*)mp70;
    ListNode* e = head->pNext;
    if (e == head)
        return;

    for (;;) {
        if (e->mKey == key) {
            ListNode* nx = e->pNext;
            ListNode* pv = e->pPrev;
            pv->pNext = nx;
            nx->pPrev = pv;
            FUN_00f47380(e);

            if (key == FUN_01021090()) {
                if (SELF(SELF(FUN_00b3d300())->FUN_00f67d90())->FUN_00c75620())
                    SELF(SELF(FUN_00b3d300())->FUN_00f67d90())->FUN_00c755f0();
            }

            void* vec = SELF(FUN_00b3d300())->FUN_00b21340(
                (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00ad48b0,
                (void*)0x00b1e500, (void*)0x018ebadc);
            void** pBeg = (void**)((u8*)vec + 4);
            int n = (int)(((u8*)*(void**)((u8*)vec + 8) - (u8*)*pBeg) >> 2);
            if (n <= 0)
                return;
            for (int i = 0; i < n; ++i) {
                void* en = *(void**)((u8*)(*pBeg) + i * 4);
                if (*(u32*)((u8*)en + 0x714) != 3)
                    continue;
                if ((u32)(size_t)VRet0(en, 0x4c) != key)
                    continue;

                SELF(FUN_010066a0(en))->FUN_010682a0();

                void* m = FUN_00b3d2a0((u32)(size_t)VRet0(en, 0x4c));
                void* esi = SELF(m)->FUN_00ba9370();
                u32 ebx = 0;
                u32 st = *(u32*)((u8*)esi + 0x58);
                switch (st) {
                case 0: ebx = 0xcb19e4c0; break;
                case 1: ebx = 0xba635bd9; break;
                case 2: ebx = 0x65e635e8; break;
                case 3: ebx = 0x9f662d7f; break;
                case 4: ebx = 0xe9456f91; break;
                case 5: ebx = 0xe5113ad8; break;
                case 6: ebx = 0x1354f721; break;
                case 7: ebx = 0x6e53f191; break;
                case 8: ebx = 0x76e772d8; break;
                default:
                    if (esi == (void*)(size_t)FUN_01021300())
                        ebx = 0xa90fb3de;
                    break;
                }

                void* a = FUN_00a206f0();
                void* ebp = a ? VRet0(a, 0x20) : 0;
                if (flag == 0) {
                    void* s2 = FUN_00a206f0();
                    if (s2) {
                        VRet1(s2, 0x38, (void*)0x03475365);
                        VRet2(s2, 0x40, (void*)0x03475381, (void*)ebx);
                        VRet2(s2, 0x40, (void*)0x03475385, ebp);
                        VRet0(s2, 0x58);
                    }
                }

                Entry* ent = (Entry*)en;
                u32 c = ent->mW68c;
                if (c) {
                    ent->mW68c = 0;
                    VRet0((void*)(size_t)c, 4);
                }
                ent->mW714 = 6;

                u32 mm = FUN_01021080();
                if (!mm) {
                    SELF(en)->FUN_00c37270();
                } else if (mm - 1 <= 1) {
                    float loc[2] = { 0.0f, 0.0f };
                    FUN_00ebbb40(loc);
                    float k = *(float*)0x015b6250;
                    Vec3 out;
                    out.x = k * loc[0];
                    out.y = k * loc[1];
                    out.z = k * *(float*)0x01485378;
                    SELF(en)->FUN_00c3bfe0(&out);
                }
                return;
            }
            return;
        }
        e = e->pNext;
        if (e == head)
            return;
    }
}

// @ 0x010019a0
void CReg::FUN_010019a0()
{
    void* a = SELF(FUN_01021260())->FUN_00c71e30();
    float tmp = 0.0f;
    void* r = FUN_0102f810((u32)(size_t)a, (u32)(size_t)&tmp);
    int n = (int)(size_t)SELF(r)->FUN_01030b70();
    if (!(tmp > *(float*)0x01485378))
        return;

    SELF(FUN_01021300())->FUN_00c31a00(-n);

    u8* ed = (u8*)mp40;
    u8* sub = ed + 0x508;
    float base = *(float*)(ed + 0x540);
    float cur = VFRet0(sub, 0x58);
    float v = cur - base;
    float lo = (v > tmp) ? tmp : v;
    SELF(sub)->FUN_00bfd1a0(lo);

    float dv = tmp - v;
    void* o = FUN_01002bd0(0xc);
    void* obj = SELF(o)->FUN_01005180();
    SELF(obj)->FUN_007eb820(8);
    SELF(*(void**)((u8*)obj + 0xc))->FUN_00c389f0(dv);

    if (tmp > *(float*)0x01485378) {
        void* vec = SELF(FUN_00b3d300())->FUN_00b21340(
            (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00ad48b0,
            (void*)0x00b1e500, (void*)0x018ebadc);
        void** pBeg = (void**)((u8*)vec + 4);
        void** pEnd = (void**)((u8*)vec + 4);
        int cnt = (int)(((u8*)*(void**)((u8*)vec + 8) - (u8*)*pEnd) >> 2);
        (void)cnt;
        for (int i = 0; i < cnt; ++i) {
            void* en = *(void**)((u8*)(*pBeg) + i * 4);
            if (*(u32*)((u8*)en + 0x714) != 3)
                continue;
            u8* esub = (u8*)en + 0x508;
            float b2 = *(float*)((u8*)en + 0x540);
            float c2 = VFRet0(esub, 0x58);
            float d2 = c2 - b2;
            float pick = (d2 > cur) ? cur : d2;
            SELF(esub)->FUN_00bfd1a0(pick);
        }
    }
}

// @ 0x01001b60
void* CReg::FUN_01001b60()
{
    u32 tag = 0xffffffff;
    if (FUN_01021260()) {
        void* a = SELF(FUN_01021260())->FUN_00c71e30();
        if (a)
            tag = *(u32*)((u8*)SELF(FUN_01021260())->FUN_00c71e30() + 0x84);
    }

    void* mv = (u8*)mp40 + 0x34;
    void* vp = VRet0(mv, 0x2c);
    float p[3];
    p[0] = *(float*)((u8*)vp + 0);
    p[1] = *(float*)((u8*)vp + 4);
    p[2] = *(float*)((u8*)vp + 8);

    float best = *(float*)0x014950e0;
    void* res = 0;

    void* vec = SELF(FUN_00b3d300())->FUN_00b21340(
        (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00ad48b0,
        (void*)0x00b1e500, (void*)0x018ebadc);
    void** pBeg = (void**)((u8*)vec + 4);
    int n = (int)(((u8*)*(void**)((u8*)vec + 8) - (u8*)*pBeg) >> 2);
    if (n <= 0)
        return res;

    for (int i = 0; i < n; ++i) {
        void* en = *(void**)((u8*)(*pBeg) + i * 4);
        if ((u32)(size_t)VRet0(en, 0x4c) != tag)
            continue;
        void* t = VRet0((u8*)en + 0x34, 0x2c);
        float dx = p[0] - *(float*)((u8*)t + 0);
        float dy = p[1] - *(float*)((u8*)t + 4);
        float dz = p[2] - *(float*)((u8*)t + 8);
        float d2 = dx * dx + dy * dy + dz * dz;
        if (best > d2) {
            best = d2;
            res = en;
        }
    }
    return res;
}

// @ 0x01001cd0
void CReg::FUN_01001cd0(u32 arg1, float arg2)
{
    u32 mode = FUN_01021080();
    void* mgr = SELF(FUN_01002bd0((u32)(size_t)FUN_01021260()))->FUN_00a1ad60();
    void* tgt = SELF(mgr)->FUN_00ff3f00();

    if (!tgt || SELF(tgt)->FUN_0104cce0())
        goto clear_target;

    {
        void* q = FUN_0067dd10();
        void* s = VRet0(VRet0(q, 0x50), 0x1c);
        u8 blobA[0x40];
        u8 blobB[0x40];
        SELF(s)->FUN_007c4900(blobA, blobB);
        if (!tgt) { /* keep */ }

        u32 ap = (u32)(size_t)(mp40 ? (u8*)mp40 + 0x508 : 0);
        if (!FUN_00cb6960(0, 0, 0, (void*)(size_t)ap, 0, 0, 0, 0)) {
            if (mpD0) {
                void* e = mpD0;
                mpD0 = 0;
                VRet0(e, 0x64);
            }
        }
    }

clear_target:
    if (mpD0) {
        void* e = mpD0;
        mpD0 = 0;
        VRet0(e, 0x64);
    }

    mWcc += arg1;
    if (mWcc > SELF(FUN_0102f810(0, 0))->FUN_0102fbf0()) {
        float s = SELF(FUN_0102f810(0, 0))->FUN_0102fc60();
        float k = *(float*)((u8*)mp40 + 0x7f8) * *(float*)0x013eb960;
        SELF(mp40)->FUN_00c389f0(
            (float)((double)arg1 - (double)(u32)((*(u32*)&arg2) & 0x7fffffff)) * s * k);
    }

    if (mode == 0) {
        void* q = FUN_0067dd10();
        void* s = VRet0(VRet0(q, 0x50), 0x38);
        if (s && VRet1(s, 0xc, (void*)0x303154cd))
            FUN_00b3d380();
    } else if (mode == 1) {
        if (*(u8*)((u8*)mp40 + 0x74c))
            FUN_01021260();
    }

    {
        void* e = mpD0;
        if (e) {
            void* q = VRet1(e, 0x5c, (void*)0xce9f6639);
            int bad = 1;
            if (q) {
                u8 b0 = *(u8*)((u8*)q + 0xb5e);
                u8 b1 = *(u8*)((u8*)q + 0x130);
                u8 b2 = *(u8*)((u8*)q + 0xf90);
                bad = (b0 != 0) || (b1 == 0) || (b2 == 0);
            }
            if (bad) {
                void* ec = mpD0;
                if (ec) {
                    mpD0 = 0;
                    VRet0(ec, 0x64);
                }
            }
        }
    }

    SELF(this)->FUN_01000eb0();
    SELF(this)->FUN_01000dc0();
}