// 0x00F5CCF0: writes the particles of an effect emitter into a locked vertex buffer, 4 vertices (a quad) per
// particle. Per-particle size, rotation, colour and alpha come from curves of the current effect description
// (ctx+0x24), cross-faded with the next description (ctx+0x28) by ctx+0x38 * 0.5; once the fade reaches 2.0 the
// next description becomes current.
//
// NAMING NOTE: no symbol or PDB type is known for this function or its structures; every name here is
// Claude-coined (marked "(name guessed)"). The draw-parameter record filled by 0x00F5A200 follows the layout
// used in match/slices/s00f5a200. Offsets are the retail 32-bit ones.
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

struct EmitterContext
{
	char pad00[0x18];
	Particle* mpParticles;          // +0x18
	uint32_t pad1c;
	int mParticleCount;             // +0x20
	EffectDescription* mpCurrent;   // +0x24
	EffectDescription* mpNext;      // +0x28
	uint32_t pad2c[2];
	ViewMatrixOwner* mpCamera;      // +0x34
	float mCrossFade;               // +0x38
	char pad3c[0x108 - 0x3c];
	uint32_t mFlags;                // +0x108 (bit 1: transform particle positions by mRotation)
	float mOrigin[3];               // +0x10c
	float mScale;                   // +0x118
	float mRotation[3][3];          // +0x11c
	char pad140[0x19c - 0x140];
	float mSizeScale;               // +0x19c
	float mAlphaScale;              // +0x1a0
	uint32_t pad1a4;
	float mColorScale[3];           // +0x1a8
};

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

// @ 0x00f5ccf0
void WriteParticleQuads(EmitterContext* ctx, VertexWriter* writer, const VertexFormat* format)
{
	EffectDescription* cur = ctx->mpCurrent;
	EffectDescription* next = ctx->mpNext;
	DrawParams dp;
	BuildDrawParams(ctx, cur, &dp);

	const uint32_t nColorA = SegmentCount(cur->mColorCurve);
	const uint32_t nAlphaA = SegmentCount(cur->mAlphaCurve);
	const uint32_t nSizeA = SegmentCount(cur->mSizeCurve);
	const uint32_t nUnusedA = SegmentCount(cur->mUnusedCurve);
	const uint32_t nRotA = SegmentCount(cur->mRotationCurve);
	const float crossFade = ctx->mCrossFade;
	Particle* p = ctx->mpParticles;
	const uint32_t nColorB = SegmentCount(next->mColorCurve);
	const uint32_t nAlphaB = SegmentCount(next->mAlphaCurve);
	const uint32_t nSizeB = SegmentCount(next->mSizeCurve);
	const uint32_t nUnusedB = SegmentCount(next->mUnusedCurve);
	const float wNext = crossFade * 0.5f;

	int remaining = ctx->mParticleCount;
	while (remaining > 0)
	{
		char* data;
		int stride;
		int n = writer->Lock(remaining, &data, &stride);
		remaining -= n;
		if (n > 0)
		{
			const float wCur = 1.0f - wNext;
			do
			{
				const float t = p->mAge / p->mLifetime;
				(void)SampleCurve(cur->mUnusedCurve, nUnusedA, t);
				(void)SampleCurve(next->mUnusedCurve, nUnusedB, t);

				float sizeA = ctx->mSizeScale * SampleCurve(cur->mSizeCurve, nSizeA, t) * p->mSize;
				float size = ctx->mSizeScale * SampleCurve(next->mSizeCurve, nSizeB, t) * p->mSize * wNext + wCur * sizeA;

				float angle = p->mRotation * SampleCurve(cur->mRotationCurve, nRotA, t) + cur->mRotationOffset;

				Vector3 ca = SampleCurve(cur->mColorCurve, nColorA, t);
				float rA = p->mColor[0] * ca.x * ctx->mColorScale[0];
				float gA = ctx->mColorScale[1] * (p->mColor[1] * ca.y);
				float bA = ctx->mColorScale[2] * (p->mColor[2] * ca.z);
				Vector3 cb = SampleCurve(next->mColorCurve, nColorB, t);
				float rB = p->mColor[0] * cb.x * ctx->mColorScale[0];
				float gB = ctx->mColorScale[1] * (p->mColor[1] * cb.y);
				float bB = ctx->mColorScale[2] * (p->mColor[2] * cb.z);
				float red = rB * wNext + rA * wCur;
				float green = gB * wNext + gA * wCur;
				float blue = bB * wNext + bA * wCur;

				float alphaA = SampleCurve(cur->mAlphaCurve, nAlphaA, t) * p->mAlpha * ctx->mAlphaScale;
				float alphaB = SampleCurve(next->mAlphaCurve, nAlphaB, t) * p->mAlpha * ctx->mAlphaScale;
				float alpha = alphaB * wNext + wCur * alphaA;

				float x = p->mPos[0];
				float y = p->mPos[1];
				float z = p->mPos[2];
				if (ctx->mFlags & 2)
				{
					float tx = ctx->mRotation[2][0] * z + ctx->mRotation[1][0] * y + x * ctx->mRotation[0][0];
					float ty = ctx->mRotation[0][1] * x + ctx->mRotation[2][1] * z + ctx->mRotation[1][1] * y;
					float tz = ctx->mRotation[0][2] * x + ctx->mRotation[2][2] * z + ctx->mRotation[1][2] * y;
					x = tx; y = ty; z = tz;
				}
				const float scale = ctx->mScale;
				float quadSize = scale * size;
				const float px = ctx->mOrigin[0] + x * scale;
				const float py = ctx->mOrigin[1] + y * scale;
				const float pz = ctx->mOrigin[2] + z * scale;

				// Fade alpha and size toward the screen edge.
				if (cur->mScreenEdgeFade)
				{
					const float (*m)[4] = ctx->mpCamera->m;
					float sx0 = m[2][0] * pz + m[1][0] * py + m[0][0] * px + m[3][0];
					float sy0 = m[0][1] * px + m[2][1] * pz + m[1][1] * py + m[3][1];
					float w = m[0][3] * px + m[2][3] * pz + m[1][3] * py + m[3][3];
					float invW = 1.0f / w;
					float sy = invW * sy0;
					float sx = invW * sx0;
					float ay = fabsf(sy);
					float ax = fabsf(sx);
					float edge = 1.0f - ((ay > ax) ? ay : ax);
					float sizeFade;
					if (edge > 0.0f)
					{
						float a;
						if (dp.invertEdgeFade)
							a = (1.0f - edge) * dp.edgeAlphaSlope + dp.edgeAlphaBase;
						else
							a = dp.edgeAlphaSlope * edge + dp.edgeAlphaBase;
						alpha = ((1.0f > a) ? a : 1.0f) * alpha;
						float s = dp.edgeSizeSlope * edge + dp.edgeSizeBase;
						sizeFade = (1.0f > s) ? s : 1.0f;
					}
					else
					{
						alpha = dp.edgeAlphaBase * alpha;
						sizeFade = dp.edgeSizeBase;
					}
					quadSize = sizeFade * quadSize;
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
					float a = angle * g_angleScale;
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

				const uint32_t corner = (uint32_t)p->mCorner << 24;
				char* vPos = data + format->posOffset;
				char* vDir = data + format->dirOffset;
				char* vColor = data + format->colorOffset;
				char* vCorner = data + format->cornerOffset;
				// Vertex k of the quad: corner code 0, 0xff0000, 0xffff00, 0xff00 (u/v bytes) under the corner byte.
				Store4(vPos, px, py, pz, t);
				Store4(vDir, dx * quadSize, dy * quadSize, dz * quadSize, quadSize);
				*(uint32_t*)vColor = color;
				*(uint32_t*)vCorner = corner;
				vPos += stride; vDir += stride; vColor += stride; vCorner += stride;
				Store4(vPos, px, py, pz, t);
				Store4(vDir, dx * quadSize, dy * quadSize, dz * quadSize, quadSize);
				*(uint32_t*)vColor = color;
				*(uint32_t*)vCorner = corner | 0xff0000;
				vPos += stride; vDir += stride; vColor += stride; vCorner += stride;
				Store4(vPos, px, py, pz, t);
				Store4(vDir, dx * quadSize, dy * quadSize, dz * quadSize, quadSize);
				*(uint32_t*)vColor = color;
				*(uint32_t*)vCorner = corner | 0xffff00;
				vPos += stride; vDir += stride; vColor += stride; vCorner += stride;
				Store4(vPos, px, py, pz, t);
				Store4(vDir, dx * quadSize, dy * quadSize, dz * quadSize, quadSize);
				*(uint32_t*)vColor = color;
				*(uint32_t*)vCorner = corner | 0xff00;
				data += stride * 4;
				p = p->mpNext;
			} while (--n != 0);
		}
		writer->Unlock();
	}

	if (crossFade >= 2.0f)
	{
		ctx->mpCurrent = ctx->mpNext;
		ctx->mCrossFade = 0.0f;
	}
}
