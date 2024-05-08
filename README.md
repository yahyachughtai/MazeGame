# MazeGame
A C++ console based maze game

Introduction
Welcome to our maze-solving game! The aim is simple: navigate through mazes,
Dodge obstacles, and collect rewards for the highest score. The maze map is crafted using
graphs. You’ve got different ways to play the game. Use your skills to navigate manually or let
the game find the best path for you using Dijkstra”s and Prim's algorithms. You can even create
your own maze!

Classes

BinaryHeap
setSize
Parameters: an int size
Return Type: void
Explanation: This function initializes the binary heap array with this size

Insert
Parameters: a var of Game data type
Return Type: void
Explanation: This function adds the game to the last empty index of the array and the checks
to make sure that the property on the binary heap tree has not been violated.

Check
Parameters: an int
Return Type: void
Explanation: this function starts checking to make sure that the property on the binary heap
tree has not been violated from the variable passed as a parameter.

Deletion
Parameters: none
Return Type: void
Explanation: this function removes the element from index 1 of the array and replaces it with
the last game in the array and then checks to make sure that the property on the binary heap
tree has not been violated.

Swap
Parameters: 2 indexes (int)
Return Type: void
Explanation: this function switches the values of the two indexes passed as parameter.

Print
Parameters: none
Return Type: void
Explanation: this function recursively prints the game at the index 1, then stores it in a
temporary variable then recursively calls itself. This happens until the array is empty, then it calls
the insert function to insert them back into the array one by one.

Search
Parameters: string name
Return Type: int
Explanation: this function finds the game which was played by the player whose name has
been passed as a parameter. If found it returns its index else returns -1.

Color
displayCentered
Parameters: none
Return Type: void
Explanation: a

Difficulty

setDifficulty
Parameters: string difficulty
Return Type: void
Explanation: This function sets the difficulty level that is passed as a parameter. There are 3
levels:easy, medium and hard. Each one determines the maze's size, the percentage of nodes
in the maze that are going to be empty, obstacle,coin, trophy and power. Furthermore, it also
determines the rate of a connection that a node will be connected to.

Info
Parameters: none
Return Type: void
Explanation: This function prints the maze's difficulty and its size.

Game
Print
Parameters: none
Return Type: void
Explanation: This function prints the name of the player, their final score, time taken to
complete the game, and number of moves/hops they did.

Graph
initilizeMazeSize
Parameters: length and width (int)
Return Type: void
Explanation: This function initializes the length and width of the graph and creates a
adjacencyList of length * width size.

initilizeAllNodes
Parameters: none
Return Type: void
Explanation: This function contains a loop that runs n times (n is the number of nodes in the
maze = length * width). Every time it runs it generates a random number between 1-100 and
then uses the rate of each node type to insert a random node into a queue such as
obstacles,power ups etc along with a unique index.

generateMaze
Parameters: none
Return Type: void
Explanation: This function contains a for loop that starts counting the number of connections of
each node (starting from the first all the way to the last). To count the number of connections it
calculates the size of the adjacencyList of that nodes index. If any node has less than two
connections it calls the populate function to add more connections. The reason why each node
should have 2 connections is to avoid any islands from forming in the maze that is going to be
generated.

generateMazeUsingDijkstraAlgorithm
Parameters: none
Return Type: void
Explanation: This fusion calls the following to functions in an order:
● generateInitialMaze
● generateMazeWithDijkstraAlgorithm

generateInitialMaze
Parameters: none
Return Type: void
Explanation: This function does the same thing as the generateMaze function except it’s
condition is that each node should has minion 1 connection.

generateMazeWithDijkstraAlgorithm
Parameters: none
Return Type: void
Explanation: This function first calls the dijkstraAlgorithm function. This function populates the
parent of each node from the starting node because of this function all nodes except the start
node and nodes that don't have a connection (direct or indirect) with the start node will have
their parent as null. This means that these nodes are islands. This function then runs a while
loop and goes to each node and if they have their parent as null i.e are islands (except the
starting node) then it calls the populate function and creates its connection randomly. Then it
recursively calls itself to recheck if now all nodes are connected.

populate
Parameters: 2 indexes (int)
Return Type: void
Explanation: This function first checks if this function can have a right connection (i.e is not the
right most node in the maze) and checks if the node is already connected to the node on its
right to avoid double connections. If the node can have a right connection and is unconnected to
the node on its right then it generates a random number between 1-10. If the random number is
less than the connection rate set by the difficulty of the game then it adds the right node to the
current node's adjacencyList and adds the current node to the right node's adjacencyList (since
this is an undirected graph). This process is then repeated for the left, bottom and top nodes as
well respectively.

printMaze
Parameters: none
Return Type: void
Explanation: This function uses the queue of all nodes to first print the node’s type i.e # for
obstacles and $ for coins. (it also checks what kind of node it is to print it with a different color
so the user can easily differentiate between different types of nodes).
Additionally if a non obstacle node was already visited then it prints and displays it the same as
an empty node (“O”) to convey to the user that they have already traversed from here.
After this the function checks if the current node is connected to the node on its right, if so print
“----” else empty spaces (the color of the path is changed if the current node and the node on its
right are both visited).
Next it checks if the current node was the last node in its row. If so it reinitializes it to the node to
the node at the start of the row and begins to check for vertical connections (only if the node is
not the node at the bottom of the maze). If the node is connect to the one below it, it prints (“|”)
else spaces. Then when it reaches the end it initializes it with the first node of the next row.

printMazeIndexes
Parameters: 4 bools: top, right, bottom and left
Return Type: void
Explanation: This function does the same thing as the printMaze except it prints the indexes of
the nodes. If the node is the top most node and top bool is true it prints it with the color green
else red. Same goes for bottom, right and left respectively. All other nodes i.e center nodes are
printed with the default color (white).

printMazeInfo
Parameters: none
Return Type: void
Explanation: This function calls the difficulty class’s info function. Then prints the mazes key i.e
what is an obstacle, path etc. and finally the current points the user has.

defaultMazeStartAndEnd
Parameters: none
Return Type: void
Explanation: This function initializes the starting point as the top left most node (i.e node with
the index = 1) and the end as the bottom rightmost node (i.e node with index = length * width)

customMazeStartAndEnd
Parameters: start and end (int)
Return Type: void
Explanation: This function initializes the starting point as the node with index start and ending
node with the node of index end.

undoMazeStartAndEnd
Parameters: none
Return Type: void
Explanation: This reverts the actions of the above to functions by reinitializing the start and end
to their original nodes.

primAlogorithum
Parameters: none
Return Type: void
Explanation: This function applies the prim algorithm to set the parents of the nodes for the
shortest path. First it locates the destination node. Then enqueues all the nodes in a priority
queue. Then it takes out the destination node and then sends the nodes it is connected to as
visited and updates their parent to itself.
Next it runs a while loop until the priority queue is empty. The loop first dequeues the node with
the most benefit. Then updates its neighboring nodes are not visited as visited and sets their
parent as itself. Once the loop breaks it calls the resetVisited function.

resetVisited
Parameters: none
Return Type: void
Explanation: this function sets all nodes’ visited bool as false so that this bool can be used later
on for other reasons.

autoNavigateUsingPrimAlogorithum
Parameters: none
Return Type: void
Explanation: this function first calls the primAlogorithum function. Then it locates the ending
and starting nodes. It sets the start node’s current bool to true(this bool is used to locate where
the player/car is at). It runs this loop until the end node’s current is true i.e the car has reached
the end. The current node’s visited is set to true, cost to 0, and current is set to false. Then the
score is added which is the cost of the next node(the next node is also inserted into its linkedlist
for final calculations. The current node is set to the next node. During this function every they
the node updates the terminal is cleared and the maze is printed again. When the loop breaks
the result function is called.

dijkstraAlgorithm
Parameters: none
Return Type: NodeQueue<NodeType>*
Explanation: This function locates the start node, sets its visited to true, parent to null and key
to 0. Then enqueues it into a priority queue. Then a while loop is called until the queue is empty.
In the loop the node with the most benefit (key) is dequeued and its neighbors that aren't visited
their key are updated if the new key value is higher than the current one and so is their parent.
After this these neighbors are enqueued.
When the loop breaks resetVisited is called. In a queue called bestPath the end node is
enqueued at the front. Then a loop runs until the node at the front has no parent (which will be
the starting node) In the loop the front element's parent is then enqueued at the front.
Lastly the start of this queue is returned.

autoNavigateUsingDijkstraAlgorithm
Parameters: none
Return Type: void
Explanation: this function first calls the dijkstraAlgorithm function and stores its return type in a
pointer. Then it sets the current node at the start of the queue. It sets the start node’s current
bool to true(this bool is used to locate where the player/car is at). It runs this loop until the
current nodes reache sthe end. The current node’s visited is set to true, cost to 0, and current is
set to false. Then the score is added which is the cost of the next node(the next node is also
inserted into its linkedlist for final calculations. The current node is set to the next node. During
this function every time the node updates the terminal is cleared and the maze is printed again.
When the loop breaks the result function is called.

Result
Parameters: none
Return Type: void
Explanation: This function prints the result i.e the number of power ups collected, the time
taken etc and then the final score is displayed. Additionally if this score is greater than the is the
file then previous highest and the new highest score is displayed.

getHighest
Parameters: name and key (both string)
Return Type: Game
Explanation: This function reads the score file locate the game of the user (name) and of the
difficulty (key) with the highest score and returns it.

breakString
Parameters: original (string) & key (int)
Return Type: string
Explanation: This function returns the text from the original that is right before the key th
comma.

saveResult
Parameters: none
Return Type: void
Explanation: this function save the game date into the score file.

isNextNodeConnected
Parameters: currentNodeIndex, nextNodeIndex (both integer)
Return Type: bool
Explanation: This function checks whether there is a connection between the current node and
the next node in a maze. It takes the indices of the current and next nodes as parameters. It
begins by iterating through the list of all nodes to find the current node. If the current node is not
found, an error message is displayed, and the function returns false. Assuming the current node
is located, the function then checks if the next node is present in the adjacency list of the current
node. The adjacency list stores connections between nodes in the graph. If a connection is
found, the function returns true, indicating that the nodes are connected. If no connection is
found, it returns false. This function determines whether a valid path exists between two nodes
in the maze.

manualnavigate
Parameters: bool savedGame = false, bool custom = false
Return Type: bool
Explanation: This function initiates by determining the starting and ending nodes in the maze. It
then identifies the current node for the player, whether in a saved or new game. After clearing
the console, it prints maze information, displays instructions, and starts tracking time. The game
loop awaits user input for maze navigation, checking for the 'R' key to save the game if
applicable. It updates the player's position, game score, and checks for completion. Upon
reaching the end, the console is cleared, and final game details, including time taken and
results, are displayed. The function returns true if the game was saved during play.

LeaderBoard
leaderBoardMenu
Parameters: none
Return Type: void
Explanation: This function displays the options to the user:
1. Personal Leader Board
2. Globle Leader Board
Then it displays which difficulty. Based on this it calls the following two functions. Then calls the
print function of each game.

setPersonalLeaderBoard
Parameters: string difficulty
Return Type: void
Explanation: This function reads the score file and extracts all the games that were played by
the user (who is logged in), of the difficulty passed as parameter. Each game is stored in a heap
of size 10 and once the heap is full it starts replacing the game at the bottom with the new one
read from file if its score was higher. As a result only the top ten games of the user are
displayed.

setGolbleLeaderBoard
Parameters: string difficulty
Return Type: void
Explanation: This function reads the score file and extracts all the games of the difficulty
passed as parameter. Each game is stored in a heap of size 100. Each player has only one
game added to the heap to ensure only the top 100 players are shown. If a player already has
his game added into the heap then it calls the search function and replaces it with the new one
read from file if the new one’s score is higher.

globleMenu
Parameters: none
Return Type: void
Explanation: This function displays which difficulty. Based on this it calls the
setGolbleLeaderBoard function. Then calls the print function of each game.

Menu
setGameMode
Parameters: difficulty (string)
Return Type: void
Explanation: This function is responsible for allowing the user to choose between different
game modes. It first prompts the user to select between manual and automatic navigation
modes. For the manual mode, the user is further given the option to choose default or custom
start and end points in the maze. If the user selects automatic navigation, they can opt for either
Prim's or Dijkstra's algorithm for maze-solving. Once the choices are made, it creates an
instance of the Graph class, initializes maze parameters, and generates the maze accordingly.
Depending on the selected options, it then initiates manual navigation with the ability to save the
game or automatic navigation using Prim's or Dijkstra's algorithm. The last game is stored in a
stack for reference.

signupMenu
Parameters: none
Return Type: void
Explanation: This function presents a user interface for interacting with the maze-solving and
gaming application. It displays a menu allowing the user to choose various options:
1. Play saved game: If a saved game exists, it loads the top saved game from the stack
and allows the user to resume manual navigation. The game is removed from the stack
after playing, and the user can save it again.
2. Play new game: The user is prompted to choose a difficulty level and then the function
proceeds to the setGameMode function, initiating the maze creation and navigation
process.
3. Play custom game: Points to the custom function, allowing the user to customize maze
parameters such as width, length, and difficulty.
4. Leaderboard: Redirects to the LeaderBoard class, where the user can view the global
leaderboard or their own performance if logged in.
5. Help: Redirects to the help function, providing information and guidance on how to play
the game.
6. Logout: Logs the user out, clearing their username and password, and returns to the
main menu.

Menu
Parameters: none
Return Type: void
Explanation: This function serves as the main menu of the maze-solving game application.
1. Sign up : If the user chooses to sign up, the signUp function of the user object is called.
If the signup is successful, it clears the screen, introduces a delay for visual effect using
Sleep(700), clears the screen again, and then calls the SignupMenu function.
2. Login : If the user chooses to log in, the login function of the user object is called. If the
login is successful, it follows a similar process as the signup option—clear screen, delay,
clear screen, and then call SignupMenu.
3. Guest mode : If the user chooses the guest mode, it directly calls the SignupMenu
function without requiring signup or login.
4. Exit : If the user chooses to exit, the program terminates (exit(0)).

Help
Parameters: none
Return Type: void
Explanation: This function displays an interactive help menu, allowing the user to choose
between different topics like understanding the game, game modes, score calculation, or exiting
the help menu. Each option provides information about the chosen topic.

Custom
Parameters: none
Return Type: void
Explanation: This function asks the user to enter the size of the maze (maze size can only be
from 2-15 to prevent the user from creating a game that cannot fit within the terminal display).
Then this function asks the user to select with difficulty they want, easy, medium or hard. Then it
calls the following functions:
● setDifficulty
● initilizeMazeSize
● initilizeAllNodes
● generateMaze
After which it asks the user to custom select their start and end points. After which it calls the
following functions:
● customMazeStartAndEnd
● printMaze
● manualnavigate
