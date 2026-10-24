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

// ============================================================================
// Simulator record vector / list / hash map (gold7 claim VAs)
// ============================================================================

struct VecA {
    void* b; void* e; void* c;
    VecA& operator=(const VecA&);                  // 0x0050d4e0
};
struct VecB {
    void* b; void* e; void* c;
    VecB& operator=(const VecB&);                  // 0x00473b00
};
struct ByteV {
    void* b; void* e; void* c;
    void assign(const ByteV&);                     // 0x00420e30
};
struct KeyV {
    uint32_t w[12];
    KeyV& operator=(const KeyV&);                  // 0x006609a0
};
struct VecC {
    uint32_t w[0x136];
    void CopyFrom(const VecC&);                    // 0x00bc5070
};
struct VecD {
    uint8_t* b; uint8_t* e; uint8_t* c;
    uint8_t pad[0x28];
    void assign(uint8_t*, uint8_t*);               // 0x0045f430
};

struct Sub {
    uint32_t f00;                                  // +0x000 (vtable for standalone)
    uint32_t f04;                                  // +0x004 (anim handle when embedded)
    VecA v08;                                      // +0x008
    uint8_t pad14[0x2c];
    VecB v40;                                      // +0x040
    uint8_t pad4c[0x10c];
    VecA v158;                                     // +0x158
    uint8_t pad164[0x8c];
    ByteV v1f0;                                    // +0x1f0
    uint8_t pad1fc[0x2c];
    KeyV v228;                                     // +0x228
    VecB v258;                                     // +0x258
    uint8_t pad264[0x1c];
    VecC v280;                                     // +0x280
    VecD v758;                                     // +0x758
    float f78c;                                    // +0x78c
    float f790;                                    // +0x790
    uint32_t d794;                                 // +0x794
    uint32_t d798;                                 // +0x798
    uint8_t b79c;                                  // +0x79c
    uint8_t b79d;                                  // +0x79d
    uint8_t pad79e[2];
    uint32_t d7a0, d7a4, d7a8, d7ac, d7b0;         // +0x7a0
    Sub(const Sub&);                               // 0x00bc54f0
    Sub& Assign(const Sub&);                       // @ 0x00bc6360
};

// @ 0x00bc6360
Sub& Sub::Assign(const Sub& src)
{
    f00 = src.f00;
    f04 = src.f04;
    v08 = src.v08;
    v40 = src.v40;
    v158 = src.v158;
    v1f0.assign(src.v1f0);
    v228 = src.v228;
    v258 = src.v258;
    v280.CopyFrom(src.v280);
    VecD* s = (VecD*)&src.v758;
    VecD* dst = &v758;
    if (dst != s) {
        if (dst->b != dst->e) {
            *dst->b = 0;
            dst->e = dst->b;
        }
        dst->assign(s->b, s->e);
    }
    f78c = src.f78c;
    f790 = src.f790;
    d794 = src.d794;
    d798 = src.d798;
    b79c = src.b79c;
    b79d = src.b79d;
    d7a0 = src.d7a0;
    d7a4 = src.d7a4;
    d7a8 = src.d7a8;
    d7ac = src.d7ac;
    d7b0 = src.d7b0;
    return *this;
}

struct Anim {
    uint32_t pad0;
    void Build(int anim, int* out);                // 0x004b2030
};
struct EntryB {
    int32_t key;                                   // +0x00
    V3 a;                                          // +0x04
    V3 b;                                          // +0x10
    float f1c;                                     // +0x1c
    Sub sub;                                       // +0x20 (0x7b4)
    uint8_t b7d4;                                  // +0x7d4
    uint8_t disabled;                              // +0x7d5
    uint8_t pad7d6[2];
    int32_t state;                                 // +0x7d8
    int32_t busy;                                  // +0x7dc
    uint32_t p7e0;                                 // +0x7e0
    uint32_t p7e4;                                 // +0x7e4
    uint8_t pad7e8[0x878-0x7e8];
    Anim anim;                                     // +0x878
};
struct Node2;                                       // { next, prev, EntryB }
struct FixedState {
    uint32_t w[8];
};
struct ListHead {
    Node2* next;                                   // +0x00
    Node2* prev;                                   // +0x04
    FixedState alloc;                              // +0x08..0x28 (object+0x24..0x44)
    void Init();                                   // 0x00bc51c0
};
struct Node2 {
    Node2* next;
    Node2* prev;
    EntryB e;
};

void __cdecl ReadPropRecord(int a, int b, void* out);   // 0x00bc5730
void __fastcall SubDtor(Sub* p);                         // 0x00bc4730

// ---- vector<Sub> -----------------------------------------------------------
struct SubVec {
    Sub* b; Sub* e; Sub* c;
    SubVec() {}
    SubVec(const SubVec&);                         // @ 0x00bc6e20
    Sub* Erase(Sub*, Sub*);                        // @ 0x00bc7110
    void Insert(Sub*, uint32_t, const Sub&);       // @ 0x00bc7170
};

void* __cdecl SimNew(uint32_t size, const char* name, int a, int b, void* alloc, int line); // 0x00f473a0
void __cdecl MoveRange5(Sub** out, Sub* first, Sub* last, Sub* dst, SubVec* self);          // 0x00bc56b0
Sub* __cdecl CopyRange2(Sub* first, Sub* last, Sub* dst);                                   // 0x00bc56f0
void __cdecl DestroyRange2(Sub* first, Sub* last, Sub* dst);                                // 0x00bc48c0
void __cdecl FillCopy(Sub* dst, uint32_t n, const Sub& value);                              // 0x00bc6540
void __cdecl MoveAssignRange(Sub* dst, Sub* first, Sub* last);                              // 0x00bc65b0
void __cdecl FillValueRange(Sub* pos, Sub* end, const Sub* value);                          // 0x00bc6f40
Sub* __cdecl ShiftTail(Sub* last, Sub* end, Sub* first);                                    // 0x00bc6570
void __fastcall DestroyVecA(SubVec* p);            // 0x00bc5300
void __fastcall DestroyVecB(SubVec* p);            // 0x00bc5210

// @ 0x00bc6e20
SubVec::SubVec(const SubVec& src)
{
    int n = (int)(((char*)src.e - (char*)src.b) / 0x7b4);
    Sub* p = n ? (Sub*)SimNew((uint32_t)n * 0x7b4, "Simulator", 0, 0, (void*)0x13ebb38, 0xd1) : 0;
    b = p;
    e = p;
    c = p + n;
    Sub* outEnd = p;
    MoveRange5(&outEnd, src.b, src.e, p, (SubVec*)&src);
    e = outEnd;
}

// @ 0x00bc7110
Sub* SubVec::Erase(Sub* first, Sub* last)
{
    Sub* newEnd = ShiftTail(last, e, first);
    Sub* oldEnd = e;
    for (Sub* p = newEnd; p < oldEnd; ++p)
        SubDtor(p);
    e += last - first;
    return first;
}

// @ 0x00bc7170
void SubVec::Insert(Sub* pos, uint32_t n, const Sub& value)
{
    uint32_t capN = (uint32_t)(c - b);
    uint32_t usedN = (uint32_t)(e - b);
    if (n > capN - usedN) {
        uint32_t oldN = (uint32_t)(e - b);
        uint32_t newCap = oldN * 2;
        if (oldN == 0)
            newCap = 1;
        uint32_t need = oldN + n;
        if (newCap < need)
            newCap = need;
        Sub* nb;
        if (newCap == 0)
            nb = 0;
        else
            nb = (Sub*)SimNew(newCap * 0x7b4, "Simulator", 0, 0, (void*)0x13ebb38, 0xd1);
        Sub* mid = CopyRange2(b, pos, nb);
        DestroyRange2(b, pos, nb);
        FillCopy(mid, n, value);
        Sub* mid2 = mid + n;
        Sub* end2 = CopyRange2(pos, e, mid2);
        DestroyRange2(pos, e, mid2);
        if (b && ((int*)b)[-1] != 0)
            operator_delete__((void*)b);
        b = nb;
        e = end2;
        c = nb + newCap;
        return;
    }
    if (n == 0)
        return;
    Sub tmp(value);
    Sub* oldEnd = e;
    uint32_t tailN = (uint32_t)(oldEnd - pos);
    if (n < tailN) {
        Sub* srcFirst = oldEnd - n;
        Sub* outEnd = oldEnd;
        MoveRange5(&outEnd, srcFirst, oldEnd, oldEnd, this);
        e += n;
        MoveAssignRange(pos, srcFirst, oldEnd);
        Sub* fillEnd = pos + n;
        FillValueRange(pos, fillEnd, &tmp);
    } else {
        FillCopy(oldEnd, n - tailN, tmp);
        e += n - tailN;
        Sub* outEnd = e;
        MoveRange5(&outEnd, pos, oldEnd, e, this);
        e += tailN;
        Sub* fillEnd = pos + n;
        FillValueRange(pos, fillEnd, &tmp);
    }
    SubDtor(&tmp);
}

// ---- hash map --------------------------------------------------------------
struct HashNode2 {
    uint32_t pad0;
    Sub* begin;                                    // +0x04
    Sub* end;                                      // +0x08
    uint32_t pad0c[3];
    HashNode2* next;                               // +0x18
};

struct HashMap {
    uint32_t field00;                              // +0x00
    void** buckets;                                // +0x04
    uint32_t bucketCount;                          // +0x08
    uint32_t size;                                 // +0x0c
    float loadF;                                   // +0x10
    float growF;                                   // +0x14
    uint32_t field18;                              // +0x18
    void ClearBuckets(void** buckets, uint32_t count);   // @ 0x00bc6eb0
    void Find(void** out, uint32_t* key);                // 0x00aea1b0
    void Insert(void** pos, uint32_t* key, void* value); // 0x00bc6f90
    SubVec* FindOrAdd(uint32_t* key);                    // @ 0x00bc7440
};

struct SimClass {
    uint32_t vtbl0;                                // +0x00
    uint32_t vtbl1;                                // +0x04
    uint8_t pad08[0x14];
    ListHead list;                                 // +0x1c
    uint32_t count;                                // +0x44
    HashMap map;                                   // +0x48
    void BaseCtor();                               // 0x00b5b960
    void BaseDtor();                               // 0x00b5b9a0
    int CreateEntry(int, int, const V3*, const V3*);           // @ 0x00bc64a0
    int CreateEntryCopy(const Sub*, const V3*, const V3*);     // @ 0x00bc65f0
    SimClass();                                    // @ 0x00bc7380
    void Destroy();                                // @ 0x00bc7080
    void ClearMap();                               // @ 0x00bc6f70
};

// @ 0x00bc64a0
int SimClass::CreateEntry(int a, int b, const V3* pa, const V3* pb)
{
    list.Init();
    EntryB* e = (EntryB*)((char*)list.prev + 8);
    e->key = (int)count;
    count++;
    ReadPropRecord(a, b, &e->sub);
    e->f1c = 0.0f;
    int anim = (int)e->sub.f04;
    e->busy = anim;
    b = 0;
    e->anim.Build(anim, &b);
    e->a = *pa;
    e->b = *pb;
    e->b7d4 = 0;
    e->disabled = 0;
    e->state = 0;
    return e->key;
}

// @ 0x00bc65f0
int SimClass::CreateEntryCopy(const Sub* src, const V3* pa, const V3* pb)
{
    list.Init();
    EntryB* e = (EntryB*)((char*)list.prev + 8);
    e->key = (int)count;
    count++;
    const Sub* s = src;
    e->sub.Assign(*s);
    e->f1c = 0.0f;
    int anim = (int)s->f04;
    e->busy = anim;
    src = 0;
    e->anim.Build(anim, (int*)&src);
    e->a = *pa;
    e->b = *pb;
    e->b7d4 = 0;
    e->disabled = 0;
    e->state = 0;
    return e->key;
}

// @ 0x00bc6eb0
void HashMap::ClearBuckets(void** bucketArray, uint32_t n)
{
    uint32_t i = 0;
    while (i < n) {
        HashNode2* node = (HashNode2*)bucketArray[i];
        while (node) {
            HashNode2* cur = node;
            node = cur->next;
            Sub* end = cur->end;
            Sub* p = cur->begin;
            while (p < end) {
                SubDtor(p);
                ++p;
            }
            freeBuf(cur->begin);
            operator_delete__(cur);
        }
        bucketArray[i] = 0;
        ++i;
    }
}

// @ 0x00bc6f70
void SimClass::ClearMap()
{
    HashMap* m = &map;
    m->ClearBuckets((void**)m->buckets, m->bucketCount);
    m->size = 0;
}

// @ 0x00bc7440
SubVec* HashMap::FindOrAdd(uint32_t* key)
{
    void* found = 0;
    Find(&found, key);
    if (found == buckets[bucketCount]) {
        uint32_t k = *key;
        SubVec tmp;
        tmp.b = tmp.e = tmp.c = 0;
        SubVec v(tmp);
        Insert(&found, &k, &v);
        DestroyVecA(&v);
        DestroyVecB(&tmp);
    }
    return (SubVec*)((char*)found + 4);
}

// ---- Simulator object ------------------------------------------------------
struct FixedAlloc {
    FixedState st;
    FixedAlloc(uint32_t size, uint32_t align, uint32_t blocks, uint32_t a,
               uint32_t max, void* alloc, void* free, const char* name);  // 0x00926720
    void Commit();                                 // 0x00926640
};

void __fastcall DestroyList(void* p);              // 0x00bc53f0
void __fastcall CommitAlloc(void* p);              // 0x00926640

// @ 0x00bc7380
SimClass::SimClass()
{
    BaseCtor();
    vtbl0 = (uint32_t)0x1466898;
    vtbl1 = (uint32_t)0x1466890;
    uint32_t zero = 0;
    FixedAlloc fa(0x95c, 4, 0x20, zero, 0xffffffff, (void*)0x6abeb0, (void*)0xf47410, "Simulator/list");
    ListHead* l = &list;
    l->alloc = fa.st;
    l->next = (Node2*)l;
    l->prev = (Node2*)l;
    fa.Commit();
    count = zero;
    map.loadF = 1.0f;
    map.growF = 2.0f;
    map.size = zero;
    map.field18 = zero;
    map.bucketCount = 1;
    map.buckets = (void**)0x154df28;
}

// @ 0x00bc7080
void SimClass::Destroy()
{
    HashMap* m = &map;
    vtbl0 = (uint32_t)0x1466898;
    vtbl1 = (uint32_t)0x1466890;
    m->ClearBuckets((void**)m->buckets, m->bucketCount);
    m->size = 0;
    if (m->bucketCount > 1)
        operator_delete__(m->buckets);
    ListHead* l = &list;
    DestroyList(l);
    CommitAlloc(&l->alloc);
    BaseDtor();
}
