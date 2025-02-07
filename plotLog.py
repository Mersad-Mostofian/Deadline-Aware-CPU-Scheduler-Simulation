import matplotlib.pyplot as plt
import pandas as pd
import datetime
import os


def hit_rate(row_index, col_index, count):
    hit_rates = []

    for file in files:
        miss_rate = (pd.read_csv(file).iloc[row_index, col_index] / count) * 100
        hit_rates.append(100-miss_rate)
    return hit_rates

def score(row_index, col_index):
    scores = []
    for file in files:
        s = pd.read_csv(file).iloc[row_index, col_index]
        scores.append(s)
    return scores

def expire(row_index, col_index):
    return score(row_index, col_index)

def AVG_waiting_time(row_index, col_index):
    waiting_times = score(row_index, col_index)
    return waiting_times

status = input("Do you have log(.csv) file? [Y/n] ")
files = []
while(status.lower() != "no" and status.lower() != "nope" and status.lower() != "n"):
    file = input("Enter file directory or Drag your file into terminal: ").strip().strip("'\"")
    files.append(file)
    status = input("Do you have log(.csv) file? [Y/n] ")

time = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
hit_rates = hit_rate(-1, -2, 50)


file_names = []
for file in files:
    file_name = os.path.basename(file)
    file_names.append(file_name)

plt.figure(figsize=(10, 5))
plt.bar(file_names, hit_rates, color="skyblue", edgecolor="black")

plt.xlabel("Log Files", fontsize=12)
plt.ylabel("Hit Rate (%)", fontsize=12)
plt.title("Hit Rate per Log File", fontsize=14)
plt.xticks(rotation=30)

for i, v in enumerate(hit_rates):
    plt.text(i, v + 2, f"{v}%", ha="center", fontsize=10)

plt.savefig(f"./plots/plot_HitRate_{time}.png")


scores = score(-1, -1)

plt.figure(figsize=(10, 5))
plt.bar(file_names, scores, color="skyblue", edgecolor="black")

plt.xlabel("Log Files", fontsize=12)
plt.ylabel("Score", fontsize=12)
plt.title("Score per Log File", fontsize=14)
plt.xticks(rotation=30)

for i, v in enumerate(scores):
    plt.text(i, v + 2, f"{v}", ha="center", fontsize=10)

plt.savefig(f"./plots/plot_Score_{time}")

waiting_times = AVG_waiting_time(-1, -4)
plt.figure(figsize=(10, 5))
plt.bar(file_names, waiting_times, color="skyblue", edgecolor="black")

plt.xlabel("Log Files", fontsize=12)
plt.ylabel("AVG-Waiting times", fontsize=12)
plt.title("AVG per Log File", fontsize=14)
plt.xticks(rotation=30)

for i, v in enumerate(waiting_times):
    plt.text(i, v + 2, f"{v}", ha="center", fontsize=10)

plt.savefig(f"./plots/plot_waitingtimes_{time}")

expires = expire(-1, -3)
plt.figure(figsize=(10, 5))
plt.bar(file_names, expires, color="skyblue", edgecolor="black")

plt.xlabel("Log Files", fontsize=12)
plt.ylabel("Count of Expires", fontsize=12)
plt.title("Count per Log File", fontsize=14)
plt.xticks(rotation=30)

for i, v in enumerate(expires):
    plt.text(i, v + 2, f"{v}", ha="center", fontsize=10)

plt.savefig(f"./plots/plot_expire_{time}")
