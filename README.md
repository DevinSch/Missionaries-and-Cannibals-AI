# Missionaries and Cannibals AI
 CPSC 3615 Artificial Intelligence. Assignment 1 (question 4)

 To compile use the command 'make' or 'make problem1'


 • Formulate the problem precisely in terms of search, making only those distinctions
 necessary to ensure a valid solution. What is the best representation (abstraction) of
 a state?

STATES: any number of missionaries and cannibals on each side of the river (3! * 3!) * (3! * 3!) 
INITIAL STATE: All six people are yet to cross the river
ACTIONS: any one or two people take the boat across the river (boat cannot move while empty so one or more may have to return to the start to gather the others)
TRANSITION MODEL: 
GOAL STATE: All six people are across the river
ACTION COST: 1 

- I found the best representation of each state was based on the populations on each side of the river after people use the boat. Both sides of the river need to be checked to ensure the missionaries are never outnumbered.

 • Implement and solve the problem optimally using an appropriate search algorithm.
 Is it a good idea to check for repeated states?

- While checking for repeated states can be a good idea, and can help prevent duplicating the same wok, I did not find it necessary in this case as the state space is relatively small when preforming BFS. If I had used DFS it may have been more important as there are many ways to get to similar states.

 • Why do you think people have a hard time solving this puzzle, given that the state
 space is so simple?

 - I think people have a hard time with this people because of the amount of objects. which at the start doesn't seem like much. But after a few moves can be harder to keep track off. This type of object tracking is simple for the computer and can be done very quickly.![image](https://user-images.githubusercontent.com/61724378/152275475-00edb8ac-a576-47b1-9da6-0a523f3b739d.png)
