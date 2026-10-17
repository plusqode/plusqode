/*
 * Copyright (C) 2026 - PlusQode - www.plusqode.com - plusqode@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
     quoteToken = 258,
     dotToken = 259,
     semicolonToken = 260,
     colonToken = 261,
     commaToken = 262,
     openBraceToken = 263,
     closeBraceToken = 264,
     openSquareBracketToken = 265,
     closeSquareBracketToken = 266,
     openRoundBracketToken = 267,
     closeRoundBracketToken = 268,
     assignmentToken = 269,
     keywordToken = 270,
     stringToken = 271,
     string2Token = 272,
     charToken = 273,
     intToken = 274,
     floatToken = 275,
     boolToken = 276,
     wicketToken = 277,
     atToken = 278,
     symbolToken = 279,
     greaterToken = 280
   };
#endif
/* Tokens.  */
#define quoteToken 258
#define dotToken 259
#define semicolonToken 260
#define colonToken 261
#define commaToken 262
#define openBraceToken 263
#define closeBraceToken 264
#define openSquareBracketToken 265
#define closeSquareBracketToken 266
#define openRoundBracketToken 267
#define closeRoundBracketToken 268
#define assignmentToken 269
#define keywordToken 270
#define stringToken 271
#define string2Token 272
#define charToken 273
#define intToken 274
#define floatToken 275
#define boolToken 276
#define wicketToken 277
#define atToken 278
#define symbolToken 279
#define greaterToken 280




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 32 "pconfigurationparser.y"
{
  char* str;
  PVariant* variant;
  PVariantList* array;
  PVariantMap* hash;
}
/* Line 1489 of yacc.c.  */
#line 106 "pconfigurationparser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

