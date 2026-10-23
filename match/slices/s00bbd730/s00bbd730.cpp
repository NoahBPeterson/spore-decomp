// Slice s00bbd730 - terraforming / debug-draw helpers from SporeApp.exe.
// Reconstructed from Ghidra decompilation and annotated disassembly.

typedef unsigned char byte;
#include <math.h>
#pragma intrinsic(sqrt)
#pragma intrinsic(fabs)

// ------------------------------------------------------------------ externs
struct DebugDrawObj;
struct PlanetModelObj;
struct StarManagerObj;
struct TerraObj;

struct PlanetModelObj {
    float get_radius();            // 0xb7e4d0
    void* get_scene();             // unused here
};

struct DebugDrawObj {
    void begin(float* pos, float radius);   // 0xb2d870
    void flush(unsigned flags);             // 0xb2a750
};

extern "C" {
    void* FUN_01021260();   // GetActivePlanet
    void* FUN_010212a0();   // GetActivePlanetRecord
    PlanetModelObj* FUN_00b3d350();   // SP::PlanetModel
    DebugDrawObj* FUN_00b3d3b0();     // debug-draw singleton
    int   TerraDistClass(float x, float y);        // 0xfc2080
    void  FUN_00b2d870(DebugDrawObj* self, float* pos, float radius);
    void  FUN_00b2a750(DebugDrawObj* self, unsigned flags);

    extern unsigned char DAT_014665e0[];
    extern unsigned char DAT_014665e1[];
    extern unsigned char DAT_014665e2[];
    extern int DAT_0168a488;
    extern int DAT_0168a48c;
    extern int DAT_0168a490;
}

struct PlanetSceneObj {
    int  field_38;                 // +0x38
};

struct GridObj {
    char* data;                    // +0x10
};

// allocate / lookup helpers used by the debug-draw code
struct DrawBucketObj {
    int* lookup(int* key);         // 0xc7e1a0
    void first(void* out);         // 0xc7ead0
    void next(void* out);          // 0xc7e160
};

struct SurfaceObj {
    float* DirectionToSurfacePosition(void* out, float* dir);  // 0xb815a0
    void first(void* out);         // 0xc7ead0
    void next(void* out);          // 0xc7e160
};

struct RenderObj {
    int unk();                     // 0x8414c0
};

struct TerraObj {
    RenderObj* fn_8414c0();        // 0x8414c0
};

struct ListItem;
struct CityHolder {
    int  fn_b8de30();              // 0xb8de30
    float* GetCities();            // 0x5c65e0
};

struct AvatarObj {
    int fn_b1fdb0();               // 0xb1fdb0
    int fn_c30c60();               // 0xc30c60
};

struct CombatTuning {
    float* GetModelOffset();       // 0x102a3e0
};

struct StarMgr {
    int  fn_885c90();              // 0x885c90
    void* fn_00ba93b0();           // 0xba93b0
    float field_1bc;
};

extern "C" {
    StarMgr* FUN_00b3d2a0();       // SP_StarManager
    CombatTuning* FUN_01029940();  // SP::GetSpaceCombatTuning
}

// ------------------------------------------------------------------ 0x00bbd730
// Voxelise a polyline against the planet voxel grid.
// @ 0x00bbd730
void __stdcall FUN_00bbd730(int* param_1, char param_2)
{
    if (*param_1 != param_1[1]) {
        bool hit = false;
        float step = ((PlanetModelObj*)FUN_00b3d350())->get_radius() * 0.0078125f;
        PlanetSceneObj* scene = (PlanetSceneObj*)FUN_00b3d3b0();
        char* grid = ((GridObj*)scene->field_38)->data;

        float* p = (float*)*param_1;
        float* end = (float*)param_1[1];
        float* next = p + 3;
        if (next == end)
            return;

        do {
            float x = p[0];
            float y = p[1];
            float z = p[2];
            float dx = next[0] - x;
            float dy = next[1] - y;
            float dz = next[2] - z;
            float len = (float)sqrtf(dz * dz + (dx * dx + dy * dy));

            if (1.5258789e-05f < len) {
                float inv = 1.0f / len;
                float t = 0.0f;
                if (0.0f < len) {
                    do {
                        float ax = (float)fabs(x);
                        float ay = (float)fabs(y);
                        float az = (float)fabs(z);
                        int i10, i11, i12;

                        if ((az < ax) || (az < ay)) {
                            if (ay < ax) {
                                i10 = (int)((y / x + 1.0f) * 64.0f);
                                i11 = (int)((z / ax + 1.0f) * 64.0f);
                                i12 = 2;
                                if (x < 0.0f)
                                    i12 = 3;
                            } else {
                                i10 = (int)((z / y + 1.0f) * 64.0f);
                                i11 = (int)((x / ay + 1.0f) * 64.0f);
                                if (y < 0.0f)
                                    i12 = 5;
                                else
                                    i12 = 4;
                            }
                        } else {
                            i10 = (int)((x / z + 1.0f) * 64.0f);
                            i11 = (int)((y / az + 1.0f) * 64.0f);
                            if (z < 0.0f)
                                i12 = 1;
                            else
                                i12 = 0;
                        }
                        if (i10 == 0x80)
                            i10 = 0x7f;
                        if (i11 == 0x80)
                            i11 = 0x7f;

                        char* cell = grid + ((i12 * 0x80 + i11) * 0x80 + i10);
                        if (*cell == 0)
                            hit = true;

                        x = inv * dx * step + x;
                        y = inv * dy * step + y;
                        z = inv * dz * step + z;
                        t = t + step;
                        *cell = (char)0xff;
                    } while (t < len);
                }

                {
                    float ex = next[0];
                    float ey = next[1];
                    float ez = next[2];
                    float ax = (float)fabs(ex);
                    float ay = (float)fabs(ey);
                    float az = (float)fabs(ez);
                    int i10, i11, i12;

                    if ((az < ax) || (az < ay)) {
                        if (ay < ax) {
                            i10 = (int)((ey / ex + 1.0f) * 64.0f);
                            i11 = (int)((ez / ax + 1.0f) * 64.0f);
                            i12 = 2;
                            if (ex < 0.0f)
                                i12 = 3;
                        } else {
                            i10 = (int)((ez / ey + 1.0f) * 64.0f);
                            i11 = (int)((ex / ay + 1.0f) * 64.0f);
                            if (ey < 0.0f)
                                i12 = 5;
                            else
                                i12 = 4;
                        }
                    } else {
                        i10 = (int)((ex / ez + 1.0f) * 64.0f);
                        i11 = (int)((ey / az + 1.0f) * 64.0f);
                        if (ez < 0.0f)
                            i12 = 1;
                        else
                            i12 = 0;
                    }
                    if (i10 == 0x80)
                        i10 = 0x7f;
                    if (i11 == 0x80)
                        i11 = 0x7f;

                    char* cell = grid + ((i12 * 0x80 + i11) * 0x80 + i10);
                    if (*cell == 0)
                        hit = true;
                    *cell = (char)0xff;
                }
            }

            p = next;
            next += 3;
        } while (next != end);

        if (hit && param_2 != 0) {
            ((DebugDrawObj*)FUN_00b3d3b0())->flush(0xf);
        }
    }
}

// ------------------------------------------------------------------ 0x00bbdbf0
// @ 0x00bbdbf0
void __stdcall FUN_00bbdbf0(float* param_1, float param_2)
{
    float radius2 = param_2 * param_2;

    ((DebugDrawObj*)FUN_00b3d3b0())->begin(param_1, radius2);

    void* planet = FUN_01021260();
    if (planet == 0)
        return;
    RenderObj* render = (RenderObj*)((TerraObj*)planet)->fn_8414c0();
    if (render == 0)
        return;

    float cx = param_1[0];
    float cy = param_1[1];
    float cz = param_1[2];
    int key[4];
    byte flags[4];
    flags[0] = 0;
    flags[1] = 0;
    flags[2] = 0;

    float ax = (float)fabs(cx);
    float ay = (float)fabs(cy);
    float az = (float)fabs(cz);

    if ((az < ax) || (az < ay)) {
        if (ay < ax) {
            key[0] = (int)((cy / cx + 1.0f) * 2.0f);
            key[1] = (int)((cz / ax + 1.0f) * 2.0f);
            key[2] = 2;
            if (cx < 0.0f)
                key[2] = 3;
        } else {
            key[0] = (int)((cz / cy + 1.0f) * 2.0f);
            key[1] = (int)((cx / ay + 1.0f) * 2.0f);
            if (cy < 0.0f)
                key[2] = 5;
            else
                key[2] = 4;
        }
    } else {
        key[0] = (int)((cx / cz + 1.0f) * 2.0f);
        key[1] = (int)((cy / az + 1.0f) * 2.0f);
        if (cz < 0.0f)
            key[2] = 1;
        else
            key[2] = 0;
    }
    if (key[0] == 4)
        key[0] = 3;
    if (key[1] == 4)
        key[1] = 3;

    DrawBucketObj* bucket = (DrawBucketObj*)((char*)render + 0x50);
    int* qi = bucket->lookup(key);

    int n = 0;
    do {
        int* qn = qi + 4;
        if (*qn != 0) {
            *qn = 0;
            qi[1] = 0;
            qi[2] = 0;
            qi[3] = 0;
            flags[n] = 1;
        }
        n++;
        qi = qn;
    } while (n < 3);

    SurfaceObj* surface = (SurfaceObj*)FUN_00b3d350();
    int st[4];
    surface->first(st);

    while (st[3] != 0) {
        int idx = (st[2] >> 1) * 4;
        float gx = ((float)st[0] + 0.5f) * 0.5f - 1.0f;
        float gy = ((float)st[1] + 0.5f) * 0.5f - 1.0f;
        float inv = 1.0f / (float)sqrtf((gy * gy + gx * gx) + 1.0f);
        float s = inv;
        if ((st[2] & 1) != 0)
            s = -inv;

        unsigned char b0 = DAT_014665e0[idx];
        unsigned char b1 = DAT_014665e1[idx];
        unsigned char b2 = DAT_014665e2[idx];
        float dir[4];
        dir[b0] = s * gx;
        dir[b1] = inv * gy;
        dir[b2] = s;

        float out[4];
        float* sp = surface->DirectionToSurfacePosition(out, dir);
        dir[0] = sp[0];
        dir[1] = sp[1];
        dir[2] = sp[2];

        float dx = dir[0] - param_1[0];
        float dy = dir[1] - param_1[1];
        float dz = dir[2] - param_1[2];
        if ((dx * dx + dy * dy + dz * dz) < radius2) {
            int off = 0;
            int i = 0;
            do {
                if (*(int*)(off + 0x10 + st[3]) != 0) {
                    *(int*)(off + 0x10 + st[3]) = 0;
                    flags[i] = 1;
                }
                off += 0x10;
                i++;
            } while (off < 0x30);
        }
        surface->next(st);
    }

    unsigned out = (flags[0] != 0) ? 1u : 0u;
    if (flags[1] != 0)
        out |= 2;
    if (flags[2] != 0)
        out |= 4;
    ((DebugDrawObj*)FUN_00b3d3b0())->flush(out);
}

// ------------------------------------------------------------------ 0x00bbdff0
// @ 0x00bbdff0
void __stdcall FUN_00bbdff0(float* param_1, float param_2)
{
    RenderObj* render = (RenderObj*)((TerraObj*)FUN_01021260())->fn_8414c0();
    if (render == 0)
        return;

    float cx = param_1[0];
    float cy = param_1[1];
    float cz = param_1[2];
    int key[4];
    float ax = (float)fabs(cx);
    float ay = (float)fabs(cy);
    float az = (float)fabs(cz);

    if ((az < ax) || (az < ay)) {
        if (ay < ax) {
            key[0] = (int)((cy / cx + 1.0f) * 2.0f);
            key[1] = (int)((cz / ax + 1.0f) * 2.0f);
            key[2] = 2;
            if (cx < 0.0f)
                key[2] = 3;
        } else {
            key[0] = (int)((cz / cy + 1.0f) * 2.0f);
            key[1] = (int)((cx / ay + 1.0f) * 2.0f);
            if (cy < 0.0f)
                key[2] = 5;
            else
                key[2] = 4;
        }
    } else {
        key[0] = (int)((cx / cz + 1.0f) * 2.0f);
        key[1] = (int)((cy / az + 1.0f) * 2.0f);
        if (cz < 0.0f)
            key[2] = 1;
        else
            key[2] = 0;
    }
    if (key[0] == 4)
        key[0] = 3;
    if (key[1] == 4)
        key[1] = 3;

    DrawBucketObj* bucket = (DrawBucketObj*)((char*)render + 0x50);
    int* qi = bucket->lookup(key);
    if (*(int*)((char*)qi + 0x40) != 0)
        *(int*)((char*)qi + 0x40) = 0;
    if (*(int*)((char*)qi + 0x50) != 0)
        *(int*)((char*)qi + 0x50) = 0;

    SurfaceObj* surface = (SurfaceObj*)FUN_00b3d350();
    int st[4];
    surface->first(st);

    float radius2 = param_2 * param_2;

    while (st[3] != 0) {
        int idx = (st[2] >> 1) * 4;
        float gx = ((float)st[0] + 0.5f) * 0.5f - 1.0f;
        float gy = ((float)st[1] + 0.5f) * 0.5f - 1.0f;
        float inv = 1.0f / (float)sqrtf((gy * gy + gx * gx) + 1.0f);
        float s = inv;
        if ((st[2] & 1) != 0)
            s = -inv;

        unsigned char b0 = DAT_014665e0[idx];
        unsigned char b1 = DAT_014665e1[idx];
        unsigned char b2 = DAT_014665e2[idx];
        float dir[4];
        dir[b0] = s * gx;
        dir[b1] = inv * gy;
        dir[b2] = s;

        float out[4];
        float* sp = surface->DirectionToSurfacePosition(out, dir);
        dir[0] = sp[0];
        dir[1] = sp[1];
        dir[2] = sp[2];

        float dx = param_1[0] - dir[0];
        float dy = param_1[1] - dir[1];
        float dz = param_1[2] - dir[2];
        if ((dx * dx + dy * dy + dz * dz) < radius2) {
            int off = 0x40;
            do {
                if (*(int*)(off + st[3]) != 0)
                    *(int*)(off + st[3]) = 0;
                off += 0x10;
            } while (off < 0x60);
        }
        surface->next(st);
    }
}

// ------------------------------------------------------------------ 0x00bbe370
// TerraformingManager::something
// @ 0x00bbe370
class TerraformingManager;

struct TerraRec {
    int  id;
};

struct TerraKeyArray {
    int v[3];
};

class TerraformingManager {
public:
    bool check_requirements(int param);
    int  unlocked_count(int param);
    bool has_unlocks(int param);
    int* query(int* out, int dist, unsigned code, int param);   // 0xbbc870
    int  fn_bbce40(int param);                                  // 0xbbce40
};

// @ 0x00bbe370
bool TerraformingManager::check_requirements(int param)
{
    if (param == 0)
        param = (int)FUN_010212a0();
    int rec = param;
    if (rec == 0)
        rec = (int)FUN_010212a0();

    int dist = TerraDistClass(*(float*)(rec + 0xb0), *(float*)(rec + 0xb4));

    int key[3];
    int* a = query(key, dist, 0x6d60a1cc, param);
    if (a[0] == DAT_0168a488 && a[1] == DAT_0168a48c && a[2] == DAT_0168a490) {
        a = query(key, dist, 0x29c388a, param);
        if (a[0] == DAT_0168a488 && a[1] == DAT_0168a48c && a[2] == DAT_0168a490) {
            a = query(key, dist, 0x3a8be428, param);
            if (a[0] == DAT_0168a488 && a[1] == DAT_0168a48c && a[2] == DAT_0168a490)
                return false;
        }
    }
    return true;
}

// ------------------------------------------------------------------ 0x00bbe470
// @ 0x00bbe470
int TerraformingManager::unlocked_count(int param)
{
    unsigned count;
    float len, scale;
    float* m;
    int sortval, other, av;

    if (param == 0)
        param = *(int*)((char*)FUN_01021260() + 0x13c);

    sortval = ((CityHolder*)param)->fn_b8de30();
    StarMgr* star = FUN_00b3d2a0();
    other = star->fn_885c90();
    av = ((AvatarObj*)sortval)->fn_b1fdb0();

    if (av == other) {
        StarMgr* star2 = FUN_00b3d2a0();
        if (sortval == ((AvatarObj*)star2->fn_00ba93b0())->fn_c30c60())
            return 3;

        float* cities = ((CityHolder*)((CityHolder*)param)->fn_b8de30())->GetCities();
        len = (float)sqrt(cities[0] * cities[0] + cities[1] * cities[1] +
                          cities[2] * cities[2]);
        StarMgr* star3 = FUN_00b3d2a0();
        scale = star3->field_1bc;
        m = FUN_01029940()->GetModelOffset();
        count = (len < m[0] * scale) ? 1u : 0u;
        if (len < m[1] * scale)
            count++;
        if (len < m[2] * scale)
            count++;
    } else {
        if ((*(unsigned*)(param + 0x2c) & 0x800) != 0)
            return 0;
        count = (unsigned)fn_bbce40(param);
    }

    return (int)count > 1 ? (int)count : 1;
}

// ------------------------------------------------------------------ 0x00bbe5c0
// @ 0x00bbe5c0
bool TerraformingManager::has_unlocks(int param)
{
    if (param == 0)
        param = *(int*)((char*)FUN_01021260() + 0x13c);
    return fn_bbce40(param) > 0;
}
