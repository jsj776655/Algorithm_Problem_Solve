/*
1991 - 트리 순회

문제
이진 트리를 입력받아 전위 순회(preorder traversal), 중위 순회(inorder traversal), 후위 순회(postorder traversal)한 결과를 
출력하는 프로그램을 작성하시오.

입력
첫째 줄에는 이진 트리의 노드의 개수 N(1≤N≤26)이 주어진다. 
둘째 줄부터 N개의 줄에 걸쳐 각 노드와 그의 왼쪽 자식 노드, 오른쪽 자식 노드가 주어진다. 
노드의 이름은 A부터 차례대로 영문자 대문자로 매겨지며, 항상 A가 루트 노드가 된다. 
자식 노드가 없는 경우에는 .으로 표현된다.

출력
첫째 줄에 전위 순회, 둘째 줄에 중위 순회, 셋째 줄에 후위 순회한 결과를 출력한다. 
각 줄에 N개의 알파벳을 공백 없이 출력하면 된다.
*/

#include <iostream>
#include <string.h> //gcc memset
using namespace std;

//노드 구조체
struct node
{
	char value;
	node* left;
	node* right;

	node()
	: value(0), left(nullptr), right(nullptr)
	{}

	~node()
	{
		delete left;
		delete right;
	}
};

int N = 0; //노드 갯수 (1 <= N <= 26)
node* rootNode = nullptr; //루트 노드
node* indexArray[27]; //각 알파벳 별 노드 (생성되어 있는지 확인 용도)

//전위 순회
void preOrder(node* root)
{
	if (root == 0)
		return;

	cout << root->value;
	if(root->left) preOrder(root->left);
	if(root->right) preOrder(root->right);
}

//중위 순회
void inOrder(node* root)
{
	if (root == 0)
		return;

	if (root->left) inOrder(root->left);
	cout << root->value;
	if (root->right) inOrder(root->right);
}

//후위 순회
void postOrder(node* root)
{
	if (root == 0)
		return;

	if (root->left) postOrder(root->left);
	if (root->right) postOrder(root->right);
	cout << root->value;
}

int main()
{
	ios::sync_with_stdio(false);

	cin >> N;
	memset(indexArray, 0, sizeof(node*) * 27);

	//트리 구성하기
	//루트 노드 먼저 세팅
	rootNode = new node();
	rootNode->value = 'A';
	indexArray[0] = rootNode;

	int k = 0;
	for (k = 0; k < N; ++k)
	{
		char val = 0;
		char left = 0;
		char right = 0;

		cin >> val >> left >> right;

		//indexArray 상에서 인덱스 구하기
		int nodeIdx = (int)(val - 'A');

		//해당 알파벳에 노드 할당되어 있는지 체크
		node* pNode = indexArray[nodeIdx];
		if (pNode == 0)
		{
			pNode = new node();
			pNode->value = val;
		}

		//자식으로 '.' 문자가 온 것이 아니면 노드 생성하여 연결
		if (left != '.' && indexArray[left - 'A'] == 0)
		{
			indexArray[left - 'A'] = new node();
			indexArray[left - 'A']->value = left;

			pNode->left = indexArray[left - 'A'];
		}

		if (right != '.' && indexArray[right - 'A'] == 0)
		{
			indexArray[right - 'A'] = new node();
			indexArray[right - 'A']->value = right;

			pNode->right = indexArray[right - 'A'];
		}
	}

	//트리 순회하기
	preOrder(rootNode);
	cout << '\n';
	inOrder(rootNode);
	cout << '\n';
	postOrder(rootNode);
	cout << '\n';
	
	delete rootNode;
	return 0;
}