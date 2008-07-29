//
// sampleFactory.h
//
// Copyright (c) 2004-2008, Applied Informatics Software Engineering GmbH.
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
#ifndef Foundation_Sample_Factory_INCLUDED
#define Foundation_Sample_Factory_INCLUDED

#include <iostream>

class Resource
    /// a dummy resource class
{

public: 

    void foo(){
        std::cout << "Resource::foo()\n";
    }

private:

    Resource(){
        std::cout<< "Resource::Resource()\n";
    }

    ~Resource(){
        std::cout<< "Resource::~Resource()\n";
    }

    Resource& operator=(const Resource&);

    friend Resource* createResource();
    friend void destoryResource(Resource* ptr);
};

/// It is quite common some platform dependent resource are managed by
/// create/desotry like "factory method".
/// SharedPtr can wrap them and realize the RAII. See ResourceFacotry class
/// in sampleFactory.cpp 
Resource* createResource()
{
    return new Resource();
}

void destoryResource(Resource* ptr)
{
    delete ptr;
}

#endif // Foundation_Sample_Factory_INCLUDED
