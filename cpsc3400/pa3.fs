/// F# Programming Assignment 1 (pa3.fs)
/// Author: Devon McKee
/// 
/// TEXT FROM SYLLABUS BELOW:
/// All of the code you turn in must have been written by you without immediate reference to another solution to the problem you are solving.  That means that you can look at other programs to see how someone solved a similar problem, but you shouldn't have any code written by someone else visible when you write yours (and you shouldn't have looked at a solution just a few seconds before you type!).  You should compose the code you write based on your understanding of how the features of the language you are using can be used to implement the algorithm you have chosen to solve the problem you are addressing.  Doing it this way is "real programming" - in contrast to just trying to get something to work by cutting and pasting stuff you don't actually understand.  It is the only way to achieve the learning objectives of the course.
/// --- PROJECT PART 1 --- 
/// - maxCubeVolume function (parameter: list of tuples with cube dimensions) -
/// 
/// purpose: find cube with max volume from list of cube dimensions
/// 
/// mechanism: finds volumes for each cube, adds to list, finds max of list 
///            with recursive function
/// 
/// variables: t = tuple, l = list, e = element, m = max, x/y/z = temp,
///            h = head, t = tail
let maxCubeVolume l : float =
    let volume t = 
        let (x, y, z) = t
        (x * y * z)
    let volumes = [for e in l do yield (volume e)]
    let max l = 
        let rec maxRecur (x, m) =
            match x with
            | [] -> m
            | (h :: t) -> maxRecur (t, if (h > m) then h else m)
        maxRecur(l, 0.0)
    max volumes

/// --- PROJECT PART 2 ---
// findMatches using single list comprehension statement
let findMatchesLC s (l : (string * int) list) = 
    List.sort [for (ts, n) in l do if s = ts then yield n]

/// - findMatches function (parameters: string, list) -
/// 
/// purpose: finds strings in list of tuples of type string * int that match
///          the given string, and returns their ints
/// 
/// mechanism: calls a recursive loop to iterate over the list, passing the cumulative
///            list of all ints to return until end, then returns list of ints (sorted)
/// 
/// variables: s = string, l = list, r = return list, m = match string, i = int, 
let findMatches s (l : (string * int) list) = 
    let rec loop l r =
        match l with
        | [] -> r
        | head :: tail ->
            let (m, i) = head
            if (s = m) then loop tail (i::r) else loop tail r
    let result = loop l []
    List.sort result

/// --- PROJECT PART 3 ---
type BST = 
    | Empty
    | TreeNode of int * BST * BST


/// - insert function (parameters: value, tree) -
/// 
/// purpose: inserts value in binary search tree
/// 
/// mechanism: uses pattern matching to recursively reconstruct tree
///            starting from lowest level in which value is added
/// 
/// variables: i = val of current tree node, l = left of node, r = right of node 
let rec insert value (tree : BST) = 
    match tree with
    | Empty -> TreeNode(value, Empty, Empty)
    | TreeNode(i, l, r) -> 
        if (value <= i) then TreeNode(i, (insert value l), r)
        else TreeNode(i, l, (insert value r))


/// - contains function (parameters: value, tree) -
/// 
/// purpose: searches tree for given value, returns bool telling if
///          given value exists in tree
/// 
/// mechanism: recursively iterates through tree, traversing according to BST rules
///            (left = values lower than current node, right = vice versa)
/// 
/// variables: i = int of current node, l = left tree, r = right tree
let rec contains value (tree : BST) = 
    match tree with
    | Empty -> false
    | TreeNode(i, l, r) ->
        if (value < i) then contains value l
        elif (value > i) then contains value r
        else true


/// - count function (parameters: function (int -> bool), tree) - 
/// 
/// purpose: counts number of nodes in tree that satisfy given function
/// 
/// mechanism: recursively traverses all tree nodes, returning int depending on
///            satisfaction of given function
/// 
/// variables: i = int of current node, l = left tree, r = right tree
let rec count func (tree : BST) = 
    match tree with
    | Empty -> 0
    | TreeNode(i, l, r) ->
        if (func i) then (1 + (count func l) + (count func r))
        else (0 + (count func l) + (count func r))


/// - evenCount function (parameter: tree) - 
/// 
/// purpose: lists number of nodes in tree that contain even number
/// 
/// mechanism: calls count function with lambda function to return true if
///            int is even
/// 
/// variables: x = temp
let evenCount tree = 
    count (fun x -> x % 2 == 0) tree
