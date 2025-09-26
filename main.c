#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspgu.h>
#include <pspgum.h>
#include <stdlib.h>
#include <math.h>
#include "world.h"

PSP_MODULE_INFO("Dystopia", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4)
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH*SCR_HEIGHT*2)

static unsigned int __attribute__((aligned(16))) list[262144];

int running = 1;
float playerX = 0, playerY = 1.5f, playerZ = 0;
float rotY = 0;

void drawCube(float x, float y, float z) {
    sceGumPushMatrix();
    ScePspFVector3 pos = {x,y,z};
    sceGumTranslate(&pos);
    sceGumScale((ScePspFVector3*)&(ScePspFVector3){0.5f,0.5f,0.5f});
    sceGumDrawArray(GU_TRIANGLES, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D,
        36, 0, cubeVertices);
    sceGumPopMatrix();
}

int main() {
    pspDebugScreenInit();
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    sceGuInit();
    sceGuStart(GU_DIRECT,list);

    sceGuDrawBuffer(GU_PSM_8888,(void*)0,BUF_WIDTH);
    sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,(void*)FRAME_SIZE,BUF_WIDTH);
    sceGuDepthBuffer((void*)(FRAME_SIZE*2),BUF_WIDTH);
    sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
    sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
    sceGuDepthRange(65535,0);
    sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuDepthFunc(GU_GEQUAL);
    sceGuEnable(GU_DEPTH_TEST);
    sceGuShadeModel(GU_SMOOTH);
    sceGuEnable(GU_CULL_FACE);
    sceGuEnable(GU_CLIP_PLANES);
    sceGuEnable(GU_TEXTURE_2D);
    sceGuFinish();
    sceGuSync(0,0);

    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);

    while(running) {
        SceCtrlData pad;
        sceCtrlReadBufferPositive(&pad, 1);

        if(pad.Buttons & PSP_CTRL_START) running = 0;

        float speed = 0.1f;
        if(pad.Buttons & PSP_CTRL_UP) {
            playerX += sinf(rotY) * speed;
            playerZ += cosf(rotY) * speed;
        }
        if(pad.Buttons & PSP_CTRL_DOWN) {
            playerX -= sinf(rotY) * speed;
            playerZ -= cosf(rotY) * speed;
        }
        if(pad.Buttons & PSP_CTRL_LEFT) rotY -= 0.05f;
        if(pad.Buttons & PSP_CTRL_RIGHT) rotY += 0.05f;

        sceGuStart(GU_DIRECT,list);
        sceGuClearColor(0xFF444444);
        sceGuClearDepth(0);
        sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

        sceGumMatrixMode(GU_PROJECTION);
        sceGumLoadIdentity();
        sceGumPerspective(75.0f, (SCR_WIDTH/(float)SCR_HEIGHT), 0.1f, 100.0f);

        sceGumMatrixMode(GU_VIEW);
        sceGumLoadIdentity();
        ScePspFVector3 pos = {0.f,0.f,-3.f};
        sceGumTranslate(&pos);
        sceGumRotateY(rotY);
        sceGumTranslate(&(ScePspFVector3){-playerX,-playerY,-playerZ});

        sceGumMatrixMode(GU_MODEL);
        sceGumLoadIdentity();

        drawWorld();
        drawCube(playerX, playerY, playerZ);

        sceGuFinish();
        sceGuSync(0,0);
        sceDisplayWaitVblankStart();
        sceGuSwapBuffers();
    }

    sceGuTerm();
    sceKernelExitGame();
    return 0;
}
