// s0085f1e0: float AAN forward DCT on an 8x8 block (IJG jfdctflt.c, jpeg_fdct_float),
// used by EA's JPEG encoder (EA framework region). Straight-line SSE code: both passes
// unrolled 8 times.
#include "types.h"

#define DCTSIZE 8

void jpeg_fdct_float(float* data)
{
    float tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    float tmp10, tmp11, tmp12, tmp13;
    float z1, z2, z3, z4, z5, z11, z13;
    float* dataptr;
    int ctr;

    /* Pass 1: process rows. */
    dataptr = data;
    for (ctr = DCTSIZE - 1; ctr >= 0; ctr--) {
        tmp0 = dataptr[0] + dataptr[7];
        tmp7 = dataptr[0] - dataptr[7];
        tmp1 = dataptr[1] + dataptr[6];
        tmp6 = dataptr[1] - dataptr[6];
        tmp2 = dataptr[2] + dataptr[5];
        tmp5 = dataptr[2] - dataptr[5];
        tmp3 = dataptr[3] + dataptr[4];
        tmp4 = dataptr[3] - dataptr[4];

        /* Even part */
        tmp10 = tmp0 + tmp3;
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;

        dataptr[0] = tmp10 + tmp11;
        dataptr[4] = tmp10 - tmp11;

        z1 = (tmp12 + tmp13) * ((float)0.707106781);
        dataptr[2] = tmp13 + z1;
        dataptr[6] = tmp13 - z1;

        /* Odd part */
        tmp10 = tmp4 + tmp5;
        tmp11 = tmp5 + tmp6;
        tmp12 = tmp6 + tmp7;

        z5 = (tmp10 - tmp12) * ((float)0.382683433);
        z2 = ((float)0.541196100) * tmp10 + z5;
        z4 = ((float)1.306562965) * tmp12 + z5;
        z3 = tmp11 * ((float)0.707106781);

        z11 = tmp7 + z3;
        z13 = tmp7 - z3;

        dataptr[5] = z13 + z2;
        dataptr[3] = z13 - z2;
        dataptr[1] = z11 + z4;
        dataptr[7] = z11 - z4;

        dataptr += DCTSIZE;
    }

    /* Pass 2: process columns. */
    dataptr = data;
    for (ctr = DCTSIZE - 1; ctr >= 0; ctr--) {
        tmp0 = dataptr[DCTSIZE * 0] + dataptr[DCTSIZE * 7];
        tmp7 = dataptr[DCTSIZE * 0] - dataptr[DCTSIZE * 7];
        tmp1 = dataptr[DCTSIZE * 1] + dataptr[DCTSIZE * 6];
        tmp6 = dataptr[DCTSIZE * 1] - dataptr[DCTSIZE * 6];
        tmp2 = dataptr[DCTSIZE * 2] + dataptr[DCTSIZE * 5];
        tmp5 = dataptr[DCTSIZE * 2] - dataptr[DCTSIZE * 5];
        tmp3 = dataptr[DCTSIZE * 3] + dataptr[DCTSIZE * 4];
        tmp4 = dataptr[DCTSIZE * 3] - dataptr[DCTSIZE * 4];

        /* Even part */
        tmp10 = tmp0 + tmp3;
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;

        dataptr[DCTSIZE * 0] = tmp10 + tmp11;
        dataptr[DCTSIZE * 4] = tmp10 - tmp11;

        z1 = (tmp12 + tmp13) * ((float)0.707106781);
        dataptr[DCTSIZE * 2] = tmp13 + z1;
        dataptr[DCTSIZE * 6] = tmp13 - z1;

        /* Odd part */
        tmp10 = tmp4 + tmp5;
        tmp11 = tmp5 + tmp6;
        tmp12 = tmp6 + tmp7;

        z5 = (tmp10 - tmp12) * ((float)0.382683433);
        z2 = ((float)0.541196100) * tmp10 + z5;
        z4 = ((float)1.306562965) * tmp12 + z5;
        z3 = tmp11 * ((float)0.707106781);

        z11 = tmp7 + z3;
        z13 = tmp7 - z3;

        dataptr[DCTSIZE * 5] = z13 + z2;
        dataptr[DCTSIZE * 3] = z13 - z2;
        dataptr[DCTSIZE * 1] = z11 + z4;
        dataptr[DCTSIZE * 7] = z11 - z4;

        dataptr++;
    }
}
