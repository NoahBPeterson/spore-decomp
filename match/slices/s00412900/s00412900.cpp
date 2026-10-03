// Builds a ribbon/trail of points ("rope" segments) for one node of a 0x8c-byte-stride node array.
// Built /Od /Ob1 /MD /Gy /TP /arch:SSE (unoptimized module). Behavioral reconstruction, not byte-exact.
#include "types.h"
namespace A {
struct Vec3 { float x, y, z; };

// helper callees (addresses in comments)
Vec3* __cdecl Vec3Sub(Vec3* out, const Vec3* a, const Vec3* b);                       // 41db10
Vec3* __cdecl Vec3SubScaled(Vec3* out, const Vec3* a, const Vec3* b, const float* s); // 41db10 (4-arg call site)
Vec3* __cdecl Vec3Unary(Vec3* out, const Vec3* v);                                    // 41dca0
Vec3* __cdecl Vec3Add(Vec3* out, const Vec3* a, const Vec3* b);                       // 41dc10
Vec3* __cdecl Vec3Mul(Vec3* out, const Vec3* a, const Vec3* b);                       // 41db10-like (scale)
void  __cdecl Vec3Normalize(Vec3* v, const Vec3* ref);                                // 41ddb0
float __cdecl Vec3Length(const Vec3* v);                                              // 413d60
float __cdecl Vec3Length2(const Vec3* v);                                             // 40ae50
Vec3* __cdecl Vec3Transform(Vec3* out, const Vec3* v, const Vec3* m);                 // unchecked helper
Vec3* __cdecl Vec3Curve(Vec3* out, const Vec3* a, const Vec3* b, const Vec3* c, const Vec3* d, float t); // 4224b0
Vec3* __cdecl Vec3Blend(Vec3* out, const Vec3* a, const Vec3* b, float t, const float* w, const Vec3* c); // 413cc0
void  __cdecl GetFloatProp(int obj, uint32_t id, float* v);                           // 40cf10
void  __cdecl GetIntProp(int obj, uint32_t id, int* v);                               // 6a12a0
int*  __cdecl FindFirst(int* begin, int* end, const int* key);                        // 422430

struct PointList { char pad[8]; char* first; char* last; };
struct Path {
    int AddPoint(const Vec3* pos, float w, float width, uint32_t color);   // 4fcc20
    void Link(int a, int b, float w, uint32_t color);                      // 4fcca0
};
struct Node {                 // sizeof 0x8c
    uint16_t pad0;
    int16_t  parent;          // 0x04
    uint16_t flags;           // 0x08 (low byte at 8, type byte at 0xb)
    char     pad1[0x30 - 0x0a];
    Vec3     axis;            // 0x30
    char     pad2[0x54 - 0x3c];
    Vec3     pos;             // 0x54
    char     pad3[0x70 - 0x60];
    float    radius;          // 0x70
    float    t;               // 0x74
    float    w0;              // 0x78
    float    w1;              // 0x7c
    char     pad4[0x84 - 0x80];
    int      keyB;            // 0x84
    int      keyA;            // 0x88
};
struct Builder {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual int LookupEffect(int a, int b);   // slot 0x58/4 = 22
    char pad[0x90 - 4 - 23 * 4 + 0];          // up to 0x90 -> fields at 0x90.. (approx)
    PointList tracks;   // 0x90 (param_1[0x24])
    char* tracksEnd;    // 0x94
    char pad2[0x88 - 0x08 + 0];
    int  dataBase;      // 0xa4 (param_1[0x29])
    Path* path;         // 0x88 in Ghidra's index 0x22 (approx)
    int BuildRope(Node* nodes, int count, int idx, uint32_t colA, uint32_t colB, uint32_t colMid, int prev);
};

static const float kLinkW = 0.3f;     // 0x3e99999a
static const float kOne   = 1.0f;

// @ 0x00412900
int Builder::BuildRope(Node* nodes, int count, int idx, uint32_t colA, uint32_t colB, uint32_t colMid, int prev)
{
    const uint32_t kPropWidth = 0xfe0926f6, kPropScale = 0xfba611, kPropA = 0x105f54ff, kPropB = 0xf061e767;
    Node* n = nodes + idx;
    float radius = n->radius;
    Vec3 base = n->pos;
    Vec3 dir = { 0.0f, -radius, 0.0f };
    Vec3 tmp;
    dir = *Vec3Transform(&tmp, &dir, &n->axis);
    Vec3Normalize(&dir, &n->pos);

    int fx = LookupEffect(n->keyA, n->keyB);
    if (fx != 0) {
        float minW = 0.5f;
        GetFloatProp(fx, kPropWidth, &minW);
        float minWidth = minW * 0.1f;
        if ((n->flags & 0x10) == 0) {
            float scale = 1.0f; int keyA = 0, keyB = 0;
            GetFloatProp(fx, kPropScale, &scale);
            GetIntProp(fx, kPropA, &keyA);
            GetIntProp(fx, kPropB, &keyB);
            if (keyA == 0 || keyB == 0) {
                Vec3 d1; Vec3 e = *Vec3Sub(&d1, (Vec3*)((char*)n + 0x20), (Vec3*)((char*)n + 0x14));
                float len = Vec3Length(&e);
                float lo = 0.01f;
                const float* pl = (len <= lo) ? &lo : &len;
                float base_w = *pl;
                float w3 = base_w * 3.0f, w27 = base_w * 2.7f, w2 = base_w * 2.0f;
                float half = 0.5f;
                Vec3 t1, t2, t3;
                Vec3 mid = *Vec3Add(&t3, &base, Vec3Unary(&t2, Vec3SubScaled(&t1, &dir, &base, &half)));
                if (prev == -1) prev = path->AddPoint(&base, kOne, w3, colA | 0x80000000);
                int pm = path->AddPoint(&mid, kOne, w27, colMid);
                int pe = path->AddPoint(&dir, kOne, w2, colB | 0x80000000);
                path->Link(prev, pm, kLinkW, colMid);
                path->Link(pm, pe, kLinkW, colMid);
            } else {
                int data = dataBase;
                int* tb = (int*)tracks.pad;  // list begin (approx)
                int* lb = *(int**)&tracks.first;
                int* le = (int*)((char*)lb + ((((char*)tracksEnd - (char*)lb) / 12) * 12));
                int* sa = FindFirst(lb, le, &keyA);
                int* sb = FindFirst(lb, le, &keyB);
                int na = 0, nb = 0;
                int* pa = sa; int* pb = sb;
                for (; pa != le && *pa == keyA; pa += 3) na++;
                for (; pb != le && *pb == keyB; pb += 3) nb++;
                (void)tb;
                if (na == nb) {
                    for (int k = 0; k < na; k++) {
                        int cnt = sa[k * 3 + 1];
                        if (sa[k * 3 + 1] != sa[k * 3 + 1]) break;
                        int offA = data + sa[k * 3 + 2] * 4;
                        int offB = data + sb[k * 3 + 2] * 4;
                        int posA = offA, widA = offA + cnt * 12, wA = offA + cnt * 16;
                        int posB = offB, widB = offB + cnt * 12, wB = offB + cnt * 16;
                        int cur = (*(int*)((char*)path + 0xc) - *(int*)((char*)path + 8)) / 0x18;
                        int start = 0;
                        if (prev == -1) { path->Link(cur, cur + 1, kLinkW, colMid); cur++; }
                        else { path->Link(prev, cur, kLinkW, colMid); start = 1; }
                        for (int i = start; i < cnt; i++) {
                            float tt = n->t, w1 = n->w0, w2 = n->w1;
                            if (w2 < 0.0f) w2 = 1.0f;
                            float a0 = *(float*)(wA + i * 4);
                            float mixed = a0 + (*(float*)(wB + i * 4) - a0) * tt;
                            Vec3 t1, t2, t3, t4, t5;
                            Vec3 p = *Vec3Add(&t3, &base, Vec3Unary(&t2, Vec3SubScaled(&t1, &dir, &base, &mixed)));
                            Vec3 d0 = *Vec3Sub(&t4, &p, &base);
                            float f0 = 1.0f - Vec3Length2(&d0) / radius;
                            Vec3 d1v = *Vec3Sub(&t5, &p, &dir);
                            float f1 = 1.0f - Vec3Length2(&d1v) / radius;
                            float c0 = ((w1 - 0.0f) * f0 + 0.0f + (w2 - 0.0f) * f1 + 0.0f) * scale;
                            float wa = *(float*)(widA + i * 4);
                            float w = (wa + (*(float*)(widB + i * 4) - wa) * tt) * c0;
                            if (w < minWidth) w = minWidth;
                            Vec3 t6, t7, t8;
                            Vec3 pt = *Vec3Transform(&t8, Vec3Unary(&t7, Vec3Blend(&t6, (Vec3*)(i * 12 + posA), (Vec3*)(i * 12 + posB), tt, &c0, &n->axis)), 0);
                            uint32_t col;
                            if (i == 0) col = colA | 0x80000000;
                            else if (i == cnt - 1) col = colB | 0x80000000;
                            else { col = colMid; path->Link(cur, cur + 1, kLinkW, colMid); cur++; }
                            path->AddPoint(&pt, kOne, w, col);
                        }
                    }
                }
            }
        } else {
            // chained branch: walk following nodes of type 3 that are children of this node
            Vec3 pA = base, pB = dir, pC = base, pD = dir;
            if (n->parent != -1 && (nodes[n->parent].flags & 4)) pC = nodes[n->parent].pos;
            int j = idx;
            for (;;) {
                j++;
                if (j >= count || *((char*)nodes + 0xb + j * 0x8c) != 3 || nodes[j].parent < idx) break;
                if (nodes[j].parent == idx) {
                    Vec3 t9; Vec3 v = { 0.0f, -nodes[j].radius, 0.0f };
                    pD = *Vec3Transform(&t9, &v, &nodes[j].axis);
                    Vec3Normalize(&pD, &nodes[j].pos);
                    break;
                }
            }
            float w1 = n->w0, w2 = n->w1;
            if (w2 < 0.0f) w2 = 1.0f;
            float a = w1 * 0.1f, b = w2 * 0.1f;
            if (a < minWidth) a = minWidth;
            if (b < minWidth) b = minWidth;
            float half = 0.5f; Vec3 t1, t2, t3;
            Vec3 mid = *Vec3Add(&t3, &base, Vec3Unary(&t2, Vec3SubScaled(&t1, &dir, &base, &half)));
            (void)mid;
            if (prev == -1) prev = path->AddPoint(&base, kOne, a, colA | 0x80000000);
            bool degenerate = !(1.1754944e-38f <= (pA.x < 0 ? -pA.x : pA.x) || 1.1754944e-38f <= (pB.x < 0 ? -pB.x : pB.x));
            if (degenerate) { pC.x = 0.0f; pD.x = 0.0f; }
            int last = prev;
            for (float f = 1.0f; f < 15.0f; f += 1.0f) {
                float t = f / 15.0f;
                Vec3 t4; Vec3 p = *Vec3Curve(&t4, &pC, &pA, &pB, &pD, t);
                int cur = path->AddPoint(&p, kOne, a + (b - a) * t, colMid);
                path->Link(last, cur, kLinkW, colMid);
                last = cur;
            }
            int fin = path->AddPoint(&dir, kOne, b, colB | 0x80000000);
            path->Link(last, fin, kLinkW, colMid);
        }
        prev = (*(int*)((char*)path + 0xc) - *(int*)((char*)path + 8)) / 0x18 - 1;
    }
    return prev;
}
}
