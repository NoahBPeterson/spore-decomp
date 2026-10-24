// Slice s00ea0910: SP::Audio::cCityMusicEditor and small collaborators.
// Layout reconstructed from the retail constructor at 0x00EA0EA0 (no migrated source exists):
//   +0x00/0x04/0x08  three vptrs (BIWinProc / IHandler bases)
//   +0x0c            scratch pointer (cleared by the ctor)
//   +0x10            cPlayerCityMusicConfig (embedded, 0x30 bytes)
//   +0x40            deletable array
//   +0x54            deletable array
//   +0xc4..+0xcc     three ImageEntry arrays
//   +0xd0/+0xd4      refcounted helpers
//   +0xd8            cPlayerCityMusic*
//   +0xdc            cSPUILayout*
//   +0xe0            cCityMusicNoteEditor*
//   +0xe4..+0xec     eastl::vector<cWindowPulse*> (begin/end/cap)
//   +0xf8            cCityMusicLoadSave*
//   +0x100           Connector (5 dwords)
// Calls are masked relocations: declarations only need the right convention/arity.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned int u32;
typedef unsigned char u8;

struct ReloadArgs { int a, b, c; };

// ---------------------------------------------------------------- window interfaces
// Slots are named by their retail vtable byte offset.
struct IWinNode {
    virtual void  v00(); virtual void  v04(); virtual void  v08();
    virtual void  v0c(int b);
    virtual void* v10();
    virtual void  v14(int a, void* b);
    virtual void  v18();
    virtual int   v1c();
    virtual void  v20(); virtual void  v24();
    virtual void  v28(int a, int b);
    virtual int   v2c();
    virtual int   v30();
    virtual void  v34(); virtual void  v38();
    virtual void  v3c(); virtual void  v40();
    virtual void  v44(); virtual void  v48();
    virtual void  v4c(); virtual void  v50();
    virtual void  v54(); virtual void  v58();
    virtual void  v5c(); virtual void  v60();
    virtual void  v64(); virtual void  v68();
    virtual void  v6c(); virtual void  v70();
    virtual void  v74(); virtual void  v78();
    virtual void  v7c();
    virtual void  v80(); virtual void  v84();
    virtual void  v88(); virtual void  v8c();
    virtual void  v90(); virtual void  v94();
    virtual void  v98();
    virtual void  v9c(); virtual void  va0();
    virtual void  va4();
    virtual void* va8();
    virtual void  vac(); virtual void  vb0();
    virtual void  vb4(); virtual void  vb8();
    virtual void  vbc(); virtual void  vc0();
    virtual void  vc4(); virtual void  vc8();
    virtual void  vcc(void** outBegin);
    virtual void  vd0(void** outEnd);
    virtual void  vd4(); virtual void  vd8();
    virtual void  vdc(); virtual void  ve0();
    virtual void  ve4();
    virtual void  ve8(void* p);
    virtual void  vec();
    virtual void* vf0(int id, int b);
    virtual void  vf4(); virtual void  vf8();
    virtual void  vfc();
    virtual void  v100();
    virtual void  v104(void* p);
    virtual void  v108(void* p);
};

struct IWinButton {
    virtual void b00(); virtual void b04(); virtual void b08();
    virtual void b0c(); virtual void b10(); virtual void b14();
    virtual void b18(); virtual void b1c(); virtual void b20();
    virtual void b24();
    virtual void b28(int a, int b);
};

// Refcounted interface whose Release lives at vtable+4.
struct IRef4 {
    virtual void q00();
    virtual void Release();
};

// Refcounted interface whose AddRef/Release live at vtable+4/+8.
struct IRef8 {
    virtual void r00();
    virtual void AddRef();
    virtual void Release();
};

// Refcounted interface whose AddRef/Release live at vtable+0/+4.
struct IRef0 {
    virtual void AddRef();
    virtual void Release();
};

// Generic payload object; slots used by the message handlers.
struct IObject {
    virtual void  o00(); virtual void  o04(); virtual void  o08();
    virtual void* o0c(u32 id);
    virtual void  o10();
    virtual void  o14(int a, void* b);
    virtual void  o18();
    virtual int   o1c();
    virtual void  o20(); virtual void  o24();
    virtual int   o28(int a, int b);
    virtual int   o2c();
    virtual int   o30();
};

struct IMessageServer {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10();
    virtual int  s14(int a, int b, int c);
};

// ---------------------------------------------------------------- collaborators
struct cPlayerCityMusicConfig;
struct cPlayerCityMusic;
struct cCityMusicNoteEditor;
struct cCityMusicLoadSave;

struct cSPUILayout {
    IWinNode* FindWindowByID(u32 id, int b);                        // 0x008105b0 (ret 8)
    bool      Init(const void* key, int b, u32 id);                 // 0x008120d0 (ret 0xc)
    bool      IsVisible();                                          // 0x00810070
    void      SetVisibility(int b);                                 // 0x00810590 (ret 4)
    void      SetReloadCallback(void (*cb)(void*, cSPUILayout*, char), void* ctx); // 0x00810090
    void      Shutdown(u32 b);                                      // 0x00811ad0 (ret 4)
    cSPUILayout* ctor();                                            // 0x00810000
};

struct cWindowPulse : IRef4 {
    void SetWindow(void* pWindow);                                  // 0x00e9fe90
};

// EASTL 3-pointer vector of 4-byte elements.
struct PulseVec {
    void* mpBegin;   // +0x00
    void* mpEnd;     // +0x04
    void* mpCap;     // +0x08

    ~PulseVec();                                                    // 0x00ea0e60
    void insert(void* pos, u32 n, void* value);                     // 0x00ea1220 (ret 0xc)
    void erase(void* first, void* last);                            // 0x00e25bd0
};

struct cPlayerCityMusicConfig {
    void* mpVtbl;              // +0x00 (editor+0x10)
    int   mField04;            // +0x04
    int   mField08;            // +0x08
    int   mNumLogReporters;    // +0x0c (editor+0x1c)
    int   mField10;            // +0x10
    int   mField14;
    int   mField18;
    int   mField1c;
    int   mField20;
    int   mField24;
    int   mField28;
    int   mField2c;

    void  ctor();                                                   // 0x00eb19e0
    bool  Reload(ReloadArgs v);                                     // 0x00eb14c0 (12-byte arg)
};

struct cPlayerCityMusic {
    char* mpNotesBegin;        // +0x08 (note vector begin)
    char* mpNotesEnd;          // +0x0c (note vector end)

    int NoteCount() { return (int)((mpNotesEnd - mpNotesBegin) >> 2); }

    void PlayMelody(int b);                                         // 0x00eaceb0 (ret 4)
    void AddUndoState();                                            // 0x00eb1170
    void RemoveNote(int index);                                     // 0x00eac??
    void PlayNote(int index);                                       // 0x00eac??
    void Undo();                                                    // 0x00eb0c30
    void Redo();                                                    // 0x00eb0c70
    char SelectInstrument(int index);                               // 0x00eace30 (ret 4)
    char SelectRhythm(int index);                                   // 0x00eacdb0 (ret 4)
    void SelectAmbience(int id, int* outIndex);                     // 0x00eadd60 (ret 8)
    void DeselectAmbience(int id, int* outIndex, int* outFlag);     // 0x00eae0f0 (ret 0xc)
    void FUN_00eb0120();                                            // 0x00eb0120
    void FUN_00eb0460();                                            // 0x00eb0460
    void FUN_00ead090(int mode, float value);                       // 0x00ead090 (ret 8)
};

struct cCityMusicNoteEditor {
    void LoopMelody();                                              // 0x00ea3120
    void RedrawMelody(bool selected);                               // 0x00ea3??
    void FUN_00ea3ed0();                                            // 0x00ea3ed0
    void FUN_00ea3f10();                                            // 0x00ea3f10
    bool FUN_00ea4250(cSPUILayout* layout, int b);                  // 0x00ea4250 (ret 8)
    cCityMusicNoteEditor* ctor(cPlayerCityMusicConfig* cfg);        // 0x00ea3c20 (ret 4)
};

struct cCityMusicLoadSave {
    bool Init();                                                    // 0x00ea2310
    void Load();                                                    // 0x00ea20a0
    void FUN_00ea26f0();                                            // 0x00ea26f0
    void FUN_00ea2a60();                                            // 0x00ea2a60
    cCityMusicLoadSave* ctor();                                     // 0x00ea2170
};

struct Connector {
    void* mpField00;  // +0x00
    void* mpField04;  // +0x04
    void* mpField08;  // +0x08
    void* mpField0c;  // +0x0c
    void* mpField10;  // +0x10
    void Init(void* server, void* handler, void* key, int mode);    // 0x004db620 (ret 0x10)
};

struct ImageEntry { int m0, m4, m8; };

// ---------------------------------------------------------------- the editor
struct cCityMusicEditor {
    void* mpVtbl_00;                  // +0x00
    void* mpVtbl_04;                  // +0x04
    void* mpVtbl_08;                  // +0x08
    void* mpField0c;                  // +0x0c
    cPlayerCityMusicConfig mConfig;   // +0x10
    void* mpArray40;                  // +0x40
    char  mPad44[0x10];               // +0x44..+0x54
    void* mpArray54;                  // +0x54
    char  mPad58[0x6c];               // +0x58..+0xc4
    ImageEntry* mpImages[3];          // +0xc4,+0xc8,+0xcc
    void* mpFieldD0;                  // +0xd0
    void* mpFieldD4;                  // +0xd4
    cPlayerCityMusic* mpPlayer;       // +0xd8
    cSPUILayout* mpLayout;            // +0xdc
    cCityMusicNoteEditor* mpNoteEditor; // +0xe0
    PulseVec mPulses;                 // +0xe4
    char  mPadF0[8];                  // +0xf0..+0xf8
    cCityMusicLoadSave* mpLoadSave;   // +0xf8
    void* mpFieldFc;                  // +0xfc
    Connector mHandler;               // +0x100

    cWindowPulse* PulseAt(int i) { return ((cWindowPulse**)mPulses.mpBegin)[i]; }

    // methods declared out of line elsewhere
    unsigned DoMessage(int unused, struct Message* msg);             // 0x00ea0910 (ret 8)
    void     SetVisibility(int b);                                   // 0x00ea0010
    void     Update();                                               // 0x00ea0200
    void     Redraw();                                               // 0x00ea0460
    void     FUN_00e9ffb0(void* p);                                  // 0x00e9ffb0 (ret 4)
    void     Shutdown();                                             // 0x00ea13e0
    char     Init();                                                 // 0x00ea17b0
};

// Message payload passed to DoMessage: ids live at +0x08 and +0x0c.
struct Message {
    IObject* mpObject;   // +0x00
    int      mField04;   // +0x04
    int      mType;      // +0x08
    int      mId;        // +0x0c
    int      mField10;   // +0x10
    int      mSelected;  // +0x14
    int      mField18;   // +0x18
};

// IHandler subobject at editor+4: the PDB HandleMessage override.
struct cCityMusicHandler {
    cCityMusicEditor*     Editor() { return (cCityMusicEditor*)((char*)this - 4); }
    cPlayerCityMusicConfig* Config() { return (cPlayerCityMusicConfig*)((char*)this + 0x0c); }
    char HandleMessage(int id, Message* msg);                        // 0x00ea1710 (ret 8)
};

struct cCityMusicLargeAssetView {
    char DoMessage(int unused, Message* msg);                        // 0x00ea18c0 (ret 8)
};

struct cPlayerCivilization {
    char      mPad[0x274];
    IObject*  mpMusic;   // +0x274
};

struct cGameNounManager {
    void* GetPlayerCivilization();                                   // 0x00b25fb0
};

// ---------------------------------------------------------------- externs
extern "C" void* operator_new(u32 n, const char* tag, int a, int b, const char* file, int line);
extern "C" void  operator_delete_array(void* p);
extern "C" void* memcpy(void* d, const void* s, u32 n);
extern "C" void* memmove(void* d, const void* s, u32 n);

extern "C" void  RemoveHandler(void* h, void* a, void* b, void* c, void* d);   // 0x00571db0
extern "C" void* MessageServer();                                             // 0x0067dcc0
extern "C" void  PlayEditorSound(u32 id, u32 a, float vol, int b);             // 0x00?? (EditorUtils)
extern "C" char  CreateImageFromResource2(void* a, void** b, char c, int d, int e); // 0x00806230
extern "C" void  FUN_00eaf510(void* out12);                                   // 0x00eaf510
extern "C" float FUN_00e9ff20(int a, int b);                                  // 0x00e9ff20
extern "C" IWinButton* InterfaceCastButton(void* p);                          // 0x005ca960
extern "C" void* NounManager();                                               // 0x00b3d300

extern char vtbl_CityMusicEditor_00[];   // 0x014871f8
extern char vtbl_CityMusicEditor_04[];   // 0x014871f0
extern char vtbl_CityMusicEditor_08[];   // 0x014871e0
extern char vtbl_Reporter_00[];          // 0x014871c4
extern char vtbl_Reporter_04[];          // 0x014871b4
extern char vtbl_ContentValidationSummarizer[];
extern char vtbl_PaintSystem[];
extern char vtbl_ITracerBase[];
extern char DAT_015a8ba8;                // layout resource key
extern char DAT_0148730c;                // handler key
extern const u32 DAT_01487198[6];        // editor sound ids
extern void* DAT_01440aec;               // SP_STL_Sound allocator

// eastl::vector<cWindowPulse*> destructor.
// @ 0x00ea0e60
PulseVec::~PulseVec()
{
    cWindowPulse** p = (cWindowPulse**)mpBegin;
    cWindowPulse** e = (cWindowPulse**)mpEnd;
    while (p < e) {
        cWindowPulse* item = *p;
        if (item)
            item->Release();
        ++p;
    }
    if (mpBegin)
        operator_delete_array(mpBegin);
}

// vector<cWindowPulse*>::insert(pos, n, value) - grow (or shift) then fill.
// @ 0x00ea1220
void PulseVec::insert(void* pos, u32 n, void* value)
{
    u32 spare = (u32)((char*)mpCap - (char*)mpEnd) >> 2;
    if (spare < n) {
        u32 len = (u32)((char*)mpEnd - (char*)mpBegin) >> 2;
        u32 newCap = len * 2;
        if (len == 0)
            newCap = 1;
        u32 want = len + n;
        if (want > newCap)
            newCap = want;
        void* dst = newCap
            ? operator_new(newCap * 4, "Simulator", 0, 0,
                           "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                           0xd1)
            : 0;
        char* out = (char*)dst;
        char* first = (char*)mpBegin;
        char* at = (char*)pos;
        u32 headBytes = (u32)(at - first);
        memcpy(out, first, headBytes);
        out += headBytes;
        char* fillEnd = out + n * 4;
        u32* q = (u32*)out;
        while ((char*)q != fillEnd) {
            *(u32*)q = *(u32*)value;
            q += 1;
        }
        out = fillEnd;
        u32 tailBytes = (u32)((char*)mpEnd - at);
        memcpy(out, at, tailBytes);
        out += tailBytes;
        if (mpBegin)
            operator_delete_array(mpBegin);
        mpBegin = dst;
        mpEnd = out;
        mpCap = (char*)dst + newCap * 4;
        return;
    }
    if (n == 0)
        return;
    char* at = (char*)pos;
    char* oldEnd = (char*)mpEnd;
    u32 tailBytes = (u32)(oldEnd - at);
    memmove(oldEnd + n * 4, at, tailBytes);
    u32* q = (u32*)at;
    u32* fillEnd = q + n;
    while (q != fillEnd) {
        *(u32*)q = *(u32*)value;
        q += 1;
    }
    mpEnd = oldEnd + n * 4;
}

// cCityMusicEditor constructor.
// @ 0x00ea0ea0
cCityMusicEditor* __fastcall FUN_00ea0ea0(cCityMusicEditor* self)
{
    self->mpVtbl_00 = (void*)vtbl_CityMusicEditor_00;
    self->mpVtbl_04 = (void*)vtbl_CityMusicEditor_04;
    self->mpVtbl_08 = (void*)vtbl_CityMusicEditor_08;
    self->mpField0c = 0;
    self->mConfig.ctor();

    self->mpPlayer = 0;
    self->mpLayout = 0;
    self->mpNoteEditor = 0;
    self->mPulses.mpBegin = 0;
    self->mPulses.mpEnd = 0;
    self->mPulses.mpCap = 0;
    self->mpLoadSave = 0;
    self->mpFieldFc = 0;
    self->mpFieldD0 = 0;
    self->mpFieldD4 = 0;
    self->mpArray40 = 0;
    self->mpArray54 = 0;
    self->mpImages[0] = 0;
    self->mpImages[1] = 0;
    self->mpImages[2] = 0;
    self->mHandler.mpField00 = 0;
    self->mHandler.mpField04 = 0;
    self->mHandler.mpField08 = 0;
    self->mHandler.mpField0c = 0;
    self->mHandler.mpField10 = 0;

    {
        void* mem = operator_new(0x18, "Audio", 0, 0, 0, 0);
        cSPUILayout* layout = mem ? ((cSPUILayout*)mem)->ctor() : 0;
        cSPUILayout* old = self->mpLayout;
        if (layout != old) {
            if (layout)
                ((IRef8*)layout)->AddRef();
            self->mpLayout = layout;
            if (old)
                ((IRef8*)old)->Release();
        }
    }
    {
        void* mem = operator_new(0x34, "Audio", 0, 0, 0, 0);
        cCityMusicLoadSave* ls = mem ? ((cCityMusicLoadSave*)mem)->ctor() : 0;
        cCityMusicLoadSave* old = self->mpLoadSave;
        if (ls != old) {
            if (ls)
                ((IRef8*)ls)->AddRef();
            self->mpLoadSave = ls;
            if (old)
                ((IRef8*)old)->Release();
        }
    }
    {
        void* mem = operator_new(0xc8, "Audio", 0, 0, 0, 0);
        cCityMusicNoteEditor* ne = mem ? ((cCityMusicNoteEditor*)mem)->ctor(&self->mConfig) : 0;
        cCityMusicNoteEditor* old = self->mpNoteEditor;
        if (ne != old) {
            if (ne)
                ((IRef0*)ne)->AddRef();
            self->mpNoteEditor = ne;
            if (old)
                ((IRef0*)old)->Release();
        }
    }
    return self;
}

// Rebuild the editable window images after a layout reload.
// @ 0x00ea1060
void __fastcall FUN_00ea1060(cCityMusicEditor* self)
{
    static const u32 s_ids[3] = { 0x41914e9, 0x41914f0, 0x41914f3 };
    for (int k = 0; k < 3; ++k) {
        IWinNode* w = self->mpLayout->FindWindowByID(s_ids[k], 1);
        void* it = 0;
        void* end = 0;
        w->vcc(&it);
        w->vd0(&end);
        while (it != end) {
            IWinNode* node = *(IWinNode**)it;
            IWinNode* created = (IWinNode*)node->vf0(0x5bfe9d0, 0);
            ImageEntry* images = self->mpImages[k];
            if (created && images) {
                int idx = node->v1c();
                ImageEntry* e = &images[idx - 1];
                void* image = 0;
                CreateImageFromResource2(e, &image, 0, -1, -1);
                IObject* obj = (IObject*)created->va8();
                if (obj)
                    obj = (IObject*)obj->o0c(0x103c1908);
                if (obj)
                    obj->o14(0, image);
                if (image)
                    ((IRef4*)image)->Release();
            }
            it = *(void**)it;
        }
    }
    self->mpNoteEditor->FUN_00ea3f10();
    self->Redraw();
    IWinNode* w = self->mpLayout->FindWindowByID(0x45958e0, 1);
    w->v104(self);
}

// Layout reload callback.
// @ 0x00ea1200
void FUN_00ea1200(void* p, cSPUILayout* layout, char flag)
{
    if (flag)
        FUN_00ea1060((cCityMusicEditor*)p);
}

// @ 0x00ea13e0
void cCityMusicEditor::Shutdown()
{
    SetVisibility(0);
    if (mHandler.mpField00) {
        RemoveHandler(mHandler.mpField00, mHandler.mpField04, mHandler.mpField08,
                      mHandler.mpField0c, mHandler.mpField10);
        mHandler.mpField00 = 0;
    }
    mPulses.erase(mPulses.mpBegin, mPulses.mpEnd);
    mpNoteEditor->FUN_00ea3ed0();
    mpLoadSave->FUN_00ea26f0();
    mpLayout->Shutdown(1);
}

// Destructor body.
// @ 0x00ea1470
void __fastcall FUN_00ea1470(cCityMusicEditor* self)
{
    self->mpVtbl_00 = (void*)vtbl_CityMusicEditor_00;
    self->mpVtbl_04 = (void*)vtbl_CityMusicEditor_04;
    self->mpVtbl_08 = (void*)vtbl_CityMusicEditor_08;
    self->Shutdown();

    if (self->mHandler.mpField00) {
        RemoveHandler(self->mHandler.mpField00, self->mHandler.mpField04,
                      self->mHandler.mpField08, self->mHandler.mpField0c,
                      self->mHandler.mpField10);
        self->mHandler.mpField00 = 0;
    }
    if (self->mpLoadSave) {
        ((IRef8*)self->mpLoadSave)->Release();
    }
    self->mPulses.~PulseVec();
    if (self->mpNoteEditor)
        ((IRef0*)self->mpNoteEditor)->Release();
    if (self->mpLayout)
        ((IRef8*)self->mpLayout)->Release();
    if (self->mpPlayer)
        ((IRef4*)self->mpPlayer)->Release();
    if (self->mpFieldD4)
        ((IRef4*)self->mpFieldD4)->Release();
    if (self->mpFieldD0)
        ((IRef4*)self->mpFieldD0)->Release();
    if (self->mpArray54)
        operator_delete_array(self->mpArray54);
    if (self->mpArray40)
        operator_delete_array(self->mpArray40);
    self->mpVtbl_08 = (void*)vtbl_ContentValidationSummarizer;
    self->mpVtbl_04 = (void*)vtbl_PaintSystem;
    self->mpVtbl_00 = (void*)vtbl_ITracerBase;
}

// Re-create the per-vehicle pulse reporters.
// @ 0x00ea1570
void __fastcall FUN_00ea1570(cCityMusicEditor* self)
{
    u32 count = (u32)((char*)self->mPulses.mpEnd - (char*)self->mPulses.mpBegin) >> 2;
    for (u32 i = 0; i < count; ++i) {
        cWindowPulse* item = ((cWindowPulse**)self->mPulses.mpBegin)[i];
        IWinNode* w = (IWinNode*)((char*)item + 0x0c);  // item window interface
        if (w) {
            w->v108(item);
            w->v98();
        }
        if (w) {
            *((IWinNode**)((char*)item + 0x0c)) = 0;
            ((IRef4*)w)->Release();
        }
        w = (IWinNode*)((char*)item + 0x0c);
        if (w) {
            w->v104(item);
            w->v98();
            IWinNode* owner = (IWinNode*)w->v10();
            owner->ve8(w);
        }
    }

    u32 want = (u32)self->mConfig.mNumLogReporters + 2;
    u32 have = (u32)((char*)self->mPulses.mpEnd - (char*)self->mPulses.mpBegin) >> 2;
    if (have < want) {
        u32 zero = 0;
        self->mPulses.insert(self->mPulses.mpEnd, want - have, &zero);
    } else {
        self->mPulses.erase((char*)self->mPulses.mpBegin + want * 4, self->mPulses.mpEnd);
    }

    for (u32 i = 0; i < want; ++i) {
        void* mem = operator_new(0x14, "Audio", 0, 0, 0, 0);
        cWindowPulse* created;
        if (!mem) {
            created = 0;
        } else {
            void** p = (void**)mem;
            p[0] = (void*)vtbl_Reporter_00;
            p[1] = (void*)vtbl_Reporter_04;
            p[2] = 0;
            p[3] = 0;
            p[4] = (void*)0x3f800000;
            created = (cWindowPulse*)mem;
        }
        cWindowPulse* old = ((cWindowPulse**)self->mPulses.mpBegin)[i];
        if (created != old) {
            if (created)
                ((IRef0*)created)->AddRef();
            ((cWindowPulse**)self->mPulses.mpBegin)[i] = created;
            if (old)
                ((IRef4*)old)->Release();
        }
    }
    FUN_00ea1060(self);
}

// @ 0x00ea1710  (this == editor+4)
char cCityMusicHandler::HandleMessage(int id, Message* msg)
{
    if (id == 0xf62def) {
        ReloadArgs v;
        v.a = msg->mField18;
        v.b = msg->mType;
        v.c = msg->mField10;
        char ok = Config()->Reload(v) ? 1 : 0;
        if (ok)
            FUN_00ea1570(Editor());
        return ok;
    }
    if (id == 0x510b72f) {
        if ((void*)Editor()->mpPlayer != (void*)msg) {
            return 0;
        }
        Editor()->Redraw();
        return 1;
    }
    return 0;
}

// @ 0x00ea17b0
char cCityMusicEditor::Init()
{
    cGameNounManager* nouns = (cGameNounManager*)NounManager();
    cPlayerCivilization* civ = (cPlayerCivilization*)nouns->GetPlayerCivilization();
    if (!civ->mpMusic)
        return 0;
    void* music = civ->mpMusic->o0c(0x4223298);
    if (!music)
        return 0;
    if (!mpLayout->Init(&DAT_015a8ba8, 1, 0x5b598fa))
        return 0;
    if (!mpNoteEditor->FUN_00ea4250(mpLayout, 1))
        return 0;
    if (!mpLoadSave->Init())
        return 0;
    FUN_00e9ffb0(music);
    mpLayout->SetVisibility(0);
    mHandler.Init(MessageServer(), (void*)((char*)this + 4), &DAT_0148730c, 2);
    mpLayout->SetReloadCallback(FUN_00ea1200, this);
    FUN_00ea1570(this);
    return 1;
}

// @ 0x00ea18c0
char cCityMusicLargeAssetView::DoMessage(int unused, Message* msg)
{
    if (msg->mType == 0x287259f6 && msg->mId == 0x74174c59) {
        IMessageServer* server = (IMessageServer*)MessageServer();
        server->s14(0x14ac4938, 0, 0);
        return 1;
    } else {
        return 0;
    }
}

// @ 0x00ea0910
unsigned cCityMusicEditor::DoMessage(int unused, Message* msg)
{
    unsigned type = (unsigned)msg->mType;
    if (type < 0x18) {
        if (type != 0x17) {
            if (type == 0xc) {
                if (mpLayout->IsVisible()) {
                    Update();
                    return 1;
                }
            } else {
                if (type != 0xd)
                    return 0;
                if (mpLayout->IsVisible()) {
                    for (unsigned off = 0; off < 0x18; off += 4)
                        PlayEditorSound(DAT_01487198[off / 4], 0xdb83a083, 1.0f, 0);
                    return 1;
                }
            }
            return 1;
        }

        unsigned id = (unsigned)msg->mId;
        if (id < 0x4ed09b9) {
            if (id == 0x4ed09b8) {
                mpPlayer->FUN_00eb0120();
                mpNoteEditor->LoopMelody();
                mpPlayer->PlayMelody(0);
                mpPlayer->AddUndoState();
                return 1;
            }
            if (id < 0x419154e) {
                if (id == 0x419154d) {
                    mpPlayer->RemoveNote(mpPlayer->NoteCount() - 1);
                    mpNoteEditor->LoopMelody();
                    mpPlayer->AddUndoState();
                    return 1;
                }
                if (id == 0x4191520) {
                    mpPlayer->PlayMelody(0);
                    return 1;
                }
                if (id == 0x4191529) {
                    u8 local[12];
                    FUN_00eaf510(local);
                    mpNoteEditor->LoopMelody();
                    mpPlayer->PlayNote(mpPlayer->NoteCount() - 1);
                    mpPlayer->AddUndoState();
                    return 1;
                }
            } else if (id == 0x456ff90) {
                mpPlayer->FUN_00eb0460();
                Redraw();
                mpPlayer->PlayMelody(0);
                mpPlayer->AddUndoState();
                return 1;
            }
        } else if (id < 0x5023c01) {
            if (id == 0x5023c00) {
                mpLoadSave->FUN_00ea2a60();
                return 1;
            }
            if (id == 0x4f8c2c3) {
                mpPlayer->Undo();
                mpPlayer->PlayMelody(0);
                return 1;
            }
            if (id == 0x4f8c2c7) {
                mpPlayer->Redo();
                mpPlayer->PlayMelody(0);
                return 1;
            }
        } else if (id == 0x5023c10) {
            mpLoadSave->Load();
            return 1;
        }
        return 0;
    }

    if (type == 0x18) {
        unsigned id = (unsigned)msg->mId;
        int which = msg->mpObject->o1c();
        bool selected = msg->mSelected != 0;
        if (id < 0x419151d) {
            if (id == 0x419151c) {
                bool ok = mpPlayer->SelectInstrument(which) != 0;
                if (!ok) {
                    PulseAt(1)->SetWindow(0);
                    IWinButton* button = InterfaceCastButton(msg->mpObject);
                    button->b28(4, 0);
                } else {
                    mpPlayer->PlayMelody(0);
                    PulseAt(1)->SetWindow(msg->mpObject);
                }
                mpNoteEditor->RedrawMelody(selected);
                mpPlayer->AddUndoState();
                return 1;
            }
            if (id == 0x419150a) {
                if (msg->mSelected != 0) {
                    int idx = 0;
                    int flag = 0;
                    mpPlayer->DeselectAmbience(which, &idx, &flag);
                    PulseAt(idx + 2)->SetWindow(msg->mpObject);
                    if (flag != 0) {
                        IWinNode* w = mpLayout->FindWindowByID(0x41914e9, 1);
                        IWinButton* button = InterfaceCastButton(w->vf0(flag, 0));
                        button->b28(4, 0);
                        mpPlayer->AddUndoState();
                        return 0;
                    }
                } else {
                    int idx = 0;
                    mpPlayer->SelectAmbience(which, &idx);
                    PulseAt(idx + 2)->SetWindow(0);
                }
                mpPlayer->AddUndoState();
                return 1;
            }
            if (id == 0x4191515) {
                if (mpPlayer->SelectRhythm(which) != 0) {
                    PulseAt(0)->SetWindow(msg->mpObject);
                    mpPlayer->AddUndoState();
                    return 1;
                }
                PulseAt(0)->SetWindow(0);
                IWinButton* button = InterfaceCastButton(msg->mpObject);
                button->b28(4, 0);
                mpPlayer->AddUndoState();
                return 0;
            }
        } else if (id == 0x4ee92a8) {
            // SetSoundProperty(msg)
            return 1;
        }
        return 0;
    }

    if (type == 0xef00a884) {
        int id = msg->mId;
        IObject* obj = 0;
        if (msg->mpObject)
            obj = (IObject*)msg->mpObject->o0c(0xf00a8a0);
        int a = obj->o30();
        int b = obj->o28(a, 0);
        float f = FUN_00e9ff20(msg->mSelected, b);
        if (id == 0x4d83000) {
            mpPlayer->FUN_00ead090(1, f);
            return 1;
        }
        if (id == 0x4d83008) {
            mpPlayer->FUN_00ead090(2, f);
            return 1;
        }
        if (id == 0x4d83010) {
            mpPlayer->FUN_00ead090(0, f);
            return 1;
        }
    }
    return 0;
}
