#include "luavgl.h"

static int luavgl_img_dcdr_get_info(lua_State *L)
{
  const char *path = luaL_checkstring(L, 1);
  lv_image_header_t header = {};
  if (lv_image_decoder_get_info(path, &header) == LV_RES_OK) {
    lua_newtable(L);
    lua_pushinteger(L, header.w);
    lua_setfield(L, -2, "w");
    lua_pushinteger(L, header.h);
    lua_setfield(L, -2, "h");
    return 1;
  }
  return 0;
}

static const luaL_Reg luavgl_img_dcdr_methods[] = {
    {"get_info", luavgl_img_dcdr_get_info},
    {NULL,       NULL                    }
};
