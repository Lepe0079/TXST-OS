def logger(s):
    scrapelog = open("scrapelog.txt", "a")
    scrapelog.write(s)
    scrapelog.close()
    print(s)

hello = "hellow world\n"
logger(hello)

