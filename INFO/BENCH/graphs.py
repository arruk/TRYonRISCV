import pandas as pd
import matplotlib.pyplot as plt
import glob
import seaborn as sns
csv_files = glob.glob('./*.csv')

op = int(input('which core (5-8)? (0 for general) '))
num = int(input('benchmarks: (1 - dhrystones) (2 - raystones) (3 - coremark) (4 - alltogether )'))

if num == 1:
    benchmark = "MIPS"
elif num == 2:
    benchmark = "RAYS"
elif num == 3:
    benchmark = "C/MHz"
else:
    benchmark = " "

if op == 0:
    kd = "bar"
    path="./"
    cols = ["CORE", "CPI", benchmark]
    colsa= ["CORE", "CPI"]
else:
    kd = "line"
    path=f"core{op}/"
    cols = ["BHT", "CPI", benchmark]
    colsa= ["BHT", "CPI"]

if num == 1:
    bench = pd.read_csv(path+"dhrystones.csv", usecols=cols)
elif num == 2:
    bench = pd.read_csv(path+"raystones.csv", usecols=cols)
    print(bench.head())
elif num == 3:
    bench = pd.read_csv(path+"coremark.csv", usecols=cols)
elif num == 4:
    bench = pd.DataFrame()
    x=0
    df0 = pd.read_csv(path+"dhrystones.csv", usecols=colsa)
    df1 = pd.read_csv(path+"raystones.csv" , usecols=colsa)
    df2 = pd.read_csv(path+"coremark.csv"  , usecols=colsa)
    df0['Benchmark']="dhrystones" 
    df1['Benchmark']="raystones"
    df2['Benchmark']="coremark"
    bench = pd.concat([df0, df1, df2])

    
if num == 4:
    ax = sns.lineplot(x=colsa[0], y='CPI', data=bench, hue='Benchmark')
else:
    ax = bench.plot(kind = kd,x=cols[0]) 
#ax.set_ylim([, None])
plt.show()
