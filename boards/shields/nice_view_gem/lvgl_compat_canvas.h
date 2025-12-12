// SPDX-License-Identifier: MIT
//
// Copyright (c) 2025
//
// This header provides a thin compatibility layer around the LVGL canvas
// drawing functions.  Between LVGL v8 and v9 a number of canvas APIs
// were renamed from the `lv_canvas_*` namespace to just `canvas_*` and
// in some cases had their parameter ordering adjusted.  Rather than
// conditionally peppering the codebase with `#if` checks, we define a
// small set of wrapper functions here that delegate to whichever API is
// available at build time.  Future changes to LVGL/ZMK can be
// accommodated by editing this file rather than touching each widget.
//
// The wrappers are defined as `static inline` functions so that the
// compiler can optimise away the indirection when possible.

#ifndef NICE_VIEW_GEM_LVGL_COMPAT_CANVAS_H
#define NICE_VIEW_GEM_LVGL_COMPAT_CANVAS_H

#include <lvgl.h>

/*
 * Wrapper for drawing a line on a canvas.  LVGL v9 renamed
 * `lv_canvas_draw_line()` to `canvas_draw_line()`.  Detect the new
 * symbol and dispatch appropriately.  The function signature is
 * maintained so call sites do not need to change.
 */
static inline void nice_canvas_draw_line(lv_obj_t *canvas,
                                         const lv_point_t *points,
                                         uint32_t point_cnt,
                                         const lv_draw_line_dsc_t *line_dsc) {
#if defined(canvas_draw_line)
    /* LVGL v9+ */
    canvas_draw_line(canvas, points, point_cnt, line_dsc);
#else
    /* LVGL v8 */
    lv_canvas_draw_line(canvas, points, point_cnt, line_dsc);
#endif
}

/*
 * Wrapper for drawing a rectangle on a canvas.  Similar to the line
 * wrapper above, this dispatches to the correct function depending on
 * which LVGL API is available.
 */
static inline void nice_canvas_draw_rect(lv_obj_t *canvas,
                                         const lv_area_t *coords,
                                         const lv_area_t *clip_area,
                                         const lv_draw_rect_dsc_t *rect_dsc) {
#if defined(canvas_draw_rect)
    canvas_draw_rect(canvas, coords, clip_area, rect_dsc);
#else
    lv_canvas_draw_rect(canvas, coords, clip_area, rect_dsc);
#endif
}

/*
 * Wrapper for drawing an arc on a canvas.  LVGL v9 renamed
 * `lv_canvas_draw_arc()` to `canvas_draw_arc()`.
 */
static inline void nice_canvas_draw_arc(lv_obj_t *canvas,
                                        lv_coord_t x,
                                        lv_coord_t y,
                                        lv_coord_t r,
                                        int16_t start_angle,
                                        int16_t end_angle,
                                        const lv_draw_arc_dsc_t *arc_dsc) {
#if defined(canvas_draw_arc)
    canvas_draw_arc(canvas, x, y, r, start_angle, end_angle, arc_dsc);
#else
    lv_canvas_draw_arc(canvas, x, y, r, start_angle, end_angle, arc_dsc);
#endif
}

/*
 * Wrapper for drawing text on a canvas.  LVGL v9 shortened
 * `lv_canvas_draw_text()` to `canvas_draw_text()`.  The arguments
 * remain the same.
 */
static inline void nice_canvas_draw_text(lv_obj_t *canvas,
                                         lv_coord_t x,
                                         lv_coord_t y,
                                         lv_coord_t max_width,
                                         const lv_draw_label_dsc_t *label_dsc,
                                         const char *txt) {
#if defined(canvas_draw_text)
    canvas_draw_text(canvas, x, y, max_width, label_dsc, txt);
#else
    lv_canvas_draw_text(canvas, x, y, max_width, (lv_draw_label_dsc_t *)label_dsc, txt);
#endif
}

/*
 * Wrapper for filling the canvas background.  In LVGL v9 the API was
 * renamed from `lv_canvas_fill_bg()` to `canvas_fill_bg()`.  Some
 * downstream modules may instead call `fill_background()` from util.c
 * which uses style properties.  This wrapper exists for code that
 * still uses the native canvas fill API.
 */
static inline void nice_canvas_fill_bg(lv_obj_t *canvas,
                                       lv_color_t color,
                                       lv_opa_t opa) {
#if defined(canvas_fill_bg)
    canvas_fill_bg(canvas, color, opa);
#else
    lv_canvas_fill_bg(canvas, color, opa);
#endif
}

#endif /* NICE_VIEW_GEM_LVGL_COMPAT_CANVAS_H */