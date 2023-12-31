from cs50 import get_int, get_string

def main():

    cardNumber = get_int("Number: ")

    if valid_card(card):
        card_company(card)
    # Card not valid
    else:
        print("INVALID")


def is_valid_card(num):
    num_str = str(num)[::-1]  # Convert the number to a reversed string

    total = 0

    for i, digit in enumerate(num_str):
        if i % 2 == 0:
            total += int(digit)
        else:
            doubled_digit = int(digit) * 2
            total += sum(int(digit) for digit in str(doubled_digit))

    return total % 10 == 0

def checkCard(card):
    num = int(str(card)[0:2]) # filters out every number except the two first.

    if (num is 34 or num is 37) and len(str(card)) is 15:
        print("AMEX")
    elif num > 50 and num < 56 and len(str(card)) is 16:
        print("MASTERCARD")
    elif num >= 40 and num < 50 and (len(str(card)) is 13 or len(str(card)) is 16):
        print("VISA")
    else:
        print("INVALID")

if __name__ == "__main__":
    main()
