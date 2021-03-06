//
// JSON.cpp
//
// $Id: //poco/svn/Web/samples/JSON/src/JSON.cpp#1 $
//
// This sample demonstrates the JSON parser.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
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


#include "Poco/Web/JSONParser.h"
#include "Poco/Web/JSONPrinter.h"
#include "Poco/Web/JSONPrettyPrinter.h"
#include "Poco/Web/JSONCondenser.h"
#include <iostream>


using Poco::Web::JSONHandler;
using Poco::Web::JSONEntity;
using Poco::Web::JSONParser;
using Poco::Web::JSONPrinter;
using Poco::Web::JSONPrettyPrinter;
using Poco::Web::JSONCondenser;


class PersonInfoHandler: public JSONHandler
{
public:
	PersonInfoHandler(std::ostream& out): JSONHandler(out)
	{
	}

	void handleKey(const JSONEntity& val)
	{
		_key = val;
	}

	void handleInteger(const JSONEntity& val)
	{
		if (_key.toString() == "postalCode")
			stream() << ' '  << val.toInteger() << '.' << std::endl;
	}

	void handleString(const JSONEntity& val)
	{
		if (_key.toString() == "firstName")
			stream() << val.toString();
		else if (_key.toString() == "lastName")
			stream() << ' ' << val.toString();
		else if (_key.toString() == "streetAddress")
			stream() << " lives at " << val.toString(); 
		else if (_key.toString() == "city")
			stream() << " in " << val.toString();
		else if (_key.toString() == "state")
			stream() << ", " << val.toString();
	}

private:
	JSONEntity _key;
};


int main()
{
	const std::string str("{"
		"\"firstName\": \"John\","
		"\"lastName\": \"Smith\","
		"\"address\": {"
			"\"streetAddress\": \"21 2nd Street\","
			"\"city\": \"New York\","
			"\"state\": \"NY\","
			"\"postalCode\": 10021"
		"},"
	"\"phoneNumbers\": ["
		"\"212 555-1234\","
		"\"646 555-4567\""
	"],"
	"\"weight\": {"
		"\"value\": 123.456, \"units\": \"lbs\""
		"}"
	"}");

	std::cout << "JSON structure:" << std::endl;
	std::cout << "===============" << std::endl;
	JSONParser jp(new JSONPrinter(std::cout));
	jp.parse(str);

	std::cout << std::endl;

	std::cout << std::endl << "Condensed JSON:" << std::endl;
	std::cout << "===============" << std::endl;
	JSONParser jp2(new JSONCondenser(std::cout));
	jp2.parse(str);

	std::cout << std::endl;

	std::cout << std::endl << "Readable JSON:" << std::endl;
	std::cout << "==============" << std::endl;
	JSONParser jp3(new JSONPrettyPrinter(std::cout, JSONPrettyPrinter::JSON_FORMAT_READABLE));
	jp3.parse(str);

	std::cout << std::endl;

	std::cout << std::endl << "Person Info:" << std::endl;
	std::cout << "============" << std::endl;
	JSONParser jp4(new PersonInfoHandler(std::cout));
	jp4.parse(str);

	std::cout << std::endl;

	return 0;
}
