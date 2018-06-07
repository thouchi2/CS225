/* Your code here! */
#include "maze.h"
#include <map>
#include <queue>

SquareMaze::SquareMaze(){
    width = 0;
    height = 0;
    downW.clear();
    rightW.clear();
    store = -1;
}

void SquareMaze::makeMaze(int width, int height){
    this->width = width;
    this->height = height;
    int size = width * height;
    cells.addelements(size);

    for(int i = 0; i < size; i++){
        downW.push_back(true);
        rightW.push_back(true);
    }

    int x = 0;
    while(x < size - 1){
        for(int i = 0; i < size; i++){
            if((random() * 10 % 100) / (float) 100.0 > 0.9)
                continue;
            bool random = (rand() % 10 > 4);
            if((random && (i % width + 1) == width) ||
              (!random && (i / width + 1) == height)||
              (random && (cells.find(i) == cells.find(i + 1))) ||
              (!random && (cells.find(i) == cells.find(i + width))))
                continue;
            if(random){
                cells.setunion(i, i + 1);
                rightW[i] = false;
                x++;
            }
            else{
                cells.setunion(i, i + width);
                downW[i] = false;
                x++;
            }
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
    if(dir == 0 && x != width - 1)
        return (rightW[y * width + x] == false);
    if(dir == 1 && y != height - 1)
        return (downW[y * width + x] == false);
    if(dir == 2 && x != 0)
        return(rightW[y * width + x - 1] == false);
    if(dir == 3 && y != 0)
        return (downW[(y - 1) * width + x] == false);
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
    int i = y * width + x;
    if(dir == 0)
        rightW[i] = exists;
    if(dir == 1)
        downW[i] = exists;
}

vector<int> SquareMaze::solveMaze(){
    int size = height * width;
    map<int, int> path;
    vector<int> dir;
    vector<bool> visit;

    for(int i = 0; i < size; i++)
        visit.push_back(false);

    queue<int> q;
    q.push(0);

    int curr;
    int cx;
    int cy;

    while(!q.empty()){
        curr = q.front();
        cx = curr % width;
        cy = curr / height;
        q.pop();

        if(canTravel(cx, cy, 0) && !visit[curr + 1]){
            q.push(curr + 1);
            path[curr + 1] = curr;
            visit[curr + 1] = true;
        }
        if(canTravel(cx, cy, 1) && !visit[curr + width]){
            q.push(curr + width);
            path[curr + width] = curr;
            visit[curr + width] = true;
        }
        if(canTravel(cx, cy, 2) && !visit[curr - 1]){
            q.push(curr - 1);
            path[curr - 1] = curr;
            visit[curr - 1] = true;
        }
        if(canTravel(cx, cy, 3) && !visit[curr - width]){
            q.push(curr - width);
            path[curr - width] = curr;
            visit[curr - width] = true;
        }
    }

    int max = -1;
    int x = width;
    int c = 0;
    int begin;

    for(int i = 0; i < width; i++){
        c = 0;
        begin = 0;
        int end = width * (height - 1) + i;
        while(begin != end){
            end = path[end];
            c++;
        }
        if(c > max){
            max = c;
            x = i;
        }
    }

    int end = width * (height - 1) + x;

    while(begin != end){
        int d = getDir(end, path[end]);
        dir.push_back(d);
        end = path[end];
    }

    reverse(dir.begin(), dir.end());

    return dir;
}

int SquareMaze::getDir(int c, int n) const{
    int difference = c - n;
    if(difference == 1)
        return 0;
    if(difference == -1)
        return 2;
    if(difference == width)
        return 1;
    else
        return 3;
}

PNG * SquareMaze::drawMaze() const{
    PNG * out = new PNG(width * 10 + 1, height * 10 + 1);
    int size = width * height;
    for(int r = 0; r < height * 10 + 1; r++){
        (*out)(0, r)->red = 0;
        (*out)(0, r)->green = 0;
        (*out)(0, r)->blue = 0;
    }
    for(int c = 10; c < width * 10 + 1; c++){
        (*out)(c, 0)->red = 0;
        (*out)(c, 0)->green = 0;
        (*out)(c, 0)->blue = 0;
    }

    for(int i = 0; i < size; i++){
        int my = i / width;
        int mx = i % width;
        if(rightW[i]){
            for(int j = 0; j <= 10; j++){
                (*out)((mx + 1) * 10, my * 10 + j)->red = 0;
                (*out)((mx + 1) * 10, my * 10 + j)->green = 0;
                (*out)((mx + 1) * 10, my * 10 + j)->blue = 0;
            }
        }
        if(downW[i]){
            for(int j = 0; j <= 10; j++){
                (*out)(mx * 10 + j, (my + 1) * 10)->red = 0;
                (*out)(mx * 10 + j, (my + 1) * 10)->green = 0;
                (*out)(mx * 10 + j, (my + 1) * 10)->blue = 0;
            }
        }
    }
    return out;
}

PNG * SquareMaze::drawMazeWithSolution(){
    PNG * out = drawMaze();
    vector<int> sol = solveMaze();
    int x = 5; int y = 5;

    for(size_t i = 0; i < sol.size(); i++){
        if(sol[i] == 0){
            for(int j = 0; j < 11; j++){
                (*out)(x + j, y)->red = 255;
                (*out)(x + j, y)->green = 0;
                (*out)(x + j, y)->blue = 0;
            }
            x += 10;
        }
        if(sol[i] == 1){
            for(int j = 0; j < 11; j++)
			{
				(*out)(x, y + j)->red = 255;
				(*out)(x, y + j)->green = 0;
				(*out)(x, y + j)->blue = 0;
			}
			y += 10;
        }
        if(sol[i] == 2){
			for(int j = 0; j < 11; j++)
			{
				(*out)(x - j, y)->red = 255;
				(*out)(x - j, y)->green = 0;
				(*out)(x - j, y)->blue = 0;
			}
			x -= 10;
		}
        if(sol[i] == 3){
			for(int j = 0; j < 11; j++)
			{
				(*out)(x, y - j)->red = 255;
				(*out)(x, y - j)->green = 0;
				(*out)(x, y - j)->blue = 0;
			}
			y -= 10;
		}
    }

    int mx = x / 10;
    int my = height - 1;
    for(int i = 1; i < 10; i++){
        (*out)(mx * 10 + i, (my + 1) * 10)->red = 255;
		(*out)(mx * 10 + i, (my + 1) * 10)->green = 255;
		(*out)(mx * 10 + i, (my + 1) * 10)->blue = 255;
    }
    return out;
}
