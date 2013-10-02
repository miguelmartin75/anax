///
/// anax
/// An open source C++ entity system.
///
/// Copyright (C) 2013 Miguel Martin (miguel.martin7.5@hotmail.com)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
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
		BaseSystem();
		
		/// Sets the ComponentFilter
		/// \param componentFilter The ComponentFilter you wish the system to have
		BaseSystem(const ComponentFilter& componentFilter);
		
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