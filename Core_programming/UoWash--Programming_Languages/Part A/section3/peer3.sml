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

val only_capitals = List.filter (fn s => Char.isUpper(String.sub(s, 0)))
    
val longest_string1 = List.foldl (fn (s1, s2) => if String.size(s1) > String.size(s2) then s1 else s2) ""

val longest_string2 = List.foldl (fn (s1, s2) => if String.size(s1) >= String.size(s2) then s1 else s2) ""

fun longest_string_helper f =
    List.foldl (fn (s1, s2) => if f(String.size(s1), String.size(s2)) then s1 else s2) ""
    
val longest_string3 = longest_string_helper (fn (x, y) => x > y)

val longest_string4 = longest_string_helper (fn (x, y) => x >= y)

val longest_capitalized = longest_string1 o only_capitals

val rev_string = String.implode o rev o String.explode

fun first_answer f xs =
    case xs of
        [] => raise NoAnswer
      | x::xs' => case f(x) of
                      NONE => first_answer f xs'
                    | SOME(ans) => ans

fun all_answers f xs =
    let fun aux(xs, acc) =
        case xs of
            [] => SOME(acc)
          | x::xs' => case f(x) of
                          NONE => NONE
                        | SOME(ans) => aux(xs', acc@ans)
    in
        aux(xs, [])
    end

val count_wildcards = g (fn () => 1) (fn x => 0)

val count_wild_and_variable_lengths = g (fn () => 1) String.size

fun count_some_var(str, p) = g (fn () => 0) (fn x => if x = str then 1 else 0) p

fun check_pat p =
    let fun aux1(p) =
        case p of
            Variable x        => [x]
          | TupleP ps         => List.foldl (fn (p, acc) => acc @ aux1(p)) [] ps
          | ConstructorP(_,p') => aux1(p')
          | _                 => []
        fun aux2(xs) =
            case xs of
                [] => true
              | x::xs' => if List.exists (fn s => s = x) xs'
                         then false
                         else aux2(xs')
    in
        aux2(aux1(p))
    end

fun match(v, p) =
    case (v, p) of
        (_, Wildcard) => SOME []
      | (v, Variable s) => SOME [(s, v)]
      | (Unit, UnitP) => SOME []
      | (Const n, ConstP m) => if n = m then SOME [] else NONE
      | (Tuple vs, TupleP ps) => if List.length vs = List.length ps
                                 then all_answers match (ListPair.zip(vs, ps))
                                 else NONE
      | (Constructor(s2, vc), ConstructorP(s1, pc)) => if s1 = s2
                                                       then match(vc, pc)
                                                       else NONE
      | _ => NONE
      
fun first_match v ps =
    SOME (first_answer (fn x => match(v, x)) ps) 
    handle NoAnswer => NONE



(* Challenge problem *)

fun pat_to_type(xs, pat) =
    case pat of
        UnitP => UnitT
      | ConstP(_) => IntT
      | TupleP(ps) => TupleT(List.map (fn p => pat_to_type(xs, p)) ps)
      | ConstructorP(str, p) => (case List.find (fn (x1, x2, x3) => x1 = str) xs of
                                   NONE => raise NoAnswer
                                 | SOME(x1, x2, x3) => let val new_pat = pat_to_type(xs, p)
                                                       in
                                                           if new_pat = x3 orelse new_pat = Anything
                                                           then Datatype(x2)
                                                           else raise NoAnswer
                                                       end)
      | _ => Anything

fun typecheck_patterns(xs, ps) =
    let fun aux(t1, t2) = 
            if t1 = t2
            then t1
            else case (t1, t2) of
                    (t1, Anything) => t1
                  | (Anything, t2) => t2
                  | (TupleT ps1, TupleT ps2) =>
                        if List.length ps1 = List.length ps2
                        then TupleT(List.map aux(ListPair.zip(ps1, ps2)))
                        else raise NoAnswer
                  | (_, _) => raise NoAnswer
        val typs = List.map (fn x => pat_to_type(xs, x)) ps
                   handle NoAnswer => []
    in
        case typs of
            [] => NONE
          | t::ts => SOME (List.foldl aux t ts)
                          handle NoAnswer => NONE
    end


















































