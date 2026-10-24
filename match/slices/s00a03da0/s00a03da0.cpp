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

// 0x00a03da0: stores the transform used by the draw state (cdecl); first arg unused by the callee
const float* FUN_00a03da0(void* target, const float* matrix3x3, const float* pos, float scale);
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
	FUN_00a03da0(target, m, body->m_pos, body->m_scale);

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

// ============================================================================================
// The "animating creature" debug/attachment group (00a04550 .. 00a04cc0).
//
// A cAnimatingCreature owns a physics body (at +0x17c), a root render instance (at +0x180), a
// render-manager lookup (at +0x184) and a scene-manager chain (at +0x190). The body holds its
// world frame (position +0x18, quaternion +0x3c, scale +0x70) and a part list (+0x2c0) whose
// 0x14-byte slots point (+0x0c) at child render instances. Each render instance carries a
// position (+0x0c), a scale (+0x18), a 3x3 basis (+0x1c), two dirty-bit words (+0x44/+0x48)
// and a ref-counted model pointer (+0x64).
// ============================================================================================

// --- ref-counted model interface ------------------------------------------------------------
struct IUnknown
{
	virtual void AddRef();
	virtual void Release();
};

struct PartSlot   // 0x14 bytes, element of the part list
{
	char pad00[0x0c];
	void* m_inst;   // +0x0c  (child render instance)
};

struct PartList
{
	char pad00[0x28];
	char* m_begin;  // +0x28
	char* m_end;    // +0x2c

	// thiscall members of the part list itself (ecx = this)
	void FUN_009c6fc0(void* mgrpart, float a, float b, float c, float d,
	                  int e, int f, unsigned char g);   // 0x9c6fc0
};

struct RenderInst
{
	char pad00[8];
	unsigned short m_flags;     // +0x08  (bit 1 = basis dirty, bit 2 = position dirty)
	signed short m_dirty;       // +0x0a  bump counter
	float m_x;                  // +0x0c
	float m_y;                  // +0x10
	float m_z;                  // +0x14
	float m_scale;              // +0x18
	float m_basis[9];           // +0x1c
	char pad40[4];              // +0x40  (unused by these functions)
	uint32_t m_bits0;           // +0x44  (model-group bits 0..31)
	uint32_t m_bits1;           // +0x48  (model-group bits 32..63)
	char pad4c[0x64 - 0x4c];
	IUnknown* m_model;          // +0x64  ref-counted model pointer
};

struct AnimBody
{
	void* m_data;               // +0x00  points at the raw transform storage
	char pad04[0x18 - 4];
	float m_px;                 // +0x18
	float m_py;                 // +0x1c
	float m_pz;                 // +0x20
	char pad24[0x3c - 0x24];
	float m_qw;                 // +0x3c
	float m_qx;                 // +0x40
	float m_qy;                 // +0x44
	float m_qz;                 // +0x48
	char pad4c[0x70 - 0x4c];
	float m_scale;              // +0x70
	char pad74[0x2c0 - 0x74];
	PartList* m_parts;          // +0x2c0
	char pad2c4[0x2d4 - 0x2c4];
	unsigned char m_field2d4;   // +0x2d4
	unsigned char m_field2d5;   // +0x2d5
	char pad2d6[0x1684 - 0x2d6];
	int m_field1684;            // +0x1684
	char pad1688[0x168d - 0x1688];
	unsigned char m_field168d;  // +0x168d

	// thiscall members of the physics body itself (ecx = this)
	void FUN_009b3b20(void* a, void* b, int c);                       // 0x9b3b20
	void FUN_009b3920(const float* pos, const float* quat);           // 0x9b3920
};

struct Mgr193
{
	char pad00[0x1c];
	void* m_field1c;   // +0x1c
};

struct Node50
{
	char pad00[0x50];
	void* m_field50;   // +0x50
};

struct LookupEntry
{
	void* m_obj;               // +0x00
	char pad04[0xc0 - 4];
	uint32_t m_fieldC0;        // +0xc0
};

struct SceneTarget   // object returned by the scene chain virtual call
{
	char pad00[0x10];
	unsigned char m_field10;   // +0x10
	char pad11[0x12 - 0x11];
	unsigned short m_kind;     // +0x12
};

struct cAnimatingCreature
{
	char pad00[4];
	char m_frame04[0x0c];       // +0x04  (target frame position, for the body transform helper)
	char m_frame10[0x40];       // +0x10
	int m_mode50;               // +0x50
	int m_mode54;               // +0x54
	char pad58[0x74 - 0x58];
	float m_blendX;             // +0x74
	float m_blendY;             // +0x78
	float m_blendZ;             // +0x7c
	float m_blendW;             // +0x80
	unsigned char m_flag84;     // +0x84
	char pad85[0x17c - 0x85];
	AnimBody* m_body;           // +0x17c
	RenderInst* m_inst;         // +0x180
	void* m_lookup184;          // +0x184
	void* m_field188;           // +0x188  (unused by these functions)
	void* m_field18c;           // +0x18c  (unused by these functions)
	Mgr193* m_scene190;         // +0x190

	void FUN_00a04550(int index, const float* value);
	void FUN_00a047d0(unsigned char param2);
	int  FUN_00a048b0(int id, int a3, int a4, int a5);
	bool FUN_00a04900(int unused);
	bool FUN_00a04940(int id);
	bool FUN_00a04990(int id);
	float FUN_00a049f0(int id);
	void FUN_00a04ab0(unsigned char value);
	void FUN_00a04ad0(int value);
	void FUN_00a04af0(IUnknown* model);
	void FUN_00a04bb0(unsigned index, unsigned char enable);
	void FUN_00a04ca0(unsigned char value);
	void FUN_00a04cc0(unsigned char value);
};

// Free (cdecl) helpers: they take the creature pointer as a stack argument.
float* FUN_00a04590(cAnimatingCreature* self, float* out);              // 0x00a04590
void FUN_00a04630(cAnimatingCreature* self, unsigned char param2, unsigned char param3);  // 0x00a04630

// --- external helpers -----------------------------------------------------------------------
extern "C" void* FUN_009ff750(void* mgr);                            // 0x9ff750
extern "C" void* FUN_009ff6f0(void* mgr, int id);                    // 0x9ff6f0
extern "C" int   FUN_0099d0b0(void* a, void* b, void* c, void* d);   // 0x99d0b0
extern "C" __declspec(dllimport) double modf(double x, double* iptr);  // msvcr90!modf
// Quaternion -> 3x3 rotation basis (cdecl: out, quat). Returns `out`.
extern "C" float* FUN_009a46a0(float* out, const float* quat);       // 0x9a46a0
// Blend-state setter (cdecl: body, blend).
extern "C" void FUN_009bc580(void* body, float blend);               // 0x9bc580

#define g_softStateDirty      (*(uint32_t*)0x16f9528)
#define g_transformType       (*(uint32_t*)0x16f96a0)
#define g_transformPtr        (*(void**)0x16fa380)
#define g_transformLocal      ((float*)0x16fa4f0)
#define g_posNegate           (*(const uint32_t*)0x13eb8b0)
#define g_sceneKindDefault    (*(const unsigned char*)0x15d115d)
#define g_minusOne            (*(const float*)0x13eb1bc)
#define g_blendConst          (*(const double*)0x1448b20)
#define g_uintToFloat         (*(const float*)0x13f4fd0)
#define g_realOne             (*(const float*)0x1485720)

// Float arguments for helpers whose real ABI is opaque to the harness.
static float PassFloat(float v) { return v; }

// @ 0x00a03da0
const float* FUN_00a03da0(void* target, const float* m, const float* pos, float scale)
{
	(void)target;
	g_softStateDirty |= 1;
	g_transformType = 2;
	g_transformPtr = g_transformLocal;

	float* d = g_transformLocal;
	d[0] = m[0] * scale; d[1] = m[3] * scale; d[2] = m[6] * scale; d[3] = m[0] * scale;
	d[4] = m[1] * scale; d[5] = m[4] * scale; d[6] = m[7] * scale; d[7] = m[1] * scale;
	d[8] = m[2] * scale; d[9] = m[5] * scale; d[10] = m[8] * scale; d[11] = m[2] * scale;
	d[12] = pos[0]; d[13] = pos[1]; d[14] = pos[2]; d[15] = pos[0];
	return m;
}

// @ 0x00a03e80
void FUN_00a03e80(DebugTarget* target, const float* m, const float* pos, float scale,
                  const float* negOffset, const float* extents, uint32_t color, int arg8)
{
	FUN_00a03da0(target, m, pos, scale);

	void* verts;
	char aux[4];
	if (!LockVertices_006ddcc0(4, 0x18, &verts, aux))
		return;

	float basis[9];
	float center[3];
	basis[1] = 0.0f; basis[2] = 0.0f; basis[3] = 0.0f;
	basis[5] = 0.0f; basis[6] = 0.0f; basis[7] = 0.0f;
	basis[8] = 1.0f; basis[4] = 1.0f; basis[0] = 1.0f;
	center[0] = 0.0f; center[1] = 0.0f; center[2] = 0.0f;
	BuildBoxVertices_00a02da0(verts, basis, center, negOffset, extents, color);
	UnlockVertices_006ddd40(3, target, arg8);
}

// @ 0x00a04550
void cAnimatingCreature::FUN_00a04550(int index, const float* value)
{
	AnimBody* body = m_body;
	if (!body)
		return;
	float* data = (float*)body->m_data;
	if (!data)
		return;
	if ((unsigned)index >= 3)
		return;
	float* dst = data + index * 3 + 0xc9;
	dst[0] = value[0];
	dst[1] = value[1];
	dst[2] = value[2];
}

// @ 0x00a04590
float* FUN_00a04590(cAnimatingCreature* self, float* out)
{
	int mode = self->m_mode54;
	if (mode == 4)
		mode = self->m_mode50;
	if (mode == 0)
	{
		out[0] = 1.0f; out[1] = 0.0f; out[2] = 0.0f; out[3] = 1.0f;
	}
	else if (mode == 1)
	{
		out[0] = 1.0f; out[1] = 0.0f; out[2] = 1.0f; out[3] = 1.0f;
	}
	else if (mode == 2)
	{
		out[0] = 0.0f; out[1] = 0.0f; out[2] = 1.0f; out[3] = 1.0f;
	}
	else
	{
		return (float*)(size_t)(mode - 2);
	}
	return out;
}

// @ 0x00a04630
void FUN_00a04630(cAnimatingCreature* self, unsigned char param2, unsigned char param3)
{
	AnimBody* body = self->m_body;
	if (body->m_parts == 0)
	{
		RenderInst* inst = self->m_inst;
		if (inst != 0)
		{
			inst->m_x = body->m_px;
			inst->m_y = body->m_py;
			inst->m_z = body->m_pz;
			inst->m_flags |= 4;
			inst->m_dirty++;

			uint32_t quat[4];
			quat[0] = *(uint32_t*)&body->m_qw ^ g_posNegate;
			quat[1] = *(uint32_t*)&body->m_qx ^ g_posNegate;
			quat[2] = *(uint32_t*)&body->m_qy ^ g_posNegate;
			quat[3] = *(uint32_t*)&body->m_qz;

			float local[9];
			float* mat = FUN_009a46a0(local, (const float*)quat);
			for (int i = 0; i < 9; i++)
				inst->m_basis[i] = mat[i];
			inst->m_flags |= 2;
			inst->m_dirty++;
			inst->m_scale = body->m_scale;
			inst->m_dirty++;
		}
		return;
	}

	float blend[4];
	blend[0] = self->m_blendX;
	blend[1] = self->m_blendY;
	blend[2] = self->m_blendZ;
	blend[3] = self->m_blendW;
	unsigned char flag = self->m_flag84;
	int mode = self->m_mode54;
	if (mode == 4)
		mode = self->m_mode50;
	char* mgrpart = (char*)self->m_scene190 + 0x68;
	if (param2)
	{
		flag = 0;
		typedef float* (*BlendFn)(cAnimatingCreature*, float*);
		BlendFn volatile blendFn = &FUN_00a04590;
		blendFn(self, blend);
	}
	float d = param3 ? 0.0f : blend[3];

	body->m_parts->FUN_009c6fc0(mgrpart,
	                            blend[0], blend[1], blend[2], d,
	                            mode == 2, mode > 0 ? 1 : 0, flag);
}

// @ 0x00a047d0
void cAnimatingCreature::FUN_00a047d0(unsigned char param2)
{
	AnimBody* body = m_body;

	body->FUN_009b3b20(m_frame04, m_frame10, 0);
	body->FUN_009b3920(&body->m_px, &body->m_qw);
	FUN_009bc580(body, param2 ? (float)g_blendConst : 0.0f);

	Mgr193* m193 = m_scene190;
	Node50* node = (Node50*)m193->m_field1c;
	void* obj = node->m_field50;
	SceneTarget* target = (SceneTarget*)((void*(__thiscall*)(void*, uint32_t))((void**)*(void***)obj)[0x28 / 4])(obj, 0xe0e98b25);

	unsigned short kind = target->m_kind;
	if (kind == 1 || kind == 0x10)
	{
		if (target->m_field10 & 0x30)
			FUN_00a04630(this, *(unsigned char*)*(void**)target, 0);
		else
			FUN_00a04630(this, *(unsigned char*)(size_t)(-(int)(kind != 0) & (int)target), 0);
	}
	else
	{
		FUN_00a04630(this, g_sceneKindDefault, 0);
	}
}

// @ 0x00a048b0
int cAnimatingCreature::FUN_00a048b0(int id, int a3, int a4, int a5)
{
	void* e = FUN_009ff6f0(m_lookup184, id);
	void* result = 0;
	if (e != 0)
	{
		void* obj = *(void**)e;
		if (obj != 0 && *((uint32_t*)obj) != 0)
			result = *((void**)((char*)obj + 8));
	}
	if (result != 0)
		return FUN_0099d0b0(result, (void*)a3, (void*)a4, (void*)a5);
	return -1;
}

// @ 0x00a04900
bool cAnimatingCreature::FUN_00a04900(int unused)
{
	(void)unused;
	bool result;
	LookupEntry* e = (LookupEntry*)FUN_009ff750(m_lookup184);
	if (e == 0)
	{
		result = true;
	}
	else
	{
		void* obj = e->m_obj;
		if (*(unsigned char*)((char*)obj + 0xac) == 0 && e->m_fieldC0 != 0)
			result = true;
		else
			result = false;
	}
	return result;
}

// @ 0x00a04940
bool cAnimatingCreature::FUN_00a04940(int id)
{
	LookupEntry* e = id ? (LookupEntry*)FUN_009ff6f0(m_lookup184, id)
	                    : (LookupEntry*)FUN_009ff750(m_lookup184);
	if (e != 0 && e->m_obj != 0)
	{
		if (e->m_fieldC0 == 3)
			return true;
		return false;
	}
	return true;
}

// @ 0x00a04990
bool cAnimatingCreature::FUN_00a04990(int id)
{
	LookupEntry* e = id ? (LookupEntry*)FUN_009ff6f0(m_lookup184, id)
	                    : (LookupEntry*)FUN_009ff750(m_lookup184);
	if (e != 0 && *(uint32_t*)e != 0)
	{
		if (*(float*)((char*)e + 0xa0) == g_minusOne)
			return true;
	}
	return false;
}

// @ 0x00a049f0
float cAnimatingCreature::FUN_00a049f0(int id)
{
	float out = 0.0f;
	LookupEntry* e = id ? (LookupEntry*)FUN_009ff6f0(m_lookup184, id)
	                    : (LookupEntry*)FUN_009ff750(m_lookup184);
	if (e && e->m_obj)
	{
		void* obj = e->m_obj;
		double f = *(double*)((char*)obj + 0xb0) / *(double*)((char*)obj + 0xb8);
		double ipart;
		double frac = modf(f, &ipart);
		if ((float)f < 0.0f)
			frac = 1.0 - frac;
		int whole = *(int*)((char*)e + 0xb0);
		double sum = (double)whole;
		if (whole < 0)
			sum += g_uintToFloat;
		sum += frac;
		out = (float)sum;
	}
	return out;
}

// @ 0x00a04ab0
void cAnimatingCreature::FUN_00a04ab0(unsigned char value)
{
	AnimBody* body = m_body;
	if (!body)
		return;
	body->m_field168d = value;
}

// @ 0x00a04ad0
void cAnimatingCreature::FUN_00a04ad0(int value)
{
	AnimBody* body = m_body;
	if (!body)
		return;
	body->m_field1684 = value;
}

static void AssignModel(RenderInst* inst, IUnknown* model)
{
	if (!inst)
		return;
	IUnknown* old = inst->m_model;
	if (model == old)
		return;
	if (model)
		model->AddRef();
	inst->m_model = model;
	if (old)
		old->Release();
}

// @ 0x00a04af0
void cAnimatingCreature::FUN_00a04af0(IUnknown* model)
{
	AssignModel(m_inst, model);

	AnimBody* body = m_body;
	if (!body)
		return;
	PartList* parts = body->m_parts;
	if (!parts)
		return;
	unsigned count = (unsigned)((parts->m_end - parts->m_begin) / 0x14);
	if (count == 0)
		return;
	for (unsigned i = 0; i < count; i++)
	{
		PartSlot* slot = (PartSlot*)(m_body->m_parts->m_begin + i * 0x14);
		AssignModel((RenderInst*)slot->m_inst, model);
	}
}

// @ 0x00a04bb0
void cAnimatingCreature::FUN_00a04bb0(unsigned index, unsigned char enable)
{
	RenderInst* inst = m_inst;
	if (!inst)
		return;

	if (index < 0x40)
	{
		uint32_t bit = 1u << (index & 0x1f);
		uint32_t* word = &inst->m_bits0 + (index >> 5);
		if (enable)
			*word |= bit;
		else
			*word &= ~bit;
	}

	AnimBody* body = m_body;
	if (!body)
		return;
	PartList* parts = body->m_parts;
	if (!parts)
		return;
	unsigned count = (unsigned)((parts->m_end - parts->m_begin) / 0x14);
	if (count == 0)
		return;
	for (unsigned i = 0; i < count; i++)
	{
		PartSlot* slot = (PartSlot*)(parts->m_begin + i * 0x14);
		RenderInst* child = (RenderInst*)slot->m_inst;
		if (!child)
			continue;
		if (index < 0x40)
		{
			uint32_t bit = 1u << (index & 0x1f);
			uint32_t* word = &child->m_bits0 + (index >> 5);
			if (enable)
				*word |= bit;
			else
				*word &= ~bit;
		}
		child->m_flags &= ~8;
	}
}

// @ 0x00a04ca0
void cAnimatingCreature::FUN_00a04ca0(unsigned char value)
{
	AnimBody* body = m_body;
	body->m_field2d4 = value;
}

// @ 0x00a04cc0
void cAnimatingCreature::FUN_00a04cc0(unsigned char value)
{
	AnimBody* body = m_body;
	body->m_field2d5 = value;
}
