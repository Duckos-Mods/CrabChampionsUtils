#pragma once
#include <Mod/CppUserModBase.hpp>
#include <LuaMadeSimple/LuaMadeSimple.hpp>
#include <vector>
#include "../macros.hpp"



class ccu
{
private:
	using LuaFunction = int (*)(const RC::LuaMadeSimple::Lua&);
	class LuaFuncdata
	{
	public:
		LuaFuncdata(const std::string& name, const LuaFunction& function, const std::wstring& onRegMessage, const LogLevel::LogLevel& ll) : name(name), funct(function), onRegisterMessage(onRegMessage), logLevel(ll) {}
		const std::string name;
		const LuaFunction funct;
		const std::wstring onRegisterMessage;
		const RC::LogLevel::LogLevel logLevel = RC::LogLevel::Normal;
	};
	std::vector<LuaFuncdata> m_luaFunctions;
public:
	ccu();
	~ccu();

	auto registerLuaFunctions(LuaMadeSimple::Lua& lua) -> void;
};