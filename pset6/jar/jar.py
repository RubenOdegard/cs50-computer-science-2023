class Jar:
    def __init__(self, capacity=12):
        if not isinstance(capacity, int) or capacity < 0:
            raise ValueError("Capacity cannot be a negative integer.")
        # set the capacity
        self._capacity = capacity
        # set the cookies to 0 at init
        self._cookies = 0

    def __str__(self):
        return "🍪" * self._cookies

    def deposit(self, n):
        ## Raise error if not an int, or negative number.
        if not isinstance(n, int) or n < 0:
            raise ValueError("Deposit amount cannot be a negative integer.")
        # Raise error if the deposit amounts exceeds the capacity of the jar.
        if n + self._cookies > self._capacity:
            raise ValueError("That many cookies can't fit in the jar!")
        else:
            self._cookies = self._cookies + n

    def withdraw(self, n):
        ## Raise error if not an int, or negative number.
        if not isinstance(n, int) or n < 0:
            raise ValueError("Withdraw amount cannot be a negative integer.")
        # Raise error if the withdraw amounts exceeds the amount in the jar.
        if n > self._cookies:
            raise ValueError("You can't withdraw that many! That's more than what's in the jar.")
        else:
            self._cookies = self._cookies - n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._cookies

my_jar = Jar()
print(my_jar)  # Output: ""

my_jar.deposit(3)
print(my_jar)  # Output: "🍪🍪🍪"

my_jar.withdraw(2)
print(my_jar)  # Output: "🍪"

print(my_jar.capacity)  # Output: 12
print(my_jar.size)     # Output: 1
