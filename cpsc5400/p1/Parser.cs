using System;
using System.Collections;
using System.Collections.Generic;
using Project1;

namespace Project1 {
    using static Project1.PToken;  // defined in Token.cs

    /// <summary>
    /// Recursive-descent parser based on the grammar given
    ///   in Figure 2.1
    /// 
    /// </summary>
    /// 
    public struct Symbol {
        public int type;
        public dynamic value;
    }

    public class Parser {

        private TokenStream ts;
        private const Boolean parseTrace = false;
        private const Boolean symbolTrace = false;
        private PToken lastToken;
        private Dictionary<string, Symbol> symbolTable;
        private Symbol lastSymbol;

        public Parser(string f) {
            ts = new TokenStream(f);
            symbolTable = new Dictionary<string, Symbol>();
        }


        public virtual void Prog() {
            if (ts.peek() == FLTDCL || ts.peek() == INTDCL || ts.peek() == ID || ts.peek() == PRINT || ts.peek() == EOF) {
                Things();
                expect(EOF);
                if (symbolTrace) printSymbols(); 
            } else {
                error("expected floatdcl, intdcl, id, print, or eof");
            }
            if (parseTrace) Console.WriteLine("Recognized Prog");
        }

        public virtual void Things()
        /***** This is not a complete procedure for matching Things -- it only handles the production with an empty RHS.
         * Add the logic needed to match any other productions for Things.
         */

        {
            if (ts.peek() == EOF) {
                // Do nothing for lambda-production
            } else if (ts.peek() == FLTDCL || ts.peek() == INTDCL) {
                Dcl();
                Things();
            } else if (ts.peek() == ID || ts.peek() == PRINT) {
                Stmt();
                Things();
            } else {
                error("expected floatdcl, intdcl, id, print, or eof");
            }
        }

        /***** functions to match all of the other rules of the grammar go here */
        public virtual void Dcl() {
            if (ts.peek() == FLTDCL) {
                expect(FLTDCL);
                expect(ID);
                if (symbolTable.ContainsKey(lastToken.val)) {
                    error(String.Format("variable {0} is already declared", lastToken.val));
                }
                Symbol sym;
                sym.type = FNUM;
                sym.value = null;
                symbolTable.Add(lastToken.val, sym);
            } else if (ts.peek() == INTDCL) {
                expect(INTDCL);
                expect(ID);
                if (symbolTable.ContainsKey(lastToken.val)) {
                    error(String.Format("variable {0} is already declared", lastToken.val));
                }
                Symbol sym;
                sym.type = INUM;
                sym.value = null;
                symbolTable.Add(lastToken.val, sym);
            } else {
                error("expected float or int declaration");
            }
        }

        public virtual void Stmt() {
            if (ts.peek() == ID) {
                expect(ID);
                string lval = lastToken.val;
                expect(ASSIGN);
                Val();
                Expr();
                if (symbolTable.ContainsKey(lval)) {
                    Symbol sym = symbolTable[lval];
                    if (sym.type == FNUM) {
                        if (lastSymbol.type == FNUM) {
                            symbolTable[lval] = lastSymbol;
                        } else if (lastSymbol.type == INUM) {
                            lastSymbol.type = FNUM;
                            lastSymbol.value = (float)lastSymbol.value;
                            symbolTable[lval] = lastSymbol;
                        }
                    } else if (sym.type == INUM) {
                        if (lastSymbol.type == FNUM) {
                            error("invalid assignment of float to integer variable");
                        } else if (lastSymbol.type == INUM) {
                            symbolTable[lval] = lastSymbol;
                        }
                    }
                } else {
                    error(String.Format("variable {0} is not declared", lval));
                }
            } else if (ts.peek() == PRINT) {
                expect(PRINT);
                expect(ID);
                if (symbolTable.ContainsKey(lastToken.val)) {
                    Console.WriteLine(symbolTable[lastToken.val].value);
                } else {
                    error(String.Format("variable {0} is not declared", lastToken.val));
                }
            } else {
                error("expected id or print");
            }

        }
        public virtual void Expr() {
            if (ts.peek() == PLUS) {
                Symbol sym = lastSymbol;
                expect(PLUS);
                Val();
                if (sym.type == FNUM) {
                    if (lastSymbol.type == FNUM) {
                        sym.value += lastSymbol.value;
                    } else if (lastSymbol.type == INUM) {
                        sym.value += (float)lastSymbol.value;
                    }
                } else if (sym.type == INUM) {
                    if (lastSymbol.type == FNUM) {
                        sym.type = FNUM;
                        sym.value = (float)sym.value + lastSymbol.value;
                    } else if (lastSymbol.type == INUM) {
                        sym.value += lastSymbol.value;
                    }
                }
                lastSymbol = sym;
                Expr();
            } else if (ts.peek() == MINUS) {
                Symbol sym = lastSymbol;
                expect(MINUS);
                Val();
                if (sym.type == FNUM) {
                    if (lastSymbol.type == FNUM) {
                        sym.value -= lastSymbol.value;
                    } else if (lastSymbol.type == INUM) {
                        sym.value -= (float)lastSymbol.value;
                    }
                } else if (sym.type == INUM) {
                    if (lastSymbol.type == FNUM) {
                        sym.type = FNUM;
                        sym.value = (float)sym.value - lastSymbol.value;
                    } else if (lastSymbol.type == INUM) {
                        sym.value -= lastSymbol.value;
                    }
                }
                lastSymbol = sym;
                Expr();
            } else if (ts.peek() == ID || ts.peek() == PRINT || ts.peek() == EOF) {
                // Do nothing for lambda-production
            } else {
                error("expected plus, minus, id, print, or eof");
            }

        }

        public virtual void Val() {
            if (ts.peek() == ID) {
                expect(ID);
                if (symbolTable.ContainsKey(lastToken.val)) {
                    lastSymbol = symbolTable[lastToken.val];
                } else {
                    error(String.Format("variable {0} is not declared", lastToken.val));
                }
            } else if (ts.peek() == INUM) {
                expect(INUM);
                lastSymbol.type = INUM;
                lastSymbol.value = Int32.Parse(lastToken.val);
            } else if (ts.peek() == FNUM) {
                expect(FNUM);
                lastSymbol.type = FNUM;
                lastSymbol.value = float.Parse(lastToken.val);
            } else {
                error("expected id, inum, or fnum");
            }

        }

        private void expect(int type) {
            lastToken = ts.advance();
            if (lastToken.type != type) {
                throw new Exception("Expected type " + token2str[type] + " but received type " + token2str[lastToken.type]);

            }
        }

        private void error(string message) {
            if (symbolTrace) printSymbols();
            throw new Exception(message);
        }

        private void printSymbols() { 
            foreach (var entry in symbolTable) {
                Console.WriteLine("Symbol: {0}, Type: {1}, Value: {2}", entry.Key, token2str[entry.Value.type], entry.Value.value);
            }
        }
    }

}