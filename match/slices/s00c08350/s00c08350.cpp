// Slice s00c08350: creature awareness / sensing update (one 4275-byte function).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS- /fp:fast
#include "types.h"
#include <math.h>
#include <string.h>

struct Vec3 { float x, y, z; };

// Growable array of 4-byte elements (begin/end/capacity), eastl::vector layout.
struct Vec32 {
    uint32_t* b; uint32_t* e; uint32_t* cap;
    void __thiscall DoInsert(uint32_t* pos, uint32_t* val);   // 0x00b96600
    void __thiscall AddUnique(uint32_t* val);                 // 0x00c072f0
};

// A scored-target container: 0x00c05ee0 resets it, 0x00c06750/0x00c066a0 add an entry.
struct TargetSet {
    uint8_t data[0x2c];
    void __thiscall Reset();  // 0x00c05ee0
};
uint32_t __cdecl AddTarget(TargetSet* set, void* obj, float dist, bool a, bool b);    // 0x00c06750
uint32_t __cdecl AddTargetOld(TargetSet* set, void* obj, float dist, bool a, bool b); // 0x00c066a0
void __cdecl SortScores(uint32_t* b, uint32_t* e, uint32_t extra);  // 0x00c07320
float __cdecl Normalize3(Vec3* v);                                  // 0x00c02690 (returns old length)
float __cdecl GetCreatureFactor(int which, void* creature);         // 0x00d38a30
extern float g_NearLimit;                                           // 0x01582fa8
extern float g_NearCmp;                                             // 0x01485378
extern float g_PostDuration;                                        // 0x01486110
void __cdecl MsgCallback();                                         // 0x00d995c0

struct Gauge {
    virtual void v0() {}
    virtual void g1() {}
    virtual void g2() {}
    virtual void g3() {}
    virtual void g4() {}
    virtual void g5() {}
    virtual void g6() {}
    virtual void g7() {}
    virtual void g8() {}
    virtual void g9() {}
    virtual void g10() {}
    virtual void g11() {}
    virtual void g12() {}
    virtual void g13() {}
    virtual void g14() {}
    virtual void g15() {}
    virtual void g16() {}
    virtual void g17() {}
    virtual void g18() {}
    virtual void g19() {}
    virtual void g20() {}
    virtual void g21() {}
    virtual float GetValue();   // slot 22 (+0x58)
};

struct Node;
struct Owner {
    uint8_t pad0[0x1d8];
    uint32_t id;
    uint8_t pad1[0x420];
    uint32_t flags;
};
struct OwnerSub {
    void __thiscall PostEvent(uint32_t id, uint32_t zero, float f, Node* who);  // 0x00bc97f0 (on Owner+8)
};
struct Tuning {
    uint8_t pad[0xa8];
    float range;
    float __thiscall GetBound(bool b);  // TuningObj::GetBound 0x004d3d70
};

struct Entity {
    virtual void v0() {}
    virtual void e1() {}
    virtual void e2() {}
    virtual void e3() {}
    virtual void e4() {}
    virtual void e5() {}
    virtual void e6() {}
    virtual void e7() {}
    virtual void e8() {}
    virtual void e9() {}
    virtual void e10() {}
    virtual Vec3* GetPosition();      // slot 11
    virtual void f12() {}
    virtual void f13() {}
    virtual void f14() {}
    virtual void f15() {}
    virtual void f16() {}
    virtual void f17() {}
    virtual void f18() {}
    virtual void f19() {}
    virtual void f20() {}
    virtual void f21() {}
    virtual void f22() {}
    virtual void f23() {}
    virtual void f24() {}
    virtual void f25() {}
    virtual void f26() {}
    virtual void f27() {}
    virtual void f28() {}
    virtual float GetRadius();        // slot 29
    virtual void h30() {}
    virtual void h31() {}
    virtual void h32() {}
    virtual void h33() {}
    virtual void h34() {}
    virtual void h35() {}
    virtual void h36() {}
    virtual void h37() {}
    virtual void h38() {}
    virtual void h39() {}
    virtual void h40() {}
    virtual void h41() {}
    virtual void h42() {}
    virtual void h43() {}
    virtual void h44() {}
    virtual void h45() {}
    virtual Node* Query(uint32_t id); // slot 46 (+0xb8)
    uint8_t pad0[0x4c];
    uint32_t flags;
    uint8_t pad1[0x8];
    Vec3 pos;
    uint8_t pad2[0xd];
    uint8_t active;
};

struct Body;
struct Node {
    virtual void v0() {}
    virtual void a1() {}
    virtual void a2() {}
    virtual Node* QueryCreature(uint32_t id);   // slot 3 (+0xc)
    virtual void b4() {}
    virtual void b5() {}
    virtual void b6() {}
    virtual void b7() {}
    virtual uint32_t GetType();                  // slot 8 (+0x20)
    virtual void c9() {}
    virtual void c10() {}
    virtual bool IsIgnorable();                  // slot 11 (+0x2c)
    virtual void d12() {}
    virtual void d13() {}
    virtual void d14() {}
    virtual void d15() {}
    virtual void d16() {}
    virtual void d17() {}
    virtual void d18() {}
    virtual void d19() {}
    virtual void d20() {}
    virtual void d21() {}
    virtual void d22() {}
    virtual void d23() {}
    virtual void d24() {}
    virtual void d25() {}
    virtual void d26() {}
    virtual void d27() {}
    virtual void d28() {}
    virtual void d29() {}
    virtual void d30() {}
    virtual void d31() {}
    virtual void d32() {}
    virtual void d33() {}
    virtual void d34() {}
    virtual void d35() {}
    virtual void d36() {}
    virtual void d37() {}
    virtual void d38() {}
    virtual void d39() {}
    virtual void d40() {}
    virtual void d41() {}
    virtual void d42() {}
    virtual void d43() {}
    virtual void d44() {}
    virtual Tuning* Lookup(uint32_t k);          // slot 45 (+0xb4)
    virtual void i46() {}
    virtual void i47() {}
    virtual void i48() {}
    virtual void i49() {}
    virtual void i50() {}
    virtual void i51() {}
    virtual bool IsBlocked();                    // slot 52 (+0xd0)
    uint8_t pad0[0x120];
    uint32_t flags124;
    uint8_t pad1[0x44];
    uint32_t state16c;
    uint8_t pad2[0x9b0];
    uint32_t groupId;
    uint8_t pad3[0x34];
    uint32_t bflags;
    uint8_t pad4[0x2];
    uint8_t aggro;
    int __thiscall GetState();                   // 0x00c0c2f0
    Vec3* __thiscall GetEyePos(Vec3* out);       // 0x00c0d660
    float __thiscall GetSightRange();            // 0x00c0e4f0
    float __thiscall GetFovDegrees();            // 0x00c0c010
    float __thiscall GetStealthLevel();          // 0x00c0b9c0
    bool __thiscall IsHidden();                  // 0x00c0c130
    uint32_t __thiscall GetSpeciesKey();         // 0x00c0c140
    bool __thiscall CanSense(Node* other, float a, float b);  // 0x00c0d560
    void __thiscall SetStealthed(bool a, bool b);             // 0x00c1aed0
    Node* __thiscall GetTargetAsCreature();      // 0x00c0ee70
    void* __thiscall GetSpeciesProfile();        // 0x00c0bbd0
    bool __thiscall IsNearTarget();              // 0x00c6aa50
    Body* body() { return (Body*)((char*)this + 0xc0); }
};
Node* __cdecl FindSubNode(Node* n, uint32_t id);   // 0x00ac80d0

struct Sink {
    int __thiscall Run();  // 0x00bca620
};
struct Msg { void* p; uint32_t z; };
Sink* __stdcall MakeSink(uint32_t id, void (__cdecl* fn)(), Msg* m);   // 0x00bc9b00

struct Tuning;
struct Tracker {
    void __thiscall Update();  // 0x00c7dcb0
};
struct Planet {
    Vec3* __thiscall GetCenter();  // 0x00b816f0
};
Planet* __stdcall PlanetModel(void* out, Vec3* p); // SP::PlanetModel 0x00b3d350
struct EntityQuery {
    void __thiscall Run();  // 0x00b09070
};
struct EntityList { Entity** b; Entity** e; Entity** cap; uint32_t alloc; Entity* buf[256]; };
EntityQuery* __stdcall QueryEntities(Vec3* center, float radius, EntityList* out, int zero);   // 0x00b3d440
struct FlagSet {
    bool __thiscall Test(uint32_t mask);  // 0x00bc9a00
};
struct NounMgr {
    void* __thiscall GetAvatar();  // SP::cGameNounManager::GetAvatar 0x00b1fdb0
};
NounMgr* __cdecl NounManager();                    // SP::NounManager 0x00b3d300
struct ListPair { Entity** b; Entity** e; };
uint32_t __cdecl GetCurrentGameMode();             // SP::GetCurrentGameMode 0x00b5b800
void __cdecl FreeArray(void* p);                   // operator delete[] 0x00f47380

struct Body {
    virtual void v0() {}
    virtual void a1() {}
    virtual void a2() {}
    virtual void a3() {}
    virtual void a4() {}
    virtual void a5() {}
    virtual void a6() {}
    virtual void a7() {}
    virtual void a8() {}
    virtual void a9() {}
    virtual void a10() {}
    virtual Vec3* GetPosition();                 // slot 11 (+0x2c)
    virtual void b12() {}
    virtual void b13() {}
    virtual void b14() {}
    virtual void b15() {}
    virtual void b16() {}
    virtual void b17() {}
    virtual void b18() {}
    virtual void b19() {}
    virtual void b20() {}
    virtual void b21() {}
    virtual bool IsBusy();                       // slot 22 (+0x58)
    virtual void GetForward(Vec3* out);          // slot 23 (+0x5c)
    virtual void c24() {}
    virtual void c25() {}
    virtual void c26() {}
    virtual void c27() {}
    virtual void c28() {}
    virtual float GetRadius();                   // slot 29 (+0x74)
    uint8_t pad0[0x4e4];
    Gauge gauge;
    uint8_t pad1[0x34];
    float gaugeLimit;
    uint8_t pad2[0x524];
    float planetDist;
    uint8_t pad3[0x14];
    uint32_t groupId;
    uint8_t pad4[0x28];
    Owner* owner;
    uint8_t pad5[0x8];
    uint32_t uflags;
    uint8_t pad6[0x2];
    uint8_t disabled;
    uint8_t pad7[0x431];
    uint8_t wide;
    uint8_t pad8[0x27];
    uint8_t alerted;
    uint8_t calm;
    uint8_t pad9[0x62];
    uint32_t mode;
    uint8_t pad10[0x14];
    TargetSet setA;
    TargetSet setB;
    Vec32 listWide;
    uint8_t pad11[0x8c];
    Vec32 listCreatures;
    uint8_t pad12[0x20c];
    Vec32 listB;
    uint8_t pad13[0x8c];
    Vec32 listC;
    uint8_t pad14[0x2c];
    Vec32 listD;
    uint8_t pad15[0x20c];
    FlagSet flagSet;

    void BaseUpdate();                 // 0x00c42350
    ListPair* GetNearbyList();         // 0x00c420d0
    void Update();      // 0x00c08350
};

static inline void Clear(Vec32& v)
{
    uint32_t* last = v.e;
    uint32_t* first = v.b;
    memcpy(first, last, (char*)v.e - (char*)last);
    v.e = (uint32_t*)((char*)v.e - ((last - first) * 4));
}

static inline void Push(Vec32& v, uint32_t x)
{
    uint32_t* p = v.e;
    if (p < v.cap) {
        v.e = p + 1;
        if (p) *p = x;
    } else {
        v.DoInsert(p, &x);
    }
}

// @ 0x00c08350
void Body::Update()
{
    Node* me = (Node*)((char*)this - 0xc0);
    BaseUpdate();
    if (GetCurrentGameMode() == 0x1654c10) {
        Vec3 e1, e2;
        uint8_t scratch[64];
        Vec3* c = PlanetModel(scratch, me->GetEyePos(&e1))->GetCenter();
        Vec3* p = me->GetEyePos(&e2);
        float dz = p->z - c->z, dy = p->y - c->y, dx = p->x - c->x;
        planetDist = (float)sqrt((double)(dz * dz + dy * dy + dx * dx));
        ((Tracker*)((char*)this + 0x5b0))->Update();
    }
    Clear(listWide);
    setB.Reset();
    int state = me->GetState();
    if (state == 2 || (wide && state == 1)) {
        Vec3* pos = GetPosition();
        EntityList list;
        list.b = list.e = list.buf;
        list.cap = list.buf + 256;
        list.alloc = 0;
        QueryEntities(GetPosition(), 20.0f, &list, 0)->Run();
        Entity** end = list.e;
        for (Entity** it = list.b; it != end; ++it) {
            Entity* o = *it;
            float dx = o->pos.x - pos->x;
            float dy = o->pos.y - pos->y;
            float dz = o->pos.z - pos->z;
            Push(listWide, AddTargetOld(&setB, o, (float)sqrt((double)(dy * dy + (dz * dz + dx * dx)) + 1e-8), true, false));
        }
        SortScores(listWide.b, listWide.e, 0);
        if (list.b && ((uint32_t*)list.b)[-1] != 0)
            FreeArray(list.b);
    }

    if ((uflags >> 9) & 1) {
        GetCreatureFactor(1, me);
        GetCreatureFactor(2, me);
        Clear(listCreatures);
        Clear(listD);
        setA.Reset();
        ListPair* lp = GetNearbyList();
        float myRad = GetRadius();
        me->GetSightRange();
        me->GetFovDegrees();
        Vec3 fwd;
        GetForward(&fwd);
        Vec3* pos = GetPosition();
        float lim = gaugeLimit;
        alerted = 0;
        bool seen = false;
        if (gauge.GetValue() > lim)
            seen = me->GetStealthLevel() >= 1.0f;
        uint32_t v = 0;
        Entity** end = lp->e;
        for (Entity** it = lp->b; it != end; ++it) {
            Entity* o = *it;
            if (!o->active || (o->flags & 0x10)) continue;
            Node* n = o->Query(0x17f243b);
            if (n->IsIgnorable()) continue;
            Node* cr = o->Query(0xce9f6639);
            if (cr) {
                Body* cb = cr->body();
                Vec3* p2 = cb->GetPosition();
                float dx = p2->x - pos->x, dy = p2->y - pos->y, dz = p2->z - pos->z;
                float len = (float)sqrt((double)(dy * dy + (dz * dz + dx * dx)) + 1e-8);
                float d = len - (cb->GetRadius() + myRad);
                if (!(0.0f <= d)) d = 0.0f;
                v = AddTarget(&setA, cr, d, true, true);
                Push(listCreatures, v);
            } else if (n->GetType() == 0x52aa6122) {
                n->flags124 |= 1;
                Vec3* p2 = o->GetPosition();
                float dx = p2->x - pos->x, dy = p2->y - pos->y, dz = p2->z - pos->z;
                float len = (float)sqrt((double)(dy * dy + (dz * dz + dx * dx)) + 1e-8);
                float d = len - (o->GetRadius() + myRad);
                if (!(0.0f <= d)) d = 0.0f;
                v = AddTarget(&setA, n, d, true, true);
                Push(listD, v);
                if (!alerted && seen && n->IsNearTarget() && g_NearLimit > d && owner->id != 0x2e5e38d) {
                    Msg m;
                    m.p = me ? (void*)&gauge : 0;
                    m.z = 0;
                    if (!MakeSink(0x60995fc, MsgCallback, &m)->Run())
                        alerted = 1;
                }
            }
        }
        SortScores(listCreatures.b, listCreatures.e, v);
        return;
    }

    Node* best = 0;
    int count = 0;
    setA.Reset();
    Clear(listCreatures);
    Clear(listB);
    Clear(listC);
    Clear(listD);
    if (disabled) return;

    bool hideCheck;
    if (!IsBusy() && !me->IsBlocked() && me->GetState() == 2)
        hideCheck = GetCurrentGameMode() != 0x1654c05;
    else
        hideCheck = false;

    float bestDist = 3.402823466e+38f;
    bool anyBusy = false, anyHidden = false, otherGroup = false;
    float f1 = GetCreatureFactor(1, me);
    float f2 = GetCreatureFactor(2, me);
    float R = me->GetSightRange() * f2;
    float cosv = (float)cos((double)(me->GetFovDegrees() * 0.008726646f));
    Vec3 fwd;
    GetForward(&fwd);
    ListPair* lp = GetNearbyList();
    Vec3* pos = GetPosition();
    float myRad = GetRadius();
    bool seen = false;
    if ((uflags >> 8) & 1) {
        float lim = gaugeLimit;
        alerted = 0;
        if (gauge.GetValue() > lim)
            seen = me->GetStealthLevel() >= 1.0f;
    }
    Entity** end = lp->e;
    for (Entity** it = lp->b; it != end; ++it) {
        Entity* o = *it;
        if (!o->active || (o->flags & 0x10)) continue;
        Node* n = o ? o->Query(0x17f243b) : 0;
        Vec3* p = o->GetPosition();
        Node* cr;
        if (!n || !(cr = n->QueryCreature(0xce9f6639))) {
            uint32_t t = n->GetType();
            if (t == 0x2a034cd) {
                float dx = p->x - pos->x, dy = p->y - pos->y, dz = p->z - pos->z;
                float len = (float)sqrt((double)(dz * dz + dy * dy + dx * dx) + 1e-8);
                float inv = 1.0f / len;
                float d = len - (o->GetRadius() + myRad);
                if (!(0.0f <= d)) d = 0.0f;
                Push(listC, AddTarget(&setA, n, d, true, true));
            } else if (t == 0x2c9cc91) {
                if (n->state16c == 2) {
                    Vec3 dir = { p->x - pos->x, p->y - pos->y, p->z - pos->z };
                    float len = Normalize3(&dir);
                    float d = len - (o->GetRadius() + myRad);
                    if (!(0.0f <= d)) d = 0.0f;
                    uint32_t v = AddTarget(&setA, n, d, true, true);
                    listB.AddUnique(&v);
                }
            } else if (t != 0x2e72cae) {
                Vec3 dir = { p->x - pos->x, p->y - pos->y, p->z - pos->z };
                float len = Normalize3(&dir);
                float d = len - (o->GetRadius() + myRad);
                if (!(0.0f <= d)) d = 0.0f;
                bool inView = R >= d && (dir.x * fwd.x + fwd.z * dir.z + fwd.y * dir.y) >= cosv;
                uint32_t v = AddTarget(&setA, n, d, inView, false);
                listD.AddUnique(&v);
                if ((uflags >> 8) & 1) {
                    Node* s = FindSubNode(n, 0x52aa6122);
                    if (s && !alerted && seen && s->IsNearTarget() && g_NearLimit != g_NearCmp && owner->id != 0x2d852e6) {
                        Msg m;
                        m.p = me ? (void*)&gauge : 0;
                        m.z = 0;
                        if (!MakeSink(0x60995fc, MsgCallback, &m)->Run())
                            alerted = 1;
                    }
                }
            }
            continue;
        }
        if (n->GetType() == 0x18eb45e) {
            uint32_t fl = n->bflags;
            if ((fl >> 9) & 1) continue;
            if (fl & 4) continue;
        }
        float dx = p->x - pos->x, dy = p->y - pos->y, dz = p->z - pos->z;
        float len = (float)sqrt((double)(dz * dz + dy * dy + dx * dx) + 1e-8);
        float inv = 1.0f / len;
        Vec3 dir = { inv * dx, dy * inv, dz * inv };
        float d = len - (o->GetRadius() + myRad);
        if (!(0.0f <= d)) d = 0.0f;
        bool inRange = !cr->IsHidden() && R >= d && (dir.x * fwd.x + fwd.z * dir.z + fwd.y * dir.y) >= cosv;
        bool sensed = me->CanSense(cr, f1, d);
        if (inRange || sensed) {
            Push(listCreatures, AddTarget(&setA, cr, d, inRange, sensed));
            if (!cr->aggro) {
                anyBusy |= cr->body()->IsBusy();
                if (cr->groupId == groupId)
                    ++count;
                else
                    otherGroup = true;
            } else if (bestDist > d) {
                bestDist = d;
                best = cr;
            }
        } else if (hideCheck && cr->IsHidden() && cr->body()->IsBusy() && R >= d
                   && (dir.x * fwd.x + fwd.z * dir.z + fwd.y * dir.y) >= cosv) {
            Tuning* x = cr->Lookup(cr->GetSpeciesKey());
            if (x && x->range > d) {
                bool st = (cr->bflags >> 9) & 1;
                anyHidden = true;
                if (x->GetBound(st) > d) {
                    anyBusy = true;
                    cr->SetStealthed(false, false);
                }
            }
        }
    }
    uint32_t endv = (uint32_t)lp->e;
    SortScores(listCreatures.b, listCreatures.e, endv);
    SortScores(listB.b, listB.e, endv);
    SortScores(listC.b, listC.e, endv);
    SortScores(listD.b, listD.e, endv);
    if (best)
        ((OwnerSub*)((char*)owner + 8))->PostEvent(0x40000, 0, g_PostDuration, best);

    Node* tgt = me->GetTargetAsCreature();
    bool al = flagSet.Test(4);
    bool setFlag = al;
    if (!setFlag) {
        if (tgt) {
            void* a = tgt->GetSpeciesProfile();
            void* b = me->GetSpeciesProfile();
            if (a != b) setFlag = true;
        }
        if (!setFlag && otherGroup) setFlag = true;
    }
    if (setFlag)
        owner->flags |= 0x10;
    else
        owner->flags &= ~0x10u;
    if (count > 0)
        owner->flags |= 0x20;
    else
        owner->flags &= ~0x20u;
    if (NounManager()->GetAvatar()) return;
    if (anyBusy) { mode = 1; return; }
    if (anyHidden) { mode = 2; return; }
    calm = 1;
    mode = 0;
}
