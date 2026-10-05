// SP::cSPEditorBlock — limb/part selection (unoptimized /Od /Ob1).
#include "types.h"

namespace SP {

struct Vec3 { float x, y, z; };
struct Blk {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void SetState(int a, int b);      // +0x30
    virtual void Refresh();                    // +0x14
};

struct cSPEditorBlock {
    char     pad00[0x10];
    void*    mModel;        // +0x10
    char     pad14[0x18 - 0x14];
    void*    p18;           // +0x18
    char     pad1c[0x154 - 0x1c];
    Blk*     slots[3];      // +0x154
    char     pad160[0x1A8 - 0x160];
    uint8_t  f1a8;          // +0x1A8
    char     pad1a9[0x1B0 - 0x1A9];
    int      f1b0;          // +0x1B0
    char     pad1b4[0x330 - 0x1B4];
    int      f330;          // +0x330
    char     pad334[0x3F0 - 0x334];
    void*    p3f0;          // +0x3F0
    char     pad3f4[0x40C - 0x3F4];
    Vec3     v40c;          // +0x40C
    char     pad418[0x43C - 0x418];
    int      f43c;          // +0x43C
    float    f440;          // +0x440
    float    f444;          // +0x444
    char     pad448[0x6CC - 0x448];
    void**   vec6cc;        // +0x6CC
    void**   vec6d0;        // +0x6D0
    char     pad6d4[0xDC8 - 0x6D4];
    uint32_t flags0;        // +0xDC8
    uint32_t flags1;        // +0xDCC

    int  F3d690(int idx, int a3, int a4, char a5, char a6);  // 0043D690
    Vec3* F3e080(Vec3* out);                                 // 0043E080
    bool F3e0f0(int* out);                                   // 0043E0F0
    void F3e2b0();                                           // 0043E2B0
};

bool  Sub_401060(void);                        // 00401060
void  Sub_4809A0(int x);                       // 004809A0
void  Sub_435a10(int a, int b);                // 00435A10
void  Sub_4D570();
void  Sub_37400(int x);
void  Sub_37310(int x, int y);
int   Sub_3c3d0(void* p);
void  Sub_85650();
void* Sub_41DCA0(void* out, void* table, const float* key);
void* Sub_41DAF0(void* out, void* v);
void  Sub_4_85650();

// @ 0x0043D690
int cSPEditorBlock::F3d690(int idx, int a3, int a4, char a5, char a6)
{
    int count = (int)(vec6d0 - vec6cc);
    if (idx >= count) return 0;
    Blk* b = *(Blk**)((char*)vec6cc + idx * 4);
    b->Refresh();
    float lo = 0.0f, hi = 0.0f;
    float s = (hi - lo) * *(float*)((char*)b + 0x180) + lo;
    (void)s;
    Sub_4D570();
    if (a5 != 0) {
        Sub_37400(1);
        Sub_37310(idx, 1);
    }
    f1a8 = 1;
    if (a6 != 0 && *(int*)((char*)b + 0xB4) != 0) {
        int c = Sub_3c3d0(*(void**)((char*)b + 0xB4));
        if (c != idx) F3d690(c, a3, a4, a5, 0);
    }
    for (int i = 0; i < 3; i++) {
        if (slots[i] != 0) {
            Sub_85650();
            slots[i]->Refresh();
        }
    }
    return 1;
}

// @ 0x0043E080
Vec3* cSPEditorBlock::F3e080(Vec3* out)
{
    void* r = Sub_41DCA0(&v40c, (char*)this + 0x1D8, &v40c.x);
    Vec3* p = (Vec3*)Sub_41DAF0(out, r);
    out->x = p->x;
    out->y = p->y;
    out->z = p->z;
    return out;
}

// @ 0x0043E0F0
bool cSPEditorBlock::F3e0f0(int* out)
{
    int n = 0;
    (void)n;
    int count = (int)(vec6d0 - vec6cc);
    if (out == 0 || count <= 0) return false;
    return false;
}

// @ 0x0043E2B0
void cSPEditorBlock::F3e2b0()
{
    int count = (int)(vec6d0 - vec6cc);
    f440 = 0.4f;
    f444 = -0.35f;
    if (count > 0) {
        f43c = 0;
        for (int i = 0; i < count; i++) {
            if ((flags0 & 0x800u) == 0 || i != 0) {
                Blk* b = *(Blk**)((char*)vec6cc + i * 4);
                F3d690(i, *(int*)((char*)b + 0xA8), 0, 0, 1);
            }
        }
    }
}

} // namespace SP
