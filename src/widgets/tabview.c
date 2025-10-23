#include "luavgl.h"
#include "rotable.h"

static int luavgl_tabview_create(lua_State *L)
{
  return luavgl_obj_create_helper(L, lv_tabview_create);
}

static int luavgl_tabview_add_tab(lua_State *L)
{
  lv_obj_t *obj = luavgl_to_obj(L, 1);
  const char *name = luaL_checkstring(L, 2);
  lv_obj_t *page = lv_tabview_add_tab(obj, name);
  luavgl_obj_t *lobj = luavgl_add_lobj(L, page);
  lobj->lua_created = false;
  return 1;
}

static int luavgl_tabview_rename_tab(lua_State *L)
{
  lv_obj_t *obj = luavgl_to_obj(L, 1);
  int id = luaL_checkinteger(L, 2);
  const char *name = luaL_checkstring(L, 3);
  lv_tabview_rename_tab(obj, id, name);
  return 0;
}

static int luavgl_tabview_set_tab_bar_positoin(lua_State *L)
{
  lv_obj_t *obj = luavgl_to_obj(L, 1);
  lv_tabview_set_tab_bar_position(obj, luaL_checkinteger(L, 2));
  return 0;
}

static int luavgl_tabview_set_tab_bar_size(lua_State *L)
{
  lv_obj_t *obj = luavgl_to_obj(L, 1);
  lv_tabview_set_tab_bar_size(obj, luaL_checkinteger(L, 2));
  return 0;
}

static int luavgl_tabview_get_tab_bar(lua_State *L)
{
  lv_obj_t *obj = luavgl_to_obj(L, 1);
  lv_obj_t *tab_bar = lv_tabview_get_tab_bar(obj);
  luavgl_obj_t *lobj = luavgl_add_lobj(L, tab_bar);
  lobj->lua_created = false;
  return 1;
}

static int luavgl_tabview_get_tab_count(lua_State *L)
{
  lv_obj_t *obj = luavgl_to_obj(L, 1);
  lua_pushinteger(L, lv_tabview_get_tab_count(obj));
  return 1;
}

static int luavgl_tabview_get_tab_button(lua_State *L)
{
  lv_obj_t *obj = luavgl_to_obj(L, 1);
  int id = luaL_checkinteger(L, 2);
  lv_obj_t *tab_btn = lv_tabview_get_tab_button(obj, id);
  luavgl_obj_t *lobj = luavgl_add_lobj(L, tab_btn);
  lobj->lua_created = false;
  return 1;
}

static int luavgl_tabview_get_tab_active(lua_State *L)
{
  lv_obj_t *obj = luavgl_to_obj(L, 1);
  lua_pushinteger(L, lv_tabview_get_tab_active(obj));
  return 1;
}

static const rotable_Reg luavgl_tabview_methods[] = {
    {"add_tab", LUA_TFUNCTION, {luavgl_tabview_add_tab}},
    {"rename_tab", LUA_TFUNCTION, {luavgl_tabview_rename_tab}},
    {"set_tab_bar_positoin",
     LUA_TFUNCTION, {luavgl_tabview_set_tab_bar_positoin}},
    {"set_tab_bar_size", LUA_TFUNCTION, {luavgl_tabview_set_tab_bar_size}},
    {"get_tab_bar", LUA_TFUNCTION, {luavgl_tabview_get_tab_bar}},
    {"get_tab_count", LUA_TFUNCTION, {luavgl_tabview_get_tab_count}},
    {"get_tab_button", LUA_TFUNCTION, {luavgl_tabview_get_tab_button}},
    {"get_tab_active", LUA_TFUNCTION, {luavgl_tabview_get_tab_active}},
    {},
};

static void luavgl_tabview_init(lua_State *L)
{
  luavgl_obj_newmetatable(L, &lv_tabview_class, "lv_tabview",
                          luavgl_tabview_methods);
  lua_pop(L, 1);
}
