// SP::cCommunityEditor::RefreshOrCreateBuildingLinkEffect (retail 0x00d11950).
// Looks up (or creates) the tBuildingLinkEffect for a pair of buildings, (re)starts its link effect
// and puts a small icon effect at the midpoint of the link (pushed out from the planet).
// Types follow the dev PDB (tBuildingLinkEffect, cCommunityEditor) and the ModAPI IVisualEffect vtable.
#include "types.h"

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
    int pad;
    char anchor[0x10];                                                      // +4: the end() node
    Iter find(const Key& k);                                                // 0x00d0bd60 (thiscall, sret)
    tBuildingLinkEffect& operator[](const Key& k);                          // 0x00d0ff80 (thiscall)
    Node* End() { return (Node*)anchor; }
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

struct cCommunityEditor {
    const SVec3* GetCommunityCenter();                                      // 0x00d09960 (thiscall)
    void RefreshOrCreateBuildingLinkEffect(LinkMap* map, int a, int b, SVec3 p1, SVec3 p2, int type);
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
