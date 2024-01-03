import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

# Before clustering
df = pd.read_csv("data/data.csv")
sns.scatterplot(x=df.f1,
                y=df.f2)
plt.title("k-means clustering")

# After clustering
plt.figure()
df = pd.read_csv("data/output.csv")
sns.scatterplot(x=df.f1, y=df.f2,
                hue=df.cluster,
                palette=sns.color_palette("hls", n_colors=6))
plt.title("k-means clustering")

plt.show()
