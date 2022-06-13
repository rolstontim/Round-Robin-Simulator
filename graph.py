#Tim Rolston #V00920780
#Data graph creation

import matplotlib
matplotlib.use('Agg')

import matplotlib.pyplot as plt
import numpy as np

def graph_plot(q_50, q_100, q_250, q_500, seeds, tasks, type):

        plt.clf()
        plt.rcParams["axes.titlesize"] = 8
        x = [0, 5, 10, 15, 20, 25]
        plt.margins(x = 0)

        plt.plot(x, q_50, label='q = 50')
        plt.plot(x, q_100, label='q = 100')
        plt.plot(x, q_250, label='q = 250')
        plt.plot(x, q_500, label='q = 500')
        plt.xlabel('Dispatch overhead')

        if type == "wait":
            plt.ylabel('Average waiting time')
        if type == "tat":
            plt.ylabel('Average turnaround time')

        axes = plt.gca()
        axes.xaxis.label.set_size(8)
        axes.yaxis.label.set_size(8)

        plt.title(f'Round Robin Scheduler -- #tasks: {tasks};\n seed values: {seeds}' )
        plt.legend()

        if type == "wait":
            plt.savefig('graph_waiting.pdf')
        if type == "tat":
            plt.savefig("graph_turnaround.pdf")
