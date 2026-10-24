// Slice s00cac360 -- retail cVehicle invalid-area notification, weapon-list refresh and
// goal/curve plumbing.
//
// The retail cVehicle is larger than the development PDB type (0x740), so the object is
// modelled locally with role-named members and explicit padding for untouched gaps.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-

typedef unsigned int   u32;
typedef unsigned char  u8;
typedef int            i32;

struct Vec3 { float x, y, z; };

// Vehicle+0x34: embedded steering/spatial sub-object; only its vtable pointer is used.
struct CSteeringSub {
    void **m_vtbl;                 // +0x00
};

// Object referenced by vehicle+0xd0; only the flags word at +0x04 is read.
struct CPropFlags {
    u32 m_pad0;                    // +0x00
    u32 m_flags;                   // +0x04
};

struct CVehicle {
    void **m_vtbl;                 // +0x000
    u8  m_pad004[0x34 - 0x04];     // +0x004
    CSteeringSub m_steering;       // +0x034
    u8  m_pad038[0xd0 - 0x38];     // +0x038
    CPropFlags *m_propD0;          // +0x0d0
    u8  m_padD4[0x108 - 0xd4];     // +0x0d4
    u8  m_subObject108;            // +0x108  (opaque sub-object, only addressed)
    u8  m_pad109[0x2a4 - 0x109];   // +0x109
    u32 m_flags2a4;                // +0x2a4
    u8  m_pad2a8[0x508 - 0x2a8];   // +0x2a8
    u8  m_weaponList508[0x14];     // +0x508  (object passed to GetFileCount)
    u8  m_pad51c[0xb1c - 0x51c];   // +0x51c
    u32 m_factionB1c;              // +0xb1c
    u32 m_modelB20;                // +0xb20
    u8  m_padB24[0xc3c - 0xb24];   // +0xb24
    Vec3  m_posC3c;                // +0xc3c
    float m_altC48;                // +0xc48
    float m_altC4c;                // +0xc4c
    u8  m_padC50[0xd10 - 0xc50];   // +0xc50
    u8  m_boolD10;                 // +0xd10
    u8  m_padD11[0xd24 - 0xd11];   // +0xd11
    void *m_ptrD24;                // +0xd24
};

// One curve point (0x3c bytes).
struct CCurvePoint {
    Vec3 m_pos;                    // +0x00
    float m_w;                     // +0x0c
    u32   m_u10;                   // +0x10
    u8    m_pad14[0x38 - 0x14];    // +0x14
    u8    m_b38;                   // +0x38
    u8    m_pad39[0x3c - 0x39];    // +0x39
};

// Curve container returned by FUN_00c41ec0 (vehicle+0x34 + 0x1f4).
struct CCurve {
    CCurvePoint *m_begin;          // +0x00
    CCurvePoint *m_end;            // +0x04
    CCurvePoint *m_cap;            // +0x08
    u8  m_pad0c[0x14 - 0x0c];      // +0x0c
    CCurvePoint m_start;           // +0x14
    float m_f50;                   // +0x50
    float m_f54;                   // +0x54
    float m_f58;                   // +0x58
    u32   m_u5c;                   // +0x5c
    float m_f60;                   // +0x60
    float m_f64;                   // +0x64
    float m_f68;                   // +0x68
    float m_f6c;                   // +0x6c
    u32   m_u70;                   // +0x70
};

// 0x3c-byte goal structure copied by FUN_00ac1ff0.
struct CGoal {
    Vec3 m_pos;                    // +0x00
    u8   m_rest[0x3c - 0x0c];      // +0x0c
};

// Vector returned by cGameNounManager::GetGameDataVector.
struct GameDataList {
    u8 m_pad0[4];                  // +0x00
    CVehicle **m_begin;            // +0x04
    CVehicle **m_end;              // +0x08
};

// Model-key -> Vec3 map used by the community-editor helpers.
struct CModelMap {
    u32   m_pad0;                  // +0x00
    u32   m_anchorSelf;            // +0x04
    u32   m_anchorParent;          // +0x08
    void *m_root;                  // +0x0c
    u32   m_u10;                   // +0x10
    u32   m_u14;                   // +0x14
};

struct CTreeNode {
    void      *m_child;            // +0x00
    CTreeNode *m_next;             // +0x04
};

// Generic noun carrying an embedded model map at +0x6c (cCity and friends).
struct CGameObject {
    u8        m_pad0[0x6c];        // +0x00
    CModelMap m_map;               // +0x6c
};

inline bool vec_eq(const Vec3 &a, const Vec3 &b)
{
    const u32 *pa = (const u32 *)&a;
    const u32 *pb = (const u32 *)&b;
    return pa[0] == pb[0] && pa[1] == pb[1] && pa[2] == pb[2];
}

inline float fsqrt_(float x)
{
    float r;
    __asm {
        fld  x
        fsqrt
        fstp r
    }
    return r;
}

// --------------------------------------------------------------- extern decls

extern "C" void  FUN_00caa980();       // 0x00caa980  cVehicle::ReadWeaponsFromPropList (ecx)
extern "C" void  FUN_00c9f380();       // 0x00c9f380  (ecx) -> x87 float
extern "C" void  FUN_00b3d290();       // 0x00b3d290  () -> void*
extern "C" void  FUN_00ac4ef0();       // 0x00ac4ef0  cAStar::release (ecx, one stack arg)
extern "C" void  FUN_00b3d350();       // 0x00b3d350  PlanetModel
extern "C" void  FUN_00b88420();       // 0x00b88420
extern "C" void  FUN_00b3d300();       // 0x00b3d300  NounManager
extern "C" void  FUN_00b21340();       // 0x00b21340  GetGameDataVector (ecx, five stack args)
extern "C" void  FUN_008e7f80();       // 0x008e7f80  GetFileCount (ecx)
extern "C" void  FUN_00c41ec0();       // 0x00c41ec0  (ecx) -> void*
extern "C" void  FUN_00c421f0();       // 0x00c421f0  (ecx) -> Vec3*
extern "C" void  FUN_00ac1ff0();       // 0x00ac1ff0  (ecx = dest, source Vec3*)
extern "C" void  FUN_00c9e960();       // 0x00c9e960  CanOccupyTerrain (ecx, Vec3*)
extern "C" void  FUN_00c9fb40();       // 0x00c9fb40  (ecx, Vec3, float, float)
extern "C" void  FUN_00b45c10();       // 0x00b45c10  (ecx = dest vector, source vector)
extern "C" void  FUN_00ac45e0();       // 0x00ac45e0  vector::DoInsertValue (ecx, pos, value)
extern "C" void  FUN_00ac4570();       // 0x00ac4570  vector::erase (ecx, first, last)
extern "C" void  FUN_00ca0170();       // 0x00ca0170  BringGoalToAltitude (ecx, Vec3*)
extern "C" void  FUN_00f47380();       // 0x00f47380  operator delete[] (cdecl, one arg)
extern "C" void  FUN_00b3d2b0();       // 0x00b3d2b0  () -> void*
extern "C" void  FUN_00ac7ab0();       // 0x00ac7ab0  (ecx, float, void*, u32)
extern "C" void  FUN_00b25f40();       // 0x00b25f40  (ecx, int) -> void*
extern "C" void  FUN_0067dcd0();       // 0x0067dcd0  GetManager
extern "C" void  FUN_00bf2c60();       // 0x00bf2c60
extern "C" void  FUN_00bf9300();       // 0x00bf9300
extern "C" void  FUN_00bf9700();       // 0x00bf9700
extern "C" void  FUN_00ba5df0();       // 0x00ba5df0
extern "C" void  FUN_00bf2c80();       // 0x00bf2c80
extern "C" void  FUN_00bf4a60();       // 0x00bf4a60
extern "C" void  FUN_00bf9770();       // 0x00bf9770
extern "C" void  FUN_00bf4b10();       // 0x00bf4b10
extern "C" void  FUN_009a9600();       // 0x009a9600  DoNukeSubtree (ecx, one stack arg)
extern "C" void  FUN_00b5b800();       // 0x00b5b800  GetCurrentGameMode

extern const u32 DAT_01474a28[];       // 0x01474a28
extern const u32 DAT_014749ec[];       // 0x014749ec
extern u8        DAT_01654c05;         // 0x01654c05
extern u8        DAT_0168caf0[];       // 0x0168caf0

char __fastcall FUN_00cac740(CVehicle *v, float x, float y, float z, float a, float b);  // 0x00cac740

// float square root uses the x87 fsqrt helper above (matches the original codegen).

// ------------------------------------------------------------------ functions

// @ 0x00cac360
void __cdecl FUN_00cac360(float px, float py, float pz, float radius)
{
    CGoal goal;
    GameDataList *list;
    int count;

    ((void (__thiscall *)(void *))FUN_00b88420)(((void *(__cdecl *)())FUN_00b3d350)());
    list = (GameDataList *)((void *(__thiscall *)(void *, u32, u32, u32, u32, u32))FUN_00b21340)(
            ((void *(__cdecl *)())FUN_00b3d300)(),
            0x00cd7d10, 0x00d3d420, 0x00ae72d0, 0x00b1e500, 0x018c6de8);
    count = (int)(list->m_end - list->m_begin);
    for (int i = 0; i < count; i++) {
        CVehicle *v = list->m_begin[i];
        if (((char (__thiscall *)(CVehicle *))v->m_vtbl[0x2c / 4])(v) != 0)
            continue;
        if (((int (__thiscall *)(void *))FUN_008e7f80)(&v->m_weaponList508) == 2)
            continue;

        CSteeringSub *sub = &v->m_steering;
        CCurve *curve = (CCurve *)((CCurve *(__thiscall *)(CSteeringSub *))FUN_00c41ec0)(sub);
        Vec3 *sp = ((Vec3 *(__thiscall *)(CSteeringSub *))sub->m_vtbl[0x2c / 4])(sub);
        Vec3 prev = *sp;
        if (curve->m_u5c == 0)
            continue;

        ((void (__thiscall *)(CGoal *, CGoal *))FUN_00ac1ff0)(&goal,
                (CGoal *)((CGoal *(__thiscall *)(CSteeringSub *))FUN_00c421f0)(sub));
        float gx = goal.m_pos.x - px;
        float gy = goal.m_pos.y - py;
        float gz = goal.m_pos.z - pz;
        if (radius > fsqrt_(gx * gx + gy * gy + gz * gz)) {
            ((void (__thiscall *)(CSteeringSub *))sub->m_vtbl[0xec / 4])(sub);
            v->m_flags2a4 &= 0x10;
            continue;
        }

        bool found = false;
        CCurvePoint *pt = curve->m_begin;
        if (pt != curve->m_end) {
            int n = (int)(curve->m_end - pt);
            for (int j = 0; j < n; j++, pt++) {
                float cx = pt->m_pos.x, cy = pt->m_pos.y, cz = pt->m_pos.z;
                float dx = cx - px, dy = cy - py, dz = cz - pz;
                if (fsqrt_(dx * dx + dy * dy + dz * dz) < radius) {
                    found = true;
                    break;
                }
                float vx = prev.x - cx, vy = prev.y - cy, vz = prev.z - cz;
                float b = vx * dx + vy * dy + vz * dz;
                float c2 = vx * vx + vy * vy + vz * vz;
                float disc = b * b - ((dx * dx + dy * dy + dz * dz) - radius * radius) * c2;
                if (disc >= 0.0f) {
                    float s = fsqrt_(disc);
                    if (s - b >= 0.0f && -b - s <= c2) {
                        found = true;
                        break;
                    }
                }
                prev = pt->m_pos;
            }
        }
        if (found) {
            if (v->m_altC48 == 0.0f) {
                ((void (__thiscall *)(CSteeringSub *, Vec3 *, float))sub->m_vtbl[0xe4 / 4])
                        (sub, &v->m_posC3c, 1.0f);
            } else {
                ((void (__thiscall *)(CSteeringSub *, Vec3 *, float, float))sub->m_vtbl[0xe8 / 4])
                        (sub, &v->m_posC3c, v->m_altC48, v->m_altC4c);
                ((void (__thiscall *)(CVehicle *, float, float, float, float, float))FUN_00c9fb40)
                        (v, v->m_posC3c.x, v->m_posC3c.y, v->m_posC3c.z,
                         v->m_altC48, v->m_altC4c);
            }
        }
    }
}

// @ 0x00cac740
char __fastcall FUN_00cac740(CVehicle *v, float px, float py, float pz, float a, float b)
{
    if (v->m_ptrD24 == 0)
        return 0;

    CVehicle *best = 0;
    float bestDist = 3.402823466e+38f;

    GameDataList *list = (GameDataList *)((void *(__thiscall *)(void *, u32, u32, u32, u32, u32))FUN_00b21340)(
            ((void *(__cdecl *)())FUN_00b3d300)(),
            0x00cd7d10, 0x00d3d420, 0x00ae72d0, 0x00b1e500, 0x018c6de8);
    for (CVehicle **it = list->m_begin; it != list->m_end; it++) {
        CVehicle *o = *it;
        if (o == v || o->m_ptrD24 != v->m_ptrD24 || o->m_factionB1c != v->m_factionB1c)
            continue;
        CCurve *c = (CCurve *)((CCurve *(__thiscall *)(CSteeringSub *))FUN_00c41ec0)(&o->m_steering);
        if (c->m_u5c == 0)
            continue;
        Vec3 *gp = (Vec3 *)((Vec3 *(__thiscall *)(CSteeringSub *))FUN_00c421f0)(&o->m_steering);
        float dx = gp->x - px, dy = gp->y - py, dz = gp->z - pz;
        float d = fsqrt_(dx * dx + dy * dy + dz * dz);
        if (!((a < d && d < b) || (a == 0.0f && d < 128.0f)))
            continue;
        CCurvePoint *pt = c->m_begin;
        if (pt == c->m_end)
            continue;
        Vec3 cp = pt->m_pos;
        if (((char (__thiscall *)(CVehicle *, Vec3 *))FUN_00c9e960)(v, &cp) == 0)
            continue;
        CSteeringSub *sub = &v->m_steering;
        Vec3 *sp = ((Vec3 *(__thiscall *)(CSteeringSub *))sub->m_vtbl[0x2c / 4])(sub);
        float sx = cp.x - sp->x, sy = cp.y - sp->y, sz = cp.z - sp->z;
        float sd = fsqrt_(sx * sx + sy * sy + sz * sz);
        if (sd < bestDist && sd < 64.0f) {
            best = o;
            bestDist = sd;
        }
    }
    if (best == 0)
        return 0;

    CCurve *src = (CCurve *)((CCurve *(__thiscall *)(CSteeringSub *))FUN_00c41ec0)(&best->m_steering);
    CCurve tmp;
    ((void (__thiscall *)(CCurve *, CCurve *))FUN_00b45c10)(&tmp, src);
    ((void (__thiscall *)(CCurvePoint *, CCurvePoint *))FUN_00ac1ff0)(&tmp.m_start, &src->m_start);
    tmp.m_f50 = src->m_f50;
    tmp.m_f54 = src->m_f54;
    tmp.m_f58 = src->m_f58;
    tmp.m_u5c = src->m_u5c;
    tmp.m_f60 = src->m_f60;
    tmp.m_f64 = src->m_f64;
    tmp.m_f68 = src->m_f68;
    tmp.m_f6c = src->m_f6c;
    tmp.m_u70 = src->m_u70;

    if (a == 0.0f) {
        CCurvePoint np;
        np.m_pos.x = px;
        np.m_pos.y = py;
        np.m_pos.z = pz;
        np.m_w = 1.0f;
        np.m_u10 = 0;
        np.m_b38 = 0;
        if (tmp.m_end < tmp.m_cap) {
            if (tmp.m_end != 0)
                ((void (__thiscall *)(CCurvePoint *, CCurvePoint *))FUN_00ac1ff0)(tmp.m_end, &np);
            tmp.m_end++;
        } else {
            ((void (__thiscall *)(CCurve *, CCurvePoint *, CCurvePoint *))FUN_00ac45e0)(
                    &tmp, tmp.m_end, &np);
        }
    }

    CCurvePoint *start = tmp.m_begin;
    CCurvePoint *chosen = start;
    float nearDist = 3.402823466e+38f;
    CSteeringSub *sub = &v->m_steering;
    Vec3 *sp = ((Vec3 *(__thiscall *)(CSteeringSub *))sub->m_vtbl[0x2c / 4])(sub);
    for (CCurvePoint *p = start; p != tmp.m_end; p++) {
        float x = p->m_pos.x, y = p->m_pos.y, z = p->m_pos.z;
        float dx = x - sp->x, dy = y - sp->y, dz = z - sp->z;
        float d = dx * dx + dy * dy + dz * dz;
        if (d < nearDist) {
            Vec3 cp = p->m_pos;
            if (((char (__thiscall *)(CVehicle *, Vec3 *))FUN_00ca0170)(v, &cp) == 0) {
                chosen = p;
                nearDist = d;
            }
        }
    }
    if (chosen != start)
        ((void (__thiscall *)(CCurve *, CCurvePoint *, CCurvePoint *))FUN_00ac4570)(
                &tmp, start, chosen);
    ((void (__thiscall *)(CSteeringSub *, CCurve *))sub->m_vtbl[0xdc / 4])(sub, &tmp);
    if (tmp.m_begin != 0 && ((u32 *)tmp.m_begin)[-1] != 0)
        ((void (__cdecl *)(void *))FUN_00f47380)(tmp.m_begin);
    return 1;
}

// @ 0x00cac710
void __fastcall FUN_00cac710(CVehicle *v)
{
    if (v->m_boolD10 == 0) {
        CPropFlags *p = v->m_propD0;
        if (p != 0) {
            u8 f = (u8)(p->m_flags >> 0x12);
            if ((f & 1) == 0) {
                v->m_boolD10 = 1;
                ((void (__thiscall *)(CVehicle *))FUN_00caa980)(v);
            }
        }
    }
}

// @ 0x00cacbe0
void __fastcall FUN_00cacbe0(CVehicle *v)
{
    if ((v->m_flags2a4 & 4) != 0) {
        if (FUN_00cac740(v, v->m_posC3c.x, v->m_posC3c.y, v->m_posC3c.z,
                          v->m_altC48, v->m_altC4c) != 0) {
            void **vtbl = v->m_steering.m_vtbl;
            void *self = &v->m_steering;
            ((void (__thiscall *)(void *, float, int))vtbl[0xc4 / 4])(self,
                    ((float (__thiscall *)(CVehicle *))FUN_00c9f380)(v), 0);
            ((void (__thiscall *)(void *, void *))FUN_00ac4ef0)(
                    ((void *(__cdecl *)(void))FUN_00b3d290)(),
                    &v->m_subObject108);
        }
    }
}

// @ 0x00cacc60
char __fastcall FUN_00cacc60(CVehicle *v)
{
    CSteeringSub *sub = &v->m_steering;
    Vec3 pos = *((Vec3 *(__thiscall *)(CSteeringSub *))sub->m_vtbl[0x98 / 4])(sub);

    int val = ((int (__thiscall *)(CVehicle *))v->m_vtbl[0x4c / 4])(v);
    ((void (__thiscall *)(void *, int))FUN_00b25f40)(
            ((void *(__cdecl *)())FUN_00b3d300)(), val);

    u32 faction = v->m_factionB1c;
    u32 model = v->m_modelB20;
    u32 key;
    if (((void *(__cdecl *)())FUN_00b5b800)() == (void *)&DAT_01654c05)
        key = DAT_01474a28[faction];
    else
        key = DAT_014749ec[faction + model * 3];

    u32 tab[14] = {
        0x7d433fad, 0x8f963dcb, 0x441cd3e6, 0xf670aa43,
        0x2a5147a9, 0x1a4e0708, 0x9ad7d4aa, 0x1f2a25b6,
        0x449c040f, 0xc0b74287, 0xbc1041e6, 0xc15695da,
        0x2090a11b, 0x98e03c0d
    };

    if (((const u32 *)&pos)[0] == 0)
        return 1;

    void *mgr = ((void *(__cdecl *)())FUN_0067dcd0)();
    void **mgrVtbl = *(void ***)mgr;
    if (((char (__thiscall *)(void *, Vec3 *, int, int, int, int, int))mgrVtbl[3])
            (mgr, &pos, 0, 0, 0, 0, 0) != 0)
        return 1;

    CModelMap map;
    ((void (__thiscall *)(CModelMap *))FUN_00bf2c60)(&map);
    ((void (__thiscall *)(CModelMap *, u32))FUN_00bf9300)(&map, key);
    Vec3 cur = *((Vec3 *(__thiscall *)(CModelMap *, u32))FUN_00bf9700)(&map, key);
    ((void (__cdecl *)(Vec3 *, Vec3 *))FUN_00ba5df0)(&pos, &cur);

    for (u8 *p = DAT_0168caf0; p < DAT_0168caf0 + 0x54; p += 0x1c) {
        for (int j = 0; j < 14; j++) {
            u32 k = tab[j];
            if (((char (__thiscall *)(void *, u32))FUN_00bf2c80)(p, k) != 0) {
                Vec3 *pk = (Vec3 *)((Vec3 *(__thiscall *)(void *, u32))FUN_00bf9700)(p, k);
                if (vec_eq(*pk, pos))
                    ((void (__stdcall *)(u32, Vec3 *))FUN_00bf4a60)(k, &cur);
            }
        }
    }

    GameDataList *list2 = (GameDataList *)((void *(__thiscall *)(void *, u32, u32, u32, u32, u32))FUN_00b21340)(
            ((void *(__cdecl *)())FUN_00b3d300)(),
            0x00b21080, 0x00d3d420, 0x00b236c0, 0x00b1e500, 0x018c816a);
    for (CVehicle **it = list2->m_begin; it != list2->m_end; it++) {
        CGameObject *o = (CGameObject *)*it;
        if (((char (__thiscall *)(CModelMap *, u32))FUN_00bf2c80)(&o->m_map, key) != 0) {
            Vec3 *pk = (Vec3 *)((Vec3 *(__thiscall *)(CGameObject *, u32))FUN_00bf9770)(o, key);
            if (vec_eq(*pk, pos))
                ((void (__thiscall *)(CGameObject *, u32, Vec3 *))FUN_00bf4b10)(o, key, &cur);
        }
    }

    if (((void *(__cdecl *)())FUN_00b5b800)() == (void *)&DAT_01654c05) {
        GameDataList *list3 = (GameDataList *)((void *(__thiscall *)(void *, u32, u32, u32, u32, u32))FUN_00b21340)(
                ((void *(__cdecl *)())FUN_00b3d300)(),
                0x00cd7d10, 0x00d3d420, 0x00ae72d0, 0x00b1e500, 0x018c6de8);
        for (CVehicle **it = list3->m_begin; it != list3->m_end; it++) {
            CVehicle *veh = *it;
            CSteeringSub *s = &veh->m_steering;
            Vec3 *pk = ((Vec3 *(__thiscall *)(CSteeringSub *))s->m_vtbl[0x98 / 4])(s);
            if (vec_eq(*pk, pos))
                ((void (__thiscall *)(CSteeringSub *, Vec3 *))s->m_vtbl[0x94 / 4])(s, &cur);
        }
    }

    CTreeNode *n = (CTreeNode *)map.m_root;
    while (n != 0) {
        ((void (__thiscall *)(CModelMap *, void *))FUN_009a9600)(&map, n->m_child);
        CTreeNode *next = n->m_next;
        ((void (__cdecl *)(void *))FUN_00f47380)(n);
        n = next;
    }
    return 1;
}
