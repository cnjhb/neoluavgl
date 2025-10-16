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

static const struct luaL_Reg luavgl_draw_buf_methods[] = {
    {"destroy", luavgl_draw_buf_destroy},
    {},
};
