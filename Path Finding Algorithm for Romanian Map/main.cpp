#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <cstdlib>

using namespace std;

int flag = 1;

//node required for stack, priority queue and queue implementation
struct node {
	float fcost;
	int info;
	struct node* next;
};

//stack implementation
class stack {
	struct node* top;
public:
	stack();
	bool isEmpty();
	void push(int);
	int pop();
};
stack::stack() {
	top = NULL;
}
bool stack::isEmpty() { 
	return (top == NULL); 
}
void stack::push(int info) {
	node* n = new node;
	n->info = info;
	n->next = top;
	top = n;
}
int stack::pop() {
	node* temp = new node;
	int value;
	if (top == NULL) {
		cout << "\nEmpty stack" << endl;
	}
	else {
		temp = top;
		top = top->next;
		value = temp->info;
		delete temp;
	}
	return value;
}

//priority queue implementation
class Pqueue {
private:
	node *front;
public:
	Pqueue();
	bool isEmpty();
	void enqueue(int, float);
	int dequeue();
};
Pqueue::Pqueue() {
	front = NULL;
}
bool Pqueue::isEmpty() {
	return (front == NULL);
}
void Pqueue::enqueue(int data, float fcost) {
	node *temp = new node();
	temp->info = data;
	temp->fcost = fcost;
	node *temp2;

	if (front == NULL || fcost < front->fcost) {
		temp->next = front;
		front = temp;
	}
	else {
		temp2 = front;
		while (temp2->next != NULL && temp2->next->fcost <= fcost) {
			temp2 = temp2->next;
		}
		temp->next = temp2->next;
		temp2->next = temp;
	}
}
int Pqueue::dequeue() {
	node *temp = new node();
	int value;
	if (front == NULL) {
		cout << "\nQueue is Emtpty\n";
	}
	else {
		temp = front;
		value = temp->info;
		front = front->next;
		delete temp;
	}
	return value;
}

//Queue implementation
class Queue {
private:
	node *front;
	node *rear;
public:
	Queue();
	bool isEmpty();
	void enqueue(int);
	int dequeue();
};
Queue::Queue() {
	front = NULL;
	rear = NULL;
}
bool Queue::isEmpty() {
	return (front == NULL);
}
void Queue::enqueue(int data) {
	node *temp = new node();
	temp->info = data;
	temp->next = NULL;
	if (front == NULL) {
		front = temp;
	}
	else {
		rear->next = temp;
	}
	rear = temp;
}
int Queue::dequeue() {
	node *temp = new node();
	int value;
	if (front == NULL) {
		cout << "\nQueue is Emtpty\n";
	}
	else {
		temp = front;
		value = temp->info;
		front = front->next;
		delete temp;
	}
	return value;
}

//Calculate hcost for straight line distance between two cities
float calc_hcost(string sCity, string dCity) {
	ifstream InputFile2;
	string InputFileName2 = "locations.txt";
	InputFile2.open(InputFileName2.c_str());

	string city, lat, lon;
	float lat1, lon1, lat2, lon2;

	while (!InputFile2.eof()) {
		InputFile2 >> city;
		InputFile2 >> lat;
		InputFile2 >> lon;

		if (city == sCity) {
			lat1 = std::atof(lat.c_str());	//conversion string to float
			lon1 = std::atof(lon.c_str());
		}
		if (city == dCity) {
			lat2 = std::atof(lat.c_str());  //conversion string to float
			lon2 = std::atof(lon.c_str());
		}
	}

	//calculation of pythagorean staright line distance
	float y2 = (lon2-lon1);
	y2 = y2*100;
	y2 = y2*y2;					
	float x2 = (lat2-lat1);
	x2 = x2*100;
	x2 = x2*x2;

	float sum = x2+y2;
	float dist = sqrt(sum);

	//close file before return
	InputFile2.close();
	return dist;
}



//implementation of graph for the map
class graph {
public:
	int no_of_cities;
	string* list_of_cities;
	int total_distance;
	int** distance_table;

	graph(int);
	bool isConnected(int, int);
	void add_neighbour(string, string, int);
	int DFS(string, string);
	int BFS(string, string);
	int ASTAR(string, string);
};
graph::graph(int n) {
	int i, j;
	no_of_cities = n;
	list_of_cities = new string[no_of_cities];
	distance_table = new int*[no_of_cities];


	for (i = 0; i < no_of_cities; i++)
	{
		distance_table[i] = new int[no_of_cities];

		//initializing distance matrix to 0
		for (j = 0; j < no_of_cities; j++) {

			distance_table[i][j] = 0;
		}

	}
}

bool graph::isConnected(int n1, int n2)
{

	return (distance_table[n1][n2] > 0);
}


void graph::add_neighbour(string sCity, string gCity, int distance) {
	int n1, n2, i, j, end_of_list;
	bool found;
	found = false;
	
	end_of_list = i = 0;
	found = false;
	//add city if not already added in list
	while (i < no_of_cities) {
		if (list_of_cities[i] == sCity) {
			found = true;
			break;
		}

		if (list_of_cities[i] == "") {
			end_of_list = i;
			break;
		}
		i++;
	}

	if (found == false)
	{
		list_of_cities[end_of_list] = sCity;
	}



	end_of_list = i = 0;
	found = false;
	while (i < no_of_cities) {

		if (list_of_cities[i] == gCity) {
			found = true;
			break;
		}

		if (list_of_cities[i] == "") {
			end_of_list = i;
			break;
		}
		i++;
	}

	if (found == false)
	{
		list_of_cities[end_of_list] = gCity;

	}


	i = 0;
	for (i = 0; i < no_of_cities; i++) {
		if (sCity == list_of_cities[i]) {
			n1 = i; break;
		}
	}
	i = 0;


	for (i = 0; i < no_of_cities; i++) {

		if (gCity == list_of_cities[i]) {

			n2 = i; break;
		}
	}
	distance_table[n1][n2] = distance_table[n2][n1] = distance;
}

int graph::DFS(string sCity, string gCity) {

	int i,j, sNode, gNode, cNode;
	bool* visited_city = new bool[no_of_cities];
	int *where = new int[no_of_cities];
	int *final_path = new int[no_of_cities];
	stack city;
	int num_visit=0;

	for (i = 0; i < no_of_cities; i++)
	{
		if (list_of_cities[i] == sCity)
		{
			sNode = i;
			break;
		}

	}

	for (i = 0; i < no_of_cities; i++)
	{

		if (list_of_cities[i] == gCity)
		{
			gNode = i;
			break;

		}
	}


	for (i = 0; i < no_of_cities; i++)
	{
		visited_city[i] = false;

	}

	city.push(sNode);
	visited_city[sNode] = true;

	if (flag==1) {
		cout << "Depth First Search starting from city " << list_of_cities[sNode] << ":" << endl;
		cout << "List of node traversed : " ;
	}
	string temp_c;
	string back_city;
	while (!city.isEmpty())
	{
		cNode = city.pop() ;
		num_visit++;

		if (cNode == gNode) {
			if (flag==1) {
				cout << list_of_cities[cNode] << endl;
			}
			break;
		}
		if (flag==1) {
			cout << list_of_cities[cNode]<<" , ";
		}

		for (i = no_of_cities - 1; i >= 0; i--)
		{
			if (isConnected(cNode, i) && !visited_city[i]) {
				where[i] = cNode;
				if (i == gNode)
				{
					for (j = 0; j < no_of_cities; j++)
					{
						final_path[j] = where[j];

					}
				}
				city.push(i);
				visited_city[i] = true;
			}
		}

	}

	int ind, t2, t1,node, no_of_traversed_nodes=0;
	string path;
	ind = 0;
	node = gNode;
	while (node != sNode) {
		t1 = final_path[node];
		node = t1;

		if (ind == 0) {
			path = list_of_cities[node] ;
		}
		else {
			path = list_of_cities[node] + " -> " + path;
		}
		ind = 1;
	}

	for (i = 0; i < no_of_cities; i++) {
		if (visited_city[i] == true) {
			no_of_traversed_nodes = no_of_traversed_nodes + 1;
		}
	}
	if (flag==1) {
		cout << endl << "Total traversed nodes: "<< num_visit <<endl;
		cout << endl << "Final path: ";
		cout << path << " -> " + list_of_cities[gNode] << endl;
		cout << endl;
	}

	return num_visit;


}

int graph::ASTAR(string sCity, string gCity) {
	Pqueue city;
	int sNode, gNode,cNode,i;
	int *where = new int[no_of_cities];
	int *old_gcost = new int[no_of_cities];
	int *final_path = new int[no_of_cities];
	float hcost = 0, fcost = 0;
	int gcost = 0;

	i = 0;

	bool* visited_city = new bool[no_of_cities];
	for (i = 0; i < no_of_cities; i++) {
		visited_city[i] = false;
	}

	for (i = 0; i < no_of_cities; i++) {
		if (list_of_cities[i] == sCity) {
			sNode = i;
			break;
		}
	}
	for (i = 0; i < no_of_cities; i++) {
		if (list_of_cities[i] == gCity) {
			gNode = i;
			break;
		}
	}

	hcost = calc_hcost(sCity, gCity);
	old_gcost[sNode] = 0;
	city.enqueue(sNode, hcost);

	if (flag==1) {
		cout << "A* Search starting from city " << list_of_cities[sNode] << endl;
		cout << "List of traversed nodes:" << endl;
	}

	int temp;
	int j;

	while (!city.isEmpty()) {

		cNode = city.dequeue();
		visited_city[cNode] = true;

		if (cNode == gNode) {
			if (flag==1) {
				cout << list_of_cities[cNode] << endl;
			}
				break;
		}
		if (flag==1) {
			cout << list_of_cities[cNode] << " , ";
		}

		for (i = 0; i < no_of_cities; i++)
		{
			//if ((isConnected(cNode, i) && (i==gNode)) || (isConnected(cNode, i) && !visited_city[i])) {
			//if (isConnected(cNode, i)) {
			if ((isConnected(cNode, i) && !visited_city[i])) {
				where[i] = cNode;
				if (i == gNode) {
					for (j = 0; j < no_of_cities; j++) {
						final_path[j] = where[j];
					}
				}
				hcost = calc_hcost(list_of_cities[i], gCity);
				gcost = distance_table[i][cNode] + old_gcost[cNode];
				old_gcost[i] = gcost;
				fcost = gcost + hcost;
				city.enqueue(i, fcost);
			}
		}
	}

	int ind, t2, t1, node, no_of_traversed_nodes = 0;
	string path;
	ind = 0;
	node = gNode;
	while (node != sNode)
	{
		t1 = final_path[node];
		node = t1;
		if (ind == 0) {
			path = list_of_cities[node];
		}
		else {
			path = list_of_cities[node] + " -> " + path;
		}
		ind = 1;
	}

	for (i = 0; i < no_of_cities; i++) {
		if (visited_city[i] == true) {
			no_of_traversed_nodes = no_of_traversed_nodes + 1 ;
		}
	}
	if (flag==1) {
		cout << endl << "Total traversed nodes: " << no_of_traversed_nodes << endl;
		cout << endl << "Final path: ";
		cout << path << " -> " + list_of_cities[gNode] << endl;
		cout << endl;
	}
	return no_of_traversed_nodes;
}

int graph::BFS(string sCity, string gCity)

{
	Queue city;
	int sNode, gNode,cNode,i;
	int *where = new int[no_of_cities];
	int *final_path = new int[no_of_cities];
	i = 0;
	int num_visit=0;


	bool* visited_city = new bool[no_of_cities];

	for (i = 0; i < no_of_cities; i++)
	{
		visited_city[i] = false;

	}

	for (i = 0; i < no_of_cities; i++)
	{
		if (list_of_cities[i] == sCity)
		{

			sNode = i;
			break;
		}

	}

	for (i = 0; i < no_of_cities; i++)
	{

		if (list_of_cities[i] == gCity)
		{
			gNode = i;
			break;

		}

	}

	city.enqueue(sNode);
	visited_city[sNode] = true;
	if (flag==1) {
		cout << "Breadh First Search starting from city " << list_of_cities[sNode] << ":" << endl;
		cout << "List of traversed nodes:";
	}
	int temp;
	int j;
	while (!city.isEmpty())
	{

		cNode = city.dequeue();
		num_visit++;

		if (cNode == gNode) {
			if (flag==1) {
				cout << list_of_cities[cNode] << endl;
			}
				break;
		}
		if (flag==1) {
			cout << list_of_cities[cNode] << " , ";
		}

		for (i = 0; i < no_of_cities; i++)
		{

			if (isConnected(cNode, i) && !visited_city[i]) {

				where[i] = cNode;
				if (i == gNode)
				{
					for (j = 0; j < no_of_cities; j++)
					{
						final_path[j] = where[j];

					}
				}

				city.enqueue(i);
				visited_city[i] = true;
			}

		}

	}


	int ind, t2, t1, node, no_of_traversed_nodes = 0;
	string path;
	ind = 0;
	node = gNode;
	while (node != sNode)
	{

		t1 = final_path[node];
		node = t1;

		if (ind == 0)
		{
			path = list_of_cities[node];

		}
		else {

			path = list_of_cities[node] + " -> " + path;
		}

		ind = 1;
	}

	for (i = 0; i < no_of_cities; i++)
	{

		if (visited_city[i] == true)
		{

			no_of_traversed_nodes = no_of_traversed_nodes + 1 ;
		}
	}
	if (flag==1) {
		cout << endl << "Total traversed nodes: " << num_visit << endl;
		cout << endl << "Final path: ";
		cout << path << " -> " + list_of_cities[gNode] << endl;
		cout << endl;
	}
	return num_visit;

}


int main(int argc,char *argv[])
{
    string searchtype, src, dest;
    searchtype = argv[1];
    src = argv[2];
    dest = argv[3];
	string number;
	int num, count;

	string src1, dest1, len1;
	int len11;

	ifstream InputFile;
	string InputFileName = "neighbours.txt";
	InputFile.open(InputFileName.c_str());

	InputFile >> number;
	num = std::atoi(number.c_str());

	graph country(num);

	while (!InputFile.eof())
	{
		InputFile >> src1;
		InputFile >> dest1;
		InputFile >> len1;
		len11 = std::atoi(len1.c_str());

		country.add_neighbour(src1, dest1, len11);
	}
	InputFile.close();

	if (searchtype == "BFS") {
		count = country.BFS(src, dest);
	}
	else if (searchtype == "DFS") {
		count = country.DFS(src, dest);

	}
	else if (searchtype == "A*") {
		count = country.ASTAR(src, dest);
	}
	else if (searchtype == "BFSvsDFS") {
		int bfs_count, dfs_count;
		flag = 0;

		for (int i=0; i<country.no_of_cities ; i++) {
			for (int j=0; j<country.no_of_cities; j++) {
				if (i==j)
					continue;
				bfs_count = country.BFS(country.list_of_cities[i], country.list_of_cities[j]);
				dfs_count = country.DFS(country.list_of_cities[i], country.list_of_cities[j]);

				if (bfs_count < dfs_count) {
					cout << "FOUND!!!	Source: " << country.list_of_cities[i] << "	Dest: " << country.list_of_cities[j] << "	BFS: " << bfs_count << "	DFS: " << dfs_count << endl;
				}
			}
		}
	}
	else if (searchtype == "DFSvsA*") {
		int dfs_count, as_count;
		flag = 0;

		for (int i=0; i<country.no_of_cities ; i++) {
			for (int j=0; j<country.no_of_cities; j++) {
				if (i==j)
					continue;
				dfs_count = country.DFS(country.list_of_cities[i], country.list_of_cities[j]);
				as_count = country.ASTAR(country.list_of_cities[i], country.list_of_cities[j]);

				if (dfs_count < as_count) {
					cout << "FOUND!!!	Source: " << country.list_of_cities[i] << "	Dest: " << country.list_of_cities[j] << "	DFS: " << dfs_count << "	A*: " << as_count << endl;
				}
			}
		}

	}
	else {
        cout<<"Wrong input";
    }

	return 0;
}
