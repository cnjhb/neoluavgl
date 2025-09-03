#include "luavgl.h"
#include "rotable.h"

typedef struct luavgl_line_s {
  luavgl_obj_t obj;
  lv_point_precise_t *points;
} luavgl_line_t;

static const luavgl_obj_class_t luavgl_line_class = {
    .base_class = &luavgl_obj_class,
    .instance_size = sizeof(luavgl_line_t),
};

static int line_set_points(lua_State *L, lv_obj_t *obj, bool set)
{
  luavgl_line_t *line = (luavgl_line_t *)luavgl_obj_to_lobj(L, obj);
  if (!set) {
    if (line->points) {
      int num = lv_line_get_point_count(obj);
      lua_createtable(L, num, 0);
      for (int i = 0; i < num; i++) {
        lua_createtable(L, 2, 0);

        lua_pushnumber(L, line->points[i].x);
        lua_seti(L, -2, 1);

        lua_pushnumber(L, line->points[i].y);
        lua_seti(L, -2, 2);

        lua_rawseti(L, -2, i + 1);
      }
    } else {
      lua_pushnil(L);
    }
    return 1;
  }
  if (line->points) {
    free(line->points);
  }
  int len = luaL_len(L, -1);
  line->points = malloc(len * sizeof(lv_point_precise_t));
  for (int i = 1; i <= len; i++) {
    lua_geti(L, -1, i);

    lua_geti(L, -1, 1);
    line->points[i - 1].x = lua_tonumber(L, -1);
    lua_pop(L, 1);

    lua_geti(L, -1, 2);
    line->points[i - 1].y = lua_tonumber(L, -1);
    lua_pop(L, 1);

    lua_pop(L, 1);
  }
  lv_line_set_points(obj, line->points, len);
  return 1;
}

static const luavgl_property_ops_t line_property_ops[] = {
    {.name = "points", .ops = line_set_points},
};
static const luavgl_table_t line_property_table = {
    .len = sizeof(line_property_ops) / sizeof(line_property_ops[0]),
    .array = line_property_ops,
};

static const rotable_Reg luavgl_line_methods[] = {
    {"__class", LUA_TLIGHTUSERDATA, {.ptr = &luavgl_line_class}},
    {"__property", LUA_TLIGHTUSERDATA, {.ptr = &line_property_table}},
    {}
};

static void luavgl_line_init(lua_State *L)
{
  luavgl_obj_newmetatable(L, &lv_line_class, "lv_line", luavgl_line_methods);
  lua_pop(L, 1);
}

static int luavgl_line_create(lua_State *L)
{
  return luavgl_obj_create_helper(L, lv_line_create);
}
