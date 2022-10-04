import unicodedata

names = []
for c in range(0,0x10FFF + 1):
    try:
        names.append(unicodedata.name(chr(c)).lower() + " " + chr(c))
    except ValueError:
        pass

with open("~/.unicode.txt", "w") as fd:
    fd.write("\n".join(names))

