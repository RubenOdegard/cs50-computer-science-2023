# Expects zero or two command-line arguments:
# Zero if the user would like to output text in a random font.
# Two if the user would like to output text in a specific font, in which case the first of the two should be -f or --font, and the second of the two should be the name of the font.
# Prompts the user for a str of text.
# Outputs that text in the desired font.

import sys
import random

# initiate Figlet
from pyfiglet import Figlet
figlet = Figlet()

# get a list of all available fonts
fonts = figlet.getFonts()

def main():
    args = sys.argv[1:] # exludes file name from arguments

    if len(args) == 0: # if user does not input an argument
        print("Setting font to random font")
        figlet.setFont(font=random.choice(fonts))
    elif len(args) == 2 and (args[0] == "-f" or args[0] == "--font"):
        print("Setting font to custom font")
        if args[1] in fonts:
            figlet.setFont(font=args[1])
        else:
            print("Custom font not found.")
            sys.exit(1)
    else:
        print("Wrong command line arguments.")
        sys.exit(1)

    text = getInput()
    printText(text)

def getInput():
    t = input("Input text: ")
    return t

def printText(text):
    print(figlet.renderText(text))

main()
