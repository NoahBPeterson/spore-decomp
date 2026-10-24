// Slice s00b40a20: contact generation between a sphere-like shape A and a shape B (sphere, or a convex polygon hull
// when B's data flag is set). Writes one contact (point on A, point on B, normal, penetration vector) into `out`.
//
//  * early out when the centres are further apart than rA + rB;
//  * for a hull with >= 3 vertices: A's centre is moved into B's local frame, rejected when above the box height,
//    flattened onto the z = 0 plane, and the polygon edge closest to it is found (edge i joins vertex i-1 and i). If the
//    edge is within rA, the normal points from the point to its closest point on that edge (flipped, with penetration
//    set to the edge distance, when the flattened point lies inside the polygon) and is rotated back to world space;
//  * otherwise (sphere, or a degenerate hull) the normal is the centre-to-centre direction.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include <math.h>
#include <float.h>

struct Vec3 { float x, y, z; };

struct BoundingBox
{
	Vec3 min;
	Vec3 max;
	BoundingBox();   // 0x00576b40
};

struct cSPTransform
{
	unsigned short mFlags;
	unsigned short mModificationCount;
	Vec3 mTranslation;
	float mScale;
	float mRotation[9];
	cSPTransform();                          // 0x00409930
	void BackTransformPoint(Vec3* p);        // 0x004ff6d0
	void TransformVector(Vec3* v);           // 0x0049d640
};

struct Hull
{
	char pad0[0x4c];
	Vec3* m_begin;   // +0x4c
	Vec3* m_end;     // +0x50
};

struct GeomData
{
	char pad0[0x71];
	char m_isPolygon;   // +0x71
};

struct Contact
{
	Vec3 m_pointA[16];   // +0x000
	Vec3 m_pointB[16];   // +0x0c0
	int m_count;         // +0x180
	Vec3 m_normal;       // +0x184
	float m_zero;        // +0x190
	Vec3 m_separation;   // +0x194
};

class Geom
{
public:
	void GetCenter(Vec3* out);                    // 0x00b3d9c0
	float GetRadius();                            // 0x00b3d630
	Hull* GetHull();                              // 0x00b3d6a0
	void GetTransform(cSPTransform* out);         // 0x00b3f6c0
	void GetBoundingBox(BoundingBox* out);        // 0x00b3f420

	int m_pad0;
	int m_type;           // +4
	char pad8[0x38];
	GeomData* m_data;     // +0x40
};

float SegmentDistance_00698b30(const Vec3* p, const Vec3* a, const Vec3* b);
void ClosestPointOnSegment_00698e00(Vec3* out, const Vec3* p, const Vec3* a, const Vec3* b);
void NormalizedSafe_00449c20(Vec3* out, const Vec3* in);
char PointInPolygon_0069a050(const Vec3* verts, int count, const Vec3* p);

// @ 0x00b40a20
void CollideSphereShape_00b40a20(Geom* a, Geom* b, Contact* out)
{
	Vec3 ca, cb;
	a->GetCenter(&ca);
	b->GetCenter(&cb);
	float rA = a->GetRadius();
	float rB = b->GetRadius();

	Vec3 d;
	d.x = cb.x - ca.x;
	d.y = cb.y - ca.y;
	d.z = cb.z - ca.z;
	float sum = rB + rA;
	float distSq = (d.x * d.x + d.z * d.z) + d.y * d.y;
	if (!(sum * sum > distSq))
		return;

	Vec3 pt;
	pt.x = d.x;
	pt.y = d.y;
	pt.z = d.z;
	char hullFlag = 1;
	if (b->m_type == 0)
		hullFlag = b->m_data->m_isPolygon;
	else if (b->m_type == 1)
		hullFlag = b->m_data->m_isPolygon;
	bool useHull = hullFlag != 0;

	if (useHull)
	{
		Hull* hull = b->GetHull();
		if (hull && (unsigned)(hull->m_end - hull->m_begin) >= 3)
		{
			cSPTransform t;
			b->GetTransform(&t);
			t.mScale = 1.0f;
			t.mModificationCount++;
			pt.x = ca.x;
			pt.y = ca.y;
			pt.z = ca.z;
			t.BackTransformPoint(&pt);
			float ptz = pt.z;
			{
				BoundingBox box;
				b->GetBoundingBox(&box);
				if (ptz > box.max.z - box.min.z)
					return;
			}

			pt.z = 0.0f;
			Vec3& prev = cb;   // B's centre is dead on this path (every exit below returns)
			prev.x = hull->m_begin[0].x;
			prev.y = hull->m_begin[0].y;
			prev.z = hull->m_begin[0].z;
			int n = hull->m_end - hull->m_begin;
			float best = FLT_MAX;
			int bestIdx = 0;
			for (int i = 1; i < n; i++)
			{
				const Vec3* cur = hull->m_begin + i;
				float dist = SegmentDistance_00698b30(&pt, &prev, cur);
				if (dist < best)
				{
					best = dist;
					bestIdx = i;
				}
				prev = *cur;
			}
			if (bestIdx == 0 || !(rA > best))
				return;

			const Vec3* edgeEnd = hull->m_begin + bestIdx;
			Vec3 closest;
			ClosestPointOnSegment_00698e00(&closest, &pt, edgeEnd - 1, edgeEnd);
			{
				Vec3 diff;
				diff.x = closest.x - pt.x;
				diff.y = closest.y - pt.y;
				diff.z = closest.z - pt.z;
				NormalizedSafe_00449c20(&d, &diff);
			}
			float pen = rA - best;
			if (PointInPolygon_0069a050(hull->m_begin, hull->m_end - hull->m_begin, &pt))
			{
				d.x = d.x * -1.0f;
				d.y = d.y * -1.0f;
				d.z = d.z * -1.0f;
				pen = best;
			}
			t.TransformVector(&d);

			float depth = rA - pen;
			out->m_pointA[0].x = d.x * depth + ca.x;
			out->m_pointA[0].y = d.y * depth + ca.y;
			out->m_pointA[0].z = d.z * depth + ca.z;
			out->m_pointB[0] = out->m_pointA[0];
			out->m_normal = d;
			out->m_count = 1;
			out->m_separation.x = out->m_normal.x * pen;
			out->m_separation.y = out->m_normal.y * pen;
			out->m_separation.z = out->m_normal.z * pen;
			out->m_zero = 0.0f;
			return;
		}
	}

	float dist = (float)sqrt((double)distSq);
	float pen = sum - dist;
	float inv = 1.0f / (dist + 1.5258789e-05f);
	Vec3 n;
	n.y = d.y * inv;
	n.z = d.z * inv;
	n.x = inv * d.x;
	float depthA = rA - pen;
	out->m_pointA[0].x = n.x * depthA + ca.x;
	out->m_pointA[0].y = n.y * depthA + ca.y;
	out->m_pointA[0].z = n.z * depthA + ca.z;
	float depthB = rB - pen;
	out->m_pointB[0].x = cb.x - n.x * depthB;
	out->m_pointB[0].y = cb.y - n.y * depthB;
	out->m_pointB[0].z = cb.z - n.z * depthB;
	out->m_normal = n;
	out->m_count = 1;
	out->m_separation.x = out->m_normal.x * pen;
	out->m_separation.y = out->m_normal.y * pen;
	out->m_separation.z = out->m_normal.z * pen;
	out->m_zero = 0.0f;
}

// ---------------------------------------------------------------------------
// Tuning-property loaders.
//   0x00B41020  refresh the global tuning floats from the "gold" property list.
//   0x00B41390  CapsuleShape::LoadSphereTuning -- planet tuning (0x00b51460) + capsule constants
//               (0x00b4d930) then a batch of property reads into the shared tuning block and globals.
// Neither emits an SEH frame, so these two rows compile without /EHsc:
//   Flags: /O2 /MD /Gy /GS- /TP /arch:SSE.
// ---------------------------------------------------------------------------

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

extern bool  g_defaultBool;    // 0x015d9c70
extern int   g_defaultInt;     // 0x015d9c68
extern float g_defaultFloat;   // 0x015d9c6c

struct Property                        // EA::Property entry (flags +0x10, type +0x12)
{
	void* data;             // +0
	uint32 pad[3];
	uint16 flags;           // +0x10
	uint16 type;            // +0x12
	// Type-mismatch fallbacks live in the shared default globals above.
	void* GetStorage() { if (flags & 0x30) { return data; } else if (type) return this; return 0; }
	bool*  GetBool()  { if (type == 1  || type == 0x10) return (bool*)GetStorage();  return &g_defaultBool; }
	int*   GetInt()   { if (type == 9  || type == 0x10) return (int*)GetStorage();   return &g_defaultInt; }
	float* GetFloat() { if (type == 13 || type == 0x10) return (float*)GetStorage(); return &g_defaultFloat; }
};

struct IPropertyList                   // vt[1] = Release, vt[0x24] = GetProperty
{
	virtual void v0();          // +0
	virtual void Release();     // +4
	virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
	virtual void v6(); virtual void v7(); virtual void v8();
	virtual bool GetProperty(uint32 key, Property** out);   // +0x24
};

struct IPropertyManager                // vt[0x30] = GetPropertyList
{
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual bool GetPropertyList(uint32 key, IPropertyList** out);   // +0x30
};
IPropertyManager* PropertyManager();   // 0x0067de30

struct PropListPtr                    // AutoRefCount<IPropertyList>
{
	IPropertyList* mp;
	IPropertyList** AsOutParam() { if (mp) { IPropertyList* o = mp; mp = 0; o->Release(); } return &mp; }
	~PropListPtr() { if (mp) mp->Release(); }
};

extern float g_156964c, g_1569650, g_1569654, g_156965c, g_15695f0, g_15695f4,
	g_1569678, g_1569680, g_1569684, g_1569688, g_156968c, g_1569690, g_1569694;

// @ 0x00b41020
void FUN_00b41020()
{
	PropListPtr bag;
	bag.mp = 0;
	if (PropertyManager()->GetPropertyList(0x93e8e9b7, bag.AsOutParam()))
	{
#define READPROP(key, dst) \
	if (!bag.mp) return; \
	{ Property* p; if (bag.mp->GetProperty(key, &p) && p->type == 13) dst = *p->GetFloat(); }
	READPROP(0x319c4a93u, g_156964c)
	READPROP(0x119c4ad5u, g_1569650)
	READPROP(0x519c4ad7u, g_1569654)
	READPROP(0x519c4ad9u, g_156965c)
	READPROP(0xd19da711u, g_15695f0)
	READPROP(0x31b02eeau, g_15695f4)
	READPROP(0xd1b02eecu, g_1569678)
	READPROP(0x51d13278u, g_1569680)
	READPROP(0x31d2512fu, g_1569684)
	READPROP(0x11d27e35u, g_1569688)
	READPROP(0x11d39e51u, g_156968c)
	READPROP(0x11d3a085u, g_1569690)
	READPROP(0xb1d3a61bu, g_1569694)
#undef READPROP
	}
}

// Sphere tuning block reachable through the pointer at 0x0167eb70 (fields +0xa8..+0xb8).
struct SphereTuning { uint8 pad0[0xa8]; float fA8; float fAC; float fB0; float fB4; int iB8; };
extern SphereTuning* g_pTuning;            // 0x0167eb70

extern float g_hkRealOne;                  // 0x01485720
extern float g_013eb960;                   // 0x013eb960
extern float g_01470f1c;                   // 0x01470f1c
extern float g_013ec4d0;                   // 0x013ec4d0
extern float g_013f1cac;                   // 0x013f1cac
extern float g_f167eb78, g_f167eb7c, g_f167eb80, g_f167eb84;   // 0x0167eb78..
extern float g_f15695fc, g_f15695f8, g_f1569648;               // 0x015695f8..

void LoadPlanetTuning(IPropertyList* list);   // 0x00b51460

struct CapsuleShape
{
	uint8 pad0[0x31];
	bool  m_b31;                  // +0x31
	bool  m_b32;                  // +0x32
	void CapsuleConstant();                          // 0x00b4d930
	void LoadSphereTuning(IPropertyList* list);      // 0x00b41390
};

// @ 0x00b41390
void CapsuleShape::LoadSphereTuning(IPropertyList* list)
{
	LoadPlanetTuning(list);
	CapsuleConstant();
	Property* p;
	m_b31 = (list && list->GetProperty(0x21859677u, &p)) ? *p->GetBool() : false;
	m_b32 = 1;
	g_pTuning->fA8 = (list && list->GetProperty(0xc03f2383u, &p)) ? *p->GetFloat() : g_hkRealOne;
	g_pTuning->fAC = (list && list->GetProperty(0xa098ae0au, &p)) ? *p->GetFloat() : g_013eb960;
	g_pTuning->fB0 = (list && list->GetProperty(0xfb8c381cu, &p)) ? *p->GetFloat() : 0.0f;
	g_pTuning->iB8 = (list && list->GetProperty(0x96b2b086u, &p)) ? *p->GetInt() : 10;
	g_pTuning->fB4 = (list && list->GetProperty(0x182b28dau, &p)) ? *p->GetFloat() : g_01470f1c;
	g_f15695fc = (list && list->GetProperty(0x45b2dc22u, &p)) ? *p->GetFloat() : g_013ec4d0;
	g_f167eb78 = (list && list->GetProperty(0x85a22616u, &p)) ? *p->GetFloat() : 0.0f;
	g_f15695f8 = (list && list->GetProperty(0xb06ebb0eu, &p)) ? *p->GetFloat() : 0.0f;
	g_f167eb7c = (list && list->GetProperty(0x1cd0a1fu, &p)) ? *p->GetFloat() : g_hkRealOne;
	g_f167eb80 = (list && list->GetProperty(0xd087a9d6u, &p)) ? *p->GetFloat() : g_hkRealOne;
	g_f167eb84 = (list && list->GetProperty(0xaf48a431u, &p)) ? *p->GetFloat() : g_hkRealOne;
	g_f1569648 = (list && list->GetProperty(0x617d0eeau, &p)) ? *p->GetFloat() : g_013f1cac;
}
