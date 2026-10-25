// Spore retail 00c2e420..00c2f690 -- creature/tribe mission classes.
// Small accessors/thunks are reconstructed exactly; the large Read/Update bodies are
// reconstructed from the original instruction flow (see partial.txt / nonmatching.txt).

#include "types.h"

typedef unsigned int uint32;
typedef unsigned int size_type;

extern "C" void* FUN_00401090(void*);
extern "C" int   FUN_004df550(void*);
extern "C" void* FUN_00b3d4c0(void*, int, int);
extern "C" void  FUN_00ba3f90(void*);
extern "C" int   FUN_00b6e270(int);
extern "C" int   FUN_00b6e290(int);
extern "C" void  FUN_00c46500(void*);
extern "C" void  FUN_00c45140(void*);
extern "C" void  FUN_00c449c0();
extern "C" void  SP_cCreatureModeStrategy_NotifyEvent(float);
extern "C" int   SP_cSPTimer_IsRunning(void*);
extern "C" void  SP_cSPTimer_Restart(void*);
extern "C" int   SP_GetPropertyAsKey(int, int, int);
void* __fastcall FUN_0041ea00(void*);   // Property::GetUInt (this in ECX, returns &value)
extern "C" void* FUN_00b3d300(int);     // 0x00b3d300 SP::NounManager accessor
int  __fastcall FUN_00b1f9d0(void*);    // 0x00b1f9d0 ?GetPlayerEmpireOrMinus1 (this in ECX)
extern "C" void* FUN_00b3d2c0(int);     // 0x00b3d2c0 SP::RelationshipManager accessor
void __fastcall FUN_00d00a10(void*);    // 0x00d00a10 (this in ECX)
extern "C" void FUN_00b18600();         // 0x00b18600 SP::cGameData::Read     (this in ECX, stack stream)
extern "C" void FUN_00692f90();         // 0x00692f90 SP::cVarListSerializer ctor
extern "C" void FUN_00693e10();         // 0x00693e10 SP::cVarListSerializer Read

extern "C" void* __cdecl FUN_00b5b800();          // 0x00b5b800 SP::GetCurrentGameMode
extern "C" void* FUN_00d37cb0();                  // 0x00d37cb0
extern "C" void* FUN_00cd3440();                  // 0x00cd3440
extern "C" void* FUN_00d004b0();                  // 0x00d004b0
extern "C" void  FUN_00d2e8a0(float);             // 0x00d2e8a0 cCreatureModeStrategy::NotifyEvent
extern "C" void  FUN_00e39710(unsigned, int, void*, int*, int*); // 0x00e39710
extern "C" void  FUN_00ba58e0(int, int);          // 0x00ba58e0
extern "C" void  FUN_00b707a0();                  // 0x00b707a0 (thiscall, 1 stack arg)
extern "C" void  FUN_00cdb3a0();                  // 0x00cdb3a0 (thiscall, 2 stack args)
extern "C" void  FUN_00cdab10();                  // 0x00cdab10 (thiscall, no args)
extern "C" void* FUN_00cd40b0();                  // 0x00cd40b0 cTribeModeStrategy::Instance
extern "C" void* FUN_00d539d0();                  // 0x00d539d0 cPosseSimulator::Instance
extern "C" void* FUN_00b3d240();                  // 0x00b3d240
extern "C" void* FUN_00b3d4d0();                  // 0x00b3d4d0 GetTriggerMgr
extern "C" void* FUN_00ae0930();                  // 0x00ae0930 cTriggerMgr::PostTrigger (thiscall, 6 args)
extern "C" void* FUN_00f67d90();                  // 0x00f67d90
extern "C" int   FUN_00b1fdb0();                  // 0x00b1fdb0 avatar accessor
extern "C" int   FUN_00c0bc00();                  // 0x00c0bc00 creature key accessor
extern "C" int   FUN_00bfc5f0();                  // 0x00bfc5f0
extern "C" int   FUN_00d52e10();                  // 0x00d52e10
extern "C" float FUN_00c03440(int);               // 0x00c03440 (cdecl, returns float in st0)
extern "C" int   FUN_00d00a70();                  // 0x00d00a70 cRelationshipManager::ClampClassify
extern "C" int   FUN_00ba4370();                  // 0x00ba4370 (thiscall, 1 stack arg)
extern "C" int   FUN_00ba4390();                  // 0x00ba4390 (thiscall, 1 stack arg)
extern "C" int   FUN_00ad7a30();                  // 0x00ad7a30 cActionTarget ctor
extern "C" void  FUN_00ad7ad0();                  // 0x00ad7ad0 cActionTarget dtor
extern "C" void  FUN_00ae09b0();                  // 0x00ae09b0 cTriggerMgr::PostAction
extern "C" char  __cdecl CreateImageFromResource2(void*, void**, char, int, int); // 0x00806230
extern "C" void  __cdecl SetGlobalProperty(unsigned int, float);                  // 0x005ca880
extern "C" void  __cdecl RecordEvent2(unsigned int, unsigned int);                // 0x00435ed0
extern "C" int   __cdecl GetRecorderState();                                      // 0x00435e90
extern "C" void* __cdecl FUN_00a206f0();                                          // 0x00a206f0 audio system
extern "C" void* __cdecl FUN_0067cb30();                                          // 0x0067cb30
extern "C" void  FUN_00c756a0();                                                  // 0x00c756a0 (thiscall, 2 args)
extern "C" void  FUN_0060d860();                                                  // 0x0060d860

extern char DAT_01654c01;
extern char DAT_01654c02;
extern char DAT_01654c04;
extern int* g_169e3e8;                  // 0x0169e3e8 creature token translator

struct cVarListSerializer { char mPad[0xa14]; };   // 2580-byte stack serializer

typedef void (__fastcall *VFn)(void*);

struct SP_cSPTimer {
    bool IsRunning();                       // 0x00feba90
    unsigned long long GetElapsedTime();    // 0x00bc3190
    void Stop();                            // 0x00bc3110
};
struct C45140Dtor {
    void FUN_00c45140();                    // 0x00c45140
};

class MissionStub {
public:
    void  SetSerializer();
    char  FUN_00c2e4b0();
    int   FUN_00c2e4f0(int param);
    void  FUN_00c2e780();
    void  FUN_00c2e820();
    void  FUN_00c2e980();
    float FUN_00c2e9b0();
    char  FUN_00c2e9e0();
    void  FUN_00c2eb60();
    void  FUN_00c2ebc0();
    int   FUN_00c2f300();
    char  FUN_00c2f320(int* out);
    unsigned char FUN_00c2e420(int param_2);

    void  FUN_00c2e520();
    void  FUN_00c2e5a0();
    unsigned char FUN_00c2e6c0(int param_2);
    void  FUN_00c2e7b0(int param_2);
    unsigned char FUN_00c2e8c0(int param_2);
    unsigned char FUN_00c2eaa0(int param_2);
    void  FUN_00c2ed20(int* out1, int* out2);
    void  FUN_00c2f090();
    int   FUN_00c2f190();
    int   FUN_00c2f240();
    void  FUN_00c2f520();
    void  FUN_00c2f590();
    void  FUN_00c2f5f0();
    char  FUN_00c2f690();
};

// ---------------------------------------------------------------------------
// Small accessors/thunks.
// ---------------------------------------------------------------------------

// @ 0x00c2e4e0
void MissionStub::SetSerializer()
{
}

// @ 0x00c2e4b0
char MissionStub::FUN_00c2e4b0()
{
    char* self = (char*)this;
    if (*(int*)(self + 0x7c) != 5) {
        *(int*)(self + 0x7c) = 5;
        void** vt = *(void***)self;
        ((VFn)vt[0xbc / 4])(self);
        ((VFn)vt[0x6c / 4])(self);
        return 1;
    }
    return 0;
}

// @ 0x00c2e4f0
int MissionStub::FUN_00c2e4f0(int param)
{
    char* self = (char*)this;
    void** vt = *(void***)self;
    int r = ((int(__fastcall*)(void*))vt[0xc0 / 4])(self);
    if (r != 0)
        return SP_GetPropertyAsKey(r, (int)0xff60c676, param);
    return 0;
}

// @ 0x00c2e780
void MissionStub::FUN_00c2e780()
{
    char* p = (char*)this + 0x80;
    FUN_004df550(FUN_00401090(p));
}

// @ 0x00c2e820
void MissionStub::FUN_00c2e820()
{
    char* p = (char*)this + 0x80;
    FUN_00ba3f90(FUN_00b3d4c0(p, 0, 0));
}

// @ 0x00c2e980
void MissionStub::FUN_00c2e980()
{
    SP_cCreatureModeStrategy_NotifyEvent((float)*(int*)((char*)this + 0x84));
}

// @ 0x00c2e9b0
float MissionStub::FUN_00c2e9b0()
{
    char* self = (char*)this;
    if (!((SP_cSPTimer*)(self + 0x38))->IsRunning() && *(int*)(self + 0x7c) == 5)
        return 0.0f;
    return *(float*)(self + 0x88);
}

// @ 0x00c2e9e0
char MissionStub::FUN_00c2e9e0()
{
    char* self = (char*)this;
    if (*(int*)(self + 0x7c) != 5) {
        *(int*)(self + 0x7c) = 5;
        void** vt = *(void***)self;
        ((VFn)vt[0xbc / 4])(self);
        ((VFn)vt[0x6c / 4])(self);
        SP_cSPTimer_Restart(self + 0x38);
        return 1;
    }
    return 0;
}

// @ 0x00c2eb60
void MissionStub::FUN_00c2eb60()
{
    char* self = (char*)this;
    FUN_00b6e270(*(int*)(self + 0x8c));
    FUN_00b6e290(*(int*)(self + 0x90));
}

// @ 0x00c2ebc0
void MissionStub::FUN_00c2ebc0()
{
    char* self = (char*)this;
    if (*(int*)(self + 0x7c) != 5)
        *(int*)(self + 0x7c) = 4;
}

// @ 0x00c2f300
int MissionStub::FUN_00c2f300()
{
    char* self = (char*)this;
    int p = *(int*)(self + 0xc8);
    if (p != 0 && (*(unsigned char*)(p + 4) & 1) != 0)
        return 1;
    return 0;
}

// @ 0x00c2f320
char MissionStub::FUN_00c2f320(int* out)
{
    char* self = (char*)this;
    int p = *(int*)(self + 0xc8);
    if (p != 0 && (*(unsigned char*)(p + 4) & 1) != 0) {
        *out = p;
        return 1;
    }
    return 0;
}

// @ 0x00c2f340
int* __fastcall FUN_00c2f340(int* self)
{
    FUN_00c46500(self);
    self[0x1e] = 0;
    self[0x1f] = 3;
    self[0] = 0x146b0f8;
    self[1] = 0x146b0e8;
    self[0xd] = 0x146b0d8;
    self[0x20] = 0;
    return self;
}

// @ 0x00c2f3e0
void __fastcall FUN_00c2f3e0(int* self)
{
    self[0] = 0x146b0f8;
    self[1] = 0x146b0e8;
    self[0xd] = 0x146b0d8;
    int* p = (int*)self[0x20];
    if (p != 0) {
        typedef void (__fastcall *Fn)(void*);
        ((Fn*)p[0])[1](p);
    }
    self[0] = 0x146aff0;
    self[1] = 0x146afdc;
    self[0xd] = 0x146afcc;
    ((C45140Dtor*)self)->FUN_00c45140();
}

// ===========================================================================
// Large Read/Update/serialization members.
// ===========================================================================

// @ 0x00c2e420
unsigned char MissionStub::FUN_00c2e420(int param_2)
{
    // cGameData::Read, then one cVarListSerializer pass over the mission var list.
    unsigned char a = ((unsigned char(__thiscall*)(void*, int))FUN_00b18600)(this, param_2);
    cVarListSerializer ser;
    ((void(__thiscall*)(void*, void*, int, int))FUN_00692f90)(&ser, this, (int)0x01572560, (int)0x01a80d26);
    unsigned char b = ((unsigned char(__thiscall*)(void*, int))FUN_00693e10)(&ser, param_2);
    return (unsigned char)(a & b);
}

// @ 0x00c2e520
void MissionStub::FUN_00c2e520()
{
    char* self = (char*)this;
    SP_cSPTimer* timer = (SP_cSPTimer*)(self + 0x38);
    if (timer->IsRunning())
    {
        unsigned long long elapsed = timer->GetElapsedTime();
        if ((unsigned int)(elapsed >> 32) != 0 || (unsigned int)elapsed > 3000)
        {
            timer->Stop();
            char* mode = (char*)FUN_00b5b800();
            void* obj;
            if (mode == &DAT_01654c01)
                obj = FUN_00d37cb0();
            else if (mode == &DAT_01654c02)
                obj = FUN_00cd3440();
            else if (mode == &DAT_01654c04)
                obj = FUN_00d004b0();
            else
                return;
            if (obj != 0)
            {
                if (*(int*)(self + 0x7c) == 5)
                    ((void(__thiscall*)(void*, void*))(*(void***)obj)[0x30 / 4])(obj, self);
                ((void(__thiscall*)(void*, int))(*(void***)obj)[0x28 / 4])(obj, 0);
            }
        }
    }
}

// @ 0x00c2e5a0
void MissionStub::FUN_00c2e5a0()
{
    char* self = (char*)this;
    ((void(__thiscall*)(void*))FUN_00c449c0)(self);
    char* mode = (char*)FUN_00b5b800();
    void* obj;
    if (mode == &DAT_01654c01)
        obj = FUN_00d37cb0();
    else if (mode == &DAT_01654c02)
        obj = FUN_00cd3440();
    else if (mode == &DAT_01654c04)
        obj = FUN_00d004b0();
    else
        return;

    if (((char(__thiscall*)(void*, void*))(*(void***)obj)[0x2c / 4])(obj, self))
    {
        SetGlobalProperty(0xc1fa4704, 1.0f);
        void* audio = FUN_00a206f0();
        unsigned int v;
        if (audio != 0)
            v = ((unsigned int(__thiscall*)(void*))(*(void***)audio)[0x20 / 4])(audio);
        else
            v = 0;
        RecordEvent2(0xc871d6e, v);
    }
}

// @ 0x00c2e6c0
unsigned char MissionStub::FUN_00c2e6c0(int param_2)
{
    char* self = (char*)this;
    cVarListSerializer ser1;
    cVarListSerializer ser2;

    unsigned char a = ((unsigned char(__thiscall*)(void*, int))FUN_00b18600)(self, param_2);
    ((void(__thiscall*)(void*, void*, int, int))FUN_00692f90)(&ser1, self, (int)0x01572560, (int)0x01a80d26);
    unsigned char b = ((unsigned char(__thiscall*)(void*, int))FUN_00693e10)(&ser1, param_2);
    b &= a;
    ((void(__thiscall*)(void*, void*, int, int))FUN_00692f90)(&ser2, self, (int)0x01572618, (int)0x01a80d26);
    unsigned char c = ((unsigned char(__thiscall*)(void*, int))FUN_00693e10)(&ser2, param_2);
    c &= b;
    return c;
}

// @ 0x00c2e7b0
struct ImageKey { unsigned int mA; unsigned int mB; unsigned int mC; };

void MissionStub::FUN_00c2e7b0(int param_2)
{
    char* self = (char*)this;
    void* g = ((void*(*)())FUN_00401090)();
    int profile = ((int(__thiscall*)(void*, void*))FUN_004df550)(g, self + 0x80);
    if (profile != 0)
    {
        ImageKey key;
        key.mA = *(unsigned int*)(profile + 0x504);
        key.mB = 0x2f7d0004;
        key.mC = *(unsigned int*)(profile + 0x50c);
        CreateImageFromResource2(&key, (void**)param_2, 0, -1, -1);
    }
}

// @ 0x00c2e8c0
unsigned char MissionStub::FUN_00c2e8c0(int param_2)
{
    char* self = (char*)this;
    cVarListSerializer ser1;
    cVarListSerializer ser2;

    unsigned char a = ((unsigned char(__thiscall*)(void*, int))FUN_00b18600)(self, param_2);
    ((void(__thiscall*)(void*, void*, int, int))FUN_00692f90)(&ser1, self, (int)0x01572560, (int)0x01a80d26);
    unsigned char b = ((unsigned char(__thiscall*)(void*, int))FUN_00693e10)(&ser1, param_2);
    b &= a;
    ((void(__thiscall*)(void*, void*, int, int))FUN_00692f90)(&ser2, self, (int)0x01572960, (int)0x01a80d26);
    unsigned char c = ((unsigned char(__thiscall*)(void*, int))FUN_00693e10)(&ser2, param_2);
    c &= b;
    return c;
}

// @ 0x00c2eaa0
unsigned char MissionStub::FUN_00c2eaa0(int param_2)
{
    char* self = (char*)this;
    cVarListSerializer ser1;
    cVarListSerializer ser2;

    unsigned char a = ((unsigned char(__thiscall*)(void*, int))FUN_00b18600)(self, param_2);
    ((void(__thiscall*)(void*, void*, int, int))FUN_00692f90)(&ser1, self, (int)0x01572560, (int)0x01a80d26);
    unsigned char b = ((unsigned char(__thiscall*)(void*, int))FUN_00693e10)(&ser1, param_2);
    b &= a;
    ((void(__thiscall*)(void*, void*, int, int))FUN_00692f90)(&ser2, self, (int)0x01572a18, (int)0x01a80d26);
    unsigned char c = ((unsigned char(__thiscall*)(void*, int))FUN_00693e10)(&ser2, param_2);
    c &= b;
    return c;
}

// @ 0x00c2ed20
void MissionStub::FUN_00c2ed20(int* out1, int* out2)
{
    char* self = (char*)this;
    void* mgr = ((void*(*)())FUN_00b3d4c0)();

    int old8c = *(int*)(self + 0x8c);
    int olda0 = *(int*)(self + 0xa0);
    int old90 = *(int*)(self + 0x90);
    void* p80 = self + 0x80;

    int n8c = ((int(__thiscall*)(void*, void*))FUN_00ba4370)(mgr, p80);
    *(int*)(self + 0x8c) = n8c;
    int n90 = ((int(__thiscall*)(void*, void*))FUN_00ba4390)(mgr, p80);
    *(int*)(self + 0x90) = n90;
    int na0 = ((int(__thiscall*)(void*, void*, int, int))FUN_00ba3f90)(mgr, p80, 0, 0);
    *(int*)(self + 0xa0) = na0;

    if (*(int*)(self + 0x7c) != 5)
    {
        if (old8c != n8c && olda0 != na0 && *(int*)(self + 0xa4) != 0 &&
            n8c == *(int*)(self + 0xbc) && na0 == 6)
        {
            RecordEvent2(0xc871d6e, GetRecorderState());
            ((void(__thiscall*)(void*))(*(void***)self)[0x78 / 4])(self);

            int keyA[3] = { 0, 0, 0 };
            int keyB[3] = { 0, 0, 0 };
            void* noun = ((void*(*)())FUN_00b3d300)();
            int avatar = ((int(__thiscall*)(void*))FUN_00b1fdb0)(noun);
            int ch = ((int(__thiscall*)(void*))FUN_00c0bc00)((void*)avatar);
            FUN_00e39710(0x43715491, ch, p80, keyB, keyA);

            ((void(__thiscall*)(void*))(*(void***)self)[0x6c / 4])(self);

            float f = FUN_00c03440(*(int*)(self + 0xc0));
            int v = (int)(f * *(int*)(self + 0x94));
            *(int*)(self + 0x9c) = v;
            float fv = (float)v;
            FUN_00d2e8a0(fv);

            noun = ((void*(*)())FUN_00b3d300)();
            void* terrain = ((void*(__thiscall*)(void*))FUN_00f67d90)(noun);
            ((void(__thiscall*)(void*, float, int))FUN_00c756a0)(terrain, fv, 1);

            void* poll = ((void*(*)())FUN_0067cb30)();
            ((void(__thiscall*)(void*, unsigned int, void*))FUN_0060d860)(poll, 0xcdb3f5d8, p80);
        }

        if (old90 != *(int*)(self + 0x90) && *(int*)(self + 0xa8) != 0 &&
            *(int*)(self + 0x90) == *(int*)(self + 0xb0) && *(int*)(self + 0xa0) == 5)
        {
            RecordEvent2(0xc871d6e, GetRecorderState());
            ((void(__thiscall*)(void*))(*(void***)self)[0x78 / 4])(self);

            int keyA[3] = { 0, 0, 0 };
            int keyB[3] = { 0, 0, 0 };
            void* noun = ((void*(*)())FUN_00b3d300)();
            int avatar = ((int(__thiscall*)(void*))FUN_00b1fdb0)(noun);
            int ch = ((int(__thiscall*)(void*))FUN_00c0bc00)((void*)avatar);
            FUN_00e39710(0xb4987e04, ch, p80, keyB, keyA);

            ((void(__thiscall*)(void*))(*(void***)self)[0x6c / 4])(self);

            float f = FUN_00c03440(*(int*)(self + 0xc0));
            int v = (int)(f * *(int*)(self + 0x98));
            *(int*)(self + 0x9c) = v;
            float fv = (float)v;
            FUN_00d2e8a0(fv);

            noun = ((void*(*)())FUN_00b3d300)();
            void* terrain = ((void*(__thiscall*)(void*))FUN_00f67d90)(noun);
            ((void(__thiscall*)(void*, float, int))FUN_00c756a0)(terrain, fv, 0);
        }
    }

    void* posse = FUN_00d539d0();
    int r = ((int(__thiscall*)(void*))FUN_00d52e10)(posse);

    if ((unsigned int)*(int*)(self + 0x90) >= (unsigned int)*(int*)(self + 0xb0))
    {
        *out1 = 0;
        *out2 = 0x602c1346;
        return;
    }
    if ((unsigned int)*(int*)(self + 0x8c) >= (unsigned int)*(int*)(self + 0xbc))
    {
        *out1 = ((r <= 0 ? -1 : 0) & 0xa84c376f) + 0xdc9fb12c;
        *out2 = 0;
        return;
    }
    if (*(int*)(self + 0xa0) == 5)
    {
        *out1 = (int)0xa0065a8;
        *out2 = ((*(unsigned char*)(self + 0xc4) != 0 ? -1 : 0) & 0xd7a75edd) + 0x281fbe06;
        return;
    }
    if (*(unsigned char*)(self + 0xc4) != 0)
    {
        *out1 = 0x240d5188;
        *out2 = (int)0xffc71ce3;
        return;
    }
    *out1 = ((r <= 0 ? -1 : 0) & 0x18ef9bed) + 0x4fd8b903;
    *out2 = 0x281fbe06;
}

// @ 0x00c2f090
void MissionStub::FUN_00c2f090()
{
    char* self = (char*)this;

    int* pi = (int*)((void*(__thiscall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (pi != 0)
        ((void(__thiscall*)(void*))(*(void***)pi)[0 / 4])(pi);

    unsigned int u = ((unsigned int(__thiscall*)(void*))(*(void***)self)[0x58 / 4])(self);
    g_169e3e8[0x14 / 4] = (int)u;
    g_169e3e8[0x10 / 4] = (int)u;

    void* gobj = ((void*(*)())FUN_00401090)();
    int profile = ((int(__thiscall*)(void*, void*))FUN_004df550)(gobj, self + 0x80);
    if (profile != 0)
        g_169e3e8[0x1c / 4] = profile;

    int v = ((int(__thiscall*)(void*))(*(void***)self)[0xa4 / 4])(self);
    g_169e3e8[0x20 / 4] = v;

    if (pi == *(int**)(self + 0xa4))
    {
        g_169e3e8[0xc / 4] = *(int*)(self + 0x8c);
        if ((unsigned int)*(int*)(self + 0x8c) < u)
            g_169e3e8[0x18 / 4] = (int)(u - (unsigned int)*(int*)(self + 0x8c));
        else
            g_169e3e8[0x18 / 4] = 0;
    }
    else if (pi == *(int**)(self + 0xa8))
    {
        g_169e3e8[0xc / 4] = *(int*)(self + 0x90);
        if ((unsigned int)*(int*)(self + 0x90) < u)
            g_169e3e8[0x18 / 4] = (int)(u - (unsigned int)*(int*)(self + 0x90));
        else
            g_169e3e8[0x18 / 4] = 0;
    }

    if (pi != 0)
        ((void(__thiscall*)(void*))(*(void***)pi)[4 / 4])(pi);
}

// @ 0x00c2f190
int MissionStub::FUN_00c2f190()
{
    char* self = (char*)this;
    int* pi = (int*)((void*(__thiscall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (pi != 0)
        ((void(__thiscall*)(void*))(*(void***)pi)[0 / 4])(pi);

    int r;
    if (pi == *(int**)(self + 0xa4))
    {
        r = *(int*)(self + 0x8c);
    }
    else if (pi == *(int**)(self + 0xa8))
    {
        r = *(int*)(self + 0x90);
    }
    else
    {
        if (pi != 0)
            ((void(__thiscall*)(void*))(*(void***)pi)[4 / 4])(pi);
        return 0;
    }

    if (pi != 0)
        ((void(__thiscall*)(void*))(*(void***)pi)[4 / 4])(pi);
    return r;
}

// @ 0x00c2f240
int MissionStub::FUN_00c2f240()
{
    char* self = (char*)this;
    if (*(int*)(self + 0x7c) == 5)
        return *(int*)(self + 0x9c);

    int* pi = (int*)((void*(__thiscall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (pi != 0)
        ((void(__thiscall*)(void*))(*(void***)pi)[0 / 4])(pi);

    int r;
    if (pi == *(int**)(self + 0xa4))
    {
        if (*(int*)(self + 0xa0) == 5 || *(int*)(self + 0xa0) == 6)
        {
            if (pi != 0)
                ((void(__thiscall*)(void*))(*(void***)pi)[4 / 4])(pi);
            return 0;
        }
        float f = FUN_00c03440(*(int*)(self + 0xc0));
        r = (int)(f * *(int*)(self + 0x94));
    }
    else if (pi == *(int**)(self + 0xa8))
    {
        float f = FUN_00c03440(*(int*)(self + 0xc0));
        r = (int)(f * *(int*)(self + 0x98));
    }
    else
    {
        if (pi != 0)
            ((void(__thiscall*)(void*))(*(void***)pi)[4 / 4])(pi);
        return 0;
    }

    if (pi != 0)
        ((void(__thiscall*)(void*))(*(void***)pi)[4 / 4])(pi);
    return r;
}

// @ 0x00c2f470
int* __fastcall FUN_00c2f470(int* self)   // Simulator::cTribeToTribeMission ctor
{
    FUN_00c46500(self);                   // base ctor (this in ECX)
    self[0x1e] = 0;
    self[0x1f] = 3;
    self[0] = 0x0146b210;                 // vtbl_Simulator::cTribeToTribeMission
    self[1] = 0x0146b200;
    self[0x0d] = 0x0146b1f0;
    self[0x20] = 0;
    self[0x21] = 0;
    self[0x22] = 0;
    self[0x23] = 0;
    self[0x24] = 0;
    return self;
}

// @ 0x00c2f520
void MissionStub::FUN_00c2f520()
{
    char* self = (char*)this;
    *(int*)(self + 0x00) = 0x0146b210;
    *(int*)(self + 0x04) = 0x0146b200;
    *(int*)(self + 0x34) = 0x0146b1f0;

    int* p = *(int**)(self + 0x88);
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[4 / 4])(p);
    p = *(int**)(self + 0x84);
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[4 / 4])(p);
    p = *(int**)(self + 0x80);
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[4 / 4])(p);

    *(int*)(self + 0x00) = 0x0146aff0;
    *(int*)(self + 0x04) = 0x0146afdc;
    *(int*)(self + 0x34) = 0x0146afcc;

    ((void(__thiscall*)(void*))FUN_00c45140)(self);
}

// @ 0x00c2f590
void MissionStub::FUN_00c2f590()
{
    char* self = (char*)this;
    void* noun = ((void*(*)())FUN_00b3d300)();
    int tribe = ((int(__thiscall*)(void*))FUN_00bfc5f0)(noun);
    int t = (tribe != 0) ? (tribe + 0x230) : 0;
    *(int*)(self + 0x8c) = FUN_00b6e270(t);

    int q = *(int*)(self + 0x80);
    *(int*)(self + 0x90) = FUN_00b6e290((q != 0) ? (q + 0x230) : 0);
}

// @ 0x00c2f5f0
void MissionStub::FUN_00c2f5f0()
{
    char* self = (char*)this;
    FUN_00c2e520();

    int* obj = *(int**)(self + 0x80);
    int empire = FUN_00b1f9d0(obj);
    int rel = ((int(__thiscall*)(void*, int))(*(void***)obj)[0x4c / 4])(obj, empire);
    void* mgr = ((void*(*)())FUN_00b3d2c0)();
    int cls = ((int(__thiscall*)(void*, int, int, int))FUN_00d00a70)(mgr, rel, empire, 1);

    if (cls == 4)
        ((void(__thiscall*)(void*))(*(void***)self)[0x78 / 4])(self);

    if (*(unsigned char*)(*(int*)(self + 0x80) + 0x556) != 0)
        ((void(__thiscall*)(void*))(*(void***)self)[0x78 / 4])(self);
}

// @ 0x00c2f650
void __fastcall FUN_00c2f650(int* self)
{
    int* p = *(int**)((char*)self + 0x80);
    void* noun = FUN_00b3d300(0);
    int empire = FUN_00b1f9d0(noun);
    int rel = ((int(__thiscall*)(void*, int))(*(void***)p)[0x4c / 4])(p, empire);
    void* relMgr = FUN_00b3d2c0(rel);
    FUN_00d00a10(relMgr);
}

// @ 0x00c2f690
char MissionStub::FUN_00c2f690()
{
    char* self = (char*)this;
    if (*(int*)(self + 0x7c) == 5)
        return 0;

    *(int*)(self + 0x7c) = 5;
    ((void(__thiscall*)(void*))(*(void***)self)[0xbc / 4])(self);
    ((void(__thiscall*)(void*))(*(void***)self)[0x6c / 4])(self);

    int* obj = *(int**)(self + 0x80);
    int empire = FUN_00b1f9d0(obj);
    int rel = ((int(__thiscall*)(void*, int))(*(void***)obj)[0x4c / 4])(obj, empire);
    void* mgr = ((void*(*)())FUN_00b3d2c0)();
    int cls = ((int(__thiscall*)(void*, int, int, int))FUN_00d00a70)(mgr, rel, empire, 1);

    int code;
    if (cls == 4)
    {
        code = 2;
    }
    else
    {
        int* sub = (int*)(*(int*)(self + 0x80) + 0x120);
        void* eng = ((void*(*)())FUN_00b3d240)();
        int tmp = ((int(__thiscall*)(void*, int))(*(void***)sub)[0x2c / 4])(sub, (int)0x0168de6c);
        ((void(__thiscall*)(void*, unsigned int, int))(*(void***)eng)[0x60 / 4])(eng, 0x1046f5ef, tmp);
        FUN_00ba58e0(*(int*)(self + 0x80), 6);
        code = 1;
    }

    void* s1 = FUN_00cd3440();
    ((void(__thiscall*)(void*, unsigned int))FUN_00b707a0)(s1, 0xdcdf2f2f);

    void* s2 = FUN_00cd40b0();
    ((void(__thiscall*)(void*, int, int))FUN_00cdb3a0)(s2, code, *(int*)(self + 0x80));

    if (code == 1)
    {
        void* trigger = ((void*(*)())FUN_00b3d4d0)();
        int t = ((int(__thiscall*)(void*, int, int, int, int, int, int))FUN_00ae0930)
                    (trigger, (int)0x0146b300, 1, 1, 0, 0, 0);

        int* obj2 = *(int**)(self + 0x80);
        int ap = ((int(__thiscall*)(void*))(*(void***)obj2)[0xac / 4])(obj2);
        int* target = (ap != 0) ? (int*)(ap + 0x34) : 0;

        char tgt[0x40];
        ((void(__thiscall*)(void*, int*, int))FUN_00ad7a30)(tgt, target, t);
        void* tm1 = ((void*(*)())FUN_00b3d4d0)();
        ((void(__thiscall*)(void*, unsigned int, void*))FUN_00ae09b0)(tm1, 0xd749c1, tgt);
        ((void(__thiscall*)(void*))FUN_00ad7ad0)(tgt);

        int q = *(int*)(self + 0x80);
        int* target2 = (q != 0) ? (int*)(q + 0x120) : 0;
        ((void(__thiscall*)(void*, int*, int))FUN_00ad7a30)(tgt, target2, t);
        void* tm2 = ((void*(*)())FUN_00b3d4d0)();
        ((void(__thiscall*)(void*, unsigned int, void*))FUN_00ae09b0)(tm2, 0xe44aea33, tgt);
        ((void(__thiscall*)(void*))FUN_00ad7ad0)(tgt);

        void* s3 = FUN_00cd40b0();
        ((void(__thiscall*)(void*))FUN_00cdab10)(s3);
    }

    return 1;
}
