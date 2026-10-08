// Slice s00a03da0: debug-draw of a rigid body's collision boxes (00a03f50).
//
// For a body object (position at +0x18, quaternion at +0x3c..+0x48, scale at +0x70, and a vector of 700-byte
// shape entries at +0x2e4/+0x2e8) this computes the body's rotation matrix, hands it to the debug-draw state setter
// (0x00a03da0), then locks a vertex buffer for 24 vertices per entry and fills it with box geometry
// (BuildBoxVertices, 0x00a02da0, 0x360 bytes per box). If the single bulk lock fails, every entry is locked,
// built and committed on its own. The first entry is drawn with param 4's colour, the others with param 3's.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (same module as 0x00a02da0).
#include "types.h"

struct DebugShape
{
	char pad0[0x138];
	float m_offset[3];   // +0x138
};

struct DebugEntry   // 700 bytes
{
	DebugShape* m_shape;   // +0x00
	char pad04[0x0c];
	float m_pos[3];        // +0x10
	float m_qw;            // +0x1c
	float m_qx;            // +0x20
	float m_qy;            // +0x24
	float m_qz;            // +0x28
	char pad2c[700 - 0x2c];
};

struct DebugBody
{
	char pad00[0x18];
	float m_pos[3];        // +0x18
	char pad24[0x3c - 0x24];
	float m_qw;            // +0x3c
	float m_qx;            // +0x40
	float m_qy;            // +0x44
	float m_qz;            // +0x48
	char pad4c[0x70 - 0x4c];
	float m_scale;         // +0x70
	char pad74[0x2e4 - 0x74];
	DebugEntry* m_begin;   // +0x2e4
	DebugEntry* m_end;     // +0x2e8
};

struct DebugTarget
{
	char pad0[4];
	void* m_field4;
};

// 0x00a03da0: stores the transform used by the draw state (cdecl)
void SetDebugTransform_00a03da0(DebugTarget* target, const float* matrix3x3, const float* pos, float scale);
// 0x006ddcc0 / 0x006ddd40: lock and unlock a vertex range (cdecl)
bool LockVertices_006ddcc0(int kind, int count, void** outPtr, void* aux);
void UnlockVertices_006ddd40(int kind, DebugTarget* target, int arg);
// 0x00a02da0: writes 24 vertices (0x360 bytes) of one box
void BuildBoxVertices_00a02da0(void* out, const float* matrix, const float* pos, const float* negOffset,
                               const float* extents, uint32_t color);

static __forceinline void QuatToMatrix(float* m, float w, float x, float y, float z)
{
	m[0] = 1.0f - (y * y + x * x) * 2.0f;
	m[1] = (x * w - z * y) * 2.0f;
	m[2] = (z * x + y * w) * 2.0f;
	m[3] = (z * y + x * w) * 2.0f;
	m[4] = 1.0f - (y * y + w * w) * 2.0f;
	m[5] = (y * x - z * w) * 2.0f;
	m[6] = (y * w - z * x) * 2.0f;
	m[7] = (z * w + y * x) * 2.0f;
	m[8] = 1.0f - (x * x + w * w) * 2.0f;
}

// @ 0x00a03f50
void DrawBodyBoxes_00a03f50(DebugTarget* target, DebugBody* body, uint32_t color3, uint32_t color4, int arg5)
{
	float m[9];
	QuatToMatrix(m, body->m_qw, body->m_qx, body->m_qy, body->m_qz);
	SetDebugTransform_00a03da0(target, m, body->m_pos, body->m_scale);

	float invScale = 1.0f / body->m_scale;
	unsigned count = body->m_end - body->m_begin;
	void* verts;
	char aux[4];

	if (!LockVertices_006ddcc0(4, count * 0x18, &verts, aux))
	{
		for (unsigned i = 0; i < count; i++)
		{
			DebugEntry* e = body->m_begin + i;
			if (LockVertices_006ddcc0(4, 0x18, &verts, aux))
			{
				const uint32_t* color = &color4;
				if (i != 0)
					color = &color3;
				DebugShape* shape = e->m_shape;
				float negOffset[3];
				negOffset[0] = -shape->m_offset[0];
				negOffset[1] = -shape->m_offset[1];
				negOffset[2] = -shape->m_offset[2];
				float pos[3];
				pos[0] = e->m_pos[0] * invScale;
				pos[1] = e->m_pos[1] * invScale;
				pos[2] = e->m_pos[2] * invScale;
				QuatToMatrix(m, e->m_qw, e->m_qx, e->m_qy, e->m_qz);
				BuildBoxVertices_00a02da0(verts, m, pos, negOffset, shape->m_offset, *color);
				UnlockVertices_006ddd40(3, target, arg5);
			}
		}
		return;
	}

	char* out = (char*)verts;
	for (unsigned i = 0; i < count; i++)
	{
		DebugEntry* e = body->m_begin + i;
		const uint32_t* color = &color4;
		if (i != 0)
			color = &color3;
		DebugShape* shape = e->m_shape;
		float negOffset[3];
		negOffset[0] = -shape->m_offset[0];
		negOffset[1] = -shape->m_offset[1];
		negOffset[2] = -shape->m_offset[2];
		float pos[3];
		pos[0] = e->m_pos[0] * invScale;
		pos[1] = e->m_pos[1] * invScale;
		pos[2] = e->m_pos[2] * invScale;
		QuatToMatrix(m, e->m_qw, e->m_qx, e->m_qy, e->m_qz);
		BuildBoxVertices_00a02da0(out, m, pos, negOffset, shape->m_offset, *color);
		out += 0x360;
	}
	UnlockVertices_006ddd40(3, target, arg5);
}
