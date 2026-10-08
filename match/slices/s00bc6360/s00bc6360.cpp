// Slice s00bc6360: per-frame update of the creature animation/effect sequence registry
// (intrusive list at this+0x1c of 0x940-byte entries; ctor/lookups are in slice s00bc34c0).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <string.h>

extern "C" void __cdecl operator_delete__(void*);   // 0x00f47380 operator delete[]
static inline void freeBuf(void* p) { if (p && ((int*)p)[-1] != 0) operator_delete__(p); }

struct V3 {
    float x, y, z;
    V3() {}
    V3(const V3& o) { x = o.x; y = o.y; z = o.z; }
};
struct Mat3 {
    float m[9];
    Mat3() {}
    Mat3(const Mat3& o) { for (int i = 0; i < 9; ++i) m[i] = o.m[i]; }
    Mat3& operator=(const Mat3& o) { memcpy(m, o.m, sizeof(m)); return *this; }
};
struct V2 { float x, y; };
struct A12 { uint32_t id, b, c; };                 // 12-byte effect description element (id first)

extern Mat3 gIdentity3;                            // 0x0168ab3c
extern float gOne;                                 // 0x01485720

// Spore ModAPI Math::Transform layout (0x38 bytes)
struct Transform {
    int16_t flags;
    int16_t count;
    V3 offset;
    float scale;
    Mat3 rot;
    Transform() { count = 1; flags = 0; scale = gOne; rot = gIdentity3; }
    void SetOffset(const V3& v) { offset = v; flags |= 4; }
    void SetRotation(const Mat3& r) { rot = r; flags |= 2; ++count; }
};

// ---- external classes ------------------------------------------------------------
struct Effect {
    virtual void v0();
    virtual void Release();                        // +4
    virtual void Start(int a);                     // +8
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void SetTransform(Transform* t);       // +0x18
};
struct EffectsMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool CreateEffect(uint32_t id, int zero, Effect** out);   // +0x2c
};
EffectsMgr* __cdecl GetEffectsManager();           // 0x0067ddd0 SP::EffectsManager

struct Loco {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual float GetScale();                      // +0x74
    bool __thiscall IsNearGoal();                  // 0x00c42e20 SP::cLocomotiveObject::IsNearGoal
};

struct Creature {
    virtual void v0();
    virtual void Release();                        // +4
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7();
    virtual int GetTypeId();                       // +0x20
    uint32_t pad04[0x2f];
    Loco loco;                                     // +0xc0
    bool __thiscall f00c25480(int a, int b);                    // 0x00c25480
    int __thiscall GetBodyPartIndex(int a, int b);              // 0x00c17580
    void __thiscall SetCurrentToolEffect(int a, int b);         // 0x00c24f40
    void __thiscall InterruptAnimation(int a, int b, int c);    // 0x00c12310
    void __thiscall f00c0e640(int a);                           // 0x00c0e640
    int __thiscall f00c0e370();                                 // 0x00c0e370
    bool __thiscall AnimationFinished(int a);                   // 0x00c123f0
    void __thiscall StartIndependentSound(const char* name, const V3* pos, void* ids);  // 0x00c1db40
};

struct Elem16 { uint32_t a, b, c, d; };
struct Elem98 {                                    // fixed_vector<Elem16, 8>
    Elem16* mpBegin; Elem16* mpEnd; uint32_t rest[0x26 - 2];
};

struct FxVec {                                     // vector<AutoRefCount<Effect>>
    Effect** mpBegin; Effect** mpEnd; Effect** mpCap;
    void __thiscall insertFill(Effect** pos, unsigned n, Effect* const* val);   // 0x00a72db0
    void __thiscall erase(Effect** first, Effect** last);                       // 0x00533500
};

struct Planet {
    void* __thiscall BuildSurfaceOrientation2(void* out, V3* pos, V3* up);      // 0x00b7f250
};
Planet* __cdecl GetPlanetModel();                  // 0x00b3d350 SP::PlanetModel
void __cdecl Matrix3FromQuaternion(Mat3* out, void* q);                         // 0x0059c190

struct Reg;
void* __stdcall FUN_00bc3c20(void* out, char* obj, const float* v2, float f);   // slice s00bc34c0

struct Entry {                                     // list node payload (node + 8)
    int key;                                       // +0x00
    V3 a;                                          // +0x04
    V3 b;                                          // +0x10
    uint32_t pad1c[3];
    int* indices;                                  // +0x28 (rec.mIndices.mpBegin)
    uint32_t pad2c[(0x248 - 0x2c) / 4];
    A12* fxBegin; A12* fxEnd;                      // +0x248 effect descriptions
    uint32_t pad250[(0x278 - 0x250) / 4];
    V2* fxPos;                                     // +0x278
    uint32_t pad27c[(0x2a0 - 0x27c) / 4];
    Elem98* lists;                                 // +0x2a0
    uint32_t pad2a4[(0x778 - 0x2a4) / 4];
    char* nameBegin; char* nameEnd;                // +0x778
    uint8_t pad780[0x7bd - 0x780];
    uint8_t b7bd;
    uint8_t pad7be[0x7d0 - 0x7be];
    uint32_t f7d0;
    uint8_t b7d4;
    uint8_t disabled;                              // +0x7d5
    uint8_t pad7d6[2];
    int state;                                     // +0x7d8
    int busy;                                      // +0x7dc
    Creature** crBegin; Creature** crEnd;          // +0x7e0
    uint32_t pad7e8[(0x878 - 0x7e8) / 4];
    int* animIdx;                                  // +0x878
    uint32_t pad87c[(0x8d4 - 0x87c) / 4];
    void* soundIds;                                // +0x8d4 (vector, passed by address)
    uint32_t pad8d8[(0x92c - 0x8d8) / 4];
    FxVec fx;                                      // +0x92c
};
struct Node { Node* next; Node* prev; Entry e; };

struct Reg {
    uint32_t pad00[7];
    Node* head;                                    // +0x1c (sentinel anchor)
    uint32_t pad20[5];
    Node* freeList;                                // +0x34
    void __thiscall f00bc4bf0(Entry* e);           // 0x00bc4bf0
    void __thiscall Update(int a, int b);
};
struct Rec { void __thiscall dtor(); };            // 0x00bc4730

#define LIST_END(self) ((Node*)((char*)(self) + 0x1c))

// @ 0x00bc6690
void __thiscall Reg::Update(int, int)
{
    for (Node* node = head; node != LIST_END(this); node = node->next) {
        Entry* e = &node->e;
        if (e->busy != 0 || e->disabled != 0) continue;
        int n = e->crEnd - e->crBegin;
        if (e->state != 2) {
            if (!e->b7d4) {
                e->b7d4 = 1;
                for (int i = 0; i < n; ++i) {
                    if (!e->crBegin[i]->loco.IsNearGoal()) { e->b7d4 = 0; break; }
                }
            }
            if (!e->b7d4) continue;
            switch (e->state) {
            case 1: {
                bool pending = false;
                for (int i = 0; i < n; ++i) {
                    Elem98* l = &e->lists[e->indices[i]];
                    Creature* c = e->crBegin[i];
                    if (c && c->GetTypeId() == 0x18eb4b7) {
                        Elem16* f = l->mpBegin;
                        if (f->c != -1 && f->d == 0xb)
                            pending |= (c->f00c25480(f->c, 0) == 0);
                    }
                }
                if (!pending) e->state = 2;
                break;
            }
            case 0: {
                e->state = 2;
                for (int i = 0; i < n; ++i) {
                    Elem98* l = &e->lists[e->indices[i]];
                    Creature* c = e->crBegin[i];
                    if (c && c->GetTypeId() == 0x18eb4b7) {
                        Elem16* f = l->mpBegin;
                        if (f->c != -1) {
                            if (f->d == 0xb) {
                                e->state = 1;
                                c->f00c25480(f->c, 0);
                            } else {
                                c->SetCurrentToolEffect(f->c, c->GetBodyPartIndex(f->d, 0));
                            }
                        }
                    }
                }
                break;
            }
            }
            if (e->state != 2) continue;
            // sequence just started: interrupt, play sound, spawn effects
            for (int i = 0; i < n; ++i) {
                Creature* c = e->crBegin[i];
                c->InterruptAnimation(e->lists[e->indices[i]].mpBegin->a, -1, 0);
                c->f00c0e640(e->f7d0);
            }
            if (e->nameBegin != e->nameEnd)
                e->crBegin[0]->StartIndependentSound(e->nameBegin, &e->a, &e->soundIds);
            if (e->fxBegin != e->fxEnd) {
                FxVec* v = &e->fx;
                unsigned cnt = e->fxEnd - e->fxBegin;
                if (cnt > (unsigned)(v->mpEnd - v->mpBegin)) {
                    Effect* nul = 0;
                    v->insertFill(v->mpEnd, cnt - (v->mpEnd - v->mpBegin), &nul);
                } else {
                    v->erase(v->mpBegin + cnt, v->mpEnd);
                }
                for (int i = 0; i < (int)cnt; ++i) {
                    EffectsMgr* fm = GetEffectsManager();
                    Effect** slot = &v->mpBegin[i];
                    if (*slot) { Effect* o = *slot; *slot = 0; o->Release(); }
                    if (fm->CreateEffect(e->fxBegin[i].id, 0, slot)) {
                        float s = e->crBegin[0]->loco.GetScale();
                        V3 pos3;
                        FUN_00bc3c20(&pos3, (char*)e, (const float*)&e->fxPos[i], s);
                        Transform t;
                        t.SetOffset(pos3);
                        uint32_t quatBuf[4];
                        void* q = GetPlanetModel()->BuildSurfaceOrientation2(quatBuf, &pos3, &e->b);
                        Mat3 m;
                        Matrix3FromQuaternion(&m, q);
                        t.SetRotation(m);
                        v->mpBegin[i]->SetTransform(&t);
                        v->mpBegin[i]->Start(0);
                    }
                }
            }
        } else {
            bool allDone = true;
            for (int i = 0; i < n; ++i) {
                Elem98* l = &e->lists[e->indices[i]];
                Creature* c = e->crBegin[i];
                int cur = e->animIdx[i];
                if (cur < (l->mpEnd - l->mpBegin)) {
                    int dur = l->mpBegin[cur].b;
                    allDone = false;
                    bool fin;
                    if (dur > 0) fin = c->f00c0e370() >= dur;
                    else fin = c->AnimationFinished(0);
                    if (fin) {
                        e->animIdx[i] = ++cur;
                        if (cur < (l->mpEnd - l->mpBegin)) {
                            c->InterruptAnimation(l->mpBegin[cur].a, -1, 0);
                            if (c && c->GetTypeId() == 0x18eb4b7) {
                                if (l->mpBegin[0].c != -1) {
                                    int bp;
                                    if (l->mpBegin[cur].d == 0xb) bp = -1;
                                    else bp = c->GetBodyPartIndex(l->mpBegin[cur].d, 0);
                                    c->SetCurrentToolEffect(l->mpBegin[cur].c, bp);
                                }
                            }
                        }
                    }
                }
            }
            if (allDone) {
                int key = e->key;
                for (Node* m = head; m != LIST_END(this); m = m->next) {
                    if (m->e.key == key) { f00bc4bf0(&m->e); break; }
                }
            }
        }
    }
    // reap disabled entries
    for (Node* node = head; node != LIST_END(this); node = node->next) {
        if (node->e.disabled) {
            Node* nxt = node->next;
            Node* s = nxt->prev;
            s->prev->next = s->next;
            s->next->prev = s->prev;
            for (Effect** p = s->e.fx.mpBegin; p < s->e.fx.mpEnd; ++p) if (*p) (*p)->Release();
            freeBuf(s->e.fx.mpBegin);
            freeBuf(s->e.soundIds);
            freeBuf(s->e.animIdx);
            for (Creature** p = s->e.crBegin; p < s->e.crEnd; ++p) if (*p) (*p)->Release();
            freeBuf(s->e.crBegin);
            ((Rec*)((char*)s + 0x28))->dtor();
            s->next = freeList;
            freeList = s;
            node = nxt;
        }
    }
}
