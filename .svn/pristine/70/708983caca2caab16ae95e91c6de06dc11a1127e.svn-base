/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
    vector<Vertex> verts = graph.getVertices();
    vector<Edge> edges = graph.getEdges();

    for(size_t i = 0; i < verts.size(); i++)
        graph.setVertexLabel(verts[i], "UNEXPLORED");

    for(size_t i = 0; i < edges.size(); i++){
        Vertex s = edges[i].source;
        Vertex d = edges[i].dest;
        graph.setEdgeLabel(s, d, "UNEXPLORED");
    }

    queue<Vertex> q;
    q.push(verts[0]);
    graph.setVertexLabel(verts[0], "VISITED");
    Vertex start = (graph.getAdjacent(verts[0]))[0];
    int min = graph.getEdgeWeight(verts[0], start);
    Vertex minVert1 = verts[0];
    Vertex minVert2 = start;

    while(!q.empty()){
        Vertex s = q.front();
        q.pop();
        vector<Vertex> adj = graph.getAdjacent(s);

        for(size_t i = 0; i < adj.size(); i++){
            if(graph.getVertexLabel(adj[i]) == "UNEXPLORED"){
                graph.setEdgeLabel(s, adj[i], "DISCOVERY");
                graph.setVertexLabel(adj[i], "VISITED");
                int curr = graph.getEdgeWeight(adj[i], s);
                if(min > curr){
                    min = curr;
                    minVert1 = s;
                    minVert2 = adj[i];
                }
                q.push(adj[i]);
            }
            else if(graph.getEdgeLabel(s, adj[i]) == "UNEXPLORED"){
                graph.setEdgeLabel(s, adj[i], "CROSS");
                int curr = graph.getEdgeWeight(adj[i], s);
                if(min > curr){
                    min = curr;
                    minVert1 = s;
                    minVert2 = adj[i];
                }
            }
        }
    }
    graph.setEdgeLabel(minVert1, minVert2, "MIN");
    return min;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    vector<Vertex> verts = graph.getVertices();
    vector<Edge> edges = graph.getEdges();

    for(size_t i = 0; i < verts.size(); i++)
        graph.setVertexLabel(verts[i], "UNEXPLORED");

    for(size_t i = 0; i < edges.size(); i++){
        Vertex s = edges[i].source;
        Vertex d = edges[i].dest;
        graph.setEdgeLabel(s, d, "UNEXPLORED");
    }

    unordered_map<Vertex, Vertex> par;
    queue<Vertex> q;
    q.push(start);
    graph.setVertexLabel(start, "VISITED");

    while(!q.empty()){
        Vertex s = q.front();
        q.pop();
        vector<Vertex> adj = graph.getAdjacent(s);

        for(size_t i = 0; i < adj.size(); i++){
            if(graph.getVertexLabel(adj[i]) == "UNEXPLORED"){
                graph.setEdgeLabel(s, adj[i], "DISCOVERY");
                graph.setVertexLabel(adj[i], "VISITED");
                pair<Vertex, Vertex> pairVertex(adj[i], s);
                q.push(adj[i]);
                par.insert(pairVertex);
            }
            else if(graph.getEdgeLabel(s, adj[i]) == "UNEXPLORED")
                graph.setEdgeLabel(s, adj[i], "CROSS");
        }
    }

    int c = 0;
    while(start != end){
        graph.setEdgeLabel(end, par[end], "MINPATH");
        end = par[end];
        c++;
    }
    return c;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    vector<Edge> edges = graph.getEdges();
    vector<Edge>::iterator it;
    sort(edges.begin(), edges.end(), sortEdge);
    DisjointSets verts;
    vector<Vertex> vertList = graph.getVertices();
    verts.addelements(vertList.size());

    for(size_t i = 0; i < edges.size(); i++){
        Vertex s = edges[i].source;
        Vertex d = edges[i].dest;

        if(verts.find(s) != verts.find(d)){
            verts.setunion(s, d);
            graph.setEdgeLabel(s, d, "MST");
        }
    }
}

bool GraphTools::sortEdge(Edge a, Edge b){
    return (a.weight < b.weight);
}
