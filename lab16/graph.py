import matplotlib.pyplot as plt
results = {}

with open("data.txt", "r") as f:
    for line in f:
        n, t, time_ms = line.split()
        n, t, time_ms = int(n), int(t), float(time_ms)
        
        if t not in results:
            results[t] = []
        results[t].append([n, time_ms])

plt.figure(figsize=(10, 6))
for t in sorted(results.keys()):
    data = sorted(results[t]) 
    plt.plot([r[0] for r in data], [r[1] for r in data], marker='o', label=f'{t} потоков')

plt.legend()
plt.grid(True)
plt.savefig('graph.png')
plt.show()
