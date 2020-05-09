from cs50 import get_string

text = get_string("Text: ")
letters, words, sentences = 0, 0, 0

for letter in text:
    if letter.isalpha():
        letters += 1
    elif letter == ' ':
        words += 1
    elif letter == '.' or letter == '?' or letter == '!':
        sentences += 1

if len(text) > 2:
    words += 1

avgLettersPercent = letters / words * 100
avgSentencesPercent = sentences / words * 100
clIndex = round(0.0588 * avgLettersPercent - 0.296 * avgSentencesPercent - 15.8)

if clIndex > 16:
    print("Grade 16+")
elif clIndex < 1:
    print("Before Grade 1")
else:
    print(f"Grade {clIndex}")