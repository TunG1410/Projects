#include "PriorityQueue.cpp" // Su dung hang doi uu tien da tao
using namespace std;

// Canh co kieu la mot struct
struct Edge {
    int src, dest, weight; // Dinh nguon, dinh dich, trong so

    // Ham tao mot canh
    Edge(int s=0, int d=0, int w=0) : src(s), dest(d), weight(w) {}

    // Operator de so sanh cac canh theo trong khoi
    bool operator<(const Edge &other) {
        return weight<other.weight;
    }
};

// Lop do thi
class Graph {

    int V; // So luong dinh
    int** graph; // Ma tran de luu tru trong so cac canh (do thi vo huong)

public:
    // Ham tao do thi
    Graph(int vertices) : V(vertices) {
        // Khoi tao do thi voi V dinh
        graph = new int*[V];
        for (int i = 0; i < V; ++i) {
            graph[i] = new int[V];
            for (int j = 0; j < V; ++j) {
                graph[i][j] = 0; // Khoi tao tat ca trong so = 0
            }
        }
    }

    // Ham huy giai phong bo nho
    ~Graph() {
        for (int i = 0; i < V; ++i) {
            delete[] graph[i];
        }
        delete[] graph;
    }

    // Ham de them 1 canh co trong so vao do thi
    void addEdge(int src, int dest, int weight) {
        graph[src][dest] = weight;
        graph[dest][src] = weight;
    }

    // Thuat toan Prim tim cay khung nho nhat
    void primMST() {
        // Hang doi uu tien luu tru cac canh + trong so voi suc chua ban dau = V
        PriorityQueue<Edge> pq(V);

        // Tao mang va gia tri ban dau cho mang kiem tra 1 dinh da duoc duyet qua chua
        bool* inMST = new bool[V];
        for (int i = 0; i < V; ++i) {
            inMST[i] = false;
        }

        // Chon dinh dau tien la dinh bat dau
        int startVertex = 0;

        // So lan chon va tong trong so
        int times = 0, sumWeight = 0;

        cout<< "The PRIM algorithm finds the smallest spanning tree:\n";
        for (int count = 0; count < V - 1; ++count) {
            inMST[startVertex] = true; // Danh dau dinh sau khi duyet qua

            // Them cac canh vao hang doi uu tien
            for (int v = 0; v < V; ++v) {
                if (graph[startVertex][v] && !inMST[v]) {
                    pq.push(Edge(startVertex, v, graph[startVertex][v]));
                }
            }

            // Tim canh co trong so nho nhat noi dinh da duyet va dinh chua duyet
            while (pq.getSize()!=0 && inMST[pq.top().dest]) {
                pq.pop();
            }

            // Lay canh co trong so nho nhat
            if (pq.getSize()!=0) {
                Edge minEdge = pq.top();
                pq.pop();

                // Tinh so lan chon va tong trong so
                ++times;
                sumWeight+=minEdge.weight;

                // In ra canh da chon
                cout << "Times: "<< times << " | Edge: " << minEdge.src << " - " << minEdge.dest << " | Weight: " << minEdge.weight << "\n";

                // Chuyen den dinh ke tiep va tiep tuc vong lap
                startVertex = minEdge.dest;
            }
        }

        // In ra so lan chon va tong trong so
        cout << "Total weight: " << sumWeight << "\n";

        delete[] inMST;
    }
};

int main() {

    //==========< TAO SAN >==========
    // Example: Tao moi do thi voi 4 dinh
    Graph g(4);

    //Them cac canh va trong so
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 3);
    g.addEdge(2, 3, 5);
    //===========================

    //==========< NHAP >==========
    // int e, s, d, w;
    // cout << "Number of edges: "; cin >> e;
    // Graph g(e);
    // cout << "Edge: source - destination - weight\n";
    // for(int i = 0; i < e; ++i) {
    //     cout << "Edge " << i+1 << ": ";
    //     cin >> s >> d >> w;
    //     g.addEdge(s, d, w);
    // }
    // cout << "\n";
    //============================

    // Thuat toan Prim tim cau khung nho nhat
    g.primMST();

    return 0;
}