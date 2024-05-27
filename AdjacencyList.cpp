#include "AdjacencyList.h"
#include <iostream>
#include <queue>
#include <string>

using namespace std;

AdjacencyList::AdjacencyList()
{
    //Nothing Special Has Been Done Here.
}

AdjacencyList::AdjacencyList(int VerA) : noOfVertices(VerA)
{
    //Adj is pointing to the array of Lists.
    adj = new List * [noOfVertices];

    //Iterating the loop noOfvertices times.
    for (int i = 0;i <= noOfVertices;i++)
    {
        //Declaring as NULL.
        adj[i] = NULL;
    }
}

void AdjacencyList::addEdge(int src, int des)
{
    //Creating a new Node.
    List* newNode = new List;

    //Initializing the vertex value.
    newNode->vertex = des;

    //Adding a new node at the end of specified array of list index.
    //If it is NULL.
    if (adj[src] == NULL)
    {
        newNode->next = adj[src];
        adj[src] = newNode;
    }

    //If it is not NULL.
    else
    {
        //Starting from the head.
        List* currentptr = adj[src];

        //Going where we wanna enter new edge.
        while (currentptr->next != NULL)
            currentptr = currentptr->next;

        //Declaring that last node is connected with any node in the list.
        newNode->next = NULL;
        currentptr->next = newNode;
    }
}
void AdjacencyList::BFS(int vertexId, int LadderPos1[], int LadderPos2[], int SnakePos1[])
{
    //Creating a queue to insert the adjacent vertices of a vertex.
    queue<int> Q;

    //Creating an array to check whether a vertex has been visited or not.
    bool flag[noOfVertices + 1];

    //Creating an array to record the path and an integer type variable to show the current position.
    int roll[noOfVertices + 1], curr, end = 100;

    //To show the number of times you've to roll dice.
    int rolls =0;

    //Declaring the initials conditions.
    for (int i = 1; i < noOfVertices + 1; i++)
    {
        //Ensures that no vertex has been visited.
        flag[i] = false;

        //No record has been put in it.
        roll[i] = -1;
    }

    //Source vertex has been visited and enqueued it.
    flag[vertexId] = true;
    Q.push(vertexId);

    //Iterate until we reach the final vertex which is '100'.
    while (!flag[end])
    {
        //Getting the value which is at the rear of the queue.
        curr = Q.back();

        //If the vertex/current position is greater than 93.
        if (end - curr <= 6)
        {
            //Marked this vertex as visited.
            flag[end] = true;

            //Updating the record for rolls.
            roll[end] = end - curr;

            //Updating the current position of the vertex.
            curr = end;
        }

        else
        {
            //Ensuring that ladder vertex will only be queued rather than other adjacent vertices of a vertex.
            int Lad = 0;
            List* NextVertice = adj[curr];

            while (NextVertice != NULL && Lad == 0)
            {
                //Checking if vertex is a ladder.
                for (int i = 0; i < 8; i++)
                {
                    //Validating that vertex is a ladder and ensuring that vertex has not been visited.
                    if (NextVertice->vertex == LadderPos1[i] && !flag[NextVertice->vertex])
                    {
                        //Updating the current position vertex.
                        curr = LadderPos2[i];

                        //Mark this vertex as visited.
                        flag[NextVertice->vertex] = true;

                        //Updating the roll.
                        roll[curr] = NextVertice->vertex - Q.back();

                        //Ensuring.
                        Lad = 1;

                        //Terminating because this is our best possible vertex.
                        break;
                    }
                }

                //Checking if vertex is a snake.
                for (int i = 0; i < 8; i++)
                {
                    //Validating vertex is not a snake and ensuring that vertex has not been visited.
                    if (NextVertice->vertex != SnakePos1[i] && !flag[NextVertice->vertex] && Lad == 0)
                    {
                        //Updating the current position vertex.
                        curr = NextVertice->vertex;

                        //Mark this vertex as visited.
                        flag[NextVertice->vertex] = true;

                        //Updating the roll.
                        roll[curr] = NextVertice->vertex - Q.back();
                    }
                }

                //Moving ahead in the list.
                NextVertice = NextVertice->next;
            }
        }

        //Enqueueing the vertex Id.
        Q.push(curr);
    }

    cout << "The shortest path from the " << vertexId << " to the last vertex.\n";
    //Showing the shortest path by eliminating the starting vertex.
    Q.pop();
    while (!Q.empty())
    {
        //Dequeuing and showing the  vertices.
        int value = Q.front();
        Q.pop();
        cout << "-> " << value << " ( Dice Roll Required : " << roll[value] << " ) " << endl;
        rolls++;
    }
    cout << "The minimum numbers of times you've to roll dice : " << rolls << endl;
}

AdjacencyList::~AdjacencyList()
{
    //Freeing the memory.
    delete[] adj;
}
