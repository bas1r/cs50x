from sys import argv, exit
import csv


if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# open database and dna sequence text file
with open(argv[1], newline='') as csvFile, open(argv[2], newline='') as txtFile:
    #reader = csv.DictReader(csvfile)
    reader = csv.reader(csvFile)

    # STR List
    strList = next(reader)
    strList.remove('name')

    dna = txtFile.read()

    # count the highest strs in dna sequence store it result
    result = []
    for s in range(len(strList)):
        i = 0
        strCount = 0
        maxStr = 0

        strLen = len(strList[s])
        while i < len(dna):
            if dna[i:i + strLen] == strList[s]:
                i += strLen
                strCount += 1

                if maxStr < strCount:
                    maxStr = strCount

            else:
                i += 1
                strCount = 0

        result.append(maxStr)

    dataset = list(reader)  # list of dataset
    for row in dataset:
        rowcopy = row   # copy each row
        name = rowcopy[0]  # copy of name
        rowcopy.remove(rowcopy[0])  # remove name from copy

        for c in range(len(rowcopy)):   # convert strings to integers
            rowcopy[c] = int(rowcopy[c])

        if result == rowcopy:  # find the match
            print(name)
            exit(1)

    print("No match")