load single.dat;
load col.dat;
load row.dat;
load full.dat;

count = col(:,1);

single = single(:, 2:end);
sin_avg = mean(single')/1000;

col = col(:, 2:end);
col_avg = mean(col')/1000;

row = row(:, 2:end);
row_avg = mean(row')/1000;

full = full(:, 2:end);
full_avg = mean(full')/1000;

plot( count, sin_avg, count, col_avg, count, row_avg, count, full_avg);
legend('Single Threaded', 'Column Decomposition', 'Row Decomposition', 'Full Decomposition')
xlabel('Grid Size (n by n)')
ylabel('Time (s)')
title('6-core Threaded Comparison')
print -dpng 'comparison.png'


colspeedup = sin_avg./col_avg;
rowspeedup = sin_avg./row_avg;
fullspeedup = sin_avg./full_avg;
normalized = sin_avg./sin_avg;
plot(count, colspeedup, count, rowspeedup, count, fullspeedup, count, normalized);
legend('Column Decomposition', 'Row Decomposition', 'Full Decomposition', 'Serial');
xlabel('Grid Size (n by n)');
ylabel('Speed-Up');
print -dpng 'speedup.png'

%Calculate efficiency
col_eff = sin_avg./(col_avg*6)*100;
row_eff = sin_avg./(row_avg*6)*100;
full_eff = sin_avg./(full_avg*6)*100;
plot(count, col_eff, count, row_eff, count, full_eff);
legend('Column Decomposition', 'Row Decomposition', 'Full Decomposition');
xlabel('Grid Size (n by n)');
ylabel('Efficiency (%)');
print -dpng 'efficiency.png';


