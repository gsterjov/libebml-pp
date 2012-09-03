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

#ifndef EBML_ELEMENT_H_
#define EBML_ELEMENT_H_


#include <Ebml/Types.h>
#include <Ebml/VInt.h>
#include <string>
#include <list>
#include <cassert>
#include <iostream>


namespace Ebml
{
	/* forward declaration */
	class Element;
	
	
	
	/* reference counted element */
	class ElementRef
	{
	private:
		Element* mPointer;
		
		
	public:
		explicit ElementRef (uint32 id);
		ElementRef (Element* ptr);
		ElementRef (const ElementRef& ref);
		
		ElementRef () : mPointer(0) {}
		~ElementRef ();
		
		
		/* assignment, copy operators */
		ElementRef& operator= (Element* ptr);
		ElementRef& operator= (const ElementRef& ref);
		
		/* dereference, indirection operators */
		Element& operator*  () const { assert (mPointer); return *mPointer; }
		Element* operator-> () const { assert (mPointer); return  mPointer; }
		
		
		const Element* get() const { return mPointer; }
		
		void release();
	};
	
	
	
	
	/* element list type */
	typedef std::list<ElementRef> ElementList;
	
	
	
	/* ebml element */
	class Element
	{
		friend class ElementRef;
		
	public:
		enum Mode { READ_ONLY, WRITE_ONLY, READ_WRITE };
		
		
	private:
		/* reference counter */
		uint mRefCount;
		Mode mMode;
		
		
	protected:
		Element (uint32 id, uint64 size, Mode mode = READ_WRITE);
		
		/* properties */
		uint32 mID;
		uint64 mSize;
		uint8* mValue;
		
		ElementList  mChildren;
		
		
	public:
		explicit Element (uint32 id, Mode mode = READ_WRITE);
		virtual ~Element ();
		
		
		/* access properties */
		Mode getMode() { return mMode; }
		
		
		/* add child element */
		void append (const ElementRef& element) { mChildren.push_back (element); }
		
		/* element children */
		const ElementList& getChildren() { return mChildren; }
		
		
		
		/* get element properties */
		              uint32 getID()    { return mID; }
		virtual       uint64 getSize()  { return mSize; }
		virtual const uint8* getValue() { return mValue; }
		
		
		/* element value */
		virtual void getValue (uint8* value);
		virtual void setValue (const uint8* value, uint64 size);
		
		
		
		
		/* convenience value properties */
		void getValue (bool&   value) { getValue (reinterpret_cast<uint8*> (&value)); }
		void getValue (float&  value) { getValue (reinterpret_cast<uint8*> (&value)); }
		void getValue (double& value) { getValue (reinterpret_cast<uint8*> (&value)); }
		void getValue (int8&   value) { getValue (reinterpret_cast<uint8*> (&value)); }
		void getValue (int16&  value) { getValue (reinterpret_cast<uint8*> (&value)); }
		void getValue (int32&  value) { getValue (reinterpret_cast<uint8*> (&value)); }
		void getValue (int64&  value) { getValue (reinterpret_cast<uint8*> (&value)); }
		void getValue (uint8&  value) { getValue (reinterpret_cast<uint8*> (&value)); }
		void getValue (uint16& value) { getValue (reinterpret_cast<uint8*> (&value)); }
		void getValue (uint32& value) { getValue (reinterpret_cast<uint8*> (&value)); }
		void getValue (uint64& value) { getValue (reinterpret_cast<uint8*> (&value)); }
		void getValue (void*   value) { getValue (reinterpret_cast<uint8*> (value)); }
		
		void getValue (std::string& value)
		{
			char* str = new char[mSize];
			getValue (reinterpret_cast<uint8*> (str));
			value = str;
		}
		
		
		
		/* convenience value properties */
		void setValue (const bool&   value) { setValue (reinterpret_cast<const uint8*> (&value), sizeof(value)); }
		void setValue (const float&  value) { setValue (reinterpret_cast<const uint8*> (&value), sizeof(value)); }
		void setValue (const double& value) { setValue (reinterpret_cast<const uint8*> (&value), sizeof(value)); }
		void setValue (const int8&   value) { setValue (reinterpret_cast<const uint8*> (&value), sizeof(value)); }
		void setValue (const int16&  value) { setValue (reinterpret_cast<const uint8*> (&value), sizeof(value)); }
		void setValue (const int32&  value) { setValue (reinterpret_cast<const uint8*> (&value), sizeof(value)); }
		void setValue (const int64&  value) { setValue (reinterpret_cast<const uint8*> (&value), sizeof(value)); }
		void setValue (const uint8&  value) { setValue (reinterpret_cast<const uint8*> (&value), sizeof(value)); }
		void setValue (const uint16& value) { setValue (reinterpret_cast<const uint8*> (&value), sizeof(value)); }
		void setValue (const uint32& value) { setValue (reinterpret_cast<const uint8*> (&value), sizeof(value)); }
		void setValue (const uint64& value) { setValue (reinterpret_cast<const uint8*> (&value), sizeof(value)); }
		
		/* convenience value array properties */
		void setValue (const bool*   value, uint64 length) { setValue (reinterpret_cast<const uint8*> (value), sizeof(bool)   * length); }
		void setValue (const float*  value, uint64 length) { setValue (reinterpret_cast<const uint8*> (value), sizeof(float)  * length); }
		void setValue (const double* value, uint64 length) { setValue (reinterpret_cast<const uint8*> (value), sizeof(double) * length); }
		void setValue (const int8*   value, uint64 length) { setValue (reinterpret_cast<const uint8*> (value), sizeof(int8)   * length); }
		void setValue (const int16*  value, uint64 length) { setValue (reinterpret_cast<const uint8*> (value), sizeof(int16)  * length); }
		void setValue (const int32*  value, uint64 length) { setValue (reinterpret_cast<const uint8*> (value), sizeof(int32)  * length); }
		void setValue (const int64*  value, uint64 length) { setValue (reinterpret_cast<const uint8*> (value), sizeof(int64)  * length); }
		void setValue (const uint16* value, uint64 length) { setValue (reinterpret_cast<const uint8*> (value), sizeof(uint16) * length); }
		void setValue (const uint32* value, uint64 length) { setValue (reinterpret_cast<const uint8*> (value), sizeof(uint32) * length); }
		void setValue (const uint64* value, uint64 length) { setValue (reinterpret_cast<const uint8*> (value), sizeof(uint64) * length); }
		
		
		void setValue (const void* value, uint64 size) { setValue (reinterpret_cast<const uint8*> (value), size); }
		
		void setValue (const std::string& value) { setValue (value.c_str(), value.length()); }
	};

}


#endif /* EBML_ELEMENT_H_ */
