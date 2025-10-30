// glu replacements cuz glu doesn't work for me
//   ~ gorciu

#include <math.h>
#include <GL/gl.h>

// @madebyai
void perspective(float fovy, float aspect, float znear, float zfar) {
    float f = 1.0f / tan(fovy * 3.14159265f / 360.0f);
    float m[16] = {0};
    m[0] = f / aspect;
    m[5] = f;
    m[10] = (zfar + znear) / (znear - zfar);
    m[11] = -1.0f;
    m[14] = 2.0f * zfar * znear / (znear - zfar);
    glMultMatrixf(m);
}

// @madebyai
void lookAt(float eyeX, float eyeY, float eyeZ,
            float centerX, float centerY, float centerZ,
            float upX, float upY, float upZ) 
{
    float F[3] = { centerX - eyeX, centerY - eyeY, centerZ - eyeZ };
    float fMag = sqrt(F[0]*F[0] + F[1]*F[1] + F[2]*F[2]);
    F[0] /= fMag; F[1] /= fMag; F[2] /= fMag;

    float UP[3] = { upX, upY, upZ };
    float upMag = sqrt(UP[0]*UP[0] + UP[1]*UP[1] + UP[2]*UP[2]);
    UP[0] /= upMag; UP[1] /= upMag; UP[2] /= upMag;

    float S[3] = { 
        F[1]*UP[2] - F[2]*UP[1],
        F[2]*UP[0] - F[0]*UP[2],
        F[0]*UP[1] - F[1]*UP[0]
    };
    float sMag = sqrt(S[0]*S[0] + S[1]*S[1] + S[2]*S[2]);
    S[0] /= sMag; S[1] /= sMag; S[2] /= sMag;

    float U[3] = {
        S[1]*F[2] - S[2]*F[1],
        S[2]*F[0] - S[0]*F[2],
        S[0]*F[1] - S[1]*F[0]
    };

    float M[16] = {
        S[0], U[0], -F[0], 0,
        S[1], U[1], -F[1], 0,
        S[2], U[2], -F[2], 0,
        0,    0,    0,     1
    };

    glMultMatrixf(M);
    glTranslatef(-eyeX, -eyeY, -eyeZ);
}