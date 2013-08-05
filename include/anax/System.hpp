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

#ifndef __ANAX_SYSTEM_HPP__
#define __ANAX_SYSTEM_HPP__

#include <cstddef>
#include <vector>

#include <anax/detail/ClassTypeId.hpp>

#include <anax/Entity.hpp>
#include <anax/ComponentFilter.hpp>

namespace anax
{
	class World;
	
	/// \brief Describes the base class for a systems
	///
	/// A system is basically a container for entities with
	/// a specific amount of components.
	///
	/// \author Miguel Martin
	class BaseSystem
	{
	public:
		
		/// Default constructor
		BaseSystem()
		{
		}
		
		/// Sets the ComponentFilter
		/// \param componentFilter The ComponentFilter you wish the system to have
		BaseSystem(const ComponentFilter& componentFilter)
			: _componentFilter(componentFilter)
		{
		}
		
		/// Destructor
		virtual ~BaseSystem() = 0;
		
		/// \return The Component Filter attached to the System
		const ComponentFilter& getComponentFilter() const;
		
		/// \return The World attached to the System
		World& getWorld() const;
		
		/// \return All the entities that are within the System
		std::vector<Entity> getEntities() const;
		
	private:
		
		/// Initializes the system, when a world is succesfully
		/// attached to it.
		virtual void initialize() {}
		
		/// Occurs when an Entity is added to the system
		/// \param entity The Entity that is added to the system
		virtual void onEntityAdded(Entity& entity) {}
		
		/// Occurs when an Entity is removed to the system
		/// \param entity The Entity that is removed from the system
		virtual void onEntityRemoved(Entity& entity) {}
		
		
		
		/// Used to add an Entity to the system
		/// \param entity The Entity you wish to add
 		/// \note This is called by the attached World object
		void add(Entity& entity);
		
		/// Used to remove an Entity from the system
		/// \param entity The Entity you wish to remove
 		/// \note This is called by the attached World object
		void remove(Entity& entity);
		
		/// Used to set the attached World
		/// \param world The World to attach to
		/// \note This is called by the attached World object
		void setWorld(World& world);
		
		
		
		/// The component filter
		ComponentFilter _componentFilter;
		
		/// The Entities that are attached to this system
		std::vector<Entity> _entities;
		
		/// The World attached to the system
		World* _world;
		
		
		
		friend class World;
	};
	
	/// \brief A class that follows the CRTP pattern, used to define custom systems
	/// \tparam T The System you are defining
	///
	/// This class uses the CRTP pattern to make a unique identifier for each system
	/// class
	///
	/// \see BaseSystem
	/// If you wish to store systems generically and for further documentation.
	///
	/// \author Miguel Martin
	template <typename T>
	class System
		: public BaseSystem
	{
	public:
		
		/// A handy typedef for sub-classing the System class
		typedef System<T> Base;
		
		/// Default constructor
		System()
		{
		}
		
		/// Sets the ComponentFilter
		/// \param componentFilter The ComponentFilter you wish the system to have
		System(const ComponentFilter& componentFilter)
			: BaseSystem(componentFilter)
		{
		}
		
		/// \return A unique TypeId for this type of System
		static detail::TypeId GetTypeId()
		{
			return detail::ClassTypeId<BaseSystem>::GetTypeId<T>();
		}
	};
}

#endif // __ANAX_SYSTEM_HPP__