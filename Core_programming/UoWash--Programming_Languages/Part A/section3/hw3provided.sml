(* Coursera Programming Languages, Homework 3, Provided Code *)

exception NoAnswer

datatype pattern = Wildcard
		 | Variable of string
		 | UnitP
		 | ConstP of int
		 | TupleP of pattern list
		 | ConstructorP of string * pattern

datatype valu = Const of int
	      | Unit
	      | Tuple of valu list
	      | Constructor of string * valu

fun g f1 f2 p =
    let 
	val r = g f1 f2 
    in
	case p of
	    Wildcard          => f1 ()
	  | Variable x        => f2 x
	  | TupleP ps         => List.foldl (fn (p,i) => (r p) + i) 0 ps
	  | ConstructorP(_,p) => r p
	  | _                 => 0
    end

(**** for the challenge problem only ****)

datatype typ = Anything
	     | UnitT
	     | IntT
	     | TupleT of typ list
	     | Datatype of string

(**** you can put all your code here ****)
(* Problem 1 *)
fun only_capitals strings = 
  List.filter (fn s => Char.isUpper(String.sub(s,0)))  strings

(* Problem 2 *)
fun longest_string1 strings = 
  List.foldl (fn (a, b) => if String.size(a) > String.size(b) then a else b) "" strings

(* Problem 3 *)
fun longest_string2 strings =
  List.foldl (fn (a, b) => if String.size(a) >= String.size(b) then a else b) ""  strings

(* Problem 4 *)
fun longest_string_helper f strings = List.foldl(fn (a,b) => if f(String.size(a),String.size(b)) then a else b) "" strings

val longest_string3 = longest_string_helper (op >)  

val longest_string4  = longest_string_helper (op >=)  

(* Problem 5 *)
val longest_capitalized = longest_string1 o only_capitals

(* Problem 6 *)
val rev_string = implode o rev o explode

(* Problem 7 *)
fun first_answer f stuff = 
  case stuff of
       []        => raise NoAnswer
     | s::stuff' => case f(s) of
                         NONE    => first_answer f stuff'
                       | SOME(v) => v

(* Problem 8 *)
fun all_answers f stuff =
  case stuff of 
       [] => SOME []
     | _  => let val answer = List.filter (fn x => x <> NONE) (map f stuff) in
               if length answer = length stuff 
               then SOME(List.concat(map (fn x => case x of SOME(v) => v) answer)) (* To avoid a list of 
                                                                                      lists we need to 
                                                                                      concatenate *) 
               else NONE
             end

(* Problem 9 *)
val count_wildcards = g (fn x => 1) (fn s => 0)

val count_wild_and_variable_lengths = g (fn x => 1) (fn s => String.size s)

fun count_some_var (s, p) = g (fn x => 0) (fn ss => if ss = s then 1 else 0) p 

(* Problem 10*)
fun check_pat p =
  let 
    fun first_helper p = 
      case p of 
           TupleP pats          => List.foldl (fn(a,b) => first_helper(a) @ b) []  (pats)
         | Variable s           => [s]
         | ConstructorP (s,cp)  => first_helper cp
         | _                    => []
    fun second_helper strings = 
      case strings of
           []          => true
         | s::strings' => if (List.exists (fn x => x = s) strings')
                          then false
                          else second_helper strings'
  in
    second_helper(first_helper(p))
  end

(* Problem 11*)
fun match (v, p) =
  case (v,p) of
       (_, Wildcard)                               => SOME []
     | (_, Variable s)                             => SOME [(s,v)]
     | (Unit, UnitP)                               => SOME []
     | (Const n, ConstP m)                         => if n = m then SOME[] else NONE
     | (Constructor(s2, vv), ConstructorP(s1, pp)) => if s1 = s2 then match(vv,pp) else NONE
     | (Tuple vs, TupleP ps)                       => if length vs <> length ps 
                                                      then NONE
                                                      else all_answers (fn pair => match pair) 
                                                                       (ListPair.zip(vs, ps))
     | (_,_)                                       => NONE


(* Problem 12 *)
fun first_match v ps =
  SOME (first_answer (fn p => match(v,p) ) ps)
  handle NoAnswer => NONE
