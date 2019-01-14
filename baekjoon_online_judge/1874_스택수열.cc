/*
1874 - 스택 수열

문제
스택 (stack)은 기본적인 자료구조 중 하나로, 컴퓨터 프로그램을 작성할 때 자주 이용되는 개념이다. 
스택은 자료를 넣는 (push) 입구와 자료를 뽑는 (pop) 입구가 같아 제일 먼저 들어간 자료가 제일 나중에 나오는 (FILO, first in last out) 특성을 가지고 있다.
1부터 n까지의 수를 스택에 넣었다가 뽑아 늘어놓음으로써, 하나의 수열을 만들 수 있다. 
이때, 스택에 push하는 순서는 반드시 오름차순을 지키도록 한다고 하자. 임의의 수열이 주어졌을 때 스택을 이용해 그 수열을 만들 수 있는지 없는지, 
있다면 어떤 순서로 push와 pop 연산을 수행해야 하는지를 알아낼 수 있다. 이를 계산하는 프로그램을 작성하라.

입력
첫 줄에 n (1 ≤ n ≤ 100,000)이 주어진다. 
둘째 줄부터 n개의 줄에는 수열을 이루는 1이상 n이하의 정수가 하나씩 순서대로 주어진다. 물론 같은 정수가 두 번 나오는 일은 없다.

출력
입력된 수열을 만들기 위해 필요한 연산을 한 줄에 한 개씩 출력한다. 
push연산은 +로, pop 연산은 -로 표현하도록 한다. 불가능한 경우 NO를 출력한다.
*/

#include <iostream>
#include <stack>
#include <vector>
//#include <string.h> //gcc memset

using namespace std;

int pushReady = 1; //스택에 넣을 수 있는 숫자 (1 ~ n까지 순차적으로 숫자를 넣음)
int pushMax = 0; //스탯에 넣을 수 있는 숫자 최대값

std::vector<int> requireSeq; //만들어야 할 수열
std::vector<char> operation; //입력된 수열을 만들기 위한 연산 모음
std::stack<int> stackData; //연산 중인 스택

int k = 0;

int main()
{
	ios::sync_with_stdio(false);

	bool bSolved = true;

	cin >> pushMax;

	for (int k = 0; k < pushMax; ++k)
	{
		int input = 0;
		cin >> input;
		requireSeq.push_back(input);
	}

	//수열의 숫자들마다 체크해본다
	for (auto m : requireSeq)
	{
		//만약 현재 와야하는 수열의 숫자가
		//넣을 수 있는 숫자보다 크다면 수열의 숫자가 Top이 될때까지 push
		if (m >= pushReady)
		{
			for (k = pushReady; k <= m; ++k)
			{
				stackData.push(k);
				operation.push_back('+');
			}

			//m까지 삽입되었으니 다음 삽입할 숫자는 m + 1 로 갱신
			pushReady = m + 1; 

			//pop해야 해당 숫자 나오니까.
			stackData.pop();
			operation.push_back('-');
		}
		//아니면 스택의 Top과 현재 수열에 와야하는 숫자가 같은지 비교
		//같으면 pop, 다르거나 중간에 스택이 비었으면 수열 성립 안되므로 종료
		else
		{
			if (!stackData.empty() && stackData.top() == m)
			{
				stackData.pop();
				operation.push_back('-');
			}
			else
			{
				bSolved = false;
				break;
			}
		}
	}

	

	//수열을 만들 수 있다면 연산들을 출력
	if (bSolved)
	{
		for (auto op : operation)
			cout << op << '\n';
	}
	//만들 수 없음 NO 출력
	else
		cout << "NO" << '\n';

	return 0;
}