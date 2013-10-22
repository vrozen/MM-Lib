//
//  Map.h
//  mm
//
//  Created by Riemer van Rozen on 9/13/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Map__
#define __mm__Map__

#include <functional>
#include <map>

//The Map class hides internal details of the STL implementation of std::map
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
    
    MM::Map<MAP_KEY, MAP_VALUE, COMPARE>::Iterator getIterator()
    {
      return MM::Map<MAP_KEY, MAP_VALUE, COMPARE>::Iterator(map->begin(), map->end());
    }

    
    //MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__Map__) */
