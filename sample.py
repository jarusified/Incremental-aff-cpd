import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from ipca_aff_cpd import IPCAAFFCPD

# df, X: row: data points (KPs), col: time points (time)
df = pd.read_csv('../../sample_data/ross-df-256kp-500gvt_RbSec.csv')
X = np.array(df)
# dft, Xt: row: time points (time), col: data points (KPs)
Xt = X.transpose()
dft = df.transpose()

aff = IPCAAFFCPD(alpha=0.2)
change_points = []
pca_results = []
for i in range(Xt.shape[0]):
    change = aff.feed_predict(Xt[i, :])
    if change:
        print("Here is a change", i)
        change_points.append(i)

dft.plot.line(color="gray", linewidth=0.5, legend=False, alpha=0.5)
for change_point in change_points:
    plt.axvline(x=change_point, color="#c74e52")

plt.show()
