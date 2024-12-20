const int ALPHABET_SIZE = 26;
struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
};
struct TrieNode* getNode(void){
    struct TrieNode* pNode = new TrieNode;
    pNode->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
    return pNode;
}
//Complexidade: O(n)
void insert(struct TrieNode* root, string key){
    struct TrieNode* pCrawl = root;
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
        pCrawl = pCrawl->children[index];
    }
    pCrawl->isEndOfWord = true;
}
//Complexidade: O(n)
bool search(struct TrieNode* root, string key){
    struct TrieNode* pCrawl = root;
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return false;
        pCrawl = pCrawl->children[index];
    }
    return (pCrawl != NULL && pCrawl->isEndOfWord);
}
bool isEmpty(TrieNode* root){
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}
//Complexidade: O(n)
TrieNode* remove(TrieNode* root, string key, int depth = 0){
    if (!root)
        return NULL;
    if (depth == key.size()) {
        if (root->isEndOfWord)
            root->isEndOfWord = false;
        if (isEmpty(root)) {
            delete (root);
            root = NULL;
        }
        return root;
    }
    int index = key[depth] - 'a';
    root->children[index] = 
        remove(root->children[index], key, depth + 1);
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = NULL;
    }
    return root;
}
int main(){
    struct TrieNode* root = getNode();
    for (int i = 0; i < n; i++)
        insert(root, keys[i]);
    search(root, "the");
    search(root, "these");
    remove(root, "heroplane");
    search(root, "hero");
    return 0;
}