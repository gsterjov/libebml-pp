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

#ifndef FILESTREAM_H_
#define FILESTREAM_H_


#include <Ebml/Stream.h>
#include <fstream>
#include <cassert>


namespace Ebml
{

	class FileStream : public Stream
	{
	public:
		enum Mode { READ, WRITE };
		
		
	private:
		Mode mMode;
		std::string mFile;
		
		std::fstream mStream;
		
		
		void readData  (uint8 *data, int length);
		void writeData (const uint8 *data, int length);
		
		
	public:
		FileStream (const std::string& file, Mode mode = READ);
		~FileStream ();
		
		
		bool open ();
		bool close ();
		
		void skip  (int size);
		int  peek() { assert (mMode == READ); return mStream.peek (); }
		bool eos()  { peek(); return mStream.eof(); }
	};

}


#endif /* FILESTREAM_H_ */
