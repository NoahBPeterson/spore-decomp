// Slice s00dfe460 (batch bfs3, slice 12). Region 0xdfe460-0xdff7ff.
// EASTL vector helpers over large element types (0x188, 0x238, 0x4e0, 0x27e8,
// 0x2788) plus a big UI message handler and a large destructor.
// Optimised: /O2 /MD /Gy /TP /arch=SSE.
#include "types.h"

extern "C" void* __cdecl EA_Allocate(uint32_t size, const char* name, int a, int b,
                                     int c, int d);              // 0xf473a0
extern "C" void  __cdecl EA_Free(void* p);                       // 0xf47380
extern "C" void  __fastcall FUN_00f280f0(void* self, int dummy);
extern "C" void  __fastcall FUN_00dfbba0(void* self, int dummy);
extern "C" void  __cdecl FUN_00dfdfe0(void*);
extern "C" void  __cdecl FUN_00dfdf70(void*, void*);
extern "C" void  __cdecl FUN_00dfd300(void*, void*);
extern "C" void  __cdecl FUN_00dfdf10(void*, void*);
extern "C" void* __cdecl FUN_00dfd250(void*, void*, void*);
extern "C" void* __cdecl FUN_00dfd2c0(void*, void*, void*);
extern "C" void  __cdecl FUN_00dfd4e0(void*, void*, void*, void*, void*);
// thiscall stub classes (receiver in ECX)
struct V188 {
    void* b; void* e; void* cap;
    V188* Assign(V188* other);                       // 0x00dfeb00 ret 4
    void* Alloc(uint32_t n, void* f, void* l);       // 0x00dfe9e0 ret 0xc
    void  Destroy(void* f, void* l);                 // 0x00dfc600 ret 8
};
struct V4e0 {
    void* b; void* e; void* cap;
    V4e0* Assign(V4e0* other);                       // 0x00dfec50 ret 4
    V4e0* AssignWrap(V4e0* other);                   // 0x00dfed90 ret 4
    void* Alloc(uint32_t n, void* f, void* l);       // 0x00dfea40 ret 0xc
    void  Destroy(void* f, void* l);                 // 0x00dfc660 ret 8
};
struct CStr {
    uint8_t mData[0x3c];                             // own storage, 0x3c bytes
    void Assign(void* o);                            // 0x006b5430 thiscall ret 4
    void Destroy();                                  // 0x00f280f0 thiscall, ??1CStr@@QAE@XZ
};
struct ElemA {                                       // 0x2788-class
    void* CopyAssign(void* o);                       // 0x00dfedb0 ret 4
    void* CopyCtor(void* o);                         // 0x00dff1a0 ret 4
};
struct ElemB {                                       // 0x27e8-class
    void* CopyCtor(void* o);                         // 0x00dfee80 ret 4
    void* Init(void* o);                             // 0x00dff130 ret 4
};
struct Buf3c {
    void Copy(void* o);                              // 0x00dfb280 thiscall ret 4
};
extern "C" void __fastcall WStr_Assign(void* self, int dummy, void* begin, void* end); // 0x00423650 thiscall ret 8
extern "C" void  __cdecl FUN_00df9990();
extern "C" void  __cdecl FUN_00df9ef0();
extern "C" void  __cdecl FUN_00df9e60();
extern "C" void  __cdecl FUN_00dfae50();
extern "C" void  __cdecl FUN_00dfab20();
extern "C" void  __cdecl FUN_00dfa460();
extern "C" void  __cdecl FUN_00685a30(void*, void*);
extern "C" uint32_t __cdecl FUN_00435e90();     // GetRecorderState
extern "C" void  __cdecl FUN_00435ed0(uint32_t id, uint32_t value);  // RecordEvent2
extern "C" void* __cdecl FUN_00a206f0();        // EA::Audio::GetSystemAT

// ===========================================================================
//  0x00dfe460  SP::cSPUISpace message/command handler (big prologue switch)
// ===========================================================================
struct Any3 {                                       // three-word command payload
    uint32_t a, b, c;
};
struct CmdObj {                                     // command object carried by a message
    virtual uint32_t Vf00();
    virtual uint32_t Vf01();
    virtual uint32_t Vf02();
    virtual uint32_t Vf03();
    virtual uint32_t Vf04();
    virtual uint32_t Vf05();
    virtual uint32_t Vf06();
    virtual uint32_t CommandId();                   // +0x1c
    virtual uint32_t Vf08();
    virtual uint32_t Vf09();
    virtual uint8_t  Flags();                       // +0x28
};
struct GGUIMsg {
    CmdObj*  mpObj;                                 // +0x00
    uint32_t mPad004;                               // +0x04
    uint32_t mType08;                               // +0x08
};
struct AudioSys {
    virtual uint32_t Vf00();
    virtual uint32_t Vf01();
    virtual uint32_t Vf02();
    virtual uint32_t Vf03();
    virtual uint32_t Vf04();
    virtual uint32_t Vf05();
    virtual uint32_t Vf06();
    virtual uint32_t Vf07();
    virtual uint32_t EventId();                     // +0x20
};
struct cSPUIWindow {                                // window object
    virtual uint32_t Vf00();
    virtual uint32_t Vf01();
    virtual uint32_t Vf02();
    virtual cSPUIWindow* FindChild(uint32_t id);    // +0x0c
    virtual uint32_t Vf04();
    virtual uint32_t Vf05();
    virtual uint32_t Vf06();
    virtual uint32_t Vf07();
    virtual uint32_t Vf08();
    virtual uint32_t Vf09();
    virtual uint32_t Vf10();
    virtual uint32_t Vf11();
    virtual uint32_t Vf12();
    virtual uint32_t Vf13();
    virtual uint32_t Vf14();
    virtual uint32_t Vf15();
    virtual uint32_t Vf16();
    virtual uint32_t Vf17();
    virtual uint32_t Vf18();
    virtual uint32_t Vf19();
    virtual uint32_t Vf20();
    virtual void*    GetText();                     // +0x54
    virtual uint32_t Vf22();
    virtual uint32_t Vf23();
    virtual void     SetText(void* text, int b);    // +0x60
};
struct cSPUILayout {                                // layout anchored at space+0x48
    uint8_t mData[0x36];
    cSPUIWindow* FindWindowByID(uint32_t id, int flag);   // 0x008105b0 ret 8
};
struct WString {
    wchar_t* mpData;                                // +0x00
    void Append(void* text);                        // 0x005c3d90 ret 4
};
struct SomeActive {                                 // object behind globals+0x1c
    char IsActive();                                // 0x00ec4320
};
struct cEditorGlobals {                             // object behind 0x016c7aa4
    uint32_t    mPad000[7];
    SomeActive* mpActive1c;                         // +0x001c
};
struct IfcStateSub {                                // object behind ifcstate+0x198
    void NotifySequence();                          // 0x00de0890
};
struct cInterfaceState {                            // object behind 0x016a1344
    uint32_t    mPad000[0x198 / 4];
    IfcStateSub* mpSub198;                          // +0x198
    void SetSlotMode(uint32_t a, uint32_t b);       // 0x00de86d0
    void SetEntryFlag(char v);                      // 0x00de5330
};
extern "C" cEditorGlobals*    g_pEditorGlobals;    // 0x016c7aa4
extern "C" cInterfaceState*   g_pInterfaceState;   // 0x016a1344

struct cSPUISpace {
    uint32_t     mPad000[(0x20 - 0x00) / 4];
    int32_t      mMode20;                           // +0x20  current editor mode
    uint32_t     mPad024[(0x48 - 0x24) / 4];
    cSPUILayout  mLayout48;                         // +0x48
    uint8_t      mFlag7e;                           // +0x7e
    uint8_t      mPad07f[0xa4 - 0x7f];
    Any3         mAny3A4;                           // +0x0a4
    uint32_t     mPad0b0[(0x168 - 0xb0) / 4];
    WString      mStr168;                           // +0x168
    char DoMessage(int arg1, GGUIMsg* msg);         // 0x00dfe460 ret 8
    void Fn9990();                                  // 0x00df9990
    void Fn9ef0();                                  // 0x00df9ef0
    void Fn9e60();                                  // 0x00df9e60
    void Fn9a70();                                  // 0x00df9a70
    void Fn9a00();                                  // 0x00df9a00
    void Fn9ad0();                                  // 0x00df9ad0
    void SetModeEnabled(int on);                    // 0x00dfab20 ret 4
    void FnAe50();                                  // 0x00dfae50
    void FnA460(Any3* p, int b);                    // 0x00dfa460 ret 8
    void LaunchAssetBrowser(int kind);              // 0x00dfa5c0 ret 4
    void FnAf80();                                  // 0x00dfaf80
    void FnD5b0();                                  // 0x00dfd5b0
    void FnDc50();                                  // 0x00dfdc50
    void FnDe90();                                  // 0x00dfde90
    void FnE220();                                  // 0x00dfe220
    char CheckX();                                  // 0x00dfc500
};

static __forceinline void RecordEvent(uint32_t id) { // 0x00435ed0 wrapper
    FUN_00435ed0(id, FUN_00435e90());
}

static __forceinline uint32_t AudioEventValue() {   // audio system event tag
    AudioSys* p = (AudioSys*)FUN_00a206f0();
    return p ? p->EventId() : 0;
}

// @ 0x00dfe460
char cSPUISpace::DoMessage(int arg1, GGUIMsg* msg) {
    (void)arg1;
    if (msg->mType08 == 0x287259f6) {
        if (mMode20 != 0xb && !g_pEditorGlobals->mpActive1c->IsActive()) {
            switch (msg->mpObj->CommandId()) {
            case 0x54045ce:
                Fn9990();
                return 1;
            case 0x5384d05:
            case 0x5384d06:
            case 0x5384d07:
            case 0x5384d08:
                RecordEvent(0x8e82b51c);
                Fn9ef0();
                return 1;
            case 0x5933fe0:
            case 0x5933fe1:
            case 0x5933fe2:
            case 0x5933fe3:
                RecordEvent(0x8e82b51c);
                Fn9e60();
                return 1;
            case 0x5951103:
            case 0x5951104:
                RecordEvent(0xddd740f9);
                FnAe50();
                return 1;
            case 0x733b57f:
                SetModeEnabled(0);
                mMode20 = 9;
                return 1;
            case 0x733fe09: {
                Any3 t;
                t.a = 0;
                t.b = 0;
                t.c = 0;
                FnA460(&t, 0);
                mMode20 = 6;
                SetModeEnabled(0);
                return 1;
            }
            case 0x733fe08:
                RecordEvent(0x8e82b51c);
                FnE220();
                return 1;
            case 0x73bba58:
                mMode20 = 5;
                SetModeEnabled(0);
                Fn9a70();
                return 1;
            case 0x74d0932:
                Fn9a00();
                mMode20 = 7;
                SetModeEnabled(0);
                return 1;
            case 0x7c683f0:
                LaunchAssetBrowser(0);
                return 1;
            case 0x7bfb76e:
            case 0x7bfcff8:
                if (mMode20 == 0) {
                    SetModeEnabled(0);
                    RecordEvent(0xebadb118);
                    g_pInterfaceState->mpSub198->NotifySequence();
                    g_pInterfaceState->SetSlotMode(2, 0);
                    g_pInterfaceState->SetEntryFlag(1);
                } else {
                    RecordEvent(0x8e82b51c);
                    Fn9ad0();
                    mMode20 = 0;
                }
                return 1;
            case 0x7c683f1:
                LaunchAssetBrowser(1);
                return 1;
            case 0x7c683f2:
                LaunchAssetBrowser(2);
                return 1;
            case 0x7ca4119:
                FnA460(&mAny3A4, 0);
                return 1;
            case 0x7ccc126:
                RecordEvent(0x91be3241);
                FnD5b0();
                return 1;
            case 0x7ccc115:
                FnDe90();
                return 1;
            case 0x7ccc133:
                RecordEvent(0x91be3241);
                FnDc50();
                return 1;
            case 0x7ccc2a4:
                RecordEvent(0x91be3241);
                FnAf80();
                return 1;
            default:
                break;
            }
        }
    } else if (msg->mType08 == 0x9b1552d8) {
        FUN_00435ed0(0x1ac6d1af, AudioEventValue());
        uint32_t cmd = msg->mpObj->CommandId();
        if (cmd == 0x5400fa5) {
            cSPUIWindow* w = mLayout48.FindWindowByID(cmd, 1);
            if (w != 0) {
                cSPUIWindow* child = w->FindChild(0xcf428691);
                if (child != 0) {
                    mStr168.Append(child->GetText());
                    if (CheckX())
                        child->SetText(mStr168.mpData, 0);
                }
            }
            mFlag7e = 1;
            return 1;
        }
    } else if (msg->mType08 == 0x1b) {
        uint32_t cmd = msg->mpObj->CommandId();
        if (cmd == 0x73bba58 || cmd == 0x733fe08 || cmd == 0x74d0932) {
            if ((msg->mpObj->Flags() & 2) != 0)
                FUN_00435ed0(0xd607a5a7, AudioEventValue());
        }
    }
    return 1;
}

// ===========================================================================
//  0x00dfe910  destroy a range of 0x27e8-stride elements
// ===========================================================================
struct Elem27e8 { char pad[0x78]; void* mp; };   // vector member at +0x78
// @ 0x00dfe910
Elem27e8* __stdcall DestroyRange27e8(Elem27e8* first, Elem27e8* last) {
    Elem27e8* result = first;
    while (first < last) {
        FUN_00f280f0((char*)first + 0x78 + 0x2718, 0);
        void** begin = *(void***)((char*)first + 0x78);
        void** end = *(void***)((char*)first + 0x7c);
        while (begin < end) {
            FUN_00dfbba0(begin, 0);
            begin = (void**)((char*)begin + 0x4e0);
        }
        void* p = *(void**)((char*)first + 0x78);
        result = (Elem27e8*)p;
        if (p != 0 && *((int*)p - 1) != 0) {
            EA_Free(p);
        }
        first = (Elem27e8*)((char*)first + 0x27e8);
    }
    return result;
}

// ===========================================================================
//  0x00dfeaa0  uninitialized_copy, stride 0x238
// ===========================================================================
// @ 0x00dfeaa0
void** UninitCopy238(void** dstp, int* first, int* last, int val) {
    *dstp = (void*)val;
    while (first != last) {
        char* d = (char*)*dstp;
        if (d != 0) {
            *(int*)d = *first;
            if (*first >= 0) {
                d += 4;
                if (d != 0) {
                    FUN_00dfdfe0(first + 1);
                }
            }
        }
        *dstp = (char*)*dstp + 0x238;
        first = (int*)((char*)first + 0x238);
    }
    return dstp;
}

// ===========================================================================
//  0x00dfeb00  vector assign, stride 0x188
// ===========================================================================
// @ 0x00dfeb00
V188* V188::Assign(V188* other_) {
    void** self = (void**)this; int* other = (int*)other_;
    if (other == (int*)self) {
        return this;
    }
    int iVar1 = *other;
    uint32_t uVar2 = (uint32_t)((other[1] - iVar1) / 0x188);
    int iVar5 = (int)*self;
    if ((uint32_t)(((int*)self)[2] - iVar5) / 0x188 < uVar2) {
        iVar5 = (int)Alloc(uVar2, (void*)iVar1, (void*)other[1]);
        Destroy(*self, (void*)((int*)self)[1]);
        int p = (int)*self;
        if (p != 0 && *(int*)(p - 4) != 0) {
            EA_Free((void*)p);
        }
        ((int*)self)[1] = uVar2 * 0x188 + iVar5;
        *self = (void*)iVar5;
        ((int*)self)[2] = uVar2 * 0x188 + iVar5;
        return this;
    }
    uint32_t uVar3 = (uint32_t)(((int*)self)[1] - iVar5) / 0x188;
    if (uVar3 < uVar2) {
        FUN_00dfd250((void*)iVar1, (void*)(uVar3 * 0x188 + iVar1), (void*)iVar5);
        other = (int*)other[1];
        FUN_00dfd4e0(&other, (void*)((((int*)self)[1] - (int)*self) / 0x188 * 0x188 + *other),
                     other, (void*)((int*)self)[1], other);
        ((int*)self)[1] = uVar2 * 0x188 + (int)*self;
        return this;
    }
    void* uVar6 = FUN_00dfd250((void*)iVar1, (void*)other[1], (void*)iVar5);
    Destroy(uVar6, (void*)((int*)self)[1]);
    ((int*)self)[1] = uVar2 * 0x188 + (int)*self;
    return this;
}

// ===========================================================================
//  0x00dfec50  vector resize/assign, stride 0x4e0
// ===========================================================================
// @ 0x00dfec50
V4e0* V4e0::Assign(V4e0* other_) {
    void** self = (void**)this; int* other = (int*)other_;
    if (other == (int*)self) {
        return this;
    }
    int iVar1 = *other;
    uint32_t uVar2 = (uint32_t)((other[1] - iVar1) / 0x4e0);
    int ebp0 = (int)*self;
    if ((uint32_t)(((int*)self)[2] - ebp0) / 0x4e0 < uVar2) {
        int iVar5 = (int)Alloc(uVar2, (void*)iVar1, (void*)other[1]);
        Destroy(*self, (void*)((int*)self)[1]);
        int p = (int)*self;
        if (p != 0 && *(int*)(p - 4) != 0) {
            EA_Free((void*)p);
        }
        *self = (void*)iVar5;
        ((int*)self)[2] = uVar2 * 0x4e0 + iVar5;
        ((int*)self)[1] = uVar2 * 0x4e0 + iVar5;
        return this;
    }
    uint32_t uVar3 = (uint32_t)(((int*)self)[1] - ebp0) / 0x4e0;
    if (uVar3 < uVar2) {
        FUN_00dfd2c0((void*)iVar1, (void*)(uVar3 * 0x4e0 + iVar1), (void*)ebp0);
        other = (int*)other[1];
        FUN_00dfd4e0(&other, (void*)((((int*)self)[1] - (int)*self) / 0x4e0 * 0x4e0 + *other),
                     other, (void*)((int*)self)[1], other);
        ((int*)self)[1] = uVar2 * 0x4e0 + (int)*self;
        return this;
    }
    void* uVar6 = FUN_00dfd2c0((void*)iVar1, (void*)other[1], (void*)ebp0);
    Destroy(uVar6, (void*)((int*)self)[1]);
    ((int*)self)[1] = uVar2 * 0x4e0 + (int)*self;
    return this;
}

// @ 0x00dfed90  wrapper calling 00dfec50
V4e0* V4e0::AssignWrap(V4e0* other) {
    Assign(other);
    return this;
}

// ===========================================================================
//  0x00dfedb0  copy-assign for the 0x2788 element class
// ===========================================================================
// @ 0x00dfedb0
void* ElemA::CopyAssign(void* o) {
    void* s = this;
    ((CStr*)s)->Assign(o);
    if ((void*)((char*)o + 0x14) != (void*)((char*)s + 0x14)) {
        WStr_Assign((char*)s + 0x14, 0, *(void**)((char*)o + 0x14), *(void**)((char*)o + 0x18));
    }
    *(uint32_t*)((char*)s + 0x24) = *(uint32_t*)((char*)o + 0x24);
    *(uint32_t*)((char*)s + 0x28) = *(uint32_t*)((char*)o + 0x28);
    if ((void*)((char*)o + 0x2c) != (void*)((char*)s + 0x2c)) {
        WStr_Assign((char*)s + 0x2c, 0, *(void**)((char*)o + 0x2c), *(void**)((char*)o + 0x30));
    }
    ((CStr*)((char*)s + 0x3c))->Assign((char*)o + 0x3c);
    if ((void*)((char*)o + 0x50) != (void*)((char*)s + 0x50)) {
        WStr_Assign((char*)s + 0x50, 0, *(void**)((char*)o + 0x50), *(void**)((char*)o + 0x54));
    }
    *(uint32_t*)((char*)s + 0x60) = *(uint32_t*)((char*)o + 0x60);
    *(uint32_t*)((char*)s + 0x64) = *(uint32_t*)((char*)o + 0x64);
    if ((void*)((char*)o + 0x68) != (void*)((char*)s + 0x68)) {
        WStr_Assign((char*)s + 0x68, 0, *(void**)((char*)o + 0x68), *(void**)((char*)o + 0x6c));
    }
    *(uint32_t*)((char*)s + 0x78) = *(uint32_t*)((char*)o + 0x78);
    *(uint8_t*)((char*)s + 0x7c) = *(uint8_t*)((char*)o + 0x7c);
    *(uint32_t*)((char*)s + 0x80) = *(uint32_t*)((char*)o + 0x80);
    ((V188*)((char*)s + 0x84))->Assign((V188*)((char*)o + 0x84));
    return s;
}

// ===========================================================================
//  0x00dfee80  copy-ctor for the 0x27e8 element class
// ===========================================================================
// @ 0x00dfee80
void* ElemB::CopyCtor(void* o) {
    void* s = this;
    for (int i = 0; i < 8; ++i) ((uint32_t*)s)[i] = ((uint32_t*)o)[i];
    *(uint8_t*)((char*)s + 0x20) = *(uint8_t*)((char*)o + 0x20);
    *(uint32_t*)((char*)s + 0x24) = *(uint32_t*)((char*)o + 0x24);
    for (int i = 0; i < 8; ++i) ((uint32_t*)((char*)s + 0x28))[i] = ((uint32_t*)((char*)o + 0x28))[i];
    *(uint32_t*)((char*)s + 0x48) = *(uint32_t*)((char*)o + 0x48);
    for (int i = 0; i < 8; ++i) ((uint32_t*)((char*)s + 0x50))[i] = ((uint32_t*)((char*)o + 0x50))[i];
    ((V4e0*)((char*)s + 0x70))->Assign((V4e0*)((char*)o + 0x70));
    ((CStr*)((char*)s + 0x2788))->Assign((char*)o + 0x2788);
    if ((void*)((char*)o + 0x2788 + 0x14) != (void*)((char*)s + 0x2788 + 0x14)) {
        WStr_Assign((char*)s + 0x2788 + 0x14, 0, *(void**)((char*)o + 0x2788 + 0x14), *(void**)((char*)o + 0x2788 + 0x18));
    }
    *(uint32_t*)((char*)s + 0x27ac) = *(uint32_t*)((char*)o + 0x27ac);
    *(uint32_t*)((char*)s + 0x27b0) = *(uint32_t*)((char*)o + 0x27b0);
    if ((void*)((char*)o + 0x2788 + 0x2c) != (void*)((char*)s + 0x2788 + 0x2c)) {
        WStr_Assign((char*)s + 0x2788 + 0x2c, 0, *(void**)((char*)o + 0x2788 + 0x2c), *(void**)((char*)o + 0x2788 + 0x30));
    }
    *(uint32_t*)((char*)s + 0x27c4) = *(uint32_t*)((char*)o + 0x27c4);
    *(uint32_t*)((char*)s + 0x27c8) = *(uint32_t*)((char*)o + 0x27c8);
    *(uint32_t*)((char*)s + 0x27cc) = *(uint32_t*)((char*)o + 0x27cc);
    *(uint32_t*)((char*)s + 0x27d0) = *(uint32_t*)((char*)o + 0x27d0);
    *(uint32_t*)((char*)s + 0x27d8) = *(uint32_t*)((char*)o + 0x27d8);
    *(uint32_t*)((char*)s + 0x27dc) = *(uint32_t*)((char*)o + 0x27dc);
    return s;
}

// ===========================================================================
//  0x00dfef70  large destructor
// ===========================================================================
// An eastl vector of unknown element type: only the range and the begin pointer
// (which owns its allocation, hence the [-4] ownership flag) are touched here.
struct VecAny {
    void* mpBegin;                                   // +0x00
    void* mpEnd;                                     // +0x04
    void* mpCapacity;                                // +0x08
    void DestroyRange(void* first, void* last);           // 0x00dfdf70 ret 8
    void DestroyRangeUnk(void* first, void* last);        // 0x00dfd300 ret 8
    void DestroyRange27e8(void* first, void* last);       // 0x00dfe910 ret 8
    void DestroyRange534(void* first, void* last);        // 0x00dfdf10 ret 8
    void DestroyRangeVariant(void* first, void* last);    // 0x00685a30 ret 8
};

// 0x2c84-byte editor resource: message handler, vectors, three strings and a
// tracer object.  Handles for the original member offsets.
struct cUISpaceRes {
    void*     mpVtbl00;                              // +0x0000
    uint32_t  mPad04[(0x18 - 0x04) / 4];
    void*     mpVtbl18;                              // +0x0018
    uint32_t  mPad1c[(0x30 - 0x1c) / 4];
    VecAny    mVec30;                                // +0x0030  EA::Variant vector
    uint32_t  mPad3c[(0x48 - 0x3c) / 4];
    void*     mpTracer48;                            // +0x0048  object with a virtual dtor
    uint32_t  mPad4c[(0x7c - 0x4c) / 4];
    CStr      mStr7c;                                // +0x007c
    CStr      mStrB8;                                // +0x00b8
    CStr      mStrF4;                                // +0x00f4
    uint32_t  mPad130[(0x178 - 0x130) / 4];
    void*     mpOwned178;                            // +0x0178  owned allocation ([-4] flag)
    uint32_t  mPad17c[(0x23c - 0x17c) / 4];
    VecAny    mPod23c;                               // +0x023c  eastl::pod_array<0x534>
    uint32_t  mPad248[(0x2bf4 - 0x248) / 4];
    VecAny    mVec2bf4;                              // +0x2bf4  vector of 0x27e8 elements
    uint32_t  mPad2c00[(0x2c10 - 0x2c00) / 4];
    VecAny    mVec2c10;                              // +0x2c10  vector of unnamed elements
    uint32_t  mPad2c1c[(0x2c54 - 0x2c1c) / 4];
    void*     mpRaw2c54;                             // +0x2c54  raw allocation
    uint32_t  mPad2c58[(0x2c6c - 0x2c58) / 4];
    VecAny    mVec2c6c;                              // +0x2c6c  vector of 0x27e0 elements
    uint32_t  mPad2c78[(0x2c80 - 0x2c78) / 4];
    void*     mpOwned2c80;                           // +0x2c80  owned allocation ([-4] flag)
    void Destroy();                                  // 0x00dfef70  destructor body
};

// eastl frees an element block only when the four bytes before it (the
// "owned" flag) are set; a raw new/delete block has no such flag.
static inline void OwnedFree(void* p) {
    if (p && ((int*)p)[-1] != 0)
        EA_Free(p);
}

static inline void RawFree(void* p) {
    if (p)
        EA_Free(p);
}

// @ 0x00dfef70
void cUISpaceRes::Destroy() {
    OwnedFree(mpOwned2c80);
    mVec2c6c.DestroyRange(mVec2c6c.mpBegin, mVec2c6c.mpEnd);       // 0x00dfdf70
    OwnedFree(mVec2c6c.mpBegin);
    RawFree(mpRaw2c54);
    mVec2c10.DestroyRangeUnk(mVec2c10.mpBegin, mVec2c10.mpEnd);    // 0x00dfd300
    RawFree(mVec2c10.mpBegin);
    mVec2bf4.DestroyRange27e8(mVec2bf4.mpBegin, mVec2bf4.mpEnd);   // 0x00dfe910
    RawFree(mVec2bf4.mpBegin);
    mPod23c.DestroyRange534(mPod23c.mpBegin, mPod23c.mpEnd);       // 0x00dfdf10
    OwnedFree(mPod23c.mpBegin);
    OwnedFree(mpOwned178);
    mStrF4.Destroy();
    mStrB8.Destroy();
    mStr7c.Destroy();
    if (mpTracer48)
        ((void (__thiscall*)(void*))(*(void***)mpTracer48)[1])(mpTracer48);
    mVec30.DestroyRangeVariant(mVec30.mpBegin, mVec30.mpEnd);      // 0x00685a30
    RawFree(mVec30.mpBegin);
    mpVtbl00 = (void*)0x13eb938;
    mpVtbl18 = (void*)0x13eb938;
}

// ===========================================================================
//  0x00dff130  element-wise assign for the 0x27e8 class (from a fresh object)
// ===========================================================================
// @ 0x00dff130
void* ElemB::Init(void* o) {
    void* s = this;
    ((Buf3c*)s)->Copy(o);
    ((Buf3c*)((char*)s + 0x3c))->Copy((char*)o + 0x3c);
    *(uint32_t*)((char*)s + 0x78) = *(uint32_t*)((char*)o + 0x78);
    *(uint8_t*)((char*)s + 0x7c) = *(uint8_t*)((char*)o + 0x7c);
    *(uint32_t*)((char*)s + 0x80) = *(uint32_t*)((char*)o + 0x80);
    *(void**)((char*)s + 0x84) = (char*)s + 0x9c;
    *(void**)((char*)s + 0x88) = (char*)s + 0x9c;
    *(void**)((char*)s + 0x98) = 0;
    *(void**)((char*)s + 0x8c) = (char*)s + 0x534;
    ((V188*)((char*)s + 0x84))->Assign((V188*)((char*)o + 0x84));
    return s;
}

// ===========================================================================
//  0x00dff1a0  copy-ctor for the 0x2788 element class
// ===========================================================================
// @ 0x00dff1a0
void* ElemA::CopyCtor(void* o) {
    void* s = this;
    for (int i = 0; i < 8; ++i) ((uint32_t*)s)[i] = ((uint32_t*)o)[i];
    *(uint8_t*)((char*)s + 0x20) = *(uint8_t*)((char*)o + 0x20);
    *(uint32_t*)((char*)s + 0x24) = *(uint32_t*)((char*)o + 0x24);
    for (int i = 0; i < 8; ++i) ((uint32_t*)((char*)s + 0x28))[i] = ((uint32_t*)((char*)o + 0x28))[i];
    *(uint32_t*)((char*)s + 0x48) = *(uint32_t*)((char*)o + 0x48);
    for (int i = 0; i < 8; ++i) ((uint32_t*)((char*)s + 0x50))[i] = ((uint32_t*)((char*)o + 0x50))[i];
    *(void**)((char*)s + 0x70) = (char*)s + 0x88;
    *(void**)((char*)s + 0x74) = (char*)s + 0x88;
    *(void**)((char*)s + 0x78) = (char*)s + 0x2788;
    *(void**)((char*)s + 0x84) = 0;
    ((V4e0*)((char*)s + 0x70))->Assign((V4e0*)((char*)o + 0x70));
    ((Buf3c*)((char*)s + 0x2788))->Copy((char*)o + 0x2788);
    *(uint32_t*)((char*)s + 0x27c4) = *(uint32_t*)((char*)o + 0x27c4);
    *(uint32_t*)((char*)s + 0x27c8) = *(uint32_t*)((char*)o + 0x27c8);
    *(uint32_t*)((char*)s + 0x27cc) = *(uint32_t*)((char*)o + 0x27cc);
    *(uint32_t*)((char*)s + 0x27d0) = *(uint32_t*)((char*)o + 0x27d0);
    *(uint32_t*)((char*)s + 0x27d8) = *(uint32_t*)((char*)o + 0x27d8);
    *(uint32_t*)((char*)s + 0x27dc) = *(uint32_t*)((char*)o + 0x27dc);
    return s;
}

// ===========================================================================
//  0x00dff330  vector assign, stride 0x238
// ===========================================================================
// eastl vector assign: if the destination has no room, allocate and copy the
// whole source range; if it has room, copy the elements that fit and then
// move the rest; otherwise copy and destroy the tail of the old range.
struct V238 {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    V238* Assign(V238* other);                       // 0x00dff330 ret 4
    void* Alloc(uint32_t n, void* f, void* l);       // 0x00dff0d0 ret 0xc
    void  DestroyRange(void* f, void* l);            // 0x00dfd300 ret 8
};
struct V534 {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    V534* Assign(V534* other);                       // 0x00dff650 ret 4
    void* Alloc(uint32_t n, void* f, void* l);       // 0x00dff530 ret 0xc
    void  DestroyRange(void* f, void* l);            // 0x00dfdf10 ret 8
};
extern "C" void* __cdecl FUN_00dfe9a0(void* f, void* l, void* d);                 // 0x00dfe9a0
extern "C" void* __cdecl FUN_00dff270(void* f, void* l, void* d);                 // 0x00dff270
extern "C" void  __cdecl FUN_00dfeaa0(void** out, void* f, void* l, void* d, void* o); // 0x00dfeaa0
extern "C" void  __cdecl FUN_00dff460(void** out, void* f, void* l, void* d, void* o); // 0x00dff460

// @ 0x00dff330
V238* V238::Assign(V238* other) {
    if (other == this)
        return this;
    char* oEnd = (char*)other->mpEnd;
    char* oBeg = (char*)other->mpBegin;
    uint32_t nOther = (uint32_t)((oEnd - oBeg) / 0x238);
    char* sBeg = (char*)mpBegin;
    if (nOther > (uint32_t)(((char*)mpCapacity - sBeg) / 0x238)) {
        char* p = (char*)Alloc(nOther, oBeg, oEnd);
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin)
            EA_Free(mpBegin);
        mpBegin = p;
        mpCapacity = p + nOther * 0x238;
    } else {
        uint32_t nHave = (uint32_t)(((char*)mpEnd - sBeg) / 0x238);
        if (nOther > nHave) {
            FUN_00dfe9a0(oBeg, oBeg + nHave * 0x238, sBeg);
            FUN_00dfeaa0((void**)&other,
                         (char*)other->mpBegin +
                             (((char*)mpEnd - (char*)mpBegin) / 0x238) * 0x238,
                         other->mpEnd, mpEnd, other);
        } else {
            void* e = FUN_00dfe9a0(oBeg, oEnd, sBeg);
            DestroyRange(e, mpEnd);
        }
    }
    mpEnd = (char*)mpBegin + nOther * 0x238;
    return this;
}

// @ 0x00dff650
V534* V534::Assign(V534* other) {
    if (other == this)
        return this;
    char* oEnd = (char*)other->mpEnd;
    char* oBeg = (char*)other->mpBegin;
    uint32_t nOther = (uint32_t)((oEnd - oBeg) / 0x534);
    char* sBeg = (char*)mpBegin;
    if (nOther > (uint32_t)(((char*)mpCapacity - sBeg) / 0x534)) {
        char* p = (char*)Alloc(nOther, oBeg, oEnd);
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            EA_Free(mpBegin);
        mpBegin = p;
        mpCapacity = p + nOther * 0x534;
    } else {
        uint32_t nHave = (uint32_t)(((char*)mpEnd - sBeg) / 0x534);
        if (nOther > nHave) {
            FUN_00dff270(oBeg, oBeg + nHave * 0x534, sBeg);
            FUN_00dff460((void**)&other,
                         (char*)other->mpBegin +
                             (((char*)mpEnd - (char*)mpBegin) / 0x534) * 0x534,
                         other->mpEnd, mpEnd, other);
        } else {
            void* e = FUN_00dff270(oBeg, oEnd, sBeg);
            DestroyRange(e, mpEnd);
        }
    }
    mpEnd = (char*)mpBegin + nOther * 0x534;
    return this;
}

// ===========================================================================
//  0x00dff4e0  uninitialized_copy, stride 0x27e8
// ===========================================================================
// @ 0x00dff4e0
void** UninitCopy27e8(void** dstp, int* first, int* last, int val) {
    *dstp = (void*)val;
    while (first != last) {
        char* d = (char*)*dstp;
        if (d != 0) {
            *(int*)d = *first;
            ((ElemA*)(d + 8))->CopyCtor(first + 2);
        }
        *dstp = (char*)*dstp + 0x27e8;
        first = (int*)((char*)first + 0x27e8);
    }
    return dstp;
}

// 0x00dff650 is the same assign for stride 0x534; its body is next to the
// 0x238 version above (V534::Assign).
