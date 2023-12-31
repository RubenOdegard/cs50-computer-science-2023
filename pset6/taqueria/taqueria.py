
menu = {
    "Baja Taco": 4.25,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}

# how to access values
# print(menu["Baja Taco"])

    # get user intput
    # if input does not exist in menu{} we repromt (loop + try/catch block)
    # if user inputs ctrl d, we exit.
    # print new total each successful attemt of a new menu item


def main():

    total = 0

    while True:
        try:
            item = input("Item: ") # get input from user
        except EOFError: # if user presses "ctrl + d" we break out of loop
            exit(0)
        try:
            item_price = menu[item.title()] # check item price from input, set item from input to title case to match menu set.
            total += item_price # add the price of current item to total
            print(f"Total: ${total:.2f}") # print new total with two decimals pr the instructions
        except KeyError:
            print("Item not found in the menu.") # if not found, print error.

if __name__ == "__main__":
    main()
