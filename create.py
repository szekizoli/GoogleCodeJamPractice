#!/usr/local/bin/python3

from argparse import ArgumentParser
from argparse import ArgumentTypeError
import itertools
import os
import string
from shutil import copyfile
import pathlib

def validateProblemCount(value):
	ivalue = int(value)
	if ivalue < 1 or ivalue > 25:
		raise ArgumentTypeError(str(value) + " is not within range [1, 25]")
	return ivalue

parser = ArgumentParser()
parser.add_argument("-y", "--year", dest="year", required=True,
                    help="the year of the problem set", type=int)
parser.add_argument("-r", "--round", dest="round", required=True,
                    help="the round of the problem set, e.g. 1B", type=str)
parser.add_argument("-c", "--count", dest="count", default=3,
                    help="the number of problems in the round", type=validateProblemCount)


args = parser.parse_args()

dir = str(args.year) + "_Round_" + args.round + "/"
print(dir)
pathlib.Path(dir).mkdir(parents=True, exist_ok=True) 

with open('./template.cpp', 'r') as original: data = original.read()
alphabet = list(string.ascii_lowercase)

build_cmd = "#!/bin/sh\nclang++ -g --std=c++14 -o "

print(args.count)
for char in itertools.islice(alphabet, 0, args.count):
	with open(dir + char + ".cpp", 'w') as modified: modified.write("// " + str(args.year) + " Round " + args.round  + " Problem " + str(char).upper() + "\n" + data)
	with open(dir + "build-" +  char + ".sh", 'w') as build_file: build_file.write(build_cmd + char + ".out " + char + ".cpp")

