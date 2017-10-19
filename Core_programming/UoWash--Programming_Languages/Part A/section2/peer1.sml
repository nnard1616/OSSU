(* Dan Grossman, Coursera PL, HW2 Provided Code *)

(* if you use this function to compare two strings (returns true if the same
   string), then you avoid several of the functions in problem 1 having
   polymorphic types that may be confusing *)
fun same_string(s1 : string, s2 : string) =
    s1 = s2

(* put your solutions for problem 1 here *)


(* val all_except_option = fn : string * string list -> string list option *)
fun all_except_option (s, slist) =
    let fun helper(slist, res) =
            case slist of
                  [] => NONE
                | x::xs => if not (same_string(x, s))
                            (* place the most frequent case to "then"
                               for better performance *)
                            then helper(xs, res @ [x])
                            else SOME(res @ xs)
    in
        helper(slist, [])
    end
    
(* val get_substitutions1 = fn : string list list * string -> string list *)
fun get_substitutions1 (sll, s) =
	case sll of
		  [] => []
		| sl::sll' => (case all_except_option (s, sl) of
						 NONE => []
						| SOME sl' => sl')
					@ get_substitutions1 (sll', s)

(* val get_substitutions2 = fn : string list list * string -> string list *)
fun get_substitutions2 (sll, s) =
	let fun helper(sll, res) = 
		case sll of
			  [] => res
			| sl::sll' => let val sl' =
							case all_except_option (s, sl) of
								  NONE => []
								| SOME sl' => sl'
						in
							 helper(sll', sl' @ res)
						end
	in
		helper(sll, [])
	end
					
(* val similar_names = fn : string list list * {first:string, last:string, middle:string}
								-> {first:string, last:string, middle:string} list *)
fun similar_names (subsList, {first = first, last = last, middle = middle}) =
	let val names = get_substitutions2(subsList, first)
		fun helper(sl, res) =
			case sl of
				  [] => res
				| x::sl' => helper(sl', res @ [{first = x, last = last, middle = middle}])
	in
		helper(names, [{first = first, last = last, middle = middle}])
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


(* val card_color = fn : card -> color *)
fun   card_color (Clubs, _) = Black
    | card_color (Spades, _) = Black
    | card_color (Diamonds, _) = Red
    | card_color (Hearts, _) = Red
        
(* val card_value = fn : card -> int *)
fun   card_value (_, Num n) = n
    | card_value (_, Ace) = 11
    | card_value (_) = 10


(* val remove_card = fn : card list * card * exn -> card list *)
fun remove_card (cs, c, e) =
    let fun helper(cs, res) = 
		case cs of
			  [] => raise e
			| c'::cs' => if c = c'
                         then res @ cs'
                         else helper(cs', res @ [c'])
	in
		helper(cs, [])
	end
    
(* val all_same_color = fn : card list -> bool *)
fun all_same_color (cs) =
    case cs of
        [] => true
        | c::[] => true
        | c1::c2::cs' => if card_color (c1) = card_color (c2)
                      then all_same_color (c2::cs')
                      else false
        
(* val sum_cards = fn : card list -> int *)
fun sum_cards (cs) =
    let fun helper(cs, res) =
            case cs of
                  [] => res
                | c::cs' => helper(cs', res + card_value(c))
    in
        helper(cs, 0)
    end
    
(* val score = fn : card list * int -> int *)
fun score (cs, goal) =
    let val sumc = sum_cards (cs)
    in
        let val pscore =
                if sumc > goal
                then 3 * (sumc - goal)
                else (goal - sumc)
        in
            if all_same_color (cs)
            then pscore div 2
            else pscore
        end
    end
    
(* val officiate = fn : card list * move list * int -> int *)
fun officiate (cs, ms, goal) =
    let fun helper(cs, ms, hs) =
            case ms of
                  [] => score(hs, goal)
                | (Discard c) ::ms' =>
                        helper(cs, ms', remove_card (hs, c, IllegalMove))
                | Draw::ms' =>
					case cs of
						  [] => score (hs, goal)
						| c::cs' => let val newHs = hs @ [c] 
									val newScore = score(newHs, goal)
								  in if newScore > goal
									then newScore
									else helper(cs', ms', newHs)
								  end
						  
                
    in
        helper(cs, ms, [])
    end
