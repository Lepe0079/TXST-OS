#Dan Lepe
#10/12/2020
#Theory of Automata Mini Programming Assignment
#Byron Gao CS3378

def logger(s):
    scrapelog = open("scrapelog.txt", "w")
    scrapelog.write(s)
    scrapelog.close()
    print(s)


from urllib.request import urlopen
import re

#test inputs
url = "https://cs.txstate.edu/accounts/profiles/jg66/"
#url = "https://cs.txstate.edu/accounts/profiles/ma04/"
#url = "https://cs.txstate.edu/accounts/profiles/xc10/"

#read page and turn to text
page = urlopen(url)
html_bytes = page.read()
webpageText = html_bytes.decode("utf-8")

#different regex to search for the data
name = re.search(r"(?:\balt=\")(.*)(email\b)", webpageText).group(1)
education = re.search(r"(?:<p>)(.*PhD.*University)", webpageText).group(1)
research = re.search(r"(:?Interests.*?p>)(.*?)(:?</p>)", webpageText, flags=re.S).group(2)
office = re.search(r"(?:Office Location.*?p>)(.*?)(:?</p>)", webpageText, flags=re.S).group(1)
webPage = re.search(r"(?:href=\")(.*)(\">Homepage)", webpageText).group(1)

#make it into a string and put it in the log
data = "Name: " + name + "\nEducation: " + education + "\nResearch Interests: " + research + "\nOffice: " + office + "\nWebpage: " + webPage
logger(data)
