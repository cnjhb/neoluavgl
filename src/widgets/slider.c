#include "lauxlib.h"
#include "luavgl.h"
#include "rotable.h"

static int luavgl_slider_create(lua_State *L)
{
  return luavgl_obj_create_helper(L, lv_slider_create);
}

static int slider_set_min_value(lua_State *L, lv_obj_t *obj, bool set)
{
  if (set) {
    int32_t val = luaL_checkinteger(L, -1);
    lv_slider_set_min_value(obj, val);
  }
  return 1;
}

static int slider_set_max_value(lua_State *L, lv_obj_t *obj, bool set)
{
  if (set) {
    int32_t val = luaL_checkinteger(L, -1);
    lv_slider_set_max_value(obj, val);
  }
  return 1;
}

static int slider_set_value(lua_State *L, lv_obj_t *obj, bool set)
{
  if (set) {
    int32_t val = luaL_checkinteger(L, -1);
    lv_slider_set_value(obj, val, false);
    return 1;
  }
  lua_pushinteger(L, lv_slider_get_value(obj));
  return 1;
}

static const luavgl_property_ops_t sld_property_ops[] = {
    {.name = "min_value", .ops = slider_set_min_value},
    {.name = "max_value", .ops = slider_set_max_value},
    {.name = "value",     .ops = slider_set_value    },
};

static const luavgl_table_t sld_property_table = {
    .len = sizeof(sld_property_ops) / sizeof(sld_property_ops[0]),
    .array = sld_property_ops};

static const rotable_Reg luavgl_sld_methods[] = {
    {"__property", LUA_TLIGHTUSERDATA, {.ptr = &sld_property_table}},
    {},
};

static void luavgl_slider_init(lua_State *L)
{
  luavgl_obj_newmetatable(L, &lv_slider_class, "lv_slider", luavgl_sld_methods);
  lua_pop(L, 1);
}
