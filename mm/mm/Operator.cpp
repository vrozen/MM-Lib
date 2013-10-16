/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The Operator abstraction defines operator lexicals and codes.
 * @package MM
 * @file    Operator.cpp
 * @author  Riemer van Rozen
 * @date    July 27th 2013
 */
/******************************************************************************/
#include <string.h>
#include "Types.h"
#include "Operator.h"

const MM::CHAR * MM::Operator::OP_STR[] =
{
  "error",
  "+",
  "-",
  "*",
  "/",
  "&&",
  "||",
  ">",
  "<",
  "<=",
  ">=",
  "==",
  "!=",
  "~",
  "!",
  "%",
  "|"
};

const MM::UINT32 MM::Operator::OP_LEN[] =
{
  strlen(OP_STR[0]), /**> error */
  strlen(OP_STR[1]), /**> +     */
  strlen(OP_STR[2]), /**> -     */
  strlen(OP_STR[3]), /**> *     */
  strlen(OP_STR[4]), /**> /     */
  strlen(OP_STR[5]), /**> &&    */
  strlen(OP_STR[6]), /**> ||    */
  strlen(OP_STR[7]), /**> >     */
  strlen(OP_STR[8]), /**> <     */
  strlen(OP_STR[9]), /**> <=    */
  strlen(OP_STR[10]), /**> >=    */
  strlen(OP_STR[11]), /**> ==    */
  strlen(OP_STR[12]), /**> !=    */
  strlen(OP_STR[13]), /**> ~     */
  strlen(OP_STR[14]), /**> !     */
  strlen(OP_STR[15]), /**> %     */
  strlen(OP_STR[16])  /**> |     */
};
