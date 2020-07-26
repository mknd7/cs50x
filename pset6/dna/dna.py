import sys
import csv

if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    sys.exit(1)

csv_file = open(sys.argv[1])
dna_database = csv.DictReader(csv_file)

str_keys = dna_database.fieldnames[1:]

txt_file = open(sys.argv[2], 'r')
dna_sequence = txt_file.read()

# Find STRs in DNA sequence and store counts
counts = {}
name = ''


for strp in str_keys:
    index = dna_sequence.find(strp)
    if index == -1:
        counts[strp] = 0
        continue

    high_count = 0
    while True:

        count = 1
        # find consecutive sequence
        while dna_sequence.find(strp, index + len(strp), index + 2 * len(strp)) != -1:
            index = dna_sequence.find(strp, index + len(strp), index + 2 * len(strp))
            count += 1

        high_count = count if count > high_count else high_count
        index = dna_sequence.find(strp, index + len(strp))
        if index == -1:
            break

    counts[strp] = high_count


for person in dna_database:
    name = person.pop('name')
    match = True

    for strp in person:
        if counts[strp] != int(person[strp]):
            match = False
            break

    if match == True:
        break


if match == True:
    print(name)
else:
    print("No match")

csv_file.close()