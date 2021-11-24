#include<bits/stdc++.h>
using namespace std;
char grid[7][7]= { {'A', ' ', 'B', ' ', 'C', ' ', 'D'},
    {' ', ' ', ' ', ' ', ' ', ' ',' '},
    {'E', ' ', 'F', ' ', 'G', ' ', 'H'},
    {' ', ' ', ' ', ' ', ' ', ' ',' '},
    {'I', ' ', 'J', ' ', 'K', ' ', 'L'},
    {' ', ' ', ' ', ' ', ' ', ' ',' '},
    {'M', ' ', 'N', ' ', 'O', ' ', 'P'}
};

map<char,pair<int,int> >mp;
map<pair<int,int>, int> cord_to_node;
map<pair<int,int>, int> node_to_edge;
bool check[24];
bool sqr_check[9];



vector<int>sqr[9];
vector<pair<int,int> >middle_coordinate_of_sqr(9);
int p1_score = 0;
int p2_score = 0;
void init()
{
    mp['A']= {0,0};
    mp['B']= {0,2};
    mp['C']= {0,4};
    mp['D']= {0,6};
    mp['E']= {2,0};
    mp['F']= {2,2};
    mp['G']= {2,4};
    mp['H']= {2,6};
    mp['I']= {4,0};
    mp['J']= {4,2};
    mp['K']= {4,4};
    mp['L']= {4,6};
    mp['M']= {6,0};
    mp['N']= {6,2};
    mp['O']= {6,4};
    mp['P']= {6,6};

    for(auto it:mp)
    {
        cord_to_node[it.second] = it.first;
    }

    node_to_edge[ {0,1}] = 0;
    node_to_edge[ {1,2}] = 1;
    node_to_edge[ {2,3}] = 2;
    node_to_edge[ {4,5}] = 7;
    node_to_edge[ {5,6}] = 8;
    node_to_edge[ {6,7}] = 9;
    node_to_edge[ {8,9}] = 14;
    node_to_edge[ {9,10}] = 15;
    node_to_edge[ {10,11}] = 16;
    node_to_edge[ {12,13}] = 21;
    node_to_edge[ {13,14}] = 22;
    node_to_edge[ {14,15}] = 23;
    node_to_edge[ {0,4}] = 3;
    node_to_edge[ {1,5}] = 4;
    node_to_edge[ {2,6}] = 5;
    node_to_edge[ {3,7}] = 6;
    node_to_edge[ {4,8}] = 10;
    node_to_edge[ {5,9}] = 11;
    node_to_edge[ {6,10}] = 12;
    node_to_edge[ {7,11}] = 13;
    node_to_edge[ {8,12}] = 17;
    node_to_edge[ {9,13}] = 18;
    node_to_edge[ {10,14}] = 19;
    node_to_edge[ {11,15}] = 20;

    for(auto it:node_to_edge)
    {
        int x = it.first.first;
        int y = it.first.second;
        node_to_edge[{y,x}]=it.second;
    }

    sqr[0] = {0,3,4,7};
    sqr[1] = {1,4,5,8};
    sqr[2] = {2,5,6,9};
    sqr[3] = {7,10,11,14};
    sqr[4] = {8,11,12,15};
    sqr[5] = {9,12,13,16};
    sqr[6] = {14,17,18,21};
    sqr[7] = {15,18,19,22};
    sqr[8] = {16,19,20,23};

    middle_coordinate_of_sqr[0] = {1,1};
    middle_coordinate_of_sqr[1] = {1,3};
    middle_coordinate_of_sqr[2] = {1,5};
    middle_coordinate_of_sqr[3] = {3,1};
    middle_coordinate_of_sqr[4] = {3,3};
    middle_coordinate_of_sqr[5] = {3,5};
    middle_coordinate_of_sqr[6] = {5,1};
    middle_coordinate_of_sqr[7] = {5,3};
    middle_coordinate_of_sqr[8] = {5,5};
}

void show(void)
{
    printf("\nCurrent grid:                      SCORE BOARD:\n\n");
    for(int i=0; i<7; i++)
    {
        printf("            ");
        for(int j=0; j<7; j++)
        {
            printf("%c",grid[i][j]);
        }
        if(i<2)
        {
            printf("                            ");
            printf("Player 0%d: %d",i+1,(i)?p2_score:p1_score);
        }
        printf("\n");
    }



}
void gameOver(bool flag)
{
    printf("\n------------------------------GAME OVER!!!!!---------------------------------");
    printf("\nCurrent grid:                      SCORE BOARD:\n\n");
    for(int i=0; i<7; i++)
    {
        printf("            ");
        for(int j=0; j<7; j++)
        {
            printf("%c",grid[i][j]);
        }
        if(i<2)
        {
            printf("                            ");
            printf("Player 0%d: %d",i+1,(i)?p2_score:p1_score);
        }
        else if(i==3)
        {
            printf("                            ");
            printf("Player 0%d wins!!!!",(flag)?1:2);
        }
        printf("\n");
    }
}

int func(int player, bool* f)
{
    int count = 0;
    bool ans = 0;
    for(int i=0; i<9; i++)
    {
        if(sqr_check[i])continue;//square completed already
        bool flag = 1;//edge check

        for(int j=0; j<4; j++)
        {
            if(!check[sqr[i][j]])flag=0;    //any edge of an square are not connected
        }
        if(flag)//all 4 edge are connected
        {
            pair<int,int> p= middle_coordinate_of_sqr[i];
            grid[p.first][p.second] = player+48;
            sqr_check[i] = 1;//square complete
            count++;
            ans=1;
        }


    }
    if(!ans) *f = !(*f);
    return count;
}
int main()
{
    init();
    bool flag = 0;
    while(1)
    {
        if(p1_score + p2_score ==9)
        {
            gameOver(p1_score>p2_score);
            break;
        }
        show();
        if(!flag)
        {
            char p1,p2;
            printf("\n------------------------Player 01-----------------------------");
            printf("\nChoose two points: \n");
            printf("\n            Point 01 : ");
            cin>>p1;
            if(p1>='A' && p1<='P');
            else
            {
                printf("\n                              Invalid point\n");
                continue;
            }
            printf("            Point 02 : ");
            cin>>p2;
            if(p2>='A' && p2<='P');
            else
            {
                printf("\n                              Invalid point\n");
                continue;
            }

            int x1,x2,y1,y2;
            x1= mp[p1].first;
            x2=mp[p2].first;
            y1=mp[p1].second;
            y2=mp[p2].second;
            if(node_to_edge.find({p1-'A',p2-'A'}) == node_to_edge.end())
            {
                printf("\n                              This move is not permitted\n");
                continue;
            }
            else
            {
                int xedge = node_to_edge[ {p1-'A',p2-'A'}];
                if(check[xedge])
                {
                    printf("\n                              This edge is already taken\n");
                    continue;
                }
            }
            if(x1==x2 && abs(y1-y2)==2)
            {
                int xedge = node_to_edge[ {p1-'A',p2-'A'}];
                check[xedge]=1;
                grid[x1][min(y1,y2)+1] = '_';
            }
            else if(y1==y2 && abs(x1-x2)==2)
            {
                int xedge = node_to_edge[ {p1-'A',p2-'A'}];
                check[xedge]=1;
                grid[min(x1,x2)+1][y1] = '|';
            }
            p1_score+=func(1,&flag);

        }
        else
        {
            char p1,p2;
            printf("\n------------------------Player 02-----------------------------");
            printf("\nChoose two points: \n");
            printf("\n            Point 01 : ");
            cin>>p1;
            if(p1>='A' && p1<='P');
            else
            {
                printf("\n                              Invalid point\n");
                continue;
            }
            printf("\n            Point 02 : ");
            cin>>p2;
            if(p2>='A' && p2<='P');
            else
            {
                printf("\n                              tInvalid point\n");
                continue;
            }

            int x1,x2,y1,y2;
            x1= mp[p1].first;
            x2=mp[p2].first;
            y1=mp[p1].second;
            y2=mp[p2].second;

            if(node_to_edge.find({p1-'A',p2-'A'}) == node_to_edge.end())
            {
                printf("\n                              This move is not permitted\n");
                continue;
            }
            else
            {
                int xedge = node_to_edge[ {p1-'A',p2-'A'}];
                if(check[xedge])
                {
                    printf("\n                              This edge is already taken\n");
                    continue;
                }
            }

            if((x1==x2 && abs(y1-y2)==2))
            {
                int xedge = node_to_edge[ {p1-'A',p2-'A'}];
                check[xedge]=1;
                grid[x1][min(y1,y2)+1] = '_';
            }
            else if(y1==y2 && abs(x1-x2)==2)
            {

                int xedge = node_to_edge[ {p1-'A',p2-'A'}];
                check[xedge]=1;
                grid[min(x1,x2)+1][y1] = '|';
            }
            p2_score+=func(2,&flag);
        }

    }

}
