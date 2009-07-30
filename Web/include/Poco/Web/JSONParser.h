//
// JSONParser.h
//
// $Id: //poco/Main/Web/include/Poco/Web/JSONParser.h#2 $
//
// Library: Web
// Package: Configuration
// Module:  JSONParser
//
// Definition of the JSONParser class.
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

// Adapted from JSON parser ( http://fara.cs.uni-potsdam.de/~jsg/json_parser/ )

/*
Copyright (c) 2005 JSON.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

The Software shall be used for Good, not Evil.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef Web_JSONParser_INCLUDED
#define Web_JSONParser_INCLUDED


#include "Poco/Web/Web.h"
#include "Poco/Web/JSONConfiguration.h"
#include "Poco/Web/JSONHandler.h"


namespace Poco {
namespace Web {


class Web_API JSONParser
	/// JSONParser parses JSON string and passes events to the
	/// handler, if one is supplied during construction.
	/// JSONParser takes shared ownership on the handler.
	/// Usage Example:
	///
	/// JSONParser jp(new JSONPrinter(std::cout));
	/// jp.parse("{\"Name\": \"Bart\"}"
{
public:
	typedef JSONConfiguration::ContextPtr ContextPtr;

	enum Classes
	{
		C_SPACE,  /* space */
		C_WHITE,  /* other whitespace */
		C_LCURB,  /* {  */
		C_RCURB,  /* } */
		C_LSQRB,  /* [ */
		C_RSQRB,  /* ] */
		C_COLON,  /* : */
		C_COMMA,  /* , */
		C_QUOTE,  /* " */
		C_BACKS,  /* \ */
		C_SLASH,  /* / */
		C_PLUS,   /* + */
		C_MINUS,  /* - */
		C_POINT,  /* . */
		C_ZERO ,  /* 0 */
		C_DIGIT,  /* 123456789 */
		C_LOW_A,  /* a */
		C_LOW_B,  /* b */
		C_LOW_C,  /* c */
		C_LOW_D,  /* d */
		C_LOW_E,  /* e */
		C_LOW_F,  /* f */
		C_LOW_L,  /* l */
		C_LOW_N,  /* n */
		C_LOW_R,  /* r */
		C_LOW_S,  /* s */
		C_LOW_T,  /* t */
		C_LOW_U,  /* u */
		C_ABCDF,  /* ABCDF */
		C_E,      /* E */
		C_ETC,    /* everything else */
		C_STAR,   /* * */   
		NR_CLASSES
	};
	
	enum States
		/// State codes
	{
		GO,  /* start    */
		OK,  /* ok       */
		OB,  /* object   */
		KE,  /* key      */
		CO,  /* colon    */
		VA,  /* value    */
		AR,  /* array    */
		ST,  /* string   */
		ES,  /* escape   */
		U1,  /* u1       */
		U2,  /* u2       */
		U3,  /* u3       */
		U4,  /* u4       */
		MI,  /* minus    */
		ZE,  /* zero     */
		IT,  /* integer  */
		FR,  /* fraction */
		E1,  /* e        */
		E2,  /* ex       */
		E3,  /* exp      */
		T1,  /* tr       */
		T2,  /* tru      */
		T3,  /* true     */
		F1,  /* fa       */
		F2,  /* fal      */
		F3,  /* fals     */
		F4,  /* false    */
		N1,  /* nu       */
		N2,  /* nul      */
		N3,  /* null     */
		C1,  /* /        */
		C2,  /* / *     */
		C3,  /* *        */
		FX,  /* *.* *eE* */
		D1,  /* second UTF-16 character decoding started by \ */
		D2,  /* second UTF-16 character proceeded by u */
		NR_STATES
	};

	enum Modes
		/// Modes that can be pushed on the _pStack.
	{
		MODE_ARRAY = 1, 
		MODE_DONE = 2,  
		MODE_KEY = 3,   
		MODE_OBJECT = 4
	};

	enum Actions
	{
		CB = -10, /* _comment begin */
		CE = -11, /* _comment end */
		FA = -12, /* 0 */
		TR = -13, /* 0 */
		NU = -14, /* null */
		DE = -15, /* double detected by exponent e E */
		DF = -16, /* double detected by fraction . */
		SB = -17, /* string begin */
		MX = -18, /* integer detected by minus */
		ZX = -19, /* integer detected by zero */
		IX = -20, /* integer detected by 1-9 */
		EX = -21, /* next char is _escaped */
		UC = -22  /* Unicode character read */
	};

	static const int PARSE_BUFFER_SIZE = 3500;
	static const int PARSER_STACK_SIZE = 128;

	JSONParser(const JSONConfiguration& config, JSONHandler::Ptr pHandler);
		/// Creates JSONParser.

	JSONParser(JSONHandler::Ptr pHandler = 0);
		/// Creates JSONParser. The context pointer typically
		/// points to the handler object which, in turn, is used in
		/// the callback to handle the parsed data.

	~JSONParser();
		/// Destroys JSONParser.
	
	void parse(const std::string& json);

private:
	void init();
		/// Initializes the parser.

	bool push(int mode);
		/// Push a mode onto the _pStack. Return false if there is overflow.

	bool pop(int mode);
		/// Pops the _pStack, assuring that the current mode matches the expectation.
		/// Returns false if there is underflow or if the modes mismatch.

	void growBuffer();
	void clearBuffer();
	void parseBufferPushBackChar(char c);
	void parseBufferPopBackChar();
	int addCharToParseBuffer(int nextChar, int nextClass);
	int addEscapedCharToParseBuffer(int nextChar);
	int decodeUnicodeChar();
	void assertNotStringNullBool();
	void assertNonContainer();

	void parseBuffer();
	int parseChar(int nextChar);
		/// Called for each character (or partial character) in JSON string.
		/// It accepts UTF-8, UTF-16, or UTF-32. It returns 1 if things are looking ok so far.
		/// If it rejects the character, it returns 0.

	bool done();

	JSONConfiguration _config;
	static const int  _asciiClass[128];
		/// This array maps the 128 ASCII characters into character classes.
		/// The remaining Unicode characters should be mapped to C_ETC.
		/// Non-whitespace control characters are errors.
	static const int  _stateTransitionTable[NR_STATES][NR_CLASSES];
	static const int  xx = -1;
		
	JSONHandler::Ptr _pHandler;

	signed char      _state;
	signed char      _beforeCommentState;
	JSONEntity::Type _type;
	signed char      _escaped;
	signed char      _comment;
	unsigned short   _utf16HighSurrogate;
	long             _depth;
	long             _top;
	signed char*     _pStack;
	long             _stackCapacity;
	char*            _pParseBuffer;
	size_t           _pParseBufferCapacity;
	size_t           _parseBufferCount;
	size_t           _commentBeginOffset;
	char             _decimalPoint;
	signed char      _staticStack[PARSER_STACK_SIZE];
	char             _staticParseBuffer[PARSE_BUFFER_SIZE];
};


//
// inlines
//

inline bool JSONParser::done()
{
    return _state == OK && pop(MODE_DONE);
}


inline void JSONParser::assertNotStringNullBool()
{
	poco_assert(_type != JSONEntity::JSON_T_FALSE &&
		_type != JSONEntity::JSON_T_TRUE &&
		_type != JSONEntity::JSON_T_NULL &&
		_type != JSONEntity::JSON_T_STRING);
}


inline void JSONParser::assertNonContainer()
{
	poco_assert(_type == JSONEntity::JSON_T_NULL ||
		_type == JSONEntity::JSON_T_FALSE ||
		_type == JSONEntity::JSON_T_TRUE ||
		_type == JSONEntity::JSON_T_FLOAT ||
		_type == JSONEntity::JSON_T_INTEGER ||
		_type == JSONEntity::JSON_T_STRING);
}


} } // namespace Poco::Web


#endif // Web_JSONParser_INCLUDED