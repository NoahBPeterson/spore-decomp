// Slice s00b80630 -- rw::graphics::ImmediateMode / planet-layer event dispatch cluster.
//
// Modelled types:
//   Layer      the outer event layer (vtable pair, refcounted sub-objects)
//   Mode       an ImmediateMode-style object (cStaticBuffer at +8, render ranges)
//   RefArray   the refcounted vertex-range container stored at Layer+0x20
//
// Retail member offsets are read from the disassembly; the dev PDB layout differs,
// so objects are modelled locally with role-named members at retail offsets.

typedef unsigned int   u32;
typedef unsigned char  u8;
typedef int            i32;
typedef unsigned int   size_t;

extern "C" float sqrtf(float);
extern "C" float acosf(float);

#define FORCEINLINE __forceinline

// --------------------------------------------------------------- extern decls
extern "C" void *operator_new(u32 n, const char *pFile, int a, int b, int c, int d); // 0xf473a0
extern "C" void  operator_delete_array(void *p);                                     // 0xf47380

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long *, long);
extern "C" long __cdecl _InterlockedExchange(volatile long *, long);
extern "C" long __cdecl _InterlockedDecrement(volatile long *);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedDecrement)

extern const float kOne;      // 0x1485720 = 1.0f
extern const float kHalf;     // 0x1471064 = 0.5f
extern const float kEps;      // 0x146543c = 1.5258789e-05f
extern const float kByteScale;// 0x1465434 = 255.0f
extern const float k64;       // 0x140f334 = 64.0f
extern const float k128;      // 0x1400a58 = 128.0f
extern const float kZero;     // 0x1485378 = 0.0f
extern const float kNegOne;   // 0x13eb1bc = -1.0f
extern const float kGridStep; // 0x1471064 = 0.5f (same value, terrain reuse)
extern const u8    gPlaneOrder[]; // 0x14653b8 face-permutation table

struct Mode;
struct Layer;

// --------------------------------------------------------- refcounted objects
// +0x00 vtable, +0x04 atomic reference count, +0x08 payload.
struct RefObj {
    void         **m_vtbl;  // +0x00
    volatile long  m_ref;   // +0x04
    void          *m_data;  // +0x08
};

// ---------------------------------------------------- ImmediateMode-style mode
// Only the members touched by this cluster are named; the rest are padding.
struct RangeEntry {
    const void *m_begin;   // +0x00
    const void *m_end;     // +0x04
    u8          m_pad08[0x0c];
};

struct RangeSecondEntry {
    const void *m_ptr;     // +0x00
    u8          m_pad04[0x10];
};

struct Mode {
    void         **m_vtbl;          // +0x00
    volatile long  m_ref;           // +0x04
    void          *m_buffer;        // +0x08  cStaticBuffer*
    RangeSecondEntry *m_rangeSecond;// +0x0c  per-range second vertex pointer
    u8             m_pad10[0x10];   // +0x10
    RangeEntry    *m_ranges;        // +0x20  per-range span table, stride 0x14
    u8             m_pad24[0x10];   // +0x24
    u32           *m_idBegin;       // +0x34  planet-id vector begin
    u32           *m_idEnd;         // +0x38  planet-id vector end

    void Submit();                                   // 0x00b80b40
    void DrawMaterial(void *pMaterial, void *pParam); // 0x00b80a50
    void SetMaterialA(void *pParam);                 // 0x00b80a80
    void SetMaterialB(void *pParam);                 // 0x00b80ac0
    void SetMaterialC(void *pParam);                 // 0x00b80b00
    Mode *DeleteInstance(u32 flags);                 // 0x00b80ff0
    void BuildRibbon(const void *pVerts, const void *pOther, int count, u32 color); // 0x00b807e0
};

// The mode's +4 word is a reference count for the smart-pointer paths, so the
// generic release helpers below operate on Mode.
FORCEINLINE void AddModeRef(Mode *p)
{
    _InterlockedExchangeAdd(&p->m_ref, 1);
}

FORCEINLINE void ReleaseMode(Mode *p)
{
    if (p != 0) {
        long n = _InterlockedDecrement(&p->m_ref);
        if (n == 0) {
            _InterlockedExchange(&p->m_ref, 1);
            ((void (__thiscall *)(Mode *, int))((RefObj *)p)->m_vtbl[0])(p, 1);
        }
    }
}

// Destructor flavour: the original re-tests the pointer before the virtual call.
FORCEINLINE void DestroyMode(Mode *p)
{
    if (p != 0) {
        long n = _InterlockedDecrement(&p->m_ref);
        if (n == 0) {
            _InterlockedExchange(&p->m_ref, 1);
            if (p != 0) {
                ((void (__thiscall *)(Mode *, int))((RefObj *)p)->m_vtbl[0])(p, 1);
            }
        }
    }
}

FORCEINLINE void AssignMode(Mode **ppField, Mode *pNew)
{
    Mode *pOld = *ppField;
    if (pNew != pOld) {
        if (pNew != 0)
            _InterlockedExchangeAdd(&pNew->m_ref, 1);
        *ppField = pNew;
        if (pOld != 0) {
            long n = _InterlockedDecrement(&pOld->m_ref);
            if (n == 0) {
                _InterlockedExchange(&pOld->m_ref, 1);
                ((void (__thiscall *)(Mode *, int))((RefObj *)pOld)->m_vtbl[0])(pOld, 1);
            }
        }
    }
}

FORCEINLINE Mode *NewModifier()
{
    Mode *p = (Mode *)operator_new(0xc, "Simulator", 0, 0, 0, 0);
    if (p != 0) {
        p->m_vtbl = (void **)0x13ef094;
        _InterlockedExchange(&p->m_ref, 0);
        p->m_vtbl = (void **)0x146545c;
        ((RefObj *)p)->m_data = 0;
    } else {
        p = 0;
    }
    return p;
}

// --------------------------------------------- refcounted vertex-range payload
struct RefArray {
    void         **m_vtbl;   // +0x00
    u32            m_flags;  // +0x04
    u8             m_pad08[0x38];
    int            m_ref;    // +0x40
};

// --------------------------------------------------------------- outer layer
struct Layer {
    void     **m_vtbl;       // +0x00
    void     **m_vtbl2;      // +0x04
    volatile long m_lock8;   // +0x08
    u8         m_flag0c;     // +0x0c
    u8         m_pad0d[3];
    void      *m_p10;        // +0x10
    void      *m_p14;        // +0x14
    void      *m_p18;        // +0x18
    void      *m_p1c;        // +0x1c
    RefArray  *m_pRanges;    // +0x20
    Mode      *m_pMode;      // +0x24
    u8         m_flag28;     // +0x28
    u8         m_pad29[3];
    Mode      *m_pMod0;      // +0x2c
    Mode      *m_pMod1;      // +0x30
    Mode      *m_pMod2;      // +0x34

    Layer *Init();                                                   // 0x00b80630
    void   Destroy();                                                // 0x00b80d30
    void   StopAudio();                                              // 0x00b80e40
    void   DispatchEvent(void *p2, int event, void *pViewer, void *pMaterial); // 0x00b80ea0
};

// -------------------------------------------------------- drawing helper types
struct cStaticBuffer {
    void Dispatch(void *a, void *b);   // 0x007a3e60
};

struct Vertex {
    float x, y, z;
};

struct RibbonVertex {
    float x, y, z;    // +0x00
    u32   color;      // +0x0c
    float u;          // +0x10
    float v;          // +0x14
};

struct MaterialRef {
    void *m_unknown0;   // +0x00
    void *m_material;   // +0x04
};

struct MaterialManager {
    void *m_vtbl;       // +0x00
};

typedef MaterialRef *(__thiscall *FindMaterialFn)(MaterialManager *, u32);

extern "C" MaterialManager *SP_MaterialManager();   // 0x0067dd70
extern "C" void *FUN_0067dd50();                    // 0x0067dd50
extern "C" void *FUN_00761cf0(int n);               // 0x00761cf0
extern "C" void  FUN_007a4650();                    // 0x007a4650
extern "C" void  cSB_GetVertexBuffer(void *buf, int a, void *b, void *c); // 0x007a47c0
extern "C" void  cSB_Begin(void *buf, u32 a, u32 b, u32 c, u32 d);        // 0x007a4420
extern "C" void  cSB_Flush(void *buf);                                    // 0x007a4710

extern "C" void *SP_GetActiveTerrainSphere();       // 0x00f48aa0
extern "C" void *SP_GetUniverseContext();           // 0x01021080
extern "C" void *SP_PlanetModel();                  // 0x00b3d350
extern "C" void *SP_NounManager(int id);            // 0x00b3d300

struct EffectsDispatch_t {
    float m[4][4];
};
extern "C" void EffectsDispatch(EffectsDispatch_t *m, u32 n); // 0x005291f0

struct Viewer {
    bool Update();   // 0x007c4fd0
    void Finish();   // 0x007c3c10
};

struct ViewerHandle {
    Viewer *m_viewer;  // +0x00
};

struct PlanetRecord {
    int  m_noun;       // +0x00
    u8   m_pad04[0x0d];
    u8   m_flag11;     // +0x11
    u8   m_pad12[6];
};

struct PlanetModel {
    u8            m_pad00[0x80];
    PlanetRecord *m_records;   // +0x80
};

struct NounColor {
    u8    m_pad00[0xc4];
    float m_r;   // +0xc4
    float m_g;   // +0xc8
    float m_b;   // +0xcc
};

struct NounThing {
    NounColor *GetColor();   // 0x00b25f40
};

// The singleton holder at 0x15ddc84 points at the active static vertex buffer.
struct DrawHolder {
    void *m_draw;   // +0x00
    void Begin(u32 a, u32 b, u32 c, u32 d);   // 0x007a4420
};
extern DrawHolder *gDrawHolder;   // 0x15ddc84

struct Draw {
    void Flush();                                            // 0x007a4710
    void GetVertexBuffer(int a, void *b, void *c);           // 0x007a47c0
};

// ---------------------------------------------------------------------------
// @ 0x00b80630
Layer *Layer::Init()
{
    volatile int probe;
    m_vtbl = (void **)0x13f1ab0;
    m_vtbl2 = (void **)0x13ef094;
    _InterlockedExchange(&m_lock8, 0);
    m_vtbl = (void **)0x1465474;
    m_vtbl2 = (void **)0x1465470;
    m_flag0c = 0;
    m_p10 = 0;
    m_p14 = 0;
    m_p18 = 0;
    m_p1c = 0;
    m_pRanges = 0;
    m_pMode = 0;
    m_flag28 = 0;
    m_pMod0 = 0;
    m_pMod1 = 0;
    m_pMod2 = 0;
    AssignMode(&m_pMod0, NewModifier());
    AssignMode(&m_pMod1, NewModifier());
    AssignMode(&m_pMod2, NewModifier());
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00b80d30
void Layer::Destroy()
{
    volatile int probe;
    m_vtbl = (void **)0x1465474;
    m_vtbl2 = (void **)0x1465470;
    DestroyMode(m_pMod2);
    DestroyMode(m_pMod1);
    DestroyMode(m_pMod0);
    DestroyMode(m_pMode);
    if (m_pRanges != 0) {
        if (m_pRanges->m_ref <= 1) {
            void **iface = (void **)((RefObj *)m_pRanges)->m_vtbl[0];
            u32 flags = (m_pRanges->m_flags >> 31) & 1;
            ((void (__thiscall *)(void *, RefArray *, u32))iface[0x170 / 4])
                (((RefObj *)m_pRanges)->m_vtbl, m_pRanges, flags);
        } else {
            m_pRanges->m_ref--;
        }
    }
    if (m_p1c != 0) {
        ((void (__thiscall *)(void *))((RefObj *)m_p1c)->m_vtbl[1])(m_p1c);
    }
    m_vtbl = (void **)0x13eb938;
    m_vtbl2 = (void **)0x13ef094;
}

// ---------------------------------------------------------------------------
// @ 0x00b80e40
void Layer::StopAudio()
{
    volatile int probe;
    void *p = FUN_0067dd50();
    ((void (__thiscall *)(void *, int))((RefObj *)p)->m_vtbl[0x50 / 4])(p, 9);
    p = FUN_0067dd50();
    ((void (__thiscall *)(void *, int))((RefObj *)p)->m_vtbl[0x50 / 4])(p, 0x19);

    Mode *pMode = m_pMode;
    if (pMode != 0) {
        m_pMode = 0;
        long n = _InterlockedDecrement(&pMode->m_ref);
        if (n == 0) {
            _InterlockedExchange(&pMode->m_ref, 1);
            ((void (__thiscall *)(Mode *, int))((RefObj *)pMode)->m_vtbl[0])(pMode, 1);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00b80a50
void Mode::DrawMaterial(void *pMaterial, void *pParam)
{
    if (m_buffer != 0) {
        FUN_00761cf0(200);
        ((cStaticBuffer *)m_buffer)->Dispatch(pParam, ((MaterialRef *)pMaterial)->m_material);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00b80a80
void Mode::SetMaterialA(void *pParam)
{
    MaterialManager *mm = SP_MaterialManager();
    MaterialRef *pMaterial = ((FindMaterialFn)((void **)mm->m_vtbl)[0x28 / 4])(mm, 0x9276314a);
    if (pMaterial != 0 && m_buffer != 0) {
        ((cStaticBuffer *)m_buffer)->Dispatch(pParam, pMaterial->m_material);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00b80ac0
void Mode::SetMaterialB(void *pParam)
{
    MaterialManager *mm = SP_MaterialManager();
    MaterialRef *pMaterial = ((FindMaterialFn)((void **)mm->m_vtbl)[0x28 / 4])(mm, 0x32fb723);
    if (pMaterial != 0 && m_buffer != 0) {
        ((cStaticBuffer *)m_buffer)->Dispatch(pParam, pMaterial->m_material);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00b80b00
void Mode::SetMaterialC(void *pParam)
{
    MaterialManager *mm = SP_MaterialManager();
    MaterialRef *pMaterial = ((FindMaterialFn)((void **)mm->m_vtbl)[0x28 / 4])(mm, 0xc13ad5ef);
    if (pMaterial != 0 && m_buffer != 0) {
        ((cStaticBuffer *)m_buffer)->Dispatch(pParam, pMaterial->m_material);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00b80ff0
Mode *Mode::DeleteInstance(u32 flags)
{
    if (m_buffer != 0) {
        ((void (__thiscall *)(void *))((RefObj *)m_buffer)->m_vtbl[2])(m_buffer);
    }
    m_vtbl = (void **)0x13ef094;
    if (flags & 1)
        operator_delete_array(this);
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00b80b40
void Mode::Submit()
{
    if (m_buffer != 0) {
        void *pOld = m_buffer;
        m_buffer = 0;
        ((void (__thiscall *)(void *))((RefObj *)pOld)->m_vtbl[2])(pOld);
    }
    if (m_idBegin == m_idEnd)
        return;

    gDrawHolder->Begin(0, 4, 2, 0x1000);

    int i = 0;
    int n = (int)(m_idEnd - m_idBegin);
    if (n > 0) {
        do {
            PlanetModel *pModel = (PlanetModel *)SP_PlanetModel();
            u32 id = m_idBegin[i];
            PlanetRecord *pRec = &pModel->m_records[id];
            if (pRec->m_flag11 != 0) {
                float cr = 0.5f, cg = 0.5f, cb = 0.5f;
                int noun = pRec->m_noun;
                if (noun != -1) {
                    NounColor *pColor = ((NounThing *)SP_NounManager(noun))->GetColor();
                    if (pColor != 0) {
                        cr = pColor->m_r;
                        cg = pColor->m_g;
                        cb = pColor->m_b;
                    }
                }
                float fr = cr > 0.0f ? cr : 0.0f;
                fr = fr * 255.0f;
                if (fr > 255.0f) fr = 255.0f;
                float fg = cg > 0.0f ? cg : 0.0f;
                fg = fg * 255.0f;
                if (fg > 255.0f) fg = 255.0f;
                float fb = cb > 0.0f ? cb : 0.0f;
                fb = fb * 255.0f;
                if (fb > 255.0f) fb = 255.0f;
                u32 r = (u32)(int)fr;
                u32 g = (u32)(int)fg;
                u32 b = (u32)(int)fb;
                u32 color = (((r | 0xffffff00u) << 8) | g) << 8 | b;

                RangeEntry *pRange = &m_ranges[i];
                int begin = (int)(size_t)pRange->m_begin;
                int end = (int)(size_t)pRange->m_end;
                int count = (end - begin) / 0xc;
                BuildRibbon((const void *)begin,
                            m_rangeSecond[i].m_ptr,
                            count, color);
            }
            i++;
        } while (i < n);
    }

    if (m_buffer != 0) {
        void *pOld = m_buffer;
        m_buffer = 0;
        ((void (__thiscall *)(void *))((RefObj *)pOld)->m_vtbl[2])(pOld);
    }
    Draw *pDraw2 = (Draw *)gDrawHolder->m_draw;
    pDraw2->Flush();
    m_buffer = gDrawHolder->m_draw;
    gDrawHolder->m_draw = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00b807e0
void Mode::BuildRibbon(const void *pVerts, const void *pOther, int count, u32 color)
{
    RibbonVertex *pOut = (RibbonVertex *)pVerts;
    const Vertex *pV = (const Vertex *)pOther;
    float dist = 0.0f;
    float prevX = 0.0f, prevY = 0.0f, prevZ = 0.0f;
    int idx = 1;
    int nSeg = count * 2 - 2;
    if (count <= 1)
        return;
    do {
        int got = 0;
        ((Draw *)gDrawHolder->m_draw)->GetVertexBuffer(nSeg + 4, &pOut, &got);
        nSeg += 4 - got;
        idx--;
        const Vertex *pCur = (const Vertex *)pVerts + idx;
        pOut->x = pCur->x;
        pOut->y = pCur->y;
        pOut->z = pCur->z;
        pOut->color = color;
        pOut->u = kOne;
        pOut->v = dist;
        pOut++;
        prevX = pCur->x;
        prevY = pCur->y;
        prevZ = pCur->z;
        if (got - 1 > 1) {
            int wraps = ((got - 3) >> 1) + 1;
            idx += wraps;
            do {
                const Vertex *pNext = pCur + 1;
                float dx = pNext->x - prevX;
                float dy = pNext->y - prevY;
                float dz = pNext->z - prevZ;
                pOut->x = pNext->x;
                pOut->y = pNext->y;
                pOut->z = pNext->z;
                pOut->color = color;
                pOut->u = kOne;
                dist = (float)(dz * dz + dy * dy + dx * dx);
                dist = sqrtf(dist) + dist;
                pOut->v = dist;
                pOut->x = pNext->x;
                pOut->y = pNext->y;
                pOut->z = pNext->z;
                pOut->color = color;
                pOut->u = 0.0f;
                pOut->v = dist;
                prevX = pCur->x;
                prevY = pCur->y;
                prevZ = pCur->z;
                pOut++;
                pCur = pNext;
                wraps--;
            } while (wraps != 0);
        }
        const Vertex *pTail = (const Vertex *)pOther + idx;
        pOut->x = pTail->x;
        pOut->y = pTail->y;
        pOut->z = pTail->z;
        pOut->color = color;
        pOut->u = 0.0f;
        pOut->v = dist;
        FUN_007a4650();
    } while (idx < count);
}

// ---------------------------------------------------------------------------
// @ 0x00b80ea0
void Layer::DispatchEvent(void *p2, int event, void *pViewer, void *pMaterial)
{
    (void)p2;
    if (m_pMode == 0 || m_pMod0 == 0)
        return;
    if (SP_GetActiveTerrainSphere() == 0)
        return;
    if (SP_GetUniverseContext() != 0)
        return;
    if (m_flag0c != 0) {
        m_flag0c = 0;
        m_pMode->Submit();
    }
    ViewerHandle *pHandle = (ViewerHandle *)pViewer;
    if (!pHandle->m_viewer->Update())
        return;

    EffectsDispatch_t mat;
    mat.m[0][0] = kOne;  mat.m[0][1] = 0.0f; mat.m[0][2] = 0.0f; mat.m[0][3] = 0.0f;
    mat.m[1][0] = 0.0f;  mat.m[1][1] = kOne; mat.m[1][2] = 0.0f; mat.m[1][3] = 0.0f;
    mat.m[2][0] = 0.0f;  mat.m[2][1] = 0.0f; mat.m[2][2] = kOne; mat.m[2][3] = 0.0f;
    mat.m[3][0] = 0.0f;  mat.m[3][1] = 0.0f; mat.m[3][2] = 0.0f; mat.m[3][3] = 0.0f;
    EffectsDispatch(&mat, 4);

    if (event == 9) {
        MaterialManager *mm = SP_MaterialManager();
        MaterialRef *pMat = ((FindMaterialFn)((void **)mm->m_vtbl)[0x28 / 4])(mm, 0x8c4c893e);
        m_pMode->DrawMaterial(pMat, pMaterial);
        pHandle->m_viewer->Finish();
        return;
    }
    if (event == 0x19) {
        m_pMod0->SetMaterialA(pMaterial);
        m_pMod1->SetMaterialB(pMaterial);
        m_pMod2->SetMaterialC(pMaterial);
    }
    pHandle->m_viewer->Finish();
}

// ---------------------------------------------------------------------------
// Terrain stamping state: bit plane and coverage mask.
struct StampState {
    u8    m_pad00[0x4c];
    u32  *m_bits;   // +0x4c
    u8    m_pad50[0x2c];
    u8   *m_mask;   // +0x7c

    void Stamp(const float *pDir, float radius, u32 planeMask);   // 0x00b81020
};

struct SearchCoord {
    int m_a;   // +0x00
    int m_b;   // +0x04
    int m_c;   // +0x08
};

struct StampSpan {
    u32 m_plane;   // +0x00
    int m_minB;    // +0x04
    int m_minC;    // +0x08
    int m_maxB;    // +0x0c
    int m_maxC;    // +0x10
};

extern "C" int FUN_00685450(int maxVal, int *pCoord, int count, StampSpan *pOut); // 0x685450

// ---------------------------------------------------------------------------
// @ 0x00b81020
void StampState::Stamp(const float *pDir, float radius, u32 planeMask)
{
    float vx = pDir[0];
    float vy = pDir[1];
    float vz = pDir[2];
    float len = sqrtf(vx * vx + vy * vy + vz * vz);
    if (len <= kEps)
        return;

    float inv = kOne / len;
    float scaled = inv * k128 * radius;
    int steps = (int)scaled;
    if ((float)steps < scaled)
        steps++;
    if (steps == 0)
        return;

    vx *= inv;
    vy *= inv;
    vz *= inv;
    float reach = (inv * radius) * (inv * radius);

    float ax = vx < 0.0f ? -vx : vx;
    float ay = vy < 0.0f ? -vy : vy;
    float az = vz < 0.0f ? -vz : vz;

    int ca, cb, plane;
    if (az < ax || az < ay) {
        if (ay < ax) {
            ca = (int)((vy / vx + kOne) * k64);
            cb = (int)((vz / ax + kOne) * k64);
            plane = vx < 0.0f ? 3 : 2;
        } else {
            ca = (int)((vz / vy + kOne) * k64);
            cb = (int)((vx / ay + kOne) * k64);
            plane = vy < 0.0f ? 5 : 4;
        }
    } else {
        ca = (int)((vx / vz + kOne) * k64);
        cb = (int)((vy / az + kOne) * k64);
        plane = vz < 0.0f ? 1 : 0;
    }
    if (ca == 0x80) ca = 0x7f;
    if (cb == 0x80) cb = 0x7f;

    SearchCoord coord;
    coord.m_a = ca;
    coord.m_b = cb;
    coord.m_c = plane;

    StampSpan spans[29];
    int nSpans = FUN_00685450(0x80, &coord.m_a, steps, spans);
    if (nSpans <= 0)
        return;

    u8 *pMask = m_mask;
    u32 *pBits = m_bits;
    u32 andMask = planeMask & 0x3c000000u;
    u8 sel0 = (u8)(andMask >> 0x16);
    u8 sel1 = (u8)(andMask >> 0x1a);
    u8 sel[2] = { sel0, sel1 };

    for (int s = 0; s < nSpans; s++) {
        StampSpan *pSpan = &spans[s];
        for (int c = pSpan->m_minC; c < pSpan->m_maxC; c++) {
            for (int b = pSpan->m_minB; b < pSpan->m_maxB; b++) {
                u32 idx = (pSpan->m_plane * 0x80 + (u32)c) * 0x80 + (u32)b;
                u8 *pCell = pMask + (idx >> 1);
                u8 cell = *pCell;
                u8 mask = sel[idx & 1];
                if ((mask & cell) == 0)
                    continue;

                const u8 *order = &gPlaneOrder[(pSpan->m_plane >> 1) * 4];
                float fbx = ((float)b + 0.5f) * 0.015625f - kOne;
                float fcy = ((float)c + 0.5f) * 0.015625f - kOne;
                float invLen = kOne / sqrtf(fcy * fcy + fbx * fbx + kOne);
                float sgn = (pSpan->m_plane & 1) ? -invLen : invLen;

                float normal[3];
                normal[order[0]] = sgn * fbx;
                normal[order[1]] = invLen * fcy;
                normal[order[2]] = sgn;

                float dx = normal[0] - vx;
                float dy = normal[1] - vy;
                float dz = normal[2] - vz;
                if (dx * dx + dy * dy + dz * dz <= reach) {
                    *pCell = (u8)(~mask & cell);
                    pBits[idx] &= ~andMask;
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------
struct cPlanetModel {
    float GetRadiusAt(const Vertex *p);                              // 0x00b7ef70
    float DistanceBetweenPoints(const Vertex *a, const Vertex *b);   // 0x00b81470
};

// lib_cblock acos helper (float argument)

// @ 0x00b81470
float cPlanetModel::DistanceBetweenPoints(const Vertex *a, const Vertex *b)
{
    float r1 = GetRadiusAt(a);
    float r2 = GetRadiusAt(b);

    float ax = a->x, ay = a->y, az = a->z;
    float bx = b->x, by = b->y, bz = b->z;

    float alen = sqrtf(ax * ax + ay * ay + az * az);
    float blen = sqrtf(bx * bx + by * by + bz * bz);
    float aInv = kOne / alen;
    float bInv = kOne / blen;

    float dot = (ax * aInv) * (bx * bInv) +
                (ay * aInv) * (by * bInv) +
                (az * aInv) * (bz * bInv);

    if (dot > kOne)
        dot = kOne;
    if (dot < kNegOne)
        dot = kNegOne;

    float angle = acosf(dot);
    return angle * ((r1 + r2) * kHalf);
}
