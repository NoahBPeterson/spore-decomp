// Slice s007c77e0 -- SP::cConfigManager / ArgScript option commands (retail build).
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// ---------------------------------------------------------------- masked externs
uint32_t __cdecl FNVHash(const char* p, uint32_t hash, int ignore);              // 0x00932e80
void*    __cdecl EA_New(unsigned size, const char* name, int, int, const char*, int); // 0x00f473a0
void     __cdecl EA_Free(void* p);                                               // 0x00f47380
void*    __cdecl CreateParser();                                                 // 0x008408d0
void*    __cdecl CheatManager();                                                 // 0x0067de20
void*    __cdecl GetSaveArea(const char* name);                                  // 0x006b1f90
bool     __cdecl SaveResource(void* res, void* area, int flags);                 // 0x006b1d50
void*    __cdecl FormatString(int idx, const char* fmt, const char* arg);        // 0x00840810
void     __cdecl FormatDouble(double v, char* out, int len, int prec, int flags);// 0x0092d730
void*    __cdecl DesktopDisplayMode(void* out);                                  // 0x011f8270
int      __cdecl TryGetUIntProperty(void* prop, unsigned key, uint32_t* out);    // 0x00410370
void     __cdecl RegisterConfigScriptCommands(void* parser);                     // 0x007c8530

typedef void (__thiscall *VFn0)(void*);
typedef void (__thiscall *VFn1)(void*, void*);
typedef void (__thiscall *VFn2P)(void*, void*, void*);
typedef void (__thiscall *VFn2)(void*, int, int);
typedef void* (__thiscall *VFnR)(void*);
typedef void* (__thiscall *VFnR1)(void*, void*);
typedef int (__thiscall *VFnI1)(void*, void*);
#define VSLOT(obj, byteoff) (*(void***)(obj))[(byteoff) / 4]

extern const char  g_saveAreaName[];  // 0x011ac192
extern const uint8_t g_randomData[];  // 0x01410708

// operator new used by the ArgScript command registration code (6-arg EA form).
inline void* operator new(size_t size, const char* pName, int flags, unsigned dbg, const char* file, int line)
{ return EA_New((unsigned)size, pName, flags, (int)dbg, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}

// ---------------------------------------------------------------- globals
extern const uint32_t g_BitLengthTable[];   // 0x01410e24
extern void* g_sAppPreferences;             // 0x015fd91c
extern void* g_CmdKey_setting;              // 0x0153d204
extern void* g_CmdKey_boolProp;             // 0x0153d208
extern void* g_CmdKey_intProp;              // 0x0153d20c
extern void* g_CmdKey_floatProp;            // 0x0153d210
extern void* g_CmdKey_keyProp;              // 0x0153d214
extern void* g_CmdKey_props;                // 0x0153d218
extern void* g_CmdKey_option;               // 0x0153d200
extern void* g_CmdKey_vendor;               // 0x0153d22c
extern void* g_CmdKey_setVariables;         // 0x0153d1ec
extern void* g_CmdKey_setOption;            // 0x0153d21c
extern void* g_CmdKey_alert;                // 0x0153d220
extern void* g_CmdKey_setResolution;        // 0x0153d224
extern void* g_CmdKey_boolProp2;            // 0x0153d1f0
extern void* g_CmdKey_intProp2;             // 0x0153d1f4
extern void* g_CmdKey_floatProp2;           // 0x0153d1f8
extern void* g_CmdKey_keyProp2;             // 0x0153d1fc
extern void* g_CmdKey_card;                 // 0x0153d228

// ---------------------------------------------------------------- types
struct RC { virtual void AddRef(); virtual void Release(); };  // refcount interface

struct AutoRefCount {
    uint32_t m0;
    uint32_t m4;
    RC*      mRC;
    uint32_t mPad;
};

struct String16 { char* mpBegin; char* mpEnd; char* mpCap; int mAlloc; };

struct cOption {
    uint32_t mID;            // +0x00
    uint32_t mDefault;       // +0x04
    uint32_t mCurrent;       // +0x08
    uint8_t* mResBegin;      // +0x0c
    uint8_t* mResEnd;        // +0x10
    char pad14[0xac - 0x14];
};

struct cConfigScriptState {
    char pad00[0x44];
    cOption* mOptionsBegin;     // +0x44
    cOption* mOptionsEnd;       // +0x48
    char pad4c[0x60 - 0x4c];
    String16* mConfigStrings;   // +0x60
    char pad64[0x74 - 0x64];
    float*   mConfigNumbers;    // +0x74

    bool SetOptionDefault(uint32_t id, uint32_t value);  // 0x007c7ac0
    void DumpAll(void* args);                            // 0x007c7b30
};

struct cConfigManager {
    char pad0[0xc];
    RC*  mFileParser;           // +0x0c
    void* mScriptParser;        // +0x10
    char pad14[0x20 - 0x14];
    cConfigScriptState mState;  // +0x20

    int  GetOption(uint32_t id);                                  // 0x007c7c40
    int  GetOptionDefault(uint32_t id);                           // 0x007c7c70
    int  GetNumScreenResolutions();                               // 0x007c7ca0
    bool GetScreenResolutionInfo(int i, uint32_t*, uint32_t*, uint32_t*); // 0x007c7cd0
    bool SavePreferences();                                       // 0x007c7a10
    bool Shutdown();                                              // 0x007c7be0
    void SetScriptPath(const void* a, const void* b);             // 0x007c8880
};

// The string-seeded LFSR byte generator used by the config system.
struct cRandom {
    char pad0[4];
    const uint8_t* mData;   // +0x04
    uint32_t mSize;         // +0x08
    uint32_t mPos;          // +0x0c
    uint32_t mPoly;         // +0x10
    uint32_t mState;        // +0x14
    uint32_t mMask;         // +0x18

    void Init(const uint8_t* data, uint32_t size);  // 0x007c7770
    bool Seed(const char* name);                    // 0x007c77e0
    int  Mode();                                    // 0x007c78c0
    int  Query(int which);                          // 0x007c78e0
    int  Read(void* dst, int n);                    // 0x007c7910
    bool Reset();                                   // 0x007c7980
};

// @ 0x007c77e0
bool cRandom::Seed(const char* name)
{
    if (mData != 0) {
        uint32_t v = mSize;
        int n = 0;
        if (v & 0xffff0000u) { n = 0x10; v >>= 0x10; }
        if (v & 0xff00u)     { n += 8;   v >>= 8; }
        if (v & 0xf0u)       { n += 4;   v >>= 4; }
        if (v & 0xcu)        { n += 2;   v >>= 2; }
        if (v & 2u)          { n += 1; }
        uint32_t p = g_BitLengthTable[n];
        int m = ++n;
        mPoly  = p;
        mState = p;
        mMask  = (1u << m) - 1;
        uint32_t h = FNVHash(name, 0x811c9dc5u, 0);
        mState = mMask & h;
        mPos   = 0;
        return true;
    }
    return false;
}

// @ 0x007c78c0
int cRandom::Mode()
{
    return mData ? 0 : -2;
}

// @ 0x007c78e0
int cRandom::Query(int which)
{
    switch (which) {
    case 0: return (int)mPos;
    case 1: return 0;
    case 2: return (int)(mSize - mPos);
    }
    return -1;
}

// @ 0x007c7910
int cRandom::Read(void* dst, int n)
{
    if (mData != 0 && dst != 0 && (mPos + 1) < mSize) {
        uint8_t* out = (uint8_t*)dst;
        while (n--) {
            uint32_t v = mState;
            do {
                if (v & 1)
                    v = (v >> 1) ^ mPoly;
                else
                    v >>= 1;
            } while (v >= mSize);
            mState = v;
            *out = mData[v];
            mPos++;
            out++;
        }
        return (int)(out - (uint8_t*)dst);
    }
    return -1;
}

// @ 0x007c7980
bool cRandom::Reset()
{
    if (mData != 0) {
        uint32_t v = mSize;
        int n = 0;
        if (v & 0xffff0000u) { n = 0x10; v >>= 0x10; }
        if (v & 0xff00u)     { n += 8;   v >>= 8; }
        if (v & 0xf0u)       { n += 4;   v >>= 4; }
        if (v & 0xcu)        { n += 2;   v >>= 2; }
        if (v & 2u)          { n += 1; }
        uint32_t p = g_BitLengthTable[n];
        int m = ++n;
        mPoly  = p;
        mState = p;
        mMask  = (1u << m) - 1;
    }
    return true;
}

// @ 0x007c7c40
int cConfigManager::GetOption(uint32_t id)
{
    cOption* p = mState.mOptionsBegin;
    cOption* e = mState.mOptionsEnd;
    while (p != e) {
        if (p->mID == id)
            return (int)p->mCurrent;
        p++;
    }
    return 0;
}

// @ 0x007c7c70
int cConfigManager::GetOptionDefault(uint32_t id)
{
    cOption* p = mState.mOptionsBegin;
    cOption* e = mState.mOptionsEnd;
    while (p != e) {
        if (p->mID == id)
            return (int)p->mDefault;
        p++;
    }
    return 0;
}

// @ 0x007c7ca0
int cConfigManager::GetNumScreenResolutions()
{
    cOption* p = mState.mOptionsBegin;
    cOption* e = mState.mOptionsEnd;
    while (p != e) {
        if (p->mID == 0x46170a1u)
            return (int)(p->mResEnd - p->mResBegin) >> 2;
        p++;
    }
    return 0;
}

// @ 0x007c7cd0
bool cConfigManager::GetScreenResolutionInfo(int i, uint32_t* p1, uint32_t* p2, uint32_t* p3)
{
    cOption* p = mState.mOptionsBegin;
    cOption* e = mState.mOptionsEnd;
    while (p != e) {
        if (p->mID == 0x46170a1u)
            goto found;
        p++;
    }
    return false;
found:
    if (i < 0)
        return false;
    if (i >= (int)((p->mResEnd - p->mResBegin) >> 2))
        return false;
    uint32_t prop = ((uint32_t*)p->mResBegin)[i];
    *p1 = 0;
    *p2 = 0;
    *p3 = 0;
    TryGetUIntProperty((void*)prop, 0x38d0a06u, p1);
    TryGetUIntProperty((void*)prop, 0x38d0a07u, p2);
    TryGetUIntProperty((void*)prop, 0xd77e98u, p3);
    return true;
}

struct cOptionCheat {
    const char* Description(int which);     // 0x007c7aa0
};

// @ 0x007c7aa0
const char* cOptionCheat::Description(int which)
{
    const char* s = "no arguments       lists all options\n[option]           list value of given option\n[option value]     sets option\n-reset             reset all options to default\n-save              save current options\n";
    if (which == 0)
        s = "lists options or sets an option";
    return s;
}

// @ 0x007c7ac0
bool cConfigScriptState::SetOptionDefault(uint32_t id, uint32_t value)
{
    cOption* begin = mOptionsBegin;
    for (unsigned i = 0; i < (unsigned)((int)((char*)mOptionsEnd - (char*)begin) / 0xac); i++) {
        if (begin[i].mID == id) {
            begin[i].mDefault = value;
            return true;
        }
    }
    return false;
}

struct cOptionBlockCommand {
    char pad0[0x30];
    cConfigScriptState* mState;     // +0x30
    void OnEndBlock(int);           // 0x007c7e70
    void OnRegister(void*, void*);  // 0x007c8270
};

struct cVendorCommand {
    char pad0[0x30];
    cConfigScriptState* mState;     // +0x30
    void OnRegister(void*, void*);  // 0x007c84a0
};

extern cRandom g_random;    // 0x0153cf9c

// @ 0x007c7870
cRandom* __stdcall GetRandom(const char* name, int, int)
{
    g_random.Init(g_randomData, 0x6d5);
    g_random.Seed(name);
    return &g_random;
}

// @ 0x007c7a10
bool cConfigManager::SavePreferences()
{
    void* prefs = g_sAppPreferences;
    if (prefs != 0)
        return SaveResource(prefs, GetSaveArea(g_saveAreaName), 0);
    return false;
}

// @ 0x007c7be0
bool cConfigManager::Shutdown()
{
    void* cm = CheatManager();
    ((VFn1)VSLOT(cm, 0x1c))(cm, (void*)"option");
    if (mFileParser != 0) {
        ((VFn0)VSLOT(mFileParser, 0xc))(mFileParser);
        RC* old = mFileParser;
        if (old != 0) {
            mFileParser = 0;
            ((VFn0)VSLOT(old, 4))(old);
        }
    } else {
        ((VFn0)VSLOT(mScriptParser, 0xc))(mScriptParser);
    }
    RC* p = (RC*)mScriptParser;
    if (p != 0) {
        mScriptParser = 0;
        ((VFn0)VSLOT(p, 4))(p);
    }
    return true;
}

// @ 0x007c7b30
void cConfigScriptState::DumpAll(void* args)
{
    __declspec(align(64)) char buf[92];
    for (int i = 0; i < 0x21; i++) {
        FormatDouble((double)mConfigNumbers[i], buf, 0x1f, 6, 0);
        void* s = FormatString(i, "cpuSpeed", buf);
        ((VFn1)VSLOT(args, 0x6c))(args, s);
    }
    String16* p = mConfigStrings;
    for (int off = 0, j = 0; off < 0xe0; off += 0x10, p++, j++) {
        void* s = FormatString(j, "userName", p->mpBegin);
        ((VFn1)VSLOT(args, 0x6c))(args, s);
    }
}

// @ 0x007c7ec0
void SetResolutionCommand_Execute(void* self, void* args)
{
    int id = ((VFnI1)VSLOT((void*)*(uint32_t*)((char*)self + 4), 0x9c))(
        (void*)*(uint32_t*)((char*)self + 4), *(void**)args);
    cConfigScriptState* st = *(cConfigScriptState**)((char*)self + 0xc);
    cOption* op = st->mOptionsBegin;
    cOption* end = st->mOptionsEnd;
    while (op != end) {
        if (op->mID == 0x46170a1u)
            goto found;
        op++;
    }
    return;
found:
    {
        float ratio;
        uint32_t desktopW;
        uint32_t desktopH;
        uint8_t dmod[8];
        uint32_t best = 0;
        void* disp = DesktopDisplayMode(dmod);
        uint32_t* dm = (uint32_t*)disp;
        desktopW = dm[0];
        desktopH = dm[1];
        ratio = (float)desktopW / (float)desktopH;
        int count = (int)((op->mResEnd - op->mResBegin) >> 2);
        float bestScore = 3.4028234663852886e38f;
        int bestIdx = -1;
        for (int i = 0; i < count; i++) {
            uint32_t prop = ((uint32_t*)op->mResBegin)[i];
            uint32_t w = 0, h = 0, monitor = 0;
            if (prop != 0) {
                ((VFn1)VSLOT((void*)prop, 0x24))((void*)prop, &w);
                ((VFn1)VSLOT((void*)prop, 0x24))((void*)prop, &h);
                ((VFn1)VSLOT((void*)prop, 0x24))((void*)prop, &monitor);
            }
            float score = (float)((int)(desktopH - w) < 0 ? w - desktopH : desktopH - w) * 300000.0f
                        + (float)(int)monitor;
            if (score < bestScore) {
                bestScore = score;
                bestIdx = i;
            }
        }
        op->mDefault = bestIdx;
    }
}

// @ 0x007c80c0
struct AutoRefVec {
    void** mpBegin;      // +0x00
    void** mpEnd;        // +0x04
    void** mpCap;        // +0x08
    char   pad0C[4];
    void*  mInline[4];   // +0x10
    void Destroy();
};

// @ 0x007c80c0
void AutoRefVec::Destroy()
{
    void** it = mpBegin;
    void** e = mpEnd;
    for (; it < e; it++) {
        if (*it != 0)
            ((VFn0)VSLOT(*it, 4))(*it);
    }
    void* b = mpBegin;
    if (b != 0 && b != mInline[0])
        EA_Free(b);
}

// @ 0x007c8160
void LowerBoundPair(uint32_t* first, uint32_t* last, uint32_t* key)
{
    int n = (int)((char*)last - (char*)first) >> 4;
    while (n > 0) {
        int half = n >> 1;
        uint32_t* mid = (uint32_t*)((char*)first + (half << 4));
        if (mid[1] < key[1] || (mid[1] == key[1] && mid[0] < key[0])) {
            first = (uint32_t*)((char*)mid + 0x10);
            n = n - 1 - half;
        } else {
            n = half;
        }
    }
}

// @ 0x007c7e70
void cOptionBlockCommand::OnEndBlock(int)
{
    *(uint32_t*)((char*)mState + 0x58) = 0xffffffffu;
}

struct cCmdArgs {
    char pad0[4];
    void* mArg;                     // +0x04
    char pad8[4];
    cConfigScriptState* mState;     // +0x0c
    void Do(int);                   // 0x007c7eb0
};

// @ 0x007c7eb0
void cCmdArgs::Do(int)
{
    mState->DumpAll(mArg);
}

// @ 0x007c7d70
AutoRefCount** CopyConstructAutoRef(AutoRefCount** out, AutoRefCount* first, AutoRefCount* last, AutoRefCount* dest)
{
    *out = dest;
    for (; first != last; first++) {
        AutoRefCount* d = *out;
        if (d != 0) {
            d->m0  = first->m0;
            d->m4  = first->m4;
            d->mRC = first->mRC;
            if (d->mRC != 0)
                ((VFn0)VSLOT(d->mRC, 0))(d->mRC);
        }
        *out = *out + 1;
    }
    return out;
}

// @ 0x007c7e10
AutoRefCount* CopyAutoRef(AutoRefCount* first, AutoRefCount* last, AutoRefCount* dest)
{
    while (first != last) {
        dest->m0 = first->m0;
        dest->m4 = first->m4;
        RC* s = first->mRC;
        RC* d = dest->mRC;
        if (s != d) {
            if (s != 0)
                ((VFn0)VSLOT(s, 0))(s);
            dest->mRC = s;
            if (d != 0)
                ((VFn0)VSLOT(d, 4))(d);
        }
        first++;
        dest++;
    }
    return dest;
}

// ---------------------------------------------------------------- ArgScript commands
struct CmdBase  { CmdBase();  char pad[0x0c]; };   // 0x10 with vptr
struct BlockBase { BlockBase(); char pad[0x30]; }; // 0x34 with vptr

struct CmdOptionSetting       : CmdBase { virtual void Execute(); };
struct CmdOptionBoolProperty  : CmdBase { virtual void Execute(); };
struct CmdOptionIntProperty   : CmdBase { virtual void Execute(); };
struct CmdOptionFloatProperty : CmdBase { virtual void Execute(); };
struct CmdOptionKeyProperty   : CmdBase { virtual void Execute(); };
struct CmdOptionProperties    : CmdBase { virtual void Execute(); };
struct CmdCard                : CmdBase { virtual void Execute(); };
struct CmdSetVariables        : CmdBase { virtual void Execute(); };
struct CmdSetOption           : CmdBase { virtual void Execute(); };
struct CmdAlert               : CmdBase { virtual void Execute(); };
struct CmdSetResolution       : CmdBase { virtual void Execute(); };
struct CmdBoolProperty        : CmdBase { virtual void Execute(); };
struct CmdIntProperty         : CmdBase { virtual void Execute(); };
struct CmdFloatProperty       : CmdBase { virtual void Execute(); };
struct CmdKeyProperty         : CmdBase { virtual void Execute(); };
struct CmdOptionBlock         : BlockBase { virtual void Execute(); };
struct CmdVendor              : BlockBase { virtual void Execute(); };

void __cdecl FUN_0083c780(void* a, void* b);   // 0x0083c780

// @ 0x007c8270
void cOptionBlockCommand::OnRegister(void* a, void* b)
{
    mState = (cConfigScriptState*)b;
    FUN_0083c780(a, b);
    void* c;
    c = new ("ArgScript/OptionSetting", 0, 0, 0, 0) CmdOptionSetting();
    ((VFn2P)VSLOT(this, 0x18))(this, g_CmdKey_setting, c);
    c = new ("ArgScript/OptionBoolProperty", 0, 0, 0, 0) CmdOptionBoolProperty();
    ((VFn2P)VSLOT(this, 0x18))(this, g_CmdKey_boolProp, c);
    c = new ("ArgScript/OptionIntProperty", 0, 0, 0, 0) CmdOptionIntProperty();
    ((VFn2P)VSLOT(this, 0x18))(this, g_CmdKey_intProp, c);
    c = new ("ArgScript/OptionFloatProperty", 0, 0, 0, 0) CmdOptionFloatProperty();
    ((VFn2P)VSLOT(this, 0x18))(this, g_CmdKey_floatProp, c);
    c = new ("ArgScript/OptionKeyProperty", 0, 0, 0, 0) CmdOptionKeyProperty();
    ((VFn2P)VSLOT(this, 0x18))(this, g_CmdKey_keyProp, c);
    c = new ("ArgScript/OptionProperties", 0, 0, 0, 0) CmdOptionProperties();
    ((VFn2P)VSLOT(this, 0x18))(this, g_CmdKey_props, c);
}

// @ 0x007c84a0
void cVendorCommand::OnRegister(void* a, void* b)
{
    mState = (cConfigScriptState*)b;
    FUN_0083c780(a, b);
    void* c = new ("ArgScript/Card", 0, 0, 0, 0) CmdCard();
    ((VFn2P)VSLOT(this, 0x18))(this, g_CmdKey_card, c);
}

// @ 0x007c8530
void __cdecl RegisterConfigScriptCommands(void* parser)
{
    void* c;
    c = new ("ArgScript/OptionBlock", 0, 0, 0, 0) CmdOptionBlock();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_option, c);
    c = new ("ArgScript/Vendor", 0, 0, 0, 0) CmdVendor();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_vendor, c);
    c = new ("ArgScript/SetVariables", 0, 0, 0, 0) CmdSetVariables();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_setVariables, c);
    c = new ("ArgScript/SetOption", 0, 0, 0, 0) CmdSetOption();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_setOption, c);
    c = new ("ArgScript/Alert", 0, 0, 0, 0) CmdAlert();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_alert, c);
    c = new ("ArgScript/SetResolution", 0, 0, 0, 0) CmdSetResolution();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_setResolution, c);
    c = new ("ArgScript/BoolProperty", 0, 0, 0, 0) CmdBoolProperty();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_boolProp2, c);
    c = new ("ArgScript/IntProperty", 0, 0, 0, 0) CmdIntProperty();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_intProp2, c);
    c = new ("ArgScript/FloatProperty", 0, 0, 0, 0) CmdFloatProperty();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_floatProp2, c);
    c = new ("ArgScript/KeyProperty", 0, 0, 0, 0) CmdKeyProperty();
    ((VFn2P)VSLOT(parser, 0x14))(parser, g_CmdKey_keyProp2, c);
}

// @ 0x007c8880
void cConfigManager::SetScriptPath(const void* a, const void* b)
{
    if (mScriptParser == 0) {
        void* p = CreateParser();
        if (p != mScriptParser) {
            if (p != 0)
                ((VFn0)VSLOT(p, 0))(p);
            void* old = mScriptParser;
            mScriptParser = p;
            if (old != 0)
                ((VFn0)VSLOT(old, 4))(old);
        }
        ((VFn0)VSLOT(mScriptParser, 8))(mScriptParser);
        ((VFn2)VSLOT(mScriptParser, 0x24))(mScriptParser, 0, 1);
        ((VFn1)VSLOT(mScriptParser, 0x10))(mScriptParser, &mState);
        void* cm = CheatManager();
        void* c = ((VFnR)VSLOT(cm, 0x38))(cm);
        void* r = ((VFnR)VSLOT(c, 0xc4))(c);
        ((VFn1)VSLOT(mScriptParser, 0xbc))(mScriptParser, r);
        RegisterConfigScriptCommands(mScriptParser);
    }
    *(void**)((char*)this + 0x14) = (void*)a;
    *(void**)((char*)this + 0x1c) = (void*)b;
}
