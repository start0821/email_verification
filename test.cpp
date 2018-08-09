// #include <iostream>
// using namespace std;



// // function AlphaBeta(State, Alpha, Beta, Player){
// // 	if(State == done){
// // 		return Result(state)
// // 	}
// // 	if (Player){
// // 		for(int i=0;i<possible_play;i++){
// // 			if()
// // 		}
// // 	}
// // }

// // class Evaluation{
// // public:
// // 	int* pattern;
// // 	int pattern_num;
// // 	int value;
// // private:
// // 	Evaluation(int,int);
// // };

// // Evaluation::Evaluation(int pattern,int value){

// // }

// // int get_point(int a=1,int b=1,int board[BOARDSIZE][BOARDSIZE]){

// // }

struct Evaluation{
	int pattern[9];
	int pattern_num; // 패턴의 개수를 의미함
	int value; // evaluation score을 의미함.
};
Evaluation score[45] = {{{1,1,1,1,1,1,4,4,4},6,100000000},
						{{0,1,1,1,1,0,4,4,4},6,471125},
					   	{{0,1,0,1,1,1,0,1,0},9,178408},
					   	{{0,1,0,1,1,1,0,0,1},9,178408},
					   	{{1,0,0,1,1,1,0,1,0},9,968445},
					   	{{1,0,0,1,1,1,0,0,1},9,136975},
					   	{{0,0,1,1,1,1,0,0,4},8,958631},
					   	{{1,1,1,1,1,0,4,4,4},6,224804},
					   	{{0,1,1,1,1,1,4,4,4},6,224804},
					   	{{1,0,1,1,1,1,4,4,4},6,745729},
					   	{{1,1,1,1,0,1,4,4,4},6,745729},
					   	{{1,1,0,1,1,1,4,4,4},6,146434},
					   	{{1,1,1,0,1,1,4,4,4},6,146434},
					   	{{1,0,0,1,1,1,1,4,4},7,653420},
					   	{{1,1,1,1,0,0,1,4,4},7,653420},
					   	{{1,1,0,0,1,1,1,4,4},7,406632},
					   	{{1,1,1,0,0,1,1,4,4},7,406632},
					   	{{1,0,1,0,1,1,1,4,4},7,752847},
					   	{{1,1,1,0,1,0,1,4,4},7,752847},
					   	{{1,1,0,1,1,0,1,4,4},7,835834},
					   	{{1,0,1,1,0,1,1,4,4},7,835834},
					   	{{1,0,1,1,1,0,1,4,4},7,180915},
					   	{{1,1,0,1,0,1,1,4,4},7,170667},
					   	{{1,1,1,1,0,0,4,4,4},6,965425},
					   	{{0,0,1,1,1,1,4,4,4},6,965425},
					   	{{1,1,1,0,0,1,4,4,4},6,294247},
					   	{{1,0,0,1,1,1,4,4,4},6,294247},
					   	{{1,1,0,0,1,1,4,4,4},6,308961},
					   	{{1,0,1,0,1,1,4,4,4},6,296802},
					   	{{1,1,0,1,0,1,4,4,4},6,296802},
					   	{{1,0,1,1,0,1,4,4,4},6,919855},
					   	{{0,0,1,1,1,0,0,0,4},8,916206},
					   	{{0,0,0,1,1,1,0,0,4},8,916206},
					   	{{0,0,1,1,0,1,0,0,4},8,378982},
					   	{{0,0,1,0,1,1,0,0,4},8,378982},
					   	{{0,0,0,0,1,1,0,1,0},9,262479},
					   	{{0,1,0,1,1,0,0,0,0},9,262479},
					   	{{0,0,0,0,1,1,0,0,1},9,771643},
					   	{{1,0,0,1,1,0,0,0,0},9,771643},
					   	{{0,0,0,1,1,0,0,1,0},9,28720},
					   	{{0,1,0,0,1,1,0,0,0},9,28720},
					   	{{0,0,0,1,1,0,0,1,0},9,437413},
					   	{{0,1,0,1,0,1,0,0,0},9,437413},
					   	{{1,1,1,0,0,0,4,4,4},6,625778},
						{{0,0,0,1,1,1,4,4,4},6,625778}};
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <cstdlib>
using namespace std;
#define BOARDSIZE 19
int BOARD[19][19];
void getPi(Evaluation line, int* pi){
	int j=0;
	int length = (int)(line.pattern_num);
	for(int i = 1; i< length ; i++){
		while(j > 0 && line.pattern[i] != line.pattern[j]){
			j = pi[j-1];
		}
		if(line.pattern[i] == line.pattern[j])
			pi[i] = ++j;
	}
	// return pi;
}
std::vector<int> kmp(std::vector<int> s, Evaluation line, int pi[]){   //kmp 알고리즘  -> 긴 나열속에서 주어진 패턴을 찾는것.
	std::vector<int> ans;
	if(s.size()<line.pattern_num) return ans;

	// pi = getPi(line,pi);
	int n = s.size();
	int m = line.pattern_num;
	int j =0;
	for(int i = 0 ; i < n ; i++){
		while(j>0 && s[i] != line.pattern[j])
			j = pi[j-1];
		if(s[i] == line.pattern[j]){
			if(j==m-1){
				ans.push_back(i-m+1);
				j = pi[j];
			}
			else{
				j++;
			}
		}
	}
	return ans;  // 이 answer에 대해서는 딱히 위치가 중요하진 않기 때문에 변수타입을 내가 필요한 것만 넣을수있도록 바꾸어 주자.
}

std::vector<std::vector<int> >get_board(){
	std::vector<std::vector<int> > board(BOARDSIZE, std::vector<int>(BOARDSIZE,0));
	//board의 3을 1로 표시
	for(int i=0;i<BOARDSIZE;i++){ // 블로킹 돌을 내돌로 인식하도록 함.
		for(int j=0;j<BOARDSIZE;j++){
			board[j][i] = BOARD[j][i];
		}
	}
	return board;
}

std::vector<std::vector<int> >remove_block(int player, std::vector<std::vector<int> > board){
	//board의 3을 1로 표시
	std::vector<std::vector<int> > temp;
	temp = board;
	for(int i=0;i<BOARDSIZE;i++){ // 블로킹 돌을 내돌로 인식하도록 함.
		for(int j=0;j<BOARDSIZE;j++){
			if(board[j][i] == 3){
				temp[j][i] = 1;
			}
		}
	}
	return temp;
}

std::vector<std::vector<int> >put_rock(int X[2],int Y[2],int player, std::vector<std::vector<int> > board){ // 임시로 돌을 놓는다. //player : 1은 나 2는 상대
	std::vector<std::vector<int> > temp;
	temp = board;
	// x,y위치에 흰돌을 놓는다.
	//놓으려는 x y위치가 free한 위치인지 확인한다.
	for(int i=0;i<2;i++){
		// if(isFree(X[i],Y[i])){    // 나중에는 if문 comment 풀어줘야함.
			temp[X[i]][Y[i]] = player;
		// }
	}
	return temp;
}

std::vector<std::vector<int> > getBoardline(std::vector<std::vector<int> > board){  // 보드에 있는
	std::vector<std::vector<int> > boardline;

	for(int i=0;i<BOARDSIZE;i++){ //가로부분 발췌
		std::vector<int> temp;
		for(int j=0;j<BOARDSIZE;j++){
			temp.push_back(board[j][i]);
		}
		boardline.push_back(temp);
	}
	for(int i=0;i<BOARDSIZE;i++){ //세로부분 발췌
		boardline.push_back(board[i]);
	}
	for(int i=0;i<BOARDSIZE;i++){ // 대각선 남서부분 발췌
		std::vector<int> temp;
		int k=0;
		for(int j=i;j<BOARDSIZE;j++){
			temp.push_back(board[k][j]);
			k++;
		}
		boardline.push_back(temp);
	}
	for(int i=0;i<BOARDSIZE;i++){ // 대각선 남동부분 발췌
		std::vector<int> temp;
		int k = BOARDSIZE-1;
		for(int j=i;j<BOARDSIZE;j++){
			temp.push_back(board[k][j]);
			k--;
		}
		boardline.push_back(temp);
	}
	for(int i=1;i<BOARDSIZE;i++){ // 대각선 북동부분 발췌
		std::vector<int> temp;
		int k = i;
		for(int j=0;j<BOARDSIZE-i;j++){
			temp.push_back(board[k][j]);
			k++;
		}
		boardline.push_back(temp);
	}
	for(int i=0;i<BOARDSIZE-1;i++){ // 대각선 북서부분 발췌
		std::vector<int> temp;
		int k = 0;
		for(int j=i;j>=0;j--){
			temp.push_back(board[k][j]);
			k++;
		}
		boardline.push_back(temp);
	}
	return boardline;
}

float evaluate_score(vector<vector<int> >board){
	std::vector<std::vector<int> > boardline;
	boardline = getBoardline(board);
	float totalscore = 0;
	for(int a=0;a<45;a++){
		int sum = 0;
		int pi[score[a].pattern_num];
		for(int b=0;b<score[a].pattern_num;b++){
			pi[b] = 0;
		}
		getPi(score[a],pi);
		for(int c=0;c<boardline.size();c++){
			std::vector<int> temp = kmp(boardline[c],score[a],pi);
			sum += temp.size();
		}
		totalscore += sum * score[a].value;
	}
	return totalscore;
}

class Node{
public:
	vector<int> location;
	vector<Node> child;
	Node(int x[2],int y[2]){
		for(int order=0;order<2;order++) this -> location.push_back(x[order]);
		for(int order=0;order<2;order++) this -> location.push_back(y[order]);
	}
	Node(){};
};
Node get_node(int x[2],int y[2]){
	Node temp;
		for(int order=0;order<2;order++) temp.location.push_back(x[order]);
		for(int order=0;order<2;order++) temp.location.push_back(y[order]);
	return temp;
}


Node get_tree(vector<vector<int> > board,int depth,Node node){
	if(depth==1){
		cout << "hi" << flush;
		for(int y1=2;y1<BOARDSIZE-2;y1++){
			for(int x1=2;x1<BOARDSIZE-2;x1++){
				if(board[x1][y1]==0){
					for(int y2=y1;y2<BOARDSIZE-2;y2++){
						if(y2==y1){
							for(int x2=x1+1;x2<BOARDSIZE-2;x2++){
								if(board[x2][y2]==0){
									int X[2] = {x1,x2}, Y[2] = {y1,y2};
									node.child.push_back(get_node(X,Y));
								}
							}
						}
						else{
							for(int x2=2;x2<BOARDSIZE-2;x2++){
								if(board[x2][y2]==0){
									int X[2] = {x1,x2}, Y[2] = {y1,y2};
									node.child.push_back(get_node(X,Y));
								}
							}
						}
					}
				}
			}
		}
		return node;
	}
	else{
		for(int y1=2;y1<BOARDSIZE-2;y1++){
			for(int x1=2;x1<BOARDSIZE-2;x1++){
				if(board[x1][y1]==0){
					for(int y2=y1;y2<BOARDSIZE-2;y2++){
						if(y2==y1){
							for(int x2=x1+1;x2<BOARDSIZE-2;x2++){
								if(board[x2][y2]==0){
									// vector<vector<int> >tmp;
									int X[2] = {x1,x2}, Y[2] = {y1,y2};
									// tmp = put_rock(X,Y,1,board);
									Node child1(X,Y);
									child1 = get_tree(board,depth-1,child1);
									node.child.push_back(child1);
								}
							}
						}
						else{
							for(int x2=2;x2<BOARDSIZE-2;x2++){
								if(board[x2][y2]==0){
									// vector<vector<int> >tmp;
									int X[2] = {x1,x2}, Y[2] = {y1,y2};
									// tmp = put_rock(X,Y,1,board);
									Node child1(X,Y);
									child1 = get_tree(board,depth-1,child1);
									node.child.push_back(child1);
								}
							}
						}
					}
				}
			}
		}
		return node;
	}
}

int main(){
	srand (time(NULL));
	for(int i=0;i<BOARDSIZE;i++){
		for(int j=0;j<BOARDSIZE;j++){
			BOARD[i][j]=rand()%4;
			if(i==1&&j==2) BOARD[i][j]=0;
		}
	}
	std::vector<std::vector<int> > boardline;
	int x[2] = {1,2}, y[2]={2,3};
	vector<vector<int> > board = get_board();
	boardline = getBoardline(board);
	for(int i=0;i<boardline.size();i++){
		for(int j=0;j<boardline[i].size();j++){
					cout<<(int)boardline[i][j];
		}
		cout << endl;
	}
	std::vector<std::vector<int> > temp;
	temp = board;
	Node node;
	node = get_tree(temp,2,node);
	board = remove_block(2,board);
	cout <<  evaluate_score(board);

}
// vector는 parameter에 함수를 넣고 수정이 되면 함수 밖으로 나와도 그대로 적용됨. x -- 함수안에서 변수의 변화가 함수 밖에서 영향을 주지 않는다.

//구현해야할것 :: alphabeta algorithm
