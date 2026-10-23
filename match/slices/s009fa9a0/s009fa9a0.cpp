// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// Slice s009fa9a0: creature gait / rigid-body (IK body) integrator helpers (7 functions).
//
// Reconstructed from the retail disassembly of SporeApp.exe (image base 0x400000); raw 32-bit struct
// offsets are used instead of the generated SP headers.  A "body" is one 0x2bc-byte element of the
// creature's body array (creature +0x2e4 / +0x2e8); body+0x00 points back at the creature and body+0x08
// links to the neighbouring body whose two 0x20-byte joint records (+0x170) drive the solve.
//
// The retail code is dense scalar SSE (movss/addss/mulss/divss) with a few x87 (fld/fmul/faddp/fsqrt)
// islands; cl15 emits that schedule only for the float-free loops, so the SSE-heavy functions are
// recorded as nonmatching.
#include <math.h>

struct Vec3_s009fa9a0 { float x, y, z; };
struct Quat_s009fa9a0 { float x, y, z, w; };

// 0x20-byte joint record: position +0x00, quaternion +0x0c, tail pad.  jnt[0] lives at +0x170.
struct Jnt_s009fa9a0 { Vec3_s009fa9a0 pos; Quat_s009fa9a0 rot; float _pad; };

// ---- the creature / instance root (a body's owner) ------------------------------------------------
struct B_s009fa9a0;
struct Cr_s009fa9a0 {
	char _pad000[0x70];
	float m70;                    // +0x70
	char _pad074[0xa4 - 0x74];
	Vec3_s009fa9a0 mA4;           // +0xa4
	char _pad0b0[0xbc - 0xb0];
	Vec3_s009fa9a0 mBC;           // +0xbc
	Quat_s009fa9a0 mC8;           // +0xc8
	char _pad0d8[0x1ac - 0xd8];
	int  m1ac;                    // +0x1ac
	char _pad1b0[0x204 - 0x1b0];
	int  m204;                    // +0x204
	char _pad208[0x20c - 0x208];
	int  m20c;                    // +0x20c
	char _pad210[0x2e4 - 0x210];
	B_s009fa9a0* mBodiesBegin;    // +0x2e4
	B_s009fa9a0* mBodiesEnd;      // +0x2e8
	char _pad2ec[0x35c - 0x2ec];
	Vec3_s009fa9a0 m35c;          // +0x35c
	float m368;                   // +0x368
	char _pad36c[0x370 - 0x36c];
	char  m370;                   // +0x370
	char _pad371[0x374 - 0x371];
	float m374;                   // +0x374
};

// ---- one IK body (stride 0x2bc) -------------------------------------------------------------------
struct B_s009fa9a0 {
	Cr_s009fa9a0* owner;          // +0x00  back-pointer to the creature
	int _m04;                     // +0x04
	B_s009fa9a0*  link;           // +0x08  neighbouring body
	char _pad00c[0x144 - 0x0c];
	int  m144;                    // +0x144
	Quat_s009fa9a0 m148;          // +0x148  joint orientation
	Vec3_s009fa9a0 m158;          // +0x158  angular velocity
	Vec3_s009fa9a0 m164;          // +0x164  accumulated torque
	Jnt_s009fa9a0  jnt[2];        // +0x170, +0x190
};

// ---- retail callees -------------------------------------------------------------------------------
void F_009b4ba0(void* out, const void* q, int n);          // 0x009b4ba0
void F_0099c1a0(void* out, const void* q, const void* v);  // 0x0099c1a0  checkerlib::QuaternionVectorTransform
void F_0099c310(void* out, const void* q, const void* v);  // 0x0099c310
void F_009fa170(B_s009fa9a0* body);                        // 0x009fa170
void F_009f9dc0(Cr_s009fa9a0* cr, B_s009fa9a0* b);         // 0x009f9dc0
void F_009f9e20(Cr_s009fa9a0* cr, B_s009fa9a0* b);         // 0x009f9e20
void F_009fa770(Cr_s009fa9a0* cr, B_s009fa9a0* b);         // 0x009fa770
void F_009fa870(Cr_s009fa9a0* cr, B_s009fa9a0* b);         // 0x009fa870

// ---- retail tunables -------------------------------------------------------------------------------
extern int   g_01550ad8;                                      // +0x1550ad8
extern float g_01550adc;                                      // +0x1550adc
extern float g_01550ae0;                                      // +0x1550ae0
extern float g_01550ae4;                                      // +0x1550ae4
extern float g_01550ae8;                                      // +0x1550ae8
extern float g_01550aec;                                      // +0x1550aec
extern float g_01550af0;                                      // +0x1550af0
extern int   g_01550afc;                                      // +0x1550afc
extern float g_01551648;                                      // +0x1551648
extern float g_01551678;                                      // +0x1551678
extern float g_0155167c;                                      // +0x155167c
extern float g_01551680;                                      // +0x1551680
extern float g_01551684;                                      // +0x1551684
extern float g_0166c980;                                      // +0x166c980

// ---- forward declarations --------------------------------------------------------------------------
void f_009fa9a0(float* out, Cr_s009fa9a0* cr, B_s009fa9a0* body, float dt);
void f_009fae30(float* out, Cr_s009fa9a0* cr, B_s009fa9a0* body, float dt);
void f_009fb090(float* out, Cr_s009fa9a0* cr, B_s009fa9a0* body);
void f_009fb130(B_s009fa9a0* body, float dt);
void f_009fb510(Cr_s009fa9a0* cr, B_s009fa9a0* body, float dt);
void f_009fb7c0(Cr_s009fa9a0* cr, B_s009fa9a0* body, float dt);
void f_009fb830(Cr_s009fa9a0* cr, float dt);

// =================================================================================================
// @ 0x009fa9a0
// Compose three quaternion-rotation rows (creature orientation, link's jnt[0]/jnt[1], body's jnt[1]) and
// scale the result by -(g_01550adc/(dt+1e-8)); writes the resulting direction to out.
void f_009fa9a0(float* out, Cr_s009fa9a0* cr, B_s009fa9a0* body, float dt)
{
	B_s009fa9a0* p = body->link;
	float u = p->jnt[0].rot.x;       // +0x17c
	float v = p->jnt[0].rot.z;       // +0x184
	float w = p->jnt[0].rot.y;       // +0x180
	float t = p->jnt[0].rot.w;       // +0x188
	float a0 = cr->mC8.x;
	float a1 = cr->mC8.y;
	float a2 = cr->mC8.z;
	float a3 = cr->mC8.w;

	float r7 = -((v * w + t * u) * 2.0f);
	float r6 = -(1.0f - (v * v + u * u) * 2.0f);
	float r3 = -((w * u - v * t) * 2.0f);

	float c0 = (((a2 * a0 + -(a1 * a3)) * r7 + (a1 * a0 - -(a2 * a3)) * r6) +
	            (-(a2 * a2) + -(a1 * a1)) * r3) * 2.0f + r3;
	float c1 = (((-(a1 * a1) + -(a0 * a0)) * r7 + (a2 * a1 + -(a0 * a3)) * r6) +
	            (a2 * a0 - -(a1 * a3)) * r3) * 2.0f + r7;
	float c2 = (((a2 * a1 - -(a0 * a3)) * r7 + (-(a2 * a2) + -(a0 * a0)) * r6) +
	            (a1 * a0 + -(a2 * a3)) * r3) * 2.0f + r6;

	float q0 = p->jnt[1].rot.x;      // +0x19c
	float q1 = p->jnt[1].rot.y;      // +0x1a0
	float q2 = p->jnt[1].rot.z;      // +0x1a4
	float q3 = p->jnt[1].rot.w;      // +0x1a8
	float s7 = -((q1 * q0 - q2 * q3) * 2.0f);
	float s6 = -((q2 * q1 + q3 * q0) * 2.0f);
	float s3 = -(1.0f - (q2 * q2 + q0 * q0) * 2.0f);

	float tf = -(g_01550adc / (dt + 1e-8f));
	float y7 = (s6 * c2 - s3 * c1) * tf;
	float y3 = (c1 * s7 - s6 * c0) * tf;
	float y0 = (s3 * c0 - c2 * s7) * tf;

	float e0 = body->jnt[1].rot.x;
	float e1 = body->jnt[1].rot.y;
	float e2 = body->jnt[1].rot.z;
	float e3 = body->jnt[1].rot.w;

	out[0] = (((-(e2 * e2) + -(e1 * e1)) * y7 + (e2 * e0 + -(e1 * e3)) * y0) +
	          (e1 * e0 - -(e2 * e3)) * y3) * 2.0f + y7;
	out[1] = (((-(e2 * e2) + -(e0 * e0)) * y3 + (e2 * e1 - -(e0 * e3)) * y0) +
	          (e1 * e0 + -(e2 * e3)) * y7) * 2.0f + y3;
	out[2] = (((-(e1 * e1) + -(e0 * e0)) * y0 + (e2 * e1 + -(e0 * e3)) * y3) +
	          (e2 * e0 - -(e1 * e3)) * y7) * 2.0f + y0;
}

// =================================================================================================
// @ 0x009fae30
// Acceleration from the creature's position/velocity plus the link's joint separation, then the torque
// contribution cross(axisf, acc) rotated back through the body's jnt[1] quaternion.  Zero when tiny.
void f_009fae30(float* out, Cr_s009fa9a0* cr, B_s009fa9a0* body, float dt)
{
	B_s009fa9a0* p = body->link;
	float inv = 1.0f / (dt * dt + 1e-8f);
	float dx = p->jnt[1].pos.x - p->jnt[0].pos.x;
	float dy = p->jnt[1].pos.y - p->jnt[0].pos.y;
	float dz = p->jnt[1].pos.z - p->jnt[0].pos.z;

	float ax = cr->mA4.x * g_01550ae4 + (cr->mBC.x * g_01550ae0 + dx * g_01550ae8 * inv);
	float ay = cr->mA4.y * g_01550ae4 + (cr->mBC.y * g_01550ae0 + dy * g_01550ae8 * inv);
	float az = cr->mA4.z * g_01550ae4 + (cr->mBC.z * g_01550ae0 + dz * g_01550ae8 * inv);

	if ((az * az + ay * ay) + ax * ax > 1e-6f)
	{
		Cr_s009fa9a0* ty = body->owner;
		Vec3_s009fa9a0 r;
		F_0099c1a0(&r, &body->jnt[1].rot, &ty->m35c);

		float f = 1.0f / ((ty->m368 * cr->m70) * -1.0f);
		float rx = r.x * f;
		float ry = r.y * f;
		float rz = r.z * f;
		float sc = ty->m374;

		Vec3_s009fa9a0 c;
		c.x = sc * (rz * ay - ry * az);
		c.y = sc * (rx * az - rz * ax);
		c.z = sc * (ry * ax - rx * ay);

		Vec3_s009fa9a0 res;
		F_0099c310(&res, &body->jnt[1].rot, &c);
		out[0] = res.x;
		out[1] = res.y;
		out[2] = res.z;
		return;
	}

	out[0] = 0.0f;
	out[1] = 0.0f;
	out[2] = 0.0f;
}

// =================================================================================================
// @ 0x009fb090
// Angular contribution: scale the body's jnt[1] quaternion's xyz by -(((w*1.6+1)*w)*g_01550aec).
void f_009fb090(float* out, Cr_s009fa9a0* cr, B_s009fa9a0* body)
{
	float v[4];
	F_009b4ba0(v, &body->m148, 0);
	if (v[3] > 1e-6f)
	{
		float f = -(((v[3] * 1.6f + 1.0f) * v[3]) * g_01550aec);
		out[0] = f * v[0];
		out[1] = f * v[1];
		out[2] = f * v[2];
		return;
	}
	out[0] = 0.0f;
	out[1] = 0.0f;
	out[2] = 0.0f;
}

// =================================================================================================
// @ 0x009fb130
// Integrate one body: torque -> angular velocity (clamped), quaternion += 0.5*dt*(0,omega) x q, then
// normalise; when the orientation degenerates snap it to the reference quaternion.
void f_009fb130(B_s009fa9a0* body, float dt)
{
	body->m158.y = body->m158.y + body->m164.y * dt;
	body->m158.z = body->m158.z + body->m164.z * dt;
	body->m158.x = body->m158.x + body->m164.x * dt;

	float n2 = (body->m158.x * body->m158.x + body->m158.y * body->m158.y) +
	           body->m158.z * body->m158.z;
	if (g_0166c980 < n2)
	{
		float f = g_01551648 / sqrtf(n2);
		body->m158.x = f * body->m158.x;
		body->m158.y = f * body->m158.y;
		body->m158.z = f * body->m158.z;
	}

	float h = dt * 0.5f;
	float wx = body->m158.x * h;
	float wy = body->m158.y * h;
	float wz = body->m158.z * h;
	float zero = h * 0.0f;

	float qx = body->m148.x, qy = body->m148.y, qz = body->m148.z, qw = body->m148.w;
	float dx = ((qx * zero + qw * wx) - qy * wz) + qz * wy;
	float dy = ((qy * zero + qx * wz) + qw * wy) - qz * wx;
	float dz = ((qw * wz - qx * wy) + qz * zero) + qy * wx;
	float dw = ((qw * zero - qx * wx) - qy * wy) - qz * wz;
	body->m148.x = dx + body->m148.x;
	body->m148.y = dy + body->m148.y;
	body->m148.z = dz + body->m148.z;
	body->m148.w = dw + body->m148.w;

	float len = sqrtf(((body->m148.x * body->m148.x + body->m148.y * body->m148.y) +
	                   body->m148.z * body->m148.z) + body->m148.w * body->m148.w);
	if (len != 0.0f)
	{
		float inv = 1.0f / len;
		body->m148.x = body->m148.x * inv;
		body->m148.y = body->m148.y * inv;
		body->m148.z = body->m148.z * inv;
		body->m148.w = body->m148.w * inv;
	}

	if (g_01550afc != 0)
		F_009fa170(body);

	if ((1.0f - fabsf(body->m148.w) < 1e-6f) &&
	    ((body->m158.x * body->m158.x + body->m158.y * body->m158.y) +
	     body->m158.z * body->m158.z < 1e-6f))
	{
		body->m148.x = g_01551678;
		body->m148.y = g_0155167c;
		body->m148.z = g_01551680;
		body->m148.w = g_01551684;
		body->m158.x = 0.0f;
		body->m158.y = 0.0f;
		body->m158.z = 0.0f;
	}
}

// =================================================================================================
// @ 0x009fb510
// Per-body step: accumulate the torque contributions, integrate, then let the caller's constraint pass
// run; when the body is disabled, wrap/normalise the orientation and clear the angular velocity.
void f_009fb510(Cr_s009fa9a0* cr, B_s009fa9a0* body, float dt)
{
	if (body->owner->m370 != 0 && body->link != 0)
	{
		if (g_01550ad8 != 0)
		{
			Vec3_s009fa9a0 t;
			f_009fa9a0(&t.x, cr, body, dt);
			body->m164.x = body->m164.x + t.x;
			body->m164.y = body->m164.y + t.y;
			body->m164.z = body->m164.z + t.z;
		}

		Vec3_s009fa9a0 t2;
		f_009fae30(&t2.x, cr, body, dt);
		body->m164.x = body->m164.x + t2.x;
		body->m164.y = body->m164.y + t2.y;
		body->m164.z = body->m164.z + t2.z;

		Vec3_s009fa9a0 t3;
		f_009fb090(&t3.x, cr, body);
		body->m164.x = body->m164.x + t3.x;
		body->m164.y = body->m164.y + t3.y;
		body->m164.z = body->m164.z + t3.z;

		float damp = -g_01550af0;
		body->m164.x = body->m164.x + body->m158.x * damp;
		body->m164.y = body->m164.y + body->m158.y * damp;
		body->m164.z = body->m164.z + body->m158.z * damp;

		f_009fb130(body, dt);
		F_009f9e20(cr, body);
		return;
	}

	float qw = body->m148.w;
	if (qw < 0.0f)
		qw = qw - 1.0f;
	else
		qw = qw + 1.0f;
	body->m148.w = qw;

	float len = sqrtf(((body->m148.x * body->m148.x + body->m148.y * body->m148.y) +
	                   body->m148.z * body->m148.z) + body->m148.w * body->m148.w);
	if (len != 0.0f)
	{
		float inv = 1.0f / len;
		body->m148.x = body->m148.x * inv;
		body->m148.y = body->m148.y * inv;
		body->m148.z = body->m148.z * inv;
		body->m148.w = body->m148.w * inv;
	}
	body->m158.x = 0.0f;
	body->m158.y = 0.0f;
	body->m158.z = 0.0f;

	F_009f9e20(cr, body);
}

// =================================================================================================
// @ 0x009fb7c0
// Step one body then every body from the creature's m204 index (stride 0x2bc).
void f_009fb7c0(Cr_s009fa9a0* cr, B_s009fa9a0* body, float dt)
{
	f_009fb510(cr, body, dt);
	Cr_s009fa9a0* ty = body->owner;
	int m = ty->m204;
	if ((unsigned)ty->m20c <= 0u)
		return;
	unsigned n = ty->m20c;
	do
	{
		f_009fb510(cr, (B_s009fa9a0*)((char*)cr->mBodiesBegin + m * 0x2bc), dt);
		m += 1;
	} while (--n);
}

// =================================================================================================
// @ 0x009fb830
// Walk the creature's whole body array: for each live body whose link is idle, release its constraint,
// bump its active count, then run the sub-step.
void f_009fb830(Cr_s009fa9a0* cr, float dt)
{
	int n = (int)((char*)cr->mBodiesEnd - (char*)cr->mBodiesBegin) / 700;
	if (n == 0)
		return;
	int off = 0;
	for (int i = n; i != 0; --i)
	{
		B_s009fa9a0* el = (B_s009fa9a0*)((char*)cr->mBodiesBegin + off);
		int m = el->m144;
		if (m > 0 && el->link != 0 && el->link->m144 == 0)
		{
			if (m == 1)
			{
				F_009f9dc0(cr, el->link);
				if (cr->m1ac <= 1)
					F_009fa870(cr, el);
				else
					F_009fa770(cr, el);
				el->m144 = el->m144 + 1;
			}
			f_009fb7c0(cr, el, dt);
		}
		off += 700;
	}
}
