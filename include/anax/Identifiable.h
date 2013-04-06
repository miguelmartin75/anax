///
/// Anax RTTI
/// Copyright (C) 2012-2013 Anax Creations. All rights reserved.
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

#ifndef __ANAX_IDENTIFIABLE_H__
#define __ANAX_IDENTIFIABLE_H__

// TODO: remove depenancy of this

/********************************************************************************
 * HOW TO USE
 * ==========
 *
 * In order to identify an object, you must include a macro INSIDE the class. It
 * is reccomended to put it at the top of the class, before any declarations.
 *
 * This macro simply adds a Class to the class and a couple of methods. There
 * are different types of macros and they will be discussed. This is for POLYMORPHIC
 * CLASSES ONLY.
 *
 * MACROS:
 * -------
 *
 * ANAX_IDENTIFIABLE(classtype)
 *		This macro is used to mark base classes as identifiable.
 *
 * ANAX_IDENTIFIABLEBASE(classtype)
 *		Marks a class as identifiable that inherits from a base class, publicly.
 *
 *
 * \note
 * This is aimed for single PUBLIC inheritance, no exceptions. If you want to adjust this
 * so it works for multiple inheritance, go ahead. I'm not stopping you.
 *
 * Here is an example:
 * \code
 *
 * class Example
 * {
 *		AC_IDENTIFIABLE_BASE(Example)
 * };
 *
 * \endcode
 *******************************************************************************/

#include <string>

namespace anax
{
	/// \class Class
	/// \brief Describes a class
	///
	/// A simple class that describes another class. This
	/// class has a Base class, this is useful if you only
	/// wish to have a restricted amount of classes to have
	/// a unique ID.
	///
	/// \tparam Base The base class of the Class
	///
	/// \author Miguel Martin
	template <class T>
	class Class
	{
	public:
		
		/// The base class type
		typedef T BaseClassType;
		
		/// The type which is used for an ID
		typedef size_t Id;
		
		
		
		explicit Class(const std::string& name)
			: _id(nextId++),
			  _name(name)
		{
		}
		
		
		/// \return The name of the class
		const std::string& getName() const
		{
			return _name;
		}
		
		/// \return The ID of the class
		Id getId() const
		{
			return _id;
		}
		
		/// Compares two class objects to see if they are equal
		/// \param c The class you wish to compare with
		/// \return true if the two classes are equal
		bool operator==(const Class<T>& c) const
		{
			return (this->_id == c._id);
		}
		
		/// Compares two class objects to see if they are equal
		/// \param c The class you wish to compare with
		/// \return true if the two classes are not equal
		bool operator!=(const Class<T>& c) const
		{
			return !operator==(c);
		}
		
		/// \return The last ID given out
		static Id GetLastId()
		{
			return nextId == 0 ? 0 : nextId - 1;
		}
		
	private:
		
		/// The ID
		Id _id;
		
		/// The name of the class
		const std::string _name;
		
		/// The next ID for the class
		static Id nextId;
	};
	
	template <class Base>
	typename Class<Base>::Id Class<Base>::nextId = 0;
	
#	define ANAX_UTIL_CONVERT_TO_STRING(x) #x
	
	// INTERFACE MACROS
	
#	define ANAX_IDENTIFIABLE(classtype) \
public: \
static const classtype::Class& GetClass() \
{ \
static const classtype::Class instance(ANAX_UTIL_CONVERT_TO_STRING(classtype)); \
return instance; \
} \
virtual const classtype::Class& getClass() const \
{ \
return classtype::GetClass(); \
} \
private:
	
	/// Marks a class that is a base class idenfitiable.
	///
	///
	/// For example:
	/// \code
	/// class Example
	/// {
	///		AC_IDENTFIABLE_BASE(Example)
	/// };
	/// \endcode
#	define ANAX_IDENTIFIABLE_BASE(classtype) \
public: \
typedef anax::Class<classtype> Class; \
static const classtype::Class& GetClass() \
{ \
static const classtype::Class instance(ANAX_UTIL_CONVERT_TO_STRING(_class)); \
return instance; \
} \
virtual const classtype::Class& getClass() const \
{ \
return classtype::GetClass(); \
} \
private:
	
	
	
	namespace util
	{
		/// \struct ClassGetter
		/// \brief A utility class that gets a class of an object
		///
		/// This is used so that it can be overloaded with pointer types.
		///
		/// \author Miguel Martin
		template <class T>
		struct ClassGetter
		{
		public:
			
			static const typename T::Class& Get()
			{
				return T::GetClass();
			}
			
			
			static const typename T::Class& Get(const T& obj)
			{
				return obj.getClass();
			}
		};
		
		/// A template specialization of the ClassGetter class,
		/// but used for pointer types.
		template <class T>
		struct ClassGetter <T*>
		{
		public:
			
			static const typename T::Class& Get()
			{
				return T::GetClass();
			}
			
			static const typename T::Class& Get(const T* obj)
			{
				return obj->getClass();
			}
		};
		
		namespace
		{
			/// \note This may or may NOT work on every platform/compiler
			/// \param obj A pointer to an object with a v-table
			/// \return A pointer to the v-table of the object
			void* getVtable(void *obj)
			{
				return *(reinterpret_cast<void **>(obj));
			}
		}
	}
	
	/// Compares two objects and tells whether they are from the same class
	/// \param x The first object that you wish to compare with
	/// \param y The second object that you wish to compare with
	/// \return true if the two objects are of the same type
	template <typename X, typename Y>
	bool isSameType(const X& x, const Y& y)
	{
		return util::ClassGetter<X>::Get(x) == util::ClassGetter<Y>::Get(y);
	}
	
	
	/// Tells whether an object is a specific type
	/// \tparam Type The type of class that you wish to check that an object is
	/// \return true if the object is of the class Type
	template <class Type, class T>
	bool isType(const T& obj)
	{
		return util::ClassGetter<Type>::Get() == util::ClassGetter<T>::Get(obj);
	}
	
	
	namespace
	{
		/// Compares two polymorphic objects to tell whether they are equal types
		/// \note
		/// If you have two objects, that do NOT declare the macro AC_IDENTIFIABLE in
		/// their class defintion, then perhaps you would want to use this method.
		/// This may or may NOT work on every platform/compiler (since this is basically a hack).
		/// \param obj1 The first object you wish to compare
		/// \param obj2 The second object you wish to compare
		/// \return true if the two objects are of the same type
		bool isSameType(void* obj1, void* obj2)
		{
			return util::getVtable(obj1) == util::getVtable(obj2);
		}
	}
}

#endif // __ANAX_IDENTIFIABLE_H__