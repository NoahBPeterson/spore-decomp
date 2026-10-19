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

// ---- EAPD voice start: helper types ---------------------------------------
struct EvSub {};
class EvResA {
public:
    virtual void AddRef();
    virtual void Release();
    char  pad[0x10];
    EvSub sub;                      // +0x14
};
class EvResB {
public:
    virtual void AddRef();
    virtual void Release();
};
class EvNode {
public:
    static void* operator new(unsigned n);     // 0x00a10750 (cdecl)
    EvNode(EvResB* b, EvSub* s);               // 0x00a10860 (thiscall, ret 8)
    char pad[0x14];
};
struct EvVar { int type; float f; int i; };
struct EvIter { int first; int second; };
struct EvVoiceKey { int a; int b; int c; };
class EvPropList {
public:
    virtual void v0();
    virtual bool Get(unsigned id, EvVar* out);                    // +4
    virtual bool Next(EvIter* it, EvVar* cur);                    // +8
};
class EvGroup {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual bool GetValue(unsigned id, float* out);               // +0x10
};
class EvSubIf {
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void SetValue(int id, float f, int one);              // +0xc
};
class EvOutV {
public:
    virtual void AddRef();
    virtual void Release();                                       // +4
    virtual void v2(); virtual void v3(); virtual void v4();
    virtual bool Finish(double t);                                // +0x14
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24();
    virtual void SetWord(int id, int v, int zero);                // +0x64
};
template<class T> struct EvRef {
    T* p;
    EvRef() : p(0) {}
    ~EvRef() { if (p) p->Release(); }
};

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
    virtual void v36();
    virtual char StartIt(int a, int handle, EvSub* q, float* pos, EvOutV** out);   // +0x94
    virtual void Call98(int a, int b);                       // +0x98
    virtual void Call9c(int a, int b, int c, float f, int e); // +0x9c
    virtual void v40(); virtual void v41();
    virtual char CallA8(int a, int b, int c, int d);          // +0xa8
    virtual char CallAC(int a, int b, float c, int d);        // +0xac
    virtual void v44();
    virtual void CallB4();                                    // +0xb4
    virtual int  GetHandle();                                  // +0xb8 (46)
    virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50();
    virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
    virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58();
    virtual void v59(); virtual void v60(); virtual void v61(); virtual void v62();
    virtual void v63(); virtual void v64();
    virtual void Attach(int group, int handle);                // +0x104 (65)
    virtual void v66(); virtual void v67(); virtual void v68(); virtual void v69();
    virtual void v70();
    virtual EvGroup* GetGroup(int group);                      // +0x11c (71)
    virtual void v72(); virtual void v73();
    virtual void Fail(int code, int handle, int a, int b, int c);  // +0x128 (74)
    virtual void v75(); virtual void v76(); virtual void v77();
    virtual void LookupA(int id, EvResB** out, int type);      // +0x138 (78)
    virtual void v79(); virtual void v80(); virtual void v81(); virtual void v82();
    virtual void v83(); virtual void v84(); virtual void v85(); virtual void v86();
    virtual void v87(); virtual void v88(); virtual void v89(); virtual void v90();
    virtual void v91(); virtual void v92(); virtual void v93(); virtual void v94();
    virtual void v95(); virtual void v96(); virtual void v97(); virtual void v98();
    virtual void LookupB(EvVoiceKey* key, EvResA** out);       // +0x18c (99)
};

extern "C" AudioSystem* GetSystemAT();   // 0x00a206f0

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
Sym2* atom_getsymbol(Sym2* out, Atom* in)
{
    if (in->type == 2) {
        out->a = in->v[0];
        out->b = in->v[1];
    } else {
        out->a = gEmptyA.a;
        out->b = gEmptyA.b;
    }
    return out;
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
Sym2* atom_getsymbol_at(Sym2* out, int i, int n, Atom* arr)
{
    if (n <= i) {
        out->a = gEmptyB.a;
        out->b = gEmptyB.b;
        return out;
    }
    if (arr[i].type == 2) {
        out->a = arr[i].v[0];
        out->b = arr[i].v[1];
        return out;
    }
    out->a = gEmptyB.a;
    out->b = gEmptyB.b;
    return out;
}


// ---- SPAudioSystem: multiple-inheritance adjustor thunks -------------------
// SPAudioSystem derives from three bases; the second and third sit at +0x15bc14 and +0x15bc18
// and re-declare the same two virtuals, so the compiler emits 'sub ecx, N; jmp' thunks:
//   0xa45c90 / 0xa45ca0 (adjust 0x15bc14), 0xa45cf0 / 0xa45d00 (adjust 0x15bc18).
struct SPAudioSystemBase0 { virtual void VMethodA(); virtual void VMethodB(); char pad[0x15bc10]; };
struct SPAudioSystemBase1 { virtual void VMethodA(); virtual void VMethodB(); };
struct SPAudioSystemBase2 { virtual void VMethodA(); virtual void VMethodB(); };
class SPAudioSystem : public SPAudioSystemBase0, public SPAudioSystemBase1, public SPAudioSystemBase2 {
public:
    virtual void VMethodA();
    virtual void VMethodB();
    SPAudioSystem();
};
SPAudioSystem::SPAudioSystem() {}   // forces the vtables (and with them the thunks) to be emitted

// ---- SPAudioVoiceManagerEAPD ----------------------------------------------
extern "C" void __cdecl EASTL_deallocate(void* p);   // 0x00f47380

struct VMNode { unsigned key; unsigned val; VMNode* next; };   // eastl pair node: key, value, next

struct VMHash {
    int       pad0;
    VMNode**  mpBucketArray;   // +4
    unsigned  mnBucketCount;   // +8
    unsigned  mnElementCount;  // +0xc
    struct Policy { float mMaxLoad; float mGrowth; unsigned mnNextResize; Policy() : mMaxLoad(1.0f), mGrowth(2.0f) {} } mPolicy;
    struct Iter { VMNode* node; VMNode** bucket; };
    unsigned  erase(const unsigned& key);                  // at 0x00a460d0
    void      find(Iter* out, const unsigned* key);        // 0x00645ed0 (thiscall, ret 8)
    void      DoFreeNodes(VMNode** buckets, unsigned n);   // 0x00693230 (thiscall, ret 8)
    VMNode**  DoAllocateBuckets(unsigned n);
    VMHash(unsigned nBuckets = 0);
    ~VMHash() throw();
};
extern VMNode* gEmptyBucketArray[2];   // 0x154df28

VMHash::VMHash(unsigned nBuckets)
{
    mnElementCount = 0;
    if (nBuckets < 2) {
        mnBucketCount = 1;
        mpBucketArray = gEmptyBucketArray;
        mPolicy.mnNextResize = 0;
    } else {
        mnBucketCount = nBuckets;
        mpBucketArray = DoAllocateBuckets(nBuckets);
    }
}

VMHash::~VMHash() throw()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        EASTL_deallocate(mpBucketArray);
}

// @ 0x00a460d0
unsigned VMHash::erase(const unsigned& key)
{
    const unsigned nPrev = mnElementCount;
    VMNode** pBucketArray = &mpBucketArray[key % mnBucketCount];
    if (*pBucketArray) {
        VMNode* pNode;
        do {
            pNode = *pBucketArray;
            if (key == pNode->key)
                break;
            pBucketArray = &pNode->next;
        } while (pNode->next);
        while (*pBucketArray && key == (*pBucketArray)->key) {
            VMNode* p = *pBucketArray;
            *pBucketArray = p->next;
            EASTL_deallocate(p);
            --mnElementCount;
        }
    }
    return nPrev - mnElementCount;
}

class IVoiceManager {
public:
    virtual ~IVoiceManager() throw() {}
    virtual double GetTime() = 0;                          // +4
};
class RefCountT {
public:
    virtual ~RefCountT() throw() {}
    int mRefCount;
    RefCountT() : mRefCount(0) {}
};
extern double gMaxAge;   // 0x013f1298

class SPAudioVoiceManagerEAPD : public IVoiceManager, public RefCountT {
public:
    VMHash mInstanceToGroup;                               // +0xc
    SPAudioVoiceManagerEAPD();                             // ctor at 0x00a465b0
    virtual ~SPAudioVoiceManagerEAPD() throw() {}          // scalar deleting dtor: 0x00a46620
    virtual double GetTime();                              // 0x00a45fd0 (vtable slot 1, same body as GetAudioTime)
    virtual bool StartVoice(int a, int unused, double time, EvPropList* props, const unsigned* key,
                    int instId, int unused2, int* out);    // 0x00a46160 (vtable slot 2)
};
double SPAudioVoiceManagerEAPD::GetTime() { return 0.0; }
// @ 0x00a465b0
SPAudioVoiceManagerEAPD::SPAudioVoiceManagerEAPD() {}

// @ 0x00a46160
bool SPAudioVoiceManagerEAPD::StartVoice(int a, int unused, double time, EvPropList* props, const unsigned* key,
                                         int instId, int unused2, int* out)
{
    if (GetTime() - time > gMaxAge)
        return false;
    bool result = false;
    AudioSystem* sys = GetSystemAT();
    if (sys) {
        int handle = sys->GetHandle();
        EvIter iter;
        iter.first = a;
        iter.second = 0;
        EvVoiceKey vk;
        vk.a = instId;
        vk.b = 0x3f51892;
        vk.c = 0x21407ee;
        EvRef<EvResA> pA;
        {
            AudioSystem* s2 = GetSystemAT();
            s2->LookupB(&vk, &pA.p);
        }
        EvRef<EvResB> pB;
        sys->LookupA(a, &pB.p, 0x21407ee);
        EvSub* q = 0;
        if (pA.p) {
            if (pB.p) {
                EvNode* n = new EvNode(pB.p, pA.p ? &pA.p->sub : 0);
                q = (EvSub*)n;
            } else {
                q = &pA.p->sub;
            }
        } else if (pB.p) {
            q = (EvSub*)pB.p;
        }
        VMHash::Iter it;
        mInstanceToGroup.find(&it, key);
        int group = 0;
        if (mInstanceToGroup.mpBucketArray[mInstanceToGroup.mnBucketCount] != it.node)
            group = (int)it.node->val;
        float vec[3] = { 0.0f, 0.0f, 0.0f };
        float* pos = 0;
        EvVar t1, t2, t3;
        if (props->Get(0x50c5d67, &t1) && props->Get(0x50c5d66, &t2) && props->Get(0x50c5d65, &t3)) {
            vec[0] = t1.f; vec[1] = t2.f; vec[2] = t3.f;
            pos = vec;
        } else if (group) {
            EvGroup* g = sys->GetGroup(group);
            float f1, f2, f3;
            if (g && g->GetValue(0x50c5d67, &f1) && g->GetValue(0x50c5d66, &f2) && g->GetValue(0x50c5d65, &f3)) {
                vec[0] = f1; vec[1] = f2; vec[2] = f3;
                pos = vec;
            }
        }
        EvRef<EvOutV> outV;
        bool ok = sys->StartIt(a, handle, q, pos, &outV.p) != 0;
        if (ok) {
            if (group)
                sys->Attach(group, handle);
            EvVar cur;
            bool more = props->Next(&iter, &cur);
            while (more) {
                if (cur.type == 0)
                    ((EvSubIf*)((char*)outV.p + 4))->SetValue(iter.first, cur.f, 1);
                else if (cur.type == 1)
                    outV.p->SetWord(iter.first, cur.i, 0);
                more = props->Next(&iter, &cur);
            }
            ok = outV.p->Finish(time);
            if (ok) {
                *out = handle;
                result = true;
            }
        }
        if (!ok)
            sys->Fail(0x3a129ee, handle, 0, 0, 0);
    }
    return result;
}

// ---- remaining functions (not reconstructed) -------------------------------
extern "C" int __cdecl Placeholder_459d0() { return 0; }
extern "C" int __cdecl Placeholder_45d10() { return 0; }
extern "C" int __cdecl Placeholder_45f30() { return 0; }
extern "C" int __cdecl Placeholder_466d0() { return 0; }
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
