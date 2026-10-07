// slice s00589ce0 -- SP::cAppModeEditorBase model loading helpers, Undo and Redo.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
// Retail layout: offsets below are from the disassembly (the 2008 PDB layout is shifted).
#include "types.h"
#include <intrin.h>

typedef unsigned int uint;

void* __cdecl operator_new(unsigned, const char*, int, int, int, int);   // 0x00F473A0
void __cdecl operator_delete_array(void* p);                              // 0x00F47380

// ---------------------------------------------------------------- stub helpers
struct Key16 { uint a, b, c, d; };
struct Key12 { uint inst, type, group; };

// refcount sub-object {vptr, count} lives at obj+4 (count at obj+8)
struct RcSub { void** vt; int cnt; };
inline void RcRelease(void* obj) {
    RcSub* sub = (RcSub*)((char*)obj + 4);
    int c = sub->cnt - 1;
    sub->cnt = c;
    if (c == 0) {
        _ReadWriteBarrier();
        sub->cnt = 1;
        _ReadWriteBarrier();
        ((void(__thiscall*)(void*, int))sub->vt[0])(sub, 1);
    }
}

// eastl::basic_string<wchar_t> as used by the editor name provider copies
struct WStr {
    wchar_t* mb;
    wchar_t* me;
    wchar_t* mc;
    int mAlloc;
    void RangeInit(const wchar_t* p);   // 0x00579A90 basic_string::RangeInitialize
    void Erase(int first, int last);    // 0x004228E0
    WStr(const wchar_t* p) { mb = 0; me = 0; mc = 0; RangeInit(p); }
    ~WStr() {
        if ((((char*)mc - (char*)mb) & ~1) > 2) {
            if (mb) operator_delete_array(mb);
        }
    }
};

struct IRefObj {   // vtable: AddRef(+4) Release(+8) style objects (RefCountVTemplate)
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};

struct FileStream {
    virtual void v0();
    virtual void AddRef();     // +4
    virtual void Release();    // +8
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void Close();      // +0x18
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void SetPath(const wchar_t* path);   // +0x3c
    virtual void v16(); virtual void v17(); virtual void v18();
    virtual bool Open(int access, int mode, int share, int flags);   // +0x4c
    FileStream* Init(int path);   // 0x00931DA0 (PFRecordWrite/FileStream ctor)
};

struct EditorResHeader {   // result of cast(0x3c609f8): holds the model type at +0x18
    char pad[0x18];
    int mModelType;
    void ReadKey(Key16* out, Key16 inKey, int zero);                        // 0x004BAC30
};

struct RawResource {       // 0xAC, ctor 0x004B9C70; vtable: AddRef(+0) Release(+4) x(+8) Cast(+0xC)
    virtual void AddRef();
    virtual void Release();
    virtual void v2();
    virtual EditorResHeader* Cast(uint typeId);
    RawResource* Init();                                                    // 0x004B9C70
};

// 0xE0, ctor 0x004AB690. vtable at +0, refcount sub-object (vptr +4, count +8), key at +0xC.
struct EditorResource {
    virtual void v0();
    virtual int  GetThing();   // +4 (slot 1)
    char pad4[0x4];
    int  mRefCount;                   // +8
    Key12 mKey;                       // +0xC
    EditorResource* Init();                         // 0x004AB690
    bool CopyFrom(void* src);                       // 0x004AE3B0
};

// Entry of the undo list: refcounted, AddRef(+0) Release(+4).
struct UndoEntry {
    virtual void AddRef();
    virtual void Release();
};

// Local state object: RefCountVTemplate (AddRef +4, Release +8).
struct LocalState : IRefObj {};

struct AnimEventInfo {   // cSPEditorAnimatedEventInfo, 0x30
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
    char pad[0x8];
    uint f0c;     // +0xC
    uint f10;     // +0x10
    void* f14;    // +0x14
    uint f18;     // +0x18
    uint8_t f1c;  // +0x1C
    float f20;    // +0x20
    uint8_t f24;  // +0x24
    uint f28;     // +0x28
    AnimEventInfo* Init();    // 0x0059D960
    void MessagePost(uint msg, int a, void* model, int b, int c, float d, int e, int f, float g);   // 0x0059D840
};

struct EditorUI {
    void UpdateUIBasedOnModelSaveability();   // 0x005DD7A0
    void EnableUndoButton(bool b);            // 0x005DCEB0
    void EnableRedoButton(bool b);            // 0x005DCE40
};

struct ModelObj {   // cSPEditorModel
    virtual void v0();
    virtual uint GetModelThing();   // +4
    char pad[0xA];
    uint mKeyInstance;   // +0xC (declared via offsets below)
};

// Name provider sub-object at this+0xC (cISPEditorNameProvider)
struct NameProvider {
    virtual void SetA(const wchar_t* s);       // +0
    virtual const wchar_t* GetA();             // +4
    virtual void SetB(const wchar_t* s);       // +8
    virtual const wchar_t* GetB();             // +0xC
    virtual void SetC(const wchar_t* s);       // +0x10
    virtual const wchar_t* GetC();             // +0x14
};

struct IDGen {
    virtual void v0();
    virtual void v1();
    virtual void Generate(uint* out, uint hi, uint lo);   // +8
};

struct TokenTranslator { void SetOldModelName(const wchar_t* n); };   // 0x005D6090

struct Out16 { uint w[4]; };
struct ModelHook { void FUN_004ae0f0(); };   // 0x004AE0F0

// ---------------------------------------------------------------- globals / externs
extern wchar_t gDelimiters[];          // 0x013F5CA8
extern Key16 gNullKey;                 // 0x015DAC10
extern TokenTranslator* gTokenTranslator;   // 0x015EEBEC
struct PropList {
    bool GetDescription(uint id);   // 0x006A25A0
};
extern PropList* sAppProperties;   // 0x015FD918

const wchar_t* __cdecl GetTypeExtension(uint typeId);                                      // 0x004BB490
int  __cdecl WStrNCompare(const wchar_t* a, const wchar_t* b, int n);                      // 0x00572930
const wchar_t* __cdecl FindFirstOfRev(const wchar_t* pEnd, const wchar_t* pBegin,
                                      const wchar_t* dBegin, const wchar_t* dEnd);         // 0x005728F0
bool __cdecl ReadResourceFromStream(FileStream* fs, RawResource* res, int flags);          // 0x004BC6D0
bool __cdecl KeyEquals(Key16 a, Key16 b);                                                  // 0x004F3D60
int  __cdecl RemapTypeId(int typeId);                                                      // 0x00432F10
uint64_t __cdecl MapModeToId(uint v);                                                      // 0x00572110
IDGen* __cdecl GetIDGenerator();                                                           // 0x0067DE60
void* __cdecl RBTreeIncrement(void* node);                                                 // 0x00921580
bool __cdecl FUN_004edf40(int a, int b);
float __cdecl CalculateModelSize(void* model);                                             // 0x0048CA10
int   __cdecl CountModelParts(void* model);                                                // 0x0048CC20
void  __cdecl PlayEditorSound(uint a, uint b, float v, int z);                             // 0x00435F40

struct EditorSkin;
struct SkinManager { SkinManager* GetSkin(int a); };       // 0x004C49E0
struct AnimCreatureMgr { bool HandleAnimatedEvent(AnimEventInfo* e); };   // 0x0059D300
struct UIHints { void SetEnabled(); };               // 0x0067C420
struct AuthMgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                 virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                 virtual void v8(); virtual bool IsX(); };   // +0x24
AuthMgr* __cdecl GetAuthManager();                   // 0x00607A60
UIHints* __stdcall GetUIHints(int a, int b);         // 0x0067CAC0
int  __cdecl FUN_00552300(void* key);
bool __cdecl GetCreatorType(void* key);              // 0x00641900

struct PaintTheme {
    void ReadFromAsset(void* model);   // 0x004B2800
};
struct CamController { void SetCenterCameraOffset(); };   // 0x005A2370
struct IFace3 { virtual void v0(); virtual void v1(); virtual void v2(); virtual CamController* Cast(uint id); };
struct IFace2 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
                virtual void v12(); virtual void v13(); virtual IFace3* GetCtl(); };   // +0x38
struct IFace1 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
                virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
                virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
                virtual IFace2* GetCam(); };   // +0x50

struct EditorUIEx : EditorUI {
    bool FUN_005dc450();                       // 0x005DC450
    void FUN_005dd090(int a);                  // 0x005DD090
    void EnableBasicEditorButtons(int a, int b);   // 0x005DE690
    void FUN_005dd1d0();                       // 0x005DD1D0
    void Hide();                               // 0x005DD050
};

// Container helpers
struct UndoListVec {
    UndoEntry** mpBegin;
    void Resize(int n);   // 0x005E77E0
};
struct LocalStateVec {
    void Resize(int n);   // 0x00584160
};

struct ModelMem { char pad0[0xC]; Key12 key; char pad1[0x40]; uint f58; };

inline uint* FindU(uint* f, uint* l, const uint& v) { for (; f != l && *f != v; ++f) {} return f; }

namespace SP {

class cAppModeEditorBase {
public:
    // The real class begins with the cIAppMode vtable; the name provider sub-object is at +0xC.
    virtual void v0();
    char pad[0x1000];

    void FUN_00589ce0(const wchar_t* path);              // 0x00589ce0
    void LoadModelInternal(void* model);                  // 0x0058a1e0
    void LoadModel(int mode, int a, int b);               // 0x0058a350
    void Undo(char postMsg, char isRedoFlag);             // 0x0058a5a0
    void Redo();                                          // 0x0058a950

    // callees (other slices)
    void PrepareAppForNewModel(void* res);                // 0x00586B00
    void SetCurrentConfig(int cfg, int z0, int z1, int z2);   // 0x00579720
    void InitializeUndoList();                            // 0x00586690
    void ResetEconomy();                                  // 0x005754C0
    void ShowError(Key16 a, Key16 b);                     // 0x005721B0
    Out16* GetMask(Out16* out);                           // 0x0057A960
    void SetLocalState(LocalState* ls);                   // 0x0057C2F0
    Out16* SomeSetup(Out16* out, void* entry, uint v, int one);   // 0x0057AC00
    int  FUN_00576140();                                  // 0x00576140
    void FUN_00572220(void* m);                           // 0x00572220
    void FUN_0057bfb0();                                  // 0x0057BFB0
    void FUN_005802f0(int a, int b);                      // 0x005802F0
    void FUN_0057e8a0();                                  // 0x0057E8A0
    void FUN_0057c1e0();                                  // 0x0057C1E0
    void FUN_00572430(void* key);                         // 0x00572430
    void SetMode(int a, int b);                           // 0x00587270
    void FUN_00573f20(int v);                             // 0x00573F20
    void FUN_00582fe0(int a, int b);                      // 0x00582FE0
    void FUN_0057e340(int a);                             // 0x0057E340
    void FUN_0057c0e0();                                  // 0x0057C0E0
};

}  // namespace SP

using namespace SP;

#define M(T, off) (*(T*)((char*)this + (off)))

// ---------------------------------------------------------------------------
// @ 0x00589ce0
// Load a model from a file path: extension -> editor config via mResourceToConfigMap, then read the
// resource file and prepare the editor for it (reports an error through ShowError on failure).
void cAppModeEditorBase::FUN_00589ce0(const wchar_t* path) {
    if (M(uint8_t, 0x2b0) == 0) return;

    WStr s(path);
    // find the last '.' and keep only the extension: s.erase(0, pos + 1)
    const wchar_t* dEnd = gDelimiters;
    while (*dEnd) dEnd++;
    int n = ((char*)s.me - (char*)s.mb) >> 1;
    int pos = -1;
    if (n != 0) {
        int last = n - 1;
        const wchar_t* r = FindFirstOfRev(s.mb + last + 1, s.mb, gDelimiters, dEnd);
        if (r != s.mb) pos = (((char*)r - (char*)s.mb) - 2) >> 1;
    }
    s.Erase(0, pos + 1);

    if ((((char*)s.me - (char*)s.mb) & ~1) == 6) {
        // iterate the (type id -> config) map; node layout: +0x10 key
        char* anchor = (char*)this + 0x1b4;
        char* node = M(char*, 0x1b8);
        while (node != anchor) {
            uint typeId = *(uint*)(node + 0x10);
            if (typeId == 0) typeId = M(uint, 0x2a8);
            const wchar_t* ext = GetTypeExtension(typeId);
            const wchar_t* e = ext;
            while (*e) e++;
            int len = (e - ext);
            int cmpN = len < 3 ? len : 3;
            if (WStrNCompare(s.mb, ext, cmpN) == 0 && len == 3) {
                FileStream* fs = (FileStream*)operator_new(0x22c, "Editor", 0, 0, 0, 0);
                if (fs) fs = fs->Init(0);
                if (fs) fs->AddRef();
                fs->SetPath(path);
                if (fs->Open(1, 6, 1, 0)) {
                    RawResource* res = (RawResource*)operator_new(0xac, "Editor", 0, 0, 0, 0);
                    if (res) res = res->Init();
                    if (res) res->AddRef();
                    EditorResource* out = (EditorResource*)operator_new(0xe0, "Editor", 0, 0, 0, 0);
                    if (out) out = out->Init();
                    if (out) out->mRefCount++;
                    if (!ReadResourceFromStream(fs, res, -1) || !out->CopyFrom(res)) {
                        Key16 e1 = { 0x4000000, 0, 0, 0 };
                        Key16 e2 = { 0x4000000, 0, 0, 0 };
                        ShowError(e1, e2);
                    } else {
                        EditorResHeader* hdr = res ? res->Cast(0x3c609f8) : 0;
                        Key16 got;
                        hdr->ReadKey(&got, gNullKey, 0);
                        if (KeyEquals(got, gNullKey)) {
                            int cfg = RemapTypeId(hdr->mModelType);
                            if (cfg != ((int (__thiscall*)(void*))(*(void***)this)[0x44 / 4])(this))
                                SetCurrentConfig(cfg, 0, 0, 0);
                            uint genOut[3] = { 0, 0, 0 };
                            IDGen* gen = GetIDGenerator();
                            uint64_t id = MapModeToId(M(uint, 0x2a8));
                            gen->Generate(genOut, (uint)(id >> 32), (uint)id);
                            out->mKey.inst = genOut[0];
                            out->mKey.type = genOut[1];
                            out->mKey.group = genOut[2];
                            PrepareAppForNewModel(out);
                            M(uint8_t, 0x4b0) = 1;
                            M(uint8_t, 0x4b1) = 0;
                            ((EditorUIEx*)M(void*, 0x78))->FUN_005dd1d0();
                            InitializeUndoList();
                            NameProvider* np = (NameProvider*)((char*)this + 0xc);
                            gTokenTranslator->SetOldModelName(np->GetA());
                            ResetEconomy();
                            fs->Close();
                        } else {
                            Out16 mask;
                            Out16* m = GetMask(&mask);
                            Key16 mk = { m->w[0], m->w[1], m->w[2], m->w[3] };
                            ShowError(mk, got);
                            fs->Close();
                        }
                    }
                    if (out) {
                        RcRelease(out);
                    }
                    if (res) ((RawResource*)res)->Release();
                }
                fs->Release();
                break;
            }
            node = (char*)RBTreeIncrement(node);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x0058a1e0
// Load an already-built editor resource: prepare the app, play the sound hooks, apply paint theme.
void cAppModeEditorBase::LoadModelInternal(void* model) {
    uint8_t saveable = 0;
    if (model) {
        FUN_00572220(model);
        PrepareAppForNewModel(model);
        ((EditorUIEx*)M(void*, 0x78))->FUN_005dd1d0();
        uint* begin = M(uint*, 0x334);
        uint* end = M(uint*, 0x338);
        ModelMem* m = M(ModelMem*, 0x98);
        uint* p = FindU(begin, end, m->f58);
        if (p == end && (((char*)end - (char*)begin) & ~3) == 4) {
            m->f58 = *begin;
            M(uint8_t, 0x4b0) = 0;
            saveable = 1;
        }
        if (M(uint8_t, 0x20e)) {
            float sz = CalculateModelSize(M(void*, 0x98));
            PlayEditorSound(0x1d6253c0, 0xdef22b96, sz, 0);
            if (M(uint8_t, 0x20e)) {
                int cnt = CountModelParts(M(void*, 0x98));
                PlayEditorSound(0x1d6253c0, 0x5ee38119, (float)cnt, 0);
            }
        }
        // model-save-state refresh on the editor model
        ((ModelHook*)M(void*, 0x98))->FUN_004ae0f0();
        ResetEconomy();
        char* ld = M(char*, 0x1cc);
        if (ld && ld[0x64]) FUN_0057bfb0();
        InitializeUndoList();
        if (M(void*, 0x2a0)) ((PaintTheme*)M(void*, 0x2a0))->ReadFromAsset(M(void*, 0x98));
    }
    if (sAppProperties->GetDescription(0x677d3ea)) {
        ModelMem* m = M(ModelMem*, 0x98);
        if (m->f58 == 0xdfad9f51 && M(uint, 0x2a8) == 0x2b978c46) {
            m->f58 = 0x9ea3031a;
            saveable = 1;
        }
    }
    M(uint8_t, 0x4b3) = saveable;
    ((EditorUIEx*)M(void*, 0x78))->UpdateUIBasedOnModelSaveability();
}

// ---------------------------------------------------------------------------
// @ 0x0058a350
// Per-mode editor model load tail: dispatch on mode (0/1/2), refresh UI, camera and animated creature.
void cAppModeEditorBase::LoadModel(int mode, int a, int b) {
    M(uint, 0x1a8) = 1;
    switch (mode) {
    case 0:
        M(uint, 0x1a4) = 1;
        FUN_005802f0(b, a);
        break;
    case 1:
        if (M(uint8_t, 0x4b5)) {
            AuthMgr* auth = GetAuthManager();
            if (!auth->IsX()) {
                void* key = (char*)M(void*, 0x98) + 0xc;
                if (FUN_00552300(key) == 1) {
                    if (!GetCreatorType(key)) FUN_00572430(key);
                }
            }
        }
        M(uint, 0x1a4) = 0;
        FUN_0057e8a0();
        break;
    case 2:
        M(uint, 0x1a4) = 0;
        FUN_0057c1e0();
        break;
    }

    if (((EditorUIEx*)M(void*, 0x78))->FUN_005dc450()) {
        ((EditorUIEx*)M(void*, 0x78))->FUN_005dd090(0);
        ((EditorUIEx*)M(void*, 0x78))->EnableBasicEditorButtons(0, 1);
    }
    GetUIHints(0, 1)->SetEnabled();
    if (M(int, 0x31c) == 2) SetMode(0, 1);
    FUN_00573f20(M(int, 0x19c));

    if (M(uint8_t, 0x191)) {
        IFace1* f1 = M(IFace1*, 0x20);
        IFace3* f3 = f1->GetCam()->GetCtl();
        if (f3) {
            CamController* cc = f3->Cast(0x29da727);
            if (cc) cc->SetCenterCameraOffset();
        }
    }
    if (M(uint8_t, 0x190)) ((EditorUIEx*)M(void*, 0x78))->Hide();
    M(uint, 0x198) = 0;

    if (M(uint, 0x194) && M(void*, 0x360) && M(void*, 0x150)) {
        SkinManager* skin = ((SkinManager*)M(void*, 0x150))->GetSkin(1);
        if (skin && mode != 2) {
            if (M(uint, 0x364) == 0) {
                FUN_00582fe0(0, 0);
                if (M(uint, 0x364) == 0) { FUN_0057c0e0(); return; }
            }
            FUN_0057e340(1);
            IRefObj* old = M(IRefObj*, 0x380);
            if (old) {
                M(IRefObj*, 0x380) = 0;
                old->Release();
            }
            void* rawEv = operator_new(0x30, "Editor", 0, 0, 0, 0);
            AnimEventInfo* ev = rawEv ? ((AnimEventInfo*)rawEv)->Init() : 0;
            if (ev) ev->AddRef();
            ev->f0c = M(uint, 0x364);
            ev->f28 = M(uint, 0x194);
            ev->f18 = 0x248dca26;
            ev->f10 = 0;
            ev->f14 = M(void*, 0x98);
            ev->f1c = 0;
            ev->f20 = 0.0f;
            ev->f24 = 0;
            if (((AnimCreatureMgr*)M(void*, 0x360))->HandleAnimatedEvent(ev)) M(uint, 0x198) = 1;
            ev->Release();
        }
    }
    FUN_0057c0e0();
}

// ---------------------------------------------------------------------------
// Shared body of Undo/Redo: rebuild the editor from undo-list entry [idx] and restore the name provider.
// (Written out in each function, as in the original.)

// @ 0x0058a5a0
void cAppModeEditorBase::Undo(char postMsg, char isRedoFlag) {
    if (M(int, 0x188) > 1) {
        ((char*)M(void*, 0x4d8))[0xb] = 1;
        int idx = FUN_00576140();
        if (idx < 6) {
            char* ld = M(char*, 0x1cc);
            if (ld && ld[0x6e]) {
                char* o = *(char**)((char*)this + idx * 20 + 0x508);
                o[0xb] = 1;
            }
        }
        M(int, 0x188)--;
        LocalState* ls = ((LocalState**)M(void*, 0x160))[M(int, 0x188) - 1];
        if (ls) ls->AddRef();

        {
        NameProvider* np = (NameProvider*)((char*)this + 0xc);
        WStr s1(np->GetA());
        WStr s2(np->GetB());
        WStr s3(np->GetC());
        UndoListVec* ul = (UndoListVec*)((char*)this + 0x174);
        uint8_t savedFlag = M(uint8_t, 0x4b4);
        UndoEntry* entry = ((UndoEntry**)M(void*, 0x174))[M(int, 0x188) - 1];
        if (entry) entry->AddRef();

        void* rawRes = operator_new(0xe0, "Editor", 0, 0, 0, 0);
        EditorResource* res = rawRes ? ((EditorResource*)rawRes)->Init() : 0;
        if (res) res->mRefCount++;
        res->CopyFrom(entry);
        ModelMem* mm = M(ModelMem*, 0x98);
        res->mKey = mm->key;
        PrepareAppForNewModel(res);

        np->SetA(s1.mb);
        np->SetB(s2.mb);
        np->SetC(s3.mb);
        M(uint8_t, 0x4b4) = savedFlag;
        SetLocalState(ls);

        UndoEntry* e2 = ul->mpBegin[M(int, 0x188) - 1];
        if (e2) e2->AddRef();
        Out16 tmp;
        uint mt = ((ModelObj*)M(void*, 0x98))->GetModelThing();
        Out16* r = SomeSetup(&tmp, e2, mt, 1);
        M(uint, 0x48) = r->w[0];
        M(uint, 0x4c) = r->w[1];
        M(uint, 0x50) = r->w[2];
        M(uint, 0x54) = r->w[3];
        ((EditorUI*)M(void*, 0x78))->UpdateUIBasedOnModelSaveability();

        if (!sAppProperties->GetDescription(0x55d7ca1)) {
            if (!FUN_004edf40(res->GetThing(), 0)) M(uint, 0x48) |= 0x10;
            else M(uint, 0x48) &= ~0x10u;
        }
        if (M(void*, 0x78)) ((EditorUI*)M(void*, 0x78))->UpdateUIBasedOnModelSaveability();

        if (!isRedoFlag) {
            ul->Resize(M(int, 0x188));
            ((LocalStateVec*)((char*)this + 0x160))->Resize(M(int, 0x188));
        }
        if (postMsg) {
            void* rawEv = operator_new(0x30, "Editor", 0, 0, 0, 0);
            AnimEventInfo* ev = rawEv ? ((AnimEventInfo*)rawEv)->Init() : 0;
            if (ev) ev->AddRef();
            ev->MessagePost(0xb23938bc, 0, M(void*, 0x98), 0, 0, 0.0f, 0, -1, 1.0f);
            if (ev) ev->Release();
        }
        if (isRedoFlag && M(void*, 0x78)) ((EditorUI*)M(void*, 0x78))->EnableRedoButton(true);
        if (e2) e2->Release();
        RcRelease(res);
        if (entry) entry->Release();
        }   // s3, s2, s1 destruct here
        if (ls) ls->Release();
    }
    if (M(void*, 0x78)) ((EditorUI*)M(void*, 0x78))->EnableUndoButton(M(int, 0x188) != 1);
}

// ---------------------------------------------------------------------------
// @ 0x0058a950
void cAppModeEditorBase::Redo() {
    int count = (M(int, 0x178) - M(int, 0x174)) >> 2;
    if (M(int, 0x188) < count) {
        int i = ++M(int, 0x188);
        LocalState* ls = ((LocalState**)M(void*, 0x160))[i - 1];
        if (ls) ls->AddRef();

        {
        NameProvider* np = (NameProvider*)((char*)this + 0xc);
        WStr s1(np->GetA());
        WStr s2(np->GetB());
        WStr s3(np->GetC());
        uint8_t savedFlag = M(uint8_t, 0x4b4);
        UndoEntry* entry = ((UndoEntry**)M(void*, 0x174))[M(int, 0x188) - 1];
        if (entry) entry->AddRef();

        void* rawRes = operator_new(0xe0, "Editor", 0, 0, 0, 0);
        EditorResource* res = rawRes ? ((EditorResource*)rawRes)->Init() : 0;
        if (res) res->mRefCount++;
        res->CopyFrom(entry);
        ModelMem* mm = M(ModelMem*, 0x98);
        res->mKey = mm->key;
        PrepareAppForNewModel(res);

        np->SetA(s1.mb);
        np->SetB(s2.mb);
        np->SetC(s3.mb);
        M(uint8_t, 0x4b4) = savedFlag;
        SetLocalState(ls);

        UndoEntry* e2 = ((UndoEntry**)M(void*, 0x174))[M(int, 0x188) - 1];
        if (e2) e2->AddRef();
        Out16 tmp;
        uint mt = ((ModelObj*)M(void*, 0x98))->GetModelThing();
        Out16* r = SomeSetup(&tmp, e2, mt, 1);
        M(uint, 0x48) = r->w[0];
        M(uint, 0x4c) = r->w[1];
        M(uint, 0x50) = r->w[2];
        M(uint, 0x54) = r->w[3];
        ((EditorUI*)M(void*, 0x78))->UpdateUIBasedOnModelSaveability();
        if (M(void*, 0x78)) ((EditorUI*)M(void*, 0x78))->EnableUndoButton(true);
        if (e2) e2->Release();
        RcRelease(res);
        if (entry) entry->Release();
        }
        if (ls) ls->Release();
    }
    if (M(void*, 0x78)) {
        int cnt = (M(int, 0x178) - M(int, 0x174)) >> 2;
        ((EditorUI*)M(void*, 0x78))->EnableRedoButton(M(int, 0x188) != cnt);
    }
}
