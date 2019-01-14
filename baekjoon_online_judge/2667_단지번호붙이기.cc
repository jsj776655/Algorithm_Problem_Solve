/*
2667 - 단지번호 붙이기

문제
정사각형 모양의 지도가 있다. 
1은 집이 있는 곳을, 0은 집이 없는 곳을 나타낸다. 
철수는 이 지도를 가지고 연결된 집들의 모임인 단지를 정의하고, 단지에 번호를 붙이려 한다. 
여기서 연결되었다는 것은 어떤 집이 좌우, 혹은 아래위로 다른 집이 있는 경우를 말한다. 
대각선상에 집이 있는 경우는 연결된 것이 아니다.
지도를 입력하여 단지수를 출력하고,
각 단지에 속하는 집의 수를 오름차순으로 정렬하여 출력하는 프로그램을 작성하시오.

입력
첫 번째 줄에는 지도의 크기 N(정사각형이므로 가로와 세로의 크기는 같으며 5≤N≤25)이 입력되고, 
그 다음 N줄에는 각각 N개의 자료(0혹은 1)가 입력된다.

출력
첫 번째 줄에는 총 단지수를 출력하시오. 
그리고 각 단지내 집의 수를 오름차순으로 정렬하여 한 줄에 하나씩 출력하시오.

예제 입력 1 
7
0110100
0110101
1110101
0000111
0100000
0111110
0111000

예제 출력 1 
3
7
8
9

*/

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>  // std::sort
//#include <string.h> //gcc memset

using namespace std;

int N = 0; //지도의 크기
int mapData[26][26]; //지도

queue< pair<int, int> > searchQ; //단지 영역을 찾기 위한 큐
vector<int> answers; //단지 별 집의 수 저장

//오름차순 비교 함수
bool comp(int a, int b) { return (a < b); }

void searchArea(int _x, int _y)
{
	int currAnswer = 0;
	
	//최초 검사 지점 큐에 넣기
	searchQ.push(pair<int, int>(_x, _y));
	mapData[_y][_x] += (answers.size() + 1);
	currAnswer++;

	//연결된 집 체크
	while (!searchQ.empty())
	{
		pair<int, int> currHouse = searchQ.front();
		searchQ.pop();

		//왼쪽 체크
		if (currHouse.first - 1 >= 0 && currHouse.first - 1 < N &&
			mapData[currHouse.second][currHouse.first - 1] == 1)
		{
			mapData[currHouse.second][currHouse.first - 1] += (answers.size() + 1);
			currAnswer++;

			searchQ.push(pair<int, int>(currHouse.first - 1, currHouse.second));
		}
		//오른쪽 체크
		if (currHouse.first + 1 >= 0 && currHouse.first + 1 < N &&
			mapData[currHouse.second][currHouse.first + 1] == 1)
		{
			mapData[currHouse.second][currHouse.first + 1] += (answers.size() + 1);
			currAnswer++;

			searchQ.push(pair<int, int>(currHouse.first + 1, currHouse.second));
		}
		//위쪽 체크
		if (currHouse.second - 1 >= 0 && currHouse.second - 1 < N &&
			mapData[currHouse.second - 1][currHouse.first] == 1)
		{
			mapData[currHouse.second - 1][currHouse.first] += (answers.size() + 1);
			currAnswer++;

			searchQ.push(pair<int, int>(currHouse.first, currHouse.second - 1));
		}
		//아래쪽 체크
		if (currHouse.second + 1 >= 0 && currHouse.second + 1 < N &&
			mapData[currHouse.second + 1][currHouse.first] == 1)
		{
			mapData[currHouse.second + 1][currHouse.first] += (answers.size() + 1);
			currAnswer++;

			searchQ.push(pair<int, int>(currHouse.first, currHouse.second + 1));
		}
	}

	//현재 구한 단지의 집 수 저장
	answers.push_back(currAnswer);
}

int main()
{
	//ios::sync_with_stdio(false);

	scanf("%d", &N);

	int x = 0; int y = 0;
	for (y = 0; y < N; ++y)
		for (x = 0; x < N; ++x)
			scanf("%1d", &mapData[y][x]);

	for(y = 0; y < N; ++y)
		for(x = 0; x < N; ++x)
		{
			//방문할 때 mapData 배열 값을 2,3,4... 이런식으로 갱신할 것임
			//현재 순회하는 칸이 1이면 방문하지 않은 것이니 단지 체크하기
			if (mapData[y][x] == 1)
				searchArea(x, y);
		}

	//구한 단지의 집 갯수를 오름차순 정렬
	std::sort(answers.begin(), answers.end(), comp);

	//단지 갯수와 각 단지의 집 갯수 출력 
	printf("%d\n", answers.size());
	for (auto k : answers)
		printf("%d\n", k);

	return 0;
}