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

val only_capitals = List.filter (Char.isUpper o (fn x => String.sub(x, 0)))

val longest_string1 =
    List.foldl
		(fn (s, maxS) =>
            if String.size s > String.size maxS
            then s
            else maxS
		)
		""
        
val longest_string2 =
    List.foldl
		(fn (s, maxS) =>
            if String.size s >= String.size maxS
            then s
            else maxS
		)
		""

val longest_string_helper = (fn gt_fun =>
    List.foldl
		(fn (s, maxS) =>
			if gt_fun(String.size s, String.size maxS)
            then s
            else maxS
		)
		"")
        
val longest_string3 = longest_string_helper op>
val longest_string4 = longest_string_helper op>=

val longest_capitalized = longest_string3 o only_capitals

val rev_string = String.implode o List.rev o String.explode

fun first_answer f = fn xs =>
	case xs of
		  [] => raise NoAnswer
		| x::xs' =>
			case (f x) of
				  NONE => (first_answer f xs')
				| SOME v => v

fun all_answers f = fn xs =>
	let fun helper (xs, res) =
		case xs of
			  [] => (SOME res)
			| x::xs' =>
				case (f x) of
					  NONE => NONE
					| SOME v => helper(xs', res @ v)
	in
		helper(xs, [])
	end

val count_wildcards = g (fn _ => 1) (fn _ => 0)

val count_wild_and_variable_lengths = g (fn _ => 1) String.size

fun count_some_var (s, p) = g (fn _ => 0)
	(fn x => if x = s then 1 else 0) p
	
fun check_pat p =
	let fun getVars(p, res) =
			case p of
				  Variable x         => x :: res
				| TupleP ps          => List.foldl getVars res ps
				| ConstructorP(_,p') => getVars(p', res)
				| _                  => res;
		
		fun isDistinct xs =
			case xs of
				 x::xs' =>
					if List.exists (fn s => s=x) xs'
					then false
					else isDistinct xs'
				| _ => true
	in
		isDistinct (getVars(p, []))
	end

fun match vp = case vp of
	  (_, Wildcard) => SOME []
	| (v, Variable s) => SOME [(s, v)]
	| (Unit, UnitP) => SOME []
	| (Const i, ConstP i') =>
		if i = i'
		then SOME []
		else NONE
	| (Tuple vs, TupleP ps) =>  
		if List.length(vs) = List.length(ps)
		then (all_answers match (ListPair.zip(vs, ps)))
		else NONE
	| (Constructor(s1, v), ConstructorP(s2, p)) =>
		if s1 = s2
		then match (v, p)
		else NONE
	| _ => NONE
	
fun first_match v ps =
	SOME (first_answer (fn p => match(v, p)) ps)
	handle NoAnswer => NONE
