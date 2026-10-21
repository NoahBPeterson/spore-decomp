// Slice s00a102e0 (gold1 batch, MSVC 2008 SP1 /O2 /MD /Gy /EHsc /TP).
// Three unrelated modules share this address range:
//   - a growable byte-buffer serialization writer (0xa102e0..0xa10670)
//   - a small refcounted tree/observer helper (0xa10780..0xa10e90)
//   - the rw audio core bit reader, resource-key formatter and EA::Audio::EmitterSndPlayer
//     sample player methods (0xa10ef0..0xa113c0).
#include "types.h"

// =====================================================================================
// External callees (defined in other slices / libraries).
// =====================================================================================
extern "C" __declspec(dllimport) char* __cdecl strncpy(char*, const char*, unsigned);

void* __cdecl f_00a206f0_GetSystemAT();

// EA::Audio::ResponseCurve (lives at EmitterSndPlayer+0x10)
struct ResponseCurve {
    void InitFromConfiguration(void*, unsigned);
    void ApplySetting(unsigned, int);
};
// EA::Audio::VoiceContainer (lives at EmitterSndPlayer+0x38c)
struct VoiceContainer {
    void SetValue(int);
    void Reconnect();
};
// rw::audio::core::System (the object a command is issued on)
struct RwSystem {
    void IsCommandComplete(int, float);
};
// audio system singleton support object
struct SysGlobal {
    bool Check(void*);
    void DoA();
    void DoB();
};
// eastl rbtree base (0x9a9600)
struct TreeBase {
    void Nuke(void*);
};

extern float g_1473c70;
extern float g_1471064;
extern float g_1470f1c;
extern float g_1485720;
extern void* g_16e61a8;
extern void* g_166d868;

// =====================================================================================
// Serialization writer.
//   +0x00 base, +0x04 end, +0x2c write, +0x30 read, +0x34 mark0, +0x38 mark1,
//   +0x3c count-slot, +0x44 size, +0x48 count.
// =====================================================================================
struct Serializer {
    uint8_t* mpBase;      // 0x00
    uint8_t* mpEnd;       // 0x04
    uint8_t* mpPad08[9];  // 0x08
    uint8_t* mpWrite;     // 0x2c
    uint8_t* mpRead;      // 0x30
    uint8_t* mpMark0;     // 0x34
    uint8_t* mpMark1;     // 0x38
    uint32_t* mpCountSlot;// 0x3c
    uint32_t mPad40;      // 0x40
    uint32_t mSize;       // 0x44
    uint32_t mCount;      // 0x48

    void Grow(uint32_t);
    void WriteBytes(const void*, uint32_t);
    void WriteFloatRaw(int, float); // 0xa10060 (elsewhere)

    __forceinline void Ensure(uint32_t n) {
        if ((uint32_t)(mpBase - mpWrite) + mSize < n) Grow((uint32_t)(mpEnd - mpBase) * 2);
    }
    __forceinline void W32(uint32_t v) {
        Ensure(4);
        *(uint32_t*)mpWrite = v;
        mpWrite += 4;
    }
    __forceinline void W32p(const uint32_t* p) {
        Ensure(4);
        if (p) *(uint32_t*)mpWrite = *p;
        mpWrite += 4;
    }

    void BeginTree(uint32_t id);                            // 0xa102e0
    void WriteFloat(int, float);                            // 0xa10390
    void WriteString(int, const char*, int);                // 0xa103c0
    void WriteBlob(int, const void*, int);                  // 0xa10490
    void WriteVec3(int, const uint32_t*);                   // 0xa10540
    void WriteArr9(int, const uint32_t*);                   // 0xa10670
};

// @ 0x00A102E0
void Serializer::BeginTree(uint32_t id) {
    if (mpMark1 != 0 && mpMark0 != 0) {
        mpWrite = mpMark0;
        mpMark0 = 0;
        mpMark1 = 0;
        mpCountSlot = 0;
    }
    mpMark0 = mpWrite;
    W32(id);
    mpMark1 = mpWrite;
    W32(0);
    mpCountSlot = (uint32_t*)mpWrite;
    W32(0);
    mCount = 0;
}

// @ 0x00A10390
void Serializer::WriteFloat(int id, float v) { WriteFloatRaw(id, v); }

// @ 0x00A103C0
void Serializer::WriteString(int id, const char* s, int n) {
    if (n == 0) {
        const char* p = s;
        while (*p) ++p;
        n = (int)(p - s);
    }
    ++n;
    W32((uint32_t)id);
    W32((uint32_t)n);
    W32(3);
    WriteBytes(s, (uint32_t)n);
    ++mCount;
    *mpCountSlot = mCount;
}

// @ 0x00A10490
void Serializer::WriteBlob(int id, const void* data, int n) {
    W32((uint32_t)id);
    W32((uint32_t)n);
    W32(5);
    WriteBytes(data, (uint32_t)n);
    ++mCount;
    *mpCountSlot = mCount;
}

// @ 0x00A10540
void Serializer::WriteVec3(int id, const uint32_t* p) {
    W32((uint32_t)id);
    W32(0xc);
    W32(6);
    W32p(p);
    W32p(p + 1);
    W32p(p + 2);
    ++mCount;
    *mpCountSlot = mCount;
}

// @ 0x00A10670
void Serializer::WriteArr9(int id, const uint32_t* p) {
    W32((uint32_t)id);
    W32(0x24);
    W32(7);
    for (int i = 0; i < 9; ++i) W32p(p + i);
    ++mCount;
    *mpCountSlot = mCount;
}

// =====================================================================================
// Refcounted observer/tree helper.
// =====================================================================================
struct IChild {
    virtual void AddRef();                   // 0x00
    virtual void Release();                  // 0x04
    virtual bool q08(int);                   // 0x08
    virtual void q0c(void*, int);            // 0x0c
    virtual void q10(void*, int);            // 0x10
    virtual void q14(int);                   // 0x14
    virtual bool q18(int);                   // 0x18
    virtual void q1c(); virtual void q20(); virtual void q24(); virtual void q28();
    virtual void q2c(); virtual void q30(); virtual void q34(); virtual void q38();
    virtual int  q3c(int);                   // 0x3c
    virtual int  q40(int);                   // 0x40
    virtual bool q44(int, int, int);         // 0x44
    virtual bool q48(int, int, int);         // 0x48
    virtual bool q4c(int, int, int);         // 0x4c
};

struct Ability {
    void*   vtbl0;   // 0x00
    void*   vtbl1;   // 0x04
    int     ref;     // 0x08
    IChild* childA;  // 0x0c
    IChild* childB;  // 0x10

    void* ctor();                         // 0xa107a0
    void  dtor();                         // 0xa10800
    Ability* ctor2(IChild*, IChild*);     // 0xa10860
    bool  q08(int);                       // 0xa10960
    void  q10(void*, int);                // 0xa109a0
    void  q14(int);                       // 0xa109d0
    bool  q18(int);                       // 0xa10a00
    int   q3c(int);                       // 0xa10cc0
    int   q40(int);                       // 0xa10d00
    bool  q44(int, int, int);             // 0xa10d40
    bool  q48(int, int, int);             // 0xa10da0
    bool  q4c(int, int, int);             // 0xa10e00
    void  q0c(void*, char);                // 0xa10e90
};

// @ 0x00A10780
void f_00a10780(void** node) {
    *node = g_166d868;
    g_166d868 = node;
}
void* g_166d868;

// @ 0x00A107A0
void* Ability::ctor() {
    vtbl1 = (void*)0x13ef094;
    ref = 0;
    vtbl0 = (void*)0x14492a0;
    vtbl1 = (void*)0x1449298;
    childA = 0;
    childB = 0;
    return this;
}

// @ 0x00A10800
void Ability::dtor() {
    if (childB) childB->Release();
    if (childA) childA->Release();
    vtbl1 = (void*)0x13ef094;
}

// @ 0x00A10860
Ability* Ability::ctor2(IChild* a, IChild* b) {
    vtbl1 = (void*)0x13ef094;
    ref = 0;
    vtbl0 = (void*)0x14492a0;
    vtbl1 = (void*)0x1449298;
    childA = a;
    if (a) a->AddRef();
    childB = b;
    if (b) b->AddRef();
    return this;
}

// @ 0x00A10960
bool Ability::q08(int x) {
    if (childA && childA->q08(x)) return true;
    if (childB && childB->q08(x)) return true;
    return false;
}

// @ 0x00A109A0
void Ability::q10(void* p, int x) {
    IChild* c = childA;
    if (c) return c->q10(p, x);
    c = childB;
    if (c) return c->q10(p, x);
}

// @ 0x00A109D0
void Ability::q14(int x) {
    IChild* c = childA;
    if (c) c->q14(x);
    c = childB;
    if (c) c->q14(x);
}

// @ 0x00A10A00
bool Ability::q18(int x) {
    return (childA && childA->q18(x)) || (childB && childB->q18(x));
}

// @ 0x00A10CC0
int Ability::q3c(int x) {
    int r = 0;
    IChild* c = childA;
    if (c) { r = c->q3c(x); if (r) return r; }
    c = childB;
    if (c) r = c->q3c(x);
    return r;
}

// @ 0x00A10D00
int Ability::q40(int x) {
    int r = 0;
    IChild* c = childA;
    if (c) { r = c->q40(x); if (r) return r; }
    c = childB;
    if (c) r = c->q40(x);
    return r;
}

// @ 0x00A10D40
bool Ability::q44(int a, int b, int c) {
    return (childA && childA->q44(a, b, c)) || (childB && childB->q44(a, b, c));
}

// @ 0x00A10DA0
bool Ability::q48(int a, int b, int c) {
    return (childA && childA->q48(a, b, c)) || (childB && childB->q48(a, b, c));
}

// @ 0x00A10E00
bool Ability::q4c(int a, int b, int c) {
    return (childA && childA->q4c(a, b, c)) || (childB && childB->q4c(a, b, c));
}

// @ 0x00A10E90
void Ability::q0c(void* p, char flag) {
    if (flag) {
        ((TreeBase*)p)->Nuke(*(void**)((char*)p + 0xc));
        *(void**)((char*)p + 4) = (char*)p + 4;
        *(void**)((char*)p + 8) = (char*)p + 4;
        *(void**)((char*)p + 0xc) = 0;
        *(uint8_t*)((char*)p + 0x10) = 0;
        *(void**)((char*)p + 0x14) = 0;
    }
    IChild* c = childA;
    if (c) c->q0c(p, 0);
    c = childB;
    if (c) c->q0c(p, 0);
}

// =====================================================================================
// rw::audio::core::BitGetter -- little-endian bit reader.
// =====================================================================================
struct BitGetter {
    uint8_t* mpBitBuffer;   // 0x00
    uint32_t mBitPosition;  // 0x04
    uint32_t GetBits(uint32_t n);
};

// @ 0x00A10EF0
uint32_t BitGetter::GetBits(uint32_t n) {
    uint32_t result = 0;
    if (n != 0) {
        do {
            uint32_t pos = mBitPosition;
            uint32_t avail = 8 - (pos & 7);
            uint32_t take = avail > n ? n : avail;
            uint8_t  b = mpBitBuffer[pos >> 3];
            result = ((b >> (8 - (pos & 7) - take)) & ((1u << take) - 1)) | (result << take);
            mBitPosition = pos + take;
            n -= take;
        } while (n != 0);
    }
    return result;
}

// @ 0x00A10F70
namespace EA { namespace Audio {
class ResourceDeviceDriver { public:
    static bool KeyToText(uint8_t* key, char* text, uint32_t* size);
};
bool ResourceDeviceDriver::KeyToText(uint8_t* key, char* text, uint32_t* size) {
    int n = 12;
    if (*size < 0x20) {
        *size = 0x20;
        return false;
    }
    strncpy(text, "resman:", 7);
    text += 7;
    do {
        uint8_t b = *key++;
        *text++ = (char)((b & 0xf) + 'A');
        *text++ = (char)((b >> 4) + 'A');
    } while (--n);
    *text = 0;
    *size = 0x20;
    return true;
}
}} // namespace EA::Audio

// =====================================================================================
// EA::Audio::EmitterSndPlayer
// =====================================================================================
struct EmitterSndPlayer {
    unsigned char m[0xdd0];

    __forceinline void** Vt() { return (void**)*(void**)&m[0]; }

    uint32_t SetFlag(uint32_t mask, char flag);  // 0xa10fe0
    bool     Init();                             // 0xa11010
    bool     q11050();                           // 0xa11050
    bool     q11080(char);                       // 0xa11080
    void     q110c0(const uint32_t*);            // 0xa110c0
    bool     SetData(uint32_t, uint32_t, uint32_t); // 0xa11100
    void     Tick();                             // 0xa11190
    bool     FinalStop(float);                   // 0xa111c0
    bool     q11210(float);                      // 0xa11210
    bool     q11270(float);                      // 0xa11270
    void     q112c0();                           // 0xa112c0
    EmitterSndPlayer* q11350();                  // 0xa11350
    void     q11370();                           // 0xa11370
    bool     Shutdown();                         // 0xa11380
    bool     Create();                           // 0xa113c0
};

// @ 0x00A10FE0
uint32_t EmitterSndPlayer::SetFlag(uint32_t mask, char flag) {
    uint32_t* p = (uint32_t*)(m + 0xd84);
    if (flag) *p |= mask;
    else      *p &= ~mask;
    return *p;
}

// @ 0x00A11010
bool EmitterSndPlayer::Init() {
    uint32_t* flags = (uint32_t*)(m + 0xd84);
    if (*flags & 1) return false;
    *flags |= 1;
    void* sys = f_00a206f0_GetSystemAT();
    ((void(__thiscall*)(void*, void*, int, int))((void**)*(void**)sys)[0x184 / 4])(sys, m + 0xd24, 0, 0);
    return true;
}

// @ 0x00A11050
bool EmitterSndPlayer::q11050() {
    if (!(*(uint32_t*)(m + 0xd84) & 0x10)) return false;
    ((void(__thiscall*)(void*))Vt()[0x5c / 4])(this);
    uint32_t f = *(uint32_t*)(m + 0xd84);
    f = (f & 0xffffffdf) | 0x80;
    *(uint32_t*)(m + 0xd84) = f;
    return true;
}

// @ 0x00A11080
bool EmitterSndPlayer::q11080(char v) {
    if (*(char*)(m + 0xd28) != v) {
        *(char*)(m + 0xd29) = 1;
        *(char*)(m + 0xd28) = v;
    }
    return true;
}

// @ 0x00A110C0
void EmitterSndPlayer::q110c0(const uint32_t* p) {
    *(uint32_t*)(m + 0xcf0) = p[0];
    *(uint32_t*)(m + 0xcf4) = p[1];
    *(uint32_t*)(m + 0xcf8) = p[2];
    *(uint32_t*)(m + 0xcf4) = 0x1a527db;
    *(char*)(m + 0xd2a) = 0;
}

// @ 0x00A11100
bool EmitterSndPlayer::SetData(uint32_t id, uint32_t value, uint32_t) {
    if (id != 0x2fe09c83) {
        if (id == 0x6e3d22e0) {
            ((ResponseCurve*)(m + 0x10))->ApplySetting(value, 0);
        }
        return true;
    }
    void* sys = f_00a206f0_GetSystemAT();
    int r = ((int(__thiscall*)(void*, int))((void**)*(void**)sys)[0xf4 / 4])(sys, (int)value);
    ((VoiceContainer*)(m + 0x38c))->SetValue(r);
    ((VoiceContainer*)(m + 0x38c))->Reconnect();
    return true;
}

// @ 0x00A11190
void EmitterSndPlayer::Tick() {
    void* sys = f_00a206f0_GetSystemAT();
    ((void(__thiscall*)(void*, int, int, int, int, int))((void**)*(void**)sys)[0x128 / 4])(
        sys, 0x3a0fd6e, *(int*)(m + 0xd0c), 0, 0, 0);
    ((void(__thiscall*)(void*))Vt()[0x18 / 4])(this);
}

// @ 0x00A111C0
bool EmitterSndPlayer::FinalStop(float f) {
    *(uint32_t*)(m + 0xd88) &= ~4;
    if (f < 0.0f || f > g_1473c70) return false;
    void* p = *(void**)(m + 0xd70);
    if (!p) return false;
    ((RwSystem*)p)->IsCommandComplete(0, f);
    return true;
}

// @ 0x00A11210
bool EmitterSndPlayer::q11210(float f) {
    *(uint32_t*)(m + 0xd88) &= ~8;
    if (g_1471064 > f || f > g_1470f1c) return false;
    void* p = *(void**)(m + 0xd78);
    if (!p) return false;
    if (*(int*)(m + 0xd24) < 2) f = g_1485720;
    ((RwSystem*)p)->IsCommandComplete(0, f);
    return true;
}

// @ 0x00A11270
bool EmitterSndPlayer::q11270(float f) {
    *(uint32_t*)(m + 0xd88) &= ~1;
    if (f < 0.0f || f > g_1485720) return false;
    void* p = *(void**)(m + 0xd74);
    if (!p) return false;
    ((RwSystem*)p)->IsCommandComplete(0, f);
    return true;
}

// @ 0x00A112C0
void EmitterSndPlayer::q112c0() {
    if (!g_16e61a8) return;
    if (!((SysGlobal*)g_16e61a8)->Check(*(void**)(m + 0xcec))) return;
    if (*(uint32_t*)(m + 0xd84) & 2) {
        *(uint32_t*)(m + 0xd84) &= ~2;
        void* arg = m + 4;
        void* sys = f_00a206f0_GetSystemAT();
        ((void(__thiscall*)(void*, void*))((void**)*(void**)sys)[0x74 / 4])(sys, arg);
    }
    ((void(__thiscall*)(void*))Vt()[4 / 4])(this);
}

// @ 0x00A11310
void f_00a11310(const void* src, const void* end, void* dst) {
    if (src == end) return;
    do {
        if (dst) {
            ((uint32_t*)dst)[0] = ((const uint32_t*)src)[0];
            ((uint32_t*)dst)[1] = ((const uint32_t*)src)[1];
            ((uint32_t*)dst)[2] = ((const uint32_t*)src)[2];
        }
        src = (const char*)src + 12;
        dst = (char*)dst + 12;
    } while (src != end);
}

// @ 0x00A11350
EmitterSndPlayer* EmitterSndPlayer::q11350() {
    if (g_16e61a8) ((SysGlobal*)g_16e61a8)->DoA();
    return this;
}

// @ 0x00A11370
void EmitterSndPlayer::q11370() {
    if (g_16e61a8) ((SysGlobal*)g_16e61a8)->DoB();
}

// @ 0x00A11380
bool EmitterSndPlayer::Shutdown() {
    void* z = 0;
    if (*(uint32_t*)(m + 0xd84) & 1) {
        ((void(__thiscall*)(void*))Vt()[0x18 / 4])(this);
        *(uint32_t*)(m + 0xd84) &= ~1;
    }
    void* p = *(void**)(m + 0x378);
    if (p != z) {
        *(void**)(m + 0x378) = z;
        ((void(__thiscall*)(void*))((void**)*(void**)p)[4 / 4])(p);
    }
    *(void**)(m + 0xdc8) = z;
    return true;
}

// @ 0x00A113C0
bool EmitterSndPlayer::Create() {
    if (*(uint32_t*)(m + 0xd84) & 0x20) return false;
    if (*(void**)(m + 0x374)) {
        void* cfg = *(void**)(m + 0x374);
        if (((bool(__thiscall*)(void*, int))((void**)*(void**)cfg)[0x18 / 4])(cfg, 0x79da6d74)) {
            uint32_t local[3] = {0, 0, 0};
            void* c = *(void**)(m + 0x374);
            ((void(__thiscall*)(void*, int, void*))((void**)*(void**)c)[0x34 / 4])(c, 0x79da6d74, local);
            *(uint32_t*)(m + 0xd14) = local[0];
        }
        void* c1 = *(void**)(m + 0x374);
        ((ResponseCurve*)(m + 0x10))->InitFromConfiguration(c1, 0x1e4db1eb);
        void* c2 = *(void**)(m + 0x374);
        ((void(__thiscall*)(void*, void*, int))((void**)*(void**)c2)[0x2c / 4])(c2, m + 0xd20, 0xed1f36d5);
        void* c3 = *(void**)(m + 0x374);
        uint32_t r = 0;
        if (((bool(__thiscall*)(void*, int, void*))((void**)*(void**)c3)[0x24 / 4])(c3, 0x12d2a4d4, &r)) {
            SetFlag(4, (char)r);
        }
    }
    return ((int(__thiscall*)(void*))Vt()[0x4c / 4])(this) != 0;
}
