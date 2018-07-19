
#include<iostream>
#include<fstream>
using namespace std;

class listBinTreeNode {
	private:
		string chStr;
		int prob;
		listBinTreeNode* next = NULL;
		listBinTreeNode* left = NULL;
		listBinTreeNode* right = NULL;
	
	public:
		listBinTreNode(){
		}
		
		listBinTreeNode(string c, int p){
			chStr = c;
			prob = p;
		}
		
		void printNode(ofstream& out){//to print newnode constructed from first and second
			out<<"Node: "<<prob<<"("<<chStr<<") ";
			if(next != NULL){
				out<<"nextString("<<next->getChStr()<<") ";
			}
			else
				out<<"nextString(NULL) ";
			out<<"leftString("<<left->getChStr()<<") rightString("<<right->getChStr()<<")"<<endl;
			
		}
		
		string getChStr(){
			return chStr;
		}
		
		int getProb(){
			return prob;
		}
		
		listBinTreeNode* getNext(){
			return next;
		}
		
		listBinTreeNode* getLeft(){
			return left;
		}
		
		listBinTreeNode* getRight(){
			return right;
		}
		
		void setNext(listBinTreeNode* n){
			next = n;
		}
		
		void setLeft(listBinTreeNode* l){
			left = l;
		}
		
		void setRight(listBinTreeNode* r){
			right = r;
		}
};

class HuffmanLinkedList{
	private:
		listBinTreeNode* listHead;
		listBinTreeNode* oldListHead;
		int size;
		
	public:
		HuffmanLinkedList(){
			listHead = new listBinTreeNode("dummy", 0);
			oldListHead = new listBinTreeNode("dummy", 0);
			size = 0;
		}
		
		listBinTreeNode* findSpot(int p){
			listBinTreeNode* current = listHead;
			listBinTreeNode* spot = current;
			
			while(current != NULL){
				if(current->getProb() < p){
					spot = current;
					current = current->getNext();
				}
				else
					break;
			}
			return spot;
		}
		
		void listInsert(listBinTreeNode* location, listBinTreeNode* node){
			if(location->getNext() == NULL){
				location->setNext(node);
			}
			else{
				listBinTreeNode* temp = location->getNext();
				location->setNext(node);
				node->setNext(temp);
			}
		}
		
		void printList(listBinTreeNode* head, ofstream& out3){
			listBinTreeNode* current = head;
			
			out3<<"ListHead-->";
			while(current->getNext() != NULL){
				out3<<"("<<current->getChStr()<<", "<<current->getProb()<<", "<<current->getNext()->getChStr()<<")-->";
				current = current->getNext();
			}
			out3<<"("<<current->getChStr()<<", "<<current->getProb()<<", NULL)-->NULL"<<endl;;
		}
		
		isEmpty(){
			if(size==0){
				return true;
			}
		}
		
		listBinTreeNode* getHead(){
			return listHead;
		}
		
		listBinTreeNode* getOldHead(){
			return oldListHead;
		}
		
		listBinTreeNode* setHead(listBinTreeNode* h){
			listHead = h;
		}
		
};

class HuffmanBinaryTree{
	private:
		listBinTreeNode* root = NULL;
		
	public:
		HuffmanBinaryTree(){
		}
		
		void expandList(HuffmanLinkedList list, ofstream& out3){
			listBinTreeNode* first = list.getHead()->getNext();											//point to first node
			listBinTreeNode* second;
			listBinTreeNode* newNode;
			listBinTreeNode* spot;
			string concatenation;
			int sum;
			out3<<endl;
			
			while(first->getNext() != NULL){															//while first is not the last node
				second = first->getNext();
				sum = first->getProb() + second->getProb();
				concatenation = first->getChStr() + second->getChStr();
				newNode = new listBinTreeNode(concatenation, sum);
				newNode->setLeft(first);
				newNode->setRight(second);
				spot = list.findSpot(sum);
				list.listInsert(spot, newNode);
				newNode->printNode(out3);
				list.printList(list.getOldHead(), out3);
				out3<<endl;
				list.setHead(second->getNext());
				first = list.getHead();
			}
			root = first;
		}
		
		void constructCharCode(listBinTreeNode* T, string code, ofstream& out1){						//to output code of leaves
			if(T == NULL){
				return;
			}
			else if(T->getLeft() == NULL && T->getRight() == NULL){										//if T is a leaf, output charString and code
				out1<<T->getChStr()<<" "<<code<<endl;;
			}
			else												  										//keep searching until leaf is reached
				constructCharCode(T->getLeft(), code+"0", out1);
				constructCharCode(T->getRight(), code+"1", out1);
		}
		
		void preOrder(listBinTreeNode* T, ofstream& out2){
			if(T->getLeft() == NULL && T->getRight() == NULL){	  										//if it's leaf node, just output
				//T->printNode(out2); this crashes the program, dont know why...
				out2<<T->getProb()<<"\t"<<T->getChStr()<<endl;
			}
			else{
				//T->printNode(out2); this crashes the program, dont know why...
				out2<<T->getProb()<<"\t"<<T->getChStr()<<endl;
				preOrder(T->getLeft(), out2);
				preOrder(T->getRight(), out2);
			}
		}
		
		listBinTreeNode* getRoot(){
			return root;
		}
		
};

int main(int argc, char** argv){
	ifstream inFile;
	ofstream outFile1;
	ofstream outFile2;
	ofstream outFile3;
	inFile.open(argv[1]);
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);
	outFile3.open(argv[4]);
	string ch;
	int p;
	listBinTreeNode* spot;
	listBinTreeNode* newNode;
	string empty = "";
	
	HuffmanLinkedList HLL;
	HuffmanBinaryTree HBT;
	
	//check the number of arguments
	if (argc != 5) {																
        cerr << "Error: Number of arguments unsatisfied."<<endl;
        exit(1);
    }
	
	while(inFile>>ch && inFile>>p){									//construct the Huffman LinkedList
		spot = HLL.findSpot(p);
		newNode = new listBinTreeNode(ch, p);
		HLL.listInsert(spot, newNode);
		HLL.printList(HLL.getHead(), outFile3);
	}

	HLL.getOldHead()->setNext(HLL.getHead()->getNext());
	HBT.expandList(HLL, outFile3);
	HBT.constructCharCode(HBT.getRoot(), empty, outFile1);
	HBT.preOrder(HBT.getRoot(), outFile2);

	inFile.close();
	outFile1.close();
	outFile2.close();
	outFile3.close();
	
	return 0;
}
