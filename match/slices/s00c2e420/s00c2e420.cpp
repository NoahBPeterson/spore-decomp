// Spore retail 00c2e420..00c2f690 -- creature/tribe mission classes.
// Small accessors/thunks are reconstructed exactly; the large Read/Update bodies are
// best-effort skeletons (see partial.txt).

#include "types.h"

typedef unsigned int uint32;
typedef unsigned int size_type;

extern "C" void* FUN_00401090(void*);
extern "C" int   FUN_004df550(void*);
extern "C" void* FUN_00b3d4c0(void*, int, int);
extern "C" void  FUN_00ba3f90(void*);
extern "C" void  FUN_00b6e270(int);
extern "C" void  FUN_00b6e290(int);
extern "C" void  FUN_00c46500(void*);
extern "C" void  FUN_00c45140(void*);
extern "C" void  SP_cCreatureModeStrategy_NotifyEvent(float);
extern "C" int   SP_cSPTimer_IsRunning(void*);
extern "C" void  SP_cSPTimer_Restart(void*);
extern "C" int   SP_GetPropertyAsKey(int, int, int);

typedef void (__fastcall *VFn)(void*);

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
};

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
    if (!SP_cSPTimer_IsRunning(self + 0x38) && *(int*)(self + 0x7c) == 5)
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
        (*(Fn*)p[0])(p);
    }
    self[0] = 0x146aff0;
    self[1] = 0x146afdc;
    self[0xd] = 0x146afcc;
    FUN_00c45140(self);
}

// ===========================================================================
// Large Read/Update/serialization members: best-effort skeletons.
// ===========================================================================

// @ 0x00c2e420
unsigned char __fastcall FUN_00c2e420(int* self, int param)
{
    (void)self; (void)param;
    return 0;
}

// @ 0x00c2e520
void __fastcall FUN_00c2e520(int* self, int param)
{
    (void)self; (void)param;
}

// @ 0x00c2e5a0
void __fastcall FUN_00c2e5a0(int* self, int param)
{
    (void)self; (void)param;
}

// @ 0x00c2e6c0
unsigned char __fastcall FUN_00c2e6c0(int* self, int param)
{
    (void)self; (void)param;
    return 0;
}

// @ 0x00c2e7b0
void __fastcall FUN_00c2e7b0(int* self, int param)
{
    (void)self; (void)param;
}

// @ 0x00c2e8c0
unsigned char __fastcall FUN_00c2e8c0(int* self, int param)
{
    (void)self; (void)param;
    return 0;
}

// @ 0x00c2eaa0
unsigned char __fastcall FUN_00c2eaa0(int* self, int param)
{
    (void)self; (void)param;
    return 0;
}

// @ 0x00c2ec30
void __fastcall FUN_00c2ec30(int* self, int param)
{
    (void)self; (void)param;
}

// @ 0x00c2ec80
void __fastcall FUN_00c2ec80(int* self, int param)
{
    (void)self; (void)param;
}

// @ 0x00c2ecd0
int __fastcall FUN_00c2ecd0(int* self)
{
    (void)self;
    return 0;
}

// @ 0x00c2ed20
void __fastcall FUN_00c2ed20(int* self, int param)
{
    (void)self; (void)param;
}

// @ 0x00c2f090
void __fastcall FUN_00c2f090(int* self, int param)
{
    (void)self; (void)param;
}

// @ 0x00c2f190
void __fastcall FUN_00c2f190(int* self, int param)
{
    (void)self; (void)param;
}

// @ 0x00c2f1f0
void __fastcall FUN_00c2f1f0(int* self, int param)
{
    (void)self; (void)param;
}

// @ 0x00c2f240
int __fastcall FUN_00c2f240(int* self)
{
    (void)self;
    return 0;
}

// @ 0x00c2f470
int* __fastcall FUN_00c2f470(int* self)
{
    self[0] = 0x146b238;
    return self;
}

// @ 0x00c2f520
void __fastcall FUN_00c2f520(int* self, int param)
{
    (void)self; (void)param;
}

// @ 0x00c2f590
void __fastcall FUN_00c2f590(int* self, int param)
{
    (void)self; (void)param;
}

// @ 0x00c2f5f0
void __fastcall FUN_00c2f5f0(int* self, int param)
{
    (void)self; (void)param;
}

// @ 0x00c2f650
void __fastcall FUN_00c2f650(int* self, int param)
{
    (void)self; (void)param;
}

// @ 0x00c2f690
void __fastcall FUN_00c2f690(int* self, int param)
{
    (void)self; (void)param;
}
