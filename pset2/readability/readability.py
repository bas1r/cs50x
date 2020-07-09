from cs50 import get_string
import string


def main():
    getText = text()

    # print(f"{letterCount(getText)} letters")
    # print(f"{wordCount(getText)} words")
    print(f"{sntsCount(getText)} sentences")

    grade = gradeIndex(letterCount(getText), wordCount(getText), sntsCount(getText))

    if grade < 16 and grade >= 0:
        print(f"Grade {int(grade)}")
    elif grade >= 16:
        print("Grade 16+")
    elif grade < 0:
        print("Before Grade 1")


def text():  # prompt user to text input
    while True:
        getText = get_string("Text: ")
        if len(getText) > 0: break
    return getText


def letterCount(text):  # returns total number of letters
    return len([letter for letter in text if letter.isalpha()])


def wordCount(text):  # count words
    return len(text.split())


def sntsCount(text):  # count sentences
   # counter = 0
  #  for c in text:
  #      if c in ['.', '!', '?']:
  #          counter += 1
   # return counter
    return len([snts for snts in text if snts in ['.', '!', '?']])


# The Coleman-Liau index of a text is designed to output what (U.S.) grade level is needed to understand the text.
# The formula is: index = 0.0588 * L - 0.296 * S - 15.8  Here, L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.


def gradeIndex(letters, words, sentences):

    letters = 100 * letters / words
    sentences = 100 * sentences / words
    #print(f"letter: {letters} sentences: {sentences}")

    return round(0.0588 * letters - 0.296 * sentences - 15.8)


main()