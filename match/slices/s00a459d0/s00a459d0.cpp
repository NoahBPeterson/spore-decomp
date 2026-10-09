// Slice s00a459d0 - EA::Audio / Eapd atom helpers and small virtual wrappers.
#include "types.h"

// ---- stub interfaces -------------------------------------------------------
class RefC {
public:
    virtual void AddRef();       // +0x00
    virtual void Release();      // +0x04
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void M14();          // +0x14
};

class Holder {
public:
    char  pad[0x5c];
    RefC* mp;                    // +0x5c
    void  Set(RefC* p);          // @ 0xa45cb0
};

// @ 0xa45cb0
void Holder::Set(RefC* p)
{
    RefC* old = mp;
    if (p != old) {
        if (p)
            p->AddRef();
        mp = p;
        if (old)
            old->Release();
    }
    if (mp)
        mp->M14();
}

class AudioSystem {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37();
    virtual void Call98(int a, int b);                       // +0x98
    virtual void Call9c(int a, int b, int c, float f, int e); // +0x9c
    virtual void v40(); virtual void v41();
    virtual char CallA8(int a, int b, int c, int d);          // +0xa8
    virtual char CallAC(int a, int b, float c, int d);        // +0xac
    virtual void v44();
    virtual void CallB4();                                    // +0xb4
};

extern "C" AudioSystem* GetSystemAT();

extern "C" {
    extern float g_13f1160;
    extern float g_13eb1bc;
    extern void* g_p16e61a8;   // DAT_016e61a8
}

// @ 0xa45fd0
double GetAudioTime()
{
    double result = 0.0;
    if (g_p16e61a8)
        result = g_13f1160 / *(float*)((char*)g_p16e61a8 + 0xc0) +
                 *(double*)((char*)g_p16e61a8 + 8);
    return result;
}

// @ 0xa45ff0
void __stdcall AudioFunc98(int a)
{
    AudioSystem* s = GetSystemAT();
    s->Call98(a, 0);
}

// @ 0xa46010
void __stdcall AudioFunc9c(int a, int b)
{
    AudioSystem* s = GetSystemAT();
    s->Call9c(a, b, 0, g_13eb1bc, 1);
}

// @ 0xa46040
bool __stdcall AudioCopyPtr(int a, int b, void** out)
{
    *out = (void*)a;
    return true;
}

// @ 0xa46050
bool __stdcall AudioFuncAC(int a, int b, int c, float d)
{
    AudioSystem* s = GetSystemAT();
    return s->CallAC(a, b, d, 0) != 0;
}

// @ 0xa46080
bool __stdcall AudioFuncA8(int a, int b, int c, int d, int e)
{
    AudioSystem* s = GetSystemAT();
    return s->CallA8(a, b, e, 0) != 0;
}

// @ 0xa460b0
void AudioFuncB4()
{
    AudioSystem* s = GetSystemAT();
    s->CallB4();
}

// @ 0xa46690
int __stdcall AtomCheckPtr(int* p, unsigned int n)
{
    if (p != 0) {
        if (n == 0)
            return 0;
        *p = 0x3f51892;
    }
    return 1;
}

// ---- Eapd atom helpers -----------------------------------------------------
struct Sym2 {
    const char* a;
    const char* b;
};

extern Sym2 gEmptyA;   // 0x16758c4
extern Sym2 gEmptyB;   // 0x167589c

struct Atom {
    int   type;
    union {
        float f;
        const char* s;
        const char* v[2];
    };
};

// @ 0xa46760
float atom_getfloat(Atom* a)
{
    if (a->type == 1)
        return a->f;
    return 0.0f;
}

// @ 0xa46770
int atom_getint(Atom* a)
{
    if (a->type == 1)
        return (int)a->f;
    return 0;
}

// @ 0xa46790
void atom_getsymbol(Sym2* out, Atom* in)
{
    if (in->type == 2) {
        out->a = in->v[0];
        out->b = in->v[1];
    } else {
        out->a = gEmptyA.a;
        out->b = gEmptyA.b;
    }
}

extern "C" int __cdecl hk_snprintf(char* buf, unsigned int n, const char* fmt, ...);   // 0x0107f390 (equiv t2)
extern "C" void __cdecl gensym(Sym2* out, const char* name);   // 0x00a675f0 (equiv t2)

// @ 0xa467c0
Sym2* atom_gensym(Sym2* out, Atom* in)
{
    char buf[32];
    if (in->type == 2) {
        out->a = in->v[0];
        out->b = in->v[1];
        return out;
    }
    if (in->type == 1)
        hk_snprintf(buf, 32, "%g", (double)in->f);
    else
        hk_snprintf(buf, 32, "???");
    gensym(out, buf);
    return out;
}

// @ 0xa46830
Sym2* atom_vectorgensym(Sym2* out, int count, Atom* atoms)
{
    char buf[1000];
    int used = 0;
    int remain = 1000;
    int n = count;
    Atom* p = atoms;
    while (n > 0) {
        int w;
        if (p->type == 1)
            w = hk_snprintf(buf + used, remain, "%g ", (double)p->f);
        else if (p->type == 2)
            w = hk_snprintf(buf + used, remain, "%s ", p->s);
        else
            w = hk_snprintf(buf + used, remain, "??? ");
        if (w > 0) {
            used += w;
            remain -= w;
        }
        ++p;
        --n;
    }
    buf[used] = 0;
    gensym(out, buf);
    return out;
}

// @ 0xa468f0
float atom_getfloat_at(int i, int n, Atom* arr)
{
    if (n <= i)
        return 0.0f;
    if (arr[i].type != 1)
        return 0.0f;
    return arr[i].f;
}

// @ 0xa46920
int atom_getint_at(int i, int n, Atom* arr)
{
    if (n <= i)
        return 0;
    if (arr[i].type != 1)
        return 0;
    return (int)arr[i].f;
}

// @ 0xa46950
void atom_getsymbol_at(Sym2* out, int i, int n, Atom* arr)
{
    if (n <= i) {
        out->a = gEmptyB.a;
        out->b = gEmptyB.b;
        return;
    }
    if (arr[i].type == 2) {
        out->a = arr[i].v[0];
        out->b = arr[i].v[1];
        return;
    }
    out->a = gEmptyB.a;
    out->b = gEmptyB.b;
}

// ---- remaining functions (not reconstructed) -------------------------------
extern "C" int __cdecl Placeholder_459d0() { return 0; }
extern "C" int __cdecl Placeholder_45c90() { return 0; }
extern "C" int __cdecl Placeholder_45ca0() { return 0; }
extern "C" int __cdecl Placeholder_45cf0() { return 0; }
extern "C" int __cdecl Placeholder_45d00() { return 0; }
extern "C" int __cdecl Placeholder_45d10() { return 0; }
extern "C" int __cdecl Placeholder_45f30() { return 0; }
extern "C" int __cdecl Placeholder_460d0() { return 0; }
extern "C" int __cdecl Placeholder_46160() { return 0; }
extern "C" int __cdecl Placeholder_465b0() { return 0; }
extern "C" int __cdecl Placeholder_46620() { return 0; }
extern "C" int __cdecl Placeholder_466d0() { return 0; }
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
