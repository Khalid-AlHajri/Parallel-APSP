import subprocess
import networkx as nx
import random
import string
import os

def graph_read_process(fpath):
    G = nx.DiGraph()
    strres = ''
    with open(fpath, 'r') as f:
        for line in f.readlines():
            if line.startswith('a'):
                toks = line.split()
                u, v, w = map(int, toks[1:])
                G.add_edge(u, v, weight=w)
    resmat = nx.all_pairs_dijkstra_path_length(G, weight='weight')
    resmat = {k:v for k,v in resmat}
    for i in sorted(G.nodes):
        for j in sorted(G.nodes):
            try:
                weight = resmat[i][j]
            except KeyError:
                weight = 2**31 - 1
            strres = strres + str(weight) + " "
    return strres

i = 1
while True:
    # Make some graph by invoking gen_random_graph.py
    curr_name = ''.join(random.choices(string.ascii_letters, k=15))
    fpath = '/tmp/' + curr_name
    # Generate the graph & save it on temporary storage
    subprocess.run(
        ["python3", "gen_random_graph.py", "--weight_min", "1", "--weight_max", "1000", "--density", ".10",
         "--nodes", "600", "--output", fpath]
    )

    # Run python script on it and result.
    respy = graph_read_process(fpath)        
    # Run C Parallel Program on it and save stdout
    program_name = './bin/validation_test'
    try:
        resc = subprocess.run(
        [program_name, str(random.randint(1, 32)), fpath],
        capture_output=True,
        text=True,
        check=True
    )
        text = resc.stdout.strip()
    except subprocess.CalledProcessError as e:
        print("ERROR RUNNING C PROGRAM")
    # Compare results
    print(text[:120])
    print(respy.strip()[:120])
    try:
        assert text == respy.strip()
    except AssertionError as e:
        print(f"Iteration {i} failed. Dumping original graph.")
        with open("graphdump", 'w') as f:
            f.write(open(fpath, 'r').read())
        os.remove(fpath)
        break
    print(f"Iteration {i} complete.")
    i = i + 1
    os.remove(fpath)