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
