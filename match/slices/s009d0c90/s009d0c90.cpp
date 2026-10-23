// nSPCreatureAnim dynamics slice s009d0c90.
//
// Toolchain: the shipped module is cl 13.10 (VC .NET 2003) SSE code; this slice is built with
// /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast.
#include "s009d0c90.h"
#include <math.h>

// constant pool referenced by the SSE / x87 math (extern "C" keeps the relocation, the VA comment is
// what the tools bind it to).
extern "C" const float g_animEpsilon_014479b0;   // 0x014479b0  1.0e-6f
extern "C" const float g_animSentinel_014479b4;  // 0x014479b4  1.0e6f
extern "C" const float g_negSentinel_013ef654;   // 0x013ef654  -1.0e6f
extern "C" const float g_half_01471064;          // 0x01471064  0.5f
extern "C" const float g_centi_013eb960;         // 0x013eb960  0.01f
extern "C" const float g_one_01485720;           // 0x01485720  1.0f
extern "C" const float g_twoPi_0155145c;         // 0x0155145c  2*pi

// runtime data (not present in the on-disk image)
extern "C" const float g_dynClampLo_0166c090;    // 0x0166c090
extern "C" const float g_dynClampHi_0166c098;    // 0x0166c098
extern "C" const float g_angleScale_0166c78c;    // 0x0166c78c

// 0x011E0906 is a CRT import thunk taking one double on the stack.
extern "C" double crtFn_011e0906(double x);      // 0x011e0906

// hk-style min/max that yield a reference: the original selects one of the two operands and copies it.
static __inline const float& hkMin2(const float& a, const float& b)
{
    return a > b ? b : a;
}

static __inline const float& hkMax2(const float& a, const float& b)
{
    return a > b ? a : b;
}

// @ 0x009d0c90
float nSPCreatureAnimDynamics::getMaxBoneValue() const
{
    int n = (int)(m_activeBonesEnd - m_activeBones);
    float best = g_animEpsilon_014479b0;
    for (int i = 0; i < n; i++)
    {
        const AnimBone* bone = &m_skeleton->m_bones[m_activeBones[i]];
        float v = bone->m_fieldAC;
        if (v > best)
            best = v;
    }
    return best;
}

// @ 0x009d0db0
float nSPCreatureAnimDynamics::getMinBoneValue() const
{
    int n = (int)(m_activeBonesEnd - m_activeBones);
    float best = g_animSentinel_014479b4;
    for (int i = 0; i < n; i++)
    {
        const AnimBone* bone = &m_skeleton->m_bones[m_activeBones[i]];
        float v = bone->m_fieldAC;
        if (v < best)
            best = v;
    }
    return g_animEpsilon_014479b0 > best ? g_animEpsilon_014479b0 : best;
}

// @ 0x009d0ee0
int nSPCreatureAnimDynamics::findSteepestBone() const
{
    const int* p = m_activeBones;
    int n = (int)(m_activeBonesEnd - m_activeBones);
    const AnimBone* cur = &m_skeleton->m_bones[p[0]];
    float bestDelta = 0.0f;
    int best = -1;
    for (int i = 1; i < n; i++)
    {
        float d = cur->m_fieldAC - m_skeleton->m_bones[p[i]].m_fieldAC;
        if (d > bestDelta)
        {
            bestDelta = d;
            best = i;
        }
        cur = &m_skeleton->m_bones[p[i]];
    }
    return best;
}

// @ 0x009d1050
void nSPCreatureAnimDynamics::destroyLayers()
{
    int n = (int)(m_layersEnd - m_layers);
    for (int i = 0; i < n; i++)
        m_layers[i].destroy();
}

// @ 0x009d1090
void nSPCreatureAnimDynamics::computeBounds(AnimBone** bones)
{
    int n = (int)(m_activeBonesEnd - m_activeBones);

    m_boundMin[0] = g_animSentinel_014479b4;
    m_boundMin[1] = g_animSentinel_014479b4;
    m_boundMin[2] = g_animSentinel_014479b4;
    m_boundMax[0] = g_negSentinel_013ef654;
    m_boundMax[1] = g_negSentinel_013ef654;
    m_boundMax[2] = g_negSentinel_013ef654;
    m_sum[0] = 0.0f;
    m_sum[1] = 0.0f;
    m_sum[2] = 0.0f;

    for (int i = 0; i < n; i++)
    {
        const AnimBone* b = &(*bones)[m_activeBones[i]];
        m_sum[0] += b->m_field7C;
        m_sum[1] += b->m_field80;
        m_sum[2] += b->m_field84;
        m_boundMin[0] = hkMin2(m_boundMin[0], b->m_field7C);
        m_boundMax[0] = hkMax2(b->m_field7C, m_boundMax[0]);
        m_boundMin[1] = hkMin2(m_boundMin[1], b->m_field80);
        m_boundMax[1] = hkMax2(b->m_field80, m_boundMax[1]);
        m_boundMin[2] = hkMin2(m_boundMin[2], b->m_field84);
        m_boundMax[2] = hkMax2(b->m_field84, m_boundMax[2]);
    }

    if (n > 1)
    {
        float inv = 1.0f / (float)n;
        m_sum[0] *= inv;
        m_sum[1] *= inv;
        m_sum[2] *= inv;
    }
    if (fabsf(m_sum[0]) < g_animEpsilon_014479b0)
        m_sum[0] = 0.0f;
    if (fabsf(m_sum[1]) < g_animEpsilon_014479b0)
        m_sum[1] = 0.0f;
    if (fabsf(m_sum[2]) < g_animEpsilon_014479b0)
        m_sum[2] = 0.0f;
}

// @ 0x009d12c0
void nSPCreatureAnimDynamics::getExtentAndCentre(Vec4& extent, Vec4& centre) const
{
    float cx = m_boundMin[0] + m_boundMax[0];
    float cy = m_boundMin[1] + m_boundMax[1];
    float cz = m_boundMin[2] + m_boundMax[2];
    centre.x = cx * 0.5f;
    centre.y = cy * 0.5f;
    centre.z = cz * 0.5f;

    extent.x = m_boundMax[0] - m_boundMin[0];
    extent.y = m_boundMax[1] - m_boundMin[1];
    extent.z = m_boundMax[2] - m_boundMin[2];

    int n = (int)(m_activeBonesEnd - m_activeBones);
    if (extent.x < 0.01f || (n == 2 && extent.y > extent.x))
        extent.x = 0.0f;
    if (extent.y < 0.01f || (n == 2 && extent.x > extent.y))
        extent.y = 0.0f;
}

// @ 0x009d13a0
void nSPCreatureAnimDynamics::resetBoneFields(const AnimPhaseData* data)
{
    m_field60 = 0.0f;
    m_field68 = 0.0f;
    m_field6C = 0.0f;
    m_field70 = 0.0f;
    m_field74 = 0.0f;
    m_field78 = 0.0f;
    m_field7C = 0.0f;
    m_field80 = 0.0f;
    m_field84 = 0.0f;
    m_field88 = 0.0f;
    m_fieldD4 = 0.0f;
    m_fieldD8 = 0.0f;
    m_field98 = 0.0f;

    if (data->m_count != -1)
    {
        int nIdx = (int)(m_activeBonesEnd - m_activeBones);
        int n12 = (int)(data->m_end - data->m_begin);
        int limit = (unsigned)nIdx < (unsigned)n12 ? nIdx : n12;
        if (limit != 0)
        {
            int nLayers = (int)(m_layersEnd - m_layers);
            int used = 0;
            for (int L = 0; L < nLayers; L++)
            {
                AnimDynamicsLayer& layer = m_layers[L];
                int cnt = (int)(layer.m_end - layer.m_begin);
                for (int k = 0; k < cnt; k++)
                {
                    if (used >= n12)
                        break;
                    AnimBone* b = layer.m_begin[k];
                    b->m_field6C = 0.0f;
                    b->m_field70 = 0.0f;
                    b->m_field74 = 0.0f;
                    b->m_field78 = 0.0f;
                    used++;
                }
            }
            m_field64 = 0.0f;
        }
    }

    for (int i = 0; i < 14; i++)
        m_field10[i] = 0.0f;
}

// @ 0x009d15e0
void nSPCreatureAnimDynamics::accumulate(float dt, const AnimPhaseData* data)
{
    m_field60 += data->m_f04 * dt;
    m_field68 += data->m_f44 * dt;
    m_field6C += data->m_f48 * dt;
    m_field70 += data->m_f4c * dt;
    m_field74 += data->m_f50 * dt;
    m_field78 += data->m_f54 * dt;
    m_field7C += data->m_f58 * dt;
    m_field80 += data->m_f5c * dt;
    m_field84 += (g_one_01485720 - data->m_f60 * g_centi_013eb960) * dt;
    m_field88 += data->m_f34 * dt;
    m_fieldD4 += data->m_f38 * dt;
    m_fieldD8 += data->m_f3c * dt;
    m_field98 += data->m_f40 * dt;

    if (data->m_count != -1)
    {
        int nIdx = (int)(m_activeBonesEnd - m_activeBones);
        int n12 = (int)(data->m_end - data->m_begin);
        int limit = (unsigned)nIdx < (unsigned)n12 ? nIdx : n12;
        if (limit != 0)
        {
            int nLayers = (int)(m_layersEnd - m_layers);
            int used = 0;
            float sum = 0.0f;
            for (int L = 0; L < nLayers; L++)
            {
                AnimDynamicsLayer& layer = m_layers[L];
                int cnt = (int)(layer.m_end - layer.m_begin);
                for (int k = 0; k < cnt; k++)
                {
                    if (used >= limit)
                        break;
                    AnimBone* b = layer.m_begin[k];
                    float phase = data->m_begin[used].m_angle * g_twoPi_0155145c;
                    b->m_field70 += sinf(phase) * dt;
                    b->m_field74 += cosf(phase) * dt;
                    float w = data->m_begin[used].m_field04 * dt;
                    b->m_field78 += w;
                    sum += w;
                    used++;
                }
            }
            m_field64 += sum / (float)limit;
        }
    }

    m_field10[0] += data->m_f64 * dt;
    m_field10[1] += data->m_f68 * dt;
    m_field10[2] += data->m_f6c * dt;
    m_field10[3] += data->m_f70 * dt;
    m_field10[4] += data->m_f74 * dt;
    m_field10[5] += data->m_f78 * dt;
    m_field10[6] += data->m_f7c * dt;
    m_field10[7] += data->m_f80 * dt;
    m_field10[8] += data->m_f84 * dt;
    m_field10[9] += data->m_f88 * dt;
    m_field10[10] += data->m_f8c * dt;
    m_field10[11] += data->m_f90 * dt;
    m_field10[12] += data->m_f94 * dt;
    m_field10[13] += data->m_f98 * dt;
}

// @ 0x009d19b0
void nSPCreatureAnimDynamics::computeAngles(const AnimPhaseData* data)
{
    float v = m_field64;
    if (v < g_dynClampLo_0166c090)
        v = g_dynClampLo_0166c090;
    if (v > g_dynClampHi_0166c098)
        v = g_dynClampHi_0166c098;
    m_field64 = v;

    if (data->m_count != -1)
    {
        int nIdx = (int)(m_activeBonesEnd - m_activeBones);
        int n12 = (int)(data->m_end - data->m_begin);
        int limit = (unsigned)nIdx < (unsigned)n12 ? nIdx : n12;
        if (limit != 0)
        {
            int nLayers = (int)(m_layersEnd - m_layers);
            int used = 0;
            for (int L = 0; L < nLayers; L++)
            {
                AnimDynamicsLayer& layer = m_layers[L];
                int cnt = (int)(layer.m_end - layer.m_begin);
                for (int k = 0; k < cnt; k++)
                {
                    if (used >= n12)
                        break;
                    AnimBone* b = layer.m_begin[k];
                    float y = b->m_field70;
                    float x = b->m_field74;
                    if (x * x + y * y > g_animEpsilon_014479b0)
                    {
                        float angle = atan2f(y, x) * g_angleScale_0166c78c;
                        b->m_field6C = angle - (float)crtFn_011e0906(angle);
                    }
                    else
                    {
                        b->m_field6C = 0.0f;
                    }
                    used++;
                }
            }
        }
    }
}
