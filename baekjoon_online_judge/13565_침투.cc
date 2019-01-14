/*
13565 - 침투

시간 제한	1 초
메모리 제한	 512 MB

문제
인제대학교 생화학연구실에 재직중인 석교수는 전류가 침투(percolate) 할 수 있는 섬유 물질을 개발하고 있다. 
이 섬유 물질은 2차원 M × N 격자로 표현될 수 있다. 
편의상 2차원 격자의 위쪽을 바깥쪽(outer side), 아래쪽을 안쪽(inner side)라고 생각하기로 한다. 
또한 각 격자는 검은색 아니면 흰색인데, 검은색은 전류를 차단하는 물질임을 뜻하고 흰색은 전류가 통할 수 있는 물질임을 뜻한다. 
전류는 섬유 물질의 가장 바깥쪽 흰색 격자들에 공급되고, 이후에는 상하좌우로 인접한 흰색 격자들로 전달될 수 있다.
김 교수가 개발한 섬유 물질을 나타내는 정보가 2차원 격자 형태로 주어질 때, 
바깥쪽에서 흘려 준 전류가 안쪽까지 침투될 수 있는지 아닌지를 판단하는 프로그램을 작성하시오.


입력
첫째 줄에는 격자의 크기를 나타내는  M (2 ≤ M ≤ 1,000) 과 N (2 ≤ N ≤ 1,000) 이 주어진다. 
M줄에 걸쳐서, N개의 0 또는 1 이 공백 없이 주어진다. 0은 전류가 잘 통하는 흰색, 1은 전류가 통하지 않는 검은색 격자임을 뜻한다.

출력
바깥에서 흘려준 전류가 안쪽까지 잘 전달되면 YES를 출력한다.
그렇지 않으면 NO를 출력한다.

예제 입력 1 
5 6
010101
010000
011101
100011
001011
예제 출력 1 
NO

예제 입력 2 
8 8
11000111
01100000
00011001
11001000
10001001
10111100
01010000
00001011
예제 출력 2 
YES
*/

#include <iostream>
#include <queue>
#include <string.h> //gcc memset declare

using namespace std;

int M = 0;
int N = 0;

char clothMap[1001][1001]; //섬유 물질 격자
char checkMap[1001][1001]; //임시 기록 배열, 탐색하면서 이미 침투된 칸인지 기록함

struct node
{
	int x;
	int y;

	node(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};

void ResetCheckMap()
{
	memset(checkMap, 0, sizeof(char) * 1001 * 1001);
}

bool solve()
{
	//맨 위의 줄의 칸들 부터 큐에 삽입
	for (int _x = 0; _x < N; ++_x)
	{
		//각 맨위의 칸들을 시작점으로 맨 아래까지 침투하는 지 체크해본다.
		if (clothMap[0][_x] == '0')
		{
			int startX = _x;
			int startY = 0;

			queue<node> bfsQ;

			//시작점 삽입
			bfsQ.push(node(startX, startY));
			checkMap[startY][startX] = '1';
			//printf("************************************\n");
			//printf("startX : %d, startY : %d \n", startX, startY);

			while (1)
			{
				bool bUp = false;
				bool bDown = false;
				bool bLeft = false;
				bool bRight = false;

				//이동 가능한 칸을 큐에 넣고 하나씩 pop해서 방향 별로 체크한다.
				node popNode = bfsQ.front();
				bfsQ.pop();

				//만약 맨 밑까지 내려갔다면 침투가 잘 되었다는 것으로 바로 끝냄
				if (popNode.y == M - 1)
					return true;

				//Up 체크
				if (popNode.y - 1 >= 0 && clothMap[popNode.y - 1][popNode.x] == '0' && checkMap[popNode.y - 1][popNode.x] != '1')
				{
					bUp = true;
					bfsQ.push(node(popNode.x, popNode.y - 1));
					checkMap[popNode.y - 1][popNode.x] = '1';
					//printf("x : %d, y : %d \n", popNode.x, popNode.y - 1);
				}
				//Down 체크
				if (popNode.y + 1 < M && clothMap[popNode.y + 1][popNode.x] == '0' && checkMap[popNode.y + 1][popNode.x] != '1')
				{
					bDown = true;
					bfsQ.push(node(popNode.x, popNode.y + 1));
					checkMap[popNode.y + 1][popNode.x] = '1';
					//printf("x : %d, y : %d \n", popNode.x, popNode.y + 1);
				}
				//Left 체크
				if (popNode.x - 1 >= 0 && clothMap[popNode.y][popNode.x - 1] == '0' && checkMap[popNode.y][popNode.x - 1] != '1')
				{
					bLeft = true;
					bfsQ.push(node(popNode.x - 1, popNode.y));
					checkMap[popNode.y][popNode.x - 1] = '1';
					//printf("x : %d, y : %d \n", popNode.x - 1, popNode.y);
				}
				//Right 체크
				if (popNode.x + 1 < N && clothMap[popNode.y][popNode.x + 1] == '0' && checkMap[popNode.y][popNode.x + 1] != '1')
				{
					bRight = true;
					bfsQ.push(node(popNode.x + 1, popNode.y));
					checkMap[popNode.y][popNode.x + 1] = '1';
					//printf("x : %d, y : %d \n", popNode.x + 1, popNode.y);
				}

				//만약 현재 노드에서 더 이상 갈 곳이 없고
				//큐가 비어있으면 루프 빠져나옴
				if (bfsQ.empty() && !bUp && !bDown && !bLeft && !bRight)
					break;
			}
		}

		//임시 기록 배열 리셋
		ResetCheckMap();
	}

	return false;
}

int main()
{
	cin >> M;
	cin >> N;

	int x, y;
	std::cin.width(1);
	for (y = 0; y < M; ++y)
		for (x = 0; x < N; ++x)
			cin >> clothMap[y][x];

	bool bAnswer = solve();

	if (bAnswer)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

    return 0;
}