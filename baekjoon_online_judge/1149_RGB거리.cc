/*
1149 - RGB거리

문제
RGB거리에 사는 사람들은 집을 빨강, 초록, 파랑중에 하나로 칠하려고 한다. 
또한, 그들은 모든 이웃은 같은 색으로 칠할 수 없다는 규칙도 정했다. 집 i의 이웃은 집 i-1과 집 i+1이다.
각 집을 빨강으로 칠할 때 드는 비용, 초록으로 칠할 때 드는 비용, 파랑으로 드는 비용이 주어질 때, 
모든 집을 칠할 때 드는 비용의 최솟값을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 집의 수 N이 주어진다. N은 1,000보다 작거나 같다. 
둘째 줄부터 N개의 줄에 각 집을 빨강으로 칠할 때, 초록으로 칠할 때, 파랑으로 칠할 때 드는 비용이 주어진다. 
비용은 1,000보다 작거나 같은 자연수이다.

출력
첫째 줄에 모든 집을 칠할 때 드는 비용의 최솟값을 출력한다.
*/

#include <iostream>
//#include <string.h> //gcc memset

using namespace std;


/*
DP(x, y) = x 번째 집에서 색깔 y를 택할 때 칠하는 최소 비용
예를 들어 DP(x, R) 의 하위 문제는 DP(x + 1, G), DP(x + 1, B) 가 됨

이런식으로 DP(x, R), DP(x, G), DP(x, B) 를 구하여 이 중 최소값을 구하면 될 듯

실제 DP 저장할 구조를 2차원 배열로 하면 어떨까?
int DP[(집 번호)][(색깔)] = 해당 집에서 해당 색깔을 칠했을 때 첫 번째 집부터 누적해온 최소 비용
*/

int cost[1001][3]; //집에서 각 색깔 별로 칠할 때의 비용
int dp[1001][3]; //[(집 번호)][(색깔 수)] 현재 집에서 어떤 색을 칠했을 때 누적해온 최소 비용
int houseNum = 0;
int answer = 0;

int k = 0;
int m = 0;

enum COLOR
{
	RED = 0,
	GREEN,
	BLUE,
};

int _min(int a, int b)
{
	return (a > b) ? b : a;
}

int _max(int a, int b)
{
	return (a > b) ? a : b;
}

int main()
{
	ios::sync_with_stdio(false);

	//집의 수
	cin >> houseNum;

	//각 집에서 색깔 별 비용
	//dp 배열은 0으로 초기 세팅
	for (k = 0; k < houseNum; ++k)
	{
		cin >> cost[k][RED] >> cost[k][GREEN] >> cost[k][BLUE];
		dp[k][RED] = dp[k][GREEN] = dp[k][BLUE] = 0;
	}

	//문제 풀기
	{
		for (k = 0; k < houseNum; ++k)
		{
			for (m = 0; m <= BLUE; ++m)
			{
                //최초 집에서는 DP 값을 바로 대입
				if (k == 0)
				{
					dp[k][m] = cost[k][m];
				}
				else
				{
                    //각 색깔별로 이전 집에 구한 DP를 더한것 중 최소값 현재 집의 DP을 더해준다
					if (m == RED)
						dp[k][m] += _min(cost[k][m] + dp[k - 1][GREEN], cost[k][m] + dp[k - 1][BLUE]);
					else if (m == GREEN)
						dp[k][m] += _min(cost[k][m] +  dp[k - 1][RED], cost[k][m] + dp[k - 1][BLUE]);
					else
						dp[k][m] += _min(cost[k][m] + dp[k - 1][RED], cost[k][m] + dp[k - 1][GREEN]);
				}
			}
		}

        //마지막에는 DP 배열에 저장된 세 색깔의 값 중 최소값을 찾으면 그것이 답
		answer = _min(dp[houseNum - 1][RED], dp[houseNum - 1][GREEN]);
		answer = _min(answer, dp[houseNum - 1][BLUE]);
	}

	cout << answer << '\n';

	return 0;
}