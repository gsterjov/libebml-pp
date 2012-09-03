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

#ifndef STREAM_H_
#define STREAM_H_


#include <Ebml/Types.h>
#include <Ebml/VInt.h>
#include <string.h>


namespace Ebml
{

	class Stream
	{
	protected:
		virtual void readData  (uint8 *data, int length) = 0;
		virtual void writeData (const uint8 *data, int length) = 0;
		
		
	public:
		virtual bool open () = 0;
		virtual bool close () = 0;
		
		virtual void skip  (int size) = 0;
		virtual int  peek() = 0;
		virtual bool eos() = 0;
		
		
		
		/* convenience read functions
		 * always reads big endian data */
		void read (uint8 *data, int length) { readData (data, length); }
		
		void read (uint8  &value) { read (reinterpret_cast<uint8*> (&value), 1); }
		void read (uint16 &value);
		void read (uint32 &value);
		void read (uint64 &value);
		
		void read (float &value);
		void read (bool  &value) { read (reinterpret_cast<uint8*> (&value), 1); }
		
		/* element tags */
		int readID (uint32 &id);
		int readSize (uint64 &size);
		
		
		/* convenience write functions
		 * always writes big endian data */
		void write (const uint8 *data, int length) { writeData (data, length); }
		
		void write (uint8  value) { write (reinterpret_cast<uint8*> (&value), 1); }
		void write (uint16 value);
		void write (uint32 value);
		void write (uint64 value);
		
		void write (float value);
		void write (bool  value) { write (reinterpret_cast<uint8*> (&value), 1); }
		
		void write (VInt32 &value);
		void write (VInt64 &value);
	};

}


#endif /* STREAM_H_ */
