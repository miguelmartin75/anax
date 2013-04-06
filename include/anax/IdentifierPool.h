///
/// anax
/// Copyright (C) 2013 Anax Creations. All rights reserved.
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

#ifndef __ANAX_IDENTIFIERPOOL_H__
#define __ANAX_IDENTIFIERPOOL_H__

// TODO: remove depenancy of this

#include <queue>

namespace anax
{
	/// \class IdentifierPool
	/// \brief Describes a pool of IDs
	/// \tparam IdType Typically an integer
	///
	/// An IdentifierPool is used to identify objects in which IDs need to be re-used.
	///
	/// \author Miguel Martin
	template <typename IdType>
	class IdentifierPool
	{
	public:
		
		typedef std::queue<IdType> Queue;
		
		/// Constructor
		IdentifierPool()
			: _nextId(IdType())
		{
		}
		
		/// Copy Constructor
		IdentifierPool(const IdentifierPool& pool)
			: _nextId(pool._nextId),
			  _ids(pool._ids)
		{
		}
		
		/// Move Constructor
		IdentifierPool(IdentifierPool&& pool)
			: _nextId(pool._nextId),
			  _ids(pool._ids)
		{
			pool._nextId = IdType();
		}
		
		/// Destructor
		~IdentifierPool()
		{
		}
		
		
		/// Adds an id to the pool
		/// \param id The ID you wish to add to the pool
		void add(IdType id)
		{
			_ids.push(id);
		}
		
		/// \return The next ID in the ID pool
		IdType next()
		{
			if(_ids.size() > 0)
			{
				size_t front = _ids.front(); // store the ID in a local var
											 // pop off that id from the queue
				_ids.pop();
				
				// return it
				return front;
			}
			
			return _nextId++; // otherwise, we'll just return the next avaliable ID, and increment it
		}
		
		const Queue& getIds() const
		{ return _ids; }
		
		
		IdentifierPool& operator=(const IdentifierPool& pool)
		{
			if(this != &pool)
			{
				_ids = pool._ids;
				_nextId = pool._nextId;
			}
			
			return *this;
		}
		
		IdentifierPool& operator=(IdentifierPool&& pool)
		{
			if(this != &pool)
			{
				_nextId = pool._nextId;
				pool._nextId = IdType();
				_ids = pool._ids;
			}
			return *this;
		}
		
	private:
		
		Queue _ids;
		
		IdType _nextId;
	};
}

#endif // __ANAX_IDENTIFIERPOOL_H__