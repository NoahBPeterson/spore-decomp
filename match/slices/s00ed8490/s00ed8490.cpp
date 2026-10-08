// Slice s00ed8490 -- resource/array lookup helpers and a small refcounted container.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef void  (__thiscall *FV_v)(void*);
typedef void* (__thiscall *FV_p)(void*);

// ================================================================ 0x00ed8490
int __cdecl FUN_00ed8490(int p)
{
    if (*(char*)(p + 0x4c8) == 1) {
        int diff = *(int*)(p + 0x4d0) - *(int*)(p + 0x4cc);
        if ((diff & ~0x1f) > 0) {
            int* q = *(int**)(p + 0x4cc);
            int n = 0;
            do {
                if (q[3] == 3 && q[4] == 2)
                    return q[5];
                n++;
                q = (int*)((char*)q + 0x20);
            } while (n < (*(int*)(p + 0x4d0) - *(int*)(p + 0x4cc)) >> 5);
        }
    } else if (*(int*)(p + 0x4b0) == 3) {
        return *(int*)(p + 0x4bc);
    }
    return -1;
}

// ================================================================ 0x00ed8500
int __cdecl FUN_00ed8500(int p)
{
    if (*(char*)(p + 0x4c8) == 1) {
        int diff = *(int*)(p + 0x4d0) - *(int*)(p + 0x4cc);
        if ((diff & ~0x1f) > 0) {
            int* q = *(int**)(p + 0x4cc);
            int n = 0;
            do {
                if (q[3] == 4 && q[6] == 2)
                    return q[7];
                n++;
                q = (int*)((char*)q + 0x20);
            } while (n < (*(int*)(p + 0x4d0) - *(int*)(p + 0x4cc)) >> 5);
        }
    } else if (*(int*)(p + 0x4b4) == 3) {
        return *(int*)(p + 0x4c0);
    }
    return -1;
}

// ================================================================ 0x00ed8570
int __cdecl FUN_00ed8570(int p)
{
    if (*(char*)(p + 0x4c8) == 1) {
        int diff = *(int*)(p + 0x4d0) - *(int*)(p + 0x4cc);
        if ((diff & ~0x1f) > 0) {
            int* q = *(int**)(p + 0x4cc);
            int n = 0;
            do {
                if (q[3] == 7 && q[4] == 2)
                    return q[7];
                n++;
                q = (int*)((char*)q + 0x20);
            } while (n < (*(int*)(p + 0x4d0) - *(int*)(p + 0x4cc)) >> 5);
        }
    } else if (*(int*)(p + 0x4b8) == 5) {
        return *(int*)(p + 0x4c4);
    }
    return -1;
}

// ================================================================ 0x00ed85e0
struct Obj85e0 { void* f(); };
void* Obj85e0::f()
{
    char* s = (char*)this;
    *(int*)s = 0x148a22c;
    *(int*)(s + 4) = 0;
    *(int*)(s + 8) = 0;
    *(int*)(s + 0xc) = 0;
    *(int*)(s + 0x10) = 0;
    *(int*)(s + 0x14) = 0;
    *(int*)(s + 0x18) = 0;
    *(int*)(s + 0x1c) = 0;
    *(int*)(s + 0x20) = 0;
    *(int*)(s + 0x24) = 0;
    return s;
}

// ================================================================ 0x00ed8610
struct Obj8610 { void f(); };
void Obj8610::f()
{
    char* s = (char*)this;
    *(int*)s = 0x148a22c;
    int i = 2;
    char* e = s + 0x28;
    do {
        int* p = *(int**)(e - 4);
        e -= 4;
        if (p) ((FV_v)(*(void***)p)[4 / 4])(p);
        i--;
    } while (i >= 0);
    i = 2;
    e = s + 0x1c;
    do {
        int* p = *(int**)(e - 4);
        e -= 4;
        if (p) ((FV_v)(*(void***)p)[4 / 4])(p);
        i--;
    } while (i >= 0);
    if (*(int**)(s + 0xc)) ((FV_v)(*(void***)*(int**)(s + 0xc))[4 / 4])(*(int**)(s + 0xc));
    if (*(int**)(s + 8)) ((FV_v)(*(void***)*(int**)(s + 8))[4 / 4])(*(int**)(s + 8));
    if (*(int**)(s + 4)) ((FV_v)(*(void***)*(int**)(s + 4))[4 / 4])(*(int**)(s + 4));
}


// ================================================================ shared callees
void* __cdecl FUN_00b3d300(void);                 // SP::NounManager
void* __cdecl FUN_00b1f9b0(void*);                // cGameNounManager::GetAllNouns
void* __cdecl SP_EffectsManager(void);            // 0x67ddd0
int   __cdecl FUN_006c0200(void*);                // 0x6c0200
int   __cdecl FUN_00f40d00(void*);                // 0xf40d00
void* __cdecl FUN_013c8830(void);                 // atexit callback
extern int __cdecl atexit(void*);

typedef void  (__thiscall *FVf_v)(void*);
typedef void* (__thiscall *FVf_p)(void*);
typedef void  (__thiscall *FVf_i)(void*, int);
typedef void  (__thiscall *FVf_ii)(void*, int, int);
typedef void  (__thiscall *FVf_iip)(void*, int, int, void*);
typedef void  (__thiscall *FVf_if)(void*, int, float);

struct S_c8ad30 { void f(int, int); };
struct S_c8b210 { void f(int); };
struct S_c88a00 { void f(int, float); };
struct S_c8a200 { void f(int, float); };

// ================================================================ 0x00ed8690
void FUN_00ed8690(void)
{
    void* nm = FUN_00b3d300();
    int* v = (int*)FUN_00b1f9b0(nm);
    int* end = (int*)((char*)v - 0xc);
    int* it = (*v == 0) ? 0 : (int*)((char*)*v - 0xc);
    while (it != end) {
        int esi = 0;
        if (it != 0)
            esi = ((int(__thiscall*)(void*, int))(*(void***)it)[3])(it, 0x1186577);
        if (FUN_006c0200(it) != 0) {
            ((S_c8ad30*)(void*)esi)->f(0xd79308d, 0);
            ((S_c8ad30*)(void*)esi)->f(0x25e2b68, 0);
            ((S_c8ad30*)(void*)esi)->f(0xe1b86fea, 0);
            ((S_c8ad30*)(void*)esi)->f(0xfeacc46f, 0);
            ((S_c8ad30*)(void*)esi)->f(0xad89ad7d, 0);
            for (unsigned i = 0; i < 3; i++)
                ((S_c8ad30*)(void*)esi)->f((int)(0xcaf390f3u + i), 0);
        }
        int* nxt = (int*)it[3];
        it = (nxt == 0) ? 0 : (int*)((char*)nxt - 0xc);
    }
}

// ================================================================ 0x00ed8780
struct Obj8780 { void f(int b); };
static void grab(int id, int* field)
{
    int* em = (int*)SP_EffectsManager();
    int* old = *(int**)field;
    if (old != 0) {
        *(int**)field = 0;
        ((FVf_v)(*(void***)old)[4 / 4])(old);
    }
    ((FVf_iip)(*(void***)em)[0x2c / 4])(em, id, 0, field);
}
static void clear2(int* field)
{
    int* p = *(int**)field;
    if (p != 0) {
        ((FVf_i)(*(void***)p)[0xc / 4])(p, 0);
        int* q = *(int**)field;
        if (q != 0) {
            *(int**)field = 0;
            ((FVf_v)(*(void***)q)[4 / 4])(q);
        }
    }
}
void Obj8780::f(int b)
{
    char* s = (char*)this;
    if (b != 0) {
        grab(0x654889e6, (int*)(s + 4));
        grab(0x95354ff3, (int*)(s + 8));
        grab(0xcbe66649, (int*)(s + 0xc));
        for (int i = 0; i < 3; i++) {
            grab(0xe3a79142, (int*)(s + 0x10 + i * 4));
            grab(0xe3a79142, (int*)(s + 0x1c + i * 4));
        }
    } else {
        clear2((int*)(s + 4));
        clear2((int*)(s + 8));
        clear2((int*)(s + 0xc));
        for (int i = 0; i < 3; i++) {
            clear2((int*)(s + 0x10 + i * 4));
            clear2((int*)(s + 0x1c + i * 4));
        }
    }
}

// ================================================================ 0x00ed8950
void FUN_00ed8950(int a, int b)
{
    int* local = 0;
    int* local10 = 0;
    int cap = 0;
    FUN_00f40d00((void*)a);
    (void)local; (void)local10; (void)cap;
    // Placeholder: the real body iterates a noun vector and pushes float params.
}

// ================================================================ 0x00ed8a30
// Per-noun effect/indicator update for the ability UI (players' "selected / hovered" markers).
struct Fx8a30 {                                   // effects component of a noun (entries are 0x3c bytes at +0xc0)
    struct Eff { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                 virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
                 virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
                 virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void SetPtr(int, void*);
                 virtual void v20(); virtual void v21(); virtual void v22(); virtual void* GetPtr(int);
                 virtual unsigned long long GetKey(); };
    Eff*  FindEff(unsigned id);                   // 0x00c888e0
    bool  IsActive(unsigned id);                  // 0x00c88940
    void  Remove(unsigned id, int);               // 0x00c8ad30
    void  Add(unsigned lo, unsigned hi, unsigned id);  // 0x00c8b130
    void  SetMax(unsigned id, float);             // 0x00c88a00
    void  SetScale(unsigned id, float);           // 0x00c8a200
    void  SetVis(unsigned id, int);               // 0x00c8a110
};
struct GData8a30 {                                // per-player data holder (SP::cGameData-like)
    bool IsKind1();                               // 0x00f25330
    bool IsKind2();                               // 0x00f25470
};
struct Holder8a30 {
    GData8a30* GetData(int);                      // 0x00f3e8a0
    char*      GetPlayer(int);                    // 0x00f3be60 (0x534-byte records)
};
struct Noun8a30 {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual Fx8a30* GetComponent(unsigned id);
    int*       Owner();                           // 0x006c0200
    GData8a30* GetGameData();                     // 0x00b18530
};
struct NounMgr8a30 { int* GetAllNouns(); };      // 0x00b1f9b0
struct Game8a30 { char pad[0x74]; Holder8a30* holder; };
extern Game8a30* g_game8a30;                      // 0x016c7aa4
NounMgr8a30* __cdecl NounManager8a30(void);       // 0x00b3d300
int* __cdecl FUN_00efc910(void);                  // 0x00efc910 current-selection owner
void __cdecl FUN_00ed82e0(Fx8a30*, unsigned id, unsigned hi, int enable, float scale, int vis);
void __cdecl FUN_00ed8350(Fx8a30*, unsigned id, unsigned lo, unsigned hi, int enable, float scale, int vis);
unsigned* __cdecl FUN_00ed83f0(Noun8a30*, int, float, int);
void __cdecl SetNumberString8a30(long long v, wchar_t* buf, int n);   // 0x00881ae0 EA::Locale::SetNumberString
struct WStr8a30 { void assign(const wchar_t* b, const wchar_t* e); };  // 0x00423650
void* __cdecl operator_new8a30(unsigned sz, const char* name, int, int, int, int);  // 0x00f473a0
struct UiVal8a30 { virtual void* GetItem(int); /* slot 0x5c is 23 */ };
struct Slot8a30 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void SetItem(int, void*);             // +0x4c
    virtual void v20(); virtual void v21(); virtual void v22();
    virtual void* GetItem(int);                   // +0x5c
};
struct Msg8a30 {
    virtual void AddRef();
    virtual void Release();
    int pad[1];
};
extern unsigned g_tab108[];                       // 0x0148a108: {lo,hi} * 3 per kind
extern unsigned g_tab0d8[];                       // 0x0148a0d8: {lo,hi} per slot

static inline int count188(char* vec)             // (end - begin) / 0x188 as signed
{
    return (*(int*)(vec + 4) - *(int*)vec) / 0x188;
}

// FUN_00ed8a30 @ 0x00ed8a30
void __cdecl FUN_00ed8a30(int a, int b)
{
    int owner64 = -1, owner60 = -1, owner5c = -1;
    GData8a30* gd0 = g_game8a30->holder->GetData(b);
    int* sel = FUN_00efc910();
    if (gd0 != 0) {
        char* rec = *(char**)((char*)gd0 + 0x70) + a * 0x4e0;
        owner64 = FUN_00ed8490((int)rec);
        owner60 = FUN_00ed8500((int)rec);
        owner5c = FUN_00ed8570((int)rec);
    }
    char* player = g_game8a30->holder->GetPlayer(a);
    char* vec = player + 0x84;
    bool isMinus2 = (b == -2);

    NounMgr8a30* nm = NounManager8a30();
    int* v = nm->GetAllNouns();
    int* end = (int*)((char*)v - 0xc);
    Noun8a30* it = (*v == 0) ? 0 : (Noun8a30*)((char*)*v - 0xc);
    while ((int*)it != end) {
        Fx8a30* fx = 0;
        if (it != 0)
            fx = it->GetComponent(0x1186577);
        int* ownerp = it->Owner();
        if (ownerp != 0) {
            int kind = *ownerp;
            if (it != 0 && it->GetComponent(0xce9f6639) != 0)
                FUN_00ed82e0(fx, 0x1d5458be, 0, ownerp == sel, 0.0f, 1);
            if (kind == -2) {
                Fx8a30::Eff* e = fx->FindEff(0xd79308d);
                bool skip = false;
                if (e != 0) {
                    unsigned long long k = e->GetKey();
                    if (k == 0x329fef20ULL) skip = true;
                    else fx->Remove(0xd79308d, 0);
                }
                if (!skip) {
                    fx->Add(0x329fef20, 0, 0xd79308d);
                    fx->SetMax(0xd79308d, 3.402823466e+38f);
                    fx->SetScale(0xd79308d, 0.0f);
                    fx->SetVis(0xd79308d, 1);
                }
            } else {
                GData8a30* gd = it->GetGameData();
                char* rec = *(char**)((char*)gd + 0x70) + a * 0x4e0;
                int en = 0;
                if (gd->IsKind1() && *(int*)(rec + 0x4a8) != 1)
                    en = 1;
                unsigned* t = FUN_00ed83f0(it, en, 0.0f, 1);
                int ix = *(int*)(rec + 0x4a8);
                FUN_00ed8350(fx, 0xd79308d, t[ix * 2], t[ix * 2 + 1], en, 0.0f, 1);
                int en2 = (gd->IsKind2() && kind == b) ? 1 : 0;
                int jx = *(int*)(rec + 0x4ac);
                FUN_00ed8350(fx, 0x25e2b68, g_tab0d8[jx * 2], g_tab0d8[jx * 2 + 1], en2, 1.0f, 0);
                int cnt = *(int*)(rec + 0x4a4);
                float fcnt = (float)cnt;
                FUN_00ed82e0(fx, 0x7c1c3d38, 0, cnt != -1, 1.0f, 0);
                Fx8a30::Eff* e = fx->FindEff(0x7c1c3d38);
                if (e != 0) {
                    wchar_t buf[0x20];
                    SetNumberString8a30((long long)fcnt, buf, 0x20);
                    Slot8a30* sl = (Slot8a30*)(void*)e;
                    int* m = (int*)sl->GetItem(8);
                    if (m == 0) {
                        int* n = (int*)operator_new8a30(0x1c, "Simulator", 0, 0, 0, 0);
                        if (n != 0) {
                            n[1] = 0x13ef094;
                            n[2] = 0;
                            n[0] = 0x13f585c;
                            n[1] = 0x13f5858;
                            n[3] = 0x1667bac;
                            n[4] = 0x1667bac;
                            n[5] = 0x1667bae;
                            ((Msg8a30*)(void*)n)->AddRef();
                        }
                        m = n;
                    } else {
                        ((Msg8a30*)(void*)m)->AddRef();
                    }
                    const wchar_t* pe = buf;
                    while (*pe) pe++;
                    ((WStr8a30*)(void*)(m + 3))->assign(buf, pe);
                    sl->SetItem(8, m);
                    if (m != 0)
                        ((Msg8a30*)(void*)m)->Release();
                }
            }
            // owner-colour markers
            bool isOwner64 = (kind == owner64);
            bool act = fx->IsActive(0xe1b86fea);
            if (isOwner64) {
                if (!act) {
                    fx->Add(0xe1b86fea, 0, 0xe1b86fea);
                    fx->SetMax(0xe1b86fea, 3.402823466e+38f);
                    fx->SetScale(0xe1b86fea, 1.0f);
                    fx->SetVis(0xe1b86fea, 0);
                }
            } else if (act) {
                fx->Remove(0xe1b86fea, 0);
            }
            bool isOwner60 = (kind == owner60);
            act = fx->IsActive(0xfeacc46f);
            if (isOwner60) {
                if (!act) {
                    fx->Add(0xfeacc46f, 0, 0xfeacc46f);
                    fx->SetMax(0xfeacc46f, 3.402823466e+38f);
                    fx->SetScale(0xfeacc46f, 1.0f);
                    fx->SetVis(0xfeacc46f, 0);
                }
            } else if (act) {
                fx->Remove(0xfeacc46f, 0);
            }
            unsigned lo = (isOwner64 || kind == owner60) ? 0x841f707au : 0xad89ad7du;
            FUN_00ed8350(fx, 0xd55fed1a, lo, 0, kind == owner5c, 1.0f, 0);

            unsigned k = 0;
            bool fill = true;
            if (isMinus2) {
                unsigned i = 0;
                if (count188(vec) != 0) {
                    unsigned id = 0xcaf390f3u;
                    int off = 0;
                    do {
                        char* el = *(char**)vec + off;
                        if (kind == *(int*)(el + 4) || kind == *(int*)(el + 8)) {
                            int ti = *(int*)el * 3 + (int)k;
                            unsigned lo2 = g_tab108[ti * 2];
                            unsigned hi2 = g_tab108[ti * 2 + 1];
                            Fx8a30::Eff* e = fx->FindEff(id);
                            bool done = false;
                            if (e != 0) {
                                unsigned long long key = e->GetKey();
                                if (key == (((unsigned long long)hi2 << 32) | lo2)) done = true;
                                else fx->Remove(id, 0);
                            }
                            if (!done) {
                                fx->Add(lo2, hi2, id);
                                fx->SetMax(id, 3.402823466e+38f);
                                fx->SetScale(id, 1.0f);
                                fx->SetVis(id, 0);
                            }
                            k++;
                            id++;
                        }
                        i++;
                        off += 0x188;
                    } while (i < (unsigned)count188(vec));
                    if (k >= 3) fill = false;
                }
            }
            if (fill) {
                do {
                    fx->Remove(0xcaf390f3u + k, 0);
                    k++;
                } while (k < 3);
            }
        }
        int nxt = ((int*)it)[3];
        it = (nxt == 0) ? 0 : (Noun8a30*)((char*)nxt - 0xc);
    }
}

// ================================================================ 0x00ed9040
void* __cdecl FUN_00ed9040(int id, float* pos)
{
    float best = 3.402823466e+38f;
    int* found = 0;
    if (id == -1) return 0;
    void* nm = FUN_00b3d300();
    int* v = (int*)FUN_00b1f9b0(nm);
    int* end = (int*)((char*)v - 0xc);
    int* it = (*v == 0) ? 0 : (int*)((char*)*v - 0xc);
    while (it != end) {
        int esi = 0;
        if (it != 0)
            esi = ((int(__thiscall*)(void*, int))(*(void***)it)[3])(it, 0x1186577);
        float* p = (float*)((FVf_p)(*(void***)esi)[0x2c / 4])((void*)esi);
        float dx = p[0] - pos[0];
        float dy = p[1] - pos[1];
        float dz = p[2] - pos[2];
        float d = dx * dx + dy * dy + dz * dz;
        if (d < best) { best = d; found = (int*)esi; }
        int* nxt = (int*)it[3];
        it = (nxt == 0) ? 0 : (int*)((char*)nxt - 0xc);
    }
    return found;
}
