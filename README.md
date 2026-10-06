# DSA_C_Project-2_-Assignment

## Question 1(3pts): Airport Baggage Handling Priority Queue

At an international airport, an automated baggage handling system assigns a priority score to baggage containers based on factors such as connecting-flight departure time, passenger priority, and handling requirements.

The system must always process the container with the highest priority score first. An array-based Max-Heap is used to efficiently manage the containers.

The following priority scores have been received:

P = {56, 23, 91, 34, 72, 48, 85, 17, 63, 79, 42}

### Tasks

#### 1. Build the Max-Heap

Construct the initial binary tree from the given array and convert it into a valid Max-Heap.

Assign each baggage container a unique identifier using uppercase letters: A, B, C, D, ...

Each heap element must contain:

Container ID
Priority Score
Clearly show the resulting heap.

#### 2. Urgent Baggage Container

A new container X arrives with a priority score of 100.

Insert container X into the Max-Heap.
Apply the appropriate heapify operation.
Show the resulting heap after insertion.
Ensure that the container ID remains associated with priority 100.

#### 3. Cancelled Container
Container X is subsequently removed from the processing queue.

Remove container X from the heap.
Restore the Max-Heap property using the appropriate heapify operation.
Show the resulting heap.
Ensure that the remaining container IDs remain correctly associated with their priority scores.

#### Constraints
The solution must be implemented in C.
Use an array-based binary heap.
Maintain both the container ID and priority score during swaps.
Demonstrate appropriate heapify operations during insertion and deletion.
Clearly show the heap after:
Initial Max-Heap construction
Insertion of container X
Removal of container X

## Question 2 (4pts): Hospital Emergency Triage Priority System
A hospital emergency department receives patients continuously. Each patient is assigned a triage priority score by the medical triage system. Patients with higher scores must be attended to before patients with lower scores.

The hospital uses an array-based Max-Heap to manage the emergency queue.

Each patient record contains:

Patient ID
Patient name
Triage priority score
The following patients are waiting for assessment:

Patient ID	Patient Name	Priority Score
PO1	Amina	72
PO2	Daniel	45
PO3	Eric	91
PO4	Grace	63
PO5	Hassan	88
PO6	Irene	54
PO7	Jean	76

### Tasks

#### 1. Build the Max-Heap

Using the patient records above:

Build a binary tree from the given data.
Convert it into an array-based Max-Heap.
Ensure the patient with the highest priority is at the root.
Keep each patient's name and ID correctly associated with their priority score.
Clearly show the resulting heap.

#### 2. Generate the Treatment Order
Use the Max-Heap to repeatedly extract the highest-priority patient.

Display the resulting treatment order from highest to lowest priority.

For example:

Patient ___ — Priority ___
Patient ___ — Priority ___
Patient ___ — Priority ___

#### 3. New Emergency Patient
A new patient, Kofi (P08), arrives with a triage priority score of 98.

Insert the patient into the existing Max-Heap.
Restore the Max-Heap property using the appropriate heap operation.
Display the heap after insertion.

#### 4. Patient Cleared
Patient P08 is subsequently cleared from the emergency queue.

Remove P08 from the Max-Heap.
Restore the Max-Heap property.
Display the resulting heap.
Ensure all remaining patient IDs, names, and priority scores remain correctly associated.
Constraints

Implement the solution in C.
Use an array-based Max-Heap.
Each heap element must contain the patient ID, patient name, and priority score.
Correctly implement:
Heap construction
Heapify
Extraction
Insertion
Deletion
The Max-Heap property must be maintained after every operation.

## Question 3 (4pts): EV Charging Station Power Network
A city is installing a network of electric vehicle (EV) charging stations. The charging stations must be connected to the city's main power distribution network so that every station can receive electricity either directly or through another station.

Several possible underground power-cable connections are available. Each connection has an estimated installation cost.

The network is modeled as an undirected weighted graph.

Available Power Connections

Connection	Installation Cost
A — B	6
A — D	12
B — D	5
B — C	11
C — D	17
C — G	25
D — E	22
D — F	15
E — F	10
F — G	22
The installation cost is measured in thousands of dollars.

Each node represents an EV charging station, and each edge represents a possible underground power-cable connection.

### Tasks
#### 1. Graph Representation
Construct an adjacency matrix for the EV charging-station network.

The matrix must satisfy:

Each row and column represents one charging station.
Each cell represents the cable installation cost.
A value of 0 brepresents no direct connection.
The matrix must represent the graph as an undirected graph.

#### 2. Apply Kruskal's Algorithm

Use Kruskal's Algorithm to determine the Minimum Spanning Tree (MST) for the charging-station network.

Your solution should:

Sort the available connections by increasing cost.
Consider the connections in the appropriate order.
Select an edge only when it does not create a cycle.
Continue until all charging stations are connected.

#### 3. Identify the Selected Connections
Clearly list the cable connections selected for the MST.

For each selected connection, display:

Station A — Station B : Cost

The resulting network must:

Connect all charging stations.
Contain exactly v-1 connections.
Contain no cycles.
Have the minimum possible total installation cost.

#### 4. Calculate Total Installation Cost
Calculate and display the total cost of the selected connections.

Your answer should clearly show:

Selected Connections:

....

Total Installation Cost: ______ thousand dollars

 

## Question 4(3pts): IoT Gateway Connectivity Analyzer
A smart agriculture company operates several IoT gateways that collect data from sensors deployed across different farm zones. Gateways communicate directly with nearby gateways to exchange sensor data.

Each gateway is represented as a node, while a direct communication link is represented as an edge. The number on each edge represents the average data-transfer time in milliseconds between the two gateways.

IoT Gateway Network

Gateway 1	Gateway 2	Data-Transfer Time (ms)
A	B	6
A	D	12
B	D	5
B	C	11
C	D	17
C	G	25
D	E	22
D	F	15
E	F	10
F	G	22
Important: The network is an undirected graph, meaning a connection between A and B allows communication in both directions.

### Tasks
#### 1. Gateway Selection
Allow the user to enter the gateway from which the analysis should begin.

Enter starting gateway: D

Validate that the gateway exists in the network.

#### 2. BFS Connectivity Analysis
Using Breadth-First Search (BFS) starting from the selected gateway:

Traverse the graph using a queue.
Identify all gateways that are directly connected (one hop) to the selected gateway.
Display the discovered gateways in the order in which BFS encounters them.

#### 3. Communication Analysis
For the gateways directly connected to the selected gateway:

Examine their corresponding communication-link times.
Identify the directly connected gateway associated with the highest data-transfer time.
Display the gateway and its transfer time.

### Constraints
Implement the solution in C.
Represent the network using an appropriate graph representation.
Implement BFS using a queue.
The BFS must begin from the gateway entered by the user.
Do not use Dijkstra's Algorithm or DFS.
Handle an invalid gateway name gracefully.
 

## Question 5 (4pts): Cloud Service Data Routing Analyzer
A company operates several data centers that exchange application data and backups. A routing analyzer is used to determine the minimum cumulative cost of sending data from the Primary Data Center (A) to every other data center.

The network is modeled as a weighted directed graph:

Each node represents a data center.
Each directed edge represents a possible data-transfer route.
Each edge weight represents the net transfer cost of using that route.
A negative weight represents a route that provides a transfer credit or optimization benefit that reduces the overall cost.
The network is defined below:

From	To	Net Transfer Cost
A	B	6
A	D	16
B	C	6
B	D	6
B	J	7
C	G	-9
D	E	7
D	J	8
E	F	10
E	I	-2
F	G	4
F	I	2
G	H	13
I	F	2
J	E	3

### Tasks to Complete
#### 1. Graph Representation
Model the data-center network as a weighted directed graph suitable for shortest-path analysis.

Clearly represent:

Data centers as vertices.
Data-transfer routes as directed edges.
Transfer costs as edge weights.

#### 2. Bellman–Ford Algorithm
Implement the Bellman–Ford algorithm to calculate the minimum cumulative transfer cost from data center A to every other reachable data center.

For each destination, determine:

The minimum cumulative cost.
The sequence of data centers forming the minimum-cost route.
For example:

Destination: G

Path: A → B → C → G

Cost: XX

#### 3. Negative-Weight Handling
The routing system may contain transfer routes with negative costs because of optimization credits.

Your implementation must correctly handle negative-weight edges when calculating shortest paths.

The program must not assume that all edge weights are positive.

#### 4. Negative-Cycle Detection
After performing the required Bellman–Ford relaxation operations, determine whether the network contains a negative-weight cycle reachable from A.

If a negative cycle exists:

Negative-weight cycle detected.
Shortest-path results may be undefined.
If no negative cycle exists:

No negative-weight cycle detected.

#### 5. Display Results
Display a routing table similar to:

Source: A

Destination	 Shortest Cost	 Path
B	xx	A → ...
C	xx	A → ...
E	xx	A → ...
E	xx	A → ...

#### Constraints
Implement the solution in C.
Use the Bellman–Ford algorithm rather than Dijkstra's Algorithm.
The implementation must support negative edge weights.
Store sufficient information to reconstruct the actual shortest path.
Correctly identify unreachable data centers.
Handle invalid data-center names without crashing.
