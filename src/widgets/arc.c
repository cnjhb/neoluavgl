#include "luavgl.h"
#include "private.h"
#include "rotable.h"

static int luavgl_arc_create(lua_State *L)
{
  return luavgl_obj_create_helper(L, lv_arc_create);
}

static int luavgl_arc_rotate_obj_to_angle(lua_State *L)
{
  lv_obj_t *obj = luavgl_to_obj(L, 1), *obj_to_rotate = luavgl_to_obj(L, 2);

  int32_t r_offset = 0;
  if (lua_isinteger(L, 3)) {
    r_offset = lua_tointeger(L, 3);
  }
  lv_arc_rotate_obj_to_angle(obj, obj_to_rotate, r_offset);
  return 0;
}

static const rotable_Reg luavgl_arc_methods[] = {
    {"rotate_obj_to_angle",
     LUA_TFUNCTION, {.ptr = luavgl_arc_rotate_obj_to_angle}},
    {},
};

static void luavgl_arc_init(lua_State *L)
{
  luavgl_obj_newmetatable(L, &lv_arc_class, "lv_arc", luavgl_arc_methods);
  lua_pop(L, 1);
}
