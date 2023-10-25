#pragma once

#define STRI(string) std::wstring(L##string) + L"\n"

namespace CCU
{
	template <int size>
	using padder = const char* [size];
}