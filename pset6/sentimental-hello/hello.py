def main():
    name = input("What is your name?\n")
    if len(name) != 0:
        print(f"hello, {name}")
    else:
        print("Hello there.")


if __name__ == "__main__":
    main()
