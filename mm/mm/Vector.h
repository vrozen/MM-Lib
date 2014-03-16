/******************************************************************************
 * Copyright (c) 2013-2014, Amsterdam University of Applied Sciences (HvA) and
 *                          Centrum Wiskunde & Informatica (CWI)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contributors:
 *   * Riemer van Rozen - rozen@cwi.nl - HvA / CWI
 ******************************************************************************/
/*!
 * /namespace MM
 * /class     Vector
 * /brief     The Vector abstraction stores elements by index.
 * /note      Currently wraps STL, we intend to remove this dependency.
 * /note      The Vector class hides internal details
 *            of the STL implementation of std::map
 * /file      Vector.h
 * /author    Riemer van Rozen
 * /date      September 18th 2013
 */
/******************************************************************************/


#ifndef mm_Vector_h
#define mm_Vector_h

#include <vector>

//FIXME: HACK
#if _MSC_VER
  #include <algorithm>
#endif

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
    
    MM::VOID addAll(MM::Vector<T> * other)
    {
      MM::Vector<T>::Iterator i = other->getIterator();
      while(i.hasNext())
      {
        T element = i.getNext();
        add(element);
      }
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
    
    T elementAt(MM::UINT32 pos)
    {
      return v->at(pos);
    }
    
    MM::INT32 getPosition(T element)
    {
      typename std::vector<T>::iterator begin = v->begin();
      typename std::vector<T>::iterator end = v->end();
      
      for(MM::UINT32 i = 0; begin+i < end; i++)
      {
        if(*(begin+i) == element)
        {
          return i;
        }
      }
      return -1;
    }
    
    MM::VOID remove(MM::UINT32 pos)
    {
      typename std::vector<T>::iterator i = v->begin() + pos;
      typename std::vector<T>::iterator end = v->end();
      
      if(i < end)
      {
        v->erase(i);
      }
    }
    
    MM::VOID remove(T element)
    {
      typename std::vector<T>::iterator i = v->begin();
      typename std::vector<T>::iterator end = v->end();
      
      for(; i < end; i++)
      {
        if(*i == element)
        {
          v->erase(i);
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
      if(std::find(v->begin(), v->end(), element ) < v->end())
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
        if(cur < end)
        {
          haveNext = MM_TRUE;
        }
        return haveNext;
      }
      
      T getNext()
      {
        T next = MM_NULL;
        
        next = *(this->cur);
        
        if (this->cur < this->end)
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
    
    typename MM::Vector<T>::Iterator getIterator()
    {
      return MM::Vector<T>::Iterator(v->begin(), v->end());
    }
    
    typename MM::Vector<T>::Iterator * getNewIterator()
    {
      return new MM::Vector<T>::Iterator(v->begin(), v->end());
    }
    
  };
}
#endif
