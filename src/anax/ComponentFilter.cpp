///
/// anax
/// Copyright (C) 2013 Miguel Martin (miguel.martin7.5@hotmail.com)
///
///
/// This software is provided 'as-is', without any express or implied warranty.
/// In no event will the authors be held liable for any damages arising from the
/// use of this software.
///
/// Permission is hereby granted, free of charge, to any person
/// obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// 1. The origin of this software must not be misrepresented;
///    you must not claim that you wrote the original software.
///    If you use this software in a product, an acknowledgment
///    in the product documentation would be appreciated but is not required.
///
/// 2. Altered source versions must be plainly marked as such,
///	   and must not be misrepresented as being the original software.
///
/// 3. The above copyright notice and this permission notice shall be included in
///    all copies or substantial portions of the Software.
///

#include "ComponentFilter.hpp"

namespace anax
{
	void ComponentFilter::clear()
	{
		_requiredComponentsList.clear();
		_requiresOneOfComponentsList.clear();
		_excludeComponentsList.clear();
	}
	
	bool ComponentFilter::doesPassFilter(const ComponentTypeList &componentTypeList) const
	{
		// loop through all the component type bits
		std::size_t index = _requiredComponentsList.find_first();
		for(; index != ComponentTypeList::npos; index = _requiredComponentsList.find_next(index))
		{
			// ensure that the none of the component types at index
			// are false (i.e. ensure that it meets all of the requirement list)
			if(index >= componentTypeList.size() || componentTypeList[index] == false)
			{
				// we'll return false
				return false;
			}
		}
		
		// if the optional bitset is not empty
		if(!_requiresOneOfComponentsList.empty())
		{
			if(!_requiresOneOfComponentsList.intersects(componentTypeList))
			{
				return false;
			}
		}
		
		// however if we got this far...
		// then...
		
		// check if the exclude bitset is not empty
		if(!_excludeComponentsList.empty())
		{
			// if there is AT LEAST one bit that interesects the excludeBitSet
			// then we shall set returnValue to false, indicating that it is NOT
			// interested in the Entity
			if(_excludeComponentsList.intersects(componentTypeList))
			{
				return false;
			}
		}
		
		// otherwise, everything passed the test, so we will return true
		return true;
	}
}