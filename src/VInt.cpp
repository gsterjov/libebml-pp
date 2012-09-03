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

#include "VInt.h"
#include <stdexcept>



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
/* variable integeer class masks */
#define  CLASS_A_MASK  0x80
#define  CLASS_B_MASK  0x4000
#define  CLASS_C_MASK  0x200000
#define  CLASS_D_MASK  0x10000000
#define  CLASS_E_MASK  0x0800000000
#define  CLASS_F_MASK  0x040000000000
#define  CLASS_G_MASK  0x02000000000000
#define  CLASS_H_MASK  0x0100000000000000


/* variable integer class range */
#define  CLASS_A_MAX  0x7f
#define  CLASS_B_MAX  0x3fff
#define  CLASS_C_MAX  0x1fffff
#define  CLASS_D_MAX  0x0fffffff
#define  CLASS_E_MAX  0x07ffffffff
#define  CLASS_F_MAX  0x03ffffffffff
#define  CLASS_G_MAX  0x01ffffffffffff
#define  CLASS_H_MAX  0x00ffffffffffffff



namespace Ebml
{

	/* assign new value */
	void VInt32::setValue (uint32 value)
	{
		mValue = value;
		
		/* determine integer class */
		if      (value < CLASS_A_MAX) mLength = 1;
		else if (value < CLASS_B_MAX) mLength = 2;
		else if (value < CLASS_C_MAX) mLength = 3;
		else if (value < CLASS_D_MAX) mLength = 4;
		
		/* invalid range */
		else throw std::range_error ("Variable integer must belong to a valid class range");
	}
	
	
	/* assign new value */
	void VInt64::setValue (uint64 value)
	{
		mValue = value;
		
		
		/* determine integer class */
		if      (value < CLASS_A_MAX) mLength = 1;
		else if (value < CLASS_B_MAX) mLength = 2;
		else if (value < CLASS_C_MAX) mLength = 3;
		else if (value < CLASS_D_MAX) mLength = 4;
		else if (value < CLASS_E_MAX) mLength = 5;
		else if (value < CLASS_F_MAX) mLength = 6;
		else if (value < CLASS_G_MAX) mLength = 7;
		else if (value < CLASS_H_MAX) mLength = 8;
		
		/* invalid range */
		else throw std::range_error ("Variable integer must belong to a valid class range");
	}
	
	
	
	
	/* classed value */
	uint32 VInt32::data ()
	{
		/* determine integer class */
		switch (mLength)
		{
			case 1: return mValue | CLASS_A_MASK; break;
			case 2: return mValue | CLASS_B_MASK; break;
			case 3: return mValue | CLASS_C_MASK; break;
			case 4: return mValue | CLASS_D_MASK; break;
			default: return 0;
		}
	}
	
	
	/* classed value */
	uint64 VInt64::data ()
	{
		/* determine integer class */
		switch (mLength)
		{
			case 1: return mValue | CLASS_A_MASK; break;
			case 2: return mValue | CLASS_B_MASK; break;
			case 3: return mValue | CLASS_C_MASK; break;
			case 4: return mValue | CLASS_D_MASK; break;
			case 5: return mValue | CLASS_E_MASK; break;
			case 6: return mValue | CLASS_F_MASK; break;
			case 7: return mValue | CLASS_G_MASK; break;
			case 8: return mValue | CLASS_H_MASK; break;
			default: return 0;
		}
	}

}
