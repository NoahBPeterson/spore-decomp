// Slice s007ba350 — SP::cThumbnailManager::InitPostProcessEffect  (0x007ba350, 4887 bytes)
//
// Builds the post-process filter chain used for thumbnails.  `type` selects the effect:
//   6/7/8/9  (only when `enable`): one base filter (material 0x88549f64 when `alt`, else
//            0x0fa800f3) from the renderer's current target into mThumbRectID (type 7) or
//            mBlurThumbRectID1; type 6 adds a 2-pass separable blur + combine, type 8 a
//            directional blur (offset/strength) + combine.
//   1        raster-sourced filter (texture 0x918c362c/0x40607300) into mThumbRectID.
//   2        material 0x46 thumb -> thumb filter.
//   5        threshold pipeline: allocates two half-size RTTs and a full-size temp RTT, two
//            threshold filters, four quadrant colour filters and a final copy back.
// Every filter is an EA::AutoRefCount<cJobPostFilter> appended to `chain`.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-  (movss/xorps, no frame pointer, EH frame, no cookie)
// Retail cJobPostFilter is 0xe4 bytes (the 2008 PDB's is 0xa8); offsets below are retail.

#include <new>
#include "types.h"

namespace rw { namespace graphics {
struct Raster {
    uint32_t pad0[3];
    unsigned short m_width;   // +0xc
    unsigned short m_height;  // +0xe
};
} }

namespace EA {
template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0

namespace SP {

struct cRenderTargetRectID {
    int mPageID;
    int mAllocID;
    cRenderTargetRectID() : mPageID(-1), mAllocID(-1) {}
};

struct Vector2 {
    float x, y;
    Vector2() {}
    Vector2(float ax, float ay) : x(ax), y(ay) {}
};
inline Vector2 operator*(const Vector2& v, float s) { return Vector2(v.x * s, v.y * s); }

struct Vector4 {
    float x, y, z, w;
    Vector4() {}
    Vector4(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
};

struct cSPColorRGBA {
    float r, g, b, a;
    cSPColorRGBA() {}
    cSPColorRGBA(float ar, float ag, float ab, float aa) : r(ar), g(ag), b(ab), a(aa) {}
    cSPColorRGBA(const cSPColorRGBA& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
};

namespace eastl_ {
template <typename T>
struct sp_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[3];
    void DoInsertValue(T* position, const T& value);  // 0x006ec390
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
}

class cILayer {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

class cTextureInstance {
public:
    rw::graphics::Raster* GetRaster();  // 0x0046f260
};

class cTextureManager {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual cTextureInstance* GetTexture(uint32_t instance, uint32_t group, int flags);  // +0x20
};
cTextureManager* TextureManager();  // 0x0067dd60

class cRenderer {
public:
#define PV(n) virtual void pv##n();
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
    PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56)
    virtual void GetCurrentRenderTarget(cRenderTargetRectID* pRect);  // +0xe4
};
cRenderer* Renderer();  // 0x0067dd40

class cIRTTManager {
public:
    PV(0) PV(1) PV(2) PV(3)
    virtual cRenderTargetRectID AllocateRTT(int width, int height, int format, int a, int b, int c);  // +0x10
    PV(5) PV(6) PV(7) PV(8)
    virtual void GetRTTInfo(cRenderTargetRectID id, int* x, int* y, int* width, int* height);  // +0x24
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    virtual void SetRTTName(cRenderTargetRectID id, const char* name);  // +0x48
};

class cThumbnailManager {
public:
    class cJobPostFilter;
    class cFilterChainJob;

    uint32_t pad0[4];
    rw::graphics::Raster* mThumbRaster;           // +0x10
    cRenderTargetRectID mThumbRectID;             // +0x14
    cRenderTargetRectID mBlurThumbRectID1;        // +0x1c
    cRenderTargetRectID mBlurThumbRectID2;        // +0x24
    cRenderTargetRectID mTempThumbnailBuffer;     // +0x2c
    uint32_t pad1[(0x10b4 - 0x34) / 4];
    cIRTTManager* mRTTMgr;                        // +0x10b4

    void InitPostProcessEffect(int type, cFilterChainJob* pChain, bool enable, bool alt,
                               Vector2 blurOffset, float blurStrength);
};

class cThumbnailManager::cJobPostFilter : public cILayer {
public:
    uint32_t mRefCountV[2];                       // +0x04 RefCountVTemplate
    unsigned int mMaterialId;                     // +0x0c
    cRenderTargetRectID mSrcRectID;               // +0x10
    rw::graphics::Raster* mSrcRaster;             // +0x18
    cRenderTargetRectID mDestRectID;              // +0x1c
    eastl_::sp_vector<cRenderTargetRectID> mAdditionalRectIDs;  // +0x24
    float mCustomParams[16];                      // +0x3c
    unsigned int mCallNumber;                     // +0x7c
    bool mInitialized;                            // +0x80
    bool mDumpTexture;                            // +0x81
    bool mClearBeforeDraw;                        // +0x82
    bool mOverrideViewport;                       // +0x83
    int mViewX, mViewY, mViewW, mViewH;           // +0x84
    int mQuadrant;                                // +0x94
    cSPColorRGBA mClearColor;                     // +0x98
    uint32_t mPreSetViewport;                     // +0xa8
    Vector2 mBlurA, mBlurB, mBlurC, mBlurD;       // +0xac
    float mBlurStrength;                          // +0xcc
    uint32_t pad2[(0xe4 - 0xd0) / 4];

    cJobPostFilter();                             // 0x007b8550
    virtual int AddRef();
    virtual int Release();
    void Initialize(int flags);                   // 0x007b9420
    void InitBlur(int taps, const cRenderTargetRectID& src, const cRenderTargetRectID& dest, int flags);  // 0x007b9510

    void SetCustomParams(int index, const Vector4& v);  // 0x007b3a30

    void SetClearColor(cSPColorRGBA color)        // 0x007b27a0
    {
        mClearColor = color;
        mClearBeforeDraw = true;
    }
    void SetViewport(int x, int y, int w, int h, int quadrant)  // 0x007b27e0
    {
        mViewX = x;
        mViewY = y;
        mViewW = w;
        mViewH = h;
        mOverrideViewport = true;
        mQuadrant = quadrant;
    }
    void SetBlurParams(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d, float strength)  // 0x007b2820
    {
        mBlurA = a;
        mBlurB = b;
        mBlurC = c;
        mBlurD = d;
        mBlurStrength = strength;
    }
    void AddAdditionalRect(const cRenderTargetRectID& id)  // 0x007b9690
    {
        mAdditionalRectIDs.push_back(id);
    }
};

void cThumbnailManager::cJobPostFilter::SetCustomParams(int index, const Vector4& v)
{
    mCustomParams[index * 4 + 0] = v.x;
    mCustomParams[index * 4 + 1] = v.y;
    mCustomParams[index * 4 + 2] = v.z;
    mCustomParams[index * 4 + 3] = v.w;
}

class cThumbnailManager::cFilterChainJob {
public:
    void AddFilter(cJobPostFilter* pFilter);      // 0x007b9750
};

typedef EA::AutoRefCount<cThumbnailManager::cJobPostFilter> FilterPtr;

void cThumbnailManager::InitPostProcessEffect(int type, cFilterChainJob* pChain, bool enable, bool alt,
                                              Vector2 blurOffset, float blurStrength)
{
    cRenderTargetRectID srcRect;

    if (type == 6 || type == 7 || type == 8 || type == 9) {
        if (!enable)
            return;
        Renderer()->GetCurrentRenderTarget(&srcRect);

        FilterPtr filter = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
        filter->Initialize(0);
        if (alt) {
            filter->mMaterialId = 0x88549f64;
            filter->mSrcRectID = srcRect;
            filter->mDestRectID = (type == 7) ? mThumbRectID : mBlurThumbRectID1;
            filter->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));
            filter->mCustomParams[0] = 1.2f;
            filter->mCustomParams[1] = 1.0f;
            filter->mCustomParams[2] = 0.0f;
            filter->mCustomParams[3] = 1.0f;
            filter->mCustomParams[4] = 0.0f;
            filter->mCustomParams[5] = 1.0f;
            filter->mCustomParams[6] = 1.0f;
            filter->mCustomParams[7] = 0.0f;
        } else {
            filter->mMaterialId = 0x0fa800f3;
            filter->mSrcRectID = srcRect;
            filter->mDestRectID = (type == 7) ? mThumbRectID : mBlurThumbRectID1;
            filter->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));
            filter->mCustomParams[0] = 1.0f;
            filter->mCustomParams[1] = 1.0f;
            filter->mCustomParams[2] = 1.0f;
            filter->mCustomParams[3] = 1.0f;
            filter->mCustomParams[4] = 0.0f;
            filter->mCustomParams[5] = 1.2f;
            filter->mCustomParams[6] = 1.2f;
            filter->mCustomParams[7] = 0.0f;
        }
        filter->mCustomParams[15] = 0.0f;
        filter->mCustomParams[14] = 0.0f;
        filter->mCustomParams[13] = 0.0f;
        filter->mCustomParams[12] = 0.0f;
        pChain->AddFilter(filter);

        if (type == 6) {
            FilterPtr blurH = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
            FilterPtr blurV = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
            FilterPtr combine = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();

            blurH->InitBlur(100, mBlurThumbRectID1, mThumbRectID, 0);
            blurH->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));
            blurV->InitBlur(100, mThumbRectID, mBlurThumbRectID2, 0);
            blurV->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));
            blurH->mCustomParams[0] = 1.0f;
            blurH->mCustomParams[1] = -1.0f;
            blurH->mCustomParams[2] = -1.0f;
            blurH->mCustomParams[3] = 0.0f;
            blurV->mCustomParams[0] = 1.0f;
            blurV->mCustomParams[1] = -1.0f;
            blurV->mCustomParams[2] = 1.0f;
            blurV->mCustomParams[3] = 0.0f;

            combine->Initialize(0);
            combine->mMaterialId = 0xad3dd399;
            combine->mSrcRectID = mBlurThumbRectID1;
            combine->AddAdditionalRect(mBlurThumbRectID2);
            combine->mCustomParams[0] = 1.0f / (float)mThumbRaster->m_width;
            combine->mCustomParams[1] = 1.0f / (float)mThumbRaster->m_height;
            combine->mCustomParams[2] = 0.0f;
            combine->mCustomParams[3] = 0.0f;
            combine->mDestRectID = mThumbRectID;
            combine->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));

            pChain->AddFilter(blurH);
            pChain->AddFilter(blurV);
            pChain->AddFilter(combine);
        } else if (type == 8) {
            FilterPtr blur = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
            FilterPtr combine = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();

            blur->Initialize(0);
            blur->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));
            blur->mMaterialId = 0x2a4a174c;
            blur->mSrcRectID = mBlurThumbRectID1;
            blur->mCustomParams[0] = 1.0f / (float)mThumbRaster->m_width;
            blur->mCustomParams[1] = 1.0f / (float)mThumbRaster->m_height;
            blur->mCustomParams[2] = 0.0f;
            blur->mCustomParams[3] = 0.0f;
            blur->mDestRectID = mBlurThumbRectID2;
            Vector2 offset = blurOffset * -0.2f;
            blur->SetBlurParams(offset, offset, blurOffset, blurOffset, blurStrength);

            combine->Initialize(0);
            combine->mMaterialId = 0xda76c2bf;
            combine->mSrcRectID = mBlurThumbRectID1;
            combine->mDestRectID = mThumbRectID;
            combine->AddAdditionalRect(mBlurThumbRectID2);
            combine->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));

            pChain->AddFilter(blur);
            pChain->AddFilter(combine);
        }
    } else if (type == 1) {
        FilterPtr filter = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
        cTextureInstance* pTexture = TextureManager()->GetTexture(0x918c362c, 0x40607300, 0);
        if (pTexture) {
            rw::graphics::Raster* pRaster = pTexture->GetRaster();
            filter->Initialize(0);
            filter->mMaterialId = 0xf515ba42;
            filter->mSrcRaster = pRaster;
            filter->mDestRectID = mThumbRectID;
            filter->SetCustomParams(0, Vector4(6.0f, 6.0f, 5.0f, 5.0f));
            filter->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));
            pChain->AddFilter(filter);
        }
    } else if (type == 2) {
        FilterPtr filter = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
        filter->Initialize(0);
        filter->mMaterialId = 0x46;
        filter->mSrcRectID = mThumbRectID;
        filter->mDestRectID = mThumbRectID;
        filter->SetCustomParams(0, Vector4(0.8f, 0.5f, 0.3f, 1.0f));
        filter->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));
        pChain->AddFilter(filter);
    } else if (type == 5) {
        int x, y, width, height;
        mRTTMgr->GetRTTInfo(mThumbRectID, &x, &y, &width, &height);
        int halfWidth = width / 2;
        int halfHeight = height / 2;

        cRenderTargetRectID id = mRTTMgr->AllocateRTT(halfWidth, halfHeight, 0x15, 0, -1, 0);
        mBlurThumbRectID1 = id;
        mRTTMgr->SetRTTName(id, "ThumbnailThresholdRTT1");
        id = mRTTMgr->AllocateRTT(halfWidth, halfHeight, 0x15, 0, -1, 0);
        mBlurThumbRectID2 = id;
        mRTTMgr->SetRTTName(id, "ThumbnailThresholdRTT2");
        id = mRTTMgr->AllocateRTT(width, height, 0x15, 0, -1, 0);
        mTempThumbnailBuffer = id;
        mRTTMgr->SetRTTName(id, "ThumbnailFullsizeTemp");

        FilterPtr threshold1 = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
        threshold1->Initialize(0);
        threshold1->mMaterialId = 0x5b6fc7d2;
        threshold1->mSrcRectID = mThumbRectID;
        threshold1->mDestRectID = mBlurThumbRectID1;
        threshold1->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));

        FilterPtr threshold2 = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
        threshold2->Initialize(0);
        threshold2->mMaterialId = 0x5b6fc7d1;
        threshold2->mSrcRectID = mThumbRectID;
        threshold2->mDestRectID = mBlurThumbRectID2;
        threshold2->SetClearColor(cSPColorRGBA(0.0f, 0.0f, 0.0f, 0.0f));

        FilterPtr quad1 = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
        FilterPtr quad2 = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
        FilterPtr quad3 = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
        FilterPtr quad4 = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();
        FilterPtr copyBack = new ("Graphics", 0, 0, 0, 0) cJobPostFilter();

        quad1->Initialize(0);
        quad1->mMaterialId = 0x050c0e26;
        quad1->AddAdditionalRect(mBlurThumbRectID1);
        quad1->AddAdditionalRect(mBlurThumbRectID2);
        quad1->mSrcRectID = mThumbRectID;
        quad1->mDestRectID = mTempThumbnailBuffer;
        quad1->SetViewport(0, 0, halfWidth, halfHeight, 1);
        quad1->SetCustomParams(0, Vector4(0.9453125f, 0.76171875f, 0.30078125f, 0.0f));
        quad1->SetCustomParams(1, Vector4(0.5234375f, 0.7109375f, 0.7265625f, 0.0f));
        quad1->SetCustomParams(3, Vector4(0.9296875f, 0.83203125f, 0.8046875f, 0.0f));
        quad1->SetClearColor(cSPColorRGBA(1.0f, 1.0f, 1.0f, 1.0f));

        quad2->Initialize(0);
        quad2->mMaterialId = 0x050c0e26;
        quad2->AddAdditionalRect(mBlurThumbRectID1);
        quad2->AddAdditionalRect(mBlurThumbRectID2);
        quad2->mSrcRectID = mThumbRectID;
        quad2->mDestRectID = mTempThumbnailBuffer;
        quad2->SetViewport(halfWidth, 0, width, halfHeight, 2);
        quad2->SetCustomParams(0, Vector4(0.671875f, 0.3984375f, 0.37109375f, 0.0f));
        quad2->SetCustomParams(1, Vector4(0.77734375f, 0.640625f, 0.3828125f, 0.0f));
        quad2->SetCustomParams(3, Vector4(0.88671875f, 0.4765625f, 0.59765625f, 0.0f));

        quad3->Initialize(0);
        quad3->mMaterialId = 0x050c0e26;
        quad3->AddAdditionalRect(mBlurThumbRectID1);
        quad3->AddAdditionalRect(mBlurThumbRectID2);
        quad3->mSrcRectID = mThumbRectID;
        quad3->mDestRectID = mTempThumbnailBuffer;
        quad3->SetViewport(0, halfHeight, halfWidth, height, 3);
        quad3->SetCustomParams(0, Vector4(0.62109375f, 0.265625f, 0.24609375f, 0.0f));
        quad3->SetCustomParams(1, Vector4(0.30078125f, 0.4296875f, 0.34765625f, 0.0f));
        quad3->SetCustomParams(3, Vector4(0.54296875f, 0.63671875f, 0.38671875f, 0.0f));

        quad4->Initialize(0);
        quad4->mMaterialId = 0x050c0e26;
        quad4->AddAdditionalRect(mBlurThumbRectID1);
        quad4->AddAdditionalRect(mBlurThumbRectID2);
        quad4->mSrcRectID = mThumbRectID;
        quad4->mDestRectID = mTempThumbnailBuffer;
        quad4->SetViewport(halfWidth, halfHeight, width, height, 4);
        quad4->SetCustomParams(0, Vector4(0.92578125f, 0.63671875f, 0.41015625f, 0.0f));
        quad4->SetCustomParams(1, Vector4(0.9296875f, 0.8046875f, 0.84765625f, 0.0f));
        quad4->SetCustomParams(3, Vector4(0.44140625f, 0.68359375f, 0.80078125f, 0.0f));

        copyBack->Initialize(0);
        copyBack->mMaterialId = 0x28;
        copyBack->mSrcRectID = mTempThumbnailBuffer;
        copyBack->mDestRectID = mThumbRectID;
        copyBack->SetCustomParams(0, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
        copyBack->SetCustomParams(1, Vector4(0.0f, 1.0f, 1.0f, 0.0f));
        copyBack->SetCustomParams(3, Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        copyBack->SetClearColor(cSPColorRGBA(1.0f, 1.0f, 1.0f, 1.0f));

        pChain->AddFilter(threshold1);
        pChain->AddFilter(threshold2);
        pChain->AddFilter(quad1);
        pChain->AddFilter(quad2);
        pChain->AddFilter(quad3);
        pChain->AddFilter(quad4);
        pChain->AddFilter(copyBack);
    }
}

}  // namespace SP
