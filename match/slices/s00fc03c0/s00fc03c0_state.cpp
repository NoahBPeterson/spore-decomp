// Slice s00fc03c0 -- core terrain-state value copy and the reset of the terrain globals.
//   00fc03c0  SP::cTerrainStateMgr::cStateParms::operator=
//   00fc0fe0  ResetTerrainGlobals
// Layout (retail, 0x2ec bytes): see the assignment body for the member offsets.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast.
#include "types.h"

// ---- EASTL containers --------------------------------------------------------
struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };

// 20-byte eastl::vector (begin/end/capacity + 8-byte allocator), assignment is out of line.
template <class T>
struct eastl_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator0;
    uint32_t mAllocator1;
    eastl_vector& operator=(const eastl_vector& other);
};
typedef eastl_vector<Vector2> Vector2Vector;

// ---- refcounted pointer (assignment is the usual add-ref/store/release) ------
struct IRefCounted {
    virtual void AddRef();      // +0x00
    virtual void Release();     // +0x04
};

template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pOld = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pOld)
                pOld->Release();
        }
        return *this;
    }
};

// Three adjacent texturing members copied as one record: the vector table followed by two
// scale floats. MSVC keeps the record address in esi/edi across the vector assignment.
struct TexturingParms {
    Vector2Vector mTable;           // +0x00
    float m134;                     // +0x14
    float m138;                     // +0x18
    TexturingParms& operator=(const TexturingParms& other)
    {
        mTable = other.mTable;
        m134 = other.m134;
        m138 = other.m138;
        return *this;
    }
};

// ---- sub-records whose copies live out of line -------------------------------
struct PlanarDef {                  // 0xa0 bytes: five floats + seven vectors
    uint32_t mData[0xa0 / 4];
    PlanarDef& operator=(const PlanarDef& other);
};

struct TerrainRecord {              // 0x6c bytes
    uint32_t mData[0x6c / 4];
    void Assign(const TerrainRecord& other);
};

struct StateOutputParms {           // 0x90 bytes
    uint32_t mData[0x90 / 4];
    StateOutputParms& operator=(const StateOutputParms& other);
};

// ---- SP::cTerrainStateMgr::cStateParms --------------------------------------
namespace SP {
struct cTerrainStateMgr {
    struct cStateParms;
};

struct cTerrainStateMgr::cStateParms {
    struct PodBlock { uint32_t m[0x118 / 4]; };

    PodBlock mPlanetaryParms;       // +0x000 opaque value block
    uint32_t m118;                  // +0x118
    uint32_t m11c;                  // +0x11c
    TexturingParms mTexturingParms; // +0x120
    PlanarDef mTerrainParms;        // +0x13c
    float m1dc;                     // +0x1dc
    float m1e0;                     // +0x1e0
    float m1e4;                     // +0x1e4
    float m1e8;                     // +0x1e8
    AutoRefCount<IRefCounted> m1ec; // +0x1ec
    TerrainRecord mScatterParms;    // +0x1f0
    StateOutputParms mOutputParms;  // +0x25c

    cStateParms* Reset();                                   // 0x00fbe050
    void DestroySubObjects();                               // 0x00fbcd80
    cStateParms& operator=(const cStateParms& other);
};
}

// @ 0x00fc03c0
SP::cTerrainStateMgr::cStateParms& SP::cTerrainStateMgr::cStateParms::operator=(const cStateParms& other)
{
    mPlanetaryParms = other.mPlanetaryParms;
    m118 = other.m118;
    m11c = other.m11c;
    mTexturingParms = other.mTexturingParms;
    mTerrainParms = other.mTerrainParms;
    m1dc = other.m1dc;
    m1e0 = other.m1e0;
    m1e4 = other.m1e4;
    m1e8 = other.m1e8;
    m1ec = other.m1ec.mpObject;
    mScatterParms.Assign(other.mScatterParms);
    mOutputParms = other.mOutputParms;
    return *this;
}

// ---- render state ------------------------------------------------------------
struct ImageRef {
    void* mpResource;
};

template <class T>
struct RefPtr {
    T* mpObject;
};

struct RenderState {                // 0x2b8 bytes
    ImageRef images[14];            // +0x000
    RefPtr<IRefCounted> refs[8];    // +0x038
    uint32_t mScalars[(0x2b8 - 0x58) / 4];

    void ReleaseImages();                                   // 0x00fb9fc0
    RenderState& operator=(const RenderState& other);       // 0x00fbce30
};

// ---- terrain globals ---------------------------------------------------------
extern SP::cTerrainStateMgr::cStateParms gCoreState;   // 0x016d6788
extern RenderState gRenderState;                       // 0x016d6a78
extern IRefCounted* gTerrainLayerTable[];              // 0x016d6d30, 16 entries
extern IRefCounted* gTerrainLayerTable2[];             // 0x016d6d70, 16 entries

// @ 0x00fc0fe0
void ResetTerrainGlobals()
{
    {
        SP::cTerrainStateMgr::cStateParms state;
        gCoreState = *state.Reset();
        state.DestroySubObjects();
    }

    {
        RenderState renderState;
        void** refs = &renderState.images[0].mpResource;    // 22 reference slots, images then refs
        for (unsigned i = 0; i < 22; i++)
            refs[i] = 0;
        gRenderState = renderState;
        renderState.ReleaseImages();
    }

    for (unsigned i = 0; i < 16; i++) {
        IRefCounted* p = gTerrainLayerTable[i];
        if (p) {
            gTerrainLayerTable[i] = 0;
            p->Release();
        }
    }
    for (unsigned i = 0; i < 16; i++) {
        IRefCounted* p = gTerrainLayerTable2[i];
        if (p) {
            gTerrainLayerTable2[i] = 0;
            p->Release();
        }
    }
}
