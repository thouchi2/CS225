/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    /// @todo Graded in MP3.1
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1
    ListNode * curr = head;
    while(curr != NULL){
        ListNode * temp;
        temp = curr;
        curr = curr->next;
        delete temp;
    }
    length = 0;
    tail = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
    /// @todo Graded in MP3.1
    ListNode * temp = new ListNode(ndata);
    if(head == NULL){
        temp->prev = NULL;
        temp->next = NULL;
        head = temp;
        tail = head;
    }

    else{
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
    temp = NULL;
    length++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
    /// @todo Graded in MP3.1
    ListNode * temp = new ListNode(ndata);
    if (tail == NULL){
        temp->prev = NULL;
        temp->next = NULL;
        head = temp;
        tail = head;
    }

    else{
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
    }
    temp = NULL;
    length++;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    if(head != NULL && tail != NULL && head != tail)
        reverse(head, tail);
    else
        return;
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
    /// @todo Graded in MP3.1
    //check for bad input
    if(startPoint == NULL || endPoint == NULL || startPoint == endPoint)
        return;

    ListNode * first = startPoint;
    ListNode * last = endPoint;
    ListNode * back = startPoint->prev;
    ListNode * foward = endPoint->next;

    while(startPoint != endPoint){
        ListNode * temp = startPoint->prev;
        startPoint->prev = startPoint->next;
        startPoint->next = temp;
        startPoint = startPoint->prev;
    }
    ListNode * temp = startPoint->prev;
    startPoint->prev = back;
    startPoint->next = temp;
    endPoint = first;
    endPoint->next = foward;

    if(back != NULL)
        back->next = startPoint;
    else
        head = startPoint;

    if(foward != NULL)
        foward->prev = endPoint;
    else
        tail = endPoint;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{
    /// @todo Graded in MP3.1
    if(head == NULL)
        return;
    ListNode * start = head;
    ListNode * end = head;

    while(end->next != NULL && start->next != NULL){
        end = start;

        int i = 0;
        while(i < n - 1){
            if(end->next != NULL)
                end = end->next;
            i++;
        }
        reverse(start, end);
        start = end->next;
    }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
    if(length < 3  || head == NULL || tail == NULL)
        return;
    ListNode * store = head;
    ListNode * temp = head;
    while(store != tail && store->next != tail && store != NULL){
        temp = store;
        store = store->next;
        temp->next = store->next;
        store->next->prev = temp;
        tail->next = store;
        store->prev = tail;
        store->next = NULL;
        tail = store;
        store = temp->next;
    }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
    /// @todo Graded in MP3.2
    if(splitPoint == 0 || start == NULL)
        return start;
    ListNode * newH = head;
    for(int i = 0; i < splitPoint; i++){
            newH = newH->next;
    }
    newH->prev->next = NULL;
    newH->prev = NULL;
    return newH;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
    /// @todo Graded in MP3.2
    //bad input
    if(first == NULL|| second == NULL)
        return NULL;
    if(first == second)
        return first;

    ListNode *trackFinal;
    ListNode *temp;
    ListNode *trackFirst = first;
    ListNode *trackSecond = second;
    ListNode *retH = NULL;

    //start at lesser value
    if(first->data < second->data){
        trackFinal = trackFirst;
        trackFirst = trackFirst->next;
        retH = first;
    }
    else{
        trackFinal = trackSecond;
        trackSecond = trackSecond->next;
        retH = second;
    }

    //loop until end of list
    while(trackFirst != NULL || trackSecond != NULL){
        if(trackSecond == NULL || (trackFirst != NULL && trackFirst->data < trackSecond->data)){
            trackFinal->next = trackFirst;
            trackFirst->prev = trackFinal;
            temp = trackFinal->next;
            trackFinal = trackFinal->next;
            trackFirst = trackFirst->next;
        }
        else{
            trackFinal->next = trackSecond;
            trackSecond->prev = trackFinal;
            temp = trackFinal->next;
            trackFinal = trackFinal->next;
            trackSecond = trackSecond->next;
        }
    }
    return retH;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
    /// @todo Graded in MP3.2
    ListNode *mergeHead = start;
    if(chainLength == 1){
        start->next = start->prev = NULL;
        return start;
    }
    else{
        ListNode *ss = start;
        for(int i = 0; i < chainLength/2; i++){
            ss = ss->next;
        }
        ss->prev->next = NULL;
        ss->prev = NULL;
        start = mergesort(start, chainLength/2);
        ss = mergesort(ss, chainLength - chainLength/2);
        mergeHead = merge(start, ss);
    }
    return mergeHead;
}
