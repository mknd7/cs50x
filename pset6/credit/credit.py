from cs50 import get_int

ccnumber = get_int("Number: ")
ccnumcopy = ccnumber
mul_sum, alt_sum, temp, num_digits = 0, 0, 0, 0

while ccnumcopy != 0:
    alt_sum += ccnumcopy % 10
    ccnumcopy = ccnumcopy // 10
    num_digits += 1

    if ccnumcopy == 0:
        break

    temp = 2 * (ccnumcopy % 10)
    if temp > 9:
        temp = 1 + temp % 10

    mul_sum += temp
    ccnumcopy = ccnumcopy // 10
    num_digits += 1

total_sum = mul_sum + alt_sum

if total_sum % 10 != 0:
    print("INVALID")

else:
    ccnumcopy = ccnumber
    while (ccnumcopy // 10) > 10:
        ccnumcopy = ccnumcopy // 10

    if (ccnumcopy >= 51 and ccnumcopy <= 55) and num_digits == 16:
        print("MASTERCARD")

    elif (ccnumcopy == 34 or ccnumcopy == 37) and num_digits == 15:
        print("AMEX")

    else:
        ccnumcopy = ccnumcopy // 10
        if ccnumcopy == 4 and (num_digits == 13 or num_digits == 16):
            print("VISA")
        else:
            printf("INVALID")