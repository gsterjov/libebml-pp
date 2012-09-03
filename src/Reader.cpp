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

#include "Reader.h"
#include "FileStream.h"
#include <iostream>


namespace Ebml
{

	/* constructor */
	Reader::Reader (Stream* stream)
	: mStream (stream),
	  mInternalStream (false),
	  mRoot (0)
	{
		
	}
	
	
	/* constructor */
	Reader::Reader (const std::string& file)
	: mStream (new FileStream (file)),
	  mInternalStream (true),
	  mRoot (0)
	{
		
	}
	
	
	/* destructor */
	Reader::~Reader ()
	{
		if (mInternalStream)
			delete mStream;
	}
	
	
	
	
	/* open document */
	bool Reader::open ()
	{
		mStream->open ();
		mRoot = new ReaderElement (mStream);
		return true;
	}
	
	
	/* clsoe document */
	void Reader::close ()
	{
		mStream->close();
		delete mRoot;
		mRoot = 0;
	}
	
	
	
	
	
	
	/* element constructor */
	ReaderElement::ReaderElement (Stream* stream, uint32 id, uint64 size)
	: mIndex (0),
	  mChild (0),
	  mStream (stream),
	  Element (id, size)
	{
		
	}
	
	
	/* element contructor */
	ReaderElement::ReaderElement (Stream* stream)
	: mIndex (0),
	  mChild (0),
	  mStream (stream),
	  Element (0, 0)
	{
		
	}
	
	
	/* element destructor */
	ReaderElement::~ReaderElement ()
	{
		if (mChild) delete mChild;
	}
	
	
	
	
	/* read element value */
	const uint8* ReaderElement::getValue ()
	{
		uint8* data = new uint8[mSize];
		mStream->read (data, mSize);
		mIndex += mSize;
		return data;
	}
	
	
	/* read element value */
	void ReaderElement::getValue (uint8* data)
	{
		mStream->read (data, mSize);
		mIndex += mSize;
	}
	
	
	
	
	/* get the next child element */
	ReaderElement* ReaderElement::getNextChild ()
	{
		
		/* skip child */
		if (mChild)
		{
			/* go to the end of the child */
			mStream->skip (mChild->mSize - mChild->mIndex);
			delete mChild;
			mChild = 0;
		}
		
		
		/* reached end of container */
		if ((mSize > 0 && mIndex >= mSize) || mStream->eos())
			return 0;
		
		
		uint32 id;
		uint64 size;
		
		/* read element header */
		mIndex += mStream->readID (id);
		mIndex += mStream->readSize (size);
		
		/* move index to end of child */
		mIndex += size;
		
		
		/* create new child element */
		mChild = new ReaderElement (mStream, id, size);
		return mChild;
	}

}
