using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Project1;

namespace Project1
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 1) 
            {
                Console.WriteLine("Supply one input file as an argument");
                return;
            }
            if (!File.Exists(args[0]))
            {
                Console.WriteLine("File not found");
                return;
            }

            Parser p = new Parser(args[0]);
            p.Prog();
            
            Console.Read(); //  keep the console window open
        }
    }
}
