#include "core/CCU/ccu.hpp"
#include <DynamicOutput/DynamicOutput.hpp>
#include <DynamicOutput/Output.hpp>


class CrabChampionsUtilsMod : public RC::CppUserModBase
{
private:
    ccu m_ccu;

public:
    CrabChampionsUtilsMod() : CppUserModBase()
    {
        ModName = STR("CrabChampionsUtils");
        ModVersion = STR("1.0");
        ModDescription = STR("A Utility mod for modding making Crab Champions mods easier");
        ModAuthors = STR("Duckos Mods");
        Output::send<LogLevel::Verbose>(STR("hello World!"));
    }

    ~CrabChampionsUtilsMod()
    {
    }

    auto on_update() -> void override
    {
    }

    void on_lua_start(StringViewType mod_name, LuaMadeSimple::Lua& lua, LuaMadeSimple::Lua& main_lua, LuaMadeSimple::Lua& async_lua, std::vector<LuaMadeSimple::Lua*>& hook_luas) override
    {
		m_ccu.registerLuaFunctions(lua);
    }
};
#define CCU_MOD_API __declspec(dllexport)
extern "C"
{
    CCU_MOD_API  RC::CppUserModBase* start_mod()
    {
        return new CrabChampionsUtilsMod();
    }

    CCU_MOD_API  void uninstall_mod(RC::CppUserModBase* mod)
    {
        delete mod;
    }
}