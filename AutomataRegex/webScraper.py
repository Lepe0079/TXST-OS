def logger(s):
    scrapelog = open("scrapelog.txt", "a")
    scrapelog.write(s)
    scrapelog.close()
    print(s)


from urllib.request import urlopen
import re

url = "https://faculty.txstate.edu/profile/1921720"
page = urlopen(url)

html_bytes = page.read()
html = html_bytes.decode("utf-8")

clean = re.sub('<.*?>', '',html)

print(clean)