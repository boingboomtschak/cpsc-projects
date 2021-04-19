# Project-1

The files in this project repository are a starting point for you to use in completing this project.  
Completing the parser and scanner integration part of the project will only involve changes to two 
of the files: Parser.cs and Project1.Language.analyzer.lex
The code necessary to implement the interpretation part of the project will be inserted in the 
parsing functions that you add to Parser.cs

When you run the project, it will read and process a single ac program found in acTestFile.txt
The scanner generated from the lex file as currently specified only recognizes whitespace.  
It simply skips everything else and thus the only token that is ever given to the parser is the 
end-of-file token, since that one is generated in the token handling layer between the generated scanner
and the parser.  You will be adding rules to the lex file to recognize ac tokens.

There is a stub of a recursive descent parser in the Parser.cs file.  It includes a function to recognize
Prog and a version of a Things function that only handles the production with the empty right hand side.
This production is triggered by EOF, so the parser in its current state makes a single call to Things,
which succeeds because the only token it gets is EOF ($).  You job is to copy the parsing procedures from
Studio 2 into this file, doing the generalization of the grammar to all declarations and statements to be
interleaved rather than forcing all of the declarations to appear first.  As we discussed in class, 
the Things is the beginning of that generalization.  The Prog function has a statement at the end to print
out a trace line when it is executed.  Add similar lines at least to your functions for 
Dcl and Stmt (and maybe to all of your other parse functions) so that you can tell what is happening.  
The program produces no output except traces from the scanner and parser -- unless something goes wrong,
in which case it will throw an exception and you will see a traceback.
\
The places where you need to add rules or code are marked with comments that begin /*****
You don't have to even look at the rest of the files, but I do encourage you to understand the whole 
structure and control flow.
