fun is_older ((y1: int, m1: int, d1: int), (y2: int, m2: int, d2: int))  = 
	y1 < y2 orelse (y1 = y2 andalso (m1 < m2 orelse (m1 = m2 andalso d1 < d2)))
    
fun number_in_month (ds: (int * int * int) list, m: int) =
    let fun countM(ds: (int * int * int) list, cnt: int) =
		if null ds
		then cnt
		else let val incDay = if #2 (hd ds) = m then 1 else 0
			 in
				countM(tl ds, cnt + incDay)
			 end
    in
        countM(ds, 0)
    end
    
fun number_in_months (dates: (int * int * int) list, days: int list) =
    let fun sumDays(days: int list, cnt: int) = 
		if null days
		then cnt
		else let val cntDay = number_in_month(dates, hd days)
			 in
				sumDays(tl days, cnt + cntDay)
			 end
    in
        sumDays(days, 0)
    end
    
fun dates_in_month (ds: (int * int * int) list, m: int) =
    let fun getDates(ds: (int * int * int) list) =
		if null ds
		then []
		else if #2 (hd ds) = m
			then (hd ds) :: getDates(tl ds)
			else getDates(tl ds)
    in
        getDates(ds)
    end

fun dates_in_months (dates: (int * int * int) list, ms: int list) =
    let fun listOfDays(ms: int list) = 
		if null ms
		then []
		else dates_in_month(dates, hd ms) @ listOfDays(tl ms)
    in
        listOfDays(ms)
    end

fun get_nth (ss: string list, n: int) =
    if null ss
    then ""
    else if n <= 1
         then hd ss
         else get_nth (tl ss, n-1)

fun date_to_string (y: int, m: int, d: int) =
	let val monthsStrings = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
	in 
		get_nth(monthsStrings, m) ^ " " ^ Int.toString(d) ^ ", " ^ Int.toString(y)
	end

fun number_before_reaching_sum (sum: int, xs: int list) =
	let fun cumSumSlice(xs: int list, sumLeft: int, idx: int) =
			let val topVal = (hd xs)
			in if sumLeft <= topVal
				then idx
				else cumSumSlice(tl xs, sumLeft - topVal, idx + 1)
			end
	in
		cumSumSlice(xs, sum, 0)
	end

fun what_month (dayN: int) =
	let val monthsLength = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
	in 
		number_before_reaching_sum(dayN, monthsLength) + 1
	end

fun month_range(d1: int, d2: int) =
	let fun mr (curDay: int, months: int list) =
			if curDay > d2
			then months
			else mr(curDay+1, months @ [what_month (curDay)])
	in
		mr(d1, [])
	end
	
fun oldest (dates: (int * int * int) list) =
	if null dates
	then NONE
	else let fun findOldest(dates: (int * int * int) list, oldestDate: (int * int * int)) =
				if null dates
				then oldestDate
				else let val newOldesDate =
						if is_older(hd dates, oldestDate)
						then hd dates
						else oldestDate
					in
						findOldest(tl dates, newOldesDate)
					end
		in
			SOME (findOldest(tl dates, hd dates))
		end

