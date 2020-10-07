import cs50
import sys

if len(sys.argv) != 2:
    print("Usage: python roster.py [house]")
    sys.exit(1)

house = sys.argv[1]
db = cs50.SQL("sqlite:///students.db")

db_read = db.execute("SELECT first, middle, last, birth from students WHERE house=? ORDER BY last, first;", house)
for row in db_read:
    firstName = row['first']
    middleName = row['middle'] or ''
    lastName = row['last']
    birth = row['birth']

    print(firstName, end=' ')
    if middleName:
        print(middleName, end=' ')
    print(f"{lastName}, born {birth}")