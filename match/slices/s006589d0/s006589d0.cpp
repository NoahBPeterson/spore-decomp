// slice s006589d0: SP::cSPUIAssetView mouse/update methods.
// UI module: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <intrin.h>

// ---------------------------------------------------------------------------
// Raw virtual-call helpers (vtable byte offsets, as in the retail code).
// ---------------------------------------------------------------------------
inline void  vc0(void* p, int off) { ((void(__thiscall*)(void*))(*(void**)((char*)*(void**)p + off)))(p); }
inline void  vc1(void* p, int off, int a) { ((void(__thiscall*)(void*, int))(*(void**)((char*)*(void**)p + off)))(p, a); }
inline void  vc2(void* p, int off, int a, int b) { ((void(__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)p + off)))(p, a, b); }
inline int   vcr0(void* p, int off) { return ((int(__thiscall*)(void*))(*(void**)((char*)*(void**)p + off)))(p); }
inline void* vcp0(void* p, int off) { return ((void*(__thiscall*)(void*))(*(void**)((char*)*(void**)p + off)))(p); }
inline void* vcp1(void* p, int off, void* a) { return ((void*(__thiscall*)(void*, void*))(*(void**)((char*)*(void**)p + off)))(p, a); }
inline int   vcri4(void* p, int off, int a, int b, int c, int d) {
    typedef int(__thiscall* F)(void*, int, int, int, int);
    return ((F)(*(void**)((char*)*(void**)p + off)))(p, a, b, c, d);
}
struct Vec3i { int x, y, z; };
inline int vcvec3(void* p, int off, Vec3i v, int d) {
    typedef int(__thiscall* F)(void*, Vec3i, int);
    return ((F)(*(void**)((char*)*(void**)p + off)))(p, v, d);
}
inline void  vc3(void* p, int off, int a, int b, int c) {
    ((void(__thiscall*)(void*, int, int, int))(*(void**)((char*)*(void**)p + off)))(p, a, b, c);
}

// ---------------------------------------------------------------------------
// External callees (retail addresses; resolved by the equivalence checker).
// ---------------------------------------------------------------------------
struct cSPUIAnimator {
    void RemoveAnimation(void* win, int channel);              // 0x007f6210
    void AddAnimation(void* target, void* win, int channel);   // 0x007f8d10
};

void* __cdecl AssetBrowser();                                  // 0x00401030
void* __cdecl MessageServer();                                 // 0x0067dcc0
void* __cdecl GetSystemAT();                                   // 0x00a206f0
void  __cdecl KillSetiEffects(int id, int handle);             // 0x00435ed0
float __cdecl GetElapsedSeconds(float dur, int a, void* win, int b);  // 0x00805080
float __cdecl GetPropertyF(void* obj, unsigned int id, float def);    // 0x004e1c70
void  __cdecl FUN_008082f0(void* win, float a, float b);       // 0x008082f0
void  __cdecl FUN_00808190(void* win, float a, float b);       // 0x00808190
void  __cdecl SetGlobalProperty(unsigned int id, float v);     // 0x005ca880
void  __cdecl FUN_00572020(void* p, int b);                    // 0x00572020
void* __cdecl FUN_0067dd60();                                  // 0x0067dd60
void  __cdecl FUN_0103a330(void* a, void* b);                  // 0x0103a330
void  __cdecl FUN_00657370();                                  // 0x00657370
void  __cdecl FUN_00657a30(void* self, int a, int b, int c, int d, int e);  // 0x00657a30 (SelectAsset)
void* __cdecl AllocDbg(int size, const void* tag, int a, int b, int c, int d);  // 0x00f473a0

struct LimitStopwatch {
    void SetTimeLimit(int ms, int flag);                       // 0x0093a480
    bool IsDone();                                             // 0x005ff1c0
};

struct IAssetViewWin {
    void Show();                                               // 0x00657810
    void SetFirstUpdate(int first);                            // 0x00657930
};

struct cSPUILayout2 {
    void Shutdown(int flag);                                   // 0x00811ad0
    void SetParentWin(void* parent, int a, unsigned int id);   // 0x008121b0
    void SetReloadCallback(void* fn, void* self);              // 0x00810090
};

// Animation construction helpers (cdecl, first argument is the result buffer).
void* __cdecl CreateTimerInterpolation(void* out, float t);            // 0x007f7eb0
void* __cdecl CreatePositionTarget(void* out, void* win, float x, float y, void* timer);  // 0x007f7050
void* __cdecl CreateSizeTarget(void* out, void* win, float* size, void* timer);  // 0x007f73e0
void* __cdecl CreateShadeTarget(void* out, void* win, int shade, void* timer);   // 0x007f75d0
void* __cdecl CreateScaleTarget(void* out, void* win, float scale, void* timer); // 0x007f7340
void* __cdecl CreateRawTarget(void* out, void* win, float x, float y, void* timer);  // 0x007f7100
void* __cdecl CreateCallbackTarget(void* out, void* cb, void* p, void* variant); // 0x007f7830
void* __cdecl CreateSequenceTarget(void* out, void* innerOut);          // 0x007f9340
inline void SequenceAdd(void* seq, void* target, void* win, int channel) {
    ((void(__thiscall*)(void*, void*, void*, int))0x007f8fd0)(seq, target, win, channel);
}
inline void VariantDestruct(void* v, int flag) {
    ((void(__cdecl*)(void*, int))0x0093db80)(v, flag);
}

struct IStopwatchHolder {
    void Reset(int a);                                         // 0x00834c60
    void Unk();                                                // 0x00834e30
};

struct IImageSlot {
    void Set(void* handle);                                    // 0x00576650
};


// ---------------------------------------------------------------------------
// Data / vtable symbols.
// ---------------------------------------------------------------------------
extern int gAllocTag;         // 0x013f6b3c
extern int gVt13ef094;        // 0x013ef094
extern int gVt13ff800;        // 0x013ff800
extern int gVt13ff7fc;        // 0x013ff7fc
extern int gVt6400;           // 0x013f6400
extern int gVt63fc;           // 0x013f63fc

// Temporary animation target / timer records.
struct AnimTargetX {
    void* vtbl;   // +0x00
    void* update; // +0x04
    void* vtbl2;  // +0x08
    void* ref;    // +0x0c
    void* win;    // +0x10
    int   p14;    // +0x14
    int   p18;    // +0x18
    int   p1c;    // +0x1c
};
struct TimerX {
    void* vtbl;   // +0x00
    void* ref;    // +0x04
};
inline void EndTarget(AnimTargetX* t) {
    t->vtbl = &gVt6400;
    t->vtbl2 = &gVt63fc;
    if (t->ref) vc0(t->ref, 4);
}
inline void EndTimer(TimerX* t) {
    t->vtbl = &gVt63fc;
    if (t->ref) vc0(t->ref, 4);
}
inline void ClearRelease(void** slot) {
    void* p = *slot;
    if (p) {
        *slot = 0;
        vc0(p, 4);
    }
}
inline void AssignWin(void** slot, void* p) {
    void* old = *slot;
    if (p != old) {
        if (p) vc0(p, 0);
        *slot = p;
        if (old) vc0(old, 4);
    }
}
// EA intrusive refcount release sequence (Interlocked decrement then revive if <= 0).
inline void ReleaseRefCount(void* p) {
    volatile long* rc = (volatile long*)((char*)p + 8);
    _InterlockedExchangeAdd(rc, -1);
    if (_InterlockedExchangeAdd(rc, 0) < 1) _InterlockedExchangeAdd(rc, 1);
    else _InterlockedExchangeAdd(rc, 0);
}

// Message object allocated by FUN_00658c70.
struct MsgObj {
    void* vtbl;    // +0x00
    void* vtbl2;   // +0x04
    void* p08;     // +0x08
    void* p0c;     // +0x0c
    char  b10;     // +0x10
    void* p14;     // +0x14
    char  b18;     // +0x18
    char  b19;     // +0x19
};

// Entry points (member functions so the compiler emits __thiscall).
struct cSPUIAssetViewS {
    void OnLeftMouseDown(char param2);
    void RolloverHelper(void* ev);
    void SelectUpdate();
    bool RefreshResources();
    void ReleaseResources();
    void Cleanup();
};

// @ 0x006589d0  SP::cSPUIAssetView::OnLeftMouseDown
void cSPUIAssetViewS::OnLeftMouseDown(char param2) {
    char* s = (char*)this;
    if (*(void**)(s + 0x28) != 0 && *(void**)(s + 0x2c) != 0 &&
        (s[0xf4] != 0 || param2 != 0)) {
        void* ab = AssetBrowser();
        void* anim = 0;
        if (ab) {
            ab = AssetBrowser();
            anim = *(void**)((char*)ab + 0x14);
        }
        if (anim) {
            float* r = (float*)vcp0(*(void**)(s + 0x28), 0x38);
            float w = r[2] - r[0];
            float h = r[3] - r[1];
            ((cSPUIAnimator*)anim)->RemoveAnimation(*(void**)(s + 0x2c), 1);
            ((cSPUIAnimator*)anim)->RemoveAnimation(*(void**)(s + 0x2c), 0);
            {
                AnimTargetX t;
                TimerX tm;
                void* win = *(void**)(s + 0x2c);
                float e = GetElapsedSeconds(0.1f, 2, win, 1);
                CreateTimerInterpolation(&tm, e);
                void* target = CreatePositionTarget(&t, win, 0.0f, 0.0f, &tm);
                ((cSPUIAnimator*)anim)->AddAnimation(target, win, 1);
                EndTarget(&t);
                EndTimer(&tm);
            }
            {
                AnimTargetX t;
                TimerX tm;
                float wh[2];
                void* win = *(void**)(s + 0x2c);
                wh[0] = w;
                wh[1] = h;
                float e = GetElapsedSeconds(0.1f, 2, win, 0);
                CreateTimerInterpolation(&tm, e);
                void* target = CreateSizeTarget(&t, win, wh, &tm);
                ((cSPUIAnimator*)anim)->AddAnimation(target, win, 0);
                EndTarget(&t);
                EndTimer(&tm);
            }
            if (*(void**)(s + 0x94)) {
                ((IStopwatchHolder*)*(void**)(s + 0x94))->Reset(0);
                ((IStopwatchHolder*)*(void**)(s + 0x94))->Unk();
                if (*(void**)(s + 0x94)) {
                    void* p = *(void**)(s + 0x94);
                    *(void**)(s + 0x94) = 0;
                    vc0(p, 8);
                }
            }
        }
        if (*(void**)(s + 0x38)) {
            vc2(*(void**)(s + 0x38), 0x7c, 1, 0);
            ((IAssetViewWin*)this)->SetFirstUpdate(*(unsigned char*)(s + 0x15));
        }
        if (*(void**)(s + 0x78)) vc2(*(void**)(s + 0x78), 0x7c, 1, 0);
        if (*(void**)(s + 0x7c)) vc2(*(void**)(s + 0x7c), 0x7c, 1, 0);
        if (*(void**)(s + 0x80)) vc2(*(void**)(s + 0x80), 0x7c, 1, 0);
        if (*(void**)(s + 0x84)) vc2(*(void**)(s + 0x84), 0x7c, 1, 0);
        *(int*)(s + 0xd0) = 0;
        *(int*)(s + 0xd4) = 0;
        *(int*)(s + 0xd8) = 0;
        *(int*)(s + 0xdc) = 0;
    }
    if (*(void**)(s + 0x100)) {
        FUN_00572020(*(void**)(s + 0x100), 0);
        *(void**)(s + 0x100) = 0;
        SetGlobalProperty(0x8dff6314u, 0.0f);
    }
}

// @ 0x00658c70  SP::cSPUIAssetView rollover/state helper
void cSPUIAssetViewS::RolloverHelper(void* ev) {
    char* s = (char*)this;
    if (s[0xf4] == 0) {
        MsgObj* o = (MsgObj*)AllocDbg(0x1c, &gAllocTag, 0, 0, 0, 0);
        if (o == 0) {
            o = 0;
        } else {
            *(void* volatile*)&o->vtbl2 = &gVt13ef094;
            *(void* volatile*)&o->p08 = 0;
            *(void* volatile*)&o->vtbl = &gVt13ff800;
            *(void* volatile*)&o->vtbl2 = &gVt13ff7fc;
            *(void* volatile*)&o->p0c = 0;
            o->b10 = 0;
            *(void* volatile*)&o->p14 = 0;
            o->b18 = 0;
            o->b19 = 0;
            vc0(o, 4);
        }
        void* srv = MessageServer();
        vc3(srv, 0x14, (int)0x94174b89, (int)o, 0);
        if (o) vc0(o, 8);
        return;
    }
    if (*(int*)(s + 0xd0) != 0 || *(int*)(s + 0xd4) != 0) {
        LimitStopwatch* ls = (LimitStopwatch*)(s + 0xd0);
        if (ls->IsDone()) {
            ls->SetTimeLimit(500, 1);
            return;
        }
        if ((*(unsigned char*)((char*)ev + 0x14) & 3) != 0)
            return;
        void* srv = MessageServer();
        vc3(srv, 0x14, (int)0x0141a7b3, 0, 0);
        return;
    }
    char local_c = 0;
    char local_10 = 0;
    unsigned int flags = *(unsigned int*)((char*)ev + 0x14);
    if ((flags & 2) != 0) {
        local_10 = 1;
        local_c = 0;
    } else if ((flags & 1) != 0) {
        local_10 = 1;
        local_c = 1;
    } else {
        ((LimitStopwatch*)(s + 0xd0))->SetTimeLimit(500, 1);
    }
    FUN_00657a30((void*)this, 0, 1, 0, local_10, local_c);
    void* audio = GetSystemAT();
    int handle = audio ? vcr0(audio, 0x20) : 0;
    KillSetiEffects((int)0x49cfcdd2, handle);
}

// @ 0x00658e80  SP::cSPUIAssetView selection animation update
void cSPUIAssetViewS::SelectUpdate() {
    char* s = (char*)this;
    void* ab = AssetBrowser();
    void* anim = 0;
    if (ab) {
        ab = AssetBrowser();
        anim = *(void**)((char*)ab + 0x14);
    }
    if (anim != 0 && *(void**)(s + 0x28) != 0) {
        void* win = *(void**)(s + 0x28);
        ((cSPUIAnimator*)anim)->RemoveAnimation(win, -1);
        int shade = vcr0(win, 0x30);
        vc1(win, 0x5c, shade & 0xffffff);
        float dur = 0.1f;
        void* ab2 = AssetBrowser();
        if (ab2 != 0 && *(void**)((char*)ab2 + 0x18) != 0) {
            void* ab3 = AssetBrowser();
            dur = GetPropertyF(*(void**)((char*)ab3 + 0x18), 0x24ccfb15u, 0.1f);
        }
        float* r1 = (float*)vcp0(win, 0x38);
        float halfW = (r1[2] - r1[0]) * 0.5f;
        float* r2 = (float*)vcp0(win, 0x38);
        float halfH = (r2[3] - r2[1]) * 0.5f;
        FUN_008082f0(win, 0.0f, 0.0f);
        FUN_00808190(win, 1.52587890625e-05f, 1.52587890625e-05f);
        {
            AnimTargetX t;
            TimerX tm;
            float e = GetElapsedSeconds(dur, 2, win, 4);
            CreateTimerInterpolation(&tm, e);
            void* target = CreateShadeTarget(&t, win, shade, &tm);
            ((cSPUIAnimator*)anim)->AddAnimation(target, win, 4);
            EndTarget(&t);
            EndTimer(&tm);
        }
        AnimTargetX seq;
        void* seqObj = 0;
        CreateSequenceTarget(&seq, &seqObj);
        {
            AnimTargetX t;
            TimerX tm;
            float e = GetElapsedSeconds(dur * 0.5f, 0, win, 5);
            CreateTimerInterpolation(&tm, e);
            void* target = CreateRawTarget(&t, win, -halfW, -halfH, &tm);
            SequenceAdd(seqObj, target, win, 5);
            EndTarget(&t);
            EndTimer(&tm);
        }
        {
            AnimTargetX t;
            int variant[3];
            variant[0] = 0;
            variant[1] = 0;
            variant[2] = 0;
            void* target = CreateCallbackTarget(&t, (void*)FUN_00657370, 0, variant);
            SequenceAdd(seqObj, target, win, 5);
            EndTarget(&t);
            if (((unsigned char*)variant)[0] & 4)
                VariantDestruct(variant, 0);
        }
        {
            AnimTargetX t;
            TimerX tm;
            float e = GetElapsedSeconds(dur, 2, win, 5);
            CreateTimerInterpolation(&tm, e);
            void* target = CreateRawTarget(&t, win, 0.0f, 0.0f, &tm);
            SequenceAdd(seqObj, target, win, 5);
            EndTarget(&t);
            EndTimer(&tm);
        }
        ((cSPUIAnimator*)anim)->AddAnimation(&seq, win, 5);
        {
            AnimTargetX t;
            TimerX tm;
            float e = GetElapsedSeconds(dur, 2, win, 2);
            CreateTimerInterpolation(&tm, e);
            void* target = CreateScaleTarget(&t, win, 1.0f, &tm);
            ((cSPUIAnimator*)anim)->AddAnimation(target, win, 2);
            EndTarget(&t);
            EndTimer(&tm);
        }
        EndTarget(&seq);
    }
    return ((IAssetViewWin*)this)->Show();
}

// @ 0x00659270  SP::cSPUIAssetView resource refresh
bool cSPUIAssetViewS::RefreshResources() {
    char* s = (char*)this;
    void* p = *(void**)(s + 0x90);
    if (p != 0) {
        Vec3i tmp;
        void* mgr = FUN_0067dd60();
        Vec3i* q = (Vec3i*)vcp1(p, 0x18, &tmp);
        int handle = vcvec3(mgr, 0x1c, *q, 0);
        ((IImageSlot*)(s + 0x98))->Set((void*)handle);
        p = *(void**)(s + 0x90);
        mgr = FUN_0067dd60();
        q = (Vec3i*)vcp1(p, 0x1c, &tmp);
        handle = vcvec3(mgr, 0x1c, *q, 0);
        ((IImageSlot*)(s + 0x9c))->Set((void*)handle);
    }
    return *(void**)(s + 0x98) != 0 && *(void**)(s + 0x9c) != 0;
}

// @ 0x00659340  SP::cSPUIAssetView release resource references
void cSPUIAssetViewS::ReleaseResources() {
    char* s = (char*)this;
    if (*(void**)(s + 0x98)) {
        void* p = *(void**)(s + 0x98);
        *(void**)(s + 0x98) = 0;
        ReleaseRefCount(p);
    }
    if (*(void**)(s + 0x9c)) {
        void* p = *(void**)(s + 0x9c);
        *(void**)(s + 0x9c) = 0;
        ReleaseRefCount(p);
    }
}

// @ 0x006593c0  SP::cSPUIAssetView shutdown/cleanup
void cSPUIAssetViewS::Cleanup() {
    char* s = (char*)this;
    if (s[0xf5] == 0)
        return;
    s[0xf5] = 0;
    ReleaseResources();
    if (*(void**)(s + 0x88)) {
        vc0(*(void**)(s + 0x88), 0x18);
        ClearRelease((void**)(s + 0x88));
    }
    if (*(void**)(s + 0x28))
        vc1(*(void**)(s + 0x28), 0x108, (int)this);
    if (*(void**)(s + 0x54)) {
        void* q = vcp0(*(void**)(s + 0x54), 0x10);
        if (q) {
            q = vcp0(*(void**)(s + 0x54), 0x10);
            vc1(q, 0xe0, *(int*)(s + 0x54));
        }
    }
    ClearRelease((void**)(s + 0x28));
    ClearRelease((void**)(s + 0x30));
    ClearRelease((void**)(s + 0x34));
    ClearRelease((void**)(s + 0x38));
    ClearRelease((void**)(s + 0x3c));
    ClearRelease((void**)(s + 0x40));
    ClearRelease((void**)(s + 0x44));
    ClearRelease((void**)(s + 0x48));
    ClearRelease((void**)(s + 0x4c));
    ClearRelease((void**)(s + 0x50));
    ClearRelease((void**)(s + 0x54));
    ClearRelease((void**)(s + 0x58));
    ClearRelease((void**)(s + 0x5c));
    ClearRelease((void**)(s + 0x64));
    ClearRelease((void**)(s + 0x68));
    ClearRelease((void**)(s + 0x6c));
    ClearRelease((void**)(s + 0x70));
    ClearRelease((void**)(s + 0x74));
    ClearRelease((void**)(s + 0x78));
    ClearRelease((void**)(s + 0x7c));
    ClearRelease((void**)(s + 0x80));
    ClearRelease((void**)(s + 0x84));
    if (*(void**)(s + 0x88)) {
        vc0(*(void**)(s + 0x88), 0x18);
        ClearRelease((void**)(s + 0x88));
    }
    if (*(void**)(s + 0x8c)) {
        vc0(*(void**)(s + 0x8c), 0x18);
        ClearRelease((void**)(s + 0x8c));
    }
    if (*(void**)(s + 0x20)) {
        if (s[0x1c] != 0) {
            void* layout = *(void**)(s + 0x20);
            int count = *(int*)0x015f9f40;
            int i = 0;
            if (count > 0) {
                void** arr = *(void***)0x015fa018;
                while (i < count) {
                    if (arr[i] == layout) {
                        if (i < count)
                            FUN_0103a330(&arr[i], &arr[count - 1]);
                        break;
                    }
                    ++i;
                }
            }
            *(int*)0x015f9f40 = count - 1;
            ((cSPUILayout2*)*(void**)(s + 0x20))->SetParentWin(0, 0, 0x5b598fa);
            ((cSPUILayout2*)*(void**)(s + 0x20))->SetReloadCallback(0, 0);
        } else {
            ((cSPUILayout2*)*(void**)(s + 0x20))->Shutdown(1);
        }
        if (*(void**)(s + 0x20)) {
            void* p = *(void**)(s + 0x20);
            *(void**)(s + 0x20) = 0;
            return vc0(p, 8);
        }
    }
}
