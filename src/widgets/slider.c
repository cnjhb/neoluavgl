#include "lauxlib.h"
#include "luavgl.h"
#include "rotable.h"

static int luavgl_slider_create(lua_State *L)
{
  return luavgl_obj_create_helper(L, lv_slider_create);
}

static const rotable_Reg luavgl_sld_methods[] = {
    {},
};

static void luavgl_slider_init(lua_State *L)
{
  luavgl_obj_newmetatable(L, &lv_slider_class, "lv_slider", luavgl_sld_methods);
  lua_pop(L, 1);
}
