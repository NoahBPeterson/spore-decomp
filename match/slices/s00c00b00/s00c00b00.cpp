// @ 0x00c00b00 -- SP::cCommunity::NotifyAttack(eAttackTrackingType, unsigned int)
//
// Reconstructed from the retail disassembly.  The retail cCommunity layout is eight bytes
// larger than the generated header from +0x2c upwards (the cISPEditorNameProvider subobject
// sits at +0x34), so the three attack stamps are at +0x98 and the player-warning timer at
// +0xb0.  The body records the attack time, posts the kUnderAttack slot message, and (outside
// the diplomatic attack) periodically warns the owning player; a second block advances a
// per-planet combat timer while the active game mode is 5.
//
// flags /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <intrin.h>

typedef unsigned int u32;
typedef unsigned __int64 u64;

// ---- engine entry points used by the body -----------------------------------------------
u32  SP_GetCurrentGameMode();                        // 0x00b5b800
void* SP_GetServer();                                // 0x00883860 EA::Messaging::GetServer
void* SP_NounManager();                              // 0x00b3d300
void* SP_GameTimeManager();                          // 0x00b3d380
void* SP_GetActivePlanetRecord();                    // 0x010212a0
void* SP_GetSpaceCombatTuning();                     // 0x01029940
void* SP_ConfigManager();                            // 0x0067dd30
void* SP_GetAudioSystem();                           // 0x00a206f0
u32   FNV1_String16(const wchar_t*, u32, int);       // 0x00932f30
void  FUN_00435ed0(u32, u32);                        // 0x00435ed0 (audio event post)
u32   FUN_00435e90();                                // 0x00435e90
void  FUN_0040cf10(void* mgr, u32 id, float* out);   // 0x0040cf10 GetPropertyT
void* FUN_00ac86d0(void*);                           // 0x00ac86d0
void* FUN_00b3d4d0();                                // 0x00b3d4d0 (message manager)

// Attacker position passed to the strategy warning method.  In retail the four floats are
// built as a temporary at the call site, so the stores interleave with the last argument
// pushes.
struct Vec4 {
    float x, y, z, w;
    Vec4(float fx, float fy, float fz, float fw) { x = fx; y = fy; z = fz; w = fw; }
};
void* FUN_00cf74c0();                                // 0x00cf74c0 cCivModeStrategy::Get()
void  FUN_00cf9040();                                // 0x00cf9040, thiscall warning on the strategy
void  FUN_00ae09b0();                                // 0x00ae09b0, thiscall send
void  FUN_00ae0930();                                // 0x00ae0930, thiscall send
void  FUN_00ad7a30();                                // 0x00ad7a30, thiscall ctor
void  FUN_00ad7ad0();                                // 0x00ad7ad0, thiscall dtor

// __thiscall helpers, declared without a prototype and cast at the call site.
void FUN_00b316c0();   // GameTimeManager::Ticks -> u64
void FUN_00b1f9d0();   // noun manager -> player civilization
void FUN_00b25f40();   // noun manager -> noun for an id
void FUN_00b25fb0();   // noun manager -> player civilization noun
void FUN_00b8dab0();   // active planet record -> type
void FUN_00f67d90();   // noun manager -> terrain object
void FUN_00bd9b40();   // cCity::GetCityHall
void FUN_00c772c0();   // bool (terrain object, id)
void FUN_00c77bf0();   // void (terrain object, id)

bool FUN_00c004c0();                                               // 0x00c004c0

extern const float g_Milli;   // 0x013f9428  0.001f (ticks -> seconds)
extern const float g_Sixty;   // 0x013ebc4c  60.0f
extern const float g_One;     // 0x01485720  1.0f

// The slot message's and the marker's vtables, and the vtable FUN_00ae0930 hands on as a message id
// (retail links absolute addresses at all three, so they must be names; cf. s004215f0's vtbl_UI_BehaviorMessage).
extern "C" char g_13eb90c[];  // 0x013eb90c  vtbl_UI::BehaviorMessage (symbols/vtable_names.txt)
extern "C" char g_13eb844[];  // 0x013eb844
extern "C" char g_1469ca8[];  // 0x01469ca8  (s00c011c0's constructor installs g_1469cc0/g_1469cd8 next to it)

#define VTABLE(obj)         (*(void***)(obj))
#define VSLOT(obj, off)     (VTABLE(obj)[(off) / 4])

// Ref-counted stack message used by the messaging server (see s01058950).
struct SlotMessage {
    void** vtbl;                    // +0x00
    u32    mRefCount;               // +0x04
    void*  mpObject;                // +0x08
    u32    m0c;                     // +0x0c
    u32    m10;                     // +0x10
    u32    m14;                     // +0x14
    u32    m18;                     // +0x18
    u32    m1c;                     // +0x1c
    u32    m20;                     // +0x20
    u32    m24;                     // +0x24
    u32    m28;                     // +0x28
    u32    m2c;                     // +0x2c
    u32    mKind;                   // +0x30
    u32    m34;                     // +0x34
    u32    m38;                     // +0x38
    u32    m3c;                     // +0x3c
    void Destruct();                // 0x00421cf0
};

namespace SP {

// On the retail layout the timer occupies +0xb0..+0xcf.
struct cSPTimer {
    unsigned char mData[0x20];
    void Restart();                          // 0x00bc3130
    u64  GetElapsedTime() const;             // 0x00bc3190
};

// Small stack object built from a city-hall position.
struct Marker {
    float v[3];
};

class cCommunity {
 public:
    enum eAttackTrackingType {
        kMilitaryAttack = 0,
        kCulturalAttack = 1,
        kDiplomaticAttack = 2,
        kAttackTypeCount = 3,
    };
    enum eCommunityMessages {
        kUnderAttack = 51027995,             // 0x030aa01b
    };

    void NotifyAttack(eAttackTrackingType, unsigned int);

    unsigned char mPad0[0x98];
    u64   mLastAttack[3];                    // 0x98
    cSPTimer mPlayerWarningTimer;            // 0xb0
};

}  // namespace SP

using SP::cCommunity;

// @ 0x00c00b00
void cCommunity::NotifyAttack(eAttackTrackingType type, unsigned int attackerId)
{
    unsigned char* const self = (unsigned char*)this;

    // The slot message and the later city-hall marker share one stack slot in retail.
    union Scratch {
        SlotMessage msg;
        SP::Marker marker;
    };
    Scratch scratch;

    bool isCivilizationMode = SP_GetCurrentGameMode() == 0x1654c02;
    bool isSpaceMode        = SP_GetCurrentGameMode() == 0x1654c04;

    if (isCivilizationMode ||
        !((bool (__thiscall*)(void*, int))FUN_00c004c0)(self, (int)type)) {
        scratch.msg.mKind = 0;
        scratch.msg.vtbl = (void**)g_13eb90c;
        _InterlockedExchange((long*)&scratch.msg.mRefCount, 0);
        scratch.msg.vtbl = (void**)g_13eb844;
        scratch.msg.m38 = 0;
        scratch.msg.mKind = kUnderAttack;
        scratch.msg.mpObject = self;
        scratch.msg.m10 = 0xffff0000;
        scratch.msg.m18 = (u32)type;
        scratch.msg.m20 = attackerId;

        void* server = SP_GetServer();
        ((void (__thiscall*)(void*, u32, void*, int))VSLOT(server, 0x14))
            (server, scratch.msg.mKind, &scratch.msg, 0);
        scratch.msg.Destruct();
    }

    mLastAttack[type] = ((u64 (__thiscall*)(void*))FUN_00b316c0)(SP_GameTimeManager());

    if (type != kDiplomaticAttack && isSpaceMode) {
        int playerCiv = ((int (__thiscall*)(void*))FUN_00b1f9d0)(SP_NounManager());
        if (((int (__thiscall*)(void*))VSLOT(self, 0x4c))(self) == playerCiv) {
            if (mPlayerWarningTimer.GetElapsedTime() > 15000) {
                void* attacker = ((void* (__thiscall*)(void*, u32))FUN_00b25f40)
                    (SP_NounManager(), attackerId);
                if (attacker == 0) {
                    attacker = ((void* (__thiscall*)(void*))FUN_00b25fb0)(SP_NounManager());
                }

                float communityPos[3];
                ((void (__thiscall*)(void*, float*))VSLOT(self, 0x5c))(self, communityPos);

                void* nameProvider = self + 0x34;
                const wchar_t* name = ((const wchar_t* (__thiscall*)(void*))
                                       VSLOT(nameProvider, 0x04))(nameProvider);
                u32 nameHash = FNV1_String16(name, 0x811c9dc5u, 1);

                void* iface = ((void* (__thiscall*)(void*, u32))VSLOT(self, 0x0c))
                    (self, 0xee9b2232u);

                ((void (__thiscall*)(void*, void*, u32, u32, const float*,
                                     const Vec4&, int, u32))FUN_00cf9040)
                    (FUN_00cf74c0(), iface, 0x38320b95u, 0xaa9a8ed7u, communityPos,
                     Vec4(*(float*)((unsigned char*)attacker + 0xc4),
                          *(float*)((unsigned char*)attacker + 0xc8),
                          *(float*)((unsigned char*)attacker + 0xcc),
                          g_One),
                     0, nameHash);
                FUN_00435ed0(0xb3f166fdu, 0x387cfa0u);

                void* cfg = SP_ConfigManager();
                if (((int (__thiscall*)(void*, u32))VSLOT(cfg, 0x30))(cfg, 0x4ea96cbu) != 0) {
                    void* terrain = ((void* (__thiscall*)(void*))FUN_00f67d90)
                        (SP_NounManager());
                    if (!((bool (__thiscall*)(void*, u32))FUN_00c772c0)
                            (terrain, 0x5b86eb6u)) {
                        ((void (__thiscall*)(void*, u32))FUN_00c77bf0)(terrain, 0x5b86eb6u);

                        void* cityHall = ((void* (__thiscall*)(void*))FUN_00bd9b40)
                            (FUN_00ac86d0(self));
                        unsigned char* markerPos = cityHall
                            ? (unsigned char*)cityHall + 0x34 : 0;

                        ((void (__thiscall*)(void*, void*))FUN_00ad7a30)
                            (&scratch.marker, markerPos);

                        ((void (__thiscall*)(void*, u32, void*, int))FUN_00ae09b0)
                            (FUN_00b3d4d0(), 0x48ecbb8au, &scratch.marker, 0);

                        ((void (__thiscall*)(void*, u32, int, int, int, int, int))
                         FUN_00ae0930)
                            (FUN_00b3d4d0(), (u32)g_1469ca8, 1, 0, 0, 0, 0);

                        ((void (__thiscall*)(void*))FUN_00ad7ad0)(&scratch.marker);
                    }
                }
            }
            mPlayerWarningTimer.Restart();
        }
    }

    if (SP_GetCurrentGameMode() == 0x1654c05) {
        void* record = SP_GetActivePlanetRecord();
        if (((int (__thiscall*)(void*))FUN_00b8dab0)(record) == 5) {
            float now = (float)(((u64 (__thiscall*)(void*))FUN_00b316c0)
                               (SP_GameTimeManager())) * g_Milli;
            float* field = (float*)((unsigned char*)record + 0x12c);

            if (*field == 0.0f) {
                *field = now;
                void* audio = SP_GetAudioSystem();
                u32 value = audio
                    ? ((u32 (__thiscall*)(void*))VSLOT(audio, 0x20))(audio) : 0;
                FUN_00435ed0(0xe00c599au, value);
            } else if (*field < 0.0f) {
                float limit = g_Sixty;
                void* tuning = SP_GetSpaceCombatTuning();
                void** sub = (void**)((unsigned char*)tuning + 8);
                FUN_0040cf10(*sub, 0x5c2cbea, &limit);
                if (*field + now > limit) {
                    *field = now;
                    FUN_00435ed0(0xe00c599au, FUN_00435e90());
                }
            }
        }
    }
}
