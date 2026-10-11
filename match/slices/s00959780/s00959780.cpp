// Slice s00959780 -- EA::UTFWin WindowMgr window/message/render plumbing.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE2
#include <intrin.h>
#include <string.h>

typedef unsigned int  uint;
typedef unsigned char uchar;

#define B(p)     ((char*)(p))
#define I8(p,o)  (*(char*)((char*)(p)+(o)))
#define U8(p,o)  (*(unsigned char*)((char*)(p)+(o)))
#define I16(p,o) (*(short*)((char*)(p)+(o)))
#define I32(p,o) (*(int*)((char*)(p)+(o)))
#define U32(p,o) (*(unsigned*)((char*)(p)+(o)))
#define PTR(p,o) (*(void**)((char*)(p)+(o)))
#define F32(p,o) (*(float*)((char*)(p)+(o)))

// ---- external functions (all __thiscall; self == ecx) ----
double __cdecl  iat_floor(double);                                 // 0x11e0906
int    __cdecl  ModulateARGB32(int a, int b);                      // 0x95f8c0

struct TC {
    void* Fn00951d50();                                            // 0x951d50
    void  Fn009592e0(void* p, int a);                              // 0x9592e0
    void* GetPositionStatic(void* p, int b);                       // 0x959050
    char  AllDescendants(int a);                                   // 0x95fbb0
    void* Fn0095fc00(int a);                                       // 0x95fc00
    void  Fn0095e7a0();                                            // 0x95e7a0
    void  Fn0095f620();                                            // 0x95f620 Invert
    void  Fn0095e890(void* p);                                     // 0x95e890
    void  Fn0095e810(void* a, void* b);                            // 0x95e810
    void  Fn0095f860(void* p);                                     // 0x95f860 Matrix43::Multiply
    int   Lock_(const void* name);                                 // 0x9221b0
    int   Unlock_();                                               // 0x922270
    void  e31b20(void* p);                                         // 0x00e31b20
    void  End2D();                                                 // 0x0095bb20
    void  Fn00957fa0();                                            // 0x957fa0
};
#define TH(x) ((TC*)(x))

struct W {
    char GV(int a, int b, void* c, int d, int e);                  // 0x00959640
    void RenderWindow(int win, void* ctx);                         // 0x0095a510
    void a0b0(int p2, int* p3);                                    // 0x0095a0b0
    void fe0(int win);                                             // 0x00959fe0
    void cf0(int p2, int p3);                                      // 0x00959cf0
    int  b70(int p2, int p3);                                      // 0x00959b70
    void DetachWindow(void* win);                                  // 0x00959e00
    void UpdateRenderState(int win, char p3, char p4);             // 0x0095a140
    char Fn00959780(int* ev, char p3);                             // 0x00959780
};

// vtable slot accessor: function pointer at byte offset `off` of this->vtable
#define VFP(off) (*(void**)((char*)*(void**)this + (off)))

// ===========================================================================
// @ 0x0095a510  W::RenderWindow
// ===========================================================================
void W::RenderWindow(int win, void* ctx)
{
    void* v = PTR(win, 0x1e4);
    if (v == 0)
        v = TH(this)->Fn00951d50();
    TH(ctx)->e31b20(v);
    void* sub = B(ctx) + 0x58;
    ((int(__thiscall*)(void*, int, int))*(void**)((char*)*(void**)sub + 0x10))(sub, 0, 0);
    int ev[7];
    ev[2] = 0xd;
    ev[6] = (int)ctx;
    GV(0, win + 4, ev, 0, 0);
    TH(ctx)->End2D();
}

// ===========================================================================
// @ 0x0095a0b0  W::a0b0
// ===========================================================================
void W::a0b0(int p2, int* p3)
{
    int saved = I32(this, 0x688);
    I32(this, 0x688) = 0;
    int local[7];
    memcpy(local, p3, 28);
    local[0] = p2 ? p2 + 4 : 0;
    int v = I32(p2, 0x38);
    local[1] = v ? v + 4 : 0;
    int* p = (int*)PTR(this, 0xc8);
    if (p != 0) {
        ((int(__thiscall*)(void*, int, int, void*))*(void**)((char*)*(void**)p + 0xc))
            (p, 3, 0, local);
    }
    TH(this)->Fn009592e0(local, 1);
    I32(this, 0x688) = saved;
}

// ===========================================================================
// @ 0x00959fe0  W::fe0
// ===========================================================================
void W::fe0(int win)
{
    float* dst = (float*)(B(win) + 0x88);
    dst[0] = F32(win, 0x98);
    int ev[7];
    ev[2] = 0x10;
    dst[1] = F32(win, 0x9c);
    ev[6] = (int)dst;
    dst[2] = F32(win, 0xa0);
    dst[3] = F32(win, 0xa4);
    void* b = win ? (void*)(B(win) + 4) : 0;
    GV((int)b, (int)b, ev, 0, 0);
    float* ft = (float*)ev;
    ft[0] = (float)iat_floor((double)F32(win, 0x88));
    ft[1] = (float)iat_floor((double)F32(win, 0x8c));
    ft[2] = (float)iat_floor((double)F32(win, 0x90));
    float t3 = (float)iat_floor((double)F32(win, 0x94));
    dst[0] = ft[0];
    dst[1] = ft[1];
    dst[2] = ft[2];
    dst[3] = t3;
}

// ===========================================================================
// @ 0x00959cf0  W::cf0
// ===========================================================================
void W::cf0(int p2, int p3)
{
    p3 = p3 ? p3 - 4 : 0;
    int* piVar1 = (int*)(B(this) + p2 * 0x28 + 0x68c);
    if (p3 != piVar1[2]) {
        int ev[7];
        if (piVar1[5] != 0) {
            memcpy(ev, piVar1 + 3, 28);
            piVar1[5] = 0;
            Fn00959780(ev, 0);
        }
        ev[2] = 0xb;
        ev[3] = p2;
        ev[6] = p3 ? p3 + 4 : 0;
        int iVar2 = piVar1[2];
        piVar1[2] = 0;
        if (iVar2 != 0) {
            GV(0, iVar2 + 4, ev, 0, 0);
        }
        if (piVar1[2] == 0) {
            if (p3 == 0) {
                int t = piVar1[1] ? piVar1[1] + 4 : 0;
                ((int(__thiscall*)(void*, int, int))VFP(0x4c))(this, p2, t);
            } else {
                ((int(__thiscall*)(void*, int, int))VFP(0x4c))(this, p2, p3 + 4);
                if (piVar1[2] == 0 && piVar1[0] == p3) {
                    piVar1[2] = p3;
                    GV(0, p3 + 4, ev, 0, 0);
                    return;
                }
            }
        }
    }
}

// ===========================================================================
// @ 0x00959b70  W::b70
// ===========================================================================
int W::b70(int p2, int p3)
{
    p3 = p3 ? p3 - 4 : 0;
    int* piVar1 = (int*)(B(this) + p2 * 0x28 + 0x68c);
    if (p3 != 0) {
        void* obj = (void*)(p3 + 4);
        uchar r = ((uchar(__thiscall*)(void*))*(void**)((char*)*(void**)obj + 0x28))(obj);
        if ((r & 1) == 0)
            return 0;
        if ((r & 2) == 0 && p2 != 1)
            return 0;
        if (TH(p3)->AllDescendants(p2 == 1) == 0)
            return 0;
    }
    if (piVar1[2] != 0) {
        piVar1[1] = p3;
        return 1;
    }
    if (p3 != piVar1[0]) {
        int ev[7];
        if (piVar1[5] != 0) {
            memcpy(ev, piVar1 + 3, 28);
            piVar1[5] = 0;
            Fn00959780(ev, 0);
        }
        ev[3] = p2;
        ev[6] = p3 ? p3 + 4 : 0;
        int iVar4 = piVar1[0] ? piVar1[0] + 4 : 0;
        piVar1[0] = p3;
        piVar1[1] = p3;
        if (iVar4 != 0) {
            ev[2] = 10;
            GV(0, iVar4, ev, 0, 0);
            ev[2] = 0x1c;
            ev[6] = iVar4;
            GV(iVar4, iVar4, ev, 1, 0);
            if (piVar1[0] != p3)
                return 1;
        }
        piVar1[0] = p3;
        piVar1[1] = p3;
        TH(this)->Fn00957fa0();
        if (p3 != 0) {
            p3 = p3 + 4;
            ev[2] = 10;
            ev[6] = p3;
            GV(0, p3, ev, 0, 0);
            ev[2] = 0x1b;
            GV(p3, p3, ev, 1, 0);
        }
    }
    return 1;
}

// ===========================================================================
// @ 0x00959e00  W::DetachWindow
// ===========================================================================
void W::DetachWindow(void* win)
{
    int ev[7];
    ev[2] = 0x12;
    void* p = win ? (void*)((int)B(win) + 4) : 0;
    GV((int)p, (int)p, ev, 0, 0);

    void* anchor0 = B(win) + 0x3c;
    for (void** pu = (void**)PTR(win, 0x3c); pu != (void**)anchor0; pu = (void**)*pu) {
        void* q = pu ? (void*)((int)pu - 8) : 0;
        DetachWindow(q);
    }

    int iVar13 = 0;
    char* pSVar = B(this) + 0x690;
    do {
        if (I32(pSVar, 4) == (int)win) {
            ((int(__thiscall*)(void*, int, int))VFP(0x5c))(this, iVar13, (int)B(win) + 4);
        }
        if (I32(pSVar, 0) == (int)win) {
            int mId = I32(win, 0x38);
            int iVar10 = mId ? mId + 4 : 0;
            char c = (char)((int(__thiscall*)(void*, int, int))VFP(0x4c))(this, iVar13, iVar10);
            if (c == 0) {
                int t = (int)TH(mId)->Fn0095fc00(0);
                iVar10 = t ? t + 4 : 0;
                ((int(__thiscall*)(void*, int, int))VFP(0x4c))(this, iVar13, iVar10);
            }
        }
        iVar13++;
        pSVar += 0x28;
    } while (iVar13 < 10);

    TH(B(this) + 0x658)->Lock_((const void*)0x1440688);
    void* head = PTR(this, 0xd4);
    void* anchor1 = B(this) + 0xd4;
    while (head != anchor1) {
        void* w4 = (void*)((int)B(win) + 4);
        if (I32(head, 8) == (int)w4 || I32(head, 0xc) == (int)w4) {
            void* nxt = PTR(head, 0);
            void* eax = PTR(nxt, 4);
            void* c1 = PTR(eax, 4);
            void* d1 = PTR(eax, 0);
            I32(c1, 0) = (int)d1;
            void* c2 = PTR(eax, 0);
            void* d2 = PTR(eax, 4);
            I32(c2, 4) = (int)d2;
            void* alloc = PTR(this, 0xdc);
            ((void(__thiscall*)(void*, void*, int))*(void**)((char*)*(void**)alloc + 0xc))
                (alloc, eax, 0x24);
            head = nxt;
        } else {
            head = PTR(head, 0);
        }
    }
    TH(B(this) + 0x658)->Unlock_();

    if (I32(win, 0x1c) != 0) {
        void* node = B(win) + 0x18;
        void* it = PTR(this, 0x20);
        if (it == node) {
            U8(this, 0x24) = 1;
            void* nxt = PTR(node, 0);
            void* prv = PTR(node, 4);
            I32(prv, 0) = (int)nxt;
            I32(nxt, 4) = (int)prv;
            I32(node, 0) = 0;
            I32(node, 4) = 0;
            PTR(this, 0x20) = nxt;
        } else {
            void* prv = PTR(node, 4);
            void* nxt = PTR(node, 0);
            I32(prv, 0) = (int)nxt;
            I32(nxt, 4) = (int)prv;
            I32(node, 0) = 0;
            I32(node, 4) = 0;
        }
        I32(win, 0x1c) = 0;
    }
    if (I32(win, 0x24) != 0) {
        void* prv = PTR(win, 0x24);
        void* nxt = PTR(win, 0x20);
        I32(prv, 0) = (int)nxt;
        I32(nxt, 4) = (int)prv;
        I32(win, 0x20) = 0;
        I32(win, 0x24) = 0;
    }
    if (I32(win, 0x14) != 0) {
        void* prv = PTR(win, 0x14);
        void* nxt = PTR(win, 0x10);
        I32(prv, 0) = (int)nxt;
        I32(nxt, 4) = (int)prv;
        I32(win, 0x10) = 0;
        I32(win, 0x14) = 0;
    }
    if (PTR(win, 0x78) != 0 && U8(this, 0x25) == 0) {
        char* anchor = B(this) + 0x18;
        U8(this, 0x25) = 1;
        while (PTR(anchor, 4) != anchor) {
            void* N = PTR(anchor, 4);
            void* P = PTR(N, 4);
            I32(P, 0) = (int)anchor;
            PTR(anchor, 4) = P;
            if (N != anchor) {
                I32(N, 4) = 0;
                I32(N, 0) = 0;
            }
        }
    }
    I32(win, 0x78) = 0;
    I32(win, 0x34) = 0;
}

// ===========================================================================
// @ 0x0095a140  W::UpdateRenderState
// ===========================================================================
void W::UpdateRenderState(int win, char p3, char p4)
{
    char c1 = 0, c2 = 0;
    if ((U8(win, 0x30) & 0x20) != 0) {
        U8(win, 0x30) = (uchar)(U8(win, 0x30) & 0xdf);
        TH(win + 0xc4)->Fn0095e7a0();
        int ev[7];
        ev[2] = 0x15;
        ev[6] = win + 0xc4;
        GV(0, win + 4, ev, 0, 0);
        memcpy((void*)(win + 0x108), (void*)(win + 0xc4), 0x44);
        TH(win + 0x108)->Fn0095f620();
        c1 = 1;
    }
    if ((U8(win, 0x30) & 0x40) != 0) {
        U8(win, 0x30) = (uchar)(U8(win, 0x30) & 0xbf);
        c2 = 1;
    }
    if (c1 != 0) {
        float f0 = (F32(win, 0x90) + F32(win, 0x88)) * 0.5f;
        float f1 = (F32(win, 0x94) + F32(win, 0x8c)) * 0.5f;
        memcpy((void*)(win + 0x14c), (void*)(win + 0xc4), 0x44);
        float lv[3];
        lv[0] = f0;
        lv[1] = f1;
        lv[2] = 0.0f;
        TH(win + 0x14c)->Fn0095e890(lv);
        int p = I32(win, 0x38);
        if (p != 0 && I32(p, 0x1e8) == 0) {
            TH(win + 0x14c)->Fn0095f860((void*)(p + 0x14c));
        }
        if (I32(win, 0x38) == 0) {
            float one[3];
            one[0] = 1.0f;
            one[1] = 1.0f;
            one[2] = 1.0f;
            float neg[3];
            neg[0] = -f0;
            neg[1] = -f1;
            neg[2] = -0.0f;
            TH(win + 0x190)->Fn0095e810(neg, one);
        } else {
            memcpy((void*)(win + 0x190), (void*)(I32(win, 0x38) + 0x190), 0x44);
            float neg[3];
            neg[0] = -f0;
            neg[1] = -f1;
            neg[2] = -0.0f;
            TH(win + 0x190)->Fn0095e890(neg);
        }
        if (I32(win, 0x148) != 4) {
            TH(win + 0x190)->Fn0095f860((void*)(win + 0x108));
        }
        float g0 = (F32(win, 0x90) - F32(win, 0x88)) * 0.5f;
        float g1 = (F32(win, 0x94) - F32(win, 0x8c)) * 0.5f;
        float gv[3];
        gv[0] = g0;
        gv[1] = g1;
        gv[2] = 0.0f;
        TH(win + 0x190)->Fn0095e890(gv);
        if (I32(win, 0x18c) == 0)
            I32(win, 0x18c) = 1;
        F32(win, 0x180) = F32(win, 0x180) - (F32(win, 0x150) * g0 + F32(win, 0x160) * g1);
        F32(win, 0x184) = F32(win, 0x184) - (F32(win, 0x154) * g0 + F32(win, 0x164) * g1);
        F32(win, 0x17c) = F32(win, 0x17c) - (F32(win, 0x14c) * g0 + F32(win, 0x15c) * g1);
        F32(win, 0x188) = F32(win, 0x188) - (F32(win, 0x158) * g0 + F32(win, 0x168) * g1);
        if (I32(win, 0x78) != 0 && I32(win, 0x24) == 0 && U8(this, 0x25) == 0) {
            void* node = B(win) + 0x20;
            I32(node, 4) = I32(this, 0x1c);
            I32(node, 0) = (int)(B(this) + 0x18);
            I32(this, 0x1c) = (int)node;
            I32(I32(node, 4), 0) = (int)node;
        }
    }
    if (p4 != 0) {
        I32(win, 0x1d4) = I32(win, 0x1d8);
        int p = I32(win, 0x38);
        if (p != 0) {
            I32(win, 0x1d4) = ModulateARGB32(I32(win, 0x1d8), I32(p, 0x1d4));
        }
        if (I32(win, 0x78) != 0 && I32(win, 0x24) == 0 && U8(this, 0x25) == 0) {
            void* node = B(win) + 0x20;
            I32(node, 4) = I32(this, 0x1c);
            I32(node, 0) = (int)(B(this) + 0x18);
            I32(this, 0x1c) = (int)node;
            I32(I32(node, 4), 0) = (int)node;
        }
    }
    int bVar2;
    if (c1 == 0 && p4 == 0)
        bVar2 = 0;
    else
        bVar2 = 1;
    if (I8(win, 0x30) < 0) {
        U8(win, 0x30) = (uchar)(U8(win, 0x30) & 0x7f);
    } else if (bVar2 == 0) {
        return;
    }
    void* anchor = B(win) + 0x3c;
    for (void** pu = (void**)PTR(win, 0x3c); pu != (void**)anchor; pu = (void**)*pu) {
        void* q = pu ? (void*)((int)pu - 8) : 0;
        UpdateRenderState((int)q, p3, p4);
    }
}

// ===========================================================================
// @ 0x00959780  W::Fn00959780  (window message dispatcher)
// ===========================================================================
char W::Fn00959780(int* ev, char p3)
{
    char ret = 0;
    int id = ev[2];
    if (id == 0x4ecd5687) {
        float f1 = F32(ev, 0xc);
        float f2 = F32(ev, 0x10);
        F32(this, 0xa8) = f1 * 0.5f;
        F32(this, 0xac) = f2 * 0.5f;
        F32(this, 0xb0) = 2.0f / f1;
        F32(this, 0xb4) = 2.0f / f2;
        void* im = PTR(this, 4);
        if (im != 0) {
            float r[4];
            r[0] = 0.0f;
            r[1] = 0.0f;
            r[2] = f1;
            r[3] = f2;
            ((void(__thiscall*)(void*, void*))*(void**)((char*)*(void**)im + 0x60))(im, r);
        }
        return 1;
    }
    if (id == 0x74d2e9) {
        ((void(__cdecl*)(int, void*))PTR(ev, 0xc))((int)this, (void*)ev[4]);
        if (ev[4] != 0) {
            void* o = (void*)ev[4];
            ((void(__thiscall*)(void*))*(void**)((char*)*(void**)o + 4))(o);
            return 0;
        }
        return ret;
    }
    if (PTR(this, 4) == 0)
        return ret;

    switch (id) {
    case 1:
    case 2:
    case 5: {
        int idx = ev[3];
        int* piVar2 = (int*)(B(this) + idx * 0x28 + 0x68c);
        if (I32(this, idx * 0x28 + 0x68c) != 0) {
            if (piVar2[5] != 0) {
                int t[7];
                memcpy(t, piVar2 + 3, 28);
                piVar2[5] = 0;
                Fn00959780(t, 0);
            }
            int iv = *piVar2;
            int t[7];
            memcpy(t, ev, 28);
            if (id == 1) {
                t[2] = 3;
                iv = iv ? iv + 4 : 0;
                ret = GV(0, iv, t, 1, 1);
            } else if (id == 2) {
                t[2] = 4;
                iv = iv ? iv + 4 : 0;
                ret = GV(0, iv, t, 1, 1);
            }
            if (ret == 0) {
                int jv = *piVar2;
                jv = jv ? jv + 4 : 0;
                ret = ((char(__thiscall*)(void*, int, void*, int*, int))VFP(0x10))
                    (this, 0, (void*)jv, ev, 1);
            }
        }
        return ret;
    }
    case 0x19:
    case 0x1a: {
        int idx = ev[3];
        int* piVar2 = (int*)(B(this) + idx * 0x28 + 0x68c);
        if (I32(this, idx * 0x28 + 0x68c) != 0) {
            if (piVar2[5] != 0) {
                int t[7];
                memcpy(t, piVar2 + 3, 28);
                piVar2[5] = 0;
                Fn00959780(t, 0);
            }
            int jv = *piVar2;
            jv = jv ? jv + 4 : 0;
            ret = ((char(__thiscall*)(void*, int, void*, int*, int))VFP(0x10))
                (this, 0, (void*)jv, ev, 1);
        }
        return ret;
    }
    case 3:
    case 4:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
        return ret;
    case 6:
    case 7:
    case 8:
    case 9: {
        void* pv = (void*)ev[4];
        I32(this, 0x6dc) = ev[3];
        I32(this, 0x6e0) = (int)pv;
        float local[2];
        local[0] = -1000.0f;
        local[1] = -1000.0f;
        int* r = (int*)TH(this)->GetPositionStatic(local, id == 6);
        if (r != 0) {
            if (p3 != 0) {
                unsigned u3 = ((unsigned(__thiscall*)(void*))*(void**)((char*)*(void**)r + 0x28))(r);
                unsigned u4 = U32(this, 0x6c8);
                if (((u4 == 0) || (u4 == (unsigned)id)) && ((u3 >> 7 & 1) != 0)) {
                    if (id == 8) {
                        memcpy((void*)(B(this) + 0x6c0), ev, 28);
                        return 1;
                    }
                    if (id == 9) {
                        I32(this, 0x6d8) = I32(this, 0x6d8) + ev[6];
                        return 1;
                    }
                } else if (u4 != 0) {
                    int t[7];
                    memcpy(t, (void*)(B(this) + 0x6c0), 28);
                    I32(this, 0x6c8) = 0;
                    Fn00959780(t, 0);
                }
            }
            int loc[7];
            loc[2] = ev[2];
            loc[6] = ev[6];
            loc[5] = ev[5];
            loc[3] = (int)local[0];
            unsigned u = ((unsigned(__thiscall*)(void*, int, int*, void*, int))
                VFP(0x10))(this, 0, r, loc, 0);
            return (char)u;
        }
        return ret;
    }
    case 10:
        ((int(__thiscall*)(void*, int, int))VFP(0x4c))(this, ev[3], 0);
        return ret;
    default:
        return ret;
    }
}
