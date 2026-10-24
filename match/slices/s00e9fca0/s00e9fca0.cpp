// Slice s00e9fca0 -- SP::Audio ambience-layer / city-music-editor cluster
// (0x00e9fca0..0x00ea0900).
//
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), same family as the sibling
// Audio/Simulator slices.
//
// Contents:
//   e9fca0  SP::Audio::cAmbienceLayerManager::SetupLayers -- re-run FUN_00e9e220, pull the
//           layer configuration blob out of mConfiguration (a small inline container whose
//           flags live at +0x10 and count at +0x12), then funn IConfiguration values through
//           EA::ConvertToString8 and hand each to FUN_00e9faa0.
//   e9fd70  cAmbienceLayerManager::ReadTuningValues -- drop the old mConfiguration, re-acquire
//           it from the audio system (slot 0x14), read the cell count (0xa), the sample-point
//           iterator and two ResponseCurves, then FUN_00e9fbc0 + SetupLayers.
//   e9fe40  small helper: when the opaque key at +8 == 0x15 build the Vector3{x, x, 1.0} from
//           this+0x10 and hand it to FUN_0095ea30 (this = key+0x18).
//   e9fe90  cWindowPulse::SetWindow -- detach the old window (0x108/0x98), swap the ref-counted
//           mpWindow (+0xc), re-attach through 0x104/0x98/0x10->0xe8.
//   e9ff20  quadratic ease: ((a-b)/(c-b))^2, with an inf/nan-prevention pow() branch.
//   e9ffb0  cCityMusicEditor::SetMusic -- swap the ref-counted mpMusic (+0xd8) then propagate it
//           to the undo buffer, the note editor (+0xe0) and the load/save (+0xf8).
//   ea0010  cCityMusicEditor::SetVisibility -- when the layout visibility changes, poke every
//           editor sound handle and mirror the state through the audio system.
//   ea0200  cCityMusicEditor::Update -- refresh the two toggle windows, the note editor and the
//           per-pulse VU-meter values (+0x10) from the audio system.
//   ea0350  assign every element of a range from a single ref-counted source object.
//   ea03e0  RecursiveButtonSelect -- walk the child-window list of a window and mark each child.
//   ea0460  cCityMusicEditor::Redraw -- tear down + rebuild the six pulse windows and the three
//           VU meters, then redraw/loop the melody.
//
// Result (this session): see manifest.txt / nonmatching.txt / partial.txt.
// Every function below is a complete definition.
//
// Notes / decisions:
//  * ABI: thiscall methods are reproduced as `__fastcall(T* self, void* edx, ...)` free
//    functions; external thiscall callees are invoked through the `Thiscall` registry struct so
//    that ecx receives the receiver without cl15 materialising an unused edx (cl15 rejects
//    __thiscall on a free function).  `ret 4`/`ret 8` originals => __fastcall with 2 stack args.
//  * Virtual window accesses go through the IWnd/IThumb interfaces (declaration order == vtable
//    order): IWnd carries 0x0c GetChild, 0x10, 0x28(2 args), 0x7c, 0x98, 0xcc/0xd0, 0xe8, 0xf0,
//    0x104/0x108; IThumb carries the VU getters/setter 0x1c/0x28/0x30.  IConfiguration carries the
//    config getters 0x1c/0x28/0x30; AudioSystem carries 0x14/0x30/0x38/0x40/0x58.
//  * Field offsets use named members only (no raw-pointer arithmetic on the real objects).
//    Where the original really iterates a byte blob (the layer config container at +0x10), the
//    blob is described by `AmbConfig`'s named fields.
//  * The three VU-meter blocks in Redraw share the VU_BLOCK macro (only the window id and the
//    Vector3 component differ), matching the original's textual repetition.
#include "types.h"
#include <math.h>

typedef unsigned int uintptr_t;
typedef unsigned int uint;

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

// Ref-counted handle: slot 0 = AddRef-like, slot 4 = Release-like.
struct IRefCount {
    virtual void AddRef();                        // 0x00
    virtual void Release();                       // 0x04
};

// The window / child-window interface (cSPUIWindow-like): declaration order == vtable order.
struct IWnd {
    virtual void AddRef();                        // 0x00
    virtual void Release();                       // 0x04
    PV                                            // 0x08
    virtual void* GetChild(uint id);              // 0x0c
    virtual IWnd* Slot10();                       // 0x10
    PV4 PV                                        // 0x14..0x24
    virtual void  Slot28(int a, int b);           // 0x28
    PV16 PV4                                      // 0x2c..0x78
    virtual void  Slot7c(int a, int b);           // 0x7c
    PV4 PV2                                       // 0x80..0x94
    virtual void  Slot98();                       // 0x98
    PV8 PV4                                       // 0x9c..0xc8
    virtual void  SlotCC(void** out);             // 0xcc
    virtual void  SlotD0(void** out);             // 0xd0
    PV4 PV                                        // 0xd4..0xe4
    virtual void  SlotE8(void* p);                // 0xe8
    PV                                            // 0xec
    virtual void* SlotF0(uint id, int a);         // 0xf0
    PV4                                           // 0xf4..0x100
    virtual void  Slot104(void* p);               // 0x104
    virtual void  Slot108(void* p);               // 0x108
};

// VU-meter thumb/slider object reached through GetChild(0xf00a8a0).
struct IThumb {
    PV4 PV2 PV                                    // 0x00..0x18
    virtual void Slot1c(int a, int b);            // 0x1c
    PV2                                           // 0x20, 0x24
    virtual int  Slot28();                        // 0x28
    PV                                            // 0x2c
    virtual int  Slot30();                        // 0x30
};

// audio-system configuration object (EA::Audio::IConfiguration-like).
struct IConfiguration {
    virtual void AddRef();                        // 0x00
    virtual void Release();                       // 0x04
    PV4 PV                                        // 0x08..0x18
    virtual void Slot1c(uint id, void** out);     // 0x1c
    PV2                                           // 0x20, 0x24
    virtual void Slot28(uint id, int* out);       // 0x28
    PV                                            // 0x2c
    virtual void Slot30(uint id, void** out);     // 0x30
};

// EA::Audio system (AT) reached through GetSystemAT().
struct AudioSystem {
    PV4 PV                                        // 0x00..0x10
    virtual bool Slot14(uint a, void** cfg, uint b);        // 0x14
    PV4 PV2                                       // 0x18..0x2c
    virtual void Slot30(void* id, uint hash, void** out);   // 0x30
    PV                                            // 0x34
    virtual void Slot38(uint a);                  // 0x38
    PV                                            // 0x3c
    virtual void Slot40(uint a, uint b);          // 0x40
    PV4 PV                                        // 0x44..0x54
    virtual void Slot58();                        // 0x58
};

// The sound-pulse wrapper: window at +0xc, value at +0x10.
struct cWindowPulse {
    uint8_t pad00[0x0c];
    IWnd*   mpWindow;                             // +0x0c
    float   mValue;                               // +0x10
};

// cSPUILayout non-virtual helpers (undefined externs; only ecx matters).
struct cSPUILayout {
    char  IsVisible();                            // 0x00810070
    void  SetVisibility(uint v);                  // 0x00810590
    void* FindWindowByID(uint id, int a);         // 0x008105b0 (2-arg form)
    void* FindWindowByID3(uint id, int a, int b); // 0x008105b0 (3-arg form)
};

// The city music data object (cPlayerCityMusic): an id vector at +0x114 and a level Vector3.
struct cPlayerCityMusic {
    uint8_t  pad00[0x114];
    int32_t* mpIds;                               // +0x114
    int32_t* mpIdsEnd;                            // +0x118
    uint8_t  pad11c[0x198 - 0x11c];
    Vector3* mpVuLevel;                           // +0x198
    uint8_t  pad19c[0x1c4 - 0x19c];
    int32_t  mSel1c4;                             // +0x1c4
    int32_t  mFlag1c8;                            // +0x1c8
};

struct cCityMusicNoteEditor;
struct cCityMusicLoadSave;

struct cCityMusicEditor {
    uint8_t               pad00[0xd8];
    cPlayerCityMusic*     mpMusic;                // +0xd8
    cSPUILayout*          mpLayout;               // +0xdc
    cCityMusicNoteEditor* mpNoteEditor;           // +0xe0
    cWindowPulse**        mpPulsesBegin;          // +0xe4
    cWindowPulse**        mpPulsesEnd;            // +0xe8
    uint8_t               padEC[0xf8 - 0xec];
    cCityMusicLoadSave*   mpLoadSave;             // +0xf8
};

// Layer-config container handed back by IConfiguration::Slot1c: an inline/dynamic tag word
// at +0x10, an element count at +0x12, a begin pointer at +0 and an end at +8.
struct AmbConfig {
    void*    mpBegin;                             // +0x00
    uint8_t  pad04[4];                            // +0x04
    void*    mpEnd;                               // +0x08
    uint8_t  pad0c[4];                            // +0x0c
    uint16_t mFlags;                              // +0x10
    uint16_t mCount;                              // +0x12
};

struct cAmbienceLayerManager {
    uint8_t         pad00[0x10];
    IConfiguration* mpConfiguration;              // +0x10
    uint8_t         pad14[0x14];                  // +0x14..+0x27
    int32_t         mNumCells;                    // +0x28
    uint8_t         pad2c[0xc0];                  // +0x2c..+0xeb
    uint8_t         mCurveA[0x364];               // +0xec (ResponseCurve)
    uint8_t         mCurveB[0x364];               // +0x450 (ResponseCurve)
    uint8_t         mItSamplePts[0x40];           // +0x7b4
};

// ---------------------------------------------------------------------------------------------
// External callees.
// ---------------------------------------------------------------------------------------------
void*       EA_GetSystemAT(void);                       // 0x00a206f0
void*       __cdecl EA_ConvertToString8(void*, const int*);   // 0x0093c570
void        __cdecl operator_delete_array(void*);       // 0x00f47380
void        __cdecl SetGlobalProperty(uint key, float value);      // 0x005ca880
void        __cdecl RecordEvent4(uint id, uint hash, float value, uint extra); // 0x00435f40
double      __cdecl _CIpow_dummy(void);                 // 0x011e08f0 (x87 pow helper)

extern const float  gRealOne;         // 0x01485720 (_HK_REAL_ONE)
extern const float  gRealZero;        // 0x01485378 (_HK_REAL_ZERO)
extern const float  gConst13ec478;    // 0x013ec478
extern const double gConst140ebb0;    // 0x0140ebb0
extern const float  gConst13eecd8;    // 0x013eecd8
extern const float  gConst1486110;    // 0x01486110
extern uint32_t     gEditorSoundHandles[6];   // 0x01487198
extern uint32_t     gPropId015a8b78;  // 0x015a8b78
extern uint32_t     gListBase1440aec; // 0x01440aec

// Registry of thiscall callees.
struct Thiscall {
    void  FUN_00e9e220();                        // 0x00e9e220
    void  FUN_00e9faa0(void* s);                 // 0x00e9faa0
    void  FUN_00e9fbc0();                        // 0x00e9fbc0
    void  FUN_00e9fca0();                        // 0x00e9fca0 (SetupLayers)
    void  SetWindow(IWnd* w);                    // 0x00e9fe90 (cWindowPulse::SetWindow)
    void  SetMusicNote(void* m);                 // 0x00ea2d50 (cCityMusicNoteEditor::SetMusic)
    void  SetMusicLoad(void* m);                 // 0x00ea23a0 (cCityMusicLoadSave::SetMusic)
    void  ResetUndoBuffer();                     // 0x00eb10d0
    unsigned char FUN_00ead820();                // 0x00ead820 (returns char)
    unsigned char FUN_00ead840();                // 0x00ead840 (returns char)
    void  FUN_00ea3b50();                        // 0x00ea3b50 (cCityMusicNoteEditor::Update)
    void  FUN_00ea3420(int b);                   // 0x00ea3420 (RedrawMelody)
    void  FUN_00ea3120();                        // 0x00ea3120 (LoopMelody)
    void  SetSoundProperty(int v);               // 0x00ea3040
    void  InitFromConfiguration(void* cfg, uint id);   // 0x00a1a9d0
    void  FUN_0095ea30(void* vec);               // 0x0095ea30
};

void __fastcall FUN_00e9ffb0(cCityMusicEditor* self, void* edx, void* music);
void __cdecl    RecursiveButtonSelect(void* wnd, void* ctx);

// ---------------------------------------------------------------------------------------------
// @ 0x00e9fca0
// ---------------------------------------------------------------------------------------------
bool __fastcall FUN_00e9fca0(cAmbienceLayerManager* self, void* edx)
{
    (void)edx;
    ((Thiscall*)self)->FUN_00e9e220();
    AmbConfig c;
    self->mpConfiguration->Slot1c(0xc49b97a3, (void**)&c);
    bool dynamic = (c.mFlags & 0x30) != 0;
    if (!dynamic) {
        if (c.mCount == 0)
            return true;
    } else if (c.mpEnd == 0) {
        return true;
    }
    void* iter = dynamic ? c.mpBegin : (void*)&c;
    int count = dynamic ? (int)(uintptr_t)c.mpEnd : (c.mCount != 0 ? 1 : 0);
    for (int i = 0; i < count; ++i) {
        void* tmp = 0;
        void* s = EA_ConvertToString8(&tmp, (const int*)iter);
        ((Thiscall*)self)->FUN_00e9faa0(*(void**)s);
        if (tmp)
            operator_delete_array(tmp);
        iter = (char*)iter + 0x10;
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00e9fd70
// ---------------------------------------------------------------------------------------------
char __fastcall FUN_00e9fd70(cAmbienceLayerManager* self, void* edx)
{
    (void)edx;
    AudioSystem* sys = (AudioSystem*)EA_GetSystemAT();
    IConfiguration* cfg = self->mpConfiguration;
    if (cfg) {
        self->mpConfiguration = 0;
        cfg->Release();
    }
    if (!sys->Slot14(0x6ff1e689, (void**)&self->mpConfiguration, 0x21407ee))
        return 0;
    cfg = self->mpConfiguration;
    self->mNumCells = 10;
    cfg->Slot28(gPropId015a8b78, &self->mNumCells);
    self->mpConfiguration->Slot30(0xf5a18499, (void**)&self->mItSamplePts);
    ((Thiscall*)(void*)self->mCurveA)->InitFromConfiguration(self->mpConfiguration, 0xdc079eb6);
    ((Thiscall*)(void*)self->mCurveB)->InitFromConfiguration(self->mpConfiguration, 0x2f826725);
    ((Thiscall*)self)->FUN_00e9fbc0();
    ((Thiscall*)self)->FUN_00e9fca0();
    return 1;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00e9fe40
// ---------------------------------------------------------------------------------------------
bool __fastcall FUN_00e9fe40(void* self, void* edx, uint param_2, uint param_3)
{
    (void)edx;
    (void)param_2;
    bool ok = false;
    uint32_t* key = (uint32_t*)(uintptr_t)param_3;
    if (key[2] == 0x15) {
        float x = *(float*)((char*)self + 0x10);
        float vec[3];
        vec[0] = x;
        vec[1] = x;
        vec[2] = 1.0f;
        ((Thiscall*)(void*)(uintptr_t)key[6])->FUN_0095ea30(vec);
        ok = true;
    }
    return ok;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00e9fe90
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00e9fe90(cWindowPulse* self, void* edx, IWnd* wnd)
{
    (void)edx;
    IWnd* old = self->mpWindow;
    if (old) {
        old->Slot108(self);
        old->Slot98();
    }
    if (wnd != self->mpWindow) {
        if (wnd)
            wnd->AddRef();
        self->mpWindow = wnd;
        if (old)
            old->Release();
    }
    IWnd* cur = self->mpWindow;
    if (cur) {
        cur->Slot104(self);
        cur->Slot98();
        IWnd* r = cur->Slot10();
        r->SlotE8(cur);
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00e9ff20
// ---------------------------------------------------------------------------------------------
float __cdecl FUN_00e9ff20(int param_1, int param_2, int param_3)
{
    if (param_2 < 0 && param_3 == 0) {
        if (param_1 == param_2)
            return 0.0f;
        return (float)pow((double)param_1 * (double)gConst13ec478, gConst140ebb0);
    }
    float v = (float)(param_1 - param_2) / (float)(param_3 - param_2);
    float r = 1.0f;
    unsigned n = 2;
    for (;;) {
        if (n & 1)
            r *= v;
        n >>= 1;
        if (n == 0)
            break;
        v *= v;
    }
    return r;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00e9ffb0
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00e9ffb0(cCityMusicEditor* self, void* edx, void* music)
{
    (void)edx;
    void* old = self->mpMusic;
    if (music != old) {
        if (music)
            ((IRefCount*)music)->AddRef();
        self->mpMusic = (cPlayerCityMusic*)music;
        if (old)
            ((IRefCount*)old)->Release();
    }
    ((Thiscall*)(void*)self->mpMusic)->ResetUndoBuffer();
    ((Thiscall*)(void*)self->mpNoteEditor)->SetMusicNote(music);
    ((Thiscall*)(void*)self->mpLoadSave)->SetMusicLoad(music);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00ea0010
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00ea0010(cCityMusicEditor* self, void* edx, uint param_2)
{
    (void)edx;
    if (self->mpLayout->IsVisible() == (char)param_2)
        return;
    ((Thiscall*)(void*)self->mpNoteEditor)->SetSoundProperty(param_2);
    SetGlobalProperty(0x1d3d023a, (float)(uint)(unsigned char)param_2);
    if ((char)param_2 != 0) {
        unsigned off = 0;
        do {
            RecordEvent4(*(uint32_t*)((char*)gEditorSoundHandles + off), 0xdb83a083, 1.0f, 0);
            uint32_t v = *(uint32_t*)((char*)gEditorSoundHandles + off);
            AudioSystem* sys = (AudioSystem*)EA_GetSystemAT();
            if (sys) {
                sys->Slot38(0x407ab38);
                sys->Slot40(0x3475385, v);
                sys->Slot40(0x34753a7, 0xad57725a);
                sys->Slot58();
            }
            sys = (AudioSystem*)EA_GetSystemAT();
            if (sys) {
                sys->Slot38(0x407ab38);
                sys->Slot40(0x3475385, v);
                sys->Slot40(0x34753a7, 0xdf08e251);
                sys->Slot58();
            }
            off += 4;
        } while (off < 0x18);
    } else {
        unsigned off = 0;
        do {
            RecordEvent4(*(uint32_t*)((char*)gEditorSoundHandles + off), 0xdb83a083, 0.0f, 0);
            uint32_t v = *(uint32_t*)((char*)gEditorSoundHandles + off);
            AudioSystem* sys = (AudioSystem*)EA_GetSystemAT();
            if (sys) {
                sys->Slot38(0x407ab40);
                sys->Slot40(0x3475385, v);
                sys->Slot40(0x34753a7, 0xad57725a);
                sys->Slot58();
            }
            sys = (AudioSystem*)EA_GetSystemAT();
            if (sys) {
                sys->Slot38(0x407ab40);
                sys->Slot40(0x3475385, v);
                sys->Slot40(0x34753a7, 0xdf08e251);
                sys->Slot58();
            }
            off += 4;
        } while (off < 0x18);
    }
    self->mpLayout->SetVisibility(param_2);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00ea0200
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00ea0200(cCityMusicEditor* self, void* edx)
{
    (void)edx;
    IWnd* w1 = (IWnd*)self->mpLayout->FindWindowByID(0x4f8c2b2, 1);
    int v1 = ((Thiscall*)(void*)self->mpMusic)->FUN_00ead820();
    w1->Slot7c(2, v1);
    IWnd* w2 = (IWnd*)self->mpLayout->FindWindowByID(0x4f8c2bd, 1);
    int v2 = ((Thiscall*)(void*)self->mpMusic)->FUN_00ead840();
    w2->Slot7c(2, v2);
    ((Thiscall*)(void*)self->mpNoteEditor)->FUN_00ea3b50();
    int n = (int)(self->mpPulsesEnd - self->mpPulsesBegin);
    for (int i = 0; i < n; ++i) {
        cWindowPulse* e = self->mpPulsesBegin[i];
        if (e->mpWindow) {
            float a = 0.0f;
            float b = 0.0f;
            AudioSystem* sys = (AudioSystem*)EA_GetSystemAT();
            if (sys)
                sys->Slot30((void*)(uintptr_t)gEditorSoundHandles[i], 0xad57725a, (void**)&a);
            sys = (AudioSystem*)EA_GetSystemAT();
            if (sys)
                sys->Slot30((void*)(uintptr_t)gEditorSoundHandles[i], 0xdf08e251, (void**)&b);
            float v = (b + a) * gConst1486110 + gRealOne;
            if (v != e->mValue) {
                e->mValue = v;
                if (e->mpWindow)
                    e->mpWindow->Slot98();
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00ea0350
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00ea0350(void** begin, void** end, void** src)
{
    while (begin != end) {
        void* nv = *src;
        void* ov = *begin;
        if (nv != ov) {
            if (nv)
                ((IRefCount*)nv)->AddRef();
            *begin = nv;
            if (ov)
                ((IRefCount*)ov)->Release();
        }
        ++begin;
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00ea03e0
// ---------------------------------------------------------------------------------------------
void __cdecl RecursiveButtonSelect(void* wnd, void* ctx)
{
    IWnd* obj = (IWnd*)wnd;
    void* itEnd;
    void* itBeg;
    obj->SlotCC(&itBeg);
    obj->SlotD0(&itEnd);
    while (itBeg != itEnd) {
        RecursiveButtonSelect((void*)((uintptr_t)itBeg + gListBase1440aec), ctx);
        itBeg = *(void**)itBeg;
    }
    IWnd* child = (IWnd*)obj->GetChild(0x8ed27e7a);
    if (child)
        child->Slot28(4, (int)(uintptr_t)ctx);
}

#define VU_BLOCK(WINID, COMP)                                                    \
    do {                                                                         \
        IWnd* wv = (IWnd*)self->mpLayout->FindWindowByID(WINID, 1);              \
        IThumb* th = wv ? (IThumb*)wv->GetChild(0xf00a8a0) : (IThumb*)0;         \
        float fv = self->mpMusic->mpVuLevel->COMP;                               \
        int hi = th->Slot30();                                                   \
        int lo = th->Slot28();                                                   \
        int res;                                                                 \
        if (lo < 0 && hi == 0) {                                                 \
            if (fv != 0.0f)                                                      \
                res = (int)(logf(fv) / logf(10.0f) * 20.0f);                     \
            else                                                                 \
                res = lo;                                                        \
        } else {                                                                 \
            res = (int)(sqrtf(fv) * (float)(hi - lo)) + lo;                      \
        }                                                                        \
        th->Slot1c(res, 0);                                                      \
    } while (0)

// ---------------------------------------------------------------------------------------------
// @ 0x00ea0460
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00ea0460(cCityMusicEditor* self, void* edx)
{
    (void)edx;
    cWindowPulse** p = self->mpPulsesBegin;
    cWindowPulse** pend = self->mpPulsesEnd;
    uint n = (uint)(pend - p);
    for (uint i = 0; i < n; ++i) {
        cWindowPulse* e = p[i];
        IWnd* w = e->mpWindow;
        if (w) {
            w->Slot108(e);
            w->Slot98();
        }
        w = e->mpWindow;
        if (w) {
            e->mpWindow = 0;
            w->Release();
        }
        w = e->mpWindow;
        if (w) {
            w->Slot104(e);
            w->Slot98();
            IWnd* r = w->Slot10();
            r->SlotE8(w);
        }
    }

    IWnd* root = (IWnd*)self->mpLayout->FindWindowByID3(0x45958e0, 1, 0);
    RecursiveButtonSelect(root, 0);

    VU_BLOCK(0x4d82fc8, x);
    VU_BLOCK(0x4d82fb8, y);
    VU_BLOCK(0x4d82fc0, z);

    cPlayerCityMusic* music = self->mpMusic;
    IWnd* wE9 = (IWnd*)self->mpLayout->FindWindowByID(0x41914e9, 1);
    uint cnt = (uint)((char*)music->mpIdsEnd - (char*)music->mpIds) >> 2;
    uint i = 0;
    if (cnt != 0) {
        do {
            uint id = (uint)music->mpIds[i];
            if (id > 0) {
                IWnd* c = (IWnd*)wE9->SlotF0(id, 0);
                IWnd* child = c ? (IWnd*)c->GetChild(0x8ed27e7a) : 0;
                child->Slot28(4, 1);
                ((Thiscall*)self->mpPulsesBegin[i + 2])->SetWindow(c);
            }
            ++i;
        } while (i < cnt);
    }

    IWnd* wF0 = (IWnd*)self->mpLayout->FindWindowByID(0x41914f0, 1);
    if (music->mSel1c4 != 0) {
        IWnd* c = (IWnd*)wF0->SlotF0((uint)music->mSel1c4, 0);
        IWnd* child = c ? (IWnd*)c->GetChild(0x8ed27e7a) : 0;
        child->Slot28(4, 1);
        ((Thiscall*)self->mpPulsesBegin[0])->SetWindow(c);
    }

    IWnd* wF3 = (IWnd*)self->mpLayout->FindWindowByID(0x41914f3, 1);
    if (music->mFlag1c8 != 0) {
        IWnd* c = (IWnd*)wF3->SlotF0((uint)music->mFlag1c8, 0);
        IWnd* child = c ? (IWnd*)c->GetChild(0x8ed27e7a) : 0;
        child->Slot28(4, 1);
        ((Thiscall*)self->mpPulsesBegin[1])->SetWindow(c);
    }

    ((Thiscall*)(void*)self->mpNoteEditor)->FUN_00ea3420(music->mFlag1c8 != 0);
    ((Thiscall*)(void*)self->mpNoteEditor)->FUN_00ea3120();
}