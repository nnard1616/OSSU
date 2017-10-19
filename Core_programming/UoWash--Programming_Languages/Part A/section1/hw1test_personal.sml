(* Homework1 Simple Test *)
(* These are basic test cases. Passing these tests does not guarantee that your code will pass the actual homework grader *)
(* To run the test, add a new line to the top of this file: use "homeworkname.sml"; *)
(* All the tests should evaluate to true. For example, the REPL should say: val test1 = true : bool *)

use "nathan_nard_hw1.sml";

val test1 = is_older ((1,2,3),(2,3,4)) 

val test2 = number_in_month ([(2012,2,28),(2013,12,1)],2) 

val test3 = number_in_months ([(2012,2,28),(2013,12,1),(2011,3,31),(2011,4,28)],[2,3,4]) 

val test4 = dates_in_month ([(2012,2,28),(2013,12,1)],2) 


val test5 = dates_in_months ([(2012,2,28),(2013,12,1),(2011,3,31),(2011,4,28)],[2,3,4]) 

val test6 = get_nth (["hi", "there", "how", "are", "you"], 2)

val test7 = date_to_string (2013, 6, 1) 

val test8 = number_before_reaching_sum (10, [1,2,3,4,5]) 
val test81 = number_before_reaching_sum (10, [11,2,3,4,5])
val test82 = number_before_reaching_sum (10, [1,2,3])

val test9 = what_month 70 

val test10 = month_range (31, 34)
val test101 = month_range (330, 365)

val test11 = oldest([(2012,2,28),(2011,3,31),(2011,4,28)]) 

val test12 = remove_dupes([2,3,4,3,4,5], [])

val test131 = reasonable_date((2001, 2, 29))
val test132 = reasonable_date((2000, 2, 29))
val test133 = reasonable_date((~20, 2, 29))
val test134 = reasonable_date((2345, 2, 50))
val test135 = reasonable_date((2345, 20, 5))
val test136 = reasonable_date((2345, 20, 50))
val test137 = reasonable_date((2017, 12, 31))
