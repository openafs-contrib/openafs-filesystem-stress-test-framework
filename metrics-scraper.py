import os
import matplotlib.pyplot as plt
import numpy as np

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
            if "read" in filename:
                data = np.asarray(data, type=float)
                for i in range(0, len(data)):
                    if data[i] > 600000000:
                        data.remove(data[i])
            total_entries = len(data)
            x = list(range(0, total_entries))
            y = data
            name = filename[:len(filename)-4]
            plt.figure(figsize=(total_entries/100, 100), dpi=50)

            plt.title(name, fontsize='108')
            plt.scatter(x, y)
            plt.savefig('metrics/'+name+'.png')
            #plt.show()







