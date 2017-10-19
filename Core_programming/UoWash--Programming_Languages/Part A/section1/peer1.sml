fun is_older((y1 : int,m1 : int,d1 : int),(y2 : int, m2 : int, d2 : int))=
  if y1 < y2 
  then true 
  else
    if y1 <= y2 andalso m1 < m2 
     then true 
    else 
	if y1<= y2 andalso m1 <= m2 andalso d1 < d2
	then true 
	else false;
		
fun is_larger(x1 : int, x2 :int) = x1 > x2;

fun number_in_month( dateList : (( int*int*int)list), month : int) =
  if null dateList
  then 0
  else if (#2 (hd dateList)) = month
  then 1 + number_in_month( tl dateList, month)
  else 0 + number_in_month( tl dateList, month);

fun number_in_months ( dateList : (( int*int*int)list), monthList : int list) =
  if null monthList
  then 0
  else number_in_month ( dateList, hd monthList) + number_in_months( dateList, tl monthList);

fun dates_in_month ( dateList : (( int*int*int)list), month : int) =
  if null dateList
  then []
  else if (#2 (hd dateList)) = month
  then hd dateList :: dates_in_month (tl dateList, month)
  else dates_in_month( tl dateList, month);

fun dates_in_months ( dateList: (( int*int*int)list), monthList : int list) =
    if null monthList
    then []
   else dates_in_month( dateList, hd monthList) @ dates_in_months ( dateList, tl monthList);

fun get_nth ( stringList: string list, n : int) =
  if n = 1
  then hd stringList
  else get_nth( tl stringList, n-1);

fun get_month( month: int ) =
  let val the_months = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
  in 
      get_nth(the_months, month)
  end;


fun date_to_string ( date : (int*int*int) ) =
  get_month(#2 date) ^ " " ^ Int.toString(#3 date) ^ ", " ^ Int.toString(#1 date);

(* *)
fun number_before_reaching_sum( sum : int, intList : int list ) =
  if hd intList >=  sum
  then 0
  else 1 + number_before_reaching_sum (sum - hd intList, tl intList);

fun what_month (day : int) =
  let val days_in_months = [31,28,31,30,31,30,31,31,30,31,30,31]
  in
    1 +  number_before_reaching_sum( day, days_in_months )
  end;

fun month_range(day1 : int, day2 : int ) = 
  if day1 > day2
  then []
  else what_month( day1 ) :: month_range( day1+1, day2 );

fun month_range2(day1 : int, day2 : int) = 
  if day1 > day2
  then []
  else month_range2(day1, day2-1) @ [what_month(day2)];


fun oldest( dateList : (int*int*int) list ) =
  if null dateList
  then NONE
  else
      let fun oldtail ( dateList: (int*int*int) list) =
	    if null (tl dateList) then hd dateList
	    else
		let val oldestTail = oldtail(tl dateList)
		in
		    if is_older(hd dateList, oldestTail)
		    then hd dateList
		    else oldestTail
		end
      in
	  SOME(oldtail(dateList))
      end
	  


