// Slice s0041aaa0: builds a quantized bounds table by sweeping an animation/morph
// controller's parameters (up to 8) and sampling bounds at each combination.
#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; };
struct Bounds { Vec3 lo, hi; };               // 0x18 bytes

struct Transform { uint32_t d[0x5c / 4]; };   // 0x5c bytes
void __fastcall Transform_Ctor(Transform*);   // placeholders for thiscall helpers

struct IController {
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual void p3();
    virtual void p4();
    virtual void p5();
    virtual void p6();
    virtual void p7();
    virtual void p8();
    virtual void p9();
    virtual void p10();
    virtual void p11();
    virtual void p12();
    virtual void p13();
    virtual void p14();
    virtual void p15();
    virtual void p16();
    virtual void p17();
    virtual void p18();
    virtual void p19();
    virtual void p20();
    virtual void p21();
    virtual void p22();
    virtual void p23();
    virtual void p24();
    virtual void p25();
    virtual void p26();
    virtual void p27();
    virtual void p28();
    virtual void SetParam(void* obj, int id, float value, int flags);               // slot 29, 0x74
    virtual void p30();
    virtual void p31();
    virtual void GetParamRange(void* obj, int id, float* lo, float* hi, int fl);    // slot 32, 0x80
    virtual void p33();
    virtual void p34();
    virtual void p35();
    virtual void p36();
    virtual void p37();
    virtual void p38();
    virtual void p39();
    virtual void p40();
    virtual void p41();
    virtual void p42();
    virtual void p43();
    virtual void p44();
    virtual void p45();
    virtual void p46();
    virtual void p47();
    virtual void p48();
    virtual void p49();
    virtual void p50();
    virtual void p51();
    virtual void p52();
    virtual void p53();
    virtual void p54();
    virtual void p55();
    virtual void p56();
    virtual void p57();
    virtual int  EnumParams(void* obj, void* out, int max);                         // slot 58, 0xe8
    virtual void p59();
    virtual void p60();
    virtual void GetComponents(void* obj, void* outVec);                            // slot 61, 0xf4
};

struct IWriter {
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual void p3();
    virtual void p4();
    virtual void p5();
    virtual void p6();
    virtual void p7();
    virtual void p8();
    virtual void p9();
    virtual void p10();
    virtual void p11();
    virtual void p12();
    virtual void p13();
    virtual void Write(const void* data, int size);                                 // slot 14, 0x38
};

// Helpers (callees, resolved by address in the original)
void __cdecl  BoundsReset();                                  // 0x409c00
Vec3* __cdecl Vec3Min(Vec3* out, const Vec3* a, const Vec3* b); // 0x41c0c0
Vec3* __cdecl Vec3Max(Vec3* out, const Vec3* a, const Vec3* b); // 0x41bfb0
Vec3* __cdecl Vec3Sub(Vec3* out, const Vec3* a, const Vec3* b); // 0x41db10
float __cdecl Vec3Length(const Vec3* v);                      // 0x41bf30
int   __cdecl FindComponentIndex(unsigned id, int a, int b, int c, int d); // 0x71ddc0
void  __cdecl AccumulateComponent(int p);                     // 0x41bd50
void  __cdecl Cleanup1();                                     // 0x41eb80

struct ParamSweep {
    Bounds* begin;        // 0x00
    Bounds* end;          // 0x04
    int     pad08[3];
    int     counts[8];    // 0x14
    int     handles[8];   // 0x34
    int     numParams;    // 0x54
    IController* ctl;     // 0x58
    void*   obj;          // 0x5c

    // @ 0x41aaa0
    bool Build(void* object, IWriter* out);
};

static inline unsigned QuantNibble(float v, float step)
{
    float q = v / step;
    int c = (int)floorf(q + 0.5f);
    if ((float)c < q) c++;
    unsigned u = 15;
    return (unsigned)(c < 16 ? c : u) & 0xf;
}

// @ 0x41aaa0
bool ParamSweep::Build(void* object, IWriter* out)
{
    obj = object;
    ctl = *(IController**)object;

    Transform xforms[32];
    for (int i = 0; i < 32; i++) Transform_Ctor(&xforms[i]);

    int n = ctl->EnumParams(obj, xforms, 32);
    float minV[8], maxV[8];
    float hdr[9];
    hdr[0] = hdr[1] = hdr[2] = hdr[3] = hdr[4] = hdr[5] = hdr[6] = 0.0f;
    hdr[7] = 0.0f; hdr[8] = 0.0f;

    if (n != 0) {
        int total = 1;
        for (int i = 0; i < n; i++) {
            handles[i] = ((int*)&xforms[i])[0];
            ctl->GetParamRange(obj, handles[i], &minV[i], &maxV[i], 0);
            ctl->SetParam(obj, handles[i], minV[i], 0);
            counts[i] = 4;
            total <<= 2;
        }
        for (int i = n; i < 8; i++) { handles[i] = 0; counts[i] = 0; }
        numParams = n;

        int idx[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        for (;;) {
            BoundsReset();
            void* comps[3] = {0, 0, 0};
            ctl->GetComponents(obj, comps);
            int cnt = (int)(((char*)comps[1] - (char*)comps[0]) >> 2);
            for (int i = 0; i < cnt; i++) {
                int e = FindComponentIndex(((unsigned*)comps[0])[i], 1, -1, 3, 0xe);
                if (e >= 0) AccumulateComponent(e);
            }
            int p = numParams - 1;
            while (++idx[p] >= counts[p]) {
                idx[p] = 0;
                ctl->SetParam(obj, handles[p], minV[p], 0);
                if (--p < 0) {
                    // all samples gathered
                    Vec3 lo = begin->lo, hi = begin->hi;
                    Vec3 lo2 = begin->lo, hi2 = begin->hi;
                    for (int k = 1; k < total; k++) {
                        Vec3 t;
                        hi = *Vec3Min(&t, &hi, &begin[k].hi);
                        hi2 = *Vec3Max(&t, &hi2, &begin[k].hi);
                        lo = *Vec3Max(&t, &lo, &begin[k].lo);
                        lo2 = *Vec3Min(&t, &lo2, &begin[k].lo);
                    }
                    Vec3 t1, t2;
                    float l1 = Vec3Length(Vec3Sub(&t1, &lo, &lo2));
                    float l2 = Vec3Length(Vec3Sub(&t2, &hi2, &hi));
                    float step = (l1 <= l2 ? l2 : l1) / 15.0f;
                    hdr[0] = lo.x; hdr[1] = lo.y; hdr[2] = lo.z;
                    hdr[3] = hi.x; hdr[4] = hi.y; hdr[5] = hi.z;
                    hdr[6] = step;
                    unsigned char* pk = (unsigned char*)&hdr[7];
                    for (int k = 0; k < 8; k++) pk[k] = (unsigned char)counts[k];
                    out->Write(hdr, 0x24);

                    unsigned char* buf = new unsigned char[total * 3];
                    unsigned char* w = buf;
                    for (int k = 0; k < total; k++) {
                        Vec3 a, b, ta, tb;
                        a = *Vec3Sub(&ta, &lo, (Vec3*)&begin[k]);
                        b = *Vec3Sub(&tb, (Vec3*)&begin[k].hi, &hi2);
                        w[0] = (unsigned char)((QuantNibble(a.x, step) << 4) | QuantNibble(b.x, step));
                        w[1] = (unsigned char)((QuantNibble(a.y, step) << 4) | QuantNibble(b.y, step));
                        w[2] = (unsigned char)((QuantNibble(a.z, step) << 4) | QuantNibble(b.z, step));
                        w += 3;
                    }
                    out->Write(buf, total * 3);
                    delete[] buf;
                    Cleanup1();
                    return true;
                }
            }
            float lo = minV[p];
            float v = lo + ((float)idx[p] / (float)(counts[p] - 1)) * (maxV[p] - lo);
            ctl->SetParam(obj, handles[p], v, 0);
        }
    }

    // no parameters: single sample
    BoundsReset();
    void* comps[3] = {0, 0, 0};
    ctl->GetComponents(obj, comps);
    int cnt = (int)(((char*)comps[1] - (char*)comps[0]) >> 2);
    for (int i = 0; i < cnt; i++) {
        int e = FindComponentIndex(((unsigned*)comps[0])[i], 1, -1, 3, 0xe);
        if (e >= 0) AccumulateComponent(e);
    }
    Cleanup1();
    return false;
}
