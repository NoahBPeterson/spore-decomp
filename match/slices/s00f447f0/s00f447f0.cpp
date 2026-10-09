// Slice s00f447f0 -- scenario-mode object (Simulator cScenario* family): init, action insert, tag apply,
// reinit and save.  Module flags: /O2 /MD /Gy /TP /GS-
#include "types.h"

struct V3u { uint32_t x, y, z; };
struct V4u { uint32_t x, y, z, w; };
struct IRef {
    virtual void AddRef();
    virtual void Release();
};

struct ResourceKey {
    uint32_t instance, type, group;
};

// ---- ResourceMan -----------------------------------------------------------------------------
struct IRecord : IRef {
    virtual void v2();
    virtual IRef* QueryInterface(uint32_t type);   // 0x0c
};

struct AssetMetadata : IRef {
    char pad[0xd8 - 4];
    AssetMetadata();                                   // 0x550450
    void SetLocalMetadata(const ResourceKey* key, const wchar_t* name, const wchar_t* desc, const wchar_t* tags,
                          const ResourceKey* old, int zero);          // 0x551240
    void GetTagsString(void* outStr);                  // 0x550cf0
};

struct ScenarioResource;

struct IResMan {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void GetResource(const ResourceKey* key, IRecord** out, int, int, int, int);   // 0x0c
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual bool WriteRecord(void* a, int, void* area, int, int);                          // 0x20
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26();
    virtual bool Commit(void* a, int flag);                                                // 0x6c
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void SetPath(const ResourceKey* key, const wchar_t* path);                     // 0x80
};

struct IDGen {
    virtual void v0(); virtual void v1();
    virtual void MakeKey(ResourceKey* out, uint32_t type, uint32_t group);                 // 0x08
};

struct IMsgServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void PostMessage(uint32_t id, void* data, int arg);                            // 0x14
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual void AddListener(void* listener, uint32_t id);                                 // 0x24
};

struct ISink {
    uint32_t d0, d1;
    virtual void s0(const void* a);
    virtual void s1();
    virtual void s2(const void* a);
    virtual void s3();
    virtual void s4(const wchar_t* a);
};

// ---- helpers ---------------------------------------------------------------------------------
extern wchar_t gEmptyStr16[];   // 0x1667bac
struct EStr16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    EStr16() : mpBegin(gEmptyStr16), mpEnd(gEmptyStr16), mpCapacity(gEmptyStr16 + 1) {}
    ~EStr16() {
        if (((mpCapacity - mpBegin) & ~1) > 2 && mpBegin) {
            delete[] mpBegin;
        }
    }
};

struct EStrA {   // eastl::basic_string<wchar_t, allocator>: zeroed then RangeInitialize
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void RangeInitialize(const wchar_t* p);   // 0x579a90
    explicit EStrA(const wchar_t* p) {
        mpBegin = 0; mpEnd = 0; mpCapacity = 0;
        RangeInitialize(p);
    }
    ~EStrA() {
        if (((mpCapacity - mpBegin) & ~1) > 2 && mpBegin) {
            delete[] mpBegin;
        }
    }
};

struct ScenarioEconomy {
    int mnRefCount;   // +4
    char pad[0x30 - 8];
    ScenarioEconomy();   // 0xecff20
    virtual void Destroy(int);
};

struct Action {   // 0x534 bytes
    char d[0x534];
    Action();    // 0xf2d330
    ~Action();   // 0xdfce40
};

struct ActionVec {   // eastl::vector<Action>, at ScenarioResource+0x23c
    Action* mpBegin;
    Action* mpEnd;
    void Insert(Action* pos, const Action* v);   // 0xf44780
    void Init446f0();                            // 0xf446f0
};

struct Vec4e0 {
    char* mpBegin;
    void set_capacity(int n);           // 0xf2dbe0
    void Copy(char* dst, char* src);    // 0xf43880
};
struct Vec34 {
    char* mpBegin;
    void set_capacity(int n);           // 0xf2bb10
    void Copy(char* dst, char* src);    // 0xf42dc0
};

struct PerActionBlock {   // 0x27e8 bytes, vec at +0x78
    char pad[0x78];
    Vec4e0 vec;
    char pad2[0x27e8 - 0x78 - 4];
};

struct HashNode {   // 0x238 bytes
    uint32_t flags;
    char pad[0x2c - 4];
    Vec34 vec;
    char pad2[0x238 - 0x30];
};

__declspec(align(8)) struct ScenarioResource : IRef {
    uint32_t pad04;
    ResourceKey key;          // +0x08
    char pad14[0x78 - 0x14];
    uint32_t m78;
    char pad7c[0x130 - 0x7c];
    V3u pos;                  // +0x130
    char pad13c[0x150 - 0x13c];
    V3u pos2;                 // +0x150
    V4u rot;                  // +0x15c
    float scale;              // +0x16c
    char pad170[0x23c - 0x170];
    ActionVec actions;        // +0x23c
    char pad244[0x2bf4 - 0x244];
    PerActionBlock* blocksBegin;   // +0x2bf4
    PerActionBlock* blocksEnd;     // +0x2bf8
    char pad2bfc[0x2c10 - 0x2bfc];
    HashNode* hashBegin;      // +0x2c10
    HashNode* hashEnd;        // +0x2c14
    char pad2c18[0x2c24 - 0x2c18];
    uint32_t hashCount;       // +0x2c24
    char pad2c28[0x2c2c - 0x2c28];
    uint8_t m2c2c;
    char pad2c2d[3];
    float camAnchor[3];       // +0x2c30
    float camRot[4];          // +0x2c3c
    float camFloat;           // +0x2c4c
    char pad2c50[0x2ca8 - 0x2c50];
    uint32_t m2ca8;
    char pad2cac[4];

    ScenarioResource();                       // 0xf2e7d0
    ~ScenarioResource();                      // 0xdfef70
    void CopyFrom(const ScenarioResource& o); // 0xdffa30
    void Init2c470();   // 0xf2c470
    void Init26230();   // 0xf26230
    void Init2b340();   // 0xf2b340
    void Init27d80();   // 0xf27d80
    void GatherObjects(void* outVec, uint32_t type, int a);   // 0xf2b040
    int NumActions() { return (int)((char*)actions.mpEnd - (char*)actions.mpBegin) / 0x534; }
};

// ---- globals ---------------------------------------------------------------------------------
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct G534 {
    void Call(uint32_t a, uint32_t b);   // 0xddddf0
};
extern G534 g15b0534;   extern uint32_t g15b0530;
struct LogVec {
    void erase(void* b, void* e);   // 0xe25bd0
    void* mpBegin;
    void* mpEnd;
};
extern LogVec g16065d8;
extern uint32_t g16065ec, g16065f0;
extern uint8_t g16065f8;
extern IRef* g16065fc;
struct G15ad328 {
    void Init();   // 0xf03290
};
extern G15ad328 g15ad328;
struct G16c7c08 {
    void Init();   // 0xf02670
};
extern G16c7c08 g16c7c08;
extern V3u g16c87f8;
extern V4u g15b0398;
extern uint32_t g15b03a8;


V3u* F43010();                                // 0xf43010 (cdecl, returns vec3*)
float __cdecl F_eed280(V3u* v, int n);        // 0xeed280
IMsgServer* MessageServer();                    // 0x67dcc0
IResMan* GetManager();                          // 0x67dcd0
extern "C++" void* operator new(size_t, const char*, int, int, int, int);   // 0xf473a0
void operator delete(void* p);   // 0xf47380
void F_ef29c0();   void F_b3d3c0();
extern void* g_msgIds;   // 0x148d35c

extern const uint32_t g148d35c[3];   // 0x148d35c

void F_ef29c0();                       // 0xef29c0
void F_6b2350();                       // 0x6b2350
void F_6ad010(AssetMetadata* m);       // 0x6ad010
uint32_t F_10c7aa0();                  // 0x10c7aa0
void* GetSaveArea(uint32_t id);        // 0x6b1f90
IDGen* IDGenerator();                  // 0x67de60
void MakeFileNameValid(const wchar_t* src, wchar_t* dst, int mode);   // 0x931250
void Replace(wchar_t* b, wchar_t* e, const wchar_t& oldv, const wchar_t& newv);   // 0x63eda0
// BuildPaths is called through a const function pointer in .rdata (0x154c468 -> 0x8ddc80)
typedef void (__cdecl* BuildPathsFn)(ResourceKey* key, struct EStr16* out, IResMan* mgr, void* area, const wchar_t* name);
extern BuildPathsFn const BuildPaths;   // 0x154c468
void* F_414e10(AssetMetadata* m);      // 0x414e10
void* F_5508c0(AssetMetadata* m);      // 0x5508c0

struct SingA {
    void m781d0();   // 0xb781d0
    void m79aa0();   // 0xb79aa0
};
SingA* GetSingA();   // 0xb3d3c0
struct SingB {
    void m5a390();   // 0xb5a390
    void m515e0();   // 0xb515e0
};
SingB* GetSingB();   // 0xb3d310
struct Obj37be0 { void Init37be0(); };
struct G7aa4 { char pad[0x18]; Obj37be0* p; };
extern G7aa4* g16c7aa4;
extern const char k13ec468[];

struct FStr {   // eastl fixed string header: begin, end, capacity, +1 dword
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCap; uint32_t pad;
    void append(const wchar_t* s);   // 0x5c3d90
};

struct CamObj {
    float* GetAnchorDirection();   // 0xb10260
    float* GetRotation();          // 0x644a70
    float GetDistance();           // 0xc37540
};
struct Obj1 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual IRecord* GetHost();   // 0x38
};
struct AppX {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual Obj1* Get50();
};
AppX* SP_App();   // 0x67dd10

struct ImgData { void* handle; uint32_t flags; };
struct ImgRef {
    ImgData* p;
    void GetImageResource(void* r);   // 0x576650
};
struct ImgMan {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void* LoadImage(ResourceKey k, int zero);   // 0x1c
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void Register(ImgData* d);                  // 0x34
};
ImgMan* GetImgMan();   // 0x67dd60
struct ThumbMgr {
    bool CreateExportThumb(void* r, void* img, void* area, int a, int b);   // 0x5fa8d0
    void RemoveExportThumb(ResourceKey* k);   // 0x5faec0
};
ThumbMgr* GetThumbMgr();   // 0x5f7930 (thiscall target is the returned object)
struct ObjTemplateDB {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29();
    virtual void Invalidate(ResourceKey* k, int z);     // 0x78
};
ObjTemplateDB* GetObjectTemplateDB();   // 0x67cb40
struct LayoutCollection {
    void Hide();   // 0x801380
};
LayoutCollection* GetLayoutCollection();    // 0x67cab0

// ScenarioObj8: the scenario-mode controller (vtable at +0, ISink subobject at +4, ScenarioResource at +0x10)
struct ScenarioObj8 {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(uint32_t id);
    ISink sink;                 // +0x04
    ScenarioResource* mpManager;// +0x10
    uint8_t f14;
    char pad15[3];
    uint32_t m18;               // +0x18
    uint8_t m1c;                // +0x1c
    char pad1d[0x38 - 0x1d];
    ImgRef imgRef;              // +0x38
    char pad3c[0x4c - 0x3c];
    FStr nameStr;               // +0x4c
    FStr descStr;               // +0x5c
    FStr tagStr;                // +0x6c
    uint32_t m7c;
    uint32_t m80;
    uint8_t m84, m85;
    char pad86[0xd0 - 0x86];
    ScenarioEconomy* mpEconomy; // +0xd0
    IMsgServer* mpMsgServer;    // +0xd4
    ScenarioObj8* mpListener;   // +0xd8
    const uint32_t* mpIds;      // +0xdc
    uint32_t mnIds;             // +0xe0
    uint32_t mdummy;            // +0xe4

    bool f447f0(char flag);
    int  f44a40(int idx);
    bool f44bf0(void* msg);
    void f44dd0();
    char f44fe0();
    void F3c420(); void F3d210(); void F41300(); void F3cf10(int a);
    void F3d3e0(const wchar_t* n, const ResourceKey* k, const EStr16* s);   // 0xf3d3e0
    void F3d5d0(const wchar_t* n, const ResourceKey* k, const EStr16* s);   // 0xf3d5d0
};

// @ 0x00f447f0
bool ScenarioObj8::f447f0(char flag)
{
    g15b0534.Call(0x55c0377, g15b0530);

    ScenarioResource* res = new("Simulator/cScenarioResource", 0, 0, 0, 0) ScenarioResource();
    ScenarioResource* old = mpManager;
    if (res != old) {
        if (res) res->AddRef();
        mpManager = res;
        if (old) old->Release();
    }

    ScenarioEconomy* eco = new("Simulator/cScenarioEconomy", 0, 0, 0, 0) ScenarioEconomy();
    ScenarioEconomy* oldEco = mpEconomy;
    if (eco != oldEco) {
        if (eco) eco->mnRefCount++;
        mpEconomy = eco;
        if (oldEco) {
            int cnt = oldEco->mnRefCount;
            --cnt;
            oldEco->mnRefCount = cnt;
            if (cnt == 0) {
                oldEco->mnRefCount = 1;
                oldEco->Destroy(1);
            }
        }
    }
    f14 = 0;
    g16065ec = 0;
    g16065d8.erase(g16065d8.mpBegin, g16065d8.mpEnd);
    g16065f0++;
    g16065f8 = 1;
    if (g16065fc) {
        IRef* p = g16065fc;
        g16065fc = 0;
        p->Release();
    }
    g15ad328.Init();
    g16c7c08.Init();
    F3c420();
    if (flag) {
        ScenarioResource* r = mpManager;
        V3u* v = F43010();
        r->pos = *v;
        r = mpManager;
        r->pos2 = g16c87f8;
        r = mpManager;
        r->rot = g15b0398;
        r = mpManager;
        r->scale = F_eed280(&r->pos, 0);
        mpManager->actions.Init446f0();
        m80 = g16065f0;
        m84 = 0;
        m85 = 0;
    }
    IMsgServer* ms = MessageServer();
    mpMsgServer = ms;
    mpListener = this;
    mpIds = g148d35c;
    mnIds = 3;
    mdummy = 0;
    if (ms) {
        for (uint32_t i = 0; i < 0xc; i += 4) {
            ms->AddListener(this, *(const uint32_t*)((const char*)g148d35c + i));
        }
    }
    return true;
}

// @ 0x00f44a40
// Inserts an action at index idx (1..7), growing every per-action vector in the scenario by one slot.
int ScenarioObj8::f44a40(int idx)
{
    ScenarioResource* r = mpManager;
    int n = r->NumActions();
    if ((uint32_t)(n - 1) > 6 || idx < 1 || idx > r->NumActions()) {
        return -1;
    }
    Action* base = r->actions.mpBegin;
    Action tmp;
    r->actions.Insert((Action*)((char*)base + idx * 0x534), &tmp);

    PerActionBlock* b = mpManager->blocksBegin;
    PerActionBlock* e = mpManager->blocksEnd;
    if (b != e) {
        do {
            b->vec.set_capacity(n + 1);
            char* dst = b->vec.mpBegin + idx * 0x4e0;
            b->vec.Copy(dst, dst - 0x4e0);
            b++;
        } while (b != e);
    }
    ScenarioResource* r2 = mpManager;
    HashNode* it;
    if (r2->hashCount < 0x3fffffff) {
        it = (HashNode*)((char*)r2->hashBegin + r2->hashCount * 0x238);
    } else {
        it = r2->hashEnd;
    }
    HashNode* end = r2->hashEnd;
    if (end != it) {
        do {
            it->vec.set_capacity(n + 1);
            char* dst = it->vec.mpBegin + idx * 0x34;
            it->vec.Copy(dst, dst - 0x34);
            uint32_t f;
            do {
                f = it->flags;
                it = (HashNode*)((char*)it + 0x238);
                if ((f >> 0x1e) & 1) break;
            } while ((int)it->flags < 0);
        } while (end != it);
    }
    return idx;
}

// @ 0x00f44bf0
// Applies a scenario tag/asset message: resolves the record, pushes name/tags to the sink and loads the scenario.
struct TagMsg { uint32_t name; uint32_t pad; uint32_t group; };
bool ScenarioObj8::f44bf0(void* vmsg)
{
    TagMsg* msg = (TagMsg*)vmsg;
    if (msg->group == g15b03a8 && msg->name != 0) {
        bool ok = false;
        ResourceKey key;
        key.instance = msg->name; key.type = 0x30bdee3; key.group = msg->group;
        IRecord* rec = 0;
        IResMan* mgr = GetManager();
        if (rec) { IRecord* t = rec; rec = 0; t->Release(); }
        mgr->GetResource(&key, &rec, 0, 0, 0, 0);

        AssetMetadata* meta = 0;
        if (rec) {
            meta = (AssetMetadata*)rec->QueryInterface(0x30bdee3);
            if (meta) {
                meta->AddRef();
                ISink* s = &sink;
                s->s0(F_414e10(meta));
                s->s2(F_5508c0(meta));
                EStr16 tags;
                meta->GetTagsString(&tags);
                s->s4(tags.mpBegin);
            }
        }
        ResourceKey key2;
        key2.instance = msg->name; key2.type = 0x366a930d; key2.group = msg->group;
        IRecord* rec2 = 0;
        mgr = GetManager();
        if (rec2) { IRecord* t = rec2; rec2 = 0; t->Release(); }
        mgr->GetResource(&key2, &rec2, 0, 0, 0, 0);
        if (rec2) {
            IRef* p = rec2->QueryInterface(0xe742574a);
            if (p) {
                mpManager->CopyFrom(*(ScenarioResource*)p);
                v3(mpManager->m78);
                ok = true;
            }
        }
        if (rec2) rec2->Release();
        if (meta) meta->Release();
        if (rec) rec->Release();
        return ok;
    }
    return false;
}

// @ 0x00f44dd0
// Reinitializes the scenario state to defaults and re-announces it.
void ScenarioObj8::f44dd0()
{
    ScenarioResource* m = mpManager;
    m->CopyFrom(ScenarioResource());

    ScenarioResource* r = mpManager;
    V3u* v = F43010();
    r->pos = *v;
    r = mpManager;
    r->pos2 = g16c87f8;
    r = mpManager;
    r->rot = g15b0398;
    r = mpManager;
    r->scale = F_eed280(&r->pos, 0);
    mpManager->actions.Init446f0();
    F41300();
    F3c420();
    F3cf10(0);
    sink.s0(k13ec468);
    sink.s2(k13ec468);
    sink.s4((const wchar_t*)k13ec468);
    v3(0x20790816);
    g16c7aa4->p->Init37be0();
    MessageServer()->PostMessage(0x72bdb11, 0, 0);
    MessageServer()->PostMessage(0x86a4609d, (void*)1, 0);
    MessageServer()->PostMessage(0x7e1e46d, 0, 0);
    GetSingA()->m781d0();
    GetSingB()->m5a390();
    GetSingB()->m515e0();
    GetSingA()->m79aa0();
    g16065ec = 0;
    g16065d8.erase(g16065d8.mpBegin, g16065d8.mpEnd);
    g16065f0++;
    g16065f8 = 1;
    if (g16065fc) {
        IRef* p = g16065fc;
        g16065fc = 0;
        p->Release();
    }
    F_ef29c0();
    m84 = 0;
    m85 = 0;
    m80 = g16065f0;
}

struct PtrVec {
    void** mpBegin; void** mpEnd; void** mpCap;
    ~PtrVec() {
        if (mpBegin && ((int*)mpBegin)[-1]) {
            delete[] mpBegin;
        }
    }
};

// @ 0x00f44fe0
// Saves the current scenario: builds the file name, writes the .scenario / thumbnail records and
// announces the result.  Returns true on success.
char ScenarioObj8::f44fe0()
{
    bool ok = false;
    IResMan* mgr = GetManager();
    void* area = GetSaveArea(0x86ca01c9);
    if (mgr && area) {
        ResourceKey key = {0, 0, 0};
        ResourceKey oldkey = {0, 0, 0};
        IDGenerator()->MakeKey(&key, 0x366a930d, g15b03a8);
        oldkey = mpManager->key;
        mpManager->key = key;

        if (nameStr.mpBegin == nameStr.mpEnd) {
            nameStr.append(L"Temporary name");
        }
        wchar_t buf[248];
        MakeFileNameValid(nameStr.mpBegin, buf, 4);
        EStrA name2(buf);
        const wchar_t kBang = L'!', kUnder = L'_';
        Replace(name2.mpBegin, name2.mpEnd, kBang, kUnder);
        EStr16 str;
        BuildPaths(&key, &str, mgr, area, name2.mpBegin);
        mgr->SetPath(&key, str.mpBegin);
        ResourceKey k3 = {key.instance, 0x30bdee3, key.group};
        BuildPaths(&k3, &str, mgr, area, name2.mpBegin);
        mgr->SetPath(&k3, str.mpBegin);
        ResourceKey k4 = {key.instance, 0x2f7d0004, key.group};
        BuildPaths(&k4, &str, mgr, area, name2.mpBegin);
        mgr->SetPath(&k4, str.mpBegin);
        F3d210();
        F3d3e0(name2.mpBegin, &key, &str);
        F3d5d0(name2.mpBegin, &key, &str);

        CamObj* cam = 0;
        IRecord* host = SP_App()->Get50()->GetHost();
        if (host) {
            cam = (CamObj*)host->QueryInterface(0x11966ed);
            if (cam) {
                ScenarioResource* r = mpManager;
                float* a = cam->GetAnchorDirection();
                r->camAnchor[0] = a[0]; r->camAnchor[1] = a[1]; r->camAnchor[2] = a[2];
                r = mpManager;
                float* q = cam->GetRotation();
                r->camRot[0] = q[0]; r->camRot[1] = q[1]; r->camRot[2] = q[2]; r->camRot[3] = q[3];
                r = mpManager;
                r->camFloat = cam->GetDistance();
            }
        }
        PtrVec objs = {0, 0, 0};
        mpManager->GatherObjects(&objs, 0x30f0f, 0);
        for (uint32_t i = 0; i < (uint32_t)(objs.mpEnd - objs.mpBegin); i++) {
            ((uint8_t*)objs.mpBegin[i])[0x1c] = 0;
        }

        ScenarioResource* r = new("Simulator/cScenarioResource", 0, 0, 0, 0) ScenarioResource();
        if (r) r->AddRef();
        r->CopyFrom(*mpManager);
        r->m2ca8 = F_10c7aa0();
        r->key = key;
        r->Init2c470();
        r->Init26230();
        r->Init2b340();
        r->Init27d80();
        r->m78 = m7c;
        r->m2c2c = 0;

        AssetMetadata* meta = new("Simulator", 0, 0, 0, 0) AssetMetadata();
        if (meta) meta->AddRef();
        meta->SetLocalMetadata(&key, nameStr.mpBegin, descStr.mpBegin, tagStr.mpBegin, &oldkey, 0);
        GetManager()->WriteRecord(meta, 0, area, 0, 0);
        F_6ad010(meta);
        if (GetManager()->WriteRecord(r, 0, area, 0, 0)) {
            ok = true;
            if (!GetManager()->Commit(r, 1)) ok = false;
        } else {
            ok = false;
        }
        ImgData* img = imgRef.p;
        if (!(img->flags & 1)) {
            GetImgMan()->Register(img);
            img = imgRef.p;   // reloaded from the stack copy
        }
        if (GetThumbMgr()->CreateExportThumb(r, img->handle, area, 0, 1)) {
            MessageServer()->PostMessage(0xca665fa7, &key, 0);
        } else {
            ok = false;
        }
        ImgMan* im = GetImgMan();
        ResourceKey rk = r->key;
        void* ih = im->LoadImage(rk, 0);
        imgRef.GetImageResource(ih);
        if (!m1c) {
            ResourceKey rm = oldkey;
            GetThumbMgr()->RemoveExportThumb(&rm);
            GetObjectTemplateDB()->Invalidate(&rm, 0);
        }
        if (meta) meta->Release();
        r->Release();
    }
    F_6b2350();
    m18 = 0;
    GetLayoutCollection()->Hide();
    if (ok) {
        m80 = g16065f0;
        m84 = 0;
        m85 = 0;
        ResourceKey k = mpManager->key;
        MessageServer()->PostMessage(0xfd7a08d0, &k, 0);
    }
    return ok;
}
// --- equivalence checker address annotations
    void* operator new(unsigned int, char*, int, int, int, int); // 0x00f473a0
    void GetSingA(...); // 0x00b3d3c0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct Vec4e0 {
    void Copy(char*, char*); // 0x00f43880
};
struct Vec34 {
    void Copy(char*, char*); // 0x00f42dc0
    void set_capacity(int); // 0x00f2bb10
};
struct CamObj {
    void GetDistance(); // 0x00c37540
    void GetAnchorDirection(); // 0x00b10260
    void GetRotation(); // 0x00644a70
};
struct G15ad328 {
    void Init(); // 0x00f03290
};
struct LogVec {
    void erase(void*, void*); // 0x00e25bd0
};
struct ScenarioResource {
    void CopyFrom(int&); // 0x00dffa30
    ScenarioResource(); // 0x00f2e7d0
    ~ScenarioResource(); // 0x00dfef70
    void GatherObjects(void*, unsigned int, int); // 0x00f2b040
};
struct G534 {
    void Call(unsigned int, unsigned int); // 0x00ddddf0
};
struct SingA {
    void m781d0(); // 0x00b781d0
};
}
