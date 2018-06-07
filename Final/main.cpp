#include <iostream>
#include <string>
#include <vector>

using namespace std;

void leftRot(AVLTreeNode * & ptr){
    TreeNode* temp = ptr->right;
    ptr->right = temp->left;
    temp->left = ptr;
    //update height
    ptr = temp;
}

void rightRot(AVLTreeNode * & ptr){
    TreeNode* temp = ptr->left;
    ptr->left = temp->right;
    temp->right = ptr;
    //update height
    ptr = temp;
}

void DoubleRight(AVLTreeNode * & ptr){
    TreeNode* firstRot = ptr->left;

    TreeNode* temp = firstRot->right;
    firstRot->right = temp->left;
    temp->left = firstRot;
    firstRot->height = max(height(firstRot->left), height(firstRot->right));
    temp->height = max(height(temp->left), height(temp->right));
    firstRot = temp;

    ptr->left = temp->right;
    temp->right = ptr;
    ptr->height = max(height(ptr->left), height(ptr->right));
    temp->height = max(height(temp->left), height(temp->right));
    ptr = temp;
}

int height(TreeNode * & root){
    if(root == NULL)
        return -1;
    return 1 + max(height(root->left), height(root->right));
}

bool isHeightBalanced(TreeNode * & root){
    if(root == NULL)
        return true;
    int lheight = height(root->left);
    int rheight = height(root->right);

    if(abs(lheight - rheight) > 1)
        return false;
    return true;
}

int doubleStart(TrieNode *ptr){
    if(ptr == NULL)
        return 0;
    TrieNode *temp = ptr;
    while(temp != NULL){
        if(temp->letter == temp->subtree->head->letter)
            return 1 + doubleStart(ptr->next);
        temp = temp->subtree->next;
    }
    return doubleStart(TrieNode *ptr)
}

Array<DSNode*> makeTrees(Array<int> sets){
    Array<DSNode*> dynamicSets(1, sets.size());

    for(int i = 1; i < dynamicSets.size(); i++)
        dynamicSets[i] = new DSNode(i);
    for(int i = 1; i < sets.size(); i++)
        dynamicSets[i].parent = dynamicSets[sets[i]];
    return dynamicSets;
}


int countLeftFirst(Array<int> tree) {
    int count = 0;
    for(int i = 1; i < tree.size(); i++){
        if(tree[2 * i] < tree[i] && tree[2 * i] < tree[2 * i + 1])
            count++;
    }
    return count;
}

int numOddDegree(Array<EdgeNode*>& graph){
    int numOdd = 0;
    int curr = 1;
    while(curr <= graph.size()){
        EdgeNode* trav = graph[curr];
        int count = 0;
        while(trav != NULL){
            trav = trav->next;
            count++;
        }
        if(count % 2 == 1)
            numOdd++;
        curr++;
    }
    return numOdd;
}

int DistanceCheck(int** graph, int n){
    int flag = 1;
    int curr = 0;
    int* store = new int[n];
    while(flag && curr < n){
        for(int i = 0; i < n; i++)
            store[i] = 0;
        store[curr] = 1;
        for(int i = 0; i < n; i++){
            if(graph[curr][i] == 1){
                store[i] = 1;
                for(int j = 0; j < n; j++){
                    if(graph[i][j] == 1)
                        store[j] = 1;
                }
            }
        }
        int i = 0;
        while(flag && i < n){
            if(store[i] != 1)
                flag = 0;
            else
                i++;
        }
        if(flag)
            curr++;
    }
    delete[] marks;
    return (curr == n);
}

void dijkstra(int graph[V][V], int src)
{
     int dist[V];     // The output array.  dist[i] will hold the shortest
                      // distance from src to i

     bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
                     // path tree or shortest distance from src to i is finalized

     // Initialize all distances as INFINITE and stpSet[] as false
     for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

     // Distance of source vertex from itself is always 0
     dist[src] = 0;

     // Find shortest path for all vertices
     for (int count = 0; count < V-1; count++)
     {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in first iteration.
       int u = minDistance(dist, sptSet);

       // Mark the picked vertex as processed
       sptSet[u] = true;

       // Update dist value of the adjacent vertices of the picked vertex.
       for (int v = 0; v < V; v++)

         // Update dist[v] only if is not in sptSet, there is an edge from
         // u to v, and total weight of path from src to  v through u is
         // smaller than current value of dist[v]
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }

     // print the constructed distance array
     printSolution(dist, V);
}

TreeNode* LevelOrderToTree(ListNode* head){
    if(head == NULL)
        return NULL;

    queue<ListNode*> q;
    TreeNode* root = new TreeNode();
    root->element = head->element;
    TreeNode* temp;
    q.push(root);
    ListNode* curr = head->next;

    while(!q.empty()){
        temp = q.front();
        q.pop();

        if(curr == NULL){
            temp->left = NULL;
            temp->right = NULL;
        }
        else{
            temp->left = new TreeNode();
            temp->left->element = curr->element;
            q.push(temp->left);
            curr = curr->next;

            temp->right = new TreeNode();
            temp->right->element = curr->element;
            q.push(temp->right);
            curr = curr->next;
        }
    }
    return temp;
}

int CountLeaves(TreeNode* ptr){
    if(ptr == NULL)
        return 0;
    if(ptr->left == NULL && ptr->right == NULL)
        return 1;
    return CountLeaves(ptr->left) + CountLeaves(ptr->right);
}

IntTriple Verify(TreeNode* ptr){
    IntTriple triple = new IntTriple();
    if(ptr == NULL){
        triple.first = 1;
        return triple;
    }
    bool isBST;
    while(ptr)
}

IntTriple Verify(TreeNode* ptr){
    IntTriple retVal;
    if(ptr == NULL){
        retVal.first = 1;
        retVal.second = 0;
        retVal.third = -1;
    }
    IntTriple left = Verify(ptr->left);
    IntTriple right = Verify(ptr->right);
    retVal.first = 1;
    retVal.second = ptr->element;
    retVal.third = ptr->element;

    if(left.first == 0 || right.first == 0)
        retVal.first = 0;

    if((left.second <= left.third && left.second > ptr->element) ||
        (right.second <= right.third && right.third < ptr->element))
        retVal.first = 0;

    if(left.second <= left.third){
        if(retVal.second > left.second)
            retVal.second = left.second;
        if(retVal < left.third)
            retVal.third = left.third;
    }

    if(right.second <= right.third){
        if(retVal.second > right.second)
            retVal.second = right.second;
        if(retVal.third < right.third)
            retVal.third = right.third;
    }
    return retVal;
}

ListNode* TreeToList(TreeNode* ptr){
    if(ptr == NULL)
        return NULL;
    ListNode* head = new ListNode();
    head->element = ptr->element;
    ListNode* before = TreeToList(ptr->left);
    ListNode* after = TreeToList(ptr->right);

    head->next = after;
    if(after != NULL)
        after->prev = head;

    if(before != NULL){
        ListNode* temp = before;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = head;
        head->prev = temp;
        return before;
    }
    return head;
}

int find(int x){
    if(x < 0 || x > set.size())
        return x;
    return set[x] = find(set[x]);
}

void setUnion(int a, int b){
    int x = find(x);
    int y = find(y);
    int size = set[x] + set[y];

    if(set[x] <= set[y]){
        set[y] = set[x];
        set[x] = size;
    }
    else{
        set[x] = set[y];
        set[y] = size;
    }
    return;
}

int main() {

}
