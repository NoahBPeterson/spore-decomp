// src/game/Swarm/GameEffect.cpp -- migrated from slice(s) s00a978d0, s004ad550 by tools/migrate/rewrite.py
// Object file: Swarm/GameEffect.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPBoundingBox.h"
#include "cSPColorRGB.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorModel.h"
#include "SP/cSPEditorPhysicsWorld.h"
#include "cSPMatrix3.h"
#include "cSPTransform.h"
#include "cSPVector3.h"

// ---- items of slice s004ad550 begin (TODO(rewrite): local stubs, replace by canonical classes)
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct Vector3T {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T {                              // rw::math::fpu::Matrix33Template<float,0>
    Vector3T xAxis, yAxis, zAxis;
};
struct cSPMatrix3_s004a_d550 : Matrix33T {};
struct cSPVector3_s004a_d550 : Vector3T {
    cSPVector3_s004a_d550() {}
    cSPVector3_s004a_d550(const Vector3T& v) : Vector3T(v) {}
};
Vector3T& operator*=(Vector3T& v, const float& s);           // 0x41dba0
struct cSPTransform_s004a_d550 {
    uint16_t mFlags;
    uint16_t mModificationCount;
    cSPVector3_s004a_d550 mTranslation;
    float mScale;
    cSPMatrix3_s004a_d550 mRotation;
    cSPTransform_s004a_d550();                                          // 0x409930
    void SetTranslation(const cSPVector3_s004a_d550& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
    void SetRotation(const cSPMatrix3_s004a_d550& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
};
struct cSPBoundingBox_s004a_d550 {
    cSPVector3_s004a_d550 mMin, mMax;
    cSPBoundingBox_s004a_d550& operator=(const cSPBoundingBox_s004a_d550& b) { mMax = b.mMax; mMin = b.mMin; return *this; }
    cSPBoundingBox_s004a_d550();                                        // 0x409c00 (folded with Reset)
    cSPBoundingBox_s004a_d550(const cSPBoundingBox_s004a_d550& b);                 // 0x511140
    void Reset();                                            // 0x409c00
    void Add(const cSPBoundingBox_s004a_d550& b);                       // 0x43f050
    void Transform(const cSPTransform_s004a_d550& t);                   // 0x409dd0
};
struct cSPColorRGB_s004a_d550 {
    float r, g, b;
    cSPColorRGB_s004a_d550(const cSPColorRGB_s004a_d550& c) : r(c.r), g(c.g), b(c.b) {}
};
template<class T> struct AutoRefCount {
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
template<class T> struct AutoRefCountP {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
    AutoRefCountP& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        ScratchSlots<3>();
        return *this;
    }
};
struct false_type { false_type() {} };
struct input_iterator_tag { input_iterator_tag() {} };
struct forward_iterator_tag : input_iterator_tag { forward_iterator_tag() {} };
struct bidirectional_iterator_tag : forward_iterator_tag { bidirectional_iterator_tag() {} };
struct random_access_iterator_tag : bidirectional_iterator_tag { random_access_iterator_tag() {} };
template<class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    T* begin() const { return mpBegin; }
    T* end() const { return mpEnd; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t n) { return mpBegin[n]; }
    bool empty() const;                                      // 0x526430
    void DoAssignFromIterator(T* first, T* last, input_iterator_tag);  // 0x4b1cc0
    // __forceinline: plain inline is declined by /Ob1 inside GetBlockBoundingBoxes
    __forceinline void DoAssign(T* first, T* last, const false_type&) { DoAssignFromIterator(first, last, random_access_iterator_tag()); }
    void assign(T* first, T* last) { DoAssign(first, last, false_type()); }
    void resize(uint32_t n);                                 // 0x4aff80
};
template<int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) {
            uint32_t word = mWord[i >> 5];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};
struct wstring {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    wchar_t* begin() { return mpBegin; }
    wchar_t* end() { return mpEnd; }
    const wchar_t* c_str() const { return mpBegin; }
    static uint32_t CharStrlen(const wchar_t* p) { const wchar_t* pCurrent = p; while (*pCurrent) ++pCurrent; return (uint32_t)(pCurrent - p); }
    wstring& assign(const wchar_t* first, const wchar_t* last);   // 0x423650
    wstring& assign(const wchar_t* p) { return assign(p, p + CharStrlen(p)); }
};
namespace SP {
struct cSPEditorModel_s004a_d550;
}
namespace SP {
struct cSPEditorBlock_s004a_d550 {
    virtual void _v0();
    virtual int Release();
    char pad0[0x48 - 4];
    cSPVector3_s004a_d550 mPosition;                       // +0x48
    char pad1[0x60 - 0x54];
    cSPMatrix3_s004a_d550 mOrientation;                    // +0x60
    char pad2[0x1d8 - 0x84];
    float mUniformScale;                        // +0x1d8
    char pad3[0x33c - 0x1dc];
    AutoRefCount<cSPEditorBlock_s004a_d550> mParentBlock;  // +0x33c
    char pad4[0xdc8 - 0x340];
    bitset<60> mFlags;                          // +0xdc8

    float GetUniformScale() const { return mUniformScale; }
    cSPBoundingBox_s004a_d550 GetBBox(int a, int b, int c);             // 0x44ae00
    bool IsSelectable();                                     // 0x435d40
    void ClearHighlight();                                   // 0x437890
    void SetHighlight(int state, int flags);                 // 0x437a60
    Vector3T GetSnapNormal(bool world);                      // 0x4381e0
    Vector3T GetSnapPosition(bool world);                    // 0x438120
    bool Snap(Vector3T position, Vector3T normal);           // 0x437b00
    bool Load(void* source, int group, float bounds, bool a, bool b);   // 0x450f70
};
}
namespace SP {
struct cSPEditorPhysicsWorld_s004a_d550 {
    virtual void _v0();
    int mRefCount;                              // +0x04
    int AddRef() { return mRefCount++ + 1; }
    int Release();                                           // 0x453540
    int GetGroup();                                          // 0x4b91c0
    void AttachModel(cSPEditorModel_s004a_d550* model);                 // 0x4b94a0
};
}
namespace SP {
struct cSPEditorModel_s004a_d550 {
    virtual void SetName(const wchar_t* name);               // 0x00
    virtual void _v1();
    virtual void SetDescription(const wchar_t* desc);        // 0x08
    char pad0[0x18 - 4];
    vector<AutoRefCount<cSPEditorBlock_s004a_d550> > mBlockList;        // +0x18
    bool mbAllBlocksLoaded;                     // +0x2c
    AutoRefCountP<cSPEditorPhysicsWorld_s004a_d550> mPhysicsWorld;      // +0x30
    char pad1[0x38 - 0x34];
    float mBounds;                              // +0x38
    char pad2[0x5c - 0x3c];
    wstring mName;                              // +0x5c
    wstring mDescription;                       // +0x6c
    wstring mCleanName;                         // +0x7c
    uint32_t mSkinEffects[3];                   // +0x8c
    uint32_t mSkinEffectSeeds[3];               // +0x98
    cSPColorRGB_s004a_d550 mSkinColors[3];                 // +0xa4
    vector<cSPBoundingBox_s004a_d550> mBBoxesOverride;     // +0xc8

    cSPBoundingBox_s004a_d550 GetBoundingBox(bool selectableOnly);
    void GetBlockBoundingBoxes(vector<cSPBoundingBox_s004a_d550>& boxes);
    void SetBBoxesOverride(const vector<cSPBoundingBox_s004a_d550>& boxes);
    uint32_t GetSkinEffect(int i);
    uint32_t GetSkinEffectSeed(int i);
    cSPColorRGB_s004a_d550 GetSkinColor(int i);
    void SetSkinEffect(int i, uint32_t effect);
    void SetSkinEffectSeed(int i, uint32_t seed);
    void SetSkinColor(int i, cSPColorRGB_s004a_d550 color);
    cSPEditorBlock_s004a_d550* GetBlock(uint32_t index);                // 0x4accb0
    int GetBlockCount();                                     // 0x4accf0
    void ClearHighlights();
    void SetHighlights(int state);
    bool SnapBlocks();
    void Update();
    bool LoadBlocks(void* source, cSPEditorPhysicsWorld_s004a_d550* world, bool a, bool b);
};
}
// ---- items of slice s004ad550 end

// ---- items of slice s00a978d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* EA_Messaging_GetServer();                                    // (0x883860)
extern void Matrix3_Assign();                                             // (0x41cb40)
extern void cTransform_PreTransformBy();                                  // (0x537f40)
extern void cSPTransformOps_Assign();                                     // (0x537dc0)
extern float   g_realZero;            // (0x1485378)
extern float   g_realOne;             // (0x1485720)
extern char    g_mat1678b78[];        // (0x1678b78) identity Matrix3
extern char vtable_Eff0[];            // (0x1458788)
extern char vtable_Eff1[];            // (0x14599e8)
extern char vtable_IEvent[];          // (0x13ef094) SP::Audio::IEventModifier
typedef unsigned short u16;
typedef unsigned char  u8;
typedef unsigned int   u32;
struct Vector3_t { float x, y, z; };   // 0xc
struct Matrix3   { float m[9]; };      // 0x24
extern Vector3_t g_vec1678ad0;        // (0x1678ad0)
struct cSPTransform_s00a9_78d0                    // 0x38 bytes
{
	u16     mFlags;                    // +0x00
	u16     mModCount;                 // +0x02
	float   mOffsetX;                  // +0x04
	float   mOffsetY;                  // +0x08
	float   mOffsetZ;                  // +0x0c
	float   mScale;                    // +0x10
	Matrix3 mRotation;                 // +0x14
};
struct cGameDescription
{
	char  pad00[8];                    // +0x00
	u32   mFlags;                      // +0x08
	u32   mMessageID;                  // +0x0c
	u32   mData1;                      // +0x10
	u32   mData2;                      // +0x14
	u32   mData3;                      // +0x18
	u32   mData4;                      // +0x1c
	const void* mString;               // +0x20
	char  pad24[0x0c];                 // +0x24
	float mLife;                       // +0x30
};
namespace EA {
namespace Swarm {
struct IUnknown32;
}
}
namespace EA {
namespace Swarm {
struct cGameEffect                     // layout from the (0x00a98340) constructor
{
	void*  mpVtbl0;                    // +0x00  (0x1458788)
	void*  mpVtbl1;                    // +0x04  (0x14599e8)
	u32    mn08;                       // +0x08
	cGameDescription* mpDesc;          // +0x0c
	u8     mActive;                    // +0x10
	char   pad11[3];                   // +0x11
	float  mAge;                       // +0x14
	cSPTransform_s00a9_78d0 mTransform;           // +0x18
	IUnknown32*  mOwner;               // +0x50

	char SetUnknownParam(int which, IUnknown32* value);   // (0xa98030)
	void ApplyEffect(float dt, int, int);                 // (0xa98050)
	void Init(int, int, void* owner);                     // (0xa98090)
	void Start(int);                                      // (0xa980b0)
	void Stop(int);                                       // (0xa98200)
	void SetTransform(void* xform, const cSPTransform_s00a9_78d0* src);  // (0xa98400)
	cGameEffect* Construct(cGameDescription* desc);       // (0xa98340)
};
}
}
namespace EA {
namespace Swarm {
struct InitSource
{
	char pad00[0xb8];                  // +0x00
	IUnknown32* mpOwner;               // +0xb8
};
}
}
using EA::Swarm::cGameEffect;
using EA::Swarm::IUnknown32;
struct EffectMsg
{
	u32 mData1;                        // +0x00
	u32 mPad04;                        // +0x04
	u32 mData2;                        // +0x08
	u32 mPad0c;                        // +0x0c
	u32 mData3;                        // +0x10
	u32 mPad14;                        // +0x14
	u32 mData4;                        // +0x18
	u32 mPad1c;                        // +0x1c
	const void* mString;               // +0x20
	u32 mPad24;                        // +0x24
	void* mTransform;                  // +0x28
	u32 mPad2c;                        // +0x2c
	void* mOwner;                      // +0x30
	u32 mPad34;                        // +0x34
	u32 mType;                         // +0x38
	u32 mPad3c;                        // +0x3c
};
// ---- items of slice s00a978d0 end

// @ 0x004ae250
namespace SP {
void cSPEditorModel_s004a_d550::Update()
{
}
}  // namespace SP

// @ 0x00a98030
char EA::Swarm::cGameEffect::SetUnknownParam(int which, IUnknown32* value)
{
	char result = 1;
	if (which == 1)
		mOwner = value;
	else
		result = 0;
	return result;
}

// @ 0x00a98050
void EA::Swarm::cGameEffect::ApplyEffect(float dt, int, int)
{
	mAge = dt + mAge;
	float life = mpDesc->mLife;
	if (life > g_realZero && mAge > life)
		(*(void(__thiscall**)(void*, int))(*(char**)this + 0x0c))(this, 0);
}

// @ 0x00a98090
void EA::Swarm::cGameEffect::Init(int, int, void* owner)
{
	if (owner != 0)
		mOwner = ((InitSource*)owner)->mpOwner;
}

// @ 0x00a980b0
void EA::Swarm::cGameEffect::Start(int)
{
	if (mActive != 0)
		return;

	mActive = 1;
	mAge = 0.0f;

	void* server = EA_Messaging_GetServer();
	if (server == 0)
		return;

	cGameDescription* desc = mpDesc;

	if (((desc->mFlags >> 3) & 1) != 0) {
		EffectMsg msg;
		msg.mType = 0;
		if (((desc->mFlags >> 5) & 1) != 0)
			msg.mData1 = desc->mData1;
		if (((desc->mFlags >> 6) & 1) != 0)
			msg.mData2 = desc->mData2;
		if (((desc->mFlags >> 7) & 1) != 0)
			msg.mData3 = desc->mData3;
		if (((desc->mFlags >> 8) & 1) != 0)
			msg.mData4 = desc->mData4;
		if (((desc->mFlags >> 9) & 1) != 0)
			msg.mString = desc->mString;
		msg.mOwner = mOwner;
		msg.mTransform = &mTransform;
		(*(void(__thiscall**)(void*, u32, EffectMsg*, int))(*(char**)server + 0x14))(server, desc->mMessageID, &msg, 0);
	}

	cGameDescription* desc0 = mpDesc;
	if ((desc0->mFlags & 1) != 0) {
		EffectMsg msg;
		msg.mData1 = 0;
		msg.mData2 = 0;
		(*(void(__thiscall**)(void*, u32, EffectMsg*, int))(*(char**)server + 0x14))(server, 0x0e7a8471, &msg, 0);
	}

	cGameDescription* desc1 = mpDesc;
	if (((desc1->mFlags >> 1) & 1) != 0) {
		EffectMsg msg;
		msg.mData1 = 1;
		msg.mData2 = 0;
		(*(void(__thiscall**)(void*, u32, EffectMsg*, int))(*(char**)server + 0x14))(server, 0x0e7a8471, &msg, 0);
	}

	cGameDescription* desc2 = mpDesc;
	if (((desc2->mFlags >> 2) & 1) != 0) {
		EffectMsg msg;
		msg.mData1 = 2;
		msg.mData2 = 0;
		(*(void(__thiscall**)(void*, u32, EffectMsg*, int))(*(char**)server + 0x14))(server, 0x0e7a8473, &msg, 0);
	}
}

// @ 0x00a98200
void EA::Swarm::cGameEffect::Stop(int)
{
	if (mActive == 0)
		return;

	mActive = 0;

	void* server = EA_Messaging_GetServer();
	if (server == 0)
		return;

	cGameDescription* desc = mpDesc;

	if ((desc->mFlags & 1) != 0) {
		EffectMsg msg;
		msg.mData1 = 0;
		msg.mData2 = 0;
		(*(void(__thiscall**)(void*, u32, EffectMsg*, int))(*(char**)server + 0x14))(server, 0x0e7a8472, &msg, 0);
	}

	cGameDescription* desc1 = mpDesc;
	if (((desc1->mFlags >> 1) & 1) != 0) {
		EffectMsg msg;
		msg.mData1 = 1;
		msg.mData2 = 0;
		(*(void(__thiscall**)(void*, u32, EffectMsg*, int))(*(char**)server + 0x14))(server, 0x0e7a8472, &msg, 0);
	}

	cGameDescription* desc2 = mpDesc;
	if (((desc2->mFlags >> 2) & 1) != 0) {
		EffectMsg msg;
		msg.mData1 = 0;
		msg.mData2 = 0;
		(*(void(__thiscall**)(void*, u32, EffectMsg*, int))(*(char**)server + 0x14))(server, 0x0e7a8474, &msg, 0);
	}

	cGameDescription* desc3 = mpDesc;
	if (((desc3->mFlags >> 4) & 1) != 0) {
		EffectMsg msg;
		msg.mType = 0;
		if (((desc3->mFlags >> 5) & 1) != 0)
			msg.mData1 = desc3->mData1;
		if (((desc3->mFlags >> 6) & 1) != 0)
			msg.mData2 = desc3->mData2;
		if (((desc3->mFlags >> 7) & 1) != 0)
			msg.mData3 = desc3->mData3;
		if (((desc3->mFlags >> 8) & 1) != 0)
			msg.mData4 = desc3->mData4;
		if (((desc3->mFlags >> 9) & 1) != 0)
			msg.mString = desc3->mString;
		msg.mOwner = mOwner;
		msg.mTransform = &mTransform;
		(*(void(__thiscall**)(void*, u32, EffectMsg*, int))(*(char**)server + 0x14))(server, desc3->mMessageID, &msg, 0);
	}
}

// @ 0x00a98340
EA::Swarm::cGameEffect* EA::Swarm::cGameEffect::Construct(cGameDescription* desc)
{
	*(volatile void**)&mpVtbl1 = (void*)vtable_IEvent;
	mn08 = 0;
	mAge = 0.0f;
	mpVtbl0 = (void*)vtable_Eff0;
	mpVtbl1 = (void*)vtable_Eff1;
	mpDesc = desc;
	mActive = 0;
	mTransform.mFlags = 0;
	mTransform.mModCount = 0;
	mTransform.mOffsetX = g_vec1678ad0.x;
	mTransform.mOffsetY = g_vec1678ad0.y;
	mTransform.mOffsetZ = g_vec1678ad0.z;
	mTransform.mScale = g_realOne;
	((void(__thiscall*)(void*, const void*))Matrix3_Assign)(&mTransform.mRotation, g_mat1678b78);
	mOwner = 0;
	return this;
}

// @ 0x00a98400
void EA::Swarm::cGameEffect::SetTransform(void* xform, const cSPTransform_s00a9_78d0* src)
{
	cSPTransform_s00a9_78d0 tmp;
	tmp.mFlags = src->mFlags;
	tmp.mModCount = src->mModCount;
	tmp.mOffsetX = src->mOffsetX;
	tmp.mOffsetY = src->mOffsetY;
	tmp.mOffsetZ = src->mOffsetZ;
	tmp.mScale = src->mScale;
	((void(__thiscall*)(void*, const void*))Matrix3_Assign)(&tmp.mRotation, &src->mRotation);
	((void(__thiscall*)(void*, void*))cTransform_PreTransformBy)(&tmp, xform);
	((void(__thiscall*)(void*, const void*))cSPTransformOps_Assign)(&mTransform, &tmp);
}
