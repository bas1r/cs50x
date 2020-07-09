import cs50
import csv
import sys

# Open a students database
db = cs50.SQL("sqlite:///students.db")

# Check number of arguments
if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} <csv file>")
    exit(1)

# Open CSV file
with open(sys.argv[1], "r") as file:

    # Create a DictReader
    reader = csv.DictReader(file)

    # Iterate over CSV file
    for row in reader:

        # Separate first middle last name
        name = row["name"].split()

        # If no middle name
        if len(name) == 2:
            name.insert(1, None)
        name = dict(first=name[0], middle=name[1], last=name[2])
        house = row["house"]
        birth = int(row["birth"])

        # Insert data
        if name["middle"] == None:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, NULL, ?, ?, ?)",
                       name["first"], name["last"], house, birth)
        else:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                       name["first"], name["middle"], name["last"], house, birth)