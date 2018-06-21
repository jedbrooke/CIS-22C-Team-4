from os import listdir
import os as os
from os import walk

files = []

mypath = os.path.realpath(__file__)
mypath = mypath.split("/")
mypath.remove(mypath[-1])
mypath = "/".join(mypath)

outputFile = open("Run.cpp","w")

for (dirpath, dirnames, filenames) in walk(mypath):
	files.extend(filenames)
	break

for i in reversed(range(len(files))):
	if files[i][0] == "." or len(files[i].split(".")) < 2:
		files.remove(files[i])

	if files[i].split(".")[1] != "h" and files[i].split(".")[1] != "cpp":
		files.remove(files[i])

	if "test" in files[i].lower() or "driver" in files[i].lower():
		files.remove(files[i])

headers = [file for file in files if file.split(".")[1] == "h"]
sources = [file for file in files if file.split(".")[1] == "cpp"]


headers.insert(0,headers.pop(headers.index("Product.h")))
headers.insert(1,headers.pop(headers.index("ProductS.h")))
headers.insert(2,headers.pop(headers.index("User.h")))
headers.insert(3,headers.pop(headers.index("List.h")))
headers.insert(4,headers.pop(headers.index("SubOrder.h")))



headers.extend(sources)

files = headers


for fileName in files:
	if fileName == "Run.cpp":
		continue
	file = open(fileName,encoding="UTF-8")

	for line in file:
		if not "#include \"" in line and not line == "\n":
			outputFile.write(line)

	outputFile.write("\n")

	file.close()

outputFile.flush()
outputFile.close()
