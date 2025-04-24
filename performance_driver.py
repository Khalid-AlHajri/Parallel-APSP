import subprocess

# Path to your compiled C program
C_PROGRAM_PATH = "./bin/test_performance"

# List of input files (graph files of different sizes)
INPUT_FILES = ["graph.gr", "medium"]

# Range of threads you want to test
THREAD_COUNTS = [1, 2, 4, 8, 16]

# Output file
OUTPUT_FILE = "results.txt"

with open(OUTPUT_FILE, "w") as f:
    for input_file in INPUT_FILES:
        for threads in THREAD_COUNTS:
            print(f"Running with {threads} threads on input file {input_file}...")
            try:
                result = subprocess.run(
                    [C_PROGRAM_PATH, str(threads), "tests/" +input_file],
                    capture_output=True,
                    text=True,
                    check=True
                )
                output_line = result.stdout.strip()
                f.write(f"{input_file}, {threads} threads: {output_line}\n")
            except subprocess.CalledProcessError as e:
                f.write(f"{input_file}, {threads} threads: Error - {e}\n")

print(f"Results saved to {OUTPUT_FILE}")