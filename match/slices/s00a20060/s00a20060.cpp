// Slice s00a20060 - EA::Audio::System property routing / setup helpers.
#include "types.h"

typedef unsigned char u8;
typedef unsigned int  u32;

void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);
extern "C" unsigned int _controlfp(unsigned int, unsigned int);
unsigned int __cdecl FNV1_String8(const void* s, unsigned int basis, int flag);

void  FUN_00a0fdd0(void*);
void  FUN_00a0f9f0();
void  FUN_00a0f940();
void  FUN_00a10390(void*, void*, float);
void  FUN_00926460(void*, void*);
void  FUN_00926300();
int   FUN_00a1af50(void*);
float FUN_00a1af70(void*);
int   FUN_00a1adb0(void*);
int   FUN_00a1b3f0(void*);
int   FUN_00a1ad70(void*);
void  FUN_00a0fee0(void*);
void  FUN_00922940(void*, int);
void  FUN_00a12d80();
extern int g_166d9fc;
extern int g_166d9f4;
extern int g_166d9f8;
void  FUN_00a1fbb0();

struct Mutex {
    void Lock(void* tag);
    void Unlock();
    int  GetLocation();
};
struct ScopedLock {
    Mutex* volatile m;
    ScopedLock(Mutex* mm, void* tag) : m(mm) { m->Lock(tag); }
    ~ScopedLock() { m->Unlock(); }
};
struct Sub264 { void F(void*); };         // 00a0fee0
struct Sub20  { void F(void*, int); };    // 00922940
struct SubRel { virtual void r0(); virtual void r1(); virtual void r2(); virtual void Rel(); };
void ThreadSleep(const int*);              // 00921df0

struct DPF {
    int GetLocation();
};

struct Sub214 {
    void Release();      // 00a0fdd0
    int  Get();          // 00a0f9f0
    void Reset();        // 00a0f940
    void Add(void*, float); // 00a10390
};

struct Node {
    virtual void n0();
};

struct Obj {
    int Check();       // 00a1b3f0
    int Span();        // 00a1ad70
};

struct X119 {
    void m(void* b);   // 00926460
    void m2();         // 00926300
};

struct Sys {
    u8 pad[0x200000];

    long long GetZero(int);                       // 00a20690

    int   ReleaseSub();                           // 00a207a0
    bool  Shutdown();                             // 00a207d0
    bool  Route1(u32 id, int a, int b, float c, int d); // 00a20910
    bool  Route2(u32 id, float value);            // 00a20950
    bool  Route3(u32 id, float a, float b, float c); // 00a20990
    bool  Route4(u32 id, void* a, void* b, void* c); // 00a20a00
    void  SetSlot(int idx, void* a, void* b);     // 00a20a40
    void  GetSlot(int idx, void* out, void* big); // 00a20ac0
    void  Add214(void* a, float b);               // 00a20b20
    void  Commit214();                            // 00a20ba0
    void  Flush();                                // 00a20be0
    void  LockB8();                               // 00a210d0
    bool  HasLocation();                          // 00a21100
    bool  WithinRange(void* a, int b);            // 00a21080
    void* SlotA(int idx);                         // 00a20d20
    void* SlotB(int idx);                         // 00a20d40
    void* Field119();                             // 00a20cf0? no
    void  Tick119(int a, int b);                  // 00a20cf0
    void  Tick119b();                             // 00a20d10
};

// ---------------------------------------------------------------------------
// @ 0x00a20690
// ---------------------------------------------------------------------------
unsigned long long __stdcall GetZero(int)
{
    return 0;
}

// @ 0x00a206c0
void __fastcall SetFp(const unsigned int* p)
{
    unsigned int v = *p;
    if ((v & 0x30000) != 0x10000)
        _controlfp(v, 0x30000);
}

// @ 0x00a20700
struct EmitterSndPlayer {
    EmitterSndPlayer();
};
EmitterSndPlayer* ConstructEmitterSndPlayer()
{
    return new ("audio", 0, 0, 0, 0) EmitterSndPlayer();
}

// ---------------------------------------------------------------------------
// @ 0x00a207a0
// ---------------------------------------------------------------------------
int Sys::ReleaseSub()
{
    int n = --*(int*)((char*)this + 0x18);
    if (n <= 0) {
        *(int*)((char*)this + 0x18) = 1;
        if ((char*)this - 4 != 0)
            ((Node*)((char*)this - 4))->n0();
        return 0;
    }
    return n;
}

// @ 0x00a20910
bool Sys::Route1(u32 id, int a, int b, float c, int d)
{
    void* o = ((void* (__thiscall*)(void*, u32))((*(void***)this)[0x1d4 / 4]))(this, id);
    if (o == 0)
        return false;
    ((void (__thiscall*)(void*, int, int, float, int))((*(void***)o)[0x1c / 4]))(o, a, b, c, d);
    return true;
}

// @ 0x00a20950
bool Sys::Route2(u32 id, float value)
{
    void* o = ((void* (__thiscall*)(void*, u32))((*(void***)this)[0x1d4 / 4]))(this, id);
    if (o == 0)
        return false;
    void* s = (char*)o + 4;
    ((void (__thiscall*)(void*, int, float, int))((*(void***)s)[0xc / 4]))(
        s, 0x25df0108, value, 1);
    return true;
}

// @ 0x00a20a00
bool Sys::Route4(u32 id, void* a, void* b, void* c)
{
    void* o = ((void* (__thiscall*)(void*, u32))((*(void***)this)[0x1d4 / 4]))(this, id);
    if (o == 0)
        return false;
    ((void (__thiscall*)(void*, void*, void*, void*))((*(void***)o)[0x64 / 4]))(o, a, b, c);
    return true;
}

// @ 0x00a20a40
void Sys::SetSlot(int idx, void* a, void* b)
{
    u32* dst = (u32*)((char*)this + 0x15b6c0 + idx * 0xc);
    const u32* src = (const u32*)a;
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    ((void (__thiscall*)(void*, int))((*(void***)this)[0x38 / 4]))(this, 0x3992099);
    ((void (__thiscall*)(void*, int, int))((*(void***)this)[0x40 / 4]))(this, 0x490d2eb, idx);
    ((void (__thiscall*)(void*, int, void*))((*(void***)this)[0x50 / 4]))(this, 0x3abafae, a);
    ((void (__thiscall*)(void*, int, void*))((*(void***)this)[0x54 / 4]))(this, 0x39e41fc, b);
    ((void (__thiscall*)(void*))((*(void***)this)[0x58 / 4]))(this);
}

// @ 0x00a20ac0
struct V3 { u32 a, b, c; };
struct Big9 { u32 v[9]; };
void Sys::GetSlot(int idx, void* out, void* big)
{
    *(V3*)out = *(V3*)((char*)this + 0x15b6d8 + idx * 0xc);
    *(Big9*)big = *(Big9*)((char*)this + 0x15b6f0 + idx * 0x24);
}

// @ 0x00a20b20
void Sys::Add214(void* a, float b)
{
    ((Sub214*)((char*)this + 0x214))->Add(a, b);
}

// @ 0x00a20ba0
void Sys::Commit214()
{
    int x = ((Sub214*)((char*)this + 0x214))->Get();
    ((void (__thiscall*)(void*, int))((*(void***)this)[0x1e8 / 4]))(this, x);
    ((Sub214*)((char*)this + 0x214))->Reset();
}

// @ 0x00a20cd0
unsigned int __stdcall HashString(const void* s)
{
    return FNV1_String8(s, 0x811c9dc5, 1);
}

// @ 0x00a20cf0
void Sys::Tick119(int a, int b)
{
    (void)a;
    X119* p = *(X119**)((char*)this + 0x119ba0);
    p->m((void*)b);
}

// @ 0x00a20d10
void Sys::Tick119b()
{
    X119* p = *(X119**)((char*)this + 0x119ba0);
    p->m2();
}

// @ 0x00a20d20
void* Sys::SlotA(int idx)
{
    return (void*)((char*)this + 0x15b6c0 + idx * 0xc);
}

// @ 0x00a20d40
void* Sys::SlotB(int idx)
{
    return (void*)((char*)this + 0x15b6d8 + idx * 0xc);
}

// @ 0x00a20d60
struct Sound;
struct Sound2 {
    Sound2();
    virtual void s0();
    virtual void s1();
};
bool MakeSound(Sound2** out)
{
    if (out == 0)
        return false;
    Sound2* p = new ("Audio/Sound", 0, 0, 0, 0) Sound2();
    *out = p;
    p->s0();
    return true;
}

// @ 0x00a21080
bool Sys::WithinRange(void* a, int b)
{
    Obj* o = (Obj*)a;
    if (o->Check() != 0)
        return false;
    void** vt = *(void***)this;
    unsigned int idx = ((unsigned int (__thiscall*)(void*, int))((*(void***)o)[0x44 / 4]))(o, b);
    int got = ((int (__thiscall*)(void*, unsigned int))(vt[0x15c / 4]))(this, idx);
    unsigned int d = (unsigned int)(got - b);
    unsigned int len = (unsigned int)o->Span();
    if (d < len)
        return true;
    return false;
}

// @ 0x00a210d0
void Sys::LockB8()
{
    ((Mutex*)((char*)this + 0xb8))->Lock((void*)0x1452970);
}

// @ 0x00a21100
bool Sys::HasLocation()
{
    int n = ((DPF*)((char*)this + 0xb8))->GetLocation();
    return n > 0;
}


// @ 0x00a207d0
bool Sys::Shutdown()
{
    if (*(char*)((char*)this + 0x94) == 0)
        return false;
    Mutex* m = (Mutex*)((char*)this + 0xb8);
    *(char*)((char*)this + 0x94) = 0;
    int n;
    {
        ScopedLock guard(m, (void*)0x1452970);
        ((Sub214*)((char*)this + 0x214))->Release();
        ((Sub214*)((char*)this + 0x264))->Release();
        ((Sub214*)((char*)this + 0x304))->Release();
        ((Sub214*)((char*)this + 0x354))->Release();
        ((void (__thiscall*)(void*, int))((*(void***)this)[0x38 / 4]))(this, 0x435b26d);
        ((void (__thiscall*)(void*))((*(void***)this)[0x58 / 4]))(this);
        *(char*)((char*)this + 0x88) = 1;
        n = m->GetLocation();
        if (n > 0) {
            int k = n;
            do {
                m->Unlock();
            } while (--k != 0);
        }
        ((Sub20*)((char*)this + 0x20))->F((void*)0x1452970, 0);
        if (n > 0) {
            do {
                m->Lock((void*)0x1452970);
            } while (--n != 0);
        }
    }
    if (g_166d9f4 != 0)
        ((SubRel*)(g_166d9f4 + 4))->Rel();
    g_166d9f4 = 0;
    g_166d9f8 = 0;
    return true;
}

// @ 0x00a20990
bool Sys::Route3(u32 id, float a, float b, float c)
{
    void* o = ((void* (__thiscall*)(void*, u32))((*(void***)this)[0x1d4 / 4]))(this, id);
    if (o == 0)
        return false;
    void* s = (char*)o + 4;
    typedef void (__thiscall *Set)(void*, int, float, int);
    ((Set)((*(void***)s)[0xc / 4]))(s, 0x50c5d67, a, 1);
    ((Set)((*(void***)s)[0xc / 4]))(s, 0x50c5d66, b, 1);
    ((Set)((*(void***)s)[0xc / 4]))(s, 0x50c5d65, c, 1);
    return false;
}

// @ 0x00a20be0
void Sys::Flush()
{
    if (g_166d9fc == 0)
        return;
    char c = *(char*)((char*)this + 0x3f4);
    while (c != 0) {
        int t = 0;
        ThreadSleep(&t);
        c = *(char*)((char*)this + 0x3f4);
    }
    int seq;
    {
        ScopedLock guard((Mutex*)((char*)this + 0xb8), (void*)0x1452970);
        *(char*)((char*)this + 0x3f4) = 1;
        ((Sub264*)((char*)this + 0x264))->F((char*)this + 0x214);
        seq = *(int*)((char*)this + 0x3f8);
    }
    int cur = *(int*)((char*)this + 0x3f8);
    while (seq == cur) {
        int t = 0;
        ThreadSleep(&t);
        cur = *(int*)((char*)this + 0x3f8);
    }
}

// ---------------------------------------------------------------------------
// Sound / ordering helpers (cdecl free functions)
// ---------------------------------------------------------------------------
struct PropSet {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
    virtual void GetFloat(u32 key, float* out);   // +0x10
};
struct SoundOrd {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual bool Flag(int which, int z);          // +0x20
    virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual float Dist();                         // +0x60
    PropSet props;                                // +4 (embedded subobject with its own vptr)
    bool  Has();        // 00a1af50
    float Key1();       // 00a1af70
    float Key2();       // 00a1adb0
    u32 Flags() { return *(u32*)((char*)this + 0xce4); }
};
struct OrdInfo {
    u8 present;
    u8 pad[0xb];
    float dist;
    float key;
};

// @ 0x00a20df0
bool Less1(SoundOrd* s, bool flag, OrdInfo* info)
{
    if (s->Flag(-1, 0) && !flag)
        return true;
    if (!s->Flag(-1, 0) && flag)
        return false;
    if (s->Flags() & 0x80)
        return true;
    bool has = s->Has() != 0;
    if (!has) {
        if (info->present != 0)
            return false;
    } else if (info->present == 0) {
        return true;
    }
    float f = s->Key1();
    if (f > info->key)
        return false;
    if (info->key > f)
        return true;
    if (has && info->present != 0) {
        float d = s->Dist();
        if (d > info->dist)
            return false;
        if (info->dist > d)
            return true;
    }
    return false;
}

// @ 0x00a20eb0
bool Less2(SoundOrd* a, SoundOrd* b)
{
    bool A = a->Flag(-1, 0) && !a->Flag(3, 0) && !a->Flag(2, 0);
    bool B = b->Flag(-1, 0) && !b->Flag(3, 0) && !b->Flag(2, 0);
    if (!A) {
        if (B)
            return true;
    } else if (!B) {
        return false;
    }
    bool ca = (a->Flags() & 0x80) == 0x80;
    bool cb = (b->Flags() & 0x80) == 0x80;
    if (!ca) {
        if (cb)
            return true;
    } else if (!cb) {
        return false;
    }
    bool ha = a->Has() != 0;
    bool hb = b->Has() != 0;
    if (!ha) {
        if (hb)
            return true;
    } else if (!hb) {
        return false;
    }
    float fa = a->Key1();
    float fb = b->Key1();
    if (fa > fb)
        return true;
    if (fb > fa)
        return false;
    if (ha && hb) {
        float va = 0.0f, vb = 0.0f;
        a->props.GetFloat(0x6325c989, &va);
        b->props.GetFloat(0x6325c989, &vb);
        if (va > vb)
            return true;
        if (vb > va)
            return false;
    }
    float ga = a->Key2();
    float gb = b->Key2();
    if (ga > gb)
        return true;
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x00a20060  Sound::ConfigureSound
// ---------------------------------------------------------------------------
struct IConfig {
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
    virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
    virtual void c08();
    virtual bool GetBool(u32 key, void* out);              // +0x24
    virtual void c0a();
    virtual bool GetInt(u32 key, void* out);               // +0x2c
    virtual bool GetFloat(u32 key, void* out);             // +0x30
    virtual void c0d();
    virtual void SetStr(u32 key, void* in);                // +0x38
    virtual void* GetPtr(u32 key);                         // +0x3c
    virtual void c10();
    virtual bool GetPair(u32 key, void* a, void* b);       // +0x44
    virtual bool GetList8(u32 key, void* a, void* b);      // +0x48
    virtual bool GetList12(u32 key, void* a, void* b);     // +0x4c
};
struct Sound;
struct ResponseCurve {
    void InitFromConfiguration(IConfig* cfg, u32 key);       // 00a1a9d0
    void SetResponseCurveData(void* data, int count);        // 00a1a590
};
struct Playlist {                                             // [esi+0x2d8]
    int  Ok();                                                // 00a14690
    u32  Id();                                                // 00a146a0
};
struct BitVec {
    void Resize(int n);                                       // 0089cb60
};
struct GroupVec {
    u32* b; u32* e; u32* cap;
    void DoInsertValue(u32* pos, const u32& v);               // 00899480
    void push_back(const u32& v)
    {
        if (e < cap) {
            if (e) *e = v;
            ++e;
        } else {
            DoInsertValue(e, v);
        }
    }
};
struct Fx {                                                   // 0x1c bytes, vtable: AddRef/Release
    virtual void AddRef();
    virtual void Release();
    Fx(Sound* owner);                                         // 00a17100
    void  SetLevel(float v);                                  // 00a16fd0
    static void* operator new(unsigned size);                 // 00a17090
};
void* __cdecl memcpy_(void*, const void*, unsigned);          // 011e0744
struct ISys {                                                 // EA::Audio::System as seen by sounds
    void  Slot108(u32 id, void* a)  { ((void (__thiscall*)(void*, u32, void*))((*(void***)this)[0x108 / 4]))(this, id, a); }
    void* Slot11c(u32 id)           { return ((void* (__thiscall*)(void*, u32))((*(void***)this)[0x11c / 4]))(this, id); }
    u32   Slot0f0(void* p)          { return ((u32 (__thiscall*)(void*, void*))((*(void***)this)[0xf0 / 4]))(this, p); }
    void  Slot160(u32 a, int b, int c, void* d) { ((void (__thiscall*)(void*, u32, int, int, void*))((*(void***)this)[0x160 / 4]))(this, a, b, c, d); }
};
ISys* GetSystemAT();                                          // 00a206f0

template<int Off> inline void VThis(void* self, u32 a)
{
    ((void (__thiscall*)(void*, u32))((*(void***)self)[Off / 4]))(self, a);
}

struct Rc {                                                   // refcounted object: vtbl, count at +4
    void* vt; int rc;
};

struct Sound {
    void** vt;
    template<class T> T& at(int off) { return *(T*)((char*)this + off); }
    bool ConfigureSound();
};

static inline u32 Id(u32 x) { return x; }

bool Sound::ConfigureSound()
{
    ((void (__thiscall*)(void*))(vt[0x94 / 4]))(this);
    ISys* sys = GetSystemAT();
    if (sys == 0)
        return false;
    IConfig* cfg = (IConfig*)((char*)this + 0xe4);
    at<u32>(0x40) = at<u32>(0x38);
    cfg->GetInt(0x51997db2, &at<u32>(0xcdc));
    cfg->GetInt(0xd9ec19d6, &at<u32>(0xce0));
    cfg->GetBool(0xfd9003a3, &at<u8>(0x9f));
    if (cfg->GetFloat(0xb1f42539, &at<u8>(0xcd0)))
        at<u32>(0xce4) |= 0x400;
    u8 flag;
    if (cfg->GetBool(0xd1daef42, &flag) && flag)
        at<u32>(0xce4) |= 0x1000;
    if (cfg->GetBool(0x6257eb2a, &flag) && flag)
        at<u8>(0xcd4) = 1;
    if (cfg->GetBool(0x3c10c7b9, &flag) && flag)
        at<u8>(0xcd5) = 1;
    VThis<0x74>(this, 0x2406a047);
    VThis<0x74>(this, 0x25df0108);
    VThis<0x74>(this, 0x0f616b72);
    VThis<0x74>(this, 0x03593710);
    VThis<0x74>(this, 0x29e8b9f8);
    VThis<0x74>(this, 0x8fc9308e);
    VThis<0x74>(this, 0x56e7c242);
    VThis<0x74>(this, 0x71bc3009);
    VThis<0x74>(this, 0x98ac8996);
    VThis<0x74>(this, 0xe8ab99b9);
    VThis<0x74>(this, 0x8fc9308e);
    VThis<0x74>(this, 0x393f7f7d);
    VThis<0x74>(this, 0x49eb68db);
    VThis<0x74>(this, 0x6eb7a717);
    VThis<0x74>(this, 0x9d554d95);
    VThis<0x74>(this, 0xc57f4567);
    u8 flag2;
    if (cfg->GetBool(0x12d2a4d4, &flag2)) {
        if (flag2)
            at<u8>(0xc0) |= 8;
        else
            at<u8>(0xc0) &= 0xf7;
    }
    cfg->GetBool(0x6dd08218, &at<u8>(0x9d));
    cfg->GetBool(0xba134192, &at<u8>(0xa0));
    cfg->GetInt(0xbaf7f4f9, &at<u32>(0x330));
    cfg->SetStr(0x07f28acc, &at<u32>(0x334));
    cfg->GetInt(0xed1f36d5, &at<u32>(0xa4));
    cfg->GetInt(0x6610c2bd, &at<u32>(0xe0));
    cfg->GetFloat(0xc742ceb8, &at<u32>(0x60));
    {
        u32 l18, l20;
        if (cfg->GetList12(0x701ed91e, &l20, &l18)) {
            Rc*& pl = at<Rc*>(0x2d8);
            Rc* old = pl;
            if (old) {
                pl = 0;
                int n = (*(volatile int*)&old->rc += -1);
                if (n == 0) {
                    old->rc = 1;
                    ((void (__thiscall*)(void*, int))(((void***)old)[0][0]))(old, 1);
                }
            }
            sys->Slot160(at<u32>(0x38), (int)l18, (int)l20, &pl);
        } else {
            cfg->SetStr(0x701ed91e, &at<u32>(0x2d8));
        }
    }
    static u32 kA = Id(0x0f70317c);
    static u32 kB = Id(0x09d0b38e);
    at<ResponseCurve>(0xcec).InitFromConfiguration(cfg, kA);
    at<ResponseCurve>(0x1050).InitFromConfiguration(cfg, kB);
    at<ResponseCurve>(0x13b4).InitFromConfiguration(cfg, 0x173c2710);
    {
        int cnt; void* data;
        if (cfg->GetPair(0x9bfc37ac, &data, &cnt)) {
            at<u32>(0xce4) |= 0x4000;
            at<ResponseCurve>(0x1718).SetResponseCurveData(data, cnt >> 1);
        }
    }
    if (at<Playlist*>(0x2d8)) {
        if (at<Playlist*>(0x2d8)->Ok())
            at<u32>(0x40) = at<Playlist*>(0x2d8)->Id();
    }
    {
        u32 count; u32* arr;
        if (cfg->GetList12(0x7cb81a35, &count, &arr) && count) {
            GroupVec& groups = at<GroupVec>(0x2e0);
            while (count) {
                --count;
                u32 id = arr[0];
                arr += 3;
                sys->Slot108(id, (char*)this + 4);
                groups.push_back(id);
            }
        }
    }
    {
        u32 count; u32* arr;
        if (cfg->GetList8(0xa095ea05, &count, &arr)) {
            at<BitVec>(0xc3c).Resize(count);
            memcpy_(*(void**)&at<BitVec>(0xc3c), arr, count * 4);
            cfg->GetInt(0xa25a9f30, &at<u32>(0xce8));
            at<ResponseCurve>(0x1a7c).InitFromConfiguration(cfg, 0x9b3918c4);
            Fx* fx = new Fx(this);
            Fx* old = at<Fx*>(0xc38);
            if (fx != old) {
                if (fx) fx->AddRef();
                at<Fx*>(0xc38) = fx;
                if (old) old->Release();
            }
            at<Fx*>(0xc38)->SetLevel(1.0f);
            while (count--) {
                u32 id = *arr++;
                void* o = GetSystemAT()->Slot11c(id);
                if (o)
                    ((void (__thiscall*)(void*, u32, void*))((*(void***)o)[0x18 / 4]))(o, at<u32>(0xce8), at<Fx*>(0xc38));
            }
        }
    }
    void* p = cfg->GetPtr(0x2fe09c83);
    if (p)
        at<u32>(0x320) = GetSystemAT()->Slot0f0(p);
    ((void (__thiscall*)(void*))(vt[0xb0 / 4]))(this);
    return true;
}
