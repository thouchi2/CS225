/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    Node *temp = t->right;
    t->right = temp->left;
    temp->left = t;
    t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;
    temp->height = max(heightOrNeg1(temp->left), heightOrNeg1(temp->right))+1;
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    Node *temp = t->left;
    t->left = temp->right;
    temp->right = t;
    t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;
    temp->height = max(heightOrNeg1(temp->left), heightOrNeg1(temp->right))+1;
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
int AVLTree<K, V>::balance(Node*& subtree){
    if(subtree == NULL)
        return 0;
    int lHeight = heightOrNeg1(subtree->left);
    int rHeight = heightOrNeg1(subtree->right);
    return lHeight - rHeight;
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree == NULL)
        return;
    subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right))+1;
    int bal = balance(subtree);
    if(abs(bal) <= 1)
        return;
    if(bal < 0){
        if(balance(subtree->right) > 0)
            rotateRightLeft(subtree);
        else
            rotateLeft(subtree);
    }
    else{
        if(balance(subtree->left) < 0)
            rotateLeftRight(subtree);
        else
            rotateRight(subtree);
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL)
        subtree = new Node(key, value);
    else if(subtree->key == key)
        subtree->value = value;
    else if(key < subtree->key){
        insert(subtree->left, key, value);
        rebalance(subtree);
    }
    else{
        insert(subtree->right, key, value);
        rebalance(subtree);
    }
}

template <class K, class V>
typename AVLTree<K, V>::Node*& AVLTree<K, V>::getRight(Node*& subtree){
    if(subtree->right == NULL)
        return subtree;
    return getRight(subtree->right);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node *& IOP = getRight(subtree->left);
            swap(IOP, subtree);
            delete IOP;
            IOP = NULL;
        } else {
            /* one-child remove */
            // your code here
            Node* temp = subtree->right != NULL ? subtree->right : subtree->left;
            delete subtree;
            subtree = temp;
        }
        // your code here
        rebalance(subtree);
    }
}
