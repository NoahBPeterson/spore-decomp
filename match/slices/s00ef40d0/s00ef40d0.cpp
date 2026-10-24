// slice s00ef40d0: SP::cSPUIAssetView editor-panel helpers (layout refresh, message handler,
// shutdown, thumbnail refresh), the cILayer/cContentValidationSummarizer key-provider object
// (ctor/dtor/query/key) and the SPUI window-image helper.
// UI module: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-.
#include <intrin.h>

typedef unsigned char  uchar;
typedef unsigned int   uint;
typedef unsigned short ushort;

// ---------------------------------------------------------------------------
// Resource key: {instance id, type hash, payload hash} (12 bytes, returned by value).
// ---------------------------------------------------------------------------
struct ResKey {
    uint mId;      // 0x00
    uint mType;    // 0x04
    uint mSub;     // 0x08
};

struct Pair8 {      // 8-byte register return (eax:edx)
    uint mLo;
    uint mHi;
};

// ---------------------------------------------------------------------------
// Window interface (only the vtable slots this slice touches are named).
// ---------------------------------------------------------------------------
inline void  WndAddRef(void* p)    { ((void  (__thiscall*)(void*))(*(void***)p)[0x00/4])(p); }
inline void  WndRelease(void* p)   { ((void  (__thiscall*)(void*))(*(void***)p)[0x04/4])(p); }
inline void  WndReleaseVt8(void* p){ ((void  (__thiscall*)(void*))(*(void***)p)[0x08/4])(p); }
inline int   WndGetHash(void* p)   { return ((int (__thiscall*)(void*))(*(void***)p)[0x24/4])(p); }
inline uint  WndGetHashU(void* p)  { return ((uint (__thiscall*)(void*))(*(void***)p)[0x24/4])(p); }
inline int   WndIsVisible(void* p) { return ((int (__thiscall*)(void*))(*(void***)p)[0x28/4])(p); }
inline void* WndGetArea(void* p)   { return ((void*(__thiscall*)(void*))(*(void***)p)[0x38/4])(p); }
inline void  WndSetArea(void* p, void* r) { ((void (__thiscall*)(void*, void*))(*(void***)p)[0x6c/4])(p, r); }
inline void  WndShow(void* p, int a, int b) { ((void (__thiscall*)(void*, int, int))(*(void***)p)[0x7c/4])(p, a, b); }
inline void* WndGetChild(void* p)  { return ((void*(__thiscall*)(void*))(*(void***)p)[0x10/4])(p); }
inline void* WndFindChild(void* p, int id, int recurse)
{
    return ((void*(__thiscall*)(void*, int, int))(*(void***)p)[0xf0/4])(p, id, recurse);
}
inline void  WndHookEvent(void* p, void* owner)
{
    ((void (__thiscall*)(void*, void*))(*(void***)p)[0x108/4])(p, owner);
}
inline int   WndGetSenderType(void* p) { return ((int (__thiscall*)(void*))(*(void***)p)[0x1c/4])(p); }
inline void* WndGetItem(void* p, void* msg, int flag)
{
    return ((void*(__thiscall*)(void*, void*, int))(*(void***)p)[0x10/4])(p, msg, flag);
}
inline void* WndGetItem1(void* p, int flag)
{
    return ((void*(__thiscall*)(void*, int))(*(void***)p)[0x10/4])(p, flag);
}
inline void* WndGetSlot20(void* p)  { return ((void*(__thiscall*)(void*))(*(void***)p)[0x20/4])(p); }
inline void  WndSetSlot34(void* p, void* a)
{
    ((void (__thiscall*)(void*, void*))(*(void***)p)[0x34/4])(p, a);
}
inline void  WindowManager_SetCurrent(void* mgr, void* child)
{
    ((void (__thiscall*)(void*, void*))(*(void***)mgr)[0x10/4])(mgr, child);
}
inline void  MessageServer_Send(void* srv, int msg, void* data, int flag)
{
    ((void (__thiscall*)(void*, int, void*, int))(*(void***)srv)[0x14/4])(srv, msg, data, flag);
}
inline void  WndGetKey(void* p, ResKey* out)
{
    ((void (__thiscall*)(void*, ResKey*))(*(void***)p)[0x18/4])(p, out);
}
inline uchar ResourceMan_Query(void* mgr, ResKey* key, int a, int b, int c, int d, int e)
{
    return ((uchar (__thiscall*)(void*, ResKey*, int, int, int, int, int))(*(void***)mgr)[0x0c/4])
        (mgr, key, a, b, c, d, e);
}
inline uchar PropertyManager_Get(void* pm, int a, int b, void** out)
{
    return ((uchar (__thiscall*)(void*, int, int, void**))(*(void***)pm)[0x2c/4])(pm, a, b, out);
}
extern void __fastcall cString_Ctor(void* self);   // 0x006b5060
extern void __fastcall cString_Dtor(void* self);   // 0x006b5240

// Release an AutoRefCount slot that holds a window (Release is vtable slot 1).
inline void ResetWindow(void** slot)
{
    void* p = *slot;
    if (p) {
        *slot = 0;
        WndRelease(p);
    }
}

// AutoRefCount assignment with window refcounting (AddRef slot 0 / Release slot 1).
inline void AssignWindow(void** slot, void* p)
{
    void* old = *slot;
    if (p != old) {
        if (p) WndAddRef(p);
        *slot = p;
        if (old) WndRelease(old);
    }
}

// ---------------------------------------------------------------------------
// cSPUILayout: layout object whose windows are found by hashed id.
// ---------------------------------------------------------------------------
struct cSPUILayout {
    void* mpVtbl;                                   // 0x000
    void* FindWindowByID(int id, int recursive);    // 0x8105b0
};

// ---------------------------------------------------------------------------
// Generic UI helper entry points.
// ---------------------------------------------------------------------------
extern void* __cdecl SP_PropertyManager();                       // 0x0067de30
extern void* __cdecl SP_WindowManager();                         // 0x0067caa0
extern void* __cdecl SP_MessageServer();                         // 0x0067dcc0
extern void* __cdecl ResourceMan_GetManager();                   // 0x0067dcd0
extern void* __cdecl FUN_0067de40();                             // 0x0067de40
extern void* __cdecl SPUIHelpers_GetImageFromLayout(void* layout, int id);   // 0x008061c0
extern uchar __cdecl FUN_008068d0(void* wnd, void* image, int flag);         // 0x008068d0
extern uchar __cdecl SetWindowImage(void* wnd, ResKey* key, int flag);       // 0x00807bb0
// AutoRefCount<T>: single pointer plus a refcounting assignment (0x00b5f950).
struct AutoRefCount {
    void* mpObject;                                     // 0x00
    AutoRefCount& operator=(void* p);                   // 0x00b5f950
    operator void*() const { return mpObject; }
};
extern uchar __cdecl UI_CalloutMessageBox(void* self, int msg);              // 0x00809db0
extern __int64 __fastcall Meta_GetId(void* self);                            // 0x005508a0
extern void __fastcall AssetView_LoadLayout(void* self);                     // 0x0065a070
extern void __fastcall AssetView_RefreshDetails(void* self);                 // 0x00ef3e40
extern void __fastcall AssetView_Refresh(void* self);                        // 0x00ef3a60
extern void __fastcall cSPUIAssetVerbs_Shutdown(void* self);                 // 0x006566f0
extern void __fastcall FUN_00f47040(void* self);                             // 0x00f47040
extern void __fastcall TextZoomName_Shutdown(void* self);                    // 0x00834e30
extern void __fastcall TextZoomName_Activate(void* self, int a);             // 0x00834a00
extern void __fastcall TextZoomName_Deactivate(void* self, int a);           // 0x00834c60
extern void __fastcall Layer_Init(void* self, void* dummy, void* param);     // 0x006412c0
extern void __fastcall Layer_Shutdown(void* self);                           // 0x006412a0
extern void __cdecl operator_delete(void* p);                                // 0x00f47380
extern void __cdecl SP_GetPropertyAsText(void* bag, int key, void* out);     // 0x006a1360
extern void __cdecl SP_GetPropertyAsKeyInstance(void* bag, int key, int* out); // 0x006a12a0
extern void __cdecl SP_GetPropertyAsKey(void* bag, int key, ResKey* out);    // 0x006a1250

extern int VTABLE_0148b2d0;    // cLayerKeyProvider primary vtable
extern int VTABLE_0148b2c0;    // cILayer sub-object vtable
extern int VTABLE_0148b2b0;    // cContentValidationSummarizer sub-object vtable
extern int VTABLE_013f1ab0;    // cILayer base vtable
extern int VTABLE_013ec458;    // cContentValidationSummarizer base vtable
extern uint DAT_015acdf4;      // shared resource type hash

// ---------------------------------------------------------------------------
// cLayerKeyProvider: 0x4c-byte object with a cILayer and a
// cContentValidationSummarizer sub-object and three loaded resource keys.
// ---------------------------------------------------------------------------
struct cString {
    int mStorage[5];        // 0x00..0x13
};

struct cLayerKeyProvider {
    void*    mpVtbl;        // 0x000
    int      m04;           // 0x004
    int      m08;           // 0x008
    int      m0C;           // 0x00c
    void*    mpLayerVt;     // 0x010  cILayer vtable
    void*    mpSummaryVt;   // 0x014  cContentValidationSummarizer vtable
    int      m18;           // 0x018
    cString  mName;         // 0x01c
    int      mKeyInstance;  // 0x030
    ResKey   mKeyA;         // 0x034
    ResKey   mKeyB;         // 0x040
};

// ---------------------------------------------------------------------------
// Asset noun (the object whose type hash selects the displayed image).
// ---------------------------------------------------------------------------
struct AssetNoun {
    void* mpVtbl;           // 0x000
    char  mPad04[0x79 - 4]; // 0x004..0x078
    uchar m79;              // 0x079
    uchar m7A;              // 0x07a
    uchar m7B;              // 0x07b
    uchar m7C;              // 0x07c
    char  mPad7D[0x88 - 0x7d]; // 0x07d..0x087
    int   m88;              // 0x088
};

// Embedded text/field object at +0x0c (vtable slot 1 takes a value and a message id).
struct cField {
    void* mpVtbl;           // 0x00
};
inline void FieldSet(cField* f, int value, int id)
{
    ((void (__thiscall*)(cField*, int, int))(*(void***)f)[1])(f, value, id);
}

// Flags array reached through the +0xa4 pointer (the thumbnail slots' "used" flags).
struct NounFlagBlock {
    int mPad[0x1a];         // 0x000..0x067
    int mFlags[4];          // 0x068
};

// ---------------------------------------------------------------------------
// cAssetPanel: the editor asset view (cSPUIAssetView-derived), 0x14c bytes.
// ---------------------------------------------------------------------------
struct cAssetPanel {
    void*        mpVtbl0;       // 0x000
    void*        mpVtbl4;       // 0x004
    int          m08;           // 0x008
    cField       mField;        // 0x00c
    char         mPad10[0x10];  // 0x010..0x01f
    cSPUILayout* mpViewLayout;  // 0x020  window layout used by the refresh
    char         mPad24[0x0c];  // 0x024..0x02f
    cSPUILayout* mpLayout;      // 0x030  layout used by the image helpers
    char         mPad34[0x04];  // 0x034..0x037
    void*        mpWin38;       // 0x038
    void*        mpWin3C;       // 0x03c
    void*        mpWin40;       // 0x040
    void*        mpWin44;       // 0x044
    void*        mpWin48;       // 0x048
    void*        mpWin4C;       // 0x04c
    void*        mpWin50;       // 0x050
    void*        mpWin54;       // 0x054
    void*        mpWin58;       // 0x058
    void*        mpWinA[4];     // 0x05c..0x06b
    void*        mpWinB[4];     // 0x06c..0x07b
    void*        mpWin7C;       // 0x07c
    void*        mpWin80;       // 0x080
    void*        mpWin84;       // 0x084
    void*        mpWin88;       // 0x088
    void*        mpWin8C;       // 0x08c
    void*        mpWin90;       // 0x090
    void*        mpVerbs94;     // 0x094
    void*        mpVerbs98;     // 0x098
    void*        mpNoun9C;      // 0x09c
    void*        mpNounA0;      // 0x0a0
    NounFlagBlock* mpFlagsA4;   // 0x0a4
    void*        mpObjA8;       // 0x0a8
    void*        mpZoomAC;      // 0x0ac
    void*        mpZoomB0;      // 0x0b0
    char         mPadB4[0x0c];  // 0x0b4..0x0bf
    uchar        mC0;           // 0x0c0
    char         mPadC1[0x5f];  // 0x0c1..0x11f
    AssetNoun*   mpNoun120;     // 0x120
    void*        mpWin124;      // 0x124
    void*        mpWin128;      // 0x128
    void*        mpWin12C;      // 0x12c
    void*        mpWin130;      // 0x130
    void*        mpWin134;      // 0x134
    void*        mpWin138;      // 0x138
    void*        mpWin13C;      // 0x13c
    void*        mpWin140;      // 0x140
    void*        mpWin144;      // 0x144
    void*        mpWin148;      // 0x148
};

// Message record handed to the handler (type at +8, window payload at +4).
struct Msg {
    void* mpSender;     // 0x00
    void* mpWindow;     // 0x04
    uint  mType;        // 0x08
    int   mSub;         // 0x0c
};

// ---------------------------------------------------------------------------
// @ 0x00ef40d0  refresh the layout: re-resolve every window and update the
// visibility of the detail controls.
// ---------------------------------------------------------------------------
void __fastcall FUN_00ef40d0(cAssetPanel* self)
{
    AssetView_LoadLayout(self);
    AssignWindow(&self->mpWin12C, self->mpViewLayout->FindWindowByID(0x7bb81c0, 1));
    AssignWindow(&self->mpWin128, self->mpViewLayout->FindWindowByID(0x7e0ba78, 1));
    AssignWindow(&self->mpWin130, self->mpViewLayout->FindWindowByID(0x7bb9c30, 1));
    AssignWindow(&self->mpWin134, self->mpViewLayout->FindWindowByID(0x7bb9c10, 1));
    AssignWindow(&self->mpWin138, self->mpViewLayout->FindWindowByID(0x7bb9c18, 1));
    AssetView_RefreshDetails(self);
    AssignWindow(&self->mpWin13C, self->mpViewLayout->FindWindowByID(0x7bfe394, 1));
    if (self->mpWin13C != 0) {
        if (WndGetHash(self->mpNoun120) != 0x24720859) {
            WndShow(self->mpWin13C, 1, self->mpNoun120->m79 == 0);
        }
    }
    AssignWindow(&self->mpWin140, self->mpViewLayout->FindWindowByID(0xb498717e, 1));
    AssignWindow(&self->mpWin144, self->mpViewLayout->FindWindowByID(0x7e0b9b0, 1));
    AssignWindow(&self->mpWin148, self->mpViewLayout->FindWindowByID(0x7ee12a8, 1));
    if (self->mpNoun120 != 0) {
        int n = self->mpNoun120->m88;
        if (n != 0x7fffffff) {
            if (n > 0) {
                WndShow(self->mpWin144, 1, 1);
            } else if (n < 0) {
                WndShow(self->mpWin148, 1, 1);
            }
        }
    }
    AssignWindow(&self->mpWin124, self->mpViewLayout->FindWindowByID(0x7cd2a58, 1));
    AssetView_Refresh(self);
    if (self->mpWinA[0] == 0) {
        return;
    }
    if (self->mpWinA[1] == 0) {
        return;
    }
    {
        AssetNoun* noun = self->mpNoun120;
        if (noun->m7C != 0) {
            WndShow(self->mpWin140, 1, 1);
            WndShow(self->mpWinA[0], 1, 0);
            WndShow(self->mpWinA[1], 1, 0);
        } else if (noun->m7B != 0) {
            WndShow(self->mpWin140, 1, 0);
            WndShow(self->mpWinA[0], 1, 0);
            WndShow(self->mpWinA[1], 1, 1);
        } else if (noun->m7A != 0) {
            WndShow(self->mpWin140, 1, 0);
            WndShow(self->mpWinA[0], 1, 1);
            WndShow(self->mpWinA[1], 1, 0);
        } else {
            WndShow(self->mpWin140, 1, 0);
            WndShow(self->mpWinA[0], 1, 0);
            WndShow(self->mpWinA[1], 1, 0);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00ef4440  interface query on the cILayer sub-object (this is cILayer*,
// the owning object starts 0x10 bytes before it).
// ---------------------------------------------------------------------------
void* __fastcall FUN_00ef4440(cLayerKeyProvider* self, void* dummy, int id)
{
    if ((id == 0x13d6b42b) || (id == 0x93d55b46)) {
        return (char*)self - 0x10;
    }
    if (id != 0xee3f516e) {
        return 0;
    }
    return ((char*)self - 0x10) ? self : 0;
}

// ---------------------------------------------------------------------------
// @ 0x00ef4490  resource key of the layer object: the loaded key when the
// object carries a known key-instance type, else the inline {id, type} pair.
// ---------------------------------------------------------------------------
void __fastcall FUN_00ef4490(cLayerKeyProvider* self, void* dummy, ResKey* out)
{
    uint type = self->mKeyInstance;
    if ((type == 0xdb5cad8b) || (type == 0x28c176eb) || (type == 0x15677bf)) {
        ResKey key;
        key.mId = self->mKeyB.mId;
        key.mType = 0x2f7d0004;
        key.mSub = DAT_015acdf4;
        *out = key;
    } else {
        ResKey key = *(const ResKey*)&self->m04;
        key.mType = 0x2f7d0004;
        key.mSub = 0x65928944;
        *out = key;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00ef4520  default "no extra id" virtual (returns {0, 0}).
// ---------------------------------------------------------------------------
Pair8 __fastcall FUN_00ef4520(void* self)
{
    Pair8 r;
    r.mLo = 0;
    r.mHi = 0;
    return r;
}

// ---------------------------------------------------------------------------
// @ 0x00ef4550  constructor.
// ---------------------------------------------------------------------------
cLayerKeyProvider* __fastcall FUN_00ef4550(cLayerKeyProvider* self)
{
    self->m04 = 0;
    self->m08 = 0;
    self->m0C = 0;
    self->mpLayerVt = (void*)&VTABLE_013f1ab0;
    self->mpSummaryVt = (void*)&VTABLE_013ec458;
    self->m18 = 0;
    _ReadWriteBarrier();
    self->mpVtbl = (void*)&VTABLE_0148b2d0;
    self->mpLayerVt = (void*)&VTABLE_0148b2c0;
    self->mpSummaryVt = (void*)&VTABLE_0148b2b0;
    cString_Ctor(&self->mName);
    self->mKeyInstance = 0;
    self->mKeyA.mId = 0;
    self->mKeyA.mType = 0;
    self->mKeyA.mSub = 0;
    self->mKeyB.mId = 0;
    self->mKeyB.mType = 0;
    self->mKeyB.mSub = 0;
    return self;
}

// ---------------------------------------------------------------------------
// @ 0x00ef45b0  scalar deleting destructor.
// ---------------------------------------------------------------------------
cLayerKeyProvider* __fastcall FUN_00ef45b0(cLayerKeyProvider* self, void* dummy, char flags)
{
    self->mpVtbl = (void*)&VTABLE_0148b2d0;
    self->mpLayerVt = (void*)&VTABLE_0148b2c0;
    self->mpSummaryVt = (void*)&VTABLE_0148b2b0;
    cString_Dtor(&self->mName);
    Layer_Shutdown(self);
    if (flags & 1) {
        operator_delete(self);
    }
    return self;
}

// ---------------------------------------------------------------------------
// @ 0x00ef4620  load the object's properties (name text and three keys).
// ---------------------------------------------------------------------------
void __fastcall FUN_00ef4620(cLayerKeyProvider* self, void* dummy, void* param)
{
    void* pm;
    void* bag;

    Layer_Init(self, 0, param);
    bag = 0;
    pm = SP_PropertyManager();
    ResetWindow(&bag);
    if (PropertyManager_Get(pm, self->m04, self->m0C, &bag)) {
        SP_GetPropertyAsText(bag, 0x71e9bd1, &self->mName);
        self->mKeyInstance = 0;
        SP_GetPropertyAsKeyInstance(bag, 0x5cd8beab, &self->mKeyInstance);
        self->mKeyA.mId = 0;
        self->mKeyA.mType = 0;
        self->mKeyA.mSub = 0;
        SP_GetPropertyAsKey(bag, 0xaeb7704e, &self->mKeyA);
        self->mKeyB.mId = 0;
        self->mKeyB.mType = 0;
        self->mKeyB.mSub = 0;
        SP_GetPropertyAsKey(bag, 0xf9efbb, &self->mKeyB);
    }
    if (bag) {
        WndRelease(bag);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00ef46f0  message handler.
// ---------------------------------------------------------------------------
bool __fastcall FUN_00ef46f0(cAssetPanel* self, void* dummy, void* context, Msg* msg)
{
    void* w;

    switch (msg->mType) {
    case 9:
        w = msg->mpWindow;
        if (self->mpWin40 != 0) {
            if (WndGetChild(self->mpWin40) == w) {
                WindowManager_SetCurrent(SP_WindowManager(),
                                         WndGetItem(self->mpWin40, msg, 0));
            }
        }
        if (self->mpWin44 != 0) {
            if (WndGetChild(self->mpWin44) == w) {
                WindowManager_SetCurrent(SP_WindowManager(),
                                         WndGetItem(self->mpWin44, msg, 0));
            }
        }
        break;
    case 0x1b:
    case 0x1c: {
        void* obj;
        if (WndGetSenderType(msg->mpSender) == 0x53d6fe29) {
            obj = self->mpZoomB0;
        } else if (WndGetSenderType(msg->mpSender) == 0xb456a47a) {
            obj = self->mpZoomAC;
        } else {
            return false;
        }
        if (obj != 0) {
            if (msg->mType == 0x1b) {
                TextZoomName_Activate(obj, 0);
            } else {
                TextZoomName_Deactivate(obj, 0);
            }
        }
        return false;
    }
    case 0x287259f6:
        switch (msg->mSub) {
        case 0x7b69988:
            FieldSet(&self->mField, (int)self->mpLayout, 0x7ccce38);
            return true;
        case 0x6135298:
            if (self->mpNoun9C != 0) {
                void* a = WndGetSlot20(FUN_0067de40());
                void* child = WndGetItem1(self->mpNoun9C, 0);
                WndSetSlot34(a, child);
            }
            UI_CalloutMessageBox(&self->m08, 0x15aced8);
            return true;
        case 0x7b69998:
            FieldSet(&self->mField, (int)self->mpLayout, 0x7ccce30);
            return true;
        case 0x53d6fe2a:
            if (self->mpNounA0 != 0) {
                __int64 id = Meta_GetId(self->mpNounA0);
                MessageServer_Send(SP_MessageServer(), 0x6299932, &id, 0);
            }
            return true;
        case 0x74174c59:
            MessageServer_Send(SP_MessageServer(), 0x14ac4938, 0, 0);
            return true;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x00ef4940  shut the panel down: release every window and sub-object.
// ---------------------------------------------------------------------------
void __fastcall FUN_00ef4940(cAssetPanel* self)
{
    void* p;
    int i;

    if (self->mC0 == 0) {
        return;
    }
    p = self->mpVerbs98;
    if (p != 0) {
        cSPUIAssetVerbs_Shutdown(p);
        p = self->mpVerbs98;
        if (p != 0) {
            self->mpVerbs98 = 0;
            WndRelease(p);
        }
    }
    p = self->mpVerbs94;
    if (p != 0) {
        FUN_00f47040(p);
        p = self->mpVerbs94;
        if (p != 0) {
            self->mpVerbs94 = 0;
            WndRelease(p);
        }
    }
    if (self->mpWin38 != 0) {
        WndHookEvent(self->mpWin38, self);
    }
    if (self->mpWin40 != 0) {
        p = WndGetChild(self->mpWin40);
        if (p != 0) {
            WndHookEvent(p, self);
        }
    }
    if (self->mpWin44 != 0) {
        p = WndGetChild(self->mpWin44);
        if (p != 0) {
            WndHookEvent(p, self);
        }
    }
    p = self->mpZoomAC;
    if (p != 0) {
        TextZoomName_Shutdown(p);
        p = self->mpZoomAC;
        if (p != 0) {
            self->mpZoomAC = 0;
            WndReleaseVt8(p);
        }
    }
    p = self->mpZoomB0;
    if (p != 0) {
        TextZoomName_Shutdown(p);
        p = self->mpZoomB0;
        if (p != 0) {
            self->mpZoomB0 = 0;
            WndReleaseVt8(p);
        }
    }
    ResetWindow(&self->mpWin38);
    ResetWindow(&self->mpWin3C);
    ResetWindow(&self->mpWin40);
    ResetWindow(&self->mpWin44);
    ResetWindow(&self->mpWin48);
    ResetWindow(&self->mpWin4C);
    ResetWindow(&self->mpWin50);
    ResetWindow(&self->mpWin54);
    ResetWindow(&self->mpWin58);
    WndGetHash(self->mpObjA8);
    ResetWindow(&self->mpObjA8);
    for (i = 0; i < 4; ++i) {
        ResetWindow(&self->mpWinA[i]);
        ResetWindow(&self->mpWinB[i]);
    }
    ResetWindow(&self->mpWin7C);
    ResetWindow(&self->mpWin80);
    ResetWindow(&self->mpWin84);
    ResetWindow(&self->mpWin88);
    ResetWindow(&self->mpWin8C);
    ResetWindow(&self->mpWin90);
    self->mC0 = 0;
}

// Reference-releasing minimum used by the thumbnail inset (eastl::min style).
inline float MinRef(float& a, float& b)
{
    return a > b ? b : a;
}

// @ 0x00ef4bd0  refresh the four thumbnail slots: relink the image and inset the
// picture area of the two picture windows to a centred square.
void __fastcall FUN_00ef4bd0(cAssetPanel* self)
{
    int i;
    for (i = 0; i < 4; ++i) {
        void* wA = self->mpWinA[i];
        void* wB = self->mpWinB[i];
        if (wA == 0) {
            continue;
        }
        if (wB == 0) {
            continue;
        }
        {
            void* imgWnd = WndFindChild(wA, 0x80834b0, 1);
            void* btnWnd = WndFindChild(wA, 0x805a361, 1);
            void* btnWnd2 = WndFindChild(wA, 0x805a360, 1);
            if (imgWnd == 0) {
                continue;
            }
            if (btnWnd == 0) {
                continue;
            }
            if (btnWnd2 == 0) {
                continue;
            }
            {
                ResKey key;
                uint sub;
                void* mgr;
                int vis;

                WndGetKey(self->mpVerbs98, &key);
                sub = key.mSub;
                sub = ((uint)(i + 1) ^ sub) & 0xff;
                key.mSub = sub ^ key.mSub;
                mgr = ResourceMan_GetManager();
                if (ResourceMan_Query(mgr, &key, 0, 0, 0, 0, 0)) {
                    SetWindowImage(imgWnd, &key, -1);
                }
                vis = WndIsVisible(imgWnd);
                if (vis) {
                    WndShow(btnWnd, 1, 1);
                } else {
                    WndShow(btnWnd, 1, 0);
                }
                WndShow(btnWnd2, 1, vis);
            }
            if (self->mpFlagsA4 != 0) {
                if (self->mpFlagsA4->mFlags[i] != 0) {
                    continue;
                }
            }
            {
                void* wins[2];
                int j;
                wins[0] = wA;
                wins[1] = wB;
                for (j = 0; j < 2; ++j) {
                    float* r = (float*)WndGetArea(wins[j]);
                    float dx = r[2] - r[0];
                    float dy = r[3] - r[1];
                    float inset;
                    float dxn;
                    float dyn;
                    float rect[4];

                    if (dx <= 0.0f) {
                        return;
                    }
                    if (dy <= 0.0f) {
                        return;
                    }
                    inset = MinRef(dx, dy);
                    dxn = (dx - inset) * 0.5f;
                    dyn = (dy - inset) * 0.5f;
                    rect[0] = r[0] + dxn;
                    rect[1] = r[1] + dyn;
                    rect[2] = r[2] - dxn;
                    rect[3] = r[3] - dyn;
                    WndSetArea(wins[j], rect);
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00ef4e40  set the layout's picture from the noun's type hash.
// ---------------------------------------------------------------------------
void __fastcall FUN_00ef4e40(cAssetPanel* self)
{
    void* w = self->mpLayout->FindWindowByID(0x79836c0, 1);
    if (w == 0) {
        return;
    }
    WndAddRef(w);
    AssetNoun* noun = (AssetNoun*)self->mpNoun9C;
    if (noun != 0) {
        uint imageId = 0;
        switch (WndGetHashU(noun)) {
        case 0x24720859: imageId = 0xf2801199; break;
        case 0x20790816: imageId = 0x65623b56; break;
        case 0x25a6ea6e: imageId = 0xba317a23; break;
        case 0x27818fe6: imageId = 0x8292c121; break;
        case 0x287adcdc: imageId = 0x4a2d27f7; break;
        case 0x37fd4e0d: imageId = 0x77806e4c; break;
        case 0xfb734cd1: imageId = 0xecd899dc; break;
        case 0xe27ddad4: imageId = 0x2df397e7; break;
        case 0xc34c5e14: imageId = 0x257164c3; break;
        case 0xb4707f8f: imageId = 0xbe33ecce; break;
        case 0xc422519e: imageId = 0x70eb3237; break;
        default: break;
        }
        AutoRefCount ref;
        void* img = 0;
        ref.mpObject = 0;
        if (imageId != 0) {
            ref = SPUIHelpers_GetImageFromLayout(self->mpLayout, imageId);
            img = ref.mpObject;
        }
        if (img != 0) {
            FUN_008068d0(w, img, -1);
            WndRelease(img);
        } else {
            FUN_008068d0(w, 0, -1);
        }
    }
    WndRelease(w);
}

// ---------------------------------------------------------------------------
// Restored by the check-in: byte-exact 00ef4f80 from commit 8dd062dbc, dropped when this
// slice was rewritten for its new functions.
// Slice s00ef40d0: 00ef4f80, a UI spinner's per-frame update (thiscall, one int arg, ret 4).
// Class and field names are descriptive guesses; offsets, vtable slots and call conventions come from the binary.

float __cdecl GetElapsedSeconds();                                  // SPUIHelpers::GetElapsedSeconds (0x805080): no args, float in st0
void __cdecl SetRotationQuat(void* transform, const float* rot);    // 0x808230: cdecl (caller does add esp,8)

namespace SP {
class cCombatant {
public:
    void NotifyAttack(int arg);                                     // thiscall, ret 4 (0x10829f0)
};
}

// Virtual interface stub: only the slots this function calls are named (vtable offset = slot * 4).
struct IVirtualSlots {
    virtual void Slot0();  virtual void Slot1();  virtual void Slot2();  virtual void Slot3();
    virtual void Slot4();  virtual void Slot5();  virtual void Slot6();
    virtual void Slot7(int arg);                                    // +0x1c
    virtual void Slot8();  virtual void Slot9();
    virtual unsigned char Slot10();                                 // +0x28
    virtual void Slot11(); virtual void Slot12(); virtual void Slot13(); virtual void Slot14();
    virtual void Slot15(); virtual void Slot16(); virtual void Slot17(); virtual void Slot18();
    virtual void Slot19(); virtual void Slot20(); virtual void Slot21(); virtual void Slot22();
    virtual void Slot23(); virtual void Slot24(); virtual void Slot25(); virtual void Slot26();
    virtual void Slot27(); virtual void Slot28(); virtual void Slot29(); virtual void Slot30();
    virtual void Slot31(int a, int b);                              // +0x7c
};

class cSpinner {
public:
    char mUnk00[0x2c];
    IVirtualSlots* mpB;          // +0x2c: slot 10 tested with & 1; also the SetRotation target of the second block
    char mUnk30[0x68 - 0x30];
    void* mpTransform;           // +0x68
    IVirtualSlots* mpC;          // +0x6c: slot 31
    char mUnk70[0x74 - 0x70];
    SP::cCombatant* mpCombatant; // +0x74
    char mUnk78[0x84 - 0x78];
    IVirtualSlots* mpD;          // +0x84: slot 7, then slot 10 as bool
    char mUnk88[0x9e - 0x88];
    unsigned char mFlag9e;       // +0x9e
    unsigned char mFlag9f;       // +0x9f

    void Update(int arg);
};

// Quaternion-like rotation {0, 0, 1, -2 * elapsed}, stored as four floats and passed by pointer.
// The target is taken by reference so the member is read after GetElapsedSeconds() returns.
template <typename T>
__forceinline void SetSpinRotation(T* const& target) {
    float rot[4];
    rot[3] = GetElapsedSeconds() * -2.0f;
    rot[0] = 0.0f;
    rot[1] = 0.0f;
    rot[2] = 1.0f;
    SetRotationQuat(target, rot);
}

void cSpinner::Update(int arg)
{
    if (mpCombatant)
        mpCombatant->NotifyAttack(arg);
    IVirtualSlots* d = mpD;
    if (d != 0)
        d->Slot7(arg);
    if (mpTransform != 0 && mpC != 0) {
        bool spin;
        if (mFlag9f == 0 && mFlag9e == 0) {
            IVirtualSlots* e = mpD;
            spin = e != 0 && e->Slot10() != 0;
        } else {
            spin = true;
        }
        if (spin) {
            mpC->Slot31(1, 1);
            SetSpinRotation(mpTransform);
        } else {
            mpC->Slot31(1, 0);
        }
    }
    IVirtualSlots* b = mpB;
    if (b != 0 && (b->Slot10() & 1) != 0)
        SetSpinRotation(mpB);
}
