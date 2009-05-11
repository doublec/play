/* A recursive-descent parser generated by peg 0.1.2 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYRULECOUNT 5

#include <iostream>
#include <cstring>
#include "expr.h"

#define YYSTYPE Object*

#ifndef YY_VARIABLE
#define YY_VARIABLE(T)	static T
#endif
#ifndef YY_LOCAL
#define YY_LOCAL(T)	static T
#endif
#ifndef YY_ACTION
#define YY_ACTION(T)	static T
#endif
#ifndef YY_RULE
#define YY_RULE(T)	static T
#endif
#ifndef YY_PARSE
#define YY_PARSE(T)	T
#endif
#ifndef YYPARSE
#define YYPARSE		yyparse
#endif
#ifndef YYPARSEFROM
#define YYPARSEFROM	yyparsefrom
#endif
#ifndef YY_INPUT
#define YY_INPUT(buf, result, max_size)			\
  {							\
    int yyc= getchar();					\
    result= (EOF == yyc) ? 0 : (*(buf)= yyc, 1);	\
    yyprintf((stderr, "<%c>", yyc));			\
  }
#endif
#ifndef YY_BEGIN
#define YY_BEGIN	( yybegin= yypos, 1)
#endif
#ifndef YY_END
#define YY_END		( yyend= yypos, 1)
#endif
#ifdef YY_DEBUG
# define yyprintf(args)	fprintf args
#else
# define yyprintf(args)
#endif
#ifndef YYSTYPE
#define YYSTYPE	int
#endif

#ifndef YY_PART

typedef void (*yyaction)(char *yytext, int yyleng);
typedef struct _yythunk { int begin, end;  yyaction  action;  struct _yythunk *next; } yythunk;

YY_VARIABLE(char *   ) yybuf= 0;
YY_VARIABLE(int	     ) yybuflen= 0;
YY_VARIABLE(int	     ) yypos= 0;
YY_VARIABLE(int	     ) yylimit= 0;
YY_VARIABLE(char *   ) yytext= 0;
YY_VARIABLE(int	     ) yytextlen= 0;
YY_VARIABLE(int	     ) yybegin= 0;
YY_VARIABLE(int	     ) yyend= 0;
YY_VARIABLE(int	     ) yytextmax= 0;
YY_VARIABLE(yythunk *) yythunks= 0;
YY_VARIABLE(int	     ) yythunkslen= 0;
YY_VARIABLE(int      ) yythunkpos= 0;
YY_VARIABLE(YYSTYPE  ) yy;
YY_VARIABLE(YYSTYPE *) yyval= 0;
YY_VARIABLE(YYSTYPE *) yyvals= 0;
YY_VARIABLE(int      ) yyvalslen= 0;

YY_LOCAL(int) yyrefill(void)
{
  int yyn;
  while (yybuflen - yypos < 512)
    {
      yybuflen *= 2;
      yybuf= (char*)realloc(yybuf, yybuflen);
    }
  YY_INPUT((yybuf + yypos), yyn, (yybuflen - yypos));
  if (!yyn) return 0;
  yylimit += yyn;
  return 1;
}

YY_LOCAL(int) yymatchDot(void)
{
  if (yypos >= yylimit && !yyrefill()) return 0;
  ++yypos;
  return 1;
}

YY_LOCAL(int) yymatchChar(int c)
{
  if (yypos >= yylimit && !yyrefill()) return 0;
  if (yybuf[yypos] == c)
    {
      ++yypos;
      yyprintf((stderr, "  ok   yymatchChar(%c) @ %s\n", c, yybuf+yypos));
      return 1;
    }
  yyprintf((stderr, "  fail yymatchChar(%c) @ %s\n", c, yybuf+yypos));
  return 0;
}

YY_LOCAL(int) yymatchString(char *s)
{
  int yysav= yypos;
  while (*s)
    {
      if (yypos >= yylimit && !yyrefill()) return 0;
      if (yybuf[yypos] != *s)
        {
          yypos= yysav;
          return 0;
        }
      ++s;
      ++yypos;
    }
  return 1;
}

YY_LOCAL(int) yymatchClass(unsigned char *bits)
{
  int c;
  if (yypos >= yylimit && !yyrefill()) return 0;
  c= yybuf[yypos];
  if (bits[c >> 3] & (1 << (c & 7)))
    {
      ++yypos;
      yyprintf((stderr, "  ok   yymatchClass @ %s\n", yybuf+yypos));
      return 1;
    }
  yyprintf((stderr, "  fail yymatchClass @ %s\n", yybuf+yypos));
  return 0;
}

YY_LOCAL(void) yyDo(yyaction action, int begin, int end)
{
  while (yythunkpos >= yythunkslen)
    {
      yythunkslen *= 2;
      yythunks= (yythunk*)realloc(yythunks, sizeof(yythunk) * yythunkslen);
    }
  yythunks[yythunkpos].begin=  begin;
  yythunks[yythunkpos].end=    end;
  yythunks[yythunkpos].action= action;
  ++yythunkpos;
}

YY_LOCAL(int) yyText(int begin, int end)
{
  int yyleng= end - begin;
  if (yyleng <= 0)
    yyleng= 0;
  else
    {
      while (yytextlen < (yyleng - 1))
	{
	  yytextlen *= 2;
	  yytext= (char*)realloc(yytext, yytextlen);
	}
      memcpy(yytext, yybuf + begin, yyleng);
    }
  yytext[yyleng]= '\0';
  return yyleng;
}

YY_LOCAL(void) yyDone(void)
{
  int pos;
  for (pos= 0;  pos < yythunkpos;  ++pos)
    {
      yythunk *thunk= &yythunks[pos];
      int yyleng= thunk->end ? yyText(thunk->begin, thunk->end) : thunk->begin;
      yyprintf((stderr, "DO [%d] %p %s\n", pos, thunk->action, yytext));
      thunk->action(yytext, yyleng);
    }
  yythunkpos= 0;
}

YY_LOCAL(void) yyCommit()
{
  if ((yylimit -= yypos))
    {
      memmove(yybuf, yybuf + yypos, yylimit);
    }
  yybegin -= yypos;
  yyend -= yypos;
  yypos= yythunkpos= 0;
}

YY_LOCAL(int) yyAccept(int tp0)
{
  if (tp0)
    {
      fprintf(stderr, "accept denied at %d\n", tp0);
      return 0;
    }
  else
    {
      yyDone();
      yyCommit();
    }
  return 1;
}

YY_LOCAL(void) yyPush(char *text, int count)	{ yyval += count; }
YY_LOCAL(void) yyPop(char *text, int count)	{ yyval -= count; }
YY_LOCAL(void) yySet(char *text, int count)	{ yyval[count]= yy; }

#endif /* YY_PART */

#define	YYACCEPT	yyAccept(yythunkpos0)

YY_RULE(int) yy_Number(); /* 5 */
YY_RULE(int) yy__(); /* 4 */
YY_RULE(int) yy_Value(); /* 3 */
YY_RULE(int) yy_Product(); /* 2 */
YY_RULE(int) yy_Expr(); /* 1 */

YY_ACTION(void) yy_1_Number(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_Number\n"));
   yy = new Number(atof(yytext)); ;
}
YY_ACTION(void) yy_3_Product(char *yytext, int yyleng)
{
#define rhs yyval[-1]
#define lhs yyval[-2]
  yyprintf((stderr, "do yy_3_Product\n"));
   yy =lhs ;
#undef rhs
#undef lhs
}
YY_ACTION(void) yy_2_Product(char *yytext, int yyleng)
{
#define rhs yyval[-1]
#define lhs yyval[-2]
  yyprintf((stderr, "do yy_2_Product\n"));
   lhs = new Divide(lhs, rhs); ;
#undef rhs
#undef lhs
}
YY_ACTION(void) yy_1_Product(char *yytext, int yyleng)
{
#define rhs yyval[-1]
#define lhs yyval[-2]
  yyprintf((stderr, "do yy_1_Product\n"));
   lhs = new Multiply(lhs, rhs); ;
#undef rhs
#undef lhs
}
YY_ACTION(void) yy_3_Expr(char *yytext, int yyleng)
{
#define rhs yyval[-1]
#define lhs yyval[-2]
  yyprintf((stderr, "do yy_3_Expr\n"));
   yy = lhs ;
#undef rhs
#undef lhs
}
YY_ACTION(void) yy_2_Expr(char *yytext, int yyleng)
{
#define rhs yyval[-1]
#define lhs yyval[-2]
  yyprintf((stderr, "do yy_2_Expr\n"));
   lhs = new Subtract(lhs, rhs); ;
#undef rhs
#undef lhs
}
YY_ACTION(void) yy_1_Expr(char *yytext, int yyleng)
{
#define rhs yyval[-1]
#define lhs yyval[-2]
  yyprintf((stderr, "do yy_1_Expr\n"));
   lhs = new Add(lhs, rhs); ;
#undef rhs
#undef lhs
}

YY_RULE(int) yy_Number()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "Number"));  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l1;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\377\003\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l1;
  l2:;	
  {  int yypos3= yypos, yythunkpos3= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\377\003\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l3;  goto l2;
  l3:;	  yypos= yypos3; yythunkpos= yythunkpos3;
  }
  {  int yypos4= yypos, yythunkpos4= yythunkpos;  if (!yymatchChar('.')) goto l4;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\377\003\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l4;
  l6:;	
  {  int yypos7= yypos, yythunkpos7= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\377\003\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l7;  goto l6;
  l7:;	  yypos= yypos7; yythunkpos= yythunkpos7;
  }  goto l5;
  l4:;	  yypos= yypos4; yythunkpos= yythunkpos4;
  }
  l5:;	  yyText(yybegin, yyend);  if (!(YY_END)) goto l1;  yyDo(yy_1_Number, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "Number", yybuf+yypos));
  return 1;
  l1:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "Number", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy__()
{
  yyprintf((stderr, "%s\n", "_"));
  l9:;	
  {  int yypos10= yypos, yythunkpos10= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\002\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l10;  goto l9;
  l10:;	  yypos= yypos10; yythunkpos= yythunkpos10;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "_", yybuf+yypos));
  return 1;
}
YY_RULE(int) yy_Value()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "Value"));  if (!yy_Number()) goto l11;  if (!yy__()) goto l11;
  yyprintf((stderr, "  ok   %s @ %s\n", "Value", yybuf+yypos));
  return 1;
  l11:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "Value", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_Product()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 2, 0);
  yyprintf((stderr, "%s\n", "Product"));  if (!yy_Value()) goto l12;  yyDo(yySet, -2, 0);
  l13:;	
  {  int yypos14= yypos, yythunkpos14= yythunkpos;
  {  int yypos15= yypos, yythunkpos15= yythunkpos;  if (!yymatchChar('*')) goto l16;  if (!yy_Value()) goto l16;  yyDo(yySet, -1, 0);  yyDo(yy_1_Product, yybegin, yyend);  goto l15;
  l16:;	  yypos= yypos15; yythunkpos= yythunkpos15;  if (!yymatchChar('/')) goto l14;  if (!yy_Value()) goto l14;  yyDo(yySet, -1, 0);  yyDo(yy_2_Product, yybegin, yyend);
  }
  l15:;	  goto l13;
  l14:;	  yypos= yypos14; yythunkpos= yythunkpos14;
  }  if (!yy__()) goto l12;  yyDo(yy_3_Product, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "Product", yybuf+yypos));  yyDo(yyPop, 2, 0);
  return 1;
  l12:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "Product", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_Expr()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 2, 0);
  yyprintf((stderr, "%s\n", "Expr"));  if (!yy_Product()) goto l17;  yyDo(yySet, -2, 0);
  l18:;	
  {  int yypos19= yypos, yythunkpos19= yythunkpos;
  {  int yypos20= yypos, yythunkpos20= yythunkpos;  if (!yymatchChar('+')) goto l21;  if (!yy_Product()) goto l21;  yyDo(yySet, -1, 0);  yyDo(yy_1_Expr, yybegin, yyend);  goto l20;
  l21:;	  yypos= yypos20; yythunkpos= yythunkpos20;  if (!yymatchChar('-')) goto l19;  if (!yy_Product()) goto l19;  yyDo(yySet, -1, 0);  yyDo(yy_2_Expr, yybegin, yyend);
  }
  l20:;	  goto l18;
  l19:;	  yypos= yypos19; yythunkpos= yythunkpos19;
  }  yyDo(yy_3_Expr, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "Expr", yybuf+yypos));  yyDo(yyPop, 2, 0);
  return 1;
  l17:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "Expr", yybuf+yypos));
  return 0;
}

#ifndef YY_PART

typedef int (*yyrule)();

YY_PARSE(int) YYPARSEFROM(yyrule yystart)
{
  int yyok;
  if (!yybuflen)
    {
      yybuflen= 1024;
      yybuf= (char*)malloc(yybuflen);
      yytextlen= 1024;
      yytext= (char*)malloc(yytextlen);
      yythunkslen= 32;
      yythunks= (yythunk*)malloc(sizeof(yythunk) * yythunkslen);
      yyvalslen= 32;
      yyvals= (YYSTYPE*)malloc(sizeof(YYSTYPE) * yyvalslen);
      yybegin= yyend= yypos= yylimit= yythunkpos= 0;
    }
  yybegin= yyend= yypos;
  yythunkpos= 0;
  yyval= yyvals;
  yyok= yystart();
  if (yyok) yyDone();
  yyCommit();
  return yyok;
  (void)yyrefill;
  (void)yymatchDot;
  (void)yymatchChar;
  (void)yymatchString;
  (void)yymatchClass;
  (void)yyDo;
  (void)yyText;
  (void)yyDone;
  (void)yyCommit;
  (void)yyAccept;
  (void)yyPush;
  (void)yyPop;
  (void)yySet;
  (void)yytextmax;
}

YY_PARSE(int) YYPARSE(void)
{
  return YYPARSEFROM(yy_Expr);
}

#endif

YYSTYPE parse() {
  int r = yyparse();
  yybuflen = 0;
  return r ? yy : 0;
}


