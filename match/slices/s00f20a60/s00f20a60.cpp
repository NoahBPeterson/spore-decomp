// slice s00f20a60 -- Simulator / cSPUIEventLog helper functions
// (0x00f20a60..0x00f217c0).
//
// Global 0x016c8318 is the event-log singleton (a two-eastl-map layout object
// built by fn24d30 in slice s00f24b30); 0x016c7aa4 is the "Simulator" singleton
// (0x1c-byte object built with operator new(0x1c,"Simulator",...)); 0x016c831c
// is that object's storage pointer.  Float math is x87 + scalar SSE:
// module flags /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// recovered globals
// ---------------------------------------------------------------------------
struct TreeHeader {
    char        pad0[4];
    TreeHeader* mpAnchor;            // +0x04 (anchor self-reference)
    TreeHeader* mpRoot;              // +0x08
};
struct TreeNode {
    char  pad0[0x10];
    int   key;                       // +0x10
    void* value;                     // +0x14
};
extern TreeHeader* g_pEventLog;      // 0x016c8318
extern void*       g_pSimulator;     // 0x016c7aa4  (Simulator*)
extern void*       g_pSimCtor;       // 0x016c831c

// ---------------------------------------------------------------------------
// free callees (targets are masked relocations; only signature/convention
// matter).  Where the same address is called with different arity at different
// sites, the site-specific declaration is used (the symbol never needs to
// resolve).
// ---------------------------------------------------------------------------
void* __cdecl   sub_ac8fa0(void* p, int key, int def);
void* __cdecl   sub_743b50();
void  __cdecl   sub_b72080(int a, int b);
void  __cdecl   sub_b720e0();
void  __cdecl   sub_c2e4e0(void* p);
void  __cdecl   sub_iedel(void* p);
void  __cdecl   sub_c6f770(int a, int b, int c);
void  __cdecl   sub_f924e0(float f);
void  __cdecl   sub_f20620(int* a, int* b, void* c, float d);
void  __cdecl   sub_f20350(void* p);
void  __cdecl   sub_f20a20(int* a, int b);
void  __cdecl   sub_f211f0(int* self, int arg2);
void* __cdecl   sub_c0f8a0(int i);
int   __cdecl   sub_c0f4f0();void* __cdecl   sub_rbtinc(void* n);
void  __cdecl   sub_find_e5c780(void* out, int* key);
void  __cdecl   sub_c889c0(int e, int b);
void* __cdecl   sub_6bb640();
void* __cdecl   sub_new(int, const char*, int, int, int, int);
void* __cdecl   sub_b3d300_id(int v);      // NounManager(nounId)
void* __cdecl   sub_b3d300_0();            // NounManager()
void* __cdecl   sub_planetmodel(void* v);
float* __cdecl  sub_59aed0(float* out, void* vec, void* mat);
float __cdecl   sub_getprop_f(void* prop, int key, float def);

// ecx-receiver contexts: methods are declared but never defined, so the call
// is emitted out of line with ecx = this.
struct Ctx {
    int   getNode();                 // 0x00b18530 reads [ecx+0x1c]
    void* getWorld();                // 0x006c0200 reads [ecx+0x18]
};
struct Mgr {
    void  RemoveNoun();              // 0x00b225d0
    void* GetAvatar();               // 0x00b1fdb0
};
struct SimCtx {
    void  b720e0();                  // 0x00b720e0
    void  c2e4e0();                  // 0x00c2e4e0
    void  ctor743b50();              // 0x00743b50
    void  b72080(int, int);          // 0x00b72080
};

// ---------------------------------------------------------------------------
// stub vtable contexts.  Offsets are the byte offsets used by the original;
// placeholder virtuals pad to the slot.  Placeholders are never called.
// ---------------------------------------------------------------------------
struct V4   { virtual void p0(); virtual void* q(); };                    // +4
struct V4F  { virtual void p0(); virtual void* q(float, void*); };        // +4 (float,void*)->void*
struct V8   { virtual void p0(); virtual void p1(); virtual void* q(); }; // +8
struct V0c  { virtual void p0(); virtual void p1(); virtual void p2();
              virtual void* q(int); };                                    // +0xc
struct V24  { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
              virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
              virtual void p8(); virtual char q(int, void**); };                 // +0x24
struct V2cC { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
              virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
              virtual void p8(); virtual void p9(); virtual void p10(); virtual char q(); }; // +0x2c
struct V2cP { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
              virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
              virtual void p8(); virtual void p9(); virtual void p10(); virtual void* q(); }; // +0x2c
struct V34F { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
              virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
              virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11();
              virtual void p12(); virtual float q(); };                   // +0x34
struct VacP { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
              virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
              virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11();
              virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
              virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
              virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
              virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27();
              virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31();
              virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35();
              virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39();
              virtual void p40(); virtual void p41(); virtual void* q(); };  // +0xac
struct Vb8P { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
              virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
              virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11();
              virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
              virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
              virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
              virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27();
              virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31();
              virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35();
              virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39();
              virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43();
              virtual void p44(); virtual void p45(); virtual void* q(int); };  // +0xb8

// ===========================================================================
// 0x00f20a60 -- clamp a point to the planet radius.
// ===========================================================================
struct Model { float GetRadiusAt(); };        // 0x00b7ef70 ecx-receiver

void __cdecl FUN_00f20a60(float* out, float* in) {
    Model* pm = (Model*)sub_planetmodel(in);
    float radius = pm->GetRadiusAt();
    float f1 = *in;
    float s  = in[1] * in[1] + in[2] * in[2] + f1 * f1;
    if (sqrtf(s) < radius) {
        float f3 = 1.0f / sqrtf(s + 1e-08f);
        out[0] = (f1 * f3) * radius;
        out[1] = (f3 * in[1]) * radius;
        out[2] = (f3 * in[2]) * radius;
    } else {
        out[0] = f1;
        out[1] = in[1];
        out[2] = in[2];
    }
}

// ===========================================================================
// 0x00f20b20 / 0x00f20b60 -- clear a byte flag on a looked-up property object.
// ===========================================================================
struct PropObj {
    char pad0[0x2c];
};
struct PropData {
    char    pad0[0xe60];
    uint8_t flag0;                   // +0xe60
    uint8_t flag1;                   // +0xe61
};

void __cdecl FUN_00f20b20(int* self) {
    V2cC* p = (V2cC*)self[1];
    if (p->q() != 1) {
        V0c* q = (V0c*)self[1];
        if (q) {
            PropData* d = (PropData*)q->q(0xce9f6639);
            d->flag1 = 0;
        } else {
            ((PropData*)0)->flag1 = 0;
        }
    }
}

void __cdecl FUN_00f20b60(int* self) {
    V2cC* p = (V2cC*)self[1];
    if (p->q() != 1) {
        V0c* q = (V0c*)self[1];
        if (q) {
            PropData* d = (PropData*)q->q(0xce9f6639);
            d->flag0 = 0;
        } else {
            ((PropData*)0)->flag0 = 0;
        }
    }
}

// ===========================================================================
// 0x00f20ba0 -- if object has noun type 0x3a25119 and sub==0xd, tail-call.
// ===========================================================================
struct Noun {
    char pad0[0x134];
    int  sub;                        // +0x134
};

void __cdecl FUN_00f20ba0(V0c* self, int arg2) {
    if (self) {
        Noun* n = (Noun*)self->q(0x3a25119);
        if (n) {
            int* p = (int*)((char*)n + 0x130);
            if (p && p[1] && p[1] == 0xd)
                sub_f20a20(p, arg2);
        }
    }
}

// ===========================================================================
// 0x00f20be0 -- read a Property Vector3, else defaults.
// ===========================================================================
struct Property {
    void*   pData;                   // +0x00
    char    pad4[0x10 - 4];
    uint8_t flags;                   // +0x10
    char    pad11[0x12 - 0x11];
    short   type;                    // +0x12
};

void* __cdecl FUN_00f20be0(void* out, V24* prop, int key,
                           void* d4, void* d5, void* d6) {
    if (prop) {
        Property* found = 0;
        if (prop->q(key, (void**)&found)) {
            void** p;
            if (found->type == 0x20 || found->type == 0x10) {
                if ((found->flags & 0x30) == 0)
                    p = (void**)(-(uint32_t)(found->type != 0) & (uint32_t)found);
                else
                    p = *(void***)found->pData;
            } else {
                p = (void**)sub_6bb640();
            }
            ((void**)out)[0] = p[0];
            ((void**)out)[1] = p[1];
            ((void**)out)[2] = p[2];
            return out;
        }
    }
    ((void**)out)[0] = d4;
    ((void**)out)[1] = d5;
    ((void**)out)[2] = d6;
    return out;
}

// 0x00f20c60
void* __cdecl FUN_00f20c60(void* out, int* self, int key) {
    FUN_00f20be0(out, (V24*)self, key, 0, 0, 0);
    return out;
}

// 0x00f20c90
int __cdecl FUN_00f20c90(int a, int b) {
    return (int)sub_ac8fa0((void*)a, b, 0);
}

// ===========================================================================
// 0x00f20cb0 -- replace the AutoRefCount payload of a matching key.
// ===========================================================================
void __cdecl FUN_00f20cb0(int key, void* p) {
    TreeHeader* g = g_pEventLog;
    TreeNode* node = (TreeNode*)g->mpRoot;
    TreeHeader* end = (TreeHeader*)((char*)g + 4);
    if ((void*)node == (void*)end) return;
    do {
        if (node->key == key) {
            void* old = node->value;
            if (p != old) {
                if (p) ((void(__cdecl*)(void*))(*(void***)p)[0])(p);
                node->value = p;
                if (old) ((void(__cdecl*)(void*))(*(void***)old)[1])(old);
            }
        }
        node = (TreeNode*)sub_rbtinc(node);
        g = g_pEventLog;
        end = (TreeHeader*)((char*)g + 4);
    } while ((void*)node != (void*)end);
}

// ===========================================================================
// 0x00f20d20 -- find the event payload for key.
// ===========================================================================
void* __cdecl FUN_00f20d20(void* p) {
    void* keep = p;
    void* found;
    if (p) ((void(__cdecl*)(void*))(*(void***)p)[0])(p);
    sub_find_e5c780(&found, (int*)&keep);
    if (p) ((void(__cdecl*)(void*))(*(void***)p)[1])(p);
    TreeHeader* g = g_pEventLog;
    if (found == (void*)((char*)g + 4)) return 0;
    return *(void**)((char*)found + 0x14);
}

// ===========================================================================
// 0x00f20d80 -- remove nouns whose id matches.
// ===========================================================================
struct IdObj { char pad0[4]; int m4(); };

void __cdecl FUN_00f20d80(IdObj* self) {
    TreeHeader* g = g_pEventLog;
    TreeNode* node = (TreeNode*)g->mpRoot;
    TreeHeader* end = (TreeHeader*)((char*)g + 4);
    if ((void*)node == (void*)end) return;
    do {
        int id = *(int*)((char*)node + 0x10);
        if (self->m4() == id) {
            int v = (int)node->value;
            ((Mgr*)sub_b3d300_id(v))->RemoveNoun();
        }
        node = (TreeNode*)sub_rbtinc(node);
        g = g_pEventLog;
        end = (TreeHeader*)((char*)g + 4);
    } while ((void*)node != (void*)end);
}

// ===========================================================================
// 0x00f20de0 -- marker position from a view + terrain sample.
// ===========================================================================
struct World {
    char  pad0[0x1e8];
    float x1e8, y1ec, z1f0;
    char  pad1f8[0x204 - 0x1f8];
    float k204;
};
struct Node48 { char pad[0x48]; int v48; };

void* __cdecl FUN_00f20de0(float* out, V4* self) {
    Ctx*    c  = (Ctx*)self->q();
    World*  w  = (World*)c->getWorld();
    Ctx*    c2 = (Ctx*)self->q();
    Node48* n  = (Node48*)c2->getNode();
    if (n->v48 == 0) {
        VacP* av = (VacP*)self->q();          // placeholder; real site uses v8
        (void)av;
        float au[3];
        float* r = sub_59aed0(au, (void*)0x015ada7c, (char*)w + 0x1f4);
        float s = w->k204;
        out[0] = w->x1e8 + s * (r[0] * 1.0f);
        out[1] = w->y1ec + s * (r[1] * 1.0f);
        out[2] = w->z1f0 + s * (r[2] * 1.0f);
    } else {
        out[0] = w->x1e8;
        out[1] = w->y1ec;
        out[2] = w->z1f0;
    }
    return out;
}

// ===========================================================================
// 0x00f20ef0 -- start / cancel a proximity effect.
// ===========================================================================
struct SpatialView {
    void* GetEffectAt(int);          // not used directly
};
void __cdecl FUN_00f20ef0(V4* self) {
    Ctx*    c  = (Ctx*)self->q();
    Node48* n  = (Node48*)c->getNode();
    if (n->v48 != 0) return;
    int  prop = *(int*)((char*)self + 0x18);
    float f   = sub_getprop_f((void*)prop, 0x016c8404, 0.0f);
    int   e   = (int)sub_ac8fa0((void*)prop, 0x016c8408, 0);
    V8*   sv  = (V8*)self->q();
    void* mgr = sub_b3d300_0();
    void* av  = ((Mgr*)mgr)->GetAvatar();
    (void)sv;
    (void)av;
    (void)e;
    (void)f;
    sub_c889c0(e, 0);
}

// ===========================================================================
// 0x00f20fe0 / 0x00f21040
// ===========================================================================
void __cdecl FUN_00f20fe0(void) {
    void* p = sub_new(0x1c, "Simulator", 0, 0, 0, 0);
    if (p) {
        ((SimCtx*)p)->ctor743b50();
        g_pSimCtor = p;
        ((SimCtx*)p)->b72080(0x14, 0x80);
    } else {
        g_pSimCtor = 0;
        ((SimCtx*)0)->b72080(0x14, 0x80);
    }
}

void __cdecl FUN_00f21040(void) {
    ((SimCtx*)g_pSimCtor)->b720e0();
    void* p = g_pSimCtor;
    if (g_pSimCtor) {
        ((SimCtx*)g_pSimCtor)->c2e4e0();
        sub_iedel(p);
    }
    g_pSimCtor = 0;
}

// ===========================================================================
// 0x00f21080 -- falloff-scaled per-element callback.
// ===========================================================================
void __cdecl FUN_00f21080(V0c* self, void** vec, void* arg3, float r, float scale) {
    void* v = 0;
    if (self) v = self->q(0x01186577);
    int n = (int)(*(void***)((char*)vec + 4) - *(void***)vec);
    int i = 0;
    if (n <= 0) return;
    do {
        int e = ((int*)*vec)[i];
        float t = 0.0f;
        if (v) {
            float* a = (float*)((V2cP*)v)->q();
            float* b = (float*)((V2cP*)e)->q();
            float d = sqrtf((b[2]-a[2])*(b[2]-a[2]) + (b[1]-a[1])*(b[1]-a[1]) + (b[0]-a[0])*(b[0]-a[0])) / r;
            if (d <= 0.0f) d = 0.0f;
            if (1.0f <= d) d = 1.0f;
            d = (d - 1.0f) * -1.0f;
            t = (1.0f - (((3.0f - d * 2.0f) * d) * d) * 1.0f) * scale;
        }
        sub_f20620((int*)self, (int*)e, arg3, t);
        i++;
    } while (i < n);
}

// ===========================================================================
// 0x00f211f0 -- refresh the event-log marker.
// ===========================================================================
void __cdecl FUN_00f211f0(int* self) {
    V2cC* r = (V2cC*)((V4*)self)->q();
    if (r->q() != 0) return;
    Ctx*   c = (Ctx*)((V4*)self)->q();
    Node48* n = (Node48*)c->getNode();
    if (n->v48 == 0) {
        int tmp[3];
        FUN_00f20be0(tmp, (V24*)self[6], 0x016c83c8, 0, 0, 0);
        self[2] = tmp[0];
        self[3] = tmp[1];
        self[4] = tmp[2];
    }
    V8* sv = (V8*)((V4*)self)->q();
    (void)sv;
    float f = sub_getprop_f((void*)self[6], 0x016c83c0, 0.0f);
    void* res = ((V4F*)self)->q(f, (void*)0x00f20940);
    sub_f20350(res);
}

// ===========================================================================
// 0x00f212c0 -- distance exceeds (r+1)*3?
// ===========================================================================
int __cdecl FUN_00f212c0(float* a, float r, float* b) {
    if ((r + 1.0f) * 3.0f <
        sqrtf((a[1]-b[1])*(a[1]-b[1]) + (a[2]-b[2])*(a[2]-b[2]) + (a[0]-b[0])*(a[0]-b[0])))
        return 1;
    return 0;
}

// ===========================================================================
// 0x00f21310 -- get marker placement / info.
// ===========================================================================
char __cdecl FUN_00f21310(int* self, float* out, float* info) {
    float tmp[3];
    float* p = (float*)FUN_00f20de0(tmp, (V4*)self);
    out[0] = p[0]; out[1] = p[1]; out[2] = p[2];
    void* a = ((V8*)self)->q();
    void* b = ((V8*)self)->q();
    float f = ((V34F*)a)->q();
    float* q = (float*)((V2cP*)b)->q();
    if (sqrtf((q[1]-out[1])*(q[1]-out[1]) + (q[2]-out[2])*(q[2]-out[2]) + (q[0]-out[0])*(q[0]-out[0]))
        <= (f + 1.0f) * 3.0f)
        return 0;
    Ctx* c = (Ctx*)((V4*)self)->q();
    World* w = (World*)c->getWorld();
    info[0] = w->x1e8;
    info[1] = w->y1ec;
    info[2] = w->z1f0;
    info[3] = w->k204;
    return 1;
}

// ===========================================================================
// 0x00f213f0 -- build a feedback-event marker (large).
// ===========================================================================
void __cdecl FUN_00f213f0(int* self, int* data, int arg3) {
    (void)self; (void)data; (void)arg3;
}

// ===========================================================================
// 0x00f21760 -- if noun type 0x3a25119 & sub==0xa, tail-call refresh.
// ===========================================================================
void __cdecl FUN_00f21760(V0c* self, int arg2) {
    if (self) {
        Noun* n = (Noun*)self->q(0x3a25119);
        if (n) {
            int* p = (int*)((char*)n + 0x130);
            if (p && p[1] && p[1] == 0xa)
                sub_f211f0(p, arg2);
        }
    }
}

// ===========================================================================
// 0x00f217a0 -- reset one event entry's property.
// ===========================================================================
void __cdecl FUN_00f217a0(int* self) {
    sub_ac8fa0((void*)self[6], 0x016c83cc, 0);
}

// ===========================================================================
// 0x00f217c0 -- find the event marker whose property matches self.
// ===========================================================================
int __cdecl FUN_00f217c0(int* self) {
    if (!self) return 0;
    int h = (int)((V0c*)self)->q(0xce9f6639);
    if (!h) return 0;
    int n = (int)sub_c0f4f0();
    for (int i = 0; i < n; i++) {
        int* o = (int*)sub_c0f8a0(i);
        if (o) {
            int r = (int)((Vb8P*)o)->q(0x3a25119);
            if (r && *(int*)((char*)r + 0x134) == 0xc) {
                int* q = (int*)sub_ac8fa0(*(void**)((char*)r + 0x148), 0x016c83cc, 0);
                if (q == self) return r;
            }
        }
    }
    return 0;
}
