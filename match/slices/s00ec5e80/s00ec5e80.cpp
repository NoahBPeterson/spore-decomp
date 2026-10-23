// Slice s00ec5e80 - SP::cTestScript / SP::cUnlockedCardUI region 0x00ec5e80..0x00ec6e00.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch/SSE /fp:fast   (matches the neighbour s00ec51a0,
// same object: the state-machine driver FUN_00ec5e80 and its message helpers).
#include "types.h"

typedef unsigned int  uint;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

// ---- eastl / external helpers (addresses in comments) ------------------
extern "C" __declspec(dllimport) void  __cdecl operator_delete__(void* p);            // 0x11e0744 area
extern "C" __declspec(dllimport) void* __cdecl memcpy(void*, const void*, uint);      // 0x011e0744
extern "C" __declspec(dllimport) int   __cdecl _decode_pointer(void*);               // reserved

void* __cdecl FUN_00f2b4f0(void* self, int n);              // 0x00f2b4f0 vector clear/resize
void* __cdecl FUN_00f2b690(void* self, int n);              // 0x00f2b690
void* __cdecl FUN_00f2c070(void* dst, void* src);           // 0x00f2c070
u8    __cdecl FUN_00f2c330(void* a, void* b);               // 0x00f2c330
void* __cdecl FUN_004f6b70(void* a, void* b);               // 0x004f6b70 eastl::sort
void* __cdecl FUN_004f6830(void* a, void* b, void* c);      // 0x004f6830 eastl::unique
u8    __cdecl FUN_004eb930(void* a, void* b);               // 0x004eb930 operator== declparam
u8    __cdecl FUN_00660650(void* a, void* b, void* c);      // 0x00660650 KeyContains
void* __cdecl FUN_00ec48c0(void* a, void* b);               // 0x00ec48c0
void* __cdecl FUN_00ec4d30(void* a, void* b, void* c);      // 0x00ec4d30
void  __cdecl FUN_00ec4e50(void* a);                        // 0x00ec4e50
void* __cdecl FUN_00ec4f00(void* a, void* b);               // 0x00ec4f00
void  __cdecl FUN_00ec5160();                               // 0x00ec5160
void  __cdecl FUN_00ec5340();                               // 0x00ec5340 SP::cTestScript::HandleMessage
void* __cdecl FUN_00ac0d80(void* a, void* b, void* c);     // 0x00ac0d80 eastl::find
void  __cdecl FUN_00eeee40(void* a);                        // 0x00eeee40
void* __cdecl FUN_00540520(void* a);                        // 0x00540520 SlotMessage dtor
void  __cdecl FUN_00571e80(void* a);                        // 0x00571e80 EA::Stopwatch::Restart
void* __cdecl FUN_0067cb30();                               // 0x0067cb30
void* __cdecl FUN_00612a50(void* self);                     // 0x00612a50
void* __cdecl FUN_00610460(void* a);                        // 0x00610460 PostEatFeed
void* __cdecl FUN_00607a60();                               // 0x00607a60 SP::Pollen::AuthManager
void* __cdecl FUN_0067dcd0();                               // 0x0067dcd0 EA::ResourceMan::GetManager
void* __cdecl FUN_0067dcc0();                               // 0x0067dcc0 SP::MessageServer
void* __cdecl FUN_00efc520();                               // 0x00efc520 ScenarioTutorials_GetActive
void* __cdecl FUN_00f3e8a0(void* a);                        // 0x00f3e8a0
u8    __cdecl FUN_00f25680(void* a);                        // 0x00f25680
u8    __cdecl FUN_00f25670(void* a);                        // 0x00f25670
void* __cdecl FUN_00a206f0();                               // 0x00a206f0 EA::Audio::GetSystemAT
void  __cdecl FUN_00435ed0(void* a, void* b);               // 0x00435ed0 SP::cSPUISpace::KillSetiEffects
void  __cdecl FUN_0050f740(void* a, void* b, void* c);      // 0x0050f740 SpVector::erase
void* __cdecl FUN_004e3e10(void* a, void* b, void* c);      // 0x004e3e10 vector DoInsertValue
void  __cdecl FUN_00809db0(void* a, void* b);               // 0x00809db0 UI::CalloutMessageBox
void  __cdecl FUN_00f47380(void* p);                        // 0x00f47380 operator delete[]
void  __cdecl FUN_00421cf0(void* a);                        // 0x00421cf0 SlotMessage::Destruct
void  __cdecl FUN_00ec5b10();                               // 0x00ec5b10 SP::RelationShipDebugDraw
void  __cdecl FUN_00ec5c70();                               // 0x00ec5c70
void  __cdecl FUN_00ec46c0();                               // 0x00ec46c0
void  __cdecl FUN_00ec4750();                               // 0x00ec4750
void  __cdecl FUN_00ec4f70(int a, int b);                   // 0x00ec4f70
void  __cdecl FUN_00ec5100();                               // 0x00ec5100
void  __cdecl FUN_00ec51f0();                               // 0x00ec51f0
void  __cdecl FUN_00ec56b0();                               // 0x00ec56b0 SP::cTestScript tick

u8    __cdecl FUN_0054e460(void* key, void* a, void* out);  // 0x0054e460 cAssetDirectory::GetLocalKey

extern "C" __declspec(dllimport) int __cdecl QueryPerformanceCounter(u64* out);  // kernel32

u64 __rdtsc_(void);

// ---- modelled objects --------------------------------------------------
//
// EA::ResourceMan::Key is a 12-byte {u32 type; u32 group; u32 instance}.
struct RmKey {
    u32 mType;      // +0x00
    u32 mGroup;     // +0x04
    u32 mInstance;  // +0x08
};

// A reference-counted object: vtable[0] = AddRef, vtable[1] = Release.
struct RefObj {
    void* mpVtbl;   // +0x00
};

// ---- SP::cTestScript ---------------------------------------------------
//
// The class the whole slice belongs to. Only the fields the code touches are
// named; anything in between is padding.
struct cTestScript {
    char    pad00[0x8];
    // +0x08 : the sub-object FUN_00ec67d0 / FUN_00ec6820 operate on (this-8)
    void*   mpMsg;        // +0x08  message/context object
    void*   mpWStr;       // +0x10  UI string (EaString)
    u8      mbCard;       // +0x14  card index
    u8      pad15[0x18 - 0x15];
    RefObj* mpAuth;       // +0x18  ref-counted auth/task object
    int     mMode;        // +0x1c
    char    pad20[0x48 - 0x20];
    int     mState;       // +0x48  state machine 0..5
    void*   mpKeysBegin;  // +0x4c  eastl::vector<RmKey>
    void*   mpKeysEnd;    // +0x50
    char    pad54[0x60 - 0x54];
    void*   mpBufBegin;   // +0x60  eastl::vector<u64-ish> stride 8
    void*   mpBufEnd;     // +0x64
    char    pad68[0x78 - 0x68];
    u32     mPerfLo;      // +0x78
    u32     mPerfHi;      // +0x7c
    u32     mPerfFlag0;   // +0x80  pending stopwatch
    u32     mPerfFlag1;   // +0x84
    int     mUseRdtsc;    // +0x88
    char    pad8c[0x90 - 0x8c];
    int     mCallout;     // +0x90

    void Dispatch();          // 0x00ec5e80
    u8   HandleMessage(int msg, void* args); // 0x00ec6250
    u8   KillMessage(int msg, int p);        // 0x00ec64b0
    u8   OnAuth(RefObj* auth);               // 0x00ec66a0
    u8   OnMsg(int msg, void* args);         // 0x00ec67d0
    u8   OnCard(int id);                     // 0x00ec6820
    u8   OnCardId(void* p);                  // 0x00ec68d0
    void KillSeti();                         // inline helper (audio + seti kill)
};

// Helper shared by every KillMessage() arm: stop the audio system's current
// effect and tear down the SETI effects for the id 0xe76c9b4f.
inline void cTestScript::KillSeti()
{
    void* at = FUN_00a206f0();
    if (at != 0) {
        ((void(__thiscall*)(void*))((void**)((RefObj*)at)->mpVtbl)[0x20 / 4])(at);
    }
    FUN_00435ed0(0, (void*)0xe76c9b4f);
}

int  __cdecl FUN_00ec6a00(int state);           // 0x00ec6a00
int  __cdecl FUN_00ec6ab0(int card);            // 0x00ec6ab0
int  __cdecl FUN_00ec6b20(RmKey* key);          // 0x00ec6b20
int  __cdecl FUN_00ec6940(float* v, float scale); // 0x00ec6940
void* __cdecl FUN_00ec6d00();                   // 0x00ec6d00
u8 __cdecl FUN_00ec68f0(const void* a, const void* b);  // 0x00ec68f0
u8 __cdecl FUN_00ec6d70(int* a);                        // 0x00ec6d70

// =======================================================================
// 0x00ec6a00 - 172 bytes: map a state enum to a card UI id
// =======================================================================
// @ 0x00ec6a00
int __cdecl FUN_00ec6a00(int state)
{
    switch (state) {
    case 0:  return 0xaaa0016;
    case 1:  return 0xaaa0010;
    case 2:  return 0xaaa0020;
    case 3:  return 0xaaa0013;
    case 4:  return 0xaaa0012;
    case 5:  return 0xaaa0017;
    case 6:  return 0xaaa0021;
    case 7:  return 0xaaa0023;
    case 8:  return 0xaaa0018;
    case 9:  return 0xaaa0019;
    case 10: return 0xaaa0022;
    case 11: return 0xaaa0015;
    case 12: return 0xaaa0014;
    case 13: return 0xaaa0011;
    case 14: return 0xaaa0070;
    default: return 0;
    }
}

// =======================================================================
// 0x00ec6ab0 - 112 bytes: map a card enum to a card UI id
// =======================================================================
// @ 0x00ec6ab0
int __cdecl FUN_00ec6ab0(int card)
{
    switch (card) {
    case 0:  return 0xaaa0061;
    case 1:  return 0xaaa0062;
    case 2:  return 0xaaa0063;
    case 3:  return 0xaaa0065;
    case 4:  return 0xaaa0064;
    case 5:  return 0xaaa0066;
    case 6:  return 0xaaa0069;
    case 7:  return 0xaaa0067;
    case 8:  return 0xaaa0068;
    default: return 0;
    }
}

// =======================================================================
// 0x00ec6b20 - 468 bytes: map a (kind, value) key to a card UI id
// =======================================================================
// @ 0x00ec6b20
int __cdecl FUN_00ec6b20(RmKey* key)
{
    switch (key->mType) {
    case 0:
        return 0xaaa0034;
    case 8:
        return 0xaaa0035;
    case 1:
        switch (key->mGroup) {
        case 1: return 0xaaa0036;
        case 2: return 0xaaa0037;
        case 3: return 0xaaa0038;
        case 4: return 0xaaa0039;
        }
        break;
    case 3:
        switch (key->mGroup) {
        case 8: return 0xaaa0024;
        case 0: return 0xaaa0025;
        case 1: return 0xaaa0026;
        case 2: return 0xaaa0027;
        case 3: return 0xaaa0028;
        case 4: return 0xaaa0029;
        case 5: return 0xaaa0030;
        case 6: return 0xaaa0031;
        case 7: return 0xaaa0032;
        }
        break;
    case 7:
        switch (key->mGroup) {
        case 10000: return 0xaaa0041;
        case 30000: return 0xaaa0042;
        case 60000: return 0xaaa0043;
        }
        break;
    case 5:
        switch (key->mGroup) {
        case 0x19: return 0xaaa0057;
        case 0x32: return 0xaaa0056;
        case 0x4b: return 0xaaa0055;
        }
        break;
    case 6:
        switch (key->mGroup) {
        case 0x19: return 0xaaa0051;
        case 0x32: return 0xaaa0052;
        case 0x4b: return 0xaaa0053;
        case 100:  return 0xaaa0054;
        }
        break;
    }
    return 0;
}

// =======================================================================
// 0x00ec68f0 - 76 bytes: field-wise equality of two 8-word keys
// =======================================================================
// @ 0x00ec68f0
u8 __cdecl FUN_00ec68f0(const void* a, const void* b)
{
    const u32* p = (const u32*)a;
    const u32* q = (const u32*)b;
    return (u8)(p[3] == q[3] && p[4] == q[4] && p[5] == q[5] && p[6] == q[6] &&
                p[7] == q[7] && p[0] == q[0] && p[1] == q[1] && p[2] == q[2]);
}

// =======================================================================
// 0x00ec6940 - 183 bytes: nearest card slot under the cursor position
// =======================================================================
// @ 0x00ec6940
int __cdecl FUN_00ec6940(float* v, float scale)
{
    int count = *(int*)(*(int*)(*(int*)0x16c7584) + 0x144);
    float y = v[1];
    float x = v[0];
    if (-scale > y) return -1;
    float limit = ((float)count - 2.0f + 0.5f) * scale;
    if (y > limit) return -1;
    if (-100.0f > x) return -1;
    if (x > 100.0f) return -1;
    int n = (int)(y / scale);
    float fv = (float)n;
    float lo = 0.0f;
    float hi = (float)count - 2.0f;
    float clamped = fv;
    if (clamped < lo) clamped = lo;
    if (clamped > hi) clamped = hi;
    return (int)clamped;
}

// =======================================================================
// 0x00ec6d70 - 134 bytes: tutorial gate predicate
// =======================================================================
struct TutorObj {                 // anonymous object at *[0x16c7aa4]+0x74
    void* Fn(void* arg);          // 0x00f3e8a0 (thiscall)
};
struct TutorRes {                 // result of the tutorial lookup
    u8   ChkA();                  // 0x00f25680 (thiscall)
    u8   ChkB();                  // 0x00f25670 (thiscall)
};
struct TutorInner {               // object at *[0x16c757c]
    char  pad00[0x70];
    void* mBase;                  // +0x70
};
struct TutorG {                   // *[0x16c757c]
    TutorInner* mInner;           // +0x00
};

// @ 0x00ec6d70
u8 FUN_00ec6d70(int* a)
{
    int n = (int)FUN_00efc520();
    int cnt = *(int*)((char*)(*(int*)(*(int*)0x16c757c) + 0x70) + n * 0x4e0 + 0x4a8) - 1;
    int kind = *a;
    if (kind == 1) {
        if (cnt == 0 || cnt == kind || a[1] != cnt) return 1;
        return 0;
    }
    if (kind == 2) {
        TutorObj* obj = *(TutorObj**)(*(int*)0x16c7aa4 + 0x74);
        TutorRes* m = (TutorRes*)obj->Fn((void*)a[1]);
        if (*(int*)(*(int*)0x16c757c) == (int)m) return 0;
        if (m->ChkA()) return 1;
        if (m->ChkB()) return 1;
        return 0;
    }
    if (kind == 8 && cnt == 1) return 0;
    return 1;
}

// =======================================================================
// 0x00ec6d00 - 111 bytes: acquire the next free card slot and start it
// =======================================================================
// @ 0x00ec6d00
struct CardSlot {
    u8      mbUsed;   // +0x00
    char    pad01[0x4 - 1];
    RefObj* mpObj;    // +0x04
    char    pad08[0x20 - 8];
};

void* __cdecl FUN_00ec6d00()
{
    int* root = *(int**)0x16c7584;
    if (*(int*)((char*)root + 0x144) == 10) {
        return 0;
    }
    CardSlot* slot = (CardSlot*)((char*)root + 4);
    int i = 0;
    for (;;) {
        CardSlot* cur = slot;
        if (cur->mbUsed == 0) {
            slot = cur;
            break;
        }
        i++;
        slot = (CardSlot*)((char*)slot + 0x20);
        if (i >= 10) break;
    }
    slot->mbUsed = 1;
    ((void(__thiscall*)(void*, int, int))((void**)((RefObj*)slot->mpObj)->mpVtbl)[0x7c / 4])(slot->mpObj, 1, 1);
    ((void(__thiscall*)(void*, float, float))((void**)((RefObj*)slot->mpObj)->mpVtbl)[0x64 / 4])(slot->mpObj, 0.0f, 200.0f);
    ((void(__thiscall*)(void*, int))((void**)((RefObj*)slot->mpObj)->mpVtbl)[0x5c / 4])(slot->mpObj, -1);
    (*(int*)((char*)(*(int**)0x16c7584) + 0x144))++;
    return slot;
}

// =======================================================================
// 0x00ec6820 - 165 bytes: resource lookup + register the auth/task object
// =======================================================================
// @ 0x00ec6820
u8 cTestScript::OnCard(int resId)
{
    RefObj* found;
    FUN_00ec4f70(1, 0);
    found = 0;
    void* mgr = FUN_0067dcd0();
    if (found != 0) {
        RefObj* tmp = found;
        found = 0;
        ((void(__thiscall*)(RefObj*))((void**)tmp->mpVtbl)[4 / 4])(tmp);
    }
    u8 ok = ((u8(__thiscall*)(void*, int, RefObj**, int, int, int, int))
             ((void**)((RefObj*)mgr)->mpVtbl)[0xc / 4])(mgr, resId, &found, 0, 0, 0, 0);
    if (ok) {
        if (found == 0) return 0;
        RefObj* obj = (RefObj*)((void*(__thiscall*)(RefObj*, int))
                                ((void**)found->mpVtbl)[0xc / 4])(found, 0xe742574a);
        if (obj != 0) {
            u8 r = OnAuth(obj);
            if (found != 0) {
                ((void(__thiscall*)(RefObj*))((void**)found->mpVtbl)[4 / 4])(found);
            }
            return r;
        }
    }
    if (found != 0) {
        ((void(__thiscall*)(RefObj*))((void**)found->mpVtbl)[4 / 4])(found);
    }
    return 0;
}

// =======================================================================
// 0x00ec68d0 - 32 bytes: message filter for the "0x366a930d" resource id
// =======================================================================
// The original's `this` sits 0x14 bytes past the cTestScript base.
struct CardMsgCtx {
    cTestScript* Parent();  // this - 0x14
};

// @ 0x00ec68d0
u8 __fastcall FUN_00ec68d0(CardMsgCtx* self, void*, void* arg)
{
    if (*(int*)((char*)arg + 4) == 0x366a930d) {
        ((cTestScript*)((char*)self - 0x14))->OnCard((int)arg);
        return 1;
    }
    return 0;
}

// =======================================================================
// 0x00ec67d0 - 79 bytes: dispatch a message to the cTestScript state machine
// =======================================================================
// The original's `this` sits 8 bytes past the cTestScript base; it forwards to
// the tick (0x00ec56b0) or message (0x00ec6250) helpers based on mMode.
struct TickCtx {
    char  pad00[0x14];
    int   mMode;      // +0x14 (i.e. cTestScript + 0x1c)
};

// @ 0x00ec67d0
u8 __fastcall FUN_00ec67d0(TickCtx* self, void*, int msg, void* args)
{
    cTestScript* p = (cTestScript*)((char*)self - 8);
    if (msg == 0x1ee100a) {
        FUN_00ec51f0();
    }
    if (self->mMode == 1) {
        FUN_00ec56b0();
    } else if (self->mMode == 2) {
        p->HandleMessage(msg, args);
    }
    return 0;
}

// =======================================================================
// 0x00ec66a0 - 290 bytes: adopt the auth object and (re)start the sequence
// =======================================================================
// @ 0x00ec66a0
u8 cTestScript::OnAuth(RefObj* auth)
{
    FUN_00ec4f70(1, 0);
    if (auth == 0) return 0;
    RefObj* old = mpAuth;
    if (auth != old) {
        ((void(__thiscall*)(RefObj*))((void**)auth->mpVtbl)[0 / 4])(auth);
        mpAuth = auth;
        if (old != 0) {
            ((void(__thiscall*)(RefObj*))((void**)old->mpVtbl)[4 / 4])(old);
        }
    }
    void* mgr = FUN_00607a60();
    if (((u8(__thiscall*)(void*))((void**)((RefObj*)mgr)->mpVtbl)[0x58 / 4])(mgr)) {
        if (!((u8(__thiscall*)(void*))((void**)((RefObj*)mgr)->mpVtbl)[0x24 / 4])(mgr)) {
            mMode = 2;
            mState = 0;
            FUN_00f2b4f0(&mpKeysBegin, 2);
            FUN_00f2b690(&mpBufBegin, 0x100);
            Dispatch();
            return 1;
        }
    }
    if (mpAuth != 0) {
        RefObj* tmp = mpAuth;
        mpAuth = 0;
        ((void(__thiscall*)(RefObj*))((void**)tmp->mpVtbl)[4 / 4])(tmp);
    }
    mMode = 0;
    FUN_00f2b4f0(&mpKeysBegin, 2);
    FUN_00f2b690(&mpBufBegin, 0x100);
    mCallout = 9;
    FUN_00809db0(&mpWStr, (void*)0x15abc28);
    return 0;
}

// =======================================================================
// 0x00ec5e80 - 965 bytes: the cTestScript state-machine driver
// =======================================================================
// @ 0x00ec5e80
void cTestScript::Dispatch()
{
    for (;;) {
        if (mState > 5) return;
        switch (mState) {
        case 0:
            break;
        case 1:
            FUN_00f2b4f0(&mpKeysBegin, 2);
            if (mpKeysBegin != mpKeysEnd) {
                FUN_00ec5b10();
                return;
            }
            break;
        case 2:
            FUN_00f2b690(&mpBufBegin, 0x100);
            if (mpBufBegin != mpBufEnd) {
                FUN_00610460(FUN_0067cb30());
                return;
            }
            break;
        case 3:
            if (mpBufBegin != mpBufEnd) {
                FUN_00ec5c70();
                return;
            }
            break;
        case 4: {
            if (mpAuth == 0) return;
            RmKey* begin = 0;
            RmKey* end   = 0;
            RmKey* cap   = 0;
            bool   haveKeys = false;
            if (((char*)mpBufEnd - (char*)mpBufBegin) >> 3 != 0) {
                int n = 0;
                do {
                    RmKey k;
                    k.mType = 0; k.mGroup = 0; k.mInstance = 0;
                    void* dir = (void*)((u32*)FUN_0067cb30())[0x58 / 4];
                    if (!FUN_0054e460(dir, (void*)((u32*)mpBufBegin)[n * 2 + 1], &k)) {
                        FUN_00ec4f70(1, 0);
                        if (begin && ((u32*)begin)[-1]) FUN_00f47380(begin);
                        if (end && ((u32*)end)[-1]) FUN_00f47380(end);
                        return;
                    }
                    if (begin < cap) {
                        *begin = k;
                    } else {
                        begin = (RmKey*)FUN_004e3e10(begin, end, &k);
                    }
                    begin++;
                    n++;
                } while ((u32)(((char*)mpBufEnd - (char*)mpBufBegin) >> 3) > (u32)n);
                haveKeys = begin != cap;
                if (haveKeys) FUN_00f2c070(&begin, &end);
            }
            if (FUN_00f2c330(0, mpKeysBegin) || haveKeys) {
                FUN_00ec46c0();
                FUN_00f2b4f0(&mpKeysBegin, 2);
                FUN_004f6b70(begin, end);
                FUN_004f6830(begin, end, end);
            }
            if (mpKeysBegin != mpKeysEnd) {
                goto step4_send;
            }
            break;
        }
        case 5:
            FUN_00ec5160();
            break;
        }
        if (++mState > 5) return;
    }
step4_send:
    {
        void* ms = FUN_0067dcc0();
        (void)ms;
    }
}

// =======================================================================
// 0x00ec6250 - 598 bytes: incoming message handler
// =======================================================================
// @ 0x00ec6250
u8 cTestScript::HandleMessage(int msg, void* args)
{
    if (msg == 0x68cd252) {
        if (mState == 4 && args != 0) {
            RmKey* a = (RmKey*)args;
            RmKey k;
            k.mType = a->mType; k.mGroup = a->mGroup; k.mInstance = a->mInstance;
            RmKey* found = (RmKey*)FUN_00ac0d80(mpKeysBegin, mpKeysEnd, &k);
            if (found != mpKeysEnd) {
                if (*(u8*)args != 0) {
                    FUN_00eeee40(found);
                    if (mpKeysBegin != mpKeysEnd) {
                        FUN_00571e80(&mPerfLo);
                        return 0;
                    }
                    FUN_00ec46c0();
                    void* v0 = 0; void* v1 = 0; void* v2 = 0;
                    FUN_00f2b4f0(&v0, 2);
                    if (v0 == v1) {
                        void* ms = FUN_0067dcc0();
                        ((void(__thiscall*)(void*, int, void*, int))
                         ((void**)((RefObj*)ms)->mpVtbl)[0x14 / 4])(ms, 0x2ba2010, (char*)mpAuth + 8, 0);
                        FUN_00540520(&v0);
                        return 0;
                    }
                    FUN_00ec4f70(1, 0);
                    FUN_00540520(&v0);
                    return 0;
                }
                FUN_00ec4f70(1, 0);
                return 0;
            }
            if (mpAuth != 0) {
                if (FUN_004eb930(&k, (char*)mpAuth + 8)) {
                    if (*(u8*)args != 0) {
                        FUN_00ec5160();
                        return 0;
                    }
                    FUN_00ec4f70(0, 0);
                }
            }
        }
    } else if (msg == 0x1dd7bda9 && mState == 2) {
        int flag = *(int*)args;
        void* obj = (void*)((void**)args)[1];
        if (obj != 0) {
            RefObj* o = (RefObj*)obj;
            if (((int(__thiscall*)(RefObj*))((void**)o->mpVtbl)[0x10 / 4])(o) == (int)0x86080586) {
                if (!FUN_00ec48c0((char*)o + 0x30, &mpBufBegin)) {
                    if (flag == 1) {
                        FUN_00ec4f00(mpBufBegin, mpBufEnd);
                        void* sub = *(void**)((char*)o + 8);
                        u8 i = 0;
                        int cnt = (int)FUN_00612a50((char*)sub + 0x60);
                        if (cnt != 0) {
                            int off = 0;
                            do {
                                void* hit = FUN_00ec4d30(mpBufBegin, mpBufEnd, (char*)(*(int*)((char*)sub + 0x60)) + 0x10 + off);
                                if (hit != mpBufEnd) FUN_00ec4e50(hit);
                                sub = *(void**)((char*)o + 8);
                                off += 0x118;
                                i++;
                            } while (i < (u8)FUN_00612a50((char*)sub + 0x60));
                        }
                        mState++;
                        Dispatch();
                        return 0;
                    }
                    FUN_00ec4f70(1, 0);
                    return 0;
                }
            }
        }
    }
    return 0;
}

// =======================================================================
// 0x00ec64b0 - 488 bytes: modal-window / card callback
// =======================================================================
// @ 0x00ec64b0
u8 cTestScript::KillMessage(int msg, int p)
{
    int which = mPerfFlag0;
    mPerfFlag0 = 0;
    cTestScript* p2 = (cTestScript*)((char*)this - 0x10);
    u8 r = 0;
    switch (which) {
    case 1: case 2: case 3: case 4:
        KillSeti();
        if (p == 0x5107b1a) {
            p2->mMode++;
            FUN_00ec5340();
            break;
        }
        FUN_00ec4f70(1, 0);
        break;
    case 5: case 6:
        KillSeti();
        if (p == 0x5107b1a) {
            p2->mState++;
            Dispatch();
            break;
        }
        FUN_00ec4f70(1, 0);
        break;
    case 7:
        KillSeti();
        if (p == 0x5107b1a) {
            FUN_00ec5100();
            break;
        }
        FUN_00ec4f70(1, 3);
        break;
    case 8:
        KillSeti();
        FUN_00ec4f70(1, 3);
        break;
    case 9:
        KillSeti();
        if (p == 0x5107b1a) {
            void* mgr = FUN_00607a60();
            ((void(__thiscall*)(void*))((void**)((RefObj*)mgr)->mpVtbl)[0x44 / 4])(mgr);
            break;
        }
        if (p == 0x5107b19) {
            FUN_00ec5100();
            break;
        }
        FUN_00ec4f70(1, 0);
        break;
    default:
        break;
    }
    return r;
}
