#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

using namespace std;

//Constructing a structure for creating a linked list.
struct List
{
    //Data Members.
    int vertex;
    List* next;
};

//AdjacencyList Class
class AdjacencyList
{
    //Member Functions
    public:
        AdjacencyList();
        AdjacencyList(int VerA);
        void addEdge(int src, int des);
        void BFS(int vertexId,int LadderPos1[],int LadderPos2[], int SnakePos1[]);
        virtual ~AdjacencyList();

    //Data Members
    private:
      int noOfVertices;
      //Creating a pointer to pointer variable to point to the array of linked lists.
      List** adj;
};
#endif // ADJACENCYLIST_H
