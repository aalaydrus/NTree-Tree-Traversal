#pragma once

#include "DoublyLinkedNode.h"

template<class DataType> 
class DoublyLinkedNodeIterator
{
private:
	enum IteratorStates { BEFORE, DATA , AFTER }; 
	
	IteratorStates fState;

	typedef DoublyLinkedNode<DataType> Node;

	const Node* fLeftmost; 
	const Node* fRightmost; 
	const Node* fCurrent;
    
public:
	typedef DoublyLinkedNodeIterator<DataType> Iterator;

	DoublyLinkedNodeIterator( const Node& aList ); 
	
	// dereference
	const DataType& operator*() const;
	// prefix increment
	Iterator& operator++();	
	// postfix increment
	Iterator operator++(int);
	// prefix decrement
	Iterator& operator--();	
	// postfix decrement
	Iterator operator--(int);

	bool operator==( const Iterator& aOtherIter ) const; 
	bool operator!=( const Iterator& aOtherIter ) const;

    Iterator begin() const;
    Iterator end() const;
    Iterator rbegin() const;
    Iterator rend() const;
};

// implementation

template<class DataType> 
DoublyLinkedNodeIterator<DataType>::DoublyLinkedNodeIterator( const Node& aList )
{
	// set leftmost element
	fLeftmost = &aList;

	while ( &fLeftmost->getPrevious() != &Node::NIL )
	{
		fLeftmost = &fLeftmost->getPrevious();	
	}

	// set current to first
	fCurrent = fLeftmost;

	if ( fCurrent != &Node::NIL )
		fState = DATA;
	else
		fState = AFTER;

	// set rightmost element
	fRightmost = &aList;

	while ( &fRightmost->getNext() != &Node::NIL )
	{
		fRightmost = &fRightmost->getNext();
	}
}
	
template<class DataType> 
const DataType& DoublyLinkedNodeIterator<DataType>::operator*() const
{
	return fCurrent->getValue();
}

template<class DataType>
DoublyLinkedNodeIterator<DataType>& DoublyLinkedNodeIterator<DataType>::operator++()
{
    // or if-then-else
	switch ( fState )
	{
	case BEFORE:
		fCurrent = fLeftmost;
		if ( fCurrent == &Node::NIL )
		{
			fState = AFTER;
		}
		else
		{
			fState = DATA;
		}
		break;
	case DATA:
		fCurrent = &fCurrent->getNext();
		if ( fCurrent == &Node::NIL )
		{
			fState = AFTER;
		}
		break;
	default: ;
	}

	return *this;
}

template<class DataType> 
DoublyLinkedNodeIterator<DataType> DoublyLinkedNodeIterator<DataType>::operator++(int)
{
	Iterator temp = *this;

	++(*this);

	return temp;
}

template<class DataType> 
DoublyLinkedNodeIterator<DataType>& DoublyLinkedNodeIterator<DataType>::operator--()
{
	switch ( fState )
	{
	case AFTER:
		fCurrent = fRightmost;
		if ( fCurrent == &Node::NIL )
		{
			fState = BEFORE;
		}
		else
		{
			fState = DATA;
		}
		break;
	case DATA:
		fCurrent = &fCurrent->getPrevious();
		if ( fCurrent == &Node::NIL )
		{
			fState = BEFORE;
		}
		break;
	default: ;
	}

	return *this;
}

template<class DataType> 
DoublyLinkedNodeIterator<DataType> DoublyLinkedNodeIterator<DataType>::operator--(int)
{
	Iterator temp = *this;

	--(*this);

	return temp;
}

template<class DataType> 
bool DoublyLinkedNodeIterator<DataType>::operator==( const Iterator& aOtherIter ) const
{
	return fLeftmost == aOtherIter.fLeftmost &&
		fRightmost == aOtherIter.fRightmost &&
		fCurrent == aOtherIter.fCurrent &&
		fState == aOtherIter.fState;
}

template<class DataType> 
bool DoublyLinkedNodeIterator<DataType>::operator!=( const Iterator& aOtherIter ) const
{
	return !(*this == aOtherIter);
}

template<class DataType>
DoublyLinkedNodeIterator<DataType> DoublyLinkedNodeIterator<DataType>::begin() const
{
    return ++(rend());
}

template<class DataType>
DoublyLinkedNodeIterator<DataType> DoublyLinkedNodeIterator<DataType>::end() const
{
    Iterator temp = *this;
    
    temp.fCurrent = &Node::NIL;
    temp.fState = AFTER;
    
    return temp;
}

template<class DataType>
DoublyLinkedNodeIterator<DataType> DoublyLinkedNodeIterator<DataType>::rbegin() const
{
    return --(end());
}

template<class DataType>
DoublyLinkedNodeIterator<DataType> DoublyLinkedNodeIterator<DataType>::rend() const
{
	Iterator temp = *this;

	temp.fCurrent = &Node::NIL;
	temp.fState = BEFORE;

	return temp;
}

