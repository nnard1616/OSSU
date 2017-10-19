(* Homework2 Simple Test *)
(* These are basic test cases. Passing these tests does not guarantee that your code will pass the actual homework grader *)
(* To run the test, add a new line to the top of this file: use "homeworkname.sml"; *)
(* All the tests should evaluate to true. For example, the REPL should say: val test1 = true : bool *)
use "Nathan_hw2.sml";

val test1 = all_except_option ("string", ["SHIT", "string", "FUCK"]) 

val test2 = get_substitutions1 ([["foo"],["there"]], "foo")
val test21 = get_substitutions1 ([["fuck"],["foo"],["foo","foot","fool"],["there"]], "foo") 

val test3 = get_substitutions2 ([["foo"],["there"]], "foo") 

val test4 = similar_names ([["Fred","Fredrick"],["Elizabeth","Betty"],["Freddie","Fred","F"]], {first="Fred", middle="W", last="Smith"}) 
	    

val test5 = card_color (Clubs, Num 2)

val test6 = card_value (Clubs, Num 2)

val test7 = remove_card ([(Hearts, Ace), (Diamonds, Num 5), (Hearts, Ace), (Diamonds, Jack)], (Hearts, Ace), IllegalMove) 

val test8 = all_same_color [(Hearts, Ace), (Hearts, Ace)] 
val test81 = all_same_color [(Spades, Ace), (Hearts, Ace)] 
val test82 = all_same_color [(Diamonds, Ace), (Hearts, Ace)] 
val test83 = all_same_color [(Diamonds, Ace), (Hearts, Ace), (Spades, Num 5)] 

val test9 = sum_cards [(Clubs, Num 2),(Clubs, Num 2)]

val test101 = score ([(Hearts, Num 2),(Clubs, Num 4)],10) 
val test102 = score ([(Hearts, Num 2),(Diamonds, Num 4)],10)
val test103 = score ([(Hearts, Num 10),(Diamonds, Num 4)],10)

val test11 = officiate ([(Hearts, Num 2),(Clubs, Num 4)],[Draw], 15) 

val test12 = officiate ([(Clubs,Ace),(Spades,Ace),(Clubs,Ace),(Spades,Ace)],
                        [Draw,Draw,Draw,Draw,Draw],
                        42)
             

val test13 = (officiate([(Clubs,Jack),(Spades,Num(8))],[Draw,Discard(Hearts,Jack)],42)
      (*       *)
             
