import matplotlib.pyplot as plt
import sys
import math
import numpy

logNs = []
genTimes = []
sortTimes = []
setSortTimes = []
for line in sys.stdin:
    nums = line.split(" ") #why is there not a different delimiter possible for stdin? Would be nice if different lines had different amount of inputs but you just wanted to keep reading till the end. Obv not that much extra complexity but still, like, why is there any?
    logN, genTime, sortTime, setSortTime = nums
    logNs.append(float(logN))
    genTimes.append(float(genTime))
    sortTimes.append(float(sortTime))
    setSortTimes.append(float(setSortTime))

logNs = numpy.array(logNs)
genTimes = numpy.array(genTimes)
sortTimes = numpy.array(sortTimes)
setSortTimes = numpy.array(setSortTimes)

plt.plot(logNs, numpy.log2(genTimes), label="Gen time")
plt.plot(logNs, numpy.log2(sortTimes), label="Sort Time")
plt.plot(logNs, numpy.log2(setSortTimes), label="Sort Time using Set")
plt.xlabel("logN")
plt.legend(loc="best")
plt.savefig('plotTime.png')

plt.clf()

ratio = numpy.array(setSortTimes) / numpy.array(sortTimes)
plt.plot(logNs, ratio, label="Ratio of sort times")
plt.legend(loc="best")
plt.xlabel("logN")
plt.savefig('plotRatio.png')