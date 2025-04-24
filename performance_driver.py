import subprocess
import csv

# Path to your compiled C program
C_PROGRAM_PATH = "./bin/test_performance"

# Input graph files
INPUT_FILES = ["graph.gr", "medium"]

# Thread counts to test
THREAD_COUNTS = [1, 2, 4, 8, 16]

# Output CSV file
OUTPUT_CSV = "results.csv"

# Prepare data matrix: first row is headers
matrix = [["Threads"] + INPUT_FILES]

for threads in THREAD_COUNTS:
    row = [threads]
    for input_file in INPUT_FILES:
        print(f"Running with {threads} threads on {input_file}...")
        try:
            result = subprocess.run(
                [C_PROGRAM_PATH, str(threads), "tests/" + input_file],
                capture_output=True,
                text=True,
                check=True
            )
            output = result.stdout.strip()
            row.append(output)
        except subprocess.CalledProcessError as e:
            row.append(f"Error")
    matrix.append(row)

# Write matrix to CSV
with open(OUTPUT_CSV, "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerows(matrix)

print(f"CSV results written to {OUTPUT_CSV}")
