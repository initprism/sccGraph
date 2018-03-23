#include <string>
#include <vector>
#include <boost/graph/graphviz.hpp>

enum files_e { dax_h, yow_h, boz_h, zow_h, foo_cpp,
               foo_o, bar_cpp, bar_o, libfoobar_a,
               zig_cpp, zig_o, zag_cpp, zag_o,
                 libzigzag_a, killerapp, N };

const std::vector<std::string> GetNames()
{
  std::vector<std::string> v;
  v.push_back("dax.h");
  v.push_back("yow.h");
  v.push_back("boz.h");
  v.push_back("zow.h");
  v.push_back("foo.cpp");
  v.push_back("foo.o");
  v.push_back("bar.cpp");
  v.push_back("bar.o");
  v.push_back("libfoobar.a");
  v.push_back("zig.cpp");
  v.push_back("zig.o");
  v.push_back("zag.cpp");
  v.push_back("zag.o");
  v.push_back("libzigzag.a");
  v.push_back("killerapp");
  return v;
}

const std::vector<std::pair<int,int> > GetEdges()
{
  std::vector<std::pair<int,int> > v;
  v.push_back(std::make_pair(dax_h, foo_cpp));
  v.push_back(std::make_pair(dax_h, bar_cpp));
  v.push_back(std::make_pair(dax_h, yow_h));
  v.push_back(std::make_pair(yow_h, bar_cpp));
  v.push_back(std::make_pair(yow_h, zag_cpp));
  v.push_back(std::make_pair(boz_h, bar_cpp));
  v.push_back(std::make_pair(boz_h, zig_cpp));
  v.push_back(std::make_pair(boz_h, zag_cpp));
  v.push_back(std::make_pair(zow_h, foo_cpp));
  v.push_back(std::make_pair(foo_cpp, foo_o));
  v.push_back(std::make_pair(foo_o, libfoobar_a));
  v.push_back(std::make_pair(bar_cpp, bar_o));
  v.push_back(std::make_pair(bar_o, libfoobar_a));
  v.push_back(std::make_pair(libfoobar_a, libzigzag_a));
  v.push_back(std::make_pair(zig_cpp, zig_o));
  v.push_back(std::make_pair(zig_o, libzigzag_a));
  v.push_back(std::make_pair(zag_cpp, zag_o));
  v.push_back(std::make_pair(zag_o, libzigzag_a));
  v.push_back(std::make_pair(libzigzag_a, killerapp));
  return v;
}

int main()
{
  const std::vector<std::string> names = GetNames();
  const std::vector<std::pair<int,int> > used_by = GetEdges();

  const int n_edges = used_by.size();
  std::vector<int> weights(n_edges,1);

  typedef boost::adjacency_list<
    boost::vecS,
    boost::vecS,
    boost::undirectedS,
    boost::property< boost::vertex_color_t, boost::default_color_type >,
    boost::property< boost::edge_weight_t, int >
    > Graph;

  Graph g(used_by.begin(), used_by.end(), weights.begin(), N); //WORKS

  //Write graph to file
  {
    std::ofstream f("test.dot");
    boost::write_graphviz(f, g, boost::make_label_writer(&names[0]));
    f.close();
  }

  std::system("kgraphviewer test.dot");
}
