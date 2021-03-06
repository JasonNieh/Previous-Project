//
//  main.cpp
//  Chess
//
//  Created by Jason Nie on 7/19/18.
//  Copyright © 2018 Jason Nie. All rights reserved.
//
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <iomanip>
int ChessB[15][15]={0};
using namespace std;
struct pos{
    int x;
    int y;
};
struct POS_AI{
    int x;
    int y;
    int weight;
};
class Chess
{
public:
   
    int judge(int a, int b, int c,int map[15][15]);
    POS_AI ai(int player_x,int player_y,int ai_x,int ai_y,int map[15][15]);
    int cal(int i, int j,int point[15][15]);
    
    int stone_x,stone_y;
    int stone_map[15][15];// 0代表空，1黑，2白
  
    
};
int Chess::judge(int Cx, int Cy, int Now,int point[15][15]) //a表示行，b表示列 ,c表示颜色
{
    //累计横竖正斜反邪四个方向的连续相同棋子数目
    int w = 1, x = 1, y = 1, z = 1, i;
    
    //上下方向检查
    {
        //向下检查
        for (i = 1; i < 5; i++)
            if (Cy + i <= 15 && point[Cx][Cy + i] == Now)
                w++;
            else break;
        //向上检查
        for (i = 1; i < 5; i++)
            if (Cy - i >= 0 && point[Cx][Cy - i] == Now)
                w++;
            else break;
        //若果达到5个则判断当前走子玩家为赢家
        if (w >= 5)
            return Now;
    }
    //左右检查
    {
        //向右检查
        for (i = 1; i < 5; i++)
            if (Cx + i <= 15 && point[Cx + i][Cy] == Now)
                x++;
            else break;
        //向左检查
        for (i = 1; i < 5; i++)
            if (Cx - i >= 0 && point[Cx - i][Cy] == Now)
                x++;
            else break;
        //若果达到5个则判断当前走子玩家为赢家
        if (x >= 5)
            return Now;
    }
    //“\”方向检查
    {
        //向右下检查
        for (i = 1; i < 5; i++)
            if (Cx + i <= 15 && Cy + i <= 15 && point[Cx + i][Cy + i] == Now)
                y++;
            else break;
        //向左上检查
        for (i = 1; i < 5; i++)
            if (Cx - i >= 0 && Cy - i >= 0 && point[Cx - i][Cy - i] == Now)
                y++;
            else break;
        //若果达到5个则判断当前走子玩家为赢家
        if (y >= 5)
            return Now;
    }
    //“/”方向检查
    {
        //向右上检查
        for (i = 1; i < 5; i++)
            if (Cx + i <= 15 && Cy - i >= 0 && point[Cx + i][Cy - i] == Now)
                z++;
            else break;
        //向左下检查
        for (i = 1; i < 5; i++)
            if (Cx - i >= 0 && Cy + i <= 15 && point[Cx - i][Cy + i] == Now)
                z++;
            else break;
        //若果达到5个则判断当前走子玩家为赢家
        if (z >= 5)
            return Now;
    }
    
    //若没有检查到五连珠，则返回0表示还没有玩家达成胜利
    return 0;
}
POS_AI Chess::ai(int player_x,int player_y,int ai_x,int ai_y,int map[15][15]){
    int point[15][15]={0};
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++)
            point[i][j]=map[i][j];
    }
    int winner=0;
    POS_AI oldPos;
    oldPos.weight=0;
    POS_AI newPos;
    newPos.weight=0;
    POS_AI tempPos;
    POS_AI pos1,pos2,pos3,pos_player_win;
    
    int a,b,c,d,s;
    a=((ai_x-4)>=0)?(ai_x-4):0;
    b=((ai_x+4)<=14)?(ai_x+4):14;
    c=((ai_y-4)>=0)?(ai_y-4):0;
    d=((ai_y+4)<=14)?(ai_y+4):14;
    for(int i=a;i<=b;i++){
        for(int j=c;j<=d;j++){
            s=cal(i, j,point);
            if(newPos.weight<s){
                newPos.weight=s;
                newPos.x=i;
                newPos.y=j;
            }
        }
    }
    
    a=((player_x-4)>=0)?(player_x-4):0;
    b=((player_x+4)<=14)?(player_x+4):14;
    c=((player_y-4)>=0)?(player_y-4):0;
    d=((player_y+4)<=14)?(player_y+4):14;
    for(int i=a;i<=b;i++){
        for(int j=c;j<=d;j++){
            s=cal(i, j,point);
            if(oldPos.weight<s){
                oldPos.weight=s;
                oldPos.x=i;
                oldPos.y=j;
            }
        }
    }
    tempPos=(newPos.weight>=oldPos.weight)?newPos:oldPos;
    pos_player_win=tempPos;
    ai_x=tempPos.x;ai_y=tempPos.y;
    point[tempPos.x][tempPos.y]=2;
    winner=judge(tempPos.x,tempPos.y,2,point);
    if(winner==2){
        return tempPos;
    }
    else{
        newPos.weight=0;
        a=((player_x-4)>=0)?(player_x-4):0;
        b=((player_x+4)<=14)?(player_x+4):14;
        c=((player_y-4)>=0)?(player_y-4):0;
        d=((player_y+4)<=14)?(player_y+4):14;
        for(int i=0;i<15;i++){
            for(int j=0;j<15;j++)
                if(point[i][j]!=0)
                    point[i][j]=(point[i][j]==1)?2:1;
        }
        for(int i=a;i<=b;i++){
            for(int j=c;j<=d;j++){
                s=cal(i, j,point);
                if(newPos.weight<s){
                    newPos.weight=s;
                    newPos.x=i;
                    newPos.y=j;
                }
            }
        }
        
        oldPos.weight=0;
        a=((tempPos.x-4)>=0)?(tempPos.x-4):0;
        b=((tempPos.x+4)<=14)?(tempPos.x+4):14;
        c=((tempPos.y-4)>=0)?(tempPos.y-4):0;
        d=((tempPos.y+4)<=14)?(tempPos.y+4):14;
        for(int i=a;i<=b;i++){
            for(int j=c;j<=d;j++){
                s=cal(i, j,point);
                if(oldPos.weight<s){
                    oldPos.weight=s;
                    oldPos.x=i;
                    oldPos.y=j;
                }
            }
        }
        tempPos=(newPos.weight>=oldPos.weight)?newPos:oldPos;
        player_x=tempPos.x;
        player_y=tempPos.y;
        point[tempPos.x][tempPos.y]=1;
        winner=judge(tempPos.x,tempPos.y,2,point);
        if(winner==2){
            return tempPos;
        }
        else{
            pos1=tempPos;
            
            newPos.weight=0;
            a=((ai_x-4)>=0)?(ai_x-4):0;
            b=((ai_x+4)<=14)?(ai_x+4):14;
            c=((ai_y-4)>=0)?(ai_y-4):0;
            d=((ai_y+4)<=14)?(ai_y+4):14;
            
            for(int i=0;i<15;i++){
                for(int j=0;j<15;j++)
                    if(point[i][j]!=0)
                        point[i][j]=(point[i][j]==1)?2:1;
            }
            for(int i=a;i<=b;i++){
                for(int j=c;j<=d;j++){
                    s=cal(i, j,point);
                    if(newPos.weight<s){
                        newPos.weight=s;
                        newPos.x=i;
                        newPos.y=j;
                    }
                }
            }
            
            oldPos.weight=0;
            a=((tempPos.x-4)>=0)?(tempPos.x-4):0;
            b=((tempPos.x+4)<=14)?(tempPos.x+4):14;
            c=((tempPos.y-4)>=0)?(tempPos.y-4):0;
            d=((tempPos.y+4)<=14)?(tempPos.y+4):14;
            for(int i=a;i<=b;i++){
                for(int j=c;j<=d;j++){
                    s=cal(i, j,point);
                    if(oldPos.weight<s){
                        oldPos.weight=s;
                        oldPos.x=i;
                        oldPos.y=j;
                    }
                }
            }
            tempPos=(newPos.weight>=oldPos.weight)?newPos:oldPos;
            ai_x=tempPos.x;ai_y=tempPos.y;
            
            point[tempPos.x][tempPos.y]=2;
            winner=judge(tempPos.x,tempPos.y,2,point);
            if(winner==2){
                return pos_player_win;
            }
            else{
                newPos.weight=0;
                a=((player_x-4)>=0)?(player_x-4):0;
                b=((player_x+4)<=14)?(player_x+4):14;
                c=((player_y-4)>=0)?(player_y-4):0;
                d=((player_y+4)<=14)?(player_y+4):14;
                
                for(int i=0;i<15;i++){
                    for(int j=0;j<15;j++)
                        if(point[i][j]!=0)
                            point[i][j]=(point[i][j]==1)?2:1;
                }
                
                for(int i=a;i<=b;i++){
                    for(int j=c;j<=d;j++){
                        s=cal(i, j,point);
                        if(newPos.weight<s){
                            newPos.weight=s;
                            newPos.x=i;
                            newPos.y=j;
                        }
                    }
                }
                
                oldPos.weight=0;
                a=((tempPos.x-4)>=0)?(tempPos.x-4):0;
                b=((tempPos.x+4)<=14)?(tempPos.x+4):14;
                c=((tempPos.y-4)>=0)?(tempPos.y-4):0;
                d=((tempPos.y+4)<=14)?(tempPos.y+4):14;
                for(int i=a;i<=b;i++){
                    for(int j=c;j<=d;j++){
                        s=cal(i, j,point);
                        if(oldPos.weight<s){
                            oldPos.weight=s;
                            oldPos.x=i;
                            oldPos.y=j;
                        }
                    }
                }
                tempPos=(newPos.weight>=oldPos.weight)?newPos:oldPos;
                player_x=tempPos.x;
                player_y=tempPos.y;
                point[tempPos.x][tempPos.y]=1;
                winner=judge(tempPos.x,tempPos.y,2,point);
                if(winner==2){
                    return ((tempPos.weight>pos1.weight)?tempPos:pos1);
                }
                else{
                    pos2=tempPos;
                    
                    newPos.weight=0;
                    a=((ai_x-4)>=0)?(ai_x-4):0;
                    b=((ai_x+4)<=14)?(ai_x+4):14;
                    c=((ai_y-4)>=0)?(ai_y-4):0;
                    d=((ai_y+4)<=14)?(ai_y+4):14;
                    
                    for(int i=0;i<15;i++){
                        for(int j=0;j<15;j++)
                            if(point[i][j]!=0)
                                point[i][j]=(point[i][j]==1)?2:1;
                    }
                    
                    for(int i=a;i<=b;i++){
                        for(int j=c;j<=d;j++){
                            s=cal(i, j,point);
                            if(newPos.weight<s){
                                newPos.weight=s;
                                newPos.x=i;
                                newPos.y=j;
                            }
                        }
                    }
                    
                    oldPos.weight=0;
                    a=((tempPos.x-4)>=0)?(tempPos.x-4):0;
                    b=((tempPos.x+4)<=14)?(tempPos.x+4):14;
                    c=((tempPos.y-4)>=0)?(tempPos.y-4):0;
                    d=((tempPos.y+4)<=14)?(tempPos.y+4):14;
                    for(int i=a;i<=b;i++){
                        for(int j=c;j<=d;j++){
                            s=cal(i, j,point);
                            if(oldPos.weight<s){
                                oldPos.weight=s;
                                oldPos.x=i;
                                oldPos.y=j;
                            }
                        }
                    }
                    tempPos=(newPos.weight>=oldPos.weight)?newPos:oldPos;
                    ai_x=tempPos.x;ai_y=tempPos.y;
                    
                    point[tempPos.x][tempPos.y]=2;
                    winner=judge(tempPos.x,tempPos.y,2,point);
                    if(winner==2){
                        return pos_player_win;
                    }
                    else{
                        newPos.weight=0;
                        a=((player_x-4)>=0)?(player_x-4):0;
                        b=((player_x+4)<=14)?(player_x+4):14;
                        c=((player_y-4)>=0)?(player_y-4):0;
                        d=((player_y+4)<=14)?(player_y+4):14;
                        
                        for(int i=0;i<15;i++){
                            for(int j=0;j<15;j++)
                                if(point[i][j]!=0)
                                    point[i][j]=(point[i][j]==1)?2:1;
                        }
                        
                        for(int i=a;i<=b;i++){
                            for(int j=c;j<=d;j++){
                                s=cal(i, j,point);
                                if(newPos.weight<s){
                                    newPos.weight=s;
                                    newPos.x=i;
                                    newPos.y=j;
                                }
                            }
                        }
                        
                        oldPos.weight=0;
                        a=((tempPos.x-4)>=0)?(tempPos.x-4):0;
                        b=((tempPos.x+4)<=14)?(tempPos.x+4):14;
                        c=((tempPos.y-4)>=0)?(tempPos.y-4):0;
                        d=((tempPos.y+4)<=14)?(tempPos.y+4):14;
                        for(int i=a;i<=b;i++){
                            for(int j=c;j<=d;j++){
                                s=cal(i, j,point);
                                if(oldPos.weight<s){
                                    oldPos.weight=s;
                                    oldPos.x=i;
                                    oldPos.y=j;
                                }
                            }
                        }
                        tempPos=(newPos.weight>=oldPos.weight)?newPos:oldPos;
                        player_x=tempPos.x;
                        player_y=tempPos.y;
                        point[tempPos.x][tempPos.y]=1;
                        winner=judge(tempPos.x,tempPos.y,2,point);
                        if(winner==2){
                            pos3=tempPos;
                            tempPos=(pos1.weight>pos2.weight)?pos1:pos2;
                            tempPos=(tempPos.weight>pos3.weight)?tempPos:pos3;
                            return tempPos;
                        }
                    }
                }
            }
        }
    }
    
    return pos_player_win;
}
int Chess::cal(int i, int j,int point[15][15])
{
    int l=0,p=0;
    //定义s为该点权值；a、b、c、d为四个方向的棋子和；k为距离该点的长度
    int s=0, a=0, b=0, c=0, d=0,k;
    //如果该点不空则权值为0
    if (point[i][j] != 0)
    {
        s = 0;
        return s;
    }
    
    //进行权值评估
    {
        //上下
        {
            //电脑五连
            {
                for (k = 1; k < 5; k++)
                    if (j - k >= 0 && point[i][j - k] == 2)
                        a++;
                    else break;
                for (k = 1; k < 5; k++)
                    if (j + k <= 15 && point[i][j + k] == 2)
                        a++;
                    else break;
                if (a >= 4)
                    s += 1000000;
            }
            //玩家五连
            {
                a = 0;
                for (k = 1; k < 5; k++)
                {
                    if (j - k >= 0 && point[i][j - k] == 1)
                        a++;
                    else break;
                }
                for (k = 1; k < 5; k++)
                {
                    if (j + k <= 15 && point[i][j + k] == 1)
                        a++;
                    else break;
                }
                if (a >= 4)
                    s += 666666;
            }
            //电脑活四
            {
                a = 0;
                for (k = 1; k < 5; k++)
                {
                    if (j - k >= 0 && point[i][j - k] == 2)
                        a++;
                    else if (j - k >= 0 && point[i][j - k] == 0)
                    {
                        a++;
                        break;
                    }
                    else break;
                }
                for (k = 1; k < 5; k++)
                {
                    if (j + k <= 15 && point[i][j + k] == 2)
                        a++;
                    else if (j + k <= 15 && point[i][j + k] == 0)
                    {
                        a++;
                        break;
                    }
                    else break;
                }
                if (a >= 5)
                    s += 444444;
            }
            //电脑冲四
            {
                if (j - 1 >= 0 && j + 3 <= 15 && point[i][j - 1] == 0 && point[i][j + 1] == 2 && point[i][j + 2] == 2 && point[i][j + 3] == 2&&((j-2>=0&&point[i][j-1]==0)||(j+4<=15&&point[i][j+4]==0)))
                {    s += 15000;l++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && point[i][j - 2] == 0 && point[i][j + 1] == 2 && point[i][j + 2] == 2 && point[i][j - 1] == 2 && ((j - 3 >= 0 && point[i][j - 3] == 0) || (j + 3 <= 15 && point[i][j + 3] == 0)))
                {    s += 15000;l++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && point[i][j - 3] == 0 && point[i][j + 1] == 2 && point[i][j - 2] == 2 && point[i][j - 1] == 2 && ((j - 4 >= 0 && point[i][j - 4] == 0) || (j + 2 <= 15 && point[i][j + 2] == 0)))
                {    s += 15000;l++;}
                else if (j - 4 >= 0 && point[i][j - 4] == 0 && point[i][j - 3] == 2 && point[i][j - 2] == 2 && point[i][j - 1] == 2 && ((j - 5 >= 0 && point[i][j - 5] == 0) || (j + 1 <= 15 && point[i][j + 1] == 0)))
                {    s += 15000;l++;}
                else if (j - 1 >= 0 && j + 3 <= 15 && point[i][j + 1] == 2 && point[i][j + 2] == 2 && point[i][j + 3] == 2 && point[i][j + 4] == 0)
                {    s += 15000;l++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && point[i][j + 1] == 2 && point[i][j + 2] == 2 && point[i][j + 3] == 0 && point[i][j - 1] == 2)
                {    s += 15000;l++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && point[i][j + 1] == 2 && point[i][j + 2] == 0 && point[i][j - 2] == 2 && point[i][j - 1] == 2)
                {    s += 15000;l++;}
                else if (j - 4 >= 0 && point[i][j + 1] == 0 && point[i][j - 3] == 2 && point[i][j - 2] == 2 && point[i][j - 1] == 2)
                {    s += 15000;l++;}
                else if (j + 4 <= 15 && point[i][j + 1] == 0 && point[i][j + 2] == 2 && point[i][j + 3] == 2 && point[i][j + 4] == 2)
                {    s += 15000;l++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && point[i][j + 1] == 2 && point[i][j + 2] == 2 && point[i][j - 2] == 2 && point[i][j - 1] == 2)
                {    s += 15000;l++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && point[i][j + 1] == 2 && point[i][j - 3] == 2 && point[i][j - 2] == 0 && point[i][j - 1] == 2)
                {    s += 15000;l++;}
                else if (j - 4 >= 0 && point[i][j - 4] == 2 && point[i][j - 3] == 0 && point[i][j - 2] == 2 && point[i][j - 1] == 2)
                {    s += 15000;l++;}
                else if (j + 4 <= 15 && point[i][j + 1] == 2 && point[i][j + 2] == 2 && point[i][j + 3] == 0 && point[i][j + 4] == 2)
                {    s += 15000;l++;}
                else if (j - 1 >= 0 && j + 3 <= 15 && point[i][j + 1] == 2 && point[i][j + 2] == 0 && point[i][j + 3] == 2 && point[i][j - 1] == 2)
                {    s += 15000;l++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && point[i][j + 2] == 2 && point[i][j + 1] == 0 && point[i][j - 2] == 2 && point[i][j - 1] == 2)
                {    s += 15000;l++;}
                else if (j - 4 >= 0 && point[i][j - 4] == 2 && point[i][j - 3] == 2 && point[i][j - 2] == 2 && point[i][j - 1] == 0)
                {    s += 15000;l++;}
                else if (j + 4 <= 15 && point[i][j + 1] == 2 && point[i][j + 2] == 0 && point[i][j + 3] == 2 && point[i][j + 4] == 2)
                {    s += 15000;l++;}
                else if (j - 1 >= 0 && j + 3 <= 15 && point[i][j + 1] == 0 && point[i][j + 2] == 2 && point[i][j + 3] == 2 && point[i][j - 1] == 2)
                {    s += 15000;l++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && point[i][j + 1] == 2 && point[i][j - 3] == 2 && point[i][j - 2] == 2 && point[i][j - 1] == 0)
                {    s += 15000;l++;}
                else if (j - 4 >= 0 && point[i][j - 4] == 2 && point[i][j - 3] == 2 && point[i][j - 2] == 0 && point[i][j - 1] == 2)
                {    s += 15000;l++;}
            }
            //玩家活四
            {
                a = 0;
                for (k = 1; k < 5; k++)
                {
                    if (j - k >= 0 && point[i][j - k] == 1)
                        a++;
                    else if (j - k >= 0 && point[i][j - k] == 0)
                    {
                        a++;
                        break;
                    }
                    else break;
                }
                for (k = 1; k < 5; k++)
                {
                    if (j + k <= 15 && point[i][j + k] == 1)
                        a++;
                    else if (j + k <= 15 && point[i][j + k] == 0)
                    {
                        a++;
                        break;
                    }
                    else break;
                }
                if (a >= 5)
                    s += 30000;
            }
            //电脑活三
            {
                if (j - 1 >= 0 && j + 4 <= 15 && point[i][j + 1] == 2 && point[i][j + 2] == 2 && point[i][j + 3] == 0 && point[i][j + 4] == 0 && point[i][j - 1] == 0)
                {   s += 1000;l++;}
                else if (j - 2 >= 0 && j + 3 <= 15 && point[i][j + 1] == 2 && point[i][j + 2] == 0 && point[i][j + 3] == 0 && point[i][j - 2] == 0 && point[i][j - 1] == 2)
                {   s += 1000;l++;}
                else if (j - 3 >= 0 && j + 2 <= 15 && point[i][j + 1] == 0 && point[i][j + 2] == 0 && point[i][j - 3] == 0 && point[i][j - 2] == 2 && point[i][j - 1] == 2)
                {   s += 1000;l++;}
                else if (j - 2 >= 0 && j + 3 <= 15 && point[i][j + 1] == 2 && point[i][j + 2] == 2 && point[i][j + 3] == 0 && point[i][j - 2] == 0 && point[i][j - 1] == 0)
                {   s += 1000;l++;}
                else if (j - 3 >= 0 && j + 2 <= 15 && point[i][j + 1] == 2 && point[i][j + 2] == 0 && point[i][j - 3] == 0 && point[i][j - 2] == 0 && point[i][j - 1] == 2)
                {   s += 1000;l++;}
                else if (j - 4 >= 0 && j + 1 <= 15 && point[i][j + 1] == 0 && point[i][j - 4] == 0 && point[i][j - 3] == 0 && point[i][j - 2] == 2 && point[i][j - 1] == 2)
                {   s += 1000;l++;}
            }
            //玩家冲四
            {
                if (j - 1 >= 0 && j + 3 <= 15 && point[i][j - 1] == 0 && point[i][j + 1] == 1 && point[i][j + 2] == 1 && point[i][j + 3] == 1 && ((j - 2 >= 0 && point[i][j - 1] == 0) || (j + 4 <= 15 && point[i][j + 4] == 0)))
                {    s += 800;p++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && point[i][j - 2] == 0 && point[i][j + 1] == 1 && point[i][j + 2] == 1 && point[i][j - 1] == 1 && ((j - 3 >= 0 && point[i][j - 3] == 0) || (j + 3 <= 15 && point[i][j + 3] == 0)))
                {    s += 800;p++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && point[i][j - 3] == 0 && point[i][j + 1] == 1 && point[i][j - 2] == 1 && point[i][j - 1] == 1 && ((j - 4 >= 0 && point[i][j - 4] == 0) || (j + 2 <= 15 && point[i][j + 2] == 0)))
                {    s += 800;p++;}
                else if (j - 4 >= 0 && point[i][j - 4] == 0 && point[i][j - 3] == 1 && point[i][j - 2] == 1 && point[i][j - 1] == 1 && ((j - 5 >= 0 && point[i][j - 5] == 0) || (j + 1 <= 15 && point[i][j + 1] == 0)))
                {    s += 800;p++;}
                else if (j - 1 >= 0 && j + 3 <= 15 && point[i][j + 1] == 1 && point[i][j + 2] == 1 && point[i][j + 3] == 1 && point[i][j + 4] == 0)
                {    s += 800;p++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && point[i][j + 1] == 1 && point[i][j + 2] == 1 && point[i][j + 3] == 0 && point[i][j - 1] == 1)
                {    s += 800;p++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && point[i][j + 1] == 1 && point[i][j + 2] == 0 && point[i][j - 2] == 1 && point[i][j - 1] == 1)
                {    s += 800;p++;}
                else if (j - 4 >= 0 && point[i][j + 1] == 0 && point[i][j - 3] == 1 && point[i][j - 2] == 1 && point[i][j - 1] == 1)
                {    s += 800;p++;}
                else if (j + 4 <= 15 && point[i][j + 1] == 0 && point[i][j + 2] == 1 && point[i][j + 3] == 1 && point[i][j + 4] == 1)
                {    s += 800;p++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && point[i][j + 1] == 1 && point[i][j + 2] == 1 && point[i][j - 2] == 1 && point[i][j - 1] == 0)
                {    s += 800;p++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && point[i][j + 1] == 1 && point[i][j - 3] == 1 && point[i][j - 2] == 0 && point[i][j - 1] == 1)
                {    s += 800;p++;}
                else if (j - 4 >= 0 && point[i][j - 4] == 1 && point[i][j - 3] == 0 && point[i][j - 2] == 1 && point[i][j - 1] == 1)
                {    s += 800;p++;}
                else if (j + 4 <= 15 && point[i][j + 1] == 1 && point[i][j + 2] == 1 && point[i][j + 3] == 0 && point[i][j + 4] == 1)
                {    s += 800;p++;}
                else if (j - 1 >= 0 && j + 3 <= 15 && point[i][j + 1] == 1 && point[i][j + 2] == 0 && point[i][j + 3] == 1 && point[i][j - 1] == 1)
                {    s += 800;p++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && point[i][j + 2] == 1 && point[i][j + 1] == 0 && point[i][j - 2] == 1 && point[i][j - 1] == 1)
                {    s += 800;p++;}
                else if (j - 4 >= 0 && point[i][j - 4] == 1 && point[i][j - 3] == 1 && point[i][j - 2] == 1 && point[i][j - 1] == 0)
                {    s += 800;p++;}
                else if (j + 4 <= 15 && point[i][j + 1] == 1 && point[i][j + 2] == 0 && point[i][j + 3] == 1 && point[i][j + 4] == 1)
                {    s += 800;p++;}
                else if (j - 1 >= 0 && j + 3 <= 15 && point[i][j + 1] == 0 && point[i][j + 2] == 1 && point[i][j + 3] == 1 && point[i][j - 1] == 1)
                {    s += 800;p++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && point[i][j + 1] == 1 && point[i][j - 3] == 1 && point[i][j - 2] == 1 && point[i][j - 1] == 0)
                {    s += 800;p++;}
                else if (j - 4 >= 0 && point[i][j - 4] == 1 && point[i][j - 3] == 1 && point[i][j - 2] == 0 && point[i][j - 1] == 1)
                {    s += 800;p++;}
            }
            //电脑冲三
            {
                if (j - 1 >= 0 && j + 4 <= 15 && point[i][j + 1] == 2 && point[i][j + 2] == 0 && point[i][j + 3] == 2 && point[i][j + 4] == 0 && point[i][j - 1] == 0)
                    s += 550;
                else if (j - 2 >= 0 && j + 3 <= 15 && point[i][j + 1] == 0 && point[i][j + 2] == 2 && point[i][j + 3] == 0 && point[i][j - 2] == 0 && point[i][j - 1] == 2)
                    s += 550;
                else if (j - 4 >= 0 && j + 1 <= 15 && point[i][j + 1] == 0 && point[i][j - 4] == 0 && point[i][j - 3] == 2 && point[i][j - 2] == 2 && point[i][j - 1] == 0)
                    s += 550;
                else if (j - 1 >= 0 && j + 4 <= 15 && point[i][j + 1] == 0 && point[i][j + 2] == 2 && point[i][j + 3] == 2 && point[i][j + 4] == 0 && point[i][j - 1] == 0)
                    s += 550;
                else if (j - 3 >= 0 && j + 2 <= 15 && point[i][j + 1] == 2 && point[i][j + 2] == 0 && point[i][j - 3] == 0 && point[i][j - 2] == 2 && point[i][j - 1] == 0)
                    s += 550;
                else if (j - 4 >= 0 && j + 1 <= 15 && point[i][j + 1] == 0 && point[i][j - 4] == 0 && point[i][j - 3] == 2 && point[i][j - 2] == 0 && point[i][j - 1] == 2)
                    s += 550;
            }
            //玩家活三
            {
                if (j - 1 >= 0 && j + 4 <= 15 && point[i][j + 1] == 1 && point[i][j + 2] == 1 && point[i][j + 3] == 0 && point[i][j + 4] == 0 && point[i][j - 1] == 0)
                {    s += 300;p++;}
                else if (j - 2 >= 0 && j + 3 <= 15 && point[i][j + 1] == 1 && point[i][j + 2] == 0 && point[i][j + 3] == 0 && point[i][j - 2] == 0 && point[i][j - 1] == 1)
                {    s += 300;p++;}
                else if (j - 3 >= 0 && j + 2 <= 15 && point[i][j + 1] == 0 && point[i][j + 2] == 0 && point[i][j - 3] == 0 && point[i][j - 2] == 1 && point[i][j - 1] == 1)
                {    s += 300;p++;}
                else if (j - 2 >= 0 && j + 3 <= 15 && point[i][j + 1] == 1 && point[i][j + 2] == 1 && point[i][j + 3] == 0 && point[i][j - 2] == 0 && point[i][j - 1] == 0)
                {    s += 300;p++;}
                else if (j - 3 >= 0 && j + 2 <= 15 && point[i][j + 1] == 1 && point[i][j + 2] == 0 && point[i][j - 3] == 0 && point[i][j - 2] == 0 && point[i][j - 1] == 1)
                {    s += 300;p++;}
                else if (j - 4 >= 0 && j + 1 <= 15 && point[i][j + 1] == 0 && point[i][j - 4] == 0 && point[i][j - 3] == 0 && point[i][j - 2] == 1 && point[i][j - 1] == 1)
                {    s += 300;p++;}
            }
            //电脑活二
            {
                if (j - 2 >= 0 && j + 2 <= 15 && point[i][j - 2] == 0 && point[i][j - 1] == 0 && point[i][j + 1] == 2 && point[i][j + 2] == 0)
                    s += 200;
                else if (j - 3 >= 0 && j + 1 <= 15 && point[i][j - 2] == 0 && point[i][j - 1] == 2 && point[i][j + 1] == 0 && point[i][j - 3] == 0)
                    s += 200;
                else if (j - 1 >= 0 && j + 3 <= 15 && point[i][j + 2] == 0 && point[i][j - 1] == 0 && point[i][j + 1] == 2 && point[i][j + 3] == 0)
                    s += 200;
                else if (j - 2 >= 0 && j + 2 <= 15 && point[i][j - 2] == 0 && point[i][j - 1] == 2 && point[i][j + 1] == 0 && point[i][j + 2] == 0)
                    s += 200;
            }
            //玩家冲三
            {
                if (j - 1 >= 0 && j + 4 <= 15 && point[i][j + 1] == 1 && point[i][j + 2] == 0 && point[i][j + 3] == 1 && point[i][j + 4] == 0 && point[i][j - 1] == 0)
                    s += 180;
                else if (j - 2 >= 0 && j + 3 <= 15 && point[i][j + 1] == 0 && point[i][j + 2] == 1 && point[i][j + 3] == 0 && point[i][j - 2] == 0 && point[i][j - 1] == 1)
                    s += 180;
                else if (j - 4 >= 0 && j + 1 <= 15 && point[i][j + 1] == 0 && point[i][j - 4] == 0 && point[i][j - 3] == 1 && point[i][j - 2] == 1 && point[i][j - 1] == 0)
                    s += 180;
                else if (j - 1 >= 0 && j + 4 <= 15 && point[i][j + 1] == 0 && point[i][j + 2] == 1 && point[i][j + 3] == 1 && point[i][j + 4] == 0 && point[i][j - 1] == 0)
                    s += 180;
                else if (j - 3 >= 0 && j + 2 <= 15 && point[i][j + 1] == 1 && point[i][j + 2] == 0 && point[i][j - 3] == 0 && point[i][j - 2] == 1 && point[i][j - 1] == 0)
                    s += 180;
                else if (j - 4 >= 0 && j + 1 <= 15 && point[i][j + 1] == 0 && point[i][j - 4] == 0 && point[i][j - 3] == 1 && point[i][j - 2] == 0 && point[i][j - 1] == 1)
                    s += 180;
            }
            //电脑冲二
            {
                if (j - 2 >= 0 && j + 3 <= 15 && point[i][j - 2] == 0 && point[i][j - 1] == 0 && point[i][j + 1] == 0 && point[i][j + 2] == 2 && point[i][j + 3] == 0)
                    s += 100;
                else if (j - 4 >= 0 && j + 1 <= 15 && point[i][j - 2] == 2 && point[i][j - 1] == 0 && point[i][j + 1] == 0 && point[i][j - 3] == 0 && point[i][j - 4] == 0)
                    s += 100;
                else if (j - 1 >= 0 && j + 4 <= 15 && point[i][j + 2] == 2 && point[i][j - 1] == 0 && point[i][j + 1] == 0 && point[i][j + 3] == 0 && point[i][j + 4] == 0)
                    s += 100;
                else if (j - 3 >= 0 && j + 2 <= 15 && point[i][j - 2] == 2 && point[i][j - 1] == 0 && point[i][j + 1] == 0 && point[i][j + 2] == 0 && point[i][j - 3] == 0)
                    s += 100;
            }
            //玩家活二
            {
                if (j - 2 >= 0 && j + 2 <= 15 && point[i][j - 2] == 0 && point[i][j - 1] == 0 && point[i][j + 1] == 1 && point[i][j + 2] == 0)
                    s += 50;
                else if (j - 3 >= 0 && j + 1 <= 15 && point[i][j - 2] == 0 && point[i][j - 1] == 1 && point[i][j + 1] == 0 && point[i][j - 3] == 0)
                    s += 50;
                else if (j - 1 >= 0 && j + 3 <= 15 && point[i][j + 2] == 0 && point[i][j - 1] == 0 && point[i][j + 1] == 1 && point[i][j + 3] == 0)
                    s += 50;
                else if (j - 2 >= 0 && j + 2 <= 15 && point[i][j - 2] == 0 && point[i][j - 1] == 1 && point[i][j + 1] == 0 && point[i][j + 2] == 0)
                    s += 50;
            }
            //玩家冲二
            {
                if (j - 2 >= 0 && j + 3 <= 15 && point[i][j - 2] == 0 && point[i][j - 1] == 0 && point[i][j + 1] == 0 && point[i][j + 2] == 2 && point[i][j + 3] == 0)
                    s += 10;
                else if (j - 4 >= 0 && j + 1 <= 15 && point[i][j - 2] == 1 && point[i][j - 1] == 0 && point[i][j + 1] == 0 && point[i][j - 3] == 0 && point[i][j - 4] == 0)
                    s += 10;
                else if (j - 1 >= 0 && j + 4 <= 15 && point[i][j + 2] == 1 && point[i][j - 1] == 0 && point[i][j + 1] == 0 && point[i][j + 3] == 0 && point[i][j + 4] == 0)
                    s += 10;
                else if (j - 3 >= 0 && j + 2 <= 15 && point[i][j - 2] == 1 && point[i][j - 1] == 0 && point[i][j + 1] == 0 && point[i][j + 2] == 0 && point[i][j - 3] == 0)
                    s += 10;
            }
        }
        //左右
        {
            //电脑五连22222
            {
                for (k = 1; k <= 5; k++)
                    if (i + k <= 15 && point[i + k][j] == 2)
                        b++;
                    else break;
                for (k = 1; k <= 5; k++)
                    if (i - k >= 0 && point[i - k][j] == 2)
                        b++;
                    else break;
                if (b >= 4)
                    s = 1000000;
            }
            //玩家五连11111
            {
                b = 0;
                for (k = 1; k < 5; k++)
                {
                    if (i - k >= 0 && point[i - k][j] == 1)
                        b++;
                    else break;
                }
                for (k = 1; k < 5; k++)
                {
                    if (i + k <= 15 && point[i + k][j] == 1)
                        b++;
                    else break;
                }
                if (b >= 4)
                    s += 666666;
            }
            //电脑活四+2222+
            {
                b = 0;
                for (k = 1; k < 5; k++)
                {
                    if (i - k >= 0 && point[i - k][j - k] == 2)
                        b++;
                    else if (i - k >= 0 && point[i - k][j] == 0)
                    {
                        b++;
                        break;
                    }
                    else break;
                }
                for (k = 1; k < 5; k++)
                {
                    if (i + k <= 15 && point[i - k][j] == 2)
                        b++;
                    else if (i + k <= 15 && point[i - k][j] == 0)
                    {
                        b++;
                        break;
                    }
                    else break;
                }
                if (b >= 5)
                    s += 444444;
            }
            //电脑冲四
            {
                //+22221
                if (i - 1 >= 0 && i + 3 <= 15 && point[i - 1][j] == 0 && point[i + 1][j] == 2 && point[i + 2][j] == 2 && point[i + 3][j] == 2 && ((i - 2 >= 0 && point[i-2][j ] == 0) || (j + 4 <= 15 && point[i+4][j ] == 0)))
                {    s += 15000;l++;}
                else if (i - 2 >= 0 && i + 2 <= 15 && point[i - 2][j] == 0 && point[i + 1][j] == 2 && point[i + 2][j] == 2 && point[i - 1][j] == 2 && ((i - 3 >= 0 && point[i-3][j ] == 0) || (i + 3 <= 15 && point[i+3][j ] == 0)))
                {    s += 15000;l++;}
                else if (i - 3 >= 0 && i + 1 <= 15 && point[i - 3][j] == 0 && point[i + 1][j] == 2 && point[i - 2][j] == 2 && point[i - 1][j] == 2 && ((i - 4 >= 0 && point[i - 4][j] == 0) || (i + 2 <= 15 && point[i + 2][j] == 0)))
                {    s += 15000;l++;}
                else if (i - 4 >= 0 && point[i - 4][j] == 0 && point[i - 3][j] == 2 && point[i - 2][j] == 2 && point[i - 1][j] == 2 && ((i - 5 >= 0 && point[i - 5][j] == 0) || (i + 1 <= 15 && point[i + 1][j] == 0)))
                {    s += 15000;l++;}
                //12222+
                else if (i - 1 >= 0 && i + 3 <= 15 && point[i + 1][j] == 2 && point[i + 2][j] == 2 && point[i + 3][j] == 2 && point[i + 4][j] == 0)
                {    s += 15000;l++;}
                else if (i - 2 >= 0 && i + 2 <= 15 && point[i + 1][j] == 2 && point[i + 2][j] == 2 && point[i + 3][j] == 0 && point[i - 1][j] == 2)
                {    s += 15000;l++;}
                else if (i - 3 >= 0 && i + 1 <= 15 && point[i + 1][j] == 2 && point[i + 2][j] == 0 && point[i - 2][j] == 2 && point[i - 1][j] == 2)
                {    s += 15000;l++;}
                else if (i - 4 >= 0 && point[i + 1][j] == 0 && point[i - 3][j] == 2 && point[i - 2][j] == 2 && point[i - 1][j] == 2)
                {    s += 15000;l++;}
                //2+222
                else if (i + 4 <= 15 && point[i + 1][j] == 0 && point[i + 2][j] == 2 && point[i + 3][j] == 2 && point[i + 4][j] == 2)
                {    s += 15000;l++;}
                else if (i - 2 >= 0 && i + 2 <= 15 && point[i + 1][j] == 2 && point[i + 2][j] == 2 && point[i - 2][j] == 2 && point[i - 1][j] == 2)
                {    s += 15000;l++;}
                else if (i - 3 >= 0 && i + 1 <= 15 && point[i + 1][j] == 2 && point[i - 3][j] == 2 && point[i - 2][j] == 0 && point[i - 1][j] == 2)
                {    s += 15000;l++;}
                else if (i - 4 >= 0 && point[i - 4][j] == 2 && point[i - 3][j] == 0 && point[i - 2][j] == 2 && point[i - 1][j] == 2)
                {    s += 15000;l++;}
                //222+2
                else if (i + 4 <= 15 && point[i + 1][j] == 2 && point[i + 2][j] == 2 && point[i + 3][j] == 0 && point[i + 4][j] == 2)
                {    s += 15000;l++;}
                else if (i - 1 >= 0 && i + 3 <= 15 && point[i + 1][j] == 2 && point[i + 2][j] == 0 && point[i + 3][j] == 2 && point[i - 1][j] == 2)
                {    s += 15000;l++;}
                else if (i - 2 >= 0 && i + 2 <= 15 && point[i + 2][j] == 2 && point[i + 1][j] == 0 && point[i - 2][j] == 2 && point[i - 1][j] == 2)
                {    s += 15000;l++;}
                else if (i - 4 >= 0 && point[i - 4][j] == 2 && point[i - 3][j] == 2 && point[i - 2][j] == 2 && point[i - 1][j] == 0)
                {    s += 15000;l++;}
                //22+22
                else if (i + 4 <= 15 && point[i + 1][j] == 2 && point[i + 2][j] == 0 && point[i + 3][j] == 2 && point[i + 4][j] == 2)
                {    s += 15000;l++;}
                else if (i - 1 >= 0 && i + 3 <= 15 && point[i + 1][j] == 0 && point[i + 2][j] == 2 && point[i + 3][j] == 2 && point[i - 1][j] == 2)
                {    s += 15000;l++;}
                else if (i - 3 >= 0 && i + 1 <= 15 && point[i + 1][j] == 2 && point[i - 3][j] == 2 && point[i - 2][j] == 2 && point[i - 1][j] == 0)
                {    s += 15000;l++;}
                else if (i - 4 >= 0 && point[i - 4][j] == 2 && point[i - 3][j] == 2 && point[i - 2][j] == 0 && point[i - 1][j] == 2)
                {    s += 15000;l++;}
            }
            //玩家活四+1111+
            {
                b = 0;
                for (k = 1; k < 5; k++)
                {
                    if (i - k >= 0 && point[i - k][j] == 1)
                        b++;
                    else if (i - k >= 0 && point[i - k][j] == 0)
                    {
                        b++;
                        break;
                    }
                    else break;
                }
                for (k = 1; k < 5; k++)
                {
                    if (i + k <= 15 && point[i + k][j] == 1)
                        b++;
                    else if (i + k <= 15 && point[i + k][j] == 0)
                    {
                        b++;
                        break;
                    }
                    else break;
                }
                if (b >= 5)
                    s += 30000;
            }
            //电脑活三
            {
                //+222++
                if (i - 1 >= 0 && i + 4 <= 15 && point[i + 1][j] == 2 && point[i + 2][j] == 2 && point[i + 3][j] == 0 && point[i + 4][j] == 0 && point[i - 1][j] == 0)
                {   s += 1000;l++;}
                else if (i - 2 >= 0 && i + 3 <= 15 && point[i + 1][j] == 2 && point[i + 2][j] == 0 && point[i + 3][j] == 0 && point[i - 2][j] == 0 && point[i - 1][j] == 2)
                {   s += 1000;l++;}
                else if (i - 3 >= 0 && i + 2 <= 15 && point[i + 1][j] == 0 && point[i + 2][j] == 0 && point[i - 3][j] == 0 && point[i - 2][j] == 2 && point[i - 1][j] == 2)
                {   s += 1000;l++;}
                //++222+
                else if (i - 2 >= 0 && i + 3 <= 15 && point[i + 1][j] == 2 && point[i + 2][j] == 2 && point[i + 3][j] == 0 && point[i - 2][j] == 0 && point[i - 1][j] == 0)
                {   s += 1000;l++;}
                else if (i - 3 >= 0 && i + 2 <= 15 && point[i + 1][j] == 2 && point[i + 2][j] == 0 && point[i - 3][j] == 0 && point[i - 2][j] == 0 && point[i - 1][j] == 2)
                {   s += 1000;l++;}
                else if (i - 4 >= 0 && i + 1 <= 15 && point[i + 1][j] == 0 && point[i - 4][j] == 0 && point[i - 3][j] == 0 && point[i - 2][j] == 2 && point[i - 1][j] == 2)
                {   s += 1000;l++;}
            }
            //玩家冲四
            {
                //+11112
                if (i - 1 >= 0 && i + 3 <= 15 && point[i - 1][j] == 0 && point[i + 1][j] == 1 && point[i + 2][j] == 1 && point[i + 3][j] == 1 && ((i - 2 >= 0 && point[i - 2][j] == 0) || (i + 4 <= 15 && point[i + 4][j] == 0)))
                {    s += 800;p++;}
                else if (i - 2 >= 0 && i + 2 <= 15 && point[i - 2][j] == 0 && point[i + 1][j] == 1 && point[i + 2][j] == 1 && point[i - 1][j] == 1 && ((i - 3 >= 0 && point[i - 3][j] == 0) || (i + 3 <= 15 && point[i + 3][j] == 0)))
                {    s += 800;p++;}
                else if (i - 3 >= 0 && i + 1 <= 15 && point[i - 3][j] == 0 && point[i + 1][j] == 1 && point[i - 2][j] == 1 && point[i - 1][j] == 1 && ((i - 4 >= 0 && point[i - 4][j] == 0) || (i + 2 <= 15 && point[i + 2][j] == 0)))
                {    s += 800;p++;}
                else if (i - 4 >= 0 && point[i - 4][j] == 0 && point[i - 3][j] == 1 && point[i - 2][j] == 1 && point[i - 1][j] == 1 && ((i - 5 >= 0 && point[i - 5][j] == 0) || (i + 1 <= 15 && point[i + 1][j] == 0)))
                {    s += 800;p++;}
                //21111+
                else if (i - 1 >= 0 && i + 3 <= 15 && point[i + 1][j] == 1 && point[i + 2][j] == 1 && point[i + 3][j] == 1 && point[i + 4][j] == 0)
                {    s += 800;p++;}
                else if (i - 2 >= 0 && i + 2 <= 15 && point[i + 1][j] == 1 && point[i + 2][j] == 1 && point[i + 3][j] == 0 && point[i - 1][j] == 1)
                {    s += 800;p++;}
                else if (i - 3 >= 0 && i + 1 <= 15 && point[i + 1][j] == 1 && point[i + 2][j] == 0 && point[i - 2][j] == 2 && point[i - 1][j] == 2)
                {    s += 800;p++;}
                else if (i - 4 >= 0 && point[i + 1][j] == 0 && point[i - 3][j] == 1 && point[i - 2][j] == 1 && point[i - 1][j] == 1)
                {    s += 800;p++;}
                //1+111
                else if (i + 4 <= 15 && point[i + 1][j] == 0 && point[i + 2][j] == 1 && point[i + 3][j] == 1 && point[i + 4][j] == 1)
                {    s += 800;p++;}
                else if (i - 2 >= 0 && i + 2 <= 15 && point[i + 1][j] == 1 && point[i + 2][j] == 1 && point[i - 2][j] == 1 && point[i - 1][j] == 0)
                {    s += 800;p++;}
                else if (i - 3 >= 0 && i + 1 <= 15 && point[i + 1][j] == 1 && point[i - 3][j] == 1 && point[i - 2][j] == 0 && point[i - 1][j] == 1)
                {    s += 800;p++;}
                else if (i - 4 >= 0 && point[i - 4][j] == 1 && point[i - 3][j] == 0 && point[i - 2][j] == 1 && point[i - 1][j] == 1)
                {    s += 800;p++;}
                //111+1
                else if (i + 4 <= 15 && point[i + 1][j] == 1 && point[i + 2][j] == 1 && point[i + 3][j] == 0 && point[i + 4][j] == 1)
                {    s += 800;p++;}
                else if (i - 1 >= 0 && i + 3 <= 15 && point[i + 1][j] == 1 && point[i + 2][j] == 0 && point[i + 3][j] == 1 && point[i - 1][j] == 1)
                {    s += 800;p++;}
                else if (i - 2 >= 0 && i + 2 <= 15 && point[i + 2][j] == 1 && point[i + 1][j] == 0 && point[i - 2][j] == 1 && point[i - 1][j] == 1)
                {    s += 800;p++;}
                else if (i - 4 >= 0 && point[i - 4][j] == 1 && point[i - 3][j] == 1 && point[i - 2][j] == 1 && point[i - 1][j] == 0)
                {    s += 800;p++;}
                //11+11
                else if (i + 4 <= 15 && point[i + 1][j] == 1 && point[i + 2][j] == 0 && point[i + 3][j] == 1 && point[i + 4][j] == 1)
                {    s += 800;p++;}
                else if (i - 1 >= 0 && i + 3 <= 15 && point[i + 1][j] == 0 && point[i + 2][j] == 1 && point[i + 3][j] == 1 && point[i - 1][j] == 1)
                {    s += 800;p++;}
                else if (i - 3 >= 0 && i + 1 <= 15 && point[i + 1][j] == 1 && point[i - 3][j] == 1 && point[i - 2][j] == 1 && point[i - 1][j] == 0)
                {    s += 800;p++;}
                else if (i - 4 >= 0 && point[i - 4][j] == 1 && point[i - 3][j] == 1 && point[i - 2][j] == 0 && point[i - 1][j] == 1)
                {    s += 800;p++;}
            }
            //电脑冲三
            {
                //+22+2+
                if (i - 1 >= 0 && i + 4 <= 15 && point[i + 1][j] == 2 && point[i + 2][j] == 0 && point[i + 3][j] == 2 && point[i + 4][j] == 0 && point[i - 1][j] == 0)
                    s += 550;
                else if (i - 2 >= 0 && i + 3 <= 15 && point[i + 1][j] == 0 && point[i + 2][j] == 2 && point[i + 3][j] == 0 && point[i - 2][j] == 0 && point[i - 1][j] == 2)
                    s += 550;
                else if (i - 4 >= 0 && i + 1 <= 15 && point[i + 1][j] == 0 && point[i - 4][j] == 0 && point[i - 3][j] == 2 && point[i - 2][j] == 2 && point[i - 1][j] == 0)
                    s += 550;
                //+2+22+
                else if (i - 1 >= 0 && i + 4 <= 15 && point[i + 1][j] == 0 && point[i + 2][j] == 2 && point[i + 3][j] == 2 && point[i + 4][j] == 0 && point[i - 1][j] == 0)
                    s += 550;
                else if (i - 3 >= 0 && i + 2 <= 15 && point[i + 1][j] == 2 && point[i + 2][j] == 0 && point[i - 3][j] == 0 && point[i - 2][j] == 2 && point[i - 1][j] == 0)
                    s += 550;
                else if (i - 4 >= 0 && i + 1 <= 15 && point[i + 1][j] == 0 && point[i - 4][j] == 0 && point[i - 3][j] == 2 && point[i - 2][j] == 0 && point[i - 1][j] == 2)
                    s += 550;
            }
            //玩家活三
            {
                //+111++
                if (i - 1 >= 0 && i + 4 <= 15 && point[i + 1][j] == 1 && point[i + 2][j] == 1 && point[i + 3][j] == 0 && point[i + 4][j] == 0 && point[i - 1][j] == 0)
                {    s += 300;p++;}
                else if (i - 2 >= 0 && i + 3 <= 15 && point[i + 1][j] == 1 && point[i + 2][j] == 0 && point[i + 3][j] == 0 && point[i - 2][j] == 0 && point[i - 1][j] == 1)
                {    s += 300;p++;}
                else if (i - 3 >= 0 && i + 2 <= 15 && point[i + 1][j] == 0 && point[i + 2][j] == 0 && point[i - 3][j] == 0 && point[i - 2][j] == 1 && point[i - 1][j] == 1)
                {    s += 300;p++;}
                //++111+
                else if (i - 2 >= 0 && i + 3 <= 15 && point[i + 1][j] == 1 && point[i + 2][j] == 1 && point[i + 3][j] == 0 && point[i - 2][j] == 0 && point[i - 1][j] == 0)
                {    s += 300;p++;}
                else if (i - 3 >= 0 && i + 2 <= 15 && point[i + 1][j] == 1 && point[i + 2][j] == 0 && point[i - 3][j] == 0 && point[i - 2][j] == 0 && point[i - 1][j] == 1)
                {    s += 300;p++;}
                else if (i - 4 >= 0 && i + 1 <= 15 && point[i + 1][j] == 0 && point[i + 2][j] == 0 && point[i - 3][j] == 0 && point[i - 2][j] == 1 && point[i - 1][j] == 1)
                {    s += 300;p++;}
            }
            //电脑活二
            {
                //++22+
                if (i - 2 >= 0 && i + 2 <= 15 && point[i - 2][j] == 0 && point[i - 1][j] == 0 && point[i + 1][j] == 2 && point[i + 2][j] == 0)
                    s += 200;
                else if (i - 3 >= 0 && i + 1 <= 15 && point[i - 2][j] == 0 && point[i - 1][j] == 2 && point[i + 1][j] == 0 && point[i - 3][j] == 0)
                    s += 200;
                //+22+
                else if (i - 1 >= 0 && i + 3 <= 15 && point[i + 2][j] == 0 && point[i - 1][j] == 0 && point[i + 1][j] == 2 && point[i + 3][j] == 0)
                    s += 200;
                else if (i - 2 >= 0 && i + 2 <= 15 && point[i - 2][j] == 0 && point[i - 1][j] == 2 && point[i + 1][j] == 0 && point[i + 2][j] == 0)
                    s += 200;
            }
            //玩家冲三
            {
                //+11+1+
                if (i - 1 >= 0 && i + 4 <= 15 && point[i + 1][j] == 1 && point[i + 2][j] == 0 && point[i + 3][j] == 1 && point[i + 4][j] == 0 && point[i - 1][j] == 0)
                    s += 180;
                else if (i - 2 >= 0 && i + 3 <= 15 && point[i + 1][j] == 0 && point[i + 2][j] == 1 && point[i + 3][j] == 0 && point[i - 2][j] == 0 && point[i - 1][j] == 1)
                    s += 180;
                else if (i - 4 >= 0 && i + 1 <= 15 && point[i + 1][j] == 0 && point[i - 4][j] == 0 && point[i - 3][j] == 1 && point[i - 2][j] == 1 && point[i - 1][j] == 0)
                    s += 180;
                //+1+11+
                else if (i - 1 >= 0 && i + 4 <= 15 && point[i + 1][j] == 0 && point[i + 2][j] == 1 && point[i + 3][j] == 1 && point[i + 4][j] == 0 && point[i - 1][j] == 0)
                    s += 180;
                else if (i - 3 >= 0 && i + 2 <= 15 && point[i + 1][j] == 1 && point[i + 2][j] == 0 && point[i - 3][j] == 0 && point[i - 2][j] == 1 && point[i - 1][j] == 0)
                    s += 180;
                else if (i - 4 >= 0 && i + 1 <= 15 && point[i + 1][j] == 0 && point[i - 4][j] == 0 && point[i - 3][j] == 1 && point[i - 2][j] == 0 && point[i - 1][j] == 1)
                    s += 180;
            }
            //电脑冲二
            {
                //+2+2++
                if (i - 2 >= 0 && i + 3 <= 15 && point[i - 2][j] == 0 && point[i - 1][j] == 0 && point[i + 1][j] == 0 && point[i + 2][j] == 2 && point[i + 3][j] == 0)
                    s += 100;
                else if (i - 4 >= 0 && i + 1 <= 15 && point[i - 2][j] == 2 && point[i - 1][j] == 0 && point[i + 1][j] == 0 && point[i - 3][j] == 0 && point[i - 4][j] == 0)
                    s += 100;
                //++2+2+
                else if (i - 1 >= 0 && i + 4 <= 15 && point[i + 2][j] == 2 && point[i - 1][j] == 0 && point[i + 1][j] == 0 && point[i + 3][j] == 0 && point[i + 4][j] == 0)
                    s += 100;
                else if (i - 3 >= 0 && i + 2 <= 15 && point[i - 2][j] == 2 && point[i - 1][j] == 0 && point[i + 1][j] == 0 && point[i + 2][j] == 0 && point[i - 3][j] == 0)
                    s += 100;
            }
            //玩家活二
            {
                //++11+
                if (i - 2 >= 0 && i + 2 <= 15 && point[i - 2][j] == 0 && point[i - 1][j] == 0 && point[i + 1][j] == 1 && point[i + 2][j] == 0)
                    s += 50;
                else if (i - 3 >= 0 && i + 1 <= 15 && point[i - 2][j] == 0 && point[i - 1][j] == 1 && point[i + 1][j] == 0 && point[i - 3][j] == 0)
                    s += 50;
                //+11++
                else if (i - 1 >= 0 && i + 3 <= 15 && point[i + 2][j] == 0 && point[i - 1][j] == 0 && point[i + 1][j] == 1 && point[i + 3][j] == 0)
                    s += 50;
                else if (i - 2 >= 0 && i + 2 <= 15 && point[i - 2][j] == 0 && point[i - 1][j] == 1 && point[i + 1][j] == 0 && point[i + 2][j] == 0)
                    s += 50;
            }
            //玩家冲二
            {
                //+1+1++
                if (i - 2 >= 0 && i + 3 <= 15 && point[i - 2][j] == 0 && point[i - 1][j] == 0 && point[i + 1][j] == 0 && point[i + 2][j] == 1 && point[i + 3][j] == 0)
                    s += 10;
                else if (i - 4 >= 0 && i + 1 <= 15 && point[i - 2][j] == 1 && point[i - 1][j] == 0 && point[i + 1][j] == 0 && point[i - 3][j] == 0 && point[i - 4][j] == 0)
                    s += 10;
                //++1+1+
                else if (i - 1 >= 0 && i + 4 <= 15 && point[i + 2][j] == 1 && point[i - 1][j] == 0 && point[i + 1][j] == 0 && point[i + 3][j] == 0 && point[i + 4][j] == 0)
                    s += 10;
                else if (i - 3 >= 0 && i + 2 <= 15 && point[i - 2][j] == 1 && point[i - 1][j] == 0 && point[i + 1][j] == 0 && point[i + 2][j] == 0 && point[i - 3][j] == 0)
                    s += 10;
            }
        }
        //“\”方向
        {
            //电脑五连
            {
                for (k = 1; k <= 5; k++)
                    if (i - k >= 0 && j - k >= 0 && point[i - k][j - k] == 2)
                        c++;
                    else break;
                for (k = 1; k <= 5; k++)
                    if (i + k <= 15 && j + k <= 15 && point[i + k][j + k] == 2)
                        c++;
                    else break;
                if (c >= 4)
                    s += 100000;
            }
            //玩家五连
            {
                c = 0;
                for (k = 1; k < 5; k++)
                {
                    if (j - k >= 0 && i - k >= 0 && point[i - k][j - k] == 1)
                        c++;
                    else break;
                }
                for (k = 1; k < 5; k++)
                {
                    if (j + k <= 15 && i + k <= 15 && point[i + k][j + k] == 1)
                        c++;
                    else break;
                }
                if (c >= 4)
                    s += 666666;
            }
            //电脑活四
            {
                c = 0;
                for (k = 1; k < 5; k++)
                {
                    if (j - k >= 0 && i - k >= 0 && point[i - k][j - k] == 2)
                        c++;
                    else if (j - k >= 0 && i - k >= 0 && point[i - k][j - k] == 0)
                    {
                        c++;
                        break;
                    }
                    else break;
                }
                for (k = 1; k < 5; k++)
                {
                    if (j + k <= 15 && i + k <= 15 && point[i + k][j + k] == 2)
                        c++;
                    else if (j + k <= 15 && i + k <= 15 && point[i + k][j + k] == 0)
                    {
                        c++;
                        break;
                    }
                    else break;
                }
                if (c >= 5)
                    s += 444444;
            }
            //电脑冲四
            {
                if (j - 1 >= 0 && i - 1 >= 0 && j + 3 <= 15 && j + 3 <= 15 && point[i - 1][j - 1] == 0 && point[i + 1][j + 1] == 2 && point[i + 2][j + 2] == 2 && point[i + 3][j + 3] == 2 && ((j - 2 >= 0 && i - i >= 0 && point[i - 2][j-2] == 0) || (i + 4 <= 15 && j + 4 <= 15 && point[i + 4][j+4] == 0)))
                {    s += 15000;l++;}
                else if (j - 2 >= 0 && i - 2 >= 0 && j + 2 <= 15 && i + 2 <= 15 && point[i - 2][j - 2] == 0 && point[i + 1][j + 1] == 2 && point[i + 2][j + 2] == 2 && point[i - 1][j - 1] == 2 && ((i - 3 >= 0 && j - 3 >= 0 && point[i - 3][j - 3] == 0) || (i + 3 <= 15 && j + 3 <= 15 && point[i + 3][j + 3] == 0)))
                {    s += 15000;l++;}
                else if (j - 3 >= 0 && i - 3 >= 0 && j + 1 <= 15 && i + 1 <= 15 && point[i - 3][j - 3] == 0 && point[i + 1][j + 1] == 2 && point[i - 2][j - 2] == 2 && point[i - 1][j - 1] == 2 && ((i - 4 >= 0 && j - 4 >= 0 && point[i - 4][j - 4] == 0) || (i + 2 <= 15 && j + 2 <= 15 && point[i + 2][j + 2] == 0)))
                {    s += 15000;l++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i - 4][j - 4] == 0 && point[i - 3][j - 3] == 2 && point[i - 2][j - 2] == 2 && point[i - 1][j - 1] == 2 && ((i - 5 >= 0 && j - 5 >= 0 && point[i -5][j - 5] == 0) || (i + 1 <= 15 && j + 1 <= 15 && point[i + 1][j + 1] == 0)))
                {    s += 15000;l++;}
                else if (j - 1 >= 0 && j + 3 <= 15 && i - 1 >= 0 && i + 3 <= 15 && point[i + 1][j + 1] == 2 && point[i + 2][j + 2] == 2 && point[i + 3][j + 3] == 2 && point[i + 4][j + 4] == 0)
                {    s += 15000;l++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i + 1][j + 1] == 2 && point[i + 2][j + 2] == 2 && point[i + 3][j + 3] == 0 && point[i - 1][j - 1] == 2)
                {    s += 15000;l++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && i - 3 >= 0 && i + 1 <= 15 && point[i + 1][j + 1] == 2 && point[i + 2][j + 2] == 0 && point[i - 2][j - 2] == 2 && point[i - 1][j - 1] == 2)
                {    s += 15000;l++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i + 1][j + 1] == 0 && point[i - 3][j - 3] == 2 && point[i - 2][j - 2] == 2 && point[i - 1][j - 1] == 2)
                {    s += 15000;l++;}
                else if (j + 4 <= 15 && i + 4 <= 15 && point[i + 1][j + 1] == 0 && point[i + 2][j + 2] == 2 && point[i + 3][j + 3] == 2 && point[i + 4][j + 4] == 2)
                {    s += 15000;l++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i + 1][j + 1] == 2 && point[i + 3][j + 2] == 2 && point[i - 2][j - 2] == 2 && point[i - 1][j - 1] == 2)
                {    s += 15000;l++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && i - 3 >= 0 && i + 1 <= 15 && point[i + 1][j + 1] == 2 && point[i - 3][j - 3] == 2 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 2)
                {    s += 15000;l++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i - 4][j - 4] == 2 && point[i - 3][j - 3] == 0 && point[i - 2][j - 2] == 2 && point[i - 1][j - 1] == 2)
                {    s += 15000;l++;}
                else if (j + 4 <= 15 && i + 4 <= 15 && point[i + 1][j + 1] == 2 && point[i + 2][j + 2] == 2 && point[i + 3][j + 3] == 0 && point[i + 4][j + 4] == 2)
                {    s += 15000;l++;}
                else if (j - 1 >= 0 && j + 3 <= 15 && i - 1 >= 0 && i + 3 <= 15 && point[i + 1][j + 1] == 2 && point[i + 2][j + 2] == 0 && point[i + 3][j + 3] == 2 && point[i - 1][j - 1] == 2)
                {    s += 15000;l++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i + 2][j + 2] == 2 && point[i + 1][j + 1] == 0 && point[i - 2][j - 2] == 2 && point[i - 1][j - 1] == 2)
                {    s += 15000;l++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i - 4][j - 4] == 2 && point[i - 3][j - 3] == 2 && point[i - 2][j - 2] == 2 && point[i - 1][j - 1] == 0)
                {    s += 15000;l++;}
                else if (j + 4 <= 15 && i + 4 <= 15 && point[i + 1][j + 1] == 2 && point[i + 2][j + 2] == 0 && point[i + 3][j + 3] == 2 && point[i + 4][j + 4] == 2)
                {    s += 15000;l++;}
                else if (j - 1 >= 0 && j + 3 <= 15 && i - 1 >= 0 && i + 3 <= 15 && point[i + 1][j + 1] == 0 && point[i + 2][j + 2] == 2 && point[i + 3][j + 3] == 2 && point[i - 1][j - 1] == 2)
                {    s += 15000;l++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && i - 3 >= 0 && i + 1 <= 15 && point[i + 1][j + 1] == 2 && point[i - 3][j - 3] == 2 && point[i - 2][j - 2] == 2 && point[i - 1][j - 1] == 0)
                {    s += 15000;l++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i - 4][j - 4] == 2 && point[i - 3][j - 3] == 2 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 2)
                {    s += 15000;l++;}
            }
            //玩家活四
            {
                c = 0;
                for (k = 1; k < 5; k++)
                {
                    if (j - k >= 0 && i - k >= 0 && point[i - k][j - k] == 1)
                        c++;
                    else if (j - k >= 0 && i - k >= 0 && point[i - k][j - k] == 0)
                    {
                        c++;
                        break;
                    }
                    else break;
                }
                for (k = 1; k < 5; k++)
                {
                    if (j + k <= 15 && i + k <= 15 && point[i + k][j + k] == 1)
                        c++;
                    else if (j + k <= 15 &&i + k <= 15  && point[i + k][j + k] == 0)
                    {
                        c++;
                        break;
                    }
                    else break;
                }
                if (c >=5)
                    s += 30000;
            }
            //电脑活三
            {
                if (j - 1 >= 0 && j + 4 <= 15 && i - 1 >= 0 && i + 4 <= 15 && point[i + 1][j + 1] == 2 && point[i + 2][j + 2] == 2 && point[i + 3][j + 3] == 0 && point[i + 4][j + 4] == 0 && point[i - 1][j - 1] == 0)
                {   s += 1000;l++;}
                else if (j - 2 >= 0 && j + 3 <= 15 && i - 2 >= 0 && i + 3 <= 15 && point[i + 1][j + 1] == 2 && point[i + 2][j + 2] == 0 && point[i + 3][j + 3] == 0 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 2)
                {   s += 1000;l++;}
                else if (j - 3 >= 0 && j + 2 <= 15 && i - 3 >= 0 && i + 2 <= 15 && point[i + 1][j + 1] == 0 && point[i + 2][j + 2] == 0 && point[i - 3][j - 3] == 0 && point[i - 2][j - 2] == 2 && point[i - 1][j - 1] == 2)
                {   s += 1000;l++;}
                else if (j - 2 >= 0 && j + 3 <= 15 && i - 2 >= 0 && i + 3 <= 15 && point[i + 1][j + 1] == 2 && point[i + 2][j + 2] == 2 && point[i + 3][j + 3] == 0 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 0)
                {   s += 1000;l++;}
                else if (j - 3 >= 0 && j + 2 <= 15 && i - 3 >= 0 && i + 2 <= 15 && point[i + 1][j + 1] == 2 && point[i + 2][j + 2] == 0 && point[i - 3][j - 3] == 0 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 2)
                {   s += 1000;l++;}
                else if (j - 4 >= 0 && j + 1 <= 15 && i - 4 >= 0 && i + 1 <= 15 && point[i + 1][j + 1] == 0 && point[i - 4][j - 4] == 0 && point[i - 3][j - 3] == 0 && point[i - 2][j - 2] == 2 && point[i - 1][j - 1] == 2)
                {   s += 1000;l++;}
            }
            //玩家冲四
            {
                if (j - 1 >= 0 && i - 1 >= 0 && j + 3 <= 15 && j + 3 <= 15 && point[i - 1][j - 1] == 0 && point[i + 1][j + 1] == 1 && point[i + 2][j + 2] == 1 && point[i + 3][j + 3] == 1 && ((j - 2 >= 0 && i - 2 >= 0 && point[i - 2][j - 2] == 0) || (i + 4 <= 15 && j + 4 <= 15 && point[i + 4][j + 4] == 0)))
                {    s += 800;p++;}
                else if (j - 2 >= 0 && i - 2 >= 0 && j + 2 <= 15 && i + 2 <= 15 && point[i - 2][j - 2] == 0 && point[i + 1][j + 1] == 1 && point[i + 2][j + 2] == 1 && point[i - 1][j - 1] == 1 && ((j - 3 >= 0 && i - 3 >= 0 && point[i - 3][j - 3] == 0) || (i + 3 <= 15 && j + 3 <= 15 && point[i + 3][j + 3] == 0)))
                {    s += 800;p++;}
                else if (j - 3 >= 0 && i - 3 >= 0 && j + 1 <= 15 && i + 1 <= 15 && point[i - 3][j - 3] == 0 && point[i + 1][j + 1] == 1 && point[i - 2][j - 2] == 1 && point[i - 1][j - 1] == 1 && ((j - 4 >= 0 && i - 4 >= 0 && point[i - 4][j - 4] == 0) || (i + 2 <= 15 && j + 2 <= 15 && point[i + 2][j + 2] == 0)))
                {    s += 800;p++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i - 4][j - 4] == 0 && point[i - 3][j - 3] == 1 && point[i - 2][j - 2] == 1 && point[i - 1][j - 1] == 1 && ((j - 5 >= 0 && i - 5 >= 0 && point[i - 5][j - 5] == 0) || (i + 1 <= 15 && j + 1 <= 15 && point[i + 1][j + 1] == 0)))
                {    s += 800;p++;}
                else if (j - 1 >= 0 && j + 3 <= 15 && i - 1 >= 0 && i + 3 <= 15 && point[i + 1][j + 1] == 1 && point[i + 2][j + 2] == 1 && point[i + 3][j + 3] == 1 && point[i + 4][j + 4] == 0)
                {    s += 800;p++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i + 1][j + 1] == 1 && point[i + 2][j + 2] == 1 && point[i + 3][j + 3] == 0 && point[i - 1][j - 1] == 1)
                {    s += 800;p++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && i - 3 >= 0 && i + 1 <= 15 && point[i + 1][j + 1] == 1 && point[i + 2][j + 2] == 0 && point[i - 2][j - 2] == 1 && point[i - 1][j - 1] == 1)
                {    s += 800;p++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i + 1][j + 1] == 0 && point[i - 3][j - 3] == 1 && point[i - 2][j - 2] == 1 && point[i - 1][j - 1] == 1)
                {    s += 800;p++;}
                else if (j + 4 <= 15 && i + 4 <= 15 && point[i + 1][j + 1] == 0 && point[i + 2][j + 2] == 1 && point[i + 3][j + 3] == 1 && point[i + 4][j + 4] == 1)
                {    s += 800;p++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i + 1][j + 1] == 1 && point[i + 3][j + 2] == 1 && point[i - 2][j - 2] == 1 && point[i - 1][j - 1] == 0)
                {    s += 800;p++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && i - 3 >= 0 && i + 1 <= 15 && point[i + 1][j + 1] == 1 && point[i - 3][j - 3] == 1 && point[i - 2][j - 1] == 0 && point[i - 1][j - 1] == 1)
                {    s += 800;p++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i - 4][j - 4] == 1 && point[i - 3][j - 3] == 0 && point[i - 2][j - 2] == 1 && point[i - 1][j - 1] == 1)
                {    s += 800;p++;}
                else if (j + 4 <= 15 && i + 4 <= 15 && point[i + 1][j + 1] == 1 && point[i + 2][j + 2] == 1 && point[i + 3][j + 3] == 0 && point[i + 4][j + 4] == 1)
                {    s += 800;p++;}
                else if (j - 1 >= 0 && j + 3 <= 15 && i - 1 >= 0 && i + 3 <= 15 && point[i + 1][j + 1] == 1 && point[i + 2][j + 2] == 0 && point[i + 3][j + 3] == 1 && point[i - 1][j - 1] == 1)
                {    s += 800;p++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i + 2][j + 2] == 1 && point[i + 1][j + 1] == 0 && point[i - 2][j - 2] == 1 && point[i - 1][j - 1] == 1)
                {    s += 800;p++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i - 4][j - 4] == 1 && point[i - 3][j - 3] == 1 && point[i - 2][j - 2] == 1 && point[i - 1][j - 1] == 0)
                {    s += 800;p++;}
                else if (j + 4 <= 15 && i + 4 <= 15 && point[i + 1][j + 1] == 1 && point[i + 2][j + 2] == 0 && point[i + 3][j + 3] == 1 && point[i + 4][j + 4] == 1)
                {    s += 800;p++;}
                else if (j - 1 >= 0 && j + 3 <= 15 && i - 1 >= 0 && i + 3 <= 15 && point[i + 1][j + 1] == 0 && point[i + 2][j + 2] == 1 && point[i + 3][j + 3] == 1 && point[i - 1][j - 1] == 1)
                {    s += 800;p++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && i - 3 >= 0 && i + 1 <= 15 && point[i + 1][j + 1] == 1 && point[i - 3][j - 3] == 1 && point[i - 2][j - 2] == 1 && point[i - 1][j - 1] == 0)
                {    s += 800;p++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i - 4][j - 4] == 1 && point[i - 3][j - 3] == 1 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 1)
                {    s += 800;p++;}
            }
            //电脑冲三
            {
                if (j - 1 >= 0 && j + 4 <= 15 && i - 1 >= 0 && i + 4 <= 15 && point[i + 1][j + 1] == 2 && point[i + 2][j + 2] == 0 && point[i + 3][j + 3] == 2 && point[i + 4][j + 4] == 0 && point[i - 1][j - 1] == 0)
                    s += 550;
                else if (j - 2 >= 0 && j + 3 <= 15 && i - 2 >= 0 && i + 3 <= 15 && point[i + 1][j + 1] == 0 && point[i + 2][j + 2] == 2 && point[i + 3][j + 3] == 0 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 2)
                    s += 550;
                else if (j - 4 >= 0 && j + 1 <= 15 && i - 4 >= 0 && i + 1 <= 15 && point[i + 1][j + 1] == 0 && point[i - 4][j - 4] == 0 && point[i - 3][j - 3] == 2 && point[i - 2][j - 2] == 2 && point[i - 1][j - 1] == 0)
                    s += 550;
                else if (j - 1 >= 0 && j + 4 <= 15 && i - 1 >= 0 && i + 4 <= 15 && point[i + 1][j + 1] == 0 && point[i + 2][j + 2] == 2 && point[i + 3][j + 3] == 2 && point[i + 4][j + 4] == 0 && point[i - 1][j - 1] == 0)
                    s += 550;
                else if (j - 3 >= 0 && j + 2 <= 15 && i - 3 >= 0 && i + 2 <= 15 && point[i + 1][j + 1] == 2 && point[i + 2][j + 2] == 0 && point[i - 3][j - 3] == 0 && point[i - 2][j - 2] == 2 && point[i - 1][j - 1] == 0)
                    s += 550;
                else if (j - 4 >= 0 && j + 1 <= 15 && i - 4 >= 0 && i + 1 <= 15 && point[i + 1][j + 1] == 0 && point[i - 4][j - 4] == 0 && point[i - 3][j - 3] == 2 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 2)
                    s += 550;
            }
            //玩家活三
            {
                if (j - 1 >= 0 && j + 4 <= 15 && i - 1 >= 0 && i + 4 <= 15 && point[i + 1][j + 1] == 1 && point[i + 2][j + 2] == 1 && point[i + 3][j + 3] == 0 && point[i + 4][j + 4] == 0 && point[i - 1][j - 1] == 0)
                {    s += 300;p++;}
                else if (j - 2 >= 0 && j + 3 <= 15 && i - 2 >= 0 && i + 3 <= 15 && point[i + 1][j + 1] == 1 && point[i + 2][j + 2] == 0 && point[i + 3][j + 3] == 0 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 1)
                {    s += 300;p++;}
                else if (j - 3 >= 0 && j + 2 <= 15 && i - 3 >= 0 && i + 2 <= 15 && point[i + 1][j + 1] == 0 && point[i + 2][j + 2] == 0 && point[i - 3][j - 3] == 0 && point[i - 2][j - 2] == 1 && point[i - 1][j - 1] == 1)
                {    s += 300;p++;}
                else if (j - 2 >= 0 && j + 3 <= 15 && i - 2 >= 0 && i + 3 <= 15 && point[i + 1][j + 1] == 1 && point[i + 2][j + 2] == 1 && point[i + 3][j + 3] == 0 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 0)
                {    s += 300;p++;}
                else if (j - 3 >= 0 && j + 2 <= 15 && i - 3 >= 0 && i + 2 <= 15 && point[i + 1][j + 1] == 1 && point[i + 2][j + 2] == 0 && point[i - 3][j - 3] == 0 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 1)
                {    s += 300;p++;}
                else if (j - 4 >= 0 && j + 1 <= 15 && i - 4 >= 0 && i + 1 <= 15 && point[i + 1][j + 1] == 0 && point[i - 4][j - 4] == 0 && point[i - 3][j - 3] == 0 && point[i - 2][j - 2] == 1 && point[i - 1][j - 1] == 1)
                {    s += 300;p++;}
            }
            //电脑活二
            {
                if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 0 && point[i + 1][j + 1] == 2 && point[i + 2][j + 2] == 0)
                    s += 200;
                else if (j - 3 >= 0 && j + 1 <= 15 && i - 3 >= 0 && i + 1 <= 15 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 2 && point[i + 1][j + 1] == 0 && point[i - 3][j - 3] == 0)
                    s += 200;
                else if (j - 1 >= 0 && j + 3 <= 15 && i - 1 >= 0 && i + 3 <= 15 && point[i + 2][j + 2] == 0 && point[i - 1][j - 1] == 0 && point[i + 1][j + 1] == 2 && point[i + 3][j + 3] == 0)
                    s += 200;
                else if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 2 && point[i + 1][j + 1] == 0 && point[i + 2][j + 2] == 0)
                    s += 200;
            }
            //玩家冲三
            {
                if (j - 1 >= 0 && j + 4 <= 15 && i - 1 >= 0 && i + 4 <= 15 && point[i + 1][j + 1] == 1 && point[i + 2][j + 2] == 0 && point[i + 3][j + 3] == 1 && point[i + 4][j + 4] == 0 && point[i - 1][j - 1] == 0)
                    s += 180;
                else if (j - 2 >= 0 && j + 3 <= 15 && i - 2 >= 0 && i + 3 <= 15 && point[i + 1][j + 1] == 0 && point[i + 2][j + 2] == 1 && point[i + 3][j + 3] == 0 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 1)
                    s += 180;
                else if (j - 4 >= 0 && j + 1 <= 15 && i - 4 >= 0 && i + 1 <= 15 && point[i + 1][j + 1] == 0 && point[i - 4][j - 4] == 0 && point[i - 3][j - 3] == 1 && point[i - 2][j - 2] == 1 && point[i - 1][j - 1] == 0)
                    s += 180;
                else if (j - 1 >= 0 && j + 4 <= 15 && i - 1 >= 0 && i + 4 <= 15 && point[i + 1][j + 1] == 0 && point[i + 2][j + 2] == 1 && point[i + 3][j + 3] == 1 && point[i + 4][j + 4] == 0 && point[i - 1][j - 1] == 0)
                    s += 180;
                else if (j - 3 >= 0 && j + 2 <= 15 && i - 3 >= 0 && i + 2 <= 15 && point[i + 1][j + 1] == 1 && point[i + 2][j + 2] == 0 && point[i - 3][j - 3] == 0 && point[i - 2][j - 2] == 1 && point[i - 1][j - 1] == 0)
                    s += 180;
                else if (j - 4 >= 0 && j + 1 <= 15 && i - 4 >= 0 && i + 1 <= 15 && point[i + 1][j + 1] == 0 && point[i - 4][j - 4] == 0 && point[i - 3][j - 3] == 1 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 1)
                    s += 180;
            }
            //电脑冲二
            {
                if (j - 2 >= 0 && j + 3 <= 15 && i - 2 >= 0 && i + 3 <= 15 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 0 && point[i + 1][j + 1] == 0 && point[i + 2][j + 2] == 2 && point[i + 3][j + 3] == 0)
                    s += 100;
                else if (j - 4 >= 0 && j + 1 <= 15 && i - 4 >= 0 && i + 1 <= 15 && point[i - 2][j - 2] == 2 && point[i - 1][j - 1] == 0 && point[i + 1][j + 1] == 0 && point[i - 3][j - 3] == 0 && point[i - 4][j - 4] == 0)
                    s += 100;
                else if (j - 1 >= 0 && j + 4 <= 15 && i - 1 >= 0 && i + 4 <= 15 && point[i + 2][j + 2] == 2 && point[i - 1][j - 1] == 0 && point[i + 1][j + 1] == 0 && point[i + 3][j + 3] == 0 && point[i + 4][j + 4] == 0)
                    s += 100;
                else if (j - 3 >= 0 && j + 2 <= 15 && i - 3 >= 0 && i + 2 <= 15 && point[i - 2][j - 2] == 2 && point[i - 1][j - 1] == 0 && point[i + 1][j + 1] == 0 && point[i + 2][j + 2] == 0 && point[i - 3][j - 3] == 0)
                    s += 100;
            }
            //玩家活二
            {
                if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 0 && point[i + 1][j + 1] == 1 && point[i + 2][j + 2] == 0)
                    s += 50;
                else if (j - 3 >= 0 && j + 1 <= 15 && i - 3 >= 0 && i + 1 <= 15 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 1 && point[i + 1][j + 1] == 0 && point[i - 3][j - 3] == 0)
                    s += 50;
                else if (j - 1 >= 0 && j + 3 <= 15 && i - 1 >= 0 && i + 3 <= 15 && point[i + 2][j + 2] == 0 && point[i - 1][j - 1] == 0 && point[i + 1][j + 1] == 1 && point[i + 3][j + 3] == 0)
                    s += 50;
                else if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 1 && point[i + 1][j + 1] == 0 && point[i + 2][j + 2] == 0)
                    s += 50;
            }
            //玩家冲二
            {
                if (j - 2 >= 0 && j + 3 <= 15 && i - 2 >= 0 && i + 3 <= 15 && point[i - 2][j - 2] == 0 && point[i - 1][j - 1] == 0 && point[i + 1][j + 1] == 0 && point[i + 2][j + 2] == 1 && point[i + 3][j + 3] == 0)
                    s += 10;
                else if (j - 4 >= 0 && j + 1 <= 15 && i - 4 >= 0 && i + 1 <= 15 && point[i - 2][j - 2] == 1 && point[i - 1][j - 1] == 0 && point[i + 1][j + 1] == 0 && point[i - 3][j - 3] == 0 && point[i - 4][j - 4] == 0)
                    s += 10;
                else if (j - 1 >= 0 && j + 4 <= 15 && i - 1 >= 0 && i + 4 <= 15 && point[i + 2][j + 2] == 1 && point[i - 1][j - 1] == 0 && point[i + 1][j + 1] == 0 && point[i + 3][j + 3] == 0 && point[i + 4][j + 4] == 0)
                    s += 10;
                else if (j - 3 >= 0 && j + 2 <= 15 && i - 3 >= 0 && i + 2 <= 15 && point[i - 2][j - 2] == 1 && point[i - 1][j - 1] == 0 && point[i + 1][j + 1] == 0 && point[i + 2][j + 2] == 0 && point[i - 3][j - 3] == 0)
                    s += 10;
            }
        }
        //“/”方向
        {
            //电脑五连
            {
                for (k = 1; k <= 5; k++)
                    if (i + k <= 15 && j - k >= 0 && point[i + k][j - k] == 2)
                        d++;
                    else break;
                for (k = 1; k <= 5; k++)
                    if (i - k >= 0 && j + k <= 15 && point[i - k][j + k] == 2)
                        d++;
                    else break;
                if (d >= 4)
                    s += 100000;
            }
            //玩家五连
            {
                d = 0;
                for (k = 1; k < 5; k++)
                {
                    if (j - k >= 0 && i + k <= 15 && point[i + k][j - k] == 1)
                        d++;
                    else break;
                }
                for (k = 1; k < 5; k++)
                {
                    if (j + k <= 15 && i - k >= 0 && point[i - k][j + k] == 1)
                        d++;
                    else break;
                }
                if (d >= 4)
                    s += 666666;
            }
            //电脑活四
            {
                d = 0;
                for (k = 1; k < 5; k++)
                {
                    if (j - k >= 0 && i + k <= 15 && point[i + k][j - k] == 2)
                        d++;
                    else if (j - k >= 0 && i + k <= 15 && point[i + k][j - k] == 0)
                    {
                        d++;
                        break;
                    }
                    else break;
                }
                for (k = 1; k < 5; k++)
                {
                    if (j + k <= 15 && i - k >= 0 && point[i - k][j + k] == 2)
                        d++;
                    else if (j + k <= 15 && i - k >= 0 && point[i - k][j + k] == 0)
                    {
                        d++;
                        break;
                    }
                    else break;
                }
                if (d >= 5)
                    s += 444444;
            }
            //电脑冲四
            {
                if (j - 1 >= 0 && i - 1 >= 0 && j + 3 <= 15 && j + 3 <= 15 && point[i - 1][j + 1] == 0 && point[i + 1][j - 1] == 2 && point[i + 2][j - 2] == 2 && point[i + 3][j - 3] == 2 && ((j + 2 <= 15 && i - 2 >= 0 && point[i - 2][j + 2] == 0) || (i + 4 <= 15 && j - 4 >=0 && point[i + 4][j - 4] == 0)))
                {    s += 15000;l++;}
                else if (j - 2 >= 0 && i - 2 >= 0 && j + 2 <= 15 && i + 2 <= 15 && point[i - 2][j + 2] == 0 && point[i + 1][j - 1] == 2 && point[i + 2][j - 2] == 2 && point[i - 1][j + 1] == 2 && ((j + 3 <= 15 && i - 3 >= 0 && point[i - 3][j + 3] == 0) || (i + 3 <= 15 && j - 3 >= 0 && point[i + 3][j - 3] == 0)))
                {    s += 15000;l++;}
                else if (j - 3 >= 0 && i - 3 >= 0 && j + 1 <= 15 && i + 1 <= 15 && point[i - 3][j + 3] == 0 && point[i + 1][j - 1] == 2 && point[i - 2][j + 2] == 2 && point[i - 1][j + 1] == 2 && ((j + 4 <= 15 && i - 4 >= 0 && point[i - 4][j + 4] == 0) || (i + 2 <= 15 && j - 2 >= 0 && point[i + 2][j - 2] == 0)))
                {    s += 15000;l++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i - 4][j + 4] == 0 && point[i - 3][j + 3] == 2 && point[i - 2][j + 2] == 2 && point[i - 1][j + 1] == 2 && ((j + 5 <= 15 && i - 5 >= 0 && point[i - 5][j + 5] == 0) || (i + 1 <= 15 && j -1 >= 0 && point[i + 1][j - 1] == 0)))
                {    s += 15000;l++;}
                else if (j - 1 >= 0 && j + 3 <= 15 && i - 1 >= 0 && i + 3 <= 15 && point[i + 1][j - 1] == 2 && point[i + 2][j - 2] == 2 && point[i + 3][j - 3] == 2 && point[i + 4][j - 4] == 0)
                {    s += 15000;l++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i + 1][j - 1] == 2 && point[i + 2][j - 2] == 2 && point[i + 3][j - 3] == 0 && point[i - 1][j + 1] == 2)
                {    s += 15000;l++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && i - 3 >= 0 && i + 1 <= 15 && point[i + 1][j - 1] == 2 && point[i + 2][j - 2] == 0 && point[i - 2][j + 2] == 2 && point[i - 1][j + 1] == 2)
                {    s += 15000;l++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i + 1][j - 1] == 0 && point[i - 3][j + 3] == 2 && point[i - 2][j + 2] == 2 && point[i - 1][j + 1] == 2)
                {    s += 15000;l++;}
                else if (j + 4 <= 15 && i + 4 <= 15 && point[i + 1][j -1] == 0 && point[i + 2][j - 2] == 2 && point[i + 3][j - 3] == 2 && point[i + 4][j - 4] == 2)
                {    s += 15000;l++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i + 1][j -1] == 2 && point[i + 3][j - 3] == 2 && point[i - 2][j + 2] == 2 && point[i - 1][j + 1] == 2)
                {    s += 15000;l++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && i - 3 >= 0 && i + 1 <= 15 && point[i + 1][j - 1] == 2 && point[i - 3][j + 3] == 2 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 2)
                {    s += 15000;l++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i - 4][j + 4] == 2 && point[i - 3][j + 3] == 0 && point[i - 2][j + 2] == 2 && point[i - 1][j + 1] == 2)
                {    s += 15000;l++;}
                else if (j + 4 <= 15 && i + 4 <= 15 && point[i + 1][j - 1] == 2 && point[i - 2][j - 2] == 2 && point[i + 3][j - 3] == 0 && point[i + 4][j - 4] == 2)
                {    s += 15000;l++;}
                else if (j - 1 >= 0 && j + 3 <= 15 && i - 1 >= 0 && i + 3 <= 15 && point[i + 1][j - 1] == 2 && point[i + 2][j - 2] == 0 && point[i + 3][j - 3] == 2 && point[i - 1][j + 1] == 2)
                {    s += 15000;l++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i + 2][j - 2] == 2 && point[i + 1][j - 1] == 0 && point[i - 2][j + 2] == 2 && point[i - 1][j + 1] == 2)
                {    s += 15000;l++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i - 4][j -+4] == 2 && point[i - 3][j + 3] == 2 && point[i - 2][j + 2] == 2 && point[i - 1][j + 1] == 0)
                {    s += 15000;l++;}
                else if (j + 4 <= 15 && i + 4 <= 15 && point[i + 1][j - 1] == 2 && point[i + 2][j - 2] == 0 && point[i + 3][j - 3] == 2 && point[i + 4][j - 4] == 2)
                {    s += 15000;l++;}
                else if (j - 1 >= 0 && j + 3 <= 15 && i - 1 >= 0 && i + 3 <= 15 && point[i + 1][j - 1] == 0 && point[i + 2][j - 2] == 2 && point[i + 3][j - 3] == 2 && point[i - 1][j + 1] == 2)
                {    s += 15000;l++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && i - 3 >= 0 && i + 1 <= 15 && point[i + 1][j - 1] == 2 && point[i - 3][j + 3] == 2 && point[i - 2][j + 2] == 2 && point[i - 1][j + 1] == 0)
                {    s += 15000;l++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i - 4][j + 4] == 2 && point[i - 3][j + 3] == 2 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 2)
                {    s += 15000;l++;}
            }
            //玩家活四
            {
                d = 0;
                for (k = 1; k < 5; k++)
                {
                    if (j - k >= 0 && i+ k <= 15 && point[i + k][j - k] == 1)
                        d++;
                    else if (j - k >= 0 && i + k <= 15 && point[i + k][j - k] == 0)
                    {
                        d++;
                        break;
                    }
                    else break;
                }
                for (k = 1; k < 5; k++)
                {
                    if (j + k <= 15 && i - k >= 0 && point[i - k][j + k] == 1)
                        d++;
                    else if (j + k <= 15 && i - k >= 0 &&  point[i - k][j + k] == 0)
                    {
                        d++;
                        break;
                    }
                    else break;
                }
                if (d >= 5)
                    s += 30000;
            }
            //电脑活三
            {
                if (j - 1 >= 0 && j + 4 <= 15 && i - 1 >= 0 && i + 4 <= 15 && point[i + 1][j - 1] == 2 && point[i + 2][j - 2] == 2 && point[i + 3][j - 3] == 0 && point[i + 4][j - 4] == 0 && point[i - 1][j + 1] == 0)
                {   s += 1000;l++;}
                else if (j - 2 >= 0 && j + 3 <= 15 && i - 2 >= 0 && i + 3 <= 15 && point[i + 1][j - 1] == 2 && point[i + 2][j - 2] == 0 && point[i + 3][j - 3] == 0 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 2)
                {   s += 1000;l++;}
                else if (j - 3 >= 0 && j + 2 <= 15 && i - 3 >= 0 && i + 2 <= 15 && point[i + 1][j - 1] == 0 && point[i + 2][j - 2] == 0 && point[i - 3][j + 3] == 0 && point[i - 2][j + 2] == 2 && point[i - 1][j + 1] == 2)
                {   s += 1000;l++;}
                else if (j - 2 >= 0 && j + 3 <= 15 && i - 2 >= 0 && i + 3 <= 15 && point[i + 1][j - 1] == 2 && point[i + 2][j - 2] == 2 && point[i + 3][j - 3] == 0 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 0)
                {   s += 1000;l++;}
                else if (j - 3 >= 0 && j + 2 <= 15 && i - 3 >= 0 && i + 2 <= 15 && point[i + 1][j - 1] == 2 && point[i + 2][j - 2] == 0 && point[i - 3][j + 3] == 0 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 2)
                {   s += 1000;l++;}
                else if (j - 4 >= 0 && j + 1 <= 15 && i - 4 >= 0 && i + 1 <= 15 && point[i + 1][j - 1] == 0 && point[i - 4][j + 4] == 0 && point[i - 3][j + 3] == 0 && point[i - 2][j + 2] == 2 && point[i - 1][j + 1] == 2)
                {   s += 1000;l++;}
            }
            //玩家冲四
            {
                if (j - 1 >= 0 && i - 1 >= 0 && j + 3 <= 15 && j + 3 <= 15 && point[i - 1][j + 1] == 0 && point[i + 1][j - 1] == 1 && point[i + 2][j - 2] == 1 && point[i + 3][j - 3] == 1 && ((j + 2 <= 15 && i - 2 >= 0 && point[i - 2][j + 2] == 0) || (i + 4 <= 15 && j - 4 >= 0 && point[i + 4][j - 4] == 0)))
                {    s += 800;p++;}
                else if (j - 2 >= 0 && i - 2 >= 0 && j + 2 <= 15 && i + 2 <= 15 && point[i - 2][j + 2] == 0 && point[i + 1][j - 1] == 1 && point[i + 2][j - 2] == 1 && point[i - 1][j + 1] == 1 && ((j + 3 <= 15 && i - 3 >= 0 && point[i - 3][j + 3] == 0) || (i + 3 <= 15 && j - 3 >= 0 && point[i + 3][j - 3] == 0)))
                {    s += 800;p++;}
                else if (j - 3 >= 0 && i - 3 >= 0 && j + 1 <= 15 && i + 1 <= 15 && point[i - 3][j + 3] == 0 && point[i + 1][j - 1] == 1 && point[i - 2][j + 2] == 1 && point[i - 1][j + 1] == 1 && ((j + 4 <= 15 && i - 4 >= 0 && point[i - 4][j + 4] == 0) || (i + 2 <= 15 && j - 2 >= 0 && point[i + 2][j - 2] == 0)))
                {    s += 800;p++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i - 4][j + 4] == 0 && point[i - 3][j + 3] == 1 && point[i - 2][j + 2] == 1 && point[i - 1][j + 1] == 1 && ((j + 5 <= 15 && i - 5 >= 0 && point[i - 5][j + 5] == 0) || (i + 1 <= 15 && j - 1 >= 0 && point[i + 1][j - 1] == 0)))
                {    s += 800;p++;}
                else if (j - 1 >= 0 && j + 3 <= 15 && i - 1 >= 0 && i + 3 <= 15 && point[i + 1][j - 1] == 1 && point[i + 2][j - 2] == 1 && point[i + 3][j - 3] == 1 && point[i + 4][j - 4] == 0)
                {    s += 800;p++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i + 1][j - 1] == 1 && point[i + 2][j - 2] == 1 && point[i + 3][j - 3] == 0 && point[i - 1][j + 1] == 1)
                {    s += 800;p++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && i - 3 >= 0 && i + 1 <= 15 && point[i + 1][j - 1] == 1 && point[i + 2][j - 2] == 0 && point[i - 2][j + 2] == 1 && point[i - 1][j + 1] == 1)
                {    s += 800;p++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i + 1][j - 1] == 0 && point[i - 3][j + 3] == 1 && point[i - 2][j + 2] == 1 && point[i - 1][j + 1] == 1)
                {    s += 800;p++;}
                else if (j + 4 <= 15 && i + 4 <= 15 && point[i + 1][j - 1] == 0 && point[i + 2][j - 2] == 1 && point[i + 3][j - 3] == 1 && point[i + 4][j - 4] == 1)
                {    s += 800;p++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i + 1][j - 1] == 1 && point[i + 3][j - 3] == 1 && point[i - 2][j + 2] == 1 && point[i - 1][j + 1] == 0)
                {    s += 800;p++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && i - 3 >= 0 && i + 1 <= 15 && point[i + 1][j - 1] == 1 && point[i - 3][j + 3] == 1 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 1)
                {    s += 800;p++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i - 4][j + 4] == 1 && point[i - 3][j + 3] == 0 && point[i - 2][j + 2] == 1 && point[i - 1][j + 1] == 1)
                {    s += 800;p++;}
                else if (j + 4 <= 15 && i + 4 <= 15 && point[i + 1][j - 1] == 1 && point[i - 2][j - 2] == 1 && point[i + 3][j - 3] == 0 && point[i + 4][j - 4] == 1)
                {    s += 800;p++;}
                else if (j - 1 >= 0 && j + 3 <= 15 && i - 1 >= 0 && i + 3 <= 15 && point[i + 1][j - 1] == 1 && point[i + 2][j - 2] == 0 && point[i + 3][j - 3] == 1 && point[i - 1][j + 1] == 1)
                {    s += 800;p++;}
                else if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i + 2][j - 2] == 1 && point[i + 1][j - 1] == 0 && point[i - 2][j + 2] == 1 && point[i - 1][j + 1] == 1)
                {    s += 800;p++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i - 4][j - +4] == 1 && point[i - 3][j + 3] == 1 && point[i - 2][j + 2] == 1 && point[i - 1][j + 1] == 0)
                {    s += 800;p++;}
                else if (j + 4 <= 15 && i + 4 <= 15 && point[i + 1][j - 1] == 1 && point[i + 2][j - 2] == 0 && point[i + 3][j - 3] == 1 && point[i + 4][j - 4] == 1)
                {    s += 800;p++;}
                else if (j - 1 >= 0 && j + 3 <= 15 && i - 1 >= 0 && i + 3 <= 15 && point[i + 1][j - 1] == 0 && point[i + 2][j - 2] == 1 && point[i + 3][j - 3] == 1 && point[i - 1][j + 1] == 1)
                {    s += 800;p++;}
                else if (j - 3 >= 0 && j + 1 <= 15 && i - 3 >= 0 && i + 1 <= 15 && point[i + 1][j - 1] == 1 && point[i - 3][j + 3] == 1 && point[i - 2][j + 2] == 1 && point[i - 1][j + 1] == 0)
                {    s += 800;p++;}
                else if (j - 4 >= 0 && i - 4 >= 0 && point[i - 4][j + 4] == 1 && point[i - 3][j + 3] == 1 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 1)
                {    s += 800;p++;}
            }
            //电脑冲三
            {
                if (j - 1 >= 0 && j + 4 <= 15 && i - 1 >= 0 && i + 4 <= 15 && point[i + 1][j - 1] == 2 && point[i + 2][j - 2] == 0 && point[i + 3][j - 3] == 2 && point[i + 4][j - 4] == 0 && point[i - 1][j + 1] == 0)
                    s += 550;
                else if (j - 2 >= 0 && j + 3 <= 15 && i - 2 >= 0 && i + 3 <= 15 && point[i + 1][j - 1] == 0 && point[i + 2][j - 2] == 2 && point[i + 3][j - 3] == 0 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 2)
                    s += 550;
                else if (j - 4 >= 0 && j + 1 <= 15 && i - 4 >= 0 && i + 1 <= 15 && point[i + 1][j - 1] == 0 && point[i - 4][j + 4] == 0 && point[i - 3][j + 3] == 2 && point[i - 2][j + 2] == 2 && point[i - 1][j + 1] == 0)
                    s += 550;
                else if (j - 1 >= 0 && j + 4 <= 15 && i - 1 >= 0 && i + 4 <= 15 && point[i + 1][j - 1] == 0 && point[i + 2][j - 2] == 2 && point[i + 3][j - 3] == 2 && point[i + 4][j - 4] == 0 && point[i - 1][j + 1] == 0)
                    s += 550;
                else if (j - 3 >= 0 && j + 2 <= 15 && i - 3 >= 0 && i + 2 <= 15 && point[i + 1][j - 1] == 2 && point[i + 2][j - 2] == 0 && point[i - 3][j + 3] == 0 && point[i - 2][j + 2] == 2 && point[i - 1][j + 1] == 0)
                    s += 550;
                else if (j - 4 >= 0 && j + 1 <= 15 && i - 4 >= 0 && i + 1 <= 15 && point[i + 1][j - 1] == 0 && point[i - 4][j + 4] == 0 && point[i - 3][j + 3] == 2 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 2)
                    s += 550;
            }
            //玩家活三
            {
                if (j - 1 >= 0 && j + 4 <= 15 && i - 1 >= 0 && i + 4 <= 15 && point[i + 1][j - 1] == 1 && point[i + 2][j - 2] == 1 && point[i + 3][j - 3] == 0 && point[i + 4][j - 4] == 0 && point[i - 1][j + 1] == 0)
                {    s += 300;p++;}
                else if (j - 2 >= 0 && j + 3 <= 15 && i - 2 >= 0 && i + 3 <= 15 && point[i + 1][j - 1] == 1 && point[i + 2][j - 2] == 0 && point[i + 3][j - 3] == 0 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 1)
                {    s += 300;p++;}
                else if (j - 3 >= 0 && j + 2 <= 15 && i - 3 >= 0 && i + 2 <= 15 && point[i + 1][j - 1] == 0 && point[i + 2][j - 2] == 0 && point[i - 3][j + 3] == 0 && point[i - 2][j + 2] == 1 && point[i - 1][j + 1] == 1)
                {    s += 300;p++;}
                else if (j - 2 >= 0 && j + 3 <= 15 && i - 2 >= 0 && i + 3 <= 15 && point[i + 1][j - 1] == 1 && point[i + 2][j - 2] == 1 && point[i + 3][j - 3] == 0 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 0)
                {    s += 300;p++;}
                else if (j - 3 >= 0 && j + 2 <= 15 && i - 3 >= 0 && i + 2 <= 15 && point[i + 1][j - 1] == 1 && point[i + 2][j - 2] == 0 && point[i - 3][j + 3] == 0 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 1)
                {    s += 300;p++;}
                else if (j - 4 >= 0 && j + 1 <= 15 && i - 4 >= 0 && i + 1 <= 15 && point[i + 1][j - 1] == 0 && point[i - 4][j + 4] == 0 && point[i - 3][j + 3] == 0 && point[i - 2][j + 2] == 1 && point[i - 1][j + 1] == 1)
                {    s += 300;p++;}
            }
            //电脑活二
            {
                if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 0 && point[i + 1][j - 1] == 2 && point[i + 2][j - 2] == 0)
                    s += 200;
                else if (j - 3 >= 0 && j + 1 <= 15 && i - 3 >= 0 && i + 1 <= 15 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 2 && point[i + 1][j - 1] == 0 && point[i - 3][j + 3] == 0)
                    s += 200;
                else if (j - 1 >= 0 && j + 3 <= 15 && i - 1 >= 0 && i + 3 <= 15 && point[i + 2][j - 2] == 0 && point[i - 1][j + 1] == 0 && point[i + 1][j - 1] == 2 && point[i + 3][j - 3] == 0)
                    s += 200;
                else if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 2 && point[i + 1][j - 1] == 0 && point[i + 2][j - 2] == 0)
                    s += 200;
            }
            //玩家冲三
            {
                if (j - 1 >= 0 && j + 4 <= 15 && i - 1 >= 0 && i + 4 <= 15 && point[i + 1][j - 1] == 1 && point[i + 2][j - 2] == 0 && point[i + 3][j - 3] == 1 && point[i + 4][j - 4] == 0 && point[i - 1][j + 1] == 0)
                    s += 180;
                else if (j - 2 >= 0 && j + 3 <= 15 && i - 2 >= 0 && i + 3 <= 15 && point[i + 1][j - 1] == 0 && point[i + 2][j - 2] == 1 && point[i + 3][j - 3] == 0 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 1)
                    s += 180;
                else if (j - 4 >= 0 && j + 1 <= 15 && i - 4 >= 0 && i + 1 <= 15 && point[i + 1][j - 1] == 0 && point[i - 4][j + 4] == 0 && point[i - 3][j + 3] == 1 && point[i - 2][j + 2] == 1 && point[i - 1][j + 1] == 0)
                    s += 180;
                else if (j - 1 >= 0 && j + 4 <= 15 && i - 1 >= 0 && i + 4 <= 15 && point[i + 1][j - 1] == 0 && point[i + 2][j - 2] == 1 && point[i + 3][j - 3] == 1 && point[i + 4][j - 4] == 0 && point[i - 1][j + 1] == 0)
                    s += 180;
                else if (j - 3 >= 0 && j + 2 <= 15 && i - 3 >= 0 && i + 2 <= 15 && point[i + 1][j - 1] == 1 && point[i + 2][j - 2] == 0 && point[i - 3][j + 3] == 0 && point[i - 2][j + 2] == 1 && point[i - 1][j + 1] == 0)
                    s += 180;
                else if (j - 4 >= 0 && j + 1 <= 15 && i - 4 >= 0 && i + 1 <= 15 && point[i + 1][j - 1] == 0 && point[i - 4][j + 4] == 0 && point[i - 3][j + 3] == 1 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 1)
                    s += 180;
            }
            //电脑冲二
            {
                if (j - 2 >= 0 && j + 3 <= 15 && i - 2 >= 0 && i + 3 <= 15 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 0 && point[i + 1][j- 1] == 0 && point[i + 2][j - 2] == 2 && point[i + 3][j - 3] == 0)
                    s += 100;
                else if (j - 4 >= 0 && j + 1 <= 15 && i - 4 >= 0 && i + 1 <= 15 && point[i - 2][j + 2] == 2 && point[i - 1][j + 1] == 0 && point[i + 1][j - 1] == 0 && point[i - 3][j + 3] == 0 && point[i - 4][j + 4] == 0)
                    s += 100;
                else if (j - 1 >= 0 && j + 4 <= 15 && i - 1 >= 0 && i + 4 <= 15 && point[i + 2][j - 2] == 2 && point[i - 1][j + 1] == 0 && point[i + 1][j - 1] == 0 && point[i + 3][j - 3] == 0 && point[i + 4][j - 4] == 0)
                    s += 100;
                else if (j - 3 >= 0 && j + 2 <= 15 && i - 3 >= 0 && i + 2 <= 15 && point[i - 2][j + 2] == 2 && point[i - 1][j + 1] == 0 && point[i + 1][j - 1] == 0 && point[i + 2][j - 2] == 0 && point[i - 3][j + 3] == 0)
                    s += 100;
            }
            //玩家活二
            {
                if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 0 && point[i + 1][j - 1] == 1 && point[i + 2][j - 2] == 0)
                    s += 50;
                else if (j - 3 >= 0 && j + 1 <= 15 && i - 3 >= 0 && i + 1 <= 15 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 1 && point[i + 1][j - 1] == 0 && point[i - 3][j + 3] == 0)
                    s += 50;
                else if (j - 1 >= 0 && j + 3 <= 15 && i - 1 >= 0 && i + 3 <= 15 && point[i + 2][j - 2] == 0 && point[i - 1][j + 1] == 0 && point[i + 1][j - 1] == 1 && point[i + 3][j - 3] == 0)
                    s += 50;
                else if (j - 2 >= 0 && j + 2 <= 15 && i - 2 >= 0 && i + 2 <= 15 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 1 && point[i + 1][j - 1] == 0 && point[i + 2][j - 2] == 0)
                    s += 50;
            }
            //玩家冲二
            {
                if (j - 2 >= 0 && j + 3 <= 15 && i - 2 >= 0 && i + 3 <= 15 && point[i - 2][j + 2] == 0 && point[i - 1][j + 1] == 0 && point[i + 1][j - 1] == 0 && point[i + 2][j - 2] == 1 && point[i + 3][j - 3] == 0)
                    s += 10;
                else if (j - 4 >= 0 && j + 1 <= 15 && i - 4 >= 0 && i + 1 <= 15 && point[i - 2][j + 2] == 1 && point[i - 1][j + 1] == 0 && point[i + 1][j - 1] == 0 && point[i - 3][j + 3] == 0 && point[i - 4][j + 4] == 0)
                    s += 10;
                else if (j - 1 >= 0 && j + 4 <= 15 && i - 1 >= 0 && i + 4 <= 15 && point[i + 2][j - 2] == 1 && point[i - 1][j + 1] == 0 && point[i + 1][j - 1] == 0 && point[i + 3][j - 3] == 0 && point[i + 4][j - 4] == 0)
                    s += 10;
                else if (j - 3 >= 0 && j + 2 <= 15 && i - 3 >= 0 && i + 2 <= 15 && point[i - 2][j + 2] == 1 && point[i - 1][j + 1] == 0 && point[i + 1][j - 1] == 0 && point[i + 2][j - 2] == 0 && point[i - 3][j + 3] == 0)
                    s += 10;
            }
        }
    }
    
    if(l>1)
        s+=20000;
    if(p>1)
        s+=10000;
    return s;
}


int First,now,ene=0;
double Count[3];
double score[15];
int G[15][15];
#ifdef _BOTZONE_ONLINE
#include "jsoncpp/json.h"

int tot = 0;

void placeAt(int x, int y, int c) {
    if (x < 0) return;
    G[x][y] = c; Count[c]++;
}

Json::Reader reader;
Json::Value input;

int A, B;

void read() {
    string str;
    getline(cin, str);
    reader.parse(str, input);
    int turnID = input["responses"].size();
    for (int i = 0; i < turnID; i++) {
        placeAt(input["requests"][i]["x"].asInt(), input["requests"][i]["y"].asInt(),2);
        placeAt(input["responses"][i]["x"].asInt(), input["responses"][i]["y"].asInt(),1);
    }
    placeAt(input["requests"][turnID]["x"].asInt(), input["requests"][turnID]["y"].asInt(),2);
    if (tot&1) {
        First=0;now=2;ene=1;
    }
    else {
        First=1;now=1;ene=2;
    }
    A = Count[1], B = Count[2];
    Count[0] = 225- Count[1] - Count[2];
}

Json::Value Position(int x,int y) {
    Json::Value action;
    action["x"] = x;
    action["y"] = y;
    return action;
}

void print(int x,int y) {
    Json::Value ret;
    //	myData = "---- " + to_string(A + B) + " ----\n" + myData + "\n";
    ret["response"] = Position(x,y);
    //	if (A + B < 3) ret["globaldata"] = myData;
    //	else ret["globaldata"] = input["globaldata"].asString() + myData;
    Json::FastWriter writer;
    cout << writer.write(ret) << endl;
}

#else
void read() {
    freopen("board.in","r",stdin);
    scanf("%d",&now);
    ene=3-now;
    //printf("[%d %d]\n", now, ene);
    for (int i=1;i<=15;i++) {
        for (int j=1;j<=15;j++) {
            int ch=getchar();
            while (ch<'0') ch=getchar();
            G[i][j]=ch-'0';
            Count[G[i][j]]++;
        }
    }
    freopen("/dev/tty", "r", stdin);
}

void print(int x, int y) {
    //	cout << myData << endl;
    freopen("decision.out","w",stdout);
    printf("%d %d\n", x, y);
    fclose(stdin);
    fclose(stdout);
}
#endif

int main() {
    for (int i = 0; i < 5; i++) score[i] = pow(10, i);
    score[2] *= 2.501;
    score[5] = 1e10;
    read();
    if (Count[0] == 15*15) {
        print(8,8);
        return 0;
    }
    if (Count[1]==Count[2]) First=1;
    else First=0;
    POS_AI result=Chess().ai(0, 0, 0, 0, G);
    print(result.x,result.y);
    return 0;
}

