//
//  Vector.h
//  mm
//
//  Created by Riemer van Rozen on 9/18/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef mm_Vector_h
#define mm_Vector_h

#include <vector>

//The Vector class hides internal details
//of the STL implementation of std::vector
namespace MM
{
  template <class T>
  class Vector
  {
  private:
    std::vector<T> * v;
   
  public:
    Vector()
    {
      v = new std::vector<T>();
    }
    
    ~Vector()
    {
      delete v;
    }
    
    //FIXME: same id for different types...
    virtual MM::TID getTypeId()
    {
      return MM::T_Vector;
    }
    
    virtual MM::BOOLEAN instanceof(MM::TID tid)
    {
      if(tid == MM::T_Vector)
      {
        return MM_TRUE;
      }
      else
      {
        return MM_FALSE;
      }
    }
    
    MM::VOID add(T element)
    {
      v->push_back(element);
    }
    
    T pop()
    {
      T element = v->back();
      v->pop_back();
      return element;
    }
    
    MM::BOOLEAN isEmpty()
    {
      MM::BOOLEAN empty = MM_FALSE;
      if(v->empty())
      {
        empty = MM_TRUE;
      }      
      return empty;
    }
    
    MM::VOID remove(T element)
    {
      typename std::vector<T>::iterator i = v->begin();
      typename std::vector<T>::iterator end = v->end();
      
      for(; i != end; i++)
      {
        if(*i == element)
        {
          v->erase(i);
          //delete *i;
          break;
        }
      }
    }
    
    MM::VOID clear()
    {
      v->clear();
    }
    
    T at(MM::UINT32 pos)
    {
      return (*v)[pos];
    }
    
    MM::BOOLEAN contains(T element)
    {
      
      MM::BOOLEAN contains = MM_FALSE;
      if(std::find(v->begin(), v->end(), element ) != v->end())
      {
        contains = MM_TRUE;
      }
      return contains;
    }
    
    MM::UINT32 size()
    {
      return v->size();
    }
    
    class Iterator
    {
    private:
      typename std::vector<T>::iterator begin;
      typename std::vector<T>::iterator end;
      typename std::vector<T>::iterator cur;
    public:
      Iterator(typename std::vector<T>::iterator begin,
               typename std::vector<T>::iterator end)
      {
        this->begin = begin;
        this->end = end;
        this->cur = begin;
      }
      
      ~Iterator()
      {
      }
      
      MM::BOOLEAN hasNext()
      {
        MM::BOOLEAN haveNext = MM_FALSE;
        if(cur != end)
        {
          haveNext = MM_TRUE;
        }
        return haveNext;
      }
      
      T getNext()
      {
        T next = MM_NULL;
        
        next = *(this->cur);
        
        if (this->cur != this->end)
        {
          (this->cur)++;
        }
        
        return next;
      }
      
      MM::VOID reset()
      {
        this->cur = this->begin;
      }
      
    };
    
    MM::Vector<T>::Iterator getIterator()
    {
      return MM::Vector<T>::Iterator(v->begin(), v->end());
    }
    
  };
}
#endif
