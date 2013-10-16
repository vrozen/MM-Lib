//
//  Evaluator.h
//  mm
//
//  Created by Riemer van Rozen on 9/26/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Evaluator__
#define __mm__Evaluator__

namespace  MM
{
  class Evaluator
  {
  private:
    MM::Machine * m;
  public:
    
    Evaluator(MM::Machine * m);
    
    ~Evaluator();    
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    
    //------------------------------------------------------------
    //Visitor
    //------------------------------------------------------------
    MM::ValExp * eval(MM::Exp * exp,
                      MM::Instance * i,
                      MM::Edge * e);

  private:
    MM::ValExp * eval(MM::OneExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::ActiveExp * exp,
                      MM::Instance *i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::DieExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::OverrideExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::VarExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::AllExp exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::BinExp * exp,
                      MM::Instance *i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::UnExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::BooleanValExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::NumberValExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::RangeValExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    //------------------------------------------------------------
    //BinExp Visitor
    //------------------------------------------------------------    
    MM::ValExp * eval(MM::ValExp * e1,
                      MM::Operator::OP op,
                      MM::ValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::BooleanValExp * e1,
                      MM::Operator::OP op,
                      MM::BooleanValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e);

    MM::ValExp * eval(MM::BooleanValExp * e1,
                      MM::Operator::OP op,
                      MM::NumberValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e);

    MM::ValExp * eval(MM::BooleanValExp * e1,
                      MM::Operator::OP op,
                      MM::RangeValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::NumberValExp * e1,
                      MM::Operator::OP op,
                      MM::BooleanValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::NumberValExp * e1,
                      MM::Operator::OP op,
                      MM::NumberValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e);

    MM::ValExp * eval(MM::NumberValExp * e1,
                      MM::Operator::OP op,
                      MM::RangeValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e);

    MM::ValExp * eval(MM::RangeValExp * e1,
                      MM::Operator::OP op,
                      MM::BooleanValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e);

    MM::ValExp * eval(MM::RangeValExp * e1,
                      MM::Operator::OP op,
                      MM::NumberValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e); 

    MM::ValExp * eval(MM::RangeValExp * e1,
                      MM::Operator::OP op,
                      MM::RangeValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e);
    
    //------------------------------------------------------------
    //UnExp Visitor
    //------------------------------------------------------------
    MM::ValExp * eval(MM::Operator::OP op,
                      MM::ValExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::Operator::OP op,
                      MM::BooleanValExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);

    MM::ValExp * eval(MM::Operator::OP op,
                      MM::NumberValExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);

    MM::ValExp * eval(MM::Operator::OP op,
                      MM::RangeValExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
  };
}
#endif /* defined(__mm__Evaluator__) */
