#include "luavgl.h"
#include "rotable.h"

static int luavgl_ffmpeg_player_create(lua_State *L)
{
  return luavgl_obj_create_helper(L, lv_ffmpeg_player_create);
}

static int luavgl_ffmpeg_player_set_src(lua_State *L)
{
  lv_obj_t *obj = luavgl_to_obj(L, 1);
  const char *src = luaL_checkstring(L, 2);
  lv_ffmpeg_player_set_src(obj, src);
  return 0;
}

static int luavgl_ffmpeg_player_set_cmd(lua_State *L)
{
  lv_obj_t *obj = luavgl_to_obj(L, 1);
  lv_ffmpeg_player_cmd_t cmd = luaL_checkinteger(L, 2);
  lv_ffmpeg_player_set_cmd(obj, cmd);
  return 0;
}

static int luavgl_ffmpeg_player_set_decoder(lua_State *L)
{
  lv_obj_t *obj = luavgl_to_obj(L, 1);
  const char *decoder = luaL_checkstring(L, 2);
  lv_ffmpeg_player_set_decoder(obj, decoder);
  return 0;
}

static const rotable_Reg luavgl_ffmpeg_player_methods[] = {
    {"set_src", LUA_TFUNCTION, {luavgl_ffmpeg_player_set_src}},
    {"set_cmd", LUA_TFUNCTION, {luavgl_ffmpeg_player_set_cmd}},
    {"set_decoder", LUA_TFUNCTION, {luavgl_ffmpeg_player_set_decoder}},
    {},
};

static void luavgl_ffmpeg_player_init(lua_State *L)
{
  luavgl_obj_newmetatable(L, &lv_ffmpeg_player_class, "lv_ffmpeg_player",
                          luavgl_ffmpeg_player_methods);
  lua_pop(L, 1);
}
