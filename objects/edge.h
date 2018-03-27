#ifndef EDGE_H
#define EDGE_H


class Edge
{
private:
    int V1, V2;
public:
    Edge() : V1(0), V2(0) { }
    Edge(int v1, int v2) : V1(v1), V2(v2) { }

    int v1() const { return V1; }
    int v2() const { return V2; }

    void setV1(int v1) { V1 = v1; }
    void setV2(int v2) { V2 = v2; }
};

#endif // EDGE_H
