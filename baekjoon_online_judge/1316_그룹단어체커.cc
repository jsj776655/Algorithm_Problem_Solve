/*
1316 - 그룹 단어 체커

문제
그룹 단어란 단어에 존재하는 모든 문자에 대해서, 각 문자가 연속해서 나타나는 경우만을 말한다. 
예를 들면, ccazzzzbb는 c, a, z, b가 모두 연속해서 나타나고, kin도 k, i, n이 연속해서 나타나기 때문에 그룹 단어이지만, 
aabbbccb는 b가 떨어져서 나타나기 때문에 그룹 단어가 아니다.
단어 N개를 입력으로 받아 그룹 단어의 개수를 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 단어의 개수 N이 들어온다. N은 100보다 작거나 같은 자연수이다. 
둘째 줄부터 N개의 줄에 단어가 들어온다. 단어는 알파벳 소문자로만 되어있고 중복되지 않으며, 길이는 최대 100이다.

출력
첫째 줄에 그룹 단어의 개수를 출력한다.

예제 입력 1 
3
happy
new
year
예제 출력 1 
3

예제 입력 2 
4
aba
abab
abcabc
a
예제 출력 2 
1
*/

#include <iostream>
#include <cmath>
#include <string.h> //gcc memset 

using namespace std;

int N = 0; //입력 단어 갯수
int answer = 0; //답, 그룹 단어의 갯수
int lastIdxArray[26]; //해당 알파벳 문자가 마지막으로 온 인덱스를 저장하는 배열
char word[101]; //현재 단어

int main()
{
	cin >> N;
	while (N > 0)
	{
		memset(word, 0, 101);
		memset(lastIdxArray, -1, sizeof(int) * 26);

		cin >> word;
		//그룹 단어인지 체크하는 플래그
		bool bGroupWord = true;

		for (int k = 0; word[k] != 0; ++k)
		{
			//문자 하나마다 순차적으로 검사 진행
			int alphaIdx = word[k] - 'a';
			//해당 문자가 처음인 경우 인덱스 배열에 현재 인덱스 삽입
			if (lastIdxArray[alphaIdx] == -1)
				lastIdxArray[alphaIdx] = k;
			else
			{
				//해당 알파벳이 마지막에 나온 인덱스가
				//현재 인덱스와의 차이가 1을 넘으면 붙어있는 것이 아님..
				if (k - lastIdxArray[alphaIdx] > 1)
				{
					bGroupWord = false;
					break;
				}
				else
					lastIdxArray[alphaIdx] = k;
			}
		}

		//단어의 모든 문자에 대한 검사를 통과 시 그룹단어로 인정
		if(bGroupWord)
			answer++;
		//다음 단어로
		N--;
	}

	cout << answer << endl;
}