// slice s00577130
// SP::cAppModeEditorBase methods, /O2 /arch:SSE /fp:fast (same module as s00575270).
#include <new>
#include <string.h>
#include <math.h>
#include "types.h"

namespace SP { namespace EditorUtils {
    void __cdecl PlayEditorSound(uint32_t id, uint32_t sound, float value, int flags);   // 0x435f40
    float __cdecl CalculateModelSize(void* model);                                      // 0x48ca10
    int   __cdecl CountModelParts(void* model);                                         // 0x48cc20
} }

void   __stdcall SomeGuardCall(void* p);          // 0x440b90
void   __cdecl PlayEditorEvent(uint32_t id);      // 0x4a88d0
int    __cdecl g_soundBlockCounter;               // 0x15e4eec

struct IObject {
    virtual void slot0();
    virtual void AddRef();                        // +0x4
    virtual void Release();                       // +0x8
};

struct ISkinManager {
    void* GetSkin(int);                           // 0x4c49e0
};

struct ObjF8 {
    void SomeMethod(int);                         // 0x697a10
};

struct ObjE4 {
    void* SomeCall();                             // 0x47e6c0
};

template <typename T> static inline T* Field(void* self, uint32_t off) {
    return *(T**)((char*)self + off);
}
template <typename T> static inline T& Ref(void* self, uint32_t off) {
    return *(T*)((char*)self + off);
}


// ---- helpers for PreloadResources / HasAnyResource / LoadSomething / SomeLoader ----
struct ResKey3 { uint32_t a, b, c; };
struct IRC {                                      // COM-style refcounted: AddRef +0, Release +4
    virtual void AddRef();
    virtual void Release();
};
struct IRCptr {                                   // raw ref slot with the AsPointer() idiom (no dtor: orig has no EH)
    IRC* mp;
    IRCptr() : mp(0) {}
    void Drop() { if (mp) mp->Release(); }
    IRC** AsPointer()
    {
        if (mp) {
            IRC* t = mp;
            mp = 0;
            t->Release();
        }
        return &mp;
    }
};
struct cTexturePreload {                          // size 0x34
    cTexturePreload(int mode);                    // 0x007b07e0
    virtual void AddRef();                        // vtable +0
    virtual void Release();                       // vtable +4
    void PreloadTextureList(ResKey3* key);        // 0x007b1e90 (thiscall, ret 4)
    uint32_t pad[12];                             // object size 0x34
};
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);   // 0x00f473a0
struct cPropMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, IRC** ppList);   // 0x2c
};
cPropMgr* PropertyManager();                      // 0x0067de30
bool GetPropertyAsKeyInstance(IRC* list, uint32_t id, uint32_t* out);   // 0x006a12a0 (cdecl)
bool GetPropertyAsKey(IRC* list, uint32_t id, ResKey3* out);            // 0x006a1250 (cdecl)
extern uint32_t g_preloadGroup;                   // 0x0150cdd4
namespace SP {
class cSPEditorBlock {
public:
    ResKey3 GetMirroredKey(int type, int sub);    // 0x00438f20 (thiscall, hidden return, ret 0xc)
    void* F40b90(void* out);                      // 0x440b90 (copies 12 bytes at +0x5f8)
};
}
using SP::cSPEditorBlock;
struct Block {                                    // creature part, 0x1d8 bytes
    uint32_t pad0;
    uint32_t id;                                  // +4
    char pad[0x1d0];
};
struct IModelRes : IRC {
    virtual void v08();
    virtual struct ModelParts* Query(uint32_t typeId);   // +0xc
};
struct ModelParts {
    char pad[0x98];
    Block* mpBegin;                               // +0x98
    Block* mpEnd;                                 // +0x9c
};
struct IResMan {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool GetResource(ResKey3* key, IRC** out, int a, int b, int c, int d);   // +0xc
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual bool WriteResource(void* res, void* factoryData, void* db, void* factory, ResKey3* nameKey);   // +0x20
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68();
    virtual bool Slot6c(void* res, int flag);     // +0x6c
};
IResMan* GetManager();                            // 0x0067dcd0
struct cSPPaletteCursor {                         // size 0x20
    cSPPaletteCursor();                           // 0x005c7b80
    virtual void v0();
    virtual void AddRef();                        // +4
    virtual void Release();                       // +8
    void SetPalette(void* palette);               // 0x005c7bc0 (ret 4)
    struct PRec* First(void*, void*, void*, void*);   // 0x005c7e80 (ret 0x10)
    struct PRec* Next(void*, void*, void*, void*);    // 0x005c7e20 (ret 0x10)
    void Close();                                 // 0x00c2e4e0
    uint32_t pad[7];                              // object size 0x20 (vptr + 7 dwords)
};
struct PRec {
    char pad0[0xc];
    uint32_t f0c;
    char pad10[4];
    uint32_t f14;
    char pad18[0xc];
    uint32_t f24;
};
struct ModelObj {
    void Reset();                                 // 0x004ad110
};
bool __cdecl HasAnyResource(cSPEditorBlock* block, ResKey3* key);   // 0x577b20

// ---- helpers for SaveSomething ----
struct ModelRes {                                 // cSPEditorModelResource, 0xac bytes
    virtual void AddRef();                        // +0
    virtual void Release();                       // +4
    uint32_t mRefCount;                           // +4
    ResKey3 mKey;                                 // +8
    uint32_t pad14[(0xac - 0x14) / 4];
    ModelRes();                                   // 0x004b9c70
};
struct ThumbRes {                                 // 0x128 bytes
    virtual void AddRef();
    virtual void Release();
    uint32_t mRefCount;
    ResKey3 mKey;                                 // +8
    uint32_t pad14[(0x128 - 0x14) / 4];
    ThumbRes();                                   // 0x004b9da0
};
struct MetaObj {                                  // Pollinator::cAssetMetadata, 0xd8 bytes
    virtual void AddRef();
    virtual void Release();
    uint32_t pad[(0xd8 - 4) / 4];
    MetaObj();                                    // 0x00550450
    char Set(ResKey3* assetKey, const wchar_t* name, const wchar_t* description, const wchar_t* tags,
             ResKey3* parentKey, bool isPollinated);   // 0x00551240 (ret 0x18)
};
struct ResRef {                                   // holder whose out-of-line ctor stores + AddRefs
    void* mpObject;
    explicit ResRef(void* p);                     // 0x00572660
};
struct cMWModel {
    virtual void s0();
    virtual const wchar_t* Slot1();               // +4
    virtual void s2();
    virtual const wchar_t* Slot3();               // +0xc
    char pad[0xc - 4];
    ResKey3 mKey;                                 // +0xc
    bool SaveResource(ModelRes* res);             // 0x004af260 (ret 4)
};
struct SubObj5 {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual const wchar_t* Slot5();               // +0x14
};
struct TexSvc {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25();
    virtual void Slot68(void* arg);               // +0x68
};
TexSvc* __cdecl GetTexSvc();                      // 0x0067dd60
void* __cdecl GetSaveArea(uint32_t id);           // 0x006b1f90
void __cdecl Fn46d840(ModelRes* model, ThumbRes* thumb);   // 0x0046d840 (cdecl)
struct ImgObj { void* GetPixels(); };             // 0x0046f260
struct cImportExport {
    bool CreateExportThumb(ModelRes* model, void* pixels, void* saveDb, int zero, bool flag);   // 0x005fa8d0 (ret 0x14)
};
cImportExport* __cdecl GetImportExport();         // 0x005f7930
struct IAuth { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
               virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8();
               virtual bool Slot24(); };          // +0x24
IAuth* __cdecl AuthManager();                     // 0x00607a60
bool __cdecl MarkDirty(void* res);                // 0x006ad010
struct Bits128 { uint32_t w[4]; };
bool __cdecl Fn4f3d60(Bits128 a, Bits128 b);      // 0x004f3d60
extern Bits128 g_validBits;                       // 0x015dab94
int  __cdecl GetModelCategory(ResKey3* key);      // 0x00552300
int  __cdecl FindModelPart(ResKey3* key, uint32_t hash);   // 0x00556140
void __cdecl SummarizeVehiclePart(ResKey3* newKey, int part);   // 0x00555f70
static __forceinline void SummarizePart(ResKey3* key, ResKey3* newKey, uint32_t hash)
{
    if (FindModelPart(key, hash))
        SummarizeVehiclePart(newKey, FindModelPart(key, hash));
}

namespace SP {
class cAppModeEditorBase {
public:
    char pad[0x458];

    void SetSoundBlockAdded(cSPEditorBlock*);     // 0x577130
    void SetSoundBlockRemoved(cSPEditorBlock*);   // 0x5771f0
    void RemoveTorsoFromEffectsMask();            // 0x5772b0
    void PreloadResources(int key);               // 0x577310
    void SetSomeBlock(int);                       // 0x5774f0
    void UpdateBlockState();                      // 0x577520
    void SetTorsoBlock(void*, char);              // 0x577580
    bool HasSkin();                               // 0x577620
    void SaveSomething();                         // 0x577650
    bool LoadSomething(void* block);              // 0x577c40
    int  FlushFactory(void* factory);             // 0x574a20 (ret 4)
    void Sub572430(ResKey3* key);                 // 0x572430 (ret 4)
    void SomeLoader();                            // 0x577dd0

    void SetRolloverHandle(int, int);             // 0x573d70
    void DoSomeOther(int, int);                   // 0x573c00
};
}

using SP::cAppModeEditorBase;

// @ 0x00577130
void cAppModeEditorBase::SetSoundBlockAdded(cSPEditorBlock* param)
{
    int p = (int)param;
    if (Ref<char>(this, 0x20e) != 0) {
        if (p != 0) {
            int local[3];
            param->F40b90(local);
            int n = g_soundBlockCounter + 1;
            g_soundBlockCounter = n;
            SP::EditorUtils::PlayEditorSound(0x1d6253c0, 0xc8b0416e, (float)n, 0);
        }
        if (Ref<char>(this, 0x20e) != 0) {
            float sz = SP::EditorUtils::CalculateModelSize(Field<void>(this, 0x98));
            SP::EditorUtils::PlayEditorSound(0x1d6253c0, 0xdef22b96, sz, 0);
            if (Ref<char>(this, 0x20e) != 0) {
                int cnt = SP::EditorUtils::CountModelParts(Field<void>(this, 0x98));
                SP::EditorUtils::PlayEditorSound(0x1d6253c0, 0x5ee38119, (float)cnt, 0);
            }
        }
    }
}

// @ 0x005771f0
void cAppModeEditorBase::SetSoundBlockRemoved(cSPEditorBlock* param)
{
    int p = (int)param;
    if (Ref<char>(this, 0x20e) != 0) {
        if (p != 0) {
            int local[3];
            param->F40b90(local);
            SP::EditorUtils::PlayEditorSound(0x1d6253c0, 0xbb98bc04, (float)g_soundBlockCounter, 0);
        }
        if (Ref<char>(this, 0x20e) != 0) {
            float sz = SP::EditorUtils::CalculateModelSize(Field<void>(this, 0x98));
            SP::EditorUtils::PlayEditorSound(0x1d6253c0, 0xdef22b96, sz, 0);
            if (Ref<char>(this, 0x20e) != 0) {
                int cnt = SP::EditorUtils::CountModelParts(Field<void>(this, 0x98));
                SP::EditorUtils::PlayEditorSound(0x1d6253c0, 0x5ee38119, (float)cnt, 0);
            }
        }
    }
}

// @ 0x005772b0
void cAppModeEditorBase::RemoveTorsoFromEffectsMask()
{
    void* p = Ref<void*>(this, 0xf0);
    if (p) {
        void** vt = *(void***)(*(void**)p);
        ((void(__stdcall*)(void*, int))vt[91])(p, 0);
        p = Ref<void*>(this, 0xf0);
        if (p) {
            Ref<void*>(this, 0xf0) = 0;
            int c = Ref<int>(p, 0x40);
            if (c > 1) {
                Ref<int>(p, 0x40) = c - 1;
                return;
            }
            unsigned r = Ref<unsigned>(p, 4);
            int b = (r >> 31) & 1;
            void** vt2 = *(void***)(*(void**)p);
            ((void(__stdcall*)(void*, int))vt2[92])(p, b);
        }
    }
}

// @ 0x005774f0
void cAppModeEditorBase::SetSomeBlock(int param)
{
    ((ObjF8*)((char*)this + 0xf8))->SomeMethod(param);
    if ((unsigned char)param == 0)
        DoSomeOther(0, -1);
}

// @ 0x00577520
void cAppModeEditorBase::UpdateBlockState()
{
    void* p = Ref<void*>(this, 0xcc);
    if (p != 0) {
        unsigned bits = Ref<unsigned>(p, 0xdc8);
        unsigned flag = (bits >> 1) & 1;
        if (flag != 0)
            DoSomeOther(0, -1);
    }

    if (Ref<void*>(this, 0xe4) != 0) {
        void* r = ((ObjE4*)Ref<void*>(this, 0xe4))->SomeCall();
        if (r == 0 ||
            ((Ref<unsigned>(((ObjE4*)Ref<void*>(this, 0xe4))->SomeCall(), 0xdc8) >> 1) & 1) != 0)
            SetRolloverHandle(0, 1);
    }
}

// @ 0x00577580
void cAppModeEditorBase::SetTorsoBlock(void* block, char param)
{
    if (block != 0) {
        if (param != 0)
            param = 0;
        PlayEditorEvent(0xe5469985);
    } else {
        if (param != 0)
            PlayEditorEvent(0xe5469985);
    }
    void* prev = Ref<void*>(this, 0xdc);
    if (block != prev) {
        if (block)
            ((IObject*)block)->AddRef();
        Ref<void*>(this, 0xdc) = block;
        if (prev)
            ((IObject*)prev)->Release();
    }
    void* a = Ref<void*>(this, 0xd4);
    Ref<char>(this, 0xe0) = param;
    void* b = Ref<void*>(this, 0xd8);
    if (a != b) {
        if (a)
            ((IObject*)a)->AddRef();
        Ref<void*>(this, 0xd8) = a;
        if (b)
            ((IObject*)b)->Release();
    }
}

// @ 0x00577620
bool cAppModeEditorBase::HasSkin()
{
    if (Ref<int>(this, 0x360) != 0 && Ref<int>(this, 0x150) != 0) {
        if (Field<ISkinManager>(this, 0x150)->GetSkin(1) != 0)
            return true;
    }
    return false;
}

// @ 0x00577310
void cAppModeEditorBase::PreloadResources(int key)
{
    if (Ref<cTexturePreload*>(this, 0x308) == 0) {
        cTexturePreload* p = new ("Editor", 0, 0, 0, 0) cTexturePreload(-1);
        cTexturePreload* old = Ref<cTexturePreload*>(this, 0x308);
        if (p != old) {
            if (p)
                p->AddRef();
            Ref<cTexturePreload*>(this, 0x308) = p;
            if (old)
                old->Release();
        }
        ResKey3 k0 = { 0x8104e4b0, 0x510a95b, 0x40464100 };
        Ref<cTexturePreload*>(this, 0x308)->PreloadTextureList(&k0);
        ResKey3 k1 = { 0x9d1fcc2f, 0x510a95b, 0x40464100 };
        Ref<cTexturePreload*>(this, 0x308)->PreloadTextureList(&k1);
        ResKey3 k2 = { 0x7d708f46, 0x510a95b, 0x40464100 };
        Ref<cTexturePreload*>(this, 0x308)->PreloadTextureList(&k2);
    }
    if (key != -1) {
        IRCptr props;
        if (PropertyManager()->GetPropertyList(key, g_preloadGroup, props.AsPointer())) {
            cTexturePreload* p = new ("Editor", 0, 0, 0, 0) cTexturePreload(-1);
            cTexturePreload* old = Ref<cTexturePreload*>(this, 0x30c);
            if (p != old) {
                if (p)
                    p->AddRef();
                Ref<cTexturePreload*>(this, 0x30c) = p;
                if (old)
                    old->Release();
            }
            uint32_t inst = 0;
            GetPropertyAsKeyInstance(props.mp, 0x700ed5e1, &inst);
            if (inst != 0) {
                ResKey3 k3 = { inst, 0x510a95b, 0x40464100 };
                Ref<cTexturePreload*>(this, 0x30c)->PreloadTextureList(&k3);
            }
        }
        props.Drop();
    }
}

// @ 0x00577650
void cAppModeEditorBase::SaveSomething()
{
    IResMan* mgr = GetManager();
    void* saveArea = GetSaveArea(Ref<uint32_t>(this, 0x2ac));
    GetTexSvc()->Slot68(Ref<void*>(this, 0x28c));
    ModelRes* model = new ("Editor", 0, 0, 0, 0) ModelRes();
    if (model)
        model->AddRef();
    if (!Field<cMWModel>(this, 0x9c)->SaveResource(model)) {
        if (model)
            model->Release();
        return;
    }
    ResKey3* newKey = &model->mKey;
    ResKey3 nameKey = *newKey;
    nameKey.b = 0x1a99b06b;
    bool w1 = mgr->WriteResource(model, 0, saveArea, 0, &nameKey);
    bool w2 = mgr->Slot6c(model, 1);
    if (!w1 || !w2) {
        model->Release();
        return;
    }
    if (FlushFactory(Ref<void*>(this, 0x154))) {
        ThumbRes* t = new ("Editor", 0, 0, 0, 0) ThumbRes();
        ResRef tr(t);
        ThumbRes* th = (ThumbRes*)tr.mpObject;
        Fn46d840(model, th);
        ResKey3 tk = *newKey;
        tk.b = 0xf43029a;
        th->mKey = tk;
        bool t1 = mgr->WriteResource(th, 0, saveArea, 0, 0);
        bool t2 = mgr->Slot6c(th, 1);
        if (!t1 || !t2) {
            th->Release();
            model->Release();
            return;
        }
        th->Release();
    }
    bool pollen = false;
    int mode = Ref<int>(this, 0x388);
    if (((mode == 2 && Ref<char>(this, 0x4b5) != 0 && Field<cMWModel>(this, 0x9c)->mKey.b != 0x3d97a8e4) || mode == 1) &&
        Fn4f3d60(Ref<Bits128>(this, 0x58), g_validBits))
        pollen = true;
    MetaObj* mo = new ("Pollinator", 0, 0, 0, 0) MetaObj();
    ResRef mr(mo);
MetaObj* meta = (MetaObj*)mr.mpObject;
#define META meta
    cMWModel* ped = Field<cMWModel>(this, 0x9c);
    ResKey3* parentKey = (ResKey3*)((char*)this + 0x1d0);
    META->Set(newKey, ped->Slot1(), ped->Slot3(), ((SubObj5*)((char*)this + 0xc))->Slot5(), parentKey, pollen);
    bool w3 = mgr->WriteResource(META, 0, saveArea, 0, 0);
    bool w4 = MarkDirty(META);
    if (w3 && w4) {
        cImportExport* ie = GetImportExport();
        if (ie)
            ie->CreateExportThumb(model, Field<ImgObj>(this, 0x28c)->GetPixels(), saveArea, 0, 0);
        if (!pollen) {
            Ref<char>(this, 0x4b0) = 1;
        } else if (!AuthManager()->Slot24()) {
            Sub572430(&Field<cMWModel>(this, 0x9c)->mKey);
        }
        if (model->mKey.b == 0x2b978c46) {
            int* vb = Ref<int*>(this, 0x588);
            int* ve = Ref<int*>(this, 0x58c);
            if (vb == ve) {
                if (Ref<char>(this, 0x4b8) != 0 && GetModelCategory(parentKey) == 1) {
                    SummarizePart(parentKey, newKey, 0xa426730b);
                    SummarizePart(parentKey, newKey, 0xad56080c);
                    SummarizePart(parentKey, newKey, 0xf71fa311);
                    SummarizePart(parentKey, newKey, 0xbeb528cb);
                    SummarizePart(parentKey, newKey, 0x2db6dad3);
                }
            } else {
                int n = ve - vb;
                for (int i = 0; i < n; i++) {
                    int part = Ref<int*>(this, 0x588)[i];
                    if (part)
                        SummarizeVehiclePart(newKey, part);
                }
            }
        }
    }
    if (META)
        META->Release();
    model->Release();
}

#undef META

// @ 0x00577b20
bool __cdecl HasAnyResource(cSPEditorBlock* block, ResKey3* key)
{
    IResMan* mgr = GetManager();
    IRCptr ref;
    ResKey3 k0 = block->GetMirroredKey(-1, 0);
    ResKey3 k1 = block->GetMirroredKey(0, 0);
    ResKey3 k2 = block->GetMirroredKey(1, 0);
    if (mgr) {
        if (mgr->GetResource(key, ref.AsPointer(), 0, 0, 0, 0)) {
            if (!ref.mp)
                return false;
            ModelParts* m = ((IModelRes*)ref.mp)->Query(0x3c609f8);
            if (!m) {
                ref.Drop();
                return false;
            }
            Block* base = m->mpBegin;
            int n = m->mpEnd - base;
            for (int i = 0; i < n; i++) {
                if (base[i].id == k0.a || base[i].id == k1.a || base[i].id == k2.a) {
                    ref.Drop();
                    return true;
                }
            }
        }
    }
    ref.Drop();
    return false;
}

// @ 0x00577c40
bool cAppModeEditorBase::LoadSomething(void* param)
{
    ResKey3 k0 = ((cSPEditorBlock*)param)->GetMirroredKey(-1, 0);
    ResKey3 k1 = ((cSPEditorBlock*)param)->GetMirroredKey(0, 0);
    ResKey3 k2 = ((cSPEditorBlock*)param)->GetMirroredKey(1, 0);
    cSPPaletteCursor* cur = new ("Editor", 0, 0, 0, 0) cSPPaletteCursor();
    if (cur)
        cur->AddRef();
    cur->SetPalette(Ref<void*>(this, 0x3b8));
    PRec* rec = cur->First(0, 0, 0, 0);
    bool found = false;
    while (rec && !found) {
        if (rec->f24 == 0xc9db779b) {
            IRCptr props;
            if (PropertyManager()->GetPropertyList(rec->f0c, rec->f14, props.AsPointer())) {
                ResKey3 key = { 0, 0, 0 };
                if (GetPropertyAsKey(props.mp, 0x22e8410, &key))
                    found = HasAnyResource((cSPEditorBlock*)param, &key);
            }
            props.Drop();
        } else {
            uint32_t id = rec->f0c;
            if (id == k0.a || id == k1.a || id == k2.a)
                found = true;
        }
        rec = cur->Next(0, 0, 0, 0);
    }
    cur->Close();
    if (cur)
        cur->Release();
    return found;
}

// @ 0x00577dd0
void cAppModeEditorBase::SomeLoader()
{
    if (Ref<int>(this, 0x360) != 0 && Field<ISkinManager>(this, 0x150) != 0 &&
        Field<ISkinManager>(this, 0x150)->GetSkin(1) != 0)
        return;
    Field<ModelObj>(this, 0x98)->Reset();
    Ref<char>(this, 0x385) = 0;
}
