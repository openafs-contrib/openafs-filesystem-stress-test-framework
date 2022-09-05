import os
import matplotlib.pyplot as plt
import numpy as np
import math
import numpy.ma


#Plots given data from a file into a scatterplot
def plot(data_param, filename_param):
    total_entries = len(data_param)
    x = list(range(0, total_entries))
    y = data_param
    s = [500 for i in range(total_entries)]
    name = filename_param[:len(filename_param) - 4]
    plt.figure(figsize=(300, 100), dpi=50)
    plt.title(name, fontsize='108')
    plt.scatter(x, y, s=s)
    plt.savefig('metrics/' + name + '.png')


#Reads through the metrics branch and plots visualization for all the gathered data
def main():
    current_dir = os.getcwd()
    metrics = os.path.join(current_dir, 'metrics')
    test_dir = os.path.join(current_dir, 'test-directory')
    if not os.path.exists(metrics):
        if os.path.exists(test_dir):
            raise Exception("metrics directory does not exist, run the testing suite")
        else:
            raise Exception("metrics directory does not exist, initialize and run the testing suite")

    for filename in os.listdir(metrics):
        if ".txt" in filename and "file" not in filename:
            with open(os.path.join(metrics, filename), 'r') as metric_file:
                data = metric_file.readlines()
                if "read" in filename:
                    data = np.asarray(data, dtype=float)
                    data.tolist()
                    data_uncached = numpy.ma.masked_array(data, mask=data > 300000000)
                    data_cached = numpy.ma.masked_array(data, mask=data <= 300000000)

                    plot(data_cached, 'cached_' + filename)
                    plot(data_uncached, 'uncached_' + filename)
                else:
                    plot(data, filename)
                # plt.show()


if __name__ == "__main__":
    main()
