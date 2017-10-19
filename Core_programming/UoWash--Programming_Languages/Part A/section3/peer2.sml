
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

val only_capitals = List.filter (Char.isUpper o (fn st => String.sub(st, 0))) 

val longest_string1 = 
	foldl (fn (x, y) => if String.size x > String.size y then x else y) ""

val longest_string2 = 
	foldl (fn (x, y) => if String.size x >= String.size y then x else y) ""

fun longest_string_helper f = 
	foldl (fn (x, y) => if f(String.size x, String.size y) then x else y) ""

val longest_string3 = longest_string_helper op>
val longest_string4 = longest_string_helper op>=

val longest_capitalized = longest_string1 o only_capitals

val rev_string = String.implode o rev o String.explode

fun first_answer f ls  =
	case ls of [] => raise NoAnswer
		| x::xs => case f x of 
			NONE => first_answer f xs
			|SOME x' => x'

fun all_answers f ls  =
	case ls of [] => SOME []
		| x::xs => 
			case f x of 
				NONE => NONE
				| SOME x' => 
						case all_answers f xs of
							NONE => NONE
							|SOME ls' => SOME (x'::ls')

val count_wildcards = g (fn _ => 1) (fn _ => 0)
val count_wild_and_variable_lengths = g (fn _ => 1) String.size

fun count_some_var(s, p) = g (fn _ => 0) (fn x => if s = x then 1 else 0) p

fun check_pat p =
	let 
		fun names p =
			case p of
				  Wildcard => []
				| Variable x => [x]
				| TupleP ps => 
					List.foldl (fn (p,acc) => (names p) @ acc) [] ps
				| ConstructorP(_,p) => names p
				| _ => []

		fun repeats ls =
			case ls of [] => false
				| x::xs => List.exists (fn a => a = x) xs orelse repeats xs
	in
		not (repeats (names p))
	end

fun match (v, p) =
	case (v, p) of
		(_, Wildcard) => SOME []
		| (Unit, UnitP) => SOME []
		| (_,Variable x) => SOME [(x, v)]
		| (Const x, ConstP x') => 
			if x = x'
			then SOME []
			else NONE
		| (Constructor (s', v'), ConstructorP (s, p')) =>
			if s' = s
			then match(v', p')
			else NONE
		| (Tuple vs, TupleP ps) => 
			let val res = all_answers match (ListPair.zip (vs, ps)) in
			case res of 
				NONE => NONE
				|SOME bnds => SOME (foldl op@ [] bnds)
			end
		| _ => NONE

fun first_match v ps =
	SOME (first_answer match (map (fn p => (v, p)) ps)) 
		handle NoAnswer => NONE
