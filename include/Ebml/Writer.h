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

#ifndef WRITER_H_
#define WRITER_H_


#include <Ebml/Types.h>
#include <Ebml/Stream.h>
#include <Ebml/Element.h>
#include <string>


namespace Ebml
{

	class WriterElement : public Element
	{
	private:
		uint8* mData;
		
		void getData (uint8* data);
		void setData (const uint8* data, uint64 size);
		
		
	public:
		explicit WriterElement (uint32 id);
		~WriterElement ();
	};
	
	
	
	
	class Writer
	{
	private:
		Stream* mStream;
		bool mInternalStream;
		
		
	public:
		explicit Writer (Stream* stream);
		explicit Writer (const std::string& file);
		~Writer ();
		
		
		bool open ();
		void close ();
		
		
		void write (const ElementRef& element);
	};

}


#endif /* WRITER_H_ */
