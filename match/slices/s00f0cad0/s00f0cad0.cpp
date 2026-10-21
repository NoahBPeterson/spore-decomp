// Slice s00f0cad0: SporeApp/Simulator SP palette-item UI + placeable-effect.
// Functions 00f0cad0..00f0d8b0 of utl/SP*.obj.
//
//  00f0cad0  SP::cSPPaletteItemUIOneClickPaint::Init
//  00f0cc80  SP::cSPPaletteItemUIOneClickPaint::Shutdown
//  00f0cce0  SP::cSPPaletteItemUIOneClickPaint::DoMessage
//  00f0cdd0  ctor (OneClickPaint)
//  00f0ce10  dtor (OneClickPaint)
//  00f0ce60  SP::cSPPaletteItemUIOneClickPaint::HandleMessage
//  00f0d3f0  Simulator::cBuilding::func80h  (returns 1.0f)
//  00f0d400  float  * this->f114 * this->f60
//  00f0d450  Simulator::cPlaceableEffect::cPlaceableEffect
//  00f0d620  Simulator::cPlaceableEffect::Shutdown
//  00f0d6a0  Simulator::cPlaceableEffect::SetViewportScale
//  00f0d6e0  Simulator::cPlaceableEffect::Write
//  00f0d840  Simulator::cPlaceableEffect::~cPlaceableEffect
//  00f0d8b0  Simulator::cPlaceableEffect::ReadProperties
//
// The class layouts are taken directly from this slice's disassembly (offsets
// are documented per field).  All object members are addressed by byte offset
// because only a partial PDB is available.
//
// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

// ---------------------------------------------------------------------------
// External helpers (real addresses of the sibling functions).
// ---------------------------------------------------------------------------
extern "C" void   f_00f0cad0(void* self, void* a, void* b, void* c);   // Init (self)
extern "C" void   f_00f0cc80(void* self);                               // Shutdown
extern "C" void*  f_MessageServer(void);                                // 0x67dcc0
extern "C" void   f_00f0cce0(void* self, void* a, void* b);             // DoMessage
extern "C" void*  f_00f0cce0_ptr(void* self, void* a, void* b);         // DoMessage
extern "C" void   f_00f0cdd0(void* self);                               // ctor
extern "C" void   f_00f0ce10(void* self, unsigned flags);               // dtor
extern "C" void   f_00f0ce60(void* self, void* a, void* b);             // HandleMessage
extern "C" float  f_00f0d3f0(void);                                     // returns 1.0f
extern "C" float  f_00f0d400(void* self);                               // f114 * f60
extern "C" void   f_00f0d450(void* self);                               // cPlaceableEffect ctor
extern "C" void   f_00f0d620(void* self);                               // cPlaceableEffect Shutdown
extern "C" void   f_00f0d6a0(void* self, float v);                      // SetViewportScale
extern "C" int    f_00f0d6e0(void* self, void* stream);                 // Write
extern "C" void   f_00f0d840(void* self, unsigned flags);               // dtor
extern "C" void   f_00f0d8b0(void* self);                               // ReadProperties

// ---------------------------------------------------------------------------
// Globals referenced by this object file.
// ---------------------------------------------------------------------------
extern float g_16c7f54;         // 0x16c7f54
extern float g_16c7fa8;         // 0x16c7fa8
extern float g_16c7fac;         // 0x16c7fac
extern float g_16c7fb0;         // 0x16c7fb0
extern float g_16c7fb4;         // 0x16c7fb4
extern float g_16c7fb8;         // 0x16c7fb8
extern float g_16c7fbc;         // 0x16c7fbc
extern void* g_16c7aa4;         // 0x16c7aa4
extern float g_1485378;         // 0x1485378 == 0.0f

extern "C" void* f_EAAllocate(unsigned size, const char* file, int a, int b, int c, int d); // 0xf473a0
extern "C" void* f_00f0cb29(void* p);                                   // 0x810000 cConnectionDialog::ctor
extern "C" char  f_00f0cc_Init(void* self, void* key, int a, unsigned b); // 0x8120d0
extern "C" void  f_00f0cc_Shutdown(void* self, unsigned a);             // 0x811ad0
extern "C" char  f_00f0cc_SetParent(void* self, void* w, int a, unsigned b); // 0x8121b0
extern "C" void* f_00f0cc_FindWin(void* self, unsigned id, int a);      // 0x8105b0
extern "C" char  f_00f0cc_SetImg(void* a, void* b, int c);              // 0x807bb0
extern "C" void  f_00f0cc_Json(void** self, void* a);                   // 0x8120d0 alt

extern "C" void SetGlobalProperty(unsigned id, float v, ...);           // 0x5ca880
extern "C" void* f_EAudioGetSystemAT(void);                             // 0xa206f0
extern "C" void  f_KillSetiEffects(unsigned a, unsigned b);             // 0x435ed0

// ---------------------------------------------------------------------------
// 0x00f0d3f0 -- trivial constant-1.0f accessor.
// ---------------------------------------------------------------------------
struct CBuilding {
    char pad[0x120];
    float func80h();                // 0x00f0d3f0
    long double scale();            // 0x00f0d400
};

// @ 0x00f0d3f0
float CBuilding::func80h()
{
    return 1.0f;
}

// ---------------------------------------------------------------------------
// 0x00f0d400 -- this->f114 * this->f60
// ---------------------------------------------------------------------------
// @ 0x00f0d400
long double CBuilding::scale()
{
    char* s = (char*)this;
    return (long double)(*(float*)(s + 0x114) * *(float*)(s + 0x60));
}

// ---------------------------------------------------------------------------
// Simulator::cPlaceableEffect
// ---------------------------------------------------------------------------
extern "C" void f_cGameData_ctor(void* self);           // 0xb18660
extern "C" void f_cSpatialObject_ctor(void* self);      // 0xc89630
extern "C" void f_cSpatialObject_dtor(void* self);      // 0xc8a420
extern "C" void f_cGameData_dtor(void* self);           // 0xb184c0
extern "C" void f_FUN_00c8b2e0(void* self);             // 0xc8b2e0
struct SpatialShutdown { void Shutdown(); };            // 0xc8b2e0 thiscall
extern "C" char f_cGameData_Write(void* self, void* s);// 0xb18590
extern "C" char f_cSpatialObject_Write(void* self, void* s); // 0xc88a90
extern "C" char f_WriteUint32(void* stream, const unsigned* p, unsigned n, int a); // 0x93aa70
extern "C" void* f_cVarListSerializer_Construct(void* a, void* b, unsigned c, ...); // 0x692f90
extern "C" char f_cVarListSerializer_Serialize(void* self, void* s); // 0x692900
extern "C" void f_operator_delete(void* p);             // 0xf47380

extern uint8_t g_vtbl_cPlaceableEffect0[];      // 0x148bc50
extern uint8_t g_vtbl_cPlaceableEffect1[];      // 0x148bc3c
extern uint8_t g_vtbl_cSpatialObject[];         // 0x148bb78

struct GameDataBase { void Ctor(); };           // 0xb18660 SP::cGameData::cGameData
struct SpatialDtor  { void Dtor(); };           // 0xc8a420 SP::cSpatialObject::~cSpatialObject
struct GameDataDtor { void Dtor(); };           // 0xb184c0 SP::cGameData::~cGameData
struct SpatialBase  { void Ctor(); };           // 0xc89630 SP::cSpatialObject::cSpatialObject

// Minimal interface shape for the visual-effect / resource objects referenced
// through m114 / m118 / m2c.  Only the vtable slots this slice touches.
struct IEffect {
    virtual void s00();                     // +0x00
    virtual void Release();                 // +0x04
    virtual void s08();                     // +0x08
    virtual void s0c(int b);                // +0x0c
    virtual char s10();                     // +0x10
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24(unsigned id, void* out);
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44(int id, void* p, int a);   // +0x44
};

struct IEffect2 {
    virtual void s00();                     // +0x00
    virtual void Release();                 // +0x04
    virtual void s08();                     // +0x08
    virtual void s0c();                     // +0x0c
    virtual char s10();                     // +0x10
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual unsigned s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();                     // +0x2c
};

struct CPlaceableEffect {
    char pad[0x108];
    void* m108;                 // +0x108
    void* m10c;                 // +0x10c
    void* m110;                 // +0x110
    void* m114;                 // +0x114
    void* m118;                 // +0x118
    char  b11c;                 // +0x11c
    char  b11d;                 // +0x11d
    char  b11e;                 // +0x11e
    char  b11f;                 // +0x11f
    char  b120;                 // +0x120
    char  b121;                 // +0x121
    char  pad122[2];
    float f124;                 // +0x124
    float f128;                 // +0x128
    float f12c;                 // +0x12c
    float f130;                 // +0x130
    float f134;                 // +0x134
    float f138;                 // +0x138
    float f13c;                 // +0x13c
    float f140;                 // +0x140
    float f144;                 // +0x144
    float f148;                 // +0x148
    float f14c;                 // +0x14c
    float f150;                 // +0x150
    float f154;                 // +0x154
    float f158;                 // +0x158
    float f15c;                 // +0x15c
    float f160;                 // +0x160
    float f164;                 // +0x164

    CPlaceableEffect();                     // 0x00f0d450
    void Shutdown();                        // 0x00f0d620
    void SetViewportScale(float v);         // 0x00f0d6a0
    bool Write(void* stream);               // 0x00f0d6e0
    void* Destroy(unsigned flags);          // 0x00f0d840
    void ReadProperties();                  // 0x00f0d8b0
};

// @ 0x00f0d450
CPlaceableEffect::CPlaceableEffect()
{
    char* s = (char*)this;
    ((GameDataBase*)s)->Ctor();
    ((SpatialBase*)(s + 0x34))->Ctor();

    *(void**)(s + 0x00) = (void*)g_vtbl_cPlaceableEffect0;
    *(void**)(s + 0x04) = (void*)g_vtbl_cPlaceableEffect1;
    *(void**)(s + 0x34) = (void*)g_vtbl_cSpatialObject;

    *(int*)(s + 0x108) = 0;
    *(int*)(s + 0x10c) = 0;
    *(int*)(s + 0x110) = 0;
    *(int*)(s + 0x114) = 0;
    *(int*)(s + 0x118) = 0;

    *(float*)(s + 0x124) = 1.0f;
    *(float*)(s + 0x12c) = 2.0f;
    *(float*)(s + 0x130) = 1.0f;
    *(float*)(s + 0x134) = 1.0f;
    *(float*)(s + 0x148) = 1.0f;

    *(char*)(s + 0x11c) = 0;
    *(char*)(s + 0x11d) = 0;
    *(char*)(s + 0x11e) = 0;
    *(char*)(s + 0x11f) = 0;
    *(char*)(s + 0x120) = 0;
    *(char*)(s + 0x121) = 0;

    *(float*)(s + 0x128) = 0.0f;
    *(float*)(s + 0x138) = 0.0f;
    *(float*)(s + 0x13c) = 5.0f;
    *(float*)(s + 0x140) = 0.0f;
    *(float*)(s + 0x144) = 5.0f;
    *(float*)(s + 0x14c) = 3.402823466e+38f;    // FLT_MAX

    *(float*)(s + 0x150) = g_16c7fb4 * 7.0f;
    *(float*)(s + 0x154) = g_16c7fb8 * 7.0f;
    *(float*)(s + 0x158) = g_16c7fbc * 7.0f;
    *(float*)(s + 0x15c) = g_16c7fa8;
    *(float*)(s + 0x160) = g_16c7fac;
    *(float*)(s + 0x164) = g_16c7fb0;
}

// @ 0x00f0d620
void CPlaceableEffect::Shutdown()
{
    if (*(IEffect**)((char*)this + 0x118) != 0) {
        if ((*(IEffect**)((char*)this + 0x118))->s10()) {
            (*(IEffect**)((char*)this + 0x118))->s0c(*(int*)((char*)g_16c7aa4 + 0xcc) == 1);
            IEffect* p = *(IEffect**)((char*)this + 0x118);
            if (p != 0) {
                *(void**)((char*)this + 0x118) = 0;
                p->Release();
            }
        }
    }
    IEffect2* q = *(IEffect2**)((char*)this + 0x2c);
    if (q != 0) {
        *(void**)((char*)this + 0x2c) = 0;
        q->Release();
    }
    ((SpatialShutdown*)((char*)this + 0x34))->Shutdown();
}

// @ 0x00f0d6a0
void CPlaceableEffect::SetViewportScale(float v)
{
    f124 = v;
    if (*(IEffect**)((char*)this + 0x118) != 0) {
        if ((*(IEffect**)((char*)this + 0x118))->s10())
            (*(IEffect**)((char*)this + 0x118))->s44(0xf, &f124, 1);
    }
}

// @ 0x00f0d840
void* CPlaceableEffect::Destroy(unsigned flags)
{
    char* s = (char*)this;
    char* sub = s + 0x34;
    *(void**)(s + 0x00) = (void*)g_vtbl_cPlaceableEffect0;
    *(void**)(s + 0x04) = (void*)g_vtbl_cPlaceableEffect1;
    *(void**)sub = (void*)g_vtbl_cSpatialObject;

    IEffect* p = *(IEffect**)(s + 0x118);
    if (p)
        p->Release();
    IEffect2* q = *(IEffect2**)(s + 0x114);
    if (q)
        q->Release();
    ((SpatialDtor*)sub)->Dtor();
    ((GameDataDtor*)s)->Dtor();
    if (flags & 1)
        f_operator_delete(s);
    return s;
}

// ---------------------------------------------------------------------------
// SP palette-item UI classes (local minimal layouts; offsets from this slice).
// ---------------------------------------------------------------------------
extern uint8_t g_vtbl_OneClickPaint0[];      // 0x148bb3c  cISPPaletteItemUI
extern uint8_t g_vtbl_OneClickPaint1[];      // 0x148bb20  IWinProc
extern uint8_t g_vtbl_OneClickPaint2[];      // 0x148bb10  RefCountVTemplate<int>
extern uint8_t g_vtbl_OneClickPaint3[];      // 0x148bb00  IMsgHandler
extern uint8_t g_vtbl_PICTSel[];             // 0x13eb384  cSPPaletteItemUISelectable subobject
extern uint8_t g_vtbl_IMsgHandler[];         // 0x13eb394  IMsgHandler (dtor restore)

struct IRefObj {
    virtual void s0();
    virtual int  AddRef();
    virtual int  Release();
};

struct PaletteItemUIBase {                    // SP::cSPPaletteItemUI (0x20 bytes)
    void BaseCtor();                          // 0x5c6bf0
    void BaseDtor();                          // 0x5c6c50
    void BaseShutdown();                      // 0x5c6d20
    void BaseInit(void* item, void* win, void* a, void* info); // 0x5c6ca0
};

struct IMessageServer {
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual void s4();
    virtual void Post(unsigned key, void* p, int a);       // +0x14
    virtual void s6();  virtual void s7();
    virtual void AddHandler(void* p, unsigned key);        // +0x20
    virtual void s9();  virtual void s10();
    virtual void RemoveHandler(void* p, unsigned key, unsigned code); // +0x2c
};

struct IWindow {
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
    virtual void s8();  virtual void s9();  virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s30();
    virtual void SetFlag(int flag, int value);             // +0x7c
    virtual void s33() ; virtual void s34(); virtual void s35(); virtual void s36();
    virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40();
    virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
    virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48();
    virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52();
    virtual void s53(); virtual void s54(); virtual void s55(); virtual void s56();
    virtual void s57(); virtual void s58(); virtual void s59(); virtual void s60();
    virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64();
    virtual void SetIcon(void* p);                         // +0x104
};

struct PaletteItemUIOneClickPaint {
    char pad[0x34];
    PaletteItemUIOneClickPaint* Ctor();                            // 0x00f0cdd0
    void* Dtor(unsigned flags);                                    // 0x00f0ce10
    void Shutdown();                                               // 0x00f0cc80
    bool DoMessage(void* window, void* message);                   // 0x00f0cce0
    void Init(void* item, void* parent, void* a, void* info);      // 0x00f0cad0
    int  HandleMessage(unsigned messageID, void* message);         // 0x00f0ce60
};

struct cSPUILayout {
    char pad[0x30];
    char Init(void* key, int a, unsigned b);              // 0x8120d0
    void Shutdown(unsigned a);                            // 0x811ad0
    char SetParentWin(void* w, int a, unsigned b);        // 0x8121b0
    void* FindWindowByID(unsigned id, int a);             // 0x8105b0
};

// ---------------------------------------------------------------------------
// SP property helpers + terrain-editor helpers used by the handlers.
// ---------------------------------------------------------------------------
struct SpVec { void* mpBegin; void* mpEnd; void* mpCap; int mAlloc[2]; };

namespace SP {
bool GetBoolProperty(void* list, unsigned key, bool* out);          // 0x407190
bool GetPropertyAsVector3(void* list, unsigned key, void* out);     // 0x6a1110
bool GetPropertyAsVector4(void* list, unsigned key, void* out);     // 0x6a1160
bool GetPropertyAsFloatArray(void* list, unsigned key, void* a, void* b); // 0x6a08b0
bool GetPropertyT(void* list, unsigned key, int* out);              // 0x40cf10
}  // namespace SP

struct IPropertyMgr {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual char Get2(void* key, void** out, int a, int b, int c);  // +0xc
};
struct IPropertyList {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8();
    virtual char Query(unsigned key, void* out);                    // +0x24
};
struct IEffectsManager {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10();
    virtual void Create(unsigned id, int a, void** out);            // +0x2c
};
struct cTerrainEditor {
    void UpdateEditedScript(void* begin, void* end);
    void* mpBegin; void* mpEnd;
};
struct CMWModelVec {
    void* mpBegin; void* mpEnd; void* mpCap; int mAlloc[2];
    void Reserve(unsigned key);
};

extern "C" void  f_00eed0b0(void* a, void* b, void* c);            // 0xeed0b0 PropertyPairRead
extern "C" void* f_EapdObjectError();                              // 0x8de1a0
extern "C" float* f_PropertyGetFloat(void* prop);                  // 0x41ea70
extern "C" char*  f_PropertyGetKeyArray(void* prop);
extern "C" unsigned* f_PropertyGetWString(void* prop);
extern "C" void* f_EffectsManager();                               // SP::EffectsManager
extern "C" void* f_PropertyManager_Get(unsigned a, unsigned b, int c); // 0x67de30 helper
extern "C" void  f_00f33bf0();
extern "C" void  f_00f32240(void* self, float v);
extern "C" void  f_00f31d80(void* self, float v);
extern "C" void  f_00f31de0(void* self, float v);
extern "C" void  f_00f31c20(void* self, int v);
extern "C" void  f_00f31c40(void* self, int v);
extern "C" void  f_00f31cb0(void* self, int v);
extern "C" void  f_00f31d20(void* self, int v);
extern "C" void  f_00f31d50(void* self, int v);
extern "C" void  f_00f343a0(void* self, int v);
extern "C" void  f_00f321a0(void* self, void* p);
extern "C" void  f_00f321f0(void* self, void* p);
extern "C" void  f_00f32100(void* self, void* p);
extern "C" void  f_00f32150(void* self, void* p);
extern "C" void  f_00f344e0(void* self, void* a, void* b);
extern "C" void  f_00f374a0(void* self, void* p);
extern "C" void  f_00f352c0(void* self, void* p);
extern "C" void  f_00f31ea0(void* self);
extern "C" void  f_00f34560(void* self);
extern "C" void  f_004548d0(void* p);
extern "C" void  f_006a0990(void* list, unsigned key, void* a, void* b);
extern "C" void  f_004afc80(void* v, int n);
extern "C" void  f_004d04f0(void* a, void* b, int c);
extern "C" void  f_00473810(void* v);
extern "C" void  f_0056fee0(int a, int b, int c);
extern "C" void  f_00540520(void* p);
extern "C" void  f_004e1bf0(void* p);

// @ 0x00f0cdd0
PaletteItemUIOneClickPaint* PaletteItemUIOneClickPaint::Ctor()
{
    ((PaletteItemUIBase*)this)->BaseCtor();
    *(void* volatile*)((char*)this + 0x20) = (void*)g_vtbl_PICTSel;
    int zero = 0;
    *(void* volatile*)((char*)this + 0x00) = (void*)g_vtbl_OneClickPaint0;
    *(void* volatile*)((char*)this + 0x0c) = (void*)g_vtbl_OneClickPaint1;
    *(void* volatile*)((char*)this + 0x10) = (void*)g_vtbl_OneClickPaint2;
    *(void* volatile*)((char*)this + 0x20) = (void*)g_vtbl_OneClickPaint3;
    *(volatile int*)((char*)this + 0x24) = zero;
    *(volatile int*)((char*)this + 0x28) = zero;
    *(volatile int*)((char*)this + 0x2c) = zero;
    *(volatile int*)((char*)this + 0x30) = zero;
    return this;
}

// @ 0x00f0ce10
void* PaletteItemUIOneClickPaint::Dtor(unsigned flags)
{
    char* s = (char*)this;
    *(void* volatile*)(s + 0x00) = (void*)g_vtbl_OneClickPaint0;
    *(void* volatile*)(s + 0x0c) = (void*)g_vtbl_OneClickPaint1;
    *(void* volatile*)(s + 0x10) = (void*)g_vtbl_OneClickPaint2;
    *(void* volatile*)(s + 0x20) = (void*)g_vtbl_OneClickPaint3;
    volatile void* p = *(void* volatile*)(s + 0x24);
    if (p)
        ((IRefObj*)p)->Release();
    *(void**)(s + 0x20) = (void*)g_vtbl_IMsgHandler;
    ((PaletteItemUIBase*)s)->BaseDtor();
    if (flags & 1)
        f_operator_delete(s);
    return s;
}

// @ 0x00f0cc80
void PaletteItemUIOneClickPaint::Shutdown()
{
    char* s = (char*)this;
    void* sub = s ? (s + 0x20) : 0;
    IMessageServer* ms = (IMessageServer*)f_MessageServer();
    ms->RemoveHandler(sub, 0x743b6fa, 0xffffd8f1);

    cSPUILayout* pcVar1 = *(cSPUILayout**)(s + 0x24);
    if (pcVar1) {
        pcVar1->Shutdown(1);
        pcVar1 = *(cSPUILayout**)(s + 0x24);
        if (pcVar1) {
            *(void**)(s + 0x24) = 0;
            ((IRefObj*)pcVar1)->Release();
        }
    }
    ((PaletteItemUIBase*)s)->BaseShutdown();
}

// @ 0x00f0cce0
bool PaletteItemUIOneClickPaint::DoMessage(void* window, void* message)
{
    char* s = (char*)this;
    int* msg = (int*)message;
    int zero = 0;
    switch (msg[2]) {
    case 7:
        {
            if (msg[6] != 1000)
                break;
            IMessageServer* ms = (IMessageServer*)f_MessageServer();
            ms->Post(0x743b6fa, s - 0xc, zero);
            void* at = f_EAudioGetSystemAT();
            unsigned r = zero;
            if (at)
                r = ((IEffect2*)at)->s20();
            f_KillSetiEffects(0xa03e74b2, r);
            float nv = (float)(g_16c7f54 == 0.0f);
            g_16c7f54 = nv;
            SetGlobalProperty(0x66fb5cf, nv);
            return true;
        }
    case 0x1b:
    case 0x1c:
        {
            cSPUILayout* lay = *(cSPUILayout**)(s + 0x18);
            void* w = lay->FindWindowByID(0x743bba8, 1);
            if (w != (void*)zero) {
                ((IWindow*)w)->SetFlag(1, msg[2] == 0x1b);
                return true;
            }
        }
    }
    return false;
}

// @ 0x00f0cad0
void PaletteItemUIOneClickPaint::Init(void* item, void* parent, void* a, void* info)
{
    char* s = (char*)this;
    ((PaletteItemUIBase*)s)->BaseInit(item, parent, a, info);

    unsigned local0 = 0xb74c6b64;
    unsigned local1 = 0x510a95b;
    unsigned local2 = 0x40464100;

    void* obj = f_EAAllocate(0x18, (const char*)0x013f6b3c, 0, 0, 0, 0);
    void* pcVar4;
    if (obj)
        pcVar4 = f_00f0cb29(obj);
    else
        pcVar4 = 0;

    void* pcVar1 = *(void**)(s + 0x24);
    if (pcVar4 != pcVar1) {
        if (pcVar4)
            ((IRefObj*)pcVar4)->AddRef();
        *(void**)(s + 0x24) = pcVar4;
        if (pcVar1)
            ((IRefObj*)pcVar1)->Release();
    }

    char ok = (*(cSPUILayout**)(s + 0x24))->Init(&local0, 0, 0x5b598fa);
    if (ok == 0) {
        (*(cSPUILayout**)(s + 0x24))->Shutdown(1);
        void* q = *(void**)(s + 0x24);
        if (q) {
            *(void**)(s + 0x24) = 0;
            ((IRefObj*)q)->Release();
        }
        return;
    }

    (*(cSPUILayout**)(s + 0x24))->SetParentWin(parent, 1, 0x5b598fa);
    *(unsigned*)(s + 0x28) = *(unsigned*)((char*)item + 0x0c);
    *(void**)(s + 0x2c) = *(void**)((char*)item + 0x10);
    *(void**)(s + 0x30) = *(void**)((char*)item + 0x14);

    void* w = (*(cSPUILayout**)(s + 0x24))->FindWindowByID(0x743c2e8, 1);
    if (w) {
        unsigned img[3];
        img[0] = *(unsigned*)(s + 0x28);
        img[1] = 0x2f7d0004;
        img[2] = 0x86c40741;
        f_00f0cc_SetImg(w, img, -1);
        ((IWindow*)w)->SetIcon((void*)(s + 0x0c));
    }

    void* w1 = (*(cSPUILayout**)(s + 0x24))->FindWindowByID(0x743bba8, 1);
    if (w1)
        ((IWindow*)w1)->SetFlag(1, 0);
    void* w2 = (*(cSPUILayout**)(s + 0x24))->FindWindowByID(0x743bb80, 1);
    if (w2)
        ((IWindow*)w2)->SetFlag(1, 0);

    IMessageServer* ms = (IMessageServer*)f_MessageServer();
    ms->AddHandler(s + 0x20, 0x743b6fa);
}

// @ 0x00f0ce60
int PaletteItemUIOneClickPaint::HandleMessage(unsigned messageID, void* message)
{
    char* s = (char*)this;
    if (messageID != 0x743b6fa)
        return 0;

    IWindow* w = (IWindow*)(*(cSPUILayout**)(s + 0x04))->FindWindowByID(0x743bb80, 1);
    if (w)
        w->SetFlag(1, message == (s - 0x20));
    if (message != (s - 0x20))
        return 0;
    if (*(int*)((char*)g_16c7aa4 + 0x18) == 0)
        return 0;

    cTerrainEditor* ed = *(cTerrainEditor**)(s + 0x18);
    if (!ed)
        return 0;

    bool  v = false;
    char  a8[0xc];
    char  a4[0xc];
    char  a0[0xc];
    char  a3[0x18];
    CMWModelVec  m1;
    CMWModelVec  m2;
    IPropertyList* pl = (IPropertyList*)f_PropertyManager_Get(*(unsigned*)(s + 0x08), *(unsigned*)(s + 0x10), 0);
    if (!pl)
        goto cleanup;

    {
        SP::GetBoolProperty(pl, 0x7b18058, &v);
        SP::GetPropertyAsVector3(pl, 0x3a23f98, a8);
        int i = 0;
        SP::GetPropertyT(pl, 0x7163782e, &i);
        m1.Reserve(0x4e13cb7);
        f_004548d0(m1.mpBegin);
        ed->UpdateEditedScript(m2.mpBegin, m2.mpEnd);
        m2.Reserve(0x40cf84f);
        f_004548d0(m2.mpBegin);
        ed->UpdateEditedScript(m1.mpBegin, m1.mpEnd);
    }

    f_00f33bf0();

    float f0 = *(float*)(a8 + 0x00);
    float f1 = *(float*)(a8 + 0x04);
    float f2 = *(float*)(a8 + 0x08);
    if (0.0f <= f0) f_00f32240(this, f0);
    if (0.0f <= f1) f_00f31d80(this, f1);
    if (0.0f <= f2) f_00f31de0(this, f2);

    if (!v) {
        f_00f31c20(this, 0);
        float r[4];
        SP::GetPropertyAsVector4(pl, 0xf20664ef, r);
        if (0.0f <= r[0]) f_00f31c40(this, (int)r[0]);
        if (0.0f <= r[1]) f_00f31cb0(this, (int)r[1]);
        if (0.0f <= r[2]) f_00f31d20(this, (int)r[2]);
        if (0.0f <= r[3]) f_00f31d50(this, (int)r[3]);
        f_00f343a0(this, 1);
        f_00f31c20(this, 1);
    } else {
        SpVec vecV;
        SpVec vecF;
        char  x[0x4c];
        SP::GetPropertyAsVector3(pl, 0xb6929c95, x + 0x00);
        SP::GetPropertyAsVector3(pl, 0xb6929c94, x + 0x0c);
        SP::GetPropertyAsVector3(pl, 0x968c496b, x + 0x18);
        SP::GetPropertyAsVector3(pl, 0x968c496a, x + 0x24);
        f_006a0990(pl, 0xb6929c93, &vecV, &vecF);
        SP::GetPropertyAsFloatArray(pl, 0xb6929c92, &vecF, &vecV.mpBegin);
        f_004afc80(&vecF, (int)vecF.mpEnd);
        f_004d04f0(vecF.mpBegin, vecF.mpEnd, 0);
        f_00473810(vecV.mpBegin);
        f_0056fee0(0, (int)vecV.mpEnd * 0xc, 0);
        f_00f31c20(this, 1);
        f_00f321a0(this, x + 0x00);
        f_00f321f0(this, x + 0x0c);
        f_00f32100(this, x + 0x24);
        f_00f32150(this, x + 0x18);
        f_00f344e0(this, x + 0x30, x + 0x3c);
        f_00540520(x + 0x30);
        f_004e1bf0(x + 0x3c);
    }

    f_00f374a0(this, a0);

cleanup:
    if (*(void**)(s + 0x114))
        ((IRefObj*)*(void**)(s + 0x114))->Release();
    return 1;
}

// @ 0x00f0d8b0
void CPlaceableEffect::ReadProperties()
{
    char* s = (char*)this;
    f_00eed0b0(s + 0x108, s + 0x130, s + 0x134);

    IPropertyMgr* mgr = (IPropertyMgr*)f_EapdObjectError();
    void* old = *(void**)(s + 0x114);
    void** slot = (void**)(s + 0x114);
    if (old) {
        *slot = 0;
        ((IRefObj*)old)->Release();
    }
    mgr->Get2(s + 0x108, slot, 0, 0, 0);

    IPropertyList* pl = (IPropertyList*)*slot;
    if (!pl)
        return;

    void* prop = 0;
    if (pl->Query(0xcce9e754, &prop) && *(short*)((char*)prop + 0x12) == 0xd)
        *(float*)(s + 0x148) = *f_PropertyGetFloat(prop);

    SP::GetPropertyAsVector3(pl, 0xb14ca983, s + 0x150);
    SP::GetPropertyAsVector3(pl, 0x4888547a, s + 0x15c);

    if (pl->Query(0xc9a583f6, &prop) && *(short*)((char*)prop + 0x12) == 0xd)
        *(float*)(s + 0x128) = *f_PropertyGetFloat(prop);
    if (pl->Query(0x8d3ef5d0, &prop) && *(short*)((char*)prop + 0x12) == 0xd)
        *(float*)(s + 0x138) = *f_PropertyGetFloat(prop);
    if (pl->Query(0x4102db36, &prop) && *(short*)((char*)prop + 0x12) == 0xd)
        *(float*)(s + 0x13c) = *f_PropertyGetFloat(prop);
    if (pl->Query(0x0eb4af2d, &prop) && *(short*)((char*)prop + 0x12) == 0xd)
        *(float*)(s + 0x140) = *f_PropertyGetFloat(prop);
    if (pl->Query(0x298a6aff, &prop) && *(short*)((char*)prop + 0x12) == 0xd)
        *(float*)(s + 0x144) = *f_PropertyGetFloat(prop);
    if (pl->Query(0x30c04a2a, &prop) && *(short*)((char*)prop + 0x12) == 1)
        *(char*)(s + 0x11e) = *f_PropertyGetKeyArray(prop);

    if (pl->Query(0x42b43056, &prop) && *(short*)((char*)prop + 0x12) == 10) {
        unsigned id = *f_PropertyGetWString(prop);
        IEffectsManager* em = (IEffectsManager*)f_EffectsManager();
        void* q = *(void**)(s + 0x118);
        if (q) {
            *(void**)(s + 0x118) = 0;
            ((IRefObj*)q)->Release();
        }
        em->Create(id, 0, (void**)(s + 0x118));
    }
}

// @ 0x00f0d6e0
bool CPlaceableEffect::Write(void* stream)
{
    char* s = (char*)this;
    unsigned tag = 0x7b38ba7;
    void** st = *(void***)stream;
    void* inner = ((void* (*)(void*))st[0x20 / 4])(stream);
    void** it = *(void***)inner;
    void* wr = ((void* (*)(void*))it[0x18 / 4])(inner);
    f_WriteUint32(wr, &tag, 1, 0);

    bool ok = f_cGameData_Write(this, stream) &&
              f_cSpatialObject_Write(s + 0x34, stream);

    if (ok)
        return f_cVarListSerializer_Serialize(0, stream) != 0;
    return false;
}
