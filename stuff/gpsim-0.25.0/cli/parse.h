/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ABORT = 258,
     ATTACH = 259,
     BREAK = 260,
     BUS = 261,
     CLEAR = 262,
     DISASSEMBLE = 263,
     DUMP = 264,
     ENDM = 265,
     FREQUENCY = 266,
     HELP = 267,
     LOAD = 268,
     LOG = 269,
     LIST = 270,
     NODE = 271,
     MACRO = 272,
     MODULE = 273,
     PROCESSOR = 274,
     QUIT = 275,
     RESET = 276,
     RUN = 277,
     SET = 278,
     SHELL = 279,
     STEP = 280,
     STIMULUS = 281,
     SYMBOL = 282,
     TRACE = 283,
     gpsim_VERSION = 284,
     X = 285,
     ICD = 286,
     END_OF_COMMAND = 287,
     MACROBODY_T = 288,
     MACROINVOCATION_T = 289,
     INDIRECT = 290,
     END_OF_INPUT = 291,
     BIT_FLAG = 292,
     EXPRESSION_OPTION = 293,
     NUMERIC_OPTION = 294,
     STRING_OPTION = 295,
     CMD_SUBTYPE = 296,
     SYMBOL_OPTION = 297,
     LITERAL_INT_T = 298,
     LITERAL_BOOL_T = 299,
     LITERAL_FLOAT_T = 300,
     LITERAL_STRING_T = 301,
     LITERAL_ARRAY_T = 302,
     SYMBOL_T = 303,
     GPSIMOBJECT_T = 304,
     PORT_T = 305,
     EQU_T = 306,
     AND_T = 307,
     COLON_T = 308,
     COMMENT_T = 309,
     DIV_T = 310,
     EOLN_T = 311,
     MINUS_T = 312,
     MPY_T = 313,
     OR_T = 314,
     PLUS_T = 315,
     SHL_T = 316,
     SHR_T = 317,
     XOR_T = 318,
     INDEXERLEFT_T = 319,
     INDEXERRIGHT_T = 320,
     DECLARE_TYPE = 321,
     DECLARE_INT_T = 322,
     DECLARE_FLOAT_T = 323,
     DECLARE_BOOL_T = 324,
     DECLARE_CHAR_T = 325,
     LOR_T = 326,
     LAND_T = 327,
     NE_T = 328,
     EQ_T = 329,
     ABS_T = 330,
     MAX_T = 331,
     MIN_T = 332,
     GE_T = 333,
     GT_T = 334,
     LE_T = 335,
     LT_T = 336,
     IND_T = 337,
     BITS_T = 338,
     BIT_T = 339,
     WORD_T = 340,
     LADDR_T = 341,
     HIGH_T = 342,
     LOW_T = 343,
     INDEXED_T = 344,
     UNARYOP_PREC = 345,
     ONESCOMP_T = 346,
     LNOT_T = 347,
     POW_T = 348,
     REG_T = 349
   };
#endif
/* Tokens.  */
#define ABORT 258
#define ATTACH 259
#define BREAK 260
#define BUS 261
#define CLEAR 262
#define DISASSEMBLE 263
#define DUMP 264
#define ENDM 265
#define FREQUENCY 266
#define HELP 267
#define LOAD 268
#define LOG 269
#define LIST 270
#define NODE 271
#define MACRO 272
#define MODULE 273
#define PROCESSOR 274
#define QUIT 275
#define RESET 276
#define RUN 277
#define SET 278
#define SHELL 279
#define STEP 280
#define STIMULUS 281
#define SYMBOL 282
#define TRACE 283
#define gpsim_VERSION 284
#define X 285
#define ICD 286
#define END_OF_COMMAND 287
#define MACROBODY_T 288
#define MACROINVOCATION_T 289
#define INDIRECT 290
#define END_OF_INPUT 291
#define BIT_FLAG 292
#define EXPRESSION_OPTION 293
#define NUMERIC_OPTION 294
#define STRING_OPTION 295
#define CMD_SUBTYPE 296
#define SYMBOL_OPTION 297
#define LITERAL_INT_T 298
#define LITERAL_BOOL_T 299
#define LITERAL_FLOAT_T 300
#define LITERAL_STRING_T 301
#define LITERAL_ARRAY_T 302
#define SYMBOL_T 303
#define GPSIMOBJECT_T 304
#define PORT_T 305
#define EQU_T 306
#define AND_T 307
#define COLON_T 308
#define COMMENT_T 309
#define DIV_T 310
#define EOLN_T 311
#define MINUS_T 312
#define MPY_T 313
#define OR_T 314
#define PLUS_T 315
#define SHL_T 316
#define SHR_T 317
#define XOR_T 318
#define INDEXERLEFT_T 319
#define INDEXERRIGHT_T 320
#define DECLARE_TYPE 321
#define DECLARE_INT_T 322
#define DECLARE_FLOAT_T 323
#define DECLARE_BOOL_T 324
#define DECLARE_CHAR_T 325
#define LOR_T 326
#define LAND_T 327
#define NE_T 328
#define EQ_T 329
#define ABS_T 330
#define MAX_T 331
#define MIN_T 332
#define GE_T 333
#define GT_T 334
#define LE_T 335
#define LT_T 336
#define IND_T 337
#define BITS_T 338
#define BIT_T 339
#define WORD_T 340
#define LADDR_T 341
#define HIGH_T 342
#define LOW_T 343
#define INDEXED_T 344
#define UNARYOP_PREC 345
#define ONESCOMP_T 346
#define LNOT_T 347
#define POW_T 348
#define REG_T 349




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 140 "parse.yy"
{
  guint32              i;
  guint64             li;
  float                f;
  char                *s;
  cmd_options        *co;
  cmd_options_num   *con;
  cmd_options_str   *cos;
  cmd_options_expr  *coe;

  BinaryOperator*           BinaryOperator_P;
  Boolean*                  Boolean_P;
  Expression*               Expression_P;
  Float*                    Float_P;
  Integer*                  Integer_P;
  String*                   String_P;
  gpsimObject*              Symbol_P;
  gpsimObject*              gpsimObject_P;

  StringList_t             *StringList_P;
  ExprList_t               *ExprList_P;
  gpsimObjectList_t        *gpsimObjectList_P;

  Macro                    *Macro_P;
}
/* Line 1489 of yacc.c.  */
#line 263 "parse.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



