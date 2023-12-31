def main():
    text = input("Text: ")

    letters = calc_letters(text)
    words = calc_words(text)
    sentences = calc_sentences(text)

    averageLetters = letters / words * 100.0
    averageSentence = sentences / words * 100.0

    index = Cl_Index(averageLetters, averageSentence)

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")


# Coleman-Liau formula
def Cl_Index(L, S):
    index = 0.0588 * L - 0.296 * S - 15.8
    return index


def calc_letters(text):
    length = len(text)
    count = 0

    for i in range(length):
        if (text[i]).isalpha():
            count += 1
    return count


def calc_words(text):
    length = len(text)
    count = 0
    isInsideWord = False

    for i in range(length):
        if text[i].isspace():
            isInsideWord = False
        else:
            if not isInsideWord:
                isInsideWord = True
                count += 1

    return count


def calc_sentences(text):
    length = len(text)
    count = 0
    isInsideSentence = False

    for i in range(length):
        current = text[i]
        if current == "." or current == "!" or current == "?":
            isInsideSentence = False
            count += 1
        else:
            if not isInsideSentence and current.isalpha():
                isInsideSentence = True

    return count


if __name__ == "__main__":
    main()
