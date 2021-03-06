//
// Parser.cpp
//
// $Id$
//
// Library: JSON
// Package: JSON
// Module:  Parser
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

#include "Poco/Ascii.h"
#include "Poco/Token.h"

#include "Poco/JSON/Parser.h"
#include "Poco/JSON/JSONException.h"

namespace Poco
{
namespace JSON
{


class SeparatorToken: public Token
{
public:
	SeparatorToken()
	{
	}

	virtual ~SeparatorToken()
	{
	}

	Class tokenClass() const
	{
		return Token::SEPARATOR_TOKEN;
	}

	bool start(char c, std::istream& istr)
	{
		if (   c == '{'
		        || c == '}'
		        || c == ']'
		        || c == '['
		        || c == ','
		        || c == ':' )
		{
			_value = c;
			return true;
		}

		if ( c == '\'' )
		{
			throw JSONException("Invalid quote found");
		}

		else return false;
	}

	void finish(std::istream& istr)
	{
	}
};

class StringToken: public Token
{
public:
	StringToken()
	{
	}

	virtual ~StringToken()
	{
	}

	Class tokenClass() const
	{
		return Token::STRING_LITERAL_TOKEN;
	}

	bool start(char c, std::istream& istr)
	{
		if ( c == '"')
		{
			_value = ""; // We don't need the quote!
			return true;
		}
		else return false;
	}

	void finish(std::istream& istr)
	{
		int c = istr.get();
		while (c != -1)
		{
			if ( c == 0 )
			{
				throw JSONException("Null byte not allowed");
			}

			if ( 0 < c && c <= 0x1F )
			{
				throw JSONException(format("Control character 0x%x not allowed", (unsigned int) c));
			}

			if ( c == '"' )
				break;

			if ( c == '\\' ) // Escaped String
			{
				c = istr.get();
				switch(c)
				{
				case '"' :
					c = '"';
					break;
				case '\\' :
					c = '\\';
					break;
				case '/' :
					c = '/';
					break;
				case 'b' :
					c = '\b';
					break;
				case 'f' :
					c = '\f';
					break;
				case 'n' :
					c = '\n';
					break;
				case 'r' :
					c = '\r';
					break;
				case 't' :
					c = '\t';
					break;
				case 'u' : // Unicode
				{
					Poco::Int32 unicode = decodeUnicode(istr);
					if ( unicode == 0 )
					{
						throw JSONException("\\u0000 is not allowed");
					}
					if ( unicode >= 0xD800 && unicode <= 0xDBFF )
					{
						c = istr.get();
						if ( c != '\\' )
						{
							throw JSONException("Invalid unicode surrogate pair");
						}
						c = istr.get();
						if ( c != 'u' )
						{
							throw JSONException("Invalid unicode surrogate pair");
						}
						Poco::Int32 surrogatePair = decodeUnicode(istr);
						if ( 0xDC00 <= surrogatePair && surrogatePair <= 0xDFFF )
						{
							unicode = 0x10000 + ((unicode & 0x3FF) << 10) + (surrogatePair & 0x3FF);
						}
						else
						{
							throw JSONException("Invalid unicode surrogate pair");
						}
					}
					else if ( 0xDC00 <= unicode && unicode <= 0xDFFF )
					{
						throw JSONException("Invalid unicode");
					}
					c = unicode;
					break;
				}
				default:
				{
					throw JSONException(format("Invalid escape '%c' character used", (char) c));
				}
				}
			}
			_value += c;
			c = istr.get();
		}

		if ( c == -1 )
		{
			throw JSONException("Unterminated string found");
		}
	}

	Poco::Int32 decodeUnicode(std::istream& istr)
	{
		Poco::Int32 value = 0;

		for(int i = 0; i < 4; i++)
		{
			value <<= 4;
			int nc = istr.peek();
			if ( nc == -1 )
			{
				throw JSONException("Invalid unicode sequence");
			}
			istr.get(); // No EOF, so read the character

			if (nc >= '0' && nc <= '9')
				value += nc - '0';
			else if (nc >= 'A' && nc <= 'F')
				value += 10 + nc - 'A';
			else if (nc >= 'a' && nc <= 'f')
				value += 10 + nc - 'a';
			else
				throw JSONException("Invalid unicode sequence. Hexadecimal digit expected");
		}

		return value;
	}
};

class KeywordToken : public Token
{
public:
	KeywordToken()
	{
	}

	virtual ~KeywordToken()
	{
	}

	Class tokenClass() const
	{
		return Token::KEYWORD_TOKEN;
	}

	bool start(char c, std::istream& istr)
	{
		if ( Ascii::isAlpha(c) )
		{
			_value = c;
			return true;
		}
		return false;
	}

	void finish(std::istream& istr)
	{
		int c = istr.peek();
		while (c != -1 && Ascii::isAlpha(c) )
		{
			istr.get();
			_value += c;
			c = istr.peek();
		}
	}
};

class NumberToken: public Token
{
public:
	NumberToken() : _activeClass(INTEGER_LITERAL_TOKEN)
	{
	}

	virtual ~NumberToken()
	{
	}

	Class tokenClass() const
	{
		return _activeClass;
	}

	bool start(char c, std::istream& istr)
	{
		// Reset the active class to integer
		_activeClass = INTEGER_LITERAL_TOKEN;

		if ( c == -1 )
			return false;

		if ( Ascii::isDigit(c) )
		{
			if ( c == '0' )
			{
				int nc = istr.peek();
				if ( Ascii::isDigit(nc) ) // A digit after a zero is not allowed
				{
					throw JSONException("Number can't start with a zero");
				}
			}
			_value = c;
			return true;
		}

		if ( c == '-' )
		{
			_value = c;

			int nc = istr.peek();
			if ( Ascii::isDigit(nc) )
			{
				if ( nc == '0' )
				{
					_value += '0';
					istr.get();

					nc = istr.peek();
					if ( Ascii::isDigit(nc) ) // A digit after -0 is not allowed
					{
						throw JSONException("Number can't start with a zero");
					}
				}
				return true;
			}
		}

		return false;
	}

	void finish(std::istream& istr)
	{
		int c;
		while( (c = istr.peek()) != -1)
		{
			if ( Ascii::isDigit(c) )
			{
				_value += c;
				istr.get();
			}
			else
			{
				switch(c)
				{
				case '.': // Float
				{
					if ( _activeClass == Token::FLOAT_LITERAL_TOKEN )
					{
						throw JSONException("Invalid float value");
					}
					_activeClass = Token::FLOAT_LITERAL_TOKEN;

					_value += c;
					istr.get();

					// After a . we need a digit
					c = istr.peek();
					if ( ! Ascii::isDigit(c) )
					{
						throw JSONException("Invalid float value");
					}

					break;
				}
				case 'E':
				case 'e':
				{
					if ( _activeClass == Token::DOUBLE_LITERAL_TOKEN )
					{
						throw JSONException("Invalid double value");
					}
					_activeClass = Token::DOUBLE_LITERAL_TOKEN;

					// Add the e or E
					_value += c;
					istr.get();

					// When the next char is - or + then read the next char
					c = istr.peek();
					if ( c == '-' || c == '+' )
					{
						_value += c;
						istr.get();
						c = istr.peek();
					}

					if ( ! Ascii::isDigit(c) )
					{
						throw JSONException("Invalid double value");
					}

					break;
				}
				default:
					return; // End of number token
				}

				istr.get(); // If we get here we have a valid character for a number
				_value += c;
			}
		}
	}

private:

	Class _activeClass;

};


Parser::Parser() : _tokenizer(), _handler(NULL)
{
	_tokenizer.addToken(new WhitespaceToken());
	_tokenizer.addToken(new InvalidToken());
	_tokenizer.addToken(new SeparatorToken());
	_tokenizer.addToken(new StringToken());
	_tokenizer.addToken(new NumberToken());
	_tokenizer.addToken(new KeywordToken());
}


Parser::~Parser()
{

}


const Token* Parser::nextToken()
{
	const Token* token = _tokenizer.next();
	if ( token->is(Token::EOF_TOKEN) )
	{
		throw JSONException("Unexpected EOF found");
	}
	return token;
}


void Parser::parse(std::istream& in)
{
	_tokenizer.attachToStream(in);
	const Token* token = nextToken();

	if ( token->is(Token::SEPARATOR_TOKEN) )
	{
		// This must be a { or a [
		if ( token->asChar() == '{' )
		{
			readObject();
		}
		else if ( token->asChar() == '[' )
		{
			readArray();
		}
		else
		{
			throw JSONException(format("Invalid separator '%c' found. Expecting { or [", token->asChar()));
		}
		token = _tokenizer.next();
		if ( ! token->is(Token::EOF_TOKEN) )
		{
			throw JSONException(format("EOF expected but found '%s'", token->asString()));
		}
	}
	else
	{
		throw JSONException(format("Invalid token '%s' found. Expecting { or [", token->asString()));
	}
}


void Parser::readObject()
{
	if ( _handler != NULL )
	{
		_handler->startObject();
	}

	if ( readRow(true) ) // First call is special: check for empty object
	{
		while(readRow());
	}

	if ( _handler != NULL )
	{
		_handler->endObject();
	}
}


bool Parser::readRow(bool firstCall)
{
	const Token* token = nextToken();

	if ( firstCall && token->tokenClass() == Token::SEPARATOR_TOKEN && token->asChar() == '}' )
	{
		return false; // End of object is possible for an empty object
	}

	if ( token->tokenClass() == Token::STRING_LITERAL_TOKEN )
	{
		std::string propertyName = token->tokenString();
		if ( _handler != NULL )
		{
			_handler->key(propertyName);
		}

		token = nextToken();

		if (    token->is(Token::SEPARATOR_TOKEN)
		        && token->asChar() == ':' )
		{
			readValue(nextToken());

			token = nextToken();

			if ( token->is(Token::SEPARATOR_TOKEN) )
			{
				if ( token->asChar() == ',' )
				{
					return true; // Read next row
				}
				else if ( token->asChar() == '}' )
				{
					return false; // End of object
				}
				else
				{
					throw JSONException(format("Invalid separator '%c' found. Expecting , or }", token->asChar()));
				}
			}
			else
			{
				throw JSONException(format("Invalid token '%s' found. Expecting , or }", token->asString()));
			}
		}
		else
		{
			throw JSONException(format("Invalid token '%s' found. Expecting :", token->asString()));
		}
	}
	else
	{
		throw JSONException(format("Invalid token '%s' found. Expecting key", token->asString()));
	}
}


void Parser::readValue(const Token* token)
{
	switch(token->tokenClass())
	{
	case Token::INTEGER_LITERAL_TOKEN:
		if ( _handler != NULL )
		{
			_handler->value(token->asInteger());
		}
		break;
	case Token::KEYWORD_TOKEN:
	{
		if ( token->tokenString().compare("null") == 0 )
		{
			if ( _handler != NULL )
			{
				_handler->null();
			}
		}
		else  if ( token->tokenString().compare("true") == 0 )
		{
			if ( _handler != NULL )
			{
				_handler->value(true);
			}
		}
		else if ( token->tokenString().compare("false") == 0 )
		{
			if ( _handler != NULL )
			{
				_handler->value(false);
			}
		}
		else
		{
			throw JSONException(format("Invalid keyword '%s' found", token->asString()));
		}
		break;
	}
	case Token::FLOAT_LITERAL_TOKEN:
		// Fall through
	case Token::DOUBLE_LITERAL_TOKEN:
		if ( _handler != NULL )
		{
			_handler->value(token->asFloat());
		}
		break;
	case Token::STRING_LITERAL_TOKEN:
		if ( _handler != NULL )
		{
			_handler->value(token->tokenString());
		}
		break;
	case Token::SEPARATOR_TOKEN:
	{
		if ( token->asChar() == '{' )
		{
			readObject();
		}
		else if ( token->asChar() == '[' )
		{
			readArray();
		}
		break;
	}
	}
}


void Parser::readArray()
{
	if ( _handler != NULL )
	{
		_handler->startArray();
	}

	if ( readElements(true) ) // First call is special: check for empty array
	{
		while(readElements());
	}

	if ( _handler != NULL )
	{
		_handler->endArray();
	}
}


bool Parser::readElements(bool firstCall)
{
	const Token* token = nextToken();

	if ( firstCall && token->is(Token::SEPARATOR_TOKEN) && token->asChar() == ']' )
	{
		// End of array is possible for an empty array
		return false;
	}

	readValue(token);

	token = nextToken();

	if ( token->is(Token::SEPARATOR_TOKEN) )
	{
		if ( token->asChar() == ']' )
			return false; // End of array

		if ( token->asChar() == ',' )
			return true;

		throw JSONException(format("Invalid separator '%c' found. Expecting , or ]", token->asChar()));
	}

	throw JSONException(format("Invalid token '%s' found.", token->asString()));
}

}}
