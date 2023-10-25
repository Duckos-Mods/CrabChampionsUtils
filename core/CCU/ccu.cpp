#include "ccu.hpp"
#include <LuaType/LuaTArray.hpp>
#include <Unreal/TArray.hpp>
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/UObject.hpp>
#include <Constructs/Views/EnumerateView.hpp>
#include <LuaType/LuaUObject.hpp>

using namespace Unreal;
ccu::ccu()
{
	m_luaFunctions.push_back(
		{
			"CCU_Init_Test_Function",
			[](const LuaMadeSimple::Lua& lua) -> int {
				Output::send<LogLevel::Verbose>(STRI("Called CITF From Lua!"));
				return 0;
			},
			STRI("Registered CCU_Init_Test_Function"),
			LogLevel::Verbose
		}
	);

	m_luaFunctions.push_back(
		{
			"CCU_GetAllPlayers",
			[](const LuaMadeSimple::Lua& lua) -> int {
				// create a vector for fao to fill
				std::vector<UObject*> players{};
				RC::Unreal::UObjectGlobals::FindAllOf(STR("CrabPS"), players);

				// Create a TArray from the vector
				TArray<UObject*> playersTarray(players.data(), players.size());
				auto luaPlayers = lua.prepare_new_table();
				// Iterate through the TArray and add each element to the Lua table
				for (const auto& [elem, index] : players | views::enumerate)
				{
					luaPlayers.add_key(index);
					LuaType::auto_construct_object(lua, elem);
					luaPlayers.fuse_pair();
				}
				luaPlayers.make_local();
				// Return one thing, in this case the table because that's what's at the top of the Lua stack.
				return 1; 
			},
			STRI("Registered CCU_GetAllPlayers"),
			LogLevel::Verbose
		}
	);

}

ccu::~ccu()
{

}

auto ccu::registerLuaFunctions(LuaMadeSimple::Lua& lua) -> void
{

	lua.register_function("CCU_Init_Test_Function",
		[](const LuaMadeSimple::Lua& lua) -> int {
		Output::send<LogLevel::Verbose>(STRI("Called CITF From Lua!"));
		return 0;
	});
	for (auto& lfd : m_luaFunctions)
	{
		lua.register_function(lfd.name, lfd.funct);
		switch (lfd.logLevel)
		{
		case LogLevel::Verbose:
			Output::send<LogLevel::Verbose>(lfd.onRegisterMessage);
			break;
		case LogLevel::Default:
			Output::send<LogLevel::Default>(lfd.onRegisterMessage);
			break;
		case LogLevel::Warning:
			Output::send<LogLevel::Warning>(lfd.onRegisterMessage);
			break;
		case LogLevel::Error:
			Output::send<LogLevel::Error>(lfd.onRegisterMessage);
			break;
		case LogLevel::Normal:
			Output::send<LogLevel::Normal>(lfd.onRegisterMessage);
			break;
		default:
			break;
		}
	}
}