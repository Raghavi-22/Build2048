#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct Game2048{
    int board[4][4];
    int score;  // To keep track of the score

    Game2048() : score(0) {}  // Initialize score to 0
   //Slide the non-zero elements to the right.
   //Merge adjacent elements that have the same value.
    void swipe_right(int arr[]){
        int last_placed=4;
        int can_merge = 0;
        for(int i=3;i>=0;i--){
            if(arr[i]!=0){
                if(can_merge){
                    if(arr[i]==arr[last_placed]){
                        arr[last_placed]*=2;
                        score += arr[last_placed];  // Update score when tiles merge
                        arr[i]=0;
                        can_merge=0;
                    }
                    else{
                        arr[last_placed-1]=arr[i];
                        last_placed--;
                        if(i!=last_placed){
                            arr[i]=0;
                        }
                        can_merge = 1;
                    }
                }
                else{
                    arr[last_placed-1]=arr[i];
                    last_placed--;
                    if(i!=last_placed){
                        arr[i]=0;
                    }
                    can_merge = 1;
                }
            }
        }
    }

    bool has_game_ended(){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(board[i][j]==0){
                    return false;
                }
            }
        }
        return true;
    }

    bool check_win(){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(board[i][j] == 2048){
                    return true;
                }
            }
        }
        return false;
    }

    void random_populate(){
        while(1){
            int i = rand()%4;
            int j = rand()%4;
            if(board[i][j]==0){
                int ch = rand()%2;
                if(ch==0){
                    board[i][j]=2;
                }
                else{
                    board[i][j]=4;
                }
                return;
            }
        }
    }

    void init(){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                board[i][j]=0;
            }
        }
        random_populate();
        random_populate();
    }

    bool up(){
        for(int col=0;col<4;col++){
            int arr[4];
            for(int row=0;row<4;row++){
                arr[3-row]=board[row][col];
            }
            swipe_right(arr);
            for(int row=0;row<4;row++){
                board[row][col]=arr[3-row];
            }
        }
        return move_end();
    }

    bool down(){
        for(int col=0;col<4;col++){
            int arr[4];
            for(int row=0;row<4;row++){
                arr[row]=board[row][col];
            }
            swipe_right(arr);
            for(int row=0;row<4;row++){
                board[row][col]=arr[row];
            }
        }
        return move_end();
    }

    bool left(){
        for(int row=0;row<4;row++){
            int arr[4];
            for(int col=0;col<4;col++){
                arr[3-col]=board[row][col];
            }
            swipe_right(arr);
            for(int col=0;col<4;col++){
                board[row][col]=arr[3-col];
            }
        }
        return move_end();
    }

    bool right(){
        for(int row=0;row<4;row++){
            int arr[4];
            for(int col=0;col<4;col++){
                arr[col]=board[row][col];
            }
            swipe_right(arr);
            for(int col=0;col<4;col++){
                board[row][col]=arr[col];
            }
        }
        return move_end();
    }

    bool move_end(){
        if(has_game_ended()){
            return false;
        }
        else{
            random_populate();
            return true;
        }
    }

    void print_board(){
        cout << "Score: " << score << "\n";  // Display the score
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(board[i][j]){
                    cout<<board[i][j]<<"\t";
                }
                else{
                    cout<<".\t";
                }
            }
            cout<<endl;
        }
    }
};

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    srand(time(0)); //generate new number everytime or different every time
    Game2048 mygame;
    mygame.init();

    while(1){
        mygame.print_board();
        cout<<"What move?(L,D,R,U)"<<endl;
        char ch;
        bool ended;
        
        cin>>ch;
        if(ch=='U'){
            ended = mygame.up();
        }
        else if(ch=='D'){
            ended = mygame.down();
        }
        else if(ch=='L'){
            ended = mygame.left();
        }
        else if(ch=='R'){
            ended = mygame.right();
        }
        else{
            cout<<"INVALID\n";
            continue;
        }

        if(mygame.check_win()){
            mygame.print_board();
            cout<<"You reached 2048! You win!\n";
            return 0;
        }

        if(!ended){
            mygame.print_board();
            cout<<"Game ended\n";
            return 0;
        }
    }
    return 0;
}
