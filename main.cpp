#include <ogdf/energybased/FMMMLayout.h>
using namespace ogdf;

int main(){
    Graph G;
    node a = G.newNode();
    node b = G.newNode();
    node c = G.newNode();
    G.newEdge(a, b);
    G.newEdge(b, c);

    GraphAttributes GA(G);

    FMMMLayout fmmm;
    fmmm.call(GA);

    cout << GA.x(a) << ", " << GA.y(a) << "; \n";
    cout << GA.x(b) << ", " << GA.y(b) << "; \n";
    cout << GA.x(c) << ", " << GA.y(c) << "; \n";
    return 0;
}
