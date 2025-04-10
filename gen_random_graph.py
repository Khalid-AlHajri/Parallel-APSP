import random
import argparse

def generate_graph(num_nodes, density, weight_min, weight_max, output_file):
    edges = []
    total_weight = 0
    max_out_degree = 0
    out_degrees = [0] * (num_nodes + 1)

    for u in range(1, num_nodes + 1):
        for v in range(1, num_nodes + 1):
            if u != v and random.random() < density:
                weight = random.randint(weight_min, weight_max)
                edges.append((u, v, weight))
                total_weight += weight
                out_degrees[u] += 1

    max_out_degree = max(out_degrees)

    with open(output_file, 'w') as f:
        f.write(f"p sp {num_nodes} {len(edges)}\n")
        for u, v, w in edges:
            f.write(f"a {u} {v} {w}\n")
        f.write(f"c Total edge weight: {total_weight}\n")
        f.write(f"c Number of edges: {len(edges)}\n")
        f.write(f"c Max out-degree: {max_out_degree}\n")

    print(f"Graph with {num_nodes} nodes and {len(edges)} edges written to {output_file}.")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate a random .gr graph file.")
    parser.add_argument("--nodes", type=int, required=True, help="Number of nodes in the graph")
    parser.add_argument("--density", type=float, required=True, help="Probability of edge existence between two nodes")
    parser.add_argument("--weight_min", type=int, required=True, help="Minimum edge weight")
    parser.add_argument("--weight_max", type=int, required=True, help="Maximum edge weight")
    parser.add_argument("--output", type=str, default="tests/test.gr", help="Output .gr file name")

    args = parser.parse_args()

    if not (0 <= args.density <= 1):
        raise ValueError("Density must be between 0 and 1.")
    if args.weight_min > args.weight_max:
        raise ValueError("Minimum weight cannot be greater than maximum weight.")

    generate_graph(args.nodes, args.density, args.weight_min, args.weight_max, args.output)
