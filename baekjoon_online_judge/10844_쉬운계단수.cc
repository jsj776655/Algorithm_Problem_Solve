/*
10844 - 쉬운 계단수

문제
45656이란 수를 보자.
이 수는 인접한 모든 자리수의 차이가 1이 난다. 이런 수를 계단 수라고 한다.
세준이는 수의 길이가 N인 계단 수가 몇 개 있는지 궁금해졌다.
N이 주어질 때, 길이가 N인 계단 수가 총 몇 개 있는지 구하는 프로그램을 작성하시오. (0으로 시작하는 수는 없다.)

입력
첫째 줄에 N이 주어진다. N은 1보다 크거나 같고, 100보다 작거나 같은 자연수이다.

출력
첫째 줄에 정답을 1,000,000,000으로 나눈 나머지를 출력한다.
*/

#include <iostream>
#include <string.h> //gcc memset

using namespace std;

unsigned long long N = 0; //주어진 길이 N
unsigned long long dp[102][10]; //dp[x][y] 라 할 때, x = (자리수), y = (자리수 x에 온 숫자) 에 대한 계단수를 저장 
unsigned long long answer = 0; //정답

//문제 풀이 함수
//_n : 현재 계산중인 자리수
//_currNum : 자리수 _n에 오는 숫자
unsigned long long solve(unsigned long long _n, unsigned long long _currNum)
{
	//자리수가 1씩 줄어들면서 계산함
	if (_n <= 0)
		return 0;
	//최고 자리수일 때 0이 올 수 없다
	if (_n == N && _currNum == 0)
		return 0;
	//이미 계산된 자리수에 대한 숫자의 계단수가 있음 그걸 리턴
	if (dp[_n][_currNum] > 0)
		return dp[_n][_currNum];

	//다음 자리수에 오는 숫자가 현재 숫자에서 1을 더하거나 1을 뺀 경우의 수를 구함 
	if(_currNum < 9)
		dp[_n][_currNum] += (solve(_n - 1, _currNum + 1) % 1000000000);
	if(_currNum > 0)
		dp[_n][_currNum] += (solve(_n - 1, _currNum - 1) % 1000000000);

	//마지막에 저장된 횟수 리턴
	return dp[_n][_currNum];
}

int main()
{
	ios::sync_with_stdio(false);

	cin >> N;
	memset(dp, 0, sizeof(unsigned long long) * 102 * 10);

	//1자리 일 때 (0~9) 경우의 수를 미리 구함
	int k = 0;
	for(k = 0; k <= 9; ++k)
		dp[1][k] = 1;

	//각 자리에 오는 숫자 0~9까지 경우의 수를 나누어 구하고 리턴된 횟수를 더함
	for (k = 0; k <= 9; ++k)
		answer += solve(N, k);

    //답으로 나온 값이 10억을 넘길 수 있으므로 여기서도 나머지 구함
	cout << answer % 1000000000 << '\n';
	return 0;
}