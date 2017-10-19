(* Dan Grossman, Coursera PL, HW2 Provided Code *)

(* if you use this function to compare two strings (returns true if the same
   string), then you avoid several of the functions in problem 1 having
   polymorphic types that may be confusing *)
fun same_string(s1 : string, s2 : string) =
    s1 = s2

(* Problem 1a *)
fun all_except_option( q_string : string, strings : string list) = (*q_string = query string*)
  let fun extract(q_string, strings, acc) = (*accumulator to collect mismatched strings*)
          case strings of 
               []          => acc
             | s::strings' => if same_string(q_string, s)
                              then extract(q_string, strings', acc) (*q_string in strings*)
                              else extract(q_string, strings', acc@[s]) (*q_string not in strings*)
  in let val extracts = extract(q_string, strings, []) (*so we don't have to compute twice*)
     in if extracts = strings (*if accumulator creates the same list as 'strings'*)
        then NONE (*then 'strings' does not contain q_string*)
        else SOME extracts (*else 'strings' did contain q_string, return popped 'strings'*)
     end
  end

(* Problem 1b *)
fun get_substitutions1(subs : (string list) list, q_string : string) =
  let fun extract(subs, q_string, acc) =  
          case subs of 
               []         => acc
             | sub::subs' => case all_except_option(q_string, sub) of
                                  NONE     => extract(subs', q_string, acc)
                                | SOME ext => extract(subs', q_string, acc @ ext)
  in
    extract(subs,q_string, [])
  end

(* Problem 1c - First attempt at Problem 1b satisfied Problem 1c as well, so I copy/pasted*)
fun get_substitutions2(subs : (string list) list, q_string : string) =
  let fun extract(subs, q_string, acc) =  
          case subs of 
               []         => acc
             | sub::subs' => case all_except_option(q_string, sub) of
                                  NONE     => extract(subs', q_string, acc)
                                | SOME ext => extract(subs', q_string, acc @ ext)
  in
    extract(subs,q_string, [])
  end

(* Problem 1d *)
fun similar_names(subs, {first=f, middle=m, last=l}) =
  let fun possible_full_names(names, acc) = 
      case names of
           []        => acc
         | n::names' => possible_full_names(names', acc@[{first=n, middle=m, last=l}])    
  in 
    possible_full_names(get_substitutions1(subs, f), [{first=f, middle=m, last=l}])
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
(* Problem 2a *)
fun card_color(in_card) =
  case in_card of
       (Diamonds, _) => Red
     | (Hearts, _)   => Red
     | (Clubs, _)    => Black
     | (Spades, _)   => Black

(* Problem 2b *)
fun card_value(in_card) = 
  case in_card of
       (_, Num value) => value
     | (_, Ace)       => 11
     | (_, _)         => 10

(* Problem 2c *)
fun remove_card(cs, c, e) =
  case cs of
       []      => raise e
     | cc::cs' => if cc = c
                  then cs'
                  else cc::remove_card(cs', c, e)  

(* Problem 2d *)
fun all_same_color(cards) =
  case cards of
       []             => true
     | [c1]           => true
     | c1::c2::cards' => if card_color(c1) = card_color(c2)
                         then all_same_color(c2::cards')
                         else false
(* Problem 2e *)
fun sum_cards(cards) =
  let fun sum_values(cards, sum) =
          case cards of
               [] => sum
             | c::cards' => sum_values(cards', card_value(c) +sum)
  in
    sum_values(cards, 0)
  end

(* Problem 2f *)
fun pscore(hand, goal) = 
  let val sum = sum_cards(hand) 
  in
    if sum > goal
    then 3*(sum-goal)
    else goal - sum
  end

fun score (hand, goal) = 
  if all_same_color(hand)
  then pscore(hand,goal) div 2
  else pscore(hand,goal)

(* Problem 2g *)
fun officiate(cards, moves, goal) = 
  let fun current(cards, moves, hand) = 
          case (cards, moves, hand) of
               (_, [],_)                           => score(hand, goal)
             | ([], _,_)                           => score(hand, goal)
             | (c::cards', Draw::moves',_)         => if sum_cards(c::hand) > goal
                                                      then score(c::hand, goal)
                                                      else current(cards', moves', c::hand)
             | (c::cards', (Discard d)::moves', _) => current(cards, moves', remove_card(hand, d, IllegalMove))
  in
    current(cards, moves, [])
  end

