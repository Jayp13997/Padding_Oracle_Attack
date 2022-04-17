import os
import subprocess

testcaseIndices = ["1", "2", "3", "4", "5"]
testcaseDistro = [10, 10, 10, 10, 10]
totalPoints = 50
inputDir = "testcases/inputs"
solutionDir = "testcases/solutions"

# Make clean
print("Performing make clean")
p = subprocess.Popen(["make", "clean"], stdout = subprocess.PIPE, stderr = subprocess.PIPE)
output, errors = p.communicate()

print("Performing make")
# Make
p = subprocess.Popen(["make"], stdout = subprocess.PIPE, stderr = subprocess.PIPE)
output, errors = p.communicate()
output = output.decode('ascii')
errors = errors.decode('ascii')

if not errors == "" :
    print("Error during make. Please fix errors.")
    print("Error message:")
    print(errors)
    exit(0)

points = 0;
print("Setup complete. Running test cases.")

for (ind, dist) in zip(testcaseIndices, testcaseDistro) :
    inputFileName = os.path.join(inputDir, "input" + ind);
    print("Testing input " + inputFileName)
    
    solFileName = os.path.join(solutionDir, "solution" + ind);
    p = subprocess.Popen(["./attack", inputFileName], stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    output, errors = p.communicate()
    output = output.decode('ascii')

    solution = ""
    with open(solFileName, 'r') as f:
        solution = f.read()

    if output == solution :
        print("\tTest passed for input" + inputFileName)
        points = points + dist
    else :
        print("\tTest failed. Output discrepancy found")
        print("Please check output vs " + solFileName + ". Make sure to check for invisible whitespaces.")

print("Testing complete. Final Grade: " )
print("Public test cases:  " + str(points) + "/50")
print("Private test cases: ??/50")
