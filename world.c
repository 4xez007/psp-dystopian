#include <pspgu.h>
#include <pspgum.h>
#include "world.h"

float cubeVertices[36*6] = {
    -1,-1,-1, 0xFFFFFFFF,   1,-1,-1, 0xFFFFFFFF,   1, 1,-1, 0xFFFFFFFF,
    -1,-1,-1, 0xFFFFFFFF,   1, 1,-1, 0xFFFFFFFF,  -1, 1,-1, 0xFFFFFFFF,
    -1,-1, 1, 0xFFFFFFFF,   1,-1, 1, 0xFFFFFFFF,   1, 1, 1, 0xFFFFFFFF,
    -1,-1, 1, 0xFFFFFFFF,   1, 1, 1, 0xFFFFFFFF,  -1, 1, 1, 0xFFFFFFFF,
    -1,-1,-1, 0xFFFFFFFF,  -1, 1,-1, 0xFFFFFFFF,  -1, 1, 1, 0xFFFFFFFF,
    -1,-1,-1, 0xFFFFFFFF,  -1, 1, 1, 0xFFFFFFFF,  -1,-1, 1, 0xFFFFFFFF,
     1,-1,-1, 0xFFFFFFFF,   1, 1,-1, 0xFFFFFFFF,   1, 1, 1, 0xFFFFFFFF,
     1,-1,-1, 0xFFFFFFFF,   1, 1, 1, 0xFFFFFFFF,   1,-1, 1, 0xFFFFFFFF,
    -1,-1,-1, 0xFFFFFFFF,  -1,-1, 1, 0xFFFFFFFF,   1,-1, 1, 0xFFFFFFFF,
    -1,-1,-1, 0xFFFFFFFF,   1,-1, 1, 0xFFFFFFFF,   1,-1,-1, 0xFFFFFFFF,
    -1, 1,-1, 0xFFFFFFFF,  -1, 1, 1, 0xFFFFFFFF,   1, 1, 1, 0xFFFFFFFF,
    -1, 1,-1, 0xFFFFFFFF,   1, 1, 1, 0xFFFFFFFF,   1, 1,-1, 0xFFFFFFFF,
};

void drawWorld() {
    sceGumPushMatrix();
    ScePspFVector3 scale = {50.f, 0.1f, 50.f};
    sceGumScale(&scale);
    sceGumDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D,
        36, 0, cubeVertices);
    sceGumPopMatrix();

    for(int i=0; i<10; i++) {
        sceGumPushMatrix();
        ScePspFVector3 pos = { (float)(i*5 - 25), 1.0f, -20.f};
        sceGumTranslate(&pos);
        sceGumDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D,
            36, 0, cubeVertices);
        sceGumPopMatrix();
    }
}
