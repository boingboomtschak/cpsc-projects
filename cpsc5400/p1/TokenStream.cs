using System;
using System.IO;

namespace Project1
{
    // $Id: TokenStream.cs  2017-03-24 leblanc $
    // Translated from TokenStream.java 22 2010-01-07 16:50:05Z cytron $

    public class TokenStream
	{

		private PToken nextToken = new PToken(0);
        private Scanner scanner;
        private const Boolean tokenTrace = false;

		public TokenStream(string f)
		{
            scanner = new Project1.Scanner(File.OpenRead(f));
            advance();
		}

		public virtual int peek()
		{
			return nextToken.type;
		}

		public virtual PToken advance()
		{
			PToken ans = nextToken;
            if (tokenTrace) Console.WriteLine(ans.ToString());

            // Call yylex to get the next token for use by peek()
            var type = scanner.yylex();
            if (type == 7 || type == 8 || type == 9)  // These are token classes (identifiers and numbers), 
                                                      // text of token is needed for semantics
            {
                nextToken = new PToken(type, scanner.yytext);  
            }
            else
            {
                nextToken = new PToken(type);
            }
            return ans;
		}



	}

}