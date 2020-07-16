
// COS30008, Problem Set 7, 2020

#pragma once

#include "List.h"
#include "DoublyLinkedNodeIterator.h"
#include "DoublyLinkedNode.h"
#include <stdexcept>

using namespace std;

template<class T>
class Queue
{
private:
  List<T> fElements;

public:
	//Definition for iterator usage
	typedef DoublyLinkedNodeIterator<T> Iterator;

	//Checks if the queue is empty
  bool isEmpty() const
  {
	  return fElements.isEmpty();
  }

  //Returns the size of the queue
  int size() const
  {
	  return fElements.size();
  }

  //Inserts item into the back of the queue
  void enqueue(const T& aElement)
  {
	  fElements.push_back(aElement);
  }

  //Removes the last item of the queue
  void dequeue()
  {
	  //Checks if queue is not empty
	  if (!fElements.isEmpty())
	  {
		  fElements.remove(fElements[0]);
	  }
	  else
	  {
		  throw exception("Unable to dequeue an empty list");
	  }
  }

  //Returns the item at the top of the queue
  const T& top() const
  {
	  //Checks if queue is not empty
	  if (!fElements.isEmpty())
	  {
		  return fElements[0];
	  }
	  else
	  {
		  throw exception("Unable to retreive from an empty list");
	  }
  }

  // stack indexer
  const T& operator[](size_t aIndex) const
  {
	  //Checks to see if index is within bounds of queue
	  if ((aIndex >= 0) && (aIndex < fElements.size()))
	  {
		  return fElements[aIndex];
	  }
	  else
	  {
		  throw std::range_error("Index out of bounds.");
	  }
  }
 
  // stack iterators

  //Return forward iterator
  Iterator begin() const
  {
	  return fElements.begin();
  }

  //Return forward end iterator
  Iterator end() const
  {
	  return fElements.end();
  }

  //Return reverse iterator
  Iterator rbegin() const
  {
	  return fElements.rbegin();
  }

  //Return reverse end iterator
  Iterator rend() const
  {
	  return fElements.rend();
  }
};
