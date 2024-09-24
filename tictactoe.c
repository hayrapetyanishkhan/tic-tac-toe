#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void printing(char arr[3][3]){
    pid_t pid = fork();
    if(pid > 0){
        wait(NULL);
    }
    else if(pid == 0){
        system("clear");
        exit(EXIT_SUCCESS);
    }
    else if(pid == -1){
        perror("fork failed:");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i < 3;++i){
        printf(" %c  | %c  | %c\n",arr[i][0],arr[i][1],arr[i][2]);
        if(i != 2)
            printf("____|____|____\n");
        else
            printf("    |    |\n");
    }
}

int checking(char arr[3][3],int line,int row){
    int flag = 0;
    if((line + row) % 2 == 0){
        for(int i=0;i < 3;++i){
            if(arr[i][i] != arr[line][row]){
                flag = 0;
                break;
            }
            else{
                flag = 1;
            }
        }
        if(flag){
            return 1;//that means victory//
        }
        for(int i=0;i < 3;++i){
            if(arr[i][2 - i] != arr[line][row]){
                flag = 0;
                break;
            }
            else{
                flag = 1;
            }
        }
        if(flag){
            return 1;//that means victory//
        }
    }
    for(int i=0;i < 3;++i){
        if(arr[line][i] != arr[line][row]){
            flag = 0;
            break;
        }
        else{
            flag = 1;
        }
    }
    if(flag){
        return 1;//that means victory//
    }

    for(int i=0;i < 3;++i){
        if(arr[i][row] != arr[line][row]){
            flag = 0;
            break;
        }
        else{
            flag = 1;
        }
    }
    if(flag){
        return 1;//that means victory//
    }
    return 0;
}

int main(){

    char first[10] = {0};
    char second[10] = {0};

    char arr[3][3] = {"   ","   ","   "};

    int turn = 1;
    int rep = 0;

    int line = 0;
    int row = 0;

    printf("Player 1 please enter your name : ");
    scanf("%s",first);
    printf("Player 2 please enter your name : ");
    scanf("%s",second);
    first[strcspn(first,"\n")] = '\0';
    second[strcspn(second,"\n")] = '\0';

    for(int i=0; i < 3; ++i){
        for(int j=0;j < 3;++j){
            printing(arr);
            printf("It's %s's turn\n",turn ? first : second);

            printf("Enter the line:");
            scanf("%d",&line);
            printf("Enter the row:");
            scanf("%d",&row);
            if(arr[line][row] != ' '){
                printf("The square is not empty:\n");
                exit(EXIT_FAILURE);
            }
            arr[line][row] = turn ? 'X' : 'O';
            if(checking(arr,line,row)){
                printing(arr);
                printf("%s won the game!!!\n",turn ? first : second);
                exit(EXIT_SUCCESS);
            }
            turn ? turn-- : turn++;
        }
    }
    if(!checking(arr,line,row)){
        printing(arr);
        printf("IT'S A DRAW");
        }
}  
