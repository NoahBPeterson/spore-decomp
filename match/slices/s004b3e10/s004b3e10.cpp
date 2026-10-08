// Slice s004b3e10: two large cSPEditorPaintTheme bodies — GenerateSkinPaintFromRegionPaint and
// ReadSkinThemeFromProp. Unoptimized editor module: /Od /Ob1 /arch:SSE /GS- /fp:fast (no /EHsc).
//
// These are the heaviest functions of the subsystem (property maps, RandomLinearCongruential,
// EASTL vectors of map entries and skin-paint generation).  Behavior is summarized here; the
// complete inlined EASTL/RNG schedule is not reproduced (see partial.txt).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Vec3R : Vec3 {};
Vec3R operator-(const Vec3& a, const Vec3& b);               // 0x0041db10
float VectorLength(const Vec3& v);                           // 0x0040ae50 (cdecl, by address)
struct rwVec3 {
    float x, y, z;
    rwVec3() {}
    rwVec3(const rwVec3& v);                                 // 0x004098a0
};
struct BBox { rwVec3 mn, mx; };
struct rwVec3R : rwVec3 { };
rwVec3R operator-(const rwVec3& a, const rwVec3& b);         // 0x0041db10

struct EntryRec { uint32_t id; Vec3 a; Vec3 b; };
struct Entry { uint32_t inst; EntryRec rec; };
struct EntryVec { Entry* mpBegin; Entry* mpEnd; };
struct cSPEditorBlock {
    char pad[0x4c8];
    EntryVec mEntries;                                       // +0x4c8
    void GetBBox(BBox* out, int a, int b, int c);            // 0x44ae00
};
struct cSPEditorModel {
    cSPEditorBlock* GetBlock(int i);                         // 0x4accb0
    uint32_t GetBlockCount();                                // 0x4accf0
};
struct PropObj2 { virtual void v0(); virtual void Release(); };
struct PropRef {
    PropObj2* mp;
    PropRef() : mp(0) {}
    ~PropRef() { if (mp) mp->Release(); }
    PropObj2** operator&() { if (mp) { PropObj2* t = mp; mp = 0; t->Release(); } return &mp; }
};
struct PropMgr2 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool GetPropertyList(uint32_t id, uint32_t type, PropObj2** out);
};
PropMgr2* SP_PropertyManager2();                             // 0x67de30
extern uint32_t gPropListType;                               // 0x15d6cc8
void GetFloatProperty(PropObj2* list, uint32_t id, float* out);   // 0x40cf10

struct TreeNode { char hdr[0x10]; };
struct TreePair { Vec3 first; float second; };
struct TreeIter {
    TreeNode* mpNode;
    TreeIter(TreeNode* n);                                   // 0x566c50
    TreePair* operator->();                                  // 0x564f50 (returns &value)
    TreeIter& operator++();                                  // 0x422c50
};
inline bool operator!=(const TreeIter& a, const TreeIter& b) { return a.mpNode != b.mpNode; }
struct AllocTag { AllocTag() {} };
struct ColorAreaMap {
    typedef TreeIter iterator;
    uint32_t cmp;
    TreeNode* mpRight;
    TreeNode* mpLeft;
    TreeNode* mpParent;
    uint32_t mColor;
    uint32_t mnSize;
    uint32_t mPad;
    ColorAreaMap(const AllocTag& a = AllocTag());            // 0x4b5980
    ~ColorAreaMap() { DoNuke(mpParent); }
    void DoNuke(TreeNode* n);                                // 0x4e8a30
    iterator begin() { return iterator(mpLeft); }
    iterator end() { return iterator((TreeNode*)&mpRight); }
    iterator find(const Vec3& k);                            // 0x4b5210
    float& operator[](const Vec3& k);                        // 0x4b5370
};
struct PropObj;
struct PropMgr;

struct PropObj {
    virtual void v0(); virtual void Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual char Has(uint32_t id);
    virtual void v8(); virtual void v9();
    virtual void* Get(uint32_t id);
};
struct PropMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool GetPropertyList(int id, uint32_t type, void** out);
};

extern "C" {
    void* SP_PropertyManager();
    void  FUN_004b5980(void* tag);
    int   FUN_004accf0();
    void* FUN_004accb0(int i);
    void  FUN_004098a0(void* dst, const void* src);
    char  FUN_0041db10(void* a, void* b, void* c);
    float FUN_0040ae50(void* v);
    void  FUN_00422c50();
    int   FUN_00564f50();
    void  FUN_004e8a30(void* a);
    void* FUN_004bbed0(void* a);
    void* cSPUIAssetView_InitVerbCollection(void* a);
    char  ExtractSkinPaintData(void* a);
    int   FUN_004b2800(void* self, void* a);
    int   FUN_004b3e10_GetPropertyT(PropObj* list, uint32_t id, void* out);
    void  FUN_00540470(void* a);
    void  FUN_00540520(void);
    void  FUN_005156b0(void);
    void  FUN_004b3e10(int self);
}

namespace SP {
class cSPEditorPaintTheme {
public:
    void* pad[0x150 / 4];
    void* mpClosestBegin;   // +0x150
    void* mpClosestEnd;     // +0x154
    void* mpClosestCap;     // +0x158
    char  pad_15c[8];
    uint32_t mSkinEffects[3];    // +0x164
    uint32_t mSkinEffectSeeds[3];// +0x170
    Vec3 mSkinColors[3];         // +0x17c
    void __thiscall GenerateSkinPaint(cSPEditorModel* model);
    unsigned char __thiscall ReadSkinTheme(int a, int b, int c);
};
}
using namespace SP;

// @ 0x4b3e10  GenerateSkinPaintFromRegionPaint
void cSPEditorPaintTheme::GenerateSkinPaint(cSPEditorModel* model)
{
    const uint32_t n1 = 0x25e49bb;
    const uint32_t m = 0x265fb07;
    ColorAreaMap t25;
    uint32_t v14 = model->GetBlockCount();
    for (uint32_t i = 0; i < v14; i++) {
        cSPEditorBlock* n35 = model->GetBlock(i);
        const EntryVec& p15 = n35->mEntries;
        const Entry* v18 = p15.mpBegin;
        const Entry* p12 = p15.mpEnd;
        while (v18 != p12) {
            const EntryRec* t38 = &v18->rec;
            uint32_t n12 = v18->inst;
            PropRef n21;
            if (SP_PropertyManager2()->GetPropertyList(t38->id, gPropListType, &n21)) {
                float v4 = 0.0f;
                float size = 0.0f;
                GetFloatProperty(n21.mp, n1, &v4);
                GetFloatProperty(n21.mp, m, &size);
                BBox data;
                n35->GetBBox(&data, 1, 0, 0);
                ScratchSlots<6>();
                rwVec3 left = data.mx - data.mn;
                float t34 = (left.x * left.y + left.y * left.z + left.x * left.z) * 2.0f;
                float t20 = t34;
                if (v4 > 0.0f) {
                    Vec3 k(t38->a);
                    if (t25.find(k) != t25.end())
                        t25[k] += t20;
                    else
                        t25[k] = t20;
                }
                if (size > 0.0f) {
                    ScratchSlots<20>();
                    Vec3 k(t38->b);
                    if (t25.find(k) != t25.end())
                        t25[k] += t20;
                    else
                        t25[k] = t20;
                }
            }
            v18++;
        }
    }
    float t14 = 0.3f;
    for (int i = 0; i < 3; i++) {
        float p5 = 0.0f;
        bool v1 = false;
        ColorAreaMap::iterator p27 = t25.begin();
        ColorAreaMap::iterator pNode = t25.end();
        while (p27 != pNode) {
            float count = p27->second;
            if (count > p5) {
                ScratchSlots<20>();
                Vec3 cap(p27->first);
                bool p24 = false;
                for (int j = i - 1; j >= 0; j--) {
                    Vec3 elem(mSkinColors[j]);
                    Vec3 h = elem - cap;
                    float p33 = VectorLength(h);
                    if (t14 > p33) {
                        p24 = true;
                        break;
                    }
                }
                if (!p24) {
                    p5 = count;
                    mSkinColors[i] = cap;
                    v1 = true;
                }
            }
            ++p27;
        }
        if (!v1) {
            t14 -= 0.1f;
            i--;
        }
    }
}

// @ 0x4b4470  ReadSkinThemeFromProp
unsigned char __thiscall cSPEditorPaintTheme::ReadSkinTheme(int prop, int a, int b)
{
    void* view = cSPUIAssetView_InitVerbCollection(*(void**)(prop + 0x58));
    if (!ExtractSkinPaintData(view)) {
        if (!FUN_004bbed0(view))
            return 0;
        FUN_004b3e10((int)this);
        return 1;
    }
    (void)a; (void)b;
    return FUN_004b2800(this, (void*)prop) ? 1 : 0;
}
