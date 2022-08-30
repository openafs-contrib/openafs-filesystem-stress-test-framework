import os
import matplotlib.pyplot as plt

current_dir = os.getcwd()
metrics = os.path.join(current_dir, 'metrics')
testDir = os.path.join(current_dir, 'test-directory')
if not os.path.exists(metrics):
    if os.path.exists(testDir):
        raise Exception("metrics directory does not exist, run the testing suite")
    else:
        raise Exception("metrics directory does not exist, initialize and run the testing suite")

for filename in os.listdir(metrics):
    if ".txt" in filename:
        with open(os.path.join(metrics, filename), 'r') as metric_file:
            data = metric_file.readlines()
            total_entries = len(data)
            x = list(range(0, total_entries))
            y = data
            name = filename[:len(filename)-4]
            plt.title(name)
            plt.plot(x, y)
            plt.savefig('metrics/'+name+'png')
            #plt.show()







