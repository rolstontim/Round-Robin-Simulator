#Tim Rolston
#V00920780

#Data creation for csc360 assignment#3

from numpy.random import seed
from numpy.random import randint
from graph import graph_plot
import sys
import itertools
import subprocess
import difflib
import re
import os
import matplotlib.pyplot as plt

def main():

    quantum = [50, 100, 250, 500]
    dispatch = [0, 5, 10 ,15, 20, 25]
    #seed(1)
    r_seeds = randint(0, 920780, 20)
    tasks = 1000

    wait_50 = []
    wait_100 = []
    wait_250 = []
    wait_500 = []
    tat_50 = []
    tat_100 = []
    tat_250 = []
    tat_500 = []

    index = 0
    new_list = 0

    for x in quantum:
        new_list += 1

        for y in dispatch:
            for z in r_seeds:
                #print("changing seed...")
                os.system( f"./simgen {str(tasks)} {str(z)} | ./rrsim --quantum {str(x)} --dispatch {str(y)} >> average.txt")

                f = open("average.txt", "r")
                lines = f.readlines()
                wait_vals = []
                tat_vals = []
                wait_average = 0
                tat_average = 0
                temp = 0
                for i in lines:
                    wait_vals.append(i.split(",")[0])
                    wait_average += int(wait_vals[temp])
                    tat_vals.append(i.split(",")[1])
                    tat_average += int(tat_vals[temp])

                f.close()
                f = open("average.txt", "w")
                f.close()

            if new_list == 1:
                wait_50.append(wait_average)
                tat_50.append(tat_average)
            if new_list == 2:
                wait_100.append(wait_average)
                tat_100.append(tat_average)
            if new_list == 3:
                wait_250.append(wait_average)
                tat_250.append(tat_average)
            if new_list == 4:
                wait_500.append(wait_average)
                tat_500.append(tat_average)

            index += 1
    graph_plot(wait_50, wait_100, wait_250, wait_500, r_seeds, tasks, "wait")
    graph_plot(tat_50, tat_100, tat_250, tat_500, r_seeds, tasks, "tat")


if __name__=='__main__':
	main()
