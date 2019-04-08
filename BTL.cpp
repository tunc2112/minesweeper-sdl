/*input
3 3 1
*/
/********************************
 *        GGGGG      GGGGG       *
 *       G          G            *
 *       G  GGG     G  GGG       *
 *       G   GG     G   GG       *
 *        GGGGG      GGGGG       *
 *                               *
 ********************************/
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
const int INF = 1000000;

int dx[] = {1, 1, 1, 0, 0, -1, -1, -1};
int dy[] = {1, -1, 0, 1, -1, 1, -1, 0};

class Minesweeper
{
	public :
		int n, m, boom, a[101][101];
		Minesweeper(int _n, int _m, int _boom)
		{
			n = _n;
			m = _m;
			boom = _boom;
		}	
		
		void setup()
		{
			memset(a, 0, sizeof(a));
			for(int i=1;i<=boom;i++)
			{
				int x, y;
				while(1)
				{
					x = (rand() % n) + 1;
					y = (rand() % m) + 1;
					if(a[x][y] == 0)
					{
						a[x][y] = -1;
						break;
					}
				}
			}
		}

		void in()
		{
			system("cls");
			for(int i=1;i<=n;i++)
			{
				for(int j=1;j<=m;j++)
				{
					if(a[i][j] < 1)
						cout << 'X' << ' ';
					if(a[i][j] == INF)
						cout << "  ";
					if(a[i][j] > 0 && a[i][j] < INF)
						cout << a[i][j] << ' ';
				}
				cout << endl;
			}
		}

		void loang(int x, int y)
		{
			a[x][y] = INF;
			int res = 0;
			for(int i=0;i<8;i++)
			{
				int xx = x + dx[i], yy = y + dy[i];
				if(xx >= 1 && xx <= n && yy >= 1 && yy <= m && a[xx][yy] == -1)
					++res;
			}
			if(res)
			{
				a[x][y] = res;
				return ;
			}
			for(int i=0;i<8;i++)
			{
				int xx = x + dx[i], yy = y + dy[i];
				if(xx >= 1 && xx <= n && yy >= 1 && yy <= m && a[xx][yy] == 0)
					loang(xx, yy);
			}
		}

		bool check()
		{
			int cnt = 0;
			for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++)
					if(a[i][j] == 0)
						return false;
			return true;
		}

		void play()
		{
			in();
			int x, y;
			while(cin >> x >> y)
			{
				if(a[x][y] == -1)
				{
					cout << "Ban ngu vl thua me roi :)))" << endl;
					return ;
				}
				loang(x, y);
				in();
				if(check())
				{
					cout << "Ban thang con me no roi ";
					return ;
				}
			}
		}
};

int main()
{
	srand(time(NULL));
	char c;
	while(cin >> c)
	{
		int n, m, b;
		cout << "nhap size va so bom ";
		cin >> n >> m >> b;
		system("cls");
		Minesweeper game(n, m, b);
		game.setup();
		game.play();
	}
}