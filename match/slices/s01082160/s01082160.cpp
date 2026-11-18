// @ 0x01082160
#include "../s010eb310/hk31_math.h"
#include <math.h>

namespace hkMath
{
	float acos(float x);   // 0x01082160 (clamped arc cosine)
}

float hkMath::acos(float x)
{
	// |x| >= 1 (or NaN) never reaches the CRT: acos(1) = 0 and the clamped result for the rest is pi.
	if (fabsf(x) >= 1.0f)
	{
		if (x > 0.0f)
			return 0.0f;
		return 3.14159274101257324f;
	}
	return (float)::acos(x);
}
