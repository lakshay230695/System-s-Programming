//structure definition
struct fileNode
{
	char* path;
	struct fileNode* next;
};

typedef struct fileNode fileNode;

struct countNode_ {
	int count;
	char* filepath;
};

typedef struct countNode_ countNode;

struct treeNode_ {
	int count;
	int isWord;
	int level;
	char data;
	struct treeNode_* next[36];
	struct treeNode_* parent;
	countNode** countarr; //word counts for files

};

typedef struct treeNode_ treeNode;

//var declarations
int wordcount; //global word count
int filecount; //global file count
int fWordCount; //word count for a specific file
fileNode* fileRoot; //file path linked list root
fileNode* fileTemp; //for traversing the file path linked list

//func prototype declarations
int dircheck(char* filepath);
int filecall(char* path, int fileindex);
void directcall(char* filepath);
fileNode* buildFileNode(char* path);
void buildFileLL(char* path);
void addFileLL();
void writeCounts(char* writepath);
int treeDFS(treeNode* scout,char* buffer,int* index, FILE* target);
int countNodeCompare(const void* a, const void* b);
void mergeSort(countNode** countarr, int lo, int hi);
void merge(countNode** countarr, int lo, int mid, int hi);
void writeBot(treeNode* scout, char* buffer, FILE* target);
treeNode* root; //root of tree
int maxlen;
int add(char toadd,treeNode* parent);
void insert(treeNode* toinsert,treeNode* parent);
void deleteOne(treeNode* todelete);
void deleteTree(treeNode* parent);
treeNode* buildNode(char data,int isWord,int level);
countNode* buildCountNode(char* path);
int buildTree(char* input, size_t size, int filecount, int fileindex, char* path);
void printTree(treeNode* parent);
int traverseTree(treeNode* parent);