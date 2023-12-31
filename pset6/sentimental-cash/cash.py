from cs50 import get_float


def main():
    # get user input in dollars, needs be converted to cents later
    # check if input is a positiv int, if not we reprompt.

    while True:
        try:
            input = get_float("Changed owed: ")
            if input > 0:
                break
            else:
                continue
        except ValueError:
            raise ValueError

    cents = round(input * 100)  # convert dollar to cents

    # // operator floors to the nearest full number
    # % operator gets the remainder after dividing

    # example
    # print("int divison" and 4.5 // 2) - 4.5 / 2 is 2,25, but 4.5 // 2 returns 2.0
    # print("modulo" and 4.5 % 2) - 4.5 % 2 gives the remainder when diving by two, which is 0.5

    quarters = cents // 25
    cents = cents % 25

    # print(f"Quarters: {quarters}")

    dimes = cents // 10
    cents = cents % 10

    # print(f"Dimes: {dimes}")

    nickels = cents // 5
    cents = cents % 5

    # print(f"Nickels: {nickels}")

    pennies = cents

    # print(f"Pennies: {pennies}")

    coins = quarters + dimes + nickels + pennies

    print(coins)


if __name__ == "__main__":
    main()
