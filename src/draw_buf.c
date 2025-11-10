#include "luavgl.h"
#include "private.h"
#include "rotable.h"

static int luavgl_draw_buf_destroy(lua_State *L)
{
  if (lua_islightuserdata(L, 1)) {
    lv_draw_buf_destroy((lv_draw_buf_t *)lua_touserdata(L, 1));
  } else {
    luaL_argerror(L, 1, "lightuserdata expected");
  }
  return 0;
}

static int luavgl_draw_buf_create(lua_State *L)
{
  uint32_t w = luaL_checkinteger(L, 1);
  uint32_t h = luaL_checkinteger(L, 2);
  lv_color_format_t cf = luaL_checkinteger(L, 3);
  uint32_t stride = luaL_checkinteger(L, 4);
  lv_draw_buf_t *buf = lv_draw_buf_create(w, h, cf, stride);
  lua_pushlightuserdata(L, buf);
  return 1;
}

static void luavgl_draw_arc_set_width(lv_draw_arc_dsc_t *dsc, int width)
{
  dsc->width = width;
}

static void luavgl_draw_arc_set_start_angle(lv_draw_arc_dsc_t *dsc, int angle)
{
  dsc->start_angle = angle;
}

static void luavgl_draw_arc_set_end_angle(lv_draw_arc_dsc_t *dsc, int angle)
{
  dsc->end_angle = angle;
}

static void luavgl_draw_arc_set_radius(lv_draw_arc_dsc_t *dsc, int radius)
{
  dsc->radius = radius;
}

static void luavgl_draw_arc_set_center(lv_draw_arc_dsc_t *dsc, lua_State *L)
{
  lua_getfield(L, -1, "x");
  dsc->center.x = luaL_checkinteger(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, -1, "y");
  dsc->center.y = luaL_checkinteger(L, -1);
  lua_pop(L, 1);
}

static const luavgl_value_setter_t draw_arc_property_table[] = {
    {"width",
     SETTER_TYPE_INT,   {.setter = (setter_int_t)luavgl_draw_arc_set_width}         },
    {"center",
     SETTER_TYPE_STACK, {.setter_stack = (setter_stack_t)luavgl_draw_arc_set_center}},
    {"start_angle",
     SETTER_TYPE_INT,   {.setter = (setter_int_t)luavgl_draw_arc_set_start_angle}   },
    {"end_angle",
     SETTER_TYPE_INT,   {.setter = (setter_int_t)luavgl_draw_arc_set_end_angle}     },
    {"radius",
     SETTER_TYPE_INT,   {.setter = (setter_int_t)luavgl_draw_arc_set_radius}        },
};

static int draw_arc_set_para_cb(lua_State *L, void *ud)
{
  int ret = luavgl_set_property(L, ud, draw_arc_property_table);
  if (ret != 0) {
    LV_LOG_ERROR("failed");
  }
  return ret;
}

static int luavgl_draw_buf_draw_arc(lua_State *L)
{
  lv_draw_buf_t *buf = (lv_draw_buf_t *)lua_touserdata(L, 1);
  luaL_checktype(L, 2, LUA_TTABLE);
  lv_draw_arc_dsc_t dsc;
  lv_draw_arc_dsc_init(&dsc);
  luavgl_iterate(L, 2, draw_arc_set_para_cb, &dsc);
  dsc.color = lv_color_white();
  lv_obj_t *canvas = lv_canvas_create(lv_screen_active());
  lv_canvas_set_draw_buf(canvas, buf);
  lv_canvas_fill_bg(canvas, lv_color_black(), LV_OPA_TRANSP);

  lv_layer_t layer;
  lv_canvas_init_layer(canvas, &layer);

  lv_draw_arc(&layer, &dsc);

  lv_canvas_finish_layer(canvas, &layer);

  lv_obj_delete(canvas);

  return 0;
}

static const struct luaL_Reg luavgl_draw_buf_methods[] = {
    {"destroy", luavgl_draw_buf_destroy},
    {"create", luavgl_draw_buf_create},
    {"drawArc", luavgl_draw_buf_draw_arc},
    {},
};
