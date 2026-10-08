// slice s00fbce30: implicit copy-assignment of a large render-state record (0x2b8 bytes):
// 14 image references, 8 intrusive refcounted objects, then plain scalar fields.
#include "types.h"

struct ImageRef {
  void* mpResource;
  void __thiscall GetImageResource(void* resource);   // 0x00576650 (ref-counted reassign)
};

struct RefCounted {
  virtual int AddRef();
  virtual int Release();
};

template <class T>
struct RefPtr {
  T* mpObject;
  RefPtr& operator=(const RefPtr& o) {
    T* p = o.mpObject;
    T* old = mpObject;
    if (p != old) {
      if (p) p->AddRef();
      mpObject = p;
      if (old) old->Release();
    }
    return *this;
  }
};

struct Quad {
  uint32_t a, b, c, d;
};

struct Mat16 {
  uint32_t m[16];
};

struct RenderState {
  ImageRef images[14];            // +0x00
  RefPtr<RefCounted> refs[8];     // +0x38
  uint32_t w058, w05c, w060, w064, w068, w06c, w070, w074;
  uint32_t w078, w07c, w080, w084, w088, w08c, w090, w094;
  uint32_t w098, w09c, w0a0, w0a4, w0a8, w0ac, w0b0, w0b4;
  uint32_t w0b8, w0bc, w0c0, w0c4, w0c8, w0cc, w0d0, w0d4;
  uint32_t w0d8, w0dc, w0e0, w0e4, w0e8, w0ec, w0f0, w0f4;
  uint32_t w0f8, w0fc, w100, w104, w108, w10c, w110, w114;
  uint32_t w118, w11c, w120, w124, w128, w12c, w130, w134;
  uint32_t w138, w13c, w140, w144, w148, w14c, w150, w154;
  uint32_t w158, w15c, w160, w164, w168, w16c, w170, w174;
  uint32_t w178, w17c, w180, w184;
  Mat16 matrix;            // +0x188
  uint32_t w1c8, w1cc, w1d0, w1d4, w1d8, w1dc, w1e0, w1e4;
  uint32_t w1e8, w1ec, w1f0, w1f4, w1f8, w1fc, w200, w204;
  uint32_t w208, w20c, w210, w214, w218, w21c, w220, w224;
  uint32_t w228, w22c, w230, w234, w238, w23c, w240, w244;
  uint32_t w248, w24c, w250, w254, w258, w25c, w260, w264;
  uint32_t w268, w26c, w270, w274, w278, w27c, w280, w284;
  uint32_t w288, w28c, w290, w294, w298, w29c, w2a0, w2a4;
  Quad tail;                      // +0x2a8
  RenderState& operator=(const RenderState& o);
};

// @ 0x00fbce30
RenderState& RenderState::operator=(const RenderState& o) {
  images[0].GetImageResource(o.images[0].mpResource);
  images[1].GetImageResource(o.images[1].mpResource);
  images[2].GetImageResource(o.images[2].mpResource);
  images[3].GetImageResource(o.images[3].mpResource);
  images[4].GetImageResource(o.images[4].mpResource);
  images[5].GetImageResource(o.images[5].mpResource);
  images[6].GetImageResource(o.images[6].mpResource);
  images[7].GetImageResource(o.images[7].mpResource);
  images[8].GetImageResource(o.images[8].mpResource);
  images[9].GetImageResource(o.images[9].mpResource);
  images[10].GetImageResource(o.images[10].mpResource);
  images[11].GetImageResource(o.images[11].mpResource);
  images[12].GetImageResource(o.images[12].mpResource);
  images[13].GetImageResource(o.images[13].mpResource);
  refs[0] = o.refs[0];
  refs[1] = o.refs[1];
  refs[2] = o.refs[2];
  refs[3] = o.refs[3];
  refs[4] = o.refs[4];
  refs[5] = o.refs[5];
  refs[6] = o.refs[6];
  refs[7] = o.refs[7];
  w058 = o.w058; w05c = o.w05c; w060 = o.w060; w064 = o.w064;
  w068 = o.w068; w06c = o.w06c; w070 = o.w070; w074 = o.w074;
  w078 = o.w078; w07c = o.w07c; w080 = o.w080; w084 = o.w084;
  w088 = o.w088; w08c = o.w08c; w090 = o.w090; w094 = o.w094;
  w098 = o.w098; w09c = o.w09c; w0a0 = o.w0a0; w0a4 = o.w0a4;
  w0a8 = o.w0a8; w0ac = o.w0ac; w0b0 = o.w0b0; w0b4 = o.w0b4;
  w0b8 = o.w0b8; w0bc = o.w0bc; w0c0 = o.w0c0; w0c4 = o.w0c4;
  w0c8 = o.w0c8; w0cc = o.w0cc; w0d0 = o.w0d0; w0d4 = o.w0d4;
  w0d8 = o.w0d8; w0dc = o.w0dc; w0e0 = o.w0e0; w0e4 = o.w0e4;
  w0e8 = o.w0e8; w0ec = o.w0ec; w0f0 = o.w0f0; w0f4 = o.w0f4;
  w0f8 = o.w0f8; w0fc = o.w0fc; w100 = o.w100; w104 = o.w104;
  w108 = o.w108; w10c = o.w10c; w110 = o.w110; w114 = o.w114;
  w118 = o.w118; w11c = o.w11c; w120 = o.w120; w124 = o.w124;
  w128 = o.w128; w12c = o.w12c; w130 = o.w130; w134 = o.w134;
  w138 = o.w138; w13c = o.w13c; w140 = o.w140; w144 = o.w144;
  w148 = o.w148; w14c = o.w14c; w150 = o.w150; w154 = o.w154;
  w158 = o.w158; w15c = o.w15c; w160 = o.w160; w164 = o.w164;
  w168 = o.w168; w16c = o.w16c; w170 = o.w170; w174 = o.w174;
  w178 = o.w178; w17c = o.w17c; w180 = o.w180; w184 = o.w184;
  matrix = o.matrix;
  w1c8 = o.w1c8; w1cc = o.w1cc; w1d0 = o.w1d0; w1d4 = o.w1d4;
  w1d8 = o.w1d8; w1dc = o.w1dc; w1e0 = o.w1e0; w1e4 = o.w1e4;
  w1e8 = o.w1e8; w1ec = o.w1ec; w1f0 = o.w1f0; w1f4 = o.w1f4;
  w1f8 = o.w1f8; w1fc = o.w1fc; w200 = o.w200; w204 = o.w204;
  w208 = o.w208; w20c = o.w20c; w210 = o.w210; w214 = o.w214;
  w218 = o.w218; w21c = o.w21c; w220 = o.w220; w224 = o.w224;
  w228 = o.w228; w22c = o.w22c; w230 = o.w230; w234 = o.w234;
  w238 = o.w238; w23c = o.w23c; w240 = o.w240; w244 = o.w244;
  w248 = o.w248; w24c = o.w24c; w250 = o.w250; w254 = o.w254;
  w258 = o.w258; w25c = o.w25c; w260 = o.w260; w264 = o.w264;
  w268 = o.w268; w26c = o.w26c; w270 = o.w270; w274 = o.w274;
  w278 = o.w278; w27c = o.w27c; w280 = o.w280; w284 = o.w284;
  w288 = o.w288; w28c = o.w28c; w290 = o.w290; w294 = o.w294;
  w298 = o.w298; w29c = o.w29c; w2a0 = o.w2a0; w2a4 = o.w2a4;
  tail = o.tail;
  return *this;
}
