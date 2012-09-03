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

#ifndef ENDIANSWAP_H_
#define ENDIANSWAP_H_


#include <Ebml/Config.h>


namespace Ebml
{

	namespace Endian
	{
	
		/* reverse 16 bit integer */
		static inline void swap (uint16 &b)
		{
			/* AA BB -> BB AA */
			b = (b >> 8) | (b << 8);
		}
		
		
		/* reverse 32 bit integer */
		static inline void swap (uint32 &b)
		{
			/* AA BB CC DD -> DD CC BB AA */
			b = (b >> 24) |
				((b & 0x00ff0000) >> 8) |
				((b & 0x0000ff00) << 8) |
				(b << 24);
		}
		
		
		/* reverse 64 bit integer */
		static inline void swap (uint64 &b)
		{
			/* AA BB CC DD EE FF GG HH -> HH GG FF EE DD CC BB AA */
			b = (b >> 56) |
				((b & 0x00ff000000000000) >> 40) |
				((b & 0x0000ff0000000000) >> 24) |
				((b & 0x000000ff00000000) >> 8) |
				((b & 0x00000000ff000000) << 8) |
				((b & 0x0000000000ff0000) << 24) |
				((b & 0x000000000000ff00) << 40) |
				(b << 56);
		}
		
		
		
		
		
		
		/* reverse 16 bit integer */
		template <class T>
		static inline T swap16 (const T &b)
		{
			#if !SYSTEM_IS_BIG_ENDIAN
				/* AA BB -> BB AA */
				return  (b >> 8) | (b << 8);
				
			#endif
		}
		
		
		/* reverse 32 bit integer */
		template <class T>
		static inline T swap32 (const T &b)
		{
			#if SYSTEM_IS_BIG_ENDIAN
				return b;
			#else
				
				/* AA BB CC DD -> DD CC BB AA */
				return (b >> 24) |
					   ((b & 0x00ff0000) >> 8) |
					   ((b & 0x0000ff00) << 8) |
					   (b << 24);
				
			#endif
		}
		
		
		
		/* reverse 64 bit integer */
		template <class T>
		static inline T swap64 (const T &b)
		{
			#if SYSTEM_IS_BIG_ENDIAN
				return b;
			#else
				
				/* AA BB CC DD EE FF GG HH -> HH GG FF EE DD CC BB AA */
				return (b >> 56) |
					   ((b & 0x00ff000000000000) >> 40) |
					   ((b & 0x0000ff0000000000) >> 24) |
					   ((b & 0x000000ff00000000) >> 8) |
					   ((b & 0x00000000ff000000) << 8) |
					   ((b & 0x0000000000ff0000) << 24) |
					   ((b & 0x000000000000ff00) << 40) |
					   (b << 56);
				
			#endif
		}
	
	};

}


#endif /* ENDIANSWAP_H_ */
