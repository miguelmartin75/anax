///
/// AES - Anax Entity System
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

#ifndef __ANAX_IDENTIFIABLEARRAY_H__
#define __ANAX_IDENTIFIABLEARRAY_H__

// TODO: remove depenancy of this

#include <vector>
#include <cassert>
#include <memory>

#include "anax/Identifiable.h"

namespace anax
{
	/// \class IdentifiableArray
	/// \brief A specialized array that allows for Identifable objects of a Base class to be stored
	///
	/// Only one type of class can be stored in this array. It is much designed as the STL containers,
	/// however, you cannot modify the internal storage (i.e. arrangement) of these objects. It is possible to iterate through
	/// the array as if it were a std::vector<Base*>, as it uses a std::unique_ptr for the imlementation.
	///
	/// \tparam Base Where Base uses the AC_IDENTIFIABLE_BASE or AC_IDENTIFABLE macro
	///
	/// \author Miguel Martin.
	template <typename Base>
	class IdentifiableArray
	{
		typedef std::unique_ptr<Base> ImplSmartPtr;
		typedef std::vector<ImplSmartPtr> ImplContainer;
		
	public:
		
		typedef Base BaseType;
		typedef typename Base::Class Type;
		
		typedef typename ImplContainer::size_type size_type;
		typedef typename ImplContainer::value_type value_type;
		typedef typename ImplContainer::const_reference reference;
		typedef typename ImplContainer::const_reference const_reference;
		typedef typename ImplContainer::const_pointer pointer;
		typedef typename ImplContainer::const_pointer const_pointer;
		typedef typename ImplContainer::iterator iterator;
		typedef typename ImplContainer::const_iterator const_iterator;
		typedef typename ImplContainer::reverse_iterator reverse_iterator;
		typedef typename ImplContainer::const_reverse_iterator const_reverse_iterator;
		
		
		
		IdentifiableArray()
		{
		}
		
		explicit IdentifiableArray(size_type size)
			: _container(size)
		{
		}
		
		IdentifiableArray(const IdentifiableArray<Base>& identifiableArray)
			: _container(identifiableArray._container)
		{
		}
		
		IdentifiableArray(IdentifiableArray<Base>&& identifiableArray)
			: _container(identifiableArray._container)
		{
		}
		
		~IdentifiableArray()
		{
		}
		
		
		// ITERATORS
		
		iterator begin()
		{ return _container.begin(); }
		
		const_iterator begin() const
		{ return _container.begin(); }
		
		reverse_iterator rbegin()
		{ return _container.rbegin(); }
		
		const_reverse_iterator rbegin() const
		{ return _container.rbegin(); }
		
		iterator end()
		{ return _container.end(); }
		
		const_iterator end() const
		{ return _container.end(); }
		
		reverse_iterator rend()
		{ return _container.rend(); }
		
		const_reverse_iterator rend() const
		{ return _container.rend(); }
		
		
		
		// MODIFIERS
		
		template <typename J>
		void insert(J* obj)
		{
			size_type index = indexFor(obj);
			
			// do we need to resize the container?
			if(_container.size() <= index)
			{
				_container.resize(index + 1);
			}
			else
			{
				// assertion; this means there is an object of the same type already in the array,
				// if you want to overwrite the data that is specified by a type
				// use indexFor<J> and operator[]
				assert(0);
			}
			
			_container[index] = ImplSmartPtr(obj);
		}
		
		template <typename J>
		void erase()
		{
			typename Base::Class::Id index = indexFor<J>();
			assert(_container.size() > index);
			
			_container[index].reset();
		}
		
		template <typename J>
		void erase(J* obj)
		{
			typename Base::Class::Id index = indexFor(obj);
			if(_container.size() <= index)
			{
				return;
			}
			
		}
		
		void erase(iterator position)
		{
			_container.erase(position);
		}
		
		void erase(iterator first, iterator last)
		{
			_container.erase(first, last);
		}
		
		void clear()
		{
			_container.clear();
		}
		
		
		// ELEMENT ACCESSORS
		
		reference front()
		{ return _container.front(); }
		
		const_reference front() const
		{ return _container.front(); }
		
		Base* get(const Type& type) const
		{
			size_type index = type.getId();
			if(_container.size() <= index)
			{
				return NULL;
			}
			return _container[index].get();
		}
		
		template <typename J>
		J* get() const
		{
			return static_cast<J*>(get(J::GetClass()));
		}
		
		reference operator[](size_type n)
		{
			return _container[n];
		}
		
		const_reference operator[](size_type n) const
		{
			return _container[n];
		}
		
		reference at(size_type n)
		{
			return _container.at(n);
		}
		
		const_reference at(size_type n) const
		{
			return _container.at(n);
		}
		
		template <typename J>
		size_type indexFor() const
		{
			return J::GetClass().getId();
		}
		
		template <typename J>
		size_type indexFor(J* obj) const
		{
			return obj->getClass().getId();
		}
		
		// CAPACITY
		
		/// A fast way to determine whether the array contains a class-type
		template <typename J>
		bool contains() const
		{
			return contains(J::GetClass());
		}
		
		/// A fast way to determine whether the array contains an object
		template <typename J>
		bool contains(J* obj) const
		{
			return contains(obj, J::GetClass());
		}
		
		bool contains(const Type& type) const
		{
			return get(type) != NULL;
		}
		
		bool contains(Base* obj, const Type& type) const
		{
			return get(type) == obj;
		}
		
		bool empty() const
		{
			return _container.empty();
		}
		
		size_type size() const
		{
			return _container.size();
		}
		
		size_type capacity() const
		{
			return _container.capacity();
		}
		
		size_type max_size() const
		{
			return _container.max_size();
		}
		
		
		IdentifiableArray& operator=(const IdentifiableArray<Base>& identifiableArray)
		{
			if(this != identifiableArray)
			{
				_container = identifiableArray._container;
			}
			
			return *this;
		}
		
		IdentifiableArray& operator=(IdentifiableArray<Base>&& identifiableArray)
		{
			if(this != identifiableArray)
			{
				_container = identifiableArray._container;
			}
			
			return *this;
		}
		
	private:
		
		/// The resembling container
		ImplContainer _container;
	};
}

#endif // __ANAX_IDENTIFIABLEARRAY_H__