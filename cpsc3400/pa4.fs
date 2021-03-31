/// F# Programming Assignment 2 (pa4.fs)
/// Author : Devon McKee
/// 
/// TEXT FROM SYLLABUS BELOW:
/// All of the code you turn in must have been written by you without immediate reference to another solution to the problem you are solving.  That means that you can look at other programs to see how someone solved a similar problem, but you shouldn't have any code written by someone else visible when you write yours (and you shouldn't have looked at a solution just a few seconds before you type!).  You should compose the code you write based on your understanding of how the features of the language you are using can be used to implement the algorithm you have chosen to solve the problem you are addressing.  Doing it this way is "real programming" - in contrast to just trying to get something to work by cutting and pasting stuff you don't actually understand.  It is the only way to achieve the learning objectives of the course.
/// 
/// Format of vars: [("a",5);("b",2);("c",9)]
let eval (vars : (string * int) list) (expr : string) : int =
    let mainOps = Set.empty.Add("+").Add("-").Add("*").Add("/")
    /// findVal ch vars : takes a string and list, checks the variables list (in format
    /// (string * int) list) and returns the value associated with it in the vars list 
    let rec findVal (ch : char) (vars : (string * int) list) : int=
        match vars with
        | [] -> failwith "No value for given variable" 
        | (var, value)::tail when (System.Convert.ToString ch) = var -> value
        | (var, value)::tail -> findVal ch tail
    /// setVal ch newVal vars : takes a string, int, and list (in vars list format),
    /// recursively checks if string already has value association and returns new
    /// list with modified value if so, otherwise appends new value association to list
    /// and returns new list
    let rec setVal ch newVal (vars : (string * int) list) =
        match vars with
        | [] when ch = "" -> vars
        | [] -> (ch, newVal)::vars
        | (var, value)::tail when ch = var -> (var, newVal)::(setVal "" newVal tail)
        | (var, value)::tail -> (var, value)::(setVal ch newVal tail)
    /// pop stack : takes a list (serving as a de facto stack), returns the top element
    /// and the new list in a tuple as (int * (int list))
    let pop stack =
        match stack with
        | value::rest -> (value, rest) 
        | [] -> failwith "Stack underflow"
    /// innerEval vars stack expr : recursively uses pattern matching to identify next
    /// char to evaluate in expression string, performs necessary actions, returns int
    /// result of expression
    let rec innerEval (vars : (string * int) list) (stack : int list) (expr : string) : int =
        match (Seq.toList expr) with
        | [] -> stack.[0]
        | head::tail when (System.Char.IsLetter(head)) -> 
            innerEval vars ((findVal head vars)::stack) (System.String.Concat tail) // adds head value to stack, continues evaluating expr
        | head::tail when (mainOps.Contains (System.Convert.ToString head)) -> 
            let (firstOperand, midStack) = (pop stack)
            let (secondOperand, newStack) = (pop midStack)
            match head with
            | '+' -> innerEval vars ((secondOperand + firstOperand)::newStack) (System.String.Concat tail)
            | '-' -> innerEval vars ((secondOperand - firstOperand)::newStack) (System.String.Concat tail)
            | '*' -> innerEval vars ((secondOperand * firstOperand)::newStack) (System.String.Concat tail)
            | '/' -> innerEval vars ((secondOperand / firstOperand)::newStack) (System.String.Concat tail)
            | _ -> failwith "Unidentified operator"
        | head::tail when (head = '$') -> 
            let (firstOperand, midStack) = pop stack
            let (secondOperand, newStack) = pop midStack
            innerEval vars (secondOperand::firstOperand::newStack) (System.String.Concat tail)
        | head::tail when (head = '@') -> 
            match tail with
            | ch::newExpr -> 
                let (popped, newStack) = pop stack
                let newVars = setVal (System.Convert.ToString ch) popped vars
                innerEval newVars newStack (System.String.Concat newExpr)
            | _ -> failwith "Invalid use of @ operator"
        | head::tail -> 
            innerEval vars stack (System.String.Concat tail) /// skips any other characters
    innerEval vars [] expr


/// TEST CODE STARTS
let testvars = [("a",5);("b",2);("c",9)]
let expr1 = "ab+"
let expr2 = "cab+-"
let expr3 = "cab+$-"
let expr4 = "ab+cb-*"
let expr5 = "ab+cb-* @d bd+"
let res1 = eval testvars expr1
let res2 = eval testvars expr2
let res3 = eval testvars expr3
let res4 = eval testvars expr4
let res5 = eval testvars expr5

let testEval = eval [("a",5);("b",2);("c",9)] 
let exprList = ["ab-ab*ab+--"; "bbb @q bqbq*****"; "ca- @b bc$-"]
let resultList = List.map testEval exprList

/// TEST CODE ENDS
/// the (regrettable) above code for setVal does something a little hacky to handle both modifying var
/// and adding a new var: it sets the "ch" parameter to an empty string on next recursive call, which
/// tells the next iterations that it has already completed modifying the list. i will consider
/// this code a blight upon my otherwise relatively idiomatic and clean code.