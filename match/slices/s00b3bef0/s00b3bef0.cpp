// Slice s00b3bef0 -- 0x00b3c1a0: refresh the set of on-screen game objects that get a
// priority-sorted "visible object" entry (v1) and the shared selected-object set (g_sel).
#include "types.h"
#include <math.h>
#include <string.h>

struct Vec3 { float x, y, z; };
struct Key3 { uint32_t instance, type, group; };
struct Aux { uint32_t id; uint16_t a; uint16_t b; };
struct Mat44 { float m[4][4]; };

#define VPAD10(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); \
    virtual void p##4(); virtual void p##5(); virtual void p##6(); virtual void p##7(); \
    virtual void p##8(); virtual void p##9();

struct Model;

struct ModelOwner {
    VPAD10(a) VPAD10(b) VPAD10(c) VPAD10(d) VPAD10(e) VPAD10(f) VPAD10(g) VPAD10(h) VPAD10(i)
    virtual void pad90();
    virtual void pad91();
    virtual void Destroy(Model* m, bool flag);   // slot 92 (+0x170)
};

// object with an intrusive reference count at +0x40
struct Model {
    ModelOwner* owner;      // +0x00
    uint32_t flags;         // +0x04
    uint32_t pad08;
    float x, y, z;          // +0x0c
    float scale;            // +0x18
    uint32_t pad1c[(0x40 - 0x1c) / 4];
    int refCount;           // +0x40
    uint32_t pad44[(0x64 - 0x44) / 4];
    struct Holder* holder;  // +0x64
    uint32_t pad68;
    float radius;           // +0x6c
};

static inline void ReleaseModel(Model* m)
{
    if (m) {
        int n = m->refCount;
        if (n > 1) {
            m->refCount = n - 1;
        } else {
            bool b = (m->flags >> 31) & 1;
            m->owner->Destroy(m, b);
        }
    }
}

struct Entry {
    Model* ref;
    float f;
};

Entry* __cdecl CopyEntries(Entry* first, Entry* last, Entry* dest);   // 0x00b36530

struct EntryVec {
    Entry* mpBegin;
    Entry* mpEnd;
    Entry* mpCap;
    void DestructRange(Entry* first, Entry* last);   // 0x00b36130
    void Resize(unsigned n);                          // 0x00b3aaf0
    void clear() { erase(mpBegin, mpEnd); }
    Entry* erase(Entry* first, Entry* last)
    {
        Entry* position = CopyEntries(last, mpEnd, first);
        DestructRange(position, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    Entry* erase(Entry* position)
    {
        if (position + 1 < mpEnd)
            CopyEntries(position + 1, mpEnd, position);
        --mpEnd;
        ReleaseModel(mpEnd->ref);
        return position;
    }
};

struct PtrVec {
    void** mpBegin;
    void** mpEnd;
    void** mpCap;
    void DoInsertValue(void** position, void** const value);   // 0x005481d0
    void clear() { erase(mpBegin, mpEnd); }
    void** erase(void** first, void** last)
    {
        memcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= (last - first);
        return first;
    }
    __forceinline void insert(void* value)
    {
        void** it = mpBegin;
        int d = mpEnd - mpBegin;
        while (d > 0) {
            int step = d >> 1;
            if ((uint32_t)it[step] < (uint32_t)value) {
                it += step + 1;
                d -= step + 1;
            } else {
                d = step;
            }
        }
        if (it == mpEnd)
            insertAt(it, value);
        else if ((uint32_t)value < (uint32_t)*it)
            insertAt(it, value);
    }
    __forceinline void insertAt(void** position, void* value)
    {
        if (mpEnd == mpCap || position != mpEnd) {
            DoInsertValue(position, &value);
        } else {
            if (mpEnd) *mpEnd = value;
            ++mpEnd;
        }
    }
};

extern PtrVec g_sel;    // 0x0167ea68

struct TrueTag {};

struct RkNode {
    RkNode* right;
    RkNode* left;
    RkNode* parent;
};

void __cdecl FreeMem(void* p);   // 0x00f47380

struct RkTree {
    uint32_t cmp;
    RkNode* anchorRight;
    RkNode* anchorLeft;
    RkNode* anchorParent;
    uint8_t color;
    uint32_t size;
    RkTree()
    {
        anchorRight = (RkNode*)&anchorRight;
        anchorLeft = (RkNode*)&anchorRight;
        anchorParent = 0;
        color = 0;
        size = 0;
    }
    ~RkTree()
    {
        RkNode* n = anchorParent;
        while (n) {
            DoNukeSubtree(n->right);
            RkNode* next = n->left;
            FreeMem(n);
            n = next;
        }
    }
    RkNode** Find(RkNode** out, const Key3* key);                       // 0x00422b00
    void Insert(void* out, const Key3* key, TrueTag tag);               // 0x004290c0
    void DoNukeSubtree(RkNode* n);                                      // 0x004e8a30
};

struct GameData {
    VPAD10(a) VPAD10(b) VPAD10(c)
    virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34();
    virtual void Notify(int flag);            // slot 35 (+0x8c)
    virtual void p36(); virtual void p37();
    virtual const Key3* GetKey();             // slot 38 (+0x98)
};

struct Holder {
    virtual void h0(); virtual void h1(); virtual void h2();
    virtual GameData* Cast(uint32_t id);      // slot 3 (+0xc)
};

struct GameDataVec {
    uint32_t pad;
    GameData** mpBegin;   // +4
    GameData** mpEnd;     // +8
};

struct NounMgr {
    GameDataVec* GetGameDataVector(void* a, void* b, void* c, void* d, uint32_t id);   // 0x00b21340
};
NounMgr* __cdecl GetNounMgr();   // 0x00b3d300

void __cdecl Fn_b21080();   // 0x00b21080
void __cdecl Fn_b22e80();   // 0x00b22e80
void __cdecl Fn_b22ea0();   // 0x00b22ea0
void __cdecl Fn_b1e520();   // 0x00b1e520

struct PropList {
    int GetIntProperty(uint32_t id);          // 0x006a2660
    float GetFloatProperty(uint32_t id);      // 0x006a2710
    bool GetDescription(uint32_t id);         // 0x006a25a0
};
extern PropList* g_AppProps;   // 0x015fd918

unsigned __cdecl GetCurrentGameMode();   // 0x00b5b800

struct ResMgr {
    VPAD10(a)
    virtual void q10(); virtual void q11(); virtual void q12(); virtual void q13(); virtual void q14();
    virtual void q15(); virtual void q16(); virtual void q17(); virtual void q18();
    virtual void Preload(const Key3* key, const Aux* aux);   // slot 19 (+0x4c)
};
ResMgr* __cdecl GetResMgr();   // 0x00401010

struct Viewer {
    uint32_t pad[0x40 / 4];
    Mat44 w2c;   // +0x40
    Mat44 c2clip; // +0x80
    void GetCameraLocationInfo(Vec3* a, Vec3* b, Vec3* c, Vec3* d);   // 0x007c3d30
};
struct ViewerHolder {
    virtual void h0(); virtual void h1(); virtual void h2(); virtual void h3(); virtual void h4();
    virtual void h5(); virtual void h6();
    virtual Viewer* GetViewer();           // +0x1c
};
struct AppSub {
    VPAD10(s) VPAD10(t)
    virtual ViewerHolder* GetHolder();     // +0x50 (slot 20)
};
AppSub* __cdecl App();   // 0x0067dd10

bool __cdecl Fn_b36030(Model* m);   // 0x00b36030

struct Filter {
    uint32_t a, b, c, d;
    bool (__cdecl *cb)(Model*);
    uint8_t e, f;
};

struct World {
    virtual void AddRef();
    virtual void Release();
    virtual void w2(); virtual void w3(); virtual void w4(); virtual void w5(); virtual void w6();
    virtual void w7(); virtual void w8(); virtual void w9(); virtual void w10(); virtual void w11();
    virtual void w12(); virtual void w13();
    virtual bool Query(Vec3* pos, float radius, PtrVec* out, Filter* filter);   // slot 14 (+0x38)
};
World* __cdecl GonzagoModelWorld();   // 0x00b3d520

void __cdecl SortEntries(Entry* first, Entry* last, World* w);    // 0x00b3c120
Entry* __cdecl FindDup(Entry* first, Entry* last, Key3 key);      // 0x00b360d0

struct ModelVec {
    Model** mpBegin;
    Model** mpEnd;
    Model** mpCap;
    void clear() { erase(mpBegin, mpEnd); }
    Model** erase(Model** first, Model** last)
    {
        memcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= (last - first);
        return first;
    }
};

struct VisMgr {
    uint32_t pad0[0x2c / 4];
    ModelVec nearby;          // +0x2c
    uint32_t pad1[(0x10c - 0x38) / 4];
    bool flagA;               // +0x10c
    bool flagB;               // +0x10d
    bool flagC;               // +0x10e
    bool flagD;               // +0x10f
    EntryVec entries;         // +0x110
    void UpdateVisible();     // 0x00b3c1a0
};

// VisMgr::UpdateVisible @ 0x00b3c1a0
void VisMgr::UpdateVisible()
{
    int n = entries.mpEnd - entries.mpBegin;
    for (int i = 0; i < n; i++) {
        Entry& e = entries.mpBegin[i];
        Model* m = e.ref;
        m->flags &= 0xffffdfff;
    }
    entries.clear();

    int maxA = g_AppProps->GetIntProperty(0xabe88610);
    int maxB = g_AppProps->GetIntProperty(0x58d9d3aa);
    float thresh = g_AppProps->GetFloatProperty(0xa352f43e);

    bool a;
    if (GetCurrentGameMode() == 0x1654c10 && g_AppProps->GetDescription(0xe328373f))
        a = true;
    else
        a = false;
    bool b = g_AppProps->GetDescription(0xda4e441f);
    bool c = g_AppProps->GetDescription(0xee29756f);
    bool d = g_AppProps->GetDescription(0xc1f80d97);

    if (flagA != a || flagB != b || flagC != c || flagD != d) {
        flagA = a;
        flagD = d;
        flagB = b;
        flagC = c;
        Aux aux;
        aux.id = 0x2ea8fb98;
        aux.b = 4;
        aux.a = 0x100;
        NounMgr* nm = GetNounMgr();
        GameDataVec* gv = nm->GetGameDataVector((void*)Fn_b21080, (void*)Fn_b22e80,
                                                           (void*)Fn_b22ea0, (void*)Fn_b1e520, 0x1186577);
        RkTree tree;
        GameData** p = gv->mpBegin;
        GameData** pend = gv->mpEnd;
        for (; p != pend; ++p) {
            GameData* gd = *p;
            Key3 key = *gd->GetKey();
            if (a && key.instance != 0) {
                bool f;
                switch (key.type) {
                case 0x2399be55:
                    f = flagC;
                    break;
                case 0x24682294:
                case 0x476a98c7:
                    f = flagD;
                    break;
                default:
                    goto skip;
                }
                if (f) {
                    RkNode* it;
                    RkNode* found = *tree.Find(&it, &key);
                    if (found == (RkNode*)&tree.anchorRight) {
                        GetResMgr()->Preload(&key, &aux);
                        uint32_t outbuf[2];
                        tree.Insert(outbuf, &key, TrueTag());
                    }
                }
            }
        skip:
            gd->Notify(1);
        }
        g_sel.clear();
    }

    if (a && !b) {
        Viewer* viewer = App()->GetHolder()->GetViewer();
        Vec3 camPos;
        viewer->GetCameraLocationInfo(&camPos, 0, 0, 0);
        nearby.clear();
        World* world = GonzagoModelWorld();
        if (world) {
            world->AddRef();
            Filter filter;
            filter.a = 0; filter.b = 0; filter.c = 0; filter.d = 0;
            filter.cb = Fn_b36030;
            filter.e = 0; filter.f = 0;
            world->Query(&camPos, 128.0f, (PtrVec*)&nearby, &filter);
        }
        EntryVec* v = &entries;
        int cnt = nearby.mpEnd - nearby.mpBegin;
        v->Resize(cnt);
        cnt = nearby.mpEnd - nearby.mpBegin;
        for (int i = 0; i < cnt; i++) {
            Model* m = nearby.mpBegin[i];
            float x = m->x, y = m->y, z = m->z;
            float size = m->radius * m->scale;
            const Mat44& W = viewer->w2c;
            const Mat44& C = viewer->c2clip;
            float cx = ((z * W.m[2][0] + y * W.m[1][0]) + W.m[0][0] * x) + W.m[3][0];
            float cy = ((x * W.m[0][1] + y * W.m[1][1]) + z * W.m[2][1]) + W.m[3][1];
            float cz = ((y * W.m[1][2] + W.m[0][2] * x) + z * W.m[2][2]) + W.m[3][2];
            Entry* e = &v->mpBegin[i];
            float r;
            if (cy > 0.0f)
                r = size / cy;
            else
                r = size / (size - cy) - 1.0f;
            float inv = 1.0f / (((cx * C.m[0][3] + cz * C.m[2][3]) + C.m[1][3] * cy) + C.m[3][3]);
            float sx = inv * (((cx * C.m[0][0] + cz * C.m[2][0]) + C.m[1][0] * cy) + C.m[3][0]);
            float sy = inv * (((C.m[0][1] * cx + cy * C.m[1][1]) + cz * C.m[2][1]) + C.m[3][1]);
            Model* old = e->ref;
            e->f = (1.0f - sqrtf(sx * sx + sy * sy)) + r;
            if (m != old) {
                m->refCount++;
                e->ref = m;
                ReleaseModel(old);
            }
        }
        SortEntries(v->mpBegin, entries.mpEnd, world);
        g_sel.clear();

        Entry* ep = v->mpBegin;
        int k = 0;
        int count = 0;
        if (ep != entries.mpEnd) {
            do {
                if (count >= maxB)
                    break;
                Holder* h = ep->ref->holder;
                GameData* gd = h ? h->Cast(0x1186577) : 0;
                const Key3* kp = gd->GetKey();
                Key3 key = *kp;
                bool dup = FindDup(v->mpBegin, ep, key) != ep;
                if (!dup && k >= maxA) {
                    entries.erase(ep);
                } else {
                    ep->ref->flags |= 0x2000;
                    if (ep->f > thresh)
                        g_sel.insert(ep->ref);
                    if (!dup)
                        k++;
                    count++;
                    ep++;
                }
            } while (ep != entries.mpEnd);
        }
        entries.erase(ep, entries.mpEnd);
        if (world)
            world->Release();
    }
}

// ---------------------------------------------------------------------------------------------------
// Priority-entry sort/merge plumbing.

// Comparator functor. The original calls it as a __thiscall member whose dummy `this` is the
// address of one of the caller's stack arguments; nothing reads it.
struct EntryLess {
    bool Less(Entry* a, Entry* b);                                   // 0x00b385d0
};

void __cdecl SeqBegin(Entry* pivot, Entry* first, void* ctx);        // 0x00b3ab70
void __cdecl SeqEnd(Entry* pivot, Entry* first, void* ctx);          // 0x00b3abd0
Entry* __cdecl Partition(Entry* first, Entry* last, Entry pivot, void* ctx); // 0x00b38b40
void __cdecl InsertRun(Entry* pivot, int, int, int, Entry e, void* ctx);    // 0x00b39970
void __cdecl SmallSort(Entry* pivot, Entry* first, Entry* last, void* ctx);

// @ 0x00b3bef0
void __cdecl SmallSort(Entry* pivot, Entry* first, Entry* last, void* ctx)
{
    SeqBegin(pivot, first, ctx);
    for (Entry* p = first; p < last; ++p) {
        if (((EntryLess*)&ctx)->Less(p, pivot)) {
            Model* obj = p->ref;
            if (obj)
                obj->refCount++;
            Model* cur = pivot->ref;
            Model* old = p->ref;
            float value = p->f;
            if (cur != old) {
                if (cur)
                    cur->refCount++;
                p->ref = cur;
                ReleaseModel(old);
            }
            p->f = pivot->f;
            if (obj)
                obj->refCount++;
            Entry saved;
            saved.ref = obj;
            saved.f = value;
            InsertRun(pivot, 0, ((int)first - (int)pivot) >> 3, 0, saved, ctx);
            if (obj)
                ReleaseModel(obj);
        }
    }
    SeqEnd(pivot, first, ctx);
}

// @ 0x00b3c020
void __cdecl QuickSort(Entry* first, Entry* last, int depth, void* ctx)
{
    for (;;) {
        int span = (int)last - (int)first;
        if ((span & -8) <= 0xe0 || depth <= 0) {
            if (depth == 0)
                SmallSort(first, last, last, ctx);
            return;
        }
        int count = span >> 3;
        Entry* mid = first + count / 2;
        Entry* final = last - 1;
        Entry* pivot;
        if (((EntryLess*)&depth)->Less(first, mid)) {
            if (((EntryLess*)&depth)->Less(mid, final))
                pivot = mid;
            else if (((EntryLess*)&depth)->Less(first, final))
                pivot = final;
            else
                pivot = first;
        } else {
            if (((EntryLess*)&depth)->Less(first, final))
                pivot = first;
            else if (((EntryLess*)&depth)->Less(mid, final))
                pivot = final;
            else
                pivot = mid;
        }
        Entry copy = *pivot;
        if (copy.ref)
            copy.ref->refCount++;
        Entry* cut = Partition(first, last, copy, ctx);
        depth--;
        QuickSort(cut, last, depth, ctx);
        last = cut;
    }
}

// ---------------------------------------------------------------------------------------------------
// Game-mode dependent scalar selection.

// @ 0x00b3ce80
float __fastcall ModeValue(const float* self)
{
    unsigned mode = GetCurrentGameMode();
    if (mode == 0x01654c01)
        return self[0];
    if (mode == 0x01654c02)
        return self[1];
    if (mode == 0x01654c04)
        return self[2];
    if (mode == 0x01654c05)
        return self[3];
    return 1.0f;
}

struct ModeValues {
    uint8_t pad00[0x10];
    float a;        // +0x10
    uint8_t pad14[4];
    float b;        // +0x18
    uint8_t pad1c[4];
    float c;        // +0x20
    uint8_t pad24[4];
    float d;        // +0x28
};

extern float g_01465544;                                             // 0x01465544

// @ 0x00b3cec0
float __fastcall ModeValueAlt(const ModeValues* self)
{
    unsigned mode = GetCurrentGameMode();
    if (mode == 0x01654c01)
        return self->a;
    if (mode == 0x01654c02)
        return self->b;
    if (mode == 0x01654c04)
        return self->c;
    if (mode == 0x01654c05)
        return self->d;
    return g_01465544;
}

// ---------------------------------------------------------------------------------------------------
// Per-frame visible-object update.

struct Effect {
    virtual void e00(); virtual void e04(); virtual void e08(); virtual void e0c();
    virtual void SetCallback(int32_t which, void* fn, int32_t arg);   // +0x10
    virtual void e14(); virtual void e18(); virtual void e1c(); virtual void e20();
    virtual void SetTime(float t, int32_t flags);                     // +0x24
};

struct ModelMgr {
    void** vtbl;
    uint32_t Capacity() { return ((uint32_t (__thiscall*)(ModelMgr*))vtbl[0x100 / 4])(this); }
    void Flush() { ((void (__thiscall*)(ModelMgr*))vtbl[0x104 / 4])(this); }
    void* Models() { return ((void* (__thiscall*)(ModelMgr*))vtbl[0xfc / 4])(this); }
};

struct PlanetModelObj {
    uint8_t pad00[0x24];
    ModelMgr* mgr;          // +0x24
    bool Active();          // 0x00b7ec40
};

struct ModeState {
    uint8_t pad00[0x20];
    int32_t field20;        // +0x20
};

struct Property {
    uint8_t pad00[0x12];
    uint16_t type;          // +0x12
    uint32_t* GetUInt();    // 0x0041ea00
    float* GetFloat();      // 0x0041ea70
};

struct DirectPropList {
    virtual void p00(); virtual void p04(); virtual void p08(); virtual void p0c();
    virtual void p10(); virtual void p14(); virtual void p18(); virtual void p1c();
    virtual void p20();
    virtual bool GetProperty(uint32_t key, Property** out);           // +0x24
};

// game-data view used by the visibility filter below
struct GD2 {
    virtual void g00(); virtual void g01(); virtual void g02(); virtual void g03();
    virtual void g04(); virtual void g05(); virtual void g06(); virtual void g07();
    virtual void g08(); virtual void g09(); virtual void g10(); virtual void g11();
    virtual void g12(); virtual void g13(); virtual void g14(); virtual void g15();
    virtual void g16(); virtual void g17();
    virtual bool Ready();                                             // +0x48
    uint8_t pad04[0x4c];
    uint32_t flags50;       // +0x50
    uint8_t pad54[0x1d];
    uint8_t flag71;         // +0x71
    uint8_t pad72[3];
    uint8_t flag75;         // +0x75
};

struct ModelRec { float x, y, z, w; };

struct Model2 {
    void** vtbl;
    Vec3* GetPos() { return ((Vec3* (__thiscall*)(Model2*))vtbl[0x2c / 4])(this); }
    float GetScale() { return ((float (__thiscall*)(Model2*))vtbl[0x74 / 4])(this); }
};

struct PtrVec2 {
    void** begin;
    void** end;
    void** cap;
    void push_back(void** value);                                     // 0x00c072f0
};

struct VisNode {
    void** vtbl;   // +0x00
    VisNode* next; // +0x04
};

struct FrameVis {
    uint8_t pad00[0x20];
    VisNode sentinel;      // +0x20
    uint32_t pad28;
    ModelVec nearby;       // +0x2c
    uint8_t pad38[0xc2 - 0x38];
    uint8_t enabled;       // +0xc2
    uint8_t padc3[0x108 - 0xc3];
    Effect* effect;        // +0x108
    void Update(uint32_t param2, uint32_t param3);                    // 0x00b3c990
};

extern Vec3 g_0167ea30;                                             // 0x0167ea30
extern Effect* g_0167ea58;                                          // 0x0167ea58

PlanetModelObj* __cdecl SP_PlanetModel();                            // 0x00b3d350
ModeState* __cdecl GetModeState();                                   // 0x00b3d310
void __cdecl Fn_b36820();                                            // 0x00b36820
void __cdecl Fn_b34280();                                            // 0x00b34280
void __cdecl Fn_b34380(Effect* e, float t);                          // 0x00b34380
int __cdecl Fn_b33e80(GD2* gd);                                      // 0x00b33e80
void __cdecl Fn_b81630(Vec3* dst, Vec3* src);                        // 0x00b81630
void __cdecl Fn_b370f0(void** first, void** stop, void** last, uint32_t count); // 0x00b370f0

struct InlineBuf {
    uint32_t owner;        // +0x00 (original's vec.begin[-1])
    Model* items[128];
};

// @ 0x00b3c990
void FrameVis::Update(uint32_t param2, uint32_t param3)
{
    AppSub* app = App();
    ViewerHolder* holder = app->GetHolder();
    Viewer* viewer = holder->GetViewer();
    viewer->GetCameraLocationInfo(&g_0167ea30, 0, 0, 0);

    if (!enabled)
        return;

    PlanetModelObj* pm = SP_PlanetModel();
    if (g_0167ea58 && pm && pm->mgr) {
        ModeState* mode = GetModeState();
        void* callback;
        if (mode->field20 == 0)
            callback = (void*)Fn_b36820;
        else
            callback = (void*)Fn_b34280;
        g_0167ea58->SetCallback(1, callback, 0);
    }
    if (effect && pm && pm->mgr)
        effect->SetCallback(1, (void*)Fn_b34280, 0);

    VisNode* node = sentinel.next ? (VisNode*)((uint8_t*)sentinel.next - 4) : 0;
    VisNode* stop = &sentinel;
    while (node != stop) {
        ((void (__thiscall*)(VisNode*, uint32_t, uint32_t))node->vtbl[1])(node, param2, param3);
        node = node->next ? (VisNode*)((uint8_t*)node->next - 4) : 0;
    }

    if (g_0167ea58) {
        float t = (float)(param3 * 0.001);
        float f = 0.2f;
        if (t <= 0.2f)
            f = t;
        g_0167ea58->SetTime(f, 0);
        Fn_b34380(g_0167ea58, f);
    }
    if (effect) {
        float t = (float)(param3 * 0.001);
        float f = 0.2f;
        if (t <= 0.2f)
            f = t;
        effect->SetTime(f, 0);
        Fn_b34380(effect, f);
    }

    if (pm && pm->Active()) {
        uint32_t u1 = 0;
        uint32_t u2 = 0;
        float radius = 25.0f;
        float scale = 1.0f;
        DirectPropList* props = (DirectPropList*)g_AppProps;
        if (props) {
            Property* prop;
            if (props->GetProperty(0x5b5575e, &prop) && prop->type == 10) {
                u1 = *prop->GetUInt();
                u2 = u1;
            }
            if (props) {
                if (props->GetProperty(0x5b56cc8, &prop) && prop->type == 0xd)
                    radius = *prop->GetFloat();
                if (props && props->GetProperty(0x5b58961, &prop) && prop->type == 0xd)
                    scale = *prop->GetFloat();
            }
        }
        ModelMgr* mgr = pm->mgr;
        uint32_t cap = mgr->Capacity();
        uint32_t take = (u1 < cap) ? u1 : cap;
        if (take != 0 && radius > 0.0f) {
            InlineBuf buf;
            buf.owner = 0;
            PtrVec2 vec;
            vec.begin = (void**)buf.items;
            vec.end = (void**)buf.items;
            vec.cap = (void**)(buf.items + 128);

            World* world = GonzagoModelWorld();
            if (world) {
                world->AddRef();
                Vec3 camCopy;
                Fn_b81630(&camCopy, &g_0167ea30);
                Filter filter;
                memset(&filter, 0, sizeof(filter));
                bool ok = world->Query(&camCopy, radius, (PtrVec*)&nearby, &filter);
                if (ok) {
                    Model** end = nearby.mpEnd;
                    for (Model** it = nearby.mpBegin; it != end; ++it) {
                        Model* m = *it;
                        Holder* h = m->holder;
                        if (!h)
                            continue;
                        GD2* gd = (GD2*)h->Cast(0x1186577);
                        if (!gd)
                            continue;
                        if (gd->Ready() && gd->flag75 && !gd->flag71 &&
                            (gd->flags50 & 0x110) == 0 && Fn_b33e80(gd) == 0) {
                            vec.push_back((void**)&gd);
                        }
                    }
                }
                world->Release();
            }

            uint32_t used = (uint32_t)(vec.end - vec.begin);
            uint32_t n = (take < used) ? take : used;
            take = n;
            Fn_b370f0(vec.begin, vec.begin + n, vec.end, used);
            mgr->Flush();
            ModelRec* recs = (ModelRec*)mgr->Models();
            for (uint32_t i = 0; i < n; i++) {
                Model2* m = (Model2*)vec.begin[i];
                Vec3* pos = m->GetPos();
                recs[i].x = pos->x;
                recs[i].y = pos->y;
                recs[i].z = pos->z;
                float v = m->GetScale() + scale;
                recs[i].w = v * v;
            }
            if (vec.begin && ((uint32_t*)vec.begin)[-1] != 0)
                FreeMem(vec.begin);
        }
    }
    ((VisMgr*)this)->UpdateVisible();
}
