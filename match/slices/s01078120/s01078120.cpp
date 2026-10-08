// Slice s01078120: 0x01078120, 1788 bytes. Ghidra's PDB-candidate name is SP::cSPEditorDevUI::Init (caller-scored,
// unverified); here it is cSPPropLayoutPanel::Init (Claude-coined: it reads a property list, loads a layout and
// centres a text window inside the layout's first window).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc: the cSPUILayout local has a dtor but no EH frame).
//
// Steps: (1) tear down the previous state (message handler, window proc, window/text refs, stopwatch);
// (2) fetch the property list for the layout key and read a window id plus ~14 tuning properties with defaults;
// (3) load the first of five candidate layouts that exists and measure its first window;
// (4) derive the scaled size, find the window by id, centre a text child, subscribe to messages if requested.
#include "types.h"

struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey() {}
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};

namespace Math { struct Rectangle { float x1, y1, x2, y2; Rectangle(const Rectangle& o) : x1(o.x1), y1(o.y1), x2(o.x2), y2(o.y2) {} }; }

// ---- App::Property / PropertyList / PropertyManager (subset) ----
struct Property {
    uint16_t pad[9];
    uint16_t mnType;                                  // +0x12 (1 bool, 10 uint, 13 float)
    bool* GetBool();                                  // 0x0041e920
    uint32_t* GetUInt();                              // 0x0041ea00
    float* GetFloat();                                // 0x0041ea70
};
struct PropertyList {
    virtual int AddRef();
    virtual int Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t propertyID, Property*& result);   // +0x24
};
struct PropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppDst);   // +0x2c
};
PropertyManager* PropertyManager_Get();               // 0x0067de30
bool GetPropertyAsKeyInstance(PropertyList* list, uint32_t id, uint32_t* out);   // 0x006a12a0

inline bool GetUIntProp(PropertyList* list, uint32_t id, uint32_t& out)
{
    Property* p;
    if (list && list->GetProperty(id, p) && p->mnType == 10) { out = *p->GetUInt(); return true; }
    return false;
}
inline bool GetFloatProp(PropertyList* list, uint32_t id, float& out)
{
    Property* p;
    if (list && list->GetProperty(id, p) && p->mnType == 13) { out = *p->GetFloat(); return true; }
    return false;
}
inline bool GetBoolProp(PropertyList* list, uint32_t id, bool& out)
{
    Property* p;
    if (list && list->GetProperty(id, p) && p->mnType == 1) { out = *p->GetBool(); return true; }
    return false;
}

template <class T> struct AutoRef {
    T* mpObject;
    AutoRef() : mpObject(0) {}
    ~AutoRef() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    // Drops the reference and hands out the slot (T** out-parameter idiom).
    T** AsOutParam()
    {
        if (mpObject) { T* pOld = mpObject; mpObject = 0; pOld->Release(); }
        return &mpObject;
    }
    __forceinline AutoRef& operator=(T* p)
    {
        T* const pTemp = mpObject;
        if (p != pTemp) {
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};

// ---- UTFWin objects: AddRef +0, Release +4 ----
struct IWinProc { virtual int AddRef(); virtual int Release(); };
struct IWindow {
    virtual int AddRef();                                            // +0x00
    virtual int Release();                                           // +0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual const Math::Rectangle& GetRealArea();                    // +0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void SetPosition(float x, float y);                      // +0x70
    virtual void SetSize(float w, float h);                          // +0x74
    virtual void v78();
    virtual void SetFlag(int flag, bool value);                      // +0x7c
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual void va8(); virtual void vac(); virtual void vb0(); virtual void vb4(); virtual void vb8();
    virtual void vbc(); virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void RemoveWindow(IWindow* child);                       // +0xe0
    virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive);    // +0xf0
    virtual void vf4(); virtual void vf8(); virtual void vfc(); virtual void v100();
    virtual void AddWinProc(IWinProc* pProc);                        // +0x104
    virtual void RemoveWinProc(IWinProc* pProc);                     // +0x108
};
typedef IWindow IWinText;
IWinText* __cdecl CreateTextWindow(IWinText* src);                   // 0x00806370

// AutoRefCount<IWinText>::operator=(T*) is out of line at 0x00b5f950, but assigning null is inlined.
struct IWinTextRef {
    IWinText* mpObject;
    IWinTextRef& operator=(IWinText* p);                             // 0x00b5f950
    void Clear()
    {
        IWinText* pOld = mpObject;
        if (pOld) { mpObject = 0; pOld->Release(); }
    }
};

struct cSPUILayout {
    char pad[0x18];
    cSPUILayout();                                                   // 0x00810000
    ~cSPUILayout();                                                  // 0x00811fe0
    bool Init(const ResourceKey* key, int visible, uint32_t parentID);   // 0x008120d0
    IWindow* FindWindowByID(uint32_t id, int recursive);             // 0x008105b0
};

struct IMessageServer;
IMessageServer* __cdecl MessageServer();                             // 0x0067dcc0

struct IMsgServer;
void __cdecl RemoveHandler(void* server, uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0x00571db0 (EA::Messaging::RemoveHandler)
struct Connector {
    void* mpServer; uint32_t a, b, c, d;
    void Init(IMessageServer* server, void* handler, const uint32_t* messageIDs, int count);   // 0x004db620
};

struct Stopwatch {
    uint32_t a, b, c, d;
    void SetUnits(int units);                                        // 0x0093a1a0
    void Reset(int units) { a = 0; b = 0; c = 0; d = 0; SetUnits(units); }
};

extern uint32_t g_LayoutPropIDs[5];                                  // 0x0149c5e8
extern uint32_t g_MessageIDs[1];                                     // 0x0149c614

class cSPPropLayoutPanel : public IWinProc {
public:
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20();
    virtual void OnShow24();                                         // +0x24
    virtual void OnShow28();                                         // +0x28
    uint32_t pad04[2];                                               // +0x04
    void* mHandler;                                                  // +0x0c (second vptr: message handler base)
    ResourceKey mLayoutKey;                                          // +0x10
    cSPUILayout* mpLayout;                                           // +0x1c
    AutoRef<PropertyList> mPropList;                                 // +0x20
    AutoRef<IWindow> mWindow;                                        // +0x24
    IWinTextRef mText;                                               // +0x28
    IWinTextRef mTextClone;                                          // +0x2c
    uint32_t pad30[(0x44 - 0x30) / 4];
    ResourceKey mLayoutKeys[5];                                      // +0x44
    uint32_t m80;                                                    // +0x80
    float m84;                                                       // +0x84
    uint32_t mCols;                                                  // +0x88
    uint32_t mRows;                                                  // +0x8c
    uint32_t m90;                                                    // +0x90
    float mPadX;                                                     // +0x94
    float mPadY;                                                     // +0x98
    bool mFlag9c;                                                    // +0x9c
    uint32_t mMode;                                                  // +0xa0
    uint32_t ma4, ma8, mac, mb0;                                     // +0xa4..+0xb0
    float mLayoutW, mLayoutH;                                        // +0xb4, +0xb8
    float mScaledW, mScaledH;                                        // +0xbc, +0xc0
    uint32_t pad_c4;
    Stopwatch mStopwatch;                                            // +0xc8
    uint32_t pad_d8[(0xe0 - 0xd8) / 4];
    float mE0, mE4;                                                  // +0xe0, +0xe4
    bool mFlagE8;                                                    // +0xe8
    bool mFlagE9;                                                    // +0xe9
    uint8_t pad_ea[0x100 - 0xea];
    Connector mConnector;                                            // +0x100

    IWindow* FUN_01077ae0(cSPUILayout* layout);                      // 0x01077ae0
    bool Init();
};

// @ 0x01078120
bool cSPPropLayoutPanel::Init()
{
    void* server = mConnector.mpServer;
    if (server) {
        mConnector.mpServer = 0;
        RemoveHandler(server, mConnector.a, mConnector.b, mConnector.c, mConnector.d);
    }
    bool ok = false;
    if (mWindow.mpObject)
        mWindow.mpObject->RemoveWinProc(this);
    if (mText.mpObject && mTextClone.mpObject)
        mText.mpObject->RemoveWindow(mTextClone.mpObject);
    mWindow = 0;
    mText.Clear();
    mTextClone.Clear();
    mStopwatch.Reset(5);

    PropertyManager* pm = PropertyManager_Get();
    uint32_t windowID;
    if (pm->GetPropertyList(mLayoutKey.instanceID, mLayoutKey.groupID, mPropList.AsOutParam())
        && GetUIntProp(mPropList.get(), 0x1a561f11, windowID)) {
        m80 = 0x41478d35;
        GetUIntProp(mPropList.get(), 0x6498e0ef, m80);
        m84 = 0.0f;
        GetFloatProp(mPropList.get(), 0x7ae5959, m84);
        mCols = 1;
        GetUIntProp(mPropList.get(), 0x44833f26, mCols);
        mRows = 1;
        GetUIntProp(mPropList.get(), 0x44ae2034, mRows);
        m90 = (uint32_t)-1;
        GetUIntProp(mPropList.get(), 0x86eec9cd, m90);
        mPadX = 0.0f;
        GetFloatProp(mPropList.get(), 0xe603d9c3, mPadX);
        mPadY = 0.0f;
        GetFloatProp(mPropList.get(), 0xdfef8f2d, mPadY);
        mFlag9c = true;
        GetBoolProp(mPropList.get(), 0x2ba82aec, mFlag9c);
        mMode = (uint32_t)-1;
        GetUIntProp(mPropList.get(), 0xd2df8e4d, mMode);
        ma4 = (uint32_t)-1;
        GetUIntProp(mPropList.get(), 0x930166a3, ma4);
        ma8 = 0xfff0f0f0;
        GetUIntProp(mPropList.get(), 0xa798fc58, ma8);
        mac = (uint32_t)-1;
        GetUIntProp(mPropList.get(), 0xfcfe75a2, mac);
        mb0 = 0xff555555;
        GetUIntProp(mPropList.get(), 0xbef43c38, mb0);

        bool loaded = false;
        for (int k = 0; k < 5; ++k) {
            ResourceKey* key = &mLayoutKeys[k];
            *key = ResourceKey(0, 0x510a95b, 0x40464100);
            if (GetPropertyAsKeyInstance(mPropList.get(), g_LayoutPropIDs[k], &key->instanceID) && !loaded) {
                cSPUILayout layout;
                if (!layout.Init(key, 0, 0x5b598fa)) {
                    key->instanceID = 0;
                } else {
                    IWindow* win = FUN_01077ae0(&layout);
                    if (win) {
                        Math::Rectangle r = win->GetRealArea();
                        mLayoutW = r.x2 - r.x1;
                        mLayoutH = r.y2 - r.y1;
                        loaded = true;
                    }
                }
            }
        }

        if (loaded) {
            mScaledW = (mLayoutW + mPadX) * (float)mCols;
            mScaledH = (mLayoutH + mPadY) * (float)mRows;
            if (mpLayout) {
                mWindow = mpLayout->FindWindowByID(windowID, 1);
                if (mWindow.get()) {
                    mText = mWindow.get()->FindWindowByID(0x5f7c9b3, false);
                    if (mText.mpObject) {
                        mWindow.get()->AddWinProc(this);
                        Math::Rectangle r = mText.mpObject->GetRealArea();
                        mText.mpObject->SetPosition(((r.x2 - r.x1) - mScaledW) * 0.5f + r.x1,
                                                    ((r.y2 - r.y1) - mScaledH) * 0.5f + r.y1);
                        mText.mpObject->SetSize(mScaledW, mScaledH);
                        mText.mpObject->SetFlag(0x400, true);
                        mTextClone = CreateTextWindow(mText.mpObject);
                        mE0 = 0.0f;
                        mE4 = 0.0f;
                        if (mMode != (uint32_t)-1) {
                            mFlagE9 = (mMode == 1);
                            mConnector.Init(MessageServer(), &mHandler, g_MessageIDs, 1);
                        }
                        if (mFlagE8) {
                            OnShow28();
                            OnShow24();
                        }
                        ok = true;
                    }
                }
            }
        }
    }
    return ok;
}
