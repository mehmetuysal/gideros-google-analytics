#include "ganalytics.h"
#include "gideros.h"
#include <vector>
#include <string>

#ifndef abs_index
#define abs_index(L, i) ((i) > 0 || (i) <= LUA_REGISTRYINDEX ? (i) : lua_gettop(L) + (i) + 1)
#endif

static int isSessionStarted = 0;

static int startAnalytics(lua_State *L)
{
	if (isSessionStarted)
		return 0;
    
    const char *apikey = luaL_checkstring(L, 1);
    bool crash = lua_toboolean(L, 2);
    
    //lua_pushboolean(L, 2);
    ganalytics_StartAnalytics(apikey,crash);

	isSessionStarted = 1;
    
	return 0;
}


static char **copyParameters(lua_State *L, int index)
{
	luaL_checktype(L, index, LUA_TTABLE);

	int t = abs_index(L, index);
    
    std::vector<std::string> parameters;
	lua_pushnil(L);
	while (lua_next(L, t) != 0)
	{
        parameters.push_back(luaL_checkstring(L, -2));
        parameters.push_back(luaL_checkstring(L, -1));
		lua_pop(L, 1);
    }
    
    char **parameters2 = (char**)malloc((parameters.size() + 1) * sizeof(char*));
    for (std::size_t i = 0; i < parameters.size(); ++i)
        parameters2[i] = strdup(parameters[i].c_str());
    parameters2[parameters.size()] = NULL;

    return parameters2;
}

static void freeParameters(char **parameters)
{
    if (parameters == NULL)
        return;
    
    char **parameters2 = parameters;
    
    while (*parameters2)
        free(*parameters2++);

    free(parameters);
}

static int sendScreen(lua_State *L)
{
    const char *eventName = luaL_checkstring(L, 1);
	
	int count = 1;
	double sum = 0;
    char **parameters = NULL;
	int hadCount = 0;
	
	int parameterCount = lua_gettop(L)-1;
	for (int i = 0; i < parameterCount; ++i)
	{
		switch (lua_type(L, i + 2))
		{
			case LUA_TNUMBER:
				if(hadCount)
					sum = lua_tonumber(L, i + 2);
				else{
					count = lua_tonumber(L, i + 2);
					hadCount = 1;
				}
				break;
			case LUA_TTABLE:
				parameters = copyParameters(L, i + 2);
				break;
		}
	}
    ganalytics_SendScreen(eventName);
    
    freeParameters(parameters);
    
    return 0;
}


static int sendEvent(lua_State *L)
{
    const char *eventCategory = luaL_checkstring(L, 1);
    const char *action = luaL_checkstring(L, 2);
    const char *label = luaL_checkstring(L, 3);
    int eventValue = lua_tonumber(L, 4);
    
    ganalytics_SendEvent(eventCategory, action, label, eventValue);
    

    
    return 0;
}

static int loader(lua_State* L)
{
	lua_newtable(L);
    
	lua_pushcfunction(L, startAnalytics);
	lua_setfield(L, -2, "startAnalytics");
	lua_pushcfunction(L, sendScreen);
	lua_setfield(L, -2, "sendScreen");
    lua_pushcfunction(L, sendEvent);
    lua_setfield(L, -2, "sendEvent");
    
	lua_pushvalue(L, -1);
	lua_setglobal(L, "analytics");
    
	return 1;
}

static void g_initializePlugin(lua_State *L)
{
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "preload");
    
	lua_pushcfunction(L, loader);
	lua_setfield(L, -2, "analytics");
    
	lua_pop(L, 2);
}

static void g_deinitializePlugin(lua_State *L)
{
}

REGISTER_PLUGIN("analytics", "1.0")

