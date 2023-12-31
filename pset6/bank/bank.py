# project condition
# Take user input:
# if input starts with "hello" output $0
# if input starts with "h" but not hello output $20
# else output $100.

print("Greeting: ")
input = str(input().lower().strip())

if input.startswith("hello"):
    print("$0")
elif input.startswith("h") and input != "hello":
    print("$20")
else:
    print("$100")


