// s009cbee0: nSPCreatureAnim::InitCreatureStaticDataFromResource
// The retail layouts of creature_static_data / creature_body_static_data (size 0x468) differ from the 2008
// PDB tail, so fields are addressed by retail byte offset (verified in the asm) with the PDB names in comments.
#include "types.h"
#include <math.h>

namespace nSPCreatureAnim {

struct creature_static_data;
struct creature_body_static_data;

template <class T> static inline T& at(void* p, int off) { return *(T*)((char*)p + off); }

// thiscall stubs
struct StaticDataStub {
    void Clear(int);              // 0x9c1dc0 creature_static_data::Clear
};
struct BodyStub {
    void Clear();                 // 0x9b3180 creature_body_static_data::Clear
};
struct BodyVecStub {
    void resize(unsigned n);      // 0x9cb840 eastl::vector<creature_body_static_data>::resize
};
struct WiggleVecStub {
    void resize(unsigned n);      // 0x9cb8f0 eastl::vector<creature_body_wiggle_static_data>::resize
};

}  // namespace nSPCreatureAnim

struct PollenKey { uint32_t instance; uint32_t type; uint32_t group; };

// callees (cdecl unless noted)
const wchar_t* __cdecl GetAssetName(PollenKey* key);                         // 0x552580 SP::Pollen::GetAssetName
uint32_t __cdecl InitVerbCollection(uint32_t v);                             // 0x4bb860
int __cdecl Sprintf16(wchar_t* dst, const wchar_t* fmt, ...);                // 0x9399c0
int __cdecl appendW(wchar_t* dst, const wchar_t* src, int cap);              // 0x92cb90
void __cdecl WideToNarrow(const wchar_t* src, char* dst, int cap);           // 0x6b8db0
int __cdecl Snprintf8(char* dst, int cap, const char* fmt, ...);             // 0x9384e0
float* __cdecl matrix_to_quaternion(float* outQuat, float* inMat3x3);        // 0x9a4f10
void __cdecl NormalizeFlags(void* p);                                        // 0x9fc220 (on body+0x150)
float* __cdecl ComputeBodyVector(float* out, void* body, float scale);       // 0x9b53f0
void __cdecl FinishNoBranches(void* sd);                                     // 0x9cbdb0
char __cdecl PostProcess(void* sd);                                          // 0x9c4a30

namespace nSPCreatureAnim {

#define BF(o) at<float>(b, (o))
#define BU(o) at<uint32_t>(b, (o))

// @ 0x9cbee0
char InitCreatureStaticDataFromResource(creature_static_data* sdp, void* res)
{
    char* sd = (char*)sdp;
    uint8_t* r = (uint8_t*)res;
    uint32_t boneMap[255];

    ((StaticDataStub*)sd)->Clear(0);
    at<uint32_t>(sd, 0x318) = at<uint32_t>(r, 8);        // instance_id
    at<uint32_t>(sd, 0x31c) = at<uint32_t>(r, 0x10);     // group_id
    at<uint32_t>(sd, 0x320) = InitVerbCollection(at<uint32_t>(r, 0x18));  // type_id

    PollenKey key;
    key.instance = at<uint32_t>(r, 8);
    key.type = 0x30bdee3;
    uint32_t baseGroup = at<uint32_t>(r, 0x10) & 0xe0ffffff;
    key.group = baseGroup;
    const wchar_t* assetName = GetAssetName(&key);
    if (assetName) {
        const wchar_t* suffix = L"";
        if (baseGroup != at<uint32_t>(r, 0x10)) suffix = L" (baby)";
        Sprintf16((wchar_t*)sd, L"%s%s", assetName, suffix);
    } else {
        appendW((wchar_t*)sd, L"No Pollen Metadata", 0x104);
    }
    WideToNarrow((wchar_t*)sd, sd + 0x208, 0x100);  // filename

    // skin_colors[3] (vector_3 each) at +0x324
    {
        float* src = (float*)(r + 0x38);
        float* dst = (float*)(sd + 0x324);
        for (int i = 3; i != 0; --i) {
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            src += 3;
            dst += 3;
        }
    }

    int numBodies = (at<int>(r, 0x9c) - at<int>(r, 0x98)) / 0x8c;
    char* bodiesVec = sd + 0x384;  // eastl::vector<creature_body_static_data> Bodies (begin at +0x384, end at +0x388)
    ((BodyVecStub*)bodiesVec)->resize(numBodies);

    int meshBones = 0;  // num_bones_with_mesh_parts
    if (numBodies != 0) {
        short s = at<short>(at<char*>(r, 0x98), 4);
        if (s != -1) {
            meshBones = s;
            at<int>(sd, 0x3f0) = 1;
        }
    }
    at<int>(sd, 0x378) = meshBones;
    at<uint8_t>(sd, 0x380) = 0;
    at<uint8_t>(sd, 0x3f5) = at<uint8_t>(r, 0x110) & 1;

    {
        int srcOff = 0;
        for (int i = 0; i < numBodies; ++i) {
            char* sb = at<char*>(r, 0x98) + srcOff;  // source body record, stride 0x8c
            int bidx;
            if (i < meshBones)
                bidx = i + 1;
            else
                bidx = -(int)(i != meshBones) & i;
            char* b = at<char*>(bodiesVec, 0) + bidx * 0x468;
            ((BodyStub*)b)->Clear();
            BU(0x108) = at<uint32_t>(sb, 0x84);  // group_id
            uint32_t instId = at<uint32_t>(sb, 0x88);
            BU(0x104) = instId;                  // instance_id
            uint32_t grpId = BU(0x108);
            BU(0x1f8) = bidx;                    // caps.bidx
            BU(0x21c) = i;                       // source index
            Snprintf8(b, 0x104, "0x%08x!0x%08x.prop", grpId, instId);
            Snprintf8(b + 0x220, 0x104, "joint_b%d_n%d", bidx, (int)at<short>(sb, 2));
            BF(0x424) = 0.0f;                    // mHipHeight__SCALABLE
            BU(0x428) = 0;                       // foot_chain_foot_bidx
            at<uint8_t>(b, 0x42c) = 0;           // foot_chain_root_joint_bidx
            if (at<uint8_t>(sb, 8) & 0x20) BF(0x424) = at<float>(sb, 0x80);
            if (at<uint8_t>(sb, 8) & 0x40) BU(0x428) = at<uint32_t>(sb, 0x80);
            if (at<uint16_t>(sb, 8) & 0x400) at<uint8_t>(b, 0x42c) = 1;
            at<uint8_t>(b, 0x370) = (uint8_t)(~(uint8_t)(at<uint16_t>(sb, 8) >> 9) & 1);  // left_handed
            at<uint8_t>(b, 0x371) = (uint8_t)(at<uint16_t>(sb, 8) >> 0xb) & 1;
            BF(0x378) = at<float>(sb, 0x2c);     // local_joint_r.y
            BF(0x37c) = at<float>(sb, 0x6c);     // local_joint_r.z

            float cz = at<float>(sb, 0x5c);
            float cy = at<float>(sb, 0x58);
            float cx = at<float>(sb, 0x54);
            float scale = at<float>(sb, 0x2c);
            float e0 = at<float>(sb, 0x14) * scale;
            float e1 = at<float>(sb, 0x18) * scale;
            float e2 = at<float>(sb, 0x1c) * scale;
            float e3 = at<float>(sb, 0x20) * scale;
            float e4 = at<float>(sb, 0x24) * scale;
            float e5 = at<float>(sb, 0x28) * scale;

            float m[9];
            m[1] = 0; m[2] = 0; m[3] = 0; m[5] = 0; m[6] = 0; m[7] = 0;
            m[8] = 1.0f; m[4] = 1.0f; m[0] = 1.0f;
            {
                int k = 0, k1;
                float* p = (float*)(sb + 0x38);
                do {
                    k1 = k + 1;
                    m[k] = p[-2];
                    m[k + 3] = p[-1];
                    m[k + 6] = p[0];
                    k = k1;
                    p += 3;
                } while (k1 < 3);
            }
            float qbuf[4];
            float* q = matrix_to_quaternion(qbuf, m);
            BF(0x118) = q[0];  // rest orientation quaternion
            BF(0x11c) = q[1];
            BF(0x120) = q[2];
            BF(0x124) = q[3];

            float qy = BF(0x11c);
            float hx = (e4 + e1) * 0.5f;
            float hy = (e3 + e0) * 0.5f;
            float hz = (e5 + e2) * 0.5f;
            float qw = BF(0x124);
            float qx = BF(0x118);
            float qyqw = qy * qw;
            float qxqw = qx * qw;
            float qz = BF(0x120);
            float qzqw = qz * qw;
            float nqxqx = -(qx * qx);
            float qzqx = qz * qx;
            float qzqy = qz * qy;
            float t = ((((-(qy * qy) + nqxqx) * hz + (qzqy + qxqw) * hx) + (qzqx - qyqw) * hy) * 2.0f + hz) + cz;
            float dz = cz - t;
            BF(0x114) = t;                       // rest_center.z
            t = ((((qzqx + qyqw) * hz + (qy * qx - qzqw) * hx) + (-(qz * qz) + -(qy * qy)) * hy) * 2.0f + hy) + cx;
            float dx = cx - t;
            float ty = ((((-(qz * qz) + nqxqx) * hx + (qzqy - qxqw) * hz) + (qy * qx + qzqw) * hy) * 2.0f + hx) + cy;
            BF(0x10c) = t;                       // rest_center.x
            BF(0x110) = ty;                      // rest_center.y
            float dy = cy - ty;

            qx = BF(0x118);
            qw = BF(0x124);
            float nxw = -(qx * qw);
            qy = BF(0x11c);
            float nyw = -(qy * qw);
            qz = BF(0x120);
            float nxx = -(qx * qx);
            float nzw = -(qz * qw);
            BF(0x144) = (((-(qz * qz) + -(qy * qy)) * dx + (qy * qx - nzw) * dy) + (qz * qx + nyw) * dz) * 2.0f + dx;
            BF(0x148) = (((qy * qx + nzw) * dx + (-(qz * qz) + nxx) * dy) + (qz * qy - nxw) * dz) * 2.0f + dy;
            BF(0x14c) = (((qz * qx - nyw) * dx + (-(qy * qy) + nxx) * dz) + (qz * qy + nxw) * dy) * 2.0f + dz;
            BF(0x138) = (e3 - e0) * 0.5f;
            BF(0x140) = (e5 - e2) * 0.5f;
            BF(0x13c) = (e4 - e1) * 0.5f;
            for (int k = 0x324; k < 0x330; ++k) at<uint8_t>(b, k) = 0;
            float sc = at<float>(sb, 0x2c);
            float px = at<float>(sb, 0x64);
            float py = at<float>(sb, 0x68);
            float* ext = &BF(0x138);
            float yx = BF(0x148);
            float yy = BF(0x14c);
            BF(0x330) = at<float>(sb, 0x60) * sc + BF(0x144);
            BF(0x334) = yx + px * sc;
            BF(0x338) = yy + py * sc;
            for (int k = 3; k != 0; --k) {
                if (*ext <= 0.0f) *ext = 0.1f;
                ++ext;
            }

            uint32_t nApp = at<uint8_t>(sb, 0x10);
            if (nApp != 0) {
                float* fp = &BF(0x158);
                uint32_t k = 0;
                do {
                    *fp = at<float*>(r, 0xac)[at<uint16_t>(sb, 0xc) + k];
                    uint8_t v = at<uint8_t*>(r, 0xc0)[at<uint16_t>(sb, 0xc) + k];
                    ++k;
                    at<uint8_t>(b, 0x1d6 + k) = v;
                    ++fp;
                } while (k < nApp);
            }
            NormalizeFlags(b + 0x150);
            if (BU(0x154) & 4) ++at<int>(sd, 0x3c8);

            uint32_t v = at<uint8_t>(sb, 0xa);
            if (v == 0) v = 0xffffffff;
            BU(0x33c) = v;
            at<uint8_t>(b, 0x340) = at<uint8_t>(sb, 9) & 1;

            uint32_t nMass = at<uint8_t>(sb, 0x11);
            BU(0x380) = (nMass > 8) ? 8 : nMass;
            if (at<uint8_t>(sb, 0x11) != 0) {
                float* fp = &BF(0x38c);
                uint32_t k = 0;
                do {
                    uint16_t base = at<uint16_t>(sb, 0xe);
                    fp[0] = at<float*>(r, 0xe8)[base + k];
                    fp[2] = at<float*>(r, 0xfc)[base + k];
                    float mass = at<float*>(r, 0xd4)[base + k];
                    fp[-2] = mass;
                    if (mass == 0.0f) at<uint8_t>(sd, 0x380) = 1;
                    ++k;
                    fp += 5;
                } while (k < at<uint8_t>(sb, 0x11));
            }

            short parent = at<short>(sb, 4);
            if (parent == -1) {
                BU(0x1fc) = 0xffffffff;
            } else {
                int pi = parent;
                if (pi < meshBones)
                    BU(0x1fc) = pi + 1;
                else
                    BU(0x1fc) = -(int)(pi != meshBones) & pi;
            }
            srcOff += 0x8c;
            BU(0x200) = (int)at<short>(sb, 6);
            BU(0x204) = 0xffffffff;
            BU(0x208) = 0;
            BU(0x36c) = 0x7f7fffffu;  // FLT_MAX
        }
    }

    // second pass: child offsets relative to parents
    if ((unsigned)numBodies != 0) {
        int off = 0;
        unsigned remaining = numBodies;
        do {
            char* begin = at<char*>(bodiesVec, 0);
            char* b = begin + off;
            char* sb = at<char*>(r, 0x98) + BU(0x21c) * 0x8c;
            if (BU(0x1fc) != 0xffffffff) {
                int poff = BU(0x1fc) * 0x468;
                char* pb = begin + poff;
                ++at<int>(pb, 0x208);  // num_children
                float px = at<float>(sb, 0x54);
                float py = at<float>(sb, 0x58);
                float pz = at<float>(sb, 0x5c);
                if (at<uint8_t>(sb, 0xb) == 5 && at<short>(sb, 4) > -1) {
                    char* ps = at<char*>(r, 0x98) + at<short>(sb, 4) * 0x8c;
                    py = (at<float>(ps, 0x58) + py) * 0.5f;
                    pz = (at<float>(ps, 0x5c) + pz) * 0.5f;
                    px = (px + at<float>(ps, 0x54)) * 0.5f;
                }
                float dy = py - at<float>(pb, 0x110);
                float dx = px - at<float>(pb, 0x10c);
                float qy = at<float>(pb, 0x11c);
                float dz = pz - at<float>(pb, 0x114);
                float qw = at<float>(pb, 0x124);
                float qx = at<float>(pb, 0x118);
                float nxw = -(qx * qw);
                float qz = at<float>(pb, 0x120);
                float nxx = -(qx * qx);
                float nzw = -(qz * qw);
                float qzqy = qz * qy;
                float nyw = -(qy * qw);
                at<float>(b, 0x350) = (((qy * qx - nzw) * dy + (qz * qx + nyw) * dz) + (-(qz * qz) + -(qy * qy)) * dx) * 2.0f + dx;
                at<float>(b, 0x354) = (((-(qz * qz) + nxx) * dy + (qzqy - nxw) * dz) + (qy * qx + nzw) * dx) * 2.0f + dy;
                at<float>(b, 0x358) = (((qz * qx - nyw) * dx + (-(qy * qy) + nxx) * dz) + (qzqy + nxw) * dy) * 2.0f + dz;

                float ex = px - at<float>(b, 0x10c);
                float cqy = at<float>(b, 0x124);
                float cqx = at<float>(b, 0x11c);
                float ey = py - at<float>(b, 0x110);
                float ez = pz - at<float>(b, 0x114);
                float cqw = at<float>(b, 0x118);
                float cqz = at<float>(b, 0x120);
                float ncqwy = -(cqw * cqy);
                float ncqzy = -(cqz * cqy);
                float ncqww = -(cqw * cqw);
                float ncqxy = -(cqx * cqy);
                at<float>(b, 0x344) = (((cqx * cqw - ncqzy) * ey + (cqz * cqw + ncqxy) * ez) + (-(cqz * cqz) + -(cqx * cqx)) * ex) * 2.0f + ex;
                at<float>(b, 0x348) = (((-(cqz * cqz) + ncqww) * ey + (cqz * cqx - ncqwy) * ez) + (cqx * cqw + ncqzy) * ex) * 2.0f + ey;
                at<float>(b, 0x34c) = (((-(cqx * cqx) + ncqww) * ez + (cqz * cqx + ncqwy) * ey) + (cqz * cqw - ncqxy) * ex) * 2.0f + ez;

                float tmp[4];
                float* out = ComputeBodyVector(tmp, b, 1.0f);
                at<float>(b, 0x35c) = out[0];
                at<float>(b, 0x360) = out[1];
                at<float>(b, 0x364) = out[2];
                at<float>(b, 0x368) = sqrtf(at<float>(b, 0x35c) * at<float>(b, 0x35c) +
                                                       at<float>(b, 0x360) * at<float>(b, 0x360) +
                                                       at<float>(b, 0x364) * at<float>(b, 0x364));
            }
            off += 0x468;
        } while (--remaining != 0);
    }

    if (at<int>(sd, 0x3c8) == 0 && at<int>(sd, 0x3f0) == 0) FinishNoBranches(sd);
    char ok = PostProcess(sd);
    if (at<uint8_t>(sd, 0x3f4) == 0) at<uint8_t>(sd, 0x3f5) = 0;

    if (ok != 0) {
        unsigned count = (at<int>(bodiesVec, 4) - at<int>(bodiesVec, 0)) / 0x468;
        for (unsigned i = 0; i < count; ++i) {
            // recompute each time like the original
            char* bb = at<char*>(bodiesVec, 0) + i * 0x468;
            uint32_t srcIdx = at<uint32_t>(bb, 0x21c);
            if (srcIdx < 0xff) boneMap[srcIdx] = at<uint32_t>(bb, 0x1f8);
            count = (at<int>(bodiesVec, 4) - at<int>(bodiesVec, 0)) / 0x468;
        }

        unsigned nWig = (at<int>(r, 0x118) - at<int>(r, 0x114)) / 0x38;
        char* wigVec = sd + 0x398;  // eastl::vector<creature_body_wiggle_static_data> mWiggles
        ((WiggleVecStub*)wigVec)->resize(nWig);
        if (nWig != 0) {
            int srcOff = 0;
            int dstOff = 0;
            do {
                float* w = (float*)(at<char*>(r, 0x114) + srcOff);  // source wiggle record, stride 0x38
                uint32_t bi = boneMap[((uint32_t*)w)[0]];
                char* e = at<char*>(wigVec, 0) + dstOff;           // dest wiggle, stride 0x28
                char* sb = at<char*>(r, 0x98) + ((uint32_t*)w)[0] * 0x8c;
                char* b = at<char*>(bodiesVec, 0);
                at<uint32_t>(e, 4) = bi;
                at<uint32_t>(e, 0) = ((uint32_t*)w)[1];
                at<float>(e, 8) = at<float>(sb, 0x2c);
                float sc = at<float>(sb, 0x2c);
                float w3 = w[3];
                float w4 = w[4];
                float by = at<float>(b, bi * 0x468 + 0x148);
                float bz = at<float>(b, bi * 0x468 + 0x14c);
                at<float>(e, 0xc) = at<float>(b, bi * 0x468 + 0x144) + sc * w[2];
                at<float>(e, 0x10) = by + w3 * sc;
                at<float>(e, 0x14) = bz + w4 * sc;

                float m[9];
                m[1] = 0; m[2] = 0; m[3] = 0; m[5] = 0; m[6] = 0; m[7] = 0;
                m[8] = 1.0f; m[4] = 1.0f; m[0] = 1.0f;
                {
                    int k = 0, k1;
                    float* p = w + 7;
                    do {
                        k1 = k + 1;
                        m[k] = p[-2];
                        m[k + 3] = p[-1];
                        m[k + 6] = p[0];
                        k = k1;
                        p += 3;
                    } while (k1 < 3);
                }
                float qbuf[4];
                float* q = matrix_to_quaternion(qbuf, m);
                srcOff += 0x38;
                at<float>(e, 0x18) = q[0];
                dstOff += 0x28;
                at<float>(e, 0x1c) = q[1];
                --nWig;
                at<float>(e, 0x20) = q[2];
                at<float>(e, 0x24) = q[3];
            } while (nWig != 0);
        }
    }
    return ok;
}

}  // namespace nSPCreatureAnim
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct nSPCreatureAnim {
    void resize(unsigned int); // 0x009cb840
    void Clear(); // 0x009b3180
};
}
