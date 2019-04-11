from sys import argv

if len(argv) != 2 or not argv[1].isalpha():
    print("Usage vigenere.py [keyword]")
    exit(1)
key = [ord(i) - 97 for i in argv[1].lower()]
index = len(key)
print(key)

print("Enter plaintext")
ptext = list(input())

count = 0
for i, j in enumerate(ptext):
    if j != ' ' and j.isalpha():
        if j.islower():
            l = 97
        else:
            l = 65
        ptext[i] = chr((ord(j) - l + key[count%index]) % 26 + l)
        count += 1

print(''.join(ptext)) 
    





