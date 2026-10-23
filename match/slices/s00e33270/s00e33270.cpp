// Slice s00e33270 -- SP::cSPUISocialRainbow message handling and render plumbing
// (DoMessage, Reset, ReleaseResources, StartFill), its eastl::fixed_vector<cRound,6> insert helper
// and cRound-side helpers, the UI::cUISporepediaPlanetLargeAssetView lifetime helpers and the
// cSPSwatch-derived Sporepedia swatch view.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
//
// Layout notes: the retail cSPUISocialRainbow is 0xc bytes larger than the 2008 PDB layout (its
// mbRebuild sits at +0x24, not +0x18) and its cSPUIAnimator is 8-byte aligned, so it starts at
// +0x48 and everything after it is 0x10 further on than in the PDB. The offsets below are the
// retail ones recovered from the disassembly.
//
// The Sporepedia view (0x00e33de0/0x00e33e70/0x00e33f30/0x00e33f90/0x00e34020) and the swatch
// view (0x00e33d40/0x00e33d60/0x00e33d70/0x00e34220) have no PDB names for their retail classes
// (their vtables are unnamed in retail), so the class names below are descriptive.

typedef unsigned int uint;
typedef unsigned int size_t;

// ---------------------------------------------------------------------------
// intrusive interfaces
// ---------------------------------------------------------------------------

// EA::COM::IUnknown32: reference counting through the vtable (AddRef in slot 0, Release in slot 1).
struct IUnknown32 {
    virtual int AddRef();                    // +0x00
    virtual int Release();                   // +0x04
    virtual void v08();                      // +0x08
};

// EA::RefCountVTemplate: a vtable (deleting destructor in slot 0) followed by the inline count.
// AddRef/Release are *not* virtual: they are inlined at every call site, and Release() invokes the
// deleting destructor through slot 0 once the count drops to zero.
class RefCountVTemplate {
 public:
    virtual ~RefCountVTemplate();            // +0x00 scalar deleting destructor

    int AddRef() { return ++mRefCount; }
    int Release()
    {
        // The count update has to be spelled out (rather than "--mRefCount") so that it is
        // materialised in a register: the retail call sites reload the count, decrement it and
        // store it back before testing it.
        int nCount = mRefCount - 1;
        mRefCount = nCount;
        if (nCount == 0) {
            mRefCount = 1;
            delete this;
        }
        return nCount;
    }

    int mRefCount;                           // +0x04
};

struct IWindow;

// A window proc / message handler (EA::UTFWin::IWinProc).
struct IWinProc : public IUnknown32 {
    virtual bool DoMessage(IWindow* pWindow, void* pMessage);    // +0x0c
};

// Additional interfaces installed by the Sporepedia view (secondary and tertiary vtable slots).
struct IViewBehavior : public IUnknown32 {
};
struct IViewBehavior2 : public IUnknown32 {
};

// A refcounted image (only the pixel size is read in this slice).
struct Image : public IUnknown32 {
    uint mPad[5];                            // +0x08
    int mWidth;                              // +0x1c
    int mHeight;                             // +0x20
};

struct IRenderable : public IUnknown32 {
};

// A ref-counted effect/behaviour owned through an AutoRefCount<T>.
struct IViewEffect : public IUnknown32 {
    virtual void Stop(bool bImmediate);      // +0x0c
    virtual void v10();                      // +0x10
};

// EA::UTFWin::IWindow: only the slots used by this slice are named; the rest are placeholders.
struct IWindow : public IUnknown32 {
    virtual void* Cast(uint type);           // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual uint GetControlID();             // +0x1c
    virtual void v20(); virtual void v24();
    virtual bool IsVisible();                // +0x28
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void v5c(); virtual void v60(); virtual void v64(); virtual void v68();
    virtual void v6c(); virtual void v70(); virtual void v74(); virtual void v78();
    virtual void SetFlag(int flag, bool value);            // +0x7c
    virtual void SetCaption(const wchar_t* text);          // +0x80
    virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void Refresh();                                // +0x90
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0();
    virtual void va4(); virtual void va8(); virtual void vac(); virtual void vb0();
    virtual void vb4(); virtual void vb8(); virtual void vbc(); virtual void vc0();
    virtual void vc4(); virtual void vc8(); virtual void vcc(); virtual void vd0();
    virtual void vd4(); virtual void vd8(); virtual void vdc(); virtual void ve0();
    virtual void ve4(); virtual void ve8(); virtual void vec(); virtual void vf0();
    virtual void vf4(); virtual void vf8(); virtual void vfc(); virtual void v100();
    virtual void SetLayoutArea(void* area);                // +0x104
    virtual void SetWinProc(IWinProc* proc);               // +0x108
};

// A ref-counted property list.
struct IPropertyList {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c();
    virtual void SetProperty(uint id, void* value);          // +0x30
};

// The layout object. Embedded (not owned) in cSPUISocialRainbow at +0x0c.
class cSPUILayout : public RefCountVTemplate {
 public:
    virtual int AddRef();                                        // vtable slot 4
    virtual int Release();                                       // vtable slot 8
    void SetReloadCallback(void (__cdecl*)(void*, cSPUILayout*, bool), void*);  // 0x00810090
    IWindow* FindWindowByID(uint id, bool recursive) const;      // 0x008105b0
    void Shutdown(uint destroy);                                 // 0x00811ad0

    unsigned char mResourceKey[12];                              // +0x08
    void** mpObjectCollection;                                   // +0x14
};

// Name provider used to fill the view's caption windows: the primary interface serves the strings
// (slots +0x0c/+0x10) and a secondary IUnknown32 subobject at +0x10 owns the reference count.
class IViewNameProvider {
 public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual const wchar_t* GetTitle();        // +0x0c
    virtual const wchar_t* GetDescription();  // +0x10

    uint mPad04[3];                           // +0x04
    IUnknown32 mRefCount;                     // +0x10

    void Release() { mRefCount.Release(); }
};

// AutoRefCount<T>: Assigning a new pointer AddRefs it, stores it and Releases the old one.
template <class T>
class AutoRefCount {
 public:
    AutoRefCount() : mpObject(0) {}

    AutoRefCount& operator=(T* pObject)
    {
        if (mpObject != pObject) {
            if (pObject)
                pObject->AddRef();
            T* pOld = mpObject;
            mpObject = pObject;
            if (pOld)
                pOld->Release();
        }
        return *this;
    }

    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* Get() const { return mpObject; }
    T** AsPPTypeParam() { return &mpObject; }

    T* mpObject;
};

struct Vec2f {
    float x;
    float y;
};

// Animator. The only animator entry points used here are Update() and ClearAll().
class cSPUIAnimator {
 public:
    void ClearAll();                                             // 0x007f8f00
    void Update();                                               // 0x007f63b0

    void** mpVftable;                                            // +0x00
    void*  mpAnimationInfosBegin;                                // +0x04
    void*  mpAnimationInfosEnd;                                  // +0x08
    void*  mpAnimationInfosCapacity;                             // +0x0c
    void*  mpAnimationInfosAllocator;                            // +0x10
    float  mLastUpdateTime;                                      // +0x14
    int    mPad;                                                 // +0x18 (aligns the 0x1c retail size)
};

// One arc round of one side. sizeof(cRound) == 0x14.
struct cRound {
    float mArcTo;          // +0x00
    float mNumSegments;    // +0x04
    uint  mColor;          // +0x08
    float mRate;           // +0x0c
    float mMinRate;        // +0x10
};

// eastl::fixed_vector<cRound,6,1>: vector part, then the inline storage inside the object.
class cRoundVector {
 public:
    void DoInsertValue(cRound* position, const cRound& value);   // 0x00e33850

    cRound* mpBegin;                 // +0x00
    cRound* mpEnd;                   // +0x04
    cRound* mpCapacity;              // +0x08
    void*   mpAllocator;             // +0x0c
    cRound* mpInlineStorage;         // +0x10
    cRound  mInlineStorage[6];       // +0x14
    uint    mInlineCapacity;         // +0x8c
    uint    mCapacityValue;          // +0x90
};

// Per-side state of the social rainbow.
class cSideInfo {
 public:
    void Clear();                                            // 0x00e33990

    cRoundVector mRounds;                                    // +0x00
    float mArcSize;                                          // +0x94
    float mArcSizeTarget;                                    // +0x98
    bool  mbStopBarAnimation;                                // +0x9c
    bool  mbBarDone;                                         // +0x9d
    IViewEffect* mpDraw;                                     // +0xa0
};

// SP::cSPUISocialRainbow (retail layout). The three vtable-carrying bases sit at +0x00/+0x04/+0x08.
class cSPUISocialRainbow : public IWinProc, public IViewBehavior, public IViewBehavior2 {
 public:
    enum eState {
        kStateEmpty = 1,
        kStateFull = 2,
        kStatePartial = 3,
    };

    bool DoMessage(IWindow* pWindow, void* pMessage);          // 0x00e33270
    void Reset();                                              // 0x00e33ce0
    bool ReleaseResources();                                   // 0x00e33a00
    void StartFill(int nSide, int nSegments, float fMinRate, float fRate,
                   float fFraction, uint color, void* pParam); // 0x00e33ab0

    void Init();                                               // 0x00e32de0
    void set_full();                                           // 0x00e32f00
    void UpdateSide(int nSide);                                // 0x00e324f0
    void UpdateSideDisplay(int nSide, int nShow, void* pParam);// 0x00e32250
    void get_round_bounds(int nSide, int nRound, float* pFrom, float* pTo);  // 0x00e31bb0

    cSPUILayout mLayout;                       // +0x0c
    bool  mbRebuild;                           // +0x24
    bool  mbInitialized;                       // +0x25
    bool  mbFull;                              // +0x26
    unsigned char mPad27;                      // +0x27
    Vec2f mScreenPos;                          // +0x28
    Vec2f mArcCenter;                          // +0x30
    float mArcRadius;                          // +0x38
    float mArcAngleFrom;                       // +0x3c
    float mArcAngleTo;                         // +0x40
    int   mSegmentCount;                       // +0x44
    cSPUIAnimator mAnimator;                   // +0x48
    IUnknown32* mpAnimationObject;             // +0x64
    Image* mpImageRightBarEndNotch;            // +0x68
    Image* mpImageLeftBarEndNotch;             // +0x6c
    Image* mpImageBarNotch;                    // +0x70
    Image* mpImageBar;                         // +0x74
    Image* mpImageBarBackground;               // +0x78
    Image* mpImageBarHighlight;                // +0x7c
    Image* mpImageBarFull;                     // +0x80
    IRenderable* mpBackgroundRenderable;       // +0x84
    Vec2f* mpDebugPointsBegin;                 // +0x88
    Vec2f* mpDebugPointsEnd;                   // +0x8c
    Vec2f* mpDebugPointsCapacity;              // +0x90
    eState mState;                             // +0x94
    uint  mStateFlagsFull;                     // +0x98
    unsigned char mPad9c[8];                   // +0x9c
    cSideInfo mSideInfos[2];                   // +0xa4 (sizeof(cSideInfo) == 0xa4)
    IRenderable* mpArcRenderable;              // +0x1ec
    IRenderable* mpFullBarRenderable;          // +0x1f0
    IRenderable* mpSegmentsRenderable;         // +0x1f4
    IRenderable* mpRelationshipIcon;           // +0x1f8
    IRenderable* mpStarburst;                  // +0x1fc
};

// ---------------------------------------------------------------------------
// callees that belong to other slices / other translation units
// ---------------------------------------------------------------------------

class RenderCtx {
 public:
    void AddRenderable(IRenderable* pRenderable);        // 0x0095bbc0
    void* Begin2D(void* pRenderMode);                    // 0x0095bc10
};

class ColourCfg : public RefCountVTemplate {
 public:
    ColourCfg();                                         // 0x0066bd40
    void ApplyLayout(cSPUILayout* pLayout);              // 0x0066bd80
    void ResetColour();                                  // 0x0066bf20
};

namespace SP {
IPropertyList* __cdecl PropertyManager();                // 0x0067de30
}

namespace EA { namespace ResourceMan {
class Key {
 public:
    Key() : mInstanceID(0), mTypeID(0) {}
    uint mInstanceID;   // +0x00
    uint mTypeID;       // +0x04
};
}}

// EA global operator new (0x00f473a0): new(pName) T == operator new(sizeof(T), pName, 0, 0, 0, 0)
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);
void  operator delete[](void* p);
inline void* operator new(size_t, void* p) throw() { return p; }
inline void  operator delete(void*, void*) throw() {}

extern "C" {
IRenderable* __cdecl FUN_00828e30(RenderCtx* pCtx, IWindow* pWindow, void** ppOut);  // 0x00828e30
void       __cdecl FUN_00828ef0(RenderCtx* pCtx, void* pRenderable);                 // 0x00828ef0
void       __cdecl FUN_00e31d60(void* pBatch, float x, float y, float radius, int a, int b,
                                float angleFrom, float angleTo, Image* pImage, float step);
void       __cdecl FUN_00e32b20(void* pBatch, float x, float y, float radius, uint colorA,
                                uint colorB, float position, Image* pImage);
void       __cdecl FUN_00c50ad0(cRound* first, cRound* last, cRound* result);   // 0x00c50ad0
cRound*    __cdecl FUN_00951bb0(cRound* first, cRound* last, cRound* dest);     // 0x00951bb0
cRound*    __cdecl copy_Rec20(const cRound* first, const cRound* last, cRound* dest);  // 0x00951bf0
void       __cdecl SetWindowAreaToParent(IWindow* pWindow);                     // 0x00806bf0
}

extern const char gColourCfgName[];      // 0x013f6b3c
extern const char gSimulatorName[];      // 0x013f3f09 "Simulator"
extern const char gEastlAllocatorName[]; // 0x013ebb38
extern const wchar_t gMissingText[];     // 0x013ffd4c L"<Missing>"

// ---------------------------------------------------------------------------
// 0x00e33850 -- cRoundVector::DoInsertValue (in-place insert, grow by doubling)
// ---------------------------------------------------------------------------
// @ 0x00e33850
void cRoundVector::DoInsertValue(cRound* position, const cRound& value)
{
    if (mpEnd != mpCapacity) {
        const cRound* pValue = &value;
        if (pValue >= position && pValue < mpEnd)
            ++pValue;
        cRound* pLast = mpEnd;
        if (pLast) {
            const cRound* pPrev = pLast - 1;
            pLast->mArcTo = pPrev->mArcTo;
            pLast->mNumSegments = pPrev->mNumSegments;
            pLast->mColor = pPrev->mColor;
            pLast->mRate = pPrev->mRate;
            pLast->mMinRate = pPrev->mMinRate;
        }
        FUN_00c50ad0(position, pLast - 1, pLast);
        position->mArcTo = pValue->mArcTo;
        position->mNumSegments = pValue->mNumSegments;
        position->mColor = pValue->mColor;
        position->mRate = pValue->mRate;
        position->mMinRate = pValue->mMinRate;
        ++mpEnd;
    } else {
        int nSize = (int)(mpEnd - mpBegin);
        int nNewCapacity;
        cRound* pNewData;
        if (nSize == 0) {
            nNewCapacity = 1;
        } else {
            nNewCapacity = nSize * 2;
            if (nNewCapacity == 0) {
                pNewData = 0;
                goto copy;
            }
        }
        pNewData = (cRound*)operator new(nNewCapacity * sizeof(cRound), gSimulatorName, 0, 0,
                                         gEastlAllocatorName, 0xd1);
    copy:
        {
            cRound* pSlot = FUN_00951bb0(mpBegin, position, pNewData);
            if (pSlot) {
                pSlot->mArcTo = value.mArcTo;
                pSlot->mNumSegments = value.mNumSegments;
                pSlot->mColor = value.mColor;
                pSlot->mRate = value.mRate;
                pSlot->mMinRate = value.mMinRate;
            }
            cRound* pNewEnd = FUN_00951bb0(position, mpEnd, pSlot + 1);
            if (mpBegin && mpBegin != mpInlineStorage)
                operator delete[](mpBegin);
            mpBegin = pNewData;
            mpEnd = pNewEnd;
            mpCapacity = pNewData + nNewCapacity;
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00e33990 -- cSideInfo::Clear
// ---------------------------------------------------------------------------
// @ 0x00e33990
void cSideInfo::Clear()
{
    cRound* pBegin = mRounds.mpBegin;
    cRound* pEnd = mRounds.mpEnd;
    copy_Rec20(pBegin, pEnd, pEnd);
    // equivalent to "mpEnd = mpBegin"; the retail build updates the end pointer by the signed
    // byte count -((pEnd - pBegin) / sizeof(cRound)) * sizeof(cRound).
    int nBytes = (int)(pEnd - pBegin) / -(int)sizeof(cRound) * (int)sizeof(cRound);
    mRounds.mpEnd = (cRound*)((char*)pEnd + nBytes);
    mArcSize = 0.0f;
    mArcSizeTarget = 0.0f;
    mbStopBarAnimation = false;
    if (mpDraw) {
        IViewEffect* pOld = mpDraw;
        mpDraw = 0;
        pOld->Release();
    }
}

// ---------------------------------------------------------------------------
// 0x00e33a00 -- cSPUISocialRainbow::ReleaseResources
// ---------------------------------------------------------------------------
// @ 0x00e33a00
bool cSPUISocialRainbow::ReleaseResources()
{
    if (mpBackgroundRenderable) {
        IRenderable* pOld = mpBackgroundRenderable;
        mpBackgroundRenderable = 0;
        pOld->Release();
    }
    if (mpFullBarRenderable) {
        IRenderable* pOld = mpFullBarRenderable;
        mpFullBarRenderable = 0;
        pOld->Release();
    }
    if (mpArcRenderable) {
        IRenderable* pOld = mpArcRenderable;
        mpArcRenderable = 0;
        pOld->Release();
    }
    mSideInfos[1].Clear();
    mSideInfos[0].Clear();
    if (mpRelationshipIcon) {
        IRenderable* pOld = mpRelationshipIcon;
        mpRelationshipIcon = 0;
        pOld->Release();
    }
    if (mpStarburst) {
        IRenderable* pOld = mpStarburst;
        mpStarburst = 0;
        pOld->Release();
    }
    mLayout.SetReloadCallback(0, 0);
    mLayout.Shutdown(1);
    return true;
}

// ---------------------------------------------------------------------------
// 0x00e33ce0 -- cSPUISocialRainbow::Reset
// ---------------------------------------------------------------------------
// @ 0x00e33ce0
void cSPUISocialRainbow::Reset()
{
    mAnimator.ClearAll();
    mbInitialized = false;
    mbRebuild = true;
    mbFull = false;
    ReleaseResources();
    Init();
}

// ---------------------------------------------------------------------------
// 0x00e33ab0 -- cSPUISocialRainbow::StartFill
// ---------------------------------------------------------------------------
// @ 0x00e33ab0
void cSPUISocialRainbow::StartFill(int nSide, int nSegments, float fMinRate, float fRate,
                                   float fFraction, uint color, void* pParam)
{
    mbRebuild = true;
    UpdateSide(nSide);

    cSideInfo& side = mSideInfos[nSide];
    float fRoundFrom = 0.0f;
    float fRoundTo = 0.0f;
    int nRounds = (int)(side.mRounds.mpEnd - side.mRounds.mpBegin) - 1;
    get_round_bounds(nSide, nRounds, &fRoundFrom, &fRoundTo);

    cRound round;
    round.mArcTo = 0.0f;
    round.mNumSegments = 0.0f;
    round.mColor = 0;
    round.mRate = 0.0f;
    round.mMinRate = 0.0f;
    if (side.mRounds.mpEnd < side.mRounds.mpCapacity)
        *side.mRounds.mpEnd++ = round;
    else
        side.mRounds.DoInsertValue(side.mRounds.mpEnd, round);

    cRound& newRound = side.mRounds.mpEnd[-1];
    newRound.mNumSegments = (float)nSegments;
    newRound.mColor = color;
    newRound.mMinRate = fMinRate > 0.01f ? fMinRate : 0.01f;
    newRound.mRate = fRate;

    float fBounded = fFraction > 0.01f ? fFraction : 0.01f;
    if (fBounded > 1.0f)
        fBounded = 1.0f;
    float fAmount = (mArcAngleTo - mArcAngleFrom) * fBounded;

    float fPos = nSide == 1 ? fRoundTo - fAmount : fRoundTo + fAmount;
    if (fPos < mArcAngleFrom)
        fPos = mArcAngleFrom;
    else if (fPos > mArcAngleTo)
        fPos = mArcAngleTo;
    newRound.mArcTo = fPos;

    IWindow* pBarWindow = 0;
    if (nSide == 1)
        pBarWindow = mLayout.FindWindowByID(0x562c170, true);
    else if (nSide == 0)
        pBarWindow = mLayout.FindWindowByID(0x562c1b8, true);
    if (!pBarWindow->IsVisible())
        pBarWindow->SetFlag(1, true);

    side.mArcSizeTarget = side.mArcSize + fAmount;
    UpdateSideDisplay(nSide, 1, pParam);
}

// ---------------------------------------------------------------------------
// 0x00e33270 -- cSPUISocialRainbow::DoMessage
// ---------------------------------------------------------------------------
// Retail message layout: message id at +0x08, render context at +0x18.
struct Message {
    void* mpVftable;          // +0x00
    int   mPad04;
    int   mMessageID;         // +0x08
    int   mPad0c;
    int   mPad10;
    int   mPad14;
    RenderCtx* mpRenderContext;  // +0x18
};

// One bar segment to draw: which side it belongs to, its angle span and its end-notch image.
struct ArcSegment {
    int   mSide;              // +0x00
    float mAngleEnd;          // +0x04
    float mAngleStart;        // +0x08
    Image* mpImage;           // +0x0c
};

// @ 0x00e33270
bool cSPUISocialRainbow::DoMessage(IWindow* pWindow, void* pMessageRaw)
{
    Message* pMessage = (Message*)pMessageRaw;

    if (pMessage->mMessageID == 0x0c) {                    // kMsgUpdate
        mAnimator.Update();

        bool bFull = mSideInfos[1].mArcSize + mSideInfos[0].mArcSize
                         >= mArcAngleTo - mArcAngleFrom
                  && mSideInfos[1].mRounds.mpBegin != mSideInfos[1].mRounds.mpEnd
                  && mSideInfos[0].mRounds.mpBegin != mSideInfos[0].mRounds.mpEnd;

        if (!mbFull) {
            if (bFull)
                set_full();
            if (!mbFull) {
                for (int nSide = 0; nSide < 2; ++nSide) {
                    if (mSideInfos[nSide].mbStopBarAnimation) {
                        mSideInfos[nSide].mbStopBarAnimation = false;
                        UpdateSide(nSide);
                    }
                }
            }
        }
        if (mSideInfos[1].mbBarDone && mSideInfos[1].mArcSize == mSideInfos[1].mArcSizeTarget)
            mSideInfos[1].mbBarDone = false;
        if (mSideInfos[0].mbBarDone && mSideInfos[0].mArcSize == mSideInfos[0].mArcSizeTarget)
            mSideInfos[0].mbBarDone = false;

        if (mbRebuild) {
            IWindow* pBar = mLayout.FindWindowByID(0x562bd40, true);
            pBar->Refresh();
        }
    } else if (pMessage->mMessageID == 0x0d) {              // kMsgRender
        if (pWindow->GetControlID() != 0x562bd40)
            return false;

        RenderCtx* pCtx = pMessage->mpRenderContext;

        if (!mpArcRenderable) {
            mpArcRenderable = FUN_00828e30(pCtx, pWindow, (void**)&mpArcRenderable);
            FUN_00e31d60(mpArcRenderable, mArcCenter.x, mArcCenter.y, mArcRadius, -1, -1,
                         mArcAngleFrom, mArcAngleTo, mpImageBarHighlight, 0.1f);
            FUN_00828ef0(pCtx, mpArcRenderable);
        }
        pCtx->AddRenderable(mpArcRenderable);

        if (mbFull) {
            if (!mpFullBarRenderable) {
                IRenderable* pBatch =
                    FUN_00828e30(pCtx, pWindow, (void**)&mpFullBarRenderable);
                FUN_00e31d60(pBatch, mArcCenter.x, mArcCenter.y, mArcRadius, -1, -1,
                             mArcAngleFrom, mArcAngleTo, mpImageBarFull, 0.1f);
                FUN_00e31d60(pBatch, mArcCenter.x, mArcCenter.y, mArcRadius, -1, -1,
                             mArcAngleFrom, mArcAngleTo, mpImageBarBackground, 0.1f);
                FUN_00828ef0(pCtx, mpFullBarRenderable);
            }
            pCtx->AddRenderable(mpFullBarRenderable);
            return true;
        }

        ArcSegment segments[2];
        segments[0].mSide = 1;
        segments[0].mAngleEnd = mArcAngleTo;
        segments[0].mAngleStart = mArcAngleTo - mSideInfos[1].mArcSize;
        segments[0].mpImage = mpImageBarNotch;
        segments[1].mSide = 0;
        segments[1].mAngleEnd = mArcAngleFrom;
        segments[1].mAngleStart = mArcAngleFrom + mSideInfos[0].mArcSize;
        segments[1].mpImage = mpImageLeftBarEndNotch;

        for (int nSegment = 0; nSegment < 2; ++nSegment) {
            ArcSegment& segment = segments[nSegment];
            cSideInfo& side = mSideInfos[segment.mSide];
            bool bArcChanged = side.mArcSize != side.mArcSizeTarget;
            if (side.mRounds.mpBegin != side.mRounds.mpEnd) {
                if (!bArcChanged || side.mpDraw == 0) {
                    if (side.mpDraw) {
                        IViewEffect* pOld = side.mpDraw;
                        side.mpDraw = 0;
                        pOld->Release();
                    }
                    void* pBatch;
                    if (bArcChanged) {
                        pBatch = FUN_00828e30(pCtx, pWindow, (void**)&side.mpDraw);
                    } else {
                        pBatch = pCtx->Begin2D(0);
                    }
                    FUN_00e31d60(pBatch, mArcCenter.x, mArcCenter.y, mArcRadius, -1, -1,
                                 segment.mAngleEnd, segment.mAngleStart, mpImageBarBackground,
                                 0.1f);
                    FUN_00e32b20(pBatch, mArcCenter.x, mArcCenter.y, mArcRadius, -1, -1,
                                 segment.mAngleStart, segment.mpImage);
                    FUN_00828ef0(pCtx, side.mpDraw);
                }
                if (side.mpDraw)
                    pCtx->AddRenderable((IRenderable*)side.mpDraw);
            }
        }

        if ((uint)mSegmentCount > 0) {
            if (mpSegmentsRenderable) {
                IRenderable* pOld = mpSegmentsRenderable;
                mpSegmentsRenderable = 0;
                pOld->Release();
            }
            void* pBatch = FUN_00828e30(pCtx, pWindow, (void**)&mpSegmentsRenderable);

            float fLow = mArcAngleFrom < mArcAngleTo ? mArcAngleFrom : mArcAngleTo;
            float fCount = (float)(mSegmentCount * 2);
            float fStep = (mArcAngleTo - mArcAngleFrom) / fCount;

            float fNext = 0.0f;
            if (0.0f < fCount) {
                do {
                    FUN_00e32b20(pBatch, mArcCenter.x, mArcCenter.y, mArcRadius, 0x8f000000,
                                 0x8f000000, fNext * fStep + fLow, mpImageBar);
                    fNext = fNext + 1.0f;
                } while (fNext < fCount);
            }
            FUN_00e32b20(pBatch, mArcCenter.x, mArcCenter.y, mArcRadius, 0x8f000000, 0x8f000000,
                         (fNext * fStep + fLow) - 0.01f, mpImageBar);
            FUN_00828ef0(pCtx, mpSegmentsRenderable);
        }
        pCtx->AddRenderable(mpSegmentsRenderable);
        return true;
    }
    // IWinProc::DoMessage (0x00950ef0): the base message handler.
    return IWinProc::DoMessage(pWindow, pMessageRaw);
}

// ---------------------------------------------------------------------------
// UI::cUISporepediaPlanetLargeAssetView
// ---------------------------------------------------------------------------
// The ctor installs three vtables: the view itself at +0x00, the "PA_Agg" base at +0x04 and the
// content-validation summarizer base at +0x08.
struct PA_Agg : public IUnknown32 {
};
struct cContentValidationSummarizer : public IUnknown32 {
};

class cUISporepediaPlanetLargeAssetView : public IWinProc,
                                          public PA_Agg,
                                          public cContentValidationSummarizer {
 public:
    cUISporepediaPlanetLargeAssetView();          // 0x00e33de0
    ~cUISporepediaPlanetLargeAssetView();         // 0x00e33e70

    void Destroy();                               // 0x00e33f30
    void ReleaseWindows();                        // 0x00e33f90
    void LoadLayout();                            // 0x00e34020

    void* mpUnused0c;                             // +0x0c
    AutoRefCount<cSPUILayout> mpLayout;           // +0x10
    AutoRefCount<IWindow> mpIconWindow;           // +0x14
    AutoRefCount<IWindow> mpIcon2Window;          // +0x18
    AutoRefCount<IWindow> mpTitleWindow;          // +0x1c
    AutoRefCount<IWindow> mpDescriptionWindow;    // +0x20
    AutoRefCount<IWindow> mpValueWindow;          // +0x24
    AutoRefCount<ColourCfg> mpColourCfg;          // +0x28
    AutoRefCount<IViewNameProvider> mpNameProvider;   // +0x2c
    AutoRefCount<IUnknown32> mpMessageListener;       // +0x30
    IViewEffect* mpEffects[5];                    // +0x34 .. +0x44 (not released by the dtor)
    bool mbVisible;                               // +0x48
    bool mbInitialized;                           // +0x49
    bool mbPending;                               // +0x4a
};

// @ 0x00e33de0
cUISporepediaPlanetLargeAssetView::cUISporepediaPlanetLargeAssetView()
    : mpUnused0c(0), mbVisible(false), mbInitialized(false), mbPending(false)
{
    for (int i = 0; i < 5; ++i)
        mpEffects[i] = 0;
}

// @ 0x00e33e70
cUISporepediaPlanetLargeAssetView::~cUISporepediaPlanetLargeAssetView()
{
    if (mpMessageListener)
        mpMessageListener->Release();
    if (mpNameProvider)
        mpNameProvider->Release();
    if (mpColourCfg)
        mpColourCfg->Release();
    mpValueWindow = 0;
    mpDescriptionWindow = 0;
    mpTitleWindow = 0;
    mpIcon2Window = 0;
    mpIconWindow = 0;
    mpLayout = 0;
}

// ---------------------------------------------------------------------------
// 0x00e33f30 -- UI::cUISporepediaPlanetLargeAssetView::Destroy
// ---------------------------------------------------------------------------
class cViewModel {
 public:
    void Unload();                               // 0x005f0a60
};
cViewModel* __stdcall CastToViewModel(void* pModel);        // 0x00401020

// @ 0x00e33f30
void cUISporepediaPlanetLargeAssetView::Destroy()
{
    mbVisible = false;
    if (mpMessageListener) {
        CastToViewModel(mpMessageListener.Get())->Unload();
        mpMessageListener = 0;
    }
    if (mpLayout) {
        mpLayout->Shutdown(1);
        mpLayout = 0;
    }
}

// ---------------------------------------------------------------------------
// 0x00e33f90 -- UI::cUISporepediaPlanetLargeAssetView::ReleaseWindows
// ---------------------------------------------------------------------------
// @ 0x00e33f90
void cUISporepediaPlanetLargeAssetView::ReleaseWindows()
{
    if (!mbInitialized)
        return;
    if (mpColourCfg)
        mpColourCfg->ResetColour();
    mpColourCfg = 0;
    if (mpIcon2Window)
        mpIcon2Window->SetWinProc((IWinProc*)(PA_Agg*)this);
    mpIcon2Window = 0;
    mpTitleWindow = 0;
    mpDescriptionWindow = 0;
    mbInitialized = false;
}

// ---------------------------------------------------------------------------
// 0x00e34020 -- UI::cUISporepediaPlanetLargeAssetView::LoadLayout
// ---------------------------------------------------------------------------
// @ 0x00e34020
void cUISporepediaPlanetLargeAssetView::LoadLayout()
{
    if (mbInitialized)
        return;

    mpIconWindow = mpLayout->FindWindowByID(0xf3c6dc19, true);
    if (mpIconWindow.Get()) {
        mpIconWindow->SetLayoutArea((void*)(PA_Agg*)this);
        SetWindowAreaToParent(mpIconWindow.Get());
    }

    mpTitleWindow = mpLayout->FindWindowByID(0x53d6fe29, true);
    if (mpTitleWindow.Get() && mpNameProvider) {
        const wchar_t* pText = mpNameProvider->GetTitle();
        if (!pText)
            pText = gMissingText;
        mpTitleWindow->SetCaption(pText);
    }

    mpDescriptionWindow = mpLayout->FindWindowByID(0x53d6fe2a, true);
    if (mpDescriptionWindow.Get() && mpNameProvider) {
        const wchar_t* pText = mpNameProvider->GetDescription();
        if (!pText)
            pText = gMissingText;
        mpDescriptionWindow->SetCaption(pText);
    }

    mpValueWindow = mpLayout->FindWindowByID(0x5e62a30, true);

    ColourCfg* pCfg = (ColourCfg*)operator new(0x20, gColourCfgName, 0, 0, 0, 0);
    if (pCfg)
        pCfg = new (pCfg) ColourCfg();
    mpColourCfg = pCfg;
    mpColourCfg->ApplyLayout(mpLayout.Get());
    mbInitialized = true;
}

// ---------------------------------------------------------------------------
// 0x00e33d40 -- free helper: push the selected large-asset value into the property list
// ---------------------------------------------------------------------------
// @ 0x00e33d40
void __stdcall SetSporepediaLargeAssetValue(void* pValue)
{
    SP::PropertyManager()->SetProperty(0x120b89ce, pValue);
}

// ---------------------------------------------------------------------------
// SP::cSPSwatch and the Sporepedia swatch view built on it
// ---------------------------------------------------------------------------
struct IHandler : public IUnknown32 {
};

// SP::cSPSwatch, only the pieces touched by this slice. Its three vtable slots are at
// +0x00 (win proc), +0x04 (refcount) and +0x0c (handler); sizeof(SP::cSPSwatch) == 0x140.
class cSPSwatch : public IWinProc, public RefCountVTemplate, public IHandler {
 public:
    cSPSwatch();                                             // 0x005f6bd0
    void AddModelKey(EA::ResourceMan::Key const& key);       // 0x005f58f0
    void Shutdown();                                         // 0x005f68a0

    unsigned char mPad10[0x140 - 0x10];                      // +0x10 .. +0x13f
};

// The swatch view that shows a large Sporepedia asset.
class cSPUISwatchView : public cSPSwatch {
 public:
    cSPUISwatchView();                                       // 0x00e34220
    void AddConfiguredModelKey();                            // 0x00e33d60
    void ShutdownView();                                     // 0x00e33d70

    unsigned char mPad140[0x17c - 0x140];                    // +0x140 .. +0x17b
    EA::ResourceMan::Key mConfiguredModelKey;                // +0x17c
    void* mpUnused184;                                       // +0x184
    void* mpUnused188;                                       // +0x188
    AutoRefCount<IViewEffect> mpEffectA;                     // +0x18c
    AutoRefCount<IViewEffect> mpEffectB;                     // +0x190
};

// @ 0x00e33d60
void cSPUISwatchView::AddConfiguredModelKey()
{
    AddModelKey(mConfiguredModelKey);
}

// @ 0x00e34220
cSPUISwatchView::cSPUISwatchView()
    : mpUnused184(0), mpUnused188(0)
{
}

// @ 0x00e33d70
void cSPUISwatchView::ShutdownView()
{
    if (mpEffectA) {
        mpEffectA->Stop(true);
        mpEffectA = 0;
    }
    if (mpEffectB) {
        mpEffectB->Stop(true);
        mpEffectB = 0;
    }
    Shutdown();
}
