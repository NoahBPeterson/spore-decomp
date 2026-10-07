// Slice s00b318d0: SP::cGameTimeManager (pause gates, time flow, base stopwatch), the "settime" cheat
// command, a token translator and a few helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE.
#include "types.h"
#include <xmmintrin.h>
#include <intrin.h>
#include <new>
typedef unsigned int u32;

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64*);
extern "C" unsigned long __cdecl wcstoul(const wchar_t*, wchar_t**, int);
extern "C" int __cdecl wcsncmp(const wchar_t*, const wchar_t*, unsigned);
extern "C" wchar_t* __cdecl wcschr(const wchar_t*, wchar_t);

#define VT(p) (*(void***)(p))
#define VFN(p, off, T) ((T)(VT(p)[(off) / 4]))

void  __cdecl operator_delete__(void* p);                    // 00f47380
void* __cdecl operator_new_ea(unsigned n, const char* tag, int a, unsigned b, const char* c, int d); // 00f473a0

// ---- EA::Stopwatch (global instance sBaseTimer @ 0x0167e908) -----------------------------------
struct Stopwatch {
    unsigned __int64 mnStartTime;          // 0167e908
    unsigned __int64 mnTotalElapsedTime;   // 0167e910
    int   mnUnits;                         // 0167e918
    float mfCoeff;                         // 0167e91c
    __int64 GetElapsedTimeFloat();         // 0093a3a0
    void SetUnits(int units);              // 0093a1a0
    void Stop();                           // 0093a2e0
    __forceinline void StartIfStopped()
    {
        if (mnStartTime == 0) {
            if (mnUnits == 1) {
                unsigned __int64 t = __rdtsc();
                ((u32*)&mnStartTime)[1] = (u32)(t >> 32);
                ((u32*)&mnStartTime)[0] = (u32)t;
            } else {
                __int64 t;
                QueryPerformanceCounter(&t);
                mnStartTime = t;
            }
        }
    }
    __forceinline void RestartIfRunning()
    {
        if (mnStartTime == 0) {
            mnStartTime = 0;
        } else if (mnUnits == 1) {
            mnStartTime = __rdtsc();
        } else {
            __int64 t;
            QueryPerformanceCounter(&t);
            mnStartTime = t;
        }
        mnTotalElapsedTime = 0;
    }
    __forceinline void Restart()
    {
        if (mnUnits == 1) {
            unsigned __int64 t = __rdtsc();
            ((u32*)&mnStartTime)[1] = (u32)(t >> 32);
            ((u32*)&mnStartTime)[0] = (u32)t;
        } else {
            __int64 t;
            QueryPerformanceCounter(&t);
            mnStartTime = t;
        }
        mnTotalElapsedTime = 0;
    }
};
extern Stopwatch sBaseTimer;                                  // 0167e908

// ---- externs ---------------------------------------------------------------------------------
struct IStreamObj { virtual void v0(); };
extern "C" int __cdecl WriteUint32(void* stream, u32* p, unsigned n, int endian);   // 0093aa70

struct cVarListSerializer {
    char mData[0xa10];
    cVarListSerializer(void* obj, const void* desc, unsigned flags);   // 00692f90
    void Serialize(void* stream);                                      // 00692900
};

struct cGonzagoSubsystemBase { virtual ~cGonzagoSubsystemBase(); virtual void g1(); };
struct cRefCountBase { virtual void r0(); virtual void r1(); int mnRefCount; };
struct cGonzagoSubsystem : cGonzagoSubsystemBase, cRefCountBase {
    int mPre, mPost, mCurTrans, mPhase;
    cGonzagoSubsystem();                    // 00b5b960
    ~cGonzagoSubsystem();                   // 00b5b9a0
};

struct MessageServer { virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
                       virtual void Post(unsigned msgId, int data, int flag); };
MessageServer* __cdecl GetMessageServer();                    // 00883860
struct AppSystemObj;
AppSystemObj* __cdecl SP_AppSystem();                         // 0067dd00

// ---- eastl-like containers used by cGameTimeManager -------------------------------------------
struct MapNode { MapNode* right; MapNode* left; MapNode* parent; char color; unsigned key; unsigned val; };
struct MapIter { MapNode* mpNode; MapIter(const MapIter& o) : mpNode(o.mpNode) {} };
struct PauseMap {
    int       mpad4c;
    MapNode*  mRight;
    MapNode*  mLeft;
    MapNode*  mParent;
    union { char mColor; int mColorDw; };
    int       mnSize;
    int       mpad64;
    PauseMap() : mLeft(0), mParent(0), mColorDw(0) { mRight = (MapNode*)&mRight; mLeft = (MapNode*)&mRight; mParent = 0; mColor = 0; mnSize = 0; }
    ~PauseMap() { DoNuke(mParent); }
    MapIter   find(const unsigned& key);                // 00e5c780
    unsigned& operator[](const unsigned& key);          // 00643a40
    void      DoNuke(MapNode* n);                       // 009a9600
    MapNode*  anchor() { return (MapNode*)&mRight; }
};

struct tPauseGate {
    int      count;
    unsigned bits;
};
struct PauseGateVec {
    tPauseGate* mpBegin; tPauseGate* mpEnd; tPauseGate* mpCap;
    PauseGateVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    ~PauseGateVec() { if (mpBegin && ((int*)mpBegin)[-1]) operator_delete__(mpBegin); }
    unsigned size() const { return mpEnd - mpBegin; }
    tPauseGate& operator[](unsigned n) { return mpBegin[n]; }
    void Realloc(tPauseGate* at, const unsigned* v);     // 00b534c0
    void push_back_zero()
    {
        if (mpEnd < mpCap) {
            tPauseGate* p = mpEnd++;
            if (p) p->bits = 0;
        } else {
            unsigned z = 0;
            Realloc(mpEnd, &z);
        }
    }
};

// ---- SP::cGameTimeManager --------------------------------------------------------------------
struct cGameTimeManager : cGonzagoSubsystem {
    float             mTimeFlowRates[4];                    // +0x1c
    unsigned __int64  mBaseTimeElapsed;                     // +0x30
    unsigned __int64  mTimeAtStartOfFrame;                  // +0x38
    float             mTimeFlowRate;                        // +0x40
    int               mTimeFlowSetting;                     // +0x44
    unsigned          mCachedPauseState;                    // +0x48
    PauseMap          mPauseGateIndexMap;                   // +0x4c
    PauseGateVec      mPauseGates;                          // +0x68

    cGameTimeManager();
    virtual ~cGameTimeManager() {}
    void   UpdateTimeAtStartOfFrame();
    void   Serialize(void* stream);
    unsigned CeilScaledTime(unsigned v);
    void   UpdatePauseState();
    int    GetPauseGateCount(unsigned id);
    void   ClearPauseGates();
    void   RegisterPauseGate(unsigned id, unsigned bits, const char* name);
    int    IncPauseGate(unsigned id);
    int    DecPauseGate(unsigned id);
    bool   TogglePauseGate(unsigned id);
    void   SetTimeFlowRate(float rate);
    void   RegisterDefaultPauseGates();
    void   SetTimeFlowSetting(int idx);
};

// @ 0x00b31a90
void cGameTimeManager::UpdateTimeAtStartOfFrame()
{
    float f = (float)sBaseTimer.GetElapsedTimeFloat() * sBaseTimer.mfCoeff * mTimeFlowRate;
    __int64 d = (__int64)f;
    mTimeAtStartOfFrame = mBaseTimeElapsed + d;
}

// @ 0x00b31ae0
void cGameTimeManager::Serialize(void* stream)
{
    float f = (float)sBaseTimer.GetElapsedTimeFloat() * sBaseTimer.mfCoeff * mTimeFlowRate;
    mBaseTimeElapsed += (__int64)f;
    sBaseTimer.RestartIfRunning();
    cVarListSerializer ser(this, (const void*)0x01569130, 0x01a80d26);
    ser.Serialize(stream);
}

#pragma warning(disable:4035)
__forceinline int CeilToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        add      ecx, 1
        ucomiss  xmm1, xmm0
        cmovb    eax, ecx
    }
}

// @ 0x00b31c60
unsigned cGameTimeManager::CeilScaledTime(unsigned v)
{
    unsigned lim = 100;
    if (mCachedPauseState & 1)
        return 0;
    const unsigned* p = &v;
    if (v >= lim)
        p = &lim;
    v = *p;
    float f = (float)v * mTimeFlowRate;
    return CeilToInt(f);
}

// @ 0x00b31ea0
cGameTimeManager::cGameTimeManager()
    : mBaseTimeElapsed(0), mTimeAtStartOfFrame(0), mTimeFlowRate(1.0f), mTimeFlowSetting(0), mCachedPauseState(0)
{
    mTimeFlowRates[0] = 1.0f;
    mTimeFlowRates[1] = 2.0f;
    mTimeFlowRates[2] = 4.0f;
    mTimeFlowRates[3] = 8.0f;
}

// @ 0x00b31fa0
void cGameTimeManager::UpdatePauseState()
{
    unsigned old = mCachedPauseState;
    mCachedPauseState = 0;
    tPauseGate* g = mPauseGates.mpBegin;
    tPauseGate* e = mPauseGates.mpEnd;
    for (; g != e; ++g) {
        if (g->count > 0) {
            mCachedPauseState = g->bits;
            break;
        }
    }
    bool nb0 = (mCachedPauseState & 1) != 0;
    if (nb0 != ((old & 1) != 0)) {
        if (nb0)
            sBaseTimer.Stop();
        else
            sBaseTimer.StartIfStopped();
        MessageServer* srv = GetMessageServer();
        if (srv)
            srv->Post(0x03867294, nb0 ? 1 : 0, 0);
    }
    bool nb2 = ((mCachedPauseState >> 2) & 1) != 0;
    if (nb2 != (((old >> 2) & 1) != 0)) {
        MessageServer* srv = GetMessageServer();
        if (srv)
            srv->Post(0x0546bbb8, nb2 ? 1 : 0, 0);
    }
    bool nb1 = ((mCachedPauseState >> 1) & 1) != 0;
    if (nb1 != (((old >> 1) & 1) != 0)) {
        AppSystemObj* app = SP_AppSystem();
        if (nb1)
            VFN(app, 0x2c, void(__thiscall*)(void*))(app);
        else
            VFN(app, 0x30, void(__thiscall*)(void*))(app);
    }
}

// @ 0x00b320d0
int cGameTimeManager::GetPauseGateCount(unsigned id)
{
    MapNode* n = mPauseGateIndexMap.find(id).mpNode;
    if (n != mPauseGateIndexMap.anchor())
        return mPauseGates.mpBegin[n->val].count;
    return 0;
}

// @ 0x00b32110
void cGameTimeManager::ClearPauseGates()
{
    tPauseGate* g = mPauseGates.mpBegin;
    tPauseGate* e = mPauseGates.mpEnd;
    for (; g != e; ++g)
        g->count = 0;
    UpdatePauseState();
}

// @ 0x00b32140  (scalar deleting destructor, generated from the inline ~cGameTimeManager)
void ForceGTMDtor(cGameTimeManager* p) { delete p; }

// @ 0x00b32190
void cGameTimeManager::RegisterPauseGate(unsigned id, unsigned bits, const char* name)
{
    (void)name;
    if (mPauseGateIndexMap.find(id).mpNode == mPauseGateIndexMap.anchor()) {
        unsigned idx = mPauseGates.size();
        mPauseGates.push_back_zero();
        tPauseGate* g = mPauseGates.mpEnd - 1;
        g->count = 0;
        g->bits = bits;
        mPauseGateIndexMap[id] = idx;
    }
}

// @ 0x00b32220
int cGameTimeManager::IncPauseGate(unsigned id)
{
    tPauseGate* g = &mPauseGates[mPauseGateIndexMap[id]];
    g->count++;
    UpdatePauseState();
    return g->count;
}

// @ 0x00b32250
int cGameTimeManager::DecPauseGate(unsigned id)
{
    tPauseGate* g = &mPauseGates[mPauseGateIndexMap[id]];
    g->count--;
    UpdatePauseState();
    return g->count;
}

// @ 0x00b32280
bool cGameTimeManager::TogglePauseGate(unsigned id)
{
    tPauseGate* g = &mPauseGates[mPauseGateIndexMap[id]];
    if (g->count == 0 || g->count == 1) {
        g->count = (g->count == 0);
        UpdatePauseState();
    }
    return g->count != 0;
}

// @ 0x00b322c0
void cGameTimeManager::SetTimeFlowRate(float rate)
{
    bool wasPaused = (mCachedPauseState & 1) != 0;
    if (wasPaused)
        TogglePauseGate(0x04bf38a8);
    float f = (float)sBaseTimer.GetElapsedTimeFloat() * sBaseTimer.mfCoeff * mTimeFlowRate;
    mBaseTimeElapsed += (__int64)f;
    sBaseTimer.Restart();
    mTimeFlowRate = rate;
    AppSystemObj* app = SP_AppSystem();
    VFN(app, 0x38, void(__thiscall*)(void*, float))(app, rate);
    if (wasPaused)
        TogglePauseGate(0x04bf38a8);
}

// @ 0x00b323f0
void cGameTimeManager::RegisterDefaultPauseGates()
{
    RegisterPauseGate(0x04bf38a8, 7, "user toggle");
    RegisterPauseGate(0x04bf38a7, 3, "gameplay");
    RegisterPauseGate(0x04bf38a4, 3, "ui toggle");
    RegisterPauseGate(0x04bf38a9, 3, "modal dialog");
}

// @ 0x00b32450
void cGameTimeManager::SetTimeFlowSetting(int idx)
{
    mTimeFlowSetting = idx;
    SetTimeFlowRate(mTimeFlowRates[idx]);
}

// ---- stream writer ---------------------------------------------------------------------------
struct IOutSub { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4();
                 virtual void a5(); virtual void* GetStream(); };
struct IOutObj { virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4();
                 virtual void b5(); virtual void b6(); virtual void b7(); virtual IOutSub* GetSub(); };

// @ 0x00b318d0
IOutObj* __cdecl WriteNineUint32(IOutObj* s, u32* d)
{
    u32 v;
    v = d[0]; WriteUint32(s->GetSub()->GetStream(), &v, 1, 0);
    v = d[1]; WriteUint32(s->GetSub()->GetStream(), &v, 1, 0);
    v = d[2]; WriteUint32(s->GetSub()->GetStream(), &v, 1, 0);
    v = d[3]; WriteUint32(s->GetSub()->GetStream(), &v, 1, 0);
    v = d[4]; WriteUint32(s->GetSub()->GetStream(), &v, 1, 0);
    v = d[5]; WriteUint32(s->GetSub()->GetStream(), &v, 1, 0);
    v = d[6]; WriteUint32(s->GetSub()->GetStream(), &v, 1, 0);
    v = d[7]; WriteUint32(s->GetSub()->GetStream(), &v, 1, 0);
    v = d[8]; WriteUint32(s->GetSub()->GetStream(), &v, 1, 0);
    return s;
}

// ---- "settime" cheat command -----------------------------------------------------------------
struct cArguments {
    const char** MainArguments(int* outCount, int a, int b);     // 00838020
    const char** OptionArguments_00838330(const char* name, int n);       // 00838330 cArguments::OptionArguments(const char*,int); address in the name so the checker does not pick the 0x838130 overload
};
struct cCommandBase {
    void* mpOwner;
    int   m8, mc;
    cCommandBase();                                              // 0083c800
    virtual void c0();
    virtual void ParseLine(cArguments* args);
};
struct cSetTimeCommand : cCommandBase {
    virtual void c0();
    virtual void ParseLine(cArguments* args);
};
struct CheatManager { virtual void k0(); virtual void k1(); virtual void k2(); virtual void k3(); virtual void k4();
                      virtual void k5(); virtual void AddCommand(const char* name, cCommandBase* cmd, int flag); };
CheatManager* __cdecl SP_CheatManager();                         // 0067de20

struct cTimeOfDay {
    char  pad[0x24];
    float mfDayLength;
    void SetTime(float f, float* pos);                           // 00bc2f00
    void SetSpeed(float f);                                      // 00bc28c0
};
cTimeOfDay* __cdecl TimeOfDay_Instance();                        // 00bc30b0
void* __cdecl SP_NounManager();                                  // 00b3d300
struct GameNounManager { void* GetAvatar(); };                  // 00b1fdb0
void* __cdecl SP_App();                                          // 0067dd10
void* __cdecl GetActivePlanet();                                 // 01021260
struct Matrix3 { float m[9]; void Assign(const void* src); };    // 0041cb40
extern float g_167e8b0, g_167e8b4, g_167e8b8;
extern char  g_167e8e0[];
struct Xform {
    unsigned short flags0, flags1;
    float pos[3];
    float scale;
    Matrix3 rot;
    Xform()
    {
        pos[0] = g_167e8b0; pos[1] = g_167e8b4; flags0 = 0; pos[2] = g_167e8b8; flags1 = 0; scale = 1.0f;
        rot.Assign(g_167e8e0);
    }
};
struct Obj7c40f0 { void Apply(); };                             // 007c40f0

void* __cdecl operator new(unsigned n, const char* a, int b, unsigned c, const char* d, int e);  // 00f473a0

// @ 0x00b31bc0
void __cdecl RegisterSetTimeCommand()
{
    cSetTimeCommand* cmd = new ("Debug", 0, 0, 0, 0) cSetTimeCommand;
    SP_CheatManager()->AddCommand("settime", cmd, 0);
    sBaseTimer.SetUnits(4);
    sBaseTimer.StartIfStopped();
}

// @ 0x00b31cc0
void cSetTimeCommand::ParseLine(cArguments* args)
{
    int n;
    const char** main = args->MainArguments(&n, 0, 1);
    TimeOfDay_Instance();
    if (n > 0) {
        const char* str = *main;
        float tv[3];
        float* pt = VFN(mpOwner, 0xa4, float*(__thiscall*)(void*, float*, const char*))(mpOwner, tv, str);
        float t = pt[1] * 0.00069444446f + pt[0] * 0.041666668f;
        if (t <= 0.0f) t = 0.0f;
        if (1.0f <= t) t = 1.0f;
        float pos[3];
        void* avatar = ((GameNounManager*)SP_NounManager())->GetAvatar();
        if (avatar) {
            void* sub = (char*)avatar + 0xc0;
            float* p = VFN(sub, 0x2c, float*(__thiscall*)(void*))(sub);
            pos[0] = p[0]; pos[1] = p[1]; pos[2] = p[2];
        } else {
            Xform xf;
            void* app = SP_App();
            void* r = VFN(app, 0x58, void*(__thiscall*)(void*, Xform*))(app, &xf);
            ((Obj7c40f0*)r)->Apply();
            pos[0] = xf.pos[0]; pos[1] = xf.pos[1]; pos[2] = xf.pos[2];
        }
        if (!GetActivePlanet())
            return;
        float f = t * TimeOfDay_Instance()->mfDayLength;
        TimeOfDay_Instance()->SetTime(f, pos);
    }
    const char** opt = args->OptionArguments_00838330("speed", 1);
    if (opt) {
        float v = VFN(mpOwner, 0x98, float(__thiscall*)(void*, const char*))(mpOwner, *opt);
        const float lo = 1.52587890625e-05f;
        const float* pf = &v;
        if (!(v > lo))
            pf = &lo;
        float s = *pf;
        TimeOfDay_Instance()->SetSpeed(s);
    }
}

// ---- token translator ------------------------------------------------------------------------
struct IRef { virtual void r0(); virtual void Release(); };
struct cTranslatorBase {
    int mBase4;
    cTranslatorBase();
    ~cTranslatorBase() throw();                                  // 005725a0
    virtual void t0();
};
struct WStr {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCap;
    WStr(const wchar_t* s) : mpBegin(0), mpEnd(0), mpCap(0) { RangeInit(s); }
    ~WStr() { if (((unsigned)((char*)mpCap - (char*)mpBegin) & ~1u) > 2 && mpBegin) operator_delete__(mpBegin); }
    void RangeInit(const wchar_t* s);                            // 00579a90
    void append(const wchar_t* s);                               // 005c3d90
    void assign(const wchar_t* b, const wchar_t* e);             // 00423650
    unsigned size() const { return mpEnd - mpBegin; }
};
struct WStrEmpty {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCap;
    WStrEmpty() : mpBegin((wchar_t*)0x1667bac), mpEnd((wchar_t*)0x1667bac), mpCap((wchar_t*)0x1667bae) {}
    ~WStrEmpty() { if (((unsigned)((char*)mpCap - (char*)mpBegin) & ~1u) > 2 && mpBegin) operator_delete__(mpBegin); }
};
bool __cdecl WStrEquals(const WStrEmpty* s, const wchar_t* lit);  // 006ab760
void* __cdecl SP_StringDetokenizer();                            // 0067de50
void* __cdecl SP_PropertyManager();                              // 0067de30
bool __cdecl GetFloatProperty(void* plist, unsigned id, float* out);   // 0040cf10
bool __cdecl TryGetUIntProperty(void* plist, unsigned id, unsigned* out); // 00410370
void __cdecl SetNumberStringD(double v, wchar_t* buf, unsigned cap, int flags);  // 00881ea0
void __cdecl SetNumberStringI(__int64 v, wchar_t* buf, unsigned cap);             // 00881ae0

struct cTokenTranslator : cTranslatorBase {
    IRef* mpPropList;                                            // +8
    virtual ~cTokenTranslator();
    virtual bool Lookup(const wchar_t* tok, void* outStr);       // slot 0x10 (approx.)
    bool Translate(const wchar_t* tok, WStr* out);
};

// @ 0x00b32490  (0x00b324b0 is the compiler-generated scalar deleting destructor of this class)
cTokenTranslator::~cTokenTranslator()
{
    if (mpPropList)
        mpPropList->Release();
}
void ForceTokenTranslatorDtor(cTokenTranslator* p) { delete p; }

// @ 0x00b324f0
bool cTokenTranslator::Translate(const wchar_t* tok, WStr* out)
{
    bool result = false;
    if (wcsncmp(tok, L"^p", 2) == 0) {
        WStr s(tok);
        int idx[3];
        int count = 0;
        int pos = 1;
        while (count < 3) {
            ++pos;
            wchar_t* p = 0;
            if ((unsigned)pos < s.size()) {
                for (p = s.mpBegin + pos; p != s.mpEnd; ++p)
                    if (*p == L'^') break;
                if (p == s.mpEnd) p = 0;
            }
            if (!p) { pos = -1; }
            else pos = (int)(p - s.mpBegin);
            if (pos == -1) break;
            idx[count] = pos;
            s.mpBegin[pos] = 0;
            ++count;
        }
        if (count != 3)
            return false;
        WStrEmpty str2;
        const wchar_t* t2 = s.mpBegin + idx[0] + 1;
        if (!Lookup(t2, &str2)) {
            void* det = SP_StringDetokenizer();
            void* d2 = VFN(det, 0x10, void*(__thiscall*)(void*))(det);
            if (!VFN(d2, 0x10, bool(__thiscall*)(void*, const wchar_t*, void*))(d2, t2, &str2))
                return result;
        }
        if (WStrEquals(&str2, L"1"))
            out->append(s.mpBegin + idx[1] + 1);
        else
            out->append(s.mpBegin + idx[2] + 1);
        result = true;
        return result;
    }
    if (wcsncmp(tok, L"prop_file:1", 10) == 0) {
        const wchar_t* bang = wcschr(tok + 10, L'!');
        if (bang) {
            unsigned a = wcstoul(tok + 10, 0, 16);
            unsigned b = wcstoul(bang + 1, 0, 16);
            void* pm = SP_PropertyManager();
            IRef** ref = &mpPropList;
            if (*ref) {
                IRef* old = *ref;
                *ref = 0;
                old->Release();
            }
            result = VFN(pm, 0x2c, bool(__thiscall*)(void*, unsigned, unsigned, IRef**))(pm, b, a, ref);
        }
    }
    if (mpPropList) {
        wchar_t buf[256];
        if (wcsncmp(tok, L"tuning_float:", 13) == 0) {
            unsigned id = wcstoul(tok + 13, 0, 16);
            float fv;
            if (GetFloatProperty(mpPropList, id, &fv)) {
                SetNumberStringD((double)fv, buf, 0x100, 0);
                out->append(buf);
                result = true;
            }
        } else if (wcsncmp(tok, L"tuning_int:", 11) == 0) {
            unsigned id = wcstoul(tok + 11, 0, 16);
            unsigned iv;
            if (TryGetUIntProperty(mpPropList, id, &iv)) {
                SetNumberStringI((int)iv, buf, 0x100);
                out->append(buf);
                result = true;
            }
        }
    }
    wchar_t brk[3];
    wchar_t nl[2];
    brk[0] = 0x62; brk[1] = 0x72; brk[2] = 0;
    nl[0] = 0xa; nl[1] = 0;
    const wchar_t* a = tok;
    const wchar_t* b = brk;
    int cmp = 0;
    for (;;) {
        if (*a != *b) { cmp = (*a < *b) ? -1 : 1; break; }
        if (*a == 0) break;
        ++a; ++b;
    }
    if (cmp != 0)
        return result;
    const wchar_t* e = nl;
    while (*e) ++e;
    out->assign(nl, e);
    return true;
}

// @ 0x00b32890
int __cdecl NextStateEnum(int v)
{
    switch (v) {
    case 0x1654c00: return 0x1654c01;
    case 0x1654c01: return 0x1654c02;
    case 0x1654c02: return 0x1654c04;
    case 0x1654c04: return 0x1654c05;
    default:        return -1;
    }
}
