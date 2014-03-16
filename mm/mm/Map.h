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
 * \namespace MM
 * \class     Map
 * \brief     The Map abstraction enables quickly looking up
 *            stored values using a storage key.
 * \note      Currently wraps STL, we intend to remove this dependency.
 * \note      The Map class hides internal details
 *            of the STL implementation of std::map
 * \file      Map.h
 * \author    Riemer van Rozen
 * \date      September 13th 2013
 */
/******************************************************************************/

#ifndef __mm__Map__
#define __mm__Map__

#include <functional>
#include <map>

namespace MM
{
  template <class MAP_KEY, class MAP_VALUE, class COMPARE=std::less<MAP_KEY> >
  class Map
  {
  private:
    std::map<MAP_KEY, MAP_VALUE, COMPARE> * map;
  public:
    Map()
    {
      map = new std::map<MAP_KEY, MAP_VALUE, COMPARE>();
    }
    
    Map(MM::Map<MAP_KEY,MAP_VALUE,COMPARE> * map)
    {
      this->map = new std::map<MAP_KEY,MAP_VALUE,COMPARE>(*map->map);
    }
    
    ~Map()
    {
      delete map;
    }

    //FIXME: same id for different types
    virtual MM::TID getTypeId()
    {
      return MM::T_Map;
    }
    
    //FIXME: same id for different types
    virtual MM::BOOLEAN instanceof(MM::TID tid)
    {
      if(tid == MM::T_Map)
      {
        return MM_TRUE;
      }
      else
      {
        return MM_FALSE;
      }
    }
  
    /*static const MM::UINT32 typeId()
    {
      return reinterpret_cast<MM::UINT32>(&typeId);
    }
    
    virtual MM::UINT32 getTypeId()
    {
      return getTypeId();
    }*/

    MM::VOID put(MAP_KEY k, MAP_VALUE v)
    {
      (*map)[k] = v;
    }
    
    MM::VOID putAll(MM::Map<MAP_KEY, MAP_VALUE, COMPARE> * other)
    {
      MM::Map<MAP_KEY, MAP_VALUE, COMPARE>::Iterator i = other->getIterator();
      
      while(i.hasNext())
      {
        MAP_KEY k;
        MAP_VALUE v = i.getNext(&k);
        put(k,v);
      }
    }
    
    MAP_VALUE get(MAP_KEY k)
    {
      typename std::map<MAP_KEY, MAP_VALUE, COMPARE>::iterator i;
      
      MAP_VALUE v = MM_NULL;
      
      i = map->find(k);
      
      if(i != map->end())
      {
        v = i->second;
      }
      
      return v;
    }
    
    MM::VOID remove(MAP_KEY k)
    {
      map->erase(k);
    }
    
    MM::BOOLEAN contains(MAP_KEY k)
    {
      MM::BOOLEAN r = MM_FALSE;
      if(map->count(k) != 0)
      {
        r = MM_TRUE;
      }
      else
      {
        r = MM_FALSE;
      }
      return r;
    }
    
    MM::VOID clear()
    {
      map->clear();
    }
    
    MM::BOOLEAN isEmpty()
    {
      if(map->empty() == true)
      {
        return MM_TRUE;
      }
      else
      {
        return MM_FALSE;
      }
    }
    
    class Iterator
    {
    private:
      typename std::map<MAP_KEY, MAP_VALUE, COMPARE>::iterator begin;
      typename std::map<MAP_KEY, MAP_VALUE, COMPARE>::iterator end;
      typename std::map<MAP_KEY, MAP_VALUE, COMPARE>::iterator cur;
    public:
      Iterator(typename std::map<MAP_KEY, MAP_VALUE, COMPARE>::iterator begin,
               typename std::map<MAP_KEY, MAP_VALUE, COMPARE>::iterator end)
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
      
      MAP_VALUE getNext()
      {
        MAP_VALUE next = MM_NULL;
        
        next = (*(this->cur)).second;
        
        if (this->cur != this->end)
        {
          (this->cur)++;
        }
        
        return next;
      }
      
      MAP_VALUE getNext(MAP_KEY * key)
      {
        MAP_VALUE next = MM_NULL;
        
        next = (*(this->cur)).second;
        * key = (*(this->cur)).first;
        
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
    
    typename MM::Map<MAP_KEY, MAP_VALUE, COMPARE>::Iterator getIterator()
    {
      return MM::Map<MAP_KEY, MAP_VALUE, COMPARE>::Iterator(map->begin(), map->end());
    }

    
    //MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__Map__) */
