struct node {
    node *left, *right;
    int weight, size;
    char value;
    node(char v) {
        left = right = NULL;
        weight = rand();
        size = 1;
        value = v;
    }
};
//Complexidade: O(1)
int size(node *treap) {
    if (treap == NULL) return 0;
    return treap->size;
}
//Complexidade: O(log n)
void split(node *treap, node *&left, node *&right, int k) {
    if (treap == NULL) {
        left = right = NULL;
    } 
    else {
        if (size(treap->left) < k) {
            split(treap->right, treap->right, right, k - size(treap->left)-1);
            left = treap;
        } 
        else {
            split(treap->left, left, treap->left, k);
            right = treap;
        }
        treap->size = size(treap->left) + size(treap->right) + 1;
    }
}
//Complexidade: O(log n)
void merge(node *&treap, node *left, node *right) {
    if (left == NULL) treap = right;
    else if(right == NULL) treap = left;
    else {
        if (left->weight < right->weight) {
            merge(left->right, left->right, right);
            treap = left;
        } 
        else {
            merge(right->left, left, right->left);
            treap = right;
        }   
        treap->size = size(treap->left) + size(treap->right) + 1;
    }
}
//Complexidade: O(n)
void print(node *treap) {
    if (treap == NULL) return;
    print(treap->left);
    cout << treap->value;
    print(treap->right);
}

merge(treap, treap, new node(s[i]));
split(treap, A, B, x - 1);
split(B, D, C, y - x + 1);
merge(treap, A, C);
merge(treap, treap, D);
