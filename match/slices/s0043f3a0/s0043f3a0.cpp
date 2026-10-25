// SP::cSPEditorBlock — validity/scale helpers (unoptimized /Od /Ob1 /arch:SSE).
#include "types.h"

namespace SP {

struct Vec3 { float x, y, z; };
class cSPEditorBlock;
struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3&);                  // 0041CB40
};

struct cSPBoundingBox {                       // 24 bytes: mMin, mMax
    Vec3 mMin, mMax;
    Vec3 GetCorner(uint32_t mask) const;      // 0043F290
    Vec3 Center();                            // 00409B90
};

Vec3 operator-(const Vec3& a, const Vec3& b); // 0041DB10
float VectorLength(const Vec3* v);            // 0040AE50
void Vector3_Add(Vec3* a, const Vec3* b);     // 0041DDB0

// Transform message (0x434040 ctor).  flags/count + pos + scale + 3x3 rotation.
struct XformMsg {
    uint16_t flags;
    uint16_t count;
    Vec3     pos;
    float    scale;
    Matrix3  rot;
    XformMsg();
    void SetRot(const Matrix3& m) { rot = m; flags |= 2; ++count; }
    void SetPos(const Vec3& v)    { pos = v; flags |= 4; ++count; }
    void SetScale(float s)        { scale = s; ++count; }
};

// SP::cSPEditorModel: vfptr, EA ref-count block at +4 (count at +8), then the
// editor grid fields read by the getters below.
struct cSPEditorModel {
    struct RefCount {
        uint32_t pad04;
        int      mnRefCount;                  // model+0x08
        void     Release();                   // 0x00453540
    };
    uint32_t        vfptr;                    // +0x00
    RefCount        mRef;                     // +0x04
    char            pad0c[0x38 - 0x0c];
    float           mScale;                   // +0x38
    char            pad3c[0x40 - 0x3c];
    float           mMinHeight;               // +0x40
    float           mMaxHeight;               // +0x44
    char            pad48[0x4f - 0x48];
    bool            mbUsingSymmetry;          // +0x4f
    float GetScale();                       // 0x004ADAA0
    float GetMinHeight();                   // 0x004ADB00
    float GetMaxHeight();                   // 0x004ADB40
    bool  UsingSymmetry();                  // 0x004ADC40
    void  SetUsingSymmetry(bool b);         // 0x004ADC20
};

struct Basis { Vec3 rows[3]; };

int ClassifyAgainstSymmetryPlane(Vec3* p, float width, float zmin, float zmax, Basis* out); // 00493640
bool FUN_0049b340(void* owner);               // 0049B340
void FUN_004c5030(uint32_t id, cSPEditorBlock* block);   // 004C5030

struct BitSet60 {
    uint32_t data[2];
    bool Get(int i) {
        if (i < 60) return (data[i >> 5] & (1u << (i % 32))) != 0;
        return false;
    }
};

struct DefaultRefCounted { void Release(); };

class cSPEditorBlock;

struct cSPEditorEffects {
    int  Get(cSPEditorBlock* block);                             // 0045B210
    void Stop(cSPEditorBlock* block);                            // 0045B150
    void SetTransform(cSPEditorBlock* block, const XformMsg* m); // 0045B040
};

struct cEffectsWorld {
    void SetEffectTransform(uint32_t id, int flags, const XformMsg* m,
                            cSPEditorBlock* block);              // 0045AC20
};

struct cMessageManager {
    void PostMSG(uint32_t id, int a, cSPEditorBlock* block, void* b);  // 0045AE40
};

cSPEditorEffects* EditorEffects();            // 00401050
cEffectsWorld*    GetEditorEffectsWorld();    // 00401050
cMessageManager*  MessageManager();           // 00401050

struct Node { bool Check(); };

class cSPEditorBlock { public:
    char             pad00[0x28];
    union {
        cSPEditorModel* mEditorModel; // +0x28
        Node*           node;         // +0x28 (legacy alias)
    };
    char             pad2c[0x60 - 0x2C];
    Matrix3          mOrientation;    // +0x60
    char             pad84[0x144 - 0x84];
    Vec3             mReplacePartDisplacement;  // +0x144
    char             pad150[0x33C - 0x150];
    cSPEditorBlock*  link33c;     // +0x33C
    struct PtrVec {
        cSPEditorBlock** begin;
        cSPEditorBlock** end;
        int size() const { return (int)(end - begin); }
    }                vec340;      // +0x340
    char             pad348[0x3E0 - 0x348];
    cSPEditorBlock*  link3e0;     // +0x3E0
    char             pad3e4[0x3EC - 0x3E4];
    void*            p3ec;        // +0x3EC
    char             pad3f0[0x454 - 0x3F0];
    float            f454;        // +0x454
    char             pad458[0xDC8 - 0x458];
    BitSet60         bits;        // +0xDC8

    float F3eed0();                            // 0043EED0
    float F3f250();                            // 0043F250
    cSPBoundingBox F3eef0();                   // 0043EEF0
    void  F404f0(Matrix3 m);                    // 004404F0
    void  F40420(float v, uint8_t b);          // 00440420
    void  F40520(float v, uint8_t b, int c);   // 00440520
    void  F3a5e0(int type, uint8_t a, uint8_t b, char c);  // 0043A5E0
    void  SetUIState(int state, bool a, bool b, bool c);   // 0043A5E0
    void  SetFlag(int flag, bool value);                   // 00435A10
    bool  Paint();                                         // 0044C030
    cSPBoundingBox GetBBox(int a, bool b, int c);          // 0044AE00
    void  SetValid(char valid, int arg);       // 0043F6B0
    bool  F3fc20(void* pos);                   // 0043FC20

    float F3a0();                              // 0043F3A0
    float F3f0();                              // 0043F3F0
    float F4d0();                              // 0043F4D0
    void  F5b0(Vec3* out, float a, float b, float c, int flag);  // 0043F5B0
    void  FFa0(Matrix3 m);                     // 0043FFA0
    void  F4020(float v, uint8_t b);           // 00440020
    void  F4090(float v, uint8_t b);           // 00440090
    bool  F49b340();                           // 0049B340
};

void  Matrix3_Assign(Matrix3* dst, const Matrix3* src);       // 0041CB40
void  GetBBox(cSPEditorBlock* self, void* out, int, int, int); // from SetValid
void* Sub_41DB10(void* out, void* a, void* b);
Matrix3 Sub_4A8E10(const void* a, int b);                     // 004A8E10
int   Sub_493640(void* v, float f);
void  Sub_4ADC20(int v);
void  Sub_4ADC40_is_NodeCheck(void);

// @ 0x0043F3A0
float cSPEditorBlock::F3a0()
{
    void* p = p3ec;
    if (p != 0) {
        return F3eed0() * 0.3f * 0.5f * f454;
    }
    return 0.0f;
}

// @ 0x0043F3F0
float cSPEditorBlock::F3f0()
{
    int count = vec340.size();
    for (int i = 0; i < count; i++) {
        cSPEditorBlock* o = vec340.begin[i];
        if (o->bits.Get(31)) return o->F3eed0();
    }
    return 1.0f;
}

// @ 0x0043F4D0
float cSPEditorBlock::F4d0()
{
    int count = vec340.size();
    for (int i = 0; i < count; i++) {
        cSPEditorBlock* o = vec340.begin[i];
        if (o->bits.Get(31)) return o->F3f250();
    }
    return 1.0f;
}

// @ 0x0043F5B0
void cSPEditorBlock::F5b0(Vec3* out, float a, float b, float c, int flag)
{
    cSPBoundingBox base = F3eef0();
    if (flag > 0) {
        Vec3 p = base.GetCorner(0);
        if (0.0f > a + p.x) {
            Vec3 q = base.GetCorner(0);
            a = -q.x;
        }
    } else {
        Vec3 p = base.GetCorner(1);
        if (a + p.x >= 0.0f) {
            Vec3 q = base.GetCorner(1);
            a = -q.x;
        }
    }
    out->x = a;
    out->y = b;
    out->z = c;
}

// @ 0x0043FFA0
void cSPEditorBlock::FFa0(Matrix3 m)
{
    F404f0(m);
    if (node != 0 && node->Check() && link3e0 != 0) {
        link3e0->F404f0(Sub_4A8E10(&m, 0));
    }
}

// @ 0x00440020
void cSPEditorBlock::F4020(float v, uint8_t b)
{
    F40420(v, b);
    if (node != 0) {
        if (node->Check() && link3e0 != 0) {
            link3e0->F40420(v, b);
        }
    }
}

// @ 0x00440090
void cSPEditorBlock::F4090(float v, uint8_t b)
{
    F40520(v, b, 0);
    if (node != 0) {
        if (node->Check() && link3e0 != 0) {
            link3e0->F40520(v, b, 0);
        }
    }
}

// @ 0x0043FC20
bool cSPEditorBlock::F3fc20(void* pos)
{
    cSPEditorModel* model = mEditorModel;
    if (model != 0) {
        model->mRef.mnRefCount = model->mRef.mnRefCount + 1;
    }
    uint8_t result = 0;
    bool saved = model ? model->UsingSymmetry() : false;
    if (model != 0) model->SetUsingSymmetry(false);

    bool flag51 = bits.Get(0x33);
    if (!bits.Get(7)) {
        Vec3 local;
        if (pos != 0) {
            local = *(Vec3*)pos;
        } else {
            local = *(Vec3*)((char*)this + 0x48);
        }
        Basis basis;
        int r = ClassifyAgainstSymmetryPlane(&local, model->GetScale(),
                                             model->GetMinHeight(),
                                             model->GetMaxHeight(), &basis);
        uint8_t notThree = (uint8_t)(r != 3);
        if (notThree && !flag51) result = 1;
        if (link33c == 0 && !FUN_0049b340(this)) result = 1;
        if (bits.Get(0x14)) result = 0;
        if (bits.Get(0x2a)) result = 1;
        if (link33c != 0 && link33c->bits.Get(1)) result = 1;
    }

    if (model != 0) model->SetUsingSymmetry(saved);
    bool b = result == 0;
    if (model != 0) {
        model->mRef.Release();
    }
    return b;
}

// @ 0x0043F6B0
void cSPEditorBlock::SetValid(char valid, int arg)
{
    uint8_t wasLinked = bits.Get(1) ? 1 : 0;
    SetFlag(1, valid == 0);
    if (valid != 0) {
        SetUIState(0, true, false, false);
        if (arg != 0 && bits.Get(10)) {
            FUN_004c5030(0xca9bb36f, this);
        }
        SetFlag(0x25, true);
        if (!wasLinked) return;
        if (EditorEffects()->Get(this) != 0) {
            EditorEffects()->Stop(this);
        }
        if (!Paint()) return;

        cSPBoundingBox bbox = GetBBox(0, false, 0);
        Vec3 width = bbox.mMax - bbox.mMin;
        float len = VectorLength(&width);

        XformMsg msg;
        msg.SetRot(mOrientation);
        Vec3 center = bbox.Center();
        msg.SetPos(center);
        msg.SetScale(len);
        GetEditorEffectsWorld()->SetEffectTransform(0xabf6fbdd, 1, &msg, this);
        return;
    }

    SetUIState(1, true, false, true);
    if (arg != 0 && bits.Get(10)) {
        FUN_004c5030(0xf691ee89, this);
    }
    if (!Paint()) return;
    if (!(wasLinked && EditorEffects()->Get(this) != 0)) {
        if (EditorEffects()->Get(this) != 0) {
            EditorEffects()->Stop(this);
        }
        MessageManager()->PostMSG(0x406ed5d0, 1, this, this);
    }

    cSPBoundingBox bbox = GetBBox(0, false, 0);
    Vec3 width = bbox.mMax - bbox.mMin;
    float len = VectorLength(&width);

    XformMsg msg;
    Vec3 center = bbox.Center();
    if (bits.Get(0x2a)) {
        Vector3_Add(&center, &mReplacePartDisplacement);
    }
    msg.SetPos(center);
    msg.SetScale(len);
    EditorEffects()->SetTransform(this, &msg);
}

} // namespace SP
