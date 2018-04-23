fun same_string(s1 : string, s2 : string) =
  s1 = s2


fun all_except_option (name, nameList) =

  let
      fun inner (name, nameList) =
	case nameList of
	    [] => []
	  | head::tail => if same_string (head, name) 
			  then [] @ tail
			  else head::inner(name, tail)

      val x = inner (name, nameList)
		    
  in
      if x = nameList
      then NONE
      else SOME x
	      	
  end			 


fun get_substitutions1 (nameLists, name) =
  case nameLists of
      [] => []
    | head::rest => 
      case all_except_option(name, head) of
	  NONE => get_substitutions1 (rest, name)
	| SOME list => list @ get_substitutions1 (rest, name)	      


fun get_substitutions2 (nameLists, name) =

  let
      fun no_stack2 (nameLists, acc) =
	case nameLists of
	    [] => acc
	  | head::rest => 
	    case  all_except_option(name, head) of
		NONE => no_stack2 (rest, acc)
	      | SOME list => no_stack2 (rest, acc @ list)

  in no_stack2 (nameLists, [])

  end


fun similar_names (nameLists, {first=x,middle=y,last=z}) =	  

  let
      fun helper (sub_names) =
	case sub_names of
	    [] => []
	  | head::tail => {first=head,middle=y,last=z} :: helper(tail)
																
  in {first=x,middle=y,last=z} :: (helper (get_substitutions1 (nameLists, x)))
				      
  end

      
datatype suit = Clubs | Diamonds | Hearts | Spades
datatype rank = Jack | Queen | King | Ace | Num of int 
type card = suit * rank

datatype color = Red | Black
datatype move = Discard of card | Draw 

exception IllegalMove

val c1 = (Clubs,Jack);
val c2 = (Diamonds, Ace);
val c3 = (Spades, King);
val c4 = (Hearts, Num (1));
val c5 = (Hearts, Num (2));
val c6 = (Hearts, Num (3));
val card_list = [c1, c2, c3, c4, c5, c6];


fun card_color card =
  case card of
      (Clubs, _) => Black
    | (Spades,_) => Black 
    | _ => Red 


fun card_value card =
  case card of
      (_, Ace) => 11
    | (_, Num i) => i
    | _ => 10


fun remove_card (cs, c, e) =
  case cs of
      x::xs' => if x = c
                then [] @ xs'
                else x::remove_card (xs', c, e)				    
    | _ => raise IllegalMove 


fun all_same_color cs =
  case cs of
      [] => true
    | x::[] => true 
    | x::y::xs => if card_color(x) = card_color(y)
		  then all_same_color(y::xs)
		  else false
			   

fun sum_cards cs =
  let
      fun no_stack (cs,acc) =
	case cs of
	    [] => acc
	  | c::cs' => no_stack(cs', card_value(c) + acc) 

  in no_stack (cs, 0)
  end
      

fun score (heldcards, goal) =
  case heldcards of
      [] => 0 
   |    x::xs => 

	let val sum = sum_cards(heldcards)
	    val all_same = all_same_color (heldcards)

	in
	    if sum > goal andalso all_same
	    then 3 * (sum - goal) div 2
	    else if sum > goal
	    then  3 * (sum - goal)
	    else if sum < goal andalso all_same
	    then (goal - sum) div 2
	    else (goal - sum)

	end


fun officiate (cardList, moveList, goal) =
  let
      fun helper (heldcards, cardList, moveList, goal) =
	case moveList of
	    [] => score(heldcards, goal)
	  | head::tail => case head of
			      Discard i => helper (remove_card (heldcards, i, IllegalMove), cardList, tail, goal)
			   |  Draw => case cardList of
					  [] => score(heldcards, goal)
					| first::rest => if sum_cards (heldcards) > goal
							 then score(heldcards, goal)
							 else helper (first::heldcards, remove_card(cardList, first, IllegalMove), tail, goal)
								     

  in helper ([], cardList, moveList, goal)

  end
