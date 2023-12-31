import csv
import sys


def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    with open(sys.argv[1], mode="r") as file_database:
        reader = csv.DictReader(file_database)
        # Goes through each row in reader and creates a new list with in reach objects
        # each item in database is a list[], and in each list is a dict{} from each row
        database = [row for row in reader]

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], mode="r") as file_seq:
        sequence = file_seq.read()

    # TODO: Find longest match of each STR in DNA sequence
    STR_LongestMatches = {}
    for key in database[
        0
    ].keys():  # grab keys from first row in database, same as cvs file.
        if key == "name":  # if key is name, we skip
            continue
        STR_LongestMatches[key] = longest_match(
            sequence, key
        )  # updates the value in STR_LongestMatches in the given key, with the longest run if that STR in the DNA.

    # TODO: Check database for matching profiles
    for row in database:
        match = True  # assume we have a match
        for key in row.keys():  # loop through each attribute for current person
            if key == "name":
                continue  # skip if we hit the "name" key
            # compare STR_LongestMatches for current person against expected str_count
            # STR_LongestMatches is holding the longest match of each STR
            # if it does not match, we set match to falsr and break out
            if int(row[key]) != int(STR_LongestMatches[key]):
                match = False
                break
            # we looped through each row in the database
            # if a match is found, we will trigger the print of that name
            # if not, we continue to the print for no match.
        if match:
            print(row["name"])
            return  # return early if we find a match, otherwise move on to print("No match")

    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


if __name__ == "__main__":
    main()
