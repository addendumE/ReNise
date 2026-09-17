#include "lvgl.h"
#include <unistd.h>


#ifdef USE_SDL
#include "lv_drivers/sdl/sdl.h"
#else
#include "lv_drivers/display/sunxifb.h"
#include "lv_drivers/indev/evdev.h"
#endif

#ifdef USE_SDL
lv_disp_t * lv_disp_init()
{
    /*Linux frame buffer device init*/
    sdl_init();


    // Display
    static lv_disp_draw_buf_t draw_buf;
    static lv_color_t buf1[SDL_HOR_RES * SDL_VER_RES];

    lv_disp_draw_buf_init(&draw_buf, buf1, NULL,
                          sizeof(buf1));

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    disp_drv.hor_res = SDL_HOR_RES;
    disp_drv.ver_res = SDL_VER_RES;
    disp_drv.flush_cb = sdl_display_flush;
    disp_drv.draw_buf = &draw_buf;

    return lv_disp_drv_register(&disp_drv);
}

lv_indev_t * lv_touch_init()
{
     // Input
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);

    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = sdl_mouse_read;

    return lv_indev_drv_register(&indev_drv);
}

#else
lv_disp_t * lv_disp_init(uint32_t rotated)
{
    /*Linux frame buffer device init*/
    sunxifb_init(rotated);

    /*A buffer for LittlevGL to draw the screen's content*/
    static uint32_t width, height;
    sunxifb_get_sizes(&width, &height);

    static lv_color_t *buf;
    buf = (lv_color_t*) sunxifb_alloc(width * height * sizeof(lv_color_t),
            (char *) "renise");

    if (buf == NULL) {
        sunxifb_exit();
        return nullptr;
    }

    /*Initialize a descriptor for the buffer*/
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, width * height);

    /*Initialize and register a display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf   = &disp_buf;
    disp_drv.flush_cb   = sunxifb_flush;
    disp_drv.hor_res    = width;
    disp_drv.ver_res    = height;
    disp_drv.rotated    = rotated;
#ifndef USE_SUNXIFB_G2D_ROTATE
    if (rotated != LV_DISP_ROT_NONE)
        disp_drv.sw_rotate = 1;
#endif
    return lv_disp_drv_register(&disp_drv);
}

lv_indev_t * lv_touch_init()
{
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);                /*Basic initialization*/
    indev_drv.type =LV_INDEV_TYPE_POINTER;        /*See below.*/
    indev_drv.read_cb = evdev_read;               /*See below.*/
    /*Register the driver in LVGL and save the created input device object*/
    return lv_indev_drv_register(&indev_drv);
}

#endif





int main()
{
    lv_init();
    lv_disp_t *disp = lv_disp_init();
    lv_indev_t *indev = lv_touch_init();
    printf("start\n");
     while (1) {
        lv_timer_handler();
        usleep(5000);
    }

    return 0;
}
