(* Problem 1 *)
fun date_tuple_to_int(x:int*int*int) =(#1 x)* 10000 +(#2 x)* 100 +(#3 x)

fun is_older (x:int*int*int, y:int*int*int) = 
  date_tuple_to_int(x) < date_tuple_to_int(y)

(* Problem 2 *)
fun number_in_month (dates : (int*int*int) list, month : int) =
  if null dates
  then 0
  else
    if (#2 (hd dates)) = month
    then number_in_month(tl dates, month) + 1
    else number_in_month(tl dates, month)

(* Problem 3 *)    
fun number_in_months (dates : (int*int*int) list, months : int list) = 
  if null months
  then 0
  else number_in_month(dates, hd months) +
       number_in_months(dates, tl months)

(* Problem 4 *)    
fun dates_in_month (dates : (int*int*int) list, month : int) = 
  if null dates
  then []
  else
    if (#2 (hd dates)) = month
    then hd dates::dates_in_month(tl dates, month)
    else dates_in_month(tl dates, month)

(* Problem 5 *)
fun append_dates ( xd : (int*int*int) list, yd : (int*int*int) list) =
  if null xd
  then yd
  else (hd xd) :: append_dates(tl xd, yd)

fun dates_in_months (dates : (int*int*int) list, months : int list) = 
  if null months
  then []
  else append_dates(dates_in_month(dates, hd months), dates_in_months(dates, tl months))

(* Problem 6 *)
fun get_nth (strings : string list, nth : int) =
  if nth = 1
  then hd strings
  else get_nth(tl strings, nth-1)

(* Problem 7 *)
val months = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]

fun date_to_string(date : int*int*int) =
  get_nth(months, (#2 date)) ^ " " ^ Int.toString(#3 date) ^ ", " ^ Int.toString(#1 date)

(* Problem 8 *)
fun number_before_reaching_sum(sum : int, nums : int list) =
  if null nums orelse sum <= (hd nums)
  then 0
  else number_before_reaching_sum(sum - (hd nums), tl nums) + 1

(* Problem 9 *)
val month_days = [31,28,31,30,31,30,31,31,30,31,30,31]

fun what_month ( day_of_year : int) =
  number_before_reaching_sum(day_of_year, month_days) + 1

(* Problem 10 *)
fun month_range ( day1 : int, day2 :int ) =
  if day1 > day2
  then []
  else what_month(day1) :: month_range(day1+1, day2)

(* Problem 11 *)
fun oldest(dates : (int*int*int) list) =
  if null dates
  then NONE
  else let fun oldest_nonempty (dates : (int*int*int) list) =
      if null (tl dates)
      then hd dates
      else let val tl_oldest = oldest_nonempty(tl dates)
          in
              if is_older (hd dates, tl_oldest)
              then hd dates
              else tl_oldest
          end
      in
          SOME (oldest_nonempty dates)
      end

(* Problem 12 *)
fun search ( nums : int list, q : int) =
  if null nums
  then false
  else if (hd nums) = q
    then true
    else search(tl nums, q)

fun remove_dupes ( nums : int list, no_dupes : int list) = 
  if null nums
  then []
  else if search(no_dupes, hd nums) = false (* hd not in no_dupes *)
    then (hd nums) :: remove_dupes ( tl nums, (hd nums) :: no_dupes) (*add hd to no_dupes *)
    else remove_dupes(tl nums, no_dupes)

fun number_in_months_challenge (dates : (int*int*int) list, months : int list) = 
  number_in_months(dates, remove_dupes(months, []))

fun dates_in_months_challenge  (dates : (int*int*int) list, months : int list) = 
  dates_in_months(dates, remove_dupes(months, []))

(* Problem 13 *)
fun get_nth_int (ints : int list, nth : int) =
  if nth = 1
  then hd ints
  else get_nth_int(tl ints, nth-1)

fun february_calculator(year : int ) =
  if (( (year mod 4) = 0 andalso (year mod 100) <> 0) orelse (year mod 400) = 0)
  then 29
  else 28

fun reasonable_date (date : (int*int*int)) = 
  if (#1 date) > 0 andalso (#2 date) <= 12 andalso (#2 date) >= 1
  then if (#2 date) = 2 (*fuck february *)
       then if (#3 date) >= 1 andalso (#3 date) <= february_calculator(#1 date)
            then true
            else false
       else if (#3 date) >= 1 andalso (#3 date) <= get_nth_int(month_days, #2 date)
            then true
            else false
  else false


