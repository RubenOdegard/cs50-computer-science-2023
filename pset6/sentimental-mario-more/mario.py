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

        print(" " * space, end="")  # prints spaces for left side of pyramid
        print("#" * row, end="")  # prints hashes for left side of pyramid

        print("  ", end="")  # Print two spaces to separate the pyramids

        print("#" * row)  # prints hashes for right side of pyramid


if __name__ == "__main__":
    main()
