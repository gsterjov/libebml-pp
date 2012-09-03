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

#include "Stream.h"
#include "Endian.h"
#include <stdexcept>

#include <iostream>


/* variable integer class prefix
 * class A - 1xxx xxxx
 * class B - 01xx xxxx
 * class C - 001x xxxx
 * class D - 0001 xxxx
 * class E - 0000 1xxx
 * class F - 0000 01xx
 * class G - 0000 001x
 * class H - 0000 0001
 */
#define  CLASS_A  0x80
#define  CLASS_B  0x40
#define  CLASS_C  0x20
#define  CLASS_D  0x10
#define  CLASS_E  0x08
#define  CLASS_F  0x04
#define  CLASS_G  0x02
#define  CLASS_H  0x01


namespace Ebml
{

	/* read 16 bit integer */
	void Stream::read (uint16 &value)
	{
		read (reinterpret_cast<uint8*> (&value), 2);
		Endian::swap (value);
	}
	
	
	/* read 32 bit integer */
	void Stream::read (uint32 &value)
	{
		read (reinterpret_cast<uint8*> (&value), 4);
		Endian::swap (value);
	}
	
	
	/* read 64 bit integer */
	void Stream::read (uint64 &value)
	{
		read (reinterpret_cast<uint8*> (&value), 8);
		Endian::swap (value);
	}
	
	
	
	/* read 32 bit float */
	void Stream::read (float &value)
	{
		/* bit shifting floats usually isn't allowed
		 * so we cast it to a uint32 for the endian swap */
		uint32 tmp = reinterpret_cast<uint32&> (value);
		
		read (reinterpret_cast<uint8*> (&tmp), 4);
		Endian::swap (tmp);
		value = reinterpret_cast<float&> (tmp);
	}
	
	
	
	
	/* write 16 bit integer */
	void Stream::write (uint16 value)
	{
		Endian::swap (value);
		write (reinterpret_cast<uint8*> (&value), 2);
	}
	
	
	/* write 32 bit integer */
	void Stream::write (uint32 value)
	{
		Endian::swap (value);
		write (reinterpret_cast<uint8*> (&value), 4);
	}
	
	
	/* write 64 bit integer */
	void Stream::write (uint64 value)
	{
		Endian::swap (value);
		write (reinterpret_cast<uint8*> (&value), 8);
	}
	
	
	
	/* write 32 bit float */
	void Stream::write (float value)
	{
		/* bit shifting floats usually aren't allowed
		 * so we cast it to a uint32 for the endian swap */
		uint32 tmp = reinterpret_cast<uint32&> (value);
		Endian::swap (tmp);
		write (reinterpret_cast<uint8*> (&tmp), 4);
	}
	
	
	
	
	/* read coded ID integer */
	int Stream::readID (uint32 &id)
	{
		id = 0;
		
		int len;
		int b = peek ();
		
		
		/* determine class */
		if      ((b & CLASS_A) == CLASS_A) len = 1;
		else if ((b & CLASS_B) == CLASS_B) len = 2;
		else if ((b & CLASS_C) == CLASS_C) len = 3;
		else if ((b & CLASS_D) == CLASS_D) len = 4;
		
		/* invalid class */
		else throw std::runtime_error ("Cannot determine a valid Ebml ID class");
		
		
		/* read coded integer */
		read (reinterpret_cast<uint8*> (&id), len);
		Endian::swap (id);
		
		/* clear size prefix */
		id <<= len;
		id >>= len;
		
		/* everything in its place */
		id >>= (8 * (4 - len));
		
		return len;
	}
	
	
	
	
	/* read coded size descriptor */
	int Stream::readSize (uint64 &size)
	{
		size = 0;
		
		int len;
		int b = peek ();
		
		
		/* determine class */
		if      ((b & CLASS_A) == CLASS_A) len = 1;
		else if ((b & CLASS_B) == CLASS_B) len = 2;
		else if ((b & CLASS_C) == CLASS_C) len = 3;
		else if ((b & CLASS_D) == CLASS_D) len = 4;
		
		/* only size descriptors are this long */
		else if ((b & CLASS_E) == CLASS_E) len = 5;
		else if ((b & CLASS_F) == CLASS_F) len = 6;
		else if ((b & CLASS_G) == CLASS_G) len = 7;
		else if ((b & CLASS_H) == CLASS_H) len = 8;
		
		/* invalid class */
		else throw std::runtime_error ("Cannot determine a valid Ebml size class");
		
		
		/* read coded integer */
		read (reinterpret_cast<uint8*> (&size), len);
		Endian::swap (size);
		
		/* clear size prefix */
		size <<= len;
		size >>= len;
		
		/* everything in its place */
		size >>= (8 * (8 - len));
		
		return len;
	}
	
	
	
	/* write variable integer */
	void Stream::write (VInt32 &value)
	{
		uint32 data = value.data();
		
		data <<= (8 * (4 - value.length()));
		Endian::swap (data);
		
		/* write variable integer */
		write (reinterpret_cast<uint8*> (&data), value.length());
	}
	
	
	
	/* write variable integer */
	void Stream::write (VInt64 &value)
	{
		uint64 data = value.data();
		
		data <<= (8 * (8 - value.length()));
		Endian::swap (data);
		
		/* write variable integer */
		write (reinterpret_cast<uint8*> (&data), value.length());
	}

}
