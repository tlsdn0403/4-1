

n = int(input())  //일수 입력
line = input()     // 자산증감 문자열
M = [['.']* n]      //최소한의 2차원 행렬
r = 0              //행의 인덱스
p = '.'            // 이전 자산증감 상태
for c in range(n) :  // c 는 열에 해당하는 인덱스
	if line[c] == '+':
		if p == '/':
			if r ==0 :
				M.insert(0,['.']* n)
			else:
				r -= 1
			p = M[r][c] = '/'
		else if line[c] == '-':
			if p =='\\' or  p == '_':
				if r == len(M)-1:         #행 인덱스가 가장 아래를 가르킨다면
					M.append(['.'] * n)   #제일뒤에다가
				r += 1
			p = M[r][c] = '\\'
		else:
			r -= 1
			p = M[r][c] = '_'

for r in range(len(M)):
	print(''.join(M[r]))  //행렬의 각 행을 문자열로 합쳐서 출력
