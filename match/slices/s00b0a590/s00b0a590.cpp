// Slice s00b0a590 -- 0x00b0a6f0: per-frame update of the paired "beam" light objects that
// are attached to the nearby interactable objects around the current aim point.
#include "types.h"
#include <math.h>
#include <string.h>

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float ax, float ay, float az) { x = ax; y = ay; z = az; }
};
// per-field float copy (movss) instead of the integer copy of a plain POD
struct FVec3 : Vec3 {
    FVec3() {}
    FVec3(const FVec3& o) { x = o.x; y = o.y; z = o.z; }
    FVec3& operator=(const FVec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Mat3 { float m[9]; };
struct Quat { float x, y, z, w; };

extern FVec3 g_zeroVec;     // 0x0167af5c
extern FVec3 g_axisVec;     // 0x0167b84c
extern Mat3 g_identity;    // 0x0167b554

struct Light;
struct SrcObj;

#define VPAD10(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); \
    virtual void p##4(); virtual void p##5(); virtual void p##6(); virtual void p##7(); \
    virtual void p##8(); virtual void p##9();

struct LightOwner {
    VPAD10(a) VPAD10(b) VPAD10(c) VPAD10(d) VPAD10(e) VPAD10(f) VPAD10(g) VPAD10(h) VPAD10(i)
    virtual void pad90();
    virtual void Update(Light* l, int flag);   // slot 91 (+0x16c)
};


struct SrcObj {
    virtual void AddRef();
    virtual void Release();
    uint32_t pad[3];
    Vec3 pos;          // +0x10
    float pad1c;
    Mat3 mat;          // +0x20
    uint32_t pad44[(0x70 - 0x44) / 4];
    float sizeA;       // +0x70
    float sizeB;       // +0x74
};

struct Light {
    LightOwner* owner;   // +0x00
    uint32_t flags;      // +0x04
    uint16_t dirty;      // +0x08
    uint16_t dirtyCount; // +0x0a
    Vec3 pos;            // +0x0c
    float scale;         // +0x18
    Mat3 mat;            // +0x1c
    uint32_t pad40[9];
    SrcObj* ref;         // +0x64
    uint32_t pad68;
    float radius;        // +0x6c
    Vec3 bmin;           // +0x70
    Vec3 bmax;           // +0x7c
    void Mark(uint16_t f) { dirty |= f; dirtyCount++; }
};

struct Located {
    virtual void l0(); virtual void l1(); virtual void l2(); virtual void l3(); virtual void l4();
    virtual void l5(); virtual void l6(); virtual void l7(); virtual void l8(); virtual void l9();
    virtual void l10();
    virtual const Vec3* GetPosition();     // +0x2c
    virtual const Quat* GetOrientation();  // +0x30
};

struct Avatar { uint32_t pad[0xc0 / 4]; Located loc; };

struct NounObj;
struct NounManager {
    Avatar* GetAvatar();            // 0x00b1fdb0
    NounObj* CreateNoun(uint32_t key);   // 0x00b20c60
};

struct Viewer {
    void GetCameraLocationInfo(Vec3* a, Vec3* b, Vec3* c, Vec3* d);   // 0x007c3d30
};

struct ViewerHolder {
    virtual void h0(); virtual void h1(); virtual void h2(); virtual void h3(); virtual void h4();
    virtual void h5(); virtual void h6();
    virtual Viewer* GetViewer();           // +0x1c
};
struct AppSub {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual ViewerHolder* GetHolder();     // +0x50
};
struct AppObj { virtual void a0(); virtual void a1(); };

struct AimSource {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual void m5(); virtual void m6(); virtual void m7(); virtual void m8(); virtual void m9();
    virtual void m10(); virtual void m11(); virtual void m12(); virtual void m13();
    virtual Vec3* GetPoint(Vec3* out, int flag, FVec3 hint);   // +0x38
};

struct BeamArea {
    void GetEndPoints(Vec3* start, Vec3* end);   // 0x00cb8ba0
};
struct SpaceToolData {
    uint32_t pad[0x124 / 4];
    BeamArea* area;          // +0x124
    uint32_t pad2[(0x174 - 0x128) / 4];
    uint32_t flags174;
    bool HasFlag();                                       // 0x0104cd50
    void* GetStrategy();                                  // 0x0104f930
};
struct Inventory {
    SpaceToolData* GetTool();     // 0x00ff3f00
};
struct SpaceGame {
    Inventory* GetPlayerInventory();   // 0x00a1ad60
};

struct PtrVec {
    SrcObj** begin;
    SrcObj** end;
    SrcObj** cap;
    int zero;
    SrcObj* buf[256];
};

AppSub* __cdecl App();                       // 0x0067dd10
unsigned __cdecl GetCurrentGameMode();       // 0x00b5b800
NounManager* __cdecl GetNounManager();       // 0x00b3d300
SpaceGame* __cdecl SpaceGameGet();           // 0x01002bd0
AimSource* __cdecl GetAimSource();           // 0x00b3d240
Vec3* __cdecl RotateByQuat(Vec3* out, const Vec3* v, const Quat* q);   // 0x0059aed0
void __cdecl operator_delete_array(void* p);                          // 0x00f47380 (operator delete[])

// ---------------------------------------------------------------------------
// pooled simulator items and the auto-ref vectors that hold them
// ---------------------------------------------------------------------------
inline void* operator new(size_t, void* p) { return p; }

struct Key3 { uint32_t a, b, c; };

extern uint32_t g_15673a8;   // 0x015673a8
extern uint32_t g_15673ac;   // 0x015673ac
extern uint32_t g_15673b0;   // 0x015673b0
extern uint32_t g_15673b4;   // 0x015673b4
extern uint32_t g_15673b8;   // 0x015673b8
extern uint32_t g_1567410;   // 0x01567410
extern uint32_t g_156741c;   // 0x0156741c

// reference-counted target: AddRef in slot 0, Release in slot 1
struct RefTarget {
    virtual void AddRef();    // +0x00
    virtual void Release();   // +0x04
};

// 4-byte element of RefVec
struct RefElem {
    RefTarget* mpObject;      // +0x00
    RefElem() : mpObject(0) {}
    RefElem(RefTarget* p) : mpObject(p) { if (p) p->AddRef(); }
    ~RefElem() { if (mpObject) mpObject->Release(); }
    RefElem& operator=(RefTarget* p) {
        if (p != mpObject) {
            if (p) p->AddRef();
            RefTarget* old = mpObject;
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};

// vector<AutoRefCount> (begin/end/capacity)
struct RefVec {
    RefElem* mpBegin;   // +0x00
    RefElem* mpEnd;     // +0x04
    RefElem* mpCap;     // +0x08
    void   F06d90(uint32_t n);                              // 0x00b06d90
    void   insertSlow(RefElem* pos, const RefElem* value);  // 0x00aea5d0
    void   push_back(const RefElem& value) {
        if (mpEnd < mpCap) {
            new ((void*)mpEnd) RefElem(value);
            ++mpEnd;
        } else {
            insertSlow(mpEnd, &value);
        }
    }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    RefElem& operator[](uint32_t i) { return mpBegin[i]; }
};

// vector<uint32_t> used as the 64-entry object bit mask
struct U32Vec {
    uint32_t* mpBegin;   // +0x00
    uint32_t* mpEnd;     // +0x04
    uint32_t* mpCap;     // +0x08
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};

// spatial component every simulator item carries at item+0x34
struct SpatialC {
    VPAD10(a) VPAD10(b) VPAD10(c)
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
    virtual void v34(); virtual void v35(); virtual void v36();
    virtual void SetKey(const Key3* key);   // +0x94
    char pad_04[0x4c];                      // +0x04 .. +0x4f
    uint32_t flags;                         // +0x50
};

struct ItemObj : RefTarget {
    char pad_04[0x30];    // +0x04 .. +0x33
    SpatialC spatial;     // +0x34
};

// noun created for the second grow loop
struct NounObj : RefTarget {
    virtual void n02(); virtual void n03(); virtual void n04(); virtual void n05();
    virtual void n06(); virtual void n07(); virtual void n08(); virtual void n09();
    virtual void n10(); virtual void n11(); virtual void n12(); virtual void n13();
    virtual void n14(); virtual void n15(); virtual void n16(); virtual void n17();
    virtual void n18(); virtual void n19(); virtual void n20();
    virtual void Init();      // +0x54
};

struct PlanetObj {
    virtual void p00(); virtual void p01();
    virtual uint32_t GetId();   // +0x08
};

// ---------------------------------------------------------------------------
// 0x24-byte pooled object and its vector (glyph records share the layout)
// ---------------------------------------------------------------------------
struct GlyphInfoVec { void* mpBegin; void* mpEnd; void* mpCap; };

struct PoolOwner {
    virtual ~PoolOwner();              // slot 0 (overridden by PoolElem)
    uint8_t  mFlag_04;                 // +0x04
    uint8_t  mPad_05[3];               // +0x05
    GlyphInfoVec mGlyphs_08;           // +0x08
    uint32_t mAlloc_14;                // +0x14
    uint32_t mData_18;                 // +0x18
    uint32_t mData_1c;                 // +0x1c
    uint32_t mData_20;                 // +0x20
    PoolOwner(const PoolOwner&);       // 0x00b04520
};

struct PoolElem : PoolOwner {
    PoolElem(const PoolElem& o) : PoolOwner(o) {}
    virtual ~PoolElem();               // 0x007ced20
};

struct PoolVec {
    PoolElem* mpBegin;   // +0x00
    PoolElem* mpEnd;     // +0x04
    PoolElem* mpCap;     // +0x08
    PoolElem* erase(PoolElem* first, PoolElem* last);                     // 0x00b0aee0
    void insert(PoolElem* position, uint32_t n, const PoolElem* value);   // 0x00b0af40
};

extern "C" {
PoolElem* copy_forward(PoolElem* first, PoolElem* last, PoolElem* dst);     // 0x00b06500
PoolElem* copy_backward(PoolElem* first, PoolElem* last, PoolElem* dst);    // 0x00b06550
PoolElem* construct_range(PoolElem* first, PoolElem* last, PoolElem* dst);  // 0x00b05770
void**    construct_cursor(void** out, PoolElem* first, PoolElem* last,
                           PoolElem* result, PoolElem* extra);              // 0x00b056e0
void      fill_n_copy(PoolElem* dst, uint32_t n, const PoolElem* value,
                      PoolElem* extra);                                     // 0x00b05730
void      assign_range(PoolElem* first, PoolElem* last, const PoolElem* src); // 0x00b072d0
PoolElem* destroy_range(PoolElem* first, PoolElem* last, PoolElem* out);    // 0x00affd00
void*     EAAlloc(size_t size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
}

void* __cdecl PlanetModel();                                       // 0x00b3d350
void  __cdecl GetPropertyAsKey(uint32_t id, uint32_t key, uint32_t* out);          // 0x006a1250
void  __cdecl GetPropertyAsKeyInstance(uint32_t id, uint32_t key, uint32_t* out);  // 0x006a12a0

struct BeamMgr2 {
    uint32_t pad0[0x16504 / 4];
    Light** lightBegin;       // +0x16504
    Light** lightEnd;         // +0x16508
    uint32_t pad1[(0x1659c - 0x1650c) / 4];
    uint32_t objMask;         // +0x1659c
    uint32_t pad2[(0x1b8e10 - 0x165a0) / 4];
    int state;                // +0x1b8e10
    RefVec items;             // +0x1b8e14
    uint32_t pad3[(0x1b8f44 - 0x1b8e20) / 4];
    RefVec items2;            // +0x1b8f44
    uint32_t pad4[(0x1b905c - 0x1b8f50) / 4];
    U32Vec bitvec;            // +0x1b905c
    uint32_t pad5[(0x1b9174 - 0x1b9068) / 4];
    RefVec nouns;             // +0x1b9174
    uint32_t pad6[(0x1ba18c - 0x1b9180) / 4];
    uint32_t mode;            // +0x1ba18c
    void Gather(const Vec3* pos, PtrVec* out, uint32_t mask, float radius, char flag, Vec3* extra, char flag2); // 0x00b0a0c0
    void UpdateBeams();       // 0x00b0a6f0
    void UpdateState();       // 0x00b0a590
    void Init();              // 0x00b0b150
    void RemoveAllNouns();    // 0x00b09b00
    void FUN_00b02120();      // 0x00b02120
    void FUN_00b06cd0();      // 0x00b06cd0
    void FUN_00b091d0();      // 0x00b091d0
    ItemObj* CreateItem();    // 0x00b00220
};


// BeamMgr2::UpdateBeams @ 0x00b0a6f0
// BeamMgr2::UpdateBeams @ 0x00b0a6f0
void BeamMgr2::UpdateBeams()
{
    Viewer* viewer = App()->GetHolder()->GetViewer();
    Vec3 camPos(g_zeroVec.x, g_zeroVec.y, g_zeroVec.z);
    Vec3 camDir(g_zeroVec.x, g_zeroVec.y, g_zeroVec.z);
    if (viewer)
        viewer->GetCameraLocationInfo(&camPos, &camDir, 0, 0);

    Vec3 target(g_zeroVec.x, g_zeroVec.y, g_zeroVec.z);
    Vec3 second(g_zeroVec.x, g_zeroVec.y, g_zeroVec.z);
    Vec3* pSecond = 0;
    float radius = 20.0f;
    Vec3 scratch;
    unsigned mode = GetCurrentGameMode();
    if (mode == 0x1654c05) {
        radius = 25.0f;
        Avatar* av = GetNounManager()->GetAvatar();
        if (av) {
            Located* loc = &av->loc;
            const Vec3* a = RotateByQuat(&scratch, &g_axisVec, loc->GetOrientation());
            float d = camDir.x * a->x + a->y * camDir.y + a->z * camDir.z;
            float px = camDir.x - d * a->x;
            float pz = camDir.z - a->z * d;
            float py = camDir.y - a->y * d;
            float inv = 1.0f / sqrtf(py * py + (pz * pz + px * px));
            Vec3 n(inv * px * 16.0f, py * inv * 16.0f, pz * inv * 16.0f);
            const Vec3* lp = loc->GetPosition();
            target.x = n.x + lp->x;
            target.z = lp->z + n.z;
            target.y = lp->y + n.y;
            second = *loc->GetPosition();
            pSecond = &second;
            goto done;
        } else {
            SpaceToolData* tool = SpaceGameGet()->GetPlayerInventory()->GetTool();
            if (tool && tool->HasFlag() && tool->GetStrategy() && tool->area) {
                Vec3 end;
                tool->area->GetEndPoints(&scratch, &end);
                target = end;
                goto done;
            }
        }
        goto dflt;
    } else if (mode == 0x1654c01) {
    dflt:
        target.x = camDir.x * 20.0f + camPos.x;
        target.y = camDir.y * 20.0f + camPos.y;
        target.z = camDir.z * 20.0f + camPos.z;
    } else {
        const Vec3* r = GetAimSource()->GetPoint(&scratch, 1, g_zeroVec);
        target = *r;
    }
done:

    PtrVec v;
    v.zero = 0;
    v.begin = v.buf;
    v.end = v.buf;
    v.cap = v.buf + 256;
    Gather(&target, &v, objMask, radius, 1, pSecond, 1);

    Light** d = lightBegin;
    Light** e = lightEnd;
    SrcObj** s = v.begin;
    if (d != e) {
        do {
            if (s == v.end)
                break;
            SrcObj* src = *s;
            if (src) {
                Light* l1 = *d;
                Light** n = d + 1;
                d = n;
                if (n != e) {
                    Light* l2 = *n;
                    d = n + 1;
                    float a55 = src->sizeA * 0.55f;
                    float t = src->sizeB * 0.35f;
                    float u = src->sizeB - t;
                    float h = a55 * 0.5f;

                    l1->pos = src->pos;
                    l1->Mark(4);
                    l1->mat = src->mat;
                    l1->Mark(2);
                    {
                        Vec3 hi(h, h, t);
                        Vec3 lo(-h, -h, 0.0f);
                        l1->bmax = hi;
                        l1->bmin = lo;
                        Vec3 ext(hi.x - lo.x, hi.y - lo.y, hi.z - lo.z);
                        l1->radius = sqrtf(ext.x * ext.x + ext.y * ext.y + ext.z * ext.z);
                    }
                    if (l1->ref) {
                        SrcObj* old = l1->ref;
                        l1->ref = 0;
                        old->Release();
                    }
                    {
                        SrcObj* old = l1->ref;
                        if (src != old) {
                            src->AddRef();
                            l1->ref = src;
                            if (old) old->Release();
                        }
                    }
                    l1->flags |= 1;
                    l1->owner->Update(l1, 1);

                    float x = src->pos.x, y = src->pos.y, z = src->pos.z;
                    float inv = 1.0f / sqrtf(x * x + y * y + z * z);
                    l2->Mark(4);
                    l2->pos.x = x * inv * t + src->pos.x;
                    l2->pos.y = src->pos.y + y * inv * t;
                    l2->pos.z = src->pos.z + z * inv * t;
                    l2->mat = src->mat;
                    l2->Mark(2);
                    {
                        Vec3 hi(a55, a55, u);
                        Vec3 lo(-a55, -a55, 0.0f);
                        l2->bmax = hi;
                        l2->bmin = lo;
                        Vec3 ext(hi.x - lo.x, hi.y - lo.y, hi.z - lo.z);
                        l2->radius = sqrtf(ext.x * ext.x + ext.y * ext.y + ext.z * ext.z);
                    }
                    if (l2->ref) {
                        SrcObj* old = l2->ref;
                        l2->ref = 0;
                        old->Release();
                    }
                    {
                        SrcObj* old = l2->ref;
                        if (src != old) {
                            src->AddRef();
                            l2->ref = src;
                            if (old) old->Release();
                        }
                    }
                    l2->flags |= 1;
                    l2->owner->Update(l2, 1);
                    d = n + 1;
                    s++;
                    continue;
                }
            } else {
                s++;
                continue;
            }
            e = lightEnd;
        } while (d != e);
    }
    while (d != lightEnd) {
        Light* l = *d;
        l->flags &= ~1u;
        l->mat = g_identity;
        l->scale = 1.0f;
        l->pos = g_zeroVec;
        l->dirty = 0;
        l->dirtyCount = 0;
        SrcObj* r = l->ref;
        if (r) {
            l->ref = 0;
            r->Release();
        }
        l->owner->Update(l, 0);
        d++;
    }
    if (v.begin && v.begin[-1])
        operator_delete_array(v.begin);
}

// ---------------------------------------------------------------------------
// 00b0a590  refresh the interactable item list / mode mask
// ---------------------------------------------------------------------------
// @ 0x00b0a590
void BeamMgr2::UpdateState()
{
    uint32_t i = 0;
    if (state != 0 && state != 1)
        state = 0;
    RemoveAllNouns();
    if (state == 0) {
        items.F06d90(g_15673b0);
        uint32_t n = items.size();
        for (; i < n; ++i) {
            if (items[i].mpObject == 0) {
                RefElem& slot = items[i];
                slot = CreateItem();
                Key3 key;
                key.a = 0xb5bc5ab6;
                key.b = 0x00e6bce5;
                key.c = 0;
                ((ItemObj*)items[i].mpObject)->spatial.SetKey(&key);
                ((ItemObj*)items[i].mpObject)->spatial.flags |= 0x80;
            }
        }
    }
    if (state == 1) {
        if (mode & 0x10) {
            mode &= ~0x10u;
            objMask = 0;
            FUN_00b06cd0();
        }
        if (mode & 1)
            mode |= 0x10;
        else
            mode &= ~0x10u;
        if (mode & 0x10) {
            objMask = 6;
            return FUN_00b091d0();
        }
    }
}

// ---------------------------------------------------------------------------
// 00b0aee0  erase [first,last) out of a pooled-object vector
// ---------------------------------------------------------------------------
static void destroy_values(PoolElem* first, PoolElem* last)
{
    while (first < last) {
        first->~PoolElem();
        ++first;
    }
}

// @ 0x00b0aee0
PoolElem* PoolVec::erase(PoolElem* first, PoolElem* last)
{
    PoolElem* const position = copy_forward(last, mpEnd, first);
    destroy_values(position, mpEnd);
    mpEnd -= last - first;
    return first;
}

// ---------------------------------------------------------------------------
// 00b0b150  first-time setup of the item/noun lists and the object bit mask
// ---------------------------------------------------------------------------
// @ 0x00b0b150
void BeamMgr2::Init()
{
    if (!(mode & 1))
        return;
    if (!(mode & 2)) {
        FUN_00b02120();
        void* pm = PlanetModel();
        PlanetObj* p = pm ? *(PlanetObj**)((char*)pm + 0x24) : 0;
        if (p && p->GetId()) {
            uint32_t id = p->GetId();
            GetPropertyAsKey(id, 0x463cda3, &g_156741c);
            GetPropertyAsKey(id, 0x463d9ba, &g_1567410);
            uint32_t tmp = 0;
            GetPropertyAsKeyInstance(id, 0x463cdb4, &tmp);
            g_15673a8 = tmp;
            g_15673ac = 0;
        }
        uint32_t n = items2.size();
        while (n < g_15673b4) {
            ItemObj* it = CreateItem();
            RefElem ref(it);
            items2.push_back(ref);
            ++n;
        }
        uint32_t m = nouns.size();
        while (m < g_15673b8) {
            NounObj* nw = GetNounManager()->CreateNoun(0x2e96892);
            RefElem ref(nw);
            nw->Init();
            nouns.push_back(ref);
            ++m;
        }
        if (bitvec.size() < 0x40) {
            uint32_t* nb = (uint32_t*)EAAlloc(0x100, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            memcpy(nb, bitvec.mpBegin, (char*)bitvec.mpEnd - (char*)bitvec.mpBegin);
            if (bitvec.mpBegin && ((int*)bitvec.mpBegin)[-1] != 0)
                operator_delete_array(bitvec.mpBegin);
            uint32_t cnt = bitvec.size();
            bitvec.mpBegin = nb;
            bitvec.mpEnd = nb + cnt;
            bitvec.mpCap = nb + 0x40;
        }
    }
    if ((mode & 4) || !(mode & 2))
        UpdateState();
    mode |= 2;
    mode &= ~4u;
}

// ---------------------------------------------------------------------------
// 00b0af40  insert n copies of *value before position
// ---------------------------------------------------------------------------
// @ 0x00b0af40
void PoolVec::insert(PoolElem* position, uint32_t n, const PoolElem* value)
{
    if (n <= (uint32_t)(mpCap - mpEnd)) {
        if (n != 0) {
            const PoolElem temp = *value;
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            PoolElem* const pEnd = mpEnd;
            if (n < nExtra) {
                construct_cursor((void**)&value, mpEnd - n, mpEnd, mpEnd, position);
                mpEnd += n;
                copy_backward(position, pEnd - n, pEnd);
                assign_range(position, position + n, &temp);
            } else {
                fill_n_copy(mpEnd, n - nExtra, &temp, position);
                mpEnd += n - nExtra;
                construct_cursor((void**)&position, position, pEnd, mpEnd, position);
                mpEnd += nExtra;
                assign_range(position, pEnd, &temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        uint32_t nGrowSize = nPrevSize ? nPrevSize * 2 : 1;
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        PoolElem* const pNewData = nNewSize
            ? (PoolElem*)EAAlloc(nNewSize * 0x24, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
            : 0;
        PoolElem* pNewEnd = construct_range(mpBegin, position, pNewData);
        destroy_range(mpBegin, position, pNewData);
        fill_n_copy(pNewEnd, n, value, pNewEnd);
        PoolElem* const tail = pNewEnd + n;
        pNewEnd = construct_range(position, mpEnd, tail);
        destroy_range(position, mpEnd, tail);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete_array(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCap = pNewData + nNewSize;
    }
}
