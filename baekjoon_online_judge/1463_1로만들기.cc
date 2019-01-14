/*
1463 - 1로 만들기

문제
정수 X에 사용할 수 있는 연산은 다음과 같이 세 가지 이다.

X가 3으로 나누어 떨어지면, 3으로 나눈다.
X가 2로 나누어 떨어지면, 2로 나눈다.
1을 뺀다.
정수 N이 주어졌을 때, 위와 같은 연산 세 개를 적절히 사용해서 1을 만들려고 한다. 연산을 사용하는 횟수의 최솟값을 출력하시오.

입력
첫째 줄에 1보다 크거나 같고, 10^6보다 작거나 같은 정수 N이 주어진다.

출력
첫째 줄에 연산을 하는 횟수의 최솟값을 출력한다.
*/

#include <iostream>
#include <string.h> //gcc memset

using namespace std;

int N = 0; //주어진 정수
int dp[1000001];
int answer = 0; //정답

//문제 푸는 함수
//-1, /2, /3을 각각 연산함에 대한 최소 횟수를 계산하여 DP에 저장, 재사용함
int solve(int _n)
{
	if (_n == 1)
		return 0;
	if (dp[_n] > 0)
		return dp[_n];

	//-1 연산
	dp[_n] = solve(_n - 1) + 1;

	int temp = 0;

	// /2 연산
	if (_n % 2 == 0)
	{
		temp = solve(_n / 2) + 1;
		//현재 dp값이 해당 연산한 것의 최소 연산횟수보다 작으면 갱신
		if (dp[_n] > temp)
			dp[_n] = temp;
	}
	// /3 연산
	if (_n % 3 == 0)
	{
		temp = solve(_n / 3) + 1;
		if (dp[_n] > temp)
			dp[_n] = temp;
	}

	return dp[_n];
}

int main()
{
	ios::sync_with_stdio(false);

	cin >> N;
	memset(dp, 0, sizeof(int) * 1000001);

	//재귀와 DP를 활용하여 문제를 품
	answer = solve(N);
	
	cout << answer << '\n';
	return 0;
}