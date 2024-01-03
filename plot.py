import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

# Before clustering
df = pd.read_csv("data/data.csv")
sns.scatterplot(x=df.x,
                y=df.y)
plt.title("k-means clustering k=3")

# After clustering
plt.figure()
df = pd.read_csv("data/output.csv")
sns.scatterplot(x=df.x, y=df.y,
                hue=df.cluster,
                palette=sns.color_palette("hls", n_colors=4))
plt.title("k-means clustering k=3")

plt.show()
