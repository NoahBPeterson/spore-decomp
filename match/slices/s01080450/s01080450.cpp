// Havok 3.1.0 base library, part 2 (0x01080450..0x0108136F): hkClass reflection helpers, hkMonitorStream
// init/quit, buffered stream reader/writer, hkClassMember size queries, hkMath::equal, hkTransform math,
// hkVector4 validity checks.
//
// FLOATING POINT: the original is x87. Each expression below keeps the operand order and the grouping the
// asm uses (it is NOT the grouping Ghidra prints: the asm sums the z-term first). Intermediates live on the
// FPU stack with no stores; they are marked // X87-PRECISION: for the difftest pass.
#include "../s0107e670/hk31_base.h"
#include <math.h>
#include <string.h>

// @ 0x01080450
hkBool hkClass::hasVtable() const
{
	const hkClass* c = this;
	while (c->m_parent != 0)
		c = c->m_parent;
	return c->m_numImplementedInterfaces != 0;   // field doubles as "has vtable" in this Havok version
}

// @ 0x01080480
void hkMonitorStream::init()
{
	TlsSetValue(g_hkMonitorTlsOwnsBuf, 0);
	TlsSetValue(g_hkMonitorTlsStart, 0);
	TlsSetValue(g_hkMonitorTlsAC, 0);
	TlsSetValue(g_hkMonitorTlsCurrent, 0);
	TlsSetValue(g_hkMonitorTlsEnd, 0);
}

// @ 0x010804c0
void hkMonitorStream::quit()
{
	if (TlsGetValue(g_hkMonitorTlsStart) != 0)
	{
		if (TlsGetValue(g_hkMonitorTlsOwnsBuf) != 0)
			hkMemory::s_instance->deallocate(TlsGetValue(g_hkMonitorTlsStart));
	}
	TlsSetValue(g_hkMonitorTlsOwnsBuf, 0);
	TlsSetValue(g_hkMonitorTlsStart, 0);
	TlsSetValue(g_hkMonitorTlsAC, 0);
	TlsSetValue(g_hkMonitorTlsCurrent, 0);
	TlsSetValue(g_hkMonitorTlsEnd, 0);
}

// @ 0x01080540
void hkBufferedStreamReader::prepareBufferForRefill()
{
	int markPos = m_markPos;
	int shift = 0;
	if (markPos < 0)
	{
		m_current = 0;
		m_end = 0;
		return;
	}
	int size = m_current - markPos;
	if (m_markLimit < size)
	{
		// Mark limit exceeded: drop the mark.
		m_current = 0;
		m_end = 0;
		m_markPos = -1;
		m_markLimit = -1;
		return;
	}
	if (markPos > 0)
	{
		// Slide the marked bytes to the start, keeping the buffer 512-byte aligned at the end of the data.
		int rem = size % 512;
		if (rem != 0)
			shift = 512 - rem;
		memmove(m_buf + shift, m_buf + markPos, size);
		int filled = ((rem != 0 ? 1 : 0) + size / 512) * 512;
		m_markPos = shift;
		m_current = filled;
		m_end = filled;
	}
}

// @ 0x010805e0
hkResult hkBufferedStreamReader::refillBuffer()
{
	if (!m_stream->isOk())
		return HK_FAILURE;
	prepareBufferForRefill();
	int toRead = m_bufSize - m_end;
	int total = 0;
	if (toRead > 0)
	{
		do
		{
			int n = m_stream->read(m_buf + m_current, toRead);
			total += n;
			m_end += n;
			if (n != toRead)
				return total == 0 ? HK_FAILURE : HK_SUCCESS;
		} while (total < toRead);
	}
	return HK_SUCCESS;
}

// @ 0x01080650
int hkBufferedStreamReader::read(void* buf, int nbytes)
{
	int cur = m_current;
	int avail = m_end - cur;
	int left = nbytes;
	if (avail < nbytes)
	{
		do
		{
			hkString::memCpy(buf, m_buf + cur, avail);
			m_current += avail;
			buf = (char*)buf + avail;
			left -= avail;
			if (refillBuffer() != HK_SUCCESS)
				return nbytes - left;
			cur = m_current;
			avail = m_end - cur;
		} while (avail < left);
	}
	hkString::memCpy(buf, m_buf + m_current, left);
	m_current += left;
	return nbytes;
}

// @ 0x010806e0
int hkBufferedStreamReader::skip(int nbytes)
{
	int avail = m_end - m_current;
	int left = nbytes;
	if (avail < nbytes)
	{
		do
		{
			left -= avail;
			if (refillBuffer() != HK_SUCCESS)
				return nbytes - left;
			avail = m_end - m_current;
		} while (avail < left);
	}
	m_current += left;
	return nbytes;
}

// @ 0x01080730
hkBool hkBufferedStreamReader::isOk() const
{
	if (m_current == m_end)
	{
		if (!m_stream->isOk())
			return false;
	}
	return true;
}

// @ 0x01080770
hkBool hkBufferedStreamReader::markSupported() const
{
	return m_bufSize != 0;
}

// @ 0x01080790
hkResult hkBufferedStreamReader::setMark(int markLimit)
{
	m_markPos = m_current;
	m_markLimit = markLimit;
	return m_bufSize < markLimit ? HK_FAILURE : HK_SUCCESS;
}

// @ 0x010807b0
hkResult hkBufferedStreamReader::rewindToMark()
{
	if (m_markPos >= 0)
	{
		m_current = m_markPos;
		return HK_SUCCESS;
	}
	return HK_FAILURE;
}

// @ 0x010807d0
hkBool hkBufferedStreamReader::seekTellSupported() const
{
	return m_stream->seekTellSupported();
}

// @ 0x010807f0
hkResult hkBufferedStreamReader::seek(int offset, SeekWhence whence)
{
	m_markPos = -1;
	m_markLimit = -1;
	m_current = 0;
	m_end = 0;
	return m_stream->seek(offset, whence);
}

// @ 0x01080810
int hkBufferedStreamReader::tell() const
{
	int t = m_stream->tell();
	if (t >= 0)
		return (m_current - m_end) + t;
	return -1;
}

// @ 0x01080830
hkBufferedStreamReader::hkBufferedStreamReader(hkStreamReader* s, int bufSize)
{
	m_stream = s;
	m_buf = (char*)hkMemory::s_instance->alignedAllocate(0x40, bufSize, HK_MEMORY_CLASS_STREAM);
	m_current = 0;
	m_end = 0;
	m_bufSize = bufSize;
	m_markPos = -1;
	m_markLimit = -1;
	m_stream->addReference();
}

// @ 0x01080890 (scalar deleting destructor)
hkBufferedStreamReader::~hkBufferedStreamReader()
{
	m_stream->removeReference();
	hkMemory::s_instance->alignedDeallocate(m_buf);
}

// @ 0x010808f0
int hkStreamReader::skip(int nbytes)
{
	char scratch[512];
	int left = nbytes;
	while (left != 0)
	{
		int chunk = 0x200;
		if (left < 0x201)
			chunk = left;
		int n = read(scratch, chunk);
		if (n == 0)
			break;
		left -= n;
	}
	return nbytes - left;
}

// @ 0x01080950
int hkBufferedStreamWriter::flushBuffer()
{
	if (m_stream == 0)
		return 0;
	int n = m_current;
	int done = 0;
	if (n > 0)
	{
		do
		{
			int w = m_stream->write(m_buf + done, n - done);
			done += w;
			if (w == 0)
				return done;
		} while (done < n);
	}
	m_current = 0;
	return done;
}

// @ 0x010809a0
int hkBufferedStreamWriter::write(const void* buf, int nbytes)
{
	int space = m_bufSize - m_current;
	int left = nbytes;
	if (space < nbytes)
	{
		do
		{
			hkString::memCpy(m_buf + m_current, buf, space);
			buf = (const char*)buf + space;
			int filled = m_current + space;
			left -= space;
			space = 0;
			m_current = filled;
			if (m_stream != 0)
			{
				// Inlined flushBuffer(): push the whole buffer through to the wrapped writer.
				if (filled > 0)
				{
					do
					{
						int w = m_stream->write(m_buf + space, filled - space);
						space += w;
						if (w == 0)
							goto flushDone;
					} while (space < filled);
				}
				m_current = 0;
			}
flushDone:
			if (space != filled)
				return nbytes - left;
			space = m_bufSize - m_current;
		} while (space < left);
	}
	hkString::memCpy(m_buf + m_current, buf, left);
	m_current += left;
	return nbytes;
}

// @ 0x01080a60
void hkBufferedStreamWriter::flush()
{
	flushBuffer();
	if (m_stream != 0)
		m_stream->flush();
}

// @ 0x01080a80
hkBool hkBufferedStreamWriter::isOk() const
{
	if (m_stream != 0)
		return m_stream->isOk();
	return m_current != m_bufSize;
}

// @ 0x01080ac0
hkBool hkBufferedStreamWriter::seekTellSupported() const
{
	return m_stream->seekTellSupported();
}

// @ 0x01080ae0
hkResult hkBufferedStreamWriter::seek(int offset, SeekWhence whence)
{
	if (m_stream != 0)
	{
		flushBuffer();
		return m_stream->seek(offset, whence);
	}
	int pos = offset;
	if (whence != 0)
	{
		if (whence == 1)
		{
			pos = m_current + offset;
		}
		else
		{
			pos = -1;
			if (whence == 2)
				pos = m_current - offset;
		}
	}
	if (pos >= 0)
	{
		int cap = m_bufSize;
		int clamped = pos;
		if (cap < pos)
			clamped = cap;
		m_current = clamped;
		return cap < pos ? HK_FAILURE : HK_SUCCESS;
	}
	m_current = 0;
	return HK_FAILURE;
}

// @ 0x01080b50
int hkBufferedStreamWriter::tell() const
{
	int t = m_stream->tell();
	if (t >= 0)
		return m_current + t;
	return -1;
}

// @ 0x01080b70
hkBufferedStreamWriter::hkBufferedStreamWriter(void* buf, int bufSize, hkBool nullTerminate)
{
	m_stream = 0;
	m_buf = (char*)buf;
	m_current = 0;
	int cap = bufSize - 1;
	if (!nullTerminate)
		cap = bufSize;
	m_bufSize = cap;
	m_ownBuf = false;
	if (nullTerminate)
		hkString::memSet(buf, 0, bufSize);
}

// @ 0x01080bd0
hkBufferedStreamWriter::~hkBufferedStreamWriter()
{
	flushBuffer();
	if (m_stream != 0)
		m_stream->flush();
	if (m_stream != 0)
		m_stream->removeReference();
	if (m_ownBuf)
		hkMemory::s_instance->alignedDeallocate(m_buf);
}

// @ 0x01080c30
hkBufferedStreamWriter::hkBufferedStreamWriter(hkStreamWriter* s, int bufSize)
{
	m_stream = s;
	m_ownBuf = true;
	if (m_stream != 0)
		m_stream->addReference();
	void* buf = hkMemory::s_instance->alignedAllocate(0x40, bufSize, HK_MEMORY_CLASS_STREAM);
	m_bufSize = bufSize;
	m_buf = (char*)buf;
	m_current = 0;
}

// @ 0x01080cc0
hkUint64 hkGetCurrentThreadId()
{
	return (hkUint64)GetCurrentThreadId();
}

// @ 0x01080cd0
int hkClassMember::getCstyleArraySize() const
{
	return m_cArraySize;
}

// @ 0x01080ce0
int hkClassMember::getSizeInBytes() const
{
	int result = -1;
	switch (m_type)
	{
	case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11:
	case 12: case 13: case 14: case 15: case 16: case 17: case 18:
	case TYPE_POINTER: case TYPE_FUNCTIONPOINTER: case TYPE_ARRAY:
	case TYPE_SIMPLEARRAY: case TYPE_HOMOGENEOUSARRAY: case TYPE_VARIANT:
	{
		int n = m_cArraySize;
		if (n == 0)
			n = 1;
		return s_classMemberTypeProperties[m_type].m_size * n;
	}
	case TYPE_ZERO:
		return s_classMemberTypeProperties[m_subtype].m_size;
	case TYPE_ENUM:
	{
		int n = m_cArraySize;
		if (n == 0)
			n = 1;
		int bits = (int)m_flags * n;   // enum storage size in bits
		return bits / 8;
	}
	case TYPE_STRUCT:
	{
		int n = m_cArraySize;
		if (n == 0)
			n = 1;
		return m_class->getObjectSize() * n;
	}
	}
	return result;
}

// @ 0x01080db0
int hkClassMember::getAlignment() const
{
	if (m_type == TYPE_ENUM)
		return (int)(m_flags >> 3);
	if (m_type == TYPE_ZERO)
		return s_classMemberTypeProperties[m_subtype].m_align;
	if (m_type == TYPE_STRUCT)
	{
		int align = 1;
		int i = 0;
		if (m_class->getNumMembers() > 0)
		{
			do
			{
				if (align < m_class->getMember(i).getAlignment())
					align = m_class->getMember(i).getAlignment();
				i++;
			} while (i < m_class->getNumMembers());
		}
		return align;
	}
	return s_classMemberTypeProperties[m_type].m_align;
}

// @ 0x01080e40
hkBool hkMath::equal(float a, float b, float eps)
{
	// X87-PRECISION: (a - b) stays unrounded in an 80-bit register before fabs and the compare with eps.
	if (fabsf(a - b) < eps)
		return true;
	return false;
}

// Havok's hkVector4 is 16-byte aligned (the caller's frame does `and esp,-16`); this stand-in carries the
// two inline setters setInverse uses. setRotatedDir leaves w alone: setInverse zeroes it afterwards.
struct __declspec(align(16)) hkVector4A
{
	float x, y, z, w;
	__forceinline void setNeg4(const float* v) { x = -v[0]; y = -v[1]; z = -v[2]; w = -v[3]; }
	__forceinline void setRotatedDir(const float* r, const hkVector4A& v)
	{
		x = v.z * r[8]  + v.y * r[4] + v.x * r[0];
		y = v.z * r[9]  + v.y * r[5] + v.x * r[1];
		z = v.z * r[10] + v.y * r[6] + v.x * r[2];
	}
};

// @ 0x01080e70
void hkTransform::setInverse(const hkTransform& t)
{
	((hkRotation*)m)->setTranspose(*(const hkRotation*)t.m);
	hkVector4A tr;
	tr.setNeg4(&t.m[12]);
	((hkVector4A*)&m[12])->setRotatedDir(m, tr);
	m[15] = 0.0f;
}

// @ 0x01080ef0
void hkTransform::setMul(const hkTransform& A, const hkTransform& B)
{
	// A's rotation is read once up front; B's columns are read just before each block; A's translation is
	// read again at the very end (matters when this aliases A).
	float a0 = A.m[0], a1 = A.m[1], a2 = A.m[2];
	float a4 = A.m[4], a5 = A.m[5], a6 = A.m[6];
	float a8 = A.m[8], a9 = A.m[9], a10 = A.m[10];
	float b0, b1, b2;

	// X87-PRECISION: every sum of three products below is evaluated on the FPU stack and rounded only at the store.
	b0 = B.m[0]; b1 = B.m[1]; b2 = B.m[2];
	m[0] = (a8 * b2 + a4 * b1) + a0 * b0;
	m[1] = (a5 * b1 + a9 * b2) + a1 * b0;
	m[2] = (a10 * b2 + a6 * b1) + a2 * b0;
	m[3] = 0.0f;

	b0 = B.m[4]; b1 = B.m[5]; b2 = B.m[6];
	m[4] = (a8 * b2 + a4 * b1) + a0 * b0;
	m[5] = (a5 * b1 + a9 * b2) + a1 * b0;
	m[6] = (a10 * b2 + a6 * b1) + a2 * b0;
	m[7] = 0.0f;

	b0 = B.m[8]; b1 = B.m[9]; b2 = B.m[10];
	m[8] = (a8 * b2 + a4 * b1) + a0 * b0;
	m[9] = (a5 * b1 + a9 * b2) + a1 * b0;
	m[10] = (a10 * b2 + a6 * b1) + a2 * b0;
	m[11] = 0.0f;

	b0 = B.m[12]; b1 = B.m[13]; b2 = B.m[14];
	m[12] = (a8 * b2 + a4 * b1) + a0 * b0;
	m[13] = (a5 * b1 + a9 * b2) + a1 * b0;
	m[14] = (a10 * b2 + a6 * b1) + a2 * b0;
	m[15] = 0.0f;

	m[12] = m[12] + A.m[12];
	m[13] = A.m[13] + m[13];
	m[14] = A.m[14] + m[14];
	m[15] = A.m[15] + m[15];
}

// @ 0x010810f0
void hkTransform::setMulInverseMul(const hkTransform& A, const hkTransform& B)
{
	float a0 = A.m[0], a1 = A.m[1], a2 = A.m[2];
	float a4 = A.m[4], a5 = A.m[5], a6 = A.m[6];
	float a8 = A.m[8], a9 = A.m[9], a10 = A.m[10];
	float b0, b1, b2;

	// X87-PRECISION: every sum of three products below is evaluated on the FPU stack and rounded only at the store.
	b0 = B.m[0]; b1 = B.m[1]; b2 = B.m[2];
	m[0] = (a2 * b2 + a1 * b1) + a0 * b0;
	m[1] = (a6 * b2 + a5 * b1) + a4 * b0;
	m[2] = (a10 * b2 + a9 * b1) + a8 * b0;
	m[3] = 0.0f;

	b0 = B.m[4]; b1 = B.m[5]; b2 = B.m[6];
	m[4] = (a2 * b2 + a1 * b1) + a0 * b0;
	m[5] = (a6 * b2 + a5 * b1) + a4 * b0;
	m[6] = (a10 * b2 + a9 * b1) + a8 * b0;
	m[7] = 0.0f;

	b0 = B.m[8]; b1 = B.m[9]; b2 = B.m[10];
	m[8] = (a2 * b2 + a1 * b1) + a0 * b0;
	m[9] = (a6 * b2 + a5 * b1) + a4 * b0;
	m[10] = (a10 * b2 + a9 * b1) + a8 * b0;
	m[11] = 0.0f;

	// Translation: A and B are read again from memory here (the original does not reuse the early loads).
	float d0 = B.m[12] - A.m[12];
	float d1 = B.m[13] - A.m[13];
	float d2 = B.m[14] - A.m[14];
	m[12] = (d1 * A.m[1] + d2 * A.m[2]) + d0 * A.m[0];
	m[13] = (d2 * A.m[6] + d1 * A.m[5]) + d0 * A.m[4];
	m[14] = (d2 * A.m[10] + d1 * A.m[9]) + d0 * A.m[8];
	m[15] = 0.0f;
}

// @ 0x010812b0
hkBool hkVector4::isOk3() const
{
	const float* v = &x;
	int i = 0;
	do
	{
		// The original round-trips each component through fld/fstp before looking at the bits.
		hkUint32 bits;
		memcpy(&bits, &v[i], sizeof(bits));
		if ((bits & 0x7f800000) == 0x7f800000)
			return false;
		i++;
	} while (i < 3);
	return true;
}

// @ 0x010812f0
hkBool hkVector4::isNormalized3(float epsilon) const
{
	if (!isOk3())
		return false;
	// X87-PRECISION: (x*x + y*y) + z*z - 1.0 is formed on the FPU stack, then fabs and compare against epsilon.
	if (fabsf(((x * x + y * y) + z * z) - 1.0f) < epsilon)
		return true;
	return false;
}

// @ 0x01081360
void hkVector4::setTransformedPos(const hkTransform& t, const hkVector4& p)
{
	float a = p.x;
	float b = p.y;
	float c = p.z;
	// X87-PRECISION: z term first, then y, then x, then the translation, all on the FPU stack; rounded at the store.
	x = ((c * t.m[8] + b * t.m[4]) + a * t.m[0]) + t.m[12];
	y = ((c * t.m[9] + b * t.m[5]) + a * t.m[1]) + t.m[13];
	z = ((c * t.m[10] + b * t.m[6]) + a * t.m[2]) + t.m[14];
	w = 0.0f;
}
// --- equivalence checker address annotations
    extern unsigned int g_hkMonitorTlsAC; // 0x016e42ac
    extern unsigned int g_hkMonitorTlsCurrent; // 0x016e42a4
    extern unsigned int g_hkMonitorTlsEnd; // 0x016e42a8

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
