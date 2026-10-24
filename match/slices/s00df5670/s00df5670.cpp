// Slice s00df5670: UI::cDownloadDialog methods (0x00DF5670) plus small free helpers.
// Layout inferred from the retail constructor at 0x00DF5940 (object is larger than the PDB layout):
//   +0x00  vtable ptr (UI::cDownloadDialog)
//   +0x04  vtable ptr (second base / Resource::Async)
//   +0x08  ptr  eastl::vector<entry> begin  (stride 0xbc)
//   +0x0c  ptr  eastl::vector<entry> end
//   +0x10  float timer base   (GetElapsedSeconds stamp)
//   +0x14  float timer period
//   +0x18  bool  active
//   +0x19  bool  one-shot latch
//   +0x1c..+0x28  progress-window float block
//   +0x2c  bool  paused flag
//   +0x30  AutoRefCount<IWinText> (label)
//   +0x34..+0x40  Vec4 (window target rect)
//   +0x44  float 0..1 progress
//   +0x48  ptr   current entry
//   +0x4c  int   entry count
//   +0x50  int   entry index
//   +0x54  cSPUILayout (dialog layout)
// Callees are masked relocations: declarations only need the right calling convention and argument
// sizes (arity taken from each callee's `ret N`).
// Flags: /O2 /MD /Gy /TP /arch:SSE.
#include "types.h"
#include <math.h>

typedef unsigned int uint;

struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };

// ---- collaborators ---------------------------------------------------------------------------------
struct Obj;

struct cSPUILayout;

// cSPUILayout: opaque layout object; all thiscall members live on it.
struct cSPUILayout {
    void* FindWindowByID(uint id, int b);              // 0x008105b0 (ret 8) -> IWinNode*
    bool  Init(const void* key, bool b, uint id);      // 0x008120d0 (ret 0xc)
    void  Shutdown(uint b);                            // 0x00811ad0 (ret 4)
    void  dtor();                                      // 0x00811fe0
    void  ctor();                                      // 0x00810000
};

// IWinNode: UI window node. Slots used here: 0x34/0x38 rect getters, 0x5c/0x60 dialog slots,
// 0x64 position setter, 0x7c visibility, 0x80 text, 0x104 proc attach, 0x108 detach.
struct IWinNode {
    virtual void  v00(); virtual void  v04();
    virtual void  v08();
    virtual void  v0c(int b);
    virtual void  v10(); virtual void  v14();
    virtual void  v18(); virtual int   v1c();
    virtual void  v20(); virtual void  v24();
    virtual void  v28(); virtual void  v2c();
    virtual void  v30(); virtual Vec4* v34();
    virtual Vec4* v38();
    virtual void  v3c(); virtual void  v40();
    virtual void  v44(); virtual void  v48();
    virtual void  v4c(); virtual void  v50();
    virtual void  v54(); virtual void  v58();
    virtual void  v5c(void* p);
    virtual void  v60(int a, int b);
    virtual void  v64(float a, float b);
    virtual void  v68(); virtual void  v6c();
    virtual void  v70(); virtual void  v74();
    virtual void  v78();
    virtual void  v7c(int a, int b);
    virtual bool  v80(const wchar_t* s);    virtual void  v84(); virtual void  v88();
    virtual void  v8c(); virtual void  v90();
    virtual void  v94(); virtual void  v98();
    virtual void  v9c(); virtual void  va0();
    virtual void  va4(); virtual void  va8();
    virtual void  vac(); virtual void  vb0();
    virtual void  vb4(); virtual void  vb8();
    virtual void  vbc(); virtual void  vc0();
    virtual void  vc4(); virtual void  vc8();
    virtual void  vcc(); virtual void  vd0();
    virtual void  vd4(); virtual void  vd8();
    virtual void  vdc(); virtual void  ve0();
    virtual void  ve4(); virtual void  ve8();
    virtual void  vec();
    virtual void* vf0(int a, int b, float* p);
    virtual void  vf4(); virtual void  vf8();
    virtual void  vfc();
    virtual void  v100();
    virtual void  v104(void* p);
    virtual void  v108(void* p);
};

// Simple refcounted object (vtable[0] = addref, vtable[4] = release, vtable[0xc](int) = destroy).
struct IRef {
    virtual void  r00(); virtual void  r04();
    virtual void  r08();
    virtual void  r0c(int b);
    virtual void  r10();
    virtual void  r14(int a, int b, int c);
};

struct MsgObj {
    virtual void  m00(); virtual void  m04();
    virtual void  m08(); virtual void  m0c();
    virtual void  m10();
    virtual int   m14(int a, int b, int c);
};

// cAudio system (vtable[0x20]).
struct AudioSys {
    virtual void  a00(); virtual void  a04(); virtual void  a08(); virtual void  a0c();
    virtual void  a10(); virtual void  a14(); virtual void  a18(); virtual void  a1c();
    virtual void  a20();
};

struct cString {
    cString();                                          // 0x006b5060
    ~cString();                                         // 0x006b5240
    bool Load(uint a, uint b, const wchar_t* s);        // 0x006b54b0 (ret 0xc)
    const wchar_t* GetText();                           // 0x006b55c0
};

// Free functions.
void  __cdecl SPUIHelpers_EndModal(void* p, int a, int b);              // 0x00809c50 (cdecl)
float __cdecl SPUIHelpers_GetElapsedSeconds();                          // 0x00805080
void* __cdecl SPUIHelpers_GetMainWindowArea(Vec4* out);                 // 0x00805ea0 (ret 4)
void  __cdecl FUN_00808230(void* p, float* f);                          // 0x00808230 (ret 8)
Obj*  __cdecl SP_MessageServer();                                       // 0x0067dcc0
Obj*  __cdecl SP_App();                                                 // 0x0067dd10
Obj*  __cdecl EA_Audio_GetSystemAT();                                   // 0x00a206f0
Obj*  __cdecl SP_StarManager();                                         // 0x00b3d2a0
void  __cdecl FUN_00df5430(int b);                                      // 0x00df5430 (ret 4)
float __cdecl FUN_00df54f0(float f);                                    // 0x00df54f0 (ret 4)
void  __cdecl FUN_00df5610(float f);                                    // 0x00df5610 (ret 4)
void  __cdecl FUN_00de3c70(void* p, float* a, float* b);                // 0x00de3c70 (ret 0xc)
void  __cdecl FUN_00e00670(uint a, void* b);                            // 0x00e00670 (ret 8)
void  __cdecl FUN_00e00650(uint a, void* b);                            // 0x00e00650 (ret 8)
void  __cdecl FUN_00de86d0(uint a, int b);                              // 0x00de86d0 (ret 8)
void  __cdecl FUN_00dde570(void* p);                                    // 0x00dde570
void  __stdcall SP_cSPUISpace_KillSetiEffects(Obj* a, int flag);        // 0x00435ed0 (ret 8)
bool  __cdecl FUN_005f2350(const float* v);                             // 0x005f2350
void  __cdecl FUN_00e20860(void* p);                                    // 0x00e20860
Obj*  __cdecl FUN_00dd9190();                                           // 0x00dd9190
void  __fastcall FUN_00ddb760(Obj* p);                                  // 0x00ddb760 (this in ecx)
void  __fastcall FUN_00de9ec0(Obj* p);                                  // 0x00de9ec0 (this in ecx)
void  __cdecl QuaternionSlerp(float* out, const float* a, const float* b, float t); // 0x00698b30 (ret 0x10)
char  __cdecl FUN_007c4510(float a, float b, void* c, void* d);        // 0x007c4510 (ret 0x18)
void  __cdecl FUN_007c4180(void* a, float* b);                          // 0x007c4180 (ret 8)
void  __cdecl EA_UTFWin_MultiHeapObject_free(void* p);                  // 0x00951330 (cdecl)
// AutoRefCount<UTFWinControls::IWinText> operator=
struct WinTextRef {
    void* m_p;                                          // +0x00
    WinTextRef& operator=(void* p);                     // 0x00b5f950 (ret 4)
};

extern const float DAT_01486114;   // 0x01486114
extern const float DAT_01485720;   // 0x01485720
extern const float DAT_013fa9c8;   // 0x013fa9c8
extern const float DAT_013eb960;   // 0x013eb960
extern const float DAT_01486110;   // 0x01486110
extern const float DAT_014853e0;   // 0x014853e0
extern const float DAT_01471064;   // 0x01471064
extern float DAT_016a16a4;         // 0x016a16a4
extern float DAT_016a16a8;         // 0x016a16a8
extern const float DAT_016a0e98;   // 0x016a0e98
extern const float DAT_016a0ea8;   // 0x016a0ea8
extern const float DAT_016a0eb8;   // 0x016a0eb8
extern const float DAT_016a0ec8;   // 0x016a0ec8
extern const float DAT_014007f4;   // 0x014007f4
extern uint DAT_016a1848[];        // 0x016a1848 (bitset)
extern char* kGUI;                 // 0x016a1344

// Vtable symbols (opaque; only their addresses matter). Declared as arrays so the
// compiler folds `(void*)sym` into an immediate store of the symbol address.
extern char vtbl_UI_cDownloadDialog_A[];   // 0x0147e9d0
extern char vtbl_UI_cDownloadDialog_B[];   // 0x0147e9b4
extern char vtbl_UI_cDownloadDialog_C[];   // 0x0147ea70
extern char vtbl_UI_cDownloadDialog_D[];   // 0x0147ea54
extern char vtbl_Resource_Async[];         // 0x013fa72c
extern char vtbl_Editor_cEditorResource[]; // 0x013eb938

// ---- locals ----------------------------------------------------------------------------------------
// Random linear congruential (ecx = &_sMathRandom... at 0x1601760).
struct RandomLinCong {
    double next();                                      // 0x009360d0
};
extern RandomLinCong sMathRandom;   // 0x1601760

// =====================================================================================================
// cDownloadDialog (defined out-of-line so every VA can be its own function).
struct cDownloadDialog;

extern "C" cDownloadDialog* DownloadCtor(cDownloadDialog* self);
extern "C" cDownloadDialog* DownloadCtor2(cDownloadDialog* self);

struct cDownloadDialog {
    void* mpVtbl_00;        // +0x00
    void* mpVtbl_04;        // +0x04  Resource::Async
    void* mpVal_08;         // +0x08  (vector begin for the +0x08/+0x0c vector view)
    union { void* mpNode_0c; void* m_entryEnd; cSPUILayout* mpLayout_0c; }; // +0x0c
    float m_timerBase;      // +0x10
    float m_timerPeriod;    // +0x14
    char  m_active;         // +0x18
    char  m_latch;          // +0x19
    char pad1[0x1c - 0x1a];
    float m_p1c;            // +0x1c
    float m_p20;            // +0x20
    union { float m_p24; void* mpNode_24; }; // +0x24
    float m_p28;            // +0x28
    char  m_paused;         // +0x2c
    char pad2[0x30 - 0x2d];
    void* m_label;          // +0x30 AutoRefCount<IWinText>
    float m_r34;            // +0x34
    float m_r38;            // +0x38
    float m_r3c;            // +0x3c
    float m_r40;            // +0x40
    float m_progress;       // +0x44
    void* m_entry;          // +0x48
    int   m_count;          // +0x4c
    int   m_index;          // +0x50
    char  m_layout[0x08];   // +0x54 cSPUILayout

    cSPUILayout* Layout() { return (cSPUILayout*)((char*)this + 0x54); }
    cSPUILayout* LayoutB() { return (cSPUILayout*)((char*)this + 0x0c); }

    void   FUN_00df5670(char b);        // 0x00df5670 (ret 4)
    void   FUN_00df57d0(int b);         // 0x00df57d0 (ret 4)
    bool   FUN_00df5830(void* retaddr); // 0x00df5830 (ret 4)
    void   FUN_00df58f0();              // 0x00df58f0
    bool   FUN_00df59c0(void* p);       // 0x00df59c0 (ret 4)
    void   FUN_00df5aa0(char b);        // 0x00df5aa0 (ret 4)
    bool   FUN_00df5ac0(int b);         // 0x00df5ac0 (ret 4)
    void   FUN_00df5cd0();              // 0x00df5cd0
    void*  FUN_00df5d30(int b);         // 0x00df5d30 (ret 4)
    bool   FUN_00df5d90(void* a, void* b); // 0x00df5d90 (ret 8)
    void   FUN_00df6040();              // 0x00df6040
    bool   FUN_00df6140(Obj* a, float x, float y); // 0x00df6140 (ret 0xc)
    void   FUN_00df6330(uint id, void* p, uint b); // 0x00df6330 (ret 8)
    int    FUN_00df64c0(float a, float b, float c); // 0x00df64c0 (ret 0xc)
    void   FUN_00df65e0(void* a, void* b, float c); // 0x00df65e0 (ret 0xc)
};

extern cDownloadDialog* gDownload;

// =====================================================================================================
// 0x00DF5670
// @ 0x00df5670
void cDownloadDialog::FUN_00df5670(char b)
{
    m_paused = b;
    if (b == 0) {
        FUN_00df5430(0);
        IWinNode* w = (IWinNode*)Layout()->FindWindowByID(0x5d66f78, 1);
        if (w) {
            cString s;
            s.Load(0xd7f9d626, 0x61f1d7f, L"Pause (PLACEHOLDER)");
            w->v80(s.GetText());
        }
        return;
    }
    cSPUILayout* lay = Layout();
    IWinNode* w = (IWinNode*)lay->FindWindowByID(0x5d2bdf8, 1);
    w->v7c(1, 1);
    w->v7c(2, 1);
    IWinNode* w2 = (IWinNode*)lay->FindWindowByID(0x5006000, 1);
    if (w2) {
        cString s1;
        s1.Load(0xd7f9d626, 0x5ee1440, L"Download Paused (PLACEHOLDER)");
        w2->v80(s1.GetText());
    }
    IWinNode* w3 = (IWinNode*)lay->FindWindowByID(0x5d66f78, 1);
    if (w3) {
        cString s2;
        s2.Load(0xd7f9d626, 0x64bf9e1, L"Resume (PLACEHOLDER)");
        w3->v80(s2.GetText());
    }
}

// 0x00DF57D0
// @ 0x00df57d0
void cDownloadDialog::FUN_00df57d0(int b)
{
    SPUIHelpers_EndModal(mpNode_0c, 0, 1);
    ((IWinNode*)mpNode_0c)->v108(this);
    if (mpNode_0c) {
        IWinNode* p = (IWinNode*)mpNode_0c;
        mpNode_0c = 0;
        p->v04();
    }
    if (m_label) {
        IWinNode* q = (IWinNode*)m_label;
        m_label = 0;
        q->v04();
    }
    Layout()->Shutdown(1);
}

// 0x00DF5830
// @ 0x00df5830
bool cDownloadDialog::FUN_00df5830(void* retaddr)
{
    uint key[3];
    key[0] = 0xf7082241;
    key[1] = 0x0510a95b;
    key[2] = 0x40464100;
    cSPUILayout* lay = (cSPUILayout*)((char*)this + 0x0c);
    if (!lay->Init(key, 1, 0x5b598fa))
        return false;
    IWinNode* w = (IWinNode*)lay->FindWindowByID(0x6383590, 1);
    if (!w) {
        lay->Shutdown(1);
        return false;
    }
    w->v104(this);
    IWinNode* old = *(IWinNode**)((char*)this + 0x24);
    if (w != old) {
        w->v00();
        *(void**)((char*)this + 0x24) = w;
        if (old)
            old->v04();
    }
    IWinNode* w2 = (IWinNode*)lay->FindWindowByID(0x6393e18, 1);
    w2->v80((const wchar_t*)retaddr);
    return true;
}

// 0x00DF58F0
// @ 0x00df58f0
void cDownloadDialog::FUN_00df58f0()
{
    SPUIHelpers_EndModal(mpNode_24, 0, 1);
    ((IWinNode*)mpNode_24)->v108(this);
    if (mpNode_24) {
        IWinNode* p = (IWinNode*)mpNode_24;
        mpNode_24 = 0;
        p->v04();
    }
    LayoutB()->Shutdown(1);
}
// 0x00DF5940 : derived constructor
// @ 0x00df5940
cDownloadDialog* __fastcall cDownloadDialog_ctor_5940(cDownloadDialog* self)
{
    float f0 = DAT_01486114;
    float f1 = DAT_01485720;
    *(void**)((char*)self + 0x04) = (void*)vtbl_Resource_Async;
    self->mpVal_08 = 0;
    *(void**)self = (void*)vtbl_UI_cDownloadDialog_A;
    *(void**)((char*)self + 0x04) = (void*)vtbl_UI_cDownloadDialog_B;
    self->mpNode_0c = 0;
    self->m_timerPeriod = f0;
    self->m_active = 0;
    self->m_latch = 0;
    self->m_p1c = 0.0f;
    self->m_p20 = 0.0f;
    self->m_p24 = f1;
    self->m_p28 = 0.0f;
    self->m_paused = 0;
    self->m_label = 0;
    self->m_entry = 0;
    self->m_count = 1;
    self->m_index = 0;
    ((cSPUILayout*)((char*)self + 0x54))->ctor();
    return self;
}
// 0x00DF59C0
// @ 0x00df59c0
bool cDownloadDialog::FUN_00df59c0(void* p)
{
    uint key[3];
    key[0] = 0xdd6e903b;
    key[1] = 0x0510a95b;
    key[2] = 0x40464100;
    cSPUILayout* lay = Layout();
    if (!lay->Init(key, 1, 0x5b598fa))
        return false;
    IWinNode* w = (IWinNode*)lay->FindWindowByID(0x431e538, 1);
    if (!w) {
        lay->Shutdown(1);
        return false;
    }
    w->v104(this);
    IWinNode* w2 = (IWinNode*)lay->FindWindowByID(0x5d68ee8, 1);
    if (w2) {
        Vec4* r = w2->v34();
        m_r34 = r->x;
        m_r38 = r->y;
        m_r3c = r->z;
        m_r40 = r->w;
        ((WinTextRef*)((char*)this + 0x30))->operator=(w2);
        m_progress = 0.0f;
        FUN_00df5610(0.0f);
    }
    *(void**)((char*)this + 0x48) = p;
    *(int*)((char*)this + 0x4c) = *(int*)((char*)p + 0x58);
    (void)w2;
    return true;
}

// 0x00DF5AA0
// @ 0x00df5aa0
void cDownloadDialog::FUN_00df5aa0(char b)
{
    if (b != 0) {
        *(char*)((char*)this + 0x18) = 1;
        return;
    }
    FUN_00df57d0(0);
}

// 0x00DF5AC0
// @ 0x00df5ac0
bool cDownloadDialog::FUN_00df5ac0(int b)
{
    if (*(char*)((char*)this + 0x18) != 0) {
        float el = SPUIHelpers_GetElapsedSeconds();
        if (*(float*)((char*)this + 0x14) > (el - *(float*)((char*)this + 0x10))) {
            goto slow;
        }
        if (*(char*)((char*)this + 0x19) == 0) {
            *(char*)((char*)this + 0x19) = 1;
            *(float*)((char*)this + 0x10) = SPUIHelpers_GetElapsedSeconds();
            *(float*)((char*)this + 0x14) = 0.0f;
            m_p28 = 0.0f;
            void* lc = *(void**)((char*)this + 0x0c);
            float* arg = (float*)((char*)this + 0x1c);
            void* r = ((IWinNode*)lc)->vf0(0x43322c0, 1, arg);
            FUN_00808230(r, arg);
            return true;
        }
        FUN_00df57d0(1);
        return true;
    }
slow:
    if (*(char*)((char*)this + 0x19) != 0)
        return true;
    if (*(char*)((char*)this + 0x2c) != 0)
        return true;
    {
        float el = SPUIHelpers_GetElapsedSeconds();
        m_p28 = (el - *(float*)((char*)this + 0x10)) * DAT_013fa9c8;
        void* lc = *(void**)((char*)this + 0x0c);
        float* arg = (float*)((char*)this + 0x1c);
        void* r = ((IWinNode*)lc)->vf0(0x43322c0, 1, arg);
        FUN_00808230(r, arg);
        if (m_entry != 0) {
            FUN_00e20860(m_entry);
            m_progress = (float)*(int*)((char*)m_entry + 0x64) * DAT_013eb960;
        }
        float v = m_progress;
        if (0.0f > v) v = 0.0f;
        if (v > 1.0f) v = 1.0f;
        m_progress = v;
        if (v >= 1.0f) {
            if ((uint)m_index < (uint)(m_count - 1))
                m_index++;
            m_progress = 0.0f;
        }
        float t = FUN_00df54f0(m_progress);
        if (0.0f > t) t = 0.0f;
        if (t > 1.0f) t = 1.0f;
        if (*(void**)((char*)this + 0x30) != 0) {
            float a = m_r34;
            float c = m_r3c;
            float x = a;
            float y = m_r38;
            float z = (c - a) * t + a;
            float w = m_r40;
            IWinNode* n = *(IWinNode**)((char*)this + 0x30);
            n->v60((int)x, (int)y);
            (void)z; (void)w;
        }
    }
    return true;
}

// 0x00DF5C80 : second constructor (base sub-object)
// @ 0x00df5c80
cDownloadDialog* __fastcall cDownloadDialog_ctor_5c80(cDownloadDialog* self)
{
    *(void**)((char*)self + 0x04) = (void*)vtbl_Resource_Async;
    self->mpVal_08 = 0;
    *(void**)self = (void*)vtbl_UI_cDownloadDialog_C;
    *(void**)((char*)self + 0x04) = (void*)vtbl_UI_cDownloadDialog_D;
    ((cSPUILayout*)((char*)self + 0x0c))->ctor();
    *(void**)((char*)self + 0x24) = 0;
    return self;
}

// 0x00DF5CD0
// @ 0x00df5cd0
void cDownloadDialog::FUN_00df5cd0()
{
    IWinNode* p = *(IWinNode**)((char*)this + 0x24);
    *(void**)this = (void*)vtbl_UI_cDownloadDialog_C;
    *(void**)((char*)this + 0x04) = (void*)vtbl_UI_cDownloadDialog_D;
    if (p) {
        SPUIHelpers_EndModal(p, 0, 1);
        IWinNode* q = *(IWinNode**)((char*)this + 0x24);
        if (q) {
            *(void**)((char*)this + 0x24) = 0;
            q->v04();
        }
    }
    IWinNode* q = *(IWinNode**)((char*)this + 0x24);
    if (q)
        q->v04();
    ((cSPUILayout*)((char*)this + 0x0c))->dtor();
    *(void**)((char*)this + 0x04) = (void*)vtbl_Editor_cEditorResource;
    *(void**)this = (void*)vtbl_Editor_cEditorResource;
}

// 0x00DF5D30
// @ 0x00df5d30
void* cDownloadDialog::FUN_00df5d30(int b)
{
    *(void**)this = (void*)vtbl_UI_cDownloadDialog_A;
    *(void**)((char*)this + 0x04) = (void*)vtbl_UI_cDownloadDialog_B;
    ((cSPUILayout*)((char*)this + 0x54))->dtor();
    IWinNode* p = *(IWinNode**)((char*)this + 0x30);
    if (p)
        p->v04();
    IWinNode* q = *(IWinNode**)((char*)this + 0x0c);
    if (q)
        q->v04();
    *(void**)((char*)this + 0x04) = (void*)vtbl_Editor_cEditorResource;
    *(void**)this = (void*)vtbl_Editor_cEditorResource;
    if (b & 1)
        EA_UTFWin_MultiHeapObject_free(this);
    return this;
}

// 0x00DF5D90
// @ 0x00df5d90
struct WinMsg { void* mpNode; char pad_04[4]; uint32_t mId; };
bool cDownloadDialog::FUN_00df5d90(void* a, void* b)
{
    WinMsg* msg = (WinMsg*)b;
    uint32_t id = msg->mId;
    if (id == 0x287259f6) {
        if (((IWinNode*)msg->mpNode)->v1c() == 0x5d2bdf8) {
            MsgObj* s = (MsgObj*)SP_MessageServer();
            s->m14(0x5d663cd, 0, 0);
            return true;
        }
        if (((IWinNode*)msg->mpNode)->v1c() == 0x5d66f78) {
            MsgObj* s = (MsgObj*)SP_MessageServer();
            s->m14(0x5d6714b, 0, 0);
            return true;
        }
    } else if (id == 0x0c) {
        return FUN_00df5ac0((int)a);
    } else if (id == 0x11) {
        return ((IWinNode*)this)->v80((const wchar_t*)a);
    }
    return false;
}

// 0x00DF5EF0
// @ 0x00df5ef0
bool FUN_00df5ef0()
{
    return *(int*)(kGUI + 0xfc) == 0;
}

// 0x00DF5F10
// @ 0x00df5f10
void FUN_00df5f10()
{
    Obj* p = FUN_00dd9190();
    FUN_00ddb760(p);
    FUN_00de9ec0((Obj*)kGUI);
}

// 0x00DF5F50
static double RandRangeD(double lo, double hi)
{
    double u = sMathRandom.next();
    return u * (hi - lo) + lo;
}

// @ 0x00df5f50
float* FUN_00df5f50(float* out, const float* r)
{
    {
        double lo = r[0];
        double hi = r[3];
        double v = RandRangeD(lo, hi);
        if (v < hi) {
            if (v < lo) v = lo;
        } else {
            v = hi;
        }
        out[0] = (float)v;
    }
    {
        double lo = r[1];
        double hi = r[4];
        double v = RandRangeD(lo, hi);
        if (v < hi) {
            if (v < lo) v = lo;
        } else {
            v = hi;
        }
        out[1] = (float)v;
    }
    {
        double lo = r[2];
        double hi = r[5];
        double v = RandRangeD(lo, hi);
        if (v < hi) {
            if (v < lo) v = lo;
        } else {
            v = hi;
        }
        out[2] = (float)v;
    }
    return out;
}

// 0x00DF6040
// @ 0x00df6040
void cDownloadDialog::FUN_00df6040()
{
    int n = (int)((char*)m_entryEnd - (char*)mpVal_08) / 0xbc;
    if (n != 0) {
        char* base = (char*)mpVal_08;
        for (int i = 0; i < n; i++) {
            char* e = base + i * 0xbc;
            float a, b;
            FUN_00de3c70(e + 0x80, &a, &b);
            ((IWinNode*)this)->v64(a, b);
        }
    }
    float z[3] = { 0.0f, 0.0f, 0.0f };
    float a, b;
    FUN_00de3c70(z, &a, &b);
    if (fabsf(DAT_016a16a8 - a) > DAT_01486110)
        DAT_016a16a8 = a;
    if (fabsf(DAT_016a16a4 - b) > DAT_01486110)
        DAT_016a16a4 = b;
}

// 0x00DF6140 : UpdateGamesUILocations (PDB candidate)
// @ 0x00df6140
bool cDownloadDialog::FUN_00df6140(Obj* a, float x, float y)
{
    if (*(void**)((char*)a + 0xb8) == 0)
        return false;
    cSPUILayout* lay = *(cSPUILayout**)((char*)a + 0xb8);
    IWinNode* w = (IWinNode*)lay->FindWindowByID(0x2e5a4a8, 0);
    if (w) {
        Vec4 area;
        SPUIHelpers_GetMainWindowArea(&area);
        Vec4* r1 = w->v38();
        float a0 = r1->x, a1 = r1->y, a2 = r1->z, a3 = r1->w;
        Vec4* r2 = w->v34();
        float p0 = r2->x, p1 = r2->y;
        x = x - (a2 - a0) * DAT_01471064;
        y = y - (a3 - a1) * DAT_01471064;
        if (*(char*)((char*)a + 0xac) != 0) {
            float ty = (area.z - area.x) - DAT_016a0ec8;
            float tx = (area.w - area.y) - DAT_016a0ea8;
            float limx = DAT_016a0e98;
            float limy = DAT_016a0eb8;
            if (y <= ty) { /* keep y */ } else y = ty;
            if (limy <= y) y = limy;
            if (x <= tx) { /* keep x */ } else x = tx;
            if (limx <= x) x = limx;
        }
        if (fabsf(p0 - x) > DAT_014853e0 || fabsf(p1 - y) > DAT_014853e0) {
            w->v64(x, y);
        }
    }
    return w != 0;
}

// 0x00DF6330
// @ 0x00df6330
void cDownloadDialog::FUN_00df6330(uint id, void* p, uint b)
{
    if (((DAT_016a1848[id >> 5] >> (id & 0x1f)) & 1) != 0)
        return;
    FUN_00e00670(id, p);
    if (id == 0x1b) {
        if (*(char*)(kGUI + 0x1f0) == 0) {
            if (*(int*)(kGUI + 0xfc) != 0) {
                AudioSys* au = (AudioSys*)EA_Audio_GetSystemAT();
                if (au)
                    au->a20();
                SP_cSPUISpace_KillSetiEffects(0, 0xb7a63c50);
                if (*(char*)(*(int*)(kGUI + 0xfc) + 0xac) != 0)
                    FUN_00dde570(*(void**)(kGUI + 0x198));
                ((IWinNode*)this)->v60(0, 1);
                FUN_00e00650(0x1b, p);
                return;
            }
            FUN_00de86d0(6, 1);
            AudioSys* au = (AudioSys*)EA_Audio_GetSystemAT();
            if (au)
                au->a20();
            SP_cSPUISpace_KillSetiEffects(0, 0x5da7b944);
            MsgObj* s = (MsgObj*)SP_MessageServer();
            s->m14(0x64a5044, 0, 0);
        } else {
            IWinNode* w1 = *(IWinNode**)(kGUI + 0x160);
            if (w1) {
                w1->v0c(1);
                IWinNode* t1 = *(IWinNode**)(kGUI + 0x160);
                if (t1) {
                    *(void**)(kGUI + 0x160) = 0;
                    t1->v04();
                }
            }
            IWinNode* w2 = *(IWinNode**)(kGUI + 0x1a0);
            if (w2) {
                w2->v0c(1);
                IWinNode* t2 = *(IWinNode**)(kGUI + 0x1a0);
                if (t2) {
                    *(void**)(kGUI + 0x1a0) = 0;
                    t2->v04();
                }
            }
            MsgObj* s = (MsgObj*)SP_MessageServer();
            s->m14(0x4360e14, 0, 0);
        }
    }
    FUN_00e00650(id, p);
}

// 0x00DF64C0
// @ 0x00df64c0
int cDownloadDialog::FUN_00df64c0(float a, float b, float c)
{
    Obj* app = SP_App();
    (*(void(**)())(*(int*)app + 0x58))();
    float qa[4], qb[4];
    if (!FUN_007c4510(a, b, qa, qb))
        return 0;
    int n = (int)((char*)m_entryEnd - (char*)mpVal_08) / 0xbc;
    int best = 0;
    float bestd = c;
    if (n != 0) {
        char* base = (char*)mpVal_08;
        for (int i = 0; i < n; i++) {
            char* e = base + i * 0xbc;
            float d;
            QuaternionSlerp(&d, qa, qb, *(float*)(e + 0x80));
            if (d < bestd) {
                bestd = d;
                best = (int)e;
            }
        }
        if (best != 0) {
            Obj* app2 = SP_App();
            (*(void(**)())(*(int*)app2 + 0x58))();
            FUN_007c4180((float*)(best + 0x80), qa);
        }
    }
    return best;
}

// 0x00DF65E0
// @ 0x00df65e0
void cDownloadDialog::FUN_00df65e0(void* a, void* b, float c)
{
    if (*(char*)(kGUI + 0x17c) != 0)
        return;
    int r = FUN_00df64c0(*(float*)&a, *(float*)&b, DAT_014007f4);
    int cur = *(int*)(kGUI + 0xf8);
    if (cur == 0 || cur == r) {
        ((IWinNode*)this)->v5c((void*)r);
        return;
    }
    cSPUILayout* lay = *(cSPUILayout**)(cur + 0xb8);
    if (lay == 0)
        return;
    IWinNode* w = (IWinNode*)lay->FindWindowByID(0x2e5a4a8, 1);
    if (w == 0)
        return;
    Vec4* rect = w->v38();
    float v2[4];
    v2[0] = *(float*)&a;
    v2[1] = *(float*)&b;
    v2[2] = rect->x;
    v2[3] = rect->y;
    if (!FUN_005f2350(v2)) {
        ((IWinNode*)this)->v5c(0);
        return;
    }
}

// 0x00DF66E0
// @ 0x00df66e0
struct StarVec { uint32_t* mpBegin; uint32_t* mpEnd; int size() { return (int)(mpEnd - mpBegin); } };
struct StarManagerObj { char pad_00[0xf0]; StarVec mVec; };
int FUN_00df66e0()
{
    StarManagerObj* m = (StarManagerObj*)SP_StarManager();
    return m->mVec.size();
}
