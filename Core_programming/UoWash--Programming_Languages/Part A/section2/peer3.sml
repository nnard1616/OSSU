(* Dan Grossman, Coursera PL, HW2 Provided Code *)

(* if you use this function to compare two strings (returns true if the same
   string), then you avoid several of the functions in problem 1 having
   polymorphic types that may be confusing *)
fun same_string(s1 : string, s2 : string) =
	s1 = s2

(* put your solutions for problem 1 here *)

fun all_except_option (st, ls) =
	case ls of [] => NONE
		| l::ls' => 
			if same_string(st, l) 
				then SOME ls'
				else 
					case all_except_option(st, ls') of 
						NONE => NONE
						| SOME rst => SOME (l::rst)

fun get_substitutions1 (dict, s) = 
	case dict of [] => []
		|x::xs => case all_except_option(s, x) of 
			NONE => get_substitutions1(xs, s)
			| SOME ls => get_substitutions1(xs, s) @ ls

fun get_substitutions2 (subs, s) = 

	let fun aux(subs, ls) =
		case subs of [] => ls
		| x::xs => case all_except_option(s, x) of 
			NONE => aux(xs, ls)
			| SOME res => aux(xs, res @ ls)
	in
		aux(subs, [])
	end

fun similar_names (subs, name:{first:string, last:string, middle:string}) = 

	let
		fun aux (subs, acc) = 
			case subs of [] => acc
				| x::xs => 
					aux(xs, ({first = x, last= #last name, middle = #middle name})::acc)
	in
		aux(get_substitutions2(subs, #first name), [name])
	end


(* you may assume that Num is always used with values 2, 3, ..., 10
   though it will not really come up *)
datatype suit = Clubs | Diamonds | Hearts | Spades
datatype rank = Jack | Queen | King | Ace | Num of int 
type card = suit * rank

datatype color = Red | Black
datatype move = Discard of card | Draw 

exception IllegalMove

(* put your solutions for problem 2 here *)

fun card_color (s, _) = 
	case s of 
		Spades => Black
		|Clubs => Black
		|_ => Red

fun card_value (_, r) =
	case r of 
		Num x => x
		| Ace => 11
		| _ => 10

fun remove_card(crds, crd: card, exp) =
	case crds of [] => raise exp
		| x::xs => if x = crd
			then xs
			else x::remove_card(xs, crd, exp)

fun all_same_color crds =
	case crds of 
		x1::x2::xs => card_color x1 = card_color x2 andalso all_same_color (x2::xs)
		| _ => true

fun sum_cards crds = 
	case crds of [] => 0
		| x::xs => card_value x + sum_cards xs

fun score (crds, goal) =
	let 
		val sum = sum_cards crds
		val pre = if goal > sum 
			then goal - sum
			else 3 * (sum - goal)
	in
		if all_same_color crds 
			then pre div 2
			else pre
	end

fun officiate (crds, moves, goal) =

	let fun aux(crds, moves, held) = 

		case moves of
			[] => score(held, goal)
			| (Discard x)::moves => aux(crds, moves, remove_card(held, x, IllegalMove))
			| Draw::moves => 
				case crds of 
					[] => score(held, goal)
					| x::xs => 
						if sum_cards (x::held) > goal
						then score(x::held, goal)
						else aux(xs, moves, x::held)
	in
		aux(crds, moves, [])
	end
