// slice s00f1ef90 -- UI::cScenarioPlayProgressBar planet-progress verb handlers.
//
// Retail build: VS2008-era cl 15.  The group drives the "verb tray" of the
// scenario play progress bar: a table of records (stride 0x1ac) is walked,
// each record classified by its +0x24 type tag, and the matching sub-system
// (planet model / noun avatar / trigger manager / sound) updated.  The
// object's own state field (+0x90) gates every entry point (0 idle, 2
// loading, 3 active).
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast

#include "types.h"
#include <math.h>

struct Vector3 { float x, y, z; };

struct HashIt { void* node; void** bucket; };

// ---------------------------------------------------------------------------
// opaque collaborators -- declarations only, every call stays external
// ---------------------------------------------------------------------------
struct cScenarioPlayProgressBar
{
    // ---- defined in this slice ----
    void  FUN_00f1ef90(int index, char flag);
    void  FUN_00f1f180();
    void  FUN_00f1f3b0();
    void  FUN_00f1f4e0(int index);
    void  FUN_00f1f600();
    float FUN_00f1aa10(int flag, void* p);

    // ---- external collaborators (never defined here) ----
    void  FUN_00f1ecf0();
    void  FUN_00f1b450();
    void  FUN_00f1e6a0();
    void  FUN_00f1e020();
    void  FUN_00f1c4b0();
    void  FUN_00f1aae0(int);
    bool  FUN_00f1c030(int, int, int);
    void  FUN_00f1ae10(void*, void*, void*);
    void  FUN_00f19ac0(void*, int);
    void  FUN_00f1de30(int);
    void  FUN_00676e90();
    void* FUN_00f26360(int);
    bool  FUN_00f278b0();
    void  FUN_00f0e6c0();
    void  FUN_00f114a0();
    void  FUN_00f347e0();
    void  FUN_00e148d0();
    void  FUN_00f40d00(int, void*);
    void  FUN_00f46410(int, int, int);
    void  FUN_00f45fd0(int, int, int);
    HashIt FUN_00594410();
    void  FUN_00a18440(void*, void*);
    void* FUN_00e5c780(void*, void*);
    void* FUN_00f3be60(int);
    int   FUN_00f3be30();
    int   FUN_00f3e8a0(int);
    bool  FUN_00f3c870(void*, void*, float, int);
};

struct cPlanetModel { void MaskContinentBits(); };
struct cScreen
{
    void setX();                                    // 0x00ad7e90
};
struct cTriggerMgr  { void PostTrigger(int, int, int, int, int); };
struct cGameNounManager
{
    void* GetAvatar();                              // 0x00b1fdb0
};
struct cRandomLCG
{
    unsigned RandomUint32Uniform(unsigned);         // 0x00a68fb0
};

struct PtrVec
{
    void* begin;
    void* end;
    void* cap;
    void  Destroy();                    // 0x00ae6970
};

struct WString
{
    void assign(const wchar_t*, const wchar_t*);   // 0x00423650
};

struct cString
{
    void  Construct();                  // 0x006b5060
    bool  Load(unsigned, unsigned, int);// 0x006b54b0
    const wchar_t* GetText();           // 0x006b55c0
    void  Destroy();                    // 0x006b5240
};

// ---------------------------------------------------------------------------
// free functions
// ---------------------------------------------------------------------------
void  FUN_00f1ad00(int);                        // 0x00f1ad00
void* FUN_00572020(void*, int);                 // 0x00572020
void* FUN_00eed8c0(void*);                      // 0x00eed8c0
void* EA_Audio_GetSystemAT();                   // 0x00a206f0
void* SP_AudioSystem();                         // 0x0067cb00
void  FUN_00657240(void*, void*, void*);        // 0x00657240
void  FUN_006572b0(void*);                      // 0x006572b0
void  FUN_00dd1c50(unsigned, void*);            // 0x00dd1c50
void  RecordEvent4(unsigned, unsigned, float, unsigned);  // 0x00435f40
void  SetSoundSymbol(unsigned, unsigned, const char*);    // 0x00572070
void* FUN_0067de40();                           // 0x0067de40
void* __stdcall FUN_00675250(unsigned, int);    // 0x00675250
void* SP_NounManager();                         // 0x00b3d300
void* SP_ModelManager();                        // 0x0067dd80
void* __stdcall SP_PlanetModel(int);            // 0x00b3d350
void* __stdcall GetTriggerMgr(int);             // 0x00b3d4d0
void  FUN_00f195a0(void*, void*);               // 0x00f195a0
int   FUN_00f3b2f0(int, void*, void*);          // 0x00f3b2f0

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------
extern void*   DAT_016c7aa4;
extern int     DAT_016c826c;
extern int     DAT_016c8270;
extern int     DAT_016c8274;
extern int     DAT_016c82bc;
extern int     DAT_016c82c0;
extern float   DAT_0148c2b8;                    // FLT_MAX
extern uint8_t DAT_01601760;                    // EA::Random RNG
// the "0x01186577" argument the two noun vtbl+0xc calls receive is a hard-coded
// absolute address in the retail image (no base relocation); it is spelled as a
// literal pointer at the call sites rather than as an extern symbol.
extern const char STR_0148c304[];               // "0 1 1 1"

// ===========================================================================
// @ 0x00f1ef90
void cScenarioPlayProgressBar::FUN_00f1ef90(int index, char flag)
{
    *(int*)((char*)this + 0xb8) = index;
    FUN_00f1ad00(index);
    FUN_00f1ecf0();
    if (flag == 0)
    {
        FUN_00f1b450();
        FUN_00f1e6a0();
        if (*(int*)((char*)this + 0x90) == 3)
        {
            void* p = *(void**)((char*)*(void**)((char*)DAT_016c7aa4 + 0x6c) + 0x148);
            if (p != 0)
                ((cScenarioPlayProgressBar*)p)->FUN_00e148d0();
        }
        void* res = ((cScenarioPlayProgressBar*)*(void**)((char*)DAT_016c7aa4 + 0x74))->FUN_00f3be60(index);
        if (*(void**)((char*)this + 0xf0) != 0 &&
            (res == 0 || *(int*)((char*)res + 0x80) != *(int*)((char*)this + 0xf4)))
        {
            FUN_00572020(*(void**)((char*)this + 0xf0), 0);
            *(void**)((char*)this + 0xf0) = 0;
            *(void**)((char*)this + 0xf4) = 0;
        }
        if (*(void**)((char*)this + 0xf0) == 0 && res != 0 && *(int*)((char*)res + 0x80) != 0)
        {
            *(int*)((char*)this + 0xf4) = *(int*)((char*)res + 0x80);
            void* sys = EA_Audio_GetSystemAT();
            void* h;
            if (sys != 0)
                h = (*(void* (__thiscall**)(void*))(*(char**)sys + 0x20))(sys);
            else
                h = 0;
            *(void**)((char*)this + 0xf0) = h;
            if (SP_AudioSystem() != 0)
            {
                void* a = SP_AudioSystem();
                void* b = (*(void* (__thiscall**)(void*))(*(char**)a + 0x1c))(a);
                Vector3* pos = (Vector3*)(*(void* (__thiscall**)(void*, int))(*(char**)b + 0x10))(b, 0);
                Vector3 v;
                v.x = pos->x;
                v.y = pos->y;
                v.z = pos->z;
                FUN_00657240(*(void**)((char*)res + 0x80), *(void**)((char*)this + 0xf0), &v);
                RecordEvent4((unsigned)*(void**)((char*)this + 0xf0), 0x12d2a4d4, 0.0f, 0);
                RecordEvent4((unsigned)*(void**)((char*)this + 0xf0), 0xba134192, 0.0f, 0);
                SetSoundSymbol((unsigned)*(void**)((char*)this + 0xf0), 0x9b3918c4, STR_0148c304);
                FUN_00dd1c50(0x8514d965, *(void**)((char*)this + 0xf0));
                FUN_006572b0(*(void**)((char*)this + 0xf0));
            }
        }
        ((cScenarioPlayProgressBar*)*(void**)((char*)DAT_016c7aa4 + 0x6c))->FUN_00f0e6c0();
        ((cScenarioPlayProgressBar*)*(void**)((char*)DAT_016c7aa4 + 0x6c))->FUN_00f114a0();
    }
    void* g = *(void**)((char*)DAT_016c7aa4 + 0x18);
    if (g != 0)
        ((cScenarioPlayProgressBar*)g)->FUN_00f347e0();
}

// ===========================================================================
// @ 0x00f1f180
void cScenarioPlayProgressBar::FUN_00f1f180()
{
    FUN_00f1e020();
    *(uint8_t*)((char*)this + 0xb4) = 0;
    *(int*)((char*)this + 0xc4) = (int)FUN_00eed8c0((char*)*(void**)((char*)*(void**)((char*)DAT_016c7aa4 + 0x74) + 0x10) + 8);
    if (*(int*)((char*)this + 0x90) != 2)
        return;
    *(int*)((char*)this + 0x90) = 0;
    FUN_00f1ef90(0, 0);
    int mode = *(int*)((char*)DAT_016c7aa4 + 0xd0);
    if (mode == 1 || mode == 2)
    {
        void* mgr = *(void**)((char*)DAT_016c7aa4 + 0x74);
        int* p = *(int**)((char*)mgr + 0x10);
        void* a = FUN_0067de40();
        void* b = (*(void* (__thiscall**)(void*))(*(char**)a + 0x20))(a);
        void** vt = (void**)(*(char**)b + 0x34);
        void* r = ((cScenarioPlayProgressBar*)((char*)p + 0x7c))->FUN_00f26360(0);
        ((void (__thiscall*)(void*, void*))*vt)(b, r);
        void* avatar = ((cGameNounManager*)SP_NounManager())->GetAvatar();
        if (avatar != 0)
        {
            *(int*)((char*)avatar + 0xb58) |= 0x800;
            void* mm = SP_ModelManager();
            int obj = *(int*)((char*)avatar + 0xb54);
            unsigned bits = (*(unsigned (__thiscall**)(void*, unsigned, int))(*(char**)mm + 0x28))(mm, 0x6669387, 0);
            if (bits < 0x40)
            {
                unsigned* w = (unsigned*)(*(int*)((char*)obj + 0x180) + 0x44 + (bits >> 5) * 4);
                *w |= 1u << (bits & 0x1f);
            }
            *(float*)((char*)*(void**)((char*)avatar + 0xb54) + 0x80) = 0.0f;
            void* hash = (char*)*(void**)((char*)*(void**)((char*)avatar + 0xb54) + 0x17c) + 0x17a0;
            HashIt it = ((cScenarioPlayProgressBar*)hash)->FUN_00594410();
            void* end;
            void* node = it.node;
            void** bucket = it.bucket;
            end = ((void**)*(void**)((char*)hash + 4))[*(int*)((char*)hash + 8)];
            while (node != end)
            {
                void* e = *(void**)((char*)node + 4);
                void* o = *(void**)((char*)e + 0x8c);
                if (o != 0 &&
                    (*(uint8_t (__thiscall**)(void*))(*(char**)o + 0x10))(o))
                {
                    (*(void (__thiscall**)(void*, int))(*(char**)o + 0x2c))(o, 1);
                    (*(void (__thiscall**)(void*, int))(*(char**)o + 0x30))(o, 1);
                }
                node = *(void**)((char*)node + 8);
                if (node == 0)
                {
                    do
                    {
                        bucket = (void**)((char*)bucket + 4);
                        node = *bucket;
                    } while (node == 0);
                }
            }
        }
        ((cScreen*)GetTriggerMgr(1))->setX();
        unsigned idx = ((cRandomLCG*)&DAT_01601760)->RandomUint32Uniform((DAT_016c82c0 - DAT_016c82bc) >> 4);
        ((cTriggerMgr*)GetTriggerMgr(*(int*)(DAT_016c82bc + idx * 16)))->PostTrigger(1, 0, 0, 0, 1);
        *(int*)((char*)this + 0x90) = 1;
    }
    else
    {
        FUN_00f1c4b0();
        if (*(int*)((char*)this + 0x90) != 0)
            return;
        *(int*)((char*)this + 0x90) = 3;
        void* q = *(void**)((char*)*(void**)((char*)DAT_016c7aa4 + 0x6c) + 0x148);
        if (q != 0)
            ((cScenarioPlayProgressBar*)q)->FUN_00e148d0();
    }
}

// ===========================================================================
// @ 0x00f1f3b0
void cScenarioPlayProgressBar::FUN_00f1f3b0()
{
    int n = (*(int*)((char*)this + 0x68) - *(int*)((char*)this + 0x64)) / 0x1ac;
    int i = 0;
    if (n > 0)
    {
        int off = 0;
        do
        {
            char* rec = (char*)(*(int*)((char*)this + 0x64) + off);
            if (*rec == 0 &&
                i < (*(int*)((char*)this + 0x68) - *(int*)((char*)this + 0x64)) / 0x1ac &&
                (*(int*)(rec + 0x24) == 10 || *(int*)(rec + 0x24) == 0x0b))
            {
                *(uint8_t*)rec = 1;
                *(int*)(rec + 4) = *(int*)(rec + 0x30);
                if (*(int*)(rec + 0x24) == 0x0b)
                {
                    ++*(int*)((char*)this + 0x18);
                    if (*(int*)((char*)DAT_016c7aa4 + 0xd0) == 2)
                    {
                        void* c = FUN_00675250(0xfcace0d7, 1);
                        ((cScenarioPlayProgressBar*)c)->FUN_00676e90();
                    }
                }
                ++*(int*)((char*)this + 0x28);
            }
            ++i;
            off += 0x1ac;
        } while (i < n);
    }
    if (*(int*)((char*)this + 0xb8) == ((cScenarioPlayProgressBar*)*(void**)((char*)DAT_016c7aa4 + 0x74))->FUN_00f3be30() - 1)
    {
        FUN_00f1aae0(5);
        return;
    }
    ((cPlanetModel*)SP_PlanetModel(0x8000000))->MaskContinentBits();
    ((cScenarioPlayProgressBar*)*(void**)((char*)DAT_016c7aa4 + 0x74))->FUN_00f46410(2, *(int*)((char*)this + 0xb8), *(int*)((char*)this + 0xb8) + 1);
    if (*(int*)((char*)this + 0x90) != 3)
        *(int*)((char*)this + 0x90) = 3;
    FUN_00f1ef90(*(int*)((char*)this + 0xb8) + 1, 0);
    FUN_00f1c4b0();
}

// ===========================================================================
// @ 0x00f1f4e0
void cScenarioPlayProgressBar::FUN_00f1f4e0(int index)
{
    if (*(int*)((char*)this + 0x90) == 3 &&
        index < ((cScenarioPlayProgressBar*)*(void**)((char*)DAT_016c7aa4 + 0x74))->FUN_00f3be30())
    {
        *(uint8_t*)((char*)this + 0xec) = 1;
        ((cPlanetModel*)SP_PlanetModel(0x8000000))->MaskContinentBits();
        void* mgr = *(void**)((char*)DAT_016c7aa4 + 0x74);
        int i = 0;
        ((cScenarioPlayProgressBar*)mgr)->FUN_00f45fd0(2, 0, 0);
        FUN_00f1ef90(0, index != 0);
        if (*(int*)((char*)this + 0xb8) != index)
        {
            do
            {
                int n = (*(int*)((char*)this + 0x68) - *(int*)((char*)this + 0x64)) / 0x1ac;
                for (int j = 0; j < n; ++j)
                    FUN_00f1de30(j);
                ((cPlanetModel*)SP_PlanetModel(0x8000000))->MaskContinentBits();
                ++i;
                ((cScenarioPlayProgressBar*)mgr)->FUN_00f46410(2, *(int*)((char*)this + 0xb8), i);
                FUN_00f1ef90(i, index != i);
            } while (*(int*)((char*)this + 0xb8) != index);
        }
        FUN_00f1c4b0();
        *(uint8_t*)((char*)this + 0xec) = 0;
        ((cScenarioPlayProgressBar*)*(void**)((char*)DAT_016c7aa4 + 0x6c))->FUN_00f0e6c0();
    }
}

// ===========================================================================
// @ 0x00f1f600
void cScenarioPlayProgressBar::FUN_00f1f600()
{
    if (*(int*)((char*)this + 0x90) != 3 ||
        *(int*)((char*)this + 0x64) == *(int*)((char*)this + 0x68))
        return;
    *(float*)((char*)this + 0xdc) = DAT_0148c2b8;
    *(int*)((char*)this + 0xe0) = DAT_016c826c;
    *(int*)((char*)this + 0xe4) = DAT_016c8270;
    *(int*)((char*)this + 0xe8) = DAT_016c8274;
    int count = (*(int*)((char*)this + 0x68) - *(int*)((char*)this + 0x64)) / 0x1ac;
    bool flag = false;
    if (count != 0)
    {
        int off = 0;
        int i = 0;
        do
        {
            char* rec = (char*)(*(int*)((char*)this + 0x64) + off);
            char used = *rec;
            if (used == 0 || *(uint8_t*)(rec + 1) != 0)
            {
                int type = *(int*)(rec + 0x24);
                switch (type)
                {
                case 1:
                case 7:
                    if (used == 0)
                    {
                        bool is7 = (type == 7);
                        void* mgr = *(void**)((char*)DAT_016c7aa4 + 0x74);
                        int r = ((cScenarioPlayProgressBar*)mgr)->FUN_00f3e8a0(*(int*)(rec + 0x28));
                        if (!is7 && r != 0 && ((cScenarioPlayProgressBar*)r)->FUN_00f278b0())
                        {
                            if (*rec == 0)
                                flag = true;
                            break;
                        }
                        void* avatar = ((cGameNounManager*)SP_NounManager())->GetAvatar();
                        void* av;
                        if (avatar != 0)
                            av = (*(void* (__thiscall**)(void*, uint8_t*))(*(char**)avatar + 0xc))(avatar, (uint8_t*)0x01186577);
                        else
                            av = 0;
                        PtrVec vec;
                        vec.begin = 0;
                        vec.end = 0;
                        vec.cap = 0;
                        ((cScenarioPlayProgressBar*)mgr)->FUN_00f40d00(*(int*)(rec + 0x28), &vec);
                        int n = (int)((int*)vec.end - (int*)vec.begin);
                        for (int j = 0; j < n; ++j)
                        {
                            void* p = (void*)((int*)vec.begin)[j];
                            int key = *(int*)((char*)p + 0x24);
                            void* out;
                            void* it = ((cScenarioPlayProgressBar*)(rec + 8))->FUN_00e5c780(&out, &key);
                            if (*(void**)it == (void*)(rec + 0xc))
                            {
                                void* q = (*(void* (__thiscall**)(void*, uint8_t*))(*(char**)p + 0xc))(p, (uint8_t*)0x01186577);
                                if (q != 0)
                                {
                                    float dist = FUN_00f1aa10(is7, q);
                                    float* pf = (*(float* (__thiscall**)(void*))(*(char**)((char*)avatar + 0xc0) + 0x2c))((char*)avatar + 0xc0);
                                    float* qf = (*(float* (__thiscall**)(void*))(*(char**)q + 0x2c))(q);
                                    float dx = qf[0] - pf[0];
                                    float dy = qf[1] - pf[1];
                                    float dz = qf[2] - pf[2];
                                    float d = sqrtf(dx * dx + dy * dy + dz * dz);
                                    if (d < *(float*)((char*)this + 0xdc))
                                    {
                                        *(float*)((char*)this + 0xdc) = d;
                                        float* qq = (*(float* (__thiscall**)(void*))(*(char**)q + 0x2c))(q);
                                        *(float*)((char*)this + 0xe0) = qq[0];
                                        *(float*)((char*)this + 0xe4) = qq[1];
                                        *(float*)((char*)this + 0xe8) = qq[2];
                                    }
                                    if (((cScenarioPlayProgressBar*)mgr)->FUN_00f3c870(av, q, dist, 0))
                                    {
                                        int k2 = *(int*)((char*)p + 0x24);
                                        ((cScenarioPlayProgressBar*)(rec + 8))->FUN_00a18440(&k2, 0);
                                        FUN_00f1ae10(rec, q, 0);
                                        if (is7)
                                        {
                                            ++*(int*)((char*)this + 0x20);
                                            FUN_00f195a0(p, q);
                                            FUN_00f1c4b0();
                                        }
                                        if (*rec != 0)
                                            break;
                                    }
                                }
                            }
                        }
                        vec.Destroy();
                    }
                    if (*rec == 0)
                        flag = true;
                    break;
                case 6:
                    {
                        void* a = 0;
                        void* b = 0;
                        int r = FUN_00f3b2f0(type, &a, &b);
                        if (FUN_00f1c030(*(int*)(rec + 0x28), *(int*)(rec + 0x2c), r))
                        {
                            if (*rec == 0)
                                FUN_00f1ae10(rec, a, b);
                        }
                        else
                        {
                            flag = true;
                            if (*rec != 0)
                                FUN_00f19ac0(rec, 0);
                        }
                    }
                    break;
                case 10:
                    if (*(uint8_t*)((char*)this + 0x79) != 0 && *(uint8_t*)((char*)this + 0x78) == 0)
                        flag = true;
                    {
                        int r = FUN_00f3b2f0(type, 0, 0);
                        if (FUN_00f1c030(*(int*)(rec + 0x28), *(int*)(rec + 0x2c), r))
                        {
                            void* g = *(void**)((char*)DAT_016c7aa4 + 0x7c);
                            if (g != 0)
                                *(int*)((char*)g + 0xc) = i;
                            char buf[12];
                            cString* cs = (cString*)buf;
                            cs->Construct();
                            unsigned id;
                            if (*(int*)(rec + 0x24) == 10)
                                id = 0x796cfe1;
                            else if (*(int*)(rec + 0x24) == 0xb)
                                id = 0x796cfe5;
                            else
                                id = 0x796d59a;
                            cs->Load(0x21851ebe, id, 0);
                            const wchar_t* t = cs->GetText();
                            const wchar_t* e = t;
                            while (*e != 0)
                                ++e;
                            ((WString*)((char*)this + 0x54))->assign(t, e);
                            *(int*)((char*)this + 0xb0) = 2;
                            FUN_00f1aae0(6);
                            cs->Destroy();
                        }
                    }
                    break;
                case 11:
                    if (*(uint8_t*)((char*)this + 0x79) != 0 && *(uint8_t*)((char*)this + 0x78) == 0)
                        flag = true;
                    break;
                default:
                    if (used == 0)
                        flag = true;
                    break;
                }
            }
            ++i;
            off += 0x1ac;
        } while (i < count);
        if (flag)
            return;
    }
    FUN_00f1f3b0();
}
