// slice s00e52060 — FUN_00e52060: cell-stage creature part summary.
// Walks the part table (stride 0x48), tallies parts per type, finds the bounding
// center and the farthest extent, picks up to three "special" part indices and
// derives several tuned float values (via curve lookups by key).
#include "types.h"
#include <math.h>

extern "C" void* __cdecl FUN_00e11e073e(void*, int, unsigned);   // memset thunk @0x11e073e
extern "C" float __cdecl FUN_00e837c0(unsigned key, float v);    // tuned-curve lookup
extern "C" void* __cdecl FUN_00e4ce40(void* guard);              // guard -> config block

struct cGuard16 { void* p; cGuard16(); ~cGuard16(); };           // ctor @0x743b50, dtor @0xe82130

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};

struct cPart {
    uint8_t active;       // 0x00
    uint8_t pad0[3];
    int     type;         // 0x04
    Vec3    pos;          // 0x08
    uint32_t pad1[9];     // 0x14
    float   radius;       // 0x38
    uint32_t pad2[3];     // 0x3c
};

struct cCellStats {
    uint32_t pad0[0x481];       // 0x0000 .. 0x1204
    int     counts[13];         // 0x1204: parts per type (active counts double)
    Vec3    center;             // 0x1238
    float   maxDist;            // 0x1244
    uint8_t flag1248;           // 0x1248
    uint8_t pad1249[3];
    float   val124c;            // 0x124c
    uint8_t flag1250;           // 0x1250
    uint8_t flag1251;           // 0x1251
    uint8_t pad1252[2];
    int     mask1254;           // 0x1254
    float   val1258;            // 0x1258
    float   val125c;            // 0x125c
    float   val1260;            // 0x1260
    float   val1264;            // 0x1264
    float   val1268;            // 0x1268
    int     val126c;            // 0x126c
    float   val1270;            // 0x1270
    int     numPicks;           // 0x1274
    int     picks[3];           // 0x1278
    int     val1284;            // 0x1284
    int     val1288;            // 0x1288
    int     nearestIdx;         // 0x128c
};

extern Vec3 g_16b3c28;
extern unsigned g_16b3c84;
extern const float g_1485378;

__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }
static inline const int& MinI(const int& a, const int& b) { return (b < a) ? b : a; }
static inline const float& MaxF(const float& a, const float& b) { return (a < b) ? b : a; }

#pragma auto_inline(off)
// @ 0x00e52060  (this in ESI, part count in EAX; stack: parts, skipCurves)
static void FUN_00e52060(cCellStats* self, int count, const cPart* parts, bool skipCurves)
{
    FUN_00e11e073e(self->counts, 0, 0x34);
    self->center = g_16b3c28;
    self->maxDist = 0.0f;

    float minY = self->center.y;
    float maxY = self->center.y;
    Vec3 minPt = self->center;
    Vec3 maxPt = self->center;
    float nearestY = 10000.0f;
    int idxA = -1, idxB = -1, idxC = -1, idxD = -1;
    self->nearestIdx = -1;
    int i = 0;
    for (i = 0; i < count; ++i) {
        const cPart& p = parts[i];
        if (p.active == 1) {
            float r = p.radius;
            if (p.pos.y + r > maxY) {
                maxPt = p.pos;
                maxY = r + maxPt.y;
            } else if (p.pos.y - r < minY) {
                minPt = p.pos;
                minY = minPt.y - r;
            }
        }
        if (p.type == 12 && p.pos.y < nearestY) {
            nearestY = p.pos.y;
            self->nearestIdx = i;
        }
    }
    self->center.x = (minPt.x + maxPt.x) * 0.5f;
    self->center.y = (minY + maxY) * 0.5f;
    self->center.z = (minPt.z + maxPt.z) * 0.5f;

    int negType = 0;
    for (i = 0; i < count; ++i) {
        const cPart& p = parts[i];
        int* counter = &self->counts[p.type];
        if (p.active == 1) {
            *counter += 2;
            if (p.pos.y < 0.0f) negType = p.type;
            if (p.type == 5) {
                if (p.pos.y > 0.0f) idxB = i;
                else idxD = i;
            }
        } else {
            *counter += 1;
            if (!(p.pos.y > 1000.0f) && p.type == 5) {
                if (p.pos.x > 0.0f) idxA = i;
                else idxC = i;
            }
        }
        float dx = self->center.x - p.pos.x;
        float dy = self->center.y - p.pos.y;
        float dz = self->center.z - p.pos.z;
        float d = sqrtf(dy * dy + (dz * dz + dx * dx)) + p.radius;
        self->maxDist = MaxF(self->maxDist, d);
    }

    self->numPicks = 0;
    if (idxB != -1) self->picks[self->numPicks++] = idxB;
    if (idxA != -1) self->picks[self->numPicks++] = idxA;
    if (idxC != -1) self->picks[self->numPicks++] = idxC;
    if (self->numPicks == 0 && idxD != -1) self->picks[self->numPicks++] = idxD;

    int s = self->counts[10] / 2 * 2 + self->counts[9] / 2 / 2 + self->counts[8] / 2;
    self->val1284 = MinI(s, 10);
    int t = 0;
    if ((negType == 2 || negType == 4 || negType == 7) && self->val1284 != 0) {
        int u = self->counts[6] / 2 * 2 + self->counts[7] / 2 + self->counts[5] / 2 + 1;
        t = MinI(u, 10);
    }
    self->val1288 = t;

    if (skipCurves) return;

    self->flag1250 = (self->counts[2] > 0 || self->counts[4] > 0);
    self->flag1251 = (self->counts[3] > 0 || self->counts[4] > 0);
    self->flag1248 = self->counts[7] > 0;
    self->val124c = FUN_00e837c0(0x77540c34, (float)self->counts[11]);

    cGuard16 g1;
    const char* cfg = (const char*)FUN_00e4ce40(&g1);
    if (self->counts[10] != 0) {
        self->val1258 = FUN_00e837c0(0x2c574746,
            (float)self->counts[9] * *(const float*)(cfg + 0x78) +
            (float)self->counts[8] * *(const float*)(cfg + 0x74) + (float)self->counts[10]);
    } else if (self->counts[9] != 0) {
        self->val1258 = FUN_00e837c0(0xbbab1bf5,
            (float)self->counts[8] * *(const float*)(cfg + 0x80) + (float)self->counts[9]);
    } else if (self->counts[8] != 0) {
        self->val1258 = FUN_00e837c0(0x2ef68471,
            *(const float*)(cfg + 0x7c) * g_1485378 + (float)self->counts[8]);
    } else {
        self->val1258 = 0.0f;
    }
    self->mask1254 = (self->counts[10] > 0 ? 4 : 0) | (self->counts[8] > 0 ? 2 : 0) |
                     (self->counts[9] > 0 ? 1 : 0);
    if (self->mask1254 == 0) {
        self->mask1254 = 1;
        cGuard16 g2;
        const char* cfg2 = (const char*)FUN_00e4ce40(&g2);
        self->val1258 = *(const float*)(cfg2 + 0x90);
    }
    self->val1260 = FUN_00e837c0(0xe5015d0c, (float)self->counts[6]);
    self->val125c = FUN_00e837c0(g_16b3c84, (float)self->counts[6]);
    self->val1264 = 0.0f;
    self->val1268 = FUN_00e837c0(0x03ab589e, (float)self->counts[6]);
    float v = FUN_00e837c0(0xaee2835e, (float)self->counts[6]);
    self->val126c = RoundToInt(v);
    self->val1270 = FUN_00e837c0(0x92baae19, (float)self->counts[5]);
}
#pragma auto_inline(on)

// ---- stand-in for the original caller (0x00e67a46 is its call site): it fixes the
// cl register convention of the static function above (count in EAX, this in ESI).
struct cCellMap { cCellStats* Get(const void* key);   // 0x00e67940 (map lookup)
};
extern "C" void __cdecl FUN_00e83e30(cCellStats* cell, cPart* parts, void* arg);   // 0x00e83e30

cCellStats* CallFUN_00e52060(cCellMap* map, const void* key, void* arg)
{
    cCellStats* cell = map->Get(key);
    cPart* parts = (cPart*)((char*)cell + 4);
    FUN_00e83e30(cell, parts, arg);
    FUN_00e52060(cell, *(int*)cell, parts, false);
    return cell;
}
