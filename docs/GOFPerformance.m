Trials = [ 1 2 3]
Num_processors = 6;

SerialRT = [86.50 86.15 86.93]
SerialUser = [85.80 85.40 86.28]
SerialSys = [0.68 0.72 0.62]
SerialCPU = SerialSys/Num_processors*100;

RowRT = [103.70 103.24 103.21]
RowUser = [102.99 102.31 102.27] 
RowSys = [0.68 0.90 0.90]
RowCPU = RowSys/Num_processors*100;


ColumnRT = [103.98 102.65 102.70]
ColumnUser = [103.02 101.87 101.82]
ColumnSys = [0.93 0.75 0.84]
ColumnCPU = ColumnSys/Num_processors*100;

RegionRT = [90.37 90.43 90.48]
RegionUser = [87.94 87.93 88.04]
RegionSys = [2.40 2.47 2.42]
RegionCPU = RegionSys/Num_processors*100;



plot(Trials, SerialRT, Trials, RowRT, Trials, ColumnRT, Trials, RegionRT);
legend('Serial RT', 'Row RT', 'Column RT', 'Region RT');
title('Real-Time Comparison');
xlabel('Time (s)');
ylabel('Threading Models');
print -dpng 'rt_threading_compared.png';

plot(Trials, SerialCPU, Trials, RowCPU, Trials, ColumnCPU, Trials, RegionCPU);
legend('Serial', 'Rows', 'Columns', 'Regions');
title('CPU Utilization');
ylabel('Utilization (%)');
xlabel('Trial');
print -dpng 'utilization_compared.png';
