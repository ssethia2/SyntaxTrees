"""A Python script that uses Flask to receive HTTP requests, and processes the
request body. It accepts a sentence, splits it and tags it using the NLTK
library. Then it calls the syntax tree module to construct a syntax tree for the
sentence. Finally, it sends a response back to the client with the tree so that
it can be displayed on the browser.

Author: Satvik Sethia
Date: 09/19/2019
"""

from flask import Flask, escape, request
import nltk
import sys
import requests

app = Flask(__name__)

class Node:


def split(sentence):
  tokens = sentence.split()

  nltk_tagged = nltk.pos_tag(tokens)
  words = []
  tags = []

  for i in range(0, len(nltk_tagged)):
    tag = ""

    if 'NN' in nltk_tagged[i][1] or nltk_tagged[i][1] == 'PRP':
      tag = 'N'
    elif 'JJ' in nltk_tagged[i][1] or nltk_tagged[i][1] == 'PRP$':
      tag = 'Adj'
    elif "DT" in nltk_tagged[i][1] and i == len(nltk_tagged) - 1:
      tag = 'N'
    elif nltk_tagged[i][1] == 'MD' or 'RB' in nltk_tagged[i][1]:
      tag = 'Adv'
    elif nltk_tagged[i][1] == 'RP' or nltk_tagged[i][1] == 'TO':
      tag = 'PP'
    elif 'VB' in nltk_tagged[i][1]:
      tag = 'V'
    elif 'DT' in nltk_tagged[i][1]:
      tag = 'D'

    tags.append(tag)
    words.append(nltk_tagged[i][0])

  print(words, tags)

  return words, tags


@app.route('/', methods=['POST'])
def process():
  try:
    words, tags = split(request.form['sentence'])

    # Call c++ object file/exe



  except Exception as e:
    pass

if __name__ == "__main__":
  split(sys.argv[1])
