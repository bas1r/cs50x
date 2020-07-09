import cs50
import sys

# Open database
db = cs50.SQL("sqlite:///students.db")

# Check for number of arguments
if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} <HOUSE>")
    sys.exit(1)

# House name
houseName = sys.argv[1]

# if house in student dataset print student name and date of birth
result = db.execute("SELECT first, middle, last, birth FROM students WHERE house=? ORDER BY last,first", houseName)

for row in result:
    if row["middle"] == None:
        print(row["first"], row["last"], row["birth"])
    else:
        print(row["first"], row["middle"], row["last"], row["birth"])
