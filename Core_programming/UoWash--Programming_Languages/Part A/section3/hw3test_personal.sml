(* Homework3 Simple Test*)
(* These are basic test cases. Passing these tests does not guarantee that your code will pass the actual homework grader *)
(* To run the test, add a new line to the top of this file: use "homeworkname.sml"; *)
(* All the tests should evaluate to true. For example, the REPL should say: val test1 = true : bool *)
use "hw3provided.sml";

val test1 = only_capitals ["Aa","aB","Ca"] 

val test2 = longest_string1 ["A","bc","it","C"]

val test3 = longest_string2 ["A","bc","it","C"]

val test4a = longest_string3 ["A","bc","it","C"]

val test4b = longest_string4 ["A","bc","it","C"]

val test5 = longest_capitalized ["Ard","bcdfs","Cad"] 

val test6 = rev_string "abc" 

val test7 = first_answer (fn x => if x > 3 then SOME x else NONE) [1,2,3,4,5] 

val test8  = all_answers (fn x => if x = 1 then SOME [x] else NONE) [2,3,4,5,6,7] 
val test8a = all_answers (fn x => if x = 1 then SOME [x] else NONE) [1,1,1,1,1,1] 
val test8b = all_answers (fn x => if x = 1 then SOME [x] else NONE) [1,1,1,2,1,1] 

val test9a = count_wildcards Wildcard 

val test9b = count_wild_and_variable_lengths (Variable("a")) 

val test9c = count_some_var ("x", TupleP([Variable("x"), Variable("x"), Variable("y"), ConstP 5, Wildcard])) 

val test10 = check_pat (TupleP([Variable("x"), Variable("x"), Variable("y"), ConstP 5, Wildcard])) 
val test10a = check_pat (TupleP([Variable("z"), Variable("x"), Variable("y"), ConstP 5, Wildcard])) 
val test10b = check_pat(TupleP[TupleP[TupleP[Variable "x",ConstructorP ("wild",Wildcard)],Wildcard],Variable "x"]) (*should be false*)
val test10c = check_pat(ConstructorP ("hi",TupleP[Variable "x",Variable "x"])) 
val test10d = check_pat(ConstructorP ("hi",TupleP[Variable "x",ConstructorP ("yo",TupleP[Variable "x",UnitP])]))

val test11 = match (Const(1), UnitP) 

val test12 = first_match Unit [UnitP] 
(*
check_pat: Called check_pat on input: ConstructorP ("hi",TupleP[Variable "x",Variable "x"]), should have gotten: false but your function returned otherwise. [incorrect answer]
check_pat: Called check_pat on input: ConstructorP ("hi",TupleP[Variable "x",ConstructorP ("yo",TupleP[Variable "x",UnitP])])
*)
