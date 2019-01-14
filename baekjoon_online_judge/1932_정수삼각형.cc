/*
1932 - 정수 삼각형

문제
        7
      3   8
    8   1   0
  2   7   4   4
4   5   2   6   5
위 그림은 크기가 5인 정수 삼각형의 한 모습이다.

맨 위층 7부터 시작해서 아래에 있는 수 중 하나를 선택하여 아래층으로 내려올 때, 
이제까지 선택된 수의 합이 최대가 되는 경로를 구하는 프로그램을 작성하라. 
아래층에 있는 수는 현재 층에서 선택된 수의 대각선 왼쪽 또는 대각선 오른쪽에 있는 것 중에서만 선택할 수 있다.
삼각형의 크기는 1 이상 500 이하이다. 삼각형을 이루고 있는 각 수는 모두 정수이며, 범위는 0 이상 9999 이하이다.

입력
첫째 줄에 삼각형의 크기 n(1 ≤ n ≤ 500)이 주어지고, 둘째 줄부터 n+1번째 줄까지 정수 삼각형이 주어진다.

출력
첫째 줄에 합이 최대가 되는 경로에 있는 수의 합을 출력한다.
*/

#include <iostream>
#include <vector>
//#include <string.h> //gcc memset

using namespace std;

int N = 0; //삼각형 크기
vector<int> triangle; //삼각형을 이루는 숫자들
vector<int> dp; //아래층으로 내려가면서 현재 인덱스에 대해 누적되온 최대 합계값
int answer = 0;

int _max(int a, int b)
{
	return (a > b) ? a : b;
}

int main()
{
	ios::sync_with_stdio(false);

	cin >> N;

	int k = 1;
	int m = 0;

	while (k <= N)
	{
		for (m = 0; m < k; ++m)
		{
			int input = 0;
			cin >> input;
			triangle.push_back(input);
		}

		k++;
	}

	dp.resize(triangle.size(), -1);

	//기저 : 크기가 1이면 숫자 1개만 들어옴
	if (N == 1)
		answer = triangle[0];
	else
	{
		//현재 층
		int k = 1;
		//현재 체크 중인 데이터 배열 인덱스
		int idx = 0;

		//dp 초기값
		dp[0] = triangle[0];

		//바로 아랫줄에 값을 채워넣기에 마지막 줄까지 루프를 돌리지 않는다.
		while (k < N)
		{
			//각 층마다 루프를 돌림
			for (m = 0; m < k; ++m)
			{
				//다음 층의 값을 더해가며 갱신한 최대값을 dp에 대입, 다음 층 계산에서 이용함
				//대각선 왼쪽 아래 체크
				dp[idx + k] = _max(dp[idx + k], dp[idx] + triangle[idx + k]);
				//대각선 오른쪽 아래 체크
				dp[idx + k + 1] = _max(dp[idx + k + 1], dp[idx] + triangle[idx + k + 1]);

				//최대값 갱신
				answer = _max(answer, dp[idx + k]);
				answer = _max(answer, dp[idx + k + 1]);

				++idx;
			}

			k++;
		}
	}

	cout << answer << '\n';
	return 0;
}