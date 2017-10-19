(* Function 1 *)
fun is_older (date1 : int*int*int, date2 : int*int*int) =
  if (#1 date1) <> (#1 date2) then (#1 date1) < (#1 date2)
  else if (#2 date1) <> (#2 date2) then (#2 date1) < (#2 date2)
      else (#3 date1) < (#3 date2)	  
			    

(* Function 2 *)
fun number_in_month (dates : (int*int*int) list, month : int) =
  if null dates then 0
  else if #2 (hd dates) = month then 1 + number_in_month(tl dates,month)
  else number_in_month(tl dates,month)


(* Function 3 *)		     
fun number_in_months (dates : (int*int*int) list, months : int list) =
  if null months then 0
  else number_in_month (dates, hd months) + number_in_months (dates, tl months)


(* Function 4 *)
fun dates_in_month (dates : (int*int*int) list, month : int) =
  if null dates then []
  else if #2 (hd dates) = month then hd dates :: dates_in_month(tl dates,month) else dates_in_month(tl dates, month)


(* Function 5 *)						   
fun dates_in_months (dates : (int*int*int) list, months : int list) =
  if null months then []
  else
      dates_in_month(dates, hd months) @ dates_in_months(dates, tl months)


(* Function 6 *)
fun get_nth (words : string list, n : int) =
  if n = 1 then hd words
  else get_nth (tl words, n-1)


(* Function 7 *)
fun date_to_string (date: int*int*int) =
  get_nth (["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"], #2 date) ^ " " ^ Int.toString(#3 date) ^ ", " ^ Int.toString(#1 date)


(* Function 8 *)
fun number_before_reaching_sum (sum : int, numbers : int list) =
  if hd numbers >= sum then 0
  else 1 + number_before_reaching_sum (sum - hd numbers, tl numbers)

      
(* Function 9 *)
fun what_month (day : int) =
  1 + number_before_reaching_sum (day,[31,28,31,30,31,30,31,31,30,31,30,31])


(* Function 10 *)      
fun month_range (day1 : int, day2 : int) =
  if day1 > day2 then []
  else
      what_month(day1) :: month_range (day1 + 1, day2)
 

(* Function 11 *)	  
fun oldest (dates : (int*int*int) list) =
  if null dates then NONE
  else let
      fun oldest_nonempty(dates : (int*int*int) list)  =
	if null (tl dates) then hd dates
	else
	    let val d = oldest_nonempty(tl dates) 
	    in
		if is_older(d, hd dates) then d else hd dates
	    end
  in
      SOME (oldest_nonempty dates)
  end

(* Challenging Functions - Helper function *)
fun remove_duplicates (l: int list) =
	let
	    fun check (l: int list, n : int) =
	      if null l then false
	      else if hd l = n then true
	      else check (tl l, n)
	    fun go_through_list (l: int list) =
	      if null l then []
	      else if check(tl l, hd l) then go_through_list(tl l)
	      else hd l :: go_through_list(tl l)
	in
	    go_through_list(l)
	end
	    
(* Function 12 - 1 *)	   	   
fun number_in_months_challenge (dates : (int*int*int) list, months : int list) =
  number_in_months(dates, remove_duplicates months)

(* Function 12 - 2 *)	
fun dates_in_months_challenge (dates : (int*int*int) list, months : int list) =
  dates_in_months(dates, remove_duplicates months)
     
      
(* Function 13 *)
fun reasonable_date (date : int*int*int) = 
  if (#1 date >= 1) andalso (#2 date >= 1) andalso (#2 date <= 12) andalso (#3 date >= 1) andalso (#3 date <= 31) then
      let fun check_month (days_in_month : int list, count : int) =
	    if  #2 date = 2 then let fun leap_year(year, days_in_feb) =
				       if year mod 4 = 0 andalso year mod 100 <> 0 then #3 date <= 29 else #3 date <= 28 
				 in leap_year(#1 date, #3 date)
				 end
				     
	    else if count = #2 date then (#3 date <= hd days_in_month)
	    else check_month(tl days_in_month, count + 1)
      in
	  check_month([31,29,31,30,31,30,31,31,30,31,30,31],1)
      end
  else false

