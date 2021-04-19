namespace Project1
{
    // $Id: Token.cs  2017-03-24 leblanc $
    // Translated from Token.java 2010-01-07 17:14:40Z cytron $
    public class PToken
	{

		//
    	//   Constants to represent tokens and corresponding strings in array token2str
		//
		public const int EOF = 0, FLTDCL = 1, INTDCL = 2, PRINT = 3, ASSIGN = 4, PLUS = 5, MINUS = 6, ID = 7, INUM = 8, FNUM = 9;

		public static readonly string[] token2str = new string[] {"$", "fltdcl", "intdcl", "print", "assign", "plus", "minus", "id", "inum", "fnum"};

        // instance variables used to define a token
		public readonly int type;
		public readonly string val;   // val is unused except for ids, integers and floats

		public PToken(int type) : this(type, "")
		{
		}

		public PToken(int type, string val)
		{
			this.type = type;
			this.val = val;
		}

		public override string ToString()
		{
			return "Token type\t" + token2str[type] + "\tval\t" + val;
		}
	}

}