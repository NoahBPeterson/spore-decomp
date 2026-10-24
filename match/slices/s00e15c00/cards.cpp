// Slice s00e15c00 (continued): mission-card vector helpers and badge-card updates.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast   (UI module: no /EHsc)
#include "types.h"

typedef wchar_t char16;

struct Rect {
    float x1, y1, x2, y2;
};

// The shared empty wide string; capacity is begin+1 element.
extern char16 gEmptyString16[];   // 0x01667bac

// Four-field wide string (begin/end/capacity/allocator) with the heap-delete destructor.
struct str16 {
    char16* mpBegin;
    char16* mpEnd;
    char16* mpCapacity;
    uint32_t mAllocator;
    str16() : mpBegin(&gEmptyString16[0]), mpEnd(&gEmptyString16[0]),
              mpCapacity(&gEmptyString16[1]) {}
    ~str16()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            delete[] mpBegin;
    }
};

class cSPUILayout;
class IMission;

// A UI window / mission card.  Only the vtable slots and data offsets this slice uses
// are named; the rest keep their slot-offset names.
class Win {
public:
    virtual void  v00();                       // 0x00 AddRef
    virtual void  v04();                       // 0x04 Release
    virtual void  v08();
    virtual Win*  v0c(uint32_t typeID);        // 0x0c Cast
    virtual void  v10();
    virtual void  v14();
    virtual void  v18();
    virtual void  v1c();                       // 0x1c
    virtual void  v20();
    virtual void  v24();
    virtual void  v28(int v);                  // 0x28
    virtual void  v2c(int v);                  // 0x2c
    virtual void  v30();
    virtual void  v34();
    virtual const Rect& v38();                 // 0x38 GetRealArea
    virtual void  v3c();
    virtual void  v40();
    virtual void  v44();
    virtual void  v48();
    virtual void  v4c();
    virtual void  v50();
    virtual void  v54();
    virtual void  v58();
    virtual void  v5c(int v);                  // 0x5c
    virtual void  v60();
    virtual void  v64();
    virtual void  v68();
    virtual void  v6c();
    virtual void  v70(float w, float h);       // 0x70 SetSize
    virtual void  v74();
    virtual void  v78();
    virtual void  v7c(int a, int b);           // 0x7c SetFlag
    virtual void  v80(const char16* caption);  // 0x80 SetCaption
    virtual void  v84();
    virtual void  v88();
    virtual void  v8c();
    virtual void  v90();
    virtual void  v94();
    virtual void  v98();
    virtual void  v9c();
    virtual void  vA0();
    virtual void  vA4();
    virtual void  vA8();
    virtual void  vAC();
    virtual void  vB0();
    virtual void  vB4();
    virtual void  vB8();
    virtual void  vBC();
    virtual void  vC0();
    virtual void  vC4();
    virtual void  vC8();
    virtual void  vCC();
    virtual void  vD0();
    virtual void  vD4();
    virtual void  vD8();
    virtual void  vDC();
    virtual void  vE0();
    virtual void  vE4();
    virtual void  vE8();
    virtual void  vEC();
    virtual Win*  vF0(uint32_t controlID, bool recursive);   // 0xf0 FindWindowByID

    uint32_t     mPad04;       // +0x04
    uint32_t     mPad08;       // +0x08
    cSPUILayout* mLayout;      // +0x0c
    uint8_t      mByte10;      // +0x10
    uint8_t      mByte11;      // +0x11
    uint8_t      mPad12[0x98 - 0x12];
    uint32_t     mBadgeId;     // +0x98
    IMission*    mpMission;    // +0x9c

    void ResizeToContent(int a, int b);        // 0x00e13b50, ret 8
    void InitForCreature(int a, int b);        // 0x00e133b0, ret 8
    void UpdateButtonStateA(IMission* m);      // 0x00e145b0, ret 4
};

// Reference-counted slot in the panel's card vector.
struct CardRef {
    Win* p;
    CardRef& operator=(const CardRef& o);
};

inline CardRef& CardRef::operator=(const CardRef& o)
{
    Win* old = p;
    Win* nw = o.p;
    if (nw != old) {
        if (nw)
            nw->v00();
        p = nw;
        if (old)
            old->v04();
    }
    return *this;
}

// The panel's card vector: two pointers at +0x28 / +0x2c.
struct CardVec {
    CardRef* mpBegin;
    CardRef* mpEnd;
    CardRef& operator[](int i) { return mpBegin[i]; }
    int Size() const { return (int)(mpEnd - mpBegin); }
};

class IMission {
public:
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10(); virtual void m14(); virtual void m18(); virtual void m1c();
    virtual void m20(); virtual void m24(); virtual void m28(); virtual void m2c();
    virtual void m30(); virtual void m34(); virtual void m38(); virtual void m3c();
    virtual void m40(); virtual void m44(); virtual void m48(); virtual void m4c();
    virtual void m50(); virtual void m54(); virtual void m58(); virtual void m5c();
    virtual void m60();
    virtual bool m64();                        // 0x64
};

class cMissionPanel {
public:
    void Update(float f);                      // 0x00e49f80, ret 4
};

void UpdateProgessIcons(cSPUILayout* layout, IMission* mission);   // 0x00e2e790
void* FUN_00b3d400();                                             // 0x00b3d400 getter
char FUN_00806a60(void* w, cSPUILayout* layout, int a, int b);    // 0x00806a60 cdecl

class cUIMissionCardPanel {
public:
    char          mPadStart[0x24];       // 0x00 (vptr + unknown)
    Win*          mpRoot;                // +0x24
    CardVec       mCards;                // +0x28
    uint32_t      mPad30[3];             // 0x30 .. 0x3b
    cMissionPanel* mpMissionPanel;       // +0x3c

    void CollapseMissionCard(IMission* mission);        // 0x00e15c00
    void CollapseOtherMissionCards(IMission* mission);  // 0x00e15c70
    bool HasMissionCard(IMission* mission);             // 0x00e15cd0
    bool RemoveBadgeCard(uint32_t badgeId);             // 0x00e15d30
    void FUN_00e15de0(float f);                         // 0x00e15de0
    void FUN_00e15e40(uint32_t mode, int ms);           // 0x00e15e40
    void FUN_00e15e70(float f);                         // 0x00e15e70
    void UpdateCardPositions();                         // 0x00e14b70
    cSPUILayout* GetPanelLayout();                      // 0x00e14c70
};

// ---------------------------------------------------------------------------------------
// @ 0x00e15c00
void cUIMissionCardPanel::CollapseMissionCard(IMission* mission)
{
    int n = mCards.Size();
    for (int i = 0; i < n; ++i) {
        CardRef& slot = mCards[i];
        if (!slot.p)
            continue;
        Win* card = slot.p->v0c(0x334c6eec);
        if (!card)
            continue;
        if (card->mpMission == mission) {
            card->v2c(1);
            return;
        }
    }
}

// @ 0x00e15c70
void cUIMissionCardPanel::CollapseOtherMissionCards(IMission* mission)
{
    int n = mCards.Size();
    for (int i = 0; i < n; ++i) {
        CardRef& slot = mCards[i];
        if (!slot.p)
            continue;
        Win* card = slot.p->v0c(0x334c6eec);
        if (!card)
            continue;
        if (card->mpMission == mission)
            continue;
        card->v2c(1);
    }
}

// @ 0x00e15cd0
bool cUIMissionCardPanel::HasMissionCard(IMission* mission)
{
    int n = mCards.Size();
    for (int i = 0; i < n; ++i) {
        CardRef& slot = mCards[i];
        if (!slot.p)
            continue;
        Win* card = slot.p->v0c(0x334c6eec);
        if (!card)
            continue;
        if (card->mpMission == mission)
            return true;
    }
    return false;
}

// @ 0x00e15d30
bool cUIMissionCardPanel::RemoveBadgeCard(uint32_t badgeId)
{
    int n = mCards.Size();
    for (int i = 0; i < n; ++i) {
        CardRef& slot = mCards[i];
        if (!slot.p)
            continue;
        Win* card = slot.p->v0c(0x334c6eef);
        if (!card)
            continue;
        if (card->mBadgeId != badgeId)
            continue;

        card->v1c();
        mCards[i] = mCards.mpEnd[-1];
        --mCards.mpEnd;
        CardRef& popped = *mCards.mpEnd;
        if (popped.p)
            popped.p->v04();
        UpdateCardPositions();
        return true;
    }
    return false;
}

// @ 0x00e15de0
void cUIMissionCardPanel::FUN_00e15de0(float f)
{
    bool dirty = false;
    int n = mCards.Size();
    for (int i = 0; i < n; ++i) {
        Win* c = mCards[i].p;
        if (c && c->mByte11 != 0) {
            dirty = true;
            c->mByte11 = 0;
        }
    }
    if (mpMissionPanel)
        mpMissionPanel->Update(f);
    if (dirty)
        UpdateCardPositions();
}

// @ 0x00e15e40
void cUIMissionCardPanel::FUN_00e15e40(uint32_t mode, int ms)
{
    FUN_00e15de0((float)(uint32_t)ms * 0.001f);
}

// @ 0x00e15e70
void cUIMissionCardPanel::FUN_00e15e70(float f)
{
    int n = mCards.Size();
    for (int i = 0; i < n; ++i) {
        CardRef& slot = mCards[i];
        if (!slot.p)
            continue;
        Win* card = slot.p->v0c(0x334c6eec);
        if (!card)
            continue;

        cSPUILayout* layout = card->mLayout;
        IMission* mission = card->mpMission;
        if (layout)
            UpdateProgessIcons(layout, mission);

        if (mission->m64()) {
            if (card->mByte10 != 0)
                card->InitForCreature(1, 1);
            else
                card->ResizeToContent(1, 1);
        }
        card->UpdateButtonStateA(mission);
    }
    FUN_00e15de0(f);
}

// ---------------------------------------------------------------------------------------
class cString {
public:
    uint32_t m00;
    uint32_t m04;
    uint32_t m08;
    uint32_t m0c;
    uint32_t m10;
    cString(uint32_t a, uint32_t b, const char16* c);   // 0x006b5770
    ~cString();                                        // 0x006b5240
    const char16* GetText();                           // 0x006b55c0
};

class cSPBadgeManager {
public:
    void GetBadgeName(uint32_t badgeId, str16* out);   // 0x00fe4710, ret 8
    void FUN_00fe4900(uint32_t badgeId, str16* out);   // 0x00fe4900, ret 8
};

struct GameNounMgr {
    cSPBadgeManager* SetGameDataOwner2();              // 0x00bfc5f0
};
GameNounMgr* SpaceGameGet();                           // 0x01002bd0

class cUIBadgeCard {
public:
    virtual void b00();
    virtual void b04();
    virtual void b08();
    virtual void b0c();
    virtual void b10();
    virtual void b14();
    virtual void b18();
    virtual void b1c();
    virtual void b20();
    virtual void b24();
    virtual void b28(int v);                       // 0x28
    virtual void b2c(int v);                       // 0x2c

    uint32_t mPad04[8];                            // 0x04 .. 0x23
    Win*     mpRoot;                               // +0x24
    uint32_t mPad28[(0x98 - 0x28) / 4];            // 0x28 .. 0x97
    uint32_t mBadgeId;                             // +0x98

    bool Init(bool p);                             // 0x00e15060, ret 4
    void FUN_00e16800();                           // 0x00e16800
    void FUN_00e168d0(uint32_t badgeId, bool flag); // 0x00e168d0
};

// @ 0x00e16800
void cUIBadgeCard::FUN_00e16800()
{
    str16 name;
    cSPBadgeManager* mgr = SpaceGameGet()->SetGameDataOwner2();
    mgr->GetBadgeName(mBadgeId, &name);

    Win* w = mpRoot->vF0(0x5235140, true);
    if (w)
        w->v80(name.mpBegin);

    mgr->FUN_00fe4900(mBadgeId, &name);

    Win* w2 = mpRoot->vF0(0x74cb0c14, true);
    if (w2)
        w2->v80(name.mpBegin);
}

// @ 0x00e168d0
void cUIBadgeCard::FUN_00e168d0(uint32_t badgeId, bool flag)
{
    if (!Init(true))
        return;

    cString str(0x2db6dad3, 0x43af52b, 0);

    Win* wStatus = mpRoot->vF0(0x52350c8, true);
    if (wStatus)
        wStatus->v80(str.GetText());

    Win* wIcon = mpRoot->vF0(0x55d3e68, true);
    Win* wCount = mpRoot->vF0(0x740ea83e, true);
    if (wIcon && wCount) {
        wCount->v7c(1, 0);

        Rect r;
        const Rect& ra = wIcon->v38();
        r.x1 = ra.x1;
        r.y1 = ra.y1;
        r.x2 = ra.x2;

        const Rect& rb = wCount->v38();
        wIcon->v70(rb.x2 - (r.x2 - r.x1), r.y1);
        wIcon->v5c(0xffffff00);

        FUN_00806a60(wIcon, ((cUIMissionCardPanel*)FUN_00b3d400())->GetPanelLayout(),
                     0x678d000, -1);
    }

    mBadgeId = badgeId;
    FUN_00e16800();

    if (flag)
        b28(0);
    else
        b2c(0);
}
