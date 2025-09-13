#include "luavgl.h"

static int luavgl_tinyttf_destroy(lua_State *L)
{
  if (lua_islightuserdata(L, 1)) {
    lv_tiny_ttf_destroy((lv_font_t *)lua_touserdata(L, 1));
  } else {
    luaL_argerror(L, 1, "lightuserdata expected");
  }
  return 0;
}

static int luavgl_tinyttf_create(lua_State *L)
{
  const char *path = luaL_checkstring(L, 1);
  int font_size = luaL_checkinteger(L, 2);
  lv_font_t *font = lv_tiny_ttf_create_file(path, font_size);
  lua_pushlightuserdata(L, font);
  return 1;
}

static const struct luaL_Reg luavgl_tinyttf_methods[] = {
    {"create",  luavgl_tinyttf_create },
    {"destroy", luavgl_tinyttf_destroy},
    {NULL,      NULL                  },
};
