import sys,random
chars = list(filter(lambda x:  x.isalnum(), [ chr(i) for i in range(128) ])) + ['\n']

def main():
    size = int(sys.argv[1])
    s = ""
    for i in range(size):
        s+= ( random.choice(chars) )
    open("large_file.txt","w").write(s)

main()
