#pragma once

// source: /src/internal/glu.cpp
// description:
//  glu replacements cuz glu doesn't work for me
//    ~ gorciu

extern void perspective(float fovy, float aspect, float znear, float zfar);
extern void lookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);