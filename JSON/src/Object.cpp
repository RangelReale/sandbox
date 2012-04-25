//
// Object.cpp
//
// $Id$
//
// Library: JSON
// Package: JSON
// Module:  Object
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
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

#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/JSON/Stringifier.h"

#include <iostream>
#include <sstream>

namespace Poco {
namespace JSON {


Object::Object()
{

}

Object::Object(const Object& copy) : _values(copy._values)
{
}

Object::~Object()
{

}


DynamicAny Object::get(const std::string& key) const
{
  DynamicAny value;

  ValueMap::const_iterator it = _values.find(key);
  if ( it != _values.end() )
  {
    value = it->second;
  }
  return value;
}


Array::Ptr Object::getArray(const std::string& key) const
{
  Array::Ptr result;

  DynamicAny value = get(key);
  if ( value.type() == typeid(Array::Ptr) )
  {
    result = value.extract<Array::Ptr>();
  }
  return result;
}


Object::Ptr Object::getObject(const std::string& key) const
{
  Object::Ptr result;

  DynamicAny value = get(key);
  if ( value.type() == typeid(Object::Ptr) )
  {
    result = value.extract<Object::Ptr>();
  }
  return result;
}


void Object::getNames(std::vector<std::string>& names) const
{
  names.clear();
  for(ValueMap::const_iterator it = _values.begin(); it != _values.end(); ++it)
  {
    names.push_back(it->first);
  }
}


void Object::stringify(std::ostream& out, unsigned int indent) const
{
  out << '{';
  if ( indent > 0 )
  {
    out << std::endl;
  }

  for(ValueMap::const_iterator it = _values.begin(); it != _values.end();)
  {
    for(int i = 0; i < indent; i++)
    {
      out << ' ';
    }

    out << '"' << it->first << '"';
    out << (( indent > 0 ) ? " : " : ":");

    Stringifier::stringify(it->second, out, indent);

    if ( ++it != _values.end() )
    {
      out << ',';
    }

    if ( indent > 0 )
    {
      out << std::endl;
    }
  }

  if ( indent > 0 )
    indent -= 2;
  for(int i = 0; i < indent; i++)
  {
    out << ' ';
  }

  out << '}';

}

} } // Namespace Poco::JSON