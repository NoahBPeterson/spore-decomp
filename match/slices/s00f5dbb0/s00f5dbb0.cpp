// 0x00F5DBB0: writes the particles of an effect emitter into a locked vertex buffer, 4 vertices (a quad) per
// particle, like its sibling 0x00F5CCF0 (match/slices/s00f5ccf0) but with a single effect description (no
// cross-fade) and with the position's w taken from a 6-face cube map of 16-bit heights (512 x 512 per face,
// value = (h - 0x8000) * 100/32768) looked up by the direction of the particle's world position.
//
// NAMING NOTE: no symbol or PDB type is known for this function or its structures; every name here is
// Claude-coined, following the sibling slice s00f5ccf0. The draw-parameter record filled by 0x00F5A200 follows the
// layout used in match/slices/s00f5a200. Offsets are the retail 32-bit ones.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

// ---- curves ------------------------------------------------------------------------------------------------
template <class T> struct Vec { T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator; };   // eastl::vector (16 bytes)
struct Vector3 { float x, y, z; };

// Number of curve segments (size - 1) as an unsigned count.
template <class T> static inline uint32_t SegmentCount(const Vec<T>& v) { return (uint32_t)((int)(v.mpEnd - v.mpBegin) - 1); }

// Piecewise-linear sample of a curve at t in [0,1].
static inline float SampleCurve(const Vec<float>& v, uint32_t n, float t)
{
	if (n == 0)
		return v.mpBegin[0];
	float f = (float)n * t;
	int i = (int)f;
	float frac = f - (float)i;
	if (frac > 0.0f)
		return (v.mpBegin[i + 1] - v.mpBegin[i]) * frac + v.mpBegin[i];
	return v.mpBegin[i];
}

static inline Vector3 SampleCurve(const Vec<Vector3>& v, uint32_t n, float t)
{
	if (n == 0)
		return v.mpBegin[0];
	float f = (float)n * t;
	int i = (int)f;
	float frac = f - (float)i;
	const Vector3* p = &v.mpBegin[i];
	if (frac > 0.0f)
	{
		Vector3 r;
		r.x = (p[1].x - p[0].x) * frac + p[0].x;
		r.y = p[0].y + (p[1].y - p[0].y) * frac;
		r.z = p[0].z + (p[1].z - p[0].z) * frac;
		return r;
	}
	return *p;
}

// /arch:SSE float helpers (minss/maxss/cvtss2si in the original).
static inline float MaxF(float a, float b) { return (a > b) ? a : b; }
static inline float MinF(float a, float b) { return (a < b) ? a : b; }
static inline int RoundToInt(float f) { return _mm_cvtss_si32(_mm_set_ss(f)); }
static inline uint8_t ToByte(float c) { return (uint8_t)RoundToInt(MinF(MaxF(0.0f, c) * 255.0f, 255.0f)); }
// Reference-returning min/max (the original selects the address of the winner and loads through it).
static inline const float& MaxRef(const float& a, const float& b) { return (a > b) ? a : b; }
static inline const float& MinRef(const float& a, const float& b) { return (b > a) ? a : b; }

// ---- fast sin/cos (16-entry table + 2nd-order correction) ------------------------------------------------------
extern float g_angleScale;           // 0x016C949C (name guessed): applied to the particle angle
extern float g_sinCosTableScale;     // 0x016C940C (name guessed): angle -> table steps
extern float g_sinCosTableStep;      // 0x016C9408 (name guessed): table step -> angle
extern float g_sinCosTable[16][2];   // 0x01677840 (name guessed): {sin, cos} pairs

// ---- structures -----------------------------------------------------------------------------------------------
struct Particle
{
	Particle* mpNext;    // +0
	uint32_t pad04;
	float mAge;          // +0x8
	float mLifetime;     // +0xc
	float mPos[3];       // +0x10
	uint32_t pad1c[3];
	float mSize;         // +0x28
	uint32_t pad2c;
	float mRotation;     // +0x30
	float mAlpha;        // +0x34
	float mColor[3];     // +0x38
	uint8_t mCorner;     // +0x44 (top byte of the corner attribute)
};

struct EffectDescription
{
	char pad00[0x84];
	Vec<float> mSizeCurve;        // +0x84
	uint32_t pad94[2];
	Vec<float> mUnusedCurve;      // +0x9c (counted and sampled by the original, value never used)
	uint32_t padac[2];
	Vec<float> mRotationCurve;    // +0xb4
	uint32_t padc4[2];
	float mRotationOffset;        // +0xcc
	Vec<Vector3> mColorCurve;     // +0xd0
	uint32_t pade0[4];
	Vec<float> mAlphaCurve;       // +0xf0
	char pad100[0x178 - 0x100];
	bool mScreenEdgeFade;         // +0x178
};

struct DrawParams   // filled by 0x00F5A200 (layout from slice s00f5a200); scalar members only (no /GS cookie)
{
	Vector3 axis0;         // +0x00
	Vector3 axis1;         // +0x0c
	float edgeAlphaBase;   // +0x18
	float edgeAlphaSlope;  // +0x1c
	float edgeSizeBase;    // +0x20
	float edgeSizeSlope;   // +0x24
	uint32_t flag28;       // +0x28 (byte)
	float tileInvW;        // +0x2c
	float tileInvH;        // +0x30
	float tileMaxU;        // +0x34
	float tileMaxV;        // +0x38
	float tileLog2W;       // +0x3c
	bool invertEdgeFade;   // +0x40
};

struct ViewMatrixOwner { char pad[0x1c]; float m[4][4]; };   // +0x1c: row-major 4x4

// 6 faces x 512 x 512 unsigned 16-bit heights (+x/-x... order: face 0/1 = +z/-z, 2/3 = +x/-x, 4/5 = +y/-y).
struct HeightCubeMap { char pad[0x10]; const uint16_t* mpData; };   // +0x10

struct EmitterContext
{
	char pad00[0x18];
	Particle* mpParticles;          // +0x18
	uint32_t pad1c;
	int mParticleCount;             // +0x20
	EffectDescription* mpCurrent;   // +0x24
	uint32_t pad28[3];
	ViewMatrixOwner* mpCamera;      // +0x34
	char pad38[0x108 - 0x38];
	uint32_t mFlags;                // +0x108 (bit 1: transform particle positions by mRotation)
	float mOrigin[3];               // +0x10c
	float mScale;                   // +0x118
	float mRotation[3][3];          // +0x11c
	char pad140[0x19c - 0x140];
	float mSizeScale;               // +0x19c
	float mAlphaScale;              // +0x1a0
	uint32_t pad1a4;
	float mColorScale[3];           // +0x1a8
	HeightCubeMap* mpHeightMap;     // +0x1b4
};

// Screen-space x/y of a world point (row-vector times the 4x4 view-projection, divided by w).
struct ScreenPoint { float x, y; };
static inline ScreenPoint ProjectToScreen(const float m[4][4], float px, float py, float pz)
{
	float sx0 = m[2][0] * pz + m[1][0] * py + m[0][0] * px + m[3][0];
	float sy0 = m[2][1] * pz + m[1][1] * py + m[0][1] * px + m[3][1];
	float w = m[2][3] * pz + m[1][3] * py + m[0][3] * px + m[3][3];
	float invW = 1.0f / w;
	ScreenPoint r;
	r.x = invW * sx0;
	r.y = invW * sy0;
	return r;
}

struct VertexWriter
{
	virtual int Lock(int count, char** ppData, int* pStride);   // 0
	virtual void v1();
	virtual void Unlock();                                       // 2
};

struct VertexFormat { uint8_t posOffset, dirOffset, colorOffset, cornerOffset; };

void BuildDrawParams(EmitterContext* ctx, EffectDescription* desc, DrawParams* out);   // 0x00F5A200

static inline void Store4(char* p, float a, float b, float c, float d)
{
	float* f = (float*)p;
	f[0] = a; f[1] = b; f[2] = c; f[3] = d;
}

// Cube-map texel coordinate of a ratio in [-1, 1]: 0..512, with 512 folded onto the last texel.
static inline int CubeTexel(float ratio)
{
	return (int)((ratio + 1.0f) * 256.0f);
}

// @ 0x00f5dbb0
void WriteParticleQuadsHeight(EmitterContext* ctx, VertexWriter* writer, const VertexFormat* format)
{
	const uint16_t* heights = ctx->mpHeightMap->mpData;
	EffectDescription* desc = ctx->mpCurrent;
	DrawParams dp;
	BuildDrawParams(ctx, desc, &dp);

	Particle* p = ctx->mpParticles;
	const uint32_t nAlpha = SegmentCount(desc->mAlphaCurve);
	const uint32_t nSize = SegmentCount(desc->mSizeCurve);
	const uint32_t nUnused = SegmentCount(desc->mUnusedCurve);
	const uint32_t nRot = SegmentCount(desc->mRotationCurve);
	const uint32_t nColor = SegmentCount(desc->mColorCurve);

	int remaining = ctx->mParticleCount;
	while (remaining > 0)
	{
		char* data;
		int stride;
		int n = writer->Lock(remaining, &data, &stride);
		remaining -= n;
		if (n > 0)
		{
			do
			{
				const float t = p->mAge / p->mLifetime;
				(void)SampleCurve(desc->mUnusedCurve, nUnused, t);

				float size = p->mSize * ctx->mSizeScale * SampleCurve(desc->mSizeCurve, nSize, t);
				float angle = p->mRotation * SampleCurve(desc->mRotationCurve, nRot, t) + desc->mRotationOffset;

				Vector3 c = SampleCurve(desc->mColorCurve, nColor, t);
				float red = ctx->mColorScale[0] * (p->mColor[0] * c.x);
				float green = p->mColor[1] * c.y * ctx->mColorScale[1];
				float blue = p->mColor[2] * c.z * ctx->mColorScale[2];

				float alpha = p->mAlpha * ctx->mAlphaScale * SampleCurve(desc->mAlphaCurve, nAlpha, t);

				float x = p->mPos[0];
				float y = p->mPos[1];
				float z = p->mPos[2];
				if (ctx->mFlags & 2)
				{
					float tx = ctx->mRotation[2][0] * z + ctx->mRotation[1][0] * y + x * ctx->mRotation[0][0];
					float ty = ctx->mRotation[2][1] * z + ctx->mRotation[1][1] * y + ctx->mRotation[0][1] * x;
					float tz = ctx->mRotation[2][2] * z + ctx->mRotation[1][2] * y + ctx->mRotation[0][2] * x;
					x = tx; y = ty; z = tz;
				}
				const float px = ctx->mOrigin[0] + ctx->mScale * x;
				const float py = ctx->mOrigin[1] + ctx->mScale * y;
				const float pz = ctx->mOrigin[2] + ctx->mScale * z;
				float quadSize = ctx->mScale * size;

				// Fade alpha and size toward the screen edge.
				if (desc->mScreenEdgeFade)
				{
					const ScreenPoint sp = ProjectToScreen(ctx->mpCamera->m, px, py, pz);
					float sx = sp.x;
					float sy = sp.y;
					float ay = fabsf(sy);
					float ax = fabsf(sx);
					float edge = 1.0f - MaxRef(ay, ax);
					if (edge > 0.0f)
					{
						float a;
						if (dp.invertEdgeFade)
							a = (1.0f - edge) * dp.edgeAlphaSlope + dp.edgeAlphaBase;
						else
							a = dp.edgeAlphaSlope * edge + dp.edgeAlphaBase;
						alpha = MinRef(a, 1.0f) * alpha;
						float s = dp.edgeSizeSlope * edge + dp.edgeSizeBase;
						quadSize = MinRef(s, 1.0f) * quadSize;
					}
					else
					{
						alpha = dp.edgeAlphaBase * alpha;
						quadSize = dp.edgeSizeBase * quadSize;
					}
				}

				const uint8_t r8 = ToByte(red);
				const uint8_t g8 = ToByte(green);
				const uint8_t b8 = ToByte(blue);
				const uint8_t a8 = ToByte(alpha);
				const uint32_t color = ((((uint32_t)a8 << 8 | r8) << 8 | g8) << 8) | b8;

				// Quad direction: the second axis of the draw frame, rotated by the particle angle in the frame plane.
				float dx = dp.axis1.x;
				float dy = dp.axis1.y;
				float dz = dp.axis1.z;
				if (fabsf(angle) > 9.99999997e-07f)
				{
					float a = g_angleScale * angle;
					float k = a * g_sinCosTableScale + 12582912.0f;
					int kBits = *(int*)&k;
					int idx = kBits & 0xf;
					float s0 = g_sinCosTable[idx][0];
					float r = a - (float)(kBits - 0x4b400000) * g_sinCosTableStep;
					float c0 = g_sinCosTable[idx][1];
					float sinA = (c0 - r * s0 * 0.5f) * r + s0;
					float cosA = c0 - (r * c0 * 0.5f + s0) * r;
					dx = dp.axis1.x * cosA - dp.axis0.x * sinA;
					dy = dp.axis1.y * cosA - dp.axis0.y * sinA;
					dz = dp.axis1.z * cosA - dp.axis0.z * sinA;
				}
				dx = dx * quadSize;
				dy = dy * quadSize;
				dz = dz * quadSize;

				// Height of the cube-map texel in the direction of the world position.
				const float ax = fabsf(px);
				const float ay = fabsf(py);
				const float az = fabsf(pz);
				int u, v, face;
				if (az >= ax && az >= ay)
				{
					u = CubeTexel(px / pz);
					v = CubeTexel(py / az);
					face = (pz < 0.0f) ? 1 : 0;
				}
				else if (ay >= ax)
				{
					u = CubeTexel(pz / py);
					v = CubeTexel(px / ay);
					face = (py < 0.0f) ? 5 : 4;
				}
				else
				{
					u = CubeTexel(py / px);
					v = CubeTexel(pz / ax);
					face = (px < 0.0f) ? 3 : 2;
				}
				if (u == 512) u = 511;
				if (v == 512) v = 511;
				const float height = (float)((int)heights[(face * 512 + v) * 512 + u] - 0x8000) * 0.0030517578125f;

				const uint32_t corner = (uint32_t)p->mCorner << 24;
				char* vPos = data + format->posOffset;
				char* vDir = data + format->dirOffset;
				char* vColor = data + format->colorOffset;
				char* vCorner = data + format->cornerOffset;
				// Vertex k of the quad: corner code 0, 0xff0000, 0xffff00, 0xff00 (u/v bytes) under the corner byte.
				Store4(vPos, px, py, pz, height);
				Store4(vDir, dx, dy, dz, quadSize);
				*(uint32_t*)vColor = color;
				*(uint32_t*)vCorner = corner;
				vPos += stride; vDir += stride; vColor += stride; vCorner += stride;
				Store4(vPos, px, py, pz, height);
				Store4(vDir, dx, dy, dz, quadSize);
				*(uint32_t*)vColor = color;
				*(uint32_t*)vCorner = corner | 0xff0000;
				vPos += stride; vDir += stride; vColor += stride; vCorner += stride;
				Store4(vPos, px, py, pz, height);
				Store4(vDir, dx, dy, dz, quadSize);
				*(uint32_t*)vColor = color;
				*(uint32_t*)vCorner = corner | 0xffff00;
				vPos += stride; vDir += stride; vColor += stride; vCorner += stride;
				Store4(vPos, px, py, pz, height);
				Store4(vDir, dx, dy, dz, quadSize);
				*(uint32_t*)vColor = color;
				*(uint32_t*)vCorner = corner | 0xff00;
				data += stride * 4;
				p = p->mpNext;
			} while (--n != 0);
		}
		writer->Unlock();
	}
}
