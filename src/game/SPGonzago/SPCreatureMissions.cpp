// src/game/SPGonzago/SPCreatureMissions.cpp -- migrated from slice(s) s00c2e420, s01335f70, s00c2f830 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureMissions.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cString.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void __fastcall FUN_00c45140(void*);  // base dtor
extern "C" void  operator_delete(void*);         // 0x00f47380 ??3@YAXPAX@Z
extern "C" void* SP_PropertyManager();           // 0x0067de30
extern "C" void* EA_ResourceMan_GetManager();    // 0x0067dcd0 ::EA::ResourceMan::GetManager
extern "C" void* __stdcall FUN_00401090(void*);  // species profile lookup (setting)
extern "C" void* FUN_004df550(void*);            // species profile lookup
extern "C" void* FUN_0067dd60();
extern "C" int   FUN_004e1c30(void*, int, int);   // 0x004e1c30 cTribeTool::GetTutorialToolPrice
extern "C" int   __fastcall SP_GetPlayerEmpireOrMinus1(void*);  // 0x00b1f9d0 ecx=obj
extern "C" void* SP_NounManager();
extern "C" void* SP_RelationshipManager();
extern "C" void* SP_cTribeModeStrategy_Instance();          // 0x00cd40b0
extern "C" void* FUN_00c0c1a0();
extern "C" char  SP_GetPropertyAsText(int, int, void*);   // 0x006a1360
extern "C" float* __fastcall SP_GetPropertyAsFloat(void*); // 0x0041ea70
extern "C" int*  __fastcall Property_GetInt(void*);        // 0x0041e990
#include <intrin.h>
#include <stdlib.h>
#include <float.h>
#include "SP/cSPTimer.h"
#include "SP/cVarListSerializer.h"

// ---- items of slice s00c2f830 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
typedef unsigned char u8;
template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    T*& AsOutParam() { return mpObject; }
    operator T*() const { return mpObject; }
};
typedef void (__fastcall *VFn0)(void*);
struct ThiscallStub {
    void FUN_00c2ed20(int*, int*);      // 0x00c2ed20 load two AutoRefCount slots
    void FUN_00c2fd20(int);             // 0x00c2fd20 tutorial mission Init
    void FUN_00d00a10(int, int);
    int  FUN_00d00780();
    void FUN_00c8f3a0();
    char FUN_00c905a0();
    void FUN_00c7bbc0(int member, int param);
    void FUN_00c7a7d0(int member);
    void FUN_00ac9480(int* src);
    void* FUN_004df550();
    void FUN_00401090();
    void FUN_00ac9480();
    int  FUN_00d2e490();
};
extern "C" void __fastcall FUN_00c46500_s00c2_f830(void*);  // base ctor
static void ReleaseRef(int* obj)
{
    volatile long* p = (volatile long*)((int)obj + 8);
    (void)_InterlockedExchangeAdd(p, -1);
    long v = _InterlockedExchangeAdd(p, 0);
    if (v < 1)
        _InterlockedExchangeAdd(p, 1);
    else
        _InterlockedExchangeAdd(p, 0);
}
struct PropMgr {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual void GetProperty(int obj, int key, int* out);   // +0x2c
};
struct ResKey { int f0, f1, f2, f3; };
struct ImageRes { void Set(void* img); };         // __thiscall 0x00576650
extern "C" u32*  __fastcall Property_GetUInt(void*);       // 0x0041ea00
#define VT_FIND              0x146b338
#define VT_FIND_2            0x146b328
#define VT_FIND_3            0x146b318
#define VT_SPECIES           0x146b420
#define VT_SPECIES_2         0x146b40c
#define VT_SPECIES_3         0x146b3fc
#define VT_TUTORIAL          0x146b0f8
#define VT_TUTORIAL_2        0x146b0e8
#define VT_TUTORIAL_3        0x146b0d8
#define VT_BASE              0x146aff0
#define VT_BASE_2            0x146afdc
#define VT_BASE_3            0x146afcc
struct cString {
    cString();                                                  // 0x006b5060
    cString(u32 table, u32 instance, const wchar_t* fallback);  // 0x006b5770
    ~cString();                                                 // 0x006b5240
    const wchar_t* c_str();                                     // 0x006b55c0
    u32 mTable; u32 mInstance; u32 pad08; u32 pad0c; u32 pad10;
};
struct WStr {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity;
    void assign(const wchar_t* b, const wchar_t* e);   // 0x00423650
    void append(const wchar_t* s);                     // 0x005c3d90
};
struct Mission {
    char FUN_00c2fc00(int param);
    void FUN_00c2fc10();
    void FUN_00c2fc80();
    int* FUN_00c2fcc0(unsigned int flags);
    void FUN_00c2fd20(int id);
    char FUN_00c2fdd0(int param);
    void FUN_00c2fde0();
    void FUN_00c2fea0();
    int* FUN_00c2fb30();
    int* FUN_00c2ffb0();
    char FUN_00c30090(int param);
    int* FUN_00c300a0(unsigned int flags);
    void FUN_00c30100(int id);
    char FUN_00c30150(int param);
    void FUN_00c301c0(int src);
    void FUN_00c30270(int obj);
    void FUN_00c302b0(char* out);
    void FUN_00c30350(char* out);
    void GetTitleText(char* out);
    void GetBodyText(char* out);
    void GetSummaryText(char* out);
    void GetRewardText(char* out);
    void GetStatusText(char* out);
    void GetSubTitleText(char* out);
    void GetProgressText(char* out);
    void FUN_00c307f0(char* out);
    int* FUN_00c30820(int key);
    void FUN_00c30860(int param);
    void FUN_00c30890();
};
// ---- items of slice s00c2f830 end

// unnamed retail callees and globals that name local stubs (address in the comment)

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __fastcall FUN_00c2fa50(int* self);  // 0x00c2fa50 (stays in the slice: not this object's)

// ---- items of slice s01335f70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char H_692ca0[];                                              // 0x00692ca0  (all records)
extern "C" char J_ae3430_0[], J_ae3450_0[], J_693150_0[], J_695080_0[], J_ae5720_0[];
extern "C" char J_572810_1[], J_572810_2[], J_572810_3[], J_572810_4[];
extern "C" char J_572810_5[], J_572810_6[], J_572810_7[];
extern "C" char J_572840_1[], J_572840_2[], J_572840_3[], J_572840_4[];
extern "C" char J_572840_5[], J_572840_6[], J_572840_7[];
extern "C" char J_693090_1[], J_693090_2[], J_693090_3[], J_693090_4[];
extern "C" char J_693090_5[], J_693090_6[], J_693090_7[];
extern "C" char J_694f00_1[], J_694f00_2[], J_694f00_3[], J_694f00_4[];
extern "C" char J_694f00_5[], J_694f00_6[], J_694f00_7[];
extern "C" char J_b1fbf0_0[], J_b1fbf0_gA[], J_675ca0_gA[];
extern "C" char J_572810_8[], J_572810_9[], J_572840_8[], J_572840_9[];
extern "C" char J_692ff0_8[], J_692ff0_9[], J_694ee0_8[], J_694ee0_9[];
extern "C" char J_b1fbf0_gB[], J_57cde0_gB[];
extern "C" char J_ac8750_10[], J_ac8780_10[], J_693090_10[], J_694fa0_10[];
extern "C" char J_b1fbf0_10[], J_57ce00_10[];
extern "C" char J_572810_11[], J_572810_12[], J_572840_11[], J_572840_12[];
extern "C" char J_692ff0_11[], J_692ff0_12[], J_694ee0_11[], J_694ee0_12[];
struct AttrDesc {
    const char* mName;      // +0x00  member name
    uint32_t    mHash;      // +0x04  name hash
    uint32_t    mOffset;    // +0x08  byte offset of the member
    uint32_t    mPad0c[3];  // +0x0c  (not written by these initializers)
    uint32_t    mZero18;    // +0x18
    uint32_t    mZero1c;    // +0x1c
    void*       mFn20;      // +0x20  DefaultOffset
    void*       mFn24;      // +0x24  writer
    void*       mFn28;      // +0x28  writer2
    void*       mFn2c;      // +0x2c  parser
    void*       mFn30;      // +0x30  parser2
    void*       mFn34;      // +0x34
    void*       mFn38;      // +0x38
};
extern AttrDesc g_tbl_1572618[];   // 0x01572618  table written by $E222
#define REC222(i,nm,h,of,s20,s24,s28,s2c,s30,s34,s38)           \
    d.mName = nm; d.mHash = h; d.mZero18 = 0; d.mZero1c = 0;    \
    d.mFn20 = (void*)s20; d.mFn24 = (void*)s24; d.mFn28 = (void*)s28; \
    d.mFn2c = (void*)s2c; d.mFn30 = (void*)s30;                 \
    d.mFn34 = (void*)s34; d.mFn38 = (void*)s38;                 \
    d.mOffset = of; g_tbl_1572618[i] = d;
// ---- items of slice s01335f70 end

// ---- items of slice s00c2e420 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_00b3d4c0(void*, int, int);
extern "C" void  FUN_00ba3f90(void*);
extern "C" int   FUN_00b6e270(int);
extern "C" int   FUN_00b6e290(int);
extern "C" void  FUN_00c46500(void*);
extern "C" void  FUN_00c449c0();
extern "C" void  SP_cCreatureModeStrategy_NotifyEvent(float);
extern "C" void  SP_cSPTimer_Restart(void*);
extern "C" int   SP_GetPropertyAsKey(int, int, int);
extern "C" void* FUN_00b3d300(int);     // 0x00b3d300 SP::NounManager accessor
extern "C" void* FUN_00b3d2c0(int);     // 0x00b3d2c0 SP::RelationshipManager accessor
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
extern "C" int   FUN_004df550_s00c2_e420(void*);
int  __fastcall FUN_00b1f9d0(void*);    // 0x00b1f9d0 ?GetPlayerEmpireOrMinus1 (this in ECX)
void __fastcall FUN_00d00a10(void*);    // 0x00d00a10 (this in ECX)
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
struct ImageKey { unsigned int mA; unsigned int mB; unsigned int mC; };
// ---- items of slice s00c2e420 end

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

// @ 0x00c2e4e0
void MissionStub::SetSerializer()
{
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

// @ 0x00c2e780
void MissionStub::FUN_00c2e780()
{
    char* p = (char*)this + 0x80;
    FUN_004df550_s00c2_e420(FUN_00401090(p));
}

// @ 0x00c2e7b0
void MissionStub::FUN_00c2e7b0(int param_2)
{
    char* self = (char*)this;
    void* g = ((void*(*)())FUN_00401090)();
    int profile = ((int(__thiscall*)(void*, void*))FUN_004df550_s00c2_e420)(g, self + 0x80);
    if (profile != 0)
    {
        ImageKey key;
        key.mA = *(unsigned int*)(profile + 0x504);
        key.mB = 0x2f7d0004;
        key.mC = *(unsigned int*)(profile + 0x50c);
        CreateImageFromResource2(&key, (void**)param_2, 0, -1, -1);
    }
}

// @ 0x00c2e820
void MissionStub::FUN_00c2e820()
{
    char* p = (char*)this + 0x80;
    FUN_00ba3f90(FUN_00b3d4c0(p, 0, 0));
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
    int profile = ((int(__thiscall*)(void*, void*))FUN_004df550_s00c2_e420)(gobj, self + 0x80);
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

// @ 0x00c2f470
int* __fastcall FUN_00c2f470(int* self) // Simulator::cTribeToTribeMission ctor
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

// @ 0x00c2f830
int* __fastcall cFindMission_ctor(int* self)
{
    FUN_00c46500_s00c2_f830(self);
    self[0x1e] = 0;
    self[0x1f] = 3;
    self[0] = VT_FIND;
    self[1] = VT_FIND_2;
    self[0xd] = VT_FIND_3;
    *(volatile int*)(self + 0x20) = 0;
    return self;
}

// @ 0x00c2f890
void __fastcall FUN_00c2f890(int* self)
{
    int* p = (int*)((int(__fastcall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (p) {
        ((VFn0)(*(void***)p)[0])(p);
        ((VFn0)(*(void***)p)[1])(p);
    }
}

// @ 0x00c2f8c0
int* __fastcall cCreatureSpeciesMission_ctor(int* self)
{
    FUN_00c46500_s00c2_f830(self);
    self[0x1e] = 0;
    self[0x1f] = 3;
    self[0] = VT_SPECIES;
    self[1] = VT_SPECIES_2;
    self[0xd] = VT_SPECIES_3;
    for (int i = 0x20; i < 0x30; ++i)
        self[i] = 0;
    *(u8*)(self + 0x31) = 0;
    self[0x32] = 0;
    return self;
}

// @ 0x00c2f9c0
void __fastcall FUN_00c2f9c0(int* self)
{
    self[0] = VT_SPECIES;
    self[1] = VT_SPECIES_2;
    self[0xd] = VT_SPECIES_3;
    int* p = (int*)self[0x32];
    if (p != 0)
        ReleaseRef(p);
    if ((int*)self[0x2a] != 0) {
        int* q = (int*)self[0x2a];
        ((VFn0)(*(void***)q)[1])(q);
    }
    if ((int*)self[0x29] != 0) {
        int* q = (int*)self[0x29];
        ((VFn0)(*(void***)q)[1])(q);
    }
    self[0] = VT_BASE;
    self[1] = VT_BASE_2;
    self[0xd] = VT_BASE_3;
    FUN_00c45140(self);
}

// @ 0x00c2fa50
void __fastcall FUN_00c2fa50(int* self)
{
    int local8 = 0;
    int local4 = 0;
    ((ThiscallStub*)self)->FUN_00c2ed20(&local8, &local4);
    if (local8 != 0) {
        PropMgr* pm = (PropMgr*)SP_PropertyManager();
        int* slot = (int*)((char*)self + 0xa4);
        if (*slot != 0) {
            int* old = (int*)*slot;
            *slot = 0;
            ((VFn0)(*(void***)old)[1])(old);
        }
        pm->GetProperty(local8, 0x5267de50, slot);
    } else {
        int* slot = (int*)((char*)self + 0xa4);
        if (*slot != 0) {
            int* old = (int*)*slot;
            *slot = 0;
            ((VFn0)(*(void***)old)[1])(old);
        }
    }
    if (local4 != 0) {
        PropMgr* pm = (PropMgr*)SP_PropertyManager();
        int* slot = (int*)((char*)self + 0xa8);
        if (*slot != 0) {
            int* old = (int*)*slot;
            *slot = 0;
            ((VFn0)(*(void***)old)[1])(old);
        }
        pm->GetProperty(local4, 0x5267de50, slot);
    } else {
        int* slot = (int*)((char*)self + 0xa8);
        if (*slot != 0) {
            int* old = (int*)*slot;
            *slot = 0;
            ((VFn0)(*(void***)old)[1])(old);
        }
    }
}

// @ 0x00c2fb30
int* Mission::FUN_00c2fb30()
{
    int* self = (int*)this;
    int edi = ((ThiscallStub*)self)->FUN_00d2e490();
    AutoRefCount<int> local;
    int* esi;
    int r = ((int(__fastcall*)(void*))(*(void***)self)[0x60 / 4])(self);
    if (r == 5 && self[0x28] == 6) {
        esi = (int*)self[0x29];
    } else if (((int(__fastcall*)(void*))(*(void***)self)[0x60 / 4])(self) == 5) {
        esi = (int*)self[0x2a];
    } else {
        int* src;
        if (edi == 0) {
            if (self[0x29] == 0)
                goto fallback;
            src = self + 0x29;
        } else if (edi == 1) {
            if (self[0x2a] == 0)
                goto fallback;
            src = self + 0x2a;
        } else {
        fallback:
            if (self[0x29] != 0)
                src = self + 0x29;
            else if (self[0x2a] != 0)
                src = self + 0x2a;
            else
                return 0;
        }
        ((ThiscallStub*)&local)->FUN_00ac9480(src);
        esi = local.mpObject;
        goto done;
    }
    if (esi == 0)
        return 0;
    ((VFn0)(*(void***)esi)[0])(esi);
done:
    if (esi != 0)
        ((VFn0)(*(void***)esi)[1])(esi);
    return esi;
}

// @ 0x00c2fc00
char Mission::FUN_00c2fc00(int param)
{
    (void)param;
    FUN_00c2fa50((int*)this);
    return 1;
}

// @ 0x00c2fc10
void Mission::FUN_00c2fc10()
{
    int* self = (int*)this;
    int* prof = (int*)((ThiscallStub*)FUN_00401090((char*)self + 0x80))->FUN_004df550();
    if (prof != 0) {
        int b = prof[0x508 / 4];
        void* mgr = FUN_0067dd60();
        ResKey key;
        key.f0 = prof[0x504 / 4];
        key.f1 = 0x2f7d0004;
        key.f2 = prof[0x50c / 4];
        key.f3 = b & 0;   // zero, but keeps the 0x508 load live
        int img = ((int(__thiscall*)(void*, ResKey))(*(void***)mgr)[0x1c / 4])(mgr, key);
        ((ImageRes*)((char*)this + 0xc8))->Set((void*)img);
    }
}

// @ 0x00c2fc80
void Mission::FUN_00c2fc80()
{
    int* self = (int*)this;
    int* p = (int*)self[0x32];
    if (p != 0) {
        self[0x32] = 0;
        ReleaseRef(p);
    }
}

// @ 0x00c2fcc0
int* Mission::FUN_00c2fcc0(unsigned int flags)
{
    int* self = (int*)this;
    self[0] = VT_TUTORIAL;
    self[1] = VT_TUTORIAL_2;
    self[0xd] = VT_TUTORIAL_3;
    _ReadWriteBarrier();
    if ((int*)self[0x20] != 0) {
        int* q = (int*)self[0x20];
        ((VFn0)(*(void***)q)[1])(q);
    }
    self[0] = VT_BASE;
    self[1] = VT_BASE_2;
    self[0xd] = VT_BASE_3;
    FUN_00c45140(self);
    if (flags & 1)
        operator_delete(self);
    return self;
}

// @ 0x00c2fd20
void Mission::FUN_00c2fd20(int id)
{
    int* self = (int*)this;
    self[0x1e] = id;
    PropMgr* pm = (PropMgr*)SP_PropertyManager();
    int* slot = (int*)((char*)self + 0x80);
    if (*slot != 0) {
        int* old = (int*)*slot;
        *slot = 0;
        ((VFn0)(*(void***)old)[1])(old);
    }
    pm->GetProperty(self[0x1e], 0x5267de50, slot);
    int* po = (int*)*slot;
    if (po != 0) {
        int temp;
        char ok = ((char(__thiscall*)(void*, int, int*))(*(void***)po)[0x24 / 4])(po, 0x393f7f7d, &temp);
        if (ok && *(unsigned short*)((char*)temp + 0x12) == 0xd) {
            float* fv = SP_GetPropertyAsFloat((void*)temp);
            *(float*)((char*)self + 0x88) = *fv;
        }
    }
    po = (int*)*slot;
    if (po != 0) {
        int temp;
        char ok = ((char(__thiscall*)(void*, int, int*))(*(void***)po)[0x24 / 4])(po, 0x1ecff7aa, &temp);
        if (ok && *(unsigned short*)((char*)temp + 0x12) == 9) {
            int* iv = Property_GetInt((void*)temp);
            self[0x21] = *iv;
        }
    }
}

// @ 0x00c2fdd0
char Mission::FUN_00c2fdd0(int param)
{
    (void)param;
    int* self = (int*)this;
    ((Mission*)self)->FUN_00c2fd20(self[0x1e]);
    return 1;
}

// @ 0x00c2fde0
void Mission::FUN_00c2fde0()
{
    int* self = (int*)this;
    int* obj = (int*)((int(__fastcall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (obj != 0) {
        ((VFn0)(*(void***)obj)[0])(obj);
        int temp;
        char ok = ((char(__thiscall*)(void*, int, int*))(*(void***)obj)[0x24 / 4])(obj, 0x6b15b5cb, &temp);
        if (ok && *(unsigned short*)((char*)temp + 0x12) == 0xa) {
            u32 val = *Property_GetUInt((void*)temp);
            *(u32*)((char*)*(int**)0x169e3e8 + 0x10) = val;
        }
    }
    u32 m = self[0x21];
    *(u32*)((char*)*(int**)0x169e3e8 + 0x20) = m;
    if (*(int**)0x169b41c != 0) {
        int r = FUN_004e1c30(*(void**)0x1581288, 0xb79e0065, 0x28);
        *(int*)((char*)*(int**)0x169b41c + 0xc) = r;
    }
    if (obj != 0)
        ((VFn0)(*(void***)obj)[1])(obj);
}

// @ 0x00c2fea0
void Mission::FUN_00c2fea0()
{
    int* self = (int*)this;
    int* edi = (int*)self[0x20];
    int ebp = 0x57e2f080;
    int empire = SP_GetPlayerEmpireOrMinus1(SP_NounManager());
    int rel = ((int(__thiscall*)(void*, int))(*(void***)edi)[0x4c / 4])(edi, empire);
    void* rm = SP_RelationshipManager();
    float f = ((float(__thiscall*)(void*, int, int, int))0xd00a10)(rm, rel, empire, 0);
    void* rm2 = SP_RelationshipManager();
    int kind = ((int(__thiscall*)(void*, float))0xd00780)(rm2, f);
    if (kind >= 2)
        ebp = 0x3d61df6c;
    if (!((int(__thiscall*)(void*))0xc8f3a0)((void*)self[0x20])) {
        if (((char(__thiscall*)(void*))0xc905a0)((void*)self[0x20]))
            ebp = 0xf1e0dd24;
        else
            goto notset;
    }
    if (ebp != 0) {
        PropMgr* pm = (PropMgr*)SP_PropertyManager();
        int* slot = (int*)((char*)self + 0x84);
        if (*slot != 0) {
            int* old = (int*)*slot;
            *slot = 0;
            ((VFn0)(*(void***)old)[1])(old);
        }
        pm->GetProperty(ebp, 0x5267de50, slot);
    } else {
notset:
        int* slot = (int*)((char*)self + 0x84);
        if (*slot != 0) {
            int* old = (int*)*slot;
            *slot = 0;
            ((VFn0)(*(void***)old)[1])(old);
        }
    }
    PropMgr* pm2 = (PropMgr*)SP_PropertyManager();
    int* slot2 = (int*)((char*)self + 0x88);
    if (*slot2 != 0) {
        int* old = (int*)*slot2;
        *slot2 = 0;
        ((VFn0)(*(void***)old)[1])(old);
    }
    pm2->GetProperty(0xf1e0dd24, 0x5267de50, slot2);
}

// @ 0x00c2ffb0
int* Mission::FUN_00c2ffb0()
{
    int* self = (int*)this;
    int* strat = (int*)SP_cTribeModeStrategy_Instance();
    int ebx = strat[0x390 / 4];
    int* p = (int*)self[0x20];
    AutoRefCount<int> local;
    int empire = SP_GetPlayerEmpireOrMinus1(SP_NounManager());
    int rel = ((int(__thiscall*)(void*, int))(*(void***)p)[0x4c / 4])(p, empire);
    void* rm = SP_RelationshipManager();
    float f = ((float(__thiscall*)(void*, int, int, int))0xd00a10)(rm, rel, empire, 0);
    void* rm2 = SP_RelationshipManager();
    int kind = ((int(__thiscall*)(void*, float))0xd00780)(rm2, f);
    int* esi;
    if (((int(__thiscall*)(void*))(*(void***)self)[0x60 / 4])(self) == 5 && kind == 4) {
        esi = (int*)self[0x21];
    } else if (((int(__thiscall*)(void*))(*(void***)self)[0x60 / 4])(self) == 5) {
        esi = (int*)self[0x22];
    } else if (ebx == 0) {
        esi = (int*)self[0x21];
    } else if (ebx == 1) {
        ((ThiscallStub*)&local)->FUN_00ac9480((int*)((char*)self + 0x88));
        esi = local.mpObject;
    } else {
        return 0;
    }
    if (esi == 0)
        return 0;
    ((VFn0)(*(void***)esi)[0])(esi);
    if (esi != 0)
        ((VFn0)(*(void***)esi)[1])(esi);
    return esi;
}

// @ 0x00c30090
char Mission::FUN_00c30090(int param)
{
    (void)param;
    ((Mission*)this)->FUN_00c2fea0();
    return 1;
}

// @ 0x00c300a0
int* Mission::FUN_00c300a0(unsigned int flags)
{
    int* self = (int*)this;
    self[0] = VT_FIND;
    self[1] = VT_FIND_2;
    self[0xd] = VT_FIND_3;
    _ReadWriteBarrier();
    if ((int*)self[0x20] != 0) {
        int* q = (int*)self[0x20];
        ((VFn0)(*(void***)q)[1])(q);
    }
    self[0] = VT_BASE;
    self[1] = VT_BASE_2;
    self[0xd] = VT_BASE_3;
    FUN_00c45140(self);
    if (flags & 1)
        operator_delete(self);
    return self;
}

// @ 0x00c30100
void Mission::FUN_00c30100(int id)
{
    int* self = (int*)this;
    self[0x1e] = id;
    PropMgr* pm = (PropMgr*)SP_PropertyManager();
    int* slot = (int*)((char*)self + 0x80);
    if (*slot != 0) {
        int* old = (int*)*slot;
        *slot = 0;
        ((VFn0)(*(void***)old)[1])(old);
    }
    pm->GetProperty(self[0x1e], 0x5267de50, slot);
}

// @ 0x00c30150
char Mission::FUN_00c30150(int param)
{
    (void)param;
    int* self = (int*)this;
    PropMgr* pm = (PropMgr*)SP_PropertyManager();
    int* slot = (int*)((char*)self + 0x80);
    if (*slot != 0) {
        int* old = (int*)*slot;
        *slot = 0;
        ((VFn0)(*(void***)old)[1])(old);
    }
    pm->GetProperty(self[0x1e], 0x5267de50, slot);
    return 1;
}

// @ 0x00c301c0
void Mission::FUN_00c301c0(int src)
{
    int* self = (int*)this;
    int* s = (int*)src;
    self[0x20] = s[0xb28 / 4];
    self[0x21] = s[0xb2c / 4];
    self[0x22] = s[0xb30 / 4];
    int* o = (int*)FUN_00c0c1a0();
    if (o != 0) {
        self[0x2b] = o[0x3fc / 4];
        self[0x2c] = o[0x400 / 4];
        self[0x2d] = o[0x404 / 4];
        self[0x2e] = o[0x408 / 4];
        self[0x2f] = o[0x40c / 4];
        self[0x25] = o[0x418 / 4];
        self[0x26] = o[0x420 / 4];
        self[0x30] = o[0x330 / 4];
        *(u8*)((char*)self + 0xc4) = *(u8*)((char*)o + 0x389);
    }
    FUN_00c2fa50(self);
}

// @ 0x00c30270
void Mission::FUN_00c30270(int obj)
{
    int* self = (int*)this;
    int* old = (int*)self[0x20];
    if (obj != (int)old) {
        if (obj != 0)
            ((VFn0)(*(void***)obj)[0])((void*)obj);
        self[0x20] = obj;
        if (old != 0)
            ((VFn0)(*(void***)old)[1])(old);
    }
    ((Mission*)self)->FUN_00c2fea0();
}

// @ 0x00c302b0
void Mission::FUN_00c302b0(char* out)
{
    int* self = (int*)this;
    int* obj = (int*)((int(__fastcall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (obj == 0)
        return;
    cString cs;
    char ok = SP_GetPropertyAsText((int)obj, 0x15e95780, &cs);
    if (!ok) {
        ((void(__thiscall*)(void*, char*))(*(void***)self)[0x8c / 4])(self, out);
        return;
    }
    const wchar_t* t = cs.c_str();
    const wchar_t* e = t;
    while (*e) e++;
    ((WStr*)out)->assign(t, t + (e - t));
}

// @ 0x00c30350
void Mission::FUN_00c30350(char* out)
{
    int* self = (int*)this;
    int* obj = (int*)((int(__fastcall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (obj == 0)
        return;
    cString cs;
    char ok = SP_GetPropertyAsText((int)obj, 0xcbbe0580, &cs);
    if (!ok) {
        ((void(__thiscall*)(void*, char*))(*(void***)self)[0x98 / 4])(self, out);
        return;
    }
    const wchar_t* t = cs.c_str();
    const wchar_t* e = t;
    while (*e) e++;
    ((WStr*)out)->assign(t, t + (e - t));
}

// @ 0x00c303f0
void Mission::GetTitleText(char* out)
{
    int* self = (int*)this;
    int* obj = (int*)((int(__fastcall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (obj == 0)
        return;
    cString cs;
    SP_GetPropertyAsText((int)obj, 0xa7696d50, &cs);
    const wchar_t* t = cs.c_str();
    const wchar_t* e = t;
    while (*e) e++;
    ((WStr*)out)->assign(t, t + (e - t));
}

// @ 0x00c30460
void Mission::GetBodyText(char* out)
{
    int* self = (int*)this;
    int* obj = (int*)((int(__fastcall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (obj == 0)
        return;
    cString cs;
    SP_GetPropertyAsText((int)obj, 0xb6496990, &cs);
    const wchar_t* t = cs.c_str();
    const wchar_t* e = t;
    while (*e) e++;
    ((WStr*)out)->assign(t, t + (e - t));
}

// @ 0x00c304d0
void Mission::GetSummaryText(char* out)
{
    int* self = (int*)this;
    int* obj = (int*)((int(__fastcall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (obj == 0)
        return;
    cString cs;
    SP_GetPropertyAsText((int)obj, 0xfc89a37e, &cs);
    const wchar_t* t = cs.c_str();
    const wchar_t* e = t;
    while (*e) e++;
    ((WStr*)out)->assign(t, t + (e - t));
}

// @ 0x00c30540
void Mission::GetRewardText(char* out)
{
    int* self = (int*)this;
    int* obj = (int*)((int(__fastcall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (obj == 0)
        return;
    cString cs;
    SP_GetPropertyAsText((int)obj, 0xadf78285, &cs);
    const wchar_t* t = cs.c_str();
    const wchar_t* e = t;
    while (*e) e++;
    ((WStr*)out)->assign(t, t + (e - t));
}

// @ 0x00c305b0
void Mission::GetStatusText(char* out)
{
    int* self = (int*)this;
    int* obj = (int*)((int(__fastcall*)(void*))(*(void***)self)[0xc0 / 4])(self);
    if (obj == 0)
        return;
    int kind = self[0x1f];
    switch (kind) {
    case 3: {
        cString cs;
        SP_GetPropertyAsText((int)obj, 0x34255d1e, &cs);
        ((WStr*)out)->append(cs.c_str());
        break;
    }
    case 5: {
        cString cs;
        SP_GetPropertyAsText((int)obj, 0xd2f7cd25, &cs);
        ((WStr*)out)->append(cs.c_str());
        break;
    }
    }
}

// @ 0x00c30630
void Mission::GetSubTitleText(char* out)
{
    int* self = (int*)this;
    void* prof = ((ThiscallStub*)FUN_00401090((char*)self + 0x80))->FUN_004df550();
    if (prof == 0)
        return;
    int* p = (int*)prof;
    int key = p[0x504 / 4];
    int key2 = p[0x508 / 4];
    int key3 = p[0x50c / 4];
    int holder = 0;
    void* mgr = EA_ResourceMan_GetManager();
    if (holder != 0) {
        int* o = (int*)holder;
        holder = 0;
        ((VFn0)(*(void***)o)[1])(o);
    }
    char ok = ((char(__thiscall*)(void*, int*, int*, int, int))(*(void***)mgr)[0xc / 4])(mgr, &key, &holder, 0, 0);
    if (ok) {
        if (holder == 0)
            return;
        int* o = (int*)holder;
        int sub = ((int(__thiscall*)(void*, int))(*(void***)o)[0xc / 4])(o, 0x30bdee3);
        if (sub != 0) {
            int r = ((int(__fastcall*)(void*))0x550880)((void*)sub);
            *(int*)(*(int**)0x169e3e8 + 0x28) = r;
            cString cs(0xad56080c, 0xb3daed77, L"~Unknown");
            const wchar_t* t = cs.c_str();
            ((WStr*)out)->append(t);
            cs.~cString();
        }
    } else {
        cString cs(0xad56080c, 0x73db4258, L"~Unknown");
        const wchar_t* t = cs.c_str();
        const wchar_t* e = t;
        while (*e) e++;
        ((WStr*)out)->assign(t, t + (e - t));
        cs.~cString();
    }
    if (holder != 0) {
        int* o = (int*)holder;
        ((VFn0)(*(void***)o)[1])(o);
    }
}

// @ 0x00c30780
void Mission::GetProgressText(char* out)
{
    int* self = (int*)this;
    unsigned int a = ((unsigned int(__fastcall*)(void*))(*(void***)self)[0x58 / 4])(self);
    unsigned int b = ((unsigned int(__fastcall*)(void*))(*(void***)self)[0x54 / 4])(self);
    if (b >= a)
        return;
    cString cs(0xad56080c, 0x53b644df, L"~Goal");
    const wchar_t* t = cs.c_str();
    const wchar_t* e = t;
    while (*e) e++;
    ((WStr*)out)->assign(t, t + (e - t));
}

// @ 0x00c307f0
void Mission::FUN_00c307f0(char* out)
{
    int* self = (int*)this;
    int n = ((int(__fastcall*)(void*))(*(void***)self)[0xa4 / 4])(self);
    if (n > 0)
        ((Mission*)self)->GetRewardText(out);
}

// @ 0x013366e0
void FUN_013366e0(void)
{
    AttrDesc d;
    REC222(0,  "mSpeciesKey",                0x540ff31f, 0x80,
            H_692ca0, J_ae3430_0, J_ae3450_0, J_693150_0, J_695080_0, J_b1fbf0_0, J_ae5720_0)
    REC222(1,  "mNumBefriended",             0x140ff31e, 0x8c,
            H_692ca0, J_572810_1, J_572840_1, J_693090_1, J_694f00_1, J_b1fbf0_gA, J_675ca0_gA)
    REC222(2,  "mNumKilled",                 0x140ff320, 0x90,
            H_692ca0, J_572810_2, J_572840_2, J_693090_2, J_694f00_2, J_b1fbf0_gA, J_675ca0_gA)
    REC222(3,  "mNumToKillForFearful",       0x940ff321, 0xac,
            H_692ca0, J_572810_3, J_572840_3, J_693090_3, J_694f00_3, J_b1fbf0_gA, J_675ca0_gA)
    REC222(4,  "mNumToKillForExtinction",    0xd40ff322, 0xb0,
            H_692ca0, J_572810_4, J_572840_4, J_693090_4, J_694f00_4, J_b1fbf0_gA, J_675ca0_gA)
    REC222(5,  "mNumToImpressForCurious",    0xf42532e2, 0xb4,
            H_692ca0, J_572810_5, J_572840_5, J_693090_5, J_694f00_5, J_b1fbf0_gA, J_675ca0_gA)
    REC222(6,  "mNumToImpressForFriendly",   0x942532e3, 0xb8,
            H_692ca0, J_572810_6, J_572840_6, J_693090_6, J_694f00_6, J_b1fbf0_gA, J_675ca0_gA)
    REC222(7,  "mNumToImpressForBestFriends",0x942532e4, 0xbc,
            H_692ca0, J_572810_7, J_572840_7, J_693090_7, J_694f00_7, J_b1fbf0_gA, J_675ca0_gA)
    REC222(8,  "mSocialEvoPointReward",      0xb4111890, 0x94,
            H_692ca0, J_572810_8, J_572840_8, J_692ff0_8, J_694ee0_8, J_b1fbf0_gB, J_57cde0_gB)
    REC222(9,  "mCombatEvoPointReward",      0x54113b0f, 0x98,
            H_692ca0, J_572810_9, J_572840_9, J_692ff0_9, J_694ee0_9, J_b1fbf0_gB, J_57cde0_gB)
    REC222(10, "mbMiniBoss",                 0xb52f62df, 0xc4,
            H_692ca0, J_ac8750_10, J_ac8780_10, J_693090_10, J_694fa0_10, J_b1fbf0_10, J_57ce00_10)
    REC222(11, "mFoodChainLevel",            0x61dc170, 0xc0,
            H_692ca0, J_572810_11, J_572840_11, J_692ff0_11, J_694ee0_11, J_b1fbf0_gB, J_57cde0_gB)
    REC222(12, "mRelationship",              0x943c7a58, 0xa0,
            H_692ca0, J_572810_12, J_572840_12, J_692ff0_12, J_694ee0_12, J_b1fbf0_gB, J_57cde0_gB)
}
