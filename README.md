
# CSC 360, March, 2021
## Assignment #3 submission

* Name: `Tim, Rolston`
* VNum: `V00920780`

---

### Description of approach to collecting data for task 2

**In order to achieve average wait and tat collection, I edited `rrsim.c` to not print
anything except for the calculated averages at the end of the program**
 
My approach to collecting average wait and turnaround time data for different 
dispatch and quantum times included the use of 2 python programs I created, `a3data.py`
and `graph.py`, as well as the use of `rrsim.c` and `simgen.c`. I also edited my
implementation to `rrsim.c` in order to calculate and output average wait and
turnaround times everytime the program is called.

#### Contents of `a3data.py`

What I did was within `a3data.py`
a few pre made arrays are created as well as a task number. The task number indicating
how many tasks to perform for every call to `simgen.c` and arrays *quantum* which
carries 4 different "quantum" values, *dispatch* which holds 6 different "dispatch"
values, and *r_seeds* which is an array with 20 randomly generated seeds that vary
between 0 and 920780. It should be noted that these seed values will be different
everytime `a3data.py` is called. `a3data.py` iterates through a 3 tier loop, so 
for each quantum number it will match with each dispatch number and for each dispatch
number  will match with every seed and call the bash command
`./simgen *numOfTasks* *random seed* | ./rrsim --quantum *q_val* --dispatch *d_val* >> average.txt`
this command will call `rrsim.c` which prints the wait and tat averages for every seed
and this will occur for every combination of quantum and dispatch times. The two averages
get stored within a .txt file called `average.txt`. Within each seed iteration `average.txt`
is read and the values are added together, one for wait time and one for turnaround time
and then the text file contents are erased. Within each iteration of dispatch, 2 new 
list are created, each containing wait times and turnaround times for each dispatch time
respectively. These two array will act as a "line" within the graph as it represents 
all the dispatch averages for one quantum time. New arrays will be created and filled
for each quantum time until the loop has finished. At the end of the program a call
to `graph.py` is called to create a graph with the wait averages and the turnaround
averages. 

#### Contents of `graph.py`

**Utilized matplotlib and numpy python libraries**

Within `graph.py` I have a basic set up creation of a graph with a function that will
take in a series of arrays for each line as well as the array of random seeds, number 
of tasks and an indication of the type of graph that is being created. The function then
creates and labels a graph based on the parameters and saves it as a pdf within the 
same directory as the program.