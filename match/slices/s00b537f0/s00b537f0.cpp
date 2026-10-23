// Slice s00b537f0 (gold5 #15) -- EA Simulator / SP:: game code (cLocomotiveObject / Havok glue).
// Hand-written faithful C++ reconstruction from the disassembly + Ghidra decompilation.
// Callee addresses are relocations (masked); only the call shapes and the surrounding code matter.
//
// VA map:
//   00b537f0  (323B)  00b53940 (154B)  00b539e0 (183B)  00b53aa0 (124B)
//   00b53b20  (157B)  00b53bc0 (1083B) 00b54000 (506B)  00b54200 ( 41B)
//   00b54230  (201B)  00b54300 ( 58B)  00b54340 (378B)  00b544c0 ( 45B)
//   00b544f0  ( 45B)  00b54520 (139B)  00b545b0 (139B)  00b54640 (259B)
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

struct __declspec(align(16)) Vec4 { float x, y, z, w; };

// ---- eastl hashtable (unsigned key -> int value), find() by value ----
struct EIt { void* node; void* pad; };
struct HT {
    int    f00;          // +0
    void** buckets;      // +4
    int    bucketCount;  // +8
    EIt find(const uint& k) const;
};

struct hkBool { char b; };

// SP spatial / locomotive object.  Virtual slots we call: 0x2c,0x30,0x38,0x60,0x68,0x70,0xb8.
struct CObj {
    virtual void* m00(); virtual void* m01(); virtual void* m02(); virtual void* m03();
    virtual void* m04(); virtual void* m05(); virtual void* m06(); virtual void* m07();
    virtual void* m08(); virtual void* m09(); virtual void* m10();
    virtual void* m11();                 // 0x2c
    virtual void* m12();                 // 0x30
    virtual void* m13();
    virtual void  m14(const void*);      // 0x38
    virtual void* m15(); virtual void* m16(); virtual void* m17();
    virtual void* m18(); virtual void* m19(); virtual void* m20(); virtual void* m21();
    virtual void* m22(); virtual void* m23();
    virtual void  m24(const void*);      // 0x60
    virtual void* m25();
    virtual void* m26();                 // 0x68
    virtual void* m27();
    virtual float m28();                 // 0x70
    virtual void* m29(); virtual void* m30(); virtual void* m31(); virtual void* m32();
    virtual void* m33(); virtual void* m34(); virtual void* m35(); virtual void* m36();
    virtual void* m37(); virtual void* m38(); virtual void* m39(); virtual void* m40();
    virtual void* m41(); virtual void* m42(); virtual void* m43(); virtual void* m44();
    virtual void* m45();
    virtual int   m46(int);              // 0xb8
    // non-virtual thiscall externals (not defined here)
    float  getMass();
    void   setMotionType(int, int, int);
    void   setPosition(const void*);
    void   setLinearVelocity(const void*);
    void   setTranslation(const void*);
    hkBool isActive();
    void   activate();
    void   d1df0(void*, void*);
    void   d3d0(const void*);
    void   d530(const void*, int);
    void   d7e0(const void*);
    int    d2e0();
    void   d570(const void*);
    void   d8ae0();
};

// ---- external callees ----
extern "C" int  FUN_00b53940(void*);
extern "C" void FUN_00b4d8e0(void*, int);
extern "C" void FUN_00b4e1d0(void*, int);
extern "C" void FUN_00b523e0(void*, int);
extern "C" void FUN_00b4e0c0(void*, int, void*);
extern "C" void FUN_00b658c0(void*, void*);
extern "C" void FUN_00b55680(void*, void*, int);
extern "C" int  FUN_00b521f0(int);
extern "C" void FUN_01087820(void*);
extern "C" void operator_delete(void*);
extern "C" int  gEmptyString16;
extern "C" int  eastl_sprintf(void* s, const char* fmt, ...);

extern HT HT_167ed58, HT_16801a8, HT_1682a48, HT_16852e8, HT_1569cb8;
extern int* g_1569c9c;
extern int  g_1569ca0;
extern CObj* g_167ecdc;

// ---- eastl hashtable whose iterator is materialised in a caller 12-byte slot ----
struct EIt12 { int a, b, c; };
struct S12   { uint key; int b, c; };
struct HT12  { EIt12 find(const uint& k) const; void** add(const S12* k); };
struct ObjB  { void d770(); };
extern HT12 g_ht12;    // 0x1569cb8
extern int* g_arr12;   // 0x1569cbc
extern int  g_cnt12;   // 0x1569cc0
extern "C" void* FUN_00b51e80(S12*, float);

// ---------------------------------------------------------------------------
// @ 0x00b537f0
extern "C" void FUN_00b537f0(CObj* p, int a2, char a3, char a4)
{
    if (a2 == 0)
        return;
    if (a3 != 0) {
        float* v = (float*)p->m11();
        Vec4 vv;
        vv.x = v[0]; vv.y = v[1]; vv.z = v[2]; vv.w = 0.0f;
        p->d3d0(&vv);
    }
    if (a4 != 0) {
        float* v = (float*)p->m11();
        Vec4 vv;
        vv.x = v[0]; vv.y = v[1]; vv.z = v[2]; vv.w = 0.0f;
        p->d7e0(&vv);
    }
    {
        float* v = (float*)p->m12();
        Vec4 vv;
        vv.x = v[0]; vv.y = v[1]; vv.z = v[2]; vv.w = v[3];
        p->d530(&vv, a4);
    }
    if ((*(uint*)((char*)p + 0x50) & 0x2000) != 0) {
        int h = p->m46(0x1186577);
        int q = FUN_00b521f0(h);
        if (q != 0) {
            int r = ((CObj*)a2)->d2e0();
            int x = *(int*)(r + 0x1c);
            int y = *(int*)(r + 0x58);
            Vec4 ab;
            typedef void (__stdcall *FNAABB)(void*, float, int, void*);
            ((FNAABB)*(void**)((*(int*)x) + 0xc))((void*)(y + 0x10), 1.0f, x, &ab);
            ((CObj*)q)->setPosition(&ab);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00b53940
extern "C" int FUN_00b53940(void* p)
{
    if (p != 0 && ((CObj*)p)->m46(0x116dd1b) != 0) {
        EIt it = HT_167ed58.find((uint)p);
        if (it.node != HT_167ed58.buckets[HT_167ed58.bucketCount]) {
            int v = *(int*)((char*)it.node + 4);
            if (v != 0)
                return ((CObj*)v)->d2e0();
        }
    } else {
        EIt it = HT_16801a8.find((uint)p);
        if (it.node != HT_16801a8.buckets[HT_16801a8.bucketCount])
            return *(int*)((char*)it.node + 4);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00b539e0
extern "C" void FUN_00b539e0(void* p)
{
    uint k = (uint)p;
    EIt it = HT_1682a48.find(k);
    if (it.node != HT_1682a48.buckets[HT_1682a48.bucketCount])
        FUN_00b4e1d0(p, *(int*)((char*)it.node + 4));
    if (p == 0)
        { FUN_00b523e0(p, 0); return; }
    int e = ((CObj*)p)->m46(0x116dd1b);
    if (e == 0)
        { FUN_00b523e0(p, 0); return; }
    EIt it2 = HT_167ed58.find(k);
    if (it2.node == HT_167ed58.buckets[HT_167ed58.bucketCount])
        return;
    if (*(int*)((char*)it2.node + 4) == 0)
        return;
    FUN_00b537f0((CObj*)e, *(int*)((char*)it2.node + 4), 1, 1);
}

// ---------------------------------------------------------------------------
// @ 0x00b53aa0
extern "C" void FUN_00b53aa0(int* p, void* out)
{
    char* s4;
    char* s3;
    int   ecx;
    int   id;
    switch (p[5]) {
    case 1:  s4 = (char*)0x01461318; break;   // "@center"
    case 2:  s4 = (char*)0x01461320; break;   // "  @base"
    default: s4 = (char*)0x01461328; break;   // "   @???"
    }
    ecx = p[6];
    if (ecx != 0)
        s3 = (char*)0x0146130c;               // " resource"
    else
        s3 = (p[0x1c] == 0) ? (char*)0x014612f4 /* "generated" */
                            : (char*)0x01461300 /* "   cloned" */;
    if (ecx != 0)
        id = (int)*(short*)((char*)ecx + 6);
    else {
        ecx = p[3];
        if (ecx != 0)
            id = (int)*(short*)((char*)ecx + 6);
        else
            id = 0;
    }
    eastl_sprintf(out, "[%3d](%08x!%08x, %6.3f, %s, %s) <%08x>",
                  id, p[2], p[0], (double)*(float*)&p[4], s3, s4, (int)p);
}

// ---------------------------------------------------------------------------
// @ 0x00b53b20
extern "C" void FUN_00b53b20(void)
{
    int* base = g_1569c9c;
    int* it = base;
    int v = *it;
    if (v == 0) {
        do { it++; } while (*it == 0);
        v = *it;
    }
    int end = base[g_1569ca0];
    while (v != end) {
        char* buf[3];
        buf[0] = (char*)&gEmptyString16;
        buf[1] = (char*)&gEmptyString16;
        buf[2] = (char*)0x01667bad;
        FUN_00b53aa0((int*)(v + 0x10), buf);
        if (1 < buf[2] - buf[0] && buf[0] != 0)
            operator_delete(buf[0]);
        v = *(int*)(v + 0x90);
        while (v == 0) { it++; v = *it; }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00b53bc0  (approximate)
extern "C" char FUN_00b53bc0(CObj* p, void* a2, void* a3, Vec4* a4, char a5)
{
    (void)a2; (void)a3; (void)a4; (void)a5;
    int e = FUN_00b53940(p);
    if (e == 0)
        return 0;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00b54000  (approximate)
extern "C" void FUN_00b54000(CObj* p, int a2)
{
    if (a2 == 0) {
        uint k = (uint)p;
        EIt it = HT_16852e8.find(k);
        if (it.node == HT_16852e8.buckets[HT_16852e8.bucketCount])
            return;
        a2 = *(int*)((char*)it.node + 4);
        if (a2 == 0)
            return;
    }
    (void)p; (void)a2;
}

// ---------------------------------------------------------------------------
// @ 0x00b54200
extern "C" char FUN_00b54200(void* p)
{
    char r = 0;
    CObj* o = (CObj*)FUN_00b53940(p);
    if (o != 0) {
        o->setMotionType(1, 1, 0);
        r = 1;
    }
    return r;
}

// ---------------------------------------------------------------------------
// @ 0x00b54230
extern "C" int FUN_00b54230(void* p, CObj* b)
{
    if (b == 0) {
        b = (CObj*)FUN_00b53940(p);
        if (b == 0) {
            uint k = (uint)p;
            EIt it = HT_167ed58.find(k);
            int val = (it.node != HT_167ed58.buckets[HT_167ed58.bucketCount])
                          ? *(int*)((char*)it.node + 4) : 0;
            if (val != 0) {
                float* v = (float*)((CObj*)p)->m11();
                Vec4 vv;
                vv.x = v[0]; vv.y = v[1]; vv.z = v[2]; vv.w = 0.0f;
                ((CObj*)val)->d7e0(&vv);
                return 1;
            }
            return 0;
        }
    }
    Vec4 vv;
    FUN_00b4e0c0(p, (int)b, &vv);
    b->setPosition(&vv);
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00b54300
extern "C" void FUN_00b54300(void* a, void* b)
{
    if (g_167ecdc == 0)
        return;
    int x = FUN_00b53940(a);
    int y = FUN_00b53940(b);
    if (x != 0 && y != 0)
        g_167ecdc->d1df0((void*)x, (void*)y);
}

// ---------------------------------------------------------------------------
// @ 0x00b54340  (approximate)
extern "C" void FUN_00b54340(void* p, float* v, char a3)
{
    if (p != 0 && *((char*)p + 0x71) == 0) {
        int e = FUN_00b53940(p);
        if (e != 0)
            ((CObj*)e)->setMotionType(1, 1, 0);
    }
    {
        uint k = (uint)p;
        EIt it = HT_167ed58.find(k);
        if (it.node != HT_167ed58.buckets[HT_167ed58.bucketCount] &&
            *(int*)((char*)it.node + 4) != 0) {
            int e = ((CObj*)*(int*)((char*)it.node + 4))->d2e0();
            if (e != 0) {
                Vec4 vv;
                vv.x = v[0]; vv.y = v[1]; vv.z = v[2]; vv.w = 0.0f;
                if (a3 != 0) {
                    float m = ((CObj*)(*(int*)((char*)e + 0x58)))->getMass();
                    vv.x *= m; vv.y *= m; vv.z *= m; vv.w *= m;
                }
                ((CObj*)e)->d570(&vv);
            }
            return;
        }
    }
    {
        int e = FUN_00b53940(p);
        if (e != 0) {
            Vec4 vv;
            vv.x = v[0]; vv.y = v[1]; vv.z = v[2]; vv.w = 0.0f;
            if (a3 != 0) {
                float m = ((CObj*)(*(int*)((char*)e + 0x58)))->getMass();
                vv.x *= m; vv.y *= m; vv.z *= m; vv.w *= m;
            }
            ((CObj*)e)->activate();
            ((CObj*)(*(int*)((char*)e + 0x58)))->m24(&vv);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00b544c0
extern "C" void FUN_00b544c0(void* a, int b)
{
    *(uint*)((char*)a + 0x50) &= 0xffffff7fu;
    if (b == 0) {
        b = FUN_00b53940(a);
        if (b == 0)
            return;
    }
    FUN_00b4d8e0(a, b);
}

// ---------------------------------------------------------------------------
// @ 0x00b544f0
extern "C" void FUN_00b544f0(void* a, int b)
{
    *(uint*)((char*)a + 0x50) |= 0x80u;
    if (b == 0) {
        b = FUN_00b53940(a);
        if (b == 0)
            return;
    }
    FUN_00b4d8e0(a, b);
}

// ---------------------------------------------------------------------------
// @ 0x00b54520
extern "C" bool FUN_00b54520(void* p)
{
    CObj* e = (CObj*)FUN_00b53940(p);
    if (e != 0 && e->isActive().b != 0) {
        Vec4 v;
        FUN_00b658c0(&v, e);
        float s = v.x * v.x;
        s = s + v.y * v.y;
        s = s + v.z * v.z;
        return s > 1.52587890625e-05f;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x00b545b0
extern "C" bool __stdcall FUN_00b545b0(S12* p)
{
    EIt12 it = g_ht12.find(p->key);
    int n = g_cnt12;
    if (it.a != g_arr12[n])
        return true;
    it = *(EIt12*)p;
    it.b = 0;
    void* r = FUN_00b51e80((S12*)&it, 1.0f);
    if (r != 0) {
        ((ObjB*)r)->d770();
        *(void**)g_ht12.add((S12*)&it) = r;
    } else {
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00b54640  (approximate)
struct C54640 { int FUN_00b54640(int); };
int C54640::FUN_00b54640(int a)
{
    return (int)this + a;
}
