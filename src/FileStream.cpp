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

#include "FileStream.h"


namespace Ebml
{

	/* constructor */
	FileStream::FileStream (const std::string& file, Mode mode)
	: mFile (file),
	  mMode (mode)
	{
		
	}
	
	
	/* destructor */
	FileStream::~FileStream ()
	{
		
	}
	
	
	
	/* open the file */
	bool FileStream::open ()
	{
		using std::fstream;
		
		
		/* write to file */
		if (mMode == WRITE)
			mStream.open (mFile.c_str(), fstream::out | fstream::trunc | fstream::binary);
		
		/* read from file */
		else
			mStream.open (mFile.c_str(), fstream::in | fstream::binary);
		
		
		return mStream.good();
	}
	
	
	/* close the file */
	bool FileStream::close ()
	{
		mStream.close ();
		return true;
	}
	
	
	
	/* read binary from the file */
	void FileStream::readData (uint8 *data, int length)
	{
		assert (mMode == READ);
		mStream.read (reinterpret_cast<char*> (data), length);
	}
	
	
	/* write binary to the file */
	void FileStream::writeData (const uint8 *data, int length)
	{
		assert (mMode == WRITE);
		mStream.write (reinterpret_cast<const char*> (data), length);
	}
	
	
	/* seek forward */
	void FileStream::skip (int size)
	{
		mStream.seekg (size, std::ios_base::cur);
	}

}
