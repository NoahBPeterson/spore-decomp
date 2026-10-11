// Slice s00a3cbb0: EA::Swarm mixevent-inline command, EA::Audio mixer plugin, and
// track-vector / string helpers (0xa3cbb0-0xa3db50).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.  Callees outside the slice are
// masked relocations, so they are declared with the right calling convention only.
#include "types.h"

void* operator new(unsigned int, const char*, int, int, int, int);
void* operator new(unsigned int, const char*, int, int, const char*, int);
void operator delete(void*);
void operator delete[](void*);
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(pad_, __COUNTER__)();

#define kEastlFile \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

extern float kMapGain;                      // 0x01485720 (default gain written by the MapDescription ctor)
extern char  PTR_FUN_01453930[];            // ICommand vtable for the mixevent inline command
extern char  PTR_FUN_01453998[];            // cCreatureAbility-derived vtable
extern char  PTR_FUN_014599e8[];            // override vtable
extern char  PTR_FUN_01453918[];            // NotifyAttack command vtable
extern char  vtbl_GmeRefCount[];            // 0x013ef094  ??_7GmeRefCount@@6B@
extern char  DAT_01453a40[];                // "mixer" name literal

extern int DAT_01676458, DAT_0167645c, DAT_01676468, DAT_0167646c;
extern int s_mixer, DAT_0166ee94, DAT_0166ee98, DAT_0166ee9c, spMixerClass;

// ---- external callees (masked relocations) ----------------------------------
void SetGlobalProperty(int a, float b);
int  FNV1_String8(const char* s, unsigned seed, int flag);          // 0x00932e80
int  FUN_00a67d00(void);
void FUN_00a144c0(int* a, int* b);
void FUN_00fccdd0(int a);
void FUN_00a16fd0(int a);
int  FUN_00a17090(int n);
int  FUN_00a17100(int self);
void FUN_00a136f0(void* out, int* src, unsigned flags);
void FUN_00a24480(int a, int b);
void FUN_00a3d4c0(int count, void* p);
void FUN_00a3d5b0(void* p);
int* FUN_00a11310(int* a, int* b, int* c);
void FUN_0057cc10(int a);
void FUN_0061eba0(void);
void FUN_0061ec30(void);
int* FUN_00608310(int* out, int n);
void FUN_00a3cb20(void);
void eastl_TrackVec_erase(void* begin, void* end);                  // 0x011e0744
bool eastl_hashtable_find(void* map, void* key);                    // 0x00645ed0
void eastl_string_assign(char* a, char* b);
int* eastl_string_substr(char** out, int pos, int len);

struct EObj;   // entry object destroyed by Mixer::Release (defined below)

namespace EA {
namespace ArgScript {
struct cArguments {
    int* MainArguments(int* outCount, int mn, int mx);   // 0x00838020
};
void cCommandBase_ctor(void* p);
}}
void MixEventAddCommands(int* mgr);   // 0xa3cce0

// Object reached through map-description owner (+4); carries a virtual at slot 38.
struct VtObj {
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP     // 0..15
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP     // 16..31
    VP VP VP VP VP VP                                   // 32..37
    virtual long double Slot38(const char* s);          // +0x98
};

namespace EA {
namespace Audio {
struct MixerObj {
    VP VP VP                                            // slots 0..2
    virtual void Slot3(int a, int b, int c);            // +0x0c
    VP                                                  // slot 4
    virtual void Slot5();                               // +0x14
    virtual void Slot6(int a);                          // +0x18
    virtual void Slot7(int a);                          // +0x1c
};
struct SysObj {
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP     // slots 0..15
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP     // slots 16..31
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP     // slots 32..47
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP           // slots 48..61
    virtual int Slot62(int id);                         // +0xf8
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP     // slots 63..78
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP           // slots 79..92
    virtual MixerObj* Slot93(int x);                    // +0x174
};
SysObj* GetSystemAT(void);                              // 0x00a206f0
// The 0x444-byte mixer state object stored at the PD object's +0x28.
struct Mixer {
    char  pad0[4];
    int   m4;            // +0x04  (object passed to SysObj::Slot93)
    int   m8;            // +0x08
    int   mC;            // +0x0c
    int*  m10;           // +0x10  (track array)
    int   m14;           // +0x14  (track count)
    int   m18;           // +0x18  (active flag)
    char  pad1c[4];
    int*  mpBegin;       // +0x20  (entry list begin)
    int*  mpEnd;         // +0x24  (entry list end)
    int   m28;           // +0x28
    char  pad2c[4];
    int*  m30;           // +0x30
    int*  m34;           // +0x34
    char  pad38[4];
    int*  m3c;           // +0x3c
    void  Release();                                   // 0x00a3d150
    void  Command(int a, int b, int count, int* entries);  // 0x00a3cef0
    int   FindByIndex(int key);                        // 0x00a3d430
    int   FindByName(int key);                         // 0x00a3d480
};
namespace Eapd {
int   pd_new(void* cls);
void* getbytes(int n, const char* tag);
void  freebytes(void* p, int n);
void* gensym(void* out, const void* name);
int   class_new(void* name, void* a, void* alloc, void* dtor, int size, int a2, int a3, int a4);
void  class_addmethod(int cls, void* fn, int a, int b, int c, int d);
void  class_addanything(int cls, void* fn);
}
}
namespace Hash {
int FNV1_String8(const char* s, unsigned seed, int flag);   // 0x00932e80
}
namespace Swarm {
struct cEffectsParser;
}
}

struct MapDescription {
    virtual void Dtor();     // slot 0 (scalar-deleting at vtable[0])
    int mRefCount;           // +0x04
    unsigned mHash;          // +0x08
    float mGain;             // +0x0c
    float mField;            // +0x10
    MapDescription();
};
MapDescription::MapDescription() : mRefCount(0), mHash(0), mGain(kMapGain), mField(0.0f) {}

namespace EA { namespace Swarm {
struct cEffectsParser {
    void AddAnonDescription(ArgScript::cArguments* args, int id, MapDescription* d, int flags);   // 0x00a6fd40
};
}}

// entry object used by the mixer destruction path (vtable slots 5..7)
struct EObj {
    VP VP VP VP VP
    virtual void Slot5();          // +0x14
    virtual int  Slot6(int a);     // +0x18
};

typedef void (__thiscall *DelDtorFn)(void*, int);

// Vtable base of an object whose pointer is held as an int (matches the original's int-field layout).
inline char* VT(int obj) { return *(char**)obj; }

// The inline-command argument type: holds a value provider and the effects parser.
struct cMixEventInlineCommand {
    char pad0[4];
    VtObj* mpValueProvider;                 // +0x04
    char pad8[4];
    EA::Swarm::cEffectsParser* mpParser;    // +0x0c
    void Execute(EA::ArgScript::cArguments* args);   // 0x00a3cbb0
};

// @ 0x00a3cbb0
void cMixEventInlineCommand::Execute(EA::ArgScript::cArguments* args) {
    int count;
    int* a = args->MainArguments(&count, 1, 3);
    if (!a) return;
    MapDescription* d = (MapDescription*)::operator new(0x14, "Swarm", 0, 0, 0, 0);
    if (d) new (d) MapDescription();
    if (d) d->mRefCount++;
    d->mHash = FNV1_String8((const char*)a[0], 0x811c9dc5, 1);
    if (count > 1)
        d->mGain = (float)mpValueProvider->Slot38((const char*)a[1]);
    if (count > 2)
        d->mField = (float)mpValueProvider->Slot38((const char*)a[2]);
    mpParser->AddAnonDescription(args, 0x2d, d, 0);
    if (--d->mRefCount == 0) {
        d->mRefCount = 1;
        ((DelDtorFn)(*(void***)d)[0])(d, 1);
    }
}

// @ 0x00a3cce0
void MixEventAddCommands(int* mgr) {
    void* c1 = ::operator new(0x10, "ArgScript/MixEventInline", 0, 0, 0, 0);
    if (c1) {
        EA::ArgScript::cCommandBase_ctor(c1);
        *(void**)c1 = (void*)PTR_FUN_01453930;
    }
    (*(void(__thiscall**)(int*, const char*, void*))(VT((int)mgr) + 0x18))(mgr, "mixevent", c1);
    void* c2 = ::operator new(0xc, "Swarm", 0, 0, 0, 0);
    if (c2) {
        EA::ArgScript::cCommandBase_ctor(c2);
        *(void**)c2 = (void*)PTR_FUN_01453918;
    }
    (*(void(__thiscall**)(int*, const char*, void*))(VT((int)mgr) + 0x14))(mgr, "mixevent", c2);
}

// A small option holder: an object pointer plus "on"/"off" values.
struct MixEnableCtx {
    char    pad0[0xc];
    int     mObj;      // +0x0c
    float   mOn;       // +0x10
    float   mOff;      // +0x14
    uint8_t mState;    // +0x18
    void Enable(int arg);     // 0x00a3cdf0
    void Disable(int arg);    // 0x00a3ce10
};

// @ 0x00a3cdf0
void MixEnableCtx::Enable(int arg) {
    (void)arg;
    SetGlobalProperty(mObj, mOn);
    mState = 1;
}

// @ 0x00a3ce10
void MixEnableCtx::Disable(int arg) {
    (void)arg;
    if (mState != 0) {
        SetGlobalProperty(mObj, mOff);
        mState = 0;
    }
}

// @ 0x00a3ce40
int* FUN_00a3ce40(int self) {
    int* p = (int*)::operator new(0x1c, "Swarm", 0, 0, 0, 0);
    if (!p) return 0;
    p[1] = (int)(void*)vtbl_GmeRefCount;
    p[2] = 0;
    p[0] = (int)(void*)PTR_FUN_01453998;
    p[1] = (int)(void*)PTR_FUN_014599e8;
    p[3] = *(int*)(self + 8);
    *(float*)((char*)p + 0x10) = *(float*)(self + 0xc);
    *(uint8_t*)((char*)p + 0x18) = 0;
    *(float*)((char*)p + 0x14) = *(float*)(self + 0x10);
    return p;
}

// @ 0x00a3cea0
void FUN_00a3cea0(void) {
    DAT_01676458 = (int)(void*)FUN_00a3ce40;
    DAT_0167645c = (int)(void*)FUN_00a3cb20;
    DAT_01676468 = 1;
    DAT_0167646c = 2;
}

// @ 0x00a3ced0
void FUN_00a3ced0(int self, int a, int b) {
    int obj = *(int*)(*(int*)(self + 0x28) + 8);
    (*(void(__thiscall**)(void*, int, int, int))(VT(obj) + 0x14))((void*)obj, a, b, *(int*)(self + 0x28) + 4);
}

// @ 0x00a3cef0
void EA::Audio::Mixer::Command(int a, int b, int count, int* entries) {
    if (count <= 0) return;
    for (int i = 0; i < count; i++, entries += 3) {
        int type = entries[0];
        if (type == 1) {
            int key = a;
            EA::Audio::SysObj* sys = EA::Audio::GetSystemAT();
            EA::Audio::MixerObj* mo;
            if (sys->Slot62(a) == 0) {
                sys = EA::Audio::GetSystemAT();
                mo = sys->Slot93(m4);
                if (mo) mo->Slot3(a, key, 1);
            } else {
                if (eastl_hashtable_find((void*)((char*)this + 0xc), &key)) {
                    int obj = FUN_00a17090(0x1c);
                    if (obj) obj = FUN_00a17100((int)this);
                    if (obj) {
                        (*(void(__thiscall**)(int))VT(obj))(obj);
                    }
                    FUN_00fccdd0(a);
                    FUN_00a16fd0(key);
                    (*(void(__thiscall**)(int, int))(VT(obj) + 4))(obj, 0);
                    sys = EA::Audio::GetSystemAT();
                    mo = sys->Slot93(m4);
                    if (mo) mo->Slot6(a);
                }
            }
        } else if (type == 2) {
            int obj = m8;
            (*(void(__thiscall**)(int, int, int, int))(VT(obj) + 0x18))(obj, entries[1], entries[2], 0);
        }
    }
}

// @ 0x00a3d120
void FUN_00a3d120(int a1, int a2, int a3, int a4, int a5) {
    ((EA::Audio::Mixer*)*(int*)(a1 + 0x28))->Command(a2, a3, a4, (int*)a5);
}

// @ 0x00a3d150
void EA::Audio::Mixer::Release() {
    EA::Audio::SysObj* sys = EA::Audio::GetSystemAT();
    EA::Audio::MixerObj* mo = sys->Slot93(m4);
    if (mo) {
        int* p = m10;
        int first = *p;
        if (first == 0) {
            p++;
            first = *p;
            while (first == 0) { p++; first = *p; }
        }
        int last = *(int*)((char*)m10 + m14 * 4);
        while (first != last) {
            EObj* e = *(EObj**)(first + 4);
            e->Slot5();
            int v = e->Slot6((int)e);
            mo->Slot7(v);
            first = *(int*)(first + 8);
            while (first == 0) { p++; first = *p; }
        }
        FUN_00a24480((int)m10, m14);
        m18 = 0;
    }
    FUN_00a24480((int)m10, m14);
    int* v = m10;
    m18 = 0;
    if ((unsigned)m14 > 1 && v != m3c) {
        if (m30 <= v && v < m34) {
            *v = m28;
            m28 = (int)v;
            return;
        }
        operator delete[](v);
    }
}

// @ 0x00a3d2a0
int FUN_00a3d2a0(int a, int b, int c, int d) {
    int r = EA::Audio::Eapd::pd_new((void*)spMixerClass);
    int* m = (int*)EA::Audio::Eapd::getbytes(0x444, "EAPd/Mixer");
    *(int**)(r + 0x28) = m;
    if (m) {
        *m = r;
        m[1] = 0;
        m[2] = FUN_00a67d00();
        FUN_00a144c0(&c, &c);
    } else {
        m = 0;
    }
    *(int**)(r + 0x28) = m;
    if (c == 1) {
        int obj = m[2];
        (*(void(__thiscall**)(int, int, int, int*))(VT(obj) + 0x14))(obj, *(int*)(d + 4), *(int*)(d + 8), m + 1);
    }
    return r;
}

// @ 0x00a3d360
void FUN_00a3d360(int self) {
    ((EA::Audio::Mixer*)*(int*)(self + 0x28))->Release();
    EA::Audio::Eapd::freebytes(*(void**)(self + 0x28), 0x444);
}

// @ 0x00a3d380
int SP_Audio_Mixer_Register(void) {
    uint8_t buf[8];
    int* p = (int*)EA::Audio::Eapd::gensym(buf, "mixer");
    s_mixer = p[0];
    DAT_0166ee94 = p[1];
    p = (int*)EA::Audio::Eapd::gensym(buf, DAT_01453a40);
    DAT_0166ee98 = p[0];
    DAT_0166ee9c = p[1];
    spMixerClass = EA::Audio::Eapd::class_new((void*)s_mixer, (void*)DAT_0166ee94,
                                              (void*)FUN_00a3d2a0, (void*)FUN_00a3d360,
                                              0x30, 0, 9, 0);
    EA::Audio::Eapd::class_addmethod(spMixerClass, (void*)FUN_00a3ced0, DAT_0166ee98, DAT_0166ee9c, 2, 0);
    EA::Audio::Eapd::class_addanything(spMixerClass, (void*)FUN_00a3d120);
    return 1;
}

// @ 0x00a3d430
int EA::Audio::Mixer::FindByIndex(int key) {
    int p = (int)mpBegin;
    for (;;) {
        if (p == (int)mpEnd) return 0;
        if (*(int*)(p + 0x14) == key) break;
        p += 0x28;
    }
    return p;
}

// @ 0x00a3d480
int EA::Audio::Mixer::FindByName(int key) {
    int a = (int)mpBegin;
    int b = (int)mpEnd;
    for (;;) {
        if (a == b) return 0;
        if (eastl_hashtable_find((void*)(a + 0x18), (void*)key)) break;
        a += 0x28;
    }
    return a;
}

// An eastl string member (begin/end/capacity pointers).
struct TeString {
    void* mpBegin;     // +0x00
    void* mpEnd;       // +0x04
    void* mpCapacity;  // +0x08
    void RangeInitialize(const char* s);   // 0x0057cc10
    ~TeString();                            // external
};

// A growable vector of 0xc-stride track records plus an eastl string at +0x18.
struct TrackVec {
    int* mpBegin;    // +0x00
    int* mpEnd;      // +0x04
    int* mpCapacity; // +0x08
    char padC[8];
    int  m14;        // +0x14
    TeString mStr;   // +0x18
    TrackVec* Ctor(int a, const char* b);         // 0x00a3d630
    void DoInsertValue(int* pos, int* value);     // 0x00a3d6e0
    void Erase(int* a, int* b);                   // 0x011e0744 (eastl vector erase)
    void Dtor();                                  // 0x00a3d690
};

// @ 0x00a3d630
TrackVec* TrackVec::Ctor(int a, const char* b) {
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    m14 = a;
    mStr.mpBegin = 0;
    mStr.mpEnd = 0;
    mStr.mpCapacity = 0;
    mStr.RangeInitialize(b);
    return this;
}

// @ 0x00a3d690
void TrackVec::Dtor() {
    void* i = mStr.mpBegin;
    if (1 < (int)((char*)mStr.mpCapacity - (char*)i) && i != 0) operator delete[](i);
    Erase(mpBegin, mpEnd);
    int b = (int)mpBegin;
    if (b != 0 && *(int*)(b - 4) != 0) operator delete[]((void*)b);
}

// @ 0x00a3d6e0
void FUN_00a3d6e0(int* v, int* pos, int* value) {
    int* end = (int*)v[1];
    if (end != (int*)v[2]) {
        if (pos <= value && value < end) value += 3;
        if (end) {
            end[0] = end[-3];
            end[1] = end[-2];
            end[2] = end[-1];
        }
        int* dst = (int*)v[1];
        int* src = (int*)v[1] - 3;
        if (src != pos) {
            do {
                src -= 3;
                dst -= 3;
                dst[0] = src[0];
                dst[1] = src[1];
                dst[2] = src[2];
            } while (src != pos);
        }
        pos[0] = value[0];
        pos[1] = value[1];
        pos[2] = value[2];
        v[1] = (int)((char*)v[1] + 0xc);
        return;
    }
    int n = ((int)end - v[0]) / 0xc;
    int* nd;
    if (n == 0) {
        n = 1;
        nd = (int*)::operator new(n * 0xc, "EASTL", 0, 0, kEastlFile, 0xd1);
    } else {
        n = n * 2;
        if (n == 0) nd = 0;
        else nd = (int*)::operator new(n * 0xc, "EASTL", 0, 0, kEastlFile, 0xd1);
    }
    int* r = (int*)FUN_00a11310((int*)v[0], pos, nd);
    if (r) {
        r[0] = value[0];
        r[1] = value[1];
        r[2] = value[2];
    }
    int ni = (int)FUN_00a11310(pos, (int*)v[1], r + 3);
    if (v[0] != 0 && *(int*)(v[0] - 4) != 0) operator delete[]((void*)v[0]);
    v[0] = (int)nd;
    v[1] = ni;
    v[2] = (int)nd + n * 0xc;
}

// @ 0x00a3d810
int* FUN_00a3d810(int* out, int* first, int* last, int dst) {
    *out = dst;
    for (; first != last; first += 8) {
        int* p = (int*)*out;
        if (p) {
            p[0] = first[0];
            p[1] = first[1];
            p[2] = first[2];
            FUN_00a3d5b0(first + 3);
        }
        *out += 0x20;
    }
    return out;
}

// @ 0x00a3d8a0
int FUN_00a3d8a0(unsigned* first, unsigned* last, int acc) {
    if (first != last) {
        do {
            unsigned u = first[6];
            if (1 < (int)(first[8] - u) && u != 0) operator delete[]((void*)u);
            unsigned e = first[1];
            for (unsigned i = *first; i < e; i += 0x20) {
                int j = *(int*)(i + 0xc);
                if (j != 0 && *(int*)(j - 4) != 0) operator delete[]((void*)j);
            }
            unsigned b = *first;
            if (b != 0 && *(int*)(b - 4) != 0) operator delete[]((void*)b);
            first += 10;
            acc += 0x28;
        } while (first != last);
    }
    return acc;
}

// @ 0x00a3d920
int FUN_00a3d920(int* str, int* out) {
    if (str[1] == *str) return 0;
    FUN_0061eba0();
    FUN_0061ec30();
    char* pcVar1 = (char*)str[1];
    char* pcVar2 = (char*)*str;
    char* pcVar3;
    if (pcVar1 != pcVar2 && (pcVar3 = pcVar2, pcVar2 != pcVar1)) {
        do {
            if (*pcVar3 == ' ') break;
            pcVar3 = pcVar3 + 1;
        } while (pcVar3 != pcVar1);
        int iVar4 = (int)pcVar3 - (int)pcVar2;
        if (pcVar3 != pcVar1 && iVar4 != -1) {
            int local_2c[2];
            int* piVar5 = FUN_00608310(local_2c, iVar4);
            if (piVar5 != out) eastl_string_assign((char*)*piVar5, (char*)piVar5[1]);
            if (1 < local_2c[1] - local_2c[0] && local_2c[0] != 0) operator delete[]((void*)local_2c[0]);
            char* local_1c[2];
            piVar5 = eastl_string_substr(local_1c, iVar4, 0xffffffff);
            if (piVar5 != str) eastl_string_assign((char*)*piVar5, (char*)piVar5[1]);
            if (1 < (int)(local_1c[1] - local_1c[0]) && local_1c[0] != 0) operator delete[](local_1c[0]);
            return 1;
        }
    }
    if (str != out) eastl_string_assign(pcVar2, pcVar1);
    if ((char*)*str != (char*)str[1]) {
        *(char*)*str = 0;
        str[1] = *str;
    }
    return 1;
}

// @ 0x00a3da70
void __stdcall FUN_00a3da70(unsigned* first, unsigned* last) {
    for (; first < last; first += 10) {
        unsigned u = first[6];
        if (1 < (int)(first[8] - u) && u != 0) operator delete[]((void*)u);
        unsigned e = first[1];
        for (unsigned i = *first; i < e; i += 0x20) {
            int j = *(int*)(i + 0xc);
            if (j != 0 && *(int*)(j - 4) != 0) operator delete[]((void*)j);
        }
        unsigned b = *first;
        if (b != 0 && *(int*)(b - 4) != 0) operator delete[]((void*)b);
    }
}

// @ 0x00a3db50
int* FUN_00a3db50(int* out, int* src) {
    FUN_00a3d4c0((src[1] - *src) >> 5, src + 3);
    int tmp;
    FUN_00a3d810(&tmp, (int*)*src, (int*)src[1], *out);
    out[1] = (int)src;
    return out;
}
