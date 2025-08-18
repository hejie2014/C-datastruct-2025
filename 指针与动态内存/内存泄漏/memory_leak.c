#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cash = 100;
void Play(int bet);
int main()
{
    int bet = 0;
    printf("***Welcome to the Virtual Casino !***\n");
    printf("Total cash = $%d\n", cash);

    while (cash > 0)
    {
        printf("What's your bet ?: $");
        scanf("%d", &bet);
        if (bet == 0 || bet > cash)
        {
            printf("bet 不能为0并且不能大于本金!\n");
            // break;
            continue;
        }
        Play(bet);
        printf("\n********************************\n");
    }

    return 0;
}

void Play(int bet)
{
    char C[3] = {'J', 'Q', 'K'};
    printf("Shuffling.....");
    // 设置种子
    srand(time(NULL));
    // 进行洗牌，每次数据两两交换，
    for (int i = 0; i < 5; i++)
    {
        int x = rand() % 3; // 获取随机值，取模-->得到 0,1,2
        int y = rand() % 3;
        int temp = C[x];
        C[x] = C[y];
        C[y] = temp;
    }
    int playerGuess = 0;
    printf("What's the position of queen - 1, 2 or 3? ");
    scanf("%d", &playerGuess);
    if (C[playerGuess - 1] == 'Q')
    {
        cash += (3 * bet);
        printf("You Win ! Result = \"%c %c %c\" Total Cash = %d\n", C[0], C[1], C[2], cash);
    }
    else
    {
        cash -= bet;
        printf("You Lose ! Result = \"%c %c %c\" Total Cash = %d\n", C[0], C[1], C[2], cash);
    }
}