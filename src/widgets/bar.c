#include "luavgl.h"
#include "rotable.h"

static int luavgl_bar_create(lua_State *L)
{
  return luavgl_obj_create_helper(L, lv_bar_create);
}

static rotable_Reg luavgl_bar_methods[] = {
    {},
};

static void luavgl_bar_init(lua_State *L)
{
  luavgl_obj_newmetatable(L, &lv_bar_class, "lv_bar", luavgl_bar_methods);
  lua_pop(L, 1);
}
