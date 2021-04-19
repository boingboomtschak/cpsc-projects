%namespace Project1
%scannertype Scanner
%visibility internal
%tokentype Token
%using Project1;

%option stack, minimize, parser, verbose, persistbuffer, noembedbuffers, noparser

LineTerminator	(\r\n?|\n)
WhiteSpace	({LineTerminator}|[ \t\f])

/* The following constants should be used to tell the parser what tokens have been recogized by the scanner.
   The rule associated with each token should simply be  { return(token-number) }
   where token-number is provided by using one of the constants.
 */
%{
	public const int EOF = 0, FLTDCL = 1, INTDCL = 2, PRINT = 3, ASSIGN = 4, PLUS = 5, MINUS = 6, ID = 7, INUM = 8, FNUM = 9;
%}

%%
 
/*****  Add your rules for recognizing ac tokens here.  I have given you one for skipping whitespace.  */

f                                { return(FLTDCL); } // floatdcl
i                                { return(INTDCL); } // intdcl
p                                { return(PRINT); }  // print
[a-eg-hj-oq-z]                   { return(ID); }     // id
\=                               { return(ASSIGN); } // assign
\+                               { return(PLUS); }   // plus
\-                               { return(MINUS); }  // minus
[0-9]+.[0-9]+                    { return(FNUM); }   // fnum
[0-9]+                           { return(INUM); }   // inum
Whitespace+		                 { }                 // whitespace
<<EOF>>                          { return(EOF); }    // EOF 


%%