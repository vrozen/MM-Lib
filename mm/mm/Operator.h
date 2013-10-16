/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The Operator abstraction defines operator lexicals and codes.
 * @package MM
 * @file    Operator.h
 * @author  Riemer van Rozen
 * @date    July 27th 2013
 */
/******************************************************************************/
#ifndef __mm__Operator__
#define __mm__Operator__

namespace MM
{
  /**
   * @class Operator
   * @brief Operator class
   */
  class Operator
  {    
    /**
     * @enum __OP
     * @brief Operator enum
     * @typedef OP
     * @brief Operator type
     */
  public:
    typedef enum __OP
    {
      OP_ERROR,   /**< error */
      OP_ADD,     /**< +     */
      OP_SUB,     /**< -     */
      OP_MUL,     /**< *     */
      OP_DIV,     /**< /     */
      OP_AND,     /**< &&    */
      OP_OR,      /**< ||    */
      OP_GT,      /**< >     */
      OP_LT,      /**< <     */
      OP_LE,      /**< <=    */
      OP_GE,      /**< >=    */
      OP_EQ,      /**< ==    */
      OP_NEQ,     /**< !=    */
      OP_UNM,     /**< ~     */
      OP_NOT,     /**< !     */
      OP_PERCENT, /**< %     */
      OP_PER      /**< |     */
    } OP;
    static const MM::CHAR * OP_STR[]; /**< Operator strings*/
    static const MM::UINT32 OP_LEN[]; /**< Operator string lengths*/
  };
}

#endif /* defined(__mm__Operator__) */
