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

#include "Writer.h"
#include "FileStream.h"


namespace Ebml
{

	/* constructor */
	Writer::Writer (Stream* stream) : mStream(stream), mInternalStream(false)
	{
		
	}
	
	
	/* constructor */
	Writer::Writer (const std::string& file)
	: mStream (new FileStream (file, FileStream::WRITE)),
	  mInternalStream (true)
	{
		
	}
	
	
	/* destructor */
	Writer::~Writer ()
	{
		if (mInternalStream)
			delete mStream;
	}
	
	
	
	
	/* open stream */
	bool Writer::open ()
	{
		return mStream->open();
	}
	
	
	/* close stream */
	void Writer::close ()
	{
		mStream->close();
	}
	
	
	
	
	/* returns the size of the element including children sizes */
	uint64 getElementSize (const ElementRef& element)
	{
		/* get data size */
		uint64 size = element->getSize();
		
		
		/* get children */
		ElementList children = element->getChildren();
		ElementList::iterator iter;
		
		/* get total children size */
		for (iter = children.begin(); iter != children.end(); iter++)
		{
			ElementRef child = *iter;
			
			/* get child header */
			VInt32 child_id = child->getID();
			VInt64 child_size = getElementSize (child);
			
			/* add child header size */
			size += child_id.length();
			size += child_size.length();
			
			/* add total child size */
			size += child_size.value();
		}
		
		
		return size;
	}
	
	
	
	
	/* write element to stream */
	void Writer::write (const ElementRef& element)
	{
		/* get header */
		VInt32 id = element->getID();
		VInt64 size = getElementSize (element);
		
		/* write header */
		mStream->write (id);
		mStream->write (size);
		
		/* write data */
		if (element->getSize() > 0)
			mStream->write (element->getValue(), element->getSize());
		
		
		/* get children */
		ElementList children = element->getChildren();
		ElementList::iterator iter;
		
		/* write children */
		for (iter = children.begin(); iter != children.end(); iter++)
			write (*iter);
	}

}
