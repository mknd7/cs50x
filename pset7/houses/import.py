import cs50
import sys
import csv

if len(sys.argv) != 2:
    print("Usage: python import.py data.csv")
    sys.exit(1)

csv_file = sys.argv[1]
open("students.db", "w").close()
db = cs50.SQL("sqlite:///students.db")
db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC);")

with open(csv_file, "r") as chars:
    reader = csv.DictReader(chars)

    for row in reader:
        names = row['name'].split()
        firstName = names[0]

        if len(names) > 2:
            middleName = names[1]
            lastName = names[2]
        else:
            middleName = None
            lastName = names[1]

        house = row['house']
        birth = row['birth']

        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?);",
        firstName, middleName, lastName, house, birth)

