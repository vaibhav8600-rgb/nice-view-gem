// SPDX-License-Identifier: MIT
#ifndef NICE_VIEW_GEM_LVGL_COMPAT_CANVAS_H
#define NICE_VIEW_GEM_LVGL_COMPAT_CANVAS_H

#include <lvgl.h>

/* Draw a line on a canvas.  In LVGL 9 the prefix “lv_” was dropped.  */
static inline void nice_canvas_draw_line(lv_obj_t *canvas,
                                         const lv_point_t *points,
                                         uint32_t point_cnt,
                                         const lv_draw_line_dsc_t *line_dsc) {
#if defined(LV_VERSION_MAJOR) && (LV_VERSION_MAJOR >= 9)
    canvas_draw_line(canvas, points, point_cnt, line_dsc);
#else
    lv_canvas_draw_line(canvas, points, point_cnt, line_dsc);
#endif
}

/* Draw a rectangle on a canvas. */
static inline void nice_canvas_draw_rect(lv_obj_t *canvas,
                                         const lv_area_t *coords,
                                         const lv_area_t *clip_area,
                                         const lv_draw_rect_dsc_t *rect_dsc) {
#if defined(LV_VERSION_MAJOR) && (LV_VERSION_MAJOR >= 9)
    canvas_draw_rect(canvas, coords, clip_area, rect_dsc);
#else
    lv_canvas_draw_rect(canvas, coords, clip_area, rect_dsc);
#endif
}

/* Draw an arc on a canvas. */
static inline void nice_canvas_draw_arc(lv_obj_t *canvas,
                                        lv_coord_t x,
                                        lv_coord_t y,
                                        lv_coord_t r,
                                        int16_t start_angle,
                                        int16_t end_angle,
                                        const lv_draw_arc_dsc_t *arc_dsc) {
#if defined(LV_VERSION_MAJOR) && (LV_VERSION_MAJOR >= 9)
    canvas_draw_arc(canvas, x, y, r, start_angle, end_angle, arc_dsc);
#else
    lv_canvas_draw_arc(canvas, x, y, r, start_angle, end_angle, arc_dsc);
#endif
}

/* Draw text on a canvas. */
static inline void nice_canvas_draw_text(lv_obj_t *canvas,
                                         lv_coord_t x,
                                         lv_coord_t y,
                                         lv_coord_t max_width,
                                         const lv_draw_label_dsc_t *label_dsc,
                                         const char *txt) {
#if defined(LV_VERSION_MAJOR) && (LV_VERSION_MAJOR >= 9)
    canvas_draw_text(canvas, x, y, max_width, label_dsc, txt);
#else
    lv_canvas_draw_text(canvas, x, y, max_width, (lv_draw_label_dsc_t *)label_dsc, txt);
#endif
}

/* Fill the canvas background. */
static inline void nice_canvas_fill_bg(lv_obj_t *canvas,
                                       lv_color_t color,
                                       lv_opa_t opa) {
#if defined(LV_VERSION_MAJOR) && (LV_VERSION_MAJOR >= 9)
    canvas_fill_bg(canvas, color, opa);
#else
    lv_canvas_fill_bg(canvas, color, opa);
#endif
}

#endif /* NICE_VIEW_GEM_LVGL_COMPAT_CANVAS_H */
