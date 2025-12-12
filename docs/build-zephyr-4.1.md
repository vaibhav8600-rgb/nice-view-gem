# Building nice-view-gem against ZMK + Zephyr 4.1

The Zephyr 4.1 upgrade in ZMK firmware (see zmkfirmware/zmk#3060) bumped
LVGL to a new major version.  As a result several canvas APIs were
renamed or removed.  This module now provides a compatibility layer
(`lvgl_compat_canvas.h`) so that it will continue to build against
both LVGL v8 and v9.  To verify that everything still compiles cleanly
you can follow the steps below.

1. **Update your west manifest** to pull the latest ZMK main branch and
   reference this fork of `nice-view-gem` as an extra module:

   ```yml
   manifest:
     remotes:
       - name: zmkfirmware
         url-base: https://github.com/zmkfirmware
       - name: m165437
         url-base: https://github.com/vaibhav8600-rgb
     projects:
       - name: zmk
         remote: zmkfirmware
         revision: main
         import: app/west.yml
       - name: nice-view-gem
         remote: m165437
         revision: chore/zmk-zephyr-4-1-lvgl-compat
     self:
       path: config
   ```

2. **Set `ZMK_EXTRA_MODULES`** in your build environment to point to
   the location of the cloned `nice-view-gem` repository.  For
   example, if your workspace layout is `~/zmk` and you cloned this
   module to `~/zmk/nice-view-gem`, then export:

   ```sh
   export ZMK_EXTRA_MODULES=$HOME/zmk/nice-view-gem
   ```

3. **Build a firmware** that uses the `nice_view_gem` shield.  At a
   minimum you should build both halves of a split board to ensure
   none of the widgets reference missing symbols:

   ```sh
   # Example for a Sofle keyboard using nice_nano_v2 controllers
   west build -s app -b nice_nano_v2 -- -DSHIELD="sofle_left nice_view_adapter nice_view_gem"
   west build -s app -b nice_nano_v2 -- -DSHIELD="sofle_right nice_view_adapter nice_view_gem"
   ```

4. **Verify the build succeeds.**  There should be no compiler
   warnings or errors related to missing LVGL symbols such as
   `lv_canvas_draw_*` after applying this patch.

If you encounter any issues, double‑check that your ZMK tree really
includes the PR #3060 changes and that the `nice-view-gem` module is on
the `chore/zmk-zephyr-4-1-lvgl-compat` branch.