// SP::cCommunityEditor::RefreshOrCreateBuildingLinkEffect (retail 0x00d11950).
// Looks up (or creates) the tBuildingLinkEffect for a pair of buildings, (re)starts its link effect
// and puts a small icon effect at the midpoint of the link (pushed out from the planet).
// Types follow the dev PDB (tBuildingLinkEffect, cCommunityEditor) and the ModAPI IVisualEffect vtable.
#include "types.h"
#include <math.h>

struct SVec3 { float x, y, z; };                    // plain POD triple (copied through integer registers)
struct Vec3c {                                      // by-value argument flavour: user copy ctor (fld/fstp)
    float x, y, z;
    Vec3c() {}
    Vec3c(const Vec3c& o) : x(o.x), y(o.y), z(o.z) {}
    Vec3c(const SVec3& o) : x(o.x), y(o.y), z(o.z) {}
};

// ModAPI Swarm::IVisualEffect vtable (offsets are the retail ones)
struct IVisualEffect {
    virtual int AddRef();                                                   // +0x00
    virtual int Release();                                                  // +0x04
    virtual void Start(int hard);                                           // +0x08
    virtual int Stop(int hard);                                             // +0x0c
    virtual int IsRunning();                                                // +0x10
    virtual void v14();                                                     // +0x14
    virtual void SetSourceTransform(const void* xform);                     // +0x18
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c();
    virtual bool SetVectorParams(int param, const Vec3c* data, int count);  // +0x40
    virtual bool SetFloatParams(int param, const float* data, int count);   // +0x44
    virtual bool SetIntParams(int param, const int* data, int count);       // +0x48
    virtual void v4c(); virtual void v50();
    virtual const float* GetFloatParams(int param, int* count);             // +0x54
    virtual void v58(); virtual void v5c();
    virtual uint32_t GetEffectID();                                         // +0x60
};

template <class T> struct Ref {                                             // EA::AutoRefCount
    T* p;
    Ref& operator=(T* q) {
        if (q != p) { T* old = p; if (q) q->AddRef(); p = q; if (old) old->Release(); }
        return *this;
    }
    T* operator->() const { return p; }
};

struct IEffectsManager {
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10(); virtual void m14(); virtual void m18(); virtual void m1c();
    virtual void m20(); virtual void m24(); virtual void m28();
    virtual bool CreateVisualEffect(uint32_t id, uint32_t group, Ref<IVisualEffect>& dst);   // +0x2c
};

// XformMsg (0x00434040): flags, count, pos, scale, rot
struct XformMsg {
    uint16_t flags, count;
    SVec3 pos;
    float scale;
    float rot[9];
    XformMsg();                                                             // 0x00434040
};

struct tBuildingLinkEffect {
    Ref<IVisualEffect> mLinkEffect;                                         // +0x00
    Ref<IVisualEffect> mIconEffect;                                         // +0x04
    SVec3 mPos1;                                                            // +0x08
    SVec3 mPos2;                                                            // +0x14
    int mState;                                                             // +0x20
    unsigned mTimer;                                                        // +0x24
    bool mTicked;                                                           // +0x28
};
struct Key { int a, b; };
struct Node { Node* r; Node* l; Node* p; int color; Key key; tBuildingLinkEffect value; };
struct Iter { Node* node; Iter() {} };
struct LinkMap {                                                            // eastl::map<pair<int,int>, tBuildingLinkEffect>
    int      mPad00;                                                        // +0x00
    Node*    mpAnchorParent;                                                // +0x04
    Node*    mpAnchorLeft;                                                  // +0x08  (begin)
    Node*    mpAnchorRight;                                                 // +0x0c
    uint32_t mAnchorColor;                                                  // +0x10
    int      mCount;                                                        // +0x14
    Iter find(const Key& k);                                                // 0x00d0bd60 (thiscall, sret)
    tBuildingLinkEffect& operator[](const Key& k);                          // 0x00d0ff80 (thiscall)
    Node* End() { return mpAnchorParent; }
    Node* Begin() { return mpAnchorLeft; }
};

struct PtVec { Vec3c* b; Vec3c* e; Vec3c* c; };

extern SVec3 kLinkColorA;     // 0x01582370
extern SVec3 kLinkColorB;     // 0x0158237c
extern SVec3 kLinkColorC;     // 0x01582388
extern SVec3 kLinkColorD;     // 0x01582394

IEffectsManager* EffectsManager();                                          // 0x0067ddd0
uint32_t GetCurrentGameMode();                                              // 0x00b5b800
SVec3* Vector3_Normalize(SVec3* out, const SVec3* v);                       // 0x00436ce0
void CreatedInterpolatedVectorList(Vec3c a, Vec3c b, PtVec* out);           // 0x00d0d6b0 (cdecl)
uint32_t FNV1_String8(const char* s, uint32_t seed, int flag);              // 0x00932e80 (cdecl)
float GetPropertyT_float(uint32_t a, uint32_t b, uint32_t c, float def);    // 0x00bcea30 (cdecl, x87 return)
void operator_delete__(void* p);                                            // 0x00f47380 (cdecl)

template <class T> inline const T& Min(const T& a, const T& b) { return b < a ? b : a; }
template <class T> inline const T& Max(const T& a, const T& b) { return a < b ? b : a; }

// ---------------------------------------------------------------------------------------------
// Editor proxies. The community editor keeps engine objects behind a small proxy interface:
// slot +0x0c fetches an object by id, +0x38 is the object's kind, +0x3c the current selection,
// +0x5c the per-object colour/effect query, +0x6c the slot offset and +0xb8 the editor object.
struct IEditorObj {
    virtual void   s00();                                   // +0x00
    virtual void   s01();                                   // +0x04
    virtual void   s02();                                   // +0x08
    virtual void*  GetObject(uint32_t nID);                 // +0x0c
    virtual void   s04();                                   // +0x10
    virtual void   s05();                                   // +0x14
    virtual void   AttachObject(int nSlot, void* pObject);  // +0x18
    virtual void   GetViewport(void* pRect, void* pPoint);  // +0x1c
    virtual void   s08();                                   // +0x20
    virtual void   s09();                                   // +0x24
    virtual void   s10();                                   // +0x28
    virtual SVec3* GetPosition();                           // +0x2c
    virtual SVec3* GetPositionCopy();                       // +0x30
    virtual void   s13();                                   // +0x34
    virtual uint32_t GetKind();                             // +0x38
    virtual void*  GetSelection();                          // +0x3c
    virtual void   s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void*  GetUiRoot();                             // +0x50
    virtual void   s21(); virtual void s22();
    virtual void*  GetColor(void* pOut, int nIndex, void* pArg, float fValue);  // +0x5c
    virtual void   s24(); virtual void s25(); virtual void s26();
    virtual int    GetSlotOffset();                         // +0x6c
    virtual void   s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void   s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void   s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void   s40(); virtual void s41(); virtual void s42(); virtual void s43();
    virtual void   s44(); virtual void s45();
    virtual void*  FindEditorObject(uint32_t nID);          // +0xb8
};
struct ILinkAnchor : IEditorObj {                           // editor proxy with per-slot link flags
    uint8_t mPad04[0x274 - 4];
    bool    mLinkable[0x100];                               // +0x274
};
struct ICreatureProxy : IEditorObj {                        // proxy with the placed flag
    uint8_t mPad04[0x289 - 4];
    bool    mbPlaced;                                       // +0x289
};
struct IEffectHost {                                        // manager/audio host (+0x3c/+0x5c)
    virtual void   s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void   s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void   s08();                                   // +0x20
    virtual void   s09(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual void   s13(); virtual void s14();
    virtual void   GetSelectionSlots(void* pOut, int nCount);   // +0x3c
    virtual void   s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void   s20(); virtual void s21(); virtual void s22();
    virtual void   AddEffect(uint32_t nID, const SVec3* pPos);  // +0x5c
};
struct IWinProc {
    virtual void s0(); virtual void s1();
    virtual void Hide();                                    // +0x08 (0x005cc690)
};
struct IPalette {
    int GetCurrentCategoryIndex();                          // 0x005ca9c0
};
struct ICircleSlot {                                        // cActionCircle slot
    uint8_t mPad00[0x0c];
    SVec3   mPosition;                                      // +0x0c
    uint8_t mPad18[0x289 - 0x18];
    bool    mbLinkable;                                     // +0x289
    IEditorObj* GetObject();                                // 0x00fcc210
};
struct IActionCircle {
    ICircleSlot* SlotAt(unsigned nIndex);                   // 0x00af9ff0
};
struct LinkPair { uint32_t a, b; uint8_t mPad08[0x50 - 8]; };
struct LinkPairList { LinkPair* mpBegin; LinkPair* mpEnd; };
struct PlacementTrail {
    SVec3* Add(IEditorObj** ppVehicle);                     // 0x00d0fee0
};
struct VehicleList {
    IEditorObj** mpBegin;                                   // +0x00
    IEditorObj** mpEnd;                                     // +0x04
    void erase(IEditorObj** ppSlot);                        // 0x00bf3420
    IEditorObj** find(IEditorObj* p) {
        IEditorObj** pIt = mpBegin;
        while (pIt != mpEnd && *pIt != p) ++pIt;
        return pIt;
    }
};

struct cCommunityEditor;

IEditorObj*  App();                                         // 0x0067dd10
void         FUN_007c4900(void* a, void* b);                // 0x007c4900
IEffectHost* FUN_00b3d240();                                // 0x00b3d240
float        DistancePointSegment(const SVec3* pA, const SVec3* pB,
                                  const SVec3* pC, float fD);   // 0x00698e00
IEditorObj*  PlanetModel(const SVec3* pDir, const SVec3* pIn);  // 0x00b3d350
void         BuildSurfaceOrientation(IEditorObj* pModel);   // 0x00b7f1f0
IEditorObj*  FUN_00d0a3f0(IEditorObj* pVehicle);            // 0x00d0a3f0
void         FUN_00d0dea0(cCommunityEditor* pEditor);       // 0x00d0dea0
void         FUN_00d0a5b0(cCommunityEditor* pEditor);       // 0x00d0a5b0
void         FUN_005cc690(IWinProc* pWin);                  // 0x005cc690
void         SetManipulatedObject(cCommunityEditor* pEditor, void* pObject);  // 0x00d09f60
IActionCircle* FUN_00bd7f40(ICreatureProxy* pCurrent);      // 0x00bd7f40
LinkPairList*  FUN_00bd8230(ICreatureProxy* pCurrent);      // 0x00bd8230
bool         FUN_00c3f540(ILinkAnchor* pAnchor);            // 0x00c3f540
void         FUN_00d0d880(void* pArg, tBuildingLinkEffect* pValue);  // 0x00d0d880
IEffectHost* GetAudioSystem();                              // 0x00a206f0 (EA::Audio::GetSystemAT)
void         KillSetiEffects(IEffectHost* pAudio, uint32_t nID);     // 0x00435ed0
void         DisbandUnit(IEditorObj* pVehicle, char bFlag);          // 0x00caa610
Node*        RBTreeIncrement(Node* pNode);                  // 0x00921580
void         RBTreeErase(Node* pNode, Node* pHeader);       // 0x00921880

static int LinkKind(IEditorObj* pObj1, IEditorObj* pObj2)
{
    uint32_t k1 = pObj1->GetKind();
    uint32_t k2 = pObj2->GetKind();
    if (k1 == 0x1007ae63u || k1 == 0x0ff10521u) {
        if (k2 == 0x0ecade42u || k2 == 0x1007ae63u || k2 == 0x0ff10521u)
            return 4;
        return (k2 == 0x01a55e4du) ? 2 : 1;
    }
    if (k1 == 0x0ecade42u) {
        if (k2 == 0x1007ae63u || k2 == 0x0ff10521u)
            return 4;
        return (k2 == 0x01a55e4du) ? 3 : 1;
    }
    if (k2 == 0x1007ae63u || k2 == 0x0ff10521u)
        return 2;
    return (k2 == 0x0ecade42u) ? 3 : 1;
}

struct cCommunityEditor {
    uint8_t         mPad00[0x40];
    IEditorObj*     mpSelection;                            // +0x40
    uint8_t         mPad44[0x68 - 0x44];
    IEditorObj*     mpPlacementServices;                    // +0x68
    uint8_t         mPad6c[0x7c - 0x6c];
    IWinProc*       mpSellBackRollover;                     // +0x7c
    uint8_t         mPad80[0x84 - 0x80];
    IWinProc*       mpEditorWin;                            // +0x84
    uint8_t         mPad88[0xb4 - 0x88];
    IPalette*       mpPalette;                              // +0xb4
    uint8_t         mPadB8[0xc0 - 0xb8];
    Ref<IEditorObj> mPlacementVehicle;                      // +0xc0
    uint8_t         mPadC4[0xf8 - 0xc4];
    int             mCurrentSlot;                           // +0xf8
    uint8_t         mPadFC[0x108 - 0xfc];
    SVec3           mPlanetOffset;                          // +0x108
    PlacementTrail  mTrail;                                 // +0x114
    uint8_t         mPad118[0x1f0 - 0x118];
    VehicleList     mPotentialVehicles;                     // +0x1f0

    const SVec3* GetCommunityCenter();                                      // 0x00d09960 (thiscall)
    void RefreshOrCreateBuildingLinkEffect(LinkMap* map, int a, int b, SVec3 p1, SVec3 p2, int type);
    int  EndVehiclePlacement(int nArg0, int nArg1);                         // 0x00d11730
    void UpdateBuildingLinkEffects(LinkMap* map, int nMode, void* pArg);    // 0x00d11f80
};

// @ 0x00D11950
void cCommunityEditor::RefreshOrCreateBuildingLinkEffect(LinkMap* map, int a, int b, SVec3 p1, SVec3 p2, int type)
{
    Key key;
    key.a = Min(a, b);
    key.b = Max(a, b);

    SVec3 color;
    color.x = kLinkColorA.x;
    color.y = kLinkColorA.y;
    color.z = kLinkColorA.z;
    uint32_t effectId = 0;
    uint32_t iconId = 0;
    switch (type) {
    case 0:
        effectId = 0x5eb915b0;
        iconId = 0;
        color = kLinkColorA;
        break;
    case 1:
        effectId = 0xba8a69d1;
        iconId = 0;
        color = kLinkColorA;
        break;
    case 4:
        color = kLinkColorD;
        effectId = 0xba8a69d1;
        iconId = (GetCurrentGameMode() == 0x1654c05) ? 0xe256dd92 : 0xb5c829c8;
        break;
    case 2:
        effectId = 0xba8a69d1;
        iconId = 0xb18452da;
        color = kLinkColorC;
        break;
    case 3:
        effectId = 0xba8a69d1;
        iconId = 0xa62cbc30;
        color = kLinkColorB;
        break;
    default:
        break;
    }

    Iter it = map->find(key);
    float f = 0.0f;
    tBuildingLinkEffect* v;
    if (it.node == map->End()) {
        v = &(*map)[key];
        IEffectsManager* em = EffectsManager();
        v->mLinkEffect = 0;
        em->CreateVisualEffect(effectId, 0, v->mLinkEffect);
        if (v->mLinkEffect.p != 0) {
            const SVec3* c = GetCommunityCenter();
            float dx1 = c->x - p1.x;
            float dy1 = c->y - p1.y;
            float dz1 = c->z - p1.z;
            c = GetCommunityCenter();
            float dx2 = c->x - p2.x;
            float dy2 = c->y - p2.y;
            float dz2 = c->z - p2.z;
            if ((dx2 * dx2 + dy2 * dy2) + dz2 * dz2 > (dx1 * dx1 + dy1 * dy1) + dz1 * dz1) {
                v->mPos1 = p1;
                v->mPos2 = p2;
            } else {
                v->mPos1 = p2;
                v->mPos2 = p1;
            }
            PtVec vec = { 0, 0, 0 };
            CreatedInterpolatedVectorList(Vec3c(v->mPos1), Vec3c(v->mPos1), &vec);
            Vec3c* data = vec.b;
            int n = (int)(vec.e - data);
            v->mLinkEffect->SetVectorParams(0xd, data, n);
            v->mLinkEffect->SetFloatParams(4, &f, 1);
            v->mLinkEffect->Start(0);
            v->mState = 0;
            v->mTimer = 0;
            v->mTicked = true;
            if (data != 0 && ((int*)data)[-1] != 0)
                operator_delete__(data);
        }
    } else {
        v = &it.node->value;
        v->mLinkEffect->SetFloatParams(5, &color.x, 3);
        int st = v->mState;
        v->mTicked = true;
        if (st == 1) {
            f = 1.0f;
        } else if (st == 2 || st == 3) {
            v->mState = 0;
            int n = 1;
            const float* fp = v->mLinkEffect->GetFloatParams(4, &n);
            if (n >= 1)
                f = fp[0];
        }
    }

    Ref<IVisualEffect>* icon = &v->mIconEffect;
    if (icon->p != 0) {
        if (iconId == icon->p->GetEffectID())
            return;
        (*icon)->Stop(0);
        *icon = 0;
    }
    if (iconId == 0)
        return;

    IEffectsManager* em2 = EffectsManager();
    *icon = 0;
    em2->CreateVisualEffect(iconId, 0, *icon);
    if (icon->p != 0) {
        uint32_t hName = FNV1_String8("BuildingLinkIconEffectOffsetFromPlanet", 0x811c9dc5, 1);
        uint32_t hGroup = FNV1_String8("CommunityEditor", 0x811c9dc5, 1);
        float off = GetPropertyT_float(hGroup, 0, hName, 5.0f);
        SVec3 t1, t2;
        SVec3 pt1, pt2, mid;
        SVec3* n1 = Vector3_Normalize(&t1, &p2);
        pt1.x = n1->x * off + p2.x;
        pt1.y = n1->y * off + p2.y;
        pt1.z = n1->z * off + p2.z;
        SVec3* n2 = Vector3_Normalize(&t2, &p1);
        pt2.x = n2->x * off + p1.x;
        pt2.y = n2->y * off + p1.y;
        pt2.z = n2->z * off + p1.z;
        mid.x = (pt1.x - pt2.x) * 0.5f + pt2.x;
        mid.y = (pt1.y - pt2.y) * 0.5f + pt2.y;
        mid.z = (pt1.z - pt2.z) * 0.5f + pt2.z;
        XformMsg msg;
        msg.flags |= 4;
        ++msg.count;
        msg.pos = mid;
        (*icon)->SetSourceTransform(&msg);
        (*icon)->SetFloatParams(4, &f, 1);
        (*icon)->Start(0);
    }
}

// @ 0x00D11730
int cCommunityEditor::EndVehiclePlacement(int nArg0, int nArg1)
{
    if (mpSelection)
        mpSelection->GetObject(0xee9b2232);

    ICreatureProxy* pVehicle = 0;
    if (mPlacementVehicle.p)
        pVehicle = (ICreatureProxy*)mPlacementVehicle.p->FindEditorObject(0x137e8e0);
    if (pVehicle) {
        IEditorObj* pUi = (IEditorObj*)App()->GetUiRoot();
        SVec3 rect;
        SVec3 point;
        pUi->GetViewport(&rect, &point);
        FUN_007c4900(&rect, &point);

        IEffectHost* pSelection = FUN_00b3d240();
        SVec3 slotPos;
        pSelection->GetSelectionSlots(&slotPos, 1);

        SVec3 probe;
        float fDist = DistancePointSegment(&probe, &slotPos, &mPlanetOffset, 0.0f);
        (void)fDist;

        IEditorObj* pModel = PlanetModel(pVehicle->GetPositionCopy(), &probe);
        BuildSurfaceOrientation(pModel);

        float dx = probe.x - mPlanetOffset.x;
        float dy = probe.y - mPlanetOffset.y;
        float dz = probe.z - mPlanetOffset.z;
        float fSurfaceDist = sqrtf(dx * dx + dy * dy + dz * dz);
        if (fSurfaceDist < 15.0f) {
            SVec3* pTrail = mTrail.Add(&mPlacementVehicle.p);
            *pTrail = mPlanetOffset;
        } else {
            IEditorObj* pFaded = FUN_00d0a3f0(pVehicle);
            mpPlacementServices->AttachObject(0, pFaded);

            IEffectHost* pHost = FUN_00b3d240();
            char colorBuf[0x0c];
            void* pColor = mPlacementVehicle.p->GetColor(colorBuf, -1, pFaded, 1.0f);
            (void)pColor;
            pColor = mPlacementVehicle.p->GetPosition();
            pHost->AddEffect(0x64bf470, (const SVec3*)pColor);

            IEffectHost* pAudio = GetAudioSystem();
            if (pAudio)
                pAudio->s08();
            KillSetiEffects(pAudio, 0x275cdfce);
            DisbandUnit(pFaded, 0);

            IEditorObj** pFound = mPotentialVehicles.find(pFaded);
            if (pFound != mPotentialVehicles.mpEnd)
                mPotentialVehicles.erase(pFound);
        }
    }

    FUN_00d0dea0(this);
    SetManipulatedObject(this, 0);
    if (mpEditorWin)
        FUN_005cc690(mpEditorWin);
    if (mpSellBackRollover)
        mpSellBackRollover->Hide();
    FUN_00d0a5b0(this);
    return 0;
}

// @ 0x00D11F80
void cCommunityEditor::UpdateBuildingLinkEffects(LinkMap* map, int nMode, void* pArg)
{
    if (!mpSelection)
        return;
    ICreatureProxy* pCurrent = (ICreatureProxy*)mpSelection->GetObject(0xee9b2232);
    if (!pCurrent)
        return;

    IActionCircle* pActionCircle = FUN_00bd7f40(pCurrent);

    for (Node* pNode = map->Begin(); pNode != map->End(); pNode = RBTreeIncrement(pNode))
        pNode->value.mTicked = false;

    if (mpPalette && mpPalette->GetCurrentCategoryIndex() == 0) {
        if (nMode == 0) {
            LinkPairList* pPairs = FUN_00bd8230(pCurrent);
            int nCount = (int)(pPairs->mpEnd - pPairs->mpBegin);
            for (int i = 0; i < nCount; ++i) {
                LinkPair* pPair = &pPairs->mpBegin[i];
                ICircleSlot* pSlot1 = pActionCircle->SlotAt(pPair->a);
                ICircleSlot* pSlot2 = pActionCircle->SlotAt(pPair->b);
                if (!pSlot1 || !pSlot2)
                    continue;
                IEditorObj* pObj1 = pSlot1->GetObject()
                    ? (IEditorObj*)pSlot1->GetObject()->GetObject(0xe9cb8ba) : 0;
                IEditorObj* pObj2 = pSlot2->GetObject()
                    ? (IEditorObj*)pSlot2->GetObject()->GetObject(0xe9cb8ba) : 0;
                bool bPlaced = (pObj1 && ((ICreatureProxy*)pObj1)->mbPlaced)
                            || (pObj2 && ((ICreatureProxy*)pObj2)->mbPlaced);
                if (!bPlaced)
                    continue;
                // The two slots may reference the same editor object only when both are
                // present; a lone null endpoint is skipped.
                if ((!pObj1 || !pObj2) && (pObj1 != pObj2))
                    continue;
                RefreshOrCreateBuildingLinkEffect(map, (int)pPair->a, (int)pPair->b,
                                                 pSlot1->mPosition, pSlot2->mPosition,
                                                 LinkKind(pObj1, pObj2));
            }
        } else if (nMode == 1 && mPlacementVehicle.p) {
            ILinkAnchor* pAnchor = (ILinkAnchor*)mPlacementVehicle.p->FindEditorObject(0xe9cb8ba);
            if (pAnchor) {
                int nSlotOffset = pAnchor->GetSlotOffset();
                int nBase = 0;
                for (int nRow = 0; nRow < 0xc4; nRow += 14) {
                    for (int nCol = 0; nCol < 14; ++nCol) {
                        if ((!FUN_00c3f540(pAnchor)
                             || nRow == mCurrentSlot || nCol == mCurrentSlot)
                            && pAnchor->mLinkable[nSlotOffset + nBase + nCol]) {
                            ICircleSlot* pSlot1 = pActionCircle->SlotAt(nRow);
                            ICircleSlot* pSlot2 = pActionCircle->SlotAt(nCol);
                            if (pSlot1 && pSlot2) {
                                IEditorObj* pObj1 = pSlot1->GetObject()
                                    ? (IEditorObj*)pSlot1->GetObject()->GetObject(0xe9cb8ba) : 0;
                                IEditorObj* pObj2 = pSlot2->GetObject()
                                    ? (IEditorObj*)pSlot2->GetObject()->GetObject(0xe9cb8ba) : 0;
                                if ((pObj1 && ((ICreatureProxy*)pObj1)->mbPlaced)
                                    || (pObj2 && ((ICreatureProxy*)pObj2)->mbPlaced)) {
                                    if (pObj1 == (IEditorObj*)pAnchor || pObj2 == (IEditorObj*)pAnchor)
                                        continue;
                                    RefreshOrCreateBuildingLinkEffect(map, nRow, nCol,
                                                                     pSlot1->mPosition,
                                                                     pSlot2->mPosition, 0);
                                }
                            }
                        }
                    }
                    nBase += 14;
                }
            }
        }
    }

    Node* pNode = map->Begin();
    while (pNode != map->End()) {
        FUN_00d0d880(pArg, &pNode->value);
        if (!pNode->value.mTicked && pNode->value.mState != 2 && pNode->value.mState != 3)
            pNode->value.mState = 2;
        if (pNode->value.mState != 3) {
            pNode = RBTreeIncrement(pNode);
            continue;
        }
        if (pNode->value.mLinkEffect.p)
            pNode->value.mLinkEffect.p->Stop(0);
        if (pNode->value.mIconEffect.p)
            pNode->value.mIconEffect.p->Stop(0);
        --map->mCount;
        Node* pNext = RBTreeIncrement(pNode);
        RBTreeErase(pNode, map->End());
        if (pNode->value.mIconEffect.p)
            pNode->value.mIconEffect.p->Release();
        if (pNode->value.mLinkEffect.p)
            pNode->value.mLinkEffect.p->Release();
        operator_delete__(pNode);
        pNode = pNext;
    }
}
