# 🚀 Deadline-Aware CPU Scheduler Simulation

A simulation of a CPU scheduler that prioritizes processes based on their deadlines and scores. This project demonstrates a real-time scheduling algorithm with process expiration handling and logging capabilities. 🖥️

## 🌟 Features

- **⏳ Deadline-Aware Scheduling**: Processes are prioritized by score/deadline ratio.
- **📊 Dynamic Queue Management**: Handles process expiration and queue limits.
- **⚡ Multithreaded Simulation**: Runs process generation, scheduling, and execution in parallel.
- **📝 Comprehensive Logging**: Records all scheduling events with timestamps and metrics.
- **📈 Visualization Script**: Python script to generate performance plots from logs.

## 📋 Requirements

- 🖥️ C++17 compatible compiler
- 🐍 Python 3.x (for visualization)
- 📦 Matplotlib and Pandas (install via `pip install matplotlib pandas`)

## 🛠️ Installation & Usage

### 📥 Clone the repository:
```bash
git clone https://github.com/yourusername/Deadline-Aware-CPU-Scheduler.git
cd Deadline-Aware-CPU-Scheduler
```

### 🏗️ Compile the project:
```bash
g++ -o a.out main.cpp classes/cpu.cpp classes/queue.cpp classes/process.cpp classes/scheduler.cpp modules/process_generator.cpp logEvent.cpp -pthread
```

### ▶️ Run the simulation:
```bash
./a.out
```
Enter the number of CPUs and processes when prompted. 🖩

### 📊 Generate visualizations after simulation completes:
```bash
python3 plotLog.py
```
Follow prompts to input generated log files (drag & drop supported). 📂

## 📈 Key Metrics Tracked

- ✅ **Hit Rate**: Percentage of processes meeting deadlines
- 🎯 **Total Score**: Cumulative score of executed processes
- ⏳ **Average Waiting Time**
- ❌ **Expired Processes Count**

## 📜 Example Output

Logs are saved in `logs/log_YYYY-MM-DD_HH-MM-SS.csv` with columns:
```csv
time, event, cpu_id, process_id, execution_time, start_deadline, 
end_deadline, total_waiting_time, score, count_of_expire, count_of_misses, total_score
```

The visualization script generates 4 plots in the `plots/` directory:

- 📊 **Hit Rate Comparison**
- 📉 **Total Scores**
- ⏳ **Average Waiting Times**
- ❌ **Expired Processes Count**

## 📂 File Structure
```
├── 📁 classes/          # Core components (CPU, Process, Queue, Scheduler)
├── 📁 headers/          # Header files
├── 📁 modules/          # Process generation implementation
├── 📁 logs/             # Generated log files
├── 📁 plots/            # Visualization outputs
├── 📜 plot_results.py   # Python visualization script
└── 📜 main.cpp          # Entry point
```

