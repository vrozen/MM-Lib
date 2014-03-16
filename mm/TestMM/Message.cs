#if __cplusplus
namespace MM
{
#else
namespace LibMM
{
  public
#endif
  enum MESSAGE
  {
    MSG_ERROR,    //error message
    
    //type creation messages
    MSG_NEW_TYPE,   //a new type definition was created
    MSG_NEW_DECL,   //a declaration of a certain type was made in a definition
    MSG_NEW_POOL,   //a pool was added to a definiton
    MSG_NEW_SOURCE, //a source was added to a definition
    MSG_NEW_DRAIN,  //a drain was added to a definition
    MSG_NEW_GATE,   //a gate was added to a definition
    MSG_NEW_REF,    //a reference (alias) was added to a definition
    MSG_NEW_CONVERTER,
 
    MSG_NEW_CONDITION,
    MSG_NEW_TRIGGER,
    MSG_NEW_FLOW,

    
    //type deletion messages
    MSG_DEL_TYPE,   //a type definition was deleted
    MSG_DEL_DECL,   //a declaration was undeclared from a definition
    MSG_DEL_POOL,   //a pool was removed from a definition
    MSG_DEL_SOURCE, //a source was removed from a definition
    MSG_DEL_DRAIN,  //a drain was removed from a definition
    MSG_DEL_GATE,   //a gate was removed from a definition
    MSG_DEL_REF,    //a reference (alias) was removed from a definition
    MSG_DEL_CONVERTER,

    MSG_DEL_CONDITION,
    MSG_DEL_TRIGGER,
    MSG_DEL_FLOW,
    
    //type update messages
    MSG_UPD_TYPE,   //a type definition was updated
    MSG_UPD_DECL,   //a declaration was updated (it changed type!)
    MSG_UPD_POOL,   //a pool was updated (changed modifiers)
    MSG_UPD_SOURCE, //a source was updated (changed modifiers)
    MSG_UPD_DRAIN,  //a drain was updated (changed modifiers)
    MSG_UPD_GATE,   //a gate was updated (changed modifiers)
    MSG_UPD_REF,    //a reference was updated (can this happen?)
    MSG_UPD_CONVERTER,
    
    MSG_UPD_CONDITION,
    MSG_UPD_TRIGGER,
    MSG_UPD_FLOW,
    
    //instance messages
    MSG_NEW_INST,   //a new instance was created inside another instance
    MSG_DEL_INST,   //an instance was deleted from another instance
    
    //instance flow messages needed?
    
    //instance value messages
    MSG_ADD_VALUE,
    MSG_SUB_VALUE,
	MSG_HAS_VALUE,
    
    //instance trigger message
    MSG_TRIGGER,   //a trigger inside an instance happened

    //instance activated message
    MSG_ACTIVATED, //a node inside an instance was activated
    
    //instance disabled message
    MSG_DISABLED,  //a node inside an instance was not activated
                   //because at least one of its conditions was false
    
    //instance signal condition message
    MSG_SIGNAL     //an invariant inside an instance was violated
  };

#if __cplusplus
};
typedef enum MESSAGE MSG;

#else
}
#endif