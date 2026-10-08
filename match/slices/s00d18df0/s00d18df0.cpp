// Slice s00d18df0: SP::cGameEditInputStrategy::DoSaveSelectedFile (0x00d18df0, 1633 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (same module as Init / HandleMessage).
//
// Level-editor "save selected" command: takes the selected gameplay markers, computes their
// centroid and a surface-aligned frame (planet normal + camera direction orthonormalised) at that
// centroid, opens "<name>.ltp" through the resource manager and writes one
// "GameplayMarkerTemplate a b c d <x> <y>" line per marker followed by its typed properties
// ("bool/int/uint/float/enum ...") and "end".
#include "types.h"
#include <math.h>

void operator delete(void* p);   // 0x00f47380 (operator delete[])
void* operator new[](unsigned int n, const char* name, int flags, unsigned int debugFlags,
                     const char* file, int line);   // 0x00f473a0

namespace eastl {
extern char gEmptyString[];   // 0x01667bac

struct allocator {
    void deallocate(void* p, unsigned int) { operator delete(p); }
};

template <class T> struct basic_string {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mAllocator;

    __forceinline basic_string() { AllocateSelf(); }
    ~basic_string() { DeallocateSelf(); }

    void AllocateSelf() {
        mpBegin = (T*)gEmptyString;
        mpEnd = (T*)gEmptyString;
        mpCapacity = (T*)gEmptyString + 1;
    }
    void DoFree(T* p, unsigned int n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
    }
    const T* c_str() const { return mpBegin; }
    int size() const { return (int)(mpEnd - mpBegin); }

    void sprintf(const T* fmt, ...);                        // 0x00472fe0 (char) / 0x0041e050 (wchar_t)
    void append_sprintf(const T* fmt, ...);                 // 0x005f9450 (char)
    void append(const T* pBegin, const T* pEnd);            // 0x00455d60 (char)
};
typedef basic_string<wchar_t> string16;
typedef basic_string<char> string8;
}  // namespace eastl

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

struct Vec3 { float x, y, z; };
struct Vec3c {                       // Vector3 with a user copy ctor (movss member copies)
    float x, y, z;
    Vec3c() {}
    Vec3c(const Vec3c& o) : x(o.x), y(o.y), z(o.z) {}
};

inline Vec3c Scale(const Vec3c& v, const float& s)
{
    Vec3c r;
    r.x = v.x * s;
    r.y = v.y * s;
    r.z = v.z * s;
    return r;
}

inline Vec3c& operator-=(Vec3c& a, const Vec3c& b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

struct ResKey { uint32_t instance, type, group; };

// ---------------------------------------------------------------- stream / resource manager
struct IWriter {
    PV8 PV4 PV2                                              // +0x00..+0x34
    virtual void Write(const void* pData, uint32_t size);    // +0x38
};

struct IRefCounted {
    PV
    virtual void AddRef();                                    // +0x04
    virtual void Release();                                   // +0x08
};

struct IFileStream : IRefCounted {
    PV2 PV                                                    // +0x0c..+0x14
    virtual IWriter* GetWriter();                             // +0x18
    PV2
    virtual void Close();                                     // +0x24
};

struct IRecordDB {
    PV8 PV4 PV
    virtual bool OpenRecord(ResKey* key, IFileStream** pStream, int mode, int access, int create,
                            int flags);                       // +0x34
};

struct IResourceManager {
    PV16 PV8 PV4 PV2                                          // +0x00..+0x74
    virtual void GetKey(ResKey* pKey, const wchar_t* pPath, uint32_t typeID, uint32_t groupID);  // +0x78
};
IResourceManager* GetManager();                               // 0x0067dcd0
IRecordDB* FindRecordDB(ResKey* key);                         // 0x00685d40 (cdecl)

// ---------------------------------------------------------------- editor objects
struct IMarkerPart {                                          // sub-object at marker +0x34
    PV8 PV2 PV
    virtual const Vec3* GetPosition();                        // +0x2c
    PV4 PV4
    virtual bool IsPlaced();                                  // +0x50
};

struct cGameplayMarkerCmd {                                   // object returned by Cast(0x36be278)
    uint32_t pad00[13];
    IMarkerPart part;                                         // +0x34
    uint32_t pad38[(0x108 - 0x38) / 4];
    uint32_t ids[4];                                          // +0x108
    uint32_t mCount;                                          // +0x118
    int mValues[32];                                          // +0x11c
};

struct ISelectable {
    PV16 PV16 PV8 PV4 PV2                                     // +0x00..+0xb4
    virtual cGameplayMarkerCmd* Cast(uint32_t typeID);        // +0xb8
};

struct SelectionList {
    ISelectable** mpBegin;                                    // +0x00
    ISelectable** mpEnd;                                      // +0x04
};
struct cEditSelection {
    char pad[0x40];
    SelectionList mSelected;                                  // +0x40
};
cEditSelection* GetEditSelection();                           // 0x00d1bf00

struct cPlanetModel {
    Vec3c* GetNormalAt(Vec3c* pOut, const Vec3c* pPos);          // 0x00b7e3b0 (thiscall, ret 8)
};
cPlanetModel* PlanetModel();                                  // 0x00b3d350
struct cCameraCtl {
    void GetDirection(Vec3c* pOut);                            // 0x00b13a10 (thiscall, ret 4)
};
cCameraCtl* GetCameraCtl();                                   // 0x00b3d280

bool __cdecl GetGameplayMarkerTypes(uint32_t id, uint32_t* pTypes);   // 0x00d16620

extern Vec3c gZeroVec3;                                        // 0x0169dc28

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T** operator&() { return &mpObject; }
    T* operator->() const { return mpObject; }
};

namespace SP {
struct cGameEditInputStrategy {
    void DoSaveSelectedFile(eastl::string16* pName);          // 0x00d18df0
};
}

// @ 0x00d18df0
void SP::cGameEditInputStrategy::DoSaveSelectedFile(eastl::string16* pName)
{
    SelectionList* pSel = &GetEditSelection()->mSelected;
    ISelectable** pBegin = pSel->mpBegin;
    ISelectable** pEnd = pSel->mpEnd;
    if (pBegin == pEnd)
        return;

    Vec3c sum(gZeroVec3);
    int count = 0;
    for (ISelectable** it = pBegin; it != pEnd; ++it) {
        if (*it) {
            cGameplayMarkerCmd* pMarker = (*it)->Cast(0x36be278);
            if (pMarker && pMarker->part.IsPlaced()) {
                const Vec3* pPos = pMarker->part.GetPosition();
                sum.x = pPos->x + sum.x;
                sum.y = pPos->y + sum.y;
                sum.z = pPos->z + sum.z;
                count++;
            }
        }
    }

    cCameraCtl* pCam = GetCameraCtl();
    if (count == 0 || !pCam)
        return;

    Vec3c centroid(Scale(sum, 1.0f / (float)(uint32_t)count));

    eastl::string16 path;
    path.sprintf(L"%s.%s", pName->c_str(), L"ltp");

    Vec3c n;
    PlanetModel()->GetNormalAt(&n, &centroid);
    Vec3c u;
    pCam->GetDirection(&u);

    // Gram-Schmidt: tangent = normalize(u - n * (n . u)), binormal = tangent x n
    float d = n.x * u.x + n.y * u.y + n.z * u.z;
    u -= Scale(n, d);
    Vec3c t(Scale(u, 1.0f / sqrtf(u.x * u.x + u.y * u.y + u.z * u.z + 1e-8f)));
    Vec3 b;
    b.x = t.y * n.z - t.z * n.y;
    b.y = t.z * n.x - n.z * t.x;
    b.z = n.y * t.x - t.y * n.x;

    IResourceManager* pMgr = GetManager();
    if (!pMgr)
        return;
    ResKey key;
    key.instance = 0;
    key.type = 0;
    key.group = 0;
    pMgr->GetKey(&key, path.c_str(), 0xf2b924b3, 0x72b924b5);
    IRecordDB* pDB = FindRecordDB(&key);
    if (!pDB)
        return;
    AutoRefCount<IFileStream> pStream;
    if (!pDB->OpenRecord(&key, &pStream, 2, 2, 1, 0))
        return;
    IWriter* pWriter = pStream->GetWriter();
    eastl::string8 line;
    for (ISelectable** it = pSel->mpBegin; it != pSel->mpEnd; ++it) {
        if (*it) {
            cGameplayMarkerCmd* pMarker = (*it)->Cast(0x36be278);
            if (pMarker && pMarker->part.IsPlaced()) {
                line.sprintf("GameplayMarkerTemplate %d %d %d %d", pMarker->ids[0], pMarker->ids[1],
                             pMarker->ids[2], pMarker->ids[3]);
                if (count == 1) {
                    line.append_sprintf(" %f %f\n", 0.0, 0.0);
                } else {
                    pMarker->part.GetPosition();
                    const Vec3* pPos = pMarker->part.GetPosition();
                    float dx = pPos->x - centroid.x;
                    float dy = pPos->y - centroid.y;
                    float dz = pPos->z - centroid.z;
                    double tx = dx * t.x + dy * t.y + dz * t.z;
                    double bx = dx * b.x + dy * b.y + dz * b.z;
                    line.append_sprintf(" %f %f\n", bx, tx);
                }
                uint32_t types[32];
                if (GetGameplayMarkerTypes(pMarker->ids[0], types)) {
                    for (uint32_t i = 0; i < pMarker->mCount; i++) {
                        switch (types[i]) {
                        case 1:
                            line.append_sprintf("bool %s\n", pMarker->mValues[i] == 1 ? "true" : "false");
                            break;
                        case 9:
                            line.append_sprintf("int %d\n", pMarker->mValues[i]);
                            break;
                        case 10:
                            line.append_sprintf("uint %d\n", pMarker->mValues[i]);
                            break;
                        case 13:
                            line.append_sprintf("float %f\n", (double)*(float*)&pMarker->mValues[i]);
                            break;
                        default:
                            line.append_sprintf("enum %d\n", pMarker->mValues[i]);
                            break;
                        }
                    }
                }
                line.append("end\n", "end\n" + 4);
                pWriter->Write(line.mpBegin, line.mpEnd - line.mpBegin);
                if (count == 1)
                    break;
            }
        }
    }
    pStream->Close();
}
