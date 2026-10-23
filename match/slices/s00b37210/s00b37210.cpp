// Slice s00b37210: editor resource / Gonzago layer helpers.
//   - the "gme" console command (dump / views on|off / updates on|off)
//   - the editor-resource destructor and constructor
//   - two eastl-vector assignment helpers (AnalysisInfo / GlyphInfo)
//   - the layer enable/notify path and the effect/planet spawn helper
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int  uint;
typedef unsigned char uchar;

// ---------------------------------------------------------------- CRT / allocator
#define ALLOC_FILE \
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

void* __cdecl EAAllocate(unsigned size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  __cdecl opdel(void* p);                                                                        // 0x00f47380
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned n);
extern "C" void* __cdecl memset(void* dst, int v, unsigned n);

extern wchar_t gEmptyString16[];   // 0x01667bac  eastl::gEmptyString16

// ---------------------------------------------------------------- EA::ArgScript
namespace EA { namespace ArgScript {
struct cArguments {
    int          NumArguments() const;        // 0x00837f30
    const char*  operator[](int i) const;     // 0x00837f20
};
}}

// ---------------------------------------------------------------- eastl string (char)
bool __cdecl eStringEq(const void* str, const char* text);   // 0x00555020
void* __cdecl eStringAssign(void* self, const char* first, const char* last); // 0x00454cb0

struct eString {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;

    eString() : mpBegin(0), mpEnd(0), mpCap(0) {}

    // eastl::basic_string<char>::basic_string(const char*)
    eString(const char* p)
    {
        const char* e = p;
        while (*e)
            ++e;
        unsigned len = (unsigned)(e - p);
        if (len + 1 > 1) {
            char* b = (char*)EAAllocate(len + 1, "Simulator", 0, 0, ALLOC_FILE, 0xd1);
            memcpy(b, p, len);
            b[len] = 0;
            mpBegin = b;
            mpEnd   = b + len + 1;
            mpCap   = b + len + 1;
        } else {
            char* b = (char*)gEmptyString16;
            mpBegin = b;
            mpEnd   = b + 1;
            mpCap   = b + 1;
        }
    }

    __declspec(noinline) eString& assign(const char* first, const char* last)
    {
        eStringAssign(this, first, last);
        return *this;
    }
};

static bool strEq(const eString& s, const char* text) { return eStringEq(&s, text); }

// ---------------------------------------------------------------- game side
struct cEditorGame {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void gv1c(int value, int flag);                 // +0x1c
    virtual void v20();
    virtual void gv24(int enabled);                         // +0x24
    virtual void v28();
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void v5c(); virtual void v60(); virtual void v64(); virtual void v68();
    virtual void v6c(); virtual void v70(); virtual void v74();
    virtual void gv78();                                    // +0x78
};

cEditorGame* __cdecl GetEditorGame();     // 0x00b3d240
int          __cdecl ParseIntArg(const char* s);  // 0x00b214e0

// @ 0x00b37210
void __stdcall EditorConsoleCommand(EA::ArgScript::cArguments* args)
{
    int n = args->NumArguments();
    if (n <= 1)
        return;

    eString cmd(args->operator[](1));

    if (strEq(cmd, "dump"))
        GetEditorGame()->gv78();

    if (strEq(cmd, "views") && n > 2) {
        const char* p = args->operator[](2);
        const char* e = p;
        while (*e)
            ++e;
        cmd.assign(p, e);

        int value = -1;
        if (strEq(cmd, "off")) {
            if (n > 3)
                value = ParseIntArg(args->operator[](3));
            GetEditorGame()->gv1c(value, 0);
        }
        if (strEq(cmd, "on")) {
            if (n > 3)
                value = ParseIntArg(args->operator[](3));
            GetEditorGame()->gv1c(value, 1);
        }
    }

    if (strEq(cmd, "updates") && n > 2) {
        const char* p = args->operator[](2);
        const char* e = p;
        while (*e)
            ++e;
        cmd.assign(p, e);

        int enabled = 1;
        if (strEq(cmd, "off"))
            enabled = 0;
        GetEditorGame()->gv24(enabled);
    }

    if (cmd.mpEnd - cmd.mpBegin > 1 && cmd.mpBegin)
        opdel(cmd.mpBegin);
}

// ---------------------------------------------------------------- external helpers
struct RefObj {                       // minimal COM-ish reference object
    virtual void v00();
    virtual void Release();           // +0x04
    virtual void v08();               // +0x08
};

struct EaVector {
    void* mpBegin;                    // +0x00
    void* mpEnd;                      // +0x04
    char  pad08[8];                   // +0x08
    void* mpCap;                      // +0x10
    void destroy(void* begin, void* end);          // 0x00b36130
};

struct EaHashtable {
    void*  mSelf;                     // +0x00
    void** mpBuckets;                 // +0x04
    uint   mBucketCount;              // +0x08
    uint   mCount;                    // +0x0c
    void freeNodes(void* a, uint b);  // 0x004e3590
    void find(void** out, const uint* key);  // 0x005538f0
    void* end() { return mpBuckets + mBucketCount; }
};

struct IntrusiveList {                // {next, prev}, sentinel lives inside the layer
    void* mpNext;
    void* mpPrev;
    ~IntrusiveList();                 // 0x00620230
};

struct cGonzagoSubsystem {
    void ctor();                      // 0x00b5b960
    void dtor();                      // 0x00b5b9a0
    char data[0x100];
};

struct TreeOps {                      // rbtree inserted at layer+0xc8
    void erase(void* key);            // 0x00b36360
    void insert(void* key, void* value, int flag);   // 0x00b37180
    void nuke(void* node);            // 0x009a9600
};

struct AnalysisVector;

struct cEditorRes {
    void  dtor();                     // 0x00b37440
    cEditorRes* ctor();               // 0x00b379f0
    void  SetAnalysis(const AnalysisVector* other, bool renumber); // 0x00b38140
};

// vtable slot addresses baked into the original image
#define VT_EDITOR_0   ((void*)0x014609f0)
#define VT_EDITOR_4   ((void*)0x014609e0)
#define VT_SUB_0      ((void*)0x01460990)
#define VT_SUB_4      ((void*)0x0146098c)
#define VT_GME_0      ((void*)0x014609f0)
#define VT_GME_4      ((void*)0x014609e0)
#define VT_CTOR_0     ((void*)0x013f1ab0)
#define VT_CTOR_4     ((void*)0x013eb384)
#define VT_FINAL_4    ((void*)0x013eb394)
#define VT_FINAL_0    ((void*)0x013eb938)
#define GLOBAL_90     ((void*)0x0154df28)

extern float gOne;        // 0x01485720
extern float gTwo;        // 0x01470f1c

// @ 0x00b37440
void __thiscall cEditorRes::dtor()
{
    char* self = (char*)this;

    *(void**)self        = VT_EDITOR_0;
    *(void**)(self + 4)  = VT_EDITOR_4;
    *(void**)(self + 8)  = VT_SUB_0;
    *(void**)(self + 0xc)= VT_SUB_4;

    EaVector* vec = (EaVector*)(self + 0x110);
    vec->destroy(vec->mpBegin, vec->mpEnd);
    if (vec->mpBegin && vec->mpBegin != vec->mpCap)
        opdel(vec->mpBegin);

    if (*(RefObj**)(self + 0x108))
        (*(RefObj**)(self + 0x108))->Release();
    if (*(RefObj**)(self + 0xe8))
        (*(RefObj**)(self + 0xe8))->Release();
    if (*(RefObj**)(self + 0xe4))
        (*(RefObj**)(self + 0xe4))->Release();

    ((TreeOps*)(self + 0xc8))->nuke(*(void**)(self + 0xd4));

    if (*(RefObj**)(self + 0xc4))
        (*(RefObj**)(self + 0xc4))->v08();

    void* p = *(void**)(self + 0xac);
    if (p && *(int*)((char*)p - 4) != 0)
        opdel(p);

    EaHashtable* ht = (EaHashtable*)(self + 0x8c);
    ht->freeNodes(ht->mpBuckets, ht->mBucketCount);
    ht->mCount = 0;
    if (ht->mBucketCount > 1)
        opdel(ht->mpBuckets);

    if (*(RefObj**)(self + 0x88))
        (*(RefObj**)(self + 0x88))->Release();

    p = *(void**)(self + 0x2c);
    if (p && p != *(void**)(self + 0x3c))
        opdel(p);

    ((IntrusiveList*)(self + 0x24))->~IntrusiveList();
    ((cGonzagoSubsystem*)(self + 8))->dtor();

    *(void**)(self + 4) = VT_FINAL_4;
    *(void**)self       = VT_FINAL_0;
}

// @ 0x00b375f0  eastl vector<AnalysisInfo>::operator=
struct AnalysisInfo {
    int m0;
    int m4;
    int mIndex;          // +0x08
};

struct AnalysisVector {
    AnalysisInfo* mpBegin;
    AnalysisInfo* mpEnd;
    AnalysisInfo* mpCap;

    __declspec(noinline) AnalysisVector& assign(const AnalysisVector& other);
};

AnalysisInfo* __cdecl vecGrow(unsigned n, AnalysisInfo* first, AnalysisInfo* last);   // 0x00b84c20
AnalysisInfo* __cdecl vecCopy(AnalysisInfo* first, AnalysisInfo* last, AnalysisInfo* dst); // 0x00b84c80
void* __cdecl vecUninitCopy(void* result, AnalysisInfo* first, AnalysisInfo* last,
                            AnalysisInfo* dst, void* extra);                          // 0x00898b80

AnalysisVector& AnalysisVector::assign(const AnalysisVector& other)
{
    if (this == &other)
        return *this;

    unsigned n = (unsigned)(other.mpEnd - other.mpBegin);
    if ((unsigned)(mpEnd - mpBegin) < n) {
        AnalysisInfo* nb = vecGrow(n, other.mpBegin, other.mpEnd);
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            opdel(mpBegin);
        mpCap   = nb + n;
        mpBegin = nb;
        mpEnd   = nb + n;
        return *this;
    }

    unsigned have = (unsigned)(mpEnd - mpBegin);
    if (have < n) {
        vecCopy(other.mpBegin, other.mpBegin + have, mpBegin);
        vecUninitCopy((void*)0, other.mpBegin + have, other.mpEnd, mpEnd, (void*)0);
        mpEnd = mpBegin + n;
        return *this;
    }

    vecCopy(other.mpBegin, other.mpEnd, mpBegin);
    mpEnd = mpBegin + n;
    return *this;
}

// @ 0x00b37720  eastl vector<GlyphInfo>::insert
struct GlyphInfo {
    int m0;
    int m4;
};

struct GlyphVector {
    GlyphInfo* mpBegin;
    GlyphInfo* mpEnd;
    GlyphInfo* mpCap;

    void insert(GlyphInfo* pos, GlyphInfo* first, GlyphInfo* last, int alloc);
};

void* __cdecl elCopy5(void* result, void* first, void* last, void* dst, void* src); // 0x0076ffd0
void  __cdecl elCopyBackward(void* first, void* last, void* dst);                   // 0x0073fe50
void* __cdecl elDoCopy(void* first, void* last, void* dst);                         // 0x00ac4440
void* __cdecl elUninitCopy(void* first, void* last, void* dst);                     // 0x0099efa0

void __thiscall GlyphVector::insert(GlyphInfo* pos, GlyphInfo* first, GlyphInfo* last, int alloc)
{
    (void)alloc;
    if (first == last)
        return;

    unsigned n = (unsigned)(last - first);
    if (n > (unsigned)(mpCap - mpEnd)) {
        unsigned size = (unsigned)(mpEnd - mpBegin);
        unsigned newCap = size * 2;
        if (size == 0)
            newCap = 1;
        if (newCap <= size + n)
            newCap = size + n;

        GlyphInfo* nb = newCap
            ? (GlyphInfo*)EAAllocate(newCap * 8, "Simulator", 0, 0, ALLOC_FILE, 0xd1)
            : 0;

        GlyphInfo* mid = (GlyphInfo*)elUninitCopy(mpBegin, pos, nb);
        GlyphInfo* end = (GlyphInfo*)elCopy5(pos, first, last, mid, 0);
        GlyphInfo* fin = (GlyphInfo*)elUninitCopy(pos, mpEnd, end);
        if (mpBegin && mpBegin != (GlyphInfo*)0)
            opdel(mpBegin);
        mpBegin = nb;
        mpEnd   = fin;
        mpCap   = nb + newCap;
        return;
    }

    unsigned tail = (unsigned)(mpEnd - pos);
    if (n < tail) {
        GlyphInfo* oldEnd = mpEnd;
        GlyphInfo* cut    = mpEnd - n;
        elCopy5(pos, cut, oldEnd, oldEnd, first);
        mpEnd += n;
        elCopyBackward(pos, cut, oldEnd);
        elDoCopy(first, last, pos);
        return;
    }

    GlyphInfo* newEnd = pos + n;
    elCopy5(pos, mpEnd, newEnd, newEnd, first);
    mpEnd += n;
    elCopy5(pos, first, last, pos, 0);
    elCopyBackward(first, last, pos);
}

// ---------------------------------------------------------------- editor layer
struct LayerNode;

struct LayerObject {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual bool Match(uint id);          // +0x0c
    virtual void v10(); virtual void v14();
    virtual void Notify(bool on);         // +0x18
};

struct LayerArg {                         // argument of AddObject
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual bool Match(uint id);          // +0x0c
    virtual void v10();
    virtual void Notify(int flag);        // +0x18
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c(); virtual void v30(); virtual void v34();
    virtual unsigned Key();               // +0x38
    void* mpResult;                       // +0x14
};

struct LayerNodeObj {
    virtual void v00();
    virtual void v04();
    virtual LayerObject* GetObject();     // +0x08
    virtual bool Match(uint id);          // +0x0c
};

struct Link {
    Link* mpNext;
    Link* mpPrev;
};

struct LayerNode {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual LayerObject* GetObject();     // +0x0c
    virtual void v10(); virtual void v14();
    virtual void Notify(bool on);         // +0x18
    Link  mLink;                          // +0x04
};

struct Vec3;

struct cEditorLayer {
    void AddObject(void* arg);            // 0x00b37b70
    void SpawnEffect(uint key, const void* a, const void* b, int idA, int idB, int arg6); // 0x00b37c60
    virtual void v00();                   // +0x00
    virtual void v04();                   // +0x04
    virtual void gv08(uint id, bool on);  // +0x08
    virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void gv18(void* msg);         // +0x18
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c();
    virtual void gv40(int cmd, void* data, int n);   // +0x40
    virtual void gv44(int cmd, void* data, int n);   // +0x44
    virtual void v48();
    virtual void gv4c(int cmd, void* data);          // +0x4c
};

static LayerNode* NodeFromLink(Link* l)
{
    return l ? (LayerNode*)((char*)l - 4) : 0;
}

// helper declarations for the layer's embedded containers
void __cdecl rbIncrementStub(void*);                 // 0x00921580
void* __cdecl mapLowerBound(void* map, void* end, uint* key, unsigned char flag); // 0x00d01260

// the intrusive rbtree living at cEditorLayer+0xc8
struct LayerTree {
    void*         mpUnk0;      // +0x00
    void*         mpHeaderA;   // +0x04
    void*         mpHeaderB;   // +0x08
    void*         mpRoot;      // +0x0c
    unsigned char mColor;      // +0x10
    int           mSize;       // +0x14

    bool erase(uint* key);                       // 0x00b36360
    void insert(void* out, uint* key, int hint); // 0x00b37180
};

struct LayerTreeNuker {     // 0x009a9600  ?f@S9a9600@@QAEXPAX@Z
    void f(void* node);
};

struct LayerTreeOut {       // result of LayerTree::insert
    bool mCreated;
};

// @ 0x00b378d0
void __thiscall cEditorLayer::gv08(uint id, bool on)
{
    LayerTree* tree = (LayerTree*)((char*)this + 0xc8);

    LayerTreeOut result;
    if (on)
        tree->erase(&id);
    else {
        result.mCreated = false;
        tree->insert(&result, &id, *(int*)&result);
    }

    Link* head = (Link*)((char*)this + 0x24);
    LayerNode* node = NodeFromLink(head->mpNext);
    LayerNode* end  = NodeFromLink(head);

    if (id == (uint)-1) {
        if (on) {
            ((LayerTreeNuker*)tree)->f(tree->mpRoot);
            void* self = (char*)tree + 4;
            tree->mpHeaderA = self;
            tree->mpHeaderB = self;
            tree->mpRoot    = 0;
            tree->mColor    = 0;
            tree->mSize     = 0;
        }
        *(unsigned char*)((char*)this + 0xc1) = on;

        while (node != end) {
            node->Notify(on);
            node = NodeFromLink(node->mLink.mpNext);
        }
        return;
    }

    while (node != end) {
        LayerObject* obj = node->GetObject();
        if (obj->Match(id))
            node->Notify(on);
        node = NodeFromLink(node->mLink.mpNext);
    }
}

// @ 0x00b379f0
cEditorRes* cEditorRes::ctor()
{
    char* self = (char*)this;
    *(void**)self        = VT_CTOR_0;
    *(void**)(self + 4)  = VT_CTOR_4;
    ((cGonzagoSubsystem*)(self + 8))->ctor();
    *(void**)self        = VT_GME_0;
    *(void**)(self + 4)  = VT_GME_4;
    *(void**)(self + 8)  = VT_SUB_0;
    *(void**)(self + 0xc)= VT_SUB_4;

    float one = gOne;
    *(void**)(self + 0x24) = self + 0x24;
    *(void**)(self + 0x28) = self + 0x24;

    *(void**)(self + 0x3c) = self + 0x44;
    *(void**)(self + 0x30) = self + 0x44;
    *(void**)(self + 0x2c) = self + 0x44;
    *(void**)(self + 0x34) = self + 0x84;

    *(int*)(self + 0x84)  = -1;
    *(int*)(self + 0x88)  = 0;
    *(float*)(self + 0x9c) = one;
    *(float*)(self + 0xa0) = gTwo;
    *(int*)(self + 0x98)  = 0;
    *(int*)(self + 0xa4)  = 0;
    *(int*)(self + 0x94)  = 1;
    *(void**)(self + 0x90) = GLOBAL_90;
    *(int*)(self + 0xac)  = 0;
    *(int*)(self + 0xb0)  = 0;
    *(int*)(self + 0xb4)  = 0;
    *(char*)(self + 0xc0) = 0;
    *(int*)(self + 0xc4)  = 0;
    *(int*)(self + 0xd0)  = 0;
    *(int*)(self + 0xd4)  = 0;
    *(int*)(self + 0xd8)  = 0;
    *(int*)(self + 0xd4)  = 0;
    *(char*)(self + 0xd8) = 0;
    *(int*)(self + 0xdc)  = 0;

    *(void**)(self + 0xcc) = self + 0xcc;
    *(void**)(self + 0xd0) = self + 0xcc;

    *(int*)(self + 0xe4)  = 0;
    *(int*)(self + 0xe8)  = 0;
    *(int*)(self + 0xec)  = 0;
    *(int*)(self + 0xfc)  = 0;
    *(int*)(self + 0x100) = 0;
    *(int*)(self + 0x104) = 0;
    *(int*)(self + 0x108) = 0;
    *(char*)(self + 0x10c) = 0;
    *(char*)(self + 0x10d) = 0;
    *(char*)(self + 0x10e) = 0;
    *(char*)(self + 0x10f) = 0;

    *(void**)(self + 0x120) = self + 0x128;
    *(void**)(self + 0x114) = self + 0x128;
    *(void**)(self + 0x110) = self + 0x128;
    *(void**)(self + 0x118) = self + 0x1a8;
    return this;
}

// @ 0x00b37b70
void* __cdecl rbIncrement(void* node);               // 0x00921580

struct MapItem {
    virtual void v00();
    virtual void v04();
    virtual LayerObject* Create(LayerArg* arg);      // +0x08
};

void cEditorLayer::AddObject(void* argp)
{
    LayerArg* arg = (LayerArg*)argp;
    char* base = (char*)this;
    int ok = *(char*)(base + 0xc1);

    if (ok) {
        void* sentinel = base + 0xcc;
        void* node = *(void**)(base + 0xd0);
        while (node != sentinel) {
            if (arg->Match(*(uint*)((char*)node + 0x10))) {
                ok = 0;
                break;
            }
            node = rbIncrement(node);
        }
    }

    arg->Key();
    uint key = arg->Key();
    void* it = mapLowerBound((void*)0x0167ea3c, (void*)0x0167ea40, &key,
                             *(unsigned char*)0x0167ea50);
    if (it == (void*)0x0167ea40)
        return;
    if (key < *(uint*)it)
        return;

    MapItem* item = *(MapItem**)((char*)it + 4);
    LayerObject* obj = item->Create(arg);
    if (!obj)
        return;

    Link* link = (Link*)((char*)obj + 4);
    link->mpPrev = *(Link**)(base + 0x28);
    link->mpNext = (Link*)(base + 0x24);
    ((Link*)(base + 0x24))->mpPrev = link;
    link->mpPrev->mpNext = link;
    arg->mpResult = obj;
    obj->Notify(ok);
}

// @ 0x00b37c60
struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };
struct Mat33 { float m[9]; };

struct EffectsManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool CreateEffect(uint res, uint id, void** out);   // +0x2c
};

struct EffectRef {
    virtual void v00();
    virtual void Release();               // +0x04
    virtual void v08(int flag);           // +0x08
};

// node found in the layer's resource table: a refcounted observer with the
// two resource ids at +0x08/+0x0c
struct EffectTarget {
    virtual void v00(); virtual void v04();
    virtual void v08(int flag);           // +0x08
    virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void Notify(void* msg);       // +0x18
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c();
    virtual void gv40(int cmd, void* data, int n);   // +0x40
    virtual void gv44(int cmd, void* data, int n);   // +0x44
    virtual void v48();
    virtual void gv4c(int cmd, void* data);          // +0x4c
    int  mPad4;                           // +0x04
    uint mRes;                            // +0x08
    uint mId;                             // +0x0c
};

struct XformMsg {
    unsigned short mFlags;
    short          mCount;
    Vec3           mPos;
    float          mW;
    Mat33          mRot;
};

struct CheatObject2 {
    void ctor();                          // 0x0057a6d0
    virtual void v00();
    virtual void Release();               // +0x04
    wchar_t mText[8];                     // +0x0c
};

EffectsManager* __cdecl GetEffectsManager();       // 0x0067ddd0
void* __cdecl GetPlanetModel();                    // 0x00b3d350
Quat& __cdecl BuildSurfaceOrientation(void* model, Quat* out, const Vec3* v);      // 0x00b7f190
Quat& __cdecl BuildSurfaceOrientation2(void* model, Quat* out, const Vec3* a, const Vec3* b); // 0x00b7f250
Mat33& __cdecl Matrix3FromQuaternion(Mat33* out, const Quat* q);                   // 0x0059c190
void  __cdecl Matrix3Assign(Mat33* self, const void* src);                         // 0x0041cb40
void  __cdecl LayerHelper3B5B80(cEditorLayer* self, void* a, int b);               // 0x00b35b80
Vec3& __cdecl DirectionToSurfacePosition(void* model, Vec3* out, const Vec3* dir); // 0x00b815a0
void  __cdecl FormatString(wchar_t* dst, const wchar_t* fmt, int a, const wchar_t* b); // 0x0041e050
void  __cdecl BuildCheatMessage(double value, void* buf, int a, int b, int c);      // 0x008822e0
void  __cdecl XformMsgCtor(XformMsg* self);                                        // 0x00434040

void cEditorLayer::SpawnEffect(uint key, const void* ap, const void* bp, int idA, int idB, int arg6)
{
    const Vec3* a = (const Vec3*)ap;
    const Vec3* b = (const Vec3*)bp;
    char* base = (char*)this;
    (void)arg6;

    EaHashtable* ht = (EaHashtable*)(base + 0x8c);
    void* it = 0;
    ht->find(&it, &key);
    if (it == ht->end())
        return;

    EffectTarget* target = (EffectTarget*)it;

    EffectsManager* fx = GetEffectsManager();
    EffectRef* ref = 0;
    if (ref)
        ref->Release();

    if (!fx->CreateEffect(target->mRes, target->mId, (void**)&ref))
        return;

    Quat q;
    q.x = *(float*)0x0167e9f8;
    q.y = *(float*)0x0167e9fc;
    q.w = 1.0f;
    q.z = *(float*)0x0167ea00;

    Mat33 mat;
    Matrix3Assign(&mat, (void*)0x0167ea08);

    Vec3 v = *a;
    XformMsg msg;
    msg.mFlags |= 4;
    msg.mCount++;
    msg.mPos = v;
    msg.mW = 0.0f;

    if (b->x == *(float*)0x0167e9a4 &&
        b->y == *(float*)0x0167e9a8 &&
        b->z == *(float*)0x0167e9ac)
        BuildSurfaceOrientation(GetPlanetModel(), &q, a);
    else
        BuildSurfaceOrientation2(GetPlanetModel(), &q, a, b);

    Matrix3FromQuaternion(&mat, &q);
    msg.mRot = mat;
    msg.mFlags |= 2;
    msg.mCount += 2;

    target->Notify(&msg);

    if (idA != -1) {
        char tmp[16];
        LayerHelper3B5B80(this, &tmp, idA);
        target->gv44(5, &tmp, 3);
    }

    if (key == 0x1b55d9a) {
        Vec3 sum;
        sum.x = a->x + b->x;
        sum.y = a->y + b->y;
        sum.z = a->z + b->z;
        target->gv40(9, &sum, 1);
        target->gv44(10, &sum, 1);
    }

    target->v08(0);

    if (idB != -1) {
        wchar_t buf[64];
        memset(buf, 0, sizeof(buf));
        BuildCheatMessage((double)idA, buf, 0x28, 0, 0);

        CheatObject2* cheat = (CheatObject2*)EAAllocate(0x1c, "Simulator", 0, 0, 0, 0);
        if (cheat) {
            cheat->ctor();
            cheat->v00();
        }
        FormatString(cheat->mText, L"%lc%ls", 0x2b, buf);
        target->gv4c(8, cheat);
        if (cheat)
            cheat->Release();
    }

    if (key == 0x147e293) {
        Vec3 dir;
        DirectionToSurfacePosition(GetPlanetModel(), &dir, a);

        float len2 = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
        float root;
        __asm {
            fld len2
            fsqrt
            fstp root
        }
        float inv = 1.0f / root;
        Vec3 add;
        add.x = dir.x * inv + dir.x;
        add.y = dir.y * inv + dir.y;
        add.z = dir.z * inv + dir.z;

        float dx = a->x - add.x;
        float dy = a->y - add.y;
        float dz = a->z - add.z;
        if (dx * dx + dy * dy + dz * dz < 16.0f) {
            if (ref)
                ref->Release();
            ref = 0;

            EffectsManager* fx2 = GetEffectsManager();
            if (fx2->CreateEffect(0xf740edd5u, 0, (void**)&ref)) {
                XformMsg msg2;
                XformMsgCtor(&msg2);
                msg2.mFlags |= 4;
                msg2.mCount++;
                msg2.mPos = dir;

                Quat q2;
                BuildSurfaceOrientation(GetPlanetModel(), &q2, a);
                Matrix3FromQuaternion(&mat, &q2);
                msg2.mRot = mat;
                msg2.mFlags |= 2;
                msg2.mCount++;

                target->Notify(&msg2);
                if (ref)
                    ref->v08(0);
            }
        }
    }

    if (ref)
        ref->Release();
}

// @ 0x00b38140
void cEditorRes::SetAnalysis(const AnalysisVector* other, bool renumber)
{
    char* base = (char*)this;
    AnalysisVector* vec = (AnalysisVector*)(base + 0xac);
    vec->assign(*other);

    if (renumber) {
        int n = (int)(vec->mpEnd - vec->mpBegin);
        for (unsigned i = 0; (int)i < n; i++)
            vec->mpBegin[i].mIndex = (int)i;
    }
}
