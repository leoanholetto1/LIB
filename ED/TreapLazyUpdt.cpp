//mudar

struct node {
    node *left, *right;
    int weight, size,flip,mn;
    int value;
    node(int v) {
        left = right = NULL;
        weight = rand();
        size = 1;
        value = v;
		flip=0;
		mn = v;
    }
};
//Complexidade: O(1)
int size(node *treap) {
    if (treap == NULL) return 0;
    return treap->size;
}
//Complexidade: O(log n)
void push(node *treap){
	if(treap!=NULL && treap->flip){
		treap->flip=0;
		swap(treap->left,treap->right);
		if(treap->left!=NULL) treap->left->flip^=1;
		if(treap->right!=NULL) treap->right->flip^=1;
	}
}
//Complexidade: O(log n) 
void split(node *treap, node *&left, node *&right, int k) {
    if (treap == NULL) {
        left = right = NULL;
    } 
    else {
		push(treap);
        if (size(treap->left) < k) {
            split(treap->right, treap->right, right, k - size(treap->left)-1);
            left = treap;
			treap->mn = treap->value;
			if(treap->left!=NULL) treap->mn = min(treap->mn,treap->left->mn);
			if(treap->right!=NULL) treap->mn = min(treap->mn,treap->right->mn);
        } 
        else {
            split(treap->left, left, treap->left, k);
            right = treap;
			treap->mn = treap->value;
			if(treap->left!=NULL) treap->mn = min(treap->mn,treap->left->mn);
			if(treap->right!=NULL) treap->mn = min(treap->mn,treap->right->mn);
        }
        treap->size = size(treap->left) + size(treap->right) + 1;
    }
}
//Complexidade: O(log n) 
void merge(node *&treap, node *left, node *right) {
    if (left == NULL) treap = right;
    else if(right == NULL) treap = left;
    else {
		push(left);
		push(right);
        if (left->weight < right->weight) {
            merge(left->right, left->right, right);
            treap = left;
			treap->mn = treap->value;
			if(treap->left!=NULL) treap->mn = min(treap->mn,treap->left->mn);
			if(treap->right!=NULL) treap->mn = min(treap->mn,treap->right->mn);
        } 
        else {
            merge(right->left, left, right->left);
            treap = right;
			treap->mn = treap->value;
			if(treap->left!=NULL) treap->mn = min(treap->mn,treap->left->mn);
			if(treap->right!=NULL) treap->mn = min(treap->mn,treap->right->mn);
        }   
        treap->size = size(treap->left) + size(treap->right) + 1;
    }
}
//Complexidade: O(log n)
int menor(node *treap){
	if(treap==NULL) return 0;
	push(treap);
	if(treap->size==1) return 1;
	if(treap->value == treap->mn) return size(treap->left)+1;
	if(treap->left!=NULL && treap->left->mn == treap->mn) return menor(treap->left);
	return menor(treap->right) + size(treap->left) + 1;
}

split(treap, A, B, i - 1);
int pos = menor(B)+i-1;
split(B, D, C, pos - i + 1);
D->flip^=1;//inverte
merge(treap, A, D);
merge(treap, treap, C);