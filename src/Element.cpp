/*
Copyright (c) 2009 Goran Sterjov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "Element.h"
#include <cstring>


namespace Ebml
{

	/* constructor */
	ElementRef::ElementRef (uint32 id) : mPointer(new Element(id))
	{
		/* increase reference count */
		if (mPointer) ++(mPointer->mRefCount);
	}
	
	
	/* constructor */
	ElementRef::ElementRef (Element* ptr) : mPointer(ptr)
	{
		/* increase reference count */
		if (mPointer) ++(mPointer->mRefCount);
	}
	
	
	/* copy constructor */
	ElementRef::ElementRef (const ElementRef& ref) : mPointer(ref.mPointer)
	{
		/* increase reference count */
		if (mPointer) ++(mPointer->mRefCount);
	}
	
	
	/* destructor */
	ElementRef::~ElementRef ()
	{
		release();
	}
	
	
	
	
	
	/* assignment operator */
	ElementRef& ElementRef::operator= (Element* ptr)
	{
		/* copy new pointer */
		if (mPointer != ptr)
		{
			release();
			mPointer = ptr;
			
			/* increase reference count */
			if (mPointer) ++(mPointer->mRefCount);
		}
		return *this;
	}
	
	
	
	/* copy operator */
	ElementRef& ElementRef::operator= (const ElementRef& ref)
	{
		/* copy new pointer */
		if (ref.mPointer != mPointer)
		{
			release();
			mPointer = ref.mPointer;
			
			/* increase reference count */
			if (mPointer) ++(mPointer->mRefCount);
		}
		return *this;
	}
	
	
	
	
	/* release element data */
	void ElementRef::release ()
	{
		if (mPointer)
		{
			assert (mPointer->mRefCount > 0);
			
			/* decrease reference */
			--(mPointer->mRefCount);
			
			/* free pointer */
			if (mPointer->mRefCount == 0)
				delete mPointer;
			
			mPointer = 0;
		}
	}
	
	
	
	
	
	
	/* constructor */
	Element::Element (uint32 id, uint64 size, Mode mode)
	: mRefCount(0), mMode(mode), mID(id), mSize(size), mValue(0) {}
	
	
	/* constructor */
	Element::Element (uint32 id, Mode mode)
	: mRefCount(0), mMode(mode), mID(id), mSize(0), mValue(0) {}
	
	
	
	/* destructor */
	Element::~Element ()
	{
		/* free data */
		if (mValue) delete[] mValue;
	}
	
	
	
	
	/* get element data */
	void Element::getValue (uint8* value)
	{
		memcpy (value, mValue, mSize);
	}
	
	
	
	/* set element data */
	void Element::setValue (const uint8* value, uint64 size)
	{
		/* free last value */
		if (mValue) delete[] mValue;
		
		/* copy new value */
		mValue = new uint8[size];
		memcpy (mValue, value, size);
		
		mSize = size;
	}

}
