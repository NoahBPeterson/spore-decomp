// Slice s00eba650 -- Spore creature/vehicle steering, camera-ray and ray/sphere helpers.
//
// Module style: /O2 /MD /Gy /TP /arch:SSE /fp:fast (single-precision SSE arithmetic,
// x87 only for the inlined sqrt).
//
// Three functions in this slice receive one of their pointers in a register
// (00ebacb0 and 00ebb0b0 take the object in ESI; 00ebb2e0 forwards its steering
// target in EDI/ESI to 0x00eba290) under the whole-program-optimisation register
// convention.  Their bodies are reconstructed faithfully below with that pointer
// modelled as an ordinary argument, so they are behaviourally equivalent but not
// byte-identical.

#include <math.h>

typedef unsigned int  u32;
typedef unsigned char u8;

struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };

// ---------------------------------------------------------------- masked externs
struct Query {                                    // result of 0x00b3d350
    void resolve();                               // 0x00b82060
};

struct Viewer {
    void setup(void* a, void* b);                                     // 0x007c4900
    void camera_location_info(void* a, void* b, void* c, void* d);    // 0x007c3d30
};

struct AppObj { void** vtbl; };

typedef Viewer* (__thiscall* GetViewerFn)(AppObj*);

Query* __stdcall ray_query(float* out, const float* pos, const float* dir); // 0x00b3d350

bool __cdecl mask_probe_a(const void* a, const void* b, void* out);         // 0x00eba340
bool __cdecl mask_probe_b(const void* a, const void* b);                    // 0x00eba0e0
bool __cdecl mask_probe_c(const void* a, unsigned flags);                   // 0x00eba540

void* __cdecl app_instance();                                               // 0x0067dd10

void __cdecl quat_from_directions(Vec4* q, const Vec3* from, const Vec3* to); // 0x00698180

// Steering target helper (0x00eba290).  The original writes both its direction
// argument and the target in registers (ESI/EDI); modelled here as plain out/in
// parameters.
bool __cdecl steering_target(Vec3* target, const Vec3* delta, int flag9, int flag10);

extern const Vec3 g_steering_origin;                                        // 0x016c733c

static __forceinline Viewer* get_viewer(AppObj* app)
{
    return ((GetViewerFn)((void**)app->vtbl)[0x16])(app);
}

// ------------------------------------------------------------------ 0x00eba650
// Advance test: normalise (b - a), run a scene query, then check that the queried
// direction is both non-degenerate and closer than the original segment.
//
// The two Vec3 locals mirror the original's stack layout: the raw difference lives
// in `dir` and is copied into `d`, which is the array handed to the query and the
// source of `len`; `dir` then receives the normalised direction handed to the query
// as its direction argument.
// @ 0x00eba650
bool __cdecl advance_test(const Vec3* a, const Vec3* b)
{
    Vec3 d;
    Vec3 dir;
    dir.x = b->x - a->x;
    dir.y = b->y - a->y;
    dir.z = b->z - a->z;
    d.x = dir.x;
    d.y = dir.y;
    d.z = dir.z;

    float len = sqrtf(d.x * d.x + (d.y * d.y + d.z * d.z));
    if (len < 1.5258789e-05f)
        return false;

    float inv = 1.0f / len;
    dir.x = d.x * inv;
    dir.y = d.y * inv;
    dir.z = d.z * inv;

    ray_query(&d.x, &a->x, &dir.x)->resolve();

    if (d.x * d.x + (d.y * d.y + d.z * d.z) < 1.5258789e-05f)
        return false;

    float e0 = d.x - a->x;
    float e1 = d.y - a->y;
    float e2 = d.z - a->z;
    if (sqrtf(e0 * e0 + (e1 * e1 + e2 * e2)) < len)
        return true;
    return false;
}

// ------------------------------------------------------------------ 0x00eba790
// Mask dispatch over the three available advance tests.
// @ 0x00eba790
bool __cdecl mask_dispatch(const Vec3* a, const Vec3* b, unsigned mask)
{
    if ((mask & 0x400) != 0 && mask_probe_a(a, b, 0))
        return true;
    if ((mask & 0x100) != 0 && advance_test(a, b))
        return true;
    if ((mask & 0x200) != 0 && mask_probe_b(a, b))
        return true;
    return false;
}

// ------------------------------------------------------------------ 0x00eba7f0
// Mode-selected advance test with a caller-supplied fallback flag.
// @ 0x00eba7f0
bool __cdecl advance_dispatch(int mode, const Vec3* a, const Vec3* b, unsigned mask, bool flag)
{
    switch (mode) {
    case 2:
    case 3:
        return true;
    case 0:
    case 1:
        if (mask_probe_c(a, mask))
            return false;
        return mask_dispatch(b, a, mask) ? false : flag;
    }
    return flag;
}

// ------------------------------------------------------------------ 0x00eba860
// Radial advance: step outwards from src along its own direction until the scene query
// stops reporting a new position.
// @ 0x00eba860
float* __cdecl advance_radial(float* p, void* unused, const Vec3* src, float step)
{
    p[0] = src->x;
    p[1] = src->y;
    p[2] = src->z;

    float inv = 1.0f / sqrtf(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);

    Vec3 prop;
    prop.x = p[0] + p[0] * inv * step;
    prop.y = p[1] + p[1] * inv * step;
    prop.z = p[2] + p[2] * inv * step;

    Vec3 next;
    while (mask_probe_a(&prop.x, p, &next.x) &&
           (next.x != p[0] || next.y != p[1] || next.z != p[2])) {
        p[0] = next.x;
        p[1] = next.y;
        p[2] = next.z;

        inv = 1.0f / sqrtf(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
        prop.x = p[0] + p[0] * inv * step;
        prop.y = p[1] + p[1] * inv * step;
        prop.z = p[2] + p[2] * inv * step;
    }
    return p;
}

// ------------------------------------------------------------------ 0x00ebaa20
// Ray/sphere intersection; writes the nearest positive parameter and reports a hit.
// @ 0x00ebaa20
bool __cdecl ray_sphere(const Vec3* a, const Vec3* b, const Vec3* c, float radius, float* out)
{
    float dx = a->x - c->x;
    float dy = a->y - c->y;
    float dz = a->z - c->z;

    float dot = b->x * dx + b->y * dy + b->z * dz;
    float b2  = b->x * b->x + b->y * b->y + b->z * b->z;
    float disc = dot * dot - ((dx * dx + dy * dy) + dz * dz - radius * radius) * b2;
    if (disc < 0.0f)
        return false;

    float s  = sqrtf(disc);
    float t1 = -dot - s;
    float t2 = s - dot;
    if (t2 < 0.0f)
        return false;

    if (out != 0) {
        if (t1 > 0.0f)
            *out = t1 / b2;
        else
            *out = t2 / b2;
    }
    return true;
}

// ------------------------------------------------------------------ 0x00ebab30
// Project a camera ray onto the view plane and return the offset from the ray to the
// projected point.  Writes through its first argument (the ray) and returns it.
// @ 0x00ebab30
Vec3* __cdecl camera_project(Vec3* out, const Vec3* ray)
{
    Vec3 A, B, cam;
    get_viewer((AppObj*)app_instance())->setup(&A, &B);
    get_viewer((AppObj*)app_instance())->camera_location_info(0, &cam, 0, 0);

    float nx = -cam.x;
    float ny = -cam.y;
    float nz = -cam.z;

    float num = ray->z * nz + ray->x * nx + ray->y * ny;
    float den = B.z * nz + B.y * ny + B.x * nx;

    float t = ray->x;
    if (den != 0.0f)
        t = -((A.z * nz + A.y * ny) + A.x * nx - num) / den;

    out->x = (A.x + B.x * t) - ray->x;
    out->y = (A.y + B.y * t) - ray->y;
    out->z = (A.z + B.z * t) - ray->z;
    return out;
}

// ------------------------------------------------------------------ object layout
struct Tracked {
    u32  mode;        // +0x00  selector bits (9, 10) for the steering helper
    Vec3 dir;         // +0x04
    Vec4 quat;        // +0x10
    Vec3 offset;      // +0x20  camera-relative position
    float radius;     // +0x2c
    float speed;      // +0x30
    Vec3 dir2;        // +0x34
    bool flag;        // +0x40
    u8   pad41[3];
    Vec3 dir3;        // +0x44
};

// ------------------------------------------------------------------ 0x00ebacb0
// Advance along the current direction until the next surface and orient towards it.
// The original receives its object in ESI (LTCG register convention).
// @ 0x00ebacb0
void __cdecl advance_to_surface(Tracked* self)
{
    Vec3 A, B, cam;
    get_viewer((AppObj*)app_instance())->setup(&A, &B);
    get_viewer((AppObj*)app_instance())->camera_location_info(0, &cam, 0, 0);

    float dx = self->dir.x;
    float dy = self->dir.y;
    float dz = self->dir.z;

    float inv = 1.0f / sqrtf((dx * dx + dy * dy) + dz * dz);
    float nx = dx * inv;
    float ny = dy * inv;
    float nz = dz * inv;

    float t = (nx * -cam.x + nz * -cam.z) + ny * -cam.y;
    float px = -cam.x - nx * t;
    float py = -cam.y - ny * t;
    float pz = -cam.z - nz * t;

    float l2 = (pz * pz + py * py) + px * px;
    if (l2 < 1.5258789e-05f)
        return;

    float s = 1.0f / sqrtf(l2);
    py = py * s;
    pz = pz * s;
    px = s * px;

    float ux = A.x - self->offset.x;
    float uy = A.y - self->offset.y;
    float uz = A.z - self->offset.z;

    float den = (B.x * px * s + B.z * pz * s) + B.y * py * s;
    if (den == 0.0f)
        return;

    float num = ((ux * px * s + uz * pz * s) + uy * py * s)
              - ((dz * pz * s + dy * py * s) + dx * px * s);
    float u = -(num / den);
    if (u < 0.0f)
        return;

    float d2x = self->dir2.x;
    float d2y = self->dir2.y;
    float d2z = self->dir2.z;

    float scale = ((((ux + B.x * u) - d2x) * nx
                  + ((uz + B.z * u) - d2z) * nz)
                  + ((uy + B.y * u) - d2y) * ny)
                + self->speed;

    float inv2 = 1.0f / sqrtf((d2x * d2x + d2z * d2z) + d2y * d2y);
    self->dir.x = (inv2 * d2x) * scale;
    self->dir.y = (d2y * inv2) * scale;
    self->dir.z = (d2z * inv2) * scale;

    Vec3 tmp;
    self->offset = *camera_project(&tmp, &self->dir);
}

// ------------------------------------------------------------------ 0x00ebafe0
// Initialise a tracked object from its direction, orientation, radius and mode flags.
// @ 0x00ebafe0
void __cdecl init_tracked(Tracked* t, int mode, const Vec3* dir, const Vec4* quat,
                          float radius, u32 flags)
{
    t->dir  = *dir;
    t->quat = *quat;

    // The original keeps a register pointer to dir and drives the inline sqrt and
    // the dir2/dir3 copies through it.
    Vec3* d = &t->dir;
    t->dir2 = *d;
    t->mode = flags;
    t->speed = sqrtf(d->x * d->x + d->y * d->y + d->z * d->z);

    Vec3 tmp;
    t->offset = *camera_project(&tmp, d);

    t->flag = advance_dispatch(mode, d, d, t->mode, t->flag);
    t->dir3 = *d;
    t->radius = radius;
}

// ------------------------------------------------------------------ 0x00ebb0b0
// Track the point where the camera ray meets the sphere around the origin.
// The original receives its object in ESI (LTCG register convention).
// @ 0x00ebb0b0
void __cdecl track_camera_ray(Tracked* self)
{
    Vec3 camPos, camDir;
    get_viewer((AppObj*)app_instance())->setup(&camPos, &camDir);

    Vec3 delta;
    delta.x = camPos.x - self->offset.x;
    delta.y = camPos.y - self->offset.y;
    delta.z = camPos.z - self->offset.z;

    float t;
    if (!ray_sphere(&delta, &camDir, &g_steering_origin, self->speed, &t))
        return;

    Vec3 target;
    target.x = delta.x + camDir.x * t;
    target.y = delta.y + camDir.y * t;
    target.z = delta.z + camDir.z * t;

    Vec4 q;
    quat_from_directions(&q, &self->dir, &target);

    float ax = self->quat.x, ay = self->quat.y, az = self->quat.z, aw = self->quat.w;
    float qx = q.x, qy = q.y, qz = q.z, qw = q.w;
    self->quat.x = (qw * ax + aw * qx) + (qy * az - qz * ay);
    self->quat.y = (qw * ay + aw * qy) + (qz * ax - qx * az);
    self->quat.z = (qw * az + aw * qz) + (qx * ay - qy * ax);
    self->quat.w = aw * qw - ((qx * ax + qy * ay) + qz * az);

    self->dir = target;

    Vec3 tmp;
    self->offset = *camera_project(&tmp, &self->dir);
}

// ------------------------------------------------------------------ 0x00ebb2e0
// Follow the steering helper's target direction.
// @ 0x00ebb2e0
void __cdecl follow_steering(Tracked* self)
{
    Vec3 camPos, camDir;
    get_viewer((AppObj*)app_instance())->setup(&camPos, &camDir);

    Vec3 delta;
    delta.x = camPos.x - self->offset.x;
    delta.y = camPos.y - self->offset.y;
    delta.z = camPos.z - self->offset.z;

    int flag9  = (self->mode >> 9) & 1;
    int flag10 = (self->mode >> 10) & 1;

    Vec3 target;
    if (!steering_target(&target, &delta, flag9, flag10))
        return;

    Vec4 q;
    quat_from_directions(&q, &self->dir, &target);

    float ax = self->quat.x, ay = self->quat.y, az = self->quat.z, aw = self->quat.w;
    float qx = q.x, qy = q.y, qz = q.z, qw = q.w;
    self->quat.x = (qw * ax + aw * qx) + (qy * az - qz * ay);
    self->quat.y = (qw * ay + aw * qy) + (qz * ax - qx * az);
    self->quat.z = (qw * az + aw * qz) + (qx * ay - qy * ax);
    self->quat.w = aw * qw - ((qx * ax + qy * ay) + qz * az);

    self->dir = target;

    Vec3 tmp;
    self->offset = *camera_project(&tmp, &self->dir);
}
