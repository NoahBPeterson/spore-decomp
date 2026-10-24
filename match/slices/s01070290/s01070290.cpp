// Slice s01070290: SP::cSPUISpace saved-games UI.
//   01070890  SP::cSPUISpace::ShowSavedGames   (thiscall)  - one row per star-manager civ that is
//             not the player's home planet: pull the "saved game" property from the effects manager,
//             stamp a 0x38-byte city record and append the property to the +0x308 pointer list.
//   01070af0  eastl::vector<SP::cSPUISpace::cFoodwebSlotInfo>::resize(uint)  (thiscall, ret 4)
// Everything that is not a plain field hangs off a vtable slot, so the vcall targets are declared as
// virtual functions of small classes whose layouts put them at the original offsets.
#include "types.h"
#include <stddef.h>

#define CHK(cls, name, off) typedef char chk_##cls##_##name[(offsetof(cls, name) == (off)) ? 1 : -1]

struct cProperty;
struct cSavedGameRec;

// 12-byte resource key (memory order: three dwords).
struct Key {
    uint32_t a, b, c;
};
extern Key gNullKey;                                    // 0x016e224c

struct Vec3 { float x, y, z; };
struct Matrix3 {
    float m[9];
    Matrix3() {}
    // User-defined copy ctor: retail copies the 3x3 through a stack temporary one float at a time
    // before storing it into the record.
    Matrix3(const Matrix3& o) {
        m[0] = o.m[0]; m[1] = o.m[1]; m[2] = o.m[2];
        m[3] = o.m[3]; m[4] = o.m[4]; m[5] = o.m[5];
        m[6] = o.m[6]; m[7] = o.m[7]; m[8] = o.m[8];
    }
};

// Default contents of a saved-game record: the identity-ish city transform, copied out of the
// engine's constant tables (Havok _HK_REAL_ONE for the w component).
extern const Vec3 kSavedGamePos;                        // 0x016e2824
extern const Matrix3 kSavedGameRot;                     // 0x016e2800
extern const float kOne;                                // 0x01485720  (_HK_REAL_ONE)

// ---------------------------------------------------------------------------
// 0x38-byte city record handed to cProperty::v14.
// ---------------------------------------------------------------------------
struct cSavedGameRec {
    uint16_t mFlags;                                    // +0x00
    uint16_t mCount;                                    // +0x02
    Vec3 mPos;                                          // +0x04
    float mW;                                           // +0x10
    Matrix3 mRot;                                       // +0x14
    // The matrix arrives by reference; retail copies it into a local temporary first (the class has
    // a user copy constructor) and then bit-copies that temporary into the record.
    cSavedGameRec(const Vec3& pos, const Matrix3& rot)
        : mFlags(0), mCount(0), mPos(pos), mW(kOne) { mRot = rot; }
};
CHK(cSavedGameRec, mFlags, 0x00);
CHK(cSavedGameRec, mCount, 0x02);
CHK(cSavedGameRec, mPos, 0x04);
CHK(cSavedGameRec, mW, 0x10);
CHK(cSavedGameRec, mRot, 0x14);
typedef char chk_cSavedGameRec_size[(sizeof(cSavedGameRec) == 0x38) ? 1 : -1];

// Refcounted property value. Only the slots this slice calls are named.
struct cProperty {
    virtual void AddRef();                              // +0x00
    virtual void Release();                             // +0x04
    virtual void V08(int);                              // +0x08
    virtual void V0c();                                 // +0x0c
    virtual void V10();                                 // +0x10
    virtual void V14(cSavedGameRec* rec);               // +0x14
};

// ---------------------------------------------------------------------------
// SP::cSPUISpace::cFoodwebSlotInfo - 0x28-byte row of the foodweb slot table. The default row is
// what vector::resize(n) fills new slots with.
// ---------------------------------------------------------------------------
struct cFoodwebSlotInfo {
    cProperty* mpWindow;                                // +0x00  refcounted window (AddRef/Release)
    Key mKey2;                                          // +0x04  secondary key, gNullKey by default
    int mKind;                                          // +0x10
    uint32_t mKey;                                      // +0x14
    int mField18;                                       // +0x18
    uint8_t mFlag1c;                                    // +0x1c
    int mIndex;                                         // +0x20
    int mFlag24;                                        // +0x24
    cFoodwebSlotInfo()
        : mpWindow(0), mKey2(gNullKey), mKind(0), mKey(0x3a8be428u),
          mField18(1), mFlag1c(0), mIndex(1), mFlag24(1) {}
};
CHK(cFoodwebSlotInfo, mpWindow, 0x00);
CHK(cFoodwebSlotInfo, mKey2, 0x04);
CHK(cFoodwebSlotInfo, mKind, 0x10);
CHK(cFoodwebSlotInfo, mKey, 0x14);
CHK(cFoodwebSlotInfo, mField18, 0x18);
CHK(cFoodwebSlotInfo, mFlag1c, 0x1c);
CHK(cFoodwebSlotInfo, mIndex, 0x20);
CHK(cFoodwebSlotInfo, mFlag24, 0x24);
typedef char chk_cFoodwebSlotInfo_size[(sizeof(cFoodwebSlotInfo) == 0x28) ? 1 : -1];

// eastl::vector<cFoodwebSlotInfo, sp_vector_allocator>: begin/end/capacity only (the allocator is
// stateless and never materialised by these functions).
struct cFoodwebSlotVec {
    cFoodwebSlotInfo* mpBegin;                          // +0x00
    cFoodwebSlotInfo* mpEnd;                            // +0x04
    cFoodwebSlotInfo* mpCapacity;                       // +0x08
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    void insert(cFoodwebSlotInfo* pos, unsigned count, const cFoodwebSlotInfo& value);  // 0x0106ebb0
    void erase(cFoodwebSlotInfo* first, cFoodwebSlotInfo* last);                        // 0x0106eb40
    void resize(unsigned count);
};
CHK(cFoodwebSlotVec, mpBegin, 0x00);
CHK(cFoodwebSlotVec, mpEnd, 0x04);
CHK(cFoodwebSlotVec, mpCapacity, 0x08);

// eastl pointer vector sitting at cSPUISpace+0x308 (saved-game property list).
struct cPropertyVec {
    cProperty** mpBegin;                                // +0x00
    cProperty** mpEnd;                                  // +0x04
    cProperty** mpCapacity;                             // +0x08
    void insert(cProperty** pos, cProperty* const& value);   // 0x00a0a360 (grow path)
};
CHK(cPropertyVec, mpBegin, 0x00);
CHK(cPropertyVec, mpEnd, 0x04);
CHK(cPropertyVec, mpCapacity, 0x08);

// ---------------------------------------------------------------------------
// Engine objects reached through the free functions below.
// ---------------------------------------------------------------------------
struct EffectsManager {
    virtual void V00();  virtual void V04();  virtual void V08();  virtual void V0c();
    virtual void V10();  virtual void V14();  virtual void V18();  virtual void V1c();
    virtual void V20();  virtual void V24();  virtual void V28();
    virtual bool GetProperty(uint32_t key, int arg, cProperty** out);   // +0x2c
};
EffectsManager* EffectsManagerPtr();                    // 0x0067ddd0

struct cPointerVec {                                     // eastl::vector<void*, sp_vector_allocator>
    void** mpBegin;                                     // +0x00
    void** mpEnd;                                       // +0x04
    void** mpCapacity;                                  // +0x08
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};
struct StarManager {
    char pad0[0xf0];
    cPointerVec mCivs;                                  // +0xf0 (one entry per empire/civ)
};
CHK(StarManager, mCivs, 0xf0);
typedef char chk_StarManager_mCivEnd[(offsetof(StarManager, mCivs) + 4 == 0xf4) ? 1 : -1];
StarManager* StarManager();                             // 0x00b3d2a0

struct cPlanet {
    void* SortBanners();                                // 0x00b8de30
};
cPlanet* GetPlayerHomePlanet();                         // 0x01021370

struct cCivData {
    Vec3* GetCities();                                  // 0x005c65e0
};

struct cSPUISpace {
    char pad0[0x308];
    cPropertyVec mSavedGameList;                        // +0x308
    void F0106f380();                                   // 0x0106f380
    void ShowSavedGames();
};
CHK(cSPUISpace, mSavedGameList, 0x308);
typedef char chk_cSPUISpace_mListEnd[(offsetof(cSPUISpace, mSavedGameList) + 4 == 0x30c) ? 1 : -1];
typedef char chk_cSPUISpace_mListCap[(offsetof(cSPUISpace, mSavedGameList) + 8 == 0x310) ? 1 : -1];

// ===========================================================================
// 0x01070890
// ===========================================================================
// @ 0x01070890
void cSPUISpace::ShowSavedGames()
{
    F0106f380();
    unsigned count = StarManager()->mCivs.size();
    for (unsigned i = 0; i < count; ++i) {
        cProperty* value = 0;
        void* civ = StarManager()->mCivs.mpBegin[i];
        if (civ != GetPlayerHomePlanet()->SortBanners()) {
            EffectsManager* effects = EffectsManagerPtr();
            if (value != 0) {
                cProperty* old = value;
                value = 0;
                old->Release();
            }
            if (effects->GetProperty(0xf0eb627c, 0, &value))
                value->V08(0);
            if (value != 0) {
                Matrix3 rot = kSavedGameRot;
                cSavedGameRec rec(kSavedGamePos, rot);
                rec.mPos = *((cCivData*)StarManager()->mCivs.mpBegin[i])->GetCities();
                rec.mFlags |= 4;
                rec.mCount += 1;
                value->V14(&rec);
            }
            if (mSavedGameList.mpEnd < mSavedGameList.mpCapacity) {
                *mSavedGameList.mpEnd++ = value;
                if (value != 0)
                    value->AddRef();
            } else {
                mSavedGameList.insert(mSavedGameList.mpEnd, value);
            }
        }
        if (value != 0)
            value->Release();
    }
}

// ===========================================================================
// 0x01070af0
// ===========================================================================
// @ 0x01070af0
void cFoodwebSlotVec::resize(unsigned count)
{
    if (count > size()) {
        cFoodwebSlotInfo value;
        insert(mpEnd, count - size(), value);
    } else {
        erase(mpBegin + count, mpEnd);
    }
}
