# problem 1

balance = 484
annualInterestRate = 0.2
monthlyPaymentRate = 0.04

monthly_interest_rate = annualInterestRate /12.0
for m in range(12):
  minimum_monthly_payment = (monthlyPaymentRate)*balance
  monthly_unpaid_balance = balance - minimum_monthly_payment
  balance = monthly_unpaid_balance * (monthly_interest_rate+1)
print("Remaining balanced: ", round(balance, 2))


# problem 2 - skip

# problem 3
balance = 999999
annualInterestRate = 0.18


monthly_interest_rate = annualInterestRate /12.0
min_monthly_payment = balance /12.0
max_monthly_payment = (balance*(1.0+monthly_interest_rate)**12.0)/12.0
end_balance = balance
monthly_payment = (min_monthly_payment+max_monthly_payment) / 2.0


while ( abs(end_balance) >= 0.01):

  end_balance = balance
  monthly_payment = (min_monthly_payment+max_monthly_payment) / 2.0
  for m in range(12):
    monthly_unpaid_balance = end_balance - monthly_payment
    end_balance = monthly_unpaid_balance * (monthly_interest_rate + 1)

  if(end_balance > 0):
    min_monthly_payment = monthly_payment
  else:
    max_monthly_payment = monthly_payment

print("Lowest Payment: ", round(monthly_payment, 2))
