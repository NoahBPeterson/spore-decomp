// Slice s00ca6630: gameplay/object helpers.
//
// Targets:
//   00ca6db0  update a cVehicle-like object's combat/status flags
//   00ca6f20  lazily initialised global object list A
//   00ca6f70  block-list pop-front
//   00ca6ff0  cVehicle::UpdateCombatStatus (timed messages / UI effects)
//   00ca71d0  lazily initialised global object list B
//   00ca7250  assign a C string into an eastl::basic_string at +0xd14
//   00ca72a0  cPathAndTurnLocomotion::Execute
//   00ca7520  model-key / profile change handler
//
// Global tables and singleton cells live at fixed image addresses; naming them
// with macros keeps the source readable while preserving absolute addressing.
#include <stddef.h>

// ---------------------------------------------------------------------------
// External routines.  Member declarations are used for __thiscall targets so
// that the compiler emits an `ecx = this` direct call, exactly as the original
// does; the linker resolves the callee by its mangled name.
// ---------------------------------------------------------------------------
struct ExtObj {
    void __thiscall ClearCreature();                    // 0x00ca0430
    void __thiscall SetModelKey(void* key);             // 0x00c88810
    void __thiscall ResetModel();                       // 0x00ca42c0
    void __thiscall ResetCreature();                    // 0x00ca3f20
    void* __thiscall GetProfile(void* key);             // 0x004df550
    void __thiscall SetByte(unsigned char value);       // 0x00bfc470
    void __thiscall SetFlags(int, int, float, int);     // 0x00bc97f0
    void* __thiscall Get74(void* self);                 // 0x00f3f950
    void* __thiscall GetData();                         // 0x00b18530
    char __thiscall Test(int offset);                   // 0x00f25080
    void __thiscall SetA(void* value);                  // 0x00ca33b0
    void __thiscall KillEffect(void* value);            // not used directly
};

struct EastlString {
    void __thiscall Assign(const char* first, const char* last); // 0x00454cb0
};

extern "C" int __cdecl atexit(void (__cdecl*)(void));
void __cdecl FUN_013c4400(void);
void __cdecl FUN_013c4420(void);

void __cdecl FUN_00f47380(void*);                       // operator delete

void* __cdecl FUN_00401090(void);                       // editor species manager
void* __cdecl FUN_00a206f0(void);                       // EA::Audio::GetSystemAT
void* __cdecl FUN_00b5b800(void);                       // SP::GetCurrentGameMode
unsigned __cdecl FUN_00435e90(void);                    // GetRecorderState
void __cdecl FUN_00435ed0(void* space, unsigned value); // SP::cSPUISpace::KillSetiEffects
void __cdecl FUN_00421cf0(void* message);               // SlotMessage::Destruct
void __cdecl FUN_00d9a290(int a, void* b, void* c, void* d);
void* __cdecl FUN_00883860(void);                        // EA::Messaging::GetServer
void __cdecl FUN_00afba10(void);
void __cdecl FUN_00af9cf0(void* a, float b, void* c, void* d);
void __cdecl FUN_00afef10(int a, float b);
void* __cdecl FUN_00b25f40(void* a);
void* __cdecl FUN_00bef6c0(void);
void __cdecl FUN_00ac9310(void* a, void* b, unsigned c);
void* __cdecl FUN_00bdca30(void* a, int b);
void __cdecl FUN_00afbad0(void* a);
char __cdecl FUN_00c9e8e0(int a, void* b);

struct Vec3 { float x, y, z; };

struct Timer {
    unsigned __int64 __thiscall GetElapsedTime();        // 0x00bc3190
    void __thiscall Restart();                           // 0x00bc3130
};

struct PlanetModel {
    unsigned __thiscall GetAverageRadius(Vec3* p);       // 0x00c... 
};
void* __cdecl GetPlanetModel(void);                      // SP::PlanetModel

// ---------------------------------------------------------------------------
// Global cells.
// ---------------------------------------------------------------------------
extern unsigned int g_list_a_flags;     // 0x01699adc
extern int g_list_a_data[3];            // 0x01699ac8
extern int g_list_a_alt;                // 0x0169a104

extern unsigned int g_list_b_flags;     // 0x01699af8
extern void* g_list_b_cell;             // 0x01699ae0
extern void* g_list_b_zero;             // 0x01699af0
extern void* g_list_b_result;           // 0x01699af4

#define G_GAME_DATA      (*(int*)0x016c7aa4)

// ---------------------------------------------------------------------------
// 00ca6f20
// ---------------------------------------------------------------------------
// __fastcall, ecx = this.  Returns one of two singleton list heads.  The first
// use of the primary list registers its atexit destructor exactly once.
// @ 0x00ca6f20
int* __fastcall FUN_00ca6f20(char* self)
{
    int zero = 0;

    if (*(int*)(self + 0x550) != zero) {
        int one = 1;
        if ((g_list_a_flags & one) == 0) {
            g_list_a_flags |= one;
            g_list_a_data[0] = zero;
            g_list_a_data[1] = zero;
            g_list_a_data[2] = zero;
            atexit(FUN_013c4400);
        }
        return g_list_a_data;
    }
    return &g_list_a_alt;
}

// ---------------------------------------------------------------------------
// 00ca6f70
// ---------------------------------------------------------------------------
// A simple block list: mpCur walks a block of 0x100 dwords; when it reaches the
// end the next block header is read from mpBlockPtr and the old block deleted.
struct BlockList {
    char pad00[0xb34];
    unsigned* mpCur;        // +0xb34
    int* mpBlock;           // +0xb38
    unsigned* mpEnd;        // +0xb3c
    int* mpBlockPtr;        // +0xb40
    unsigned* mpLimit;      // +0xb44
};

// @ 0x00ca6f70
unsigned __fastcall FUN_00ca6f70(BlockList* self)
{
    unsigned* cur = self->mpCur;
    if (cur == self->mpLimit)
        return 0;

    unsigned value = *cur;
    if (cur + 1 != self->mpEnd) {
        self->mpCur = cur + 1;
        return value;
    }

    if (self->mpBlock != 0)
        FUN_00f47380(self->mpBlock);

    int* next = self->mpBlockPtr + 1;
    self->mpBlockPtr = next;
    int block = *next;
    self->mpBlock = (int*)block;
    self->mpEnd = (unsigned*)(block + 0x100);
    self->mpCur = (unsigned*)block;
    return value;
}

// ---------------------------------------------------------------------------
// 00ca71d0
// ---------------------------------------------------------------------------
// Same lazy-destructor pattern as 00ca6f20, then a small container check.
struct ObjectAt508 {
    void** mpVtbl;          // +0x00
};

struct Object71d0 {
    char pad00[0x508];
    ObjectAt508 mObject;    // +0x508
    char pad50c[0xb68 - 0x50c];
    void* mpCur;            // +0xb68
    void* mpEnd;            // +0xb6c
};

// @ 0x00ca71d0
void* __fastcall FUN_00ca71d0(Object71d0* self)
{
    int one = 1;
    if ((g_list_b_flags & one) == 0) {
        g_list_b_flags |= one;
        g_list_b_cell = 0;
        atexit(FUN_013c4420);
    }

    void* cur = self->mpCur;
    if (cur != self->mpEnd)
        return cur;

    void* old = g_list_b_cell;
    if (old != 0) {
        g_list_b_cell = 0;
        void** vtbl = *(void***)old;
        ((void (__thiscall*)(void*))vtbl[1])(old);
    }

    g_list_b_zero = 0;
    void* result = ((void* (__thiscall*)(void*))
                    (*(void***)((char*)self + 0x508))[4])((char*)self + 0x508);
    g_list_b_result = result;
    return &g_list_b_cell;
}

// ---------------------------------------------------------------------------
// 00ca7250
// ---------------------------------------------------------------------------
// __thiscall, one stack argument (ret 4).  Assigns either the empty string or
// the [param, param + strlen(param)) range into the eastl string at +0xd14.
struct StringOwner {
    char pad00[0xd14];
    char mString;           // +0xd14
    void __thiscall FUN_00ca7250(char* text);
};

// @ 0x00ca7250
void StringOwner::FUN_00ca7250(char* text)
{
    if (text == 0) {
        ((EastlString*)&mString)->Assign((const char*)0x013ec47c,
                                         (const char*)0x013ec47c);
        return;
    }

    char* next = text;
    char* end;
    do {
        end = next;
        next = end + 1;
    } while (*end != 0);

    ((EastlString*)&mString)->Assign(text, end);
}

// ---------------------------------------------------------------------------
// 00ca7520
// ---------------------------------------------------------------------------
// __thiscall, one stack argument (ret 4).  The magic in key->mMagic selects
// between clearing the model key and looking a species profile up.
struct ModelKey {
    char pad00[4];
    unsigned mMagic;        // +0x04
};

struct SpatialObject {
    char pad00[0xcd0];
    void* mpProfile;        // +0xcd0
    void __thiscall FUN_00ca7520(ModelKey* key);
};

struct EnclosingObject {
    char pad00[0x34];
    SpatialObject mSpatial; // +0x34
};

// @ 0x00ca7520
void SpatialObject::FUN_00ca7520(ModelKey* key)
{
    switch (key->mMagic) {
    case 0x24682294:
    case 0x476a98c7:
        ((ExtObj*)((char*)this - 0x34))->ClearCreature();
        mpProfile = 0;
        ((ExtObj*)this)->SetModelKey(key);
        return;

    case 0x2b978c46: {
        void* profile = ((ExtObj*)FUN_00401090())->GetProfile(key);
        mpProfile = profile;
        if (profile == 0)
            return;
        SpatialObject* base = (SpatialObject*)((char*)this - 0x34);
        ((ExtObj*)base)->ClearCreature();
        ((ExtObj*)base)->ResetModel();
        ((ExtObj*)base)->ResetCreature();
        return;
    }
    }
}

// ---------------------------------------------------------------------------
// 00ca6db0
// ---------------------------------------------------------------------------
// Per-frame vehicle/status update: notify the HUD, probe the object's control
// mode, select the bit in the shared flag word, then run the post-update hook.
struct Self6db0 {
    char pad00[0x18];
    void* mp18;             // +0x18
    char pad1c[0x34 - 0x1c];
    ObjectAt508 mSub34;     // +0x34
    char pad38[0x2a0 - 0x38];
    float m2a0;             // +0x2a0
    char pad2a4[0xaf0 - 0x2a4];
    int* mpAf0;             // +0xaf0
    char padAf4[0xafc - 0xaf4];
    unsigned char mAfC;     // +0xafc
    char padAfD[0xb00 - 0xafd];
    void* mpB00;            // +0xb00
};

// @ 0x00ca6db0
void __fastcall FUN_00ca6db0(Self6db0* self)
{
    int* game = (int*)G_GAME_DATA;
    int* settings = *(int**)((char*)game + 0x78);
    int count = *(int*)((char*)settings + 0xb8);

    ObjectAt508* sub = &self->mSub34;
    void* result = ((void* (__thiscall*)(ObjectAt508*))sub->mpVtbl[0x2c / 4])(sub);
    FUN_00d9a290(count, self->mp18, result, self->mpB00);

    char* status = (char*)((ExtObj*)(*(int**)((char*)game + 0x74)))->Get74(self);
    ((ExtObj*)((char*)self + 0x508))->SetByte((unsigned char)status[1]);

    count = *(int*)((char*)(*(int**)((char*)game + 0x78)) + 0xb8);
    if (count > 0) {
        char* data = (char*)((ExtObj*)self)->GetData();
        if (((ExtObj*)status)->Test(count * 0x4e0 - 0x4e0 + *(int*)(data + 0x70)))
            ((ExtObj*)((char*)self->mpAf0 + 8))->SetFlags(1, 0,
                                                         *(float*)0x014749a8, 0);
    }

    unsigned* flags = (unsigned*)((char*)self->mpAf0 + 0x5fc);
    *flags &= 0xffff83ff;
    switch (*(int*)(status + 0x4ac)) {
    case 1: *flags |= 0x2000; break;
    case 2: *flags |= 0x0800; break;
    case 3: *flags |= 0x1000; break;
    case 4: *flags |= 0x4000; break;
    case 5: *flags |= 0x0400; break;
    }

    ((void (__thiscall*)(ObjectAt508*))sub->mpVtbl[0xf4 / 4])(sub);
    self->m2a0 = *(float*)(status + 0x484);
    result = ((void* (__thiscall*)(ObjectAt508*))sub->mpVtbl[0x2c / 4])(sub);
    ((ExtObj*)self)->SetA(result);
    self->mAfC = 1;
}

// ---------------------------------------------------------------------------
// 00ca6ff0
// ---------------------------------------------------------------------------
// cVehicle::UpdateCombatStatus.  A one-second timer emits a HUD message; the
// current game mode then decides between two ten-second UI-effect timers.
struct MessageBasicRC5 {
    void* mpVtbl;           // +0x00
    volatile int mRefCount; // +0x04
    void* mData0;           // +0x08
    char pad0c[0x10 - 0x0c];
    unsigned mData1;        // +0x10
    char pad14[0x30 - 0x14];
    unsigned mId;           // +0x30
    char pad34[0x38 - 0x34];
    int mRCFlags;           // +0x38
    char pad3c[4];
};

struct Self6ff0 {
    char pad34[0x34];
    ObjectAt508 mSub34;     // +0x34
    char pad38[0xaf0 - 0x38];
    int* mpAf0;             // +0xaf0
    char padAf4[0xb20 - 0xaf4];
    int mB20;               // +0xb20
    char padB24[0xbcc - 0xb24];
    unsigned char mBcc;     // +0xbcc
    char padBcd[0xc88 - 0xbcd];
    Timer mTimer1;          // +0xc88
    char padC9c[0xca8 - 0xc9c];
    Timer mTimer2;          // +0xca8
    void __thiscall FUN_00ca6ff0(void* arg);
};

// @ 0x00ca6ff0
void Self6ff0::FUN_00ca6ff0(void* arg)
{
    if (mTimer1.GetElapsedTime() > 1000) {
        MessageBasicRC5 msg;
        msg.mpVtbl = (void*)0x013eb90c;
        msg.mRefCount = 0;
        msg.mpVtbl = (void*)0x013eb844;
        msg.mRCFlags = 0;
        msg.mId = 0x354b9e8;
        msg.mData0 = this;
        msg.mData1 = 0xffff0000;

        void* server = FUN_00883860();
        ((void (__thiscall*)(void*, unsigned, MessageBasicRC5*, int))
         (*(void***)server)[0x14 / 4])(server, msg.mId, &msg, 0);

        mTimer1.Restart();
        mBcc = 1;
        FUN_00421cf0(&msg);
    }

    if (FUN_00b5b800() == (void*)0x01654c10) {
        if ((*(unsigned*)((char*)mpAf0 + 0x5fc) & 0x3000) == 0)
            return;
        if (mTimer2.GetElapsedTime() <= 10000)
            return;

        mTimer2.Restart();
        unsigned audio = 0;
        void* sys = FUN_00a206f0();
        if (sys)
            audio = ((unsigned (__thiscall*)(void*))(*(void***)sys)[0x20 / 4])(sys);
        FUN_00435ed0(((void**)0x01474b10)[mB20], audio);
        return;
    }

    char active = ((char (__thiscall*)(ObjectAt508*))
                   mSub34.mpVtbl[0x58 / 4])(&mSub34);
    if (!active)
        return;
    if (mTimer2.GetElapsedTime() <= 60000)
        return;

    mTimer2.Restart();
    if (arg != 0) {
        void* obj = ((void* (__thiscall*)(void*, void*))
                     (*(void***)arg)[0x5c / 4])(arg, (void*)0x0137e8e0);
        if (obj != 0 && *(int*)((char*)obj + 0xb20) == 1) {
            unsigned state = FUN_00435e90();
            FUN_00435ed0(((void**)0x01474b04)[mB20], state);
            return;
        }
    }

    unsigned audio = 0;
    void* sys = FUN_00a206f0();
    if (sys)
        audio = ((unsigned (__thiscall*)(void*))(*(void***)sys)[0x20 / 4])(sys);
    FUN_00435ed0(((void**)0x01474af8)[mB20], audio);
}

// ---------------------------------------------------------------------------
// 00ca72a0
// ---------------------------------------------------------------------------
// cPathAndTurnLocomotion::Execute.  Samples the path, filters points by
// planet-model region flags, then pushes the chosen target to the action
// circle.  This is a readable reconstruction of the original control flow.
struct Self72a0 {
    char pad34[0x34];
    ObjectAt508 mSub34;     // +0x34
    char pad38[0x508 - 0x38];
    void* mp508;            // +0x508
    char pad50c[0xb1c - 0x50c];
    int mB1c;               // +0xb1c
};

// @ 0x00ca72a0
void __fastcall FUN_00ca72a0(Self72a0* self)
{
    ObjectAt508* sub = &self->mSub34;
    float* p = ((float* (__thiscall*)(ObjectAt508*))
                sub->mpVtbl[0x2c / 4])(sub);
    Vec3 here = { p[0], p[1], p[2] };

    if (FUN_00c9e8e0(self->mB1c, &here))
        return;

    FUN_00afba10();
    void* path = 0;
    void* ctx = ((void* (__thiscall*)(ObjectAt508*, void*, int))
                 sub->mpVtbl[0x5c / 4])(sub, &path, 0);
    FUN_00af9cf0(&path, 0x43000000, ctx, &path);

    float radius = ((float (__thiscall*)(ObjectAt508*))
                    sub->mpVtbl[0x70 / 4])(sub);
    FUN_00afef10(0, radius);

    void* noun = ((void* (__thiscall*)(void*))
                  (*(void***)((char*)self + 0x508))[4])((char*)self + 0x508);
    if (FUN_00b25f40(noun) != 0) {
        void* state = FUN_00bef6c0();
        if (*(int*)state != *(int*)((char*)state + 4)) {
            void* filter = 0;
            FUN_00ac9310(state, &filter, (unsigned)(size_t)sub & 0xffffff00);
            Vec3 target;
            FUN_00bdca30(&target, self->mB1c);
            if (target.x != *(float*)0x01699b08 ||
                target.y != *(float*)0x01699b0c ||
                target.z != *(float*)0x01699b10) {
                ((void (__thiscall*)(ObjectAt508*, Vec3*))
                 sub->mpVtbl[0x38 / 4])(sub, &target);
            }
        }
    }

    FUN_00afbad0(&path);
}
