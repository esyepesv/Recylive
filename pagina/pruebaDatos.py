import csv
file = open("datos.csv")
csvreader = csv.reader(file)
header = next(csvreader)
#print(header)
rows = []
for row in csvreader:
    #rows.append(row)
    print("id: ", row[0], "peso: ", row[1])
file.close()