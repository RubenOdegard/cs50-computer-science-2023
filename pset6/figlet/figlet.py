# Expects zero or two command-line arguments:
# Zero if the user would like to output text in a random font.
# Two if the user would like to output text in a specific font, in which case the first of the two should be -f or --font, and the second of the two should be the name of the font.
# Prompts the user for a str of text.
# Outputs that text in the desired font.

# argparse to go through command line arguments
import argparse
# random to generate random fonts
import random
# sys to exit
import sys

# import and initiate Figlet
from pyfiglet import Figlet
figlet = Figlet()

# get a list of available fonts
fonts = figlet.getFonts()

def main():
    parser = argparse.ArgumentParser(description="Output text in a specific or random font with Figlet.")
    parser.add_argument("-f", "--font", help="Specify a font", type=str)
    # parse the arguments and save to a variable
    args = parser.parse_args()

    if args.font:
        if args.font in fonts:
            figlet.setFont(font=args.font)
        else:
            print("Font not found.")
            sys.exit(1)
    else:
        figlet.setFont(font=random.choice(fonts))

    # promt user for text
    text = getUserText()
    printText(text)

##################################

def getUserText():
    t = input("Input text: ")
    return t

def printText(text):
    print(figlet.renderText(text))

if __name__ == "__main__":
    main()
