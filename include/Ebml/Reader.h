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

#ifndef READER_H_
#define READER_H_


#include <Ebml/Types.h>
#include <Ebml/Stream.h>
#include <Ebml/Element.h>
#include <string>
#include <iterator>


namespace Ebml
{

	class ReaderElement : public Element
	{
	private:
		Stream* mStream;
		uint64 mIndex;
		
		ReaderElement* mChild;
		
		
	public:
		ReaderElement (Stream* stream, uint32 id, uint64 size);
		explicit ReaderElement (Stream* stream);
		virtual ~ReaderElement ();
		
		
		uint64 getIndex() { return mIndex; }
		void setIndex (uint64 value) { mIndex = value; }
		void addIndex (uint64 value) { mIndex += value; }
		
		
		/* data properties */
		const uint8* getValue ();
		void getValue (uint8* data);
		
		
		ReaderElement* getNextChild ();
	};
	
	
	
	
	class Reader
	{
	private:
		Stream* mStream;
		bool mInternalStream;
		
		ReaderElement* mRoot;
		
		
	public:
		explicit Reader (Stream* stream);
		explicit Reader (const std::string& file);
		~Reader ();
		
		
		bool open ();
		void close ();
		
		
//		ReaderElement* getRoot() { return mRoot; }
//		ReaderElement* getNext() { return mRoot->getNextChild(); }
		
		
		
		/* forward iterator class */
		class iterator : public std::iterator<std::forward_iterator_tag, ReaderElement*>
		{
		private:
			ReaderElement* mRoot;
			ReaderElement* mChild;
			
			
		public:
			iterator (ReaderElement* root) : mRoot(root), mChild(root ? root->getNextChild() : 0) {}
			iterator () : mRoot(0), mChild(0) {}
			~iterator () {}
			
			
			/* equality operators */
			bool operator== (const iterator& other) { return mChild == other.mChild; }
			bool operator!= (const iterator& other) { return mChild != other.mChild; }
			
			
			
			/* dereference operator */
			Element* operator* () { assert (mRoot); return mChild; }
			
			/* indirection operator */
			Element* operator-> () { assert (mRoot); return mChild; }
			
			
			/* assignment operator */
			iterator& operator= (const iterator& other)
			{
				mRoot  = other.mRoot;
				mChild = other.mChild;
				return *this;
			}
			
			
			/* prefix increment operator */
			iterator operator++ ()
			{
				assert (mRoot);
				mChild = mRoot->getNextChild ();
				return *this;
			}
			
			/* postfix increment operator */
			iterator operator++ (int)
			{
				iterator tmp = *this;
				++(*this);
				return tmp;
			}
			
			
			
			/* get the current node */
			ReaderElement* get() { return mChild; }
			
			
			/* iterator accessors */
			iterator begin (ReaderElement* root) { return iterator (root); }
			iterator begin() { return iterator (mChild); }
			iterator end() { return iterator (); }
			
		}; /* end iterator class */
		
		
		
		/* iterator accessors */
		iterator begin() { return iterator (mRoot); }
		iterator end() { return iterator (); }
	};

}


#endif /* READER_H_ */
