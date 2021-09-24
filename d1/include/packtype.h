#ifndef PACKINT_H_
#define PACKINT_H_
typedef ubyte pint[4], puint[4], pfix[4];
typedef ubyte pshort[2], pushort[2], pfixang[2];
typedef struct pvms_vector { pfix x, y, z; } pvms_vector;
typedef struct pvms_angvec { pfixang p, b, h; } pvms_angvec;
typedef struct pvms_matrix { pvms_vector rvec, uvec, fvec; } pvms_matrix;
#endif
