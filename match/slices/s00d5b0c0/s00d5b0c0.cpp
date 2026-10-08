// Slice s00d5b0c0: SP::cCityVisualizer::UpdateBackgroundNoise (0x00d5b0c0).
//
// Retail layout differs from the 2008 PDB, so members are accessed by retail byte offset
// (F<T>(p, off)), as in the sibling slices s00d5fb60 / s00d60ce0.
//
// Picks the background noise (crowd / siren / religious ...) from the visualised city's state, then
// starts or stops the looping sounds: the event noise (timer 0xb28), the "set-i" noise (0xb50/0xb54)
// and the capture noise (0xb4c).
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include <string.h>
typedef unsigned int u32;
typedef unsigned long long u64;

template <class T> static inline T& F(void* p, int off) { return *(T*)((char*)p + off); }

struct Vec3 { float x, y, z; };

template <class R> static inline R VC0(void* o, int slot) {
    typedef R(__thiscall * Fn)(void*);
    return ((Fn)(*(void***)o)[slot])(o);
}
template <class R, class A> static inline R VC1(void* o, int slot, A a) {
    typedef R(__thiscall * Fn)(void*, A);
    return ((Fn)(*(void***)o)[slot])(o, a);
}

struct Timer {
    u64  GetElapsedTime();          // 0x00bc3190
    void Restart();                 // 0x00bc3130
};
struct AudioSystem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual u32  Create();                           // 0x20
    virtual void v24();
    virtual bool IsPlaying(u32 h);                   // 0x28
    virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void Begin(u32 id);                      // 0x38
    virtual void v3c();
    virtual void SetParam(u32 id, u32 value);        // 0x40
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void Commit();                           // 0x58
};
AudioSystem* GetSystemAT();                          // 0x00a206f0

struct NounMgr { int GetPlayerEmpireOrMinus1(); };   // 0x00b1f9d0
NounMgr* __cdecl NounManager();                      // 0x00b3d300
struct CivStrategy { bool FUN_00cf7a90(); };         // 0x00cf7a90
CivStrategy* __cdecl CivModeStrategyGet();           // 0x00cf74c0

struct City {
    bool  FUN_00bd7df0();                            // 0x00bd7df0
    float FUN_00bd7d00();                            // 0x00bd7d00
    bool  FUN_00c004c0(int);                         // 0x00c004c0
    bool  FUN_00bd8f30();                            // 0x00bd8f30
    void* FUN_00bd8d60(int i);                       // 0x00bd8d60
    void  FUN_00bd9480(Vec3* out);                   // 0x00bd9480
    void  FUN_00c00510(int);                         // 0x00c00510
    struct Vec* GetMembers();                        // 0x00c8e810
};
struct Vec { int begin, end; };
struct Creature {
    void StartIndependentSound(u32 snd, void* pos, void* handles);   // 0x00c1db40
};
struct SimGlobal {
    char pad[0x2c];
    int mode;                                        // +0x2c
};

u32 SP_GetCurrentGameMode();                         // 0x00b5b800
SimGlobal* FUN_00b3d4d0();                           // 0x00b3d4d0
void __cdecl FUN_00572020(u32 handle, int);          // 0x00572020
void __cdecl Start3dSoundByName(u32 snd, u32 handle, float x, float y, float z);   // 0x00571f80
void __cdecl KillSetiEffects(u32 a, u32 handle);     // 0x00435ed0
extern u32 g_tab147ba00[];                           // 0x0147ba00
extern u32 g_tab147b9f4[];                           // 0x0147b9f4
extern u32 g_tab01583e6c[];                          // 0x01583e6c


// Same body as the standalone StopAndClearSoundList (0x00d5adf0): stop every handle, then clear the vector.
static inline void StopSounds(Vec* hv)
{
    int i = 0;
    if (((hv->end - hv->begin) & ~3) > 0) {
        do {
            u32 hh = ((u32*)hv->begin)[i];
            AudioSystem* at = GetSystemAT();
            if (at) {
                at->Begin(0x347536b);
                at->SetParam(0x3475385, hh);
                at->SetParam(0x34753a0, 0);
                at->Commit();
            }
            i++;
        } while (i < (hv->end - hv->begin) >> 2);
    }
    u32* last = (u32*)hv->end;
    u32* first = (u32*)hv->begin;
    memcpy(first, last, (char*)last - (char*)last);
    hv->end += -((((int)last - (int)first) >> 2)) * 4;
}

struct Viz {
    void UpdateBackgroundNoise();                    // 0x00d5b0c0
};

#define CITY F<City*>(this, 0xaf0)

// @ 0xd5b0c0
void Viz::UpdateBackgroundNoise()
{
    if (F<int>(this, 0xa64) == F<int>(this, 0xa68)) return;

    int  noise = 1;
    bool haveVec = false;
    Vec3 v = { 0.0f, 0.0f, 0.0f };
    Vec3 tmp;

    if (CITY->FUN_00bd7df0()) noise = 2;
    if (CITY->FUN_00bd7d00() > F<float>(this, 0xb18)) noise = 3;

    if (F<int>(this, 0xb20) < 8) {
        float delta = CITY->FUN_00bd7d00() - F<float>(this, 0xb58);
        F<float>(this, 0xb58) = CITY->FUN_00bd7d00();
        if (delta > 2.0f) {
            F<int>(this, 0xb20) = 5;
            F<u32>(this, 0xb48) = 3000;
            ((Timer*)((char*)this + 0xb28))->Restart();
        } else if (delta < -2.0f) {
            F<int>(this, 0xb20) = 6;
            F<u32>(this, 0xb48) = 3000;
            ((Timer*)((char*)this + 0xb28))->Restart();
        } else if (F<int>(this, 0x38c) != 0) {
            F<int>(this, 0xb20) = 7;
            F<u32>(this, 0xb48) = 2000;
            ((Timer*)((char*)this + 0xb28))->Restart();
        }
        if (CITY->FUN_00c004c0(0)) noise = 4;
    }

    if (CITY->FUN_00bd8f30()) {
        int pid = NounManager()->GetPlayerEmpireOrMinus1();
        int found = -1, other = -1;
        bool sawOwn = false;
        for (int i = 0; i < 4; i++) {
            void* c = CITY->FUN_00bd8d60(i);
            if (F<int>(c, 0x1d8) == 2) {
                if (i == F<int>(this, 0xb1c)) sawOwn = true;
                if (F<int>(c, 0x1dc) == pid) found = i;
                else other = i;
            }
        }
        if (found > -1) other = found;
        else if (sawOwn) other = F<int>(this, 0xb1c);
        F<int>(this, 0xb1c) = other;
        void* c2 = CITY->FUN_00bd8d60(other);
        if (F<float>(c2, 0x20c) > 0.85f) {
            noise = 0xb;
        } else if (F<float>(c2, 0x210) > 0.85f) {
            noise = 0xc;
        } else {
            goto noVec;
        }
        {
            haveVec = true;
            Vec3* p = VC0<Vec3*>((char*)c2 + 0x100, 0x2c / 4);
            ((u32*)&v)[0] = ((u32*)p)[0]; ((u32*)&v)[1] = ((u32*)p)[1]; ((u32*)&v)[2] = ((u32*)p)[2];
        }
    } else {
        F<int>(this, 0xb1c) = -1;
    }

noVec:
    Vec* members = CITY->GetMembers();
    if ((u32)((members->end - members->begin) >> 2) < 2 && SP_GetCurrentGameMode() == 0x1654c05)
        noise = 0;

    u32 h = F<u32>(this, 0xb50);
    if (h != 0) {
        AudioSystem* at = GetSystemAT();
        if (at == 0 || !at->IsPlaying(h)) {
            F<u32>(this, 0xb50) = 0;
            F<bool>(this, 0xb54) = false;
        }
    }
    if (F<u32>(this, 0xb50) != 0 && F<bool>(this, 0xb54)) {
        int mode = FUN_00b3d4d0()->mode;
        if (mode != 1 && mode != 2) {
            FUN_00572020(F<u32>(this, 0xb50), 0);
            F<bool>(this, 0xb54) = false;
            F<u32>(this, 0xb50) = 0;
        }
    }

    if (F<char>(CITY, 0x2a0) != 0) {
        int mode = FUN_00b3d4d0()->mode;
        bool indoors = (mode == 1 || mode == 2);
        F<int>(this, 0xb20) = F<int>(CITY, 0x29c) + 8;
        F<u32>(this, 0xb48) = 10000;
        ((Timer*)((char*)this + 0xb28))->Restart();
        AudioSystem* at = GetSystemAT();
        u32 nh = at ? at->Create() : 0;
        F<u32>(this, 0xb50) = nh;
        if (indoors) {
            KillSetiEffects(g_tab147ba00[F<int>(CITY, 0x29c)], nh);
            F<bool>(this, 0xb54) = true;
        } else if (!VC0<bool>((char*)CITY + 0x120, 0x58 / 4)) {
            CITY->FUN_00bd9480(&tmp);
            Start3dSoundByName(g_tab147b9f4[F<int>(CITY, 0x29c)], F<u32>(this, 0xb50), tmp.x, tmp.y, tmp.z);
        }
    }

    u64 elapsed = ((Timer*)((char*)this + 0xb28))->GetElapsedTime();
    if (elapsed < (u64)F<u32>(this, 0xb48) && F<int>(this, 0xb20) != 0)
        noise = F<int>(this, 0xb20);
    else
        F<int>(this, 0xb20) = 0;

    if (noise != F<int>(this, 0xb14)) {
        Vec* hv = (Vec*)((char*)this + 0xb00);
        F<int>(this, 0xb14) = noise;
        if (hv->begin != hv->end)
            StopSounds(hv);
        if (noise != 0) {
            Vec3* pos;
            if (haveVec) pos = &v;
            else pos = VC1<Vec3*, Vec3*>(CITY, 0x58 / 4, &tmp);
            ((Creature*)F<void*>(F<void*>(this, 0xa64), 0))->StartIndependentSound(g_tab01583e6c[noise], pos, hv);
        }
    }

    if (CivModeStrategyGet()->FUN_00cf7a90())
        CITY->FUN_00c00510(0);

    if (CITY->FUN_00c004c0(0)) {
        if (F<u32>(this, 0xb4c) == 0) {
            AudioSystem* at = GetSystemAT();
            F<u32>(this, 0xb4c) = at ? at->Create() : 0;
            CITY->FUN_00bd9480(&tmp);
            Start3dSoundByName(0xc0ba2669, F<u32>(this, 0xb4c), tmp.x, tmp.y, tmp.z);
        }
    } else if (F<u32>(this, 0xb4c) != 0) {
        u32 bh = F<u32>(this, 0xb4c);
        AudioSystem* at = GetSystemAT();
        if (at) {
            at->Begin(0x347536b);
            at->SetParam(0x3475385, bh);
            at->SetParam(0x34753a0, 0);
            at->Commit();
        }
        F<u32>(this, 0xb4c) = 0;
    }
}
