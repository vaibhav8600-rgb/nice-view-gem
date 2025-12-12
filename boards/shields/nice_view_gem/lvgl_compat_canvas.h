// SPDX-License-Identifier: MIT
#ifndef NICE_VIEW_GEM_LVGL_COMPAT_CANVAS_H
#define NICE_VIEW_GEM_LVGL_COMPAT_CANVAS_H

#include <lvgl.h>

/*
 * Define the new canvas_* names on older LVGL versions.  If the
 * canvas_draw_* API is not provided by LVGL (i.e. on v8 and earlier),
 * map the new names back to the old lv_canvas_* equivalents.  This
 * allows us to call canvas_draw_* unconditionally in our wrappers.
 */
#ifndef canvas_draw_line
#define canvas_draw_line lv_canvas_draw_line
#endif
#ifndef canvas_draw_rect
#define canvas_draw_rect lv_canvas_draw_rect
#endif
#ifndef canvas_draw_arc
#define canvas_draw_arc lv_canvas_draw_arc
#endif
#ifndef canvas_draw_text
#define canvas_draw_text lv_canvas_draw_text
#endif
#ifndef canvas_fill_bg
#define canvas_fill_bg lv_canvas_fill_bg
#endif

/* Draw a line on a canvas. */
static inline void nice_canvas_draw_line(lv_obj_t *canvas,
                                         const lv_point_t *points,
                                         uint32_t point_cnt,
                                         const lv_draw_line_dsc_t *line_dsc) {
    /* Always call the canvas_* variant; the macro above maps it to
     * lv_canvas_* on older LVGL versions.
     */
    canvas_draw_line(canvas, points, point_cnt, line_dsc);
}

/* Draw a rectangle on a canvas. */
static inline void nice_canvas_draw_rect(lv_obj_t *canvas,
                                         const lv_area_t *coords,
                                         const lv_area_t *clip_area,
                                         const lv_draw_rect_dsc_t *rect_dsc) {
    canvas_draw_rect(canvas, coords, clip_area, rect_dsc);
}

/* Draw an arc on a canvas. */
static inline void nice_canvas_draw_arc(lv_obj_t *canvas,
                                        lv_coord_t x, lv_coord_t y, lv_coord_t r,
                                        int16_t start_angle, int16_t end_angle,
                                        const lv_draw_arc_dsc_t *arc_dsc) {
    canvas_draw_arc(canvas, x, y, r, start_angle, end_angle, arc_dsc);
}

/* Draw text on a canvas. */
static inline void nice_canvas_draw_text(lv_obj_t *canvas,
                                         lv_coord_t x, lv_coord_t y,
                                         lv_coord_t max_width,
                                         const lv_draw_label_dsc_t *label_dsc,
                                         const char *txt) {
    canvas_draw_text(canvas, x, y, max_width, label_dsc, txt);
}

/* Fill the canvas background. */
static inline void nice_canvas_fill_bg(lv_obj_t *canvas,
                                       lv_color_t color, lv_opa_t opa) {
    canvas_fill_bg(canvas, color, opa);
}

#endif /* NICE_VIEW_GEM_LVGL_COMPAT_CANVAS_H */
