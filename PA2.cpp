#include "PA2.h"
using namespace std;
/*INCLUDE header PA2.h*/


int Solver(string filename){
	/*Initializes types of colors*/
	string red = "red";
	string blue = "blue";
	string Uncolored = "uncolored";
	/*Initialize variables to parse and keep track of an arbitrary starting point fron textfile*/
	int startingpoint,num1,num2,a,b;
	/*The file pointer for the output file and string name*/
	FILE* outputfile;
	string output;
	/*Initialize Graph*/
	Graph X;
	/*Initalize Cycle for odd cycle print*/
	int* cycle;
	/*Initalize stack for DFS traversal*/
	list<int> stack;
	/*colormap to keep track of colors and marked nodes*/
	map<int,string> colormap;
	char stringending[] = "output.txt";
	/*PART1 OPEN AND PARSE TEXTFILE TO DATASTRUCTURES*/
	ifstream mainfile(filename); //open the file
	output = intoout(filename,stringending);//open outfile
	outputfile = fopen(output.c_str(), "w");
	if(mainfile.is_open()){
		string sline;
		/*This gets the first line, and initiliazes the total vertices to the c variable also intializes the GRAPH and the cycle */
		getline(mainfile,sline); //grabs the first line and puts it in sline variable
		int c = stoi(sline); 
		X.setGraph(c+1);
		cycle = new int[X.vertex];
		/*Parses the lines of the textfile into either num1/num2 or a/b*/
		/*use getline for first line to initalize an arbitrary startingpoint variable*/
		stringstream ss;
		getline(mainfile,sline); 
		ss << sline;
		ss>>num1>>num2;
		startingpoint = num1;
		X.addEdges(num1,num2);
		colormap[num1] = Uncolored;
		colormap[num2] = Uncolored;
		//printf("the very first number is %d and an edge of it is %d\n", num1,num2);


		while(mainfile >> a >> b){ //parse the file lines by (int (space) int)
			//printf("first number: %d, has edge: %d\n", a,b);
			X.addEdges(a,b); // connect the pair of int with an undirected edge
			//printf("node a: %d with first edge:%d\n", a,X.edgelist[a].front());
			colormap[a] = Uncolored;
			colormap[b] = Uncolored;
		}

	}
	/*PART 2*/
	/*iterate through all the vertex checking if they marked. If they are not then traverse their subtree else do not*/
	for(map<int,string>::iterator colorit = colormap.begin(); colorit!=colormap.end();++colorit){
	if(colorit->second==Uncolored){
	colorit->second = red;
	stack.push_front(colorit->first);
	fprintf(outputfile, "Vertex: %d has color: %s\n", colorit->first, red.c_str());
	int ptr = 0; //pointer at the beginning of the current cycle;
	/*Traverse DFS the subtree starting at node colorit->first*/
	while(!stack.empty()){ //begin traversing subtree of colorit-first vertex
		int a = stack.front(); 
		//printf("current at node: %d\n",a);
		cycle[ptr] = a;
		ptr++;
		stack.pop_front();
		for(vector<int>::iterator it = X.edgelist[a].begin(); it!=X.edgelist[a].end();it++){
			/*Case: node is uncolored then color it the other color and push it onto the stack
			  print to document the node# and the color{red,blue}*/
			if(colormap[*it]==Uncolored){
				colormap[*it] = (colormap[a]==red) ? blue: red;
				fprintf(outputfile, "Vertex: %d has color: %s\n", *it, colormap[*it].c_str());
				 //printf("Node:%d is color:%s\n", *it , Colorgraph[*it].c_str());
				stack.push_front(*it);
			}
			/*Invalid Case-> add last statements then print to file and print to console*/
			else if(strcmp(colormap[*it].c_str(),colormap[a].c_str())==0){
				fprintf(outputfile,"\nThe Graph is not 2 Colorable\n\n");
				fprintf(outputfile,"Here is the odd cycle of the Graph with size:%d\n",ptr+1);
				/*Print cycle*/
				if(ptr <100){
					printf("Here is the odd cycle of the Graph with size:%d\n",ptr+1);
					for(int i = 0; i < ptr; i ++){
						fprintf(outputfile,"%d,",cycle[i]);
						printf("%d,",cycle[i]);
					}
				/*last digit of cycle*/
					fprintf(outputfile,"%d",*it);
					printf("%d",*it);
				}
				else{
					for(int i = 0; i < ptr; i ++){
						fprintf(outputfile,"%d,",cycle[i]);
					}
					fprintf(outputfile,"%d",*it);
				}
				return 0;

			}	
		}
	}
	}
}	
	/*Close file return 1 for validity*/
	fprintf(outputfile,"The Graph is a valid bipartite");
	fclose(outputfile);
	return 1;

}
/*Alters input file name to correct output format by adding "output.txt" */
string intoout(string input, string add){
	string returner = input+add;
	return returner;
}

