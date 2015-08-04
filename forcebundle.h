#ifndef FORCEBUNDLE
#define FORCEBUNDLE

#include <vector>
#include <fstream>

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

struct Point
{
    float X;
    float Y;
};

struct Node
{
    int nodeid;
    struct Point p;
};

struct Edge
{
    int source;
    int target;
};

class Forcebundle
{
public:
    Forcebundle(){}
    Forcebundle(std::vector<Point> nodes, std::vector<Edge> edges)
    {
        K = 0.1;
        S_initial = 0.1;
        P_initial = 1;
        P_rate = 2;
        C = 6;
        I_initial = 90;
        I_rate = 0.6666667;
        compatibility_threshold = 0.4;
        invers_quadratic_mode = false;
        eps = 1e-6;

        data_nodes = nodes;
        data_edges = filter_self_loops(edges);

        subdivision_points_for_edge = std::vector<std::vector<Point> >(data_edges.size());
        compatibility_list_for_edge = std::vector<std::vector<int> >(data_edges.size());
    }

    ~Forcebundle() {}

    /*** Main Bundling Loop Methods ***/
    void forcebundle()
    {
        float S = S_initial;
        int I = I_initial;
        int P = P_initial;

        initialize_edge_subdivisions();
        initialize_compatibility_lists();
        update_edge_division(P);
        compute_compatibility_lists();

        for(int cycle = 0; cycle < C; cycle++)
        {
            for(int iteration = 0; iteration < I; iteration++)
            {
                std::vector<std::vector<Point> > forces(data_edges.size());
                for(size_t edge = 0; edge < data_edges.size(); edge++)
                {
                    forces[edge] = apply_resulting_forces_on_subdivision_points(edge, P, S);
                }

                for(size_t e = 0; e < data_edges.size(); e++)
                {
                    for(int i = 0; i < P + 1; i++)
                    {
                        subdivision_points_for_edge[e][i].X += forces[e][i].X;
                        subdivision_points_for_edge[e][i].Y += forces[e][i].Y;
                    }
                }
            }

            S /= 2;
            P *= 2;
            I *= I_rate;

            update_edge_division(P);
        }
    }
    /*** ************************** ***/

    void saveCenters(const char * path)
    {
        std::ofstream outfile(path, std::ios::binary | std::ios::trunc);

        for(size_t i = 0; i < subdivision_points_for_edge.size(); i++)
        {
            std::vector<Point> current_points = subdivision_points_for_edge[i];

            for(size_t k = 0; k < current_points.size(); k++)
            {
                outfile << std::fixed << current_points[k].X << ", " << std::fixed << current_points[k].Y << ", \r\n";
            }
        }

        outfile.close();
    }

public:
    /*** Geometry Helper Methods ***/
    float vector_dot_product(Point p, Point q)
    {
        return p.X * q.X + p.Y * q.Y;
    }

    Point edge_as_vector(Edge P)
    {
        Point result;
        result.X = data_nodes[P.target].X - data_nodes[P.source].X;
        result.Y = data_nodes[P.target].Y - data_nodes[P.source].Y;
        return result;
    }

    float edge_length(Edge e)
    {
        return sqrtf(pow(data_nodes[e.source].X - data_nodes[e.target].X, 2) +
                    pow(data_nodes[e.source].Y - data_nodes[e.target].Y, 2));
    }

    float custom_edge_length(Point p, Point q)
    {
        return sqrtf(pow(p.X - q.X, 2) + pow(p.Y - q.Y, 2));
    }

    Point edge_midpoint(Edge e)
    {
        Point result;
        result.X = (data_nodes[e.source].X + data_nodes[e.target].X) / 2.0;
        result.Y = (data_nodes[e.source].Y + data_nodes[e.target].Y) / 2.0;
        return result;
    }

    float euclidean_distance(Point p, Point q)
    {
        return sqrtf(pow(p.X - q.X, 2) + pow(p.Y - q.Y, 2));
    }

    float compute_divided_edge_length(int e_idx)
    {
        float length = 0;
        for(size_t i = 1; i < subdivision_points_for_edge[e_idx].size(); i++)
        {
            float segment_length = euclidean_distance(
                subdivision_points_for_edge[e_idx][i],
                subdivision_points_for_edge[e_idx][i - 1]);
            length += segment_length;
        }
        return length;
    }

    Point project_point_on_line(Point p, Point Q1, Point Q2)
    {
        float L = sqrtf((Q2.X - Q1.X) * (Q2.X - Q1.X) + (Q2.Y - Q1.Y) * (Q2.Y - Q1.Y));
        float r = ((Q1.Y - p.Y) * (Q1.Y - Q2.Y) - (Q1.X - p.X) * (Q2.X - Q1.X)) / (L * L);

        Point result = {
            (Q1.X + r * (Q2.X - Q1.X)), (Q1.Y + r * (Q2.Y - Q1.Y))
        };

        return result;
    }

    /*** ********************** ***/

    /*** Initialization Methods ***/
    void initialize_edge_subdivisions()
    {
        for(size_t i = 0; i < data_edges.size(); i++)
        {
            if(P_initial == 1)
            {
                subdivision_points_for_edge[i].clear();
            }
            else
            {
                subdivision_points_for_edge[i].clear();
                subdivision_points_for_edge[i].push_back(data_nodes[data_edges[i].source]);
                subdivision_points_for_edge[i].push_back(data_nodes[data_edges[i].target]);
            }
        }
    }

    void initialize_compatibility_lists()
    {
        for(size_t i = 0; i < data_edges.size(); i++)
        {
            compatibility_list_for_edge[i].clear();
        }
    }

    std::vector<Edge> filter_self_loops(std::vector<Edge> edgelist)
    {
        std::vector<Edge> filtered_edge_list;

        for(size_t e = 0; e < edgelist.size(); e++)
        {
            if(data_nodes[edgelist[e].source].X != data_nodes[edgelist[e].target].X &&
                data_nodes[edgelist[e].source].Y != data_nodes[edgelist[e].target].Y)
            {
                filtered_edge_list.push_back(edgelist[e]);
            }
        }

        return filtered_edge_list;
    }
    /*** ************************* ***/

    /*** Force Calculation Methods ***/
    Point apply_spring_force(int e_idx, int i, float kP)
    {
        Point result;

        Point prev = subdivision_points_for_edge[e_idx][i - 1];
        Point next = subdivision_points_for_edge[e_idx][i + 1];
        Point crnt = subdivision_points_for_edge[e_idx][i];

        result.X = prev.X - crnt.X + next.X - crnt.X;
        result.Y = prev.Y - crnt.Y + next.Y - crnt.Y;

        result.X *= kP;
        result.Y *= kP;

        return result;
    }

    Point apply_electrostatic_force(int e_idx, int i, float S)
    {
        Point sum_of_forces = {0, 0};
        std::vector<int> compatible_edges_list = compatibility_list_for_edge[e_idx];

        for(size_t oe = 0; oe < compatible_edges_list.size(); oe++)
        {
            Point force = {
                subdivision_points_for_edge[compatible_edges_list[oe]][i].X - subdivision_points_for_edge[e_idx][i].X,
                subdivision_points_for_edge[compatible_edges_list[oe]][i].Y - subdivision_points_for_edge[e_idx][i].Y
            };

            if(abs(force.X) > eps || abs(force.Y) > eps)
            {
                float customedgelength = custom_edge_length(subdivision_points_for_edge[compatible_edges_list[oe]][i], subdivision_points_for_edge[e_idx][i]);
                float diff = (1 / pow(customedgelength, 1));

                sum_of_forces.X += force.X * diff;
                sum_of_forces.Y += force.Y * diff;
            }
        }

        return sum_of_forces;
    }

    std::vector<Point> apply_resulting_forces_on_subdivision_points(int e_idx, int P, float S)
    {
        float kP = K / (edge_length(data_edges[e_idx]) * (P + 1));
        std::vector<Point> resulting_forces_for_subdivision_points;
        Point temp = {0, 0};
        resulting_forces_for_subdivision_points.push_back(temp);

        for(int i = 1; i < P + 1; i++)
        {
            Point resulting_force = {0, 0};
            Point spring_force = apply_spring_force(e_idx, i, kP);
            Point electrostatic_force = apply_electrostatic_force(e_idx, i, S);

            resulting_force.X = S * (spring_force.X + electrostatic_force.X);
            resulting_force.Y = S * (spring_force.Y + electrostatic_force.Y);

            resulting_forces_for_subdivision_points.push_back(resulting_force);
        }

        resulting_forces_for_subdivision_points.push_back(temp);
        return resulting_forces_for_subdivision_points;
    }
    /*** ********************************* ***/

    /*** Edge Division Calculation Methods ***/
    void update_edge_division(int P)
    {
        for(size_t e_idx = 0; e_idx < data_edges.size(); e_idx++)
        {
            if(P == 1)
            {
                subdivision_points_for_edge[e_idx].push_back(data_nodes[data_edges[e_idx].source]);
                subdivision_points_for_edge[e_idx].push_back(edge_midpoint(data_edges[e_idx]));
                subdivision_points_for_edge[e_idx].push_back(data_nodes[data_edges[e_idx].target]);
            }
            else
            {
                float divided_edge_length = compute_divided_edge_length(e_idx);
                float segment_length = divided_edge_length / (P + 1);
                float current_segment_length = segment_length;
                std::vector<Point> new_subdivision_points;
                new_subdivision_points.push_back(data_nodes[data_edges[e_idx].source]);

                for(size_t i = 1; i < subdivision_points_for_edge[e_idx].size(); i++)
                {
                    float old_segment_length = euclidean_distance(subdivision_points_for_edge[e_idx][i], subdivision_points_for_edge[e_idx][i - 1]);

                    while(old_segment_length > current_segment_length)
                    {
                        float percent_position = current_segment_length / old_segment_length;
                        float new_subdivision_point_x = subdivision_points_for_edge[e_idx][i - 1].X;
                        float new_subdivision_point_y = subdivision_points_for_edge[e_idx][i - 1].Y;

                        new_subdivision_point_x += percent_position * (subdivision_points_for_edge[e_idx][i].X - subdivision_points_for_edge[e_idx][i - 1].X);
                        new_subdivision_point_y += percent_position * (subdivision_points_for_edge[e_idx][i].Y - subdivision_points_for_edge[e_idx][i - 1].Y);

                        Point temp = {new_subdivision_point_x, new_subdivision_point_y};
                        new_subdivision_points.push_back(temp);

                        old_segment_length -= current_segment_length;
                        current_segment_length = segment_length;
                    }

                    current_segment_length -= old_segment_length;
                }

                new_subdivision_points.push_back(data_nodes[data_edges[e_idx].target]);
                subdivision_points_for_edge[e_idx] = new_subdivision_points;
            }
        }
    }

    /*** Edge compatibility measures ***/
    float angle_compatibility(Edge P, Edge Q)
    {
        return abs(vector_dot_product(edge_as_vector(P), edge_as_vector(Q)) / (edge_length(P) * edge_length(Q)));
    }

    float scale_compatibility(Edge P, Edge Q)
    {
        float lavg = (edge_length(P) + edge_length(Q)) / 2.0;
        return 2.0 / (lavg / min(edge_length(P), edge_length(Q)) + max(edge_length(P), edge_length(Q)) / lavg);
    }

    float position_compatibility(Edge P, Edge Q)
    {
        float lavg = (edge_length(P) + edge_length(Q)) / 2.0;

        Point midP = {
            (data_nodes[P.source].X + data_nodes[P.target].X) / 2.0,
            (data_nodes[P.source].Y + data_nodes[P.target].Y) / 2.0
        };

        Point midQ = {
            (data_nodes[Q.source].X + data_nodes[Q.target].X) / 2.0,
            (data_nodes[Q.source].Y + data_nodes[Q.target].Y) / 2.0
        };

        return lavg / (lavg + euclidean_distance(midP, midQ));
    }

    float edge_visibility(Edge P, Edge Q)
    {
        Point I0 = project_point_on_line(data_nodes[Q.source], data_nodes[P.source], data_nodes[P.target]);
        Point I1 = project_point_on_line(data_nodes[Q.target], data_nodes[P.source], data_nodes[P.target]);

        Point midI = {(I0.X + I1.X) / 2.0, (I0.Y + I1.Y) / 2.0};
        Point midP = {
            (data_nodes[P.source].X + data_nodes[P.target].X) / 2.0,
            (data_nodes[P.source].Y + data_nodes[P.target].Y) / 2.0
        };

        return max(0, 1 - 2 * euclidean_distance(midP, midI) / euclidean_distance(I0, I1));
    }

    float visibility_compatibility(Edge P, Edge Q)
    {
        return min(edge_visibility(P, Q), edge_visibility(Q, P));
    }

    float compatibility_score(Edge P, Edge Q)
    {
        return angle_compatibility(P, Q) * scale_compatibility(P, Q) *
            position_compatibility(P, Q) * visibility_compatibility(P, Q);
    }

    bool are_compatible(Edge P, Edge Q)
    {
        return (compatibility_score(P, Q) >= compatibility_threshold);
    }

    void compute_compatibility_lists()
    {
        for(size_t e = 0; e < data_edges.size() - 1; e++)
        {
            for(size_t oe = e + 1; oe < data_edges.size(); oe++)
            {
                if(e == oe)
                    continue;
                else
                {
                    if(are_compatible(data_edges[e], data_edges[oe]))
                    {
                        compatibility_list_for_edge[e].push_back(oe);
                        compatibility_list_for_edge[oe].push_back(e);
                    }
                }
            }
        }
    }

public:
    std::vector<Point> data_nodes;
    std::vector<Edge> data_edges;
    std::vector<std::vector<int> > compatibility_list_for_edge;
    std::vector<std::vector<Point> > subdivision_points_for_edge;
    float K;
    float S_initial;
    int P_initial;
    int P_rate;
    int C;
    int I_initial;
    float I_rate;
    float compatibility_threshold;
    bool invers_quadratic_mode;
    float eps;
};

#endif // FORCEBUNDLE

