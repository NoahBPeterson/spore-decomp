// slice s00586b00 -- SP::cAppModeEditorBase::PrepareAppForNewModel (0x00586b00) and SetMode (0x00587270).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
// Retail layout: member offsets come from the disassembly (the 2008 PDB layout is shifted).
#include "types.h"

typedef unsigned int uint;

extern "C" void* __cdecl FUN_011e0744(void* dst, const void* src, unsigned n);   // memcpy/memmove thunk
void __cdecl operator_delete_array(void* p);                                      // 0x00F47380
void* __cdecl operator_new(unsigned, const char*, int, int, int, int);           // 0x00F473A0

extern wchar_t gEmptyString16[2];     // 0x01667BAC

struct WStrE {   // eastl::basic_string<wchar_t> (default constructed)
    wchar_t* mb;
    wchar_t* me;
    wchar_t* mc;
    WStrE() { mb = gEmptyString16; me = gEmptyString16; mc = gEmptyString16 + 1; }
    ~WStrE() {
        if ((((char*)mc - (char*)mb) & ~1) > 2) {
            if (mb) operator_delete_array(mb);
        }
    }
};

// refcount sub-object {vptr, count} lives at obj+4 (count at obj+8)
inline void RcRelease(void* obj) {
    void** sub = (void**)((char*)obj + 4);
    int c = ((int*)sub)[1] - 1;
    ((int*)sub)[1] = c;
    if (c == 0) {
        ((int*)sub)[1] = 1;
        ((void(__thiscall*)(void*, int))(*(void***)sub)[0])(sub, 1);
    }
}

struct IRef {   // AddRef/Release in slots 1/2 (RefCountVTemplate)
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};
struct IRef4 {   // Release in slot 1
    virtual void v0();
    virtual void Release();
};

struct NameProvider {   // cISPEditorNameProvider at this+0xC
    virtual void SetA(const wchar_t* s);        // +0
    virtual const wchar_t* GetA();              // +4
    virtual void SetB(const wchar_t* s);        // +8
    virtual const wchar_t* GetB();              // +0xC
    virtual void SetC(const wchar_t* s);        // +0x10
};

struct Key { uint inst, type, group; };

struct Property {
    char pad[0x12];
    uint16_t type;
    uint* GetUInt();     // 0x0041EA00
    float* GetFloat();   // 0x0041EA70
};
struct PropList {   // vtable slot 9 (+0x24): lookup
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool Get(uint id, Property** out);
};

struct AssetMeta { void GetTagsString(WStrE* out); };   // 0x00550CF0
struct MetaObj { virtual void v0(); virtual void v1(); virtual void v2(); virtual AssetMeta* Cast(uint id); };

struct ResManager {   // vslot 3 (+0xC) gets a resource
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool GetResource(Key* key, MetaObj** out, int a, int b, int c, int d);
};
ResManager* __cdecl GetManager();          // 0x0067DCD0

struct Naming { void SetDataProvider(NameProvider* np); };       // 0x005BFCC0
struct TokenTranslator {
    void SetOldModelName(const wchar_t* n);   // 0x005D6090
    void FUN_005d60c0(const wchar_t* n);      // 0x005D60C0
};
extern TokenTranslator* gTokenTranslator;     // 0x015EEBEC

struct CreatureMgr {   // cSPEditorAnimatedCreatureManager
    void RemoveCreature(uint id);                                    // 0x0059C6E0
    void SetCreaturePreserveHeight(uint id, int v);                  // 0x0059CF60
    void SetCreatureTargetPosition(uint id, float x, float y, float z, int a, int b);   // 0x0059CF00 (vec3 by value)
    void* GetCreatureStructure(uint id);                             // 0x0059CAC0
    void* GetCreatureStructure2(uint id, int a);                     // 0x0059CAC0 (2 arg)
    void SetCreatureTargetAngle(uint id, float a, int b);            // 0x0059CEA0
};

struct Vec3 { float x, y, z; };
struct FVec { FVec& operator=(const FVec& o); };   // 0x0050D4E0
struct Flagged {
    void SetFlag();   // 0x0059AEA0
};
struct Sink { void FUN_00a04550(int i, Vec3* v); };   // 0x00A04550

struct SPModel {   // cSPEditorModel
    char pad[0x8];
    int mRefCount;     // +8
    uint kInst;        // +0xC
    uint kType;        // +0x10
    uint kGroup;       // +0x14
    char pad2[0x40];
    uint f58;
    void FUN_004ad330();                                  // 0x004AD330
    void FUN_004ada80(float v);                           // 0x004ADA80
    void FUN_004adac0(float v);                           // 0x004ADAC0
    void FUN_004adae0(float v);                           // 0x004ADAE0
    void FUN_004adb20(float v);                           // 0x004ADB20
    void FUN_004adc00(float v);                           // 0x004ADC00
    void FUN_004ae260(uint a, uint b, int c, int d);      // 0x004AE260
    void FUN_004adba0(uint v);                            // 0x004ADBA0
    void FUN_004adbe0(uint v);                            // 0x004ADBE0
    void FUN_004adb60(uint v);                            // 0x004ADB60
    void FUN_004abad0(uint v);                            // 0x004ABAD0
    float FUN_004adb40();                                 // 0x004ADB40
    void FUN_004ad550(float* out, int a);                 // 0x004AD550
    void FUN_004adc20(int v);                             // 0x004ADC20
    void FUN_004adfc0(int v);                             // 0x004ADFC0
    int  FUN_004accf0();                                  // 0x004ACCF0
    struct SubObj* FUN_004accb0(int i, int a, int b, int c, int d);   // 0x004ACCB0 (5 arg)
    struct SubObj* FUN_004accb0b(int i, int a);                       // 0x004ACCB0 (2 arg)
    float* FUN_004adca0(float* out, int i);               // 0x004ADCA0
};
struct SubObj {
    void FUN_0043a5e0();   // 0x0043A5E0
    void FUN_0043a830();   // 0x0043A830
    void FUN_0043a9a0(int a, int b);   // 0x0043A9A0
};

struct SkinMgr {
    bool FUN_004c4630();                  // 0x004C4630
    void FUN_004c4eb0();                  // 0x004C4EB0
    void FUN_004c3070(void* app, SPModel* m, void* x);   // 0x004C3070
    void FUN_004c5100(float a, float b);  // 0x004C5100
    void FUN_004c4650(int v);             // 0x004C4650
    bool FUN_004c58b0();                  // 0x004C58B0
    void FUN_004c5200(SPModel* m);        // 0x004C5200
    void* GetSkin(int v);                 // 0x004C49E0
};
struct DecoMgr {   // this+0x14C
    void FUN_005d31b0();                  // 0x005D31B0
    void FUN_005d3f10(SPModel* m, void* x);                  // 0x005D3F10
    void FUN_005d36e0(SPModel* m, void* x, int v);           // 0x005D36E0
};
struct Handle { void* FUN_0047e6c0(); };    // 0x0047E6C0
struct PlayMode {
    void Stop();                  // 0x0062C340
    void HandleMessages(int v);   // 0x0062BF10
};
struct VProbe { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                virtual void v5(); virtual void v6(); virtual void v7();
                virtual void SlotX(int a);   // +0x1c
};
struct CamHolder {   // object at creatureMgr+0x38
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void SlotX(int a);   // +0x50
};
struct AnimEventInfo {   // cSPEditorAnimatedEventInfo, 0x30
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
    AnimEventInfo* Init();    // 0x0059D960
    void MessageSend(uint msg, int a, void* model, int b, int c, float d, int e, int f, float g);   // 0x0059D8B0
};
struct MessageServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Post(uint msg, int a, int b);   // +0x14
};
MessageServer* __cdecl GetMessageServer();   // 0x0067DCC0

struct Obj401050 {
    bool FUN_0045b210();    // 0x0045B210
    void FUN_0045b150();    // 0x0045B150
    void FUN_0045ae10();    // 0x0045AE10
};
Obj401050* __stdcall FUN_00401050(int a);                 // 0x00401050
Obj401050* __stdcall FUN_00401050_2(int a, int b);        // 0x00401050 (2 arg)

float __cdecl GetModelMinZ(SPModel* m);                   // 0x0048CF00
bool  __cdecl FUN_004a0ac0(SPModel* m);                   // 0x004A0AC0
void  __cdecl FUN_004934d0(SPModel* m, Vec3 v, int z);    // 0x004934D0
void* __cdecl FUN_0046b8e0(float* out, SPModel* m, uint v);   // 0x0046B8E0
void  __cdecl FUN_004b7660(SPModel* m);                   // 0x004B7660
void  __cdecl FUN_0046bfd0(float* out, SPModel* m);       // 0x0046BFD0
void  __cdecl PlayEditorSound(uint a, uint b, float v, int z);   // 0x00435F40
extern float gFloatThreshold;    // 0x01485378
extern float gDefaultA;          // 0x013EC478
extern float gDefaultB;          // 0x013F0318
extern float gSignMask;          // 0x013EB8B0 (xorps constant, used for negation)
extern uint  gDefaultBlock[9];   // 0x015E505C

namespace SP {

class cAppModeEditorBase {
public:
    virtual void v0();
    char pad[0x1000];

    void PrepareAppForNewModel(SPModel* model);   // 0x00586b00
    bool SetMode(int mode, char force);           // 0x00587270

    // callees (other slices)
    void ScaleBlock();                  // 0x00586960
    void FUN_0057e340(int a);           // 0x0057E340
    void FUN_00582fe0(int a, int b);    // 0x00582FE0
    void FUN_0057c440();                // 0x0057C440
    int  FUN_00576140();                // 0x00576140
    void CreateWidget2(int a);          // 0x005DBB60
    void FUN_00573c00(int a, int b);    // 0x00573C00
    void SetRolloverHandle(int a, int b);   // 0x00573D70
    void RemoveTorsoFromEffectsMask();  // 0x005772B0
    void FUN_005744b0(int mode);        // 0x005744B0
    void UpdateRenderSettings();        // 0x005794B0
    void FUN_00573390();                // 0x00573390
    void FUN_00573330();                // 0x00573330
};

}  // namespace SP

using namespace SP;

#define M(T, off) (*(T*)((char*)this + (off)))

// ---------------------------------------------------------------------------
// @ 0x00586b00
// Reset all per-model editor state, adopt the new model (updating name provider / tags), then
// re-apply bounds, skin, decorations and preload settings for it.
void cAppModeEditorBase::PrepareAppForNewModel(SPModel* model) {
    if (M(uint8_t, 0x472)) ScaleBlock();

    if (M(void*, 0x380)) {
        IRef* p = M(IRef*, 0x380);
        if (p) {
            M(void*, 0x380) = 0;
            p->Release();
        }
    }

    // M(0x39c).clear()  (vector erase(begin, end))
    {
        uint* e = M(uint*, 0x3a0);
        uint* b = M(uint*, 0x39c);
        FUN_011e0744(b, e, (char*)e - (char*)e);
        M(uint*, 0x3a0) = M(uint*, 0x3a0) + (-(e - b));
    }

    {
        IRef* p = M(IRef*, 0xd0);
        if (p) { M(void*, 0xd0) = 0; p->Release(); }
    }
    {
        IRef4* p = M(IRef4*, 0x148);
        if (p) { M(void*, 0x148) = 0; p->Release(); }
    }
    {
        IRef* p = M(IRef*, 0xd4);
        if (p) { M(void*, 0xd4) = 0; p->Release(); }
    }
    {
        IRef* p = M(IRef*, 0xd8);
        if (p) { M(void*, 0xd8) = 0; p->Release(); }
    }
    {
        IRef* p = M(IRef*, 0xdc);
        if (p) { M(void*, 0xdc) = 0; p->Release(); }
    }
    {
        IRef* p = M(IRef*, 0xcc);
        if (p) { M(void*, 0xcc) = 0; p->Release(); }
    }

    if (M(SPModel*, 0x98)) M(SPModel*, 0x98)->FUN_004ad330();

    NameProvider* np = (NameProvider*)((char*)this + 0xc);
    if (M(char*, 0x1cc)) np->SetC(*(const wchar_t**)(M(char*, 0x1cc) + 0x50));

    SPModel* newModel = model;
    if (newModel) {
        SPModel* cur = M(SPModel*, 0x98);
        if (newModel != cur) {
            newModel->mRefCount++;
            M(SPModel*, 0x98) = newModel;
            if (cur) RcRelease(cur);
        }
        Key key;
        SPModel* m = M(SPModel*, 0x98);
        key.inst = m->kInst;
        key.type = m->kType;
        key.group = m->kGroup;
        key.type = 0x30bdee3;
        MetaObj* meta = 0;
        ResManager* mgr = GetManager();
        if (meta) {
            IRef4* t = (IRef4*)meta;
            meta = 0;
            t->Release();
        }
        if (mgr->GetResource(&key, &meta, 0, 0, 0, 0)) {
            AssetMeta* am = meta ? meta->Cast(0x30bdee3) : 0;
            WStrE tags;
            am->GetTagsString(&tags);
            np->SetC(tags.mb);
        }
        ((Naming*)M(void*, 0x358))->SetDataProvider(np);
        gTokenTranslator->SetOldModelName(np->GetA());
        TokenTranslator* tt = gTokenTranslator;
        tt->FUN_005d60c0(np->GetA());
        if (meta) ((IRef4*)meta)->Release();
        newModel = model;
    }

    if (M(void*, 0x360) && M(uint, 0x364)) {
        if (M(uint8_t, 0x385)) FUN_0057e340(0);
        ((CreatureMgr*)M(void*, 0x360))->RemoveCreature(M(uint, 0x364));
        M(uint, 0x364) = 0;
    }

    SPModel* m = M(SPModel*, 0x98);
    M(uint8_t, 0x4b2) = 0;
    M(uint8_t, 0x39a) = 1;
    m->FUN_004ada80(M(float, 0x2b8));
    M(SPModel*, 0x98)->FUN_004adac0(M(float, 0x2bc));
    M(SPModel*, 0x98)->FUN_004adae0(M(float, 0x2c0));
    M(SPModel*, 0x98)->FUN_004adb20(M(float, 0x2c4));
    M(SPModel*, 0x98)->FUN_004adc00(M(float, 0x2d4));
    M(SPModel*, 0x98)->FUN_004ae260(M(uint, 0x84), M(uint, 0x90), 1, 1);
    M(SPModel*, 0x98)->FUN_004adba0(M(uint8_t, 0x470));
    M(SPModel*, 0x98)->FUN_004adbe0(M(uint8_t, 0x471));
    M(SPModel*, 0x98)->FUN_004adb60(M(uint8_t, 0x2f9));
    M(SPModel*, 0x98)->FUN_004abad0(M(uint, 0x304));

    if (M(float, 0x2d4) > gFloatThreshold) {
        if (!FUN_004a0ac0(M(SPModel*, 0x98))) {
            float minZ = GetModelMinZ(M(SPModel*, 0x98));
            if (M(float, 0x2d4) > minZ) {
                float d = M(float, 0x2d4) - minZ;
                float bbox[6];
                M(SPModel*, 0x98)->FUN_004ad550(bbox, 0);
                float top = bbox[5] + d;
                if (M(SPModel*, 0x98)->FUN_004adb40() > top) {
                    Vec3 v = { 0.0f, 0.0f, d };
                    FUN_004934d0(M(SPModel*, 0x98), v, 0);
                }
            }
        }
    }

    if (M(PropList*, 0x24)) {
        Property* prop;
        if (M(PropList*, 0x24)->Get(0x600c6b8, &prop) && prop->type == 0xa) {
            uint v = *prop->GetUInt();
            if (v) {
                float out[4];
                FUN_0046b8e0(out, M(SPModel*, 0x98), v);
                Vec3 t = { out[3], out[1], out[2] };
                FUN_004934d0(M(SPModel*, 0x98), t, 0);
            }
        }
    }

    if (M(uint8_t, 0x2f2)) {
        if (M(DecoMgr*, 0x14c)) M(DecoMgr*, 0x14c)->FUN_005d31b0();
        if (M(uint8_t, 0x2f3)) {
            if (newModel)
                M(DecoMgr*, 0x14c)->FUN_005d3f10(M(SPModel*, 0x98), M(void*, 0x84));
            else
                M(DecoMgr*, 0x14c)->FUN_005d36e0(M(SPModel*, 0x98), M(void*, 0x84), 8);
        }
    }

    if (M(uint8_t, 0x2f1)) {
        SkinMgr* sk = M(SkinMgr*, 0x150);
        if (sk) {
            bool r = sk->FUN_004c4630();
            M(SkinMgr*, 0x150)->FUN_004c4eb0();
            M(SkinMgr*, 0x150)->FUN_004c3070(this, M(SPModel*, 0x98), M(void*, 0x84));
            float a = gDefaultA;
            float b = gDefaultB;
            if (M(PropList*, 0x24)) {
                Property* prop;
                if (M(PropList*, 0x24)->Get(0x711306cd, &prop) && prop->type == 0xd)
                    a = *prop->GetFloat();
            }
            if (M(PropList*, 0x24)) {
                Property* prop;
                if (M(PropList*, 0x24)->Get(0x711306ce, &prop) && prop->type == 0xd)
                    b = *prop->GetFloat();
            }
            M(SkinMgr*, 0x150)->FUN_004c5100(a, b);
            M(SkinMgr*, 0x150)->FUN_004c4650(r);
        }
        if (M(int, 0x31c) == 1) {
            FUN_00582fe0(0, 0);
            FUN_0057e340(1);
            SPModel* mm = M(SPModel*, 0x98);
            bool skip = false;
            if (M(SkinMgr*, 0x154)) skip = M(SkinMgr*, 0x154)->FUN_004c58b0();
            if (!skip && mm && M(SkinMgr*, 0x150)) M(SkinMgr*, 0x150)->FUN_004c5200(mm);
        }
    } else {
        FUN_004b7660(M(SPModel*, 0x98));
        if (M(int, 0x31c) == 1) {
            SPModel* mm = M(SPModel*, 0x98);
            int n = mm->FUN_004accf0();
            for (int i = 0; i < n; i++) {
                M(SPModel*, 0x98)->FUN_004accb0(i, 3, 1, 0, 1)->FUN_0043a5e0();
                M(SPModel*, 0x98)->FUN_004accb0b(i, 0)->FUN_0043a830();
            }
        }
    }

    FUN_0057c440();
    {
        SPModel* mm = M(SPModel*, 0x98);
        if (mm->f58 == 0) mm->f58 = *M(uint*, 0x334);
    }
    if (M(uint8_t, 0x2f4)) M(SPModel*, 0x98)->FUN_004adc20(1);

    if (M(char*, 0x1cc) && M(SPModel*, 0x98)->kType == 0x2b978c46) {
        // M(0x588) = ld->vec at +0x70  (eastl::vector<float>::operator=)
        *(FVec*)((char*)this + 0x588) = *(FVec*)(M(char*, 0x1cc) + 0x70);
    } else {
        uint* e = M(uint*, 0x58c);
        uint* b = M(uint*, 0x588);
        FUN_011e0744(b, e, (char*)e - (char*)e);
        M(uint*, 0x58c) = M(uint*, 0x58c) + (-(e - b));
    }
    M(SPModel*, 0x98)->FUN_004adfc0(0);
}

// ---------------------------------------------------------------------------
// @ 0x00587270
// Switch the editor mode (0 = parts, 1 = paint, 2 = play/test): tear down the old mode's state, set
// the new mode, then set up the new mode (messages, widgets, creature animation).
bool cAppModeEditorBase::SetMode(int mode, char force) {
    int* pMode = &M(int, 0x31c);
    int old = *pMode;
    if (old == mode && !force) return false;
    int busy = M(int, 0x38c);
    if (busy != 0 && busy != 6) return false;
    M(float, 0x68) = 0.0f;

    if (old == 0) {
        if (M(uint8_t, 0x472)) ScaleBlock();
    } else if (old == 1) {
        int n = M(SPModel*, 0x98)->FUN_004accf0();
        for (int i = 0; i < n; i++) {
            M(SPModel*, 0x98)->FUN_004accb0(i, 0, 1, 0, 1)->FUN_0043a5e0();
            M(SPModel*, 0x98)->FUN_004accb0b(i, 0)->FUN_0043a830();
        }
        M(uint, 0x3c) &= ~1u;
    } else if (old == 2) {
        if (FUN_00401050(M(int, 0x278))->FUN_0045b210())
            FUN_00401050(M(int, 0x278))->FUN_0045b150();
        if (M(int, 0x27c)) FUN_00401050_2(M(int, 0x27c), 1)->FUN_0045ae10();
        char* a = M(char*, 0xa4);
        if (a) {
            FUN_011e0744(a + 0x1c, gDefaultBlock, 36);
            *(uint16_t*)(a + 8) |= 2;
            (*(uint16_t*)(a + 0xa))++;
        }
        M(PlayMode*, 0x7c)->Stop();
        char* b = M(char*, 0xa8);
        if (b) *(uint*)(b + 4) |= 1;
        CreateWidget2(3);
        CreatureMgr* cm = M(CreatureMgr*, 0x360);
        cm->SetCreaturePreserveHeight(M(uint, 0x364), 1);
        float bb[8];
        FUN_0046bfd0(bb, M(SPModel*, 0x98));
        cm = M(CreatureMgr*, 0x360);
        cm->SetCreatureTargetPosition(M(uint, 0x364), -bb[2], -bb[3], -bb[4], 1, 0);
        if (M(CreatureMgr*, 0x360)->GetCreatureStructure(M(uint, 0x364))) {
            ((Flagged*)M(CreatureMgr*, 0x360)->GetCreatureStructure2(M(uint, 0x364), 1))->SetFlag();
        }
    }

    FUN_00573c00(0, -1);
    {
        char* h = M(char*, 0xd4);
        if (h) {
            if (!((*(uint*)(h + 0xdc8) >> 1) & 1)) {
                Handle* hd = M(Handle*, 0xe4);
                if (hd && hd->FUN_0047e6c0() == h) SetRolloverHandle(0, 1);
                ((SubObj*)M(void*, 0xd4))->FUN_0043a9a0(0, 1);
            }
            IRef* r = M(IRef*, 0xd4);
            if (r) {
                M(void*, 0xd4) = 0;
                r->Release();
            }
        }
    }
    if (M(uint8_t, 0xe8)) M(uint8_t, 0xe8) = 0;
    if (M(uint8_t, 0xe9)) {
        RemoveTorsoFromEffectsMask();
        M(uint8_t, 0xe9) = 0;
    }

    bool wasPainted = M(SkinMgr*, 0x150) && M(SkinMgr*, 0x150)->FUN_004c4630();
    bool nowPainted = M(SkinMgr*, 0x150) && mode != 0;
    if (wasPainted) {
        if (!nowPainted) M(SkinMgr*, 0x150)->FUN_004c4650(0);
    } else if (nowPainted) {
        M(SkinMgr*, 0x150)->FUN_004c4650(1);
        SPModel* mm = M(SPModel*, 0x98);
        bool skip = false;
        if (M(SkinMgr*, 0x154)) skip = M(SkinMgr*, 0x154)->FUN_004c58b0();
        if (!skip && mm && M(SkinMgr*, 0x150)) M(SkinMgr*, 0x150)->FUN_004c5200(mm);
    }
    FUN_005744b0(mode);

    if (M(void*, 0x360) && M(SkinMgr*, 0x150) && M(SkinMgr*, 0x150)->GetSkin(1) && old == 0) {
        if (M(void*, 0x360) && M(uint, 0x364)) {
            if (M(uint8_t, 0x385)) FUN_0057e340(0);
            M(CreatureMgr*, 0x360)->RemoveCreature(M(uint, 0x364));
            M(uint, 0x364) = 0;
        }
    }
    *pMode = mode;

    if (!M(void*, 0x360)) goto angle_step;
    if (M(SkinMgr*, 0x150) && M(SkinMgr*, 0x150)->GetSkin(1) && mode == 0) {
        if (!M(void*, 0x360)) goto angle_step;
        if (M(uint, 0x364)) {
            if (M(uint8_t, 0x385)) FUN_0057e340(0);
            M(CreatureMgr*, 0x360)->RemoveCreature(M(uint, 0x364));
            M(uint, 0x364) = 0;
        }
    }
    if (!M(void*, 0x360) || !M(SkinMgr*, 0x150) || !M(SkinMgr*, 0x150)->GetSkin(1)) goto angle_step;
    if (M(uint8_t, 0x385) == 0) {
        FUN_00582fe0(0, 0);
        FUN_0057e340(1);
        goto render_step;
    }
angle_step:
    if (M(uint8_t, 0x385) && old == 2)
        M(CreatureMgr*, 0x360)->SetCreatureTargetAngle(M(uint, 0x364), 0.0f, 1);
render_step:
    UpdateRenderSettings();
    {
        char* cm = M(char*, 0x360);
        if (cm) {
            CamHolder* ch = *(CamHolder**)(cm + 0x38);
            if (ch) ch->SlotX(0);
        }
    }

    if (mode == 0) {
        if (M(void*, 0x360) && M(SkinMgr*, 0x150) && M(SkinMgr*, 0x150)->GetSkin(1) && M(uint8_t, 0x2b5))
            FUN_00573330();
        void* rawEv = operator_new(0x30, "Editor", 0, 0, 0, 0);
        AnimEventInfo* ev = rawEv ? ((AnimEventInfo*)rawEv)->Init() : 0;
        if (ev) ev->AddRef();
        ev->MessageSend(0xcb52be29, 0, M(void*, 0x98), 0, 0, 0.0f, 0, -1, 1.0f);
        if (ev) ev->Release();
    } else if (mode == 1) {
        M(char*, 0x4d8)[5] = 1;
        int r = FUN_00576140();
        if (r < 6 && M(char*, 0x1cc) && M(char*, 0x1cc)[0x6e]) {
            (*(char**)((char*)this + r * 20 + 0x508))[5] = 1;
        }
        if (M(void*, 0x360) && M(SkinMgr*, 0x150) && M(SkinMgr*, 0x150)->GetSkin(1) && M(uint8_t, 0x2b5))
            FUN_00573330();
        int n = M(SPModel*, 0x98)->FUN_004accf0();
        for (int i = 0; i < n; i++) {
            M(SPModel*, 0x98)->FUN_004accb0(i, 3, 1, 0, 1)->FUN_0043a5e0();
            M(SPModel*, 0x98)->FUN_004accb0b(i, 0)->FUN_0043a830();
        }
        void* rawEv = operator_new(0x30, "Editor", 0, 0, 0, 0);
        AnimEventInfo* ev = rawEv ? ((AnimEventInfo*)rawEv)->Init() : 0;
        if (ev) ev->AddRef();
        ev->MessageSend(0x565d8223, 0, M(void*, 0x98), 0, 0, 0.0f, 0, -1, 1.0f);
        GetMessageServer()->Post(0x578dedb, 0, 0);
        if (ev) ev->Release();
    } else if (mode == 2) {
        M(char*, 0x4d8)[6] = 1;
        int r = FUN_00576140();
        if (r < 6 && M(char*, 0x1cc) && M(char*, 0x1cc)[0x6e]) {
            char** c = (char**)((char*)this + r * 20 + 0x508);
            M(char*, 0x580)[r] = (*c)[6];
            (*c)[6] = 1;
        }
        CreateWidget2(2);
        if (M(VProbe*, 0x358)) M(VProbe*, 0x358)->SlotX(0);
        if (M(void*, 0x360) && M(SkinMgr*, 0x150) && M(SkinMgr*, 0x150)->GetSkin(1)) FUN_00573390();
        {
            char* cm = M(char*, 0x360);
            if (cm) {
                CamHolder* ch = *(CamHolder**)(cm + 0x38);
                if (ch) {
                    ch->SlotX(1);
                    char* s = (char*)M(CreatureMgr*, 0x360)->GetCreatureStructure(M(uint, 0x364));
                    if (s && *(void**)(s + 8)) {
                        for (int i = 0; i < 3; i++) {
                            float tmp[3];
                            float* p = M(SPModel*, 0x98)->FUN_004adca0(tmp, i);
                            Vec3 v = { p[0], p[1], p[2] };
                            ((Sink*)*(void**)(s + 8))->FUN_00a04550(i, &v);
                        }
                    }
                }
            }
        }
        if (FUN_00401050(M(int, 0x27c))->FUN_0045b210())
            FUN_00401050(M(int, 0x27c))->FUN_0045b150();
        if (M(int, 0x278)) FUN_00401050_2(M(int, 0x278), 1)->FUN_0045ae10();
        char* b = M(char*, 0xa8);
        if (b) *(uint*)(b + 4) &= ~1u;
        M(PlayMode*, 0x7c)->HandleMessages(M(int, 0x278));
        M(CreatureMgr*, 0x360)->SetCreaturePreserveHeight(M(uint, 0x364), 0);
    }

    if (M(uint8_t, 0x20e)) PlayEditorSound(0x1d6253c0, 0xbd5385c8, (float)*pMode, 0);
    return true;
}
