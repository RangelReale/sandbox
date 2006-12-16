//
// EntityInfo.h
//
//
// Library: Container
// Package: ContainerCore
// Module:  EntityInfo
//
// Definition of the EntityInfo class.
//
// Copyright (c) 2006, Aleksandar Fabijanic and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

#ifndef Container_EntityInfo_INCLUDED
#define Container_EntityInfo_INCLUDED


#include <string>


namespace Poco {
namespace Servlet {
namespace Container {


template <class C>
class RegistrationInfo
	/// Structure containing info about entities registered
	/// with a WebApplication (servlets and filters).
{
public:
	RegistrationInfo(C* pConfig):_pConfig(pConfig)
	{
	}

	const std::string& libName() const
	/// Return the name of the library where the entity
	/// class resides.
	{
		return _pConfig->getLibrary();
	}

	const std::string& className() const
	/// Return the entity class name.
	{
		return _pConfig->getClass();
	}

	const C& config() const
	/// Return the entity configuration.
	{
		poco_check_ptr(_pConfig);
		return *_pConfig;
	}

private:
	RegistrationInfo();
	RegistrationInfo(const RegistrationInfo&);
	RegistrationInfo& operator=(const RegistrationInfo&);

	C* _pConfig;
	/// Configuration (obtained from deployment descriptor).
};

template <class R, class T>
class EntityInfo
/// Loaded entities info class.
{
public:
	EntityInfo(const std::string& name, R* pRegInfo, T* pEntity):
	_name(name), _pRegInfo(pRegInfo), _pEntity(pEntity)
	{
		poco_check_ptr(_pEntity);
		poco_check_ptr(_pRegInfo);
	}

	const std::string& name() const
	{
		return _name;
	}

	T* instance()
	{
		return _pEntity;
	}

	const R& regInfo() const
	{
		return *_pRegInfo;
	}

protected:
	EntityInfo();
	EntityInfo(const EntityInfo&);
	EntityInfo& operator=(const EntityInfo&);

private:
	std::string _name;
	/// Servlet name.

	T* _pEntity;
	/// Pointer to the entity.

	R* _pRegInfo;
	/// Pointer to registration information.
};


} } } // namespace Poco::Servlet::Container


#endif  //Container_EntityInfo_INCLUDED
