/* Don't remove this comment */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mark.h"
#include "mode.h"
#include "stringutil.h"

int expect_nl = 0;

#define COMMAND(x) {x} expect_nl = 1;
#define CTEXT(x) (yytext+sizeof("."x))
#define DIV(x)      do{ mode_change(mode_div); printf("<div class=\""x"\">\n"); }while(0)
#define NSPAN(x,f)  do{ printf("<span class=\""x"\">"f"</span>"); }while(0) 
#define NBLOCK(x) do{ mode_change(mode_normal); printf("<div class=\""x"\">%s</div>\n",yytext+sizeof("."x)); }while(0)
#define NDIV(x)   do{ mode_change(mode_div); printf("<div class=\""x"\">\n<span class=\""x"\">%s</span></br>",yytext+sizeof("."x)); }while(0)
%}

%option noyywrap

%%
^\.\..*           { COMMAND() }
^\.section\ .*    { COMMAND(NBLOCK("section");) }
^\.header\ .*     { COMMAND(NBLOCK("header");) }
^\.text/\n        { COMMAND(DIV("text");) }
^\.info\ .*       { COMMAND(NDIV("info");) }
^\.edit\ .*       { COMMAND(NDIV("edit");) }

^\\\ .*           { COMMAND(printf("%s",CTEXT(""));) }
^\./\n            { COMMAND(DIV("</br>");) }

^\.image\ .*      { COMMAND(DIV("image"); printf("<img src=\"%s\"></br>",CTEXT("code"));) }
^\.code\ .*       { COMMAND(mode_change(mode_code); printf("<div class=\"code\"><div class=\"code-%s\"><div class=\"codeinner\"><pre>",CTEXT("code"));) }
^\.code/\n        { COMMAND(mode_change(mode_code); printf("<div class=\"code\"><div><div class=\"codeinner\"><pre>");) }


\n                { if(!expect_nl) printf("</br>"); }
.*                { mark_string(yytext); }

%%
/*
^\.section\ .* { mode_change(NORMAL); printf("</br><div class=\"section\">%s</div>\n",yytext+sizeof(".section")); text_mode(); }
^\.header\ .*  { mode_change(NORMAL); printf("</br><div class=\"header\">%s</div>\n", yytext+sizeof(".header")); text_mode(); }
^\.info\ .*\n     { mode_change(INFO);   printf("<div class=\"info\"><b>%s</b></br>",yytext+sizeof(".info")); }
^\.code\n         { mode_change(CODE);   printf("<div class=\"code\"><div><div class=\"codeinner\"><pre><code>"); }
^\.code\ .*\n     { mode_change(CODE);   printf("<div class=\"code\"><div class=\"code-%s\"><div class=\"codeinner\"><pre>",yytext+sizeof(".code")); }
^\.image\ .*   { mode_change(NORMAL); printf("<div class=\"image\"><img src=\"%s\"/></div></br>\n", yytext+sizeof(".image")); text_mode(); }
^\.progfile\ .*\n { execrun(); strcpy(execname, yytext+sizeof(".progfile")); printf("<div class=\"source\"><b>File: </b>%s<div class=\"sourceinner\">",yytext + sizeof(".progfile")); exec = 2; }
^\.program\ .*\n  { execrun(); strcpy(execname, yytext+sizeof(".program")); printf("<div class=\"source\"><b>Program: </b>%s<div class=\"sourceinner\">",yytext + sizeof(".program")); exec = 1; }
^\.>\ .*\n        { printf("%s",yytext); }
^\.[0-9]\ .*\n    { mode_change(NORMAL); printf("<div class=\"text\"><span class=\"numberlist\">%c.</span> %s</div>\n", yytext[1],yytext+sizeof(".0")); text_mode(); }
^\.\.(.*)\n       { }
^\.\n             { text_mode(); }
\n\n              { if(mode != CODE) printf("</br>"); printf("\n\n"); if(exec) execptr = scopy(execptr, "\n\n"); }
\n                { printf("\n"); if(exec) execptr = scopy(execptr, "\n"); }
.+/\n             { printf("%s ",yytext); if(exec) execptr = scopy(execptr, yytext); }
*/
int main(void)
{
  printf("<!DOCTYPE html><html><head><link rel=\"stylesheet\" href=\"style.css\">");
  yylex();
  printf("</html></head>");
  return 0;
}
