#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <cstring>
#include <string>
#include <boost/graph/graphviz.hpp>

#define MAX_V 10000

using namespace std;
int v, e, visited[MAX_V + 1], x ,y ,r;
vector<vector<int>> scc;
vector<vector<int>> vt;
vector<vector<int>> rvt;
stack<int> st;

bool cmp(vector<int> x, vector<int> y){
	  return x[0] < y[0];
}

void dfs(int v){
	  visited[v] = true;
		for(int next : vt[v]){
			  if(visited[next])
					continue;
				dfs(next);
		}
		st.push(v);
}

void func(int v, int c){
	  visited[v] = true;
		scc[c].push_back(v);
		for(int next : rvt[v]){
			  if(visited[next])
					continue;
				func(next, c);
		}
}

int main(){
		printf("정점의 수 입력 : ");
	  scanf("%d", &v);
		printf("간선의 수 입력 : ");
	  scanf("%d", &e);

		vt.resize(v +1);
		rvt.resize(v + 1);
		if(e != 0)
			printf("연결된 노드 입력(%d - %d) : \n", 0, v-1);
		for(int i = 0; i < e; i++){
			  scanf("%d %d", &x, &y);
				vt[x].push_back(y);
				rvt[y].push_back(x);
		}
		for(int i = 0; i< v; i++){
			  if(visited[i])
					continue;
				dfs(i);
		}
		memset(visited, 0, sizeof(visited));
		while(st.size()){
			  int here = st.top();
				st.pop();
				if(visited[here])
					continue;
				scc.resize(++r);
				func(here, r -1);
		}
		for(int i = 0; i < r; i++)
			sort(scc[i].begin(), scc[i].end());
		sort(scc.begin(), scc.end(), cmp);
		printf("*******************************\n");
		printf("강연결요소의 개수 : %d\n", r);
		for(int i = 0; i < r; i++){
					printf("%d번째 scc : ", i+1 );
			  for(int x : scc[i]){
					printf("%d ", x);
				}
				printf("\n");
		}
		printf("*******************************\n");
		
//graphviz
		vector<string>names;
		vector<pair<int, int>>used_by;
		
		for(int i = 0; i< v; i++){
			  names.push_back(to_string(i));
		}

		for(int i = 0; i < r; i++){
			if(scc[i].size() != 1){
			  for(int x : scc[i]){
						for(int y : vt[x])
							for(int z : scc[i])
								if(z != x and y == z)
										used_by.push_back(make_pair(x, z));		  
				}
			}
		}
		const int n_edges = used_by.size();
		vector<int> weights(n_edges, 1);

	typedef boost::adjacency_list<
	    boost::vecS,
	    boost::vecS,
		  boost::directedS,
		  boost::property< boost::vertex_color_t, boost::default_color_type >,
		  boost::property< boost::edge_weight_t, int >
		  > Graph;	
		Graph g(used_by.begin(), used_by.end(), weights.begin(), v);

	  {
		    std::ofstream f("scc.dot");
		    boost::write_graphviz(f, g, boost::make_label_writer(&names[0]));
		    f.close();
		}
		system("dot scc.dot -Tpng -o scc.png");

		return 0;
}
