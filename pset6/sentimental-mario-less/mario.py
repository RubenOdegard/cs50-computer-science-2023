def main():
    while True:
        try:
            height = int(input("Height: "))
            if 1 <= height <= 8:
                break
            else:
                print("Please enter a number between 1 and 8.")
        except ValueError:
            print("Not a number.")

    for row in range(1, height + 1):
        space = height - row

        print(" " * space, end="")
        print("#" * row)


if __name__ == "__main__":
    main()
