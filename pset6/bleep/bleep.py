from sys import argv

def main():
    if len(argv) == 1:
        print("usage bleep.py [dictpath]")
        exit(1)
    banned = "/home/eric/Programming/C/psets/pset6/bleep/" + argv[1]

    print("Enter some text to be censored")
    text = input().split()

    badwords = open(banned, "r").read().splitlines()

    for words in text:
        if words.lower() in badwords:
            text[text.index(words)] = '*' * len(words)
    
    print(' '.join(text))
    

    





if __name__ == "__main__":
    main()
