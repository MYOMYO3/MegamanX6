#pragma once
#include <map>


class JTemplate
{
public:

	template<typename TReturn, typename TKey, typename TMap>
	static TReturn* MapFindToPointer(TKey& _Key, TMap& _Map)
	{
		typename TMap::iterator FindIter = _Map.find(_Key);

		if (FindIter == _Map.end())
		{
			return nullptr;
		}

		return FindIter->second;
	}

private:
	JTemplate() {};
	~JTemplate() {};
};